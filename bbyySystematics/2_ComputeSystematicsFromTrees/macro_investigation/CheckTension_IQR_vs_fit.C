int CheckTension_IQR_vs_fit()
{
  string m_string_observable_shape="m_yy";

  string string_path="/sps/atlas/e/escalier/ATLAS_HGam/";
  //  string string_rel_path_shape="Outputs_syst_h025_shape_Run2/";
  
  string string_rel_path_shape="Outputs_syst_shape_Run2/";

  //  string string_category="Inclusive";
  string string_category="XGBoost_btag77_withTop_BCal_tightScore_HMass";
  //  string string_MxAOD="h025_mc16d";
  string string_MxAOD="h025_mc16a_h025_mc16d_h025_mc16e";
  //string string_process="aMCnloHwpp_hh_yybb";
  //  string string_process="HH_non_resonant_kappa_lambda_01";
  string string_process="SingleHiggs";
  string string_systematic="EG_RESOLUTION_ALL";
  string suffix_asymmetry_systematic="__1up";
  
  string string_results_tree="tree_";
  string_results_tree+=string_category;
  string_results_tree+="_";
  string_results_tree+=string_MxAOD;
  string_results_tree+="_";
  string_results_tree+=string_process;
  string_results_tree+="_";
  string_results_tree+=string_systematic;
  string_results_tree+=suffix_asymmetry_systematic;
  
  TChain *chain_results_toys_IQR=new TChain(string_results_tree.c_str());
  TChain *chain_results_toys_fit=new TChain(string_results_tree.c_str());
  
  //--------------------
  string string_results_toys=string_path;
  string_results_toys+=string_rel_path_shape;
  string_results_toys+="results_toys/";
  
  string_results_toys+=string_process;
  string_results_toys+="/";
  string_results_toys+=string_MxAOD;
  string_results_toys+="/";
  string_results_toys+=string_category;
  string_results_toys+="/";
  string_results_toys+=m_string_observable_shape;
  string_results_toys+="/";
  string_results_toys+=string_systematic;
  string_results_toys+="/";


  /*
  string_results_toys+=m_string_observable_shape;
  string_results_toys+="/";
  string_results_toys+=string_category;
  string_results_toys+="/";
  string_results_toys+=string_MxAOD;
  string_results_toys+="/";
  string_results_toys+=string_process;
  string_results_toys+="/";
  string_results_toys+=string_systematic;
  string_results_toys+="/";
  */

  string string_results_toys_IQR=string_results_toys;
  string string_results_toys_fit=string_results_toys;
  
  string_results_toys_IQR+="ShapeFrom_mean_interquartile_";
  string_results_toys_fit+="ShapeFrom_fit_";

  string_results_toys_IQR+=string_category;
  string_results_toys_IQR+="_";
  string_results_toys_IQR+=string_MxAOD;
  string_results_toys_IQR+="_";
  string_results_toys_IQR+=string_process;
  string_results_toys_IQR+="_";
  
  string_results_toys_IQR+=string_systematic;
  string_results_toys_IQR+=suffix_asymmetry_systematic;
  
  string_results_toys_IQR+="_range_toys_";
  string_results_toys_IQR+="*.root";

  string_results_toys_fit+=string_category;
  string_results_toys_fit+="_";
  string_results_toys_fit+=string_MxAOD;
  string_results_toys_fit+="_";
  string_results_toys_fit+=string_process;
  string_results_toys_fit+="_";
  
  string_results_toys_fit+=string_systematic;
  string_results_toys_fit+=suffix_asymmetry_systematic;
  
  string_results_toys_fit+="_range_toys_";
  string_results_toys_fit+="*.root";

  cout << "string_results_toys_IQR=" << string_results_toys_IQR << endl;
  cout << "string_results_toys_fit=" << string_results_toys_fit << endl;
  
  //  chain_results_toys_fit->Add(string_results_toys_fit.c_str());
  
  //shit  chain_results_toys_fit->Add("/sps/atlas/e/escalier/ATLAS_HGam/Outputs_syst_h025_shape_Run2/results_toys/m_yy/Inclusive/h025_mc16d/aMCnloHwpp_hh_yybb/EG_RESOLUTION_ALL/ShapeFrom_fit_Inclusive_h025_mc16d_aMCnloHwpp_hh_yybb_EG_RESOLUTION_ALL__1up_range_toys_0_100.root");
  
  cout << "string_results_toys_fit=" << string_results_toys_fit << endl;
  cout << "string_results_toys_IQR=" << string_results_toys_IQR << endl;
  chain_results_toys_fit->Add(string_results_toys_fit.c_str());

  //string_results_toys_fit.c_str());
  chain_results_toys_IQR->Add(string_results_toys_IQR.c_str());

  cout << "entries=" << chain_results_toys_fit->GetEntries() << endl;
  cout << "entries=" << chain_results_toys_IQR->GetEntries() << endl;
  
  int index_toy_IQR; int index_toy_fit;
  TBranch *b_index_toy_IQR; TBranch *b_index_toy_fit;
  
  chain_results_toys_fit->SetBranchAddress("index_toy",&index_toy_fit,&b_index_toy_fit);
  chain_results_toys_IQR->SetBranchAddress("index_toy",&index_toy_IQR,&b_index_toy_IQR);
  
  int converged_fit;
  TBranch *b_converged_fit;
  
  chain_results_toys_fit->SetBranchAddress("converged",&converged_fit,&b_converged_fit);
  
  //  chain_results_toys_fit->Print();
  //  exit(1);

  double rel_effect_position_shape_IQR;
  TBranch *b_rel_effect_position_shape_IQR;
  chain_results_toys_IQR->SetBranchAddress("rel_effect_position_shape",&rel_effect_position_shape_IQR,&b_rel_effect_position_shape_IQR);

  double rel_effect_position_shape_fit;
  TBranch *b_rel_effect_position_shape_fit;
  chain_results_toys_fit->SetBranchAddress("rel_effect_position_shape",&rel_effect_position_shape_fit,&b_rel_effect_position_shape_fit);
  
  double rel_effect_spread_shape_IQR;
  TBranch *b_rel_effect_spread_shape_IQR;
  chain_results_toys_IQR->SetBranchAddress("rel_effect_spread_shape",&rel_effect_spread_shape_IQR,&b_rel_effect_spread_shape_IQR);

  double rel_effect_spread_shape_fit;
  TBranch *b_rel_effect_spread_shape_fit;
  chain_results_toys_fit->SetBranchAddress("rel_effect_spread_shape",&rel_effect_spread_shape_fit,&b_rel_effect_spread_shape_fit);
  
  int nb_entries=chain_results_toys_fit->GetEntries(); //this is the most restrictve of the two scenarios, since it has the convergence status
		    
  cout << "nb_entries=" << nb_entries << endl;
  
  int nb_toys_converged=0;
  int nb_toys_done=0;

  TH1D *hist_delta_position=new TH1D("hist_delta_position","hist_delta_position",30,-15,15);
  TH1D *hist_delta_spread=new TH1D("hist_delta_spread","hist_delta_spread",30,-15,15);
  
  for (int index_entry=0;index_entry<nb_entries;index_entry++) {
    
    Long64_t centry_fit=chain_results_toys_fit->LoadTree(index_entry); //mandatory to move from index_entry to centry_fit with LoadTree, due to presence of several chains, else problem (else need to do Hadd, either in line command, or dynamically in the program
    if (centry_fit<0)
      continue;
    
    b_converged_fit->GetEntry(centry_fit);
    
    nb_toys_done++;
    
    /*
    if (!converged_fit)
      continue;
    */

    nb_toys_converged++;
    
    Long64_t centry_IQR=chain_results_toys_IQR->LoadTree(index_entry); //mandatory to move from index_entry to centry_fit with LoadTree, due to presence of several chains, else problem (else need to do Hadd, either in line command, or dynamically in the program
    if (centry_IQR<0)
      continue;
    

    b_index_toy_fit->GetEntry(centry_fit);
    b_index_toy_IQR->GetEntry(centry_IQR);
    




    b_rel_effect_position_shape_fit->GetEntry(centry_fit);
    b_rel_effect_spread_shape_fit->GetEntry(centry_fit);
    
    b_rel_effect_position_shape_IQR->GetEntry(centry_IQR);
    b_rel_effect_spread_shape_IQR->GetEntry(centry_IQR);
    
        cout << "index_toy_fit=" << index_toy_fit << ", index_toy_IQR=" << index_toy_IQR << endl;

    if (index_toy_fit!=index_toy_IQR) {
      cout << "index_toy_fit=" << index_toy_fit << ", index_toy_IQR=" << index_toy_IQR << endl;

      cout << "problem" << endl;
      exit(1);
    }
    
    hist_delta_position->Fill(rel_effect_position_shape_IQR-rel_effect_position_shape_fit);
    hist_delta_spread->Fill(rel_effect_spread_shape_IQR-rel_effect_spread_shape_fit);
  }    
  
  TCanvas *canvas=new TCanvas("canvas","canvas",800,600);
  
  hist_delta_spread->Draw();
  
  string string_canvas=m_string_observable_shape;
  
  string_canvas+=string_MxAOD;
  
  string_canvas+="_";
  string_canvas+=string_process;
  string_canvas+="_";
  string_canvas+=string_systematic;
  string_canvas+="_";
  string_canvas+=suffix_asymmetry_systematic;
  string_canvas+="_";
  string_canvas+=string_process;
  string_canvas+="_";
  string_canvas+=string_category;
  //  string_canvas+=".root";
  string_canvas+=".png";
  canvas->SaveAs(string_canvas.c_str());
  
  return 0;
}
