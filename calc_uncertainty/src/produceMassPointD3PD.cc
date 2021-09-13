#include "CommonHead.h"
#include "CommonFunc.h"
#include "Hgg_tree.h"

using namespace std;

int main(int argc, char**argv){
  TString inputFileName=argv[1];
  TString outputFileName=argv[2];
  TString selection=argv[3];
  
  TChain *c=CommonFunc::MakeChain("Hgg_tree", inputFileName, "badfile", inputFileName.Contains(".root"));
  Hgg_tree *p=new Hgg_tree(c);
  
  int nevt=c->GetEntries();

  ofstream fout(outputFileName);
  for(int ievt=0;ievt<nevt;ievt++){
    if(ievt%100==0){
      cout<<"Processing "<<ievt*100./double(nevt)<<"% of events...\r"<<std::flush;
    }
    p->fChain->GetEntry(ievt);
    if(p->flag_pre_graviton && p->flag_pt_graviton && p->flag_PID && p->flag_iso_graviton && p->flag_mgg_150) fout<<p->mass_PV_EM/CommonFunc::GeV<<endl;
  }
  fout.close();
}
