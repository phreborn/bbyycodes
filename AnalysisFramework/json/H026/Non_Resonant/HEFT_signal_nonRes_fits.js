{
  "sequencer":["YieldCalculator","VariablePlotter"],

    "name":{
        "yields" : "HEFT_BM_HH_nonres_efficiencies"
    },

    "reweight":{
	"SM" : "HEFT_weight.BM_SM",
	"BM_1" : "HEFT_weight.BM_1",
	"BM_2" : "HEFT_weight.BM_2",
        "BM_3" : "HEFT_weight.BM_3",
        "BM_4" : "HEFT_weight.BM_4",
        "BM_5" : "HEFT_weight.BM_5",
        "BM_6" : "HEFT_weight.BM_6",
        "BM_7" : "HEFT_weight.BM_7",
        "CMS_BM_1" : "HEFT_weight.CMS_BM_1",
        "CMS_BM_2" : "HEFT_weight.CMS_BM_2",
        "CMS_BM_3" : "HEFT_weight.CMS_BM_3",
        "CMS_BM_4" : "HEFT_weight.CMS_BM_4",
        "CMS_BM_5" : "HEFT_weight.CMS_BM_5",
        "CMS_BM_6" : "HEFT_weight.CMS_BM_6",
        "CMS_BM_7" : "HEFT_weight.CMS_BM_7",
        "CMS_BM_8" : "HEFT_weight.CMS_BM_8",
        "CMS_BM_9" : "HEFT_weight.CMS_BM_9",
        "CMS_BM_10" : "HEFT_weight.CMS_BM_10",
        "CMS_BM_11" : "HEFT_weight.CMS_BM_11",
        "CMS_BM_12" : "HEFT_weight.CMS_BM_12"
    },
 
    "directories": {
	"mc16a": "root://eosatlas.cern.ch//eos/user/l/lapereir/HH/Signals/H26/diphotonsel/HEFT_reweighted/",
	"mc16d": "root://eosatlas.cern.ch//eos/user/l/lapereir/HH/Signals/H26/diphotonsel/HEFT_reweighted/",
	"mc16e": "root://eosatlas.cern.ch//eos/user/l/lapereir/HH/Signals/H26/diphotonsel/HEFT_reweighted/"
  },

  "dumper": {
    "mc16a": true,
    "mc16d": true,
    "mc16e": true
  },

  "variables": {
    "m_yy": {
      "var": "HGamEventInfoAuxDyn.m_yy*0.001",
      "bins": {
        "nbins": 55,
        "lbins": 105,
        "ubins": 160
      }	
    },

    "m_jj": {
	"var": "HGamEventInfoAuxDyn.yybb_m_jj*0.001",
	"bins": {
            "nbins": 60,
            "lbins": 0,
            "ubins": 300
	}
    },
      
    "weight": {
	"var": "HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*FJvt",
	"bins": {
            "nbins": 200,
            "lbins": -10,
            "ubins": 10
	}
    }
  },

  "selections": {

    "weight": "HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*HGamEventInfoAuxDyn.weightFJvt",

    "tight_HMass": "(HGamEventInfoAuxDyn.isPassed == 1 &&  HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 1) && HGamEventInfoAuxDyn.m_yy*0.001 > 105 && HGamEventInfoAuxDyn.m_yy*0.001 < 160) ",

    "loose_HMass": "(HGamEventInfoAuxDyn.isPassed == 1 &&  HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 2) && HGamEventInfoAuxDyn.m_yy*0.001 > 105 && HGamEventInfoAuxDyn.m_yy*0.001 < 160)   ",

    "tight_LMass": "(HGamEventInfoAuxDyn.isPassed == 1 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix]  && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 3) && HGamEventInfoAuxDyn.m_yy*0.001 > 105 && HGamEventInfoAuxDyn.m_yy*0.001 < 160)   ",

    "loose_LMass": "(HGamEventInfoAuxDyn.isPassed == 1 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix]  && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 4) && HGamEventInfoAuxDyn.m_yy*0.001 > 105 && HGamEventInfoAuxDyn.m_yy*0.001 < 160)   "
  },

  "lumi": {
    "mc16a": 36207.66,
    "mc16d": 44307.4,
    "mc16e": 58450.1
  },


  "samples": {
    "HH": {
      "datafiles": {
        "mc16a": "mc16a.PowhegH7_HHbbyy_cHHH01d0.root",
        "mc16d": "mc16d.PowhegH7_HHbbyy_cHHH01d0.root",
        "mc16e": "mc16e.PowhegH7_HHbbyy_cHHH01d0.root"
      },
      "histoName": "CutFlow_PowhegH7_HHbbyy_cHHH01d0_noDalitz_weighted"
    }
  }
}
