/*****************************************************************************
 * Project: RooFit                                                           *
 * Package: RooFitModels                                                     *
 *    File: $Id: RooVoigtian.h,v 1.7 2007/07/12 20:30:49 wouter Exp $
 * Authors:                                                                  *
 *   TS, Thomas Schietinger, SLAC,          schieti@slac.stanford.edu        *
 *                                                                           *
 * Copyright (c) 2000-2005, Regents of the University of California          *
 *                          and Stanford University. All rights reserved.    *
 *                                                                           *
 * Redistribution and use in source and binary forms,                        *
 * with or without modification, are permitted according to the terms        *
 * listed in LICENSE (http://roofit.sourceforge.net/license.txt)             *
 *****************************************************************************/

#ifndef ROO_HGGBWDBCB
#define ROO_HGGBWDBCB

#include "RooAbsPdf.h"
#include "RooRealProxy.h"

class RooRealVar;

class RooHggBWDBCB : public RooAbsPdf {
public:
  RooHggBWDBCB() {} ;
  RooHggBWDBCB(const char *name, const char *title,
	      RooAbsReal& _x, RooAbsReal& _mean, 
              RooAbsReal& _width, RooAbsReal& _sigma,
              Bool_t doFast = kFALSE);
  RooHggBWDBCB(const RooHggBWDBCB& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new RooHggBWDBCB(*this,newname); }
  inline virtual ~RooHggBWDBCB() { }

// These methods allow the user to select the fast evaluation
// of the complex error function using look-up tables
// (default is the "slow" CERNlib algorithm)

  inline void selectFastAlgorithm()    { _doFast = kTRUE;  }
  inline void selectDefaultAlgorithm() { _doFast = kFALSE; }

protected:

  RooRealProxy x ;
  RooRealProxy mean ;
  RooRealProxy width ;
  RooRealProxy sigma ;
  RooRealProxy alphaLo;
  RooRealProxy alphaHi;
  RooRealProxy nLo;
  RooRealProxy nHi;
  Double_t evaluate() const ;

private:

  Double_t _invRootPi;
  Bool_t _doFast;
  ClassDef(RooHggBWDBCB,1) // Voigtian PDF (Gauss (x) BreitWigner)
};

#endif

