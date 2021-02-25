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
	TString mXName=argv[2];
	TString targetName=argv[3];
	TString dataName=argv[4];
	TString ttyyallName=argv[5];
	TString ttyynoName=argv[6];
	TString varName=argv[7];


	TString dir = "../run/plots/";

	TFile * purityFile = new TFile("Resonant_purity.root", "read");
	TH1F * ggHist = (TH1F *) purityFile->Get("GG"); 
	TH1F * jgHist = (TH1F *) purityFile->Get("JG"); 
	TH1F * jjHist = (TH1F *) purityFile->Get("JJ"); 

	vector<TString> varNames={"m_yy", "m_jj", "m_yyjj_tilde", "N_j", "N_j_central"};

	TFile * dataFile = new TFile(dir+Form("%s_%s_%s.root", dataName.Data(), mXName.Data(), regionName.Data()), "read");
	TH1F * dataHist_1 = (TH1F *) dataFile->Get(Form("sumHisto_%s_%s_%s", varNames[0].Data(), mXName.Data(), regionName.Data()));
	TH1F * dataHist_2 = (TH1F *) dataFile->Get(Form("sumHisto_%s_%s_%s", varNames[1].Data(), mXName.Data(), regionName.Data()));
	TH1F * dataHist_3 = (TH1F *) dataFile->Get(Form("sumHisto_%s_%s_%s", varNames[2].Data(), mXName.Data(), regionName.Data()));
	TH1F * dataHist_4 = (TH1F *) dataFile->Get(Form("sumHisto_%s_%s_%s", varNames[3].Data(), mXName.Data(), regionName.Data()));
	TH1F * dataHist_5 = (TH1F *) dataFile->Get(Form("sumHisto_%s_%s_%s", varNames[4].Data(), mXName.Data(), regionName.Data()));

	TFile * ttyyallFile = new TFile(dir+Form("%s_%s_%s.root", ttyyallName.Data(), mXName.Data(), regionName.Data()), "read");
	TH1F * ttyyallHist_1 = (TH1F *) ttyyallFile->Get(Form("sumHisto_%s_%s_%s", varNames[0].Data(), mXName.Data(), regionName.Data()));
	TH1F * ttyyallHist_2 = (TH1F *) ttyyallFile->Get(Form("sumHisto_%s_%s_%s", varNames[1].Data(), mXName.Data(), regionName.Data()));
	TH1F * ttyyallHist_3 = (TH1F *) ttyyallFile->Get(Form("sumHisto_%s_%s_%s", varNames[2].Data(), mXName.Data(), regionName.Data()));
	TH1F * ttyyallHist_4 = (TH1F *) ttyyallFile->Get(Form("sumHisto_%s_%s_%s", varNames[3].Data(), mXName.Data(), regionName.Data()));
	TH1F * ttyyallHist_5 = (TH1F *) ttyyallFile->Get(Form("sumHisto_%s_%s_%s", varNames[4].Data(), mXName.Data(), regionName.Data()));

	TFile * ttyynoFile = new TFile(dir+Form("%s_%s_%s.root", ttyynoName.Data(), mXName.Data(), regionName.Data()), "read");
	TH1F * ttyynoHist_1 = (TH1F *) ttyynoFile->Get(Form("sumHisto_%s_%s_%s", varNames[0].Data(), mXName.Data(), regionName.Data()));
	TH1F * ttyynoHist_2 = (TH1F *) ttyynoFile->Get(Form("sumHisto_%s_%s_%s", varNames[1].Data(), mXName.Data(), regionName.Data()));
	TH1F * ttyynoHist_3 = (TH1F *) ttyynoFile->Get(Form("sumHisto_%s_%s_%s", varNames[2].Data(), mXName.Data(), regionName.Data()));
	TH1F * ttyynoHist_4 = (TH1F *) ttyynoFile->Get(Form("sumHisto_%s_%s_%s", varNames[3].Data(), mXName.Data(), regionName.Data()));
	TH1F * ttyynoHist_5 = (TH1F *) ttyynoFile->Get(Form("sumHisto_%s_%s_%s", varNames[4].Data(), mXName.Data(), regionName.Data()));

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

/*
	vector<TString> SHmodes={"ggH_PowhegPy8","VBFH_PowhegPy8","WmH_PowhegPy8","WpH_PowhegPy8","ZH_PowhegPy8","ggZH_PowhegPy8","tHjb","tWH","ttH_PowhegPy8","bbH"};
	float SH_integral_SB = 0.;
	for(auto SH : SHmodes){
		TFile * SHFile = new TFile(dir+Form(SH+"_%s_%s.root", mXName.Data(), regionName.Data()), "read");
		TH1F * SHHist_1 = (TH1F *) SHFile->Get(Form("sumHisto_%s_%s_%s", varNames[0].Data(), mXName.Data(), regionName.Data()));
		SH_integral_SB += SHHist_1->Integral(SHHist_1->FindBin(lowcut), SHHist_1->FindBin(highcut))- SHHist_1->Integral(SHHist_1->FindBin(x1), SHHist_1->FindBin(x2));
	}
	cout<<"SHHist_1= "<<SH_integral_SB<<endl;
*/

	if (targetName.Contains("yy")) {
		TH1F * purityHist = (TH1F*)ggHist->Clone("purity");
		if (mXName.Contains("X251") ) {
			purity=purityHist->GetBinContent(1);
		}
		else if (mXName.Contains("X260") ) {
			purity=purityHist->GetBinContent(2);
		}
		else if (mXName.Contains("X280") ) {
			purity=purityHist->GetBinContent(3);
		}
		else if (mXName.Contains("X300") ) {
			purity=purityHist->GetBinContent(4);
		}
		else if (mXName.Contains("X325") ) {
			purity=purityHist->GetBinContent(5);
		}
		else if (mXName.Contains("X350") ) {
			purity=purityHist->GetBinContent(6);
		}
		else if (mXName.Contains("X400") ) {
			purity=purityHist->GetBinContent(7);
		}
		else if (mXName.Contains("X450") ) {
			purity=purityHist->GetBinContent(8);
		}
		else if (mXName.Contains("X500") ) {
			purity=purityHist->GetBinContent(9);
		}
		else if (mXName.Contains("X550") ) {
			purity=purityHist->GetBinContent(10);
		}
		else if (mXName.Contains("X600") ) {
			purity=purityHist->GetBinContent(11);
		}
		else if (mXName.Contains("X700") ) {
			purity=purityHist->GetBinContent(12);
		}
		else if (mXName.Contains("X800") ) {
			purity=purityHist->GetBinContent(13);
		}
		else if (mXName.Contains("X900") ) {
			purity=purityHist->GetBinContent(14);
		}
		else if (mXName.Contains("X1000") ) {
			purity=purityHist->GetBinContent(15);
		}
	}

	else if (targetName.Contains("15_to_18_data_jj")) {
		TH1F * purityHist = (TH1F*)jjHist->Clone("purity");
		if (mXName.Contains("X251") ) {
			purity=purityHist->GetBinContent(1);
		}
		else if (mXName.Contains("X260") ) {
			purity=purityHist->GetBinContent(2);
		}
		else if (mXName.Contains("X280") ) {
			purity=purityHist->GetBinContent(3);
		}
		else if (mXName.Contains("X300") ) {
			purity=purityHist->GetBinContent(4);
		}
		else if (mXName.Contains("X325") ) {
			purity=purityHist->GetBinContent(5);
		}
		else if (mXName.Contains("X350") ) {
			purity=purityHist->GetBinContent(6);
		}
		else if (mXName.Contains("X400") ) {
			purity=purityHist->GetBinContent(7);
		}
		else if (mXName.Contains("X450") ) {
			purity=purityHist->GetBinContent(8);
		}
		else if (mXName.Contains("X500") ) {
			purity=purityHist->GetBinContent(9);
		}
		else if (mXName.Contains("X550") ) {
			purity=purityHist->GetBinContent(10);
		}
		else if (mXName.Contains("X600") ) {
			purity=purityHist->GetBinContent(11);
		}
		else if (mXName.Contains("X700") ) {
			purity=purityHist->GetBinContent(12);
		}
		else if (mXName.Contains("X800") ) {
			purity=purityHist->GetBinContent(13);
		}
		else if (mXName.Contains("X900") ) {
			purity=purityHist->GetBinContent(14);
		}
		else if (mXName.Contains("X1000") ) {
			purity=purityHist->GetBinContent(15);
		}


	}
	else if (targetName.Contains("15_to_18_data_yj")) {
		TH1F * purityHist = (TH1F*)jgHist->Clone("purity");
		if (mXName.Contains("X251") ) {
			purity=purityHist->GetBinContent(1);
		}
		else if (mXName.Contains("X260") ) {
			purity=purityHist->GetBinContent(2);
		}
		else if (mXName.Contains("X280") ) {
			purity=purityHist->GetBinContent(3);
		}
		else if (mXName.Contains("X300") ) {
			purity=purityHist->GetBinContent(4);
		}
		else if (mXName.Contains("X325") ) {
			purity=purityHist->GetBinContent(5);
		}
		else if (mXName.Contains("X350") ) {
			purity=purityHist->GetBinContent(6);
		}
		else if (mXName.Contains("X400") ) {
			purity=purityHist->GetBinContent(7);
		}
		else if (mXName.Contains("X450") ) {
			purity=purityHist->GetBinContent(8);
		}
		else if (mXName.Contains("X500") ) {
			purity=purityHist->GetBinContent(9);
		}
		else if (mXName.Contains("X550") ) {
			purity=purityHist->GetBinContent(10);
		}
		else if (mXName.Contains("X600") ) {
			purity=purityHist->GetBinContent(11);
		}
		else if (mXName.Contains("X700") ) {
			purity=purityHist->GetBinContent(12);
		}
		else if (mXName.Contains("X800") ) {
			purity=purityHist->GetBinContent(13);
		}
		else if (mXName.Contains("X900") ) {
			purity=purityHist->GetBinContent(14);
		}
		else if (mXName.Contains("X1000") ) {
			purity=purityHist->GetBinContent(15);
		}	

	}

	TFile * yy_m_yyjjFile = new TFile(dir+Form("yy_m_yyjj_%s_%s.root", mXName.Data(), regionName.Data()), "read");
	TH1F * yy_m_yyjjHist_1 = (TH1F *) yy_m_yyjjFile->Get(Form("sumHisto_%s_%s_%s", varNames[0].Data(), mXName.Data(), regionName.Data()));
	TH1F * yy_m_yyjjHist_2 = (TH1F *) yy_m_yyjjFile->Get(Form("sumHisto_%s_%s_%s", varNames[1].Data(), mXName.Data(), regionName.Data()));
	TH1F * yy_m_yyjjHist_3 = (TH1F *) yy_m_yyjjFile->Get(Form("sumHisto_%s_%s_%s", varNames[2].Data(), mXName.Data(), regionName.Data()));
	TH1F * yy_m_yyjjHist_4 = (TH1F *) yy_m_yyjjFile->Get(Form("sumHisto_%s_%s_%s", varNames[3].Data(), mXName.Data(), regionName.Data()));
	TH1F * yy_m_yyjjHist_5 = (TH1F *) yy_m_yyjjFile->Get(Form("sumHisto_%s_%s_%s", varNames[4].Data(), mXName.Data(), regionName.Data()));

	TFile * yyFile = new TFile(dir+Form("yy_%s_%s.root", mXName.Data(), regionName.Data()), "read");
	TH1F * yyHist_1 = (TH1F *) yyFile->Get(Form("sumHisto_%s_%s_%s", varNames[0].Data(), mXName.Data(), regionName.Data()));
	TH1F * yyHist_2 = (TH1F *) yyFile->Get(Form("sumHisto_%s_%s_%s", varNames[1].Data(), mXName.Data(), regionName.Data()));
	TH1F * yyHist_3 = (TH1F *) yyFile->Get(Form("sumHisto_%s_%s_%s", varNames[2].Data(), mXName.Data(), regionName.Data()));
	TH1F * yyHist_4 = (TH1F *) yyFile->Get(Form("sumHisto_%s_%s_%s", varNames[3].Data(), mXName.Data(), regionName.Data()));
	TH1F * yyHist_5 = (TH1F *) yyFile->Get(Form("sumHisto_%s_%s_%s", varNames[4].Data(), mXName.Data(), regionName.Data()));

	TFile * outFile = new TFile(dir+Form("%s_reweighted_%s_%s.root", targetName.Data(), mXName.Data(), regionName.Data()), "recreate");
        TH1F * outHist_1 = (TH1F*)yyHist_1->Clone(Form("sumHisto_%s_%s_%s", varNames[0].Data(), mXName.Data(), regionName.Data()));
        TH1F * outHist_2 = (TH1F*)yyHist_2->Clone(Form("sumHisto_%s_%s_%s", varNames[1].Data(), mXName.Data(), regionName.Data()));
        TH1F * outHist_3 = (TH1F*)yyHist_3->Clone(Form("sumHisto_%s_%s_%s", varNames[2].Data(), mXName.Data(), regionName.Data()));
        TH1F * outHist_4 = (TH1F*)yyHist_4->Clone(Form("sumHisto_%s_%s_%s", varNames[3].Data(), mXName.Data(), regionName.Data()));
        TH1F * outHist_5 = (TH1F*)yyHist_5->Clone(Form("sumHisto_%s_%s_%s", varNames[4].Data(), mXName.Data(), regionName.Data()));

	float new_N_target = yy_m_yyjjHist_1->Integral(yy_m_yyjjHist_1->FindBin(lowcut), yy_m_yyjjHist_1->FindBin(highcut))- yy_m_yyjjHist_1->Integral(yy_m_yyjjHist_1->FindBin(x1), yy_m_yyjjHist_1->FindBin(x2));

        float SF = purity * (N_data - N_ttyy ) / new_N_target;
        //float SF = purity * (N_data - N_ttyy - SH_integral_SB) / new_N_target;
        cout<<"purity = "<<purity<<endl;
        cout<<N_data<<" - "<<N_ttyy<<" / "<<new_N_target<<endl;
        //cout<<N_data<<" - "<<N_ttyy<<" - "<<SH_integral_SB<<" / "<<new_N_target<<endl;

	outHist_1->Scale(SF);
	outHist_2->Scale(SF);
	outHist_3->Scale(SF);
	outHist_4->Scale(SF);
	outHist_5->Scale(SF);
	cout<<mXName<<" "<<SF<<endl;

	outFile->cd();
	outHist_1->Write();
	outHist_2->Write();
	outHist_3->Write();
	outHist_4->Write();
	outHist_5->Write();
	outFile->Close();
}
