#include "CommonHead.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"
#include "HggTwoSidedCBPdf.hh"

using namespace RooFit;
using namespace RooStats;

// void testConvolution(){
int main(int argc, char** argv){
  RooWorkspace *w=new RooWorkspace("wfactory");
  // w->importClassCode(HggTwoSidedCBPdf::Class(), true);
  // w->factory("mXtrue[0,-1000,1000]");
  w->factory("mXtrue[750,650,850]");
  w->factory("mRes[750]");
  w->factory("widthBW[0.004]");
  w->factory("RooBreitWigner::truth(mXtrue, mRes, widthBW)");

  w->factory("sigmaCB[5.88]");
  w->factory("alphaCBLo[1.74]");
  w->factory("alphaCBHi[2.55]");
  w->factory("nCBLo[4.00]");
  w->factory("nCBHi[2.06]");
  w->factory("mu[0]");
  w->factory("mXreco[750,650,850]");

  // w->factory("expr::x('@0-@1',mXreco,mXtrue)");  
  // w->factory("HggTwoSidedCBPdf::detector(x, mu, sigmaCB, alphaCBLo, nCBLo, alphaCBHi, nCBHi)");

  w->factory("HggTwoSidedCBPdf::detector(mXtrue, mu, sigmaCB, alphaCBLo, nCBLo, alphaCBHi, nCBHi)");
  w->var("mXtrue")->setBins(1000000,"cache");
  RooFFTConvPdf *conv=new RooFFTConvPdf("convolution","convolution", *w->var("mXtrue"), *w->pdf("truth"), *w->pdf("detector"));

  conv->Print("v");
  //RooNumConvPdf *conv=new RooNumConvPdf("convolution","convolution", *w->var("mXtrue"), *w->pdf("truth"), *w->pdf("detector"));
  
  // RooProdPdf prod("prod","prod",*w->pdf("truth"),*w->pdf("detector"));
  // RooAbsPdf* conv=prod.createProjection(*w->var("mXtrue"));

  
  // HggTwoSidedCBPdf *truth=new HggTwoSidedCBPdf("truth", "truth", *w->var("x"), *w->var("mu"), *w->var("sigmaCB"), *w->var("alphaCBLo"), *w->var("nCBLo"), *w->var("alphaCBHi"), *w->var("nCBHi"));

  // w->import(*truth);

  //w->factory("RooFFTConvPdf::conv(mX, truth, detector)");

  TCanvas *c=new TCanvas("c","c",800,600);
  
  RooPlot *frame=w->var("mXtrue")->frame();
  // RooPlot *frame=w->var("mXtrue")->frame();
  conv->plotOn(frame, LineColor(kRed));
  
  // w->pdf("conv")->plotOn(frame, LineColor(kBlack));
  w->var("mu")->setVal(750);
  w->pdf("detector")->plotOn(frame, LineColor(kBlue), LineStyle(4));
  
  // w->pdf("truth")->plotOn(frame, LineColor(kRed));

  // w->var("widthBW")->setVal(2);
  // w->var("sigmaCB")->setVal(1);
  // w->pdf("conv")->plotOn(frame, LineColor(kRed));

  // w->var("widthBW")->setVal(1);
  // w->var("sigmaCB")->setVal(2);
  // w->pdf("conv")->plotOn(frame, LineColor(kBlue));

  // w->factory("mean_1[1]");
  // w->factory("widthBW_1[2]");
  // w->factory("RooGaussian::detector_1(x, mean_1, widthBW_1)");
  // w->factory("mu_1[0]");
  // w->factory("sigmaCB_1[1]");
  // w->factory("alphaCBLo_1[0.1]");
  // w->factory("alphaCBHi_1[0.1]");
  // w->factory("nCBLo_1[10]");
  // w->factory("nCBHi_1[10]");
  
  // w->factory("HggTwoSidedCBPdf::truth_1(x, mu_1, sigmaCB_1, alphaCBLo_1, nCBLo_1, alphaCBHi_1, nCBHi_1)");

  // w->factory("RooFFTConvPdf::conv_1(x, detector_1, truth_1)");

  // w->pdf("conv_1")->plotOn(frame, LineColor(kOrange), LineStyle(3));

  // w->factory("mean_2[1]");
  // w->factory("widthBW_2[1]");
  // w->factory("RooGaussian::detector_2(x, mean_2, widthBW_2)");
  // w->factory("mu_2[0]");
  // w->factory("sigmaCB_2[2]");
  // w->factory("alphaCBLo_2[0.1]");
  // w->factory("alphaCBHi_2[0.1]");
  // w->factory("nCBLo_2[10]");
  // w->factory("nCBHi_2[10]");
  
  // w->factory("HggTwoSidedCBPdf::truth_2(x, mu_2, sigmaCB_2, alphaCBLo_2, nCBLo_2, alphaCBHi_2, nCBHi_2)");

  // w->factory("RooFFTConvPdf::conv_2(x, detector_2, truth_2)");

  // w->pdf("conv_2")->plotOn(frame, LineColor(kMagenta), LineStyle(3));
  frame->GetXaxis()->SetRangeUser(650, 850);
  frame->Draw();
  c->SaveAs("test.pdf");
}
