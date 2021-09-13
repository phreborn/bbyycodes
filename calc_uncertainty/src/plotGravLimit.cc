#include "CommonHead.h"
#include "CommonFunc.h"

using namespace std;

void set_palette(TString name="palette", int ncontours=999){
  double stops[5] = {0};
  double red[5] = {0};
  double green[5] = {0};
  double blue[5] = {0};
  if (name.Contains("gray")){
    stops[0] = 0.00; stops[1] = 0.34; stops[2] = 0.61; stops[3] = 0.84; stops[4] = 1.00;
    red[0] = 1.00; red[1] = 0.84; red[2] = 0.61; red[3] = 0.34; red[4] = 0.00;
    green[0] = 1.00; green[1] = 0.84; green[2] = 0.61; green[3] = 0.34; green[4] = 0.00;
    blue[0] = 1.00; blue[1] = 0.84; blue[2] = 0.61; blue[3] = 0.34; blue[4] = 0.00;
  }
  else{
    stops[0] = 0.00; stops[1] = 0.34; stops[2] = 0.61; stops[3] = 0.84; stops[4] = 1.00;
    red[0] = 0.00; red[1] = 0.00; red[2] = 0.87; red[3] = 1.00; red[4] = 0.51;
    green[0] = 0.00; green[1] = 0.81; green[2] = 1.00; green[3] = 0.20; green[4] = 0.00;
    blue[0] = 0.51; blue[1] = 1.00; blue[2] = 0.12; blue[3] = 0.00; blue[4] = 0.00;
  }

  int npoints = 5;
  TColor::CreateGradientColorTable(npoints, stops, red, green, blue, ncontours);
  gStyle->SetNumberContours(ncontours);
}

int main(int argc, char**argv){
  TString jobname=argv[0];
  TString option=argv[1];
  set_palette();

  //string prefix = "/tmp/fwang/high_mass_diphoton_Graviton_13TeV_histfactory_limit";
  string prefix = "high_mass_diphoton_Graviton_13TeV_histfactory_EKEI_v3_2dlimit_binned/";
  vector<double> coup = {0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.10,0.11,0.12,0.13,0.14,0.15,
			 0.16,0.17,0.18,0.19,0.20,0.21,0.22,0.23,0.24,0.25,0.26,0.27,0.28,0.29,0.30};
  TGraph2D* g = new TGraph2D();

  ifstream input;
  string dummy;
  double obslim;
  double explim;
  int ipoint = 0;
  for( double m=500; m<=3500; m+=10 ){
    for( auto c: coup ){
      //TString filename = Form("%s/high_mass_diphoton_Graviton_13TeV_histfactory_limit_%.2f_%.2f.txt",prefix.c_str(),m,c);
      TString filename = Form("%s/%s_%.2f_%.2f.txt",prefix.c_str(),prefix.c_str(),m,c);
      input.open(filename.Data());
	    
      if( !input.is_open() ) continue;
      input>>dummy>>obslim>>explim;
      input.close();
      //g->SetPoint(ipoint,m,c,obslim);
      g->SetPoint(ipoint,m,c,explim);
      ipoint++;
    }
  }

  TCanvas* c1 = new TCanvas();
  c1->cd();
  c1->SetLogx();
  c1->SetLogz();
  gPad->SetRightMargin(0.18);

  int bins = 400;
  TH2D* h_tmp= g->GetHistogram();
  TH2D* h_int = new TH2D("h_int","",bins,h_tmp->GetXaxis()->GetXmin(),h_tmp->GetXaxis()->GetXmax(),bins,h_tmp->GetYaxis()->GetXmin(),h_tmp->GetYaxis()->GetXmax());
  //TH2D* h_int = new TH2D("h_int","",bins,400,1600,bins,h_tmp->GetYaxis()->GetXmin(),h_tmp->GetYaxis()->GetXmax());
  h_int->GetXaxis()->SetTitle("m_{G*} [GeV]");
  h_int->GetYaxis()->SetTitle("#kappa/#bar{M}_{Pl}");
  //h_int->SetZTitle("95\%CL upper limit on #sigma_{obs} [fb]");
  h_int->SetZTitle("95\%CL upper limit on #sigma_{exp} [fb]");
  h_int->GetZaxis()->SetTitleOffset(1.2);

  g->SetHistogram(h_int);
  g->Draw("colz");
  h_int = g->GetHistogram();

  h_int->GetXaxis()->SetNdivisions(5);
  h_int->Draw("colz");
  TLatex l;
  l.SetNDC(kFALSE);
  l.DrawLatex(455,-0.013,"5#times10^{2}");
  l.DrawLatex(1825,-0.013,"2#times10^{3}");

  CommonFunc::PrintCanvas(c,"fig");
}
