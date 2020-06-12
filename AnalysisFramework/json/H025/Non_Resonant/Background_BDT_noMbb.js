{
  "sequencer":["VariablePlotter"],

    "directories":{
      "mc16a" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h025/mc16a/Nominal/",
      "mc16d" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h025/mc16d/Nominal/",
      "mc16e" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h025/mc16e/Nominal/"
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


      "Pass_yy" : "HGamEventInfoAuxDyn.isPassed == 1",
      "TEST" : "HGamEventInfoAuxDyn.isPassedPreselection&&HGamEventInfoAuxDyn.isPassedTriggerMatch&&HGamEventInfoAuxDyn.isPassedPID&&HGamEventInfoAuxDyn.isPassedIsolation&&HGamEventInfoAuxDyn.isPassedRelPtCuts&&HGamEventInfoAuxDyn.isPassedMassCut&&EventInfoAuxDyn.passTrig_HLT_g35_medium_g25_medium_L12EM20VH",
      "Validation" : "HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_85_cutFlow == 6",
      "LM_A" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_Cat  % 10) == 1 ))",


      "XGBoost_btag77_85_noMbb_tightScore_HMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_Cat/100) % 10) == 1))",
      "XGBoost_btag77_85_noMbb_looseScore_HMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_Cat/100) % 10) == 2))",
      "XGBoost_btag77_85_noMbb_tightScore_LMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_Cat/100) % 10) == 3))",
      "XGBoost_btag77_85_noMbb_looseScore_LMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_Cat/100) % 10) == 4))",

      "XGBoost_btag77_noMbb_tightScore_HMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_Cat/100) % 10) == 1))",
      "XGBoost_btag77_noMbb_looseScore_HMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_Cat/100) % 10) == 2))",
      "XGBoost_btag77_noMbb_tightScore_LMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_Cat/100) % 10) == 3))",
      "XGBoost_btag77_noMbb_looseScore_LMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_Cat/100) % 10) == 4))",

      "XGBoost_btag77_85_noMbb_BCal_tightScore_HMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_BCal_Cat/100) % 10) == 1))",
      "XGBoost_btag77_85_noMbb_BCal_looseScore_HMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_BCal_Cat/100) % 10) == 2))",
      "XGBoost_btag77_85_noMbb_BCal_tightScore_LMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_BCal_Cat/100) % 10) == 3))",
      "XGBoost_btag77_85_noMbb_BCal_looseScore_LMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_BCal_Cat/100) % 10) == 4))",      

      "XGBoost_btag77_noMbb_BCal_tightScore_HMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/100) % 10) == 1))",
      "XGBoost_btag77_noMbb_BCal_looseScore_HMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/100) % 10) == 2))",
      "XGBoost_btag77_noMbb_BCal_tightScore_LMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/100) % 10) == 3))",
      "XGBoost_btag77_noMbb_BCal_looseScore_LMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/100) % 10) == 4))",  

      "XGBoost_btag77_85_noMbb_KF_tightScore_HMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_KF_Cat/100) % 10) == 1))",
      "XGBoost_btag77_85_noMbb_KF_looseScore_HMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_KF_Cat/100) % 10) == 2))",
      "XGBoost_btag77_85_noMbb_KF_tightScore_LMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_KF_Cat/100) % 10) == 3))",
      "XGBoost_btag77_85_noMbb_KF_looseScore_LMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_KF_Cat/100) % 10) == 4))",

      "XGBoost_btag77_noMbb_KF_tightScore_HMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_KF_Cat/100) % 10) == 1))",
      "XGBoost_btag77_noMbb_KF_looseScore_HMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_KF_Cat/100) % 10) == 2))",
      "XGBoost_btag77_noMbb_KF_tightScore_LMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_KF_Cat/100) % 10) == 3))",
      "XGBoost_btag77_noMbb_KF_looseScore_LMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_KF_Cat/100) % 10) == 4))",
       

      "VBF_btag77" : "(HGamEventInfoAuxDyn.isPassed == 1 && (HGamEventInfoAuxDyn.yybb_btag77_vbf_selected == 1))",

      "VBF_btag77_85" : "(HGamEventInfoAuxDyn.isPassed == 1 && (HGamEventInfoAuxDyn.yybb_btag77_85_vbf_selected == 1))",

      "VBF_btag77_BCal" : "(HGamEventInfoAuxDyn.isPassed == 1 && (HGamEventInfoAuxDyn.yybb_btag77_BCal_vbf_selected == 1))",

      "VBF_btag77_85_BCal" : "(HGamEventInfoAuxDyn.isPassed == 1 && (HGamEventInfoAuxDyn.yybb_btag77_85_BCal_vbf_selected == 1))",

      "VBF_btag77_KF" : "(HGamEventInfoAuxDyn.isPassed == 1 && (HGamEventInfoAuxDyn.yybb_btag77_KF_vbf_selected == 1))",

      "VBF_btag77_KF" : "(HGamEventInfoAuxDyn.isPassed == 1 && (HGamEventInfoAuxDyn.yybb_btag77_85_KF_vbf_selected == 1))"

   },

    "lumi" : {
      "mc16a" : 36209.04,
      "mc16d" : 44385.7,
      "mc16e" : 58450.1
    },

    "samples" : {

      "ttH":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegHw7_ttH125_fixweight.MxAODDetailedNoSkim.e7488_s3126_r9364_p4097_h025.root",
          "mc16d" : "mc16d.PowhegHw7_ttH125_fixweight.MxAODDetailedNoSkim.e7488_s3126_r10201_p4097_h025.root",
          "mc16e" : "mc16e.PowhegHw7_ttH125_fixweight.MxAODDetailedNoSkim.e7488_s3126_r10724_p4097_h025.root"
        },
        "histoName" : "CutFlow_PowhegHw7_ttH125_fixweight_noDalitz_weighted"
      },

      "ZH_PowhegH7":	{
        "datafiles" : {
          "mc16a" : "mc16a.PowhegH713_ZH125J.MxAODDetailedNoSkim.e7929_s3126_r9364_p4097_h025.root",
          "mc16d" : "mc16d.PowhegH713_ZH125J.MxAODDetailedNoSkim.e7929_s3126_r10201_p4097_h025.root",
          "mc16e" : "mc16e.PowhegH713_ZH125J.MxAODDetailedNoSkim.e7929_s3126_r10724_p4097_h025.root"
        },
        "histoName": "CutFlow_PowhegH713_ZH125J_noDalitz_weighted"
      },

      "ZH_PowhegPy8":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8_ZH125J.MxAODDetailed.e5743_s3126_r9364_p4097_h025.root",
          "mc16d" : "mc16d.PowhegPy8_ZH125J.MxAODDetailed.e5743_s3126_r10201_p4097_h025.root",
          "mc16e" : "mc16e.PowhegPy8_ZH125J.MxAODDetailed.e5743_s3126_r10724_p4097_h025.root"
        },
        "histoName": "CutFlow_PowhegPy8_ZH125J_noDalitz_weighted"
      }
 
     }

}
