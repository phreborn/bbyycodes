#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"
#include "Hgg_tree.h"

using namespace std;
using namespace RooFit;
using namespace RooStats;

const double epsilon=1e-4;

int FileNameToMassIdx(TString fileName){
  // genData_ggH1100_W10p.root
  if(fileName.Contains("_500."))   return 0;
  if(fileName.Contains("_750."))   return 1;
  if(fileName.Contains("_1000."))  return 2;
  if(fileName.Contains("_1500."))  return 3;
  if(fileName.Contains("_2000."))  return 4;
  if(fileName.Contains("_3000."))  return 5;
  if(fileName.Contains("_4000."))  return 6;
  if(fileName.Contains("_5000."))  return 7;
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

int minimize(RooWorkspace *ws, RooDataSet *data){
  unique_ptr<RooAbsReal> nll(ws->pdf("poly")->createNLL(*data));
  nll->enableOffsetting(true);
  RooMinimizer minim(*nll);
  minim.setStrategy(1);
  minim.setPrintLevel(0);
  minim.setProfile(); /* print out time */
  minim.setEps(1);
  minim.optimizeConst(2);
  int status=minim.minimize("Minuit2");
  return status;
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

  double xmin=200, xmax=3500;
  unique_ptr<TChain> c(CommonFunc::MakeChain("Hgg_tree",inputFileList,"badfile", inputFileList.Contains(".root")));

  Hgg_tree *p=new Hgg_tree(c.get());

  RooWorkspace *ws=new RooWorkspace("factory");

  ws->factory(Form("x[%f,%f]",xmin,xmax));
  ws->factory("w[1]");
  RooRealVar* x=ws->var("x");
  RooRealVar* w=ws->var("w");
  
  RooDataSet data("data","data",RooArgSet(*x,*w),WeightVar(*w));
  
  TH1D *h=new TH1D("h","h",3000,xmin,xmax);
  
  int nevt=c->GetEntries();
  
  for(int ievt=0;ievt<nevt;ievt++){
    if(ievt%100==0){
      cout<<"Processing "<<ievt*100./double(nevt)<<"% of events...\r"<<std::flush;
    }
    c->GetEntry(ievt);

    double weight=p->MCweight*p->PUweight*p->ZVTXweight*p->ph_SF_1st*p->ph_SF_2nd;
    double mass=p->mass_PV_EM/1000.;
    if(!(p->flag_pre_graviton && p->flag_pt_graviton && p->flag_PID && p->flag_iso_graviton && p->flag_mgg_150)) continue;
    if(mass<xmin||mass>xmax) continue;
    x->setVal(mass);
    w->setVal(weight);
    
    data.add(RooArgSet(*x,*w), weight);
    
    h->Fill(mass,weight);
  }

  ws->factory("RooBernstein::poly(x,{p0[0], p1[0.1,0,100], p2[0.148873,0,1], p3[0.203653,0,1], p4[0.12976,0,1], p5[0.0855217,0,1], p6[0.0536125,0,1]})");

  minimize(ws,&data);

  RooPlot *frame=ws->var("x")->frame();
  TCanvas *c1=new TCanvas("c","c",800,600);

  data.plotOn(frame);
  ws->pdf("poly")->plotOn(frame);

  frame->Draw();
  CommonFunc::PrintCanvas(c1,"flat_hist");

  TFile *fout=TFile::Open("hist.root","recreate");
  
  h->Write();
  fout->Close();
}

