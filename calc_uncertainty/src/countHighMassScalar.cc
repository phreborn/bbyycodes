#include "CommonHead.h"
#include "CommonFunc.h"

using namespace std;

const double epsilon=1e-4;

int main(int argc, char **argv){
  if(argc<3){
    cout<<"Usage: "<<argv[0]<<" <jobname> <input file list> <option>"<<endl;
    exit(0);
  }
  CommonFunc::SetAtlasStyle();
  TString jobname=argv[1];
  TString inputFileList=argv[2];
  TString option=argv[3];

  unique_ptr<TChain> c(CommonFunc::MakeChain("CollectionTree",inputFileList,"badfile", inputFileList.Contains(".root")));

  int nevt=c->GetEntries();

  float mass, weight;
  ULong64_t eventNumber;
  UInt_t runNumber;
  char isPassedLowHighMyy, isPassedExotic, isDalitz;
  vector<int>     *conversionType=0;
  vector<float>   *eta_s2=0;
  
  gErrorIgnoreLevel = kError+1;
  c->SetBranchAddress("EventInfoAuxDyn.runNumber",&runNumber);
  c->SetBranchAddress("EventInfoAuxDyn.eventNumber",&eventNumber);

  c->SetBranchAddress("HGamEventInfoAuxDyn.m_yy",&mass);
  c->SetBranchAddress("HGamEventInfoAuxDyn.weight",&weight);

  c->SetBranchAddress("HGamEventInfoAuxDyn.isDalitz",&isDalitz);
  c->SetBranchAddress("HGamEventInfoAuxDyn.isPassedExotic",&isPassedExotic);
  c->SetBranchAddress("HGamEventInfoAuxDyn.isPassedLowHighMyy",&isPassedLowHighMyy);

  c->SetBranchAddress("HGamPhotonsAuxDyn.conversionType", &conversionType);
  c->SetBranchAddress("HGamPhotonsAuxDyn.eta_s2", &eta_s2);
  
  double yield[3]={0,0,0};

  for(int ievt=0;ievt<nevt;ievt++){
    if(ievt%100==0){
      cout<<"Processing "<<ievt*100./double(nevt)<<"% of events...\r"<<std::flush;
    }
    c->GetEntry(ievt);

    if(option.Contains("HKHI")&&!(isPassedLowHighMyy&&!isDalitz)) continue;
    else if(option.Contains("EKHI")&&!(isPassedLowHighMyy&&!isDalitz)) continue;

    if(option.Contains("UC2")){
      if(conversionType->at(0)==0&&conversionType->at(1)==0) yield[0]+=weight;
      else yield[1]+=weight;
    }
    if(option.Contains("BE2")){
      if(fabs(eta_s2->at(0))<1.375&&fabs(eta_s2->at(1))<1.375) yield[0]+=weight;
      else yield[1]+=weight;
    }
    if(option.Contains("BE3")){
      if(fabs(eta_s2->at(0))<1.375&&fabs(eta_s2->at(1))<1.375) yield[0]+=weight;
      else if(fabs(eta_s2->at(0))<1.375||fabs(eta_s2->at(1))<1.375) yield[1]+=weight;
      else yield[2]+=weight;
    }
    if(option.Contains("CF2")){
      if(fabs(eta_s2->at(0))<0.75&&fabs(eta_s2->at(1))<0.75) yield[0]+=weight;
      else yield[1]+=weight;
    }
    if(option.Contains("CF3")){
      if(fabs(eta_s2->at(0))<0.75&&fabs(eta_s2->at(1))<0.75) yield[0]+=weight;
      else if((fabs(eta_s2->at(0))>1.3&&fabs(eta_s2->at(0))<1.75)||(fabs(eta_s2->at(1))>1.3&&fabs(eta_s2->at(1))<1.75)) yield[1]+=weight;
      else yield[2]+=weight;
    }
  }
  ofstream fout("/afs/cern.ch/user/y/yanght/workarea/GG/xmlAnaWSBuilder/config/high_mass_diphoton/improve/frac/hkhi/"+jobname);
  cout<<yield[0]/(yield[0]+yield[1]+yield[2])
      <<" "<<yield[1]/(yield[0]+yield[1]+yield[2])
      <<" "<<yield[2]/(yield[0]+yield[1]+yield[2])
      <<endl;
  fout<<yield[0]/(yield[0]+yield[1]+yield[2])
      <<" "<<yield[1]/(yield[0]+yield[1]+yield[2])
      <<" "<<yield[2]/(yield[0]+yield[1]+yield[2])
      <<endl;
}

