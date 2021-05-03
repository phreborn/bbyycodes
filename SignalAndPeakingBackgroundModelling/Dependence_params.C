//TO REMOVE THE SINGLE HIGGS SINCE NOT IN PARAM

// root -b Dependence_params.C+
//===================================================================================================================================================
//===================================================================================================================================================
//Choice of finalDV

string string_chosen_finalDV="m_bb";
string string_latex_chosen_finalDV;

//"m_yy"
//"m_bb"
//"m_yybb_tilde"

//===================================================================================================================================================
vector<string> vec_string_latex_finalDV;
vector<string> vec_string_latex_root_finalDV;

//===================================
#include <string.h>

#include "ClassesFunctionalForms/RooTwoSidedCBShape.h"
#include "ClassesFunctionalForms/ExpGausExpPDF.h"

#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string.hpp>

#include <iostream>
#include <limits>
#include <math.h> //for ceil

#include <RooAbsPdf.h>
#include <RooAddPdf.h>
#include <RooArgSet.h>
#include <RooBernstein.h>
#include <RooBreitWigner.h>
#include <RooBukinPdf.h>
#include <RooCBShape.h>
#include <RooChebychev.h>
#include <RooExponential.h>
#include <RooFitResult.h>
#include <RooGamma.h>
#include <RooGaussian.h>
#include <RooGenericPdf.h>
#include <RooHist.h>
#include <RooLandau.h>
#include <RooNovosibirsk.h>
#include <RooPlot.h>
#include <RooProduct.h>
#include <RooProdPdf.h>
#include <RooRealVar.h>
#include <RooVoigtian.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TF1.h>
#include <TFile.h>
#include <TGraphErrors.h>
#include <TH1F.h>
#include <TH1D.h>
#include <TH2F.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TLine.h>
#include <TMarker.h>
#include <TString.h>
#include <TStyle.h>
#include <TSystem.h>

#include <vector>

#include <fstream>

using namespace RooFit;
using namespace std;

class result_current_process
{
public:
  double characteristic_sample;
  string string_process;
  RooAbsPdf *pdf;

  RooArgList arglist_parameters;
};

vector<result_current_process> vec_results_f_process;

TCanvas *canvas_parameter_f_process;


//prototypes
double ReturnCharacteristicResonance(string string_process);
void Draw_observable_f_mX(string string_category,vector<result_current_process> vec_results_f_process);

//keep index category, in order to be transparent for the exportation to HGam coupling suffixes
int Signal_given_category(int index_category,string string_process,string string_finalDV);

RooAbsPdf *TheReturnPdfSignal(string string_functional_form,string string_finalDV,string string_process,string string_category);

//RooArgSet is the best choice
RooArgSet argset_finalDV_noWeight; //argset of finalDVs

//--------------
//final luminosity Moriond 2021 : dictated by the framework

//       20170619 : GRL v89 :  3 219.56 pb-1
//       20180129 : GRLv89 : 32 988.1 pb-1
//       36 207.66 pb-1
//       20180619 : GRLv99 : 44 307.4 pb-1
//       20190318 : GRLv102 : 58 450.1 pb-1
//       138 965.16 pb-1

float lumi_mc16a=36.20766;
float lumi_mc16d=44.3074;
float lumi_mc16e=58.4501;
/*
float lumi_mc16a=36.20904;
float lumi_mc16d=44.3857;
float lumi_mc16e=58.4501;
*/
//references:
// /cvmfs/atlas.cern.ch/repo/sw/database/GroupData/GoodRunsLists/data18_13TeV/20190708/
// Luminosity:   3219.44 pb-1
// Luminosity:   32989.6 pb-1
// Luminosity:   44385.7 pb-1
// Luminosity:   58450.1 pb-1

float lumi=0;

vector<string> vec_string_category;

bool do_mc16a=1;
bool do_mc16d=1;
bool do_mc16e=1;
//do it only incremently: example: not 0 1 1

//from /cvmfs/atlas.cern.ch/repo/sw/database/GroupData/GoodRunsLists/
//notes.txt

FILE *fp_results;
FILE *fp_results_sorted;

RooRealVar *roorealvar_m_yy;
RooRealVar *roorealvar_m_bb;
RooRealVar *roorealvar_m_yybb_tilde;

vector<string> vec_string_process;

//-----
string string_non_resonant_resonant;

int Dependence_params()
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0000000);

  if (string_chosen_finalDV=="m_yy")
    string_latex_chosen_finalDV="m_{#gamma#gamma}";
  else if (string_chosen_finalDV=="m_bb")
    string_latex_chosen_finalDV="m_{bb}";
  else if (string_chosen_finalDV=="m_yybb_tilde")
    string_latex_chosen_finalDV="m_{#gamma#gammabb tilde}";
  
  gROOT->ProcessLine(".L ClassesFunctionalForms/RooTwoSidedCBShape.cxx+");
  
  cout << "compile ExpGausExpPDF" << endl;
  gROOT->ProcessLine(".L ClassesFunctionalForms/ExpGausExpPDF.cxx+");
  
  gSystem->Load("ClassesFunctionalForms/RooTwoSidedCBShape_cxx.so");
  gSystem->Load("ClassesFunctionalForms/ExpGausExpPDF_cxx.so");

  if (do_mc16a)
    lumi+=lumi_mc16a;
  if (do_mc16d)
    lumi+=lumi_mc16d;
  if (do_mc16e)
    lumi+=lumi_mc16e;
  
  vec_string_category.push_back("baseline");

  int n_mX=0;

  //non-resonant and resonant
  //for (unsigned int index_non_resonant_resonant=0;index_non_resonant_resonant<2;index_non_resonant_resonant++) {

  //non-resonant only
  //for (unsigned int index_non_resonant_resonant=0;index_non_resonant_resonant<1;index_non_resonant_resonant++) {
    
  //resonant only:
  for (unsigned int index_non_resonant_resonant=1;index_non_resonant_resonant<2;index_non_resonant_resonant++) {
    
    if (index_non_resonant_resonant==0)
      string_non_resonant_resonant="non_resonant";
    else if (index_non_resonant_resonant==1)
      string_non_resonant_resonant="resonant";
    
    //TO DO : TO DO PER CATEGORY : inside a process
    
    vec_string_process.clear();
    
    if (string_non_resonant_resonant=="non_resonant")  {
      //----------------
      vec_string_process.push_back("gg_HH_kappa_lambda_minus_10");
      vec_string_process.push_back("gg_HH_kappa_lambda_minus_6");
      vec_string_process.push_back("gg_HH_kappa_lambda_minus_4");
      vec_string_process.push_back("gg_HH_kappa_lambda_minus_2");
      vec_string_process.push_back("gg_HH_kappa_lambda_0");
      vec_string_process.push_back("gg_HH");
      vec_string_process.push_back("gg_HH_kappa_lambda_plus_2");
      vec_string_process.push_back("gg_HH_kappa_lambda_plus_4");
      vec_string_process.push_back("gg_HH_kappa_lambda_plus_6");
      vec_string_process.push_back("gg_HH_kappa_lambda_plus_10");
    }
    else if (string_non_resonant_resonant=="resonant")  {
      //----------------
      vec_string_process.push_back("gg_X251");

      vec_string_process.push_back("gg_X260");
      vec_string_process.push_back("gg_X280");
      
      vec_string_process.push_back("gg_X300");
      
      vec_string_process.push_back("gg_X325");
      vec_string_process.push_back("gg_X350");
      vec_string_process.push_back("gg_X400");
      vec_string_process.push_back("gg_X450");
      vec_string_process.push_back("gg_X500");
      vec_string_process.push_back("gg_X550");
      vec_string_process.push_back("gg_X600");
      vec_string_process.push_back("gg_X700");
      vec_string_process.push_back("gg_X800");
      vec_string_process.push_back("gg_X900");
      vec_string_process.push_back("gg_X1000");
      vec_string_process.push_back("gg_X2000");
      
      vec_string_process.push_back("gg_X3000");
    }
    
    n_mX=vec_string_process.size();

    for (unsigned int index_categ=0;index_categ<vec_string_category.size();index_categ++) {
      string string_category=vec_string_category[index_categ];
      
      for (int index_mX=0;index_mX<n_mX;index_mX++) {
	cout << "index_mX=" << index_mX << endl;
	
	Signal_given_category(index_categ,vec_string_process[index_mX],string_chosen_finalDV);

	if (string_chosen_finalDV=="m_yy")
	  delete roorealvar_m_yy;
	
	if (string_chosen_finalDV=="m_bb") {	
	  delete roorealvar_m_bb;
	}
	
	if (string_chosen_finalDV=="m_yybb_tilde") {
	  delete roorealvar_m_yybb_tilde;
	}
	
	argset_finalDV_noWeight.removeAll();

      } //end loop on processes      

      cout << "call draw observable" << endl;
      Draw_observable_f_mX(string_category,vec_results_f_process);
  
      vec_results_f_process.clear();
      
    } //end loop on categories

  cout << "loop on non resonant resonant" << endl;
  } //end loop on non-resonant/resonant

  vec_string_process.clear();  

  //  vec_string_finalDV.clear();
  vec_string_latex_finalDV.clear();
  vec_string_latex_root_finalDV.clear();
  
  cout << "end program" << endl;
  
  return 0;
  }

//to make a class in order to store the parameters ?
//===========================================================================================================
int Signal_given_category(int index_category,string string_process,string string_finalDV)
{
  string string_category=vec_string_category[index_category];
  
  lumi=0;
  
  if (do_mc16a)
    lumi+=lumi_mc16a;
  if (do_mc16d)
    lumi+=lumi_mc16d;
  if (do_mc16e)
    lumi+=lumi_mc16e;

  //---------------------------------------------
  for (int i=0;i<10;i++)
    cout << "=======================================================================================" << endl;
  
  cout << "Treat Signal_given_category for categ=" << string_category << ", string_process=" << string_process << endl;

  //-----------------------------------------------------------------------------
  if (string_finalDV=="m_yy") {
    roorealvar_m_yy=new RooRealVar("m_yy","m_{#gamma#gamma}",125,114,136,"GeV");
    //    roorealvar_m_yy->setBins((roorealvar_m_yy->getMax()-roorealvar_m_yy->getMin())/1.); //m_yy: bin width=1 GeV
  }

  if (string_finalDV=="m_bb")
    roorealvar_m_bb=new RooRealVar("m_bb","m_{bb}",125,"GeV"); //remark : range need at least 500 for ttH, with fraction 0.95
    
  if (string_finalDV=="m_yybb_tilde") {
    roorealvar_m_yybb_tilde=new RooRealVar("m_yybb_tilde","m_{#gamma#gammabb tilde}",125,"GeV");
  }

  RooArgSet argset_finalDV;

  cout << "after creation of argset" << endl;
  cout << "argset_finalDV=" << argset_finalDV.size() << endl;
  cout << "argset_finalDV_noWeight=" << argset_finalDV_noWeight.size() << endl;

  if (string_finalDV=="m_yy") {
    argset_finalDV_noWeight.add(*roorealvar_m_yy);
  }

  if (string_finalDV=="m_bb") {
    argset_finalDV_noWeight.add(*roorealvar_m_bb);
  }
  
  if (string_finalDV=="m_yybb_tilde") {
    argset_finalDV_noWeight.add(*roorealvar_m_yybb_tilde);
  }

  //-----------------------------
  //keep it there : not above : after the change of range of m_yy, else problems for debugging

  //3) prepare Pdf

  //functional forms

  string string_functional_form;
  
  if (string_non_resonant_resonant=="non_resonant" && string_finalDV=="m_yy")
    string_functional_form="DoubleCrystalBall";
  else if (string_non_resonant_resonant=="non_resonant" && string_finalDV=="m_bb")
    string_functional_form="DoubleCrystalBall";
  else if (string_non_resonant_resonant=="resonant" && string_finalDV=="m_yy")
    string_functional_form="DoubleCrystalBall";
  else if (string_non_resonant_resonant=="resonant" && string_finalDV=="m_bb")
    //string_functional_form="Bukin";
    string_functional_form="DoubleCrystalBall";

  //============================================================================================================================
  result_current_process new_result;
  
  new_result.string_process=string_process;

  new_result.pdf=TheReturnPdfSignal(string_functional_form,string_finalDV,string_process,string_category);

  cout << "parameters" << endl;
  ((RooArgSet *)new_result.pdf->getParameters(argset_finalDV_noWeight))->Print("v");
  
  RooArgSet *argset_shape=(RooArgSet *)((RooArgSet *)new_result.pdf->getParameters(argset_finalDV_noWeight))->selectByAttrib("Constant",kTRUE);

  if (string_non_resonant_resonant=="non_resonant") {
    argset_shape->readFromFile((string("inputs_dependence_params/")+string_finalDV+"/"+"datacard_non_resonant"+"_"+string_category+".txt").c_str());
  }
  else if (string_non_resonant_resonant=="resonant") {
    argset_shape->readFromFile((string("inputs_dependence_params/")+string_finalDV+"/"+"datacard_resonant"+"_"+string_category+".txt").c_str());
  }

  argset_shape->Print("v");

  new_result.arglist_parameters.add(*argset_shape);
  
  new_result.arglist_parameters.Print();

  //to rename
  new_result.characteristic_sample=ReturnCharacteristicResonance(string_process);
 
  vec_results_f_process.push_back(new_result);
  //==========================================================================================================================
  //---------------------------------------------
  //extract mX
  
  int mX=0;
  
  string string_delimiter="_X";
  
  //  cout << "string_process=" << string_process << endl;
  
  //  size_t pos=string_process.find(string_delimiter,0);
  //  cout << "pos=" << pos << endl;
  
  size_t pos=string_process.find(string_delimiter,0);
  
  if (pos==string::npos) {
    //mX=125;
    
  }
  else {
    string string_mX=string_process.substr(pos+2,string_process.size()-(pos+2));
    
    cout << "string_mX=" << string_mX << endl;
    
    mX=atoi(string_mX.c_str());
  }

  
  cout << "mX=" << mX << endl;

  return 0;
}
//===========================================================================================================
void Draw_observable_f_mX(string string_category,vector<result_current_process> vec_results_f_process)
{
  string string_finalDV=string_chosen_finalDV;

  cout << "Draw_observable_f_mX phase 1" << endl;
  
  //to rename in string_latex_parameter;

  string string_latex_parameter;

  //assume that all have the same parameterisation, else there is not interest in a parameterisation

  cout << "vec_results_f_process[0].arglist_parameters.size()=" << vec_results_f_process[0].arglist_parameters.size() << endl;

  

  RooRealVar *roorealvar;
  
  for (unsigned int index_parameter=0;index_parameter<vec_results_f_process[0].arglist_parameters.size();index_parameter++) {

    cout << "index_parameter=" << index_parameter << endl;

    roorealvar=(RooRealVar *)vec_results_f_process[0].arglist_parameters.at(index_parameter);
    string_latex_parameter=roorealvar->GetTitle();

    string string_parameter=((RooRealVar *)vec_results_f_process[0].arglist_parameters.at(index_parameter))->GetName();

    //----------------------------------------------------------------------
    //TCanvas *canvas_parameter_f_process=new TCanvas("canvas_parameter_f_process","canvas_parameter_f_process",800,600);
    //TCanvas *canvas_parameter_f_process=new TCanvas((string("canvas_parameter_f_process_")+string_parameter).c_str(),(string("canvas_parameter_f_process_")+string_parameter).c_str(),800,600);
    canvas_parameter_f_process=new TCanvas((string("canvas_parameter_f_process_")+string_parameter).c_str(),(string("canvas_parameter_f_process_")+string_parameter).c_str(),800,600);
    canvas_parameter_f_process->SetLeftMargin(0.13);
    canvas_parameter_f_process->SetRightMargin(0.03);
    canvas_parameter_f_process->SetTopMargin(0.05);
    
    unsigned int n_processes=vec_results_f_process.size();
    
    vector<double> vec_parameter_f_process;
    vector<double> vec_err_parameter_f_process;

    float min_graph_observable_f_process=std::numeric_limits<float>::max();
    float max_graph_observable_f_process=-std::numeric_limits<float>::max();
    
    for (unsigned int index_process=0;index_process<vec_string_process.size();index_process++) {
      
      roorealvar=(RooRealVar *)vec_results_f_process[index_process].arglist_parameters.at(index_parameter);
      
      cout << "index_process=" << index_process << endl;

      cout << "parameter=" << string_latex_parameter << endl;
      
      cout << "roorealvar->getVal()=" << roorealvar->getVal() << endl;
      vec_parameter_f_process.push_back(roorealvar->getVal());
      vec_err_parameter_f_process.push_back(roorealvar->getError());
      
      //search for max and min, for the range
      
      if (vec_parameter_f_process[index_process]<min_graph_observable_f_process)
	min_graph_observable_f_process=vec_parameter_f_process[index_process];
      if (vec_parameter_f_process[index_process]>max_graph_observable_f_process)
	max_graph_observable_f_process=vec_parameter_f_process[index_process];
    } //end loop on processes
    
    cout << "max_graph_observable_f_process=" << max_graph_observable_f_process << endl;
    cout << "min_graph_observable_f_process=" << min_graph_observable_f_process << endl;
    
    double coefficient=1.;

    if (string_finalDV=="m_yy" && (string_parameter.find("muCB")!=string::npos || string_parameter.find("muBukin")!=string::npos))
      coefficient=1.005;
    else
      coefficient=1.05;

    cout << "string_finalDV=" << string_finalDV << ", string_parameter=" << string_parameter << ", coefficient=" << coefficient << endl;
    
    if (min_graph_observable_f_process>0)
      min_graph_observable_f_process/=coefficient;
    else if (min_graph_observable_f_process==0)
      min_graph_observable_f_process-=0.05;
    else
      //min_graph_observable_f_process*=1.05;
      min_graph_observable_f_process*=coefficient;
    
    if (max_graph_observable_f_process>0)
      max_graph_observable_f_process*=coefficient;
    else if (max_graph_observable_f_process==0)
      max_graph_observable_f_process+=0.05;
    else
      max_graph_observable_f_process/=coefficient;
    
    vector<double> vec_process;
    vector<double> vec_err_process;
    for (unsigned int index_process=0;index_process<vec_string_process.size();index_process++) {
      vec_process.push_back(vec_results_f_process[index_process].characteristic_sample);
      vec_err_process.push_back(0);
    }
    
    TGraphErrors *graph_observable_f_process=new TGraphErrors(n_processes,vec_process.data(),vec_parameter_f_process.data(),vec_err_process.data(),vec_err_parameter_f_process.data());
    
    graph_observable_f_process->SetMarkerStyle(20);
    graph_observable_f_process->SetMarkerColor(kBlack);
    graph_observable_f_process->SetMarkerSize(1.);
    graph_observable_f_process->SetLineColor(kBlack);
    
    TH1F *hist_frame=0;

    cout << "n_processes=" << n_processes << endl;

    if (string_non_resonant_resonant=="non_resonant") //kappa_lambda
      hist_frame=new TH1F("hist_frame","hist_frame",n_processes,vec_process[0]-2,vec_process[n_processes-1]+2); 
    else if (string_non_resonant_resonant=="resonant")
      hist_frame=new TH1F("hist_frame","hist_frame",n_processes,vec_process[0]-100,vec_process[n_processes-1]+100);
    
    hist_frame->SetMinimum(min_graph_observable_f_process);
    hist_frame->SetMaximum(max_graph_observable_f_process);

    
    //     if (string_non_resonant_resonant=="non_resonant") {
    //       for (unsigned int index_process=0;index_process<vec_string_process.size();index_process++) {
    // 	hist_frame->GetXaxis()->SetBinLabel(index_process+1,vec_string_process[index_process].c_str());
    //       }
    //     }


    hist_frame->Draw();

    if (string_non_resonant_resonant=="non_resonant")
      hist_frame->SetXTitle("#kappa_{#lambda}");
    else if (string_non_resonant_resonant=="resonant")
      hist_frame->SetXTitle("m_{X} [GeV]");
    
    hist_frame->SetYTitle(string_latex_parameter.c_str());
        
    //never choose "A" option for graph, since axis chosen with DrawFrame
        
    graph_observable_f_process->Draw("P");
    graph_observable_f_process->Draw("L");
    
    canvas_parameter_f_process->RedrawAxis();
    
    TLatex mylatex;
    mylatex.SetNDC();
    mylatex.SetTextAlign(3);
    
    mylatex.SetTextSize(0.05); //0.045 is std
    mylatex.SetTextFont(72);
    mylatex.DrawLatex(0.60,0.92,"ATLAS internal");
    
    mylatex.SetTextSize(0.05); //0.045 is std
    mylatex.SetTextFont(42); //put back the font
    
    mylatex.SetTextSize(0.03); //0.045 is std
    
    float position_y=0.85;
    
    float step_delta_y=0.04;
    
    char buffer_lumi[15];
    sprintf(buffer_lumi,"L=%4.1f fb^{-1}",lumi);
    mylatex.DrawLatex(0.60,position_y,buffer_lumi);
    
    position_y-=step_delta_y;
    
    mylatex.DrawLatex(0.60,position_y,string_latex_chosen_finalDV.c_str());

    position_y-=step_delta_y;
    
    //    mylatex.DrawLatex(0.16,position_y,string_category.c_str());
    mylatex.DrawLatex(0.60,position_y,string_category.c_str());

    position_y-=step_delta_y;

    
    string string_saveas_observable_f_process="figures/";
    string_saveas_observable_f_process+=string_chosen_finalDV;
    string_saveas_observable_f_process+="/";
    string_saveas_observable_f_process+=string_non_resonant_resonant;
    string_saveas_observable_f_process+="_";
    string_saveas_observable_f_process+="Overview_";
    string_saveas_observable_f_process+="finalDV_";

    string_saveas_observable_f_process+=string_finalDV;
    
    string_saveas_observable_f_process+="_";
    string_saveas_observable_f_process+=string_category.c_str();
    string_saveas_observable_f_process+="_";
    
    string_saveas_observable_f_process+=vec_results_f_process[0].arglist_parameters.at(index_parameter)->GetName();

    string_saveas_observable_f_process+="_f_process";
    string_saveas_observable_f_process+=".png";
    
    cout << "save " << string_saveas_observable_f_process << endl;

    canvas_parameter_f_process->SaveAs(string_saveas_observable_f_process.c_str());

    //    delete graph_observable_f_process;

    //    delete canvas_parameter_f_process;

    //    delete hist_frame;

    vec_parameter_f_process.clear();
  } //end loop on parameter
}
//===========================================================================================================
//===========================================================================================================
RooAbsPdf *TheReturnPdfSignal(string string_functional_form,string string_finalDV,string string_process,string string_category)
{
  RooRealVar *roorealvar_finalDV=0;
  
  if (string_finalDV=="m_yy")
    roorealvar_finalDV=roorealvar_m_yy;
  else if (string_finalDV=="m_bb")
    roorealvar_finalDV=roorealvar_m_bb;
  
  RooAbsPdf *pdf_signal=0;
  
  //initialize with 0
  //and parameters read from datacard  


  cout << "string_functional_form=" << string_functional_form << endl;
  cout << "string_finalDV=" << string_finalDV << endl;

  if (string_functional_form=="DoubleCrystalBall") {
    RooRealVar *roorealvar_muCB=new RooRealVar((string("muCB")+"_"+string_finalDV+"_"+string_process).c_str(),"#mu_{CB}",0);
    RooRealVar *roorealvar_sigmaCB=new RooRealVar((string("sigmaCB")+"_"+string_finalDV+"_"+string_process).c_str(),"#sigma_{CB}",0);
    RooRealVar *roorealvar_alphaCB_Low=new RooRealVar((string("alphaCB_Low")+"_"+string_finalDV+"_"+string_process).c_str(),"#alpha_{CB}^{Low}",0);
    RooRealVar *roorealvar_nCB_Low=new RooRealVar((string("nCB_Low")+"_"+string_finalDV+"_"+string_process).c_str(),"n_{CB}^{Low}",0);
    RooRealVar *roorealvar_alphaCB_High=new RooRealVar((string("alphaCB_High")+"_"+string_finalDV+"_"+string_process).c_str(),"#alpha_{CB}^{High}",0);
    RooRealVar *roorealvar_nCB_High=new RooRealVar((string("nCB_High")+"_"+string_finalDV+"_"+string_process).c_str(),"n_{CB}^{High}",0);
    pdf_signal=new RooTwoSidedCBShape(
				      (string("Pdf_Signal")+"_"+string_finalDV+"_"+string_category).c_str(),
				      (string("Pdf_")+string_process+"_DoubleCrystalBall"+"_"+string_finalDV).c_str(),
				      *roorealvar_finalDV,*roorealvar_muCB,*roorealvar_sigmaCB,*roorealvar_alphaCB_Low,*roorealvar_nCB_Low,*roorealvar_alphaCB_High,*roorealvar_nCB_High);
  }
  else if (string_functional_form=="Bukin") {
    RooRealVar *roorealvar_muBukin=new RooRealVar((string("muBukin")+"_"+string_finalDV+"_"+string_process).c_str(),"#mu_{Bukin}",0);
    RooRealVar *roorealvar_sigmaBukin=new RooRealVar((string("sigmaBukin")+"_"+string_finalDV+"_"+string_process).c_str(),"#sigma_{Bukin}",0);
    RooRealVar *roorealvar_xiBukin=new RooRealVar((string("xiBukin")+"_"+string_finalDV+"_"+string_process).c_str(),"#xi_{Bukin}",0);
    RooRealVar *roorealvar_rho1Bukin=new RooRealVar((string("rho1Bukin")+"_"+string_finalDV+"_"+string_process).c_str(),"#rho_{1 Bukin}",0);
    RooRealVar *roorealvar_rho2Bukin=new RooRealVar((string("rho2Bukin")+"_"+string_finalDV+"_"+string_process).c_str(),"#rho_{2 Bukin}",0);
    
    pdf_signal=new RooBukinPdf(
			       (string("Pdf_Signal")+"_"+string_finalDV+"_"+string_category).c_str(),
			       (string("Pdf_")+string_process+"_Bukin"+"_"+string_finalDV).c_str(),
			       *roorealvar_finalDV,*roorealvar_muBukin,*roorealvar_sigmaBukin,*roorealvar_xiBukin,*roorealvar_rho1Bukin,*roorealvar_rho2Bukin);
  }

  cout << "pdf_signal=" << pdf_signal << endl;
  
  return pdf_signal;
}
//===========================================================================================================
double ReturnCharacteristicResonance(string string_process)
{
  double characteristic_resonance=-1;
  
  if (string_process=="gg_HH_kappa_lambda_minus_10")
    characteristic_resonance=-10;
  else if (string_process=="gg_HH_kappa_lambda_minus_6")
    characteristic_resonance=-6;
  else if (string_process=="gg_HH_kappa_lambda_minus_4")
    characteristic_resonance=-4;
  else if (string_process=="gg_HH_kappa_lambda_minus_2")
    characteristic_resonance=-2;
  else if (string_process=="gg_HH_kappa_lambda_0")
    characteristic_resonance=0;
  else if (string_process=="gg_HH")
    characteristic_resonance=1;
  else if (string_process=="gg_HH_kappa_lambda_plus_2")
    characteristic_resonance=2;
  else if (string_process=="gg_HH_kappa_lambda_plus_4")
    characteristic_resonance=4;
  else if (string_process=="gg_HH_kappa_lambda_plus_6")
    characteristic_resonance=6;
  else if (string_process=="gg_HH_kappa_lambda_plus_10")
    characteristic_resonance=10;

  else if (string_process=="gg_X251")
    characteristic_resonance=251;
  else if (string_process=="gg_X260")
    characteristic_resonance=260;
  else if (string_process=="gg_X280")
    characteristic_resonance=280;
  else if (string_process=="gg_X300")
    characteristic_resonance=300;
  else if (string_process=="gg_X325")
    characteristic_resonance=325;
  else if (string_process=="gg_X350")
    characteristic_resonance=350;
  else if (string_process=="gg_X400")
    characteristic_resonance=400;
  else if (string_process=="gg_X450")
    characteristic_resonance=450;
  else if (string_process=="gg_X500")
    characteristic_resonance=500;
  else if (string_process=="gg_X550")
    characteristic_resonance=550;
  else if (string_process=="gg_X600")
    characteristic_resonance=600;
  else if (string_process=="gg_X700")
    characteristic_resonance=700;
  else if (string_process=="gg_X800")
    characteristic_resonance=800;
  else if (string_process=="gg_X900")
    characteristic_resonance=900;
  else if (string_process=="gg_X1000")
    characteristic_resonance=1000;
  else if (string_process=="gg_X2000")
    characteristic_resonance=2000;
  else if (string_process=="gg_X3000")
    characteristic_resonance=3000;
  
  return characteristic_resonance;
}
//===========================================================================================================
