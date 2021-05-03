//the substraction could drive to aritificial apparent shift due to centered weighted for pdf different to center

void PrintHeaderResults(FILE **fpp,string string_process,string string_category,bool sorted)
{
  //fpp : file pointer on pointer

  if (sorted)
    (*fpp)=fopen((string("results/")+string_non_resonant_resonant+"/"+string_model+"/"+"Table_shape_analysis_"+string_non_resonant_resonant+"_proc_"+string_process+"_cat_"+string_category+"_sorted.tex").c_str(),"wt");
  else
    (*fpp)=fopen((string("results/")+string_non_resonant_resonant+"/"+string_model+"/"+"Table_shape_analysis_"+string_non_resonant_resonant+"_proc_"+string_process+"_cat_"+string_category+".tex").c_str(),"wt");
 
  fprintf(*fpp,"\\begin{table}[h!]\n");
  /*
    if (string_model=="m_yy_and_m_bb") {
    fprintf(*fpp,"\\begin{table}[h!]\n");
    fprintf(*fpp,"\\scalebox{0.52} {\n");
    }
    else
    fprintf(*fpp,"\\begin{sidewaystable}[h!]\n");
  */
  fprintf(*fpp,"\\tiny\n");
  fprintf(*fpp,"\\begin{tabular}{");
  
  //because weight is an additional parameter

  //TO DO : change by vector

  for (unsigned int index_finalDV=0;index_finalDV<argset_finalDV_noWeight.size();index_finalDV++) {
    fprintf(*fpp,"|l|l|"); //functional form & n params

    fprintf(*fpp,"l|"); //sigma68
    //l|l|
    // & mu_peak & sigma68
  }
  
  
  fprintf(*fpp,"|l|"); //&chi2/ndf
  fprintf(*fpp,"|l|"); //p-value
  
  //  for (unsigned int index_finalDV=0;index_finalDV<argset_finalDV_noWeight.size();index_finalDV++) {
  //    fprintf(*fpp,"|l|l|l|l|l|l|"); //shape parameters
  //  }
  
  fprintf(*fpp,"}\n");
  
  fprintf(*fpp,"\\hline\n");
  //-----
  for (unsigned int index_finalDV=0;index_finalDV<argset_finalDV_noWeight.size();index_finalDV++) {
    fprintf(*fpp,"func. form ");
    
    if (argset_finalDV_noWeight.size()!=1)
      fprintf(*fpp,"%d",index_finalDV+1);
    
    fprintf(*fpp,"            &$n_{par}$ ");
    //     fprintf(*fpp,"            &$\\mu_{peak}\ [GeV]$ ");
    fprintf(*fpp,"            &$\\sigma_{68}\\ [GeV]$ ");

    if (index_finalDV+1<argset_finalDV_noWeight.size())
      fprintf(*fpp,"  &");
  }

  int max_parameters_functional_form=6; //for Double Crystal-Ball
  
  cout << "argset_finalDV_noWeight.size()=" << argset_finalDV_noWeight.size() << endl;
  
  //  fprintf(*fpp,"%s",(string("&$p$    &$\\chi^2/ndf$")).c_str());
  fprintf(*fpp,"%s",(string("   &$\\chi^2/ndf$")).c_str());
  fprintf(*fpp,"&p-value");
  
  //fprintf(*fpp,"%s",(string("&\\multicolumn{")+to_string(max_parameters_functional_form*argset_finalDV_noWeight.size())+"}{c|}{Parameters shape}").c_str());
  fprintf(*fpp,"\\\\\n");
  //-----
  for (unsigned int index_finalDV=0;index_finalDV<vec_string_finalDV.size();index_finalDV++) {
    //    fprintf(*fpp,"\\verb|%s|    &",((RooRealVar *) RooArgList(argset_finalDV_noWeight).at(index_finalDV))->GetName());
    fprintf(*fpp,"%s    &",vec_string_latex_finalDV[index_finalDV].c_str());
    fprintf(*fpp,"      &"); //for field sigma68
    if (index_finalDV+1<argset_finalDV_noWeight.size())
      fprintf(*fpp,"             &");
  }
  
  //  fprintf(*fpp,"%s","          &       &         &");
  //fprintf(*fpp,"%s","                 &         &");

  fprintf(*fpp,"%s","                 &         "); //for chi2/ndf
  fprintf(*fpp,"%s","                 &         "); //for p-value

  /*
    for (unsigned int index_finalDV=0;index_finalDV<argset_finalDV_noWeight.size();index_finalDV++) {
    string string_finalDV_multicolumn=((RooRealVar *) RooArgList(argset_finalDV_noWeight).at(index_finalDV))->GetName();
    boost::replace_all(string_finalDV_multicolumn,"_","\\_");
    
    fprintf(*fpp,"\\multicolumn{%d}{c|}{%s}",max_parameters_functional_form,string_finalDV_multicolumn.c_str());

    if (index_finalDV+1<argset_finalDV_noWeight.size())
    fprintf(*fpp,"   &");
    }
  */
  fprintf(*fpp,"     \\\\\n");
  
  fprintf(*fpp,"\\hline\n");
}
//===========================================================================================================
void PrintTailResults(FILE **fpp,string string_process,string string_category)
{
  fprintf(*fpp,"\\end{tabular}\n");
  
  //  if (string_model=="m_yy_and_m_bb")
  //    fprintf(*fpp,"}\n"); //end scale box

  string string_category_caption=string_category;
  boost::replace_all(string_category_caption,"_","\\_");

  string string_non_resonant_resonant_caption=string_non_resonant_resonant;

  if (string_non_resonant_resonant=="non_resonant")
    boost::replace_all(string_non_resonant_resonant_caption,"_","\\_");
  
  string string_process_caption=string_process;
  
  cout << "string_process_caption=" << string_process_caption << endl;
  boost::replace_all(string_process_caption,"_","\\_");
  
  fprintf(*fpp,"%s",(string("\\caption{Results for ")+string_non_resonant_resonant_caption+", "+string_process_caption+", "+string_category_caption+"}\n").c_str());
  
  fprintf(*fpp,"%s",(string("\\label{")+string_non_resonant_resonant+"_"+string_category+"_"+string_process+string("}\n")).c_str());

  /*
    if (string_model=="m_yy_and_m_bb") {
    fprintf(*fpp,"\\end{table}\n");
    }
    else
    fprintf(*fpp,"\\end{sidewaystable}\n");
  */
  fprintf(*fpp,"\\end{table}\n");

  fclose(*fpp);
}
//===========================================================================================================
void ReturnWindowFromDatasetInitFitParameters(float percentage,TChain *chain_process,string string_process,string string_finalDV,double *preferred_low_x,double *preferred_high_x)
{
  cout << "Search Window for fit range containing fraction=" << percentage << ", for finalDV=" << string_finalDV << endl;

  RooRealVar *roorealvar_finalDV=(RooRealVar *)argset_finalDV_noWeight.find(string_finalDV.c_str());

  int nb_bins=roorealvar_finalDV->numBins();
  double min_hist=roorealvar_finalDV->getMin();
  double max_hist=roorealvar_finalDV->getMax();

  if (string_finalDV=="m_yy") {
    nb_bins=(int)((max_hist-min_hist)/1.);
  }

  TH1D *hist_projection=new TH1D("hist_projection","hist_projection",nb_bins,min_hist,max_hist);
     
  //  cout << "string_finalDV=" << string_finalDV << endl;
  //   cout << "roorealvar_finalDV->numBins()=" << roorealvar_finalDV->numBins() << endl;
  //   cout << "roorealvar_finalDV->getMin()=" << roorealvar_finalDV->getMin() << endl;
  //   cout << "roorealvar_finalDV->getMax()=" << roorealvar_finalDV->getMax() << endl;
  
  string string_weight_and_cut="weight_total";
  
  //prevent huge tail for m_bb of X
  
  if (string_finalDV=="m_bb" && 
      (string_process=="gg_X2000" || string_process=="gg_X3000")
      )
    string_weight_and_cut+="*(m_bb<250)";
  
  chain_process->Project("hist_projection",string_finalDV.c_str(),string_weight_and_cut.c_str());
  
  TCanvas *canvas=new TCanvas("canvas","canvas",800,600);
  hist_projection->Draw();
  canvas->SaveAs("figures/test.png");
  delete canvas;

  //representing parameter for the mean of the pdf : use the max position, else it would depend on the range of the histogram
  double hist_integral=hist_projection->Integral(0,hist_projection->GetNbinsX()+1);
  double hist_max=hist_projection->GetMaximum();
  int hist_bin_position_max=hist_projection->GetMaximumBin();
  hist_position_max=hist_projection->GetBinCenter(hist_projection->GetMaximumBin());
  
  hist_position_FWHM_low=hist_projection->GetBinCenter(hist_projection->FindFirstBinAbove(0.5*hist_max));
  hist_position_FWHM_high=hist_projection->GetBinCenter(hist_projection->FindLastBinAbove(0.5*hist_max));
  
  cout << "hist_max=" << hist_max << endl;
  cout << "hist_position_max=" << hist_position_max << endl;
  cout << "hist_position_FWHM_low=" << hist_position_FWHM_low << endl;
  cout << "hist_position_FWHM_high=" << hist_position_FWHM_high << endl;
  
  //RMS is not enough representative, in particular for distributions that have a core and a long tail
  
  hist_sigma_effective=(hist_position_FWHM_high-hist_position_FWHM_low)/2.355;
  
  cout << "hist_sigma_effective=" << hist_sigma_effective << endl;
  
  //variante from FWHM : less stable ; double hist_sigma=(hist->GetBinCenter(hist->FindLastBinAbove(0.5*hist_max))-hist->GetBinCenter(hist->FindFirstBinAbove(0.5*hist_max)))/2.355;
  
  //next two lines : not used
  double hist_minimum_x=hist_projection->GetXaxis()->GetXmin();
  double hist_maximum_x=hist_projection->GetXaxis()->GetXmax();
  
  int high_bin=hist_bin_position_max;
  int low_bin=hist_bin_position_max;
  float low_x=hist_projection->GetBinCenter(low_bin);
  float high_x=hist_projection->GetBinCenter(high_bin);
  
  *preferred_low_x=-99999;  //final solution to search for
  *preferred_high_x=99999;
  
  //	cout << "search for the window at most to the left" << endl;
  //1 : initialization : search for the window at most to the left
  
  //	cout << "hist_position_max-2*hist_sigma_effective=" << hist_position_max-2*hist_sigma_effective << endl;
  
  //for example of 251 GeV, it is mandatory to catch low value of 250 GeV
  for (;low_bin>=1;low_bin--) {
    
    low_x=hist_projection->GetBinCenter(low_bin);
    
    cout << "current window=[" << hist_projection->GetBinCenter(low_bin) << " ; " << hist_projection->GetBinCenter(high_bin) << "], frac Integral=" << hist_projection->Integral(low_bin,high_bin)/hist_integral << endl;
    
    if (hist_projection->Integral(low_bin,high_bin)>=percentage*hist_integral) { //found a possible solution
      //      cout << "found possible solution : window=[" << low_x << " ; " << high_x << ", frac Integral=" << hist_projection->Integral(low_bin,high_bin)/hist_integral << endl;
      if (high_x-low_x < (*preferred_high_x) - (*preferred_low_x) ) { //found a new best solution
	*preferred_low_x=low_x;
	*preferred_high_x=high_x;
      }
      break; //exit the loop on the search for left side: else it would be higher to requested percentage
    }
  }
  
  cout << "low_x=" << low_x << ", high_x=" << high_x << endl;
  cout << "hist_sigma_effective=" << hist_sigma_effective << endl;
  cout << "hist_position_max-2*hist_sigma_effective=" << hist_position_max-2*hist_sigma_effective << endl;
  cout << "first step result " << endl;
  
  cout << "so far, preferred solution for " << percentage << " : [" << *preferred_low_x << " ; " << *preferred_high_x << " ] " << endl;
  
  //2 : loop on method : increase left side by epsilon, and extend the right till having percentage_window_hist
  //  cout << "now loop on the right" << endl;
  
  while (low_bin<hist_bin_position_max) { // continue until the left side contains the maximum
    
    low_x=hist_projection->GetBinCenter(low_bin);
    
    //	  cout << "low_bin=" << low_bin << endl;
    
    //example 251 GeV: even 7 sigma is not enough, so explore until last bin
    for (high_bin=hist_bin_position_max;high_bin<=hist_projection->GetNbinsX();high_bin++) {     //explore up to maximum+5 sigma
      
      //      cout << "loop on the right" << endl;
      
      high_x=hist_projection->GetBinCenter(high_bin);
      
      cout << "current window=[" << hist_projection->GetBinCenter(low_bin) << " ; " << hist_projection->GetBinCenter(high_bin) << "], frac Integral=" << hist_projection->Integral(low_bin,high_bin)/hist_integral << endl;
      
      if (hist_projection->Integral(low_bin,high_bin)>=percentage*hist_integral) { //found a possible solution
	//cout << "found possible solution : window=[" << low_x << " ; " << high_x << ", frac Integral=" << hist_projection->Integral(low_bin,high_bin)/hist_integral << endl;
	if (high_x-low_x < (*preferred_high_x) - (*preferred_low_x) ) { //found a new best solution
	  *preferred_low_x=low_x;
	  *preferred_high_x=high_x;
	}
	break; //exit the loop on the search for right side, else it will be higher to percentage
      }
    } //end high side
    
    low_bin++;
    
  } //end loop on low side
  
  delete hist_projection;
}
//===========================================================================================================
void ReturnWindow(float percentage,RooAbsPdf *pdf_signal,string string_finalDV,float mResonance,double *preferred_left_side,double *preferred_right_side,string string_category)
{
  //mResonance could be used as optional, in case no info on the peak position from the shape parameters

  cout << "=============================" << endl;
  cout << "Start ReturnWindow" << endl;
  cout << "string_non_resonant_resonant=" << string_non_resonant_resonant << endl;
  cout << "string_model=" << string_model << endl;

  double current_mass=0;
  RooRealVar *roorealvar_finalDV=(RooRealVar*)(pdf_signal->getVariables()->find(string_finalDV.c_str()));
  
  if (!roorealvar_finalDV) {
    cout << "didn't find finalDV variable, halt program" << endl;
    exit(1);
  }
  
  double sigma_low=0;
  double sigma_high=0;

  //initialization of mass to the peak parameter minus a margin, in order to start algorithm searching for mass of maximum
  //grab also the sigma parameter in order to have an estimation, for the maximum extension used afterwards in the search for percentage window
  
  if (!strcmp(pdf_signal->GetName(),(string("Pdf_Signal_Gaussian_")+string_finalDV).c_str())) {
    current_mass=((RooRealVar*)pdf_signal->getVariables()->find((string("muGauss_")+string_finalDV).c_str()))->getVal();
    sigma_low=((RooRealVar*)pdf_signal->getVariables()->find((string("sigmaGauss_")+string_finalDV).c_str()))->getVal();
    sigma_high=((RooRealVar*)pdf_signal->getVariables()->find((string("sigmaGauss_")+string_finalDV).c_str()))->getVal();
  }
  else if (!strcmp(pdf_signal->GetName(),(string("Pdf_Signal_CrystalBall_")+string_finalDV).c_str())) {
    current_mass=((RooRealVar*)pdf_signal->getVariables()->find((string("mu_simple_CB_")+string_finalDV).c_str()))->getVal();
    sigma_low=((RooRealVar*)pdf_signal->getVariables()->find((string("sigma_simple_CB_")+string_finalDV).c_str()))->getVal();
    sigma_high=((RooRealVar*)pdf_signal->getVariables()->find((string("sigma_simple_CB_")+string_finalDV).c_str()))->getVal();
  }
  else if (!strcmp(pdf_signal->GetName(),(string("Pdf_Signal_DoubleCrystalBall_")+string_finalDV+"_"+string_category).c_str())) {
    current_mass=((RooRealVar*)pdf_signal->getVariables()->find((string("muCB_")+string_finalDV+"_"+string_category).c_str()))->getVal();
    sigma_low=((RooRealVar*)pdf_signal->getVariables()->find((string("sigmaCB_")+string_finalDV+"_"+string_category).c_str()))->getVal();
    sigma_high=((RooRealVar*)pdf_signal->getVariables()->find((string("sigmaCB_")+string_finalDV+"_"+string_category).c_str()))->getVal();
  }
  else if (!strcmp(pdf_signal->GetName(),(string("Pdf_Signal_Bukin_")+string_finalDV).c_str())) {
    current_mass=((RooRealVar*)pdf_signal->getVariables()->find((string("muBukin_")+string_finalDV).c_str()))->getVal();
    sigma_low=((RooRealVar*)pdf_signal->getVariables()->find((string("sigmaBukin_")+string_finalDV).c_str()))->getVal();
    sigma_high=((RooRealVar*)pdf_signal->getVariables()->find((string("sigmaBukin_")+string_finalDV).c_str()))->getVal();
  }
  else if (!strcmp(pdf_signal->GetName(),(string("Pdf_Signal_ExpGausExp_")+string_finalDV).c_str())) {
    current_mass=((RooRealVar*)pdf_signal->getVariables()->find((string("muExpGausExp_")+string_finalDV).c_str()))->getVal();
    sigma_low=((RooRealVar*)pdf_signal->getVariables()->find((string("sigmaExpGausExp_")+string_finalDV).c_str()))->getVal();
    sigma_high=((RooRealVar*)pdf_signal->getVariables()->find((string("sigmaExpGausExp_")+string_finalDV).c_str()))->getVal();
  }
  else if (!strcmp(pdf_signal->GetName(),(string("Pdf_Signal_Novosibirsk_")+string_finalDV).c_str())) {
    current_mass=((RooRealVar*)pdf_signal->getVariables()->find((string("peak_Novosibirsk_")+string_finalDV).c_str()))->getVal();
    sigma_low=((RooRealVar*)pdf_signal->getVariables()->find((string("width_Novosibirsk_")+string_finalDV).c_str()))->getVal();
    sigma_high=((RooRealVar*)pdf_signal->getVariables()->find((string("width_Novosibirsk_")+string_finalDV).c_str()))->getVal();
  }
  
  cout << "sigma_low=" << sigma_low << endl;
  cout << "sigma_high=" << sigma_high << endl;

  cout << "current_mass=" << current_mass << endl;
  current_mass/=1.05; //reduces by 5 %
  
  if (current_mass<roorealvar_finalDV->getMin())
    current_mass=roorealvar_finalDV->getMin();

  //rename to step_finalDV
  
  double step_scan=0.1*sigma_high;
  
  //Search for the exact position of the max

  cout << "current_mass=" << current_mass << endl;

  roorealvar_finalDV->setVal(current_mass);
  
  double current_value=pdf_signal->getVal(RooArgSet(*roorealvar_finalDV));

  cout << "current_value=" << current_value << endl;

  double previous_value=current_value-0.1; //deliberate put the previous value to a lower value by a dumb shift
  
  printf("current_mass=%10.10f\n",current_mass);
  cout << "previous_value=" << previous_value << endl;
  
  cout << endl;
  cout << "search at the right" << endl;
  while (current_value>previous_value) { //it will naturally stop when the mass if at the maximum+ESPILON
    current_mass+=step_scan;
    //    printf("current_mass=%10.10f\n",current_mass);
    roorealvar_finalDV->setVal(current_mass);
    previous_value=current_value;
    current_value=pdf_signal->getVal(RooArgSet(*roorealvar_finalDV));
    //    cout << "current_value=" << current_value << endl;
    //    cout << "previous_value=" << previous_value << endl;
  }

  current_mass-=step_scan; //go back to left by one unit
  roorealvar_finalDV->setVal(current_mass);
  
  double mass_maximum=current_mass;
  double max=pdf_signal->getVal(RooArgSet(*roorealvar_finalDV));
  
  printf("mass_maximum=%4.5f\n",mass_maximum);
  
  // backup solution in case no parameter of width
  /*
  //---------------------------------
  //1) Search for the pseudo FWHM at the left : this allows for afterwards to know the limits where roughly to stop the search
  
  roorealvar_finalDV->setVal(mass_maximum);
  
  current_mass=mass_maximum;
  current_value=max;

  //search for the pdf of the current finalDV, in order to access to the spread parameter, to judge the maximum for extension at left and right
  //to rename as internal

  unsigned int index_finalDV=0;
  
  for (unsigned index_finalDV=0;index_finalDV<vec_string_finalDV.size();index_finalDV++) {
  if (vec_string_finalDV[index_finalDV]==string_finalDV)
  break;
  }

  if (index_finalDV>=vec_string_finalDV.size()) {
  cout << "string_finalDV not found, halt program" << endl;
  exit(1);
  }

  double sigma_parameter=0;
  
  if (vec_string_signal_model[index_finalDV]=="DBCB")
  sigma_parameter=((RooRealVar *)(vec_pdf_signal[index_finalDV]->getVariables()->find( (string("SignalPdf_")+string( ((RooRealVar *) RooArgList(argset_finalDV_noWeight).at(index_finalDV))->GetName() ) + "_"+string("sigmaCB")).c_str())))->getVal();
  else if (vec_string_signal_model[index_finalDV]=="ExpGausExp")
  sigma_parameter=((RooRealVar *)(vec_pdf_signal[index_finalDV]->getVariables()->find( (string("SignalPdf_")+string( ((RooRealVar *) RooArgList(argset_finalDV_noWeight).at(index_finalDV))->GetName() ) + "_"+string("sigmaGauss")).c_str())))->getVal();

  cout << "sigma_parameter=" << sigma_parameter << endl;
  */

  //does not go beyond N*sigma effective

  // method from smallest interval that contains percentage of events
  // algorithm : sliding variable window :
  // fix right side of window to maximum. Extend the left side of window till having percentage
  // loop to increase left side by epsilon
  // for each value of the left side, extend the right side till having percentage
  // among the different window, take the smallest one and divide it by 2 : this is the sigma
  
  //restore context to have the maximum computed already in the previous method
  roorealvar_finalDV->setVal(mass_maximum);
  
  //  double step_scan_coarse=0.5;
  double step_scan_coarse_low=0.1*sigma_low;
  double step_scan_coarse_high=0.1*sigma_high;

  double right_side=mass_maximum;
  double left_side=mass_maximum;

  *preferred_left_side=-99999;  //final solution to search for
  *preferred_right_side=99999;
  
  cout << "phase 1 : [ " << *preferred_left_side << " ; " << *preferred_right_side << " ] " << endl;

  //cout << "step_scan_coarse_low=" << step_scan_coarse_low << endl;
  
  cout << "search for the window at most to the left" << endl;
  //1 : initialization : search for the window at most to the left  
  //  for (;left_side>mass_maximum-6*sigma_low;left_side-=step_scan_coarse_low) {

  //for (;left_side>roorealvar_finalDV->getMin() && left_side>mass_maximum-6*sigma_low;left_side-=step_scan_coarse_low) {
  //  for (;left_side>roorealvar_finalDV->getMin() && left_side>mass_maximum-7*sigma_low;left_side-=step_scan_coarse_low) {

  //7 is not enough for mX=3000 for example, for sure

  for (;left_side>roorealvar_finalDV->getMin() && left_side>mass_maximum-10*sigma_low;left_side-=step_scan_coarse_low) {
    
    //    cout << "left_side=" << left_side << endl;
    
    roorealvar_finalDV->setRange("RangeToConsider",left_side,right_side);
    RooAbsReal* integralInChosenRange=pdf_signal->createIntegral(*roorealvar_finalDV,*roorealvar_finalDV,"RangeToConsider");
    //cout << "current window=[" << left_side << " ; " << right_side << "], Integral=" << integralInChosenRange->getVal(RooArgSet(*roorealvar_finalDV)) << endl;
    
    if (integralInChosenRange->getVal(RooArgSet(*roorealvar_finalDV))>=percentage) { //found a possible solution
      //      cout << "found possible solution : window=[" << left_side << " ; " << right_side << "], sigma=" << (right_side-left_side)/2 << endl;
      if (right_side-left_side < *preferred_right_side - *preferred_left_side) { //found a new best solution
	*preferred_left_side=left_side;
	*preferred_right_side=right_side;
      }
      break; //exit the loop on the search for left side
    }
  }
  
  cout << "first step result " << endl;
  cout << "preferred solution passing threshold of fraction=" << percentage << " : [" << *preferred_left_side << " ; " << *preferred_right_side << " ] " << endl;
  cout << "left_side=" << left_side << endl;
  
  //2 : loop on method : increase left side by epsilon, and extend the right till having percentage %
  cout << "now loop on the right" << endl;
  
  //mandatory to put <=, else for case of pdf decreasing only, algorithm will not work
  while (left_side<=mass_maximum) { // continue until the left side contains the maximum
  //bug  while (left_side<mass_maximum) { // continue until the left side contains the maximum
    //    for (right_side=mass_maximum;right_side<roorealvar_finalDV->getMax() && right_side<mass_maximum+6*sigma_high;right_side+=step_scan_coarse_high) {     //explore up to maximum+3 sigma
    for (right_side=mass_maximum;right_side<roorealvar_finalDV->getMax() && right_side<mass_maximum+8*sigma_high;right_side+=step_scan_coarse_high) {     //explore up to maximum+3 sigma

      RooAbsReal* integralInChosenRange=0;
      
      //      cout << "left_side=" << left_side << ", right_side=" << right_side << endl;
      roorealvar_finalDV->setRange("RangeToConsider",left_side,right_side);
      integralInChosenRange=pdf_signal->createIntegral(*roorealvar_finalDV,*roorealvar_finalDV,"RangeToConsider");

      //      cout << "current window=[" << left_side << " ; " << right_side << "], Integral=" << integralInChosenRange->getVal(RooArgSet(*roorealvar_finalDV)) << endl;

      if (integralInChosenRange->getVal(RooArgSet(*roorealvar_finalDV))>=percentage) { //found a possible solution
	//cout << "found possible solution : window=[" << left_side << " ; " << right_side << "], sigma=" << (right_side-left_side)/2 << endl;
	if (right_side-left_side < *preferred_right_side - *preferred_left_side) { //found a new best solution
	  *preferred_left_side=left_side;
	  *preferred_right_side=right_side;
	}
	break; //exit the loop on the search for right side
      }
    } //end high side
    
    left_side+=step_scan_coarse_low;
  } //end loop on left side
  
  //do not apply any rounding
  
  cout << "preferred solution for " << percentage << " : [" << *preferred_left_side << " ; " << *preferred_right_side << " ] " << endl;
  
  return;
}
//===========================================================================================================
void PrintOverviewResultsShape(result_f_process current_results_f_process,string string_category)
{
  FILE *fp=fopen((string("results/")+string_non_resonant_resonant+"/"+string_model+"/"+"Table_shape_Overview_analysis_"+string_non_resonant_resonant+"_cat_"+string_category+".tex").c_str(),"wt");
  
  fprintf(fp,"\\begin{table}[h!]\n");
  //fprintf(fp,"\\begin{sidewaystable}[h!]\n");

  fprintf(fp,"\\tiny\n");
  fprintf(fp,"\\begin{tabular}{|l|l");
  
  fprintf(fp,"|l|"); //process
  
  //vec_string_finalDV.size() is more powerful than argset since we clear this last one
  for (unsigned int index_finalDV=0;index_finalDV<vec_string_finalDV.size();index_finalDV++) {
    fprintf(fp,"l|");
    fprintf(fp,"l|l|"); //mu peak and sigma68
  }
  
  fprintf(fp,"}\n");
  
  fprintf(fp,"\\hline\n");

  fprintf(fp,"Process   &");

  for (unsigned int index_finalDV=0;index_finalDV<vec_string_finalDV.size();index_finalDV++) {

    cout << "index_finalDV=" << index_finalDV << endl;

    if (index_finalDV!=0)
      fprintf(fp,"  &");

    fprintf(fp,"  func. form ");
    if (vec_string_finalDV.size()!=1)
      fprintf(fp,"%d ",index_finalDV+1);

    fprintf(fp,"  &$\\mu_{peak}\\ [GeV]$     &$\\sigma_{68}\\ [GeV]$"); //mu peak and sigma68
  }
  
  fprintf(fp,"\\\\\n");

  fprintf(fp,"& "); //empty for process

  for (unsigned int index_finalDV=0;index_finalDV<vec_string_finalDV.size();index_finalDV++) {
    fprintf(fp,"%s             ",vec_string_latex_finalDV[index_finalDV].c_str());
    fprintf(fp,"&  & "); //for mu peak and sigma68
    if (index_finalDV+1<vec_string_finalDV.size())
      fprintf(fp,"             &");
  }
  fprintf(fp,"     \\\\\n");
  
  fprintf(fp,"\\hline\n");
  cout << "current_results_f_process.vec_string_process.size()=" << current_results_f_process.vec_string_process.size() << endl;
  for (unsigned int index_process=0;index_process<current_results_f_process.vec_string_process.size();index_process++) {
    cout << "inside loop process, index_process=" << index_process << endl;
    fprintf(fp,"\\verb|%s|     &",current_results_f_process.vec_string_process[index_process].c_str());
    
    for (unsigned int index_finalDV=0;index_finalDV<vec_string_finalDV.size();index_finalDV++) {
      fprintf(fp,"%s    ",current_results_f_process.vec_string_functional_form[index_process][index_finalDV].c_str());

      fprintf(fp,"&%6.2f &%6.2f",current_results_f_process.vec_mu_model_chosen[index_process][index_finalDV],current_results_f_process.vec_sigma68[index_process][index_finalDV]);
      
      if (index_finalDV+1<vec_string_finalDV.size())
	fprintf(fp,"    &");
    }
    fprintf(fp,"\\\\\n");
    
    fprintf(fp,"\\hline\n");
  } //end loop on process
  
  fprintf(fp,"\\end{tabular}\n");
  
  string string_category_caption=string_category;
  boost::replace_all(string_category_caption,"_","\\_");

  string string_non_resonant_resonant_caption=string_non_resonant_resonant;

  cout << "will replace all 1" << endl;

  if (string_non_resonant_resonant=="non_resonant")
    boost::replace_all(string_non_resonant_resonant_caption,"_","\\_");
  
  fprintf(fp,"%s",(string("\\caption{Overview results for ")+string_non_resonant_resonant_caption+", "+string_category_caption+"}\n").c_str());
  fprintf(fp,"%s",(string("\\label{")+string_non_resonant_resonant+"_"+string_category+string("}\n")).c_str());
  fprintf(fp,"\\end{table}\n");
  //fprintf(fp,"\\end{sidewaystable}\n");
  fclose(fp);
  //---------------------------
  if (do_fit_shape) {
    for (unsigned int index_process=0;index_process<current_results_f_process.vec_string_process.size();index_process++) {
      
      string string_process=current_results_f_process.vec_string_process[index_process];
      
      for (unsigned int index_finalDV=0;index_finalDV<vec_string_finalDV.size();index_finalDV++) {
	
	string string_finalDV=vec_string_finalDV[index_finalDV];

	ofstream stream_datacard_parameters_shape;
	stream_datacard_parameters_shape.open((string("results/")+string_non_resonant_resonant+"/"+string_model+"/export/"+"datacard_proc_"+string_process+"_"+string_finalDV+"_cat_"+string_category+".txt").c_str());
	
	stream_datacard_parameters_shape << "[" << string_category << "]" << endl;
	stream_datacard_parameters_shape << endl;
	
	((RooArgSet)current_results_f_process.vec_arglist_parameters[index_process][index_finalDV]).writeToStream(stream_datacard_parameters_shape,0,string_category.c_str());

	//automatically add a line for the next set
	
	//	if (index_finalDV+1<vec_string_finalDV.size())
	//	  stream_datacard_parameters_shape << endl;
	
	//      stream_datacard_parameters_shape << "#---------------------------------------" << endl;
	stream_datacard_parameters_shape.close();
      } //end finalDV

    } //end loop on process
  }
}
//===========================================================================================================
//===========================================================================================================
double GetCrossSectionTimesBR(string string_process)
{
  double cross_section_times_br=-1;
  
  if (string_process=="gg_HH" || string_process=="gg_HH_NLO" || string_process=="gg_HH_NLO_train_events" 
      || string_process=="PowhegPy8_HHbbyy_cHHH01d0"
      ) {
    //this is for mH=125.09 GeV
    cross_section_times_br=8.18086e-5*1.e-12; //DSID : 600051 : BR H->gamgam already included, BR H->bb already included
  }
  else if (string_process=="gg_HH_NLO_kappa_lambda_10") {
    cross_section_times_br=1.7110E-03*1.e-12; //DSID : 600051 : BR H->gamgam already included, BR H->bb already included
  }
  else if (string_process=="vbf_HH") {

    //this if for mH=125.0 GeV for Py8 version
    //so correct it to 125.09 GeV
    
    cross_section_times_br=4.551955636e-6*(1.723/1.726)*1.e-12; //DSID 503004 : BR H->gamgam already included, BR H->bb already included
    //shit    cross_section_times_br=4.5440E-6*1.e-12; //DSID : 450031 : BR H->gamgam already included, BR H->bb already included
  }

  else if (string_process=="vbf_HH_kappa_lambda_0") {
    
    //this if for mH=125.0 GeV for Py8 version
    //so correct it to 125.09 GeV
    
    cross_section_times_br=1.22285587849e-5*(1.723/1.726)*1.e-12; //DSID : 503010 : BR H->gamgam already included, BR H->bb already included
  }
  else if (string_process=="vbf_HH_kappa_lambda_2") {
    //this if for mH=125.0 GeV for Py8 version
    //so correct it to 125.09 GeV
    
    cross_section_times_br=4.12762078854e-6*(1.723/1.726)*1.e-12; //DSID : 503011 : BR H->gamgam already included, BR H->bb already included
  }
  else if (string_process=="vbf_HH_kappa_lambda_10") {
    //this if for mH=125.0 GeV for Py8 version
    //so correct it to 125.09 GeV

    cross_section_times_br=2.60001533785e-4*(1.723/1.726)*1.e-12; //DSID : 503012 : BR H->gamgam already included, BR H->bb already included
  }  
  else if (string_process=="gg_vbf_HH") {
    //this if for mH=125.09 GeV for gg HH
    // and 125 for VBF HH : so make a fit for VBF HH to move to 125.0 GeV
    
    cross_section_times_br=(8.18086e-5+(1.723/1.726)*4.551955636e-6)*1.e-12; //DSID : 600051 : BR H->gamgam already included, BR H->bb already included

    //bias    cross_section_times_br=(8.18086e-5+4.551955636e-6)*1.e-12; //DSID : 600051 : BR H->gamgam already included, BR H->bb already included
    //shit    cross_section_times_br=(8.18086e-5+4.5440E-6)*1.e-12; //DSID : 600051 : BR H->gamgam already included, BR H->bb already included
  }
  //----------
  else if (string_process.find("reweight_mHH_1p0_to_")!=string::npos) {
    string string_expression="reweight_mHH_1p0_to_";
    size_t position_string=string_process.find(string_expression);
    position_string+=string_expression.size();
    
    string string_target_kappa=string_process.substr(position_string);

    string string_sample="PowhegH7_HHbbyy_reweight_mHH_1p0_to_"+string_target_kappa+"_nominal.root";

    float numerical_target_kappa=Return_numerical_target_kappa(string_target_kappa); 
    
    cross_section_times_br=ReturnCrossSectionTimesBR(numerical_target_kappa)*1.e-15;
  }
  //-----------------------------------------------
  //reference : https://indico.cern.ch/event/821325/contributions/3433651/attachments/1886891/3110925/ResonantXS_260719.pdf
  //https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/DiHiggsTobbyy#Cross_sections_for_the_optimisat

  else if (string_process=="gg_X251")
    cross_section_times_br=9.5973e-4*1.e-12; //DSID : 450527 includes already 2 * times BRgamgam BRbb
  else if (string_process=="gg_X260")
    cross_section_times_br=9.5973e-4*1.e-12; //DSID : 450528 : includes already 2 * times BRgamgam BRbb





  
  else if (string_process=="gg_X270")
    cross_section_times_br=9.981e-4*1.e-12; //DSID : 451892 : includes already 2 * times BRgamgam BRbb

  else if (string_process=="gg_X290")
    cross_section_times_br=1.0e-3*1.e-12; //DSID : 451893 : includes already 2 * times BRgamgam BRbb

  else if (string_process=="gg_X312.5")
    cross_section_times_br=8.399e-4*1.e-12; //DSID : 451894 : includes already 2 * times BRgamgam BRbb

  else if (string_process=="gg_X337.5")
    cross_section_times_br=6.345e-4*1.e-12; //DSID : 451895 : includes already 2 * times BRgamgam BRbb

  else if (string_process=="gg_X375")
    cross_section_times_br=4.811e-4*1.e-12; //DSID : 451896 : includes already 2 * times BRgamgam BRbb

  else if (string_process=="gg_X425")
    cross_section_times_br=3.188e-4*1.e-12; //DSID : 451897 : includes already 2 * times BRgamgam BRbb

  else if (string_process=="gg_X475")
    cross_section_times_br=2.044e-4*1.e-12; //DSID : 451898 : includes already 2 * times BRgamgam BRbb

  

  else if (string_process=="gg_X280"
	   ||
	   string_process=="gg_X280_Py8"
	   )
    cross_section_times_br=1.0388e-3*1.e-12; //DSID : 450529 includes already 2 * times BRgamgam BRbb
  else if (string_process=="gg_X300")
    cross_section_times_br=9.6416e-4*1.e-12; //DSID : 450530 includes already 2 * times BRgamgam BRbb
  else if (string_process=="gg_X325")
    cross_section_times_br=7.1762e-4*1.e-12; //DSID : 450531 includes already 2 * times BRgamgam BRbb
  else if (string_process=="gg_X350")
    cross_section_times_br=5.5285e-4*1.e-12; //DSID : 450532 includes already 2 * times BRgamgam BRbb
  else if (string_process=="gg_X400")
    cross_section_times_br=4.1052e-4*1.e-12; //DSID : 450533 includes already 2 * times BRgamgam BRbb
  else if (string_process=="gg_X450")
    cross_section_times_br=2.2778e-4*1.e-12; //DSID : 450534 includes already 2 * times BRgamgam BRbb
  else if (string_process=="gg_X500"
	   ||
	   string_process=="gg_X500_Py8"
	   )
    cross_section_times_br=1.8156e-4*1.e-12; //DSID : 450535 includes already 2 * times BRgamgam BRbb
  else if (string_process=="gg_X550")
    cross_section_times_br=1.5602e-4*1.e-12; //DSID : 450536 includes already 2 * times BRgamgam BRbb
  else if (string_process=="gg_X600")
    cross_section_times_br=1.0412e-4*1.e-12; //DSID : 450537 includes already 2 * times BRgamgam BRbb
  else if (string_process=="gg_X700")
    cross_section_times_br=6.8335e-5*1.e-12; //DSID : 450538 includes already 2 * times BRgamgam BRbb
  else if (string_process=="gg_X800")
    cross_section_times_br=5.1825e-5*1.e-12; //DSID : 450539 includes already 2 * times BRgamgam BRbb
  else if (string_process=="gg_X900")
    cross_section_times_br=4.0684e-5*1.e-12; //DSID : 450540 includes already 2 * times BRgamgam BRbb
  else if (string_process=="gg_X1000"
	   ||
	   string_process=="gg_X1000_Py8"
	   )
    cross_section_times_br=3.3025e-5*1.e-12; //DSID : 450541 includes already 2 * times BRgamgam BRbb
  else if (string_process=="gg_X2000")
    //in old framework    cross_section_times_br=0.001*1.e-12*2*0.5809*0.00227; //DSID : 450542
    cross_section_times_br=9.0e-6*1.e-12; //DSID : 450542 includes already 2 * times BRgamgam BRbb
  else if (string_process=="gg_X3000")
    cross_section_times_br=8.0557e-6*1.e-12; //DSID : 450543 includes already 2 * times BRgamgam BRbb
  //-----------------------------------------------
  else if (string_process=="ggH")
    cross_section_times_br=0.1101404*1.e-12; //DSID : 343981 //BR : H->gamgam already included
  else if (string_process=="VBF")
    cross_section_times_br=0.00857833*1.e-12; //DSID : 343981 //BR : H->gamgam already included
  else if (string_process=="WH")
    cross_section_times_br=(0.00190226+0.00120605)*1.e-12; //DSID : 345317, 345318 //BR : H->gamgam already included
  else if (string_process=="ZH")
    cross_section_times_br=(0.001724519+0.000278529)*1.e-12; //DSID : 345319, 345061 //BR : H->gamgam already included
  else if (string_process=="ttH")
    cross_section_times_br=0.001149755*1.e-12; //DSID : 345863 //BR : H->gamgam already included
  else if (string_process=="bbH")
    cross_section_times_br=0.00110390*1.e-12; //DSID : 345315 //BR : H->gamgam already included
  else if (string_process=="tHjb")
    cross_section_times_br=0.00016857*1.e-12; //DSID : 364188 //BR : H->gamgam already included
  else if (string_process=="tWH")
    cross_section_times_br=3.44359e-5*1.e-12; //DSID : 346486 //BR : H->gamgam already included
  
  else if (string_process=="SingleHiggs") {
    //cross_section_times_br=(0.1101404+0.00857833+0.001724519+0.000278529+0.001149755+0.00016857)*1.e-12; //DSID : 343981 //BR : H->gamgam already included
    cross_section_times_br=(0.1101404+0.00857833+0.00190226+0.00120605+0.001724519+0.000278529+0.001149755+0.00110390+0.00016857+3.44359e-5)*1.e-12; //DSID : 343981 //BR : H->gamgam already included
  }
  else {
    cout << "problem, add cross-section times br, halt program" << endl;
    exit(1);
  }

  return cross_section_times_br;
}
//===========================================================================================================
void PrintResultYieldEfficiency(string string_yield_efficiency)
{
  //for HH resonant, to do a parametrisation : to store yield somewhere : in the yaml ?

  cout << "print result " << string_yield_efficiency << endl;
  
  string string_file_result="results/";
  string_file_result+=string_non_resonant_resonant;
  string_file_result+="/";
  string_file_result+=string_model;
  string_file_result+="/";
  string_file_result+=string_yield_efficiency;
  string_file_result+="_analysis_";
  string_file_result+=string_non_resonant_resonant;
  string_file_result+=".tex";
  
  FILE *fp=fopen(string_file_result.c_str(),"wt");
  
  fprintf(fp,"\\begin{sidewaystable}[h!]\n");
  /*
    if (string_non_resonant_resonant=="non_resonant")
    fprintf(fp,"\\begin{sidewaystable}[h!]\n");
    else
    fprintf(fp,"\\begin{table}[h!]\n");
  */
  
  //  if (string_yield_efficiency=="efficiency")
  fprintf(fp,"\\tiny\n");
  //  fprintf(fp,"\\small\n");
  
  fprintf(fp,"\\scalebox{0.80}\n");
  fprintf(fp,"{\n");
  
  
  fprintf(fp,"\\begin{tabular}{");
  fprintf(fp,"|l|"); //Reco category
  
  int n_processes=vec_string_process.size();

  for (int index_process=0;index_process<n_processes;index_process++)
    fprintf(fp,"l|");
  
  fprintf(fp,"}\n");
  
  fprintf(fp,"\\hline\n");
  //-----
  
  fprintf(fp,"Category \t\t\t\t\t\t &");
  
  for (int index_process=0;index_process<n_processes;index_process++) {
    string string_process=vec_string_process[index_process];
    boost::replace_all(string_process,"_","\\_");
    
    fprintf(fp,"%s",string_process.c_str());
    if (index_process+1<n_processes)
      fprintf(fp,"\t &");
  }
  
  fprintf(fp,"\\\\\n");
  fprintf(fp,"\\hline\n");

  for (unsigned int index_categ=0;index_categ<vec_string_category.size();index_categ++) { //category first, since it corresponds to line of various processes in the print-out
    
    string string_category=vec_string_category[index_categ];
    
    cout << "index_categ=" << index_categ << endl;
    
    string string_category_replaced_underscore=string_category;
    boost::replace_all(string_category_replaced_underscore,"_","\\_");

    fprintf(fp,"%s \t &",string_category_replaced_underscore.c_str());
    
    for (int index_process=0;index_process<n_processes;index_process++) {
      string string_process=vec_string_process[index_process];
      
      string string_resonant_corresponding_category=string_category;

      if (string_category=="Resonant" && string_process.find("_X")!=string::npos)
	string_resonant_corresponding_category=ReturnResonantCorrespondingCategory(string_process);
    
      cout << "at this stage, string_category=" << string_category << endl;
      
      double quantity=map_map_yield_f_category_f_process[string_resonant_corresponding_category][string_process].value;
      double err_quantity=map_map_yield_f_category_f_process[string_resonant_corresponding_category][string_process].err_value;
      
      if (string_yield_efficiency=="efficiency") {
	quantity/=(lumi*1e15*GetCrossSectionTimesBR(string_process));
	err_quantity/=(lumi*1e15*GetCrossSectionTimesBR(string_process));
      }
    
      cout << "in table, string_category=" << string_category << ", string_resonant_corresponding_category=" << string_resonant_corresponding_category << ", string_process=" << string_process << endl;

      if (string_category=="Resonant" || IsCategoryCompatibleToProcess(string_category,string_process)) {
	//need 4 digits for resonant analysis

	if (string_yield_efficiency=="yield") {
	  if (string_non_resonant_resonant=="non_resonant")
	    fprintf(fp,"$%4.4f \\pm %4.4f$",quantity,err_quantity);
	  else if (string_non_resonant_resonant=="resonant")
	    fprintf(fp,"$%4.3f \\pm %4.3f$",quantity,err_quantity);
	}
	else if (string_yield_efficiency=="efficiency") {
	  if (string_non_resonant_resonant=="non_resonant")
	    fprintf(fp,"$%6.6f \\pm %6.6f$",quantity,err_quantity); //needed for Single higgs in HH resonant analysis
	  else if (string_non_resonant_resonant=="resonant")
	    fprintf(fp,"$%6.4f \\pm %6.4f$",quantity,err_quantity); //needed for Single higgs in HH resonant analysis
	}
      }
      else {

	cout << "this is not compatible" << endl;

	fprintf(fp,"N.A.");
      }
      
      if (index_process+1<n_processes)
	fprintf(fp,"\t &");
      
    } //end loop processes
    
    fprintf(fp,"\\\\\n");
    fprintf(fp,"\\hline\n");
  } //end loop on category

  fprintf(fp,"\\end{tabular}\n");
  fprintf(fp,"}\n");

  string string_non_resonant_resonant_caption=string_non_resonant_resonant;

  if (string_non_resonant_resonant=="non_resonant")
    boost::replace_all(string_non_resonant_resonant_caption,"_","\\_");

  fprintf(fp,"%s",(string("\\caption{Results for ")+string_yield_efficiency+" "+string_non_resonant_resonant_caption+"}\n").c_str());
  
  fprintf(fp,"%s",(string("\\label{")+string_non_resonant_resonant+"_"+string_yield_efficiency+string("}\n")).c_str());

  fprintf(fp,"\\end{sidewaystable}\n");
  /*
  if (string_non_resonant_resonant=="non_resonant")
    fprintf(fp,"\\end{sidewaystable}\n");
  else
    fprintf(fp,"\\end{table}\n");
  */

  fclose(fp);
}

bool IsCategoryCompatibleToProcess(string string_category,string string_process)
{
  bool isCompatible=1;
  
  if (string_process=="gg_X251" && string_category!="Resonant_mX251")
    isCompatible=0;
  else if (string_process=="gg_X260" && string_category!="Resonant_mX260")
    isCompatible=0;
  else if (string_process=="gg_X280" && string_category!="Resonant_mX280")
    isCompatible=0;
  else if (string_process=="gg_X300" && string_category!="Resonant_mX300")
    isCompatible=0;
  else if (string_process=="gg_X325" && string_category!="Resonant_mX325")
    isCompatible=0;
  else if (string_process=="gg_X350" && string_category!="Resonant_mX350")
    isCompatible=0;
  else if (string_process=="gg_X400" && string_category!="Resonant_mX400")
    isCompatible=0;
  else if (string_process=="gg_X450" && string_category!="Resonant_mX450")
    isCompatible=0;
  else if (string_process=="gg_X500" && string_category!="Resonant_mX500")
    isCompatible=0;
  else if (string_process=="gg_X550" && string_category!="Resonant_mX550")
    isCompatible=0;
  else if (string_process=="gg_X600" && string_category!="Resonant_mX600")
    isCompatible=0;
  else if (string_process=="gg_X700" && string_category!="Resonant_mX700")
    isCompatible=0;
  else if (string_process=="gg_X800" && string_category!="Resonant_mX800")
    isCompatible=0;
  else if (string_process=="gg_X900" && string_category!="Resonant_mX900")
    isCompatible=0;
  else if (string_process=="gg_X1000" && string_category!="Resonant_mX1000")
    isCompatible=0;
  else if (string_process=="gg_X2000" && string_category!="Resonant_mX2000")
    isCompatible=0;
  else if (string_process=="gg_X3000" && string_category!="Resonant_mX3000")
    isCompatible=0;
  
  return isCompatible;
}


string ReturnResonantCorrespondingCategory(string string_process)
{
  string string_resonant_corresponding_category="";
  
  if (string_process=="gg_X251")
    string_resonant_corresponding_category="Resonant_mX251";


  else if (string_process=="gg_X270")
    string_resonant_corresponding_category="Resonant_mX270";
  else if (string_process=="gg_X290")
    string_resonant_corresponding_category="Resonant_mX290";
  else if (string_process=="gg_X312.5")
    string_resonant_corresponding_category="Resonant_mX312.5";
  else if (string_process=="gg_X337.5")
    string_resonant_corresponding_category="Resonant_mX337.5";
  else if (string_process=="gg_X375")
    string_resonant_corresponding_category="Resonant_mX375";
  else if (string_process=="gg_X425")
    string_resonant_corresponding_category="Resonant_mX425";
  else if (string_process=="gg_X475")
    string_resonant_corresponding_category="Resonant_mX475";
  
  else if (string_process=="gg_X260")
    string_resonant_corresponding_category="Resonant_mX260";
  else if (string_process=="gg_X280")
    string_resonant_corresponding_category="Resonant_mX280";
  else if (string_process=="gg_X300")
    string_resonant_corresponding_category="Resonant_mX300";
  else if (string_process=="gg_X325")
    string_resonant_corresponding_category="Resonant_mX325";
  else if (string_process=="gg_X350")
    string_resonant_corresponding_category="Resonant_mX350";
  else if (string_process=="gg_X400")
    string_resonant_corresponding_category="Resonant_mX400";
  else if (string_process=="gg_X450")
    string_resonant_corresponding_category="Resonant_mX450";
  else if (string_process=="gg_X500")
    string_resonant_corresponding_category="Resonant_mX500";
  else if (string_process=="gg_X550")
    string_resonant_corresponding_category="Resonant_mX550";
  else if (string_process=="gg_X600")
    string_resonant_corresponding_category="Resonant_mX600";
  else if (string_process=="gg_X700")
    string_resonant_corresponding_category="Resonant_mX700";
  else if (string_process=="gg_X800")
    string_resonant_corresponding_category="Resonant_mX800";
  else if (string_process=="gg_X900")
    string_resonant_corresponding_category="Resonant_mX900";
  else if (string_process=="gg_X1000")
    string_resonant_corresponding_category="Resonant_mX1000";
  else if (string_process=="gg_X2000")
    string_resonant_corresponding_category="Resonant_mX2000";
  else if (string_process=="gg_X3000")
    string_resonant_corresponding_category="Resonant_mX3000";

  else if (string_process=="gg_X280_Py8")
    string_resonant_corresponding_category="Resonant_mX280";
  else if (string_process=="gg_X500_Py8")
    string_resonant_corresponding_category="Resonant_mX500";
  else if (string_process=="gg_X1000_Py8")
    string_resonant_corresponding_category="Resonant_mX1000";
  
  return string_resonant_corresponding_category;
}

//to rename with suffix_ process
double ReturnCharacteristic(string string_process)
{
  double characteristic=0;
  
  if (string_process=="gg_X251")
    characteristic=251;
  else if (string_process=="gg_X260")
    characteristic=260;
  else if (string_process=="gg_X280")
    characteristic=280;
  else if (string_process=="gg_X300")
    characteristic=300;
  else if (string_process=="gg_X325")
    characteristic=325;
  else if (string_process=="gg_X350")
    characteristic=350;
  else if (string_process=="gg_X400")
    characteristic=400;
  else if (string_process=="gg_X450")
    characteristic=450;
  else if (string_process=="gg_X500")
    characteristic=500;
  else if (string_process=="gg_X550")
    characteristic=550;
  else if (string_process=="gg_X600")
    characteristic=600;
  else if (string_process=="gg_X700")
    characteristic=700;
  else if (string_process=="gg_X800")
    characteristic=800;
  else if (string_process=="gg_X900")
    characteristic=900;
  else if (string_process=="gg_X1000")
    characteristic=1000;
  else if (string_process=="gg_X2000")
    characteristic=2000;
  else if (string_process=="gg_X3000")
    characteristic=3000;

  //  else if (string_process=="gg_HH_NLO")
  else if (string_process=="gg_HH")
    characteristic=1;
  else if (string_process.find("reweight_mHH_1p0_to_")!=string::npos) {

    string string_expression="reweight_mHH_1p0_to_";
    size_t position_string=string_process.find(string_expression);
    position_string+=string_expression.size();

    string string_target_kappa=string_process.substr(position_string);
    
    //    cout << "string_target_kappa=" << string_target_kappa << endl;
    
    float numerical_target_kappa=Return_numerical_target_kappa(string_target_kappa);

    //    cout << "numerical_target_kappa=" << numerical_target_kappa << endl;
    characteristic=numerical_target_kappa;
  }
  
  return characteristic;
}

double ReturnCharacteristic_category(string string_category)
{
  //  cout << "in ReturnCharacteristic_category phase 1" << endl;
  double characteristic=0;
  
  if (string_category=="Resonant_mX251")
    characteristic=251;
  else if (string_category=="Resonant_mX260")
    characteristic=260;
  else if (string_category=="Resonant_mX270")
    characteristic=270;
  else if (string_category=="Resonant_mX280")
    characteristic=280;
  else if (string_category=="Resonant_mX290")
    characteristic=290;
  else if (string_category=="Resonant_mX300")
    characteristic=300;
  else if (string_category=="Resonant_mX312.5")
    characteristic=312.5;
  else if (string_category=="Resonant_mX325")
    characteristic=325;
  else if (string_category=="Resonant_mX337.5")
    characteristic=337.5;
  else if (string_category=="Resonant_mX350")
    characteristic=350;
  else if (string_category=="Resonant_mX375")
    characteristic=375;
  else if (string_category=="Resonant_mX400")
    characteristic=400;
  else if (string_category=="Resonant_mX425")
    characteristic=425;
  else if (string_category=="Resonant_mX450")
    characteristic=450;
  else if (string_category=="Resonant_mX475")
    characteristic=475;
  else if (string_category=="Resonant_mX500")
    characteristic=500;
  else if (string_category=="Resonant_mX550")
    characteristic=550;
  else if (string_category=="Resonant_mX600")
    characteristic=600;
  else if (string_category=="Resonant_mX700")
    characteristic=700;
  else if (string_category=="Resonant_mX800")
    characteristic=800;
  else if (string_category=="Resonant_mX900")
    characteristic=900;
  else if (string_category=="Resonant_mX1000")
    characteristic=1000;
  else if (string_category=="Resonant_mX2000")
    characteristic=2000;
  else if (string_category=="Resonant_mX3000")
    characteristic=3000;
  
  return characteristic;
}
//=====================================================================================================================================================
float Return_numerical_target_kappa(string string_target_kappa)
{
  float sign=1;
  
  int index_first_position=0;
  
  if (string_target_kappa[0]=='n') {
    sign=-1;
    index_first_position=1;
  }
  
  int position_point=0;
  
  unsigned int index_character=0;
  
  for (;index_character<string_target_kappa.size() && string_target_kappa[index_character]!='p';index_character++)
    ;
  
  if (index_character>=string_target_kappa.size()) {
    cout << "not found the point, halt program" << endl;
    exit(1);
  }
  
  int index_point=index_character;
  
  //  cout << "index_point=" << index_point << endl;
  
  int coefficient_power=index_point-index_first_position-1;
  
  //  cout << "index_first_position=" << index_first_position << ", index_point=" << index_point << endl;
  //  cout << "coefficient_power=" << coefficient_power << endl;
  
  float numerical_target_kappa=0;
  
  for (index_character=index_first_position;index_character<string_target_kappa.size();index_character++) {

    char character[1];
    character[0]=string_target_kappa[index_character];
    //    cout << "in loop, coefficient_power=" << coefficient_power << endl;
    //    cout << "before treatment, numerical_target_kappa=" << numerical_target_kappa << endl;
    
    numerical_target_kappa+=atoi(character)*pow(10,coefficient_power);
    //    cout << "after treatment of character index " << index_first_position << ", which is " << string_target_kappa[index_character] << ", numerical_target_kappa=" << numerical_target_kappa << endl;
    
    if (string_target_kappa[index_character]!='p')
      coefficient_power--;
  }
  
  numerical_target_kappa*=sign;

  return numerical_target_kappa;
}

//###################################################################################################
//used for inputs : this was correct
//###################################################################################################
float ReturnCrossSectionTimesBR(float kappa_lambda)
{
//this gives cross-section for 125 GeV
  float cross_section;
  
  //formula at mh=125 GeV
  cross_section=70.3874-50.4111*kappa_lambda+11.0595*pow(kappa_lambda,2); //in fb

  /*shit
  //MARC NEW
  if (kappa_lambda==1) //for kappa_lambda=1, the framework uses mH=125.0 GeV
    ;
  else
  */

  //we now (thanks to GetYield_given_process) moved everything to 125.09 GeV

  cross_section*=31.05/31.0358;

  //31.05 : 125 GeV
  //31.02 : 125.09 GeV

  /*shit
  //31.02=125.0 GeV
  //31.05=125.09 GeV
  */

  //correction to 125.09 GeV

  cross_section*=31.02/31.05;
  
  //31.05 not used : normal : the inputs in the samples are with 125 GeV
  
  cross_section*=2*0.5809*0.00227;

  return cross_section;
}
//###################################################################################################

/*
No, because in the samples, the cross sections values are those of 125 GeV

//###################################################################################################
float ReturnCrossSectionTimesBR(float kappa_lambda)
{
  //here, since the HH samples are made with mH=125 GeV, this is correct to keep 125 GeV

  float cross_section;
  
  //formula at mh=125 GeV
  cross_section=70.3874-50.4111*kappa_lambda+11.0595*pow(kappa_lambda,2); //in fb

  //31.02=125.0 GeV

  //correction for the formula
  cross_section*=31.02/31.0358;

  //31.05=125.09 GeV

  //moving to 125.09 GeV
  cross_section*=31.05/31.02;

  cross_section*=2*0.5809*0.00227;

  return cross_section;
}
*/
