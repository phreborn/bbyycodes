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

      "XGBoost_btag77_withTop_BCal_tightScore_HMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_BCal_vbf_selected == 0 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 1)   ",
      "XGBoost_btag77_withTop_BCal_looseScore_HMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_BCal_vbf_selected == 0 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 2)   ",
      "XGBoost_btag77_withTop_BCal_tightScore_LMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_BCal_vbf_selected == 0 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 3)   ",
      "XGBoost_btag77_withTop_BCal_looseScore_LMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_BCal_vbf_selected == 0 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 4)   ",                                                                                                                                                                                                                                                     
      "VBF_btag77_withTop_BCal" 	: "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000)  % 10) != 9) && (HGamEventInfoAuxDyn.yybb_btag77_BCal_vbf_selected == 1)  )",



   },

    "lumi" : {
      "mc16a" : 36209.04,
      "mc16d" : 44385.7,
      "mc16e" : 58450.1
    },

    "samples" : {

      "HH":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegH7_HHbbyy_cHHH01d0.root",
          "mc16d" : "mc16d.PowhegH7_HHbbyy_cHHH01d0.root",
          "mc16e" : "mc16e.PowhegH7_HHbbyy_cHHH01d0.root"
        },
        "histoName" : "CutFlow_PowhegH7_HHbbyy_cHHH01d0_noDalitz_weighted"
      },

      "VBF":	{
        "datafiles" : {
          "mc16a" : "mc16a.MGH7_hh_bbyy_vbf_l1cvv1cv1.root",
          "mc16d" : "mc16d.MGH7_hh_bbyy_vbf_l1cvv1cv1.root",
          "mc16e" : "mc16e.MGH7_hh_bbyy_vbf_l1cvv1cv1.root"
        },
        "histoName": "CutFlow_MGH7_hh_bbyy_vbf_l1cvv1cv1_noDalitz_weighted"
      },


      "ttH_PowhegPy8":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8_ttH125_fixweight.root",
          "mc16d" : "mc16d.PowhegPy8_ttH125_fixweight.MxAODDetailed.root",
          "mc16e" : "mc16e.PowhegPy8_ttH125_fixweight.root"
        },
        "histoName" : "CutFlow_PowhegPy8_ttH125_fixweight_noDalitz_weighted"
      },


      "ZH_PowhegPy8":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8_ZH125J.root",
          "mc16d" : "mc16d.PowhegPy8_ZH125J.MxAODDetailed.root",
          "mc16e" : "mc16e.PowhegPy8_ZH125J.root"
        },
        "histoName": "CutFlow_PowhegPy8_ZH125J_noDalitz_weighted"
      },
 
      "yy":    {
        "datafiles" : {
          "mc16a" : "mc16a.Sherpa2_myy_90_175.root",
          "mc16d" : "mc16d.Sherpa2_diphoton_myy_90_175.root",
          "mc16e" : "mc16e.Sherpa2_myy_90_175.root"
        },
        "histoName" : "CutFlow_Sherpa2_myy_90_175_noDalitz_weighted"
      }
     
     }

}
