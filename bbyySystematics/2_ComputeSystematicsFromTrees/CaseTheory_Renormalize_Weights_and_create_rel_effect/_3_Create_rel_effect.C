//to make a function, for creating list of categories, in common with other : a tool ?

//---------------------------------------------------------------------------------------------------
string string_sample="kappa_lambda_samples";

//for single higgs, careful : to develop

//candidates

//ttH
//Resonant_samples
//"PowhegH7_HHbbyy_cHHH01d0"
//"PowhegH7_HHbbyy_cHHH10d0"
//"kappa_lambda_samples"
//---------------------------------------------------------------------------------------------------
//root -b
//.x _3_Create_rel_effect.C

/*note that
T.SetBranchStatus("*",0); //disable all branches
T.SetBranchStatus("c",1);
T.setBranchStatus("e",1);
T.GetEntry(i);
*/

//root -b
//.x 3_Create_rel_effect.C

using namespace std;

string string_path="/sps/atlas/e/escalier/ATLAS_HGam/";

string string_rel_path="Outputs_syst_yield_shape/trees_and_hist/Theory/";

string string_prefix_tree="tree_sel_";
vector<string> vec_string_category;

vector<string> vec_files={};

//for potential categories
//not add the 251 ?
vector<int> vec_mX_th_systematics={251,260,280,300,325,350,400,450,500,550,600,700,800,900,1000};

//prototypes

vector<string> CreateList_HH_non_resonant_kappa_lambda();
string Return_string_target_kappa(double numerical_target_kappa);

pair<double,double> return_nb_sel(TTree *tree);

double get_err_rel_effect_yield_fully_correlated(double yield_nominal,
						 double yield_sys,
						 double err_yield_nominal,
						 double err_yield_sys);

#include "tool_CreateList_HH_non_resonant_kappa_lambda.C"
#include "tool_CreateList_Categories.C"

//#####################################################################################################################################################
int _3_Create_rel_effect()
{
  if (string_sample=="kappa_lambda_samples") {
    //==============================================================
    //special case of reweighted kappa lambda
    
    vector<string> vec_string_kappa_lambda_destination=CreateList_HH_non_resonant_kappa_lambda();
    
    vec_string_kappa_lambda_destination=CreateList_HH_non_resonant_kappa_lambda();
    
    cout << "vec_string_kappa_lambda_destination[0]=" << vec_string_kappa_lambda_destination[0] << endl;
    
    for (int index_kappa_lambda=0;index_kappa_lambda<vec_string_kappa_lambda_destination.size();index_kappa_lambda++) {
      vec_files.push_back("h026_mc16a_PowhegPy8_HHbbyy_reweight_mHH_1p0_to_"+vec_string_kappa_lambda_destination[index_kappa_lambda]+"_nominal.root");
      vec_files.push_back("h026_mc16d_PowhegPy8_HHbbyy_reweight_mHH_1p0_to_"+vec_string_kappa_lambda_destination[index_kappa_lambda]+"_nominal.root");
      vec_files.push_back("h026_mc16e_PowhegPy8_HHbbyy_reweight_mHH_1p0_to_"+vec_string_kappa_lambda_destination[index_kappa_lambda]+"_nominal.root");

      /*
      vec_files.push_back("h026_mc16a_PowhegH7_HHbbyy_reweight_mHH_1p0_to_"+vec_string_kappa_lambda_destination[index_kappa_lambda]+"_nominal.root");
      vec_files.push_back("h026_mc16d_PowhegH7_HHbbyy_reweight_mHH_1p0_to_"+vec_string_kappa_lambda_destination[index_kappa_lambda]+"_nominal.root");
      vec_files.push_back("h026_mc16e_PowhegH7_HHbbyy_reweight_mHH_1p0_to_"+vec_string_kappa_lambda_destination[index_kappa_lambda]+"_nominal.root");
      */
    }
  }

  /*
  //---------------------------------------------------------  
  //ggH

  "h026_mc16a_PowhegPy8_NNLOPS_ggH125_PhotonSys.root",
  "h026_mc16d_PowhegPy8_NNLOPS_ggH125_PhotonSys.root",
  "h026_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys.root"
  //,
  */


  else if (string_sample=="ZH") {
    vec_files.push_back("h026_mc16a_PowhegPy8_ZH125J_PhotonSys.root");
    vec_files.push_back("h026_mc16d_PowhegPy8_ZH125J_PhotonSys.root");
    vec_files.push_back("h026_mc16e_PowhegPy8_ZH125J_PhotonSys.root");
    vec_files.push_back("h026_mc16a_PowhegPy8_ggZH125_PhotonSys.root");
    vec_files.push_back("h026_mc16d_PowhegPy8_ggZH125_PhotonSys.root");
    vec_files.push_back("h026_mc16e_PowhegPy8_ggZH125_PhotonSys.root");
  }


  else if (string_sample=="ttH") {
    vec_files.push_back("h026_mc16a_PowhegPy8_ttH125_fixweight_PhotonSys.root");
    vec_files.push_back("h026_mc16d_PowhegPy8_ttH125_fixweight_PhotonSys.root");
    vec_files.push_back("h026_mc16d_PowhegPy8_ttH125_fixweight_PhotonSys.root");
  }
  else if (string_sample=="Resonant_samples") {
    vec_files.push_back("h026_mc16a_MGH7_X251tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16d_MGH7_X251tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16e_MGH7_X251tohh_bbyy_AF2_nominal.root");

    vec_files.push_back("h026_mc16a_MGH7_X260tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16d_MGH7_X260tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16e_MGH7_X260tohh_bbyy_AF2_nominal.root");

    vec_files.push_back("h026_mc16a_MGH7_X280tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16d_MGH7_X280tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16e_MGH7_X280tohh_bbyy_AF2_nominal.root");

    vec_files.push_back("h026_mc16a_MGH7_X300tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16d_MGH7_X300tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16e_MGH7_X300tohh_bbyy_AF2_nominal.root");

    vec_files.push_back("h026_mc16a_MGH7_X325tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16d_MGH7_X325tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16e_MGH7_X325tohh_bbyy_AF2_nominal.root");

    vec_files.push_back("h026_mc16a_MGH7_X350tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16d_MGH7_X350tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16e_MGH7_X350tohh_bbyy_AF2_nominal.root");

    vec_files.push_back("h026_mc16a_MGH7_X400tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16d_MGH7_X400tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16e_MGH7_X400tohh_bbyy_AF2_nominal.root");

    vec_files.push_back("h026_mc16a_MGH7_X450tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16d_MGH7_X450tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16e_MGH7_X450tohh_bbyy_AF2_nominal.root");

    vec_files.push_back("h026_mc16a_MGH7_X500tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16d_MGH7_X500tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16e_MGH7_X500tohh_bbyy_AF2_nominal.root");

    vec_files.push_back("h026_mc16a_MGH7_X550tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16d_MGH7_X550tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16e_MGH7_X550tohh_bbyy_AF2_nominal.root");

    vec_files.push_back("h026_mc16a_MGH7_X600tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16d_MGH7_X600tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16e_MGH7_X600tohh_bbyy_AF2_nominal.root");

    vec_files.push_back("h026_mc16a_MGH7_X700tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16d_MGH7_X700tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16e_MGH7_X700tohh_bbyy_AF2_nominal.root");

    vec_files.push_back("h026_mc16a_MGH7_X800tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16d_MGH7_X800tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16e_MGH7_X800tohh_bbyy_AF2_nominal.root");

    vec_files.push_back("h026_mc16a_MGH7_X900tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16d_MGH7_X900tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16e_MGH7_X900tohh_bbyy_AF2_nominal.root");

    vec_files.push_back("h026_mc16a_MGH7_X1000tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16d_MGH7_X1000tohh_bbyy_AF2_nominal.root");
    vec_files.push_back("h026_mc16e_MGH7_X1000tohh_bbyy_AF2_nominal.root");
  }
  else {
    //TO MAKE A IF DEPENDING ON SAMPLE
    
    vec_files.push_back((string("h026_mc16a_")+string_sample+"_nominal.root").c_str());
    vec_files.push_back((string("h026_mc16d_")+string_sample+"_nominal.root").c_str());
    vec_files.push_back((string("h026_mc16e_")+string_sample+"_nominal.root").c_str());
  }
  

  for (int index_file=0;index_file<vec_files.size();index_file++) {
    cout << "index_file=" << index_file << ", name=" << vec_files[index_file] << endl;
  }

  //==============================================================
  //else, put a dedicated sample and don't call previous block

  //==============================================================
  for (int index_file=0;index_file<vec_files.size();index_file++) {
    cout << "==================================================================" << endl;

    string string_file_raw=vec_files[index_file];

    string string_file="";

    //no more useful    string prefix_file="tree_";

    string_file+=string_file_raw;
    
    cout << "string_file=" << string_file << endl;
    
    size_t position_string_root=0;
    
    position_string_root=string_file.find(".root");
    
    if (position_string_root==string::npos) {
      cout << "problem, didn't found the root suffix, halt program" << endl;
      exit(1);
    }

    //----------------------------------------------------------------------------------------------
    //creation of categories

    vec_string_category.clear();

    vec_string_category=CreateListCategories(string_file);

    cout << endl;
    cout << endl;
    cout << endl;

    for (int index_category=0;index_category<vec_string_category.size();index_category++)
      cout << "index_category=" << index_category << ", " << vec_string_category[index_category] << endl;
   
    //----------------------------------------------------------------------------------------------
    
    cout << "index_file=" << index_file << " / " << vec_files.size() << endl;

    TFile *f_source_being_updated=TFile::Open((string_path+string_rel_path+vec_files[index_file]).c_str(),"update");
    
    cout << "(string_path+string_rel_path+vec_files[index_file])=" << (string_path+string_rel_path+vec_files[index_file]) << endl;
    f_source_being_updated->cd();

    TList *list=f_source_being_updated->GetListOfKeys();

    int nb_keys=list->GetEntries();
    
    for (int index_category=0;index_category<vec_string_category.size();index_category++) {
      
      string string_category=vec_string_category[index_category];

      pair<double,double> pair_nb_sel_nominal;
      pair<double,double> pair_nb_sel_sys;

      bool found_nominal=0;
      
      for (int index_key=0;index_key<nb_keys;index_key++) {
	//cout << "index_key=" << index_key << endl;
	
	TKey *key=(TKey *)list->At(index_key);
	
	if (strcmp(key->GetClassName(),"TTree"))
	  continue;
	
	//this is a TTree at this place
	
	char *name_tree=(char *)key->GetName();
	
	TTree *tree=(TTree *)f_source_being_updated->Get(name_tree);
	
	//      cout << "tree->GetName()=" << tree->GetName() << endl;
	
	string string_tree=name_tree;
	
	if (string_tree.find(string_category)==string::npos) //ignore if it does not belong to current category
	  continue;
	//----------
	//identify the variation : remove word Inclusive or other word of category
	
	int size_string_prefix_tree=string_prefix_tree.size();
	
	size_t position_string_category=0;
	
	int index_category=0;
	
	position_string_category=string_tree.find(string_category);
	
	if (position_string_category==string::npos) {
	  cout << "problem, didn't found the category, halt program" << endl;
	  exit(1);
	}
	
	position_string_category--; //take into account the "_" before the category
	string string_variation=string_tree.substr(size_string_prefix_tree,position_string_category-size_string_prefix_tree);
	
	cout << "===" << endl;
	cout << "dealing with string_variation=" << string_variation << ", tree=" << name_tree << endl;
	//----------	
	if (string_variation=="nominal") {
	  found_nominal=1;

	  pair_nb_sel_nominal=return_nb_sel(tree);
	}
	else
	  pair_nb_sel_sys=return_nb_sel(tree);
	
	if (found_nominal && string_variation=="nominal") { //write the results
	  string string_hist_nb_sel_nominal="hist_nb_sel_nominal";
	  
	  string_hist_nb_sel_nominal+="_";
	  string_hist_nb_sel_nominal+=string_category;
	  
	  cout << "string_hist_nb_sel_nominal=" << string_hist_nb_sel_nominal << endl;

	  TH1D hist_nb_sel_nominal(string_hist_nb_sel_nominal.c_str(),string_hist_nb_sel_nominal.c_str(),1,-1e9,1e9);
	  hist_nb_sel_nominal.SetBinContent(1,pair_nb_sel_nominal.first);
	  hist_nb_sel_nominal.SetBinError(1,pair_nb_sel_nominal.second);

	  hist_nb_sel_nominal.Write();
	}	  
	else if (found_nominal && string_variation!="nominal") { //write the results

	  string string_hist_nb_sel_sys="hist_nb_sel_sys_";

	  string_hist_nb_sel_sys+=string_variation;
	  string_hist_nb_sel_sys+="_";
	  string_hist_nb_sel_sys+=string_category;

	  cout << "string_hist_nb_sel_sys=" << string_hist_nb_sel_sys << endl;

	  TH1D hist_nb_sel_sys(string_hist_nb_sel_sys.c_str(),string_hist_nb_sel_sys.c_str(),1,-1e9,1e9);
	  hist_nb_sel_sys.SetBinContent(1,pair_nb_sel_sys.first);
	  hist_nb_sel_sys.SetBinError(1,pair_nb_sel_sys.second);
	  
	  //=====================================================================================================================================================

	  hist_nb_sel_sys.Write();

	} //end write results
	
	//      vec_string_branch_weights.clear();
	
	//      return 0;
      } //end list of keys
      
    } //end loop on category
    
    f_source_being_updated->Close();

  } //end list of files
  
  return 0;
}
//#####################################################################################################################################################
//return_b_sel
pair<double,double> return_nb_sel(TTree *tree)
{
  double weight_total=0;
  
  TBranch *branch_weight_total=0;
  
  //      tree->SetBranchAddress("weight_event",&weight_event);
  //      tree->SetBranchAddress("weight_lumi",&weight_lumi);
  
  tree->SetBranchAddress("weight_total",&weight_total,&branch_weight_total);

  double nb_sel=0;
  double err_nb_sel=0;

  int nb_entries=tree->GetEntries();
  
  for (int index_entry=0;index_entry<nb_entries;index_entry++) {
    //for (int index_entry=0;index_entry<5;index_entry++) {
    
    //cout << "index_entry=" << index_entry << endl;
    
    //	tree->GetEntry(index_entry);
    
    branch_weight_total->GetEntry(index_entry);
    
    nb_sel+=weight_total;
    err_nb_sel+=weight_total*weight_total;
    
  } //end loop on entries

  err_nb_sel=sqrt(err_nb_sel);

  cout << "nb_sel=" << nb_sel << " +/- " << err_nb_sel << endl;

  return make_pair(nb_sel,err_nb_sel);
  //  exit(1);
}
//#####################################################################################################################################################
double get_err_rel_effect_yield_fully_correlated(double yield_nominal,
						 double yield_sys,
						 double err_yield_nominal,
						 double err_yield_sys)
{
  double local_err_rel_effect_yield=100.*sqrt(
					      (pow(yield_sys,2)*pow(err_yield_nominal,2)/pow(yield_nominal,4))
					      +(pow(err_yield_sys,2)/pow(yield_nominal,2))
					      -2.*yield_sys*err_yield_nominal*err_yield_sys/pow(yield_nominal,3)
					      );
  cout << "- - - - - - - - - - - - - -" << endl;
  cout << "full treatment" << endl;
  cout << "yield_nominal=" << yield_nominal << endl;
  cout << "yield_sys=" << yield_sys << endl;
  cout << "err_yield_nominal=" << err_yield_nominal << endl;
  cout << "err_yield_sys=" << err_yield_sys << endl;
  
  cout << "local_err_rel_effect_yield=" << local_err_rel_effect_yield << endl;

  return local_err_rel_effect_yield;
}
//#####################################################################################################################################################
