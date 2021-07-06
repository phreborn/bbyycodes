//no need to make the search : access direct, in the spirit of yield ?

//use .x Systematics_Yield_Shape.C from the other main "caller" program (trick due to some interferences with the pdfs)
//=================================================================================
//string string_syst_yield_err="bootstrap"; //analytic, bootstrap
string string_syst_yield_err="analytic"; //analytic, bootstrap

//JBdV : MARC

void PrintTableSystematics_detail(string string_sample,FILE *fp_results_sys_details,string string_category,string string_yield_shape,string string_observable_shape,vector<string> vec_string_systematic_selected);
void PrintTableSystematics_subthematic(string string_sample,FILE *fp_results_sys_subthematic,string string_category,string string_yield_shape,string string_observable_shape);
//=================================================================================
//TO DO

//correlation_full1_partial2 : to make as a string : more intuitive

//to remove subprocesses
//a option in script to clean the bootstrap trees
//a option in script to clean the results toys

//to do : for bootstrap : to consider a seed different for mc16a, mc16d, mc16e, else, since the seed depends on eventNumber, the weight poisson could be the same : it could correlate a bit the results, but not sot much
//a priori, not useful, because already, the eventNumber are depending on the mc16a, mc16d, mc16e
//but it could have an effect when combining different subprocess of single Higgs, but not intrinsic problem because the intrinsic original weights are different

//to remove subloop

//1) to move PrintTable in tool_helper
//2) to try to factorize the two PrintTable if time available and if feasible
//PrintTable : to factorize details and subthematic

///REMOVE "ALL SYS" ?

//make only once the nominal (?) : could be very dangerous, because stat evolves with sample, etc.
//========================
//TO REPLACE ALL SYS BY EXPERIMENTAL ?

//quid showering ?

//FOR THEORETICAL : for datacard : put a suffix acceptance_ ?
//
//TO DO string_process : avoir the vector in order to have in the script ?
//in this case, no possibility of big table

//to search for "to do"
//if ok, to delete GetPtr
//=================================================================================
//to do : begin of finalize : make a loop of prun in order to simplify

//to do : map for effect yield, position shape, spread shape

//to do : manage syst_showering

//minor
//to do axis at the top and the right for the plot of syst

//=================================================================================
//careful : for full sim, not to use AF2
//to give the sample in line command ?
//drawback : the merging stuff
//=================================================================================
//MENU

bool do_symmetric_syst=0;
bool show_error_effect=0;

//string_method_partition_events : "individual", "bootstrap", "jacknife"
int mode_shape_MakeAndStoreFits=1;
int mode_shape_ReadFits_previously_made=1;

bool do_prun=1;

bool do_envelope_QCD=1;
bool do_prescription_pdf_alpha_s=1;

bool mode_skip_non_significative_systematics=1; //nominal mode is on
double THR_MIN_PRUNING=0.1; //0.1 %

int nb_sys_selected_object_all=0;
int nb_sys_selected_object_event_based=0;
int nb_sys_selected_object_photon=0;
int nb_sys_selected_object_jet=0;
int nb_sys_selected_object_flavor_tagging=0;
int nb_sys_selected_object_LEPTON_MET=0;
int nb_sys_selected_object_theory=0;

//=================================================================================
//=================================================================================
//=================================================================================
//=================================================================================
//=================================================================================
//TO DO
//for merging of various h_..., needs to add flags in the Merge part

//TO DO
//0) to remove global variable string_sample and add it in the tool of systematic shape
//1) to rename local_string_sample in string_sample

//2) change local in the tool_ComputeSystematicShape
//=================================================================================

//thematic as a function of category : for sure not useful : to simplify this

//rename file_syst to file_syst_yield ?

//now : 3008 lines

//problem if run in parallel : communicate between them ?!?

//renamer the caller with caller_etc..

//to do classes for shape in order to communicate ?

//to do a loop in order to manage the two modes of yields and shape
//with a index for the caller

#include "includes.h"

#include "global.h"

//thematic=object : to rename
//subthematic : nature on object : example : PH_PES, PH_PER, etc.
//=============================================================================
//mandatory so that the classes are known for the declaration of pdfs

#include "ClassesFunctionalForms/HggTwoSidedCBPdf.h"
#include "ClassesFunctionalForms/ExpGausExpPDF.h"

#include "tool_syst_shape.h"
#include "tool_syst_yield.h"

//=============================================================================
//variables

//to do : check the usefulness of vec_string_category

//for shape, need to hadd before
//to develop possibility of merging several classes of processes

bool flag_FitShapeQuiet=0;

bool FLAG_SYST_YIELD=1;
bool FLAG_SYST_SHAPE=2;

int mode_PrintResults_table_and_datacard=0; //never touch it: automatically filled

//for m_bbgamgam fit (resonant analysis)
//the range is the following
//low mass : 245-610 GeV
//high mass : 335-1500 GeV
//
//format of the table of systematics :
//
//         process1      process2
//sys_i

//to do setError in other program, in order to reduce nb of informations

//=============================================================================
//specific to shape

bool done_fit_shape_nominal=0; //do not touch that
//=============================================================================

using namespace std;

//to make a map of this

//later remove the raw and the preliminary loop on subthematic

//to call object ?

int nb_sys_raw_object_all;
int nb_sys_raw_object_event_based;
int nb_sys_raw_object_photon;
int nb_sys_raw_object_jet;
int nb_sys_raw_object_flavor_tagging;
int nb_sys_raw_object_LEPTON_MET;
int nb_sys_raw_object_theory;

//TO MAKE IT INDEPENDENT

//1 URGENT TO DO TRY REMOVE THAT AND MAKE LOCAL
//string string_sample;

//to change ordering

int index_sys; //used for tool_ComputeSystematicShape : to add as a parameter local ?

//to rename with something clear, and be careful for the replacement


//this is subthematic
vector<string> vec_string_systematic_subthematic={"PRW","Trigger","PH_PES","PH_PER","PH_EFF_ID","PH_EFF_Isol","JET_JES","JET_JER","FT_EFF_B","FT_EFF_C","FT_EFF_Light","QCD","PDF_alpha_s"};


//vector<string> vec_string_systematic_subthematic={"PRW","Trigger","PH_PES","PH_PER","PH_EFF_ID","PH_EFF_Isol","JET_JES","JET_JER","FT_EFF_B","FT_EFF_C","FT_EFF_Light","EL_EFF","MUON_EFF","MUON_SCALE","MUON_RESOLUTION","TAU_SCALE","QCD","PDF_alpha_s"};

map<string,map<string,config_subthematic_results>> map_config_results_f_subthematic_f_modified_parameter;
    
//for current_subprocess

//to do a map on that : it will simplify rather well the code
//f_modified_parameter
//vector modified exists : to adapt

double rel_effect_position_shape=0;
double err_rel_effect_position_shape=0;
		  
double rel_effect_spread_shape;
double err_rel_effect_spread_shape;
//----------------------
//for merging of several subprocesses
//- - - - - - - - - - -
//for computing error with fully correlated events (encoded in SF)
double nb_sel_nominal_all_parts_process; double err_nb_sel_nominal_all_parts_process;
double nb_sel_sys_all_parts_process; double err_nb_sel_sys_all_parts_process;
//- - - - - - - - - - -
//for computing error with partially correlated events (not encoded in SF)

double nb_sel_uncommon_part_nominal_all_parts_process;
double nb_sel_common_part_nominal_all_parts_process;
double nb_sel_uncommon_part_sys_all_parts_process;

double err_nb_sel_common_part_nominal_all_parts_process;
double err_nb_sel_uncommon_part_nominal_all_parts_process;
double err_nb_sel_uncommon_part_sys_all_parts_process; //=0; //non useful ?

double nb_sel_nominal_unweighted_all_parts_process;
double nb_sel_sys_unweighted_all_parts_process;
double nb_sel_uncommon_part_nominal_unweighted_all_parts_process;
double nb_sel_uncommon_part_sys_unweighted_all_parts_process;

vector <string> vec_string_subprocesses_current_process;

int index_subprocess;
//----------------------
//to replace with information of campaign : h024, mcd16d, etc. or in a separate information field ?

bool case_symmetric_syst=0; //do not change that

//for root
TFitResultPtr fitresult_nominal;
TFitResultPtr fitresult_syst;

//- - - - - - - - - -
//for syst yield

map<string,FILE *> fp_datacard_subthematic_syst_yield_f_category_f_process[MAX_PROCESSES];
map<string,FILE *> fp_datacard_details_syst_yield_f_category_f_process[MAX_PROCESSES];

map<string,FILE *> fp_datacard_subthematic_syst_position_shape_f_category_f_process[MAX_PROCESSES];
map<string,FILE *> fp_datacard_details_syst_position_shape_f_category_f_process[MAX_PROCESSES];

map<string,FILE *> fp_datacard_subthematic_syst_spread_shape_f_category_f_process[MAX_PROCESSES];
map<string,FILE *> fp_datacard_details_syst_spread_shape_f_category_f_process[MAX_PROCESSES];

tool_syst_shape syst_shape;
tool_syst_yield syst_yield;

vector<string> vec_modified_parameter;

class class_rel_effect_syst
{
public:
  double rel_effect_up;
  double rel_effect_down;
  double rel_effect_sym;
  
  double err_rel_effect_up;
  double err_rel_effect_down;
  double err_rel_effect_sym;
  
  bool file_or_tree_exists_up;
  bool file_or_tree_exists_down;
  bool file_or_tree_exists_sym;
};

map<string,map<string,map<string,class_rel_effect_syst>>> map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process; //observable : yield, position_shape, spread_shape;
map<string,map<string,map<string,class_rel_effect_syst>>> map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process; //observable : yield, position_shape, spread_shape;

//=============================================================================
//functions prototypes

#include "prototypes.h"
//===================================================================================================
//tools

#include "tool_helper.C"
#include "tool_Return_subthematic_given_systematic.C"


#include "tool_FunctionalForm_shape.C"
#include "tool_ComputeSystematicsShape.C"

#include "tool_ComputeSystematicsYields.C"

//config_subthematic_results::config_subthematic_results()

//by all means do not rename string_sample to string_process, else problems at other places
//#######################################################################################################################################################################################################
int Systematics_Yield_Shape(string string_sample,string string_yield_shape,string string_method_syst_shape,string string_method_partition_events,string string_category,string string_observable_shape,string string_campaign_MxAOD,int index_start_toy,int index_stop_toy)
{
  //string_yield_shape : "yield" or "shape"
  //string_method_syst_shape : "fit" or "mean_interquartile"
  //string_method_partition_events : "individual" or "bootstrap" or "jacknife"
  
//   cout << "ProcessLine" << endl;
//   gROOT->ProcessLine(".L tool_ComputeSystematicsYields.C+");
//   cout << "Load" << endl;
//   gSystem->Load("tool_ComputeSystematicsYields_C.so");
//   cout << "ProcessedLine" << endl;

  //================================================================================================
  gROOT->ProcessLine(".L ClassesFunctionalForms/HggTwoSidedCBPdf.cxx+");
  gSystem->Load("ClassesFunctionalForms/HggTwoSidedCBPdf_cxx.so");
  cout << "compile ExpGausExpPDF" << endl;
  gROOT->ProcessLine(".L ClassesFunctionalForms/ExpGausExpPDF.cxx+");
  gSystem->Load("ClassesFunctionalForms/ExpGausExpPDF_cxx.so");

  cout << "index_start_toy=" << index_start_toy << endl;
  cout << "index_stop_toy=" << index_stop_toy << endl;
  //================================================================================================
  gStyle->SetOptStat(0000000);
  gStyle->SetOptTitle(0);
  
  TH1::SetDefaultSumw2(1);

  if (flag_FitShapeQuiet) {
    RooMsgService::instance().setGlobalKillBelow(RooFit::INFO);
    //enum MsgLevel { DEBUG=0, INFO=1, PROGRESS=2, WARNING=3, ERROR=4, FATAL=5 } ;
    
    RooMsgService::instance().setSilentMode(1);
    RooMsgService::instance().setStreamStatus(1,false);
  }

  //  string_previous_MxAODSys_directory="NotInitialized";

  if (string_yield_shape=="yield")
    vec_modified_parameter.push_back("yield");
  else if (string_yield_shape=="shape") {
    vec_modified_parameter.push_back("position_shape");
    vec_modified_parameter.push_back("spread_shape");
  }
  
  //add the prefix for campaign
  
  string string_tempo=string_sample;
  
  string_sample=string_campaign_MxAOD;
  string_sample+="_";
  string_sample+=string_tempo;
  
  //to do if mode merge then make the merging one by one

  //cout << "string_category=" << string_category << endl;
  
  cout << "start treatment systematics" << endl;
  
  Systematics_Yield_Shape_current_subset_systematics(string_sample,string_yield_shape,string_method_syst_shape,string_method_partition_events,string_category,string_observable_shape,string_campaign_MxAOD,"ALL_SYS",index_start_toy,index_stop_toy);
  
  vec_modified_parameter.clear();

  cout << "end of program" << endl;

  return 0;
}
//#######################################################################################################################################################################################################
int Systematics_Yield_Shape_current_subset_systematics(string string_sample,string string_yield_shape,string string_method_syst_shape,string string_method_partition_events,string string_category,string string_observable_shape,string string_campaign_MxAOD,string menu_systematics,int index_start_toy /* =-1 */,int index_stop_toy /* =-1 */)
{
  cout << "in Systematics_Yield_Shape_current_subset_systematics, index_start_toy=" << index_start_toy << ", index_stop_toy=" << index_stop_toy << endl;

  //mode yield : always plot the results
  //mode shape : plot the results in classical mode, in jacknife mode, and in bootstrap specific mode shape ReadFits previously made

  //code preventing printing results of each toy

  if (
      string_yield_shape=="yield"
      ||
      (string_yield_shape=="shape" && (string_method_partition_events!="bootstrap" || (string_method_partition_events=="bootstrap" && (mode_shape_ReadFits_previously_made))))
      )
    mode_PrintResults_table_and_datacard=1;

  cout <<  "mode_PrintResults_table_and_datacard=" << mode_PrintResults_table_and_datacard << endl;

  for (int index_systematic_subthematic=0;index_systematic_subthematic<(int)vec_string_systematic_subthematic.size();index_systematic_subthematic++) {
    string string_systematic_subthematic=vec_string_systematic_subthematic[index_systematic_subthematic];
    
    for (unsigned int index_modified_parameter=0;index_modified_parameter<vec_modified_parameter.size();index_modified_parameter++) {
      string string_modified_parameter=vec_modified_parameter[index_modified_parameter];
      
      map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].init_results(string_category);
    } //end loop on modified parameter
  } //end loop on systematic thematic

  //maybe put a flag of the treatment : yield or shape
  
  ifstream stream_list_syst;
  
  stream_list_syst.open("Inputs/list_syst_all.sh");


  //the technique with eof is not working: see :
  //https://softwareengineering.stackexchange.com/questions/318081/why-does-ifstream-eof-not-return-true-after-reading-the-last-line-of-a-file

  nb_sys_raw_object_all=0;    
  nb_sys_raw_object_event_based=0;
  nb_sys_raw_object_photon=0;
  nb_sys_raw_object_jet=0;
  nb_sys_raw_object_flavor_tagging=0;
  nb_sys_raw_object_LEPTON_MET=0;
  nb_sys_raw_object_theory=0;
    
  vector<string> vec_string_systematic_raw;
  vec_string_systematic_raw.clear();
    
  //  cout << "menu_systematics=" << menu_systematics << endl;
    
  char buffer[128];
    
  while (stream_list_syst.getline(buffer,128)) { // for all systematics
    cout << "reads : " << buffer << endl;
    //    cout << "buffer[0]=" << buffer[0] << endl;
    if (buffer[0]=='#')
      continue;
      
    string string_systematic;
    string_systematic=buffer;

    string string_directory=ReturnMxAODSyst_directory(string_systematic);
    //to change so as to add this separatly
    string_directory+="/";

    if (string_directory=="PhotonAllSys/" && do_EGamma_1NP) //skip ALL-NPs systematics if not studying it
      continue;
    
    vec_string_systematic_raw.push_back(string_systematic);
    
    nb_sys_raw_object_all++;
      
    cout << "string_systematic=" << string_systematic << endl;
    cout << "nb_sys_raw_object_event_based=" << nb_sys_raw_object_event_based << endl;

    if (Return_object_given_systematic(string_systematic)=="event_based")
      nb_sys_raw_object_event_based++;
    else if (Return_object_given_systematic(string_systematic)=="photon")
      nb_sys_raw_object_photon++;
    else if (Return_object_given_systematic(string_systematic)=="jet")
      nb_sys_raw_object_jet++;
    else if (Return_object_given_systematic(string_systematic)=="flavor_tagging")
      nb_sys_raw_object_flavor_tagging++;
    else if (Return_object_given_systematic(string_systematic)=="LEPTON_MET")
      nb_sys_raw_object_flavor_tagging++;
    else if (Return_object_given_systematic(string_systematic)=="theory")
      nb_sys_raw_object_theory++;
  } //end read txt file on systematics to consider

  cout << "nb_sys_raw_object_theory=" << nb_sys_raw_object_theory << endl;

  cout << "nb_sys_raw_object_all=" << nb_sys_raw_object_all << endl;


  //======================================================================
  //does not allow both theoretical and experimental simultaneously for the moment
  
  found_theory=0;
  found_experimental=0;
  
  for (index_sys=0;index_sys<nb_sys_raw_object_all;index_sys++) {
    
    cout << "vec_string_systematic_raw[index_sys]=" << vec_string_systematic_raw[index_sys] << endl;
    cout << "Return_object_given_systematic(vec_string_systematic_raw[index_sys]=" << Return_object_given_systematic(vec_string_systematic_raw[index_sys]) << endl;
    
    if (Return_object_given_systematic(vec_string_systematic_raw[index_sys])=="theory")
      found_theory=1;
    else if (Return_object_given_systematic(vec_string_systematic_raw[index_sys])!="theory")
      found_experimental=1;
  }
  
  if (found_theory && found_experimental) {
    cout << "does not allow both theoretical and experimental simultaneously for the moment, halt program" << endl;
    exit(1);
  }
  
  if (found_theory && string_yield_shape=="shape") {
    //consider as well the mode_skip_non_significative_systematics=1

    //string_method_syst_shape="fit";

    string_method_syst_shape="mean_IQR";
    //NO because events are highly correlated
    //string_method_partition_events="individual";
    
    //do not do next lines !!
    //mode_shape_MakeAndStoreFits=0;
    //mode_shape_ReadFits_previously_made=0;
  }
  //======================================================================
  cout << "nb_sys_raw_object_all=" << nb_sys_raw_object_all << endl;

  //to replace nb_processes by nb_samples
  nb_processes=1;
    
  cout << "nb_processes=" << nb_processes << endl;
  
  //to do : try to factorize with details and merged

  string string_file_results_systematics_details="results/tables/details/results_rel_effect_";

  if (found_theory)
    string_file_results_systematics_details+="theoretical_";
  else
    string_file_results_systematics_details+="experimental_";

  string_file_results_systematics_details+=string_yield_shape;
  string_file_results_systematics_details+="_";

  if (string_yield_shape=="shape") {
    string_file_results_systematics_details+=string_observable_shape;
    string_file_results_systematics_details+="_";
  }
    
  string_file_results_systematics_details+="systematics_details_";
  string_file_results_systematics_details+="all_syst";

  string_file_results_systematics_details+="_proc_";
  string_file_results_systematics_details+=string_sample;

  string_file_results_systematics_details+="_cat_";
  string_file_results_systematics_details+=string_category;
  string_file_results_systematics_details+=".txt";
    
  //  cout << "string_file_results_systematics_details=" << string_file_results_systematics_details << endl;
    
  string string_file_results_systematics_subthematic;
  
  string_file_results_systematics_subthematic="results/tables/subthematic/results_rel_effect_";

  if (found_theory)
    string_file_results_systematics_subthematic+="theoretical_";
  else
    string_file_results_systematics_subthematic+="experimental_";
    
  string_file_results_systematics_subthematic+=string_yield_shape;
  string_file_results_systematics_subthematic+="_";
  if (string_yield_shape=="shape") {
    string_file_results_systematics_subthematic+=string_observable_shape;
    string_file_results_systematics_subthematic+="_";
  }
  
  string_file_results_systematics_subthematic+="systematics_thematic";
  
  if (nb_processes==1) {
    string_file_results_systematics_subthematic+="_";
    string_file_results_systematics_subthematic+="proc_";
    string_file_results_systematics_subthematic+=string_sample;
  }

  string_file_results_systematics_subthematic+="_cat_";
  string_file_results_systematics_subthematic+=string_category;
  string_file_results_systematics_subthematic+=".txt";
    
  //  cout << "string_file_results_systematics_subthematic=" << string_file_results_systematics_subthematic << endl;
    
  FillTableSyst(string_sample,string_yield_shape,string_method_syst_shape,string_method_partition_events,string_category,string_observable_shape,string_campaign_MxAOD,menu_systematics,vec_string_systematic_raw,string_file_results_systematics_details,string_file_results_systematics_subthematic,index_start_toy,index_stop_toy);
  
  return 0;
}
//#######################################################################################################################################################################################################
void FillTableSyst(string string_sample,string string_yield_shape,string string_method_syst_shape,string string_method_partition_events,string string_category,string string_observable_shape,string string_campaign_MxAOD,string menu_systematics,vector<string> vec_string_systematic_raw,string string_file_results_systematics_details,string string_file_results_systematics_subthematic,int index_start_toy /* =-1 */,int index_stop_toy /* =-1 */)
{
  cout << "FillTableSyst, string_category=" << string_category << endl;
  
  int nb_systematics_raw=vec_string_systematic_raw.size();
  //-----------------------------------------------------------------------------------
  cout << "nb_systematics_raw=" << nb_systematics_raw << endl;

  for (index_sys=0;index_sys<nb_systematics_raw;index_sys++) { //for all systematics

    string string_systematic=vec_string_systematic_raw[index_sys];

    for (int i=0;i<100;i++)
      cout << "========================================================================================================" << endl;
    
    string string_directory=ReturnMxAODSyst_directory(string_systematic);
    string_directory+="/";
  
    if (string_systematic=="showering") //switch off the printing of the Table
      mode_PrintResults_table_and_datacard=0;
    
    cout << "index_sys=" << index_sys << " / " << nb_systematics_raw << ", " << string_systematic << endl;
    
    cout << "main, start loop" << endl;

    //remove the loop
    for (int index_process=0;index_process<nb_processes;index_process++) { //for all processes

      //      string_sample=vec_string_sample[index_process];
      
      cout << "index_process=" << index_process << " / " << nb_processes << ", string_sample=" << string_sample << endl;

      //-------------
      //keep here, because systematics of shape are made w/ a same file for each b-tagging

      file_or_tree_exists_up=1;
      file_or_tree_exists_down=1;
      file_or_tree_exists_sym=1;
      //---
      //to rename in representative
      //consider current process, in a potential list of several candidates of representative of the systematics, in context of max systematic over various candidate of processes
      int index_start_nature_syst_components_sym_asym;
      int index_stop_nature_syst_components_sym_asym;
      
      if (
	  string_systematic=="MET_SoftTrk_ResoPara"
	  ||
	  string_systematic=="MET_SoftTrk_ResoPerp"
	  ||
	  Return_object_given_systematic(string_systematic)=="theory"
	  ) {
	index_start_nature_syst_components_sym_asym=0;
	index_stop_nature_syst_components_sym_asym=0;
	
	case_symmetric_syst=1;
      }
      else if ( //special case showering with other approach : no up and down
	       string_systematic=="showering"
		) {
	index_start_nature_syst_components_sym_asym=0;
	index_stop_nature_syst_components_sym_asym=0;
	
	case_symmetric_syst=1;
      }
      
      else {
	case_symmetric_syst=0;
	index_start_nature_syst_components_sym_asym=1;
	//index_start_nature_syst_components_sym_asym=2;
	index_stop_nature_syst_components_sym_asym=2;
      }
      //-----
      double rel_effect_yield_up=0;
      double rel_effect_yield_down=0;
      double rel_effect_yield_sym=0;
      
      double err_rel_effect_yield_up=0;
      double err_rel_effect_yield_down=0;
      double err_rel_effect_yield_sym=0;
      //-----
      double rel_effect_position_shape_up=0;
      double rel_effect_position_shape_down=0;
      double rel_effect_position_shape_sym=0;
      
      double err_rel_effect_position_shape_up=0;
      double err_rel_effect_position_shape_down=0;
      double err_rel_effect_position_shape_sym=0;
      //-----
      double rel_effect_spread_shape_up=0;
      double rel_effect_spread_shape_down=0;
      double rel_effect_spread_shape_sym=0;
      
      double err_rel_effect_spread_shape_up=0;
      double err_rel_effect_spread_shape_down=0;
      double err_rel_effect_spread_shape_sym=0;
      //-----
      //do not fill the roorealvar directly because of subtles of the asymmetric error : for example, when filling a low error higher than the error high, it will trunk the result, so could not do it before having made the loop on up and down
      
      done_fit_shape_nominal=0;
      
      cout << "start loop on index_sym_asym" << endl;
      
      cout << "index_start_nature_syst_components_sym_asym=" << index_start_nature_syst_components_sym_asym << endl;
      cout << "index_stop_nature_syst_components_sym_asym=" << index_stop_nature_syst_components_sym_asym << endl;
      
      for (index_sym_asym=index_start_nature_syst_components_sym_asym;index_sym_asym<=index_stop_nature_syst_components_sym_asym;index_sym_asym++) {
	
	cout << "consider index_sym_asym=" << index_sym_asym << endl;
	
	suffix_asymmetry_systematic=vec_nature_syst_components_sym_asym[index_sym_asym];
	
	cout << "suffix_asymmetry_systematic=" << suffix_asymmetry_systematic << endl;

	//information for merging
	
	if (string_yield_shape=="yield") {
	  nb_sel_nominal_all_parts_process=0;
	  nb_sel_sys_all_parts_process=0;
	  nb_sel_uncommon_part_nominal_all_parts_process=0;
	  nb_sel_common_part_nominal_all_parts_process=0;
	  nb_sel_uncommon_part_sys_all_parts_process=0;
	  
	  err_nb_sel_common_part_nominal_all_parts_process=0;
	  err_nb_sel_uncommon_part_nominal_all_parts_process=0;
	  
	  err_nb_sel_uncommon_part_sys_all_parts_process=0;
	  
	  err_nb_sel_nominal_all_parts_process=0;
	  err_nb_sel_sys_all_parts_process=0;
	  
	  nb_sel_nominal_unweighted_all_parts_process=0;
	  nb_sel_sys_unweighted_all_parts_process=0;
	  nb_sel_uncommon_part_nominal_unweighted_all_parts_process=0;
	  nb_sel_uncommon_part_sys_unweighted_all_parts_process=0;
	}
	
	//for shape, need to hadd before
	
	//to remove subloop

	vec_string_subprocesses_current_process.clear();
	
	int nb_subprocesses=1;

	for (index_subprocess=0;index_subprocess<nb_subprocesses;index_subprocess++) {
	  
	  cout << "index_subprocess=" << index_subprocess << " / " << nb_subprocesses << endl;
	  
	  string string_file_input=string_path;
	  
	  //to improve, delibarety crazy for the moment
	  if (string_yield_shape=="yield") {
	  
	    string string_directory_MxAOD=ReturnMxAODSyst_directory(string_systematic);
	    
	    string_file_input+=string_rel_path_yield;

	    string_file_input+="trees_and_hist/";
	    string_file_input+=string_directory_MxAOD;
	    string_file_input+="/";
	    
	    string_file_input+=string_campaign_MxAOD;
	    string_file_input+="_";
	    
	    int size_string_campaign_MxAOD=string_campaign_MxAOD.size();
	    string string_process=string_sample.substr(size_string_campaign_MxAOD+1); //h0xx_mc16x_, or h0xx_mc16x_h0xx_mc16x, etc. : transparent with multiple parts
	    
	    string_file_input+=string_process;
	    string_file_input+="_";
	    
	    if (found_theory) {
	      if (string_sample.find("HH")!=string::npos
		  ||
		  string_sample.find("MGH7")!=string::npos
		  )
		string_file_input+="nominal";
	      else
		string_file_input+="PhotonSys";
	    }
	    else {
	      string_file_input+=string_directory_MxAOD;
	    }
	    
	    cout << "index_sym_asym=" << index_sym_asym << ", vec_nature_syst_components_sym_asym[index_sym_asym]=" << vec_nature_syst_components_sym_asym[index_sym_asym] << endl;
	    
	    string_file_input+=".root";

	    cout << "string_file_input=" << string_file_input << endl;

	    //alternative if (!file_syst exist OR !file_syst->IsOpen with TFile::Openstuff

	    file_syst=new TFile(string_file_input.c_str(),"read");
	    
	    //drawback of next instruction : file_syst is null, so could not detect it !!
	    //file_syst=TFile::Open(string_file_input.c_str(),"read");
	    
	    //solution would be to use without pointer ?
	    
	    if (!file_syst->IsOpen()) {
	      cout << "problem, file does not exist" << endl;
	      
	      if (vec_nature_syst_components_sym_asym[index_sym_asym]=="")
		file_or_tree_exists_sym=0;
	      else if (vec_nature_syst_components_sym_asym[index_sym_asym]=="__1up")
		file_or_tree_exists_up=0;
	      else if (vec_nature_syst_components_sym_asym[index_sym_asym]=="__1down")
		file_or_tree_exists_down=0;

	      continue;
	    }
	  } //end case yield
	  
	  //if file exists, it is not enough in the case of the shape systematics : one should also have the existence of the tree
	  else if (string_yield_shape=="shape") { //mode shape
	    cout << "call ComputeSystematicShape_classical_jacknife_bootstrap" << endl;
	    
	    syst_shape.string_method_syst_shape=string_method_syst_shape;
	    
	    syst_shape.string_method_partition_events=string_method_partition_events;

	    int success=syst_shape.ComputeSystematicShape_classical_jacknife_bootstrap(string_sample,string_category,string_observable_shape,string_campaign_MxAOD,vec_string_systematic_raw[index_sys],index_start_toy,index_stop_toy);
	    cout << "called ComputeSystematicShape_classical_jacknife_bootstrap" << endl;
	    
	    if (!success)
	      continue;
	    //==============================================================================
	  } //end case file of yield exists
	  
	  //to make a function for the yield part ?
	  
	  //to delete the tree
	  //====================================================================================================
	  if (string_yield_shape=="yield") { //mode yield
	    
	    if (string_syst_yield_err=="analytic") {

	      get_yield_from_file(string_category,string_sample,vec_string_systematic_raw[index_sys]);
	      
	      cout << "nb_sel_nominal=" << nb_sel_nominal << endl;
	      //	    exit(1);
	      
	      file_syst->Close();
	      
	      cout << "vec_nature_syst_components_sym_asym[index_sym_asym]=" << vec_nature_syst_components_sym_asym[index_sym_asym] << endl;
	      cout << "values" << endl;
	      cout << "nb_sel_nominal=" << nb_sel_nominal << endl;
	      cout << "nb_sel_sys=" << nb_sel_sys << endl;
	      
	      if (nb_sel_nominal) { //if denominator non null
		rel_effect_yield=100.*((nb_sel_sys/nb_sel_nominal)-1);
		
		/*
		//-------------
		//debug

		//case fully correlated
		err_rel_effect_yield=get_err_rel_effect_yield_fully_correlated(nb_sel_nominal,
									       nb_sel_sys,
									       err_nb_sel_nominal,
									       err_nb_sel_sys);
		
		printf("rel_effect_yield for case fully correlated, %s (%%) =%4.4f +/- %4.4f\n",vec_string_systematic_raw[index_sys].c_str(),rel_effect_yield,err_rel_effect_yield);

		err_rel_effect_yield=get_err_rel_effect_yield_partially_correlated(nb_sel_nominal,
										   nb_sel_common_part_nominal,
										   nb_sel_uncommon_part_nominal,
										   nb_sel_uncommon_part_sys,
										   err_nb_sel_uncommon_part_nominal,
										   err_nb_sel_common_part_nominal,
										   err_nb_sel_uncommon_part_sys);
		printf("rel_effect_yield for case partially correlated, %s (%%) =%4.4f +/- %4.4f\n",vec_string_systematic_raw[index_sys].c_str(),rel_effect_yield,err_rel_effect_yield);
		//end debug
		*/

		cout << "correlation_full1_partial2=" << correlation_full1_partial2 << endl;

		//-------------
		if (correlation_full1_partial2==1)
		  err_rel_effect_yield=get_err_rel_effect_yield_fully_correlated(nb_sel_nominal,
										 nb_sel_sys,
										 err_nb_sel_nominal,
										 err_nb_sel_sys);
		else if (correlation_full1_partial2==2)
		  err_rel_effect_yield=get_err_rel_effect_yield_partially_correlated(nb_sel_nominal,
										     nb_sel_common_part_nominal,
										     nb_sel_uncommon_part_nominal,
										     nb_sel_uncommon_part_sys,
										     err_nb_sel_uncommon_part_nominal,
										     err_nb_sel_common_part_nominal,
										     err_nb_sel_uncommon_part_sys);
		
		printf("rel_effect_yield for %s (%%) =%4.4f +/- %4.4f\n",vec_string_systematic_raw[index_sys].c_str(),rel_effect_yield,err_rel_effect_yield);

		

	      }
	    } //end case analytic
	    else if (string_syst_yield_err=="bootstrap") {
	      cout << "call ComputeSystematicYield_bootstrap" << endl;
	      int success=syst_yield.ComputeSystematicYield_bootstrap(string_sample,string_category,string_observable_shape,string_campaign_MxAOD,vec_string_systematic_raw[index_sys],index_start_toy,index_stop_toy);
	      cout << "called ComputeSystematicYield_bootstrap" << endl;
	      
	      cout << "success=" << success << endl;

	      if (!success)
		continue;
	      
	      cout << "to develop following" << endl;
	    }
	  } //end case yield
	  //--------------------------------------------
	  //direct access if needed
	  //--------------------------------------------
	} //end loop on index_subprocess
	
	cout << "index_sym_asym=" << index_sym_asym << endl;
	cout << "file_or_tree_exists_up=" << file_or_tree_exists_up << endl;
	cout << "file_or_tree_exists_down=" << file_or_tree_exists_down << endl;
	cout << "file_or_tree_exists_sym=" << file_or_tree_exists_sym << endl;
	
	if (
	    (index_sym_asym==1 && !file_or_tree_exists_up)
	    ||
	    (index_sym_asym==2 && !file_or_tree_exists_down)
	    ||
	    (index_sym_asym==0 && !file_or_tree_exists_sym)
	    )
	  continue;

	//--------------------------------------------
	//encode the effect in the error part of the final roorealvar
	  
	//for merging systematics
	  
	if (string_yield_shape=="yield") { //mode yield

	  if (index_sym_asym==0) { //case symmetric
	    //scenario signed, MARC
	    //rel_effect_yield_sym=rel_effect_yield;
	    //err_rel_effect_yield_sym=err_rel_effect_yield;
	    
	    //scenario non signed
	    rel_effect_yield_sym=fabs(rel_effect_yield);
	    err_rel_effect_yield_sym=err_rel_effect_yield;
	    
	    //create the corresponding sym/asym	    
	    rel_effect_yield_up=fabs(rel_effect_yield);
	    err_rel_effect_yield_up=err_rel_effect_yield;
	    rel_effect_yield_down=-fabs(rel_effect_yield);
	    err_rel_effect_yield_down=err_rel_effect_yield;

	  }
	  else if (index_sym_asym==1) { //up error
	    rel_effect_yield_up=rel_effect_yield;
	    err_rel_effect_yield_up=err_rel_effect_yield;
	  }
	  else if (index_sym_asym==2) { //down error
	    rel_effect_yield_down=rel_effect_yield;
	    err_rel_effect_yield_down=err_rel_effect_yield;
	  }
	}
	else if (string_yield_shape=="shape") { //mode shape
	  //---
	  if (index_sym_asym==0) { //case symmetric
	    rel_effect_position_shape_sym=rel_effect_position_shape;
	    err_rel_effect_position_shape_sym=err_rel_effect_position_shape;
		
	    rel_effect_position_shape_up=rel_effect_position_shape;
	    err_rel_effect_position_shape_up=err_rel_effect_position_shape;
	    rel_effect_position_shape_down=-rel_effect_position_shape;
	    err_rel_effect_position_shape_down=err_rel_effect_position_shape;
	  }
	  else if (index_sym_asym==1) { //up error
	    rel_effect_position_shape_up=rel_effect_position_shape;
	    err_rel_effect_position_shape_up=err_rel_effect_position_shape;
	  }
	  else if (index_sym_asym==2) { //down error
	    rel_effect_position_shape_down=rel_effect_position_shape;
	    err_rel_effect_position_shape_down=err_rel_effect_position_shape;
	  }
	  //---
	  if (index_sym_asym==0) { //case symmetric
	    rel_effect_spread_shape_sym=rel_effect_spread_shape;
	    err_rel_effect_spread_shape_sym=err_rel_effect_spread_shape;
		
	    rel_effect_spread_shape_up=rel_effect_spread_shape;
	    err_rel_effect_spread_shape_up=err_rel_effect_spread_shape;
	    rel_effect_spread_shape_down=-rel_effect_spread_shape;
	    err_rel_effect_spread_shape_down=err_rel_effect_spread_shape;
	  }
	  else if (index_sym_asym==1) { //up error
	    rel_effect_spread_shape_up=rel_effect_spread_shape;
	    err_rel_effect_spread_shape_up=err_rel_effect_spread_shape;
	  }
	  else if (index_sym_asym==2) { //down error
	    rel_effect_spread_shape_down=rel_effect_spread_shape;
	    err_rel_effect_spread_shape_down=err_rel_effect_spread_shape;
	  }
	  //---
	} //end shape : 2
	
	cout << "index_sym_asym=" << index_sym_asym << endl;
	cout << "rel_effect_yield_up=" << rel_effect_yield_up << " +/- " << err_rel_effect_yield_up << endl;
	cout << "rel_effect_yield_down=" << rel_effect_yield_down << " +/- " << err_rel_effect_yield_down << endl;
	cout << "rel_effect_yield_sym=" << rel_effect_yield_sym << " +/- " << err_rel_effect_yield_sym << endl;
	
      } //end loop on sym/asym
    
      //at this stage, one has the up, down, sym
      
      //treatment for case UP and DOWN of same sign


      cout << "before treatment of potential same sign" << endl;
      cout << "string systematic=" << string_systematic << endl;
      cout << "rel_effect_yield_up=" << rel_effect_yield_up << " +/- " << err_rel_effect_yield_up << endl;
      cout << "rel_effect_yield_down=" << rel_effect_yield_down << " +/- " << err_rel_effect_yield_down << endl;
      cout << "rel_effect_yield_sym=" << rel_effect_yield_sym << " +/- " << err_rel_effect_yield_sym << endl;

      cout << "rel_effect_position_shape_up=" << rel_effect_position_shape_up << " +/- " << err_rel_effect_position_shape_up << endl;
      cout << "rel_effect_position_shape_down=" << rel_effect_position_shape_down << " +/- " << err_rel_effect_position_shape_down << endl;
      cout << "rel_effect_position_shape_sym=" << rel_effect_position_shape_sym << " +/- " << err_rel_effect_position_shape_sym << endl;

      cout << "rel_effect_spread_shape_up=" << rel_effect_spread_shape_up << " +/- " << err_rel_effect_spread_shape_up << endl;
      cout << "rel_effect_spread_shape_down=" << rel_effect_spread_shape_down << " +/- " << err_rel_effect_spread_shape_down << endl;
      cout << "rel_effect_spread_shape_sym=" << rel_effect_spread_shape_sym << " +/- " << err_rel_effect_spread_shape_sym << endl;
      
      cout << "rel_effect_yield_up=" << rel_effect_yield_up << " +/- " << err_rel_effect_yield_up << endl;
      cout << "rel_effect_yield_down=" << rel_effect_yield_down << " +/- " << err_rel_effect_yield_down << endl;
      cout << "rel_effect_yield_sym=" << rel_effect_yield_sym << " +/- " << err_rel_effect_yield_sym << endl;

      
      if (!case_symmetric_syst) { //cas asymmetric
	if (string_yield_shape=="yield") //mode yield
	  prevent_pathological_same_sign_syst(&rel_effect_yield_up,
					      &rel_effect_yield_down
					      );
	
	else if (string_yield_shape=="shape") { //mode shape
	  prevent_pathological_same_sign_syst(&rel_effect_position_shape_up,
					      &rel_effect_position_shape_down
					      );
	  
	  prevent_pathological_same_sign_syst(&rel_effect_spread_shape_up,
					      &rel_effect_spread_shape_down
					      );
	} //end case shape

      } //end case asymmetric
      //===========================================================================================
      cout << "before removing systematic with either non significative or with a file missing" << endl;
      cout << "string systematic=" << string_systematic << endl;
      cout << "rel_effect_yield_up=" << rel_effect_yield_up << " +/- " << err_rel_effect_yield_up << endl;
      cout << "rel_effect_yield_down=" << rel_effect_yield_down << " +/- " << err_rel_effect_yield_down << endl;
      cout << "rel_effect_yield_sym=" << rel_effect_yield_sym << " +/- " << err_rel_effect_yield_sym << endl;
	
      cout << "rel_effect_position_shape_up=" << rel_effect_position_shape_up << " +/- " << err_rel_effect_position_shape_up << endl;
      cout << "rel_effect_position_shape_down=" << rel_effect_position_shape_down << " +/- " << err_rel_effect_position_shape_down << endl;
      cout << "rel_effect_position_shape_sym=" << rel_effect_position_shape_sym << " +/- " << err_rel_effect_position_shape_sym << endl;
      
      cout << "rel_effect_spread_shape_up=" << rel_effect_spread_shape_up << " +/- " << err_rel_effect_spread_shape_up << endl;
      cout << "rel_effect_spread_shape_down=" << rel_effect_spread_shape_down << " +/- " << err_rel_effect_spread_shape_down << endl;
      cout << "rel_effect_spread_shape_sym=" << rel_effect_spread_shape_sym << " +/- " << err_rel_effect_spread_shape_sym << endl;
      
      //remove systematics with either non significative or with a file missing
      //===========================================================================================
      for (unsigned int index_modified_parameter=0;index_modified_parameter<vec_modified_parameter.size();index_modified_parameter++) {
	  
	string string_modified_parameter=vec_modified_parameter[index_modified_parameter];

	cout << "string_modified_parameter=" << string_modified_parameter << endl;

	for (index_sym_asym=index_start_nature_syst_components_sym_asym;index_sym_asym<=index_stop_nature_syst_components_sym_asym;index_sym_asym++) {
	  //	for (index_sym_asym=0;index_sym_asym<=3;index_sym_asym++) {
	  
	  string string_nature_syst_components_sym_asym=vec_nature_syst_components_sym_asym[index_sym_asym];
	  
	  cout << "phase index_sym_asym=" << index_sym_asym << endl;
	  
	  cout << "string_nature_syst_components_sym_asym=" << string_nature_syst_components_sym_asym << endl;
	  
	  double current_rel_effect=-99999;
	  double current_err_rel_effect=99999;
	    
	  cout << "rel_effect_yield_sym=" << rel_effect_yield_sym << endl;

	  if (string_modified_parameter=="yield") {
	    if (string_nature_syst_components_sym_asym=="") {
	      current_rel_effect=rel_effect_yield_sym;
	      current_err_rel_effect=err_rel_effect_yield_sym;
	    }
	    else if (vec_nature_syst_components_sym_asym[index_sym_asym]=="__1up") {
	      current_rel_effect=rel_effect_yield_up;
	      current_err_rel_effect=err_rel_effect_yield_up;
	    }
	    else if (vec_nature_syst_components_sym_asym[index_sym_asym]=="__1down") {
	      current_rel_effect=rel_effect_yield_down;
	      current_err_rel_effect=err_rel_effect_yield_down;
	    }
	  }
	  else if (vec_modified_parameter[index_modified_parameter]=="position_shape") {
	    if (vec_nature_syst_components_sym_asym[index_sym_asym]=="") {
	      current_rel_effect=rel_effect_position_shape_sym;
	      current_err_rel_effect=err_rel_effect_position_shape_sym;
	    }
	    else if (vec_nature_syst_components_sym_asym[index_sym_asym]=="__1up") {
	      current_rel_effect=rel_effect_position_shape_up;
	      current_err_rel_effect=err_rel_effect_position_shape_up;
	    }
	    else if (vec_nature_syst_components_sym_asym[index_sym_asym]=="__1down") {
	      current_rel_effect=rel_effect_position_shape_down;
	      current_err_rel_effect=err_rel_effect_position_shape_down;
	    }
	  }
	  else if (vec_modified_parameter[index_modified_parameter]=="spread_shape") {
	    if (vec_nature_syst_components_sym_asym[index_sym_asym]=="") {
	      current_rel_effect=rel_effect_spread_shape_sym;
	      current_err_rel_effect=err_rel_effect_spread_shape_sym;
	    }
	    else if (vec_nature_syst_components_sym_asym[index_sym_asym]=="__1up") {
	      current_rel_effect=rel_effect_spread_shape_up;
	      current_err_rel_effect=err_rel_effect_spread_shape_up;
	    }
	    else if (vec_nature_syst_components_sym_asym[index_sym_asym]=="__1down") {
	      current_rel_effect=rel_effect_spread_shape_down;
	      current_err_rel_effect=err_rel_effect_spread_shape_down;
	    }
	  }

	  
	  cout << "index_sym_asym=" << index_sym_asym << endl;
	  //	    cout << "string_thematic=" << string_thematic << endl;
	  cout << "string_sample=" << string_sample << endl;
	  cout << "string_systematic=" << string_systematic << endl;
	  cout << "rel_effect_yield_sym=" << rel_effect_yield_sym << " +/- " << err_rel_effect_yield_sym << endl;
	  cout << "rel_effect_yield_up=" << rel_effect_yield_up << " +/- " << err_rel_effect_yield_up << endl;
	  cout << "rel_effect_yield_down=" << rel_effect_yield_down << " +/- " << err_rel_effect_yield_down << endl;

	  cout << "rel_effect_yield_up=" << rel_effect_yield_up << " +/- " << err_rel_effect_yield_up << endl;
	  cout << "rel_effect_yield_down=" << rel_effect_yield_down << " +/- " << err_rel_effect_yield_down << endl;
	  cout << "rel_effect_yield_sym=" << rel_effect_yield_sym << " +/- " << err_rel_effect_yield_sym << endl;
	  
	  cout << "now fill the map" << endl;
	  cout << "string_nature_syst_components_sym_asym=" << string_nature_syst_components_sym_asym	<< endl;
	  
	  cout << "vec_nature_syst_components_sym_asym[index_sym_asym]=" << vec_nature_syst_components_sym_asym[index_sym_asym] << endl;

	  if (vec_nature_syst_components_sym_asym[index_sym_asym]=="__1up") {
	    map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_up=current_rel_effect;
	    map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_up=current_err_rel_effect;
	    
	    map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_up=file_or_tree_exists_up;
	  }
	  else if (vec_nature_syst_components_sym_asym[index_sym_asym]=="__1down") {
	    map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_down=current_rel_effect;
	    map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_down=current_err_rel_effect;
	    
	    map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_down=file_or_tree_exists_down;
	  }
	  else if (vec_nature_syst_components_sym_asym[index_sym_asym]=="") {
	    map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_sym=current_rel_effect;
	    map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_sym=current_err_rel_effect;
	    
	    map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_sym=file_or_tree_exists_sym;

	    cout << "map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_sym=" << map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_sym << endl;
	  }
	  
	  cout << "Diagnostic 1" << endl;
	  cout << "map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_up=" << map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_up << endl;
	  cout << "map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_down=" << map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_down << endl;
	  cout << "map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_sym=" << map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_sym << endl;
		    
	  cout << "string_modified_parameter " << string_modified_parameter << endl;
	  cout << "string_sample " << string_sample << endl;
	  //----------
	} //end loop sym/asym
      } //end loop on modified parameter
      //===========================================================================================
    } //end loop process
  } //end syst

  //  cout << "rel_effect_yield_sym=" << rel_effect_yield_sym << " +/- " << err_rel_effect_yield_sym << endl;

  //end raw results
  //====================================================================================================================================================================================================
  //====================================================================================================================================================================================================
  //====================================================================================================================================================================================================
  //====================================================================================================================================================================================================
  //====================================================================================================================================================================================================
  //====================================================================================================================================================================================================
  //treatment of pathological cases and prun
  
  cout << "treatment of pathological cases and prun phase 1" << endl;

  for (index_sys=0;index_sys<nb_systematics_raw;index_sys++) { //for all systematics
    
    //    cout << "index_sys=" << index_sys << endl;

    string string_systematic=vec_string_systematic_raw[index_sys];
    
    //remove the loop
    for (int index_process=0;index_process<nb_processes;index_process++) { //for all processes
      
      cout << "before prun of string_systematic=" << string_systematic << endl;

      for (unsigned int index_modified_parameter=0;index_modified_parameter<vec_modified_parameter.size();index_modified_parameter++) {
	string string_modified_parameter=vec_modified_parameter[index_modified_parameter];

	if (do_prun)
	  prun_systematic_effect(&map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_up,
				 &map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_down,
				 &map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_sym,
				 &map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_up,
				 &map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_down,
				 &map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_sym);

      } //end loop on modified parameter
    } //end list processes
  } //end list on systematics

  //=================================================================
  //2) construct results of systematics, taking into account MCsmear-PDsmear, of the envelope for QCD, etc.

  cout << "phase construct results of systematics" << endl;
  
  vector<string> vec_string_systematic_selected;
  //eventually, to clean
  
  nb_sys_selected_object_all=0;
  nb_sys_selected_object_event_based=0;
  nb_sys_selected_object_photon=0;
  nb_sys_selected_object_jet=0;
  nb_sys_selected_object_flavor_tagging=0;
  nb_sys_selected_object_LEPTON_MET=0;
  nb_sys_selected_object_theory=0;


  //  bool do_subtract_MCsmear_PDsmear=0;
  bool do_subtract_MCsmear_PDsmear=1;

  bool found_QCD=0;
  bool found_pdf_alpha_s=0;

  
  for (index_sys=0;index_sys<nb_systematics_raw;index_sys++) { //for all systematics
    string string_systematic_raw=vec_string_systematic_raw[index_sys];
    
    //    cout << "string_systematic_raw=" << string_systematic_raw << endl;
    //    cout << "is it pdf+alpha s : " << Return_subthematic_given_systematic(string_systematic_raw) << endl;

    if (do_subtract_MCsmear_PDsmear && string_systematic_raw.find("PDsmear")!=string::npos) //skip PDsmear, since it is treated when encountering MCsmear
      continue;
    
    if (do_envelope_QCD && found_QCD && Return_subthematic_given_systematic(string_systematic_raw)=="QCD") //does not manage several times QCD
      continue;

    cout << "found_pdf_alpha_s=" << found_pdf_alpha_s << endl;
    
    if (do_prescription_pdf_alpha_s && found_pdf_alpha_s && Return_subthematic_given_systematic(string_systematic_raw)=="PDF_alpha_s") //does not manage several times pdf+alpha_s
      continue;
    
    string string_systematic=string_systematic_raw;
    
    size_t found_MCsmear=string_systematic_raw.find("_MCsmear");
    
    if (do_subtract_MCsmear_PDsmear && found_MCsmear!=string::npos) {
      string_systematic=string_systematic_raw.substr(0,found_MCsmear);
    }
    
    //to improve with return_subthematic
    if (do_envelope_QCD && string_systematic_raw.find("muR")!=string::npos) {
      string_systematic="QCD";
      found_QCD=1;
    }
    
    if (do_prescription_pdf_alpha_s && Return_subthematic_given_systematic(string_systematic_raw)=="PDF_alpha_s") { //does not manage several times pdf+alpha_s
      string_systematic="PDF_alpha_s";

      found_pdf_alpha_s=1;
    }    
    
    nb_sys_selected_object_all++;

    if (Return_object_given_systematic(string_systematic)=="event_based")
      nb_sys_selected_object_event_based++;
    else if (Return_object_given_systematic(string_systematic)=="photon")
      nb_sys_selected_object_photon++;
    else if (Return_object_given_systematic(string_systematic)=="jet")
      nb_sys_selected_object_jet++;
    else if (Return_object_given_systematic(string_systematic)=="flavor_tagging")
      nb_sys_selected_object_flavor_tagging++;
    else if (Return_object_given_systematic(string_systematic)=="LEPTON_MET")
      nb_sys_selected_object_LEPTON_MET++;
    else if (Return_object_given_systematic(string_systematic)=="theory")
      nb_sys_selected_object_theory++;

    vec_string_systematic_selected.push_back(string_systematic);
    
    //remove the loop
    for (int index_process=0;index_process<nb_processes;index_process++) { //for all processes
      
      for (unsigned int index_modified_parameter=0;index_modified_parameter<vec_modified_parameter.size();index_modified_parameter++) {
	
	string string_modified_parameter=vec_modified_parameter[index_modified_parameter];
	
	if (do_subtract_MCsmear_PDsmear && found_MCsmear!=string::npos) {
	  
	  string string_systematic_MCsmear=string_systematic+"_MCsmear";
	  string string_systematic_PDsmear=string_systematic+"_PDsmear";
	  
	  cout << "string_modified_parameter=" << string_modified_parameter << endl;

	  map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_up=
	    (
	     map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_MCsmear][string_modified_parameter][string_sample].rel_effect_up
	     -
	     map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_PDsmear][string_modified_parameter][string_sample].rel_effect_up
	     );
	  
	  map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_down=
	    (
	     map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_MCsmear][string_modified_parameter][string_sample].rel_effect_down
	     -
	     map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_PDsmear][string_modified_parameter][string_sample].rel_effect_down
	     );
	  
	  map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_sym=
	    (
	     map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_MCsmear][string_modified_parameter][string_sample].rel_effect_sym
	     -
	     map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_PDsmear][string_modified_parameter][string_sample].rel_effect_sym
	     );
	  
	  map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_up=sqrt(
																							     pow(map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_MCsmear][string_modified_parameter][string_sample].err_rel_effect_up,2)
																							     +
																							     pow(map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_PDsmear][string_modified_parameter][string_sample].err_rel_effect_up,2)
																							     );
	  
	  map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_down=sqrt(
																							       pow(map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_MCsmear][string_modified_parameter][string_sample].err_rel_effect_down,2)
																							       +
																							       pow(map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_PDsmear][string_modified_parameter][string_sample].err_rel_effect_down,2)
																							       );
	  
	  map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_sym=sqrt(
																							     pow(map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_MCsmear][string_modified_parameter][string_sample].err_rel_effect_sym,2)
																							     +
																							     pow(map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_PDsmear][string_modified_parameter][string_sample].err_rel_effect_sym,2)
																							      );
	  cout << "-----" << endl;
	  cout << "before potential sam sign" << endl;
	  cout << "MCsmear rel_effect_up=" << map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_MCsmear][string_modified_parameter][string_sample].rel_effect_up << " +/- " << map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_MCsmear][string_modified_parameter][string_sample].err_rel_effect_up << endl;
	  cout << "PDsmear rel_effect_up=" << map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_PDsmear][string_modified_parameter][string_sample].rel_effect_up << " +/- " << map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_PDsmear][string_modified_parameter][string_sample].err_rel_effect_up << endl;
	  
	  cout << "MCsmear rel_effect_down=" << map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_MCsmear][string_modified_parameter][string_sample].rel_effect_down << " +/- " << map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_MCsmear][string_modified_parameter][string_sample].err_rel_effect_down << endl;
	  cout << "PDsmear rel_effect_down=" << map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_PDsmear][string_modified_parameter][string_sample].rel_effect_down << " +/- " << map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_PDsmear][string_modified_parameter][string_sample].err_rel_effect_down << endl;
	  
	  cout << "MCsmear - PDsmear rel effect up=" << map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_up << " +/- " << map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_up << endl;
	  cout << "MCsmear - PDsmear rel effect down=" << map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_down << " +/- " << map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_down << endl;
	  cout << "-----" << endl;
	  cout << "after potential sam sign" << endl;

	  prevent_pathological_same_sign_syst(&map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_up,
					      &map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_down);
	  
	  cout << "MCsmear - PDsmear rel effect up=" << map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_up << " +/- " << map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_up << endl;
	  cout << "MCsmear - PDsmear rel effect down=" << map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_down << " +/- " << map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_down << endl;
	  //----------
	  if (
	      map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_MCsmear][string_modified_parameter][string_sample].file_or_tree_exists_sym==1
	      &&
	      map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_PDsmear][string_modified_parameter][string_sample].file_or_tree_exists_sym==1
	      )
	    map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_sym=1;
	  
	  if (
	      map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_MCsmear][string_modified_parameter][string_sample].file_or_tree_exists_up==1
	      &&
	      map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_PDsmear][string_modified_parameter][string_sample].file_or_tree_exists_up==1
	      )
	    map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_up=1;
	  
	  if (
	      map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_MCsmear][string_modified_parameter][string_sample].file_or_tree_exists_down==1
	      &&
	      map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_PDsmear][string_modified_parameter][string_sample].file_or_tree_exists_down==1
	      )
	    map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_down=1;
	}
	else if (do_envelope_QCD && string_systematic=="QCD") {
	  //search for |max| over systematics
	  
	  double max_sys_QCD=0;
	  double err_max_sys_QCD=0;
	  for (int index_search_sys=index_sys;index_search_sys<nb_systematics_raw;index_search_sys++) {
	    
	    cout << "investigating " << vec_string_systematic_raw[index_search_sys] << endl;
	    
	    string string_search_systematic_raw=vec_string_systematic_raw[index_search_sys];
	    if (string_search_systematic_raw.find("muR")==string::npos)
	      continue;
	    
	    //	    cout << "so far, max_sys_QCD=" << max_sys_QCD << endl;
	    //	    cout << "now encounter " << string_search_systematic_raw << ", value=" << map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_search_systematic_raw][string_modified_parameter][string_sample].rel_effect_sym << endl;
	    
	    if (fabs(map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_search_systematic_raw][string_modified_parameter][string_sample].rel_effect_sym)>max_sys_QCD) {
	      cout << "this is above max" << endl;
	      max_sys_QCD=fabs(map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_search_systematic_raw][string_modified_parameter][string_sample].rel_effect_sym);
	      err_max_sys_QCD=map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_search_systematic_raw][string_modified_parameter][string_sample].err_rel_effect_sym;
	    }
	  } //end search for max of systematic QCD
	  
	  map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_sym=max_sys_QCD;
	  map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_sym=err_max_sys_QCD;
	  map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_sym=1;
	}

	else if (do_prescription_pdf_alpha_s && Return_subthematic_given_systematic(string_systematic_raw)=="PDF_alpha_s") {

	  cout << "computation of the pdf systematic" << endl;

	  double rel_effect_pdf=0;
	  double err_rel_effect_pdf=0;
	  
	  string string_alpha_s_up="90432";
	  string string_alpha_s_down="90431";
	  
	  double rel_effect_alpha_s=0;
	  double err_rel_effect_alpha_s=0;

	  double rel_effect_pdf_plus_alpha_s=0;
	  double err_rel_effect_pdf_plus_alpha_s=0;

	  int nb_pdfs_not_alpha_s=0;
	  
	  for (int index_search_sys=index_sys;index_search_sys<nb_systematics_raw;index_search_sys++) {
	    
	    string string_search_systematic_raw=vec_string_systematic_raw[index_search_sys];
	    
	    //serie 904xx and 260xxx
	    //to make a OR ?

	    cout << "-----" << endl;
	    cout << "string_search_systematic_raw=" << string_search_systematic_raw << endl;

	    //	    if (string_search_systematic_raw.find("lhapdf")!=string::npos) { //pdf or alpha_s information
	    if (string_search_systematic_raw.find("pdf_set")!=string::npos) { //pdf or alpha_s information

	      if (string_search_systematic_raw.find(string_alpha_s_up)!=string::npos || string_search_systematic_raw.find(string_alpha_s_down)!=string::npos) {  //alpha_s
		
		double sign=1;
		
		if (string_search_systematic_raw.find(string_alpha_s_down)!=string::npos)
		  sign=-1;
		
		rel_effect_alpha_s+=sign*0.5*map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_search_systematic_raw][string_modified_parameter][string_sample].rel_effect_sym;
		
		err_rel_effect_alpha_s+=pow(0.5*map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_search_systematic_raw][string_modified_parameter][string_sample].err_rel_effect_sym,2);
	      }
	      else { //pure pdf effect
		nb_pdfs_not_alpha_s++;
		rel_effect_pdf+=pow(map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_search_systematic_raw][string_modified_parameter][string_sample].rel_effect_sym,2);
		err_rel_effect_pdf+=pow(map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_search_systematic_raw][string_modified_parameter][string_sample].rel_effect_sym*map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_search_systematic_raw][string_modified_parameter][string_sample].err_rel_effect_sym,2);
	      }

	      printf("so far, rel_effect_pdf=%10.10f +/- %10.10f\n",rel_effect_pdf,err_rel_effect_pdf);

	    } //end search of systematics corresponding to keywords
	  } //end search sys
	  
	  //don't change order of instructions by all means, else computation will be wrong
	  
	  cout << "nb_pdfs_not_alpha_s=" << nb_pdfs_not_alpha_s << endl;

	  //scenario 904xx
	  rel_effect_pdf=sqrt(rel_effect_pdf);
	  if (rel_effect_pdf)
	    err_rel_effect_pdf=sqrt(err_rel_effect_pdf)/rel_effect_pdf;
	  else
	    err_rel_effect_pdf=0;
	  
	  //This is only scenario pdf 260xxx : NNPDF : take rms so take / n pdfs not alpha_s, and divide by N-1 !
	  //	  err_rel_effect_pdf=sqrt(err_rel_effect_pdf)/((nb_pdfs_not_alpha_s-1)*sqrt(rel_effect_pdf));
	  //	  rel_effect_pdf=(1./(nb_pdfs_not_alpha_s-1))*sqrt(rel_effect_pdf);
	  
	  rel_effect_alpha_s=fabs(rel_effect_alpha_s);
	  err_rel_effect_alpha_s=sqrt(err_rel_effect_alpha_s);

	  rel_effect_pdf_plus_alpha_s=sqrt(pow(rel_effect_pdf,2)+pow(rel_effect_alpha_s,2)); //sure
	  err_rel_effect_pdf_plus_alpha_s=sqrt(pow(rel_effect_pdf*err_rel_effect_pdf,2)+pow(rel_effect_alpha_s*err_rel_effect_alpha_s,2))/rel_effect_pdf_plus_alpha_s; //sure

	  cout << "rel_effect_pdf=" << rel_effect_pdf << " +/-" << err_rel_effect_pdf << endl;
	  cout << "rel_effect_alpha_s=" << rel_effect_alpha_s << " +/- =" << err_rel_effect_alpha_s << endl;
	  cout << "rel_effect_pdf_plus_alpha_s=" << rel_effect_pdf_plus_alpha_s << " +/-" << err_rel_effect_pdf_plus_alpha_s << endl;
	  
	  map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_sym=rel_effect_pdf_plus_alpha_s;
	  map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_sym=err_rel_effect_pdf_plus_alpha_s;
	  map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_sym=1;
	}
	else { //case without MCsmear and PDsmear
	  map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_sym=map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_raw][string_modified_parameter][string_sample].rel_effect_sym;
	  map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_up=map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_raw][string_modified_parameter][string_sample].rel_effect_up;
	  map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_down=map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_raw][string_modified_parameter][string_sample].rel_effect_down;

	  map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_sym=map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_raw][string_modified_parameter][string_sample].err_rel_effect_sym;
	  map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_up=map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_raw][string_modified_parameter][string_sample].err_rel_effect_up;
	  map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_down=map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_raw][string_modified_parameter][string_sample].err_rel_effect_down;

	  map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_sym=map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_raw][string_modified_parameter][string_sample].file_or_tree_exists_sym;
	  map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_up=map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_raw][string_modified_parameter][string_sample].file_or_tree_exists_up;
	  map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_down=map_map_map_raw_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic_raw][string_modified_parameter][string_sample].file_or_tree_exists_down;
	} //end general case
	
	//ideally, to do if time available, one should recall the prevent_pathological_same_sign_syst(double *ptr_rel_effect_up

      } //end loop on modified parameter
    } //end list processes
  } //end list on systematics
  //=================================================================
  FILE *fp_results_sys_details=0;

  cout << "phase prepare writing results " << endl;

  //check if there is showering in the list of systematics : in this case, do not do print table
  for (index_sys=0;index_sys<nb_systematics_raw;index_sys++) {
    if (vec_string_systematic_raw[index_sys]=="showering") //switch off the printing of the Table
      mode_PrintResults_table_and_datacard=0;
  }

  cout << "phase writing 1" << endl;

  //prepare the header table and the datacard files

  int nb_systematics_selected=vec_string_systematic_selected.size();

  cout << "phase writing 2" << endl;

  if (mode_PrintResults_table_and_datacard) {
    //-----------------------------------------------------------------------------------
    fp_results_sys_details=fopen(string_file_results_systematics_details.c_str(),"wt");
    
    cout << "phase writing 3" << endl;
    PrintHeaderTableSyst(string_sample,fp_results_sys_details,string_yield_shape);
    
    cout << "phase writing 4" << endl;
    PrintTableSystematics_detail(string_sample,fp_results_sys_details,string_category,string_yield_shape,string_observable_shape,vec_string_systematic_selected);

  } //end print table

  cout << "phase writing 5" << endl;

  //-------------------------
  //================================================================================================
  //Merged systematic
  
  //here the ordering of the loop is directly related to the format of the Table, so could not factorize with previous loops
  
  PrepareMergedSystematic(string_sample,string_category,vec_string_systematic_selected);

  //to do factorize this in a function, in order to make as the details

  FILE *fp_results_sys_subthematic=0;

  if (mode_PrintResults_table_and_datacard) {
    
    if (menu_systematics=="ALL_SYS")
      fp_results_sys_subthematic=fopen(string_file_results_systematics_subthematic.c_str(),"wt");
    
    PrintHeaderTableSyst(string_sample,fp_results_sys_subthematic,string_yield_shape);
    
    PrintTableSystematics_subthematic(string_sample,fp_results_sys_subthematic,string_category,string_yield_shape,string_observable_shape);
    
    //=================================================================================================
    //graphical representation of the systematics
    
    //[3] : symmetric, up, down
    //per thematic = object of interest
    
    map<string,map<string,map<string,TH1F *>>> map_map_map_hist_rel_effect_modified_parameter_f_sym_asym_f_modified_parameter_f_thematic_f_process[3]; //observable : yield, position_shape, spread_shape
    
    vector<string> vec_string_object={"all","event_based","photon","jet","flavor_tagging","LEPTON_MET","theory"};
    
    int nb_thematics=vec_string_object.size();
    
    int nb_systematics_object=0;
    
    for (unsigned int index_modified_parameter=0;index_modified_parameter<vec_modified_parameter.size();index_modified_parameter++) {
      string string_modified_parameter=vec_modified_parameter[index_modified_parameter];
      
      for (int index_object=0;index_object<nb_thematics;index_object++) {
	string string_object=vec_string_object[index_object];
	
	cout << "prepare string_object=" << string_object << endl;
	
	if (string_object=="all")
	  nb_systematics_object=nb_sys_selected_object_all;
	if (string_object=="event_based")
	  nb_systematics_object=nb_sys_selected_object_event_based;
	else if (string_object=="photon")
	  nb_systematics_object=nb_sys_selected_object_photon;
	else if (string_object=="jet")
	  nb_systematics_object=nb_sys_selected_object_jet;
	else if (string_object=="flavor_tagging")
	  nb_systematics_object=nb_sys_selected_object_flavor_tagging;
	else if (string_object=="LEPTON_MET")
	  nb_systematics_object=nb_sys_selected_object_LEPTON_MET;
	else if (string_object=="theory")
	  nb_systematics_object=nb_sys_selected_object_theory;
	
	cout << "nb_systematics_object=" << nb_systematics_object << endl;
	
	if (!nb_systematics_object)
	  continue;

	//remove the loop	
	for (int index_process=0;index_process<nb_processes;index_process++) { //for all processes

	  for (index_sym_asym=0;index_sym_asym<3;index_sym_asym++) { //consider all potential systematic
	    
	    string string_sym_asym;
	    int color_hist=kBlack;
	    
	    if (index_sym_asym==0)
	      string_sym_asym="sym";
	    else if (index_sym_asym==1) {
	      string_sym_asym="up";
	      color_hist=kRed;
	    }
	    else if (index_sym_asym==2) {
	      string_sym_asym="down";
	      color_hist=kBlue;
	    }
	    
	    cout << "phase A, string_object=" << string_object << endl;
	    
	    map_map_map_hist_rel_effect_modified_parameter_f_sym_asym_f_modified_parameter_f_thematic_f_process[index_sym_asym][string_modified_parameter][string_object][string_sample]=new TH1F(
																								  (string("hist_rel_effect_"+string_modified_parameter+"_")+string_sym_asym+"_"+string_sample+"_"+string_object).c_str(),
																								  (string("hist_rel_effect_"+string_modified_parameter+"_")+string_sym_asym+"_"+string_sample+"_"+string_object).c_str(),
																								  nb_systematics_object,0,nb_systematics_object
																								  );
	    
	    map_map_map_hist_rel_effect_modified_parameter_f_sym_asym_f_modified_parameter_f_thematic_f_process[index_sym_asym][string_modified_parameter][string_object][string_sample]->SetLineColor(color_hist);
	    
	    //	  cout << "nb_systematics_object=" << nb_systematics_object << endl;
	    
	    //	  cout << "index_sym_asym=" << index_sym_asym << endl;
	    //	  cout << "string_object=" << string_object << endl;
	    //	  cout << "string_sample=" << string_sample << endl;
	    //	  cout << "map_map_map_hist_rel_effect_modified_parameter_f_sym_asym_f_modified_parameter_f_thematic_f_process[index_sym_asym][string_modified_parameter][string_object][string_sample]=" << map_map_map_hist_rel_effect_modified_parameter_f_sym_asym_f_modified_parameter_f_thematic_f_process[index_sym_asym][string_modified_parameter][string_object][string_sample] << endl;
	    
	  } //end loop index sym asym
	} //end loop on processes
      } //end loop object
    } //end loop on modified parameter
    //=================================================================================================
  //Fill the information

  cout << "fill the information" << endl;

  for (index_sys=0;index_sys<nb_systematics_selected;index_sys++) { //for all systematics
    
    for (int i=0;i<100;i++)
      cout << "========================================================================================================" << endl;

    //    cout << "index_sys=" << index_sys << endl;
    
    string string_systematic;
    string_systematic=vec_string_systematic_selected[index_sys];
    
    for (unsigned int index_modified_parameter=0;index_modified_parameter<vec_modified_parameter.size();index_modified_parameter++) {
      
      string string_modified_parameter=vec_modified_parameter[index_modified_parameter];
      
      for (int index_thematic=0;index_thematic<nb_thematics;index_thematic++) {
	string string_object=vec_string_object[index_thematic];

	if (string_object=="all")
	  nb_systematics_object=nb_sys_selected_object_all;
	else if (string_object=="event_based")
	  nb_systematics_object=nb_sys_selected_object_event_based;
	else if (string_object=="photon")
	  nb_systematics_object=nb_sys_selected_object_photon;
	else if (string_object=="jet")
	  nb_systematics_object=nb_sys_selected_object_jet;
	else if (string_object=="flavor_tagging")
	  nb_systematics_object=nb_sys_selected_object_flavor_tagging;
	else if (string_object=="LEPTON_MET")
	  nb_systematics_object=nb_sys_selected_object_LEPTON_MET;
	else if (string_object=="theory")
	  nb_systematics_object=nb_sys_selected_object_theory;
	
	if (!nb_systematics_object)
	  continue;
	
	for (int index_process=0;index_process<nb_processes;index_process++) { //for all processes
	  
	  for (index_sym_asym=0;index_sym_asym<3;index_sym_asym++) { //consider all sym/asym
	    
	    string string_sym_asym;
	    
	    if (index_sym_asym==0)
	      string_sym_asym="sym";
	    else if (index_sym_asym==1)
	      string_sym_asym="up";
	    else if (index_sym_asym==2)
	      string_sym_asym="down";
	    
	    int index_sys_thematic=-1;
	    for (int index_search_sys=0;index_search_sys<nb_sys_selected_object_all && index_search_sys<=index_sys;index_search_sys++) {
	      if (Return_object_given_systematic(vec_string_systematic_selected[index_search_sys])==string_object)
		index_sys_thematic++;
	      
	      if (index_search_sys==index_sys)
		break;
	    } //end loop on search syst
	    
	    if (string_sym_asym=="up") {
	      map_map_map_hist_rel_effect_modified_parameter_f_sym_asym_f_modified_parameter_f_thematic_f_process[index_sym_asym][string_modified_parameter][string_object][string_sample]->SetBinContent(index_sys_thematic+1,map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_up); //+1 for position due to histogram structure
	      map_map_map_hist_rel_effect_modified_parameter_f_sym_asym_f_modified_parameter_f_thematic_f_process[index_sym_asym][string_modified_parameter][string_object][string_sample]->SetBinError(index_sys_thematic+1,map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_up); //+1 for position due to histogram structure
	      //----------
	      //also, always fills the case "all"

	      map_map_map_hist_rel_effect_modified_parameter_f_sym_asym_f_modified_parameter_f_thematic_f_process[index_sym_asym][string_modified_parameter]["all"][string_sample]->SetBinContent(index_sys+1,map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_up); //+1 for position due to histogram structure
	      map_map_map_hist_rel_effect_modified_parameter_f_sym_asym_f_modified_parameter_f_thematic_f_process[index_sym_asym][string_modified_parameter]["all"][string_sample]->SetBinError(index_sys+1,map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_up); //+1 for position due to histogram structure
	    }
	    else if (string_sym_asym=="down") {
	      map_map_map_hist_rel_effect_modified_parameter_f_sym_asym_f_modified_parameter_f_thematic_f_process[index_sym_asym][string_modified_parameter][string_object][string_sample]->SetBinContent(index_sys_thematic+1,map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_down); //+1 for position due to histogram structure
	      map_map_map_hist_rel_effect_modified_parameter_f_sym_asym_f_modified_parameter_f_thematic_f_process[index_sym_asym][string_modified_parameter][string_object][string_sample]->SetBinError(index_sys_thematic+1,map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_down); //+1 for position due to histogram structure
	      //----------
	      //also, always fills the case "all"
	      map_map_map_hist_rel_effect_modified_parameter_f_sym_asym_f_modified_parameter_f_thematic_f_process[index_sym_asym][string_modified_parameter]["all"][string_sample]->SetBinContent(index_sys+1,map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_down); //+1 for position due to histogram structure
	      map_map_map_hist_rel_effect_modified_parameter_f_sym_asym_f_modified_parameter_f_thematic_f_process[index_sym_asym][string_modified_parameter]["all"][string_sample]->SetBinError(index_sys+1,map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_down); //+1 for position due to histogram structure

	      cout << "phase down=" << map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_down << endl;
	    }
	    else if (string_sym_asym=="sym") {
	      map_map_map_hist_rel_effect_modified_parameter_f_sym_asym_f_modified_parameter_f_thematic_f_process[index_sym_asym][string_modified_parameter][string_object][string_sample]->SetBinContent(index_sys_thematic+1,map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_sym); //+1 for position due to histogram structure
	      map_map_map_hist_rel_effect_modified_parameter_f_sym_asym_f_modified_parameter_f_thematic_f_process[index_sym_asym][string_modified_parameter][string_object][string_sample]->SetBinError(index_sys_thematic+1,map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_sym); //+1 for position due to histogram structure
	      //----------
	      //also, always fills the case "all"
	      map_map_map_hist_rel_effect_modified_parameter_f_sym_asym_f_modified_parameter_f_thematic_f_process[index_sym_asym][string_modified_parameter]["all"][string_sample]->SetBinContent(index_sys+1,map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_sym); //+1 for position due to histogram structure
	      map_map_map_hist_rel_effect_modified_parameter_f_sym_asym_f_modified_parameter_f_thematic_f_process[index_sym_asym][string_modified_parameter]["all"][string_sample]->SetBinError(index_sys+1,map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_sym); //+1 for position due to histogram structure

	      cout << "phase sym=" << map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_sym << endl;
	    }
	  } //end loop index sym asym
	} //end loop on processes
      } //end loop thematic
    } //end loop on modified parameter

  } //end loop on sys
  //=================================================================================================
  //Make the draw

  //to make a function ?

  cout << "make the draw of relative systematics" << endl;

  for (unsigned int index_modified_parameter=0;index_modified_parameter<vec_modified_parameter.size();index_modified_parameter++) {  
    string string_modified_parameter=vec_modified_parameter[index_modified_parameter];
    
    for (int index_thematic=0;index_thematic<nb_thematics;index_thematic++) {

      string string_object=vec_string_object[index_thematic];

      //      cout << "index_thematic=" << index_thematic << endl;
      //      cout << "corresponding string_object=" << string_object << endl;

      //to rename in nb_systematics_object ?

      if (string_object=="all")
	nb_systematics_object=nb_sys_selected_object_all;
      else if (string_object=="event_based")
	nb_systematics_object=nb_sys_selected_object_event_based;
      else if (string_object=="photon")
	nb_systematics_object=nb_sys_selected_object_photon;
      else if (string_object=="jet")
	nb_systematics_object=nb_sys_selected_object_jet;
      else if (string_object=="flavor_tagging")
	nb_systematics_object=nb_sys_selected_object_flavor_tagging;
      else if (string_object=="LEPTON_MET")
	nb_systematics_object=nb_sys_selected_object_LEPTON_MET;
      else if (string_object=="theory")
	nb_systematics_object=nb_sys_selected_object_theory;
      
      //cout << "nb_sys_selected_object_theory=" << nb_sys_selected_object_theory << endl;
      
      cout << "nb_systematics_object=" << nb_systematics_object << endl;

      if (!nb_systematics_object)
	continue;
      
      for (int index_process=0;index_process<nb_processes;index_process++) { //for all processes
	
	cout << "index_process=" << index_process << endl;
	
	TLegend legend(0.75,0.86,0.81,0.97);
	
	legend.SetTextSize(0.04);
	legend.SetBorderSize(2);
	legend.SetBorderSize(0);
	legend.SetLineColor(0);
	legend.SetLineWidth(0);
	legend.SetFillStyle(1001);
	legend.SetFillColor(kWhite);
	
	//TCanvas canvas("canvas","canvas",800,600);
	TCanvas canvas("canvas","canvas",1000,750); //reduce the blur
	canvas.SetTopMargin(0.02);
	
	if (string_object=="all")
	  canvas.SetBottomMargin(0.37);
	else if (string_object=="event_based")
	  canvas.SetBottomMargin(0.30);
	else if (string_object=="photon")
	  canvas.SetBottomMargin(0.32);
	else if (string_object=="jet")
	  canvas.SetBottomMargin(0.42);
	else if (string_object=="flavor_tagging")
	  canvas.SetBottomMargin(0.35);
	else if (string_object=="LEPTON_MET")
	  canvas.SetBottomMargin(0.37);
	else if (string_object=="theory") {
	  if (do_envelope_QCD || do_prescription_pdf_alpha_s) {
	    canvas.SetBottomMargin(0.08);
	  }
	  else
	    canvas.SetBottomMargin(0.15);
	}
	
	canvas.SetLeftMargin(0.13);
	canvas.SetRightMargin(0.01);
	
	TH1F hist_dummy("hist_dummy","hist_dummy",nb_systematics_object,0,nb_systematics_object);
	hist_dummy.SetLineColor(kBlack);
	hist_dummy.SetLineStyle(kDashed);

	bool found_theory=0;
	bool found_experimental=0;
	
	for (index_sys=0;index_sys<nb_sys_selected_object_all;index_sys++) {
	  
	  cout << "vec_string_systematic_selected[index_sys]=" << vec_string_systematic_selected[index_sys] << endl;
	  //	  cout << "A, Return_object_given_systematic(vec_string_systematic_selected[index_sys]=" << Return_object_given_systematic(vec_string_systematic_selected[index_sys]) << endl;
	  
	  if (Return_object_given_systematic(vec_string_systematic_selected[index_sys])=="theory" && (string_object=="all" || string_object=="theory")) {
	    found_theory=1;
	  }
	  else if (Return_object_given_systematic(vec_string_systematic_selected[index_sys])!="theory") {
	    found_experimental=1;
	  }
	}

	if (string_modified_parameter=="yield") {
	  
	  if (found_theory) {
	    hist_dummy.SetMinimum(-20);
	    hist_dummy.SetMaximum(20);
	  }
	  else {
	    hist_dummy.SetMinimum(-5);
	    hist_dummy.SetMaximum(5);
	  }
	} //end yield
	else { //15 is really a minimum : example EG_RESOLUTION
	  hist_dummy.SetMinimum(-20);
	  hist_dummy.SetMaximum(20);
	}

	string string_latex_modified_parameter;
	
	if (string_modified_parameter=="yield")
	  string_latex_modified_parameter="yield";
	else if (string_modified_parameter=="position_shape") {

	  if (string_method_syst_shape=="mean_interquartile") {
	    if (string_observable_shape=="m_yy")
	      string_latex_modified_parameter="<m_{#gamma#gamma}>";
	    else if (string_observable_shape=="m_bb")
	      string_latex_modified_parameter="<m_{bb}>";
	    else if (string_observable_shape=="m_yybb_tilde")
	      string_latex_modified_parameter="<m_{yybb tilde}>";
	  }
	  else {
	    if (string_observable_shape=="m_yy")
	      string_latex_modified_parameter="#mu_{CB}(m_{#gamma#gamma})";
	    else if (string_observable_shape=="m_bb")
	      string_latex_modified_parameter="#mu_{param}(m_{bb})";
	    else if (string_observable_shape=="m_yybb_tilde")
	      string_latex_modified_parameter="#mu_{param}(m_{yybb tilde})";
	  }
	}
	else if (string_modified_parameter=="spread_shape") {
	  if (string_observable_shape=="m_yy")
	    string_latex_modified_parameter="IQR_{0.25 ; 0.75}(m_{#gamma#gamma})";
	  else if (string_observable_shape=="m_bb")
	    string_latex_modified_parameter="IQR_{0.25 ; 0.75}(m_{bb})";
	  else if (string_observable_shape=="m_yybb_tilde")
	    string_latex_modified_parameter="IQR_{0.25 ; 0.75}(m_{yybb tilde})";
	}
	
	//	cout << "string_latex_modified_parameter=" << string_latex_modified_parameter << endl;
	
	string string_title="#frac{"+string_latex_modified_parameter+"^{var}}{"+string_latex_modified_parameter+"^{nom}} -1 [%]";
	
	hist_dummy.SetYTitle(string_title.c_str());
	
	//	cout << "vec_string_systematic.size()=" << vec_string_systematic.size() << endl;
	//	cout << "nb_sys_thematic_all=" << nb_sys_thematic_all << endl;
	
	//to rename index_sys_thematic in index_sys_in_current_thematic

	int index_sys_thematic=0;
	
	cout << "phase 4" << endl;

	for (index_sys=0;index_sys<nb_sys_selected_object_all;index_sys++) {
	  cout << "index_sys=" << index_sys << endl;
	  
	  cout << "string_object=" << string_object << endl;
	  cout << "vec_string_systematic_selected[index_sys]=" << vec_string_systematic_selected[index_sys] << endl;

	  if (string_object=="all" || Return_object_given_systematic(vec_string_systematic_selected[index_sys])==string_object) {
	    hist_dummy.GetXaxis()->SetBinLabel(index_sys_thematic+1,(Return_name_for_syst(vec_string_systematic_selected[index_sys])).c_str()); //+1 for position due to histogram structure
	    
	    index_sys_thematic++;
	  }
	}
	
	if (string_object=="all")
	  hist_dummy.GetXaxis()->SetLabelSize(0.025); //0.03 too big for all
	else if (string_object=="LEPTON_MET")
	  hist_dummy.GetXaxis()->SetLabelSize(0.025);
	else
	  hist_dummy.GetXaxis()->SetLabelSize(0.03); //0.03 too big for all

	hist_dummy.GetXaxis()->LabelsOption("v");
	
	hist_dummy.Draw();
	
	cout << "phase 7" << endl;

	for (index_sym_asym=0;index_sym_asym<3;index_sym_asym++) {

	  string string_sym_asym=vec_nature_syst_components_sym_asym[index_sym_asym];

	  if (vec_nature_syst_components_sym_asym[index_sym_asym]=="")
	    string_sym_asym="sym";
	  else if (vec_nature_syst_components_sym_asym[index_sym_asym]=="__1up")
	    string_sym_asym="up";
	  else if (vec_nature_syst_components_sym_asym[index_sym_asym]=="__1down")
	    string_sym_asym="down";

	  cout << "hello, index_sym_asym=" << index_sym_asym << ", string_sym_asym=" << string_sym_asym << endl;

	  cout << "found_theory=" << found_theory << endl;
	  cout << "found_experimental=" << found_experimental << endl;

	  //if theory only, skip up an down
	  if (found_theory && !found_experimental && string_sym_asym!="sym")
	    continue;
	  
	  cout << "index_sym_asym=" << index_sym_asym << endl;
	  cout << "string_modified_parameter=" << string_modified_parameter << endl;
	  cout << "string_object=" << string_object << endl;
	  cout << "string_sample=" << string_sample << endl;

	  map_map_map_hist_rel_effect_modified_parameter_f_sym_asym_f_modified_parameter_f_thematic_f_process[index_sym_asym][string_modified_parameter][string_object][string_sample]->Draw("hsame");
	  map_map_map_hist_rel_effect_modified_parameter_f_sym_asym_f_modified_parameter_f_thematic_f_process[index_sym_asym][string_modified_parameter][string_object][string_sample]->Draw("esame");
	  
	  legend.AddEntry(map_map_map_hist_rel_effect_modified_parameter_f_sym_asym_f_modified_parameter_f_thematic_f_process[index_sym_asym][string_modified_parameter][string_object][string_sample],string_sym_asym.c_str(),"lp");
	} //end loop on sym/asym
	
	cout << "phase 4" << endl;
	
	//-----
	//add separator of thematic for case all
	
	if (string_object=="all") {
	  TLine line;
	  line.SetLineStyle(kDashed);
	  
	  cout << "now, thematic=all" << endl;
	  
	  for (index_sys=0;index_sys<nb_sys_selected_object_all;index_sys++) {
	    
	    cout << "index_sys=" << index_sys << endl;
	    
	    if (index_sys>0 && Return_object_given_systematic(vec_string_systematic_selected[index_sys])!=Return_object_given_systematic(vec_string_systematic_selected[index_sys-1])) { //if change of thematic, put a separator
	      //	      cout << "index_sys=" << index_sys << ", vec_string_systematic_selected[index_sys]=" << vec_string_systematic_selected[index_sys] << ", thematic=" << Return_object_given_systematic(vec_string_systematic_selected[index_sys]) << endl;
	      
	      //when a thematic is new, we need to put it earlier to it : so the position is index_sys+1-1=index_sys
	      line.DrawLine(index_sys,hist_dummy.GetMinimum(),index_sys,hist_dummy.GetMaximum());
	    }
	  }
	} //all
	//-----
	//	TGaxis axis_top_contrib_err(canvas.GetUxmin(),canvas.GetUymax(),canvas.GetUxmax(),canvas.GetUymax(),hist_dummy.GetXaxis()->GetXmin(),hist_dummy.GetXaxis()->GetXmax(),510,"-LU");
	//	axis_top_contrib_err.Draw();
	
	legend.Draw();
	
	TLatex latex;
	latex.SetTextColor(kBlack);
	latex.SetNDC();
	//latex.SetTextSize(0.04); //0.045 is std
	//latex.SetTextFont(72);
	//latex.DrawLatex(horizontal_position,0.92,"ATLAS");
	//latex.SetTextFont(42); //put back the font
	//latex.DrawLatex(horizontal_position+0.1,0.92,"internal");
	
	latex.SetTextFont(42); //put back the font
	//latex.SetTextSize(0.025); //0.045 is std
	latex.SetTextSize(0.022); //0.045 is std

	latex.DrawLatex(0.18,0.94,string_category.c_str());
	latex.DrawLatex(0.18,0.89,string_sample.c_str());
	
	string string_canvas_saveas="results/plots_syst/";
	string_canvas_saveas+=string_modified_parameter;

	if (string_yield_shape=="shape") {
	  string_canvas_saveas+="_";
	  string_canvas_saveas+=string_observable_shape;
	}
	string_canvas_saveas+="_";
	string_canvas_saveas+=string_category;
	string_canvas_saveas+="_";
	string_canvas_saveas+=string_sample;
	string_canvas_saveas+="_";
	string_canvas_saveas+=string_object;
	string_canvas_saveas+=".png";
	
	canvas.SaveAs(string_canvas_saveas.c_str());
	
	//	canvas.SaveAs("test.C");
      } //end loop on process

    } //end loop on subthematic
  } //end loop on modified parameter
  
  
  }
  //to free memory
}
//#######################################################################################################################################################################################################
void prun_systematic_effect(double *ptr_rel_effect_up,
			    double *ptr_rel_effect_down,
			    double *ptr_rel_effect_sym,
			    double *ptr_err_rel_effect_up,
			    double *ptr_err_rel_effect_down,
			    double *ptr_err_rel_effect_sym)
{
  int nb_sigma=1;

  cout << "prun_systematic_effect" << endl;

  cout << "before applying it, one has " << endl;
  cout << "case_symmetric_syst=" << case_symmetric_syst << endl;
  cout << "up=" << (*ptr_rel_effect_up) << " +/- " << *ptr_err_rel_effect_up << endl;
  cout << "down=" << (*ptr_rel_effect_down) << " +/- " << *ptr_err_rel_effect_down << endl;
  cout << "sym=" << (*ptr_rel_effect_sym) << " +/- " << *ptr_err_rel_effect_sym << endl;
  
  //no more prun here for 0.1 %, because some tiny systematics, as pdf for example, could accumulate, else they would disappear artificially
  //	  ||
  //	  fabs((*ptr_rel_effect_sym))<THR_MIN_PRUNING // to put a prunning variable here 

  if (case_symmetric_syst) {
    if (
	(*ptr_rel_effect_sym)==0
	||
	(mode_skip_non_significative_systematics &&
	 
	 (
	  (*ptr_err_rel_effect_sym)>nb_sigma*fabs((*ptr_rel_effect_sym)) 
	  //no more prun here for 0.1 %, because some tiny systematics, as pdf for example, could accumulate, else they would disappear artificially
	  //	  ||
	  //	  fabs((*ptr_rel_effect_sym))<THR_MIN_PRUNING // to put a prunning variable here 
	  )
	 ) //valid because err is always positive
	) {
      *ptr_rel_effect_sym=0;
      *ptr_err_rel_effect_sym=0;
    }
  }
  else if ( !case_symmetric_syst) {
    if ( 
	(*ptr_rel_effect_up)==0
	||
	(
	 mode_skip_non_significative_systematics &&
	 (
	  (*ptr_err_rel_effect_up)>fabs((*ptr_rel_effect_up)) 
	  //	  ||
	  //	  fabs((*ptr_rel_effect_up))<THR_MIN_PRUNING // to put a prunning variable here 
	  )
	 ) //valid because err is always positive
	 ) { //non-significative effect
      *ptr_rel_effect_up=0;    //force to 0, for possible combination with other systematics
      *ptr_err_rel_effect_up=0;
    }

    if (
	(*ptr_rel_effect_down)==0
	||
	(
	 mode_skip_non_significative_systematics &&
	 ( 
	  (*ptr_err_rel_effect_down)>fabs((*ptr_rel_effect_down))
	  //no more prun here for 0.1 %, because some tiny systematics, as pdf for example, could accumulate, else they would disappear artificially
	  //	  ||
	  //	  fabs((*ptr_rel_effect_down))<THR_MIN_PRUNING // to put a prunning variable here 
	   )
	 ) //valid because err is always positive
	) { //non-significative effect
      *ptr_rel_effect_down=0;    //force to 0, for possible combination with other systematics
      *ptr_err_rel_effect_down=0;
    }
  }
  
  if (!case_symmetric_syst && ( (*ptr_rel_effect_up)!=0 || (*ptr_rel_effect_down)!=0) ) {

    *ptr_rel_effect_sym=sqrt( 0.5 * pow((*ptr_rel_effect_up),2) + 0.5 * pow((*ptr_rel_effect_down),2) );
    
    *ptr_err_rel_effect_sym=sqrt(pow(0.5*(*ptr_rel_effect_up)*(*ptr_err_rel_effect_up),2)+pow(0.5*(*ptr_rel_effect_down)*(*ptr_err_rel_effect_down),2))/((*ptr_rel_effect_sym));

    //remark : it is exactly the same to put the 0.5^2 within the sqrt
  }
  
  cout << "after applying it, one has " << endl;
  cout << "up=" << (*ptr_rel_effect_up) << " +/- " << *ptr_err_rel_effect_up << endl;
  cout << "down=" << (*ptr_rel_effect_down) << " +/- " << *ptr_err_rel_effect_down << endl;
  cout << "sym=" << (*ptr_rel_effect_sym) << " +/- " << *ptr_err_rel_effect_sym << endl;
}
//#######################################################################################################################################################################################################
void PrepareMergedSystematic(string string_sample,string string_category,vector<string> vec_string_systematic_selected)
{
  int nb_systematics_selected=vec_string_systematic_selected.size();

  for (index_sys=0;index_sys<nb_systematics_selected;index_sys++) { //for all systematics
    string string_systematic=vec_string_systematic_selected[index_sys];
    
    cout << "preparation of merged systematic for systematic : " << string_systematic << endl;
    string string_systematic_subthematic=Return_subthematic_given_systematic(string_systematic);
    
    //remove the loop
    for (int index_process=0;index_process<nb_processes;index_process++) { //for all processes
      
      //for up and down
      
      //thematic : symmetrize
      
      //formula for error is :
      //derivate : sqrt( 0.5 (up^2 + down^2) + ... + 0.5 (up^2 + down^2) )
      
      // sqrt   (    (0.5^2 up^2 delta_up^2 + 0.5^down^2 delta_down^2) )   /   ( sqrt( 0.5 (up^2 + down^2) + ... + 0.5 (up^2 + down^2) ) )
      //=sqrt   (    (0.5^2 up^2 delta_up^2 + 0.5^down^2 delta_down^2) /  ( 0.5 (up^2 + down^2) + ... + 0.5 (up^2 + down^2) )
      
      
      //since denominator is known only after the loop, need to compute parts (numerator and denominator), can only compute the numerator : the denominator will be applied at the end of the loop
      //remark : sqrt is made after the loop on systematics merging
      
      //for symmetric :
      
      //Fill the corresponding systematic per subthematic
      
      cout << "add the systematic in the summary per subthematic" << endl;
      
      if (mode_PrintResults_table_and_datacard) { //if the usage of this flag useful ?
	
	for (unsigned int index_modified_parameter=0;index_modified_parameter<vec_modified_parameter.size();index_modified_parameter++) {
	  
	  string string_modified_parameter=vec_modified_parameter[index_modified_parameter];
	  
	  cout << "string_systematic=" << string_systematic << ", string_systematic_subthematic" << string_systematic_subthematic << endl;

	  cout << "index_modified_parameter=" << index_modified_parameter << ", string_modified_parameter=" << string_modified_parameter << endl;

	  if (
	      map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_up
	      ) {
	    //example
	    //UP :   +9 -4
	    //DOWN : -5 +15
	    
	    //there is no bug : for subthematic, one adds the up and the down in the resulting up, and in the resulting down, and then symmetrize

	    if (string_systematic_subthematic=="JET_JES") {
	      cout << "will add " << map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_up << endl;
	      cout << "will add " << map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_down << endl;
	    
	      cout << "so far, rel_effect_up=" << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_up_f_category_f_process[index_process][string_category] << endl;
	    }
	    
	    map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_up_f_category_f_process[index_process][string_category]+=0.5*pow(map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_up,2);
	    map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_up_f_category_f_process[index_process][string_category]+=0.5*pow(map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_down,2);
	    
	    cout << "phase add in up : now, up=" << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_up_f_category_f_process[index_process][string_category] << endl;
	    
	    
	    cout << "string_systematic_subthematic=" << string_systematic_subthematic << endl;
	    cout << "string_modified_parameter=" << string_modified_parameter << endl;

	    cout << "string_category=" << string_category << endl;
	    cout << "index_process=" << index_process << endl;

	    cout << "map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_up_f_category_f_process[index_process][string_category]=" << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_up_f_category_f_process[index_process][string_category] << endl;
	    
	    map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_err_rel_effect_up_f_category_f_process[index_process][string_category]+=pow(0.5,2)*pow(map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_up,2)*pow(map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_up,2);
	    map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_err_rel_effect_up_f_category_f_process[index_process][string_category]+=pow(0.5,2)*pow(map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_down,2)*pow(map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_down,2); //yes, we add the down in the up for the thematic and we symmetrize afterwards
	    
	    map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_file_or_tree_exists_up_f_category_f_process[index_process][string_category]=1;
	  }

	  //non exclusive condition

	  if (
	      map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_down
	      ) {
	    map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_down_f_category_f_process[index_process][string_category]+=0.5*pow(map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_down,2);
	    map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_down_f_category_f_process[index_process][string_category]+=0.5*pow(map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_up,2);
	    
	    //	    cout << "phase add in down : now, down=" << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_down_f_category_f_process[index_process][string_category] << endl;

	    map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_err_rel_effect_down_f_category_f_process[index_process][string_category]+=pow(0.5,2)*pow(map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_down,2)*pow(map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_down,2);
	    map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_err_rel_effect_down_f_category_f_process[index_process][string_category]+=pow(0.5,2)*pow(map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_up,2)*pow(map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_up,2);  //yes, we add the up in the down for the thematic and we symmetrize afterwards
	    
	    //	    cout << "phase add in down : now, down=" << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_down_f_category_f_process[index_process][string_category] << endl;

	    map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_file_or_tree_exists_down_f_category_f_process[index_process][string_category]=1;
	  }



	  //non exclusive condition

	  if (
	      map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_sym
	      ) {
	    map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_sym_f_category_f_process[index_process][string_category]+=pow(map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_sym,2);
	    map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_err_rel_effect_sym_f_category_f_process[index_process][string_category]+=pow(map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_sym,2)*pow(map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_sym,2);
	    
	    cout << "inject sym central " << map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_sym << endl;
	    cout << "inject sym error " << map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_sym << endl;

	    map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_file_or_tree_exists_sym_f_category_f_process[index_process][string_category]=1;

	    cout << ", now, fill " << string_systematic_subthematic << " " << string_modified_parameter << ", map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_sym_f_category_f_process[index_process][string_category]=" << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_sym_f_category_f_process[index_process][string_category] << endl;
	  }
	  
	  
	} //end loop on modified parameter
      } //end mode print table

      //-----
    } //end loop on processes
  } //end loop on systematics

  //=========================================
  //put the final sqrt
  
  cout << "===================================" << endl;
  cout << "===================================" << endl;
  cout << "===================================" << endl;
  cout << "Systematic Subthematic" << endl;
    
  //at this stage, we already have the pointers
    
  string string_systematic_subthematic;
    
  for (int index_process=0;index_process<nb_processes;index_process++)
    for (int index_systematic_subthematic=0;index_systematic_subthematic<(int)vec_string_systematic_subthematic.size();index_systematic_subthematic++) {
	
      string_systematic_subthematic=vec_string_systematic_subthematic[index_systematic_subthematic];
	
      cout << "index_systematic_subthematic=" << index_systematic_subthematic << " string_systematic_subthematic=" << string_systematic_subthematic << endl;	
	
      //careful of communication of the subthematic systematics if same object
	
      for (unsigned int index_modified_parameter=0;index_modified_parameter<vec_modified_parameter.size();index_modified_parameter++) {
	  
	string string_modified_parameter=vec_modified_parameter[index_modified_parameter];

	cout << "string_modified_parameter=" << string_modified_parameter << endl;
	  
	//sqrt to add since in the loop, was adding the pow of various contributions
	  
	//pow was already done previously
	map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_up_f_category_f_process[index_process][string_category]=sqrt(map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_up_f_category_f_process[index_process][string_category]);
	  
	//pow was already done previously (sign is adjusted after the computation of the error, to prevent nan, and to make the most optimial way of computation)
	map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_down_f_category_f_process[index_process][string_category]=sqrt(map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_down_f_category_f_process[index_process][string_category]);
	  
	map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_sym_f_category_f_process[index_process][string_category]=sqrt(map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_sym_f_category_f_process[index_process][string_category]);


	cout << "resulting value up=" << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_up_f_category_f_process[index_process][string_category] << endl;	  
	cout << "resulting value down=" << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_down_f_category_f_process[index_process][string_category] << endl;
	cout << "resulting value sym=" << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_sym_f_category_f_process[index_process][string_category] << endl;
	  
	//	  cout << "HERE, rel up=" << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_up_f_category_f_process[index_process][string_category] << endl;
	if (map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_up_f_category_f_process[index_process][string_category]!=0)
	  map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_err_rel_effect_up_f_category_f_process[index_process][string_category]=sqrt(																								      map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_err_rel_effect_up_f_category_f_process[index_process][string_category]) / map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_up_f_category_f_process[index_process][string_category];
	//this is correct

	//note negative sign
	if (map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_down_f_category_f_process[index_process][string_category]!=0)
	  map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_err_rel_effect_down_f_category_f_process[index_process][string_category]=sqrt(
																									    map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_err_rel_effect_down_f_category_f_process[index_process][string_category]) / map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_down_f_category_f_process[index_process][string_category];

	cout << "map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_sym_f_category_f_process[index_process][string_category]=" << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_sym_f_category_f_process[index_process][string_category] << endl;
	cout << "map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_err_rel_effect_sym_f_category_f_process[index_process][string_category]=" << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_err_rel_effect_sym_f_category_f_process[index_process][string_category] << endl;

	if (map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_sym_f_category_f_process[index_process][string_category]!=0)
	  map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_err_rel_effect_sym_f_category_f_process[index_process][string_category]=sqrt(
																									   map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_err_rel_effect_sym_f_category_f_process[index_process][string_category]) / map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_sym_f_category_f_process[index_process][string_category]; //sqrt(numerator) / rel_effect
	  
	cout << "resulting err value up=" << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_err_rel_effect_up_f_category_f_process[index_process][string_category] << endl;	  
	cout << "resulting err value down=" << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_err_rel_effect_down_f_category_f_process[index_process][string_category] << endl;
	cout << "resulting err value sym=" << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_err_rel_effect_sym_f_category_f_process[index_process][string_category] << endl;
	  
	  
	  
	  
	cout << "phase thematic, string_modified_parameter=" << string_modified_parameter << ", up=" << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_up_f_category_f_process[index_process][string_category] << endl;
	  
	//force sign of down to -
	  
	map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_down_f_category_f_process[index_process][string_category]=-map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_down_f_category_f_process[index_process][string_category];
	  
	cout << "map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_up_f_category_f_process[index_process][string_category]=" << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_up_f_category_f_process[index_process][string_category] << endl;
	cout << "map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_down_f_category_f_process[index_process][string_category]=" << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_down_f_category_f_process[index_process][string_category] << endl;
	  
	  
	  
	cout << "conclusion" << endl;
	cout << "resulting value up=" << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_up_f_category_f_process[index_process][string_category] << endl;
	cout << "resulting value down=" << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_down_f_category_f_process[index_process][string_category] << endl;
	cout << "resulting value sym=" << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_sym_f_category_f_process[index_process][string_category] << endl;
	  
	cout << "err resulting value up=" << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_err_rel_effect_up_f_category_f_process[index_process][string_category] << endl;
	cout << "err resulting value down=" << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_err_rel_effect_down_f_category_f_process[index_process][string_category] << endl;
	cout << "err resulting value sym=" << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_err_rel_effect_sym_f_category_f_process[index_process][string_category] << endl;
	  
      } //end loop on modified parameter
	
    } //end loop on systematic subthematic
}
//#######################################################################################################################################################################################################
//to do : rename the parameter rel_

void PrintRepresentativeSystematic(string string_overview_subthematic,
				   string string_systematic,
				   FILE *fp_table,
				   FILE *fp_datacard,
				   double rel_effect_up,
				   double rel_effect_down,
				   double rel_effect_sym,
				   double err_rel_effect_up,
				   double err_rel_effect_down,
				   double err_rel_effect_sym)
{
  //in case effect is not significative, the datacard is not written

  cout << "in function PrintRepresentativeSystematic phase 1 for string_systematic=" << string_systematic << endl;

  cout << "string_systematic=" << string_systematic << ", case_symmetric_syst=" << case_symmetric_syst << endl;
  
  cout << "rel_effect_up=" << rel_effect_up << " +/- " << err_rel_effect_up << endl;
  cout << "rel_effect_down=" << rel_effect_down << " +/- " << err_rel_effect_down << endl;

  cout << "rel_effect_sym=" << rel_effect_sym << endl;
  cout << "err_rel_effect_sym=" << err_rel_effect_sym << endl;

  if ( (case_symmetric_syst && rel_effect_sym==0)
       ||
       (!case_symmetric_syst && rel_effect_up==0 && rel_effect_down==0)
       ||
       (
	mode_skip_non_significative_systematics
	&&
	(
	 ( case_symmetric_syst && err_rel_effect_sym>fabs(rel_effect_sym) )
	 ||
	 ( !case_symmetric_syst && ( err_rel_effect_up>fabs(rel_effect_up) || (err_rel_effect_down>fabs(rel_effect_down)) ) )
	 )
	)
       ) { //non-significative effect
    cout << "case non significative effect" << endl;
    fprintf(fp_table,"-");
  }
  
  //at this stage, effect is significative, but don't consider/print it necessary if it is tiny
  
  else if ( //below THR_MIN_PRUNING % effect: symmetrize it
	   ( case_symmetric_syst && fabs(rel_effect_sym)<THR_MIN_PRUNING )
	   ||
	   ( !case_symmetric_syst && ( fabs(rel_effect_up)<THR_MIN_PRUNING && ( (fabs(rel_effect_down)<THR_MIN_PRUNING) ) ) )
	    ) {
    cout << "below 0.1 \% effect\n" << endl;
    fprintf(fp_table,"$<%3.1f$",THR_MIN_PRUNING);
  }
  else { //above 0.1 % : consider it
    
    fprintf(fp_table,"$");

    cout << "PrintRepresentativeSystematic, above 0.1 %" << endl;
    cout << "string_systematic=" << string_systematic << endl;
    
    if (case_symmetric_syst || string_overview_subthematic=="overview_subthematic") {
      fprintf(fp_table,"\\pm %4.2f",rel_effect_sym);
      
      if (show_error_effect)
	fprintf(fp_table,"\\ %4.2f",err_rel_effect_sym);
    }
    else { //case asymmetric
      //cout << "case asym" << endl;
      
      if (do_symmetric_syst) {
	fprintf(fp_table,"\\pm %4.2f",sqrt(0.5*pow(rel_effect_up,2)+0.5*pow(rel_effect_down,2)));
	
	if (show_error_effect)
	  fprintf(fp_table,"\\ %4.2f",0.5*sqrt((pow(fabs(err_rel_effect_up),2)+pow(fabs(err_rel_effect_down),2))));
      }
      else {
	fprintf(fp_table,"^{");
	if (rel_effect_up>=0)
	  fprintf(fp_table,"+");
	
	//in case negative, it will print the sign automatically
	fprintf(fp_table,"%4.2f",rel_effect_up);
	
	if (show_error_effect)
	  fprintf(fp_table,"\\ %4.2f",err_rel_effect_up);
	
	fprintf(fp_table,"}");
	
	fprintf(fp_table,"_{");
	if (rel_effect_down>0)
	  fprintf(fp_table,"+");
	
	//in case negative, it will print the sign automatically
	fprintf(fp_table,"%4.2f",rel_effect_down);
	
	if (show_error_effect)
	  fprintf(fp_table,"\\ %4.2f",err_rel_effect_down);
	
	fprintf(fp_table,"}");
      } //end show asymmetric
      
    } //end case standard treatment
      
    fprintf(fp_table,"$");
    
    //    cout << "menu_systematics=" << menu_systematics << endl;
    
    //in case of symmetric, put the sign of the up systematic
    //fprintf(fp_datacard,"%s %4.2f\n",string_systematic.c_str(),rel_effect_sym);
    
    if (do_symmetric_syst || case_symmetric_syst) {
      
      if (fp_datacard) {
	
	if (rel_effect_sym>=THR_MIN_PRUNING) {
	  
	  fprintf(fp_datacard,"%s ",string_systematic.c_str());
	  
	  //put the sign of the up variation for example : this will manage the correlation among potential categories
	  
	  if (case_symmetric_syst)
	    ;
	  else {
	    if (rel_effect_up>=0)
	      fprintf(fp_datacard,"+");
	    else
	      fprintf(fp_datacard,"-");
	  }
	  
	  fprintf(fp_datacard,"%4.3f\n",rel_effect_sym);
	} //end not negligeable
      } //end fp_datacard
    }
    else { //case asymmetric syst
      
      if (fp_datacard) {
	
	if (fabs(rel_effect_up)>=THR_MIN_PRUNING || fabs(rel_effect_down)>THR_MIN_PRUNING) {
	  
	  fprintf(fp_datacard,"%s ",string_systematic.c_str());
	  
	  if (fabs(rel_effect_up)>=THR_MIN_PRUNING)
	    fprintf(fp_datacard,"%4.3f",rel_effect_up);
	  else
	    fprintf(fp_datacard,"0");
	  
	  if (fabs(rel_effect_down)>=THR_MIN_PRUNING)
	    fprintf(fp_datacard," %4.3f",rel_effect_down);
	  else
	    fprintf(fp_datacard," 0");
	  
	  fprintf(fp_datacard,"\n");
	  
	  //shit if ok fprintf(fp_datacard,"%s %4.3f %4.3f\n",string_systematic.c_str(),rel_effect_up,rel_effect_down);
	} //end case at least one component not negligeable
      } //end datacard exists
      
    } // end case effect significative
  } //end else

  cout << "end PrintRepresentativeSystematic" << endl;
  
  return;
}
//#######################################################################################################################################################################################################
void prevent_pathological_same_sign_syst(double *ptr_rel_effect_up,double *ptr_rel_effect_down)
{
  //sym not useful, but kept in case of change of algorithm

  if ((*ptr_rel_effect_up)*(*ptr_rel_effect_down)>0) { //if same sign and different to 0
    
    cout << "found case with same sign, rel_effect_up=" << *ptr_rel_effect_up << ", " << ", rel_effect_down=" << *ptr_rel_effect_down << endl;
    
    if (fabs(*ptr_rel_effect_up)>=fabs(*ptr_rel_effect_down)) //if up is higher or equal, change sign of down : conservative
      *ptr_rel_effect_down=-(*ptr_rel_effect_down);
    else
      *ptr_rel_effect_up=-(*ptr_rel_effect_up);
    
    //if equal, we don't care
  }
}
//#######################################################################################################################################################################################################
void config_subthematic_results::init_results(string string_category)
{
  //  cout << "init_results" << endl;

  for (int index_process=0;index_process<MAX_PROCESSES;index_process++) { //for all processes
    vec_rel_effect_up_f_category_f_process[index_process][string_category]=0.;
    vec_rel_effect_down_f_category_f_process[index_process][string_category]=0.;
    vec_rel_effect_sym_f_category_f_process[index_process][string_category]=0.;
    vec_err_rel_effect_up_f_category_f_process[index_process][string_category]=0.;
    vec_err_rel_effect_down_f_category_f_process[index_process][string_category]=0.;
    vec_err_rel_effect_sym_f_category_f_process[index_process][string_category]=0.;
    
    vec_file_or_tree_exists_up_f_category_f_process[index_process][string_category]=0;
    vec_file_or_tree_exists_down_f_category_f_process[index_process][string_category]=0;
    vec_file_or_tree_exists_sym_f_category_f_process[index_process][string_category]=0;
  }
}
//#######################################################################################################################################################################################################
void PrintTableSystematics_detail(string string_sample,FILE *fp_results_sys_details,string string_category,string string_yield_shape,string string_observable_shape,vector<string> vec_string_systematic_selected)
{
  int nb_systematics_selected=vec_string_systematic_selected.size();

  //remove the loop
  //-----------------------------------------------------------------------------------
  for (int index_process=0;index_process<nb_processes;index_process++) { //for all processes
    string string_datacard_syst_yield;
    string string_datacard_syst_position_shape;
    string string_datacard_syst_spread_shape;

    if (string_yield_shape=="yield") {
      string_datacard_syst_yield="datacard_";
      if (found_theory)
	string_datacard_syst_yield+="theory_";
      else if (found_experimental)
	string_datacard_syst_yield+="experimental_";
      string_datacard_syst_yield+="yield_";

      string_datacard_syst_yield+="proc_";
      string_datacard_syst_yield+=string_sample;
      string_datacard_syst_yield+="_cat_";
      string_datacard_syst_yield+=string_category;
      string_datacard_syst_yield+=".txt";
    }
    else if (string_yield_shape=="shape") {
      string_datacard_syst_position_shape+="datacard_";
      if (found_theory)
	string_datacard_syst_position_shape+="theory_";
      else if (found_experimental)
	string_datacard_syst_position_shape+="experimental_";
      string_datacard_syst_position_shape+="position_shape_";
      string_datacard_syst_position_shape+=string_observable_shape;
      string_datacard_syst_position_shape+="_";
      string_datacard_syst_position_shape+="proc_";
      string_datacard_syst_position_shape+=string_sample;
      string_datacard_syst_position_shape+="_cat_";
      string_datacard_syst_position_shape+=string_category;
      string_datacard_syst_position_shape+=".txt";
      //-----
      string_datacard_syst_spread_shape="datacard_";
      if (found_theory)
	string_datacard_syst_spread_shape+="theory_";
      else if (found_experimental)
	string_datacard_syst_spread_shape+="experimental_";
      string_datacard_syst_spread_shape+="spread_shape_";
      string_datacard_syst_spread_shape+=string_observable_shape;
      string_datacard_syst_spread_shape+="_";
      string_datacard_syst_spread_shape+="proc_";
      string_datacard_syst_spread_shape+=string_sample;
      string_datacard_syst_spread_shape+="_cat_";
      string_datacard_syst_spread_shape+=string_category;
      string_datacard_syst_spread_shape+=".txt";
      
      cout << "string_datacard_syst_position_shape=" << string_datacard_syst_position_shape << endl;
      cout << "string_datacard_syst_spread_shape=" << string_datacard_syst_spread_shape << endl;
    }
    
    //to open in any circumstance, since we are in a loop over systematics
    if (string_yield_shape=="yield") {
      fp_datacard_details_syst_yield_f_category_f_process[index_process][string_category]=fopen((string("results/datacards/details/")+string_datacard_syst_yield).c_str(),"wt");
      //not useful      fp_datacard_subthematic_syst_yield_f_category_f_process[index_process][string_category]=fopen((string("results/datacards/subthematic/")+string_datacard_syst_yield).c_str(),"wt");
      
      cout << "string_datacard_syst_yield.c_str()=" << string_datacard_syst_yield.c_str() << endl;
    }
    else if (string_yield_shape=="shape") {
      fp_datacard_details_syst_position_shape_f_category_f_process[index_process][string_category]=fopen((string("results/datacards/details/")+string_datacard_syst_position_shape).c_str(),"wt");
      fp_datacard_details_syst_spread_shape_f_category_f_process[index_process][string_category]=fopen((string("results/datacards/details/")+string_datacard_syst_spread_shape).c_str(),"wt");
      
      //not useful fp_datacard_subthematic_syst_position_shape_f_category_f_process[index_process][string_category]=fopen((string("results/datacards/subthematic/")+string_datacard_syst_position_shape).c_str(),"wt");
      //not useful fp_datacard_subthematic_syst_spread_shape_f_category_f_process[index_process][string_category]=fopen((string("results/datacards/subthematic/")+string_datacard_syst_spread_shape).c_str(),"wt");
    }
  }
  
  //=================================================================

  bool shown_syst_event_based=0;
  bool shown_syst_photons=0;
  bool shown_syst_jets=0;
  bool shown_syst_flavor_tagging=0;
  bool shown_syst_electron_muon_MET=0;
  bool shown_syst_theory=0;
  
  fprintf(fp_results_sys_details,"\\hline\n");
  
  for (index_sys=0;index_sys<nb_systematics_selected;index_sys++) { //for all systematics
    
    string string_systematic=vec_string_systematic_selected[index_sys];
    
    if (mode_PrintResults_table_and_datacard) {

      if (
	 (shown_syst_event_based==0 && Return_object_given_systematic(string_systematic)=="event_based")
	 ||
	 (shown_syst_photons==0 && Return_object_given_systematic(string_systematic)=="photon")
	  ||
	 (shown_syst_jets==0 && Return_object_given_systematic(string_systematic)=="jet")
	 ||
	 (shown_syst_flavor_tagging==0 && Return_object_given_systematic(string_systematic)=="flavor_tagging")
	 ||
	 (shown_syst_electron_muon_MET==0 && Return_object_given_systematic(string_systematic)=="LEPTON_MET")
	 ||
	 (shown_syst_theory==0 && Return_object_given_systematic(string_systematic)=="theory")
	 ) {
	fprintf(fp_results_sys_details,"\\hline\n");
	fprintf(fp_results_sys_details,"\\multirow{");
	
	if (shown_syst_event_based==0 && Return_object_given_systematic(string_systematic)=="event_based") {
	  shown_syst_event_based=1;
	  fprintf(fp_results_sys_details,"%d}{*}{Event-based}          ",nb_sys_selected_object_event_based);
	}
	else if (shown_syst_photons==0 && Return_object_given_systematic(string_systematic)=="photon") {
	  shown_syst_photons=1;
	  fprintf(fp_results_sys_details,"%d}{*}{Photon}          ",nb_sys_selected_object_photon);
	}
	else if (shown_syst_jets==0 && Return_object_given_systematic(string_systematic)=="jet") {
	  shown_syst_jets=1;
	  fprintf(fp_results_sys_details,"%d}{*}{Jet}          ",nb_sys_selected_object_jet);
	}
	else if (shown_syst_flavor_tagging==0 && Return_object_given_systematic(string_systematic)=="flavor_tagging") {
	  shown_syst_flavor_tagging=1;
	  fprintf(fp_results_sys_details,"%d}{*}{Flavour tagging}          ",nb_sys_selected_object_flavor_tagging);
	}
	else if (shown_syst_electron_muon_MET==0 && Return_object_given_systematic(string_systematic)=="LEPTON_MET") {
	  shown_syst_electron_muon_MET=1;
	  fprintf(fp_results_sys_details,"%d}{*}{Lepton+MET}          ",nb_sys_selected_object_LEPTON_MET);
	}
	else if (shown_syst_theory==0 && Return_object_given_systematic(string_systematic)=="theory") {
	  shown_syst_theory=1;
	  fprintf(fp_results_sys_details,"%d}{*}{Theory}          ",nb_sys_selected_object_theory);
	}
      } //end case start of a new thematic
      else {
	fprintf(fp_results_sys_details,"                                 ");
      }
      
      fprintf(fp_results_sys_details,"\\rule[-1.ex]{0pt}{3.5ex}"); //add a bit of vertical space so that the exposant and indice are not on the line ; skipped the \\strut command, because too separated
      
      fprintf(fp_results_sys_details,"&");
      
      fprintf(fp_results_sys_details,"\\verb|%s|\t",(Return_name_for_syst(vec_string_systematic_selected[index_sys])).c_str());
      
    } //end mode Print

    //remove the loop
    for (int index_process=0;index_process<nb_processes;index_process++) { //for all processes

      //===================================================================================================

      //===================================================================================================
      if (mode_PrintResults_table_and_datacard)
	fprintf(fp_results_sys_details,"&");
      //-----------------------------------------------
      //printing of the representative systematic
      
      //relative effect should be signed
      
      //TO DO : FACTORIZE ?

      if (mode_PrintResults_table_and_datacard) {
	
	FILE *fp_datacard_current_result=0;

	for (unsigned int index_modified_parameter=0;index_modified_parameter<vec_modified_parameter.size();index_modified_parameter++) {
	  
	  string string_modified_parameter=vec_modified_parameter[index_modified_parameter];
	  
	  if (string_modified_parameter=="yield")
	    fp_datacard_current_result=fp_datacard_details_syst_yield_f_category_f_process[index_process][string_category];
	  else if (string_modified_parameter=="position_shape")
	    fp_datacard_current_result=fp_datacard_details_syst_position_shape_f_category_f_process[index_process][string_category];
	  else if (string_modified_parameter=="spread_shape")
	    fp_datacard_current_result=fp_datacard_details_syst_spread_shape_f_category_f_process[index_process][string_category];

	  cout << "-----" << endl;
	  cout << "string_systematic=" << string_systematic << endl;
	  cout << "map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_up=" << map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_up << endl;
	  cout << "map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_down=" << map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_down << endl;
	  cout << "map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_sym=" << map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_sym << endl;

	  cout << "map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_up=" << map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_up << endl;
	  cout << "map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_down=" << map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_down << endl;
	  cout << "map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_up=" << map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_up << endl;
	  cout << "map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_down=" << map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_down << endl;
	  cout << "map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_sym=" << map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_sym << endl;
	  
	  //if file does not exist, do not store it
	  if (
	      (
	       Return_object_given_systematic(string_systematic)=="theory" && !map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_sym)
	      || 
	      (Return_object_given_systematic(string_systematic)!="theory" && (!map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_up || !map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].file_or_tree_exists_up) )
	      ) {
	    if (string_modified_parameter=="yield") {
	      cout << "string_systematic=" << string_systematic << endl;
	      cout << "Return_object_given_systematic(string_systematic)=" << Return_object_given_systematic(string_systematic) << endl;
	      fprintf(fp_results_sys_details,"n/a");
	    }
	    else if ( (string_modified_parameter=="position_shape" || string_modified_parameter=="spread_shape") ) {
	      fprintf(fp_results_sys_details,"n/a");

	      if (string_modified_parameter=="position_shape")
		fprintf(fp_results_sys_details," &");
	    }
	  }
	  else {
	    PrintRepresentativeSystematic("",
					  //menu_systematics,
					  string_systematic,
					  fp_results_sys_details,
					  fp_datacard_current_result,
					  map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_up,
					  map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_down,
					  map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].rel_effect_sym,
					  map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_up,
					  map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_down,
					  map_map_map_selected_rel_effect_modified_parameter_f_systematic_f_modified_parameter_f_process[string_systematic][string_modified_parameter][string_sample].err_rel_effect_sym);

	    if (string_modified_parameter=="position_shape") //put a separator just after
	      fprintf(fp_results_sys_details," &");
	  }
	} //end loop on modified parameter

	fprintf(fp_results_sys_details,"\t");	
      } //end print table
      
      //-----
    } //end loop on processes
    
    if (mode_PrintResults_table_and_datacard) {
      fprintf(fp_results_sys_details,"\\\\\n");
      fprintf(fp_results_sys_details,"\\cline{2-");
      
      //for details, there are two columns (one for thematic, one for systematic), plus one column for yield, and two columns for shape

      if (string_yield_shape=="shape")
	fprintf(fp_results_sys_details,"%d}\n",2+nb_processes*2);
      else
	fprintf(fp_results_sys_details,"%d}\n",nb_processes+2);
    } //end mode print
    
    //    fprintf(fp_results_sys_details,"\\hline\n");
  } //end loop on systematics
  
  string string_latex_category;

  //to do : move at a better more intuitive place ?

  //TO GENERALIZE FOR SUBTHEMATIC AS WELL ?
  if (mode_PrintResults_table_and_datacard) {
    fprintf(fp_results_sys_details,"\\hline\n");
    fprintf(fp_results_sys_details,"\\end{tabular}\n");
    fprintf(fp_results_sys_details,"\\end{center}\n");
    fprintf(fp_results_sys_details,"\\vspace{-0.5cm}\n");
    
    string_latex_category=string_category;
    
    size_t start_pos = 0;
    string string_to_change="_";
    string string_changed="\\_";
    
    while ((start_pos=string_latex_category.find(string_to_change,start_pos))!=string::npos) {
      string_latex_category.replace(start_pos,string_to_change.length(),string_changed);
      start_pos+=string_changed.length();
    }
    
    fprintf(fp_results_sys_details,"\\caption{Summary of dominant systematic uncertainties affecting expected yields or shape parameters after the selection of the category \\textrm{%s}. Sources marked ~-~ and other sources not listed in the table are negligible by comparison. No systematic uncertainties related to the continuum background are considered, since this is derived through a fit to the observed data.}\n",string_latex_category.c_str());

    fprintf(fp_results_sys_details,"\\label{table_systematics_details}\n");
    
    fprintf(fp_results_sys_details,"\\end{table}\n");
    fclose(fp_results_sys_details);
  } //end print table
  //-------------------------
}
//#######################################################################################################################################################################################################
void PrintTableSystematics_subthematic(string string_sample,FILE *fp_results_sys_subthematic,string string_category,string string_yield_shape,string string_observable_shape)
{ 
  cout << "Systematics_Yield_Shape.C : PrintTableSystematics_subthematic" << endl;


  /*
  //datacard subthematic not useful  
  for (int index_process=0;index_process<nb_processes;index_process++) { //for all processes
    string string_datacard_syst_yield;
    string string_datacard_syst_position_shape;
    string string_datacard_syst_spread_shape;
    
    if (string_yield_shape=="yield") {
      string_datacard_syst_yield="datacard_yield_";
      string_datacard_syst_yield+="proc_";
      string_datacard_syst_yield+=string_sample;
      string_datacard_syst_yield+="_cat_";
      string_datacard_syst_yield+=string_category;
      string_datacard_syst_yield+=".txt";
    }
    else if (string_yield_shape=="shape") {
      string_datacard_syst_position_shape+="datacard_position_shape_";
      string_datacard_syst_position_shape+="proc_";
      string_datacard_syst_position_shape+=string_sample;
      string_datacard_syst_position_shape+="_cat_";
      string_datacard_syst_position_shape+=string_category;
      string_datacard_syst_position_shape+=".txt";
      //-----
      string_datacard_syst_spread_shape="datacard_spread_shape_";
      string_datacard_syst_spread_shape+=string_observable_shape;
      string_datacard_syst_spread_shape+="_";
      string_datacard_syst_spread_shape+="proc_";
      string_datacard_syst_spread_shape+=string_sample;
      string_datacard_syst_spread_shape+="_cat_";
      string_datacard_syst_spread_shape+=string_category;
      string_datacard_syst_spread_shape+=".txt";
      //      cout << "string_datacard_syst_position_shape=" << string_datacard_syst_position_shape << endl;
      //      cout << "string_datacard_syst_spread_shape=" << string_datacard_syst_spread_shape << endl;
    }
    
    //to open in any circumstance, since we are in a loop over systematics
    if (string_yield_shape=="yield") {
      fp_datacard_subthematic_syst_yield_f_category_f_process[index_process][string_category]=fopen((string("results/datacards/subthematic/")+string_datacard_syst_yield).c_str(),"wt");
    }
    else if (string_yield_shape=="shape") {
      fp_datacard_subthematic_syst_position_shape_f_category_f_process[index_process][string_category]=fopen((string("results/datacards/subthematic/")+string_datacard_syst_position_shape).c_str(),"wt");
      fp_datacard_subthematic_syst_spread_shape_f_category_f_process[index_process][string_category]=fopen((string("results/datacards/subthematic/")+string_datacard_syst_spread_shape).c_str(),"wt");
    }
  }
  */
  
  //end case print header table and prepare datacards    
  
  cout << "summary for subthematic " << endl;
  
  for (int index_systematic_subthematic=0;index_systematic_subthematic<(int)vec_string_systematic_subthematic.size();index_systematic_subthematic++) {
    
    if (found_theory && (vec_string_systematic_subthematic[index_systematic_subthematic]!="QCD" && vec_string_systematic_subthematic[index_systematic_subthematic]!="PDF_alpha_s"))
      continue;
    
    if (found_experimental && (vec_string_systematic_subthematic[index_systematic_subthematic]=="QCD" || vec_string_systematic_subthematic[index_systematic_subthematic]=="PDF_alpha_s"))
      continue;
    
    string string_systematic_subthematic=vec_string_systematic_subthematic[index_systematic_subthematic];
    
    cout << "index_systematic_subthematic=" << index_systematic_subthematic << ", string_systematic_subthematic=" << string_systematic_subthematic << endl;
    
    //first line of each block per object
    
    //restrict to first of each thematic
    //to improve concept of thematic : subthematic ?
    
    //to improve in case does not start at the first of the subthematic

    if (string_systematic_subthematic=="PRW" || string_systematic_subthematic=="PH_PES" || string_systematic_subthematic=="JET_JES" || string_systematic_subthematic=="FT_EFF_B" || string_systematic_subthematic=="EL_EFF" || string_systematic_subthematic=="QCD") { //only first element of various thematic
      
      fprintf(fp_results_sys_subthematic,"\\hline\n");
      
      //hard-coded #lines for sure : does not depend on sources systematics but on number of destination systematics
      if (string_systematic_subthematic=="PRW")
	fprintf(fp_results_sys_subthematic,"\\multirow{2}{*}{Event-based}    ");
      else if (string_systematic_subthematic=="PH_PES")
	fprintf(fp_results_sys_subthematic,"\\multirow{4}{*}{Photon}         ");
      else if (string_systematic_subthematic=="JET_JES")
	fprintf(fp_results_sys_subthematic,"\\multirow{3}{*}{Jet}            ");
      else if (string_systematic_subthematic=="FT_EFF_B")
	fprintf(fp_results_sys_subthematic,"\\multirow{3}{*}{Flavour tagging}");
      else if (string_systematic_subthematic.find("EL_EFF")!=string::npos)
	fprintf(fp_results_sys_subthematic,"\\multirow{5}{*}{Lepton+MET}");
      else if (string_systematic_subthematic=="QCD")
	fprintf(fp_results_sys_subthematic,"\\multirow{3}{*}{Theory}");
    }
    else
      fprintf(fp_results_sys_subthematic,"                                 ");
    
    fprintf(fp_results_sys_subthematic,"\\rule[-1.ex]{0pt}{3.5ex}"); //add a bit of vertical space so that the exposant and indice are not on the line ; skipped the \\strut command, because too separated
    
    fprintf(fp_results_sys_subthematic,"&");
    fprintf(fp_results_sys_subthematic,"\\verb|%s|\t",string_systematic_subthematic.c_str());
    
    for (int index_process=0;index_process<nb_processes;index_process++) { //for all processes
      
      cout << "index_process=" << index_process << endl;
      
      fprintf(fp_results_sys_subthematic,"&");
      
      for (unsigned int index_modified_parameter=0;index_modified_parameter<vec_modified_parameter.size();index_modified_parameter++) {
	
	string string_modified_parameter=vec_modified_parameter[index_modified_parameter];
	
	if (do_prun
	    &&
	    (
	     map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_file_or_tree_exists_up_f_category_f_process[index_process][string_category]==1
	     ||
	     map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_file_or_tree_exists_down_f_category_f_process[index_process][string_category]==1
	     )
	    ) {
	  cout << "prun of modified parameter " << string_modified_parameter << endl;
	  
	  prun_systematic_effect(&map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_up_f_category_f_process[index_process][string_category],
				 &map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_down_f_category_f_process[index_process][string_category],
				 &map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_sym_f_category_f_process[index_process][string_category],
				 &map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_err_rel_effect_up_f_category_f_process[index_process][string_category],
				 &map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_err_rel_effect_down_f_category_f_process[index_process][string_category],
				 &map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_err_rel_effect_sym_f_category_f_process[index_process][string_category]
				 );
	  
	}
      } //end loop on modified parameter
      
      for (unsigned int index_modified_parameter=0;index_modified_parameter<vec_modified_parameter.size();index_modified_parameter++) {
	
	string string_modified_parameter=vec_modified_parameter[index_modified_parameter];
	
	/*not useful
	FILE *fp_datacard_current_result=0;
	
	if (string_modified_parameter=="yield")
	  fp_datacard_current_result=fp_datacard_subthematic_syst_yield_f_category_f_process[index_process][string_category];
	else if (string_modified_parameter=="position_shape")
	  fp_datacard_current_result=fp_datacard_subthematic_syst_position_shape_f_category_f_process[index_process][string_category];
	else if (string_modified_parameter=="spread_shape")
	  fp_datacard_current_result=fp_datacard_subthematic_syst_spread_shape_f_category_f_process[index_process][string_category];
	*/
	
	
	
	
	cout << "information rel_effect_up for modified parameter=" << string_modified_parameter << ", " << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_up_f_category_f_process[index_process][string_category] << endl;
	
	cout << "information rel_effect_down for modified parameter=" << string_modified_parameter << ", " << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_down_f_category_f_process[index_process][string_category] << endl;
	
	cout << "information err_rel_effect_up for modified parameter=" << string_modified_parameter << ", " << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_err_rel_effect_up_f_category_f_process[index_process][string_category] << endl;
	cout << "information err_rel_effect_down for modified parameter=" << string_modified_parameter << ", " << map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_err_rel_effect_down_f_category_f_process[index_process][string_category] << endl;
	
	if (
	    ((string_systematic_subthematic=="QCD" || string_systematic_subthematic=="PDF_alpha_s") && map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_file_or_tree_exists_sym_f_category_f_process[index_process][string_category]==1)
	    ||
	    (
	     string_systematic_subthematic!="QCD"
	     &&
	     (
	      (map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_file_or_tree_exists_up_f_category_f_process[index_process][string_category]==1)
	      ||
	      (map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_file_or_tree_exists_down_f_category_f_process[index_process][string_category]==1)
	      )
	     )
	    ) {
	  PrintRepresentativeSystematic("overview_subthematic",
					//menu_systematics,
					string_systematic_subthematic,
					fp_results_sys_subthematic,
					0,
					//					fp_datacard_current_result,
					map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_up_f_category_f_process[index_process][string_category],
					map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_down_f_category_f_process[index_process][string_category],
					map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_rel_effect_sym_f_category_f_process[index_process][string_category],
					
					map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_err_rel_effect_up_f_category_f_process[index_process][string_category],
					map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_err_rel_effect_down_f_category_f_process[index_process][string_category],
					map_config_results_f_subthematic_f_modified_parameter[string_systematic_subthematic][string_modified_parameter].vec_err_rel_effect_sym_f_category_f_process[index_process][string_category]
					);
	  
	  if (string_modified_parameter=="position_shape")
	    fprintf(fp_results_sys_subthematic," &");
	}
	else {
	  if (string_modified_parameter=="yield")
	    fprintf(fp_results_sys_subthematic,"n/a");
	  else if ( (string_modified_parameter=="position_shape" || string_modified_parameter=="spread_shape") ) {
	    
	    fprintf(fp_results_sys_subthematic,"n/a");
	    
	    if (string_modified_parameter=="position_shape")
	      fprintf(fp_results_sys_subthematic," &");
	  }
	}
      } //end loop on systematic thematic	
      
      fprintf(fp_results_sys_subthematic,"\t");
    } //end loop on process
    
    fprintf(fp_results_sys_subthematic,"\\\\\n");
    //      fprintf(fp_results_sys_subthematic,"\\hline\n");
    
  } //end loop on subthematic
  
  fprintf(fp_results_sys_subthematic,"\\hline\n");
  fprintf(fp_results_sys_subthematic,"\\end{tabular}\n");
  fprintf(fp_results_sys_subthematic,"\\end{center}\n");
  fprintf(fp_results_sys_subthematic,"\\vspace{-0.5cm}\n");
  
  string string_latex_category=string_category;
  
  size_t start_pos = 0;
  string string_to_change="_";
  string string_changed="\\_";
  
  while ((start_pos=string_latex_category.find(string_to_change,start_pos))!=string::npos) {
    string_latex_category.replace(start_pos,string_to_change.length(),string_changed);
    start_pos+=string_changed.length();
  }
  
  fprintf(fp_results_sys_subthematic,"\\caption{Summary of dominant ");
  
  if (found_theory)
    fprintf(fp_results_sys_subthematic,"theoretical ");
  else
    fprintf(fp_results_sys_subthematic,"experimental ");
  
  fprintf(fp_results_sys_subthematic,"systematic uncertainties affecting expected %s after the selection of the category \\textrm{%s}. Sources marked ~-~ are not significant.}\n",string_yield_shape.c_str(),string_latex_category.c_str());
  
  string string_label="\\label{table_";
  if (found_theory)
    string_label+="theoretical";
  else
    string_label+="experimental";
  string_label+="_systematics_thematic_";
  string_label+=string_yield_shape;
  string_label+="_";
  string_label+=string_sample; //clumsy because currently, there could be several processes

  string_label+="_";
  string_label+=string_category;
  string_label+="}\n";
  
  fprintf(fp_results_sys_subthematic,"%s",string_label.c_str());
  fprintf(fp_results_sys_subthematic,"\\end{table}\n");
  
  fclose(fp_results_sys_subthematic);
  
  if (mode_PrintResults_table_and_datacard) {
    cout << "close the file datacard subthematic" << endl;

    //loop not useful
    for (int index_process=0;index_process<nb_processes;index_process++) { //for all processes
      
      if (string_yield_shape=="yield") {
	//not useful fclose(fp_datacard_subthematic_syst_yield_f_category_f_process[index_process][string_category]);
	fclose(fp_datacard_details_syst_yield_f_category_f_process[index_process][string_category]);
      }
      else if (string_yield_shape=="shape") {
	cout << "close the file for shape" << endl;
	fclose(fp_datacard_details_syst_position_shape_f_category_f_process[index_process][string_category]);
	fclose(fp_datacard_details_syst_spread_shape_f_category_f_process[index_process][string_category]);
	cout << "closed the file for shape" << endl;
      }
    }
  }
  
}
//#######################################################################################################################################################################################################
