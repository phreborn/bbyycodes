#include "CommonHead.h"
#include "CommonFunc.h"
#include "MxAODNtup.h"
#include "MyGRL.h"

using namespace std;
using namespace CommonFunc;

int main(int argc, char** argv){
  MyGRL *grl=new MyGRL("Input/grl/data16_13TeV.periodAllYear_DetStatus-v76-pro20-02_DQDefects-00-02-02_PHYS_StandardGRL_All_Good_25ns_ignore_TOROID_STATUS.xml");
  grl->PrintMap();

  TString inputFileList=argv[1];
  TChain *c=MakeChain("CollectionTree", inputFileList, "badfile", inputFileList.Contains(".root"));

  MxAODNtup *p=new MxAODNtup(c);

  TFile *fout=TFile::Open("Output/data16_grl.root","recreate");
  TTree *t=(TTree*)c->CloneTree(0);
  
  int nevt=p->fChain->GetEntries();
  for(int ievt=0;ievt<nevt;ievt++){
    p->fChain->GetEntry(ievt);
    // bool passGRL=grl->GoodEvent(p->runNumber, p->lumiBlock);
    // if(!passGRL) continue;
  //   t->Fill();
  }
  // fout->cd();
  // t->Write();
  // fout->Close();
}
