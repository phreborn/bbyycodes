#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"
#include "statistics.hh"

using namespace std;
using namespace RooFit;
using namespace RooStats;
using namespace CommonFunc;

TString categoryTranslator(TString channelname){
  if(channelname=="BB_13TeV") return "barrel-barrel";
  if(channelname=="nonBB_13TeV") return "non-barrel-barrel";
  if(channelname=="CC_13TeV") return "central-central";
  if(channelname=="nonCC_13TeV") return "non-central-central";
  return "";
}

int main( int argc, char** argv ){
  if( argc<2 ){
    cout<<"Usage: "<<argv[0]<<" input_file"<<endl;
    exit(0);
  }
  TString jobname=argv[1];
  TString inputFileName=argv[2];
  
  const double binwidth = 20, xmax=2000;
  
  SetAtlasStyle();

  TFile* fin = TFile::Open(inputFileName);
  RooWorkspace* w = dynamic_cast<RooWorkspace*>(fin->Get("combWS"));
  ModelConfig *mc=(ModelConfig*)w->obj("ModelConfig");
  RooDataSet* m_data = (RooDataSet*)w->data("combData");
  RooSimultaneous* m_pdf = (RooSimultaneous*)mc->GetPdf();

  RooAbsCategoryLValue*  m_cat = (RooAbsCategoryLValue*)&m_pdf->indexCat();
  int numChannels = m_cat->numBins(0);

  TList* m_dataList = m_data->split( *m_cat, true );
  
  w->loadSnapshot("ucmles");
  for ( int i= 0; i < numChannels; i++ ) {
    m_cat->setBin(i);
    TString channelname=m_cat->getLabel();
    RooAbsPdf* pdfi = m_pdf->getPdf(m_cat->getLabel());

    RooDataSet* datai = ( RooDataSet* )( m_dataList->At( i ) );
    std::cout << "\t\tIndex: " << i << ", Pdf: " << pdfi->GetName() << ", Data: " << datai->GetName()  << ", SumEntries: " << datai->sumEntries() << " NumEntries: "<< datai->numEntries() <<std::endl;
    RooRealVar *x=(RooRealVar*)pdfi->getObservables(datai)->first();
  
    cout<<"okok 1"<<endl;
    const int Nbins = ( xmax-x->getMin() )/ binwidth;
    TH1D *hframe=new TH1D("hframe","hframe", Nbins, x->getMin(), xmax);
    hframe->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
    hframe->GetYaxis()->SetTitle(Form("Events / %.0f GeV",binwidth));

    RooPlot* frame = x->frame(Bins(Nbins));
    cout<<"okok 1.1"<<endl;
    frame->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
    frame->GetYaxis()->SetTitle(Form("Events / %.0f GeV",binwidth));
    cout<<"okok 1.2"<<endl;
    // w->pdf("pdf_background_"+channelname)->plotOn(frame,LineColor(kBlue),Normalization(w->function("yield_background_"+channelname)->getVal()));
    cout<<"okok 1.3"<<endl;
    //w->data("combData")->plotOn(frame,Cut("sample==indexCat::"+channelname));
    datai->plotOn(frame, Binning(Nbins), DataError(RooAbsData::Poisson));
    cout<<"okok 1.4"<<endl;
    //w->pdf("modelSB_"+channelname)->plotOn(frame,LineColor(kRed),Normalization((w->function("expectation_proc_signal_"+channelname)->getVal()+w->function("yield_background_"+channelname)->getVal())/7391.));
    pdfi->plotOn(frame,LineColor(kBlue), Components("pdf_background_"+channelname));
    pdfi->plotOn(frame,LineColor(kRed));
    cout<<"okok 1.5 "<<w->function("expectation_proc_signal_"+channelname)->getVal()+w->function("yield_background_"+channelname)->getVal()<<endl;
    datai->plotOn(frame, Binning(Nbins), DataError(RooAbsData::Poisson));
    cout<<"okok 2"<<endl;

    TH1F* h1 = new TH1F("h1","h1",Nbins,x->getMin(),xmax); h1->Sumw2();
    TH1F* hdata = new TH1F("hdata","hdata",Nbins,x->getMin(),xmax); hdata->Sumw2();
    m_data->fillHistogram(hdata,RooArgList(*x));
    double mass_val = x->getMin();
    cout<<"okok 3"<<endl;

    double sumS = 0;
    double totalD = m_data->sumEntries();
    for( int i = 0 ; i < Nbins; i ++ ){
      x->setRange("range",mass_val,mass_val+binwidth);
      RooAbsReal* integral =  dynamic_cast<RooAbsReal*>(w->pdf("pdf_background_"+channelname)->createIntegral(RooArgSet(*x), NormSet(*x), Range("range"))) ;
      double weight = integral->getVal()*w->function("yield_background_"+channelname)->getVal();
      RooAbsReal* integralA =  dynamic_cast<RooAbsReal*>(pdfi->createIntegral(RooArgSet(*x), NormSet(*x), Range("range"))) ;
      double weightA = integralA->getVal()*totalD;
      sumS += weightA-weight;
      double value = hdata->GetBinContent(i+1);
      double error = hdata->GetBinError(i+1);
      if(value>0.5) {
	h1->SetBinContent(i+1,value-weight);
	h1->SetBinError(i+1,error);
      }
      mass_val+=binwidth;
    }
    cout<<"okok 4"<<endl;

    h1->GetYaxis()->SetRangeUser(-19,29);
    h1->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
    h1->GetYaxis()->SetTitle("Data - Bkg Fit");
    h1->GetYaxis()->SetTitleSize(0.075);
    h1->GetYaxis()->SetTitleOffset(0.80);
    h1->GetYaxis()->SetLabelSize(0.075);
    h1->GetXaxis()->SetTitleSize(0.075);
    h1->GetXaxis()->SetTitleOffset(0.9);
    h1->GetXaxis()->SetLabelSize(0.075);
    h1->SetLineWidth(1);
    RooPlot* frameS = x->frame(Bins(Nbins));
    //w->pdf("pdf_signal_"+channelname)->plotOn(frameS,LineColor(kRed),Normalization(sumS));
    w->pdf("pdf_signal_"+channelname)->plotOn(frameS,LineColor(kRed),Normalization(w->function("expectation_proc_signal_"+channelname)->getVal()));
    
    TH1F* hdummyS = new TH1F("hdummyS","hdummyS",Nbins,x->getMin(),xmax);
    TH1F* hdummyB = new TH1F("hdummyB","hdummyB",Nbins,x->getMin(),xmax);
    hdummyS->SetLineColor(kRed);
    hdummyS->SetLineWidth(2);
    hdummyB->SetLineColor(kBlue);
    hdummyB->SetLineWidth(2);
    TLegend* lg = new TLegend(0.55,0.6,0.9,0.9);
    lg->SetLineColor(0);
    lg->SetFillColor(0);
    lg->SetShadowColor(0);
    lg->AddEntry(h1,"Data","EP");
    lg->AddEntry(hdummyB,"Background","L");
    lg->AddEntry(hdummyS,"Signal+Background","L");


    TCanvas* c1 = new TCanvas("c1","c1",800,800);
    c1->cd();
  
    //double part = 0.45;
    //TPad *pad1 =  new TPad("pad1","pad1name",0.01,0.40*(1-part)+part,0.99,0.99*(1-part)+part);
    //TPad *pad2 =  new TPad("pad2","pad2name",0.01,0.05*(1-part)+part,0.99,0.402*(1-part)+part);
    TPad *pad1 =  new TPad("pad1","pad1name",0.01,0.40,0.99,0.99);
    TPad *pad2 =  new TPad("pad2","pad2name",0.01,0.05,0.99,0.402);
    pad1->Draw();
    pad2->Draw();

    pad1->SetBottomMargin(0.);
    pad1->cd();
    pad1->SetLogy();
    hframe->GetYaxis()->SetRangeUser(0.002,datai->sumEntries());
    hframe->Draw();
    frame->Draw("same");
    lg->Draw("same");
    pad1->RedrawAxis();
    pad1->Update();

    TLatex* text = new TLatex();
    TString textString = "#bf{#it{ATLAS}} Internal";
    text->SetNDC();
    text->SetTextFont(42);
    text->SetTextColor(kBlack);
    text->SetTextSize(0.05);
    text->DrawLatex(0.2,0.28,textString);
    textString = "#sqrt{s}=13 TeV, 3.2 fb^{-1}";
    text->DrawLatex(0.2,0.2,textString);
    if(inputFileName.Contains("HKHI")) textString="Spin-0 selection, ";
    if(inputFileName.Contains("EKHI")) textString="Spin-2 selection, ";
    textString += categoryTranslator(channelname);
    text->DrawLatex(0.2,0.12,textString);
    pad2->SetTopMargin(0.);
    pad2->cd();
    h1->Draw();
    TLine* l = new TLine(x->getMin(),0,xmax,0);
    l->SetLineColor(kBlue);
    l->SetLineWidth(2);
    l->Draw("same");
    frameS->Draw("same");
    pad2->RedrawAxis();
    pad2->Update();

    system("mkdir -vp fig/invmass/"+jobname);
    PrintCanvas(c1, "fig/invmass/"+jobname+"/"+channelname);

  }
}
