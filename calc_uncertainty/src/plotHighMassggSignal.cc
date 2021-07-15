#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"
#include "MxAODNtup.h"
#include "statistics.hh"
#include "ToolsSignificanceHist.h"

using namespace std;
using namespace RooFit;
using namespace RooStats;

const double epsilon=1e-4;

int FileNameToMassIdx(TString fileName){
  // genData_ggH1100_W10p.root
  if(fileName.Contains("_500.")||fileName.Contains("_ggH200.")||fileName.Contains("_ggH200."))   return 0;
  if(fileName.Contains("_550.")||fileName.Contains("_ggH250.")||fileName.Contains("_ggH250."))   return 1;
  if(fileName.Contains("_600.")||fileName.Contains("_ggH300.")||fileName.Contains("_ggH300."))   return 2;
  if(fileName.Contains("_650.")||fileName.Contains("_ggH350.")||fileName.Contains("_ggH350."))   return 3;
  if(fileName.Contains("_700.")||fileName.Contains("_ggH400.")||fileName.Contains("_ggH400."))   return 4;
  if(fileName.Contains("_750.")||fileName.Contains("_ggH450.")||fileName.Contains("_ggH450."))   return 5;
  if(fileName.Contains("_800.")||fileName.Contains("_ggH500.")||fileName.Contains("_ggH500."))   return 6;
  if(fileName.Contains("_850.")||fileName.Contains("_ggH600.")||fileName.Contains("_ggH600."))   return 7;
  if(fileName.Contains("_900.")||fileName.Contains("_ggH700.")||fileName.Contains("_ggH700."))   return 8;
  if(fileName.Contains("_950.")||fileName.Contains("_ggH800.")||fileName.Contains("_ggH800."))   return 9;
  if(fileName.Contains("_1000.")||fileName.Contains("_ggH1000.")||fileName.Contains("_ggH1000."))  return 10;
  if(fileName.Contains("_1500.")||fileName.Contains("_ggH1500.")||fileName.Contains("_ggH1500."))  return 11;
  if(fileName.Contains("_2000.")||fileName.Contains("_ggH2000.")||fileName.Contains("_ggH2000."))  return 12;
  if(fileName.Contains("_2500."))  return 13;
  if(fileName.Contains("_3000."))  return 14;
  if(fileName.Contains("_3500."))  return 15;
  if(fileName.Contains("_4000."))  return 16;
  if(fileName.Contains("_4500."))  return 17;
  if(fileName.Contains("_5000."))  return 18;
  if(fileName.Contains("_5500."))  return 19;
  return -1;
}

int FileNameToWidthIdx(TString fileName){
  if(fileName.Contains("_001_")||fileName.Contains("0.MxAOD"))    return 0;
  if(fileName.Contains("_005_")||fileName.Contains("_W5p."))    return 1;
  if(fileName.Contains("_01_")||fileName.Contains("_W7p."))     return 2;
  if(fileName.Contains("_015_")||fileName.Contains("_W10p."))    return 3;
  if(fileName.Contains("_02_"))     return 4;
  if(fileName.Contains("_025_"))    return 5;
  // if(fileName.Contains("_k03."))     return 6;
  // if(fileName.Contains("_k035."))    return 7;
  // if(fileName.Contains("_k037."))    return 8;
  // if(fileName.Contains("_k04."))     return 9;
  return -1;
}


int main(int argc, char **argv){
  if(argc<5){
    cout<<"Usage: "<<argv[0]<<" <jobname> <input file list> <signal> <selection> <option>"<<endl;
    exit(0);
  }
  CommonFunc::SetAtlasStyle();
  TString jobname=argv[1];
  TString inputFileList=argv[2];
  TString signal=argv[3];
  TString selection=argv[4];
  TString option=argv[5];

  TString wsFileName="";
  if(signal=="graviton"&&selection=="EKHI") wsFileName="workspace/high_mass_diphoton/1516_Graviton_histfactory_EKHI_v36.root";
  if(signal=="scalar"&&selection=="HKHI"){
    wsFileName="workspace/high_mass_diphoton/2015_Scalar_2D_v7.root";
    if(option.Contains("nocutoff")) wsFileName="workspace/high_mass_diphoton/2015_Scalar_2D_v7_no_cutoff.root";
  }
  
  unique_ptr<TFile> f(TFile::Open(wsFileName,"read"));
  RooWorkspace *ws=dynamic_cast<RooWorkspace*>(f->Get("combWS"));
  
  RooAbsPdf *pdf=ws->pdf("pdf__signal_inclusive_13TeV_2016_EKHI");
  RooRealVar *x=(RooRealVar*)ws->set("Observables")->first();
  cout<<pdf<<" "<<x<<endl;
  assert(pdf);
  assert(x);
  if(ws->var("ATLAS_mRes")) ws->var("ATLAS_mRes")->setVal(0);

  // Get the file list. who cares!

  unique_ptr<TChain> c(CommonFunc::MakeChain("CollectionTree",inputFileList,"badfile", inputFileList.Contains(".root")));

  MxAODNtup *p=new MxAODNtup(c.get());

  vector<Double_t> massArr, widthArr;

  if(signal=="graviton"){
    for(int m=500;m<1000;m+=50) massArr.push_back(m);
    for(int m=1000;m<=5500;m+=500) massArr.push_back(m);

    for(int w=0;w<=25;w+=5) widthArr.push_back(w==0?0.01:w/100.);
  }

  if(signal=="scalar"){
    for(int m=200;m<500;m+=50) massArr.push_back(m);
    for(int m=500;m<800;m+=100) massArr.push_back(m);
    for(int m=800;m<1000;m+=200) massArr.push_back(m);
    for(int m=1000;m<=2000;m+=500) massArr.push_back(m);

    widthArr.push_back(0);
    widthArr.push_back(0.05);
    widthArr.push_back(0.07);
    widthArr.push_back(0.10);
  }
  const int nmass=massArr.size(), nwidth=widthArr.size();

  RooWorkspace *wsCat[nmass][nwidth];
  RooDataSet* MCCat[nmass][nwidth];
  RooRealVar* xCat[nmass][nwidth], *wCat[nmass][nwidth];
  RooAbsPdf* pdfCat[nmass][nwidth];
  RooPlot* frameCat[nmass][nwidth];
  double xMinArr[nmass][nwidth], xMaxArr[nmass][nwidth];
  int nBinArr[nmass][nwidth];
  TH1F *histData[nmass][nwidth];
  
  for(int imass=0;imass<nmass;imass++){
    for(int iwidth=0;iwidth<nwidth;iwidth++){
      double width=(signal=="graviton")?1.44*massArr[imass]*widthArr[iwidth]*widthArr[iwidth]:massArr[imass]*widthArr[iwidth];
      if(width<12) width=12;
      wsCat[imass][iwidth]=new RooWorkspace(Form("wsCat_%.0f_%.2f", massArr[imass], widthArr[iwidth]));
      wsCat[imass][iwidth]->import(*pdf);
      cout<<"Okay here"<<endl;
      pdfCat[imass][iwidth]=wsCat[imass][iwidth]->pdf(pdf->GetName());
      xCat[imass][iwidth]=wsCat[imass][iwidth]->var(x->GetName());
      cout<<"Okay here"<<endl;
      
      double binw=5;
      if(signal=="graviton"){
	xMaxArr[imass][iwidth]=massArr[imass]+8*width;
	xMinArr[imass][iwidth]=massArr[imass]-4*width;
	if(option.Contains("logy")){
	  xMaxArr[imass][iwidth]=massArr[imass]+10*width;
	  if(widthArr[iwidth]==0.01){
	    xMinArr[imass][iwidth]=massArr[imass]-6*width;
	    xMaxArr[imass][iwidth]=massArr[imass]+14*width;
	  }
	}

	if(widthArr[iwidth]==0.01){
	  if(massArr[imass]<=1000) binw=2;
	  else if(massArr[imass]<=3000) binw=5;
	  else binw=10;
	}
	if(widthArr[iwidth]==0.05){
	  if(massArr[imass]<=1000) binw=5;
	  else if(massArr[imass]<=3000) binw=10;
	  else binw=20;
	}
	if(widthArr[iwidth]==0.10){
	  if(massArr[imass]<=1000) binw=5;
	  else if(massArr[imass]<=3000) binw=10;
	  else binw=20;
	}
	if(widthArr[iwidth]==0.15){
	  if(massArr[imass]<=1000) binw=10;
	  else if(massArr[imass]<=3000) binw=20;
	  else binw=40;
	}
	if(widthArr[iwidth]==0.2){
	  if(massArr[imass]<=1000) binw=10;
	  else if(massArr[imass]<=3000) binw=20;
	  else binw=40;
	}
	if(widthArr[iwidth]==0.25){
	  if(massArr[imass]<=1000) binw=20;
	  else if(massArr[imass]<=3000) binw=40;
	  else binw=50;
	}
      }
      if(signal=="scalar"){
	xMaxArr[imass][iwidth]=massArr[imass]+6*width;
	xMinArr[imass][iwidth]=massArr[imass]-10*width;

	if(widthArr[iwidth]==0){
	  if(massArr[imass]<=1000) binw=2;
	  else if(massArr[imass]<=3000) binw=5;
	  else binw=10;
	}
	if(widthArr[iwidth]==0.05){
	  if(massArr[imass]<=1000) binw=5;
	  else if(massArr[imass]<=3000) binw=10;
	  else binw=20;
	}
	if(widthArr[iwidth]==0.07){
	  if(massArr[imass]<=1000) binw=10;
	  else if(massArr[imass]<=3000) binw=20;
	  else binw=20;
	}
	if(widthArr[iwidth]==0.10){
	  if(massArr[imass]<=1000) binw=20;
	  else if(massArr[imass]<=3000) binw=40;
	  else binw=40;
	}
      }

      nBinArr[imass][iwidth]=int((xMaxArr[imass][iwidth]-xMinArr[imass][iwidth])/binw)+1;
      xMinArr[imass][iwidth]=xMaxArr[imass][iwidth]-nBinArr[imass][iwidth]*binw;
      // cout<<massArr[imass]<<" "<<widthArr[iwidth]<<" "<<xMinArr[imass][iwidth]<<" "<<xMaxArr[imass][iwidth]<<endl; getchar();
      xCat[imass][iwidth]->setRange(xMinArr[imass][iwidth], xMaxArr[imass][iwidth]);
      xCat[imass][iwidth]->setBins(nBinArr[imass][iwidth]);
      cout<<massArr[imass]<<" "<<widthArr[iwidth]<<" "<<xMinArr[imass][iwidth]<<" "<<xMaxArr[imass][iwidth]<<" "<<nBinArr[imass][iwidth]<<endl;
      frameCat[imass][iwidth]=xCat[imass][iwidth]->frame();

      wCat[imass][iwidth]=new RooRealVar(Form("w_%.0f_%.2f",massArr[imass], widthArr[iwidth]),Form("w_%.0f_%.2f",massArr[imass], widthArr[iwidth]),1);

      MCCat[imass][iwidth]=new RooDataSet(Form("MC_%.0f_%.2f",massArr[imass], widthArr[iwidth]),Form("MC_%.0f_%.2f",massArr[imass], widthArr[iwidth]), RooArgSet(*xCat[imass][iwidth],*wCat[imass][iwidth]), WeightVar(*wCat[imass][iwidth]));

      histData[imass][iwidth]=new TH1F(Form("hist_%.0f_%.2f",massArr[imass], widthArr[iwidth]),Form("hist_%.0f_%.2f",massArr[imass], widthArr[iwidth]), nBinArr[imass][iwidth], xMinArr[imass][iwidth], xMaxArr[imass][iwidth]);
      histData[imass][iwidth]->Sumw2();
    }
  }
  
  int nevt=c->GetEntries();
  
  for(int ievt=0;ievt<nevt;ievt++){
    if(ievt%100==0){
      cout<<"Processing "<<ievt*100./double(nevt)<<"% of events...\r"<<std::flush;
    }
    c->GetEntry(ievt);

    TString fileName=c->GetFile()->GetName();
    int imass=FileNameToMassIdx(fileName);
    int iwidth=FileNameToWidthIdx(fileName);

    double weight=p->vertexWeight*p->mcEventWeights->at(0);
    if(imass<0||iwidth<0) continue;
    // cout<<p->isPassedIsolationLowHighMyy<<" "<<p->isPassedExotic<<" "<<p->isDalitz<<endl;
    if(selection.Contains("EKHI")){
      if(!(p->isPassedIsolationLowHighMyy&&p->isPassedExotic&&!p->isDalitz)) continue;
    }
    if(selection.Contains("HKHI")){
      if(!(p->isPassedLowHighMyy&&!p->isDalitz)) continue;
    }
    histData[imass][iwidth]->Fill(p->m_yy/GeV, weight);
    // cout<<p->m_yy/GeV<<endl;
  }

  cout<<"okay here"<<endl;
  for(int imass=0;imass<nmass;imass++){
    for(int iwidth=0;iwidth<nwidth;iwidth++){
      if(histData[imass][iwidth]->Integral()<=0){
	cout<<"0 events for "<<massArr[imass]<<" and "<<widthArr[iwidth]<<endl;
	continue;
      }

      CommonFunc::ScaleToOne(histData[imass][iwidth], true);
      // MCCat[imass][iwidth]=statistics::histToDataSet(histData[imass][iwidth],xCat[imass][iwidth],wCat[imass][iwidth]);
      // if(iwidth!=3) continue;
      TCanvas canvas("c","c",800,600);

      TPad pad1("pad1", "pad1", 0.00, 0.33, 1.00, 1.00);
      TPad pad2("pad2", "pad2", 0.00, 0.00, 1.00, 0.33);
      pad1.SetBottomMargin(0.00001);
      pad1.SetBorderMode(0);
      pad2.SetTopMargin(0.00001);
      pad2.SetBottomMargin(0.4);
      pad2.SetBorderMode(0);
      // canvas.cd();
      pad1.Draw();
      pad2.Draw();
      pad1.cd();

      // MCCat[imass][iwidth]->plotOn(frameCat[imass][iwidth], DataError(RooAbsData::SumW2), Binning(nBinArr[imass][iwidth]));
      if(signal=="graviton"){
	statistics::setVal(wsCat[imass][iwidth]->var("mG"), massArr[imass], true);
	statistics::setVal(wsCat[imass][iwidth]->var("GkM"), widthArr[iwidth], true);
	wsCat[imass][iwidth]->var("mG")->Print();
	wsCat[imass][iwidth]->var("GkM")->Print();
      }

      if(signal=="scalar"){
	Double_t actualWidth=massArr[imass]*widthArr[iwidth];
	if(actualWidth==0) actualWidth=0.004;
	statistics::setVal(wsCat[imass][iwidth]->var("mX"), massArr[imass], true);
	statistics::setVal(wsCat[imass][iwidth]->var("wX"), actualWidth, true);
	wsCat[imass][iwidth]->var("mX")->Print();
	wsCat[imass][iwidth]->var("wX")->Print();
      }

      pdfCat[imass][iwidth]->plotOn(frameCat[imass][iwidth], LineColor(CommonFunc::ColorWheel(imass+1)), Normalization(histData[imass][iwidth]->Integral()));

      // TH1F hframe("hframe","hframe", nBinArr[imass][iwidth], xMinArr[imass][iwidth], xMaxArr[imass][iwidth]);
      // if(option.Contains("logy")){
      // 	hframe.SetMinimum(10);
      // 	if(widthArr[iwidth]==0.01) hframe.SetMinimum(1);
      // 	hframe.SetMaximum(5e3);
      // }
      // else{
      // 	hframe.SetMinimum(0);
      // 	hframe.SetMaximum(0.23);
      // }
      
      // hframe.SetLineWidth(0);
      histData[imass][iwidth]->GetYaxis()->SetTitle(Form("1/N dN/dm_{#gamma#gamma} / %.0f GeV",(xMaxArr[imass][iwidth]-xMinArr[imass][iwidth])/double(nBinArr[imass][iwidth])));
      histData[imass][iwidth]->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
      histData[imass][iwidth]->GetXaxis()->SetTitleSize(0.06);
      histData[imass][iwidth]->GetYaxis()->SetTitleSize(0.06);
      histData[imass][iwidth]->GetYaxis()->SetTitleOffset(1.3);
      histData[imass][iwidth]->SetLineWidth(1.5);
      histData[imass][iwidth]->SetMaximum(histData[imass][iwidth]->GetMaximum()*1.2);
      histData[imass][iwidth]->Draw();
      
      frameCat[imass][iwidth]->Draw("same");
      histData[imass][iwidth]->Draw("same,E");

      TLatex l; //l.SetTextAlign(12); l.SetTextSize(tsize);
      l.SetNDC();
      l.SetTextColor(1);
      l.SetTextSize(0.05);

      if(signal=="graviton"){
	if(option.Contains("note")) l.DrawLatex(0.47, 0.85, "#bf{#it{ATLAS}} Simulation Preliminary");
	else if(option.Contains("paper")) l.DrawLatex(0.47, 0.85, "#bf{#it{ATLAS}} Simulation");
	else l.DrawLatex(0.47, 0.85, "#bf{#it{ATLAS}} Simulation Internal"); 
	l.DrawLatex(0.5, 0.78, "#sqrt{#it{s}} = 13 TeV, G*#rightarrow#gamma#gamma");
	l.DrawLatex(0.5, 0.71, "Spin-2 Selection");
	l.SetTextSize(0.045);
	
	l.DrawLatex(0.5, 0.64, Form("m_{G*} = %.0f GeV", massArr[imass]));
	if(widthArr[iwidth]==0.01){
	  l.DrawLatex(0.5, 0.57, Form("#it{k}/#bar{M}_{Pl} = %.2f (#Gamma_{G*}/m_{G*} = %.2f%%)", widthArr[iwidth], 1.44*widthArr[iwidth]*widthArr[iwidth]*100));
	}
	else{
	  l.DrawLatex(0.5, 0.57, Form("#it{k}/#bar{M}_{Pl} = %.2f (#Gamma_{G*}/m_{G*} = %.1f%%)", widthArr[iwidth], 1.44*widthArr[iwidth]*widthArr[iwidth]*100));
	}
      }
      if(signal=="scalar"){
	if(option.Contains("note")) l.DrawLatex(0.2, 0.85, "#bf{#it{ATLAS}} Simulation Preliminary");
	else if(option.Contains("paper")) l.DrawLatex(0.2, 0.85, "#bf{#it{ATLAS}} Simulation");
	else l.DrawLatex(0.2, 0.85, "#bf{#it{ATLAS}} Simulation Internal"); 
	l.DrawLatex(0.2, 0.78, "#sqrt{#it{s}} = 13 TeV, X#rightarrow#gamma#gamma");
	l.DrawLatex(0.2, 0.71, "Spin-0 Selection");
	l.SetTextSize(0.045);
	
	l.DrawLatex(0.2, 0.64, Form("m_{X} = %.0f GeV", massArr[imass]));
	if(widthArr[iwidth]==0){
	  l.DrawLatex(0.2, 0.57, "NWA");
	}
	else{
	  l.DrawLatex(0.2, 0.57, Form("#Gamma_{X}/m_{X} = %.1f%%", widthArr[iwidth]*100));
	}
      }

      pad2.cd();
    
      TH1F hframe2("hframe2","hframe2",nBinArr[imass][iwidth],xMinArr[imass][iwidth],xMaxArr[imass][iwidth]);
      hframe2.SetMinimum(0.1);
      hframe2.SetMaximum(1.9);
      hframe2.SetLineWidth(2);
      hframe2.GetXaxis()->SetTitle("m_{X} [GeV]");
      hframe2.GetXaxis()->SetTitleOffset(1);
      hframe2.GetYaxis()->SetTitleOffset(0.5);
      hframe2.GetXaxis()->SetTitleSize(0.15);
      hframe2.GetYaxis()->SetTitleSize(0.12);
      hframe2.GetXaxis()->SetLabelSize(0.12);
      hframe2.GetYaxis()->SetLabelSize(0.12);
      hframe2.GetYaxis()->SetNdivisions(205);
  
      hframe2.GetYaxis()->SetTitle("MC / fit");
      hframe2.Draw();
    
      CommonFunc::DrawConstantLine(&pad2, 1,  xMinArr[imass][iwidth],xMaxArr[imass][iwidth],kBlue,3,2);
      CommonFunc::DrawConstantLine(&pad2, 0.5,xMinArr[imass][iwidth],xMaxArr[imass][iwidth],kRed,2,2);
      CommonFunc::DrawConstantLine(&pad2, 1.5,xMinArr[imass][iwidth],xMaxArr[imass][iwidth],kRed,2,2);
    
      double currChi2Prob=0;
    
      // TGraphErrors *subtraction=plotDivision(MCCat[imass][iwidth], pdfCat[imass][iwidth], xCat[imass][iwidth], nBinArr[imass][iwidth],currChi2Prob);
      // subtraction->Draw("EPSAME");

      TH1F *hpdf=(TH1F*)histData[imass][iwidth]->Clone("pdf");
      hpdf->Reset();
      pdfCat[imass][iwidth]->fillHistogram(hpdf, RooArgList(*xCat[imass][iwidth]));
      CommonFunc::ScaleToOne(hpdf);
      for(int ibin=1;ibin<=hpdf->GetNbinsX();ibin++) hpdf->SetBinError(ibin,0);

      SignificanceHist tool(*histData[imass][iwidth], *hpdf);
      TH1F *hratio=tool.GetRatioHist(0.5);
      hratio->Draw("same,E");
      
      system("mkdir -vp fig/fit/"+jobname);
      TString outputCanvasName="fig/fit/"+jobname+Form("/plot_%.0f_%.2f", massArr[imass], widthArr[iwidth]);
      if(option.Contains("logy")){
	canvas.SetLogy();
	outputCanvasName+="_logy";
      }
      CommonFunc::PrintCanvas(&canvas, outputCanvasName);
      // wsCat[imass][iwidth]->import(*MCCat[imass][iwidth]);
      // wsCat[imass][iwidth]->writeToFile(outputCanvasName+"_ws.root");
    }
  }
  // pad1->RedrawAxis();
}

