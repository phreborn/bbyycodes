//estimation: 120 hours for 3 mc16a, mc16d, mc16e, 80 syst, up, down, 4 cateogries, etc., uncommon, common, etc.
-->Not good approach

//careful, in case of chain, need to change to centry

//careful : h026 : TO ADD the mc_ID !!

//to do only for HH samples

string string_path="/sps/atlas/e/escalier/ATLAS_HGam/";
string string_rel_path_shape="Outputs_syst_yield_shape/trees_and_hist/";

string string_prefix_tree="tree_sel_";

vector<string> vec_MxAODSyst_directory={"PhotonSys"};

//vector<string> vec_MxAODSyst_directory={"PhotonSys","JetSys1","JetSys2","JetSys3","JetSys4","FlavorSys"}; //"Theory"

vector<string> vec_string_category={"XGBoost_btag77_withTop_BCal_tightScore_HMass"};

/*
vector<string> vec_string_category={"XGBoost_btag77_withTop_BCal_tightScore_HMass",
				    "XGBoost_btag77_withTop_BCal_looseScore_HMass",
				    "XGBoost_btag77_withTop_BCal_tightScore_LMass",
				    "XGBoost_btag77_withTop_BCal_looseScore_LMass"};
*/

//could accomodate from the hadded sample

string string_file="h026_mc16d_PowhegH7_HHbbyy_cHHH01d0_PhotonSys.root";

//to read file list systematics
vector<string> vec_string_systematic={"EG_SCALE_ALL"};

vector<string> vec_nature_syst_components_sym_asym={"","__1up","__1down"}; //some systematics have a symmetric split, some others not

//to do a connection between systematic and mxaodsyst_directory

int CreateHistSystYields_CommonUncommon()
{
  TH1::SetDefaultSumw2(1);
  //-------------------------------------------------------------------------------------------------
  for (int index_MxAODSyst_directory=0;index_MxAODSyst_directory<vec_MxAODSyst_directory.size();index_MxAODSyst_directory++) {
    
    string string_MxAODSyst_directory=vec_MxAODSyst_directory[index_MxAODSyst_directory];
    cout << "string_MxAODSyst_directory=" << string_MxAODSyst_directory << endl;
    
    TFile *f_source=TFile::Open((string_path+string_rel_path_shape+string_MxAODSyst_directory+"/"+string_file).c_str());
    f_source->cd();
    
    //    f_source->ls();

    //-------------------------------------------------------------------------------------------------
    for (int index_category=0;index_category<vec_string_category.size();index_category++) {
      
      cout << "index_category=" << index_category << " / " << vec_string_category.size() << endl;
      string string_category=vec_string_category[index_category];
      
      cout << "string_category=" << string_category << endl;
      //-------------------------------------------------------------------------------------------------
      int nb_sys=vec_string_systematic.size();
      
      for (int index_sys=0;index_sys<nb_sys;index_sys++) {
	
	cout << "index_sys=" << index_sys << " / " << nb_sys << endl;

	string string_systematic=vec_string_systematic[index_sys];
	//-------------------------------------------------------------------------------------------------
	for (int index_nature_syst_components_sym_asym=1;index_nature_syst_components_sym_asym<2;index_nature_syst_components_sym_asym++) {
	  //	for (int index_nature_syst_components_sym_asym=1;nature_syst_components_sym_asym<vec_nature_syst_components_sym_asym.size();nature_syst_components_sym_asym++) {
	  
	  cout << "index_nature_syst_components_sym_asym=" << index_nature_syst_components_sym_asym << endl;
	  
	  string string_nature_syst_components_sym_asym=vec_nature_syst_components_sym_asym[index_nature_syst_components_sym_asym];
	  
	  string string_name_tree_nominal="tree_sel_nominal_";
	  string_name_tree_nominal+=string_category;
	  
	  string string_name_tree_sys="tree_sel_";
	  string_name_tree_sys+=string_systematic;
	  string_name_tree_sys+=string_nature_syst_components_sym_asym;
	  string_name_tree_sys+="_";
	  string_name_tree_sys+=string_category;
	  
	  TTree *tree_nominal=(TTree *)f_source->Get(string_name_tree_nominal.c_str());
	  TTree *tree_sys=(TTree *)f_source->Get(string_name_tree_sys.c_str());
    
	  int eventNumber_nominal;
	  TBranch *branch_eventNumber_nominal=0;
	  
	  int mcID_nominal;
	  TBranch *branch_mcID_nominal=0;
	  
	  double weight_total_nominal=0;
	  TBranch *branch_weight_total_nominal=0;

	  tree_nominal->SetBranchAddress("eventNumber",&eventNumber_nominal,&branch_eventNumber_nominal);
	  tree_nominal->SetBranchAddress("mcID",&mcID_nominal,&branch_mcID_nominal);
	  tree_nominal->SetBranchAddress("weight_total",&weight_total_nominal,&branch_weight_total_nominal);
	  
	  tree_nominal->SetBranchStatus("*",1);
	  //----------
	  int eventNumber_sys;
	  TBranch *branch_eventNumber_sys=0;
	  
	  int mcID_sys;
	  TBranch *branch_mcID_sys=0;
	  
	  double weight_total_sys=0;
	  TBranch *branch_weight_total_sys=0;
	  
	  tree_sys->SetBranchAddress("eventNumber",&eventNumber_sys,&branch_eventNumber_sys);
	  tree_sys->SetBranchAddress("mcID",&mcID_sys,&branch_mcID_sys);
	  tree_sys->SetBranchAddress("weight_total",&weight_total_sys,&branch_weight_total_sys);
	  
	  tree_sys->SetBranchStatus("*",1);

	  int nb_entries_nominal=tree_nominal->GetEntries();
	  int nb_entries_sys=tree_sys->GetEntries();

	  //----------
	  //search for events uncommon, belonging to nominal only

	  double nb_sel_nominal_uncommon=0;
	  double err_nb_sel_nominal_uncommon=0;
	  
	  double nb_sel_nominal_uncommon_unweighted=0;
	  double err_nb_sel_nominal_uncommon_unweighted=0;

	  cout << "summary, for string_name_tree_nominal=" << string_name_tree_nominal << ", string_name_tree_sys=" << string_name_tree_sys << endl;

	  for (int index_tree_nominal=0;index_tree_nominal<nb_entries_nominal;index_tree_nominal++) {
	    
	    //index : works for tree (for chain, need centry)
	    branch_eventNumber_nominal->GetEntry(index_tree_nominal);
	    branch_mcID_nominal->GetEntry(index_tree_nominal); //in order to work also in case of merge of some various processes
	    
	    cout << "index_tree_nominal=" << index_tree_nominal << " / " << nb_entries_nominal << ", search eventNumber_nominal=" << eventNumber_nominal << " in systematic" << endl;
	    
	    int index_tree_sys=0;
	    for (;index_tree_sys<nb_entries_sys;index_tree_sys++) {
	      
	      branch_eventNumber_sys->GetEntry(index_tree_sys);
	      branch_mcID_sys->GetEntry(index_tree_sys);

	      if (eventNumber_sys==eventNumber_nominal && mcID_sys==mcID_nominal) { //found
		break;
	      }
	    }
	    
	    if (index_tree_sys>=nb_entries_sys) { //event uncommon, belonging to nominal only
	      branch_weight_total_nominal->GetEntry(index_tree_nominal); //get the weight nominal
	      
	      nb_sel_nominal_uncommon+=weight_total_nominal;
	      err_nb_sel_nominal_uncommon+=weight_total_nominal*weight_total_nominal;
	      
	      nb_sel_nominal_uncommon_unweighted++;
	    }
	  } //end loop on nominal
	  
	  err_nb_sel_nominal_uncommon=sqrt(err_nb_sel_nominal_uncommon);
	  err_nb_sel_nominal_uncommon_unweighted=sqrt(nb_sel_nominal_uncommon_unweighted);
	  
	  cout << "summary, for string_name_tree_nominal=" << string_name_tree_nominal << ", string_name_tree_sys=" << string_name_tree_sys << endl;
	  cout << "nb_sel_nominal_uncommon=" << nb_sel_nominal_uncommon << endl;
	  cout << "nb_sel_nominal_uncommon_unweighted=" << nb_sel_nominal_uncommon_unweighted << endl;
	} //end loop on up, down
	
      } //end loop on syst
      
    } //end loop on category

  } //end loop on MxAODSyst_directory
  
  return 0;
}
