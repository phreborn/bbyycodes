#ifndef TOOL_HELPER_H
#define TOOL_HELPER_H

//#######################################################################################################################################################################################################
string Return_string_latex_sample(string string_sample)
{   
  string string_latex_sample;
  
  if (string_sample.find("gg_HH_non_resonant_kappa_lambda_01")!=string::npos
      ||
      string_sample.find("PowhegH7_HHbbyy_cHHH01d0")!=string::npos
      ||
      string_sample.find("aMCnloHwpp_hh_yybb")!=string::npos
      )
    string_latex_sample="non resonant gg HH (SM)";
  else if (string_sample.find("gg_HH_non_resonant_kappa_lambda_10")!=string::npos
	   ||
	   string_sample.find("PowhegH7_HHbbyy_cHHH10d0")!=string::npos
	   )
    string_latex_sample="non resonant gg HH $\\kappa_{\\lambda}=10$ signal";
  else if (string_sample.find("vbf_HH_non_resonant_kappa_lambda_01")!=string::npos
	   ||
	   string_sample.find("MGH7_hh_bbyy_vbf_l1cvv1cv1")!=string::npos
	   )
    string_latex_sample="non resonant VBF HH (SM)";
  
  else if (string_sample.find("HHbbyy_reweight_mHH")!=string::npos)
    string_latex_sample=string_sample;

  else if (string_sample.find("NonResonantPlusSingle")!=string::npos)
    string_latex_sample="SM HH signal + Single-H bkg";

  else if (string_sample.find("SingleHiggs")!=string::npos)
    string_latex_sample="Single-H bkg";
  
  else if (string_sample.find("PowhegPy8_NNLOPS_ggH125")!=string::npos
	   ||
	   string_sample.find("ggH125")!=string::npos)
    string_latex_sample="ggH125";
  else if (string_sample.find("PowhegPy8_ZH125J")!=string::npos)
    string_latex_sample="ZH125J";
  else if (string_sample.find("ZH125")!=string::npos)
    string_latex_sample="ZH125";
  //shit  else if (string_sample.find("PowhegPy8_ttH125")!=string::npos)
  else if (string_sample.find("ttH125")!=string::npos)
    string_latex_sample="ttH125";
  

  else if (string_sample.find("MGH7_X251tohh_bbyy")!=string::npos)
    string_latex_sample="X251";
  else if (string_sample.find("MGH7_X260tohh_bbyy")!=string::npos)
    string_latex_sample="X260";
  else if (string_sample.find("MGH7_X280tohh_bbyy")!=string::npos)
    string_latex_sample="X280";
  else if (string_sample.find("MGH7_X300tohh_bbyy")!=string::npos)
    string_latex_sample="X300";
  else if (string_sample.find("MGH7_X325tohh_bbyy")!=string::npos)
    string_latex_sample="X325";
  else if (string_sample.find("MGH7_X350tohh_bbyy")!=string::npos)
    string_latex_sample="X350";
  else if (string_sample.find("MGH7_X400tohh_bbyy")!=string::npos)
    string_latex_sample="X400";
  else if (string_sample.find("MGH7_X450tohh_bbyy")!=string::npos)
    string_latex_sample="X450";
  else if (string_sample.find("MGH7_X450tohh_bbyy")!=string::npos)
    string_latex_sample="X450";
  else if (string_sample.find("MGH7_X500tohh_bbyy")!=string::npos)
    string_latex_sample="X500";
  else if (string_sample.find("MGH7_X550tohh_bbyy")!=string::npos)
    string_latex_sample="X550";
  else if (string_sample.find("MGH7_X600tohh_bbyy")!=string::npos)
    string_latex_sample="X600";
  else if (string_sample.find("MGH7_X700tohh_bbyy")!=string::npos)
    string_latex_sample="X700";
  else if (string_sample.find("MGH7_X800tohh_bbyy")!=string::npos)
    string_latex_sample="X800";
  else if (string_sample.find("MGH7_X900tohh_bbyy")!=string::npos)
    string_latex_sample="X900";
  else if (string_sample.find("MGH7_X1000tohh_bbyy")!=string::npos)
    string_latex_sample="X1000";
  else if (string_sample.find("MGH7_X2000tohh_bbyy")!=string::npos)
    string_latex_sample="X2000";
  else if (string_sample.find("MGH7_X3000tohh_bbyy")!=string::npos)
    string_latex_sample="X3000";
  
  else {
    cout << "to implement functionality" << endl;
    exit(1);
  }
  
  return string_latex_sample;
}
//#######################################################################################################################################################################################################
void PrintHeaderTableSyst(string string_sample,FILE *fp,string string_yield_shape)
{
  fprintf(fp,"\\newcolumntype{C}{>{\\centering\\arraybackslash}p{2cm}}\n");
  
  fprintf(fp,"\\begin{table}[h!]\n");
  fprintf(fp,"\\begin{center}\n");
  //  fprintf(fp,"\\small\n");
  //  fprintf(fp,"\\footnotesize\n");
  fprintf(fp,"\\scriptsize\n");
  //fprintf(fp,"\\tiny\n");
  
  fprintf(fp,"\\begin{tabular}{|l|l|");
  
  for (int index_process=0;index_process<nb_processes;index_process++) {
    if (string_yield_shape=="yield") {
      
      fprintf(fp,"c|");
    }
    else if (string_yield_shape=="shape") {
      fprintf(fp,"C|"); //mu
      fprintf(fp,"C|"); //sigma
    }
  }
  
  fprintf(fp,"}\n");
  
  fprintf(fp,"\\hline\n");
  
  //to generalize ?

  if (string_yield_shape=="yield")
    fprintf(fp,"\\multicolumn{2}{|l|}{Source of systematic uncertainty}   &\\multicolumn{%d}{c|}{\\%% effect wrt nominal}\\\\\n",nb_processes);
    //    fprintf(fp,"\\multicolumn{2}{|l|}{Source of systematic uncertainty}   &\\multicolumn{%d}{c|}{\\%% effect relative to nominal in the category}\\\\\n",nb_processes);
  else if (string_yield_shape=="shape")
    fprintf(fp,"\\multicolumn{2}{|l|}{Source of systematic uncertainty}    &\\multicolumn{%d}{c|}{\\%% effect wrt nominal}\\\\\n",nb_processes*2); //2 : mu and sigma
    //    fprintf(fp,"\\multicolumn{2}{|l|}{Source of systematic uncertainty}    &\\multicolumn{%d}{c|}{\\%% effect relative to nominal in the category}\\\\\n",nb_processes*2); //2 : mu and sigma
  
  //keep this
  fprintf(fp,"\\multicolumn{2}{|l|}{                                }");

  //no more several processes : remove the loop

  for (int index_process=0;index_process<nb_processes;index_process++) {
    fprintf(fp,"   &");
    
    if (string_yield_shape=="shape")
      fprintf(fp,"\\multicolumn{2}{c|}{");
    
    cout << "in PrintHeader" << endl;
    cout << "index_process=" << index_process << endl;

    //to improve : make a function that return the human reading name

    string string_latex_sample=Return_string_latex_sample(string_sample);
    fprintf(fp,"%s",string_latex_sample.c_str());

    if (string_yield_shape=="shape")
      fprintf(fp,"}");
  } //end loop on processes
  
  fprintf(fp,"\\\\\n");

  //additional splitting into position and shape
  if (string_yield_shape=="shape") {
  
    fprintf(fp,"\\multicolumn{2}{|l|}{                                }");
    
    for (int index_process=0;index_process<nb_processes;index_process++) {
      
      //to develop in such a way to detect if several b-categories are made
      fprintf(fp," &$\\mu$");
      fprintf(fp,"   &$\\sigma$");

    } //end loop on process
    fprintf(fp,"\\\\\n");
  } //end mode shape
  
  fprintf(fp,"\\hline\n");
  
  return;
}
//#######################################################################################################################################################################################################
//#######################################################################################################################################################################################################
//#######################################################################################################################################################################################################
string Return_object_given_systematic(string string_systematic)
{
  //  cout << "in Return_object_given_systematic" << endl;
  string string_object;

  if (
      string_systematic.find("muR")!=string::npos
      ||
      string_systematic.find("renscfact")!=string::npos
      ||
      string_systematic.find("facscfact")!=string::npos
      ||
      string_systematic.find("lhapdf")!=string::npos
      ||
      string_systematic.find("pdf_set")!=string::npos
      ||
      string_systematic.find("QCD")!=string::npos
      ||
      string_systematic.find("PDF_alpha_s")!=string::npos
      ) {
    string_object="theory";
  }
  else if (string_systematic=="PRW_DATASF" || string_systematic=="PH_EFF_TRIGGER_Uncertainty")
    string_object="event_based";
  else if (string_systematic.find("PH_EFF_")!=string::npos
	   ||
	   string_systematic.find("EG_SCALE_")!=string::npos
	   ||
	   string_systematic.find("EG_RESOLUTION_")!=string::npos
	   ||
	   string_systematic.find("PH_SCALE_")!=string::npos
	   )
    string_object="photon";
  else if (string_systematic.find("JET_")!=string::npos)
    string_object="jet";
  else if (string_systematic.find("FT_EFF")!=string::npos)
    string_object="flavor_tagging";
  else if (string_systematic.find("EL_EFF")!=string::npos
	   ||
	   string_systematic.find("MUON_SCALE")!=string::npos
	   ||
	   string_systematic.find("MUON_EFF")!=string::npos
	   ||
	   string_systematic.find("MUON_ID")!=string::npos
	   ||
	   string_systematic.find("MUON_MS")!=string::npos
	   ||
	   string_systematic.find("MUON_SAGITTA")!=string::npos

	   ||
	   string_systematic.find("TAUS_TRUE")!=string::npos
	   ||
	   string_systematic.find("MET_Soft")!=string::npos
	   )
    string_object="LEPTON_MET";
  else {
    cout << "string_object=" << string_object << endl;
    cout << "problem, systematic not taken into account : " << string_systematic << endl;
    cout << "halt program" << endl;
    exit(1);
  }
  
  return string_object;
}
//#######################################################################################################################################################################################################
string ReturnMxAODSyst_directory(string string_systematic)
{
  cout << "start ReturnMxAODSyst_directory" << endl;
  string string_directory;
  
  if (string_systematic=="PRW_DATASF")
    string_directory="PhotonSys";
  else if (string_systematic.find("PH_EFF_")!=string::npos)
    string_directory="PhotonSys";
  else if (string_systematic.find("EG_SCALE_ALL")!=string::npos)
    string_directory="PhotonSys";
  else if (string_systematic.find("EG_SCALE_AF2")!=string::npos) {
    if (do_EGamma_1NP)
      string_directory="PhotonSys";
    else
      string_directory="PhotonAllSys";
  }
  else if (string_systematic.find("PH_SCALE")!=string::npos)
    string_directory="PhotonAllSys";
  else if (string_systematic.find("EG_SCALE")!=string::npos)
    string_directory="PhotonAllSys";
  else if (string_systematic.find("EG_RESOLUTION_ALL")!=string::npos)
    string_directory="PhotonSys";
  else if (string_systematic.find("EG_RESOLUTION_AF2")!=string::npos) {
    string_directory="PhotonAllSys";
  }
  else if (string_systematic.find("EG_RESOLUTION_")!=string::npos) //order is important : do not put before
    string_directory="PhotonAllSys";

  //To revisit for each MxAOD h... production, since the potential number of files could vary, thus the merging would be different (for GetListOfSubprocessesToMerge)
  //https://gitlab.cern.ch/atlas-hgam-sw/HGamCore/-/blob/master/HGamTools/data/MxAODJetSys1.config

  else if (string_systematic.find("MCsmear")!=string::npos)
    string_directory="JetSys3";
  else if (string_systematic.find("PDsmear")!=string::npos)
    string_directory="JetSys4";
  else if (string_systematic.find("JET_EffectiveNP")!=string::npos)
    string_directory="JetSys1";
  else if (string_systematic.find("JET_")!=string::npos)
    string_directory="JetSys2";

  //  else if (string_systematic.find("JET_")!=string::npos)
  //    string_directory="JetSys";

  else if (string_systematic.find("FT_EFF")!=string::npos)
    string_directory="FlavorSys";
  else if (
	   string_systematic.find("EL_EFF")!=string::npos
	   ||
	   string_systematic.find("MUON")!=string::npos
	   ||
	   string_systematic.find("TAUS")!=string::npos
	   ||
	   string_systematic.find("MET")!=string::npos
	   )
    string_directory="LeptonMETSys";
  else if (
      string_systematic.find("muR")!=string::npos
      ||
      string_systematic.find("renscfact")!=string::npos
      ||
      string_systematic.find("facscfact")!=string::npos
      ||
      string_systematic.find("lhapdf")!=string::npos
      ||
      string_systematic.find("pdf_set")!=string::npos
      ) {
    string_directory="Theory";
  }
  else {
    cout << "problem in ReturnMxAODSyst_directory, systematic not taken into account : " << string_systematic << endl;
    cout << "halt program" << endl;
    exit(1);
  }
  

  cout << "string_systematic=" << string_systematic << ", string_directory=" << string_directory << endl;
  return string_directory;
}
//#######################################################################################################################################################################################################
string Return_name_for_syst(string string_systematic)
{
  string name_for_syst=string_systematic;
  
  if (string_systematic=="muR=0.5_muF=0.5")
    name_for_syst="#mu_{R}=0.5, #mu_{F}=0.5";
  else if (string_systematic=="muR=0.5_muF=1.0")
    name_for_syst="#mu_{R}=0.5, #mu_{F}=1.0";
  else if (string_systematic=="muR=1.0_muF=0.5")
    name_for_syst="#mu_{R}=1.0, #mu_{F}=0.5";
  else if (string_systematic=="muR=1.0_muF=2.0")
    name_for_syst="#mu_{R}=1.0, #mu_{F}=2.0";
  else if (string_systematic=="muR=2.0_muF=1.0")
    name_for_syst="#mu_{R}=2.0, #mu_{F}=1.0";
  else if (string_systematic=="muR=2.0_muF=2.0")
    name_for_syst="#mu_{R}=2.0, #mu_{F}=2.0";
  else if (string_systematic=="PDF_alpha_s")
    name_for_syst="PDF+#alpha_{s}";

  return name_for_syst;
}
//###################################################################################################
double ReturnRoundedExtremal(double value,string string_min_max)
{
  //code checked : correct treatment

  double rounded=value;
  
  int nb_multiplication_by_10=0;

  while ((int)rounded==0 && nb_multiplication_by_10<10) {
    rounded*=10;
    nb_multiplication_by_10++;
  }
    
  rounded=(int)rounded;

  if (nb_multiplication_by_10<10) {
    if (string_min_max=="max")
      rounded++; //increment of 1
    else if (string_min_max=="min")
      rounded--; //increment of 1
    
    rounded/=pow(10,nb_multiplication_by_10);
  }
  
  return rounded;
}
//###################################################################################################
string get_string_ECM_luminosity(string string_campaign_MxAOD)
{
  if (string_campaign_MxAOD=="h026_mc16a")
    return "#sqrt{s}=13 TeV, #int L dt=36.2 fb^{-1}";
  else if (string_campaign_MxAOD=="h026_mc16d")
    return "#sqrt{s}=13 TeV, #int L dt=44.4 fb^{-1}";
  else if (string_campaign_MxAOD=="h026_mc16e")
    return "#sqrt{s}=13 TeV, #int L dt=58.5 fb^{-1}";
  else if (string_campaign_MxAOD=="h026_mc16d_h026_mc16d")
    return "#sqrt{s}=13 TeV, #int L dt=80.6 fb^{-1}";
  else if (string_campaign_MxAOD=="h026_mc16a_h026_mc16e")
    return "#sqrt{s}=13 TeV, #int L dt=94.7 fb^{-1}";
  else if (string_campaign_MxAOD=="h026_mc16a_h026_mc16d_h026_mc16e")
    return "#sqrt{s}=13 TeV, #int L dt=139.0 fb^{-1}";
  else {
    cout << "case not anticipated, halt program" << endl;
    exit(1);
  }

  /*
  if (string_campaign_MxAOD=="h025_mc16a")
    return "#sqrt{s}=13 TeV, #int L dt=36.2 fb^{-1}";
  else if (string_campaign_MxAOD=="h025_mc16d")
    return "#sqrt{s}=13 TeV, #int L dt=44.4 fb^{-1}";
  else if (string_campaign_MxAOD=="h025_mc16e")
    return "#sqrt{s}=13 TeV, #int L dt=58.5 fb^{-1}";
  else if (string_campaign_MxAOD=="h025_mc16d_h025_mc16d")
    return "#sqrt{s}=13 TeV, #int L dt=80.6 fb^{-1}";
  else if (string_campaign_MxAOD=="h025_mc16a_h025_mc16e")
    return "#sqrt{s}=13 TeV, #int L dt=94.7 fb^{-1}";
  else if (string_campaign_MxAOD=="h025_mc16a_h025_mc16d_h025_mc16e")
    return "#sqrt{s}=13 TeV, #int L dt=139.0 fb^{-1}";
  else {
    cout << "case not anticipated, halt program" << endl;
    exit(1);
  }
  */

  //  float lumi_mc16a=36.20904;
  //  float lumi_mc16d=44.3857;
  //  float lumi_mc16e=58.4501;
  return "";
}
 
#endif
