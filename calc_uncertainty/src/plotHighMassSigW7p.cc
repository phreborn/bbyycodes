#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"

using namespace std;
using namespace RooFit;
using namespace RooStats;

const double epsilon=-1e-4;

int FileNameToCat(TString fileName){
  if(fileName.Contains("H400")) return 0;
  if(fileName.Contains("H800")) return 1;
  if(fileName.Contains("H1500")) return 2;
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

TGraphErrors* plotSubtraction(RooAbsData *data, RooAbsPdf *pdf, 
			      RooRealVar *observable, double xBins,
			      double &chi2Prob) {
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
  double increment = (maxOrigin - minOrigin) / ((double)xBins);
  
  RooAbsReal* intTot
    = (RooAbsReal*)pdf->createIntegral(RooArgSet(*observable),
				       RooFit::NormSet(*observable), 
				       RooFit::Range("fullRange"));
  double valTot = intTot->getVal();
  
  int pointIndex = 0;
  
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
    double currDataWeight = data->sumEntries(Form("%s>%f&&%s<%f",varName.Data(),
						  i_m,varName.Data(),
						  (i_m+increment)));
    double currWeight = currDataWeight - currPdfWeight;
    result->SetPoint(pointIndex, currMass, currWeight);
    
    double currError = originHist->GetBinError(pointIndex+1);
    result->SetPointError(pointIndex, 0.0, currError);
    pointIndex++;
  }
  observable->setMin(minOrigin);
  observable->setMax(maxOrigin);
  delete originHist;
  return result;
}

int main(int argc, char **argv){
  if(argc<2){
    cout<<"Usage: "<<argv[0]<<" <jobname> <input file list> <option>"<<endl;
    exit(0);
  }
  CommonFunc::SetAtlasStyle();
  // gErrorIgnoreLevel=kError+1;
  TString jobname=argv[1];
  TString inputFileList=argv[2];
  
  TString option=argv[argc-1];
  double binw=10;		// 10 GeV bins
  double fraction=0.07;		// Width fraction
  
  // Get the workspace. my precious!
  unique_ptr<TFile> f(TFile::Open("workspace/high_mass_diphoton/2015_2D.root","read"));
  RooWorkspace *ws=dynamic_cast<RooWorkspace*>(f->Get("combWS"));
  ws->var("mX")->setRange(0,10000);
  ws->var("wX")->setRange(0,10000);
  RooAbsPdf *pdf=ws->pdf("pdf_signal_inclusive_13TeV");
  RooRealVar *x=ws->var("atlas_invMass");
  RooRealVar w("w","w",1);	// weight variable

  
  // Get the file list. who cares!
  float mass, weight, sigmaXBRXEff;
  bool isPassedLowHighMass, isDalitz;
  
  unique_ptr<TChain> c(CommonFunc::MakeChain("CollectionTree",inputFileList,"badfile", inputFileList.Contains(".root")));
  c->SetBranchAddress("HGamEventInfoAuxDyn.m_yy",&mass);
  c->SetBranchAddress("HGamEventInfoAuxDyn.weight",&weight);
  c->SetBranchAddress("HGamEventInfoAuxDyn.crossSectionBRfilterEff",&sigmaXBRXEff);
  c->SetBranchAddress("HGamEventInfoAuxDyn.isPassedLowHighMyy",&isPassedLowHighMass);
  c->SetBranchAddress("HGamEventInfoAuxDyn.isDalitz",&isDalitz);

  const int npoint=3;
  double massArr[npoint]={400, 800, 1500};
  double widthArr[npoint], xMinArr[npoint], xMaxArr[npoint];
  int nBinArr[npoint];
  
  RooWorkspace *wsCat[npoint];
  RooDataSet* MCCat[npoint];
  RooRealVar* xCat[npoint], *wCat[npoint];
  RooAbsPdf* pdfCat[npoint];
  RooPlot* frameCat[npoint];
  for(int ipoint=0;ipoint<npoint;ipoint++){
    widthArr[ipoint]=massArr[ipoint]*fraction;
    xMinArr[ipoint]=massArr[ipoint]-5*widthArr[ipoint];
    xMaxArr[ipoint]=massArr[ipoint]+5*widthArr[ipoint];
    nBinArr[ipoint]=int((xMaxArr[ipoint]-xMinArr[ipoint])/binw)+1;
    xMinArr[ipoint]=xMaxArr[ipoint]-nBinArr[ipoint]*binw;
    
    wsCat[ipoint]=new RooWorkspace(Form("wsCat_%d",ipoint));
    wsCat[ipoint]->import(*pdf);
    pdfCat[ipoint]=wsCat[ipoint]->pdf(pdf->GetName());
    xCat[ipoint]=wsCat[ipoint]->var(x->GetName());
    xCat[ipoint]->setRange(xMinArr[ipoint], xMaxArr[ipoint]);
    
    wCat[ipoint]=new RooRealVar(Form("w_%d",ipoint),Form("w_%d",ipoint),1);
    frameCat[ipoint]=xCat[ipoint]->frame();
    MCCat[ipoint]=new RooDataSet(Form("MC_%.0f",massArr[ipoint]),Form("MC_%.0f",massArr[ipoint]), RooArgSet(*xCat[ipoint],*wCat[ipoint]), WeightVar(*wCat[ipoint]));
  }
  
  int nevt=c->GetEntries();
  
  for(int ievt=0;ievt<nevt;ievt++){
    if(ievt%100==0){
      cout<<"Processing "<<ievt*100./double(nevt)<<"% of events...\r"<<std::flush;
    }
    TString fileName=c->GetFile()->GetName();
    int icat=FileNameToCat(fileName);
    
    c->GetEntry(ievt);
    // cout<<mass<<" "<<weight<<" "<<isPassedLowHighMass<<" "<<isDalitz<<endl; getchar();
    if(!isPassedLowHighMass||isDalitz) continue;

    xCat[icat]->setVal(mass/1000.);
    wCat[icat]->setVal(weight);
    // cout<<x->getVal()<<" "<<w.getVal()<<endl; getchar();
    if(mass/1000.>xMinArr[icat]&&mass/1000.<xMaxArr[icat])
      MCCat[icat]->add(RooArgSet(*xCat[icat], *wCat[icat]), weight);
  }

  for(int ipoint=0;ipoint<npoint;ipoint++){
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
    
    frameCat[ipoint]->SetMinimum(epsilon);
    frameCat[ipoint]->GetYaxis()->SetTitle(Form("Events / %.0f GeV",binw));
    frameCat[ipoint]->GetYaxis()->SetTitleSize(0.07);
    frameCat[ipoint]->GetYaxis()->SetTitleOffset(0.9);

    MCCat[ipoint]->plotOn(frameCat[ipoint], DataError(RooAbsData::SumW2), Binning(nBinArr[ipoint]));
    wsCat[ipoint]->var("mX")->setVal(massArr[ipoint]);
    wsCat[ipoint]->var("wX")->setVal(widthArr[ipoint]);
    wsCat[ipoint]->var("mX")->Print();
    wsCat[ipoint]->var("wX")->Print();
    pdfCat[ipoint]->plotOn(frameCat[ipoint], LineColor(CommonFunc::ColorWheel(ipoint+1)));
    frameCat[ipoint]->Draw("same");
  
    pad2.cd();
    
    TH1D hframe2("hframe2","hframe2",nBinArr[ipoint],xMinArr[ipoint],xMaxArr[ipoint]);
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
    
    CommonFunc::DrawConstantLine(&pad2, 1,  xMinArr[ipoint],xMaxArr[ipoint],kRed,3,2);
    CommonFunc::DrawConstantLine(&pad2, 0.5,xMinArr[ipoint],xMaxArr[ipoint],kRed,2,2);
    CommonFunc::DrawConstantLine(&pad2, 1.5,xMinArr[ipoint],xMaxArr[ipoint],kRed,2,2);
    
    double currChi2Prob=0;
    
    TGraphErrors *subtraction=plotDivision(MCCat[ipoint], pdfCat[ipoint], xCat[ipoint], nBinArr[ipoint],currChi2Prob);
    subtraction->Draw("EPSAME");

    system("mkdir -vp fig/fit/"+jobname);
    TString outputCanvasName="fig/fit/"+jobname+Form("/plot_%.0f",massArr[ipoint]);
    CommonFunc::PrintCanvas(&canvas, outputCanvasName);
    wsCat[ipoint]->import(*MCCat[ipoint]);
    wsCat[ipoint]->writeToFile(outputCanvasName+"_ws.root");
  }
  // pad1->RedrawAxis();
  
}

