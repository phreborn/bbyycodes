#include "CommonHead.h"
#include "CommonFunc.h"
#include "MxAODNtup.h"

using namespace std;
using namespace CommonFunc;

bool selectTruthPhotonPair(MxAODNtup *p, TLorentzVector truth[2]){
  int n=p->HGamTruthPhotonsAuxDyn_px->size();
  int idx=0;
  for(int i=0;i<n;i++){
    // Type = 14 means isolated photon, origin = 14 means from Higgs.

    if(p->HGamTruthPhotonsAuxDyn_truthOrigin->at(i)==14){
      if(idx>=2){
	cerr<<"Warning: more than two photons from Higgs boson..."<<endl;
	continue;
      }
      truth[idx].SetPxPyPzE(p->HGamTruthPhotonsAuxDyn_px->at(i), p->HGamTruthPhotonsAuxDyn_py->at(i), p->HGamTruthPhotonsAuxDyn_pz->at(i), p->HGamTruthPhotonsAuxDyn_e->at(i));
      idx++;
    }
  }

  if(idx!=2) return false;
  else return true;
}

int selectTruthLeptonWH(MxAODNtup *p, TLorentzVector &truth){
  int n=p->HGamTruthMuonsAuxDyn_px->size();
  int idx=0;
  for(int i=0;i<n;i++){
    // Type = 6 means isolated muon, origin = 12 means from W boson.
    if(p->HGamTruthMuonsAuxDyn_truthOrigin->at(i)==12){
      if(idx>=1){
	cerr<<"Warning: more than one muon from W boson..."<<endl;
	continue;
      }
      truth.SetPxPyPzE(p->HGamTruthMuonsAuxDyn_px->at(i), p->HGamTruthMuonsAuxDyn_py->at(i), p->HGamTruthMuonsAuxDyn_pz->at(i), p->HGamTruthMuonsAuxDyn_e->at(i));
      idx++;
    }
  }
  // If there are no muons, then select electron
  if(idx==0){
    n=p->HGamTruthElectronsAuxDyn_px->size();
    for(int i=0;i<n;i++){
      // Type = 2 means isolated electron, origin = 12 means from W boson.
      if(p->HGamTruthElectronsAuxDyn_truthOrigin->at(i)==12){
	if(idx>=1){
	  cerr<<"Warning: more than one electron from W boson..."<<endl;
	  continue;
	}
	truth.SetPxPyPzE(p->HGamTruthElectronsAuxDyn_px->at(i), p->HGamTruthElectronsAuxDyn_py->at(i), p->HGamTruthElectronsAuxDyn_pz->at(i), p->HGamTruthElectronsAuxDyn_e->at(i));
	idx++;
      }
    }
  }
  return idx;
}

int selectTruthLeptonPairZH(MxAODNtup *p, TLorentzVector truth[2]){
  int n=p->HGamTruthMuonsAuxDyn_px->size();
  int idx=0;
  for(int i=0;i<n;i++){
    // Type = 6 means isolated muon, origin = 13 means from Z boson.
    if(p->HGamTruthMuonsAuxDyn_truthOrigin->at(i)==13){
      if(idx>=2){
	cerr<<"Warning: more than two muons from Z boson..."<<endl;
	continue;
      }
      truth[idx].SetPxPyPzE(p->HGamTruthMuonsAuxDyn_px->at(i), p->HGamTruthMuonsAuxDyn_py->at(i), p->HGamTruthMuonsAuxDyn_pz->at(i), p->HGamTruthMuonsAuxDyn_e->at(i));
      idx++;
    }
  }
  // If there are no muons, then select electron
  if(idx==0){
    n=p->HGamTruthElectronsAuxDyn_px->size();
    for(int i=0;i<n;i++){
      // Type = 2 means isolated electron, origin = 13 means from Z boson.
      if(p->HGamTruthElectronsAuxDyn_truthOrigin->at(i)==13){
	if(idx>=2){
	  cerr<<"Warning: more than two electrons from Z boson..."<<endl;
	  continue;
	}
	truth[idx].SetPxPyPzE(p->HGamTruthElectronsAuxDyn_px->at(i), p->HGamTruthElectronsAuxDyn_py->at(i), p->HGamTruthElectronsAuxDyn_pz->at(i), p->HGamTruthElectronsAuxDyn_e->at(i));
	idx++;
      }
    }
  }
  return idx;
}

int selectTruthLeptonsttH(MxAODNtup *p, TLorentzVector truth[2]){
  int n=p->HGamTruthMuonsAuxDyn_px->size();
  int idx=0;
  for(int i=0;i<n;i++){
    // Type = 6 means isolated muon, origin = 10 means from top quark.
    if(p->HGamTruthMuonsAuxDyn_truthOrigin->at(i)==10){
      if(idx>=2){
	cerr<<"Warning: more than two leptons from top quarks..."<<endl;
	continue;
      }
      truth[idx].SetPxPyPzE(p->HGamTruthMuonsAuxDyn_px->at(i), p->HGamTruthMuonsAuxDyn_py->at(i), p->HGamTruthMuonsAuxDyn_pz->at(i), p->HGamTruthMuonsAuxDyn_e->at(i));
      idx++;
    }
  }

  n=p->HGamTruthElectronsAuxDyn_px->size();
  for(int i=0;i<n;i++){
    // Type = 2 means isolated electron, origin = 10 means from top quark.
    if(p->HGamTruthElectronsAuxDyn_truthOrigin->at(i)==10){
      if(idx>=2){
	cerr<<"Warning: more than two leptons from top quarks..."<<endl;
	continue;
      }
      truth[idx].SetPxPyPzE(p->HGamTruthElectronsAuxDyn_px->at(i), p->HGamTruthElectronsAuxDyn_py->at(i), p->HGamTruthElectronsAuxDyn_pz->at(i), p->HGamTruthElectronsAuxDyn_e->at(i));
      idx++;
    }
  }
  return idx;
}

bool matchTruthPhoton(double eta, double phi, TLorentzVector truth[2], double cut=0.2){
  if(Cone(eta, phi, truth[0].Eta(), truth[0].Phi())<cut) return true;
  else if(Cone(eta, phi, truth[1].Eta(), truth[1].Phi())<cut) return true;
  else return false;
}

bool matchTruthLeptonWH(double eta, double phi, TLorentzVector truth, double cut=0.2){
  if(Cone(eta, phi, truth.Eta(), truth.Phi())<cut) return true;
  else return false;
}

bool matchTruthLeptonsZH(double eta, double phi, TLorentzVector truth[2], double cut=0.2){
  if(Cone(eta, phi, truth[0].Eta(), truth[0].Phi())<cut) return true;
  else if(Cone(eta, phi, truth[1].Eta(), truth[1].Phi())<cut) return true;
  else return false;
}

bool matchTruthLeptonsttH(double eta, double phi, TLorentzVector truth[2], int nTruthLep, double cut=0.2){
  if(nTruthLep==1){
    if(Cone(eta, phi, truth[0].Eta(), truth[0].Phi())<cut) return true;
    else return false;
  }
  else{
    if(Cone(eta, phi, truth[0].Eta(), truth[0].Phi())<cut) return true;
    else if(Cone(eta, phi, truth[1].Eta(), truth[1].Phi())<cut) return true;
    else return false;
  }
}

int main(int argc, char** argv){
  TString jobname=argv[1];
  TString inputFileList=argv[2];
  const int mode=atoi(argv[3]);	// WH=1, ZH=2, ttH lep-had=3, ttH lep-lep=4

  TChain *c=MakeChain("CollectionTree", inputFileList, "badfile", inputFileList.Contains(".root"));
  MxAODNtup *p=new MxAODNtup(c);

  TH1D *h_pt_1st=new TH1D("h_pt_1st", "h_pt_1st", 150, 0, 300);
  TH1D *h_pt_2nd=new TH1D("h_pt_2nd", "h_pt_2nd", 150, 0, 300);
  
  long int nevt=p->fChain->GetEntries();
  double total=0, total_lep=0, total_lep_sel=0, pass_current_pt=0;

  for(int ievt=0; ievt<nevt; ievt++){
    p->fChain->GetEntry(ievt);
    if(!p->isPassedBasic||!p->isPassedPID||!p->isPassedIsolation) continue;

    TLorentzVector truth[2];
    if(!selectTruthPhotonPair(p, truth)) continue; // Cannot select two photons from Higgs

    if(!matchTruthPhoton(p->eta->at(0), p->phi->at(0), truth) || !matchTruthPhoton(p->eta->at(1), p->phi->at(1), truth)) continue; // Cannot be matched to photon decay from Higgs
    if(p->pt->at(0)<5*GeV||p->pt->at(1)<5*GeV) continue; // Require less than 5 GeV
    total+=p->weight;

    TLorentzVector truthlepton[2];
    int nTruthLep=0;
    if(mode==1){
      nTruthLep=selectTruthLeptonWH(p, truthlepton[0]);
      if(nTruthLep!=1) continue;
    }
    if(mode==2){
      nTruthLep=selectTruthLeptonPairZH(p, truthlepton);
      if(nTruthLep!=2) continue;
    }
    if(mode==3){
      nTruthLep=selectTruthLeptonsttH(p, truthlepton);
      if(nTruthLep!=1&&nTruthLep!=2) continue;
    }
    total_lep+=p->weight;

    int nElec=p->HGamElectronsAuxDyn_pt->size(), nMuon=p->HGamMuonsAuxDyn_pt->size();
    if(nElec==0 && nMuon==0) continue; // At least contain one reconstructed lepton

    bool lepMatched=false;
    int matchedElecIdx[2]={-1, -1}, matchedMuonIdx[2]={-1, -1};

    for(int i=0;i<nElec;i++){
      if(mode==1) lepMatched=matchTruthLeptonWH(p->HGamElectronsAuxDyn_eta->at(i), p->HGamElectronsAuxDyn_phi->at(i), truthlepton[0]);
      else if(mode==2) lepMatched=matchTruthLeptonsZH(p->HGamElectronsAuxDyn_eta->at(i), p->HGamElectronsAuxDyn_phi->at(i), truthlepton);
      else if(mode==3) lepMatched=matchTruthLeptonsttH(p->HGamElectronsAuxDyn_eta->at(i), p->HGamElectronsAuxDyn_phi->at(i), truthlepton, nTruthLep);
      if(lepMatched){
	if(mode==1){
	  matchedElecIdx[0]=i;
	  break;
	}
	else if(mode==2||mode==3){
	  if(matchedElecIdx[0]==-1) matchedElecIdx[0]=i;
	  else if(matchedElecIdx[1]==-1) matchedElecIdx[1]=i;
	  else abort();
	}
      }
    }

    for(int i=0;i<nMuon;i++){
      if(mode==1) lepMatched=matchTruthLeptonWH(p->HGamMuonsAuxDyn_eta->at(i), p->HGamMuonsAuxDyn_phi->at(i), truthlepton[0]);
      else if(mode==2) lepMatched=matchTruthLeptonsZH(p->HGamMuonsAuxDyn_eta->at(i), p->HGamMuonsAuxDyn_phi->at(i), truthlepton);
      else if(mode==3) lepMatched=matchTruthLeptonsttH(p->HGamMuonsAuxDyn_eta->at(i), p->HGamMuonsAuxDyn_phi->at(i), truthlepton, nTruthLep);
      if(lepMatched){
	if(mode==1){
	  if(matchedElecIdx[0]!=-1) abort();
	  matchedMuonIdx[0]=i;
	  break;
	}
	else if(mode==2||mode==3){
	  if(mode==2&&matchedElecIdx[0]!=-1) abort();
	  if(mode==3&&matchedElecIdx[1]!=-1) abort();

	  if(matchedMuonIdx[0]==-1) matchedMuonIdx[0]=i;
	  else if(matchedMuonIdx[1]==-1) matchedMuonIdx[1]=i;
	  else abort();
	}
      }
    }

    if(!lepMatched) continue; 	// Lepton cannot be matched to truth particles
    total_lep_sel+= p->weight; // Selected leptonic events

    h_pt_1st->Fill(p->pt->at(0)/GeV,p->weight);
    h_pt_2nd->Fill(p->pt->at(1)/GeV,p->weight);

    if(p->pt->at(0)/p->m_yy>0.35&&p->pt->at(1)/p->m_yy>0.25) pass_current_pt+=p->weight; // Passing relative pT cut
  }

  SetAtlasStyle();
  TCanvas *cv=new TCanvas("c","c",1600,600);
  cv->Divide(2);
  h_pt_1st->SetLineColor(kRed);
  h_pt_2nd->SetLineColor(kBlue);
  h_pt_1st->SetMinimum(0);
  h_pt_2nd->SetMinimum(0);
  cv->cd(1);
  h_pt_1st->Draw("hist");
  cv->cd(2);
  h_pt_2nd->Draw("hist");

  system("mkdir -vp fig/"+jobname);
  PrintCanvas(cv,"fig/"+jobname+"/pt");
  ofstream fout("fig/"+jobname+"/summary.txt");
  stringstream str;
  str<<"Passing inclusive selection: "<<total<<", leptonic events: "<<total_lep<<"("<<total_lep/total
     <<"), selected leptonic events: "<<total_lep_sel<<"("<<total_lep_sel/total_lep
     <<") passing current pT cut: "<<pass_current_pt<<"("<<pass_current_pt/total_lep_sel<<")"<<endl;
  cout<<str.str();
  fout<<str.str();
  fout.close();
}
