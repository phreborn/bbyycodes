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
        "m_jj" :{"var":"HGamEventInfoAuxDyn.yybb_m_jj*0.001","bins":{"nbins" : 60,"lbins" : 0,"ubins" : 300}},
        "m_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj*0.001","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 1600}},
        "m_yyjj_cnstrnd" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_cnstrnd*0.001","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 1600}},
        "m_yyjj_tilde" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_tilde*0.001","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 1600}},
        "nonRes_XGBoost_btag77_BCal_withTop_lowMass_Score" :{"var": "HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_withTop_lowMass_Score","bins":{"nbins" : 50,"lbins" : 0,"ubins" : 1}},
        "nonRes_XGBoost_btag77_BCal_withTop_highMass_Score" :{"var": "HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_withTop_highMass_Score","bins":{"nbins" : 50,"lbins" : 0,"ubins" : 1}},
        "weight" : {"var": "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*HGamEventInfoAuxDyn.weightFJvt", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10} }
     
    },

    "selections": { 

      "weight" : "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*HGamEventInfoAuxDyn.weightFJvt",
      "Validation_2bjet"    : "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] )",
      "XGBoost_btag77_withTop_BCal_tightScore_HMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 &&  HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 1))   ",
      "XGBoost_btag77_withTop_BCal_looseScore_HMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 &&  HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 2))   ",
      "XGBoost_btag77_withTop_BCal_tightScore_LMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix]  && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 3))   ",
      "XGBoost_btag77_withTop_BCal_looseScore_LMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix]  && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 4))   "                                                                                                                                                                


   },

    "lumi" : {
      "mc16a" : 36209.04,
      "mc16d" : 44385.7,
      "mc16e" : 58450.1
    },

    "samples" : {


      "ttH_PowhegPy8":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8_ttH125_fixweight.root",
          "mc16d" : "mc16d.PowhegPy8_ttH125_fixweight.root",
          "mc16e" : "mc16e.PowhegPy8_ttH125_fixweight.root"
        },
        "histoName" : "CutFlow_PowhegPy8_ttH125_fixweight_noDalitz_weighted"
      },


  "VBFH_PowhegPy8":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8EG_NNPDF30_VBFH125.root",
          "mc16d" : "mc16d.PowhegPy8EG_NNPDF30_VBFH125.root",
          "mc16e" : "mc16e.PowhegPy8EG_NNPDF30_VBFH125.root"
        },
        "histoName" : "CutFlow_PowhegPy8EG_NNPDF30_VBFH125_noDalitz_weighted"
      },



      "ZH_PowhegPy8":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8_ZH125J.root",
          "mc16d" : "mc16d.PowhegPy8_ZH125J.root",
          "mc16e" : "mc16e.PowhegPy8_ZH125J.root"
        },
        "histoName": "CutFlow_PowhegPy8_ZH125J_noDalitz_weighted"
      },
 
       "ggZH_PowhegPy8":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8_ggZH125.root",
          "mc16d" : "mc16d.PowhegPy8_ggZH125.root",
          "mc16e" : "mc16e.PowhegPy8_ggZH125.root"
        },
        "histoName" : "CutFlow_PowhegPy8_ggZH125_noDalitz_weighted"
      },

      "ggH_PowhegPy8":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8_NNLOPS_ggH125.root",
          "mc16d" : "mc16d.PowhegPy8_NNLOPS_ggH125.root",
          "mc16e" : "mc16e.PowhegPy8_NNLOPS_ggH125.root"
        },
        "histoName" : "CutFlow_PowhegPy8_NNLOPS_ggH125_noDalitz_weighted"
      },


      "WmH_PowhegPy8":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8_WmH125J.root",
          "mc16d" : "mc16d.PowhegPy8_WmH125J.root",
          "mc16e" : "mc16e.PowhegPy8_WmH125J.root"
        },
        "histoName" : "CutFlow_PowhegPy8_WmH125J_noDalitz_weighted"
      },


      "WpH_PowhegPy8":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8_WpH125J.root",
          "mc16d" : "mc16d.PowhegPy8_WpH125J.root",
          "mc16e" : "mc16e.PowhegPy8_WpH125J.root"
        },
        "histoName" : "CutFlow_PowhegPy8_WpH125J_noDalitz_weighted"
      }


     
     }

}
