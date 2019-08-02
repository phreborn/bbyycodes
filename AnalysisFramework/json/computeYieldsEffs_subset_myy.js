{

    "directories":{
    			"mc16a" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h024/mc16a/Nominal/",
    			"mc16d" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h024/mc16d/Nominal/",
    			"mc16e" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h024/mc16e/Nominal/"
    },

	"variables":{
		"m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 55,"lbins" : 105,"ubins" : 160}}
	},

    
    "selections": {
    
    			"LM_A" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_nonRes_cutBased_discreteMV2c10pT_Cat == 1  )*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_weight",
    			"LM_B" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_nonRes_cutBased_discreteMV2c10pT_Cat == 2  )*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_weight",
    			"HM_A" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_nonRes_cutBased_discreteMV2c10pT_Cat == 3  )*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_weight",
    			"HM_B" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_nonRes_cutBased_discreteMV2c10pT_Cat == 4  )*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_weight"

    },

    "lumi" : {
  
    	"mc16a" : 36100,
    	"mc16d" : 43700,
     	"mc16e" : 60000
    },

    "samples" : {
    
        "HH": 	{
		"datafiles" : { 
		"mc16a" : "mc16a.aMCnloHwpp_hh_yybb_AF2.MxAODDetailed.e4419_a875_r9364_p3629.h024.root",
	      	"mc16d" : "mc16d.aMCnloHwpp_hh_yybb_AF2.MxAODDetailed.e4419_a875_r10201_p3629.h024.root",
	      	"mc16e" : "mc16d.aMCnloHwpp_hh_yybb_AF2.MxAODDetailed.e4419_a875_r10201_p3629.h024.root"
		},
	      	"histoName" : "CutFlow_aMCnlo_Hwpp_hh_yybb_noDalitz_weighted"
	      	},
		
	"ttH":	{
		"datafiles" : { 
		"mc16a" : "mc16a.PowhegPy8_ttH125.MxAODDetailed.e6503_s3126_r9364_p3665.h024.root",
		"mc16d" : "mc16d.PowhegPy8_ttH125.MxAODDetailed.e6503_s3126_r10201_p3665.h024.root",
		"mc16e" : "mc16e.PowhegPy8_ttH125.MxAODDetailed.e6503_s3126_r10724_p3665.h024.root"
		},
		"histoName" : "CutFlow_PowhegPy8_ttH125_noDalitz_weighted"
		}
		

    }

}
