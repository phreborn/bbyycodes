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
        "m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 22,"lbins" : 105,"ubins" : 160}},
        "N_j" :{"var": "HGamEventInfoAuxDyn.N_j","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "N_j_central" :{"var": "HGamEventInfoAuxDyn.N_j_central","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "m_jj" :{"var":"HGamEventInfoAuxDyn.yybb_m_jj*0.001","bins":{"nbins" : 30,"lbins" : 0,"ubins" : 300}},
        "m_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj*0.001","bins":{"nbins" : 40,"lbins" : 200,"ubins" : 1400}},
        "m_yyjj_cnstrnd" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_cnstrnd*0.001","bins":{"nbins" : 40,"lbins" : 200,"ubins" : 1400}},
        "m_yyjj_tilde" :{"var": "HGamEventInfoAuxDyn.yybb_BCal_m_yyjj_tilde*0.001","bins":{"nbins" : 40,"lbins" : 200,"ubins" : 1400}},
        "weight" : {"var": "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*FJvt", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10} }
     
    },

    "selections": {
	
	"weight" : "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*HGamEventInfoAuxDyn.weightFJvt",
	"X251toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.7)",
        "X260toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.75)",
      "X270toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.8)",
      "X280toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 )",
      "X290toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 )",
        "X300toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 )",
	"X3125toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85)",
        "X325toHH_BDT_Selection_h026_optimized" : "( HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 )",
        "X350toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 )",
	"X3375toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85)",
	"X375toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.9)",
        "X400toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.8)",
	"X425toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85)",
         "X450toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 )",
	"X475toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.8)",
        "X500toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.75)",
         "X550toHH_BDT_Selection_h026_optimized" : "( HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.6)",
        "X600toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.45 )",
         "X700toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.2 )",
        "X800toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.1 )",
        "X900toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.2 )",
        "X1000toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.05 )"


   },

    "lumi" : {
      "mc16a" : 36207.66,
      "mc16d" : 44307.4,
      "mc16e" : 58450.1
    },

    "samples" : {

      "ttyy_allhad_m_yyjj":    {
        "datafiles" : {
          "mc16a" : "mc16a.MGPy8_ttgammagamma_allhad_AF2.root",
          "mc16d" : "mc16d.MGPy8_ttgammagamma_allhad_AF2.root",
          "mc16e" : "mc16e.MGPy8_ttgammagamma_allhad_AF2.root"
        },
        "histoName" : "CutFlow_MGPy8_ttgammagamma_allhad_AF2_noDalitz_weighted"
      },

      "ttyy_noallhad_m_yyjj":    {
        "datafiles" : {
          "mc16a" : "mc16a.MGPy8_ttgammagamma_noallhad_AF2.root",
          "mc16d" : "mc16d.MGPy8_ttgammagamma_noallhad_AF2.root",
          "mc16e" : "mc16e.MGPy8_ttgammagamma_noallhad_AF2.root"
        },
        "histoName" : "CutFlow_MGPy8_ttgammagamma_noallhad_AF2_noDalitz_weighted"
      }

     }

}
