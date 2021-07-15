#include "CommonHead.h"
#include "CommonFunc.h"
#include "MxAODNtup.h"

using namespace std;
using namespace CommonFunc;

int main(int argc, char** argv){
  TString inputFileName=argv[1];
  TString option=argv[2];
  option.ToLower();
  
  TFile *f=TFile::Open(inputFileName,"read");
  TTree *t=(TTree*)f->Get("CollectionTree");
  TH1F *hcut=(TH1F*)f->Get("CutFlow_PowhegPy8_ggH750_W6p_noDalitz");
  
  MxAODNtup *p=new MxAODNtup(t);

  int nevt=p->fChain->GetEntries();
  double selected=0;
  for(int ievt=0;ievt<nevt;ievt++){
    p->fChain->GetEntry(ievt);
    if(option.Contains("ekhi")){
      if(!(p->isPassedExotic&&p->isPassedIsolationLowHighMyy)) continue;
    }
    if(option.Contains("hkhi")){
      if(!(p->isPassedLowHighMyy&&!p->isDalitz)) continue;
    }
    // selected+=p->vertexWeight*p->mcEventWeights->at(0);;
    selected+=1;
  }
  double ntotal=hcut->GetBinContent(3);

  cout<<selected<<" "<<ntotal<<" "<<selected/ntotal<<endl;
}
