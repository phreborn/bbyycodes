{
  "sequencer":["YieldCalculator"],

    "name":{
	"yields" : "Signal_yields"
    },

    
    "directories":{
        "mc16a" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/mc16a/",
        "mc16d" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/mc16d/",
        "mc16e" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/mc16e/"

    },

    "variables":{
	"m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 55,"lbins" : 105,"ubins" : 160}}
   },

    "selections": {
  
	"weight" : "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",
 
        "Resonant_BDT_260" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.75 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((259.899-2*3.45878)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((259.899+2*3.45878)*1000))",

        "Resonant_BDT_280" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((278.598-2*5.93442)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((278.598+2*5.93442)*1000))",

        "Resonant_BDT_300" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((298.248-2*6.80417)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((298.248+2*6.80417)*1000))",

        "Resonant_BDT_325" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((322.359-2*8.32443)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((322.359+2*8.32443)*1000))",

	
        "Resonant_BDT_350" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((346.891-2*9.42102)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((346.891+2*9.42102)*1000))",

        "Resonant_BDT_400" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((395.797-2*11.7374)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((395.797+2*11.7374)*1000))",
	
        "Resonant_BDT_450" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((445.429-2*13.3727)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((445.429+2*13.3727)*1000))",


        "Resonant_BDT_500" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.80 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((494.862-2*15.0873)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((494.862+2*15.0873)*1000))",

        "Resonant_BDT_550" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.65 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((544.569-2*16.507)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((544.569+2*16.507)*1000))",


        "Resonant_BDT_600" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.50 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((594.803-2*17.6)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((594.803+2*17.6)*1000))",

        "Resonant_BDT_700" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.30 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((694.781-2*19.9737)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((694.781+2*19.9737)*1000))",

	"Resonant_BDT_800" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.25 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((794.196-2*22.3182)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((794.196+2*22.3182)*1000))",

	"Resonant_BDT_900" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.07 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((894.305-2*24.2746)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((894.305+2*24.2746)*1000))",

	"Resonant_BDT_1000" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.10 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((998.186-4*24.2607)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((998.186+4*24.2607)*1000))"

    
 
    },

  

    "lumi" : {
	
	"mc16a" : 36209.04,
	"mc16d" : 44385.7,
	"mc16e" : 58450.1
    },

    "samples" : {
	
	"X260toHH":    {
            "datafiles" : {
		"mc16a" : "mc16a.MGH7_X260tohh_bbyy_AF2.root",
		"mc16d" : "mc16d.MGH7_X260tohh_bbyy_AF2.root",
		"mc16e" : "mc16e.MGH7_X260tohh_bbyy_AF2.root"
	    },
	    "histoName" : "CutFlow_MGH7_X260tohh_bbyy_AF2_noDalitz_weighted"
	},

	"X280toHH":    {
	    "datafiles" : {
		"mc16a" : "mc16a.MGH7_X280tohh_bbyy_AF2.root",
		"mc16d" : "mc16d.MGH7_X280tohh_bbyy_AF2.root",
		"mc16e" : "mc16e.MGH7_X280tohh_bbyy_AF2.root"
	    },
	    "histoName" : "CutFlow_MGH7_X280tohh_bbyy_AF2_noDalitz_weighted"
	},

	"X300toHH":    {
	    "datafiles" : {
		"mc16a" : "mc16a.MGH7_X300tohh_bbyy_AF2.root",
		"mc16d" : "mc16d.MGH7_X300tohh_bbyy_AF2.root",
		"mc16e" : "mc16e.MGH7_X300tohh_bbyy_AF2.root"
	    },
	    "histoName" : "CutFlow_MGH7_X300tohh_bbyy_AF2_noDalitz_weighted"
	},

        "X325toHH":    {
            "datafiles" : {
                "mc16a" : "mc16a.MGH7_X325tohh_bbyy_AF2.root",
                "mc16d" : "mc16d.MGH7_X325tohh_bbyy_AF2.root",
                "mc16e" : "mc16e.MGH7_X325tohh_bbyy_AF2.root"
            },
            "histoName" : "CutFlow_MGH7_X325tohh_bbyy_AF2_noDalitz_weighted"
        },


        "X350toHH":    {
            "datafiles" : {
                "mc16a" : "mc16a.MGH7_X350tohh_bbyy_AF2.root",
                "mc16d" : "mc16d.MGH7_X350tohh_bbyy_AF2.root",
                "mc16e" : "mc16e.MGH7_X350tohh_bbyy_AF2.root"
            },
            "histoName" : "CutFlow_MGH7_X350tohh_bbyy_AF2_noDalitz_weighted"
        },


        "X400toHH":    {
            "datafiles" : {
                "mc16a" : "mc16a.MGH7_X400tohh_bbyy_AF2.root",
                "mc16d" : "mc16d.MGH7_X400tohh_bbyy_AF2.root",
                "mc16e" : "mc16e.MGH7_X400tohh_bbyy_AF2.root"
            },
            "histoName" : "CutFlow_MGH7_X400tohh_bbyy_AF2_noDalitz_weighted"
        },


        "X500toHH":    {
            "datafiles" : {
                "mc16a" : "mc16a.MGH7_X500tohh_bbyy_AF2.root",
                "mc16d" : "mc16d.MGH7_X500tohh_bbyy_AF2.root",
                "mc16e" : "mc16e.MGH7_X500tohh_bbyy_AF2.root"
            },
            "histoName" : "CutFlow_MGH7_X500tohh_bbyy_AF2_noDalitz_weighted"
        },

        "X550toHH":    {
            "datafiles" : {
                "mc16a" : "mc16a.MGH7_X550tohh_bbyy_AF2.root",
                "mc16d" : "mc16d.MGH7_X550tohh_bbyy_AF2.root",
                "mc16e" : "mc16e.MGH7_X550tohh_bbyy_AF2.root"
            },
            "histoName" : "CutFlow_MGH7_X550tohh_bbyy_AF2_noDalitz_weighted"
        },

        "X600toHH":    {
            "datafiles" : {
                "mc16a" : "mc16a.MGH7_X600tohh_bbyy_AF2.root",
                "mc16d" : "mc16d.MGH7_X600tohh_bbyy_AF2.root",
                "mc16e" : "mc16e.MGH7_X600tohh_bbyy_AF2.root"
            },
            "histoName" : "CutFlow_MGH7_X600tohh_bbyy_AF2_noDalitz_weighted"
        },

        "X700toHH":    {
            "datafiles" : {
                "mc16a" : "mc16a.MGH7_X700tohh_bbyy_AF2.root",
                "mc16d" : "mc16d.MGH7_X700tohh_bbyy_AF2.root",
                "mc16e" : "mc16e.MGH7_X700tohh_bbyy_AF2.root"
            },
            "histoName" : "CutFlow_MGH7_X700tohh_bbyy_AF2_noDalitz_weighted"
        },

        "X800toHH":    {
            "datafiles" : {
                "mc16a" : "mc16a.MGH7_X800tohh_bbyy_AF2.root",
                "mc16d" : "mc16d.MGH7_X800tohh_bbyy_AF2.root",
                "mc16e" : "mc16e.MGH7_X800tohh_bbyy_AF2.root"
            },
            "histoName" : "CutFlow_MGH7_X800tohh_bbyy_AF2_noDalitz_weighted"
        },

        "X900toHH":    {
            "datafiles" : {
                "mc16a" : "mc16a.MGH7_X900tohh_bbyy_AF2.root",
                "mc16d" : "mc16d.MGH7_X900tohh_bbyy_AF2.root",
                "mc16e" : "mc16e.MGH7_X900tohh_bbyy_AF2.root"
            },
            "histoName" : "CutFlow_MGH7_X900tohh_bbyy_AF2_noDalitz_weighted"
        },

        "X1000toHH":    {
            "datafiles" : {
                "mc16a" : "mc16a.MGH7_X1000tohh_bbyy_AF2.root",
                "mc16d" : "mc16d.MGH7_X1000tohh_bbyy_AF2.root",
                "mc16e" : "mc16e.MGH7_X1000tohh_bbyy_AF2.root"
            },
            "histoName" : "CutFlow_MGH7_X1000tohh_bbyy_AF2_noDalitz_weighted"
        }
    
    }   
}
