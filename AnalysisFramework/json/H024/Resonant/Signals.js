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
                "m_yyjj_tilde" :{"var": "HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_yyjj_tilde","bins":{"nbins" : 30,"lbins" : 250,"ubins" : 1000}},
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
		"btag_score" :{"var": "yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[0].MV2c10bin+yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[1].MV2c10bin","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
		"m_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_yyjj","bins":{"nbins" : 30,"lbins" : 250,"ubins" : 1000}},
		"m_yyjj_HM" :{"var": "HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_yyjj","bins":{"nbins" : 26,"lbins" : 350,"ubins" : 1000}},
		"m_yyjj_cnstrnd" :{"var": "HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_yyjj_cnstrnd","bins":{"nbins" : 30,"lbins" : 250,"ubins" : 1000}},
		"m_yyjj_cnstrnd_HM" :{"var": "HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_yyjj_cnstrnd","bins":{"nbins" : 26,"lbins" : 350,"ubins" : 1000}}
    },


    "selections": {

      "Resonant" : "(HGamEventInfoAuxDyn.isPassed && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[0].MV2c10bin >= 1 && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[1].MV2c10bin >= 1 && HGamEventInfoAuxDyn.N_lep == 0 && HGamEventInfoAuxDyn.N_j_central < 6 && HGamEventInfoAuxDyn.N_j_btag == 2 && HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_jj >= 80.0 && HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_jj <= 140.0 && HGamEventInfoAuxDyn.m_yy*0.001 < 160.0 && HGamEventInfoAuxDyn.m_yy*0.001 > 105.0 && HGamEventInfoAuxDyn.pT_y1/(HGamEventInfoAuxDyn.m_yy*0.001) > 0.35 && HGamEventInfoAuxDyn.pT_y2/(HGamEventInfoAuxDyn.m_yy*0.001) > 0.25 && HGamEventInfoAuxDyn.pT_j1>40 && HGamEventInfoAuxDyn.pT_j2 > 25)*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_weight",

      "Continuum_CR" : "((HGamEventInfoAuxDyn.isPassed && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[0].MV2c10bin == 0 && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[1].MV2c10bin == 0 && HGamEventInfoAuxDyn.N_lep == 0 && HGamEventInfoAuxDyn.N_j_central < 6 && HGamEventInfoAuxDyn.N_j_btag < 3 && HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_jj >= 70.0 && HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_jj <= 180.0) )*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_weight"

    },

    "lumi" : {

      "mc16a" : 36100,
      "mc16d" : 43700,
      "mc16e" : 59900
    },

    "samples" : {

      "X251toHH": 	{
        "datafiles" : { 
          "mc16a" : "mc16a.MGH7_X251tohh_bbyy.MxAOD-yybbDetailed.e7251_s3126_r9364_p3714.h024.root",
          "mc16d" : "mc16d.MGH7_X251tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10201_p3714.h024.root",
          "mc16e" : "mc16e.MGH7_X251tohh_bbyy.MxAOD-yybbDetailed.e7251_s3126_r10724_p3714.h024.root"
        },
        "histoName" : "CutFlow_MGH7_X251tohh_bbyy_AF2_noDalitz_weighted"
      },
      
      "X260toHH": 	{
        "datafiles" : { 
          "mc16a" : "mc16a.MGH7_X260tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r9364_p3714.h024.root",
          "mc16d" : "mc16d.MGH7_X260tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10201_p3714.h024.root",
          "mc16e" : "mc16e.MGH7_X260tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10724_p3714.h024.root"
        },
        "histoName" : "CutFlow_MGH7_X260tohh_bbyy_AF2_noDalitz_weighted"
      },
      
      "X280toHH": 	{
        "datafiles" : { 
          "mc16a" : "mc16a.MGH7_X280tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r9364_p3714.h024.root",
          "mc16d" : "mc16d.MGH7_X280tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10201_p3714.h024.root",
          "mc16e" : "mc16e.MGH7_X280tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10724_p3714.h024.root"
        },
        "histoName" : "CutFlow_MGH7_X280tohh_bbyy_AF2_noDalitz_weighted"
      },
      
      "X300toHH": 	{
        "datafiles" : { 
          "mc16a" : "mc16a.MGH7_X300tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r9364_p3714.h024.root",
          "mc16d" : "mc16d.MGH7_X300tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10201_p3714.h024.root",
          "mc16e" : "mc16e.MGH7_X300tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10724_p3714.h024.root"
        },
        "histoName" : "CutFlow_MGH7_X300tohh_bbyy_AF2_noDalitz_weighted"
      },
      
      "X325toHH": 	{
        "datafiles" : { 
          "mc16a" : "mc16a.MGH7_X325tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r9364_p3714.h024.root",
          "mc16d" : "mc16d.MGH7_X325tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10201_p3714.h024.root",
          "mc16e" : "mc16e.MGH7_X325tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10724_p3714.h024.root"
        },
        "histoName" : "CutFlow_MGH7_X325tohh_bbyy_AF2_noDalitz_weighted"
      },
      
      "X350toHH": 	{
        "datafiles" : { 
          "mc16a" : "mc16a.MGH7_X350tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r9364_p3714.h024.root",
          "mc16d" : "mc16d.MGH7_X350tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10201_p3714.h024.root",
          "mc16e" : "mc16e.MGH7_X350tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10724_p3714.h024.root"
        },
        "histoName" : "CutFlow_MGH7_X350tohh_bbyy_AF2_noDalitz_weighted"
      },
      
      "X400toHH": 	{
        "datafiles" : { 
          "mc16a" : "mc16a.MGH7_X400tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r9364_p3714.h024.root",
          "mc16d" : "mc16d.MGH7_X400tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10201_p3714.h024.root",
          "mc16e" : "mc16e.MGH7_X400tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10724_p3714.h024.root"
        },
        "histoName" : "CutFlow_MGH7_X400tohh_bbyy_AF2_noDalitz_weighted"
      },
      
      "X450toHH": 	{
        "datafiles" : { 
          "mc16a" : "mc16a.MGH7_X450tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r9364_p3714.h024.root",
          "mc16d" : "mc16d.MGH7_X450tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10201_p3714.h024.root",
          "mc16e" : "mc16e.MGH7_X450tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10724_p3714.h024.root"
        },
        "histoName" : "CutFlow_MGH7_X450tohh_bbyy_AF2_noDalitz_weighted"
      },
      
      "X500toHH": 	{
        "datafiles" : { 
          "mc16a" : "mc16a.MGH7_X500tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r9364_p3714.h024.root",
          "mc16d" : "mc16d.MGH7_X500tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10201_p3714.h024.root",
          "mc16e" : "mc16e.MGH7_X500tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10724_p3714.h024.root"
        },
        "histoName" : "CutFlow_MGH7_X500tohh_bbyy_AF2_noDalitz_weighted"
      },
      
      "X550toHH": 	{
        "datafiles" : { 
          "mc16a" : "mc16a.MGH7_X550tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r9364_p3714.h024.root",
          "mc16d" : "mc16d.MGH7_X550tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10201_p3714.h024.root",
          "mc16e" : "mc16e.MGH7_X550tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10724_p3714.h024.root"
        },
        "histoName" : "CutFlow_MGH7_X550tohh_bbyy_AF2_noDalitz_weighted"
      },
      
      "X600toHH": 	{
        "datafiles" : { 
          "mc16a" : "mc16a.MGH7_X600tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r9364_p3714.h024.root",
          "mc16d" : "mc16d.MGH7_X600tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10201_p3714.h024.root",
          "mc16e" : "mc16e.MGH7_X600tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10724_p3714.h024.root"
        },
        "histoName" : "CutFlow_MGH7_X600tohh_bbyy_AF2_noDalitz_weighted"
      },
      
      "X700toHH": 	{
        "datafiles" : { 
          "mc16a" : "mc16a.MGH7_X700tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r9364_p3714.h024.root",
          "mc16d" : "mc16d.MGH7_X700tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10201_p3714.h024.root",
          "mc16e" : "mc16e.MGH7_X700tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10724_p3714.h024.root"
        },
        "histoName" : "CutFlow_MGH7_X700tohh_bbyy_AF2_noDalitz_weighted"
      },
      
      "X800toHH": 	{
        "datafiles" : { 
          "mc16a" : "mc16a.MGH7_X800tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r9364_p3714.h024.root",
          "mc16d" : "mc16d.MGH7_X800tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10201_p3714.h024.root",
          "mc16e" : "mc16e.MGH7_X800tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10724_p3714.h024.root"
        },
        "histoName" : "CutFlow_MGH7_X800tohh_bbyy_AF2_noDalitz_weighted"
      },
      
      "X900toHH": 	{
        "datafiles" : { 
          "mc16a" : "mc16a.MGH7_X900tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r9364_p3714.h024.root",
          "mc16d" : "mc16d.MGH7_X900tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10201_p3714.h024.root",
          "mc16e" : "mc16e.MGH7_X900tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10724_p3714.h024.root"
        },
        "histoName" : "CutFlow_MGH7_X900tohh_bbyy_AF2_noDalitz_weighted"
      },
      
      "X1000toHH": 	{
        "datafiles" : { 
          "mc16a" : "mc16a.MGH7_X1000tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r9364_p3714.h024.root",
          "mc16d" : "mc16d.MGH7_X1000tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10201_p3714.h024.root",
          "mc16e" : "mc16e.MGH7_X1000tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10724_p3714.h024.root"
        },
        "histoName" : "CutFlow_MGH7_X1000tohh_bbyy_AF2_noDalitz_weighted"
      },
      
      "X2000toHH": 	{
        "datafiles" : { 
          "mc16a" : "mc16a.MGH7_X2000tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r9364_p3714.h024.root",
          "mc16d" : "mc16d.MGH7_X2000tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10201_p3714.h024.root",
          "mc16e" : "mc16e.MGH7_X2000tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10724_p3714.h024.root"
        },
        "histoName" : "CutFlow_MGH7_X2000tohh_bbyy_AF2_noDalitz_weighted"
      },

      "X3000toHH": 	{
        "datafiles" : { 
          "mc16a" : "mc16a.MGH7_X3000tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r9364_p3714.h024.root",
          "mc16d" : "mc16d.MGH7_X3000tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10201_p3714.h024.root",
          "mc16e" : "mc16e.MGH7_X3000tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10724_p3714.h024.root"
        },
        "histoName" : "CutFlow_MGH7_X3000tohh_bbyy_AF2_noDalitz_weighted"
      }
    }

}
