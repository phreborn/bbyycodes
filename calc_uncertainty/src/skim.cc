#include "CommonHead.h"
#include "CommonFunc.h"
#include "MyGRL.h"

using namespace std;
using namespace CommonFunc;
// Wen's repository:     /afs/cern.ch/user/w/wguan/workdisk/public/mxaod/
// Shaojun's repository: /afs/cern.ch/user/s/shsun/workarea/public/mxaod/
// HGam repository:      HSG1/MxAOD/h012/

// Input/grl/data16_13TeV.periodAllYear_DetStatus-v78-pro20-04_DQDefects-00-02-02_PHYS_StandardGRL_All_Good_25ns_ignore_TOROID_STATUS.xml
int main(int argc, char**argv){
  gErrorIgnoreLevel = kError+1;
  TString inputFileName=argv[1];
  TString outputFileName=argv[2];
  
  TChain *c=MakeChain("CollectionTree", inputFileName, "badfile", inputFileName.Contains(".root"));
  cout<<c<<endl;

  int nevt=c->GetEntries();
  // MxAODNtup *p=new MxAODNtup(c);
  
  TFile *fout=TFile::Open(outputFileName,"recreate");

  float mass;
  ULong64_t eventNumber;
  UInt_t runNumber;
  Char_t isPassedLowHighMyy, isPassedExotic, isDalitz, isPassedIsolationLowHighMyy;

  c->SetBranchStatus("*",0);
  c->SetBranchStatus("HGamEventInfoAuxDyn.m_yy",1);
  c->SetBranchStatus("HGamEventInfoAuxDyn.isPassedExotic",1);
  c->SetBranchStatus("HGamEventInfoAuxDyn.isPassedLowHighMyy",1);
  c->SetBranchStatus("HGamEventInfoAuxDyn.isPassedIsolationLowHighMyy",1);
  
  c->SetBranchAddress("HGamEventInfoAuxDyn.m_yy",&mass);
  c->SetBranchAddress("HGamEventInfoAuxDyn.isPassedExotic",&isPassedExotic);
  c->SetBranchAddress("HGamEventInfoAuxDyn.isPassedIsolationLowHighMyy",&isPassedIsolationLowHighMyy);
  c->SetBranchAddress("HGamEventInfoAuxDyn.isPassedLowHighMyy",&isPassedLowHighMyy);

  TTree *tout=(TTree*)c->CloneTree(0);
  
  for(int ievt=0;ievt<nevt;ievt++){
    // cout<<ievt/double(nevt)*100<<"\r"<<flush;
    // cout<<"Okay 1"<<endl;
    c->GetEntry(ievt);
    // cout<<"Okay"<<endl;
    // cout<<runNumber<<" "<<eventNumber<<" "
    // 	<<bool(isPassedExotic)<<" "<<bool(isPassedLowHighMyy)<<" "
    // 	<<mass
    // 	<<endl;
    if(!((bool(isPassedLowHighMyy)||bool(isPassedExotic))&&mass>150*GeV)) continue;
    tout->Fill();
    if (ievt%1000 == 1) tout->AutoSave("SaveSelf");
  }
  fout->cd();
  tout->Write();
  fout->Close();
}
