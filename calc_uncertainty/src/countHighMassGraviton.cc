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

  unique_ptr<TChain> c(CommonFunc::MakeChain("CollectionTree",inputFileList,"badfile", inputFileList.Contains(".root")));

  gravitonNtup *p=new gravitonNtup(c.get());
  
  int nevt=c->GetEntries();

  double yield[3]={0,0,0};
  
  for(int ievt=0;ievt<nevt;ievt++){
    if(ievt%100==0){
      cout<<"Processing "<<ievt*100./double(nevt)<<"% of events...\r"<<std::flush;
    }
    c->GetEntry(ievt);

    double weight=p->total_weight;
    p->accepted=p->pass_ld_subld_id&&(p->pt_leading>55*1e3)&&(p->pt_subleading>55*1e3)&&(p->topoetcone40_leading<0.022*p->pt_leading+2450)&&(p->topoetcone40_subleading<0.022*p->pt_subleading+2450)&&(p->ptcone20_leading<0.05*p->pt_leading)&&(p->ptcone20_subleading<0.05*p->pt_subleading);
    if(p->accepted*weight==0) continue;

    if(option.Contains("UC2")){
      if(p->conv_leading==0&&p->conv_subleading==0) yield[0]+=weight;
      else yield[1]+=weight;
    }
    if(option.Contains("BE2")){
      if(fabs(p->etaS2_leading)<1.375&&fabs(p->etaS2_subleading)<1.375) yield[0]+=weight;
      else yield[1]+=weight;
    }
    if(option.Contains("BE3")){
      if(fabs(p->etaS2_leading)<1.375&&fabs(p->etaS2_subleading)<1.375) yield[0]+=weight;
      else if(fabs(p->etaS2_leading)<1.375||fabs(p->etaS2_subleading)<1.375) yield[1]+=weight;
      else yield[2]+=weight;
    }
    if(option.Contains("CF2")){
      if(fabs(p->etaS2_leading)<0.75&&fabs(p->etaS2_subleading)<0.75) yield[0]+=weight;
      else yield[1]+=weight;
    }
    if(option.Contains("CF3")){
      if(fabs(p->etaS2_leading)<0.75&&fabs(p->etaS2_subleading)<0.75) yield[0]+=weight;
      else if((fabs(p->etaS2_leading)>1.3&&fabs(p->etaS2_leading)<1.75)||(fabs(p->etaS2_subleading)>1.3&&fabs(p->etaS2_subleading)<1.75)) yield[1]+=weight;
      else yield[2]+=weight;
    }
  }
  ofstream fout("/afs/cern.ch/user/y/yanght/workarea/GG/xmlAnaWSBuilder/config/high_mass_diphoton/improve/frac/ekhi/"+jobname);
  cout<<yield[0]/(yield[0]+yield[1]+yield[2])
      <<" "<<yield[1]/(yield[0]+yield[1]+yield[2])
      <<" "<<yield[2]/(yield[0]+yield[1]+yield[2])
      <<endl;
  fout<<yield[0]/(yield[0]+yield[1]+yield[2])
      <<" "<<yield[1]/(yield[0]+yield[1]+yield[2])
      <<" "<<yield[2]/(yield[0]+yield[1]+yield[2])
      <<endl;
}

