#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"

#include "statistics.hh"
#include "tout.h"
#include "gravitonNtup.h"
#include "MxAODNtup.h"

using namespace std;
using namespace CommonFunc;
using namespace RooFit;
using namespace RooStats;

const double epsilon=1e-6;

double poisson_cdf_c(Double_t n, double mu) {
  double a = n + 1.0;
  return isfinite(ROOT::Math::gamma_cdf(mu, a, 1.0))?ROOT::Math::gamma_cdf(mu, a, 1.0):0;
}

double poisson_pdf(double n, double mu){
  return isfinite(std::exp (n*std::log(mu) - ROOT::Math::lgamma(n+1) - mu))?(std::exp (n*std::log(mu) - ROOT::Math::lgamma(n+1) - mu)):0;
}

double twoBinCounting(double *x, double *p){
  double poi1=poisson_pdf(p[0]+x[0]*p[1], p[0]);
  double poi2=poisson_pdf(p[2]+x[0]*p[3], p[2]);
  return poi1*poi2;
}

int main(int argc, char** argv){
  gErrorIgnoreLevel=kError+1;
  double costCut=atof(argv[1]);
  TString selection=argv[2];
  double injectedNsig=atof(argv[3]);
  TString option=argv[4];
  
  double xmin=200, xmax=2000;
  int nbin=360;

  if(option.Contains("input")){
    xmin=(selection=="EKHI"?200:150);
    xmax=2500;
    nbin=int((xmax-xmin+epsilon)/5.);
    cout<<xmin<<" "<<xmax<<" "<<nbin<<endl;
  }

  double binw=(xmax-xmin)/nbin;
  const int ncat=option.Contains("3cat")?3:2;
  
  TH1D *hdata[ncat], *hsig[ncat], *hbkg[ncat];

  for(int icat=0; icat<ncat; icat++){
    hdata[icat]=new TH1D(Form("hdata_%d", icat), Form("hdata_%d", icat), nbin, xmin, xmax); hdata[icat]->Sumw2();
    hsig[icat]=new TH1D(Form("hsig_%d", icat), Form("hsig_%d", icat), nbin, xmin, xmax); hsig[icat]->Sumw2();
    hbkg[icat]=new TH1D(Form("hbkg_%d", icat), Form("hbkg_%d", icat), nbin, xmin, xmax); hbkg[icat]->Sumw2();
  }
  
  TString inputDataFileName="Output/sample/data/skim.root";
  TString inputBkgMCFileName="Output/sample/mc/Sherpa_gamgam_2DP20.root";
  TString inputSigMCFileName="";

  TString sigModel="";
  if(option.Contains("scalar")){
    inputSigMCFileName="Output/sample/mc/PowhegPy8_ggH750_W6p.MxAOD.p2470.h011.root";
    sigModel="scalar";
  }
  else if(option.Contains("graviton")){
    inputSigMCFileName="Output/Graviton/single_sample/mc15_m750_k02.root";
    sigModel="graviton";
  }
  else abort();
  
  TChain *cdata=MakeChain("CollectionTree", inputDataFileName, inputDataFileName+".bdf", inputDataFileName.Contains(".root"));
  TChain *csig=MakeChain("CollectionTree", inputSigMCFileName, inputSigMCFileName+".bdf", inputSigMCFileName.Contains(".root"));
  TChain *cbkg=MakeChain("tout", inputBkgMCFileName, inputBkgMCFileName+".bdf", inputBkgMCFileName.Contains(".root"));

  MxAODNtup *pData=new MxAODNtup(cdata);
  tout *pBkg=new tout(cbkg);

  // First step: fill data into histograms
  bool produceDataPoints=option.Contains("datapoint");
  bool produceFraction=option.Contains("fraction");
  
  ofstream* fout_data_Cost=NULL, *fout_data_nonCost=NULL;

  if(produceDataPoints){
    fout_data_Cost=new ofstream("/afs/cern.ch/user/y/yanght/workarea/GG/xmlAnaWSBuilder/Input/data/high_mass_diphoton/mass_points_data15_13TeV_"+selection+Form("_Cost%02d.txt", int(costCut*10)));
    fout_data_nonCost=new ofstream("/afs/cern.ch/user/y/yanght/workarea/GG/xmlAnaWSBuilder/Input/data/high_mass_diphoton/mass_points_data15_13TeV_"+selection+Form("_nonCost%02d.txt", int(costCut*10)));
  }
  int ndata_evt=cdata->GetEntries();
  cout<<ndata_evt<<endl;
  for(int idata=0;idata<ndata_evt;idata++){
    cdata->GetEntry(idata);
    // cout<<bool(pData->isPassedExotic)<<" "<<bool(pData->isPassedIsolationLowHighMyy)<<endl;
    if(selection=="EKHI"){
      if(!(bool(pData->isPassedExotic)&&bool(pData->isPassedIsolationLowHighMyy))) continue;
    }
    else if(selection=="HKHI"){
      if(!bool(pData->isPassedLowHighMyy)) continue;
    }
    else abort();
    // cout<<pData->cosTS_yy<<endl;
    if(fabs(pData->cosTS_yy)<costCut){
      hdata[0]->Fill(pData->m_yy/GeV);
      if(produceDataPoints) *fout_data_Cost<<pData->m_yy/GeV<<endl;
    }
    else{
      hdata[1]->Fill(pData->m_yy/GeV);
      if(produceDataPoints) *fout_data_nonCost<<pData->m_yy/GeV<<endl;
    }
  }

  if(option.Contains("datapoint")){
    fout_data_Cost->close();
    fout_data_nonCost->close();
  }
  
  // Then fill the bkg MC histogram and normalize it properly
  int nbkg_evt=cbkg->GetEntries();
  for(int ibkg=0;ibkg<nbkg_evt;ibkg++){
    cbkg->GetEntry(ibkg);
    if(selection=="EKHI"){
      if(!pBkg->isPassEKHI) continue;
    }
    else if(selection=="HKHI"){
      if(!pBkg->isPassHKHI) continue;
    }
    TLorentzVector v1, v2;
    v1.SetPtEtaPhiM(pBkg->pt_1st, pBkg->eta_1st, pBkg->phi_1st, 0);
    v2.SetPtEtaPhiM(pBkg->pt_2nd, pBkg->eta_2nd, pBkg->phi_2nd, 0);
    double costs=CommonFunc::CostsCS(v1, v2);
    
    if(fabs(costs)<costCut) hbkg[0]->Fill(pBkg->m_yy/GeV, pBkg->vertexWeight*pBkg->crossSectionBRfilterEff/pBkg->totalEvents);
    else hbkg[1]->Fill(pBkg->m_yy/GeV, pBkg->vertexWeight*pBkg->crossSectionBRfilterEff/pBkg->totalEvents);
  }

  if(option.Contains("inclusive_norm")){
    double normData=0, normMC=0;
    
    for(int icat=0;icat<ncat;icat++){
      int binStart=FindBin(hdata[icat], xmin);
      int binEnd=FindBin(hdata[icat], xmax)-1;
      
      normData+=hdata[icat]->Integral(binStart, binEnd);
      normMC+=hbkg[icat]->Integral(binStart, binEnd);
    }
    for(int icat=0;icat<ncat;icat++) hbkg[icat]->Scale(normData/normMC);
  }
  else{
    for(int icat=0;icat<ncat;icat++){
      int binStart=FindBin(hdata[icat], xmin);
      int binEnd=FindBin(hdata[icat], xmax)-1;
      
      double normData=hdata[icat]->Integral(binStart, binEnd);
      double normMC=hbkg[icat]->Integral(binStart, binEnd);
      
      hbkg[icat]->Scale(normData/normMC);
    }
  }
  
  // Finally inject signal
  int nsig_evt=csig->GetEntries();
  if(sigModel=="scalar"){  
    MxAODNtup *pSig=new MxAODNtup(csig);
    for(int isig=0;isig<nsig_evt;isig++){
      csig->GetEntry(isig);

      if(selection=="HKHI"){
	if(!(bool(pSig->isPassedLowHighMyy)&&!bool(pSig->isDalitz))) continue;
      }
      else if(selection=="EKHI"){
	if(!(bool(pSig->isPassedExotic)&&bool(pSig->isPassedIsolationLowHighMyy)&&!bool(pSig->isDalitz))) continue;
      }
      if(fabs(pSig->cosTS_yy)<costCut) hsig[0]->Fill(pSig->m_yy/GeV, pSig->weight);
      else hsig[1]->Fill(pSig->m_yy/GeV, pSig->weight);
    }
  }
  else if(sigModel=="graviton"){
    gravitonNtup *pSig=new gravitonNtup(csig);
    for(int isig=0;isig<nsig_evt;isig++){
      csig->GetEntry(isig);
      if(selection=="EKHI"){
	pSig->accepted=pSig->pass_ld_subld_id&&(pSig->pt_leading>55*1e3)&&(pSig->pt_subleading>55*1e3)&&(pSig->topoetcone40_leading<0.022*pSig->pt_leading+2450)&&(pSig->topoetcone40_subleading<0.022*pSig->pt_subleading+2450)&&(pSig->ptcone20_leading<0.05*pSig->pt_leading)&&(pSig->ptcone20_subleading<0.05*pSig->pt_subleading);
      }
      if(selection=="HKHI"){
	pSig->accepted=pSig->pass_ld_subld_id&&(pSig->pt_leading>(pSig->mass_gev*1E3*0.4))&&(pSig->pt_subleading>(pSig->mass_gev*1E3*0.3))&&(pSig->topoetcone40_leading<0.022*pSig->pt_leading+2450)&&(pSig->topoetcone40_subleading<0.022*pSig->pt_subleading+2450)&&(pSig->ptcone20_leading<0.05*pSig->pt_leading)&&(pSig->ptcone20_subleading<0.05*pSig->pt_subleading);
      }
      if(pSig->accepted*pSig->total_weight==0) continue;
      TLorentzVector v1, v2;
      v1.SetPtEtaPhiM(pSig->pt_leading, pSig->eta_leading, pSig->phi_leading, 0);
      v2.SetPtEtaPhiM(pSig->pt_subleading, pSig->eta_subleading, pSig->phi_subleading, 0);
      double costs=CostsCS(v1, v2);
      if(fabs(costs)<costCut) hsig[0]->Fill(pSig->mgg, pSig->total_weight);
      else hsig[1]->Fill(pSig->mgg, pSig->total_weight);
    }
  }
  double totalSig=0;
  for(int icat=0;icat<ncat; icat++) totalSig+=hsig[icat]->Integral();

  ofstream *fout_frac=NULL;
  if(produceFraction){
    fout_frac=new ofstream("Output/frac/"+selection+Form("/Cost%d_%s", int(costCut*100), sigModel.Data()));
  }
  for(int icat=0;icat<ncat; icat++){
    double frac=hsig[icat]->Integral()/totalSig;
    ScaleTo(hsig[icat], frac*injectedNsig);
    if(produceFraction) (*fout_frac)<<frac<<" ";
  }
  if(produceFraction){
    (*fout_frac)<<endl<<totalSig<<endl;
    fout_frac->close();
  }
  // Now calculating the number counting significance
  TF1 *pdf=new TF1("pdf",twoBinCounting,-1000,1000,4);
  double totalSignif=0;
  double significance[ncat], nsig[ncat], nbkg[ncat];

  int paramIdx=0;
  for(int icat=0;icat<ncat;icat++){
    int binStart=FindBin(hbkg[icat], 700);
    int binEnd=FindBin(hbkg[icat], 800)-1;
    
    nbkg[icat]=hbkg[icat]->Integral(binStart, binEnd);
    nsig[icat]=hsig[icat]->Integral(binStart, binEnd);

    // pdf->SetParameter(paramIdx, normBkg);
    // pdf->SetParameter(paramIdx+1, normSig);
    // paramIdx+=2;
    
    significance[icat]=statistics::significance(nbkg[icat]+nsig[icat], nbkg[icat]);
    // significance[icat]=RooStats::PValueToSignificance(poisson_cdf_c(nbkg[icat]+nsig[icat], nbkg[icat]));
    totalSignif+=significance[icat]*significance[icat];
  }
  totalSignif=sqrt(totalSignif);
  // ROOT::Math::Functor1D f1(pdf);
  // ROOT::Math::Integrator ig(f1, ROOT::Math::IntegrationOneDim::kADAPTIVE,1.E-12,1.E-12);
  
  // cout<<pdf->Integral(0,100)<<endl;
  // cout<<ig.Integral(1,1000)<<endl;
  // Save the output
  TString outputDir="Output/optimization/"+selection;
  if(option.Contains("inclusive_norm")) outputDir+="_inclusive_norm";
  if(option.Contains("input")) outputDir+="_input";
  system("mkdir -vp "+outputDir);
  TString outputFileName=outputDir+Form("/summary_%s_costs_%.2f_%.4f", sigModel.Data(), costCut, injectedNsig);
  TFile *fout_root=TFile::Open(outputFileName+".root","recreate");
  ofstream fout_txt(outputFileName+".txt");
  
  for(int icat=0;icat<ncat;icat++){
    fout_root->cd();
    hdata[icat]->Write();
    hbkg[icat]->Write();
    hsig[icat]->Write();
    fout_txt<<significance[icat]<<" ";
  }
  
  cout<<totalSignif<<endl;

  fout_txt<<totalSignif<<endl;

  for(int icat=0; icat<ncat; icat++){
    fout_txt<<nsig[icat]<<" "<<nbkg[icat]<<" "<<endl;
  }
  
  fout_root->Close();
  fout_txt.close();
}
