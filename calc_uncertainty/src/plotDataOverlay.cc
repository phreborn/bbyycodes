#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"
#include "statistics.hh"

using namespace std;
using namespace RooFit;
using namespace RooStats;
using namespace CommonFunc;

int main( int argc, char** argv ){
  if( argc<5 ){
    cout<<"Usage: "<<argv[0]<<" <input_file 1> <input file 2> <output_file> <selection>"<<endl;
    exit(0);
  }
  SetAtlasStyle();

  vector<TString> inputArgOld=SplitString(argv[1],',');
  vector<TString> inputArgNew=SplitString(argv[2],',');
  
  TString inputFileNameOld=inputArgOld[0], oldTitle=inputArgOld[1];
  TString inputFileNameNew=inputArgNew[0], newTitle=inputArgNew[1];

  TString outputFileName=argv[3];
  TString selection=argv[4];

  TString option=argv[5];
  
  ifstream fin1(inputFileNameOld);
  ifstream fin2(inputFileNameNew);

  double xmin=0, xmax=0;
  double binw=20;
  if(selection=="scalar"){
    xmin=160, xmax=2000;
  }
  else if(selection=="graviton"){
    xmin=200, xmax=2000;
  }

  if(option.Contains("zoom")){
    xmin=700,xmax=800,binw=5;
    outputFileName+="_zoom";
  }
  
  const int Nbins=(xmax-xmin)/binw;
  
  TH1D* hdata1 = new TH1D("hdata1","hdata1",Nbins,xmin,xmax);
  hdata1->Sumw2();
  hdata1->SetLineColor(kRed);
  hdata1->SetMarkerColor(kRed);
  hdata1->SetMarkerStyle(26);
  hdata1->SetLineWidth(2);
  
  TH1D* hdata2 = new TH1D("hdata2","hdata2",Nbins,xmin,xmax);
  hdata2->Sumw2();
  hdata2->SetLineColor(kBlue);
  hdata2->SetMarkerColor(kBlue);
  hdata2->SetMarkerStyle(32);
  hdata2->SetLineWidth(2);

  if(option.Contains("zoom")){
    hdata1->SetLineWidth(1);
    hdata1->SetFillColor(kRed);
    hdata1->SetFillStyle(3335);
    
    hdata2->SetLineWidth(1);
    hdata2->SetFillColor(kBlue);
    hdata2->SetFillStyle(3353);
  }
  
  double mass;
  hdata1->GetYaxis()->SetTitle(Form("Events / %.0f GeV", binw));
  while((fin1>>mass)) hdata1->Fill(mass);
  while((fin2>>mass)) hdata2->Fill(mass);

  fin1.close();
  fin2.close();
  for(int ibin=1;ibin<=Nbins;ibin++){
    hdata1->SetBinError(ibin, 0);
    hdata2->SetBinError(ibin, 0);
  }
  
  TLegend* lg = new TLegend(0.6,0.7,0.9,0.9);
  lg->SetLineColor(0);
  lg->SetFillColor(0);
  lg->SetFillStyle(0);
  lg->SetShadowColor(0);

  if(option.Contains("zoom")){
    lg->AddEntry(hdata1, oldTitle,"F");
    lg->AddEntry(hdata2, newTitle,"F");
  }
  else{
    lg->AddEntry(hdata1, oldTitle,"L");
    lg->AddEntry(hdata2, newTitle,"L");
  }

  TCanvas* c1 = new TCanvas("c1","c1",800,800);
  c1->cd();

  TPad *pad1 =  new TPad("pad1","pad1name",0.01,0.40,0.99,0.99);
  TPad *pad2 =  new TPad("pad2","pad2name",0.01,0.05,0.99,0.402);
  pad1->Draw();
  pad2->Draw();

  pad1->SetBottomMargin(0.);
  pad1->cd();
  if(!option.Contains("zoom")) pad1->SetLogy();
  pad1->SetGrid();
  
  hdata1->Draw("hist");
  // hdata1->Draw("same,P");
  hdata2->Draw("same,hist");
  // hdata2->Draw("same,P");
  lg->Draw("same");

  TH1D* h0 = new TH1D("h0","h0",Nbins,xmin,xmax);
  h0->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
  h0->GetYaxis()->SetTitle(newTitle+"-"+oldTitle);
  h0->GetYaxis()->SetTitleSize(0.075);
  h0->GetYaxis()->SetTitleOffset(0.80);
  h0->GetYaxis()->SetLabelSize(0.075);
  h0->GetXaxis()->SetTitleSize(0.075);
  h0->GetXaxis()->SetTitleOffset(0.9);
  h0->GetXaxis()->SetLabelSize(0.075);
  h0->GetYaxis()->SetRangeUser(-1.5,4.5);
  h0->SetLineWidth(2);
  pad2->SetGrid();

  h0->Add(hdata2);
  h0->Add(hdata1,-1);

  pad2->SetTopMargin(0.);
  pad2->cd();
  h0->Draw("hist");

  PrintCanvas(c1, outputFileName);
  cout<<hdata1->Integral()<<" "<<hdata2->Integral()<<endl;
  return 0;
}
