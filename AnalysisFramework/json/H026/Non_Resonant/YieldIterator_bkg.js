{
  "sequencer":["YieldCalculator"],

    "directories":{
        "mc16a" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h026_diphotonselection/mc16a/",
        "mc16d" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h026_diphotonselection/mc16d/",
        "mc16e" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h026_diphotonselection/mc16e/"

    },

    "variables":{
	"m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 55,"lbins" : 104,"ubins" : 161}}
   },

    "selections": {
  
        "weight" : "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*HGamEventInfoAuxDyn.weightFJvt",

        "tight_HMass" : "( HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.passCrackVetoCleaning  == 1 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] == 1 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 1) )",
        "loose_HMass" : "( HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.passCrackVetoCleaning  ==  1 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] == 1 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 2) )",
        "tight_LMass" : "( HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.passCrackVetoCleaning  == 1 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] == 1 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 3) )",
        "loose_LMass" : "( HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.passCrackVetoCleaning  == 1 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] == 1 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 4) )"
    },

  

    "lumi" : {
	
	"mc16a" : 36209.04,
	"mc16d" : 44385.7,
	"mc16e" : 58450.1
    },

    "samples" : {
	
	"HH":{
	    "datafiles":{
		"mc16a" : "mc16a.PowhegH7_HHbbyy_cHHH01d0.root",
		"mc16d" : "mc16d.PowhegH7_HHbbyy_cHHH01d0.root",
		"mc16e" : "mc16e.PowhegH7_HHbbyy_cHHH01d0.root"
	    },
	    
	 "histoName" : 	"CutFlow_PowhegH7_HHbbyy_cHHH01d0_noDalitz_weighted"
	},

	"ggH":    {
            "datafiles" : {
		"mc16a" : "mc16a.PowhegPy8_NNLOPS_ggH125.root",
		"mc16d" : "mc16d.PowhegPy8_NNLOPS_ggH125.root",
		"mc16e" : "mc16e.PowhegPy8_NNLOPS_ggH125.root"
            },
            "histoName" : "CutFlow_PowhegPy8_NNLOPS_ggH125_noDalitz_weighted"
	},
	
	"VBF":    {
            "datafiles" : {
		"mc16a" : "mc16a.PowhegPy8EG_NNPDF30_VBFH125.root",
		"mc16d" : "mc16d.PowhegPy8EG_NNPDF30_VBFH125.root",
		"mc16e" : "mc16e.PowhegPy8EG_NNPDF30_VBFH125.root"
            },
            "histoName" : "CutFlow_PowhegPy8EG_NNPDF30_VBFH125_noDalitz_weighted"
	},
	
	"WpH":    {
            "datafiles" : {
		"mc16a" : "mc16a.PowhegPy8_WpH125J.root",
		"mc16d" : "mc16d.PowhegPy8_WpH125J.root",
		"mc16e" : "mc16e.PowhegPy8_WpH125J.root"
            },
            "histoName" : "CutFlow_PowhegPy8_WpH125J_noDalitz_weighted"
	},
	
	"WmH":    {
            "datafiles" : {
		"mc16a" : "mc16a.PowhegPy8_WmH125J.root",
		"mc16d" : "mc16d.PowhegPy8_WmH125J.root",
		"mc16e" : "mc16e.PowhegPy8_WmH125J.root"
            },
            "histoName" : "CutFlow_PowhegPy8_WmH125J_noDalitz_weighted"
	}
	
    }
    
}
