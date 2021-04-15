//7 minutes
//this is for theory systematics

bool mode_debug=0;
//problem of the environment variable


vector<string> CreateList_HH_non_resonant_kappa_lambda();
string Return_string_target_kappa(double numerical_target_kappa);

#include "CaseTheory_Renormalize_Weights_and_create_rel_effect/tool_CreateList_HH_non_resonant_kappa_lambda.C"

void macro_merge_KappaLambda_Reweighted_syst_trees_and_yields()
{
  //==============================================================
  //special case of reweighted kappa lambda
  
  vector<string> vec_string_kappa_lambda_destination=CreateList_HH_non_resonant_kappa_lambda();
  
  vec_string_kappa_lambda_destination=CreateList_HH_non_resonant_kappa_lambda();
  
  for (int index_kappa_lambda=0;index_kappa_lambda<vec_string_kappa_lambda_destination.size();index_kappa_lambda++) {
    cout << "index_kappa_lambda=" << index_kappa_lambda << ", name=" << vec_string_kappa_lambda_destination[index_kappa_lambda] << endl;
  }
  //==============================================================
  for (int index_kappa_lambda=0;index_kappa_lambda<vec_string_kappa_lambda_destination.size();index_kappa_lambda++) {
    //for (int index_kappa_lambda=0;index_kappa_lambda<1;index_kappa_lambda++) {
    
    string string_kappa_lambda=vec_string_kappa_lambda_destination[index_kappa_lambda];
        
    cout << "==================================================================" << endl;
    cout << "==================================================================" << endl;
    cout << "==================================================================" << endl;
    cout << "==================================================================" << endl;
    cout << "==================================================================" << endl;
      
    string string_unix;
    
    string string_path="/sps/atlas/e/escalier/ATLAS_HGam/Outputs_syst_yield_shape";
    
    //does not work with root : variable is not considered
    //    string_unix="export string_path=/sps/atlas/e/escalier/ATLAS_HGam/Outputs_syst_yield_shape";

    gSystem->Setenv("string_path","/sps/atlas/e/escalier/ATLAS_HGam/Outputs_syst_yield_shape");
    cout << "string_unix=" << string_unix << endl;
    
    gSystem->Exec(string_unix.c_str());
    
    cout << "make the print" << endl;
    gSystem->Exec("echo $string_path");

    if (mode_debug)
      string_unix="echo ";
    else
      string_unix="";
    
    string_unix+="rm -f ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_HHbbyy_reweight_mHH_1p0_to_";
    string_unix+=string_kappa_lambda;
    string_unix+="_nominal";
    string_unix+=".root";
    
    gSystem->Exec(string_unix.c_str());
    
    cout << "phase 2" << endl;
    cout << "string_unix=" << string_unix << endl;

    cout << "phase 3" << endl;

    //shit    string_unix="ls ${string_path}/trees_and_hist/Theory/ | grep h026 | grep HHbbyy_reweight | grep 1p0_to_"+string_kappa_lambda;

    string_unix="ls ${string_path}/trees_and_hist/Theory/ | grep h026 | grep PowhegPy8_HHbbyy_reweight | grep 1p0_to_"+string_kappa_lambda;

    string_unix+=" > ";
    string_unix+=" to_delete_list_to_hadd.txt";

    cout << "string_unix=" << string_unix << endl;

    gSystem->Exec(string_unix.c_str());

    //    gSystem->Exec("ls");

    ifstream stream_list_files("to_delete_list_to_hadd.txt");
    
    if (stream_list_files.fail()) {
      cout << "major problem : not able to open the file that has just been created, is there no more place on hard disk ?" << endl;
      cout << "halt program" << endl;
      exit(1);
    }

    char buffer[256];

    string string_list_files;
    
    if (stream_list_files.is_open()) {
      stream_list_files >> buffer;
      string_list_files+=buffer;
      
      while (stream_list_files.getline(buffer,256)) { // for all systematics
	string_list_files+=" ";
	
	stream_list_files >> buffer;
	
	string_list_files+=buffer;
      }
    }

    //       while (stream_list_files.getline(buffer,256)) { // for all systematics
    //       stream_list_files >> buffer;
    //       string_list_files+=buffer;
    //       string_list_files+=" ";
    //       }
    
    stream_list_files.close();

    cout << "string_list_files=" << string_list_files << endl;

    gSystem->Setenv("mylist",string_list_files.c_str());
    gSystem->Exec("echo $mylist");

    gSystem->Exec("rm to_delete_list_to_hadd.txt");
    
    cout << "string_unix=" << string_unix << endl;
    
    if (mode_debug)
      string_unix="echo ";
    else
      string_unix="";
    string_unix+="hadd ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_HHbbyy_reweight_mHH_1p0_to_";

    string_unix+=string_kappa_lambda;
    string_unix+="_nominal";
    string_unix+=".root";
    string_unix+=" `for i in $mylist ; do echo \"${string_path}/trees_and_hist/Theory/$i\" ; done`";
    
    cout << "string_unix=" << string_unix << endl;

    gSystem->Exec(string_unix.c_str());
    
    //example
    //  rm -f ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_HHbbyy_reweight_mHH_1p0_to_XXX.root
    //  mylist=( `ls ${string_path}/trees_and_hist/Theory/ | grep h026 |grep HHbbyy_reweight |grep 1p0_to_XXX` )
    //  hadd ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_HHbbyy_reweight_mHH_1p0_to_XXX.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/Theory/$i" ; done`
    
  } //end list on kappa_lambda
  //==============================================================
}
