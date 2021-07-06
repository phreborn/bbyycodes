//to rename observables in finalDV

//IF AT LIMIT, AVOID ?

//exemple le dernier : voir le plot
//et voir si la roorealvar a le range


void AddToChi2(double &chi2,int &ndf,RooRealVar *roorealvar_HH,RooRealVar *rororealvar_1H);

int CompareChi2_Pdfs_HH_1H()
{
  gROOT->ProcessLine(".L HggTwoSidedCBPdf.cxx+");
  cout << "compile ExpGausExpPDF" << endl;
  gROOT->ProcessLine(".L ExpGausExpPDF.cxx+");
  gSystem->Load("HggTwoSidedCBPdf_cxx.so");
  gSystem->Load("ExpGausExpPDF_cxx.so");

  RooRealVar *roorealvar_m_yy=new RooRealVar("m_yy","m_yy",0,1000);
  RooRealVar *roorealvar_m_bb=new RooRealVar("m_bb","m_bb",0,1000);
  RooRealVar *roorealvar_m_yybb=new RooRealVar("m_yybb","m_yybb",0,1000);
  
  RooArgSet argset_observables(*roorealvar_m_yy,*roorealvar_m_bb,*roorealvar_m_yybb);
  
  vector<string> vec_string_category={"NonResonant_LooseLowMass","NonResonant_TightLowMass","NonResonant_LooseHighMass","NonResonant_TightHighMass","NonResonant_Inclusive"};
  //vector<string> vec_string_category={"NonResonant_Inclusive"};
  //vector<string> vec_string_category={"NonResonant_LooseLowMass"};
  
  //  vector<string> vec_string_campaign={"h024_mc16a","h024_mc16d","h024_mc16e","h024_mc16a_h024_mc16d","h024_mc16a_h024_mc16d_h024_mc16e"};
  //vector<string> vec_string_campaign={"h024_mc16d"};
  // vector<string> vec_string_campaign={"h024_mc16d","h024_mc16a_h024_mc16d_h024_mc16e"};
  vector<string> vec_string_campaign={"h024_mc16a_h024_mc16d_h024_mc16e"};

  for (int index_category=0;index_category<vec_string_category.size();index_category++) {
    string string_category=vec_string_category[index_category];
    
    for (int index_campaign=0;index_campaign<vec_string_campaign.size();index_campaign++) {
      string string_campaign_MxAOD=vec_string_campaign[index_campaign];
      
      string string_process;
      
      string_process="SingleHiggs";
      
      //construct
      TFile f_1H((string("/sps/atlas/e/escalier/ATLAS_HGam/Outputs_syst_shape_Run2/Pdf_nominal/")+string_category+"/"+string_campaign_MxAOD+"/"+string_process+"/"+"Pdf_"+string_campaign_MxAOD+"_"+string_process+"_"+string_category+string(".root")).c_str());
      RooAbsPdf *Pdf_Signal_1H=(RooAbsPdf *)f_1H.Get((string("Pdf_Signal_m_yy_")+string_category).c_str());

      string_process="aMCnloHwpp_hh_yybb_AF2";
      TFile f_HH((string("/sps/atlas/e/escalier/ATLAS_HGam/Outputs_syst_shape_Run2/Pdf_nominal/")+string_category+"/"+string_campaign_MxAOD+"/"+string_process+"/"+"Pdf_"+string_campaign_MxAOD+"_"+string_process+"_"+string_category+string(".root")).c_str());
      RooAbsPdf *Pdf_Signal_HH=(RooAbsPdf *)f_HH.Get((string("Pdf_Signal_m_yy_")+string_category).c_str());
      
      //      Pdf_Signal_1H->Print("v");

      RooArgSet *argset_parameters_1H=Pdf_Signal_1H->getParameters(argset_observables);
      RooArgSet *argset_parameters_HH=Pdf_Signal_HH->getParameters(argset_observables);
      
      double chi2=0;
      int ndf=0;
      
      AddToChi2(chi2,ndf,(RooRealVar *)argset_parameters_HH->selectByName("*muCB*")->first(),(RooRealVar *)argset_parameters_1H->selectByName("*muCB*")->first());
      AddToChi2(chi2,ndf,(RooRealVar *)argset_parameters_HH->selectByName("*sigmaCB*")->first(),(RooRealVar *)argset_parameters_1H->selectByName("*sigmaCB*")->first());
      AddToChi2(chi2,ndf,(RooRealVar *)argset_parameters_HH->selectByName("*alphaCB_Low*")->first(),(RooRealVar *)argset_parameters_1H->selectByName("*alphaCB_Low*")->first());
      AddToChi2(chi2,ndf,(RooRealVar *)argset_parameters_HH->selectByName("*nCB_Low*")->first(),(RooRealVar *)argset_parameters_1H->selectByName("*nCB_Low*")->first());
      AddToChi2(chi2,ndf,(RooRealVar *)argset_parameters_HH->selectByName("*alphaCB_High*")->first(),(RooRealVar *)argset_parameters_1H->selectByName("*alphaCB_High*")->first());
      AddToChi2(chi2,ndf,(RooRealVar *)argset_parameters_HH->selectByName("*nCB_High*")->first(),(RooRealVar *)argset_parameters_1H->selectByName("*nCB_High*")->first());

      double pvalue=TMath::Prob(chi2,ndf);

      double Z=-TMath::NormQuantile(pvalue/2); //division by 2 because chi2 counts also the deficit as an uncertainty
     
      cout << "----------------------------" << endl;
      cout << string_category << endl;
      cout << string_campaign_MxAOD << endl;

      printf("chi2/ndf=%4.2f (%4.2f / %d ), p-value=%4.2f, Z=%4.2f\n",chi2/ndf,chi2,ndf,pvalue,Z);

      /*
      TIterator *iter=0;  
      RooRealVar *roorealvar=0;
      
      iter=argset_parameters_1H->createIterator();
      
      while ((roorealvar=(RooRealVar *)iter->Next())) {
	cout << roorealvar->GetName() << ", " << roorealvar->getVal() << " +/- " << roorealvar->getError() << endl;
      }
      delete iter;
      */

    }
  }
  
  return 0;
}

void AddToChi2(double &chi2,int &ndf,RooRealVar *roorealvar_HH,RooRealVar *roorealvar_1H)
{
  /*
  cout << "======" << endl;
  cout << roorealvar_HH->GetName() << endl;
  cout << "roorealvar_HH=" << roorealvar_HH->getVal() << " +/- " << roorealvar_HH->getError() << endl;
  cout << "roorealvar_1H=" << roorealvar_1H->getVal() << " +/- " << roorealvar_1H->getError() << endl;
  */  
  
  if (roorealvar_HH->getMin()!=0) {
    if (fabs((roorealvar_HH->getVal()-roorealvar_HH->getMin())/roorealvar_HH->getMin())<0.0001)
      return;
  }
  else if (fabs((roorealvar_HH->getVal()-roorealvar_HH->getMin()))<0.01)
    return;
  
  if (roorealvar_1H->getMin()!=0) {
    if (fabs((roorealvar_1H->getVal()-roorealvar_1H->getMin())/roorealvar_1H->getMin())<0.0001)
      return;
  }
  else if (fabs((roorealvar_1H->getVal()-roorealvar_1H->getMin()))<0.01)
    return;
  
  
  if (fabs((roorealvar_HH->getVal()-roorealvar_HH->getMax())/roorealvar_HH->getMax())<0.0001)
    return;
  
  if (fabs((roorealvar_1H->getVal()-roorealvar_1H->getMax())/roorealvar_1H->getMax())<0.0001)
    return;
  
  
  //  cout << "before, chi2=" << chi2 << endl;  
  chi2+=pow(roorealvar_HH->getVal()-roorealvar_1H->getVal(),2)/(pow(roorealvar_HH->getError(),2)+pow(roorealvar_1H->getError(),2));
  ndf++;
  //  cout << "internal, chi2=" << chi2 << ", ndf=" << ndf << endl;

  return;
}
