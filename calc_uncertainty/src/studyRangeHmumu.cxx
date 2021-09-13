#include "CommonHead.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"
#include "statistics.hh"

using namespace RooFit;
using namespace RooStats;

double getSignificance(ModelConfig *mc, RooAbsData *data){
  mc->GetWS()->var("mu")->setVal(1);
  mc->GetWS()->var("mu")->setConstant(false);
  statistics::fixSyst(mc);
  RooFitResult *resHat=statistics::profileToData(mc, data, "Minuit2", 1, 1e-6, -1, 0, 0);
  double nllHat=resHat->minNll();
  mc->GetWS()->var("mu")->Print();
  mc->GetWS()->var("mu")->setVal(0);
  mc->GetWS()->var("mu")->setConstant(true);
  RooFitResult *resFix=statistics::profileToData(mc, data, "Minuit2", 1, 1e-6, -1, 0, 0);
  double nllFix=resFix->minNll();
  return sqrt(2*(nllHat-nllFix));
}

int main(int argc, char**argv){
  RooMsgService::instance().getStream(1).removeTopic(RooFit::NumIntegration) ;
  RooMsgService::instance().getStream(1).removeTopic(RooFit::Fitting) ;
  RooMsgService::instance().getStream(1).removeTopic(RooFit::Minimization) ;
  RooMsgService::instance().getStream(1).removeTopic(RooFit::InputArguments) ;
  RooMsgService::instance().getStream(1).removeTopic(RooFit::Eval) ;
  RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);
  
  TString inputWSFileName=argv[1];
  TString inputAltWSFileName=argv[2];
  
  TFile *f=TFile::Open(inputWSFileName);
  RooWorkspace *w=(RooWorkspace*)f->Get("combined");
  ModelConfig *mc=(ModelConfig*)w->obj("ModelConfig");
  RooAbsData *data=(RooAbsData*)w->data("asimovData_1");
  RooArgSet *nuis=(RooArgSet*)mc->GetNuisanceParameters();

  TFile *fAlt=TFile::Open(inputAltWSFileName);
  RooWorkspace *wAlt=(RooWorkspace*)fAlt->Get("combined");
  ModelConfig *mcAlt=(ModelConfig*)wAlt->obj("ModelConfig");
  RooArgSet *nuisAlt=(RooArgSet*)mcAlt->GetNuisanceParameters();

  // Copy the NP values
  // nuisAlt->Print("V");
  *nuisAlt=*nuis;
  // nuisAlt->Print("V");

  // Create new Asimov data for alt workspace
  RooSimultaneous* m_pdf = (RooSimultaneous*)mcAlt->GetPdf();
  RooArgSet* Observables=(RooArgSet*)mcAlt->GetObservables();

  RooAbsCategoryLValue*  m_cat = (RooAbsCategoryLValue*)&m_pdf->indexCat();
  int numChannels = m_cat->numBins(0);

  wAlt->var("mu")->setVal(0);
  
  for ( int i= 0; i < numChannels; i++ ) {
    m_cat->setBin(i);
    TString channelname=m_cat->getLabel();
    
    RooAbsPdf* pdfi = m_pdf->getPdf(channelname);

    RooRealVar *x=(RooRealVar*)pdfi->getObservables(Observables)->first();
    x->Print();
    x->setRange("nominal",110,160);
    RooAbsReal *integral=pdfi->createIntegral(RooArgSet(*x), NormSet(*x), Range("nominal"));
    RooAbsReal *integralFull=pdfi->createIntegral(RooArgSet(*x), NormSet(*x));

    RooRealVar *nbkg=wAlt->var("nbkg_"+channelname);
    cout<<nbkg->getVal()<<" "<<integral->getVal()<<" "<<integralFull->getVal()<<endl;
    nbkg->setVal(nbkg->getVal()*integralFull->getVal()/integral->getVal());
    cout<<nbkg->getVal()<<endl;
  }

  wAlt->var("mu")->setVal(1);
  RooAbsData* dataAlt=AsymptoticCalculator::GenerateAsimovData(*mcAlt->GetPdf(), *mcAlt->GetObservables());
  
  cout<<getSignificance(mc, data)<<endl;
  cout<<getSignificance(mcAlt, dataAlt)<<endl;
}
