#include "aux/output.C"
#include "TLorentzVector.h"

output *c;

void get_event(int i) {
  if ( c->LoadTree(i) < 0) {
    cout<<"\nProblem in LoadTree."
        <<"\nEntry: "<<i<<endl;
    exit(0);
  }
  c->fChain->GetEntry(i);
}


void Report(const char* _filename_,const char *_output_){
  ofstream fout(_output_,ios::app | ios::out);
  if(!!fout){
    fout<<_filename_<<endl;
    fout.close();
  }
  else Error("Report","cannot open badfiles");
}


TChain* MakeChain(const char* _treename_, TString _listname_, TString _logname_, bool isroot){
  TChain *fchain=new TChain(_treename_);
  if(isroot){
    fchain->Add(_listname_);
    return fchain;
  }
  TString filename;
  ifstream fin(_listname_.Data(),ios::in);
  if(!fin){
    Error("MakeChain","Cannot open list file %s.",_listname_.Data());
    return NULL;
  }
  Int_t n=0;
  int nbad=0;

  cout<<" DATA SETS:"<<endl;
  while(fin>>filename){
    if (!filename.BeginsWith("#")) {
      int status=fchain->AddFile(filename,-1);
      if(!status){
        Report(filename.Data(),_logname_.Data());nbad++;
      }
      else n++;
      if(n%1000==0)
	cout<<"Chaining "<<n<<"th file..."<<filename.Data()<<", "<<nbad<<" files are removed out of them."<<endl;
    }
  }
  cout<<n<<" files are chained."<<endl;
  if(nbad>0) cout<<nbad<<" files are bad. Please check "<<_logname_<<endl;
  cout<<"--------------"<<endl;
  fin.close();
  return fchain;
}
