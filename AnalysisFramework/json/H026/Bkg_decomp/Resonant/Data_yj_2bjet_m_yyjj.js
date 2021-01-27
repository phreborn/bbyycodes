{
  "sequencer":["DataAnalysis"],

  "directories":
  {
    "data1" :"root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h026_diphotonpreselection/data/",
    "data2" :"root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h026_diphotonpreselection/data/",
    "data3" :"root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h026_diphotonpreselection/data/"

  },

  "dumper":
  {
    "data1" : false,
    "data2" : false,
    "data3" : false
  },

  "variables":
  {
    "m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 55,"lbins" : 105,"ubins" : 160}},
    "N_j" :{"var": "HGamEventInfoAuxDyn.N_j","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
    "N_j_central" :{"var": "HGamEventInfoAuxDyn.N_j_central","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
    "m_jj" :{"var":"HGamEventInfoAuxDyn.yybb_m_jj*0.001","bins":{"nbins" : 60,"lbins" : 0,"ubins" : 300}},
    "m_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj*0.001","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 1600}},
    "m_yyjj_cnstrnd" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_cnstrnd*0.001","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 1600}},
    "m_yyjj_tilde" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_tilde*0.001","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 1600}}

  },

  "selections": 
  {
"X260toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.isPassedRelPtCuts == 1 && HGamEventInfoAuxDyn.isPassedMassCut == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[0] == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[1] == 1 && ( ( HGamPhotonsAuxDyn.isTight[0] ==1 && HGamPhotonsAuxDyn.isTight[1] == 0) || ( HGamPhotonsAuxDyn.isTight[0] ==0 && HGamPhotonsAuxDyn.isTight[1] == 1 ) ) && (HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.75) )",
        "X280toHH_BDT_Selection_h026_optimized" : "( HGamEventInfoAuxDyn.isPassedRelPtCuts == 1 && HGamEventInfoAuxDyn.isPassedMassCut == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[0] == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[1] == 1 && ( ( HGamPhotonsAuxDyn.isTight[0] ==1 && HGamPhotonsAuxDyn.isTight[1] == 0) || ( HGamPhotonsAuxDyn.isTight[0] ==0 && HGamPhotonsAuxDyn.isTight[1] == 1 ) ) && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 )",
        "X300toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.isPassedRelPtCuts == 1 && HGamEventInfoAuxDyn.isPassedMassCut == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[0] == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[1] == 1 && ( ( HGamPhotonsAuxDyn.isTight[0] ==1 && HGamPhotonsAuxDyn.isTight[1] == 0) || ( HGamPhotonsAuxDyn.isTight[0] ==0 && HGamPhotonsAuxDyn.isTight[1] == 1 ) ) && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 )",
        "X325toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.isPassedRelPtCuts == 1 && HGamEventInfoAuxDyn.isPassedMassCut == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[0] == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[1] == 1 && ( ( HGamPhotonsAuxDyn.isTight[0] ==1 && HGamPhotonsAuxDyn.isTight[1] == 0) || ( HGamPhotonsAuxDyn.isTight[0] ==0 && HGamPhotonsAuxDyn.isTight[1] == 1 ) ) && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 )",
        "X350toHH_BDT_Selection_h026_optimized" : "( HGamEventInfoAuxDyn.isPassedRelPtCuts == 1 && HGamEventInfoAuxDyn.isPassedMassCut == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[0] == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[1] == 1 && ( ( HGamPhotonsAuxDyn.isTight[0] ==1 && HGamPhotonsAuxDyn.isTight[1] == 0) || ( HGamPhotonsAuxDyn.isTight[0] ==0 && HGamPhotonsAuxDyn.isTight[1] == 1 ) ) && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 )",
        "X400toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.isPassedRelPtCuts == 1 && HGamEventInfoAuxDyn.isPassedMassCut == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[0] == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[1] == 1 && ( ( HGamPhotonsAuxDyn.isTight[0] ==1 && HGamPhotonsAuxDyn.isTight[1] == 0) || ( HGamPhotonsAuxDyn.isTight[0] ==0 && HGamPhotonsAuxDyn.isTight[1] == 1 ) ) && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.8 )",
        "X450toHH_BDT_Selection_h026_optimized" : "( HGamEventInfoAuxDyn.isPassedRelPtCuts == 1 && HGamEventInfoAuxDyn.isPassedMassCut == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[0] == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[1] == 1 && ( ( HGamPhotonsAuxDyn.isTight[0] ==1 && HGamPhotonsAuxDyn.isTight[1] == 0) || ( HGamPhotonsAuxDyn.isTight[0] ==0 && HGamPhotonsAuxDyn.isTight[1] == 1 ) ) && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 )",
        "X500toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.isPassedRelPtCuts == 1 && HGamEventInfoAuxDyn.isPassedMassCut == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[0] == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[1] == 1 && ( ( HGamPhotonsAuxDyn.isTight[0] ==1 && HGamPhotonsAuxDyn.isTight[1] == 0) || ( HGamPhotonsAuxDyn.isTight[0] ==0 && HGamPhotonsAuxDyn.isTight[1] == 1 ) ) && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.75 )",
        "X550toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.isPassedRelPtCuts == 1 && HGamEventInfoAuxDyn.isPassedMassCut == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[0] == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[1] == 1 && ( ( HGamPhotonsAuxDyn.isTight[0] ==1 && HGamPhotonsAuxDyn.isTight[1] == 0) || ( HGamPhotonsAuxDyn.isTight[0] ==0 && HGamPhotonsAuxDyn.isTight[1] == 1 ) ) &&  HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.6 )",
        "X600toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.isPassedRelPtCuts == 1 && HGamEventInfoAuxDyn.isPassedMassCut == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[0] == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[1] == 1 && ( ( HGamPhotonsAuxDyn.isTight[0] ==1 && HGamPhotonsAuxDyn.isTight[1] == 0) || ( HGamPhotonsAuxDyn.isTight[0] ==0 && HGamPhotonsAuxDyn.isTight[1] == 1 ) ) && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.45 )",
        "X700toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.isPassedRelPtCuts == 1 && HGamEventInfoAuxDyn.isPassedMassCut == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[0] == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[1] == 1 && ( ( HGamPhotonsAuxDyn.isTight[0] ==1 && HGamPhotonsAuxDyn.isTight[1] == 0) || ( HGamPhotonsAuxDyn.isTight[0] ==0 && HGamPhotonsAuxDyn.isTight[1] == 1 ) ) && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.2 )",
        "X800toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.isPassedRelPtCuts == 1 && HGamEventInfoAuxDyn.isPassedMassCut == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[0] == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[1] == 1 && ( ( HGamPhotonsAuxDyn.isTight[0] ==1 && HGamPhotonsAuxDyn.isTight[1] == 0) || ( HGamPhotonsAuxDyn.isTight[0] ==0 && HGamPhotonsAuxDyn.isTight[1] == 1 ) ) && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.1 )",
        "X900toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.isPassedRelPtCuts == 1 && HGamEventInfoAuxDyn.isPassedMassCut == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[0] == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[1] == 1 && ( ( HGamPhotonsAuxDyn.isTight[0] ==1 && HGamPhotonsAuxDyn.isTight[1] == 0) || ( HGamPhotonsAuxDyn.isTight[0] ==0 && HGamPhotonsAuxDyn.isTight[1] == 1 ) ) && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.2 )",
        "X1000toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.isPassedRelPtCuts == 1 && HGamEventInfoAuxDyn.isPassedMassCut == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[0] == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[1] == 1 && ( ( HGamPhotonsAuxDyn.isTight[0] ==1 && HGamPhotonsAuxDyn.isTight[1] == 0) || ( HGamPhotonsAuxDyn.isTight[0] ==0 && HGamPhotonsAuxDyn.isTight[1] == 1 ) ) && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.05 )"

  },

  "lumi": 
  {
    "data1" : 1,
    "data2" : 1,
    "data3" : 1
  },

  "samples": 
  {

"data":
    {
      "datafiles":
      {
        "data1": "data1516.root",
        "data2": "data17.root",
        "data3": "data18.root"
      },
      "histoName": "15_to_18_data_yj"
    }

  }

}
