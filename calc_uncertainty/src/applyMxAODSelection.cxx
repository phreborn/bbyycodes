#include "CommonHead.h"
#include "CommonFunc.h"
#include "MxAODNtup.h"

using namespace std;
int main(int argc, char** argv){
  TString inputFileName=argv[1];
  TChain *c=CommonFunc::MakeChain("CollectionTree", inputFileName, "badfile", inputFileName.Contains(".root"));
  MxAODNtup *p=new MxAODNtup(c);
  long int nentries=p->fChain->GetEntries();
  long int counter=0;
  for(long int ientry=0;ientry<nentries;ientry++){
    p->fChain->GetEntry(ientry);
    if(!p->isPassedBasic) continue;
    int size=p->pt->size();
    for(auto pt : *p->pt){
      if(pt<25*CommonFunc::GeV) size--;
    }
    if(size<2) continue;
    counter++;
  }
  cout<<counter<<endl;
}
