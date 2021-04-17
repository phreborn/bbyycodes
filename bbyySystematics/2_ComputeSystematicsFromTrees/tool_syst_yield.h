#ifndef TOOL_SYST_YIELD_H
#define TOOL_SYST_YIELD_H

#include <RooMinimizer.h>
#include <Math/MinimizerOptions.h>

#include <string>
using namespace std;

//to put string_sample in the class ?

class tool_syst_yield
{
 public:
  //-----------------------
  //methods

  int ComputeSystematicYield_bootstrap(string string_sample,string string_category,string string_observable,string string_MxAOD,string string_systematic,int index_start_toy_bootstrap,int index_stop_toy_bootstrap);

  bool GetTreesYield(string string_sample,string string_category,string string_MxAOD,string string_systematic,TTree **pptr_tree_nominal,TTree **pptr_tree_syst);

  void ConstructTreeForBootStrap(string string_category,string string_MxAOD,string string_systematic,string string_nominal_bootstrap,TTree *tree_original,TTree **pptr_tree_bootstrap);

  void ComputeSystematicsYield(string string_sample,string string_category,string string_MxAOD,string string_systematic,int index_toy,TTree *local_tree_nominal,TTree *local_tree_syst);

  void ComputeAndPlot_Syst_yield_From_Mean_and_Interquartile(string string_sample,string string_category,string string_MxAOD,string string_systematic,string string_finalDV,int index_toy,TTree *current_tree_nominal,TTree *current_tree_syst);
  
  void StoreResults(string string_category,string string_MxAOD,string string_systematic);

  void PlotYieldResults_current_systematic(string string_sample,string string_category,string string_MxAOD,string string_systematic,int index_toy);

  void Plot_pseudo_experiments(string string_sample,string string_category,string string_MxAOD,string string_systematic,int local_index_sym_asym,string string_observable,TH1F *hist_rel_effect,double local_rel_effect,double local_err_rel_effect);

  void LoadTreeBootStrap(string string_category,string string_campaign_MxAOD,string string_systematic,string string_nominal_systematic);
  //-----------------------
  //configuration
  
  string string_functional_form;

  //bootstrap, etc.
  
  string string_method_partition_events;

  string string_method_syst_yield; //do not change it : it will be filled either by "mean_IQR" or "fit"
  //-----------------------
  //inputs

  //shit  RooAbsData *absdata_nominal=0;
  
  TTree *tree_original_nominal;

  TTree *tree_nominal;
  TTree *tree_syst;

  TTree *tree_nominal_bootstrap;
  TTree *tree_syst_bootstrap;

  RooAbsData *absdata_syst=0;
  
  string string_process;
  //-----------------------
  //observables

  //histogram used for choosing the initial parameters of the functional form, the extension of the fit, etc.
  TH1F *hist_nominal;
  TH1F *hist_syst;

  //shit  TH1F *hist_nominal_fine_bins;


  /*shit
  //-----------------------
  //helper to get the results

  bool ParamAtLimit_nominal;
  bool ParamAtLimit_syst;
  */

  vector<int> vec_index_toy;
  //-------------------------------------------
  vector<float> vec_result_rel_effect_yield;
  
  vector<float> vec_mean_nominal;
  vector<float> vec_err_mean_nominal;
  vector<float> vec_mean_syst;
  vector<float> vec_err_mean_syst;


  int nb_toys;
  
  //but probably could be improved
  
  unsigned int nb_toys_done; //to keep

  //shit  unsigned int nb_toys_converged;

  int nb_bins_histogram_yield;
  int extension_low_histogram_yield;
  int extension_high_histogram_yield;

  int index_start_toy_bootstrap,index_stop_toy_bootstrap;

};

#endif
