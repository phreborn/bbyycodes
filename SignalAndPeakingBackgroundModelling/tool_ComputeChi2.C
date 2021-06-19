//===========================================================================================================
//to do : make a class for information of chi2

//to do : class chi2_info
//with err_chi2 in particular !

//need flexibility of the error (MC-like error or data-like error), and need 2D as well as blinding, so new code

//code with only mc like and data like error

//to do : why should we use the integral of the full range, and not the integral of the restricted pdf ?

//asked on forum atlas-phys-stat-root@cern.ch, 07/04/2020
//about normalisation integral_data

void ComputeChi2_ndf(double &chi2,int &ndfs,int &nbins,int &nparams,RooDataSet *dataset,RooAbsPdf *pdf)
{
  bool DEBUG=0;

  cout << "start ComputeChi2_ndf" << endl;

  vector<RooRealVar *> vec_roorealvar_finalDV;
 
  for (unsigned int index_finalDV=0;index_finalDV<argset_finalDV_noWeight.size();index_finalDV++) {
    vec_roorealvar_finalDV.push_back( (RooRealVar *) RooArgList(argset_finalDV_noWeight).at(index_finalDV) );
  }

  chi2=0;
  //TO DO : to addoutside
  double err_chi2=0;

  nbins=0;

  //to use rooargset

  //solution: to use TH1 * (and recast everything...)

  TH1 *representative_hist_dataset_for_chi2=0;
  TH1 *representative_hist_unweighted_dataset_for_chi2=0; //for number of entries

 //  TH1 *representative_hist_pdf_for_chi2=0; //for debugging
    
  cout << "vec_roorealvar_finalDV[0]->getMin()=" << vec_roorealvar_finalDV[0]->getMin() << endl;
  cout << "vec_roorealvar_finalDV[0]->getMax()=" << vec_roorealvar_finalDV[0]->getMax() << endl;
  cout << "vec_roorealvar_finalDV[0]->numBins()=" << vec_roorealvar_finalDV[0]->numBins() << endl;
  cout << "vec_roorealvar_finalDV[0]->getBinWidth(1)=" << vec_roorealvar_finalDV[0]->getBinWidth(1) << endl;

  if (vec_roorealvar_finalDV.size()==1) {
    representative_hist_dataset_for_chi2=new TH1D("representative_hist_dataset_for_chi2","representative_hist_dataset_for_chi2",vec_roorealvar_finalDV[0]->numBins(),vec_roorealvar_finalDV[0]->getMin(),vec_roorealvar_finalDV[0]->getMax());
    representative_hist_unweighted_dataset_for_chi2=new TH1D("representative_hist_unweighted_dataset_for_chi2","representative_hist_unweighted_dataset_for_chi2",vec_roorealvar_finalDV[0]->numBins(),vec_roorealvar_finalDV[0]->getMin(),vec_roorealvar_finalDV[0]->getMax());
  }
  else if (vec_roorealvar_finalDV.size()==2) {
    representative_hist_dataset_for_chi2=(TH2D *)new TH2D("representative_hist2D_dataset_for_chi2","representative_hist2D_dataset_for_chi2",vec_roorealvar_finalDV[0]->numBins(),vec_roorealvar_finalDV[0]->getMin(),vec_roorealvar_finalDV[0]->getMax(),vec_roorealvar_finalDV[1]->numBins(),vec_roorealvar_finalDV[1]->getMin(),vec_roorealvar_finalDV[1]->getMax());
    representative_hist_unweighted_dataset_for_chi2=(TH2D *)new TH2D("representative_hist2D_unweighted_dataset_for_chi2","representative_hist2D_unweighted_dataset_for_chi2",vec_roorealvar_finalDV[0]->numBins(),vec_roorealvar_finalDV[0]->getMin(),vec_roorealvar_finalDV[0]->getMax(),vec_roorealvar_finalDV[1]->numBins(),vec_roorealvar_finalDV[1]->getMin(),vec_roorealvar_finalDV[1]->getMax());

    //for debugging
    //representative_hist_pdf_for_chi2=(TH2D *)new TH2D("representative_hist2D_pdf_for_chi2","representative_hist2D_pdf_for_chi2",vec_roorealvar_finalDV[0]->numBins(),vec_roorealvar_finalDV[0]->getMin(),vec_roorealvar_finalDV[0]->getMax(),vec_roorealvar_finalDV[1]->numBins(),vec_roorealvar_finalDV[1]->getMin(),vec_roorealvar_finalDV[1]->getMax());
  }
  
  int nb_entries_dataset=dataset->numEntries();
  
  //need to use the *discretization* of the value corresponding range, else there would be a major bias for the first and last bin of the fit range, since pdf could not be interpreted by the fact that the first and last bin would be partially filled
  
  vector<double> vec_discretized_fitrange_min;
  vector<double> vec_discretized_fitrange_max;
  
  argset_finalDV_noWeight.Print();

  //prepare the region of blinding
  
  for (unsigned int index_finalDV=0;index_finalDV<argset_finalDV_noWeight.size();index_finalDV++) {
    cout << "index_finalDV=" << index_finalDV << endl;
    
    if (IsFinalDV_in_list(vec_string_finalDV[index_finalDV].c_str())) {
      double discretized_fitrange_min;
      double discretized_fitrange_max;
      
      TAxis *axis=0;
      
      if (index_finalDV==0) { //x axis
	axis=representative_hist_dataset_for_chi2->GetXaxis();
      }
      else if (index_finalDV==1) { //y axis
	axis=representative_hist_dataset_for_chi2->GetYaxis();
      }
	
      cout << "index_finalDV=" << index_finalDV << endl;
      cout << "fitrange min=" << vec_roorealvar_finalDV[index_finalDV]->getMin("fitrange") << endl;
      cout << "fitrange max=" << vec_roorealvar_finalDV[index_finalDV]->getMax("fitrange") << endl;

      int index_bin_min=axis->FindBin(vec_roorealvar_finalDV[index_finalDV]->getMin("fitrange"));
      cout << "discretized value min=" << axis->GetBinLowEdge(index_bin_min) << endl;
      
      vec_discretized_fitrange_min.push_back(axis->GetBinLowEdge(index_bin_min));

      //MARC      
      //      int index_bin_max=-1+axis->FindBin(vec_roorealvar_finalDV[index_finalDV]->getMax("fitrange"));

      //it will contain the high range
      int index_bin_max=axis->FindBin(vec_roorealvar_finalDV[index_finalDV]->getMax("fitrange"));
      cout << "discretized value max=" << axis->GetBinUpEdge(index_bin_max) << endl;
      vec_discretized_fitrange_max.push_back(axis->GetBinUpEdge(index_bin_max));
    }
  } //end loop on finalDV
  
  for (unsigned int index_finalDV=0;index_finalDV<argset_finalDV_noWeight.size();index_finalDV++) {
    cout << "index_finalDV=" << index_finalDV << ", range=" << vec_discretized_fitrange_min[index_finalDV] << " ; " << vec_discretized_fitrange_max[index_finalDV] << endl;
  }

  cout << "argset_finalDV_noWeight.size()=" << argset_finalDV_noWeight.size() << endl;

  //for sure, after detailed investigation, one needs really the integral, wo/ restriction to fitted region part
  //asked to Stephan Hageboeck on 11/April/2020, 13:10
  double integral_dataset=dataset->sumEntries();

  //remark: if we would use pdf->setNormRange("thefitrange"), then we would use the integral in the restricted range)
  
  //MARC
  //double integral_dataset=dataset->sumEntries("m_yy>117 && m_yy<131 && m_bb>45 && m_bb<165");

  //double integral_dataset=dataset->sumEntries("m_yy>121 && m_yy<128 && m_bb>60 && m_bb<145");

  //  double integral_dataset=dataset->sumEntries("m_yy>121 && m_yy<128");

  cout << "integral_dataset=" << integral_dataset << endl;

  //cout << "integral_dataset in 117-131 ; 45-165=" << dataset->sumEntries("m_yy>117 && m_yy<131 && m_bb>45 && m_bb<165") << endl;
  //  cout << "integral in 119, 130=" << dataset->sumEntries("m_yy>119 && m_yy<130") << endl;
  //  exit(1);

  /*
  //==============================================================================
  //debugging information, for plot per slice
  //do not remove

  if (vec_roorealvar_finalDV.size()==2) {
    cout << "vec_roorealvar_finalDV[0]->numBins()=" << vec_roorealvar_finalDV[0]->numBins() << endl;
    cout << "vec_roorealvar_finalDV[0]->getMin()=" << vec_roorealvar_finalDV[0]->getMin() << endl;
    cout << "vec_roorealvar_finalDV[0]->getMax()=" << vec_roorealvar_finalDV[0]->getMax() << endl;
    
    cout << "vec_roorealvar_finalDV[1]->numBins()=" << vec_roorealvar_finalDV[1]->numBins() << endl;
    cout << "vec_roorealvar_finalDV[1]->getMin()=" << vec_roorealvar_finalDV[1]->getMin() << endl;
    cout << "vec_roorealvar_finalDV[1]->getMax()=" << vec_roorealvar_finalDV[1]->getMax() << endl;
    
    TH1F **hist_dataset_first_finalDV_f_slice_second=new TH1F *[vec_roorealvar_finalDV[1]->numBins()];
    TH1F **hist_unweighted_dataset_first_finalDV_f_slice_second=new TH1F *[vec_roorealvar_finalDV[1]->numBins()];
    TH1F **hist_pdf_first_finalDV_f_slice_second=new TH1F *[vec_roorealvar_finalDV[1]->numBins()];

    for (int index_second=0;index_second<vec_roorealvar_finalDV[1]->numBins();index_second++) {

      //correct
      float value_low_threshold_second=vec_roorealvar_finalDV[1]->getMin()+index_second*vec_roorealvar_finalDV[1]->getBinWidth(index_second);
      float value_high_threshold_second=vec_roorealvar_finalDV[1]->getMin()+(index_second+1)*vec_roorealvar_finalDV[1]->getBinWidth(index_second);

      double integral_dataset_slice=dataset->sumEntries(
							(
							 //current bin of second variable
							 string(vec_roorealvar_finalDV[1]->GetName())+">="+to_string(value_low_threshold_second) +" && "+ string(vec_roorealvar_finalDV[1]->GetName())+"<"+to_string(value_high_threshold_second)
							 //additional fitranges
							 +" && " + string(vec_roorealvar_finalDV[1]->GetName())+">="+to_string(vec_discretized_fitrange_min[1])
							 +" && " + string(vec_roorealvar_finalDV[1]->GetName())+"<"+to_string(vec_discretized_fitrange_max[1])
							 ).c_str()
							);
      
      cout << "command integral_first=" << 							(
												 //current bin of second variable
												 string(vec_roorealvar_finalDV[1]->GetName())+">="+to_string(value_low_threshold_second) +" && "+ string(vec_roorealvar_finalDV[1]->GetName())+"<"+to_string(value_high_threshold_second)
												 //additional fitranges
												 +" && " + string(vec_roorealvar_finalDV[1]->GetName())+">="+to_string(vec_discretized_fitrange_min[1])
												 +" && " + string(vec_roorealvar_finalDV[1]->GetName())+"<"+to_string(vec_discretized_fitrange_max[1])
												 ).c_str() << endl;

      float value_second=vec_roorealvar_finalDV[1]->getMin()+(0.5+index_second)*vec_roorealvar_finalDV[1]->getBinWidth(index_second);
      
      //       cout << "consider index_second=" << index_second << ", for mbb in range " << value_low_threshold_second << " ; " << value_high_threshold_second << endl;
      //       cout << "value_second=" << value_second << endl;
      
      //       cout << "integral_dataset=" << integral_dataset << endl;
      //       cout << "reduce=" << string(vec_roorealvar_finalDV[1]->GetName())+">="+to_string(value_low_threshold_second) +" && "+ string(vec_roorealvar_finalDV[1]->GetName())+"<"+to_string(value_high_threshold_second) << endl;
      //       cout << "integral_dataset_slice=" << integral_dataset_slice << endl;


      hist_dataset_first_finalDV_f_slice_second[index_second]=new TH1F((string("hist_dataset_first_variable_for_second_variable_bin_equals_")+to_string(value_second)).c_str(),
								       (string("hist_dataset_first_variable_for_second_variable_bin_equals_")+to_string(value_second)).c_str(),
								       vec_roorealvar_finalDV[0]->numBins(),
								       vec_roorealvar_finalDV[0]->getMin(),
								       vec_roorealvar_finalDV[0]->getMax()
								       );
      hist_dataset_first_finalDV_f_slice_second[index_second]->SetMarkerStyle(20);
      hist_dataset_first_finalDV_f_slice_second[index_second]->SetMarkerSize(0.5);
      hist_dataset_first_finalDV_f_slice_second[index_second]->SetMarkerColor(kBlack);
      hist_dataset_first_finalDV_f_slice_second[index_second]->SetLineColor(kBlack);

      hist_unweighted_dataset_first_finalDV_f_slice_second[index_second]=new TH1F((string("hist_unweighted_dataset_first_variable_for_second_variable_bin_equals_")+to_string(value_second)).c_str(),
										  (string("hist_unweighted_dataset_first_variable_for_second_variable_bin_equals_")+to_string(value_second)).c_str(),
										  vec_roorealvar_finalDV[0]->numBins(),
										  vec_roorealvar_finalDV[0]->getMin(),
										  vec_roorealvar_finalDV[0]->getMax()
										  );
      hist_unweighted_dataset_first_finalDV_f_slice_second[index_second]->SetMarkerStyle(20);
      hist_unweighted_dataset_first_finalDV_f_slice_second[index_second]->SetMarkerColor(kBlack);
      hist_unweighted_dataset_first_finalDV_f_slice_second[index_second]->SetLineColor(kBlack);

      hist_pdf_first_finalDV_f_slice_second[index_second]=new TH1F((string("hist_pdf_first_variable_for_second_variable_bin_equals_")+to_string(value_second)).c_str(),
								   (string("hist_pdf_first_variable_for_second_variable_bin_equals_")+to_string(value_second)).c_str(),
								   vec_roorealvar_finalDV[0]->numBins(),
								   vec_roorealvar_finalDV[0]->getMin(),
								   vec_roorealvar_finalDV[0]->getMax()
								   );
      hist_pdf_first_finalDV_f_slice_second[index_second]->SetMarkerStyle(20);
      hist_pdf_first_finalDV_f_slice_second[index_second]->SetMarkerColor(kBlue);
      hist_pdf_first_finalDV_f_slice_second[index_second]->SetLineColor(kBlue+2);
      
      for (int index_entry=0;index_entry<nb_entries_dataset;index_entry++) {
	
	RooArgSet *argset=(RooArgSet *)dataset->get(index_entry);
	
	bool keep_event=1;
	
	//------
	//skip events based on current bin of second variable

	double value_second_finalDV=argset->getRealValue(vec_roorealvar_finalDV[1]->GetName());

	if (!
	    (
	     value_second_finalDV>=value_low_threshold_second
	     &&
	     value_second_finalDV<value_high_threshold_second
	     )
	    ) {
	  //	  cout << "does not pass due to current bin of second value=" << value_second_finalDV << ", while range=" << value_low_threshold_second << ", " << value_high_threshold_second << endl;
	  
	  keep_event=0;
	  continue; //skip event
	}
	//------
	//skip events based on current fit range of second variable (so it could cut a subpart inside the bin

	double value_finalDV=argset->getRealValue(vec_roorealvar_finalDV[1]->GetName());
	
	if (
	    (value_finalDV<vec_discretized_fitrange_min[1] || value_finalDV>vec_discretized_fitrange_max[1])
	    ) {
	  keep_event=0;
	  
	  continue;
	}
	//------
	//	cout << "conclusion, keep_event=" << keep_event << endl;

	if (!keep_event)
	  continue;
	
	if (vec_roorealvar_finalDV.size()==2) {
	  hist_dataset_first_finalDV_f_slice_second[index_second]->Fill(argset->getRealValue(vec_roorealvar_finalDV[0]->GetName()),dataset->weight());
	  hist_unweighted_dataset_first_finalDV_f_slice_second[index_second]->Fill(argset->getRealValue(vec_roorealvar_finalDV[0]->GetName()));
	  
	  pdf->fillHistogram(hist_pdf_first_finalDV_f_slice_second[index_second],RooArgList(*vec_roorealvar_finalDV[0]),integral_dataset_slice);
	}
	
      } //end loop on entries
      
      //      cout << "hist_dataset_first_finalDV_f_slice_second[index_second]->Integral()=" << hist_dataset_first_finalDV_f_slice_second[index_second]->Integral() << endl;
      
      TCanvas *canvas_debugging=new TCanvas("canvas_debugging","canvas_debugging",800,600);
      hist_dataset_first_finalDV_f_slice_second[index_second]->SetMaximum(0.00011);
      hist_dataset_first_finalDV_f_slice_second[index_second]->SetMinimum(0.);
      hist_dataset_first_finalDV_f_slice_second[index_second]->Draw("PL");
      hist_pdf_first_finalDV_f_slice_second[index_second]->Draw("histPsame");
      canvas_debugging->SaveAs((string("figures/hist_debugging_first_variable_for_second_variable_bin_equals_")+to_string(value_second)+".png").c_str());
      
      TCanvas *canvas_debugging_entries=new TCanvas("canvas_debugging_entries","canvas_debugging_entries",800,600);
      TH1F *hist_dummy=canvas_debugging_entries->DrawFrame(vec_roorealvar_finalDV[0]->getMin(),0,vec_roorealvar_finalDV[0]->getMax(),50);
      hist_unweighted_dataset_first_finalDV_f_slice_second[index_second]->Draw("histPsame");
      canvas_debugging_entries->SaveAs((string("figures/hist_entries_first_variable_for_second_variable_bin_equals_")+to_string(value_second)+".png").c_str());
      
      delete canvas_debugging;
      delete canvas_debugging_entries;
    }
    
    //============================
    TH1F **hist_dataset_second_finalDV_f_slice_first=new TH1F *[vec_roorealvar_finalDV[0]->numBins()];
    TH1F **hist_unweighted_dataset_second_finalDV_f_slice_first=new TH1F *[vec_roorealvar_finalDV[0]->numBins()];
    TH1F **hist_pdf_second_finalDV_f_slice_first=new TH1F *[vec_roorealvar_finalDV[0]->numBins()];
    
    for (int index_first=0;index_first<vec_roorealvar_finalDV[0]->numBins();index_first++) {
      
      //correct
      float value_low_threshold_first=vec_roorealvar_finalDV[0]->getMin()+index_first*vec_roorealvar_finalDV[0]->getBinWidth(index_first);
      float value_high_threshold_first=vec_roorealvar_finalDV[0]->getMin()+(index_first+1)*vec_roorealvar_finalDV[0]->getBinWidth(index_first);

      double integral_dataset_slice=dataset->sumEntries(
							(
							 //current bin of first variable
							 string(vec_roorealvar_finalDV[0]->GetName())+">="+to_string(value_low_threshold_first) +" && "+ string(vec_roorealvar_finalDV[0]->GetName())+"<"+to_string(value_high_threshold_first)
							 //additional fitranges
							 +" && " + string(vec_roorealvar_finalDV[0]->GetName())+">="+to_string(vec_discretized_fitrange_min[0])
							 +" && " + string(vec_roorealvar_finalDV[0]->GetName())+"<"+to_string(vec_discretized_fitrange_max[0])
							 ).c_str()
							);


      cout << "command for second integral=" << 							(
												 //current bin of first variable
												 string(vec_roorealvar_finalDV[0]->GetName())+">="+to_string(value_low_threshold_first) +" && "+ string(vec_roorealvar_finalDV[0]->GetName())+"<"+to_string(value_high_threshold_first)
												 //additional fitranges
												 +" && " + string(vec_roorealvar_finalDV[0]->GetName())+">="+to_string(vec_discretized_fitrange_min[0])
												 +" && " + string(vec_roorealvar_finalDV[0]->GetName())+"<"+to_string(vec_discretized_fitrange_max[0])
												 ).c_str()	   << endl;

      
      float value_first=vec_roorealvar_finalDV[0]->getMin()+(0.5+index_first)*vec_roorealvar_finalDV[0]->getBinWidth(index_first);
      
      //       cout << "consider index_first=" << index_first << ", for mbb in range " << value_low_threshold_first << " ; " << value_high_threshold_first << endl;
      //       cout << "value_first=" << value_first << endl;
      
      //       cout << "integral_dataset=" << integral_dataset << endl;
      //       cout << "reduce=" << string(vec_roorealvar_finalDV[1]->GetName())+">="+to_string(value_low_threshold_first) +" && "+ string(vec_roorealvar_finalDV[1]->GetName())+"<"+to_string(value_high_threshold_first) << endl;
      //       cout << "integral_dataset_slice=" << integral_dataset_slice << endl;


      hist_dataset_second_finalDV_f_slice_first[index_first]=new TH1F((string("hist_dataset_second_variable_for_first_variable_bin_equals_")+to_string(value_first)).c_str(),
								       (string("hist_dataset_second_variable_for_first_variable_bin_equals_")+to_string(value_first)).c_str(),
								      vec_roorealvar_finalDV[1]->numBins(),
								      vec_roorealvar_finalDV[1]->getMin(),
								      vec_roorealvar_finalDV[1]->getMax()
								       );

      cout << "vec_roorealvar_finalDV[1]->numBins()=" << vec_roorealvar_finalDV[1]->numBins() << "vec_roorealvar_finalDV[1]->getMin()=" << vec_roorealvar_finalDV[1]->getMin() << ", vec_roorealvar_finalDV[1]->getMax()=" << vec_roorealvar_finalDV[1]->getMax() << endl;
      hist_dataset_second_finalDV_f_slice_first[index_first]->SetMarkerStyle(20);
      hist_dataset_second_finalDV_f_slice_first[index_first]->SetMarkerSize(0.5);
      hist_dataset_second_finalDV_f_slice_first[index_first]->SetMarkerColor(kBlack);
      hist_dataset_second_finalDV_f_slice_first[index_first]->SetLineColor(kBlack);

      hist_unweighted_dataset_second_finalDV_f_slice_first[index_first]=new TH1F((string("hist_unweighted_dataset_second_variable_for_first_variable_bin_equals_")+to_string(value_first)).c_str(),
										  (string("hist_unweighted_dataset_second_variable_for_first_variable_bin_equals_")+to_string(value_first)).c_str(),
										  vec_roorealvar_finalDV[1]->numBins(),
										  vec_roorealvar_finalDV[1]->getMin(),
										  vec_roorealvar_finalDV[1]->getMax()
										  );
      hist_unweighted_dataset_second_finalDV_f_slice_first[index_first]->SetMarkerStyle(20);
      hist_unweighted_dataset_second_finalDV_f_slice_first[index_first]->SetMarkerColor(kBlack);
      hist_unweighted_dataset_second_finalDV_f_slice_first[index_first]->SetLineColor(kBlack);

      hist_pdf_second_finalDV_f_slice_first[index_first]=new TH1F((string("hist_pdf_second_variable_for_first_variable_bin_equals_")+to_string(value_first)).c_str(),
								   (string("hist_pdf_second_variable_for_first_variable_bin_equals_")+to_string(value_first)).c_str(),
								   vec_roorealvar_finalDV[1]->numBins(),
								   vec_roorealvar_finalDV[1]->getMin(),
								   vec_roorealvar_finalDV[1]->getMax()
								   );
      hist_pdf_second_finalDV_f_slice_first[index_first]->SetMarkerStyle(20);
      hist_pdf_second_finalDV_f_slice_first[index_first]->SetMarkerColor(kBlue);
      hist_pdf_second_finalDV_f_slice_first[index_first]->SetLineColor(kBlue+2);
      
      for (int index_entry=0;index_entry<nb_entries_dataset;index_entry++) {
	
	RooArgSet *argset=(RooArgSet *)dataset->get(index_entry);
	
	bool keep_event=1;
	
	//------
	//skip events based on current bin of first variable

	double value_first_finalDV=argset->getRealValue(vec_roorealvar_finalDV[0]->GetName());

	if (!
	    (
	     value_first_finalDV>=value_low_threshold_first
	     &&
	     value_first_finalDV<value_high_threshold_first
	     )
	    ) {
	  //	  cout << "does not pass due to current bin of first value=" << value_first_finalDV << ", while range=" << value_low_threshold_first << ", " << value_high_threshold_first << endl;
	  
	  keep_event=0;
	  continue; //skip event
	}
	//------
	//skip events based on current fit range of first variable (so it could cut a subpart inside the bin

	double value_finalDV=argset->getRealValue(vec_roorealvar_finalDV[0]->GetName());
	
	if (
	    (value_finalDV<vec_discretized_fitrange_min[0] || value_finalDV>vec_discretized_fitrange_max[0])
	    ) {
	  keep_event=0;
	  
	  continue;
	}
	//------
	//	cout << "conclusion, keep_event=" << keep_event << endl;

	if (!keep_event)
	  continue;
	
	if (vec_roorealvar_finalDV.size()==2) {
	  hist_dataset_second_finalDV_f_slice_first[index_first]->Fill(argset->getRealValue(vec_roorealvar_finalDV[1]->GetName()),dataset->weight());
	  hist_unweighted_dataset_second_finalDV_f_slice_first[index_first]->Fill(argset->getRealValue(vec_roorealvar_finalDV[1]->GetName()));
	  
	  pdf->fillHistogram(hist_pdf_second_finalDV_f_slice_first[index_first],RooArgList(*vec_roorealvar_finalDV[1]),integral_dataset_slice);
	}
	
      } //end loop on entries
      
      //      cout << "hist_dataset_second_finalDV_f_slice_first[index_first]->Integral()=" << hist_dataset_second_finalDV_f_slice_first[index_first]->Integral() << endl;
      
      TCanvas *canvas_debugging=new TCanvas("canvas_debugging","canvas_debugging",800,600);
      //      hist_dataset_second_finalDV_f_slice_first[index_first]->SetMaximum(0.0002);
      hist_dataset_second_finalDV_f_slice_first[index_first]->SetMaximum(0.0003);
      hist_dataset_second_finalDV_f_slice_first[index_first]->SetMinimum(0.);
      hist_dataset_second_finalDV_f_slice_first[index_first]->Draw("PL");
      hist_pdf_second_finalDV_f_slice_first[index_first]->Draw("histPsame");
      canvas_debugging->SaveAs((string("figures/hist_debugging_second_variable_for_first_variable_bin_equals_")+to_string(value_first)+".png").c_str());
      
      TCanvas *canvas_debugging_entries=new TCanvas("canvas_debugging_entries","canvas_debugging_entries",800,600);
      TH1F *hist_dummy=canvas_debugging_entries->DrawFrame(vec_roorealvar_finalDV[1]->getMin(),0,vec_roorealvar_finalDV[1]->getMax(),50);
      hist_unweighted_dataset_second_finalDV_f_slice_first[index_first]->Draw("histPsame");
      canvas_debugging_entries->SaveAs((string("figures/hist_entries_second_variable_for_first_variable_bin_equals_")+to_string(value_first)+".png").c_str());
      
      delete canvas_debugging;
      delete canvas_debugging_entries;
    }
  }
  */
  //==============================================================================
  //-----------------------
  //dataset->fillHistogram(representative_hist_data_for_chi2,RooArgList(*roorealvar_observable));
  //dataset->fillHistogram(representative_hist_data_for_chi2,RooArgList(*vec_roorealvar_finalDV[0],*vec_roorealvar_finalDV[1]));
  
  //for debugging
  //  if (vec_roorealvar_finalDV.size()==2)
  //    pdf->fillHistogram(representative_hist_pdf_for_chi2,RooArgList(*vec_roorealvar_finalDV[0],*vec_roorealvar_finalDV[1]),integral_dataset);
  
  //adapted from fillObservable
  
  for (int index_entry=0;index_entry<nb_entries_dataset;index_entry++) {
    
    RooArgSet *argset=(RooArgSet *)dataset->get(index_entry);
    
    bool keep_event=1;
    
    for (unsigned int index_finalDV=0;index_finalDV<argset_finalDV_noWeight.size();index_finalDV++) {
      
      double value_finalDV=argset->getRealValue(vec_roorealvar_finalDV[index_finalDV]->GetName());
      
      //      cout << "value_finalDV=" << value_finalDV << endl;
      
      if (
	  (value_finalDV<vec_discretized_fitrange_min[index_finalDV] || value_finalDV>vec_discretized_fitrange_max[index_finalDV])
	  ) {
	//	cout << "remove it" << endl;
	keep_event=0;
	break; //at least one final DV is outside region of fit, so skip it for computation of chi2
      }
    }
    
    if (!keep_event)
      continue;

    if (vec_roorealvar_finalDV.size()==1) {
      representative_hist_dataset_for_chi2->Fill(argset->getRealValue(vec_roorealvar_finalDV[0]->GetName()),dataset->weight());
      representative_hist_unweighted_dataset_for_chi2->Fill(argset->getRealValue(vec_roorealvar_finalDV[0]->GetName()));
    }
    else if (vec_roorealvar_finalDV.size()==2) {
      ((TH2D *)representative_hist_dataset_for_chi2)->Fill(argset->getRealValue(vec_roorealvar_finalDV[0]->GetName()),argset->getRealValue(vec_roorealvar_finalDV[1]->GetName()),dataset->weight());
      ((TH2D *)representative_hist_unweighted_dataset_for_chi2)->Fill(argset->getRealValue(vec_roorealvar_finalDV[0]->GetName()),argset->getRealValue(vec_roorealvar_finalDV[1]->GetName()));
    }

    //    double observable_value=argset->getRealValue("m_yy");
    //   hist_dataset_for_chi2->Fill(observable_value,dataset->weight());

    //for 2D, bin is function of two coordinates : see fillHistogram

    int bin_x=0;

    if (vec_roorealvar_finalDV.size()==1)
      bin_x=representative_hist_dataset_for_chi2->FindBin(argset->getRealValue(vec_roorealvar_finalDV[0]->GetName()));
    
    int bin_y=0;
    if (vec_roorealvar_finalDV.size()==2)
      bin_y=representative_hist_dataset_for_chi2->FindBin(argset->getRealValue(vec_roorealvar_finalDV[0]->GetName()),argset->getRealValue(vec_roorealvar_finalDV[1]->GetName()));
    
    //not used ?
    if (vec_roorealvar_finalDV.size()==1)
      representative_hist_dataset_for_chi2->SetBinError(bin_x,sqrt(TMath::Power(representative_hist_dataset_for_chi2->GetBinError(bin_x),2)));
    else if (vec_roorealvar_finalDV.size()==2)
      representative_hist_dataset_for_chi2->SetBinError(bin_x,bin_y,sqrt(TMath::Power(representative_hist_dataset_for_chi2->GetBinError(bin_x,bin_y),2)));
  } //end loop on entries

  cout << "representative_hist_dataset_for_chi2->Integral()=" << representative_hist_dataset_for_chi2->Integral() << endl;
  //  exit(1);

  //  representative_hist_dataset_for_chi2->Sumw2();

  TCanvas *canvas=new TCanvas("canvas","canvas",800,600);
  representative_hist_dataset_for_chi2->SetMaximum(0.2);
  representative_hist_dataset_for_chi2->Draw();
  canvas->SaveAs("debug.png");
  delete canvas;
  //  exit(1);
  
  //shit  TArrayD *array_dataset_sumw=0;

  TArrayD *array_dataset_sumw2=0;

  array_dataset_sumw2=representative_hist_dataset_for_chi2->GetSumw2();
  
  //careful array_dataset_sumw2 size is (nbins_x+2)*(nbins_y+2) : because of underflow, overflow

  cout << "representative_hist_dataset_for_chi2->GetNbinsX()=" << representative_hist_dataset_for_chi2->GetNbinsX() << endl;
  cout << "array_dataset_sumw2->GetSize()=" << array_dataset_sumw2->GetSize() << endl;
  //  exit(1);
  //  cout << "vec_roorealvar_finalDV[0]->numBins()=" << vec_roorealvar_finalDV[0]->numBins() << endl;
  //  if (vec_roorealvar_finalDV.size()==2)
  //    cout << "vec_roorealvar_finalDV[1]->numBins()=" << vec_roorealvar_finalDV[1]->numBins() << endl;
  
  //  cout << "loop on bins of histogram" << endl;

  unsigned int max_index_bin_y=0;

  if (vec_roorealvar_finalDV.size()==1)
    max_index_bin_y=1;
  else if (vec_roorealvar_finalDV.size()==2)
    max_index_bin_y=representative_hist_dataset_for_chi2->GetNbinsY();

  /*
  if (argset_finalDV_noWeight.size()==1)
    max_index_bin_y=1;
  else if (argset_finalDV_noWeight.size()==2)
    max_index_bin_y=representative_hist_dataset_for_chi2->GetNbinsY();
  */

  for (unsigned int index_bin_y=1;index_bin_y<=max_index_bin_y;index_bin_y++) {
    
    //cout << "index_bin_y=" << index_bin_y << endl;

    double position_dataset_current_bin_y=0;

    if (argset_finalDV_noWeight.size()==2) {
      position_dataset_current_bin_y=representative_hist_dataset_for_chi2->GetYaxis()->GetBinCenter(index_bin_y);
      
      if (position_dataset_current_bin_y<vec_discretized_fitrange_min[1] || position_dataset_current_bin_y>vec_discretized_fitrange_max[1])
	continue;
    }
    
    int n_bins_x=representative_hist_dataset_for_chi2->GetNbinsX();
    
    for (int index_bin_x=1;index_bin_x<=n_bins_x;index_bin_x++) {
      
      //cout << "index_bin_x=" << index_bin_x << " / " << n_bins_x << endl;
      
      double position_dataset_current_bin_x=representative_hist_dataset_for_chi2->GetXaxis()->GetBinCenter(index_bin_x);

      if (DEBUG)
	cout << "position_dataset_current_bin_x=" << position_dataset_current_bin_x << endl;

      if (position_dataset_current_bin_x<vec_discretized_fitrange_min[0] || position_dataset_current_bin_x>vec_discretized_fitrange_max[0])
	continue; //at least one final DV is outside region of fit, so skip it for computation of chi2
      
      double value_dataset_current_bin=0;

      if (argset_finalDV_noWeight.size()==1)
	value_dataset_current_bin=representative_hist_dataset_for_chi2->GetBinContent(index_bin_x);
      else if (argset_finalDV_noWeight.size()==2)
	value_dataset_current_bin=((TH2D *)representative_hist_dataset_for_chi2)->GetBinContent(index_bin_x,index_bin_y);
      
      double err_value_dataset_current_bin=0;
      double err_l_value_dataset_current_bin=0;
      double err_h_value_dataset_current_bin=0;
      
      int index_bin_effective=0;
      
      if (argset_finalDV_noWeight.size()==1)
	index_bin_effective=index_bin_x;
      else if (argset_finalDV_noWeight.size()==2) {
	//note: +2 for index_bin_y: because of underflow and overflow values
	//note: index_bin_x is transparent
	
	index_bin_effective=index_bin_y*(2+n_bins_x)+index_bin_x;
	//	cout << "index_bin_effective=" << index_bin_effective << endl;
      }
      
      err_value_dataset_current_bin=sqrt(array_dataset_sumw2->GetAt(index_bin_effective));
      
      err_l_value_dataset_current_bin=err_value_dataset_current_bin;
      err_h_value_dataset_current_bin=err_value_dataset_current_bin;
      
      //trapezoid rule (rectangle method drives an important bias)
      //this approach does not allow to make trapezoidal rule : bias
      
      double value_pdf_current_bin=0;

      if (argset_finalDV_noWeight.size()==1) {
	double Xmin=representative_hist_dataset_for_chi2->GetBinCenter(index_bin_x)-0.5*representative_hist_dataset_for_chi2->GetBinWidth(index_bin_x);
	double Xmax=representative_hist_dataset_for_chi2->GetBinCenter(index_bin_x)+0.5*representative_hist_dataset_for_chi2->GetBinWidth(index_bin_x);
	//double granularity_x=(Xmax-Xmin)/5.5; //typical of RooPlot::chiSquare
	//double granularity_x=(Xmax-Xmin)/5;

	//	cout << "Xmin=" << Xmin << ", Xmax=" << Xmax << endl;
	//never replace Xmin due to fit range, else huge bias on tails

	double granularity_x=(Xmax-Xmin)/10; //important to have an integer, else, algorithm will either miss residual or catch part from next bin another algorithm that manages the residual would deteriorate readiness

	// 	cout << "Xmin=" << Xmin << ", Xmax=" << Xmax << endl;
	// 	cout << "granularity_x=" << granularity_x << endl;

	double value_pdf_low_edge_current_sub_bin=0;
	double value_pdf_high_edge_current_sub_bin=0;
	
	double sum=0;
	
	double x=Xmin;
	
	double x_low_edge_current_sub_bin=0;
	double x_high_edge_current_sub_bin=0;

	//variante for extra term
	//	for (x=Xmin;x+granularity_x<Xmax;x+=granularity_x) { //special trick to reproduce as much as possible RooPlot::chiSquare

	double epsilon=1e-3; //trick to enter cases with numerical<numerical !
	for (x=Xmin;x<Xmax-epsilon;x+=granularity_x) {
	  x_low_edge_current_sub_bin=x;
	  x_high_edge_current_sub_bin=x+granularity_x;
	  
	  vec_roorealvar_finalDV[0]->setVal(x_low_edge_current_sub_bin);
	  value_pdf_low_edge_current_sub_bin=integral_dataset*pdf->getVal(RooArgSet(*(vec_roorealvar_finalDV[0])))*vec_roorealvar_finalDV[0]->getBinWidth(1);
	  
	  vec_roorealvar_finalDV[0]->setVal(x_high_edge_current_sub_bin);
	  value_pdf_high_edge_current_sub_bin=integral_dataset*pdf->getVal(RooArgSet(*(vec_roorealvar_finalDV[0])))*vec_roorealvar_finalDV[0]->getBinWidth(1);

	  if (DEBUG) {	  
	    cout << "x_low_edge_current_sub_bin=" << x_low_edge_current_sub_bin << ", value_pdf_low_edge_current_sub_bin=" << value_pdf_low_edge_current_sub_bin << endl;
	    cout << "x_high_edge_current_sub_bin=" << x_high_edge_current_sub_bin << ", value_pdf_high_edge_current_sub_bin=" << value_pdf_high_edge_current_sub_bin << endl;
	  }
	  
	  double value_pdf_current_sub_bin=0.5*(value_pdf_low_edge_current_sub_bin+value_pdf_high_edge_current_sub_bin);
	  //	  cout << "value_pdf_current_sub_bin=" << value_pdf_current_sub_bin << endl;

	  sum+=(x_high_edge_current_sub_bin-x_low_edge_current_sub_bin)*value_pdf_current_sub_bin;
	  //	  cout << "so far, sum=" << sum << endl;
	} //end loop on sub_bins of current bin

	sum/=(Xmax-Xmin);

	value_pdf_current_bin=sum;
	//	cout << "sum=" << sum << endl;
      } //end case 1 variable
      else if (argset_finalDV_noWeight.size()==2) {

	double Xmin=representative_hist_dataset_for_chi2->GetXaxis()->GetBinCenter(index_bin_x)-0.5*representative_hist_dataset_for_chi2->GetXaxis()->GetBinWidth(index_bin_x);
	double Xmax=representative_hist_dataset_for_chi2->GetXaxis()->GetBinCenter(index_bin_x)+0.5*representative_hist_dataset_for_chi2->GetXaxis()->GetBinWidth(index_bin_x);

	double Ymin=representative_hist_dataset_for_chi2->GetYaxis()->GetBinCenter(index_bin_y)-0.5*representative_hist_dataset_for_chi2->GetYaxis()->GetBinWidth(index_bin_y);
	double Ymax=representative_hist_dataset_for_chi2->GetYaxis()->GetBinCenter(index_bin_y)+0.5*representative_hist_dataset_for_chi2->GetYaxis()->GetBinWidth(index_bin_y);

	//	cout << "Xmin=" << Xmin << ", Xmax=" << Xmax << endl;
	//	cout << "Ymin=" << Ymin << ", Ymax=" << Ymax << endl;

	//never replace Xmin due to fit range, else huge bias on tails

	double granularity_x=(Xmax-Xmin)/10; //important to have an integer, else, algorithm will either miss residual or catch part from next bin another algorithm that manages the residual would deteriorate readiness
	double granularity_y=(Ymax-Ymin)/10; //important to have an integer, else, algorithm will either miss residual or catch part from next bin another algorithm that manages the residual would deteriorate readiness
	
	//	double granularity_x=(Xmax-Xmin)/10; //important to have an integer, else, algorithm will either miss residual or catch part from next bin another algorithm that manages the residual would deteriorate readiness
	//	double granularity_y=(Ymax-Ymin)/5; //important to have an integer, else, algorithm will either miss residual or catch part from next bin another algorithm that manages the residual would deteriorate readiness
	
	//	cout << "granularity_x=" << granularity_x << endl;
	//	cout << "granularity_y=" << granularity_y << endl;
	
	// 	cout << "new values" << endl;
	// 	cout << "Xmin=" << Xmin << ", Xmax=" << Xmax << endl;
	// 	cout << "Ymin=" << Ymin << ", Ymax=" << Ymax << endl;
	// 	cout << "granularity_x=" << granularity_x << endl;
	// 	cout << "granularity_y=" << granularity_y << endl;
	
	double value_pdf_corner_low_edge_x_low_edge_y_current_sub_bin=0;
	double value_pdf_corner_low_edge_x_high_edge_y_current_sub_bin=0;
	double value_pdf_corner_high_edge_x_low_edge_y_current_sub_bin=0;
	double value_pdf_corner_high_edge_x_high_edge_y_current_sub_bin=0;
	
	double sum=0;
	
	double epsilon=1e-3; //trick to enter cases with numerical<numerical !

	//--------------------------
	//debugging
	
	//	vec_roorealvar_finalDV[0]->setVal(representative_hist_dataset_for_chi2->GetXaxis()->GetBinCenter(index_bin_x));
	//	vec_roorealvar_finalDV[1]->setVal(representative_hist_dataset_for_chi2->GetYaxis()->GetBinCenter(index_bin_y));
	// 	cout << "for x=" << representative_hist_dataset_for_chi2->GetXaxis()->GetBinCenter(index_bin_x) << ", y=" << representative_hist_dataset_for_chi2->GetYaxis()->GetBinCenter(index_bin_y) << endl;
	// 	cout << "nb entries data: =" << representative_hist_unweighted_dataset_for_chi2->GetBinContent(index_bin_x,index_bin_y) << endl;
	// 	cout << "value_dataset_current_bin=" << value_dataset_current_bin << endl;
	// 	cout << "value pdf=" << integral_dataset*pdf->getVal(RooArgSet(*(vec_roorealvar_finalDV[0]),*(vec_roorealvar_finalDV[1])))*vec_roorealvar_finalDV[0]->getBinWidth(1)*vec_roorealvar_finalDV[1]->getBinWidth(1) << endl;
	// 	cout << "detail information for construction of pdf: pdf normalized to 1 : " << pdf->getVal(RooArgSet(*(vec_roorealvar_finalDV[0]),*(vec_roorealvar_finalDV[1]))) << endl;
	// 	cout << "integral_dataset=" << integral_dataset << endl;
	// 	cout << "bin width x=" << vec_roorealvar_finalDV[0]->getBinWidth(1) << endl;
	// 	cout << "bin width y=" << vec_roorealvar_finalDV[1]->getBinWidth(1) << endl;
	
	for (double y=Ymin;y<Ymax-epsilon;y+=granularity_y) {
	  
	  vec_roorealvar_finalDV[1]->setVal(y);

	  double y_low_edge_current_sub_bin=y;
	  double y_high_edge_current_sub_bin=y+granularity_y;

	  for (double x=Xmin;x<Xmax-epsilon;x+=granularity_x) {
	    
	    double x_low_edge_current_sub_bin=x;
	    double x_high_edge_current_sub_bin=x+granularity_x;
	    
	    vec_roorealvar_finalDV[0]->setVal(x_low_edge_current_sub_bin);
	    vec_roorealvar_finalDV[1]->setVal(y_low_edge_current_sub_bin);
	    value_pdf_corner_low_edge_x_low_edge_y_current_sub_bin=integral_dataset*pdf->getVal(RooArgSet(*(vec_roorealvar_finalDV[0]),*(vec_roorealvar_finalDV[1])))*vec_roorealvar_finalDV[0]->getBinWidth(1)*vec_roorealvar_finalDV[1]->getBinWidth(1);
	    
	    vec_roorealvar_finalDV[0]->setVal(x_high_edge_current_sub_bin);
	    vec_roorealvar_finalDV[1]->setVal(y_low_edge_current_sub_bin);
	    value_pdf_corner_high_edge_x_low_edge_y_current_sub_bin=integral_dataset*pdf->getVal(RooArgSet(*(vec_roorealvar_finalDV[0]),*(vec_roorealvar_finalDV[1])))*vec_roorealvar_finalDV[0]->getBinWidth(1)*vec_roorealvar_finalDV[1]->getBinWidth(1);
	    
	    vec_roorealvar_finalDV[0]->setVal(x_low_edge_current_sub_bin);
	    vec_roorealvar_finalDV[1]->setVal(y_high_edge_current_sub_bin);
	    value_pdf_corner_low_edge_x_high_edge_y_current_sub_bin=integral_dataset*pdf->getVal(RooArgSet(*(vec_roorealvar_finalDV[0]),*(vec_roorealvar_finalDV[1])))*vec_roorealvar_finalDV[0]->getBinWidth(1)*vec_roorealvar_finalDV[1]->getBinWidth(1);
	    
	    vec_roorealvar_finalDV[0]->setVal(x_high_edge_current_sub_bin);
	    vec_roorealvar_finalDV[1]->setVal(y_high_edge_current_sub_bin);
	    value_pdf_corner_high_edge_x_high_edge_y_current_sub_bin=integral_dataset*pdf->getVal(RooArgSet(*(vec_roorealvar_finalDV[0]),*(vec_roorealvar_finalDV[1])))*vec_roorealvar_finalDV[0]->getBinWidth(1)*vec_roorealvar_finalDV[1]->getBinWidth(1);;

	    // 	    cout << "value_pdf_corner_low_edge_x_low_edge_y_current_sub_bin=" << value_pdf_corner_low_edge_x_low_edge_y_current_sub_bin << endl;
	    // 	    cout << "value_pdf_corner_high_edge_x_low_edge_y_current_sub_bin=" << value_pdf_corner_high_edge_x_low_edge_y_current_sub_bin << endl;
	    // 	    cout << "value_pdf_corner_low_edge_x_high_edge_y_current_sub_bin=" << value_pdf_corner_low_edge_x_high_edge_y_current_sub_bin << endl;
	    // 	    cout << "value_pdf_corner_high_edge_x_high_edge_y_current_sub_bin=" << value_pdf_corner_high_edge_x_high_edge_y_current_sub_bin << endl;
	    
	    double value_pdf_current_sub_bin=0.25*(value_pdf_corner_low_edge_x_low_edge_y_current_sub_bin+value_pdf_corner_high_edge_x_low_edge_y_current_sub_bin+value_pdf_corner_low_edge_x_high_edge_y_current_sub_bin+value_pdf_corner_high_edge_x_high_edge_y_current_sub_bin);
	    //	    cout << "x_low_edge_current_sub_bin=" << x_low_edge_current_sub_bin << ", x_high_edge_current_sub_bin=" << x_high_edge_current_sub_bin << ", y_low_edge_current_sub_bin=" << y_low_edge_current_sub_bin << ", y_high_edge_current_sub_bin=" << y_high_edge_current_sub_bin << ", value_pdf_current_sub_bin=" << value_pdf_current_sub_bin << endl;
	    
	    sum+=granularity_x*granularity_y*value_pdf_current_sub_bin/( (Xmax-Xmin)*(Ymax-Ymin) );
	    //	    cout << "sum=" << sum << endl;
	  } //end loop on sub_bins of current bin
	} //end loop on y
	
	value_pdf_current_bin=sum;
      } //end case 2 variables
      
      //       cout << "value_dataset_current_bin=" << value_dataset_current_bin << endl;
      //       cout << "value_pdf_current_bin=" << value_pdf_current_bin << endl;


      //more stable, in particular for 2D, with 10 entries

      if (
	  (argset_finalDV_noWeight.size()==1 && representative_hist_unweighted_dataset_for_chi2->GetBinContent(index_bin_x)<10)
	  ||
	  (argset_finalDV_noWeight.size()==2 && representative_hist_unweighted_dataset_for_chi2->GetBinContent(index_bin_x,index_bin_y)<10)
	  )
	continue;


      //skip case with <5 entries : non gaussian like: could not trust contribution of chi2
      
      /*
      if (
	  (argset_finalDV_noWeight.size()==1 && representative_hist_unweighted_dataset_for_chi2->GetBinContent(index_bin_x)<5)
	  ||
	  (argset_finalDV_noWeight.size()==2 && representative_hist_unweighted_dataset_for_chi2->GetBinContent(index_bin_x,index_bin_y)<5)
	  )
	continue;
      */      

      /*
      //6
      if (
	  (argset_finalDV_noWeight.size()==1 && representative_hist_unweighted_dataset_for_chi2->GetBinContent(index_bin_x)<6)
	  ||
	  (argset_finalDV_noWeight.size()==2 && representative_hist_unweighted_dataset_for_chi2->GetBinContent(index_bin_x,index_bin_y)<6)
	  )
	continue;
      */


      //7
      /*
      if (
	  (argset_finalDV_noWeight.size()==1 && representative_hist_unweighted_dataset_for_chi2->GetBinContent(index_bin_x)<7)
	  ||
	  (argset_finalDV_noWeight.size()==2 && representative_hist_unweighted_dataset_for_chi2->GetBinContent(index_bin_x,index_bin_y)<7)
	  )
	continue;
      */

      /*
      //8
      if (
	  (argset_finalDV_noWeight.size()==1 && representative_hist_unweighted_dataset_for_chi2->GetBinContent(index_bin_x)<8)
	  ||
	  (argset_finalDV_noWeight.size()==2 && representative_hist_unweighted_dataset_for_chi2->GetBinContent(index_bin_x,index_bin_y)<8)
	  )
	continue;
      */

      /*
      //9
      if (
	  (argset_finalDV_noWeight.size()==1 && representative_hist_unweighted_dataset_for_chi2->GetBinContent(index_bin_x)<9)
	  ||
	  (argset_finalDV_noWeight.size()==2 && representative_hist_unweighted_dataset_for_chi2->GetBinContent(index_bin_x,index_bin_y)<9)
	  )
	continue;
      */

      /*
      //10
      if (
	  (argset_finalDV_noWeight.size()==1 && representative_hist_unweighted_dataset_for_chi2->GetBinContent(index_bin_x)<10)
	  ||
	  (argset_finalDV_noWeight.size()==2 && representative_hist_unweighted_dataset_for_chi2->GetBinContent(index_bin_x,index_bin_y)<10)
	  )
	continue;
      */

      /*
      if (
	  (argset_finalDV_noWeight.size()==1 && representative_hist_unweighted_dataset_for_chi2->GetBinContent(index_bin_x)<15)
	  ||
	  (argset_finalDV_noWeight.size()==2 && representative_hist_unweighted_dataset_for_chi2->GetBinContent(index_bin_x,index_bin_y)<15)
	  )
	continue;
      */

      if (value_dataset_current_bin==0)
	continue;
      
      nbins++;
      
      if (err_value_dataset_current_bin==0) {
	cout << "problem, halt program" << endl;
	
	if (vec_roorealvar_finalDV.size()==1)
	  cout << "index_bin_x=" << index_bin_x << ", position_dataset_current_bin_x=" << position_dataset_current_bin_x << ", value_dataset_current_bin=" << value_dataset_current_bin << ", value_pdf_current_bin=" << value_pdf_current_bin << ", err_l_value_dataset_current_bin=" << err_l_value_dataset_current_bin << ", err_h_value_dataset_current_bin=" << err_h_value_dataset_current_bin << endl;
	else if (vec_roorealvar_finalDV.size()==2)
	  cout << "index_bin_x=" << index_bin_x << ", position_dataset_current_bin_x=" << position_dataset_current_bin_x << ", position_dataset_current_bin_y=" << position_dataset_current_bin_y << ", value_dataset_current_bin=" << value_dataset_current_bin << ", value_pdf_current_bin=" << value_pdf_current_bin << ", err_l_value_dataset_current_bin=" << err_l_value_dataset_current_bin << ", err_h_value_dataset_current_bin=" << err_h_value_dataset_current_bin << ", err_value_dataset_current_bin=" << err_value_dataset_current_bin << endl;
      }
      
      //      cout << "now, nbins=" << nbins << endl;
      //double pull_current_bin=(value_dataset_current_bin-value_pdf_current_bin)/err_value_dataset_current_bin;
      
      //mimic exactly RooPlot::chiSquare, but allowing to change error treatment, and allowing 2D
      double pull_current_bin=(value_dataset_current_bin>value_pdf_current_bin) ? (value_dataset_current_bin-value_pdf_current_bin)/err_l_value_dataset_current_bin : (value_dataset_current_bin-value_pdf_current_bin)/err_h_value_dataset_current_bin;
      
      chi2+=pull_current_bin*pull_current_bin;

      /*
      cout << "====" << endl;
      cout << "position_dataset_current_bin_x=" << position_dataset_current_bin_x << endl;
      cout << "add pull_current_bin^2=" << pull_current_bin*pull_current_bin << endl;
      cout << "value_dataset_current_bin=" << value_dataset_current_bin << endl;
      cout << "value_pdf_current_bin=" << value_pdf_current_bin << endl;
      cout << "so far, chi2=" << chi2 << endl;
      */

      //cout << "before, err_chi2=" << err_chi2 << endl;
      err_chi2+=4*pull_current_bin*pull_current_bin;  //sqrt{  sum  [2(d_i-t_i)/sigma_i]^2 }
      //	cout << "after, err_chi2=" << err_chi2 << endl;
      
      //	cout << "nbins=" << nbins << endl;
      
      if (DEBUG) {
	if (vec_roorealvar_finalDV.size()==1) {
	  if (1) {
	  //	  if (representative_hist_unweighted_dataset_for_chi2->GetBinContent(index_bin_x)<10) {
	    cout << "index_bin_x=" << index_bin_x << ", position_dataset_current_bin_x=" << position_dataset_current_bin_x << ", value_dataset_current_bin=" << value_dataset_current_bin << ", value_pdf_current_bin=" << value_pdf_current_bin << ", err_l_value_dataset_current_bin=" << err_l_value_dataset_current_bin << ", err_h_value_dataset_current_bin=" << err_h_value_dataset_current_bin << ", add " << pull_current_bin*pull_current_bin << ", so far, chi2=" << chi2 << endl;
	    cout << ", nb entries=" << representative_hist_unweighted_dataset_for_chi2->GetBinContent(index_bin_x,index_bin_y) << endl;
	  }
	}
	else if (vec_roorealvar_finalDV.size()==2) {
	  //cout << "index_bin_x=" << index_bin_x << ", index_bin_y=" << index_bin_y << ", position_dataset_current_bin_x=" << position_dataset_current_bin_x << ", position_dataset_current_bin_y=" << position_dataset_current_bin_y << ", value_dataset_current_bin=" << value_dataset_current_bin << ", value_pdf_current_bin=" << value_pdf_current_bin << ", err_l_value_dataset_current_bin=" << err_l_value_dataset_current_bin << ", err_h_value_dataset_current_bin=" << err_h_value_dataset_current_bin << ", add " << pull_current_bin*pull_current_bin << ", nb entries=" << representative_hist_unweighted_dataset_for_chi2->GetBinContent(index_bin_x,index_bin_y) << endl;
	  
	  //cout << "index_bin_x=" << index_bin_x << ", index_bin_y=" << index_bin_y << ", position_dataset_current_bin_x=" << position_dataset_current_bin_x << ", position_dataset_current_bin_y=" << position_dataset_current_bin_y << ", value_dataset_current_bin=" << value_dataset_current_bin << ", value_pdf_current_bin=" << value_pdf_current_bin << ", err_l_value_dataset_current_bin=" << err_l_value_dataset_current_bin << ", err_h_value_dataset_current_bin=" << err_h_value_dataset_current_bin << ", add " << pull_current_bin*pull_current_bin << ", so far, chi2=" << chi2 << ", so far err_chi2=" << sqrt(err_chi2) << ", nb entries=" << representative_hist_unweighted_dataset_for_chi2->GetBinContent(index_bin_x,index_bin_y) << ", error data variante=" << representative_hist_dataset_for_chi2->GetBinError(index_bin_x,index_bin_y) << ", variante pdf=" << representative_hist_pdf_for_chi2->GetBinContent(index_bin_x,index_bin_y) << endl;
	  
	  //nominal one	
	  cout << "index_bin_x=" << index_bin_x << ", index_bin_y=" << index_bin_y << ", position_dataset_current_bin_x=" << position_dataset_current_bin_x << ", position_dataset_current_bin_y=" << position_dataset_current_bin_y << ", value_dataset_current_bin=" << value_dataset_current_bin << ", value_pdf_current_bin=" << value_pdf_current_bin << ", err_l_value_dataset_current_bin=" << err_l_value_dataset_current_bin << ", err_h_value_dataset_current_bin=" << err_h_value_dataset_current_bin << ", add " << pull_current_bin*pull_current_bin << ", so far, chi2=" << chi2 << ", so far err_chi2=" << sqrt(err_chi2) << ", nb entries=" << representative_hist_unweighted_dataset_for_chi2->GetBinContent(index_bin_x,index_bin_y) << endl;
	} 
	//	  cout << "so far, nbins=" << nbins << endl;
      }
      
      //      cout << "go to next x" << endl;
    } //end loop on bins x
    
    //    cout << "go to next y" << endl;
  } //end loop on bins y
  
  err_chi2=sqrt(err_chi2);
  
  if (vec_roorealvar_finalDV.size()==1)
    nparams=((RooArgSet *)pdf->getParameters(RooArgSet(*vec_roorealvar_finalDV[0]))->selectByAttrib("Constant",kFALSE))->getSize();
  else if (vec_roorealvar_finalDV.size()==2)
    nparams=((RooArgSet *)pdf->getParameters(RooArgSet(*vec_roorealvar_finalDV[0],*vec_roorealvar_finalDV[1]))->selectByAttrib("Constant",kFALSE))->getSize();
  
  nparams++; //consider the normalization parameter, since the pdf is not extended
  
  ndfs=nbins-nparams;
  
  cout << "chi2=" << chi2 << " +/- " << err_chi2 << endl;
  cout << "nbins=" << nbins << endl;
  cout << "nparams=" << nparams << endl;
  cout << "chi2/ndf=" << chi2/(nbins-nparams) << " +/- " << err_chi2/(nbins-nparams) << endl;

  cout << "inside, ndfs=" << ndfs << endl;

  //  cout << "delete histograms" << endl;
  delete representative_hist_dataset_for_chi2;
  delete representative_hist_unweighted_dataset_for_chi2;

  //  cout << "return macro chi2/ndf" << endl;
  //  cout << "exit ComputeChi2" << endl;

  vec_discretized_fitrange_min.clear();
  vec_discretized_fitrange_max.clear();
  vec_roorealvar_finalDV.clear();

  cout << "END ComputeChi2_ndf" << endl;
}
