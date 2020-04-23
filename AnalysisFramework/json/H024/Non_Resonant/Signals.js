{
  "sequencer":["YieldCalculator","VariablePlotter"],

    "directories":{
      "mc16a" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h024/mc16a/Nominal/",
      "mc16d" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h024/mc16d/Nominal/",
      "mc16e" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h024/mc16e/Nominal/"
    },

    "variables":{
		"m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 55,"lbins" : 105,"ubins" : 160}},
                "m_jj" :{"var":"HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_jj","bins":{"nbins" : 22,"lbins" : 70,"ubins" : 180}},
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

      "LM_A" : "((HGamEventInfoAuxDyn.isPassed && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[0].MV2c10bin >= 1 && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[1].MV2c10bin >= 1 && HGamEventInfoAuxDyn.N_lep == 0 && HGamEventInfoAuxDyn.N_j_central < 6 && HGamEventInfoAuxDyn.N_j_btag < 3 && HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_jj >= 70.0 && HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_jj <= 180.0&& HGamEventInfoAuxDyn.yybb_nonRes_cutBased_discreteMV2c10pT_Cat == 1) && (HGamEventInfoAuxDyn.m_yy*0.001 < 120.0 || HGamEventInfoAuxDyn.m_yy*0.001 > 130.0 )  )*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_weight",
      "LM_B" : "((HGamEventInfoAuxDyn.isPassed && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[0].MV2c10bin >= 1 && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[1].MV2c10bin >= 1 && HGamEventInfoAuxDyn.N_lep == 0 && HGamEventInfoAuxDyn.N_j_central < 6 && HGamEventInfoAuxDyn.N_j_btag < 3 && HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_jj >= 70.0 && HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_jj <= 180.0&& HGamEventInfoAuxDyn.yybb_nonRes_cutBased_discreteMV2c10pT_Cat == 2) && (HGamEventInfoAuxDyn.m_yy*0.001 < 120.0 || HGamEventInfoAuxDyn.m_yy*0.001 > 130.0 )  )*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_weight",
      "HM_A" : "((HGamEventInfoAuxDyn.isPassed && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[0].MV2c10bin >= 1 && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[1].MV2c10bin >= 1 && HGamEventInfoAuxDyn.N_lep == 0 && HGamEventInfoAuxDyn.N_j_central < 6 && HGamEventInfoAuxDyn.N_j_btag < 3 && HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_jj >= 70.0 && HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_jj <= 180.0&& HGamEventInfoAuxDyn.yybb_nonRes_cutBased_discreteMV2c10pT_Cat == 3) && (HGamEventInfoAuxDyn.m_yy*0.001 < 120.0 || HGamEventInfoAuxDyn.m_yy*0.001 > 130.0 )  )*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_weight",
      "HM_B" : "((HGamEventInfoAuxDyn.isPassed && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[0].MV2c10bin >= 1 && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[1].MV2c10bin >= 1 && HGamEventInfoAuxDyn.N_lep == 0 && HGamEventInfoAuxDyn.N_j_central < 6 && HGamEventInfoAuxDyn.N_j_btag < 3 && HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_jj >= 70.0 && HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_jj <= 180.0&& HGamEventInfoAuxDyn.yybb_nonRes_cutBased_discreteMV2c10pT_Cat == 4) && (HGamEventInfoAuxDyn.m_yy*0.001 < 120.0 || HGamEventInfoAuxDyn.m_yy*0.001 > 130.0 )  )*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_weight",
      "Continuum" : "((HGamEventInfoAuxDyn.isPassed && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[0].MV2c10bin >= 1 && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[1].MV2c10bin >= 1 && HGamEventInfoAuxDyn.N_lep == 0 && HGamEventInfoAuxDyn.N_j_central < 6 && HGamEventInfoAuxDyn.N_j_btag < 3 && HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_jj >= 70.0 && HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_jj <= 180.0) && (HGamEventInfoAuxDyn.m_yy*0.001 < 120.0 || HGamEventInfoAuxDyn.m_yy*0.001 > 130.0 )  )*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_weight"

    },

    "lumi" : {

      "mc16a" : 36100,
      "mc16d" : 43700,
      "mc16e" : 59900
    },

    "samples" : {

      "HH":     {
        "datafiles" : {
          "mc16a" : "mc16a_hh_yybb_NLO.root",
          "mc16d" : "mc16d_hh_yybb_NLO.root",
          "mc16e" : "mc16e_hh_yybb_NLO.root"
        },
        "histoName" : "CutFlow_aMCnlo_Hwpp_hh_yybb_noDalitz_weighted" 
      },

      "HHlamMinus2": 	{
        "datafiles" : { 
          "mc16a" : "mc16a.MGPy8_hh_yybb_minus_lambda02_AF2.MxAODDetailed.e5504_a875_r9364_p3629.h024.root",
          "mc16d" : "mc16d.MGPy8_hh_yybb_minus_lambda02_AF2.MxAODDetailed.e5504_a875_r10201_p3629.h024.root",
          "mc16e" : "mc16e.MGPy8_hh_yybb_minus_lambda02_AF2.MxAODDetailed.e5504_a875_r10724_p3705.h024.root"
        },
        "histoName" : "CutFlow_MGPy8_hh_yybb_minus_lambda02_noDalitz_weighted"
      },

      "HHlamPlus2": 	{
        "datafiles" : { 
          "mc16a" : "mc16a.MGPy8_hh_yybb_plus_lambda02_AF2.MxAODDetailed.e5504_a875_r9364_p3629.h024.root",
          "mc16d" : "mc16d.MGPy8_hh_yybb_plus_lambda02_AF2.MxAODDetailed.e5504_a875_r10201_p3629.h024.root",
          "mc16e" : "mc16e.MGPy8_hh_yybb_plus_lambda02_AF2.MxAODDetailed.e5504_a875_r10724_p3705.h024.root"
        },
        "histoName" : "CutFlow_MGPy8_hh_yybb_plus_lambda02_noDalitz_weighted"
      },

      "HHlamMinus4": 	{
        "datafiles" : { 
          "mc16a" : "mc16a.MGPy8_hh_yybb_minus_lambda04_AF2.MxAODDetailed.e5504_a875_r9364_p3629.h024.root",
          "mc16d" : "mc16d.MGPy8_hh_yybb_minus_lambda04_AF2.MxAODDetailed.e5504_a875_r10201_p3629.h024.root",
          "mc16e" : "mc16e.MGPy8_hh_yybb_minus_lambda04_AF2.MxAODDetailed.e5504_a875_r10724_p3705.h024.root"
        },
        "histoName" : "CutFlow_MGPy8_hh_yybb_minus_lambda04_noDalitz_weighted"
      },

      "HHlamPlus4": 	{
        "datafiles" : { 
          "mc16a" : "mc16a.MGPy8_hh_yybb_plus_lambda04_AF2.MxAODDetailed.e5504_a875_r9364_p3629.h024.root",
          "mc16d" : "mc16d.MGPy8_hh_yybb_plus_lambda04_AF2.MxAODDetailed.e5504_a875_r10201_p3629.h024.root",
          "mc16e" : "mc16e.MGPy8_hh_yybb_plus_lambda04_AF2.MxAODDetailed.e5504_a875_r10724_p3705.h024.root"
        },
        "histoName" : "CutFlow_MGPy8_hh_yybb_plus_lambda04_noDalitz_weighted"
      },
      
      "HHlamMinus10": 	{
        "datafiles" : { 
          "mc16a" : "mc16a.MGPy8_hh_yybb_minus_lambda10_AF2.MxAODDetailed.e5504_a875_r9364_p3629.h024.root",
          "mc16d" : "mc16d.MGPy8_hh_yybb_minus_lambda10_AF2.MxAODDetailed.e5504_a875_r10201_p3629.h024.root",
          "mc16e" : "mc16e.MGPy8_hh_yybb_minus_lambda10_AF2.MxAODDetailed.e5504_a875_r10724_p3705.h024.root"
        },
        "histoName" : "CutFlow_MGPy8_hh_yybb_minus_lambda10_noDalitz_weighted"
      },

      "HHlamPlus10": 	{
        "datafiles" : { 
          "mc16a" : "mc16a.MGPy8_hh_yybb_plus_lambda10_AF2.MxAODDetailed.e5504_a875_r9364_p3629.h024.root",
          "mc16d" : "mc16d.MGPy8_hh_yybb_plus_lambda10_AF2.MxAODDetailed.e5504_a875_r10201_p3629.h024.root",
          "mc16e" : "mc16e.MGPy8_hh_yybb_plus_lambda10_AF2.MxAODDetailed.e5504_a875_r10724_p3705.h024.root"
        },
        "histoName" : "CutFlow_MGPy8_hh_yybb_plus_lambda10_noDalitz_weighted"
      }
    }
}
