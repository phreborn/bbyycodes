//root -b
//.x Reweight.C

string string_path="/sps/atlas/e/escalier/ATLAS_HGam/";
string string_rel_path_shape="Outputs_trees_selection_HH_baseline/";

string string_prefix_tree="tree_sel_";

vector<string> vec_string_category={"XGBoost_btag77_withTop_BCal_tightScore_HMass",
				    "XGBoost_btag77_withTop_BCal_looseScore_HMass",
				    "XGBoost_btag77_withTop_BCal_tightScore_LMass",
				    "XGBoost_btag77_withTop_BCal_looseScore_LMass"
};

vector<string> vec_files={
  "tree_h026_mc16a_PowhegH7_HHbbyy_",
  "tree_h026_mc16d_PowhegH7_HHbbyy_",
  "tree_h026_mc16e_PowhegH7_HHbbyy_"
};

vector<string> vec_string_kappa_lambda_destination;

//={"n10p0","n5p0","0p0","5p0","10p0"};
//vector<string> vec_string_kappa_lambda_destination={"n94p3"};

string string_bin_size="10";

//prototypes
vector<string> CreateList_HH_non_resonant_kappa_lambda();
double Return_numerical_target_kappa(string string_target_kappa);
string Return_string_target_kappa(double numerical_target_kappa);
double ReturnCrossSection(double kappa_lambda);

//###################################################################################################
int Reweight()
{
  
  /*
  cout << "Return_string_target_kappa(9.99999999999999467093)=" << endl;
  cout << Return_string_target_kappa(9.99999999999999467093) << endl;
  exit(1);
  */  
  
  /*
    exploring kappa_lambda=-0.2
    add the string
    exploring kappa_lambda=-2.05391e-15
    add the string
    exploring kappa_lambda=0.2
  */

  vec_string_kappa_lambda_destination=CreateList_HH_non_resonant_kappa_lambda();
  
  for (int index_kappa_lambda_destination=0;index_kappa_lambda_destination<vec_string_kappa_lambda_destination.size();index_kappa_lambda_destination++) {
    string string_kappa_lambda_destination=vec_string_kappa_lambda_destination[index_kappa_lambda_destination];
    
    //    cout << "==================================================================" << endl;
    cout << "string_kappa_lambda_destination=" << string_kappa_lambda_destination << endl;
  }


  //cout << "Return_string_target_kappa(35.4)=" << Return_string_target_kappa(35.4) << endl;
  //cout << "Return_string_target_kappa(-9.2)=" << Return_string_target_kappa(-9.2) << endl;
  //  cout << "Return_string_target_kappa(-94.3)=" << Return_string_target_kappa(-94.3) << endl;

  for (int index_file=0;index_file<vec_files.size();index_file++) {
    //----------------------------------------------------------------------------------------------
    cout << "==================================================================" << endl;
    cout << "index_file=" << index_file << " / " << vec_files.size() << endl;
    
    string string_file=vec_files[index_file];
    string_file+="cHHH01d0_nominal.root";

    cout << "string_path+string_rel_path_shape+string_file=" << string_path+string_rel_path_shape+string_file << endl;

    TFile *f_source=TFile::Open((string_path+string_rel_path_shape+string_file).c_str());
    f_source->cd();

    TList *list=f_source->GetListOfKeys();
    
    int nb_keys=list->GetEntries();
    
    //sure before the categories
    for (int index_kappa_lambda_destination=0;index_kappa_lambda_destination<vec_string_kappa_lambda_destination.size();index_kappa_lambda_destination++) {

      string string_kappa_lambda_destination=vec_string_kappa_lambda_destination[index_kappa_lambda_destination];
      
      cout << "==================================================================" << endl;
      cout << "string_kappa_lambda_destination=" << string_kappa_lambda_destination << endl;

      TString m_reweightFile = "./source/klambdareweighttool/data/weight-mHH-from-cHHHp01d0-to-cHHHpx_"+string_bin_size+"GeV_Jul28.root";
      
      TFile *inFile=new TFile(m_reweightFile,"READ");
      
      string string_target_kappa=vec_string_kappa_lambda_destination[index_kappa_lambda_destination];
      
      //float numerical_target_kappa=0;
      double numerical_target_kappa=0;

      int nb_characters_string_target_kappa=string_target_kappa.size();
      
      numerical_target_kappa=Return_numerical_target_kappa(string_target_kappa);

      cout << "string_target_kappa=" << string_target_kappa << ", numerical_target_kappa=" << numerical_target_kappa << endl;

      TString target="reweight_mHH_1p0_to_"+string_target_kappa;

      inFile->ls();
      
      cout << "target=" << target << endl;

      TH1 *mhh_hist=(TH1 *)inFile->Get(target);
      cout << "mhh_hist=" << mhh_hist << endl;


      vector<float> m_mHHUpperBinEdge;
      vector<float> m_kFactor;
      vector<float> m_kFactorErr;
      
      for(int iBin =0; iBin < mhh_hist->GetNbinsX()+1; ++iBin){
	m_mHHUpperBinEdge.push_back(mhh_hist->GetBinLowEdge(iBin)+mhh_hist->GetBinWidth(iBin));
	m_kFactor        .push_back(mhh_hist->GetBinContent(iBin)        );
	m_kFactorErr     .push_back(mhh_hist->GetBinError  (iBin));
      }
      
      //
      // Overflow
      //
      m_mHHUpperBinEdge.push_back(1e9);
      m_kFactor        .push_back(mhh_hist->GetBinContent(mhh_hist->GetNbinsX()+1));
      m_kFactorErr     .push_back(mhh_hist->GetBinError(mhh_hist->GetNbinsX()+1));
      
      unsigned int m_nMHHBins = m_mHHUpperBinEdge.size();
      
      inFile->Close(); 
      
      string string_file_target_kappa=string_path+string_rel_path_shape+vec_files[index_file]+"reweight_mHH_1p0_to_"+string_kappa_lambda_destination+"_nominal.root";
      
      cout << "string_file_target_kappa=" << string_file_target_kappa << endl;
      
      TFile *f_destination=TFile::Open(string_file_target_kappa.c_str(),"recreate");
      f_destination->ls();
      
      cout << "nb_keys=" << nb_keys << endl;
      
      for (int index_key=0;index_key<nb_keys;index_key++) {
	//	cout << "index_key=" << index_key << endl;
	
	TKey *key=(TKey *)list->At(index_key);
	
	if (strcmp(key->GetClassName(),"TTree"))
	  continue;
	
	//this is a TTree at this place
	
	char *name_tree=(char *)key->GetName();
	
	string string_name_tree=name_tree;

	cout << "name_tree=" << name_tree << endl;

	int index_category=0;
	
	for (;index_category<vec_string_category.size();index_category++) {
	  if (string_name_tree.find(vec_string_category[index_category])!=string::npos)
	    break;
	}
	
	if (index_category>=vec_string_category.size()) //not find a relevant category to reweight
	  continue;
	
	TTree *oldtree=(TTree *)f_source->Get(name_tree);
	
	cout << "oldtree->GetName()=" << oldtree->GetName() << endl;
	
	//works
	double weight_event=0;
	double weight_lumi=0;
	double weight_total=0;

	double truth_m_hh=-999;
	oldtree->SetBranchAddress("truth_m_hh",&truth_m_hh);
	
	oldtree->SetBranchAddress("weight_event",&weight_event);
	oldtree->SetBranchAddress("weight_lumi",&weight_lumi);
	oldtree->SetBranchAddress("weight_total",&weight_total);
	
	oldtree->SetBranchStatus("*",1);
	
	TTree *newtree=oldtree->CloneTree(0);
	
	//to use double ?
	float weight;
	float weight_err;
	
	TBranch *b_kappalambdaweight=newtree->Branch(("kappa_lambda_weight_"+string_bin_size+"GeV_"+string_target_kappa).c_str(),&weight,("kappa_lambda_weight_"+string_bin_size+"GeV_"+string_target_kappa+"/F").c_str());
	TBranch *b_kappalambdaweight_err=newtree->Branch(("kappa_lambda_weight_err_"+string_bin_size+"GeV_"+string_target_kappa).c_str(),&weight_err,("kappa_lambda_weight_err_"+string_bin_size+"GeV_"+string_target_kappa+"/F").c_str());
	
	int nb_entries=oldtree->GetEntries();
	
	for (int index_entry=0;index_entry<nb_entries;index_entry++) {
	  //for (int index_entry=0;index_entry<5;index_entry++) {

	  //cout << "index_entry=" << index_entry << endl;

	  oldtree->GetEntry(index_entry);
	  
	  bool done=false;
	  
	  for (unsigned int iBin=0;iBin<m_nMHHBins;++iBin) {
	    //	    if (mhh_in_GeV < m_mHHUpperBinEdge.at(iBin) && !done){
	    if (truth_m_hh<m_mHHUpperBinEdge.at(iBin) && !done){
	      weight= m_kFactor.at(iBin);
	      weight_err = m_kFactorErr.at(iBin);
	      done = true;
            }
	  }
	  
	  if (!done) {
            weight=m_kFactor.back();
            weight_err=m_kFactorErr.back();
	  }

	  float CrossSection_kappa_lambda=ReturnCrossSection(numerical_target_kappa);
	  float CrossSection_SM=ReturnCrossSection(1);

	  //cout << "CrossSection_kappa_lambda=" << CrossSection_kappa_lambda << endl;
	  //cout << "CrossSection_SM=" << CrossSection_SM << endl;
	  
	  //shape part
	  weight_event*=weight;
	  weight_total*=weight;

	  //cross-section part
	  weight_lumi*=CrossSection_kappa_lambda/CrossSection_SM;
	  weight_event*=CrossSection_kappa_lambda/CrossSection_SM;
	  weight_total*=CrossSection_kappa_lambda/CrossSection_SM;
	  
	  //	  b_kappalambdaweight->Fill();
	  
	  newtree->Fill(); //this fills everything, including the new variables ?
	
	} //end loop on entries
	
	//      cout << "finished reading tree" << endl;
	//OK      f_destination->cd();
	
	//      cout << "writing tree" << endl;
	//      newtree->Write();
	
	//      vec_string_branch_weights.clear();
	
	//      return 0;
      } //end list of keys
      
      f_destination->Write();
      f_destination->Close();
      
      //    cout << "closing f_destination" << endl;
    } //end loop on target_kappa
    
  } //end list of files

  return 0;
}
//###################################################################################################
double ReturnCrossSection(double kappa_lambda)
{
  double cross_section;
  
  //formula at mh=125 GeV
  cross_section=70.3874-50.4111*kappa_lambda+11.0595*pow(kappa_lambda,2); //in fb
  
  cross_section*=31.02/31.05;

  cross_section*=2*0.5809*0.00227;

  return cross_section;
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
  
  cout << "index_point=" << index_point << endl;
  
  int coefficient_power=index_point-index_first_position-1;
  
  cout << "index_first_position=" << index_first_position << ", index_point=" << index_point << endl;
  cout << "coefficient_power=" << coefficient_power << endl;
  
  double numerical_target_kappa=0;
  
  for (index_character=index_first_position;index_character<string_target_kappa.size();index_character++) {

    char character[1];
    character[0]=string_target_kappa[index_character];
    cout << "in loop, coefficient_power=" << coefficient_power << endl;
    cout << "before treatment, numerical_target_kappa=" << numerical_target_kappa << endl;
    
    numerical_target_kappa+=atoi(character)*pow(10,coefficient_power);
    cout << "after treatment of character index " << index_first_position << ", which is " << string_target_kappa[index_character] << ", numerical_target_kappa=" << numerical_target_kappa << endl;
    
    if (string_target_kappa[index_character]!='p')
      coefficient_power--;
  }
  
  numerical_target_kappa*=sign;

  return numerical_target_kappa;
}
//###################################################################################################
vector<string> CreateList_HH_non_resonant_kappa_lambda()
{
  double epsilon=1e-5;
  //avoid 1

  vector<string> vector_string_kappa_lambda;

  //better to use double to prevent some clumsy changes of digits

  double step_kappa_lambda=0.2; //this is what there is in the official kappa lambda reweighting
  
  double kappa_lambda=-10;
  
  for (;kappa_lambda<=10;kappa_lambda+=step_kappa_lambda) {
    
    printf("exploring kappa_lambda=%20.20f\n",kappa_lambda);
    
    //    if (kappa_lambda-!=1) {
    if (fabs(kappa_lambda-1.)>epsilon) {
      cout << "add the string" << endl;
      vector_string_kappa_lambda.push_back(Return_string_target_kappa(kappa_lambda));
    }
  }
  
  return vector_string_kappa_lambda;
}
//###################################################################################################
string Return_string_target_kappa(double numerical_target_kappa)
{
  bool DEBUG=0;

  if (DEBUG) {
    cout << "====================================" << endl;
    printf("Decode kappa lambda=%20.20f\n",numerical_target_kappa);
  }
  
  double epsilon=1e-5; //to avoid rounding due to representation in power of 2

  string string_target_kappa;
  
  char buffer[1];
  
  if (numerical_target_kappa<0) {
    string_target_kappa+='n';

    numerical_target_kappa=fabs(numerical_target_kappa);
    //change sign to prevent having the sign everywhere
  }
  
  //at this stage, we have absolute number

  if (DEBUG) {
    cout << endl;
    cout << "phase 1" << endl;
    printf("numerical_target_kappa=%20.20f\n",numerical_target_kappa);

    cout << "test >=10" << endl;
  }
  
  if (numerical_target_kappa/10.+epsilon>=1) {
    sprintf(buffer,"%d",(int)(numerical_target_kappa/10.+epsilon));
    
    if (DEBUG) {
      cout << "yes" << endl;
      cout << "buffer=" << buffer << endl;
    }
    string_target_kappa+=buffer;
    numerical_target_kappa-=(int)((numerical_target_kappa/10.+epsilon))*10;
    numerical_target_kappa=fabs(numerical_target_kappa);
  }
  
  if (DEBUG) {
    cout << endl;
    
    printf("numerical_target_kappa=%20.20f\n",numerical_target_kappa);
    cout << "test >=1" << endl;
  }
  
  if (numerical_target_kappa+epsilon>=1) {

    sprintf(buffer,"%d",(int)(numerical_target_kappa+epsilon));
    
    if (DEBUG) {
      cout << "yes" << endl;
      cout << "resulting buffer=" << buffer << endl;
    }
    
    string_target_kappa+=buffer;
    numerical_target_kappa-=((int)(numerical_target_kappa+epsilon));
    numerical_target_kappa=fabs(numerical_target_kappa);
  }
  else
    string_target_kappa+='0';  

  string_target_kappa+='p';
  
  if (DEBUG) {
    cout << "phase 3" << endl;
    printf("numerical_target_kappa=%20.20f\n",numerical_target_kappa);
    
    cout << "test>=0.1" << endl;
  }

  if (numerical_target_kappa+epsilon>=0.1) {
    
    sprintf(buffer,"%01d",(int)(numerical_target_kappa*10.+epsilon));
    
    if (DEBUG) {
      cout << "yes" << endl;
      
      cout << "buffer=" << buffer << endl;
    }
    
    string_target_kappa+=buffer;
  }
  else
    string_target_kappa+='0';
  
  //keep that for sure
  if (string_target_kappa=="n0p0")
    string_target_kappa="0p0";
  
  if (DEBUG) {
    cout << "this gives : " << string_target_kappa << endl;
    cout << "====================================" << endl;
  }
  
  return string_target_kappa;
}
//###################################################################################################




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


	/*

	//      int nb_branches_weight=vec_string_branch_weights.size();

	  for (index_branch_weight=0;index_branch_weight<nb_branches_weight;index_branch_weight++) {
		
  cout << "index_branch_weight=" << index_branch_weight << ", vec_string_branch_weights[index_branch_weight]=" << vec_string_branch_weights[index_branch_weight] << ", so far, vec_value_branch_weights[" << index_branch_weight << "]=" << vec_value_branch_weights[index_branch_weight] << endl;
	  
	  cout << "multiplication by 10" << endl;
	  vec_value_branch_weights[index_branch_weight]*=10;

	  
	} //end list of branch of weights
	  */
	





/*
	  | HGamEventInfoAuxDyn.crossSectionBRfilterEff/F                    *
	  crossSectionBR_0p0 : crossSectionBR_0p0/F                          *
	  crossSectionBR_2p0 : crossSectionBR_2p0/F                          *
	  crossSectionBR_3p0 : crossSectionBR_3p0/F                          *
	  crossSectionBR_4p0 : crossSectionBR_4p0/F                          *
	  crossSectionBR_6p0 : crossSectionBR_6p0/F                          *
	  crossSectionBR_7p0 : crossSectionBR_7p0/F                          *
	  crossSectionBR_8p0 : crossSectionBR_8p0/F                          *
	  crossSectionBR_9p0 : crossSectionBR_9p0/F                          *
	  crossSectionBR_10p0 : crossSectionBR_10p0/F                        *
	  crossSectionBR_n1p0 : crossSectionBR_n1p0/F                        *
	  crossSectionBR_n2p0 : crossSectionBR_n2p0/F                        *
	  crossSectionBR_n3p0 : crossSectionBR_n3p0/F                        *
	  crossSectionBR_n4p0 : crossSectionBR_n4p0/F                        *
	  crossSectionBR_n5p0 : crossSectionBR_n5p0/F                        *
	  crossSectionBR_n6p0 : crossSectionBR_n6p0/F                        *
	  crossSectionBR_n7p0 : crossSectionBR_n7p0/F                        *
	  crossSectionBR_n8p0 : crossSectionBR_n8p0/F                        *
	  crossSectionBR_n9p0 : crossSectionBR_n9p0/F                        *
	  crossSectionBR_n10p0 : crossSectionBR_n10p0/F                      *
*/

