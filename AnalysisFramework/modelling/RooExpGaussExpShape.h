/// V.Cairo

#ifndef ROOT_Hfitter_RooExpGaussExpShape
#define ROOT_Hfitter_RooExpGaussExpShape


#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooAbsReal.h"
#include "RooArgSet.h"

class RooRealVar;

class RooExpGaussExpShape : public RooAbsPdf {

public:
  
  RooExpGaussExpShape() {}
  
  RooExpGaussExpShape(const char *name, const char *title, 
               RooAbsReal& _m, //x
               RooAbsReal& _m0,//mean
               RooAbsReal& _sigma,
               RooAbsReal& _kLo, 
               RooAbsReal& _kHi);
               //RooAbsReal& _norm);
  
  RooExpGaussExpShape(const RooExpGaussExpShape& other, const char* name = 0);
  
  virtual TObject* clone(const char* newname) const { return new RooExpGaussExpShape(*this,newname); }
  
  inline virtual ~RooExpGaussExpShape() { }
  
protected:
  
  Double_t evaluate() const;
  
  RooRealProxy m; //x
  RooRealProxy m0; //mean
  RooRealProxy sigma;
  RooRealProxy kLo;
  RooRealProxy kHi;
  //RooRealProxy norm;

private:
  ClassDef(RooExpGaussExpShape,1)
};

#endif

