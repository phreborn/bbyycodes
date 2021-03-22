#include "aux/plotter.h"
#include "aux/stats.h"
#include "aux/AtlasStyle.C"
#include "aux/AtlasLabels.C"

TGraphAsymmErrors MakePoissonErrors(TH1F hist, double scale, int rebin) {
  hist.Rebin(rebin);
 int npoint=0;
 for (int ibin = 0; ibin < hist.GetNbinsX() + 1; ibin++) {
   if(hist.GetBinContent(ibin)>0) npoint += 1;
 }

  cout << npoint << endl;
  TGraphAsymmErrors graph = TGraphAsymmErrors(npoint);
  graph.SetLineWidth(hist.GetLineWidth());
  graph.SetMarkerSize(hist.GetMarkerSize());
  int ipoint=0;
  for (int ibin = 0; ibin < hist.GetNbinsX() + 1; ibin++) {
    int bincontent=int(hist.GetBinContent(ibin));
    double EYlow=bincontent-0.5*TMath::ChisquareQuantile(0.1586555,2.*bincontent);
    double EYhigh=0.5*TMath::ChisquareQuantile(1-0.1586555,2.*(bincontent+1))-bincontent;
    //double EX=hist.GetBinWidth(ibin)/2.;
    double EX = 0;
    if(bincontent!=0){
      graph.SetPoint(ipoint,hist.GetBinCenter(ibin),bincontent/scale);
      graph.SetPointEXlow(ipoint,EX);
      graph.SetPointEXhigh(ipoint,EX);
      graph.SetPointEYlow(ipoint,EYlow/scale);
      graph.SetPointEYhigh(ipoint,EYhigh/scale);
      ipoint += 1;
    }
  }
 return graph;
}
  /*
 TGraphAsymmErrors graph = TGraphAsymmErrors(npoint)
 graph.SetLineWidth(hist.GetLineWidth())
 ipoint=0
 for ibin in range(0,hist.GetNbinsX()+1):
   bincontent=int(hist.GetBinContent(ibin))
   EYlow=bincontent-0.5*ROOT.TMath.ChisquareQuantile(0.1586555,2.*bincontent)
   EYhigh=0.5*ROOT.TMath.ChisquareQuantile(1-0.1586555,2.*(bincontent+1))-bincontent
   EX=hist.GetBinWidth(ibin)/2.
   if(bincontent!=0):
     graph.SetPoint(ipoint,hist.GetBinCenter(ibin),bincontent)
      
     graph.SetPointEXlow(ipoint,EX)
     graph.SetPointEXhigh(ipoint,EX)
     graph.SetPointEYlow(ipoint,EYlow)
     graph.SetPointEYhigh(ipoint,EYhigh)
     ipoint += 1

 return graph
*/


double find_max(TH1F * first, TH1F * second){
  double max_1 = first->GetMaximum();
  double max_2 = second->GetMaximum();
  if(max_1 >  max_2) return 1.2*max_1;
  else               return 1.2*max_2;
}

void plotter_yybb(TString region = "SM", TString s_test="test", TString MVA ="BDT_cat"){

  SetAtlasStyle();
  gStyle->SetErrorX(0);
  cout << region << endl;
  TString s_data, s_HH, s_HHBSM, s_yy, s_H;

  s_data = "/eos/atlas/unpledged/group-wisc/users/alwang/2021_02_07_h026_new_lumi/data.root";
  s_HH = "/eos/atlas/unpledged/group-wisc/users/alwang/2021_02_07_h026_new_lumi/PowhegH7/HHbbyy_cHHH01d0.root";
  s_HHBSM = "/eos/atlas/unpledged/group-wisc/users/alwang/2021_02_07_h026_new_lumi/PowhegH7/HHbbyy_cHHH10d0.root";
  s_yy = "/eos/atlas/unpledged/group-wisc/users/alwang/2021_02_07_h026_new_lumi/yy.root";
  s_H = "/eos/atlas/unpledged/group-wisc/users/alwang/2021_02_07_h026_new_lumi/singleH.root";

  TFile *f_data = TFile::Open(s_data);
  TFile *f_HH = TFile::Open(s_HH);
  TFile *f_HHBSM = TFile::Open(s_HHBSM);
  TFile *f_yy = TFile::Open(s_yy);
  TFile *f_H = TFile::Open(s_H);

  cout << "data: " << s_data << endl;
  cout << "HH: " << s_HH << endl;
  cout << "HHBSM: " << s_HHBSM << endl;
  cout << "yy: " << s_yy << endl;
  cout << "H: "  << s_H << endl;

  int n_bins = 100;
  TH1F* h_TI = new TH1F("h_TI", "h_TI", n_bins, 0, 1);
  TH1F* h_HH = new TH1F("h_HH",	"h_HH",	n_bins, 0,	1);
  TH1F* h_HHBSM = new TH1F("h_HHBSM",	"h_HHBSM",	n_bins, 0,	1);
  TH1F* h_yy = new TH1F("h_yy",	"h_yy",	n_bins, 0,	1);
  TH1F* h_H = new TH1F("h_H",	"h_H",	n_bins, 0,	1);

  TTree *t_data = (TTree*)f_data->Get("output");
  TTree *t_HH = (TTree*)f_HH->Get("output");
  TTree	*t_HHBSM =	(TTree*)f_HHBSM->Get("output");
  TTree	*t_yy =	(TTree*)f_yy->Get("output");
  TTree	*t_H =	(TTree*)f_H->Get("output");

  if (region == "SM") {
  t_data->Draw("yybb_nonRes_XGBoost_btag77_BCal_withTop_highMass_Score >> h_TI", "isPassed && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow==6 && N_bjet_fixed77 >= 2 && mass_yy > 105000 && mass_yy < 160000 && mass_yybb_bcal_mod > 350000");
  t_HH->Draw("yybb_nonRes_XGBoost_btag77_BCal_withTop_highMass_Score >> h_HH", "(eventNumber % 4 == 3 && isPassed && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow==6 && N_bjet_fixed77 >= 2 && mass_yy > 105000 && mass_yy < 160000 && mass_yybb_bcal_mod > 350000) * weight * 4");
  t_HHBSM->Draw("yybb_nonRes_XGBoost_btag77_BCal_withTop_highMass_Score >> h_HHBSM", "(eventNumber % 4 == 3 && isPassed && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow==6 && N_bjet_fixed77 >= 2 && mass_yy > 105000 && mass_yy < 160000 && mass_yybb_bcal_mod > 350000) * weight * 4");
  t_yy->Draw("yybb_nonRes_XGBoost_btag77_BCal_withTop_highMass_Score >> h_yy", "(eventNumber % 4 == 3 && isPassed && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow==6 && N_bjet_fixed77 >= 2 && mass_yy > 105000 && mass_yy < 160000 && mass_yybb_bcal_mod > 350000) * weight * 4");
  t_H->Draw("yybb_nonRes_XGBoost_btag77_BCal_withTop_highMass_Score >> h_H", "(eventNumber % 4 == 3 && isPassed && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow==6 && N_bjet_fixed77 >= 2 && mass_yy > 105000 && mass_yy < 160000 && mass_yybb_bcal_mod > 350000) * weight * 4");
  } else if (region == "BSM") {
  t_data->Draw("yybb_nonRes_XGBoost_btag77_BCal_withTop_lowMass_Score >> h_TI", "isPassed && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow==6 && N_bjet_fixed77 >= 2 && mass_yy > 105000 && mass_yy < 160000 && mass_yybb_bcal_mod < 350000");
  t_HH->Draw("yybb_nonRes_XGBoost_btag77_BCal_withTop_lowMass_Score >> h_HH", "(eventNumber % 4 == 3 && isPassed && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow==6 && N_bjet_fixed77 >= 2 && mass_yy > 105000 && mass_yy < 160000 && mass_yybb_bcal_mod < 350000) * weight * 4");
  t_HHBSM->Draw("yybb_nonRes_XGBoost_btag77_BCal_withTop_lowMass_Score >> h_HHBSM", "(eventNumber % 4 == 3 && isPassed && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow==6 && N_bjet_fixed77 >= 2 && mass_yy > 105000 && mass_yy < 160000 && mass_yybb_bcal_mod < 350000) * weight * 4");
  t_yy->Draw("yybb_nonRes_XGBoost_btag77_BCal_withTop_lowMass_Score >> h_yy", "(eventNumber % 4 == 3 && isPassed && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow==6 && N_bjet_fixed77 >= 2 && mass_yy > 105000 && mass_yy < 160000 && mass_yybb_bcal_mod < 350000) * weight * 4");
  t_H->Draw("yybb_nonRes_XGBoost_btag77_BCal_withTop_lowMass_Score >> h_H", "(eventNumber % 4 == 3 && isPassed && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow==6 && N_bjet_fixed77 >= 2 && mass_yy > 105000 && mass_yy < 160000 && mass_yybb_bcal_mod < 350000) * weight * 4");
  }
  cout << h_TI->Integral() << endl;
  cout << h_HH->Integral() << endl;
  cout << h_HHBSM->Integral() << endl;
  cout << h_yy->Integral() << endl;
  cout << h_H->Integral() << endl;
  TGraphAsymmErrors err_TI = MakePoissonErrors(*h_TI, h_TI->Integral(), 4);
  TGraphAsymmErrors errCopy_TI = MakePoissonErrors(*h_TI, h_TI->Integral(0.8 * n_bins, n_bins), 1);
  
  //normalize
  h_H->Scale(1/h_H->Integral() );
  h_TI->Scale(1/h_TI->Integral() );
  h_HH->Scale(1/h_HH->Integral() );
  h_HHBSM->Scale(1/h_HHBSM->Integral() );
  h_yy->Scale(1/h_yy->Integral() );

TColor *color1 = gROOT->GetColor(2); // dark pink
color1->SetRGB(242/255., 56/255., 90/255.);
TColor *color2 = gROOT->GetColor(3); // dark blue
color2->SetRGB(52/255., 56/255., 68/255.);
TColor *color3 = gROOT->GetColor(4); // medium turquoise
color3->SetRGB(54/255., 177/255., 191/255.);
TColor *color4 = gROOT->GetColor(7); // light turquoise
color4->SetRGB(74/255., 217/255., 217/255.);
TColor *color5 = gROOT->GetColor(6); // off white
color5->SetRGB(233/255., 241/255., 223/255.);
TColor *color6 = gROOT->GetColor(5); // dark yellow
color6->SetRGB(253/255., 197/255., 54/255.);


  h_TI->SetLineColor(1);
  h_TI->SetLineWidth(3);
  h_TI->SetMarkerSize(1.5);
  h_TI->SetMarkerColor(1);

  err_TI.SetLineWidth(3);
  err_TI.SetMarkerSize(1.5);

  h_HH->SetLineColor(2);
  h_HH->SetLineWidth(3);

  h_HHBSM->SetLineColor(4);
  h_HHBSM->SetLineWidth(3);

  h_yy->SetLineColor(3);
  h_yy->SetLineWidth(3);

  h_H->SetLineColor(5);
  h_H->SetLineWidth(3);

  TCanvas *c_1 = hist_1d(h_TI,1200,900);
  c_1->SetLeftMargin(0.15);


  //clone for subpanel
  TH1F* hCopy_TI = (TH1F*) h_TI->Clone();
  TH1F* hCopy_HH = (TH1F*) h_HH->Clone();
  TH1F* hCopy_HHBSM = (TH1F*) h_HHBSM->Clone();
  TH1F* hCopy_yy = (TH1F*) h_yy->Clone();
  TH1F* hCopy_H = (TH1F*) h_H->Clone();

  //renormalize to subpanel range (range from 0.8 - 1.0 with n_bins)
  hCopy_H->Scale(1/h_H->Integral(0.8 * n_bins, n_bins) );
  hCopy_TI->Scale(1/h_TI->Integral(0.8 * n_bins, n_bins) );
  hCopy_HH->Scale(1/h_HH->Integral(0.8 * n_bins, n_bins) );
  hCopy_HHBSM->Scale(1/h_HHBSM->Integral(0.8 * n_bins, n_bins) );
  hCopy_yy->Scale(1/h_yy->Integral(0.8 * n_bins, n_bins) );

  hCopy_TI->SetMarkerSize(1);
  hCopy_TI->SetLineWidth(2);
  hCopy_HH->SetLineWidth(2);
  hCopy_HHBSM->SetLineWidth(2);
  hCopy_yy->SetLineWidth(2);
  hCopy_H->SetLineWidth(2);

  errCopy_TI.SetLineWidth(2);
  errCopy_TI.SetMarkerSize(1);

  h_TI->Rebin(4);
  h_HH->Rebin(4);
  h_HHBSM->Rebin(4);
  h_yy->Rebin(4);
  h_H->Rebin(4);

  //h_TI->Draw("EPX0");
  h_TI->Draw("histPX0");
  h_HH->Draw("histsame");
  h_HHBSM->Draw("histsame");
  h_yy->Draw("histsame");
  h_H->Draw("histsame");
  err_TI.Draw("P0same");

  //category boundaries
  double boundary_1, boundary_2;

  if (region == "SM") {
  boundary_1 = 0.967;
  boundary_2 = 0.857;
  } else if (region == "BSM") {
  boundary_1 = 0.966;
  boundary_2 = 0.881;
  }
  //c_1->SetLogy();

  TPad cInsert("", "", 0.20, 0.38, 0.56, 0.73); 
  cInsert.Draw();
  cInsert.cd();
  hCopy_TI->Draw("histPX0");
  hCopy_HH->Draw("histsame");
  hCopy_HHBSM->Draw("histsame");
  hCopy_yy->Draw("histsame");
  hCopy_H->Draw("histsame");
  errCopy_TI.Draw("P0same");
  hCopy_TI->GetXaxis()->SetRangeUser(0.8, 1.0);
  hCopy_TI->GetYaxis()->SetRangeUser(0.001, find_max(hCopy_TI,hCopy_HH));
  hCopy_TI->GetXaxis()->SetLabelSize(0.07);
  hCopy_TI->GetYaxis()->SetLabelSize(0.07);
  hCopy_TI->GetXaxis()->SetNdivisions(-(5 + 4*100)); //default 10 + 40 * 100
  hCopy_TI->GetYaxis()->SetNdivisions(+(8 + 5*100));

  TLine *insertline = new TLine();
  insertline->SetLineStyle(2);
  insertline->SetLineColor(kBlack);
  insertline->SetLineWidth(1);
  insertline->DrawLine(boundary_1, 0, boundary_1, hCopy_TI->GetMaximum());
  insertline->DrawLine(boundary_2, 0, boundary_2, hCopy_TI->GetMaximum());

  c_1->cd();

  gPad->RedrawAxis();

  h_TI->GetYaxis()->SetRangeUser(0.001, find_max(h_TI,h_HH) );
  h_TI->GetYaxis()->SetTitleOffset(1.20);
  h_TI->GetYaxis()->SetTitle("Fraction of events / 0.04");
  h_TI->GetXaxis()->SetTitle("BDT Score");

  TLine *line1 = new TLine(boundary_1,0,boundary_1,h_TI->GetMaximum() * 0.5);
  line1->SetLineStyle(2);
  line1->SetLineColor(kBlack);
  line1->SetLineWidth(2);
  line1->Draw("same");

  TLine *line2 = new TLine(boundary_2,0,boundary_2,h_TI->GetMaximum() * 0.5);
  line2->SetLineStyle(2);
  line2->SetLineColor(kBlack);
  line2->SetLineWidth(2);
  line2->Draw("same");

  TLatex* Text1 = new TLatex(0.53,0.55,"#leftarrow Rejected events");
  Text1->SetNDC();
  Text1->SetTextSize(0.055);
  Text1->SetTextColor(kBlack);
//  Text1->Draw();

  TLatex* Text2 = new TLatex(0.58,0.6,"Selected events #rightarrow");
  Text2->SetNDC();
  Text2->SetTextSize(0.055);
  Text2->SetTextColor(kBlack);
//  Text2->Draw();

/* LOL
  TLine *tbar = new TLine(0.7435,0.843,0.7535,0.843);
  tbar->SetNDC();
  tbar->SetLineColor(kBlack);
  tbar->SetLineWidth(2);
  tbar->Draw("same");

  TLine *tbar2 = new TLine(0.6795,0.793,0.6895,0.793);
  tbar2->SetNDC();
  tbar2->SetLineColor(kBlack);
  tbar2->SetLineWidth(2);
  tbar2->Draw("same");
*/

  TLegend * leg_1 = leg(0.28, 0.45, 0.040, 1.50); //0.33 0.60 0.040
  leg_1->AddEntry(h_HH, "HH ggF, #kappa_{#lambda}=1", "L");
  leg_1->AddEntry(h_HHBSM,"HH ggF, #kappa_{#lambda}=10", "L");
  leg_1->AddEntry(h_H,"Single H","L");
  leg_1->AddEntry(h_yy,"#gamma#gamma+jets", "L");
  leg_1->AddEntry(h_TI,"Data","EP");
  leg_1->SetBorderSize(0);
  leg_1->Draw();



  double x_loc = 0.20; double y_loc = 0.80;
  double t_size = 0.05;
  TLatex * l_fit = caption_fit(t_size);
  ATLASLabel(x_loc,y_loc+0.05,"Internal",t_size,0.13);
  l_fit->DrawLatex(x_loc,y_loc, "#sqrt{s} = 13 TeV, 139 fb^{-1}" );
  if (region == "SM") {
  l_fit->DrawLatex(x_loc,y_loc-0.05, "High mass region" );
  Save_canvas(c_1, "yybb_highMass_Score");
  } else if (region == "BSM") {
  l_fit->DrawLatex(x_loc,y_loc-0.05, "Low mass region" );
  Save_canvas(c_1, "yybb_lowMass_Score");
  }
  return;
}
