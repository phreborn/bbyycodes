vector<string> CreateListCategories(string string_file)
{
  vector<string> vec_string_category;
  
  //HH non resonant baseline
  if (string_file.find("_X")==string::npos) { //sample is not a resonant sample, so either a HH non resonant or a single Higgs
    
    //so consider to include the non resonant categories
    
    //NO vec_string_category.push_back("Inclusive_HH_NonResonant");
    
    vec_string_category.push_back("XGBoost_btag77_withTop_BCal_tightScore_HMass");
    vec_string_category.push_back("XGBoost_btag77_withTop_BCal_looseScore_HMass");
    vec_string_category.push_back("XGBoost_btag77_withTop_BCal_tightScore_LMass");
    vec_string_category.push_back("XGBoost_btag77_withTop_BCal_looseScore_LMass");
    
    //      vec_string_category.push_back("VBF_btag77_withTop_BCal");
  }
  
  //HH resonant baseline
  
  if (string_file.find("_HHH")==string::npos
      &&
      string_file.find("HHbbyy_reweight")==string::npos
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
	
	vec_string_category.push_back("Resonant_m"+string_resonance);
      }
      
    } //end loop on mX
  } //end case resonant

  return vec_string_category;
}
