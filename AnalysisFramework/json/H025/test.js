{
  "sequencer":["YieldCalculator","VariablePlotter"],

    "directories":{
	"mc16d" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h025/mc16d/Nominal/",
	"mc16e" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h025/mc16d/Nominal/"
    },

    "dumper":{

       "mc16d" : true,
       "mc16e" : true

    },

    "variables":{
        "m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 55,"lbins" : 105,"ubins" : 160}},
        "N_j" :{"var": "HGamEventInfoAuxDyn.N_j","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "N_j_central" :{"var": "HGamEventInfoAuxDyn.N_j_central","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "m_jj" :{"var":"HGamEventInfoAuxDyn.yybb_m_jj*0.001","bins":{"nbins" : 30,"lbins" : 0,"ubins" : 300}},
        "m_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj*0.001","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 1600}},
        "m_yyjj_cnstrnd" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_cnstrnd*0.001","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 1600}},
        "weight_2" : {"var": "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10} },
        "weight_BRFilterEff" : {"var": "HGamEventInfoAuxDyn.crossSectionBRfilterEff", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10} },
        "weight_HGam" : {"var": "HGamEventInfoAuxDyn.weight", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10} },
        "weight_bbyy" : {"var": "HGamEventInfoAuxDyn.yybb_weight", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10} }
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
            "mc16d" : "mc16d.aMCnloHwpp_hh_yybb.MxAODDetailedNoSkim.e4419_a875_r10201_p4097_h025.root",
	    "mc16e" : "mc16d.aMCnloHwpp_hh_yybb.MxAODDetailedNoSkim.e4419_a875_r10201_p4097_h025.root"
        },
        "histoName" : "CutFlow_aMCnlo_Hwpp_hh_yybb_noDalitz_weighted"
      }
     }

}
