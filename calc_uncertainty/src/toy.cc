#include "toy.hh"

const double epsilon=1e-5;

void profileToData(ModelConfig *mc, RooAbsData *data){
  RooSimultaneous* combPdf  =  (RooSimultaneous*)mc->GetPdf();
  RooArgSet* nuisanceParameters = (RooArgSet*)mc->GetNuisanceParameters();
  RooArgSet* globalObservables = (RooArgSet*)mc->GetGlobalObservables();
  unique_ptr<RooAbsReal> nll(combPdf->createNLL(*data, Constrain(*nuisanceParameters), GlobalObservables(*globalObservables), Extended(combPdf->canBeExtended())));
  nll->enableOffsetting(true);
  RooMinimizer minim(*nll);
  cout<<"Now performing the fit..."<<endl;
  cout<<ROOT::Math::MinimizerOptions::DefaultMinimizerType()<<" "<<ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str()<<endl;
  minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());
}

int main( int argc , char **argv)
{
  //============================ Global booking and setting ==========================
  map<string,bool> Opt;
  Opt["MU"]=false;

  TString myOptList="";
  if(argc>1) myOptList=argv[1];
  myOptList.ToUpper();
  if (myOptList != "") {
    for (std::map<std::string,bool>::iterator it = Opt.begin(); it != Opt.end(); it++) it->second = false;

    std::vector<TString> olist = SplitString( myOptList, ',' );
    for (UInt_t i=0; i<olist.size(); i++) {
      std::string Option(olist[i]);
      
      if (Opt.find(Option) == Opt.end()) {
	std::cout << "Option \"" << Option << "\" not known in Frame under this name. Choose among the following:" << std::endl;
	for (std::map<std::string,bool>::iterator it = Opt.begin(); it != Opt.end(); it++) std::cout << it->first << " ";
	std::cout << std::endl;
	return 1;
      }
      Opt[Option] = true;
    }
  }

  TString option=argv[argc-1];
  option.ToLower();
  bool m_debug=option.Contains("debug");
  // *******************************************************************************
  if(Opt["MU"]){
    if(argc<6){
      cout<<"Usage: "<<argv[0]<<" "<<argv[1]<<" <seed> <inputFile> <mu> <ntoy> <option>"<<endl;
      return 0;
    }
    
    ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit2");
    ROOT::Math::MinimizerOptions::SetDefaultStrategy(0);
    ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(-1);
    
    int seed = atoi(argv[2]);
    TString inputFile=argv[3];
    double mu=atof(argv[4]);
    int ntoy=atoi(argv[5]);

    TString wname="combWS";
    TString mname="ModelConfig";
    TString dname="combData";

    TString option=argv[argc-1];
    option.ToLower();

    bool m_plot=option.Contains("plot");
    bool m_fixmu=option.Contains("fixmu");
    bool m_binned=option.Contains("binned");
    bool m_noprofile=option.Contains("noprofile");
    bool m_newmc=option.Contains("newmc");
    bool m_ghost=option.Contains("ghost");
    bool m_scale=option.Contains("scale");

    if(m_binned) cout<<"REGTEST: using binned data."<<endl;

    TFile fOutputFile("outcome.root","recreate") ;
    TTree fOutputTree("toy","toy") ;

    double nllfixsb, nllhatsb, nllfixbo, nllhatbo;
    double statusfixsb, statushatsb, statusfixbo, statushatbo;
    double muhatsb, muhatbo;
    double nevtsb, nevtbo, nevtsbbox, nevtbobox;
    vector<double> valuenpfixsb,valuenphatsb,valuenpfixbo,valuenphatbo;
    vector<string> namenp;

    fOutputTree.Branch("nllfixsb", &nllfixsb , "nllfixsb/D") ;
    fOutputTree.Branch("nllhatsb", &nllhatsb , "nllhatsb/D") ;
    fOutputTree.Branch("muhatsb", &muhatsb , "muhatsb/D") ;
    fOutputTree.Branch("statusfixsb", &statusfixsb , "statusfixsb/D") ;
    fOutputTree.Branch("statushatsb", &statushatsb , "statushatsb/D") ;
    fOutputTree.Branch("nevtsb", &nevtsb , "nevtsb/D") ;
    fOutputTree.Branch("nevtsbbox", &nevtsbbox , "nevtsbbox/D") ;
    fOutputTree.Branch("valuenpfixsb",&valuenpfixsb);
    fOutputTree.Branch("valuenphatsb",&valuenphatsb);

    fOutputTree.Branch("nllfixbo", &nllfixbo , "nllfixbo/D") ;
    fOutputTree.Branch("nllhatbo", &nllhatbo , "nllhatbo/D") ;
    fOutputTree.Branch("muhatbo", &muhatbo , "muhatbo/D") ;
    fOutputTree.Branch("statusfixbo", &statusfixbo , "statusfixbo/D") ;
    fOutputTree.Branch("statushatbo", &statushatbo , "statushatbo/D") ;
    fOutputTree.Branch("nevtbo", &nevtbo , "nevtbo/D") ;
    fOutputTree.Branch("nevtbobox", &nevtbobox , "nevtbobox/D") ;
    fOutputTree.Branch("valuenpfixbo",&valuenpfixbo);
    fOutputTree.Branch("valuenphatbo",&valuenphatbo);

    fOutputTree.Branch("seed", &seed , "seed/I") ;
    fOutputTree.Branch("namenp",&namenp);


    TFile f(inputFile,"read");
    RooWorkspace *w = dynamic_cast<RooWorkspace*>(f.Get(wname));    
    ModelConfig* mc = dynamic_cast<ModelConfig*>(w->obj(mname));
    RooAbsData *obsData = w->data(dname);
    RooArgSet funcs = w->allPdfs();
    {
      std::unique_ptr<TIterator> iter(funcs.createIterator());
      for ( RooAbsPdf* v = (RooAbsPdf*)iter->Next(); v!=0; v = (RooAbsPdf*)iter->Next() ) {
	std::string name = v->GetName();
	if (v->IsA() == RooRealSumPdf::Class() && name.find("binned")!=std::string::npos) {
	  std::cout << "\tset binned likelihood for: " << v->GetName() << std::endl;
	  v->setAttribute("BinnedLikelihood", true);
	}
      }
    }
    
    RooRealVar* firstPOI=dynamic_cast<RooRealVar*>(mc->GetParametersOfInterest()->first());
    RooArgSet nuisAndPOIAndGlob;
    nuisAndPOIAndGlob.add(*mc->GetNuisanceParameters());
    nuisAndPOIAndGlob.add(*mc->GetParametersOfInterest());
    nuisAndPOIAndGlob.add(*mc->GetGlobalObservables());
    
    if(option.Contains("qmutilde")) firstPOI->setRange(0,100);	// calculate qmutilde
    
    w->saveSnapshot("Origin",nuisAndPOIAndGlob);
    cout<<"Snapshot \"Origin\" saved."<<endl;
    w->loadSnapshot("conditionalNuis_0");
    firstPOI->setVal(0);
    firstPOI->setConstant(true);
    profileToData(mc, obsData);
    firstPOI->setConstant(false);

    w->saveSnapshot("Profile0",nuisAndPOIAndGlob);
    cout<<"Snapshot \"Profile0\" saved."<<endl;
    w->loadSnapshot("conditionalNuis_1");
    firstPOI->setVal(mu);
    firstPOI->setConstant(true);
    profileToData(mc, obsData);
    firstPOI->setConstant(false);
    w->saveSnapshot("Profilemu",nuisAndPOIAndGlob);
    cout<<"Snapshot \"Profilemu\" saved."<<endl;

    for(int itoy=0;itoy<ntoy;itoy++){

      RooRandom::randomGenerator() -> SetSeed(seed) ; // This step is necessary
      
      w->loadSnapshot("Profilemu");
      firstPOI->setVal(mu);
      unique_ptr<RooAbsData> toyData(generateToyData(mc, m_binned, m_ghost));
      nevtsb=toyData->sumEntries();
      obsData->Print(); toyData->Print();
      //cout<<nevtsb<<" "<<nevtsbbox<<endl;getchar();
      map<string, double> resultssb=calcTestStat(w, mc, toyData.get(), mu, &namenp, &valuenpfixsb, &valuenphatsb, option);
      nllfixsb=resultssb["nllfix"];
      nllhatsb=resultssb["nllhat"];
      muhatsb=resultssb["muhat"];
      statusfixsb=resultssb["statusfix"];
      statushatsb=resultssb["statushat"];

      namenp.clear();

      w->loadSnapshot("Profile0");
      firstPOI->setVal(0);
      toyData.reset(generateToyData(mc, m_binned, m_ghost));
      nevtbo=toyData->sumEntries();

      map<string, double> resultsbo=calcTestStat(w, mc, toyData.get(), mu, &namenp, &valuenpfixbo, &valuenphatbo, option);
      nllfixbo=resultsbo["nllfix"];
      nllhatbo=resultsbo["nllhat"];
      muhatbo=resultsbo["muhat"];
      statusfixbo=resultsbo["statusfix"];
      statushatbo=resultsbo["statushat"];

      fOutputTree.Fill() ;
      seed++;

      valuenpfixsb.clear();
      valuenphatsb.clear();
      valuenpfixbo.clear();
      valuenphatbo.clear();
      namenp.clear();

      fOutputTree.AutoSave("SaveSelf");
    }

    f.Close();
    fOutputFile.cd();

    fOutputTree.Write() ;
    fOutputFile.Close();
    return 0 ;
  }
  // *******************************************************************************
}
