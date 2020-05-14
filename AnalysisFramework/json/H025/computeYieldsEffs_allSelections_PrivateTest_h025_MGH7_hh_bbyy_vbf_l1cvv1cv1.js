{
  "sequencer":["YieldCalculator","VariablePlotter"],

    "directories":{
      "mc16d" : "root://eosatlas.cern.ch//eos/user/e/epetit/Higgs/yybb/data/h025/MGH7_hh_bbyy_vbf_l1cvv1cv1/data-MxAOD/"
    },

    "variables":{
	"m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 55,"lbins" : 105,"ubins" : 160}},
        "N_j" :{"var": "HGamEventInfoAuxDyn.N_j","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "N_j_central" :{"var": "HGamEventInfoAuxDyn.N_j_central","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "m_jj" :{"var":"HGamEventInfoAuxDyn.yybb_m_jj*0.001","bins":{"nbins" : 30,"lbins" : 0,"ubins" : 300}},
        "m_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj*0.001","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 1600}},
        "m_yyjj_cnstrnd" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_cnstrnd*0.001","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 1600}},
        "m_yyjj_tilde" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_tilde*0.001","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 1600}}
    },

    "selections": {

      "Pass_yy" : "HGamEventInfoAuxDyn.isPassed",

      "TEST" : "HGamEventInfoAuxDyn.isPassedPreselection&&HGamEventInfoAuxDyn.isPassedTriggerMatch&&HGamEventInfoAuxDyn.isPassedPID&&HGamEventInfoAuxDyn.isPassedIsolation&&HGamEventInfoAuxDyn.isPassedRelPtCuts&&HGamEventInfoAuxDyn.isPassedMassCut&&EventInfoAuxDyn.passTrig_HLT_g35_medium_g25_medium_L12EM20VH",

      "Validation" : "HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_btag77_85_cutFlow == 6", 

      "XGBoost_btag77_85_tightScore_LowMass" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_85_Cat == 1111)*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

       "XGBoost_btag77_VBF" : "(HGamEventInfoAuxDyn.isPassed && (HGamEventInfoAuxDyn.yybb_btag77_vbf_selected == 1))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "XGBoost_btag77_85_VBF" : "(HGamEventInfoAuxDyn.isPassed && (HGamEventInfoAuxDyn.yybb_btag77_85_vbf_selected == 1))*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight" 

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
