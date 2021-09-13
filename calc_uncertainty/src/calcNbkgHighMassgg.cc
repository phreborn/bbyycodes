#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"
#include "titleList.hh"
#include "HggTwoSidedCBPdf.hh"
#include "statistics.hh"
#include "TMVA/Tools.h"
using namespace std;
using namespace RooFit;
using namespace RooStats;
using namespace CommonFunc;

bool _nllOffset=true;
int _minimizerStrategy=1;
string _minimizerAlgo="Minuit2";
double _minimizerTolerance=1e-5;
int _printLevel=0;

RooFitResult* profileToData(ModelConfig *mc, RooAbsData *data){
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
  nll->enableOffsetting(_nllOffset);
  RooMinimizer minim(*nll);
  minim.setStrategy(_minimizerStrategy);
  minim.setPrintLevel(_printLevel-1);
  minim.setProfile(); /* print out time */
  minim.setEps(_minimizerTolerance/0.001);
  // minim.optimizeConst(2);
  int status=minim.minimize(_minimizerAlgo.c_str());
  status += minim.hesse();
  if(status!=0) abort();
  return minim.save();
}

void calcNbkg(RooCurve* nominal, RooCurve* band, double& central, double& errHi, double& errLow) {
    RooCurve *upper=new RooCurve();
    RooCurve *lower=new RooCurve();
    int npoint=band->GetN()/2;
    // Split the band into upper and lower errors
    for(int ipoint=0; ipoint<npoint; ipoint++){
      double x,y;
      band->GetPoint(ipoint,x,y);
      lower->addPoint(x,y);
      band->GetPoint(2*npoint-ipoint-1,x,y);
      upper->addPoint(x,y);
    }

    double temp;
    nominal->GetPoint(0, temp, central);
    upper->GetPoint(0, temp, errHi);
    errHi = errHi - central;
    lower->GetPoint(0, temp, errLow);
    errLow = central - errLow;
    /*
      central[itest]=nominal->average(xmin[itest], xmax[itest])*(xmax[itest]-xmin[itest])/binw;
      errHi[itest]=upper->average(xmin[itest], xmax[itest])*(xmax[itest]-xmin[itest])/binw-central[itest];
      errLo[itest]=central[itest]-lower->average(xmin[itest], xmax[itest])*(xmax[itest]-xmin[itest])/binw;
    */

}

/*RooCurve *convertAsimovToCurve(RooDataSet *asimov, TString observableName, bool isHist, double epsilon=1e-6){
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
      // cout<<mass<<" "
      // 	  <<mass-0.5*binw<<" "
      // 	  <<mass+0.5*binw<<" "
      // 	  <<weight<<endl; getchar();
    }
    else{
      curve->addPoint(mass,weight);
    }
  }
  return curve;
}*/

RooCurve *convertAsimovToCurve(RooDataSet *asimov, TString observableName, bool isHist, double epsilon=1e-6){
  RooCurve *curve=new RooCurve();
  RooArgSet* obs = const_cast<RooArgSet*>(asimov->get());
  RooRealVar* xdata = dynamic_cast<RooRealVar*>(obs->find(observableName));
  double binw=0;
  if(isHist) binw=(xdata->getMax()-xdata->getMin())/double(xdata->numBins());
  
  double integral = 0;
  for (int i=0 ; i<asimov->numEntries() ; i++) {
    asimov->get(i) ;
    double mass=xdata->getVal();
    double weight=asimov->weight();

  }
  TString cutName = "120 < " + observableName + " && " + observableName + " < 130";
  integral = asimov->sumEntries(cutName);
  curve->addPoint(0,integral);

  return curve;
}

void releaseTheGhost(RooDataSet *obsdata, RooRealVar *x, RooRealVar *w, double ghostwt){
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

RooCurve *createBand(RooCurve *cenCurve, RooAbsPdf *pdf, RooRealVar *x, RooFitResult *res, RooArgSet *params, double Z=1, bool isHist=false){
  // Generate 100 random parameter points distributed according to fit result covariance matrix
  unique_ptr<RooAbsPdf> cloneFunc((RooAbsPdf*)pdf->cloneTree());
  RooArgSet *cloneParams=cloneFunc->getObservables(res->floatParsFinal());
  RooArgSet *errorParams=(RooArgSet*)cloneParams->selectCommon(*params);
  unique_ptr<RooAbsPdf> paramPdf(res->createHessePdf(*errorParams));

  unique_ptr<RooDataSet> asimovData;

  //Int_t n = Int_t(1./TMath::Erfc(Z/sqrt(2.)))*1; // <- ALEX: quick version for testing
  Int_t n = Int_t(100./TMath::Erfc(Z/sqrt(2.)))*100; // <- ALEX: for the final result
  if (n<100) n=100 ;

  // Generate variation curves with above set of parameter values
  //RooRandom::randomGenerator() -> SetSeed(0) ;
  gRandom->SetSeed(0);
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

  RooCurve *band = cenCurve->makeErrorBand(cvec,Z);
  return band;
}

int main(int argc, char**argv){
    //============================ Global booking and setting ==========================
  //   gErrorIgnoreLevel = kError+1;
  map<string,bool> Opt;
  Opt["FIT"]=false;

  TString myOptList="";
  if(argc>1) myOptList=argv[1];
  myOptList.ToUpper();
  if (myOptList != "") {
    for (std::map<std::string,bool>::iterator it = Opt.begin(); it != Opt.end(); it++) it->second = false;

    std::vector<TString> olist = TMVA::gTools().SplitString( myOptList, ',' );
    for (UInt_t i=0; i<olist.size(); i++) {
      std::string Option(olist[i]);
      
      if (Opt.find(Option) == Opt.end()) {
	std::cout << "Option \"" << Option << "\" not known in DrawFrame under this name. Choose among the following:" << std::endl;
	for (std::map<std::string,bool>::iterator it = Opt.begin(); it != Opt.end(); it++) std::cout << it->first << " ";
	std::cout << std::endl;
	return 1;
      }
      Opt[Option] = true;
    }
  }
  SetAtlasStyle();
  map<TString,TString> title=createTitleList();
  //================================= Do the fit ====================================
  if(Opt["FIT"]){
    RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
    TString jobname=argv[2];
    TString inputWSFileName=argv[3];
    
    TString option=argv[4];
    
    TString wname="combWS", mname="ModelConfig", dname="combData";

    if(option.Contains("mt")) dname+="binned";
    if(option.Contains("asimov")) dname="asimovData_1";//ALEX: Use an asimov dataset generated by fitting the sideband only for the cont. bkg, and then adding the SM signal on top (to be consistent with the existing table yields);
    TFile *fws=TFile::Open(inputWSFileName);
    RooWorkspace *ws=(RooWorkspace*)fws->Get(wname);
    ModelConfig *mc=(ModelConfig*)ws->obj(mname);
    RooSimultaneous *pdf=(RooSimultaneous*)mc->GetPdf();
    RooDataSet *data=(RooDataSet*)ws->data(dname);
    RooAbsCategoryLValue*  m_cat = (RooAbsCategoryLValue*)&pdf->indexCat();
    RooArgSet *nuis=(RooArgSet*)mc->GetNuisanceParameters();
    
    int numChannels = m_cat->numBins(0);

    TList* m_dataList = data->split( *m_cat, true );

    RooArgSet *fullSet=new RooArgSet();
    RooArgSet *statSet=new RooArgSet();
    RooArgSet *fixSet=new RooArgSet();
    
    //ws->loadSnapshot("conditionalGlobs_1");
    //ws->loadSnapshot("conditionalNuis_1");
    ws->var("mu_XS_HH")->setVal(0);   //ALEX: Tell the program that the main POI in the fit is mu_XS_HH (otherwise it will not know).
    ws->var("mu_XS_HH")->setConstant(false);

    cout << inputWSFileName << "\t" << option << endl;

    //ALEX: we run this a few times with different options. 1 option for each row in the yield table.
    //When we try to get the uncertainty for a particular process (e.g. HH signal), we should set the other processes (e.g. cont bkg) to 0.
    //And we should only consider uncertainties that affect that particular process. 

    //here we list the uncertainties that we need to consider for each process
    //fullSet = list of uncertainties to consider
    if (option.Contains("HH") || option.Contains("H")) {
    //no ss uncertainty for HH or H components
    fullSet->add(*nuis->selectByName("A*")); //exp systematics
    fullSet->add(*nuis->selectByName("T*")); //theory systematics

    } else if (option.Contains("BKG")) {
    //for cont. bkg. 
    fullSet->add(*nuis->selectByName("BKG*")); // bkg slope parameter
    fullSet->add(*nuis->selectByName("S*")); // spurious signal
    fullSet->add(*nuis->selectByName("nbkg*")); // bkg normalization parameter
    fullSet->add(*nuis->selectByName("A*"));  //for the BKG option, we don't need to disable the exp/theory systematics here because later we will set mu = 0
    fullSet->add(*nuis->selectByName("T*"));

    }

    //statSet->add(*nuis->selectByName("BKG*"));
    //statSet->add(*nuis->selectByName("nbkg*"));

    statistics::constSet(fixSet,true);

    //cout<<"Summary of parameters:"<<endl;
    //cout<<"Full set:"<<endl;
    //fullSet->Print("V");
    //cout<<"Stat set:"<<endl;
    //statSet->Print("V");
    //cout<<"Fix set:"<<endl;
    //fixSet->Print("V");
    
    RooFitResult* res=profileToData(mc, data);
    //res->Print();
    //cout << "parameters" << endl;
    //res->floatParsFinal().Print("s");
    //cout << "Correlation matrix" << endl;
    //res->correlationMatrix().Print("V");

    //here we set the other processes to 0
    if (option.Contains("HH_ALL")) {
      //set single H and cont bkg and ss to 0
      statistics::setVal(ws->var("mu_XS_H"), 0, true);
      statistics::setVal(ws->var("nbkg_SM_1"), 0, true);
      statistics::setVal(ws->var("nbkg_SM_2"), 0, true);
      statistics::setVal(ws->var("nbkg_BSM_1"), 0, true);
      statistics::setVal(ws->var("nbkg_BSM_2"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_SM_1"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_SM_2"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_BSM_1"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_BSM_2"), 0, true);
    } else if (option.Contains("HH_ggF")) {
      //set VBF HH and single H and cont bkg and ss to 0
      //statistics::setVal(ws->var("mu_XS_HH_ggF"), 0, true);
      statistics::setVal(ws->var("mu_XS_HH_VBF"), 0, true);
      statistics::setVal(ws->var("mu_XS_H"), 0, true);
      statistics::setVal(ws->var("nbkg_SM_1"), 0, true);
      statistics::setVal(ws->var("nbkg_SM_2"), 0, true);
      statistics::setVal(ws->var("nbkg_BSM_1"), 0, true);
      statistics::setVal(ws->var("nbkg_BSM_2"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_SM_1"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_SM_2"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_BSM_1"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_BSM_2"), 0, true);
    } else if (option.Contains("HH_VBF")) {
      //set ggF HH and single H and cont bkg and ss to 0
      statistics::setVal(ws->var("mu_XS_HH_ggF"), 0, true);
      //statistics::setVal(ws->var("mu_XS_HH_VBF"), 0, true);
      statistics::setVal(ws->var("mu_XS_H"), 0, true);
      statistics::setVal(ws->var("nbkg_SM_1"), 0, true);
      statistics::setVal(ws->var("nbkg_SM_2"), 0, true);
      statistics::setVal(ws->var("nbkg_BSM_1"), 0, true);
      statistics::setVal(ws->var("nbkg_BSM_2"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_SM_1"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_SM_2"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_BSM_1"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_BSM_2"), 0, true);
    } else if (option.Contains("H_ggH")) {
      //set HH and other H and cont bkg and ss to 0
      statistics::setVal(ws->var("mu_XS_HH"), 0, true);
      //statistics::setVal(ws->var("mu_XS_ggH"), 0, true);
      statistics::setVal(ws->var("mu_XS_VBF"), 0, true);
      statistics::setVal(ws->var("mu_XS_WH"), 0, true);
      statistics::setVal(ws->var("mu_XS_ZH"), 0, true);
      statistics::setVal(ws->var("mu_XS_ttH"), 0, true);
      statistics::setVal(ws->var("mu_XS_tHjb"), 0, true);
      statistics::setVal(ws->var("mu_XS_tWH"), 0, true);
      statistics::setVal(ws->var("nbkg_SM_1"), 0, true);
      statistics::setVal(ws->var("nbkg_SM_2"), 0, true);
      statistics::setVal(ws->var("nbkg_BSM_1"), 0, true);
      statistics::setVal(ws->var("nbkg_BSM_2"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_SM_1"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_SM_2"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_BSM_1"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_BSM_2"), 0, true);      
    } else if (option.Contains("H_ttH")) {
      //set HH and other H and cont bkg and ss to 0
      statistics::setVal(ws->var("mu_XS_HH"), 0, true);
      statistics::setVal(ws->var("mu_XS_ggH"), 0, true);
      statistics::setVal(ws->var("mu_XS_VBF"), 0, true);
      statistics::setVal(ws->var("mu_XS_WH"), 0, true);
      statistics::setVal(ws->var("mu_XS_ZH"), 0, true);
      //statistics::setVal(ws->var("mu_XS_ttH"), 0, true);
      statistics::setVal(ws->var("mu_XS_tHjb"), 0, true);
      statistics::setVal(ws->var("mu_XS_tWH"), 0, true);
      statistics::setVal(ws->var("nbkg_SM_1"), 0, true);
      statistics::setVal(ws->var("nbkg_SM_2"), 0, true);
      statistics::setVal(ws->var("nbkg_BSM_1"), 0, true);
      statistics::setVal(ws->var("nbkg_BSM_2"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_SM_1"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_SM_2"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_BSM_1"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_BSM_2"), 0, true);
    } else if (option.Contains("H_ZH")) {
      //set HH and other H and cont bkg and ss to 0
      statistics::setVal(ws->var("mu_XS_HH"), 0, true);
      statistics::setVal(ws->var("mu_XS_ggH"), 0, true);
      statistics::setVal(ws->var("mu_XS_VBF"), 0, true);
      statistics::setVal(ws->var("mu_XS_WH"), 0, true);
      //statistics::setVal(ws->var("mu_XS_ZH"), 0, true);
      statistics::setVal(ws->var("mu_XS_ttH"), 0, true);
      statistics::setVal(ws->var("mu_XS_tHjb"), 0, true);
      statistics::setVal(ws->var("mu_XS_tWH"), 0, true);
      statistics::setVal(ws->var("nbkg_SM_1"), 0, true);
      statistics::setVal(ws->var("nbkg_SM_2"), 0, true);
      statistics::setVal(ws->var("nbkg_BSM_1"), 0, true);
      statistics::setVal(ws->var("nbkg_BSM_2"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_SM_1"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_SM_2"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_BSM_1"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_BSM_2"), 0, true);
    } else if (option.Contains("H_REST")) {
      //set HH and other H and cont bkg and ss to 0
      statistics::setVal(ws->var("mu_XS_HH"), 0, true);
      statistics::setVal(ws->var("mu_XS_ggH"), 0, true);
      //statistics::setVal(ws->var("mu_XS_VBF"), 0, true);
      //statistics::setVal(ws->var("mu_XS_WH"), 0, true);
      statistics::setVal(ws->var("mu_XS_ZH"), 0, true);
      statistics::setVal(ws->var("mu_XS_ttH"), 0, true);
      //statistics::setVal(ws->var("mu_XS_tHjb"), 0, true);
      //statistics::setVal(ws->var("mu_XS_tWH"), 0, true);
      statistics::setVal(ws->var("nbkg_SM_1"), 0, true);
      statistics::setVal(ws->var("nbkg_SM_2"), 0, true);
      statistics::setVal(ws->var("nbkg_BSM_1"), 0, true);
      statistics::setVal(ws->var("nbkg_BSM_2"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_SM_1"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_SM_2"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_BSM_1"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_BSM_2"), 0, true);      
    } else if (option.Contains("H_ALL")) {
      //set HH and cont bkg and ss to 0
      statistics::setVal(ws->var("mu_XS_HH"), 0, true);
      statistics::setVal(ws->var("nbkg_SM_1"), 0, true);
      statistics::setVal(ws->var("nbkg_SM_2"), 0, true);
      statistics::setVal(ws->var("nbkg_BSM_1"), 0, true);
      statistics::setVal(ws->var("nbkg_BSM_2"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_SM_1"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_SM_2"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_BSM_1"), 0, true);
      statistics::setVal(ws->var("SPURIOUS_BSM_2"), 0, true);

    } else if (option.Contains("BKG")) {
      //set H and HH to 0
      statistics::setVal(ws->var("mu_XS_HH"), 0, true);
      statistics::setVal(ws->var("mu_XS_H"), 0, true);
    } 

    for ( int i= 0; i < numChannels; i++ ) {
      m_cat->setBin(i);
      TString channelname=m_cat->getLabel();
      RooAbsPdf* pdfi = pdf->getPdf(m_cat->getLabel());
      RooDataSet* datai = ( RooDataSet* )( m_dataList->At( i ) );
      //std::cout << "\t\tIndex: " << i << ", Pdf: " << pdfi->GetName() << ", Data: " << datai->GetName()  << ", SumEntries: " << datai->sumEntries() << " NumEntries: "<< datai->numEntries() <<std::endl;
    
      RooRealVar *x=(RooRealVar*)pdfi->getObservables(datai)->first();

      AsymptoticCalculator::SetPrintLevel(0);
      unique_ptr<RooDataSet> asimovData((RooDataSet*)AsymptoticCalculator::GenerateAsimovData(*pdfi, RooArgSet(*x)));
      RooCurve *cenCurve=convertAsimovToCurve(asimovData.get(), x->GetName(), option.Contains("mt"));

      cenCurve->SetName("nominal");
      RooCurve* bandFull=createBand(cenCurve, pdfi, x, res, fullSet, 1, option.Contains("mt"));
      bandFull->SetName("bandFull");

      double central = 0, errHi = 0, errLow = 0;
      calcNbkg(cenCurve, bandFull, central, errHi, errLow);
      cout << channelname << " " << central << "+" << errHi << "-" << errLow << endl;
      //RooCurve* bandStat=NULL;
      //bandStat = (RooCurve*)bandFull->Clone();
      //if(option.Contains("fb")) bandStat=(RooCurve*)bandFull->Clone();
      //if(option.Contains("mt")) bandStat=createBand(cenCurve, pdfi, x, res, statSet, 1, option.Contains("mt"));
      
      //bandStat=createBand(cenCurve, pdfi, x, res, statSet, 1, option.Contains("mt"));      
      //bandStat->SetName("bandStat");

      system("mkdir -vp fig/fit/"+jobname);
      TString outputFileName="fig/fit/"+jobname+Form("/output_%d.root", i);
      TFile *fout=TFile::Open(outputFileName,"recreate");
      cenCurve->Write();
      bandFull->Write();
      //bandStat->Write();
      fout->Close();

      ofstream myfile;
      myfile.open("fig/fit/"+jobname+Form("/output_%d.txt", i));
      myfile << central << "+" << errHi << "-" << errLow << endl;    
      myfile.close();
      cout << "Results saved in " << "fig/fit/"+jobname << endl;
      }
  }
}
