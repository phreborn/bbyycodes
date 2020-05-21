{
  "sequencer":["YieldCalculator","VariablePlotter"],

    "directories":{
	"mc16d" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h025/mc16d/Nominal/"
    },

    "dumper":{

       "mc16d" : true

    },

    "variables":{
        "m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 55,"lbins" : 105,"ubins" : 160}},
        "m_jj" :{"var":"HGamEventInfoAuxDyn.yybb_m_jj*0.001","bins":{"nbins" : 30,"lbins" : 0,"ubins" : 300}},
        "weight_2" : {"var": "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10} },
        "weight_BRFilterEff" : {"var": "HGamEventInfoAuxDyn.crossSectionBRfilterEff", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10} },
        "weight_HGam" : {"var": "HGamEventInfoAuxDyn.weight", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10} },
        "weight_bbyy" : {"var": "HGamEventInfoAuxDyn.yybb_weight", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10} },
        "weight_TrigSF" : {"var": "HGamEventInfoAuxDyn.weightTrigSF", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10} },
        "weight_vertexWeight" : {"var": "HGamEventInfoAuxDyn.vertexWeight", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10} },
        "weight_pileupWeight" : {"var": "HGamEventInfoAuxDyn.pileupWeight", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10} },
        "weight_SF" : {"var": "HGamEventInfoAuxDyn.weightSF", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10} },
        "weight_inital" : {"var": "HGamEventInfoAuxDyn.weightInitial", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10} },
        "weight_MC" : {"var": "EventInfoAuxDyn.mcEventWeights[0]", "bins": {"nbins" : 200,"lbins" : -10,"ubins" : 10} }
    },

    "selections": {
      
	"Pass_yy" : "HGamEventInfoAuxDyn.isPassed == 1",
        "Pass_yy_NoNegWeights": "HGamEventInfoAuxDyn.isPassed == 1 && EventInfoAuxDyn.mcEventWeights[0]>0",
	"Validation" : "HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_85_cutFlow == 6",
        "LM_A" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_Cat % 10) == 1 ))",
        "XGBoost_btag77_Nominal_looseScore_LMass" : "(HGamEventInfoAuxDyn.isPassed == 1 && ((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_Cat % 10) == 4))"
	
   },

    "lumi" : {
	"mc16d" : 44386
    },

    "samples" : {

      "HH":	{
        "datafiles" : { 
            "mc16d" : "mc16d.aMCnloHwpp_hh_yybb.MxAODDetailedNoSkim.e4419_a875_r10201_p4097_h025.root"
        },
        "histoName" : "CutFlow_aMCnlo_Hwpp_hh_yybb_noDalitz_weighted"
      },
      "ttH_PowHw7":     {
        "datafiles" : {
            "mc16d" : "mc16d.PowhegHw7_ttH125_fixweight.MxAODDetailedNoSkim.e7488_s3126_r10201_p4097_h025.root"
        },
        "histoName" : "CutFlow_PowhegHw7_ttH125_fixweight_noDalitz_weighted"
      },
      "ZH_PowPy8":     {
        "datafiles" : {
            "mc16d" : "mc16d.PowhegPy8_ZH125J.MxAODDetailed.e5743_s3126_r10201_p4097_h025.root"
        },
        "histoName" : "CutFlow_PowhegPy8_ZH125J_noDalitz_weighted"
      }
     }

}
