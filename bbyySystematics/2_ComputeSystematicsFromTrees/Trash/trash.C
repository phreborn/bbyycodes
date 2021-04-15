  /*
  if (do_ShapeSyst_from_mean_interquartile)
    gErrorIgnoreLevel=kError; //switch off the message at SaveAs
  */

  /*
  cout << "ROOT::Math::MinimizerOptions::DefaultTolerance()=" << ROOT::Math::MinimizerOptions::DefaultTolerance() << endl;

  ROOT::Math::MinimizerOptions::SetDefaultTolerance(1e-5); //1e-2*1e-3

  cout << "ROOT::Math::MinimizerOptions::DefaultTolerance()=" << ROOT::Math::MinimizerOptions::DefaultTolerance() << endl;
  exit(1);
  */

  /*
  //not useful for the moment
  ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit2");
  ROOT::Math::MinimizerOptions::SetDefaultStrategy(1);
  ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(0);
  */

  /*
  cout << "ROOT::Math::MinimizerOptions::MaxFunctionCalls()=" << ROOT::Math::MinimizerOptions::MaxFunctionCalls() << endl;
  cout << "ROOT::Math::MinimizerOptions::MaxIterations()=" << ROOT::Math::MinimizerOptions::MaxIterations() << endl;
  exit(1);
  */





  /* //is it shit : if so, put in trash
    ReviewEffectSystematics_current_subset_systematics(index_category,"",string_MxAOD,MISC_SYS,flag_do_yield1_shape2,-1,-1);
    
    ReviewEffectSystematics_current_subset_systematics(index_category,"",string_MxAOD,PHOTONS_SYS_SCALE_1NP,flag_do_yield1_shape2,-1,-1);
  
    ReviewEffectSystematics_current_subset_systematics(index_category,"",string_MxAOD,PHOTONS_SYS_EFF,flag_do_yield1_shape2,-1,-1);
  
    //PhotonAllSys
    //    ReviewEffectSystematics_current_subset_systematics(index_category,"",string_MxAOD,PHOTONS_SYS_SCALE_NON_MAT_ALLNPs,-1,-1);  //for 1-H, does not exist : definitively lost from official ressources 
    //    ReviewEffectSystematics_current_subset_systematics(index_category,"",string_MxAOD,PHOTONS_SYS_SCALE_MAT_ALLNPs,-1,-1);  //for 1-H, does not exist : definitively lost from official ressources
    //    ReviewEffectSystematics_current_su bset_systematics(index_category,"",string_MxAOD,PHOTONS_SYS_RESOL_ALLNPs,-1,-1);  //for 1-H, does not exist : definitively lost from official ressources
      
    ReviewEffectSystematics_current_subset_systematics(index_category,"",string_MxAOD,JETS_SYS,flag_do_yield1_shape2,-1,-1);

    //ReviewEffectSystematics_current_subset_systematics(index_category,"",string_MxAOD,FLAVOR_SYS,flag_do_yield1_shape2,-1,-1);
      
    //FlavorAllSys
    //ReviewEffectSystematics_current_subset_systematics(index_category,"",string_MxAOD,BTAG_LIGHT_1_SYS,-1,-1);
    //ReviewEffectSystematics_current_subset_systematics(index_category,"",string_MxAOD,BTAG_LIGHT_2_SYS,-1,-1);
    //ReviewEffectSystematics_current_subset_systematics(index_category,"",string_MxAOD,BTAG_B_SYS,-1,-1);
    //ReviewEffectSystematics_current_subset_systematics(index_category,"",string_MxAOD,BTAG_C_SYS,-1,-1);
    //ReviewEffectSystematics_current_subset_systematics(index_category,"",string_MxAOD,BTAG_INDEPENDENT_TAG_SYS,-1,-1);
      
    //ReviewEffectSystematics_current_subset_systematics(index_category,"",string_MxAOD,LeptonMET_SYS,-1,-1);
    */




  /*shit put in trash if ok
  else if (menu_systematics=="MISC_SYS") {
    stream_list_syst.open("Inputs/list_syst_misc.sh");
    string_file_results_systematics_details+="misc"; //to rename in event based ?
  }
  else if (menu_systematics=="PHOTONS_SYS_SCALE_1NP") {
    stream_list_syst.open("Inputs/list_syst_photons_scale_1NP.sh");
    string_file_results_systematics_details+="photons_scale_1np";
  }
  else if (menu_systematics=="PHOTONS_SYS_EFF") {
    stream_list_syst.open("Inputs/list_syst_photons_efficiencies_allNPs.sh");
    string_file_results_systematics_details+="photons_eff";
  }
  else if (menu_systematics=="PHOTONS_SYS_SCALE_NON_MAT_ALLNPs") {
    stream_list_syst.open("Inputs/list_syst_photons_scale_non_mat_allNPs.sh");
    string_file_results_systematics_details+="photons_scale_non_mat_allnps";
  }
  else if (menu_systematics=="PHOTONS_SYS_SCALE_MAT_ALLNPs") {
    stream_list_syst.open("Inputs/list_syst_photons_scale_mat_allNPs.sh");
    string_file_results_systematics_details+="photons_scale_mat_allnps";
  }
  else if (menu_systematics=="PHOTONS_SYS_RESOL_ALLNPs") {
    stream_list_syst.open("Inputs/list_syst_photons_resolution_allNPs.sh");
    string_file_results_systematics_details+="photons_resolution_allnps";
  }
  else if (menu_systematics=="JETS_SYS") {
    stream_list_syst.open("Inputs/list_syst_jets.sh");
    string_file_results_systematics_details+="jets";
  }
  else if (menu_systematics=="FLAVOR_SYS") {
    stream_list_syst.open("Inputs/list_syst_flavor.sh");
    string_file_results_systematics_details+="flavor";
  }  
  else if (menu_systematics=="BTAG_LIGHT_1_SYS") {
    stream_list_syst.open("Inputs/list_syst_btag_light_1.sh");
    string_file_results_systematics_details+="btag_light_1";
  }
  else if (menu_systematics=="BTAG_LIGHT_2_SYS") {
    stream_list_syst.open("Inputs/list_syst_btag_light_2.sh");
    string_file_results_systematics_details+="btag_light_2";
  }
  else if (menu_systematics=="BTAG_B_SYS") {
    stream_list_syst.open("Inputs/list_syst_btag_b.sh");
    string_file_results_systematics_details+="btag_b";
  }
  else if (menu_systematics=="BTAG_C_SYS") {
    stream_list_syst.open("Inputs/list_syst_btag_c.sh");
    string_file_results_systematics_details+="btag_c";
  }
  else if (menu_systematics=="BTAG_INDEPENDENT_TAG_SYS") {
    stream_list_syst.open("Inputs/list_syst_btag_independent_tag.sh");
    string_file_results_systematics_details+="btag_independent_flavour";
  }
  else if (menu_systematics=="LeptonMET_SYS") {
    stream_list_syst.open("Inputs/list_syst_lepton_met.sh");
    string_file_results_systematics_details+="lepton_met";
  }
  else  {
    cout << "menu_systematics=" << menu_systematics << endl;
    cout << "case not anticipated, halt program" << endl;
    exit(1);
  }
  */
