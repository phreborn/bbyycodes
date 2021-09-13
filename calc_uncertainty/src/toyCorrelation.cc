#include "CommonHead.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"
#include "statistics.hh"

const double epsilon=1e-5;

RooFitResult* profileToData(ModelConfig *mc, RooAbsData *data){
  RooSimultaneous* combPdf  =  (RooSimultaneous*)mc->GetPdf();
  RooArgSet* nuisanceParameters = (RooArgSet*)mc->GetNuisanceParameters();
  RooArgSet* globalObservables = (RooArgSet*)mc->GetGlobalObservables();
  unique_ptr<RooAbsReal> nll(combPdf->createNLL(*data, Constrain(*nuisanceParameters), GlobalObservables(*globalObservables), Extended(combPdf->canBeExtended())));
  nll->enableOffsetting(true);
  RooMinimizer minim(*nll);
  minim.optimizeConst(2);
  minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str());
  return minim.save();
}

void ReleaseTheGhost(RooDataSet *obsdata, RooRealVar *x, RooRealVar *w, int nbin, double ghostwt){
  double xmin=x->getMin(), xmax=x->getMax();
  TH1F h_data("h_data","",nbin,xmin,xmax);
  RooArgSet* obs = (RooArgSet*)obsdata->get();
  RooRealVar* xdata = (RooRealVar*)obs->find(x->GetName());
  int nevt1=obsdata->numEntries();
  for (int i=0 ; i<nevt1 ; i++) {
    obsdata->get(i) ;
    h_data.Fill( xdata->getVal() );
  }
  for( int ibin = 1 ; ibin < nbin ; ibin++) {
    if(h_data.GetBinContent(ibin)==0){
      x->setVal(h_data.GetBinCenter(ibin));
      w->setVal(ghostwt);
      obsdata -> add( RooArgSet(*x,*w), ghostwt);
    }
  }
  int nevt2=obsdata->numEntries();

  obsdata->Print();
}

RooAbsData* generateToyData( ModelConfig *mc, bool m_binned=false, bool m_ghost=false){
  RooSimultaneous* combPdf  =  (RooSimultaneous*)mc->GetPdf();
  RooArgSet* nuisanceParameters = (RooArgSet*)mc->GetNuisanceParameters();
  RooArgSet* globalObservables = (RooArgSet*)mc->GetGlobalObservables();
  RooArgSet* Observables = (RooArgSet*)mc->GetObservables();
  RooArgSet* nuisanceParameters_original_values = (RooArgSet*)mc->GetNuisanceParameters()->snapshot();
 
  statistics::constSet(nuisanceParameters,true);  // Fix nuisance parameters before randomize global observables.
  statistics::constSet(globalObservables,false);  // Release global observables before randomize global observables.

  map<string,RooDataSet*> toydatasetMap; 
  RooCategory* m_cat=(RooCategory*)&combPdf->indexCat();
  
  unique_ptr<TIterator> iter(combPdf->indexCat().typeIterator());
  RooCatType* tt = NULL;
  vector<shared_ptr<RooDataSet> > datai;
  // loop over all channels
  int idx=0;
  // if(m_debug){
  //   globalObservables->Print("v");
  //   combPdf->Print();
  // }
  while((tt=dynamic_cast<RooCatType*>(iter->Next()))) {
    cout<<idx<<" "<<tt->GetName()<<endl;
    RooAbsPdf* pdfi = combPdf->getPdf(tt->GetName()) ;
    RooArgSet* obsi = pdfi->getObservables( Observables ) ;  
    RooArgSet* gloi = pdfi->getObservables( globalObservables ); // this is very important
    statistics::randomizeSet(pdfi,gloi,-1);  
    statistics::constSet(gloi,true);  
    RooRealVar w("w","w",1);
    RooRealVar *x=dynamic_cast<RooRealVar*>(obsi->first());
    
    if(m_binned){
      pdfi->setAttribute("PleaseGenerateBinned") ;
      datai.push_back(shared_ptr<RooDataSet>(pdfi->generate(*obsi,AutoBinned(true),Extended(pdfi->canBeExtended()),GenBinned("PleaseGenerateBinned"))));
    }
    else{
      unique_ptr<RooDataSet> data_tmp(pdfi->generate(*obsi,Extended(true)));
      RooArgSet* obs_tmp = const_cast<RooArgSet*>(data_tmp->get());
      RooRealVar* xdata_tmp = dynamic_cast<RooRealVar*>(obs_tmp->first()); // We only have one observable in total, so it is okay
      shared_ptr<RooDataSet> data(new RooDataSet("data","data",RooArgSet(*x,w),WeightVar(w)));
      
      for (int i=0 ; i<data_tmp->numEntries() ; i++) {
	data_tmp->get(i) ;
	x->setVal(xdata_tmp->getVal());
	double weight=data_tmp->weight();
	w.setVal(weight);
	data->add( RooArgSet(*x ,w) , weight);
      }
      // TCanvas *c=new TCanvas("c","c",800,600);
      // RooPlot *frame=x->frame();
      // data->plotOn(frame);
      // pdfi->plotOn(frame);
      // frame->Draw();
      // c->SaveAs(TString(tt->GetName())+".pdf");
      datai.push_back(data);
      if(m_ghost) ReleaseTheGhost(datai[idx].get(), x, &w, 1000, 1e-6);
    }
    toydatasetMap[(string)tt->GetName()] = datai[idx].get();
    idx++;
  }

  RooRealVar wt("wt","wt",1); 
  RooArgSet args;
  args.add(*Observables);
  args.add(wt);
  RooDataSet* toyData = new RooDataSet("toyData", "", args, Index(*m_cat), Import(toydatasetMap), WeightVar(wt));

  statistics::constSet(nuisanceParameters,false);  // release nuisance parameters
  return toyData;
}

int main( int argc , char **argv)
{
  if(argc<3){
    cout<<"Usage: "<<argv[0]<<" <seed> <inputFile> <option>"<<endl;
    return 0;
  }
    
  ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit2");
  ROOT::Math::MinimizerOptions::SetDefaultStrategy(1);
  ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(-1);
    
  int seed = atoi(argv[1]);
  TString inputFile=argv[2];

  TString wname="combWS";
  TString mname="ModelConfig";
  TString dname="combData";

  TString option=argv[argc-1];
  option.ToLower();

  bool m_binned=true;
  bool m_ghost=true;

  if(m_binned) cout<<"REGTEST: using binned data."<<endl;

  TFile fOutputFile("outcome.root","recreate") ;

  TFile f(inputFile,"read");
  RooWorkspace *w = dynamic_cast<RooWorkspace*>(f.Get(wname));    
  ModelConfig* mc = dynamic_cast<ModelConfig*>(w->obj(mname));
  RooAbsData *obsData = w->data(dname);

  RooArgSet nuisAndPOIAndGlob;
  nuisAndPOIAndGlob.add(*mc->GetParametersOfInterest());
  nuisAndPOIAndGlob.add(*mc->GetNuisanceParameters());
  nuisAndPOIAndGlob.add(*mc->GetGlobalObservables());
  
  w->loadSnapshot("nominalNuis");
  w->loadSnapshot("nominalGlobs");
  TIterator *iter=mc->GetParametersOfInterest()->createIterator();
  RooRealVar *parg=NULL;
  while((parg=(RooRealVar*)iter->Next())) parg->setVal(1);
    
  w->saveSnapshot("Origin",nuisAndPOIAndGlob);
  cout<<"Snapshot \"Origin\" saved."<<endl;

  RooRandom::randomGenerator() -> SetSeed(seed) ; // This step is necessary
      
  w->loadSnapshot("Origin");
  unique_ptr<RooAbsData> toyData(generateToyData(mc, m_binned, m_ghost));
  toyData->Print();
  RooFitResult *res=profileToData(mc, toyData.get());
  res->SetName("fitResult");
  fOutputFile.cd();
  res->Write();
  fOutputFile.Close();
  
  f.Close();
  return 0 ;
}

