#include "toyHighMassgg.hh"
#include "toyNtup.h"

void matchGlobalObs(ModelConfig* mcDebit, ModelConfig* mcCredit){
  if(mcDebit==mcCredit) return;	// They are identical. No need to synchronize
  RooArgSet *globDebit=const_cast<RooArgSet*>(mcDebit->GetGlobalObservables());
  RooArgSet *globCredit=const_cast<RooArgSet*>(mcCredit->GetGlobalObservables());

  unique_ptr<TIterator> iter(globDebit->createIterator());
  RooRealVar *parg=NULL;
  while((parg=dynamic_cast<RooRealVar*>(iter->Next()))){
    TString globName=parg->GetName();
    RooRealVar* globVar=dynamic_cast<RooRealVar*>(globCredit->find(globName));
    if(globVar) globVar->setVal(parg->getVal());
  }
}

double calcPvalue(double nllfix, double nllhat){
  double DNLL=2*(nllfix-nllhat);
  double pvalue=1-ROOT::Math::normal_cdf(sqrt(DNLL),1,0);
  if(!isfinite(pvalue)) pvalue=0.5;
  return pvalue;
}

int main( int argc , char **argv)
{
  //============================ Global booking and setting ==========================
  map<string,bool> Opt;
  Opt["TOSS"]=false;
  Opt["SUMMARIZE"]=false;

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
  ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit2");
  ROOT::Math::MinimizerOptions::SetDefaultStrategy(0);
  ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(-1);
  gErrorIgnoreLevel = kError+1;
  RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
    
  // *******************************************************************************
  if(Opt["TOSS"]){
    if(argc<7){
      cout<<"Usage: "<<argv[0]<<" "<<argv[1]<<" <seed> <input MT file> <input FB file> <ntoy> <option>"<<endl;
      return 0;
    }
    int seed = atoi(argv[2]);
    TString inputMTFile=argv[3];
    TString inputFBFile=argv[4];
    int ntoy=atoi(argv[5]);
    TString option=argv[6];

    TString wname="combWS";
    TString mname="ModelConfig";
    TString dname="combData";
    TString secPOIName="";
    
    if(option.Contains("scalar")) secPOIName="wX";
    if(option.Contains("graviton")) secPOIName="GkM";
    
    double nllfix, nllhat;
    double statusfix, statushat;
    double muhat, nevt, GkM;

    vector<double> valuenpfix,valuenphat;
    vector<string> namenp;

    TFile fOutputFBFile("outcomeFB.root","recreate") ;
    TTree fOutputFBTree("toy","toy") ;

    fOutputFBTree.Branch("nllfix", &nllfix , "nllfix/D") ;
    fOutputFBTree.Branch("nllhat", &nllhat , "nllhat/D") ;
    fOutputFBTree.Branch("muhat", &muhat , "muhat/D") ;
    fOutputFBTree.Branch("GkM", &GkM , "GkM/D") ;
    fOutputFBTree.Branch("statusfix", &statusfix , "statusfix/D") ;
    fOutputFBTree.Branch("statushat", &statushat , "statushat/D") ;
    fOutputFBTree.Branch("valuenpfix",&valuenpfix);
    fOutputFBTree.Branch("valuenphat",&valuenphat);

    fOutputFBTree.Branch("nevt", &nevt , "nevt/D") ;
    fOutputFBTree.Branch("seed", &seed , "seed/I") ;
    fOutputFBTree.Branch("namenp",&namenp);

    TFile fOutputMTFile("outcomeMT.root","recreate") ;
    TTree fOutputMTTree("toy","toy") ;

    fOutputMTTree.Branch("nllfix", &nllfix , "nllfix/D") ;
    fOutputMTTree.Branch("nllhat", &nllhat , "nllhat/D") ;
    fOutputMTTree.Branch("muhat", &muhat , "muhat/D") ;
    fOutputMTTree.Branch("GkM", &GkM , "GkM/D") ;
    fOutputMTTree.Branch("statusfix", &statusfix , "statusfix/D") ;
    fOutputMTTree.Branch("statushat", &statushat , "statushat/D") ;
    fOutputMTTree.Branch("valuenpfix",&valuenpfix);
    fOutputMTTree.Branch("valuenphat",&valuenphat);

    fOutputMTTree.Branch("nevt", &nevt , "nevt/D") ;
    fOutputMTTree.Branch("seed", &seed , "seed/I") ;
    fOutputMTTree.Branch("namenp",&namenp);

    TFile fFB(inputFBFile,"read");
    TFile fMT(inputMTFile,"read");
    RooWorkspace *wFB = dynamic_cast<RooWorkspace*>(fFB.Get(wname));    
    ModelConfig* mcFB = dynamic_cast<ModelConfig*>(wFB->obj(mname));
    RooSimultaneous *pdfFB = dynamic_cast<RooSimultaneous*>(mcFB->GetPdf());
    
    RooWorkspace *wMT = dynamic_cast<RooWorkspace*>(fMT.Get(wname));    
    ModelConfig* mcMT = dynamic_cast<ModelConfig*>(wMT->obj(mname));
    RooSimultaneous *pdfMT = dynamic_cast<RooSimultaneous*>(mcMT->GetPdf());

    ModelConfig *mcToy=NULL;
    if(option.Contains("MT")) mcToy=mcMT;
    else if(option.Contains("FB")) mcToy=mcFB;
    else{
      cerr<<"Unknown pdf type: choose between mt and fb"<<endl;
      return -1;
    }

    cout<<wFB->loadSnapshot("conditionalPOI_toy")<<endl;
    cout<<wFB->loadSnapshot("conditionalNuis_toy")<<endl;
    cout<<wFB->loadSnapshot("conditionalGlobs_toy")<<endl;
    pairNuisGlob(mcFB);
    // mcFB->GetGlobalObservables()->Print("v");
    // mcFB->GetNuisanceParameters()->Print("v");
    // getchar();
    
    cout<<wMT->loadSnapshot("conditionalPOI_toy")<<endl;
    cout<<wMT->loadSnapshot("conditionalNuis_toy")<<endl;
    cout<<wMT->loadSnapshot("conditionalGlobs_toy")<<endl;
    pairNuisGlob(mcMT);

    if(option.Contains("fixgamma")){
      RooArgSet *gammaSet=dynamic_cast<RooArgSet*>(mcMT->GetNuisanceParameters()->selectByName("gamma_*"));
      statistics::constSet(gammaSet, true);
      // gammaSet->Print("v");

      ROOT::Math::MinimizerOptions::SetDefaultStrategy(1); // we can afford strategy 1 now
    }
    // mcMT->GetGlobalObservables()->Print("v");
    // mcMT->GetNuisanceParameters()->Print("v");
    // getchar();

    RooArgSet everythingFB, everythingMT;

    everythingFB.add(*mcFB->GetNuisanceParameters());
    everythingFB.add(*mcFB->GetGlobalObservables());
    everythingFB.add(*mcFB->GetParametersOfInterest());
    wFB->saveSnapshot("toySnapshot", everythingFB);

    everythingMT.add(*mcMT->GetNuisanceParameters());
    everythingMT.add(*mcMT->GetGlobalObservables());
    everythingMT.add(*mcMT->GetParametersOfInterest());
    wMT->saveSnapshot("toySnapshot", everythingMT);

    for(int itoy=0;itoy<ntoy;itoy++){
      wFB->loadSnapshot("toySnapshot");
      wMT->loadSnapshot("toySnapshot");

      // everythingFB.Print("v"); getchar();
      RooRandom::randomGenerator() -> SetSeed(seed) ; // This step is necessary
      
      unique_ptr<RooDataSet> toyDataFB(generateToyData(mcFB, option));
      unique_ptr<RooDataSet> toyDataMT(generateToyData(mcMT, option));

      if(option.Contains("FB")){
	matchGlobalObs(mcToy, mcMT);
	toyDataMT.reset(copyData(toyDataFB.get(), toyDataMT.get(), mcToy, mcMT, option));
      }
      else if(option.Contains("MT")){
	matchGlobalObs(mcToy, mcFB);
	toyDataFB.reset(copyData(toyDataMT.get(), toyDataFB.get(), mcToy, mcFB, option));
      }
       
      toyDataFB->Print("v");
      toyDataMT->Print("v");
 
      nevt=toyDataFB->sumEntries();
      if(option.Contains("graviton")&&nevt!=toyDataMT->sumEntries()){
	cerr<<"Number of toy data events is wrong...exiting"<<endl;
	return -1;
      }
      
      map<string, double> resultsFB=calcTestStat(mcFB, toyDataFB.get(), 0, &namenp, &valuenpfix, &valuenphat, option);
      nllfix=resultsFB["nllfix"];
      nllhat=resultsFB["nllhat"];
      muhat=resultsFB["muhat"];
      statusfix=resultsFB["statusfix"];
      statushat=resultsFB["statushat"];
      GkM=wFB->var(secPOIName)->getVal();
      fOutputFBTree.Fill() ;

      valuenpfix.clear();
      valuenphat.clear();
      namenp.clear();

      map<string, double> resultsMT=calcTestStat(mcMT, toyDataMT.get(), 0, &namenp, &valuenpfix, &valuenphat, option);
      nllfix=resultsMT["nllfix"];
      nllhat=resultsMT["nllhat"];
      muhat=resultsMT["muhat"];
      statusfix=resultsMT["statusfix"];
      statushat=resultsMT["statushat"];
      GkM=wMT->var(secPOIName)->getVal();
      fOutputMTTree.Fill() ;

      valuenpfix.clear();
      valuenphat.clear();
      namenp.clear();

      seed++;
    }

    fFB.Close();
    fMT.Close();
    fOutputFBFile.cd();

    fOutputFBTree.Write();
    fOutputFBFile.Close();

    fOutputMTFile.cd();

    fOutputMTTree.Write();
    fOutputMTFile.Close();
    
    return 0 ;
  }
  // *******************************************************************************
  if(Opt["SUMMARIZE"]){
    if(argc<6){
      cout<<"Usage: "<<argv[0]<<" "<<argv[1]<<" <jobname> <input MT file> <input FB file> <option>"<<endl;
      return 0;
    }
    SetAtlasStyle();
    
    TString jobname=argv[2];
    TString inputMTFile=argv[3];
    TString inputFBFile=argv[4];
    TString option=argv[5];

    TString wname="combWS";
    TString mname="ModelConfig";
    TString dname="combDatabinned";

    TFile fFB(inputFBFile,"read");
    TFile fMT(inputMTFile,"read");
    RooWorkspace *wFB = dynamic_cast<RooWorkspace*>(fFB.Get(wname));    
    ModelConfig* mcFB = dynamic_cast<ModelConfig*>(wFB->obj(mname));
    RooSimultaneous *pdfFB = dynamic_cast<RooSimultaneous*>(mcFB->GetPdf());
    RooDataSet *dataFB = dynamic_cast<RooDataSet*>(wFB->data(dname));
      
    RooWorkspace *wMT = dynamic_cast<RooWorkspace*>(fMT.Get(wname));    
    ModelConfig* mcMT = dynamic_cast<ModelConfig*>(wMT->obj(mname));
    RooSimultaneous *pdfMT = dynamic_cast<RooSimultaneous*>(mcMT->GetPdf());
    RooDataSet *dataMT = dynamic_cast<RooDataSet*>(wMT->data(dname));
    
    TString inputDir="toy/"+jobname;

    TChain *cMT=new TChain("toy");
    TChain *cFB=new TChain("toy");
    cMT->Add(inputDir+"/"+jobname+"_*_MT.root");
    cFB->Add(inputDir+"/"+jobname+"_*_FB.root");
    toy *pMT=new toy(cMT);
    toy *pFB=new toy(cFB);

    int nevt=pMT->fChain->GetEntries();

    if(nevt!=pFB->fChain->GetEntries()){
      cout<<pMT->fChain->GetEntries()<<" "<<pFB->fChain->GetEntries()<<endl;
      cerr<<"Number of events do not match. Press any key to continue..."<<endl;
      getchar();
    }

    vector<double> zMT, zFB, zDiff;
    vector<double> xsMT, xsFB, xsDiff;
    vector<double> GkMMT, GkMFB, GkMDiff;
    map<TString, vector<double> > npMThat, npMTfix, npFBhat, npFBfix;
    
    pFB->fChain->BuildIndex("seed"); // We will use seed to match two trees

    for(int ievt=0;ievt<nevt;ievt++){
      pMT->fChain->GetEntry(ievt);
      pFB->fChain->GetEntryWithIndex(pMT->seed);

      if(pMT->seed!=pFB->seed){
	cerr<<"Seed does not match! MT="<<pMT->seed<<" FB="<<pFB->seed<<endl;
	return -1;
      }
      if(pMT->statusfix!=0||pMT->statushat!=0){
	cerr<<"\tWARNING: Toy "<<ievt
	    <<" with random seed "<<pMT->seed
	    <<" has convergence issue for MT. Fit status: fix="
	    <<pMT->statusfix<<", float="<<pMT->statushat
	    <<". Skipping this toy..."
	    <<endl;
	continue;
      }

      if(pFB->statusfix!=0||pFB->statushat!=0){
	cerr<<"\tWARNING: Toy "<<ievt
	    <<" with random seed "<<pFB->seed
	    <<" has convergence issue for FB. Fit status: fix="
	    <<pFB->statusfix<<", float="<<pFB->statushat
	    <<". Skipping this toy..."
	    <<endl;
	continue;
      }
      double ZMT=RooStats::PValueToSignificance(calcPvalue(pMT->nllfix, pMT->nllhat));
      double ZFB=RooStats::PValueToSignificance(calcPvalue(pFB->nllfix, pFB->nllhat));
      zMT.push_back(ZMT);
      zFB.push_back(ZFB);
      zDiff.push_back(ZMT-ZFB);
      // cout<<pMT->nllfix<<" "<<pMT->nllhat<<endl;
      // cout<<pFB->nllfix<<" "<<pFB->nllhat<<endl;
      // cout<<ZMT<<" "<<ZFB<<endl;
      xsMT.push_back(pMT->muhat);
      xsFB.push_back(pFB->muhat);
      xsDiff.push_back(pMT->muhat-pFB->muhat);

      GkMMT.push_back(pMT->GkM);
      GkMFB.push_back(pFB->GkM);
      GkMDiff.push_back(pMT->GkM-pFB->GkM);

      int nNPMT=pMT->namenp->size();
      for(int inp=0;inp<nNPMT;inp++){
	TString NPName=pMT->namenp->at(inp);
	if(NPName.BeginsWith("gamma_")) continue;
	npMThat[NPName].push_back(pMT->valuenphat->at(inp));
	npMTfix[NPName].push_back(pMT->valuenpfix->at(inp));
      }
      
      int nNPFB=pFB->namenp->size();
      for(int inp=0;inp<nNPFB;inp++){
	TString NPName=pFB->namenp->at(inp);
	if(NPName.BeginsWith("gamma_")) continue;
	npFBhat[NPName].push_back(pFB->valuenphat->at(inp));
	npFBfix[NPName].push_back(pFB->valuenpfix->at(inp));
      }
    }

    // Calculating observed results
    map<string, double> obsMT=calcTestStat(mcMT, dataMT, 0, NULL, NULL, NULL, option);
    map<string, double> obsFB=calcTestStat(mcFB, dataFB, 0, NULL, NULL, NULL, option);
    double zMTobs=RooStats::PValueToSignificance(calcPvalue(obsMT["nllfix"], obsMT["nllhat"]));
    double zFBobs=RooStats::PValueToSignificance(calcPvalue(obsFB["nllfix"], obsFB["nllhat"]));
    double xsMTobs=obsMT["muhat"];
    double xsFBobs=obsFB["muhat"];
    double GkMMTobs, GkMFBobs;
    if(option.Contains("scalar")){
      GkMMTobs=wMT->var("wX")->getVal();
      GkMFBobs=wFB->var("wX")->getVal();
    }
    if(option.Contains("graviton")){
      GkMMTobs=wMT->var("GkM")->getVal();
      GkMFBobs=wFB->var("GkM")->getVal();
    }
    TString outputDir="fig/toy/"+jobname;
    system("mkdir -vp "+outputDir);

    map<string, double> resultsZMT=statistics::expFromToy(zMT);
    map<string, double> resultsZFB=statistics::expFromToy(zFB);
    map<string, double> resultsZDiff=statistics::expFromToy(zDiff);

    map<string, double> resultsXSMT=statistics::expFromToy(xsMT);
    map<string, double> resultsXSFB=statistics::expFromToy(xsFB);
    map<string, double> resultsXSDiff=statistics::expFromToy(xsDiff);

    map<string, double> resultsGKMMT=statistics::expFromToy(GkMMT);
    map<string, double> resultsGKMFB=statistics::expFromToy(GkMFB);
    map<string, double> resultsGKMDiff=statistics::expFromToy(GkMDiff);

    TH1D *hZMT=statistics::plotToy(zMT, "hZMT",50,0,10,"Z [#sigma]", kRed, 2);
    TH1D *hZFB=statistics::plotToy(zFB, "hZFB",50,0,10,"Z [#sigma]", kBlue, 2);
    TH1D *hZDiff=statistics::plotToy(zDiff, "hZDiff",50,-2,2,"Z_{MT}-Z_{FB} [#sigma]", kBlack, 2);

    TH1D *hXSMT=NULL;
    TH1D *hXSFB=NULL;
    TH1D *hXSDiff=NULL;

    TH1D *hGKMMT=NULL;
    TH1D *hGKMFB=NULL;
    TH1D *hGKMDiff=NULL;

    if(option.Contains("graviton")){
      hXSMT=statistics::plotToy(xsMT, "hXSMT",50,0,50,"#sigma#timesBR [fb]", kRed, 2);
      hXSFB=statistics::plotToy(xsFB, "hXSFB",50,0,50,"#sigma#timesBR [fb]", kBlue, 2);
      hXSDiff=statistics::plotToy(xsDiff, "hXSDiff",50,-20,20,"#sigma#timesBR_{MT}-#sigma#timesBR_{FB} [fb]", kBlack, 2);

      hGKMMT=statistics::plotToy(GkMMT, "hGKMMT",50,0,0.5,"#it{k}/#bar{M}_{Pl}", kRed, 2);
      hGKMFB=statistics::plotToy(GkMFB, "hGKMFB",50,0,0.5,"#it{k}/#bar{M}_{Pl}", kBlue, 2);
      hGKMDiff=statistics::plotToy(GkMDiff, "hGKMDiff",50,-0.3,0.3,"#it{k}/#bar{M}_{Pl}_{MT}-#it{k}/#bar{M}_{Pl}_{FB}", kBlack, 2);

    }
    if(option.Contains("scalar")){
      hXSMT=statistics::plotToy(xsMT, "hXSMT",50,0,20,"#sigma#timesBR [fb]", kRed, 2);
      hXSFB=statistics::plotToy(xsFB, "hXSFB",50,0,20,"#sigma#timesBR [fb]", kBlue, 2);
      hXSDiff=statistics::plotToy(xsDiff, "hXSDiff",50,-10,10,"#sigma#timesBR_{MT}-#sigma#timesBR_{FB} [fb]", kBlack, 2);

      hGKMMT=statistics::plotToy(GkMMT, "hGKMMT",100,0,100,"#Gamma_{X} [GeV]", kRed, 2);
      hGKMFB=statistics::plotToy(GkMFB, "hGKMFB",100,0,100,"#Gamma_{X} [GeV]", kBlue, 2);
      hGKMDiff=statistics::plotToy(GkMDiff, "hGKMDiff",50,-20,20,"#Gamma_{X}_{MT}-#Gamma_{X}_{FB}", kBlack, 2);
    }
    

    TCanvas *cZ=new TCanvas("cZ","cZ",800,600);
    hZMT->Draw("hist");
    hZFB->Draw("same,hist");
    hZMT->SetMaximum(std::max(hZMT->GetMaximum(), hZFB->GetMaximum())*1.2);
    
    TLine *line=new TLine(0,0,0,std::max(hZMT->GetMaximum(),hZFB->GetMaximum()));
    line->SetLineWidth(3);
    line->SetLineStyle(5);

    TLine *medianFB=new TLine(resultsZFB["median"],0,resultsZFB["median"],hZFB->GetMaximum());
    medianFB->SetLineWidth(3);
    medianFB->SetLineStyle(2);
    medianFB->SetLineColor(kBlue);

    TLine *medianMT=new TLine(resultsZMT["median"],0,resultsZMT["median"],hZMT->GetMaximum());
    medianMT->SetLineWidth(3);
    medianMT->SetLineStyle(2);
    medianMT->SetLineColor(kRed);

    TLine *median=new TLine(resultsZFB["median"],0,resultsZFB["median"],hZFB->GetMaximum());
    median->SetLineWidth(3);
    median->SetLineStyle(2);

    if(option.Contains("MT")){
      line->SetX1(zMTobs);
      line->SetX2(zMTobs);
    }
    
    else if(option.Contains("FB")){
      line->SetX1(zFBobs);
      line->SetX2(zFBobs);
    }  
    
    line->DrawClone("same");
    medianFB->DrawClone("same");
    medianMT->DrawClone("same");
    
    double x1,y1,x2,y2;
    GetX1Y1X2Y2(cZ, x1, y1, x2, y2);
    TLegend *leg=FastLegend(x2-0.35,y2-0.3,x2-0.03,y2-0.05,0.05);

    leg->AddEntry(hZMT,"MC template","l");
    leg->AddEntry(hZFB,"Floating bkg.","l");
    leg->AddEntry(line,"Injected value","l");
    leg->AddEntry(median,"Medians","l");
    leg->DrawClone("same");
    
    PrintCanvas(cZ, outputDir+"/cZ");
    
    TCanvas *cZDiff=new TCanvas("cZDiff","cZDiff",800,600);
    hZDiff->Draw("hist");
    TLine *medianDiff=new TLine(resultsZDiff["median"],0,resultsZDiff["median"],hZDiff->GetMaximum());
    medianDiff->SetLineWidth(3);
    medianDiff->SetLineStyle(2);
    TLine *zero=new TLine(0,0,0,hZDiff->GetMaximum());
    zero->SetLineWidth(3);
    line->SetX1(zMTobs-zFBobs);
    line->SetX2(zMTobs-zFBobs);
    line->SetY2(hZDiff->GetMaximum());
    
    TLegend *legDiff=FastLegend(x1+0.03,y2-0.3,x1+0.35,y2-0.05,0.05);
    legDiff->AddEntry(medianDiff,"Median","l");
    legDiff->AddEntry(line,"Observed","l");

    medianDiff->DrawClone("same");
    zero->DrawClone("same");
    line->DrawClone("same");
    
    legDiff->DrawClone("same");
    
    PrintCanvas(cZDiff, outputDir+"/cZDiff");

    TCanvas *cXS=new TCanvas("cXS","cXS",800,600);
    hXSMT->Draw("hist");
    hXSFB->Draw("same,hist");
    hXSMT->SetMaximum(std::max(hXSMT->GetMaximum(), hXSFB->GetMaximum())*1.2);
    if(option.Contains("MT")){
      line->SetX1(xsMTobs);
      line->SetX2(xsMTobs);
      line->SetY2(std::max(hXSMT->GetMaximum(), hXSFB->GetMaximum()));
    }
    else if(option.Contains("FB")){
      line->SetX1(xsFBobs);
      line->SetX2(xsFBobs);
      line->SetY2(std::max(hXSMT->GetMaximum(), hXSFB->GetMaximum()));
    }

    medianMT->SetX1(resultsXSMT["median"]);
    medianMT->SetX2(resultsXSMT["median"]);
    medianMT->SetY2(hXSMT->GetMaximum());

    medianFB->SetX1(resultsXSFB["median"]);
    medianFB->SetX2(resultsXSFB["median"]);
    medianFB->SetY2(hXSFB->GetMaximum());

    medianFB->DrawClone("same");
    medianMT->DrawClone("same");
    line->DrawClone("same");
    leg->DrawClone("same");

    PrintCanvas(cXS, outputDir+"/cXS");

    TCanvas *cXSDiff=new TCanvas("cXSDiff","cXSDiff",800,600);
    hXSDiff->Draw("hist");

    medianDiff->SetX1(resultsXSDiff["median"]);
    medianDiff->SetX2(resultsXSDiff["median"]);
    medianDiff->SetY2(hXSDiff->GetMaximum());
    line->SetX1(xsMTobs-xsFBobs);
    line->SetX2(xsMTobs-xsFBobs);
    line->SetY2(hXSDiff->GetMaximum());
    
    zero->SetY2(hXSDiff->GetMaximum());
    medianDiff->DrawClone("same");
    zero->DrawClone("same");
    line->DrawClone("same");
    
    legDiff->DrawClone("same");
    PrintCanvas(cXSDiff, outputDir+"/cXSDiff");

    TCanvas *cGKM=new TCanvas("cGKM","cGKM",800,600);
    hGKMMT->Draw("hist");
    hGKMFB->Draw("same,hist");

    if(option.Contains("MT")){
      line->SetX1(GkMMTobs);
      line->SetX2(GkMMTobs);
      line->SetY2(std::max(hGKMMT->GetMaximum(), hGKMFB->GetMaximum()));
    }
    else if(option.Contains("FB")){
      line->SetX1(GkMFBobs);
      line->SetX2(GkMFBobs);
      line->SetY2(std::max(hGKMMT->GetMaximum(), hGKMFB->GetMaximum()));
    }

    medianMT->SetX1(resultsGKMMT["median"]);
    medianMT->SetX2(resultsGKMMT["median"]);
    medianMT->SetY2(hGKMMT->GetMaximum());

    medianFB->SetX1(resultsGKMFB["median"]);
    medianFB->SetX2(resultsGKMFB["median"]);
    medianFB->SetY2(hGKMFB->GetMaximum());

    medianFB->DrawClone("same");
    medianMT->DrawClone("same");
    line->DrawClone("same");
    leg->DrawClone("same");

    PrintCanvas(cGKM, outputDir+"/cGKM");

    TCanvas *cGKMDiff=new TCanvas("cGKMDiff","cGKMDiff",800,600);
    hGKMDiff->Draw("hist");

    medianDiff->SetX1(resultsGKMDiff["median"]);
    medianDiff->SetX2(resultsGKMDiff["median"]);
    medianDiff->SetY2(hGKMDiff->GetMaximum());
    line->SetX1(GkMMTobs-GkMFBobs);
    line->SetX2(GkMMTobs-GkMFBobs);
    line->SetY2(hGKMDiff->GetMaximum());
    
    zero->SetY2(hGKMDiff->GetMaximum());
    medianDiff->DrawClone("same");
    zero->DrawClone("same");
    line->DrawClone("same");
    
    legDiff->DrawClone("same");
    PrintCanvas(cGKMDiff, outputDir+"/cGKMDiff");
    
    cout<<"~~~~~~~~~~~~~~~~ Summary ~~~~~~~~~~~~~~"<<endl;
    cout<<Form("MC template method: Z=%.2f+%.2f-%.2f, xs=%.2f+%.2f-%.2f", resultsZMT["median"], resultsZMT["p1s"]-resultsZMT["median"], resultsZMT["median"]-resultsZMT["n1s"], resultsXSMT["median"], resultsXSMT["p1s"]-resultsXSMT["median"], resultsXSMT["median"]-resultsXSMT["n1s"])<<endl;
    cout<<Form("Floating bkg. method: Z=%.2f+%.2f-%.2f, xs=%.2f+%.2f-%.2f", resultsZFB["median"], resultsZFB["p1s"]-resultsZFB["median"], resultsZFB["median"]-resultsZFB["n1s"], resultsXSFB["median"], resultsXSFB["p1s"]-resultsXSFB["median"], resultsXSFB["median"]-resultsXSFB["n1s"])<<endl;
    cout<<Form("Difference: Delta_Z=%.2f+%.2f-%.2f (tension with obs.=%.2f), xs=%.2f+%.2f-%.2f (tension with obs.=%.2f)", resultsZDiff["median"], resultsZDiff["p1s"]-resultsZDiff["median"], resultsZDiff["median"]-resultsZDiff["n1s"], statistics::pvalueFromToy(zDiff, zMTobs-zFBobs), resultsXSDiff["median"], resultsXSDiff["p1s"]-resultsXSDiff["median"], resultsXSDiff["median"]-resultsXSDiff["n1s"], statistics::pvalueFromToy(xsDiff, xsMTobs-xsFBobs))<<endl;

    ofstream fout(outputDir+"/summary.txt");
    fout<<"~~~~~~~~~~~~~~~~ Summary ~~~~~~~~~~~~~~"<<endl;
    fout<<Form("MC template method: Z=%.2f+%.2f-%.2f, xs=%.2f+%.2f-%.2f", resultsZMT["median"], resultsZMT["p1s"]-resultsZMT["median"], resultsZMT["median"]-resultsZMT["n1s"], resultsXSMT["median"], resultsXSMT["p1s"]-resultsXSMT["median"], resultsXSMT["median"]-resultsXSMT["n1s"])<<endl;
    fout<<Form("Floating bkg. method: Z=%.2f+%.2f-%.2f, xs=%.2f+%.2f-%.2f", resultsZFB["median"], resultsZFB["p1s"]-resultsZFB["median"], resultsZFB["median"]-resultsZFB["n1s"], resultsXSFB["median"], resultsXSFB["p1s"]-resultsXSFB["median"], resultsXSFB["median"]-resultsXSFB["n1s"])<<endl;
    fout<<Form("Difference: Delta_Z=%.2f+%.2f-%.2f (tension with obs.=%.2f), xs=%.2f+%.2f-%.2f (tension with obs.=%.2f)", resultsZDiff["median"], resultsZDiff["p1s"]-resultsZDiff["median"], resultsZDiff["median"]-resultsZDiff["n1s"], statistics::pvalueFromToy(zDiff, zMTobs-zFBobs), resultsXSDiff["median"], resultsXSDiff["p1s"]-resultsXSDiff["median"], resultsXSDiff["median"]-resultsXSDiff["n1s"], statistics::pvalueFromToy(xsDiff, xsMTobs-xsFBobs))<<endl;
    fout.close();
  }
}
