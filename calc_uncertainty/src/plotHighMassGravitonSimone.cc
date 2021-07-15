#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"
#include "gravitonNtup.h"

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
  if(fileName.Contains("_m2000_"))  return 4;
  if(fileName.Contains("_m3000_"))  return 5;
  if(fileName.Contains("_m4000_"))  return 6;
  if(fileName.Contains("_m5000_"))  return 7;
  return -1;
}

int FileNameToWidthIdx(TString fileName){
  if(fileName.Contains("_k001_"))    return 0;
  if(fileName.Contains("_k005_"))    return 1;
  if(fileName.Contains("_k01_"))     return 2;
  if(fileName.Contains("_k015_"))    return 3;
  if(fileName.Contains("_k02_"))     return 4;
  if(fileName.Contains("_k025_"))    return 5;
  if(fileName.Contains("_k03_"))     return 6;
  if(fileName.Contains("_k035_"))    return 7;
  if(fileName.Contains("_k037_"))    return 8;
  if(fileName.Contains("_k04_"))     return 9;
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

  unique_ptr<TFile> f(TFile::Open("workspace/high_mass_diphoton/2015_Graviton_2D_wide.root","read"));
  RooWorkspace *ws=dynamic_cast<RooWorkspace*>(f->Get("combWS"));
  
  RooAbsPdf *pdf=ws->pdf("pdf_signal_inclusive_13TeV");
  RooRealVar *x=ws->var("atlas_invMass");
  ws->var("mG")->setRange(0,10000);
  ws->var("GkM")->setRange(0,1);
  ws->var("ATLAS_mRes")->setVal(0);

  // Get the file list. who cares!

  unique_ptr<TChain> c(CommonFunc::MakeChain("CollectionTree",inputFileList,"badfile", inputFileList.Contains(".root")));

  gravitonNtup *p=new gravitonNtup(c.get());
  
  const int nmass=8, nwidth=10;
  double massArr[nmass]={500, 750, 1000, 1500, 2000, 3000, 4000, 5000};
  double widthArr[nwidth] ={0.01, 0.05, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.37, 0.40};
  
  RooWorkspace *wsCat[nmass][nwidth];
  RooDataSet* MCCat[nmass][nwidth];
  RooRealVar* xCat[nmass][nwidth], *wCat[nmass][nwidth];
  RooAbsPdf* pdfCat[nmass][nwidth];
  RooPlot* frameCat[nmass][nwidth];
  double xMinArr[nmass][nwidth], xMaxArr[nmass][nwidth];
  int nBinArr[nmass][nwidth];
  
  for(int imass=0;imass<nmass;imass++){
    for(int iwidth=0;iwidth<nwidth;iwidth++){
      double width=1.44*massArr[imass]*widthArr[iwidth]*widthArr[iwidth];
      if(width<5) width=5;
      
      wsCat[imass][iwidth]=new RooWorkspace(Form("wsCat_%.0f_%.2f", massArr[imass], widthArr[iwidth]));
      wsCat[imass][iwidth]->import(*pdf);
      pdfCat[imass][iwidth]=wsCat[imass][iwidth]->pdf(pdf->GetName());
      xCat[imass][iwidth]=wsCat[imass][iwidth]->var(x->GetName());

      
      xMaxArr[imass][iwidth]=massArr[imass]+10*width;
      xMinArr[imass][iwidth]=massArr[imass]-10*width;

      double binw=int(width/5.);
      if(binw<0.005*massArr[imass]) binw=0.005*massArr[imass];
      nBinArr[imass][iwidth]=int((xMaxArr[imass][iwidth]-xMinArr[imass][iwidth])/binw)+1;
      xMinArr[imass][iwidth]=xMaxArr[imass][iwidth]-nBinArr[imass][iwidth]*binw;

      xCat[imass][iwidth]->setRange(xMinArr[imass][iwidth], xMaxArr[imass][iwidth]);

      cout<<massArr[imass]<<" "<<widthArr[iwidth]<<" "<<xMinArr[imass][iwidth]<<" "<<xMaxArr[imass][iwidth]<<" "<<nBinArr[imass][iwidth]<<endl;
      frameCat[imass][iwidth]=xCat[imass][iwidth]->frame();

      wCat[imass][iwidth]=new RooRealVar(Form("w_%.0f_%.2f",massArr[imass], widthArr[iwidth]),Form("w_%.0f_%.2f",massArr[imass], widthArr[iwidth]),1);

      MCCat[imass][iwidth]=new RooDataSet(Form("MC_%.0f_%.2f",massArr[imass], widthArr[iwidth]),Form("MC_%.0f_%.2f",massArr[imass], widthArr[iwidth]), RooArgSet(*xCat[imass][iwidth],*wCat[imass][iwidth]), WeightVar(*wCat[imass][iwidth]));

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
    if(option.Contains("flat")) weight=p->flat_weight;
    if(imass<0||iwidth<0) continue;
    if(p->accepted*weight==0) continue;

    xCat[imass][iwidth]->setVal(p->mgg);
    wCat[imass][iwidth]->setVal(weight);
    // cout<<x->getVal()<<" "<<w.getVal()<<endl; getchar();
    // cout<<p->mgg<<" "<<weight<<" "<<xMinArr[imass][iwidth]<<" "<<xMaxArr[imass][iwidth]<<endl;
    if(p->mgg>xMinArr[imass][iwidth]&&p->mgg<xMaxArr[imass][iwidth])
      MCCat[imass][iwidth]->add(RooArgSet(*xCat[imass][iwidth], *wCat[imass][iwidth]), weight);
  }

  cout<<"okay here"<<endl;
  for(int imass=0;imass<nmass;imass++){
    for(int iwidth=0;iwidth<nwidth;iwidth++){
      if(MCCat[imass][iwidth]->sumEntries()<=0){
	cout<<"0 events for "<<massArr[imass]<<" and "<<widthArr[iwidth]<<endl;
	continue;
      }
      // if(iwidth!=3) continue;
      TCanvas canvas("c","c",800,600);

      TPad pad1("pad1", "pad1", 0.00, 0.33, 1.00, 1.00);
      TPad pad2("pad2", "pad2", 0.00, 0.00, 1.00, 0.33);
      pad1.SetBottomMargin(0.00001);
      pad1.SetBorderMode(0);
      pad2.SetTopMargin(0.00001);
      pad2.SetBottomMargin(0.4);
      pad2.SetBorderMode(0);
      canvas.cd();
      pad1.Draw();
      pad2.Draw();
      pad1.cd();

      MCCat[imass][iwidth]->plotOn(frameCat[imass][iwidth], DataError(RooAbsData::SumW2), Binning(nBinArr[imass][iwidth]));
      wsCat[imass][iwidth]->var("mG")->setVal(massArr[imass]);
      wsCat[imass][iwidth]->var("GkM")->setVal(widthArr[iwidth]);
      wsCat[imass][iwidth]->var("mG")->Print();
      wsCat[imass][iwidth]->var("GkM")->Print();
      pdfCat[imass][iwidth]->plotOn(frameCat[imass][iwidth], LineColor(CommonFunc::ColorWheel(imass+1)));

      frameCat[imass][iwidth]->GetYaxis()->SetTitle(Form("Events / %.1f GeV",(xMaxArr[imass][iwidth]-xMinArr[imass][iwidth])/double(nBinArr[imass][iwidth])));
      frameCat[imass][iwidth]->GetYaxis()->SetTitleSize(0.07);
      frameCat[imass][iwidth]->GetYaxis()->SetTitleOffset(0.9);

      if(option.Contains("logy")){
	TH1D hframe("hframe","hframe", nBinArr[imass][iwidth], xMinArr[imass][iwidth], xMaxArr[imass][iwidth]);
	hframe.SetMinimum(epsilon);
	hframe.SetMaximum(2*frameCat[imass][iwidth]->GetMaximum());
	hframe.SetLineWidth(0);
	hframe.GetYaxis()->SetTitle(Form("Events / %.1f GeV",(xMaxArr[imass][iwidth]-xMinArr[imass][iwidth])/double(nBinArr[imass][iwidth])));
	hframe.GetYaxis()->SetTitleSize(0.07);
	hframe.GetYaxis()->SetTitleOffset(0.9);

	hframe.Draw();
      }
      
      frameCat[imass][iwidth]->Draw("same");
      TLatex l; //l.SetTextAlign(12); l.SetTextSize(tsize);
      l.SetNDC();
      l.SetTextColor(1);
      l.SetTextSize(0.08);
      l.DrawLatex(0.2, 0.85, Form("m_{G} = %.0f GeV", massArr[imass]));
      l.DrawLatex(0.2, 0.75, Form("#kappa/#bar{M}_{Pl} = %.2f", widthArr[iwidth]));

      pad2.cd();
    
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
    
      CommonFunc::DrawConstantLine(&pad2, 1,  xMinArr[imass][iwidth],xMaxArr[imass][iwidth],kRed,3,2);
      CommonFunc::DrawConstantLine(&pad2, 0.5,xMinArr[imass][iwidth],xMaxArr[imass][iwidth],kRed,2,2);
      CommonFunc::DrawConstantLine(&pad2, 1.5,xMinArr[imass][iwidth],xMaxArr[imass][iwidth],kRed,2,2);
    
      double currChi2Prob=0;
    
      TGraphErrors *subtraction=plotDivision(MCCat[imass][iwidth], pdfCat[imass][iwidth], xCat[imass][iwidth], nBinArr[imass][iwidth],currChi2Prob);
      subtraction->Draw("EPSAME");

      system("mkdir -vp fig/fit/"+jobname);
      TString outputCanvasName="fig/fit/"+jobname+Form("/plot_%.0f_%.2f", massArr[imass], widthArr[iwidth]);
      if(option.Contains("logy")){
	pad1.SetLogy();
	outputCanvasName+="_logy";
      }
      CommonFunc::PrintCanvas(&canvas, outputCanvasName);
      // wsCat[imass][iwidth]->import(*MCCat[imass][iwidth]);
      // wsCat[imass][iwidth]->writeToFile(outputCanvasName+"_ws.root");
    }
  }
  // pad1->RedrawAxis();
}

