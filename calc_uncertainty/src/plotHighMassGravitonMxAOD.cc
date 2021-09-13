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
  if(fileName.Contains("_500."))   return 0;
  if(fileName.Contains("_550."))   return 1;
  if(fileName.Contains("_600."))   return 2;
  if(fileName.Contains("_650."))   return 3;
  if(fileName.Contains("_700."))   return 4;
  if(fileName.Contains("_750."))   return 5;
  if(fileName.Contains("_800."))   return 6;
  if(fileName.Contains("_850."))   return 7;
  if(fileName.Contains("_900."))   return 8;
  if(fileName.Contains("_950."))   return 9;
  if(fileName.Contains("_1000."))  return 10;
  if(fileName.Contains("_1500."))  return 11;
  if(fileName.Contains("_2000."))  return 12;
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
  if(fileName.Contains("_001_"))    return 0;
  if(fileName.Contains("_005_"))    return 1;
  if(fileName.Contains("_01_"))     return 2;
  if(fileName.Contains("_015_"))    return 3;
  if(fileName.Contains("_02_"))     return 4;
  if(fileName.Contains("_025_"))    return 5;
  if(fileName.Contains("_03_"))     return 6;
  if(fileName.Contains("_035_"))    return 7;
  if(fileName.Contains("_037_"))    return 8;
  if(fileName.Contains("_04_"))     return 9;
  return -1;
}

//_____________________________________________________________________________
// Matrix element correction
Double_t ME(Double_t mgg){
  return mgg*mgg*mgg*mgg*mgg*mgg;
}

//_____________________________________________________________________________
// Parton luminosity correction
Double_t PL(Double_t mgg){
  Double_t mgg_norm=mgg/13000., _alpha=1.5;	// Normalize mgg by sqrt(s)
  double Lgg = pow(1-pow(mgg_norm,0.982575/3),11.2968)*pow(mgg_norm,-2.58083)*(1.89206e-6);
  double Lqq = pow(1-pow(mgg_norm,1./3),8.0919)*pow(mgg_norm,-2.26565)*(8.43489e-8);
  return Lgg+_alpha*Lqq;
}
  
//_____________________________________________________________________________
// Mediocre Breit-Wigner
Double_t BW(Double_t mgg, Double_t _mean, Double_t _width){
  return 1/((mgg*mgg-_mean*_mean)*(mgg*mgg-_mean*_mean)+(_mean*_width)*(_mean*_width));
}

double FlatSampleWeight(double _x, double _mean, double _width){
  return ME(_x)*PL(_x)*BW(_x, _mean, _width)*_x;
}

int main(int argc, char **argv){
  if(argc<3){
    cout<<"Usage: "<<argv[0]<<" <jobname> <input file list> <option>"<<endl;
    exit(0);
  }
  CommonFunc::SetAtlasStyle();
  TString jobname=argv[1];
  TString wsFileName=argv[2];
  TString inputFileList=argv[3];
  TString option=argv[4];

  unique_ptr<TFile> f(TFile::Open(wsFileName,"read"));
  RooWorkspace *ws=dynamic_cast<RooWorkspace*>(f->Get("combWS"));
  ModelConfig *mc=(ModelConfig*)ws->obj("ModelConfig");
  RooAbsPdf *pdf=(RooAbsPdf*)ws->allPdfs().selectByName("pdf__signal_*")->first();
  RooRealVar *x=(RooRealVar*)mc->GetObservables()->first();

  ws->var("mG")->setRange(0,10000);
  ws->var("GkM")->setRange(0,1);
  ws->var("ATLAS_mRes")->setVal(0);

  unique_ptr<TChain> c(CommonFunc::MakeChain("CollectionTree",inputFileList,"badfile", inputFileList.Contains(".root")));

  MxAODNtup *p=new MxAODNtup(c.get());
  
  const int nmass=20, nwidth=10;
  double massArr[nmass]={500, 550, 600, 650, 700,
			 750, 800, 850, 900, 950,
			 1000, 1500, 2000, 2500, 3000,
			 3500, 4000, 4500, 5000, 5500};
  
  double widthArr[nwidth] ={0.01, 0.05, 0.10, 0.15, 0.20,
			    0.25, 0.30, 0.35, 0.37, 0.40};

  RooWorkspace *wsCat[nmass][nwidth];
  RooDataSet* MCCat[nmass][nwidth];
  RooRealVar* xCat[nmass][nwidth], *wCat[nmass][nwidth];
  RooAbsPdf* pdfCat[nmass][nwidth];
  RooPlot* frameCat[nmass][nwidth];
  double xMinArr[nmass][nwidth], xMaxArr[nmass][nwidth];
  int nBinArr[nmass][nwidth];
  TH1D *histData[nmass][nwidth];
  
  for(int imass=0;imass<nmass;imass++){
    for(int iwidth=0;iwidth<nwidth;iwidth++){
      double width=1.44*massArr[imass]*widthArr[iwidth]*widthArr[iwidth];
      if(width<12) width=12;
      wsCat[imass][iwidth]=new RooWorkspace(Form("wsCat_%.0f_%.2f", massArr[imass], widthArr[iwidth]));
      wsCat[imass][iwidth]->import(*pdf);
      cout<<"Okay here"<<endl;
      pdfCat[imass][iwidth]=wsCat[imass][iwidth]->pdf(pdf->GetName());
      xCat[imass][iwidth]=wsCat[imass][iwidth]->var(x->GetName());
      cout<<"Okay here"<<endl;
      
      xMaxArr[imass][iwidth]=massArr[imass]+8*width;
      xMinArr[imass][iwidth]=massArr[imass]-4*width;
      if(option.Contains("logy")){
	xMaxArr[imass][iwidth]=massArr[imass]+10*width;
	if(widthArr[iwidth]==0.01){
	  xMinArr[imass][iwidth]=massArr[imass]-6*width;
	  xMaxArr[imass][iwidth]=massArr[imass]+14*width;
	}
      }
      double binw=5;
      if(widthArr[iwidth]==0.01){
	if(massArr[imass]<1000) binw=2;
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
	if(massArr[imass]<1000) binw=10;
	else if(massArr[imass]<=3000) binw=20;
	else binw=40;
      }
      if(widthArr[iwidth]==0.25){
	if(massArr[imass]<=1000) binw=20;
	else if(massArr[imass]<=3000) binw=40;
	else binw=50;
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

      histData[imass][iwidth]=new TH1D(Form("hist_%.0f_%.2f",massArr[imass], widthArr[iwidth]),Form("hist_%.0f_%.2f",massArr[imass], widthArr[iwidth]), nBinArr[imass][iwidth], xMinArr[imass][iwidth], xMaxArr[imass][iwidth]);
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
    if(option.Contains("flat")){ imass=10; iwidth=4;} // mG=1000 GeV, GkM=0.2
    double weight=p->weight;
    // double weight=p->vertexWeight*p->mcEventWeights->at(0);
    // if(option.Contains("flat")) weight*=FlatSampleWeight(p->m_yy_truth/GeV, massArr[imass], 1.44*widthArr[iwidth]*widthArr[iwidth]*massArr[imass]);
    if(!isfinite(weight)) continue;
    if(imass<0||iwidth<0) continue;
    if(option.Contains("EKHI")){
      if(!(bool(p->isPassedIsolationLowHighMyy)&&bool(p->isPassedExotic)&&!bool(p->isDalitz))) continue;
    }
    if(option.Contains("HKHI")){
      if(!(bool(p->isPassedLowHighMyy)&&!bool(p->isDalitz))) continue;
    }
    histData[imass][iwidth]->Fill(p->m_yy/GeV, weight);
  }

  cout<<"okay here"<<endl;
  for(int imass=0;imass<nmass;imass++){
    for(int iwidth=0;iwidth<nwidth;iwidth++){
      if(histData[imass][iwidth]->Integral()<=0){
	cout<<"0 events for "<<massArr[imass]<<" and "<<widthArr[iwidth]<<endl;
	continue;
      }

      CommonFunc::ScaleToOne(histData[imass][iwidth],true);

      // MCCat[imass][iwidth]=statistics::histToDataSet(histData[imass][iwidth],xCat[imass][iwidth],wCat[imass][iwidth]);
      // if(iwidth!=3) continue;
      TCanvas canvas("c","c",800,600);

      TPad *pad1, *pad2;
      if(option.Contains("subtract")){
	pad1=new TPad("pad1", "pad1", 0.00, 0.33, 1.00, 1.00);
	pad2=new TPad("pad2", "pad2", 0.00, 0.00, 1.00, 0.33);
	pad1->SetBottomMargin(0.00001);
	pad1->SetBorderMode(0);
	pad2->SetTopMargin(0.00001);
	pad2->SetBottomMargin(0.4);
	pad2->SetBorderMode(0);
	// canvas.cd();
	pad1->Draw();
	pad2->Draw();
	pad1->cd();
      }
      
      // MCCat[imass][iwidth]->plotOn(frameCat[imass][iwidth], DataError(RooAbsData::SumW2), Binning(nBinArr[imass][iwidth]));
      wsCat[imass][iwidth]->var("mG")->setVal(massArr[imass]);
      wsCat[imass][iwidth]->var("GkM")->setVal(widthArr[iwidth]);
      wsCat[imass][iwidth]->var("mG")->Print();
      wsCat[imass][iwidth]->var("GkM")->Print();

      Color_t color=CommonFunc::ColorWheel(imass+1);
      if(option.Contains("green")) color=kGreen+2;
      pdfCat[imass][iwidth]->plotOn(frameCat[imass][iwidth], LineColor(color), Normalization(histData[imass][iwidth]->Integral()));

      // TH1D hframe("hframe","hframe", nBinArr[imass][iwidth], xMinArr[imass][iwidth], xMaxArr[imass][iwidth]);
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
      histData[imass][iwidth]->GetYaxis()->SetTitle(Form("1/N dN/dm_{#gamma#gamma} [GeV^{-1}]",(xMaxArr[imass][iwidth]-xMinArr[imass][iwidth])/double(nBinArr[imass][iwidth])));
      histData[imass][iwidth]->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
      histData[imass][iwidth]->GetXaxis()->SetTitleSize(0.06);
      histData[imass][iwidth]->GetYaxis()->SetTitleSize(0.06);
      histData[imass][iwidth]->GetYaxis()->SetTitleOffset(1.3);
      histData[imass][iwidth]->SetLineWidth(1.5);
      histData[imass][iwidth]->SetMaximum(histData[imass][iwidth]->GetMaximum()*1.2);
      histData[imass][iwidth]->Draw();
      histData[imass][iwidth]->SetMinimum(0);
      frameCat[imass][iwidth]->Draw("same");
      histData[imass][iwidth]->Draw("same,E");
      TLatex l; //l.SetTextAlign(12); l.SetTextSize(tsize);
      l.SetNDC();
      l.SetTextColor(1);
      l.SetTextSize(0.05);
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

      if(option.Contains("subtract")){
	pad2->cd();
	
	TH1D hframe2("hframe2","hframe2",nBinArr[imass][iwidth],xMinArr[imass][iwidth],xMaxArr[imass][iwidth]);
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
	
	CommonFunc::DrawConstantLine(pad2, 1,  xMinArr[imass][iwidth],xMaxArr[imass][iwidth],kBlue,3,2);
	CommonFunc::DrawConstantLine(pad2, 0.5,xMinArr[imass][iwidth],xMaxArr[imass][iwidth],kRed,2,2);
	CommonFunc::DrawConstantLine(pad2, 1.5,xMinArr[imass][iwidth],xMaxArr[imass][iwidth],kRed,2,2);
    
	double currChi2Prob=0;
	
	// TGraphErrors *subtraction=plotDivision(MCCat[imass][iwidth], pdfCat[imass][iwidth], xCat[imass][iwidth], nBinArr[imass][iwidth],currChi2Prob);
	// subtraction->Draw("EPSAME");
	
	TH1D *hpdf=(TH1D*)histData[imass][iwidth]->Clone("pdf");
	hpdf->Reset();
	pdfCat[imass][iwidth]->fillHistogram(hpdf, RooArgList(*xCat[imass][iwidth]));
	CommonFunc::ScaleToOne(hpdf);
	for(int ibin=1;ibin<=hpdf->GetNbinsX();ibin++) hpdf->SetBinError(ibin,0);

	// SignificanceHist tool(*histData[imass][iwidth], *(TH1F*)hpdf);
	// TH1D *hratio=tool.GetRatioHist(0.5);
	// hratio->Draw("same,E");
      }
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

