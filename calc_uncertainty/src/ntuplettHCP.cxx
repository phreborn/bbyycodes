#include "CommonHead.h"
#include "CommonFunc.h"

#include "DiPhotonttHCPNtuple.h"
#include "DiPhotonttHCPNtuple.C"

using namespace std;

const double defaultValue=-998;
const double epsilon=1e-6;

void fill4Vec(TLorentzVector p, float &pT, float &eta, float &phi, float &E){
  if(p.Pt()<epsilon||p.E()<epsilon){
    pT=defaultValue; eta=defaultValue; phi=defaultValue; E=defaultValue;
  }
  else{
    pT=p.Pt(); eta=p.Eta(); phi=p.Phi(); E=p.E();
    // cout<<pT<<" "<<eta<<" "<<phi<<" "<<E<<endl;
  } 
}

double deltaPhill(TLorentzVector l1, TLorentzVector l2, TLorentzVector H){
  return acos((H.Vect().Cross(l1.Vect())*H.Vect().Cross(l2.Vect()))/((H.Vect().Cross(l1.Vect())).Mag()*(H.Vect().Cross(l2.Vect())).Mag()));
}

int main(int argc, char**argv){
  //***************************= Global booking and setting ************************==
  //   gErrorIgnoreLevel = kError+1;
  map<string,bool> Opt;
  Opt["NTUPLE"]=false;

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
    const int outputMode=atoi(argv[4]); // 0: SM, 1: alpha=pi/4, 2: alpha=pi/2
    bool m_debug=argc>5?atoi(argv[5]):false;
      
    TChain *c=CommonFunc::MakeChain("output",inputFileList,inputFileList+".bdf",inputFileList.Contains(".root"));
    unique_ptr<DiPhotonttHCPNtuple> p(new DiPhotonttHCPNtuple(c));
    
    TFile *fout=TFile::Open(outputFileName,"recreate");
    TTree *tout=new TTree("mvatree", "For MVA training");
    
    int ttDecayMode=0;		   // 0 had-had, 1 lep-had, 2 lep-lep
    float pT_y1=0, eta_y1=0, phi_y1=0, E_y1=0, pT_y2=0, eta_y2=0, phi_y2=0, E_y2=0; // Photon four-momentum
    float pT_t1=0, eta_t1=0, phi_t1=0, E_t1=0, pT_t2=0, eta_t2=0, phi_t2=0, E_t2=0; // Top-quark four-momentum
    float pT_b1=0, eta_b1=0, phi_b1=0, E_b1=0, pT_b2=0, eta_b2=0, phi_b2=0, E_b2=0; // Lepton four-momentum
    float pT_l1=0, eta_l1=0, phi_l1=0, E_l1=0, pT_l2=0, eta_l2=0, phi_l2=0, E_l2=0; // B-quark four-momentum
    float pT_H=0, eta_H=0, phi_H=0, E_H=0; // Diphoton four-momentum
    float delta_eta_tt=0, delta_phi_tt=0; // Opening angle between two tops
    float delta_eta_bb=0, delta_phi_bb=0; // Opening angle between two tops
    float delta_eta_ll=0, delta_phi_ll=0; // Opening angle between two leptons
    float m_ttH=0, m_t1H=0, m_t2H=0, m_tt=0, m_yy; // Invariant mass
    float weight=0;
    int N_jet=0, N_jet30=0, N_bjet_fixed70=0, N_bjet_fixed80=0, N_bjet_fixed85=0, N_bjet30_fixed70=0, N_bjet30_fixed80=0, N_bjet30_fixed85=0, N_lep=0;
    float top1_score=0, top2_score=0;
    bool flag_passedIso=0, flag_passedPID=0, isPassed=0;
    float RNDM;
    int category=0;
    
    // Photon
    tout->Branch("pT_y1", &pT_y1, "pT_y1/F");
    tout->Branch("eta_y1", &eta_y1, "eta_y1/F");
    tout->Branch("phi_y1", &phi_y1, "phi_y1/F");
    tout->Branch("E_y1", &E_y1, "E_y1/F");
    tout->Branch("pT_y2", &pT_y2, "pT_y2/F");
    tout->Branch("eta_y2", &eta_y2, "eta_y2/F");
    tout->Branch("phi_y2", &phi_y2, "phi_y2/F");
    tout->Branch("E_y2", &E_y2, "E_y2/F");

    // Top
    tout->Branch("pT_t1", &pT_t1, "pT_t1/F");
    tout->Branch("eta_t1", &eta_t1, "eta_t1/F");
    tout->Branch("phi_t1", &phi_t1, "phi_t1/F");
    tout->Branch("E_t1", &E_t1, "E_t1/F");
    tout->Branch("pT_t2", &pT_t2, "pT_t2/F");
    tout->Branch("eta_t2", &eta_t2, "eta_t2/F");
    tout->Branch("phi_t2", &phi_t2, "phi_t2/F");
    tout->Branch("E_t2", &E_t2, "E_t2/F");

    // Bottom
    tout->Branch("pT_b1", &pT_b1, "pT_b1/F");
    tout->Branch("eta_b1", &eta_b1, "eta_b1/F");
    tout->Branch("phi_b1", &phi_b1, "phi_b1/F");
    tout->Branch("E_b1", &E_b1, "E_b1/F");
    tout->Branch("pT_b2", &pT_b2, "pT_b2/F");
    tout->Branch("eta_b2", &eta_b2, "eta_b2/F");
    tout->Branch("phi_b2", &phi_b2, "phi_b2/F");
    tout->Branch("E_b2", &E_b2, "E_b2/F");

    // Lepton
    tout->Branch("pT_l1", &pT_l1, "pT_l1/F");
    tout->Branch("eta_l1", &eta_l1, "eta_l1/F");
    tout->Branch("phi_l1", &phi_l1, "phi_l1/F");
    tout->Branch("E_l1", &E_l1, "E_l1/F");
    tout->Branch("pT_l2", &pT_l2, "pT_l2/F");
    tout->Branch("eta_l2", &eta_l2, "eta_l2/F");
    tout->Branch("phi_l2", &phi_l2, "phi_l2/F");
    tout->Branch("E_l2", &E_l2, "E_l2/F");

    // Higgs
    tout->Branch("pT_H", &pT_H, "pT_H/F");
    tout->Branch("eta_H", &eta_H, "eta_H/F");
    tout->Branch("phi_H", &phi_H, "phi_H/F");
    tout->Branch("E_H", &E_H, "E_H/F");
    
    // Opening angles
    tout->Branch("delta_eta_tt", &delta_eta_tt, "delta_eta_tt/F");
    tout->Branch("delta_phi_tt", &delta_phi_tt, "delta_phi_tt/F");
    tout->Branch("delta_eta_bb", &delta_eta_bb, "delta_eta_bb/F");
    tout->Branch("delta_phi_bb", &delta_phi_bb, "delta_phi_bb/F");
    tout->Branch("delta_eta_ll", &delta_eta_ll, "delta_eta_ll/F");
    tout->Branch("delta_phi_ll", &delta_phi_ll, "delta_phi_ll/F");

    // Invariant mass
    tout->Branch("m_ttH", &m_ttH, "m_ttH/F");
    tout->Branch("m_t1H", &m_t1H, "m_t1H/F");
    tout->Branch("m_t2H", &m_t2H, "m_t2H/F");
    tout->Branch("m_tt", &m_tt, "m_tt/F");
    tout->Branch("m_yy", &m_yy, "m_yy/F");
    
    tout->Branch("weight", &weight, "weight/F");
    tout->Branch("ttDecayMode", &ttDecayMode, "ttDecayMode/I");
    
    tout->Branch("category", &category, "category/I");

    tout->Branch("top1_score", &top1_score, "top1_score/F");
    tout->Branch("top2_score", &top2_score, "top2_score/F");

    // Counters
    tout->Branch("N_jet", &N_jet, "N_jet/I");
    tout->Branch("N_jet30", &N_jet30, "N_jet30/I");
    tout->Branch("N_bjet_fixed70", &N_bjet_fixed70, "N_bjet_fixed70/I");
    tout->Branch("N_bjet_fixed80", &N_bjet_fixed80, "N_bjet_fixed80/I");
    tout->Branch("N_bjet_fixed85", &N_bjet_fixed85, "N_bjet_fixed85/I");
    tout->Branch("N_bjet30_fixed70", &N_bjet30_fixed70, "N_bjet30_fixed70/I");
    tout->Branch("N_bjet30_fixed80", &N_bjet30_fixed80, "N_bjet30_fixed80/I");
    tout->Branch("N_bjet30_fixed85", &N_bjet30_fixed85, "N_bjet30_fixed85/I");
    tout->Branch("N_lep", &N_lep, "N_lep/I");

    // Flags and handles
    tout->Branch("flag_passedIso", &flag_passedIso, "flag_passedIso/O");
    tout->Branch("flag_passedPID", &flag_passedPID, "flag_passedPID/O");
    tout->Branch("isPassed", &isPassed, "isPassed/O");
    tout->Branch("RNDM", &RNDM, "RNDM/F");
    
    long int nevt=p->fChain->GetEntries();

    cout<<"Tree ready for loop"<<endl;
    for(long int ievt=0;ievt<nevt;ievt++){
      cout<<Form("Processed %.1f%% of events",ievt/double(nevt)*100)<<"\r"<<flush;
      
      p->GetEntry(ievt);
      TString currentFileName=p->fChain->GetCurrentFile()->GetName();
      if( !(1.0*p->ph_pt1/p->m_mgg > 0.35 && 1.0*p->ph_pt2/p->m_mgg > 0.25) ) continue;

      // Mass cuts
      if( p->m_mgg < 105 || p->m_mgg > 160 ) continue;

      if(p->m_nlep==0) ttDecayMode=0;
      else if(p->m_nlep==1) ttDecayMode=1;
      else ttDecayMode=2;
      
      TLorentzVector gam1, gam2;
      gam1.SetPtEtaPhiE(p->ph_pt1, p->ph_eta1, p->ph_phi1, p->ph_E1);
      gam2.SetPtEtaPhiE(p->ph_pt2, p->ph_eta2, p->ph_phi2, p->ph_E2);
      fill4Vec(gam1, pT_y1, eta_y1, phi_y1, E_y1);
      fill4Vec(gam2, pT_y2, eta_y2, phi_y2, E_y2);
      if(m_debug) cout<<"Fill photon 4-vec finished"<<endl;
      
      TLorentzVector H=gam1+gam2;
      fill4Vec(H, pT_H, eta_H, phi_H, E_H);
      if(m_debug) cout<<"Fill diphoton 4-vec finished"<<endl;
      m_yy=H.M();
      
      // Select two hadronic tops
      TLorentzVector t1, t2;
      bool t1Exist=false, t2Exist=false;
      if(ttDecayMode==0){
	if(p->fChain->GetBranchStatus("had1top_pt")&&p->had1top_pt>epsilon&&p->had1top_E>epsilon){
	  t1.SetPtEtaPhiE(p->had1top_pt, p->had1top_eta, p->had1top_phi, p->had1top_E);
	  t1Exist=true;
	}
	top1_score=p->had1top_score;
	if(p->fChain->GetBranchStatus("had2top_pt")&&p->had2top_pt>epsilon&&p->had2top_E>epsilon){
	  t2.SetPtEtaPhiE(p->had2top_pt, p->had2top_eta, p->had2top_phi, p->had2top_E);
	  t2Exist=true;
	}
	top2_score=p->had2top_score;
      }
      else if(ttDecayMode==1){
	if(p->fChain->GetBranchStatus("leptop_pt")&&p->leptop_pt>epsilon&&p->leptop_E>epsilon){
	  t1.SetPtEtaPhiE(p->leptop_pt, p->leptop_eta, p->leptop_phi, p->leptop_E);
	  t1Exist=true;
	}
	top1_score=p->leptop_score;
	if(p->fChain->GetBranchStatus("hadtop_pt")&&p->hadtop_pt>epsilon&&p->hadtop_E>epsilon){
	  t2.SetPtEtaPhiE(p->hadtop_pt, p->hadtop_eta, p->hadtop_phi, p->hadtop_E);
	  t2Exist=true;
	}
	top2_score=p->hadtop_score;
      }

      bool ttExist=t1Exist&&t2Exist;
      
      fill4Vec(t1, pT_t1, eta_t1, phi_t1, E_t1);
      fill4Vec(t2, pT_t2, eta_t2, phi_t2, E_t2);
      if(m_debug){
	cout<<"Fill top 4-vec finished. Decay mode "
	    <<ttDecayMode<<", top 1 exist "<<t1Exist<<", top 2 exist "<<t2Exist
	    <<endl;
	if(ttDecayMode==0){
	  if(t1Exist) cout<<p->had1top_pt<<" "<<p->had1top_eta<<" "<<p->had1top_phi<<" "<<p->had1top_E<<endl;
	  if(t2Exist) cout<<p->had2top_pt<<" "<<p->had2top_eta<<" "<<p->had2top_phi<<" "<<p->had2top_E<<endl;
	}
      }
      if(ttExist){
	delta_eta_tt=t1.Eta()-t2.Eta();
	delta_phi_tt=t1.DeltaPhi(t2);
      }
      else{
	delta_eta_bb=defaultValue;
	delta_phi_bb=defaultValue;
      }
      
      // Select two b-jets with highest pT
      TLorentzVector b1, b2;
      for(int i=0; i<p->m_njet; i++){
	if( p->m_jet_PCbtag->at(i) > 1 && p->m_jet_pt->at(i) > b1.Pt() ){      // 85% b-tagging
	  b2 = b1;
	  b1.SetPtEtaPhiE(p->m_jet_pt->at(i),p->m_jet_eta->at(i),p->m_jet_phi->at(i),p->m_jet_E->at(i));
	}
	else if( p->m_jet_PCbtag->at(i) > 1 && p->m_jet_pt->at(i) > b2.Pt() ){
	  b2.SetPtEtaPhiE(p->m_jet_pt->at(i),p->m_jet_eta->at(i),p->m_jet_phi->at(i),p->m_jet_E->at(i));
	}
      }
      fill4Vec(b1, pT_b1, eta_b1, phi_b1, E_b1);
      fill4Vec(b2, pT_b2, eta_b2, phi_b2, E_b2);
      if(m_debug) cout<<"Fill b-jet 4-vec finished"<<endl;
      
      if(p->m_nbjet_fixed85>=2){
	delta_eta_bb=b1.Eta()-b2.Eta();
	delta_phi_bb=b1.DeltaPhi(b2);
      }
      else{
	delta_eta_bb=defaultValue;
	delta_phi_bb=defaultValue;
      }

      // Select electrons and muons with highest pT
      TLorentzVector l1, l2;
      for(unsigned int i=0; i<p->m_el_pt->size(); i++){
	if( p->m_el_pt->at(i) > l1.Pt() ){
	  l2=l1;
	  l1.SetPtEtaPhiM(p->m_el_pt->at(i),p->m_el_eta->at(i),p->m_el_phi->at(i),0.511e-3);
	}
	else if( p->m_el_pt->at(i) > l2.Pt() ){
	  l2.SetPtEtaPhiM(p->m_el_pt->at(i),p->m_el_eta->at(i),p->m_el_phi->at(i),0.511e-3);
	}
      }

      for(unsigned int i=0; i<p->m_mu_pt->size(); i++){
	if( p->m_mu_pt->at(i) > l1.Pt() ){
	  l2=l1;
	  l1.SetPtEtaPhiM(p->m_mu_pt->at(i),p->m_mu_eta->at(i),p->m_mu_phi->at(i),0.10566);
	}
	else if( p->m_mu_pt->at(i) > l2.Pt() ){
	  l2.SetPtEtaPhiM(p->m_mu_pt->at(i),p->m_mu_eta->at(i),p->m_mu_phi->at(i),0.10566);
	}
      }
      fill4Vec(l1, pT_l1, eta_l1, phi_l1, E_l1);
      fill4Vec(l2, pT_l2, eta_l2, phi_l2, E_l2);
      if(m_debug) cout<<"Fill lepton 4-vec finished"<<endl;
      
      if(p->N_lep>=2){
	delta_eta_ll=l1.Eta()-l2.Eta();
	delta_phi_ll=deltaPhill(l1, l2, H);
      }
      else{
	delta_eta_ll=defaultValue;
	delta_phi_ll=defaultValue;
      }

      // Invariant mass
      if(ttExist){
	m_ttH=(t1+t2+H).M();
	m_tt=(t1+t2).M();
	m_t1H=(t1+H).M();
	m_t2H=(t2+H).M();
      }
      else{			// Can still try to reconstruct m_ttH and m_tt by summing up first six jets
	m_t1H=t1Exist?(t1+H).M():defaultValue;
	m_t2H=t2Exist?(t2+H).M():defaultValue;
	int njet=std::min(6, p->m_njet);
	TLorentzVector sum;
	for(int i=0;i<njet;i++){
	  TLorentzVector jet;
	  jet.SetPtEtaPhiE(p->m_jet_pt->at(i),p->m_jet_eta->at(i),p->m_jet_phi->at(i),p->m_jet_E->at(i));
	  sum+=jet;
	}
	m_tt=sum.M();
	m_ttH=(sum+H).M();
      }

      if(p->fChain->GetBranchStatus("weight")) weight=p->weight;
      else if(p->fChain->GetBranchStatus("m_weight")){
	if(currentFileName.Contains("mc16a")) weight=p->m_weight*0.45;
	else weight=p->m_weight*0.55;
      }
      else abort();
      
      if(outputMode==1) weight*=(p->ME_tot_ttxh_cosasqrt2/p->ME_tot_ttxh_cosa1);
      else if(outputMode==2) weight*=(p->ME_tot_ttxh_cosa0/p->ME_tot_ttxh_cosa1);

      category=p->m_cateindex_wisc;
      
      flag_passedIso=p->flag_passedIso;
      flag_passedPID=p->flag_passedPID;
      isPassed=p->isPassed;
      RNDM=p->RNDM;

      N_jet=p->m_njet;
      N_jet30=p->m_njet30;
      N_bjet_fixed70=p->m_nbjet_fixed70;
      N_bjet_fixed80=p->m_nbjet_fixed80;
      N_bjet_fixed85=p->m_nbjet_fixed85;
      N_bjet30_fixed70=p->m_nbjet30_fixed70;
      N_bjet30_fixed80=p->m_nbjet30_fixed80;
      N_bjet30_fixed85=p->m_nbjet30_fixed85;
      N_lep=p->m_nlep;
      
      tout->Fill();
      if (ievt%100000 == 1) tout->AutoSave("SaveSelf");
    }

    fout->cd();
    tout->Write();
    fout->Close();
  }
  //************************************************************************************==
}
