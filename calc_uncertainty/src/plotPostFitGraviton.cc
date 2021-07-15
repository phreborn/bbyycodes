#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"
#include "titleList.hh"

using namespace std;
using namespace RooFit;
using namespace RooStats;

const double epsilon=1e-4;

TGraphErrors* plotSubtraction(RooAbsData *data, RooAbsPdf *pdf, 
			      RooRealVar *observable, double xBins,
			      double &chi2Prob) {
  double minOrigin = observable->getMin();
  double maxOrigin = observable->getMax();
  //double nEvents = data->sumEntries();
  double nEvents = data->sumEntries(Form("%s>%f&&%s<%f",
					 observable->GetName(), minOrigin,
					 observable->GetName(), maxOrigin));
  TH1F *originHist
    = (TH1F*)data->createHistogram("dataSub", *observable,
				   RooFit::Binning(xBins,minOrigin,maxOrigin));
  TGraphErrors *result = new TGraphErrors();
  double increment = (maxOrigin - minOrigin) / ((double)xBins);
  
  RooAbsReal* intTot
    = (RooAbsReal*)pdf->createIntegral(RooArgSet(*observable),
				       RooFit::NormSet(*observable), 
				       RooFit::Range("fullRange"));
  double valTot = intTot->getVal();
  
  int pointIndex = 0;
  for (double i_m = minOrigin; i_m < maxOrigin; i_m += increment) {
    observable->setRange(Form("range%2.2f",i_m), i_m, (i_m+increment));
    RooAbsReal* intCurr
      = (RooAbsReal*)pdf->createIntegral(RooArgSet(*observable), 
					 RooFit::NormSet(*observable), 
					 RooFit::Range(Form("range%2.2f",i_m)));
    double valCurr = intCurr->getVal();
    double currMass = i_m + (0.5*increment);
    double currPdfWeight = nEvents * (valCurr / valTot);
    TString varName = observable->GetName();
    double currDataWeight = data->sumEntries(Form("%s>%f&&%s<%f",varName.Data(),
						  i_m,varName.Data(),
						  (i_m+increment)));
    double currWeight = currDataWeight - currPdfWeight;
    double currError = sqrt(currDataWeight);//originHist->GetBinError(pointIndex+1);

    // cout<<currWeight<<" "<<currError<<endl;
    if(currWeight>epsilon&&currError>epsilon){
      result->SetPoint(pointIndex, currMass, currWeight);
      result->SetPointError(pointIndex, 0.0, currError);
    }
    pointIndex++;
  }
  observable->setMin(minOrigin);
  observable->setMax(maxOrigin);
  delete originHist;
  return result;
}

int minimize(RooAbsReal* fcn){
  int printLevel = ROOT::Math::MinimizerOptions::DefaultPrintLevel();
  RooFit::MsgLevel msglevel = RooMsgService::instance().globalKillBelow();
  if (printLevel < 0) RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);

  int strat = ROOT::Math::MinimizerOptions::DefaultStrategy();
  RooMinimizer minim(*fcn);
  minim.setStrategy(strat);
  minim.setPrintLevel(printLevel);
  minim.setProfile();
  minim.setEps(1);
  minim.optimizeConst(2);
  
  int status = minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());
  return status;
}

int main(int argc, char** argv)
{
  ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit2");
  ROOT::Math::MinimizerOptions::SetDefaultStrategy(0);
  ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(1);

  TString jobname=argv[1];

  TString inputFileName=argv[2];

  TString config1=argv[3];
  TString config2=argv[4];

  TString config3=argv[5];


  map<TString,TString> title=createTitleList();
  
  vector<TString> config1Arr=CommonFunc::SplitString(config1,'=');
  vector<TString> config2Arr=CommonFunc::SplitString(config2,'=');
  vector<TString> config3Arr=CommonFunc::SplitString(config3,',');
  
  TString var1Name=config1Arr[0], var2Name=config2Arr[0];
  double var1Value=config1Arr[1].Atof(), var2Value=config2Arr[1].Atof();

  double xmin=config3Arr[0].Atof(), xmax=config3Arr[1].Atof();
  int nbin=config3Arr[2].Atoi();

  CommonFunc::SetAtlasStyle();

  TString wname="combWS", mname="ModelConfig", dname="combData";
  
  TFile* f = TFile::Open(inputFileName);
  RooWorkspace* w = (RooWorkspace*)(f->Get(wname));
  RooStats::ModelConfig* mc = (RooStats::ModelConfig*)(w->obj(mname));
  //RooDataSet* m_data = w->data("obsData");
  RooDataSet* m_data = (RooDataSet*)w->data(dname);
  RooSimultaneous* m_pdf = (RooSimultaneous*)mc->GetPdf();

  RooAbsCategoryLValue*  m_cat = (RooAbsCategoryLValue*)&m_pdf->indexCat();
  int numChannels = m_cat->numBins(0);

  TList* m_dataList = m_data->split( *m_cat, true );

  system("mkdir -vp fig/"+jobname);
  
  std::cout << "\t~~~~~~~~Begin Summary~~~~~~~~" << std::endl;
  std::cout << "\tThere are " << numChannels << " sub channels:" << std::endl;

  w->loadSnapshot("ucmles");
  w->var(var1Name)->setRange(0,10000);
  w->var(var2Name)->setRange(0,10000);
  w->var(var1Name)->setVal(var1Value);
  w->var(var1Name)->setConstant(true);
  w->var(var2Name)->setVal(var2Value);
  w->var(var2Name)->setConstant(true);
  w->var("xs")->setConstant(false);
  w->var("xs")->setRange(0,10000);
  w->var("xs")->setVal(10);
  cout<<"okay here"<<endl;
  unique_ptr<RooAbsReal> nll(m_pdf->createNLL(*m_data, Constrain(*mc->GetNuisanceParameters()), GlobalObservables(*mc->GetGlobalObservables())));
  nll->enableOffsetting(true);
  minimize(nll.get());
  
  for ( int i= 0; i < numChannels; i++ ) {
    m_cat->setBin(i);
    TString channelname=m_cat->getLabel();
    
    RooAbsPdf* pdfi = m_pdf->getPdf(m_cat->getLabel());
    RooDataSet* datai = ( RooDataSet* )( m_dataList->At( i ) );
    std::cout << "\t\tIndex: " << i << ", Pdf: " << pdfi->GetName() << ", Data: " << datai->GetName()  << ", SumEntries: " << datai->sumEntries() << " NumEntries: "<< datai->numEntries() <<std::endl;
    TCanvas *c=new TCanvas(Form("c%d",i),channelname,800,600);
    TPad pad1("pad1", "pad1", 0.00, 0.33, 1.00, 1.00);
    TPad pad2("pad2", "pad2", 0.00, 0.00, 1.00, 0.33);
    pad1.SetBottomMargin(0.00001);
    pad1.SetBorderMode(0);
    pad2.SetTopMargin(0.00001);
    pad2.SetBottomMargin(0.4);
    pad2.SetBorderMode(0);
    c->cd();
    pad1.Draw();
    pad2.Draw();
    pad1.cd();
    
    TH1F *hframe=new TH1F("hframe","", 10000, xmin, xmax);
    hframe->SetMinimum(0.1);
    hframe->SetMaximum(8e3);

    hframe->GetXaxis()->SetTitle(title[var1Name]);

    hframe->SetLineWidth(0);
    hframe->GetYaxis()->SetTitleSize(0.07);
    hframe->GetYaxis()->SetTitleOffset(0.9);
    hframe->GetYaxis()->SetTitle(Form("Events / %.1f GeV", (xmax-xmin)/double(nbin)));
    hframe->Draw();
    
    RooRealVar *x=(RooRealVar*)pdfi->getObservables(datai)->first();
    x->setRange(xmin,xmax);
    
    RooPlot *frame=x->frame();
    frame->GetXaxis()->SetTitle("m_X [GeV]");
    datai->plotOn(frame, Binning(nbin), DataError(RooAbsData::Poisson));
    pdfi->plotOn(frame,LineColor(kMagenta));
    pdfi->plotOn(frame,Components("pdf_background_inclusive_13TeV"),LineColor(kBlue));
    pdfi->plotOn(frame,Components("pdf_signal_inclusive_13TeV"),LineColor(kRed));

    double x1, y1, x2, y2;
    CommonFunc::GetX1Y1X2Y2(&pad1,x1,y1,x2,y2);

    vector<TString> pavetext;
    pavetext.push_back("#bf{#it{ATLAS}} internal");
    pavetext.push_back("#sqrt{#it{s}} = 13 TeV, 3.2 fb^{-1}");
    pavetext.push_back(Form("%s=%.2f, %s=%.2f", title[var1Name].Data(), var1Value, title[var2Name].Data(), var2Value));
    TPaveText* text=CommonFunc::CreatePaveText(x2-0.5,y2-0.3,x2-0.03,y2-0.05,pavetext,0.06);
    
    frame->Draw("same");
    text->Draw("same");
    pad1.SetLogy();
    pad2.cd();

    TH1D hframe2("hframe2","hframe2",10000,xmin,xmax);
    hframe2.SetLineWidth(0);
    hframe2.GetXaxis()->SetTitle("m_{X} [GeV]");
    hframe2.GetXaxis()->SetTitleOffset(1);
    hframe2.GetYaxis()->SetTitleOffset(0.5);
    hframe2.GetXaxis()->SetTitleSize(0.15);
    hframe2.GetYaxis()->SetTitleSize(0.12);
    hframe2.GetXaxis()->SetLabelSize(0.12);
    hframe2.GetYaxis()->SetLabelSize(0.12);
    hframe2.GetYaxis()->SetNdivisions(205);
  
    hframe2.GetYaxis()->SetTitle("Data - fit");

    // CommonFunc::DrawConstantLine(&pad2, 0.5,xmin,xmax,kRed,2,2);
    // CommonFunc::DrawConstantLine(&pad2, -0.5,xmin,xmax,kRed,2,2);
    
    double currChi2Prob=0;
    w->var("xs")->setVal(0);
    TGraphErrors *subtraction=plotSubtraction(datai, pdfi, x, nbin, currChi2Prob);
    hframe2.SetMinimum(-10);
    hframe2.SetMaximum(30);
    hframe2.Draw();
    subtraction->Draw("EPSAME");
    CommonFunc::DrawConstantLine(&pad2, 0,  xmin,xmax,kRed,3,2);
    
    TString outputCanvasName="fig/"+jobname+Form("/plot_%.2f_%.2f",var1Value,var2Value);
    CommonFunc::PrintCanvas(c,outputCanvasName);
  }
  std::cout << "\t~~~~~~~~~End Summary~~~~~~~~~" << std::endl;
}

