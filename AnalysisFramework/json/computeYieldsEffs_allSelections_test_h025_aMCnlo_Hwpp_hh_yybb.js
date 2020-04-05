{
  "sequencer":["YieldCalculator","VariablePlotter"],

    "directories":{
      "mc16d" : "root://eosatlas.cern.ch//eos/user/e/epetit/Higgs/yybb/data/h025/aMCnlo_Hwpp_hh_yybb/data-MxAOD/"
    },

    "variables":{
	"m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 55,"lbins" : 105,"ubins" : 160}}
    },

    "selections": {

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

      "TEST" : "HGamEventInfoAuxDyn.isPassedPreselection&&HGamEventInfoAuxDyn.isPassedTriggerMatch&&HGamEventInfoAuxDyn.isPassedPID&&HGamEventInfoAuxDyn.isPassedIsolation&&HGamEventInfoAuxDyn.isPassedRelPtCuts&&HGamEventInfoAuxDyn.isPassedMassCut&&EventInfoAuxDyn.passTrig_HLT_g35_medium_g25_medium_L12EM20VH"
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
