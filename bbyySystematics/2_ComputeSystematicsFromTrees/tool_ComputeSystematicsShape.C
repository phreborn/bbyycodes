//to do : to delete the TLine

//why do we need a search for the sample with tree instead of direction bijection ?

//------------------------------
//gain : 60 %
bool do_construct_bootstrap_nominal_once=1;
bool do_get_tree_nominal_once=1;
bool do_open_file_syst_once=1;
//------------------------------
//to do : put string_campaign_MxAOD in the class ?

//a priori, could skip roorealvar category 

//to do : shape_root1_roofit2 : replace by a string ?

//TO DO : for string_sample : to analyze, etc.

//to simplify : remove the root mode ?

////mbb : needs the large extension of mbb

//to clear the vector after the end of the loop : no consequence but more clean

//TO FACTORIZE THE TF1

//1) to generalize the pdf definition for nominal and syst, in particular the initialization of parameters
//with a function that calls nominal and syst

//due to minuit precision, one should either :
//use fitTo, but with rescaling to the statistics available (option rescale_to_real_stat)
//or use RooMinimizer, but using the set epsilon to a tiny number (but the error would not be good)

//scan likelihood seems not to work with weight, unbinned : at least delta nll incompatible with the values found for the error
//4906 lines
using namespace std;
#include "global.h"

#include <algorithm> //for replace
#include <RooBukinPdf.h>
#include <RooFitResult.h>
#include <RooNLLVar.h>
#include <RooPlot.h>

#include <TCanvas.h>
#include <TChain.h>
#include <TFitResult.h>
#include <TGaxis.h>
#include <TGraph.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TLine.h>
#include <TRandom3.h>

//#include "RobustMinimize.C"

#include "tool_FunctionalForm_shape.C"

//using namespace ROOT;
//using namespace Math

//[#1] INFO:Eval -- RooAbsReal::attachToTree(eventNumber) TTree Int_t branch eventNumber will be converted to double precision

int shape_root1_roofit2=2;
int shape_chi2fit_1_loglikelihoodfit2=2;
bool use_minimizer=0;

//int shape_chi2fit_1_loglikelihoodfit2=1;
//bug with chi2fit, for the range https://root-forum.cern.ch/t/2-bugs-in-roochi2var-with-ranges/16258

int do_weight_event=0; //do not use it, since in particular for single Higgs, the weight lumi is not the same for all subprocesses

//for chi2fitTo : bug
//if we put range in standalone mode way, it considers it, but it crashes at a given moment
//if we consider the roolinked, it ignores the range
//https://sft.its.cern.ch/jira/si/jira.issueviews:issue-html/ROOT-5298/ROOT-5298.html

//bool rescale_to_real_stat=1; //only for bootstraps, but maybe also for classical actually


//remark : rescale to real stat to 1 is not valid for samples made of several samples
//so better to put this option to 0


bool rescale_to_real_stat=0; //only for bootstraps, but maybe also for classical actually
//bool rescale_to_real_stat=1; //only for bootstraps, but maybe also for classical actually

//to generalize to a single systematic : dangerous because nominal of a systematic may not have the same result
//as another one, in case of bug from framework

//and comparison done afterwards ?
//need to call it with nominal first, for a given b

string get_string_ECM_luminosity(string string_campaign_MxAOD);

vector <double> return_intersection(TH1D *hist_cumulative,double threshold);

double ReturnRoundedExtremal(double value,string string_min_max);

string string_input_file_systematic="NotInitialized";
string string_previous_input_file_systematic="NotInitialized";

//==============================================================================
int tool_syst_shape::ComputeSystematicShape_classical_jacknife_bootstrap(string string_sample,string string_category,string string_observable,string string_campaign_MxAOD,string string_systematic,int index_start_toy,int index_stop_toy)
{
  cout << "in tool_syst_shape::ComputeSystematicShape_classical_jacknife_bootstrap, for systematic=" << string_systematic << ", with index_start_toy=" << index_start_toy << ", index_stop_toy=" << index_stop_toy << endl;

  nb_toys=index_stop_toy-index_start_toy;
  cout << "nb_toys=" << nb_toys << endl;
  //  exit(1);

  string string_MxAODSyst_directory;

  if (do_construct_bootstrap_nominal_once)
    string_MxAODSyst_directory=ReturnMxAODSyst_directory(string_systematic);
  
  cout << "string_observable=" << string_observable << endl;

  cout << "string_method_partition_events=" << string_method_partition_events << endl;
  cout << "mode_shape_MakeAndStoreFits=" << mode_shape_MakeAndStoreFits << endl;
  
  configure(string_sample,string_observable,string_campaign_MxAOD);
  configure_bootstrap(index_start_toy,index_stop_toy);

  cout << "string_campaign_MxAOD=" << string_campaign_MxAOD << endl;

  bool found_tree=GetTreesShape(string_sample,string_category,string_campaign_MxAOD,string_systematic,&tree_nominal,&tree_syst); //needs index in order to make the RooDataSet::reduce
  
  cout << "found_tree=" << found_tree << endl;
  
  cout << "tree_nominal=" << tree_nominal << endl;
  //  tree_nominal->Print();
  //  exit(1);

  if (!found_tree) { //skip it if the systematic is not existing for this sample (for example one dedicated to an AF2 or to a full simulation)
    cout << "tree not found, continue with next syst" << endl;
    return 0;
  }
  
  if (string_method_partition_events=="individual") {
    cout << "approach classical" << endl;
    cout << "tree_nominal=" << tree_nominal << endl;
    cout << "tree_syst=" << tree_syst << endl;

    ComputeSystematicsShape(string_sample,string_category,string_campaign_MxAOD,string_systematic,-1,tree_nominal,tree_syst);
  }
  else if (string_method_partition_events=="bootstrap" || string_method_partition_events=="jacknife") {
    if (string_method_partition_events=="jacknife")
      nb_toys=10;
    
    nb_toys_done=0;

    cout << "nb_toys=" << nb_toys << endl;
    
    for (int index_toy=index_start_toy_bootstrap;index_toy<index_stop_toy_bootstrap;index_toy++) {
      
      cout << "index_toy=" << index_toy << ", index_start_toy_bootstrap=" << index_start_toy_bootstrap << ", index_stop_toy_bootstrap=" << index_stop_toy_bootstrap << endl;
      
      if (string_method_partition_events=="jacknife" || (string_method_partition_events=="bootstrap" &&  mode_shape_MakeAndStoreFits && index_toy>index_start_toy_bootstrap && index_toy<index_stop_toy_bootstrap)) {
	// 	for (int i=0;i<10;i++)
	// 	  cout << "================================================================" << endl;
	
	cout << "index_toy=" << index_toy << " / " << nb_toys << endl;
      }
      
      if (string_method_partition_events=="bootstrap" && mode_shape_MakeAndStoreFits) { //call the construction of bootstrap toys only for the first of the current block
	
	if (index_toy==index_start_toy_bootstrap) {
	  //there is no other choice than construct the nominal each time, because we open a new directory : this would be too much difficult else

	  /*shit
	    if (do_construct_bootstrap_nominal_once) {
	    if (string_input_file_systematic!=string_previous_input_file_systematic) { //no comparison to NotInitialized : for sure
	      cout << "construct bootstrap for nominal" << endl;
	      cout << "indeed, construct it" << endl;
	      ConstructTreeForBootStrap(string_category,string_campaign_MxAOD,string_systematic,"nominal",tree_nominal,&tree_nominal_bootstrap);
	    }
	    else {
	      cout << "no need to construct it" << endl;
	    }
	  }
	  else
	    ConstructTreeForBootStrap(string_category,string_campaign_MxAOD,string_systematic,"nominal",tree_nominal,&tree_nominal_bootstrap);
	  */

	  cout << "construct bootstrap for nominal" << endl;
	  ConstructTreeForBootStrap(string_category,string_campaign_MxAOD,string_systematic,"nominal",tree_nominal,&tree_nominal_bootstrap);
	  cout << "construct bootstrap for syst" << endl;
	  ConstructTreeForBootStrap(string_category,string_campaign_MxAOD,string_systematic,"syst",tree_syst,&tree_syst_bootstrap);
	}
      }
      
      if (string_method_partition_events=="jacknife" || (string_method_partition_events=="bootstrap" && mode_shape_MakeAndStoreFits)) {
	nb_toys_done++;

	cout << "so far, nb_toys_done=" << nb_toys_done << endl;
	
	if (string_method_partition_events=="jacknife") {
	  cout << "prepare for jacknive : to load the tree !" << endl;
	  exit(1);
	  ComputeSystematicsShape(string_sample,string_category,string_campaign_MxAOD,string_systematic,index_toy,tree_nominal,tree_syst);
	}
	
	else if (string_method_partition_events=="bootstrap" && mode_shape_MakeAndStoreFits) {
	 
	  LoadTreeBootStrap(string_category,string_campaign_MxAOD,string_systematic,"nominal");
	  LoadTreeBootStrap(string_category,string_campaign_MxAOD,string_systematic,"syst");

	  cout << "call ComputeSystematicsShape, for index_toy=" << index_toy << endl;

	  cout << "tree_nominal_bootstrap=" << tree_nominal_bootstrap << endl;
	  //	  tree_nominal_bootstrap->Print();

	  cout << "tree_nominal_syst=" << tree_syst_bootstrap << endl;
	  //	  tree_syst_bootstrap->Print();			

	  ComputeSystematicsShape(string_sample,string_category,string_campaign_MxAOD,string_systematic,index_toy,tree_nominal_bootstrap,tree_syst_bootstrap);
	  cout << "called ComputeSystematicsShape" << endl;
	}
	
	//careful : this is not exclusive to previous part
	if (string_method_partition_events=="bootstrap" && mode_shape_MakeAndStoreFits) {

	  if (index_toy==index_start_toy_bootstrap) { //release memory as soon as it is possible, in the case of bootstrap would no more be needed
	    //	    cout << "tree_nominal=" << tree_nominal << endl;
	    
	    if (!do_get_tree_nominal_once) {
	      cout << "before delete tree_nominal, tree_nominal=" << tree_nominal << endl;
	      delete tree_nominal; //why ?
	      tree_nominal=0; //ADDED Marc
	      cout << "after delete tree_nominal, tree_nominal=" << tree_nominal << endl;
	    }
	    
	    //	    cout << "tree_syst=" << tree_syst << endl;
	    //	    cout << "tree_syst->GetEntries()=" << tree_syst->GetEntries() << endl;

	    //	    cout << "tree_syst=" << tree_syst << endl;
	    delete tree_syst; //ADDED Marc
	    tree_syst=0;
	    
	    cout << "trees original freed" << endl;
	  }
	  else if (index_toy==index_stop_toy_bootstrap-1) { //release memory as soon as it is possible, in the case of bootstrap

	    /*shit
	    cout << "index_toy=" << index_toy << endl;
	    cout << "free the trees bootstrap" << endl;

	    delete tree_nominal_bootstrap;
	    tree_nominal_bootstrap=0; //ADDED Marc
	    cout << "deleted tree_nominal_bootstrap" << endl;

	    delete tree_syst_bootstrap;
	    tree_syst_bootstrap=0; //ADDED Marc

	    cout << "deleted tree_syst_bootstrap" << endl;
	    */

	    if (do_open_file_syst_once) {
	      if (string_input_file_systematic!=string_previous_input_file_systematic
		  &&
		  string_previous_input_file_systematic!="NotInitialized") {
		
		cout << "Close the file syst" << endl;
		file_syst->Close();
		
		cout << "Closed the file syst" << endl;
		delete file_syst;
		file_syst=0; //ADDED Marc
		cout << "deleted the file syst" << endl;
	      }
	    }
	    else {
	      cout << "Close the file syst" << endl;
	      file_syst->Close();
	      
	      cout << "Closed the file syst" << endl;
	      delete file_syst;
	      file_syst=0; //ADDED Marc
	      cout << "deleted the file syst" << endl;
	    }

	    /*shit
	    if (do_construct_bootstrap_nominal_once) {
	      cout << "string_MxAODSyst_directory=" << string_MxAODSyst_directory << endl;

	      if (string_input_file_systematic!=string_previous_input_file_systematic
		  &&
		  string_previous_input_file_systematic!="NotInitialized") {
		
		cout << "string_previous_input_file_systematic=" << string_previous_input_file_systematic << endl;
		
		cout << "close the file_nominal_bootstrap" << endl;
		file_nominal_bootstrap->Close();
		cout << "Closed the file nominal" << endl;
		delete file_nominal_bootstrap;
		file_nominal_bootstrap=0; //ADDED Marc
		cout << "deleted the file nominal bootstrap" << endl;
	      }
	    }
	    else {
	      cout << "close the file_nominal_bootstrap" << endl;
	      file_nominal_bootstrap->Close();
	      cout << "Closed the file nominal" << endl;
	      delete file_nominal_bootstrap;
	      file_nominal_bootstrap=0; //ADDED Marc
	      cout << "deleted the file nominal bootstrap" << endl;
	    }


	    file_syst_bootstrap->Close();
	    
	    cout << "delete file_syst_bootstrap" << endl;
	    
	    delete file_syst_bootstrap;
	    file_syst_bootstrap=0; //ADDED Marc
	    */
	  } //case last toy

	  //could be better by closing it only if we go to a new : to develop

	  //for sure, because bootstrap is written in a different directory
	  cout << "index_toy=" << index_toy << endl;
	  cout << "free the trees bootstrap" << endl;
	  
	  delete tree_nominal_bootstrap;
	  tree_nominal_bootstrap=0; //ADDED Marc
	  cout << "deleted tree_nominal_bootstrap" << endl;
	  
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
	  
	}
      } //end loop on restricted block of toys

      if (
	  (string_method_partition_events=="bootstrap" && mode_shape_MakeAndStoreFits)
	  ||
	  string_method_partition_events!="bootstrap"
	  ) {
	
	//		      cout << "fit status nominal=" << roofitresult_nominal->status() << endl;
	//		      cout << "fit status syst=" << roofitresult_syst->status() << endl;
	
	cout << "index_toy=" << index_toy << endl;

	vec_index_toy.push_back(index_toy);
	vec_result_rel_effect_position_shape.push_back(rel_effect_position_shape);
	vec_result_rel_effect_spread_shape.push_back(rel_effect_spread_shape);

	if (string_method_syst_shape=="fit") { //no consequence in term of speed, because loop is rather small (at most 10k events, else would be better to use a int for representing the flag)

	  if (
	      (shape_root1_roofit2==1 && (fitresult_nominal->IsValid()==0 || fitresult_syst->IsValid()==0))
	      ||
	      (shape_root1_roofit2==2 && ( (roofitresult_nominal!=0 && roofitresult_syst!=0 && (roofitresult_nominal->status()!=0 || roofitresult_syst->status()!=0)) || ParamAtLimit_nominal==1 || ParamAtLimit_syst==1))
	      ) {
	    vec_converged.push_back(0);
	    cout << "the fit has failed" << endl;
	  }
	  else
	    vec_converged.push_back(1);
	  
	  if (roofitresult_nominal!=0)
	    vec_status_nominal.push_back(roofitresult_nominal->status());
	  if (roofitresult_syst!=0)
	    vec_status_syst.push_back(roofitresult_syst->status());
	  
	  vec_chi2_nominal.push_back(chi2_nominal);
	  vec_chi2_syst.push_back(chi2_syst);
	  vec_ndof_nominal.push_back(ndof_nominal);
	  vec_ndof_syst.push_back(ndof_syst);

	  //advantage : independent of root/roofit
	  
	  if (string_functional_form=="DoubleCrystalBall") {
	    vec_muCB_nominal.push_back(muCB_nominal);
	    vec_err_muCB_nominal.push_back(err_muCB_nominal);
	    vec_sigmaCB_nominal.push_back(sigmaCB_nominal);
	    vec_err_sigmaCB_nominal.push_back(err_sigmaCB_nominal);
	    vec_alphaCB_Low_nominal.push_back(alphaCB_Low_nominal);
	    vec_err_alphaCB_Low_nominal.push_back(err_alphaCB_Low_nominal);
	    vec_nCB_Low_nominal.push_back(nCB_Low_nominal);
	    vec_err_nCB_Low_nominal.push_back(err_nCB_Low_nominal);
	    vec_alphaCB_High_nominal.push_back(alphaCB_High_nominal);
	    vec_err_alphaCB_High_nominal.push_back(err_alphaCB_High_nominal);
	    vec_nCB_High_nominal.push_back(nCB_High_nominal);
	    vec_err_nCB_High_nominal.push_back(err_nCB_High_nominal);
	    
	    vec_muCB_syst.push_back(muCB_syst);
	    vec_err_muCB_syst.push_back(err_muCB_syst);
	    vec_sigmaCB_syst.push_back(sigmaCB_syst);
	    vec_err_sigmaCB_syst.push_back(err_sigmaCB_syst);
	    vec_alphaCB_Low_syst.push_back(alphaCB_Low_syst);
	    vec_err_alphaCB_Low_syst.push_back(err_alphaCB_Low_syst);
	    vec_nCB_Low_syst.push_back(nCB_Low_syst);
	    vec_err_nCB_Low_syst.push_back(err_nCB_Low_syst);
	    vec_alphaCB_High_syst.push_back(alphaCB_High_syst);
	    vec_err_alphaCB_High_syst.push_back(err_alphaCB_High_syst);
	    vec_nCB_High_syst.push_back(nCB_High_syst);
	    vec_err_nCB_High_syst.push_back(err_nCB_High_syst);
	  }
	  else if (string_functional_form=="ExpGaussExp") {
	    vec_muGauss_nominal.push_back(muGauss_nominal);
	    vec_err_muGauss_nominal.push_back(err_muGauss_nominal);
	    vec_sigmaGauss_nominal.push_back(sigmaGauss_nominal);
	    vec_err_sigmaGauss_nominal.push_back(err_sigmaGauss_nominal);
	    vec_slopeExp_Low_nominal.push_back(slopeExp_Low_nominal);
	    vec_err_slopeExp_Low_nominal.push_back(err_slopeExp_Low_nominal);
	    vec_slopeExp_High_nominal.push_back(slopeExp_High_nominal);
	    vec_err_slopeExp_High_nominal.push_back(err_slopeExp_High_nominal);

	    vec_muGauss_syst.push_back(muGauss_syst);
	    vec_err_muGauss_syst.push_back(err_muGauss_syst);
	    vec_sigmaGauss_syst.push_back(sigmaGauss_syst);
	    vec_err_sigmaGauss_syst.push_back(err_sigmaGauss_syst);
	    vec_slopeExp_Low_syst.push_back(slopeExp_Low_syst);
	    vec_err_slopeExp_Low_syst.push_back(err_slopeExp_Low_syst);
	    vec_slopeExp_High_syst.push_back(slopeExp_High_syst);
	    vec_err_slopeExp_High_syst.push_back(err_slopeExp_High_syst);
	  }
	  else if (string_functional_form=="Bukin") {
	    vec_muBukin_nominal.push_back(muBukin_nominal);
	    vec_err_muBukin_nominal.push_back(err_muBukin_nominal);
	    vec_sigmaBukin_nominal.push_back(sigmaBukin_nominal);
	    vec_err_sigmaBukin_nominal.push_back(err_sigmaBukin_nominal);
	    vec_xiBukin_nominal.push_back(xiBukin_nominal);
	    vec_err_xiBukin_nominal.push_back(err_xiBukin_nominal);
	    vec_rho1Bukin_nominal.push_back(rho1Bukin_nominal);
	    vec_err_rho1Bukin_nominal.push_back(err_rho1Bukin_nominal);
	    vec_rho2Bukin_nominal.push_back(rho2Bukin_nominal);
	    vec_err_rho2Bukin_nominal.push_back(err_rho2Bukin_nominal);

	    vec_muBukin_syst.push_back(muBukin_syst);
	    vec_err_muBukin_syst.push_back(err_muBukin_syst);
	    vec_sigmaBukin_syst.push_back(sigmaBukin_syst);
	    vec_err_sigmaBukin_syst.push_back(err_sigmaBukin_syst);
	    vec_xiBukin_syst.push_back(xiBukin_syst);
	    vec_err_xiBukin_syst.push_back(err_xiBukin_syst);
	    vec_rho1Bukin_syst.push_back(rho1Bukin_syst);
	    vec_err_rho1Bukin_syst.push_back(err_rho1Bukin_syst);
	    vec_rho2Bukin_syst.push_back(rho2Bukin_syst);
	    vec_err_rho2Bukin_syst.push_back(err_rho2Bukin_syst);
	  }
	} //end information for fit
	else if (string_method_syst_shape=="mean_IQR") {
	  vec_mean_nominal.push_back(mean_nominal);
	  vec_err_mean_nominal.push_back(err_mean_nominal);
	  vec_mean_syst.push_back(mean_syst);
	  vec_err_mean_syst.push_back(err_mean_syst);
	  
	  vec_IQR_nominal.push_back(IQR_nominal);
	  vec_err_IQR_nominal.push_back(err_IQR_nominal);
	  vec_IQR_syst.push_back(IQR_syst);
	  vec_err_IQR_syst.push_back(err_IQR_syst);
	}
      } // end case fit converging
    } //end loop on toys

    if (string_method_partition_events!="bootstrap") {
      file_syst->Close();
      delete file_syst;
      file_syst=0; //ADDED Marc
    }
    
    cout << "with previous counter, nb_toys_done=" << nb_toys_done << endl;
    
    nb_toys_done=vec_result_rel_effect_position_shape.size();
    //    cout << "HERE, nb_toys_done=" << nb_toys_done << endl;
    //an option would be to store directly without moving to a vector
    
    //----------------------
    //store results from current range of toys

    if (string_method_partition_events=="bootstrap" && mode_shape_MakeAndStoreFits) {
      
      StoreResults(string_category,string_campaign_MxAOD,string_systematic);
      
      vec_index_toy.clear();
      vec_result_rel_effect_position_shape.clear();
      vec_result_rel_effect_spread_shape.clear();

      if (string_method_syst_shape=="mean_IQR") {
	vec_mean_nominal.clear();
	vec_err_mean_nominal.clear();
	vec_mean_syst.clear();
	vec_err_mean_syst.clear();

	vec_IQR_nominal.clear();
	vec_err_IQR_nominal.clear();
	vec_IQR_syst.clear();
	vec_err_IQR_syst.clear();
      }
      else {
	vec_converged.clear();
	
	vec_status_nominal.clear();
	vec_status_syst.clear();
	  
	vec_chi2_nominal.clear();
	vec_chi2_syst.clear();
	vec_ndof_nominal.clear();
	vec_ndof_syst.clear();
	  
	if (string_functional_form=="DoubleCrystalBall") {
	  vec_muCB_nominal.clear();
	  vec_err_muCB_nominal.clear();
	  vec_sigmaCB_nominal.clear();
	  vec_err_sigmaCB_nominal.clear();
	  vec_alphaCB_Low_nominal.clear();
	  vec_err_alphaCB_Low_nominal.clear();
	  vec_nCB_Low_nominal.clear();
	  vec_err_nCB_Low_nominal.clear();
	  vec_alphaCB_High_nominal.clear();
	  vec_err_alphaCB_High_nominal.clear();
	  vec_nCB_High_nominal.clear();
	  vec_err_nCB_High_nominal.clear();
	    
	  vec_muCB_syst.clear();
	  vec_err_muCB_syst.clear();
	  vec_sigmaCB_syst.clear();
	  vec_err_sigmaCB_syst.clear();
	  vec_alphaCB_Low_syst.clear();
	  vec_err_alphaCB_Low_syst.clear();
	  vec_nCB_Low_syst.clear();
	  vec_err_nCB_Low_syst.clear();
	  vec_alphaCB_High_syst.clear();
	  vec_err_alphaCB_High_syst.clear();
	  vec_nCB_High_syst.clear();
	  vec_err_nCB_High_syst.clear();
	}
	else if (string_functional_form=="ExpGaussExp") {
	  vec_muGauss_nominal.clear();
	  vec_err_muGauss_nominal.clear();
	  vec_sigmaGauss_nominal.clear();
	  vec_err_sigmaGauss_nominal.clear();
	  vec_slopeExp_Low_nominal.clear();
	  vec_err_slopeExp_Low_nominal.clear();
	  vec_slopeExp_High_nominal.clear();
	  vec_err_slopeExp_High_nominal.clear();

	  vec_muGauss_syst.clear();
	  vec_err_muGauss_syst.clear();
	  vec_sigmaGauss_syst.clear();
	  vec_err_sigmaGauss_syst.clear();
	  vec_slopeExp_Low_syst.clear();
	  vec_err_slopeExp_Low_syst.clear();
	  vec_slopeExp_High_syst.clear();
	  vec_err_slopeExp_High_syst.clear();
	}
	else if (string_functional_form=="Bukin") {
	  vec_muBukin_nominal.clear();
	  vec_err_muBukin_nominal.clear();
	  vec_sigmaBukin_nominal.clear();
	  vec_err_sigmaBukin_nominal.clear();
	  vec_xiBukin_nominal.clear();
	  vec_err_xiBukin_nominal.clear();
	  vec_rho1Bukin_nominal.clear();
	  vec_err_rho1Bukin_nominal.clear();
	  vec_rho2Bukin_nominal.clear();
	  vec_err_rho2Bukin_nominal.clear();
	  
	  vec_muBukin_syst.clear();
	  vec_err_muBukin_syst.clear();
	  vec_sigmaBukin_syst.clear();
	  vec_err_sigmaBukin_syst.clear();
	  vec_xiBukin_syst.clear();
	  vec_err_xiBukin_syst.clear();
	  vec_rho1Bukin_syst.clear();
	  vec_err_rho1Bukin_syst.clear();
	  vec_rho2Bukin_syst.clear();
	  vec_err_rho2Bukin_syst.clear();
	}
      }
    } //end mode MakeAndStoreFits

    //----------------------
    //to get the max for the jacknife!!
		
    if (string_method_partition_events=="bootstrap" && mode_shape_ReadFits_previously_made) {  

      //to replace here

      vec_index_toy.clear();
      vec_result_rel_effect_position_shape.clear();
      vec_result_rel_effect_spread_shape.clear();
      
      cout << "string_path=" << string_path << endl;
      cout << "string_rel_path_shape=" << string_rel_path_shape << endl;

      string string_results_toys=string_path;
      string_results_toys+=string_rel_path_shape;
      string_results_toys+="results_toys/";
      
      string_results_toys+=string_process;
      string_results_toys+="/";
      string_results_toys+=string_campaign_MxAOD;
      string_results_toys+="/";
      string_results_toys+=string_category;
      string_results_toys+="/";
      string_results_toys+=m_string_observable_shape;
      string_results_toys+="/";
      string_results_toys+=string_systematic;
      string_results_toys+="/";

      if (string_method_syst_shape=="fit")
	string_results_toys+="ShapeFrom_fit_";      
      else if (string_method_syst_shape=="mean_IQR")
	string_results_toys+="ShapeFrom_mean_IQR_";

      string_results_toys+=string_category;
      string_results_toys+="_";
      string_results_toys+=string_campaign_MxAOD;
      string_results_toys+="_";
      string_results_toys+=string_process;
      string_results_toys+="_";

      string_results_toys+=string_systematic;
      string_results_toys+=suffix_asymmetry_systematic;
      
      if (string_method_syst_shape=="fit")
	string_results_toys+="_range_toys_";
      
      string_results_toys+="*.root";

      //      string_results_toys+="AllToys.root";
      
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

      int converged;
      TBranch *b_converged;

      if (string_method_syst_shape=="fit")
	chain_results_toys->SetBranchAddress("converged",&converged,&b_converged);

      double internal_rel_effect_position_shape;
      TBranch *b_rel_effect_position_shape;
      chain_results_toys->SetBranchAddress("rel_effect_position_shape",&rel_effect_position_shape,&b_rel_effect_position_shape);
		    
      double internal_rel_effect_spread_shape;
      TBranch *b_rel_effect_spread_shape;
      chain_results_toys->SetBranchAddress("rel_effect_spread_shape",&rel_effect_spread_shape,&b_rel_effect_spread_shape);
		    
      int nb_entries=chain_results_toys->GetEntries();
		    
      cout << "nb_entries=" << nb_entries << endl;
      
      nb_toys_converged=0;
      nb_toys_done=0;
      
      for (int index_entry=0;index_entry<nb_entries;index_entry++) {

	Long64_t centry=chain_results_toys->LoadTree(index_entry); //mandatory to move from index_entry to centry with LoadTree, due to presence of several chains, else problem (else need to do Hadd, either in line command, or dynamically in the program
	if (centry<0)
	  continue;
	
	nb_toys_done++;

	if (string_method_syst_shape=="fit") {
	  b_converged->GetEntry(centry);
	  
	  if (!converged)
	    continue;
	  
	  nb_toys_converged++;
	}
	else
	  nb_toys_converged++;
	
	b_rel_effect_position_shape->GetEntry(centry);
	b_rel_effect_spread_shape->GetEntry(centry);
	
	b_index_toy->GetEntry(centry);
	
	vec_index_toy.push_back(index_toy);
	vec_result_rel_effect_position_shape.push_back(rel_effect_position_shape);
	vec_result_rel_effect_spread_shape.push_back(rel_effect_spread_shape);
	
	//	cout << "centry=" << centry << ", index_toy=" << index_toy << " / " << nb_entries << ", rel_effect_spread_shape=" << rel_effect_spread_shape << endl;
      } //end loop on entries

    } //end mode_shape_ReadFits_previously_made
    else
      nb_toys_converged=vec_result_rel_effect_position_shape.size();

    cout << "nb_toys_converged=" << nb_toys_converged << endl;
    cout << "nb_toys_done=" << nb_toys_done << endl;

    //stored : to make the clear here for sure
    vec_index_toy.clear();
    vec_result_rel_effect_position_shape.clear();
    vec_result_rel_effect_spread_shape.clear();    
    
    //dynamical range of the histogram
    
    if (string_method_partition_events=="jacknife" || mode_shape_ReadFits_previously_made) {

      double min_rel_effect_position_shape=99999;
      double max_rel_effect_position_shape=-99999;
      
      double min_rel_effect_spread_shape=99999;
      double max_rel_effect_spread_shape=-99999;
    
      double absolute_max_rel_effect_position_shape=-99999;
      double absolute_max_rel_effect_spread_shape=-99999;

      //--------------
      //search for max
      for (unsigned int index_toy=0;index_toy<nb_toys_converged;index_toy++) { //ok for sure
	
	rel_effect_position_shape=vec_result_rel_effect_position_shape[index_toy];
	rel_effect_spread_shape=vec_result_rel_effect_spread_shape[index_toy];

	//cout << "index_toy=" << index_toy << ", rel_effect_position_shape=" << rel_effect_position_shape << ", rel_effect_spread_shape=" << rel_effect_spread_shape << endl;
	
	if (rel_effect_position_shape<min_rel_effect_position_shape)
	  min_rel_effect_position_shape=rel_effect_position_shape;
	if (rel_effect_position_shape>max_rel_effect_position_shape)
	  max_rel_effect_position_shape=rel_effect_position_shape;

	if (rel_effect_spread_shape<min_rel_effect_spread_shape)
	  min_rel_effect_spread_shape=rel_effect_spread_shape;
	if (rel_effect_spread_shape>max_rel_effect_spread_shape)
	  max_rel_effect_spread_shape=rel_effect_spread_shape;
	
	if (fabs(rel_effect_position_shape)>absolute_max_rel_effect_position_shape)
	  absolute_max_rel_effect_position_shape=fabs(rel_effect_position_shape);
	
	if (fabs(rel_effect_spread_shape)>absolute_max_rel_effect_spread_shape)
	  absolute_max_rel_effect_spread_shape=fabs(rel_effect_spread_shape);
		      
      } //end loop on max

      cout << "summary of maximums before creating automatically the rounded range for illustration" << endl;
      cout << "min_rel_effect_position_shape=" << min_rel_effect_position_shape << endl;
      cout << "max_rel_effect_position_shape=" << max_rel_effect_position_shape << endl;
      cout << "min_rel_effect_spread_shape=" << min_rel_effect_spread_shape << endl;
      cout << "max_rel_effect_spread_shape=" << max_rel_effect_spread_shape << endl;
      //--------------
      int new_nb_bins_rel_effect_position_shape_visualization=20; //in case the effect is exactly 0, arbitrary choose a range of vizualization
      double rounded_min_rel_effect_position_shape=1;
      double rounded_max_rel_effect_position_shape=1;
      
      int new_nb_bins_rel_effect_spread_shape_visualization=20; //in case the effect is exactly 0, arbitrary choose a range of vizualization
      double rounded_min_rel_effect_spread_shape=0;
      double rounded_max_rel_effect_spread_shape=0;

      rounded_max_rel_effect_position_shape=ReturnRoundedExtremal(max_rel_effect_position_shape,"max");
      
      rounded_min_rel_effect_position_shape=ReturnRoundedExtremal(min_rel_effect_position_shape,"min");
      
      rounded_max_rel_effect_spread_shape=ReturnRoundedExtremal(max_rel_effect_spread_shape,"max");
      
      rounded_min_rel_effect_spread_shape=ReturnRoundedExtremal(min_rel_effect_spread_shape,"min");
      //------------------------------
      cout << "rounded range for spread" << endl;
      cout << "max_rel_effect_spread_shape=" << max_rel_effect_spread_shape << endl;
      cout << "rounded_max_rel_effect_spread_shape=" << rounded_max_rel_effect_spread_shape << endl;
      cout << "min_rel_effect_spread_shape=" << min_rel_effect_spread_shape << endl;
      cout << "rounded_min_rel_effect_spread_shape=" << rounded_min_rel_effect_spread_shape << endl;

      TH1D *hist_rel_effect_position_shape=new TH1D("hist_rel_effect_position_shape","hist_rel_effect_position_shape",new_nb_bins_rel_effect_position_shape_visualization,rounded_min_rel_effect_position_shape,rounded_max_rel_effect_position_shape);
      hist_rel_effect_position_shape->Sumw2(); //is this useful since SumW2 is already at beginnig of program ?
      hist_rel_effect_position_shape->SetLineColor(kBlack);
      
      TH1D *hist_rel_effect_spread_shape=new TH1D("hist_rel_effect_spread_shape","hist_rel_effect_spread_shape",new_nb_bins_rel_effect_spread_shape_visualization,rounded_min_rel_effect_spread_shape,rounded_max_rel_effect_spread_shape);
      hist_rel_effect_spread_shape->Sumw2(); //is this useful since SumW2 is already at beginnig of program ?
      hist_rel_effect_spread_shape->SetLineColor(kBlack);
      //------------------------------
      cout << "hist_rel_effect_position_shape->GetBinWidth(1)=" << hist_rel_effect_position_shape->GetBinWidth(1) << endl;
      cout << "hist_rel_effect_position_shape->GetBinLowEdge(1)=" << hist_rel_effect_position_shape->GetBinLowEdge(1) << endl;
      cout << "hist_rel_effect_position_shape->GetBinLowEdge(2)=" << hist_rel_effect_position_shape->GetBinLowEdge(2) << endl;
		    
      cout << "hist_rel_effect_spread_shape->GetBinWidth(1)=" << hist_rel_effect_spread_shape->GetBinWidth(1) << endl;
      cout << "hist_rel_effect_spread_shape->GetBinLowEdge(1)=" << hist_rel_effect_spread_shape->GetBinLowEdge(1) << endl;
      cout << "hist_rel_effect_spread_shape->GetBinLowEdge(2)=" << hist_rel_effect_spread_shape->GetBinLowEdge(2) << endl;
		    
      for (unsigned int index_toy=0;index_toy<nb_toys_converged;index_toy++) {
	hist_rel_effect_position_shape->Fill(vec_result_rel_effect_position_shape[index_toy]);
	hist_rel_effect_spread_shape->Fill(vec_result_rel_effect_spread_shape[index_toy]);
      }
		    
      vec_index_toy.clear();
      vec_result_rel_effect_position_shape.clear();
      vec_result_rel_effect_spread_shape.clear();
      //---
      rel_effect_position_shape=hist_rel_effect_position_shape->GetMean();
      err_rel_effect_position_shape=hist_rel_effect_position_shape->GetRMS();

      if (string_method_partition_events=="jacknife")
	err_rel_effect_position_shape/=sqrt(nb_toys_done); //even those that have failed
      //for bootstrap, no division by any function of the number of experiments, because the initial statistics is preserved
		    
      rel_effect_spread_shape=hist_rel_effect_spread_shape->GetMean();

      cout << "hist_rel_effect_spread_shape->GetMean()=" << hist_rel_effect_spread_shape->GetMean() << endl;

      err_rel_effect_spread_shape=hist_rel_effect_spread_shape->GetRMS();

      if (string_method_partition_events=="jacknife")
	err_rel_effect_spread_shape/=sqrt(nb_toys_done); //even those that have failed
      
      //---
      cout << "call Plot_pseudo_experiments for position" << endl;
		    
      Plot_pseudo_experiments(string_sample,string_category,string_campaign_MxAOD,string_systematic,index_sym_asym,"position_shape",hist_rel_effect_position_shape,rel_effect_position_shape,err_rel_effect_position_shape);
      
      cout << "call Plot_pseudo_experiments for spread" << endl;
		    
      Plot_pseudo_experiments(string_sample,string_category,string_campaign_MxAOD,string_systematic,index_sym_asym,"spread_shape",hist_rel_effect_spread_shape,rel_effect_spread_shape,err_rel_effect_spread_shape);
      //---
      delete hist_rel_effect_position_shape;
      delete hist_rel_effect_spread_shape;
      hist_rel_effect_position_shape=0; //ADDED Marc
      hist_rel_effect_spread_shape=0; //ADDED Marc
    }
  } //end jacknife or bootstrap

  cout << "summary of the partition" << endl;
  cout << "rel_effect_position_shape=" << rel_effect_position_shape << " +/- " << err_rel_effect_position_shape << endl;
  cout << "rel_effect_spread_shape=" << rel_effect_spread_shape << " +/- " << err_rel_effect_spread_shape << endl;

  //		  tree_nominal->SetDirectory(0);
    
  //    if (file_syst)
  //    file_syst->Close();

  /*
  if (do_read_tree_nominal_shape_once) {
    string string_MxAODSyst_directory=ReturnMxAODSyst_directory(string_systematic);
    
    if (string_MxAODSyst_directory!=string_previous_MxAODSys_directory) {
      string_previous_MxAODSys_directory=string_MxAODSyst_directory;
    }
  }
  */

  if (do_construct_bootstrap_nominal_once) {
    if (string_input_file_systematic!=string_previous_input_file_systematic)
      string_previous_input_file_systematic=string_input_file_systematic;
  }
  
  return 1; //return success
}

//SO FAR SO FAR SO FAR

//option for much later : to separate nominal and syst : need to close two different files
//=============================================================================================================================================================================================
void tool_syst_shape::configure(string string_sample,string string_observable_shape,string string_campaign_MxAOD)
{
  int size_string_campaign_MxAOD=string_campaign_MxAOD.size();
  
  //  cout << "string_campaign_MxAOD=" << string_campaign_MxAOD << endl;
  //  cout << "size_string_campaign_MxAOD=" << size_string_campaign_MxAOD << endl;

  string_process=string_sample.substr(size_string_campaign_MxAOD+1); //h0xx_mc16x_, or h0xx_mc16x_h0xx_mc16x, etc. : transparent with multiple parts
  cout << "string_process=" << string_process << endl;

  m_string_observable_shape=string_observable_shape;
  if (m_string_observable_shape=="m_yy")
    string_latex_observable_shape_no_units="m_{#gamma#gamma}";
  else if (m_string_observable_shape=="m_bb")
    string_latex_observable_shape_no_units="m_{bb}";
  else if (m_string_observable_shape=="m_yybb_tilde")
    string_latex_observable_shape_no_units="#tilde{m}_{#gamma#gammabb}";

  string_latex_observable_shape_units="[GeV]";

  cout << "string_sample=" << string_sample << endl;
  //  exit(1);

  if (
      string_sample.find("HH_non_resonant_kappa_lambda_01")!=string::npos
      ||
      string_sample.find("HH_non_resonant_kappa_lambda_10")!=string::npos
      ||
      string_sample.find("PowhegH7_HHbbyy_cHHH01d0")!=string::npos
      ||
      string_sample.find("aMCnloHwpp_hh_yybb")!=string::npos
      ||
      string_sample.find("aMCnloHwpp_hh_yybb_AF2")!=string::npos
      ||
      string_sample.find("MGH7_hh_bbyy_vbf_l1cvv1cv1")!=string::npos
      ||
      string_sample.find("NonResonantPlusSingle")!=string::npos
      ||
      string_sample.find("SingleHiggs")!=string::npos
      || 
      string_sample.find("PowhegPy8_NNLOPS_ggH125")!=string::npos
      || 
      string_sample.find("ggH125")!=string::npos
      || 
      string_sample.find("ZH125")!=string::npos
      ||
      string_sample.find("PowhegPy8_ZH125J")!=string::npos
      ||
      //shit      string_sample.find("PowhegPy8_ttH125")!=string::npos ) {
      string_sample.find("ttH125")!=string::npos ) {
    mass_yy_resonance=125;
    mass_bb_resonance=125;
    mass_bbyy_resonance=400; //for HH
  }
  else if (string_sample.find("PowhegH7_HHbbyy_cHHH10d0")!=string::npos) {
    mass_yy_resonance=125;
    mass_bb_resonance=125;
    mass_bbyy_resonance=270; //for HH
  }
  else if (string_sample.find("MGH7_X")!=string::npos) {
    mass_yy_resonance=125;
    mass_bb_resonance=125;
    
    if (string_sample.find("MGH7_X300tohh_bbyy")!=string::npos)
      mass_bbyy_resonance=300;
  }
  else {
    cout << "not yet implemented, halt program" << endl;
    exit(1);
  }
  
  return;
}
//=============================================================================================================================================================================================
void tool_syst_shape::configure_bootstrap(int index_start_toy,int index_stop_toy)
{
  index_start_toy_bootstrap=index_start_toy;
  index_stop_toy_bootstrap=index_stop_toy;
}

//later : maybe split in two, camm for nominal, then systematic ? Not sure

//why do we need to search : isn't it direct bijection ?

//=============================================================================================================================================================================================
bool tool_syst_shape::GetTreesShape(string string_sample,string string_category,string string_campaign_MxAOD,string string_systematic,TTree **pptr_tree_nominal,TTree **pptr_tree_syst)
{
  cout << "starts GetTreesShape" << endl;

  //search for string process, that is used for the unix command
  
  //  cout << "current_sample=" << string_sample << endl;

  //a block has been moved at the very bottom of code, just in case for very later, if it would be neede
  
  /*
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
  */

  /*
  cout << "string_file_syst_shape_candidates=" << string_file_syst_shape_candidates << endl;

  //     if (tree_original_nominal) {
  //     cout << "tree_original_nominal exists" << endl;
  //     cout << "tree_original_nominal->GetEntries()=" << tree_original_nominal->GetEntries() << endl;
  //     }

  string_input_file_systematic=string_file_syst_shape_candidates;

  if (do_open_file_syst_once) {
    if (string_input_file_systematic!=string_previous_input_file_systematic) //no comparison to NotInitialized : for sure
      file_syst=new TFile(string_input_file_systematic.c_str(),"read");
  }
  else
    file_syst=new TFile(string_input_file_systematic.c_str(),"read"); //historical
    //    file_syst=new TFile(string_file_syst_shape_candidates.c_str(),"read"); //historical

  //file_syst=TFile::Open(string_input_file_systematic.c_str(),"read");
  //  file_syst->ls();
  
  //     if (tree_original_nominal) {
  //     cout << "tree_original_nominal exists" << endl;
  //     cout << "tree_original_nominal->GetEntries()=" << tree_original_nominal->GetEntries() << endl;
  //     }



*/




  //================================
  //DEVELOP
  string string_directory_MxAOD=ReturnMxAODSyst_directory(string_systematic);

  
  string string_input_file_systematic=string_path;
  string_input_file_systematic+=string_rel_path_yield;
  
  string_input_file_systematic+="trees_and_hist/";
  string_input_file_systematic+=string_directory_MxAOD;
  string_input_file_systematic+="/";
  
  string_input_file_systematic+=string_campaign_MxAOD;
  string_input_file_systematic+="_";
  
  int size_string_campaign_MxAOD=string_campaign_MxAOD.size();
  string string_process=string_sample.substr(size_string_campaign_MxAOD+1); //h0xx_mc16x_, or h0xx_mc16x_h0xx_mc16x, etc. : transparent with multiple parts
  
  string_input_file_systematic+=string_process;
  string_input_file_systematic+="_";
  
  if (found_theory) {
    if (string_sample.find("HH")!=string::npos
	||
	string_sample.find("MGH7")!=string::npos
	)
      string_input_file_systematic+="nominal";
    else
      string_input_file_systematic+="PhotonSys";
  }
  else {
    string_input_file_systematic+=string_directory_MxAOD;
  }
  
  cout << "index_sym_asym=" << index_sym_asym << ", vec_nature_syst_components_sym_asym[index_sym_asym]=" << vec_nature_syst_components_sym_asym[index_sym_asym] << endl;
  
  string_input_file_systematic+=".root";
  
  cout << "string_input_file_systematic=" << string_input_file_systematic << endl;
  
  //alternative if (!file_syst exist OR !file_syst->IsOpen with TFile::Openstuff
  
  file_syst=new TFile(string_input_file_systematic.c_str(),"read");
  
  if (do_open_file_syst_once) {
    if (string_input_file_systematic!=string_previous_input_file_systematic) //no comparison to NotInitialized : for sure
      file_syst=new TFile(string_input_file_systematic.c_str(),"read");
  }
  else
    file_syst=new TFile(string_input_file_systematic.c_str(),"read"); //historical
  
  //file_syst=TFile::Open(string_input_file_systematic.c_str(),"read");
  //  file_syst->ls();
  
  if (!file_syst) {
    if (vec_nature_syst_components_sym_asym[index_sym_asym]=="")
      file_or_tree_exists_sym=0;
    else if (vec_nature_syst_components_sym_asym[index_sym_asym]=="__1up")
      file_or_tree_exists_up=0;
    else if (vec_nature_syst_components_sym_asym[index_sym_asym]=="__1down")
      file_or_tree_exists_down=0;

    cout << "not found_file_syst_shape_candidates, return to caller" << endl;

    return 0;
  }
  
  //  cout << "show the list" << endl;
  //  file_syst->ls();
  //================================
  //  cout << "done_fit_shape_nominal=" << done_fit_shape_nominal << endl;

  string string_tree_nominal="tree_sel_nominal_";
  string_tree_nominal+=string_category;
  
  if (do_get_tree_nominal_once) {
    if (string_input_file_systematic!=string_previous_input_file_systematic) //no comparison to NotInitialized : for sure

      if (string_previous_input_file_systematic!="NotInitialized") {
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
//=============================================================================================================================================================================================
//or classical with rescaling

void tool_syst_shape::ConstructTreeForBootStrap(string string_category,string string_campaign_MxAOD,string string_systematic,string string_nominal_syst,TTree *tree_original,TTree **pptr_tree_bootstrap)
{
  cout << "in ConstructTreeForBootStrap, phase 1" << endl;

  //mandatory to have a duplicate, in order to have authorization to add many variables (else error messages Error in <TBranch::TBranch::WriteBasketImpl>: basket's WriteBuffer failed.
  //------------
  //these will be parameters of the caller
  
  TRandom3 rand3;

  char affix_range_toys[24]; //ok for sure, with 5 digits, + 1 for \0
  
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
  string_file_bootstrap+=m_string_observable_shape;
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

  //to make a pointer on the pointer ?
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
  
  if (do_weight_event)
    (*pptr_tree_bootstrap)->SetBranchAddress("weight_event",&weight_total,&b_weight_total);
  else
    (*pptr_tree_bootstrap)->SetBranchAddress("weight_total",&weight_total,&b_weight_total);

  //DO NOT ADD +1 : because finished at nb_toys-1
  
  double *tab_weight_total_temp_bootstrap=0;
  TBranch **tab_b_weight_total_temp_bootstrap=0;
  
  if (rescale_to_real_stat) { //rescale
    tab_weight_total_temp_bootstrap=(double *)malloc((index_stop_toy_bootstrap-index_start_toy_bootstrap)*sizeof(double));
    tab_b_weight_total_temp_bootstrap=(TBranch **)malloc((index_stop_toy_bootstrap-index_start_toy_bootstrap)*sizeof(TBranch *));
  }

  cout << "index_stop_toy_bootstrap-index_start_toy_bootstrap=" << index_stop_toy_bootstrap-index_start_toy_bootstrap << endl;

  double *tab_weight_total_bootstrap=(double *)malloc((index_stop_toy_bootstrap-index_start_toy_bootstrap)*sizeof(double));
  TBranch **tab_b_weight_total_bootstrap=(TBranch **)malloc((index_stop_toy_bootstrap-index_start_toy_bootstrap)*sizeof(TBranch *));
  
  //unsigned long not considered by root 6.18.00
  int *tab_seed_bootstrap=(int *)malloc((index_stop_toy_bootstrap-index_start_toy_bootstrap)*sizeof(int));
  TBranch **tab_b_seed_bootstrap=(TBranch **)malloc((index_stop_toy_bootstrap-index_start_toy_bootstrap)*sizeof(TBranch *));

  char buffer_weight_total_temp_bootstrap_current_toy[38]; //ok for sure : for 5 digits in the index toy
  char buffer_weight_total_temp_bootstrap_current_toy_with_type[40]; //ok for sure for 5 digits in the index toy
  
  char buffer_weight_total_bootstrap_current_toy[33]; //ok for sure : for 5 digits in the index toy
  char buffer_weight_total_bootstrap_current_toy_with_type[35]; //ok for sure : for 5 digits in the index toy

  
  char buffer_seed_current_toy[15]; //ok for sure : for 5 digits in the index_toy
  char buffer_seed_current_toy_with_type[17]; //ok for sure : for 5 digits in the index_toy
  
  //------------
  for (int index_toy=0;index_toy<nb_toys;index_toy++) { //ok for sure

    if (rescale_to_real_stat) {
      sprintf(buffer_weight_total_temp_bootstrap_current_toy,"weight_total_temp_bootstrap_toy_%d",index_toy);
      sprintf(buffer_weight_total_temp_bootstrap_current_toy_with_type,"weight_total_temp_bootstrap_toy_%d/D",index_toy);
      tab_b_weight_total_temp_bootstrap[index_toy]=(*pptr_tree_bootstrap)->Branch(buffer_weight_total_temp_bootstrap_current_toy,&(tab_weight_total_temp_bootstrap[index_toy]),buffer_weight_total_temp_bootstrap_current_toy_with_type);
    }
    
    sprintf(buffer_weight_total_bootstrap_current_toy,"weight_total_bootstrap_toy_%d",index_toy);
    sprintf(buffer_weight_total_bootstrap_current_toy_with_type,"weight_total_bootstrap_toy_%d/D",index_toy);
    tab_b_weight_total_bootstrap[index_toy]=(*pptr_tree_bootstrap)->Branch(buffer_weight_total_bootstrap_current_toy,&(tab_weight_total_bootstrap[index_toy]),buffer_weight_total_bootstrap_current_toy_with_type);
    
    sprintf(buffer_seed_current_toy,"seed_toy_%d",index_toy);
    sprintf(buffer_seed_current_toy_with_type,"seed_toy_%d/I",index_toy);
    tab_b_seed_bootstrap[index_toy]=(*pptr_tree_bootstrap)->Branch(buffer_seed_current_toy,&(tab_seed_bootstrap[index_toy]),buffer_seed_current_toy_with_type);
    
  } //end loop on toys
  
  //to make a function, in order to factorize nominal and syst.
  
  //====================================================================
  double *tab_SumWeight=0;

  if (rescale_to_real_stat) { //rescale
    tab_SumWeight=(double *)malloc((index_stop_toy_bootstrap-index_start_toy_bootstrap)*sizeof(double));

    for (int index_toy=0;index_toy<nb_toys;index_toy++)
      tab_SumWeight[index_toy]=0;
  }
  //====================================================================
  
  //remark : for the seed, the value stored is not the correct one : bug of TRandom3, but no consequence
  //https://sft.its.cern.ch/jira/browse/ROOT-10059

  for (int index_entry=0;index_entry<nb_entries;index_entry++) {
    b_eventNumber->GetEntry(index_entry);
    b_weight_total->GetEntry(index_entry);
    
    for (int index_toy=0;index_toy<nb_toys;index_toy++) {

      int index_absolute_toy=index_toy+index_start_toy_bootstrap;

      unsigned long seed=1+10000*eventNumber+index_absolute_toy; //up to 10000 toys
      
      rand3.SetSeed(seed); //typically up to 1000

      int weight_Poisson=rand3.Poisson(1.);
      
      tab_seed_bootstrap[index_toy]=seed;
      tab_b_seed_bootstrap[index_toy]->Fill();

      if (rescale_to_real_stat) {
	tab_weight_total_temp_bootstrap[index_toy]=weight_total*weight_Poisson;
	tab_b_weight_total_temp_bootstrap[index_toy]->Fill(); //this fills also the other variables
	
	tab_SumWeight[index_toy]+=tab_weight_total_temp_bootstrap[index_toy];
      }
      else {
	tab_weight_total_bootstrap[index_toy]=weight_total*weight_Poisson;
	tab_b_weight_total_bootstrap[index_toy]->Fill();
      }
      
      //	  cout << "index_entry=" << index_entry << ", weight_Poisson=" << weight_Poisson << ", weight_total=" << weight_total << ", tab_weight_total_bootstrap[" << index_toy << "]=" << tab_weight_total_bootstrap[index_toy] << endl;
    }
    
  } //end loop on tree
  
  if (rescale_to_real_stat) { //rescale
    for (int index_entry=0;index_entry<nb_entries;index_entry++) {

      for (int index_toy=0;index_toy<nb_toys;index_toy++) {      
	tab_b_weight_total_temp_bootstrap[index_toy]->GetEntry(index_entry);
	
	tab_weight_total_bootstrap[index_toy]=tab_weight_total_temp_bootstrap[index_toy]*nb_entries/tab_SumWeight[index_toy];
	tab_b_weight_total_bootstrap[index_toy]->Fill(); //this fills also the other variables
      }
      
    } //end loop on tree nominal
  } //end case rescale
  
  
  (*pptr_tree_bootstrap)->Write();
  
  //   cout << "total_real_time=" << total_real_time << endl;
  
  //  (*pptr_tree_bootstrap)->Print();
  //  (*pptr_tree_bootstrap)->Scan("weight_total:weight_total_temp_bootstrap_toy_0:weight_total_bootstrap_toy_0");

  // cout << "file_syst->ls(), phase 1" << endl;
  // file_syst->ls();

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

  cout << "free(tab_weight_total_bootstrap);" << endl;
  free(tab_weight_total_bootstrap);
  cout << "free(tab_b_weight_total_bootstrap);" << endl;
  free(tab_b_weight_total_bootstrap);
  
  cout << "free(tab_seed_bootstrap);" << endl;
  free(tab_seed_bootstrap);
  cout << "free(tab_b_seed_bootstrap);" << endl;
  free(tab_b_seed_bootstrap);

  if (rescale_to_real_stat) { //rescale
    free(tab_weight_total_temp_bootstrap);
    free(tab_b_weight_total_temp_bootstrap);

    free(tab_SumWeight);
  }
  
}
//=============================================================================================================================================================================================
//=============================================================================================================================================================================================
void tool_syst_shape::ComputeSystematicsShape(string string_sample,string string_category,string string_campaign_MxAOD,string string_systematic,int index_toy,TTree *current_tree_nominal,TTree *current_tree_syst)
{
  cout << "==========================================" << endl;
  cout << "in ComputeSystematicsShape for string_systematic=" << string_systematic << ", index_toy=" << index_toy << endl;

  cout << "current_tree_nominal=" << current_tree_nominal << endl;
  cout << "current_tree_syst=" << current_tree_syst << endl;

  if (current_tree_nominal && current_tree_syst) {
    if (vec_nature_syst_components_sym_asym[index_sym_asym]=="") {
      //      found_trees_syst_sym_shape_candidate=1;
      file_or_tree_exists_sym=1;
    }
    else if (vec_nature_syst_components_sym_asym[index_sym_asym]=="__1up") {
      //found_trees_syst_up_shape_candidate=1;
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
  
  //  cout << "current_tree_nominal->GetEntries()=" << current_tree_nominal->GetEntries() << endl;
  //  cout << "current_tree_syst->GetEntries()=" << current_tree_syst->GetEntries() << endl;

  //to factorize mass_yy and mass_bb

  //it should be a function of sample and observable!!!

  //do not merge with above, in order to have high flexibility
  
  if (
      string_sample.find("HH_non_resonant_kappa_lambda_01")!=string::npos
      ||
      string_sample.find("HH_non_resonant_kappa_lambda_10")!=string::npos
      ||
      string_sample.find("PowhegH7_HHbbyy_cHHH01d0")!=string::npos
      ||
      string_sample.find("PowhegH7_HHbbyy_cHHH10d0")!=string::npos
      ||
      string_sample.find("aMCnloHwpp_hh_yybb")!=string::npos
      ||
      string_sample.find("aMCnloHwpp_hh_yybb_AF2")!=string::npos
      ||
      string_sample.find("MGH7_hh_bbyy_vbf_l1cvv1cv1")!=string::npos
      ||
      string_sample.find("NonResonantPlusSingle")!=string::npos
      ||
      string_sample.find("SingleHiggs")!=string::npos
      ||
      string_sample.find("PowhegPy8_NNLOPS_ggH125")!=string::npos
      ||
      string_sample.find("ZH125")!=string::npos
      ||
      string_sample.find("PowhegPy8_ZH125J")!=string::npos
      ||
      //shit      string_sample.find("PowhegPy8_ttH125")!=string::npos ) {
      string_sample.find("ttH125")!=string::npos ) {
    if (m_string_observable_shape=="m_yy") {
      string_functional_form="DoubleCrystalBall";
      mass_resonance=mass_yy_resonance;
    }
    else if (m_string_observable_shape=="m_bb") {
      string_functional_form="Bukin";
      //string_functional_form="DoubleCrystalBall";
      mass_resonance=mass_bb_resonance;
    }
    else if (m_string_observable_shape=="m_yybb_tilde") {
      string_functional_form="Bukin";
      //string_functional_form="DoubleCrystalBall";
      mass_resonance=mass_bbyy_resonance;
      cout << "mass_resonance=" << mass_resonance << endl;
    }
    else {
      cout << "A case of modelization not anticipated" << endl;
      exit(1);
    }
    
    mass_resonance_finalDV=mass_resonance;
  }
  else if (string_sample.find("MGH7_X")!=string::npos) {
    mass_resonance=mass_bbyy_resonance;
    
    if (m_string_observable_shape=="m_yy") {
      string_functional_form="DoubleCrystalBall";
      mass_resonance_finalDV=125;
    }
    else if (m_string_observable_shape=="m_bb") {
      string_functional_form="DoubleCrystalBall";
      mass_resonance_finalDV=125;
    }
    else if (m_string_observable_shape=="m_yybb_tilde") {
      string_functional_form="ExpGaussExp";
      mass_resonance_finalDV=mass_bbyy_resonance;
    }
    else {
      cout << "B case of modelization not anticipated" << endl;
      exit(1);
    }
  }
  else {
    cout << "problem, mass resonance unknown" << endl;
    exit(1);
  }
  
  //used in all cases in order to obtain initial values, as initial values for the fit
  
  //not used float bin_width_histogram_shape=0.5;
  
  //TO DEVELOP EXTENSION ASYMMETRIC

  //to develop extension asymmetric

  cout << "mass_resonance=" << mass_resonance << endl;

  //to state : non resonant or resonant and m_yy or m_bb

  if (BelongToKnownSample(string_sample)) {
    if (m_string_observable_shape=="m_yy") {
      extension_low_histogram_shape=13; //bin width : 0.5 GeV
      extension_high_histogram_shape=13; //bin width : 0.5 GeV
      nb_bins_histogram_shape=52;
    }
    else if (m_string_observable_shape=="m_bb") {
      extension_low_histogram_shape=45; //bin width : 5 GeV
      extension_high_histogram_shape=45; //bin width : 5 GeV
      nb_bins_histogram_shape=18;
    }
    else if (m_string_observable_shape=="m_yybb_tilde") {
      if (string_sample.find("PowhegH7_HHbbyy_cHHH10d0")!=string::npos) {
	//extension_low_histogram_shape=20;
	extension_low_histogram_shape=10;
	extension_high_histogram_shape=400;
	//extension_high_histogram_shape=130;
	nb_bins_histogram_shape=41;
      }
      else {
	extension_low_histogram_shape=150; //bin width : 0.5 GeV
	extension_high_histogram_shape=400; //bin width : 0.5 GeV
	nb_bins_histogram_shape=55;
      }
    }
  }
  else {
    cout << "case sample not anticipated" << endl;
    cout << "stop program" << endl;
    exit(1);
  }
  
  /*
//to see signal model

  //case using m_gamgam or m_bb: Non-Resonant or Resonant-2D
  if (mass_resonance==125
      ||
      (mass_resonance!=125 && m_string_observable_shape!="m_yybb_tilde")
      ) {

  }
  //-------------------------
  //Resonant samples
  
  else if (mass_resonance==350) {
    if (m_string_observable_shape=="m_yybb_tilde") {
      extension_low_histogram_shape=50;
      extension_high_histogram_shape=20;
      nb_bins_histogram_shape=70;
    }
  }
  else if (mass_resonance==500) {
    if (m_string_observable_shape=="m_yybb_tilde") {
      extension_low_histogram_shape=60;
      extension_high_histogram_shape=30;
      nb_bins_histogram_shape=80;
    }
  }
  else if (mass_resonance==1000) {
    if (m_string_observable_shape=="m_yybb_tilde") {
      extension_low_histogram_shape=200;
      extension_high_histogram_shape=100;
      nb_bins_histogram_shape=150;
    }
  }
  else {
    cout << "STOP program" << endl;
    exit(1);
  }
  */

  /*
  else if (mass_resonance==260) {
    if (m_string_observable_shape=="m_yybb_tilde") {
      extension_unilateral_histogram_shape=30;
      nb_bins_histogram_shape=30;
    }
  }
  else if (mass_resonance==280) {
    if (m_string_observable_shape=="m_yybb_tilde") {
      extension_unilateral_histogram_shape=30;  //bin width : 2 GeV
      nb_bins_histogram_shape=30;
      //nb_bins_histogram_shape=60;
      //nb_bins_histogram_shape=300;
    }
  }
  else if (mass_resonance==500) {
    if (m_string_observable_shape=="m_yybb_tilde") {
      extension_unilateral_histogram_shape=90;
      nb_bins_histogram_shape=90;
      //nb_bins_histogram_shape=36;
    }
  }
  else if (mass_resonance==750) {
    if (m_string_observable_shape=="m_yybb_tilde") {
      extension_unilateral_histogram_shape=150;
      nb_bins_histogram_shape=150;
    }
  }
  else if (mass_resonance==1000) {
    if (m_string_observable_shape=="m_yybb_tilde") {
      extension_unilateral_histogram_shape=200;
      nb_bins_histogram_shape=80;
    }
  }
  
  else
  extension_unilateral_histogram_shape=20;
  */	  

  //  cout << "allocate hist_nominal, for index_toy=" << index_toy << endl;
  
  hist_nominal=new TH1D("hist_nominal","hist_nominal",nb_bins_histogram_shape,mass_resonance_finalDV-extension_low_histogram_shape,mass_resonance_finalDV+extension_high_histogram_shape);
  hist_nominal->SetLineColor(kGreen+2);
  hist_nominal->SetMarkerColor(kGreen+2);
  hist_nominal->SetMarkerStyle(20);
  hist_nominal->SetMarkerSize(1.0);
    /*
  }
  else {
    cout << "no need to allocate again the histogram nominal" << endl;
  }
    */

  //  cout << "phase 1" << endl;

  //   cout << "nb_bins_histogram_shape=" << nb_bins_histogram_shape << endl;
  //   cout << "mass_resonance_finalDV-extension_low_histogram_shape=" << mass_resonance_finalDV-extension_low_histogram_shape << endl;
  //   cout << "mass_resonance_finalDV+extension_high_histogram_shape=" << mass_resonance_finalDV+extension_high_histogram_shape << endl;
  

  
  if (string_systematic!="showering" && current_tree_syst) {
    hist_syst=new TH1D("hist_syst","hist_syst",nb_bins_histogram_shape,mass_resonance_finalDV-extension_low_histogram_shape,mass_resonance_finalDV+extension_high_histogram_shape);
    hist_syst->SetLineColor(kBlue+2);
    hist_syst->SetMarkerColor(kBlue+2);
    hist_syst->SetMarkerStyle(20);
    hist_syst->SetMarkerSize(1.0);
  }

  char buffer_weight[32];

  if (string_method_partition_events=="individual") {
    //to prevent problem of wrong error : rescale
    //    sprintf(buffer_weight,"weight_total_bootstrap_toy_%d",0);
    
    if (do_weight_event)
      sprintf(buffer_weight,"weight_event");
    else
      sprintf(buffer_weight,"weight_total");
    
  }
  else if (string_method_partition_events=="bootstrap")
    sprintf(buffer_weight,"weight_total_bootstrap_toy_%d",index_toy);
  
  cout << "buffer_weight=" << buffer_weight << endl;

  //special code size take only one character
  
  //to revisit the size here: it should really be 19 : to check with the print out
  
  char buffer_modulo_selection[19]; // up to 2 digits for each number <=> 20 characters, including the '`0'
  
  if (string_method_partition_events=="jacknife") {
    sprintf(buffer_modulo_selection," eventNumber\%%%d==%d",nb_toys,index_toy);
    cout << "buffer_modulo_selection=" << buffer_modulo_selection << endl;
    
    cout << "studying index_toy=" << index_toy << endl;
  }
  else
    sprintf(buffer_modulo_selection,""); //useful for later
  
  string_project=buffer_weight;
  if (string_method_partition_events=="jacknife") {
    string_project+="*(";
    string_project+=buffer_modulo_selection;
    string_project+=")";
  }

  cout << "current_tree_nominal=" << current_tree_nominal << endl;
  current_tree_nominal->ls();

  cout << "call now the projection of tree nominal" << endl;
  cout << "string_project=" << string_project << endl;

  if (current_tree_nominal)
    current_tree_nominal->Project("hist_nominal",m_string_observable_shape.c_str(),string_project.c_str());
  
  //  current_tree_nominal->Print();
  cout << "m_string_observable_shape=" << m_string_observable_shape << endl;
  cout << "string_project=" << string_project << endl;

  cout << "m_string_observable_shape=" << m_string_observable_shape << endl;
  //  cout << "hist_nominal->GetEntries()=" << hist_nominal->GetEntries() << endl;

  cout << "call now the projection of tree syst" << endl;
  
  if (string_systematic!="showering" && current_tree_syst) {
    current_tree_syst->Project("hist_syst",m_string_observable_shape.c_str(),string_project.c_str());
    //    cout << "hist_syst->GetEntries()=" << hist_syst->GetEntries() << endl;
  }

  //  cout << "Projection made" << endl;

  //useful for chi2 and for some draw
  
  //to improve
  double hist_nominal_max=hist_nominal->GetMaximum();
  double hist_nominal_mean=hist_nominal->GetMean();
  double hist_nominal_position_max=hist_nominal->GetBinCenter(hist_nominal->GetMaximumBin());
  double hist_nominal_sigma=hist_nominal->GetRMS();
  //variante from FWHM : less stable ; double hist_nominal_sigma=(hist_nominal->GetBinCenter(hist_nominal->FindLastBinAbove(0.5*hist_nominal_max))-hist_nominal->GetBinCenter(hist_nominal->FindFirstBinAbove(0.5*hist_nominal_max)))/2.355;
  
  double hist_nominal_integral=hist_nominal->Integral();

  double hist_syst_max=0;
  double hist_syst_sigma=0;
  double hist_syst_mean=0;
  double hist_syst_position_max=0;

  double hist_syst_integral=0;

  if (string_systematic!="showering" && current_tree_syst) {
    hist_syst_max=hist_syst->GetMaximum();
    hist_syst_mean=hist_syst->GetMean();
    hist_syst_position_max=hist_nominal->GetBinCenter(hist_nominal->GetMaximumBin());
    hist_syst_sigma=hist_syst->GetRMS();

    //hist_syst_sigma=(hist_syst->GetBinCenter(hist_syst->FindLastBinAbove(0.5*hist_syst_max))-hist_syst->GetBinCenter(hist_syst->FindFirstBinAbove(0.5*hist_syst_max)))/2.355;
    cout << "hist_syst_mean=" << hist_syst_mean << endl;
    cout << "hist_syst_sigma=" << hist_syst_sigma << endl;
    hist_syst_integral=hist_syst->Integral();
  }

  //   cout << "hist_nominal_max=" << hist_nominal_max << endl;
  //   cout << "hist_syst_max=" << hist_syst_max << endl;
  //   cout << "hist_nominal_sigma=" << hist_nominal_sigma << endl;
  //   cout << "hist_syst_sigma=" << hist_syst_sigma << endl;
  
  //  cout << "hist_syst_integral=" << hist_syst_integral << endl;
  //  cout << "mass_resonance=" << mass_resonance << endl;

  cout << "about to make the fits" << endl;
  
  cout << "string_method_syst_shape=" << string_method_syst_shape << endl;

  if (string_method_syst_shape=="mean_IQR") {
    cout << "call ComputeAndPlot_Syst_shape_From_Mean_and_Interquartile" << endl;
    ComputeAndPlot_Syst_shape_From_Mean_and_Interquartile(string_sample,string_category,string_campaign_MxAOD,string_systematic,m_string_observable_shape,index_toy,current_tree_nominal,current_tree_syst);
    cout << "called ComputeAndPlot_Syst_shape_From_Mean_and_Interquartile" << endl;
  }
  //===========================================================================================================================
  else {
    int nb_parameters=0;
    //---
    float alphaCB_Low_init=1;
    float alphaCB_High_init=1;
    
    //nominal
    float nCB_Low_init=9;
    float nCB_High_init=5;
    
    //for debugging
    //   float nCB_Low_init=5;
    //   float nCB_High_init=9;

    //---
    
    float slopeExp_Low_init=2;
    float slopeExp_High_init=2;
    //---
    float nb_sigmas_for_fit_range_left=-1;
    float nb_sigmas_for_fit_range_right=-1;

    if (string_functional_form=="DoubleCrystalBall") {
      nb_parameters=7;
      nb_sigmas_for_fit_range_left=4; //float in avoid rounding effect
      nb_sigmas_for_fit_range_right=4; //float in avoid rounding effect
    }
    else if (string_functional_form=="ExpGaussExp") {
      nb_parameters=5;
      
      nb_sigmas_for_fit_range_left=3; //float in avoid rounding effect
      nb_sigmas_for_fit_range_right=2.5; //float in avoid rounding effect

      /*
      nb_sigmas_for_fit_range_left=1.0; //float in avoid rounding effect
      nb_sigmas_for_fit_range_right=1.0; //float in avoid rounding effect
      */

      //      nb_sigmas_for_fit_range_left=1.; //float in avoid rounding effect
      //      nb_sigmas_for_fit_range_right=2.5; //float in avoid rounding effect
    }
    else if (string_functional_form=="Bukin") {

      nb_parameters=5;
      
      if (m_string_observable_shape=="m_yybb_tilde") {
	
	//to do : detect non resonant or resonant
	
	if (
	    string_sample.find("HH_non_resonant_kappa_lambda_01")!=string::npos
	    ||
	    string_sample.find("HH_non_resonant_kappa_lambda_10")!=string::npos
	    ||
	    string_sample.find("aMCnloHwpp_hh_yybb")!=string::npos
	    ||
	    string_sample.find("MGH7_hh_bbyy_vbf_l1cvv1cv1")!=string::npos
	    ||
	    string_sample.find("PowhegH7_HHbbyy_cHHH01d0")!=string::npos
	    ||
	    string_sample.find("PowhegH7_HHbbyy_cHHH01d0")!=string::npos
	    ||
	    string_sample.find("MGH7_hh_bbyy_vbf_l1cvv1cv1")!=string::npos
	    ) {
	  //excellent choice : : 1.2-3 : it stabilizes the fit
	  //1.2 : problem for HH kappa lambda=1, merged, lhapdf=90428
	  nb_sigmas_for_fit_range_left=1.2; //float in avoid rounding effect
	  //1.1 : too short
	  //nb_sigmas_for_fit_range_left=1.1; //float in avoid rounding effect
	  //nb_sigmas_for_fit_range_right=2.; //float in avoid rounding effect
	  //nb_sigmas_for_fit_range_right=2.2; //float in avoid rounding effect
	  nb_sigmas_for_fit_range_right=3; //float in avoid rounding effect
	}

	/*
	else if (
		 string_sample.find("aMCnloHwpp_hh_yybb_AF2")!=string::npos
	    ) {
	  nb_sigmas_for_fit_range_left=1.25; //float in avoid rounding effect
	  //	  nb_sigmas_for_fit_range_left=1; //float in avoid rounding effect
	  nb_sigmas_for_fit_range_right=2.5; //float in avoid rounding effect
	}
	*/
	else { //resonant

	  cout << "case not considered, revisit, halt program" << endl;
	  exit(1);
	  nb_sigmas_for_fit_range_left=4; //float in avoid rounding effect
	  nb_sigmas_for_fit_range_right=4; //float in avoid rounding effect
	}
      } //end m_yybb_tilde
      else {
	nb_sigmas_for_fit_range_left=4; //float in avoid rounding effect
	nb_sigmas_for_fit_range_right=4; //float in avoid rounding effect
      }
    }

    low_value_nominal_fit_range=hist_nominal_position_max-nb_sigmas_for_fit_range_left*hist_nominal_sigma;
    high_value_nominal_fit_range=hist_nominal_position_max+nb_sigmas_for_fit_range_right*hist_nominal_sigma;

    cout << "temporary, low_value_nominal_fit_range=" << low_value_nominal_fit_range << ", high_value_nominal_fit_range=" << high_value_nominal_fit_range << endl;

    //algorithm to prevent going beyond the first left and last right value of the non-null bins
    if (low_value_nominal_fit_range<hist_nominal->GetBinLowEdge(hist_nominal->FindFirstBinAbove(0.)))
      low_value_nominal_fit_range=hist_nominal->GetBinLowEdge(hist_nominal->FindFirstBinAbove(0.));
    
    if (high_value_nominal_fit_range>hist_nominal->GetBinCenter(hist_nominal->FindLastBinAbove(0.))+0.5*hist_nominal->GetBinWidth(1))
      high_value_nominal_fit_range=hist_nominal->GetBinCenter(hist_nominal->FindLastBinAbove(0.))+0.5*hist_nominal->GetBinWidth(1);

    cout << "final, low_value_nominal_fit_range=" << low_value_nominal_fit_range << ", high_value_nominal_fit_range=" << high_value_nominal_fit_range << endl;

    cout << "hist_nominal_mean=" << hist_nominal_mean << endl;
    cout << "hist_nominal_sigma=" << hist_nominal_sigma << endl;
    cout << "low_value_nominal_fit_range=" << low_value_nominal_fit_range << endl;
    cout << "high_value_nominal_fit_range=" << high_value_nominal_fit_range << endl;

    if (string_systematic!="showering" && current_tree_syst) {

      low_value_syst_fit_range=hist_syst_position_max-nb_sigmas_for_fit_range_left*hist_syst_sigma;
      high_value_syst_fit_range=hist_syst_position_max+nb_sigmas_for_fit_range_right*hist_syst_sigma;

      cout << "low_value_syst_fit_range=" << low_value_syst_fit_range << endl;
      cout << "high_value_syst_fit_range=" << high_value_syst_fit_range << endl;
      
      cout << "temporary, low_value_syst_fit_range=" << low_value_syst_fit_range << ", high_value_syst_fit_range=" << high_value_syst_fit_range << endl;
      
      //algorithm to prevent going beyond the first left and last right value of the non-null bins
      if (low_value_syst_fit_range<hist_syst->GetBinLowEdge(hist_syst->FindFirstBinAbove(0.)))
	low_value_syst_fit_range=hist_syst->GetBinLowEdge(hist_syst->FindFirstBinAbove(0.));
      
      if (high_value_syst_fit_range>hist_syst->GetBinCenter(hist_syst->FindLastBinAbove(0.))+0.5*hist_syst->GetBinWidth(1))
	high_value_syst_fit_range=hist_syst->GetBinCenter(hist_syst->FindLastBinAbove(0.))+0.5*hist_syst->GetBinWidth(1);
      
      cout << "final, low_value_syst_fit_range=" << low_value_syst_fit_range << ", high_value_syst_fit_range=" << high_value_syst_fit_range << endl;
    }
    
    //on purpose outside the block in order to be accessible
    index_alphaCB_Low=2;
    index_alphaCB_High=4;
    index_nCB_Low=3;
    index_nCB_High=5;
    
    index_slopeExp_Low=2;
    index_slopeExp_High=3;

    string string_position_parameter;
    string string_spread_parameter;

    //    float nb_sigmas_for_fit_range=0;

    //could not use RooCategory (checked) : no hope of conversion from int to double

    roorealvar_eventNumber=0;
    roorealvar_weight_total=0;

    if (shape_chi2fit_1_loglikelihoodfit2==1) { //restrict to non empty or negative bins
    
      int index_bin;
      
      //      int bin_max_nominal=hist_nominal->FindBin(mass_resonance);
      int bin_max_nominal=hist_nominal->FindBin(mass_resonance_finalDV);
    
      //search at the left
      for (index_bin=bin_max_nominal;index_bin>=1 && hist_nominal->GetBinContent(index_bin)>0;index_bin--)
	;
      
      if (index_bin>=1 && hist_nominal->GetBinCenter(index_bin+1)>low_value_nominal_fit_range) //found a 0, so take the bin directly bigger
	low_value_nominal_fit_range=hist_nominal->GetBinCenter(index_bin+1);
    
      //      cout << "new low_value_nominal_fit_range=" << low_value_nominal_fit_range << endl;
    
      //search at the right
      for (index_bin=bin_max_nominal;index_bin<=hist_nominal->GetNbinsX() && hist_nominal->GetBinContent(index_bin)>0;index_bin++)
	;
      if (index_bin<=hist_nominal->GetNbinsX() && hist_nominal->GetBinCenter(index_bin-1)<high_value_nominal_fit_range) //found a 0, so take the bin directly lower
	high_value_nominal_fit_range=hist_nominal->GetBinCenter(index_bin-1);
    
      cout << "new high_value_nominal_fit_range=" << high_value_nominal_fit_range << endl;
      //------------------------
      //------------------------
      //to replace with hist->find bin mean of syst
      
      if (string_systematic!="showering" && current_tree_syst) {
	//	int bin_max_syst=hist_syst->FindBin(mass_resonance);
	int bin_max_syst=hist_syst->FindBin(mass_resonance_finalDV);
	
	//search at the left
	for (index_bin=bin_max_syst;index_bin>=1 && hist_syst->GetBinContent(index_bin)>0;index_bin--)
	  ;
	if (index_bin>=1 && hist_syst->GetBinCenter(index_bin+2)>low_value_syst_fit_range) //found a 0, so take the bin directly bigger
	  low_value_syst_fit_range=hist_syst->GetBinCenter(index_bin+2);
	
	cout << "new low_value_syst_fit_range=" << low_value_syst_fit_range << endl;
	
	//search at the right
	for (index_bin=bin_max_syst;index_bin<=hist_syst->GetNbinsX() && hist_syst->GetBinContent(index_bin)>0;index_bin++)
	  ;
	if (index_bin<=hist_syst->GetNbinsX() && hist_syst->GetBinCenter(index_bin-2)<high_value_syst_fit_range) //found a 0, so take the bin directly lower
	  high_value_syst_fit_range=hist_syst->GetBinCenter(index_bin-2);
	
	cout << "new high_value_syst_fit_range=" << high_value_syst_fit_range << endl;
      }
    }
    
    cout << "range of m_gamgam considered for the fit nominal: [" << low_value_nominal_fit_range << " ; " << high_value_nominal_fit_range << "]" << endl;

    if (string_systematic!="showering" && current_tree_syst)
      cout << "range of m_gamgam considered for the fit syst: [" << low_value_syst_fit_range << " ; " << high_value_syst_fit_range << "]" << endl;
      
    string string_normalization_parameter;
    
    //makes it crash, for unknown reason
    
    if (shape_root1_roofit2==1) { //root
      string string_function_nominal;
      string string_function_syst;

      if (string_functional_form=="DoubleCrystalBall") {
	string_function_nominal="function_shape_nominal_DoubleCrystalBall";
	function_shape_nominal=new TF1(string_function_nominal.c_str(),DoubleCrystalBall,low_value_nominal_fit_range,high_value_nominal_fit_range,nb_parameters);
		      
	string_function_syst="function_shape_syst_DoubleCrystalBall";
	function_shape_syst=new TF1(string_function_syst.c_str(),DoubleCrystalBall,low_value_syst_fit_range,high_value_syst_fit_range,nb_parameters);


	index_position_parameter=0;
	index_spread_parameter=1;
	index_normalization_parameter=6;
		      
	string_position_parameter="#mu_{CB}";
	string_spread_parameter="#sigma_{CB}";
	string_normalization_parameter="norm";
      }
      else if (string_functional_form=="ExpGaussExp") {
	string_function_nominal="function_shape_nominal_ExpGausExp";
	
	function_shape_nominal=new TF1(string_function_nominal.c_str(),ExpGausExp,low_value_nominal_fit_range,high_value_nominal_fit_range,nb_parameters);
	
	string_function_syst="function_shape_syst_ExpGausExp";
	function_shape_syst=new TF1(string_function_syst.c_str(),ExpGausExp,low_value_syst_fit_range,high_value_syst_fit_range,nb_parameters);
	
	index_position_parameter=0;
	index_spread_parameter=1;
	index_normalization_parameter=4;

	string_position_parameter="#mu_{Gauss}";
	string_spread_parameter="#sigma_{Gauss}";
	string_normalization_parameter="norm";
      }
      else {
	cout << "functional form not implemented in root format" << endl;
      }

      //		  f1->SetNpx(100000);
		    
      function_shape_nominal->SetLineColor(kGreen+2);

      function_shape_syst->SetLineColor(kBlue+2);
      
      //TO FACTORIZE
      
      function_shape_nominal->SetParameter(index_position_parameter,hist_nominal_mean); //muCB or muGauss
      function_shape_nominal->SetParameter(index_spread_parameter,hist_nominal_sigma); //sigmaCB or sigmaGauss
      function_shape_nominal->SetParameter(index_normalization_parameter,hist_nominal_max); //normalization
      
      function_shape_syst->SetParameter(index_position_parameter,hist_syst_mean); //muGauss
      function_shape_syst->SetParameter(index_spread_parameter,hist_syst_sigma); //sigmaGauss
      function_shape_syst->SetParameter(index_normalization_parameter,hist_syst_max); //normalization
      
      if (string_functional_form=="DoubleCrystalBall") {
	function_shape_nominal->SetParName(index_position_parameter,string_position_parameter.c_str());
	function_shape_nominal->SetParName(index_spread_parameter,string_spread_parameter.c_str());
	function_shape_nominal->SetParName(index_normalization_parameter,string_normalization_parameter.c_str());
	function_shape_nominal->SetParName(index_alphaCB_Low,"#alpha_{Low}");
	function_shape_nominal->SetParName(index_nCB_Low,"n_{Low}");
	function_shape_nominal->SetParName(index_alphaCB_High,"#alpha_{High}");
	function_shape_nominal->SetParName(index_nCB_High,"n_{High}");
	
	function_shape_syst->SetParName(index_position_parameter,string_position_parameter.c_str());
	function_shape_syst->SetParName(index_spread_parameter,string_spread_parameter.c_str());
	function_shape_syst->SetParName(index_normalization_parameter,string_normalization_parameter.c_str());
	function_shape_syst->SetParName(index_alphaCB_Low,"#alpha_{Low}");
	function_shape_syst->SetParName(index_nCB_Low,"n_{Low}");
	function_shape_syst->SetParName(index_alphaCB_High,"#alpha_{High}");
	function_shape_syst->SetParName(index_nCB_High,"n_{High}");
      }
      else if (string_functional_form=="ExpGaussExp") {
	function_shape_nominal->SetParName(index_position_parameter,string_position_parameter.c_str());
	function_shape_nominal->SetParName(index_spread_parameter,string_spread_parameter.c_str());
	function_shape_nominal->SetParName(index_normalization_parameter,string_normalization_parameter.c_str());
	function_shape_nominal->SetParName(index_slopeExp_Low,"k_{Low}");
	function_shape_nominal->SetParName(index_slopeExp_High,"k_{High}");
      
	function_shape_syst->SetParName(index_position_parameter,string_position_parameter.c_str());
	function_shape_syst->SetParName(index_spread_parameter,string_spread_parameter.c_str());
	function_shape_syst->SetParName(index_normalization_parameter,string_normalization_parameter.c_str());
	function_shape_syst->SetParName(index_slopeExp_Low,"k_{Low}");
	function_shape_syst->SetParName(index_slopeExp_High,"k_{High}");
      }
    
      //consider the case of ExpGausExp which has a normalization in a multiplicative factor of sigma
      function_shape_nominal->SetParLimits(index_normalization_parameter,0,hist_nominal_integral*5.*hist_nominal_sigma);
      
      function_shape_nominal->SetParLimits(index_position_parameter,hist_nominal_mean-hist_nominal_sigma,hist_nominal_mean+hist_nominal_sigma);
      
      //      function_shape_nominal->SetParLimits(index_spread_parameter,0.2*hist_nominal_sigma,5*hist_nominal_sigma);
      function_shape_nominal->SetParLimits(index_spread_parameter,0.,5*hist_nominal_sigma);
      //---
      function_shape_syst->SetParLimits(index_normalization_parameter,0,hist_syst_integral*5.*hist_syst_sigma);
      //TO CHANGE
      function_shape_syst->SetParLimits(index_position_parameter,hist_syst_mean-hist_syst_sigma,hist_syst_mean+hist_syst_sigma);
      
      function_shape_syst->SetParLimits(index_spread_parameter,0.,5*hist_syst_sigma);
      //---
      //for unknown reason, despite it is not used in the mode that crashes, the uncomment of this block crashes
      //was due to mode without compilation

      //a logical or of any of these two blocks make the program to crash, for unknown reason
      if (string_functional_form=="DoubleCrystalBall") {

	function_shape_nominal->SetParameter(index_alphaCB_Low,alphaCB_Low_init);
	function_shape_nominal->SetParameter(index_nCB_Low,nCB_Low_init);
	function_shape_nominal->SetParameter(index_alphaCB_High,alphaCB_High_init);
	function_shape_nominal->SetParameter(index_nCB_High,nCB_High_init);

	function_shape_nominal->SetParLimits(index_alphaCB_Low,0.2*alphaCB_Low_init,5*alphaCB_Low_init);

	function_shape_nominal->SetParLimits(index_nCB_Low,0,200);
          
	function_shape_nominal->SetParLimits(index_alphaCB_High,0.2*alphaCB_High_init,5*alphaCB_High_init);
	function_shape_nominal->SetParLimits(index_nCB_High,0,200);

	//---
	function_shape_syst->SetParameter(index_alphaCB_Low,alphaCB_Low_init);
	function_shape_syst->SetParameter(index_nCB_Low,nCB_Low_init);
	function_shape_syst->SetParameter(index_alphaCB_High,alphaCB_High_init);
	function_shape_syst->SetParameter(index_nCB_High,nCB_High_init);
	
	function_shape_syst->SetParLimits(index_alphaCB_Low,0.2*alphaCB_Low_init,5*alphaCB_Low_init);
	
	function_shape_syst->SetParLimits(index_nCB_Low,0,200);
	function_shape_syst->SetParLimits(index_alphaCB_High,0.2*alphaCB_High_init,5*alphaCB_High_init);
	function_shape_syst->SetParLimits(index_nCB_High,0,200);
      }      
      else if (string_functional_form=="ExpGaussExp") {
	function_shape_nominal->SetParameter(index_slopeExp_Low,slopeExp_Low_init);
	function_shape_nominal->SetParameter(index_slopeExp_High,slopeExp_High_init);
      
	function_shape_nominal->SetParLimits(index_slopeExp_Low,0.4,10);
	function_shape_nominal->SetParLimits(index_slopeExp_High,0.4,10);
      
	//---
	function_shape_syst->SetParameter(index_slopeExp_Low,slopeExp_Low_init);
	function_shape_syst->SetParameter(index_slopeExp_High,slopeExp_High_init);
	
	function_shape_syst->SetParLimits(index_slopeExp_Low,0.4,10);
	function_shape_syst->SetParLimits(index_slopeExp_High,0.4,10);
	//---
      } //end ExpGausExp
      
      cout << "=================================================================================" << endl;
      cout << "Fit of histogram nominal" << endl;
    
      if (shape_chi2fit_1_loglikelihoodfit2==1) {
	fitresult_nominal=hist_nominal->Fit(string_function_nominal.c_str(),"RNS");
	done_fit_shape_nominal=1;
      }
      else if (shape_chi2fit_1_loglikelihoodfit2==2) {
	//was a big bug there, for root version : was fitting the nominal !!

	fitresult_syst=hist_syst->Fit(string_function_nominal.c_str(),"RWLNS"); //weighted log-likelihood
      }
    
      cout << "=================================================================================" << endl;
      cout << "Fit of histogram systematics" << endl;
      if (shape_chi2fit_1_loglikelihoodfit2==1)
	fitresult_nominal=hist_syst->Fit(string_function_syst.c_str(),"RNS");
      else if (shape_chi2fit_1_loglikelihoodfit2==2) {
	fitresult_syst=hist_syst->Fit(string_function_syst.c_str(),"RWLNS"); //weighted log-likelihood
      }
    }
    else if (shape_root1_roofit2==2) { //roofit
      cout << "starts roofit" << endl;

      roorealvar_observable=new RooRealVar(m_string_observable_shape.c_str(),m_string_observable_shape.c_str(),mass_resonance_finalDV-extension_low_histogram_shape,mass_resonance_finalDV+extension_high_histogram_shape,"GeV");
      roorealvar_eventNumber=new RooRealVar("eventNumber","eventNumber",0);
      
      //      roorealvar_observable->Print();
      //      exit(1);

      //      cout << "mass_resonance_finalDV=" << mass_resonance_finalDV << endl;
      //      cout << "mass_resonance_finalDV-extension_low_histogram_shape=" << mass_resonance_finalDV-extension_low_histogram_shape << endl;
      //      cout << "mass_resonance_finalDV+extension_high_histogram_shape=" << mass_resonance_finalDV+extension_high_histogram_shape << endl;
      
      roorealvar_observable->setBins(hist_nominal->GetNbinsX());
      
      roorealvar_weight_total=new RooRealVar(buffer_weight,buffer_weight,1);
      
      RooArgSet argset_variables;
      
      argset_variables.add(*roorealvar_observable);
      //    roorealvar_observable->Print();
      
      if (shape_chi2fit_1_loglikelihoodfit2==1) {
	absdata_nominal=new RooDataHist("absdata_nominal","absdata_nominal",argset_variables,hist_nominal);
	
	if (string_systematic!="showering" && current_tree_syst)
	  absdata_syst=new RooDataHist("absdata_syst","absdata_syst",argset_variables,hist_syst);
      }		    
      else if (shape_chi2fit_1_loglikelihoodfit2==2) {
	argset_variables.add(*roorealvar_eventNumber);
	argset_variables.add(*roorealvar_weight_total);
	
	//buffer_modulo_selection is empty in case of no jacknife
	absdata_nominal=new RooDataSet("absdata_nominal","absdata_nominal",current_tree_nominal,argset_variables,buffer_modulo_selection,buffer_weight);

	//      cout << "absdata_nominal=" << absdata_nominal << endl;
	cout << "absdata_nominal numEntries=" << absdata_nominal->numEntries() << endl;
	cout << "absdata_nominal sumEntries=" << absdata_nominal->sumEntries() << endl;
	
	if (string_systematic!="showering" && current_tree_syst) {

	  absdata_syst=new RooDataSet("absdata_syst","absdata_syst",current_tree_syst,argset_variables,buffer_modulo_selection,buffer_weight);

	  cout << "absdata_syst numEntries=" << absdata_syst->numEntries() << endl;
	  cout << "absdata_syst sumEntries=" << absdata_syst->sumEntries() << endl;
	}
      }
      
      //remark: could also use the one with Import, WeightVar, etc.

      if (absdata_nominal->sumEntries()==0) {
	cout << "no event, careful" << endl;
	//      cout << "no events, halt program" << endl;
	//      exit(1);
      }

      //Double Crystal Ball
      RooRealVar **roorealvar_muCB=0;
      RooRealVar **roorealvar_sigmaCB=0;
      RooRealVar **roorealvar_alphaCB_Low=0;
      RooRealVar **roorealvar_nCB_Low=0;
      RooRealVar **roorealvar_alphaCB_High=0;
      RooRealVar **roorealvar_nCB_High=0;
      
      //Exp Gauss Exp
      RooRealVar **roorealvar_muGauss=0;
      RooRealVar **roorealvar_sigmaGauss=0;
      RooRealVar **roorealvar_slopeExp_Low=0;
      RooRealVar **roorealvar_slopeExp_High=0;

      //Bukin
      RooRealVar **roorealvar_muBukin=0;
      RooRealVar **roorealvar_sigmaBukin=0;
      RooRealVar **roorealvar_xiBukin=0;
      RooRealVar **roorealvar_rho1Bukin=0;
      RooRealVar **roorealvar_rho2Bukin=0;

      RooAbsPdf **pdf_shape;

      RooFitResult **roofitresult;
      RooAbsData *absdata;

      string string_nominal_syst;
      double hist_mean;
      double hist_position_max;
      double hist_sigma;
      
      double low_value_fit_range;
      double high_value_fit_range;

      bool *ParamAtLimit;

      for (int index_nominal_syst=0;index_nominal_syst<2;index_nominal_syst++) {

	cout << "index_nominal_syst=" << index_nominal_syst << endl;
	
	if (string_systematic=="showering" && index_nominal_syst>=1)
	  continue;
	
	if (index_nominal_syst==0) { //nominal
	  string_nominal_syst="nominal";

	  low_value_fit_range=low_value_nominal_fit_range;
	  high_value_fit_range=high_value_nominal_fit_range;

	  hist_mean=hist_nominal_mean;
	  hist_position_max=hist_nominal_position_max;
	  hist_sigma=hist_nominal_sigma;

	  pdf_shape=&pdf_shape_nominal;
	  roofitresult=&roofitresult_nominal;

	  absdata=absdata_nominal;

	  cout << "string_functional_form=" << string_functional_form << endl;

	  if (string_functional_form=="DoubleCrystalBall") {
	    roorealvar_muCB=&roorealvar_muCB_nominal;
	    roorealvar_sigmaCB=&roorealvar_sigmaCB_nominal;
	    roorealvar_alphaCB_Low=&roorealvar_alphaCB_Low_nominal;
	    roorealvar_nCB_Low=&roorealvar_nCB_Low_nominal;
	    roorealvar_alphaCB_High=&roorealvar_alphaCB_High_nominal;
	    roorealvar_nCB_High=&roorealvar_nCB_High_nominal;
	  }
	  else if (string_functional_form=="ExpGaussExp") {
	    roorealvar_muGauss=&roorealvar_muGauss_nominal;
	    roorealvar_sigmaGauss=&roorealvar_sigmaGauss_nominal;
	  
	    roorealvar_slopeExp_Low=&roorealvar_slopeExp_Low_nominal;
	    roorealvar_slopeExp_High=&roorealvar_slopeExp_High_nominal;
	  }
	  else if (string_functional_form=="Bukin") {
	    cout << "get the muBukin" << endl;
	    roorealvar_muBukin=&roorealvar_muBukin_nominal;
	    cout << "roorealvar_muBukin=" << roorealvar_muBukin << endl;
	    cout << "roorealvar_muBukin_nominal=" << roorealvar_muBukin_nominal << endl;

	    roorealvar_sigmaBukin=&roorealvar_sigmaBukin_nominal;
	    roorealvar_xiBukin=&roorealvar_xiBukin_nominal;
	    roorealvar_rho1Bukin=&roorealvar_rho1Bukin_nominal;
	    roorealvar_rho2Bukin=&roorealvar_rho2Bukin_nominal;
	  }
	  
	  ParamAtLimit=&ParamAtLimit_nominal;
	} //end case nominal
	else if (index_nominal_syst==1) { //syst
	  string_nominal_syst="syst";

	  low_value_fit_range=low_value_syst_fit_range;
	  high_value_fit_range=high_value_syst_fit_range;

	  hist_mean=hist_syst_mean;
	  hist_position_max=hist_syst_position_max;
	  hist_sigma=hist_syst_sigma;
	  
	  pdf_shape=&pdf_shape_syst;
	  roofitresult=&roofitresult_syst;

	  absdata=absdata_syst;

	  if (string_functional_form=="DoubleCrystalBall") {
	    roorealvar_muCB=&roorealvar_muCB_syst;
	    roorealvar_sigmaCB=&roorealvar_sigmaCB_syst;
	    roorealvar_alphaCB_Low=&roorealvar_alphaCB_Low_syst;
	    roorealvar_nCB_Low=&roorealvar_nCB_Low_syst;
	    roorealvar_alphaCB_High=&roorealvar_alphaCB_High_syst;
	    roorealvar_nCB_High=&roorealvar_nCB_High_syst;
	  }
	  else if (string_functional_form=="ExpGaussExp") {
	    roorealvar_muGauss=&roorealvar_muGauss_syst;
	    roorealvar_sigmaGauss=&roorealvar_sigmaGauss_syst;
	  
	    roorealvar_slopeExp_Low=&roorealvar_slopeExp_Low_syst;
	    roorealvar_slopeExp_High=&roorealvar_slopeExp_High_syst;
	  }
	  else if (string_functional_form=="Bukin") {
	    roorealvar_muBukin=&roorealvar_muBukin_syst;
	    roorealvar_sigmaBukin=&roorealvar_sigmaBukin_syst;
	    roorealvar_xiBukin=&roorealvar_xiBukin_syst;
	    roorealvar_rho1Bukin=&roorealvar_rho1Bukin_syst;
	    roorealvar_rho2Bukin=&roorealvar_rho2Bukin_syst;
	  }

	  ParamAtLimit=&ParamAtLimit_syst;
	} //end case syst
	
	if (string_functional_form=="DoubleCrystalBall") {
	  cout << "allocate memory" << endl;
	  cout << "roorealvar_muCB=" << roorealvar_muCB << endl;
	  cout << "roorealvar_muCB_nominal=" << roorealvar_muCB_nominal << endl;
	  
	  //	  *roorealvar_muCB=new RooRealVar((string("SignalPdf_")+m_string_observable_shape+"_"+"muCB_"+string_nominal_syst).c_str(),"#mu_{CB}",hist_mean,hist_mean-hist_sigma,hist_mean+hist_sigma,"GeV");
	  *roorealvar_muCB=new RooRealVar((string("SignalPdf_")+m_string_observable_shape+"_"+"muCB_"+string_nominal_syst).c_str(),"#mu_{CB}",hist_position_max,hist_position_max-hist_sigma,hist_position_max+hist_sigma,"GeV");
	  
	  *roorealvar_sigmaCB=new RooRealVar((string("SignalPdf_")+m_string_observable_shape+"_"+"sigmaCB_"+string_nominal_syst).c_str(),"#sigma_{CB}",hist_sigma,0.,5*hist_sigma,"GeV");
	  
	  *roorealvar_alphaCB_Low=new RooRealVar((string("SignalPdf_")+m_string_observable_shape+"_"+"alphaCB_Low_"+string_nominal_syst).c_str(),"#alpha_{Low}",alphaCB_Low_init,0.,5*alphaCB_Low_init,"");
	  *roorealvar_nCB_Low=new RooRealVar((string("SignalPdf_")+m_string_observable_shape+"_"+"nCB_Low_"+string_nominal_syst).c_str(),"n_{Low}",nCB_Low_init,0,200,"");
	  
	  *roorealvar_alphaCB_High=new RooRealVar((string("SignalPdf_")+m_string_observable_shape+"_"+"alphaCB_High_"+string_nominal_syst).c_str(),"#alpha_{High}",alphaCB_High_init,0.,5*alphaCB_High_init,"");
	  *roorealvar_nCB_High=new RooRealVar((string("SignalPdf_")+m_string_observable_shape+"_"+"nCB_High_"+string_nominal_syst).c_str(),"n_{High}",nCB_High_init,0,200,"");


	  cout << "initial parameters" << endl;
	  (*roorealvar_muCB)->Print();
	  
	  (*roorealvar_sigmaCB)->Print();
	  
	  (*roorealvar_alphaCB_Low)->Print();
	  (*roorealvar_nCB_Low)->Print();
	  
	  (*roorealvar_alphaCB_High)->Print();
	  (*roorealvar_nCB_High)->Print();

	  //------------------------
	  (*roorealvar_muCB)->setConstant(0);
	  (*roorealvar_sigmaCB)->setConstant(0);
	  (*roorealvar_alphaCB_Low)->setConstant(0);
	  (*roorealvar_nCB_Low)->setConstant(0);
	  (*roorealvar_alphaCB_High)->setConstant(0);
	  (*roorealvar_nCB_High)->setConstant(0);
	}
	else if (string_functional_form=="ExpGaussExp") {
	  //	  *roorealvar_muGauss=new RooRealVar((string("SignalPdf_")+m_string_observable_shape+"_"+"muGauss_"+string_nominal_syst).c_str(),"#mu_{Gauss}",hist_mean,hist_mean-hist_sigma,hist_mean+hist_sigma,"GeV");
	  *roorealvar_muGauss=new RooRealVar((string("SignalPdf_")+m_string_observable_shape+"_"+"muGauss_"+string_nominal_syst).c_str(),"#mu_{Gauss}",hist_position_max,hist_position_max-hist_sigma,hist_position_max+hist_sigma,"GeV");
	  *roorealvar_sigmaGauss=new RooRealVar((string("SignalPdf_")+m_string_observable_shape+"_"+"sigmaGauss_"+string_nominal_syst).c_str(),"#sigma_{Gauss}",hist_sigma,0.2*hist_sigma,5*hist_sigma,"GeV");
	  
	  *roorealvar_slopeExp_Low=new RooRealVar((string("SignalPdf_")+m_string_observable_shape+"_"+"slopeExp_Low_"+string_nominal_syst).c_str(),"k_{Low}",slopeExp_Low_init,0.01,10);
	  *roorealvar_slopeExp_High=new RooRealVar((string("SignalPdf_")+m_string_observable_shape+"_"+"slopeExp_High_"+string_nominal_syst).c_str(),"k_{High}",slopeExp_High_init,0.01,10);
	  
	  (*roorealvar_muGauss)->setConstant(0);
	  (*roorealvar_sigmaGauss)->setConstant(0);
	  (*roorealvar_slopeExp_Low)->setConstant(0);
	  (*roorealvar_slopeExp_High)->setConstant(0);
	}
	else if (string_functional_form=="Bukin") {
	  cout << "allocate the muBukin variables" << endl;
	  //*roorealvar_muBukin=new RooRealVar((string("SignalPdf_")+m_string_observable_shape+"_"+"muBukin_"+string_nominal_syst).c_str(),"#mu_{Bukin}",hist_mean,hist_mean-hist_sigma,hist_mean+hist_sigma,"GeV");
	  *roorealvar_muBukin=new RooRealVar((string("SignalPdf_")+m_string_observable_shape+"_"+"muBukin_"+string_nominal_syst).c_str(),"#mu_{Bukin}",hist_position_max,hist_position_max-hist_sigma,hist_position_max+hist_sigma,"GeV");
	  *roorealvar_sigmaBukin=new RooRealVar((string("SignalPdf_")+m_string_observable_shape+"_"+"sigmaBukin_"+string_nominal_syst).c_str(),"#sigma_{Bukin}",hist_sigma,0.*hist_sigma,5*hist_sigma,"GeV");
	  *roorealvar_xiBukin=new RooRealVar((string("SignalPdf_")+m_string_observable_shape+"_"+"xiBukin_"+string_nominal_syst).c_str(),"#xi_{Bukin}",0,0.,1.,"GeV");
	  *roorealvar_rho1Bukin=new RooRealVar((string("SignalPdf_")+m_string_observable_shape+"_"+"rho1Bukin_"+string_nominal_syst).c_str(),"#rho_{1 Bukin}",0,-1,0.2,"GeV"); //put 0.1 ?
	  *roorealvar_rho2Bukin=new RooRealVar((string("SignalPdf_")+m_string_observable_shape+"_"+"rho2Bukin_"+string_nominal_syst).c_str(),"#rho_{2 Bukin}",0,-1,0.2,"GeV");
	  
	  (*roorealvar_muBukin)->setConstant(0);
	  (*roorealvar_sigmaBukin)->setConstant(0);
	  (*roorealvar_xiBukin)->setConstant(0);
	  (*roorealvar_rho1Bukin)->setConstant(0);
	  (*roorealvar_rho2Bukin)->setConstant(0);
	  
	  //	  (*roorealvar_muBukin)->setConstant(1);
	  //	  (*roorealvar_sigmaBukin)->setConstant(1);
	  //	  (*roorealvar_xiBukin)->setConstant(1);
	  //	  (*roorealvar_rho1Bukin)->setConstant(1);
	  //	  (*roorealvar_rho2Bukin)->setConstant(1);
	}
	
	if (string_functional_form=="DoubleCrystalBall") {
	  cout << "allocate signal DBCB" << endl;
	  *pdf_shape=new HggTwoSidedCBPdf((string("Pdf_Signal_")+m_string_observable_shape+"_"+string_nominal_syst+"_"+string_category).c_str(),(string("pdf_shape_")+string_nominal_syst).c_str(),*roorealvar_observable,**roorealvar_muCB,**roorealvar_sigmaCB,**roorealvar_alphaCB_Low,**roorealvar_nCB_Low,**roorealvar_alphaCB_High,**roorealvar_nCB_High);
	}
	else if (string_functional_form=="ExpGaussExp")
	  *pdf_shape=new ExpGausExpPDF((string("Pdf_Signal_")+m_string_observable_shape+"_"+string_nominal_syst+"_"+string_category).c_str(),(string("pdf_shape_")+string_nominal_syst).c_str(),*roorealvar_observable,**roorealvar_muGauss,**roorealvar_sigmaGauss,**roorealvar_slopeExp_Low,**roorealvar_slopeExp_High);
	else if (string_functional_form=="Bukin")
	  *pdf_shape=new RooBukinPdf((string("Pdf_Signal_")+m_string_observable_shape+"_"+string_nominal_syst+"_"+string_category).c_str(),(string("pdf_shape_")+string_nominal_syst).c_str(),*roorealvar_observable,**roorealvar_muBukin,**roorealvar_sigmaBukin,**roorealvar_xiBukin,**roorealvar_rho1Bukin,**roorealvar_rho2Bukin);
	
	cout << "============================================================================================================" << endl;
	cout << "============================================================================================================" << endl;
	
	if (index_nominal_syst==0)
	  cout << "fit nominal" << endl;
	else if (index_nominal_syst==1)
	  cout << "fit syst" << endl;
	
	//---------------------
	//options for the roofit fit
	
	RooCmdArg arg_SumW2Error=RooFit::SumW2Error(1);
	
	cout << "at this place, low_value_nominal_fit_range=" << low_value_nominal_fit_range << ", high_value_nominal_fit_range=" << high_value_nominal_fit_range << endl;
	
	RooCmdArg arg_Range=RooFit::Range(low_value_fit_range,high_value_fit_range);

	RooCmdArg arg_strategy=RooFit::Strategy(1);
	//RooCmdArg arg_strategy=RooFit::Strategy(2);
	RooCmdArg arg_Hesse=RooFit::Hesse(1);
	RooCmdArg arg_offset=RooFit::Offset(1);
	RooCmdArg arg_save=RooFit::Save(1);
	
	RooCmdArg arg_Verbose=RooFit::Verbose(0);
	RooCmdArg arg_PrintLevel=RooFit::PrintLevel(-1);
	RooCmdArg arg_PrintEvalErrors=RooFit::PrintEvalErrors(-1);
	RooCmdArg arg_Warnings=RooFit::Warnings(0);
	
	RooCmdArg arg_Minuit2=RooFit::Minimizer("Minuit2","migrad");
	
	RooLinkedList roolinkedlist;
	roolinkedlist.Clear();

	if (shape_chi2fit_1_loglikelihoodfit2==2)
	  roolinkedlist.Add(const_cast<RooCmdArg*>(&arg_SumW2Error));
	
	roolinkedlist.Add(const_cast<RooCmdArg*>(&arg_Range));
	roolinkedlist.Add(const_cast<RooCmdArg*>(&arg_strategy));
	roolinkedlist.Add(const_cast<RooCmdArg*>(&arg_Hesse));
	
	if (shape_chi2fit_1_loglikelihoodfit2==2)
	  roolinkedlist.Add(const_cast<RooCmdArg*>(&arg_offset));
	
	roolinkedlist.Add(const_cast<RooCmdArg*>(&arg_save));
	
	//    roolinkedlist.Add(const_cast<RooCmdArg*>(&arg_Minos));
	
	//minuit *1* is better, so don't use minuit2
	//roolinkedlist.Add(const_cast<RooCmdArg*>(&arg_Minuit2));
	
	if (flag_FitShapeQuiet) {
	  roolinkedlist.Add(const_cast<RooCmdArg*>(&arg_Verbose));
	  roolinkedlist.Add(const_cast<RooCmdArg*>(&arg_PrintLevel));
	  roolinkedlist.Add(const_cast<RooCmdArg*>(&arg_PrintEvalErrors));
	  roolinkedlist.Add(const_cast<RooCmdArg*>(&arg_Warnings));
	}
	
	//====================================================================
	if (shape_chi2fit_1_loglikelihoodfit2==1) { //chi2fit
	  //remark
	  //https://root-forum.cern.ch/t/createchi2-of-binned-and-weighted-data-set/9600
	  //The RooFit chi2 fit does not work when the bins have zero entries.
	  //You should either use a binned likelihood fit or use the standard chi2 fit provided by ROOT.
	  
	  //for chi2fitTo, the roolink is buggy : does not take into account the range
	  
	  //to uncomment for commands that bugs	
	  
	  roorealvar_observable->setRange((string("restricted_range_")+string_nominal_syst).c_str(),low_value_fit_range,high_value_fit_range);
	  
	  //bug if use Range directly with values : needs to go through a Range in the RooRealVar
	  
	  //		      RooAbsReal *rooabsreal_chi2;
	  //remark: computing chi2 before the fit interfers with it

	  //chi2FitTo does not work with Range expressed in a roolinkedlist, nor in a Range expressed in line command without a name
	  
	  //does not work : bug of roofit
	  // 	  (*roofitresult)=(*pdf_shape)->chi2FitTo(*(RooDataHist *)absdata,
	  // 							    RooFit::Range(low_value_fit_range,high_value_fit_range)
	  // 							    ,RooFit::Strategy(1),RooFit::Hesse(1),RooFit::Save()); //forbidden to use SumW2Error(1)
	  
	  //roolinkedlist does not work with chi2FitTo
	  //does not work : bug of roofit	  (*roofitresult)=(*pdf_shape)->chi2FitTo(*(RooDataHist *)absdata,roolinkedlist);
	  
	  (*roofitresult)=(*pdf_shape)->chi2FitTo(*(RooDataHist *)absdata,RooFit::Range((string("restricted_range_")+string_nominal_syst).c_str()),RooFit::Strategy(1),RooFit::Hesse(1),RooFit::Offset(1),RooFit::Save()); //forbidden to use SumW2Error(1)
	  
	  cout << "low_value_fit_range,high_value_fit_range=" << low_value_fit_range << ", high_value_fit_range=" << high_value_fit_range << endl;
	}
	else if (shape_chi2fit_1_loglikelihoodfit2==2) { //fitTo
	  //	ROOT::Math::MinimizerOptions::SetDefaultMaxIterations(10000);
	  //	ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls(10000);
	  
	  if (use_minimizer==1) { //remark : if would like to have correct fit, use tiny epsilon
	    nll=(*pdf_shape)->createNLL(*absdata);
	    _minuit=new RooMinimizer(*nll);
	    
	    //	  _minuit->setEps(1.0); //default tolerance
	    
	    //	  cout << "DefaultTolerance()=" << _minuit->MinimizerOptions().DefaultTolerance() << endl;
	    
	    //	    _minuit->setEps(1e-4); //1.0*1e-3
	    
	    //DAVID
	    _minuit->setEps(1e-9);
	    
	    //_minuit->setEps(1e-8); //1.0*1e-3
	    
	    //has no impact	roorealvar_observable->setRange(low_value_fit_range,high_value_fit_range);
	    
	    cout << "FIT STANDARD" << endl;
	    //_minuit->minimize("Minuit2","Migrad");
	    
	    char buffer_range[256];
	    
	    //sprintf(buffer_range,"RooFit::Minimizer(\"Minuit\",\"migrad\"),RooFit::Offset(1),RooFit::Hesse(1),RooFit::SumW2Error(1),RooRooFit::Range(%f,%f)",low_value_fit_range,high_value_fit_range);
	    sprintf(buffer_range,"RooFit::Minimizer(\"Minuit2\",\"migrad\"),RooFit::Offset(1),RooFit::Hesse(1),RooFit::SumW2Error(1),RooRooFit::Range(%f,%f)",low_value_fit_range,high_value_fit_range);
	    
	    _minuit->fit(buffer_range);
	    cout << "fit finished" << endl;
	    
	    cout << "nll->getVal()=" << nll->getVal() << endl;
	  }
	  else {
	    cout << "do fit with roofit" << endl;

	    cout << "pdf_shape=" << pdf_shape << endl;
	    //	    (*pdf_shape)->Print();

	    cout << "absdata->numEntries()=" << absdata->numEntries() << endl;
	    cout << "absdata->sumEntries()=" << absdata->sumEntries() << endl;

	    (*roofitresult)=(*pdf_shape)->fitTo(*absdata,roolinkedlist);
	  }
	}
      
	if (index_nominal_syst==0)
	  done_fit_shape_nominal=1;

	if (*roofitresult) {
	  cout << "roofitresult->status()=" << (*roofitresult)->status() << endl;
	  cout << "roofitresult->covQual()=" << (*roofitresult)->covQual() << endl;
	}
	//------------------------
	//check whether one parameter is at limit
	(*ParamAtLimit)=0;
	
	//would be better not to put data, but a rooargset of observable : more clean
	
	RooArgSet *floatPars=(RooArgSet *)(*pdf_shape)->getParameters(*absdata)->selectByAttrib("Constant",kFALSE);
	//	floatPars->Print();
	
	TIterator *iter=floatPars->createIterator();
	
	cout << "investigate if parameters are at the limits" << endl;
	RooAbsArg *absarg;
	while ((absarg=(RooAbsArg*)iter->Next())) {
	  RooRealVar *roorealvar=((RooRealVar *)absarg);
	  
	  if (IsRooRealVarAtLimit(roorealvar)==1) {
	    (*ParamAtLimit)=1;
	    cout << "it is at limit" << endl;
	  }
	  //careful      delete roorealvar;
	}
	delete iter;
	//------------------------
      } //end loop on nominal and syst
    } //end roofit
      
    
    cout << "phase 1" << endl;
    position_parameter_nominal=0,err_position_parameter_nominal=0;
    spread_parameter_nominal=0,err_spread_parameter_nominal=0;

    if (string_systematic!="showering" && current_tree_syst) {
      position_parameter_syst=0,err_position_parameter_syst=0;
      spread_parameter_syst=0,err_spread_parameter_syst=0;
    }
    
    if (shape_root1_roofit2==1) { //root
      position_parameter_nominal=function_shape_nominal->GetParameter(index_position_parameter);
      err_position_parameter_nominal=function_shape_nominal->GetParError(index_position_parameter);
      spread_parameter_nominal=function_shape_nominal->GetParameter(index_spread_parameter);
      err_spread_parameter_nominal=function_shape_nominal->GetParError(index_spread_parameter);
	
      if (string_systematic!="showering" && current_tree_syst) {
	position_parameter_syst=function_shape_syst->GetParameter(index_position_parameter);
	err_position_parameter_syst=function_shape_syst->GetParError(index_position_parameter);
	spread_parameter_syst=function_shape_syst->GetParameter(index_spread_parameter);
	err_spread_parameter_syst=function_shape_syst->GetParError(index_spread_parameter);
      }
    }
    else if (shape_root1_roofit2==2) { //roofit

      cout << "phase 2" << endl;
      
      if (string_functional_form=="DoubleCrystalBall") {
	position_parameter_nominal=roorealvar_muCB_nominal->getVal();
	
	err_position_parameter_nominal=roorealvar_muCB_nominal->getError();
	spread_parameter_nominal=roorealvar_sigmaCB_nominal->getVal();
	err_spread_parameter_nominal=roorealvar_sigmaCB_nominal->getError();

	if (string_systematic!="showering" && current_tree_syst) {
	  position_parameter_syst=roorealvar_muCB_syst->getVal();
	  err_position_parameter_syst=roorealvar_muCB_syst->getError();
	  spread_parameter_syst=roorealvar_sigmaCB_syst->getVal();
	  err_spread_parameter_syst=roorealvar_sigmaCB_syst->getError();
	}
	
      }
      else if (string_functional_form=="ExpGaussExp") {
	position_parameter_nominal=roorealvar_muGauss_nominal->getVal();
	err_position_parameter_nominal=roorealvar_muGauss_nominal->getError();
	spread_parameter_nominal=roorealvar_sigmaGauss_nominal->getVal();
	err_spread_parameter_nominal=roorealvar_sigmaGauss_nominal->getError();

	if (string_systematic!="showering" && current_tree_syst) {
	  position_parameter_syst=roorealvar_muGauss_syst->getVal();
	  err_position_parameter_syst=roorealvar_muGauss_syst->getError();
	  spread_parameter_syst=roorealvar_sigmaGauss_syst->getVal();
	  err_spread_parameter_syst=roorealvar_sigmaGauss_syst->getError();
	}
      }
      else if (string_functional_form=="Bukin") {
	position_parameter_nominal=roorealvar_muBukin_nominal->getVal();
	err_position_parameter_nominal=roorealvar_muBukin_nominal->getError();
	spread_parameter_nominal=roorealvar_sigmaBukin_nominal->getVal();
	err_spread_parameter_nominal=roorealvar_sigmaBukin_nominal->getError();

	if (string_systematic!="showering" && current_tree_syst) {
	  position_parameter_syst=roorealvar_muBukin_syst->getVal();
	  err_position_parameter_syst=roorealvar_muBukin_syst->getError();
	  spread_parameter_syst=roorealvar_sigmaBukin_syst->getVal();
	  err_spread_parameter_syst=roorealvar_sigmaBukin_syst->getError();
	}	
      }
    }
    
    if (string_systematic!="showering" && current_tree_syst) {
      //formula is correct, including for the error with the 100 %, but it assumes no correlation
      
      rel_effect_position_shape=100.*((position_parameter_syst/position_parameter_nominal)-1);
      
      if (Return_object_given_systematic(string_systematic)=="theory") {
	cout << "this systematic is theory" << endl;
	
	err_rel_effect_position_shape=get_err_rel_effect_yield_fully_correlated(position_parameter_nominal,
										position_parameter_syst,
										err_position_parameter_nominal,
										err_position_parameter_syst);
	cout << "err fully correlated=" << err_rel_effect_position_shape << endl;
      }
      else
	err_rel_effect_position_shape=100.*fabs(position_parameter_syst/position_parameter_nominal)*sqrt(pow(err_position_parameter_syst/position_parameter_syst,2)+pow(err_position_parameter_nominal/position_parameter_nominal,2));
      
      rel_effect_spread_shape=100.*((spread_parameter_syst/spread_parameter_nominal)-1);
      
      if (Return_object_given_systematic(string_systematic)=="theory") {
	cout << "this systematic is theory" << endl;
	
	err_rel_effect_spread_shape=get_err_rel_effect_yield_fully_correlated(spread_parameter_nominal,
									      spread_parameter_syst,
									      err_spread_parameter_nominal,
									      err_spread_parameter_syst);
	cout << "err fully correlated=" << err_rel_effect_spread_shape << endl;
      }
      else
	err_rel_effect_spread_shape=100.*fabs(spread_parameter_syst/spread_parameter_nominal)*sqrt(pow(err_spread_parameter_syst/spread_parameter_syst,2)+pow(err_spread_parameter_nominal/spread_parameter_nominal,2));
    }
    
    PlotShapeResults_current_systematic(string_sample,string_category,string_campaign_MxAOD,string_systematic,index_toy);
  }

  cout << "here, phase 10" << endl;
  
  return;
}

//to separate in two ?
//=============================================================================================================================================================================================
void tool_syst_shape::ComputeAndPlot_Syst_shape_From_Mean_and_Interquartile(string string_sample,string string_category,string string_campaign_MxAOD,string string_systematic,string string_finalDV,int index_toy,TTree *current_tree_nominal,TTree *current_tree_syst)
{
  //remark discussion Louis/Guillaume : theoretical error is 1.36*rms/sqrt(2N)
  //events highly correlated for theory
  //potential development : make the interquartile directly from the events, by sorting them first, etc.
  
  //once class made which contains among other things the variables below (like extension, etc.), then makes a function for this
  
  //   cout << "starts interquartile" << endl;
  //   cout << "string_project=" << string_project << endl;
  
  //   cout << "extension_low_histogram_shape=" << extension_low_histogram_shape << endl;
  //   cout << "extension_high_histogram_shape=" << extension_high_histogram_shape << endl;

  //to prevent problems of many peaks in the relative effect
  int nb_bins_histogram_shape_fine_bins=(int)((extension_low_histogram_shape+extension_high_histogram_shape)/0.001); //1 MeV, allow to measure bias of typically 10 MeV
  //  int nb_bins_histogram_shape_fine_bins=(int)((extension_low_histogram_shape+extension_high_histogram_shape)/0.01); //10 MeV, allow to measure bias of typically 10 MeV
  //  int nb_bins_histogram_shape_fine_bins=(int)((extension_low_histogram_shape+extension_high_histogram_shape)/0.100); //100 MeV, allow to measure bias of typically 10 MeV
  
//   cout << "nb_bins_histogram_shape_fine_bins=" << nb_bins_histogram_shape_fine_bins << endl;
//   cout << "left=" << mass_resonance_finalDV-extension_low_histogram_shape << endl;
//   cout << "right=" << mass_resonance_finalDV+extension_high_histogram_shape << endl;

  //to do : move to TH1D

  hist_nominal_fine_bins=new TH1D("hist_nominal_fine_bins","hist_nominal_fine_bins",nb_bins_histogram_shape_fine_bins,mass_resonance_finalDV-extension_low_histogram_shape,mass_resonance_finalDV+extension_high_histogram_shape);
  hist_nominal_fine_bins->SetLineColor(kGreen+2);

  
  //  cout << "hist_nominal_fine_bins->GetBinWidth(1)=" << hist_nominal_fine_bins->GetBinWidth(1) << endl;
  //  exit(1);

  TH1D *hist_syst_fine_bins=new TH1D("hist_syst_fine_bins","hist_syst_fine_bins",nb_bins_histogram_shape_fine_bins,mass_resonance_finalDV-extension_low_histogram_shape,mass_resonance_finalDV+extension_high_histogram_shape);
  hist_syst_fine_bins->SetLineColor(kBlue+2);

  //  cout << "hist_syst_fine_bins->GetBinWidth(1)=" << hist_syst_fine_bins->GetBinWidth(1) << endl;


  current_tree_nominal->Project("hist_nominal_fine_bins",m_string_observable_shape.c_str(),string_project.c_str());
  hist_nominal_fine_bins->Scale(1./hist_nominal_fine_bins->Integral(0,hist_nominal_fine_bins->GetNbinsX()+1));

  current_tree_syst->Project("hist_syst_fine_bins",m_string_observable_shape.c_str(),string_project.c_str());
  hist_syst_fine_bins->Scale(1./hist_syst_fine_bins->Integral(0,hist_syst_fine_bins->GetNbinsX()+1));
  
  //    variante, independent of bins : https://root.cern.ch/root/roottalk/roottalk01/3646.html
  
  rel_effect_position_shape=100.*((hist_syst_fine_bins->GetMean()/hist_nominal_fine_bins->GetMean())-1);

  //to do : manage better all cases of fully correlated
  if (Return_object_given_systematic(string_systematic)=="theory") {
    cout << "this systematic is theory" << endl;
    
    err_rel_effect_position_shape=get_err_rel_effect_yield_fully_correlated(hist_nominal_fine_bins->GetMean(),
									    hist_syst_fine_bins->GetMean(),
									    hist_nominal_fine_bins->GetMeanError(),
									    hist_syst_fine_bins->GetMeanError());
    cout << "err fully correlated=" << err_rel_effect_position_shape << endl;
  }
  else {
    err_rel_effect_position_shape=100.*fabs(hist_syst_fine_bins->GetMean()/hist_nominal_fine_bins->GetMean())*sqrt(
														   pow(hist_nominal_fine_bins->GetMeanError()/hist_nominal_fine_bins->GetMean(),2)
														   +
														   pow(hist_syst_fine_bins->GetMeanError()/hist_syst_fine_bins->GetMean(),2)
														   );
  }




  /*
  for (int index_bin=1;index_bin<=hist_nominal_fine_bins->GetNbinsX();index_bin++) {
    cout << "index_bin=" << index_bin << ", hist_nominal_fine_bins->GetBinCenter()=" << hist_nominal_fine_bins->GetBinCenter(index_bin) << ", value=" << hist_nominal_fine_bins->GetBinContent(index_bin) << ", error=" << hist_nominal_fine_bins->GetBinError(index_bin) << endl;
  }
  */

  //cout << "string_project=" << string_project << endl;

  //   for (int index_bin=1;index_bin<=hist_cumulative_nominal->GetNbinsX();index_bin++) {
  //     cout << "index_bin=" << index_bin << ", hist_cumulative_nominal->GetBinCenter()=" << hist_cumulative_nominal->GetBinCenter(index_bin) << ", value=" << hist_cumulative_nominal->GetBinContent(index_bin) << ", error=" << hist_cumulative_nominal->GetBinError(index_bin) << endl;
  //   }


  //  cout << "start creation of cumulative" << endl;

  //TH1::GetCumulative is not managing the error, so do everything by hand : faster than using Cumulative and then filling the error
  
  TH1D *hist_cumulative_nominal;

  hist_cumulative_nominal=new TH1D("hist_cumulative_nominal","hist_cumulative_nominal",nb_bins_histogram_shape_fine_bins,mass_resonance_finalDV-extension_low_histogram_shape,mass_resonance_finalDV+extension_high_histogram_shape);
  hist_cumulative_nominal->SetLineColor(kGreen+2);

  
  TH1D *hist_cumulative_syst=new TH1D("hist_cumulative_syst","hist_cumulative_syst",nb_bins_histogram_shape_fine_bins,mass_resonance_finalDV-extension_low_histogram_shape,mass_resonance_finalDV+extension_high_histogram_shape);
  hist_cumulative_syst->SetLineColor(kBlue+2);

  double Sumw_up_to_current_bin_nominal=0;
  double Sumw2_up_to_current_bin_nominal=0;
  double Sumw_up_to_current_bin_syst=0;
  double Sumw2_up_to_current_bin_syst=0;
  
  for (int index_bin=1;index_bin<=hist_cumulative_nominal->GetNbinsX();index_bin++) { //nb of bins for systematics is the same by construction
    Sumw_up_to_current_bin_nominal+=hist_nominal_fine_bins->GetBinContent(index_bin);
    Sumw2_up_to_current_bin_nominal+=pow(hist_nominal_fine_bins->GetBinError(index_bin),2);

    Sumw_up_to_current_bin_syst+=hist_syst_fine_bins->GetBinContent(index_bin);
    Sumw2_up_to_current_bin_syst+=pow(hist_syst_fine_bins->GetBinError(index_bin),2);

    hist_cumulative_nominal->SetBinContent(index_bin,Sumw_up_to_current_bin_nominal);
    hist_cumulative_nominal->SetBinError(index_bin,sqrt(Sumw2_up_to_current_bin_nominal));

    hist_cumulative_syst->SetBinContent(index_bin,Sumw_up_to_current_bin_syst);
    hist_cumulative_syst->SetBinError(index_bin,sqrt(Sumw2_up_to_current_bin_syst));
    
    //    cout << "index_bin=" << index_bin << ", hist_cumulative_nominal->GetBinCenter()=" << hist_cumulative_nominal->GetBinCenter(index_bin) << ", value=" << hist_cumulative_nominal->GetBinContent(index_bin) << ", error=" << hist_cumulative_nominal->GetBinError(index_bin) << endl;
  }

  //interquartile : for spread
  //-----
  vector <double> vec_quantile_0_25_nominal=return_intersection(hist_cumulative_nominal,0.25);
  vector <double> vec_quantile_0_25_syst=return_intersection(hist_cumulative_syst,0.25);
  //-----  
  //   cout << "vec_quantile_0_25_nominal[0]=" << vec_quantile_0_25_nominal[0] << endl;
  //   cout << "vec_quantile_0_25_nominal[1]=" << vec_quantile_0_25_nominal[1] << endl;
  //   cout << "vec_quantile_0_25_nominal[2]=" << vec_quantile_0_25_nominal[2] << endl;
  
  //   cout << "vec_quantile_0_25_syst[0]=" << vec_quantile_0_25_syst[0] << endl;
  //   cout << "vec_quantile_0_25_syst[1]=" << vec_quantile_0_25_syst[1] << endl;
  //   cout << "vec_quantile_0_25_syst[2]=" << vec_quantile_0_25_syst[2] << endl;
  //-----
  double Q1_0_25_nominal=vec_quantile_0_25_nominal[0];
  double err_Q1_0_25_nominal=fabs(vec_quantile_0_25_nominal[0]-vec_quantile_0_25_nominal[1]);
  if (fabs(vec_quantile_0_25_nominal[2]-vec_quantile_0_25_nominal[0])>err_Q1_0_25_nominal)
    err_Q1_0_25_nominal=fabs(vec_quantile_0_25_nominal[2]-vec_quantile_0_25_nominal[0]);
  
  vec_quantile_0_25_nominal.clear();

  //add in quadrature the bin width
  err_Q1_0_25_nominal=sqrt(pow(err_Q1_0_25_nominal,2)+pow(hist_cumulative_nominal->GetBinWidth(1),2));
  //-----
  double Q1_0_25_syst=vec_quantile_0_25_syst[0];
  double err_Q1_0_25_syst=fabs(vec_quantile_0_25_syst[0]-vec_quantile_0_25_syst[1]);
  if (fabs(vec_quantile_0_25_syst[2]-vec_quantile_0_25_syst[0])>err_Q1_0_25_syst)
    err_Q1_0_25_syst=fabs(vec_quantile_0_25_syst[2]-vec_quantile_0_25_syst[0]);
  
  vec_quantile_0_25_syst.clear();

  //add in quadrature the bin width
  err_Q1_0_25_syst=sqrt(pow(err_Q1_0_25_syst,2)+pow(hist_cumulative_syst->GetBinWidth(1),2));
  //-----
  vector <double> vec_quantile_0_75_nominal=return_intersection(hist_cumulative_nominal,0.75);
  vector <double> vec_quantile_0_75_syst=return_intersection(hist_cumulative_syst,0.75);
  //-----
  
  //   cout << "vec_quantile_0_75_nominal[0]=" << vec_quantile_0_75_nominal[0] << endl;
  //   cout << "vec_quantile_0_75_nominal[1]=" << vec_quantile_0_75_nominal[1] << endl;
  //   cout << "vec_quantile_0_75_nominal[2]=" << vec_quantile_0_75_nominal[2] << endl;
  
  //   cout << "vec_quantile_0_75_syst[0]=" << vec_quantile_0_75_syst[0] << endl;
  //   cout << "vec_quantile_0_75_syst[1]=" << vec_quantile_0_75_syst[1] << endl;
  //   cout << "vec_quantile_0_75_syst[2]=" << vec_quantile_0_75_syst[2] << endl;
  //-----
  double Q3_0_75_nominal=vec_quantile_0_75_nominal[0];
  double err_Q3_0_75_nominal=fabs(vec_quantile_0_75_nominal[0]-vec_quantile_0_75_nominal[1]);
  if (fabs(vec_quantile_0_75_nominal[2]-vec_quantile_0_75_nominal[0])>err_Q3_0_75_nominal)
    err_Q3_0_75_nominal=fabs(vec_quantile_0_75_nominal[2]-vec_quantile_0_75_nominal[0]);
  
  vec_quantile_0_75_nominal.clear();

  //add in quadrature the bin width
  err_Q3_0_75_nominal=sqrt(pow(err_Q3_0_75_nominal,2)+pow(hist_cumulative_nominal->GetBinWidth(1),2));
  //-----
  double Q3_0_75_syst=vec_quantile_0_75_syst[0];
  double err_Q3_0_75_syst=fabs(vec_quantile_0_75_syst[0]-vec_quantile_0_75_syst[1]);
  if (fabs(vec_quantile_0_75_syst[2]-vec_quantile_0_75_syst[0])>err_Q3_0_75_syst)
    err_Q3_0_75_syst=fabs(vec_quantile_0_75_syst[2]-vec_quantile_0_75_syst[0]);
  
  vec_quantile_0_75_syst.clear();

  //add in quadrature the bin width
  err_Q3_0_75_syst=sqrt(pow(err_Q3_0_75_syst,2)+pow(hist_cumulative_syst->GetBinWidth(1),2));
  //-----

  IQR_nominal=Q3_0_75_nominal-Q1_0_25_nominal;
  
  err_IQR_nominal=sqrt(err_Q1_0_25_nominal*err_Q1_0_25_nominal+err_Q3_0_75_nominal*err_Q3_0_75_nominal);
  
  //  double Q1_0_25_syst=hist_cumulative_syst->GetBinCenter(hist_cumulative_syst->FindFirstBinAbove(0.25));
  //  double Q3_0_75_syst=hist_cumulative_syst->GetBinCenter(hist_cumulative_syst->FindFirstBinAbove(0.75));
  IQR_syst=Q3_0_75_syst-Q1_0_25_syst;
  
  err_IQR_syst=sqrt(err_Q1_0_25_syst*err_Q1_0_25_syst+err_Q3_0_75_syst*err_Q3_0_75_syst);
  
  rel_effect_spread_shape=100.*((IQR_syst/IQR_nominal)-1);

  //to do : do better all cases of fully correlated

  if (Return_object_given_systematic(string_systematic)=="theory") {
    cout << "this systematic is theory" << endl;

    err_rel_effect_spread_shape=get_err_rel_effect_yield_fully_correlated(IQR_nominal,
									  IQR_syst,
									  err_IQR_nominal,
									  err_IQR_syst);
    cout << "err fully correlated=" << err_rel_effect_spread_shape << endl;
  }
  else {
    //this formula assumes no correlation
    err_rel_effect_spread_shape=100.*fabs(IQR_syst/IQR_nominal)*sqrt(pow(err_IQR_syst/IQR_syst,2)+pow(err_IQR_nominal/IQR_nominal,2));
    cout << "err assuming no correlation=" << err_rel_effect_spread_shape << endl;
  }

//   cout << "Q1_0_25_nominal=" << Q1_0_25_nominal << endl;
//   cout << "Q3_0_75_nominal=" << Q3_0_75_nominal << endl;
//   cout << "IQR_nominal=" << IQR_nominal << " +/- " << err_IQR_nominal << endl;
  
//   cout << endl;
//   cout << "Q1_0_25_syst=" << Q1_0_25_syst << endl;
//   cout << "Q3_0_75_syst=" << Q3_0_75_syst << endl;
//   cout << "IQR_syst=" << IQR_syst << " +/- " << err_IQR_syst << endl;

//   cout << endl;
//   cout << "rel_effect_spread_shape=" << rel_effect_spread_shape << " +/- " << err_rel_effect_spread_shape << endl;
  //---------------------------------
  //Illustration

  double bin_width_illustration=1.;

  if (string_finalDV=="m_yybb_tilde" && string_sample.find("aMCnloHwpp_hh_yybb")!=string::npos)
    bin_width_illustration=10.; //do not take 15, due to extension chosen : not rounded
  else if (string_finalDV=="m_bb")
    bin_width_illustration=5.;
  
  int nb_bins_histogram_shape_illustration=(int)((extension_low_histogram_shape+extension_high_histogram_shape)/bin_width_illustration);
  
  TH1D *hist_nominal_illustration=new TH1D("hist_nominal_illustration","hist_nominal_illustration",nb_bins_histogram_shape_illustration,mass_resonance_finalDV-extension_low_histogram_shape,mass_resonance_finalDV+extension_high_histogram_shape);

  hist_nominal_illustration->SetLineColor(kGreen+2);

  TH1D *hist_syst_illustration=new TH1D("hist_syst_illustration","hist_syst_illustration",nb_bins_histogram_shape_illustration,mass_resonance_finalDV-extension_low_histogram_shape,mass_resonance_finalDV+extension_high_histogram_shape);
  hist_syst_illustration->SetLineColor(kBlue+2);
  
  current_tree_nominal->Project("hist_nominal_illustration",m_string_observable_shape.c_str(),string_project.c_str());
  current_tree_syst->Project("hist_syst_illustration",m_string_observable_shape.c_str(),string_project.c_str());
  
  TH1F *hist_dummy;

  //  char buffer[50]; //too short ?
  //?static char buffer[100]; //too short ?
  //char buffer[100]; //too short ?
  char buffer[200]; //too short ?
  
  TCanvas *canvas_hist_illustration=new TCanvas("canvas_hist_illustration","canvas_hist_illustration",800,600);
  //canvas_hist_illustration->SetRightMargin(0.01); //too short for sure
  canvas_hist_illustration->SetRightMargin(0.03);
  canvas_hist_illustration->SetTopMargin(0.01);
  
  hist_dummy=canvas_hist_illustration->DrawFrame(hist_nominal_illustration->GetBinLowEdge(1),1e-6,hist_nominal_illustration->GetBinLowEdge(hist_nominal_illustration->GetNbinsX())+hist_nominal_illustration->GetBinWidth(1),hist_nominal_illustration->GetMaximum()*1.2); //epsilon is to avoid for roofit the markers
  hist_dummy->GetXaxis()->SetTitle((string_latex_observable_shape_no_units+" "+string_latex_observable_shape_units).c_str());
  sprintf(buffer,"Events / %4.2f [GeV]",hist_nominal_illustration->GetBinWidth(1));
  hist_dummy->GetYaxis()->SetTitle(buffer);
  hist_dummy->GetYaxis()->SetTitleOffset(1.45);
  hist_dummy->Draw();
  
  vector<double> vec_x_nominal;
  vector<double> vec_y_nominal;
  vector<double> vec_x_syst;
  vector<double> vec_y_syst;

  vec_x_nominal.push_back(Q1_0_25_nominal);
  vec_y_nominal.push_back(hist_nominal_illustration->GetBinContent(hist_nominal_illustration->FindBin(Q1_0_25_nominal)));

  vec_x_syst.push_back(Q1_0_25_syst);
  vec_y_syst.push_back(hist_syst_illustration->GetBinContent(hist_syst_illustration->FindBin(Q1_0_25_syst)));
    
  for (int index_bin_shape_illustration=1;index_bin_shape_illustration<=nb_bins_histogram_shape_illustration;index_bin_shape_illustration++) {
    if (hist_nominal_illustration->GetBinCenter(index_bin_shape_illustration)-0.5*hist_nominal_illustration->GetBinWidth(1)>Q1_0_25_nominal && hist_nominal_illustration->GetBinCenter(index_bin_shape_illustration)-0.5*hist_nominal_illustration->GetBinWidth(1)<Q3_0_75_nominal) {
      vec_x_nominal.push_back(hist_nominal_illustration->GetBinCenter(index_bin_shape_illustration)-0.5*hist_nominal_illustration->GetBinWidth(1));
      vec_y_nominal.push_back(hist_nominal_illustration->GetBinContent(index_bin_shape_illustration));
    }
      
    if (hist_syst_illustration->GetBinCenter(index_bin_shape_illustration)-0.5*hist_syst_illustration->GetBinWidth(1)>Q1_0_25_syst && hist_syst_illustration->GetBinCenter(index_bin_shape_illustration)-0.5*hist_syst_illustration->GetBinWidth(1)<Q3_0_75_syst) {
      vec_x_syst.push_back(hist_syst_illustration->GetBinCenter(index_bin_shape_illustration)-0.5*hist_syst_illustration->GetBinWidth(1));
      vec_y_syst.push_back(hist_syst_illustration->GetBinContent(index_bin_shape_illustration));
    }
  }

  vec_x_nominal.push_back(Q3_0_75_nominal);
  vec_y_nominal.push_back(hist_nominal_illustration->GetBinContent(hist_nominal_illustration->FindBin(Q3_0_75_nominal)));
    
  vec_x_syst.push_back(Q3_0_75_syst);
  vec_y_syst.push_back(hist_syst_illustration->GetBinContent(hist_syst_illustration->FindBin(Q3_0_75_syst)));

  TH1D *hist_nominal_illustration_shaded=new TH1D("hist_nominal_illustration_shaded","hist_nominal_illustration_shaded",vec_x_nominal.size()-1,vec_x_nominal.data());
  hist_nominal_illustration_shaded->SetLineColor(kGreen+2);
  for (unsigned int index_bin_nominal_illustration=1;index_bin_nominal_illustration<=vec_x_nominal.size();index_bin_nominal_illustration++)
    hist_nominal_illustration_shaded->SetBinContent(index_bin_nominal_illustration,vec_y_nominal[index_bin_nominal_illustration-1]);
  hist_nominal_illustration_shaded->SetFillStyle(3004);
  hist_nominal_illustration_shaded->SetFillColor(kGreen+2);
  hist_nominal_illustration_shaded->Draw("fsame");

  TH1D *hist_syst_illustration_shaded=new TH1D("hist_syst_illustration_shaded","hist_syst_illustration_shaded",vec_x_syst.size()-1,vec_x_syst.data());
  hist_syst_illustration_shaded->SetLineColor(kBlue+2);
  for (unsigned int index_bin_syst_illustration=1;index_bin_syst_illustration<=vec_x_syst.size();index_bin_syst_illustration++)
    hist_syst_illustration_shaded->SetBinContent(index_bin_syst_illustration,vec_y_syst[index_bin_syst_illustration-1]);
  hist_syst_illustration_shaded->SetFillStyle(3005);
  hist_syst_illustration_shaded->SetFillColor(kBlue+2);
  hist_syst_illustration_shaded->Draw("fsame");
  
  hist_nominal_illustration->Draw("histsame");
  hist_syst_illustration->Draw("histsame");

  canvas_hist_illustration->RedrawAxis();

  //  cout << "clear vector" << endl;
  vec_x_nominal.clear();
  vec_y_nominal.clear();
  vec_x_syst.clear();
  vec_y_syst.clear();
  //  cout << "cleared vector" << endl;

  float horizontal_position=0.15;
    
  TLatex latex;
  latex.SetTextColor(kBlack);
  latex.SetNDC();
  latex.SetTextSize(0.04); //0.045 is std
  latex.SetTextFont(72);
  latex.DrawLatex(horizontal_position,0.92,"ATLAS");
  latex.SetTextFont(42); //put back the font
  latex.DrawLatex(horizontal_position+0.1,0.92,"internal");

  latex.DrawLatex(horizontal_position,0.84,(get_string_ECM_luminosity(string_campaign_MxAOD)).c_str());

  //  latex.SetTextSize(0.027); //0.034 too small for HH non resonant
  latex.SetTextSize(0.016); //0.034 too small for HH non resonant

  latex.SetTextColor(kBlack);
		  
  latex.DrawLatex(horizontal_position,0.78,string_sample.c_str());
    
  latex.SetTextSize(0.018);
  latex.DrawLatex(horizontal_position,0.73,(string_systematic+suffix_asymmetry_systematic).c_str());
  latex.SetTextSize(0.03);
  
  latex.DrawLatex(horizontal_position,0.63,string_category.c_str());
  //-----
  //left part of the screen

  if (string_method_partition_events=="bootstrap" || string_method_partition_events=="jacknife") {
    sprintf(buffer,"toy number : %d",index_toy);
    latex.DrawLatex(horizontal_position,0.58,buffer);
  }

  latex.SetTextColor(kGreen+2);
  sprintf(buffer,"nominal : <%s>=%4.2f #pm %4.2f %s",string_latex_observable_shape_no_units.c_str(),hist_nominal_fine_bins->GetMean(),hist_nominal_fine_bins->GetMeanError(),string_latex_observable_shape_units.c_str());
  latex.DrawLatex(0.65,0.65,buffer);
  latex.SetTextColor(kBlue+2);
  sprintf(buffer,"syst : <%s>=%4.2f #pm %4.2f %s",string_latex_observable_shape_no_units.c_str(),hist_syst_fine_bins->GetMean(),hist_syst_fine_bins->GetMeanError(),string_latex_observable_shape_units.c_str());
  latex.DrawLatex(0.65,0.60,buffer);
    
  latex.SetTextColor(kRed);
  sprintf(buffer,"rel effect (%%) #mu: %4.2f #pm %4.2f",rel_effect_position_shape,err_rel_effect_position_shape);
  latex.DrawLatexNDC(0.65,0.55,buffer);

  char buffer_index_toy[7]=""; //ok for sure for sure up to 5 digits + '\0'

  if (string_method_partition_events=="bootstrap" || string_method_partition_events=="jacknife") {
    sprintf(buffer_index_toy,"_%d",index_toy);
  }

  cout << "string_systematic=" << string_systematic << endl;

  cout << "in tool_syst_shape::ComputeAndPlot_Syst_shape_From_Mean_and_Interquartile, phase 1" << endl;

  string string_saveas;
  
  string_saveas=string_path+string_rel_path_shape+"figures/";
  string_saveas+=string_process;
  string_saveas+="/";
  string_saveas+=string_campaign_MxAOD;
  string_saveas+="/";
  string_saveas+=string_category;
  string_saveas+="/";
  string_saveas+=m_string_observable_shape;
  string_saveas+="/";
  string_saveas+=string_systematic;
  string_saveas+="/";
  string_saveas+="plot_syst_shape_";
  
  string_saveas+=string_method_partition_events;
  string_saveas+="_illustration_";

  //one could not have file too long, else problem with linux : cannot open image file
  string_saveas+=m_string_observable_shape+vec_nature_syst_components_sym_asym[index_sym_asym]+"_"+string_method_syst_shape+"_toy"+buffer_index_toy+".png";

  cout << "string_saveas=" << string_saveas << endl;

  //  cout << "canvas_hist_illustration=" << canvas_hist_illustration << endl;

  if (string_method_partition_events=="individual" || (string_method_partition_events!="individual" && index_toy<10))
    canvas_hist_illustration->SaveAs(string_saveas.c_str());

  delete hist_dummy;
  //-----------------------------------------------
  TCanvas *canvas_hist_cumulative=new TCanvas("canvas_hist_cumulative","canvas_hist_cumulative",800,600);
  canvas_hist_cumulative->SetRightMargin(0.03); //too short for sure
  canvas_hist_cumulative->SetTopMargin(0.01);
    
  hist_dummy=canvas_hist_cumulative->DrawFrame(hist_cumulative_nominal->GetBinLowEdge(1),1e-6,hist_cumulative_nominal->GetBinLowEdge(hist_cumulative_nominal->GetNbinsX())+hist_cumulative_nominal->GetBinWidth(1),hist_cumulative_nominal->GetMaximum()*1.1); //epsilon is to avoid for roofit the markers

  hist_dummy->GetXaxis()->SetTitle((string_latex_observable_shape_no_units+" "+string_latex_observable_shape_units).c_str());

  sprintf(buffer,"Events / %8.4f [GeV]",hist_nominal_fine_bins->GetBinWidth(1));
  hist_dummy->GetYaxis()->SetTitle(buffer);
  hist_dummy->GetYaxis()->SetTitleOffset(1.45);
  hist_dummy->Draw();
  hist_cumulative_nominal->Draw("Esame");
  hist_cumulative_syst->Draw("Esame");

  TLine *line_25percent=new TLine(hist_cumulative_nominal->GetBinLowEdge(1),0.25,hist_cumulative_nominal->GetBinLowEdge(hist_cumulative_nominal->GetNbinsX())+hist_cumulative_nominal->GetBinWidth(1),0.25);
  line_25percent->SetLineStyle(kDotted);
  line_25percent->Draw();

  TLine *line_75percent=new TLine(hist_cumulative_nominal->GetBinLowEdge(1),0.75,hist_cumulative_nominal->GetBinLowEdge(hist_cumulative_nominal->GetNbinsX())+hist_cumulative_nominal->GetBinWidth(1),0.75);
  line_75percent->SetLineStyle(kDotted);
  line_75percent->Draw();

  TLine *line_observable_nominal_for_25percent=new TLine(Q1_0_25_nominal,0,Q1_0_25_nominal,hist_dummy->GetYaxis()->GetXmax());
  line_observable_nominal_for_25percent->SetLineColor(kGreen+2);
  line_observable_nominal_for_25percent->SetLineStyle(kDashed);
  line_observable_nominal_for_25percent->Draw();

  TLine *line_observable_nominal_for_75percent=new TLine(Q3_0_75_nominal,0,Q3_0_75_nominal,hist_dummy->GetYaxis()->GetXmax());
  line_observable_nominal_for_75percent->SetLineColor(kGreen+2);
  line_observable_nominal_for_75percent->SetLineStyle(kDashed);
  line_observable_nominal_for_75percent->Draw();

  TLine *line_observable_syst_for_25percent=new TLine(Q1_0_25_syst,0,Q1_0_25_syst,hist_dummy->GetYaxis()->GetXmax());
  line_observable_syst_for_25percent->SetLineColor(kBlue+2);
  line_observable_syst_for_25percent->SetLineStyle(kDashed);
  line_observable_syst_for_25percent->Draw();
    
  TLine *line_observable_syst_for_75percent=new TLine(Q3_0_75_syst,0,Q3_0_75_syst,hist_dummy->GetYaxis()->GetXmax());
  line_observable_syst_for_75percent->SetLineColor(kBlue+2);
  line_observable_syst_for_75percent->SetLineStyle(kDashed);
  line_observable_syst_for_75percent->Draw();

  latex.SetNDC(0);
  latex.SetTextSize(0.04); //0.045 is std
  latex.SetTextColor(kBlack);
  latex.SetTextFont(42); //put back the font

  float epsilon=0.01;

  latex.DrawLatex(hist_cumulative_nominal->GetBinLowEdge(1)+0.375*(hist_cumulative_nominal->GetBinCenter(hist_cumulative_nominal->GetNbinsX())+hist_cumulative_nominal->GetBinWidth(1)-hist_cumulative_nominal->GetBinLowEdge(1)),0.25+epsilon,"25 %");
  latex.DrawLatex(hist_cumulative_nominal->GetBinLowEdge(1)+0.375*(hist_cumulative_nominal->GetBinCenter(hist_cumulative_nominal->GetNbinsX())+hist_cumulative_nominal->GetBinWidth(1)-hist_cumulative_nominal->GetBinLowEdge(1)),0.75+epsilon,"75 %");
    
  horizontal_position=0.15;
    
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
  //latex.SetTextSize(0.04);
  //  latex.SetTextSize(0.03);
  latex.SetTextSize(0.025);

  latex.DrawLatex(horizontal_position,0.63,string_category.c_str());

  //-----
  //left part of the screen
    
  if (string_method_partition_events=="bootstrap" || string_method_partition_events=="jacknife") {
    sprintf(buffer,"toy number : %d",index_toy);
    latex.DrawLatex(horizontal_position,0.58,buffer);
  }

  latex.SetTextColor(kGreen+2);
  sprintf(buffer,"nominal : Q3-Q1=%4.2f #pm %4.2f %s",IQR_nominal,err_IQR_nominal,string_latex_observable_shape_units.c_str());
  latex.DrawLatex(0.65,0.5,buffer);
  latex.SetTextColor(kBlue+2);
  sprintf(buffer,"syst : Q3-Q1=%4.2f #pm %4.2f %s",IQR_syst,err_IQR_syst,string_latex_observable_shape_units.c_str());
  latex.DrawLatex(0.65,0.45,buffer);

  //  cout << "rel_effect_spread_shape=" << rel_effect_spread_shape << endl;
  //  cout << "err_rel_effect_spread_shape=" << err_rel_effect_spread_shape << endl;

  latex.SetTextColor(kRed);
  sprintf(buffer,"rel effect (%%) #sigma: %4.2f #pm %4.2f",rel_effect_spread_shape,err_rel_effect_spread_shape);
  latex.DrawLatexNDC(0.65,0.40,buffer);

  //  cout << "buffer=" << buffer << endl;

  string_saveas=string_path+string_rel_path_shape+"figures/";
  string_saveas+=string_process;
  string_saveas+="/";
  string_saveas+=string_campaign_MxAOD;
  string_saveas+="/";
  string_saveas+=string_category;
  string_saveas+="/";
  string_saveas+=m_string_observable_shape;
  string_saveas+="/";
  string_saveas+=string_systematic;
  string_saveas+="/";
  string_saveas+="plot_syst_shape_";

  string_saveas+=string_method_partition_events;
  string_saveas+="_cumulative_";
  
  string_saveas+=m_string_observable_shape+vec_nature_syst_components_sym_asym[index_sym_asym]+"_"+string_method_syst_shape+"_toy"+buffer_index_toy+".png";

  if (string_method_partition_events=="individual" || (string_method_partition_events!="individual" && index_toy<10))
    canvas_hist_cumulative->SaveAs(string_saveas.c_str());

  delete hist_dummy;

  delete hist_nominal_fine_bins;
  delete hist_cumulative_nominal;
  delete hist_nominal_illustration;
  delete hist_nominal_illustration_shaded;

  delete hist_syst_fine_bins;
  delete hist_cumulative_syst;
  delete hist_syst_illustration;
  delete hist_syst_illustration_shaded;

  /*
  if (!do_read_tree_nominal_shape_once)
    delete hist_nominal;
  */

  delete hist_nominal;
  
  cout << "delete hist_syst" << endl;
  delete hist_syst;

  cout << "delete canvas_hist_illustration" << endl;

  delete canvas_hist_illustration;
  delete canvas_hist_cumulative;

  cout << "in tool_syst_shape::ComputeAndPlot_Syst_shape_From_Mean_and_Interquartile, phase end" << endl;
}
//=============================================================================================================================================================================================
void tool_syst_shape::StoreResults(string string_category,string string_campaign_MxAOD,string string_systematic)
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

  string_save_results_toys+=m_string_observable_shape;
  string_save_results_toys+="/";

  string_save_results_toys+=string_systematic;
  string_save_results_toys+="/";

  if (string_method_syst_shape=="fit")
    string_save_results_toys+="ShapeFrom_fit_";
  else if (string_method_syst_shape=="mean_IQR")
    string_save_results_toys+="ShapeFrom_mean_IQR_";
  
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

  int internal_converged;
  int internal_status_nominal;      
  int internal_status_syst;
  double internal_chi2_nominal;
  int internal_ndof_nominal;
  double internal_chi2_syst;
  int internal_ndof_syst;

  //-------------------------
  //DoubleCrystalBall
  double internal_muCB_nominal;
  double internal_err_muCB_nominal;
  double internal_sigmaCB_nominal;
  double internal_err_sigmaCB_nominal;
  double internal_alphaCB_Low_nominal;
  double internal_err_alphaCB_Low_nominal;
  double internal_nCB_Low_nominal;
  double internal_err_nCB_Low_nominal;
  double internal_alphaCB_High_nominal;
  double internal_err_alphaCB_High_nominal;
  double internal_nCB_High_nominal;
  double internal_err_nCB_High_nominal;
  double internal_muCB_syst;
  double internal_err_muCB_syst;
  double internal_sigmaCB_syst;
  double internal_err_sigmaCB_syst;
  double internal_alphaCB_Low_syst;      
  double internal_err_alphaCB_Low_syst;
  double internal_nCB_Low_syst;
  double internal_err_nCB_Low_syst;
  double internal_alphaCB_High_syst;
  double internal_err_alphaCB_High_syst;
  double internal_nCB_High_syst;
  double internal_err_nCB_High_syst;
  //-------------------------
  //ExpGaussExp

  double internal_muGauss_nominal;
  double internal_err_muGauss_nominal;
  double internal_sigmaGauss_nominal;
  double internal_err_sigmaGauss_nominal;
  double internal_slopeExp_Low_nominal;
  double internal_err_slopeExp_Low_nominal;
  double internal_slopeExp_High_nominal;
  double internal_err_slopeExp_High_nominal;

  double internal_muGauss_syst;
  double internal_err_muGauss_syst;
  double internal_sigmaGauss_syst;
  double internal_err_sigmaGauss_syst;
  double internal_slopeExp_Low_syst;
  double internal_err_slopeExp_Low_syst;
  double internal_slopeExp_High_syst;
  double internal_err_slopeExp_High_syst;
  //-------------------------
  //Bukin

  double internal_muBukin_nominal;
  double internal_err_muBukin_nominal;
  double internal_sigmaBukin_nominal;
  double internal_err_sigmaBukin_nominal;
  double internal_xiBukin_nominal;
  double internal_err_xiBukin_nominal;
  double internal_rho1Bukin_nominal;
  double internal_err_rho1Bukin_nominal;
  double internal_rho2Bukin_nominal;
  double internal_err_rho2Bukin_nominal;

  double internal_muBukin_syst;
  double internal_err_muBukin_syst;
  double internal_sigmaBukin_syst;
  double internal_err_sigmaBukin_syst;
  double internal_xiBukin_syst;
  double internal_err_xiBukin_syst;
  double internal_rho1Bukin_syst;
  double internal_err_rho1Bukin_syst;
  double internal_rho2Bukin_syst;
  double internal_err_rho2Bukin_syst;
  //-------------------------
  TBranch *b_internal_index_toy;
  TBranch *b_internal_converged;
  TBranch *b_internal_status_nominal;
  TBranch *b_internal_status_syst;
  TBranch *b_internal_chi2_nominal;
  TBranch *b_internal_ndof_nominal;
  TBranch *b_internal_chi2_syst;
  TBranch *b_internal_ndof_syst;
  //-----
  TBranch *b_internal_muCB_nominal;
  TBranch *b_internal_err_muCB_nominal;
  TBranch *b_internal_sigmaCB_nominal;
  TBranch *b_err_internal_sigmaCB_nominal;
  TBranch *b_internal_alphaCB_Low_nominal;
  TBranch *b_internal_err_alphaCB_Low_nominal;
  TBranch *b_internal_nCB_Low_nominal;
  TBranch *b_internal_err_nCB_Low_nominal;
  TBranch *b_internal_alphaCB_High_nominal;
  TBranch *b_internal_err_alphaCB_High_nominal;
  TBranch *b_internal_nCB_High_nominal;
  TBranch *b_internal_err_nCB_High_nominal;

  TBranch *b_internal_muCB_syst;
  TBranch *b_internal_err_muCB_syst;
  TBranch *b_internal_sigmaCB_syst;
  TBranch *b_internal_err_sigmaCB_syst;
  TBranch *b_internal_alphaCB_Low_syst;
  TBranch *b_internal_err_alphaCB_Low_syst;
  TBranch *b_internal_nCB_Low_syst;
  TBranch *b_internal_err_nCB_Low_syst;
  TBranch *b_internal_alphaCB_High_syst;
  TBranch *b_internal_err_alphaCB_High_syst;

  TBranch *b_internal_nCB_High_syst;
  TBranch *b_internal_err_nCB_High_syst;
  //-------------------------
  TBranch *b_internal_muGauss_nominal;
  TBranch *b_internal_err_muGauss_nominal;
  TBranch *b_internal_sigmaGauss_nominal;
  TBranch *b_internal_err_sigmaGauss_nominal;
  TBranch *b_internal_slopeExp_Low_nominal;
  TBranch *b_internal_err_slopeExp_Low_nominal;
  TBranch *b_internal_slopeExp_High_nominal;
  TBranch *b_internal_err_slopeExp_High_nominal;

  TBranch *b_internal_muGauss_syst;
  TBranch *b_internal_err_muGauss_syst;
  TBranch *b_internal_sigmaGauss_syst;
  TBranch *b_internal_err_sigmaGauss_syst;
  TBranch *b_internal_slopeExp_Low_syst;
  TBranch *b_internal_err_slopeExp_Low_syst;
  TBranch *b_internal_slopeExp_High_syst;
  TBranch *b_internal_err_slopeExp_High_syst;
  //-----
  TBranch *b_internal_muBukin_nominal;
  TBranch *b_internal_err_muBukin_nominal;
  TBranch *b_internal_sigmaBukin_nominal;
  TBranch *b_internal_err_sigmaBukin_nominal;
  TBranch *b_internal_xiBukin_nominal;
  TBranch *b_internal_err_xiBukin_nominal;
  TBranch *b_internal_rho1Bukin_nominal;
  TBranch *b_internal_err_rho1Bukin_nominal;
  TBranch *b_internal_rho2Bukin_nominal;
  TBranch *b_internal_err_rho2Bukin_nominal;

  TBranch *b_internal_muBukin_syst;
  TBranch *b_internal_err_muBukin_syst;
  TBranch *b_internal_sigmaBukin_syst;
  TBranch *b_internal_err_sigmaBukin_syst;
  TBranch *b_internal_xiBukin_syst;
  TBranch *b_internal_err_xiBukin_syst;
  TBranch *b_internal_rho1Bukin_syst;
  TBranch *b_internal_err_rho1Bukin_syst;
  TBranch *b_internal_rho2Bukin_syst;
  TBranch *b_internal_err_rho2Bukin_syst;
  //-----
  //for mean/IQR
  double internal_mean_nominal;
  double internal_err_mean_nominal;
  double internal_mean_syst;
  double internal_err_mean_syst;
      
  double internal_IQR_nominal;
  double internal_err_IQR_nominal;
  double internal_IQR_syst;
  double internal_err_IQR_syst;

  TBranch *b_internal_mean_nominal;
  TBranch *b_internal_err_mean_nominal;
  TBranch *b_internal_mean_syst;
  TBranch *b_internal_err_mean_syst;
      
  TBranch *b_internal_IQR_nominal;
  TBranch *b_internal_err_IQR_nominal;
  TBranch *b_internal_IQR_syst;
  TBranch *b_internal_err_IQR_syst;

  b_internal_index_toy=tree_results_toys->Branch("index_toy",&internal_index_toy);
      
  if (string_method_syst_shape=="fit") {
    b_internal_status_nominal=tree_results_toys->Branch("status_nominal",&internal_status_nominal);
    b_internal_status_syst=tree_results_toys->Branch("status_syst",&internal_status_syst);
    b_internal_converged=tree_results_toys->Branch("converged",&internal_converged);
    b_internal_chi2_nominal=tree_results_toys->Branch("chi2_nominal",&internal_chi2_nominal);
    b_internal_ndof_nominal=tree_results_toys->Branch("ndof_nominal",&internal_ndof_nominal);
    b_internal_chi2_syst=tree_results_toys->Branch("chi2_syst",&internal_chi2_syst);
    b_internal_ndof_syst=tree_results_toys->Branch("ndof_syst",&internal_ndof_syst);

    if (string_functional_form=="DoubleCrystalBall") {
      b_internal_muCB_nominal=tree_results_toys->Branch("muCB_nominal",&internal_muCB_nominal);
      b_internal_err_muCB_nominal=tree_results_toys->Branch("err_muCB_nominal",&internal_err_muCB_nominal);
      b_internal_sigmaCB_nominal=tree_results_toys->Branch("sigmaCB_nominal",&internal_sigmaCB_nominal);
      b_err_internal_sigmaCB_nominal=tree_results_toys->Branch("err_sigmaCB_nominal",&internal_err_sigmaCB_nominal);

      b_internal_alphaCB_Low_nominal=tree_results_toys->Branch("alphaCB_Low_nominal",&internal_alphaCB_Low_nominal);	  
      b_internal_err_alphaCB_Low_nominal=tree_results_toys->Branch("err_alphaCB_Low_nominal",&internal_err_alphaCB_Low_nominal);
      b_internal_nCB_Low_nominal=tree_results_toys->Branch("nCB_Low_nominal",&internal_nCB_Low_nominal);
	  
      b_internal_err_nCB_Low_nominal=tree_results_toys->Branch("err_nCB_Low_nominal",&internal_err_nCB_Low_nominal);
      b_internal_alphaCB_High_nominal=tree_results_toys->Branch("alphaCB_High_nominal",&internal_alphaCB_High_nominal);
      b_internal_err_alphaCB_High_nominal=tree_results_toys->Branch("err_alphaCB_High_nominal",&internal_err_alphaCB_High_nominal);
	  
      b_internal_nCB_High_nominal=tree_results_toys->Branch("nCB_High_nominal",&internal_nCB_High_nominal);
      b_internal_err_nCB_High_nominal=tree_results_toys->Branch("err_nCB_High_nominal",&internal_err_nCB_High_nominal);

      b_internal_muCB_syst=tree_results_toys->Branch("muCB_syst",&internal_muCB_syst);
      b_internal_err_muCB_syst=tree_results_toys->Branch("err_muCB_syst",&internal_err_muCB_syst);
      b_internal_sigmaCB_syst=tree_results_toys->Branch("sigmaCB_syst",&internal_sigmaCB_syst);	  
      b_internal_err_sigmaCB_syst=tree_results_toys->Branch("err_sigmaCB_syst",&internal_err_sigmaCB_syst);	  
      b_internal_alphaCB_Low_syst=tree_results_toys->Branch("alphaCB_Low_syst",&internal_alphaCB_Low_syst);
      b_internal_err_alphaCB_Low_syst=tree_results_toys->Branch("err_alphaCB_Low_syst",&internal_err_alphaCB_Low_syst);
      b_internal_nCB_Low_syst=tree_results_toys->Branch("nCB_Low_syst",&internal_nCB_Low_syst);
	  
      b_internal_err_nCB_Low_syst=tree_results_toys->Branch("err_nCB_Low_syst",&internal_err_nCB_Low_syst);
      b_internal_alphaCB_High_syst=tree_results_toys->Branch("alphaCB_High_syst",&internal_alphaCB_High_syst);
      b_internal_err_alphaCB_High_syst=tree_results_toys->Branch("err_alphaCB_High_syst",&internal_err_alphaCB_High_syst);
	  
      b_internal_nCB_High_syst=tree_results_toys->Branch("nCB_High_syst",&internal_nCB_High_syst);
      b_internal_err_nCB_High_syst=tree_results_toys->Branch("err_nCB_High_syst",&internal_err_nCB_High_syst);
    }
    else if (string_functional_form=="ExpGaussExp") {
      b_internal_muGauss_nominal=tree_results_toys->Branch("muGauss_nominal",&internal_muGauss_nominal);
      b_internal_err_muGauss_nominal=tree_results_toys->Branch("err_muGauss_nominal",&internal_err_muGauss_nominal);
      b_internal_sigmaGauss_nominal=tree_results_toys->Branch("sigmaGauss_nominal",&internal_sigmaGauss_nominal);
      b_internal_err_sigmaGauss_nominal=tree_results_toys->Branch("err_sigmaGauss_nominal",&internal_err_sigmaGauss_nominal);
      b_internal_slopeExp_Low_nominal=tree_results_toys->Branch("slopeExp_Low_nominal",&internal_slopeExp_Low_nominal);
      b_internal_err_slopeExp_Low_nominal=tree_results_toys->Branch("err_slopeExp_Low_nominal",&internal_err_slopeExp_Low_nominal);
      b_internal_slopeExp_High_nominal=tree_results_toys->Branch("slopeExp_High_nominal",&internal_slopeExp_High_nominal);
      b_internal_err_slopeExp_High_nominal=tree_results_toys->Branch("err_slopeExp_High_nominal",&internal_err_slopeExp_High_nominal);

      b_internal_muGauss_syst=tree_results_toys->Branch("muGauss_syst",&internal_muGauss_syst);
      b_internal_err_muGauss_syst=tree_results_toys->Branch("err_muGauss_syst",&internal_err_muGauss_syst);
      b_internal_sigmaGauss_syst=tree_results_toys->Branch("sigmaGauss_syst",&internal_sigmaGauss_syst);
      b_internal_err_sigmaGauss_syst=tree_results_toys->Branch("err_sigmaGauss_syst",&internal_err_sigmaGauss_syst);
      b_internal_slopeExp_Low_syst=tree_results_toys->Branch("slopeExp_Low_syst",&internal_slopeExp_Low_syst);
      b_internal_err_slopeExp_Low_syst=tree_results_toys->Branch("err_slopeExp_Low_syst",&internal_err_slopeExp_Low_syst);
      b_internal_slopeExp_High_syst=tree_results_toys->Branch("slopeExp_High_syst",&internal_slopeExp_High_syst);
      b_internal_err_slopeExp_High_syst=tree_results_toys->Branch("err_slopeExp_High_syst",&internal_err_slopeExp_High_syst);
    }
    else if (string_functional_form=="Bukin") {
      b_internal_muBukin_nominal=tree_results_toys->Branch("muBukin_nominal",&internal_muBukin_nominal);
      b_internal_err_muBukin_nominal=tree_results_toys->Branch("err_muBukin_nominal",&internal_err_muBukin_nominal);
      b_internal_sigmaBukin_nominal=tree_results_toys->Branch("sigmaBukin_nominal",&internal_sigmaBukin_nominal);
      b_internal_err_sigmaBukin_nominal=tree_results_toys->Branch("err_sigmaBukin_nominal",&internal_err_sigmaBukin_nominal);
      b_internal_xiBukin_nominal=tree_results_toys->Branch("xiBukin_nominal",&internal_xiBukin_nominal);
      b_internal_err_xiBukin_nominal=tree_results_toys->Branch("err_xiBukin_nominal",&internal_err_xiBukin_nominal);
      b_internal_rho1Bukin_nominal=tree_results_toys->Branch("rho1Bukin_nominal",&internal_rho1Bukin_nominal);
      b_internal_err_rho1Bukin_nominal=tree_results_toys->Branch("err_rho1Bukin_nominal",&internal_err_rho1Bukin_nominal);
      b_internal_rho2Bukin_nominal=tree_results_toys->Branch("rho2Bukin_nominal",&internal_rho2Bukin_nominal);
      b_internal_err_rho2Bukin_nominal=tree_results_toys->Branch("err_rho2Bukin_nominal",&internal_err_rho2Bukin_nominal);

      b_internal_muBukin_syst=tree_results_toys->Branch("muBukin_syst",&internal_muBukin_syst);
      b_internal_err_muBukin_syst=tree_results_toys->Branch("err_muBukin_syst",&internal_err_muBukin_syst);
      b_internal_sigmaBukin_syst=tree_results_toys->Branch("sigmaBukin_syst",&internal_sigmaBukin_syst);
      b_internal_err_sigmaBukin_syst=tree_results_toys->Branch("err_sigmaBukin_syst",&internal_err_sigmaBukin_syst);
      b_internal_xiBukin_syst=tree_results_toys->Branch("xiBukin_syst",&internal_xiBukin_syst);
      b_internal_err_xiBukin_syst=tree_results_toys->Branch("err_xiBukin_syst",&internal_err_xiBukin_syst);
      b_internal_rho1Bukin_syst=tree_results_toys->Branch("rho1Bukin_syst",&internal_rho1Bukin_syst);
      b_internal_err_rho1Bukin_syst=tree_results_toys->Branch("err_rho1Bukin_syst",&internal_err_rho1Bukin_syst);
      b_internal_rho2Bukin_syst=tree_results_toys->Branch("rho2Bukin_syst",&internal_rho2Bukin_syst);
      b_internal_err_rho2Bukin_syst=tree_results_toys->Branch("err_rho2Bukin_syst",&internal_err_rho2Bukin_syst);
    }
  }
  else if (string_method_syst_shape=="mean_IQR") {
    b_internal_mean_nominal=tree_results_toys->Branch("mean_nominal",&internal_mean_nominal);
    b_internal_err_mean_nominal=tree_results_toys->Branch("err_mean_nominal",&internal_err_mean_nominal);
    b_internal_mean_syst=tree_results_toys->Branch("mean_syst",&internal_mean_syst);
    b_internal_err_mean_syst=tree_results_toys->Branch("err_mean_syst",&internal_err_mean_syst);
    
    b_internal_IQR_nominal=tree_results_toys->Branch("IQR_nominal",&internal_IQR_nominal);
    b_internal_err_IQR_nominal=tree_results_toys->Branch("err_IQR_nominal",&internal_err_IQR_nominal);
    b_internal_IQR_syst=tree_results_toys->Branch("IQR_syst",&internal_IQR_syst);
    b_internal_err_IQR_syst=tree_results_toys->Branch("err_IQR_syst",&internal_err_IQR_syst);
  }
  
  double internal_rel_effect_position_shape;
  TBranch *b_internal_rel_effect_position_shape=tree_results_toys->Branch("rel_effect_position_shape",&internal_rel_effect_position_shape);
		    
  double internal_rel_effect_spread_shape;
  TBranch *b_internal_rel_effect_spread_shape=tree_results_toys->Branch("rel_effect_spread_shape",&internal_rel_effect_spread_shape);

  cout << "nb_toys_done=" << nb_toys_done << endl;
  for (unsigned int index_toy=0;index_toy<nb_toys_done;index_toy++) {
    internal_index_toy=vec_index_toy[index_toy];

    if (string_method_syst_shape=="fit") {
      internal_converged=vec_converged[index_toy];
	  
      if (vec_status_nominal.size()>index_toy)
	internal_status_nominal=vec_status_nominal[index_toy];

      if (vec_status_syst.size()>index_toy)
	internal_status_syst=vec_status_syst[index_toy];
	  
      internal_chi2_nominal=vec_chi2_nominal[index_toy];
      internal_ndof_nominal=vec_ndof_nominal[index_toy];
	  
      internal_chi2_syst=vec_chi2_syst[index_toy];
      internal_ndof_syst=vec_ndof_syst[index_toy];

      if (string_functional_form=="DoubleCrystalBall") {
	internal_muCB_nominal=vec_muCB_nominal[index_toy];
	internal_err_muCB_nominal=vec_err_muCB_nominal[index_toy];
	internal_sigmaCB_nominal=vec_sigmaCB_nominal[index_toy];
	internal_err_sigmaCB_nominal=vec_err_sigmaCB_nominal[index_toy];
	
	internal_alphaCB_Low_nominal=vec_alphaCB_Low_nominal[index_toy];
	internal_err_alphaCB_Low_nominal=vec_err_alphaCB_Low_nominal[index_toy];
	    
	internal_nCB_Low_nominal=vec_nCB_Low_nominal[index_toy];
	internal_err_nCB_Low_nominal=vec_err_nCB_Low_nominal[index_toy];
	    
	internal_alphaCB_High_nominal=vec_alphaCB_High_nominal[index_toy];
	internal_err_alphaCB_High_nominal=vec_err_alphaCB_High_nominal[index_toy];
	    
	internal_nCB_High_nominal=vec_nCB_High_nominal[index_toy];
	internal_err_nCB_High_nominal=vec_err_nCB_High_nominal[index_toy];
	    
	internal_muCB_syst=vec_muCB_syst[index_toy];
	internal_err_muCB_syst=vec_err_muCB_syst[index_toy];
	internal_sigmaCB_syst=vec_sigmaCB_syst[index_toy];
	internal_err_sigmaCB_syst=vec_err_sigmaCB_syst[index_toy];
	    
	    
	internal_alphaCB_Low_syst=vec_alphaCB_Low_syst[index_toy];
	internal_err_alphaCB_Low_syst=vec_err_alphaCB_Low_syst[index_toy];
	    
	internal_nCB_Low_syst=vec_nCB_Low_syst[index_toy];
	internal_err_nCB_Low_syst=vec_err_nCB_Low_syst[index_toy];
	    
	internal_alphaCB_High_syst=vec_alphaCB_High_syst[index_toy];
	internal_err_alphaCB_High_syst=vec_err_alphaCB_High_syst[index_toy];
	    
	internal_nCB_High_syst=vec_nCB_High_syst[index_toy];
	internal_err_nCB_High_syst=vec_err_nCB_High_syst[index_toy];
      }
      else if (string_functional_form=="ExpGaussExp") {
	internal_muGauss_nominal=vec_muGauss_nominal[index_toy];
	internal_err_muGauss_nominal=vec_err_muGauss_nominal[index_toy];
	internal_sigmaGauss_nominal=vec_sigmaGauss_nominal[index_toy];
	internal_err_sigmaGauss_nominal=vec_err_sigmaGauss_nominal[index_toy];
	internal_slopeExp_Low_nominal=vec_slopeExp_Low_nominal[index_toy];
	internal_err_slopeExp_Low_nominal=vec_err_slopeExp_Low_nominal[index_toy];
	internal_slopeExp_High_nominal=vec_slopeExp_High_nominal[index_toy];
	internal_err_slopeExp_High_nominal=vec_err_slopeExp_High_nominal[index_toy];

	internal_muGauss_syst=vec_muGauss_syst[index_toy];
	internal_err_muGauss_syst=vec_err_muGauss_syst[index_toy];
	internal_sigmaGauss_syst=vec_sigmaGauss_syst[index_toy];
	internal_err_sigmaGauss_syst=vec_err_sigmaGauss_syst[index_toy];
	internal_slopeExp_Low_syst=vec_slopeExp_Low_syst[index_toy];
	internal_err_slopeExp_Low_syst=vec_err_slopeExp_Low_syst[index_toy];
	internal_slopeExp_High_syst=vec_slopeExp_High_syst[index_toy];
	internal_err_slopeExp_High_syst=vec_err_slopeExp_High_syst[index_toy];
      }
      
      else if (string_functional_form=="Bukin") {
	internal_muBukin_nominal=vec_muBukin_nominal[index_toy];
	internal_err_muBukin_nominal=vec_err_muBukin_nominal[index_toy];
	internal_sigmaBukin_nominal=vec_sigmaBukin_nominal[index_toy];
	internal_err_sigmaBukin_nominal=vec_err_sigmaBukin_nominal[index_toy];
	internal_xiBukin_nominal=vec_xiBukin_nominal[index_toy];
	internal_err_xiBukin_nominal=vec_err_xiBukin_nominal[index_toy];
	internal_rho1Bukin_nominal=vec_rho1Bukin_nominal[index_toy];
	internal_err_rho1Bukin_nominal=vec_err_rho1Bukin_nominal[index_toy];
	internal_rho2Bukin_nominal=vec_rho2Bukin_nominal[index_toy];
	internal_err_rho2Bukin_nominal=vec_err_rho2Bukin_nominal[index_toy];

	internal_muBukin_syst=vec_muBukin_syst[index_toy];
	internal_err_muBukin_syst=vec_err_muBukin_syst[index_toy];
	internal_sigmaBukin_syst=vec_sigmaBukin_syst[index_toy];
	internal_err_sigmaBukin_syst=vec_err_sigmaBukin_syst[index_toy];
	internal_xiBukin_syst=vec_xiBukin_syst[index_toy];
	internal_err_xiBukin_syst=vec_err_xiBukin_syst[index_toy];
	internal_rho1Bukin_syst=vec_rho1Bukin_syst[index_toy];
	internal_err_rho1Bukin_syst=vec_err_rho1Bukin_syst[index_toy];
	internal_rho2Bukin_syst=vec_rho2Bukin_syst[index_toy];
	internal_err_rho2Bukin_syst=vec_err_rho2Bukin_syst[index_toy];
      }
    }
    else if (string_method_syst_shape=="mean_IQR") {
      internal_mean_nominal=vec_mean_nominal[index_toy];
      internal_err_mean_nominal=vec_err_mean_nominal[index_toy];
      internal_mean_syst=vec_mean_syst[index_toy];
      internal_err_mean_syst=vec_err_mean_syst[index_toy];
	  
      internal_IQR_nominal=vec_IQR_nominal[index_toy];
      internal_err_IQR_nominal=vec_err_IQR_nominal[index_toy];
      internal_IQR_syst=vec_IQR_syst[index_toy];
      internal_err_IQR_syst=vec_err_IQR_syst[index_toy];
    }

    internal_rel_effect_position_shape=vec_result_rel_effect_position_shape[index_toy];
    internal_rel_effect_spread_shape=vec_result_rel_effect_spread_shape[index_toy];
	
    tree_results_toys->Fill();
  } //end loop on toys
		    
  tree_results_toys->Write();

  delete tree_results_toys;
		    
  file_save_results_toys->Close();

  delete file_save_results_toys;
      
  cout << "stored results for current range of toys" << endl;

  return;
}

 

//=========================================================================================================================
//validated

void tool_syst_shape::PlotShapeResults_current_systematic(string string_sample,string string_category,string string_campaign_MxAOD,string string_systematic,int index_toy)
{

  replace(string_systematic.begin(),string_systematic.end(),' ','_');
  
  cout << "PlotShapeResults_current_systematic phase 1" << endl;
  
  TCanvas *canvas_syst_shape;
  
  char buffer_index_toy[7]; //ok fore sure, up to 5 digits + '\0'
  
  if (string_method_partition_events=="bootstrap" || string_method_partition_events=="jacknife") {
    sprintf(buffer_index_toy,"%d",index_toy);
  }
  
  canvas_syst_shape=new TCanvas("canvas_syst_shape","canvas_syst_shape",800,600);
  canvas_syst_shape->SetRightMargin(0.03); //not below 0.03, in order to cover numbers as 1200 GeV for resonant
  canvas_syst_shape->SetTopMargin(0.04);
  
  TH1F *hist_dummy=0;

  if (m_string_observable_shape=="m_yy")
    hist_dummy=canvas_syst_shape->DrawFrame(hist_nominal->GetBinLowEdge(1),1e-6,hist_nominal->GetBinLowEdge(hist_nominal->GetNbinsX())+hist_nominal->GetBinWidth(1),hist_nominal->GetMaximum()*1.2); //epsilon is to avoid for roofit the markers
  else if (m_string_observable_shape=="m_bb")
    hist_dummy=canvas_syst_shape->DrawFrame(hist_nominal->GetBinLowEdge(1),1e-6,hist_nominal->GetBinLowEdge(hist_nominal->GetNbinsX())+hist_nominal->GetBinWidth(1),hist_nominal->GetMaximum()*1.8); //epsilon is to avoid for roofit the markers
  else if (m_string_observable_shape=="m_yybb_tilde")
    hist_dummy=canvas_syst_shape->DrawFrame(hist_nominal->GetBinLowEdge(1),1e-6,hist_nominal->GetBinLowEdge(hist_nominal->GetNbinsX())+hist_nominal->GetBinWidth(1),hist_nominal->GetMaximum()*1.8); //epsilon is to avoid for roofit the markers
  
  char buffer[128];
  
  hist_dummy->Draw();
  hist_dummy->GetXaxis()->SetTitle((string_latex_observable_shape_no_units+" "+string_latex_observable_shape_units).c_str());
  sprintf(buffer,"Events / %4.2f [GeV]",hist_nominal->GetBinWidth(1));
  hist_dummy->GetYaxis()->SetTitle(buffer);
  hist_dummy->GetYaxis()->SetTitleOffset(1.45);

  
  if (shape_root1_roofit2==1) { //root
    hist_nominal->Draw("same");
    //the function is drawn, in order to have more flexibility, so that the fit itself does not create a canvas
    function_shape_nominal->Draw("same");
    
    hist_syst->Draw("same");
    function_shape_syst->Draw("same");
  }

  //to improve by taking case root/roofit

  cout << "PlotShapeResults_current_systematic phase 2" << endl;
  
  if (string_functional_form=="DoubleCrystalBall") {    
    muCB_nominal=position_parameter_nominal;
    err_muCB_nominal=err_position_parameter_nominal;
    
    sigmaCB_nominal=spread_parameter_nominal;
    err_sigmaCB_nominal=err_spread_parameter_nominal;
    
    //to make it independent of root/roofit
    
    if (shape_root1_roofit2==2) { //roofit
      alphaCB_Low_nominal=roorealvar_alphaCB_Low_nominal->getVal();
      err_alphaCB_Low_nominal=roorealvar_alphaCB_Low_nominal->getError();
      nCB_Low_nominal=roorealvar_nCB_Low_nominal->getVal();
      err_nCB_Low_nominal=roorealvar_nCB_Low_nominal->getError();
      alphaCB_High_nominal=roorealvar_alphaCB_High_nominal->getVal();
      err_alphaCB_High_nominal=roorealvar_alphaCB_High_nominal->getError();
      nCB_High_nominal=roorealvar_nCB_High_nominal->getVal();
      err_nCB_High_nominal=roorealvar_nCB_High_nominal->getError();
      
      if (string_systematic!="showering") {
	//for write :  but probably could directly store the roorealvar...
	muCB_syst=roorealvar_muCB_syst->getVal();
	err_muCB_syst=roorealvar_muCB_syst->getError();
	sigmaCB_syst=roorealvar_sigmaCB_syst->getVal();
	err_sigmaCB_syst=roorealvar_sigmaCB_syst->getError();
	alphaCB_Low_syst=roorealvar_alphaCB_Low_syst->getVal();
	err_alphaCB_Low_syst=roorealvar_alphaCB_Low_syst->getError();
	nCB_Low_syst=roorealvar_nCB_Low_syst->getVal();
	err_nCB_Low_syst=roorealvar_nCB_Low_syst->getError();
	alphaCB_High_syst=roorealvar_alphaCB_High_syst->getVal();
	err_alphaCB_High_syst=roorealvar_alphaCB_High_syst->getError();
	nCB_High_syst=roorealvar_nCB_High_syst->getVal();
	err_nCB_High_syst=roorealvar_nCB_High_syst->getError();
      }
    }
  }
  else if (string_functional_form=="ExpGaussExp") {
    if (shape_root1_roofit2==2) { //roofit
      muGauss_nominal=roorealvar_muGauss_nominal->getVal();
      err_muGauss_nominal=roorealvar_muGauss_nominal->getError();
      sigmaGauss_nominal=roorealvar_sigmaGauss_nominal->getVal();
      err_sigmaGauss_nominal=roorealvar_sigmaGauss_nominal->getError();
      slopeExp_Low_nominal=roorealvar_slopeExp_Low_nominal->getVal();
      err_slopeExp_Low_nominal=roorealvar_slopeExp_Low_nominal->getError();
      slopeExp_High_nominal=roorealvar_slopeExp_High_nominal->getVal();
      err_slopeExp_High_nominal=roorealvar_slopeExp_High_nominal->getError();
      
      if (string_systematic!="showering") {
	muGauss_syst=roorealvar_muGauss_syst->getVal();
	err_muGauss_syst=roorealvar_muGauss_syst->getError();
	sigmaGauss_syst=roorealvar_sigmaGauss_syst->getVal();
	err_sigmaGauss_syst=roorealvar_sigmaGauss_syst->getError();
	slopeExp_Low_syst=roorealvar_slopeExp_Low_syst->getVal();
	err_slopeExp_Low_syst=roorealvar_slopeExp_Low_syst->getError();
	slopeExp_High_syst=roorealvar_slopeExp_High_syst->getVal();
	err_slopeExp_High_syst=roorealvar_slopeExp_High_syst->getError();
      }
    }
  }
  
  else if (string_functional_form=="Bukin") {
    muBukin_nominal=position_parameter_nominal;
    err_muBukin_nominal=err_position_parameter_nominal;
    
    sigmaBukin_nominal=spread_parameter_nominal;
    err_sigmaBukin_nominal=err_spread_parameter_nominal;
    
    //to make it independent of root/roofit
    
    if (shape_root1_roofit2==2) { //roofit
      xiBukin_nominal=roorealvar_xiBukin_nominal->getVal();
      err_xiBukin_nominal=roorealvar_xiBukin_nominal->getError();
      rho1Bukin_nominal=roorealvar_rho1Bukin_nominal->getVal();
      err_rho1Bukin_nominal=roorealvar_rho1Bukin_nominal->getError();
      rho2Bukin_nominal=roorealvar_rho2Bukin_nominal->getVal();
      err_rho2Bukin_nominal=roorealvar_rho2Bukin_nominal->getError();
      
      if (string_systematic!="showering") {    
	//for write :  but probably could directly store the roorealvar...

	muBukin_syst=roorealvar_muBukin_syst->getVal();
	err_muBukin_syst=roorealvar_muBukin_syst->getError();
	sigmaBukin_syst=roorealvar_sigmaBukin_syst->getVal();
	err_sigmaBukin_syst=roorealvar_sigmaBukin_syst->getError();
	xiBukin_syst=roorealvar_xiBukin_syst->getVal();
	err_xiBukin_syst=roorealvar_xiBukin_syst->getError();
	rho1Bukin_syst=roorealvar_rho1Bukin_syst->getVal();
	err_rho1Bukin_syst=roorealvar_rho1Bukin_syst->getError();
	rho2Bukin_syst=roorealvar_rho2Bukin_syst->getVal();
	err_rho2Bukin_syst=roorealvar_rho2Bukin_syst->getError();
      }
    }
  }

  cout << "PlotShapeResults_current_systematic phase 3" << endl;
  
  RooPlot* rooplot_shape;
  
  if (shape_root1_roofit2==2) { //roofit
    rooplot_shape=roorealvar_observable->frame(hist_nominal->GetNbinsX());
    rooplot_shape->SetTitle(""); //empty title to prevent printing "A RooPlot of ..."
    rooplot_shape->SetXTitle((string_latex_observable_shape_no_units+" "+string_latex_observable_shape_units).c_str());
    sprintf(buffer,"Events / %4.2f [GeV]",hist_nominal->GetBinWidth(1));
    rooplot_shape->SetYTitle(buffer);
    //----------
    absdata_nominal->plotOn(rooplot_shape,RooFit::Name("roohist_absdata_nominal"),RooFit::MarkerStyle(20),RooFit::MarkerColor(kGreen+2),RooFit::LineColor(kGreen+2),RooFit::DataError(RooAbsData::SumW2));

    cout << "plotedOn the nominal" << endl;
    pdf_shape_nominal->plotOn(rooplot_shape,RooFit::Name("roocurve_pdf_shape_nominal"),RooFit::LineColor(kGreen+1),RooFit::LineWidth(2));
    //    pdf_shape_nominal->plotOn(rooplot_shape,RooFit::Name("roocurve_pdf_shape_nominal"),RooFit::LineColor(kGreen+2),RooFit::LineWidth(2));

    cout << "compute chisquare" << endl;
    RooArgSet *floatPars_nominal=(RooArgSet *)pdf_shape_nominal->getParameters(*absdata_nominal)->selectByAttrib("Constant",kFALSE);
    nparam_nominal=floatPars_nominal->getSize();
    delete floatPars_nominal;
    
    //    cout << "nparam_nominal=" << nparam_nominal << endl;
    
    chi2_over_ndf_nominal=rooplot_shape->chiSquare("roocurve_pdf_shape_nominal","roohist_absdata_nominal",nparam_nominal);

    int lower_nominal=hist_nominal->GetXaxis()->FindFixBin(low_value_nominal_fit_range);
    int upper_nominal=hist_nominal->GetXaxis()->FindFixBin(high_value_nominal_fit_range);
    int nb_bins_nominal=upper_nominal-lower_nominal;
    //    cout << "nb_bins_nominal=" << nb_bins_nominal << endl;
    
    ndof_nominal=nb_bins_nominal-nparam_nominal;
    chi2_nominal=chi2_over_ndf_nominal*ndof_nominal;
    
    cout << "chi2_over_ndf_nominal=" << chi2_over_ndf_nominal << endl;
    //    cout << "computed chisquare" << endl;
    //----------
    //this one

    cout << "now deals with syst" << endl;

    if (string_systematic!="showering") {
      absdata_syst->plotOn(rooplot_shape,RooFit::Name("roohist_absdata_syst"),RooFit::MarkerStyle(20),RooFit::MarkerColor(kBlue+2),RooFit::LineColor(kBlue+2),RooFit::DataError(RooAbsData::SumW2));
      //pdf_shape_syst->plotOn(rooplot_shape,RooFit::Name("roocurve_pdf_shape_syst"),RooFit::LineColor(kBlue+2),RooFit::LineWidth(2));
      pdf_shape_syst->plotOn(rooplot_shape,RooFit::Name("roocurve_pdf_shape_syst"),RooFit::LineColor(kBlue),RooFit::LineWidth(2));

      RooArgSet *floatPars_syst=(RooArgSet *)pdf_shape_syst->getParameters(*absdata_syst)->selectByAttrib("Constant",kFALSE);
      nparam_syst=floatPars_syst->getSize();
      delete floatPars_syst;
      
      chi2_over_ndf_syst=rooplot_shape->chiSquare("roocurve_pdf_shape_syst","roohist_absdata_syst",nparam_syst);
      
      int lower_syst=hist_syst->GetXaxis()->FindFixBin(low_value_syst_fit_range);
      int upper_syst=hist_syst->GetXaxis()->FindFixBin(high_value_syst_fit_range);
      int nb_bins_syst=upper_syst-lower_syst;
      ndof_syst=nb_bins_syst-nparam_syst;

      chi2_syst=chi2_over_ndf_syst*ndof_syst;
    }
    
    rooplot_shape->Draw("same");
  } //end case roofit
  else {
    cout << "case root not yet implemented" << endl;
    exit(1);
  }

  //_____________________________________________________________________________
  float vertical_position_baseline=0.65;
  float horizontal_position_baseline=0.13;
  
  float vertical_step=0.04;
  
  float vertical_position;
  
  TLatex latex;
  latex.SetNDC(0);
  latex.SetTextSize(0.04); //0.045 is std
  latex.SetTextColor(kBlack);
  latex.SetTextFont(42); //put back the font

  //  latex.SetTextSize(0.032); //0.045 is std
  latex.SetTextSize(0.03); //0.045 is std
  latex.SetNDC(1);

  TH1D *hist;
  RooFitResult *roofitresult=0;
    
  double chi2;
  int ndof;
  double chi2_over_ndf;

  TF1 *function_shape=0;
  RooRealVar *roorealvar_muCB=0;
  RooRealVar *roorealvar_sigmaCB=0;
  RooRealVar *roorealvar_alphaCB_Low=0;
  RooRealVar *roorealvar_nCB_Low=0;
  RooRealVar *roorealvar_alphaCB_High=0;
  RooRealVar *roorealvar_nCB_High=0;
    
  RooRealVar *roorealvar_sigmaGauss=0;
  RooRealVar *roorealvar_muGauss=0;
  RooRealVar *roorealvar_slopeExp_Low=0;
  RooRealVar *roorealvar_slopeExp_High=0;

  RooRealVar *roorealvar_muBukin=0;
  RooRealVar *roorealvar_sigmaBukin=0;
  RooRealVar *roorealvar_xiBukin=0;
  RooRealVar *roorealvar_rho1Bukin=0;
  RooRealVar *roorealvar_rho2Bukin=0;

  for (int index_nominal_syst=0;index_nominal_syst<2;index_nominal_syst++) {
    
    if (string_systematic=="showering" && index_nominal_syst>=1)
      continue;
    
    vertical_position=vertical_position_baseline;
      
    if (index_nominal_syst==0) { //nominal

      horizontal_position_baseline=0.13;
      latex.SetTextColor(kGreen+2);

      hist=hist_nominal;
	
      chi2=chi2_nominal;
      ndof=ndof_nominal;
      chi2_over_ndf=chi2_over_ndf_nominal;
	
      if (shape_root1_roofit2==1) { //root
	function_shape=function_shape_nominal;
      }
      else if (shape_root1_roofit2==2) { //roofit
	roofitresult=roofitresult_nominal;
 
	if (string_functional_form=="DoubleCrystalBall") {
	  roorealvar_muCB=roorealvar_muCB_nominal;
	  roorealvar_sigmaCB=roorealvar_sigmaCB_nominal;
	  roorealvar_alphaCB_Low=roorealvar_alphaCB_Low_nominal;
	  roorealvar_nCB_Low=roorealvar_nCB_Low_nominal;
	  roorealvar_alphaCB_High=roorealvar_alphaCB_High_nominal;
	  roorealvar_nCB_High=roorealvar_nCB_High_nominal;
	}
	else if (string_functional_form=="ExpGaussExp") {
	  roorealvar_muGauss=roorealvar_muGauss_nominal;
	  roorealvar_sigmaGauss=roorealvar_sigmaGauss_nominal;
	  roorealvar_slopeExp_Low=roorealvar_slopeExp_Low_nominal;
	  roorealvar_slopeExp_High=roorealvar_slopeExp_High_nominal;
	}
	else if (string_functional_form=="Bukin") {
	  roorealvar_muBukin=roorealvar_muBukin_nominal;
	  roorealvar_sigmaBukin=roorealvar_sigmaBukin_nominal;
	  roorealvar_xiBukin=roorealvar_xiBukin_nominal;
	  roorealvar_rho1Bukin=roorealvar_rho1Bukin_nominal;
	  roorealvar_rho2Bukin=roorealvar_rho2Bukin_nominal;
	}
	else {
	  cout << "not implemented" << endl;
	  exit(1);
	}
      }
    }
    else if (index_nominal_syst==1) { //syst

      horizontal_position_baseline=0.66;
      latex.SetTextColor(kBlue+2);

      hist=hist_syst;
	
      chi2=chi2_syst;
      ndof=ndof_syst;
      chi2_over_ndf=chi2_over_ndf_syst;
	
      if (shape_root1_roofit2==1) { //root
	function_shape=function_shape_syst;
	  
      }
      else if (shape_root1_roofit2==2) { //roofit
	roofitresult=roofitresult_syst;
 
	if (string_functional_form=="DoubleCrystalBall") {
	  roorealvar_muCB=roorealvar_muCB_syst;
	  roorealvar_sigmaCB=roorealvar_sigmaCB_syst;
	  roorealvar_alphaCB_Low=roorealvar_alphaCB_Low_syst;
	  roorealvar_nCB_Low=roorealvar_nCB_Low_syst;
	  roorealvar_alphaCB_High=roorealvar_alphaCB_High_syst;
	  roorealvar_nCB_High=roorealvar_nCB_High_syst;
	}
	else if (string_functional_form=="ExpGaussExp") {
	  roorealvar_muGauss=roorealvar_muGauss_syst;
	  roorealvar_sigmaGauss=roorealvar_sigmaGauss_syst;
	  roorealvar_slopeExp_Low=roorealvar_slopeExp_Low_syst;
	  roorealvar_slopeExp_High=roorealvar_slopeExp_High_syst;
	}
	else if (string_functional_form=="Bukin") {
	  roorealvar_muBukin=roorealvar_muBukin_syst;
	  roorealvar_sigmaBukin=roorealvar_sigmaBukin_syst;
	  roorealvar_xiBukin=roorealvar_xiBukin_syst;
	  roorealvar_rho1Bukin=roorealvar_rho1Bukin_syst;
	  roorealvar_rho2Bukin=roorealvar_rho2Bukin_syst;
	}
	else {
	  cout << "not implemented" << endl;
	  exit(1);
	}
      }
    }
    //-----
    //norm: only with root
    if (shape_root1_roofit2==1) { //root
      sprintf(buffer,"%s=%4.2f #pm %4.2f",function_shape->GetParName(index_normalization_parameter),function_shape->GetParameter(index_normalization_parameter),function_shape->GetParError(index_normalization_parameter));
      latex.DrawLatexNDC(horizontal_position_baseline,vertical_position,buffer);
    }
    vertical_position-=vertical_step;

    //-----
    if (shape_root1_roofit2==1) //root
      sprintf(buffer,"%s=%4.2f #pm %4.2f [GeV]",function_shape->GetParName(index_position_parameter),function_shape->GetParameter(index_position_parameter),function_shape->GetParError(index_position_parameter));
    else if (shape_root1_roofit2==2) { //roofit
      if (string_functional_form=="DoubleCrystalBall")
	sprintf(buffer,"%s=%4.2f #pm %4.2f [%s]",roorealvar_muCB->GetTitle(),roorealvar_muCB->getVal(),roorealvar_muCB->getError(),roorealvar_muCB->getUnit());
      else if (string_functional_form=="ExpGaussExp")
	sprintf(buffer,"%s=%4.2f #pm %4.2f [%s]",roorealvar_muGauss->GetTitle(),roorealvar_muGauss->getVal(),roorealvar_muGauss->getError(),roorealvar_muGauss->getUnit());
      else if (string_functional_form=="Bukin") {
	sprintf(buffer,"%s=%4.2f #pm %4.2f [%s]",roorealvar_muBukin->GetTitle(),roorealvar_muBukin->getVal(),roorealvar_muBukin->getError(),roorealvar_muBukin->getUnit());
      }
    }
    latex.DrawLatexNDC(horizontal_position_baseline,vertical_position,buffer);
    vertical_position-=vertical_step;
    //-----
    if (shape_root1_roofit2==1) //root
      sprintf(buffer,"%s=%4.2f #pm %4.2f [GeV]",function_shape->GetParName(index_spread_parameter),function_shape->GetParameter(index_spread_parameter),function_shape->GetParError(index_spread_parameter));
    else if (shape_root1_roofit2==2) { //roofit
      if (string_functional_form=="DoubleCrystalBall")
	sprintf(buffer,"%s=%4.2f #pm %4.2f [%s]",roorealvar_sigmaCB->GetTitle(),roorealvar_sigmaCB->getVal(),roorealvar_sigmaCB->getError(),roorealvar_sigmaCB->getUnit());
      else if (string_functional_form=="ExpGaussExp")
	sprintf(buffer,"%s=%4.2f #pm %4.2f [%s]",roorealvar_sigmaGauss->GetTitle(),roorealvar_sigmaGauss->getVal(),roorealvar_sigmaGauss->getError(),roorealvar_sigmaGauss->getUnit());
      else if (string_functional_form=="Bukin") {
	sprintf(buffer,"%s=%4.2f #pm %4.2f [%s]",roorealvar_sigmaBukin->GetTitle(),roorealvar_sigmaBukin->getVal(),roorealvar_sigmaBukin->getError(),roorealvar_sigmaBukin->getUnit());
      }
    }
    latex.DrawLatexNDC(horizontal_position_baseline,vertical_position,buffer);
    vertical_position-=vertical_step;
    //-----
    if (shape_root1_roofit2==1) { //root
      if (string_functional_form=="DoubleCrystalBall")
	sprintf(buffer,"%s=%4.2f #pm %4.2f",function_shape->GetParName(index_alphaCB_Low),function_shape->GetParameter(index_alphaCB_Low),function_shape->GetParError(index_alphaCB_Low));
      else if (string_functional_form=="ExpGaussExp")
	sprintf(buffer,"%s=%4.2f #pm %4.2f",function_shape->GetParName(index_slopeExp_Low),function_shape->GetParameter(index_slopeExp_Low),function_shape->GetParError(index_slopeExp_Low));
    }
    else if (shape_root1_roofit2==2) { //roofit
      if (string_functional_form=="DoubleCrystalBall")
	sprintf(buffer,"%s=%4.2f #pm %4.2f",roorealvar_alphaCB_Low->GetTitle(),roorealvar_alphaCB_Low->getVal(),roorealvar_alphaCB_Low->getError());
      else if (string_functional_form=="ExpGaussExp")
	sprintf(buffer,"%s=%4.2f #pm %4.2f",roorealvar_slopeExp_Low->GetTitle(),roorealvar_slopeExp_Low->getVal(),roorealvar_slopeExp_Low->getError());
      else if (string_functional_form=="Bukin")
	sprintf(buffer,"%s=%4.2f #pm %4.2f",roorealvar_xiBukin->GetTitle(),roorealvar_xiBukin->getVal(),roorealvar_xiBukin->getError());
    }
    latex.DrawLatexNDC(horizontal_position_baseline,vertical_position,buffer);
    vertical_position-=vertical_step;
    //-----
    if (shape_root1_roofit2==1) { //root
      if (string_functional_form=="DoubleCrystalBall")
	sprintf(buffer,"%s=%4.2f #pm %4.2f",function_shape->GetParName(index_nCB_Low),function_shape->GetParameter(index_nCB_Low),function_shape->GetParError(index_nCB_Low));
      else if (string_functional_form=="ExpGaussExp")
	sprintf(buffer,"%s=%4.2f #pm %4.2f",function_shape->GetParName(index_slopeExp_High),function_shape->GetParameter(index_slopeExp_High),function_shape->GetParError(index_slopeExp_High));
    }
    else if (shape_root1_roofit2==2) { //roofit
      if (string_functional_form=="DoubleCrystalBall")
	sprintf(buffer,"%s=%4.2f #pm %4.2f",roorealvar_nCB_Low->GetTitle(),roorealvar_nCB_Low->getVal(),roorealvar_nCB_Low->getError());
      else if (string_functional_form=="ExpGaussExp")
	sprintf(buffer,"%s=%4.2f #pm %4.2f",roorealvar_slopeExp_High->GetTitle(),roorealvar_slopeExp_High->getVal(),roorealvar_slopeExp_High->getError());
      else if (string_functional_form=="Bukin")
	sprintf(buffer,"%s=%4.2f #pm %4.2f",roorealvar_rho1Bukin->GetTitle(),roorealvar_rho1Bukin->getVal(),roorealvar_rho1Bukin->getError());
    }
    latex.DrawLatexNDC(horizontal_position_baseline,vertical_position,buffer);
    vertical_position-=vertical_step;
    //-----
    if (string_functional_form=="DoubleCrystalBall" || string_functional_form=="Bukin") {
      if (shape_root1_roofit2==1) { //root
	if (string_functional_form=="DoubleCrystalBall")
	  sprintf(buffer,"%s=%4.2f #pm %4.2f",function_shape->GetParName(index_alphaCB_High),function_shape->GetParameter(index_alphaCB_High),function_shape->GetParError(index_alphaCB_High));
	else {
	  cout << "function not implememented, halt program" << endl;
	  exit(1);
	}
      }
      else if (shape_root1_roofit2==2) { //roofit
	if (string_functional_form=="DoubleCrystalBall")
	  sprintf(buffer,"%s=%4.2f #pm %4.2f",roorealvar_alphaCB_High->GetTitle(),roorealvar_alphaCB_High->getVal(),roorealvar_alphaCB_High->getError());
	else if (string_functional_form=="Bukin")
	  sprintf(buffer,"%s=%4.2f #pm %4.2f",roorealvar_rho2Bukin->GetTitle(),roorealvar_rho2Bukin->getVal(),roorealvar_rho2Bukin->getError());
      }
      latex.DrawLatexNDC(horizontal_position_baseline,vertical_position,buffer);
    }
    vertical_position-=vertical_step;
    //-----
    if (string_functional_form=="DoubleCrystalBall") {
      if (shape_root1_roofit2==1) //root
	sprintf(buffer,"%s=%4.2f #pm %4.2f",function_shape->GetParName(index_nCB_High),function_shape->GetParameter(index_nCB_High),function_shape->GetParError(index_nCB_High));
      else if (shape_root1_roofit2==2) //roofit
	sprintf(buffer,"%s=%4.2f #pm %4.2f",roorealvar_nCB_High->GetTitle(),roorealvar_nCB_High->getVal(),roorealvar_nCB_High->getError());
      latex.DrawLatexNDC(horizontal_position_baseline,vertical_position,buffer);
    }
    vertical_position-=vertical_step;
      
    sprintf(buffer,"mean=%4.2f #pm %4.2f",hist->GetMean(),hist->GetMeanError());
    latex.DrawLatexNDC(horizontal_position_baseline,vertical_position,buffer);
      
    vertical_position-=vertical_step;
      
    sprintf(buffer,"RMS=%4.2f #pm %4.2f",hist->GetRMS(),hist->GetRMSError());
    latex.DrawLatexNDC(horizontal_position_baseline,vertical_position,buffer);
      
    vertical_position-=vertical_step;
      
    if (roofitresult) {
      sprintf(buffer,"-Log L : %4.2e",roofitresult->minNll());
      latex.DrawLatexNDC(horizontal_position_baseline,vertical_position,buffer);
    }
    vertical_position-=vertical_step;
      
    sprintf(buffer,"#chi^{2}/ndf: %4.2f/%d=%4.2f",chi2,ndof,chi2_over_ndf);
    latex.DrawLatexNDC(horizontal_position_baseline,vertical_position,buffer);
      
    vertical_position-=vertical_step;
      
  } //end loop nominal, systematic
    //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  
  vertical_position-=vertical_step;
  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  if (string_systematic!="showering") {
    latex.SetTextColor(kRed);
    
    sprintf(buffer,"rel. effect (%%) #mu: %4.3f #pm %4.3f",rel_effect_position_shape,err_rel_effect_position_shape);
    latex.DrawLatexNDC(horizontal_position_baseline,vertical_position,buffer);
    sprintf(buffer,"rel. effect (%%) #sigma: %4.3f #pm %4.3f",rel_effect_spread_shape,err_rel_effect_spread_shape);
    vertical_position-=vertical_step;
    latex.DrawLatexNDC(horizontal_position_baseline,vertical_position,buffer);
  }
  
  //this does not take into account correlation
		
  //   printf("rel effect position shape=%4.2f +/- %4.2f\n",rel_effect_position_shape,err_rel_effect_position_shape);
  //   printf("rel effect spread shape=%4.2f +/- %4.2f\n",rel_effect_spread_shape,err_rel_effect_spread_shape);
  //   cout << "=================================================================================" << endl;
  float horizontal_position=0.63;

  latex.SetTextColor(kBlack);
  latex.SetNDC();
  latex.SetTextSize(0.04); //0.045 is std
  latex.SetTextFont(72);
  latex.DrawLatex(horizontal_position,0.92,"ATLAS");
  latex.SetTextFont(42); //put back the font
  latex.DrawLatex(horizontal_position+0.1,0.92,"internal");

  latex.DrawLatex(horizontal_position,0.84,(get_string_ECM_luminosity(string_campaign_MxAOD)).c_str());

  //		  latex.SetTextSize(0.04); //0.045 is std
  latex.SetTextSize(0.016); //0.034 too small for HH non resonant
  latex.SetTextColor(kBlack);
		  
  latex.DrawLatex(horizontal_position,0.78,string_sample.c_str());
  
  latex.SetTextSize(0.018);
  latex.DrawLatex(horizontal_position,0.73,(string_systematic+suffix_asymmetry_systematic).c_str());
  //latex.SetTextSize(0.04);


  //  latex.SetTextSize(0.03);
  latex.SetTextSize(0.025);
  latex.DrawLatex(horizontal_position,0.68,string_category.c_str());
  //-----
  //left part of the screen

  latex.DrawLatex(0.15,0.90,string_functional_form.c_str());
  
  if (shape_root1_roofit2==1)
    sprintf(buffer,"root");
  else if (shape_root1_roofit2==2)
    sprintf(buffer,"roofit");
  
  if (shape_chi2fit_1_loglikelihoodfit2==1)
    sprintf(buffer,"%s, #chi^{2} fit",buffer);
  else if (shape_chi2fit_1_loglikelihoodfit2==2)
    sprintf(buffer,"%s, Log Likelihood fit",buffer);
  
  latex.DrawLatex(0.15,0.72,buffer);

  if (string_method_partition_events=="bootstrap" || string_method_partition_events=="jacknife") {
    sprintf(buffer,"toy number : %d",index_toy);
    latex.DrawLatex(0.15,0.67,buffer);
  }
  
  TLegend *legend=new TLegend(0.15,0.76,0.42,0.87);
  legend->SetTextSize(0.04);
  legend->SetBorderSize(2);
  legend->SetBorderSize(0);
  legend->SetLineColor(0);
  legend->SetLineWidth(0);
  legend->SetFillStyle(1001);
  legend->SetFillColor(kWhite);

  if (shape_root1_roofit2==1) { //root
    legend->AddEntry(hist_nominal,"nominal","lp");

    if (string_systematic!="showering")
      legend->AddEntry(hist_syst,"systematic","lp");
  }
  else if (shape_root1_roofit2==2) { //roofit
    TLegendEntry *entry;
    //trick because RooDataSet don't have a color parameter : the plotOn does not change the RooDataSet iself
		    
    entry=legend->AddEntry(absdata_nominal,"nominal","lp");
    entry->SetMarkerSize(1.0);
    entry->SetMarkerStyle(20);
    entry->SetLineColor(kGreen+2);
    entry->SetMarkerColor(kGreen+2);

    if (string_systematic!="showering") {
      entry=legend->AddEntry(absdata_syst,"systematic","lp");
      entry->SetMarkerSize(1.0);
      entry->SetMarkerStyle(20);
      entry->SetLineColor(kBlue+2);
      entry->SetMarkerColor(kBlue+2);
    }
  }
  legend->Draw();
	
  TGaxis *axis_top_contrib_err=new TGaxis(canvas_syst_shape->GetUxmin(),canvas_syst_shape->GetUymax(),canvas_syst_shape->GetUxmax(),canvas_syst_shape->GetUymax(),hist_dummy->GetXaxis()->GetXmin(),hist_dummy->GetXaxis()->GetXmax(),510,"-LU");
  axis_top_contrib_err->Draw();

  //  canvas_syst_shape->SetLogy();

  canvas_syst_shape->RedrawAxis();

  if (index_toy<10) {
    string string_saveas=string_path+string_rel_path_shape+"figures/";
    string_saveas+=string_process;
    string_saveas+="/";
    string_saveas+=string_campaign_MxAOD;
    string_saveas+="/";
    string_saveas+=string_category;
    string_saveas+="/";
    string_saveas+=m_string_observable_shape;
    string_saveas+="/";
    string_saveas+=string_systematic;
    string_saveas+="/";
    
    string_saveas+="/plot_syst_shape_";
    string_saveas+="fit_";
    string_saveas+=m_string_observable_shape;
    string_saveas+="_";
    string_saveas+=string_sample;
    string_saveas+="_";
    string_saveas+=string_systematic;
    string_saveas+=vec_nature_syst_components_sym_asym[index_sym_asym];
    string_saveas+="_";
    string_saveas+=string_category;
    string_saveas+="_";
    string_saveas+=string_method_partition_events;
    string_saveas+="_";
    string_saveas+=string_method_syst_shape;
    
    if (string_method_partition_events=="bootstrap" || string_method_partition_events=="jacknife") {
      string_saveas+="_";
      string_saveas+=buffer_index_toy;
    }
    
    string_saveas+=".png";
    
    //moved above  if (index_toy<10)
    canvas_syst_shape->SaveAs(string_saveas.c_str());
  }
  
  cout << "phase delete hist_dummy" << endl;

  delete hist_dummy;

  cout << "delete histograms" << endl;

  delete hist_nominal;

  if (string_systematic!="showering")
    delete hist_syst;
  
  if (shape_root1_roofit2==1) { //root
    cout << "delete functions" << endl;
    delete function_shape_nominal;

    if (string_systematic!="showering")
      delete function_shape_syst;
  }
  else if (shape_root1_roofit2==2) { //roofit
    cout << "delete rooabsdata" << endl;
    delete absdata_nominal;

    if (string_systematic!="showering")
      delete absdata_syst;

    if (roorealvar_observable)
      delete roorealvar_observable;

    if (roorealvar_eventNumber)
      delete roorealvar_eventNumber;
        
    if (roorealvar_weight_total)
      delete roorealvar_weight_total;
    
    if (string_functional_form=="DoubleCrystalBall") {
      delete roorealvar_muCB_nominal;
      delete roorealvar_sigmaCB_nominal;
      delete roorealvar_alphaCB_Low_nominal;
      delete roorealvar_nCB_Low_nominal;
      delete roorealvar_alphaCB_High_nominal;
      delete roorealvar_nCB_High_nominal;

      if (string_systematic!="showering") {
	delete roorealvar_muCB_syst;
	delete roorealvar_sigmaCB_syst;
	delete roorealvar_alphaCB_Low_syst;
	delete roorealvar_nCB_Low_syst;
	delete roorealvar_alphaCB_High_syst;
	delete roorealvar_nCB_High_syst;
      }
    }
    else if (string_functional_form=="ExpGaussExp") {
      delete roorealvar_muGauss_nominal;
      delete roorealvar_sigmaGauss_nominal;
      delete roorealvar_slopeExp_Low_nominal;
      delete roorealvar_slopeExp_High_nominal;

      if (string_systematic!="showering") {
	delete roorealvar_muGauss_syst;
	delete roorealvar_sigmaGauss_syst;
	if (roorealvar_slopeExp_Low_syst)
	  delete roorealvar_slopeExp_Low_syst;
	if (roorealvar_slopeExp_High_syst)
	  delete roorealvar_slopeExp_High_syst;
      }
    }
    else if (string_functional_form=="Bukin") {
      delete roorealvar_muBukin_nominal;
      delete roorealvar_sigmaBukin_nominal;
      delete roorealvar_xiBukin_nominal;
      delete roorealvar_rho1Bukin_nominal;
      delete roorealvar_rho2Bukin_nominal;

      if (string_systematic!="showering") {
	delete roorealvar_muBukin_syst;
	delete roorealvar_sigmaBukin_syst;
	delete roorealvar_xiBukin_syst;
	delete roorealvar_rho1Bukin_syst;
	delete roorealvar_rho2Bukin_syst;
      }
    }

    delete pdf_shape_nominal;

    if (string_systematic!="showering")
      delete pdf_shape_syst;
  }
    
  cout << "delete canvas" << endl;
    
  delete canvas_syst_shape;

  return;
}
 
//=============================================================================================================================================================================================
void tool_syst_shape::Plot_pseudo_experiments(string string_sample,string string_category,string string_campaign_MxAOD,string string_systematic,int local_index_sym_asym,string string_observable,TH1D *hist_rel_effect,double local_rel_effect,double local_err_rel_effect)
{
  cout << "in Plot_pseudo_experiments" << endl;
  cout << "local_rel_effect=" << local_rel_effect << endl;

  TCanvas *canvas_pseudo_experiments_rel_effect=new TCanvas("canvas_pseudo_experiments_rel_effect","canvas_pseudo_experiments_rel_effect",800,600);
  //  canvas_pseudo_experiments_rel_effect->SetRightMargin(0.03); //for sure
  //canvas_pseudo_experiments_rel_effect->SetRightMargin(0.05); //for sure

  canvas_pseudo_experiments_rel_effect->SetRightMargin(0.07); //for sure
  canvas_pseudo_experiments_rel_effect->SetTopMargin(0.03);
  
  TH1F *hist_dummy=canvas_pseudo_experiments_rel_effect->DrawFrame(hist_rel_effect->GetXaxis()->GetXmin(),1e-6,hist_rel_effect->GetXaxis()->GetXmax(),hist_rel_effect->GetMaximum()*2);

  //maybe next line is not useful because DrawFrame alreay draw ?
  //depends wether it takes care of the SetTitle and so on
  hist_dummy->Draw();

  if (string_observable=="position_shape")
    hist_dummy->GetXaxis()->SetTitle("100x(#mu_{syst}-#mu_{nominal})/#mu_{nominal} [%]");
  else if (string_observable=="spread_shape")
    hist_dummy->GetXaxis()->SetTitle("100x(#sigma_{syst}-#sigma_{nominal})/#sigma_{nominal} [%]");

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
  
  if (shape_root1_roofit2==1)
    latex.DrawLatex(0.15,0.72,"root");
  else if (shape_root1_roofit2==2)
    latex.DrawLatex(0.15,0.72,"roofit");
  
  if (shape_chi2fit_1_loglikelihoodfit2==1)
    latex.DrawLatex(0.15,0.67,"#chi^{2} fit");
  else if (shape_chi2fit_1_loglikelihoodfit2==2)
    latex.DrawLatex(0.15,0.67,"Log Likelihood fit");
  
  latex.SetTextColor(kRed);
  
  if (string_observable=="position_shape")
    sprintf(buffer,"rel. effect (%%) on #mu: %4.3f #pm %4.3f",local_rel_effect,local_err_rel_effect);
  else if (string_observable=="spread_shape")
    sprintf(buffer,"rel. effect (%%) on #sigma: %4.3f #pm %4.3f",local_rel_effect,local_err_rel_effect);
  latex.DrawLatexNDC(horizontal_position_baseline,vertical_position,buffer);

  printf("HERE, rel. effect (%%) on #sigma: %4.3f #pm %4.3f\n",local_rel_effect,local_err_rel_effect);

  vertical_position-=0.05;
  latex.SetTextColor(kBlack);

  if (string_method_partition_events=="bootstrap" || string_method_partition_events=="jacknife") {
    if (string_method_syst_shape=="fit")
      sprintf(buffer,"%s, %d converged / %d toys ",(string_method_partition_events+"_"+string_method_syst_shape).c_str(),nb_toys_converged,nb_toys_done);
    else if (string_method_syst_shape=="mean_IQR")
      sprintf(buffer,"%s, %d toys",(string_method_partition_events+"_"+string_method_syst_shape).c_str(),nb_toys_done);
    
    latex.DrawLatex(0.15,0.62,buffer);
    //    latex.DrawLatexNDC(horizontal_position_baseline,vertical_position,buffer);
  }
  
  string string_saveas=string_path+string_rel_path_shape+"figures/";

  string_saveas+=string_process;
  string_saveas+="/";
  string_saveas+=string_campaign_MxAOD;
  string_saveas+="/";
  string_saveas+=string_category;
  string_saveas+="/";
  string_saveas+=m_string_observable_shape;
  string_saveas+="/";
  string_saveas+=string_systematic;
  string_saveas+="/";

  string_saveas+="/Overview_";
  string_saveas+=string_method_partition_events;
  string_saveas+="_";
  string_saveas+=string_method_syst_shape;
  string_saveas+="_";
  
  string_saveas+=string_sample;
  string_saveas+="_rel_effect_";

  string_saveas+=string_observable;
  string_saveas+="_";
  string_saveas+=m_string_observable_shape;
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
//=============================================================================================================================================================================================
bool tool_syst_shape::IsRooRealVarAtLimit(RooRealVar *roorealvar)
{
  double roorealvar_min=roorealvar->getMin();
  double roorealvar_max=roorealvar->getMax();
  double roorealvar_val=roorealvar->getVal();
  
  cout << "-----" << endl;
  cout << "roorealvar->GetName()=" << roorealvar->GetName() << ", roorealvar->getMin()=" << roorealvar->getMin() << ", roorealvar->getMax()=" << roorealvar->getMax() << endl;
  cout << "roorealvar->getVal()=" << roorealvar->getVal() << endl;

  string string_name=roorealvar->GetName();

  //skip limits for nCB because no impact
  if (string_name.find("nCB")!=string::npos) //if variable is not nCB
    return 0;
  
  if (roorealvar_min!=0) {  //to avoir the problem of division by 0
    if (fabs((roorealvar->getVal()-roorealvar_min)/roorealvar_min)<0.01)
      return 1;
  }
  else if (fabs(roorealvar->getVal()-roorealvar_min)<0.01)
    return 1;
  
  if (fabs((roorealvar->getVal()-roorealvar_max)/roorealvar_max)<0.01)
    return 1;
  
  return 0;
}
//=============================================================================================================================================================================================
//=============================================================================================================================================================================================
/*
//    variante independent of bins : https://root.cern.ch/root/roottalk/roottalk01/3646.html
//for IQR, but too much CPU consuming
//keep that code here, just for information purpose

void sort() {
TFile f("hsimple.root");
TTree *tree = (TTree*)f.Get("ntuple");
Int_t nentries = (Int_t)tree->GetEntries();
//Drawing variable pz with no graphics option.
//variable pz stored in array fV1 (see TTree::Draw)
tree->Draw("pz","","goff");
Int_t *index = new Int_t[nentries];
//sort array containing pz in decreasing order
//The array index contains the entry numbers in decreasing order
of pz
TMath::Sort(nentries,tree->GetV1(),index);
	
//open new file to store the sorted Tree
TFile f2("hsimple_sorted.root","recreate");
//Create an empty clone of the original tree
TTree *tsorted = (TTree*)tree->CloneTree(0);
for (Int_t i=0;i<nentries;i++) {
tree->GetEntry(index[i]);
tsorted->Fill();
}
tsorted->Write();
delete [] index;
}
*/
//=============================================================================================================================================================================================
//For Francesco normalization for decorrelation model
//  if (string_functional_form=="ExpGaussExp")
//    hist_nominal_max*=hist_nominal_sigma*sqrt(TMath::TwoPi());
//=============================================================================================================================================================================================
vector <double> return_intersection(TH1D *hist_cumulative,double threshold)
{
  double Q_central;
  double Q_low;
  double Q_high;
  
  vector<double> vec_results;

  bool found_first_central=0;
  bool found_first_low=0;
  bool found_first_high=0;
  
  for (int index_bin=1;index_bin<=hist_cumulative->GetNbinsX();index_bin++) {
    if (!found_first_central && hist_cumulative->GetBinContent(index_bin)>=threshold) {
      found_first_central=1;
      Q_central=hist_cumulative->GetBinCenter(index_bin);
      //      cout << "Q_central=" << Q_central << endl;
    }
    
    if (!found_first_low && hist_cumulative->GetBinContent(index_bin)+hist_cumulative->GetBinError(index_bin)>=threshold) {
      found_first_low=1;
      Q_low=hist_cumulative->GetBinCenter(index_bin);
      //      cout << "Q_low=" << Q_low << endl;
    }
    
    if (!found_first_high && hist_cumulative->GetBinContent(index_bin)-hist_cumulative->GetBinError(index_bin)>=threshold) {
      found_first_high=1;
      Q_high=hist_cumulative->GetBinCenter(index_bin);
      //  cout << "Q_high=" << Q_high << endl;
    }
  } //end loop on bins of cumulative

  vec_results.push_back(Q_central);
  vec_results.push_back(Q_low);
  vec_results.push_back(Q_high);

  return vec_results;
}
//=============================================================================================================================================================================================
bool BelongToKnownSample(string string_sample)
{
  if (string_sample.find("HH_non_resonant_kappa_lambda_01")!=string::npos
      ||
      string_sample.find("HH_non_resonant_kappa_lambda_10")!=string::npos
      ||
      string_sample.find("PowhegH7_HHbbyy_cHHH01d0")!=string::npos
      ||
      string_sample.find("PowhegH7_HHbbyy_cHHH10d0")!=string::npos
      ||
      string_sample.find("aMCnloHwpp_hh_yybb")!=string::npos
      /*shit
      ||
      string_sample.find("aMCnloHwpp_hh_yybb_AF2")!=string::npos
      */
      ||
      string_sample.find("MGH7_hh_bbyy_vbf_l1cvv1cv1")!=string::npos
      ||
      //---------------------------------------------------------------------------------------------
      string_sample.find("SingleHiggs")!=string::npos
      ||
      string_sample.find("PowhegPy8_NNLOPS_ggH125")!=string::npos
      ||
      string_sample.find("ZH125")!=string::npos
      //shit      string_sample.find("PowhegPy8_ttH125")!=string::npos
      ||
      string_sample.find("ttH125")!=string::npos
      //---------------------------------------------------------------------------------------------
      ||
      string_sample.find("MGH7")!=string::npos
      )
    return 1;
  
  return 0;
}
//###################################################################################################
void tool_syst_shape::LoadTreeBootStrap(string string_category,string string_campaign_MxAOD,string string_systematic,string string_nominal_systematic)
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
  string_file_bootstrap+=m_string_observable_shape;
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

  //start block moved at the very bottom of the code
  /*shit if ok on full list of shape HH
  //else, to put in a trash

  string string_MxAODSyst_directory=ReturnMxAODSyst_directory(string_systematic);
  
  //to prevent accessing to subjobs files, it is mandatory that the subjobs trees are in subjobs directory, else they may be read by mistake instead of the merged sample

  //search for the file that will contains the current systematic
  string string_directory=string_path;
  
  cout << "string_systematic=" << string_systematic << endl;

  string_directory+=string_rel_path_shape;
  string_directory+="trees_and_hist/";
  
  string_directory+=ReturnMxAODSyst_directory(string_systematic);
  string_directory+="/";
  
  cout << "string_systematic=" << string_systematic << ", MxAOD directory=" << ReturnMxAODSyst_directory(string_systematic) << endl;
  string string_unix_command="ls ";
  string_unix_command+=string_directory;
  string_unix_command+=" |grep ";
  string_unix_command+=string_campaign_MxAOD;

  if (string_campaign_MxAOD=="h025_mc16a" || string_campaign_MxAOD=="h025_mc16d" || string_campaign_MxAOD=="h025_mc16e") {
    string_unix_command+=" |grep -v h025_mc16a_h025_mc16d | grep -v h025_mc16a_h025_mc16e | grep -v h025_mc16d_h025_mc16e | grep -v h025_mc16a_h025_mc16d_h025_mc16e";
  }
  
  string_unix_command+=" |grep ";
  string_unix_command+=string_process;

  //showering systematic made with an alternative approach

  //  string_unix_command+=" |grep -v nominal";

  char affix_range_toys[24]; //ok for sure, for 5 digits + 1 for \0

  if (string_method_partition_events=="bootstrap")
    sprintf(affix_range_toys,"_range_toys_%d_%d",index_start_toy_bootstrap,index_stop_toy_bootstrap);

  //to do : make a full path from previous program ?

  string string_list_candidates_files_containing_tree=string_path+string_rel_path_shape+"scratch/";

  string_list_candidates_files_containing_tree+=string_process;
  string_list_candidates_files_containing_tree+="/";
  string_list_candidates_files_containing_tree+=string_campaign_MxAOD;
  string_list_candidates_files_containing_tree+="/";
  string_list_candidates_files_containing_tree+=string_category;
  string_list_candidates_files_containing_tree+="/";
  string_list_candidates_files_containing_tree+=m_string_observable_shape;
  string_list_candidates_files_containing_tree+="/";
  string_list_candidates_files_containing_tree+=string_systematic;
  string_list_candidates_files_containing_tree+="/list_files_";
  string_list_candidates_files_containing_tree+=string_category;
  string_list_candidates_files_containing_tree+="_";
  string_list_candidates_files_containing_tree+=string_campaign_MxAOD;
  string_list_candidates_files_containing_tree+="_";
  string_list_candidates_files_containing_tree+=string_process;
  string_list_candidates_files_containing_tree+="_";
  string_list_candidates_files_containing_tree+=string_systematic;
  string_list_candidates_files_containing_tree+=suffix_asymmetry_systematic;

  if (string_method_partition_events=="bootstrap")
    string_list_candidates_files_containing_tree+=affix_range_toys;
  
  //replace space by underscore

  replace(string_list_candidates_files_containing_tree.begin(),string_list_candidates_files_containing_tree.end(),' ','_');
  
  cout << "string_list_candidates_files_containing_tree=" << string_list_candidates_files_containing_tree << endl;
  
  string_unix_command+=" > ";
  string_unix_command+=string_list_candidates_files_containing_tree;

  cout << "string_unix_command=" << string_unix_command << endl;
  gSystem->Exec(string_unix_command.c_str());

  ifstream stream_list_files;
  
  cout << "will open " << string_list_candidates_files_containing_tree << endl;

  stream_list_files.open(string_list_candidates_files_containing_tree.c_str());
  if (stream_list_files.fail()) {
    cout << "major problem : not able to open the file that has just been created, is there no more place on hard disk ?" << endl;
    cout << "halt program" << endl;
    exit(1);
  }

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
  
  string string_file_syst_shape_candidates; //candidate of file that would contains the appropriate systematic

  bool local_found=0; //could be improved if check the status of stream (later)

  //  char buffer[128];
  char buffer[256];
  while (stream_list_files.getline(buffer,256)) { // for all systematics
    string_file_syst_shape_candidates=string_directory;
    string_file_syst_shape_candidates+=buffer;

    cout << "-----" << endl;
    cout << "explore the file=" << string_file_syst_shape_candidates << endl;

    TFile *file_syst_shape_candidates=TFile::Open(string_file_syst_shape_candidates.c_str());
    //    file_syst_shape_candidates->ls();
    cout << "one searches for : " << string_to_search << endl;
    
    TList *list_keys=file_syst_shape_candidates->GetListOfKeys();
    
    int nb_keys=list_keys->GetSize();
    
    int index_key=0;
    
    for (;index_key<nb_keys;index_key++)  {
      string string_current_candidate=list_keys->At(index_key)->GetName();
      if (string_current_candidate==string_to_search) {
	cout << "found : " << string_current_candidate << endl;
	local_found=1;
	break; //break the current loop on keys
      }
    } //end search for tree candidates for current directory candidate
    
    //    cout << "close the file" << endl;
    file_syst_shape_candidates->Close();
    //    cout << "closed the file" << endl;
    delete file_syst_shape_candidates;
    file_syst_shape_candidates=0; //ADDED Marc
    
    if (index_key<nb_keys) //the key was found, quit the search
      break;
  } //end loop on directories
  
  stream_list_files.close();

  cout << "local_found=" << local_found << endl;
  //  exit(1);

  */
  //stop block moved at the very bottom of the code
