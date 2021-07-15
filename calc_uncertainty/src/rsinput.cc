#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"

using namespace std;
using namespace RooFit;
using namespace RooStats;

int main(int argc, char** argv){
  //***************************= Global booking and setting ************************==
  //   gErrorIgnoreLevel = kError+1;
  map<string,bool> Opt;
  Opt["INPUT"]=false;

  TString myOptList="";
  if(argc>1) myOptList=argv[1];
  myOptList.ToUpper();
  if (myOptList != "") {
    for (std::map<std::string,bool>::iterator it = Opt.begin(); it != Opt.end(); it++) it->second = false;

    std::vector<TString> olist = CommonFunc::SplitString( myOptList, ',' );
    for (UInt_t i=0; i<olist.size(); i++) {
      std::string Option(olist[i]);
      
      if (Opt.find(Option) == Opt.end()) {
	std::cout << "Option \"" << Option << "\" not known in DrawFrame under this name. Choose among the following:" << std::endl;
	for (std::map<std::string,bool>::iterator it = Opt.begin(); it != Opt.end(); it++) std::cout << it->first << " ";
	std::cout << std::endl;
	return 1;
      }
      Opt[Option] = true;
    }
  }
  // ************************** Generating inputs ***********************************
  if(Opt["INPUT"]){
    if(argc<4){
      cout<<"Usage: "<<argv[0]<<" "<<argv[1]<<" <jobname> <input list or file> <option>"<<endl;
      return 0;
    }
    gErrorIgnoreLevel=kError+1;
    TString jobname=argv[2];
    TString inputFileName=argv[3];
    TString option=argv[4];

    unique_ptr<TChain> c(CommonFunc::MakeChain("CollectionTree", inputFileName, "badfile", inputFileName.Contains(".root")));
    float mass, weight, sigmaXBRXEff, pt_1st, pt_2nd;
    ULong64_t eventNumber;
    UInt_t runNumber;
    bool isPassedLowHighMass, isPassedExotic, isDalitz;

    c->SetBranchAddress("EventInfoAuxDyn.runNumber",&runNumber);
    c->SetBranchAddress("EventInfoAuxDyn.eventNumber",&eventNumber);
    c->SetBranchAddress("HGamEventInfoAuxDyn.m_yy",&mass);
    c->SetBranchAddress("HGamEventInfoAuxDyn.weight",&weight);
    c->SetBranchAddress("HGamEventInfoAuxDyn.crossSectionBRfilterEff",&sigmaXBRXEff);
    c->SetBranchAddress("HGamEventInfoAuxDyn.isPassedLowHighMyy",&isPassedLowHighMass);
    c->SetBranchAddress("HGamEventInfoAuxDyn.isDalitz",&isDalitz);
    c->SetBranchAddress("HGamEventInfoAuxDyn.isPassedExotic",&isPassedExotic);
    c->SetBranchAddress("HGamEventInfoAuxDyn.pT_y1",&pt_1st);
    c->SetBranchAddress("HGamEventInfoAuxDyn.pT_y2",&pt_2nd);

    int nevt=c->GetEntries();

    system("mkdir -vp Output/datalist/"+jobname);

    ofstream fout("Output/datalist/"+jobname+"/data.txt");

    int nevtScalar=0, nevtGraviton=0, nevtBoth=0;
    
    for ( int ievt = 0; ievt < nevt; ievt++ ) {
      c->GetEntry(ievt);
      if(ievt%100==0){
	cout<<"Processing "<<ievt*100./double(nevt)<<"% of events...\r"<<std::flush;
      }
      if(mass/1000.<150) continue;
      isPassedExotic=(isPassedExotic);
      isPassedLowHighMass=(isPassedLowHighMass);
      
      if(isPassedExotic||isPassedLowHighMass){
	if(isPassedLowHighMass) nevtScalar++;
	if(isPassedExotic) nevtGraviton++;
	if(isPassedLowHighMass&&isPassedExotic) nevtBoth++;
	fout<<runNumber<<" "
	    <<eventNumber<<" "
	    <<mass/1000.<<" "
	    <<isPassedLowHighMass<<" "
	    <<isPassedExotic<<endl;
      }
    }
    
    fout.close();

    cout<<"Scalar analysis: "<<nevtScalar<<" events. Graviton analysis: "<<nevtGraviton<<" events."<<endl;
    cout<<"Only in scalar analysis: "<<nevtScalar-nevtBoth<<", only in graviton analysis: "<<nevtGraviton-nevtBoth<<", overlap: "<<nevtBoth<<endl;
  }
}
