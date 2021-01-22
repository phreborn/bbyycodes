{
"sequencer":["VariablePlotter"],
    "directories":{
	"mc16a" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/mc16a/",
	"mc16d" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/mc16d/",
	"mc16e" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/mc16e/"

    },

    "variables":{
        "m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 500,"lbins" : 0,"ubins" : 500}},
        "m_jj" :{"var":"HGamEventInfoAuxDyn.yybb_m_jj*0.001","bins":{"nbins" :  500,"lbins" : 0,"ubins" : 500}},
        "pT_jj" :{"var":"HGamEventInfoAuxDyn.pT_jj*0.001","bins":{"nbins" : 500,"lbins" : 0,"ubins" : 500}},
        "pT_yy" :{"var":"HGamEventInfoAuxDyn.pT_yy*0.001","bins":{"nbins" : 500,"lbins" : 0,"ubins" : 500}},
        "m_yyjj_tilde" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_tilde*0.001","bins":{"nbins" : 1000,"lbins" : 0,"ubins" : 1000}},
        "pT_jj_div_m_yyjj_tilde" :{"var":"HGamEventInfoAuxDyn.pT_jj/(HGamEventInfoAuxDyn.yybb_m_yyjj_tilde*0.001)","bins":{"nbins" : 1000,"lbins" : 0,"ubins" : 1000}},
        "pT_yy_div_m_yyjj_tilde" :{"var":"HGamEventInfoAuxDyn.pT_yy/(HGamEventInfoAuxDyn.yybb_m_yyjj_tilde*0.001)","bins":{"nbins" : 1000,"lbins" : 0,"ubins" : 1000}},
        "pT_jj_div_m_jj" :{"var":"HGamEventInfoAuxDyn.pT_jj/(HGamEventInfoAuxDyn.yybb_m_jj*0.001)","bins":{"nbins" : 500,"lbins" : 0,"ubins" : 5000}},
        "pT_yy_div_m_yy" :{"var":"HGamEventInfoAuxDyn.pT_yy/(HGamEventInfoAuxDyn.m_yy*0.001)","bins":{"nbins" : 500,"lbins" : 0,"ubins" : 5000}},
	"MET" :{"var": "HGamEventInfoAuxDyn.met_TST*0.001","bins":{"nbins" : 500,"lbins" : 0,"ubins" : 500}},
	"MET_phi" :{"var": "HGamEventInfoAuxDyn.phi_TST","bins":{"nbins" : 400,"lbins" : -4,"ubins" : 4}},
        "weight_HGam" : {"var": "HGamEventInfoAuxDyn.weight", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10}},
        "weight_bbyy" : {"var": "HGamEventInfoAuxDyn.yybb_weight", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10}},
        "weight_BRFilterEff" : {"var": "HGamEventInfoAuxDyn.crossSectionBRfilterEff", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10}},
	"N_j" :{"var": "HGamEventInfoAuxDyn.N_j","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
	"N_j_central" :{"var": "HGamEventInfoAuxDyn.N_j_central","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
	"N_j_btag" :{"var": "HGamEventInfoAuxDyn.N_j_btag","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}}

    },
    "selections": {

	"yy_sel" : "(HGamEventInfoAuxDyn.isPassed)*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*HGamEventInfoAuxDyn.crossSectionBRfilterEff",

	"yy_btag_77_sel" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_btag77_cutFlow >=6)*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*HGamEventInfoAuxDyn.crossSectionBRfilterEff",

	"yy_btag_77_85_sel" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_btag77_85_cutFlow >=6)*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*HGamEventInfoAuxDyn.crossSectionBRfilterEff",

	"yy_btag_77_Zbb_window" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_btag77_cutFlow >=6 && HGamEventInfoAuxDyn.yybb_m_jj*0.001 > 60.0 && HGamEventInfoAuxDyn.yybb_m_jj*0.001 < 110.0)*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*HGamEventInfoAuxDyn.crossSectionBRfilterEff",

	"yy_btag_77_85_Zbb_window" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_btag77_85_cutFlow >=6 && HGamEventInfoAuxDyn.yybb_m_jj*0.001 > 60.0 && HGamEventInfoAuxDyn.yybb_m_jj*0.001 < 110.0)*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*HGamEventInfoAuxDyn.crossSectionBRfilterEff"

    }, 

    "lumi" : {

      "mc16a" : 36209.04,
      "mc16d" : 44385.7,
      "mc16e" : 58450.1
    },

    "samples" : {

      "HH_old": 	{
        "datafiles" : { 
          "mc16a" : "mc16a.aMCnloHwpp_hh_yybb_AF2.root",
          "mc16d" : "mc16d.aMCnloHwpp_hh_yybb_AF2.root",
          "mc16e" : "mc16e.aMCnloHwpp_hh_yybb_AF2.root"
        },
        "histoName" : "CutFlow_aMCnlo_Hwpp_hh_yybb_noDalitz_weighted"
      },

      "HH": 	{
        "datafiles" : { 
          "mc16a" : "mc16a.PowhegH7_HHbbyy_cHHH01d0.root",
          "mc16d" : "mc16d.PowhegH7_HHbbyy_cHHH01d0.root",
          "mc16e" : "mc16e.PowhegH7_HHbbyy_cHHH01d0.root"
        },
        "histoName" : "CutFlow_PowhegH7_HHbbyy_cHHH01d0_noDalitz_weighted"
      },

      "ggH":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8_NNLOPS_ggH125.root",
          "mc16d" : "mc16d.PowhegPy8_NNLOPS_ggH125.root",
          "mc16e" : "mc16e.PowhegPy8_NNLOPS_ggH125.root"
        },
        "histoName" : "CutFlow_PowhegPy8_NNLOPS_ggH125_noDalitz_weighted"
      },

      "VBF":	{
        "datafiles" : { 	
          "mc16a" : "mc16a.PowhegPy8EG_NNPDF30_VBFH125.root",
          "mc16d" : "mc16d.PowhegPy8EG_NNPDF30_VBFH125.root",
          "mc16e" : "mc16e.PowhegPy8EG_NNPDF30_VBFH125.root"
        },
        "histoName" : "CutFlow_PowhegPy8EG_NNPDF30_VBFH125_noDalitz_weighted"
      }, 

      "WpH":	{
        "datafiles" : { 
          "mc16a" : "mc16a.PowhegPy8_WpH125J.root",
          "mc16d" : "mc16d.PowhegPy8_WpH125J.root",
          "mc16e" : "mc16e.PowhegPy8_WpH125J.root"
        },
        "histoName" : "CutFlow_PowhegPy8_WpH125J_noDalitz_weighted"
      },	

      "WmH":	{
        "datafiles" : { 
          "mc16a" : "mc16a.PowhegPy8_WmH125J.root",
          "mc16d" : "mc16d.PowhegPy8_WmH125J.root",
          "mc16e" : "mc16e.PowhegPy8_WmH125J.root"
        },
        "histoName" : "CutFlow_PowhegPy8_WmH125J_noDalitz_weighted"
      },

      "ZH":	{
        "datafiles" : { 
          "mc16a" : "mc16a.PowhegPy8_ZH125J.root",
          "mc16d" : "mc16d.PowhegPy8_ZH125J.root",
          "mc16e" : "mc16e.PowhegPy8_ZH125J.root"
        },
        "histoName" : "CutFlow_PowhegPy8_ZH125J_noDalitz_weighted"
      },   

      "ggZH":	{
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

      "bbH":	{
        "datafiles" : { 
          "mc16a" : "mc16a.PowhegPy8_bbH125.root",
          "mc16d" : "mc16d.PowhegPy8_bbH125.root",
          "mc16e" : "mc16e.PowhegPy8_bbH125.root"
        },
        "histoName" : "CutFlow_PowhegPy8_bbH125_noDalitz_weighted"
      }, 

      "tWH":	{
        "datafiles" : { 
          "mc16a" : "mc16a.aMCnloPy8_tWH125.root",
          "mc16d" : "mc16d.aMCnloPy8_tWH125.root",
          "mc16e" : "mc16e.aMCnloPy8_tWH125.root"
        },
        "histoName" : "CutFlow_aMCnloPy8_tWH125_noDalitz_weighted"
      }, 

      "tHjb":	{
        "datafiles" : { 
          "mc16a" : "mc16a.aMCnloPy8_tHjb125_4fl_shw_fix.root",
          "mc16d" : "mc16d.aMCnloPy8_tHjb125_4fl_shw_fix.root",
          "mc16e" : "mc16e.aMCnloPy8_tHjb125_4fl_shw_fix.root"
        },
        "histoName" : "CutFlow_aMCnloPy8_tHjb125_4fl_noDalitz_weighted"
      },

      "ttyy_nohad":	{
        "datafiles" : { 	
          "mc16a" : "mc16a.MGPy8_ttgammagamma_noallhad.root",
          "mc16d" : "mc16d.MGPy8_ttgammagamma_noallhad.root",
          "mc16e" : "mc16e.MGPy8_ttgammagamma_noallhad.root"
        },
        "histoName" : "CutFlow_MGPy8_ttgammagamma_noallhad_AF2_noDalitz_weighted"
      }, 

      "ttyy_had":	{
        "datafiles" : { 
          "mc16a" : "mc16a.MGPy8_ttgammagamma_allhad.root",
          "mc16d" : "mc16d.MGPy8_ttgammagamma_allhad.root",
          "mc16e" : "mc16e.MGPy8_ttgammagamma_allhad.root"
        },
        "histoName" : "CutFlow_MGPy8_ttgammagamma_allhad_AF2_noDalitz_weighted"
      },

      "yyjj":    {
        "datafiles" : {
          "mc16a" : "mc16a.Sherpa2_myy_90_175.root",
          "mc16d" : "mc16d.Sherpa2_myy_90_175.root",
          "mc16e" : "mc16e.Sherpa2_myy_90_175.root"
        },
        "histoName" : "CutFlow_Sherpa2_myy_90_175_noDalitz_weighted"
      }
    }

}
