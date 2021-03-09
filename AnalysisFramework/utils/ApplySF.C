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

	vector<TString> varNames={"m_yy", "m_jj", "m_yyjj_tilde", "N_j", "N_j_central","nonRes_XGBoost_btag77_BCal_withTop_lowMass_Score","nonRes_XGBoost_btag77_BCal_withTop_highMass_Score"};

	TFile * dataFile = new TFile(dir+Form("%s_%s.root", dataName.Data(), regionName.Data()), "read");
	TH1F * dataHist_1 = (TH1F *) dataFile->Get(Form("sumHisto_%s_%s", varNames[0].Data(), regionName.Data()));
	TH1F * dataHist_2 = (TH1F *) dataFile->Get(Form("sumHisto_%s_%s", varNames[1].Data(), regionName.Data()));
	TH1F * dataHist_3 = (TH1F *) dataFile->Get(Form("sumHisto_%s_%s", varNames[2].Data(), regionName.Data()));
	TH1F * dataHist_4 = (TH1F *) dataFile->Get(Form("sumHisto_%s_%s", varNames[3].Data(), regionName.Data()));
	TH1F * dataHist_5 = (TH1F *) dataFile->Get(Form("sumHisto_%s_%s", varNames[4].Data(), regionName.Data()));
	TH1F * dataHist_6 = (TH1F *) dataFile->Get(Form("sumHisto_%s_%s", varNames[5].Data(), regionName.Data()));
	TH1F * dataHist_7 = (TH1F *) dataFile->Get(Form("sumHisto_%s_%s", varNames[6].Data(), regionName.Data()));

	TFile * ttyyallFile = new TFile(dir+Form("%s_%s.root", ttyyallName.Data(), regionName.Data()), "read");
	TH1F * ttyyallHist_1 = (TH1F *) ttyyallFile->Get(Form("sumHisto_%s_%s", varNames[0].Data(), regionName.Data()));
	TH1F * ttyyallHist_2 = (TH1F *) ttyyallFile->Get(Form("sumHisto_%s_%s", varNames[1].Data(), regionName.Data()));
	TH1F * ttyyallHist_3 = (TH1F *) ttyyallFile->Get(Form("sumHisto_%s_%s", varNames[2].Data(), regionName.Data()));
	TH1F * ttyyallHist_4 = (TH1F *) ttyyallFile->Get(Form("sumHisto_%s_%s", varNames[3].Data(), regionName.Data()));
	TH1F * ttyyallHist_5 = (TH1F *) ttyyallFile->Get(Form("sumHisto_%s_%s", varNames[4].Data(), regionName.Data()));
	TH1F * ttyyallHist_6 = (TH1F *) ttyyallFile->Get(Form("sumHisto_%s_%s", varNames[5].Data(), regionName.Data()));
	TH1F * ttyyallHist_7 = (TH1F *) ttyyallFile->Get(Form("sumHisto_%s_%s", varNames[6].Data(), regionName.Data()));

	TFile * ttyynoFile = new TFile(dir+Form("%s_%s.root", ttyynoName.Data(), regionName.Data()), "read");
	TH1F * ttyynoHist_1 = (TH1F *) ttyynoFile->Get(Form("sumHisto_%s_%s", varNames[0].Data(), regionName.Data()));
	TH1F * ttyynoHist_2 = (TH1F *) ttyynoFile->Get(Form("sumHisto_%s_%s", varNames[1].Data(), regionName.Data()));
	TH1F * ttyynoHist_3 = (TH1F *) ttyynoFile->Get(Form("sumHisto_%s_%s", varNames[2].Data(), regionName.Data()));
	TH1F * ttyynoHist_4 = (TH1F *) ttyynoFile->Get(Form("sumHisto_%s_%s", varNames[3].Data(), regionName.Data()));
	TH1F * ttyynoHist_5 = (TH1F *) ttyynoFile->Get(Form("sumHisto_%s_%s", varNames[4].Data(), regionName.Data()));
	TH1F * ttyynoHist_6 = (TH1F *) ttyynoFile->Get(Form("sumHisto_%s_%s", varNames[5].Data(), regionName.Data()));
	TH1F * ttyynoHist_7 = (TH1F *) ttyynoFile->Get(Form("sumHisto_%s_%s", varNames[6].Data(), regionName.Data()));

	int x1 = 120.;
        int x2 = 130.;
        int lowcut = 105.;
        int highcut = 160.;

	float purity, N_data, N_ttyy, N_target;	
	N_data = dataHist_1->Integral(dataHist_1->FindBin(lowcut), dataHist_1->FindBin(highcut))- dataHist_1->Integral(dataHist_1->FindBin(x1), dataHist_1->FindBin(x2));
	float integral_ttyyall = ttyyallHist_1->Integral(ttyyallHist_1->FindBin(lowcut), ttyyallHist_1->FindBin(highcut))- ttyyallHist_1->Integral(ttyyallHist_1->FindBin(x1), ttyyallHist_1->FindBin(x2));
        float integral_ttyyno = ttyynoHist_1->Integral(ttyynoHist_1->FindBin(lowcut), ttyynoHist_1->FindBin(highcut))- ttyynoHist_1->Integral(ttyynoHist_1->FindBin(x1), ttyynoHist_1->FindBin(x2));
	N_ttyy = integral_ttyyall + integral_ttyyno;
	cout<<"ttyyHist_1= "<<N_ttyy<<endl;

	vector<TString> SHmodes={"ggH_PowhegPy8","VBFH_PowhegPy8","WmH_PowhegPy8","WpH_PowhegPy8","ZH_PowhegPy8","ggZH_PowhegPy8","tHjb","tWH","ttH_PowhegPy8","bbH"};
        float SH_integral_SB = 0.;
        for(auto SH : SHmodes){
          TFile * SHFile = new TFile(dir+Form(SH+"_%s.root", regionName.Data()), "read");
          TH1F * SHHist_1 = (TH1F *) SHFile->Get(Form("sumHisto_%s_%s", varNames[0].Data(), regionName.Data()));
          SH_integral_SB += SHHist_1->Integral(SHHist_1->FindBin(lowcut), SHHist_1->FindBin(highcut))- SHHist_1->Integral(SHHist_1->FindBin(x1), SHHist_1->FindBin(x2));
        }
	cout<<"SHHist_1= "<<SH_integral_SB<<endl;

	if (targetName.Contains("yy")) {
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


	else if (targetName.Contains("jj")) {
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
	else if (targetName.Contains("yj")) {
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
	TH1F * yyHist_6 = (TH1F *) yyFile->Get(Form("sumHisto_%s_%s", varNames[5].Data(), regionName.Data()));
	TH1F * yyHist_7 = (TH1F *) yyFile->Get(Form("sumHisto_%s_%s", varNames[6].Data(), regionName.Data()));


	TFile * outFile = new TFile(dir+Form("%s_reweighted_%s.root", targetName.Data(), regionName.Data()), "recreate");
	TH1F * outHist_1;
	TH1F * outHist_2;
	TH1F * outHist_3;
	TH1F * outHist_4;
	TH1F * outHist_5;
	TH1F * outHist_6;
	TH1F * outHist_7;
	outHist_1 = (TH1F*)yyHist_1->Clone(Form("sumHisto_%s_%s", varNames[0].Data(), regionName.Data()));
	outHist_2 = (TH1F*)yyHist_2->Clone(Form("sumHisto_%s_%s", varNames[1].Data(), regionName.Data()));
	outHist_3 = (TH1F*)yyHist_3->Clone(Form("sumHisto_%s_%s", varNames[2].Data(), regionName.Data()));
	outHist_4 = (TH1F*)yyHist_4->Clone(Form("sumHisto_%s_%s", varNames[3].Data(), regionName.Data()));
	outHist_5 = (TH1F*)yyHist_5->Clone(Form("sumHisto_%s_%s", varNames[4].Data(), regionName.Data()));
	outHist_6 = (TH1F*)yyHist_5->Clone(Form("sumHisto_%s_%s", varNames[5].Data(), regionName.Data()));
	outHist_7 = (TH1F*)yyHist_5->Clone(Form("sumHisto_%s_%s", varNames[6].Data(), regionName.Data()));
	
	if (targetName.Contains("yybb") || targetName.Contains("yyrr")) {
	TFile * targetFile = new TFile(dir+Form("%s_%s.root", targetName.Data(), regionName.Data()), "read");
	TH1F * targetHist_1 = (TH1F *) targetFile->Get(Form("sumHisto_%s_%s", varNames[0].Data(), regionName.Data()));
	TH1F * targetHist_2 = (TH1F *) targetFile->Get(Form("sumHisto_%s_%s", varNames[1].Data(), regionName.Data()));
	TH1F * targetHist_3 = (TH1F *) targetFile->Get(Form("sumHisto_%s_%s", varNames[2].Data(), regionName.Data()));
	TH1F * targetHist_4 = (TH1F *) targetFile->Get(Form("sumHisto_%s_%s", varNames[3].Data(), regionName.Data()));
	TH1F * targetHist_5 = (TH1F *) targetFile->Get(Form("sumHisto_%s_%s", varNames[4].Data(), regionName.Data()));
	TH1F * targetHist_6 = (TH1F *) targetFile->Get(Form("sumHisto_%s_%s", varNames[5].Data(), regionName.Data()));
	TH1F * targetHist_7 = (TH1F *) targetFile->Get(Form("sumHisto_%s_%s", varNames[6].Data(), regionName.Data()));
	outHist_1 = (TH1F*)targetHist_1->Clone(Form("sumHisto_%s_%s", varNames[0].Data(), regionName.Data()));
	outHist_2 = (TH1F*)targetHist_2->Clone(Form("sumHisto_%s_%s", varNames[1].Data(), regionName.Data()));
	outHist_3 = (TH1F*)targetHist_3->Clone(Form("sumHisto_%s_%s", varNames[2].Data(), regionName.Data()));
	outHist_4 = (TH1F*)targetHist_4->Clone(Form("sumHisto_%s_%s", varNames[3].Data(), regionName.Data()));
	outHist_5 = (TH1F*)targetHist_5->Clone(Form("sumHisto_%s_%s", varNames[4].Data(), regionName.Data()));
	outHist_6 = (TH1F*)targetHist_5->Clone(Form("sumHisto_%s_%s", varNames[5].Data(), regionName.Data()));
	outHist_7 = (TH1F*)targetHist_5->Clone(Form("sumHisto_%s_%s", varNames[6].Data(), regionName.Data()));
	
	}

	float new_N_target = yyHist_1->Integral(yyHist_1->FindBin(lowcut), yyHist_1->FindBin(highcut))- yyHist_1->Integral(yyHist_1->FindBin(x1), yyHist_1->FindBin(x2));

	float SF = ( purity * N_data - N_ttyy) / new_N_target;
	cout<<"( "<<purity<<" * "<<N_data<<" - "<<N_ttyy<<" ) / "<<new_N_target<<endl;
	if (targetName.Contains("yj") || targetName.Contains("jj")) {
		SF = ( purity * N_data ) / new_N_target;
		cout<<"( "<<purity<<" * "<<N_data<<" ) / "<<new_N_target<<endl;
	}

	cout<<"SF= "<<SF<<endl;
	outHist_1->Scale(SF);
	outHist_2->Scale(SF);
	outHist_3->Scale(SF);
	outHist_4->Scale(SF);
	outHist_5->Scale(SF);
	outHist_6->Scale(SF);
	outHist_7->Scale(SF);


	outFile->cd();
	outHist_1->Write();
	outHist_2->Write();
	outHist_3->Write();
	outHist_4->Write();
	outHist_5->Write();
	outHist_6->Write();
	outHist_7->Write();
	outFile->Close();
}
