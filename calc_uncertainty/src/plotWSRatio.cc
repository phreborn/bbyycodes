#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"
#include "statistics.hh"

using namespace std;
using namespace RooFit;
using namespace RooStats;
using namespace CommonFunc;

double minimize(ModelConfig *mc, RooAbsData *data){
  unique_ptr<RooAbsReal> nll(mc->GetPdf()->createNLL(*data, Constrain(*mc->GetNuisanceParameters()), GlobalObservables(*mc->GetGlobalObservables())));
  nll->enableOffsetting(true);
  RooMinimizer minim(*nll);
  minim.setStrategy(0);
  minim.setPrintLevel(1);
  minim.setEps(1);
  // minim.optimizeConst(2);
  int status=minim.minimize("Minuit2");
  return nll->getVal();
}

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
  TString inputWSFileName=argv[2];
  TString option=argv[3];
  
  // RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
  double binwidth = 20, xmax=200;
  if(inputWSFileName.Contains("histfactory")) xmax=2700;
  else{
    if(inputWSFileName.Contains("EKHI")) xmax=2490;
    else xmax=2700;
  }
  
  SetAtlasStyle();

  TFile* fin = TFile::Open(inputWSFileName);
  RooWorkspace* w = dynamic_cast<RooWorkspace*>(fin->Get("combWS"));
  ModelConfig *mc=(ModelConfig*)w->obj("ModelConfig");
  RooDataSet* m_data = (RooDataSet*)w->data("combDatabinned");
  RooSimultaneous* m_pdf = (RooSimultaneous*)mc->GetPdf();

  RooAbsCategoryLValue*  m_cat = (RooAbsCategoryLValue*)&m_pdf->indexCat();
  int numChannels = m_cat->numBins(0);

  TList* m_dataList = m_data->split( *m_cat, true );
  bool isBonly=false, doFit=false;

  if(option.Contains("bonly")){
    if(option.Contains("prefit")){
      w->loadSnapshot("nominalNuis");
      w->loadSnapshot("nominalGlobs");
    }
    else{
      doFit=!bool(w->loadSnapshot("ucmles_0"));
      if(doFit){
	w->var("mG")->setVal(750);
	w->var("GkM")->setVal(0.2);
	w->var("xs")->setVal(0);
	w->var("mG")->setConstant(true);
	w->var("GkM")->setConstant(true);
	w->var("xs")->setConstant(true);
	statistics::constSet((RooArgSet*)w->allVars().selectByName("gamma*"), true);
	// w->var("alpha_bkg_irreducible_13TeV")->setVal(0);
	// w->var("alpha_bkg_irreducible_13TeV")->setConstant(1);
	w->var("alpha_bkg_reducible_13TeV")->setVal(0);
	w->var("alpha_bkg_reducible_13TeV")->setConstant(1);
	// w->var("alpha_bkg_purity_13TeV")->setVal(0);
	// w->var("alpha_bkg_purity_13TeV")->setConstant(1);
	// w->var("alpha_bkg_isolation_13TeV")->setVal(0);
	// w->var("alpha_bkg_isolation_13TeV")->setConstant(1);
	
      }
    }
    isBonly=true;
  }
  else isBonly=!(w->loadSnapshot("ucmles"));

  // w->var("xs")->setVal(1);
  // w->var("xs")->setConstant(true);
  // RooArgSet *xss=(RooArgSet*)mc->GetParametersOfInterest()->selectByName("xs_*");
  // TIterator *iter_poi=xss->createIterator();
  // RooRealVar *poi=NULL;
  // while((poi=dynamic_cast<RooRealVar*>(iter_poi->Next()))){
  //   poi->setRange(0,100);
  //   poi->setConstant(false);
  // }
  // if(xss->getSize()>1){
  //   if(inputWSFileName.Contains("Graviton")){
  //     statistics::setVal(w->var("mG"), 755.137, true);
  //     statistics::setVal(w->var("GkM"), 0.195114, true);
      
  //   }
  //   if(inputWSFileName.Contains("Scalar")){
  //     statistics::setVal(w->var("mX"), 748.561, true);
  //     statistics::setVal(w->var("wX"), 46.8064, true);
  //   }
  if(doFit) minimize(mc,m_data);
  // }
  
  for ( int i= 0; i < numChannels; i++ ) {
    m_cat->setBin(i);
    TString channelname=m_cat->getLabel();
    RooAbsPdf* pdfi = m_pdf->getPdf(m_cat->getLabel());

    RooDataSet* datai = ( RooDataSet* )( m_dataList->At( i ) );
    std::cout << "\t\tIndex: " << i << ", Pdf: " << pdfi->GetName() << ", Data: " << datai->GetName()  << ", SumEntries: " << datai->sumEntries() << " NumEntries: "<< datai->numEntries() <<std::endl;
    RooRealVar *x=(RooRealVar*)pdfi->getObservables(datai)->first();
  
    cout<<"okok 1"<<endl;
    const int Nbins = ( xmax-x->getMin() )/ binwidth;
    TH1D *hframe=new TH1D("hframe","hframe", Nbins*10, x->getMin(), xmax);
    hframe->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
    hframe->GetYaxis()->SetTitle(Form("Events / %.0f GeV",binwidth));
    x->setMax(xmax);
    // x->setBins(Nbins);
    RooPlot* frame = x->frame(Binning(Nbins));
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
    pdfi->plotOn(frame,LineColor(kBlue), Components("pdf__background_"+channelname));
    if(!isBonly) pdfi->plotOn(frame,LineColor(kRed));
    // cout<<"okok 1.5 "<<w->function("expectation__proc_signal_"+channelname)->getVal()+w->function("yield_background_"+channelname)->getVal()<<endl;
    datai->plotOn(frame, Binning(Nbins), DataError(RooAbsData::Poisson));
    cout<<"okok 2"<<endl;

    TH1F* h1 = new TH1F("h1","h1",Nbins,x->getMin(),xmax); h1->Sumw2();
    TH1F* hdata = new TH1F("hdata","hdata",Nbins,x->getMin(),xmax); hdata->Sumw2();
    datai->fillHistogram(hdata,RooArgList(*x));
    for( int i = 0 ; i < Nbins; i ++ ) hdata->SetBinError(i+1,sqrt(hdata->GetBinContent(i+1)));
    double mass_val = x->getMin();
    cout<<"okok 3"<<endl;

    double sumS = 0;
    double totalD = datai->sumEntries();
    for( int i = 0 ; i < Nbins; i ++ ){
      x->setRange("range",mass_val,mass_val+binwidth);
      RooAbsReal* integral =  dynamic_cast<RooAbsReal*>(w->pdf("pdf__background_"+channelname)->createIntegral(RooArgSet(*x), NormSet(*x), Range("range"))) ;
      double weight = integral->getVal()*w->function("yield__background_"+channelname)->getVal();
      RooAbsReal* integralA =  dynamic_cast<RooAbsReal*>(pdfi->createIntegral(RooArgSet(*x), NormSet(*x), Range("range"))) ;
      double weightA = integralA->getVal()*totalD;
      sumS += weightA-weight;
      double value = hdata->GetBinContent(i+1);
      double error = hdata->GetBinError(i+1);
      if(value>0.5) {
	h1->SetBinContent(i+1,weight);
	// h1->SetBinError(i+1,error);
      }
      mass_val+=binwidth;
    }
    cout<<"okok 4"<<endl;
    TH1D* hsub=(TH1D*)hdata->Clone("hsub");
    hsub->Sumw2();
    hsub->Divide(h1);
    hsub->GetYaxis()->SetRangeUser(0,2);
    hsub->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
    hsub->GetYaxis()->SetTitle("Data - Bkg Fit");
    hsub->GetYaxis()->SetTitleSize(0.075);
    hsub->GetYaxis()->SetTitleOffset(0.80);
    hsub->GetYaxis()->SetLabelSize(0.075);
    hsub->GetXaxis()->SetTitleSize(0.075);
    hsub->GetXaxis()->SetTitleOffset(0.9);
    hsub->GetXaxis()->SetLabelSize(0.075);
    hsub->SetLineWidth(1);
    RooPlot* frameS = x->frame(Binning(Nbins));
    //w->pdf("pdf_signal_"+channelname)->plotOn(frameS,LineColor(kRed),Normalization(sumS));
    if(!isBonly) w->pdf("pdf_signal_"+channelname)->plotOn(frameS,LineColor(kRed),Normalization(w->function("yield_signal_"+channelname)->getVal()/Nbins*x->numBins()));
    
    TH1F* hdummyS = new TH1F("hdummyS","hdummyS",Nbins,x->getMin(),xmax);
    TH1F* hdummyB = new TH1F("hdummyB","hdummyB",Nbins,x->getMin(),xmax);
    hdummyS->SetLineColor(kRed);
    hdummyS->SetLineWidth(2);
    hdummyB->SetLineColor(kBlue);
    hdummyB->SetLineWidth(2);
    TLegend* lg = new TLegend(0.55,0.75,0.9,0.9);
    lg->SetLineColor(0);
    lg->SetFillColor(0);
    lg->SetShadowColor(0);
    lg->AddEntry(h1,"Data","EP");
    lg->AddEntry(hdummyB,"Background","L");
    if(!isBonly) lg->AddEntry(hdummyS,"Signal+Background","L");


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
    if(option.Contains("2015")&&channelname.Contains("2015")){
      textString = "Data 2015, #sqrt{s}=13 TeV, 3.2 fb^{-1}";
      text->DrawLatex(0.2,0.2,textString);
    }
    else if(option.Contains("2016")&&channelname.Contains("2016")){
      textString = "Data 2016, #sqrt{s}=13 TeV, 33.9 fb^{-1}";
      text->DrawLatex(0.2,0.2,textString);
    }
    else if(option.Contains("1516")){
      textString = "#sqrt{s}=13 TeV, 15.5 fb^{-1}";
      text->DrawLatex(0.2,0.2,textString);
    }
    if(inputWSFileName.Contains("EKEI_minus_EKHI")) textString="Spin-2 Loose-not-Tight Selection";
    else if(inputWSFileName.Contains("EKHI"))       textString="Spin-2 Selection";
    else if(inputWSFileName.Contains("EKEI"))       textString="Spin-2 Loose Selection";
    else                                            textString="Spin-0 Selection";
    if(option.Contains("EEOS")) textString += ", Endcap-Endcap opposite sign";
    if(option.Contains("prefit")) textString += ", pre-fit";
    if(option.Contains("postfit")) textString += ", post-fit";
    text->DrawLatex(0.2,0.12,textString);

    if(option.Contains("lowpu")) text->DrawLatex(0.2,0.05,"Low pileup");
    if(option.Contains("highpu")) text->DrawLatex(0.2,0.05,"High pileup");
    if(option.Contains("medpu")) text->DrawLatex(0.2,0.05,"Medium pileup");
    pad2->SetTopMargin(0.);
    pad2->cd();
    hsub->Draw();
    TLine* l = new TLine(x->getMin(),1,xmax,1);
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
