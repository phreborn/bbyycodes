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
      "LM_A" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_Cat % 10) == 1 ))",


      "XGBoost_btag77_85_Nominal_tightScore_HMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_Cat % 10) == 1))",
      "XGBoost_btag77_85_Nominal_looseScore_HMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_Cat % 10) == 2))",
      "XGBoost_btag77_85_Nominal_tightScore_LMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_Cat % 10) == 3))",
      "XGBoost_btag77_85_Nominal_looseScore_LMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_Cat % 10) == 4))",

      "XGBoost_btag77_Nominal_tightScore_HMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_Cat % 10) == 1))",
      "XGBoost_btag77_Nominal_looseScore_HMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_Cat % 10) == 2))",
      "XGBoost_btag77_Nominal_tightScore_LMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_Cat % 10) == 3))",
      "XGBoost_btag77_Nominal_looseScore_LMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_Cat % 10) == 4))",

      "XGBoost_btag77_85_Nominal_BCal_tightScore_HMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_BCal_Cat % 10) == 1))",
      "XGBoost_btag77_85_Nominal_BCal_looseScore_HMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_BCal_Cat % 10) == 2))",
      "XGBoost_btag77_85_Nominal_BCal_tightScore_LMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_BCal_Cat % 10) == 3))",
      "XGBoost_btag77_85_Nominal_BCal_looseScore_LMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_BCal_Cat % 10) == 4))",      

      "XGBoost_btag77_Nominal_BCal_tightScore_HMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat % 10) == 1))",
      "XGBoost_btag77_Nominal_BCal_looseScore_HMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat % 10) == 2))",
      "XGBoost_btag77_Nominal_BCal_tightScore_LMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat % 10) == 3))",
      "XGBoost_btag77_Nominal_BCal_looseScore_LMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat % 10) == 4))",  

      "XGBoost_btag77_85_Nominal_KF_tightScore_HMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_KF_Cat % 10) == 1))",
      "XGBoost_btag77_85_Nominal_KF_looseScore_HMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_KF_Cat % 10) == 2))",
      "XGBoost_btag77_85_Nominal_KF_tightScore_LMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_KF_Cat % 10) == 3))",
      "XGBoost_btag77_85_Nominal_KF_looseScore_LMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_KF_Cat % 10) == 4))",

      "XGBoost_btag77_Nominal_KF_tightScore_HMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_KF_Cat % 10) == 1))",
      "XGBoost_btag77_Nominal_KF_looseScore_HMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_KF_Cat % 10) == 2))",
      "XGBoost_btag77_Nominal_KF_tightScore_LMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_KF_Cat % 10) == 3))",
      "XGBoost_btag77_Nominal_KF_looseScore_LMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_KF_Cat % 10) == 4))",
       

      "VBF_btag77" : "(HGamEventInfoAuxDyn.isPassed == 1 && (HGamEventInfoAuxDyn.yybb_btag77_vbf_selected == 1))",

      "VBF_btag77_85" : "(HGamEventInfoAuxDyn.isPassed == 1 && (HGamEventInfoAuxDyn.yybb_btag77_85_vbf_selected == 1))",

      "VBF_btag77_BCal" : "(HGamEventInfoAuxDyn.isPassed == 1 && (HGamEventInfoAuxDyn.yybb_btag77_BCal_vbf_selected == 1))",

      "VBF_btag77_85_BCal" : "(HGamEventInfoAuxDyn.isPassed == 1 && (HGamEventInfoAuxDyn.yybb_btag77_85_BCal_vbf_selected == 1))",

      "VBF_btag77_KF" : "(HGamEventInfoAuxDyn.isPassed == 1 && (HGamEventInfoAuxDyn.yybb_btag77_KF_vbf_selected == 1))",

      "VBF_btag77_85_KF" : "(HGamEventInfoAuxDyn.isPassed == 1 && (HGamEventInfoAuxDyn.yybb_btag77_85_KF_vbf_selected == 1))"

   },

    "lumi" : {
      "mc16a" : 36209.04,
      "mc16d" : 44385.7,
      "mc16e" : 58450.1
    },

    "samples" : {

      "HH_LO":    {
        "datafiles" : {
          "mc16a" : "mc16a.aMCnloHwpp_hh_yybb_AF2.MxAODDetailedNoSkim.e4419_a875_r9364_p4097_h025.root",
          "mc16d" : "mc16d.aMCnloHwpp_hh_yybb_AF2.MxAODDetailedNoSkim.e4419_a875_r10201_p4097_h025.root",
          "mc16e" : "mc16e.aMCnloHwpp_hh_yybb_AF2.MxAODDetailedNoSkim.e4419_a875_r10724_p4097_h025.root"
        },
        "histoName" : "CutFlow_aMCnlo_Hwpp_hh_yybb_noDalitz_weighted"
      },

      "VBF":	{
        "datafiles" : {
          "mc16a" : "mc16a.MGH7_hh_bbyy_vbf_l1cvv1cv1.MxAODDetailedNoSkim.e7254_s3126_r9364_p4097_h025.root",
          "mc16d" : "mc16d.MGH7_hh_bbyy_vbf_l1cvv1cv1.MxAODDetailedNoSkim.e7254_s3126_r10201_p4097_h025.root",
          "mc16e" : "mc16e.MGH7_hh_bbyy_vbf_l1cvv1cv1.MxAODDetailedNoSkim.e7254_s3126_r10724_p4097_h025.root"
        },
        "histoName": "CutFlow_MGH7_hh_bbyy_vbf_l1cvv1cv1_noDalitz_weighted"
      },

       "HH_NLO_cHHH01d0":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegH7_HHbbyy_cHHH01d0.MxAODDetailedNoSkim.e7954_s3126_r9364_p4097_h025.root",
          "mc16d" : "mc16d.PowhegH7_HHbbyy_cHHH01d0.MxAODDetailedNoSkim.e7954_s3126_r10201_p4097_h025.root",
          "mc16e" : "mc16e.PowhegH7_HHbbyy_cHHH01d0.MxAODDetailedNoSkim.e7954_s3126_r10724_p4097_h025.root"
        },
        "histoName" : "CutFlow_PowhegH7_HHbbyy_cHHH01d0_noDalitz_weighted"
      },
      
      "HH_NLO_cHHH10d0":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegH7_HHbbyy_cHHH10d0.MxAODDetailedNoSkim.e7954_s3126_r9364_p4097_h025.root",
          "mc16d" : "mc16d.PowhegH7_HHbbyy_cHHH10d0.MxAODDetailedNoSkim.e7954_s3126_r10201_p4097_h025.root",
          "mc16e" : "mc16e.PowhegH7_HHbbyy_cHHH10d0.MxAODDetailedNoSkim.e7954_s3126_r10724_p4097_h025.root"
        },
        "histoName" : "CutFlow_PowhegH7_HHbbyy_cHHH10d0_noDalitz_weighted"
      },
      
       "HH_LO_minus10":    {
        "datafiles" : {
          "mc16a" : "mc16a.MGPy8_hh_yybb_minus_lambda10_AF2.MxAODDetailedNoSkim.e5504_a875_r9364_p4097_h025.root",
          "mc16d" : "mc16d.MGPy8_hh_yybb_minus_lambda10_AF2.MxAODDetailedNoSkim.e5504_a875_r10201_p4097_h025.root",
          "mc16e" : "mc16e.MGPy8_hh_yybb_minus_lambda10_AF2.MxAODDetailedNoSkim.e5504_a875_r10724_p4097_h025.root"
        },
        "histoName" : "CutFlow_MGPy8_hh_yybb_minus_lambda10_noDalitz_weighted"
      }

   }

}
