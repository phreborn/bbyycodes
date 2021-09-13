#include "RooFit.h"
#include "RooTrace.h"
#include "Riostream.h"

#include <vector>
#include <string>
#include <algorithm>

#include "RooSpline.h"
#include "RooNameReg.h"
#include "RooAbsReal.h"
#include "RooErrorHandler.h"
#include "RooMsgService.h"
#include "RooTrace.h"

#include "TSpline.h"
#include "TGraph.h"

using namespace std ;

ClassImp(RooSpline)
;

RooSpline::RooSpline()
  : m_spline(0), m_logx(false), m_logy(false)
{
  TRACE_CREATE;
}

RooSpline::~RooSpline()
{
  if (m_spline) { delete m_spline; }
  TRACE_DESTROY;
}


RooSpline::RooSpline(const char *name, const char *title,
		     RooAbsReal& x,
		     const TGraph* gr,
		     int order,
		     bool logy,
		     bool logx)
  : RooSpline(name, title, x,
	      vector<double>(&(gr->GetX()[0]), &(gr->GetX())[0] + gr->GetN()),
	      vector<double>(&(gr->GetY()[0]), &(gr->GetY())[0] + gr->GetN()),
	      order, logx, logy) { }

RooSpline::RooSpline(const char *name, const char *title,
		     RooAbsReal& x,
		     const std::vector<double>& x0, const std::vector<double>& y0,
		     int order,
		     bool logx, bool logy)
  : RooAbsReal(name, title),
    m_x("x", "x", this, x),
    m_logx(logx), m_logy(logy)
{
  const std::string title_spline = std::string(title) + "_spline";
  if (x0.size() != y0.size())
  {
    coutE(InputArguments) << "RooSpline::ctor(" << GetName() << ") ERROR: size of x and y are not equal" << std::endl;
  }

  // TSpline3 wants Double_t[] as input (non-const, why?)
  std::vector<double> x_nonconst(x0);
  std::vector<double> y_nonconst(y0);

  if (m_logx) { std::transform(x_nonconst.begin(), x_nonconst.end(), x_nonconst.begin(), ::log); }
  if (m_logy) { std::transform(y_nonconst.begin(), y_nonconst.end(), y_nonconst.begin(), ::log); }

  if (order == 3) {
    m_spline = new TSpline3(title_spline.c_str(),
			    &x_nonconst[0],
			    &y_nonconst[0],
			    x0.size());
  }
  else if (order == 5) {
    m_spline = new TSpline5(title_spline.c_str(),
			    &x_nonconst[0],
			    &y_nonconst[0],
			    x0.size());
  }
  else {
    coutE(InputArguments) << "supported orders are 3 or 5" << std::endl;
  }

  TRACE_CREATE;
}

RooSpline::RooSpline(const RooSpline& other, const char* name) :
  RooAbsReal(other, name),
  m_spline((TSpline*)other.m_spline->Clone()),
  m_x("x", this, other.m_x),
  m_logx(other.m_logx), m_logy(other.m_logy)
{
  TRACE_CREATE;
}

Double_t RooSpline::evaluate() const
{
  const double x_val = (!m_logx) ? m_x : exp(m_x);
  return (!m_logy) ? m_spline->Eval(x_val) : exp(m_spline->Eval(x_val));
}
