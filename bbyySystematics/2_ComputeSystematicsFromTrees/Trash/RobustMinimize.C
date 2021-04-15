#include <memory>
#include <vector>
#include <RooMinimizer.h>
#include <RooAbsPdf.h>
#include <RooAbsData.h>
#include <RooArgSet.h>
#include <RooDataSet.h>
#include <RooStats/TestStatistic.h>
#include <Math/MinimizerOptions.h>
#include <TDirectory.h>
#include <RooFitResult.h>

#include "RooMsgService.h"


bool robustMinimize(
        RooAbsReal &nll,
        RooMinimizer &minim,
	float low_value_syst_fit_range,
	float high_value_syst_fit_range,
        int verbosity
		    )
{
  char buffer_range[128];
  RooFitResult *roofitresult=0;

  minim.setPrintLevel(verbosity);
  
  double initialNll = nll.getVal();
  double nowNll = initialNll;
  std::auto_ptr<RooArgSet> pars;
  bool ret = false;

    /* check the status of minimization, takes time & cpu */
    bool checkStatus = false;

    for (int tries = 0, maxtries = 4; tries <= maxtries; ++tries) {
      // std::cout << ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo() << std::endl;

      
      sprintf(buffer_range,"RooFit::Minimizer(\"Minuit2\",\"migrad\"),RooFit::Offset(1),RooFit::Hesse(1),RooFit::SumW2Error(1),RooRooFit::Range(%f,%f)",low_value_syst_fit_range,high_value_syst_fit_range);
      
      roofitresult=minim.fit(buffer_range);
      int status = roofitresult->status();

      //historical, int status = minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());
      

      nowNll = nll.getVal();
	if(verbosity>-1)
	  printf("\n -------> initialNll: %10.7f, nll.getVal(): %10.7f", initialNll, nowNll);
	
        if (status == 0 && nowNll > initialNll + 0.02) {
	  if ( checkStatus ) {
	    std::auto_ptr<RooFitResult> res(minim.save());
	    if(verbosity>-1)
	      printf("\n  --> false minimum, status %d, cov. quality %d, edm %10.7f, nll initial % 10.4f, nll final % 10.4f, change %10.5f\n", status, res->covQual(), res->edm(), initialNll, nowNll, initialNll - nowNll);
	    if (pars.get() == 0) pars.reset(nll.getParameters((const RooArgSet*)0));
	    *pars = res->floatParsInit();
	  } else {
	    if(verbosity>-1)
	      printf("\n  --> false minimum\n");
	  }
	  
	  if (tries == 0) {
	    if(verbosity>-1)
	      printf("    ----> Doing a re-scan and re-trying\n");


	    sprintf(buffer_range,"RooFit::Minimizer(\"Minuit2\",\"Scan\"),RooFit::Offset(1),RooFit::Hesse(1),RooFit::SumW2Error(1),RooRooFit::Range(%f,%f)",low_value_syst_fit_range,high_value_syst_fit_range);

	    minim.fit(buffer_range);

	    //historical	    minim.minimize("Minuit2","Scan");
	  } else if (tries == 1) {
	    if(verbosity>-1)
	      printf("    ----> Re-trying with strategy = 1\n");
	    minim.setStrategy(1);
	    // } else if (tries == 2) {
	    //     printf("    ----> Re-trying with strategy = 2\n");
	    //     minim.setStrategy(2);
	  } else  {
	    if(verbosity>-1)
	      printf("    ----> Last attempt: simplex method \n");
            
	    sprintf(buffer_range,"RooFit::Minimizer(\"Minuit2\",\"Simplex\"),RooFit::Offset(1),RooFit::Hesse(1),RooFit::SumW2Error(1),RooRooFit::Range(%f,%f)",low_value_syst_fit_range,high_value_syst_fit_range);
	    roofitresult = minim.fit(buffer_range);
	    
	    status = roofitresult->status();

	    //	    status = minim.minimize("Minuit2","Simplex");
            if (nowNll < initialNll + 0.02) {
	      if(verbosity>-1)
                printf("\n  --> success: status %d, nll initial % 10.4f, nll final % 10.4f, change %10.5f\n", status, initialNll, nowNll, initialNll - nowNll);
	      ret = true;
	      break;
            } else {
	      if(verbosity>-1)
                printf("\n  --> final fail: status %d, nll initial % 10.4f, nll final % 10.4f, change %10.5f\n", status, initialNll, nowNll, initialNll - nowNll);
	      ret = false;
	      break;
            }
	  }
	} else if (status == 0) {
	  if(verbosity>-1)
            printf("\n  --> success: status %d, nll initial % 10.4f, nll final % 10.4f, change %10.5f\n", status, initialNll, nowNll, initialNll - nowNll);
	  ret = true;
	  break;
        } else if (tries != maxtries) {
	  if (checkStatus)
            {
	      std::auto_ptr<RooFitResult> res(minim.save());
	      // if (tries > 0 && res->edm() < 0.05*ROOT::Math::MinimizerOptions::DefaultTolerance())
	      /* lafayette */
	      if (tries >= 0 && res->edm() < 0.1*ROOT::Math::MinimizerOptions::DefaultTolerance()) {
		if(verbosity>-1)
		  printf("\n  --> acceptable: status %d, edm %10.7f, nll initial % 10.4f, nll final % 10.4f, change %10.5f\n", status, res->edm(), initialNll, nowNll, initialNll - nowNll);
		ret = true;
		break;
	      }
	      if(verbosity>-1)
		printf("\n  tries: %d, --> partial fail: status %d, cov. quality %d, edm %10.7f, nll initial % 10.4f, nll final % 10.4f, change %10.5f\n", tries, status, res->covQual(), res->edm(), initialNll, nowNll, initialNll - nowNll);
            }
	  else
            {
	      if(verbosity>-1)
		printf("\n  tries: %d, --> partial fail\n", tries);
            }
      
	  if (tries == 1) {
	    if(verbosity>-1)      
	      printf("    ----> Doing a re-scan first, and switching to strategy 1\n");


	    sprintf(buffer_range,"RooFit::Minimizer(\"Minuit2\",\"Scan\"),RooFit::Offset(1),RooFit::Hesse(1),RooFit::SumW2Error(1),RooRooFit::Range(%f,%f)",low_value_syst_fit_range,high_value_syst_fit_range);

	    minim.fit(buffer_range);


	    //	    minim.minimize("Minuit2","Scan");
	    minim.setStrategy(1);
	  }
	  else if(tries>1){
	    ret = false;
	    break;
	  }
	  /* commented because using strategy 2 is very time-consuming but not helpful */
	  // else if (tries == 2) {
	  //     printf("    ----> trying with strategy = 2\n");
	  //     minim.minimize("Minuit2","Scan");
	  //     minim.setStrategy(2);
	  // }
	  // else if (tries == 3) {
	  //     printf("    ----> trying with strategy = 2\n");
	  //     minim.minimize("Minuit2","Scan");
	  //     minim.setStrategy(2);
	  // }
        }
        else {
	  if ( checkStatus ) {
	    std::auto_ptr<RooFitResult> res(minim.save());
	    if(verbosity>-1)
	      printf("\n  --> final fail: status %d, cov. quality %d, edm %10.7f, nll initial % 10.4f, nll final % 10.4f, change %10.5f\n", status, res->covQual(), res->edm(), initialNll, nowNll, initialNll - nowNll);
	  } else {
	    if(verbosity>-1)
	      printf("\n  --> final fail\n");
	  }
        }
    }
    return ret;
}

