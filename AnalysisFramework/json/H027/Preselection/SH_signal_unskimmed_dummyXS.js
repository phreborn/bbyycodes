{
  "sequencer":["YieldCalculator"],

    "directories":{
        "mc16a" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h027/mc16a/Nominal/",
        "mc16d" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h027/mc16d/Nominal/",
        "mc16e" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h027/mc16e/Nominal/"
    },

    "name":{
        "yields" : "XtoSH_unskimmed_h027_dummy_XS"
    },

   "dumper":{
       "mc16a" : true,
       "mc16d" : true,
       "mc16e" : true
    },

    "variables":{
	"m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 55,"lbins" : 105,"ubins" : 160}}

   },

    "selections": {
  
	"weight" : "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*HGamEventInfoAuxDyn.weightFJvt",
 	        
	"Preselection" : "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.m_yy*0.001 > 105 && HGamEventInfoAuxDyn.m_yy*0.001 < 160 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow >6)"
	
    },  

    "lumi" : {
	
	"mc16a" : 36207.66,
	"mc16d" : 44307.4,
	"mc16e" : 58450.1
    },

    "samples" : {
	
        "X170_S30":{
            "datafiles":{
                "mc16a" : "mc16a.Py8_XHS_X170_S030_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r9364_p4615_h027.root",
                "mc16d" : "mc16d.Py8_XHS_X170_S030_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10201_p4615_h027.root",
                "mc16e" : "mc16e.Py8_XHS_X170_S030_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10724_p4615_h027.root"
            },

         "histoName" :  "CutFlow_Py8_XHS_X170_S030_HyySbb_AF2_noDalitz_weighted"
        },

        "X180_S50":{
            "datafiles":{
                "mc16a" : "mc16a.Py8_XHS_X180_S050_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r9364_p4615_h027.root",
                "mc16d" : "mc16d.Py8_XHS_X180_S050_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10201_p4615_h027.root",
                "mc16e" : "mc16e.Py8_XHS_X180_S050_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10724_p4615_h027.root"
            },

         "histoName" :  "CutFlow_Py8_XHS_X180_S050_HyySbb_AF2_noDalitz_weighted"
        },

        "X185_S30":{
            "datafiles":{
                "mc16a" : "mc16a.Py8_XHS_X185_S030_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r9364_p4615_h027.root",
                "mc16d" : "mc16d.Py8_XHS_X185_S030_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10201_p4615_h027.root",
                "mc16e" : "mc16e.Py8_XHS_X185_S030_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10724_p4615_h027.root"
            },

         "histoName" :  "CutFlow_Py8_XHS_X185_S030_HyySbb_AF2_noDalitz_weighted"
        },

        "X190_S15":{
            "datafiles":{
                "mc16a" : "mc16a.Py8_XHS_X190_S015_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r9364_p4615_h027.root",
                "mc16d" : "mc16d.Py8_XHS_X190_S015_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10201_p4615_h027.root",
                "mc16e" : "mc16e.Py8_XHS_X190_S015_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10724_p4615_h027.root"
            },

         "histoName" :  "CutFlow_Py8_XHS_X190_S015_HyySbb_AF2_noDalitz_weighted"
        },

        "X190_S50":{
            "datafiles":{
                "mc16a" : "mc16a.Py8_XHS_X190_S050_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r9364_p4615_h027.root",
                "mc16d" : "mc16d.Py8_XHS_X190_S050_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10201_p4615_h027.root",
                "mc16e" : "mc16e.Py8_XHS_X190_S050_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10724_p4615_h027.root"
            },

         "histoName" :  "CutFlow_Py8_XHS_X190_S050_HyySbb_AF2_noDalitz_weighted"
        },


        "X200_S70":{
            "datafiles":{
                "mc16a" : "mc16a.Py8_XHS_X200_S070_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r9364_p4615_h027.root",
                "mc16d" : "mc16d.Py8_XHS_X200_S070_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10201_p4615_h027.root",
                "mc16e" : "mc16e.Py8_XHS_X200_S070_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10724_p4615_h027.root"
            },

         "histoName" :  "CutFlow_Py8_XHS_X200_S070_HyySbb_AF2_noDalitz_weighted"
        },

        "X205_S30":{
            "datafiles":{
                "mc16a" : "mc16a.Py8_XHS_X205_S030_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r9364_p4615_h027.root",
                "mc16d" : "mc16d.Py8_XHS_X205_S030_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10201_p4615_h027.root",
                "mc16e" : "mc16e.Py8_XHS_X205_S030_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10724_p4615_h027.root"
            },

         "histoName" :  "CutFlow_Py8_XHS_X205_S030_HyySbb_AF2_noDalitz_weighted"
        },

	"X205_S50":{
	    "datafiles":{
		"mc16a" : "mc16a.Py8_XHS_X205_S050_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r9364_p4615_h027.root",
		"mc16d" : "mc16d.Py8_XHS_X205_S050_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10201_p4615_h027.root",
		"mc16e" : "mc16e.Py8_XHS_X205_S050_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10724_p4615_h027.root"
	    },
	    
	 "histoName" : 	"CutFlow_Py8_XHS_X205_S050_HyySbb_AF2_noDalitz_weighted"
	},

        "X210_S15":{
            "datafiles":{
                "mc16a" : "mc16a.Py8_XHS_X210_S015_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r9364_p4615_h027.root",
                "mc16d" : "mc16d.Py8_XHS_X210_S015_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10201_p4615_h027.root",
                "mc16e" : "mc16e.Py8_XHS_X210_S015_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10724_p4615_h027.root"
            },

         "histoName" :  "CutFlow_Py8_XHS_X210_S015_HyySbb_AF2_noDalitz_weighted"
        },
        "X210_S70":{
            "datafiles":{
                "mc16a" : "mc16a.Py8_XHS_X210_S070_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r9364_p4615_h027.root",
                "mc16d" : "mc16d.Py8_XHS_X210_S070_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10201_p4615_h027.root",
                "mc16e" : "mc16e.Py8_XHS_X210_S070_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10724_p4615_h027.root"
            },

         "histoName" :  "CutFlow_Py8_XHS_X210_S070_HyySbb_AF2_noDalitz_weighted"
        },


        "X220_S90":{
            "datafiles":{
                "mc16a" : "mc16a.Py8_XHS_X220_S090_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r9364_p4615_h027.root",
                "mc16d" : "mc16d.Py8_XHS_X220_S090_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10201_p4615_h027.root",
                "mc16e" : "mc16e.Py8_XHS_X220_S090_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10724_p4615_h027.root"
            },

         "histoName" :  "CutFlow_Py8_XHS_X220_S090_HyySbb_AF2_noDalitz_weighted"
        },


        "X225_S30":{
            "datafiles":{
                "mc16a" : "mc16a.Py8_XHS_X225_S030_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r9364_p4615_h027.root",
                "mc16d" : "mc16d.Py8_XHS_X225_S030_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10201_p4615_h027.root",
                "mc16e" : "mc16e.Py8_XHS_X225_S030_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10724_p4615_h027.root"
            },

         "histoName" :  "CutFlow_Py8_XHS_X225_S030_HyySbb_AF2_noDalitz_weighted"
        },

        "X225_S50":{
            "datafiles":{
                "mc16a" : "mc16a.Py8_XHS_X225_S050_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r9364_p4615_h027.root",
                "mc16d" : "mc16d.Py8_XHS_X225_S050_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10201_p4615_h027.root",
                "mc16e" : "mc16e.Py8_XHS_X225_S050_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10724_p4615_h027.root"
            },

         "histoName" :  "CutFlow_Py8_XHS_X225_S050_HyySbb_AF2_noDalitz_weighted"
        },

        "X225_S70":{
            "datafiles":{
                "mc16a" : "mc16a.Py8_XHS_X225_S070_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r9364_p4615_h027.root",
                "mc16d" : "mc16d.Py8_XHS_X225_S070_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10201_p4615_h027.root",
                "mc16e" : "mc16e.Py8_XHS_X225_S070_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10724_p4615_h027.root"
            },

         "histoName" :  "CutFlow_Py8_XHS_X225_S070_HyySbb_AF2_noDalitz_weighted"
        },

        "X230_S15":{
            "datafiles":{
                "mc16a" : "mc16a.Py8_XHS_X230_S015_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r9364_p4615_h027.root",
                "mc16d" : "mc16d.Py8_XHS_X230_S015_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10201_p4615_h027.root",
                "mc16e" : "mc16e.Py8_XHS_X230_S015_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10724_p4615_h027.root"
            },

         "histoName" :  "CutFlow_Py8_XHS_X230_S015_HyySbb_AF2_noDalitz_weighted"
        },

        "X230_S90":{
            "datafiles":{
                "mc16a" : "mc16a.Py8_XHS_X230_S090_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r9364_p4615_h027.root",
                "mc16d" : "mc16d.Py8_XHS_X230_S090_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10201_p4615_h027.root",
                "mc16e" : "mc16e.Py8_XHS_X230_S090_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10724_p4615_h027.root"
            },

         "histoName" :  "CutFlow_Py8_XHS_X230_S090_HyySbb_AF2_noDalitz_weighted"
        },

        "X230_S100":{
            "datafiles":{
                "mc16a" : "mc16a.Py8_XHS_X230_S100_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r9364_p4615_h027.root",
                "mc16d" : "mc16d.Py8_XHS_X230_S100_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10201_p4615_h027.root",
                "mc16e" : "mc16e.Py8_XHS_X230_S100_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10724_p4615_h027.root"
            },

         "histoName" :  "CutFlow_Py8_XHS_X230_S100_HyySbb_AF2_noDalitz_weighted"
        },

        "X240_S100":{
            "datafiles":{
                "mc16a" : "mc16a.Py8_XHS_X240_S100_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r9364_p4615_h027.root",
                "mc16d" : "mc16d.Py8_XHS_X240_S100_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10201_p4615_h027.root",
                "mc16e" : "mc16e.Py8_XHS_X240_S100_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10724_p4615_h027.root"
            },

         "histoName" :  "CutFlow_Py8_XHS_X240_S100_HyySbb_AF2_noDalitz_weighted"
        },


        "X240_S110":{
            "datafiles":{
                "mc16a" : "mc16a.Py8_XHS_X240_S110_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r9364_p4615_h027.root",
                "mc16d" : "mc16d.Py8_XHS_X240_S110_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10201_p4615_h027.root",
                "mc16e" : "mc16e.Py8_XHS_X240_S110_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10724_p4615_h027.root"
            },

         "histoName" :  "CutFlow_Py8_XHS_X240_S110_HyySbb_AF2_noDalitz_weighted"
        },


        "X245_S30":{
            "datafiles":{
		"mc16a" : "mc16a.Py8_XHS_X245_S030_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r9364_p4615_h027.root",
                "mc16d" : "mc16d.Py8_XHS_X245_S030_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10201_p4615_h027.root",
                "mc16e" : "mc16e.Py8_XHS_X245_S030_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10724_p4615_h027.root"
            },

         "histoName" :  "CutFlow_Py8_XHS_X245_S030_HyySbb_AF2_noDalitz_weighted"
        },

        "X245_S50":{
            "datafiles":{
		"mc16a" : "mc16a.Py8_XHS_X245_S050_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r9364_p4615_h027.root",
                "mc16d" : "mc16d.Py8_XHS_X245_S050_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10201_p4615_h027.root",
                "mc16e" : "mc16e.Py8_XHS_X245_S050_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10724_p4615_h027.root"
            },

         "histoName" :  "CutFlow_Py8_XHS_X245_S050_HyySbb_AF2_noDalitz_weighted"
        },

        "X245_S70":{
            "datafiles":{
		"mc16a" : "mc16a.Py8_XHS_X245_S070_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r9364_p4615_h027.root",
                "mc16d" : "mc16d.Py8_XHS_X245_S070_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10201_p4615_h027.root",
                "mc16e" : "mc16e.Py8_XHS_X245_S070_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10724_p4615_h027.root"
            },

         "histoName" :  "CutFlow_Py8_XHS_X245_S070_HyySbb_AF2_noDalitz_weighted"
        },

        "X245_S90":{
            "datafiles":{
		"mc16a" : "mc16a.Py8_XHS_X245_S090_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r9364_p4615_h027.root",
                "mc16d" : "mc16d.Py8_XHS_X245_S090_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10201_p4615_h027.root",
                "mc16e" : "mc16e.Py8_XHS_X245_S090_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10724_p4615_h027.root"
            },

         "histoName" :  "CutFlow_Py8_XHS_X245_S090_HyySbb_AF2_noDalitz_weighted"
        },

        "X250_S15":{
            "datafiles":{
                "mc16a" : "mc16a.Py8_XHS_X250_S015_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r9364_p4615_h027.root",
                "mc16d" : "mc16d.Py8_XHS_X250_S015_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10201_p4615_h027.root",
                "mc16e" : "mc16e.Py8_XHS_X250_S015_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10724_p4615_h027.root"
            },

         "histoName" :  "CutFlow_Py8_XHS_X250_S015_HyySbb_AF2_noDalitz_weighted"
        },

        "X250_S100":{
            "datafiles":{
                "mc16a" : "mc16a.Py8_XHS_X250_S100_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r9364_p4615_h027.root",
                "mc16d" : "mc16d.Py8_XHS_X250_S100_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10201_p4615_h027.root",
                "mc16e" : "mc16e.Py8_XHS_X250_S100_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10724_p4615_h027.root"
            },

         "histoName" :  "CutFlow_Py8_XHS_X250_S100_HyySbb_AF2_noDalitz_weighted"
        },

        "X250_S110":{
            "datafiles":{
                "mc16a" : "mc16a.Py8_XHS_X250_S110_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r9364_p4615_h027.root",
                "mc16d" : "mc16d.Py8_XHS_X250_S110_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10201_p4615_h027.root",
                "mc16e" : "mc16e.Py8_XHS_X250_S110_HyySbb_AF2.MxAODDetailedNoSkim.e8312_a875_r10724_p4615_h027.root"
            },

         "histoName" :  "CutFlow_Py8_XHS_X250_S110_HyySbb_AF2_noDalitz_weighted"
        }

    }
}
