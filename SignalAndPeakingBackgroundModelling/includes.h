#include <string.h>

#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string.hpp>

#include <iostream>
#include <limits>
#include <math.h> //for ceil
#include "Math/QuantFuncMathCore.h" //for ROOT::Math::gamma_quantile

#include <Math/CholeskyDecomp.h>

//#include <RooAbsData.h>
#include <RooAbsPdf.h>
#include <RooAddPdf.h>
#include <RooArgSet.h>
#include <RooBernstein.h>
#include <RooBreitWigner.h>
#include <RooBukinPdf.h>
#include <RooCBShape.h>
#include <RooChebychev.h>
#include <RooDataSet.h>
#include <RooDataHist.h>
#include <RooExponential.h>
#include <RooFitResult.h>
#include <RooGamma.h>
#include <RooGaussian.h>
#include <RooGenericPdf.h>
#include <RooHist.h>
#include <RooLandau.h>
#include <RooMinimizer.h>
#include <RooNLLVar.h>
#include <RooNovosibirsk.h>
#include <RooPlot.h>
#include <RooProduct.h>
#include <RooProdPdf.h>
#include <RooRealVar.h>
#include <RooVoigtian.h>
#include <RooWorkspace.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TF1.h>
#include <TFile.h>
#include <TGraphErrors.h>
#include <TH1F.h>
#include <TH1D.h>
#include <TH2F.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TLine.h>
#include <TMarker.h>
#include "TROOT.h"
#include <TString.h>
#include <TStyle.h>
#include <TSystem.h>

#include <vector>

#include <fstream>
