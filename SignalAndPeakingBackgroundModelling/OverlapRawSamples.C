//careful of flag

string string_version_MxAOD="h025"; //h025/h026

//TO DO : at around line 408 : to loop on category *inside* the process : switch order

//to put suffix for datacard
//
////need to be launched in compilation mode
// root -b -q OverlapRawSamples.C+

//===================================================================================================================================================
//Choice of finalDV

vector<string> vec_string_finalDV={"m_yy"};
//vector<string> vec_string_finalDV={"m_bb"}; //do not put Single Higgs for m_bb, because is is made of several shapes, else fit will have trouble
//vector<string> vec_string_finalDV={"m_yy","m_bb"};

//vector<string> vec_string_finalDV={"m_yybb_tilde"};
//===================================================================================================================================================
vector<string> vec_string_latex_finalDV;
vector<string> vec_string_latex_root_finalDV;

vector<string> vec_string_signal_model;
//===================================
#include <string.h>


#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string.hpp>

#include <RooArgSet.h>
#include <RooHist.h>
#include <RooPlot.h>
#include <RooProduct.h>
#include <RooProdPdf.h>

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

#define NOT_SORTED 0
#define SORTED 1

using namespace RooFit;
using namespace std;

//prototypes
TChain *ReturnSampleSignal(string string_process,string string_category);
void set_plot_style();

//int Signal_given_category(int string_category,string string_process,result_f_process &current_results_f_process,string string_finalDV);
int Signal_given_category(int string_category,string string_process,string string_finalDV);

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

bool do_consider_public_test=0;
bool do_consider_private_test=0; //official decision 05/August/2020 : take everything : only for yield (never for shape)

float lumi=0;

vector<string> vec_string_category;

bool do_fit_shape=1;

//f_functional_form

//TO DO : RENAME
vector<string> vec_functional_form_signal;

bool do_mc16a=1;
bool do_mc16d=1;
bool do_mc16e=1;
//do it only incremently: example: not 0 1 1

vector<string> vec_string_process;
vector<TH1D *> vec_hist_process;


TChain *chain_ggH=0;
TChain *chain_VBF=0;
TChain *chain_qqZH=0;
TChain *chain_ggZH=0;
TChain *chain_ttH=0;
TChain *chain_tHjb=0;

TChain *chain_gg_HH=0;
TChain *chain_vbf_HH=0;
TChain *chain_gg_vbf_HH=0;

string string_non_resonant_resonant="resonant"; //non_resonant, resonant

#include "tool_ReturnSample.C"

int OverlapRawSamples()
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0000000);

  gStyle->SetPalette(1);
  set_plot_style();

  for (unsigned int index_finalDV=0;index_finalDV<vec_string_finalDV.size();index_finalDV++) {
    if (vec_string_finalDV[index_finalDV]=="m_yy") {
      vec_string_latex_finalDV.push_back("$m_{\\gamma\\gamma}$");
      vec_string_latex_root_finalDV.push_back("m_{#gamma#gamma}");
    }
    else if (vec_string_finalDV[index_finalDV]=="m_bb") {
      vec_string_latex_finalDV.push_back("$m_{bb}$");
      vec_string_latex_root_finalDV.push_back("m_{bb}");
    }
    else if (vec_string_finalDV[index_finalDV]=="m_yybb_tilde") {
      vec_string_latex_finalDV.push_back("$m_{\\gamma\\gamma bb\\ tilde}$");
      vec_string_latex_root_finalDV.push_back("m_{#gamma#gammabb tilde}");
    }
    else {
      cout << "problem" << endl;
      exit(1);
    }

  } //end constructing the model

  for (unsigned int index_vec_string_finalDV=0;index_vec_string_finalDV<vec_string_finalDV.size();index_vec_string_finalDV++) {
    cout << vec_string_finalDV[index_vec_string_finalDV] << endl;
    //    cout << vec_string_latex_finalDV[index_vec_string_finalDV] << endl;
  }

  if (do_mc16a)
    lumi+=lumi_mc16a;
  if (do_mc16d)
    lumi+=lumi_mc16d;
  if (do_mc16e)
    lumi+=lumi_mc16e;
  
  //  vec_string_category.push_back("baseline");

  //vec_string_category.push_back("XGBoost_btag77_withTop_BCal_tightScore_HMass");
  
  //  vec_string_category.push_back("XGBoost_btag77_withTop_BCal_looseScore_HMass");
  
  //  vec_string_category.push_back("XGBoost_btag77_withTop_BCal_tightScore_LMass");
  
  //  vec_string_category.push_back("XGBoost_btag77_withTop_BCal_looseScore_LMass");
  



  //  vec_string_category.push_back("VBF_btag77_withTop_BCal");
  //------------------------------------------
  //resonant category
  if (string_non_resonant_resonant=="resonant") {
    //vec_string_category.push_back("Resonant_mX260");
    //    vec_string_category.push_back("Resonant_mX500");
    vec_string_category.push_back("Resonant_mX1000");
  }

  int n_mX=0;

  //TO DO : TO DO PER CATEGORY : inside a process
  
  //    result_f_process current_results_f_process;
  
  vec_string_process.clear();
  
  if (string_non_resonant_resonant=="non_resonant")  {
    //----------------
    /*
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
    */
    
    /*
      vec_string_process.push_back("gg_HH_NLO");
      vec_string_process.push_back("gg_HH_NLO_kappa_lambda_plus_10");
    */
    
    vec_string_process.push_back("gg_HH_NLO");
    vec_string_process.push_back("SingleHiggs");
    
    /*
      
      vec_string_process.push_back("gg_HH_NLO_train_events");
      vec_string_process.push_back("gg_HH_NLO_public_test_events");
    */
  }
  else if (string_non_resonant_resonant=="resonant")  {
    //----------------
    /*
      vec_string_process.push_back("gg_X251");
    */
    
    //    vec_string_process.push_back("gg_X260");
    //    vec_string_process.push_back("gg_X500");
    vec_string_process.push_back("gg_X1000");
    vec_string_process.push_back("gg_vbf_HH");
    vec_string_process.push_back("SingleHiggs");
    
    /*      
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
      */
    }
    
    n_mX=vec_string_process.size();
    
    for (unsigned int index_finalDV=0;index_finalDV<vec_string_finalDV.size();index_finalDV++) {

      string string_finalDV=vec_string_finalDV[index_finalDV];
      
      for (unsigned int index_categ=0;index_categ<vec_string_category.size();index_categ++) {
	string string_category=vec_string_category[index_categ];
	
	for (int index_mX=0;index_mX<n_mX;index_mX++) {
	  cout << "index_mX=" << index_mX << endl;
	  
	  //	  Signal_given_category(index_categ,vec_string_process[index_mX],current_results_f_process,string_finalDV);
	  Signal_given_category(index_categ,vec_string_process[index_mX],string_finalDV);
	  
	  vec_string_signal_model.clear();
	} //end loop on processes      
	
	TCanvas *canvas=new TCanvas("canvas","canvas",800,600);
	canvas->SetLeftMargin(0.13);
	canvas->SetRightMargin(0.03);
	canvas->SetTopMargin(0.05);
	
	TH1F *hist_dummy;
	
	if (string_finalDV=="m_yy")
	  //hist_dummy=canvas->DrawFrame(105,1e-6,160,0.3);
	  //	  hist_dummy=canvas->DrawFrame(110,1e-6,140,0.25);
	  hist_dummy=canvas->DrawFrame(110,1e-6,140,0.35);
	else if (string_finalDV=="m_bb")
	  hist_dummy=canvas->DrawFrame(20,1e-6,220,0.15);

	hist_dummy->SetXTitle((vec_string_latex_root_finalDV[0]+" [GeV]").c_str());
	char buffer[50];
	sprintf(buffer,"normalised / %4.1f [GeV]",vec_hist_process[0]->GetBinWidth(1));
	hist_dummy->SetYTitle(buffer);
	
	//	TLegend *legend=new TLegend(0.65,0.40,0.98,0.70);
	TLegend *legend=new TLegend(0.66,0.38,0.97,0.71);
	legend->SetMargin(0.05);
	legend->SetTextSize(0.02);
	//	legend->SetBorderSize(2);
	legend->SetBorderSize(0);
	legend->SetLineColor(0);
	legend->SetLineWidth(0);
	legend->SetFillStyle(1001);
	legend->SetFillColor(kWhite);
	
	unsigned int nb_processes=vec_hist_process.size();
	for (unsigned int index_process=0;index_process<nb_processes;index_process++) {
	  vec_hist_process[index_process]->Draw("same");
	  
	  legend->AddEntry(vec_hist_process[index_process],vec_string_process[index_process].c_str(),"lp");
	}
	
	canvas->RedrawAxis();
	
	TLatex mylatex;
	mylatex.SetNDC();
	mylatex.SetTextAlign(3);
	
	mylatex.SetTextSize(0.05); //0.045 is std
	mylatex.SetTextFont(72);
	//    mylatex.DrawLatex(0.16,0.92,"ATLAS internal");
	mylatex.DrawLatex(0.60,0.92,"ATLAS internal");
	
	mylatex.SetTextSize(0.05); //0.045 is std
	mylatex.SetTextFont(42); //put back the font
	
	mylatex.SetTextSize(0.03); //0.045 is std
	
	float position_y=0.85;
	
	//    float step_delta_y=0.05;
	float step_delta_y=0.04;
	
	char buffer_lumi[15];
	sprintf(buffer_lumi,"L=%4.1f fb^{-1}",lumi);
	//    mylatex.DrawLatex(0.16,position_y,buffer_lumi);
	mylatex.DrawLatex(0.60,position_y,buffer_lumi);
	
	position_y-=step_delta_y;
	
	position_y-=step_delta_y;
	
	//    mylatex.DrawLatex(0.16,position_y,string_category.c_str());
	mylatex.SetTextSize(0.02); //0.045 is std
	mylatex.DrawLatex(0.60,position_y,(string_category+", "+string_non_resonant_resonant).c_str());
	
	position_y-=step_delta_y;
	
	legend->Draw();

	canvas->SaveAs((string("figures/overlap_")+string_category+".png").c_str());
      } //end loop on categories
    
    } //end loop on finalDV
      
  cout << "end program" << endl;
  
  return 0;
}

//to make a class in order to store the parameters ?
//===========================================================================================================
//int Signal_given_category(int index_category,string string_process,result_f_process &results_f_process,string string_finalDV)
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

  vec_functional_form_signal.clear();


  //----------------------------------------
  //vec_functional_form_signal.push_back("Modified_Landau");
  //not mature for non-resonant, vec_functional_form_signal.push_back("Modified_Gamma");

  //need to have done the ReturnWindow, in order to define the window !!

  TChain *chain_process=ReturnSampleSignal(string_process,string_category);
  
  cout << "chain_process=" << chain_process << endl;
  
  cout << "entries=" << chain_process->GetEntries() << endl;

  TH1D *hist;

  if (string_finalDV=="m_yy")
    hist=new TH1D((string("hist_")+string_finalDV+"_"+string_process).c_str(),
		  (string("hist_")+string_finalDV+"_"+string_process).c_str(),
		  55,105,160);
  else if (string_finalDV=="m_bb")
    hist=new TH1D((string("hist_")+string_finalDV+"_"+string_process).c_str(),
		  (string("hist_")+string_finalDV+"_"+string_process).c_str(),
		  40,20,220);

  int color;
  if (vec_hist_process.size()==0)
    color=kViolet;
  else if (vec_hist_process.size()==1)
    color=kBlue;
  else if (vec_hist_process.size()==2)
    color=kCyan;
  else if (vec_hist_process.size()==3)
    color=kGreen;
  else if (vec_hist_process.size()==4)
    color=kYellow;
  else if (vec_hist_process.size()==5)
    color=kBlack;
  else if (vec_hist_process.size()==6)
    color=kYellow;
  else if (vec_hist_process.size()==7)
    color=kOrange;
  else if (vec_hist_process.size()==8)
    color=kRed;
  else if (vec_hist_process.size()==9)
    color=kPink;

  hist->SetMarkerColor(color);
  hist->SetLineColor(color);
  chain_process->Project(hist->GetName(),string_finalDV.c_str(),"weight_total");

  double integral=hist->Integral();
  hist->Scale(1./integral);
  
  vec_hist_process.push_back(hist);

  return 0;
}
//===========================================================================================================
void set_plot_style()
{
//from : http://ultrahigh.org/2007/08/making-pretty-root-color-palettes/
const Int_t NRGBs=5;
const Int_t NCont=255;

Double_t stops[NRGBs]={0.00,0.34,0.61,0.84,1.00};
Double_t red[NRGBs]={0.00,0.00,0.87,1.00,0.51};
Double_t green[NRGBs]={0.00,0.81,1.00,0.20,0.00};
Double_t blue[NRGBs]={0.51,1.00,0.12,0.00,0.00};
TColor::CreateGradientColorTable(NRGBs,stops,red,green,blue,NCont);
gStyle->SetNumberContours(NCont);
}
