//info : for new production h026 sys
//https://indico.cern.ch/event/978356/contributions/4120988/attachments/2155032/3634628/yybb_Introduction_2Dec2020_VMMCAIRO.pdf
////"yybb_nonRes_XGBoost_" + jetPreSelLabel+ CorrLabel+ "Cat" (and scores/cut based)
// ->
// "yybb_nonRes_XGBoost_" + CorrLabel+ "Cat"
////
////So now you really need to request cutflow== 7 before selecting the category (was implicitly required before by choice of 'jetPreSelLabel')

bool do_h026_Experimental_systematics=1;

//no more
//bool do_preselection_by_hand_Experimental_systematics=0; //0, starting from new h026 samples syst
//#######################################################################################################################################################################################################
//Problematic :
//nominal in sample A
//nominal in sample B
//sys1 exists in sample A
//sys1 exists in sample B

//sys2 exists in sample A
//sys2 does not exist in sample B

//thus, when adding A and B, the nominal is big, while the sys2 is small : it artificially makes a huge systematic
//if one creates artificially the fake syst and fill it with nominal, it artificially reduce the effect of systematic
//but actually, it is normal, for the common

//another solution is to create as many nominal as the number of systematics
//this drives to huge bookeeping

//the first solution to create the missing systematic is the most transparent approach
//in particular, for those systematics that don't exist officially, they would appear as null, thus they would be skipped by the pruning of the next program that estimate them
//so everything is transparent with this approach

//trick to get all systematics
//   const CP::SystematicRegistry &registry = CP::SystematicRegistry::getInstance();
//   std::vector<CP::SystematicSet> tempList = CP::make_systematics_vector(registry.recommendedSystematics());
//   for (auto sys : tempList)
//     Info("","From all syst, sys = %s",sys.name().c_str());
// to test if a systematic is available : isSystematicAvailable


//FOR RESONANT : in case of crash for resonant, make the trick of create selection baseline, with accessor and two variantes of names of variables

//HOW TO ACCELERATE THAT CODE in the treat_ method ??!?

// for the scale, the ALL and AF2 NP have to be taken into account.
// For the resolution, however, ALL already contains the AF2 variation, and one expects a single NP. This is slightly
// misleading, but correctly done (in principle) in the tool

unsigned int nb_categories_tool_exp_syst=0;

bool OLD_PRODUCTION=0;

bool inclusive_selection_exp_systematics=0;

//map is 5 % slower, but tab is too dangerous, in case the nominal would not be the first one for some productions

//to store mu in order to understand the change for PRW, in particular due to ggH which has a different sign for the effet of PRW with respect to other processes

//root [6] CollectionTree->Scan("EventInfoAux.actualInteractionsPerCrossing:EventInfoAux.averageInteractionsPerCrossing")

//see the plot of mu weighted by the weight_, to deduce if there is something

//CollectionTree->Scan("EventInfoAux.eventNumber:HGamEventInfoAuxDyn.isPassed:HGamEventInfo_JET_BJES_Response__1upAuxDyn.isPassed:HGamEventInfoAuxDyn.yybb_nonRes_cutBased_discreteMV2c10_Cat:HGamEventInfo_JET_BJES_Response__1upAuxDyn.yybb_nonRes_cutBased_discreteMV2c10_Cat","EventInfoAux.eventNumber==510251")

//to improve with pointers

//put pointer in the end : 1) string : avoid ; 2) add loops and pointer
//continuer "string_"

//could speed up by using array instead of map of string ?
//maybe not necessary

//in order to have the appropriate normalization, one needs to switch on the SumOfWeight files :
//example
// Include:          HGamAnalysisFramework/MCSamples.config
// +Include:          HGamAnalysisFramework/SumOfWeights_h015d.config

//TO DO
//1) to merge low and high mass in a table

//manage better index_b_tag by creating a buffer of index_tag : would simplify
//see if could improve the duplicate of code

//manage with additional table to prevent writing low mass and high mass
//

#include "HHyybb/tool_Experimental_Systematics.h"
#include "EventLoop/OutputStream.h"
#include "HGamAnalysisFramework/HGamCommon.h"
#include "HGamAnalysisFramework/HGamVariables.h"

#include <cstdio>
#include <cstdlib>
#include <string>

#include <TH1D.h>

// this is needed to distribute the algorithm to the workers
ClassImp(tool_Experimental_Systematics)

bool flag_tool_Experimental_Systematics_IsThisMxAOD=1;

using namespace std;

string string_path="/sps/atlas/e/escalier/ATLAS_HGam/";

string string_rel_path_experimental_systematics="Outputs_syst_yield_shape/";

vector<int> vec_mX_exp_systematics={251,260,280,300,325,350,400,450,500,550,600,700,800,900,1000};

//#######################################################################################################################################################################################################
tool_Experimental_Systematics::tool_Experimental_Systematics(const char *name)
: HgammaAnalysis(name)
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // initialize().
}
//#######################################################################################################################################################################################################
tool_Experimental_Systematics::~tool_Experimental_Systematics()
{
  // Here you delete any memory you allocated during your analysis.
}
//#######################################################################################################################################################################################################
EL::StatusCode tool_Experimental_Systematics::createOutput()
{
  cout << "createOutput, phase 1" << endl;

  // Here you setup the histograms needed for you analysis. This method
  // gets called after the Handlers are initialized, so that the systematic
  // registry is already filled.

  //commented in order to make data trees

  if (!HG::isMC()) {
    cout << "this tool is not supposed to work for input different to MC ; halt program" << endl;
    exit(1);
  }

  TH1::SetDefaultSumw2(1);

  cout << "createOutput, phase 2" << endl;

  sampleName=wk()->metaData()->castString("sample_name"); //SH::MetaFields::sampleName
  
  cout << "sampleName=" << sampleName << endl;
  
  if (inclusive_selection_exp_systematics) {
    vec_string_category.push_back("baseline");
    
    //  vec_string_category[5]="Resonant"; //if this changes, careful : some changes at some other places
  }
  else { //case modern categorisation
    vec_string_category.clear();
    FillListCategories();
  } //end modern categorisation
  
  nb_categories_tool_exp_syst=vec_string_category.size();

  for (unsigned int index_category=0;index_category<nb_categories_tool_exp_syst;index_category++) {
    cout << vec_string_category[index_category] << endl;
    cout << "index_category=" << index_category << ", " << vec_string_category[index_category] << endl;
  }

  gSystem->Exec((string("mkdir -p ")+string_path+string_rel_path_experimental_systematics).c_str());  
  gSystem->Exec((string("mkdir -p ")+string_path+string_rel_path_experimental_systematics).c_str());

  gSystem->Exec((string("mkdir -p ")+string_path+string_rel_path_experimental_systematics+"trees_and_hist/").c_str());
  gSystem->Exec((string("mkdir -p ")+string_path+string_rel_path_experimental_systematics+"trees_and_hist/subjobs").c_str());
  
  if (sampleName.find("PhotonSys")!=string::npos)
    gSystem->Exec((string("mkdir -p ")+string_path+string_rel_path_experimental_systematics+"/trees_and_hist/subjobs/PhotonSys").c_str());
  else if (sampleName.find("PhotonAllSys")!=string::npos)
    gSystem->Exec((string("mkdir -p ")+string_path+string_rel_path_experimental_systematics+"/trees_and_hist/subjobs/PhotonAllSys").c_str());
  else if (sampleName.find("JetSys1")!=string::npos)
    gSystem->Exec((string("mkdir -p ")+string_path+string_rel_path_experimental_systematics+"/trees_and_hist/subjobs/JetSys1").c_str());
  else if (sampleName.find("JetSys2")!=string::npos)
    gSystem->Exec((string("mkdir -p ")+string_path+string_rel_path_experimental_systematics+"/trees_and_hist/subjobs/JetSys2").c_str());
  else if (sampleName.find("JetSys3")!=string::npos)
    gSystem->Exec((string("mkdir -p ")+string_path+string_rel_path_experimental_systematics+"/trees_and_hist/subjobs/JetSys3").c_str());
  else if (sampleName.find("JetSys4")!=string::npos)
    gSystem->Exec((string("mkdir -p ")+string_path+string_rel_path_experimental_systematics+"/trees_and_hist/subjobs/JetSys4").c_str());
  else if (sampleName.find("FlavorSys")!=string::npos)
    gSystem->Exec((string("mkdir -p ")+string_path+string_rel_path_experimental_systematics+"/trees_and_hist/subjobs/FlavorSys").c_str());
  else if (sampleName.find("LeptonMETSys")!=string::npos)
    gSystem->Exec((string("mkdir -p ")+string_path+string_rel_path_experimental_systematics+"/trees_and_hist/subjobs/LeptonMETSys").c_str());

  string string_file_syst_yield_and_shape=string_path+string_rel_path_experimental_systematics+"trees_and_hist/subjobs/";

  string_file_syst_yield_and_shape+=ReturnSubDirectoryWhereToStore(sampleName);
  string_file_syst_yield_and_shape+="/";

  string_file_syst_yield_and_shape+=sampleName;
  string_file_syst_yield_and_shape+=".root";

  cout << "string_file_syst_yield_and_shape=" << string_file_syst_yield_and_shape << endl;
  file_syst_shape=new TFile(string_file_syst_yield_and_shape.c_str(),"recreate"); //mandatory before the loop, due to persisting behaviour of TTree

  cout << "createOutput: systematics probed" << endl;

  //to improve also in code theory

  FillListVariations(); //this fillls m_variations_translated
  
  //initialize counters and trees

  for (unsigned int index_category=0;index_category<nb_categories_tool_exp_syst;index_category++) {
    
    //---------------------------------------------------------------------------------------------------
    //yield related informations, nominal part

    /*shit
    map_nb_sel_f_categ_sys[index_category]["nominal"]=0;
    map_err_nb_sel_f_categ_sys[index_category]["nominal"]=0;

    map_nb_sel_f_categ_sys_unweighted[index_category]["nominal"]=0;
    map_err_nb_sel_f_categ_sys_unweighted[index_category]["nominal"]=0;
    */
    //---------------------------------------------------------------------------------------------------
    for (unsigned int index_sys=0;index_sys<m_variations_translated.size();index_sys++) {
      
      string string_variation_translated=m_variations_translated[index_sys];
      
      //---------------------------------------------------------------------------------------------------
      //yield related informations
      
      //no gain with tab, and advantange of map in case order of nominal changes
      
      map_nb_sel_f_categ_sys[index_category][string_variation_translated]=0;
      map_err_nb_sel_f_categ_sys[index_category][string_variation_translated]=0;
      
      map_nb_sel_f_categ_sys_unweighted[index_category][string_variation_translated]=0;
      map_err_nb_sel_f_categ_sys_unweighted[index_category][string_variation_translated]=0;
      
      if (string_variation_translated!="nominal") {
	
	//--dedicated variables for computing the error on sytematics, taking into account the correlation
	
	map_err_nb_sel_f_categ_sys_common_part_nominal[index_category][string_variation_translated]=0;
	map_err_nb_sel_f_categ_sys_uncommon_part_nominal[index_category][string_variation_translated]=0;
	//not useful map_err_nb_sel_f_categ_sys_common_part_sys[index_category][string_variation_translated]=0;
	
	map_err_nb_sel_f_categ_sys_uncommon_part_sys[index_category][string_variation_translated]=0;
	
	//--additional informations for debugging/checks, for computing the error on sytematics, taking into account the correlation
	map_nb_sel_f_categ_sys_common_part_nominal[index_category][string_variation_translated]=0;
	map_nb_sel_f_categ_sys_uncommon_part_nominal[index_category][string_variation_translated]=0;
	//not useful      map_nb_sel_f_categ_sys_common_part_sys[index_category][string_variation_translated]=0;
	map_nb_sel_f_categ_sys_uncommon_part_sys[index_category][string_variation_translated]=0;
	
	//dedicated variable to deduce wether there is a full correlation or not
	
	map_nb_sel_f_categ_sys_uncommon_part_nominal_unweighted[index_category][string_variation_translated]=0;
	map_err_nb_sel_f_categ_sys_uncommon_part_nominal_unweighted[index_category][string_variation_translated]=0;
	
	map_nb_sel_f_categ_sys_uncommon_part_sys_unweighted[index_category][string_variation_translated]=0;
	map_err_nb_sel_f_categ_sys_uncommon_part_sys_unweighted[index_category][string_variation_translated]=0;
      } //end case non nominal
      //---------------------------------------------------------------------------------------------------
      //shape related informations
      
      string string_tree_output="tree_sel_";
      string_tree_output+=string_variation_translated;
      string_tree_output+="_";
      string_tree_output+=vec_string_category[index_category];
      
      map_tree_sel_f_categ[index_category][string_variation_translated]=new TTree(string_tree_output.c_str(),string_tree_output.c_str());
      
      map_tree_sel_f_categ[index_category][string_variation_translated]->Branch("index_event",&m_index_event); //do not rename it (index_entry used for the other program : do not mix them else wrong algorithm)
      map_tree_sel_f_categ[index_category][string_variation_translated]->Branch("eventNumber",&m_eventNumber); //eventNumber is necessary in order to be able to do jacknife studies
      map_tree_sel_f_categ[index_category][string_variation_translated]->Branch("mcID",&m_mcID); //necessary in order to avoid having same eventNumber from different processes



      if (do_h026_Experimental_systematics && HG::isMC() && sampleName.find("cHHH01d0")!=string::npos)
	map_tree_sel_f_categ[index_category][string_variation_translated]->Branch("truth_m_hh",&m_truth_m_hh); //eventNumber is necessary in order to be able to do jacknife studies

      //removed      map_tree_sel_f_categ[index_category][string_variation_translated]->Branch("yybb_Cat",&m_yybb_Cat);
      
      map_tree_sel_f_categ[index_category][string_variation_translated]->Branch("m_yy",&m_m_yy);
      map_tree_sel_f_categ[index_category][string_variation_translated]->Branch("m_bb",&m_m_bb);
      
      map_tree_sel_f_categ[index_category][string_variation_translated]->Branch("m_yybb",&m_m_yybb);
      map_tree_sel_f_categ[index_category][string_variation_translated]->Branch("m_yybb_cnstrnd",&m_m_yybb_cnstrnd);
      map_tree_sel_f_categ[index_category][string_variation_translated]->Branch("m_yybb_tilde",&m_m_yybb_tilde);
      
      map_tree_sel_f_categ[index_category][string_variation_translated]->Branch("weight_event",&m_weight_event);
      map_tree_sel_f_categ[index_category][string_variation_translated]->Branch("weight_total",&m_weight_total);
      map_tree_sel_f_categ[index_category][string_variation_translated]->Branch("weight_lumi",&m_weight_lumi);
      //-----
      if (string_variation_translated=="nominal") {
	map_hist_nb_sel_f_categ[index_category][string_variation_translated]=new TH1D((string("hist_nb_sel_"+string_variation_translated+"_"+vec_string_category[index_category])).c_str(),
										      (string("hist_nb_sel_"+string_variation_translated+"_"+vec_string_category[index_category])).c_str(),1,-1e9,1e9);
	
	map_hist_nb_sel_f_categ_unweighted[index_category][string_variation_translated]=new TH1D((string("hist_nb_sel_"+string_variation_translated+"_"+vec_string_category[index_category])+"_unweighted").c_str(),
												 (string("hist_nb_sel_"+string_variation_translated+"_"+vec_string_category[index_category])+"_unweighted").c_str(),1,-1e9,1e9);
      }
      else {
	map_hist_nb_sel_f_categ[index_category][string_variation_translated]=new TH1D((string("hist_nb_sel_sys_"+string_variation_translated+"_"+vec_string_category[index_category])).c_str(),
										      (string("hist_nb_sel_sys_"+string_variation_translated+"_"+vec_string_category[index_category])).c_str(),1,-1e9,1e9);
	
	map_hist_nb_sel_f_categ_unweighted[index_category][string_variation_translated]=new TH1D((string("hist_nb_sel_sys_"+string_variation_translated+"_"+vec_string_category[index_category])+"_unweighted").c_str(),
												 (string("hist_nb_sel_sys_"+string_variation_translated+"_"+vec_string_category[index_category])+"_unweighted").c_str(),1,-1e9,1e9);
	
	map_hist_nb_sel_uncommon_part_nominal_f_categ[index_category][string_variation_translated]=new TH1D((string("hist_nb_sel_uncommon_part_nominal_"+string_variation_translated+"_"+vec_string_category[index_category])).c_str(),
													    (string("hist_nb_sel_uncommon_part_nominal_"+string_variation_translated+"_"+vec_string_category[index_category])).c_str(),1,-1e9,1e9);
	map_hist_nb_sel_common_part_nominal_f_categ[index_category][string_variation_translated]=new TH1D((string("hist_nb_sel_common_part_nominal_"+string_variation_translated+"_"+vec_string_category[index_category])).c_str(),
													  (string("hist_nb_sel_common_part_nominal_"+string_variation_translated+"_"+vec_string_category[index_category])).c_str(),1,-1e9,1e9);
	map_hist_nb_sel_uncommon_part_sys_f_categ[index_category][string_variation_translated]=new TH1D((string("hist_nb_sel_uncommon_part_sys_"+string_variation_translated+"_"+vec_string_category[index_category])).c_str(),
													(string("hist_nb_sel_uncommon_part_sys_"+string_variation_translated+"_"+vec_string_category[index_category])).c_str(),1,-1e9,1e9);
	
	map_hist_nb_sel_uncommon_part_nominal_f_categ_unweighted[index_category][string_variation_translated]=new TH1D((string("hist_nb_sel_uncommon_part_nominal_"+string_variation_translated+"_"+vec_string_category[index_category])+"_unweighted").c_str(),
														       (string("hist_nb_sel_uncommon_part_nominal_"+string_variation_translated+"_"+vec_string_category[index_category])+"_unweighted").c_str(),1,-1e9,1e9);
	map_hist_nb_sel_uncommon_part_sys_f_categ_unweighted[index_category][string_variation_translated]=new TH1D((string("hist_nb_sel_uncommon_part_sys_"+string_variation_translated+"_"+vec_string_category[index_category])+"_unweighted").c_str(),
														   (string("hist_nb_sel_uncommon_part_sys_"+string_variation_translated+"_"+vec_string_category[index_category])+"_unweighted").c_str(),1,-1e9,1e9);
      }
    } //end loop on categories
  } //end loop on systematics
  //================================
  cout << "summary of systematics" << endl;
  for (unsigned int index_variation=0;index_variation<m_variations_translated.size();index_variation++)
    cout << "index_variation=" << index_variation << " " << m_variations_translated[index_variation] << endl;
  
  //remark : one could use also HG::mcType()
  
  m_mcID=eventInfo()->mcChannelNumber(); //necessary also for the common/uncommon when merging several processes
  cout << "mcID=" << m_mcID << endl;
  
  //forbidden to get event info before the loop, because it would crash in presence of several files, because the pointer would not be at the good location
  //Thus, forbidden to get mcChannelNumber from event info here, because event info would not be loaded again for the next file : we are here in createOutput
  //m_weight_lumi=1;
  
  m_weight_lumi=lumiXsecWeight(1.,m_mcID,1);
  
  //--------------
  //final luminosity Moriond 2021 : dictated by the framework
  
  //       20170619 : GRL v89 :  3 219.56 pb-1
  //       20180129 : GRLv89 : 32 988.1 pb-1
  //       36 207.66 pb-1
  //       20180619 : GRLv99 : 44 307.4 pb-1
  //       20190318 : GRLv102 : 58 450.1 pb-1
  //       138 965.16 pb-1
  
  if (sampleName.find("mc16a")!=string::npos)
    m_weight_lumi*=36.20766;
  else if (sampleName.find("mc16d")!=string::npos)
    m_weight_lumi*=44.3074;
  else if (sampleName.find("mc16e")!=string::npos)
    m_weight_lumi*=58.4501;
  //--------------
  /*
  //new scheme of luminosity
  //references:
  // /cvmfs/atlas.cern.ch/repo/sw/database/GroupData/GoodRunsLists/data18_13TeV/20190708/
  // Luminosity:   3219.44 pb-1
  // Luminosity:   32989.6 pb-1
  // Luminosity:   44385.7 pb-1
  // Luminosity:   58450.1 pb-1
  
  if (sampleName.find("mc16a")!=string::npos)
    m_weight_lumi*=36.20904;
  else if (sampleName.find("mc16d")!=string::npos)
    m_weight_lumi*=44.3857;
  else if (sampleName.find("mc16e")!=string::npos)
    m_weight_lumi*=58.4501;
  */

  printf("m_weight_lumi=%10.10f\n",m_weight_lumi);
  //=========================
  
  m_index_event=0; //used for seed of destination trees, in order to have no duplicates of event when doing bootstrap method with random numbers

  return EL::StatusCode::SUCCESS;
}
//#######################################################################################################################################################################################################
EL::StatusCode tool_Experimental_Systematics::execute()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.

  // Important to keep this, so that internal tools / event variables
  // are filled properly.
  
  //  cout << "new event" << endl;

  HgammaAnalysis::execute();

  m_index_event++; //mandatory, for synchronizing the random numbers seed of the same events, and avoiding to go to quickly to the max number of the range of seeds

  /*
  if (
      eventInfo()->eventNumber()!=510251
      &&
      eventInfo()->eventNumber()!=498929
      )
    return EL::StatusCode::SUCCESS;
  */

  //  cout << "treat a new eventNumber=" << eventInfo()->eventNumber() << endl;

  //=========================================================================================
  //=========================================================================================
  //=========================================================================================
  //=========================================================================================
  CP::SystematicSet sys_nominal; //!

  m_weight_total_nominal=0; //mandatory at this place, before the loop on the variations
  m_weight_event_nominal=0; //mandatory at this place, before the loop on the variations
  
  //mandatory to use directly the systematic getSystematic, because of applySystematicVariation(sys)
  //  for (auto sys:getSystematics()) {
  for (CP::SystematicSet sys:getSystematics()) {
    
    string string_sys=sys.name();

    //    cout << "string_sys=" << string_sys << endl;
    if (ProtectAgainstFakeSystematic(string_sys))
      continue;
    
    current_is_nominal=0;
    
    string string_HGamEventInfo="HGamEventInfo";
    
    if (string_sys=="") {
      current_is_nominal=1;
      sys_nominal=sys; //save it for later purpose : else last systematics would bias results once going back to nominal
    }
    else {
      string_HGamEventInfo+="_";
      string_HGamEventInfo+=string_sys;
    }
    
    //check if find the systematics (this allows in particular not to have warning during the execution due to non-existing systematics)
    
    m_HGamEventInfo=0;
    event()->retrieve(m_HGamEventInfo,string_HGamEventInfo.c_str());
    if (!m_HGamEventInfo) {
      cout << string_sys << " not in MxAOD, ignore it" << endl;
      continue;
    }
    
    //this considers the nominal as well
    
    CP_CHECK("execute()",applySystematicVariation(sys));
    
    //need nominal as weel for current systematic, in order to make a decision for the common/uncomments events with respect to systematics
    
    string string_variation_translated=Translate_current_variation(string_sys);
    
    treat_selection_current_systematics_or_nominal(string_variation_translated);
  } //end loop on syst
  
  //not necessary to come back to nominal
  //    CP_CHECK("execute()",applySystematicVariation(sys_nominal));
  
  return EL::StatusCode::SUCCESS;
}
//#######################################################################################################################################################################################################
bool tool_Experimental_Systematics::treat_selection_current_systematics_or_nominal(string string_current_variation)
{
  //  cout << "treat_selection_current_systematics_or_nominal=" << "treat_selection_current_systematics_or_nominal for " <<  string_current_variation << endl;

  //current_is_nominal filled previously

  for (unsigned int index_category=0;index_category<nb_categories_tool_exp_syst;index_category++) {
    
    m_pass_HH_f_categ[index_category]=0;
    
    if (current_is_nominal)
      m_pass_HH_nominal_f_categ[index_category]=0;
  }
  
  //was *thought* to be mandatory
  //mandatory to put the weights here, before the isPassed, because of the treatment of common and uncommon, which need to have stored the weight value already, in the case of the "common" part [so called nominal] of the yields, with a given systematic that succeeds while the nominal fails
  
  //collection of objects not stored in MxAOD systematics
  
  //  cout << "about to look at cutFlow>=15" << endl;
  //-------------------------------------------
  //HGam selection
  
  //  bool isPassed=m_HGamEventInfo->auxdata<char>("isPassed");
  //isPassed=var::isPassed();
  //  cout << "isPassed=" << isPassed << endl;

  //NEW, to prevent duplicates
  int cutFlow=m_HGamEventInfo->auxdata<int>("cutFlow");
  bool Avoid_duplicates=(cutFlow>=15);

  bool isPassed=Avoid_duplicates;

  //  cout << "about to look at passCrackVetoCleaning" << endl;
  //-------------------------------------------
  bool is_passCrackVetoCleaning=1;

  //https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/HowToCleanJetsR21#EGamma_Crack_Electron_topocluste  



  //for new samples h026 Sys, no more to apply the cut 2-b jets
  // for old samples h026 Sys, need to apply 2-b jets by hand

  if (
      sampleName.find("mc16a")!=string::npos
      ||
      sampleName.find("data15")!=string::npos
      ||
      sampleName.find("data16")!=string::npos
      ||
      sampleName.find("data1516")!=string::npos
      ) {    
    is_passCrackVetoCleaning=m_HGamEventInfo->auxdata<char>("passCrackVetoCleaning");
    if (!is_passCrackVetoCleaning)
      isPassed=0;
  }
  
  //  cout << "deal with preselection 2 b jets" << endl;
  //-------------------------------------------
  pass_preselection_2_bjets=1;

  /*  
  pass_preselection_2_bjets=0;

  if (do_h026_Experimental_systematics) {
    
    if (do_preselection_by_hand_Experimental_systematics) {
      
      int Nbjets=0;
      
      if ( event()->retrieve(ptr_const_jets,"HGamAntiKt4PFlowCustomVtxHggJets").isFailure() )
	HG::fatal("Cannot access jets for full collection");

      int nb_jets=ptr_const_jets->size();
      
      static SG::AuxElement::Accessor<char> acc_DL1r_FixedCutBEff_77("DL1r_FixedCutBEff_77");
      
      for (int index_jet=0;index_jet<nb_jets;index_jet++) {
	const xAOD::Jet *current_jet=(*ptr_const_jets)[index_jet];
	//      for (int i=0; i<HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn_eta.GetSize(); i++){
	if (acc_DL1r_FixedCutBEff_77(*current_jet))
	  Nbjets++;
      }
      
      if (Nbjets==2)
	pass_preselection_2_bjets=1;
    }
    else {
      if ( event()->retrieve(ptr_const_jets,"HGamAntiKt4PFlowCustomVtxHggJets").isFailure() )
	HG::fatal("Cannot access jets for full collection");
      
      int index_jet1_fix=m_HGamEventInfo->auxdata<int>("yybb_candidate_jet1_fix");
      int index_jet2_fix=m_HGamEventInfo->auxdata<int>("yybb_candidate_jet2_fix");
      
      if (index_jet1_fix>=0 && index_jet2_fix>=0 && index_jet1_fix<ptr_const_jets->size() && index_jet2_fix<ptr_const_jets->size()) { //mandatory, to prevent crash
	
	//	cout << "ptr_const_jets->size()=" << ptr_const_jets->size() << endl;
	//	cout << "index_jet1_fix=" << index_jet1_fix << endl;
	//	cout << "index_jet2_fix=" << index_jet2_fix << endl;
	
	const xAOD::Jet *jet1_fixed=(*ptr_const_jets)[index_jet1_fix];
	const xAOD::Jet *jet2_fixed=(*ptr_const_jets)[index_jet2_fix];

	//	cout << "jet1_fixed=" << jet1_fixed << endl;
	//	cout << "jet2_fixed=" << jet2_fixed << endl;
	
	//	cout << "access to DL1r_FixedCutBEff_77, phase 1" << endl;

	static SG::AuxElement::Accessor<char> acc_DL1r_FixedCutBEff_77("DL1r_FixedCutBEff_77");
	
	//	cout << "access to DL1r_FixedCutBEff_77, phase 2" << endl;

	bool jet1_pass_b_tag=0;
	bool jet2_pass_b_tag=0;

	//to add constraint on size ?

	//	cout << "access to DL1r_FixedCutBEff_77, phase 3" << endl;

	if (acc_DL1r_FixedCutBEff_77.isAvailable(*jet1_fixed)) {
	  //	  cout << "acc_DL1r_FixedCutBEff_77 for jet1 fixed is available" << endl;
	  jet1_pass_b_tag=acc_DL1r_FixedCutBEff_77(*jet1_fixed);
	}
	else {
	  // 	  cout << "treat_selection_current_systematics_or_nominal=" << "treat_selection_current_systematics_or_nominal for " <<  string_current_variation << endl;
	  // 	  cout << "treat of eventNumber=" << eventInfo()->eventNumber() << endl;
	  // 	  cout << "acc_DL1r_FixedCutBEff_77 for jet1 fixed is NOT available" << endl;
	}

	//	cout << "access to DL1r_FixedCutBEff_77, phase 4" << endl;

	if (acc_DL1r_FixedCutBEff_77.isAvailable(*jet2_fixed)) {
	  //	  cout << "acc_DL1r_FixedCutBEff_77 for jet2 fixed is available" << endl;
	  jet2_pass_b_tag=acc_DL1r_FixedCutBEff_77(*jet2_fixed);
	}
	else {
	  cout << "treat_selection_current_systematics_or_nominal=" << "treat_selection_current_systematics_or_nominal for " <<  string_current_variation << endl;
	  cout << "treat of eventNumber=" << eventInfo()->eventNumber() << endl;
	  cout << "acc_DL1r_FixedCutBEff_77 for jet2 fixed is NOT available" << endl;
	}

	//	cout << "jet1_pass_b_tag=" << jet1_pass_b_tag << endl;
	//	cout << "jet2_pass_b_tag=" << jet2_pass_b_tag << endl;

	if (jet1_pass_b_tag && jet2_pass_b_tag)
	  pass_preselection_2_bjets=1;
      }
    }
  } // end h026

  if (!pass_preselection_2_bjets)
    isPassed=0;


  */


  //  cout << "dealt with preselection 2 b jets" << endl;

  //-------------------------------------------
  //  int variable_yybb_cutflow=m_HGamEventInfo->auxdata<int>("yybb_btag77_BCal_cutFlow");

  int variable_yybb_cutflow=m_HGamEventInfo->auxdata<int>("yybb_btag77_cutFlow"); //new name sure, in all cases

  //  if (variable_yybb_cutflow!=6) //if h026 sys old, take this line and switch on the hand made b-jet preselection above


  //MARC for specific old ttH
  //  if (variable_yybb_cutflow!=6) //this contains the 2-b-jets preselection

  if (variable_yybb_cutflow!=7) //this contains the 2-b-jets preselection
    isPassed=0;
  //-------------------------------------------
  //careful not to put it above, due to remaining information needed
  
  //do not halt program if selection does not pass gamgam selection
  //indeed, in case nominal passes but systematics fails, one would not fill the case "fail syst but pass nominal"!!
  
  //to be replaced by the appropriate variable

  //do not move since category may use it
  
  m_m_yy=var::m_yy()*0.001;
  
  m_m_bb=m_HGamEventInfo->auxdata<float>("yybb_BCal_m_jj")*0.001; //already in GeV (bug from h024)

  m_m_yybb=m_HGamEventInfo->auxdata<float>("yybb_BCal_m_yyjj")*0.001;
  m_m_yybb_cnstrnd=m_HGamEventInfo->auxdata<float>("yybb_BCal_m_yyjj_cnstrnd")*0.001;

  //necessary before the IsPassResonant
  m_m_yybb_tilde=m_HGamEventInfo->auxdata<float>("yybb_BCal_m_yyjj_tilde")*0.001;
  
  //one category for the moment, decreate the index is 0
  
  //  cout << "isPassed=" << isPassed << endl;

  //  cout << "string_current_variation=" << string_current_variation.c_str() << endl;

  if (inclusive_selection_exp_systematics) {

    //TO ADD isPassed

    for (unsigned int index_category=0;index_category<nb_categories_tool_exp_syst;index_category++) {
      
      m_pass_HH_f_categ[index_category]=1;
    }
  }
  else { //modern categorisation

    if (isPassed) { //ok : consider it !

      string string_category;
      
      if (sampleName.find("_X")==string::npos) { //sample is not a resonant sample, so either a HH non resonant or a single Higgs
	
	//so consider inclusion of non resonant categories
	
	//---------------------------------------------
	//HH non resonant

	//	cout << "call ReturnRecoCategoryNonResonant" << endl;

	string_category=ReturnRecoCategoryNonResonant();
	
	int index_category=ReturnIndexCategory(string_category);
	
	//      cout << "string_category=" << string_category << ", index_category=" << index_category << endl;
	if (index_category>=0)
	  m_pass_HH_f_categ[index_category]=1;
      }
      
      //so consider inclusion of resonant categories
      
      //---------------------------------------------
      //HH resonant
      
      for (unsigned int index_mX=0;index_mX<vec_mX_exp_systematics.size();index_mX++) {
	int mX=vec_mX_exp_systematics[index_mX];
	
	  //	cout << "mX=" << mX << endl;
	  
	  if (IsPassResonant(mX)) {
	    
	    //	  cout << "it passes" << endl;
	    
	    string_category="Resonant_mX"+to_string(mX);
	    int index_category=ReturnIndexCategory(string_category);
	    m_pass_HH_f_categ[index_category]=1;
	  } //end case passes selection
	} //end loop on resonant samples
    }
  } //end modern categorisation
  
  //optimization
  //maybe I could go further and put it after the pass HH ?
  //for later only
  
  //  m_weight=var::weight(); //weight is not recomputed, apart if one uses setSelObjects
  
  m_weight=m_HGamEventInfo->auxdata<float>("weight");
  
  m_weight_yybb=m_HGamEventInfo->auxdata<float>("yybb_weight");

  double m_weightFJvt=m_HGamEventInfo->auxdata<float>("weightFJvt");
  
  m_weight_event=m_weight*m_weight_yybb*m_weightFJvt;
  m_weight_total=m_weight_lumi*m_weight*m_weight_yybb*m_weightFJvt;
  
  if (current_is_nominal) {
    m_weight_total_nominal=m_weight_total;
    m_weight_event_nominal=m_weight_event;
  }
  
  //  printf("at this stage, m_weight=%10.10f, m_weight_yybb=%10.10f, m_weight_total=%10.10f, m_weight_total_nominal=%10.10f\n",m_weight,m_weight_yybb,m_weight_total,m_weight_total_nominal);
  
  //----------------------------------
  //----------------------------------
  //-----
  //forbidden to factorize the multiplicity of b-tag, since this is something that could change with systematics
  //-----
  if (current_is_nominal) {
    //    cout << "this is nominal" << endl;
    
    for (unsigned int index_category=0;index_category<nb_categories_tool_exp_syst;index_category++) {
      
      if (m_pass_HH_f_categ[index_category]==1)
	m_pass_HH_nominal_f_categ[index_category]=1;
    } //end case nominal
  } //end case nominal
  
  //due to the trick of common/uncommon, there is no way to generalize the following various variables
  
  //  cout << "classify the event" << endl;

  for (unsigned int index_category=0;index_category<nb_categories_tool_exp_syst;index_category++) {      
    //    cout << "index_category=" << index_category << endl;
    //    cout << "m_pass_HH_f_categ[index_category]=" << m_pass_HH_f_categ[index_category] << endl;
    
    //weight nominal needs to be a variable from the class, in order to remind the value for the nominal variation
    //by all mean, do not initialize weight nominal here, else it would initialize it when dealing with a given category !!

    //--------------------
    //treatment of tree for shape
    //code separated from yield, because one stores the tree independently of #b-tags
    
    if (m_pass_HH_f_categ[index_category]) {
      
      m_eventNumber=eventInfo()->eventNumber();
      
      if (do_h026_Experimental_systematics && HG::isMC() && sampleName.find("cHHH01d0")!=string::npos) {
	event()->retrieve(m_HGamTruthEventInfo,"HGamTruthEventInfo");
	m_truth_m_hh=m_HGamTruthEventInfo->auxdata<float>("m_hh")*0.001;
      }

      map_tree_sel_f_categ[index_category][string_current_variation]->Fill();
      
      //      cout << "eventNumber=" << m_eventNumber << endl;
      //      cout << "pass selection for current variation (either syst or nominal)" << endl;
      
      map_nb_sel_f_categ_sys[index_category][string_current_variation]+=m_weight_total;
      map_err_nb_sel_f_categ_sys[index_category][string_current_variation]+=m_weight_total*m_weight_total;
      
      map_nb_sel_f_categ_sys_unweighted[index_category][string_current_variation]++;
      map_err_nb_sel_f_categ_sys_unweighted[index_category][string_current_variation]++;
      
      //since isPassed is first to the list, the systematics common/uncommon events could be deduced
      
      if (current_is_nominal) {
	m_pass_HH_nominal_f_categ[index_category]=1;
	//	cout << "current is nominal and passes selection" << endl;
      }
      else { //non-nominal

	if (m_pass_HH_nominal_f_categ[index_category]) { //nominal passes selection
	  
	  //	  cout << "eventNumber=" << m_eventNumber << endl;
	  //	  cout << "current variation passes selection, and nominal passes selection : common event" << endl;
	  
	  //two first variables are not necessary for the error computation, but useful for debugging [in order to know how many are common/uncommon]

	  //	  printf("after, %10.10f\n",map_nb_sel_f_categ_sys_common_part_nominal[index_category][string_current_variation]);

	  map_nb_sel_f_categ_sys_common_part_nominal[index_category][string_current_variation]+=m_weight_total_nominal; //increase the nominal in the same pass
	  map_err_nb_sel_f_categ_sys_common_part_nominal[index_category][string_current_variation]+=m_weight_total_nominal*m_weight_total_nominal;
	}
	else { //nominal does not pass selection
	  //	  cout << "eventNumber=" << m_eventNumber << endl;
	  //	  cout << "current variation passes selection, but nominal does not pass selection" << endl;
	  
	  //first is necessary for the error computation, but useful for debugging [in order to know how many are common/uncommon]
	  
	  map_nb_sel_f_categ_sys_uncommon_part_sys[index_category][string_current_variation]+=m_weight_total;
	  map_err_nb_sel_f_categ_sys_uncommon_part_sys[index_category][string_current_variation]+=m_weight_total*m_weight_total;
	  
	  map_nb_sel_f_categ_sys_uncommon_part_sys_unweighted[index_category][string_current_variation]++;
	  map_err_nb_sel_f_categ_sys_uncommon_part_sys_unweighted[index_category][string_current_variation]++;
	  
	  //	      cout << "EventNumber=" << eventInfo()->eventNumber()
	  
	} //nominal does not pass selection
      } //end case non-nominal
    } //end pass current variation
    else { //fail selection for current b-tag : either because the selection fails or because b-category changed
      if (!current_is_nominal) { //non-nominal

	if (m_pass_HH_nominal_f_categ[index_category]) { //this means that the systematics failed while the nominal succeeded : so add event to nominal uncommon
	  //	  cout << "eventNumber=" << m_eventNumber << endl;
	  //	  cout << "current variation fails selection, and nominal passes selection" << endl;
	  
	  //first is necessary for the error computation, but useful for debugging [in order to know how many are common/uncommon]
	  
	  map_nb_sel_f_categ_sys_uncommon_part_nominal[index_category][string_current_variation]+=m_weight_total_nominal;
	  map_err_nb_sel_f_categ_sys_uncommon_part_nominal[index_category][string_current_variation]+=m_weight_total_nominal*m_weight_total_nominal;
	  
	  map_nb_sel_f_categ_sys_uncommon_part_nominal_unweighted[index_category][string_current_variation]++;
	  map_err_nb_sel_f_categ_sys_uncommon_part_nominal_unweighted[index_category][string_current_variation]++;
	}
      }
    } //end fail
  } //end loop on category
  //=======================
  //--------------------
  
  return 1;
}
//#######################################################################################################################################################################################################
double tool_Experimental_Systematics::get_err_rel_effect_yield_partially_correlated(double yield_nominal,	
								       double yield_common_part_nominal,
								       double yield_uncommon_part_nominal,
								       double yield_uncommon_part_sys,
								       double err_yield_uncommon_part_nominal,
								       double err_yield_common_part_nominal,
								       double err_yield_uncommon_part_sys)
{
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

  /*  
      cout << "- - - - - - - - - - - - - -" << endl;
      cout << "nb_sel_nominal=" << nb_sel_nominal << endl;
      cout << "nb_sel_uncommon_part_nominal=" << nb_sel_uncommon_part_nominal << endl;
      cout << "nb_sel_uncommon_part_sys=" << nb_sel_uncommon_part_sys << endl;
      cout << "err_nb_sel_common_part_nominal=" << err_nb_sel_common_part_nominal << endl;
      cout << "err_nb_sel_uncommon_part_nominal=" << err_nb_sel_uncommon_part_nominal << endl;
      cout << "err_nb_sel_uncommon_part_sys=" << err_nb_sel_uncommon_part_sys << endl;
  
      printf("nb_sel_sys=%10.10f, nb_sel_nominal=%10.10f\n",nb_sel_sys,nb_sel_nominal);
      printf("eff_rel_effect_yield=%10.10f +/- %10.10f\n",rel_effect_yield,err_rel_effect_yield);
  */

  //  cout << "local_err_rel_effect_yield=" << local_err_rel_effect_yield << endl;
  
  return local_err_rel_effect_yield;
}
//#######################################################################################################################################################################################################
double tool_Experimental_Systematics::get_err_rel_effect_yield_fully_correlated(double yield_nominal,
								   double yield_sys,
								   double err_yield_nominal,
								   double err_yield_sys)
{
  double local_err_rel_effect_yield=0;
  
  local_err_rel_effect_yield=100.*sqrt(
				       (pow(yield_sys,2)*pow(err_yield_nominal,2)/pow(yield_nominal,4))
				       +(pow(err_yield_sys,2)/pow(yield_nominal,2))
				       -2.*yield_sys*err_yield_nominal*err_yield_sys/pow(yield_nominal,3)
				       );
  /*  
      cout << "- - - - - - - - - - - - - -" << endl;
      cout << "full treatment" << endl;
      cout << "yield_nominal=" << yield_nominal << endl;
      cout << "yield_sys=" << yield_sys << endl;
      cout << "err_yield_nominal=" << err_yield_nominal << endl;
      cout << "err_yield_sys=" << err_yield_sys << endl;
  
      cout << "local_err_rel_effect_yield=" << local_err_rel_effect_yield << endl;
  */
  return local_err_rel_effect_yield;
}
//#######################################################################################################################################################################################################
int tool_Experimental_Systematics::ProtectAgainstFakeSystematic(string string_variation_translated)
{
  if (sampleName.find("PhotonAllSys")!=string::npos
      &&
      string_variation_translated.find("EG_RESOLUTION_ALL")!=string::npos)
    return 1;
  
  return 0;
}
//#######################################################################################################################################################################################################
string tool_Experimental_Systematics::Translate_current_variation(string string_current_variation)
{
  if (string_current_variation=="")
    string_current_variation="nominal";
  else if (
	   string_current_variation.find("JER")!=string::npos
	   &&
	   (
	    sampleName.find("JetSys3")!=string::npos
	    ||
	    sampleName.find("JetSys4")!=string::npos
	    )
	   ) {
    string string_affixe;
    if (sampleName.find("JetSys3")!=string::npos)
      string_affixe="_MCsmear";
    else if (sampleName.find("JetSys4")!=string::npos)
      string_affixe="_PDsmear";
    
    string string_up="__1up";
    string string_down="__1down";
    
    size_t position_suffix_1up;
    size_t position_suffix_1down;
    
    position_suffix_1up=string_current_variation.find("__1up");
    position_suffix_1down=string_current_variation.find("__1down");
    
    if (position_suffix_1up!=string::npos) {
      string_current_variation.replace(string_current_variation.find("__1up"),string_up.length(),string_affixe.c_str());
      string_current_variation+=string_up;
    }
    else if (position_suffix_1down!=string::npos) {
      string_current_variation.replace(string_current_variation.find("__1down"),string_down.length(),string_affixe.c_str());
      string_current_variation+=string_down;
    }
  }
  
  return string_current_variation;
}
//#######################################################################################################################################################################################################
string tool_Experimental_Systematics::ReturnSubDirectoryWhereToStore(string sampleName)
{
  string string_directory;
  
  if (sampleName.find("PhotonSys")!=string::npos)
    string_directory+="PhotonSys";
  else if (sampleName.find("PhotonAllSys")!=string::npos)
    string_directory+="PhotonAllSys";
  else if (sampleName.find("JetSys1")!=string::npos)
    string_directory+="JetSys1";
  else if (sampleName.find("JetSys2")!=string::npos)
    string_directory+="JetSys2";
  else if (sampleName.find("JetSys3")!=string::npos)
    string_directory+="JetSys3";
  else if (sampleName.find("JetSys4")!=string::npos)
    string_directory+="JetSys4";
  else if (sampleName.find("FlavorSys")!=string::npos)
    string_directory+="FlavorSys";
  else if (sampleName.find("LeptonMETSys")!=string::npos)
    string_directory+="LeptonMETSys";
  
  return string_directory;
}
//#######################################################################################################################################################################################################
string tool_Experimental_Systematics::ReturnRecoCategoryNonResonant()
{
  string string_category="Undefined";

  //MARC for specific old ttH
  //  int NonResonantCategory=m_HGamEventInfo->auxdata<int>("yybb_nonRes_XGBoost_btag77_BCal_Cat");

  //NEW Production
  int NonResonantCategory=m_HGamEventInfo->auxdata<int>("yybb_nonRes_XGBoost_BCal_Cat");
  
  if ( (NonResonantCategory/1000) %10 == 1)
    string_category="XGBoost_btag77_withTop_BCal_tightScore_HMass";
  else if ( (NonResonantCategory/1000) %10 == 2)
    string_category="XGBoost_btag77_withTop_BCal_looseScore_HMass";
  else if ( (NonResonantCategory/1000) %10 == 3)
    string_category="XGBoost_btag77_withTop_BCal_tightScore_LMass";
  else if ( (NonResonantCategory/1000) %10 == 4)
    string_category="XGBoost_btag77_withTop_BCal_looseScore_LMass";
  
  /*  
      int vbf_selected=m_HGamEventInfo->auxdata<int>("yybb_btag77_BCal_vbf_selected");

  if (vbf_selected==1 && ( (NonResonantCategory/1000) %10 ) !=9 )
    string_category="VBF_btag77_withTop_BCal";
  else if (!vbf_selected) {
    if ( (NonResonantCategory/1000) %10 == 1)
      string_category="XGBoost_btag77_withTop_BCal_tightScore_HMass";
    else if ( (NonResonantCategory/1000) %10 == 2)
      string_category="XGBoost_btag77_withTop_BCal_looseScore_HMass";
    else if ( (NonResonantCategory/1000) %10 == 3)
      string_category="XGBoost_btag77_withTop_BCal_tightScore_LMass";
    else if ( (NonResonantCategory/1000) %10 == 4)
      string_category="XGBoost_btag77_withTop_BCal_looseScore_LMass";
  }
  */

  return string_category;

  //"XGBoost_btag77_withTop_BCal_tightScore_HMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_BCal_vbf_selected == 0 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 1))   ",
  //"XGBoost_btag77_withTop_BCal_looseScore_HMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_BCal_vbf_selected == 0 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 2))   ",
  //"XGBoost_btag77_withTop_BCal_tightScore_LMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_BCal_vbf_selected == 0 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 3))   ",
  //"XGBoost_btag77_withTop_BCal_looseScore_LMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_BCal_vbf_selected == 0 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 4))   ",
  //"VBF_btag77_withTop_BCal" 	: "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000)  % 10) != 9) && (HGamEventInfoAuxDyn.yybb_btag77_BCal_vbf_selected == 1)  )"
}

//#######################################################################################################################################################################################################
int tool_Experimental_Systematics::ReturnIndexCategory(string string_category)
{
  unsigned int index_category=0;
  
  for (;index_category<vec_string_category.size();index_category++) {
    if (string_category==vec_string_category[index_category])
      break;
  }
  
  if (index_category<vec_string_category.size())
    return index_category;
  
  return -1;
}
//#######################################################################################################################################################################################################
bool tool_Experimental_Systematics::IsPassResonant(int mX)
{
  //BDT h026
  
  double score_yy=m_HGamEventInfo->auxdata<float>("yybb_Res_BDT_BCal_yy_Score");
  double score_ttH=m_HGamEventInfo->auxdata<float>("yybb_Res_BDT_BCal_ttH_Score");
  //------------------
  //example 300 GeV : (HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((298.248-2*6.80417)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((298.248+2*6.80417)*1000))",
  
  double c1=-1;
  
  double mean_resonance=0;
  double rms_resonance=0;
  
  double cut_combined_score=99999;
  //latest with h026 reoptimized with good variable

  if (mX==251) {
    c1=0.65;

    mean_resonance=249.075;
    rms_resonance=3.47843;
    
    cut_combined_score=0.70;
  }
  else if (mX==260) {
    c1=0.65;

    mean_resonance=260.012;
    rms_resonance=3.13066;
    
    cut_combined_score=0.75;
  }
  else if (mX==280) {
    c1=0.65;

    mean_resonance=279.201;
    rms_resonance=5.04804;
    
    cut_combined_score=0.85;
  }
  else if (mX==300) {
    c1=0.65;
    
    mean_resonance=298.577;
    rms_resonance=6.70871;
    
    cut_combined_score=0.85;
  }
  else if (mX==325) {
    c1=0.65;
    
    mean_resonance=323.806;
    rms_resonance=7.449;
    
    cut_combined_score=0.85;
  }
  else if (mX==350) {
    c1=0.65;
    
    mean_resonance=348.32;
    rms_resonance=8.66209;
    
    cut_combined_score=0.85;
  }
  else if (mX==400) {
    c1=0.65;
    
    mean_resonance=397.394;
    rms_resonance=10.719;
    
    cut_combined_score=0.80;
  }
  else if (mX==450) {
    c1=0.65;
    
    mean_resonance=446.732;
    rms_resonance=12.4305;
    
    cut_combined_score=0.85;
  }
  else if (mX==500) {
    c1=0.65;
    
    mean_resonance=495.738;
    rms_resonance=14.1286;
    
    cut_combined_score=0.75;
  }
  else if (mX==550) {
    c1=0.65;
    
    mean_resonance=544.868;
    rms_resonance=15.6412;
    
    cut_combined_score=0.60;
  }
  else if (mX==600) {
    c1=0.65;
    
    mean_resonance=594.493;
    rms_resonance=16.6684;
    
    cut_combined_score=0.45;
  }
  else if (mX==700) {
    c1=0.65;
    
    mean_resonance=693.149;
    rms_resonance=18.8885;
    
    cut_combined_score=0.2;
  }
  else if (mX==800) {
    c1=0.65;
    
    mean_resonance=790.638;
    rms_resonance=21.3055;
    
    cut_combined_score=0.1;
  }
  else if (mX==900) {
    c1=0.65;
    
    mean_resonance=888.031;
    rms_resonance=23.4402;
    
    cut_combined_score=0.20;
  }
  else if (mX==1000) {
    c1=0.65;
    
    mean_resonance=983.98;
    rms_resonance=26.4073;
    
    cut_combined_score=0.05;
  }
  else {
    cout << "problem, mX not anticipated, halt program" << endl;
    exit(1);
  }
  //------------------
  if (c1<0) {
    cout << "problem, negative c1, halt program" << endl;
    exit(1);
  }
  
  double c2=1.-c1;
  
  int coef_rms=2.;
  
  if (mX==900 || mX==1000)
    coef_rms=4.;
  
  //Mean+4 for 1 TeV

  /*already done, else if really persist, change the variable name
  //h026
  int variable_yybb_cutflow=m_HGamEventInfo->auxdata<int>("yybb_btag77_BCal_cutFlow");
  //new name sure : yybb_btag77_cutFlow

  //  if (variable_yybb_cutflow!=6)
  if (variable_yybb_cutflow!=7)
    return 0;
  */

  //  int nb_jets=m_HGamEventInfo->auxdata<int>("N_j_central");
  
  //for new production : sure
  //  if (nb_jets>=2 && variable_cutflow==7
  
  /*replaced
  //  if (nb_jets>=2 && variable_cutflow==6
      &&
      (1./sqrt(pow(c1,2)+pow(c2,2)))*sqrt(pow(c1,2)*pow((score_yy+1)/2,2)+pow(c2,2)*pow((score_ttH+1)/2,2))>cut_combined_score
      &&
      m_m_yybb_tilde>mean_resonance-coef_rms*rms_resonance && m_m_yybb_tilde<mean_resonance+coef_rms*rms_resonance)
    return 1;
  */

  if ( ! (m_m_yybb_tilde>=mean_resonance-coef_rms*rms_resonance && m_m_yybb_tilde<=mean_resonance+coef_rms*rms_resonance) )
    return 0;

  double combined_score=(1./sqrt(pow(c1,2)+pow(c2,2)))*sqrt(pow(c1,2)*pow((score_yy+1)/2,2)+pow(c2,2)*pow((score_ttH+1)/2,2));
  
  //  cout << "eventNumber=" << m_eventNumber << ", c1=" << c1 << ", score_yy=" << score_yy << ", score_ttH=" << score_ttH << ", combined_score=" << combined_score << ", cut_combined_score=" << cut_combined_score << endl;
  
  if (! (combined_score>cut_combined_score))
    return 0;

  return 1;
}
//#######################################################################################################################################################################################################
void tool_Experimental_Systematics::FillAdditionalHist(string string_sys_additional_translated)
{
  for (unsigned int index_category=0;index_category<nb_categories_tool_exp_syst;index_category++) {
    map_hist_nb_sel_f_categ[index_category][string_sys_additional_translated]->SetBinContent(1,map_nb_sel_f_categ_sys[index_category]["nominal"]);
    map_hist_nb_sel_f_categ[index_category][string_sys_additional_translated]->SetBinError(1,map_err_nb_sel_f_categ_sys[index_category]["nominal"]);
    
    map_hist_nb_sel_uncommon_part_nominal_f_categ[index_category][string_sys_additional_translated]->SetBinContent(1,map_nb_sel_f_categ_sys_uncommon_part_nominal[index_category]["nominal"]);
    map_hist_nb_sel_uncommon_part_nominal_f_categ[index_category][string_sys_additional_translated]->SetBinError(1,map_err_nb_sel_f_categ_sys_uncommon_part_nominal[index_category]["nominal"]);
    
    map_hist_nb_sel_common_part_nominal_f_categ[index_category][string_sys_additional_translated]->SetBinContent(1,map_nb_sel_f_categ_sys_common_part_nominal[index_category]["nominal"]);
    map_hist_nb_sel_common_part_nominal_f_categ[index_category][string_sys_additional_translated]->SetBinError(1,map_err_nb_sel_f_categ_sys_common_part_nominal[index_category]["nominal"]);
    
    map_hist_nb_sel_uncommon_part_sys_f_categ[index_category][string_sys_additional_translated]->SetBinContent(1,map_nb_sel_f_categ_sys_uncommon_part_sys[index_category]["nominal"]);
    map_hist_nb_sel_uncommon_part_sys_f_categ[index_category][string_sys_additional_translated]->SetBinError(1,map_err_nb_sel_f_categ_sys_uncommon_part_sys[index_category]["nominal"]);
    
    map_hist_nb_sel_f_categ_unweighted[index_category][string_sys_additional_translated]->SetBinContent(1,map_nb_sel_f_categ_sys_unweighted[index_category]["nominal"]);
    map_hist_nb_sel_f_categ_unweighted[index_category][string_sys_additional_translated]->SetBinError(1,map_err_nb_sel_f_categ_sys_unweighted[index_category]["nominal"]);
    
    map_hist_nb_sel_uncommon_part_nominal_f_categ_unweighted[index_category][string_sys_additional_translated]->SetBinContent(1,map_nb_sel_f_categ_sys_uncommon_part_nominal_unweighted[index_category]["nominal"]);
    map_hist_nb_sel_uncommon_part_nominal_f_categ_unweighted[index_category][string_sys_additional_translated]->SetBinError(1,map_err_nb_sel_f_categ_sys_uncommon_part_nominal_unweighted[index_category]["nominal"]);
    
    map_hist_nb_sel_uncommon_part_sys_f_categ_unweighted[index_category][string_sys_additional_translated]->SetBinContent(1,map_nb_sel_f_categ_sys_uncommon_part_sys_unweighted[index_category]["nominal"]);
    map_hist_nb_sel_uncommon_part_sys_f_categ_unweighted[index_category][string_sys_additional_translated]->SetBinError(1,map_err_nb_sel_f_categ_sys_uncommon_part_sys_unweighted[index_category]["nominal"]);


    int nb_entries=map_tree_sel_f_categ[index_category]["nominal"]->GetEntries();
    
    for (int index_entry=0;index_entry<nb_entries;index_entry++) {
      map_tree_sel_f_categ[index_category]["nominal"]->GetEntry(index_entry);
      
      map_tree_sel_f_categ[index_category][string_sys_additional_translated]->Fill();
    } //end loop on entries
  
  }     //end loop on categories
}
//#######################################################################################################################################################################################################
void tool_Experimental_Systematics::FillListCategories()
{
  //HH non resonant baseline
  if (sampleName.find("_X")==string::npos) { //sample is not a resonant sample, so either a HH non resonant or a single Higgs
    
    //so consider to include the non resonant categories
    
    //      vec_string_category.push_back("Inclusive_HH_NonResonant");

    //h026
    vec_string_category.push_back("XGBoost_btag77_withTop_BCal_tightScore_HMass");
    vec_string_category.push_back("XGBoost_btag77_withTop_BCal_looseScore_HMass");
    vec_string_category.push_back("XGBoost_btag77_withTop_BCal_tightScore_LMass");
    vec_string_category.push_back("XGBoost_btag77_withTop_BCal_looseScore_LMass");

    //    vec_string_category.push_back("VBF_btag77_withTop_BCal");
  }
  
  //HH resonant baseline

  //should consider it also for HH non resonant in resonant category
  
  if (1) {

    //so consider to include the resonant categories

    /*    
    bool is_single_Higgs=0;
    if (sampleName.find("ggH125")!=string::npos
	||
	sampleName.find("ZH125")!=string::npos
	||
	sampleName.find("ttH125")!=string::npos
	)
      is_single_Higgs=1;
    */

    bool is_Resonant_sample=0;
    if (sampleName.find("MGH7_X")!=string::npos)
      is_Resonant_sample=1;

    for (unsigned int index_mX=0;index_mX<vec_mX_exp_systematics.size();index_mX++) {
      
      string string_resonance="X"+to_string(vec_mX_exp_systematics[index_mX]);
      cout << "string_resonance=" << string_resonance << endl;

      //should consider it also for HH non resonant in resonant category

      if (!is_Resonant_sample
	  ||
	  (is_Resonant_sample && sampleName.find(string_resonance.c_str())!=string::npos)
	  ) {
	vec_string_category.push_back("Resonant_mX"+to_string(vec_mX_exp_systematics[index_mX]));
	
	cout << "adding category Resonant_mX"+to_string(vec_mX_exp_systematics[index_mX]) << endl;
      }
      /*shit
      if (1) {
	vec_string_category.push_back("Resonant_mX"+to_string(vec_mX_exp_systematics[index_mX]));
	cout << "adding category Resonant_mX"+to_string(vec_mX_exp_systematics[index_mX]) << endl;
      }
      */
      
    } //end loop on mX
  } //end case resonant
}
//#######################################################################################################################################################################################################
void tool_Experimental_Systematics::FillListVariations() //this include the nominal
{
  //establish list of systematics
  for (CP::SystematicSet sys:getSystematics()) { //this order is the most powerful, because it is the slowest part
    
    string string_sys=sys.name();
    
    //shit for sure : delete if works
    //shit    if (string_sys=="") //nominal does not belong to list of systematics
    //shit      continue;
    
    if (ProtectAgainstFakeSystematic(string_sys))
      continue;
    
    string string_HGamEventInfo="HGamEventInfo";
    if (string_sys!="") {
      string_HGamEventInfo+="_";
      string_HGamEventInfo+=string_sys;
    }

    m_HGamEventInfo=0;    
    
    event()->retrieve(m_HGamEventInfo,string_HGamEventInfo.c_str());
    
    if (!m_HGamEventInfo)
      continue;
    
    //create the additional systematics, missing, in order to avoid a problem when merging files of results

    vector<string> vec_strings_to_add_variante_if_present={"JET_JER_DataVsMC","JET_PunchThrough"};
    
    for (unsigned int index_to_add_variante_if_present=0;index_to_add_variante_if_present<vec_strings_to_add_variante_if_present.size();index_to_add_variante_if_present++) {

      /*
      cout << "-----" << endl;
      cout << "check for " << vec_strings_to_add_variante_if_present[index_to_add_variante_if_present] << endl;
      cout << "while string_sys=" << string_sys << endl;
      */
      size_t position_string=string_sys.find(vec_strings_to_add_variante_if_present[index_to_add_variante_if_present].c_str());
      /*      
      cout << "position_string=" << position_string << endl;
      cout << "string::npos=" << string::npos << endl;
      */
      if (position_string!=string::npos) {
	string string_sys_additional=string_sys;
	
	position_string=string_sys.find("AFII");
	if (position_string!=string::npos)
	  string_sys_additional.replace(position_string,4,"MC16");
	else {
	  position_string=string_sys.find("MC16");
	  string_sys_additional.replace(position_string,4,"AFII");
	}

	string string_sys_additional_translated=Translate_current_variation(string_sys_additional);
	
	//	cout << "string_sys_additional=" << string_sys_additional << ", string_sys_additional_translated=" << string_sys_additional_translated << endl;
	
	//	if (string_sys_additional_translated!="nominal")
	m_variations_translated.push_back(string_sys_additional_translated);
      }
    } //and loop on cases to consider for adding a variante (apart JET_RelativeNonClosure, which is treated after since special case)

    string string_variation_translated=Translate_current_variation(string_sys);
    
    //    cout << "string_sys=" << string_sys << ", string_variation_translated=" << string_variation_translated << endl;

    m_variations_translated.push_back(string_variation_translated);
    
  } //end loop on systematics
  
  if (ReturnSubDirectoryWhereToStore(sampleName)=="JetSys2") {
    
    //    m_HGamEventInfo=0;    
    //other approach
    //event()->retrieve(m_HGamEventInfo,"HGamEventInfo_JET_RelativeNonClosure_AFII__1up");
    //problem    event()->contains(std::string("HGamEventInfo_JET_RelativeNonClosure_AFII__1up"));
    //    if (!m_HGamEventInfo) {
    
    if (!event()->contains<xAOD::EventInfo>(string("HGamEventInfo_JET_RelativeNonClosure_AFII__1up"))) {
      cout << "JET_RelativeNonClosure_AFII does not exist, so add it" << endl;
      m_variations_translated.push_back("JET_RelativeNonClosure_AFII__1up");
      m_variations_translated.push_back("JET_RelativeNonClosure_AFII__1down");
    }
  }
}
//#######################################################################################################################################################################################################


//#######################################################################################################################################################################################################
EL::StatusCode tool_Experimental_Systematics::histFinalize()
{
  // This method is the mirror image of histInitialize(), meaning it
  // gets called after the last event has been processed on the worker
  // node and allows you to finish up any objects you created in
  // histInitialize() before they are written to disk.  This is
  // actually fairly rare, since this happens separately for each
  // worker node.  Most of the time you want to do your
  // post-processing on the submission node after all your histogram
  // outputs have been merged.  This is different from finalize() in
  // that it gets called on all worker nodes regardless of whether
  // they processed input events.
  
  cout << "tool_Experimental_Systematics::histFinalize" << endl;
  
  return EL::StatusCode::SUCCESS;
}
//#######################################################################################################################################################################################################
EL::StatusCode tool_Experimental_Systematics::finalize()
{
  cout << "tool_Experimental_Systematics::finalize" << endl;
  
  //put at the end, else we loose the objects that are needed
  HgammaAnalysis::finalize(); // keep this line!
  //--------------------------------------------------
  //information on common, uncommon, etc.

  cout << "===================================================" << endl;
  cout << "===================================================" << endl;
  cout << "===================================================" << endl;
  cout << "===================================================" << endl;
  cout << "===================================================" << endl;
  cout << "===================================================" << endl;
  cout << "===================================================" << endl;
  cout << "===================================================" << endl;

  //--------------------------------------------------
  // Manage the sqrt of err

  cout << "manage the sqrt of err" << endl;

  //done in two independent steps with respect to previous treatment, in order to be able, if necessary, to make computations of pull, relative to the nominal performance (no syst.) so on needs to have first the appropriate error on the yields, with applying sqrt

  //add sqrt for err of variations and of the common/uncommon : sure : no double counting
  
  for (auto sys:getSystematics()) {

    string string_sys=sys.name();

    //shit for sure
    //    if (string_sys=="")
    //      continue;
    
    if (ProtectAgainstFakeSystematic(string_sys))
      continue;
    
    string string_current_variation=Translate_current_variation(string_sys);

    for (unsigned int index_category=0;index_category<nb_categories_tool_exp_syst;index_category++) {
      map_err_nb_sel_f_categ_sys[index_category][string_current_variation]=sqrt(map_err_nb_sel_f_categ_sys[index_category][string_current_variation]);
      //-------------------
      //for the treatment with correlations
      
      if (string_current_variation!="nominal") {
	map_err_nb_sel_f_categ_sys_common_part_nominal[index_category][string_current_variation]=sqrt(map_err_nb_sel_f_categ_sys_common_part_nominal[index_category][string_current_variation]);
	
	//next : not used
	//map_err_nb_sel_f_categ_sys_common_part_sys[index_category][string_current_variation]=sqrt(map_err_nb_sel_f_categ_sys_common_part_sys[index_category][string_current_variation]);
	
	map_err_nb_sel_f_categ_sys_uncommon_part_nominal[index_category][string_current_variation]=sqrt(map_err_nb_sel_f_categ_sys_uncommon_part_nominal[index_category][string_current_variation]);
	map_err_nb_sel_f_categ_sys_uncommon_part_sys[index_category][string_current_variation]=sqrt(map_err_nb_sel_f_categ_sys_uncommon_part_sys[index_category][string_current_variation]);
      }
    } //end loop on categories

  } //end loop on systematics
  //----------

  //systematics results of yields
  
  /*
  cout << "==================================================================" << endl;
  cout << "==================================================================" << endl;
  cout << "==================================================================" << endl;
  cout << "==================================================================" << endl;
  cout << "==================================================================" << endl;
  */

  cout << "nb_categories_tool_exp_syst=" << nb_categories_tool_exp_syst << endl;

  for (unsigned int index_category=0;index_category<nb_categories_tool_exp_syst;index_category++) {
    
    cout << "index_category=" << index_category << endl;
    
    /*shit for sure if stable
    map_hist_nb_sel_f_categ[index_category]["nominal"]->SetBinContent(1,map_nb_sel_f_categ_sys[index_category]["nominal"]);
    map_hist_nb_sel_f_categ[index_category]["nominal"]->SetBinError(1,map_err_nb_sel_f_categ_sys[index_category]["nominal"]);
    
    map_hist_nb_sel_f_categ_unweighted[index_category]["nominal"]->SetBinContent(1,map_nb_sel_f_categ_sys_unweighted[index_category]["nominal"]);
    map_hist_nb_sel_f_categ_unweighted[index_category]["nominal"]->SetBinError(1,map_err_nb_sel_f_categ_sys_unweighted[index_category]["nominal"]);
    */
    for (CP::SystematicSet sys:getSystematics()) {
      
      cout << "=============================================================================" << endl;
      
      string string_sys=sys.name();

      //      cout << "string_sys=" << string_sys << endl;
      //shit for sure
      //      if (string_sys=="")
      //	continue;
      
      if (ProtectAgainstFakeSystematic(string_sys))
	continue;
      
      //we do everything related to nominal
      
      char buffer_index_category[50];
      
      //this could improved with pointer, if needed
      
      string string_variation_translated=Translate_current_variation(string_sys);
      
      // 	cout << "string_MxAOD_mc_campaign=" << string_MxAOD_mc_campaign.c_str() << endl;
      // 	cout << "string_sysype_sample=" << string_sysype_sample.c_str() << endl;
      // 	cout << "sampleName=" << sampleName.c_str() << endl;
      // 	cout << "position_underscore=" << position_underscore << endl;
      // 	cout << "Process_name=" << Process_name.c_str() << endl;
      
      // 	cout << "string_file=" << string_file.c_str() << endl;
      
      /*
	map_rel_effect_sel_f_categ_sys[index_category][string_variation_translated]=100.*(map_nb_sel_f_categ_sys[index_category][string_variation_translated]-map_nb_sel_f_categ_sys[index_category]["nominal"])/map_nb_sel_f_categ_sys[index_category]["nominal"];
      
      cout << "===============" << endl;
      
      cout << "map_rel_effect_sel_f_categ_sys[index_category][string_variation_translated]=" << map_rel_effect_sel_f_categ_sys[index_category][string_variation_translated] << endl;
      cout << "map_nb_sel_f_categ_sys[index_category][string_variation_translated]=" << map_nb_sel_f_categ_sys[index_category][string_variation_translated] << endl;
      cout << "map_nb_sel_f_categ_sys[index_category][nominal]=" << map_nb_sel_f_categ_sys[index_category]["nominal"] << endl;
      */

      //double nb_sel_nominal
      //double nb_sel_uncommon_part_nominal
      //double nb_sel_uncommon_part_sys
      
      //double err_nb_sel_common_part_nominal
      //double err_nb_sel_uncommon_part_nominal
      //double err_nb_sel_uncommon_part_sys
      
      // to improve with the two formulas
      
      int correlation_full1_partial2=0;
      
      //cout << "map_nb_sel_f_categ_sys_uncommon_part_nominal_unweighted[index_category][string_variation_translated]=" << map_nb_sel_f_categ_sys_uncommon_part_nominal_unweighted[index_category][string_variation_translated] << endl;
      //      cout << "map_nb_sel_f_categ_sys_uncommon_part_sys_unweighted[index_category][string_variation_translated]=" << map_nb_sel_f_categ_sys_uncommon_part_sys_unweighted[index_category][string_variation_translated] << endl;
      
      if (map_nb_sel_f_categ_sys_uncommon_part_nominal_unweighted[index_category][string_variation_translated]==0 && map_nb_sel_f_categ_sys_uncommon_part_sys_unweighted[index_category][string_variation_translated]==0 && map_nb_sel_f_categ_sys_unweighted[index_category]["nominal"]==map_nb_sel_f_categ_sys_unweighted[index_category][string_variation_translated] && 
	  fabs((map_nb_sel_f_categ_sys[index_category][string_variation_translated]-map_nb_sel_f_categ_sys[index_category]["nominal"])/map_nb_sel_f_categ_sys[index_category]["nominal"])>1.e-4) { //same yield unweighted but different yield weighted ; do not put lower than 1.e-4 because rounding effect : some same values have discrepencies of 1.5e-5 because of rounding in the representation
	//case fully correlated : uncommon unweighted yields are null, unweighted yields are equal and weighted yields have a non-negligeable effect [!= numerical rounding effect]
	
	correlation_full1_partial2=1;
      }

      else {
	correlation_full1_partial2=2;
      }

      if (correlation_full1_partial2==2) {
	map_err_rel_effect_sel_f_categ_sys[index_category][string_variation_translated]=get_err_rel_effect_yield_partially_correlated(map_nb_sel_f_categ_sys[index_category]["nominal"],
																   map_nb_sel_f_categ_sys_common_part_nominal[index_category][string_variation_translated],
																   map_nb_sel_f_categ_sys_uncommon_part_nominal[index_category][string_variation_translated],
																   map_nb_sel_f_categ_sys_uncommon_part_sys[index_category][string_variation_translated],
																   map_err_nb_sel_f_categ_sys_common_part_nominal[index_category][string_variation_translated],
																   map_err_nb_sel_f_categ_sys_uncommon_part_nominal[index_category][string_variation_translated],
																   map_err_nb_sel_f_categ_sys_uncommon_part_sys[index_category][string_variation_translated]);
	
      }
      else if (correlation_full1_partial2==1) {
	map_err_rel_effect_sel_f_categ_sys[index_category][string_variation_translated]=get_err_rel_effect_yield_fully_correlated(map_nb_sel_f_categ_sys[index_category]["nominal"],
															       map_nb_sel_f_categ_sys[index_category][string_variation_translated],
															       map_err_nb_sel_f_categ_sys[index_category]["nominal"],
															       map_err_nb_sel_f_categ_sys[index_category][string_variation_translated]);
      }
            
      sprintf(buffer_index_category,"%s",vec_string_category[index_category].c_str());
      //-----
      //develop
      /*moved !!
//shit if ok
      map_hist_nb_sel_f_categ[index_category]["nominal"]->SetBinContent(1,map_nb_sel_f_categ_sys[index_category]["nominal"]);
      map_hist_nb_sel_f_categ[index_category]["nominal"]->SetBinError(1,map_err_nb_sel_f_categ_sys[index_category]["nominal"]);
      */

      map_hist_nb_sel_f_categ[index_category][string_variation_translated]->SetBinContent(1,map_nb_sel_f_categ_sys[index_category][string_variation_translated]);
      map_hist_nb_sel_f_categ[index_category][string_variation_translated]->SetBinError(1,map_err_nb_sel_f_categ_sys[index_category][string_variation_translated]);

      map_hist_nb_sel_f_categ_unweighted[index_category][string_variation_translated]->SetBinContent(1,map_nb_sel_f_categ_sys_unweighted[index_category][string_variation_translated]);
      map_hist_nb_sel_f_categ_unweighted[index_category][string_variation_translated]->SetBinError(1,map_err_nb_sel_f_categ_sys_unweighted[index_category][string_variation_translated]);
      
      if (string_variation_translated!="nominal") {
	map_hist_nb_sel_uncommon_part_nominal_f_categ[index_category][string_variation_translated]->SetBinContent(1,map_nb_sel_f_categ_sys_uncommon_part_nominal[index_category][string_variation_translated]);
	map_hist_nb_sel_uncommon_part_nominal_f_categ[index_category][string_variation_translated]->SetBinError(1,map_err_nb_sel_f_categ_sys_uncommon_part_nominal[index_category][string_variation_translated]);
	
	map_hist_nb_sel_common_part_nominal_f_categ[index_category][string_variation_translated]->SetBinContent(1,map_nb_sel_f_categ_sys_common_part_nominal[index_category][string_variation_translated]);
	map_hist_nb_sel_common_part_nominal_f_categ[index_category][string_variation_translated]->SetBinError(1,map_err_nb_sel_f_categ_sys_common_part_nominal[index_category][string_variation_translated]);
	
	map_hist_nb_sel_uncommon_part_sys_f_categ[index_category][string_variation_translated]->SetBinContent(1,map_nb_sel_f_categ_sys_uncommon_part_sys[index_category][string_variation_translated]);
	map_hist_nb_sel_uncommon_part_sys_f_categ[index_category][string_variation_translated]->SetBinError(1,map_err_nb_sel_f_categ_sys_uncommon_part_sys[index_category][string_variation_translated]);
	
	map_hist_nb_sel_uncommon_part_nominal_f_categ_unweighted[index_category][string_variation_translated]->SetBinContent(1,map_nb_sel_f_categ_sys_uncommon_part_nominal_unweighted[index_category][string_variation_translated]);
	map_hist_nb_sel_uncommon_part_nominal_f_categ_unweighted[index_category][string_variation_translated]->SetBinError(1,map_err_nb_sel_f_categ_sys_uncommon_part_nominal_unweighted[index_category][string_variation_translated]);
	
	map_hist_nb_sel_uncommon_part_sys_f_categ_unweighted[index_category][string_variation_translated]->SetBinContent(1,map_nb_sel_f_categ_sys_uncommon_part_sys_unweighted[index_category][string_variation_translated]);
	map_hist_nb_sel_uncommon_part_sys_f_categ_unweighted[index_category][string_variation_translated]->SetBinError(1,map_err_nb_sel_f_categ_sys_uncommon_part_sys_unweighted[index_category][string_variation_translated]);
      }
      
      /*shit if ok
	moved !!
	map_hist_nb_sel_f_categ_unweighted[index_category]["nominal"]->SetBinContent(1,map_nb_sel_f_categ_sys_unweighted[index_category]["nominal"]);
	map_hist_nb_sel_f_categ_unweighted[index_category]["nominal"]->SetBinError(1,map_err_nb_sel_f_categ_sys_unweighted[index_category]["nominal"]);
      */
      
      //---
      //      printf("index_category=%d, %s, %s \t %4.2f +/- %4.2f\n",index_category,vec_string_category[index_category].c_str(),string_variation_translated.c_str(),map_rel_effect_sel_f_categ_sys[index_category][string_variation_translated],map_err_rel_effect_sel_f_categ_sys[index_category][string_variation_translated]);
      
      //obsolete if stable      file_syst_yield->Close();
      
    }     //end loop on categories
    
  } //end loop on systematics
  
  cout << "Finalize, fill the additional" << endl;
  //============================================
  //============================================
  //Fill the additional
  
  for (unsigned int index_sys=0;index_sys<m_variations_translated.size();index_sys++) {
    
    string string_variation_translated=m_variations_translated[index_sys];
    
    vector<string> vec_strings_to_add_variante_if_present={"JET_JER_DataVsMC","JET_PunchThrough"};
    
    for (unsigned int index_to_add_variante_if_present=0;index_to_add_variante_if_present<vec_strings_to_add_variante_if_present.size();index_to_add_variante_if_present++) {
      size_t position_string=string_variation_translated.find(vec_strings_to_add_variante_if_present[index_to_add_variante_if_present].c_str());
      
      if (position_string!=string::npos) {
	string string_sys_additional_translated=string_variation_translated;
	
	position_string=string_variation_translated.find("AFII");
	if (position_string!=string::npos)
	  string_sys_additional_translated.replace(position_string,4,"MC16");
	else {
	  position_string=string_variation_translated.find("MC16");
	  string_sys_additional_translated.replace(position_string,4,"AFII");
	}
	
	//	cout << "Fill information for " << string_sys_additional_translated << endl;
	FillAdditionalHist(string_sys_additional_translated);
      } //end case additional systematic to add
    } //and loop on cases to consider for adding a variante (apart JET_RelativeNonClosure, which is treated after since special case)
  } //end loop on sys

  cout << "ReturnSubDirectoryWhereToStore(sampleName)=" << ReturnSubDirectoryWhereToStore(sampleName) << endl;

  if (ReturnSubDirectoryWhereToStore(sampleName)=="JetSys2") {
    
    cout << "this is indeed JetSys2" << endl;

    unsigned int index_sys=0;
    
    for (;index_sys<m_variations_translated.size();index_sys++) {
      
      string string_variation_translated=m_variations_translated[index_sys];
      
      if (string_variation_translated=="JET_RelativeNonClosure_AFII__1up")
	break;
    }
    
    if (index_sys<m_variations_translated.size()) {
      vector<string> vec_strings_to_add_variante_if_present={"JET_RelativeNonClosure_AFII__1up","JET_RelativeNonClosure_AFII__1down"};
      
      for (unsigned int index_to_add_variante_if_present=0;index_to_add_variante_if_present<vec_strings_to_add_variante_if_present.size();index_to_add_variante_if_present++) {
	
	string string_sys_additional_translated=vec_strings_to_add_variante_if_present[index_to_add_variante_if_present];
	
	cout << "call FillAdditionalHist for " << string_sys_additional_translated << endl;
	FillAdditionalHist(string_sys_additional_translated);
	
      } //and loop on additional
    } //end case to add systematic
  } //end case JetSys2
  //================================================
  cout << "Write trees for shape" << endl;

  file_syst_shape->cd();
  
  for (unsigned int index_category=0;index_category<nb_categories_tool_exp_syst;index_category++) {
    
    //shit if ok now included    map_tree_sel_f_categ[index_category]["nominal"]->Write();
    
    for (unsigned int index_sys=0;index_sys<m_variations_translated.size();index_sys++) {
      
      string string_current_variation=m_variations_translated[index_sys];
      
      map_tree_sel_f_categ[index_category][string_current_variation]->Write();
    }
  }
  //================================================
  cout << "will write histograms for yields" << endl;
  for (unsigned int index_category=0;index_category<nb_categories_tool_exp_syst;index_category++) {
    
    /*not useful since already done below
      map_hist_nb_sel_f_categ[index_category]["nominal"]->Write();  
      map_hist_nb_sel_f_categ_unweighted[index_category]["nominal"]->Write();
    */
    
    for (unsigned int index_sys=0;index_sys<m_variations_translated.size();index_sys++) {
      
      string string_variation_translated=m_variations_translated[index_sys];
      
      map_hist_nb_sel_f_categ[index_category][string_variation_translated]->Write();

      if (string_variation_translated!="nominal") {
	map_hist_nb_sel_uncommon_part_nominal_f_categ[index_category][string_variation_translated]->Write();
	map_hist_nb_sel_common_part_nominal_f_categ[index_category][string_variation_translated]->Write();
	map_hist_nb_sel_uncommon_part_sys_f_categ[index_category][string_variation_translated]->Write();
      }
      
      map_hist_nb_sel_f_categ_unweighted[index_category][string_variation_translated]->Write();
      if (string_variation_translated!="nominal") {
	map_hist_nb_sel_uncommon_part_nominal_f_categ_unweighted[index_category][string_variation_translated]->Write();
	map_hist_nb_sel_uncommon_part_sys_f_categ_unweighted[index_category][string_variation_translated]->Write();
      }
    } //end loop on syst
  }
  //================================================  
  file_syst_shape->Close();

  return EL::StatusCode::SUCCESS;
}
//#######################################################################################################################################################################################################
    /* //just in case it would be needed for resonant analysis
    //----------------------------------
    //jets
    
    cout << "read jets container" << endl;
    
    m_allJets=jetHandler()->getCorrectedContainer();
    
    if (flag_tool_Experimental_Systematics_IsThisMxAOD) {
    //traditionnal
      
      if ( event()->retrieve(ptr_const_jets,"HGamAntiKt4EMTopoJets").isFailure())
      
      HG::fatal("Cannot access jets");
      //HH jets
      //if ( event()->retrieve(ptr_const_jets,"yybbAntiKt4EMTopoJets_discreteMV2c10pT").isFailure() )
      
      //HG::fatal("Cannot access jets");
      
      m_selJets=*((xAOD::JetContainer *)ptr_const_jets);
    }
    else {  //for DxAOD
      m_allJets=jetHandler()->getCorrectedContainer();
      m_selJets=jetHandler()->applySelection(m_allJets);
    }
    
    //  m_allJets=jetHandler()->getCorrectedContainer();
    //  m_selJets=jetHandler()->applySelection(m_allJets);
    
    //      if (m_selJets.size()<=0)
    //      return EL::StatusCode::SUCCESS;
    */

  /*
    yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn.MV2c10bin
    4<=>pass 60 %
    3<=>pass 70 %
    2<=>pass 77 %
    1<=>pass 85 %
    0<=>fail b tagging
  */

  //baseline from Alan : N85 % b tags >=2 and m_bb in 90-140 GeV, and m_gamgam in 120-130 and N_70 % b_tags=2 OR N_85 % b-tags=2


  /*alternative approach, a la Jean-Baptiste

    const CP::SystematicRegistry &registry = CP::SystematicRegistry::getInstance();
  std::vector<CP::SystematicSet> tempList = CP::make_systematics_vector(registry.recommendedSystematics());
  for (auto sys : tempList)
    Info("","From all syst, sys = %s",sys.name().c_str());

  std::vector<std::string> usys0{"JET_RelativeNonClosure_AFII"};
  std::vector<std::string> usys1{""};
  CP::SystematicSet aDummySys0(usys0);
  CP::SystematicSet aDummySys1(usys1);
  Info("","is sys %s available %d",usys0[0].c_str(),isSystematicAvailable(aDummySys0));
  Info("","is sys %s available %d",usys1[0].c_str(),isSystematicAvailable(aDummySys1));
  */
//#######################################################################################################################################################################################################
  //bool isPassed_preselection=m_HGamEventInfo->auxdata<char>("isPassedPreselection");
  
  //    eventHandler()->storeVar<char>("isPassedPreselection", Nloose >= 2);
  

//(not useful)trick of Linghua for big files : TTree::SetMaxTreeSize( 1000000000000LL )



//TRASH
  //to delete this block if ok
  /*moved in treatment with various systematics, starting from h026 updated MxAOD syst  
  pass_preselection_2_bjets=0;

  if (do_h026_Experimental_systematics) {
    
    if (do_preselection_by_hand_Experimental_systematics) {
      
      int Nbjets=0;
      
      if ( event()->retrieve(ptr_const_jets,"HGamAntiKt4PFlowCustomVtxHggJets").isFailure() )
	HG::fatal("Cannot access jets for full collection");

      int nb_jets=ptr_const_jets->size();
      
      static SG::AuxElement::Accessor<char> acc_DL1r_FixedCutBEff_77("DL1r_FixedCutBEff_77");
      
      for (int index_jet=0;index_jet<nb_jets;index_jet++) {
	const xAOD::Jet *current_jet=(*ptr_const_jets)[index_jet];
	//      for (int i=0; i<HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn_eta.GetSize(); i++){
	if (acc_DL1r_FixedCutBEff_77(*current_jet))
	  Nbjets++;
      }
      
      if (Nbjets==2)
	pass_preselection_2_bjets=1;
    }
    else {
      if ( event()->retrieve(ptr_const_jets,"HGamAntiKt4PFlowCustomVtxHggJets").isFailure() )
	HG::fatal("Cannot access jets for full collection");

      int index_jet1_fix=m_HGamEventInfo->auxdata<int>("yybb_candidate_jet1_fix");      
      int index_jet2_fix=m_HGamEventInfo->auxdata<int>("yybb_candidate_jet2_fix");
      
      if (index_jet1_fix>=0 && index_jet2_fix>=0) {
	const xAOD::Jet *jet1_fixed=(*ptr_const_jets)[index_jet1_fix];
	const xAOD::Jet *jet2_fixed=(*ptr_const_jets)[index_jet2_fix];
	
	static SG::AuxElement::Accessor<char> acc_DL1r_FixedCutBEff_77("DL1r_FixedCutBEff_77");
	
	//    cout << "access to jet collection phase 5" << endl;
	
	bool jet1_pass_b_tag=acc_DL1r_FixedCutBEff_77(*jet1_fixed);
	
	//bool jet1_pass_b_tag=acc_DL1r_FixedCutBEff_77.isAvailable(*jet1_fixed) ? acc_DL1r_FixedCutBEff_77(*jet1_fixed) : 0;
	
	//    cout << "access to jet collection phase 6" << endl;
	
	//    bool jet2_pass_b_tag=acc_DL1r_FixedCutBEff_77.isAvailable(*jet2_fixed) ? acc_DL1r_FixedCutBEff_77(*jet2_fixed) : 0;
	
	bool jet2_pass_b_tag=acc_DL1r_FixedCutBEff_77(*jet2_fixed);
	
	//	  cout << "access to jet collection phase 7" << endl;
	//	  cout << "jet1_pass_b_tag=" << jet1_pass_b_tag << ", jet2_pass_b_tag=" << jet2_pass_b_tag << endl;
	
	if (jet1_pass_b_tag && jet2_pass_b_tag)
	  pass_preselection_2_bjets=1;
      }
      }    
  } // end h026
  */
