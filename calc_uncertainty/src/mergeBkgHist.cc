#include "CommonHead.h"
#include "CommonFunc.h"

using namespace std;
using namespace CommonFunc;

int main(int argc, char** argv){
  // TString ggTemplate="Output/optimization/EKHI_inclusive_norm_input/summary_scalar_0.00_30.1212.root";
  // TString gjTemplate="Input/template/gamjet_cong/Liron_use_inclusive_20.1/spin2/yj/pdfLoosep.root";
  // TString jgTemplate="Input/template/gamjet_cong/Liron_use_inclusive_20.1/spin2/jy/pdfLoosep.root";
  // TString jjTemplate="Input/template/gamjet_cong/Liron_use_inclusive_20.1/spin2/jj/pdfLoosep.root";

  TString ggTemplate=argv[1];
  TString gjTemplate=argv[2];
  TString jgTemplate=argv[3];
  TString jjTemplate=argv[4];

  TFile *ggTempFile=TFile::Open(ggTemplate);
  TFile *gjTempFile=TFile::Open(gjTemplate);
  TFile *jgTempFile=TFile::Open(jgTemplate);
  TFile *jjTempFile=TFile::Open(jjTemplate);

  TH1D *ggTempHist=(TH1D*)ggTempFile->Get(argv[5]);
  TH1F *gjTempHist_tmp=(TH1F*)gjTempFile->Get(argv[6]);
  TH1F *jgTempHist_tmp=(TH1F*)jgTempFile->Get(argv[7]);
  TH1F *jjTempHist_tmp=(TH1F*)jjTempFile->Get(argv[8]);

  TString dataHistName=ggTempHist->GetName(); dataHistName.ReplaceAll("bkg","data");
  TString sigHistName=ggTempHist->GetName(); sigHistName.ReplaceAll("bkg","sig");

  TH1D *hdata=(TH1D*)ggTempFile->Get(dataHistName);
  TH1D *hsig=(TH1D*)ggTempFile->Get(sigHistName);
  
  cout<<"okay 1"<<endl;
  cout<<gjTempHist_tmp<<" "<<jgTempHist_tmp<<" "<<jjTempHist_tmp<<endl;
  gjTempHist_tmp->Print();
  jgTempHist_tmp->Print();
  jjTempHist_tmp->Print();
  
  TH1D *gjTempHist=TH1FtoTH1D(gjTempHist_tmp);
  TH1D *jgTempHist=TH1FtoTH1D(jgTempHist_tmp);
  TH1D *jjTempHist=TH1FtoTH1D(jjTempHist_tmp);
  cout<<"okay 2"<<endl;
  TString outputFileName=argv[9];

  TFile *fout=TFile::Open(outputFileName,"recreate");

  TH1D *hout=(TH1D*)ggTempHist->Clone();
  hout->Reset();

  gjTempHist=ExpandTH1D(gjTempHist, hout->GetXaxis()->GetXmin(), hout->GetXaxis()->GetXmax());
  jgTempHist=ExpandTH1D(jgTempHist, hout->GetXaxis()->GetXmin(), hout->GetXaxis()->GetXmax());
  jjTempHist=ExpandTH1D(jjTempHist, hout->GetXaxis()->GetXmin(), hout->GetXaxis()->GetXmax());

  gjTempHist->Rebin(gjTempHist->GetNbinsX()/hout->GetNbinsX());
  jgTempHist->Rebin(jgTempHist->GetNbinsX()/hout->GetNbinsX());
  jjTempHist->Rebin(jjTempHist->GetNbinsX()/hout->GetNbinsX());

  double norm=ggTempHist->Integral();
  ScaleTo(ggTempHist, 0.935*norm);
  ScaleTo(gjTempHist, 0.041*norm);
  ScaleTo(jgTempHist, 0.021*norm);
  ScaleTo(jjTempHist, 0.003*norm);

  hout->Add(ggTempHist);
  hout->Add(gjTempHist);
  hout->Add(jgTempHist);
  hout->Add(jjTempHist);
  
  fout->cd();
  hout->Write();
  hdata->Write();
  hsig->Write();
  fout->Close();
}
