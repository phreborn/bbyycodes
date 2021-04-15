bool mode_debug=0;
//problem of the environment variable

vector<string> CreateList_HH_non_resonant_kappa_lambda();
string Return_string_target_kappa(double numerical_target_kappa);

#include "CaseTheory_Renormalize_Weights_and_create_rel_effect/tool_CreateList_HH_non_resonant_kappa_lambda.C"

vector<string> vec_string_category;

void macro_launcher_all_KappaLambda()
{
  
  vec_string_category.push_back("XGBoost_btag77_withTop_BCal_tightScore_HMass");
  vec_string_category.push_back("XGBoost_btag77_withTop_BCal_looseScore_HMass");
  vec_string_category.push_back("XGBoost_btag77_withTop_BCal_tightScore_LMass");
  vec_string_category.push_back("XGBoost_btag77_withTop_BCal_looseScore_LMass");

  //==============================================================
  //special case of reweighted kappa lambda
  
  vector<string> vec_string_kappa_lambda_destination=CreateList_HH_non_resonant_kappa_lambda();
  
  vec_string_kappa_lambda_destination=CreateList_HH_non_resonant_kappa_lambda();
  
  for (int index_kappa_lambda=0;index_kappa_lambda<vec_string_kappa_lambda_destination.size();index_kappa_lambda++) {
    cout << "index_kappa_lambda=" << index_kappa_lambda << ", name=" << vec_string_kappa_lambda_destination[index_kappa_lambda] << endl;
  }
  
  //  exit(1);

  for (int index_category=0;index_category<vec_string_category.size();index_category++) {
    string string_category=vec_string_category[index_category];
    
    cout << "index_category=" << index_category << ", " << vec_string_category[index_category] << endl;
    
    //==============================================================
    for (int index_kappa_lambda=0;index_kappa_lambda<vec_string_kappa_lambda_destination.size();index_kappa_lambda++) {
      //for (int index_kappa_lambda=0;index_kappa_lambda<1;index_kappa_lambda++) {
      
      string string_kappa_lambda=vec_string_kappa_lambda_destination[index_kappa_lambda];
      
      cout << "==================================================================" << endl;
      cout << "==================================================================" << endl;
      cout << "==================================================================" << endl;
      cout << "==================================================================" << endl;
      cout << "==================================================================" << endl;
      
      string string_process="PowhegPy8_HHbbyy_reweight_mHH_1p0_to_";
      string_process+=string_kappa_lambda;
      
      string string_unix;
      
      if (mode_debug)
	string_unix="echo ";
      else
	string_unix="";
      
      //example
      //    root -b -q "Systematics_Yield_Shape.C+(\"PowhegPy8_HHbbyy_reweight_mHH_1p0_to_4p0\",\"yield\",\"do_not_care\",\"do_not_care\",\"XGBoost_btag77_withTop_BCal_tightScore_HMass\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee mylog_cat1
      
      string_unix+="root -b -q \"Systematics_Yield_Shape.C+(\\\"PowhegPy8_HHbbyy_reweight_mHH_1p0_to_"+string_kappa_lambda+"\\\",\\\"yield\\\",\\\"do_not_care\\\",\\\"do_not_care\\\",\\\""+string_category+"\\\",\\\"do_not_care\\\",\\\"h026_mc16a_h026_mc16d_h026_mc16e\\\",0,1)\"";
      
      string_unix+=" |tee log_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_HHbbyy_reweight_mHH_1p0_to_"+string_kappa_lambda+"_yield_cat_"+string_category;

      cout << "string_unix=" << endl;
      
      cout << string_unix << endl;
      
      cout << "launch the command" << endl;
      gSystem->Exec(string_unix.c_str());
      
    } //end list on kappa_lambda

  } //end loop on category

  //==============================================================
}
