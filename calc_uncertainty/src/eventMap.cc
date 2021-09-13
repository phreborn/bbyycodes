#include "CommonHead.h"
#include "CommonFunc.h"

#include "MxAODNtup.h"

using namespace std;
using namespace CommonFunc;

vector<pair<UInt_t, ULong64_t> > createList(MxAODNtup *p){
  vector<pair<UInt_t, ULong64_t> > result;
  int nevt=p->fChain->GetEntries();
  for(int ievt=0;ievt<nevt;ievt++){
    p->fChain->GetEntry(ievt);
    if(bool(p->isPassedExotic)&&bool(p->isPassedIsolationLowHighMyy)&&p->m_yy>700*GeV&&p->m_yy<800*GeV) result.push_back(make_pair(p->runNumber, p->eventNumber));
  }
  return result;
}

bool searchList(vector<pair<UInt_t, ULong64_t> > list, UInt_t runNumber, ULong64_t eventNumber){
  for(vector<pair<UInt_t, ULong64_t> >::iterator it=list.begin(); it!=list.end();++it){
    if(it->first==runNumber&&it->second==eventNumber) return true;
  }
  return false;
}

int main( int argc, char** argv ){
  SetAtlasStyle();

  TString inputFileName1="Output/sample/data/skim_h011.root";
  TString inputFileName2="Output/sample/data/skim_h011b.root";
  TString inputFileName3="Output/sample/data/skim_h012pre2.root";
  TString inputFileName4="Output/sample/data/skim_h012.root";

  TChain *c1=MakeChain("CollectionTree",inputFileName1,inputFileName1+".bdf",inputFileName1.Contains(".root"));
  TChain *c2=MakeChain("CollectionTree",inputFileName2,inputFileName2+".bdf",inputFileName2.Contains(".root"));
  TChain *c3=MakeChain("CollectionTree",inputFileName3,inputFileName3+".bdf",inputFileName3.Contains(".root"));
  TChain *c4=MakeChain("CollectionTree",inputFileName4,inputFileName4+".bdf",inputFileName4.Contains(".root"));

  MxAODNtup *p1=new MxAODNtup(c1);
  MxAODNtup *p2=new MxAODNtup(c2);
  MxAODNtup *p3=new MxAODNtup(c3);
  MxAODNtup *p4=new MxAODNtup(c4);

  vector<pair<UInt_t, ULong64_t> > list1=createList(p1);
  vector<pair<UInt_t, ULong64_t> > list2=createList(p2);
  vector<pair<UInt_t, ULong64_t> > list3=createList(p3);
  vector<pair<UInt_t, ULong64_t> > list4=createList(p4);

  vector<pair<UInt_t, ULong64_t> > commonList;

  TString inputFullFileName1="HSG1/MxAOD/h011/data_25ns/data15_13TeV.periodAll25ns.physics_Main.MxAOD.p2425.h011.root";
  TString inputFullFileName2="HSG1/MxAOD/h011b/data_25ns/data15_13TeV.periodAllYear.physics_Main.MxAOD.p2614.h011b.root";
  TString inputFullFileName3="HSG1/MxAOD/h012pre2/data15/data15_13TeV.periodAllYear_3194ipb.physics_Main.MxAOD.p2614.h012pre2.root";
  TString inputFullFileName4="HSG1/MxAOD/h012/data15/data15_13TeV.periodAllYear_3245ipb.physics_Main.MxAOD.p2614.h012.root";

  TChain *cfull1=MakeChain("CollectionTree",inputFullFileName1,inputFullFileName1+".bdf",inputFullFileName1.Contains(".root"));
  TChain *cfull2=MakeChain("CollectionTree",inputFullFileName2,inputFullFileName2+".bdf",inputFullFileName2.Contains(".root"));
  TChain *cfull3=MakeChain("CollectionTree",inputFullFileName3,inputFullFileName3+".bdf",inputFullFileName3.Contains(".root"));
  TChain *cfull4=MakeChain("CollectionTree",inputFullFileName4,inputFullFileName4+".bdf",inputFullFileName4.Contains(".root"));
  
  MxAODNtup *pfull1=new MxAODNtup(cfull1);
  MxAODNtup *pfull2=new MxAODNtup(cfull2);
  MxAODNtup *pfull3=new MxAODNtup(cfull3);
  MxAODNtup *pfull4=new MxAODNtup(cfull4);

  // Collection events which survive all selections
  for(vector<pair<UInt_t, ULong64_t> >::iterator it=list1.begin(); it!=list1.end();++it){
    if(searchList(list2, it->first, it->second)&&searchList(list3, it->first, it->second)&&searchList(list4, it->first, it->second)){
      commonList.push_back(*it);
      list1.erase(it);
      list2.erase(it);
      list3.erase(it);
      list4.erase(it);
    }
  }
  return 0;
}
