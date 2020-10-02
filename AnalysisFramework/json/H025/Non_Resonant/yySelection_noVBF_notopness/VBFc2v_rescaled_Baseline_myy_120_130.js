{
  "sequencer":["VariablePlotter"],

    "directories":{
      "mc16a" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/mc16a/",
      "mc16d" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/mc16d/",
      "mc16e" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/mc16e/"
    },

   "dumper":{

       "mc16a" : true,
       "mc16d" : true,
       "mc16e" : true

    },

    "variables":{
        "m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 55,"lbins" : 105,"ubins" : 160}},
        "N_j" :{"var": "HGamEventInfoAuxDyn.N_j","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "N_j_central" :{"var": "HGamEventInfoAuxDyn.N_j_central","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "m_jj" :{"var":"HGamEventInfoAuxDyn.yybb_m_jj*0.001","bins":{"nbins" : 60,"lbins" : 0,"ubins" : 300}},
        "m_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj*0.001","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 1600}},
        "m_yyjj_cnstrnd" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_cnstrnd*0.001","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 1600}},
        "m_yyjj_tilde" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_tilde*0.001","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 1600}},
        "deltaR_yy" :{"var": "HGamEventInfoAuxDyn.yybb_deltaR_yy","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 4}},
        "deltaR_jj" :{"var": "HGamEventInfoAuxDyn.yybb_deltaR_jj","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 4}},
        "deltaR_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_deltaR_yyjj","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 4}},
        "weight" : {"var": "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight/0.81771", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10}},
        "weight_no_scale" : {"var": "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10}}      
    },

    "selections": {
      "weight" : "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight/0.81771",
      "Validation" : "HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6",
      "XGBoost_btag77_Nominal_BCal_tightScore_HMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat) % 10) == 1)   && HGamEventInfoAuxDyn.m_yy*0.001 > 120 && HGamEventInfoAuxDyn.m_yy*0.001 < 130 )",
      "XGBoost_btag77_Nominal_BCal_looseScore_HMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat) % 10) == 2)   && HGamEventInfoAuxDyn.m_yy*0.001 > 120 && HGamEventInfoAuxDyn.m_yy*0.001 < 130 )",
      "XGBoost_btag77_Nominal_BCal_tightScore_LMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat) % 10) == 3)   && HGamEventInfoAuxDyn.m_yy*0.001 > 120 && HGamEventInfoAuxDyn.m_yy*0.001 < 130 )",
      "XGBoost_btag77_Nominal_BCal_looseScore_LMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat) % 10) == 4)   && HGamEventInfoAuxDyn.m_yy*0.001 > 120 && HGamEventInfoAuxDyn.m_yy*0.001 < 130 )"


   },

    "lumi" : {
      "mc16a" : 36209.04,
      "mc16d" : 44385.7,
      "mc16e" : 58450.1
    },

    "samples" : {


      "VBF_rescale_l0cvv0cv1":    {
        "datafiles" : {
          "mc16a" : "mc16a.MGH7_hh_bbyy_vbf_l0cvv0cv1.root",
          "mc16d" : "mc16d.MGH7_hh_bbyy_vbf_l0cvv0cv1.root",
          "mc16e" : "mc16e.MGH7_hh_bbyy_vbf_l0cvv0cv1.root"
        },
        "histoName" : "CutFlow_MGH7_hh_bbyy_vbf_l0cvv0cv1_noDalitz_weighted"
      },

      "VBF_rescale_l0cvv1cv1":    {
        "datafiles" : {
          "mc16a" : "mc16a.MGH7_hh_bbyy_vbf_l0cvv1cv1.root",
          "mc16d" : "mc16d.MGH7_hh_bbyy_vbf_l0cvv1cv1.root",
          "mc16e" : "mc16e.MGH7_hh_bbyy_vbf_l0cvv1cv1.root"
        },
        "histoName" : "CutFlow_MGH7_hh_bbyy_vbf_l0cvv1cv1_noDalitz_weighted"
      },

      "VBF_rescale_l10cvv1cv1":    {
        "datafiles" : {
          "mc16a" : "mc16a.MGH7_hh_bbyy_vbf_l10cvv1cv1.root",
          "mc16d" : "mc16d.MGH7_hh_bbyy_vbf_l10cvv1cv1.root",
          "mc16e" : "mc16e.MGH7_hh_bbyy_vbf_l10cvv1cv1.root"
        },
        "histoName" : "CutFlow_MGH7_hh_bbyy_vbf_l10cvv1cv1_noDalitz_weighted"
      },

      "VBF_rescale_l11cvv1cv1p5":    {
        "datafiles" : {
          "mc16a" : "mc16a.MGH7_hh_bbyy_vbf_l11cvv1cv1p5.root",
          "mc16d" : "mc16d.MGH7_hh_bbyy_vbf_l11cvv1cv1p5.root",
          "mc16e" : "mc16e.MGH7_hh_bbyy_vbf_l11cvv1cv1p5.root"
        },
        "histoName" : "CutFlow_MGH7_hh_bbyy_vbf_l11cvv1cv1p5_noDalitz_weighted"
      },

      "VBF_rescale_l1cvv0cv0p5":    {
        "datafiles" : {
          "mc16a" : "mc16a.MGH7_hh_bbyy_vbf_l1cvv0cv0p5.root",
          "mc16d" : "mc16d.MGH7_hh_bbyy_vbf_l1cvv0cv0p5.root",
          "mc16e" : "mc16e.MGH7_hh_bbyy_vbf_l1cvv0cv0p5.root"
        },
        "histoName" : "CutFlow_MGH7_hh_bbyy_vbf_l1cvv0cv0p5_noDalitz_weighted"
      },

      "VBF_rescale_l1cvv0cv1":    {
        "datafiles" : {
          "mc16a" : "mc16a.MGH7_hh_bbyy_vbf_l1cvv0cv1.root",
          "mc16d" : "mc16d.MGH7_hh_bbyy_vbf_l1cvv0cv1.root",
          "mc16e" : "mc16e.MGH7_hh_bbyy_vbf_l1cvv0cv1.root"
        },
        "histoName" : "CutFlow_MGH7_hh_bbyy_vbf_l1cvv0cv1_noDalitz_weighted"
      },

      "VBF_rescale_l1cvv0p5cv1":    {
        "datafiles" : {
          "mc16a" : "mc16a.MGH7_hh_bbyy_vbf_l1cvv0p5cv1.root",
          "mc16d" : "mc16d.MGH7_hh_bbyy_vbf_l1cvv0p5cv1.root",
          "mc16e" : "mc16e.MGH7_hh_bbyy_vbf_l1cvv0p5cv1.root"
        },
        "histoName" : "CutFlow_MGH7_hh_bbyy_vbf_l1cvv0p5cv1_noDalitz_weighted"
      },

     "VBF_rescale_l1cvv1p5cv1":    {
        "datafiles" : {
          "mc16a" : "mc16a.MGH7_hh_bbyy_vbf_l1cvv1p5cv1.root",
          "mc16d" : "mc16d.MGH7_hh_bbyy_vbf_l1cvv1p5cv1.root",
          "mc16e" : "mc16e.MGH7_hh_bbyy_vbf_l1cvv1p5cv1.root"
        },
        "histoName" : "CutFlow_MGH7_hh_bbyy_vbf_l1cvv1p5cv1_noDalitz_weighted"
      },

      "VBF_rescale_l1cvv2cv1":    {
        "datafiles" : {
          "mc16a" : "mc16a.MGH7_hh_bbyy_vbf_l1cvv2cv1.root",
          "mc16d" : "mc16d.MGH7_hh_bbyy_vbf_l1cvv2cv1.root",
          "mc16e" : "mc16e.MGH7_hh_bbyy_vbf_l1cvv2cv1.root"
        },
        "histoName" : "CutFlow_MGH7_hh_bbyy_vbf_l1cvv2cv1_noDalitz_weighted"
      },

      "VBF_rescale_l1cvv4cv1":    {
        "datafiles" : {
          "mc16a" : "mc16a.MGH7_hh_bbyy_vbf_l1cvv4cv1.root",
          "mc16d" : "mc16d.MGH7_hh_bbyy_vbf_l1cvv4cv1.root",
          "mc16e" : "mc16e.MGH7_hh_bbyy_vbf_l1cvv4cv1.root"
        },
        "histoName" : "CutFlow_MGH7_hh_bbyy_vbf_l1cvv4cv1_noDalitz_weighted"
      },

      "VBF_rescale_l2cvv1cv1":    {
        "datafiles" : {
          "mc16a" : "mc16a.MGH7_hh_bbyy_vbf_l2cvv1cv1.root",
          "mc16d" : "mc16d.MGH7_hh_bbyy_vbf_l2cvv1cv1.root",
          "mc16e" : "mc16e.MGH7_hh_bbyy_vbf_l2cvv1cv1.root"
        },
        "histoName" : "CutFlow_MGH7_hh_bbyy_vbf_l2cvv1cv1_noDalitz_weighted"
      }
      
     
     }

}

