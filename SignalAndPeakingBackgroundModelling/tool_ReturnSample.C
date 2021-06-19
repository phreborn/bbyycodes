//to rename in ReturSample, since some samples are not signal

//===========================================================================================================
TChain *ReturnSampleSignal(string string_process,string string_category)
{
  cout << "in ReturnSampleSignal, phase 1" << endl;
  //baseline
  string string_path_samples="/sps/atlas/e/escalier/ATLAS_HGam/Outputs_trees_selection_HH_baseline/";
  
  cout << "string_process=" << string_process << endl;

  //-------------------------------------------------------------
  //part that could be common to non resonant and resonant

  if (string_process=="ggH" || string_process=="SingleHiggs" || string_process=="gg_HH_NLO_plus_SingleHiggs") {
    chain_ggH=new TChain((string("tree_sel_HH_")+string_category).c_str());
    
    if (string_version_MxAOD=="h026") {
      if (do_mc16a)
	chain_ggH->Add((string_path_samples+"tree_h026_mc16a_PowhegPy8_NNLOPS_ggH125_nominal.root").c_str());
      if (do_mc16d)
	chain_ggH->Add((string_path_samples+"tree_h026_mc16d_PowhegPy8_NNLOPS_ggH125_nominal.root").c_str());
      if (do_mc16e)
	chain_ggH->Add((string_path_samples+"tree_h026_mc16e_PowhegPy8_NNLOPS_ggH125_nominal.root").c_str());
    }
  } //ggH

  if (string_process=="VBF" || string_process=="SingleHiggs" || string_process=="gg_HH_NLO_plus_SingleHiggs") {
    
    if (string_version_MxAOD=="h026") {
      chain_VBF=new TChain((string("tree_sel_HH_")+string_category).c_str());

      if (do_mc16a)
	chain_VBF->Add((string_path_samples+"tree_h026_mc16a_PowhegPy8EG_NNPDF30_VBFH125_nominal.root").c_str());
      if (do_mc16d)
	chain_VBF->Add((string_path_samples+"tree_h026_mc16d_PowhegPy8EG_NNPDF30_VBFH125_nominal.root").c_str());
      if (do_mc16e)
	chain_VBF->Add((string_path_samples+"tree_h026_mc16e_PowhegPy8EG_NNPDF30_VBFH125_nominal.root").c_str());
    }
  }

  if (string_process=="ZH" || string_process=="SingleHiggs" || string_process=="gg_HH_NLO_plus_SingleHiggs") {
    
    chain_qqZH=new TChain((string("tree_sel_HH_")+string_category).c_str());

    if (string_version_MxAOD=="h026") {
      if (do_mc16a)
	chain_qqZH->Add((string_path_samples+"tree_h026_mc16a_PowhegPy8_ZH125J_nominal.root").c_str());
      if (do_mc16d)
	chain_qqZH->Add((string_path_samples+"tree_h026_mc16d_PowhegPy8_ZH125J_nominal.root").c_str());
      if (do_mc16e)
	chain_qqZH->Add((string_path_samples+"tree_h026_mc16e_PowhegPy8_ZH125J_nominal.root").c_str());
    }
    
    chain_ggZH=new TChain((string("tree_sel_HH_")+string_category).c_str());
    
    if (string_version_MxAOD=="h026") {
      if (do_mc16a)
	chain_ggZH->Add((string_path_samples+"tree_h026_mc16a_PowhegPy8_ggZH125_nominal.root").c_str());
      if (do_mc16d)
	chain_ggZH->Add((string_path_samples+"tree_h026_mc16d_PowhegPy8_ggZH125_nominal.root").c_str());
      if (do_mc16e)
	chain_ggZH->Add((string_path_samples+"tree_h026_mc16e_PowhegPy8_ggZH125_nominal.root").c_str());
    }
  }
  
  if (string_process=="ttH" || string_process=="SingleHiggs" || string_process=="gg_HH_NLO_plus_SingleHiggs") {
    chain_ttH=new TChain((string("tree_sel_HH_")+string_category).c_str());
    
    if (string_version_MxAOD=="h026") {
      if (do_mc16a)
	chain_ttH->Add((string_path_samples+"tree_h026_mc16a_PowhegPy8_ttH125_fixweight_nominal.root").c_str());
      if (do_mc16d)
	chain_ttH->Add((string_path_samples+"tree_h026_mc16d_PowhegPy8_ttH125_fixweight_nominal.root").c_str());
      if (do_mc16e)
	chain_ttH->Add((string_path_samples+"tree_h026_mc16e_PowhegPy8_ttH125_fixweight_nominal.root").c_str());
    }
  }

  if (string_process=="WH" || string_process=="SingleHiggs" || string_process=="gg_HH_NLO_plus_SingleHiggs") {
    chain_WH=new TChain((string("tree_sel_HH_")+string_category).c_str());
    
    if (string_version_MxAOD=="h026") {
      if (do_mc16a) {
	chain_WH->Add((string_path_samples+"tree_h026_mc16a_PowhegPy8_WpH125J_nominal.root").c_str());
	chain_WH->Add((string_path_samples+"tree_h026_mc16a_PowhegPy8_WmH125J_nominal.root").c_str());
      }
      if (do_mc16d) {
	chain_WH->Add((string_path_samples+"tree_h026_mc16d_PowhegPy8_WpH125J_nominal.root").c_str());
	chain_WH->Add((string_path_samples+"tree_h026_mc16d_PowhegPy8_WmH125J_nominal.root").c_str());
      }
      if (do_mc16e) {
	chain_WH->Add((string_path_samples+"tree_h026_mc16e_PowhegPy8_WpH125J_nominal.root").c_str());
	chain_WH->Add((string_path_samples+"tree_h026_mc16e_PowhegPy8_WmH125J_nominal.root").c_str());
      }
    }
  }

  if (string_process=="bbH" || string_process=="SingleHiggs" || string_process=="gg_HH_NLO_plus_SingleHiggs") {
    chain_bbH=new TChain((string("tree_sel_HH_")+string_category).c_str());
    
    if (string_version_MxAOD=="h026") {
      if (do_mc16a)
	chain_bbH->Add((string_path_samples+"tree_h026_mc16a_PowhegPy8_bbH125_nominal.root").c_str());
      if (do_mc16d)
	chain_bbH->Add((string_path_samples+"tree_h026_mc16d_PowhegPy8_bbH125_nominal.root").c_str());
      if (do_mc16e)
	chain_bbH->Add((string_path_samples+"tree_h026_mc16e_PowhegPy8_bbH125_nominal.root").c_str());
    }
  }

  if (string_process=="tWH" || string_process=="SingleHiggs" || string_process=="gg_HH_NLO_plus_SingleHiggs") {
    chain_tWH=new TChain((string("tree_sel_HH_")+string_category).c_str());
    
    if (string_version_MxAOD=="h026") {
      if (do_mc16a)
	chain_tWH->Add((string_path_samples+"tree_h026_mc16a_aMCnloPy8_tWH125_nominal.root").c_str());
      if (do_mc16d)
	chain_tWH->Add((string_path_samples+"tree_h026_mc16d_aMCnloPy8_tWH125_nominal.root").c_str());
      if (do_mc16e)
	chain_tWH->Add((string_path_samples+"tree_h026_mc16e_aMCnloPy8_tWH125_nominal.root").c_str());
    }
  }
  
  if (string_process=="tHjb" || string_process=="SingleHiggs" || string_process=="gg_HH_NLO_plus_SingleHiggs") {

    if (string_version_MxAOD=="h026") {
      chain_tHjb=new TChain((string("tree_sel_HH_")+string_category).c_str());
      
      if (do_mc16a)
	chain_tHjb->Add((string_path_samples+"tree_h026_mc16a_aMCnloPy8_tHjb125_4fl_shw_fix_nominal.root").c_str());
      if (do_mc16d)
	chain_tHjb->Add((string_path_samples+"tree_h026_mc16d_aMCnloPy8_tHjb125_4fl_shw_fix_nominal.root").c_str());
      if (do_mc16e)
	chain_tHjb->Add((string_path_samples+"tree_h026_mc16e_aMCnloPy8_tHjb125_4fl_shw_fix_nominal.root").c_str());
    }
  }

  //do not do else, to allow addition (in particular for case Single Higgs)
  
  if (string_process=="PowhegPy8_HHbbyy_cHHH01d0" || string_process=="PowhegPy8_HHbbyy_cHHH01d0_train_events" || string_process=="PowhegPy8_HHbbyy_cHHH01d0_public_test_events" || string_process=="PowhegH7_HHbbyy_cHHH01d0_private_test_events") {
    chain_gg_HH=new TChain((string("tree_sel_HH_")+string_category).c_str());
    
    if (do_mc16a)
      chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_PowhegPy8_HHbbyy_cHHH01d0_nominal.root").c_str());
    if (do_mc16d)
      chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_PowhegPy8_HHbbyy_cHHH01d0_nominal.root").c_str());
    if (do_mc16e)
      chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_PowhegPy8_HHbbyy_cHHH01d0_nominal.root").c_str());
    
    cout << "chain_gg_HH->GetEntries()=" << chain_gg_HH->GetEntries() << endl;
    //    exit(1);
  }

  else if (string_process=="gg_HH" || string_process=="gg_HH_NLO_plus_SingleHiggs" || string_process=="gg_HH_NLO" || string_process=="gg_HH_NLO_train_events" || string_process=="gg_HH_NLO_public_test_events" || string_process=="gg_HH_NLO_private_test_events") {
    
    cout << "this scenario" << endl;
    
    chain_gg_HH=new TChain((string("tree_sel_HH_")+string_category).c_str());
    
    
    if (do_mc16a)
      chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_PowhegPy8_HHbbyy_cHHH01d0_nominal.root").c_str());
    if (do_mc16d)
      chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_PowhegPy8_HHbbyy_cHHH01d0_nominal.root").c_str());
    if (do_mc16e)
      chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_PowhegPy8_HHbbyy_cHHH01d0_nominal.root").c_str());
    
    /*
    if (do_mc16a)
      chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_PowhegH7_HHbbyy_cHHH01d0_nominal.root").c_str());
    if (do_mc16d)
      chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_PowhegH7_HHbbyy_cHHH01d0_nominal.root").c_str());
    if (do_mc16e)
      chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_PowhegH7_HHbbyy_cHHH01d0_nominal.root").c_str());
    */

    cout << "chain_gg_HH->GetEntries()=" << chain_gg_HH->GetEntries() << endl;
    //    exit(1);
  }
  
  
  if (string_process=="gg_vbf_HH") {

    /*
    cout << "TO CHANGE HERE for Py8" << endl;
    exit(1);
    */
    chain_gg_vbf_HH=new TChain((string("tree_sel_HH_")+string_category).c_str());
  
    if (string_version_MxAOD=="h026") {
      if (do_mc16a) {
	//chain_gg_vbf_HH->Add((string_path_samples+"tree_h026_mc16a_PowhegH7_HHbbyy_cHHH01d0_nominal.root").c_str());
	chain_gg_vbf_HH->Add((string_path_samples+"tree_h026_mc16a_PowhegPy8_HHbbyy_cHHH01d0_nominal.root").c_str());
	chain_gg_vbf_HH->Add((string_path_samples+"tree_h026_mc16a_MGPy8_hh_bbyy_vbf_l1cvv1cv1_nominal.root").c_str());
      }
      if (do_mc16d) {
	//	chain_gg_vbf_HH->Add((string_path_samples+"tree_h026_mc16d_PowhegH7_HHbbyy_cHHH01d0_nominal.root").c_str());
	chain_gg_vbf_HH->Add((string_path_samples+"tree_h026_mc16d_PowhegPy8_HHbbyy_cHHH01d0_nominal.root").c_str());
	chain_gg_vbf_HH->Add((string_path_samples+"tree_h026_mc16d_MGPy8_hh_bbyy_vbf_l1cvv1cv1_nominal.root").c_str());
      }
      if (do_mc16e) {
	//chain_gg_vbf_HH->Add((string_path_samples+"tree_h026_mc16e_PowhegH7_HHbbyy_cHHH01d0_nominal.root").c_str());
	chain_gg_vbf_HH->Add((string_path_samples+"tree_h026_mc16e_PowhegPy8_HHbbyy_cHHH01d0_nominal.root").c_str());
	chain_gg_vbf_HH->Add((string_path_samples+"tree_h026_mc16e_MGPy8_hh_bbyy_vbf_l1cvv1cv1_nominal.root").c_str());
      }
    }
    else {
      cout << "gg HH + vbf HH not available h026 yet" << endl;
      exit(1);
    }
  }
  else if (string_process=="vbf_HH") {

    chain_vbf_HH=new TChain((string("tree_sel_HH_")+string_category).c_str());

    if (string_version_MxAOD=="h026") {
      if (do_mc16a)
	chain_vbf_HH->Add((string_path_samples+"tree_h026_mc16a_MGPy8_hh_bbyy_vbf_l1cvv1cv1_nominal.root").c_str());
      //	chain_vbf_HH->Add((string_path_samples+"tree_h026_mc16a_MGH7_hh_bbyy_vbf_l1cvv1cv1_nominal.root").c_str());
      
      if (do_mc16d)
	chain_vbf_HH->Add((string_path_samples+"tree_h026_mc16d_MGPy8_hh_bbyy_vbf_l1cvv1cv1_nominal.root").c_str());
	//	chain_vbf_HH->Add((string_path_samples+"tree_h026_mc16d_MGH7_hh_bbyy_vbf_l1cvv1cv1_nominal.root").c_str());
      
      if (do_mc16e)
	chain_vbf_HH->Add((string_path_samples+"tree_h026_mc16e_MGPy8_hh_bbyy_vbf_l1cvv1cv1_nominal.root").c_str());
	//chain_vbf_HH->Add((string_path_samples+"tree_h026_mc16e_MGH7_hh_bbyy_vbf_l1cvv1cv1_nominal.root").c_str());
    }
    else {
      cout << "gg HH + vbf HH not available h026 yet" << endl;
      exit(1);
    }
  }
  else if (string_process=="vbf_HH_kappa_lambda_0") {
    
    chain_vbf_HH=new TChain((string("tree_sel_HH_")+string_category).c_str());
    
    if (do_mc16a)
      chain_vbf_HH->Add((string_path_samples+"tree_h026_mc16a_MGPy8_hh_bbyy_vbf_l0cvv1cv1_nominal.root").c_str());
    
    if (do_mc16d)
      chain_vbf_HH->Add((string_path_samples+"tree_h026_mc16d_MGPy8_hh_bbyy_vbf_l0cvv1cv1_nominal.root").c_str());

    if (do_mc16e)
      chain_vbf_HH->Add((string_path_samples+"tree_h026_mc16e_MGPy8_hh_bbyy_vbf_l0cvv1cv1_nominal.root").c_str());
  }
  else if (string_process=="vbf_HH_kappa_lambda_2") {
    
    chain_vbf_HH=new TChain((string("tree_sel_HH_")+string_category).c_str());
    
    if (do_mc16a)
      chain_vbf_HH->Add((string_path_samples+"tree_h026_mc16a_MGPy8_hh_bbyy_vbf_l2cvv1cv1_nominal.root").c_str());
    
    if (do_mc16d)
      chain_vbf_HH->Add((string_path_samples+"tree_h026_mc16d_MGPy8_hh_bbyy_vbf_l2cvv1cv1_nominal.root").c_str());

    if (do_mc16e)
      chain_vbf_HH->Add((string_path_samples+"tree_h026_mc16e_MGPy8_hh_bbyy_vbf_l2cvv1cv1_nominal.root").c_str());
  }
  else if (string_process=="vbf_HH_kappa_lambda_10") {
    
    chain_vbf_HH=new TChain((string("tree_sel_HH_")+string_category).c_str());
    
    if (do_mc16a)
      chain_vbf_HH->Add((string_path_samples+"tree_h026_mc16a_MGPy8_hh_bbyy_vbf_l10cvv1cv1_nominal.root").c_str());
    
    if (do_mc16d)
      chain_vbf_HH->Add((string_path_samples+"tree_h026_mc16d_MGPy8_hh_bbyy_vbf_l10cvv1cv1_nominal.root").c_str());

    if (do_mc16e)
      chain_vbf_HH->Add((string_path_samples+"tree_h026_mc16e_MGPy8_hh_bbyy_vbf_l10cvv1cv1_nominal.root").c_str());
  }

  else if (string_process.find("reweight_mHH_1p0_to_")!=string::npos) {

    string string_expression="reweight_mHH_1p0_to_";
    size_t position_string=string_process.find(string_expression);
    position_string+=string_expression.size();
    
    string string_target_kappa=string_process.substr(position_string);
    
    //    string string_sample="PowhegH7_HHbbyy_reweight_mHH_1p0_to_"+string_target_kappa+"_nominal.root";
    string string_sample="PowhegPy8_HHbbyy_reweight_mHH_1p0_to_"+string_target_kappa+"_nominal.root";
    
    cout << "string_sample=" << string_sample << endl;
    
    chain_gg_HH=new TChain((string("tree_sel_HH_")+string_category).c_str());
    
    if (do_mc16a)
      chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_"+string_sample).c_str());
    if (do_mc16d)
      chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_"+string_sample).c_str());
    if (do_mc16e)
      chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_"+string_sample).c_str());
  }

  else if (string_process=="gg_HH_NLO_kappa_lambda_10") {
    cout << "not ready for h026, and not useful" << endl;
    exit(1);
    chain_gg_HH=new TChain((string("tree_sel_HH_")+string_category).c_str());

    if (do_mc16a)
      chain_gg_HH->Add((string_path_samples+"tree_h025_mc16a_PowhegH7_HHbbyy_cHHH10d0_nominal.root").c_str());
    if (do_mc16d)
      chain_gg_HH->Add((string_path_samples+"tree_h025_mc16d_PowhegH7_HHbbyy_cHHH10d0_nominal.root").c_str());
    if (do_mc16e)
      chain_gg_HH->Add((string_path_samples+"tree_h025_mc16e_PowhegH7_HHbbyy_cHHH10d0_nominal.root").c_str());

  }


  if (string_process=="gg_HH_Full_mc16d") {
    cout << "not ready, update code" << endl;
    exit(1);
    chain_gg_HH=new TChain((string("tree_sel_HH_")+string_category).c_str());
    
    if (do_mc16d)
      chain_gg_HH->Add((string_path_samples+"tree_h025_mc16d_aMCnloHwpp_hh_yybb_nominal.root").c_str());
    
    cout << "chain_gg_HH->GetEntries()=" << chain_gg_HH->GetEntries() << endl;
  }
  
  cout << "phase get Resonant sample" << endl;

  if (string_process.find("gg_X")!=string::npos) {

    chain_gg_HH=new TChain((string("tree_sel_HH_")+string_category).c_str());
    
    if (string_process=="gg_X251") {
      
      if (string_version_MxAOD=="h026") {
	if (do_mc16a)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_MGH7_X251tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16d)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_MGH7_X251tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16e)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_MGH7_X251tohh_bbyy_AF2_nominal.root").c_str());
      }
    }
    else if (string_process=="gg_X260") {
      if (string_version_MxAOD=="h026") {
	if (do_mc16a)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_MGH7_X260tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16d)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_MGH7_X260tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16e)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_MGH7_X260tohh_bbyy_AF2_nominal.root").c_str());
      }
    }

    else if (string_process=="gg_X270") {
      if (string_version_MxAOD=="h026") {
	if (do_mc16a)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_MGH7_X270tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16d)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_MGH7_X270tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16e)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_MGH7_X270tohh_bbyy_AF2_nominal.root").c_str());
      }
    }
    
    else if (string_process=="gg_X280") {
      if (string_version_MxAOD=="h026") {
	if (do_mc16a)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_MGH7_X280tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16d)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_MGH7_X280tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16e)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_MGH7_X280tohh_bbyy_AF2_nominal.root").c_str());
      }
    }
    else if (string_process=="gg_X290") {
      if (string_version_MxAOD=="h026") {
	if (do_mc16a)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_MGH7_X290tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16d)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_MGH7_X290tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16e)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_MGH7_X290tohh_bbyy_AF2_nominal.root").c_str());
      }
    }
    else if (string_process=="gg_X300") {
  
      if (string_version_MxAOD=="h026") {
	if (do_mc16a)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_MGH7_X300tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16d)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_MGH7_X300tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16e)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_MGH7_X300tohh_bbyy_AF2_nominal.root").c_str());
      }
    }
    else if (string_process=="gg_X312.5") {
      if (string_version_MxAOD=="h026") {
	if (do_mc16a)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_MGH7_X3125tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16d)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_MGH7_X3125tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16e)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_MGH7_X3125tohh_bbyy_AF2_nominal.root").c_str());
      }
    }
    else if (string_process=="gg_X325") {

      if (string_version_MxAOD=="h026") {
	if (do_mc16a)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_MGH7_X325tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16d)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_MGH7_X325tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16e)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_MGH7_X325tohh_bbyy_AF2_nominal.root").c_str());
      }
    }
    else if (string_process=="gg_X337.5") {
      if (string_version_MxAOD=="h026") {
	if (do_mc16a)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_MGH7_X3375tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16d)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_MGH7_X3375tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16e)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_MGH7_X3375tohh_bbyy_AF2_nominal.root").c_str());
      }
    }
    else if (string_process=="gg_X350") {
      if (string_version_MxAOD=="h026") {
	if (do_mc16a)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_MGH7_X350tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16d)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_MGH7_X350tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16e)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_MGH7_X350tohh_bbyy_AF2_nominal.root").c_str());
      }
    }
    else if (string_process=="gg_X375") {
      if (string_version_MxAOD=="h026") {
	if (do_mc16a)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_MGH7_X375tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16d)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_MGH7_X375tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16e)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_MGH7_X375tohh_bbyy_AF2_nominal.root").c_str());
      }
    }
    else if (string_process=="gg_X400") {
      if (string_version_MxAOD=="h026") {
	if (do_mc16a)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_MGH7_X400tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16d)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_MGH7_X400tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16e)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_MGH7_X400tohh_bbyy_AF2_nominal.root").c_str());
      }
    }
    else if (string_process=="gg_X425") {
      if (string_version_MxAOD=="h026") {
	if (do_mc16a)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_MGH7_X425tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16d)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_MGH7_X425tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16e)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_MGH7_X425tohh_bbyy_AF2_nominal.root").c_str());
      }
    }
    else if (string_process=="gg_X450") {
      if (string_version_MxAOD=="h026") {
	if (do_mc16a)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_MGH7_X450tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16d)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_MGH7_X450tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16e)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_MGH7_X450tohh_bbyy_AF2_nominal.root").c_str());
      }
    }
    else if (string_process=="gg_X475") {
      if (string_version_MxAOD=="h026") {
	if (do_mc16a)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_MGH7_X475tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16d)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_MGH7_X475tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16e)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_MGH7_X475tohh_bbyy_AF2_nominal.root").c_str());
      }
    }
    else if (string_process=="gg_X500") {
      if (string_version_MxAOD=="h026") {
	if (do_mc16a)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_MGH7_X500tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16d)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_MGH7_X500tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16e)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_MGH7_X500tohh_bbyy_AF2_nominal.root").c_str());
      }
    }
    else if (string_process=="gg_X550") {
      if (string_version_MxAOD=="h026") {
	if (do_mc16a)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_MGH7_X550tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16d)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_MGH7_X550tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16e)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_MGH7_X550tohh_bbyy_AF2_nominal.root").c_str());
      }
    }
    else if (string_process=="gg_X600") {
      if (string_version_MxAOD=="h026") {
	if (do_mc16a)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_MGH7_X600tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16d)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_MGH7_X600tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16e)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_MGH7_X600tohh_bbyy_AF2_nominal.root").c_str());
      }
    }
    else if (string_process=="gg_X700") {
      if (string_version_MxAOD=="h026") {
	if (do_mc16a)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_MGH7_X700tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16d)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_MGH7_X700tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16e)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_MGH7_X700tohh_bbyy_AF2_nominal.root").c_str());
      }
    }
    else if (string_process=="gg_X800") {
      if (string_version_MxAOD=="h026") {
	if (do_mc16a)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_MGH7_X800tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16d)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_MGH7_X800tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16e)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_MGH7_X800tohh_bbyy_AF2_nominal.root").c_str());
      }
    }
    else if (string_process=="gg_X900") {
      if (string_version_MxAOD=="h026") {
	if (do_mc16a)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_MGH7_X900tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16d)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_MGH7_X900tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16e)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_MGH7_X900tohh_bbyy_AF2_nominal.root").c_str());
      }
    }
    else if (string_process=="gg_X1000") {
      if (string_version_MxAOD=="h026") {
      	if (do_mc16a)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_MGH7_X1000tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16d)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_MGH7_X1000tohh_bbyy_AF2_nominal.root").c_str());
	if (do_mc16e)
	  chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_MGH7_X1000tohh_bbyy_AF2_nominal.root").c_str());
      }
    }
    else if (string_process=="gg_X2000") {
      if (do_mc16a)
	chain_gg_HH->Add((string_path_samples+"tree_h025_mc16a_MGH7_X2000tohh_bbyy_AF2_nominal.root").c_str());
      if (do_mc16d)
	chain_gg_HH->Add((string_path_samples+"tree_h025_mc16d_MGH7_X2000tohh_bbyy_AF2_nominal.root").c_str());
      if (do_mc16e)
	chain_gg_HH->Add((string_path_samples+"tree_h025_mc16e_MGH7_X2000tohh_bbyy_AF2_nominal.root").c_str());
    }
    else if (string_process=="gg_X3000") {
      if (do_mc16a)
	chain_gg_HH->Add((string_path_samples+"tree_h025_mc16a_MGH7_X3000tohh_bbyy_AF2_nominal.root").c_str());
      if (do_mc16d)
	chain_gg_HH->Add((string_path_samples+"tree_h025_mc16d_MGH7_X3000tohh_bbyy_AF2_nominal.root").c_str());
      if (do_mc16e)
	chain_gg_HH->Add((string_path_samples+"tree_h025_mc16e_MGH7_X3000tohh_bbyy_AF2_nominal.root").c_str());
    }
    else if (string_process=="gg_X280_Py8") {
      if (do_mc16a)
	chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_MGPy8_X280tohh_bbyy_AF2_nominal.root").c_str());
      if (do_mc16d)
	chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_MGPy8_X280tohh_bbyy_AF2_nominal.root").c_str());
      if (do_mc16e)
	chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_MGPy8_X280tohh_bbyy_AF2_nominal.root").c_str());
    }
    else if (string_process=="gg_X500_Py8") {
      if (do_mc16a)
	chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_MGPy8_X500tohh_bbyy_AF2_nominal.root").c_str());
      if (do_mc16d)
	chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_MGPy8_X500tohh_bbyy_AF2_nominal.root").c_str());
      if (do_mc16e)
	chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_MGPy8_X500tohh_bbyy_AF2_nominal.root").c_str());
    }
    else if (string_process=="gg_X1000_Py8") {
      if (do_mc16a)
	chain_gg_HH->Add((string_path_samples+"tree_h026_mc16a_MGPy8_X1000tohh_bbyy_AF2_nominal.root").c_str());
      if (do_mc16d)
	chain_gg_HH->Add((string_path_samples+"tree_h026_mc16d_MGPy8_X1000tohh_bbyy_AF2_nominal.root").c_str());
      if (do_mc16e)
	chain_gg_HH->Add((string_path_samples+"tree_h026_mc16e_MGPy8_X1000tohh_bbyy_AF2_nominal.root").c_str());
    }
  }

  cout << "ReturnSample, phase 9" << endl;
  
  //  cout << "chain_gg_HH->GetEntries()=" << chain_gg_HH->GetEntries() << endl;
  cout << "phase B" << endl;

  cout << "ReturnSample, phase 10" << endl;

  TChain *chain_process=new TChain((string("tree_sel_HH_")+string_category).c_str());
  
  cout << "string_process=" << string_process << endl;

  if (string_process=="gg_vbf_HH")
    chain_process->Add(chain_gg_vbf_HH);

  else if (string_process=="PowhegPy8_HHbbyy_cHHH01d0" || string_process=="PowhegPy8_HHbbyy_cHHH01d0_train_events" || string_process=="PowhegPy8_HHbbyy_cHHH01d0_public_test_events" || string_process=="PowhegPy8_HHbbyy_cHHH01d0_private_test_events") {
    chain_process->Add(chain_gg_HH);
  }

  else if (string_process=="gg_HH" || string_process=="gg_HH_NLO") {
    cout << "enter here" << endl;

    cout << "chain_gg_HH->GetEntries()=" << chain_gg_HH->GetEntries() << endl;

    chain_process->Add(chain_gg_HH);

    cout << "chain_process->GetEntries()=" << chain_process->GetEntries() << endl;

  }
  else if (string_process=="vbf_HH")
    chain_process->Add(chain_vbf_HH);

  else if (string_process=="vbf_HH_kappa_lambda_0")
    chain_process->Add(chain_vbf_HH);
  else if (string_process=="vbf_HH_kappa_lambda_2")
    chain_process->Add(chain_vbf_HH);
  else if (string_process=="vbf_HH_kappa_lambda_10")
    chain_process->Add(chain_vbf_HH);
  
  else if (string_process=="SingleHiggs") {
    if (string_version_MxAOD=="h026") {
      chain_process->Add(chain_ggH);
      chain_process->Add(chain_VBF);
      
      chain_process->Add(chain_qqZH);
      chain_process->Add(chain_ggZH);
      
      chain_process->Add(chain_ttH);
      
      chain_process->Add(chain_tHjb);
      //-----
      chain_process->Add(chain_WH);
      chain_process->Add(chain_bbH);
      chain_process->Add(chain_tWH);

      cout << "chain_process->GetEntries()=" << chain_process->GetEntries() << endl;
    }
  }
  else if (string_process=="gg_HH_NLO_plus_SingleHiggs") {
    chain_process->Add(chain_ggH);
    chain_process->Add(chain_VBF);
    
    chain_process->Add(chain_qqZH);
    chain_process->Add(chain_ggZH);
    
    chain_process->Add(chain_ttH);

    chain_process->Add(chain_tHjb);

    chain_process->Add(chain_gg_HH);

    chain_process->Add(chain_WH);
    chain_process->Add(chain_bbH);
    chain_process->Add(chain_tWH);
  }
  else if (string_process=="ggH")
    chain_process->Add(chain_ggH);
  else if (string_process=="VBF")
    chain_process->Add(chain_VBF);
  else if (string_process=="WH")
    chain_process->Add(chain_WH);  
  else if (string_process=="ZH") {
    chain_process->Add(chain_qqZH);
    chain_process->Add(chain_ggZH);
  }
  else if (string_process=="ttH")
    chain_process->Add(chain_ttH);
  else if (string_process=="bbH")
    chain_process->Add(chain_bbH);
  
  else if (string_process=="tWH")
    chain_process->Add(chain_tWH);
  else if (string_process=="tHjb")
    chain_process->Add(chain_tHjb);
  
  else {
    if (string_non_resonant_resonant=="non_resonant") {  
      
      if (string_process.find("gg_HH")!=string::npos)
	chain_process->Add(chain_gg_HH);
      
      else if (string_process.find("vbf_HH")!=string::npos)
	chain_process->Add(chain_vbf_HH);
    }
    else if (string_non_resonant_resonant=="resonant") {
      /*
      if (string_process=="gg_vbf_HH")
	chain_process->Add(chain_gg_vbf_HH);
      else
      */
      chain_process->Add(chain_gg_HH);
    }
  }

  cout << "chain_process->GetEntries()=" << chain_process->GetEntries() << endl;

  if (!chain_process) {
    cout << "problem, halt program" << endl;
    exit(1);
  }


  //only for fit stuff (for yield, the modulo is at a different place)  
  //------------------------------------------------------
  if (do_fit_shape && ( (do_consider_public_test || string_process.find("train_events")!=string::npos || string_process.find("public_test_events")!=string::npos) || (do_consider_private_test || string_process.find("private_test_events")!=string::npos) ) ) {

    unsigned long long eventNumber;
    TBranch *b_eventNumber;
    chain_process->SetBranchAddress("eventNumber",&eventNumber,&b_eventNumber);

    chain_process->SetBranchStatus("*",1);
    
    //  https://root-forum.cern.ch/t/skim-events-from-a-tchain-into-a-new-file/9353/2
    //next line
    chain_process->LoadTree(0);

    //shit TChain *chain_process_restriction_test=(TChain *)chain_process->GetTree()->CloneTree(0);
    
    //shit TTree *tree_process_restriction_test=chain_process->CloneTree(0);
    
    cout << "clone tree" << endl;
    
    //next line
    TTree *tree_process_restriction_test=chain_process->GetTree()->CloneTree(0);
    
    int nb_entries=chain_process->GetEntries();
    
    cout << "nb_entries=" << nb_entries << endl;
    
    int counter_destination=0;

    for (int index_entry=0;index_entry<nb_entries;index_entry++) {
      //for (int index_entry=0;index_entry<1;index_entry++) {
      
      Long64_t centry=chain_process->LoadTree(index_entry); //mandatory to move from index_entry to centry with LoadTree, due to presence of several chains, else problems
      if (centry<0)
	continue;
      
      b_eventNumber->GetEntry(centry);
      
      //      cout << "deal with index_entry=" << index_entry << ", centry=" << centry << ", eventNumber=" << eventNumber << endl;
      
      cout << "string_process=" << string_process << endl;
      exit(1);

      if (do_consider_public_test || string_process.find("public_test_events")!=string::npos) {
	//if (eventNumber%4!=2) //restrict to test public
	if (eventNumber%4!=3) //restrict to test private
	  continue;
      }
      else if (do_consider_private_test || string_process.find("private_test_events")!=string::npos) {
	if (eventNumber%4!=3) //restrict to test private
	  continue;
      }      

      else if (string_process.find("train_events")!=string::npos) {
	cout << "RESTRICT" << endl;
	
	if (eventNumber%4!=0 && eventNumber%4!=1) //restrict to test public
	  continue;
      }
      
      //      cout << "phase 1" << endl;
      //      counter_destination++;
      
      //careful for TChain::GetEntry, one should provide the absolute index entry
      //while for branch, one should provide the relative entry
      //https://root.cern.ch/doc/master/classTBranch.html#a4f9c8c55ab275930f2fc2f9262e31f91
      chain_process->GetEntry(index_entry); //index_entry=absolute : mandatory : != branch
      
      tree_process_restriction_test->Fill();
    } //end loop on entries

    /*
    cout << "chain_process->GetEntries()=" << chain_process->GetEntries() << endl;
    cout << "tree_process_restriction_test->GetEntries()=" << tree_process_restriction_test->GetEntries() << endl;
    
    //    tree_process_restriction_test->Scan("eventNumber:m_yy:weight_total");

    //    TChain *chain_process_restriction_test=new TChain((string("tree_sel_HH_")+string_category).c_str());
    //    chain_process_restriction_test->Add(tree_process_restriction_test);
    

    
    TChain *chain_process_restriction_test=(TChain *)tree_process_restriction_test;

    chain_process_restriction_test->SetScanField(0);
    
    cout << "chain_process" << endl;

    chain_process->SetScanField(0);
    chain_process->Scan("eventNumber:m_yy:weight_total");
    
    //shit    chain_process->Scan("eventNumber:m_yy:weight_total","","",kMaxEntries,0);

    cout << endl;
    cout << "chain_process_restriction_test" << endl;
    chain_process_restriction_test->Scan("eventNumber:m_yy:weight_total");
    //shit chain_process_restriction_test->Scan("eventNumber:m_yy:weight_total","","",kMaxEntries,0);

    return chain_process_restriction_test;
    */
    
    //BETTER WOULD BE ADDClone ?
    TChain *chain_process_restriction_test=(TChain *)tree_process_restriction_test;
    
    /*TChain *chain_process_restriction_test=new TChain((string("tree_sel_HH_")+string_category).c_str());

    cout << "tree_process_restriction_test->GetEntries()=" << tree_process_restriction_test->GetEntries() << endl;

    chain_process_restriction_test->AddClone(tree_process_restriction_test);
    
    cout << "chain_process_restriction_test->GetEntries()=" << chain_process_restriction_test->GetEntries() << endl;
    */

    return chain_process_restriction_test;
    
  } //end case restriction of sample
  
  return chain_process;
}
//===========================================================================================================
