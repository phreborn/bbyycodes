{
    "sequencer":["YieldCalculator"],

    "name":{
        "yields" : "Yields_HEFT_SM"
    },
    
    "directories": {
	"mc16a": "root://eosatlas.cern.ch//eos/user/l/lapereir/HH/HEFT_skimmed_h026/",
	"mc16d": "root://eosatlas.cern.ch//eos/user/l/lapereir/HH/HEFT_skimmed_h026/",
	"mc16e": "root://eosatlas.cern.ch//eos/user/l/lapereir/HH/HEFT_skimmed_h026/"
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

	"weight": "HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*HGamEventInfoAuxDyn.weightFJvt*2*0.5809*0.002270*HEFT_weight.kl1",

	"tight_HMass": "(HGamEventInfoAuxDyn.isPassed == 1 &&  HGamEventInfoAuxDyn.yybb_btag77_cutFlow > 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_BCal_Cat/1000) % 10) == 1) && HGamEventInfoAuxDyn.m_yy*0.001 > 105 && HGamEventInfoAuxDyn.m_yy*0.001 < 160) ",

	"loose_HMass": "(HGamEventInfoAuxDyn.isPassed == 1 &&  HGamEventInfoAuxDyn.yybb_btag77_cutFlow > 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_BCal_Cat/1000) % 10) == 2) && HGamEventInfoAuxDyn.m_yy*0.001 > 105 && HGamEventInfoAuxDyn.m_yy*0.001 < 160)   ",

	"tight_LMass": "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow > 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix]  && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_BCal_Cat/1000) % 10) == 3) && HGamEventInfoAuxDyn.m_yy*0.001 > 105 && HGamEventInfoAuxDyn.m_yy*0.001 < 160)   ",

	"loose_LMass": "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow > 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix]  && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_BCal_Cat/1000) % 10) == 4) && HGamEventInfoAuxDyn.m_yy*0.001 > 105 && HGamEventInfoAuxDyn.m_yy*0.001 < 160)   "
    },

    "lumi": {
	"mc16a": 36207.66,
	"mc16d": 44307.4,
	"mc16e": 58450.1
    },

    "samples": {
	"HH_Py8": {
	    "datafiles": {
		"mc16a": "mc16a.PowhegPy8_HHbbyy_cHHH01d0.root",
		"mc16d": "mc16d.PowhegPy8_HHbbyy_cHHH01d0.root",
		"mc16e": "mc16e.PowhegPy8_HHbbyy_cHHH01d0.root"
	    },
	    "histoName": "SM_sum_weights"
	},

	"HH_kl10_Py8": {
	    "datafiles": {
		"mc16a": "mc16a.PowhegPy8_HHbbyy_cHHH10d0.root",
		"mc16d": "mc16d.PowhegPy8_HHbbyy_cHHH10d0.root",
		"mc16e": "mc16e.PowhegPy8_HHbbyy_cHHH10d0.root"
	    },
	    "histoName": "SM_sum_weights"
	},

	"HH_Pangea_Py8": {
	    "datafiles": {
		"mc16a": "mc16a.Pangea.root",
		"mc16d": "mc16d.Pangea.root",
		"mc16e": "mc16e.Pangea.root"
	    },
	    "histoName": "SM_sum_weights"
	}
    }
}
