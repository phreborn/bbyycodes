//===========================================================================================================
//rename string_observable
//vec_string_characteristic could be the process, or even the category for example

//vec_string_characteristic: in case of non resonant, for detailed processes: name, etc.

void Draw_observable_f_characteristic(string string_category,string string_finalDV,string string_observable_f_characteristic,vector<string> vec_string_characteristic,vector<double> vec_double_characteristic,vector<double> vec_observable_f_characteristic,vector<double> vec_err_observable_f_characteristic)
{
  //  cout << "Draw_observable_f_characteristic phase 1" << endl;
  
  //  cout << "vec_string_characteristic.size()=" << vec_string_characteristic.size() << endl;
  
  string string_latex_observable_f_process;
  
  if (string_observable_f_characteristic=="yield")
    string_latex_observable_f_process="yield";
  else if (string_observable_f_characteristic=="efficiency")
    string_latex_observable_f_process="efficiency";
  else if (string_observable_f_characteristic=="mu")
    string_latex_observable_f_process="#mu [GeV]";
  else if (string_observable_f_characteristic=="sigma")
    string_latex_observable_f_process="#sigma [GeV]";
  else if (string_observable_f_characteristic=="sigma68")
    string_latex_observable_f_process="#sigma_{68} [GeV]";
  else if (string_observable_f_characteristic=="sigma68_mu")
    string_latex_observable_f_process="#sigma_{68}/#mu peak";

  else if (string_observable_f_characteristic=="alphaCB_Low")
    string_latex_observable_f_process="#alpha_{CB Low} [GeV]";
  else if (string_observable_f_characteristic=="nCB_Low")
    string_latex_observable_f_process="n_{CB Low}";
  else if (string_observable_f_characteristic=="alphaCB_High")
    string_latex_observable_f_process="#alpha_{CB High} [GeV]";
  else if (string_observable_f_characteristic=="nCB_High")
    string_latex_observable_f_process="n_{CB High}";
  
  //  for (unsigned int index_finalDV=0;index_finalDV<vec_string_finalDV.size();index_finalDV++) {
  //----------------------------------------------------------------------
  //no need to put name with details ?
  //to rename in canvas
  //not put name ?

  TCanvas *canvas_observable_f_process=new TCanvas((string("canvas_observable_f_process")+string_finalDV).c_str(),(string("canvas_observable_f_process")+string_finalDV).c_str(),800,600);
  canvas_observable_f_process->SetLeftMargin(0.13);
  canvas_observable_f_process->SetRightMargin(0.03);
  canvas_observable_f_process->SetTopMargin(0.05);

  /*shit
  TCanvas canvas_observable_f_process((string("canvas_observable_f_process")+string_finalDV).c_str(),(string("canvas_observable_f_process")+string_finalDV).c_str(),800,600);
  canvas_observable_f_process.SetLeftMargin(0.13);
  canvas_observable_f_process.SetRightMargin(0.03);
  canvas_observable_f_process.SetTopMargin(0.05);
  */

  unsigned int n_processes=vec_string_characteristic.size();
  
  //search for max and min, for the range
  
  float min_graph_observable_f_process=std::numeric_limits<float>::max();
  float max_graph_observable_f_process=-std::numeric_limits<float>::max();
  
  for (unsigned int index_characteristic=0;index_characteristic<n_processes;index_characteristic++) {
    //problem in case of big error
    /*
    if (vec_observable_f_characteristic[index_characteristic]-vec_err_observable_f_characteristic[index_characteristic]<min_graph_observable_f_process)
      min_graph_observable_f_process=vec_observable_f_characteristic[index_characteristic];
    if (vec_observable_f_characteristic[index_characteristic]+vec_err_observable_f_characteristic[index_characteristic]>max_graph_observable_f_process)
      max_graph_observable_f_process=vec_observable_f_characteristic[index_characteristic];
    */

    if (vec_observable_f_characteristic[index_characteristic]<min_graph_observable_f_process)
      min_graph_observable_f_process=vec_observable_f_characteristic[index_characteristic];
    if (vec_observable_f_characteristic[index_characteristic]>max_graph_observable_f_process)
      max_graph_observable_f_process=vec_observable_f_characteristic[index_characteristic];
  }
  
  //  cout << "min_graph_observable_f_process=" << min_graph_observable_f_process << ", max_graph_observable_f_process=" << max_graph_observable_f_process << endl;
  
  min_graph_observable_f_process/=1.01;
  max_graph_observable_f_process*=1.01;
  
  vector<double> vec_double_err_characteristic;
  
  for (unsigned int index_characteristic=0;index_characteristic<vec_double_characteristic.size();index_characteristic++)
    vec_double_err_characteristic.push_back(0);
  
  //wo/ error: TGraph *graph_observable_f_process=new TGraph(n_processes,vec_double_characteristic.data(),vec_observable_f_characteristic.data());
  TGraphErrors *graph_observable_f_process=new TGraphErrors(n_processes,vec_double_characteristic.data(),vec_observable_f_characteristic.data(),vec_double_err_characteristic.data(),vec_err_observable_f_characteristic.data());
  
  graph_observable_f_process->SetMarkerStyle(20);
  graph_observable_f_process->SetMarkerColor(kBlack);
  graph_observable_f_process->SetMarkerSize(1.);
  graph_observable_f_process->SetLineColor(kBlack);
  
  TH1F *hist_frame=0;
  
  //  cout << "n_processes=" << n_processes << endl;
  
  /*keep for Single Higgs
  if (string_non_resonant_resonant=="non_resonant")
    hist_frame=new TH1F("hist_frame","hist_frame",n_processes,0,n_processes);
  */
  if (string_non_resonant_resonant=="non_resonant")
    hist_frame=new TH1F("hist_frame","hist_frame",n_processes,vec_double_characteristic[0]-1,vec_double_characteristic[n_processes-1]+1);

  else if (string_non_resonant_resonant=="resonant")
    hist_frame=new TH1F("hist_frame","hist_frame",n_processes,vec_double_characteristic[0]-10,vec_double_characteristic[n_processes-1]+10);
  
  hist_frame->SetLineColor(kBlack);
  hist_frame->SetMinimum(min_graph_observable_f_process);
  hist_frame->SetMaximum(max_graph_observable_f_process);
  
  /*keep for Single Higgs
  if (string_non_resonant_resonant=="non_resonant") {
    for (unsigned int index_characteristic=0;index_characteristic<vec_string_characteristic.size();index_characteristic++) {
      cout << "index_characteristic=" << index_characteristic << ", characteristic " << vec_string_characteristic[index_characteristic] << endl;
      hist_frame->GetXaxis()->SetBinLabel(index_characteristic+1,vec_string_characteristic[index_characteristic].c_str());
    }
  }
  */
  
  hist_frame->Draw();
  
  /*in case of single higgs
  if (string_non_resonant_resonant=="non_resonant")
    hist_frame->SetXTitle(""); //Process is obvious
  */
  
  if (string_non_resonant_resonant=="non_resonant")
    hist_frame->SetXTitle("#kappa_{#lambda}"); //Process is obvious
  else if (string_non_resonant_resonant=="resonant") {
    if (string_category=="f_categories")
      hist_frame->SetXTitle("Category m_{X} [GeV]");
    else
      hist_frame->SetXTitle("m_{X} [GeV]");
  }
  
  hist_frame->SetYTitle(string_latex_observable_f_process.c_str());
  
  //never choose "A" option for graph, since axis chosen with DrawFrame
  
  graph_observable_f_process->Draw("P");
  graph_observable_f_process->Draw("L");
  
  canvas_observable_f_process->RedrawAxis();
  //canvas_observable_f_process.RedrawAxis();
 
  float position_x=0.45;

  TLatex mylatex;
  mylatex.SetNDC();
  mylatex.SetTextAlign(3);
  
  mylatex.SetTextSize(0.05); //0.045 is std
  mylatex.SetTextFont(72);
  mylatex.DrawLatex(position_x,0.92,"ATLAS internal");
  
  mylatex.SetTextSize(0.05); //0.045 is std
  mylatex.SetTextFont(42); //put back the font
  
  mylatex.SetTextSize(0.03); //0.045 is std
  
  float position_y=0.85;
  
  float step_delta_y=0.04;
  
  char buffer_lumi[20];
  sprintf(buffer_lumi,"L=%4.1f fb^{-1}",lumi);
  mylatex.DrawLatex(position_x,position_y,buffer_lumi);
  //  cout << "buffer_lumi=" << buffer_lumi << endl;

  position_y-=step_delta_y;
  
  for (unsigned int internal_index_finalDV=0;internal_index_finalDV<vec_string_finalDV.size();internal_index_finalDV++) {
    if (internal_index_finalDV+1<vec_string_finalDV.size())
      mylatex.DrawLatex(position_x,position_y,(vec_string_latex_root_finalDV[internal_index_finalDV]+", ").c_str());
    else
      mylatex.DrawLatex(position_x+0.06*internal_index_finalDV,position_y,vec_string_latex_root_finalDV[internal_index_finalDV].c_str());
  }
  
  position_y-=step_delta_y;
  
  mylatex.DrawLatex(position_x,position_y,string_category.c_str());
  
  position_y-=step_delta_y;
  
  if (string_observable_f_characteristic!="yield" && string_observable_f_characteristic!="efficiency")
    mylatex.DrawLatex(position_x,position_y,(string("Projection: ")+string_finalDV).c_str());
  
  string string_saveas_observable_f_process="figures/";
  string_saveas_observable_f_process+=string_non_resonant_resonant;
  string_saveas_observable_f_process+="/";
  string_saveas_observable_f_process+=string_model;
  string_saveas_observable_f_process+="/";
  string_saveas_observable_f_process+=string_non_resonant_resonant;
  string_saveas_observable_f_process+="_";
  string_saveas_observable_f_process+="Overview_";
  string_saveas_observable_f_process+=string_observable_f_characteristic;
  string_saveas_observable_f_process+="_";
  string_saveas_observable_f_process+=string_model;
  string_saveas_observable_f_process+="_";
  string_saveas_observable_f_process+="finalDV_";
  string_saveas_observable_f_process+=string_finalDV;
  string_saveas_observable_f_process+="_";
  string_saveas_observable_f_process+=string_category.c_str();
  string_saveas_observable_f_process+="_f_characteristic";
  string_saveas_observable_f_process+=".png";

  //   cout << "string_saveas_observable_f_process=" << string_saveas_observable_f_process << endl;
  //   cout << "Draw_observable_f_characteristic phase 10" << endl;
  
  canvas_observable_f_process->SaveAs(string_saveas_observable_f_process.c_str());
  //canvas_observable_f_process.SaveAs(string_saveas_observable_f_process.c_str());

  //  cout << "Draw_observable_f_characteristic phase delete hist_frame" << endl;
  
  delete hist_frame;

  //  cout << "Draw_observable_f_characteristic phase delete graph" << endl;
  delete graph_observable_f_process;
  
  //  cout << "Draw_observable_f_characteristic phase delete canvas" << endl;

  delete canvas_observable_f_process;
  
  //  cout << "Draw_observable_f_characteristic phase 14" << endl;
  
  //shit  vec_observable_f_characteristic.clear();

  //  cout << "Draw_observable_f_characteristic phase 15" << endl;
}
//===========================================================================================================
/*
IF OK, THEN DELETE THIS PART

//to migrate next function into function above
//why string_process ?!?
//===========================================================================================================
void result_f_process::Draw_observable_f_mX(string string_category,string string_observable_f_process,float string_process=125.)
{
  cout << "Draw_observable_f_mX phase 1" << endl;

  cout << "vec_string_process.size()=" << vec_string_process.size() << endl;
  
  string string_latex_observable_f_process;

  if (string_observable_f_process=="sigma68")
    string_latex_observable_f_process="#sigma_{68} [GeV]";
  else if (string_observable_f_process=="mu")
    string_latex_observable_f_process="#mu peak [GeV]";
  else if (string_observable_f_process=="sigma68_mu")
    string_latex_observable_f_process="#sigma_{68}/#mu peak";
  
  for (unsigned int index_finalDV=0;index_finalDV<vec_string_finalDV.size();index_finalDV++) {
    //----------------------------------------------------------------------
    TCanvas *canvas_observable_f_process=new TCanvas((string("canvas_observable_f_process")+vec_string_finalDV[index_finalDV]).c_str(),(string("canvas_observable_f_process")+vec_string_finalDV[index_finalDV]).c_str(),800,600);
    canvas_observable_f_process->SetLeftMargin(0.13);
    canvas_observable_f_process->SetRightMargin(0.03);
    canvas_observable_f_process->SetTopMargin(0.05);
    //    canvas_observable_f_process->SetBottomMargin(0.5);
    
    unsigned int n_processes=vec_m_hyp_resonance.size();
    
    vector<double> vec_observable_f_process;
   
    for (unsigned int index_process=0;index_process<vec_string_process.size();index_process++) {

      if (string_observable_f_process=="sigma68")
	vec_observable_f_process.push_back(vec_sigma68[index_process][index_finalDV]);
      else if (string_observable_f_process=="mu")
	vec_observable_f_process.push_back(vec_mu_model_chosen[index_process][index_finalDV]);
      else if (string_observable_f_process=="sigma68_mu")
	vec_observable_f_process.push_back(vec_sigma68[index_process][index_finalDV]/vec_mu_peak[index_process][index_finalDV]);
    }

    //search for max and min, for the range

    float min_graph_observable_f_process=std::numeric_limits<float>::max();
    float max_graph_observable_f_process=-std::numeric_limits<float>::max();
    
    for (unsigned int index_process=0;index_process<n_processes;index_process++) {
      if (vec_observable_f_process[index_process]<min_graph_observable_f_process)
	min_graph_observable_f_process=vec_observable_f_process[index_process];
      if (vec_observable_f_process[index_process]>max_graph_observable_f_process)
	max_graph_observable_f_process=vec_observable_f_process[index_process];
    }
    
    cout << "max_graph_observable_f_process=" << max_graph_observable_f_process << endl;
    
    min_graph_observable_f_process/=1.01;
    max_graph_observable_f_process*=1.01;

    TGraph *graph_observable_f_process=new TGraph(n_processes,vec_m_hyp_resonance.data(),vec_observable_f_process.data());
    
    graph_observable_f_process->SetMarkerStyle(20);
    graph_observable_f_process->SetMarkerColor(kBlack);
    graph_observable_f_process->SetMarkerSize(1.);
    graph_observable_f_process->SetLineColor(kBlack);
    
    TH1F *hist_frame=0;

    cout << "n_processes=" << n_processes << endl;

    if (string_non_resonant_resonant=="non_resonant")
      hist_frame=new TH1F("hist_frame","hist_frame",n_processes,0,n_processes);
    else if (string_non_resonant_resonant=="resonant")
      hist_frame=new TH1F("hist_frame","hist_frame",n_processes,vec_m_hyp_resonance[0]-10,vec_m_hyp_resonance[n_processes-1]+10);

    hist_frame->SetMinimum(min_graph_observable_f_process);
    hist_frame->SetMaximum(max_graph_observable_f_process);

    if (string_non_resonant_resonant=="non_resonant") {
      for (unsigned int index_process=0;index_process<vec_string_process.size();index_process++) {
	cout << "index_process=" << index_process << endl;
	hist_frame->GetXaxis()->SetBinLabel(index_process+1,vec_string_process[index_process].c_str());
      }
    }

    hist_frame->Draw();

    //    cout << "hist_frame->GetNbinsX()=" << hist_frame->GetNbinsX() << endl;
    //    cout << "string_non_resonant_resonant=" << string_non_resonant_resonant << endl;
    
    if (string_non_resonant_resonant=="non_resonant")
      hist_frame->SetXTitle(""); //Process is obvious
    else if (string_non_resonant_resonant=="resonant")
      hist_frame->SetXTitle("m_{X} [GeV]");
    
    hist_frame->SetYTitle(string_latex_observable_f_process.c_str());
        
    //never choose "A" option for graph, since axis chosen with DrawFrame
        
    
    graph_observable_f_process->Draw("P");
    graph_observable_f_process->Draw("L");
    
    canvas_observable_f_process->RedrawAxis();
    
    TLatex mylatex;
    mylatex.SetNDC();
    mylatex.SetTextAlign(3);
    
    mylatex.SetTextSize(0.05); //0.045 is std
    mylatex.SetTextFont(72);
    //    mylatex.DrawLatex(0.16,0.92,"ATLAS internal");
    mylatex.DrawLatex(0.60,0.92,"ATLAS internal");
    
    mylatex.SetTextSize(0.05); //0.045 is std
    mylatex.SetTextFont(42); //put back the font
    
    mylatex.SetTextSize(0.03); //0.045 is std
    
    float position_y=0.85;
    
    //    float step_delta_y=0.05;
    float step_delta_y=0.04;
    
    char buffer_lumi[15];
    sprintf(buffer_lumi,"L=%4.1f fb^{-1}",lumi);
    //    mylatex.DrawLatex(0.16,position_y,buffer_lumi);
    mylatex.DrawLatex(0.60,position_y,buffer_lumi);
    
    position_y-=step_delta_y;
    
    for (unsigned int internal_index_finalDV=0;internal_index_finalDV<vec_string_finalDV.size();internal_index_finalDV++) {
      if (internal_index_finalDV+1<vec_string_finalDV.size())
	mylatex.DrawLatex(0.60,position_y,(vec_string_latex_root_finalDV[internal_index_finalDV]+", ").c_str());
      else
	mylatex.DrawLatex(0.60+0.06*internal_index_finalDV,position_y,vec_string_latex_root_finalDV[internal_index_finalDV].c_str());
    }
    
    position_y-=step_delta_y;
    
    //    mylatex.DrawLatex(0.16,position_y,string_category.c_str());
    mylatex.DrawLatex(0.60,position_y,string_category.c_str());

    position_y-=step_delta_y;

    mylatex.DrawLatex(0.60,position_y,(string("Projection: ")+vec_string_latex_root_finalDV[index_finalDV]).c_str());
    
    string string_saveas_observable_f_process="figures/";
    string_saveas_observable_f_process+=string_non_resonant_resonant;
    string_saveas_observable_f_process+="/";
    string_saveas_observable_f_process+=string_model;
    string_saveas_observable_f_process+="/";
    string_saveas_observable_f_process+=string_non_resonant_resonant;
    string_saveas_observable_f_process+="_";
    string_saveas_observable_f_process+="Overview_";
    string_saveas_observable_f_process+="Fit_";
    string_saveas_observable_f_process+=string_model;
    string_saveas_observable_f_process+="_";
    string_saveas_observable_f_process+="finalDV_";
    string_saveas_observable_f_process+=vec_string_finalDV[index_finalDV];
    string_saveas_observable_f_process+="_";
    string_saveas_observable_f_process+=string_category.c_str();
    string_saveas_observable_f_process+="_";
    string_saveas_observable_f_process+=string_observable_f_process;
    string_saveas_observable_f_process+="_f_process";
    string_saveas_observable_f_process+=".png";
    
    canvas_observable_f_process->SaveAs(string_saveas_observable_f_process.c_str());

    delete graph_observable_f_process;

    //    delete legend_observable_f_process;

    delete canvas_observable_f_process;

    delete hist_frame;

    vec_observable_f_process.clear();
  } //end loop on finalDV
}
//===========================================================================================================
*/
