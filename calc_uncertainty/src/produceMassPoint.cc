#include "CommonHead.h"
#include "CommonFunc.h"
#include "MxAODNtup.h"

using namespace std;

int main(int argc, char**argv){
  TString inputFileName=argv[1];
  TString outputFileName=argv[2];
  TString selection=argv[3];
  
  TChain *c=CommonFunc::MakeChain("CollectionTree", inputFileName, "badfile", inputFileName.Contains(".root"));

  int nevt=c->GetEntries();

  MxAODNtup *p=new MxAODNtup(c);
  
  ofstream fout(outputFileName);
  for(int ievt=0;ievt<nevt;ievt++){
    c->GetEntry(ievt);
    // if((selection=="scalar"&&p->isPassedLowHighMyy&&!p->isDalitz&&p->m_yy>150*CommonFunc::GeV)||(selection=="graviton"&&p->isPassedExotic&&p->isPassedIsolationLowHighMyy&&!p->isDalitz&&p->m_yy>200*CommonFunc::GeV))
    bool passCaloISO=(p->topoetcone40->at(0)<p->pt->at(0)*0.022+2450)&&(p->topoetcone40->at(1)<p->pt->at(1)*0.022+2450);
    bool passTrkISO=(p->ptcone20_corr->at(0)<p->pt->at(0)*0.05)&&(p->ptcone20_corr->at(1)<p->pt->at(1)*0.05);
    if(p->isPassedPID&&p->isPassedPreselection&&passCaloISO&&passTrkISO&&((selection=="scalar"&&p->isPassedRelPtCutsLowHighMyy&&p->m_yy>150*CommonFunc::GeV)||(selection=="graviton"&&p->isPassedExotic&&p->m_yy>200*CommonFunc::GeV)))
      fout<<p->m_yy/CommonFunc::GeV<<endl;
  }
  fout.close();
}
