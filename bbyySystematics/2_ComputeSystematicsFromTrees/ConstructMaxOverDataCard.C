//to do : get from first string if there is the word yield, position_shape or spread_shape

//to do : a string for the specific vector push, different to the string process for the saving

//===================================================================================================
//MENU

//to do a vector and a loop ?

string string_experimental_theory="experimental"; //experimental, theory

string string_type="spread_shape_m_yy"; //yield, position_shape_m_yy, spread_shape_m_yy

string string_sample="gg_HH_resonant"; //ggH_in_HH_resonant, ZH_in_HH_resonant, ttH_in_resonant, gg_HH_non_resonant, vbf_HH_non_resonant, HH_resonant, gg_HH_non_resonant_in_HH_resonant, vbf_HH_non_resonant_in_HH_resonant

string string_process; //do not change that
string string_kappa_lambda="all"; //all, ignore
//===================================================================================================

#include <algorithm>

using namespace std;

//used in the part dedicated to computing the max over systematics, in order to dump the Table of max over systematics
//usage :
//root -b
//.x ConstructMaxOverDataCard.C

vector<string> vec_result_to_probe={}; //list is at the very bottom

string string_destination_max;

//TO PUT PROC AND CAT EVERYWHERE
//-----------------------------------------

string string_path="results/datacards/details/";

vector<double> vec_characteristic;

vector<double> vec_observable_sym_f_characteristic;

vector<double> vec_observable_up_f_characteristic;
vector<double> vec_observable_down_f_characteristic;

//--------------
//final luminosity Moriond 2021 : dictated by the framework

//       20170619 : GRL v89 :  3 219.56 pb-1
//       20180129 : GRLv89 : 32 988.1 pb-1
//       36 207.66 pb-1
//       20180619 : GRLv99 : 44 307.4 pb-1
//       20190318 : GRLv102 : 58 450.1 pb-1
//       138 965.16 pb-1

float lumi_mc16a=36.20766;
float lumi_mc16d=44.3074;
float lumi_mc16e=58.4501;

float lumi;

vector<string> vec_string_category;
//-----
//prototypes

vector<string> CreateList_HH_non_resonant_kappa_lambda();
string Return_string_target_kappa(double numerical_target_kappa);

void ConstructMaxFromListDataCard(vector<string> vec_datacard,string string_category);

double ReturnCharacteristic(string string_process);
double Return_numerical_target_kappa(string string_target_kappa);

void Draw_observable_f_characteristic(string string_non_resonant_resonant,string string_systematic,string string_observable_f_characteristic,string string_category,vector<double> vec_double_characteristic,vector<double> local_vec_observable_up_f_characteristic,vector<double> local_vec_observable_down_f_characteristic);

#include "CaseTheory_Renormalize_Weights_and_create_rel_effect/tool_CreateList_HH_non_resonant_kappa_lambda.C"
//-----
//variables

bool is_theory;

//#######################################################################################################################################################################################################
int ConstructMaxOverDataCard()
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0000000);
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
  //==============================================================

  string string_datacard;

  for (int index_category=0;index_category<vec_string_category.size();index_category++) {
    string string_category=vec_string_category[index_category];

    vec_result_to_probe.clear();

    if (string_sample=="gg_HH_non_resonant") {

      string_process="gg_HH_non_resonant";

      if (string_kappa_lambda=="all") {
	//==============================================================
	//special case of reweighted kappa lambda
	
	vector<string> vec_string_kappa_lambda_destination=CreateList_HH_non_resonant_kappa_lambda();
	
	vec_string_kappa_lambda_destination=CreateList_HH_non_resonant_kappa_lambda();
	//-----
	//insert the kappa_lambda=1 at the relevant position : mandatory in order to construct correctly the graph
	
	for (int index_kappa_lambda=0;index_kappa_lambda<vec_string_kappa_lambda_destination.size();index_kappa_lambda++) {
	  string string_kappa_lambda=vec_string_kappa_lambda_destination[index_kappa_lambda];
	  double numerical_kappa_lambda=Return_numerical_target_kappa(string_kappa_lambda);
	  if (numerical_kappa_lambda>1.0) {
	    
	    vector<string>::iterator it;
	    
	    it=vec_string_kappa_lambda_destination.begin();
	    //shit	    vec_string_kappa_lambda_destination.insert(it+index_kappa_lambda,"HH_non_resonant_kappa_lambda_01");
	    vec_string_kappa_lambda_destination.insert(it+index_kappa_lambda,"gg_HH_non_resonant_kappa_lambda_01");
	    break; //Thanks to that, it inserts it only once
	  }
	}
	//-----
	for (int index_kappa_lambda=0;index_kappa_lambda<vec_string_kappa_lambda_destination.size();index_kappa_lambda++) {
	  cout << "index_kappa_lambda=" << index_kappa_lambda << ", name=" << vec_string_kappa_lambda_destination[index_kappa_lambda] << endl;
	}

	//==============================================================
	if (vec_result_to_probe.size()!=0) {
	  cout << "Alert, for special case of scanning all kappa lambda, your vec_result_to_probe should be empty" << endl;
	  exit(1);
	}
	//---------------------------------      
	
	//special case all kappa lambda, for theoretical systematic
	
	//put the SM and other kappa lambda : should be done in the appropriate order to prevent having trouble in the TGraph
	
	for (int index_kappa_lambda=0;index_kappa_lambda<vec_string_kappa_lambda_destination.size();index_kappa_lambda++) {
	  
	  string string_kappa_lambda=vec_string_kappa_lambda_destination[index_kappa_lambda];
	  
	  //example    datacard_theory_yield_proc_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_HHbbyy_reweight_mHH_1p0_to_n9p6_cat_XGBoost_btag77_withTop_BCal_looseScore_LMass.txt
	  //shit	  if (string_kappa_lambda=="HH_non_resonant_kappa_lambda_01") {
	  if (string_kappa_lambda=="gg_HH_non_resonant_kappa_lambda_01") {
	    //shit	    string_datacard="datacard_theory_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_01_cat_";
	    string_datacard="datacard_theory_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_cat_";
	    
	  }
	  else {    
	    //shit	    string_datacard="datacard_theory_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_HHbbyy_reweight_mHH_1p0_to_";
	    string_datacard="datacard_theory_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_HHbbyy_reweight_mHH_1p0_to_";
	    string_datacard+=string_kappa_lambda;
	    string_datacard+="_cat_";
	  }
	  
	  string_datacard+=string_category;
	  string_datacard+=".txt";
	  
	  vec_result_to_probe.push_back(string_datacard);
	  
	} //end loop on kappa lambda
      } //end case all
      else { //distinct samples

	string_datacard="datacard_experimental_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_cat_";
	string_datacard+=string_category;
	string_datacard+=".txt";
	vec_result_to_probe.push_back(string_datacard);
	
	string_datacard="datacard_experimental_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_10_cat_";
	string_datacard+=string_category;
	string_datacard+=".txt";
	vec_result_to_probe.push_back(string_datacard);
      } //distinct samples
    } //end case HH non resonant
    else if (string_sample=="gg_HH_resonant") {
      string_process="gg_HH_resonant";
      //was typo here
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X251tohh_bbyy_AF2_cat_Resonant_mX251"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X260tohh_bbyy_AF2_cat_Resonant_mX260"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X280tohh_bbyy_AF2_cat_Resonant_mX280"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X300tohh_bbyy_AF2_cat_Resonant_mX300"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X325tohh_bbyy_AF2_cat_Resonant_mX325"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X350tohh_bbyy_AF2_cat_Resonant_mX350"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X400tohh_bbyy_AF2_cat_Resonant_mX400"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X450tohh_bbyy_AF2_cat_Resonant_mX450"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X500tohh_bbyy_AF2_cat_Resonant_mX500"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X550tohh_bbyy_AF2_cat_Resonant_mX550"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X600tohh_bbyy_AF2_cat_Resonant_mX600"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X700tohh_bbyy_AF2_cat_Resonant_mX700"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X800tohh_bbyy_AF2_cat_Resonant_mX800"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X900tohh_bbyy_AF2_cat_Resonant_mX900"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X1000tohh_bbyy_AF2_cat_Resonant_mX1000"+".txt").c_str());
    }
    else if (string_sample=="gg_HH_non_resonant_in_HH_resonant") {
      string_process="gg_HH_non_resonant";

      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX251"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX260"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX280"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX300"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX325"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX350"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX400"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX450"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX500"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX550"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX600"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX700"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX800"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX900"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX1000"+".txt").c_str());
    }
    else if (string_sample=="vbf_HH_non_resonant_in_HH_resonant") {
      string_process="vbf_HH_non_resonant";

      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX251"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX260"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX280"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX300"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX325"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX350"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX400"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX450"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX500"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX550"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX600"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX700"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX800"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX900"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_experimental_")+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_cat_Resonant_mX1000"+".txt").c_str());
    }

    else if (string_sample=="ggH_in_HH_resonant") {
      string_process="ggH";
      
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_cat_Resonant_mX251"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_cat_Resonant_mX260"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_cat_Resonant_mX280"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_cat_Resonant_mX300"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_cat_Resonant_mX325"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_cat_Resonant_mX350"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_cat_Resonant_mX400"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_cat_Resonant_mX450"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_cat_Resonant_mX500"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_cat_Resonant_mX550"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_cat_Resonant_mX600"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_cat_Resonant_mX700"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_cat_Resonant_mX800"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_cat_Resonant_mX900"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_cat_Resonant_mX1000"+".txt").c_str());
    }
    else if (string_sample=="ZH_in_HH_resonant") {
      string_process="ZH";

      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ZH125_cat_Resonant_mX251"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ZH125_cat_Resonant_mX260"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ZH125_cat_Resonant_mX280"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ZH125_cat_Resonant_mX300"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ZH125_cat_Resonant_mX325"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ZH125_cat_Resonant_mX350"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ZH125_cat_Resonant_mX400"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ZH125_cat_Resonant_mX450"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ZH125_cat_Resonant_mX500"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ZH125_cat_Resonant_mX550"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ZH125_cat_Resonant_mX600"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ZH125_cat_Resonant_mX700"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ZH125_cat_Resonant_mX800"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ZH125_cat_Resonant_mX900"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ZH125_cat_Resonant_mX1000"+".txt").c_str());
    }
    else if (string_sample=="ttH_in_HH_resonant") {

      string_process="ttH";

      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ttH125_cat_Resonant_mX251"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ttH125_cat_Resonant_mX260"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ttH125_cat_Resonant_mX280"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ttH125_cat_Resonant_mX300"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ttH125_cat_Resonant_mX325"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ttH125_cat_Resonant_mX350"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ttH125_cat_Resonant_mX400"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ttH125_cat_Resonant_mX450"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ttH125_cat_Resonant_mX500"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ttH125_cat_Resonant_mX550"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ttH125_cat_Resonant_mX600"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ttH125_cat_Resonant_mX700"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ttH125_cat_Resonant_mX800"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ttH125_cat_Resonant_mX900"+".txt").c_str());
      vec_result_to_probe.push_back((string("datacard_")+string_experimental_theory+"_"+string_type+"_proc_h026_mc16a_h026_mc16d_h026_mc16e_ttH125_cat_Resonant_mX1000"+".txt").c_str());
    }
    
    cout << "vec_result_to_probe.size()=" << vec_result_to_probe.size() << endl;
    
    //---------------------------------
    is_theory=0;
    if (string_experimental_theory=="theory")
      is_theory=1;
    
    string_destination_max="datacard_";
    string_destination_max+=string_experimental_theory;
    string_destination_max+="_";

    string_destination_max+=string_type;
    string_destination_max+="_proc_";

    string_destination_max+=string_process;
    string_destination_max+="_";

    if (string_kappa_lambda=="all")
      //shity
      //string_destination_max+="Max_among_kappa_lambda";
      string_destination_max+="Max";
    else
      string_destination_max+="Max";
    
    string_destination_max+="_cat_";
    string_destination_max+=string_category;
    string_destination_max+=".txt";
    
    ConstructMaxFromListDataCard(vec_result_to_probe,string_category);
  } //end loop on categories
  
  return 0;
}
//#######################################################################################################################################################################################################
double ReturnCharacteristic(string string_process)
{
  cout << "ReturnCharacteristic for string_process=" << string_process << endl;

  double characteristic=0;

  if (string_process.find("X260")!=string::npos)
    characteristic=260;
  else if (string_process.find("X280")!=string::npos)
    characteristic=280;
  else if (string_process.find("X300")!=string::npos)
    characteristic=300;
  else if (string_process.find("X325")!=string::npos)
    characteristic=325;
  else if (string_process.find("X350")!=string::npos)
    characteristic=350;
  else if (string_process.find("X400")!=string::npos)
    characteristic=400;
  else if (string_process.find("X450")!=string::npos)
    characteristic=450;
  else if (string_process.find("X500")!=string::npos)
    characteristic=500;
  else if (string_process.find("X550")!=string::npos)
    characteristic=550;
  else if (string_process.find("X600")!=string::npos)
    characteristic=600;
  else if (string_process.find("X700")!=string::npos)
    characteristic=700;
  else if (string_process.find("X800")!=string::npos)
    characteristic=800;
  else if (string_process.find("X900")!=string::npos)
    characteristic=900;
  else if (string_process.find("X1000")!=string::npos)
    characteristic=1000;
  
  else if (string_process.find("HH_non_resonant_kappa_lambda_01")!=string::npos
	   ||
	   string_process=="gg_HH_NLO"
	   )
    characteristic=1;
  else if (string_process.find("reweight_mHH_1p0_to_")!=string::npos) {

    cout << "string_process=" << string_process << endl;

    size_t position_string_reweight=string_process.find("reweight_mHH_1p0_to_");

    cout << "position_string_reweight=" << position_string_reweight << endl;    

    size_t position_string_category=0;
    
    position_string_category=string_process.find("_cat");
    cout << "position_string_category=" << position_string_category << endl;
    
    //+20 : size of "reweight_mHH_1p0_to_"
    string string_kappa_lambda=string_process.substr(position_string_reweight+20,position_string_category-(position_string_reweight+20));

    cout << "string_kappa_lambda=" << string_kappa_lambda << endl;

    double numerical_target_kappa=Return_numerical_target_kappa(string_kappa_lambda);

    cout << "numerical_target_kappa=" << numerical_target_kappa << endl;

    characteristic=numerical_target_kappa;
  
  } //end case reweight

  //  cout << "return this : " << characteristic << endl;

  return characteristic;
}
//#######################################################################################################################################################################################################
//here, up plays the role of symmetric in case of theory

void Draw_observable_f_characteristic(string string_non_resonant_resonant,string string_systematic,string string_observable_f_characteristic,string string_category,vector<double> vec_double_characteristic,vector<double> local_vec_observable_up_f_characteristic,vector<double> local_vec_observable_down_f_characteristic)
{
  cout << "------------------" << endl;
  cout << "Draw_observable_f_characteristic for " << string_observable_f_characteristic << ", category=" << string_category << endl;
  
  //----------------------------------------------------------------------
  //to do : put canvas at the best position ?

  TCanvas *canvas=new TCanvas("canvas","canvas",800,600);
  canvas->SetLeftMargin(0.13);
  canvas->SetRightMargin(0.03);
  canvas->SetTopMargin(0.05);

  unsigned int n_characteristic=vec_double_characteristic.size();
  cout << "n_characteristic=" << n_characteristic << endl;
  
  for (int index_characteristic=0;index_characteristic<n_characteristic;index_characteristic++) {
    cout << "index_characteristic=" << index_characteristic << ", value characteristic=" << vec_double_characteristic[index_characteristic] << endl;
  }

  //search for max and min, for the range
  
  float min_graph_observable_f_characteristic=std::numeric_limits<float>::max();
  float max_graph_observable_f_characteristic=-std::numeric_limits<float>::max();

  cout << "list of observables to consider" << endl;
  for (unsigned int index_characteristic=0;index_characteristic<n_characteristic;index_characteristic++) {

    cout << "local_vec_observable_up_f_characteristic[index_characteristic]=" << local_vec_observable_up_f_characteristic[index_characteristic];
    if (!is_theory)
      cout << ", local_vec_observable_down_f_characteristic[index_characteristic]=" << local_vec_observable_down_f_characteristic[index_characteristic];
    
    cout << endl;
    
    if (local_vec_observable_up_f_characteristic[index_characteristic]<min_graph_observable_f_characteristic)
      min_graph_observable_f_characteristic=local_vec_observable_up_f_characteristic[index_characteristic];
    if (local_vec_observable_up_f_characteristic[index_characteristic]>max_graph_observable_f_characteristic)
      max_graph_observable_f_characteristic=local_vec_observable_up_f_characteristic[index_characteristic];

    if (!is_theory) {
      if (local_vec_observable_down_f_characteristic[index_characteristic]<min_graph_observable_f_characteristic)
	min_graph_observable_f_characteristic=local_vec_observable_down_f_characteristic[index_characteristic];
      if (local_vec_observable_down_f_characteristic[index_characteristic]>max_graph_observable_f_characteristic)
	max_graph_observable_f_characteristic=local_vec_observable_down_f_characteristic[index_characteristic];
    }
  }
  
  cout << "min_graph_observable_f_characteristic=" << min_graph_observable_f_characteristic << ", max_graph_observable_f_characteristic=" << max_graph_observable_f_characteristic << endl;
  
  //  float factor_enlarge_plot=1.05;
  float factor_enlarge_plot=1.10;
  
  if (min_graph_observable_f_characteristic>0)
    min_graph_observable_f_characteristic/=factor_enlarge_plot;
  else
    min_graph_observable_f_characteristic*=factor_enlarge_plot;
  
  if (max_graph_observable_f_characteristic>0)
    max_graph_observable_f_characteristic*=factor_enlarge_plot;
  else
    max_graph_observable_f_characteristic/=factor_enlarge_plot;
  
  cout << "after enlargement, min_graph_observable_f_characteristic=" << min_graph_observable_f_characteristic << ", max_graph_observable_f_characteristic=" << max_graph_observable_f_characteristic << endl;

  //no error by construction
  TGraph *graph_observable_up_f_characteristic=new TGraph(n_characteristic,vec_double_characteristic.data(),local_vec_observable_up_f_characteristic.data());
  graph_observable_up_f_characteristic->SetMarkerStyle(20);

  graph_observable_up_f_characteristic->SetMarkerSize(1.);
  if (is_theory) {
    graph_observable_up_f_characteristic->SetMarkerColor(kBlack);
    graph_observable_up_f_characteristic->SetLineColor(kBlack);
  }
  else {
    graph_observable_up_f_characteristic->SetMarkerColor(kRed);
    graph_observable_up_f_characteristic->SetLineColor(kRed);
  }

  TGraph *graph_observable_down_f_characteristic=0;
  
  if (!is_theory) {
    graph_observable_down_f_characteristic=new TGraph(n_characteristic,vec_double_characteristic.data(),local_vec_observable_down_f_characteristic.data());
    graph_observable_down_f_characteristic->SetMarkerStyle(20);
    graph_observable_down_f_characteristic->SetMarkerColor(kBlue);
    graph_observable_down_f_characteristic->SetMarkerSize(1.);
    graph_observable_down_f_characteristic->SetLineColor(kBlue);
  }
  
  TH1F *hist_frame=0;
  
  if (string_non_resonant_resonant=="Non Resonant analysis")
    hist_frame=new TH1F("hist_frame","hist_frame",n_characteristic,vec_double_characteristic[0]-1,vec_double_characteristic[n_characteristic-1]+1);

  else if (string_non_resonant_resonant=="Resonant analysis")
    hist_frame=new TH1F("hist_frame","hist_frame",n_characteristic,vec_double_characteristic[0]-10,vec_double_characteristic[n_characteristic-1]+10);
  

  hist_frame->SetLineColor(kBlack);
  hist_frame->SetMinimum(min_graph_observable_f_characteristic);
  hist_frame->SetMaximum(max_graph_observable_f_characteristic);
  
  hist_frame->Draw();
  
  if (string_non_resonant_resonant=="Non Resonant analysis")
    hist_frame->SetXTitle("#kappa_{#lambda}"); //Process is obvious
  else if (string_non_resonant_resonant=="Resonant analysis") {
    if (string_category=="f_categories")
      hist_frame->SetXTitle("Category m_{X} [GeV]");
    else
      hist_frame->SetXTitle("m_{X} [GeV]");
  }

  string string_latex_observable_f_characteristic="rel. effect";
  
  if (string_observable_f_characteristic=="yield")
    string_latex_observable_f_characteristic+=" on yield";
  else if (string_observable_f_characteristic=="position_shape")
    string_latex_observable_f_characteristic+=" on position shape";
  else if (string_observable_f_characteristic=="spread_shape")
    string_latex_observable_f_characteristic+=" on spread shape";

  string_latex_observable_f_characteristic+=" [%]";

  hist_frame->SetYTitle(string_latex_observable_f_characteristic.c_str());
  
  //never choose "A" option for graph, since axis chosen with DrawFrame
  
  graph_observable_up_f_characteristic->Draw("P");
  graph_observable_up_f_characteristic->Draw("L");

  if (!is_theory) {
    graph_observable_down_f_characteristic->Draw("P");
    graph_observable_down_f_characteristic->Draw("L");
  }
  
  canvas->RedrawAxis();
  //canvas.RedrawAxis();
 
  //  float position_x=0.45;
  float position_x=0.16;

  TLatex mylatex;
  mylatex.SetNDC();
  mylatex.SetTextAlign(3);
  
  mylatex.SetTextSize(0.05); //0.045 is std
  mylatex.SetTextFont(72);
  mylatex.DrawLatex(position_x,0.92,"ATLAS internal");
  
  mylatex.SetTextSize(0.05); //0.045 is std
  mylatex.SetTextFont(42); //put back the font
  
  //  mylatex.SetTextSize(0.03); //0.045 is std
  mylatex.SetTextSize(0.027); //0.045 is std
  
  float position_y=0.85;
  
  float step_delta_y=0.04;
  
  char buffer_lumi[20];
  sprintf(buffer_lumi,"L=%4.1f fb^{-1}",lumi);
  mylatex.DrawLatex(position_x,position_y,buffer_lumi);
  //  cout << "buffer_lumi=" << buffer_lumi << endl;

  position_y-=step_delta_y;
  //-----
  mylatex.DrawLatex(position_x,position_y,string_non_resonant_resonant.c_str());
  position_y-=step_delta_y;
  //-----
  mylatex.DrawLatex(position_x,position_y,string_category.c_str());
  position_y-=step_delta_y;
  //-----
  mylatex.DrawLatex(position_x,position_y,string_systematic.c_str());
  position_y-=step_delta_y;
  //-----

  /*
  for (unsigned int internal_index_finalDV=0;internal_index_finalDV<vec_string_finalDV.size();internal_index_finalDV++) {
    if (internal_index_finalDV+1<vec_string_finalDV.size())
      mylatex.DrawLatex(position_x,position_y,(vec_string_latex_root_finalDV[internal_index_finalDV]+", ").c_str());
    else
      mylatex.DrawLatex(position_x+0.06*internal_index_finalDV,position_y,vec_string_latex_root_finalDV[internal_index_finalDV].c_str());
  }
  */
  
  //  position_y-=step_delta_y;
  
  /*
  if (string_observable_f_characteristic!="yield" && string_observable_f_characteristic!="efficiency")
    mylatex.DrawLatex(position_x,position_y,(string("Projection: ")+string_finalDV).c_str());
  */
  
  //-----
  TLegend legend(0.15,0.58,0.21,0.69);
  
  legend.SetTextSize(0.04);
  legend.SetBorderSize(2);
  legend.SetBorderSize(0);
  legend.SetLineColor(0);
  legend.SetLineWidth(0);
  legend.SetFillStyle(1001);
  legend.SetFillColor(kWhite);
  
  if (is_theory)
    legend.AddEntry(graph_observable_up_f_characteristic,"sym","lp");
  else {
    legend.AddEntry(graph_observable_up_f_characteristic,"up","lp");
    legend.AddEntry(graph_observable_down_f_characteristic,"down","lp");
  }
  
  legend.Draw();
  //-----
  string string_saveas="figures/";

  if (string_non_resonant_resonant=="Non Resonant analysis")
    string_saveas+="non_resonant";
  else if (string_non_resonant_resonant=="Resonant analysis")
    string_saveas+="resonant";
  string_saveas+="_";
  string_saveas+="Overview_";
  string_saveas+=string_systematic;
  string_saveas+="_";
  string_saveas+=string_observable_f_characteristic;
  
  string_saveas+="_";
  string_saveas+=string_category.c_str();
  
  string_saveas+="_f_characteristic";
  string_saveas+=".png";
  
  canvas->SaveAs(string_saveas.c_str());

  //  cout << "Draw_observable_f_characteristic phase delete hist_frame" << endl;
  
  delete hist_frame;

  //  cout << "Draw_observable_f_characteristic phase delete graph" << endl;
  delete graph_observable_up_f_characteristic;

  if (!is_theory)
    delete graph_observable_down_f_characteristic;
  
  //  cout << "Draw_observable_f_characteristic phase delete canvas" << endl;

  delete canvas;
}
//#######################################################################################################################################################################################################
void ConstructMaxFromListDataCard(vector<string> vec_datacard,string string_category)
{
  ofstream stream_syst_result_max;
  
  vector<string> vec_string_systematics_considered;
  vector<float> vec_rel_effect_up;
  vector<float> vec_rel_effect_down;
  
  int nb_sys=0;
  
  string string_observable_f_characteristic;
  string string_non_resonant_resonant;

  lumi=0;
  
  cout << "vec_datacard.size()=" << vec_datacard.size() << endl;

  if (vec_datacard.size()!=0) {
    string string_result_to_probe=vec_datacard[0];
    
    if (string_result_to_probe.find("mc16a")!=string::npos)
      lumi+=lumi_mc16a;

    if (string_result_to_probe.find("mc16d")!=string::npos)
      lumi+=lumi_mc16d;

    if (string_result_to_probe.find("mc16e")!=string::npos)
      lumi+=lumi_mc16e;

    if (string_result_to_probe.find("yield")!=string::npos)
      string_observable_f_characteristic="yield";
    else if (string_result_to_probe.find("position_shape")!=string::npos)
      string_observable_f_characteristic="position_shape";
    else if (string_result_to_probe.find("spread_shape")!=string::npos)
      string_observable_f_characteristic="spread_shape";

    if (string_result_to_probe.find("Resonant")!=string::npos) //search for the keyword of category
      string_non_resonant_resonant="Resonant analysis";
    else
      string_non_resonant_resonant="Non Resonant analysis";
  }
  //----------------------------------------------
  for (int index_result=0;index_result<vec_datacard.size();index_result++) {
    
    cout << "index_result=" << index_result << " / " << vec_datacard.size() << endl;
    string string_result_to_probe=vec_datacard[index_result];

    //read current result
    ifstream stream_syst_result;
    
    cout << "will open " << string_path+string_result_to_probe << endl;

    stream_syst_result.open((string_path+string_result_to_probe).c_str());
    
    string string_systematic;
    double rel_effect_up;
    double rel_effect_down;
    
    bool err_code=1;
    
    while (err_code) { // for all systematics

      //- - - - -
      cout << "string_result_to_probe=" << string_result_to_probe << endl;
      double characteristic=ReturnCharacteristic(string_result_to_probe);
      cout << "characteristic=" << characteristic << endl;
      
      //for graphical plot of evolution syst=f(characteristic)
      vec_characteristic.clear();

      vec_observable_up_f_characteristic.clear();
      vec_observable_down_f_characteristic.clear();
      //- - - - -

      err_code=(stream_syst_result >> string_systematic);
      cout << "err_code=" << err_code << endl;
      if (!err_code)
	break;
      
      stream_syst_result >> rel_effect_up;
      if (!is_theory)
	stream_syst_result >> rel_effect_down;
      cout << "-----" << endl;
      for (int i=0;i<10;i++)
	cout << "=============================================" << endl;
      
      cout << "string_systematic=" << string_systematic << ", rel_effect_up=" << rel_effect_up;
      if (!is_theory)
	cout << ", rel_effect_down=" << rel_effect_down;

      cout << endl;
      
      if (find(vec_string_systematics_considered.begin(),vec_string_systematics_considered.end(),string_systematic.c_str())!=vec_string_systematics_considered.end()) //already treated : skip the current systematic
	continue;
      
      nb_sys++;
      
      vec_characteristic.push_back(characteristic);
      
      vec_string_systematics_considered.push_back(string_systematic);
      vec_rel_effect_up.push_back(rel_effect_up);
      if (!is_theory)
	vec_rel_effect_down.push_back(rel_effect_down);
      //- - - - -
      //for syst=f(characteristic)

      vec_observable_up_f_characteristic.push_back(rel_effect_up);
      if (!is_theory)
	vec_observable_down_f_characteristic.push_back(rel_effect_down);
      //- - - - -

      //----------------------------------------------
      //search for potential higher value in other files
      for (int index_alternative_results=index_result+1;index_alternative_results<vec_datacard.size();index_alternative_results++) {
	
	string string_result_alternative=vec_datacard[index_alternative_results];
	
	ifstream stream_syst_alternative_result;
	stream_syst_alternative_result.open((string_path+string_result_alternative).c_str());
	
	string string_systematic_alternative_result;
	double rel_effect_up_alternative_result;
	double rel_effect_down_alternative_result;

	bool err_code_alternative_result=1;
	
	while (err_code_alternative_result) { // for all systematics
	  
	  err_code_alternative_result=(stream_syst_alternative_result >> string_systematic_alternative_result);
	  cout << "err_code_alternative_result=" << err_code_alternative_result << endl;
	  if (!err_code_alternative_result) {
	    stream_syst_alternative_result.close();
	    break;
	  }
	  
	  stream_syst_alternative_result >> rel_effect_up_alternative_result;
	  if (!is_theory)
	    stream_syst_alternative_result >> rel_effect_down_alternative_result;

	  cout << "-----" << endl;
	  cout << "string_systematic_alternative_result=" << string_systematic_alternative_result << ", rel_effect_up_alternative_result=" << rel_effect_up_alternative_result;
	  if (!is_theory)
	    cout << ", rel_effect_down_alternative_result=" << rel_effect_down;

	  cout << endl;
	  
	  if (string_systematic_alternative_result==string_systematic) {
	    
	    cout << "found the one we are looking for" << endl;
	    //- - - - -
	    //add in the observable=f(characteristic)
	    
	    vec_characteristic.push_back(ReturnCharacteristic(string_result_alternative));
	    
	    vec_observable_up_f_characteristic.push_back(rel_effect_up_alternative_result);
	    if (!is_theory)
	      vec_observable_down_f_characteristic.push_back(rel_effect_down_alternative_result);
	    //- - - - -
	    if (fabs(rel_effect_up_alternative_result)>fabs(vec_rel_effect_up[nb_sys-1])) {
	      cout << "found higher systematic up in " << string_result_alternative << " : it is " << rel_effect_up_alternative_result << endl;
	      vec_rel_effect_up[nb_sys-1]=rel_effect_up_alternative_result;
	    }
	    
	    if (!is_theory) {
	      if (fabs(rel_effect_down_alternative_result)>fabs(vec_rel_effect_down[nb_sys-1])) {
		cout << "found higher systematic down in " << string_result_alternative << endl;
		vec_rel_effect_down[nb_sys-1]=rel_effect_down_alternative_result;
	      }
	    }
	    
	    stream_syst_alternative_result.close();
	    break; //don't search further in the alternative file : found the common systematic
	  }
	} //end search for all systematics in alternative file
      } //end loop on alternative
     
      if (!is_theory) {
	if (vec_rel_effect_up[nb_sys-1]*vec_rel_effect_down[nb_sys-1]>0) { //if same sign and different to 0
	  cout << "found case with same sign, rel_effect_up=" << vec_rel_effect_up[nb_sys-1] << ", " << ", rel_effect_down=" << vec_rel_effect_down[nb_sys-1] << endl;
	  
	  if (fabs(vec_rel_effect_up[nb_sys-1])>=fabs(vec_rel_effect_down[nb_sys-1])) { //if up is higher or equal, change sign of down : conservative
	    vec_rel_effect_down[nb_sys-1]=-vec_rel_effect_down[nb_sys-1];
	  }
	  else
	    vec_rel_effect_up[nb_sys-1]=-vec_rel_effect_up[nb_sys-1];
	}
      }
      
      //- - - - -
      //make the draw of observable=f(characteristic)

      cout << "call draw with vec_observable_up_f_characteristic.size()=" << vec_observable_up_f_characteristic.size() << endl;

      Draw_observable_f_characteristic(string_non_resonant_resonant,string_systematic,string_observable_f_characteristic,string_category,vec_characteristic,vec_observable_up_f_characteristic,vec_observable_down_f_characteristic);

      /*
      if (nb_sys>1)
	exit(1);
      */
      //- - - - -
      
    } //end loop on all systematics of main file
    
    stream_syst_result.close();
    
  } //end loop on main results
  //----------------------------------------------
  //sort of results

  for (int index_syst_first=0;index_syst_first<nb_sys;index_syst_first++)
    for (int index_syst_second=index_syst_first+1;index_syst_second<nb_sys;index_syst_second++) {
      
      if (vec_string_systematics_considered[index_syst_second]<vec_string_systematics_considered[index_syst_first]) {
	
	string temp_string_systematics_considered=vec_string_systematics_considered[index_syst_first];
	vec_string_systematics_considered[index_syst_first]=vec_string_systematics_considered[index_syst_second];
	vec_string_systematics_considered[index_syst_second]=temp_string_systematics_considered;

	float temp_rel_effect_up=vec_rel_effect_up[index_syst_first];
	vec_rel_effect_up[index_syst_first]=vec_rel_effect_up[index_syst_second];
	vec_rel_effect_up[index_syst_second]=temp_rel_effect_up;

	if (!is_theory) {
	  float temp_rel_effect_down=vec_rel_effect_down[index_syst_first];
	  vec_rel_effect_down[index_syst_first]=vec_rel_effect_down[index_syst_second];
	  vec_rel_effect_down[index_syst_second]=temp_rel_effect_down;
	}
      }
    }
  //-----
  stream_syst_result_max.open((string_path+string_destination_max).c_str(),ofstream::out);
  
  for (int index_syst=0;index_syst<nb_sys;index_syst++) {
    stream_syst_result_max << vec_string_systematics_considered[index_syst] << " " << vec_rel_effect_up[index_syst];
    if (!is_theory)
      stream_syst_result_max << " " << vec_rel_effect_down[index_syst];
    
    stream_syst_result_max << endl;
  }
  
  stream_syst_result_max.close();
  
  //======================================================================
  cout << "end of program" << endl;
  
  vec_string_systematics_considered.clear();
  vec_rel_effect_up.clear();
  vec_rel_effect_down.clear();
}
//###################################################################################################
double Return_numerical_target_kappa(string string_target_kappa)
{
  double sign=1;
  
  int index_first_position=0;
  
  if (string_target_kappa[0]=='n') {
    sign=-1;
    index_first_position=1;
  }
  
  int position_point=0;
  
  int index_character=0;
  
  for (;index_character<string_target_kappa.size() && string_target_kappa[index_character]!='p';index_character++)
    ;
  
  if (index_character>=string_target_kappa.size()) {
    cout << "not found the point, halt program" << endl;
    exit(1);
  }
  
  int index_point=index_character;
  
  //cout << "index_point=" << index_point << endl;
  
  int coefficient_power=index_point-index_first_position-1;
  
  //cout << "index_first_position=" << index_first_position << ", index_point=" << index_point << endl;
  //  cout << "coefficient_power=" << coefficient_power << endl;
  
  double numerical_target_kappa=0;
  
  for (index_character=index_first_position;index_character<string_target_kappa.size();index_character++) {

    char character[1];
    character[0]=string_target_kappa[index_character];
    //    cout << "in loop, coefficient_power=" << coefficient_power << endl;
    //    cout << "before treatment, numerical_target_kappa=" << numerical_target_kappa << endl;
    
    numerical_target_kappa+=atoi(character)*pow(10,coefficient_power);
    //    cout << "after treatment of character index " << index_first_position << ", which is " << string_target_kappa[index_character] << ", numerical_target_kappa=" << numerical_target_kappa << endl;
    
    if (string_target_kappa[index_character]!='p')
      coefficient_power--;
  }
  
  numerical_target_kappa*=sign;

  return numerical_target_kappa;
}
//###################################################################################################

//shit below


    //-----------------------------------------
    //HH non resonant

    //    "datacard_yield_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_01_XGBoost_btag77_withTop_BCal_tightScore_HMass.txt",
    //    "datacard_yield_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_10_XGBoost_btag77_withTop_BCal_tightScore_HMass.txt"

    //    "datacard_position_shape_m_yy_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_01_XGBoost_btag77_withTop_BCal_tightScore_HMass.txt",
    //    "datacard_position_shape_m_yy_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_10_XGBoost_btag77_withTop_BCal_tightScore_HMass.txt"
    
    //    "datacard_spread_shape_m_yy_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_01_XGBoost_btag77_withTop_BCal_tightScore_HMass.txt",
    //    "datacard_spread_shape_m_yy_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_10_XGBoost_btag77_withTop_BCal_tightScore_HMass.txt"
    //-----
    //    "datacard_yield_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_01_XGBoost_btag77_withTop_BCal_looseScore_HMass.txt",
    //    "datacard_yield_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_10_XGBoost_btag77_withTop_BCal_looseScore_HMass.txt"

    //    "datacard_position_shape_m_yy_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_01_XGBoost_btag77_withTop_BCal_looseScore_HMass.txt",
    //    "datacard_position_shape_m_yy_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_10_XGBoost_btag77_withTop_BCal_looseScore_HMass.txt"

    //"datacard_spread_shape_m_yy_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_01_XGBoost_btag77_withTop_BCal_looseScore_HMass.txt",
    //"datacard_spread_shape_m_yy_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_10_XGBoost_btag77_withTop_BCal_looseScore_HMass.txt"
    //-----
    //    "datacard_yield_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_01_XGBoost_btag77_withTop_BCal_tightScore_LMass.txt",
    //    "datacard_yield_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_10_XGBoost_btag77_withTop_BCal_tightScore_LMass.txt"

    //    "datacard_position_shape_m_yy_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_01_XGBoost_btag77_withTop_BCal_tightScore_LMass.txt",
    //    "datacard_position_shape_m_yy_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_10_XGBoost_btag77_withTop_BCal_tightScore_LMass.txt"

    //"datacard_spread_shape_m_yy_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_01_XGBoost_btag77_withTop_BCal_tightScore_LMass.txt",
    //    "datacard_spread_shape_m_yy_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_10_XGBoost_btag77_withTop_BCal_tightScore_LMass.txt"
    //-----
    //    "datacard_yield_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_01_XGBoost_btag77_withTop_BCal_looseScore_LMass.txt",
    //    "datacard_yield_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_10_XGBoost_btag77_withTop_BCal_looseScore_LMass.txt"

    //    "datacard_position_shape_m_yy_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_01_XGBoost_btag77_withTop_BCal_looseScore_LMass.txt",
    //    "datacard_position_shape_m_yy_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_10_XGBoost_btag77_withTop_BCal_looseScore_LMass.txt"

    //     "datacard_spread_shape_m_yy_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_01_XGBoost_btag77_withTop_BCal_looseScore_LMass.txt",
    //     "datacard_spread_shape_m_yy_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_10_XGBoost_btag77_withTop_BCal_looseScore_LMass.txt"

    //-----------------------------------------
    //HH resonant

    /*
    //yield
    "datacard_experimental_yield_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X260tohh_bbyy_AF2_cat_Resonant_mX260.txt",
    "datacard_experimental_yield_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X280tohh_bbyy_AF2_cat_Resonant_mX280.txt",
    "datacard_experimental_yield_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X300tohh_bbyy_AF2_cat_Resonant_mX300.txt",
    "datacard_experimental_yield_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X325tohh_bbyy_AF2_cat_Resonant_mX325.txt",
    "datacard_experimental_yield_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X350tohh_bbyy_AF2_cat_Resonant_mX350.txt",
    "datacard_experimental_yield_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X400tohh_bbyy_AF2_cat_Resonant_mX400.txt",
    "datacard_experimental_yield_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X450tohh_bbyy_AF2_cat_Resonant_mX450.txt",
    "datacard_experimental_yield_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X500tohh_bbyy_AF2_cat_Resonant_mX500.txt",
    "datacard_experimental_yield_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X550tohh_bbyy_AF2_cat_Resonant_mX550.txt",
    "datacard_experimental_yield_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X600tohh_bbyy_AF2_cat_Resonant_mX600.txt",
    "datacard_experimental_yield_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X700tohh_bbyy_AF2_cat_Resonant_mX700.txt",
    "datacard_experimental_yield_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X800tohh_bbyy_AF2_cat_Resonant_mX800.txt",
    "datacard_experimental_yield_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X900tohh_bbyy_AF2_cat_Resonant_mX900.txt",
    "datacard_experimental_yield_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X1000tohh_bbyy_AF2_cat_Resonant_mX1000.txt"
    */

    /*
    //shape : position
    "datacard_experimental_position_shape_m_yy_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X260tohh_bbyy_AF2_cat_Resonant_mX260.txt",
    "datacard_experimental_position_shape_m_yy_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X280tohh_bbyy_AF2_cat_Resonant_mX280.txt",
    "datacard_experimental_position_shape_m_yy_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X300tohh_bbyy_AF2_cat_Resonant_mX300.txt",
    "datacard_experimental_position_shape_m_yy_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X325tohh_bbyy_AF2_cat_Resonant_mX325.txt",
    "datacard_experimental_position_shape_m_yy_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X350tohh_bbyy_AF2_cat_Resonant_mX350.txt",
    "datacard_experimental_position_shape_m_yy_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X400tohh_bbyy_AF2_cat_Resonant_mX400.txt",
    "datacard_experimental_position_shape_m_yy_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X450tohh_bbyy_AF2_cat_Resonant_mX450.txt",
    "datacard_experimental_position_shape_m_yy_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X500tohh_bbyy_AF2_cat_Resonant_mX500.txt",
    "datacard_experimental_position_shape_m_yy_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X550tohh_bbyy_AF2_cat_Resonant_mX550.txt",
    "datacard_experimental_position_shape_m_yy_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X600tohh_bbyy_AF2_cat_Resonant_mX600.txt",
    "datacard_experimental_position_shape_m_yy_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X700tohh_bbyy_AF2_cat_Resonant_mX700.txt",
    "datacard_experimental_position_shape_m_yy_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X800tohh_bbyy_AF2_cat_Resonant_mX800.txt",
    "datacard_experimental_position_shape_m_yy_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X900tohh_bbyy_AF2_cat_Resonant_mX900.txt",
    "datacard_experimental_position_shape_m_yy_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X1000tohh_bbyy_AF2_cat_Resonant_mX1000.txt"
    */

    /*
    //shape : spread
    "datacard_experimental_spread_shape_m_yy_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X260tohh_bbyy_AF2_cat_Resonant_mX260.txt",
    "datacard_experimental_spread_shape_m_yy_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X280tohh_bbyy_AF2_cat_Resonant_mX280.txt",
    "datacard_experimental_spread_shape_m_yy_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X300tohh_bbyy_AF2_cat_Resonant_mX300.txt",
    "datacard_experimental_spread_shape_m_yy_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X325tohh_bbyy_AF2_cat_Resonant_mX325.txt",
    "datacard_experimental_spread_shape_m_yy_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X350tohh_bbyy_AF2_cat_Resonant_mX350.txt",
    "datacard_experimental_spread_shape_m_yy_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X400tohh_bbyy_AF2_cat_Resonant_mX400.txt",
    "datacard_experimental_spread_shape_m_yy_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X450tohh_bbyy_AF2_cat_Resonant_mX450.txt",
    "datacard_experimental_spread_shape_m_yy_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X500tohh_bbyy_AF2_cat_Resonant_mX500.txt",
    "datacard_experimental_spread_shape_m_yy_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X550tohh_bbyy_AF2_cat_Resonant_mX550.txt",
    "datacard_experimental_spread_shape_m_yy_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X600tohh_bbyy_AF2_cat_Resonant_mX600.txt",
    "datacard_experimental_spread_shape_m_yy_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X700tohh_bbyy_AF2_cat_Resonant_mX700.txt",
    "datacard_experimental_spread_shape_m_yy_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X800tohh_bbyy_AF2_cat_Resonant_mX800.txt",
    "datacard_experimental_spread_shape_m_yy_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X900tohh_bbyy_AF2_cat_Resonant_mX900.txt",
    "datacard_experimental_spread_shape_m_yy_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X1000tohh_bbyy_AF2_cat_Resonant_mX1000.txt"
    */

    //-----------------------------------------
    //Single Higgs : to update and see dependence with processes
    /* SHIT : only one campaign !
    "datacard_yield_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX260.txt",
    "datacard_yield_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX280.txt",
    "datacard_yield_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX300.txt",
    "datacard_yield_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX325.txt",
    "datacard_yield_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX350.txt",
    "datacard_yield_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX400.txt",
    "datacard_yield_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX450.txt",
    "datacard_yield_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX500.txt",
    "datacard_yield_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX550.txt",
    "datacard_yield_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX600.txt",
    "datacard_yield_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX700.txt",
    "datacard_yield_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX800.txt",
    "datacard_yield_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX900.txt",
    "datacard_yield_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX1000.txt"
    */

    /*
    "datacard_position_shape_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX260.txt",
    "datacard_position_shape_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX280.txt",
    "datacard_position_shape_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX300.txt",
    "datacard_position_shape_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX325.txt",
    "datacard_position_shape_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX350.txt",
    "datacard_position_shape_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX400.txt",
    "datacard_position_shape_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX450.txt",
    "datacard_position_shape_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX500.txt",
    "datacard_position_shape_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX550.txt",
    "datacard_position_shape_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX600.txt",
    "datacard_position_shape_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX700.txt",
    "datacard_position_shape_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX800.txt",
    "datacard_position_shape_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX900.txt",
    "datacard_position_shape_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX1000.txt"
    */

    /*
      "datacard_spread_shape_m_yy_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX260.txt",
    "datacard_spread_shape_m_yy_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX280.txt",
    "datacard_spread_shape_m_yy_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX300.txt",
    "datacard_spread_shape_m_yy_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX325.txt",
    "datacard_spread_shape_m_yy_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX350.txt",
    "datacard_spread_shape_m_yy_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX400.txt",
    "datacard_spread_shape_m_yy_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX450.txt",
    "datacard_spread_shape_m_yy_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX500.txt",
    "datacard_spread_shape_m_yy_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX550.txt",
    "datacard_spread_shape_m_yy_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX600.txt",
    "datacard_spread_shape_m_yy_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX700.txt",
    "datacard_spread_shape_m_yy_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX800.txt",
    "datacard_spread_shape_m_yy_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX900.txt",
    "datacard_spread_shape_m_yy_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_mX1000.txt"
    */

    /*
    "datacard_yield_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX260.txt",
    "datacard_yield_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX280.txt",
    "datacard_yield_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX300.txt",
    "datacard_yield_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX325.txt",
    "datacard_yield_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX350.txt",
    "datacard_yield_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX400.txt",
    "datacard_yield_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX450.txt",
    "datacard_yield_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX500.txt",
    "datacard_yield_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX550.txt",
    "datacard_yield_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX600.txt",
    "datacard_yield_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX700.txt",
    "datacard_yield_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX800.txt",
    "datacard_yield_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX900.txt",
    "datacard_yield_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX1000.txt"
    */

    /*
    "datacard_position_shape_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX260.txt",
    "datacard_position_shape_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX280.txt",
    "datacard_position_shape_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX300.txt",
    "datacard_position_shape_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX325.txt",
    "datacard_position_shape_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX350.txt",
    "datacard_position_shape_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX400.txt",
    "datacard_position_shape_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX450.txt",
    "datacard_position_shape_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX500.txt",
    "datacard_position_shape_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX550.txt",
    "datacard_position_shape_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX600.txt",
    "datacard_position_shape_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX700.txt",
    "datacard_position_shape_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX800.txt",
    "datacard_position_shape_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX900.txt",
    "datacard_position_shape_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX1000.txt"
    */

    /*    
    "datacard_spread_shape_m_yy_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX260.txt",
    "datacard_spread_shape_m_yy_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX280.txt",
    "datacard_spread_shape_m_yy_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX300.txt",
    "datacard_spread_shape_m_yy_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX325.txt",
    "datacard_spread_shape_m_yy_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX350.txt",
    "datacard_spread_shape_m_yy_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX400.txt",
    "datacard_spread_shape_m_yy_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX450.txt",
    "datacard_spread_shape_m_yy_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX500.txt",
    "datacard_spread_shape_m_yy_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX550.txt",
    "datacard_spread_shape_m_yy_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX600.txt",
    "datacard_spread_shape_m_yy_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX700.txt",
    "datacard_spread_shape_m_yy_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX800.txt",
    "datacard_spread_shape_m_yy_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX900.txt",
    "datacard_spread_shape_m_yy_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_mX1000.txt"
    */


//HH non resonant

//string string_destination_max="datacard_yield_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_MAX_XGBoost_btag77_withTop_BCal_tightScore_HMass.txt";
//string string_destination_max="datacard_position_shape_m_yy_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_MAX_XGBoost_btag77_withTop_BCal_tightScore_HMass.txt";
//string string_destination_max="datacard_spread_shape_m_yy_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_MAX_XGBoost_btag77_withTop_BCal_tightScore_HMass.txt";

//string string_destination_max="datacard_yield_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_MAX_XGBoost_btag77_withTop_BCal_looseScore_HMass.txt";
//string string_destination_max="datacard_position_shape_m_yy_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_MAX_XGBoost_btag77_withTop_BCal_looseScore_HMass.txt";
//string string_destination_max="datacard_spread_shape_m_yy_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_MAX_XGBoost_btag77_withTop_BCal_looseScore_HMass.txt";

//string string_destination_max="datacard_yield_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_MAX_XGBoost_btag77_withTop_BCal_tightScore_LMass.txt";
//string string_destination_max="datacard_position_shape_m_yy_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_MAX_XGBoost_btag77_withTop_BCal_tightScore_LMass.txt";
//string string_destination_max="datacard_spread_shape_m_yy_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_MAX_XGBoost_btag77_withTop_BCal_tightScore_LMass.txt";

//string string_destination_max="datacard_yield_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_MAX_XGBoost_btag77_withTop_BCal_looseScore_LMass.txt";
//string string_destination_max="datacard_position_shape_m_yy_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_MAX_XGBoost_btag77_withTop_BCal_looseScore_LMass.txt";
//string string_destination_max="datacard_spread_shape_m_yy_h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_MAX_XGBoost_btag77_withTop_BCal_looseScore_LMass.txt";
//-----------------------------------------
//Single Higgs
//string string_destination_max="datacard_yield_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_Max_among_mX.txt";
//string string_destination_max="datacard_position_shape_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_Max_among_mX.txt";
//string string_destination_max="datacard_spread_shape_h025_mc16a_h025_mc16d_h025_mc16e_SingleHiggs_Resonant_Max_among_mX.txt";

//string string_destination_max="datacard_yield_h025_mc16d_HH_non_resonant_kappa_lambda_01_Max_among_mX.txt";
//string string_destination_max="datacard_position_shape_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_Max_among_mX.txt";
//string string_destination_max="datacard_spread_shape_h025_mc16d_HH_non_resonant_kappa_lambda_01_Resonant_Max_among_mX.txt";
//-----------------------------------------
//Signal HH resonant

//string string_destination_max="datacard_experimental_yield_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_Xtohh_bbyy_AF2_cat_Resonant_Max_among_mX.txt";
//string string_destination_max="datacard_experimental_position_shape_proc_h026_mc16a_h026_mc16d_h026_mc16e_MGH7_Xtohh_bbyy_AF2_cat_Resonant_Max_among_mX.txt";
//string string_destination_max="datacard_experimental_spread_shape_proc_MGH7_Xtohh_bbyy_AF2_cat_Resonant_Max_among_mX.txt";
