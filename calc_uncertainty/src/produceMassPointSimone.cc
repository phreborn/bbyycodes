#include "CommonHead.h"
#include "CommonFunc.h"
#include "gravitonNtup.h"

using namespace std;

int main(int argc, char**argv){
  TString inputFileName=argv[1];
  TString outputFileName=argv[2];
  TString selection=argv[3];
  
  TChain *c=CommonFunc::MakeChain("CollectionTree", inputFileName, "badfile", inputFileName.Contains(".root"));
  gravitonNtup *p=new gravitonNtup(c);
  int nevt=c->GetEntries();

  ofstream fout(outputFileName);
  for(int ievt=0;ievt<nevt;ievt++){
    c->GetEntry(ievt);
    if(p->accepted*p->total_weight==0) continue;
    fout<<p->mgg<<" "<<p->total_weight<<endl;
  }
  fout.close();
}
