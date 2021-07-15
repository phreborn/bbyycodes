#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"
#include "statistics.hh"

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

  const double binwidth = 40;
  const int Nbins = ( x->getMax()-x->getMin() )/ binwidth;

  RooPlot* frame1 = x->frame(Bins(Nbins));
  frame1->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
  frame1->GetYaxis()->SetTitle("Events / 40 GeV");

  cout<<"okya here"<<endl;
  RooAbsPdf *bkgPdf=w1->pdf(pdfName);
  RooAbsData *data=w1->data("combData");
  data->plotOn(frame1, DataError(RooAbsData::Poisson));
  w1->loadSnapshot("nominalNuis");
  bkgPdf->plotOn(frame1,Name("prefit"),LineColor(kBlue));
  
  w1->loadSnapshot("ucmles_0");
  bkgPdf->plotOn(frame1,Name("postfit"),LineColor(kRed));
  data->plotOn(frame1, DataError(RooAbsData::Poisson), Name("data"));
  
  TH1F* hd = new TH1F("hd","hd",Nbins,x->getMin(),x->getMax());
  TH1F* hdata = new TH1F("hdata","hdata",Nbins,x->getMin(),x->getMax());
  double mass_val = x->getMin();

  double sumS1 = 0;
  double sumS2 = 0;
  double totalD1 = data->sumEntries();

  const int nNP=5;
  
  TString NPList[nNP]={"alpha_bkg_irreducible_13TeV", "alpha_bkg_reducible_13TeV", "alpha_bkg_purity_13TeV", "alpha_bkg_isolation_13TeV", "alpha_geo"};
  TString NPName[nNP]={"Irreducible", "Reducible", "Purity", "Isolation matching", "GEO 21 vs. 20"};

  TH1D *NPhist[nNP][2];

  for( int inp=0; inp<nNP; inp++){
    if(w1->var(NPList[inp])||NPList[inp]=="stat"||NPList[inp]=="total"){
      NPhist[inp][0]=new TH1D(NPList[inp]+"up",NPName[inp], Nbins, x->getMin(), x->getMax());
      NPhist[inp][1]=new TH1D(NPList[inp]+"dn",NPName[inp], Nbins, x->getMin(), x->getMax());
    }
    else{
      NPhist[inp][0]=NPhist[inp][1]=NULL;
    }
  }
  
  cout<<"okya here"<<endl;
  for( int i = 0 ; i < Nbins; i ++ ){
    // Pre-fit - post -fit
    x->setRange("range",mass_val,mass_val+binwidth);
    w1->loadSnapshot("nominalNuis");
    RooAbsReal* integral =  dynamic_cast<RooAbsReal*>(bkgPdf->createIntegral(RooArgSet(*x), NormSet(*x), Range("range"))) ;
    double weight1 = integral->getVal()*totalD1;
    w1->loadSnapshot("ucmles_0");
    double weight2 = integral->getVal()*totalD1;
    
    hd->SetBinContent(i+1,(weight2-weight1)/weight1);
    cout<<weight1<<" "<<weight2<<" "<<(weight2-weight1)/weight2<<endl;

    // Test each NP
    w1->loadSnapshot("nominalNuis");
    for( int inp =0; inp<nNP; inp++){
      if(NPhist[inp][0]==NULL) continue;
      // if(NPList=="stat"){
      // 	for(int idx=i*8; idx<(i+1)*8; idx++){
      // 	  TString statNPName=Form("gamma_stat_channel_bin_%d", idx);
      // 	  if(option.Contains("8tev")) statNPName=Form("gamma_stat_chan_8TeV_bin_%d", idx);
      // 	  w1->var
      // 	}
      // }
      else{
	w1->var(NPList[inp])->setVal(1);
	double weightNPUp = integral->getVal()*totalD1;
	NPhist[inp][0]->SetBinContent(i+1, (weightNPUp-weight1)/weight1);
	
	w1->var(NPList[inp])->setVal(-1);
	double weightNPDo = integral->getVal()*totalD1;
	NPhist[inp][1]->SetBinContent(i+1, (weightNPDo-weight1)/weight1);
	
	w1->var(NPList[inp])->setVal(0);
      }
    }
    mass_val+=binwidth;
  }
  cout<<"still okay here"<<endl;
  hd->GetYaxis()->SetRangeUser(-0.12,0.12);
  hd->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
  // hd->GetYaxis()->SetTitle("(Fit-Template)/Template");
  hd->GetYaxis()->SetTitle("(post #minus pre)/pre");
  hd->GetYaxis()->SetTitleSize(0.150);
  hd->GetYaxis()->SetTitleOffset(0.5);
  hd->GetYaxis()->SetLabelSize(0.12);
  hd->GetXaxis()->SetTitleSize(0.15);
  hd->GetXaxis()->SetTitleOffset(1.0);
  hd->GetXaxis()->SetLabelSize(0.15);

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
  
  TLegend *leg1 = FastLegend(x2-0.45, y2-0.45, x2-0.05, y2-0.2, 0.07);

  leg1->AddEntry("data","Data", "P");
  leg1->AddEntry("prefit","Pre-fit bkg. model","L");
  leg1->AddEntry("postfit","Post-fit bkg. model","L");
  leg1->Draw("same");
  
  pad1->RedrawAxis();
  pad1->Update();

  pad2->SetTopMargin(0.);
  pad2->SetBottomMargin(0.35);
  pad2->cd();
  hd->SetLineColor(kRed);
  // hd->SetLineStyle();
  hd->Draw();

  GetX1Y1X2Y2(pad2, x1,y1,x2,y2);
  
  // TLegend *legend2=FastLegend(x1-0.05,y1-0.3, x2-0.15, y1-0.1,0.1);
  // legend2->SetNColumns(nNP+1);
  // legend2->AddEntry(hd, "post-fit #minus pre-fit", "l");
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
  
  TLine* l = new TLine(x->getMin(),0,x->getMax(),0);
  l->SetLineColor(kBlue);
  l->SetLineWidth(2);
  l->Draw("same");
  TLine* lp10 = new TLine(x->getMin(),0.10,x->getMax(),0.10);
  lp10->SetLineWidth(2);
  lp10->SetLineStyle(kDotted);
  lp10->Draw("same");
  TLine* lm10 = new TLine(x->getMin(),-0.10,x->getMax(),-0.10);
  lm10->SetLineWidth(2);
  lm10->SetLineStyle(kDotted);
  lm10->Draw("same");
  hd->Draw("same");
  pad2->RedrawAxis();
  pad2->Update();

  system("mkdir -vp fig/fit/"+jobname+"/");
  PrintCanvas(c1, "fig/fit/"+jobname+"/bkg_prefit_vs_postfit");
}
