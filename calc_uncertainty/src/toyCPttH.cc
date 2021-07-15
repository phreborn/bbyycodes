#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"
#include "statistics.hh"

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
    cout<<idx<<" "<<tt->GetName()<<endl;
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

int main(int argc, char**argv){
  
}

