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
    "m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 25,"lbins" : 105,"ubins" : 160}},
    "N_j" :{"var": "HGamEventInfoAuxDyn.N_j","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
    "N_j_central" :{"var": "HGamEventInfoAuxDyn.N_j_central","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
    "m_jj" :{"var":"HGamEventInfoAuxDyn.yybb_m_jj*0.001","bins":{"nbins" : 30,"lbins" : 0,"ubins" : 300}},
    "m_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj*0.001","bins":{"nbins" : 40,"lbins" : 200,"ubins" : 1400}},
    "m_yyjj_cnstrnd" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_cnstrnd*0.001","bins":{"nbins" : 40,"lbins" : 200,"ubins" : 1400}},
    "m_yyjj_tilde" :{"var": "HGamEventInfoAuxDyn.yybb_BCal_m_yyjj_tilde*0.001","bins":{"nbins" : 40,"lbins" : 200,"ubins" : 1400}},
    "nonRes_XGBoost_btag77_BCal_withTop_lowMass_Score" :{"var": "HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_withTop_lowMass_Score","bins":{"nbins" : 50,"lbins" : 0,"ubins" : 1}},
    "nonRes_XGBoost_btag77_BCal_withTop_highMass_Score" :{"var": "HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_withTop_highMass_Score","bins":{"nbins" : 50,"lbins" : 0,"ubins" : 1}}

  },

  "selections": 
  { 
    "Pass_yy"    : "HGamEventInfoAuxDyn.isPassedRelPtCuts == 1 && HGamEventInfoAuxDyn.isPassedMassCut == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[0] == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[1] == 1 && HGamPhotonsAuxDyn.isTight[0] == 0 && HGamPhotonsAuxDyn.isTight[1] == 0",
    "Validation" : "HGamEventInfoAuxDyn.isPassedRelPtCuts == 1 && HGamEventInfoAuxDyn.isPassedMassCut == 1 && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[0] == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[1] == 1 && HGamPhotonsAuxDyn.isTight[0] == 0 && HGamPhotonsAuxDyn.isTight[1] == 0",
    "Validation_2bjet"    : "(HGamEventInfoAuxDyn.isPassedRelPtCuts == 1 && HGamEventInfoAuxDyn.isPassedMassCut == 1 && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[0] == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[1] == 1 && HGamPhotonsAuxDyn.isTight[0] == 0 && HGamPhotonsAuxDyn.isTight[1] == 0 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] )",
    "XGBoost_btag77_withTop_BCal_tightScore_HMass"    : "(HGamEventInfoAuxDyn.isPassedRelPtCuts == 1 && HGamEventInfoAuxDyn.isPassedMassCut == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[0] == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[1] == 1 && HGamPhotonsAuxDyn.isTight[0] == 0 && HGamPhotonsAuxDyn.isTight[1] == 0  && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 1))   ",
    "XGBoost_btag77_withTop_BCal_looseScore_HMass"    : "(HGamEventInfoAuxDyn.isPassedRelPtCuts == 1 && HGamEventInfoAuxDyn.isPassedMassCut == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[0] == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[1] == 1 && HGamPhotonsAuxDyn.isTight[0] == 0 && HGamPhotonsAuxDyn.isTight[1] == 0  && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 2))   ",
    "XGBoost_btag77_withTop_BCal_tightScore_LMass"    : "(HGamEventInfoAuxDyn.isPassedRelPtCuts == 1 && HGamEventInfoAuxDyn.isPassedMassCut == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[0] == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[1] == 1 && HGamPhotonsAuxDyn.isTight[0] == 0 && HGamPhotonsAuxDyn.isTight[1] == 0  && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix]  && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 3))   ",
    "XGBoost_btag77_withTop_BCal_looseScore_LMass"    : "(HGamEventInfoAuxDyn.isPassedRelPtCuts == 1 && HGamEventInfoAuxDyn.isPassedMassCut == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[0] == 1 && HGamPhotonsAuxDyn.isIsoFixedCutLoose[1] == 1 && HGamPhotonsAuxDyn.isTight[0] == 0 && HGamPhotonsAuxDyn.isTight[1] == 0  && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix]  && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 4))   "                                                                                                                                                                
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
      "histoName": "15_to_18_data_jj"
    }


  }

}
