/// V.Cairo

#include "RooFit.h"

#include "Riostream.h"
#include "Riostream.h"
#include <math.h>

#include "RooExpGaussExpShape.h"
#include "RooAbsReal.h"
#include "RooRealVar.h"
#include "RooMath.h"
#include "TMath.h"
#include "Math/ProbFuncMathCore.h"

ClassImp(RooExpGaussExpShape)

//_____________________________________________________________________________
RooExpGaussExpShape::RooExpGaussExpShape(const char *name, const char *title,
           RooAbsReal& _m, RooAbsReal& _m0, RooAbsReal& _sigma,
           RooAbsReal& _kLo, RooAbsReal& _kHi) :
  RooAbsPdf(name, title),
  m("m", "Dependent", this, _m), //x
  m0("m0", "M0", this, _m0), // mean 
  sigma("sigma", "Sigma", this, _sigma), //sigma
  kLo("kLo", "Low-side k", this, _kLo), //decay constant of the exponential on the LOW side tail
  kHi("kHi", "High-side k", this, _kHi) //decay constant of the exponential on the HIGH side tail
{
}


//_____________________________________________________________________________
RooExpGaussExpShape::RooExpGaussExpShape(const RooExpGaussExpShape& other, const char* name) :
  RooAbsPdf(other, name), m("m", this, other.m), m0("m0", this, other.m0),
  sigma("sigma", this, other.sigma), 
  kLo("kLo", this, other.kLo), kHi("kHi", this, other.kHi)
{
}



//Implement eq.3 from here: https://arxiv.org/pdf/1603.08591.pdf
//_____________________________________________________________________________
Double_t RooExpGaussExpShape::evaluate() const {

  Double_t t = (m-m0)/sigma;

  if (t <= -kLo) {
    Double_t a = 0.5*kLo*kLo;
    Double_t b = kLo*t; 
    return exp(a+b);
  }
  else if (t > kHi) {
    Double_t a = 0.5*kHi*kHi;
    Double_t b = kHi*t; 
    return exp(a-b);
  }
  return exp(-0.5*t*t);
}

