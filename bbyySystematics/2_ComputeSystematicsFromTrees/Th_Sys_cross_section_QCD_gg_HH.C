//from informations taken from
//https://twiki.cern.ch/twiki/bin/view/LHCPhysics/LHCHWGHH?redirectedfrom=LHCPhysics.LHCHXSWGHH#Latest_recommendations_for_gluon

double func_central_cross_section(double *par_x,double *par);
double func_upper_uncertainty(double *par_x,double *par);
double func_lower_uncertainty(double *par_x,double *par);

double rel_effect_up_times_100(double *par_x,double *par);
double rel_effect_down_times_100(double *par_x,double *par);

void Th_Sys_cross_section_QCD_gg_HH()
{
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetOptStat(1111111); //ourmen overflow, underflow, rms, mean, entries, name
  gStyle->SetOptTitle(0); // do not put the histo name

  TLatex t;
  t.SetNDC();
  t.SetTextSize(0.05);

  TH1F *hist_frame;
  //-------------------------------------------------------------------------------------------------
  TCanvas *canvas_cross_sections=new TCanvas("canvas_cross_sections","canvas_cross_sections",800,600);
  canvas_cross_sections->SetRightMargin(0.03);
  canvas_cross_sections->SetTopMargin(0.01);
  //canvas_cross_sections->SetTopMargin(0.03);

  TF1 f1_central_cross_section("f1_central_cross_section",func_central_cross_section,-10,10,0); //in fb
  f1_central_cross_section.SetLineColor(kBlack);

  TF1 f1_upper_unc_first("f1_upper_unc_first",func_upper_uncertainty,-10,10,0);
  f1_upper_unc_first.SetLineColor(kRed);

  TF1 f1_lower_unc_first("lower_unc_first",func_lower_uncertainty,-10,10,0);
  f1_lower_unc_first.SetLineColor(kBlue+2);

  hist_frame=canvas_cross_sections->DrawFrame(-10,10,10,2000);
  hist_frame->GetXaxis()->SetTitle("#kappa_{#lambda}");
  hist_frame->GetYaxis()->SetTitle("#sigma(gg HH) [fb]");
  hist_frame->Draw();

  f1_central_cross_section.Draw("same");
  f1_upper_unc_first.Draw("same");
  f1_lower_unc_first.Draw("same");
  
  t.SetTextColor(kRed);
  t.DrawLatex(0.45,0.85,"upper cross-section");
  t.SetTextColor(kBlack);
  t.DrawLatex(0.45,0.80,"central cross-section");
  t.SetTextColor(kBlue+2);
  t.DrawLatex(0.45,0.75,"lower cross-section");
  
  canvas_cross_sections->SetLogy();
  
  canvas_cross_sections->SaveAs("figures/Th_Cross_section_gg_HH_with_QCD_uncertainty.png");

  delete hist_frame;
  //-------------------------------------------------------------------------------------------------
  TCanvas *canvas=new TCanvas("canvas","canvas",800,600);
  canvas->SetRightMargin(0.03);
  canvas->SetTopMargin(0.03);

  TF1 f1_rel_effect_up_times_100("f1_rel_effect_up_times_100",rel_effect_up_times_100,-10,10,0); //in fb
  f1_rel_effect_up_times_100.SetLineColor(kRed);

  TF1 f1_rel_effect_down_times_100("f1_rel_effect_down_times_100",rel_effect_down_times_100,-10,10,0); //in fb
  f1_rel_effect_down_times_100.SetLineColor(kBlue+2);

  hist_frame=canvas->DrawFrame(-10,-10,10,10);
  hist_frame->GetXaxis()->SetTitle("#kappa_{#lambda}");
  hist_frame->GetYaxis()->SetTitle("100#times ([#sigma^{syst}(gg HH)-#sigma^{central}(gg HH)]-1)");
  hist_frame->Draw();
  f1_rel_effect_up_times_100.Draw("same");
  f1_rel_effect_down_times_100.Draw("same");
  
  t.SetTextColor(kRed);
  t.DrawLatex(0.45,0.85,"upper uncertainty");
  t.SetTextColor(kBlue+2);
  t.DrawLatex(0.45,0.80,"lower uncertainty");

  canvas->RedrawAxis();
  
  canvas->SaveAs("figures/Th_Sys_QCD_cross_section_gg_HH.png");
  //-------------------------------------------------------------------------------------------------
  //Search for extremal values

  double max_uncertainty_up=0;
  double max_uncertainty_down=0;

  for (double kappa_lambda=-10;kappa_lambda<=10;kappa_lambda+=0.01) {
    if (f1_rel_effect_up_times_100.Eval(kappa_lambda)>max_uncertainty_up)
      max_uncertainty_up=f1_rel_effect_up_times_100.Eval(kappa_lambda);
    
    if (fabs(f1_rel_effect_down_times_100.Eval(kappa_lambda))>max_uncertainty_down)
      max_uncertainty_down=f1_rel_effect_down_times_100.Eval(kappa_lambda);
  }

  double uncertainty_up_SM=f1_rel_effect_up_times_100.Eval(1);
  double uncertainty_down_SM=f1_rel_effect_down_times_100.Eval(1);

  cout << "max over kappa lambda : uncertainty (%) : " << max_uncertainty_up << " " << max_uncertainty_down << endl;
  cout << "SM : uncertainty (%) : " << uncertainty_up_SM << " " << uncertainty_down_SM << endl;
}

double func_central_cross_section(double *par_x,double *par) //in fb
{  
  double x=par_x[0];
  
  return 70.3874-50.4111*x+11.0595*x*x;
}

double func_upper_uncertainty(double *par_x,double *par) //in fb
{  
  double x=par_x[0];
  
  double value_first=72.0744-51.7362*x+11.3712*x*x;
  double value_second=70.9286-51.5708*x+11.4497*x*x;
  
  //take the max

  if (value_first>value_second)
    return value_first;
  else
    return value_second;
}


double func_lower_uncertainty(double *par_x,double *par) //in fb
{  
  double x=par_x[0];
  
  double value_first=66.0621-46.7458*x+10.1673*x*x;
  double value_second=66.7581-47.721*x+10.4535*x*x;

  //take the min
  
  if (value_first<value_second)
    return value_first;
  else
    return value_second;
}

double rel_effect_up_times_100(double *par_x,double *par)
{
  double x=par_x[0];
  
  return 100.*((func_upper_uncertainty(par_x,par)/func_central_cross_section(par_x,par))-1);
}

double rel_effect_down_times_100(double *par_x,double *par)
{
  double x=par_x[0];
  
  return 100.*((func_lower_uncertainty(par_x,par)/func_central_cross_section(par_x,par))-1);
}
