#ifndef ROOT_HggTwoSidedCBPdf
#define ROOT_HggTwoSidedCBPdf

#include <math.h>
// external include file below retrieved from workspace code storage
#include "Math/ProbFuncMathCore.h"
// external include file below retrieved from workspace code storage
#include "Riostream.h"
// external include file below retrieved from workspace code storage
#include "RooAbsPdf.h"
// external include file below retrieved from workspace code storage
#include "RooAbsReal.h"
// external include file below retrieved from workspace code storage
#include "RooFit.h"
// external include file below retrieved from workspace code storage
#include "RooMath.h"
// external include file below retrieved from workspace code storage
#include "RooRealProxy.h"
// external include file below retrieved from workspace code storage
#include "RooRealVar.h"
// external include file below retrieved from workspace code storage
#include "TMath.h"

class RooRealVar;

class HggTwoSidedCBPdf : public RooAbsPdf {

public:

  HggTwoSidedCBPdf();
  HggTwoSidedCBPdf(const char *name, const char *title, RooAbsReal &_m,
                   RooAbsReal &_m0, RooAbsReal &_sigma, RooAbsReal &_alphaLo,
                   RooAbsReal &_nLo, RooAbsReal &_alphaHi, RooAbsReal &_nHi);

  HggTwoSidedCBPdf(const HggTwoSidedCBPdf &other, const char *name = 0);
  virtual TObject *clone(const char *newname) const { return new HggTwoSidedCBPdf(*this, newname); }
  inline virtual ~HggTwoSidedCBPdf() { }

  //virtual Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars,
  //              const char* rangeName=0 ) const;
  //virtual Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const;
  Int_t getAnalyticalIntegral(RooArgSet &allVars, RooArgSet &analVars,
                              const char *rangeName = 0) const;
  Double_t analyticalIntegral(Int_t code, const char *rangeName = 0) const;

  double gaussianIntegral(double tmin, double tmax) const;
  double powerLawIntegral(double tmin, double tmax, double alpha, double n) const;

protected:

  RooRealProxy m;
  RooRealProxy m0;
  RooRealProxy sigma;
  RooRealProxy alphaLo;
  RooRealProxy nLo;
  RooRealProxy alphaHi;
  RooRealProxy nHi;

  Double_t evaluate() const;

private:

  ClassDef(HggTwoSidedCBPdf, 1); // Crystal Ball lineshape PDF

};

#endif
