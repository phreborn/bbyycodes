#include "CommonHead.h"
#include "CommonFunc.h"
#include "ToolsSignificanceHist.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"
#include "statistics.hh"

using namespace std;
using namespace CommonFunc;
using namespace RooFit;
using namespace RooStats;

double minimize(ModelConfig *mc, RooAbsData *data){
  unique_ptr<RooAbsReal> nll(mc->GetPdf()->createNLL(*data, Constrain(*mc->GetNuisanceParameters()), GlobalObservables(*mc->GetGlobalObservables())));
  nll->enableOffsetting(true);
  RooMinimizer minim(*nll);
  minim.setStrategy(1);
  minim.setPrintLevel(1);
  minim.setEps(1);
  // minim.optimizeConst(2);
  int status=minim.minimize("Minuit2");
  return nll->getVal();
}

TString translateCategory(TString channelname){
  if(channelname.Contains("inclusive")) return "Inclusive";
  else if(channelname.Contains("nonBB")) return "Non-barrel-barrel category";
  else if(channelname.Contains("BB")) return "Barrel-barrel category";
  else if(channelname.Contains("nonCC")) return "Non-central-central category";
  else if(channelname.Contains("CC")) return "Central-central category";
  else if(channelname.Contains("CostsLo")) return "|cos#theta*|<0.5 category";
  else if(channelname.Contains("CostsHi")) return "|cos#theta*|>0.5 category";
  else return channelname;
}

int main(int argc, char** argv){
  SetAtlasStyle();
  TString jobname=argv[1];
  TString inputFileName=argv[2];
  TString inputWSFileName=argv[3];
  TFile *f=TFile::Open(inputFileName,"r");

  TFile *fws=TFile::Open(inputWSFileName,"r");
  RooWorkspace* w = (RooWorkspace*)(fws->Get("combWS"));
  RooStats::ModelConfig* mc = (RooStats::ModelConfig*)(w->obj("ModelConfig"));
  RooDataSet* m_data = (RooDataSet*)w->data("combData");
  RooSimultaneous* m_pdf = (RooSimultaneous*)mc->GetPdf();
  RooArgSet* Observables=(RooArgSet*)mc->GetObservables();
  RooArgSet* POI=(RooArgSet*)mc->GetParametersOfInterest();
  RooRealVar* firstPOI=(RooRealVar*)POI->first();

  RooAbsCategoryLValue*  m_cat = (RooAbsCategoryLValue*)&m_pdf->indexCat();
  TList* m_dataList = m_data->split( *m_cat, true );
  const int ncat=m_cat->numBins(0);
  
  TH1D *hdata[ncat], *hmc[ncat], *hsig[ncat];

  TString selection="";
  if(inputFileName.Contains("EKHI")) selection="EKHI";
  if(inputFileName.Contains("HKHI")) selection="HKHI";

  w->loadSnapshot("ucmles");
  w->var("xs")->setVal(1);
  w->var("xs")->setConstant(true);
  RooArgSet *xss=(RooArgSet*)mc->GetParametersOfInterest()->selectByName("xs_*");
  TIterator *iter_poi=xss->createIterator();
  RooRealVar *poi=NULL;
  while((poi=dynamic_cast<RooRealVar*>(iter_poi->Next()))){
    poi->setRange(0,100);
    poi->setConstant(false);
  }
  if(xss->getSize()>1){
    if(inputWSFileName.Contains("Graviton")){
      statistics::setVal(w->var("mG"), 755.137, true);
      statistics::setVal(w->var("GkM"), 0.195114, true);
      
    }
    if(inputWSFileName.Contains("Scalar")){
      statistics::setVal(w->var("mX"), 748.561, true);
      statistics::setVal(w->var("wX"), 46.8064, true);
    }
    minimize(mc,m_data);
  }
  
  for(int icat=0; icat<ncat; icat++){
    m_cat->setBin(icat);
    TString channelname=m_cat->getLabel();
    RooAbsPdf* pdfi = m_pdf->getPdf(channelname);
    
    RooDataSet* datai = ( RooDataSet* )( m_dataList->At( icat ) );

    RooRealVar *x=(RooRealVar*)pdfi->getObservables(datai)->first();
    x->setMax(2000);
    
    hdata[icat]=(TH1D*)f->Get(Form("hdata_%d", ncat==1?1:icat));
    hmc[icat]=(TH1D*)f->Get(Form("hbkg_%d", ncat==1?1:icat));
    hsig[icat]=(TH1D*)f->Get(Form("hsig_%d", ncat==1?1:icat));

    hdata[icat]=ExpandTH1D(hdata[icat],x->getMin(),x->getMax());
    hmc[icat]=ExpandTH1D(hmc[icat],x->getMin(),x->getMax());
    hsig[icat]=ExpandTH1D(hsig[icat],x->getMin(),x->getMax());
    
    hdata[icat]->Rebin(4);
    hmc[icat]->Rebin(4);
    hsig[icat]->Rebin(4);

    std::cout << "\t\tIndex: " << icat << ", Pdf: " << pdfi->GetName() << ", Data: " << datai->GetName()  << ", SumEntries: " << datai->sumEntries() << " From hist: "<< hmc[icat]->Integral() <<std::endl;

    TCanvas* c1 = new TCanvas("c1","c1",800,600);
    c1->cd();
    //double part = 0.45;
    TPad *pad1 =  new TPad("pad1","pad1name",0.01,0.35,0.99,0.99);
    TPad *pad2 =  new TPad("pad2","pad2name",0.01,0.00,0.99,0.35);
    // TPad *pad3 =  new TPad("pad3","pad3name",0.01,0.10,0.99,0.352);
    pad1->Draw();
    pad2->Draw();

    pad1->Draw();
    pad2->Draw();

    pad1->SetBottomMargin(0.);
    pad1->cd();
    pad1->SetLogy();

    hmc[icat]->SetLineColor(kBlue);
    hmc[icat]->Draw("hist");
    // hsig[icat]->SetLineColor(kRed);
    // hsig[icat]->Draw("hist,same");

    // hdata[icat]->SetMarkerColor(kRed);
    // hdata[icat]->Draw("E,same");

    RooPlot *frame=x->frame();
    // x->setRange(hdata[icat]->GetXaxis()->GetXmin(), hdata[icat]->GetXaxis()->GetXmax());
    int Nbins=int((x->getMax()-x->getMin())/hdata[icat]->GetBinWidth(1));
    cout<<hdata[icat]->GetNbinsX()<<endl;
    datai->plotOn(frame, Binning(Nbins), DataError(RooAbsData::Poisson));
    pdfi->plotOn(frame, Components("pdf_background_"+channelname),LineColor(kMagenta),Name("fit"));
    datai->plotOn(frame, Binning(Nbins), DataError(RooAbsData::Poisson));

    frame->Draw("same");
    hmc[icat]->SetMaximum(hmc[icat]->GetMaximum()*5);
    hmc[icat]->SetMinimum(1e-2);
    
    hmc[icat]->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
    hmc[icat]->GetYaxis()->SetTitle(Form("Events / %.0f GeV", hmc[icat]->GetBinWidth(1)));
    hmc[icat]->GetYaxis()->SetLabelSize(0.06);
    hmc[icat]->GetYaxis()->SetTitleSize(0.07);
    hmc[icat]->GetYaxis()->SetTitleOffset(1.0);
    
    double x1,y1,x2,y2;
    GetX1Y1X2Y2(pad1, x1,y1,x2,y2);
  
    vector<TString> pavetext;
    pavetext.push_back("#bf{#it{ATLAS}} internal");
    pavetext.push_back("#sqrt{#it{s}} = 13 TeV, 3.2 fb^{-1}");
    pavetext.push_back(inputFileName.Contains("EKHI")?"Absolute p_{T} selection":"Relative p_{T} selection");
    pavetext.push_back(translateCategory(channelname));
    TPaveText* text=CreatePaveText(x2-0.45,y2-0.35,x2-0.05,y2-0.05,pavetext,0.06);
    text->Draw("same");
  
    TLegend *leg1 = FastLegend(x2-0.45, y2-0.5, x2-0.05, y2-0.35, 0.045);

    leg1->AddEntry(hdata[icat],"Data", "LEP");
    leg1->AddEntry(hmc[icat],"Sherpa LO #gamma#gamma + #gammaj + j#gamma + jj","L");
    leg1->AddEntry("fit","Bkg. model from S+B fit to data","L");
    leg1->Draw("same");

    pad1->RedrawAxis();
    pad1->Update();

    pad2->SetTopMargin(0.);
    pad2->SetBottomMargin(0.35);
    pad2->cd();

    TH1D *hfit=(TH1D*)hmc[icat]->Clone("fit");
    w->pdf("pdf_background_"+channelname)->fillHistogram(hfit,RooArgList(*x));
    ScaleTo(hfit, w->function("yield_background_"+channelname)->getVal());
    SignificanceHist *tool_fit=new SignificanceHist(*TH1DtoTH1F(hfit), *TH1DtoTH1F(hmc[icat]));

    SignificanceHist *tool=new SignificanceHist(*TH1DtoTH1F(hdata[icat]), *TH1DtoTH1F(hmc[icat]));
    // TGraphAsymmErrors *gr=tool->GetDiffHist();
    // gr->Draw("AP");

    TH1F *gr=tool->GetRatioHist(0.5);
    TH1F *gr_fit=tool_fit->GetRatioHist(0.5);
    // gr->Draw("E");
    gr_fit->SetLineColor(kMagenta);
    gr_fit->Draw("hist,same");
    pad2->RedrawAxis();
    pad2->Update();
    // DrawConstantLine(pad2,0,hdata[icat]->GetXaxis()->GetXmin(),hdata[icat]->GetXaxis()->GetXmax(),kBlue,1,3);
    DrawConstantLine(pad2,1,hdata[icat]->GetXaxis()->GetXmin(),hdata[icat]->GetXaxis()->GetXmax(),kBlue,1,3);
    DrawConstantLine(pad2,0.8,hdata[icat]->GetXaxis()->GetXmin(),hdata[icat]->GetXaxis()->GetXmax(),kRed,2,3);
    DrawConstantLine(pad2,1.2,hdata[icat]->GetXaxis()->GetXmin(),hdata[icat]->GetXaxis()->GetXmax(),kRed,2,3);
    // gr->Draw("E,same");
    gr_fit->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
    // gr->GetYaxis()->SetTitle("Data-MC");
    gr_fit->GetYaxis()->SetTitle("Fit/MC");
    gr_fit->GetYaxis()->SetTitleSize(0.150);
    gr_fit->GetYaxis()->SetTitleOffset(0.5);
    gr_fit->GetYaxis()->SetLabelSize(0.12);
    gr_fit->GetXaxis()->SetTitleSize(0.15);
    gr_fit->GetXaxis()->SetTitleOffset(1.0);
    gr_fit->GetXaxis()->SetLabelSize(0.15);
    // gr->GetYaxis()->SetRangeUser(-50,50);
    system("mkdir -vp fig/overlay/"+jobname+"/");
    PrintCanvas(c1, "fig/overlay/"+jobname+Form("/invmass_%s_%s",selection.Data(),channelname.Data()));
  }

  
}
