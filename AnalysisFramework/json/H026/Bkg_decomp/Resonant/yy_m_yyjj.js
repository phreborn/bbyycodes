{
  "sequencer":["VariablePlotter"],

    "directories":{
      "mc16a" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h026_diphotonselection/mc16a/",
      "mc16d" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h026_diphotonselection/mc16d/",
      "mc16e" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h026_diphotonselection/mc16e/"
    },

    "dumper":{
       "mc16a" : false,
       "mc16d" : false,
       "mc16e" : false
    
    },

    "variables":{
	"m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 55,"lbins" : 105,"ubins" : 160}},
        "N_j" :{"var": "HGamEventInfoAuxDyn.N_j","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "N_j_central" :{"var": "HGamEventInfoAuxDyn.N_j_central","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "m_jj" :{"var":"HGamEventInfoAuxDyn.yybb_m_jj*0.001","bins":{"nbins" : 30,"lbins" : 0,"ubins" : 300}},
        "m_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj*0.001","bins":{"nbins" : 160,"lbins" : 0,"ubins" : 1600}},
        "m_yyjj_cnstrnd" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_cnstrnd*0.001","bins":{"nbins" : 160,"lbins" : 0,"ubins" : 1600}},
        "m_yyjj_tilde" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_tilde*0.001","bins":{"nbins" : 160,"lbins" : 0,"ubins" : 1600}},
        "weight" : {"var": "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*HGamEventInfoAuxDyn.weightFJvt", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10} }

   },

    "selections": {
  
      "weight" : "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*HGamEventInfoAuxDyn.weightFJvt",

	"X260toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.75)",
	
      "X280toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 )",
	"X300toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 )",
	"X325toHH_BDT_Selection_h026_optimized" : "( HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 )",
	"X350toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 )",
	"X400toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.8)",
	 "X450toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 )",
	"X500toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.75)",
	 "X550toHH_BDT_Selection_h026_optimized" : "( HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.6)",
	"X600toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.45 )",
	 "X700toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.2 )",
	"X800toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.1 )",
	"X900toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.2 )",
	"X1000toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.05 )"   
 
 
    },

  

    "lumi" : {
      "mc16a" : 36209.04, 
      "mc16d" : 44385.7,
      "mc16e" : 58450.1
    },

    "samples" : {
	
	 "yy":    {
        "datafiles" : {
          "mc16a" : "mc16a.Sherpa2_diphoton_myy_90_175.root",
          "mc16d" : "mc16d.Sherpa2_diphoton_myy_90_175.root",
          "mc16e" : "mc16e.Sherpa2_diphoton_myy_90_175.root"
        },
        "histoName" : "CutFlow_Sherpa2_myy_90_175_noDalitz_weighted"
      }

}

}
