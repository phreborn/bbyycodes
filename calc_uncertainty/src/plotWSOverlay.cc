#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"
#include "statistics.hh"
#include "ToolsSignificanceHist.h"

using namespace std;
using namespace RooFit;
using namespace RooStats;
using namespace CommonFunc;

int main( int argc, char** argv ){
  if( argc<5 ){
    cout<<"Usage: "<<argv[0]<<" input_files what_to_be_plotted"<<endl;
    exit(0);
  }
  SetAtlasStyle();

  TFile* fin1 = TFile::Open(argv[1]);
  RooWorkspace* w1 = dynamic_cast<RooWorkspace*>(fin1->Get("combWS"));
  
  TFile* fin2 = TFile::Open(argv[2]);
  RooWorkspace* w2 = dynamic_cast<RooWorkspace*>(fin2->Get("combWS"));

  TFile* fin3 = TFile::Open(argv[3]);
  RooWorkspace* w3 = dynamic_cast<RooWorkspace*>(fin3->Get("combWS"));

  TFile* fin4 = TFile::Open(argv[4]);
  RooWorkspace* w4 = dynamic_cast<RooWorkspace*>(fin4->Get("combWS"));

  TString option=argv[5];

  TString pdfPrefix="";
  double yield1=0, yield2=0, yield3=0, yield4=0;
  
  for(int i=0;i<argc;i++) cout<<argv[i]<<endl;
  
  ModelConfig *mc1=(ModelConfig*)w1->obj("ModelConfig");
  RooSimultaneous *pdf1=(RooSimultaneous*)mc1->GetPdf();
  RooAbsCategoryLValue *cat1=(RooAbsCategoryLValue*)&pdf1->indexCat();
  cat1->setBin(0);
  TString channelname1=cat1->getLabel();

  ModelConfig *mc2=(ModelConfig*)w2->obj("ModelConfig");
  RooSimultaneous *pdf2=(RooSimultaneous*)mc2->GetPdf();
  RooAbsCategoryLValue *cat2=(RooAbsCategoryLValue*)&pdf2->indexCat();
  cat2->setBin(0);
  TString channelname2=cat2->getLabel();

  ModelConfig *mc3=(ModelConfig*)w3->obj("ModelConfig");
  RooSimultaneous *pdf3=(RooSimultaneous*)mc3->GetPdf();
  RooAbsCategoryLValue *cat3=(RooAbsCategoryLValue*)&pdf3->indexCat();
  cat3->setBin(0);
  TString channelname3=cat3->getLabel();

  ModelConfig *mc4=(ModelConfig*)w4->obj("ModelConfig");
  RooSimultaneous *pdf4=(RooSimultaneous*)mc4->GetPdf();
  RooAbsCategoryLValue *cat4=(RooAbsCategoryLValue*)&pdf4->indexCat();
  cat4->setBin(0);
  TString channelname4=cat4->getLabel();

  if(option.Contains("bonly")){
    yield1=w1->function("yield_background_"+channelname1)->getVal();
    yield2=w2->function("yield_background_"+channelname2)->getVal();
    yield3=w3->function("yield_background_"+channelname3)->getVal();
    yield4=w4->function("yield_background_"+channelname4)->getVal();
    pdfPrefix="pdf_background";
  }
  else{
    yield1=w1->function("yield_background_"+channelname1)->getVal()+w1->function("yield_signal_"+channelname1)->getVal();
    yield2=w2->function("yield_background_"+channelname2)->getVal()+w2->function("yield_signal_"+channelname2)->getVal();
    yield3=w3->function("yield_background_"+channelname3)->getVal()+w3->function("yield_signal_"+channelname3)->getVal();
    yield4=w4->function("yield_background_"+channelname4)->getVal()+w4->function("yield_signal_"+channelname4)->getVal();

    pdfPrefix="modelSB";
  }

  RooRealVar* x1 = (RooRealVar*)mc1->GetObservables()->first();
  RooRealVar* x2 = (RooRealVar*)mc2->GetObservables()->first();
  RooRealVar* x3 = (RooRealVar*)mc3->GetObservables()->first();
  RooRealVar* x4 = (RooRealVar*)mc4->GetObservables()->first();

  TString signalType="";
  if(TString(argv[1]).Contains("Scalar")){
    x1->setMax(1990);
    x2->setMax(1990);
    x3->setMax(1990);
    x4->setMax(1990);
    signalType="scalar";
  }
  else{
    x1->setMax(2000);
    x2->setMax(2000);
    x3->setMax(2000);
    x4->setMax(2000);
    signalType="graviton";
  }
  
  const double binwidth = signalType=="scalar"?20:5;
  const int Nbins = ( x1->getMax()-x1->getMin() )/ binwidth;

  TString dataname="combData";

  if(option.Contains("bonly")){
    cout<<"Check B-only model"<<endl;
    if(signalType=="scalar"){
      w1->loadSnapshot("nominalNuis");
      w2->loadSnapshot("nominalNuis");
      w3->loadSnapshot("nominalNuis");
      w4->loadSnapshot("nominalNuis");
    }
    else{
      w1->loadSnapshot("ucmles_0");
      w2->loadSnapshot("ucmles_0");
      w3->loadSnapshot("ucmles_0");
      w4->loadSnapshot("ucmles_0");
    }
  }
  else{
    w1->loadSnapshot("ucmles");
    w2->loadSnapshot("ucmles");
    w3->loadSnapshot("ucmles");
    w4->loadSnapshot("ucmles");
  }
  TCanvas* c1 = new TCanvas("c1","c1",800,800);
  c1->cd();

  RooPlot* frame1 = x1->frame(Bins(Nbins));
  frame1->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
  frame1->GetYaxis()->SetTitle(Form("Events / %.0f GeV",binwidth));
  w1->pdf(pdfPrefix+"_"+channelname1)->plotOn(frame1,LineColor(kBlack),Normalization(yield1), Name("h011"));

  RooPlot* frame2 = x2->frame(Bins(Nbins));
  frame2->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
  frame2->GetYaxis()->SetTitle(Form("Events / %.0f GeV",binwidth));
  w2->pdf(pdfPrefix+"_"+channelname2)->plotOn(frame2,LineColor(kBlue),Normalization(yield2),LineStyle(kDashed), Name("h011b"));

  RooPlot* frame3 = x3->frame(Bins(Nbins));
  frame3->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
  frame3->GetYaxis()->SetTitle(Form("Events / %.0f GeV",binwidth));
  w3->pdf(pdfPrefix+"_"+channelname3)->plotOn(frame3,LineColor(kGreen+1),Normalization(yield3),LineStyle(kDotted), Name("h012pre2"));

  RooPlot* frame4 = x4->frame(Bins(Nbins));
  frame4->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
  frame4->GetYaxis()->SetTitle(Form("Events / %.0f GeV",binwidth));
  w4->pdf(pdfPrefix+"_"+channelname4)->plotOn(frame4,LineColor(kRed),Normalization(yield4),LineStyle(kDashDotted), Name("h012"));

  TPad *pad1 =  new TPad("pad1","pad1name",0.01,0.40,0.99,0.99);
  TPad *pad2 =  new TPad("pad2","pad2name",0.01,0.05,0.99,0.402);
  pad1->Draw();
  pad2->Draw();

  pad1->SetBottomMargin(0.);
  pad1->cd();
  pad1->SetLogy();
  // c1->SetLogy();
  frame1->GetYaxis()->SetRangeUser(2e-2,5e3);
  frame2->GetYaxis()->SetRangeUser(2e-2,5e3);
  frame3->GetYaxis()->SetRangeUser(2e-2,5e3);
  frame4->GetYaxis()->SetRangeUser(2e-2,5e3);
  frame1->Draw();
  frame2->Draw("same");
  frame3->Draw("same");
  frame4->Draw("same");

  TLegend* lg = new TLegend(0.6,0.7,0.9,0.9);
  lg->SetLineColor(0);
  lg->SetFillColor(0);
  lg->SetShadowColor(0);
  lg->AddEntry("h011","h011","L");
  lg->AddEntry("h011b","h011b","L");
  lg->AddEntry("h012pre2","h012pre2","L");
  lg->AddEntry("h012","h012","L");
  lg->Draw("same");
  
  TH1F* h0 = new TH1F("h0","h0",Nbins,x1->getMin(),x1->getMax());
  h0->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
  h0->GetYaxis()->SetTitle("h012/h011");
  h0->GetYaxis()->SetTitleSize(0.075);
  h0->GetYaxis()->SetTitleOffset(0.80);
  h0->GetYaxis()->SetLabelSize(0.075);
  h0->GetXaxis()->SetTitleSize(0.075);
  h0->GetXaxis()->SetTitleOffset(0.9);
  h0->GetXaxis()->SetLabelSize(0.075);

  if(option.Contains("bonly"))   h0->GetYaxis()->SetRangeUser(0.89,1.11);
  else   h0->GetYaxis()->SetRangeUser(0.51,1.49);
  h0->SetLineWidth(0);
  pad2->SetGrid();

  TH1F* hdata1 = new TH1F("hdata1","hdata1",Nbins,x1->getMin(),x1->getMax()); hdata1->Sumw2();
  TH1F* hdata2 = new TH1F("hdata2","hdata2",Nbins,x2->getMin(),x2->getMax()); hdata2->Sumw2();
  TH1F* hdata3 = new TH1F("hdata3","hdata3",Nbins,x3->getMin(),x3->getMax()); hdata3->Sumw2();
  TH1F* hdata4 = new TH1F("hdata4","hdata4",Nbins,x4->getMin(),x4->getMax()); hdata4->Sumw2();
  
  w1->pdf(pdfPrefix+"_"+channelname1)->fillHistogram(hdata1, RooArgList(*x1));
  w2->pdf(pdfPrefix+"_"+channelname2)->fillHistogram(hdata2, RooArgList(*x2));
  w3->pdf(pdfPrefix+"_"+channelname3)->fillHistogram(hdata3, RooArgList(*x3));
  w4->pdf(pdfPrefix+"_"+channelname4)->fillHistogram(hdata4, RooArgList(*x4));

  ScaleTo(hdata1, yield1, true);
  ScaleTo(hdata2, yield2, true);
  ScaleTo(hdata3, yield3, true);
  ScaleTo(hdata4, yield4, true);

  SignificanceHist *p12=new SignificanceHist(*hdata2, *hdata1);
  SignificanceHist *p13=new SignificanceHist(*hdata3, *hdata1);
  SignificanceHist *p14=new SignificanceHist(*hdata4, *hdata1);

  
  pad2->SetTopMargin(0.);
  pad2->cd();
  h0->Draw();

  TH1F *hratio12=p12->GetRatioHist();
  TH1F *hratio13=p13->GetRatioHist();
  TH1F *hratio14=p14->GetRatioHist();

  hratio12->SetLineColor(kBlue); // hratio12->SetLineStyle(kDashed);
  hratio13->SetLineColor(kGreen+1); // hratio13->SetLineStyle(kDotted);
  hratio14->SetLineColor(kRed);  // hratio14->SetLineStyle(kDashDotted);

  DrawConstantLine(pad2, 1, x1->getMin(), x1->getMax(), kBlack, 1, 2);
  hratio12->Draw("same,hist");
  hratio13->Draw("same,hist");
  hratio14->Draw("same,hist");

  TString outputFigName="fig/background_estimate_"+signalType;
  if(option.Contains("bonly")) outputFigName+="_bonly";
  else outputFigName+="_sb";
  PrintCanvas(c1,outputFigName);

  return 0;
}
