#ifndef TOYTTH_H
#define TOYTTH_H
#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"

#include "statistics.hh"

using namespace std;
using namespace RooFit;
using namespace RooStats;
using namespace CommonFunc;

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
  RooCategory channellist("channellist","channellist");
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
    channellist.defineType(tt->GetName()) ;     
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
  RooDataSet* toyData = new RooDataSet("toyData", "", args, Index(channellist), Import(toydatasetMap), WeightVar(wt));

  statistics::constSet(nuisanceParameters,false);  // release nuisance parameters
  return toyData;
}

map<string,double> calcTestStat(RooWorkspace *w, ModelConfig *mc, RooAbsData *data, double mu, vector<string> *namenp, vector<double> *valuenpfix,vector<double> *valuenphat, TString option){
  RooAbsPdf* combPdf = mc->GetPdf();
  RooArgSet* nuisanceParameters = (RooArgSet*)mc->GetNuisanceParameters();
  RooArgSet* globalObservables = (RooArgSet*)mc->GetGlobalObservables();
  RooArgSet* Observables = (RooArgSet*)mc->GetObservables();
  RooArgSet* nuisanceParameters_original_values = (RooArgSet*)mc->GetNuisanceParameters()->snapshot();
  RooArgSet* poi=(RooArgSet*)mc->GetParametersOfInterest();
  RooRealVar* firstpoi=(RooRealVar*)poi->first();

  RooArgSet* nuisESS=(RooArgSet*)nuisanceParameters->selectByName("atlas_EM_*");
  RooArgSet* nuisRes=(RooArgSet*)nuisanceParameters->selectByName("atlas_mRes");
  RooArgSet* nuisSpurious=(RooArgSet*)nuisanceParameters->selectByName("atlas_bias_*");
//   RooRealVar* obs=(RooRealVar*)Observables->find("obs_x_atlas_costs_1265");
  bool m_noess=option.Contains("noess");
  bool m_nospurious=option.Contains("nospurious");
  bool m_nores=option.Contains("nores");

  // +++++++++++++++++++++++ Step 2: Fit toy data ++++++++++++++++++++++++

  cout<<"Fixed POI..."<<endl;
  w->loadSnapshot("Origin");
  statistics::constSet(nuisanceParameters,false);  // release nuisance parameters before fit
  statistics::constSet(globalObservables,true);  // fix global observables before fit
  if(m_noess) statistics::constSet(nuisESS,true);
  if(m_nores) statistics::constSet(nuisRes,true);
  if(m_nospurious) statistics::constSet(nuisSpurious,true);
  firstpoi->setVal(mu);
  firstpoi->setConstant(true);

  unique_ptr<RooAbsReal> nll(combPdf->createNLL(*data, Constrain(*nuisanceParameters), GlobalObservables(*globalObservables), Extended(combPdf->canBeExtended())));
  nll->enableOffsetting(true);
  unique_ptr<RooMinimizer> minim(new RooMinimizer(*nll));

  int statusfix=minim->minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());

  double NLLfix = nll->getVal();

  unique_ptr<TIterator> iter(nuisanceParameters -> createIterator());
  RooRealVar* parg_nuifix_fix = NULL;
  while((parg_nuifix_fix=(RooRealVar*)iter->Next()) ){
    namenp->push_back(parg_nuifix_fix->GetName());
    valuenpfix->push_back(parg_nuifix_fix->getVal());
  }

  cout<<"Free POI..."<<endl;  
  w->loadSnapshot("Origin");
  statistics::constSet(nuisanceParameters,false);  // release nuisance parameters before fit
  statistics::constSet(globalObservables,true);  // fix global observables before fit
  if(m_noess) statistics::constSet(nuisESS,true);
  if(m_nores) statistics::constSet(nuisRes,true);
  if(m_nospurious) statistics::constSet(nuisSpurious,true);
  firstpoi->setVal(mu); 
  firstpoi->setConstant(false);

  nll.reset(combPdf->createNLL(*data, Constrain(*nuisanceParameters), Extended(combPdf->canBeExtended())));
  nll->enableOffsetting(true);
  minim.reset(new RooMinimizer(*nll));

  int statushat=minim->minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());

  double NLLhat = nll->getVal();

  double muhat=firstpoi->getVal();

  iter.reset(nuisanceParameters -> createIterator());
  RooRealVar* parg_nuifix_hat = NULL;
  while((parg_nuifix_hat=(RooRealVar*)iter->Next()) ){
    valuenphat->push_back(parg_nuifix_hat->getVal());
  }

  map<string,double> result ;
  result["nllfix"] = NLLfix; 
  result["nllhat"] = NLLhat;
  result["muhat"] = muhat;
  result["statusfix"]=statusfix;
  result["statushat"]=statushat;
  return result;
}

double profileToData(ModelConfig *mc, RooAbsData *data){
  RooSimultaneous* combPdf  =  (RooSimultaneous*)mc->GetPdf();
  RooArgSet* nuisanceParameters = (RooArgSet*)mc->GetNuisanceParameters();
  RooArgSet* globalObservables = (RooArgSet*)mc->GetGlobalObservables();
  unique_ptr<RooAbsReal> nll(combPdf->createNLL(*data, Constrain(*nuisanceParameters), GlobalObservables(*globalObservables), Extended(combPdf->canBeExtended())));
  nll->enableOffsetting(true);
  RooMinimizer minim(*nll);
  // cout<<"Now performing the fit..."<<endl;
  minim.setPrintLevel(ROOT::Math::MinimizerOptions::DefaultPrintLevel());
  // cout<<ROOT::Math::MinimizerOptions::DefaultMinimizerType()<<" "<<ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str()<<endl;
  minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());
  return nll->getVal();
}

double GetMean(double *array, int size){
  double sum=0;
  for(int i=0;i<size;i++) sum+=array[i];
  return sum/double(size);
}

double GetMean(vector<double> array){
  int size=array.size();
  double sum=0;
  for(int i=0;i<size;i++) sum+=array[i];
  return sum/double(size);
}

double GetMedian(vector<double> array){
  vector<double> temp=array;
  //cout<<"Sorting array"<<endl;
  sort(temp.begin(),temp.end());
  //cout<<temp.size()<<endl;
  return temp[temp.size()/2];
}

double GetDeviation(vector<double> array, double value){
  vector<double> temp=array;
  //cout<<"Sorting array"<<endl;
  sort(temp.begin(),temp.end());
  //cout<<temp.size()<<endl;
  int num=temp.size();
  double frac=0;
  for(int index=0;index<num;index++){
    if(temp[index]>value) break;
    frac = double(index)/double(num);
  }
  return frac;
}
#endif
