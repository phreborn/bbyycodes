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

const double epsilon=1e-9;

void ReleaseTheGhost(RooDataSet *obsdata, RooRealVar *x, RooRealVar *w, double ghostwt){
  double xmin=x->getMin(), xmax=x->getMax();
  int nbin=x->getBins();
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

int profileToData(ModelConfig *mc, RooAbsData *data, double &nllVal, bool doFit=true){
  RooSimultaneous* combPdf  =  (RooSimultaneous*)mc->GetPdf();
  RooArgSet* nuisanceParameters = (RooArgSet*)mc->GetNuisanceParameters();
  RooArgSet* globalObservables = (RooArgSet*)mc->GetGlobalObservables();
  unique_ptr<RooAbsReal> nll(combPdf->createNLL(*data, Constrain(*nuisanceParameters), GlobalObservables(*globalObservables), Extended(combPdf->canBeExtended())));
  nll->enableOffsetting(true);
  int status=998;
  if(doFit){
    RooMinimizer minim(*nll);
    minim.optimizeConst(2);
    cout<<"Now performing the fit..."<<endl;
    cout<<ROOT::Math::MinimizerOptions::DefaultMinimizerType()<<" "<<ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str()<<endl;
    status=minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());
  }
  nllVal=nll->getVal();
  return status;
}

RooDataSet* generateToyData( ModelConfig *mc, TString option){
  RooSimultaneous* combPdf  =  (RooSimultaneous*)mc->GetPdf();
  RooArgSet* nuisanceParameters = (RooArgSet*)mc->GetNuisanceParameters();
  RooArgSet* globalObservables = (RooArgSet*)mc->GetGlobalObservables();
  RooArgSet* Observables = (RooArgSet*)mc->GetObservables();
 
  // statistics::constSet(nuisanceParameters,true);  // Fix nuisance parameters before randomize global observables.
  statistics::constSet(globalObservables,false);  // Release global observables before randomize global observables.

  map<string,RooDataSet*> toydatasetMap;
  RooCategory channellist("channellist","channellist");
  unique_ptr<TIterator> iter(combPdf->indexCat().typeIterator());
  RooCatType* tt = NULL;
  vector<shared_ptr<RooDataSet> > datai;
  // loop over all channels
  int idx=0;

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
    if(option.Contains("ghost")) ReleaseTheGhost(data.get(), x, &w, epsilon);
    // generate binned data
    if(option.Contains("binned")){
      shared_ptr<RooDataSet> databinned(statistics::unbinnedToBinned(data.get(), x, &w));
      datai.push_back(databinned);
      data.reset();
    }
    else{
      datai.push_back(data);
    }

    if(option.Contains("plot")){
      TCanvas *c=new TCanvas("c","c",800,600);
      TH1D hframe("hframe","hframe", x->numBins(), x->getMin(), x->getMax());
      hframe.SetMinimum(1e-3);
      hframe.SetMaximum(datai[idx]->sumEntries());
      hframe.Draw();
      RooPlot *frame=x->frame();
      datai[idx]->plotOn(frame);
      pdfi->plotOn(frame);
      frame->Draw("same");
      if(option.Contains("logy")) c->SetLogy();
      c->SaveAs(TString(tt->GetName())+"_"+TString(x->GetName())+".pdf");
    }
    toydatasetMap[(string)tt->GetName()] = datai[idx].get();
    idx++;
  }

  RooRealVar wt("wt","wt",1); 
  RooArgSet args;
  args.add(*Observables);
  args.add(wt);
  RooDataSet* toyData = new RooDataSet("toyData", "", args, Index(channellist), Import(toydatasetMap), WeightVar(wt));

  // statistics::constSet(nuisanceParameters,false);  // release nuisance parameters
  return toyData;
}

map<string,double> calcTestStat(ModelConfig *mc, RooAbsData *data, double mu, vector<string> *namenp, vector<double> *valuenpfix,vector<double> *valuenphat, TString option){
  RooAbsPdf* combPdf = mc->GetPdf();
  RooArgSet* nuisanceParameters = (RooArgSet*)mc->GetNuisanceParameters();
  RooArgSet* globalObservables = (RooArgSet*)mc->GetGlobalObservables();
  RooArgSet* Observables = (RooArgSet*)mc->GetObservables();

  RooArgSet* poi=(RooArgSet*)mc->GetParametersOfInterest();
  RooRealVar* firstpoi=(RooRealVar*)poi->first();
  unique_ptr<TIterator> iter(nuisanceParameters -> createIterator());
  TString secPOIName="";
    
  if(option.Contains("scalar")) secPOIName="wX";
  if(option.Contains("graviton")) secPOIName="GkM";
  RooRealVar* secondpoi=mc->GetWS()->var(secPOIName);
  
  firstpoi->setMax(1000);
  if(option.Contains("gonegative")){
    firstpoi->setMin(-10);
  }
  // +++++++++++++++++++++++ Step 2: Fit toy data ++++++++++++++++++++++++
  cout<<"Free POI..."<<endl;
  firstpoi->setVal(mu); 
  firstpoi->setConstant(false);
  firstpoi->Print();

  if(option.Contains("coupling")){
    if(option.Contains("graviton")) secondpoi->setRange(0.01,0.5);
    if(option.Contains("scalar")) secondpoi->setRange(0,100);
    secondpoi->setConstant(false);
  }

  int statushat=0;
  double NLLhat=0;

  if(option.Contains("snapshot")){
    // mc->GetWS()->loadSnapshot("ucmles");
    mc->GetWS()->loadSnapshot("conditionalPOI_toy");
    mc->GetWS()->loadSnapshot("conditionalNuis_toy");
    mc->GetWS()->loadSnapshot("nominalGlobs");
    profileToData(mc, data, NLLhat,false);
  }
  else{
    statushat=profileToData(mc, data, NLLhat);
  }
  mc->GetParametersOfInterest()->Print("v");
  double muhat=firstpoi->getVal();

  if(namenp!=NULL){
    iter.reset(nuisanceParameters -> createIterator());
    RooRealVar* parg_nuifix_hat = NULL;
    while((parg_nuifix_hat=(RooRealVar*)iter->Next()) ){
      valuenphat->push_back(parg_nuifix_hat->getVal());
    }
  }

  cout<<"Fixed POI..."<<endl;
  firstpoi->setVal(mu);
  firstpoi->setConstant(true);
  firstpoi->Print();

  if(option.Contains("coupling")){
    secondpoi->setConstant(true);
  }

  int statusfix=0;
  double NLLfix=0;
  if(option.Contains("snapshot")){
    mc->GetWS()->loadSnapshot("ucmles_0");
    profileToData(mc, data, NLLfix, false);
  }
  else{
    statusfix=profileToData(mc, data, NLLfix);
  }
  mc->GetParametersOfInterest()->Print("v");
  if(namenp!=NULL){
    iter.reset(nuisanceParameters -> createIterator());
    RooRealVar* parg_nuifix_fix = NULL;
    while((parg_nuifix_fix=(RooRealVar*)iter->Next()) ){
      namenp->push_back(parg_nuifix_fix->GetName());
      valuenpfix->push_back(parg_nuifix_fix->getVal());
    }
  }

  map<string,double> result ;
  result["nllfix"] = NLLfix; 
  result["nllhat"] = NLLhat;
  result["muhat"] = muhat;
  result["statusfix"]=statusfix;
  result["statushat"]=statushat;
  return result;
}

void unfoldConstraints(RooArgSet& initial, RooArgSet& final, RooArgSet& obs, RooArgSet& nuis, int& counter)
{
  if (counter > 50)
  {
    cout << "ERROR::Couldn't unfold constraints!" << endl;
    cout << "Initial: " << endl;
    initial.Print("v");
    cout << endl;
    cout << "Final: " << endl;
    final.Print("v");
    exit(1);
  }
  TIterator* itr = initial.createIterator();
  RooAbsPdf* pdf;
  while ((pdf = (RooAbsPdf*)itr->Next()))
  {
    RooArgSet nuis_tmp = nuis;
    RooArgSet constraint_set(*pdf->getAllConstraints(obs, nuis_tmp, false));
    //if (constraint_set.getSize() > 1)
    //{
    string className(pdf->ClassName());
    if (className != "RooGaussian" && className != "RooLognormal" && className != "RooGamma" && className != "RooPoisson" && className != "RooBifurGauss")
    {
      counter++;
      unfoldConstraints(constraint_set, final, obs, nuis, counter);
    }
    else
    {
      final.add(*pdf);
    }
  }
  delete itr;
}

int pairNuisGlob(ModelConfig *mc){
  RooArgSet mc_obs = *mc->GetObservables();
  RooArgSet mc_globs = *mc->GetGlobalObservables();
  RooArgSet mc_nuis = *mc->GetNuisanceParameters();
  RooAbsPdf *combPdf = mc->GetPdf();
//pair the nuisance parameter to the global observable
  RooArgSet mc_nuis_tmp = mc_nuis;
  RooArgList nui_list("ordered_nuis");
  RooArgList glob_list("ordered_globs");
  RooArgSet constraint_set_tmp(*combPdf->getAllConstraints(mc_obs, mc_nuis_tmp, false));
  RooArgSet constraint_set;
  int counter_tmp = 0;
  unfoldConstraints(constraint_set_tmp, constraint_set, mc_obs, mc_nuis_tmp, counter_tmp);

  TIterator* cIter = constraint_set.createIterator();
  RooAbsArg* arg;
  while ((arg = (RooAbsArg*)cIter->Next()))
  {
    RooAbsPdf* pdf = (RooAbsPdf*)arg;
    if (!pdf) continue;

    TIterator* nIter = mc_nuis.createIterator();
    RooRealVar* thisNui = NULL;
    RooAbsArg* nui_arg;
    while ((nui_arg = (RooAbsArg*)nIter->Next()))
    {
      if (pdf->dependsOn(*nui_arg))
      {
	thisNui = (RooRealVar*)nui_arg;
	break;
      }
    }
    delete nIter;

    //need this incase the observable isn't fundamental. 
    //in this case, see which variable is dependent on the nuisance parameter and use that.
    RooArgSet* components = pdf->getComponents();
    //     cout << "\nPrinting components" << endl;
    //     components->Print();
    //     cout << "Done" << endl;
    components->remove(*pdf);
    if (components->getSize())
      {
	TIterator* itr1 = components->createIterator();
	RooAbsArg* arg1;
	while ((arg1 = (RooAbsArg*)itr1->Next()))
	  {
	  TIterator* itr2 = components->createIterator();
	  RooAbsArg* arg2;
	  while ((arg2 = (RooAbsArg*)itr2->Next()))
	    {
	      if (arg1 == arg2) continue;
	      if (arg2->dependsOn(*arg1))
		{
		  components->remove(*arg1);
		}
	    }
	  delete itr2;
	  }
	delete itr1;
      }
    if (components->getSize() > 1)
      {
	cout << "ERROR::Couldn't isolate proper nuisance parameter" << endl;
	return -1;
      }
    else if (components->getSize() == 1)
      {
	thisNui = (RooRealVar*)components->first();
      }
    
    
    
    TIterator* gIter = mc_globs.createIterator();
    RooRealVar* thisGlob = NULL;
    RooAbsArg* glob_arg;
    while ((glob_arg = (RooAbsArg*)gIter->Next()))
      {
      if (pdf->dependsOn(*glob_arg))
	{
	  thisGlob = (RooRealVar*)glob_arg;
	  break;
	}
      }
    delete gIter;
    
    if (!thisNui || !thisGlob)
      {
	cout << "WARNING::Couldn't find nui or glob for constraint: " << pdf->GetName() << endl;
	//return;
	continue;
      }
    
    // cout << "Pairing nui: " << thisNui->GetName() << ", with glob: " << thisGlob->GetName() << ", from constraint: " << pdf->GetName() << endl;

    nui_list.add(*thisNui);
    glob_list.add(*thisGlob);
    
  }
  int nrNuis = nui_list.getSize();
  if (nrNuis != glob_list.getSize())
    {
      cout << "ERROR::nui_list.getSize() != glob_list.getSize()!" << endl;
      return -1;
    }
  
  for (int i=0;i<nrNuis;i++)
    {
      RooRealVar* nui = (RooRealVar*)nui_list.at(i);
      RooRealVar* glob = (RooRealVar*)glob_list.at(i);
      
      //cout << "nui: " << nui << ", glob: " << glob << endl;
      //cout << "Setting glob: " << glob->GetName() << ", which had previous val: " << glob->getVal() << ", to conditional val: " << nui->getVal() << endl;
      
      glob->setVal(nui->getVal());
    }
  return 1;
}

RooDataSet* copyData(RooDataSet *dataDebit, RooDataSet *dataCredit, ModelConfig *mcDebit, ModelConfig *mcCredit, TString option){
  if(mcDebit==mcCredit) return NULL;
  RooSimultaneous* pdfDebit = dynamic_cast<RooSimultaneous*>(mcDebit->GetPdf());
  RooAbsCategoryLValue* catDebit = (RooAbsCategoryLValue*)(&pdfDebit->indexCat());
  int numChannels = catDebit->numBins(0);
  TList* dataListDebit = dataDebit->split( *catDebit, true );

  RooSimultaneous* pdfCredit = dynamic_cast<RooSimultaneous*>(mcCredit->GetPdf());
  RooAbsCategoryLValue* catCredit = (RooAbsCategoryLValue*)(&pdfCredit->indexCat());
  TList* dataListCredit = dataCredit->split( *catCredit, true );

  if(numChannels!=catCredit->numBins(0)) return NULL;

  map<string,RooDataSet*> toydatasetMap;
  vector<shared_ptr<RooDataSet> > datai;
  RooCategory channellist("channellist","channellist");

  for ( int i= 0; i < numChannels; i++ ) {
    catDebit->setBin(i);
    catCredit->setBin(i);
    
    TString channelname=catDebit->getLabel();
    if(channelname!=catCredit->getLabel()) return NULL;
    channellist.defineType(channelname) ;     
    RooAbsPdf* pdfiDebit = pdfDebit->getPdf(catDebit->getLabel());
    RooDataSet* dataiDebit = ( RooDataSet* )( dataListDebit->At( i ) );
    std::cout << "\t\tIndex: " << i << ", Pdf: " << pdfiDebit->GetName() << ", Data: " << dataiDebit->GetName()  << ", SumEntries: " << dataiDebit->sumEntries() << " NumEntries: "<< dataiDebit->numEntries() <<std::endl;

    RooAbsPdf* pdfiCredit = pdfCredit->getPdf(catCredit->getLabel());
    shared_ptr<RooDataSet> dataiCredit(dynamic_cast<RooDataSet*>(dataListCredit->At( i )));

    RooRealVar *xDebit=(RooRealVar*)pdfiDebit->getObservables(dataiDebit)->first();    
    RooRealVar *xCredit=(RooRealVar*)pdfiCredit->getObservables(dataiCredit.get())->first();

    RooRealVar w("w","w",1);
    dataiCredit.reset(new RooDataSet("dataiCredit","dataiCredit",RooArgSet(*xCredit,w),WeightVar(w)));

    RooArgSet* obs_tmp = const_cast<RooArgSet*>(dataiDebit->get());
    RooRealVar* xdata_tmp = dynamic_cast<RooRealVar*>(obs_tmp->find(xDebit->GetName()));
    for (int ievt=0 ; ievt<dataiDebit->numEntries() ; ievt++) {
      dataiDebit->get(ievt) ;
      double mass=xdata_tmp->getVal();
      if(mass>xCredit->getMin()&&mass<xCredit->getMax()){
	xCredit->setVal(mass);
	double weight=dataiDebit->weight();
	w.setVal(weight);
	dataiCredit->add(RooArgSet(*xCredit ,w) , weight);
      }
    }
    datai.push_back(dataiCredit);
    toydatasetMap[channelname.Data()] = datai[i].get();
    if(option.Contains("plot")){
      TCanvas *c=new TCanvas("c","c",800,600);
      TH1D hframe("hframe","hframe", xCredit->numBins(), xCredit->getMin(), xCredit->getMax());
      hframe.SetMinimum(1e-3);
      hframe.SetMaximum(datai[i]->sumEntries());
      hframe.Draw();
      RooPlot *frame=xCredit->frame();
      datai[i]->plotOn(frame);
      pdfiCredit->plotOn(frame);

      frame->Draw("same");
      if(option.Contains("logy")) c->SetLogy();
      c->SaveAs(channelname+"_"+TString(xCredit->GetName())+".pdf");
    }
  }
  RooRealVar wt("wt","wt",1); 
  RooArgSet args;
  args.add(*mcCredit->GetObservables());
  args.add(wt);
  RooDataSet* toyData = new RooDataSet("toyData", "", args, Index(channellist), Import(toydatasetMap), WeightVar(wt));
  return toyData;
}

#endif
