#include "CommonHead.h"
#include "CommonFunc.h"
#include "tout.h"

using namespace std;
using namespace CommonFunc;

double costsCS(TLorentzVector v1, TLorentzVector v2){

  TLorentzVector Vdiphoton  = v1 + v2;

  Double_t Q=Vdiphoton.M();
  Double_t Qt=Vdiphoton.Pt(); 
  Double_t costs=TMath::Abs( 1/(Q*sqrt(Q*Q+Qt*Qt))*( (v1.E()+v1.Z())*(v2.E()-v2.Z()) - (v1.E()-v1.Z())*(v2.E()+v2.Z()) ) );

  return costs;
}

int main(int argc, char** argv){
  TString selection=argv[1];
  TString option=argv[2];
  
  TString inputMCFileName="Output/sample/mc/Sherpa_gamgam_2DP20_reweight.root";
  TString inputDataFileName="Output/sample/data/skim.root";
  gErrorIgnoreLevel=kError+1;

  // Delta-eta between two photons
  // double xmin=0, xmax=5;

  // Costheta*_CS
  // double xmin=0,xmax=1;

  double xmin=0, xmax=100;
  int nbin=10;
  double binw=(xmax-xmin)/nbin;
  
  TH1D *hdata=new TH1D(Form("hdata"), Form("hdata"), nbin, xmin, xmax); hdata->Sumw2();
  TH1D *hmc=new TH1D(Form("hmc"), Form("hmc"), nbin, xmin, xmax); hmc->Sumw2();

  TChain *cdata=MakeChain("CollectionTree", inputDataFileName, inputDataFileName+".bdf", inputDataFileName.Contains(".root"));
  TChain *cmc=MakeChain("tout", inputMCFileName, inputMCFileName+".bdf", inputMCFileName.Contains(".root"));

  tout *pMc=new tout(cmc);

  float mass, weight;
  ULong64_t eventNumber;
  UInt_t runNumber;
  char isPassedLowHighMyy, isPassedExotic, isDalitz, isPassedIsolationLowHighMyy;
  vector<int>     *conversionType=0;
  vector<float>   *eta_s2=0, *eta=0, *pt=0, *phi=0;
  
  cdata->SetBranchAddress("EventInfoAuxDyn.runNumber",&runNumber);
  cdata->SetBranchAddress("EventInfoAuxDyn.eventNumber",&eventNumber);

  cdata->SetBranchAddress("HGamEventInfoAuxDyn.m_yy",&mass);
  
  cdata->SetBranchAddress("HGamEventInfoAuxDyn.isDalitz",&isDalitz);
  cdata->SetBranchAddress("HGamEventInfoAuxDyn.isPassedExotic",&isPassedExotic);
  cdata->SetBranchAddress("HGamEventInfoAuxDyn.isPassedLowHighMyy",&isPassedLowHighMyy);
  cdata->SetBranchAddress("HGamEventInfoAuxDyn.isPassedIsolationLowHighMyy",&isPassedIsolationLowHighMyy);

  cdata->SetBranchAddress("HGamPhotonsAuxDyn.conversionType", &conversionType);
  cdata->SetBranchAddress("HGamPhotonsAuxDyn.eta_s2", &eta_s2);
  cdata->SetBranchAddress("HGamPhotonsAuxDyn.eta", &eta);
  cdata->SetBranchAddress("HGamPhotonsAuxDyn.pt", &pt);
  cdata->SetBranchAddress("HGamPhotonsAuxDyn.phi", &phi);

  // First step: fill data into histograms

  int ndata_evt=cdata->GetEntries();
  for(int idata=0;idata<ndata_evt;idata++){
    cdata->GetEntry(idata);
    if(selection=="EKHI"){
      if(!(bool(isPassedExotic)&&bool(isPassedIsolationLowHighMyy))) continue;
      if(mass<200*GeV||mass>2000*GeV) continue;
    }
    else if(selection=="HKHI"){
      if(!bool(isPassedLowHighMyy)) continue;
      if(mass<150*GeV||mass>2000*GeV) continue;
    }
    else abort();
    // hdata->Fill(fabs(eta_s2->at(0)-eta_s2->at(1)));
    TLorentzVector v1, v2;
    v1.SetPtEtaPhiM(pt->at(0), eta->at(0), phi->at(0), 0);
    v2.SetPtEtaPhiM(pt->at(1), eta->at(1), phi->at(1), 0);
    // hdata->Fill(fabs(costsCS(v1, v2)));
    hdata->Fill((v1+v2).Pt()/GeV);
  }

  // Then fill the mc MC histogram and normalize it properly
  int nmc_evt=cmc->GetEntries();
  for(int imc=0;imc<nmc_evt;imc++){
    cmc->GetEntry(imc);
    if(selection=="EKHI"){
      if(!pMc->isPassEKHI) continue;
      if(pMc->m_yy<200*GeV||pMc->m_yy>2000*GeV) continue;
    }
    else if(selection=="HKHI"){
      if(!pMc->isPassHKHI) continue;
      if(pMc->m_yy<150*GeV||pMc->m_yy>2000*GeV) continue;
    }
    else abort();
    // hmc->Fill(fabs(pMc->eta_s2_1st-pMc->eta_s2_2nd), pMc->vertexWeight*pMc->crossSectionBRfilterEff/pMc->totalEvents);
    TLorentzVector v1, v2;
    v1.SetPtEtaPhiM(pMc->pt_1st, pMc->eta_1st, pMc->phi_1st, 0);
    v2.SetPtEtaPhiM(pMc->pt_2nd, pMc->eta_2nd, pMc->phi_2nd, 0);
    // hmc->Fill(fabs(costsCS(v1, v2)), pMc->vertexWeight*pMc->crossSectionBRfilterEff/pMc->totalEvents);
    hmc->Fill((v1+v2).Pt()/GeV, pMc->vertexWeight*pMc->crossSectionBRfilterEff/pMc->totalEvents);
  }
  ScaleToOne(hmc);
  ScaleToOne(hdata);

  TH1D *hratio=(TH1D*)hdata->Clone("hratio");
  hratio->Divide(hmc);
  
  TFile *fout=TFile::Open("output.root","recreate");

  TTree *outputTree=cmc->CloneTree(0);
  for(int imc=0;imc<nmc_evt;imc++){
    cmc->GetEntry(imc);
    if(selection=="EKHI"){
      if(!pMc->isPassEKHI) continue;
      if(pMc->m_yy<200*GeV||pMc->m_yy>2000*GeV) continue;
    }
    else if(selection=="HKHI"){
      if(!pMc->isPassHKHI) continue;
      if(pMc->m_yy<150*GeV||pMc->m_yy>2000*GeV) continue;
    }
    else abort();
    TLorentzVector v1, v2;
    v1.SetPtEtaPhiM(pMc->pt_1st, pMc->eta_1st, pMc->phi_1st, 0);
    v2.SetPtEtaPhiM(pMc->pt_2nd, pMc->eta_2nd, pMc->phi_2nd, 0);
    // double addWt=hratio->GetBinContent(hratio->FindBin(fabs(costsCS(v1, v2))));
    double addWt=hratio->GetBinContent(hratio->FindBin((v1+v2).Pt()/GeV));
    
    // double addWt=hratio->GetBinContent(hratio->FindBin(fabs(pMc->eta_s2_1st-pMc->eta_s2_2nd)));
    pMc->vertexWeight*=addWt;
    outputTree->Fill();
  }
  
  hmc->Write();
  hdata->Write();
  hratio->Write();
  outputTree->Write();
  fout->Close();
}
