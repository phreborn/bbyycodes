{
    "sequencer":["YieldCalculator"],

    "name":{
        "yields" : "HH_presel_bkg_h27_unskimmed"
    },

  "directories": {
    "mc16a": "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h027/mc16a/Nominal/",
    "mc16d": "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h027/mc16d/Nominal/",
    "mc16e": "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h027/mc16e/Nominal/"
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

    "Preselection": "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.m_yy*0.001 > 105 && HGamEventInfoAuxDyn.m_yy*0.001 < 160 &&  HGamEventInfoAuxDyn.yybb_btag77_cutFlow > 6)"

  },

  "lumi": {
    "mc16a": 36207.66,
    "mc16d": 44307.4,
    "mc16e": 58450.1
  },
   
    "samples": {
      
      "HH": {
      "datafiles": {
        "mc16a": "mc16a.PowhegPy8_HHbbyy_cHHH01d0.MxAODDetailedNoSkim.e8222_s3126_r9364_p4239_h027.root",
        "mc16d": "mc16d.PowhegPy8_HHbbyy_cHHH01d0.MxAODDetailedNoSkim.e8222_s3126_r10201_p4239_h027.root",
        "mc16e": "mc16e.PowhegPy8_HHbbyy_cHHH01d0.MxAODDetailedNoSkim.e8222_s3126_r10724_p4239_h027.root"
      },
      "histoName": "CutFlow_PowhegPy8_HHbbyy_cHHH01d0_noDalitz_weighted"
    },

    "VBFH": {
      "datafiles": {
        "mc16a": "mc16a.PowhegPy8EG_NNPDF30_VBFH125.MxAODDetailedNoSkim.e6970_s3126_r9364_p4180_h027.root",
        "mc16d": "mc16d.PowhegPy8EG_NNPDF30_VBFH125.MxAODDetailedNoSkim.e6970_s3126_r10201_p4180_h027.root",
        "mc16e": "mc16e.PowhegPy8EG_NNPDF30_VBFH125.MxAODDetailedNoSkim.e6970_s3126_r10724_p4180_h027.root"
      },
      "histoName": "CutFlow_PowhegPy8EG_NNPDF30_VBFH125_noDalitz_weighted"
    },
	"ZH": {
      "datafiles": {
        "mc16a": "mc16a.PowhegPy8_ZH125J.MxAODDetailedNoSkim.e5743_s3126_r9364_p4207_h027.root",
        "mc16d": "mc16d.PowhegPy8_ZH125J.MxAODDetailedNoSkim.e5743_s3126_r10201_p4207_h027.root",
        "mc16e": "mc16e.PowhegPy8_ZH125J.MxAODDetailedNoSkim.e5743_s3126_r10724_p4207_h027.root"
      },
      "histoName": "CutFlow_PowhegPy8_ZH125J_noDalitz_weighted"
    },
    "ggZH": {
      "datafiles": {
        "mc16a": "mc16a.PowhegPy8_ggZH125.MxAODDetailedNoSkim.e5762_s3126_r9364_p4207_h027.root",
        "mc16d": "mc16d.PowhegPy8_ggZH125.MxAODDetailedNoSkim.e5762_s3126_r10201_p4207_h027.root",
        "mc16e": "mc16e.PowhegPy8_ggZH125.MxAODDetailedNoSkim.e5762_s3126_r10724_p4207_h027.root"
      },
      "histoName": "CutFlow_PowhegPy8_ggZH125_noDalitz_weighted"
    },

    "ttyy_allhad": {
	"datafiles": {
        "mc16a": "mc16a.MGPy8_ttgammagamma_allhad_AF2.MxAODDetailed.e6542_a875_r9364_p4204_h027.root",
        "mc16d": "mc16d.MGPy8_ttgammagamma_allhad_AF2.MxAODDetailed.e6542_a875_r10201_p4204_h027.root",
        "mc16e": "mc16e.MGPy8_ttgammagamma_allhad_AF2.MxAODDetailed.e6542_a875_r10724_p4204_h027.root"
      },
      "histoName": "CutFlow_MGPy8_ttgammagamma_allhad_AF2_noDalitz_weighted"
    },
    "ttyy_noallhad": {
      "datafiles": {
        "mc16a": "mc16a.MGPy8_ttgammagamma_noallhad_AF2.MxAODDetailed.e6542_a875_r9364_p4204_h027.root",
        "mc16d": "mc16d.MGPy8_ttgammagamma_noallhad_AF2.MxAODDetailed.e6542_a875_r10201_p4204_h027.root",
        "mc16e": "mc16e.MGPy8_ttgammagamma_noallhad_AF2.MxAODDetailed.e6542_a875_r10724_p4204_h027.root"
      },
      "histoName": "CutFlow_MGPy8_ttgammagamma_noallhad_AF2_noDalitz_weighted"
    },
    "WmH": {
      "datafiles": {
        "mc16a": "mc16a.PowhegPy8_WmH125J.MxAODDetailedNoSkim.e5734_s3126_r9364_p4207_h027.root",
        "mc16d": "mc16d.PowhegPy8_WmH125J.MxAODDetailedNoSkim.e5734_s3126_r10201_p4207_h027.root",
        "mc16e": "mc16e.PowhegPy8_WmH125J.MxAODDetailedNoSkim.e5734_s3126_r10724_p4207_h027.root"
      },
      "histoName": "CutFlow_PowhegPy8_WmH125J_noDalitz_weighted"
    },
    "WpH": {
      "datafiles": {
        "mc16a": "mc16a.PowhegPy8_WpH125J.MxAODDetailedNoSkim.e5734_s3126_r9364_p4207_h027.root",
        "mc16d": "mc16d.PowhegPy8_WpH125J.MxAODDetailedNoSkim.e5734_s3126_r10201_p4207_h027.root",
        "mc16e": "mc16e.PowhegPy8_WpH125J.MxAODDetailedNoSkim.e5734_s3126_r10724_p4207_h027.root"
      },
      "histoName": "CutFlow_PowhegPy8_WpH125J_noDalitz_weighted"
    },

    "bbH": {
      "datafiles": {
        "mc16a": "mc16a.PowhegPy8_bbH125.MxAODDetailedNoSkim.e6050_s3126_r9364_p4180_h027.root",
        "mc16d": "mc16d.PowhegPy8_bbH125.MxAODDetailedNoSkim.e6050_s3126_r10201_p4180_h027.root",
        "mc16e": "mc16e.PowhegPy8_bbH125.MxAODDetailedNoSkim.e6050_s3126_r10724_p4180_h027.root"
      },
	"histoName": "CutFlow_PowhegPy8_bbH125_noDalitz_weighted"
    },

      "tHjb": {
          "datafiles": {
              "mc16a": "mc16a.aMCnloPy8_tHjb125_4fl_shw_fix.MxAODDetailedNoSkim.e7305_s3126_r9364_p4180_h027.root",
              "mc16d": "mc16d.aMCnloPy8_tHjb125_4fl_shw_fix.MxAODDetailedNoSkim.e7305_s3126_r10201_p4180_h027.root",
              "mc16e": "mc16e.aMCnloPy8_tHjb125_4fl_shw_fix.MxAODDetailedNoSkim.e7305_s3126_r10724_p4180_h027.root"
          },
          "histoName": "CutFlow_aMCnloPy8_tHjb125_4fl_noDalitz_weighted"
      },
      "tWH": {
	  "datafiles": {
              "mc16a": "mc16a.aMCnloPy8_tWH125.MxAODDetailedNoSkim.e7425_s3126_r9364_p4180_h027.root",
              "mc16d": "mc16d.aMCnloPy8_tWH125.MxAODDetailedNoSkim.e7425_s3126_r10201_p4180_h027.root",
              "mc16e": "mc16e.aMCnloPy8_tWH125.MxAODDetailedNoSkim.e7425_s3126_r10724_p4180_h027.root"
	  },
	  "histoName": "CutFlow_aMCnloPy8_tWH125_noDalitz_weighted"
      }
    }   
}
