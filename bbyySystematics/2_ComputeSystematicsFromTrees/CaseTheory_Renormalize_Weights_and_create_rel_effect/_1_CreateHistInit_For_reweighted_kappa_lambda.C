//First, crease the reweighted samples from ReweightingKappaLambda

//do not put log, else too much space, or put log outside : in sps

//This program is only for theoretical systematic of HH non resonant reweighted samples
//.x _1_CreateHistInit_For_reweighted_kappa_lambda.C

//18 minutes for all kappa lambda

using namespace std;

string string_path="/sps/atlas/e/escalier/ATLAS_HGam/";

string string_rel_path="Outputs_syst_yield_shape/trees_and_hist/subjobs/to_correct_weights/Theory/";

string string_prefix_tree="tree_init_";

//TO DO : make a vector of construction of the files : create list from other program

vector<string> vec_files;

//for potential categories

//prototypes

vector<string> CreateList_HH_non_resonant_kappa_lambda();
string Return_string_target_kappa(double numerical_target_kappa);
pair<double,double> return_nb_init(TTree *tree);

#include "tool_CreateList_HH_non_resonant_kappa_lambda.C"

//###################################################################################################
int _1_CreateHistInit_For_reweighted_kappa_lambda()
{
  //==============================================================
  //special case of reweighted kappa lambda

  vector<string> vec_string_kappa_lambda_destination=CreateList_HH_non_resonant_kappa_lambda();

  vec_string_kappa_lambda_destination=CreateList_HH_non_resonant_kappa_lambda();
  
  cout << "vec_string_kappa_lambda_destination[0]=" << vec_string_kappa_lambda_destination[0] << endl;

  for (int index_kappa_lambda=0;index_kappa_lambda<vec_string_kappa_lambda_destination.size();index_kappa_lambda++) {
    vec_files.push_back("h026_mc16a_PowhegPy8_HHbbyy_reweight_mHH_1p0_to_"+vec_string_kappa_lambda_destination[index_kappa_lambda]+"_nominal.root");
    vec_files.push_back("h026_mc16d_PowhegPy8_HHbbyy_reweight_mHH_1p0_to_"+vec_string_kappa_lambda_destination[index_kappa_lambda]+"_nominal.root");
    vec_files.push_back("h026_mc16e_PowhegPy8_HHbbyy_reweight_mHH_1p0_to_"+vec_string_kappa_lambda_destination[index_kappa_lambda]+"_nominal.root");

    /*old generator
    vec_files.push_back("h026_mc16a_PowhegH7_HHbbyy_reweight_mHH_1p0_to_"+vec_string_kappa_lambda_destination[index_kappa_lambda]+"_nominal.root");
    //added
    vec_files.push_back("h026_mc16d_PowhegH7_HHbbyy_reweight_mHH_1p0_to_"+vec_string_kappa_lambda_destination[index_kappa_lambda]+"_nominal.root");
    vec_files.push_back("h026_mc16e_PowhegH7_HHbbyy_reweight_mHH_1p0_to_"+vec_string_kappa_lambda_destination[index_kappa_lambda]+"_nominal.root");
    */
  }
  
  for (int index_file=0;index_file<vec_files.size();index_file++) {
    cout << "index_file=" << index_file << ", name=" << vec_files[index_file] << endl;
  }
  //==============================================================
  for (int index_file=0;index_file<vec_files.size();index_file++) {
    cout << "==================================================================" << endl;

    string string_file_raw=vec_files[index_file];

    string string_file="";

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

    //HH non resonant baseline
   
    //----------------------------------------------------------------------------------------------
    
    cout << "index_file=" << index_file << " / " << vec_files.size() << endl;

    TFile *f_source=TFile::Open((string_path+string_rel_path+vec_files[index_file]).c_str(),"update");
    
    cout << "(string_path+string_rel_path+vec_files[index_file])=" << (string_path+string_rel_path+vec_files[index_file]) << endl;
    f_source->cd();

    TList *list=f_source->GetListOfKeys();

    int nb_keys=list->GetEntries();
    
    pair<double,double> pair_nb_init_nominal;
    pair<double,double> pair_nb_init_sys;
    
    bool found_nominal=0;
    
    int nb_considered_key=0;


    cout << "nb_keys=" << nb_keys << endl;


    for (int index_key=0;index_key<nb_keys;index_key++) {
      cout << "index_key=" << index_key << endl;
      
      TKey *key=(TKey *)list->At(index_key);
      
      if (strcmp(key->GetClassName(),"TTree"))
	continue;
      
      //this is a TTree at this place
      
      char *name_tree=(char *)key->GetName();
      
      string string_tree=name_tree;
      
      if (string_tree.find("tree_init")==string::npos) //consider only tree_init : so skip tree without that name
	continue;
      
      nb_considered_key++;

      //       if (nb_considered_key>2)
      // 	continue;
      
      cout << "string_tree=" << string_tree << ", name_tree=" << name_tree << endl;
      
      TTree *tree=(TTree *)f_source->Get(name_tree);
      
      //      cout << "tree=" << tree << endl;

      //      tree->Scan("weight_total");

      cout << "tree->GetName()=" << tree->GetName() << endl;
      
      //----------
      //identify the variation : remove word Inclusive or other word of category
      
      int size_string_prefix_tree=string_prefix_tree.size();
      
      size_t position_string_category=0;
      
      string string_variation=string_tree.substr(size_string_prefix_tree,string_tree.size()-size_string_prefix_tree);
      
      cout << "dealing with string_variation=" << string_variation << ", tree=" << name_tree << endl;
      
      //----------	
      if (string_variation=="nominal") {
	found_nominal=1;
	
	//	cout << "treat nominal" << endl;

	pair_nb_init_nominal=return_nb_init(tree);
      }
      else
	pair_nb_init_sys=return_nb_init(tree);
      
      if (found_nominal && string_variation=="nominal") { //write the results
	string string_hist_init_nominal="hist_init_nominal";
	
	//cout << "string_hist_nb_init_nominal=" << string_hist_nb_init_nominal << endl;
	
	TH1D hist_init_nominal(string_hist_init_nominal.c_str(),string_hist_init_nominal.c_str(),1,-1e9,1e9);
	hist_init_nominal.SetBinContent(1,pair_nb_init_nominal.first);
	hist_init_nominal.SetBinError(1,pair_nb_init_nominal.second);
	
	//	cout << "write " << string_hist_init_nominal << endl;
	hist_init_nominal.Write();
      }	  
      else if (found_nominal && string_variation!="nominal") { //write the results
	string string_hist_nb_init_sys="hist_init_";
	string_hist_nb_init_sys+=string_variation;
	
	TH1D hist_init_sys(string_hist_nb_init_sys.c_str(),string_hist_nb_init_sys.c_str(),1,-1e9,1e9);
	hist_init_sys.SetBinContent(1,pair_nb_init_sys.first);
	hist_init_sys.SetBinError(1,pair_nb_init_sys.second);
	//=====================================================================================================================================================
	
	hist_init_sys.Write();

	//	cout << "Write string_hist_init_sys=" << string_hist_nb_init_sys << endl;
      } //end write results
      
      //      vec_string_branch_weights.clear();
      
      //      return 0;
    } //end list of keys
    
  } //end list of files
  
  return 0;
}
//###################################################################################################
//return_b_sel
pair<double,double> return_nb_init(TTree *tree)
{
  //  cout << "in return_nb_init, tree=" << tree << endl;
  double weight_total=0;
  
  TBranch *branch_weight_total=0;
  
  tree->SetBranchAddress("weight_total",&weight_total,&branch_weight_total);

  double nb_init=0;
  double err_nb_init=0;

  int nb_entries=tree->GetEntries();
  
  //  cout << "nb_entries=" << nb_entries << endl;

  for (int index_entry=0;index_entry<nb_entries;index_entry++) {
  //  for (int index_entry=0;index_entry<nb_entries;index_entry++) {
  //  for (int index_entry=0;index_entry<10;index_entry++) {
    //for (int index_entry=0;index_entry<5;index_entry++) {
    
    //cout << "index_entry=" << index_entry << endl;
    
    //	tree->GetEntry(index_entry);
    
    branch_weight_total->GetEntry(index_entry);
    
    nb_init+=weight_total;
    err_nb_init+=weight_total*weight_total;

    //printf("entry=%d, weight_total=%10.10f, so far nb_init=%10.10f\n",index_entry,weight_total,nb_init);
    
  } //end loop on entries

  err_nb_init=sqrt(err_nb_init);

  printf("nb_init=%10.10f +/- %10.10f\n",nb_init,err_nb_init);

  return make_pair(nb_init,err_nb_init);
}
//###################################################################################################
