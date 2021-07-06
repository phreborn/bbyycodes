void PrepareMergedSystematic(string string_sample,string string_category,vector<string> vec_string_systematic_selected);
string Return_string_latex_sample(string string_sample);

//==============================================================
int Systematics_Yield_Shape_current_subset_systematics(string string_sample,string string_yield_shape,string string_method_syst_shape,string string_method_toys,string string_category,string string_observable,string string_MxAOD,string menu_systematics,int index_start_toy=-1,int index_stop_toy=-1);

bool BelongToKnownSample(string string_sample);


//delete HH 139 fb-1 released
//int GetListOfSubprocessesToMerge(string menu_systematics);

string Return_subthematic_given_systematic(string string_systematic);
string Return_object_given_systematic(string string_systematic);
string ReturnMxAODSyst_directory(string string_systematic);

string Return_name_for_syst(string string_systematic);
void prevent_pathological_same_sign_syst(double *ptr_rel_effect_up,
					 double *ptr_rel_effect_down
					 /*
					 ,
					double *ptr_rel_effect_sym,
					double *ptr_err_rel_effect_up,
					double *ptr_err_rel_effect_down,
					double *ptr_err_rel_effect_sym
					 */
);

//skip non significative errors
void prun_systematic_effect(double *ptr_rel_effect_up,
			    double *ptr_rel_effect_down,
			    double *ptr_rel_effect_sym,
			    double *ptr_err_rel_effect_up,
			    double *ptr_err_rel_effect_down,
			    double *ptr_err_rel_effect_sym);

void PrintRepresentativeSystematic(string string_overview_subthematic,
				   string string_systematic,
				   FILE *fp_table,
				   FILE *fp_datacard,
				   double rel_effect_up_max_effect_over_processes_current_class,
				   double rel_effect_down_max_effect_over_processes_current_class,
				   double rel_effect_sym_max_effect_over_processes_current_class,
				   double err_rel_effect_up_max_effect_over_processes_current_class,
				   double err_rel_effect_down_max_effect_over_processes_current_class,
				   double err_rel_effect_sym_max_effect_over_processes_current_class);
void FillTableSyst(string string_sample,string string_yield_shape,string string_method_syst_shape,string string_method_toys,string string_category,string string_observable_shape,string string_MxAOD,string menu_systematics,vector<string> vec_string_systematic_raw,string string_file_results_systematics_details,string string_file_results_systematics_subthematic,int index_start_toy=-1,int index_stop_toy=-1);


void get_yield_from_file(string string_category,string local_string_sample,string string_systematic);

//delete HH 139 fb-1 released
//void MergeAndStore_subprocesses_Process(string string_category,vector<string> vec_string_systematic_raw);

void GetPointer_ThematicSyst_for_DetailSyst(string string_yield_shape,string string_systematic,config_subthematic_results **ptr_config_subthematic_results_yield,config_subthematic_results **ptr_config_subthematic_results_position_shape,config_subthematic_results **ptr_config_subthematic_results_spread_shape);
void GetPointer_ThematicSyst(string string_yield_shape,string string_thematic_systematic,config_subthematic_results **ptr_config_subthematic_results_yield,config_subthematic_results **ptr_config_subthematic_results_position_shape,config_subthematic_results **ptr_config_subthematic_results_spread_shape);

void PrintHeaderTableSyst(string string_sample,FILE *fp,string string_yield_shape);

double get_err_rel_effect_yield_partially_correlated(double yield_nominal,
						     double yield_common_part_nominal,
						     double yield_uncommon_part_nominal,
						     double yield_uncommon_part_sys,
						     double err_yield_uncommon_part_nominal,
						     double err_yield_common_part_nominal,
						     double err_yield_uncommon_part_sys);

double get_err_rel_effect_yield_fully_correlated(double yield_nominal,
						 double yield_sys,
						 double err_yield_nominal,
						 double err_yield_sys);
//- - - - - - - - - -

