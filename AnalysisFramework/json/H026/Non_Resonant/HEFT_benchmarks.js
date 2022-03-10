{
  "sequencer":["YieldCalculator"],

    "name":{
        "yields" : "Pub_Note_HEFT_benchmarks_XS_1"
    },

    "reweight":{
	"SM" : "HEFT_weight.BM_SM/HEFT_den_weight.BM_SM",
        "BM_1" : "HEFT_weight.BM_1/HEFT_den_weight.BM_1",
        "BM_2" : "HEFT_weight.BM_2/HEFT_den_weight.BM_2",
        "BM_3" : "HEFT_weight.BM_3/HEFT_den_weight.BM_3",
        "BM_4" : "HEFT_weight.BM_4/HEFT_den_weight.BM_4",
        "BM_5" : "HEFT_weight.BM_5/HEFT_den_weight.BM_5",
        "BM_6" : "HEFT_weight.BM_6/HEFT_den_weight.BM_6",
        "BM_7" : "HEFT_weight.BM_7/HEFT_den_weight.BM_7",
	"kl_10" : "HEFT_weight.kl10/HEFT_den_weight.kl10"

    },
 
    "directories": {
	"mc16a": "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb//HEFT_h026_presel/",
	"mc16d": "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb//HEFT_h026_presel/",
	"mc16e": "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb//HEFT_h026_presel/"
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

        "weight": "HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*HGamEventInfoAuxDyn.weightFJvt*2*0.5809*0.002270",

        "Tight_HM": "(HGamEventInfoAuxDyn.isPassed == 1 &&  HGamEventInfoAuxDyn.yybb_btag77_cutFlow > 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_BCal_Cat/1000) % 10) == 1) && HGamEventInfoAuxDyn.m_yy*0.001 > 105 && HGamEventInfoAuxDyn.m_yy*0.001 < 160) ",

        "Loose_HM": "(HGamEventInfoAuxDyn.isPassed == 1 &&  HGamEventInfoAuxDyn.yybb_btag77_cutFlow > 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_BCal_Cat/1000) % 10) == 2) && HGamEventInfoAuxDyn.m_yy*0.001 > 105 && HGamEventInfoAuxDyn.m_yy*0.001 < 160)   ",

        "Tight_LM": "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow > 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix]  && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_BCal_Cat/1000) % 10) == 3) && HGamEventInfoAuxDyn.m_yy*0.001 > 105 && HGamEventInfoAuxDyn.m_yy*0.001 < 160)   ",

        "Loose_LM": "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow > 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix]  && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_BCal_Cat/1000) % 10) == 4) && HGamEventInfoAuxDyn.m_yy*0.001 > 105 && HGamEventInfoAuxDyn.m_yy*0.001 < 160)   "

  },

  "lumi": {
    "mc16a": 36207.66,
    "mc16d": 44307.4,
    "mc16e": 58450.1
  },


    "samples": {
      "ggF_HH": {
	"datafiles": {
          "mc16a": "mc16a.PowhegPy8_HHbbyy_cHHH01d0.root",
          "mc16d": "mc16d.PowhegPy8_HHbbyy_cHHH01d0.root",
          "mc16e": "mc16e.PowhegPy8_HHbbyy_cHHH01d0.root"
      },
	"histoName": "CutFlow_PowhegPy8_HHbbyy_cHHH01d0_noDalitz_weighted"
    }
  }
}
