#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"

using namespace std;
using namespace RooFit;
using namespace RooStats;

const double epsilon=1e-4;

int FileNameToCat(TString fileName){
  if(fileName.Contains("G500_k01"))   return 0;
  if(fileName.Contains("G1000_k01"))  return 1;
  if(fileName.Contains("G2000_k01"))  return 2;
  if(fileName.Contains("G3000_k001")) return 3;
  if(fileName.Contains("G3000_k005")) return 4;
  if(fileName.Contains("G3000_k01"))  return 5;
  if(fileName.Contains("G4000_k01"))  return 6;
  if(fileName.Contains("G5000_k01"))  return 7;
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
  gErrorIgnoreLevel=kError+1;
  TString jobname=argv[1];
  TString inputFileList=argv[2];
  TString option=argv[argc-1];

  unique_ptr<TFile> f(TFile::Open("workspace/high_mass_diphoton/2015_Graviton_2D.root","read"));
  RooWorkspace *ws=dynamic_cast<RooWorkspace*>(f->Get("combWS"));
  ws->var("mG")->setRange(0,10000);
  ws->var("GkM")->setRange(0,10000);
  
  RooAbsPdf *pdf=ws->pdf("pdf_signal_inclusive_13TeV");
  RooRealVar *x=ws->var("atlas_invMass");
  RooRealVar w("w","w",1);	// weight variable

  // Get the file list. who cares!
  float mass, weight, sigmaXBRXEff, pt_1st, pt_2nd;
  bool isPassedExotic, isDalitz;
  unique_ptr<TChain> c(CommonFunc::MakeChain("CollectionTree",inputFileList,"badfile", inputFileList.Contains(".root")));
  c->SetBranchAddress("HGamEventInfoAuxDyn.m_yy",&mass);
  c->SetBranchAddress("HGamEventInfoAuxDyn.weight",&weight);
  c->SetBranchAddress("HGamEventInfoAuxDyn.crossSectionBRfilterEff",&sigmaXBRXEff);
  c->SetBranchAddress("HGamEventInfoAuxDyn.isDalitz",&isDalitz);
  c->SetBranchAddress("HGamEventInfoAuxDyn.isPassedExotic",&isPassedExotic);
  c->SetBranchAddress("HGamEventInfoAuxDyn.pT_y1",&pt_1st);
  c->SetBranchAddress("HGamEventInfoAuxDyn.pT_y2",&pt_2nd);
  
  const int npoint=8;
  TString sampleName[npoint]={"G500_k01","G1000_k01","G2000_k01","G3000_k001","G3000_k005","G3000_k01","G4000_k01","G5000_k01"};  
  double massArr[npoint]={500, 1000, 2000, 3000, 3000, 3000, 4000, 5000};
  double GkMArr[npoint] ={0.1,0.1,0.1,0.01,0.05,0.1,0.1,0.1};
  double xMinArr[npoint]={400, 800,  1800, 2800, 2800, 2800, 3700, 4700};
  double xMaxArr[npoint]={600, 1200, 2200, 3200, 3200, 3200, 4300, 5300};
  int nBinArr[npoint]   ={100, 100,  50,  50,  50,  50,  50,  50};
  
  RooWorkspace *wsCat[npoint];
  RooDataSet* MCCat[npoint];
  RooRealVar* xCat[npoint], *wCat[npoint];
  RooAbsPdf* pdfCat[npoint];
  RooPlot* frameCat[npoint];
  
  for(int ipoint=0;ipoint<npoint;ipoint++){
    // if(fraction>0){
    //   xMinArr[ipoint]=massArr[ipoint]-10*GkMArr[ipoint];
    //   xMaxArr[ipoint]=massArr[ipoint]+10*GkMArr[ipoint];
    // }
    // else{
    //   xMinArr[ipoint]=massArr[ipoint]-0.1*massArr[ipoint];
    //   xMaxArr[ipoint]=massArr[ipoint]+0.1*massArr[ipoint];
    // }
    
    // nBinArr[ipoint]=int((xMaxArr[ipoint]-xMinArr[ipoint])/binw)+1;
    // xMinArr[ipoint]=xMaxArr[ipoint]-nBinArr[ipoint]*binw;
    
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
    isPassedExotic=(isPassedExotic&&pt_1st>55000&&pt_2nd>55000);
    if(!isPassedExotic) continue;

    xCat[icat]->setVal(mass/1000.);
    wCat[icat]->setVal(weight);

    if(mass/1000.>xMinArr[icat]&&mass/1000.<xMaxArr[icat])
      MCCat[icat]->add(RooArgSet(*xCat[icat], *wCat[icat]), weight);
  }

  for(int ipoint=0;ipoint<npoint;ipoint++){
    if(MCCat[ipoint]->sumEntries()<epsilon){
      cout<<"0 events... "<<endl; getchar();
      continue;
    }
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
    frameCat[ipoint]->GetYaxis()->SetTitle(Form("Events / %.0f GeV",(xMaxArr[ipoint]-xMinArr[ipoint])/double(nBinArr[ipoint])));
    frameCat[ipoint]->GetYaxis()->SetTitleSize(0.07);
    frameCat[ipoint]->GetYaxis()->SetTitleOffset(0.9);

    MCCat[ipoint]->plotOn(frameCat[ipoint], DataError(RooAbsData::SumW2), Binning(nBinArr[ipoint]));
    wsCat[ipoint]->var("mG")->setVal(massArr[ipoint]);
    wsCat[ipoint]->var("GkM")->setVal(GkMArr[ipoint]);
    wsCat[ipoint]->var("mG")->Print();
    wsCat[ipoint]->var("GkM")->Print();
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
    TString outputCanvasName="fig/fit/"+jobname+Form("/plot_%s_%.0f", sampleName[ipoint].Data(), massArr[ipoint]);
    CommonFunc::PrintCanvas(&canvas, outputCanvasName);
    wsCat[ipoint]->import(*MCCat[ipoint]);
    wsCat[ipoint]->writeToFile(outputCanvasName+"_ws.root");
  }
  // pad1->RedrawAxis();
}

