#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"
#include "titleList.hh"
#include "statistics.hh"

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
  minim.setEps(0.1);
  minim.optimizeConst(2);
  
  int status = minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());
  return status;
}

int main(int argc, char**argv){
  ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit2");
  ROOT::Math::MinimizerOptions::SetDefaultStrategy(2);
  ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(1);

  TString jobname=argv[1];

  TString inputWSFileName=argv[2];
  TString inputSigFileName=argv[3];

  TString config1=argv[4];
  TString config2=argv[5];
  
  TString option=argv[6];

  map<TString,TString> title=createTitleList();
  
  vector<TString> config1Arr=CommonFunc::SplitString(config1,'=');
  vector<TString> config2Arr=CommonFunc::SplitString(config2,'=');
  
  TString var1Name=config1Arr[0], var2Name=config2Arr[0];
  double var1Value=config1Arr[1].Atof(), var2Value=config2Arr[1].Atof();

  TString inputLimitFile=Form("limit/high_mass_diphoton_Graviton_13TeV_histfactory_2dlimit_v1/high_mass_diphoton_Graviton_13TeV_histfactory_2dlimit_v1_%.2f_%.2f.txt", var1Value, var2Value);

  ifstream flimit(inputLimitFile);

  double expLimit;
  TString dummy;
  flimit>>dummy>>dummy>expLimit;
  flimit.close();
  
  CommonFunc::SetAtlasStyle();

  TString wname="combWS", mname="ModelConfig", dname="AsimovB";

  TFile *f=TFile::Open(inputWSFileName);
  RooWorkspace *w=(RooWorkspace*)f->Get(wname);

  ModelConfig *mc=(ModelConfig*)w->obj(mname);
  RooDataSet* m_data = (RooDataSet*)w->data(dname);
  RooSimultaneous* m_pdf = (RooSimultaneous*)mc->GetPdf();

  RooAbsCategoryLValue*  m_cat = (RooAbsCategoryLValue*)&m_pdf->indexCat();
  int numChannels = m_cat->numBins(0);

  TList* m_dataList = m_data->split( *m_cat, true );

  system("mkdir -vp fig/"+jobname);
  
  RooRealVar *obs[50], *wt[50];
  RooDataSet *data[50];
  RooCategory channellist("channellist","channellist");
  map<string, RooDataSet*> datasetMap;

  double totalEvt[50];

  w->loadSnapshot("ucmles_0");
  // statistics::constSet((RooArgSet*)mc->GetNuisanceParameters(),true);
  w->var(var1Name)->setConstant(false);
  w->var(var2Name)->setConstant(false);
  w->var("xs")->setConstant(false);

  w->var("xs")->setRange(0,1000);
  w->var(var1Name)->setRange(var1Value-var1Value*0.1, var1Value+var1Value*0.1);
  w->var(var2Name)->setRange(var2Value-var2Value*0.8, var2Value+var2Value*0.8);
  w->var(var1Name)->setVal(var1Value);
  w->var(var2Name)->setVal(var2Value);

  if(option.Contains("fixfirst")){
    cout<<"Fixing "<<var1Name<<endl;
    w->var(var1Name)->setConstant(true);
  }
  if(option.Contains("fixsecond")){
    cout<<"Fixing "<<var2Name<<endl;
    w->var(var2Name)->setConstant(true);
  }
  
  RooArgSet obserables;

  for ( int i= 0; i < numChannels; i++ ) {
    m_cat->setBin(i);
    TString channelname=m_cat->getLabel();
    RooAbsPdf* pdfi = m_pdf->getPdf(m_cat->getLabel());
    RooDataSet* datai = ( RooDataSet* )( m_dataList->At( i ) );

    RooRealVar *x=(RooRealVar*)pdfi->getObservables(datai)->first();

    obs[i]=x;
    wt[i]=new RooRealVar(Form("w_%d",i), Form("w_%d",i), 1);
    obserables.add(*obs[i]);

    data[i]=new RooDataSet(Form("data_%d",i), Form("data_%d",i), RooArgList(*obs[i],*wt[i]),WeightVar(*wt[i]));

    RooRealVar* xdata=(RooRealVar*)(datai->get()->find(x->GetName()));
    int nevt=datai->numEntries();
    for(int ievt=0;ievt<nevt;ievt++){
      datai->get(ievt);
      obs[i]->setVal(xdata->getVal());
      double weight=datai->weight();
      wt[i]->setVal(weight);

      data[i]->add(RooArgList(*obs[i], *wt[i]), weight);
    }
    
    ifstream fin(inputSigFileName);
    cout<<inputSigFileName<<endl;
    assert(fin);
    double mass, weight;
    totalEvt[i]=0;
    while((fin>>mass>>weight)){
      weight/=100.;		// It is too large. cannot fit
      obs[i]->setVal(mass);
      wt[i]->setVal(weight);
      if(mass>obs[i]->getMin()&&mass<obs[i]->getMax()){
	data[i]->add(RooArgSet(*obs[i], *wt[i]), weight);
	totalEvt[i]+=weight;
      }
    }
    cout<<"There are "<<totalEvt[i]<<" signal events injected"<<endl;
    channellist.defineType(channelname);
    // cout<<data[i]->sumEntries()<<endl; getchar();
    datasetMap[channelname.Data()]=data[i];
  }
  RooRealVar weight("wt","wt",1);  
  RooArgSet args;
  args.add(obserables);
  args.add(weight);

  RooDataSet injectData("injectData","",args, Index(channellist), Import(datasetMap), WeightVar(weight));

  injectData.Print("v");
  // cout<<injectData.sumEntries()<<endl; getchar();
  unique_ptr<RooAbsReal> nll(m_pdf->createNLL(injectData, Constrain(*mc->GetNuisanceParameters()), GlobalObservables(*mc->GetGlobalObservables())));
  nll->enableOffsetting(true);
  minimize(nll.get());
  
  ofstream fout("fig/"+jobname+Form("/summary_%.2f_%.2f.txt",var1Value,var2Value));
  fout<<"Var \t Input \t Output"<<endl;
  fout<<Form("mG \t %.2f \t %.2f+/-%.2f", var1Value, w->var("mG")->getVal(), w->var("mG")->getError())<<endl;;
  fout<<Form("GkM \t %.2f \t %.2f+/-%.2f", var2Value, w->var("GkM")->getVal(), w->var("GkM")->getError())<<endl;;
  fout<<Form("Nsig \t %.2f \t %.2f+/-%.2f", totalEvt[0], w->var("xs")->getVal(), w->var("xs")->getError())<<endl;;


  m_dataList=injectData.split(channellist);

  for ( int i= 0; i < numChannels; i++ ) {
    channellist.setBin(i);
    TString channelname=channellist.getLabel();
    RooAbsPdf* pdfi = m_pdf->getPdf(channellist.getLabel());
    RooDataSet* datai = ( RooDataSet* )( m_dataList->At( i ) );

    RooRealVar *x=(RooRealVar*)pdfi->getObservables(datai)->first();

    TCanvas *c=new TCanvas(Form("c%d",i),channelname,800,600);
    TH1F *hframe=new TH1F("hframe","", 1600, 150, 2500);
    hframe->SetMinimum(0.1);
    hframe->SetMaximum(5e4);
    // hframe->SetMaximum(1.2e4);
    hframe->Draw();
    hframe->GetXaxis()->SetTitle(title[var1Name]);
    hframe->GetYaxis()->SetTitle("Events / 50 GeV");
    hframe->SetLineWidth(0);
    
    RooPlot *frame=x->frame();
    // frame->GetXaxis()->SetTitle("m_X [GeV]")
    datai->plotOn(frame, DataError(RooAbsData::Poisson), Binning(47));
    pdfi->plotOn(frame,LineColor(kRed));

    pdfi->plotOn(frame,Components("pdf_background_inclusive_13TeV"),LineColor(kBlue));

    double x1, y1, x2, y2;
    CommonFunc::GetX1Y1X2Y2(c,x1,y1,x2,y2);

    vector<TString> pavetext;
    pavetext.push_back("#bf{#it{ATLAS}} internal");
    pavetext.push_back("#sqrt{#it{s}} = 13 TeV, 3.2 fb^{-1}");
    pavetext.push_back(Form("%s=%.2f, %s=%.2f", title[var1Name].Data(), var1Value, title[var2Name].Data(), var2Value));
    TPaveText* text=CommonFunc::CreatePaveText(x2-0.5,y2-0.3,x2-0.03,y2-0.05,pavetext,0.045);
    
    c->cd();
    frame->Draw("same");
    text->Draw("same");
    c->SetLogy();
    TString outputCanvasName="fig/"+jobname+Form("/plot_%.2f_%.2f",var1Value,var2Value);
    CommonFunc::PrintCanvas(c,outputCanvasName);
  }
}



