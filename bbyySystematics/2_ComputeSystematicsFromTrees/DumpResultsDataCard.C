//CODE USED ONLY FOR INDEPENDENT PROGRAM !!

string string_sample="gg_HH_resonant"; //gg_HH_non_resonant, vbf_HH_non_resonant, ggH_in_HH_resonant, ZH_in_HH_resonant, ttH_in_HH_resonant, gg_HH_non_resonnat_in_HH_resonant, vbf_HH_non_resonant_in_HH_resonant, gg_HH_resonant

//used in the part dedicated to computing the max over systematics, in order to dump the Table of max over systematics

#include "tool_Return_subthematic_given_systematic.C"

void PrintHeaderTableSyst(FILE *fp,string string_yield_shape);
void PrintTableSystematics_subthematic(FILE *fp_results_sys_subthematic,string string_yield_shape);
void PrintRepresentativeSystematic(FILE *fp_table,
				   double rel_effect_up,
				   double rel_effect_down,
				   double rel_effect_sym);

string string_type="experimental"; //theory, experimental

vector<string> vec_string_systematic_subthematic; //filled automatically in program

//to make a vector and loop ?

string string_yield_shape="shape"; //yield, shape

class subthematic_results
{
 public:
  //all effects are expressed in percent
  
  double rel_effect_up;
  double rel_effect_down;
  double rel_effect_sym;
};

map<string,map<string,subthematic_results>> map_config_results_f_subthematic_f_modified_parameter;

vector<string> vec_modified_parameter;

vector<string> vec_string_category;

int DumpResultsDataCard()
{
  //-----------------
  if (string_sample=="gg_HH_resonant"
      ||
      string_sample=="gg_HH_non_resonant_in_HH_resonant"
      ||
      string_sample=="vbf_HH_non_resonant_in_HH_resonant"
      ||
      string_sample=="ggH_in_HH_resonant"
      ||
      string_sample=="ZH_in_HH_resonant"
      ||
      string_sample=="ttH_in_HH_resonant"
      ) {
    vec_string_category.push_back("Resonant");
  }
  else {
    vec_string_category.push_back("XGBoost_btag77_withTop_BCal_tightScore_HMass");
    vec_string_category.push_back("XGBoost_btag77_withTop_BCal_looseScore_HMass");
    
    vec_string_category.push_back("XGBoost_btag77_withTop_BCal_tightScore_LMass");
    vec_string_category.push_back("XGBoost_btag77_withTop_BCal_looseScore_LMass");
    
  }
  
  if (string_type=="experimental") {
    vec_string_systematic_subthematic.push_back("PRW");
    vec_string_systematic_subthematic.push_back("Trigger");
    vec_string_systematic_subthematic.push_back("PH_PES");
    vec_string_systematic_subthematic.push_back("PH_PER");
    vec_string_systematic_subthematic.push_back("PH_EFF_ID");
    vec_string_systematic_subthematic.push_back("PH_EFF_Isol");
    vec_string_systematic_subthematic.push_back("JET_JES");
    vec_string_systematic_subthematic.push_back("JET_JER");
    vec_string_systematic_subthematic.push_back("FT_EFF_B");
    vec_string_systematic_subthematic.push_back("FT_EFF_C");
    vec_string_systematic_subthematic.push_back("FT_EFF_Light");
  }
  else if (string_type=="theory") {
    vec_string_systematic_subthematic.push_back("QCD");
    vec_string_systematic_subthematic.push_back("PDF_alpha_s");
  }
  
  ifstream stream_syst_datacard_yield;
  ifstream stream_syst_datacard_position_shape;
  ifstream stream_syst_datacard_spread_shape;

  string string_path="results/datacards/details/";

  if (string_yield_shape=="yield")
    vec_modified_parameter.push_back("yield");
  else if (string_yield_shape=="shape") {
    vec_modified_parameter.push_back("position_shape");
    vec_modified_parameter.push_back("spread_shape");
  }
  

  cout << "string_yield_shape=" << string_yield_shape << endl;

  for (int index_category=0;index_category<vec_string_category.size();index_category++) {
    string string_category=vec_string_category[index_category];
    for (int i=0;i<10;i++)
      cout << "=======================================================================" << endl;
    cout << "consider " << string_category << endl;

    //----------------------------
    //initialize to 0

    for (int index_systematic_subthematic=0;index_systematic_subthematic<(int)vec_string_systematic_subthematic.size();index_systematic_subthematic++) {
      string string_systematic_subthematic=vec_string_systematic_subthematic[index_systematic_subthematic];
      
      for (int index_modified_parameter=0;index_modified_parameter<vec_modified_parameter.size();index_modified_parameter++) {
	string string_modified_parameter=vec_modified_parameter[index_modified_parameter];

	map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].rel_effect_up=0;
	map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].rel_effect_down=0;
      }
    }
    //----------------------------    
    string string_datacard_yield;
    string string_datacard_position_shape;
    string string_datacard_spread_shape;

    string string_process; //could be slightly different to string_sample

    if (string_sample=="gg_HH_non_resonant") {

      string_process="gg_HH_non_resonant";

      /*
shit
      string_datacard_yield="datacard_experimental_yield_proc_";
      string_datacard_yield+=string_process;
      string_datacard_yield+="_Max_cat_";
      string_datacard_yield+=string_category;
      string_datacard_yield+=".txt";

      string_datacard_position_shape="datacard_experimental_position_shape_m_yy_proc_";
      string_datacard_position_shape+=string_process;
      string_datacard_position_shape+="_Max_cat_";
      string_datacard_position_shape+=string_category;
      string_datacard_position_shape+=".txt";

      string_datacard_spread_shape="datacard_experimental_spread_shape_m_yy_proc_";
      string_datacard_spread_shape+=string_process;
      string_datacard_spread_shape+="_Max_cat_";
      string_datacard_spread_shape+=string_category;
      string_datacard_spread_shape+=".txt";
      */
    }

    else if (string_sample=="gg_HH_resonant") {

      string_process="gg_HH_resonant";
      /*
shit
      string_datacard_yield="datacard_experimental_yield_proc_";
      string_datacard_yield+=string_process;
      string_datacard_yield+="_Max_cat_";
      string_datacard_yield+=string_category;
      string_datacard_yield+=".txt";

      string_datacard_position_shape="datacard_experimental_position_shape_m_yy_proc_";
      string_datacard_position_shape+=string_process;
      string_datacard_position_shape+="_Max_cat_";
      string_datacard_position_shape+=string_category;
      string_datacard_position_shape+=".txt";

      string_datacard_spread_shape="datacard_experimental_spread_shape_m_yy_proc_";
      string_datacard_spread_shape+=string_process;
      string_datacard_spread_shape+="_Max_cat_";
      string_datacard_spread_shape+=string_category;
      string_datacard_spread_shape+=".txt";
      */
    }

    else if (string_sample=="gg_HH_non_resonant_in_HH_resonant")
      string_process="gg_HH_non_resonant";
    else if (string_sample=="vbf_HH_non_resonant_in_HH_resonant")
      string_process="vbf_HH_non_resonant";

    else if (string_sample=="ggH_in_HH_resonant")
      string_process="ggH";
    else if (string_sample=="ZH_in_HH_resonant")
      string_process="ZH";
    else if (string_sample=="ttH_in_HH_resonant")
      string_process="ttH";
    
    string_datacard_yield="datacard_";
    string_datacard_yield+=string_type;
    string_datacard_yield+="_yield_proc_";
    
    string_datacard_yield+=string_process;
    string_datacard_yield+="_Max_cat_";
    string_datacard_yield+=string_category;
    string_datacard_yield+=".txt";
    
    string_datacard_position_shape="datacard_";
    string_datacard_position_shape+=string_type;
    string_datacard_position_shape+="_position_shape_m_yy_proc_";
    string_datacard_position_shape+=string_process;
    string_datacard_position_shape+="_Max_cat_";
    string_datacard_position_shape+=string_category;
    string_datacard_position_shape+=".txt";

    string_datacard_spread_shape="datacard_";
    string_datacard_spread_shape+=string_type;
    string_datacard_spread_shape+="_spread_shape_m_yy_proc_";
    string_datacard_spread_shape+=string_process;
    string_datacard_spread_shape+="_Max_cat_";
    string_datacard_spread_shape+=string_category;
    string_datacard_spread_shape+=".txt";
    
    cout << "will now loop on modifiers" << endl;

    for (int index_modified_parameter=0;index_modified_parameter<vec_modified_parameter.size();index_modified_parameter++) {
      
      string string_modified_parameter=vec_modified_parameter[index_modified_parameter];
      
      cout << "string_modified_parameter=" << string_modified_parameter << endl;

      if (string_modified_parameter=="yield") {
	stream_syst_datacard_yield.open(string_path+string_datacard_yield);
	cout << "will consider string_datacard_yield=" << string_datacard_yield << endl;
      }
      else if (string_modified_parameter=="position_shape") {
	stream_syst_datacard_position_shape.open(string_path+string_datacard_position_shape);
	cout << "will consider string_datacard_position_shape=" << string_datacard_position_shape << endl;
      }
      else if (string_modified_parameter=="spread_shape") {
	stream_syst_datacard_spread_shape.open(string_path+string_datacard_spread_shape);
	cout << "will consider string_datacard_spread_shape=" << string_datacard_spread_shape << endl;
      }
      
      string string_systematic;
      double rel_effect_up;
      double rel_effect_down;
      double rel_effect_sym;
      
      bool err_code=1;
      
      while (err_code) { // for all systematics
	if (string_modified_parameter=="yield")
	  err_code=(stream_syst_datacard_yield >> string_systematic);
	else if (string_modified_parameter=="position_shape")
	  err_code=(stream_syst_datacard_position_shape >> string_systematic);
	else if (string_modified_parameter=="spread_shape")
	  err_code=(stream_syst_datacard_spread_shape >> string_systematic);
	
	cout << "err_code=" << err_code << endl;
	if (!err_code)
	  break;
	
	if (string_modified_parameter=="yield") {
	  if (string_type=="theory") {
	    stream_syst_datacard_yield >> rel_effect_sym;
	  }
	  else {
	    stream_syst_datacard_yield >> rel_effect_up;
	    stream_syst_datacard_yield >> rel_effect_down;
	  }
	}
	else if (string_modified_parameter=="position_shape") {
	  if (string_type=="theory") {
	    stream_syst_datacard_position_shape >> rel_effect_sym;
	  }
	  else {
	    stream_syst_datacard_position_shape >> rel_effect_up;
	    stream_syst_datacard_position_shape >> rel_effect_down;
	  }
	}
	else if (string_modified_parameter=="spread_shape") {
	  if (string_type=="theory") {
	    stream_syst_datacard_spread_shape >> rel_effect_sym;
	  }
	  else {
	    stream_syst_datacard_spread_shape >> rel_effect_up;
	    stream_syst_datacard_spread_shape >> rel_effect_down;
	  }
	}
	
	if (string_type=="theory") {
	  rel_effect_up=rel_effect_sym;
	  rel_effect_down=rel_effect_sym;
	}
	
	cout << "-----" << endl;
	cout << "string_systematic=" << string_systematic << ", rel_effect_up=" << rel_effect_up << ", rel_effect_down=" << rel_effect_down << endl;
	string string_systematic_subthematic=Return_subthematic_given_systematic(string_systematic);
	
	cout << "string_systematic_subthematic=" << string_systematic_subthematic << endl;
	
	map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].rel_effect_up+=0.5*pow(rel_effect_up,2);
	map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].rel_effect_up+=0.5*pow(rel_effect_down,2);
	
	//      cout << "so far, map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].rel_effect_up=" << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].rel_effect_up << endl;
	
	map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].rel_effect_down+=0.5*pow(rel_effect_up,2);
	map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].rel_effect_down+=0.5*pow(rel_effect_down,2);
      } //end read results of raw systematics
      //-----------------------------
      //finalize the merging of systematic per thematic : add the sqrt
      
      for (int index_systematic_subthematic=0;index_systematic_subthematic<(int)vec_string_systematic_subthematic.size();index_systematic_subthematic++) {
	string string_systematic_subthematic=vec_string_systematic_subthematic[index_systematic_subthematic];
	
	map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].rel_effect_up=sqrt(map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].rel_effect_up);
	map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].rel_effect_down=sqrt(map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].rel_effect_down);
	
	cout << "string_systematic_subthematic=" << string_systematic_subthematic << ", rel_effect_up=" << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].rel_effect_up << ", rel_effect_down=" << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].rel_effect_down << endl;
      } //end loop on systematic thematic


      if (string_modified_parameter=="yield")
	stream_syst_datacard_yield.close();
      else if (string_modified_parameter=="position_shape")
	stream_syst_datacard_position_shape.close();
      else if (string_modified_parameter=="spread_shape")
	stream_syst_datacard_spread_shape.close();
      
    } //end loop on modified parameter
    
    //======================================================================
    cout << "====================" << endl;
    cout << "NOW DUMP RESULTS" << endl;

    string string_latex_table="results/results_rel_effect_"+string_type+"_"+string_yield_shape;
    if (string_yield_shape=="shape")
      string_latex_table+="_m_yy";
    string_latex_table+="_systematics_thematic_proc_";
    string_latex_table+=string_process;
    string_latex_table+="_max_";
    string_latex_table+="cat_";
    string_latex_table+=string_category;
    string_latex_table+=".txt";

    FILE *fp=fopen(string_latex_table.c_str(),"wt");
    
    //FILE *fp=fopen((string("results/results_rel_effect_"+string_type+"_"+string_yield_shape+
    
    //Table_")+string_category+".tex").c_str(),"wt");
    
    PrintHeaderTableSyst(fp,string_yield_shape);
    PrintTableSystematics_subthematic(fp,string_yield_shape);
    //======================================================================
  } //end loop on category

  vec_modified_parameter.clear();

  cout << "end of program" << endl;
  
  return 0;
}
//#######################################################################################################################################################################################################
void PrintHeaderTableSyst(FILE *fp,string string_yield_shape)
{
  fprintf(fp,"\\newcolumntype{C}{>{\\centering\\arraybackslash}p{2cm}}\n");
  
  fprintf(fp,"\\begin{table}[h!]\n");
  fprintf(fp,"\\begin{center}\n");
  //  fprintf(fp,"\\small\n");
  //  fprintf(fp,"\\footnotesize\n");
  fprintf(fp,"\\scriptsize\n");
  //fprintf(fp,"\\tiny\n");
  
  fprintf(fp,"\\begin{tabular}{|l|l|");
  
  if (string_yield_shape=="yield")
    fprintf(fp,"c|");
  else if (string_yield_shape=="shape") {
    fprintf(fp,"C|"); //mu
    fprintf(fp,"C|"); //sigma
  }
  
  fprintf(fp,"}\n");
  
  fprintf(fp,"\\hline\n");
  
  if (string_yield_shape=="yield")
    fprintf(fp,"\\multicolumn{2}{|l|}{Source of systematic uncertainty}   &\\multicolumn{%d}{c|}{\\%% effect wrt nominal}\\\\\n",1);
    //    fprintf(fp,"\\multicolumn{2}{|l|}{Source of systematic uncertainty}   &\\multicolumn{%d}{c|}{\\%% effect relative to nominal in the category}\\\\\n",1);
  else if (string_yield_shape=="shape")
    fprintf(fp,"\\multicolumn{2}{|l|}{Source of systematic uncertainty}    &\\multicolumn{%d}{c|}{\\%% effect wrt nominal}\\\\\n",2); //2 : mu and sigma
    //  fprintf(fp,"\\multicolumn{2}{|l|}{Source of systematic uncertainty}    &\\multicolumn{%d}{c|}{\\%% effect relative to nominal in the category}\\\\\n",2); //2 : mu and sigma

  
  fprintf(fp,"\\multicolumn{2}{|l|}{                                }");
  
  fprintf(fp,"   &");
  
  if (string_yield_shape=="shape")
    fprintf(fp,"\\multicolumn{2}{c|}{");
  
  cout << "in PrintHeader" << endl;
  
  //to improve : make a function that return the human reading name
  
  fprintf(fp,"TheProcess");
  
  if (string_yield_shape=="shape")
    fprintf(fp,"}");
    
  fprintf(fp,"\\\\\n");
  
  //additional splitting into position and shape
  if (string_yield_shape=="shape") {
    
    fprintf(fp,"\\multicolumn{2}{|l|}{                                }");
    
    //to develop in such a way to detect if several b-categories are made
    fprintf(fp," &$\\mu$");
    fprintf(fp," &$\\sigma$");
    
    fprintf(fp,"\\\\\n");
  } //end mode shape
  
  fprintf(fp,"\\hline\n");
  
  return;
}
//#######################################################################################################################################################################################################
void PrintTableSystematics_subthematic(FILE *fp,string string_yield_shape)
{ 
  cout << "DumpResultsDataCard.C : PrintTableSystematics_subthematic" << endl;
  cout << "summary for subthematic " << endl;
  
  for (int index_systematic_subthematic=0;index_systematic_subthematic<(int)vec_string_systematic_subthematic.size();index_systematic_subthematic++) {
    
    string string_systematic_subthematic=vec_string_systematic_subthematic[index_systematic_subthematic];
    
    cout << "PrintTableSystematics_subthematic, index_systematic_subthematic=" << index_systematic_subthematic << ", string_systematic_subthematic=" << string_systematic_subthematic << endl;
    
    //first line of each block per object
    
    //restrict to first of each thematic
    //to improve concept of thematic : subthematic ?
    
    if (string_systematic_subthematic=="PRW" || string_systematic_subthematic=="PH_PES" || string_systematic_subthematic=="JET_JES" || string_systematic_subthematic=="FT_EFF_B" || string_systematic_subthematic=="EL_EFF" || string_systematic_subthematic=="QCD") { //only first element of various thematic
      
      cout << "add line" << endl;
      fprintf(fp,"\\hline\n");
      
      //algorith is not 100 % valid is one does not do a systematic belonging to the first subthematic
      //maybe to improve later in case one works with a subset of systematics, with a flag of subthematic started

      //hard-coded #lines for sure : does not depend on sources systematics but on number of destination systematics
      if (string_systematic_subthematic=="PRW")
	fprintf(fp,"\\multirow{2}{*}{Event-based}    ");
      else if (string_systematic_subthematic=="PH_PES")
	fprintf(fp,"\\multirow{4}{*}{Photon}         ");
      else if (string_systematic_subthematic=="JET_JES")
	fprintf(fp,"\\multirow{3}{*}{Jet}            ");
      else if (string_systematic_subthematic=="FT_EFF_B")
	fprintf(fp,"\\multirow{3}{*}{Flavour tagging}");
      else if (string_systematic_subthematic.find("EL_EFF")!=string::npos) {
	fprintf(fp,"\\multirow{5}{*}{Lepton+MET}");
	cout << "OK" << endl;
      }
      else if (string_systematic_subthematic=="QCD")
	fprintf(fp,"\\multirow{3}{*}{Theory}");
    }
    else
      fprintf(fp,"                                 ");
    
    fprintf(fp,"\\rule[-1.ex]{0pt}{3.5ex}"); //add a bit of vertical space so that the exposant and indice are not on the line ; skipped the \\strut command, because too separated
    
    fprintf(fp,"&");
    fprintf(fp,"\\verb|%s|\t",string_systematic_subthematic.c_str());
    
    fprintf(fp,"&");
    
    for (unsigned int index_modified_parameter=0;index_modified_parameter<vec_modified_parameter.size();index_modified_parameter++) {
      
      string string_modified_parameter=vec_modified_parameter[index_modified_parameter];
      
      PrintRepresentativeSystematic(fp,
				    map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].rel_effect_up,
				    map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].rel_effect_down,
				    map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].rel_effect_sym);
      
      if (string_modified_parameter=="position_shape")
	fprintf(fp," &");
    } //end loop on systematic thematic	
    
    fprintf(fp,"\t");
    
    fprintf(fp,"\\\\\n");
    //      fprintf(fp,"\\hline\n");
    
  } //end loop on subthematic
  
  fprintf(fp,"\\hline\n");
  fprintf(fp,"\\end{tabular}\n");
  fprintf(fp,"\\end{center}\n");
  fprintf(fp,"\\vspace{-0.5cm}\n");
  
  size_t start_pos = 0;
  string string_to_change="_";
  string string_changed="\\_";
  
  fprintf(fp,"\\caption{Summary of dominant systematic uncertainties affecting expected after the selection. Sources marked - are not significant.}\n");
  
  string string_label="\\label{table";
  string_label+="_systematics_thematic_";
  string_label+=string_yield_shape;
  string_label+="}\n";
  
  fprintf(fp,"%s",string_label.c_str());
  fprintf(fp,"\\end{table}\n");
  
  fclose(fp);
}
//#######################################################################################################################################################################################################
void PrintRepresentativeSystematic(FILE *fp_table,
				   double rel_effect_up,
				   double rel_effect_down,
				   double rel_effect_sym)
{
  bool do_symmetric_syst=1;
  
  if (fabs(rel_effect_up)<0.1 && fabs(rel_effect_down)<0.1) { //below 0.1 % effect: symmetrize it
    cout << "below 0.1 \% effect\n" << endl;
    fprintf(fp_table,"$<0.1$");
  }
  else { //above 0.1 % : consider it
    
    fprintf(fp_table,"$");
    
    if (do_symmetric_syst) {
      fprintf(fp_table,"\\pm %4.2f",sqrt(0.5*pow(rel_effect_up,2)+0.5*pow(rel_effect_down,2)));
    }
    else {
      fprintf(fp_table,"^{");
      if (rel_effect_up>=0)
	fprintf(fp_table,"+");
      
      //in case negative, it will print the sign automatically
      fprintf(fp_table,"%4.2f",rel_effect_up);
      
      fprintf(fp_table,"}");
      
      fprintf(fp_table,"_{");
      if (rel_effect_down>0)
	fprintf(fp_table,"+");
      
      //in case negative, it will print the sign automatically
      fprintf(fp_table,"%4.2f",rel_effect_down);
      
      fprintf(fp_table,"}");
    } //end show asymmetric

    fprintf(fp_table,"$");
  } //end case standard treatment
  
  return;
}
//#######################################################################################################################################################################################################
