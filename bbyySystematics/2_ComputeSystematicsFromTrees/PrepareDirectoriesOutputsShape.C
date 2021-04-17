#include <iostream>

using namespace std;

//root -b -q PrepareDirectoriesOutputsShape.C

string string_create_delete="create"; //create, delete
//int do_create1_delete2=1;

string string_directory_output="/sps/atlas/e/escalier/ATLAS_HGam/Outputs_syst_yield_shape/";

//root -b
//.x PrepareDirectoriesOutputsShape.C

vector<string> vec_information_directory={"figures","results_toys","scratch","trees_bootstrap"};

//careful : *never* put trees : this is the raw sample !!

//vector<string> vec_information_directory={"scratch"};
//vector<string> vec_information_directory={"trees_bootstrap"};

//vector<string> vec_information_directory={"figures"};
//vector<string> vec_information_directory={"results_toys"};

//vector<string> vec_string_finalDV={"m_yy","m_bb","m_yybb_tilde","m_yybb_cnstrnd"};
//vector<string> vec_string_finalDV={"m_bb"};
//vector<string> vec_string_finalDV={"m_yybb_tilde"};
//  vector<string> vec_string_finalDV={"m_yy","m_bb"};

//vector<string> vec_string_finalDV={"m_yy","m_bb","m_yybb_tilde"};

vector<string> vec_string_finalDV={"m_yy"};
//vector<string> vec_string_finalDV={"yield"};

vector<string> vec_string_category;
vector<int> vec_mX={251,260,280,300,325,350,400,450,500,550,600,700,800,900,1000}; //for categories
//vector<int> vec_mX={300}; //for categories
//vector<int> vec_mX={1000}; //for categories
//vector<int> vec_mX={500}; //for categories
//vector<int> vec_mX={260,280}; //for categories
//vector<int> vec_mX={260,280,300,325,350,500,1000}; //for categories

//vector<string> vec_string_campaign={"h025_mc16d"};
vector<string> vec_string_campaign={"h026_mc16a_h026_mc16d_h026_mc16e"};
//vector<string> vec_string_campaign={"h025_mc16a_h025_mc16d_h025_mc16e"};

vector<string> vec_string_process=
{
  //  "gg_HH_non_resonant_kappa_lambda_01"
//,
//  "gg_HH_non_resonant_kappa_lambda_10"
//,
/*
 shit
  "HH_non_resonant_kappa_lambda_01"
  ,
  "HH_non_resonant_kappa_lambda_10"
 */ 
//  "vbf_HH_non_resonant_kappa_lambda_01"
  //  "PowhegH7_HHbbyy_cHHH01d0",
  //   "PowhegH7_HHbbyy_cHHH10d0"
  
  //  "aMCnloHwpp_hh_yybb" //gg HH LO sample
  //  "MGH7_hh_bbyy_vbf_l1cvv1cv1" //vbf HH sample
  //  "MGH7_X300tohh_bbyy",
  //"SingleHiggs"
//  ,"PowhegPy8_NNLOPS_ggH125"
//  ,
"ZH125"
  
// , "ttH125"
//  ,
//shit"PowhegPy8_ttH125_fixweight"
  
  //"NonResonantPlusSingle","aMCnloHwpp_hh_yybb_AF2","SingleHiggs"
  
  /*
  "MGH7_X251tohh_bbyy_AF2",
  "MGH7_X260tohh_bbyy_AF2",
  "MGH7_X280tohh_bbyy_AF2",
  "MGH7_X300tohh_bbyy_AF2",
  "MGH7_X325tohh_bbyy_AF2",
  "MGH7_X350tohh_bbyy_AF2",
  "MGH7_X400tohh_bbyy_AF2",
  "MGH7_X450tohh_bbyy_AF2",
  "MGH7_X500tohh_bbyy_AF2",
  "MGH7_X550tohh_bbyy_AF2",
  "MGH7_X600tohh_bbyy_AF2",
  "MGH7_X700tohh_bbyy_AF2",
  "MGH7_X800tohh_bbyy_AF2",
  "MGH7_X900tohh_bbyy_AF2",
  "MGH7_X1000tohh_bbyy_AF2"
  */
};

//vector<string> vec_string_process={"SingleHiggs"};
//vector<string> vec_string_process={"NonResonantPlusSingle","aMCnloHwpp_hh_yybb_AF2","SingleHiggs","MGH7_X280tohh_bbyy_AF2","MGH7_X500tohh_bbyy_AF2","MGH7_X1000tohh_bbyy_AF2","MGPy8_X280tohh_bbyy_AF2","MGPy8_X500tohh_bbyy_AF2","MGPy8_X1000tohh_bbyy_AF2","ZH125","ggH125"};
//vector<string> vec_string_process={"ttH","ZH","ggH"};

void Manage_Directory_Information();
void Manage_Directory_Process();
void Manage_Directory_Campaign();
void Manage_Directory_Category();
void Manage_Directory_Observable();
void Manage_Directory_Systematic();
void Fill_categories(string string_process);

int index_subdirectory=0;
int index_process=0;
int index_campaign=0;
int index_category=0;
int index_observable=0;
int index_systematic=0;

vector<string> vec_string_systematic;

int PrepareDirectoriesOutputsShape()
{
  cout << "string_directory_output=" << string_directory_output << endl;
  //-------------------------------------------------------------
  //get list of systematics
  ifstream stream_list_syst;
  stream_list_syst.open("Inputs/list_syst_all.sh");
  
  //the technique with eof is not working: see :
  //https://softwareengineering.stackexchange.com/questions/318081/why-does-ifstream-eof-not-return-true-after-reading-the-last-line-of-a-file
  
  vec_string_systematic.clear();
    
  char buffer[128];
    
  int nb_sys=0;

  while (stream_list_syst.getline(buffer,128)) { // for all systematics
    cout << "reads : " << buffer << endl;
    if (buffer[0]=='#')
      continue;
      
    string string_buffer=buffer;

    replace(string_buffer.begin(),string_buffer.end(),' ','_');
    
    vec_string_systematic.push_back(string_buffer);
      
    nb_sys++;
      
    //    cout << "string_systematic=" << string_systematic << endl;

  } //end read txt file on systematics to consider
  
  cout << "nb_sys=" << nb_sys << endl;
  //-------------------------------------------------------------
  //get working directory ? and do cd() ?

  bool success;

  string string_working_directory=gSystem->GetWorkingDirectory();
  success=gSystem->cd(string_directory_output.c_str());
  cout << "going to " << string_directory_output << endl;

  if (!success) {
    cout << "problem accessing directory, halt program" << endl;
    exit(1);
  }
  //  gSystem->ls();

  //gSystem->Exec("pwd");
  //  gSystem->Exec("ls");

  //  string string_unix_command;

  //string_process
  //never delete the genuine "trees" directory : these are the original trees

  for (index_subdirectory=0;index_subdirectory<vec_information_directory.size();index_subdirectory++) {
    
    cout << "index_subdirectory=" << index_subdirectory << endl;

    //shit    if (do_create1_delete2==1)
    if (string_create_delete=="create")
      Manage_Directory_Information();
    
    for (index_process=0;index_process<vec_string_process.size();index_process++) {
      string string_process=vec_string_process[index_process];
      
      cout << "index_process=" << index_process << ", string_process=" << string_process << endl;
      
      //shit      if (do_create1_delete2==1)
      if (string_create_delete=="create")
	Manage_Directory_Process();
      
      for (index_campaign=0;index_campaign<vec_string_campaign.size();index_campaign++) {
	
	cout << "index_campaign=" << index_campaign << endl;
	
	if (string_create_delete=="create")
	  //shit	if (do_create1_delete2==1)
	  Manage_Directory_Campaign();
	//----------
	vec_string_category.clear();
	
	Fill_categories(string_process);
	
	for (index_category=0;index_category<vec_string_category.size();index_category++) {
	  
	  cout << "index_category=" << index_category << endl;
	  
	  if (string_create_delete=="create")
	    //if (do_create1_delete2==1)
	    Manage_Directory_Category();
	      
	  for (index_observable=0;index_observable<vec_string_finalDV.size();index_observable++) { //one could potentially have a different set of observables according to category
	    
	    cout << "index_observable=" << index_observable << endl;
	    
	    if (string_create_delete=="create")
	      //	    if (do_create1_delete2==1)
	      Manage_Directory_Observable();
	    
	    for (index_systematic=0;index_systematic<nb_sys;index_systematic++) {
	      
	      cout << "index_systematic=" << index_systematic << endl;
	      
	      if (string_create_delete=="create")
		//	      if (do_create1_delete2==1)
		Manage_Directory_Systematic();
	      //--------------------------------------------------------------------------------------
	      if (string_create_delete=="delete")
		//if (do_create1_delete2==2)
		Manage_Directory_Systematic();
	    } //end loop systematics

	    if (string_create_delete=="delete")
	      //if (do_create1_delete2==2)
	      Manage_Directory_Observable();
	    
	  } //end loop observable
	  
	  if (string_create_delete=="delete")
	    //	      if (do_create1_delete2==2)
	    Manage_Directory_Category();
	  
	} //end loop category

	if (string_create_delete=="delete")
	  //	if (do_create1_delete2==2)
	  Manage_Directory_Campaign();
	
      } //end loop campaigns
      
      if (string_create_delete=="delete")
	//	if (do_create1_delete2==2)
	Manage_Directory_Process();
      
    } //end loop processes
    
    if (string_create_delete=="delete")
      //    if (do_create1_delete2==2)
      Manage_Directory_Information();
    
  } //end loop subdirectory
  
  //go back to working directory
  
  success=gSystem->cd(string_working_directory.c_str());
  
  return 0;
}
//--------------------------------------------------------------------------------------------------
void Manage_Directory_Information()
{
  string string_unix_command;
  
  if (string_create_delete=="create")
    string_unix_command="mkdir -p "; //no complaint if it already exist
  else if (string_create_delete=="delete")
    //  else if (do_create1_delete2==2)
    string_unix_command="rmdir "; //no complaint if it already exist
  
  string_unix_command+=vec_information_directory[index_subdirectory];
  gSystem->Exec(string_unix_command.c_str());
}
//--------------------------------------------------------------------------------------------------
void Manage_Directory_Process()
{
  cout << "in Manage_Directory_Process()" << endl;

  string string_unix_command;

  if (string_create_delete=="create")
    //  if (do_create1_delete2==1)
    string_unix_command="mkdir -p "; //no complaint if it already exist
  else if (string_create_delete=="delete")
    //  else if (do_create1_delete2==2)
    string_unix_command="rmdir "; //no complaint if it already exist
  string_unix_command+=vec_information_directory[index_subdirectory];
  string_unix_command+="/";
  string_unix_command+=vec_string_process[index_process];
  
  cout << "string_unix_command=" << string_unix_command << endl;
  
  gSystem->Exec(string_unix_command.c_str());
}
//--------------------------------------------------------------------------------------------------
void Manage_Directory_Campaign()
{
  cout << "in Manage_Directory_Campaign()" << endl;

  string string_unix_command;

  if (string_create_delete=="create")
    //  if (do_create1_delete2==1)
    string_unix_command="mkdir -p "; //no complaint if it already exist
  else if (string_create_delete=="delete")
    //  else if (do_create1_delete2==2)
    string_unix_command="rmdir "; //no complaint if it already exist
  
  string_unix_command+=vec_information_directory[index_subdirectory];
  string_unix_command+="/";
  string_unix_command+=vec_string_process[index_process];
  string_unix_command+="/";
  string_unix_command+=vec_string_campaign[index_campaign];

  cout << "string_unix_command directory campaign=" << string_unix_command << endl;
  
  gSystem->Exec(string_unix_command.c_str());
}
//--------------------------------------------------------------------------------------------------
void Manage_Directory_Category()
{
  string string_unix_command;

  cout << "in Manage_Directory_Category" << endl;
  if (string_create_delete=="create")
    //  if (do_create1_delete2==1)
    string_unix_command="mkdir -p "; //no complaint if it already exist
  else if (string_create_delete=="delete")
    //  else if (do_create1_delete2==2)
    string_unix_command="rmdir "; //no complaint if it already exist
  
  string_unix_command+=vec_information_directory[index_subdirectory];
  string_unix_command+="/";
  string_unix_command+=vec_string_process[index_process];
  string_unix_command+="/";
  string_unix_command+=vec_string_campaign[index_campaign];
  string_unix_command+="/";
  string_unix_command+=vec_string_category[index_category];

  cout << "string_unix_command directory=" << string_unix_command << endl;
  
  gSystem->Exec(string_unix_command.c_str());
}
//--------------------------------------------------------------------------------------------------
void Manage_Directory_Observable()
{
  string string_unix_command;

  if (string_create_delete=="create")
    //  if (do_create1_delete2==1)
    string_unix_command="mkdir -p "; //no complaint if it already exist
  else if (string_create_delete=="delete")
    //  else if (do_create1_delete2==2)
    string_unix_command="rmdir "; //no complaint if it already exist
  
  string_unix_command+=vec_information_directory[index_subdirectory];
  string_unix_command+="/";
  string_unix_command+=vec_string_process[index_process];
  string_unix_command+="/";
  string_unix_command+=vec_string_campaign[index_campaign];
  string_unix_command+="/";
  string_unix_command+=vec_string_category[index_category];
  string_unix_command+="/";
  string_unix_command+=vec_string_finalDV[index_observable];

  cout << "string_unix_command=" << string_unix_command << endl;
  
  gSystem->Exec(string_unix_command.c_str());
}
//--------------------------------------------------------------------------------------------------
void Manage_Directory_Systematic()
{
  cout << "in Manage_Directory_Systematic()" << endl;

  string string_unix_command;
  
  if (string_create_delete=="create")
    //  if (do_create1_delete2==1)
    string_unix_command="mkdir -p "; //no complaint if it already exist
  else if (string_create_delete=="delete")
    //  else if (do_create1_delete2==2)
    string_unix_command="rm -f "; //no complaint if it already exist

  string_unix_command+=vec_information_directory[index_subdirectory];
  string_unix_command+="/";
  string_unix_command+=vec_string_process[index_process];
  string_unix_command+="/";
  string_unix_command+=vec_string_campaign[index_campaign];
  string_unix_command+="/";
  string_unix_command+=vec_string_category[index_category];
  string_unix_command+="/";
  string_unix_command+=vec_string_finalDV[index_observable];
  string_unix_command+="/";
  string_unix_command+=vec_string_systematic[index_systematic];

  if (string_create_delete=="delete")
    //  if (do_create1_delete2==2)
    string_unix_command+="/*";

  cout << "string_unix_command deletion systematic=" << string_unix_command << endl;
  gSystem->Exec(string_unix_command.c_str());
  
  if (string_create_delete=="delete") {
    //  if (do_create1_delete2==2) {
    string_unix_command="rmdir "; //no complaint if it already exist

    string_unix_command+=vec_information_directory[index_subdirectory];
    string_unix_command+="/";
    string_unix_command+=vec_string_process[index_process];
    string_unix_command+="/";
    string_unix_command+=vec_string_campaign[index_campaign];
    string_unix_command+="/";
    string_unix_command+=vec_string_category[index_category];
    string_unix_command+="/";
    string_unix_command+=vec_string_finalDV[index_observable];
    string_unix_command+="/";
    string_unix_command+=vec_string_systematic[index_systematic];
    
    cout << "string_unix_command rmdir systematic=" << string_unix_command << endl;
    gSystem->Exec(string_unix_command.c_str());
  }
}
//--------------------------------------------------------------------------------------------------
void Fill_categories(string string_process)
{
  //HH non resonant baseline
  if (string_process.find("_X")==string::npos) { //sample is not a resonant sample, so either a HH non resonant or a single Higgs
    
    //so consider to include the non resonant categories
   
    //    vec_string_category.push_back("Inclusive_HH_NonResonant");


    vec_string_category.push_back("XGBoost_btag77_withTop_BCal_tightScore_HMass");
    vec_string_category.push_back("XGBoost_btag77_withTop_BCal_looseScore_HMass");
    vec_string_category.push_back("XGBoost_btag77_withTop_BCal_tightScore_LMass");
    vec_string_category.push_back("XGBoost_btag77_withTop_BCal_looseScore_LMass");
    ////NO    vec_string_category.push_back("VBF_btag77_withTop_BCal");
  }
  //-----
  //HH resonant baseline
  
  bool is_HH_non_resonant=0;

  if (string_process.find("HH_non_resonant")!=string::npos
      ||
      string_process.find("_HHH")!=string::npos
      ||
      string_process.find("aMC")!=string::npos
      ||
      string_process.find("bbyy_vbf_")!=string::npos
      )
    is_HH_non_resonant=1;
      
    //so consider to include the resonant categories
    
    bool is_single_Higgs=0;
    if (string_process.find("ggH125")!=string::npos
	||
	string_process.find("ZH125")!=string::npos
	||
	string_process.find("ttH125")!=string::npos
	||
	(string_process.find("SingleHiggs")!=string::npos && string_process.find("NonResonantPlusSingleiggs")==string::npos)
	)
      is_single_Higgs=1;
    
    //---------------------------------------------
    //HH resonant
    
    bool is_Resonant_sample=0;
    
    if (string_process.find("MGH7_X")!=string::npos)
      is_Resonant_sample=1;
    
    for (unsigned int index_mX=0;index_mX<vec_mX.size();index_mX++) {
      int mX=vec_mX[index_mX];
      
      //	cout << "mX=" << mX << endl;
      
      string string_resonance="X"+to_string(vec_mX[index_mX]);
      
      if (!is_Resonant_sample
	  ||
	  (is_Resonant_sample && string_process.find(string_resonance.c_str())!=string::npos)
	  )
	vec_string_category.push_back("Resonant_mX"+to_string(mX));
    } //end loop on mX
}
//--------------------------------------------------------------------------------------------------
