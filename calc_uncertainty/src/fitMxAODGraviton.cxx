#include "TMath.h"
#include "TStopwatch.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TChain.h"
#include "TROOT.h"
#include "THStack.h"
#include "TLegend.h"
#include "TF1.h"
#include "TLatex.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TStyle.h"

#include "TLorentzVector.h"
#include "TMatrixD.h"
#include "TMatrixDSym.h"
#include "TMatrixDSymEigen.h"
#include "TRotation.h"

#include "TRandom.h"
#include "RooRealVar.h"
#include "RooFormulaVar.h"
#include "RooExponential.h"
#include "RooPlot.h"
#include "RooGaussian.h"
#include "RooPolynomial.h"
#include "RooAddPdf.h"
#include "RooAbsData.h"
#include "RooAbsRealLValue.h"
#include "RooAbsPdf.h"
#include "RooMinuit.h"
#include "RooCategory.h"
#include "RooDataSet.h"
#include "RooArgSet.h"
#include "RooDataHist.h"
#include "RooNLLVar.h"
#include "RooExponential.h"
#include "RooGlobalFunc.h"
#include "RooCBShape.h"
#include "RooFormula.h"
#include "RooRandom.h"
#include "RooFitResult.h"
#include "RooSimultaneous.h"
#include "RooConstVar.h"
#include "RooWorkspace.h"
#include "TRandom3.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;
using namespace RooFit;
#include <vector>

#include "DetectorReso/HggTwoSidedCBPdf.h"

TGraphErrors* plotDivision(RooAbsData *data, RooAbsPdf *pdf, RooRealVar *observable, int xBins) {
	// Store the original variable range:
	double minOrigin = observable->getMin();
	double maxOrigin = observable->getMax();
	//double nEvents = data->sumEntries();
	double nEvents = data->sumEntries(Form("%s>%f&&%s<%f", observable->GetName(), minOrigin, observable->GetName(), maxOrigin));
	TH1F *originHist = (TH1F*)data->createHistogram("dataSub", *observable, RooFit::Binning(xBins,minOrigin,maxOrigin));

	TGraphErrors *result = new TGraphErrors();
	double increment = ((maxOrigin - minOrigin) / ((double)xBins));
	observable->setRange("fullRange", minOrigin, maxOrigin);
	RooAbsReal* intTot = (RooAbsReal*)pdf->createIntegral(RooArgSet(*observable), RooFit::NormSet(*observable), RooFit::Range("fullRange"));
	double valTot = intTot->getVal();

	int pointIndex = 0;
	for (double i_m = minOrigin; i_m < maxOrigin; i_m += increment) {
		RooMsgService::instance().setGlobalKillBelow(RooFit::WARNING);

		observable->setRange(Form("range%2.2f",i_m), i_m, (i_m+increment));
		RooAbsReal* intCurr = (RooAbsReal*)pdf->createIntegral(RooArgSet(*observable), RooFit::NormSet(*observable), RooFit::Range(Form("range%2.2f",i_m)));
		double valCurr = intCurr->getVal();

		double currMass = i_m + (0.5*increment);
		double currPdfWeight = nEvents * (valCurr / valTot);
		TString varName = observable->GetName();
		double currDataWeight = data->sumEntries(Form("%s>%f&&%s<%f",varName.Data(), i_m,varName.Data(), (i_m+increment)));
		double currWeight = currDataWeight / currPdfWeight;
		result->SetPoint(pointIndex, currMass, currWeight);

		double currError = originHist->GetBinError(pointIndex+1) / currPdfWeight;
		result->SetPointError(pointIndex, 0.0, currError);
		pointIndex++;

	}
	// Return to the original variable range
	observable->setMin(minOrigin);
	observable->setMax(maxOrigin);
	delete originHist;
	return result;
}

int main(int argc, char** argv){

	if( argc != 2 ){
		cerr<<"Usage: "<<argv[0]<<" category name"<<endl;
		exit(1);
	}
	string category = argv[1];
	if( category[0]!='_' || category[category.size()-1]!='_' ){
		cerr<<"Category name must start and end with underscore(_)"<<endl;
		exit(1);
	}
	category = category.substr(1,category.size()-2);
	cout<<category<<endl;

	vector<double> truthmass = { 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 2500, 3500, 5000, 5500 };
	const int npoints = truthmass.size();
	gStyle->SetOptStat(0);

	double fitPercent=0.25;
	double showPercent=0.10;

	string prefix = "/localdata1/fwang/MxAOD/h012pre2/";

	vector<TTree*> datatree(npoints);
	double mass, weight;

	TFile* fout = new TFile("fout.root","recreate");
	fout->cd();
	for( int i=0; i<npoints; i++ ){
		datatree[i] = new TTree( Form("t_%.0f",truthmass[i]), "" );

		datatree[i] -> Branch("mass", &mass, "mass/D");
		datatree[i] -> Branch("weight", &weight, "weight/D");
	}

	TFile* fin = nullptr;
	TTree* tin = nullptr;
	for( int i=0; i<npoints; i++ ){
		fin = TFile::Open( Form("%sPythia8_G%.0f_k001.MxAOD.root",prefix.c_str(),truthmass[i]) );
		tin = dynamic_cast<TTree*>(fin->Get("CollectionTree"));

		char isPassedPreselection;
		char isPassedPID;
		char isPassedBasic;
		char isPassedIsolation;
		char isPassedRelPtCuts;
		char isPassedMassCut;
		char isPassedIsolationLowHighMyy;
		char isPassedRelPtCutsLowHighMyy;
		char isPassedLowHighMyy;
		char isPassedIsolationExotic;
		char isPassedlPtCutsExotic;
		char isPassedExotic;
		float vertexWeight;
		float Weight;
		vector<float>   *mcEventWeights=nullptr;
		float m_yy;
		float crossSectionBRfilterEff;
		unsigned int mcChannelNumber;
		vector<float>   *pt = nullptr;
		vector<float>   *eta_s2 = nullptr;
		vector<int>     *conversionType = nullptr;

		tin->SetBranchAddress("HGamEventInfoAuxDyn.isPassedPreselection",&isPassedPreselection);
		tin->SetBranchAddress("HGamEventInfoAuxDyn.isPassedPID",&isPassedPID);
		tin->SetBranchAddress("HGamEventInfoAuxDyn.isPassedBasic",&isPassedBasic);
		tin->SetBranchAddress("HGamEventInfoAuxDyn.isPassedIsolation",&isPassedIsolation);
		tin->SetBranchAddress("HGamEventInfoAuxDyn.isPassedRelPtCuts",&isPassedRelPtCuts);
		tin->SetBranchAddress("HGamEventInfoAuxDyn.isPassedMassCut",&isPassedMassCut);
		tin->SetBranchAddress("HGamEventInfoAuxDyn.isPassedIsolationLowHighMyy",&isPassedIsolationLowHighMyy);
		tin->SetBranchAddress("HGamEventInfoAuxDyn.isPassedRelPtCutsLowHighMyy",&isPassedRelPtCutsLowHighMyy);
		tin->SetBranchAddress("HGamEventInfoAuxDyn.isPassedLowHighMyy",&isPassedLowHighMyy);
		tin->SetBranchAddress("HGamEventInfoAuxDyn.isPassedIsolationExotic",&isPassedIsolationExotic);
		tin->SetBranchAddress("HGamEventInfoAuxDyn.isPassedlPtCutsExotic",&isPassedlPtCutsExotic);
		tin->SetBranchAddress("HGamEventInfoAuxDyn.isPassedExotic",&isPassedExotic);
		tin->SetBranchAddress("HGamEventInfoAuxDyn.m_yy",&m_yy);
		tin->SetBranchAddress("HGamEventInfoAuxDyn.crossSectionBRfilterEff",&crossSectionBRfilterEff);
		tin->SetBranchAddress("HGamEventInfoAuxDyn.vertexWeight",&vertexWeight);
		tin->SetBranchAddress("HGamEventInfoAuxDyn.weight",&Weight);
		tin->SetBranchAddress("EventInfoAuxDyn.mcEventWeights",&mcEventWeights);
		tin->SetBranchAddress("EventInfoAuxDyn.mcChannelNumber",&mcChannelNumber);
		tin->SetBranchAddress("HGamPhotonsAuxDyn.pt",&pt);
		tin->SetBranchAddress("HGamPhotonsAuxDyn.eta_s2",&eta_s2);
		tin->SetBranchAddress("HGamPhotonsAuxDyn.conversionType",&conversionType);

		tin->SetBranchStatus("*",0);
		tin->SetBranchStatus("HGamEventInfoAuxDyn.isPassedPreselection",1);
		tin->SetBranchStatus("HGamEventInfoAuxDyn.isPassedPID",1);
		tin->SetBranchStatus("HGamEventInfoAuxDyn.isPassedBasic",1);
		tin->SetBranchStatus("HGamEventInfoAuxDyn.isPassedIsolation",1);
		tin->SetBranchStatus("HGamEventInfoAuxDyn.isPassedRelPtCuts",1);
		tin->SetBranchStatus("HGamEventInfoAuxDyn.isPassedMassCut",1);
		tin->SetBranchStatus("HGamEventInfoAuxDyn.isPassedIsolationLowHighMyy",1);
		tin->SetBranchStatus("HGamEventInfoAuxDyn.isPassedRelPtCutsLowHighMyy",1);
		tin->SetBranchStatus("HGamEventInfoAuxDyn.isPassedLowHighMyy",1);
		tin->SetBranchStatus("HGamEventInfoAuxDyn.isPassedIsolationExotic",1);
		tin->SetBranchStatus("HGamEventInfoAuxDyn.isPassedlPtCutsExotic",1);
		tin->SetBranchStatus("HGamEventInfoAuxDyn.isPassedExotic",1);
		tin->SetBranchStatus("HGamEventInfoAuxDyn.m_yy",1);
		tin->SetBranchStatus("HGamEventInfoAuxDyn.crossSectionBRfilterEff",1);
		tin->SetBranchStatus("HGamEventInfoAuxDyn.vertexWeight",1);
		tin->SetBranchStatus("HGamEventInfoAuxDyn.weight",1);
		tin->SetBranchStatus("EventInfoAuxDyn.mcChannelNumber",1);
		tin->SetBranchStatus("EventInfoAuxDyn.mcEventWeights",1);
		tin->SetBranchStatus("HGamPhotonsAuxDyn.pt",1);
		tin->SetBranchStatus("HGamPhotonsAuxDyn.eta_s2",1);
		tin->SetBranchStatus("HGamPhotonsAuxDyn.conversionType",1);

		double sum_of_weight_tree = 0;
		for( int j=0; j<tin->GetEntries(); j++ ){
			tin->GetEntry(j);
			//sum_of_weight_tree += vertexWeight;
			//sum_of_weight_tree += Weight;
			sum_of_weight_tree += vertexWeight*mcEventWeights->at(0);
		}
		sum_of_weight_tree /= tin->GetEntries();
		for( int j=0; j<tin->GetEntries(); j++ ){
			tin->GetEntry(j);
			if( !(isPassedBasic&&isPassedPreselection&&isPassedPID&&isPassedlPtCutsExotic&&isPassedIsolationLowHighMyy) ) continue;
			int index1=-1, index2=-1;
			double pt1=0, pt2=0;
			for( size_t idx=0; idx<pt->size(); idx++ ){
				if( TMath::Abs(eta_s2->at(idx)) > 2.37 ) continue;
				if( pt->at(idx)>pt1 ){
					pt2 = pt1; index2 = index1;
					pt1 = pt->at(idx); index1 = idx;
				} else if( pt->at(idx)>pt2 ){
					pt2 = pt->at(idx); index2 = idx;
				}
			}
			if( index1<0 || index2<0 ) continue;
			bool Barrel1 = TMath::Abs(eta_s2->at(index1))<=1.37;
			bool Barrel2 = TMath::Abs(eta_s2->at(index2))<=1.37;
			bool Unconv1 = conversionType->at(index1)==0;
			bool Unconv2 = conversionType->at(index2)==0;
			bool isBB = Barrel1 && Barrel2;
			bool isBE = Barrel1 && !Barrel2;
			bool isEB = !Barrel1 && Barrel2;
			bool isEE = !Barrel1 && !Barrel2;
			bool isUU = Unconv1 && Unconv2;
			bool isUC = Unconv1 && !Unconv2;
			bool isCU = !Unconv1 && Unconv2;
			bool isCC = !Unconv1 && !Unconv2;

			bool isEta05 = TMath::Abs(eta_s2->at(index1))<=0.5 && TMath::Abs(eta_s2->at(index2))<=0.5;
			bool isEta06 = TMath::Abs(eta_s2->at(index1))<=0.6 && TMath::Abs(eta_s2->at(index2))<=0.6;
			bool isEta07 = TMath::Abs(eta_s2->at(index1))<=0.7 && TMath::Abs(eta_s2->at(index2))<=0.7;
			bool isEta08 = TMath::Abs(eta_s2->at(index1))<=0.8 && TMath::Abs(eta_s2->at(index2))<=0.8;
			bool isEta10 = TMath::Abs(eta_s2->at(index1))<=1.0 && TMath::Abs(eta_s2->at(index2))<=1.0;
			bool isEta12 = TMath::Abs(eta_s2->at(index1))<=1.2 && TMath::Abs(eta_s2->at(index2))<=1.2;

			bool isEPSC1 = isUU && TMath::Abs(eta_s2->at(index1))<=0.75 && TMath::Abs(eta_s2->at(index2))<=0.75;
			bool isEPSC2 = isUU && !(TMath::Abs(eta_s2->at(index1))<=0.75 && TMath::Abs(eta_s2->at(index2))<=0.75);
			bool isEPSC3 = !isUU && TMath::Abs(eta_s2->at(index1))<=0.75 && TMath::Abs(eta_s2->at(index2))<=0.75;
			bool isEPSC4 = isUU && !(TMath::Abs(eta_s2->at(index1))<=0.75 && TMath::Abs(eta_s2->at(index2))<=0.75) && (TMath::Abs(eta_s2->at(index1))<=1.3 || TMath::Abs(eta_s2->at(index1))>=1.75) && (TMath::Abs(eta_s2->at(index2))<=1.3 || TMath::Abs(eta_s2->at(index2))>=1.75);
			bool isEPSC5 = !(isEPSC1 || isEPSC2 || isEPSC3 || isEPSC4);
			bool isCenCen = isEPSC1 || isEPSC3;
			bool isnonCenCen = !isCenCen;
			bool isnonCenCennonEE = !isCenCen && !isEE;
			bool isTran = (TMath::Abs(eta_s2->at(index1))>1.30&&TMath::Abs(eta_s2->at(index1))<1.75) || (TMath::Abs(eta_s2->at(index2))>1.30&&TMath::Abs(eta_s2->at(index2))<1.75);
			bool isnonCenCennonTran = !isCenCen && !isTran;

			if( category=="BB" && !isBB ) continue;
			if( category=="nonBB" && isBB ) continue;
			if( category=="EE" && !isEE ) continue;
			if( category=="nonEE" && isEE ) continue;
			if( category=="BEEB" && !(isBE||isEB) ) continue;
			if( category=="UU" && !isUU ) continue;
			if( category=="nonUU" && isUU ) continue;
			if( category=="CC" && !isCC ) continue;
			if( category=="nonCC" && isCC ) continue;
			if( category=="UCCU" && !(isUC||isCU) ) continue;
			if( category=="EPSC1" && !isEPSC1 ) continue;
			if( category=="EPSC2" && !isEPSC2 ) continue;
			if( category=="EPSC3" && !isEPSC3 ) continue;
			if( category=="EPSC4" && !isEPSC4 ) continue;
			if( category=="EPSC5" && !isEPSC5 ) continue;
			if( category=="CenCen" && !isCenCen ) continue;
			if( category=="nonCenCen" && !isnonCenCen ) continue;
			if( category=="nonCenCennonEE" && !isnonCenCennonEE ) continue;
			if( category=="Tran" && !isTran ) continue;
			if( category=="nonCenCennonTran" && !isnonCenCennonTran ) continue;
			if( category=="Eta05" && !isEta05 ) continue;
			if( category=="Eta06" && !isEta06 ) continue;
			if( category=="Eta07" && !isEta07 ) continue;
			if( category=="Eta08" && !isEta08 ) continue;
			if( category=="Eta10" && !isEta10 ) continue;
			if( category=="Eta12" && !isEta12 ) continue;
			if( category=="nonEta05" && isEta05 ) continue;
			if( category=="nonEta06" && isEta06 ) continue;
			if( category=="nonEta07" && isEta07 ) continue;
			if( category=="nonEta08" && isEta08 ) continue;
			if( category=="nonEta10" && isEta10 ) continue;
			if( category=="nonEta12" && isEta12 ) continue;

			mass = m_yy/1000.;
			//weight = vertexWeight/sum_of_weight_tree;
			//weight = Weight/sum_of_weight_tree;
			weight = vertexWeight*mcEventWeights->at(0)/sum_of_weight_tree;
			datatree[i]->Fill();
		}
		fout->cd();
		datatree[i]->Write();

		fin->Close();
	}

	// Observables:
	RooRealVar v_mass("mass","mass",100,10000);
	RooRealVar v_weight("weight","weight",0,250);

	RooRealVar single_mean("single_mean","single_mean",100,10000);
	RooRealVar single_sigma("single_sigma","single_sigma",10,0,100);
	RooRealVar single_alphaLo("single_alphaLo","single_alphaLo",1.5,0,100);
	RooRealVar single_alphaHi("single_alphaHi","single_alphaHi",2.1,0,100);
	RooRealVar single_nLo("single_nLo","single_nLo",6.00);//5.9,0.,100);
	RooRealVar single_nHi("single_nHi","single_nHi",3.00);//2.353725,0.,100);

	HggTwoSidedCBPdf single_pdf( "single_pdf", "single_pdf", v_mass,
			single_mean, single_sigma, single_alphaLo, single_nLo, single_alphaHi, single_nHi );
	vector<double> fitted_mean(npoints);
	vector<double> fitted_sigma(npoints);
	vector<double> fitted_alphaLo(npoints);
	vector<double> fitted_alphaHi(npoints);
	vector<double> fitted_nLo(npoints);
	vector<double> fitted_nHi(npoints);
	vector<double> fitted_errmean(npoints);
	vector<double> fitted_errsigma(npoints);
	vector<double> fitted_erralphaLo(npoints);
	vector<double> fitted_erralphaHi(npoints);
	vector<double> fitted_errnLo(npoints);
	vector<double> fitted_errnHi(npoints);

	vector<RooPlot*> single_frame(npoints);
	const int nbin = 50;
	TCanvas* c1 = new TCanvas();
	c1->cd();
	//c1->SetLogy();

	// RooDataSets
	vector<RooDataSet*> data(npoints,nullptr);
	for( int i=0; i<npoints; i++ ){
		data[i] = new RooDataSet(Form("data%.0f",truthmass[i]), "", RooArgSet( v_mass, v_weight ), WeightVar( v_weight ), Import(*datatree[i]) ) ;

		v_mass.setMin((1-fitPercent)*truthmass[i]);
		v_mass.setMax((1+fitPercent)*truthmass[i]);
		//single_nLo.setVal(6);
		//single_nHi.setVal(3);
		single_mean.setVal(truthmass[i]);
		//single_sigma.setVal(1.93124+0.5927*(truthmass[i]-100)/100);
		//single_alphaLo.setVal(1.4);
		//single_alphaHi.setVal(2);
		for( int j=0; j<20; j++ )
			single_pdf.fitTo(*data[i]);

		v_mass.setMin((1-showPercent)*truthmass[i]);
		v_mass.setMax((1+showPercent)*truthmass[i]);
		single_frame[i] = v_mass.frame( Bins(nbin), Title(Form("Single_%.0f",truthmass[i])) );
		data[i]->plotOn(single_frame[i]);
		single_pdf.plotOn(single_frame[i]);

		single_frame[i]->Draw();
		c1->Print(Form("Individual_%.0f.png",truthmass[i]));
		fitted_mean[i] = single_mean.getVal();
		fitted_sigma[i] = single_sigma.getVal();
		fitted_alphaLo[i] = single_alphaLo.getVal();
		fitted_alphaHi[i] = single_alphaHi.getVal();
		fitted_nLo[i] = single_nLo.getVal();
		fitted_nHi[i] = single_nHi.getVal();
		fitted_errmean[i] = single_mean.getError();
		fitted_errsigma[i] = single_sigma.getError();
		fitted_erralphaLo[i] = single_alphaLo.getError();
		fitted_erralphaHi[i] = single_alphaHi.getError();
		fitted_errnLo[i] = single_nLo.getError();
		fitted_errnHi[i] = single_nHi.getError();

		v_mass.setMin(100);
		v_mass.setMax(10000);
	}

	RooRealVar a_muCB("a_muCB","a_muCB",-0.147889,-1.0,1.0);
	RooRealVar b_muCB("b_muCB","b_muCB",-0.0121526,-1.0,1.0);
	RooRealVar c_muCB("c_muCB","c_muCB",-0.00210331,-0.1,0.1);
	RooRealVar a_sigmaCB("a_sigmaCB","a_sigmaCB",2.04543,0.5,8.0);
	RooRealVar b_sigmaCB("b_sigmaCB","b_sigmaCB",0.577245,0.1,2.0);
	RooRealVar c_sigmaCB("c_sigmaCB","c_sigmaCB",0.0021951,-0.1,2.0);
	RooRealVar a_alphaCBLo("a_alphaCBLo","a_alphaCBLo",1.47504,0.0,4.0);
	RooRealVar b_alphaCBLo("b_alphaCBLo","b_alphaCBLo",-0.00420319,-1.0,1.0);
	RooRealVar c_alphaCBLo("c_alphaCBLo","c_alphaCBLo",5.62961e-05,-0.1,0.1);
	//RooRealVar nCBLo("nCBLo","nCBLo",2.50,0.,10.);
	RooRealVar a_nCBLo("a_nCBLo","a_nCBLo",6.00);//4.547,0.,10.);
	//RooRealVar b_nCBLo("b_nCBLo","b_nCBLo",0);//-0.0453188);//,-0.1,10.);
	RooRealVar b_nCBLo("b_nCBLo","b_nCBLo",0);//0.0453188,-1.0,10.);
	RooRealVar a_alphaCBHi("a_alphaCBHi","a_alphaCBHi",2.19685,0.0,5.0);
	RooRealVar b_alphaCBHi("b_alphaCBHi","b_alphaCBHi",-0.0144501,-1.0,0.0);
	RooRealVar c_alphaCBHi("c_alphaCBHi","c_alphaCBHi",0.000348122,0.0,0.1);
	//RooRealVar nCBHi("nCBHi","nCBHi",1.80,0.,10.);
	RooRealVar a_nCBHi("a_nCBHi","a_nCBHi",3.00);//1.56931,0.,10.);
	RooRealVar b_nCBHi("b_nCBHi","b_nCBHi",0);//0.0589371,-1.,10.);

	vector<RooFormulaVar*> muCB(npoints);
	vector<RooFormulaVar*> sigmaCB(npoints);
	vector<RooFormulaVar*> alphaCBLo(npoints);
	vector<RooFormulaVar*> alphaCBHi(npoints);
	vector<RooFormulaVar*> nCBLo(npoints);
	vector<RooFormulaVar*> nCBHi(npoints);
	vector<HggTwoSidedCBPdf*> sigPdf(npoints);

	for( int i=0; i<npoints; i++ ){
		muCB[i] = new RooFormulaVar( 
				Form("muCB_%.0f",truthmass[i]), 
				Form("@0+@1*%f+@2*%f*%f+%f",(truthmass[i]-100)/100.,(truthmass[i]-100)/100.,(truthmass[i]-100)/100.,truthmass[i]),
				RooArgSet(a_muCB,b_muCB,c_muCB) );
				//Form("@0+@1*%f+%f",(truthmass[i]-100)/100.,truthmass[i]),
				//RooArgSet(a_muCB,b_muCB) );
		sigmaCB[i] = new RooFormulaVar( 
				Form("sigmaCB_%.0f",truthmass[i]), 
				Form("@0+@1*%f+@2*%f*%f",(truthmass[i]-100)/100.,(truthmass[i]-100)/100.,(truthmass[i]-100)/100.),
				//RooArgSet(a_sigmaCB,b_sigmaCB,c_sigmaCB) );
				//Form("@0+@1*%f",(truthmass[i]-100)/100.),
				//RooArgSet(a_sigmaCB,b_sigmaCB) );
				RooArgSet(a_sigmaCB,b_sigmaCB,c_sigmaCB) );
		alphaCBLo[i] = new RooFormulaVar( 
				Form("alphaCBLo_%.0f",truthmass[i]), 
				//Form("@0+@1*%f",(truthmass[i]-100)/100.),
				//Form("exp(@0+@1*%f)",(truthmass[i]-100)/100.),
				//Form("@0+@1/(%f+@2)",(truthmass[i]-100)/100.),
				Form("@0+@1*%f+@2*%f*%f",(truthmass[i]-100)/100.,(truthmass[i]-100)/100.,(truthmass[i]-100)/100.),
				//RooArgSet(a_alphaCBLo,b_alphaCBLo) );
				RooArgSet(a_alphaCBLo,b_alphaCBLo,c_alphaCBLo) );
		alphaCBHi[i] = new RooFormulaVar( 
				Form("alphaCBHi_%.0f",truthmass[i]), 
				//Form("@0+@1*%f",(truthmass[i]-100)/100.),
				//Form("exp(@0+@1*%f)",(truthmass[i]-100)/100.),
				//Form("@0+@1/(%f+@2)",(truthmass[i]-100)/100.),
				Form("@0+@1*%f+@2*%f*%f",(truthmass[i]-100)/100.,(truthmass[i]-100)/100.,(truthmass[i]-100)/100.),
				//RooArgSet(a_alphaCBHi,b_alphaCBHi) );
				RooArgSet(a_alphaCBHi,b_alphaCBHi,c_alphaCBHi) );
		nCBLo[i] = new RooFormulaVar( 
				Form("nCBLo_%.0f",truthmass[i]), 
				Form("@0+@1*%f",(truthmass[i]-100)/100.),
				RooArgSet(a_nCBLo,b_nCBLo) );
		nCBHi[i] = new RooFormulaVar( 
				Form("nCBHi_%.0f",truthmass[i]), 
				Form("@0+@1*%f",(truthmass[i]-100)/100.),
				RooArgSet(a_nCBHi,b_nCBHi) );
		sigPdf[i] = new HggTwoSidedCBPdf(
				Form("sigPdf_%.0f",truthmass[i]), 
				Form("sigPdf_%.0f",truthmass[i]), 
				v_mass, *muCB[i], *sigmaCB[i], *alphaCBLo[i], *nCBLo[i], *alphaCBHi[i], *nCBHi[i] );
				//v_mass, *muCB[i], *sigmaCB[i], *alphaCBLo[i], nCBLo, *alphaCBHi[i], nCBHi );
	}

	RooCategory sample("sample", "sample");
	map<string,RooDataSet*> dataMap;
	for( int i=0; i<npoints; i++ ){
		TString massname = Form("m_%.0f",truthmass[i]);
		sample.defineType(massname);
		dataMap[(string)massname.Data()] = data[i];
	}
	RooDataSet combData("combData", "combData", RooArgSet(v_mass, v_weight), WeightVar(v_weight), Index(sample), Import(dataMap));

	RooSimultaneous simPdf("simPdf","simultaneous pdf",sample);
	for( int i=0; i<npoints; i++ )
		simPdf.addPdf( *sigPdf[i], Form("m_%.0f",truthmass[i]));

	vector<RooPlot*> frame(npoints);
	//int nbin = 50;
	//TCanvas* c1 = new TCanvas();
	//c1->cd();
	//c1->SetLogy();
	for( int i=0; i<npoints; i++ ){
		frame[i] = v_mass.frame(Bins(nbin), Title(Form("Mass_%.0f",truthmass[i])),Range(truthmass[i]*(1-showPercent),truthmass[i]*(1+showPercent)) );
		combData.plotOn( frame[i],Cut(Form("sample==sample::m_%.0f",truthmass[i])) );
		simPdf.plotOn( frame[i],Slice(sample,Form("m_%.0f",truthmass[i])),ProjWData(sample,combData) );
		frame[i]->GetXaxis()->SetTitle("m_{#gamma#gamma}[GeV]");
		frame[i]->Draw();
		c1->Print(Form("beforeFit_%.0f.png",truthmass[i]));
	}

	for( int i=0; i<2; i++ )
		simPdf.fitTo(combData);

	TPad *pad1 = new TPad( "pad1", "pad1", 0.00, 0.33, 1.00, 1.00 );
	TPad *pad2 = new TPad( "pad2", "pad2", 0.00, 0.00, 1.00, 0.33 );
	pad1->SetBottomMargin(0.00001);
	pad1->SetBorderMode(0);
	//pad1->SetLogy();
	pad2->SetTopMargin(0.00001);
	pad2->SetBottomMargin(0.4);
	pad2->SetBorderMode(0);
	c1->cd();
	pad1->Draw();
	pad2->Draw();

	vector<RooPlot*> postframe(npoints);

	for( int i=0; i<npoints; i++ ){
		v_mass.setMin(100);
		v_mass.setMax(10000);
		postframe[i] = v_mass.frame(Bins(nbin), Title(Form("Mass_%.0f PostFit",truthmass[i])),Range(truthmass[i]*(1-showPercent),truthmass[i]*(1+showPercent)) );
		combData.plotOn( postframe[i],Cut(Form("sample==sample::m_%.0f",truthmass[i])) );
		simPdf.plotOn( postframe[i],Slice(sample,Form("m_%.0f",truthmass[i])),ProjWData(sample,combData) );
		postframe[i]->GetXaxis()->SetTitle("m_{#gamma#gamma}[GeV]");
		pad1->cd();
		postframe[i]->Draw();
		pad2->cd();
		v_mass.setMin(truthmass[i]*(1-showPercent));
		v_mass.setMax(truthmass[i]*(1+showPercent));
		TH1F* medianHist = new TH1F(Form("median_%.0f",truthmass[i]), "", nbin, truthmass[i]*(1-showPercent), truthmass[i]*(1+showPercent));
		for (int i_b = 1; i_b <= nbin; i_b++) medianHist->SetBinContent(i_b,1.0);
		medianHist->SetLineColor(kRed);
		medianHist->SetLineWidth(2);
		medianHist->GetXaxis()->SetTitle("m_{#gamma#gamma}[GeV]");
		medianHist->GetYaxis()->SetTitle("MC / Fit");
		medianHist->GetXaxis()->SetTitleOffset(0.95);
		medianHist->GetYaxis()->SetTitleOffset(0.7);
		medianHist->GetXaxis()->SetTitleSize(0.1);
		medianHist->GetYaxis()->SetTitleSize(0.1);
		medianHist->GetXaxis()->SetLabelSize(0.1);
		medianHist->GetYaxis()->SetLabelSize(0.1);
		medianHist->GetYaxis()->SetRangeUser(-0.2, 2.2);
		medianHist->GetYaxis()->SetNdivisions(5);
		medianHist->Draw();
		TGraphErrors* ge = plotDivision(data[i],sigPdf[i],&v_mass,nbin);
		ge->Draw("EPSAME");
		c1->Print(Form("afterFit_%.0f.png",truthmass[i]));
		c1->Print(Form("afterFit_%.0f.eps",truthmass[i]));
	}

	c1->SetLogy(false);
	TGraph* g_mean = new TGraph(npoints);
	TGraph* g_sigma = new TGraph(npoints);
	TGraph* g_alphaLo = new TGraph(npoints);
	TGraph* g_alphaHi = new TGraph(npoints);
	TGraph* g_nLo = new TGraph(npoints);
	TGraph* g_nHi = new TGraph(npoints);
	for( int i=0; i<npoints; i++ ){
		g_mean->SetPoint(i,truthmass[i],fitted_mean[i]-truthmass[i]);
		g_sigma->SetPoint(i,truthmass[i],fitted_sigma[i]);
		g_alphaLo->SetPoint(i,truthmass[i],fitted_alphaLo[i]);
		g_alphaHi->SetPoint(i,truthmass[i],fitted_alphaHi[i]);
		g_nLo->SetPoint(i,truthmass[i],fitted_nLo[i]);
		g_nHi->SetPoint(i,truthmass[i],fitted_nHi[i]);
	}

	c1->cd();
	g_mean->GetXaxis()->SetTitle("m_{X} [GeV]");
	g_mean->GetYaxis()->SetTitle("#Deltam [GeV]");
	g_mean->Draw("AL*");
	TF1* fmuCB = new TF1("fmuCB", Form("%f+%f*(x-100)/100+%f*(x-100)/100*(x-100)/100",a_muCB.getVal(),b_muCB.getVal(),c_muCB.getVal()), 0.9*truthmass[0],1.05*truthmass[truthmass.size()-1]);
	fmuCB->Draw("same");
	c1->Print("mean.png");
	g_sigma->GetXaxis()->SetTitle("m_{X} [GeV]");
	g_sigma->GetYaxis()->SetTitle("#sigma_{CB} [GeV]");
	g_sigma->Draw("AL*");
	TF1* fsigmaCB = new TF1("fsigmaCB", Form("%f+%f*(x-100)/100+%f*(x-100)/100*(x-100)/100",a_sigmaCB.getVal(),b_sigmaCB.getVal(),c_sigmaCB.getVal()), 0.9*truthmass[0],1.05*truthmass[truthmass.size()-1]);
	fsigmaCB->Draw("same");
	c1->Print("sigma.png");
	g_alphaLo->GetXaxis()->SetTitle("m_{X} [GeV]");
	g_alphaLo->GetYaxis()->SetTitle("#alpha_{CB}^{lo}");
	g_alphaLo->Draw("AL*");
	TF1* falphaCBLo = new TF1("falphaCBLo", Form("%f+%f*(x-100)/100+%f*(x-100)/100*(x-100)/100",a_alphaCBLo.getVal(),b_alphaCBLo.getVal(),c_alphaCBLo.getVal()), 0.9*truthmass[0],1.05*truthmass[truthmass.size()-1]);
	falphaCBLo->Draw("same");
	c1->Print("alphaLo.png");
	g_alphaHi->GetXaxis()->SetTitle("m_{X} [GeV]");
	g_alphaHi->GetYaxis()->SetTitle("#alpha_{CB}^{hi}");
	g_alphaHi->Draw("AL*");
	TF1* falphaCBHi = new TF1("falphaCBHi", Form("%f+%f*(x-100)/100+%f*(x-100)/100*(x-100)/100",a_alphaCBHi.getVal(),b_alphaCBHi.getVal(),c_alphaCBHi.getVal()), 0.9*truthmass[0],1.05*truthmass[truthmass.size()-1]);
	falphaCBHi->Draw("same");
	c1->Print("alphaHi.png");
	g_nLo->GetXaxis()->SetTitle("m_{X} [GeV]");
	g_nLo->GetYaxis()->SetTitle("n_{CB}^{lo}");
	g_nLo->Draw("AL*");
	c1->Print("nLo.png");
	g_nHi->GetXaxis()->SetTitle("m_{X} [GeV]");
	g_nHi->GetYaxis()->SetTitle("n_{CB}^{hi}");
	g_nHi->Draw("AL*");
	c1->Print("nHi.png");
	
	ofstream output("output.txt");
	for( int i=0; i<npoints; i++ )
		output<<truthmass[i]<<" "<<fitted_mean[i]<<" "<<fitted_sigma[i]<<" "<<fitted_alphaLo[i]<<" "<<fitted_alphaHi[i]<<" "<<fitted_nLo[i]<<" "<<fitted_nHi[i]<<endl;
	ofstream outputerr("outputerr.txt");
	for( int i=0; i<npoints; i++ )
		outputerr<<truthmass[i]<<" "<<fitted_mean[i]<<" "<<fitted_errmean[i]<<" "<<fitted_sigma[i]<<" "<<fitted_errsigma[i]<<" "<<fitted_alphaLo[i]<<" "<<fitted_erralphaLo[i]<<" "<<fitted_alphaHi[i]<<" "<<fitted_erralphaHi[i]<<" "<<fitted_nLo[i]<<" "<<fitted_errnLo[i]<<" "<<fitted_nHi[i]<<" "<<fitted_errnHi[i]<<endl;

	cout<<a_muCB.GetName()<<" : "<<a_muCB.getVal()<<endl;
	cout<<b_muCB.GetName()<<" : "<<b_muCB.getVal()<<endl;
	cout<<c_muCB.GetName()<<" : "<<c_muCB.getVal()<<endl;
	cout<<a_sigmaCB.GetName()<<" : "<<a_sigmaCB.getVal()<<endl;
	cout<<b_sigmaCB.GetName()<<" : "<<b_sigmaCB.getVal()<<endl;
	cout<<c_sigmaCB.GetName()<<" : "<<c_sigmaCB.getVal()<<endl;
	cout<<a_alphaCBLo.GetName()<<" : "<<a_alphaCBLo.getVal()<<endl;
	cout<<b_alphaCBLo.GetName()<<" : "<<b_alphaCBLo.getVal()<<endl;
	cout<<c_alphaCBLo.GetName()<<" : "<<c_alphaCBLo.getVal()<<endl;
	//cout<<nCBLo.GetName()<<" : "<<nCBLo.getVal()<<endl;
	cout<<a_nCBLo.GetName()<<" : "<<a_nCBLo.getVal()<<endl;
	cout<<b_nCBLo.GetName()<<" : "<<b_nCBLo.getVal()<<endl;
	cout<<a_alphaCBHi.GetName()<<" : "<<a_alphaCBHi.getVal()<<endl;
	cout<<b_alphaCBHi.GetName()<<" : "<<b_alphaCBHi.getVal()<<endl;
	cout<<c_alphaCBHi.GetName()<<" : "<<c_alphaCBHi.getVal()<<endl;
	//cout<<nCBHi.GetName()<<" : "<<nCBHi.getVal()<<endl;
	cout<<a_nCBHi.GetName()<<" : "<<a_nCBHi.getVal()<<endl;
	cout<<b_nCBHi.GetName()<<" : "<<b_nCBHi.getVal()<<endl;

	ofstream outpar("outpar.txt");
	outpar<<a_muCB.GetName()<<" : "<<a_muCB.getVal()<<endl;
	outpar<<b_muCB.GetName()<<" : "<<b_muCB.getVal()<<endl;
	outpar<<c_muCB.GetName()<<" : "<<c_muCB.getVal()<<endl;
	outpar<<a_sigmaCB.GetName()<<" : "<<a_sigmaCB.getVal()<<endl;
	outpar<<b_sigmaCB.GetName()<<" : "<<b_sigmaCB.getVal()<<endl;
	outpar<<c_sigmaCB.GetName()<<" : "<<c_sigmaCB.getVal()<<endl;
	outpar<<a_alphaCBLo.GetName()<<" : "<<a_alphaCBLo.getVal()<<endl;
	outpar<<b_alphaCBLo.GetName()<<" : "<<b_alphaCBLo.getVal()<<endl;
	outpar<<c_alphaCBLo.GetName()<<" : "<<c_alphaCBLo.getVal()<<endl;
	outpar<<a_nCBLo.GetName()<<" : "<<a_nCBLo.getVal()<<endl;
	outpar<<a_alphaCBHi.GetName()<<" : "<<a_alphaCBHi.getVal()<<endl;
	outpar<<b_alphaCBHi.GetName()<<" : "<<b_alphaCBHi.getVal()<<endl;
	outpar<<c_alphaCBHi.GetName()<<" : "<<c_alphaCBHi.getVal()<<endl;
	outpar<<a_nCBHi.GetName()<<" : "<<a_nCBHi.getVal()<<endl;

	for( int i=0; i<npoints; i++ ){
		cout<<truthmass[i]<<" : "<<muCB[i]->getVal()<<" "<<sigmaCB[i]->getVal()<<" "<<alphaCBLo[i]->getVal()<<" "<<nCBLo[i]->getVal()<<" "<<alphaCBHi[i]->getVal()<<" "<<nCBHi[i]->getVal()<<endl;
	}

	return 0;
}
