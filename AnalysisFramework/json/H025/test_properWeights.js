{
  "sequencer":["YieldCalculator","VariablePlotter"],

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
        "m_jj" :{"var":"HGamEventInfoAuxDyn.yybb_m_jj*0.001","bins":{"nbins" : 30,"lbins" : 0,"ubins" : 300}},
        "weight" : {"var": "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10} }
    },

    "selections": {

     
        "weight" : "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",
	"Pass_yy" : "(HGamEventInfoAuxDyn.isPassed == 1)",
        "Pass_yy_NoNegWeights": "HGamEventInfoAuxDyn.isPassed == 1 && EventInfoAuxDyn.mcEventWeights[0]>0",
	"Validation" : "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_85_cutFlow == 6)",
        "LM_A" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_Cat % 10) == 1 ))",
        "XGBoost_btag77_Nominal_looseScore_LMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_Cat % 10) == 4))"
	
   },

    "lumi" : {
        "mc16a" : 36209.04,
        "mc16d" : 44385.7,
        "mc16e" : 58450.1
    },

    "samples" : {

      "HH":	{
        "datafiles" : { 
          "mc16a" : "mc16a.aMCnloHwpp_hh_yybb_AF2.MxAODDetailedNoSkim.e4419_a875_r9364_p4097_h025.root",
          "mc16d" : "mc16d.aMCnloHwpp_hh_yybb_AF2.MxAODDetailedNoSkim.e4419_a875_r10201_p4097_h025.root",
          "mc16e" : "mc16e.aMCnloHwpp_hh_yybb_AF2.MxAODDetailedNoSkim.e4419_a875_r10724_p4097_h025.root"
        },
        "histoName" : "CutFlow_aMCnlo_Hwpp_hh_yybb_noDalitz_weighted"
      }
     }

}
