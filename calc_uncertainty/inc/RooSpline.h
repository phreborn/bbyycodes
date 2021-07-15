// Author: Ruggero Turra <ruggero.turra@cern.ch>

#ifndef ROO_ROOSPLINE
#define ROO_ROOSPLINE

#include <vector>

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooListProxy.h"

#include "RooObjCacheManager.h"

class RooRealVar;
class RooArgList;
class TSpline3;
class TGraph;

class RooSpline : public RooAbsReal {
public:

  RooSpline();
  RooSpline(const char *name, const char *title, 
	    RooAbsReal& x,
	    const std::vector<double>& x0, const std::vector<double>& y0,
	    int order=3, bool logx=false, bool logy=false);
  RooSpline(const char *name, const char *title,
	    RooAbsReal& x,
	    const TGraph* gr,
	    int order=3, bool logx=false, bool logy=false);
  RooSpline(const RooSpline& other, const char* name = 0);
  virtual TObject* clone(const char* newname) const { return new RooSpline(*this, newname); }

  virtual ~RooSpline();

protected:
  Double_t evaluate() const;

private:
  TSpline* m_spline;
  RooRealProxy m_x;
  bool m_logx, m_logy;
  ClassDef(RooSpline, 1)
};
#endif
