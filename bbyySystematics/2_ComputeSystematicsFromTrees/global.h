#ifndef GLOBAL_H
#define GLOBAL_H

#define MAX_PROCESSES 4

//above : shit ?

//-----------------------------------
string string_path="/sps/atlas/e/escalier/ATLAS_HGam/";

string string_rel_path_yield="Outputs_syst_yield_shape/";
string string_rel_path_shape="Outputs_syst_yield_shape/";

int mode_yield_MakeAndStoreFits=1;
int mode_yield_ReadFits_previously_made=1;

TFile *file_syst;
string suffix_asymmetry_systematic;
int nb_processes=0;

bool do_EGamma_1NP=1;

int correlation_full1_partial2;

vector<string> vec_nature_syst_components_sym_asym={"","__1up","__1down"}; //some systematics have a symmetric split, some others not

int index_sym_asym;

bool file_or_tree_exists_up=0;
bool file_or_tree_exists_down=0;
bool file_or_tree_exists_sym=0;

//- - - - - - - - - - -
//for computing error with fully correlated events (encoded in SF)
double nb_sel_nominal; double err_nb_sel_nominal;
double nb_sel_sys; double err_nb_sel_sys;
//- - - - - - - - - - -
//for computing error with partially correlated events (not encoded in SF)
double nb_sel_uncommon_part_nominal;
double nb_sel_common_part_nominal;
double nb_sel_uncommon_part_sys;

double err_nb_sel_common_part_nominal;
double err_nb_sel_uncommon_part_nominal;

double err_nb_sel_uncommon_part_sys;

int nb_sel_nominal_unweighted;
int nb_sel_sys_unweighted;
int nb_sel_uncommon_part_nominal_unweighted;
int nb_sel_uncommon_part_sys_unweighted;

TFile *file_nominal_bootstrap;
TFile *file_syst_bootstrap;

double rel_effect_yield=0;
double err_rel_effect_yield=0;
//---------------------------
//helping variables

bool found_theory=0; //do not change this flag
bool found_experimental=0; //do not change this flag


//-----------------------------------------------
class config_subthematic_results
{
 public:
  map<string,bool> vec_file_or_tree_exists_up_f_category_f_process[MAX_PROCESSES];
  map<string,bool> vec_file_or_tree_exists_down_f_category_f_process[MAX_PROCESSES];
  map<string,bool> vec_file_or_tree_exists_sym_f_category_f_process[MAX_PROCESSES];

  //all effects are expressed in percent
  
  map<string,double> vec_rel_effect_up_f_category_f_process[MAX_PROCESSES];
  map<string,double> vec_rel_effect_down_f_category_f_process[MAX_PROCESSES];
  map<string,double> vec_rel_effect_sym_f_category_f_process[MAX_PROCESSES];
  map<string,double> vec_err_rel_effect_up_f_category_f_process[MAX_PROCESSES];
  map<string,double> vec_err_rel_effect_down_f_category_f_process[MAX_PROCESSES];
  map<string,double> vec_err_rel_effect_sym_f_category_f_process[MAX_PROCESSES];

  void init_results(string string_category);
};
#endif
