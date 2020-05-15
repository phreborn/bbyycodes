{
  "sequencer":["YieldCalculator","VariablePlotter"],

    "directories":{
	"mc16d" : "root://eosatlas.cern.ch//eos/user/e/epetit/Higgs/yybb/data/h025/aMCnlo_Hwpp_hh_yybb/data-MxAOD/",
	"mc16e" : "root://eosatlas.cern.ch//eos/user/e/epetit/Higgs/yybb/data/h025/aMCnlo_Hwpp_hh_yybb/data-MxAOD/"
    },

    "variables":{
        "m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 55,"lbins" : 105,"ubins" : 160}},
        "N_j" :{"var": "HGamEventInfoAuxDyn.N_j","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "N_j_central" :{"var": "HGamEventInfoAuxDyn.N_j_central","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "m_jj" :{"var":"HGamEventInfoAuxDyn.yybb_m_jj*0.001","bins":{"nbins" : 30,"lbins" : 0,"ubins" : 300}},
        "m_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj*0.001","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 1600}},
        "m_yyjj_cnstrnd" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_cnstrnd*0.001","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 1600}}
    },

    "selections": {
      
	"Pass_yy" : "HGamEventInfoAuxDyn.isPassed == 1",
	"Validation" : "HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_85_cutFlow == 6",
        "LM_A" : "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_Cat == ((10*1)+1) )",
        "CutBased_Selection" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central >= 2 && HGamAntiKt4EMPFlowJets_BTagging201903AuxDyn.DL1r_bin@.size()>=2 && HGamAntiKt4EMPFlowJets_BTagging201903AuxDyn.DL1r_bin[0]>=1 && HGamAntiKt4EMPFlowJets_BTagging201903AuxDyn.DL1r_bin[1]>=1 )"
 
	
   },

    "lumi" : {
	"mc16d" : 44386,
	"mc16e" : 60000
    },

    "samples" : {

      "HH":	{
        "datafiles" : { 
            "mc16d" : "aMCnlo_Hwpp_hh_yybb.root",
	    "mc16e" : "aMCnlo_Hwpp_hh_yybb.root"
        },
        "histoName" : "CutFlow_aMCnlo_Hwpp_hh_yybb_noDalitz_weighted"
      }
     }

}
