{
  "sequencer":["YieldCalculator","VariablePlotter"],

    "directories":{
      "mc16d" : "root://eosatlas.cern.ch//eos/user/e/epetit/Higgs/yybb/data/h025/aMCnlo_Hwpp_hh_yybb/data-MxAOD/"
    },

    "variables":{
	"m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 55,"lbins" : 105,"ubins" : 160}},
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

      "LM_A" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_Cat == ((10*1)+1) )*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",
      "LM_B" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_Cat == ((10*2)+2) )*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "HM_A" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_Cat == ((10*3)+3) )*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",
      "HM_B" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_Cat == ((10*4)+4) )*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",
  
      "LM_A_loosembb" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_Cat == (-99+(10*1)) )*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",
      "LM_B_loosembb" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_Cat == (-99+(10*2)) )*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",
 
      "HM_A_loosembb" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_Cat == (-99+(10*3)) )*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",
      "HM_B_loosembb" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_Cat == (-99+(10*4)) )*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",
      
      "LM_A_KF" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_KF_Cat == ((10*1)+1) )*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",
      "LM_B_KF" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_KF_Cat == ((10*2)+2) )*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "HM_A_KF" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_KF_Cat == ((10*3)+3) )*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",
      "HM_B_KF" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_KF_Cat == ((10*4)+4) )*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "LM_A_KF_loosembb" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_KF_Cat == (-99+(10*1)) )*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",
      "LM_B_KF_loosembb" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_KF_Cat == (-99+(10*2)) )*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "HM_A_KF_loosembb" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_KF_Cat == (-99+(10*3)) )*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",
      "HM_B_KF_loosembb" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_KF_Cat == (-99+(10*4)) )*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "XGBoost_btag77_85_tightScore_LowMass" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_Cat == 1111)*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight" 

   },

    "lumi" : {
      "mc16d" : 44386
    },

    "samples" : {

      "HH":	{
        "datafiles" : { 
          "mc16d" : "aMCnlo_Hwpp_hh_yybb.root"
        },
        "histoName" : "CutFlow_aMCnlo_Hwpp_hh_yybb_noDalitz_weighted"
      }
     }

}
