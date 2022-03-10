// Script to fit TH1F or TH2F histograms of the HEFT couplings to obtain their parametrised yield.
// Output: 
// - Plots = histogram+fitted function+equation 
// - JSON = dict with the parametrised fitted functions -> Handy for producing XML cards
//
// Author: laura.pereira.sanchez@cern.ch

#include "TROOT.h"
#include "TPave.h"
#include "TTreeReaderArray.h"
#include "TTreeReaderValue.h"
#include "TTreeReader.h"
#include "TH2F.h"
#include "TH1F.h"
#include "TF1.h"
#include "TF2.h"
#include <typeinfo>
#include "TLatex.h"
#include <string>
#include <unordered_map>
#include "TFormula.h"
#include <iostream>
#include <nlohmann/json.hpp>

TString  filename  = "../../../EFT_bbyy/bbyy_1D_2D_3D_scans_yield.root";
//TString  filename  = "../../../EFT_bbyy/XS_1D2D3D_scans.root";
using json = nlohmann::json;

std::vector <std::string> Regions = {"Tight_HM", "Loose_HM", "Tight_LM", "Loose_LM"};
//std::vector <std::string> Regions = {"NLO_XS"};

bool ModifyRange = false;

std::vector <std::string> Scans = {"chhh","ctth", "ctthh", "cgghh", "cggh", "ctthh_cgghh", "chhh_ctthh", "chhh_cgghh"}; 

//std::vector <std::string> Scans = {"chhh_ctthh_cgghh"}; // You still need to write a Fit3D function if you want that fit :)

std::vector <std::string> SplitString(std::string s, std::string delimiter){
  size_t pos = 0;
  std::string token;
  std::vector <std::string> split_vec;

  while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    split_vec.push_back(token);
    s.erase(0, pos + delimiter.length());
  }
  split_vec.push_back(s);
  return split_vec;
}

std::vector <TString> FitResult(std::unordered_map < std::string, const char* > Fit_poly, std::vector <float> par,  std::string poly){

  int n_par = par.size() -1;
  //std::cout << poly << std::endl;

  std::string output = Fit_poly[poly];

  std::vector <std::string> sub_output = SplitString(output, "+");

  std::vector <TString> sub_result;

  for (int i=0; i <= n_par; i++){
    TString line=sub_output[i];
    line = line.ReplaceAll("["+std::to_string(n_par-i)+"]",to_string(par[n_par-i]));
    line = line.ReplaceAll("**","^");
    int posx = line.Index("x^");
    if (posx != -1){
      line.Insert(posx+2,"{");
      line.Insert(posx+4,"}");
    }
    int posy = line.Index("y^");
    if (posy != -1){
      line.Insert(posy+2,"{");
      line.Insert(posy+4,"}");
    }

    line.ReplaceAll("*"," #upoint ");

    if (!line.Contains("0.000000")) sub_result.push_back(line);
  }

  std::vector <TString> FitResult;
  
  TString line;
  int k = 0;

  for (std::vector<TString>::iterator it_s=sub_result.begin(); it_s!=sub_result.end(); ++it_s){
    line += *it_s;
    if (k != sub_result.size()-1) line+="+";

    if (k == sub_result.size()-1 or k == 4 or k == 8 or k == 12 ){
      line.ReplaceAll("+-", "-");
      FitResult.push_back(line);
      line = "";
    }
    k+=1;
  }

  TString summary;

  for (std::vector <TString>::iterator it_f = FitResult.begin(); it_f!=FitResult.end(); ++it_f){
    summary.Append(*it_f);
  }

  summary.ReplaceAll(" #upoint "," * ");

  std::cout << "\n Best fit function = " << summary  <<  std::endl;

  return FitResult;
}


TString FitOutput(std::unordered_map < std::string, const char* > Fit_poly, std::vector<float> par,  std::string poly, std::string coupling){

  int n_par = par.size() -1;
  int total_p = n_par+1;
  int x = n_par+1;
  int y;

  std::vector<std::string> c_name = SplitString(coupling,"_");

  if (poly.find("_") != std::string::npos){
    total_p += 1;
    y = n_par+2; 
  }
  
  TString eq = Fit_poly[poly];

  eq.ReplaceAll("x", "@"+std::to_string(x));
  if (poly.find("_") != std::string::npos) eq.ReplaceAll("y", "@"+std::to_string(y));

  for (int z=0; z<=n_par; z++) {
    eq.ReplaceAll("["+std::to_string(z)+"]","@"+std::to_string(z));
  }

  TString output = "expr::yield_HH_ggF( '"+eq+"' ,";
  for (int z=0; z<=n_par; z++) {
    output+="HH_ggF_param_p"+std::to_string(z)+"["+std::to_string(par[z])+"] , ";
  }

for (int k=0; k<c_name.size();k++){
  if (c_name[k] == "chhh" or c_name[k] == "ctth") {
    output+=" "+c_name[k]+"[1,-10,10] ";
  } else{
    output+=" "+c_name[k]+"[0,-10,10] ";
  }
  if (k < c_name.size()-1) output+=",";
 }

output+=")";

  return  output;

}

TString Fit1D(TFile *f, std::string coupling, std::string region, std::unordered_map<std::string, const char *> Fit_poly, std::unordered_map<std::string, std::string> poly, std::unordered_map<std::string, std::string> name, std::vector <float> range_x, std::map<std::pair< std::string,std::string>, TString> ParamF){

  TString histo_name = coupling+"_"+region;

  TH1F* h = (TH1F*) f->Get("h_"+histo_name);

  // Assuming current binning (101 bins) with range -10, 10 and a granularity of 0.2 (x = 0 at bin 41):
  float low_range = (range_x[0]+10)/0.2+1;
  float upper_range = (range_x[1]+10)/0.2+1;
    
  h->GetXaxis()->SetRange(low_range,upper_range);

  TCanvas *c = new TCanvas("c", "c");

  TString c_name = name[coupling];
  TString Title_name;
  if (region == "NLO_XS"){
    Title_name = "\\sigma^{NLO}("+name[coupling]+")";
  } else {
    Title_name = "Yield("+name[coupling]+") in "+region;
  }    

  h->SetTitle(Title_name);
  h->GetXaxis()->SetTitle(c_name);
  h->GetYaxis()->SetTitle("Events");

  h->Draw("HIST");


  TF1 *fx = new TF1("fx",Fit_poly[poly[coupling]],range_x[0],range_x[1]);
  h->Fit(fx); //"Q"

  std::vector <float> par;

  for (int i=0;i <fx->GetNpar(); i++) par.push_back(fx->GetParameter(i));

  fx->Draw("SAME");

  TString FitR = FitResult(Fit_poly, par,  poly[coupling])[0];
  ParamF[std::make_pair(coupling,region)] = FitR;

  TLatex t(0.25,0.7,FitR);
  t.SetNDC(kTRUE);
  t.SetTextSize(0.03);
  t.Draw("SAME");

  system("mkdir -vp Fits");

  c->SaveAs("Fits/"+histo_name+".pdf");
  std::cout << "\n" << std::endl;

  delete c;

  TString output = FitOutput(Fit_poly, par, poly[coupling], coupling);
  return output;

}


TString Fit2D(TFile *f, std::string coupling, std::string region, std::unordered_map<std::string, const char *> Fit_poly, std::unordered_map<std::string, std::string> poly, std::unordered_map<std::string, std::string> name, std::unordered_map<std::string,std::vector<float>> range){

  TString histo_name = coupling+"_"+region;

  TH2F* h = (TH2F*) f->Get("h_"+histo_name);

  TCanvas *c = new TCanvas("c", "c", 800, 800);
  
  std::cout << coupling <<std::endl;  

  std::vector <std::string> c_names = SplitString(coupling,"_");

  TString c_x = name[c_names[0]];
  TString c_y = name[c_names[1]];

  std::cout << c_names[0] << std::endl;
  std::cout << c_names[1] << std::endl;

  TString Title_name = "Yield("+name[c_names[0]]+","+name[c_names[1]]+") in "+region;
  h->SetTitle(Title_name);
  h->GetXaxis()->SetTitle(c_x);
  h->GetYaxis()->SetTitle(c_y);
  h->GetZaxis()->SetTitle("Events");

  h->Draw("surf1");

  TF2 *fx = new TF2("fx",Fit_poly[poly[coupling]]);
  
  h->Fit(fx); //"Q"

  std::vector <float> par;

  for (int i=0;i <fx->GetNpar(); i++) par.push_back(fx->GetParameter(i));

  std::vector <TString> FitR = FitResult(Fit_poly, par, poly[coupling]);
  
  int v = 0;

  TLatex latex;
  latex.SetTextSize(0.02);
  latex.SetTextAlign(13); 
  latex.SetNDC(kTRUE);
  latex.DrawLatex(.05,.92, FitR[0]);
  if (FitR.size() > 1) latex.DrawLatex(.05,.90, FitR[1]);
  if (FitR.size() > 2) latex.DrawLatex(.05,.88, FitR[2]);
  if (FitR.size() > 3) std::cout << "WARNING --> Can't plot full function in plot " << std::endl;


  c->SaveAs("Fits/"+histo_name+".pdf");

  delete c;

  TString output = FitOutput(Fit_poly, par,  poly[coupling], coupling);
  return output;

  
}

int FitHistograms(){

  // Dictionary of polynomial functions

  std::unordered_map<std::string, const char *> Fit_poly;                                                    
  Fit_poly["x2"] = "[2]*x**2+[1]*x+[0]";
  Fit_poly["x3"] = "[3]*x**3+[2]*x**2+[1]*x+[0]";
  Fit_poly["x4"] = "[4]*x**4+[3]*x**3+[2]*x**2+[1]*x+[0]";
  Fit_poly["x2_y2"] =  "[8]*x**2*y**2+[7]*x**2*y+[6]*x**2+[5]*x*y**2+[4]*x*y+[3]*x+[2]*y**2+[1]*y+[0]";
  Fit_poly["x2_y3"] =  "[11]*x**2*y**3+[10]*x**2*y**2+[9]*x**2*y+[8]*x**2+[7]*x**2*y**3+[6]*x*y**2+[5]*x*y+[4]*x+[3]*y**3+[2]*y**2+[1]*y+[0]";
  Fit_poly["x2_y4"] =  "[14]*x**2*y**4+[13]*x**2*y**3+[12]*x**2*y**2+[11]*x**2*y+[10]*x**2+[9]*x*y**4+[8]*x*y**3+[7]*x*y**2+[6]*x*y+[5]*x+[4]*y**4+[3]*y**3+[2]*y**2+[1]*y+[0]";                                          

  Fit_poly["x3_y2"] =  "[11]*y**2*x**3+[10]*y**2*x**2+[9]*y**2*x+[8]*y**2+[7]*y**2*x**3+[6]*y*x**2+[5]*y*x+[4]*y+[3]*x**3+[2]*x**2+[1]*x+[0]";

  Fit_poly["x4_y3"] =  "[19]*x**4*y**3+[18]*x**4*y**2+[17]*x**4*y+[16]*x**4+[15]*x**3*y**3+[14]*x**3*y**2+[13]*x**3*y+[12]*x**3+[11]*x**2*y**3+[10]*x**2*y**2+[9]*x**2*y+[8]*x**2+[7]*x*y**3+[6]*x*y**2+[5]*x*y+[4]*x+[3]*y**3+[2]*y**2+[1]*y+[0]";
  Fit_poly["x4_y2"] =  "[14]*y**2*x**4+[13]*y**2*x**3+[12]*y**2*x**2+[11]*y**2*x+[10]*y**2+[9]*y*x**4+[8]*y*x**3+[7]*y*x**2+[6]*y*x+[5]*y+[4]*x**4+[3]*x**3+[2]*x**2+[1]*x+[0]";


  Fit_poly["x2_y3_z2"] = "[35]*x**2*y**3*z**2+[34]*x**2*y**3*z+[33]*x**2*y**3+[32]*x**2*y**2*z**2+[31]*x**2*y**2*z+[30]*x**2*y**2+[29]*x**2*y*z**2+[28]*x**2*y*z+[27]*x**2*y*+[26]*x**2*z**2+[25]*x**2*z+[24]*x**2+[23]*x*y**3*z**2+[22]*x*y**3*z+[21]*x*y**3+[20]*x*y**2*z**2+[19]*x*y**2*z+[18]*x*y**2+[17]*x*y*z**2+[16]*x*y*z+[15]*x*y+[14]*x*z**2+[13]*x*z+[12]*x+[11]*y**3*z**2+[10]*y**3*z+[9]*y**3+[8]*y**2*z**2+[7]*y**2*z+[6]*y**2+[5]*y*z**2+[4]*y*z+[3]*y+[2]*z**2+[1]*z+[0]";

  Fit_poly["x2_y2_z2"] = "[26]*x**2*y**2*z**2+[25]*x**2*y**2*z+[24]*x**2*y**2+[23]*x**2*y*z**2+[22]*x**2*y*z+[21]*x**2*y+[20]*x**2*z**2+[19]*x**2*z+[18]*x**2+[17]*x*y**2*z**2+[16]*x*y**2*z+[15]*x*y**2+[14]*x*y*z**2+[13]*x*y*z+[12]*x*y+[11]*x*z**2+[10]*x*z+[9]*x+[8]*y**2*z**2+[7]*y**2*z+[6]*y**2+[5]*y*z**2+[4]*y*z+[3]*y+[2]*z**2+[1]*z+[0]";

  // Dictionary of couplings to polynomials

  std::unordered_map<std::string, std::string> poly;
  // 1D scans
  poly["chhh"] = "x2";
  poly["ctth"] = "x4";
  poly["cggh"] = "x3";
  poly["cgghh"] = "x2";
  poly["ctthh"] = "x2";

  // 2D scans
  poly["chhh_ctth"] = "x2_y4";
  poly["chhh_cggh"] = "x2_y3";
  poly["chhh_cgghh"] = "x2_y2";
  poly["chhh_ctthh"] = "x2_y2";
  poly["ctth_ctthh"] =  "x4_y2";
  poly["ctth_cgghh"] =  "x4_y2";
  poly["ctth_cggh"] =  "x4_y3";
  poly["cggh_ctthh"] =  "x3_y2";
  poly["cggh_cgghh"] =  "x3_y2";
  poly["ctthh_cgghh"] =  "x3_y2";
 
  //3D scans
  poly["cgghh_cggh_ctthh"] = "x2_y3_z2";
  poly["chhh_ctthh_cgghh"] = "x2_y2_z2";

  std::unordered_map<std::string, std::string> name;
  name["chhh"] = "c_{hhh}";
  name["ctth"] = "c_{tth}";
  name["cggh"] = "c_{ggh}";
  name["cgghh"] = "c_{gghh}";
  name["ctthh"] = "c_{tthh}";

  std::unordered_map<std::string,std::vector<float>> range;
  range["chhh"] = {-4.0,10.0};
  range["ctth"] = {-1.0,1.5};
  range["cggh"] = {-6.0,7.0};
  range["cgghh"] = {-2.0,2.0};
  range["ctthh"] = {-2.0,2.0};
  
  

  // Starting

  std::map <std::string,std::map<std::string, std::string>> JsonMap;

  std::string json_string = "{ ";

  TFile *f = TFile::Open(filename, "READ");  

  std::map<std::pair< std::string,std::string>, TString> ParamF;

  for (std::vector<std::string>::iterator it_c= Scans.begin(); it_c!=Scans.end(); ++it_c)
    {
      std::string coupling = *it_c;

      if (coupling != Scans.at(0)) json_string+= " } ";
      json_string+=" "+coupling+" : { ";

      
      for (std::vector<std::string>::iterator it_r=Regions.begin(); it_r!=Regions.end(); ++it_r)
	{
	  std::string region = *it_r;
	  if (region != Regions.at(0)) {
	    json_string+=", ";
	  } else {
	    std::cout << " \n" << std::endl;
	  }
	  
	  json_string+= region+" : ";
	  
	  std::cout << " ### " << coupling << " " << region << " ### " << std::endl;

	  TString result;

          if (coupling.find("_") == std::string::npos) {
	    //std::cout << "Fitting a 1D function " << std::endl;
	    if (ModifyRange){
	      result = Fit1D(f, coupling, region, Fit_poly, poly, name, range[coupling], ParamF);
	    } else {
	      std::vector <float> def_range = {-10.0,10.0};
              result = Fit1D(f, coupling, region, Fit_poly, poly, name, def_range, ParamF);	      
	    }
	  } else {
	    //std::cout << "Fitting a 2D function " << std::endl;
	    result = Fit2D(f, coupling, region, Fit_poly, poly, name, range);
	  }
	    	 
	  json_string+=result;
	  
	  JsonMap[coupling][region] = result;
	}

    }
  json_string+=" }}";

  std::cout << json_string << std::endl;
  json j = JsonMap;
  std::ofstream json_file;
  json_file.open("HEFT_ParametrisedYields.json");
  json_file << std::setw(4) << j;
  
  return 0;
}
  
