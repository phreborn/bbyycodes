{
  "sequencer":["VariablePlotter"],

    "directories":{
      "mc16a" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h026/mc16a/Nominal/",
      "mc16d" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h026/mc16d/Nominal/",
      "mc16e" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h026/mc16e/Nominal/"
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
        "deltaR_yy" :{"var": "HGamEventInfoAuxDyn.yybb_deltaR_yy","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 4}},
        "deltaR_jj" :{"var": "HGamEventInfoAuxDyn.yybb_deltaR_jj","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 4}},
        "deltaR_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_deltaR_yyjj","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 4}},
        "weight" : {"var": "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10} }
    
    },

    "selections": { 

      "weight" : "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",      
      "Validation" : "HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6",
      "XGBoost_btag77_withTop_BCal_tightScore_HMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 1)   && HGamEventInfoAuxDyn.m_yy*0.001 > 120 && HGamEventInfoAuxDyn.m_yy*0.001 < 130 )",
      "XGBoost_btag77_withTop_BCal_looseScore_HMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 2)   && HGamEventInfoAuxDyn.m_yy*0.001 > 120 && HGamEventInfoAuxDyn.m_yy*0.001 < 130 )",
      "XGBoost_btag77_withTop_BCal_tightScore_LMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 3)   && HGamEventInfoAuxDyn.m_yy*0.001 > 120 && HGamEventInfoAuxDyn.m_yy*0.001 < 130 )",
      "XGBoost_btag77_withTop_BCal_looseScore_LMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 4)   && HGamEventInfoAuxDyn.m_yy*0.001 > 120 && HGamEventInfoAuxDyn.m_yy*0.001 < 130 )"

   },

    "lumi" : {
      "mc16a" : 36209.04,
      "mc16d" : 44385.7,
      "mc16e" : 58450.1
    },

    "samples" : {



      "ZH_PowhegPy8":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8_ZH125J.MxAODDetailed.e5743_s3126_r9364_p4180_h026.root",
          "mc16d" : "mc16d.PowhegPy8_ZH125J.MxAODDetailed.e5743_s3126_r10201_p4180_h026.root",
          "mc16e" : "mc16e.PowhegPy8_ZH125J.MxAODDetailed.e5743_s3126_r10724_p4180_h026.root"
        },
        "histoName": "CutFlow_PowhegPy8_ZH125J_noDalitz_weighted"
      },
 
      
      "ttyy_allhad":    {
        "datafiles" : {
          "mc16a" : "mc16a.MGPy8_ttgammagamma_allhad.MxAODDetailed.e6542_a875_r9364_p4204_h026.root",
          "mc16d" : "mc16d.MGPy8_ttgammagamma_allhad.MxAODDetailed.e6542_a875_r10201_p4204_h026.root",
          "mc16e" : "mc16e.MGPy8_ttgammagamma_allhad.MxAODDetailed.e6542_a875_r10724_p4204_h026.root"
        },
        "histoName" : "CutFlow_MGPy8_ttgammagamma_allhad_AF2_noDalitz_weighted"
      },

      "ttyy_noallhad":    {
        "datafiles" : {
          "mc16a" : "mc16a.MGPy8_ttgammagamma_noallhad.MxAODDetailed.e6542_a875_r9364_p4204_h026.root",
          "mc16d" : "mc16d.MGPy8_ttgammagamma_noallhad.MxAODDetailed.e6542_a875_r10201_p4204_h026.root",
          "mc16e" : "mc16e.MGPy8_ttgammagamma_noallhad.MxAODDetailed.e6542_a875_r10724_p4204_h026.root"
        },
        "histoName" : "CutFlow_MGPy8_ttgammagamma_noallhad_AF2_noDalitz_weighted"
      },

      "WmH_PowhegPy8":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8_WmH125J.MxAODDetailed.e5734_s3126_r9364_p4180_h026.root",
          "mc16d" : "mc16d.PowhegPy8_WmH125J.MxAODDetailed.e5734_s3126_r10201_p4180_h026.root",
          "mc16e" : "mc16e.PowhegPy8_WmH125J.MxAODDetailed.e5734_s3126_r10724_p4180_h026.root"
        },
        "histoName" : "CutFlow_PowhegPy8_WmH125J_noDalitz_weighted"
      },


      "WpH_PowhegPy8":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8_WpH125J.MxAODDetailed.e5734_s3126_r9364_p4180_h026.root",
          "mc16d" : "mc16d.PowhegPy8_WpH125J.MxAODDetailed.e5734_s3126_r10201_p4180_h026.root",
          "mc16e" : "mc16e.PowhegPy8_WpH125J.MxAODDetailed.e5734_s3126_r10724_p4180_h026.root"
        },
        "histoName" : "CutFlow_PowhegPy8_WpH125J_noDalitz_weighted"
      },


      "bbH":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8_bbH125.MxAODDetailed.e6050_s3126_r9364_p4180_h026.root",
          "mc16d" : "mc16d.PowhegPy8_bbH125.MxAODDetailed.e6050_s3126_r10201_p4180_h026.root",
          "mc16e" : "mc16e.PowhegPy8_bbH125.MxAODDetailed.e6050_s3126_r10724_p4180_h026.root"
        },
        "histoName" : "CutFlow_PowhegPy8_bbH125_noDalitz_weighted"
      },

      "tHjb":    {
        "datafiles" : {
          "mc16a" : "mc16a.aMCnloPy8_tHjb125_4fl_shw_fix.MxAODDetailed.e7305_s3126_r9364_p4180_h026.root",
          "mc16d" : "mc16d.aMCnloPy8_tHjb125_4fl_shw_fix.MxAODDetailed.e7305_s3126_r10201_p4180_h026.root",
          "mc16e" : "mc16e.aMCnloPy8_tHjb125_4fl_shw_fix.MxAODDetailed.e7305_s3126_r10724_p4180_h026.root"
        },
        "histoName" : "CutFlow_aMCnloPy8_tHjb125_4fl_noDalitz_weighted"
      },


      "tWH":    {
        "datafiles" : {
          "mc16a" : "mc16a.aMCnloPy8_tWH125.MxAODDetailed.e7425_s3126_r9364_p4180_h026.root",
          "mc16d" : "mc16d.aMCnloPy8_tWH125.MxAODDetailed.e7425_s3126_r10201_p4180_h026.root",
          "mc16e" : "mc16e.aMCnloPy8_tWH125.MxAODDetailed.e7425_s3126_r10724_p4180_h026.root"
        },
        "histoName" : "CutFlow_aMCnloPy8_tWH125_noDalitz_weighted"
      }
     
     }

}
