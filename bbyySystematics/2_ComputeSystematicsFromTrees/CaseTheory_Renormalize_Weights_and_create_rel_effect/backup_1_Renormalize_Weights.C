//root -b
//.x Renormalize_Weights.C

string string_path="/sps/atlas/e/escalier/ATLAS_HGam/";
string string_rel_path_shape="Outputs_syst_shape_Run2/";

//shit string string_rel_path_shape="Outputs_syst_h025_shape_Run2/";


string string_prefix_tree="tree_sel_";
//shitvector<string> vec_string_category={"_Inclusive","_baseline"};

vector<string> vec_string_category;

vector<string> vec_files={
  "tree_h025_mc16a_nominal_PowhegH7_HHbbyy_cHHH01d0.root",
  "tree_h025_mc16d_nominal_PowhegH7_HHbbyy_cHHH01d0.root",
  "tree_h025_mc16e_nominal_PowhegH7_HHbbyy_cHHH01d0.root",
  "tree_h025_mc16a_nominal_PowhegH7_HHbbyy_cHHH10d0.root",
  "tree_h025_mc16d_nominal_PowhegH7_HHbbyy_cHHH10d0.root",
  "tree_h025_mc16e_nominal_PowhegH7_HHbbyy_cHHH10d0.root",
  "tree_h025_mc16a_nominal_MGH7_hh_bbyy_vbf_l1cvv1cv1.root",
  "tree_h025_mc16d_nominal_MGH7_hh_bbyy_vbf_l1cvv1cv1.root",
  "tree_h025_mc16e_nominal_MGH7_hh_bbyy_vbf_l1cvv1cv1.root",

  "tree_h025_mc16a_PhotonSys_PowhegPy8_NNLOPS_ggH125.root",
  "tree_h025_mc16d_PhotonSys_PowhegPy8_NNLOPS_ggH125.root",
  "tree_h025_mc16e_PhotonSys_PowhegPy8_NNLOPS_ggH125.root",
  "tree_h025_mc16a_PhotonSys_PowhegPy8_ZH125J.root",
  "tree_h025_mc16d_PhotonSys_PowhegPy8_ZH125J.root",
  "tree_h025_mc16e_PhotonSys_PowhegPy8_ZH125J.root",
  "tree_h025_mc16a_PhotonSys_PowhegPy8_ggZH125.root",
  "tree_h025_mc16d_PhotonSys_PowhegPy8_ggZH125.root",
  "tree_h025_mc16e_PhotonSys_PowhegPy8_ggZH125.root",
  "tree_h025_mc16a_PhotonSys_PowhegPy8_ttH125_fixweight.root",
  "tree_h025_mc16d_PhotonSys_PowhegPy8_ttH125_fixweight.root",
  "tree_h025_mc16e_PhotonSys_PowhegPy8_ttH125_fixweight.root"
  
};

//for potential categories
vector<int> vec_mX_th_systematics={260,280,300,325,350,400,450,500,550,600,700,800,900,1000};

//=====================================================================================================================================================
int _1_Renormalize_Weights()
{
  for (int index_file=0;index_file<vec_files.size();index_file++) {
    cout << "==================================================================" << endl;
    
    string string_file=vec_files[index_file];
    
    //----------------------------------------------------------------------------------------------
    //creation of categories

    vec_string_category.clear();
    
    //HH non resonant baseline
    if (string_file.find("_X")==string::npos) { //sample is not a resonant sample, so either a HH non resonant or a single Higgs
      
      //so consider to include the non resonant categories
      
      vec_string_category.push_back("Inclusive_HH_NonResonant");
      vec_string_category.push_back("XGBoost_btag77_withTop_BCal_tightScore_HMass");
      vec_string_category.push_back("XGBoost_btag77_withTop_BCal_looseScore_HMass");
      vec_string_category.push_back("XGBoost_btag77_withTop_BCal_tightScore_LMass");
      vec_string_category.push_back("XGBoost_btag77_withTop_BCal_looseScore_LMass");
      vec_string_category.push_back("VBF_btag77_withTop_BCal");
    }
    
    //HH resonant baseline
    
    if (string_file.find("_HHH")==string::npos
	&&
	string_file.find("bbyy_vbf_")==string::npos
	) { //sample is not a non-resonant sample, so either a HH resonant or a single Higgs
      
      //so consider to include the resonant categories
    
      bool is_single_Higgs=0;
      if (string_file.find("ggH125")!=string::npos
	  ||
	  string_file.find("ZH125")!=string::npos
	  ||
	  string_file.find("ttH125")!=string::npos
	  )
	is_single_Higgs=1;
      
      for (unsigned int index_mX=0;index_mX<vec_mX_th_systematics.size();index_mX++) {
	
	string string_resonance="X"+to_string(vec_mX_th_systematics[index_mX]);
	cout << "string_resonance=" << string_resonance << endl;
	
	cout << "string_file=" << string_file << endl;

	if (
	    is_single_Higgs //is not a resonant sample
	    ||
	    (string_file.find("MGH7_X")!=string::npos && string_file.find(string_resonance)!=string::npos) //is the resonant sample of the corresponding mX
	    ) {
	  vec_string_category.push_back("Resonant_mX"+to_string(vec_mX_th_systematics[index_mX]));
	  cout << "adding category Resonant_mX"+to_string(vec_mX_th_systematics[index_mX]) << endl;
	}

      } //end loop on mX
    } //end case resonant

    for (int index_category=0;index_category<vec_string_category.size();index_category++)
      cout << "index_category=" << index_category << ", " << vec_string_category[index_category] << endl;
   

    //----------------------------------------------------------------------------------------------
    cout << "index_file=" << index_file << " / " << vec_files.size() << endl;
    TFile *f_source=TFile::Open((string_path+string_rel_path_shape+"trees/subjobs/to_correct_weights/Theory/"+vec_files[index_file]).c_str());
    
    f_source->cd();

    TFile *f_destination=TFile::Open((string_path+string_rel_path_shape+"trees/Theory/"+vec_files[index_file]).c_str(),"recreate");
    
    f_destination->ls();

    TH1D *hist_init_nominal=(TH1D *)f_source->Get("hist_nominal");
    double SumOfWeight_init=hist_init_nominal->GetSumOfWeights();
    //    cout << "SumOfWeight_init=" << SumOfWeight_init << endl;
    
    TList *list=f_source->GetListOfKeys();

    int nb_keys=list->GetEntries();
    
    for (int index_key=0;index_key<nb_keys;index_key++) {
      //cout << "index_key=" << index_key << endl;
      
      TKey *key=(TKey *)list->At(index_key);
      
      if (strcmp(key->GetClassName(),"TTree"))
	continue;
      
      //this is a TTree at this place
      
      char *name_tree=(char *)key->GetName();
      
      TTree *oldtree=(TTree *)f_source->Get(name_tree);

      //      cout << "oldtree->GetName()=" << oldtree->GetName() << endl;
      
      //identify the variation : remove word Inclusive or other word of category
      
      int size_string_prefix_tree=string_prefix_tree.size();

      string string_tree=name_tree;

      size_t position_string_category=0;
      
      int index_category=0;

      for (;index_category<vec_string_category.size();index_category++) {
	
	position_string_category=string_tree.find(vec_string_category[index_category]);
	
	if (position_string_category!=string::npos)
	  break;
      }

      if (index_category>=vec_string_category.size()) {
	cout << "not found category " << vec_string_category[index_category] << ", halt program" << endl;
	exit(1);
      }
      
      position_string_category--; //take into account the "_" before the category

      cout << "string_tree=" << string_tree << endl;


      cout << "position_string_category=" << position_string_category << endl;
      cout << "size_string_prefix_tree=" << size_string_prefix_tree << endl;

      string string_variation=string_tree.substr(size_string_prefix_tree,position_string_category-size_string_prefix_tree);
      
      cout << "dealing with string_variation=" << string_variation << ", tree=" << name_tree << endl;

      TH1D *hist_init_variation;
      double SumOfWeight_init_variation;

      if (string_variation!="nominal") {
	hist_init_variation=(TH1D *)f_source->Get((string("hist_")+string_variation).c_str());
	SumOfWeight_init_variation=hist_init_variation->GetSumOfWeights();
	
	//	cout << "SumOfWeight_init_variation=" << SumOfWeight_init_variation << endl;
      }

      //      oldtree->Print();

      //      cout << "oldtree->GetEntries()=" << oldtree->GetEntries() << endl;
      
      //works
      double weight_event=0;
      double weight_lumi=0;
      double weight_total=0;
      
      oldtree->SetBranchAddress("weight_event",&weight_event);
      oldtree->SetBranchAddress("weight_lumi",&weight_lumi);
      oldtree->SetBranchAddress("weight_total",&weight_total);

      /*generaliszation, does not work, for unknown reason
      TObjArray *list_branches=oldtree->GetListOfBranches();
      
      //identify the branch that are weights
      int nb_branches=list_branches->GetEntries();
      
      //identify list of branches for weights
      vector<string> vec_string_branch_weights;
      vector<double> vec_value_branch_weights;
      
//if to be use, to clear

      int index_branch_weight=0;
      
      for (int index_branch=0;index_branch<nb_branches;index_branch++) {
	TBranch *branch=(TBranch *)list_branches->At(index_branch);
	//	cout << "branch->GetName()=" << branch->GetName() << endl;
	
	if (string(branch->GetName()).find("weight")!=string::npos) {
	  vec_string_branch_weights.push_back(branch->GetName());
	  
	  vec_value_branch_weights.push_back(0); //put dumb value in order to reserve the variable
	  
	  oldtree->SetBranchAddress(branch->GetName(),&(vec_value_branch_weights[index_branch_weight]));
	  
	  index_branch_weight++;
	}
      } //end search for branch weights
      */      

      oldtree->SetBranchStatus("*",1);
 
      //      int nb_branches_weight=vec_string_branch_weights.size();

      TTree *newtree=oldtree->CloneTree(0);
      
      int nb_entries=oldtree->GetEntries();
      
      for (int index_entry=0;index_entry<nb_entries;index_entry++) {
	//for (int index_entry=0;index_entry<5;index_entry++) {

	//cout << "index_entry=" << index_entry << endl;
	
	oldtree->GetEntry(index_entry);
	
	if (string_variation!="nominal") { // change weights only if not nominal
	  //	  cout << "string_variation=" << string_variation << endl;
	  //	  cout << "(SumOfWeight_init/SumOfWeight_init_variation)=" << (SumOfWeight_init/SumOfWeight_init_variation) << endl;
	  
	  weight_event*=(SumOfWeight_init/SumOfWeight_init_variation);
	  weight_lumi*=(SumOfWeight_init/SumOfWeight_init_variation);
	  weight_total*=(SumOfWeight_init/SumOfWeight_init_variation);
	}

	/*
	  for (index_branch_weight=0;index_branch_weight<nb_branches_weight;index_branch_weight++) {
		
  cout << "index_branch_weight=" << index_branch_weight << ", vec_string_branch_weights[index_branch_weight]=" << vec_string_branch_weights[index_branch_weight] << ", so far, vec_value_branch_weights[" << index_branch_weight << "]=" << vec_value_branch_weights[index_branch_weight] << endl;
	  
	  cout << "multiplication by 10" << endl;
	  vec_value_branch_weights[index_branch_weight]*=10;

	  
	} //end list of branch of weights
	  */
	
	newtree->Fill();

      } //end loop on entries
      
      //      cout << "finished reading tree" << endl;
      f_destination->cd();
      
      //      cout << "writing tree" << endl;
      newtree->Write();
      
      /*
      cout << "closing f_destination" << endl;
      //      f_destination->Write();
      f_destination->Close();
      
      cout << "END PROGRAM" << endl;
      
      exit(1);
      */

      //      vec_string_branch_weights.clear();
      
      //      return 0;
    } //end list of keys
   
    cout << "closing f_destination" << endl;
    //      f_destination->Write();
    f_destination->Close();
    
  } //end list of files

    return 0;
}
//=====================================================================================================================================================
