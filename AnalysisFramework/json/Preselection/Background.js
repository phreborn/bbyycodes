{
  "sequencer":["YieldCalculator","VariablePlotter"],

    "directories":{
      "mc16a" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h024/mc16a/Nominal/",
      "mc16d" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h024/mc16d/Nominal/",
      "mc16e" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h024/mc16e/Nominal/"
    },

	 "variables":{
		"m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 55,"lbins" : 105,"ubins" : 160}},
		"m_jj" :{"var":"HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_jj","bins":{"nbins" : 24,"lbins" : 60,"ubins" : 180}},
	        "pT_jj" :{"var":"HGamEventInfoAuxDyn.pT_jj","bins":{"nbins" : 100,"lbins" : 500,"ubins" : 500500}},
                "pT_yy" :{"var":"HGamEventInfoAuxDyn.pT_yy","bins":{"nbins" : 100,"lbins" : 500,"ubins" : 500500}},
                "m_yyjj_tilde" :{"var": "HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_yyjj_tilde","bins":{"nbins" : 30,"lbins" : 125,"ubins" : 1000}},
                "m_yyjj_tilde_HM" :{"var": "HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_yyjj_tilde","bins":{"nbins" : 26,"lbins" : 350,"ubins" : 1000}},
                "pT_jj_div_m_yyjj_tilde" :{"var":"HGamEventInfoAuxDyn.pT_jj/HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_yyjj_tilde","bins":{"nbins" : 100,"lbins" : 0,"ubins" : 1000}},
                "pT_yy_div_m_yyjj_tilde" :{"var":"HGamEventInfoAuxDyn.pT_yy/HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_yyjj_tilde","bins":{"nbins" : 100,"lbins" : 0,"ubins" : 1000}},
                "pT_jj_div_m_jj" :{"var":"HGamEventInfoAuxDyn.pT_jj/HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_jj","bins":{"nbins" : 100,"lbins" : 0,"ubins" : 5000}},
                "pT_yy_div_m_yy" :{"var":"HGamEventInfoAuxDyn.pT_yy/(HGamEventInfoAuxDyn.m_yy*0.001)","bins":{"nbins" : 100,"lbins" : 0,"ubins" : 5000}},
                "deltaR_yy" :{"var": "HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_deltaR_yy","bins":{"nbins" : 25,"lbins" : 0,"ubins" : 5}},
		"deltaR_jj" :{"var": "HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_deltaR_jj","bins":{"nbins" : 25,"lbins" : 0,"ubins" : 5}},
		"deltaR_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_deltaR_yyjj","bins":{"nbins" : 30,"lbins" : 0,"ubins" : 6}},
		"MET" :{"var": "HGamEventInfoAuxDyn.met_TST*0.001","bins":{"nbins" : 15,"lbins" : 0,"ubins" : 150}},
		"N_j" :{"var": "HGamEventInfoAuxDyn.N_j","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
		"N_j_central" :{"var": "HGamEventInfoAuxDyn.N_j_central","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
		"btag_score" :{"var": "yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[0].MV2c10bin+yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[1].MV2c10bin","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}}
	},



    "selections": {
	
        "Presel" : "(HGamEventInfoAuxDyn.isPassed && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[0].MV2c10bin >= 1 && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[1].MV2c10bin >= 1 && HGamEventInfoAuxDyn.N_lep == 0 && HGamEventInfoAuxDyn.N_j_central < 6 && HGamEventInfoAuxDyn.N_j_btag < 3 && HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_jj > 70.0 && HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_jj < 180.0)*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_weight"

    },



    "lumi" : {

      "mc16a" : 36100,
      "mc16d" : 43700,
      "mc16e" : 59900
    },

    "samples" : {

      "HH": 	{
        "datafiles" : { 
          "mc16a" : "mc16a_hh_yybb_NLO.root",
          "mc16d" : "mc16d_hh_yybb_NLO.root",
          "mc16e" : "mc16e_hh_yybb_NLO.root"
        },
        "histoName" : "CutFlow_aMCnlo_Hwpp_hh_yybb_noDalitz_weighted"
      },

      "ggH": 	{
        "datafiles" : { 
          "mc16a" : "mc16a.PowhegPy8_NNLOPS_ggH125.MxAODDetailed.e5607_s3126_r9364_p3665.h024.root",
          "mc16d" : "mc16d.PowhegPy8_NNLOPS_ggH125.MxAODDetailed.e5607_s3126_r10201_p3665.h024.root",
          "mc16e" : "mc16e.PowhegPy8_NNLOPS_ggH125.MxAODDetailed.e5607_s3126_r10724_p3665.h024.root"
        },
        "histoName" : "CutFlow_PowhegPy8_NNLOPS_ggH125_noDalitz_weighted"
      },

      "VBF":	{
        "datafiles" : { 	
          "mc16a" : "mc16a.PowhegPy8_NNPDF30_VBFH125.MxAODDetailed.e5720_s3126_r9364_p3665.h024.root",
          "mc16d" : "mc16d.PowhegPy8_NNPDF30_VBFH125.MxAODDetailed.e6636_s3126_r10201_p3665.h024.root",
          "mc16e" : "mc16d.PowhegPy8_NNPDF30_VBFH125.MxAODDetailed.e6636_s3126_r10201_p3665.h024.root"
        },
        "histoName" : "CutFlow_PowhegPy8_NNPDF30_VBFH125_noDalitz_weighted"
      }, 

      "WpH":	{
        "datafiles" : { 
          "mc16a" : "mc16a.PowhegPy8_WpH125J.MxAODDetailed.e5734_s3126_r9364_p3665.h024.root",
          "mc16d" : "mc16d.PowhegPy8_WpH125J.MxAODDetailed.e5734_s3126_r10201_p3665.h024.root",
          "mc16e" : "mc16e.PowhegPy8_WpH125J.MxAODDetailed.e5734_s3126_r10724_p3665.h024.root"
        },
        "histoName" : "CutFlow_PowhegPy8_WpH125J_noDalitz_weighted"
      },	

      "WmH":	{
        "datafiles" : { 
          "mc16a" : "mc16a.PowhegPy8_WmH125J.MxAODDetailed.e5734_s3126_r9364_p3665.h024.root",
          "mc16d" : "mc16d.PowhegPy8_WmH125J.MxAODDetailed.e5734_s3126_r10201_p3665.h024.root",
          "mc16e" : "mc16e.PowhegPy8_WmH125J.MxAODDetailed.e5734_s3126_r10724_p3665.h024.root"
        },
        "histoName" : "CutFlow_PowhegPy8_WmH125J_noDalitz_weighted"
      },

      "ZH":	{
        "datafiles" : { 
          "mc16a" : "mc16a.PowhegPy8_ZH125J.MxAODDetailed.e5743_s3126_r9364_p3665.h024.root",
          "mc16d" : "mc16d.PowhegPy8_ZH125J.MxAODDetailed.e5743_s3126_r10201_p3665.h024.root",
          "mc16e" : "mc16e.PowhegPy8_ZH125J.MxAODDetailed.e5743_s3126_r10724_p3665.h024.root"
        },
        "histoName" : "CutFlow_PowhegPy8_ZH125J_noDalitz_weighted"
      },   

      "ggZH":	{
        "datafiles" : { 
          "mc16a" : "mc16a.PowhegPy8_ggZH125.MxAODDetailed.e5762_s3126_r9364_p3665.h024.root",
          "mc16d" : "mc16d.PowhegPy8_ggZH125.MxAODDetailed.e5762_s3126_r10201_p3665.h024.root",
          "mc16e" : "mc16e.PowhegPy8_ggZH125.MxAODDetailed.e5762_s3126_r10724_p3665.h024.root"
        },
        "histoName" : "CutFlow_PowhegPy8_ggZH125_noDalitz_weighted"
      }, 

      "ttH":	{
        "datafiles" : { 
          "mc16a" : "mc16a.PowhegPy8_ttH125.MxAODDetailed.e6503_s3126_r9364_p3665.h024.root",
          "mc16d" : "mc16d.PowhegPy8_ttH125.MxAODDetailed.e6503_s3126_r10201_p3665.h024.root",
          "mc16e" : "mc16e.PowhegPy8_ttH125.MxAODDetailed.e6503_s3126_r10724_p3665.h024.root"
        },
        "histoName" : "CutFlow_PowhegPy8_ttH125_noDalitz_weighted"
      }, 

      "bbH":	{
        "datafiles" : { 
          "mc16a" : "mc16a.PowhegPy8_bbH125.MxAODDetailed.e6050_s3126_r9364_p3665.h024.root",
          "mc16d" : "mc16d.PowhegPy8_bbH125.MxAODDetailed.e6050_s3126_r10201_p3665.h024.root",
          "mc16e" : "mc16e.PowhegPy8_bbH125.MxAODDetailed.e6050_s3126_r10724_p3665.h024.root"
        },
        "histoName" : "CutFlow_PowhegPy8_bbH125_noDalitz_weighted"
      }, 

      "tWH":	{
        "datafiles" : { 
          "mc16a" : "mc16a.aMCnloHwpp_tWH125_yt_plus1.MxAODDetailed.e4394_s3126_r9364_p3665.h024.root",
          "mc16d" : "mc16d.aMCnloHwpp_tWH125_yt_plus1.MxAODDetailed.e4394_s3126_r10201_p3665.h024.root",
          "mc16e" : "mc16e.aMCnloHwpp_tWH125_yt_plus1.MxAODDetailed.e4394_s3126_r10724_p3665.h024.root"
        },
        "histoName" : "CutFlow_aMCnloHwpp_tWH125_yt_plus1_noDalitz_weighted"
      }, 

      "tHjb":	{
        "datafiles" : { 
          "mc16a" : "mc16a.aMCnloHwpp_tWH125_yt_plus1.MxAODDetailed.e4394_s3126_r9364_p3665.h024.root",
          "mc16d" : "mc16d.aMCnloHwpp_tWH125_yt_plus1.MxAODDetailed.e4394_s3126_r10201_p3665.h024.root",
          "mc16e" : "mc16e.aMCnloHwpp_tWH125_yt_plus1.MxAODDetailed.e4394_s3126_r10724_p3665.h024.root"
        },
        "histoName" : "CutFlow_aMCnloHwpp_tWH125_yt_plus1_noDalitz_weighted"
      },

      "ttyy_nohad":	{
        "datafiles" : { 	
          "mc16a" : "mc16a.MGPy8_ttgammagamma_noallhad_AF2.MxAODDetailed.e6542_a875_r9364_p3703.h024.root",
          "mc16d" : "mc16d.MGPy8_ttgammagamma_noallhad_AF2.MxAODDetailed.e6542_a875_r10201_p3703.h024.root",
          "mc16e" : "mc16e.MGPy8_ttgammagamma_noallhad_AF2.MxAODDetailed.e6542_a875_r10724_p3703.h024.root"
        },
        "histoName" : "CutFlow_MGPy8_ttgammagamma_noallhad_AF2_noDalitz_weighted",
        "color" : "3",
        "legendEntry" : "Non-hadronic #it{ttyy}"
      }, 

      "ttyy_had":	{
        "datafiles" : { 
          "mc16a" : "mc16a.MGPy8_ttgammagamma_allhad_AF2.MxAODDetailed.e6542_a875_r9364_p3703.h024.root",
          "mc16d" : "mc16d.MGPy8_ttgammagamma_allhad_AF2.MxAODDetailed.e6542_a875_r10201_p3703.h024.root",
          "mc16e" : "mc16e.MGPy8_ttgammagamma_allhad_AF2.MxAODDetailed.e6542_a875_r10724_p3703.h024.root"
        },
        "histoName" : "CutFlow_MGPy8_ttgammagamma_allhad_AF2_noDalitz_weighted",
        "color" : "2",
        "legendEntry" : "Hadronic #it{ttyy}"
      }
     }

}
