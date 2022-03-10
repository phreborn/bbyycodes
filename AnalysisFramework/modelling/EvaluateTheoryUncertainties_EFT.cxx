// Script to obtain the theory uncertainties for the reweighted HEFT signal samples and summarise them as a dictionary in a json file.
// Author: laura.pereira.sanchez@cern.ch                                                                                                                                                                     

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2F.h"
#include "TH1.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"
#include <math.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::string coupling = "tthh";

std::vector <std::string> regions = {"Loose_HM"};//, "Tight_LM", "Loose_LM", "Tight_HM"};
std::vector <std::string> systematics = {"QCD", "alpha", "PDF"};

std::vector <std::string> HEFT = {"SM",coupling+"_m2", coupling+"_m1.4",coupling+"_m1.0",coupling+"_m0.8", coupling+"_m0.4", coupling+"_0.0", coupling+"_0.2", coupling+"_0.4", coupling+"_0.6", coupling+"_0.8", coupling+"_1.0", coupling+"_1.4", coupling+"_2.0" };

//std::vector <std::string> HEFT = {"SM", "BM1", "BM2", "BM3", "BM4", "BM5", "BM6", "BM7"};


TString path ="/eos/user/l/lapereir/HH/Signals/H26/noskim_samples_h026/theory_unc2/";
std::vector <TString> samples = {"mc16a", "mc16d", "mc16e"};


float GetSumOfWeights(TString mc, int index, int nom_index){

  TFile *f = new TFile(path+"/"+mc+".PowhegPy8_HHbbyy_cHHH01d0.root", "READ");  
  TH1F* histo = (TH1F*)f->Get("CutFlow_PowhegPy8_HHbbyy_cHHH01d0_noDalitz_weighted");
  float real = histo->GetBinContent(3);
  TTreeReader reader("CollectionTree", f);
  TTreeReaderValue<float> original_weight (reader, "HGamEventInfoAuxDyn.weightInitial");
  TTreeReaderArray<float> mc_weight (reader, "EventInfoAuxDyn.mcEventWeights");
  TTreeReaderValue<Char_t> isDalitz (reader, "HGamEventInfoAuxDyn.isDalitz");
  
  float sum = 0;
  int d;
  while (reader.Next()) {
    d = *isDalitz;                                                                                                                                                                                      
    if (d == 1) continue;                                                                                                                                                                               
    sum += (*original_weight)*mc_weight[index]/mc_weight[nom_index];
  }
 
  f->Close();

  //std::cout << sum <<  " " << real <<  std::endl;
  
  return sum;

}

float GetYield(TString reg, map<TString, TString> Selection, TString HEFT_weight, int index, int nom_index){

  float yield = 0;

  map<TString, float> lumi;
  lumi["mc16a"] = 36207.66;
  lumi["mc16d"] = 44307.4;
  lumi["mc16e"] = 58450.1;


  for (std::vector<TString>::iterator it_s=samples.begin(); it_s!=samples.end(); ++it_s)
    {
      TString mc = *it_s;
      float sum = GetSumOfWeights(mc, index, nom_index);
      //std::cout << sum << std::endl;                                                                                                                                                                                                    

      TFile *f = new TFile(path+"/"+mc+".PowhegPy8_HHbbyy_cHHH01d0.root", "READ");
      TTree *t = (TTree*) f->Get("CollectionTree");

      //TTreeReader reader("CollectionTree", f);                                                                                                                                                                                          
      //TTreeReaderValue<float> original_weight (reader, "HGamEventInfoAuxDyn.weightInitial");                                                                                                                                            

      TH1F *h = new TH1F("h", "h", 5, 0, 5);
      //std::cout << Selection[reg]+"*"+Selection["weight"]+"*"+HEFT_weight+"*EventInfoAuxDyn.mcEventWeights["+std::to_string(index)+"]/EventInfoAuxDyn.mcEventWeights["+nom_index+"]*"+std::to_string(lumi[mc])+"/"+std::to_string(sum)  << std::endl;
      t->Draw(" 2   >> h", Selection[reg]+"*"+Selection["weight"]+"*"+HEFT_weight+"*EventInfoAuxDyn.mcEventWeights["+std::to_string(index)+"]/EventInfoAuxDyn.mcEventWeights["+nom_index+"]*"+std::to_string(lumi[mc])+"/"+std::to_string(sum), "goff");
      yield += h->Integral();
      f->Close();

    }
  std::cout << "Total sum " << reg << "  = " << yield << std::endl;

  return yield;

}



float GetEfficiency(TString reg, map<TString, TString> Selection, TString HEFT_weight, int index, int nom_index){

  float yield = 0;
  float nocuts_yield = 0;

  map<TString, float> lumi;
  lumi["mc16a"] = 36207.66;
  lumi["mc16d"] = 44307.4;
  lumi["mc16e"] = 58450.1;

  float Total_Lumi =  lumi["mc16a"]+lumi["mc16d"]+lumi["mc16e"];

  for (std::vector<TString>::iterator it_s=samples.begin(); it_s!=samples.end(); ++it_s)
    {
      TString mc = *it_s;
      float sum = GetSumOfWeights(mc, index, nom_index);
      //std::cout << sum << std::endl;                                                                                                                                                                                                                                                        

      TFile *f = new TFile(path+"/"+mc+".PowhegPy8_HHbbyy_cHHH01d0.root", "READ");
      TTree *t = (TTree*) f->Get("CollectionTree");

      //TTreeReader reader("CollectionTree", f);                                                                                                                                                                                                                                              
      //TTreeReaderValue<float> original_weight (reader, "HGamEventInfoAuxDyn.weightInitial");                                                                                                                                                                                                
      TH1F *h1 = new TH1F("h1", "h1", 5, 0, 5);
      t->Draw(" 2   >> h1", "(1)*"+Selection["weight"]+"*"+HEFT_weight+"*EventInfoAuxDyn.mcEventWeights["+std::to_string(index)+"]/EventInfoAuxDyn.mcEventWeights["+nom_index+"]*"+std::to_string(lumi[mc])+"/"+std::to_string(sum), "goff");
      nocuts_yield += h1->Integral();

      TH1F *h = new TH1F("h", "h", 5, 0, 5);
      //std::cout << Selection[reg]+"*"+Selection["weight"]+"*"+HEFT_weight+"*EventInfoAuxDyn.mcEventWeights["+std::to_string(index)+"]/EventInfoAuxDyn.mcEventWeights["+nom_index+"]*"+std::to_string(lumi[mc])+"/"+std::to_string(sum)  << std::endl;                                       
      t->Draw(" 2   >> h", Selection[reg]+"*"+Selection["weight"]+"*"+HEFT_weight+"*EventInfoAuxDyn.mcEventWeights["+std::to_string(index)+"]/EventInfoAuxDyn.mcEventWeights["+nom_index+"]*"+std::to_string(lumi[mc])+"/"+std::to_string(sum), "goff");
      yield += h->Integral();
      f->Close();

    }
 
  std::cout << "Total efficiency " << reg << "  = " << yield/nocuts_yield << std::endl;

  return yield;

}


int EvaluateTheoryUncertainties_EFT(){

  std::map <std::string,std::map<std::string, std::map<std::string, std::string> > > JsonMap;
  
  map<TString, TString> Selection;
  Selection["weight"] = "HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*HGamEventInfoAuxDyn.weightFJvt*HGamEventInfoAuxDyn.crossSectionBRfilterEff";
  Selection["Tight_HM"] = "(HGamEventInfoAuxDyn.isPassed == 1 &&  HGamEventInfoAuxDyn.yybb_btag77_cutFlow > 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_BCal_Cat/1000) % 10) == 1) && HGamEventInfoAuxDyn.m_yy*0.001 > 105 && HGamEventInfoAuxDyn.m_yy*0.001 < 160) ";
  Selection["Loose_HM"] = "(HGamEventInfoAuxDyn.isPassed == 1 &&  HGamEventInfoAuxDyn.yybb_btag77_cutFlow > 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_BCal_Cat/1000) % 10) == 2) && HGamEventInfoAuxDyn.m_yy*0.001 > 105 && HGamEventInfoAuxDyn.m_yy*0.001 < 160) ";
  Selection["Tight_LM"] = "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow > 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix]  && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_BCal_Cat/1000) % 10) == 3) && HGamEventInfoAuxDyn.m_yy*0.001 > 105 && HGamEventInfoAuxDyn.m_yy*0.001 < 160) ";
  Selection["Loose_LM"] = "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow > 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix]  && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_BCal_Cat/1000) % 10) == 4) && HGamEventInfoAuxDyn.m_yy*0.001 > 105 && HGamEventInfoAuxDyn.m_yy*0.001 < 160) ";


  map<TString, TString> HEFT_weights;
  HEFT_weights["SM"] = "1";
  HEFT_weights["BM1"] = "HEFT_weight.BM_1/HEFT_den_weight.BM_1";
  HEFT_weights["BM2"] = "HEFT_weight.BM_2/HEFT_den_weight.BM_2";
  HEFT_weights["BM3"] = "HEFT_weight.BM_3/HEFT_den_weight.BM_3";
  HEFT_weights["BM4"] = "HEFT_weight.BM_4/HEFT_den_weight.BM_4";
  HEFT_weights["BM5"] = "HEFT_weight.BM_5/HEFT_den_weight.BM_5";
  HEFT_weights["BM6"] = "HEFT_weight.BM_6/HEFT_den_weight.BM_6";
  HEFT_weights["BM7"] = "HEFT_weight.BM_7/HEFT_den_weight.BM_7";

  HEFT_weights["gghh_m2.0"] = "HEFT_weight.chhh_1_ctth_1_cgghh_0_cgghh_m2.0_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_0_cgghh_m2.0_cggh_0";
  HEFT_weights["gghh_m1.8"] = "HEFT_weight.chhh_1_ctth_1_ctthh_0_cgghh_m1.8_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_0_cgghh_m1.8_cggh_0";
  HEFT_weights["gghh_m1.6"] = "HEFT_weight.chhh_1_ctth_1_ctthh_0_cgghh_m1.6_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_0_cgghh_m1.6_cggh_0";
  HEFT_weights["gghh_m1.4"] = "HEFT_weight.chhh_1_ctth_1_ctthh_0_cgghh_m1.4_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_0_cgghh_m1.4_cggh_0";
  HEFT_weights["gghh_m1.2"] = "HEFT_weight.chhh_1_ctth_1_ctthh_0_cgghh_m1.2_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_0_cgghh_m1.2_cggh_0";
  HEFT_weights["gghh_m1.0"] = "HEFT_weight.chhh_1_ctth_1_ctthh_0_cgghh_m1.0_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_0_cgghh_m1.0_cggh_0";
  HEFT_weights["gghh_m0.8"] = "HEFT_weight.chhh_1_ctth_1_ctthh_0_cgghh_m0.8_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_0_cgghh_m0.8_cggh_0";
  HEFT_weights["gghh_m0.6"] = "HEFT_weight.chhh_1_ctth_1_ctthh_0_cgghh_m0.6_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_0_cgghh_m0.6_cggh_0";
  HEFT_weights["gghh_m0.4"] = "HEFT_weight.chhh_1_ctth_1_ctthh_0_cgghh_m0.4_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_0_cgghh_m0.4_cggh_0";
  HEFT_weights["gghh_m0.2"] = "HEFT_weight.chhh_1_ctth_1_ctthh_0_cgghh_m0.2_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_0_cgghh_m0.2_cggh_0";  
  HEFT_weights["gghh_2.0"] = "HEFT_weight.chhh_1_ctth_1_ctthh_0_cgghh_2.0_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_0_cgghh_2.0_cggh_0";
  HEFT_weights["gghh_1.8"] = "HEFT_weight.chhh_1_ctth_1_ctthh_0_cgghh_1.8_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_0_cgghh_1.8_cggh_0";
  HEFT_weights["gghh_1.6"] = "HEFT_weight.chhh_1_ctth_1_ctthh_0_cgghh_1.6_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_0_cgghh_1.6_cggh_0";
  HEFT_weights["gghh_1.4"] = "HEFT_weight.chhh_1_ctth_1_ctthh_0_cgghh_1.4_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_0_cgghh_1.4_cggh_0";
  HEFT_weights["gghh_1.2"] = "HEFT_weight.chhh_1_ctth_1_ctthh_0_cgghh_1.2_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_0_cgghh_1.2_cggh_0";
  HEFT_weights["gghh_1.0"] = "HEFT_weight.chhh_1_ctth_1_ctthh_0_cgghh_1.0_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_0_cgghh_1.0_cggh_0";
  HEFT_weights["gghh_0.8"] = "HEFT_weight.chhh_1_ctth_1_ctthh_0_cgghh_0.8_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_0_cgghh_0.8_cggh_0";
  HEFT_weights["gghh_0.6"] = "HEFT_weight.chhh_1_ctth_1_ctthh_0_cgghh_0.6_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_0_cgghh_0.6_cggh_0";
  HEFT_weights["gghh_0.4"] = "HEFT_weight.chhh_1_ctth_1_ctthh_0_cgghh_0.4_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_0_cgghh_0.4_cggh_0";
  HEFT_weights["gghh_0.2"] = "HEFT_weight.chhh_1_ctth_1_ctthh_0_cgghh_0.2_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_0_cgghh_0.2_cggh_0";
  HEFT_weights["gghh_0.0"] = "HEFT_weight.chhh_1_ctth_1_ctthh_0_cgghh_0.0_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_0_cgghh_0.0_cggh_0";


  HEFT_weights["tthh_m2.0"] = "HEFT_weight.chhh_1_ctth_1_ctthh_m2.0_cgghh_0_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_m2.0_cgghh_0_cggh_0";
  HEFT_weights["tthh_m1.8"] = "HEFT_weight.chhh_1_ctth_1_ctthh_m1.8_cgghh_0_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_m1.8_cgghh_0_cggh_0";
  HEFT_weights["tthh_m1.6"] = "HEFT_weight.chhh_1_ctth_1_ctthh_m1.6_cgghh_0_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_m1.6_cgghh_0_cggh_0";
  HEFT_weights["tthh_m1.4"] = "HEFT_weight.chhh_1_ctth_1_ctthh_m1.4_cgghh_0_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_m1.4_cgghh_0_cggh_0";
  HEFT_weights["tthh_m1.2"] = "HEFT_weight.chhh_1_ctth_1_ctthh_m1.2_cgghh_0_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_m1.2_cgghh_0_cggh_0";
  HEFT_weights["tthh_m1.0"] = "HEFT_weight.chhh_1_ctth_1_ctthh_m1.0_cgghh_0_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_m1.0_cgghh_0_cggh_0";
  HEFT_weights["tthh_m0.8"] = "HEFT_weight.chhh_1_ctth_1_ctthh_m0.8_cgghh_0_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_m0.8_cgghh_0_cggh_0";
  HEFT_weights["tthh_m0.6"] = "HEFT_weight.chhh_1_ctth_1_ctthh_m0.6_cgghh_0_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_m0.6_cgghh_0_cggh_0";
  HEFT_weights["tthh_m0.4"] = "HEFT_weight.chhh_1_ctth_1_ctthh_m0.4_cgghh_0_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_m0.4_cgghh_0_cggh_0";
  HEFT_weights["tthh_m0.2"] = "HEFT_weight.chhh_1_ctth_1_ctthh_m0.2_cgghh_0_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_m0.2_cgghh_0_cggh_0";
  HEFT_weights["tthh_2.0"] = "HEFT_weight.chhh_1_ctth_1_ctthh_2.0_cgghh_0_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_2.0_cgghh_0_cggh_0";
  HEFT_weights["tthh_1.8"] = "HEFT_weight.chhh_1_ctth_1_ctthh_1.8_cgghh_0_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_1.8_cgghh_0_cggh_0";
  HEFT_weights["tthh_1.6"] = "HEFT_weight.chhh_1_ctth_1_ctthh_1.6_cgghh_0_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_1.6_cgghh_0_cggh_0";
  HEFT_weights["tthh_1.4"] = "HEFT_weight.chhh_1_ctth_1_ctthh_1.4_cgghh_0_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_1.4_cgghh_0_cggh_0";
  HEFT_weights["tthh_1.2"] = "HEFT_weight.chhh_1_ctth_1_ctthh_1.2_cgghh_0_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_1.2_cgghh_0_cggh_0";
  HEFT_weights["tthh_1.0"] = "HEFT_weight.chhh_1_ctth_1_ctthh_1.0_cgghh_0_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_1.0_cgghh_0_cggh_0";
  HEFT_weights["tthh_0.8"] = "HEFT_weight.chhh_1_ctth_1_ctthh_0.8_cgghh_0_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_0.8_cgghh_0_cggh_0";
  HEFT_weights["tthh_0.6"] = "HEFT_weight.chhh_1_ctth_1_ctthh_0.6_cgghh_0_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_0.6_cgghh_0_cggh_0";
  HEFT_weights["tthh_0.4"] = "HEFT_weight.chhh_1_ctth_1_ctthh_0.4_cgghh_0_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_0.4_cgghh_0_cggh_0";
  HEFT_weights["tthh_0.2"] = "HEFT_weight.chhh_1_ctth_1_ctthh_0.2_cgghh_0_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_0.2_cgghh_0_cggh_0";
  HEFT_weights["tthh_0.0"] = "HEFT_weight.chhh_1_ctth_1_ctthh_0.0_cgghh_0_cggh_0/HEFT_den_weight.chhh_1_ctth_1_ctthh_0.0_cgghh_0_cggh_0";


  // map<TString, float> sum_of_weight;

  //float real, sum = GetSumOfWeights(sum_of_weight, 0, 0);

  //std::cout << "sum of weights " << sum << std::endl;
  //std::cout << sum_of_weight["mc16a"] << std::endl;

  map<TString, std::vector<int> > Systematics;
  Systematics["QCD"] = {0, 2, 3, 4, 5, 6, 7};
  Systematics["PDF"] = {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43};
  Systematics["alpha"] = {44, 45};

  for (std::vector<std::string>::iterator it_w=HEFT.begin(); it_w!=HEFT.end(); ++it_w){

    TString heft_weight = HEFT_weights[*it_w];
    std::cout << *it_w << std::endl;
    //std::cout << heft_weight << std::endl;
    for (std::vector<std::string>::iterator it_r=regions.begin(); it_r!=regions.end(); ++it_r)
      {
	TString reg = *it_r;
	
	for (std::vector<std::string>::iterator it_s=systematics.begin(); it_s!=systematics.end(); ++it_s)
	  {
	    TString unc = *it_s;
	    
	    std::cout << unc << std::endl;
	    //std::cout <<  Systematics["QCD"][0] << std::endl;
	    float yield_SM = GetYield(reg, Selection, heft_weight, Systematics[unc][0], Systematics[unc][0]);

	    std::vector < float > Uncertainty_list = {};
	    for (std::vector<int>::iterator it_v=Systematics[unc].begin(); it_v!=Systematics[unc].end(); ++it_v)
	      {

		float yield_index = GetYield(reg, Selection, heft_weight, *it_v, Systematics[unc][0]);
		float sys = (1-yield_index/yield_SM)*100;
	      
		//std::cout <<  unc << " with index  " << *it_v << " has an uncertainty of " <<  sys << std::endl;

		Uncertainty_list.push_back(sys);
		//std::cout << yield_SM << " " << yield_index << " " << sys << std::endl;
	      }

	    
	    float total_unc = 0;
	    std::vector <float> total_unc_list = {};
	    for (std::vector<float>::iterator v=Uncertainty_list.begin(); v!=Uncertainty_list.end(); ++v){
	      
	      float value = *v;
	      if (*it_s == "QCD"){
		total_unc_list.push_back(value);
	      } else{
		total_unc += pow(value,2);
	      }
	    }
	    
	    if (*it_s == "QCD") {
	      total_unc = *std::max_element(total_unc_list.begin(), total_unc_list.end());
	    } else{
	      total_unc = sqrt(total_unc);
	    }

	    JsonMap[*it_r][*it_w][*it_s] = std::to_string(total_unc);
	  
	    std::cout <<  unc << " uncertainty for "<< *it_w << " in " << reg << " = " << total_unc << std::endl; 

	  }

      }
    }

  json j = JsonMap;
  std::ofstream json_file;
  json_file.open("HEFT_TheoryUncYields_scans_"+regions[0]+"_"+coupling+".json");
  json_file << std::setw(4) << j;

  return 0;

}


