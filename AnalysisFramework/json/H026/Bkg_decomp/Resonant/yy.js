{
  "sequencer":["VariablePlotter"],

    "directories":{
      "mc16a" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h026_diphotonselection/mc16a/",
      "mc16d" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h026_diphotonselection/mc16d/",
      "mc16e" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h026_diphotonselection/mc16e/"
    },

    "dumper":{
       "mc16a" : false,
       "mc16d" : false,
       "mc16e" : false
    
    },

    "variables":{
	"m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 55,"lbins" : 105,"ubins" : 160}},
        "N_j" :{"var": "HGamEventInfoAuxDyn.N_j","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "N_j_central" :{"var": "HGamEventInfoAuxDyn.N_j_central","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "m_jj" :{"var":"HGamEventInfoAuxDyn.yybb_m_jj*0.001","bins":{"nbins" : 30,"lbins" : 0,"ubins" : 300}},
        "m_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj*0.001","bins":{"nbins" : 160,"lbins" : 0,"ubins" : 1600}},
        "m_yyjj_cnstrnd" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_cnstrnd*0.001","bins":{"nbins" : 160,"lbins" : 0,"ubins" : 1600}},
        "m_yyjj_tilde" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_tilde*0.001","bins":{"nbins" : 160,"lbins" : 0,"ubins" : 1600}},
        "weight" : {"var": "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*HGamEventInfoAuxDyn.weightFJvt", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10} }

   },

    "selections": {
  
      "weight" : "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*HGamEventInfoAuxDyn.weightFJvt",

	 "X260toHH_BDT_Selection_h026_optimized" : "(1.17399) *(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.75 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((260.012-2*3.13066)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((260.012+2*3.13066)*1000))",
	"X280toHH_BDT_Selection_h026_optimized" : "(1.32877) * (HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((279.201-2*5.04804)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((279.201+2*5.04804)*1000))",
	"X300toHH_BDT_Selection_h026_optimized" : "(1.32877) * (HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((298.577-2*6.70871)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((298.577+2*6.70871)*1000))",
	"X325toHH_BDT_Selection_h026_optimized" : "(1.32877) * ( HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((323.806-2*7.449)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((323.806+2*7.449)*1000))",
	 "X350toHH_BDT_Selection_h026_optimized" : "(1.32877) * (HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((348.32-2*8.66209)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((348.32+2*8.66209)*1000))",
	"X400toHH_BDT_Selection_h026_optimized" : "(1.15894) * (HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.8 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((397.394-2*10.719)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((397.394+2*10.719)*1000))",
	"X450toHH_BDT_Selection_h026_optimized" : "(1.32877) * (HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((446.732-2*12.4305)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((446.732+2*12.4305)*1000))",
	"X500toHH_BDT_Selection_h026_optimized" : "(1.17399) * (HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.75 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((495.738-2*14.1286)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((495.738+2*14.1286)*1000))",
	"X550toHH_BDT_Selection_h026_optimized" : "(1.10187) *(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.6 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((544.868-2*15.6412)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((544.868+2*15.6412)*1000))",
	"X600toHH_BDT_Selection_h026_optimized" : "(1.57197) * (HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.45 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((594.493-2*16.6684)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((594.493+2*16.6684)*1000))",
	"X700toHH_BDT_Selection_h026_optimized" : "(1.28436) * (HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.2 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((693.149-2*18.8885)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((693.149+2*18.8885)*1000))",
	"X800toHH_BDT_Selection_h026_optimized" : "(1.18961) * (HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.1 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((790.638-2*21.3055)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((790.638+2*21.3055)*1000))",
	"X900toHH_BDT_Selection_h026_optimized" : "(1.28436) * (HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.2 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((888.031 - 4*23.4402)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((888.031+4*23.4402)*1000))",
	"X1000toHH_BDT_Selection_h026_optimized" : "(1.14906) * (HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.05 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((983.98-4*26.4073)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((983.98+4*26.4073)*1000))"
 
 
    },

  

    "lumi" : {
      "mc16a" : 36209.04, 
      "mc16d" : 44385.7,
      "mc16e" : 58450.1
    },

    "samples" : {
	
	 "yy":    {
        "datafiles" : {
          "mc16a" : "mc16a.Sherpa2_diphoton_myy_90_175.root",
          "mc16d" : "mc16d.Sherpa2_diphoton_myy_90_175.root",
          "mc16e" : "mc16e.Sherpa2_diphoton_myy_90_175.root"
        },
        "histoName" : "CutFlow_Sherpa2_myy_90_175_noDalitz_weighted"
      }

}

}
