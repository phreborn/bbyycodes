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
  if( argc<3 ){
    cout<<"Usage: "<<argv[0]<<" <jobname> <input workspace>"<<endl;
    exit(0);
  }
  SetAtlasStyle();
  TString jobname=argv[1];
  TString inputFileName=argv[2];
  TString option=argv[3];
  
  TFile* fin1 = TFile::Open(inputFileName);
  RooWorkspace* w1 = dynamic_cast<RooWorkspace*>(fin1->Get("combWS"));

  TString obsName="obs_x_channel", pdfName="pdf_background_inclusive_13TeV";

  if(option.Contains("8tev")){
    obsName="obs_x_chan_8TeV";
    pdfName="pdf_background_inclusive_8TeV";
  }
  
  RooRealVar* x = w1->var(obsName);
  x->setMax(2000);

  const double binwidth = 20;
  const int Nbins = ( x->getMax()-x->getMin() )/ binwidth;

  RooPlot* frame1 = x->frame(Bins(Nbins));
  frame1->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
  frame1->GetYaxis()->SetTitle(Form("Events / %.0f GeV", binwidth));

  cout<<"okya here"<<endl;
  RooAbsPdf *bkgPdf=w1->pdf(pdfName);
  RooAbsData *data=w1->data("combData");
  data->plotOn(frame1, DataError(RooAbsData::Poisson), MarkerSize(0.9));

  w1->loadSnapshot("ucmles_0");
  bkgPdf->plotOn(frame1,Name("postfit"),LineColor(kRed));
  data->plotOn(frame1, DataError(RooAbsData::Poisson), Name("data"), MarkerSize(0.9));
  
  TH1F* hmc = new TH1F("hmc","hmc",Nbins,x->getMin(),x->getMax());
  TH1F* hdata = new TH1F("hdata","hdata",Nbins,x->getMin(),x->getMax());
  double mass_val = x->getMin();

  double sumS1 = 0;
  double sumS2 = 0;
  double totalD1 = data->sumEntries();

  for( int i = 0 ; i < Nbins; i ++ ){
    // Pre-fit - post -fit
    x->setRange("range",mass_val,mass_val+binwidth);
    RooAbsReal* integral =  dynamic_cast<RooAbsReal*>(bkgPdf->createIntegral(RooArgSet(*x), NormSet(*x), Range("range"))) ;
    double weight1 = integral->getVal()*totalD1;

    double weight2 = data->sumEntries(Form("%s>%f&&%s<%f",
					   x->GetName(), mass_val,
					   x->GetName(), mass_val+binwidth));
    cout<<weight1<<" "<<weight2<<endl;
    hmc->SetBinContent(i+1,weight1);
    hdata->SetBinContent(i+1,weight2);
    mass_val+=binwidth;
  }

  SignificanceHist *tool=new SignificanceHist(*hdata, *hmc);
  TH1F *hsignif=tool->GetSignificanceHist();
  // hsignif->GetYaxis()->SetRangeUser(-0.12,0.12);
  // hsignif->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
  // // hsignif->GetYaxis()->SetTitle("(Fit-Template)/Template");
  // hsignif->GetYaxis()->SetTitle("Significance [#sigma]");
  // hsignif->GetYaxis()->SetTitleSize(0.150);
  // hsignif->GetYaxis()->SetTitleOffset(0.5);
  // hsignif->GetYaxis()->SetLabelSize(0.12);
  // hsignif->GetXaxis()->SetTitleSize(0.15);
  // hsignif->GetXaxis()->SetTitleOffset(1.0);
  // hsignif->GetXaxis()->SetLabelSize(0.15);

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
  TPaveText* text=CreatePaveText(x2-0.4,y2-0.2,x2-0.05,y2-0.05,pavetext,0.07);
  text->Draw("same");
  
  TLegend *leg1 = FastLegend(x2-0.45, y2-0.45, x2-0.05, y2-0.35, 0.06);

  leg1->AddEntry("data","Data", "LEP");
  leg1->AddEntry("postfit","Post-fit bkg. model","L");
  leg1->Draw("same");
  
  pad1->RedrawAxis();
  pad1->Update();

  pad2->SetTopMargin(0.);
  pad2->SetBottomMargin(0.35);
  pad2->cd();
  // hsignif->SetLineColor(kRed);
  // hsignif->SetLineStyle();
  hsignif->Draw();

  GetX1Y1X2Y2(pad2, x1,y1,x2,y2);
  
  // TLegend *legend2=FastLegend(x1-0.05,y1-0.3, x2-0.15, y1-0.1,0.1);
  // legend2->SetNColumns(nNP+1);
  // legend2->AddEntry(hsignif, "post-fit #minus pre-fit", "l");
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
  
  // TLine* l = new TLine(x->getMin(),0,x->getMax(),0);
  // l->SetLineColor(kBlue);
  // l->SetLineWidth(2);
  // l->Draw("same");
  TLine* lp10 = new TLine(x->getMin(),2.0,x->getMax(),2.0);
  lp10->SetLineWidth(2);
  lp10->SetLineStyle(kDotted);
  lp10->Draw("same");
  TLine* lm10 = new TLine(x->getMin(),-2.0,x->getMax(),-2.0);
  lm10->SetLineWidth(2);
  lm10->SetLineStyle(kDotted);
  lm10->Draw("same");

  hsignif->Draw("same");

  pad2->RedrawAxis();
  pad2->Update();

  system("mkdir -vp fig/fit/"+jobname+"/");
  PrintCanvas(c1, "fig/fit/"+jobname+"/bkg_significance");
}
