{
"sequencer":["YieldCalculator"],

    "name":{
        "yields" : "HH_preselection_skimmed_samples"
    },

  "directories": {
    "mc16a": "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h027_diphotonselection_2jets/mc16a/",
    "mc16d": "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h027_diphotonselection_2jets/mc16d/",
    "mc16e": "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h027_diphotonselection_2jets/mc16e/"
  },

  "dumper": {
    "mc16a": true,
    "mc16d": true,
    "mc16e": true
  },

  "variables": {
    "m_yy": {
      "var": "HGamEventInfoAuxDyn.m_yy*0.001",
      "bins": {
        "nbins": 55,
        "lbins": 105,
        "ubins": 160
      }	
    },

    "m_jj": {
      "var": "HGamEventInfoAuxDyn.yybb_m_jj*0.001",
      "bins": {
        "nbins": 60,
        "lbins": 0,
        "ubins": 300
      }
    },

      "weight": {
      "var": "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*FJvt",
      "bins": {
        "nbins": 200,
        "lbins": -10,
        "ubins": 10
      }
    }
  },
  "selections": {

    "weight": "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*HGamEventInfoAuxDyn.weightFJvt",

    "Preselection": "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.m_yy*0.001 > 105 && HGamEventInfoAuxDyn.m_yy*0.001 < 160 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow > 6)"

  },

  "lumi": {
    "mc16a": 36207.66,
    "mc16d": 44307.4,
    "mc16e": 58450.1
  },

  "samples": {      
    "ttH": {
      "datafiles": {
        "mc16a": "mc16a.PowhegPy8_ttH125_fixweight.root",
        "mc16d": "mc16d.PowhegPy8_ttH125_fixweight.root",
        "mc16e": "mc16e.PowhegPy8_ttH125_fixweight.root"
      },
      "histoName": "CutFlow_PowhegPy8_ttH125_fixweight_noDalitz_weighted"
    },
    "yy": {
      "datafiles": {
        "mc16a": "mc16a.Sherpa2_diphoton_myy_90_175.root",
        "mc16d": "mc16d.Sherpa2_diphoton_myy_90_175.root",
        "mc16e": "mc16e.Sherpa2_diphoton_myy_90_175.root"
      },
      "histoName": "CutFlow_Sherpa2_myy_90_175_noDalitz_weighted"
    },
    "ggH": {
      "datafiles": {
        "mc16a": "mc16a.PowhegPy8_NNLOPS_ggH125.root",
        "mc16d": "mc16d.PowhegPy8_NNLOPS_ggH125.root",
        "mc16e": "mc16e.PowhegPy8_NNLOPS_ggH125.root"
      },
      "histoName": "CutFlow_PowhegPy8_NNLOPS_ggH125_noDalitz_weighted"
    }
  }
}
