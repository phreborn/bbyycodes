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
  TString option=argv[2];
  
  RooRealVar x("x","x",750,100,2000); // Observable
  x.setBins(10000);
  RooRealVar mX("mX","mX",750);
  RooRealVar wX("wX","wX",45);
  
  HggScalarLineShapePdf pdf1("Nominal","scalar",x,mX,wX,false);
  HggScalarLineShapePdf pdf2("MELgg1", "scalar",x,mX,wX,true);   pdf2.setSigma(0.4); pdf2.setNu(-2);  pdf2.setAlpha(1.0);
  HggScalarLineShapePdf pdf3("MELgg2", "scalar",x,mX,wX,true);   pdf3.setSigma(0.6); pdf3.setNu(-2);  pdf3.setAlpha(1.0);
  HggScalarLineShapePdf pdf4("MELgg3", "scalar",x,mX,wX,true);   pdf4.setSigma(0.8); pdf4.setNu(-2);  pdf4.setAlpha(1.0);
  HggScalarLineShapePdf pdf5("MELgg4", "scalar",x,mX,wX,true);   pdf5.setSigma(1.0); pdf5.setNu(-2);  pdf5.setAlpha(1.0);

  const int nmass=1;
  double massValues[nmass]={1600};
  const int nwidth=8;
  double widthValues[nwidth]={0.02,0.04,0.06,0.08,0.10,0.15,0.2,0.25};

  system("mkdir -vp fig/fit/"+jobname);
  
  for(int imass=0;imass<nmass;imass++){
    mX.setVal(massValues[imass]);
    for(int iwidth=0;iwidth<nwidth;iwidth++){
      TCanvas c("c","c",800,600);
      
      TPad pad1("pad1", "pad1", 0.00, 0.4, 1.00, 1.0);
      TPad pad2("pad2", "pad2", 0.00, 0.0, 1.00, 0.4);

      unique_ptr<RooPlot> frame1(x.frame());
      unique_ptr<RooPlot> frame2(x.frame());
      wX.setVal(widthValues[iwidth]*massValues[imass]);
      x.setRange("norm",mX.getVal(),mX.getVal()+wX.getVal());
      double xMin=massValues[imass]-8*widthValues[iwidth]*massValues[imass];
      double xMax=massValues[imass]+2*widthValues[iwidth]*massValues[imass];
      double fid_win_low=mX.getVal()-1.5*wX.getVal();	
      pdf1.plotOn(frame1.get(),Name(pdf1.GetName()),LineWidth(2),LineColor(CommonFunc::ColorWheel(0)),NormRange("norm"));
      pdf2.plotOn(frame1.get(),Name(pdf2.GetName()),LineWidth(2),LineColor(CommonFunc::ColorWheel(1)),NormRange("norm"), LineStyle(7));
      pdf3.plotOn(frame1.get(),Name(pdf3.GetName()),LineWidth(2),LineColor(CommonFunc::ColorWheel(2)),NormRange("norm"), LineStyle(7));
      pdf4.plotOn(frame1.get(),Name(pdf4.GetName()),LineWidth(2),LineColor(CommonFunc::ColorWheel(3)),NormRange("norm"), LineStyle(7));
      pdf5.plotOn(frame1.get(),Name(pdf5.GetName()),LineWidth(2),LineColor(CommonFunc::ColorWheel(4)),NormRange("norm"), LineStyle(7));
      // pdf6.plotOn(frame.get(),Name(pdf6.GetName()),LineWidth(1.5),LineColor(CommonFunc::ColorWheel(6)),NormRange("norm"), LineStyle(7));
      // pdf7.plotOn(frame.get(),Name(pdf7.GetName()),LineWidth(1.5),LineColor(CommonFunc::ColorWheel(1)),NormRange("norm"), LineStyle(7));

      pad1.cd();
      frame1->GetXaxis()->SetRangeUser(xMin,xMax);
      frame1->Draw();
      unique_ptr<TLegend> leg(CommonFunc::FastLegend(0.2,0.5,0.5,0.85,0.045));
      leg->AddEntry(pdf1.GetName(),"Nominal","l");
      leg->AddEntry(pdf2.GetName(),"#sigma=0.4#Gamma_{X}","l");
      leg->AddEntry(pdf3.GetName(),"#sigma=0.6#Gamma_{X}","l");
      leg->AddEntry(pdf4.GetName(),"#sigma=0.8#Gamma_{X}","l");
      leg->AddEntry(pdf5.GetName(),"#sigma=1.0#Gamma_{X}","l");
      // leg->AddEntry(pdf5.GetName(),"#sigma = 0.7#Gamma_{X}","l");
      // leg->AddEntry(pdf5.GetName(),"Sigmoid #nu=3","l");
      // leg->AddEntry("infiTop4","#nu=3.0","l");
      // leg->AddEntry("infiTop5","#nu=5.0","l");
      // leg->AddEntry("infiTop6","#nu=7.0","l");
      // leg->AddEntry("infiTop7","#nu=10.0","l");
      leg->Draw("same");

      CommonFunc::DrawVerticalLine(&pad1, mX.getVal(), frame1->GetMinimum(), frame1->GetMaximum(), kMagenta, 2, 2);
      // CommonFunc::DrawVerticalLine(&pad1, mX.getVal()-wX.getVal(), frame1->GetMinimum(), frame1->GetMaximum(), kMagenta, 3, 2);
      // CommonFunc::DrawVerticalLine(&pad1, mX.getVal()+wX.getVal(), frame1->GetMinimum(), frame1->GetMaximum(), kMagenta, 3, 2);
      CommonFunc::DrawVerticalLine(&pad1, mX.getVal()-1*wX.getVal(), frame1->GetMinimum(), frame1->GetMaximum(), kRed, 3, 2);
      CommonFunc::DrawVerticalLine(&pad1, mX.getVal()+1*wX.getVal(), frame1->GetMinimum(), frame1->GetMaximum(), kRed, 3, 2);
      CommonFunc::DrawVerticalLine(&pad1, mX.getVal()-2*wX.getVal(), frame1->GetMinimum(), frame1->GetMaximum(), kRed, 3, 2);
      CommonFunc::DrawVerticalLine(&pad1, mX.getVal()-3*wX.getVal(), frame1->GetMinimum(), frame1->GetMaximum(), kRed, 3, 2);
      unique_ptr<RooDerivative> dsdx1(pdf1.derivative(x,2));
      unique_ptr<RooDerivative> dsdx2(pdf2.derivative(x,2));
      unique_ptr<RooDerivative> dsdx3(pdf3.derivative(x,2));
      unique_ptr<RooDerivative> dsdx4(pdf4.derivative(x,2));
      unique_ptr<RooDerivative> dsdx5(pdf5.derivative(x,2));

      dsdx2->plotOn(frame2.get(),Name(dsdx2->GetName()),LineWidth(2),LineColor(CommonFunc::ColorWheel(1)));
      dsdx3->plotOn(frame2.get(),Name(dsdx3->GetName()),LineWidth(2),LineColor(CommonFunc::ColorWheel(2)));
      dsdx4->plotOn(frame2.get(),Name(dsdx4->GetName()),LineWidth(2),LineColor(CommonFunc::ColorWheel(3)));
      dsdx5->plotOn(frame2.get(),Name(dsdx5->GetName()),LineWidth(2),LineColor(CommonFunc::ColorWheel(4)));
      
      frame2->GetXaxis()->SetRangeUser(xMin,xMax);
      x.setVal(fid_win_low);
      frame2->SetMaximum(2*dsdx1->getVal());
      frame2->SetMinimum(-2*dsdx1->getVal());
      pad2.cd();
      frame2->Draw();

      c.cd();
      pad1.Draw();
      pad2.Draw();
      TString outputCanvasName=Form("fig/fit/%s/plot_%.0fmass_%.2fwidth",jobname.Data(), massValues[imass], widthValues[iwidth]);
      if(option.Contains("logy")){
	pad1.SetLogy();
	outputCanvasName+="_logy";
      }
      CommonFunc::PrintCanvas(&c, outputCanvasName);
    }
  }
}

