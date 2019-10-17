#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "samples.h"
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TChain.h"
#include "TCanvas.h"

using Sample = mytest::Sample;

struct Analysis_functions {

  static void Analyze_Sample(Sample s)
  {
    if (s.type=="dummy")
      std::cout<<" found dummy sample type!"<<std::endl;
    else if (s.type=="MC")
    {
      std::cout<<"found MC sample type!"<<std::endl;
      Analyze_MCSample(s);
    }
    else if (s.type=="data")
    {
      std::cout<<"found DATA sample type"<<std::endl;
      Analyze_dataSample(s);
    }
    return;
  }

  static void Analyze_dataSample(Sample s)
  {
    //create an output file 
    TFile f_w (s.output_fileName.c_str(), "recreate" );

    TChain* nt = new TChain("CollectionTree");
    nt->Add(s.file1Name.c_str());
    nt->Add(s.file2Name.c_str());

    //const char* myy_var = "HGamEventInfoAuxDyn.m_yy*0.001";
    //const char* myybb_var = "HGamEventInfoAuxDyn.yybb_lowMass_m_yybb*0.001";

    //const char* selection = "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_bTagCat == 2 && HGamEventInfoAuxDyn.yybb_lowMass_cutFlow > 3 && (HGamEventInfoAuxDyn.m_yy*0.001 < 120.0 || HGamEventInfoAuxDyn.m_yy*0.001 > 130.0 )   )*1.0";

    //const int nbins_myy = 22;
    //const int lbins_myy = 105;
    //const int ubins_myy = 160;

    std::string s_a=s.variable+">> h_myy_mc16a";

    // define m_yy histograms for mc16a and mc16d 
    TH1* h_myy_mc16a = new TH1F("h_myy_mc16a", "h_myy_mc16a", s.nBins, s.lowerBin, s.upperBin);
    h_myy_mc16a->Sumw2();
    nt->Draw(s_a.c_str(), s.selection.c_str());

    TCanvas c1;
    std::string canvasName(s.name);
    canvasName+=".png";
    c1.SaveAs(canvasName.c_str());

    f_w.Write();
    f_w.Close();
  }

  static void Analyze_MCSample(Sample s)
  {
    TFile mc16a_file (s.file1Name.c_str());
    TFile mc16d_file (s.file2Name.c_str());

    //create an output file 
    TFile f_w (s.output_fileName.c_str(), "recreate" );

    TH1* mc16a_cut_flow_histo = dynamic_cast <TH1*> (mc16a_file.Get(s.cut_flow_histo_name.c_str()));
    TH1* mc16d_cut_flow_histo = dynamic_cast <TH1*> (mc16d_file.Get(s.cut_flow_histo_name.c_str()));

    double binA_mc16a = 0;
    double binA_mc16d = 0;
    double binB_mc16a = 0;
    double binB_mc16d = 0;

    if (mc16a_cut_flow_histo) {
      binA_mc16a = mc16a_cut_flow_histo->GetBinContent(1);
      binB_mc16a = mc16a_cut_flow_histo->GetBinContent(2);
    }

    if (mc16d_cut_flow_histo) {
      binA_mc16d = mc16d_cut_flow_histo->GetBinContent(1);
      binB_mc16d = mc16d_cut_flow_histo->GetBinContent(2);
    }

    std::cout<< "binA_mc16a=" << binA_mc16a << "  binA_mc16d=" << binA_mc16d << "   binB_mc16a=" << binB_mc16a << "   binB_mc16d=" << binB_mc16d <<std::endl;

    double sum_weights_mc16a = mc16a_cut_flow_histo->GetBinContent(3)*(binA_mc16a/binB_mc16a);
    double sum_weights_mc16d = mc16d_cut_flow_histo->GetBinContent(3)*(binA_mc16d/binB_mc16d);

    TTree* ttree_mc16a = (TTree*) mc16a_file.Get("CollectionTree");
    TTree* ttree_mc16d = (TTree*) mc16d_file.Get("CollectionTree");

    //const char* myy_var = "HGamEventInfoAuxDyn.m_yy*0.001";
    //const char* myybb_var = "HGamEventInfoAuxDyn.yybb_lowMass_m_yybb*0.001";

    const char* selection = s.selection.c_str();

    std::string s_a=s.variable+">> h_myy_mc16a";

    std::string s_d=s.variable+">> h_myy_mc16d";

    std::cout<<" ======> selection = "<<s.selection<<"  variable = "<<s.variable<<std::endl;

    // define m_yy histograms for mc16a and mc16d 
    TH1* h_myy_mc16a = new TH1F("h_myy_mc16a", "h_myy_mc16a", s.nBins, s.lowerBin, s.upperBin);
    h_myy_mc16a->Sumw2();
    ttree_mc16a->Draw(s_a.c_str(), selection);
    //ttree_mc16a->Draw("HGamEventInfoAuxDyn.m_yy*0.001 >> h_myy_mc16a", selection);

    TH1* h_myy_mc16d = new TH1F("h_myy_mc16d", "h_myy_mc16d", s.nBins, s.lowerBin, s.upperBin);
    h_myy_mc16d->Sumw2();
    ttree_mc16d->Draw(s_d.c_str(), selection);

    const double mc16a_lumi = 36100;
    const double mc16d_lumi = 43700;

    //scale histogram by factor of lumi / event weights
    h_myy_mc16a->Scale( mc16a_lumi / sum_weights_mc16a );
    h_myy_mc16d->Scale( mc16d_lumi / sum_weights_mc16d );

    std::cout << "mc16a yield = " << h_myy_mc16a->Integral() << std::endl;
    std::cout << "mc16d yield = " << h_myy_mc16d->Integral() << std::endl;

    h_myy_mc16a->Add(h_myy_mc16d);
    h_myy_mc16a->SetMarkerColor(kRed);
    h_myy_mc16a->SetLineColor(kRed); 

    //h_myy_mc16a->Draw();

    std::cout << "total yield = " << h_myy_mc16a->Integral() << std::endl;

    TH1* h_myy_combined = (TH1F*) h_myy_mc16a->Clone();
    h_myy_combined->SetName("h_myy_combined");

    TCanvas c1;
    h_myy_combined->Draw();
    std::string canvasName(s.name);
    canvasName+=".png";
    c1.SaveAs(canvasName.c_str());

    h_myy_combined->Write();

    f_w.Write();
    f_w.Close();
  }
};


