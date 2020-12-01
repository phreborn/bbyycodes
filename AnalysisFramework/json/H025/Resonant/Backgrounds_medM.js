{
  "sequencer":["VariablePlotter"],

    
    "directories":{
        "mc16a" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/mc16a/",
        "mc16d" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/mc16d/",
        "mc16e" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/mc16e/"

    },

    "variables":{
        "m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 30,"lbins" : 102,"ubins" : 162}},
        "N_j" :{"var": "HGamEventInfoAuxDyn.N_j","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "N_j_central" :{"var": "HGamEventInfoAuxDyn.N_j_central","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
	"m_jj" :{"var":"HGamEventInfoAuxDyn.yybb_m_jj*0.001","bins":{"nbins" : 20,"lbins" : 25,"ubins" : 225}},
        "m_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj*0.001","bins":{"nbins" : 25,"lbins" : 300,"ubins" : 800}},
        "m_yyjj_cnstrnd" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_cnstrnd*0.001","bins":{"nbins" : 25,"lbins" : 300,"ubins" : 800}},
        "m_yyjj_tilde" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_tilde*0.001","bins":{"nbins" : 25,"lbins" : 300,"ubins" : 800}},
	"deltaR_yy" :{"var": "HGamEventInfoAuxDyn.yybb_deltaR_yy","bins":{"nbins" : 20,"lbins" : 0,"ubins" : 5}},
        "deltaR_jj" :{"var": "HGamEventInfoAuxDyn.yybb_deltaR_jj","bins":{"nbins" : 20,"lbins" : 0,"ubins" : 5}},
        "deltaR_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_deltaR_yyjj","bins":{"nbins" : 25,"lbins" : 0,"ubins" : 5}},
        "MET" :{"var": "HGamEventInfoAuxDyn.met_TST*0.001","bins":{"nbins" : 15,"lbins" : 0,"ubins" : 150}},        
        "pT_jj" :{"var":"HGamEventInfoAuxDyn.pT_jj","bins":{"nbins" : 30,"lbins" : 50000,"ubins" : 350000}},
        "pT_yy" :{"var":"HGamEventInfoAuxDyn.pT_yy","bins":{"nbins" : 30,"lbins" : 50000,"ubins" : 350000}}


   },

    "selections": {
  
	"weight" : "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",
 
	
        "Resonant_BDT_450" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_btag77_85_BCal_resonant_score_yy +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_btag77_85_BCal_resonant_score_ttH+1)/2,2) ) > 0.85 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((445.429-2*13.3727)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((445.429+2*13.3727)*1000))",


        "Resonant_BDT_500" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_btag77_85_BCal_resonant_score_yy +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_btag77_85_BCal_resonant_score_ttH+1)/2,2) ) > 0.80 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((494.862-2*15.0873)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((494.862+2*15.0873)*1000))",

        "Resonant_BDT_550" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_btag77_85_BCal_resonant_score_yy +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_btag77_85_BCal_resonant_score_ttH+1)/2,2) ) > 0.65 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((544.569-2*16.507)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((544.569+2*16.507)*1000))",


        "Resonant_BDT_600" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_btag77_85_BCal_resonant_score_yy +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_btag77_85_BCal_resonant_score_ttH+1)/2,2) ) > 0.50 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((594.803-2*17.6)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((594.803+2*17.6)*1000))"
    
 
    },

  

    "lumi" : {
	
	"mc16a" : 36209.04,
	"mc16d" : 44385.7,
	"mc16e" : 58450.1
    },

    "samples" : {
	
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
		"mc16a" : "mc16a.MGPy8_ttgammagamma_noallhad.root",
		"mc16d" : "mc16d.MGPy8_ttgammagamma_noallhad.root",
		"mc16e" : "mc16e.MGPy8_ttgammagamma_noallhad.root"
            },
            "histoName" : "CutFlow_MGPy8_ttgammagamma_noallhad_AF2_noDalitz_weighted"
	},

	"ttyy_had":       {
            "datafiles" : {
		"mc16a" : "mc16a.MGPy8_ttgammagamma_allhad.root",
		"mc16d" : "mc16d.MGPy8_ttgammagamma_allhad.root",
		"mc16e" : "mc16e.MGPy8_ttgammagamma_allhad.root"
            },
            "histoName" : "CutFlow_MGPy8_ttgammagamma_allhad_AF2_noDalitz_weighted"
	}
	
    }
    
}
