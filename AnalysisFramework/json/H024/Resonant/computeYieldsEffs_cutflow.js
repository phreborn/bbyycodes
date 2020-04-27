{
  "sequencer":["YieldCalculator"],

    "directories":{
	"mc16a" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h024/mc16a/Nominal/",      
	"mc16d" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h024/mc16d/Nominal/",
	"mc16e" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h024/mc16e/Nominal/"
    },

    "variables":{
      "N_j" :{"var": "HGamEventInfoAuxDyn.N_j","bins":{"nbins" : 10,"lbins" : 0,"ubins" : 10}}
    },


    "selections": {

	"weight": "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_weight",
	"A_NoCuts"     : "(1)",
	"B_isPassed"    : "(HGamEventInfoAuxDyn.isPassed)",
	"C_MinTwoCentralJets" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central >= 2)",
	"D_yybbTopoJets": "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central >= 2 && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[0].MV2c10bin >= 1 && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[1].MV2c10bin >= 1)",
	"E_FourthBtagVeto"   : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central >= 2 && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[0].MV2c10bin >= 1 && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[1].MV2c10bin >= 1 && HGamEventInfoAuxDyn.N_j_btag < 3)",
	"F_Lepton_veto" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central >= 2 && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[0].MV2c10bin >= 1 && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[1].MV2c10bin >= 1 && HGamEventInfoAuxDyn.N_j_btag < 3 && HGamEventInfoAuxDyn.N_lep == 0)",
	"G_SixthJetVeto"  : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central >= 2 && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[0].MV2c10bin >= 1 && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[1].MV2c10bin >= 1 && HGamEventInfoAuxDyn.N_j_btag < 3 && HGamEventInfoAuxDyn.N_lep == 0 && HGamEventInfoAuxDyn.N_j < 6)",
	"H_bbHiggsWindow": "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central >= 2 && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[0].MV2c10bin >= 1 && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[1].MV2c10bin >= 1 && HGamEventInfoAuxDyn.N_j_btag < 3 && HGamEventInfoAuxDyn.N_lep == 0 && HGamEventInfoAuxDyn.N_j < 6 && HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_jj > 80 && HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_jj < 140)",
	"I_m_yyjjWindow"  : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central >= 2 && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[0].MV2c10bin >= 1 && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[1].MV2c10bin >= 1 && HGamEventInfoAuxDyn.N_j_btag < 3 && HGamEventInfoAuxDyn.N_lep == 0 && HGamEventInfoAuxDyn.N_j < 6 && HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_jj > 80 && HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_jj < 140 && HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_yyjj_tilde >= 289.03 && HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_yyjj_tilde <= 312.06)",
	"J_yyHiggsWindow": "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central >= 2 && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[0].MV2c10bin >= 1 && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[1].MV2c10bin >= 1 && HGamEventInfoAuxDyn.N_j_btag < 3 && HGamEventInfoAuxDyn.N_lep == 0 && HGamEventInfoAuxDyn.N_j < 6 && HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_jj > 80 && HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_jj < 140 && HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_yyjj_tilde >= 289.03 && HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_yyjj_tilde <= 312.06 && HGamEventInfoAuxDyn.m_yy/1000 > 120 && HGamEventInfoAuxDyn.m_yy/1000 < 130)"
                                                                                                                                                                             
    },

    "lumi" : {

      "mc16a" : 36207.66,
      "mc16d" : 44307.4,
      "mc16e" : 58450.1
    },

    "samples" : {

      "X300toHH": 	{
        "datafiles" : { 
          "mc16a" : "mc16a.MGH7_X300tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r9364_p3714.h024.root",
          "mc16d" : "mc16d.MGH7_X300tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10201_p3714.h024.root",
          "mc16e" : "mc16e.MGH7_X300tohh_bbyy_AF2.MxAOD-yybbDetailed.e7251_a875_r10724_p3714.h024.root"
        },
        "histoName" : "CutFlow_MGH7_X300tohh_bbyy_AF2_noDalitz_weighted"
      },
      "ZH":	{
        "datafiles" : { 
          "mc16a" : "mc16a.PowhegPy8_ZH125J.MxAODDetailed.e5743_s3126_r9364_p3665.h024.root",
          "mc16d" : "mc16d.PowhegPy8_ZH125J.MxAODDetailed.e5743_s3126_r10201_p3665.h024.root",
          "mc16e" : "mc16e.PowhegPy8_ZH125J.MxAODDetailed.e5743_s3126_r10724_p3665.h024.root"
        },
        "histoName" : "CutFlow_PowhegPy8_ZH125J_noDalitz_weighted"
      }   

}
}
