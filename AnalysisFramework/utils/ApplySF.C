#include "TLatex.h"
#include "TTree.h"
#include <TLine.h>
#include <TSpline.h>
#include <TH2.h>
#include <TStyle.h>
#include <vector>
#include <algorithm>
#include <TCanvas.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include "TLorentzVector.h"
#include "TLegend.h"
#include "TF1.h"
#include "TFile.h"

using namespace std;

int main(int argc, char** argv)
{

	TH1::SetDefaultSumw2();

	TString regionName=argv[1];
	TString targetName=argv[2];
	TString dataName=argv[3];
	TString ttyyallName=argv[4];
	TString ttyynoName=argv[5];
	TString varName=argv[6];


	TString dir = "../run/plots/";

	TFile * purityFile = new TFile("Nonresonant_purity.root", "read");
	TH1F * ggHist = (TH1F *) purityFile->Get("gg"); 
	TH1F * jgHist = (TH1F *) purityFile->Get("jg"); 
	TH1F * jjHist = (TH1F *) purityFile->Get("jj"); 
	
	vector<TString> varNames={"m_yy", "m_jj", "m_yyjj_tilde", "N_j", "N_j_central"};

	TFile * targetFile = new TFile(dir+Form("%s_%s.root", targetName.Data(), regionName.Data()), "read");
	TH1F * targetHist_1 = (TH1F *) targetFile->Get(Form("sumHisto_%s_%s", varNames[0].Data(), regionName.Data()));
	TH1F * targetHist_2 = (TH1F *) targetFile->Get(Form("sumHisto_%s_%s", varNames[1].Data(), regionName.Data()));
	TH1F * targetHist_3 = (TH1F *) targetFile->Get(Form("sumHisto_%s_%s", varNames[2].Data(), regionName.Data()));
	TH1F * targetHist_4 = (TH1F *) targetFile->Get(Form("sumHisto_%s_%s", varNames[3].Data(), regionName.Data()));
	TH1F * targetHist_5 = (TH1F *) targetFile->Get(Form("sumHisto_%s_%s", varNames[4].Data(), regionName.Data()));

	TFile * dataFile = new TFile(dir+Form("%s_%s.root", dataName.Data(), regionName.Data()), "read");
	TH1F * dataHist_1 = (TH1F *) dataFile->Get(Form("sumHisto_%s_%s", varNames[0].Data(), regionName.Data()));
	TH1F * dataHist_2 = (TH1F *) dataFile->Get(Form("sumHisto_%s_%s", varNames[1].Data(), regionName.Data()));
	TH1F * dataHist_3 = (TH1F *) dataFile->Get(Form("sumHisto_%s_%s", varNames[2].Data(), regionName.Data()));
	TH1F * dataHist_4 = (TH1F *) dataFile->Get(Form("sumHisto_%s_%s", varNames[3].Data(), regionName.Data()));
	TH1F * dataHist_5 = (TH1F *) dataFile->Get(Form("sumHisto_%s_%s", varNames[4].Data(), regionName.Data()));

	TFile * ttyyallFile = new TFile(dir+Form("%s_%s.root", ttyyallName.Data(), regionName.Data()), "read");
	TH1F * ttyyallHist_1 = (TH1F *) ttyyallFile->Get(Form("sumHisto_%s_%s", varNames[0].Data(), regionName.Data()));
	TH1F * ttyyallHist_2 = (TH1F *) ttyyallFile->Get(Form("sumHisto_%s_%s", varNames[1].Data(), regionName.Data()));
	TH1F * ttyyallHist_3 = (TH1F *) ttyyallFile->Get(Form("sumHisto_%s_%s", varNames[2].Data(), regionName.Data()));
	TH1F * ttyyallHist_4 = (TH1F *) ttyyallFile->Get(Form("sumHisto_%s_%s", varNames[3].Data(), regionName.Data()));
	TH1F * ttyyallHist_5 = (TH1F *) ttyyallFile->Get(Form("sumHisto_%s_%s", varNames[4].Data(), regionName.Data()));

	TFile * ttyynoFile = new TFile(dir+Form("%s_%s.root", ttyynoName.Data(), regionName.Data()), "read");
	TH1F * ttyynoHist_1 = (TH1F *) ttyynoFile->Get(Form("sumHisto_%s_%s", varNames[0].Data(), regionName.Data()));
	TH1F * ttyynoHist_2 = (TH1F *) ttyynoFile->Get(Form("sumHisto_%s_%s", varNames[1].Data(), regionName.Data()));
	TH1F * ttyynoHist_3 = (TH1F *) ttyynoFile->Get(Form("sumHisto_%s_%s", varNames[2].Data(), regionName.Data()));
	TH1F * ttyynoHist_4 = (TH1F *) ttyynoFile->Get(Form("sumHisto_%s_%s", varNames[3].Data(), regionName.Data()));
	TH1F * ttyynoHist_5 = (TH1F *) ttyynoFile->Get(Form("sumHisto_%s_%s", varNames[4].Data(), regionName.Data()));


	TFile * outFile = new TFile(dir+Form("%s_reweighted_%s.root", targetName.Data(), regionName.Data()), "recreate");
	TH1F * outHist_1 = (TH1F*)targetHist_1->Clone(Form("sumHisto_%s_%s", varNames[0].Data(), regionName.Data()));
	TH1F * outHist_2 = (TH1F*)targetHist_2->Clone(Form("sumHisto_%s_%s", varNames[1].Data(), regionName.Data()));
	TH1F * outHist_3 = (TH1F*)targetHist_3->Clone(Form("sumHisto_%s_%s", varNames[2].Data(), regionName.Data()));
	TH1F * outHist_4 = (TH1F*)targetHist_4->Clone(Form("sumHisto_%s_%s", varNames[3].Data(), regionName.Data()));
	TH1F * outHist_5 = (TH1F*)targetHist_5->Clone(Form("sumHisto_%s_%s", varNames[4].Data(), regionName.Data()));

	float purity, N_data, N_ttyy, N_target;	
	N_data = dataHist_1->Integral();
	cout<<"ttyyallHist_1= "<<ttyyallHist_1->Integral()<<" ttyynoHist_1= "<<ttyynoHist_1->Integral()<<endl;
	N_ttyy = ttyyallHist_1->Integral() + ttyynoHist_1->Integral();
	N_target = targetHist_1->Integral();

	if (targetName.Contains("yy")|| targetName.Contains("yybj") || targetName.Contains("yycj") || targetName.Contains("yylj")) {
		TH1F * purityHist = (TH1F*)ggHist->Clone("purity");
		if (regionName.Contains("Validation_2bjet")) {
			purity=purityHist->GetBinContent(5);
		}
		else if (regionName.Contains("XGBoost_btag77_withTop_BCal_tightScore_HMass")) {
			purity=purityHist->GetBinContent(1);
		}
		else if (regionName.Contains("XGBoost_btag77_withTop_BCal_looseScore_HMass")) {
			purity=purityHist->GetBinContent(2);
		}
		else if (regionName.Contains("XGBoost_btag77_withTop_BCal_tightScore_LMass") ){
			purity=purityHist->GetBinContent(3);
		}
		else if (regionName.Contains("XGBoost_btag77_withTop_BCal_looseScore_LMass")) {
			purity=purityHist->GetBinContent(4);
		}

	}
	else if (targetName.Contains("15_to_18_data_jj")) {
		TH1F * purityHist = (TH1F*)jjHist->Clone("purity");		
		if (regionName.Contains("Validation_2bjet")) {
			purity=purityHist->GetBinContent(5);
		}
		else if (regionName.Contains("XGBoost_btag77_withTop_BCal_tightScore_HMass")) {
			purity=purityHist->GetBinContent(1);
		}
		else if (regionName.Contains("XGBoost_btag77_withTop_BCal_looseScore_HMass")) {
			purity=purityHist->GetBinContent(2);
		}
		else if (regionName.Contains("XGBoost_btag77_withTop_BCal_tightScore_LMass") ){
			purity=purityHist->GetBinContent(3);
		}
		else if (regionName.Contains("XGBoost_btag77_withTop_BCal_looseScore_LMass")) {
			purity=purityHist->GetBinContent(4);
		}

	}
	else if (targetName.Contains("15_to_18_data_yj")) {
		TH1F * purityHist = (TH1F*)jgHist->Clone("purity");		
		if (regionName.Contains("Validation_2bjet")) {
			purity=purityHist->GetBinContent(5);
		}
		else if (regionName.Contains("XGBoost_btag77_withTop_BCal_tightScore_HMass")) {
			purity=purityHist->GetBinContent(1);
		}
		else if (regionName.Contains("XGBoost_btag77_withTop_BCal_looseScore_HMass")) {
			purity=purityHist->GetBinContent(2);
		}
		else if (regionName.Contains("XGBoost_btag77_withTop_BCal_tightScore_LMass") ){
			purity=purityHist->GetBinContent(3);
		}
		else if (regionName.Contains("XGBoost_btag77_withTop_BCal_looseScore_LMass")) {
			purity=purityHist->GetBinContent(4);
		}

	}


	TFile * yyFile = new TFile(dir+Form("yy_%s.root", regionName.Data()), "read");
	TH1F * yyHist_1 = (TH1F *) yyFile->Get(Form("sumHisto_%s_%s", varNames[0].Data(), regionName.Data()));
	TH1F * yyHist_2 = (TH1F *) yyFile->Get(Form("sumHisto_%s_%s", varNames[1].Data(), regionName.Data()));
	TH1F * yyHist_3 = (TH1F *) yyFile->Get(Form("sumHisto_%s_%s", varNames[2].Data(), regionName.Data()));
	TH1F * yyHist_4 = (TH1F *) yyFile->Get(Form("sumHisto_%s_%s", varNames[3].Data(), regionName.Data()));
	TH1F * yyHist_5 = (TH1F *) yyFile->Get(Form("sumHisto_%s_%s", varNames[4].Data(), regionName.Data()));
	float new_N_target = yyHist_1->Integral();
	if (targetName.Contains("yybj") || targetName.Contains("yycj") || targetName.Contains("yylj")) {
		N_target = new_N_target;
	}

	//float SF = purity * (N_data) / N_target;
	float SF = purity * (N_data - N_ttyy) / N_target;
	cout<<"purity = "<<purity<<endl;
	cout<<N_data<<" - "<<N_ttyy<<" / "<<N_target<<endl;
	if (N_target==0) SF=1;

	outHist_1->Scale(SF);
	outHist_2->Scale(SF);
	outHist_3->Scale(SF);
	outHist_4->Scale(SF);
	outHist_5->Scale(SF);
	cout<<N_target<<" -> "<<outHist_1->Integral()<<endl;

	outFile->cd();
	outHist_1->Write();
	outHist_2->Write();
	outHist_3->Write();
	outHist_4->Write();
	outHist_5->Write();
	outFile->Close();
}
