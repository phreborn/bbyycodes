{
  "sequencer":["YieldCalculator"],

    "name":{
	"yields" : "Background_yields"
    },
    
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
 	
        "High_M" : "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && HGamEventInfoAuxDyn.passCrackVetoCleaning  == 1 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] == 1 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] == 1 && (HGamEventInfoAuxDyn.yybb_BCal_m_yyjj - HGamEventInfoAuxDyn.m_yy - HGamEventInfoAuxDyn.yybb_BCal_m_jj + 250e3) > 350e3)",

        "High_M_myySR" : "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && HGamEventInfoAuxDyn.passCrackVetoCleaning  == 1 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] == 1 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] == 1 && (HGamEventInfoAuxDyn.yybb_BCal_m_yyjj - HGamEventInfoAuxDyn.m_yy - HGamEventInfoAuxDyn.yybb_BCal_m_jj + 250e3) > 350e3 && HGamEventInfoAuxDyn.m_yy*0.001 > 120 && HGamEventInfoAuxDyn.m_yy*0.001 < 130)"
 
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
	},

	"ZH":     {
            "datafiles" : {
		"mc16a" : "mc16a.PowhegPy8_ZH125J.root",
		"mc16d" : "mc16d.PowhegPy8_ZH125J.root",
		"mc16e" : "mc16e.PowhegPy8_ZH125J.root"
            },
            "histoName" : "CutFlow_PowhegPy8_ZH125J_noDalitz_weighted"
	},

	"ggZH":   {
            "datafiles" : {
		"mc16a" : "mc16a.PowhegPy8_ggZH125.root",
		"mc16d" : "mc16d.PowhegPy8_ggZH125.root",
		"mc16e" : "mc16e.PowhegPy8_ggZH125.root"
            },
            "histoName" : "CutFlow_PowhegPy8_ggZH125_noDalitz_weighted"
	},
	
	"ttH":    {
            "datafiles" : {
		"mc16a" : "mc16a.PowhegPy8_ttH125_fixweight.root",
		"mc16d" : "mc16d.PowhegPy8_ttH125_fixweight.root",
		"mc16e" : "mc16e.PowhegPy8_ttH125_fixweight.root"
            },
            "histoName" : "CutFlow_PowhegPy8_ttH125_fixweight_noDalitz_weighted"
	},

	"bbH":    {
            "datafiles" : {
		"mc16a" : "mc16a.PowhegPy8_bbH125.root",
		"mc16d" : "mc16d.PowhegPy8_bbH125.root",
		"mc16e" : "mc16e.PowhegPy8_bbH125.root"
            },
            "histoName" : "CutFlow_PowhegPy8_bbH125_noDalitz_weighted"
	},

	"tWH":    {
            "datafiles" : {
		"mc16a" : "mc16a.aMCnloPy8_tWH125.root",
		"mc16d" : "mc16d.aMCnloPy8_tWH125.root",
		"mc16e" : "mc16e.aMCnloPy8_tWH125.root"
            },
            "histoName" : "CutFlow_aMCnloPy8_tWH125_noDalitz_weighted"
	},

	"tHjb":   {
            "datafiles" : {
		"mc16a" : "mc16a.aMCnloPy8_tHjb125_4fl_shw_fix.root",
		"mc16d" : "mc16d.aMCnloPy8_tHjb125_4fl_shw_fix.root",
		"mc16e" : "mc16e.aMCnloPy8_tHjb125_4fl_shw_fix.root"
            },
            "histoName" : "CutFlow_aMCnloPy8_tHjb125_4fl_noDalitz_weighted"
	},

	"ttyy_nohad":     {
            "datafiles" : {
		"mc16a" : "mc16a.MGPy8_ttgammagamma_noallhad_AF2.root",
		"mc16d" : "mc16d.MGPy8_ttgammagamma_noallhad_AF2.root",
		"mc16e" : "mc16e.MGPy8_ttgammagamma_noallhad_AF2.root"
            },
            "histoName" : "CutFlow_MGPy8_ttgammagamma_noallhad_AF2_noDalitz_weighted"
	},

	"ttyy_had":       {
            "datafiles" : {
		"mc16a" : "mc16a.MGPy8_ttgammagamma_allhad_AF2.root",
		"mc16d" : "mc16d.MGPy8_ttgammagamma_allhad_AF2.root",
		"mc16e" : "mc16e.MGPy8_ttgammagamma_allhad_AF2.root"
            },
            "histoName" : "CutFlow_MGPy8_ttgammagamma_allhad_AF2_noDalitz_weighted"
	},

        "yyjj":    {
            "datafiles" : {
		"mc16a" : "mc16a.Sherpa2_diphoton_myy_90_175.root",
		"mc16d" : "mc16d.Sherpa2_diphoton_myy_90_175.root",
                "mc16e" : "mc16e.Sherpa2_diphoton_myy_90_175.root"
            },
            "histoName" : "CutFlow_Sherpa2_myy_90_175_noDalitz_weighted"
        }
	
    }
    
}
