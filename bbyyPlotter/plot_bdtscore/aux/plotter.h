#include <string>
#include "TCanvas.h"
#include "TLegend.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TSystem.h"
#include "TStyle.h"

RooPlot* roo_plot_frame(RooRealVar x){
  RooPlot* xframe = x.frame() ;
  xframe->GetYaxis()->SetTitleOffset( 1.5 );
  xframe->SetLineColor(1);
  xframe->SetMarkerSize(0.8);
  xframe->GetYaxis()->SetTitleSize(30);
  xframe->GetYaxis()->SetTitleFont(43);
  xframe->GetYaxis()->SetTitleOffset(1.5);
  xframe->GetYaxis()->SetLabelSize(0.05);
  xframe->GetXaxis()->SetLabelSize(0);
  xframe->GetXaxis()->SetLabelOffset(999);
  return xframe;
}

RooPlot* roo_plot_only(RooRealVar x){
  RooPlot* xframe = x.frame() ;
  xframe->SetLineColor(1);
  xframe->SetMarkerSize(0.8);

  xframe->GetYaxis()->SetTitleOffset( 1.5 );
  xframe->GetYaxis()->SetTitleSize(40);
  xframe->GetYaxis()->SetTitleFont(43);
  xframe->GetYaxis()->SetTitleOffset(1.5);
  xframe->GetYaxis()->SetLabelSize(0.05);

  xframe->GetXaxis()->SetTitleSize(40);
  xframe->GetXaxis()->SetTitleFont(43);
  xframe->GetXaxis()->SetTitleOffset(1.5);
  xframe->GetXaxis()->SetLabelSize(0.05);
  return xframe;
}

TCanvas *format_c(){
  double w = 1000; double h = 1000;
  TCanvas *can_1 = new TCanvas("can_1","can_1");
  can_1->SetCanvasSize(w,h);
  return can_1;
}

TCanvas *data_fit(TH1 *significance){
  double w = 1000; double h = 1000;
  TCanvas *can_1 = new TCanvas("can_1","can_1");
  can_1->SetCanvasSize(w,h);
  can_1->Divide(1,2);
  can_1->GetPad(1)->SetPad(0,0.30,1,1.);
  can_1->GetPad(2)->SetPad(0,0,1,0.3);
  can_1->GetPad(2)->SetGridy();
  can_1->GetPad(1)->SetBottomMargin(0.025);
  can_1->GetPad(2)->SetTopMargin(0.035);
  can_1->GetPad(2)->SetBottomMargin(0.31);

  significance->GetYaxis()->SetTitleSize(30.0);
  significance->GetYaxis()->SetTitleFont(43);
  significance->GetYaxis()->SetTitleOffset(1.1);
  significance->GetYaxis()->SetLabelSize(0.10);
  significance->GetYaxis()->SetNdivisions(5);

  significance->GetXaxis()->SetTitleSize(30);
  significance->GetXaxis()->SetTitleFont(43);
  significance->GetXaxis()->SetTitleOffset(3.3);
  significance->GetXaxis()->SetLabelSize(30);
  significance->GetXaxis()->SetLabelFont(43);
  significance->SetTitle("");

  return can_1;
}
TCanvas *tgraph_2d(TGraphErrors * data){
  double w = 600; double h = 600;
  TCanvas *can_1 = new TCanvas("can_1","can_1");
  can_1->SetCanvasSize(w,h);

  data->GetYaxis()->SetTitleSize(25);
  data->GetYaxis()->SetTitleFont(43);
  data->GetYaxis()->SetTitleOffset(1.0);
  data->GetYaxis()->SetLabelSize(0.04);

  data->GetXaxis()->SetTitleSize(30);
  data->GetXaxis()->SetTitleFont(43);
  data->GetXaxis()->SetTitleOffset(0.8);
  data->GetXaxis()->SetLabelSize(0.04);

  return can_1;
}

TCanvas *tgraph_2d(TGraphAsymmErrors * data){
  double w = 1000; double h = 1000;
  TCanvas *can_1 = new TCanvas("can_1","can_1");
  //can_1->SetCanvasSize(w,h);

  data->GetYaxis()->SetTitleSize(20);
  data->GetYaxis()->SetTitleFont(43);
  data->GetYaxis()->SetTitleOffset(1.2);
  data->GetYaxis()->SetLabelSize(0.04);

  data->GetXaxis()->SetTitleSize(20);
  data->GetXaxis()->SetTitleFont(43);
  data->GetXaxis()->SetTitleOffset(1.2);
  data->GetXaxis()->SetLabelSize(0.04);

  return can_1;
}

TCanvas *hist_2d(TH2F * data){
  double w = 1000; double h = 1000;
  TCanvas *can_1 = new TCanvas("can_1","can_1");
  gStyle->SetPalette(55,0);
  can_1->SetCanvasSize(w,h);
  data->GetZaxis()->SetTitleSize(40);
  data->GetZaxis()->SetTitleFont(43);
  data->GetZaxis()->SetTitleOffset(1.2);
  data->GetZaxis()->SetLabelSize(0.04);

  data->GetYaxis()->SetTitleSize(40);
  data->GetYaxis()->SetTitleFont(43);
  data->GetYaxis()->SetTitleOffset(1.2);
  data->GetYaxis()->SetLabelSize(0.04);

  data->GetXaxis()->SetTitleSize(40);
  data->GetXaxis()->SetTitleFont(43);
  data->GetXaxis()->SetTitleOffset(1.2);
  data->GetXaxis()->SetLabelSize(0.04);

  return can_1;
}
TCanvas *hist_1d(TH1F * data, double w = 1000, double h = 1000){

  TCanvas *can_1 = new TCanvas("can_1","can_1");

  can_1->SetCanvasSize(w,h);

  data->GetYaxis()->SetTitleSize(40);
  data->GetYaxis()->SetTitleFont(43);
  data->GetYaxis()->SetTitleOffset(0.8);
  data->GetYaxis()->SetLabelSize(0.04);

  data->GetXaxis()->SetTitleSize(40);
  data->GetXaxis()->SetTitleFont(43);
  data->GetXaxis()->SetTitleOffset(1.2);
  data->GetXaxis()->SetLabelSize(0.04);

  return can_1;
}
TCanvas *hist_1d(TH1F * data, TH1F* data_2, TH1F* data_3){
  double w = 1000; double h = 1000;
  TCanvas *can_1 = new TCanvas("can_1","can_1");

  can_1->SetCanvasSize(w,h);

  data->GetYaxis()->SetTitleSize(40);
  data->GetYaxis()->SetTitleFont(43);
  data->GetYaxis()->SetTitleOffset(1.2);
  data->GetYaxis()->SetLabelSize(0.04);
  
  data->GetXaxis()->SetTitleSize(40);
  data->GetXaxis()->SetTitleFont(43);
  data->GetXaxis()->SetTitleOffset(1.2);
  data->GetXaxis()->SetLabelSize(0.04);
  
  data_2->GetYaxis()->SetTitleSize(40);
  data_2->GetYaxis()->SetTitleFont(43);
  data_2->GetYaxis()->SetTitleOffset(0.8);
  data_2->GetYaxis()->SetLabelSize(0.04);

  data_2->GetXaxis()->SetTitleSize(40);
  data_2->GetXaxis()->SetTitleFont(43);
  data_2->GetXaxis()->SetTitleOffset(1.2);
  data_2->GetXaxis()->SetLabelSize(0.04);

  data_3->GetYaxis()->SetTitleSize(40);
  data_3->GetYaxis()->SetTitleFont(43);
  data_3->GetYaxis()->SetTitleOffset(0.8);
  data_3->GetYaxis()->SetLabelSize(0.04);

  data_3->GetXaxis()->SetTitleSize(40);
  data_3->GetXaxis()->SetTitleFont(43);
  data_3->GetXaxis()->SetTitleOffset(1.2);
  data_3->GetXaxis()->SetLabelSize(0.04);
  return can_1;
}
TCanvas *data_mc_ratios(TH1F * data, TH1F *mc, TH1F *ratio){
  double w = 1000; double h = 1000;
  TCanvas *can_1 = new TCanvas("can_1","can_1");
  //can_1->SetCanvasSize(w,h);
  can_1->Divide(1,2);
  can_1->GetPad(1)->SetPad(0,0.30,1,1.);
  can_1->GetPad(2)->SetPad(0,0,1,0.3);
  can_1->GetPad(2)->SetGridy();
  can_1->GetPad(1)->SetBottomMargin(0.025);
  can_1->GetPad(2)->SetTopMargin(0.035);
  can_1->GetPad(2)->SetBottomMargin(0.31);

  data->SetLineColor(1);
  data->SetMarkerSize(0.8);
  data->GetYaxis()->SetTitleSize(20);
  data->GetYaxis()->SetTitleFont(43);
  data->GetYaxis()->SetTitleOffset(1.2);
  data->GetYaxis()->SetLabelSize(0.06);
  data->GetXaxis()->SetLabelSize(0);
  data->GetXaxis()->SetLabelOffset(999);

  double color = 2;//2=red
  mc->SetLineColor(color);
  mc->SetFillColor(color);
  mc->SetMarkerSize(0.8);
  mc->SetMarkerColor(color);
  mc->SetMarkerStyle(32);

  ratio->SetMarkerSize(0.8);
  ratio->GetYaxis()->SetTitleSize(20);
  ratio->GetYaxis()->SetTitleFont(43);
  ratio->GetYaxis()->SetTitleOffset(1.0);
  ratio->GetYaxis()->SetLabelSize(0.13);
  ratio->GetYaxis()->SetNdivisions(6);

  ratio->GetXaxis()->SetTitleSize(20);
  ratio->GetXaxis()->SetTitleFont(43);
  ratio->GetXaxis()->SetTitleOffset(2.5);
  ratio->GetXaxis()->SetLabelSize(20);
  ratio->GetXaxis()->SetLabelFont(43);
  ratio->SetTitle("");

  return can_1;
}
TLegend* leg_define(double x1, double y1){
  double x2 = x1+0.1; double y2 = y1+0.10;
  TLegend * t_leg = new TLegend(x1,y1-0.1,x2,y2);
  t_leg->SetLineColor(0);
  t_leg->SetTextSize(0.04);
  t_leg->SetShadowColor(0);
  t_leg->SetFillStyle(0);
  t_leg->SetFillColor(0);

  return t_leg;
}
TLegend* leg_2d(){
  double x_loc = 0.28; double y_loc = 0.60;
  double x1 = x_loc+0.28; double y1 = 0.625;
  double x2 = x_loc+0.52; double y2 = 0.625+0.1;
  TLegend * t_leg = new TLegend(x1-0.1,y1-0.4,x2-0.1,y2-0.4);
  t_leg->SetLineColor(0);
  t_leg->SetTextSize(0.04);
  t_leg->SetShadowColor(0);
  t_leg->SetFillStyle(0);
  t_leg->SetFillColor(0);

  return t_leg;
}
TLegend* leg_left(){
  double x_loc = 0.28; double y_loc = 0.60;
  double x1 = x_loc-0.14; double y1 = y_loc+0.15;
  double x2 = x_loc+0.10; double y2 = y_loc+0.3;
  TLegend * t_leg = new TLegend(x1,y1,x2,y2);
  t_leg->SetLineColor(0);
  t_leg->SetTextSize(0.05);
  t_leg->SetShadowColor(0);
  t_leg->SetFillStyle(0);
  t_leg->SetFillColor(0);

  return t_leg;
}
TLegend* leg_bottom(double shift){
  double x_loc = 0.28; double y_loc = 0.60;
  double x1 = x_loc-0.15; double y1 = y_loc+0.2-shift;
  double x2 = x_loc+0.05; double y2 = y_loc+0.3-shift;
  TLegend * t_leg = new TLegend(x1,y1,x2,y2);
  t_leg->SetLineColor(0);
  t_leg->SetTextSize(0.035);
  t_leg->SetShadowColor(0);
  t_leg->SetFillStyle(0);
  t_leg->SetFillColor(0);

  return t_leg;
}
TLegend* leg_trigger(double shift){
  double x_loc = 0.28; double y_loc = 0.60;
  double x1 = x_loc+0.15; double y1 = y_loc+0.2-shift;
  double x2 = x_loc+0.40; double y2 = y_loc+0.5-shift;
  TLegend * t_leg = new TLegend(x1,y1,x2,y2);
  t_leg->SetLineColor(0);
  t_leg->SetTextSize(0.025);
  t_leg->SetShadowColor(0);
  t_leg->SetFillStyle(0);
  t_leg->SetFillColor(0);

  return t_leg;
}
TLegend* leg(double x_loc = 0.28, double y_loc = 0.60, double t_size = 0.05, double scale = 1.0){
  double x1 = x_loc+0.28; double y1 = y_loc+0.15;
  double x2 = x_loc+0.52*scale; double y2 = y_loc+0.3*scale;
  TLegend * t_leg = new TLegend(x1,y1,x2,y2);
  t_leg->SetLineColor(0);
  t_leg->SetTextSize(t_size);
  t_leg->SetShadowColor(0);
  t_leg->SetFillStyle(0);
  t_leg->SetFillColor(0);

  return t_leg;
}
void Save_canvas_temp(TCanvas * can, TString name){
  gSystem->Exec("mkdir pdf_files/");
  can->SaveAs("pdf_files/"+name+".pdf");
  return;
}

void Save_canvas(TCanvas * can, TString name){
  gSystem->Exec("mkdir eps_files/");
  gSystem->Exec("mkdir pdf_files/");
  gSystem->Exec("mkdir png_files/");
  gSystem->Exec("mkdir C_files/");
  can->SaveAs("eps_files/"+name+".eps");
  can->SaveAs("pdf_files/"+name+".pdf");
  can->SaveAs("png_files/"+name+".png");
  can->SaveAs("C_files/"+name+".C");
}

TLatex * caption_lly(){
  TLatex * cap = new TLatex();
  cap->SetNDC();
  cap->SetTextColor(1);
  cap->SetTextSize(0.06);
  return cap;
}

TLatex * caption_lly(TString leptons, TString kins){
  TLatex * cap = new TLatex();
  cap->SetNDC();
  cap->SetTextColor(1);
  cap->SetTextSize(0.06);
  char c_label[200];
  double x_loc = 0.28; double y_loc = 0.60;
  if(leptons == "uu")
    sprintf(c_label,"Z #rightarrow #mu#mu#gamma");
  if(leptons == "ee")
    sprintf(c_label,"Z #rightarrow ee#gamma");
  cap->DrawLatex(x_loc+0.28,y_loc+0.13,c_label);

  if(kins == "h_mass_lly")
    sprintf(c_label,"m_{ll#gamma}");
  if(kins == "h_pt_photon" || kins == "h_eta_photon")
    sprintf(c_label,"Leading #gamma");
  if(leptons == "ee"){
    if(kins == "h_pt_lepton1" || kins == "h_eta_lepton1")
      sprintf(c_label,"Leading electron");
    if(kins == "h_pt_lepton2" || kins == "h_eta_lepton2")
      sprintf(c_label,"Subleading electron");}
  if(leptons == "uu"){
    if(kins == "h_pt_lepton1" || kins == "h_eta_lepton1")
      sprintf(c_label,"Leading muon");
    if(kins == "h_pt_lepton2" || kins == "h_eta_lepton2")
      sprintf(c_label,"Subleading muon");}

  cap->DrawLatex(x_loc+0.28,y_loc+0.08,c_label);
  return cap;

}
TLatex * caption_fit(double size_f = 0.05){
  TLatex * cap = new TLatex();
  cap->SetNDC();
  cap->SetTextColor(1);
  cap->SetTextSize(size_f);

  return cap;

}
