#include <RooRealVar.h>
#include <RooDataSet.h>
#include <RooGaussian.h>
#include <RooPlot.h>
#include <RooHistPdf.h>
#include <RooHistFunc.h>
#include <RooExponential.h>
#include <RooPolynomial.h>
#include <RooPolyVar.h>
#include <RooAddPdf.h>
#include <RooAbsData.h>
#include <RooAbsRealLValue.h>
#include <RooAbsPdf.h>
#include <RooMinuit.h>
#include <RooCategory.h>
#include <RooArgSet.h>
#include <RooDataHist.h>
#include <RooNLLVar.h>
#include <RooSimultaneous.h>
#include <RooExponential.h>
#include <RooGlobalFunc.h>
#include <RooCBShape.h>
#include <RooFormula.h>
#include <RooRandom.h>
#include <RooFitResult.h>
#include <RooProdPdf.h>
#include <RooProfileLL.h>
#include <RooLognormal.h>
#include <RooPoisson.h>
#include <RooProduct.h>
#include <RooAddition.h>
#include <RooBifurGauss.h>
#include <Roo1DTable.h>
#include <RooBernstein.h>
#include <RooArgList.h>
#include <RooConstVar.h>
#include <RooExtendPdf.h>
#include <RooGenericPdf.h>
#include <RooChebychev.h>
#include <RooLognormal.h>
#include <RooNovosibirsk.h>
#include <RooLandau.h>
#include <RooWorkspace.h>
#include <RooRealSumPdf.h>
#include <RooNumIntConfig.h>
#include <RooUniform.h>
using namespace RooFit ;

void data_divide_fit(int bins, TH1 * data, RooRealVar x, RooFFTConvPdf pdf){
  data->Sumw2();
  double weight = data->Integral();
  double x_step = (100.-80.)/bins;
  for(int i = 1; i <= data->GetNbinsX(); i++){
    double mass = 80. + ( (i-1) * x_step);
    double obs  = data->GetBinContent(i);
    x.setRange("my_range", mass, mass + x_step);
    RooAbsReal* integral = pdf.createIntegral(x, RooFit::NormSet(x), RooFit::Range("my_range"));
    double fit = weight * integral->getVal() ;
    double p0 = (obs/ fit);
    double error = data->GetBinError(i)/fit;
    data->SetBinContent(i, p0);
    data->SetBinError(i, error);
  }
  return;
}

void data_minus_fit(int bins, TH1 * data, RooRealVar x, RooFFTConvPdf pdf){
  data->Sumw2();
  double weight = data->Integral();
  double x_step = (100.-80.)/bins;
  for(int i = 1; i <= data->GetNbinsX(); i++){
    double mass = 80. + ( (i-1) * x_step);
    double obs  = data->GetBinContent(i);
    x.setRange("my_range", mass, mass + x_step);
    RooAbsReal* integral = pdf.createIntegral(x, RooFit::NormSet(x), RooFit::Range("my_range"));
    double fit = weight * integral->getVal() ;
    double p0 = (obs - fit);
    double error = data->GetBinError(i);
    data->SetBinContent(i, p0);
    data->SetBinError(i, error);
  }
  return;
}

void calc_sig(int bins, TH1 * data, RooRealVar x, RooFFTConvPdf pdf){
  double weight = data->Integral();
  double x_step = (100.-80.)/bins;
  for(int i = 1; i <= data->GetNbinsX(); i++){
    double mass = 80. + ( (i-1) * x_step);  
    double obs  = data->GetBinContent(i);
    x.setRange("my_range", mass, mass + x_step);
    RooAbsReal* integral = pdf.createIntegral(x, RooFit::NormSet(x), RooFit::Range("my_range"));
    double fit = weight * integral->getVal() ;
    double p0 = (obs - fit)/sqrt(fit);
    data->SetBinContent(i, p0);
  }
  return;
}

void calc_sig(double weight, TH1 * data, RooRealVar x, RooGenericPdf pdf){
  double x_step = 70.;
  for(int i = 2; i <= data->GetNbinsX(); i++){
    double mass = 0. + ( (i-1) * x_step);
    x.setRange("my_range", mass, mass + x_step);
    RooAbsReal* integral = pdf.createIntegral(x, RooFit::NormSet(x), RooFit::Range("my_range"));
    double obs  = data->GetBinContent(i);
    double fit = weight * integral->getVal() ;
    double p0 = (obs - fit)/sqrt(fit);
    if(i > 10) data->SetBinContent(i , p0);
    else data->SetBinContent(i , 0);
    delete integral;
  }
  return;
}
