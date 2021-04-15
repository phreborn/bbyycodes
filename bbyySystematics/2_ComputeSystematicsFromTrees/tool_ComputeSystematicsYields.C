#include "includes.h"
#include "global.h"

#include "tool_helper.C"

#include "tool_syst_yield.h"

//why is nb_toys_done equal to 0 ?

//1473 lines
//it would be too complex to separate the bootstrap nominal already done, because storage in the directory of the systematic, so different...

//could be accelated a bit by computing the yield nominal only once, but then it would be very difficult due to the various bootstrap : too complex

//to remove <nb_toys

//------------------------------
//gain : 60 %
bool do_yield_construct_bootstrap_nominal_once=1;
bool do_yield_get_tree_nominal_once=1;
bool do_yield_open_file_syst_once=1;
//------------------------------
string string_yield_input_file_systematic="NotInitialized";
string string_yield_previous_input_file_systematic="NotInitialized";

//maybe just provide the string_systematic ?

//to provide index category ?
//#######################################################################################################################################################################################################

void get_yield_from_file(string string_category,string local_string_sample,string string_systematic)
{
  //  cout << "get_yield_from_file " << string_category << ", " << string_systematic << endl;
  //  file_syst->ls();
  
  //-------------------------------------
  //information for identifying wether the treatment of systematic is fully correlated (case of systematic w/ SF) or partially correlated

  TH1D *hist_nb_sel_nominal_unweighted=NULL;
  TH1D *hist_nb_sel_sys_unweighted=NULL;
  TH1D *hist_nb_sel_uncommon_part_nominal_unweighted=NULL;
  TH1D *hist_nb_sel_uncommon_part_sys_unweighted=NULL;
  TH1D *hist_nb_sel_nominal=NULL;
  TH1D *hist_nb_sel_sys=NULL;
  TH1D *hist_nb_sel_uncommon_part_nominal=NULL;
  TH1D *hist_nb_sel_common_part_nominal=NULL;
  TH1D *hist_nb_sel_uncommon_part_sys=NULL;
  
  hist_nb_sel_nominal=(TH1D *)file_syst->Get((string("hist_nb_sel_nominal")+string("_")+string_category).c_str());
  
  //    cout << "search for " << (string("hist_nb_sel_nominal")+string("_")+string_category) << endl;
  //    cout << "hist_nb_sel_nominal=" << hist_nb_sel_nominal << endl;
  
  //    cout << "search for " << (string("hist_nb_sel_sys_")+string_systematic+suffix_asymmetry_systematic+string("_")+string_category) << endl;    
  hist_nb_sel_sys=(TH1D *)file_syst->Get((string("hist_nb_sel_sys_")+string_systematic+suffix_asymmetry_systematic+string("_")+string_category).c_str());
  
  //    cout << "hist_nb_sel_sys=" << hist_nb_sel_sys << endl;
  
  if (Return_object_given_systematic(string_systematic)!="theory") {
    hist_nb_sel_nominal_unweighted=(TH1D *)file_syst->Get((string("hist_nb_sel_nominal")+string("_")+string_category+string("_unweighted")).c_str());
    
    //      cout << "hist_nb_sel_nominal_unweighted=" << hist_nb_sel_nominal_unweighted << endl;
    
    hist_nb_sel_sys_unweighted=(TH1D *)file_syst->Get((string("hist_nb_sel_sys_")+string_systematic+suffix_asymmetry_systematic+string("_")+string_category+string("_unweighted")).c_str());
    
    
    //      cout << "hist_nb_sel_sys_unweighted=" << hist_nb_sel_sys_unweighted << endl;
    
    hist_nb_sel_uncommon_part_nominal_unweighted=(TH1D *)file_syst->Get((string("hist_nb_sel_uncommon_part_nominal_")+string_systematic+suffix_asymmetry_systematic+string("_")+string_category+string("_unweighted")).c_str());
    
    //      cout << "hist_nb_sel_uncommon_part_nominal_unweighted=" << hist_nb_sel_uncommon_part_nominal_unweighted << endl;
    
    //      cout << (string("hist_nb_sel_uncommon_part_sys_")+string_systematic+suffix_asymmetry_systematic+string("_")+string_category+string("_unweighted")).c_str() << endl;      
    hist_nb_sel_uncommon_part_sys_unweighted=(TH1D *)file_syst->Get((string("hist_nb_sel_uncommon_part_sys_")+string_systematic+suffix_asymmetry_systematic+string("_")+string_category+string("_unweighted")).c_str());
    
    //      cout << "hist_nb_sel_uncommon_part_sys_unweighted=" << hist_nb_sel_uncommon_part_sys_unweighted << endl;
    
    hist_nb_sel_uncommon_part_nominal=(TH1D *)file_syst->Get((string("hist_nb_sel_uncommon_part_nominal_")+string_systematic+suffix_asymmetry_systematic+string("_")+string_category).c_str());
    //      cout << "hist_nb_sel_uncommon_part_nominal=" << hist_nb_sel_uncommon_part_nominal << endl;
    
    hist_nb_sel_common_part_nominal=(TH1D *)file_syst->Get((string("hist_nb_sel_common_part_nominal_")+string_systematic+suffix_asymmetry_systematic+string("_")+string_category).c_str());
    //      cout << "hist_nb_sel_common_part_nominal=" << hist_nb_sel_common_part_nominal << endl;
    
    //      cout << "now, search for " << (string("hist_nb_sel_uncommon_part_sys_")+string_systematic+suffix_asymmetry_systematic+string("_")+string_category).c_str() << endl;
    hist_nb_sel_uncommon_part_sys=(TH1D *)file_syst->Get((string("hist_nb_sel_uncommon_part_sys_")+string_systematic+suffix_asymmetry_systematic+string("_")+string_category).c_str());
    //      cout << "hist_nb_sel_uncommon_part_sys=" << hist_nb_sel_uncommon_part_sys << endl;
  }
  
  if (
      (
       hist_nb_sel_nominal==0
       ||
       hist_nb_sel_sys==0
       ||
       hist_nb_sel_nominal==0
       ||
       hist_nb_sel_sys==0
       )
      ||
      (Return_object_given_systematic(string_systematic)!="theory"
       &&
       (
	hist_nb_sel_uncommon_part_nominal==0
	||
	hist_nb_sel_common_part_nominal==0
	||
	hist_nb_sel_uncommon_part_sys==0
	||
	hist_nb_sel_uncommon_part_nominal==0
	||
	hist_nb_sel_common_part_nominal==0
	||
	hist_nb_sel_uncommon_part_sys==0
	||
	hist_nb_sel_nominal_unweighted==0
	||
	hist_nb_sel_sys_unweighted==0
	||
	hist_nb_sel_uncommon_part_nominal_unweighted==0
	||
	hist_nb_sel_uncommon_part_sys_unweighted==0
	)
       )
      ) {
    if (vec_nature_syst_components_sym_asym[index_sym_asym]=="")
      file_or_tree_exists_sym=0;
    else if (vec_nature_syst_components_sym_asym[index_sym_asym]=="__1up")
      file_or_tree_exists_up=0;
    else if (vec_nature_syst_components_sym_asym[index_sym_asym]=="__1down")
      file_or_tree_exists_down=0;
  }
  else {
    
    //=============================================
    //      cout << "hist_nb_sel_nominal=" << hist_nb_sel_nominal << endl;
    nb_sel_nominal=hist_nb_sel_nominal->GetBinContent(1);
    //      cout << "get_yield_from_file, phase 3 " << string_category << ", " << string_systematic << endl;
    
    //      cout << "hist_nb_sel_sys=" << hist_nb_sel_sys << endl;
    nb_sel_sys=hist_nb_sel_sys->GetBinContent(1);
    
    //      cout << "get_yield_from_file, phase 4 " << string_category << ", " << string_systematic << endl;
    err_nb_sel_nominal=hist_nb_sel_nominal->GetBinError(1);
    
    //      cout << "get_yield_from_file, phase 5 " << string_category << ", " << string_systematic << endl;
      //      cout << "hist_nb_sel_sys=" << hist_nb_sel_sys << endl;
      err_nb_sel_sys=hist_nb_sel_sys->GetBinError(1);
      
      //      cout << "get_yield_from_file, phase 3 " << string_category << ", " << string_systematic << endl;
      
      if (Return_object_given_systematic(string_systematic)!="theory") {
	nb_sel_uncommon_part_nominal=hist_nb_sel_uncommon_part_nominal->GetBinContent(1);
	nb_sel_common_part_nominal=hist_nb_sel_common_part_nominal->GetBinContent(1);
	nb_sel_uncommon_part_sys=hist_nb_sel_uncommon_part_sys->GetBinContent(1);
	
	err_nb_sel_uncommon_part_nominal=hist_nb_sel_uncommon_part_nominal->GetBinError(1);
	err_nb_sel_common_part_nominal=hist_nb_sel_common_part_nominal->GetBinError(1);
	err_nb_sel_uncommon_part_sys=hist_nb_sel_uncommon_part_sys->GetBinError(1);
	//-----
	//information for identifying wether the treatment of systematic is fully correlated (case of systematic w/ SF) or partially correlated
	nb_sel_nominal_unweighted=hist_nb_sel_nominal_unweighted->GetBinContent(1);
	
	nb_sel_sys_unweighted=hist_nb_sel_sys_unweighted->GetBinContent(1);
	
	nb_sel_uncommon_part_nominal_unweighted=hist_nb_sel_uncommon_part_nominal_unweighted->GetBinContent(1);
	
	nb_sel_uncommon_part_sys_unweighted=hist_nb_sel_uncommon_part_sys_unweighted->GetBinContent(1);
      }
  } //end case there are events
    

  //=============================================
  //-----
  //identify model of correlation, for error computation
  
  //cout << "nb_sel_uncommon_part_nominal_unweighted=" << nb_sel_uncommon_part_nominal_unweighted << ", nb_sel_uncommon_part_sys_unweighted=" << nb_sel_uncommon_part_sys_unweighted << ", nb_sel_sys=" << nb_sel_sys << ", nb_sel_nominal=" << nb_sel_nominal << endl;
  
  if (Return_object_given_systematic(string_systematic)=="theory")
    correlation_full1_partial2=1; // by construction, since systematics in the form of weight
  else if (nb_sel_uncommon_part_nominal_unweighted==0 && nb_sel_uncommon_part_sys_unweighted==0 && nb_sel_nominal_unweighted==nb_sel_sys_unweighted && fabs((nb_sel_sys-nb_sel_nominal)/nb_sel_nominal)>1.e-4) //same yield unweighted but different yield weighted ; do not put lower than 1.e-4 because rounding effect : some same values have discrepencies of 1.5e-5 because of rounding in the representation
    { //case fully correlated : uncommon unweighted yields are null, unweighted yields are equal and weighted yields have a non-negligeable effect [!= numerical rounding effect]
      cout << string_systematic << ", case fully correlated: " << local_string_sample << ", " << ", " << string_category << ", " << string_systematic << endl;
      correlation_full1_partial2=1;
    }
  else {
    cout << string_systematic << ", case partially correlated: " << local_string_sample << ", " << string_category << ", " << string_systematic << endl;
    
    correlation_full1_partial2=2;
  }
}
//#######################################################################################################################################################################################################
double get_err_rel_effect_yield_partially_correlated(double yield_nominal,
						     double yield_common_part_nominal,
						     double yield_uncommon_part_nominal,
						     double yield_uncommon_part_sys,
						     double err_yield_uncommon_part_nominal,
						     double err_yield_common_part_nominal,
						     double err_yield_uncommon_part_sys)
{
  cout << "get_err_rel_effect_yield_partially_correlated" << endl;
  double local_err_rel_effect_yield=0;
  
  local_err_rel_effect_yield=100.*pow(1./yield_nominal,2)*
    sqrt(
	 (
	  pow(yield_uncommon_part_nominal-yield_uncommon_part_sys,2)*(pow(err_yield_common_part_nominal,2))
	  +
	  pow(yield_common_part_nominal+yield_uncommon_part_sys,2)*(pow(err_yield_uncommon_part_nominal,2))
	  +
	  pow(yield_nominal,2)*pow(err_yield_uncommon_part_sys,2))
	 );
  
  cout << "- - - - - - - - - - - - - -" << endl;
  cout << "get_err_rel_effect_yield_partially_correlated" << endl;
  cout << "yield_nominal=" << yield_nominal << endl;
  cout << "yield_common_part_nominal=" << yield_common_part_nominal << endl;
  cout << "yield_uncommon_part_nominal=" << yield_uncommon_part_nominal << endl;
  cout << "yield_uncommon_part_sys=" << yield_uncommon_part_sys << endl;
  cout << "err_yield_uncommon_part_nominal=" << err_yield_uncommon_part_nominal << endl;
  cout << "err_yield_common_part_nominal=" << err_yield_common_part_nominal << endl;
  cout << "err_yield_uncommon_part_sys=" << err_yield_uncommon_part_sys << endl;
  
  cout << "local_err_rel_effect_yield=" << local_err_rel_effect_yield << endl;
  
  return local_err_rel_effect_yield;
}

//#######################################################################################################################################################################################################
double get_err_rel_effect_yield_fully_correlated(double value_nominal,
						 double value_sys,
						 double err_value_nominal,
						 double err_value_sys)
{
  cout << "get_err_rel_effect_yield_fully_correlated" << endl;
  double local_err_rel_effect=100.*sqrt(
					      (pow(value_sys,2)*pow(err_value_nominal,2)/pow(value_nominal,4))
					      +(pow(err_value_sys,2)/pow(value_nominal,2))
					      -2.*value_sys*err_value_nominal*err_value_sys/pow(value_nominal,3)
					      );
  cout << "- - - - - - - - - - - - - -" << endl;
  cout << "full treatment" << endl;
  cout << "nominal=" << value_nominal << endl;
  cout << "sys=" << value_sys << endl;
  cout << "err_nominal=" << err_value_nominal << endl;
  cout << "err_sys=" << err_value_sys << endl;
  
  cout << "local_err_rel_effect=" << local_err_rel_effect << endl;

  return local_err_rel_effect;
}
//#######################################################################################################################################################################################################
//#######################################################################################################################################################################################################
//#######################################################################################################################################################################################################
//#######################################################################################################################################################################################################
//#######################################################################################################################################################################################################
//#######################################################################################################################################################################################################
//#######################################################################################################################################################################################################
//#######################################################################################################################################################################################################
//#######################################################################################################################################################################################################
//#######################################################################################################################################################################################################
//TO SIMPLIFY FOR WHAT IS NOT USEFUL

//to revisit : mode_yield_MakeAndStoreFits

int tool_syst_yield::ComputeSystematicYield_bootstrap(string string_sample,string string_category,string string_observable,string string_campaign_MxAOD,string string_systematic,int index_start_toy,int index_stop_toy)
{
  nb_toys=index_stop_toy-index_start_toy;

  cout << "in tool_syst_yield::ComputeSystematicYield_bootstrap, for systematic=" << string_systematic << ", with index_start_toy=" << index_start_toy << ", index_stop_toy=" << index_stop_toy << endl;
  
  string string_MxAODSyst_directory;

  if (do_yield_construct_bootstrap_nominal_once)
    string_MxAODSyst_directory=ReturnMxAODSyst_directory(string_systematic);
  
  cout << "string_observable=" << string_observable << endl;

  index_start_toy_bootstrap=index_start_toy;
  index_stop_toy_bootstrap=index_stop_toy;


  cout << "string_campaign_MxAOD=" << string_campaign_MxAOD << endl;

  bool found_tree=GetTreesYield(string_sample,string_category,string_campaign_MxAOD,string_systematic,&tree_nominal,&tree_syst); //needs index in order to make the RooDataSet::reduce
  
  //  file_syst->ls();

  cout << "found_tree=" << found_tree << endl;

  cout << "tree_nominal=" << tree_nominal << endl;
  cout << "tree_syst=" << tree_syst << endl;

  //  tree_nominal->ls();
  //  tree_syst->ls();
  
  cout << "note than RelativeNonClosure is for AF2 only" << endl;
  
  cout << "tree_nominal=" << tree_nominal << endl;

  if (!found_tree) { //skip it if the systematic is not existing for this sample (for example one dedicated to an AF2 or to a full simulation)
    cout << "tree not found, continue with next syst" << endl;
    return 0;
  }
  
  //to remove the if
  //shit  if (1) {

  //to reindent
    
    nb_toys_done=0;

    cout << "nb_toys=" << nb_toys << endl;
    
    for (int index_toy=index_start_toy;index_toy<nb_toys && index_toy<index_stop_toy_bootstrap;index_toy++) {
      
      cout << "index_toy=" << index_toy << ", index_start_toy_bootstrap=" << index_start_toy_bootstrap << ", index_stop_toy_bootstrap=" << index_stop_toy_bootstrap << endl;
      
      cout << "mode_yield_MakeAndStoreFits=" << mode_yield_MakeAndStoreFits << endl;
      
      if (mode_yield_MakeAndStoreFits) { //call the construction of bootstrap toys only for the first of the current block
	
	if (index_toy==index_start_toy_bootstrap) {
	  cout << "construct bootstrap for nominal" << endl;
	  
	  //there is no other choice than construct the nominal each time, because we open a new directory : this would be too much difficult else

	  cout << "construct bootstrap for nominal" << endl;
	  ConstructTreeForBootStrap(string_category,string_campaign_MxAOD,string_systematic,"nominal",tree_nominal,&tree_nominal_bootstrap);

	  cout << "construct bootstrap for syst" << endl;
	  ConstructTreeForBootStrap(string_category,string_campaign_MxAOD,string_systematic,"syst",tree_syst,&tree_syst_bootstrap);
	}
      }
      
      if ((mode_yield_MakeAndStoreFits)) {
	nb_toys_done++;

	cout << "call ComputeSystematicsYield" << endl;
	if (mode_yield_MakeAndStoreFits) {
	 
	  cout << "LoadTreeBootStrap" << ", for string_systematic=" << string_systematic << endl;
	  LoadTreeBootStrap(string_category,string_campaign_MxAOD,string_systematic,"nominal");

	  cout << "tree_nominal_bootstrap=" << tree_nominal_bootstrap << endl;
	  cout << "tree_syst_bootstrap=" << tree_syst_bootstrap << endl;

	  LoadTreeBootStrap(string_category,string_campaign_MxAOD,string_systematic,"syst");
	  ComputeSystematicsYield(string_sample,string_category,string_campaign_MxAOD,string_systematic,index_toy,tree_nominal_bootstrap,tree_syst_bootstrap);
	}
	
	cout << "called ComputeSystematicsYield" << endl;

	//careful : this is not exclusive to previous part
	if (mode_yield_MakeAndStoreFits) {

	  if (index_toy==index_start_toy_bootstrap) { //release memory as soon as it is possible, in the case of bootstrap would no more be needed
	    
	    if (!do_yield_get_tree_nominal_once) {
	      cout << "before delete tree_nominal, tree_nominal=" << tree_nominal << endl;
	      delete tree_nominal; //why ?
	      tree_nominal=0; //ADDED Marc
	      cout << "after delete tree_nominal, tree_nominal=" << tree_nominal << endl;
	    }
	    
	    //	    cout << "tree_syst=" << tree_syst << endl;
	    delete tree_syst; //ADDED Marc
	    cout << "trees original freed" << endl;
	  }
	  else if (index_toy==index_stop_toy_bootstrap-1) { //release memory as soon as it is possible, in the case of bootstrap
	    //could delete the tree nominal bootstrap earlier!!
	    
	    cout << "index_toy=" << index_toy << ", = index_stop_toy_bootstrap -1" << endl;

	    if (do_yield_open_file_syst_once) {
	      if (string_yield_input_file_systematic!=string_yield_previous_input_file_systematic
		  &&
		  string_yield_previous_input_file_systematic!="NotInitialized") {
		
		cout << "Close the file syst" << endl;
		file_syst->Close();
		
		cout << "Closed the file syst" << endl;
		delete file_syst;
		file_syst=0; //ADDED Marc
		cout << "deleted the file syst" << endl;
	      }
	    }
	    else {
	      //CRASH HERE
	      cout << "Close the file syst" << endl;
	      file_syst->Close();
	      
	      cout << "Closed the file syst" << endl;
	      delete file_syst;
	      file_syst=0; //ADDED Marc
	      cout << "deleted the file syst" << endl;
	    }
	    
	  }

	  cout << "delete tree_nominal_bootstrap;" << endl;
	  delete tree_nominal_bootstrap;
	  tree_nominal_bootstrap=0; //ADDED Marc
	  
	  delete tree_syst_bootstrap;
	  tree_syst_bootstrap=0; //ADDED Marc
	  cout << "deleted tree_syst_bootstrap" << endl;


	  cout << "file_nominal_bootstrap->Close();" << endl;
	  file_nominal_bootstrap->Close();
	  cout << "delete file_nominal_bootstrap;" << endl;
	  delete file_nominal_bootstrap;
	  file_nominal_bootstrap=0;
	  
	  cout << "file_syst_bootstrap->Close();" << endl;
	  file_syst_bootstrap->Close();
	  cout << "delete file_syst_bootstrap;" << endl;
	  delete file_syst_bootstrap;
	  file_syst_bootstrap=0;
	  cout << "done the cleaning" << endl;

	} //and make and store results
      } //duplicate if !!

      if (mode_yield_MakeAndStoreFits && index_toy>=index_start_toy_bootstrap && index_toy<index_stop_toy_bootstrap) {
	
	cout << "index_toy=" << index_toy << ", push_back " << rel_effect_yield << endl;
	
	vec_index_toy.push_back(index_toy);
	vec_result_rel_effect_yield.push_back(rel_effect_yield);
      }
    } //end loop on toys

    cout << "finished the loop on toys" << endl;

    nb_toys_done=vec_result_rel_effect_yield.size();
    cout << "HERE, nb_toys_done=" << nb_toys_done << endl;
    //an option would be to store directly without moving to a vector
    
    //----------------------
    //store results from current range of toys

    if (mode_yield_MakeAndStoreFits) {
      cout << "call storeresult" << endl;

      //to do
      StoreResults(string_category,string_campaign_MxAOD,string_systematic);
      cout << "called storeresult" << endl;
	    
      vec_index_toy.clear();
      vec_result_rel_effect_yield.clear();
      
    } //end mode MakeAndStoreFits

    //----------------------
    //to get the max
		
    if (mode_yield_ReadFits_previously_made) {  

      //to replace here

      vec_index_toy.clear();
      vec_result_rel_effect_yield.clear();
      
      cout << "string_path=" << string_path << endl;
      cout << "string_rel_path_yield=" << string_rel_path_yield << endl;

      string string_results_toys=string_path;
      string_results_toys+=string_rel_path_yield;
      string_results_toys+="results_toys/";

      string_results_toys+=string_process;
      string_results_toys+="/";
      string_results_toys+=string_campaign_MxAOD;
      string_results_toys+="/";
      string_results_toys+=string_category;
      string_results_toys+="/";
      string_results_toys+="yield";
      string_results_toys+="/";
      string_results_toys+=string_systematic;
      string_results_toys+="/";

      string_results_toys+="ToysYield_bootstrap_";
      string_results_toys+=string_category;
      string_results_toys+="_";
      string_results_toys+=string_campaign_MxAOD;
      string_results_toys+="_";
      string_results_toys+=string_process;
      string_results_toys+="_";
      
      string_results_toys+=string_systematic;
      string_results_toys+=suffix_asymmetry_systematic;
      
      string_results_toys+="*.root";

      string string_results_tree="tree_";
      string_results_tree+=string_category;
      string_results_tree+="_";
      string_results_tree+=string_campaign_MxAOD;
      string_results_tree+="_";
      string_results_tree+=string_process;
      string_results_tree+="_";
      string_results_tree+=string_systematic;
      string_results_tree+=suffix_asymmetry_systematic;

      cout << "string_results_toys=" << string_results_toys << endl;
      cout << "string_results_tree=" << string_results_tree << endl;
      
      TChain *chain_results_toys=new TChain(string_results_tree.c_str());
      chain_results_toys->Add(string_results_toys.c_str());

      int index_toy;
      TBranch *b_index_toy;

      chain_results_toys->SetBranchAddress("index_toy",&index_toy,&b_index_toy);

      double internal_rel_effect_yield;
      TBranch *b_rel_effect_yield;
      chain_results_toys->SetBranchAddress("rel_effect_yield",&rel_effect_yield,&b_rel_effect_yield);
		    
      int nb_entries=chain_results_toys->GetEntries();
		    
      cout << "nb_entries=" << nb_entries << endl;
      
      nb_toys_done=0;
      
      for (int index_entry=0;index_entry<nb_entries;index_entry++) {

	Long64_t centry=chain_results_toys->LoadTree(index_entry); //mandatory to move from index_entry to centry with LoadTree, due to presence of several chains, else problem (else need to do Hadd, either in line command, or dynamically in the program
	if (centry<0)
	  continue;
	
	nb_toys_done++;
	
	b_rel_effect_yield->GetEntry(centry);
	
	b_index_toy->GetEntry(centry);
	
	vec_index_toy.push_back(index_toy);
	vec_result_rel_effect_yield.push_back(rel_effect_yield);
	
	//to change
	cout << "centry=" << centry << ", index_toy=" << index_toy << " / " << nb_entries << endl;
      } //end loop on entries

    } //end mode_yield_ReadFits_previously_made
    else
      nb_toys_done=vec_result_rel_effect_yield.size();
    //to change above

    cout << "nb_toys_done=" << nb_toys_done << endl;

    //stored : to make the clear here for sure
    vec_index_toy.clear();
    vec_result_rel_effect_yield.clear();
    
    //dynamical range of the histogram
    
    if (mode_yield_ReadFits_previously_made) {

      double min_rel_effect_yield=99999;
      double max_rel_effect_yield=-99999;
      
      double absolute_max_rel_effect_yield=-99999;

      //--------------
      for (int index_toy=index_start_toy;index_toy<index_stop_toy_bootstrap;index_toy++) {
	
	rel_effect_yield=vec_result_rel_effect_yield[index_toy];

	if (rel_effect_yield<min_rel_effect_yield)
	  min_rel_effect_yield=rel_effect_yield;
	if (rel_effect_yield>max_rel_effect_yield)
	  max_rel_effect_yield=rel_effect_yield;

	if (fabs(rel_effect_yield)>absolute_max_rel_effect_yield)
	  absolute_max_rel_effect_yield=fabs(rel_effect_yield);
	
      } //end loop on max

//       cout << "summary of maximums before creating automatically the rounded range for illustration" << endl;
//       cout << "min_rel_effect_yield=" << min_rel_effect_yield << endl;
//       cout << "max_rel_effect_yield=" << max_rel_effect_yield << endl;
      //--------------
      int new_nb_bins_rel_effect_yield_visualization=20; //in case the effect is exactly 0, arbitrary choose a range of vizualization
      double rounded_min_rel_effect_yield=1;
      double rounded_max_rel_effect_yield=1;
      
      rounded_max_rel_effect_yield=ReturnRoundedExtremal(max_rel_effect_yield,"max");
      rounded_min_rel_effect_yield=ReturnRoundedExtremal(min_rel_effect_yield,"min");
      //------------------------------
      TH1F *hist_rel_effect_yield=new TH1F("hist_rel_effect_yield","hist_rel_effect_yield",new_nb_bins_rel_effect_yield_visualization,rounded_min_rel_effect_yield,rounded_max_rel_effect_yield);
      hist_rel_effect_yield->Sumw2(); //is this useful since SumW2 is already at beginnig of program ?
      hist_rel_effect_yield->SetLineColor(kBlack);
      //------------------------------
      cout << "nb_toys=" << nb_toys << endl;


      for (int index_toy=0;index_toy<nb_toys;index_toy++) {
	//	cout << "Fill : index_toy=" << index_toy << ", fill with " << vec_result_rel_effect_yield[index_toy] << endl;
	hist_rel_effect_yield->Fill(vec_result_rel_effect_yield[index_toy]);
	//	cout << "so far, hist_rel_effect_yield->GetMean()=" << hist_rel_effect_yield->GetMean() << endl;
      }
      
      vec_index_toy.clear();
      vec_result_rel_effect_yield.clear();
      //---
      rel_effect_yield=hist_rel_effect_yield->GetMean();
      err_rel_effect_yield=hist_rel_effect_yield->GetRMS();

      //for bootstrap, no division by any function of the number of experiments, because the initial statistics is preserved
		    

      cout << "hist_rel_effect_yield->GetEntries()=" << hist_rel_effect_yield->GetEntries() << endl;
      cout << "hist_rel_effect_yield->GetMean()=" << hist_rel_effect_yield->GetMean() << endl;
      //      exit(1);
      //---
      Plot_pseudo_experiments(string_sample,string_category,string_campaign_MxAOD,string_systematic,index_sym_asym,"yield",hist_rel_effect_yield,rel_effect_yield,err_rel_effect_yield);

      //---
      delete hist_rel_effect_yield;
      hist_rel_effect_yield=0; //ADDED Marc
    }
    //shit  } //end bootstrap

  cout << "summary of the partition" << endl;
  cout << "rel_effect_yield=" << rel_effect_yield << " +/- " << err_rel_effect_yield << endl;

  if (do_yield_construct_bootstrap_nominal_once) {
    if (string_yield_input_file_systematic!=string_yield_previous_input_file_systematic)
      string_yield_previous_input_file_systematic=string_yield_input_file_systematic;
  }
  
  return 1; //return success
}
//option for much later : to separate nominal and syst : need to close two different files
//#######################################################################################################################################################################################################
bool tool_syst_yield::GetTreesYield(string string_sample,string string_category,string string_campaign_MxAOD,string string_systematic,TTree **pptr_tree_nominal,TTree **pptr_tree_syst)
{
  cout << "starts GetTreesYield" << endl;

  //search for string process, that is used for the unix command
  
  cout << "current_sample=" << string_sample << endl;

  string string_to_search="tree_sel_";
  if (string_systematic=="showering")
    string_to_search+="nominal";
  else {
    string_to_search+=string_systematic;
    string_to_search+=suffix_asymmetry_systematic;
  }
  string_to_search+="_";
  string_to_search+=string_category;
  cout << "string_to_search=" << string_to_search << endl;
  
  bool local_found=0; //could be improved if check the status of stream (later)

  TTree *tree_test=(TTree *)file_syst->Get(string_to_search.c_str());

  if (tree_test)
    local_found=1;

  //stream_list_files.close();

  cout << "local_found=" << local_found << endl;
  //  exit(1);

  if (local_found==0) {//not found
    if (vec_nature_syst_components_sym_asym[index_sym_asym]=="") {
      file_or_tree_exists_sym=0;
    }
    else if (vec_nature_syst_components_sym_asym[index_sym_asym]=="__1up") {
      file_or_tree_exists_up=0;
    }
    else if (vec_nature_syst_components_sym_asym[index_sym_asym]=="__1down") {
      file_or_tree_exists_down=0;
    }

    cout << "not found_file_syst_shape_candidates, return to caller" << endl;
    return 0;
  } //end not found
  
  //  cout << "string_file_syst_shape_candidates=" << string_file_syst_shape_candidates << endl;

  //     if (tree_original_nominal) {
  //     cout << "tree_original_nominal exists" << endl;
  //     cout << "tree_original_nominal->GetEntries()=" << tree_original_nominal->GetEntries() << endl;
  //     }

  string string_directory_MxAOD=ReturnMxAODSyst_directory(string_systematic);

  string string_file_input=string_path;
  string_file_input+=string_rel_path_yield;
  
  string_file_input+="trees_and_hist/";
  string_file_input+=string_directory_MxAOD;
  string_file_input+="/";
  
  string_file_input+=string_campaign_MxAOD;
  string_file_input+="_";
  
  int size_string_campaign_MxAOD=string_campaign_MxAOD.size();
  string_process=string_sample.substr(size_string_campaign_MxAOD+1); //h0xx_mc16x_, or h0xx_mc16x_h0xx_mc16x, etc. : transparent with multiple parts
  
  string_file_input+=string_process;
  string_file_input+="_";
  
  if (found_theory) {
    if (string_sample.find("HH")!=string::npos
	||
	string_sample.find("MGH7")!=string::npos
	)
      string_file_input+="nominal";
    else
      string_file_input+="PhotonSys";
  }
  else {
    string_file_input+=string_directory_MxAOD;
  }
  
  cout << "index_sym_asym=" << index_sym_asym << ", vec_nature_syst_components_sym_asym[index_sym_asym]=" << vec_nature_syst_components_sym_asym[index_sym_asym] << endl;
  
  string_file_input+=".root";

  string_yield_input_file_systematic=string_file_input;

  //!=string_previous_input_file_systematic) //no comparison to NotInitialized : for sure
      
  /*//to change names here
//shit
  string_yield_input_file_systematic=string_file_syst_shape_candidates;

  if (do_yield_open_file_syst_once) {
    if (string_input_file_systematic!=string_previous_input_file_systematic) //no comparison to NotInitialized : for sure
      file_syst=new TFile(string_input_file_systematic.c_str(),"read");
  }
  else
    file_syst=new TFile(string_input_file_systematic.c_str(),"read"); //historical
    //    file_syst=new TFile(string_file_syst_shape_candidates.c_str(),"read"); //historical

  //file_syst=TFile::Open(string_input_file_systematic.c_str(),"read");
  //  file_syst->ls();
  */
  
  //     if (tree_original_nominal) {
  //     cout << "tree_original_nominal exists" << endl;
  //     cout << "tree_original_nominal->GetEntries()=" << tree_original_nominal->GetEntries() << endl;
  //     }
  
  //  cout << "done_fit_shape_nominal=" << done_fit_shape_nominal << endl;

  string string_tree_nominal="tree_sel_nominal_";
  string_tree_nominal+=string_category;
  
  if (do_yield_get_tree_nominal_once) {
    if (string_yield_input_file_systematic!=string_yield_previous_input_file_systematic) //no comparison to NotInitialized : for sure

      if (string_yield_previous_input_file_systematic!="NotInitialized") {
	cout << "before delete tree_nominal, tree_nominal=" << tree_nominal << endl;
	delete tree_nominal;
	tree_nominal=0; //ADDED Marc
	cout << "after delete tree_nominal, tree_nominal=" << tree_nominal << endl;
      }
    
    *pptr_tree_nominal=(TTree *)file_syst->Get(string_tree_nominal.c_str()); //this is really file_syst that contains also the nominal
  }
  else
    *pptr_tree_nominal=(TTree *)file_syst->Get(string_tree_nominal.c_str()); //this is really file_syst that contains also the nominal
  
  //if we put SetDirectory(0) to TTree, the RooDataSet gets empty
  //if we don't put SetDirectory(0) to TTree, the tree_nominal information is lost once the file is closed
  
  //    file_syst->Close();
  //-------------
  //  if (*pptr_tree_nominal) {
  //    cout << "tree_nominal exists" << endl;
  //    cout << "tree_nominal=" << *pptr_tree_nominal << endl;
  //    cout << "tree_nominal->GetEntries()=" << (*pptr_tree_nominal)->GetEntries() << endl;
  //  }
  
  string string_tree_syst;
  
  if (string_systematic!="showering") {
    string_tree_syst+="tree_sel_";
    string_tree_syst+=string_systematic;
    string_tree_syst+=vec_nature_syst_components_sym_asym[index_sym_asym];
    string_tree_syst+="_";
    string_tree_syst+=string_category;
    
    *pptr_tree_syst=(TTree *)file_syst->Get(string_tree_syst.c_str());
    //    cout << "tree_syst=" << *pptr_tree_syst << endl;
  }
  
  return 1;
}
//#######################################################################################################################################################################################################
void tool_syst_yield::ComputeSystematicsYield(string string_sample,string string_category,string string_campaign_MxAOD,string string_systematic,int index_toy,TTree *current_tree_nominal,TTree *current_tree_syst)
{
  cout << "==========================================" << endl;
  cout << "in ComputeSystematicsYield for string_systematic=" << string_systematic << ", index_toy=" << index_toy << endl;

  cout << "current_tree_nominal=" << current_tree_nominal << endl;
  cout << "current_tree_syst=" << current_tree_syst << endl;

  if (current_tree_nominal && current_tree_syst) {
    if (vec_nature_syst_components_sym_asym[index_sym_asym]=="") {
      file_or_tree_exists_sym=1;
    }
    else if (vec_nature_syst_components_sym_asym[index_sym_asym]=="__1up") {
      file_or_tree_exists_up=1;
    }
    else if (vec_nature_syst_components_sym_asym[index_sym_asym]=="__1down") {
      //found_trees_syst_down_shape_candidate=1;
      file_or_tree_exists_down=1;
    }
  }
  else if (string_systematic!="showering") {
    //  if (!current_tree_nominal || !current_tree_syst) {
    cout << "problem: tree not found, return to the caller" << endl;
    return;
  }

  /*big shit
  cout << "allocate hist_nominal, for index_toy=" << index_toy << endl;
  
  hist_nominal=new TH1F("hist_nominal","hist_nominal",1,-1,1);
  
  if (string_systematic!="showering" && current_tree_syst) {
    hist_syst=new TH1F("hist_syst","hist_syst",1,-1,1);
  }
  */

  //special code size take only one character
  
  //to revisit the size here: it should really be 19 : to check with the print out
  
  //shit  char buffer_modulo_selection[19]; // up to 2 digits for each number <=> 20 characters, including the '`0'
  
  cout << "current_tree_nominal=" << current_tree_nominal << endl;
  current_tree_nominal->ls();

  double nb_sel_nominal=0;
  double err_nb_sel_nominal=0;

  //to do : could be accelerated by not doing it if this is the same nominal as previous one

  if (current_tree_nominal) {
    //to make function in order to factorize

    double weight_total=0;
    TBranch *branch_weight_total=0;
    
    cout << "index_toy=" << index_toy << endl;
    
    char buffer_weight_total_bootstrap_current_toy[33]; //ok for sure for 5 digits in the index toy + \0
    sprintf(buffer_weight_total_bootstrap_current_toy,"weight_total_bootstrap_toy_%d",index_toy);

    current_tree_nominal->SetBranchAddress(buffer_weight_total_bootstrap_current_toy,&weight_total,&branch_weight_total);
    current_tree_nominal->SetBranchStatus("*",1);

    double nb_sel=0;
    double err_nb_sel=0;

    int nb_entries=current_tree_nominal->GetEntries();
    
    for (int index_tree=0;index_tree<nb_entries;index_tree++) {
      //index : works for tree (for chain, need centry)
      branch_weight_total->GetEntry(index_tree);
      
      nb_sel+=weight_total;
      err_nb_sel+=weight_total*weight_total;
    } //end loop on events
    
    err_nb_sel=sqrt(err_nb_sel);

    nb_sel_nominal=nb_sel;
    err_nb_sel_nominal=err_nb_sel;

    cout << "index_toy=" << index_toy << ", nb_sel_nominal=" << nb_sel_nominal << " +/- " << err_nb_sel_nominal << endl;
  } //end loop on nominal
  
  double nb_sel_sys=0;
  double err_nb_sel_sys=0;

  if (string_systematic!="showering" && current_tree_syst) {
    double weight_total=0;
    TBranch *branch_weight_total=0;
    
    char buffer_weight_total_bootstrap_current_toy[33]; //ok for sure for 5 digits in the index toy + \0
    sprintf(buffer_weight_total_bootstrap_current_toy,"weight_total_bootstrap_toy_%d",index_toy);
    //sprintf(buffer_weight_total_bootstrap_current_toy,"w_total_btsp_toy_%d",index_toy);
    
    current_tree_syst->SetBranchAddress(buffer_weight_total_bootstrap_current_toy,&weight_total,&branch_weight_total);

    current_tree_syst->SetBranchStatus("*",1);

    double nb_sel=0;
    double err_nb_sel=0;

    int nb_entries=current_tree_syst->GetEntries();

    for (int index_tree=0;index_tree<nb_entries;index_tree++) {
      //index : works for tree (for chain, need centry)
      branch_weight_total->GetEntry(index_tree);
      
      nb_sel+=weight_total;
      err_nb_sel+=weight_total*weight_total;
    } //end loop on events
    
    err_nb_sel=sqrt(err_nb_sel);

    nb_sel_sys=nb_sel;
    err_nb_sel_sys=err_nb_sel;
    
    cout << "for syst, index_toy=" << index_toy << ", nb_sel_sys=" << nb_sel_sys << " +/- " << err_nb_sel_sys << endl;
  }

  rel_effect_yield=100.*((nb_sel_sys/nb_sel_nominal)-1);
  err_rel_effect_yield=100.*fabs((nb_sel_sys/nb_sel_nominal)-1.)*sqrt(pow(err_nb_sel_sys/nb_sel_sys,2)+pow(err_nb_sel_nominal/nb_sel_nominal,2));

  cout << "to see the rel effect" << endl;
  
  cout << "index_toy=" << index_toy << ", rel_effect_yield=" << rel_effect_yield << "+/- " << err_rel_effect_yield << endl;

  /*big shit
  delete hist_nominal;
  delete hist_syst;
  */

  return;
}

//to change string_nominal_bootstrap
//#######################################################################################################################################################################################################
void tool_syst_yield::ConstructTreeForBootStrap(string string_category,string string_campaign_MxAOD,string string_systematic,string string_nominal_syst,TTree *tree_original,TTree **pptr_tree_bootstrap)
{
  cout << "in ConstructTreeForBootStrap, phase 1" << endl;

  //mandatory to have a duplicate, in order to have authorization to add many variables (else error messages Error in <TBranch::TBranch::WriteBasketImpl>: basket's WriteBuffer failed.
  //------------
  //these will be parameters of the caller
  
  TRandom3 rand3;

  char affix_range_toys[24]; //ok fore sure : toys nmuber with up to 5 characters needed + 1 for \0
  
  //flag not useful ?
  
  sprintf(affix_range_toys,"_range_toys_%d_%d",index_start_toy_bootstrap,index_stop_toy_bootstrap);
  //------------
  string string_file_bootstrap=string_path+string_rel_path_shape+"trees_bootstrap/";

  string_file_bootstrap+=string_process;
  string_file_bootstrap+="/";
  string_file_bootstrap+=string_campaign_MxAOD;
  string_file_bootstrap+="/";
  string_file_bootstrap+=string_category;
  string_file_bootstrap+="/";
  string_file_bootstrap+="yield";
  string_file_bootstrap+="/";
  string_file_bootstrap+=string_systematic;
  string_file_bootstrap+="/";

  string_file_bootstrap+="tree_bootstrap_";

  string_file_bootstrap+=string_nominal_syst;
  string_file_bootstrap+="_";
  string_file_bootstrap+=string_campaign_MxAOD;
  string_file_bootstrap+="_";
  string_file_bootstrap+=string_systematic;
  string_file_bootstrap+=suffix_asymmetry_systematic;
  string_file_bootstrap+="_";
  string_file_bootstrap+=string_process;
  //not perfect, but why not, whenever it is compatible everywhere    
  string_file_bootstrap+="_";
  string_file_bootstrap+=affix_range_toys;
  string_file_bootstrap+="_";
  string_file_bootstrap+=string_category;
  string_file_bootstrap+=".root";
  
  cout << "string_file_bootstrap=" << string_file_bootstrap << endl;

  cout << "string_systematic=" << string_systematic << endl;

  //  exit(1);

  if (string_nominal_syst=="nominal")
    file_nominal_bootstrap=new TFile(string_file_bootstrap.c_str(),"recreate");
  else if (string_nominal_syst=="syst")
    file_syst_bootstrap=new TFile(string_file_bootstrap.c_str(),"recreate");
  
  cout << "cloning" << endl;
  (*pptr_tree_bootstrap)=tree_original->CloneTree();
  cout << "cloned" << endl;
  
  int nb_entries=(*pptr_tree_bootstrap)->GetEntries();
  cout << "nb_entries=" << nb_entries << endl;
  
  int eventNumber;
  TBranch *b_eventNumber;
  (*pptr_tree_bootstrap)->SetBranchAddress("eventNumber",&eventNumber,&b_eventNumber);
  
  double weight_total;
  TBranch *b_weight_total;
  
  (*pptr_tree_bootstrap)->SetBranchAddress("weight_total",&weight_total,&b_weight_total);

  unsigned long *tab_seed_bootstrap=(unsigned long *)malloc((index_stop_toy_bootstrap-index_start_toy_bootstrap+1)*sizeof(unsigned long));
  TBranch **tab_b_seed_bootstrap=(TBranch **)malloc((index_stop_toy_bootstrap-index_start_toy_bootstrap+1)*sizeof(TBranch *));
  
  double *tab_weight_poisson_bootstrap=(double *)malloc((index_stop_toy_bootstrap-index_start_toy_bootstrap+1)*sizeof(double));
  TBranch **tab_b_weight_poisson_bootstrap=(TBranch **)malloc((index_stop_toy_bootstrap-index_start_toy_bootstrap+1)*sizeof(TBranch *));

  double *tab_weight_total_bootstrap=(double *)malloc((index_stop_toy_bootstrap-index_start_toy_bootstrap+1)*sizeof(double));
  TBranch **tab_b_weight_total_bootstrap=(TBranch **)malloc((index_stop_toy_bootstrap-index_start_toy_bootstrap+1)*sizeof(TBranch *));

  char buffer_seed_current_toy[15]; //for 5 digits in the index_toy
  char buffer_seed_current_toy_with_type[16];

  char buffer_weight_poisson_bootstrap_current_toy[35]; //for 5 digits in the index toy + \0
  char buffer_weight_poisson_bootstrap_current_toy_with_type[37]; //for 5 digits in the index toy

  char buffer_weight_total_bootstrap_current_toy[33]; //for 5 digits in the index toy + \0
  char buffer_weight_total_bootstrap_current_toy_with_type[35]; //for 5 digits in the index toy
  //------------
  cout << "loop on toys" << endl;
  
  for (int index_toy=0;index_toy<nb_toys;index_toy++) { //ok for sure
    
    //Branching of seed individual, for debugging purpose
    sprintf(buffer_seed_current_toy,"seed_toy_%d",index_toy);
    sprintf(buffer_seed_current_toy_with_type,"seed_toy_%d/I",index_toy);
    tab_b_seed_bootstrap[index_toy]=(*pptr_tree_bootstrap)->Branch(buffer_seed_current_toy,&(tab_seed_bootstrap[index_toy]),buffer_seed_current_toy_with_type);

    //Branching of weight_poisson individual, for debugging purpose
    sprintf(buffer_weight_poisson_bootstrap_current_toy,"weight_poisson_bootstrap_toy_%d",index_toy);
    sprintf(buffer_weight_poisson_bootstrap_current_toy_with_type,"weight_poisson_bootstrap_toy_%d/D",index_toy);
    tab_b_weight_poisson_bootstrap[index_toy]=(*pptr_tree_bootstrap)->Branch(buffer_weight_poisson_bootstrap_current_toy,&(tab_weight_poisson_bootstrap[index_toy]),buffer_weight_poisson_bootstrap_current_toy_with_type);
    
    //weight product : for bootstrap

    sprintf(buffer_weight_total_bootstrap_current_toy,"weight_total_bootstrap_toy_%d",index_toy);
    sprintf(buffer_weight_total_bootstrap_current_toy_with_type,"weight_total_bootstrap_toy_%d/D",index_toy);

    tab_b_weight_total_bootstrap[index_toy]=(*pptr_tree_bootstrap)->Branch(buffer_weight_total_bootstrap_current_toy,&(tab_weight_total_bootstrap[index_toy]),buffer_weight_total_bootstrap_current_toy_with_type);
    
  } //end loop on toys
  //====================================================================
  cout << "change of weights of the bootstrap" << endl;

  //remark : for the seed, the value stored is not the correct one : bug of TRandom3, but no consequence
  //https://sft.its.cern.ch/jira/browse/ROOT-10059
  
  for (int index_entry=0;index_entry<nb_entries;index_entry++) {
    b_weight_total->GetEntry(index_entry);
    b_eventNumber->GetEntry(index_entry);
    
    for (int index_toy=0;index_toy<nb_toys;index_toy++) {

      int index_absolute_toy=index_toy+index_start_toy_bootstrap;

      //unsigned long : 0 to 4 294 967 295
      //always add 1 in order not to depend on CPU clock
      //one needs to depend on the eventNumber, so that the nominal and syst have the same Poisson exactly ; typically max=120k events at most
      //for sure, the seed should be the same for a same eventNumber of nominal and syst, else, there would be an important variation from Poisson which would artificially increase the bootstrap error

      unsigned long seed=1+10000*eventNumber+index_absolute_toy; //up to 10000 toys

      rand3.SetSeed(seed); //typically up to 1000
      
      int weight_poisson=rand3.Poisson(1.);

      tab_seed_bootstrap[index_toy]=seed;
      tab_b_seed_bootstrap[index_toy]->Fill();

      tab_weight_poisson_bootstrap[index_toy]=weight_poisson;
      tab_b_weight_poisson_bootstrap[index_toy]->Fill();
      
      tab_weight_total_bootstrap[index_toy]=weight_total*weight_poisson;
      tab_b_weight_total_bootstrap[index_toy]->Fill();

      //      cout << "string_nominal_syst=" << string_nominal_syst << ", index_toy=" << index_toy << ", seed=" << seed << ", weight_poisson=" << weight_poisson << ", weight after multiplication=" << weight_total*weight_poisson << endl;
    }
  } //end loop on tree
  
  cout << "nb_entries=" << nb_entries << endl;
  
  (*pptr_tree_bootstrap)->Write();
  
  if (string_nominal_syst=="nominal") {
    file_nominal_bootstrap->Close();
    delete file_nominal_bootstrap;
    file_nominal_bootstrap=0;
  }
  else if (string_nominal_syst=="syst") {
    file_syst_bootstrap->Close();
    delete file_syst_bootstrap;
    file_syst_bootstrap=0;
  }

  cout << "free(tab_seed_bootstrap);" << endl;
  free(tab_seed_bootstrap);
  cout << "free(tab_b_seed_bootstrap);" << endl;
  free(tab_b_seed_bootstrap);
  
  cout << "free(tab_weight_poisson_bootstrap);" << endl;
  free(tab_weight_poisson_bootstrap);
  cout << "free(tab_b_weight_poisson_bootstrap);" << endl;
  free(tab_b_weight_poisson_bootstrap);
  
  cout << "free(tab_weight_total_bootstrap);" << endl;
  free(tab_weight_total_bootstrap);
  cout << "free(tab_b_weight_total_bootstrap);" << endl;
  free(tab_b_weight_total_bootstrap);
  
  cout << "end of tool_syst_yield::ConstructTreeForBootStrap" << endl;
}
//#######################################################################################################################################################################################################
void tool_syst_yield::StoreResults(string string_category,string string_campaign_MxAOD,string string_systematic)
{
  cout << "store results for current range of toys" << endl;

  string string_save_results_toys=string_path;
  string_save_results_toys+=string_rel_path_shape;
  string_save_results_toys+="results_toys/";

  string_save_results_toys+=string_process;
  string_save_results_toys+="/";
  string_save_results_toys+=string_campaign_MxAOD;
  string_save_results_toys+="/";

  string_save_results_toys+=string_category;
  string_save_results_toys+="/";

  string_save_results_toys+="yield";
  string_save_results_toys+="/";

  string_save_results_toys+=string_systematic;
  string_save_results_toys+="/";

  string_save_results_toys+=string_category;
  string_save_results_toys+="_";
  string_save_results_toys+=string_campaign_MxAOD;
  string_save_results_toys+="_";
  string_save_results_toys+=string_process;
  string_save_results_toys+="_";
  string_save_results_toys+=string_systematic;
  string_save_results_toys+=suffix_asymmetry_systematic;
  string_save_results_toys+="_range_toys_";
		    
  char buffer_range_toys_considered[15];
  sprintf(buffer_range_toys_considered,"%d_%d",index_start_toy_bootstrap,index_stop_toy_bootstrap);
  string_save_results_toys+=buffer_range_toys_considered;
  string_save_results_toys+=".root";
  
  /*
    string string_unix_command="rm ";
    string_unix_command+=string_save_results_toys;
    gSystem->Exec(string_unix_command.c_str());
  */

  cout << "string_save_results_toys=" << string_save_results_toys << endl;

  TFile *file_save_results_toys=new TFile(string_save_results_toys.c_str(),"recreate");

  string string_results_tree="tree_";
  string_results_tree+=string_category;
  string_results_tree+="_";
  string_results_tree+=string_campaign_MxAOD;
  string_results_tree+="_";
  string_results_tree+=string_process;
  string_results_tree+="_";
  string_results_tree+=string_systematic;
  string_results_tree+=suffix_asymmetry_systematic;

  TTree *tree_results_toys=new TTree(string_results_tree.c_str(),string_results_tree.c_str());

  //creation of the output branches

  int internal_index_toy;
  TBranch *b_internal_index_toy=tree_results_toys->Branch("index_toy",&internal_index_toy);
      
  double internal_rel_effect_yield;
  TBranch *b_internal_rel_effect_position_shape=tree_results_toys->Branch("rel_effect_yield",&internal_rel_effect_yield);
		    

  //  cout << "nb_toys_done=" << nb_toys_done << endl;
  for (unsigned int index_toy=0;index_toy<nb_toys_done;index_toy++) {
    //for (unsigned int index_toy=0;index_toy<nb_toys;index_toy++) {
    internal_index_toy=vec_index_toy[index_toy];
    internal_rel_effect_yield=vec_result_rel_effect_yield[index_toy];

    tree_results_toys->Fill();
  } //end loop on toys
		    
  tree_results_toys->Write();

  delete tree_results_toys;
		    
  file_save_results_toys->Close();

  delete file_save_results_toys;
      
  cout << "stored results for current range of toys" << endl;

  return;
}

//to factorize with shape ? may need plenty of if
//#######################################################################################################################################################################################################
void tool_syst_yield::Plot_pseudo_experiments(string string_sample,string string_category,string string_campaign_MxAOD,string string_systematic,int local_index_sym_asym,string string_observable,TH1F *hist_rel_effect,double local_rel_effect,double local_err_rel_effect)
{
  cout << "in Plot_pseudo_experiments" << endl;
  cout << "local_rel_effect=" << local_rel_effect << endl;

  TCanvas *canvas_pseudo_experiments_rel_effect=new TCanvas("canvas_pseudo_experiments_rel_effect","canvas_pseudo_experiments_rel_effect",800,600);
  canvas_pseudo_experiments_rel_effect->SetRightMargin(0.07); //for sure
  canvas_pseudo_experiments_rel_effect->SetTopMargin(0.03);
  
  TH1F *hist_dummy=canvas_pseudo_experiments_rel_effect->DrawFrame(hist_rel_effect->GetXaxis()->GetXmin(),1e-6,hist_rel_effect->GetXaxis()->GetXmax(),hist_rel_effect->GetMaximum()*2);

  //maybe next line is not useful because DrawFrame alreay draw ?
  //depends wether it takes care of the SetTitle and so on
  hist_dummy->Draw();

  hist_dummy->GetXaxis()->SetTitle("100x(yield_{syst}-yield_{nominal})/yield_{nominal} [%]");
  
  char buffer[100];
  
  sprintf(buffer,"Entries / %4.4f",hist_rel_effect->GetBinWidth(1));
  
  hist_dummy->GetYaxis()->SetTitle(buffer);
  hist_rel_effect->Draw("histesame");
  
  float horizontal_position_baseline;
  horizontal_position_baseline=0.63;
  
  float horizontal_position=0.53;
  float vertical_position_baseline=0.58;
  float vertical_position;
  
  vertical_position=vertical_position_baseline;

  TLatex latex;
  latex.SetNDC(0);
  latex.SetTextSize(0.04); //0.045 is std
  latex.SetTextColor(kBlack);
  latex.SetTextFont(42); //put back the font
  
  latex.SetTextColor(kBlack);
  latex.SetNDC();
  latex.SetTextSize(0.04); //0.045 is std
  latex.SetTextFont(72);
  latex.DrawLatex(horizontal_position,0.92,"ATLAS");
  latex.SetTextFont(42); //put back the font
  latex.DrawLatex(horizontal_position+0.1,0.92,"internal");
  
  latex.DrawLatex(horizontal_position,0.84,(get_string_ECM_luminosity(string_campaign_MxAOD)).c_str());

  latex.SetTextSize(0.016); //0.034 too small for HH non resonant
  latex.SetTextColor(kBlack);
  
  latex.DrawLatex(horizontal_position,0.78,string_sample.c_str());
  
  latex.SetTextSize(0.018);
  latex.DrawLatex(horizontal_position,0.73,(string_systematic+suffix_asymmetry_systematic).c_str());
  latex.SetTextSize(0.022);
  
  latex.DrawLatex(horizontal_position,0.63,string_category.c_str());
  
  latex.SetTextColor(kRed);
  
  sprintf(buffer,"rel. effect (%%) on yield: %4.3f #pm %4.3f",local_rel_effect,local_err_rel_effect);
  latex.DrawLatexNDC(horizontal_position_baseline,vertical_position,buffer);

  vertical_position-=0.05;
  latex.SetTextColor(kBlack);

  sprintf(buffer,"bootstrap, %d toys",nb_toys);
  
  latex.DrawLatex(0.15,0.62,buffer);
  
  string string_saveas=string_path+string_rel_path_shape+"figures/";

  string_saveas+=string_process;
  string_saveas+="/";
  string_saveas+=string_campaign_MxAOD;
  string_saveas+="/";
  string_saveas+=string_category;
  string_saveas+="/";
  string_saveas+="yield";
  string_saveas+="/";
  string_saveas+=string_systematic;
  string_saveas+="/";

  string_saveas+="/Overview_";
  string_saveas+=string_method_partition_events;
  string_saveas+="_";
  
  string_saveas+=string_sample;
  string_saveas+="_rel_effect_";

  string_saveas+="yield";
  string_saveas+="_";
  string_saveas+=string_systematic;
  string_saveas+=vec_nature_syst_components_sym_asym[local_index_sym_asym];
  string_saveas+="_";
  string_saveas+=string_category;
  string_saveas+=".png";
  
  canvas_pseudo_experiments_rel_effect->SaveAs(string_saveas.c_str());
  
  cout << "delete the other hist_dummy" << endl;
  delete hist_dummy;
  
  delete canvas_pseudo_experiments_rel_effect;
  
  return;
}
//#######################################################################################################################################################################################################
void tool_syst_yield::LoadTreeBootStrap(string string_category,string string_campaign_MxAOD,string string_systematic,string string_nominal_systematic)
{
  cout << "in LoadTreeBootStrap, phase 1" << endl;

  char affix_range_toys[24]; //ok for sure : toys number with up to 5 characters : star and stop + 1 for \0
  
  sprintf(affix_range_toys,"_range_toys_%d_%d",index_start_toy_bootstrap,index_stop_toy_bootstrap);
  //------------
  string string_file_bootstrap=string_path+string_rel_path_shape+"trees_bootstrap/";

  string_file_bootstrap+=string_process;
  string_file_bootstrap+="/";
  string_file_bootstrap+=string_campaign_MxAOD;
  string_file_bootstrap+="/";
  string_file_bootstrap+=string_category;
  string_file_bootstrap+="/";
  string_file_bootstrap+="yield";
  string_file_bootstrap+="/";
  string_file_bootstrap+=string_systematic;
  string_file_bootstrap+="/";

  string_file_bootstrap+="tree_bootstrap_";

  string_file_bootstrap+=string_nominal_systematic;
  string_file_bootstrap+="_";
  string_file_bootstrap+=string_campaign_MxAOD;
  string_file_bootstrap+="_";
  string_file_bootstrap+=string_systematic;
  string_file_bootstrap+=suffix_asymmetry_systematic;
  string_file_bootstrap+="_";
  string_file_bootstrap+=string_process;
  //not perfect, but why not, whenever it is compatible everywhere    
  string_file_bootstrap+="_";
  string_file_bootstrap+=affix_range_toys;
  string_file_bootstrap+="_";
  string_file_bootstrap+=string_category;
  string_file_bootstrap+=".root";
  
  cout << "string_file_bootstrap=" << string_file_bootstrap << endl;
  cout << "string_systematic=" << string_systematic << endl;
  
  string string_tree_name="tree_sel_";

  if (string_nominal_systematic=="nominal")
    string_tree_name+="nominal_";
  else if (string_nominal_systematic=="syst") {
    string_tree_name+=string_systematic;
    string_tree_name+=vec_nature_syst_components_sym_asym[index_sym_asym];
    string_tree_name+="_";
  }
  
  string_tree_name+=string_category;
  
  cout << "string_tree_name=" << string_tree_name << endl;

  if (string_nominal_systematic=="nominal") {
    file_nominal_bootstrap=new TFile(string_file_bootstrap.c_str(),"read");
    
    tree_nominal_bootstrap=(TTree *)file_nominal_bootstrap->Get(string_tree_name.c_str());
  }
  else if (string_nominal_systematic=="syst") {
    file_syst_bootstrap=new TFile(string_file_bootstrap.c_str(),"read");
  
    tree_syst_bootstrap=(TTree *)file_syst_bootstrap->Get(string_tree_name.c_str());
    cout << "tree_syst_bootstrap" << endl;
  }

  cout << "in LoadTreeBootStrap, phase end" << endl;
}
//###################################################################################################
