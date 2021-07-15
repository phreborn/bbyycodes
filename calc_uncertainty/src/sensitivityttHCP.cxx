#include "CommonHead.h"
#include "CommonFunc.h"
#include "truth.h"

#include "toy.hh"

using namespace std;
using namespace RooFit;
using namespace RooStats;

void fillArray(double *x, truth *p){
  x[0]=p->delta_phi_top;
  x[1]=p->delta_eta_top;
  x[2]=p->m_H_pt->at(0);
  x[3]=p->m_H_eta->at(0);
  x[4]=p->m_ttH;
  x[5]=p->m_tt;
}

int main(int argc, char**argv){
  //***************************= Global booking and setting ************************==
  //   gErrorIgnoreLevel = kError+1;
  map<string,bool> Opt;
  Opt["NTUPLE"]=false;
  Opt["HIST"]=false;
  Opt["TOY"]=false;

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
  CommonFunc::SetAtlasStyle();
  //************************************************************************************==
  if(Opt["NTUPLE"]){
    TString inputFileList=argv[2];
    TString outputFileName=argv[3];
    
    TChain *c=CommonFunc::MakeChain("output",inputFileList,inputFileList+".bdf",inputFileList.Contains(".root"));

    TFile *fout=TFile::Open(outputFileName,"recreate");
    TTree *tout=new TTree("output", "For MVA training");
    
    unique_ptr<truth> p(new truth(c));

    float pT_H, eta_H, pT_t, pT_tx, eta_t, eta_tx;
    float delta_eta_top, delta_phi_top;
    float m_ttH, m_tH, m_txH, m_tt;
    float weight;
    
    tout->Branch("pT_H", &pT_H, "pT_H/F");
    tout->Branch("eta_H", &eta_H, "eta_H/F");
    tout->Branch("pT_t", &pT_t, "pT_t/F");
    tout->Branch("eta_t", &eta_t, "eta_t/F");
    tout->Branch("pT_tx", &pT_tx, "pT_tx/F");
    tout->Branch("eta_tx", &eta_tx, "eta_tx/F");
    tout->Branch("delta_eta_top", &delta_eta_top, "delta_eta_top/F");
    tout->Branch("delta_phi_top", &delta_phi_top, "delta_phi_top/F");
    tout->Branch("m_ttH", &m_ttH, "m_ttH/F");
    tout->Branch("m_tH", &m_tH, "m_tH/F");
    tout->Branch("m_txH", &m_txH, "m_txH/F");
    tout->Branch("m_tt", &m_tt, "m_tt/F");
    tout->Branch("weight", &weight, "weight/F");
    
    long int nevt=p->fChain->GetEntries();

    for(long int ievt=0;ievt<nevt;ievt++){
      cout<<ievt/double(nevt)*100<<"\r"<<flush;
      
      p->GetEntry(ievt);

      if(p->m_t_pt->size()!=1||p->m_tx_pt->size()!=1){
	// cerr<<"Not exactly two top in event: "
	//     <<p->m_t_pt->size()<<" "<<p->m_tx_pt->size()<<endl;
	continue;
      }
      else{
	// cout<<"Everything is okay"<<endl;
      }
      if(p->m_y_pt->size()<2){
	cerr<<"Less than two photons in event"<<endl;
	continue;
      }

      TLorentzVector H, t, tx;
      t.SetPtEtaPhiM(p->m_t_pt->at(0), p->m_t_eta->at(0), p->m_t_phi->at(0), p->m_t_m->at(0));
      tx.SetPtEtaPhiM(p->m_tx_pt->at(0), p->m_tx_eta->at(0), p->m_tx_phi->at(0), p->m_tx_m->at(0));

      TLorentzVector gam1, gam2;
      gam1.SetPtEtaPhiE(p->m_y_pt->at(0), p->m_y_eta->at(0), p->m_y_phi->at(0), p->m_y_E->at(0));
      gam2.SetPtEtaPhiE(p->m_y_pt->at(1), p->m_y_eta->at(1), p->m_y_phi->at(1), p->m_y_E->at(1));
      
      if(p->m_H_pt->size()!=1){
	// cerr<<"Not exactly one Higgs in event: "<<p->m_H_pt->size()<<endl;
	// continue;
	pT_H=(gam1+gam2).Pt();
	eta_H=(gam1+gam2).Eta();
	H=(gam1+gam2);
      }
      else{
	pT_H=p->m_H_pt->at(0);
	eta_H=p->m_H_eta->at(0);
	H.SetPtEtaPhiM(p->m_H_pt->at(0), p->m_H_eta->at(0), p->m_H_phi->at(0), p->m_H_m->at(0));
      }

      pT_t=p->m_t_pt->at(0);
      eta_t=p->m_t_eta->at(0);

      pT_tx=p->m_tx_pt->at(0);
      eta_tx=p->m_tx_eta->at(0);

      delta_eta_top=fabs(p->m_t_eta->at(0)-p->m_tx_eta->at(0));
      delta_phi_top=CommonFunc::DiffPhi(p->m_t_phi->at(0), p->m_tx_phi->at(0));

      m_ttH=(H+t+tx).M();
      m_tH=(H+t).M();
      m_txH=(H+tx).M();
      m_tt=(t+tx).M();

      weight=p->weight;
      tout->Fill();
      if (ievt%100000 == 1) tout->AutoSave("SaveSelf");
    }

    fout->cd();
    tout->Write();
    fout->Close();
  }
  //************************************************************************************==
  if(Opt["HIST"]){
    TString inputFileName1=argv[2];
    TString outputFileName=argv[3];
    
    double luminosity=150e3;
    double xsBR=2.27e-3*5.065E-01;
    // Use THn
    // Use distributions: delta_phi_t, delta_eta_t, Higgs pT, Higgs eta, m_ttH, m_tt
    const int ndim=6;
    int bins[ndim]={3,5,5,3,3,3};
    double xmin[ndim]={0,0,0,0,500,300}, xmax[ndim]={3.2,5,500,5,2000,1500};
    
    THnD *hn1=new THnD("hn1", "hn1", ndim, bins, xmin, xmax);

    cout<<hn1->GetNbins()<<endl;;
    
    TChain *c1=CommonFunc::MakeChain("output",inputFileName1,inputFileName1+".bdf",inputFileName1.Contains(".root"));
    truth *p1=new truth(c1);

    int nevt1=p1->fChain->GetEntries();

    double sumw1=0, sumw2=0;
    
    for(int ievt1=0; ievt1<nevt1; ievt1++){
      cout<<ievt1/double(nevt1)*100<<"\r"<<flush;
      p1->fChain->GetEntry(ievt1);
      double x[ndim];
      fillArray(x, p1);
      hn1->Fill(x, p1->weight);
      sumw1+=p1->weight;
    }

    hn1->Scale(luminosity*xsBR/sumw1);

    TFile *fout=TFile::Open(outputFileName,"recreate");
    hn1->Write();
    fout->Close();
  }
  //************************************************************************************==
  if(Opt["TOY"]){
    ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit2");
    ROOT::Math::MinimizerOptions::SetDefaultStrategy(0);
    ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(-3);
    RooMsgService::instance().getStream(1).removeTopic(RooFit::NumIntegration) ;
    RooMsgService::instance().getStream(1).removeTopic(RooFit::Fitting) ;
    RooMsgService::instance().getStream(1).removeTopic(RooFit::Minimization) ;
    RooMsgService::instance().getStream(1).removeTopic(RooFit::InputArguments) ;
    RooMsgService::instance().getStream(1).removeTopic(RooFit::Eval) ;
    RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);
    
    TString inputWSFileName=argv[2];
    const int mode=atoi(argv[3]);
    int ntoy=atoi(argv[4]);
    TString outputFileName=argv[5];
      
    TFile *f=TFile::Open(inputWSFileName);
    
    RooWorkspace *w=(RooWorkspace*)f->Get("combWS");
    ModelConfig *mc=(ModelConfig*)w->obj("ModelConfig");

    if(argc>6) w->var("bkgSF")->setVal(atof(argv[6]));

    double epsilon_value1, epsilon_value2;
    if(mode==0) {epsilon_value1=0.1;epsilon_value2=0.5;} // SM vs. CP mixing
    if(mode==1) {epsilon_value1=0.1;epsilon_value2=0.9;} // SM vs. CP odd
    w->var("epsilon")->setConstant(1);    
    RooArgSet nuisAndPOIAndGlob;
    nuisAndPOIAndGlob.add(*mc->GetNuisanceParameters());
    nuisAndPOIAndGlob.add(*mc->GetParametersOfInterest());
    nuisAndPOIAndGlob.add(*mc->GetGlobalObservables());
    w->saveSnapshot("Origin",nuisAndPOIAndGlob);

    TFile *fout=TFile::Open(outputFileName,"recreate");
    TTree *t=new TTree("toy","toy");
    double ts1, ts0;
    t->Branch("ts1",&ts1,"ts1/D");
    t->Branch("ts0",&ts0,"ts0/D");
    vector<double> ts1Arr, ts0Arr;
    
    for(int itoy=0;itoy<ntoy;itoy++){
      RooRandom::randomGenerator() -> SetSeed(itoy) ; // This step is necessary
      
      w->loadSnapshot("Origin");
      w->var("epsilon")->setVal(epsilon_value1);
      RooAbsData *toyData1=generateToyData(mc, true, false);
      w->var("epsilon")->setVal(epsilon_value1);
      double nll1_1=profileToData(mc, toyData1);
      w->var("epsilon")->setVal(epsilon_value2);
      double nll1_0=profileToData(mc, toyData1);
      ts1=2*(nll1_1-nll1_0);
      ts1Arr.push_back(ts1);
      
      w->var("epsilon")->setVal(epsilon_value2);
      RooAbsData *toyData0=generateToyData(mc, true, false);
      w->var("epsilon")->setVal(epsilon_value1);
      double nll0_1=profileToData(mc, toyData0);
      w->var("epsilon")->setVal(epsilon_value2);
      double nll0_0=profileToData(mc, toyData0);
      ts0=2*(nll0_1-nll0_0);
      ts0Arr.push_back(ts0);
      
      t->Fill();
      if(itoy%1000==0) t->AutoSave("SaveSelf");
    }

    cout<<GetDeviation(ts1Arr, GetMedian(ts0Arr))<<endl;;
    
    fout->cd();
    t->Write();
    fout->Close();
  }
}
