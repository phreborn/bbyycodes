#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"

#include "statistics.hh"
#include "tout.h"
#include "gravitonNtup.h"

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
  double etaCut=atof(argv[1]);
  TString selection=argv[2];
  double injectedNsig=atof(argv[3]);
  TString option=argv[4];
  
  double xmin=200, xmax=2000;
  int nbin=360;

  if(option.Contains("input")){
    xmin=(selection=="EKHI"?200:150);
    xmax=2500;
    nbin=int((xmax-xmin+epsilon)/5.);
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

  tout *pBkg=new tout(cbkg);

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
  bool produceDataPoints=option.Contains("datapoint");
  bool produceFraction=option.Contains("fraction");
  
  ofstream* fout_data_Eta=NULL, *fout_data_nonEta=NULL;

  if(produceDataPoints){
    fout_data_Eta=new ofstream("/afs/cern.ch/user/y/yanght/workarea/GG/xmlAnaWSBuilder/Input/data/high_mass_diphoton/mass_points_data15_13TeV_"+selection+Form("_Eta%02d.txt", int(etaCut*10)));
    fout_data_nonEta=new ofstream("/afs/cern.ch/user/y/yanght/workarea/GG/xmlAnaWSBuilder/Input/data/high_mass_diphoton/mass_points_data15_13TeV_"+selection+Form("_nonEta%02d.txt", int(etaCut*10)));
  }
  int ndata_evt=cdata->GetEntries();
  for(int idata=0;idata<ndata_evt;idata++){
    cdata->GetEntry(idata);
    if(selection=="EKHI"){
      if(!(bool(isPassedExotic)&&bool(isPassedIsolationLowHighMyy))) continue;
    }
    else if(selection=="HKHI"){
      if(!bool(isPassedLowHighMyy)) continue;
    }
    else abort();

    if(option.Contains("3cat")){
      if(fabs(eta_s2->at(0))<etaCut&&fabs(eta_s2->at(1))<etaCut) hdata[0]->Fill(mass/GeV);
      else if(fabs(eta_s2->at(0))<etaCut||fabs(eta_s2->at(1))<etaCut) hdata[1]->Fill(mass/GeV);
      else hdata[2]->Fill(mass/GeV);
    }
    else{
      if(fabs(eta_s2->at(0))<etaCut&&fabs(eta_s2->at(1))<etaCut){
	hdata[0]->Fill(mass/GeV);
	if(produceDataPoints) *fout_data_Eta<<mass/GeV<<endl;
      }
      else{
	hdata[1]->Fill(mass/GeV);
	if(produceDataPoints) *fout_data_nonEta<<mass/GeV<<endl;
      }
    }
  }

  if(option.Contains("datapoint")){
    fout_data_Eta->close();
    fout_data_nonEta->close();
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
    if(option.Contains("3cat")){
      if(fabs(pBkg->eta_s2_1st)<etaCut&&fabs(pBkg->eta_s2_2nd)<etaCut) hbkg[0]->Fill(pBkg->m_yy/GeV, pBkg->vertexWeight*pBkg->crossSectionBRfilterEff/pBkg->totalEvents);
      else if(fabs(pBkg->eta_s2_1st)<etaCut||fabs(pBkg->eta_s2_2nd)<etaCut) hbkg[1]->Fill(pBkg->m_yy/GeV, pBkg->vertexWeight*pBkg->crossSectionBRfilterEff/pBkg->totalEvents);
      else hbkg[2]->Fill(pBkg->m_yy/GeV, pBkg->vertexWeight*pBkg->crossSectionBRfilterEff/pBkg->totalEvents);
    }
    else{
      if(fabs(pBkg->eta_s2_1st)<etaCut&&fabs(pBkg->eta_s2_2nd)<etaCut) hbkg[0]->Fill(pBkg->m_yy/GeV, pBkg->vertexWeight*pBkg->crossSectionBRfilterEff/pBkg->totalEvents);
      else hbkg[1]->Fill(pBkg->m_yy/GeV, pBkg->vertexWeight*pBkg->crossSectionBRfilterEff/pBkg->totalEvents);
    }
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
    csig->SetBranchAddress("EventInfoAuxDyn.runNumber",&runNumber);
    csig->SetBranchAddress("EventInfoAuxDyn.eventNumber",&eventNumber);
    
    csig->SetBranchAddress("HGamEventInfoAuxDyn.m_yy",&mass);
    csig->SetBranchAddress("HGamEventInfoAuxDyn.weight",&weight);
    
    csig->SetBranchAddress("HGamEventInfoAuxDyn.isDalitz",&isDalitz);
    csig->SetBranchAddress("HGamEventInfoAuxDyn.isPassedExotic",&isPassedExotic);
    csig->SetBranchAddress("HGamEventInfoAuxDyn.isPassedLowHighMyy",&isPassedLowHighMyy);
    csig->SetBranchAddress("HGamEventInfoAuxDyn.isPassedIsolationLowHighMyy",&isPassedIsolationLowHighMyy);

    csig->SetBranchAddress("HGamPhotonsAuxDyn.conversionType", &conversionType);
    csig->SetBranchAddress("HGamPhotonsAuxDyn.eta_s2", &eta_s2);
    for(int isig=0;isig<nsig_evt;isig++){
      csig->GetEntry(isig);

      if(selection=="HKHI"){
	if(!(bool(isPassedLowHighMyy)&&!bool(isDalitz))) continue;
      }
      else if(selection=="EKHI"){
	if(!(bool(isPassedExotic)&&bool(isPassedIsolationLowHighMyy)&&!bool(isDalitz))) continue;
      }
      if(option.Contains("3cat")){
	if(fabs(eta_s2->at(0))<etaCut&&fabs(eta_s2->at(1))<etaCut) hsig[0]->Fill(mass/GeV, weight);
	else if(fabs(eta_s2->at(0))<etaCut||fabs(eta_s2->at(1))<etaCut) hsig[1]->Fill(mass/GeV, weight);
	else hsig[2]->Fill(mass/GeV, weight);
      }
      else{
	if(fabs(eta_s2->at(0))<etaCut&&fabs(eta_s2->at(1))<etaCut) hsig[0]->Fill(mass/GeV, weight);
	else hsig[1]->Fill(mass/GeV, weight);
      }
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

      if(option.Contains("3cat")){
	if(fabs(pSig->etaS2_leading)<etaCut&&fabs(pSig->etaS2_subleading)<etaCut) hsig[0]->Fill(pSig->mgg, pSig->total_weight);
	else if(fabs(pSig->etaS2_leading)<etaCut||fabs(pSig->etaS2_subleading)<etaCut) hsig[1]->Fill(pSig->mgg, pSig->total_weight);
	else hsig[2]->Fill(pSig->mgg, pSig->total_weight);
      }
      else{
	if(fabs(pSig->etaS2_leading)<etaCut&&fabs(pSig->etaS2_subleading)<etaCut) hsig[0]->Fill(pSig->mgg, pSig->total_weight);
	else hsig[1]->Fill(pSig->mgg, pSig->total_weight);
      }
    }
  }
  double totalSig=0;
  for(int icat=0;icat<ncat; icat++) totalSig+=hsig[icat]->Integral();

  ofstream *fout_frac=NULL;
  if(produceFraction){
    fout_frac=new ofstream("Output/frac/"+selection+Form("/Eta%d_%s", int(etaCut*100), sigModel.Data()));
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
  TString outputFileName=outputDir+Form("/summary_%s_%.2f_%.4f", sigModel.Data(), etaCut, injectedNsig);
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
