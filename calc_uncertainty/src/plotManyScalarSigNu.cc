#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"
#include "HggScalarLineShapePdf.hh"

using namespace std;
using namespace RooFit;
using namespace RooStats;

int main(int argc, char** argv){
  CommonFunc::SetAtlasStyle();

  TString jobname=argv[1];

  RooRealVar x("x","x",750,100,2000); // Observable

  RooRealVar mX("mX","mX",750);
  RooRealVar wX("wX","wX",45);
  
  HggScalarLineShapePdf pdf1("finiTop1","scalar",x,mX,wX,false);

  HggScalarLineShapePdf pdf2("infiTop2","scalar",x,mX,wX,true); pdf2.setSigma(0.25); pdf2.setNu(0.1);  pdf2.setAlpha(2.5);
  HggScalarLineShapePdf pdf3("infiTop3","scalar",x,mX,wX,true); pdf3.setSigma(0.25); pdf3.setNu(1.0);  pdf3.setAlpha(2.5);
  HggScalarLineShapePdf pdf4("infiTop4","scalar",x,mX,wX,true); pdf4.setSigma(0.25); pdf4.setNu(3.0);  pdf4.setAlpha(2.5);
  HggScalarLineShapePdf pdf5("infiTop5","scalar",x,mX,wX,true); pdf5.setSigma(0.25); pdf5.setNu(5.0);  pdf5.setAlpha(2.5);
  HggScalarLineShapePdf pdf6("infiTop6","scalar",x,mX,wX,true); pdf6.setSigma(0.25); pdf6.setNu(7.0);  pdf6.setAlpha(2.5);
  HggScalarLineShapePdf pdf7("infiTop7","scalar",x,mX,wX,true); pdf7.setSigma(0.25); pdf7.setNu(10.0); pdf7.setAlpha(2.5);

  const int nmass=1;
  double massValues[nmass]={1500};
  double xMin[nmass]={200};
  double xMax[nmass]={2000};
  const int nwidth=6;
  double widthValues[nwidth]={0.02,0.04,0.06,0.08,0.10,0.15};

  system("mkdir -vp fig/fit/"+jobname);
  
  for(int imass=0;imass<nmass;imass++){
    mX.setVal(massValues[imass]);
    for(int iwidth=0;iwidth<nwidth;iwidth++){
      unique_ptr<RooPlot> frame(x.frame());
      wX.setVal(widthValues[iwidth]*massValues[imass]);
      x.setRange("norm",mX.getVal(),mX.getVal()+wX.getVal());
    
      pdf1.plotOn(frame.get(),Name(pdf1.GetName()),LineWidth(1.5),LineColor(CommonFunc::ColorWheel(0)),NormRange("norm"));
      pdf2.plotOn(frame.get(),Name(pdf2.GetName()),LineWidth(1.5),LineColor(CommonFunc::ColorWheel(2)),NormRange("norm"), LineStyle(7));
      pdf3.plotOn(frame.get(),Name(pdf3.GetName()),LineWidth(1.5),LineColor(CommonFunc::ColorWheel(3)),NormRange("norm"), LineStyle(7));
      pdf4.plotOn(frame.get(),Name(pdf4.GetName()),LineWidth(1.5),LineColor(CommonFunc::ColorWheel(4)),NormRange("norm"), LineStyle(7));
      pdf5.plotOn(frame.get(),Name(pdf5.GetName()),LineWidth(1.5),LineColor(CommonFunc::ColorWheel(5)),NormRange("norm"), LineStyle(7));
      pdf6.plotOn(frame.get(),Name(pdf6.GetName()),LineWidth(1.5),LineColor(CommonFunc::ColorWheel(6)),NormRange("norm"), LineStyle(7));
      pdf7.plotOn(frame.get(),Name(pdf7.GetName()),LineWidth(1.5),LineColor(CommonFunc::ColorWheel(1)),NormRange("norm"), LineStyle(7));
      TCanvas c("c","c",800,600);
      frame->GetXaxis()->SetRangeUser(xMin[imass],xMax[imass]);
      frame->Draw();
      unique_ptr<TLegend> leg(CommonFunc::FastLegend(0.2,0.5,0.5,0.85,0.045));
      leg->AddEntry("finiTop1","Nominal","l");
      leg->AddEntry("infiTop2","#nu=0.1","l");
      leg->AddEntry("infiTop3","#nu=1.0","l");
      leg->AddEntry("infiTop4","#nu=3.0","l");
      leg->AddEntry("infiTop5","#nu=5.0","l");
      leg->AddEntry("infiTop6","#nu=7.0","l");
      leg->AddEntry("infiTop7","#nu=10.0","l");
      leg->Draw("same");
      TString outputCanvasName=Form("fig/fit/%s/plot_%.0fmass_%.2fwidth",jobname.Data(), massValues[imass], widthValues[iwidth]);
      CommonFunc::PrintCanvas(&c, outputCanvasName);
    }
  }
}

