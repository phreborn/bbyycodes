#include "CommonHead.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"

using namespace std;
using namespace RooFit;
using namespace RooStats;

int main(int argc, char**argv){
  TString inputFileName=argv[1];
  int seed=atoi(argv[2]);
  
  TString wname="combWS", mname="ModelConfig", dname="combData";
  
  unique_ptr<TFile> fin(TFile::Open(inputFileName));

  RooWorkspace *w=dynamic_cast<RooWorkspace*>(fin->Get(wname));
  ModelConfig *mc=dynamic_cast<ModelConfig*>(w->obj(mname));
  RooAbsData *data=w->data(dname);
  RooAbsPdf *pdf=mc->GetPdf();
  
  unique_ptr<RooAbsReal> nll(pdf->createNLL(*data));
  nll->enableOffsetting(true);
  RooMinimizer minim(*nll);
  minim.setStrategy(1);
  minim.setPrintLevel(0);
  minim.setProfile(); /* print out time */
  minim.setEps(1);
  // minim.optimizeConst(2);
  int status=minim.minimize("Minuit2");

  double NLL=nll->getVal(), xs=w->var("xs")->getVal();
  unique_ptr<TFile> fout(TFile::Open("rs_output.root","recreate"));
  TTree t("toy","toy");

  t.Branch("nll",&NLL,"nll/D");
  t.Branch("xs",&xs,"xs/D");
  t.Branch("seed",&seed,"seed/I");
  t.Branch("status",&status,"status/I");

  t.Fill();
  
  fout->cd();
  t.Write();
  fout->Close();
  
  fin->Close();
}
