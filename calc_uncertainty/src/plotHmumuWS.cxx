#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"
#include "statistics.hh"

using namespace std;
using namespace RooFit;
using namespace RooStats;
using namespace CommonFunc;

RooAbsPdf * StripConstraints(RooAbsPdf &pdf, const RooArgSet &observables) { 
  const std::type_info & id = typeid(pdf);
 
  if (id == typeid(RooProdPdf)) {
 
    RooProdPdf *prod = dynamic_cast<RooProdPdf *>(&pdf);
    RooArgList list(prod->pdfList()); RooArgList newList;
 
    for (int i = 0, n = list.getSize(); i < n; ++i) {
      RooAbsPdf *pdfi = (RooAbsPdf *) list.at(i);
      RooAbsPdf *newPdfi = StripConstraints(*pdfi, observables);
      if(newPdfi != NULL) newList.add(*newPdfi);
    }
 
    if(newList.getSize() == 0) return NULL; // only constraints in product
    // return single component (no longer a product)
    else if(newList.getSize() == 1) return dynamic_cast<RooAbsPdf *>(newList.at(0)->clone(TString::Format("%s_unconstrained", 
													  newList.at(0)->GetName()))); 
    else return new RooProdPdf(TString::Format("%s_unconstrained", prod->GetName()).Data(),
			       TString::Format("%s without constraints", prod->GetTitle()).Data(), newList);
 
  } else if (id == typeid(RooExtendPdf)) {
 
    TIterator *iter = pdf.serverIterator(); 
    // extract underlying pdf which is extended; first server is the pdf; second server is the number of events variable
    RooAbsPdf *uPdf = dynamic_cast<RooAbsPdf *>(iter->Next());
    RooAbsReal *extended_term = dynamic_cast<RooAbsReal *>(iter->Next());
    assert(uPdf != NULL); assert(extended_term != NULL); assert(iter->Next() == NULL);
    delete iter;
          
    RooAbsPdf *newUPdf = StripConstraints(*uPdf, observables);
    if(newUPdf == NULL) return NULL; // only constraints in underlying pdf
    else return new RooExtendPdf(TString::Format("%s_unconstrained", pdf.GetName()).Data(),
				 TString::Format("%s without constraints", pdf.GetTitle()).Data(), *newUPdf, *extended_term);
          
  } else if (id == typeid(RooSimultaneous)) {    //|| id == typeid(RooSimultaneousOpt)) {
 
    RooSimultaneous *sim  = dynamic_cast<RooSimultaneous *>(&pdf); assert(sim != NULL);
    RooAbsCategoryLValue *cat = (RooAbsCategoryLValue *) sim->indexCat().Clone(); assert(cat != NULL);
    RooArgList pdfList;
 
    for (int ic = 0, nc = cat->numBins((const char *)NULL); ic < nc; ++ic) {
      cat->setBin(ic);
      RooAbsPdf* catPdf = sim->getPdf(cat->getLabel());
      RooAbsPdf* newPdf = NULL;
      // it is possible that a pdf is not defined for every category
      if (catPdf != NULL) newPdf = StripConstraints(*catPdf, observables);
      if (newPdf == NULL) { delete cat; return NULL; } // all channels must have observables
      pdfList.add(*newPdf);
    }
 
    return new RooSimultaneous(TString::Format("%s_unconstrained", sim->GetName()).Data(), 
			       TString::Format("%s without constraints", sim->GetTitle()).Data(), pdfList, *cat); 
 
  } else if (pdf.dependsOn(observables)) {  
    return (RooAbsPdf *) pdf.clone(TString::Format("%s_unconstrained", pdf.GetName()).Data());
  }
 
  return NULL; // just  a constraint term
}

double minimize(ModelConfig *mc, RooDataSet *data){
  unique_ptr<RooAbsReal> nll(mc->GetPdf()->createNLL(*data, Constrain(*mc->GetNuisanceParameters()), GlobalObservables(*mc->GetGlobalObservables())));
  nll->enableOffsetting(true);
  RooMinimizer minim(*nll);
  minim.setStrategy(1);
  minim.setPrintLevel(1);
  minim.setEps(1e-3);
  // minim.optimizeConst(2);
  int status=minim.minimize("Minuit2");
  return nll->getVal();
}

TString categoryMergger(TString channelname, int mode){
  if(mode==0) return channelname;
  else if(mode==1){
    if(channelname.Contains("VBF")) return "VBF";
    else return "ggF";
  }
  else return "inclusive";
}

TString categoryTranslator(TString channelname){
  if(channelname=="13TeV_SR_Central_LowPtll") return "Central low #it{p_{T}^{#mu#mu}}";
  if(channelname=="13TeV_SR_Central_MidPtll") return "Central medium #it{p_{T}^{#mu#mu}}";
  if(channelname=="13TeV_SR_Central_HighPtll") return "Central high #it{p_{T}^{#mu#mu}}";
  if(channelname=="13TeV_SR_Forward_LowPtll") return "Non-central low #it{p_{T}^{#mu#mu}}";
  if(channelname=="13TeV_SR_Forward_MidPtll") return "Non-central medium #it{p_{T}^{#mu#mu}}";
  if(channelname=="13TeV_SR_Forward_HighPtll") return "Non-central high #it{p_{T}^{#mu#mu}}";
  if(channelname=="13TeV_SR_VBF_Loose") return "VBF loose";
  if(channelname=="13TeV_SR_VBF_Tight") return "VBF tight";
  if(channelname=="ggF") return "Sum of ggF-enriched categories";
  if(channelname=="VBF") return "Sum of VBF-enriched categories";
  if(channelname=="inclusive") return "Inclusive spectrum";
}

int coefType(TString coefName){
  if(coefName.Contains("spusig")||coefName.Contains("spurious")) return 0; // Spurious signal
  else if(coefName.Contains("bkg")||coefName.Contains("background")) return 1; // Background
  else return 2;			      // Signal
}

void factorizePdf(vector<RooAbsPdf*> pdfArr, vector<RooRealVar*> obsArr, TString channelname, RooAddPdf*& sigPdf, RooAddPdf*& bkgPdf, double &nsig, double &nbkg){
  if(pdfArr.size()!=obsArr.size()) abort();
  RooArgList sigPdfSet, sigCoefSet, bkgPdfSet, bkgCoefSet;
  nsig=0;
  nbkg=0;
  for(unsigned int i=0;i<pdfArr.size();i++){
    RooAddPdf *sb=(RooAddPdf*)StripConstraints(*pdfArr[i],*obsArr[i]);
    // sb->Print();
    RooArgList coefList=sb->coefList();
    RooArgList pdfList=sb->pdfList();
    for(int j=0; j<coefList.getSize(); j++){
      RooAbsArg *coef=coefList.at(j);
      RooAbsArg *pdf=pdfList.at(j);
      int type=coefType(coef->GetName());
      if(type==1){
	bkgPdfSet.add(*pdf);
	bkgCoefSet.add(*coef);
	nbkg+=((RooAbsReal*)coef)->getVal();
      }
      else if(type==2){
	sigPdfSet.add(*pdf);
	sigCoefSet.add(*coef);
	nsig+=((RooAbsReal*)coef)->getVal();
      }
    }
    obsArr[i]->SetName("atlas_invMass_"+channelname); // Harmonize observable name
  }
  sigPdf=new RooAddPdf("sigPdf_"+channelname, "sigPdf", sigPdfSet, sigCoefSet);
  bkgPdf=new RooAddPdf("bkgPdf_"+channelname, "bkgPdf", bkgPdfSet, bkgCoefSet);
}

void addData(TH1D *hdata, vector<RooDataSet*> dataArr, vector<RooRealVar*> obsArr){
  if(dataArr.size()!=obsArr.size()) abort();
  for(unsigned int i=0; i<dataArr.size(); i++) dataArr[i]->fillHistogram(hdata, RooArgSet(*obsArr[i]));
  for( int i = 0 ; i < hdata->GetNbinsX(); i ++ ) hdata->SetBinError(i+1,sqrt(hdata->GetBinContent(i+1)));
}

void removeDuplicatedString(vector<TString>& strArr){sort(strArr.begin(), strArr.end()); strArr.erase(unique(strArr.begin(), strArr.end()), strArr.end());}

int main( int argc, char** argv ){
  if( argc<2 ){
    cout<<"Usage: "<<argv[0]<<" input_file"<<endl;
    exit(0);
  }
  TString jobname=argv[1];
  TString inputWSFileName=argv[2];
  int mode=atoi(argv[3]);

  RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
  double binwidth = 1;
  
  SetAtlasStyle();

  TFile* fin = TFile::Open(inputWSFileName);
  RooWorkspace* w = dynamic_cast<RooWorkspace*>(fin->Get("combined"));
  ModelConfig *mc=(ModelConfig*)w->obj("ModelConfig");
  RooDataSet* m_data = (RooDataSet*)w->data("obsDatabinned");
  RooSimultaneous* m_pdf = (RooSimultaneous*)mc->GetPdf();

  RooAbsCategoryLValue*  m_cat = (RooAbsCategoryLValue*)&m_pdf->indexCat();
  int numChannels = m_cat->numBins(0);

  TList* m_dataList = m_data->split( *m_cat, true );
  bool isBonly=false, doFit=false;

  w->var("mu")->setVal(0);
  w->var("mu")->setConstant(true);
  w->loadSnapshot("nominalNuis");
  statistics::fixSyst(mc);
  
  minimize(mc,m_data);

  w->var("mu")->setVal(1);	// Show SM signal
  w->var("mu")->setConstant(true);
  
  vector<TString> channelList;
  map<TString, vector<RooAbsPdf*>> pdfList;
  map<TString, vector<RooRealVar*>> obsList;
  map<TString, vector<RooDataSet*>> dataList;
  
  for ( int i= 0; i < numChannels; i++ ) {
    m_cat->setBin(i);
    TString channelname=m_cat->getLabel();
    
    RooAbsPdf* pdfi = m_pdf->getPdf(m_cat->getLabel());

    RooDataSet* datai = ( RooDataSet* )( m_dataList->At( i ) );
    std::cout << "\t\tIndex: " << i << ", Pdf: " << pdfi->GetName() << ", Data: " << datai->GetName()  << ", SumEntries: " << datai->sumEntries() << " NumEntries: "<< datai->numEntries() <<std::endl;
    RooRealVar *x=(RooRealVar*)pdfi->getObservables(datai)->first();

    TString transCateName=categoryMergger(channelname, mode);
    channelList.push_back(transCateName);
    pdfList[transCateName].push_back(pdfi);
    obsList[transCateName].push_back(x);
    dataList[transCateName].push_back(datai);
  }

  removeDuplicatedString(channelList);
  numChannels=channelList.size();
  
  for ( int i= 0; i < numChannels; i++ ) {
    TString channelname=channelList[i];
    RooRealVar *x=obsList[channelname].front();
    const int Nbins = ( x->getMax()-x->getMin() )/ binwidth;
    x->setBins(Nbins);
    TH1D* hdata = new TH1D("hdata_"+channelname,"hdata_"+channelname,Nbins,x->getMin(),x->getMax()); hdata->Sumw2();
    addData(hdata, dataList[channelname], obsList[channelname]);
    
    RooAddPdf *sigPdf=NULL, *bkgPdf=NULL;
    RooDataSet *data=NULL;
    double nSig=0, nBkg=0;
    factorizePdf(pdfList[channelname], obsList[channelname], channelname, sigPdf, bkgPdf, nSig, nBkg);

    cout<<channelname<<" "<<x<<" "<<sigPdf<<" "<<bkgPdf<<" "<<nSig<<" "<<nBkg<<endl;

    // Plotting
    TCanvas* c1 = new TCanvas("c1_"+channelname,"c1",800,800);
    c1->cd();
  
    //double part = 0.45;
    //TPad *pad1 =  new TPad("pad1","pad1name",0.01,0.40*(1-part)+part,0.99,0.99*(1-part)+part);
    //TPad *pad2 =  new TPad("pad2","pad2name",0.01,0.05*(1-part)+part,0.99,0.402*(1-part)+part);
    TPad *pad1 =  new TPad("pad1_"+channelname,"pad1name",0.01,0.40,0.99,0.99);
    TPad *pad2 =  new TPad("pad2_"+channelname,"pad2name",0.01,0.05,0.99,0.402);
    pad1->Draw();
    pad2->Draw();

    pad1->SetBottomMargin(0.);
    pad1->cd();
    // pad1->SetLogy();

    TH1D *hframe=new TH1D("hframe_"+channelname,"hframe", Nbins*10, x->getMin(), x->getMax());
    hframe->GetXaxis()->SetTitle("m_{#mu#mu} [GeV]");
    hframe->GetYaxis()->SetTitle(Form("Events / GeV"));
    hframe->SetLineWidth(0);

    hframe->GetYaxis()->SetRangeUser(0.001,hdata->Integral()/Nbins*4);
    hframe->Draw();

    RooPlot* frame = x->frame();
    frame->GetXaxis()->SetTitle("m_{#mu#mu} [GeV]");
    frame->GetYaxis()->SetTitle(Form("Events / GeV"));
    // data->plotOn(frame, Binning(Nbins), DataError(RooAbsData::Poisson));
    // cout<<hdata->Integral()<<" "<<integral->getVal()<<endl;

    cout<<"Plotting signal and background"<<endl;
    bkgPdf->plotOn(frame, Binning(Nbins), LineColor(kBlue), Normalization(hdata->Integral(), RooAbsReal::NumEvent), Name("Background"));
    sigPdf->plotOn(frame, Binning(Nbins), LineColor(kRed), Normalization(nSig*20, RooAbsReal::NumEvent), Name("Signal"));
    
    frame->Draw("same");    
    hdata->Draw("E,same");

    TLatex* text = new TLatex();
    TString textString = "#bf{#it{ATLAS}} Internal";
    text->SetNDC();
    text->SetTextFont(42);
    text->SetTextColor(kBlack);
    text->SetTextSize(0.05);
    text->DrawLatex(0.25,0.85,textString);
    textString = "#sqrt{s}=13 TeV, 79.8 fb^{-1}";
    text->DrawLatex(0.25,0.75,textString);

    text->DrawLatex(0.25,0.65,categoryTranslator(channelname));
    
    TLegend* lg = new TLegend(0.65,0.65,0.9,0.85);
    lg->SetTextSize(0.05);
    lg->SetLineColor(0);
    lg->SetFillColor(0);
    lg->SetShadowColor(0);
    lg->AddEntry(hdata,"Data","EP");
    lg->AddEntry("Background","Background","L");
    lg->AddEntry("Signal","SM signal #times 20","L");
    lg->Draw("same");


    pad1->RedrawAxis();
    pad1->Update();

    // Subpanel
    cout<<"Plotting sub-panel"<<endl;
    pad2->SetTopMargin(0.);
    pad2->cd();

    TH1D* h1 = new TH1D("h1_"+channelname,"h1",Nbins,x->getMin(),x->getMax()); h1->Sumw2();
    // double mass_val = x->getMin();

    bkgPdf->Print();
    TH1D *hbkg=(TH1D*)bkgPdf->createHistogram("hbkg_"+channelname, *x);
    hbkg->Sumw2();

    double ymax=1, ymin=1;
    for( int i = 0 ; i < Nbins; i ++ ){
      // x->setRange("range",mass_val,mass_val+binwidth);
      // RooAbsReal* integral =  dynamic_cast<RooAbsReal*>(bkgPdf->createIntegral(RooArgSet(*x), NormSet(*x), Range("range"))) ;
      // double weight = integral->getVal()*nBkg;
      double weight = hbkg->GetBinContent(i+1);
      double value = hdata->GetBinContent(i+1);
      double error = hdata->GetBinError(i+1);
      if(value>0.5) {
    	h1->SetBinContent(i+1,value/weight);
    	h1->SetBinError(i+1,error/weight);
      }
      if(value/weight>ymax) ymax=value/weight;
      if(value/weight<ymin) ymin=value/weight;
      // mass_val+=binwidth;
    }
    
    // h1->GetYaxis()->SetRangeUser(-19,29);
    double rangeY=max(fabs(1-(ymin-(1-ymin)*0.2)), fabs(1-(ymax+(ymax-1)*0.2)));
    h1->GetYaxis()->SetRangeUser(1-rangeY,1+rangeY);
    h1->GetXaxis()->SetTitle("m_{#mu#mu} [GeV]");
    h1->GetYaxis()->SetTitle("Data / Bkg Fit");
    h1->GetYaxis()->SetTitleSize(0.075);
    h1->GetYaxis()->SetTitleOffset(0.80);
    h1->GetYaxis()->SetLabelSize(0.075);
    h1->GetXaxis()->SetTitleSize(0.075);
    h1->GetXaxis()->SetTitleOffset(0.9);
    h1->GetXaxis()->SetLabelSize(0.075);
    h1->SetLineWidth(1);
    RooPlot* frameS = x->frame();
    //w->pdf("pdf_signal_"+channelname)->plotOn(frameS,LineColor(kRed),Normalization(sumS));
    h1->Draw();
    TLine* l = new TLine(x->getMin(),1,x->getMax(),1);
    l->SetLineColor(kBlue);
    l->SetLineWidth(2);
    l->Draw("same");
    frameS->Draw("same");
    
    // TH1D* hdummyS = new TH1D("hdummyS","hdummyS",Nbins,x->getMin(),x->getMax());
    // TH1D* hdummyB = new TH1D("hdummyB","hdummyB",Nbins,x->getMin(),x->getMax());
    // hdummyS->SetLineColor(kRed);
    // hdummyS->SetLineWidth(2);
    // hdummyB->SetLineColor(kBlue);
    // hdummyB->SetLineWidth(2);

    pad2->RedrawAxis();
    pad2->Update();

    system("mkdir -vp fig/invmass/"+jobname);
    PrintCanvas(c1, "fig/invmass/"+jobname+"/"+channelname);
  }
}
