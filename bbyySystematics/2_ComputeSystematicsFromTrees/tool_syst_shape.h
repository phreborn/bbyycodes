#ifndef TOOL_SYST_SHAPE_H
#define TOOL_SYST_SHAPE_H

#include <RooMinimizer.h>
#include <Math/MinimizerOptions.h>

#include <string>
using namespace std;

//to put string_sample in the class ?

class tool_syst_shape
{
 public:
  //-----------------------
  //methods

  void configure(string string_sample,string string_observable,string string_MxAOD);
  void configure_bootstrap(int index_start_toy,int index_stop_toy);

  int ComputeSystematicShape_classical_jacknife_bootstrap(string string_sample,string string_category,string string_observable,string string_MxAOD,string string_systematic,int index_start_toy_bootstrap,int index_stop_toy_bootstrap);

  bool GetTreesShape(string string_sample,string string_category,string string_MxAOD,string string_systematic,TTree **pptr_tree_nominal,TTree **pptr_tree_syst);

  void ConstructTreeForBootStrap(string string_category,string string_MxAOD,string string_systematic,string string_nominal_bootstrap,TTree *tree_original,TTree **pptr_tree_bootstrap);
  //void LoadTreeBootStrap(string string_category,string string_systematic,string string_nominal_systematic);
  void LoadTreeBootStrap(string string_category,string string_campaign_MxAOD,string string_systematic,string string_nominal_systematic);

  void ComputeSystematicsShape(string string_sample,string string_category,string string_MxAOD,string string_systematic,int index_toy,TTree *local_tree_nominal,TTree *local_tree_syst);

  void ComputeAndPlot_Syst_shape_From_Mean_and_Interquartile(string string_sample,string string_category,string string_MxAOD,string string_systematic,string string_finalDV,int index_toy,TTree *current_tree_nominal,TTree *current_tree_syst);
  
  void StoreResults(string string_category,string string_MxAOD,string string_systematic);

  void PlotShapeResults_current_systematic(string string_sample,string string_category,string string_MxAOD,string string_systematic,int index_toy);

  void Plot_pseudo_experiments(string string_sample,string string_category,string string_MxAOD,string string_systematic,int local_index_sym_asym,string string_observable,TH1D *hist_rel_effect,double local_rel_effect,double local_err_rel_effect);
  
  bool IsRooRealVarAtLimit(RooRealVar *roorealvar);
  //-----------------------
  //configuration
  
  string string_functional_form;

  //bootstrap, etc.
  
  string string_method_partition_events;

  string string_method_syst_shape; //do not change it : it will be filled either by "mean_IQR" or "fit"
  //-----------------------
  //inputs

  RooAbsData *absdata_nominal=0;
  
  TTree *tree_original_nominal;

  TTree *tree_nominal;
  TTree *tree_syst;

  TTree *tree_nominal_bootstrap;
  TTree *tree_syst_bootstrap;

  RooAbsData *absdata_syst=0;
  
  string string_process;
  //-----------------------
  //observables

  string m_string_observable_shape;
  string string_latex_observable_shape_no_units;
  string string_latex_observable_shape_units;
  
  //-----------------------
  //pdf or function
  
  RooRealVar *roorealvar_observable=0;
  RooRealVar *roorealvar_eventNumber=0;
  //shit  RooRealVar *roorealvar_yybb_Cat=0;
  RooRealVar *roorealvar_weight_total=0;

  int index_position_parameter;
  int index_spread_parameter;
  int index_normalization_parameter=-1;

  int index_alphaCB_Low;
  int index_alphaCB_High;
  int index_nCB_Low;
  int index_nCB_High;
		  
  int index_slopeExp_Low;
  int index_slopeExp_High;

  TF1 *function_shape_nominal=0;
  TF1 *function_shape_syst=0;
  
  RooAbsPdf *pdf_shape_nominal=0;
  RooAbsPdf *pdf_shape_syst=0;

  RooRealVar *roorealvar_muCB_nominal;
  RooRealVar *roorealvar_sigmaCB_nominal;
  RooRealVar *roorealvar_alphaCB_Low_nominal;
  RooRealVar *roorealvar_nCB_Low_nominal;
  RooRealVar *roorealvar_alphaCB_High_nominal;
  RooRealVar *roorealvar_nCB_High_nominal;

  RooRealVar *roorealvar_muCB_syst=0;
  RooRealVar *roorealvar_sigmaCB_syst=0;
  RooRealVar *roorealvar_alphaCB_Low_syst=0;
  RooRealVar *roorealvar_nCB_Low_syst=0;
  RooRealVar *roorealvar_alphaCB_High_syst=0;
  RooRealVar *roorealvar_nCB_High_syst=0;
  
  
  RooRealVar *roorealvar_muGauss_nominal;
  RooRealVar *roorealvar_sigmaGauss_nominal;
  RooRealVar *roorealvar_slopeExp_Low_nominal;
  RooRealVar *roorealvar_slopeExp_High_nominal;
  
  RooRealVar *roorealvar_muGauss_syst=0;
  RooRealVar *roorealvar_sigmaGauss_syst=0;
  RooRealVar *roorealvar_slopeExp_Low_syst=0;
  RooRealVar *roorealvar_slopeExp_High_syst=0;


  RooRealVar *roorealvar_muBukin_nominal;
  RooRealVar *roorealvar_sigmaBukin_nominal;
  RooRealVar *roorealvar_xiBukin_nominal;
  RooRealVar *roorealvar_rho1Bukin_nominal;
  RooRealVar *roorealvar_rho2Bukin_nominal;

  RooRealVar *roorealvar_muBukin_syst;
  RooRealVar *roorealvar_sigmaBukin_syst;
  RooRealVar *roorealvar_xiBukin_syst;
  RooRealVar *roorealvar_rho1Bukin_syst;
  RooRealVar *roorealvar_rho2Bukin_syst;
  
  float low_value_nominal_fit_range;
  float high_value_nominal_fit_range;
  float low_value_syst_fit_range;
  float high_value_syst_fit_range;

  //-----------------------
  //helper to initialize the parameters

  //histogram used for choosing the initial parameters of the functional form, the extension of the fit, etc.
  TH1D *hist_nominal;
  TH1D *hist_syst;

  TH1D *hist_nominal_fine_bins;


  //-----------------------
  //helper to get the results

  bool ParamAtLimit_nominal;
  bool ParamAtLimit_syst;


  vector<int> vec_index_toy;
  vector<int> vec_status_nominal;
  vector<int> vec_status_syst;
  vector<int> vec_converged;
  vector<double> vec_chi2_nominal;
  vector<double> vec_chi2_syst;
  vector<int> vec_ndof_nominal;
  vector<int> vec_ndof_syst;
  //-------------------------------------------
  vector<double> vec_muCB_nominal;
  vector<double> vec_err_muCB_nominal;
  vector<double> vec_sigmaCB_nominal;
  vector<double> vec_err_sigmaCB_nominal;
  vector<double> vec_alphaCB_Low_nominal;
  vector<double> vec_err_alphaCB_Low_nominal;
  vector<double> vec_nCB_Low_nominal;
  vector<double> vec_err_nCB_Low_nominal;
  vector<double> vec_alphaCB_High_nominal;
  vector<double> vec_err_alphaCB_High_nominal;
  vector<double> vec_nCB_High_nominal;
  vector<double> vec_err_nCB_High_nominal;
  
  vector<double> vec_muCB_syst;
  vector<double> vec_err_muCB_syst;
  vector<double> vec_sigmaCB_syst;
  vector<double> vec_err_sigmaCB_syst;
  vector<double> vec_alphaCB_Low_syst;
  vector<double> vec_err_alphaCB_Low_syst;
  vector<double> vec_nCB_Low_syst;
  vector<double> vec_err_nCB_Low_syst;
  vector<double> vec_alphaCB_High_syst;
  vector<double> vec_err_alphaCB_High_syst;
  vector<double> vec_nCB_High_syst;
  vector<double> vec_err_nCB_High_syst;
  //-------------------------------------------
  vector<double> vec_muGauss_nominal;
  vector<double> vec_err_muGauss_nominal;
  vector<double> vec_sigmaGauss_nominal;
  vector<double> vec_err_sigmaGauss_nominal;
  vector<double> vec_slopeExp_Low_nominal;
  vector<double> vec_err_slopeExp_Low_nominal;
  vector<double> vec_slopeExp_High_nominal;
  vector<double> vec_err_slopeExp_High_nominal;
  
  vector<double> vec_muGauss_syst;
  vector<double> vec_err_muGauss_syst;
  vector<double> vec_sigmaGauss_syst;
  vector<double> vec_err_sigmaGauss_syst;
  vector<double> vec_slopeExp_Low_syst;
  vector<double> vec_err_slopeExp_Low_syst;
  vector<double> vec_slopeExp_High_syst;
  vector<double> vec_err_slopeExp_High_syst;
  //-------------------------------------------
  vector<double> vec_muBukin_nominal;
  vector<double> vec_err_muBukin_nominal;
  vector<double> vec_sigmaBukin_nominal;
  vector<double> vec_err_sigmaBukin_nominal;
  vector<double> vec_xiBukin_nominal;
  vector<double> vec_err_xiBukin_nominal;
  vector<double> vec_rho1Bukin_nominal;
  vector<double> vec_err_rho1Bukin_nominal;
  vector<double> vec_rho2Bukin_nominal;
  vector<double> vec_err_rho2Bukin_nominal;

  vector<double> vec_muBukin_syst;
  vector<double> vec_err_muBukin_syst;
  vector<double> vec_sigmaBukin_syst;
  vector<double> vec_err_sigmaBukin_syst;
  vector<double> vec_xiBukin_syst;
  vector<double> vec_err_xiBukin_syst;
  vector<double> vec_rho1Bukin_syst;
  vector<double> vec_err_rho1Bukin_syst;
  vector<double> vec_rho2Bukin_syst;
  vector<double> vec_err_rho2Bukin_syst;
  //-------------------------------------------
  vector<float> vec_result_rel_effect_position_shape;
  vector<float> vec_result_rel_effect_spread_shape;
  
  vector<float> vec_mean_nominal;
  vector<float> vec_err_mean_nominal;
  vector<float> vec_mean_syst;
  vector<float> vec_err_mean_syst;
  
  vector<float> vec_IQR_nominal;
  vector<float> vec_err_IQR_nominal;
  vector<float> vec_IQR_syst;
  vector<float> vec_err_IQR_syst;



  
  //-----------------------
  //results

  RooFitResult *roofitresult_nominal=0;
  RooFitResult *roofitresult_syst=0;
  
  double position_parameter_nominal=0,err_position_parameter_nominal=0;
  double spread_parameter_nominal=0,err_spread_parameter_nominal=0;
  double position_parameter_syst=0,err_position_parameter_syst=0;
  double spread_parameter_syst=0,err_spread_parameter_syst=0;

  //-----------------------
  //backup

  double mean_nominal;
  double err_mean_nominal;
  double mean_syst;
  double err_mean_syst;
  
  double IQR_nominal;
  double err_IQR_nominal;
  double IQR_syst;
  double err_IQR_syst;
  //---------------
  double muCB_nominal;
  double sigmaCB_nominal;
  double alphaCB_Low_nominal;
  double nCB_Low_nominal;
  double alphaCB_High_nominal;
  double nCB_High_nominal;
  
  double err_muCB_nominal;
  double err_sigmaCB_nominal;
  double err_alphaCB_Low_nominal;
  double err_nCB_Low_nominal;
  double err_alphaCB_High_nominal;
  double err_nCB_High_nominal;
  
  double muCB_syst;
  double sigmaCB_syst;
  double alphaCB_Low_syst;
  double nCB_Low_syst;
  double alphaCB_High_syst;
  double nCB_High_syst;
  
  double err_muCB_syst;
  double err_sigmaCB_syst;
  double err_alphaCB_Low_syst;
  double err_nCB_Low_syst;
  double err_alphaCB_High_syst;
  double err_nCB_High_syst;
  //---------------
  double muGauss_nominal;
  double err_muGauss_nominal;
  double sigmaGauss_nominal;
  double err_sigmaGauss_nominal;
  double slopeExp_Low_nominal;
  double err_slopeExp_Low_nominal;
  double slopeExp_High_nominal;
  double err_slopeExp_High_nominal;

  double muGauss_syst;
  double err_muGauss_syst;
  double sigmaGauss_syst;
  double err_sigmaGauss_syst;
  double slopeExp_Low_syst;
  double err_slopeExp_Low_syst;
  double slopeExp_High_syst;
  double err_slopeExp_High_syst;
  //---------------
  double muBukin_nominal;
  double sigmaBukin_nominal;
  double xiBukin_nominal;
  double rho1Bukin_nominal;
  double rho2Bukin_nominal;

  double err_muBukin_nominal;
  double err_sigmaBukin_nominal;
  double err_xiBukin_nominal;
  double err_rho1Bukin_nominal;
  double err_rho2Bukin_nominal;

  double muBukin_syst;
  double sigmaBukin_syst;
  double xiBukin_syst;
  double rho1Bukin_syst;
  double rho2Bukin_syst;

  double err_muBukin_syst;
  double err_sigmaBukin_syst;
  double err_xiBukin_syst;
  double err_rho1Bukin_syst;
  double err_rho2Bukin_syst;
  //---------------
  double chi2_over_ndf_nominal;
  double chi2_over_ndf_syst;
  
  double chi2_nominal;
  double chi2_syst;
  
  int nparam_nominal;
  int nparam_syst;
  
  int ndof_nominal;
  int ndof_syst;

  //to put a condition
  //int nb_toys=1000; //don't go above 1000 : too big for MAX_TOYS in tool_Computesystematics shapeb_toys for bootstrap : for jacknife it is forced to 10 maximum
  //int nb_toys=2000; //don't go above 1000 : too big for MAX_TOYS in tool_Computesystematics shapeb_toys for bootstrap : for jacknife it is forced to 10 maximum
  
  //  unsigned int nb_toys=5000; //don't go above 1000 : too big for MAX_TOYS in tool_Computesystematics shapeb_toys for bootstrap : for jacknife it is forced to 10 maximum
  //unsigned int nb_toys=100; //don't go above 1000 : too big for MAX_TOYS in tool_Computesystematics shapeb_toys for bootstrap : for jacknife it is forced to 10 maximum
  int nb_toys=100; //don't go above 1000 : too big for MAX_TOYS in tool_Computesystematics shapeb_toys for bootstrap : for jacknife it is forced to 10 maximum

  
  //but probably could be improved
  
  unsigned int nb_toys_done;
  unsigned int nb_toys_converged;

  float mass_resonance;
  float mass_resonance_finalDV;

  float mass_yy_resonance;
  float mass_bb_resonance;
  float mass_bbyy_resonance;

  
  int nb_bins_histogram_shape;
  //  int extension_unilateral_histogram_shape;
  int extension_low_histogram_shape;
  int extension_high_histogram_shape;

  int index_start_toy_bootstrap,index_stop_toy_bootstrap;

  RooAbsReal* nll;
  RooMinimizer *_minuit;

  //for projecting a selection, for example for jacknife

  string string_project;
};

#endif
