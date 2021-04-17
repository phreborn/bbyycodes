#ifndef HHyybb_tool_Experimental_Systematics_H
#define HHyybb_tool_Experimental_Systematics_H

#include "HGamAnalysisFramework/HgammaAnalysis.h"
//#include "hhTruthWeightTools/hhWeightTool.h"

#include <map>

//with inclusive
//#define MAX_CATEGORIES_TOOL_EXP_SYST 5
//#define MAX_CATEGORIES_TOOL_EXP_SYST 1
//#define MAX_CATEGORIES_TOOL_EXP_SYST 2
#define MAX_CATEGORIES_TOOL_EXP_SYST 30

#define MAX_SYSTEMATICS 200


using namespace std;

class tool_Experimental_Systematics : public HgammaAnalysis
{
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.
public:

  bool pass_preselection_2_bjets; //!

  int m_index_event; //! used for seed of destination trees, in order to have no duplicates of event when doing bootstrap method with random numbers

  TFile *file_syst_shape; //!

  // variables that don't get filled at submission time should be
  // protected from being send from the submission node to the worker
  // node (done by the //!)

  //variations of systematics
  vector<string> m_variations_translated; //!

  const xAOD::EventInfo *m_HGamEventInfo=0; //!
  const xAOD::EventInfo *m_HGamTruthEventInfo=0; //!

  //CHECK WHAT IS USEFUL
  xAOD::PhotonContainer m_allPhotons; //!
  xAOD::PhotonContainer m_selPhotons; //!

  const xAOD::PhotonContainer *ptr_const_photons; //!
  xAOD::PhotonContainer *ptr_photons; //!

  xAOD::ElectronContainer m_allElectrons; //!
  xAOD::ElectronContainer m_selElectrons; //!

  const xAOD::ElectronContainer *ptr_const_electrons; //!

  xAOD::MuonContainer m_allMuons; //!
  xAOD::MuonContainer m_selMuons; //!

  const xAOD::MuonContainer *ptr_const_muons; //!

  xAOD::JetContainer m_allJets; //!
  xAOD::JetContainer m_selJets; //!
  const xAOD::JetContainer *ptr_const_jets; //!

  xAOD::JetContainer jets_noJVT; //!

  const xAOD::JetContainer *ptr_const_jets_noJVT; //!

  xAOD::MissingETContainer MET_sel; //!

  const xAOD::MissingETContainer *ptr_const_MET_sel; //!

private:
  vector<string> vec_string_category; //!
  //  vector<string> vec_string_category_non_resonant; //!
  //  vector<string> vec_string_category_resonant; //!

  map<string,TTree *>map_tree_sel_f_categ[MAX_CATEGORIES_TOOL_EXP_SYST]; //! //for shape

  map<string,TH1D *>map_hist_nb_sel_f_categ[MAX_CATEGORIES_TOOL_EXP_SYST]; //! //for yield
  map<string,TH1D *>map_hist_nb_sel_uncommon_part_nominal_f_categ[MAX_CATEGORIES_TOOL_EXP_SYST]; //! //for yield
  map<string,TH1D *>map_hist_nb_sel_common_part_nominal_f_categ[MAX_CATEGORIES_TOOL_EXP_SYST]; //! //for yield
  map<string,TH1D *>map_hist_nb_sel_uncommon_part_sys_f_categ[MAX_CATEGORIES_TOOL_EXP_SYST]; //! //for yield
  map<string,TH1D *>map_hist_nb_sel_f_categ_unweighted[MAX_CATEGORIES_TOOL_EXP_SYST]; //! //for yield
  map<string,TH1D *>map_hist_nb_sel_uncommon_part_nominal_f_categ_unweighted[MAX_CATEGORIES_TOOL_EXP_SYST]; //! //for yield
  map<string,TH1D *>map_hist_nb_sel_uncommon_part_sys_f_categ_unweighted[MAX_CATEGORIES_TOOL_EXP_SYST]; //! //for yield
  //----------
  //systematics yields
  /*shit
  //shit  double *ptr_map_nb_sel_sys; //!
  double *ptr_map_err_nb_sel_sys; //!
  double *ptr_map_nb_sel_sys_common_part_sys; //!
  double *ptr_map_nb_sel_sys_common_part_nominal; //!

  double *ptr_map_nb_sel_sys_uncommon_part_sys; //!
  double *ptr_map_nb_sel_sys_uncommon_part_nominal; //!

  double *ptr_map_err_nb_sel_sys_common_part_sys; //!
  double *ptr_map_err_nb_sel_sys_common_part_nominal; //!
  
  double *ptr_map_err_nb_sel_sys_uncommon_part_sys; //!
  double *ptr_map_err_nb_sel_sys_uncommon_part_nominal; //!
  */

  double m_weight_total_nominal; //!
  double m_weight_event_nominal; //!
  
  //-----------------------------------
  //used to know if there is a full correlation or not
  /*shit
  double *ptr_map_nb_sel_sys_uncommon_part_sys_unweighted; //!
  double *ptr_map_err_nb_sel_sys_uncommon_part_sys_unweighted; //!
  double *ptr_map_nb_sel_sys_uncommon_part_nominal_unweighted; //!
  double *ptr_map_err_nb_sel_sys_uncommon_part_nominal_unweighted; //!

  double *ptr_map_nb_sel_sys_unweighted; //!
  double *ptr_map_err_nb_sel_sys_unweighted; //!
  */


  map<string,double>map_nb_sel_f_categ_sys_unweighted[MAX_CATEGORIES_TOOL_EXP_SYST]; //!
  map<string,double>map_err_nb_sel_f_categ_sys_unweighted[MAX_CATEGORIES_TOOL_EXP_SYST]; //!
  
  map<string,double>map_nb_sel_f_categ_sys_uncommon_part_nominal_unweighted[MAX_CATEGORIES_TOOL_EXP_SYST]; //!
  map<string,double>map_nb_sel_f_categ_sys_uncommon_part_sys_unweighted[MAX_CATEGORIES_TOOL_EXP_SYST]; //!
  map<string,double>map_err_nb_sel_f_categ_sys_uncommon_part_nominal_unweighted[MAX_CATEGORIES_TOOL_EXP_SYST]; //!
  map<string,double>map_err_nb_sel_f_categ_sys_uncommon_part_sys_unweighted[MAX_CATEGORIES_TOOL_EXP_SYST]; //!


  //-----------------------------------




  map<string,double>map_nb_sel_f_categ_sys[MAX_CATEGORIES_TOOL_EXP_SYST]; //!
  map<string,double>map_err_nb_sel_f_categ_sys[MAX_CATEGORIES_TOOL_EXP_SYST]; //!

  //further information for computing the error, taking into account the correlation among the yields from sytematics

  
  map<string,double>map_nb_sel_f_categ_sys_common_part_nominal[MAX_CATEGORIES_TOOL_EXP_SYST]; //!
  map<string,double>map_nb_sel_f_categ_sys_uncommon_part_nominal[MAX_CATEGORIES_TOOL_EXP_SYST]; //!
  map<string,double>map_nb_sel_f_categ_sys_common_part_sys[MAX_CATEGORIES_TOOL_EXP_SYST]; //!
  map<string,double>map_nb_sel_f_categ_sys_uncommon_part_sys[MAX_CATEGORIES_TOOL_EXP_SYST]; //!

  map<string,double>map_err_nb_sel_f_categ_sys_common_part_nominal[MAX_CATEGORIES_TOOL_EXP_SYST]; //!
  map<string,double>map_err_nb_sel_f_categ_sys_uncommon_part_nominal[MAX_CATEGORIES_TOOL_EXP_SYST]; //!
  map<string,double>map_err_nb_sel_f_categ_sys_common_part_sys[MAX_CATEGORIES_TOOL_EXP_SYST]; //!
  map<string,double>map_err_nb_sel_f_categ_sys_uncommon_part_sys[MAX_CATEGORIES_TOOL_EXP_SYST]; //!
  //==========================
  //==========================
  //-----

  map<string,double>map_rel_effect_sel_f_categ_sys[MAX_CATEGORIES_TOOL_EXP_SYST]; //!
  map<string,double>map_err_rel_effect_sel_f_categ_sys[MAX_CATEGORIES_TOOL_EXP_SYST]; //!

  //further information for computing the error, taking into account the correlation among the yields from sytematics

  int m_eventNumber; //!
  int m_mcID; //!

  double m_truth_m_hh; //!

  bool *ptr_m_pass_HH_nominal_f_categ; //!
  bool m_pass_HH; //!

  bool m_pass_HH_nominal_f_categ[MAX_CATEGORIES_TOOL_EXP_SYST]; //!

  int m_pass_HH_f_categ[MAX_CATEGORIES_TOOL_EXP_SYST]; //!

  //---------  
  string sampleName; //!

  bool current_is_nominal; //!

  double m_m_yy; //!
  double m_m_bb; //!
  double m_m_yybb; //!
  double m_m_yybb_cnstrnd; //!
  double m_m_yybb_tilde; //!
  
  int m_index_first_categ_resonant; //!
  int m_yybb_Cat; //!
  //---
  //useful for common/uncommon treatment
  //---
  /*
  float m_weight; //!
  float m_weight_yybb; //!
  */

  //use to be more precise, and avoid numerical rounding for fit part
  double m_weight; //!
  double m_weight_yybb; //!

  double m_weight_lumi; //!
  double m_weight_total; //!
  double m_weight_event; //!

  //  xAOD::hhWeightTool *m_hhWeightTool=0;
  
public:
  // this is a standard constructor
  tool_Experimental_Systematics() { }
  tool_Experimental_Systematics(const char *name);
  virtual ~tool_Experimental_Systematics();

  virtual EL::StatusCode histFinalize();
  virtual EL::StatusCode finalize();

  // these are the functions inherited from HgammaAnalysis
  virtual EL::StatusCode createOutput();
  virtual EL::StatusCode execute();

  bool treat_selection_current_systematics_or_nominal(string string_current_variation);


  double get_err_rel_effect_yield_partially_correlated(double yield_nominal,	
						       double yield_common_part_nominal,
						       double yield_uncommon_part_nominal,
						       double yield_uncommon_part_sys,
						       double err_yield_uncommon_part_nominal,
						       double err_yield_common_part_nominal,
						       double err_yield_uncommon_part_sys);

  //shit  double get_err_rel_effect_yield_partially_correlated(double yield_nominal,double yield_uncommon_part_nominal,double yield_uncommon_part_sys,double err_yield_uncommon_part_nominal,double err_yield_common_part_nominal,double err_yield_uncommon_part_sys);
  double get_err_rel_effect_yield_fully_correlated(double yield_nominal,double yield_sys,double err_yield_nominal,double err_yield_sys);

  string Translate_current_variation(string string_current_variation);
  string ReturnSubDirectoryWhereToStore(string sampleName);
  int ProtectAgainstFakeSystematic(string string_current_variation);

  string ReturnRecoCategoryNonResonant();
  bool IsPassResonant(int mX);
  int ReturnIndexCategory(string string_category);

  void FillListCategories();
  
  void FillAdditionalHist(string string_syst_additional_translated);
  void FillListVariations();

  // this is needed to distribute the algorithm to the workers
  ClassDef(tool_Experimental_Systematics, 1);
};

#endif
