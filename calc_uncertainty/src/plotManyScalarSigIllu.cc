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

  RooRealVar a1("a1","a1",0); // Observable
  RooRealVar a2("a2","a2",0.8); // Observable
  RooRealVar a3("a3","a3",1.0); // Observable
  RooRealVar a4("a4","a4",1.2); // Observable
  RooRealVar a5("a5","a5",1.5); // Observable
  RooRealVar a6("a6","a6",2.0); // Observable
  x.setBins(10000);
  
  RooRealVar mX("mX","mX",750);
  RooRealVar wX("wX","wX",45);
  
  HggScalarLineShapePdf pdf1("Nominal","scalar",x,mX,wX,a1,13,false);
  HggScalarLineShapePdf pdf2("MELgg1", "scalar",x,mX,wX,a2,13,true); 
  HggScalarLineShapePdf pdf3("MELgg2", "scalar",x,mX,wX,a3,13,true); 
  HggScalarLineShapePdf pdf4("MELgg3", "scalar",x,mX,wX,a4,13,true); 
  HggScalarLineShapePdf pdf5("MELgg4", "scalar",x,mX,wX,a5,13,true); 
  HggScalarLineShapePdf pdf6("MELgg5", "scalar",x,mX,wX,a6,13,true); 

  const int nmass=8;
  double massValues[nmass]={200, 400, 600, 750, 1000, 1200, 1400, 1800};
  // double massValues[nmass]={400};
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
      double xMin=std::max(x.getMin(),massValues[imass]-8*widthValues[iwidth]*massValues[imass]);
      double xMax=std::min(x.getMax(),massValues[imass]+2*widthValues[iwidth]*massValues[imass]);
      double fid_win_low=mX.getVal()-1.5*wX.getVal();	
      pdf1.plotOn(frame1.get(),Name(pdf1.GetName()),LineWidth(2),LineColor(CommonFunc::ColorWheel(0)),NormRange("norm"));
      pdf2.plotOn(frame1.get(),Name(pdf2.GetName()),LineWidth(2),LineColor(CommonFunc::ColorWheel(1)),NormRange("norm"), LineStyle(7));
      pdf3.plotOn(frame1.get(),Name(pdf3.GetName()),LineWidth(2),LineColor(CommonFunc::ColorWheel(2)),NormRange("norm"), LineStyle(7));
      pdf4.plotOn(frame1.get(),Name(pdf4.GetName()),LineWidth(2),LineColor(CommonFunc::ColorWheel(3)),NormRange("norm"), LineStyle(7));
      pdf5.plotOn(frame1.get(),Name(pdf5.GetName()),LineWidth(2),LineColor(CommonFunc::ColorWheel(4)),NormRange("norm"), LineStyle(7));
      pdf6.plotOn(frame1.get(),Name(pdf6.GetName()),LineWidth(2),LineColor(CommonFunc::ColorWheel(5)),NormRange("norm"), LineStyle(7));

      pad1.cd();
      pad1.SetBottomMargin(0);
      frame1->GetXaxis()->SetRangeUser(xMin,xMax);
      frame1->GetXaxis()->SetTitle("m_{X} [GeV]");
      frame1->GetYaxis()->SetTitle("A.U.");
      frame1->GetYaxis()->SetTitleSize(0.06);
      frame1->Draw();
      unique_ptr<TLegend> leg(CommonFunc::FastLegend(0.2,0.5,0.5,0.85,0.06));
      leg->AddEntry(pdf1.GetName(),"Nominal","l");
      leg->AddEntry(pdf2.GetName(),"m_{Low}=m_{X}-0.8#Gamma_{X}","l");
      leg->AddEntry(pdf3.GetName(),"m_{Low}=m_{X}-1.0#Gamma_{X}","l");
      leg->AddEntry(pdf4.GetName(),"m_{Low}=m_{X}-1.2#Gamma_{X}","l");
      leg->AddEntry(pdf5.GetName(),"m_{Low}=m_{X}-1.5#Gamma_{X}","l");
      leg->AddEntry(pdf6.GetName(),"m_{Low}=m_{X}-2.0#Gamma_{X}","l");
      // leg->AddEntry(pdf5.GetName(),"#sigma = 0.7#Gamma_{X}","l");
      // leg->AddEntry(pdf5.GetName(),"Sigmoid #nu=3","l");
      // leg->AddEntry("infiTop4","#nu=3.0","l");
      // leg->AddEntry("infiTop5","#nu=5.0","l");
      // leg->AddEntry("infiTop6","#nu=7.0","l");
      // leg->AddEntry("infiTop7","#nu=10.0","l");
      leg->Draw("same");

      CommonFunc::DrawVerticalLine(&pad1, mX.getVal()-a2.getVal()*wX.getVal(), frame1->GetMinimum(), frame1->GetMaximum(), CommonFunc::ColorWheel(1), 3, 2);
      CommonFunc::DrawVerticalLine(&pad1, mX.getVal()-a3.getVal()*wX.getVal(), frame1->GetMinimum(), frame1->GetMaximum(), CommonFunc::ColorWheel(2), 3, 2);
      CommonFunc::DrawVerticalLine(&pad1, mX.getVal()-a4.getVal()*wX.getVal(), frame1->GetMinimum(), frame1->GetMaximum(), CommonFunc::ColorWheel(3), 3, 2);
      CommonFunc::DrawVerticalLine(&pad1, mX.getVal()-a5.getVal()*wX.getVal(), frame1->GetMinimum(), frame1->GetMaximum(), CommonFunc::ColorWheel(4), 3, 2);
      CommonFunc::DrawVerticalLine(&pad1, mX.getVal()-a6.getVal()*wX.getVal(), frame1->GetMinimum(), frame1->GetMaximum(), CommonFunc::ColorWheel(5), 3, 2);

      // CommonFunc::DrawVerticalLine(&pad1, mX.getVal(), frame1->GetMinimum(), frame1->GetMaximum(), kMagenta, 2, 2);
      // CommonFunc::DrawVerticalLine(&pad1, mX.getVal()-wX.getVal(), frame1->GetMinimum(), frame1->GetMaximum(), kMagenta, 3, 2);
      // CommonFunc::DrawVerticalLine(&pad1, mX.getVal()+wX.getVal(), frame1->GetMinimum(), frame1->GetMaximum(), kMagenta, 3, 2);
      // CommonFunc::DrawVerticalLine(&pad1, mX.getVal()-1*wX.getVal(), frame1->GetMinimum(), frame1->GetMaximum(), kRed, 3, 2);
      // CommonFunc::DrawVerticalLine(&pad1, mX.getVal()+1*wX.getVal(), frame1->GetMinimum(), frame1->GetMaximum(), kRed, 3, 2);
      // CommonFunc::DrawVerticalLine(&pad1, mX.getVal()-2*wX.getVal(), frame1->GetMinimum(), frame1->GetMaximum(), kRed, 3, 2);
      // CommonFunc::DrawVerticalLine(&pad1, mX.getVal()-3*wX.getVal(), frame1->GetMinimum(), frame1->GetMaximum(), kRed, 3, 2);

      unique_ptr<RooDerivative> dsdx1(pdf1.derivative(x,2));
      unique_ptr<RooDerivative> dsdx2(pdf2.derivative(x,2));
      unique_ptr<RooDerivative> dsdx3(pdf3.derivative(x,2));
      unique_ptr<RooDerivative> dsdx4(pdf4.derivative(x,2));
      unique_ptr<RooDerivative> dsdx5(pdf5.derivative(x,2));
      unique_ptr<RooDerivative> dsdx6(pdf6.derivative(x,2));

      dsdx2->plotOn(frame2.get(),Name(dsdx2->GetName()),LineWidth(2),LineColor(CommonFunc::ColorWheel(1)));
      dsdx3->plotOn(frame2.get(),Name(dsdx3->GetName()),LineWidth(2),LineColor(CommonFunc::ColorWheel(2)));
      dsdx4->plotOn(frame2.get(),Name(dsdx4->GetName()),LineWidth(2),LineColor(CommonFunc::ColorWheel(3)));
      dsdx5->plotOn(frame2.get(),Name(dsdx5->GetName()),LineWidth(2),LineColor(CommonFunc::ColorWheel(4)));
      dsdx6->plotOn(frame2.get(),Name(dsdx6->GetName()),LineWidth(2),LineColor(CommonFunc::ColorWheel(5)));
      
      frame2->GetXaxis()->SetRangeUser(xMin,xMax);
      frame2->GetXaxis()->SetTitle("m_{X} [GeV]");
      frame2->GetYaxis()->SetTitle("d^{2}f(m_{#gamma#gamma})/dm_{#gamma#gamma}^{2}");
      frame2->GetYaxis()->SetTitleSize(0.1);
      frame2->GetYaxis()->SetTitleOffset(0.7);
      frame2->GetXaxis()->SetTitleSize(0.1);
      frame2->GetXaxis()->SetLabelSize(0.1);
      frame2->GetYaxis()->SetLabelSize(0.1);
      
      x.setVal(fid_win_low);
      frame2->SetMaximum(2*dsdx1->getVal());
      frame2->SetMinimum(-2*dsdx1->getVal());
      pad2.cd();
      pad2.SetTopMargin(0);
      pad2.SetBottomMargin(0.25);

      frame2->Draw();
      CommonFunc::DrawConstantLine(&pad2, 0, xMin, xMax, kBlack, 3, 3);
      TLatex l; //l.SetTextAlign(12); l.SetTextSize(tsize);
      l.SetNDC();
      l.SetTextColor(1);
      l.SetTextSize(0.08);
      l.DrawLatex(0.2, 0.35, Form("m_{X} = %.0f GeV, #Gamma_{X} = %.2fm_{X}", massValues[imass], widthValues[iwidth]));
      
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

