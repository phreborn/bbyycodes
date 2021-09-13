#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"
#include "titleList.hh"

using namespace std;
using namespace RooFit;
using namespace RooStats;

int minimize(RooAbsReal* fcn)
{
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
  ROOT::Math::MinimizerOptions::SetDefaultStrategy(1);
  ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(0);

  TString jobname=argv[1];

  TString inputFileName=argv[2];

  TString config1=argv[3];
  TString config2=argv[4];

  TString option=argv[5];

  map<TString,TString> title=createTitleList();
  
  vector<TString> config1Arr=CommonFunc::SplitString(config1,'=');
  vector<TString> config2Arr=CommonFunc::SplitString(config2,'=');
  
  TString var1Name=config1Arr[0], var2Name=config2Arr[0];
  double var1Value=config1Arr[1].Atof(), var2Value=config2Arr[1].Atof();
  
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

  unique_ptr<RooAbsReal> nll(m_pdf->createNLL(*m_data, Constrain(*mc->GetNuisanceParameters()), GlobalObservables(*mc->GetGlobalObservables())));
  nll->enableOffsetting(true);
  // minimize(nll.get());
  
  for ( int i= 0; i < numChannels; i++ ) {
    m_cat->setBin(i);
    TString channelname=m_cat->getLabel();
    
    RooAbsPdf* pdfi = m_pdf->getPdf(m_cat->getLabel());
    RooDataSet* datai = ( RooDataSet* )( m_dataList->At( i ) );
    std::cout << "\t\tIndex: " << i << ", Pdf: " << pdfi->GetName() << ", Data: " << datai->GetName()  << ", SumEntries: " << datai->sumEntries() << " NumEntries: "<< datai->numEntries() <<std::endl;
    TCanvas *c=new TCanvas(Form("c%d",i),channelname,800,600);
    TH1F *hframe=new TH1F("hframe","", 10000, 150, 2000);
    hframe->SetMinimum(0.1);
    hframe->SetMaximum(5e4);
    // hframe->SetMaximum(1.2e4);
    // hframe->Draw();
    hframe->GetXaxis()->SetTitle(title[var1Name]);
    // hframe->GetYaxis()->SetTitle("Events / 50 GeV");
    hframe->SetLineWidth(0);
    RooRealVar *x=(RooRealVar*)pdfi->getObservables(datai)->first();
    // x->setRange(150, 1750);
    
    RooPlot *frame=x->frame();
    frame->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
    frame->GetXaxis()->SetRangeUser(150, 500);
    // datai->plotOn(frame, Binning(47), DataError(RooAbsData::Poisson));
    // pdfi->plotOn(frame,LineColor(kRed));

    // pdfi->plotOn(frame,Components("pdf_background_inclusive_13TeV"),LineColor(kBlue));
    pdfi->plotOn(frame,Components("pdf_signal_inclusive_13TeV"),LineColor(kRed));

    double x1, y1, x2, y2;
    CommonFunc::GetX1Y1X2Y2(c,x1,y1,x2,y2);

    vector<TString> pavetext;
    pavetext.push_back("#bf{#it{ATLAS}} internal");
    pavetext.push_back("#sqrt{#it{s}} = 13 TeV, 3.2 fb^{-1}");
    pavetext.push_back(Form("%s=%.2f, %s=%.2f", title[var1Name].Data(), var1Value, title[var2Name].Data(), var2Value));
    TPaveText* text=CommonFunc::CreatePaveText(x2-0.5,y2-0.3,x2-0.03,y2-0.05,pavetext,0.045);
    
    c->cd();
    frame->Draw();
    text->Draw("same");
    TString outputCanvasName="fig/"+jobname+Form("/plot_%.2f_%.2f",var1Value,var2Value);
    if(option.Contains("logy")){
      outputCanvasName+="_logy";
      c->SetLogy();
    }

    CommonFunc::PrintCanvas(c,outputCanvasName);
  }
  std::cout << "\t~~~~~~~~~End Summary~~~~~~~~~" << std::endl;
}

