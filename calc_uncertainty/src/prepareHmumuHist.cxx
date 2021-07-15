#include "CommonHead.h"
#include "CommonFunc.h"
#include "statistics.hh"
#include "DiMuonNtuple.h"
#include "DiMuonNtuple.C"

using namespace std;

int main(int argc, char** argv){
  map<int, double> XS;

  XS[343982] =  7.7460E-01*  1.0  *          4.7221E-03;  
  XS[343983] =  1.1975E-01*  1.0  *          3.3691E-02;  
  XS[343984] =  3.9798E-02*  1.0  *          1.5006E-01;  
  XS[343985] =  1.1642E-02*  1.0  *          3.1660E-01;  
  XS[343986] =  5.0322E-03*  1.0  *          5.2206E-01;  
  XS[363123] =  1.7151E+00*  1.141*          8.3180E-01;  
  XS[363124] =  1.7154E+00*  1.141*          1.0870E-01;  
  XS[363125] =  1.7156E+00*  1.141*          5.9371E-02;  
  XS[363126] =  8.4562E-02*  1.141*          7.1889E-01;  
  XS[363127] =  8.4577E-02*  1.141*          1.7413E-01;  
  XS[363128] =  8.4753E-02*  1.141*          1.0833E-01;  
  XS[363129] =  3.5892E-02*  1.141*          6.7454E-01;  
  XS[363130] =  3.5883E-02*  1.141*          2.0018E-01;  
  XS[363131] =  3.5893E-02*  1.141*          1.2629E-01;  
  XS[363132] =  8.1918E-03*  1.141*          6.2858E-01;  
  XS[363133] =  8.1826E-03*  1.141*          2.2872E-01;  
  XS[363134] =  8.1699E-03*  1.141*          1.4309E-01;  
  XS[363135] =  1.2715E-03*  1.141*          5.9694E-01;  
  XS[363136] =  1.2678E-03*  1.141*          2.4947E-01;  
  XS[363137] =  1.2682E-03*  1.141*          1.5301E-01;  
  XS[363138] =  4.4224E-04*  1.141*          5.7158E-01;  
  XS[363139] =  4.4517E-04*  1.141*          2.6385E-01;  
  XS[363140] =  4.4382E-04*  1.141*          1.6212E-01;  
  XS[363141] =  1.4721E-04*  1.141*          5.5401E-01;  
  XS[363142] =  1.4715E-04*  1.141*          2.7780E-01;  
  XS[363143] =  1.4758E-04*  1.141*          1.7062E-01;  
  XS[363144] =  5.4993E-06*  1.141*          5.3785E-01;  
  XS[363145] =  5.5276E-06*  1.141*          2.9076E-01;

  TString inputFileName=argv[1];
  TString outputFileName=argv[2];

  cout<<inputFileName<<" "<<outputFileName<<endl;
  const int ncategory=8;	// ICHEP categorization
  
  TChain *t=CommonFunc::MakeChain("DiMuonNtuple", inputFileName, inputFileName+".bdf", inputFileName.Contains(".root"));
  
  DiMuonNtuple *p=new DiMuonNtuple(t);

  long int nevt=p->fChain->GetEntries();

  TFile *f=TFile::Open(outputFileName, "recreate");
  TH1D *bkgHist[ncategory];
  for(int icat=0; icat<ncategory; icat++)
    bkgHist[icat]=CommonFunc::CreateTH1D(Form("bkgHist_%d", icat), "bkgHist", "m_{#mu#mu}", "Event", 500, 110, 160);

  TString currentFileName="";
  double totalEvent=0;
  double luminosity=0;
  
  for(long int ievt=0;ievt<nevt;ievt++){
    cout<<ievt/double(nevt)*100<<"\r"<<flush;
    p->fChain->GetEntry(ievt);
    if(currentFileName!=TString(p->fChain->GetCurrentFile()->GetName())){
      TFile *fNtup=p->fChain->GetCurrentFile();
      assert(fNtup);
      currentFileName=fNtup->GetName();
      cout<<Form("ProcessedEntries_%d",p->EventInfo_ChannelNumber)<<" "<<fNtup<<" "<<fNtup->GetName()<<" "<<XS[p->EventInfo_ChannelNumber]<<endl;      
      TH1 *histNtup=(TH1*)fNtup->Get(Form("ProcessedEntries_%d",p->EventInfo_ChannelNumber));
      assert(histNtup);
      totalEvent=histNtup->GetBinContent(2);
      assert(totalEvent>0);
    }
    bool sherpa_cut = (fabs(p->EventWeight_MCEventWeight) < 2000);
    bool ss_cut = (p->Muons_Charge_Lead * p->Muons_Charge_Sub < 0);
    bool old_analysis_cut = (fabs(p->Muons_Eta_Lead) <= 2.5 && fabs(p->Muons_Eta_Sub) <= 2.5 && p->Muons_PT_Sub > 15);
    if(!ss_cut || !old_analysis_cut) continue;
    if(p->Muons_Minv_MuMu>160||p->Muons_Minv_MuMu<110) continue;
    if(p->PostVBF_xsecwTrue_evtwTrue_MG_nsig0_nbkg0_sigw1_mc16all_ntrees200_bagfrac0_5_btypeGrad_v14_3>0.8853) p->Event_OldCategory=8;
    else if(p->PostVBF_xsecwTrue_evtwTrue_MG_nsig0_nbkg0_sigw1_mc16all_ntrees200_bagfrac0_5_btypeGrad_v14_3>0.6845) p->Event_OldCategory=7;
    double weight=p->TotalWeight*XS[p->EventInfo_ChannelNumber]/totalEvent;
    if(currentFileName.Contains("mc16a")) luminosity=36.2e6;
    if(currentFileName.Contains("mc16d")) luminosity=43.6e6;
    // cout<<p->TotalWeight<<" "<<XS[p->EventInfo_ChannelNumber]<<" "<<histNtup->Integral()<<endl;
    bkgHist[p->Event_OldCategory-1]->Fill(p->Muons_Minv_MuMu, weight*luminosity);
  }

  f->cd();
  for(int icat=0; icat<ncategory; icat++) bkgHist[icat]->Write();
  f->Close();
}
