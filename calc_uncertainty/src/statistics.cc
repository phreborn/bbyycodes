#include "statistics.hh"

using namespace RooFit;
using namespace RooStats;

ClassImp(statistics)

statistics::statistics(){
  //other configuration
  defaultMinimizer    = "Minuit2";     // or "Minuit"
  defaultPrintLevel      = -1;             // Minuit print level
  defaultStrategy        = 0;             // Minimization strategy. 0-2. 0 = fastest, least robust. 2 = slowest, most robust
  killBelowFatal        = 1;             // In case you want to suppress RooFit warnings further, set to 1
  doBlind               = 0;             // in case your analysis is blinded
  conditionalExpected   = 1 && !doBlind; // Profiling mode for Asimov data: 0 = conditional MLEs, 1 = nominal MLEs
  doTilde               = 1;             // bound mu at zero if true and do the \tilde{q}_{mu} asymptotics
  doExp                 = 1;             // compute expected limit
  doObs                 = 1 && !doBlind; // compute observed limit
  precision           = 0.005;         // % precision in mu that defines iterative cutoff
  verbose               = 0;             // 1 = very spammy
  usePredictiveFit      = 0;             // experimental, extrapolate best fit nuisance parameters based on previous fit results
  extrapolateSigma      = 0;             // experimantal, extrapolate sigma based on previous fits
  maxRetries             = 3;             // number of minimize(fcn) retries before giving up
  fRandom=new TRandom3();
  if (killBelowFatal) RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
  ROOT::Math::MinimizerOptions::SetDefaultMinimizer(defaultMinimizer.c_str());
  ROOT::Math::MinimizerOptions::SetDefaultStrategy(defaultStrategy);
  ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(defaultPrintLevel);
}

statistics::~statistics(){
  SafeDelete(fRandom);
}

RooNLLVar* statistics::createNLL(RooAbsData* _data, ModelConfig* _mc)
{
  RooArgSet nuis = *_mc->GetNuisanceParameters();
  RooNLLVar* nll = (RooNLLVar*)_mc->GetPdf()->createNLL(*_data, Constrain(nuis), Extended(_mc->GetPdf()->canBeExtended()));
  return nll;
}

RooFitResult* statistics::minimize(RooAbsReal* fcn, TString option, RooArgSet *minosVars, bool m_save)
{
  option.ToLower();

  bool doHesse=option.Contains("hesse");
  bool doMinos=option.Contains("minos");
  bool m_2sigma=option.Contains("2sigma");

  int printLevel = ROOT::Math::MinimizerOptions::DefaultPrintLevel();
  RooFit::MsgLevel msglevel = RooMsgService::instance().globalKillBelow();
  if (printLevel < 0) RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);

  int strat = ROOT::Math::MinimizerOptions::DefaultStrategy();
  int save_strat = strat;
  RooMinimizer minim(*fcn);
  minim.setStrategy(strat);
  minim.setPrintLevel(printLevel);
  if(m_2sigma) minim.setErrorLevel(2);
  int status = minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());

//up the strategy
  if (status != 0 && status != 1 && strat < 2)
  {
    strat++;
    cout << "Fit failed with status " << status << ". Retrying with strategy " << strat << endl;
    minim.setStrategy(strat);
    status = minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());
  }

  if (status != 0 && status != 1 && strat < 2)
  {
    strat++;
    cout << "Fit failed with status " << status << ". Retrying with strategy " << strat << endl;
    minim.setStrategy(strat);
    status = minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());
  }

  cout << "status is " << status << endl;

//switch minuit version and try again
  if (status != 0 && status != 1)
  {
    string minType = ROOT::Math::MinimizerOptions::DefaultMinimizerType();
    string newMinType;
    if (minType == "Minuit2") newMinType = "Minuit";
    else newMinType = "Minuit2";
  
    cout << "Switching minuit type from " << minType << " to " << newMinType << endl;
  
    ROOT::Math::MinimizerOptions::SetDefaultMinimizer(newMinType.c_str());
    strat = ROOT::Math::MinimizerOptions::DefaultStrategy();
    minim.setStrategy(strat);

    status = minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());


    if (status != 0 && status != 1 && strat < 2)
    {
      strat++;
      cout << "Fit failed with status " << status << ". Retrying with strategy " << strat << endl;
      minim.setStrategy(strat);
      status = minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());
    }

    if (status != 0 && status != 1 && strat < 2)
    {
      strat++;
      cout << "Fit failed with status " << status << ". Retrying with strategy " << strat << endl;
      minim.setStrategy(strat);
      status = minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());
    }

    ROOT::Math::MinimizerOptions::SetDefaultMinimizer(minType.c_str());
  }

  if (status != 0 && status != 1)
  {
    cout << "WARNING::Fit failure unresolved with status " << status << endl;
    return NULL;
  }

  if (printLevel < 0) RooMsgService::instance().setGlobalKillBelow(msglevel);
  ROOT::Math::MinimizerOptions::SetDefaultStrategy(save_strat);

  if(doHesse) minim.hesse();
  if(doMinos){
    if(minosVars==NULL) minim.minos();
    else minim.minos(*minosVars);
  }
  if(m_save) return minim.save();
  else return NULL;
}

RooFitResult* statistics::minimize(RooNLLVar* nll, TString option, RooArgSet *minosVars)
{
  RooAbsReal* fcn = (RooAbsReal*)nll;
  return minimize(fcn,option,minosVars);
}

void statistics::recoverSet(RooArgSet* set, RooArgSet* snapshot){
  TIterator *iter = set -> createIterator();
  RooRealVar* parg = NULL;
  TIterator *iter_ss = snapshot -> createIterator();
  RooRealVar* parg_ss = NULL;  
  while((parg_ss=(RooRealVar*)iter_ss->Next())&&(parg=(RooRealVar*)iter->Next())){
    parg->setVal(parg_ss->getVal());
  }
}

void statistics::constSet(RooArgSet* set, bool flag, RooArgSet* snapshot){
  TIterator *iter = set -> createIterator();
  RooRealVar* parg = NULL;
//   if(snapshot!=NULL) recoverSet(set,snapshot);
  if(snapshot!=NULL) *set=*snapshot;
  while((parg=(RooRealVar*)iter->Next()) ){
    parg->setConstant(flag); 
  }
  SafeDelete(iter);
}

void statistics::rerangeSet(RooArgSet* set, double min, double max){
  TIterator *iter = set -> createIterator();
  RooRealVar* parg = NULL;
  while((parg=(RooRealVar*)iter->Next()) ){
    parg->setRange(min, max);
  }
  SafeDelete(iter);
}

void statistics::scaleSet(RooArgSet* set, double f, bool rerange){
  TIterator *iter = set -> createIterator();
  RooRealVar* parg = NULL;
  while((parg=(RooRealVar*)iter->Next()) ){
    double OV=parg->getVal();
    if(rerange&&OV*f>0){
      double winsize=5*sqrt(OV*f);
      parg->setRange(OV*f-winsize, OV*f+winsize);
    }
    parg->setVal(OV*f);
    cout<<"Scaling value of parameter "<<parg->GetName()<<" from "<<OV<<" to "<<OV*f<<endl;
  }
  SafeDelete(iter);
}

void statistics::setvalSet(RooArgSet* set, double value){
  TIterator *iter = set -> createIterator();
  RooRealVar* parg = NULL;
  while((parg=(RooRealVar*)iter->Next()) ){
    if(value>parg->getMax()) parg->setRange(parg->getMin(),value);
    if(value<parg->getMin()) parg->setRange(value,parg->getMax());
    parg->setVal(value);
  }
  SafeDelete(iter);
}

void statistics::duplicateSet(RooWorkspace* w, RooArgSet* set, TString setname){
  TIterator *iter = set -> createIterator();
  RooRealVar* parg = NULL;
  RooArgSet *temp=new RooArgSet();
  while((parg=(RooRealVar*)iter->Next()) ){
    if(!w->var(parg->GetName())){
      cerr<<"Variable "<<parg->GetName()<<" does not exist..."<<endl;
      continue;
    }
    temp->add(*w->var(parg->GetName()));
  }
  w->defineSet(setname,*temp);
  SafeDelete(iter);
}

void statistics::printSet(RooArgSet* set){
  TIterator *iter = set -> createIterator();
  RooRealVar* parg = NULL;
  while((parg=(RooRealVar*)iter->Next()) ){
    cout<<parg->GetName()<<"\t\t"<<parg->getVal()<<endl;
  }
  SafeDelete(iter);
}

void statistics::randomizeSet(RooArgSet* set, int seed, bool protection){
  TIterator *iter = set -> createIterator();
  RooRealVar* parg = NULL;

  fRandom -> SetSeed(seed) ;   
  while((parg=(RooRealVar*)iter->Next()) ){
    double r =  fRandom->Gaus(0,1);
    if(protection&&r<-5) r=-5;
    if(protection&&r>5) r=5;
    parg->setVal(r); 
  }
  SafeDelete(iter);
}

void statistics::retrieveSet(RooWorkspace*w, RooArgSet* set, RooArgSet* snapshot){
  TIterator *iter = snapshot -> createIterator();
  RooRealVar* parg = NULL;
  while((parg=(RooRealVar*)iter->Next())){
    if((bool)w->obj(parg->GetName()))
      set -> add( *(RooRealVar*)w->obj(parg->GetName()) );
  }
}

RooDataSet* statistics::histToDataSet(TH1* h, RooRealVar* x, RooRealVar* w){
  double xmin=x->getMin();
  double xmax=x->getMax();
  RooDataSet *histData =new RooDataSet(h->GetName(),h->GetTitle(),RooArgSet(*x,*w),WeightVar(*w));
  int nbin=h->GetNbinsX();
  for( int ibin = 1 ; ibin <= nbin ; ibin ++ ) {
    double center=h->GetBinCenter(ibin);
    if(center<xmin||center>xmax) continue;
    x->setVal(h->GetBinCenter(ibin));
    double weight = h->GetBinContent(ibin);
    // double weighterr = h->GetBinError(ibin);
    // weighterr=0;
    w->setVal(weight);
    histData -> add( RooArgSet(*x,*w) , weight);
    // histData -> add( RooArgSet(*x,*w) , weight, weighterr);
//     cout<<ibin<<" "<<x->getVal()<<" "<<w->getVal()<<endl; getchar();
  }
  histData->Print(); 
  return histData;
}

void statistics::addDataSet(RooDataSet *data, RooDataSet *data_add, RooRealVar* x, RooRealVar* w){
  RooRealVar* xdata=(RooRealVar*)(data_add->get()->find(x->GetName()));
  int nevt=data_add->numEntries();
  for(int ievt=0;ievt<nevt;ievt++){
    data_add->get(ievt);
    x->setVal(xdata->getVal());
    double weight=data_add->weight();
    w->setVal(weight);
    data->add(RooArgList(*x, *w), weight);
  }
}

RooDataSet* statistics::unbinnedToBinned(RooDataSet *data, RooRealVar* x, RooRealVar* w){
  double xmin=x->getMin();
  double xmax=x->getMax();
  int nbin=x->getBins();
  TH1D hist("hist","hist",nbin,xmin,xmax);

  RooArgSet* obs = const_cast<RooArgSet*>(data->get());
  RooRealVar* xdata = dynamic_cast<RooRealVar*>(obs->find(x->GetName())); 
  for (int i=0 ; i<data->numEntries() ; i++) {
    data->get(i) ;
    double value=xdata->getVal();
    double weight=data->weight();
    hist.Fill(value, weight);
  }
  
  return histToDataSet(&hist,x,w);
}

void statistics::randomizeSet(RooAbsPdf* pdf, RooArgSet* globs, int seed){
  if(seed>=0) RooRandom::randomGenerator() -> SetSeed(seed) ; // This step is necessary
  RooDataSet *one=pdf->generate(*globs, 1);
  const RooArgSet *values=one->get(0);
  RooArgSet *allVars=pdf->getVariables();
  *allVars=*values;
  delete one;
  delete allVars;
}

double statistics::pvalueError(double pvalue, int ntoy){
  return sqrt(pvalue*(1-pvalue)/double(ntoy));
}

double statistics::pvalueFromToy(vector<double> teststat, double threshold){
  std::sort(teststat.begin(),teststat.end());
  int ntoy=teststat.size();
  int marker=-1;

  for(int itoy=0;itoy<ntoy;itoy++){
//     cout<<toy[itoy]<<endl;
//     if(!isfinite(toy[itoy])) cout<<"NaN!"<<endl; 
    if(teststat[itoy]>threshold){ marker=itoy; break;}
  }
  double pvalue=double(marker)/double(ntoy);
  if(pvalue>0.5) pvalue=1-pvalue;
  return pvalue;
}

map<string,double> statistics::expFromToy(vector<double> teststat){
  double median=0;
  double mean=0;
  double n2s=0;
  double n1s=0;
  double p1s=0;
  double p2s=0;

  int num = (int)teststat.size();

  sort(teststat.begin(),teststat.end());

  for(int index=0; index<num; index++){
    double frac = double(index)/double(num);
    if (frac < LB2S) n2s = teststat[index];
    if (frac < LB1S) n1s = teststat[index];
    if (frac < B0S) median = teststat[index];
    if (frac < UB1S) p1s = teststat[index];
    if (frac < UB2S) p2s = teststat[index];
  }
  map<string,double> results;
  results["n2s"]=n2s;
  results["n1s"]=n1s;
  results["median"]=median;
  results["p1s"]=p1s;
  results["p2s"]=p2s;

  return results;
}

TH1D *statistics::plotToy(vector<double> teststat, TString histname, int nbin, double xmin, double xmax, TString xTitle, Color_t color, double width){
  TH1D *hist=new TH1D(histname,histname, nbin, xmin, xmax);
  hist->GetXaxis()->SetTitle(xTitle);
  hist->SetLineColor(color);
  hist->SetMarkerColor(color);
  hist->SetLineWidth(2);
  hist->Sumw2();
  for( auto TS : teststat) hist->Fill(TS);
  return hist;
}

TH1* statistics::calcChi2(TH1 *hobs, TH1 *hexp){
  if(hobs->GetNbinsX()!=hexp->GetNbinsX()){
    cerr<<"The number of bins do not match! Obs: "<<hobs->GetNbinsX()<<", Exp: "<<hexp->GetNbinsX()<<endl;
    return NULL;
  }
  
  TH1* hchi2=(TH1*)hobs->Clone("chi2");
  hchi2->Reset();
  int nbin=hobs->GetNbinsX();
  for(int ibin=1; ibin<=nbin; ibin++){
    double exp=hexp->GetBinContent(ibin);
    double obs=hobs->GetBinContent(ibin);

    double chi2=((exp-obs)*(exp-obs))/exp;
    //cout<<chi2<<endl;
    hchi2->SetBinContent(ibin,chi2);
  }

  return hchi2;
}

TH1* statistics::calcLikelihd(TH1 *hobs, TH1 *hexp){
  if(hobs->GetNbinsX()!=hexp->GetNbinsX()){
    cerr<<"The number of bins do not match! Obs: "<<hobs->GetNbinsX()<<", Exp: "<<hexp->GetNbinsX()<<endl;
    return NULL;
  }
  
  TH1* hlikelihd=(TH1*)hobs->Clone("likelihd");
  hlikelihd->Reset();
  int nbin=hobs->GetNbinsX();
  for(int ibin=1; ibin<=nbin; ibin++){
    double exp=hexp->GetBinContent(ibin);
    double obs=hobs->GetBinContent(ibin);

    double likelihd=TMath::Poisson(obs,exp);
    //cout<<likelihd<<endl;
    hlikelihd->SetBinContent(ibin,likelihd);
  }

  return hlikelihd;
}

double statistics::significance(double ntotal, double nbkg){
  return sqrt(2*(ntotal*log(ntotal/nbkg)+nbkg-ntotal));
}

void statistics::plotData(RooSimultaneous* m_pdf, RooDataSet* m_data, TString outputDir){

  RooAbsCategoryLValue*  m_cat = (RooAbsCategoryLValue*)&m_pdf->indexCat();
  int numChannels = m_cat->numBins(0);

  TList* m_dataList = m_data->split( *m_cat, true );

  system("mkdir -vp "+outputDir);

  std::cout << "\t~~~~~~~~Begin Plotting~~~~~~~~" << std::endl;
  std::cout << "\tThere are " << numChannels << " sub channels:" << std::endl;
  for ( int i= 0; i < numChannels; i++ ) {
    m_cat->setBin(i);
    TString channelname=m_cat->getLabel();
    RooAbsPdf* pdfi = m_pdf->getPdf(m_cat->getLabel());
    RooDataSet* datai = ( RooDataSet* )( m_dataList->At( i ) );
    std::cout << "\t\tIndex: " << i << ", Pdf: " << pdfi->GetName() << ", Data: " << datai->GetName()  << ", SumEntries: " << datai->sumEntries() << ", NumEntries: "<< datai->numEntries() <<std::endl;
    TCanvas *c=new TCanvas(Form("c%d",i),channelname,800,600);
    RooRealVar *x=(RooRealVar*)pdfi->getObservables(datai)->first();
    RooPlot *frame=x->frame();
    datai->plotOn(frame);
    pdfi->plotOn(frame,LineColor(kRed));
    c->cd();
    frame->Draw();
    PrintCanvas(c, outputDir+"/"+channelname);
  }
  std::cout << "\t~~~~~~~~~End Plotting~~~~~~~~~" << std::endl;
}

void statistics::copyDataSet(RooDataSet* datadebit,RooRealVar* obsdebit, RooDataSet* datacredit, RooRealVar* obscredit, RooRealVar* wt, double scale, bool verbose){
  RooRealVar* obs = (RooRealVar*)datadebit->get()->find(obsdebit->GetName());
  if(verbose) cout<<datadebit->numEntries()<<endl;
  double xmin=obscredit->getMin();
  double xmax=obscredit->getMax();
  //cout<<obs->GetName()<<" "<<obs->GetTitle()<<endl;getchar();
  for (int i=0 ; i<datadebit->numEntries() ; i++) {
    datadebit->get(i) ;
    if(verbose) cout<<obs->getVal()<<" "<<datadebit->weight()<<endl;
    double weight=datadebit->weight();
    weight*=scale;
    double value=obs->getVal();
    if(value<xmin||value>xmax){
      cerr<<"Warning: entry "<<i<<" with value "<< value<<" is out of the observable range ["<<xmin<<","<<xmax<<"]!"<<endl;
      continue;
    }
    obscredit->setVal(obs->getVal());
    wt->setVal(datadebit->weight());
    datacredit->add(RooArgSet(*obscredit, *wt), weight);
  }
  if(verbose) datacredit->Print("v");
}

void statistics::copyPdfParams(RooAbsPdf *pdfdebit, RooDataSet* datadebit, RooAbsPdf *pdfcredit, RooDataSet* datacredit){
  RooArgSet* paramsdebit=pdfdebit->getParameters(*datadebit);
  RooArgSet* paramscredit=pdfcredit->getParameters(*datacredit);
  *paramscredit=*paramsdebit;
}

double statistics::countDataSet(RooDataSet* data, RooSimultaneous *pdf, double xmin, double xmax, bool verbose){
  RooCategory *cat=(RooCategory*)&pdf->indexCat();
  int numChannels = cat->numBins(0);
  TList* dataList = data->split( *cat, true );
  double total_weight=0;

  for ( int i= 0; i < numChannels; i++ ) {
    cat->setBin(i);
    TString channelname=cat->getLabel();
    if(verbose) cout<<channelname<<endl;
    RooAbsPdf* pdfi = pdf->getPdf(channelname);
    RooDataSet* datai = ( RooDataSet* )( dataList->At( i ) );
    
    RooRealVar* obsi = (RooRealVar*)pdfi->getObservables(datai)->first();
    RooRealVar* obs = (RooRealVar*)datai->get()->find(obsi->GetName());
    for (int j=0 ; j<datai->numEntries() ; j++) {
      datai->get(j) ;
      if(verbose) cout<<obs->getVal()<<" "<<datai->weight()<<endl;
      double weight=datai->weight();
      double value=obs->getVal();
      if(value<xmin||value>xmax) continue;
      total_weight+=weight;
      if(verbose) cout<<total_weight<<endl;
    }
  }
  return total_weight;
}

void statistics::setVal(RooRealVar *x, double value, bool fix){
  bool constFlag=x->isConstant();
  if(constFlag) x->setConstant(false);
  if(value<x->getMin()) x->setMin(value);
  else if(value>x->getMax()) x->setMax(value);
  x->setVal(value);
  if(constFlag||fix) x->setConstant(true);
}

void statistics::fixSyst(ModelConfig *mc, bool fix, bool reset){
  RooArgSet* constraints=mc->GetPdf()->getAllConstraints(*mc->GetObservables(), *const_cast<RooArgSet*>(mc->GetNuisanceParameters()));
  RooArgSet nuisSyst;
  unique_ptr<TIterator> iter(constraints->createIterator());
  RooAbsPdf *parg=NULL;
  while((parg=dynamic_cast<RooAbsPdf*>(iter->Next()))){
    RooArgSet *nuisSet=parg->getObservables(*mc->GetNuisanceParameters());
    if(nuisSet->getSize()==1){
      RooRealVar *nuis=dynamic_cast<RooRealVar*>(nuisSet->first());
      if(reset) nuis->setVal(0);
      nuis->setConstant(fix);
    }
  }
}

void statistics::calcBandInterval(RooCurve *curCurve, vector<RooCurve*> variations,Int_t i,Double_t Z, Double_t& lo, Double_t& hi, Bool_t approxGauss)
{
  vector<double> y(variations.size()) ;
  Int_t j(0) ;
  for (vector<RooCurve*>::const_iterator iter=variations.begin() ; iter!=variations.end() ; iter++) {
    y[j++] = (*iter)->interpolate(curCurve->GetX()[i]) ;
    (*iter)->Print("v");
    cout<<curCurve->GetX()[i]<<" "<<(*iter)->interpolate(curCurve->GetX()[i])<<endl;
    cout<<curCurve->GetX()[i+1]<<" "<<(*iter)->interpolate(curCurve->GetX()[i+1])<<endl;
    cout<<curCurve->GetX()[i+2]<<" "<<(*iter)->interpolate(curCurve->GetX()[i+2])<<endl; getchar();
  }

  if (!approxGauss) {
    // Construct central 68% interval from variations collected at each point
    Double_t pvalue = TMath::Erfc(Z/sqrt(2.)) ;
    Int_t delta = Int_t( y.size()*(pvalue)/2 + 0.5) ;
    sort(y.begin(),y.end()) ;    
    lo = y[delta] ;
    hi = y[y.size()-delta] ;  
  }
}

RooCurve* statistics::makeErrorBand(RooCurve *curCurve, vector<RooCurve*> variations, Double_t Z)
{
  // Construct filled RooCurve represented error band that captures alpha% of the variations
  // of the curves passed through argument variations, where the percentage alpha corresponds to
  // the central interval fraction of a significance Z
  
  RooCurve* band = new RooCurve ;
  band->SetName(Form("%s_errorband",curCurve->GetName())) ;
  band->SetLineWidth(1) ;
  band->SetFillColor(kCyan) ;
  band->SetLineColor(kCyan) ;

  vector<double> bandLo(curCurve->GetN()) ;
  vector<double> bandHi(curCurve->GetN()) ;
  for (int i=0 ; i<curCurve->GetN() ; i++) {
    calcBandInterval(curCurve, variations,i,Z,bandLo[i],bandHi[i],kFALSE) ;
  }
  
  for (int i=0 ; i<curCurve->GetN() ; i++) {
    cout<<curCurve->GetX()[i]<<" "<<bandLo[i]<<endl; getchar();
    band->addPoint(curCurve->GetX()[i],bandLo[i]) ;
  }
  for (int i=curCurve->GetN()-1 ; i>=0 ; i--) {
    band->addPoint(curCurve->GetX()[i],bandHi[i]) ;
  }	   
  
  return band ;
}

RooCurve* statistics::convertAsimovToCurve(RooDataSet *asimov, TString observableName, bool isHist, double epsilon){
  RooCurve *curve=new RooCurve();
  RooArgSet* obs = const_cast<RooArgSet*>(asimov->get());
  RooRealVar* xdata = dynamic_cast<RooRealVar*>(obs->find(observableName));
  double binw=0;
  if(isHist) binw=(xdata->getMax()-xdata->getMin())/double(xdata->numBins());
  
  for (int i=0 ; i<asimov->numEntries() ; i++) {
    asimov->get(i) ;
    double mass=xdata->getVal();
    double weight=asimov->weight();
    
    if(isHist){
      curve->addPoint(mass-0.5*binw+epsilon,weight);
      curve->addPoint(mass+0.5*binw-epsilon,weight);
    }
    else{
      curve->addPoint(mass,weight);
    }
  }
  return curve;
}

void statistics::releaseTheGhost(RooDataSet *obsdata, RooRealVar *x, RooRealVar *w, double ghostwt){
  TH1D h_data("h_data","",x->numBins(),x->getMin(),x->getMax());
  RooArgSet* obs = const_cast<RooArgSet*>(obsdata->get());
  RooRealVar* xdata = dynamic_cast<RooRealVar*>(obs->find(x->GetName()));
  int nevt1=obsdata->numEntries();
  for (int i=0 ; i<nevt1 ; i++) {
    obsdata->get(i) ;
    h_data.Fill( xdata->getVal(), obsdata->weight() );
  }
  // Now, reset!
  obsdata->reset();
  for( int ibin = 1 ; ibin <= x->numBins() ; ibin++) {
    if(h_data.GetBinContent(ibin)==0){
      cout<<"Bin "<<ibin<<" has 0 content. Inject ghost event..."<<endl;
      x->setVal(h_data.GetBinCenter(ibin));
      w->setVal(ghostwt);
      obsdata->add( RooArgSet(*x,*w), ghostwt);
    }
    else{
      x->setVal(h_data.GetBinCenter(ibin));
      w->setVal(h_data.GetBinContent(ibin));
      obsdata->add(RooArgSet(*x,*w), h_data.GetBinContent(ibin));
    }
  }
}

RooCurve* statistics::createBand(RooCurve *cenCurve, RooAbsPdf *pdf, RooRealVar *x, RooFitResult *res, RooArgSet *params, double Z, int scale, bool isHist){
  // Generate 100 random parameter points distributed according to fit result covariance matrix
  unique_ptr<RooAbsPdf> cloneFunc((RooAbsPdf*)pdf->cloneTree());
  RooArgSet *cloneParams=cloneFunc->getObservables(res->floatParsFinal());
  RooArgSet *errorParams=(RooArgSet*)cloneParams->selectCommon(*params);
  unique_ptr<RooAbsPdf> paramPdf(res->createHessePdf(*errorParams));

  unique_ptr<RooDataSet> asimovData;

  Int_t n = Int_t(100./TMath::Erfc(Z/sqrt(2.)))*scale;
  if (n<100) n=100 ;

  // Generate variation curves with above set of parameter values
  RooRandom::randomGenerator() -> SetSeed(0) ;
  RooDataSet* d = paramPdf->generate(*errorParams,n) ;
  vector<RooCurve*> cvec ;
  for (int i=0 ; i<d->numEntries() ; i++) {
    *cloneParams = (*d->get(i)) ;
    unique_ptr<RooDataSet> asimovData_tmp((RooDataSet*)AsymptoticCalculator::GenerateAsimovData(*cloneFunc, RooArgSet(*x)));
    RooRealVar w("w","w",1);
    asimovData.reset(new RooDataSet("asimovData_tmp","asimovData_tmp", RooArgSet(*x, w), WeightVar(w)));
    statistics::copyDataSet(asimovData_tmp.get(), x, asimovData.get(), x, &w);
    releaseTheGhost(asimovData.get(), x, &w, 1e-9);

    cvec.push_back(convertAsimovToCurve(asimovData.get(), x->GetName(), isHist));
  }
  // RooCurve *band = makeErrorBand(cenCurve,cvec,Z);
  RooCurve *band = cenCurve->makeErrorBand(cvec,Z);
  return band;
}

RooFitResult* statistics::profileToData(ModelConfig *mc, RooAbsData *data, TString _minimizerAlgo, int _minimizerStrategy, double _minimizerTolerance, int _printLevel, bool doHesse, bool doMinos){
  RooMsgService::instance().getStream(1).removeTopic(RooFit::NumIntegration) ;
  RooMsgService::instance().getStream(1).removeTopic(RooFit::Fitting) ;
  RooMsgService::instance().getStream(1).removeTopic(RooFit::Minimization) ;
  RooMsgService::instance().getStream(1).removeTopic(RooFit::InputArguments) ;
  RooMsgService::instance().getStream(1).removeTopic(RooFit::Eval) ;

  RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);

  RooAbsPdf *pdf=mc->GetPdf();

  RooWorkspace *w=mc->GetWS();
  RooArgSet funcs = w->allPdfs();
  std::auto_ptr<TIterator> iter(funcs.createIterator());
  for ( RooAbsPdf* v = (RooAbsPdf*)iter->Next(); v!=0; v = (RooAbsPdf*)iter->Next() ) {
    std::string name = v->GetName();
    if (v->IsA() == RooRealSumPdf::Class()) {
      std::cout << "\tset binned likelihood for: " << v->GetName() << std::endl;
      v->setAttribute("BinnedLikelihood", true);
    }
  }
  unique_ptr<RooAbsReal> nll(pdf->createNLL(*data, Constrain(*mc->GetNuisanceParameters()), GlobalObservables(*mc->GetGlobalObservables())));
  nll->enableOffsetting(true);
  RooMinimizer minim(*nll);
  minim.setStrategy(_minimizerStrategy);
  minim.setPrintLevel(_printLevel);
  // minim.setProfile(); /* print out time */
  minim.setEps(_minimizerTolerance/1e-3);
  minim.optimizeConst(2);
  int status=minim.minimize(_minimizerAlgo);
  if(status!=0) abort();
  if(doHesse) minim.hesse();
  if(doMinos) minim.minos();
  return minim.save();
}
