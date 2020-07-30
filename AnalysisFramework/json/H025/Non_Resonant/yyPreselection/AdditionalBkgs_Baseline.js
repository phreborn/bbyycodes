{
  "sequencer":["VariablePlotter"],

    "directories":{
      "mc16a" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonpreselection/mc16a/",
      "mc16d" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonpreselection/mc16d/",
      "mc16e" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonpreselection/mc16e/"
    },

   "dumper":{

       "mc16a" : true,
       "mc16d" : true,
       "mc16e" : true

    },

    "variables":{
        "m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 55,"lbins" : 105,"ubins" : 160}},
        "N_j" :{"var": "HGamEventInfoAuxDyn.N_j","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "N_j_central" :{"var": "HGamEventInfoAuxDyn.N_j_central","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "m_jj" :{"var":"HGamEventInfoAuxDyn.yybb_m_jj*0.001","bins":{"nbins" : 60,"lbins" : 0,"ubins" : 300}},
        "m_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj*0.001","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 1600}},
        "m_yyjj_cnstrnd" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_cnstrnd*0.001","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 1600}},
        "m_yyjj_tilde" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_tilde*0.001","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 1600}},
        "weight" : {"var": "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10} }
    
    },

    "selections": {

      "weight" : "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",      

      "XGBoost_btag77_withTop_BCal_tightScore_HMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_BCal_vbf_selected == 0 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 1))   ",
      "XGBoost_btag77_withTop_BCal_looseScore_HMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_BCal_vbf_selected == 0 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 2))   ",
      "XGBoost_btag77_withTop_BCal_tightScore_LMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_BCal_vbf_selected == 0 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 3))   ",
      "XGBoost_btag77_withTop_BCal_looseScore_LMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_BCal_vbf_selected == 0 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 4))   ",                                                                                                                                                                                                                                                     
      "VBF_btag77_withTop_BCal"   : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000)  % 10) != 9) && (HGamEventInfoAuxDyn.yybb_btag77_BCal_vbf_selected == 1)  )"



   },

    "lumi" : {
      "mc16a" : 36209.04,
      "mc16d" : 44385.7,
      "mc16e" : 58450.1
    },

    "samples" : {


      "ttyy_allhad":    {
        "datafiles" : {
          "mc16a" : "mc16a.MGPy8_ttgammagamma_allhad.root",
          "mc16d" : "mc16d.MGPy8_ttgammagamma_allhad.root",
          "mc16e" : "mc16e.MGPy8_ttgammagamma_allhad.root"
        },
        "histoName" : "CutFlow_MGPy8_ttgammagamma_allhad_AF2_noDalitz_weighted"
      },

      "ttyy_noallhad":    {
        "datafiles" : {
          "mc16a" : "mc16a.MGPy8_ttgammagamma_noallhad.root",
          "mc16d" : "mc16d.MGPy8_ttgammagamma_noallhad.MxAODDetailed.root",
          "mc16e" : "mc16e.MGPy8_ttgammagamma_noallhad.root"
        },
        "histoName" : "CutFlow_MGPy8_ttgammagamma_noallhad_AF2_noDalitz_weighted"
      },

      "VBFH_PowhegPy8":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8EG_NNPDF30_VBFH125.root",
          "mc16d" : "mc16d.PowhegPy8EG_NNPDF30_VBFH125.MxAODDetailed.root",
          "mc16e" : "mc16e.PowhegPy8EG_NNPDF30_VBFH125.root"
        },
        "histoName" : "CutFlow_PowhegPy8EG_NNPDF30_VBFH125_noDalitz_weighted"
      },

      "VBFH_PowhegH7":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegH713_VBF125.root",
          "mc16d" : "mc16d.PowhegH713_VBF125.MxAODDetailedNoSkim.root",
          "mc16e" : "mc16e.PowhegH713_VBF125.root"
        },
        "histoName" : "CutFlow_PowhegH713_VBF125_noDalitz_weighted"
      },

      "WmH_PowhegPy8":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8_WmH125J.root",
          "mc16d" : "mc16d.PowhegPy8_WmH125J.root",
          "mc16e" : "mc16e.PowhegPy8_WmH125J.root"
        },
        "histoName" : "CutFlow_PowhegPy8_WmH125J_noDalitz_weighted"
      },

      "WmH_PowhegH7":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegH713_WmH125J.root",
          "mc16d" : "mc16d.PowhegH713_WmH125J.MxAODDetailed.root",
          "mc16e" : "mc16e.PowhegH713_WmH125J.root"
        },
        "histoName" : "CutFlow_PowhegH713_WmH125J_noDalitz_weighted"
      },

      "WpH_PowhegPy8":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8_WpH125J.root",
          "mc16d" : "mc16d.PowhegPy8_WpH125J.root",
          "mc16e" : "mc16e.PowhegPy8_WpH125J.root"
        },
        "histoName" : "CutFlow_PowhegPy8_WpH125J_noDalitz_weighted"
      },

      "WpH_PowhegH7":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegH713_WpH125J.root",
          "mc16d" : "mc16d.PowhegH713_WpH125J.MxAODDetailed.root",
          "mc16e" : "mc16e.PowhegH713_WpH125J.root"
        },
        "histoName" : "CutFlow_PowhegH713_WpH125J_noDalitz_weighted"
      },

      "ggZH_PowhegPy8":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8_ggZH125.root",
          "mc16d" : "mc16d.PowhegPy8_ggZH125.MxAODDetailed.root",
          "mc16e" : "mc16e.PowhegPy8_ggZH125.root"
        },
        "histoName" : "CutFlow_PowhegPy8_ggZH125_noDalitz_weighted"
      },

      "ggZH_PowhegH7":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegH713_ggZH125.root",
          "mc16d" : "mc16d.PowhegH713_ggZH125.root",
          "mc16e" : "mc16e.PowhegH713_ggZH125.root"
        },
        "histoName" : "CutFlow_PowhegH713_ggZH125_noDalitz_weighted"
      },

      "ggH_PowhegPy8":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8_NNLOPS_ggH125.root",
          "mc16d" : "mc16d.PowhegPy8_NNLOPS_ggH125.MxAODDetailed.root",
          "mc16e" : "mc16e.PowhegPy8_NNLOPS_ggH125.root"
        },
        "histoName" : "CutFlow_PowhegPy8_NNLOPS_ggH125_noDalitz_weighted"
      },

      "bbH":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8_bbH125.root",
          "mc16d" : "mc16d.PowhegPy8_bbH125.MxAODDetailed.root",
          "mc16e" : "mc16e.PowhegPy8_bbH125.root"
        },
        "histoName" : "CutFlow_PowhegPy8_bbH125_noDalitz_weighted"
      },

      "tHjb":    {
        "datafiles" : {
          "mc16a" : "mc16a.aMCnloPy8_tHjb125_4fl_shw_fix.root",
          "mc16d" : "mc16d.aMCnloPy8_tHjb125_4fl_shw_fix.MxAODDetailed.root",
          "mc16e" : "mc16e.aMCnloPy8_tHjb125_4fl_shw_fix.root"
        },
        "histoName" : "CutFlow_aMCnloPy8_tHjb125_4fl_noDalitz_weighted"
      },


      "tWH":    {
        "datafiles" : {
          "mc16a" : "mc16a.aMCnloPy8_tWH125.root",
          "mc16d" : "mc16d.aMCnloPy8_tWH125.MxAODDetailed.root",
          "mc16e" : "mc16e.aMCnloPy8_tWH125.root"
        },
        "histoName" : "CutFlow_aMCnloPy8_tWH125_noDalitz_weighted"
      },
     
     }

}

