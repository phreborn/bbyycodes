NO MORE TO BE USED




//REMARK : a priori no more to be used
//
//
//


//NO MORE TO BE USED IF OK

//USE INSTEAD HaddAllResults_toys

string string_type_of_analysis="ShapeFrom_mean_IQR";

// "ShapeFrom_mean_IQR";
// "ShapeFrom_fit"

int Merge_Results_SystShape()
{
  cout << "DO NOT USE THIS" << endl;
  cout << "USE HaddAllResults" << endl;
  exit(1);
  string string_h0XX="h024";
  vector<string> vec_year_campaigns={"mc16a","mc16d","mc16e"};
  //vector<string> vec_year_campaigns={"mc16a"};
  vector<string> vec_string_process={"aMCnloHwpp_hh_yybb_AF2","SingleHiggs"};
  //vector<string> vec_string_process={"SingleHiggs"};
  vector<string> vec_string_category={"NonResonant_LooseLowMass","NonResonant_TightLowMass","NonResonant_LooseHighMass","NonResonant_TightHighMass","NonResonant_Inclusive"};
  //vector<string> vec_string_category={"NonResonant_LooseLowMass"};
  
  ifstream stream_list_syst;
  stream_list_syst.open("Inputs/list_syst_all.sh");

  //the technique with eof is not working: see :
  //https://softwareengineering.stackexchange.com/questions/318081/why-does-ifstream-eof-not-return-true-after-reading-the-last-line-of-a-file
    
  vector<string> vec_string_systematic;
  vec_string_systematic.clear();
    
  char buffer[128];
  
  while (stream_list_syst.getline(buffer,128)) { // for all systematics
    cout << "reads : " << buffer << endl;
    //    cout << "buffer[0]=" << buffer[0] << endl;
    if (buffer[0]=='#')
      continue;
      
    //    string_systematic=buffer;
    //    vec_string_systematic.push_back(string_systematic);

    vec_string_systematic.push_back(buffer);
  } //end read txt file on systematics to consider
  
  for (unsigned int index_year_campaign=0;index_year_campaign<vec_year_campaigns.size();index_year_campaign++) {
    cout << "===============================================" << endl;
    
    for (unsigned int index_category=0;index_category<vec_string_category.size();index_category++) {
      
      for (unsigned int index_process=0;index_process<vec_string_process.size();index_process++) {
	cout << "--------------------------------------------------------" << endl;
	
	for (unsigned int index_systematic=0;index_systematic<vec_string_systematic.size();index_systematic++) {
	  cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
	  
	  string string_current_path="/sps/atlas/e/escalier/ATLAS_HGam/Outputs_syst_shape_Run2/results_toys/";
	  
	  string string_directory=string_current_path;
	  string_directory+=vec_string_category[index_category];
	  string_directory+="/";
	  string_directory+=string_h0XX;
	  string_directory+="_";
	  string_directory+=vec_year_campaigns[index_year_campaign];
	  string_directory+="/";
	  string_directory+=vec_string_process[index_process];
	  string_directory+="/";
	  string_directory+=vec_string_systematic[index_systematic];
	  string_directory+="/";

	  string string_unix_command;
	  
	  string_unix_command="rm ";
	  string_unix_command+=string_directory;
	  string_unix_command+=string_type_of_analysis;
	  string_unix_command+="_";
	  string_unix_command+="AllToys.root";
	  cout << "rm command" << endl;
	  cout << "string_unix_command=" << string_unix_command << endl;
	  gSystem->Exec(string_unix_command.c_str());

	  string_unix_command="hadd ";
	  string_unix_command+=string_directory;
	  string_unix_command+=string_type_of_analysis;
	  string_unix_command+="_";
	  string_unix_command+="AllToys.root";
	  string_unix_command+=" ";
	  string_unix_command+=string_directory;
	  string_unix_command+=string_type_of_analysis;
	  string_unix_command+="*root*";

	  cout << "string_unix_command=" << string_unix_command << endl;
	  gSystem->Exec(string_unix_command.c_str());
	}
      }
    }
  }
  
  return 0;
}
