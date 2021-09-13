#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"
#include "statistics.hh"

using namespace std;
using namespace RooFit;
using namespace RooStats;
using namespace CommonFunc;

void rootlogon()
{
  std::cout << "\nApplying ATLAS style settings...\n" << std::endl ;
  // Load ATLAS style
  TStyle *atlasStyle = new TStyle("ATLAS","Atlas style");

  // use plain black on white colors
  Int_t icol=0; // WHITE
  atlasStyle->SetFrameBorderMode(icol);
  atlasStyle->SetFrameFillColor(icol);
  atlasStyle->SetCanvasBorderMode(icol);
  atlasStyle->SetCanvasColor(icol);
  atlasStyle->SetPadBorderMode(icol);
  atlasStyle->SetPadColor(icol);
  atlasStyle->SetStatColor(icol);
  //atlasStyle->SetFillColor(icol); // don't use: white fill color for *all* objects

  // set the paper & margin sizes
  atlasStyle->SetPaperSize(20,26);

  // set margin sizes
  atlasStyle->SetPadTopMargin(0.05);
  atlasStyle->SetPadRightMargin(0.05);
  atlasStyle->SetPadBottomMargin(0.16);
  atlasStyle->SetPadLeftMargin(0.16);

  // set title offsets (for axis label)
  atlasStyle->SetTitleXOffset(1.4);
  atlasStyle->SetTitleYOffset(1.4);

  // use large fonts
  //Int_t font=72; // Helvetica italics
  Int_t font=42; // Helvetica
  Double_t tsize=0.05;
  atlasStyle->SetTextFont(font);
  atlasStyle->SetLegendFont(font);

  atlasStyle->SetTextSize(tsize);
  atlasStyle->SetLabelFont(font,"x");
  atlasStyle->SetTitleFont(font,"x");
  atlasStyle->SetLabelFont(font,"y");
  atlasStyle->SetTitleFont(font,"y");
  atlasStyle->SetLabelFont(font,"z");
  atlasStyle->SetTitleFont(font,"z");
  
  atlasStyle->SetLabelSize(tsize,"x");
  atlasStyle->SetTitleSize(tsize,"x");
  atlasStyle->SetLabelSize(tsize,"y");
  atlasStyle->SetTitleSize(tsize,"y");
  atlasStyle->SetLabelSize(tsize,"z");
  atlasStyle->SetTitleSize(tsize,"z");

  // use bold lines and markers
  atlasStyle->SetMarkerStyle(20);
  atlasStyle->SetMarkerSize(1.2);
  atlasStyle->SetHistLineWidth(3.);
  atlasStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

  // get rid of X error bars 
  //atlasStyle->SetErrorX(0.001);
  // get rid of error bar caps
  atlasStyle->SetEndErrorSize(0.);

  // do not display any of the standard histogram decorations
  atlasStyle->SetOptTitle(0);
  //atlasStyle->SetOptStat(1111);
  atlasStyle->SetOptStat(0);
  //atlasStyle->SetOptFit(1111);
  atlasStyle->SetOptFit(0);

  // put tick marks on top and RHS of plots
  atlasStyle->SetPadTickX(1);
  atlasStyle->SetPadTickY(1);

  gROOT->SetStyle("ATLAS");
  gROOT->ForceStyle();
}

int main( int argc, char** argv ){
  if( argc!=3 ){
    cout<<"Usage: "<<argv[0]<<" input_file1 input_file2"<<endl;
    exit(0);
  }
  rootlogon();

  TFile* fin1 = TFile::Open(argv[1]);
  RooWorkspace* w1 = dynamic_cast<RooWorkspace*>(fin1->Get("combWS"));
  TFile* fin2 = TFile::Open(argv[2]);
  RooWorkspace* w2 = dynamic_cast<RooWorkspace*>(fin2->Get("combWS"));

  RooRealVar* x1 = w1->var("obs_x_channel");
  x1->setMax(2000);
  RooRealVar* x2 = w2->var("atlas_invMass");
  x2->setMax(2000);
  const double binwidth = 50;
  const int Nbins = ( x1->getMax()-x1->getMin() )/ binwidth;

  RooPlot* frame1 = x1->frame(Bins(Nbins));
  frame1->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
  frame1->GetYaxis()->SetTitle("Events / 50 GeV");
  w1->pdf("pdf_background_inclusive_13TeV")->plotOn(frame1,LineColor(kBlue),Normalization(w1->var("nbkg")->getVal()),LineStyle(4));
  w1->data("combData")->plotOn(frame1);
  w1->pdf("modelSB_inclusive_13TeV")->plotOn(frame1,LineColor(kBlue));

  RooPlot* frame2 = x2->frame(Bins(Nbins));
  frame2->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
  frame2->GetYaxis()->SetTitle("Events / 50 GeV");
  w2->pdf("pdf_background_inclusive_13TeV")->plotOn(frame2,LineColor(kRed),Normalization(w2->var("nbkg")->getVal()),LineStyle(5));
  w2->pdf("modelSB_inclusive_13TeV")->plotOn(frame2,LineColor(kRed),LineStyle(kDashed),Normalization(w2->data("combData")->sumEntries()));

  TH1F* hd = new TH1F("hd","hd",Nbins,x1->getMin(),x1->getMax());
  double mass_val = x1->getMin();

  double sumS1 = 0;
  double sumS2 = 0;
  double totalD1 = w1->data("combData")->sumEntries();
  double totalD2 = w2->data("combData")->sumEntries();
  for( int i = 0 ; i < Nbins; i ++ ){
    x1->setRange("range",mass_val,mass_val+binwidth);
    RooAbsReal* integral1 =  dynamic_cast<RooAbsReal*>(w1->pdf("pdf_background_inclusive_13TeV")->createIntegral(RooArgSet(*x1), NormSet(*x1), Range("range"))) ;
    double weight1 = integral1->getVal()*w1->var("nbkg")->getVal();
    RooAbsReal* integralA1 =  dynamic_cast<RooAbsReal*>(w1->pdf("modelSB_inclusive_13TeV")->createIntegral(RooArgSet(*x1), NormSet(*x1), Range("range"))) ;
    double weightA1 = integralA1->getVal()*totalD1;
    sumS1 += weightA1-weight1;

    x2->setRange("range",mass_val,mass_val+binwidth);
    RooAbsReal* integral2 =  dynamic_cast<RooAbsReal*>(w2->pdf("pdf_background_inclusive_13TeV")->createIntegral(RooArgSet(*x2), NormSet(*x2), Range("range"))) ;
    double weight2 = integral2->getVal()*w2->var("nbkg")->getVal();
    RooAbsReal* integralA2 =  dynamic_cast<RooAbsReal*>(w2->pdf("modelSB_inclusive_13TeV")->createIntegral(RooArgSet(*x2), NormSet(*x2), Range("range"))) ;
    double weightA2 = integralA2->getVal()*totalD2;
    sumS2 += weightA2-weight2;

    hd->SetBinContent(i+1,(weight2-weight1)/weight1);

    mass_val+=binwidth;
  }

  hd->GetYaxis()->SetRangeUser(-0.12,0.12);
  hd->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
  hd->GetYaxis()->SetTitle("(Fit-Template)/Template");
  hd->GetYaxis()->SetTitleSize(0.080);
  hd->GetYaxis()->SetTitleOffset(0.80);
  hd->GetYaxis()->SetLabelSize(0.075);
  hd->GetXaxis()->SetTitleSize(0.075);
  hd->GetXaxis()->SetTitleOffset(0.9);
  hd->GetXaxis()->SetLabelSize(0.075);

  RooPlot* frameS1 = x1->frame(Bins(Nbins));
  w1->pdf("pdf_signal_inclusive_13TeV")->plotOn(frameS1,LineColor(kBlue),Normalization(sumS1));
  RooPlot* frameS2 = x2->frame(Bins(Nbins));
  w2->pdf("pdf_signal_inclusive_13TeV")->plotOn(frameS2,LineColor(kRed),LineStyle(kDashed),Normalization(sumS2));
  frameS1->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
  frameS1->GetYaxis()->SetTitle("Fitted signal");
  frameS1->GetYaxis()->SetTitleSize(0.090);
  frameS1->GetYaxis()->SetTitleOffset(0.75);
  frameS1->GetYaxis()->SetLabelSize(0.075);
  frameS1->GetXaxis()->SetTitleSize(0.085);
  frameS1->GetXaxis()->SetTitleOffset(1.0);
  frameS1->GetXaxis()->SetLabelSize(0.075);


  TCanvas* c1 = new TCanvas("c1","c1",800,1000);
  c1->cd();
  c1->SetBottomMargin(0);
  //double part = 0.45;
  //TPad *pad1 =  new TPad("pad1","pad1name",0.01,0.40*(1-part)+part,0.99,0.99*(1-part)+part);
  //TPad *pad2 =  new TPad("pad2","pad2name",0.01,0.05*(1-part)+part,0.99,0.402*(1-part)+part);
  TPad *pad1 =  new TPad("pad1","pad1name",0.01,0.60,0.99,0.99);
  TPad *pad2 =  new TPad("pad2","pad2name",0.01,0.35,0.99,0.602);
  TPad *pad3 =  new TPad("pad3","pad3name",0.01,0.10,0.99,0.352);
  pad1->Draw();
  pad2->Draw();
  pad3->Draw();

  pad1->SetBottomMargin(0.);
  pad1->cd();
  pad1->SetLogy();
  frame1->GetYaxis()->SetRangeUser(0.06,9.9e3);
  frame1->Draw();
  frame2->Draw("same");
  pad1->RedrawAxis();
  pad1->Update();

  pad2->SetTopMargin(0.);
  pad2->SetBottomMargin(0.);
  pad2->cd();
  hd->SetLineColor(kRed);
  hd->SetLineStyle(kDashed);
  hd->Draw();
  TLine* l = new TLine(x1->getMin(),0,x1->getMax(),0);
  l->SetLineColor(kBlue);
  l->SetLineWidth(2);
  l->Draw("same");
  TLine* lp10 = new TLine(x1->getMin(),0.10,x1->getMax(),0.10);
  lp10->SetLineWidth(2);
  lp10->SetLineStyle(kDotted);
  lp10->Draw("same");
  TLine* lm10 = new TLine(x1->getMin(),-0.10,x1->getMax(),-0.10);
  lm10->SetLineWidth(2);
  lm10->SetLineStyle(kDotted);
  lm10->Draw("same");
  hd->Draw("same");
  pad2->RedrawAxis();
  pad2->Update();

  pad3->SetTopMargin(0.);
  pad3->SetBottomMargin(0.2);
  pad3->SetLogy();
  pad3->cd();
  frameS1->Draw();
  frameS2->Draw("same");
  frameS1->GetXaxis()->SetTitleSize(0.10);
  frameS1->GetXaxis()->SetLabelSize(0.10);
  pad3->RedrawAxis();
  pad3->Update();

  c1->Print("comp.eps");
  c1->Print("comp.pdf");

  return 1;
}
