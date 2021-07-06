//===========================================================================================================
//to replace with string_finalDV ?
RooAbsPdf *ReturnPdfSignal(string string_functional_form,int index_finalDV,string string_category)
{
  //mandatory of having category for project of injection test, and better for construction of workspace
  RooAbsPdf *pdf_signal=0;
  
  //to add suffix category for all

  //need to delete various objects afterwards
    
  RooRealVar *roorealvar_finalDV=(RooRealVar *)((RooArgList(argset_finalDV_noWeight)).at(index_finalDV));

  string string_title_finalDV=( (RooRealVar *) ( (RooArgList(argset_finalDV_noWeight) ).at(index_finalDV) ) ) ->GetTitle();
  
  string string_finalDV=( (RooRealVar *)  ( (RooArgList(argset_finalDV_noWeight) ).at(index_finalDV) ) ) ->GetName();

  if (string_functional_form=="Gaussian") {
    double muGauss_value=hist_position_max;
    double muGauss_min=hist_position_FWHM_low;
    double muGauss_max=hist_position_FWHM_high;
    
    double sigmaGauss_value=hist_sigma_effective;
    double sigmaGauss_min=0;
    double sigmaGauss_max=5*hist_sigma_effective;
    
    cout << "muGauss_value=" << muGauss_value << endl;
    cout << "sigmaGauss_value=" << sigmaGauss_value << endl;
    
    RooRealVar *roorealvar_muGauss=new RooRealVar((string("muGauss")+"_"+string_finalDV).c_str(),"#mu_{Gauss}",muGauss_value,muGauss_min,muGauss_max,"GeV");
    RooRealVar *roorealvar_sigmaGauss=new RooRealVar((string("sigmaGauss")+"_"+string_finalDV).c_str(),"#sigma_{Gauss}",sigmaGauss_value,sigmaGauss_min,sigmaGauss_max,"GeV");
    
    pdf_signal=new RooGaussian((string("Pdf_Signal_Gaussian")+"_"+string_finalDV).c_str(),(string("Pdf_Signal_Gaussian")+"_"+string_finalDV).c_str(),*roorealvar_finalDV,*roorealvar_muGauss,*roorealvar_sigmaGauss);
  }
  else if (string_functional_form=="CrystalBall") {
    double muCB_value=hist_position_max;
    double muCB_min=hist_position_FWHM_low;
    double muCB_max=hist_position_FWHM_high;
    
    double sigmaCB_value=hist_sigma_effective;
    double sigmaCB_min=0;
    double sigmaCB_max=5*hist_sigma_effective;
    
    double alphaCB_value=1;
    double alphaCB_min=0;
    double alphaCB_max=5*alphaCB_value;
    
    double nCB_value=10;
    double nCB_min=0;
    double nCB_max=200;
    
    cout << "muCB_value=" << muCB_value << endl;
    cout << "sigmaCB_value=" << sigmaCB_value << endl;
    cout << "alphaCB_value=" << alphaCB_value << endl;
    cout << "nCB_value=" << nCB_value << endl;
    
    RooRealVar *roorealvar_muCB=new RooRealVar((string("mu_simple_CB")+"_"+string_finalDV).c_str(),"#mu_{CB}",muCB_value,muCB_min,muCB_max,"GeV");
    RooRealVar *roorealvar_sigmaCB=new RooRealVar((string("sigma_simple_CB")+"_"+string_finalDV).c_str(),"#sigma_{CB}",sigmaCB_value,sigmaCB_min,sigmaCB_max,"GeV");
    
    RooRealVar *roorealvar_alphaCB=new RooRealVar((string("alphaCB")+"_"+string_finalDV).c_str(),"#alpha_{CB}",alphaCB_value,alphaCB_min,alphaCB_max,"");
    RooRealVar *roorealvar_nCB=new RooRealVar((string("nCB")+"_"+string_finalDV).c_str(),"n_{CB}",nCB_value,nCB_min,nCB_max,"");
    
    pdf_signal=new RooCBShape((string("Pdf_Signal_CrystalBall")+"_"+string_finalDV).c_str(),(string("Pdf_Signal_CrystalBall")+"_"+string_finalDV).c_str(),*roorealvar_finalDV,*roorealvar_muCB,*roorealvar_sigmaCB,*roorealvar_alphaCB,*roorealvar_nCB);
  }
  else if (string_functional_form=="DoubleCrystalBall") {
    double muCB_value=hist_position_max;
    double muCB_min=hist_position_FWHM_low;
    double muCB_max=hist_position_FWHM_high;
    
    /*
    muCB_min=0.5*hist_position_FWHM_low;
    muCB_max=1.5*hist_position_FWHM_high;
    */

    /*
    double muCB_min=0.8*hist_position_FWHM_low;
    double muCB_max=1.2*hist_position_FWHM_high;
    */
    
    double sigmaCB_value=hist_sigma_effective;
    double sigmaCB_min=0;
    double sigmaCB_max=5*hist_sigma_effective;
    //double sigmaCB_max=10*hist_sigma_effective;
    
    double alphaCB_Low_value=1;
    double alphaCB_Low_min=0;
    double alphaCB_Low_max=5*alphaCB_Low_value;
    //double alphaCB_Low_max=10*alphaCB_Low_value;
    
    double nCB_Low_value=10;
    double nCB_Low_min=0;
    double nCB_Low_max=200;
    //double nCB_Low_max=1000;
    
    double alphaCB_High_value=1;
    double alphaCB_High_min=0;
    double alphaCB_High_max=5*alphaCB_High_value;
    //double alphaCB_High_max=10*alphaCB_High_value;
    
    double nCB_High_value=10;
    double nCB_High_min=0;
    double nCB_High_max=200;
    //double nCB_High_max=1000;
    
    cout << "muCB_value=" << muCB_value << endl;
    cout << "sigmaCB_value=" << sigmaCB_value << endl;
    cout << "alphaCB_Low_value=" << alphaCB_Low_value << endl;
    cout << "alphaCB_High_value=" << alphaCB_High_value << endl;
    
    cout << "nCB_Low_value=" << nCB_Low_value << endl;
    cout << "nCB_High_value=" << nCB_High_value << endl;
    
    RooRealVar *roorealvar_muCB=new RooRealVar((string("muCB")+"_"+string_finalDV+"_"+string_category).c_str(),"#mu_{CB}",muCB_value,muCB_min,muCB_max,"GeV");
    RooRealVar *roorealvar_sigmaCB=new RooRealVar((string("sigmaCB")+"_"+string_finalDV+"_"+string_category).c_str(),"#sigma_{CB}",sigmaCB_value,sigmaCB_min,sigmaCB_max,"GeV");
    
    RooRealVar *roorealvar_alphaCB_Low=new RooRealVar((string("alphaCB_Low")+"_"+string_finalDV+"_"+string_category).c_str(),"#alpha_{CB}^{Low}",alphaCB_Low_value,alphaCB_Low_min,alphaCB_Low_max,"");
    RooRealVar *roorealvar_nCB_Low=new RooRealVar((string("nCB_Low")+"_"+string_finalDV+"_"+string_category).c_str(),"n_{CB}^{Low}",nCB_Low_value,nCB_Low_min,nCB_Low_max,"");
    
    RooRealVar *roorealvar_alphaCB_High=new RooRealVar((string("alphaCB_High")+"_"+string_finalDV+"_"+string_category).c_str(),"#alpha_{CB}^{High}",alphaCB_High_value,alphaCB_High_min,alphaCB_High_max,"");
    RooRealVar *roorealvar_nCB_High=new RooRealVar((string("nCB_High")+"_"+string_finalDV+"_"+string_category).c_str(),"n_{CB}^{High}",nCB_High_value,nCB_High_min,nCB_High_max,"");
    
    pdf_signal=new RooTwoSidedCBShape((string("Pdf_Signal_DoubleCrystalBall")+"_"+string_finalDV+"_"+string_category).c_str(),(string("Pdf_Signal_DoubleCrystalBall")+"_"+string_finalDV+"_"+string_category).c_str(),*roorealvar_finalDV,*roorealvar_muCB,*roorealvar_sigmaCB,*roorealvar_alphaCB_Low,*roorealvar_nCB_Low,*roorealvar_alphaCB_High,*roorealvar_nCB_High);
  }
  else if (string_functional_form=="Bukin") {
    //  https://root.cern.ch/doc/master/RooBukinPdf_8cxx_source.html
    //in particular for the range

    double muBukin_value=hist_position_max;
    double muBukin_min=hist_position_FWHM_low;
    double muBukin_max=hist_position_FWHM_high;
    
    double sigmaBukin_value=hist_sigma_effective;
    double sigmaBukin_min=0;
    double sigmaBukin_max=5*hist_sigma_effective;

    double xiBukin_value=0;
    double xiBukin_min=-1;
    double xiBukin_max=1;
    
    double rho1Bukin_value=-0.01;
    double rho1Bukin_min=-1; //official range
    double rho1Bukin_max=0; //official range
    
    double rho2Bukin_value=0.01;
    double rho2Bukin_min=0; //official range
    double rho2Bukin_max=1.0; //official max
        
    cout << "muBukin_value=" << muBukin_value << endl;
    cout << "sigmaBukin_value=" << sigmaBukin_value << endl;
    cout << "rho1Bukin_value=" << rho1Bukin_value << endl;
    cout << "rho2Bukin_value=" << rho2Bukin_value << endl;
    
    RooRealVar *roorealvar_muBukin=new RooRealVar((string("muBukin")+"_"+string_finalDV).c_str(),"#mu_{Bukin}",muBukin_value,muBukin_min,muBukin_max,"GeV");
    RooRealVar *roorealvar_sigmaBukin=new RooRealVar((string("sigmaBukin")+"_"+string_finalDV).c_str(),"#sigma_{Bukin}",sigmaBukin_value,sigmaBukin_min,sigmaBukin_max,"GeV");
    RooRealVar *roorealvar_xiBukin=new RooRealVar((string("xiBukin")+"_"+string_finalDV).c_str(),"#xi_{Bukin}",xiBukin_value,xiBukin_min,xiBukin_max,"");
    RooRealVar *roorealvar_rho1Bukin=new RooRealVar((string("rho1Bukin")+"_"+string_finalDV).c_str(),"#rho_{1 Bukin}",rho1Bukin_value,rho1Bukin_min,rho1Bukin_max,"");
    RooRealVar *roorealvar_rho2Bukin=new RooRealVar((string("rho2Bukin")+"_"+string_finalDV).c_str(),"#rho_{2 Bukin}",rho2Bukin_value,rho2Bukin_min,rho2Bukin_max,"");
    
    pdf_signal=new RooBukinPdf((string("Pdf_Signal_Bukin")+"_"+string_finalDV).c_str(),(string("Pdf_Signal_Bukin")+"_"+string_finalDV).c_str(),*roorealvar_finalDV,*roorealvar_muBukin,*roorealvar_sigmaBukin,*roorealvar_xiBukin,*roorealvar_rho1Bukin,*roorealvar_rho2Bukin);
  }
  else if (string_functional_form=="ExpGausExp") {
    double muGauss_value=hist_position_max;
    double muGauss_min=hist_position_FWHM_low;
    double muGauss_max=hist_position_FWHM_high;
    
    double sigmaGauss_value=hist_sigma_effective;
    double sigmaGauss_min=0;
    double sigmaGauss_max=5*hist_sigma_effective;

    double slopeExp_Low_value=2;
    double slopeExp_Low_min=0.01;
    double slopeExp_Low_max=10;

    double slopeExp_High_value=2;
    double slopeExp_High_min=0.01;
    double slopeExp_High_max=10;
    
    cout << "muGauss_value=" << muGauss_value << endl;
    cout << "sigmaGauss_value=" << sigmaGauss_value << endl;
    cout << "slopeExp_Low_value=" << slopeExp_Low_value << endl;
    cout << "slopeExp_High_value=" << slopeExp_High_value << endl;
    
    RooRealVar *roorealvar_muGauss=new RooRealVar((string("muExpGausExp")+"_"+string_finalDV).c_str(),"#mu_{Gauss}",muGauss_value,muGauss_min,muGauss_max,"GeV");
    RooRealVar *roorealvar_sigmaGauss=new RooRealVar((string("sigmaExpGausExp")+"_"+string_finalDV).c_str(),"#sigma_{Gauss}",sigmaGauss_value,sigmaGauss_min,sigmaGauss_max,"GeV");
    RooRealVar *roorealvar_slopeExp_Low=new RooRealVar((string("slopeExp_Low_")+string_finalDV).c_str(),"k_{Low}",slopeExp_Low_value,0.01,10,"");
    RooRealVar *roorealvar_slopeExp_High=new RooRealVar((string("slopeExp_High_")+string_finalDV).c_str(),"k_{High}",slopeExp_High_value,0.01,10,"");
    
    pdf_signal=new ExpGausExpPDF((string("Pdf_Signal_ExpGausExp")+"_"+string_finalDV).c_str(),(string("Pdf_Signal_ExpGausExp")+"_"+string_finalDV).c_str(),*roorealvar_finalDV,*roorealvar_muGauss,*roorealvar_sigmaGauss,*roorealvar_slopeExp_Low,*roorealvar_slopeExp_High);
  }
  //===================
  //Dedicated to Resonant
  //to change for Resonant
  else if (string_functional_form=="Novosibirsk") {
    float novosibirsk_peak_value=hist_position_max;
    float novosibirsk_peak_min=hist_position_FWHM_low;
    float novosibirsk_peak_max=hist_position_FWHM_high;
    
    float novosibirsk_width_value=hist_sigma_effective;
    float novosibirsk_width_min=0;
    float novosibirsk_width_max=5*hist_sigma_effective;
    
    //    float novosibirsk_tail_value=0.3;
    //float novosibirsk_tail_value=0.5;
    //float novosibirsk_tail_value=0.1;
    float novosibirsk_tail_value=0; //best: not influence the location of the asymmetry
    float novosibirsk_tail_min=-10;
    float novosibirsk_tail_max=10;
    
    cout << "novosibirsk_peak_value=" << novosibirsk_peak_value << endl;
    cout << "novosibirsk_width_value=" << novosibirsk_width_value << endl;
    cout << "novosibirsk_tail_value=" << novosibirsk_tail_value << endl;

    RooRealVar *roorealvar_novosibirsk_peak=new RooRealVar((string("peak_Novosibirsk")+"_"+string_finalDV).c_str(),"peak_{Novosibirsk}",novosibirsk_peak_value,novosibirsk_peak_min,novosibirsk_peak_max,"GeV");
    RooRealVar *roorealvar_novosibirsk_width=new RooRealVar((string("width_Novosibirsk")+"_"+string_finalDV).c_str(),"width_{Novosibirsk}",novosibirsk_width_value,novosibirsk_width_min,novosibirsk_width_max,"GeV");
    RooRealVar *roorealvar_novosibirsk_tail=new RooRealVar((string("tail_Novosibirsk")+"_"+string_finalDV).c_str(),"tail_{Novosibirsk}",novosibirsk_tail_value,novosibirsk_tail_min,novosibirsk_tail_max,"");
    
    pdf_signal=new RooNovosibirsk((string("Pdf_Signal_Novosibirsk")+"_"+string_finalDV).c_str(),(string("Pdf_Signal_Novosibirsk")+"_"+string_finalDV).c_str(),*roorealvar_finalDV,*roorealvar_novosibirsk_peak,*roorealvar_novosibirsk_width,*roorealvar_novosibirsk_tail);
  }
  /*
    else if (string_functional_form=="Modified_Landau") {
    float landau_mean_p0_value=100;
    float landau_mean_p0_min=0;
    float landau_mean_p0_max=110;
    
    float landau_mean_p1_value=0;
    float landau_mean_p1_min=-5;
    float landau_mean_p1_max=5;
    
    float landau_sigma_value=15;
    float landau_sigma_min=0;
    float landau_sigma_max=60;
    
    RooRealVar *roorealvar_landau_mean_p0=new RooRealVar((string("Landau_mean_p0")+"_"+string_finalDV).c_str(),(string("landau_mean_p0")+" "+string_title_finalDV).c_str(),landau_mean_p0_value,landau_mean_p0_min,landau_mean_p0_max);
    RooRealVar *roorealvar_landau_mean_p1=new RooRealVar((string("Landau_mean_p1")+"_"+string_finalDV).c_str(),(string("landau_mean_p1")+" "+string_title_finalDV).c_str(),landau_mean_p1_value,landau_mean_p1_min,landau_mean_p1_max);
    
    RooFormulaVar *rooformulavar_landau_linear_mean=new RooFormulaVar((string("rooformulavar_landau_linear_mean")+"_"+string_finalDV).c_str(),"@0+@1*@2",RooArgList(*roorealvar_landau_mean_p0,*roorealvar_landau_mean_p1,*roorealvar_finalDV));
    
    
    RooRealVar *roorealvar_landau_sigma=new RooRealVar((string("Landau_sigma")+"_"+string_finalDV).c_str(),(string("landau_sigma")+" "+string_title_finalDV).c_str(),landau_sigma_value,landau_sigma_min,landau_sigma_max);
    
    pdf_signal=new RooLandau(string_pdf_bkg.c_str(),"Pdf_Bkg_modified_landau",*roorealvar_finalDV,*rooformulavar_landau_linear_mean,*roorealvar_landau_sigma);
    }
  */

  else {
    cout << "ReturnPdfSignal, pdf does not exist, halt program" << endl;
    exit(1);
  }
  
  //to develop the delete and check if still existence of parameters afterwards  
  
  return pdf_signal;
}
//===========================================================================================================
