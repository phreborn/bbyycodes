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
	"m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 25,"lbins" : 105,"ubins" : 160}},
        "N_j" :{"var": "HGamEventInfoAuxDyn.N_j","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "N_j_central" :{"var": "HGamEventInfoAuxDyn.N_j_central","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "m_jj" :{"var":"HGamEventInfoAuxDyn.yybb_m_jj*0.001","bins":{"nbins" : 30,"lbins" : 0,"ubins" : 300}},
        "m_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj*0.001","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 1600}},
        "m_yyjj_cnstrnd" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_cnstrnd*0.001","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 1600}},
        "m_yyjj_tilde" :{"var": "HGamEventInfoAuxDyn.yybb_BCal_m_yyjj_tilde*0.001","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 1600}},
        "weight" : {"var": "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*HGamEventInfoAuxDyn.weightFJvt", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10} }

   },

    "selections": {
  
      "weight" : "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*HGamEventInfoAuxDyn.weightFJvt",


      "X1000toHH_BDT_Selection_h026_optimized" : "(HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && 1/sqrt( pow(0.65,2)+pow(0.35,2) ) * sqrt( pow(0.65,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(0.35,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.05 && HGamEventInfoAuxDyn.yybb_BCal_m_yyjj_tilde > ((983.98-4*26.4073)*1000) &&  HGamEventInfoAuxDyn.yybb_BCal_m_yyjj_tilde < ((983.98+4*26.4073)*1000))"
    
 
    },

  

    "lumi" : {
      "mc16a" : 36207.66, 
      "mc16d" : 44307.4,
      "mc16e" : 58450.1
    },

    "samples" : {

	"Resonance":{
        "datafiles" : { 
          "mc16a" : "mc16a.MGH7_X1000tohh_bbyy_AF2.root",
          "mc16d" : "mc16d.MGH7_X1000tohh_bbyy_AF2.root",
          "mc16e" : "mc16e.MGH7_X1000tohh_bbyy_AF2.root"
        },
        "histoName" : "CutFlow_MGH7_X1000tohh_bbyy_AF2_noDalitz_weighted"
      },
	"HH":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegH7_HHbbyy_cHHH01d0.root",
          "mc16d" : "mc16d.PowhegH7_HHbbyy_cHHH01d0.root",
          "mc16e" : "mc16e.PowhegH7_HHbbyy_cHHH01d0.root"
        },
        "histoName" : "CutFlow_PowhegH7_HHbbyy_cHHH01d0_noDalitz_weighted"
      },

      "VBF":  {
        "datafiles" : {
          "mc16a" : "mc16a.MGH7_hh_bbyy_vbf_l1cvv1cv1.root",
          "mc16d" : "mc16d.MGH7_hh_bbyy_vbf_l1cvv1cv1.root",
          "mc16e" : "mc16e.MGH7_hh_bbyy_vbf_l1cvv1cv1.root"
        },
        "histoName": "CutFlow_MGH7_hh_bbyy_vbf_l1cvv1cv1_noDalitz_weighted"
      },

      "ttH_PowhegPy8":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8_ttH125_fixweight.root",
          "mc16d" : "mc16d.PowhegPy8_ttH125_fixweight.root",
          "mc16e" : "mc16e.PowhegPy8_ttH125_fixweight.root"
        },
        "histoName" : "CutFlow_PowhegPy8_ttH125_fixweight_noDalitz_weighted"
      },


  "VBFH_PowhegPy8":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8EG_NNPDF30_VBFH125.root",
          "mc16d" : "mc16d.PowhegPy8EG_NNPDF30_VBFH125.root",
          "mc16e" : "mc16e.PowhegPy8EG_NNPDF30_VBFH125.root"
        },
        "histoName" : "CutFlow_PowhegPy8EG_NNPDF30_VBFH125_noDalitz_weighted"
      },



      "ZH_PowhegPy8":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8_ZH125J.root",
          "mc16d" : "mc16d.PowhegPy8_ZH125J.root",
          "mc16e" : "mc16e.PowhegPy8_ZH125J.root"
        },
        "histoName": "CutFlow_PowhegPy8_ZH125J_noDalitz_weighted"
      },
 
       "ggZH_PowhegPy8":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8_ggZH125.root",
          "mc16d" : "mc16d.PowhegPy8_ggZH125.root",
          "mc16e" : "mc16e.PowhegPy8_ggZH125.root"
        },
        "histoName" : "CutFlow_PowhegPy8_ggZH125_noDalitz_weighted"
      },

      "ggH_PowhegPy8":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8_NNLOPS_ggH125.root",
          "mc16d" : "mc16d.PowhegPy8_NNLOPS_ggH125.root",
          "mc16e" : "mc16e.PowhegPy8_NNLOPS_ggH125.root"
        },
        "histoName" : "CutFlow_PowhegPy8_NNLOPS_ggH125_noDalitz_weighted"
      },


      "ttyy_allhad":    {
        "datafiles" : {
          "mc16a" : "mc16a.MGPy8_ttgammagamma_allhad_AF2.root",
          "mc16d" : "mc16d.MGPy8_ttgammagamma_allhad_AF2.root",
          "mc16e" : "mc16e.MGPy8_ttgammagamma_allhad_AF2.root"
        },
        "histoName" : "CutFlow_MGPy8_ttgammagamma_allhad_AF2_noDalitz_weighted"
      },

      "ttyy_noallhad":    {
        "datafiles" : {
          "mc16a" : "mc16a.MGPy8_ttgammagamma_noallhad_AF2.root",
          "mc16d" : "mc16d.MGPy8_ttgammagamma_noallhad_AF2.root",
          "mc16e" : "mc16e.MGPy8_ttgammagamma_noallhad_AF2.root"
        },
        "histoName" : "CutFlow_MGPy8_ttgammagamma_noallhad_AF2_noDalitz_weighted"
      },

      "WmH_PowhegPy8":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8_WmH125J.root",
          "mc16d" : "mc16d.PowhegPy8_WmH125J.root",
          "mc16e" : "mc16e.PowhegPy8_WmH125J.root"
        },
        "histoName" : "CutFlow_PowhegPy8_WmH125J_noDalitz_weighted"
      },


      "WpH_PowhegPy8":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8_WpH125J.root",
          "mc16d" : "mc16d.PowhegPy8_WpH125J.root",
          "mc16e" : "mc16e.PowhegPy8_WpH125J.root"
        },
        "histoName" : "CutFlow_PowhegPy8_WpH125J_noDalitz_weighted"
      },


      "bbH":    {
        "datafiles" : {
          "mc16a" : "mc16a.PowhegPy8_bbH125.root",
          "mc16d" : "mc16d.PowhegPy8_bbH125.root",
          "mc16e" : "mc16e.PowhegPy8_bbH125.root"
        },
        "histoName" : "CutFlow_PowhegPy8_bbH125_noDalitz_weighted"
      },

      "tHjb":    {
        "datafiles" : {
          "mc16a" : "mc16a.aMCnloPy8_tHjb125_4fl_shw_fix.root",
          "mc16d" : "mc16d.aMCnloPy8_tHjb125_4fl_shw_fix.root",
          "mc16e" : "mc16e.aMCnloPy8_tHjb125_4fl_shw_fix.root"
        },
        "histoName" : "CutFlow_aMCnloPy8_tHjb125_4fl_noDalitz_weighted"
      },

      "tWH":    {
        "datafiles" : {
          "mc16a" : "mc16a.aMCnloPy8_tWH125.root",
          "mc16d" : "mc16d.aMCnloPy8_tWH125.root",
          "mc16e" : "mc16e.aMCnloPy8_tWH125.root"
        },
        "histoName" : "CutFlow_aMCnloPy8_tWH125_noDalitz_weighted"
      } 
     }

}
