#ifndef ROOT_HggTruthLineShapePdf
#define ROOT_HggTruthLineShapePdf

#include <math.h>
#include "Math/ProbFuncMathCore.h"
#include "Riostream.h"
#include "RooAbsPdf.h"
#include "RooAbsReal.h"
#include "RooFit.h"
#include "RooMath.h"
#include "RooRealProxy.h"
#include "RooRealVar.h"
#include "TMath.h"

// ==================================================================
// Implemented by Hongtao Yang <Hongtao.Yang@cern.ch> on Feb. 6, 2016
// with theory inputs provided by Yee Yap <yee.yap@lpnhe.in2p3.fr> and Lydia Roos <lroos@lpnhe.in2p3.fr>
// ==================================================================
class RooRealVar;

class HggTruthLineShapePdf : public RooAbsPdf {
  
 public:
  
  HggTruthLineShapePdf();
  HggTruthLineShapePdf(const char *name, const char *title, RooAbsReal& _x,
		       RooAbsReal& _mean, RooAbsReal& _width);
  
  HggTruthLineShapePdf(const HggTruthLineShapePdf& other, const char* name = 0);
  virtual TObject* clone(const char* newname) const { return new HggTruthLineShapePdf(*this,newname); }
  inline virtual ~HggTruthLineShapePdf() { }

 protected:

  RooRealProxy x ;
  RooRealProxy mean ;
  RooRealProxy width ;
  
  Double_t evaluate() const;
  
 private:
  
  ClassDef(HggTruthLineShapePdf,1); // Crystal Ball lineshape PDF
    
};
  
#endif
