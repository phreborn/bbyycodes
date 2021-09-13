#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"
#include "gravitonNtup.h"
#include "statistics.hh"

using namespace std;
using namespace RooFit;
using namespace RooStats;

const double epsilon=1e-4;

int FileNameToMassIdx(TString fileName){
  // genData_ggH1100_W10p.root
  if(fileName.Contains("_m500_"))   return 0;
  if(fileName.Contains("_m750_"))   return 1;
  if(fileName.Contains("_m1000_"))  return 2;
  if(fileName.Contains("_m1500_"))  return 3;
  if(fileName.Contains("_m2500_"))  return 4;
  if(fileName.Contains("_m3500_"))  return 5;
  if(fileName.Contains("_m4000_"))  return 6;
  if(fileName.Contains("_m5000_"))  return 7;
  return -1;
}

int FileNameToWidthIdx(TString fileName){
  if(fileName.Contains("_k001."))    return 0;
  if(fileName.Contains("_k005."))    return 1;
  if(fileName.Contains("_k01."))     return 2;
  if(fileName.Contains("_k015."))    return 3;
  if(fileName.Contains("_k02."))     return 4;
  if(fileName.Contains("_k025."))    return 5;
  if(fileName.Contains("_k03."))     return 6;
  if(fileName.Contains("_k035."))    return 7;
  if(fileName.Contains("_k037."))    return 8;
  if(fileName.Contains("_k04."))     return 9;
  return -1;
}

TGraphErrors* plotDivision(RooAbsData *data, RooAbsPdf *pdf, 
			   RooRealVar *observable, double xBins,
			   double &chi2Prob) {
  // Store the original variable range:
  double minOrigin = observable->getMin();
  double maxOrigin = observable->getMax();
  //double nEvents = data->sumEntries();
  double nEvents = data->sumEntries(Form("%s>%f&&%s<%f",
					 observable->GetName(), minOrigin,
					 observable->GetName(), maxOrigin));
  TH1F *originHist
    = (TH1F*)data->createHistogram("dataSub", *observable,
				   RooFit::Binning(xBins,minOrigin,maxOrigin));
  TGraphErrors *result = new TGraphErrors();
  double increment = ((maxOrigin - minOrigin) / ((double)xBins));
  observable->setRange("fullRange", minOrigin, maxOrigin);
  RooAbsReal* intTot
    = (RooAbsReal*)pdf->createIntegral(RooArgSet(*observable),
				       RooFit::NormSet(*observable), 
				       RooFit::Range("fullRange"));
  double valTot = intTot->getVal();
  int pointIndex = 0; int pointIndexNonZero = 0;
  for (double i_m = minOrigin; i_m < maxOrigin; i_m += increment) {
    observable->setRange(Form("range%2.2f",i_m), i_m, (i_m+increment));
    RooAbsReal* intCurr
      = (RooAbsReal*)pdf->createIntegral(RooArgSet(*observable), 
					 RooFit::NormSet(*observable), 
					 RooFit::Range(Form("range%2.2f",i_m)));
    double valCurr = intCurr->getVal();
    
    double currMass = i_m + (0.5*increment);
    double currPdfWeight = nEvents * (valCurr / valTot);
    TString varName = observable->GetName();
    double currDataWeight
      = data->sumEntries(Form("%s>%f&&%s<%f",varName.Data(),
			      i_m,varName.Data(), (i_m+increment)));
    double currWeight = currDataWeight / currPdfWeight;
    double currError = originHist->GetBinError(pointIndex+1) / currPdfWeight;

    if(currWeight>epsilon&&currError>epsilon){
      result->SetPoint(pointIndex, currMass, currWeight);
      result->SetPointError(pointIndex, 0.0, currError);
    }
    pointIndex++;
    
    double currChi2 = (((currDataWeight-currPdfWeight) * 
    			(currDataWeight-currPdfWeight)) / 
    		       ((originHist->GetBinError(pointIndex+1)) * 
    			(originHist->GetBinError(pointIndex+1))));
    if (std::isfinite(currChi2)) {
      chi2Prob += currChi2;
      pointIndexNonZero++;
    }
  }
  // Return to the original variable range, store the chi^2 value:
  observable->setMin(minOrigin);
  observable->setMax(maxOrigin);
  chi2Prob = TMath::Prob(chi2Prob, pointIndexNonZero);
  delete originHist;
  return result;
}

int main(int argc, char **argv){
  if(argc<3){
    cout<<"Usage: "<<argv[0]<<" <jobname> <input file list> <option>"<<endl;
    exit(0);
  }
  CommonFunc::SetAtlasStyle();
  TString jobname=argv[1];
  TString inputFileList=argv[2];
  TString option=argv[3];

  option+="EKHI";
  
  TString wsFileName="";
  if(option.Contains("EKHI")) wsFileName="workspace/high_mass_diphoton/2015_Graviton_histfactory_EKHI_v7.root";
  unique_ptr<TFile> f(TFile::Open(wsFileName,"read"));
  RooWorkspace *ws=dynamic_cast<RooWorkspace*>(f->Get("combWS"));
  
  RooAbsPdf *pdf=ws->pdf("pdf_signal_inclusive_13TeV");
  RooRealVar *x=ws->var("obs_x_channel");
  ws->var("mG")->setRange(0,10000);
  ws->var("GkM")->setRange(0,1);
  ws->var("ATLAS_mRes")->setVal(0);

  // Get the file list. who cares!

  unique_ptr<TChain> c(CommonFunc::MakeChain("CollectionTree",inputFileList,"badfile", inputFileList.Contains(".root")));

  gravitonNtup *p=new gravitonNtup(c.get());
  
  const int nmass=8, nwidth=10;
  double massArr[nmass]={500, 750, 1000, 1500, 2500, 3500, 4000, 5000};
  double widthArr[nwidth] ={0.01, 0.05, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.37, 0.40};

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
	if(massArr[imass]==1000) binw=5;
	if(massArr[imass]==500) binw=2;
	if(massArr[imass]==750) binw=2;
      }
      if(widthArr[iwidth]==0.05){
	if(massArr[imass]==1000) binw=5;
	if(massArr[imass]==500) binw=5;
	if(massArr[imass]==750) binw=5;
      }
      if(widthArr[iwidth]==0.10){
	if(massArr[imass]==1000) binw=5;
	if(massArr[imass]==500) binw=5;
	if(massArr[imass]==750) binw=5;
	if(massArr[imass]==1500) binw=10;
      }
      if(widthArr[iwidth]==0.15){
	if(massArr[imass]==1000) binw=10;
	if(massArr[imass]==500) binw=5;
	if(massArr[imass]==750) binw=10;
      }
      if(widthArr[iwidth]==0.2){
	if(massArr[imass]==1000) binw=20;
	if(massArr[imass]==500) binw=10;
	if(massArr[imass]==750) binw=10;
      }
      if(widthArr[iwidth]==0.25){
	if(massArr[imass]==1000) binw=20;
	if(massArr[imass]==500) binw=20;
	if(massArr[imass]==750) binw=20;
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

    double weight=p->total_weight;
    if(option.Contains("EKHI")){
      p->accepted=p->pass_ld_subld_id&&(p->pt_leading>55*1e3)&&(p->pt_subleading>55*1e3)&&(p->topoetcone40_leading<0.022*p->pt_leading+2450)&&(p->topoetcone40_subleading<0.022*p->pt_subleading+2450)&&(p->ptcone20_leading<0.05*p->pt_leading)&&(p->ptcone20_subleading<0.05*p->pt_subleading);
    }
    if(imass<0||iwidth<0) continue;
    if(p->accepted*weight==0) continue;

    histData[imass][iwidth]->Fill(p->mgg, weight);
    // xCat[imass][iwidth]->setVal(p->mgg);
    // wCat[imass][iwidth]->setVal(weight);
    // // cout<<x->getVal()<<" "<<w.getVal()<<endl; getchar();
    // // cout<<p->mgg<<" "<<weight<<" "<<xMinArr[imass][iwidth]<<" "<<xMaxArr[imass][iwidth]<<endl;
    // if(p->mgg>xMinArr[imass][iwidth]&&p->mgg<xMaxArr[imass][iwidth])
    //   MCCat[imass][iwidth]->add(RooArgSet(*xCat[imass][iwidth], *wCat[imass][iwidth]), weight);
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

      // TPad pad1("pad1", "pad1", 0.00, 0.33, 1.00, 1.00);
      // TPad pad2("pad2", "pad2", 0.00, 0.00, 1.00, 0.33);
      // pad1.SetBottomMargin(0.00001);
      // pad1.SetBorderMode(0);
      // pad2.SetTopMargin(0.00001);
      // pad2.SetBottomMargin(0.4);
      // pad2.SetBorderMode(0);
      canvas.cd();
      // pad1.Draw();
      // pad2.Draw();
      // pad1.cd();

      // MCCat[imass][iwidth]->plotOn(frameCat[imass][iwidth], DataError(RooAbsData::SumW2), Binning(nBinArr[imass][iwidth]));
      wsCat[imass][iwidth]->var("mG")->setVal(massArr[imass]);
      wsCat[imass][iwidth]->var("GkM")->setVal(widthArr[iwidth]);
      wsCat[imass][iwidth]->var("mG")->Print();
      wsCat[imass][iwidth]->var("GkM")->Print();
      pdfCat[imass][iwidth]->plotOn(frameCat[imass][iwidth], LineColor(CommonFunc::ColorWheel(imass+1)), Normalization(histData[imass][iwidth]->Integral()));

      // TH1D hframe("hframe","hframe", nBinArr[imass][iwidth], xMinArr[imass][iwidth], xMaxArr[imass][iwidth]);
      // if(option.Contains("logy")){
      // 	hframe.SetMinimum(10);
      // 	if(widthArr[iwidth]==0.01) hframe.SetMinimum(1);
      // 	hframe.SetMaximum(5e3);
      // }
      // else{
      // 	hframe.SetMinimum(0);
      // 	hframe.SetMaximum(0.23);
      // 	// if(widthArr[iwidth]==0.01){
      // 	//   if(massArr[imass]==500) hframe.SetMaximum(2000);
      // 	//   if(massArr[imass]==750) hframe.SetMaximum(500);
      // 	//   if(massArr[imass]==1000) hframe.SetMaximum(3.2e3);
      // 	//   if(massArr[imass]==1500) hframe.SetMaximum(1500);
      // 	//   if(massArr[imass]==2500) hframe.SetMaximum(2500);
      // 	//   if(massArr[imass]==3500) hframe.SetMaximum(2500);
      // 	// }
      // 	// if(widthArr[iwidth]==0.05){
      // 	//   if(massArr[imass]==500) hframe.SetMaximum(4000);
      // 	//   if(massArr[imass]==750) hframe.SetMaximum(3000);
      // 	//   if(massArr[imass]==1000) hframe.SetMaximum(2500);
      // 	//   if(massArr[imass]==1500) hframe.SetMaximum(3000);
      // 	//   if(massArr[imass]==2500) hframe.SetMaximum(4500);
      // 	//   if(massArr[imass]==3500) hframe.SetMaximum(4500);
      // 	// }
      // 	// if(widthArr[iwidth]==0.10){
      // 	//   if(massArr[imass]==500) hframe.SetMaximum(2500);
      // 	//   if(massArr[imass]==750) hframe.SetMaximum(600);
      // 	//   if(massArr[imass]==1000) hframe.SetMaximum(1800);
      // 	//   if(massArr[imass]==1500) hframe.SetMaximum(1800);
      // 	// }
      // 	// if(widthArr[iwidth]==0.15){
      // 	//   if(massArr[imass]==500) hframe.SetMaximum(1800);
      // 	//   if(massArr[imass]==750) hframe.SetMaximum(800);
      // 	//   if(massArr[imass]==1000) hframe.SetMaximum(2000);
      // 	// }
      // 	// if(widthArr[iwidth]==0.20){
      // 	//   if(massArr[imass]==500) hframe.SetMaximum(500);
      // 	//   if(massArr[imass]==750) hframe.SetMaximum(500);
      // 	//   if(massArr[imass]==1000) hframe.SetMaximum(2.5e3);
      // 	// }
      // 	// if(widthArr[iwidth]==0.25){
      // 	//   if(massArr[imass]==500) hframe.SetMaximum(800);
      // 	//   if(massArr[imass]==750) hframe.SetMaximum(1800);
      // 	//   if(massArr[imass]==1000) hframe.SetMaximum(1800);
      // 	// }
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
      if(option.Contains("note")) l.DrawLatex(0.47, 0.85, "#bf{#it{ATLAS}} Simulation Preliminary");
      else if(option.Contains("paper")) l.DrawLatex(0.5, 0.85, "#bf{#it{ATLAS}} Simulation");
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
      // pad2.cd();
    
      // TH1D hframe2("hframe2","hframe2",nBinArr[imass][iwidth],xMinArr[imass][iwidth],xMaxArr[imass][iwidth]);
      // hframe2.SetMinimum(0.1);
      // hframe2.SetMaximum(1.9);
      // hframe2.SetLineWidth(2);
      // hframe2.GetXaxis()->SetTitle("m_{X} [GeV]");
      // hframe2.GetXaxis()->SetTitleOffset(1);
      // hframe2.GetYaxis()->SetTitleOffset(0.5);
      // hframe2.GetXaxis()->SetTitleSize(0.15);
      // hframe2.GetYaxis()->SetTitleSize(0.12);
      // hframe2.GetXaxis()->SetLabelSize(0.12);
      // hframe2.GetYaxis()->SetLabelSize(0.12);
      // hframe2.GetYaxis()->SetNdivisions(205);
  
      // hframe2.GetYaxis()->SetTitle("MC / fit");
      // hframe2.Draw();
    
      // CommonFunc::DrawConstantLine(&pad2, 1,  xMinArr[imass][iwidth],xMaxArr[imass][iwidth],kRed,3,2);
      // CommonFunc::DrawConstantLine(&pad2, 0.5,xMinArr[imass][iwidth],xMaxArr[imass][iwidth],kRed,2,2);
      // CommonFunc::DrawConstantLine(&pad2, 1.5,xMinArr[imass][iwidth],xMaxArr[imass][iwidth],kRed,2,2);
    
      // double currChi2Prob=0;
    
      // TGraphErrors *subtraction=plotDivision(MCCat[imass][iwidth], pdfCat[imass][iwidth], xCat[imass][iwidth], nBinArr[imass][iwidth],currChi2Prob);
      // subtraction->Draw("EPSAME");

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

