{
  "sequencer":["YieldCalculator","VariablePlotter"],

    "directories":{
      "mc16d" : "root://eosatlas.cern.ch//eos/user/e/epetit/Higgs/yybb/data/h025/MGH7_hh_bbyy_vbf_l1cvv1cv1/data-MxAOD/"
    },

    "variables":{
	"m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 55,"lbins" : 105,"ubins" : 160}}
    },

    "selections": {

      "TEST" : "HGamEventInfoAuxDyn.isPassedPreselection&&HGamEventInfoAuxDyn.isPassedTriggerMatch&&HGamEventInfoAuxDyn.isPassedPID&&HGamEventInfoAuxDyn.isPassedIsolation&&HGamEventInfoAuxDyn.isPassedRelPtCuts&&HGamEventInfoAuxDyn.isPassedMassCut&&EventInfoAuxDyn.passTrig_HLT_g35_medium_g25_medium_L12EM20VH",

      "XGBoost_btag77_85_tightScore_LowMass" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_Cat == 1111)*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight" 

   },

    "lumi" : {
      "mc16d" : 44386
    },

    "samples" : {

      "HH":	{
        "datafiles" : { 
          "mc16d" : "MGH7_hh_bbyy_vbf_l1cvv1cv1.root"
        },
        "histoName": "CutFlow_MGH7_hh_bbyy_vbf_l1cvv1cv1_noDalitz_weighted"
      }
     }

}
