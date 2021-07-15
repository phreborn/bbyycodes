#include "CommonHead.h"
#include "CommonFunc.h"
#include "tout.h"

using namespace std;
using namespace CommonFunc;

int main(int argc, char** argv){
  SetAtlasStyle();
  gErrorIgnoreLevel=kError+1;
  TString selection=argv[1];
  double etaCut=atof(argv[2]);
  TString option=argv[3];
  
  TString inputMCFileName="Output/sample/mc/Sherpa_gamgam_2DP20.root";
  TString inputMCRewFileName="Output/sample/mc/Sherpa_gamgam_2DP20_reweight.root";
  TString inputDataFileName="Output/sample/data/skim.root";
  
  double xmin=200, xmax=2000;
  int nbin=90;
  double binw=(xmax-xmin)/nbin;

  const int ncat=option.Contains("3cat")?3:2;
  
  TH1D *hdata[ncat], *hmc[ncat], *hmcrew[ncat];

  for(int icat=0; icat<ncat; icat++){
    hdata[icat]=new TH1D(Form("hdata_%d", icat), Form("hdata_%d", icat), nbin, xmin, xmax); hdata[icat]->Sumw2();
    hmc[icat]=new TH1D(Form("hmc_%d", icat), Form("hmc_%d", icat), nbin, xmin, xmax); hmc[icat]->Sumw2();
    hmcrew[icat]=new TH1D(Form("hmcrew_%d", icat), Form("hmcrew_%d", icat), nbin, xmin, xmax); hmcrew[icat]->Sumw2();
  }
  
  TChain *cdata=MakeChain("CollectionTree", inputDataFileName, inputDataFileName+".bdf", inputDataFileName.Contains(".root"));
  TChain *cmc=MakeChain("tout", inputMCFileName, inputMCFileName+".bdf", inputMCFileName.Contains(".root"));
  TChain *cmcrew=MakeChain("tout", inputMCRewFileName, inputMCRewFileName+".bdf", inputMCRewFileName.Contains(".root"));

  tout *pMc=new tout(cmc);
  tout *pMcRew=new tout(cmcrew);

  float mass, weight;
  ULong64_t eventNumber;
  UInt_t runNumber;
  char isPassedLowHighMyy, isPassedExotic, isDalitz, isPassedIsolationLowHighMyy;
  vector<int>     *conversionType=0;
  vector<float>   *eta_s2=0;
  
  cdata->SetBranchAddress("EventInfoAuxDyn.runNumber",&runNumber);
  cdata->SetBranchAddress("EventInfoAuxDyn.eventNumber",&eventNumber);

  cdata->SetBranchAddress("HGamEventInfoAuxDyn.m_yy",&mass);
  
  cdata->SetBranchAddress("HGamEventInfoAuxDyn.isDalitz",&isDalitz);
  cdata->SetBranchAddress("HGamEventInfoAuxDyn.isPassedExotic",&isPassedExotic);
  cdata->SetBranchAddress("HGamEventInfoAuxDyn.isPassedLowHighMyy",&isPassedLowHighMyy);
  cdata->SetBranchAddress("HGamEventInfoAuxDyn.isPassedIsolationLowHighMyy",&isPassedIsolationLowHighMyy);

  cdata->SetBranchAddress("HGamPhotonsAuxDyn.conversionType", &conversionType);
  cdata->SetBranchAddress("HGamPhotonsAuxDyn.eta_s2", &eta_s2);

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
    if(fabs(eta_s2->at(0))<etaCut&&fabs(eta_s2->at(1))<etaCut){
      hdata[0]->Fill(mass/GeV);
    }
    else{
      hdata[1]->Fill(mass/GeV);
    }
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
    if(fabs(pMc->eta_s2_1st)<etaCut&&fabs(pMc->eta_s2_2nd)<etaCut) hmc[0]->Fill(pMc->m_yy/GeV, pMc->vertexWeight*pMc->crossSectionBRfilterEff/pMc->totalEvents);
    else hmc[1]->Fill(pMc->m_yy/GeV, pMc->vertexWeight*pMc->crossSectionBRfilterEff/pMc->totalEvents);
  }

  int nmcrew_evt=cmcrew->GetEntries();
  for(int imcrew=0;imcrew<nmcrew_evt;imcrew++){
    cmcrew->GetEntry(imcrew);
    if(selection=="EKHI"){
      if(!pMcRew->isPassEKHI) continue;
      if(pMcRew->m_yy<200*GeV||pMcRew->m_yy>2000*GeV) continue;
    }
    else if(selection=="HKHI"){
      if(!pMcRew->isPassHKHI) continue;
      if(pMcRew->m_yy<150*GeV||pMcRew->m_yy>2000*GeV) continue;
    }
    else abort();
    if(fabs(pMcRew->eta_s2_1st)<etaCut&&fabs(pMcRew->eta_s2_2nd)<etaCut) hmcrew[0]->Fill(pMcRew->m_yy/GeV, pMcRew->vertexWeight*pMcRew->crossSectionBRfilterEff/pMcRew->totalEvents);
    else hmcrew[1]->Fill(pMcRew->m_yy/GeV, pMcRew->vertexWeight*pMcRew->crossSectionBRfilterEff/pMcRew->totalEvents);
  }

  cout<<hmcrew[0]->GetEntries()<<endl;
  TFile *fout=TFile::Open("output.root","recreate");
  for(int icat=0;icat<ncat;icat++){
    ScaleToOne(hmc[icat]);
    ScaleToOne(hmcrew[icat]);
    ScaleToOne(hdata[icat]);

    hmc[icat]->SetLineColor(kBlue);
    hmcrew[icat]->SetLineColor(kRed);

    TCanvas *c=new TCanvas("c","c",800,600);
    c->SetLogy();
    hdata[icat]->Draw("E");
    hmcrew[icat]->Draw("hist,same");
    hmc[icat]->Draw("hist,same");
    hdata[icat]->Draw("E,same");

    PrintCanvas(c, Form("fig/category_etaCut_%.2f_category_%d", etaCut, icat));
    fout->cd();
    hdata[icat]->Write();
    hmc[icat]->Write();
    hmcrew[icat]->Write();
  }
  fout->Close();
}
