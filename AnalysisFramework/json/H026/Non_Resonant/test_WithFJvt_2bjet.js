{
  "sequencer":["VariablePlotter"],

    "directories":{
      "mc16a" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h026_diphotonselection/mc16a/"
    },

   "dumper":{

       "mc16a" : false

    },



    "variables":{
        "m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 55,"lbins" : 105,"ubins" : 160}},
        "N_j" :{"var": "HGamEventInfoAuxDyn.N_j","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "N_j_central" :{"var": "HGamEventInfoAuxDyn.N_j_central","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "m_jj" :{"var":"HGamEventInfoAuxDyn.yybb_m_jj*0.001","bins":{"nbins" : 60,"lbins" : 0,"ubins" : 300}},
        "m_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj*0.001","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 1600}},
        "m_yyjj_cnstrnd" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_cnstrnd*0.001","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 1600}},
        "m_yyjj_tilde" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_tilde*0.001","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 1600}},
        "weight" : {"var": "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*HGamEventInfoAuxDyn.weightFJvt", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10} }

    },

    "selections": {

      "weight" : "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*HGamEventInfoAuxDyn.weightFJvt",

      "XGBoost_btag77_withTop_BCal_tightScore_HMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 &&  HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 1))   ",

      "XGBoost_btag77_withTop_BCal_looseScore_HMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 &&  HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 2))   ",

      "XGBoost_btag77_withTop_BCal_tightScore_LMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix]  && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 3))   ",

      "XGBoost_btag77_withTop_BCal_looseScore_LMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix]  && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 4))   "                                                                                                                                                                

   },

    "lumi" : {
      "mc16a" : 36209.04
    },

    "samples" : {


      "HH":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegH7_HHbbyy_cHHH01d0.root"
        },
        "histoName": "CutFlow_PowhegH7_HHbbyy_cHHH01d0_noDalitz_weighted"
      }


     }
}
