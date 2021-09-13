#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"
#include "ToolsSignificanceHist.h"

using namespace std;
using namespace RooFit;
using namespace RooStats;
using namespace CommonFunc;

int main( int argc, char** argv ){
  if( argc<4 ){
    cout<<"Usage: "<<argv[0]<<" <jobname> <input workspace> <type>"<<endl;
    exit(0);
  }
  SetAtlasStyle();
  const TString jobname=argv[1];
  const TString inputFileName=argv[2];
  const TString type=argv[3];
  TString option=argv[4];
  
  TFile* fin1 = TFile::Open(inputFileName);
  RooWorkspace* w1 = dynamic_cast<RooWorkspace*>(fin1->Get("combWS"));

  TString pdfName="pdf_background_inclusive_13TeV", SBPdfName="modelSB_inclusive_13TeV";

  if(option.Contains("8tev")){
    pdfName="pdf_background_inclusive_8TeV";
    SBPdfName="modelSB_inclusive_8TeV";
  }

  RooRealVar* x = (RooRealVar*)w1->set("Observables")->first();
  x->setMax(2000);

  const double binwidth = 20;
  const int Nbins = ( x->getMax()-x->getMin() )/ binwidth;

  RooPlot* frame1 = x->frame(Bins(Nbins));
  frame1->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
  frame1->GetYaxis()->SetTitle(Form("Events / %.0f GeV", binwidth));

  RooAbsPdf *bkgPdf=w1->pdf(pdfName);
  RooAbsData *data=w1->data("combData");
  data->plotOn(frame1, DataError(RooAbsData::Poisson), MarkerSize(0.9));

  TString tag=type;
  if(option.Contains("sb")){
    w1->loadSnapshot("ucmles");
    w1->set("POI")->Print("v");
    tag+="_sb";
  }
  else if(option.Contains("bo")){
    w1->loadSnapshot("ucmles_0");
    tag+="_bo";
  }
  else{
    cerr<<"what the fuck do you want?"<<endl;
    return -1;
  }
  if(option.Contains("plotsb")){
    w1->pdf(SBPdfName)->plotOn(frame1,Name("sbfit"),LineColor(kBlue));
    tag+="_plotsb";
  }
  bkgPdf->plotOn(frame1,Name("postfit"),LineColor(kRed));
  data->plotOn(frame1, DataError(RooAbsData::Poisson), Name("data"), MarkerSize(0.9));
  
  TH1F* hmc = new TH1F("hmc","hmc",Nbins,x->getMin(),x->getMax());
  TH1F* hdata = new TH1F("hdata","hdata",Nbins,x->getMin(),x->getMax());
  double mass_val = x->getMin();
  hmc->Sumw2();
  hdata->Sumw2();
  double sumS1 = 0;
  double sumS2 = 0;
  double totalD1 = data->sumEntries();
  double nbkg=w1->var("nbkg")->getVal();
  
  for( int i = 0 ; i < Nbins; i ++ ){
    // Pre-fit - post -fit
    x->setRange("range",mass_val,mass_val+binwidth);
    RooAbsReal* integral =  dynamic_cast<RooAbsReal*>(bkgPdf->createIntegral(RooArgSet(*x), NormSet(*x), Range("range"))) ;
    double weight1 = integral->getVal()*totalD1;

    double weight2 = data->sumEntries(Form("%s>%f&&%s<%f",
					   x->GetName(), mass_val,
					   x->GetName(), mass_val+binwidth));
    if(type=="cdf"){
      hmc->SetBinContent(i+1,weight1+hmc->GetBinContent(i));
      hdata->SetBinContent(i+1,weight2+hdata->GetBinContent(i));
    }
    else{
      hmc->SetBinContent(i+1,weight1);
      hdata->SetBinContent(i+1,weight2);
    }
    mass_val+=binwidth;
  }

  // if(type=="cdf"){
  //   for( int i = 0 ; i < Nbins; i ++ ){
  //     hmc->SetBinContent(i+1, nbkg-hmc->GetBinContent(i+1));
  //     hdata->SetBinContent(i+1, totalD1-hdata->GetBinContent(i+1));
  //   }
  // }
  SignificanceHist *tool=new SignificanceHist(*hdata, *hmc);
  TH1F *hsub=NULL;
  
  if(type=="significance"){
    hsub=tool->GetSignificanceHist();
    if(option.Contains("extend")) hsub->GetYaxis()->SetRangeUser(-2.5,3.9);
  }
  if(type=="cdf"){
    hsub=tool->GetRatioHist();
    hsub->GetYaxis()->SetRangeUser(0.95,1.05);
    hsub->SetMarkerSize(0.9);
    hsub->GetYaxis()->SetTitle("Data Int. / Bkg. Int.");
  }
  hsub->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
  // // hsub->GetYaxis()->SetTitle("(Fit-Template)/Template");
  // hsub->GetYaxis()->SetTitle("Significance [#sigma]");
  // hsub->GetYaxis()->SetTitleSize(0.150);
  // hsub->GetYaxis()->SetTitleOffset(0.5);
  // hsub->GetYaxis()->SetLabelSize(0.12);
  hsub->GetXaxis()->SetTitleSize(0.15);
  hsub->GetXaxis()->SetTitleOffset(1.0);
  hsub->GetXaxis()->SetLabelSize(0.15);

  TCanvas* c1 = new TCanvas("c1","c1",800,600);
  c1->cd();
  //double part = 0.45;
  TPad *pad1 =  new TPad("pad1","pad1name",0.01,0.35,0.99,0.99);
  TPad *pad2 =  new TPad("pad2","pad2name",0.01,0.00,0.99,0.35);
  // TPad *pad3 =  new TPad("pad3","pad3name",0.01,0.10,0.99,0.352);
  pad1->Draw();
  pad2->Draw();

  pad1->SetBottomMargin(0.);
  pad1->cd();
  pad1->SetLogy();
  frame1->GetYaxis()->SetRangeUser(0.06,9.9e3);
  frame1->GetYaxis()->SetLabelSize(0.06);
  frame1->GetYaxis()->SetTitleSize(0.07);
  frame1->GetYaxis()->SetTitleOffset(1.0);
  frame1->Draw();

  double x1,y1,x2,y2;
  GetX1Y1X2Y2(pad1, x1,y1,x2,y2);
  
  vector<TString> pavetext;
  pavetext.push_back("#bf{#it{ATLAS}} internal");
  if(option.Contains("8tev")) pavetext.push_back("#sqrt{#it{s}} = 8 TeV, 20.3 fb^{-1}");
  else pavetext.push_back("#sqrt{#it{s}} = 13 TeV, 3.2 fb^{-1}");
  if(option.Contains("ekei")) pavetext.push_back("Graviton loose selection");
  else if(option.Contains("ekhi")) pavetext.push_back("Graviton tight selection");
  else if(option.Contains("scalar")) pavetext.push_back("Scalar selection");
  
  if(option.Contains("sb")) pavetext.push_back("Signal + background fit");
  else if(option.Contains("bo")) pavetext.push_back("Background-only fit");
  
  TPaveText* text=CreatePaveText(x2-0.4,y2-0.35,x2-0.05,y2-0.05,pavetext,0.07);
  text->Draw("same");
  
  TLegend *leg1 = FastLegend(x2-0.45, y2-0.55, x2-0.05, y2-0.35, 0.07);

  leg1->AddEntry("data","Data", "LEP");
  leg1->AddEntry("postfit","Post-fit bkg. model","L");
  if(option.Contains("plotsb")){
    leg1->AddEntry("sbfit","S+B fit","L");
  }
  leg1->Draw("same");
  
  pad1->RedrawAxis();
  pad1->Update();

  pad2->SetTopMargin(0.);
  pad2->SetBottomMargin(0.35);
  pad2->cd();
  // hsub->SetLineColor(kRed);
  // hsub->SetLineStyle();
  hsub->Draw();

  GetX1Y1X2Y2(pad2, x1,y1,x2,y2);
  
  // TLegend *legend2=FastLegend(x1-0.05,y1-0.3, x2-0.15, y1-0.1,0.1);
  // legend2->SetNColumns(nNP+1);
  // legend2->AddEntry(hsub, "post-fit #minus pre-fit", "l");
  // for(int inp=0;inp<nNP;inp++){
  //   if(NPhist[inp][0]==NULL) continue;
  //   NPhist[inp][0]->SetLineColor(ColorWheel(inp+3));
  //   NPhist[inp][1]->SetLineColor(ColorWheel(inp+3));
  //   NPhist[inp][0]->SetLineWidth(2);
  //   NPhist[inp][1]->SetLineWidth(2);
  //   NPhist[inp][0]->SetLineStyle(kDashed);
  //   NPhist[inp][1]->SetLineStyle(kDashed);

  //   NPhist[inp][0]->Draw("hist,same");
  //   NPhist[inp][1]->Draw("hist,same");
  //   legend2->AddEntry(NPhist[inp][0],NPName[inp],"l");
  // }
  // legend2->Draw("same");

  if(type=="cdf"){
    TLine* l = new TLine(x->getMin(),1,x->getMax(),1);
    l->SetLineColor(kBlue);
    l->SetLineWidth(2);
    l->Draw("same");
    TLine* lp10 = new TLine(x->getMin(),1.02,x->getMax(),1.02);
    lp10->SetLineWidth(2);
    lp10->SetLineStyle(kDotted);
    lp10->Draw("same");
    TLine* lm10 = new TLine(x->getMin(),0.98,x->getMax(),0.98);
    lm10->SetLineWidth(2);
    lm10->SetLineStyle(kDotted);
    lm10->Draw("same");
  }
  else if(type=="significance"){
    TLine* lp10 = new TLine(x->getMin(),2.0,x->getMax(),2.0);
    lp10->SetLineWidth(2);
    lp10->SetLineStyle(kDotted);
    lp10->Draw("same");
    TLine* lm10 = new TLine(x->getMin(),-2.0,x->getMax(),-2.0);
    lm10->SetLineWidth(2);
    lm10->SetLineStyle(kDotted);
    lm10->Draw("same");
    TLine* lp20 = new TLine(x->getMin(),3.0,x->getMax(),3.0);
    lp20->SetLineWidth(2);
    lp20->SetLineStyle(kDotted);
    lp20->Draw("same");
  }
  hsub->Draw("same");

  pad2->RedrawAxis();
  pad2->Update();

  system("mkdir -vp fig/fit/"+jobname+"/");
  PrintCanvas(c1, "fig/fit/"+jobname+"/bkg_"+tag);
}
