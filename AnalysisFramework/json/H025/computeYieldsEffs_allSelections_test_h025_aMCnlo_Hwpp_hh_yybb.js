{
  "sequencer":["YieldCalculator","VariablePlotter"],

    "directories":{
      "mc16d" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h025/mc16d/Nominal/"
    },

    "variables":{
	      "m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 55,"lbins" : 105,"ubins" : 160}},
        "N_j" :{"var": "HGamEventInfoAuxDyn.N_j","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "N_j_central" :{"var": "HGamEventInfoAuxDyn.N_j_central","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "m_jj" :{"var":"HGamEventInfoAuxDyn.yybb_m_jj*0.001","bins":{"nbins" : 30,"lbins" : 0,"ubins" : 300}},
        "m_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj*0.001","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 1600}},
        "m_yyjj_cnstrnd" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_cnstrnd*0.001","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 1600}},
        "m_yyjj_tilde" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_tilde*0.001","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 1600}},
        "XGBoost_btag77_85_lowMass_Score": {"var":"HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_lowMass_Score","bins":{"nbins" : 100,"lbins" : 0,"ubins" : 1}},
        "XGBoost_btag77_85_highMass_Score": {"var":"HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_highMass_Score","bins":{"nbins" : 100,"lbins" : 0,"ubins" : 1}},
        "XGBoost_btag77_85_noMbb_lowMass_Score": {"var":"HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_noMbb_lowMass_Score","bins":{"nbins" : 100,"lbins" : 0,"ubins" : 1}},
        "XGBoost_btag77_85_noMbb_highMass_Score": {"var":"HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_noMbb_highMass_Score","bins":{"nbins" : 100,"lbins" : 0,"ubins" : 1}},
        "XGBoost_btag77_85_noHT_lowMass_Score": {"var":"HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_noHT_lowMass_Score","bins":{"nbins" : 100,"lbins" : 0,"ubins" : 1}},
        "XGBoost_btag77_85_noHT_highMass_Score": {"var":"HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_noHT_highMass_Score","bins":{"nbins" : 100,"lbins" : 0,"ubins" : 1}},
        "XGBoost_btag77_85_withTop_lowMass_Score": {"var":"HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_withTop_lowMass_Score","bins":{"nbins" : 100,"lbins" : 0,"ubins" : 1}},
        "XGBoost_btag77_85_withTop_highMass_Score": {"var":"HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_withTop_highMass_Score","bins":{"nbins" : 100,"lbins" : 0,"ubins" : 1}},
        "XGBoost_btag77_lowMass_Score": {"var":"HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_lowMass_Score","bins":{"nbins" : 100,"lbins" : 0,"ubins" : 1}},
        "XGBoost_btag77_highMass_Score": {"var":"HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_highMass_Score","bins":{"nbins" : 100,"lbins" : 0,"ubins" : 1}},
        "XGBoost_btag77_noMbb_lowMass_Score": {"var":"HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_noMbb_lowMass_Score","bins":{"nbins" : 100,"lbins" : 0,"ubins" : 1}},
        "XGBoost_btag77_noMbb_highMass_Score": {"var":"HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_noMbb_highMass_Score","bins":{"nbins" : 100,"lbins" : 0,"ubins" : 1}},
        "XGBoost_btag77_noHT_lowMass_Score": {"var":"HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_noHT_lowMass_Score","bins":{"nbins" : 100,"lbins" : 0,"ubins" : 1}},
        "XGBoost_btag77_noHT_highMass_Score": {"var":"HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_noHT_highMass_Score","bins":{"nbins" : 100,"lbins" : 0,"ubins" : 1}},
        "XGBoost_btag77_withTop_lowMass_Score": {"var":"HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_withTop_lowMass_Score","bins":{"nbins" : 100,"lbins" : 0,"ubins" : 1}},
        "XGBoost_btag77_withTop_highMass_Score": {"var":"HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_withTop_highMass_Score","bins":{"nbins" : 100,"lbins" : 0,"ubins" : 1}}
    },

    "selections": {

      "Pass_yy" : "HGamEventInfoAuxDyn.isPassed",

      "TEST" : "HGamEventInfoAuxDyn.isPassedPreselection&&HGamEventInfoAuxDyn.isPassedTriggerMatch&&HGamEventInfoAuxDyn.isPassedPID&&HGamEventInfoAuxDyn.isPassedIsolation&&HGamEventInfoAuxDyn.isPassedRelPtCuts&&HGamEventInfoAuxDyn.isPassedMassCut&&EventInfoAuxDyn.passTrig_HLT_g35_medium_g25_medium_L12EM20VH",

      "Validation" : "HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_btag77_85_cutFlow == 6",

      "LM_A" : "(HGamEventInfoAuxDyn.isPassed && ((HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_Cat % 10) == 1 ))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",
      "LM_B" : "(HGamEventInfoAuxDyn.isPassed && ((HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_Cat % 10) == 2 ))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "HM_A" : "(HGamEventInfoAuxDyn.isPassed && ((HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_Cat % 10) == 3 ))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",
      "HM_B" : "(HGamEventInfoAuxDyn.isPassed && ((HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_Cat % 10) == 4 ))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "LM_A_loosembb" : "(HGamEventInfoAuxDyn.isPassed && ((((HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_Cat)/10) % 10) == 1))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",
      "LM_B_loosembb" : "(HGamEventInfoAuxDyn.isPassed && ((((HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_Cat)/10) % 10) == 2))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "HM_A_loosembb" : "(HGamEventInfoAuxDyn.isPassed && ((((HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_Cat)/10) % 10) == 3))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",
      "HM_B_loosembb" : "(HGamEventInfoAuxDyn.isPassed && ((((HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_Cat)/10) % 10) == 4))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "LM_A_KF" : "(HGamEventInfoAuxDyn.isPassed && ((HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_KF_Cat % 10) == 1 ))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",
      "LM_B_KF" : "(HGamEventInfoAuxDyn.isPassed && ((HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_KF_Cat % 10) == 2 ))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "HM_A_KF" : "(HGamEventInfoAuxDyn.isPassed && ((HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_KF_Cat % 10) == 3 ))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",
      "HM_B_KF" : "(HGamEventInfoAuxDyn.isPassed && ((HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_KF_Cat % 10) == 4 ))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "LM_A_KF_loosembb" : "(HGamEventInfoAuxDyn.isPassed && ((((HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_KF_Cat)/10) % 10) == 1))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",
      "LM_B_KF_loosembb" : "(HGamEventInfoAuxDyn.isPassed && ((((HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_KF_Cat)/10) % 10) == 2))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "HM_A_KF_loosembb" : "(HGamEventInfoAuxDyn.isPassed && ((((HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_KF_Cat)/10) % 10) == 3))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",
      "HM_B_KF_loosembb" : "(HGamEventInfoAuxDyn.isPassed && ((((HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_KF_Cat)/10) % 10) == 4))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "XGBoost_btag77_85_tightScore_HMass_all" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_Cat == 1111)*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight" ,

      "XGBoost_btag77_85_Nominal_tightScore_HMass_NoWeights" : "(HGamEventInfoAuxDyn.isPassed && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_Cat % 10) == 1))",

      "XGBoost_btag77_85_Nominal_tightScore_HMass" : "(HGamEventInfoAuxDyn.isPassed && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_Cat % 10) == 1))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "XGBoost_btag77_85_Nominal_looseScore_HMass" : "(HGamEventInfoAuxDyn.isPassed && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_Cat % 10) == 2))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "XGBoost_btag77_85_Nominal_tightScore_LMass" : "(HGamEventInfoAuxDyn.isPassed && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_Cat % 10) == 3))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "XGBoost_btag77_85_Nominal_looseScore_LMass" : "(HGamEventInfoAuxDyn.isPassed && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_Cat % 10) == 4))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "XGBoost_btag77_Nominal_tightScore_HMass" : "(HGamEventInfoAuxDyn.isPassed && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_Cat % 10) == 1))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "XGBoost_btag77_Nominal_looseScore_HMass" : "(HGamEventInfoAuxDyn.isPassed && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_Cat % 10) == 2))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "XGBoost_btag77_Nominal_tightScore_LMass" : "(HGamEventInfoAuxDyn.isPassed && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_Cat % 10) == 3))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "XGBoost_btag77_Nominal_looseScore_LMass" : "(HGamEventInfoAuxDyn.isPassed && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_Cat % 10) == 4))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "XGBoost_btag77_85_NominalWithTop_tightScore_HMass" : "(HGamEventInfoAuxDyn.isPassed && ((((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_Cat)/1000) % 10) == 1))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "XGBoost_btag77_85_NominalWithTop_looseScore_HMass" : "(HGamEventInfoAuxDyn.isPassed && ((((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_Cat)/1000) % 10) == 2))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "XGBoost_btag77_85_NominalWithTop_tightScore_LMass" : "(HGamEventInfoAuxDyn.isPassed && ((((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_Cat)/1000) % 10) == 3))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "XGBoost_btag77_85_NominalWithTop_looseScore_LMass" : "(HGamEventInfoAuxDyn.isPassed && ((((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_Cat)/1000) % 10) == 4))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "XGBoost_btag77_NominalWithTop_tightScore_HMass" : "(HGamEventInfoAuxDyn.isPassed && ((((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_Cat)/1000) % 10) == 1))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "XGBoost_btag77_NominalWithTop_looseScore_HMass" : "(HGamEventInfoAuxDyn.isPassed && ((((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_Cat)/1000) % 10) == 2))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "XGBoost_btag77_NominalWithTop_tightScore_LMass" : "(HGamEventInfoAuxDyn.isPassed && ((((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_Cat)/1000) % 10) == 3))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "XGBoost_btag77_NominalWithTop_looseScore_LMass" : "(HGamEventInfoAuxDyn.isPassed && ((((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_Cat)/1000) % 10) == 4))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "VBF_btag77" : "(HGamEventInfoAuxDyn.isPassed && (HGamEventInfoAuxDyn.yybb_btag77_vbf_selected == 1))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "VBF_btag77_85" : "(HGamEventInfoAuxDyn.isPassed && (HGamEventInfoAuxDyn.yybb_btag77_85_vbf_selected == 1))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight"

   },

    "lumi" : {
      "mc16d" : 44385.7 
    },

    "samples" : {

      "HH_Official":	{
        "datafiles" : {
          "mc16d" : "mc16d.aMCnloHwpp_hh_yybb.MxAODDetailedNoSkim.e4419_a875_r10201_p4097_h025.root"
        },
        "histoName" : "CutFlow_aMCnlo_Hwpp_hh_yybb_noDalitz_weighted"
      }
     }

}
