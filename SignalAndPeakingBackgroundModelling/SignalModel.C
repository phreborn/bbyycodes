bool do_MoriondQCD=1;

//for single Higgs, take private test

//careful of change of gg_HH_NLO to gg_HH

string string_put_error_yield="no"; //yes, no

//to do : add string_category for all functional forms : mandatory to be able to construct workspace simultenous pdfs

#include <RooMinimizer.h>

string string_method_fit="fitTo"; //fitTo, RooMinimizer

string string_version_MxAOD="h026"; //h025/h026

//to fit more in the core ? Maybe not actually

//to rename argset_finalDV_noWeight in argset_finalDV_only
////TO RENAME argset_noweight in argset_finalDV
//
////see "What is goal of this"
//see why warning of canvas deleted

//===================================================================================================
//Menu

string string_non_resonant_resonant="non_resonant";
//"non_resonant","resonant"

//===================================================================================================
//Instructions

//root -b SignalModel.C+
//results in results/m_yy/export
//===================================================================================================
//TO DO

//to make argset_finalDV with a special name including the weight

//to delete (free memory) the roofit result from the class ? and pdf total

////why pdf_total_current ?

//1) return sample signal : rename since sometimes 1-H=background

//2) to do : draw evolution : to transform into a vector, in the same style as spurious signal

//4) argset for draw : make a function

//5) export workspace : make a function

//6) argset for variables of parameters : make a function

//7) argset for mu position : make a function

////need to be launched in compilation mode
// root -b -q SignalModel.C+

// NEVER  for HH resonant, but always for HH non resonant yield part

//for vbf HH, take all events

//not for Py8

//for single Higgs, use private test
bool do_consider_private_test=0; //official decision 05/August/2020 : take everything : only for yield (never for shape)
bool do_consider_public_test=0;
bool do_consider_public_train=0; //only available for yield for the moment

bool do_binned=0;

bool do_cut_anyway=0;

bool do_fit_shape=1;
bool do_compute_yield=0;

//careful that yield is not necessary is the subrange of the cuts from the finalDV
//for that, one would need to add cuts or to use RooDataSet
//but no consequence for shape

// 6.22/00, 6.20/04 for writebuffer
//use at least root 6.20.00, for bug on fit range with several ranges

//time budget: for one sample (HH) in 2D : typically 45 minutes
//-----------------------------------------
//TO DO list

//for draw : make range ploted dynamic, especially for mbb !!

//-----------------------------------------
//have in a mind that Range is not necessary a bijection to a single roorealvar: it could be a different value for different roorealvar, with a same range name

//careful for whatever is chi2, to add one whenever it is not a extended pdf
//===================================================================================================================================================
//===================================================================================================================================================
//Choice of finalDV

vector<string> vec_string_finalDV={"m_yy"};
//vector<string> vec_string_finalDV={"m_bb"}; //do not put Single Higgs for m_bb, because is is made of several shapes, else fit will have trouble
//vector<string> vec_string_finalDV={"m_yy","m_bb"};

//vector<string> vec_string_finalDV={"m_yybb_tilde"};
//===================================================================================================================================================
vector<string> vec_string_latex_finalDV;
vector<string> vec_string_latex_root_finalDV;

vector<string> vec_string_signal_model;
//===================================
double hist_position_max=0;
double hist_position_FWHM_low=0;
double hist_position_FWHM_high=0;

double hist_sigma_effective=0;

//to put the name of the functional form

#include "includes.h"

#define NOT_SORTED 0
#define SORTED 1

using namespace RooFit;
using namespace std;

//to store in a different way or does it need to reorganize everything ? see spurious signal code

class result_f_process
{
public:
  vector<string> vec_string_process;
  vector<vector<string>> vec_string_functional_form;

  vector<vector<double>> vec_mu_model_chosen;
  vector<vector<double>> vec_err_mu_model_chosen;
  vector<vector<double>> vec_sigma_model_chosen;
  vector<vector<double>> vec_err_sigma_model_chosen;

  //-----
  //only for Double Crystal Ball
  vector<vector<double>> vec_alphaCB_Low;
  vector<vector<double>> vec_err_alphaCB_Low;
  vector<vector<double>> vec_nCB_Low;
  vector<vector<double>> vec_err_nCB_Low;

  vector<vector<double>> vec_alphaCB_High;
  vector<vector<double>> vec_err_alphaCB_High;
  vector<vector<double>> vec_nCB_High;
  vector<vector<double>> vec_err_nCB_High;
  //-----
  
  vector<vector<double>> vec_sigma68;
  //  vector<vector<double>> vec_sigma90;

  //RooArgList in order to be ordered
  //to rename
  vector<vector<RooArgList>> vec_arglist_parameters;

  vector<vector<int>> vec_n_params_functional_form;
  vector<double> vec_chi2;
  vector<double> vec_ndf;

  vector<double> vec_m_hyp_resonance;

  //  void Draw_observable_f_mX(string string_category,string string_observable_f_process,float string_process);
};

//to rename the field and class in characteristic ?
class result_yield_or_efficiency
{
public:
  double value;
  double err_value;
  string string_process;
};

map<string,map<string,result_yield_or_efficiency>> map_map_yield_f_category_f_process;
map<string,map<string,result_yield_or_efficiency>> map_map_efficiency_f_category_f_process;

#include "prototypes.h"

RooDataSet *dataset_current_category;
RooDataSet *datahist_current_category;

//RooArgSet is the best choice
RooArgSet argset_finalDV_noWeight; //argset of finalDVs

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

/*
float lumi_mc16a=36.20904;
float lumi_mc16d=44.3857;
float lumi_mc16e=58.4501;
*/
//references:
// /cvmfs/atlas.cern.ch/repo/sw/database/GroupData/GoodRunsLists/data18_13TeV/20190708/
// Luminosity:   3219.44 pb-1
// Luminosity:   32989.6 pb-1
// Luminosity:   44385.7 pb-1
// Luminosity:   58450.1 pb-1

float lumi=0;

vector<string> vec_string_category;

//f_functional_form

//TO DO : RENAME
vector<string> vec_functional_form_signal;

bool do_mc16a=1;
bool do_mc16d=1;
bool do_mc16e=1;
//do it only incremently: example: not 0 1 1

//from /cvmfs/atlas.cern.ch/repo/sw/database/GroupData/GoodRunsLists/
//notes.txt

FILE *fp_results;
FILE *fp_results_sorted;

RooRealVar *roorealvar_m_yy;
RooRealVar *roorealvar_m_bb;
RooRealVar *roorealvar_m_yybb_tilde;

vector<string> vec_string_process;

float counter_single_Higgs=0.5;

TChain *chain_ggH=0;
TChain *chain_VBF=0;
TChain *chain_qqZH=0;
TChain *chain_ggZH=0;
TChain *chain_ttH=0;
TChain *chain_tHjb=0;

TChain *chain_bbH=0;

TChain *chain_WH=0;
TChain *chain_tWH=0;

TChain *chain_gg_HH=0;
TChain *chain_vbf_HH=0;
TChain *chain_gg_vbf_HH=0;

string string_model=""; //never fill this : make it empty

//vector<float> vec_mX={251,260,280,300,325,350,400,450,500,550,600,700,800,900,1000};

//vector<float> vec_mX={270,290,312.5,337.5,375,425,475};

vector<float> vec_mX={251,260,270,280,290,300,312.5,325,337.5,350,375,400,425,450,475,500,550,600,700,800,900,1000};

bool do_export_workspace_HGam=0;
bool do_export_yaml_HGam=1;

//In python if one wants to read the file he just needs to do
//import yaml
//with open("filename.yaml") as f
//    dic = yaml.load(f)

TFile *file_output_workspace;
RooWorkspace *workspace;

fstream stream_yaml_SignalParametrization;
fstream stream_yaml_SignalYield;

map<string,result_f_process> map_current_results_f_process_f_category;



#include "ClassesFunctionalForms/RooTwoSidedCBShape.h"
#include "ClassesFunctionalForms/ExpGausExpPDF.h"

#include "FunctionalFormConfiguration.C"

#include "tool_ReturnSample.C"
#include "tool_PdfSignal.C"
#include "tool_ComputeChi2.C"

#include "tool_helper.C"
#include "tool_Draw.C"
//===========================================================================================================
int SignalModel()
{

  if (do_consider_private_test+do_consider_public_test+do_consider_public_train>1) {
    cout << "problem, exclusive conditions, halt program" << endl;
    exit(1);
  }

  //cout << "ROOT::Math::MinimizerOptions::DefaultPrecision()=" << ROOT::Math::MinimizerOptions::DefaultPrecision() << endl;

  //ROOT::Math::MinimizerOptions::SetDefaultPrecision(1e-1);
  //ROOT::Math::MinimizerOptions::SetDefaultPrecision(1e-2);
  //ROOT::Math::MinimizerOptions::SetDefaultPrecision(1e-3);
  //ROOT::Math::MinimizerOptions::SetDefaultPrecision(1e-4);
  //ROOT::Math::MinimizerOptions::SetDefaultPrecision(1e-5);
  //ROOT::Math::MinimizerOptions::SetDefaultPrecision(1e-6);

  //ROOT::Math::MinimizerOptions::SetDefaultPrecision(1e-8);
  //ROOT::Math::MinimizerOptions::SetDefaultPrecision(1e-9); //shit ?

  //  ROOT::Math::MinimizerOptions::SetDefaultPrecision(1e-12); //shit ?

  //cout << "ROOT::Math::MinimizerOptions::DefaultPrecision()=" << ROOT::Math::MinimizerOptions::DefaultPrecision() << endl;
  //  exit(1);
  
  cout << "Start SignalModel" << endl;

  if (do_fit_shape && do_compute_yield) {
    cout << "do_fit_shape and do_compute_yield: exclusive modes, else change code, else the modulo 4 is done twice" << endl;
    exit(1);
  }

  //avoid commenting warning : some bugs of roofit may not have message for debugging
  //RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);
  //prevent having warning when computing chi2/ndf with data-like statistics
  //enum MsgLevel { DEBUG=0, INFO=1, PROGRESS=2, WARNING=3, ERROR=4, FATAL=5 } ;
  
  //RooMsgService::instance().setSilentMode(true);
  //RooMsgService::instance().setStreamStatus(1,false);
  //RooMsgService::instance().setGlobalKillBelow(RooFit::DEBUG);

  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0000000);
  TH1::SetDefaultSumw2(1);

  if (do_mc16a)
    lumi+=lumi_mc16a;
  if (do_mc16d)
    lumi+=lumi_mc16d;
  if (do_mc16e)
    lumi+=lumi_mc16e;
  
  for (unsigned int index_finalDV=0;index_finalDV<vec_string_finalDV.size();index_finalDV++) {
    if (vec_string_finalDV[index_finalDV]=="m_yy") {
      vec_string_latex_finalDV.push_back("$m_{\\gamma\\gamma}$");
      vec_string_latex_root_finalDV.push_back("m_{#gamma#gamma}");
    }
    else if (vec_string_finalDV[index_finalDV]=="m_bb") {
      vec_string_latex_finalDV.push_back("$m_{bb}$");
      vec_string_latex_root_finalDV.push_back("m_{bb}");
    }
    else if (vec_string_finalDV[index_finalDV]=="m_yybb_tilde") {
      vec_string_latex_finalDV.push_back("$m_{\\gamma\\gamma bb\\ tilde}$");
      vec_string_latex_root_finalDV.push_back("m_{#gamma#gammabb tilde}");
    }
    else {
      cout << "problem" << endl;
      exit(1);
    }

    string_model+=vec_string_finalDV[index_finalDV];
    if (index_finalDV+1<vec_string_finalDV.size()) //if a next one exists
      string_model+="_and_";
  } //end constructing the model

  for (unsigned int index_vec_string_finalDV=0;index_vec_string_finalDV<vec_string_finalDV.size();index_vec_string_finalDV++) {
    cout << vec_string_finalDV[index_vec_string_finalDV] << endl;
    //    cout << vec_string_latex_finalDV[index_vec_string_finalDV] << endl;
  }

  cout << "compile RooTwoSidedCBShape" << endl;
  gROOT->ProcessLine(".L ClassesFunctionalForms/RooTwoSidedCBShape.cxx+");
  gSystem->Load("ClassesFunctionalForms/RooTwoSidedCBShape_cxx.so");

  cout << "compile ExpGausExpPDF" << endl;
  gROOT->ProcessLine(".L ClassesFunctionalForms/ExpGausExpPDF.cxx+");
  gSystem->Load("ClassesFunctionalForms/ExpGausExpPDF_cxx.so");

  gSystem->Exec("mkdir -p results");
  gSystem->Exec("mkdir -p figures");
  
  gSystem->Exec((string("mkdir -p results/")+string_non_resonant_resonant).c_str());
  gSystem->Exec((string("mkdir -p figures/")+string_non_resonant_resonant).c_str());

  gSystem->Exec((string("mkdir -p results/")+string_non_resonant_resonant+"/"+string_model).c_str());
  gSystem->Exec((string("mkdir -p results/")+string_non_resonant_resonant+"/"+string_model+"/export").c_str());
  gSystem->Exec((string("mkdir -p figures/")+string_non_resonant_resonant+"/"+string_model).c_str());

  //vec_string_category.push_back("baseline");

  FillListCategories();
  
  int n_processes=0;

  result_f_process current_results_f_process; //for a given category
  
  vec_string_process.clear();
  
  if (string_non_resonant_resonant=="non_resonant")
    FillListProcessNonResonant();
  else if (string_non_resonant_resonant=="resonant")
    FillListProcessResonant();
  
  n_processes=vec_string_process.size();
  
  if (do_export_workspace_HGam) {
    file_output_workspace=new TFile ("export/workspace.root","recreate");
    workspace=new RooWorkspace("signalWS");
    workspace->autoImportClassCode(1);
  }
  /*shit
    if (do_export_yaml_HGam) {
    stream_yaml_SignalParametrization.open("export/SignalParametrization.yaml",std::fstream::out);
    stream_yaml_SignalYield.open("export/resonance_yieldList.txt",std::fstream::out);
    }
  */
  
  for (unsigned int index_categ=0;index_categ<vec_string_category.size();index_categ++) { //category first, since it corresponds to line of various processes in the print-out
    string string_category=vec_string_category[index_categ];
    
    cout << "deal with category " << string_category << endl;
    
    counter_single_Higgs=0.5;
    
    for (int index_process=0;index_process<n_processes;index_process++) {
      string string_process=vec_string_process[index_process];

      cout << "index_process=" << index_process << ", " << string_process << endl;
      
      if (string_category!="Resonant") {
	if (string_process.find("_X")!=string::npos && ReturnResonantCorrespondingCategory(string_process)!=string_category)
	  continue;
      }
      
      Signal_given_category(index_categ,string_process,current_results_f_process);
      
      if (string_non_resonant_resonant=="non_resonant")
	counter_single_Higgs++;
      
      if (IsFinalDV_in_list("m_yy"))
	delete roorealvar_m_yy;
      
      if (IsFinalDV_in_list("m_bb"))
	delete roorealvar_m_bb;
      
      if (IsFinalDV_in_list("m_yybb_tilde"))
	delete roorealvar_m_yybb_tilde;
      
      argset_finalDV_noWeight.removeAll();
      
      vec_string_signal_model.clear();
    } //end loop on processes      
    
    cout << "PHASE C" << endl;
    map_current_results_f_process_f_category[string_category]=current_results_f_process; //store results

    if (do_fit_shape)  {
      
      cout << "PHASE D" << endl;

      cout << "call PrintOverviewResultsShape" << endl;

      PrintOverviewResultsShape(current_results_f_process,string_category.c_str());
      
      cout << "PHASE E" << endl;
      /*
	current_results_f_process.Draw_observable_f_mX(string_category.c_str(),"sigma68",-1); //default parameter does not work
	current_results_f_process.Draw_observable_f_mX(string_category.c_str(),"mu",-1); //default parameter does not work
	current_results_f_process.Draw_observable_f_mX(string_category.c_str(),"sigma68_mu",-1); //default parameter does not work
      */

      //===========================
      //shape parameters=f(sample), for a given category

      //      vector<string> vec_observables={"mu","sigma","sigma68"};
      
      cout << "PHASE A" << endl;
      cout << "phase i1" << endl;

      vector<string> vec_observables={"mu","sigma","sigma68","alphaCB_Low","nCB_Low","alphaCB_High","nCB_High"};
      
      for (unsigned int index_observable=0;index_observable<vec_observables.size();index_observable++) {
	
	string string_observable=vec_observables[index_observable];

	cout << "index_observable=" << index_observable << endl;

	for (unsigned int index_categ=0;index_categ<vec_string_category.size();index_categ++) { //category first, since it corresponds to line of various processes in the print-out

	  cout << "index_categ=" << index_categ << endl;

	  string string_category=vec_string_category[index_categ];
	  
	  vector<double> vec_double_characteristic;
	  vector<double> vec_observable_f_characteristic;
	  vector<double> vec_err_observable_f_characteristic;
	  
	  for (unsigned int index_finalDV=0;index_finalDV<vec_string_finalDV.size();index_finalDV++) {

	    cout << "index_finalDV=" << index_finalDV << endl;
	    
	    string string_finalDV=vec_string_finalDV[index_finalDV];
	    
	    for (unsigned int index_characteristic=0;index_characteristic<vec_string_process.size();index_characteristic++) {
	      
	      cout << "index_characteristic=" << index_characteristic << endl;

	      string string_process=vec_string_process[index_characteristic];

	      vec_double_characteristic.push_back(ReturnCharacteristic(string_process));
	      if (string_observable=="sigma68") {
		vec_observable_f_characteristic.push_back(current_results_f_process.vec_sigma68[index_characteristic][index_finalDV]);
		vec_err_observable_f_characteristic.push_back(0);
	      }
	      else if (string_observable=="mu") {
		vec_observable_f_characteristic.push_back(current_results_f_process.vec_mu_model_chosen[index_characteristic][index_finalDV]);
		vec_err_observable_f_characteristic.push_back(current_results_f_process.vec_err_mu_model_chosen[index_characteristic][index_finalDV]);
	      }
	      else if (string_observable=="sigma") {
		vec_observable_f_characteristic.push_back(current_results_f_process.vec_sigma_model_chosen[index_characteristic][index_finalDV]);
		vec_err_observable_f_characteristic.push_back(current_results_f_process.vec_err_sigma_model_chosen[index_characteristic][index_finalDV]);
	      }
	      else if (string_observable=="alphaCB_Low") {
		vec_observable_f_characteristic.push_back(current_results_f_process.vec_alphaCB_Low[index_characteristic][index_finalDV]);
		vec_err_observable_f_characteristic.push_back(current_results_f_process.vec_err_alphaCB_Low[index_characteristic][index_finalDV]);
	      }
	      else if (string_observable=="nCB_Low") {
		vec_observable_f_characteristic.push_back(current_results_f_process.vec_nCB_Low[index_characteristic][index_finalDV]);
		vec_err_observable_f_characteristic.push_back(current_results_f_process.vec_err_nCB_Low[index_characteristic][index_finalDV]);
	      }

	      else if (string_observable=="alphaCB_High") {
		vec_observable_f_characteristic.push_back(current_results_f_process.vec_alphaCB_High[index_characteristic][index_finalDV]);
		vec_err_observable_f_characteristic.push_back(current_results_f_process.vec_err_alphaCB_High[index_characteristic][index_finalDV]);
	      }
	      else if (string_observable=="nCB_High") {
		vec_observable_f_characteristic.push_back(current_results_f_process.vec_nCB_High[index_characteristic][index_finalDV]);
		vec_err_observable_f_characteristic.push_back(current_results_f_process.vec_err_nCB_High[index_characteristic][index_finalDV]);
	      }

	    } //end loop on characteristic

	    cout << "call Draw_observable_f_characteristic 1" << endl;
	    Draw_observable_f_characteristic(string_category,string_finalDV,string_observable,vec_string_process,vec_double_characteristic,vec_observable_f_characteristic,vec_err_observable_f_characteristic);
	    cout << "called Draw_observable_f_characteristic 1" << endl;

	    cout << "phase 1" << endl;
	    vec_double_characteristic.clear();

	    cout << "phase 2" << endl;
	    vec_observable_f_characteristic.clear();
	    cout << "phase 3" << endl;
	    vec_err_observable_f_characteristic.clear();
	    cout << "phase 4" << endl;
	  } //end loop finalDV
	  
	} //end loop on categories

      } //end loop on vector_observables (yield and efficiency)      

      cout << "phase i2" << endl;

      current_results_f_process.vec_string_process.clear();
      current_results_f_process.vec_string_functional_form.clear();
      current_results_f_process.vec_mu_model_chosen.clear();
      current_results_f_process.vec_err_mu_model_chosen.clear();
      current_results_f_process.vec_sigma_model_chosen.clear();
      current_results_f_process.vec_err_sigma_model_chosen.clear();
      
      current_results_f_process.vec_alphaCB_Low.clear();
      current_results_f_process.vec_err_alphaCB_Low.clear();
      current_results_f_process.vec_nCB_Low.clear();
      current_results_f_process.vec_err_nCB_Low.clear();
      
      current_results_f_process.vec_alphaCB_High.clear();
      current_results_f_process.vec_err_alphaCB_High.clear();
      current_results_f_process.vec_nCB_High.clear();
      current_results_f_process.vec_err_nCB_High.clear();
      
      current_results_f_process.vec_sigma68.clear();
      current_results_f_process.vec_chi2.clear();
      current_results_f_process.vec_ndf.clear();
      current_results_f_process.vec_m_hyp_resonance.clear();
      
      for (unsigned int index_finalDV=0;index_finalDV<argset_finalDV_noWeight.size();index_finalDV++) {
	
	current_results_f_process.vec_arglist_parameters[index_finalDV].clear();
	current_results_f_process.vec_n_params_functional_form[index_finalDV].clear();
      }
      
      cout << "last clear" << endl;
      
      current_results_f_process.vec_arglist_parameters.clear();
      
      current_results_f_process.vec_n_params_functional_form.clear();
      
      cout << "cleared" << endl;
    } //end do fit shape
    
    cout << "phase i2" << endl;

    if (do_compute_yield) {    //Yield

      for (unsigned int index_process=0;index_process<vec_string_process.size();index_process++) {
	
	string string_process=vec_string_process[index_process];

	string string_category_real=string_category;
	
	if (string_category=="Resonant" && string_process.find("_X"))
	  string_category_real=ReturnResonantCorrespondingCategory(string_process);
	
	ofstream stream_yield;

	stream_yield.open((string("results/")+string_non_resonant_resonant+"/"+string_model+"/export/"+"yield_proc_"+string_process+"_cat_"+string_category_real+".txt").c_str());
	
	//careful of the carriage return : do not factorize
	
	if (string_put_error_yield=="yes") {
	  stream_yield << map_map_yield_f_category_f_process[string_category_real][string_process].value;
	  stream_yield << " ";
	  stream_yield << map_map_yield_f_category_f_process[string_category_real][string_process].err_value << endl;
	}
	else
	  stream_yield << map_map_yield_f_category_f_process[string_category_real][string_process].value << endl;

	printf("yield=%10.10f\n",map_map_yield_f_category_f_process[string_category_real][string_process].value);

	stream_yield.close();
	
	ofstream stream_efficiency;
	
	stream_efficiency.open((string("results/")+string_non_resonant_resonant+"/"+string_model+"/export/"+"efficiency_proc_"+string_process+"_cat_"+string_category_real+".txt").c_str());


	
	//careful of the carriage return : do not factorize
	if (string_put_error_yield=="yes") {
	  stream_efficiency << map_map_efficiency_f_category_f_process[string_category_real][string_process].value;
	  stream_efficiency << " ";
	  stream_efficiency << map_map_efficiency_f_category_f_process[string_category_real][string_process].err_value << endl;
	}
	else
	  stream_efficiency << map_map_efficiency_f_category_f_process[string_category_real][string_process].value << endl;
	
	float local_characteristic=ReturnCharacteristic(string_process);

	//stream_efficiency << "#kappa_lambda efficiency err_efficiency" << endl;
	//stream_efficiency << local_characteristic << " " << map_map_efficiency_f_category_f_process[string_category_real][string_process].value << " " << map_map_efficiency_f_category_f_process[string_category_real][string_process].err_value << endl;
	
	stream_efficiency.close();
      }

    }
  } //end loop on categories

  cout << "phase I2" << endl;

  if (do_fit_shape) {
    
    //===========================
    //===========================
    //shape parameters=f(category), for a given sample
    
    cout << "shape parameters=f(category)" << endl;
    
    //for HH resonant only : TO DO A FLAG
    
    vector<string> vec_observables={"mu","sigma","sigma68"};
    
    for (unsigned int index_observable=0;index_observable<vec_observables.size();index_observable++) {
      
      cout << "index_observable=" << index_observable << endl;
      
      string string_observable=vec_observables[index_observable];
      
      for (unsigned int index_process=0;index_process<vec_string_process.size();index_process++) { //category first, since it corresponds to line of various processes in the print-out
	cout << "index_process=" << index_process << endl;
	string string_process=vec_string_process[index_process];
	
	//to put outside and clean ?
	vector<double> vec_double_characteristic;
	vector<double> vec_observable_f_characteristic;
	vector<double> vec_err_observable_f_characteristic;

	//TO DO : to do : shit ?	
	//it is redundant with the other part above ?

	for (unsigned int index_finalDV=0;index_finalDV<vec_string_finalDV.size();index_finalDV++) {
	  
	  cout << "index_finalDV=" << index_finalDV << endl;
	  
	  string string_finalDV=vec_string_finalDV[index_finalDV];
	  
	  for (unsigned int index_characteristic=0;index_characteristic<vec_string_category.size();index_characteristic++) { //characteristic is the category
	    
	    cout << "index_characteristic=" << index_characteristic << endl;
	    string string_category=vec_string_category[index_characteristic];
	    
	    cout << "vec_string_category[index_characteristic]=" << vec_string_category[index_characteristic] << endl;
	    vec_double_characteristic.push_back(ReturnCharacteristic_category(vec_string_category[index_characteristic]));
	    
	    cout << "string_observable=" << string_observable << endl;
	    
	    if (string_observable=="sigma68") {
	      vec_observable_f_characteristic.push_back(map_current_results_f_process_f_category[string_category].vec_sigma68[index_process][index_finalDV]);
	      vec_err_observable_f_characteristic.push_back(0);
	    }
	    else if (string_observable=="mu") {
	      vec_observable_f_characteristic.push_back(map_current_results_f_process_f_category[string_category].vec_mu_model_chosen[index_process][index_finalDV]);
	      vec_err_observable_f_characteristic.push_back(map_current_results_f_process_f_category[string_category].vec_err_mu_model_chosen[index_process][index_finalDV]);
	    }
	    else if (string_observable=="sigma") {
	      vec_observable_f_characteristic.push_back(map_current_results_f_process_f_category[string_category].vec_sigma_model_chosen[index_process][index_finalDV]);
	      vec_err_observable_f_characteristic.push_back(map_current_results_f_process_f_category[string_category].vec_err_sigma_model_chosen[index_process][index_finalDV]);
	    }
	  } //end loop on characteristic

	  //	  cout << "call Draw_observable_f_characteristic 2" << endl;
	  Draw_observable_f_characteristic("f_categories",string_finalDV,string_observable,vec_string_category,vec_double_characteristic,vec_observable_f_characteristic,vec_err_observable_f_characteristic);
	  //	  cout << "called Draw_observable_f_characteristic 2" << endl;

	  vec_double_characteristic.clear();
	  vec_observable_f_characteristic.clear();
	  vec_err_observable_f_characteristic.clear();
	} //end loop finalDV
	
      } //end loop on processes
    } //end loop on vector_observables (yield and efficiency)
  } //end do_fit_shape

  cout << "phase I3" << endl;
  if (do_export_workspace_HGam) {
    cout << "now writes the workspace" << endl;
    workspace->Write();
    file_output_workspace->Close();
    delete file_output_workspace;
  }
  
  /*
    if (do_export_yaml_HGam) {
    stream_yaml_SignalParametrization.close();
    stream_yaml_SignalYield.close();
    }
  */    
  





  cout << "phase I4" << endl;




  string string_category=vec_string_category[0];
  string string_process=vec_string_process[0];
  
  //to make function
  //------------------------------------------------
  if (do_compute_yield) {
    PrintResultYieldEfficiency("yield");
    
    PrintResultYieldEfficiency("efficiency");
  }

  //Draw yield=f(characteristic)
  
  if (do_compute_yield) {

    vector<string> vec_observables={"yield","efficiency"};
    
    for (unsigned int index_observable=0;index_observable<vec_observables.size();index_observable++) {
    
      cout << "index_observable=" << index_observable << endl;

      string string_observable=vec_observables[index_observable];

      for (unsigned int index_categ=0;index_categ<vec_string_category.size();index_categ++) { //category first, since it corresponds to line of various processes in the print-out

	cout << "index_categ=" << index_categ << endl;

	string string_category=vec_string_category[index_categ];

	vector<double> vec_double_characteristic;
	vector<double> vec_observable_f_characteristic;
	vector<double> vec_err_observable_f_characteristic;
	
	//to do for both yield and efficiency, with a vector of string
	
	for (unsigned int index_characteristic=0;index_characteristic<vec_string_process.size();index_characteristic++) {
	
	  cout << "index_characteristic=" << index_characteristic << endl;
	  
	  string string_process=vec_string_process[index_characteristic];

	  string string_category_real=string_category;
	  
	  if (string_category=="Resonant" && string_process.find("_X"))
	    string_category_real=ReturnResonantCorrespondingCategory(string_process);
    
	  cout << "string_process=" << string_process << endl;

	  vec_double_characteristic.push_back(ReturnCharacteristic(string_process));

	  cout << "string_observable" << string_observable << endl;

	  if (string_observable=="yield") {
	    
	    vec_observable_f_characteristic.push_back(map_map_yield_f_category_f_process[string_category_real][string_process].value);

	    vec_err_observable_f_characteristic.push_back(map_map_yield_f_category_f_process[string_category_real][string_process].err_value);
	  }
	  else if (string_observable=="efficiency") {

	    vec_observable_f_characteristic.push_back(map_map_efficiency_f_category_f_process[string_category_real][string_process].value);
	    vec_err_observable_f_characteristic.push_back(map_map_efficiency_f_category_f_process[string_category_real][string_process].err_value);
	  }
	  //	  cout << "index_characteristic=" << index_characteristic << ", map_map_yield_f_category_f_process[string_category_real][string_process].value=" << map_map_yield_f_category_f_process[string_category_real][string_process].value << endl;

	}

	cout << "call draw observable, for efficiency" << endl;

	cout << "call Draw_observable_f_characteristic 3" << endl;
	Draw_observable_f_characteristic(string_category,"",string_observable,vec_string_process,vec_double_characteristic,vec_observable_f_characteristic,vec_err_observable_f_characteristic);
	cout << "call Draw_observable_f_characteristic 3" << endl;

	vec_double_characteristic.clear();
	vec_observable_f_characteristic.clear();
	vec_err_observable_f_characteristic.clear();
      } //end loop on categories
    } //end loop on vector_observables (yield and efficiency)
  } //end do_compute_yield
  


  cout << "PHASE B" << endl;

  if (do_compute_yield) {
    
    //===========================
    //===========================
    //yield parameters=f(category), for a given sample
    
    cout << "yield parameters=f(category)" << endl;
    
    //for HH resonant only : TO DO A FLAG
    
    vector<string> vec_observables={"yield","efficiency"};
    
    for (unsigned int index_observable=0;index_observable<vec_observables.size();index_observable++) {
      
      cout << "index_observable=" << index_observable << endl;
      
      string string_observable=vec_observables[index_observable];
      
      for (unsigned int index_process=0;index_process<vec_string_process.size();index_process++) { //category first, since it corresponds to line of various processes in the print-out
	cout << "index_process=" << index_process << endl;
	string string_process=vec_string_process[index_process];
	
	//to put outside and clean ?
	vector<double> vec_double_characteristic;
	vector<double> vec_observable_f_characteristic;
	vector<double> vec_err_observable_f_characteristic;
	
	string string_finalDV=vec_string_finalDV[0];
	  
	  for (unsigned int index_characteristic=0;index_characteristic<vec_string_category.size();index_characteristic++) { //characteristic is the category
	    
	    cout << "index_characteristic=" << index_characteristic << endl;
	    string string_category=vec_string_category[index_characteristic];
	    
	    cout << "vec_string_category[index_characteristic]=" << vec_string_category[index_characteristic] << endl;
	    vec_double_characteristic.push_back(ReturnCharacteristic_category(vec_string_category[index_characteristic]));
	    
	    cout << "string_observable=" << string_observable << endl;
	    
	    if (string_observable=="yield") {
	      vec_observable_f_characteristic.push_back(map_map_yield_f_category_f_process[string_category][string_process].value);
	      vec_err_observable_f_characteristic.push_back(map_map_yield_f_category_f_process[string_category][string_process].err_value);
	    }
	    else if (string_observable=="efficiency") {
	      vec_observable_f_characteristic.push_back(map_map_efficiency_f_category_f_process[string_category][string_process].value);
	      vec_err_observable_f_characteristic.push_back(map_map_efficiency_f_category_f_process[string_category][string_process].err_value);
	    }
	  } //end loop on characteristic

	  cout << "call Draw_observable_f_characteristic 4" << endl;
	  Draw_observable_f_characteristic("f_categories",string_finalDV,string_observable,vec_string_category,vec_double_characteristic,vec_observable_f_characteristic,vec_err_observable_f_characteristic);
	  cout << "call Draw_observable_f_characteristic 4" << endl;

	  vec_double_characteristic.clear();
	  vec_observable_f_characteristic.clear();
	  vec_err_observable_f_characteristic.clear();
	  //shit	} //end loop finalDV
	
      } //end loop on processes
    } //end loop on vector_observables (yield and efficiency)
  } //end do_compute_yield


  //------------------------------------------------
  //clear result yield
  
  for (map<string,map<string,result_yield_or_efficiency>>::iterator it=map_map_yield_f_category_f_process.begin();it!=map_map_yield_f_category_f_process.end();++it) {
    map<string,result_yield_or_efficiency> &inner=it->second;
    inner.clear();
  }
  
  for (map<string,map<string,result_yield_or_efficiency>>::iterator it=map_map_efficiency_f_category_f_process.begin();it!=map_map_efficiency_f_category_f_process.end();++it) {
    map<string,result_yield_or_efficiency> &inner=it->second;
    inner.clear();
  }
  
  cout << "end clear" << endl;
  
  vec_string_process.clear();
  
  vec_string_finalDV.clear();
  vec_string_latex_finalDV.clear();
  vec_string_latex_root_finalDV.clear();
  
  cout << "end program" << endl;
  
  return 0;
}
//===========================================================================================================
int Signal_given_category(int index_category,string string_process,result_f_process &results_f_process)
{
  cout << "Start Signal_given_category" << endl;
  
  string string_category=vec_string_category[index_category]; //for yaml

  if (string_category=="Resonant" && string_process.find("_X"))
    string_category=ReturnResonantCorrespondingCategory(string_process);
  
  cout << "string_category=" << string_category << endl;

  //---------------------------------------------
  for (int i=0;i<10;i++)
    cout << "=======================================================================================" << endl;
  
  cout << "Treat Signal_given_category for categ=" << string_category << ", string_process=" << string_process << endl;

  vec_functional_form_signal.clear();

  //this makes sense to create the dataset only after the pdf, since the dataset could be constructed for example as an Asimov dataset  
  //-----------------------------------------------------------------------------
  SetExtensionFinalDV(string_process,string_category);

  //RooArgSet is the best choice: allowing RooArgSet in RooDataSet
  RooArgSet argset_finalDV;
  
  cout << "after creation of argset" << endl;
  cout << "argset_finalDV=" << argset_finalDV.size() << endl;
  cout << "argset_finalDV_noWeight=" << argset_finalDV_noWeight.size() << endl;

  if (IsFinalDV_in_list("m_yy")) {
    argset_finalDV.add(*roorealvar_m_yy);
    argset_finalDV_noWeight.add(*roorealvar_m_yy);
  }

  if (IsFinalDV_in_list("m_bb")) {
    argset_finalDV.add(*roorealvar_m_bb);
    argset_finalDV_noWeight.add(*roorealvar_m_bb);
  }

  if (IsFinalDV_in_list("m_yybb_tilde")) {
    argset_finalDV.add(*roorealvar_m_yybb_tilde);
    argset_finalDV_noWeight.add(*roorealvar_m_yybb_tilde);
  }

  if (argset_finalDV_noWeight.size()>2) {
    cout << "program not available for > 2 simultaneous final DV, halt program" << endl;
    argset_finalDV_noWeight.Print("v");
    exit(1);
  }

  RooRealVar *roorealvar_weight_total=0;

  roorealvar_weight_total=new RooRealVar("weight_total","weight_total",1);
  //roorealvar_weight_total=new RooRealVar("weight_event","weight_event",1);
  argset_finalDV.add(*roorealvar_weight_total);
  
  argset_finalDV_noWeight.Print();
  
  //-----------------------------
  //keep it there : not above : after the change of range of m_yy, else problems for debugging

  //3) prepare Pdf

  //functional forms

  //nominal

  //if take everything, crash after because of the dump of parameters of DBCB
  /*
  vec_functional_form_signal.push_back("Gaussian");
  vec_functional_form_signal.push_back("CrystalBall");
  */
  vec_functional_form_signal.push_back("DoubleCrystalBall");
  /*
  vec_functional_form_signal.push_back("Bukin");  
  vec_functional_form_signal.push_back("ExpGausExp");
  vec_functional_form_signal.push_back("Novosibirsk");
  */
  //----------------------------------------
  //vec_functional_form_signal.push_back("Modified_Landau");
  //not mature for non-resonant, vec_functional_form_signal.push_back("Modified_Gamma");

  //need to have done the ReturnWindow, in order to define the window !!

  TChain *chain_process=ReturnSampleSignal(string_process,string_category);

  cout << "chain_process=" << chain_process << endl;
  //  chain_process->Print();

  cout << "after, entries=" << chain_process->GetEntries() << endl;

  //--------------------------  
  if (do_cut_anyway) {
    RooArgSet argset_finalDV_patch;
    argset_finalDV_patch.add(*roorealvar_m_yy);
    argset_finalDV_patch.add(*roorealvar_m_bb);
    argset_finalDV_patch.add(*roorealvar_weight_total);
    
    dataset_current_category=new RooDataSet("dataset_current_category","dataset_current_category",argset_finalDV_patch,RooFit::Import(*chain_process),RooFit::Cut("m_bb>47.5 && m_bb<162.5"),RooFit::WeightVar(*roorealvar_weight_total));
  }
  else
    dataset_current_category=new RooDataSet("dataset_current_category","dataset_current_category",argset_finalDV,RooFit::Import(*chain_process),RooFit::WeightVar(*roorealvar_weight_total));

  cout << "dataset_current_category->numEntries()=" << dataset_current_category->numEntries() << endl;
  cout << "dataset_current_category->sumEntries()=" << dataset_current_category->sumEntries() << endl;
  cout << "====================================================================" << endl;

  //debugging
  //   double total_weight=0;
  //   for (int index_event=0;index_event<dataset_current_category->numEntries();index_event++) {
  
  //     RooArgSet *argset=(RooArgSet *)dataset_current_category->get(index_event);
  
  //     double observable_value=argset->getRealValue("m_yy");
  //     double weight=dataset_current_category->weight();
  
  //     total_weight+=weight;
  
  //     cout << "m_yy=" << observable_value << ", weight=" << weight << ", so far, Total weight=" << total_weight << endl;
  //   }

  pair<double,double> pair_yield;

  cout << "hello, string_process=" << string_process << endl;

  if (do_compute_yield) {
    
    //to put first  
    if (string_process.find("gg_vbf_HH")!=string::npos) {
      //      pair_yield=GetYield_given_process(chain_gg_vbf_HH,string_category);


      pair_yield=GetYield_given_process(string_process,chain_gg_vbf_HH,string_category);
      
      delete chain_gg_vbf_HH;
    }
    
    else if (
	     string_process.find("gg_HH")!=string::npos 
	     ||
	     string_process.find("PowhegPy8_HHbbyy_cHHH01d0")!=string::npos 
	     ||
	     string_process.find("gg_X")!=string::npos
	     ) {
      //      pair_yield=GetYield_given_process(chain_gg_HH,string_category);
      pair_yield=GetYield_given_process(string_process,chain_gg_HH,string_category);
      
      delete chain_gg_HH;
    }
    
    else if (string_process.find("vbf_HH")!=string::npos) {
      //pair_yield=GetYield_given_process(chain_vbf_HH,string_category);
      pair_yield=GetYield_given_process(string_process,chain_vbf_HH,string_category);

      delete chain_vbf_HH;
    }
    
    else { //1-H processes
      
      pair<double,double> pair_yield_ggH;
      pair<double,double> pair_yield_vbf;
      pair<double,double> pair_yield_qqZH;
      pair<double,double> pair_yield_ggZH;
      pair<double,double> pair_yield_ttH;
      pair<double,double> pair_yield_tHjb;

      pair<double,double> pair_yield_WH;
      pair<double,double> pair_yield_bbH;
      pair<double,double> pair_yield_tWH;
      
      if (string_process=="SingleHiggs") {
	pair_yield_ggH=GetYield_given_process(string_process,chain_ggH,string_category);
	delete chain_ggH;
	
	pair_yield_vbf=GetYield_given_process(string_process,chain_VBF,string_category);
	delete chain_VBF;

	pair_yield_qqZH=GetYield_given_process(string_process,chain_qqZH,string_category);
	delete chain_qqZH;
	
	pair_yield_ggZH=GetYield_given_process(string_process,chain_ggZH,string_category);
	delete chain_ggZH;
	
	pair_yield_ttH=GetYield_given_process(string_process,chain_ttH,string_category);
	delete chain_ttH;

	pair_yield_tHjb=GetYield_given_process(string_process,chain_tHjb,string_category);
	delete chain_tHjb;
	//-----
	pair_yield_WH=GetYield_given_process(string_process,chain_WH,string_category);
	delete chain_WH;

	pair_yield_bbH=GetYield_given_process(string_process,chain_bbH,string_category);
	delete chain_bbH;

	pair_yield_tWH=GetYield_given_process(string_process,chain_tWH,string_category);
	delete chain_tWH;
	//-----
	pair_yield.first=pair_yield_ggH.first+pair_yield_vbf.first+pair_yield_WH.first+pair_yield_qqZH.first+pair_yield_ggZH.first+pair_yield_ttH.first+pair_yield_bbH.first+pair_yield_tHjb.first+pair_yield_tWH.first;
	
	pair_yield.second=sqrt(pow(pair_yield_ggH.second,2)+pow(pair_yield_vbf.second,2)+pow(pair_yield_WH.second,2)+pow(pair_yield_qqZH.second,2)+pow(pair_yield_ggZH.second,2)+pow(pair_yield_ttH.second,2)+pow(pair_yield_bbH.second,2)+pow(pair_yield_tHjb.second,2)+pow(pair_yield_tWH.second,2));
	
	/*old
	pair_yield.first=pair_yield_ggH.first+pair_yield_qqZH.first+pair_yield_ggZH.first+pair_yield_ttH.first+pair_yield_tHjb.first+pair_yield_vbf.first;
	pair_yield.second=sqrt(pow(pair_yield_ggH.second,2)+pow(pair_yield_qqZH.second,2)+pow(pair_yield_ggZH.second,2)+pow(pair_yield_ttH.second,2)+pow(pair_yield_tHjb.second,2)+pow(pair_yield_vbf.second,2));
	*/
	   
      }
      
      else if (string_process=="ggH") {
	pair_yield=GetYield_given_process(string_process,chain_ggH,string_category);
	
	delete chain_ggH;
      }

      else if (string_process=="VBF") {
	pair_yield=GetYield_given_process(string_process,chain_VBF,string_category);
	
	delete chain_VBF;
      }

      else if (string_process=="WH") {
	pair_yield=GetYield_given_process(string_process,chain_WH,string_category);
	
	delete chain_WH;
      }
      
      else if (string_process=="ZH") {
	pair_yield_qqZH=GetYield_given_process(string_process,chain_qqZH,string_category);
	delete chain_qqZH;
	
	pair_yield_ggZH=GetYield_given_process(string_process,chain_ggZH,string_category);
	delete chain_ggZH;
	
	pair_yield.first=pair_yield_qqZH.first+pair_yield_ggZH.first;
	pair_yield.second=sqrt(pow(pair_yield_qqZH.second,2)+pow(pair_yield_ggZH.second,2));
      }
      
      else if (string_process=="ttH") {
	pair_yield=GetYield_given_process(string_process,chain_ttH,string_category);
	
	delete chain_ttH;
      }

      else if (string_process=="bbH") {
	pair_yield=GetYield_given_process(string_process,chain_bbH,string_category);
	
	delete chain_bbH;
      }
      
      else if (string_process=="tHjb") {
	pair_yield=GetYield_given_process(string_process,chain_tHjb,string_category);
	
	delete chain_tHjb;
      }

      else if (string_process=="tWH") {
	pair_yield=GetYield_given_process(string_process,chain_tWH,string_category);
	
	delete chain_tWH;
      }
    }
    
    cout << "store yield" << endl;
    
    //store yield
    
    map_map_yield_f_category_f_process[string_category][string_process].value=pair_yield.first;
    map_map_yield_f_category_f_process[string_category][string_process].err_value=pair_yield.second;
    
    map_map_efficiency_f_category_f_process[string_category][string_process].value=map_map_yield_f_category_f_process[string_category][string_process].value/(lumi*1e15*GetCrossSectionTimesBR(string_process));
    map_map_efficiency_f_category_f_process[string_category][string_process].err_value=map_map_yield_f_category_f_process[string_category][string_process].err_value/(lumi*1e15*GetCrossSectionTimesBR(string_process));

    cout << "string_category=" << string_category << ", string_process=" << string_process << endl;

    cout << "map_map_yield_f_category_f_process[string_category][string_process].value=" << map_map_yield_f_category_f_process[string_category][string_process].value << endl;
    cout << "map_map_efficiency_f_category_f_process[string_category][string_process].value=" << map_map_efficiency_f_category_f_process[string_category][string_process].value << endl;

    cout << "map_map_yield_f_category_f_process[string_category][string_process].value=" << map_map_yield_f_category_f_process[string_category][string_process].value << endl;
    cout << "lumi=" << lumi << endl;
    cout << "GetCrossSectionTimesBR(string_process)=" << GetCrossSectionTimesBR(string_process) << endl;
    
  } //end do compute yield
  
  /*
  if (do_export_yaml_HGam) { //only implemented for case of one variable
    stream_yaml_SignalYield << "125 ";

    int local_index_category; //to implement here in case
    if (string_category=="baseline")
      local_index_category=0;
    stream_yaml_SignalYield << local_index_category << " ";
    
    //Aleksei Put here your total yield of the current category
    stream_yaml_SignalYield << " " << pair_yield.first << endl;
  }
  */
  
  if (!do_fit_shape)
    return 0;

  //============================================================================================================================
  //---------------------------
  cout << "argset_finalDV_noWeight.size()=" << argset_finalDV_noWeight.size() << endl;

  unsigned int max_index_functional_form_signal_second=0;
  if (argset_finalDV_noWeight.size()==1)
    max_index_functional_form_signal_second=1;
  else if (argset_finalDV_noWeight.size()>=2)
    max_index_functional_form_signal_second=vec_functional_form_signal.size();

  cout << "max_index_functional_form_signal_second=" << max_index_functional_form_signal_second << endl;

  //decide from p-value, because best chi2/ndf is not necessary best p-value : it is true only for a same ndf, else some inversions cases exist
  //drawback of p-value, only if not using double, we could have values of exactly 0, thus it would not allow to discriminate between several cases. With double, it is fine enough

  double best_p_value=-std::numeric_limits<float>::max();
  double best_chi2_over_ndf_value=std::numeric_limits<float>::max();

  vector<string> vec_string_functional_form_model_chosen;
  vector<int> vec_n_params_functional_form_model_chosen;

  vector<RooArgList> vec_arglist_parameters_model_chosen;

  vector<double> vec_mu_model_chosen;
  vector<double> vec_err_mu_model_chosen;
  vector<double> vec_sigma_model_chosen;
  vector<double> vec_err_sigma_model_chosen;

  vector<double> vec_alphaCB_Low;
  vector<double> vec_err_alphaCB_Low;
  vector<double> vec_nCB_Low;
  vector<double> vec_err_nCB_Low;

  vector<double> vec_alphaCB_High;
  vector<double> vec_err_alphaCB_High;
  vector<double> vec_nCB_High;
  vector<double> vec_err_nCB_High;

  vector<double> vec_sigma68_model_chosen;
  vector<double> vec_sigma90_model_chosen;

  //mandatory unique algorithm solution, since reserve does not change size and one needs to write directly in the index, in the loop over functional form candidates
  for (unsigned int index_finalDV=0;index_finalDV<argset_finalDV_noWeight.size();index_finalDV++) {
    vec_string_functional_form_model_chosen.push_back("");
    vec_n_params_functional_form_model_chosen.push_back(0);
    vec_arglist_parameters_model_chosen.push_back(RooArgList());
    vec_mu_model_chosen.push_back(0);
    vec_err_mu_model_chosen.push_back(0);
    vec_sigma_model_chosen.push_back(0);
    vec_err_sigma_model_chosen.push_back(0);
    
    vec_alphaCB_Low.push_back(0);
    vec_err_alphaCB_Low.push_back(0);
    vec_nCB_Low.push_back(0);
    vec_err_nCB_Low.push_back(0);
    
    vec_alphaCB_High.push_back(0);
    vec_err_alphaCB_High.push_back(0);
    vec_nCB_High.push_back(0);
    vec_err_nCB_High.push_back(0);

    vec_sigma68_model_chosen.push_back(0);
    vec_sigma90_model_chosen.push_back(0);
  }

  vector<FunctionalFormConfiguration> vec_functional_form_config;
  
  //special study
  //  for (unsigned int index_functional_form_signal_first=0;index_functional_form_signal_first<1;index_functional_form_signal_first++) {
  
  //general
  for (unsigned int index_functional_form_signal_first=0;index_functional_form_signal_first<vec_functional_form_signal.size();index_functional_form_signal_first++) {
    
    cout << "index_functional_form_signal_first=" << index_functional_form_signal_first << endl;
    
    //general
    for (unsigned int index_functional_form_signal_second=0;index_functional_form_signal_second<max_index_functional_form_signal_second;index_functional_form_signal_second++) {
    
      //special study  
      //for (unsigned int index_functional_form_signal_second=1;index_functional_form_signal_second<2;index_functional_form_signal_second++) {

      cout << "index_functional_form_signal_second=" << index_functional_form_signal_second << endl;
      
      FunctionalFormConfiguration functional_form_config;

      functional_form_config.string_category=string_category;

      //no need to clear since each time since this is a new one

      functional_form_config.vec_string_functional_form.push_back(vec_functional_form_signal[index_functional_form_signal_first]);
      if (argset_finalDV_noWeight.size()>=2)
	functional_form_config.vec_string_functional_form.push_back(vec_functional_form_signal[index_functional_form_signal_second]);
    
      for (int i=0;i<10;i++)
	cout << "=======================================================================================================" << endl;
      cout << "Treat Functional Form: " << functional_form_config.vec_string_functional_form[0];
      if (argset_finalDV_noWeight.size()>=2)
	cout << ", " << functional_form_config.vec_string_functional_form[1];
    
      cout << endl;

      //TO DO make a function, with keyword from_hist for a given variable

      //90 % to small, in particular for m_gamgam

      //      double percentage_window_hist=0.95;

      cout << "argset_finalDV_noWeight.size()=" << argset_finalDV_noWeight.size() << endl;

      for (unsigned int index_finalDV=0;index_finalDV<argset_finalDV_noWeight.size();index_finalDV++) {
	
	//TO DO : make function

	//BEGIN TO MAKE FUNCTION
	RooRealVar *roorealvar_finalDV=((RooRealVar *)(RooArgList(argset_finalDV_noWeight)).at(index_finalDV));
	string string_finalDV=roorealvar_finalDV->GetName();

	double percentage_window_hist=0.97;
	
	if (string_finalDV=="m_yy")
	  //	  percentage_window_hist=0.98;
	  percentage_window_hist=0.99;
	else
	  percentage_window_hist=0.95;
	  //0.95: too high for m_bb : example Gauss, ggH,	  percentage_window_hist=0.95;
	
	//	percentage_window_hist=0.90;

	double preferred_low_x=-99999;  //final solution to search for
	double preferred_high_x=99999;

	//see if could be removed for other case, or this is blocks code, example for SingleHiggs
	ReturnWindowFromDatasetInitFitParameters(percentage_window_hist,chain_process,string_process,string_finalDV,&preferred_low_x,&preferred_high_x);

	if (string_finalDV=="m_yy") {
	  
	  //to use for HH
	  	  
	  preferred_low_x=115;
	  preferred_high_x=135;
	  	  
	  /*
	  preferred_low_x=114;
	  preferred_high_x=136;
	  */

	  /*
	  //developments
	  preferred_low_x=118;
	  preferred_high_x=132;
	  */

	}
	else
	  ReturnWindowFromDatasetInitFitParameters(percentage_window_hist,chain_process,string_process,string_finalDV,&preferred_low_x,&preferred_high_x);
	
	//	cout << "define a new range" << endl;
	roorealvar_finalDV->setRange("fitrange",preferred_low_x,preferred_high_x);
	
	cout << "preferred_low_x=" << preferred_low_x << ", preferred_high_x=" << preferred_high_x << endl;

	//	exit(1);
	//	cout << "min=" << roorealvar_finalDV->getRange("fitrange").first << ", max=" << roorealvar_finalDV->getRange("fitrange").second << endl;
	
	//BEGIN TO MAKE FUNCTION

	cout << "phase 1" << endl;

	functional_form_config.vec_pdf_signal_model.push_back(ReturnPdfSignal(functional_form_config.vec_string_functional_form[index_finalDV],index_finalDV,string_category));

	cout << "phase 2" << endl;
	/*
	//------------------------
	//for fixing to a given set of parameter : for debugging
	
	functional_form_config.vec_pdf_signal_model[functional_form_config.vec_pdf_signal_model.size()-1]->Print("v");

	RooArgSet *argset_shape=(RooArgSet *)((RooArgSet *)functional_form_config.vec_pdf_signal_model[functional_form_config.vec_pdf_signal_model.size()-1]->getParameters(argset_finalDV_noWeight))->selectByAttrib("Constant",kFALSE);
	
	argset_shape->Print("v");
	cout << endl;
	
	//	argset_shape->readFromFile("results/m_bb/datacard_resonant_baseline_260.txt");
	//argset_shape->readFromFile("results/m_bb/datacard_resonant_baseline_500.txt");
	argset_shape->readFromFile("results/m_bb/datacard_resonant_baseline_1000.txt");
	
	argset_shape->Print("v");
	cout << endl;
	
	for (unsigned int index_param=0;index_param<argset_shape->size();index_param++) {
	  RooRealVar *roorealvar=((RooRealVar *)(RooArgList(*argset_shape)).at(index_param));

	  roorealvar->setConstant(1);
	}
	
	argset_shape->Print("v");
	*/

	//------------------------
      } //end loop on finalDV
      
      cout << "info on chosen pdf(s):" << endl;
      for (unsigned int index_finalDV=0;index_finalDV<argset_finalDV_noWeight.size();index_finalDV++) {
	cout << "index_finalDV=" << index_finalDV << ", pdf_signal_model=" << functional_form_config.vec_pdf_signal_model[index_finalDV] << endl;
	
	//	functional_form_config.vec_pdf_signal_model[index_finalDV]->Print();
      }
      
      cout << endl;

      //determine nb of parameters
      
      for (unsigned int index_finalDV=0;index_finalDV<argset_finalDV_noWeight.size();index_finalDV++) {
	cout << endl;
	cout << "index_finalDV=" << index_finalDV << endl;
	
	RooRealVar *roorealvar_finalDV=((RooRealVar *)(RooArgList(argset_finalDV)).at(index_finalDV));
	
	RooArgSet *argset_parameters=(RooArgSet *) functional_form_config.vec_pdf_signal_model[index_finalDV]->getParameters(RooArgSet(*roorealvar_finalDV))->selectByAttrib("Constant",kFALSE);

	functional_form_config.vec_n_params.push_back( ( (RooArgSet *) functional_form_config.vec_pdf_signal_model[index_finalDV]->getParameters(RooArgSet(*roorealvar_finalDV))->selectByAttrib("Constant",kFALSE) )->getSize() );
      }
      //---------------------------------------------------------
      //product pdf in case of 2D fit

      //-----
      RooArgList arglist_pdfs_for_rooprodpdf_signal;
    
      for (unsigned int index_finalDV=0;index_finalDV<argset_finalDV_noWeight.size();index_finalDV++) {
	arglist_pdfs_for_rooprodpdf_signal.add(*functional_form_config.vec_pdf_signal_model[index_finalDV]);
      }
            
      functional_form_config.pdf_total_current=new RooProdPdf("prodpdf_signal_model","prodpdf_signal_model",arglist_pdfs_for_rooprodpdf_signal);
      
      //===========================================================================================
      cout << "=====================================" << endl;
      cout << "=====================================" << endl;
      cout << "=====================================" << endl;
      //    cout << "index_category=" << index_category << endl;
    
      //    index_category_for_tree=index_category+1;

      //representative parameter in the signal pdf that expresses the mH position, in order to be able to shift the signal model
      //context is restore after the fit, to prevent a constant shift

      //determine the signal window: used for both defining the range to explore
      //and the blinding part for sidebands fit
      
      
      //determine the range to explore
      
      float preferred_low_bin;
      float preferred_high_bin;
      
      //if one wish to force to only a single mH    
      
      cout << "phase main body 2" << endl;
      
      //restore context: restore representative mH variables (muCB, etc.) of signal model to its original values
      
      cout << "argset_finalDV_noWeight.size()=" << argset_finalDV_noWeight.size() << endl;
      
      for (int i=0;i<5;i++)
	cout << "----------------------------" << endl;
      //--------------------------------------
      //----------
      //if necessary, to add offset option

      functional_form_config.pdf_total_current->Print();

      int nbins_mc;
      int nparams_mc;

      string string_range_fit="fitrange";
      
      RooDataHist *datahist_current_category=0;

      RooFitResult *roofitresult=0;

      //FIX HERE
      //       ((RooRealVar *)functional_form_config.pdf_total_current->getVariables()->find((string("alphaCB_Low_m_yy")).c_str()))->setVal(1.6);
      //       ((RooRealVar *)functional_form_config.pdf_total_current->getVariables()->find((string("alphaCB_High_m_yy")).c_str()))->setVal(1.55);
      
      //       ((RooRealVar *)functional_form_config.pdf_total_current->getVariables()->find((string("alphaCB_Low_m_yy")).c_str()))->setConstant(1);
      //       ((RooRealVar *)functional_form_config.pdf_total_current->getVariables()->find((string("alphaCB_High_m_yy")).c_str()))->setConstant(1);

      if (do_binned) {
	datahist_current_category=dataset_current_category->binnedClone();
	roofitresult=functional_form_config.pdf_total_current->chi2FitTo(*datahist_current_category,RooFit::Range("fitrange"),RooFit::Save(kTRUE));
      }
      else {
	//------------------
	if (string_method_fit=="RooMinimizer") { //approach RooMinimizer
	  
	  cout << "create nll" << endl;
	  RooAbsReal* nll=functional_form_config.pdf_total_current->createNLL(*dataset_current_category,RooFit::Range("fitrange"));
	  cout << "created nll" << endl;
	  
	  //using copy of RooMinimizer, in order to have public a given method : trick from Kunlin Ran
	  
	  RooMinimizerExt *roominimize=new RooMinimizerExt(*nll);
	  
	  //	RooMinimizer *roominimize=new RooMinimizer(*nll);
	  
	  //try setMinimizerType()
	  //hesse()
	  //etc.
	  //----------------------------------------------------
	  //roominimize->setEps(1e-1);
	  //roominimize->setEps(1e-2);
	  
	  //	  roominimize->setEps(1e-3);
	  //	  roominimize->setEps(1e-4);
	  //roominimize->setEps(1e-5);
	  //roominimize->setEps(1e-6);
	  
	  //roominimize->setEps(1e-8);

	  //	  roominimize->setEps(1e-9);

	  //roominimize->setEps(1e-12);
	  
	  
	  //	char buffer_fit_option[256];	
	  //	sprintf(buffer_fit_option,"RooFit::Minimizer(\"Minuit2\",\"migrad\"),RooFit::Offset(1),RooFit::Hesse(1),RooFit::SumW2Error(1),RooRooFit::Range(fitrange)");
	  //	sprintf(buffer_fit_option,"RooFit::Minimizer(\"Minuit2\",\"migrad\"),RooFit::Offset(1),RooFit::Hesse(1),RooFit::SumW2Error(1)");
	  
	  //	cout << "buffer_fit_option=" << buffer_fit_option << endl;
	  //careful : for fit(...), the options have no effect : not supported
	  
	  roominimize->minimize("Minuit2","Migrad");
	  roofitresult=roominimize->save("","");
	  
	  //	roofitresult=roominimize->fit(buffer_fit_option);
	  //	roofitresult=roominimize->fit("r");
	  
	  cout << "fit finished" << endl;
	  
	  cout << "nll->getVal()=" << nll->getVal() << endl;
	  
	  AddSumw2(nll,roominimize);
	} // end RooMinimizer
	else if (string_method_fit=="fitTo") {
	  //------------------
	  //standard fit
	  int index_iteration=0;
	  
	  //	RooRealVar *roorealvar_sigmaCB=((RooRealVar *)functional_form_config.pdf_total_current->getVariables()->find("sigmaCB_m_yy"));
	  
	  //	roorealvar_sigmaCB->Print();
	  
	  //next option seems crashing
	  //roofitresult=functional_form_config.pdf_total_current->fitTo(*dataset_current_category,RooFit::Range("fitrange"),AsymptoticError(kTRUE),RooFit::Save(kTRUE));
	  
	  //standard, historical
	  roofitresult=functional_form_config.pdf_total_current->fitTo(*dataset_current_category,RooFit::Range("fitrange"),RooFit::SumW2Error(kTRUE),RooFit::Save(kTRUE));
	  
	  cout << "fitting second time" << endl;
	  //Fitting twice helps for some cases, worst for others ! To use ?

	  //fit twice : for resonant ?
	  //try also for non resonant
	  roofitresult=functional_form_config.pdf_total_current->fitTo(*dataset_current_category,RooFit::Range("fitrange"),RooFit::SumW2Error(kTRUE),RooFit::Save(kTRUE));
	  
	  //Minuit2
	  //roofitresult=functional_form_config.pdf_total_current->fitTo(*dataset_current_category,RooFit::Range("fitrange"),RooFit::SumW2Error(kTRUE),RooFit::Minimizer("Minuit2","migrad"),RooFit::Hesse(1),RooFit::Save(kTRUE));

	  //Strategy2
	  //roofitresult=functional_form_config.pdf_total_current->fitTo(*dataset_current_category,RooFit::Range("fitrange"),RooFit::SumW2Error(kTRUE),RooFit::Strategy(2),RooFit::Save(kTRUE));
	  
	  //Offset
	  //roofitresult=functional_form_config.pdf_total_current->fitTo(*dataset_current_category,RooFit::Range("fitrange"),RooFit::SumW2Error(kTRUE),RooFit::Offset(1),RooFit::Save(kTRUE));
	  
	  //Minos
	  //roofitresult=functional_form_config.pdf_total_current->fitTo(*dataset_current_category,RooFit::Range("fitrange"),RooFit::Minos(RooArgSet(*roorealvar_sigmaCB)),RooFit::SumW2Error(kTRUE),RooFit::Save(kTRUE));
	  //roofitresult=functional_form_config.pdf_total_current->fitTo(*dataset_current_category,RooFit::Range("fitrange"),RooFit::SumW2Error(kTRUE),RooFit::Minos(1),RooFit::Save(kTRUE));	
	  
	  //	cout << "string_process=" << string_process << ", sigmaCB=" << roorealvar_sigmaCB->getVal() << " +/- " << roorealvar_sigmaCB->getError() << endl;
	  
	  index_iteration++;
	  
	  int MAX_ITERATIONS=3;
	  
	  //Minuit documentation https://cds.cern.ch/record/2296388/files/minuit.pdf
	  
	  while (index_iteration<MAX_ITERATIONS && !(roofitresult->status()==0 && ( roofitresult->covQual()==-1 || roofitresult->covQual()==3))) {
	    
	    delete roofitresult;
	    
	    //reduce range by 1 GeV in case of difficulty
	    RooRealVar *roorealvar_finalDV=((RooRealVar *)(RooArgList(argset_finalDV_noWeight)).at(0));
	    
	    double preferred_low_x=roorealvar_finalDV->getRange("fitrange").first;
	    double preferred_high_x=roorealvar_finalDV->getRange("fitrange").second;
	    
	    preferred_low_x+=1;
	    preferred_high_x-=1;
	    
	    cout << "index_iteration=" << index_iteration << endl;
	    cout << "configure range fit to :" << endl;
	    
	    cout << "preferred_low_x=" << preferred_low_x << ", preferred_high_x=" << preferred_high_x << endl;
	    
	    roorealvar_finalDV->setRange("fitrange",preferred_low_x,preferred_high_x);
	    
	    cout << "makes the fit, with index_iteration=" << index_iteration << endl;
	    roofitresult=functional_form_config.pdf_total_current->fitTo(*dataset_current_category,RooFit::Range("fitrange"),RooFit::SumW2Error(kTRUE),RooFit::Save(kTRUE));
	    
	    index_iteration++;
	  }
	}
	else {
	  cout << "case of fit not anticipated, halt program" << endl;
	  exit(1);
	}
      } //end unbinned fit

      if (roofitresult) {
	cout << "summary of fit status history for " << string_process << endl;
	for (unsigned int i=0;i<roofitresult->numStatusHistory();i++)
	  cout << i << ", type=" << roofitresult->statusLabelHistory(i) << " code = " << roofitresult->statusCodeHistory(i) << std::endl;
	cout << "================================" << endl;
	cout << "results for fit" << endl;
	cout << "string_process=" << string_process << endl;
	cout << "string_category=" << string_category << endl;
	cout << "status fit=" << roofitresult->status() << endl;
	cout << "covQual()=" << roofitresult->covQual() << endl;
      }
      
      //dump of parameters obtained
      cout << "dump of fitted parameters" << endl;
      functional_form_config.pdf_total_current->getVariables()->Print("v");

      RooRealVar *roorealvar_sigmaCB=(RooRealVar *)functional_form_config.pdf_total_current->getVariables()->find(((string("sigmaCB")+"_"+"m_yy"+"_"+string_category).c_str()));
      
      cout << "roorealvar_sigmaCB=" << roorealvar_sigmaCB->getVal() << " +/- " << roorealvar_sigmaCB->getError() << endl;

      //NO MORE !!      delete roofitresult; //mandatory

      functional_form_config.roofitresult=roofitresult;

      //      exit(1);

      //      functional_form_config.pdf_total_current->getVariables()->Print("v");
      //      exit(1);

      if (do_binned)
	ComputeChi2_ndf(functional_form_config.chi2_MC_like_stat,functional_form_config.ndf_MC_like_stat,nbins_mc,nparams_mc,(RooDataSet *)datahist_current_category,functional_form_config.pdf_total_current);
      else
	ComputeChi2_ndf(functional_form_config.chi2_MC_like_stat,functional_form_config.ndf_MC_like_stat,nbins_mc,nparams_mc,(RooDataSet *)dataset_current_category,functional_form_config.pdf_total_current);
	  
      functional_form_config.chi2_over_ndf_MC_like_stat=functional_form_config.chi2_MC_like_stat/functional_form_config.ndf_MC_like_stat;
	  
      functional_form_config.p_value_MC_like_stat=TMath::Prob(functional_form_config.chi2_MC_like_stat,functional_form_config.ndf_MC_like_stat);

      cout << "chi2=" << functional_form_config.chi2_MC_like_stat << endl;
      cout << "ndf=" << functional_form_config.ndf_MC_like_stat << endl;
      cout << "functional_form_config.ndf_MC_like_stat=" << functional_form_config.ndf_MC_like_stat << endl;
      //	  printf("p_value=%5.5g\n",functional_form_config.p_value_MC_like_stat);

      for (unsigned int index_finalDV=0;index_finalDV<argset_finalDV_noWeight.size();index_finalDV++) {
	RooRealVar *roorealvar_finalDV=((RooRealVar *)(RooArgList(argset_finalDV)).at(index_finalDV));
	string string_finalDV=roorealvar_finalDV->GetName();	
	
	double left_window_68;
	double right_window_68;
	double left_window_90;
	double right_window_90;
	
	//compute sigma68
	ReturnWindow(0.68,functional_form_config.vec_pdf_signal_model[index_finalDV],string_finalDV,125,&left_window_68,&right_window_68,string_category);
	//	      ReturnWindow(0.90,functional_form_config.vec_pdf_signal_model[index_finalDV],string_finalDV,125,&left_window_90,&right_window_90);
	
	functional_form_config.vec_sigma68.push_back(0.5*(right_window_68-left_window_68));
	//functional_form_config.vec_sigma90.push_back(0.5*(right_window_90-left_window_90));
      } //end loop on finalDV
      
      if (functional_form_config.p_value_MC_like_stat>best_p_value
	  ||
	  (functional_form_config.p_value_MC_like_stat==best_p_value && functional_form_config.chi2_over_ndf_MC_like_stat<best_chi2_over_ndf_value)
	  ) { //consider case where all functional forms are crazy and have p-value of 0, in this case, use the chi2/ndf to rank them
	cout << "new best value" << endl;
	
	cout << "index_functional_form_signal_first=" << index_functional_form_signal_first << endl;
	cout << "index_functional_form_signal_second=" << index_functional_form_signal_second << endl;

	printf("functional_form_config.p_value_MC_like_stat=%10.10e, chi2/ndf=%10.10e\n",functional_form_config.p_value_MC_like_stat,functional_form_config.chi2_over_ndf_MC_like_stat);
	best_p_value=functional_form_config.p_value_MC_like_stat;
	best_chi2_over_ndf_value=functional_form_config.chi2_over_ndf_MC_like_stat;
	  //	best_chi2_ndf_value=functional_form_config.chi2_over_ndf_MC_like_stat;
	    
	for (unsigned int index_finalDV=0;index_finalDV<argset_finalDV_noWeight.size();index_finalDV++) {
	      
	  //	      cout << "index_finalDV=" << index_finalDV << endl;

	  //	      cout << "functional_form_config.vec_string_functional_form[index_finalDV]=" << functional_form_config.vec_string_functional_form[index_finalDV] << endl;

	  vec_string_functional_form_model_chosen[index_finalDV]=functional_form_config.vec_string_functional_form[index_finalDV];

	  RooRealVar *roorealvar_finalDV=((RooRealVar *)(RooArgList(argset_finalDV)).at(index_finalDV));
	  string string_finalDV=roorealvar_finalDV->GetName();

	  vec_n_params_functional_form_model_chosen[index_finalDV]=functional_form_config.vec_n_params[index_finalDV];

	  vec_arglist_parameters_model_chosen[index_finalDV].removeAll(); //mandatory


	  //TO DO SIMPLIFY ACCESS : DIRECT from INFO in ReturnEffectiveSigma

	  cout << "vec_string_functional_form_model_chosen[index_finalDV]=" << vec_string_functional_form_model_chosen[index_finalDV] << endl;

	  //TO DO: problem for clone if several ones ? maybe could not happen by construction
	  //selectByName is not appropriate solution, because it returns a name parameters_selected

	  if (vec_string_functional_form_model_chosen[index_finalDV]=="Gaussian") {
	    vec_arglist_parameters_model_chosen[index_finalDV].add( * (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("muGauss_")+string_finalDV).c_str())->clone((string("muGauss_")+string_finalDV+"_"+string_process).c_str()) );
	    vec_arglist_parameters_model_chosen[index_finalDV].add( * (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("sigmaGauss_")+string_finalDV).c_str())->clone((string("sigmaGauss_")+string_finalDV+"_"+string_process).c_str()) );
	    vec_mu_model_chosen[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("muGauss_")+string_finalDV).c_str()))->getVal();
	    vec_err_mu_model_chosen[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("muGauss_")+string_finalDV).c_str()))->getError();
	    vec_sigma_model_chosen[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("sigmaGauss_")+string_finalDV).c_str()))->getVal();
	    vec_err_sigma_model_chosen[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("sigmaGauss_")+string_finalDV).c_str()))->getError();
	  }
	  else if (vec_string_functional_form_model_chosen[index_finalDV]=="CrystalBall") {
	    vec_arglist_parameters_model_chosen[index_finalDV].add( * (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("mu_simple_CB_")+string_finalDV).c_str())->clone((string("mu_simple_CB_")+string_finalDV+"_"+string_process).c_str()) );
	    vec_arglist_parameters_model_chosen[index_finalDV].add( * (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("sigma_simple_CB_")+string_finalDV).c_str())->clone((string("sigma_simple_CB_")+string_finalDV+"_"+string_process).c_str()) );
	    vec_arglist_parameters_model_chosen[index_finalDV].add( * (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("alphaCB_")+string_finalDV).c_str())->clone((string("alphaCB_")+string_finalDV+"_"+string_process).c_str()) );
	    vec_arglist_parameters_model_chosen[index_finalDV].add( * (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("nCB_")+string_finalDV).c_str())->clone((string("nCB_")+string_finalDV+"_"+string_process).c_str()) );
	    
	    vec_mu_model_chosen[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("mu_simple_CB_")+string_finalDV).c_str()))->getVal();
	    vec_err_mu_model_chosen[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("mu_simple_CB_")+string_finalDV).c_str()))->getError();
	    vec_sigma_model_chosen[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("sigma_simple_CB_")+string_finalDV).c_str()))->getVal();
	    vec_err_sigma_model_chosen[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("sigma_simple_CB_")+string_finalDV).c_str()))->getError();

	  }
	  else if (vec_string_functional_form_model_chosen[index_finalDV]=="DoubleCrystalBall") {
	    vec_arglist_parameters_model_chosen[index_finalDV].add( * (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("muCB_")+string_finalDV+"_"+string_category).c_str())->clone((string("muCB_")+string_finalDV+"_proc_"+string_process+"_cat_"+string_category).c_str()) );
	    vec_arglist_parameters_model_chosen[index_finalDV].add( * (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("sigmaCB_")+string_finalDV+"_"+string_category).c_str())->clone((string("sigmaCB_")+string_finalDV+"_proc_"+string_process+"_cat_"+string_category).c_str()) );
	    vec_arglist_parameters_model_chosen[index_finalDV].add( * (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("alphaCB_Low_")+string_finalDV+"_"+string_category).c_str())->clone((string("alphaCB_Low_")+string_finalDV+"_proc_"+string_process+"_cat_"+string_category).c_str()) );
	    vec_arglist_parameters_model_chosen[index_finalDV].add( * (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("nCB_Low_")+string_finalDV+"_"+string_category).c_str())->clone((string("nCB_Low_")+string_finalDV+"_proc_"+string_process+"_cat_"+string_category).c_str()) );
	    vec_arglist_parameters_model_chosen[index_finalDV].add( * (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("alphaCB_High_")+string_finalDV+"_"+string_category).c_str())->clone((string("alphaCB_High_")+string_finalDV+"_proc_"+string_process+"_cat_"+string_category).c_str()) );
	    vec_arglist_parameters_model_chosen[index_finalDV].add( * (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("nCB_High_")+string_finalDV+"_"+string_category).c_str())->clone((string("nCB_High_")+string_finalDV+"_proc_"+string_process+"_cat_"+string_category).c_str()) );
	    
	    vec_mu_model_chosen[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("muCB_")+string_finalDV+"_"+string_category).c_str()))->getVal();
	    vec_err_mu_model_chosen[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("muCB_")+string_finalDV+"_"+string_category).c_str()))->getError();
	    vec_sigma_model_chosen[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("sigmaCB_")+string_finalDV+"_"+string_category).c_str()))->getVal();
	    vec_err_sigma_model_chosen[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("sigmaCB_")+string_finalDV+"_"+string_category).c_str()))->getError();
	    
	    cout << "phase 1" << endl;
	    vec_alphaCB_Low[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("alphaCB_Low_")+string_finalDV+"_"+string_category).c_str()))->getVal();
	    cout << "phase 2" << endl;
	    vec_err_alphaCB_Low[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("alphaCB_Low_")+string_finalDV+"_"+string_category).c_str()))->getError();
	    cout << "phase 3" << endl;
	    vec_nCB_Low[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("nCB_Low_")+string_finalDV+"_"+string_category).c_str()))->getVal();
	    cout << "phase 4" << endl;
	    vec_err_nCB_Low[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("nCB_Low_")+string_finalDV+"_"+string_category).c_str()))->getError();

	    cout << "phase 5" << endl;

	    vec_alphaCB_High[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("alphaCB_High_")+string_finalDV+"_"+string_category).c_str()))->getVal();
	    cout << "phase 6" << endl;
	    vec_err_alphaCB_High[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("alphaCB_High_")+string_finalDV+"_"+string_category).c_str()))->getError();
	    cout << "phase 7" << endl;
	    vec_nCB_High[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("nCB_High_")+string_finalDV+"_"+string_category).c_str()))->getVal();
	    cout << "phase 8" << endl;
	    vec_err_nCB_High[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("nCB_High_")+string_finalDV+"_"+string_category).c_str()))->getError();
	    cout << "phase 9" << endl;
	  }
	  else if (vec_string_functional_form_model_chosen[index_finalDV]=="Bukin") {
	    vec_arglist_parameters_model_chosen[index_finalDV].add( * (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("muBukin_")+string_finalDV).c_str())->clone((string("muBukin_")+string_finalDV+"_"+string_process).c_str()) );
	    vec_arglist_parameters_model_chosen[index_finalDV].add( * (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("sigmaBukin_")+string_finalDV).c_str())->clone((string("sigmaBukin_")+string_finalDV+"_"+string_process).c_str()) );
	    vec_arglist_parameters_model_chosen[index_finalDV].add( * (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("xiBukin_")+string_finalDV).c_str())->clone((string("xiBukin_")+string_finalDV+"_"+string_process).c_str()) );
	    vec_arglist_parameters_model_chosen[index_finalDV].add( * (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("rho1Bukin_")+string_finalDV).c_str())->clone((string("rho1Bukin_")+string_finalDV+"_"+string_process).c_str()) );
	    vec_arglist_parameters_model_chosen[index_finalDV].add( * (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("rho2Bukin_")+string_finalDV).c_str())->clone((string("rho2Bukin_")+string_finalDV+"_"+string_process).c_str()) );

	    vec_mu_model_chosen[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("muBukin_")+string_finalDV).c_str()))->getVal();
	    vec_err_mu_model_chosen[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("muBukin_")+string_finalDV).c_str()))->getError();
	    vec_sigma_model_chosen[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("sigmaBukin_")+string_finalDV).c_str()))->getVal();
	    vec_err_sigma_model_chosen[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("sigmaBukin_")+string_finalDV).c_str()))->getError();
	  }
	  else if (vec_string_functional_form_model_chosen[index_finalDV]=="ExpGausExp") {
	    vec_arglist_parameters_model_chosen[index_finalDV].add( * (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("muExpGausExp_")+string_finalDV).c_str())->clone((string("muExpGausExp_")+string_finalDV+"_"+string_process).c_str()) );
	    vec_arglist_parameters_model_chosen[index_finalDV].add( * (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("sigmaExpGausExp_")+string_finalDV).c_str())->clone((string("sigmaExpGausExp_")+string_finalDV+"_"+string_process).c_str()) );
	    vec_arglist_parameters_model_chosen[index_finalDV].add( * (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("slopeExp_Low_")+string_finalDV).c_str())->clone((string("slopeExp_Low_")+string_finalDV+"_"+string_process).c_str()) );
	    vec_arglist_parameters_model_chosen[index_finalDV].add( * (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("slopeExp_High_")+string_finalDV).c_str())->clone((string("slopeExp_High_")+string_finalDV+"_"+string_process).c_str()) );
	    
	    vec_mu_model_chosen[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("muExpGausExp_")+string_finalDV).c_str()))->getVal();
	    vec_err_mu_model_chosen[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("muExpGausExp_")+string_finalDV).c_str()))->getError();
	    vec_sigma_model_chosen[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("sigmaExpGausExp_")+string_finalDV).c_str()))->getVal();
	    vec_err_sigma_model_chosen[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("sigmaExpGausExp_")+string_finalDV).c_str()))->getError();
	  }	      
	  else if (vec_string_functional_form_model_chosen[index_finalDV]=="Novosibirsk") {
	    vec_arglist_parameters_model_chosen[index_finalDV].add( * (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("peak_Novosibirsk_")+string_finalDV).c_str())->clone((string("peak_Novosibirsk_")+string_finalDV+"_"+string_process).c_str()) );
	    vec_arglist_parameters_model_chosen[index_finalDV].add( * (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("width_Novosibirsk_")+string_finalDV).c_str())->clone((string("width_Novosibirsk_")+string_finalDV+"_"+string_process).c_str()) );
	    vec_arglist_parameters_model_chosen[index_finalDV].add( * (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("tail_Novosibirsk_")+string_finalDV).c_str())->clone((string("tail_Novosibirsk_")+string_finalDV+"_"+string_process).c_str()) );
		
	    vec_mu_model_chosen[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("peak_Novosibirsk_")+string_finalDV).c_str()))->getVal();
	    vec_err_mu_model_chosen[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("peak_Novosibirsk_")+string_finalDV).c_str()))->getError();
	    vec_sigma_model_chosen[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("width_Novosibirsk_")+string_finalDV).c_str()))->getVal();
	    vec_err_sigma_model_chosen[index_finalDV]=((RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("width_Novosibirsk_")+string_finalDV).c_str()))->getError();
	  }

	  // 	  double left_window_68;
	  // 	  double right_window_68;
	  // 	  double left_window_90;
	  // 	  double right_window_90;
	  
	  // 	  ReturnWindow(0.68,functional_form_config.vec_pdf_signal_model[index_finalDV],string_finalDV,125,&left_window_68,&right_window_68);
	  //	      ReturnWindow(0.90,functional_form_config.vec_pdf_signal_model[index_finalDV],string_finalDV,125,&left_window_90,&right_window_90);
	  //vec_sigma68_model_chosen[index_finalDV]=0.5*(right_window_68-left_window_68);
	  //	      vec_sigma90_model_chosen[index_finalDV]=0.5*(right_window_90-left_window_90);

	  vec_sigma68_model_chosen[index_finalDV]=functional_form_config.vec_sigma68[index_finalDV];
	  //	  vec_sigma90_model_chosen[index_finalDV]=functional_form_config.vec_sigma90[index_finalDV];

	} //end loop on finalDV
      } //end new best result

      if (do_binned)      
	functional_form_config.Draw_pdfs_current_category(string_process,(RooDataSet *)datahist_current_category);
      else
	functional_form_config.Draw_pdfs_current_category(string_process,(RooDataSet *)dataset_current_category);
      //======================================

      //parameters of pdf
      for (unsigned int index_finalDV=0;index_finalDV<argset_finalDV_noWeight.size();index_finalDV++) {
	cout << "prepare to store index_finalDV=" << index_finalDV << " over" << argset_finalDV_noWeight.size() << endl;
	    
	RooRealVar *roorealvar_finalDV=((RooRealVar *) RooArgList(argset_finalDV_noWeight).at(index_finalDV));
	    
	string string_finalDV=roorealvar_finalDV->GetName();
	    
	RooArgSet *floatPars;
	    
	RooAbsArg *absarg;
	TIterator *iter;
	    
	floatPars=(RooArgSet *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getParameters(argset_finalDV_noWeight)->selectByAttrib("Constant",kFALSE);

	//WHAT IS GOAL OF THAT : NOT USED ?!?
	//SHIT ? TO COMMENT AND KEEP A BIT

	RooArgList arglist_param;

	if (functional_form_config.vec_string_functional_form[index_finalDV]=="Gaussian") {
	  arglist_param.add(* (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("muGauss_")+string_finalDV).c_str()));
	  arglist_param.add(* (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("sigmaGauss_")+string_finalDV).c_str()));
	}
	else if (functional_form_config.vec_string_functional_form[index_finalDV]=="CrystalBall") {
	  arglist_param.add(* (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("mu_simple_CB_")+string_finalDV).c_str()));
	  arglist_param.add(* (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("sigma_simple_CB_")+string_finalDV).c_str()));
	  arglist_param.add(* (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("alphaCB_")+string_finalDV).c_str()));
	  arglist_param.add(* (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("nCB_")+string_finalDV).c_str()));
	}
	else if (functional_form_config.vec_string_functional_form[index_finalDV]=="DoubleCrystalBall") {
	  arglist_param.add(* (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("muCB_")+string_finalDV+"_"+string_category).c_str()));
	  arglist_param.add(* (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("sigmaCB_")+string_finalDV+"_"+string_category).c_str()));
	  arglist_param.add(* (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("alphaCB_Low_")+string_finalDV+"_"+string_category).c_str()));
	  arglist_param.add(* (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("nCB_Low_")+string_finalDV+"_"+string_category).c_str()));
	  arglist_param.add(* (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("alphaCB_High_")+string_finalDV+"_"+string_category).c_str()));
	  arglist_param.add(* (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("nCB_High_")+string_finalDV+"_"+string_category).c_str()));
	}
	else if (functional_form_config.vec_string_functional_form[index_finalDV]=="Bukin") {
	  arglist_param.add(* (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("muBukin_")+string_finalDV).c_str()));
	  arglist_param.add(* (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("sigmaBukin_")+string_finalDV).c_str()));
	  arglist_param.add(* (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("xiBukin_")+string_finalDV).c_str()));
	  arglist_param.add(* (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("rho1Bukin_")+string_finalDV).c_str()));
	  arglist_param.add(* (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("rho2Bukin_")+string_finalDV).c_str()));
	}
	else if (functional_form_config.vec_string_functional_form[index_finalDV]=="ExpGausExp") {
	  arglist_param.add(* (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("muExpGausExp_")+string_finalDV).c_str()));
	  arglist_param.add(* (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("sigmaExpGausExp_")+string_finalDV).c_str()));
	  arglist_param.add(* (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("slopeExp_Low_")+string_finalDV).c_str()));
	  arglist_param.add(* (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("slopeExp_High_")+string_finalDV).c_str()));
	}
	else if (functional_form_config.vec_string_functional_form[index_finalDV]=="Novosibirsk") {
	  arglist_param.add(* (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("peak_Novosibirsk_")+string_finalDV).c_str()));
	  arglist_param.add(* (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("width_Novosibirsk_")+string_finalDV).c_str()));
	  arglist_param.add(* (RooRealVar *)functional_form_config.vec_pdf_signal_model[index_finalDV]->getVariables()->find((string("tail_Novosibirsk_")+string_finalDV).c_str()));
	}

	arglist_param.removeAll();
      } //end loop on final DV
      
      //add in vector of list of candidates, in order to be able to provide the sorted Table      
      vec_functional_form_config.push_back(functional_form_config);

      cout << "clear pdf vec_pdf_signal_model" << endl;
      
      functional_form_config.vec_pdf_signal_model.clear();
      functional_form_config.vec_string_functional_form.clear();
      functional_form_config.vec_sigma68.clear();
      
      cout << "inside second functional form" << endl;
    } //end loop on second functional form	  
    cout << "inside first functional form" << endl;
  } //end loop on functional form first

  cout << "phase after loop on functional forms" << endl;
  //----------
  unsigned int nb_functional_forms=vec_functional_form_config.size();

  //to make it in a function, in order to be able to call it twice

  //ii) print the results

  //  (a) not sorted
  PrintHeaderResults(&fp_results,string_process,string_category,NOT_SORTED);
  
  cout << "called PrintHeader for non_sorted" << endl;

  //  cout << "phase 5" << endl;




  cout << "store results" << endl;
  for (unsigned int index_functional_form=0;index_functional_form<nb_functional_forms;index_functional_form++) {

    for (unsigned int index_finalDV=0;index_finalDV<argset_finalDV_noWeight.size();index_finalDV++) {
      fprintf(fp_results,"%s         &%d",vec_functional_form_config[index_functional_form].vec_string_functional_form[index_finalDV].c_str(),vec_functional_form_config[index_functional_form].vec_n_params[index_finalDV]);
      
      fprintf(fp_results,"       &%6.2f",vec_functional_form_config[index_functional_form].vec_sigma68[index_finalDV]);
      
      if (index_finalDV+1<argset_finalDV_noWeight.size())
	fprintf(fp_results,"    &");
    }
    
    fprintf(fp_results,"        &%4.2f (%4.2f/%d)",
	    vec_functional_form_config[index_functional_form].chi2_over_ndf_MC_like_stat,
	    vec_functional_form_config[index_functional_form].chi2_MC_like_stat,
	    vec_functional_form_config[index_functional_form].ndf_MC_like_stat);
    
    fprintf(fp_results,"        &%6.3g",vec_functional_form_config[index_functional_form].p_value_MC_like_stat);

    fprintf(fp_results,"\\\\\n");
    
    fprintf(fp_results,"\\hline\n");

  } //end loop on functional form

  PrintTailResults(&fp_results,string_process,string_category);


	//shape parameters: option: do not remove it
	/*
	unsigned int index_param=0;

	  for (;index_param<arglist_param.size();index_param++) {
	      
	  cout << "index_param=" << index_param << endl;

	  RooRealVar *roorealvar=(RooRealVar *)arglist_param.at(index_param);
	      
	  cout << "roorealvar=" << roorealvar << endl;

	  string string_title_roorealvar=roorealvar->GetTitle();
	      
	  boost::replace_all(string_title_roorealvar,"#","\\");
	  boost::replace_all(string_title_roorealvar," ","\\ ");
	      
	  cout << "debug12" << endl;


	  //fprintf(fp_results,"        &$%s$=%6.3f +/- %6.3f",string_title_roorealvar.c_str(),roorealvar->getVal(),roorealvar->getError());
	      
	  fprintf(fp_results,"        &$%s$=%6.3f",string_title_roorealvar.c_str(),roorealvar->getVal()); //no need to provide error
	  
	  //if (strcmp(roorealvar->getUnit(),"")) //unit
	  //fprintf(fp_results,"       %s",roorealvar->getUnit());
	  }
	    
	  //fill remaining with white, to have alignment
	  if (index_param<6)
	  fprintf(fp_results,"&\\multicolumn{%lu}{l|}{}",6-arglist_param.size());
	*/


  //SORT
  //version sorted
  
  //i) make the sort with increasing chi2/ndf (best chi2/ndf is lower chi2/ndf)
  
  //  cout << "phase 3" << endl;
  for (unsigned int i=0;i<nb_functional_forms;i++) {
    for (unsigned int j=i+1;j<nb_functional_forms;j++) {
      if (vec_functional_form_config[j].p_value_MC_like_stat>vec_functional_form_config[i].p_value_MC_like_stat
	  ||
	  (vec_functional_form_config[j].p_value_MC_like_stat==vec_functional_form_config[i].p_value_MC_like_stat
	   &&
	   vec_functional_form_config[j].chi2_over_ndf_MC_like_stat<vec_functional_form_config[i].chi2_over_ndf_MC_like_stat
	   )
	  ) {
	FunctionalFormConfiguration config_temp=vec_functional_form_config[i];
	vec_functional_form_config[i]=vec_functional_form_config[j];
	vec_functional_form_config[j]=config_temp;
      }
    }    
  }

  
  //  cout << "phase 4" << endl;

  cout << "call PrintHeader for sorted" << endl;
  //ii) print the results

  //    (b) sorted
  PrintHeaderResults(&fp_results_sorted,string_process,string_category,SORTED);

  cout << "called PrintHeader for sorted" << endl;

  //  cout << "phase 5" << endl;

  cout << "store results sorted" << endl;
  for (unsigned int index_functional_form=0;index_functional_form<nb_functional_forms;index_functional_form++) {

    for (unsigned int index_finalDV=0;index_finalDV<argset_finalDV_noWeight.size();index_finalDV++) {
      fprintf(fp_results_sorted,"%s         &%d",vec_functional_form_config[index_functional_form].vec_string_functional_form[index_finalDV].c_str(),vec_functional_form_config[index_functional_form].vec_n_params[index_finalDV]);
      
      fprintf(fp_results_sorted,"       &%6.2f",vec_functional_form_config[index_functional_form].vec_sigma68[index_finalDV]);
      
      if (index_finalDV+1<argset_finalDV_noWeight.size())
	fprintf(fp_results_sorted,"    &");
    }
    
    fprintf(fp_results_sorted,"        &%4.2f (%4.2f/%d)",
	    vec_functional_form_config[index_functional_form].chi2_over_ndf_MC_like_stat,
	    vec_functional_form_config[index_functional_form].chi2_MC_like_stat,
	    vec_functional_form_config[index_functional_form].ndf_MC_like_stat);
    
    fprintf(fp_results_sorted,"        &%6.3g",vec_functional_form_config[index_functional_form].p_value_MC_like_stat);

    fprintf(fp_results_sorted,"\\\\\n");
    
    fprintf(fp_results_sorted,"\\hline\n");
      
  } //end loop on functional forms

  cout << "stored results sorted" << endl;

  PrintTailResults(&fp_results_sorted,string_process,string_category);

  //TO DO : make a function ?

  if (do_export_workspace_HGam) {
    //index 0 is the best functional form

    RooRealVar *export_m_yy=new RooRealVar((string("m_yy_m125000_c")+to_string(index_category)).c_str(),
					   (string("m_yy_m125000_c")+to_string(index_category)).c_str(),
					   125,
					   roorealvar_m_yy->getRange("fitrange").first,roorealvar_m_yy->getRange("fitrange").second);

    RooRealVar *export_weight=new RooRealVar("wt","wt",1);

    workspace->import(*export_weight,RecycleConflictNodes());

    //create dataset with the same variable names, in order to respect conventions of HGam

    RooDataSet *export_dataset=new RooDataSet(
					      (string("data_m125000_c")+to_string(index_category)).c_str(),
					      (string("data_m125000_c")+to_string(index_category)).c_str(),
					      RooArgSet(*export_m_yy,*export_weight),RooFit::WeightVar(*export_weight));
    //fill it with the new names
    
    for (int index_event=0;index_event<dataset_current_category->numEntries();index_event++) {
      
      RooArgSet *argset_import=(RooArgSet *)dataset_current_category->get(index_event);
      
      double observable_value=argset_import->getRealValue("m_yy");
      double weight=dataset_current_category->weight();

      export_m_yy->setVal(observable_value);
      export_weight->setVal(weight);

      export_dataset->add(RooArgSet(*export_m_yy),weight);
    }
    
    workspace->import(*export_dataset);

    RooAbsPdf *currentPdf=vec_functional_form_config[0].vec_pdf_signal_model[0];

    RooRealVar *export_roorealvar_muCBNom=new RooRealVar((string("muCBNom_m125000_c")+to_string(index_category)).c_str(),
							 (string("muCBNom_m125000_c")+to_string(index_category)).c_str(),
							 ((RooRealVar *)currentPdf->getVariables()->find((string("muCB_")+"m_yy").c_str()))->getVal(),
							 ((RooRealVar *)currentPdf->getVariables()->find((string("muCB_")+"m_yy").c_str()))->getRange("fitrange").first,
							 ((RooRealVar *)currentPdf->getVariables()->find((string("muCB_")+"m_yy").c_str()))->getRange("fitrange").second);
    export_roorealvar_muCBNom->setError(((RooRealVar *)currentPdf->getVariables()->find((string("muCB_")+"m_yy").c_str()))->getError());
    export_roorealvar_muCBNom->setConstant(1);

    RooProduct *export_product_muCB=new RooProduct((string("muCB_m125000_c")+to_string(index_category)).c_str(),
						   (string("muCB_m125000_c")+to_string(index_category)).c_str(),
						   RooArgList(*export_roorealvar_muCBNom));
    
    RooRealVar *export_roorealvar_sigmaCBNom=new RooRealVar((string("sigmaCBNom_m125000_c")+to_string(index_category)).c_str(),
							    (string("sigmaCBNom_m125000_c")+to_string(index_category)).c_str(),
							    ((RooRealVar *)currentPdf->getVariables()->find((string("sigmaCB_")+"m_yy"+"_"+string_category).c_str()))->getVal(),
							    ((RooRealVar *)currentPdf->getVariables()->find((string("sigmaCB_")+"m_yy"+"_"+string_category).c_str()))->getRange("fitrange").first,
							    ((RooRealVar *)currentPdf->getVariables()->find((string("sigmaCB_")+"m_yy"+"_"+string_category).c_str()))->getRange("fitrange").second);
    export_roorealvar_sigmaCBNom->setError(((RooRealVar *)currentPdf->getVariables()->find((string("sigmaCB_")+"m_yy"+"_"+string_category).c_str()))->getError());
    export_roorealvar_sigmaCBNom->setConstant(1);
    
    RooProduct *export_product_sigmaCB=new RooProduct((string("sigmaCB_m125000_c")+to_string(index_category)).c_str(),
						      (string("sigmaCB_m125000_c")+to_string(index_category)).c_str(),
						      RooArgList(*export_roorealvar_sigmaCBNom));

    RooRealVar *export_roorealvar_alphaCBLo=new RooRealVar((string("alphaCBLo_m125000_c")+to_string(index_category)).c_str(),
							   (string("alphaCBLo_m125000_c")+to_string(index_category)).c_str(),
							   ((RooRealVar *)currentPdf->getVariables()->find((string("alphaCB_Low_")+"m_yy"+"_"+string_category).c_str()))->getVal(),
							   ((RooRealVar *)currentPdf->getVariables()->find((string("alphaCB_Low_")+"m_yy"+"_"+string_category).c_str()))->getRange("fitrange").first,
							   ((RooRealVar *)currentPdf->getVariables()->find((string("alphaCB_Low_")+"m_yy"+"_"+string_category).c_str()))->getRange("fitrange").second);
    export_roorealvar_alphaCBLo->setError(((RooRealVar *)currentPdf->getVariables()->find((string("alphaCB_Low_")+"m_yy"+"_"+string_category).c_str()))->getError());
    export_roorealvar_alphaCBLo->setConstant(1);

    RooRealVar *export_roorealvar_nCBLo=new RooRealVar((string("nCBLo_c")+to_string(index_category)).c_str(),
						       (string("nCBLo_c")+to_string(index_category)).c_str(),
						       ((RooRealVar *)currentPdf->getVariables()->find((string("nCB_Low_")+"m_yy"+"_"+string_category).c_str()))->getVal(),
						       ((RooRealVar *)currentPdf->getVariables()->find((string("nCB_Low_")+"m_yy"+"_"+string_category).c_str()))->getRange("fitrange").first,
						       ((RooRealVar *)currentPdf->getVariables()->find((string("nCB_Low_")+"m_yy"+"_"+string_category).c_str()))->getRange("fitrange").second);
    export_roorealvar_nCBLo->setError(((RooRealVar *)currentPdf->getVariables()->find((string("nCB_Low_")+"m_yy"+"_"+string_category).c_str()))->getError());
    export_roorealvar_nCBLo->setConstant(1);
    
    RooRealVar *export_roorealvar_alphaCBHi=new RooRealVar((string("alphaCBHi_m125000_c")+to_string(index_category)).c_str(),
							   (string("alphaCBHi_m125000_c")+to_string(index_category)).c_str(),
							   ((RooRealVar *)currentPdf->getVariables()->find((string("alphaCB_High_")+"m_yy"+"_"+string_category).c_str()))->getVal(),
							   ((RooRealVar *)currentPdf->getVariables()->find((string("alphaCB_High_")+"m_yy"+"_"+string_category).c_str()))->getRange("fitrange").first,
							   ((RooRealVar *)currentPdf->getVariables()->find((string("alphaCB_High_")+"m_yy"+"_"+string_category).c_str()))->getRange("fitrange").second);
    export_roorealvar_alphaCBHi->setError(((RooRealVar *)currentPdf->getVariables()->find((string("alphaCB_High_")+"m_yy"+"_"+string_category).c_str()))->getError());
    export_roorealvar_alphaCBHi->setConstant(1);

    RooRealVar *export_roorealvar_nCBHi=new RooRealVar((string("nCBHi_c")+to_string(index_category)).c_str(),
						       (string("nCBHi_c")+to_string(index_category)).c_str(),
						       ((RooRealVar *)currentPdf->getVariables()->find((string("nCB_High_")+"m_yy"+"_"+string_category).c_str()))->getVal(),
						       ((RooRealVar *)currentPdf->getVariables()->find((string("nCB_High_")+"m_yy"+"_"+string_category).c_str()))->getRange("fitrange").first,
						       ((RooRealVar *)currentPdf->getVariables()->find((string("nCB_High_")+"m_yy"+"_"+string_category).c_str()))->getRange("fitrange").second);
    export_roorealvar_nCBHi->setError(((RooRealVar *)currentPdf->getVariables()->find((string("nCB_High_")+"m_yy"+"_"+string_category).c_str()))->getError());
    export_roorealvar_nCBHi->setConstant(1);

    RooTwoSidedCBShape *export_pdf=new RooTwoSidedCBShape((string("sigPdf_m125000_c")+to_string(index_category)).c_str(),
							  (string("sigPdf_m125000_c")+to_string(index_category)).c_str(),*export_m_yy,*export_product_muCB,*export_product_sigmaCB,*export_roorealvar_alphaCBLo,*export_roorealvar_nCBLo,*export_roorealvar_alphaCBHi,*export_roorealvar_nCBHi);
    
    workspace->import(*export_pdf);
  }

  if (do_export_yaml_HGam) { //only implemented for case of one variable
    if (argset_finalDV_noWeight.size()>1) {
      cout << "not made for more than one variable, halt program" << endl;
      exit(1);
    }
    stream_yaml_SignalParametrization << string_category << ":" << endl;
    
    RooRealVar *roorealvar_finalDV=((RooRealVar *) RooArgList(argset_finalDV_noWeight).at(0));

    RooArgList *arglist_parameters=(RooArgList *) vec_functional_form_config[0].vec_pdf_signal_model[0]->getParameters(RooArgSet(*roorealvar_finalDV));
    
    for (unsigned int index_param=0;index_param<arglist_parameters->size();index_param++) {

      RooRealVar *roorealvar=(RooRealVar *)arglist_parameters->at(index_param);
      
      string string_translation;
      
      string string_roorealvar=roorealvar->GetName();
      if (string_roorealvar.find("muCB")!=string::npos)
	string_translation="muCBNom";
      else if (string_roorealvar.find("sigmaCB")!=string::npos)
	string_translation="sigmaCBNom";
      else if (string_roorealvar.find("alphaCB_Low")!=string::npos)
	string_translation="alphaCBLo";
      else if (string_roorealvar.find("nCB_Low")!=string::npos)
	string_translation="nCBLo";
      else if (string_roorealvar.find("alphaCB_High")!=string::npos)
	string_translation="alphaCBHi";
      else if (string_roorealvar.find("nCB_High")!=string::npos)
	string_translation="nCBHi";
      
      stream_yaml_SignalParametrization << "  " << string_translation << ": " << roorealvar->getVal() << endl;
      //      stream_yaml_SignalParametrization << endl;
    }
  }


  //----------

  //delete information in memory

  for (unsigned int index_functional_form=0;index_functional_form<nb_functional_forms;index_functional_form++) {
    
    //    cout << "index_functional_form=" << index_functional_form << endl;

    //    cout << "phase 10" << endl;

    for (unsigned int index_finalDV=0;index_finalDV<argset_finalDV_noWeight.size();index_finalDV++) {

      //      cout << "index_finalDV=" << index_finalDV << endl;
      //      cout << "pointeur subpdf=" << vec_functional_form_config[index_functional_form].vec_pdf_signal_model[index_finalDV] << endl;
      vec_functional_form_config[index_functional_form].vec_pdf_signal_model[index_finalDV]->Print();
 
      //---------------------
      //delete roorealvar of internal variables of pdf
      
      cout << "delete roorealvar internal" << endl;
      RooArgList *arglist_parameters;
      
      arglist_parameters=(RooArgList *) vec_functional_form_config[index_functional_form].vec_pdf_signal_model[index_finalDV]->getParameters(argset_finalDV_noWeight);
      
      arglist_parameters->Print("v");
      
      for (unsigned int index_parameter=0;index_parameter<arglist_parameters->size();index_parameter++) {
	delete arglist_parameters->at(index_parameter);
      } //end loop on parameters
      //---------------------
      
      delete vec_functional_form_config[index_functional_form].vec_pdf_signal_model[index_finalDV];
    }
    
    delete vec_functional_form_config[index_functional_form].pdf_total_current;
    
    //     functional_form_config.vec_pdf_signal_model.clear();
    //     functional_form_config.vec_string_functional_form.clear();
    //     functional_form_config.vec_sigma68.clear();
  }

  //remove everything
  vec_functional_form_config.clear();

  //  vec_functional_form_config.shrink_to_fit();

  //store the result of the best model  
  //---------------------------------------------
  //extract mX
  
  int mX=0;
  
  string string_delimiter="_X";
  
  //  cout << "string_process=" << string_process << endl;
  
  //  size_t pos=string_process.find(string_delimiter,0);
  //  cout << "pos=" << pos << endl;
  
  size_t pos=string_process.find(string_delimiter,0);
  
  if (pos==string::npos) {
    //mX=125;
    
    //    mX=counter_single_Higgs;
  }
  else {
    string string_mX=string_process.substr(pos+2,string_process.size()-(pos+2));
    
    cout << "string_mX=" << string_mX << endl;
    
    mX=atoi(string_mX.c_str());
  }
  
  cout << "mX=" << mX << endl;
  //---------------------------------------------
  if (string_non_resonant_resonant=="non_resonant")
    results_f_process.vec_m_hyp_resonance.push_back(counter_single_Higgs);
  else if (string_non_resonant_resonant=="resonant")
    results_f_process.vec_m_hyp_resonance.push_back(mX);



  results_f_process.vec_string_process.push_back(string_process);
  //  cout << "now, results_f_process.vec_string_process.size()=" << results_f_process.vec_string_process.size() << endl;
  
  //  cout << "before, results_f_process.vec_string_functional_form.size()=" << results_f_process.vec_string_functional_form.size() << endl;
  
  //  cout << "vec_string_functional_form_model_chosen.size()=" << vec_string_functional_form_model_chosen.size() << endl;
  results_f_process.vec_string_functional_form.push_back(vec_string_functional_form_model_chosen);
  //  cout << "after, results_f_process.vec_string_functional_form.size()=" << results_f_process.vec_string_functional_form.size() << endl;
  results_f_process.vec_n_params_functional_form.push_back(vec_n_params_functional_form_model_chosen);
  
  results_f_process.vec_arglist_parameters.push_back(vec_arglist_parameters_model_chosen);

  results_f_process.vec_mu_model_chosen.push_back(vec_mu_model_chosen);
  results_f_process.vec_err_mu_model_chosen.push_back(vec_err_mu_model_chosen);
  results_f_process.vec_sigma_model_chosen.push_back(vec_sigma_model_chosen);
  results_f_process.vec_err_sigma_model_chosen.push_back(vec_err_sigma_model_chosen);

  if (vec_functional_form_signal.size()==1 && vec_functional_form_signal[0]=="DoubleCrystalBall") {
    results_f_process.vec_alphaCB_Low.push_back(vec_alphaCB_Low);
    results_f_process.vec_err_alphaCB_Low.push_back(vec_err_alphaCB_Low);
    results_f_process.vec_nCB_Low.push_back(vec_nCB_Low);
    results_f_process.vec_err_nCB_Low.push_back(vec_err_nCB_Low);
    
    results_f_process.vec_alphaCB_High.push_back(vec_alphaCB_High);
    results_f_process.vec_err_alphaCB_High.push_back(vec_err_alphaCB_High);
    results_f_process.vec_nCB_High.push_back(vec_nCB_High);
    results_f_process.vec_err_nCB_High.push_back(vec_err_nCB_High);

    vec_alphaCB_Low.clear();
    vec_err_alphaCB_Low.clear();
    vec_nCB_Low.clear();
    vec_err_nCB_Low.clear();
    
    vec_alphaCB_High.clear();
    vec_err_alphaCB_High.clear();
    vec_nCB_High.clear();
    vec_err_nCB_High.clear();
  }

  results_f_process.vec_sigma68.push_back(vec_sigma68_model_chosen);
  //  results_f_process.vec_sigma90.push_back(vec_sigma90_model_chosen);
  
  vec_string_functional_form_model_chosen.clear();
  vec_n_params_functional_form_model_chosen.clear();
  vec_arglist_parameters_model_chosen.clear();
 
  vec_mu_model_chosen.clear();
  vec_err_mu_model_chosen.clear();
  vec_sigma_model_chosen.clear();
  vec_err_sigma_model_chosen.clear();
  vec_sigma68_model_chosen.clear();
  vec_sigma90_model_chosen.clear();

  cout << "delete dataset_current_category" << endl;

  if (do_binned)
    delete datahist_current_category;
  else
    delete dataset_current_category;
  
  cout << "delete chain_process" << endl;
  
  delete chain_process;
  
  cout << "deleted chain_process" << endl;
  //other chains have already been deleted after GetYield  

  return 0;
}
//===========================================================================================================
//pair<double,double> GetYield_given_process(TChain *chain,string string_category)
pair<double,double> GetYield_given_process(string string_process,TChain *chain,string string_category)
{
  double yield=0;
  double err_yield=0;
  
  //trick : uses m_yy, which is defined in range 105, 160, so lack of events
  //take always m_yy here
  //replace by double  TH1F *hist_dummy=new TH1F("hist_dummy","hist_dummy",55,105,160);

  //much better precision with TH1D
  TH1D *hist_dummy=new TH1D("hist_dummy","hist_dummy",55,105,160);
  
  //  cout << "chain=" << chain << endl;
  //  chain->Print();

  if (string_process=="gg_HH") {
    //HH is already at 125.09 GeV in the framework
    
    if (do_consider_public_test)
      chain->Project("hist_dummy","m_yy","weight_total*4*(eventNumber%4==2)");
    else if (do_consider_private_test)
      chain->Project("hist_dummy","m_yy","weight_total*4*(eventNumber%4==3)");
    else if (do_consider_public_train)
      chain->Project("hist_dummy","m_yy","weight_total*2*(eventNumber%4==0 || eventNumber%4==1)");
    else
      chain->Project("hist_dummy","m_yy","weight_total");
  }
  //for case of Py8
  //  else if (string_process.find("vbf_HH")!=string::npos) {

  else if (string_process=="vbf_HH"
	   ||
	   string_process=="vbf_HH_kappa_lambda_0"
	   ||
	   string_process=="vbf_HH_kappa_lambda_2"
	   ||
	   string_process=="vbf_HH_kappa_lambda_10"
	   ) {
    //correct to 125.09 GeV
    
    //1.726=sigma for mH=125 GeV
    //1.723=sigma for mH=125.09 GeV
    
    //correct the original cross-section of 125 to 125.09 GeV

    if (do_consider_public_test)
      chain->Project("hist_dummy","m_yy","weight_total*(1.723/1.726)*4*(eventNumber%4==2)");
    else if (do_consider_private_test)
      chain->Project("hist_dummy","m_yy","weight_total*(1.723/1.726)4*(eventNumber%4==3)");
    else if (do_consider_public_train)
      chain->Project("hist_dummy","m_yy","weight_total*2*(1.723/1.726)*(eventNumber%4==0 || eventNumber%4==1)");
    else
      chain->Project("hist_dummy","m_yy","(1.723/1.726)*weight_total");
  }

  else {
    if (do_consider_public_test)
      chain->Project("hist_dummy","m_yy","weight_total*4*(eventNumber%4==2)");
    else if (do_consider_private_test)
      chain->Project("hist_dummy","m_yy","weight_total*4*(eventNumber%4==3)");
    else if (do_consider_public_train)
      chain->Project("hist_dummy","m_yy","weight_total*2*(eventNumber%4==0 || eventNumber%4==1)");
    else
      chain->Project("hist_dummy","m_yy","weight_total");
  }
  
  cout << "entries=" << hist_dummy->GetEntries() << endl;

  yield=hist_dummy->Integral();
  
  TArrayD *array_sumw2=hist_dummy->GetSumw2();
  int nb_array_sumw2=hist_dummy->GetSumw2N(); //it contains underflow/overflow, which are empty anyway
  
  //  cout << "nb_array_sumw2=" << nb_array_sumw2 << endl;
  
  double sumw2=0;
  
  for (int index_array_sumw2=0;index_array_sumw2<nb_array_sumw2;index_array_sumw2++) {
    sumw2+=array_sumw2->GetAt(index_array_sumw2);
  }

  err_yield=sqrt(sumw2);

  cout << "yield=" << yield << " +/- " << err_yield << endl;
  
  delete hist_dummy;

  pair<double,double> pair_yield;
  pair_yield.first=yield;
  pair_yield.second=err_yield;

  return pair_yield;
}

//need to provide the finalDV: not necessary at same position
//===========================================================================================================
//to see : for 
//https://root-forum.cern.ch/t/unbinned-fit-data-with-some-blinded-range/21097/2

//not useful at all !!
//gamma.setRange(gamma.getVal() - 2*gamma.getPropagatedError(*r_sb12),
//gamma.getVal() + 2*gamma.getPropagatedError(*r_sb12));

//TO DO : make as a member of the class !
//===========================================================================================================
bool IsFinalDV_in_list(string string_finalDV)
{
  for (unsigned int i=0;i<vec_string_finalDV.size();i++) {
    if (vec_string_finalDV[i]==string_finalDV)
      return 1;
  }
  return 0;
}
//===================================================================================================
void SetExtensionFinalDV(string string_process,string string_category)
{
  if (IsFinalDV_in_list("m_yy")) {

    //shitroorealvar_m_yy=new RooRealVar("m_yy","m_{#gamma#gamma}",125,118,132,"GeV");
    
    roorealvar_m_yy=new RooRealVar("m_yy","m_{#gamma#gamma}",125,114,136,"GeV");
    //roorealvar_m_yy=new RooRealVar("m_yy","m_{#gamma#gamma}",125,113.5,136.5,"GeV");
    
    //roorealvar_m_yy=new RooRealVar("m_yy","m_{#gamma#gamma}",125,110,140,"GeV");
    //    roorealvar_m_yy=new RooRealVar("m_yy","m_{#gamma#gamma}",125,112.9,137.9,"GeV");
    
    //roorealvar_m_yy->setBins((roorealvar_m_yy->getMax()-roorealvar_m_yy->getMin())/1.); //m_yy: bin width=1 GeV
    roorealvar_m_yy->setBins((roorealvar_m_yy->getMax()-roorealvar_m_yy->getMin())/0.5); //m_yy: bin width=0.5 GeV : this reduces the possible Karsten effect of barycenter
    cout << "roorealvar_m_yy->numBins()=" << roorealvar_m_yy->numBins() << endl;
    roorealvar_m_yy->Print();
  }

  if (IsFinalDV_in_list("m_bb") || do_cut_anyway) {
    roorealvar_m_bb=new RooRealVar("m_bb","m_{bb}",125,"GeV"); //remark : range need at least 500 for ttH, with fraction 0.95
    
    if (string_process=="ggH") {
      roorealvar_m_bb->setMax(350); //minimal for fraction=0.95 
      roorealvar_m_bb->setMin(0); //sure
      //roorealvar_m_bb->setBins((roorealvar_m_bb->getMax()-roorealvar_m_bb->getMin())/5); //m_bb: bin width=10 GeV
      roorealvar_m_bb->setBins((roorealvar_m_bb->getMax()-roorealvar_m_bb->getMin())/10); //m_bb: bin width=10 GeV, sure
    }
    else if (string_process=="VBF") {
      roorealvar_m_bb->setMax(350); //minimal for fraction=0.95 
      roorealvar_m_bb->setMin(0); //sure
      //roorealvar_m_bb->setBins((roorealvar_m_bb->getMax()-roorealvar_m_bb->getMin())/5); //m_bb: bin width=10 GeV
      roorealvar_m_bb->setBins((roorealvar_m_bb->getMax()-roorealvar_m_bb->getMin())/10); //m_bb: bin width=10 GeV, sure
    }
    else if (string_process=="ZH") {
      //      roorealvar_m_bb->setMax(180);
      //      roorealvar_m_bb->setMax(190);
      roorealvar_m_bb->setMax(220); //sure
      roorealvar_m_bb->setMin(10); //sure
      roorealvar_m_bb->setBins((roorealvar_m_bb->getMax()-roorealvar_m_bb->getMin())/5); //m_bb: bin width=10 GeV
    }
    else if (string_process=="ttH") {
      //      roorealvar_m_bb->setMax(360);
      roorealvar_m_bb->setMax(450); //minimum, else can't obtain fraction=0.95
      //      roorealvar_m_bb->setMin(20);
      roorealvar_m_bb->setMin(0); //sure
      //      roorealvar_m_bb->setBins((roorealvar_m_bb->getMax()-roorealvar_m_bb->getMin())/5); //m_bb: bin width=10 GeV
      roorealvar_m_bb->setBins((roorealvar_m_bb->getMax()-roorealvar_m_bb->getMin())/10); //m_bb: bin width=10 GeV, sure
    }
    else if (string_process=="tHjb") {
      //      roorealvar_m_bb->setMax(360);
      roorealvar_m_bb->setMax(450); //minimum, else can't obtain fraction=0.95
      //      roorealvar_m_bb->setMin(20);
      roorealvar_m_bb->setMin(0); //sure
      //      roorealvar_m_bb->setBins((roorealvar_m_bb->getMax()-roorealvar_m_bb->getMin())/5); //m_bb: bin width=10 GeV
      roorealvar_m_bb->setBins((roorealvar_m_bb->getMax()-roorealvar_m_bb->getMin())/10); //m_bb: bin width=10 GeV, sure
    }
    else if (string_process=="SingleHiggs") {
      roorealvar_m_bb->setMax(360);
      roorealvar_m_bb->setMin(20);
      roorealvar_m_bb->setBins((roorealvar_m_bb->getMax()-roorealvar_m_bb->getMin())/5); //m_bb: bin width=10 GeV
    }
    //else if (string_process=="gg_HH" || string_process=="gg_HH_Full_mc16d") {
    
    else if (string_process.find("gg_HH")!=string::npos) {
      roorealvar_m_bb->setMax(220); //sure
      roorealvar_m_bb->setMin(20);
      roorealvar_m_bb->setBins((roorealvar_m_bb->getMax()-roorealvar_m_bb->getMin())/5); //m_bb: bin width=10 GeV
    }
    else if (string_process=="gg_X251") {
      roorealvar_m_bb->setMax(220);
      roorealvar_m_bb->setMin(0);
      roorealvar_m_bb->setBins((roorealvar_m_bb->getMax()-roorealvar_m_bb->getMin())/5); //m_bb: bin width=10 GeV
    }
    else if (string_process=="gg_X260") {
      roorealvar_m_bb->setMax(220);
      roorealvar_m_bb->setMin(0);
      roorealvar_m_bb->setBins((roorealvar_m_bb->getMax()-roorealvar_m_bb->getMin())/5); //m_bb: bin width=10 GeV
    }
    else if (string_process=="gg_X280" || string_process=="gg_X280_Py8") {
      roorealvar_m_bb->setMax(220);
      roorealvar_m_bb->setMin(0);
      roorealvar_m_bb->setBins((roorealvar_m_bb->getMax()-roorealvar_m_bb->getMin())/5); //m_bb: bin width=10 GeV
    }
    else if (string_process=="gg_X300") {
      roorealvar_m_bb->setMax(220);
      roorealvar_m_bb->setMin(0);
      roorealvar_m_bb->setBins((roorealvar_m_bb->getMax()-roorealvar_m_bb->getMin())/5); //m_bb: bin width=10 GeV
    }
    else if (string_process=="gg_X325") {
      roorealvar_m_bb->setMax(220);
      roorealvar_m_bb->setMin(0);
      roorealvar_m_bb->setBins((roorealvar_m_bb->getMax()-roorealvar_m_bb->getMin())/5); //m_bb: bin width=10 GeV
    }
    else if (string_process=="gg_X350") {
      roorealvar_m_bb->setMax(220);
      roorealvar_m_bb->setMin(0);
      roorealvar_m_bb->setBins((roorealvar_m_bb->getMax()-roorealvar_m_bb->getMin())/5); //m_bb: bin width=10 GeV
    }
    else if (string_process=="gg_X400") {
      roorealvar_m_bb->setMax(220);
      roorealvar_m_bb->setMin(0);
      roorealvar_m_bb->setBins((roorealvar_m_bb->getMax()-roorealvar_m_bb->getMin())/5); //m_bb: bin width=10 GeV
    }
    else if (string_process=="gg_X450") {
      roorealvar_m_bb->setMax(220);
      roorealvar_m_bb->setMin(0);
      roorealvar_m_bb->setBins((roorealvar_m_bb->getMax()-roorealvar_m_bb->getMin())/5); //m_bb: bin width=10 GeV
    }
    else if (string_process=="gg_X500" || string_process=="gg_X500_Py8") {
      //      roorealvar_m_bb->setMax(220);
      roorealvar_m_bb->setMax(240); //sure
      roorealvar_m_bb->setMin(0);
      roorealvar_m_bb->setBins((roorealvar_m_bb->getMax()-roorealvar_m_bb->getMin())/5); //m_bb: bin width=10 GeV
    }
    else if (string_process=="gg_X550") {
      roorealvar_m_bb->setMax(220);
      roorealvar_m_bb->setMin(0);
      roorealvar_m_bb->setBins((roorealvar_m_bb->getMax()-roorealvar_m_bb->getMin())/5); //m_bb: bin width=10 GeV
    }
    else if (string_process=="gg_X600") {
      roorealvar_m_bb->setMax(220);
      roorealvar_m_bb->setMin(0);
      roorealvar_m_bb->setBins((roorealvar_m_bb->getMax()-roorealvar_m_bb->getMin())/5); //m_bb: bin width=10 GeV
    }
    else if (string_process=="gg_X700") {
      roorealvar_m_bb->setMax(220);
      roorealvar_m_bb->setMin(0);
      roorealvar_m_bb->setBins((roorealvar_m_bb->getMax()-roorealvar_m_bb->getMin())/5); //m_bb: bin width=10 GeV
    }
    else if (string_process=="gg_X800") {
      roorealvar_m_bb->setMax(250);
      roorealvar_m_bb->setMin(0);
      roorealvar_m_bb->setBins((roorealvar_m_bb->getMax()-roorealvar_m_bb->getMin())/5); //m_bb: bin width=10 GeV
    }
    else if (string_process=="gg_X900") {
      roorealvar_m_bb->setMax(250);
      roorealvar_m_bb->setMin(0);
      roorealvar_m_bb->setBins((roorealvar_m_bb->getMax()-roorealvar_m_bb->getMin())/5); //m_bb: bin width=10 GeV
    }
    else if (string_process=="gg_X1000" || string_process=="gg_X1000_Py8") {
      //      roorealvar_m_bb->setMax(270);
      roorealvar_m_bb->setMax(300); //sure
      roorealvar_m_bb->setMin(0);
      roorealvar_m_bb->setBins((roorealvar_m_bb->getMax()-roorealvar_m_bb->getMin())/5); //m_bb: bin width=10 GeV
    }
    else if (string_process=="gg_X2000") {
      // roorealvar_m_bb->setMax(300);
      roorealvar_m_bb->setMax(250);
      roorealvar_m_bb->setMin(0);
      roorealvar_m_bb->setBins((roorealvar_m_bb->getMax()-roorealvar_m_bb->getMin())/5); //m_bb: bin width=10 GeV
    }
    else if (string_process=="gg_X3000") {
      //      roorealvar_m_bb->setMax(300);
      roorealvar_m_bb->setMax(250);
      roorealvar_m_bb->setMin(0);
      roorealvar_m_bb->setBins((roorealvar_m_bb->getMax()-roorealvar_m_bb->getMin())/5); //m_bb: bin width=10 GeV
    }
  }

  if (IsFinalDV_in_list("m_yybb_tilde")) {
    roorealvar_m_yybb_tilde=new RooRealVar("m_yybb_tilde","m_{#gamma#gammabb tilde}",125,"GeV");
    
    //low region
    //roorealvar_m_yybb_tilde->setMax(621); //do not change this order, else it will create a bug
    //roorealvar_m_yybb_tilde->setMin(251);
    
    //high region
    //roorealvar_m_yybb_tilde->setMax(1150); //do not change this order, else it will create a bug
    //roorealvar_m_yybb_tilde->setMin(350);
    
    if (string_process=="ggH") {
      roorealvar_m_yybb_tilde->setMax(800);
      roorealvar_m_yybb_tilde->setMin(250);
      roorealvar_m_yybb_tilde->setBins((roorealvar_m_yybb_tilde->getMax()-roorealvar_m_yybb_tilde->getMin())/10); //m_yy: bin width=1 GeV
    }
    else if (string_process=="VBF") {
      roorealvar_m_yybb_tilde->setMax(800);
      roorealvar_m_yybb_tilde->setMin(250);
      roorealvar_m_yybb_tilde->setBins((roorealvar_m_yybb_tilde->getMax()-roorealvar_m_yybb_tilde->getMin())/10); //m_yy: bin width=1 GeV
    }
    else if (string_process=="ZH") {
      roorealvar_m_yybb_tilde->setMax(800);
      roorealvar_m_yybb_tilde->setMin(250);
      roorealvar_m_yybb_tilde->setBins((roorealvar_m_yybb_tilde->getMax()-roorealvar_m_yybb_tilde->getMin())/10); //m_yy: bin width=1 GeV
    }
    else if (string_process=="ttH") {
      roorealvar_m_yybb_tilde->setMax(800);
      roorealvar_m_yybb_tilde->setMin(250);
      roorealvar_m_yybb_tilde->setBins((roorealvar_m_yybb_tilde->getMax()-roorealvar_m_yybb_tilde->getMin())/10); //m_yy: bin width=1 GeV
    }
    else if (string_process=="tHjb") {
      roorealvar_m_yybb_tilde->setMax(800);
      roorealvar_m_yybb_tilde->setMin(250);
      roorealvar_m_yybb_tilde->setBins((roorealvar_m_yybb_tilde->getMax()-roorealvar_m_yybb_tilde->getMin())/10); //m_yy: bin width=1 GeV
    }
    else if (string_process=="SingleHiggs") {
      roorealvar_m_yybb_tilde->setMax(800);
      roorealvar_m_yybb_tilde->setMin(250);
      roorealvar_m_yybb_tilde->setBins((roorealvar_m_yybb_tilde->getMax()-roorealvar_m_yybb_tilde->getMin())/10); //m_yy: bin width=1 GeV
    }
    else if (string_process=="gg_HH" || string_process=="gg_HH_Full_mc16d") {
      roorealvar_m_yybb_tilde->setMax(800);
      roorealvar_m_yybb_tilde->setMin(250);
      roorealvar_m_yybb_tilde->setBins((roorealvar_m_yybb_tilde->getMax()-roorealvar_m_yybb_tilde->getMin())/10); //m_yy: bin width=5 GeV
    }
    //---------------------------------
    //resonant
    
    else if (string_process=="gg_X251") {
      roorealvar_m_yybb_tilde->setMax(270); //sure
      roorealvar_m_yybb_tilde->setMin(250);
      roorealvar_m_yybb_tilde->setBins((roorealvar_m_yybb_tilde->getMax()-roorealvar_m_yybb_tilde->getMin())/0.2); //m_yy: bin width=1 GeV
    }
    else if (string_process=="gg_X260") {
      roorealvar_m_yybb_tilde->setMax(280);
      roorealvar_m_yybb_tilde->setMin(250);
      roorealvar_m_yybb_tilde->setBins((roorealvar_m_yybb_tilde->getMax()-roorealvar_m_yybb_tilde->getMin())/0.5); //m_yy: bin width=1 GeV
    }
    else if (string_process=="gg_X280" || string_process=="gg_X280_Py8") {
      roorealvar_m_yybb_tilde->setMax(305);
      roorealvar_m_yybb_tilde->setMin(250);
      roorealvar_m_yybb_tilde->setBins((roorealvar_m_yybb_tilde->getMax()-roorealvar_m_yybb_tilde->getMin())/0.5); //m_yy: bin width=1 GeV
    }
    else if (string_process=="gg_X300") {
      roorealvar_m_yybb_tilde->setMax(340); //sure
      roorealvar_m_yybb_tilde->setMin(260);
      roorealvar_m_yybb_tilde->setBins((roorealvar_m_yybb_tilde->getMax()-roorealvar_m_yybb_tilde->getMin())/0.5); //m_yy: bin width=1 GeV
    }
    else if (string_process=="gg_X325") {
      roorealvar_m_yybb_tilde->setMax(350);
      roorealvar_m_yybb_tilde->setMin(280);
      roorealvar_m_yybb_tilde->setBins((roorealvar_m_yybb_tilde->getMax()-roorealvar_m_yybb_tilde->getMin())/1); //m_yy: bin width=1 GeV
    }
    else if (string_process=="gg_X350") {
      roorealvar_m_yybb_tilde->setMax(380);
      roorealvar_m_yybb_tilde->setMin(300);
      roorealvar_m_yybb_tilde->setBins((roorealvar_m_yybb_tilde->getMax()-roorealvar_m_yybb_tilde->getMin())/1); //m_yy: bin width=1 GeV
    }
    else if (string_process=="gg_X400") {
      roorealvar_m_yybb_tilde->setMax(430);
      roorealvar_m_yybb_tilde->setMin(330);
      roorealvar_m_yybb_tilde->setBins((roorealvar_m_yybb_tilde->getMax()-roorealvar_m_yybb_tilde->getMin())/1); //m_yy: bin width=1 GeV
    }
    else if (string_process=="gg_X450") {
      roorealvar_m_yybb_tilde->setMax(500);
      roorealvar_m_yybb_tilde->setMin(350);
      roorealvar_m_yybb_tilde->setBins((roorealvar_m_yybb_tilde->getMax()-roorealvar_m_yybb_tilde->getMin())/1); //m_yy: bin width=1 GeV
    }
    else if (string_process=="gg_X500" || string_process=="gg_X500_Py8") {
      //roorealvar_m_yybb_tilde->setMax(560);
      roorealvar_m_yybb_tilde->setMax(550);
      //      roorealvar_m_yybb_tilde->setMin(410);
      //roorealvar_m_yybb_tilde->setMin(390);
      roorealvar_m_yybb_tilde->setMin(370);
      roorealvar_m_yybb_tilde->setBins((roorealvar_m_yybb_tilde->getMax()-roorealvar_m_yybb_tilde->getMin())/4); //m_yy: bin width=2 GeV
    }
    else if (string_process=="gg_X550") {
      roorealvar_m_yybb_tilde->setMax(620);
      roorealvar_m_yybb_tilde->setMin(450);
      roorealvar_m_yybb_tilde->setBins((roorealvar_m_yybb_tilde->getMax()-roorealvar_m_yybb_tilde->getMin())/4); //m_yy: bin width=2 GeV
    }
    else if (string_process=="gg_X600") {
      roorealvar_m_yybb_tilde->setMax(670);
      roorealvar_m_yybb_tilde->setMin(450);
      roorealvar_m_yybb_tilde->setBins((roorealvar_m_yybb_tilde->getMax()-roorealvar_m_yybb_tilde->getMin())/4); //m_yy: bin width=2 GeV
    }
    else if (string_process=="gg_X700") {
      roorealvar_m_yybb_tilde->setMax(800);
      roorealvar_m_yybb_tilde->setMin(550);
      roorealvar_m_yybb_tilde->setBins((roorealvar_m_yybb_tilde->getMax()-roorealvar_m_yybb_tilde->getMin())/4); //m_yy: bin width=2 GeV
    }
    else if (string_process=="gg_X800") {
      roorealvar_m_yybb_tilde->setMax(900);
      roorealvar_m_yybb_tilde->setMin(600);
      roorealvar_m_yybb_tilde->setBins((roorealvar_m_yybb_tilde->getMax()-roorealvar_m_yybb_tilde->getMin())/4); //m_yy: bin width=2 GeV
    }
    else if (string_process=="gg_X900") {
      roorealvar_m_yybb_tilde->setMax(1000);
      roorealvar_m_yybb_tilde->setMin(700);
      roorealvar_m_yybb_tilde->setBins((roorealvar_m_yybb_tilde->getMax()-roorealvar_m_yybb_tilde->getMin())/4); //m_yy: bin width=2 GeV
    }
    else if (string_process=="gg_X1000" || string_process=="gg_X1000_Py8") {
      roorealvar_m_yybb_tilde->setMax(1100);
      roorealvar_m_yybb_tilde->setMin(650);
      roorealvar_m_yybb_tilde->setBins((roorealvar_m_yybb_tilde->getMax()-roorealvar_m_yybb_tilde->getMin())/10); //m_yy: bin width=2 GeV
    }
    else if (string_process=="gg_X2000") {
      roorealvar_m_yybb_tilde->setMax(2300);
      roorealvar_m_yybb_tilde->setMin(1200);
      roorealvar_m_yybb_tilde->setBins((roorealvar_m_yybb_tilde->getMax()-roorealvar_m_yybb_tilde->getMin())/20); //m_yy: bin width=2 GeV
    }
    else if (string_process=="gg_X3000") {
      roorealvar_m_yybb_tilde->setMax(3300);
      roorealvar_m_yybb_tilde->setMin(1000);
      roorealvar_m_yybb_tilde->setBins((roorealvar_m_yybb_tilde->getMax()-roorealvar_m_yybb_tilde->getMin())/20); //m_yy: bin width=2 GeV
    }
    else {
      cout << "case of string_process not anticipated, halt program" << endl;
      exit(1);
    }
    //blinding region is defined after the ReturnWindow
  }
}
//===================================================================================================
void FillListCategories()
{
  if (string_non_resonant_resonant=="non_resonant") {
    vec_string_category.push_back("XGBoost_btag77_withTop_BCal_tightScore_HMass");
    vec_string_category.push_back("XGBoost_btag77_withTop_BCal_looseScore_HMass");
    vec_string_category.push_back("XGBoost_btag77_withTop_BCal_tightScore_LMass");
    vec_string_category.push_back("XGBoost_btag77_withTop_BCal_looseScore_LMass");

    //only for h025    vec_string_category.push_back("VBF_btag77_withTop_BCal");
  }
  else { //case resonant
    
    vec_string_category.push_back("Resonant"); // for samples HH resonant
    
    /*
    //for single Higgs and HH non resonant in various resonant 'categories'
    
    for (unsigned int index_mX=0;index_mX<vec_mX.size();index_mX++) {
      string string_resonance="X"+to_string(vec_mX[index_mX]);
      cout << "string_resonance=" << string_resonance << endl;
      
      string string_category;
      
      if (vec_mX[index_mX]==312.5)
	string_category="Resonant_mX312.5";
      else if (vec_mX[index_mX]==337.5)
	string_category="Resonant_mX337.5";
      else
	string_category="Resonant_mX"+to_string((int)(vec_mX[index_mX]));
      
      vec_string_category.push_back(string_category);
    }
    */

    //    vec_string_category.push_back("Resonant_mX500");

    //vec_string_category.push_back("Resonant_mX280");
    /*
    vec_string_category.push_back("Resonant_mX260");
    vec_string_category.push_back("Resonant_mX325");
    vec_string_category.push_back("Resonant_mX900");
    */

    //    vec_string_category.push_back("Resonant_mX450");

    //vec_string_category.push_back("Resonant_mX550");

    //    vec_string_category.push_back("Resonant_mX251");

  } //end resonant
}
//===================================================================================================
void FillListProcessNonResonant()
{
  //----------------
  /*
  //study Full simulation vs AF2
    
  do_mc16a=0;
  do_mc16d=1;
  do_mc16e=0;
    
  vec_string_process.push_back("gg_HH");      
  vec_string_process.push_back("gg_HH_Full_mc16d");
  */

  //----------------
  /*
  //to use private test for yield of that
  vec_string_process.push_back("SingleHiggs"); //don't put it for m_bb

  vec_string_process.push_back("ggH");
  vec_string_process.push_back("VBF");
  vec_string_process.push_back("WH");
  vec_string_process.push_back("ZH");
  vec_string_process.push_back("ttH");
  
  vec_string_process.push_back("bbH");
  
  vec_string_process.push_back("tWH");
  vec_string_process.push_back("tHjb");
  */  
  //---------------
  //  vec_string_process.push_back("gg_HH_NLO_reweight_mHH_1p0_to_n10p0");
  /*
  vec_string_process.push_back("gg_HH_NLO_reweight_mHH_1p0_to_n5p0");
  vec_string_process.push_back("gg_HH_NLO_reweight_mHH_1p0_to_0p0");
  */

  vec_string_process.push_back("gg_vbf_HH"); //this one

  //shit  vec_string_process.push_back("gg_HH_NLO");

  //vec_string_process.push_back("gg_HH");

  //  vec_string_process.push_back("gg_HH_NLO_plus_SingleHiggs");
  
  /* shit
  //-----
  vec_string_process.push_back("gg_HH_NLO_reweight_mHH_1p0_to_n10p0");
  vec_string_process.push_back("gg_HH_NLO_reweight_mHH_1p0_to_n5p0");
  vec_string_process.push_back("gg_HH_NLO_reweight_mHH_1p0_to_n2p0");
  vec_string_process.push_back("gg_HH_NLO_reweight_mHH_1p0_to_n1p0");
  
  vec_string_process.push_back("gg_HH_NLO_reweight_mHH_1p0_to_0p0");
  
  //shit  vec_string_process.push_back("gg_HH_NLO");
  vec_string_process.push_back("gg_HH");
  
  vec_string_process.push_back("gg_HH_NLO_reweight_mHH_1p0_to_1p4");

  vec_string_process.push_back("gg_HH_NLO_reweight_mHH_1p0_to_2p0");
  vec_string_process.push_back("gg_HH_NLO_reweight_mHH_1p0_to_3p0");
  vec_string_process.push_back("gg_HH_NLO_reweight_mHH_1p0_to_4p0");
  vec_string_process.push_back("gg_HH_NLO_reweight_mHH_1p0_to_5p0");
  vec_string_process.push_back("gg_HH_NLO_reweight_mHH_1p0_to_10p0");
  */

  //shit vec_string_process.push_back("gg_HH_NLO");
  //vec_string_process.push_back("gg_HH");

  //vec_string_process.push_back("PowhegPy8_HHbbyy_cHHH01d0");

  //  PowhegPy8_HHbbyy_cHHH01d0_train_events
  //vec_string_process=CreateList_HH_non_resonant_kappa_lambda();

  //---------------
  /*  
  vec_string_process.push_back("vbf_HH"); //vbf only

  vec_string_process.push_back("vbf_HH_kappa_lambda_0");
  vec_string_process.push_back("vbf_HH_kappa_lambda_2");
  vec_string_process.push_back("vbf_HH_kappa_lambda_10");
  */
  //  vec_string_process.push_back("gg_vbf_HH"); //avoid because mH different in the two samples
    
  //vec_string_process.push_back("gg_HH_NLO_kappa_lambda_10");
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
    
    if (fabs(kappa_lambda-1.)<epsilon) {
      //shit      vector_string_kappa_lambda.push_back("gg_HH_NLO");
      vector_string_kappa_lambda.push_back("gg_HH");
      cout << "added gg HH NLO" << endl;
    }
    else if (fabs(kappa_lambda-1.)>epsilon) {
      cout << "add the string" << endl;
      vector_string_kappa_lambda.push_back(Return_string_target_kappa(kappa_lambda));
    }
  } //end loop on kappa lambda

  //post fix : put the prefix  
  for (unsigned index_kappa_lambda=0;index_kappa_lambda<vector_string_kappa_lambda.size();index_kappa_lambda++) {
    if (vector_string_kappa_lambda[index_kappa_lambda]!="gg_HH") //for gg HH NLO, don't do any change
      vector_string_kappa_lambda[index_kappa_lambda]="gg_HH_NLO_reweight_mHH_1p0_to_"+vector_string_kappa_lambda[index_kappa_lambda];
  }
  
  return vector_string_kappa_lambda;
}
//###################################################################################################
void FillListProcessResonant()
{
  //----------------
  //effect of pile-up
  //do it by one by hand (else it writes on top of each other)hand
  /*      
	  do_mc16a=1;
	  do_mc16d=0;
	  do_mc16e=0;
	  
	  vec_string_process.push_back("gg_X500");
  */
  
  /*
    do_mc16a=0;
    do_mc16d=1;
    do_mc16e=0;
    
    vec_string_process.push_back("gg_X500");
  */
  
  /*
    do_mc16a=0;
    do_mc16d=0;
    do_mc16e=1;
    
    vec_string_process.push_back("gg_X500");
  */
  
  //----------------

  //----------------
  //effect of parton showering
  /*  
  vec_string_process.push_back("gg_X280");
  vec_string_process.push_back("gg_X280_Py8");
  
  vec_string_process.push_back("gg_X500");
  vec_string_process.push_back("gg_X500_Py8");
  
  vec_string_process.push_back("gg_X1000");
  vec_string_process.push_back("gg_X1000_Py8");
  */
  //----------------
      
  //  vec_string_process.push_back("ggH");
  //  vec_string_process.push_back("ttH");

  /*
  vec_string_process.push_back("SingleHiggs");
  
  vec_string_process.push_back("ggH");
  vec_string_process.push_back("VBF");
  vec_string_process.push_back("WH");
  vec_string_process.push_back("ZH");
  vec_string_process.push_back("ttH");
  
  vec_string_process.push_back("bbH");
  
  vec_string_process.push_back("tHjb");
  vec_string_process.push_back("tWH");
  */
  
  
  //  vec_string_process.push_back("gg_vbf_HH"); //this one
  
  //separate information for information
  //  vec_string_process.push_back("gg_HH");
  
  //  vec_string_process.push_back("vbf_HH");

  //  vec_string_process.push_back("gg_X300");

  //----------
  vec_string_process.push_back("gg_X251");
  vec_string_process.push_back("gg_X260");
  vec_string_process.push_back("gg_X270");
  vec_string_process.push_back("gg_X280");

  vec_string_process.push_back("gg_X290");
  
  vec_string_process.push_back("gg_X300");

  vec_string_process.push_back("gg_X312.5");
  
  vec_string_process.push_back("gg_X325");

  vec_string_process.push_back("gg_X337.5");
  
  vec_string_process.push_back("gg_X350");

  vec_string_process.push_back("gg_X375");
  
  vec_string_process.push_back("gg_X400");

  vec_string_process.push_back("gg_X425");

  vec_string_process.push_back("gg_X450");

  vec_string_process.push_back("gg_X475");
  
  vec_string_process.push_back("gg_X500");
  
  vec_string_process.push_back("gg_X550");
  
  vec_string_process.push_back("gg_X600");
  vec_string_process.push_back("gg_X700");
  vec_string_process.push_back("gg_X800");
  vec_string_process.push_back("gg_X900");
  vec_string_process.push_back("gg_X1000");
  
  //----------

  //     vec_string_process.push_back("gg_X2000");
  //       vec_string_process.push_back("gg_X3000");
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
void AddSumw2(RooAbsReal *nll,RooMinimizerExt *roominimize)
{
  //----------------------------------------------------
  //add Sumw2 (since does not exist in native
  
  cout << "add Sumw2 phase 1" << endl;
  
  //need
  //RooAbsReal* nll
  //RooMinimizer *roominimize
  
  cout << "add Sumw2 phase 2" << endl;
  
  // Make list of RooNLLVar components of FCN
  RooArgSet* comps = nll->getComponents();
  vector<RooNLLVar*> nllComponents;
  nllComponents.reserve(comps->getSize());
  TIterator* citer = comps->createIterator();
  RooAbsArg* arg;
  while ((arg=(RooAbsArg*)citer->Next())) {
    RooNLLVar* nllComp = dynamic_cast<RooNLLVar*>(arg);
    if (!nllComp) continue;
    nllComponents.push_back(nllComp);
  }
  delete citer;
  delete comps;
  
  cout << "add Sumw2 phase 3" << endl;
  // Calculated corrected errors for weighted likelihood fits
  RooFitResult* rw = roominimize->save();
  for (vector<RooNLLVar*>::iterator it = nllComponents.begin(); nllComponents.end() != it; ++it) {
    (*it)->applyWeightSquared(kTRUE);
  }
  //	coutI(Fitting) << "RooAbsPdf::fitTo(" << GetName() << ") Calculating sum-of-weights-squared correction matrix for covariance matrix" << endl ;
  roominimize->hesse();
  RooFitResult* rw2 = roominimize->save();
  for (vector<RooNLLVar*>::iterator it = nllComponents.begin(); nllComponents.end() != it; ++it) {
    (*it)->applyWeightSquared(kFALSE);
  }
  
  cout << "add Sumw2 phase 4" << endl;
  
  cout << "rw=" << rw << endl;
  // Apply correction matrix
  const TMatrixDSym& matV = rw->covarianceMatrix();
  
  cout << "add Sumw2 phase 5" << endl;
  
  TMatrixDSym matC = rw2->covarianceMatrix();
  using ROOT::Math::CholeskyDecompGenDim;
  CholeskyDecompGenDim<Double_t> decomp(matC.GetNrows(), matC);
  
  cout << "add Sumw2 phase 6" << endl;
  cout << "decomp=" << decomp << endl;
  
  if (!decomp) {
    //	  coutE(Fitting) << "RooAbsPdf::fitTo(" << GetName()
    cout << "RooAbsPdf::fitTo(" << ") ERROR: Cannot apply sum-of-weights correction to covariance matrix: correction matrix calculated with weight-squared is singular" <<endl ;
  } else {
    // replace C by its inverse
    decomp.Invert(matC);
    // the class lies about the matrix being symmetric, so fill in the
    // part above the diagonal
    for (int i = 0; i < matC.GetNrows(); ++i)
      for (int j = 0; j < i; ++j) matC(j, i) = matC(i, j);
    matC.Similarity(matV);
    // C now contiains V C^-1 V
    // Propagate corrected errors to parameters objects
    //roominimize->applyCovarianceMatrix(matC);
    
    roominimize->applyCovarianceMatrixExt(matC);
  }
  
  delete rw;
  delete rw2;
}
//###################################################################################################
