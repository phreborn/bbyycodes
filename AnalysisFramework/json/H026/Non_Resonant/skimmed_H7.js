{
  "sequencer":["YieldCalculator"],

    "name":{
        "yields" : "Pub_Note_HEFT_HH_H7_skimmed"
    },

    "reweight":{
    },
 
    "directories": {
	"mc16a": "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h026_diphotonselection/mc16a/",
	"mc16d": "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h026_diphotonselection/mc16d/",
	"mc16e": "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h026_diphotonselection/mc16e/"
    },

  "dumper": {
    "mc16a": false,
    "mc16d": false,
    "mc16e": false
  },

  "variables": {
    "m_yy": {
      "var": "HGamEventInfoAuxDyn.m_yy*0.001",
      "bins": {
        "nbins": 55,
        "lbins": 105,
        "ubins": 160
      }
    }

  },

  "selections": {

        "weight": "HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*HGamEventInfoAuxDyn.weightFJvt*HGamEventInfoAuxDyn.crossSectionBRfilterEff",


    "btag77_withTop_BCal_tightScore_HMass": "(HGamEventInfoAuxDyn.isPassed == 1 &&  HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 1))   ",


        "Tight_HM": "(HGamEventInfoAuxDyn.isPassed == 1 &&  HGamEventInfoAuxDyn.yybb_btag77_cutFlow >= 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 1) && HGamEventInfoAuxDyn.m_yy*0.001 > 105 && HGamEventInfoAuxDyn.m_yy*0.001 < 160) ",

        "Loose_HM": "(HGamEventInfoAuxDyn.isPassed == 1 &&  HGamEventInfoAuxDyn.yybb_btag77_cutFlow >= 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 2) && HGamEventInfoAuxDyn.m_yy*0.001 > 105 && HGamEventInfoAuxDyn.m_yy*0.001 < 160)   ",

        "Tight_LM": "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow >=  6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix]  && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 3) && HGamEventInfoAuxDyn.m_yy*0.001 > 105 && HGamEventInfoAuxDyn.m_yy*0.001 < 160)   ",

        "Loose_LM": "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow >= 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix]  && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 4) && HGamEventInfoAuxDyn.m_yy*0.001 > 105 && HGamEventInfoAuxDyn.m_yy*0.001 < 160)   "

  },

  "lumi": {
    "mc16a": 36207.66,
    "mc16d": 44307.4,
    "mc16e": 58450.1
  },


    "samples": {
      "HH_H7": {
	"datafiles": {
          "mc16a": "mc16a.PowhegH7_HHbbyy_cHHH01d0.root",
          "mc16d": "mc16d.PowhegH7_HHbbyy_cHHH01d0.root",
          "mc16e": "mc16e.PowhegH7_HHbbyy_cHHH01d0.root"
      },
	"histoName": "CutFlow_PowhegH7_HHbbyy_cHHH01d0_noDalitz_weighted"
    }
  }
}
