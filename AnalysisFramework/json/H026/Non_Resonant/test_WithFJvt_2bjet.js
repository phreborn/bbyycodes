{
  "sequencer": [
    "VariablePlotter"
  ],
  "directories": {
    "mc16a": "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h026_diphotonselection/mc16a/"
  },
  "dumper": {
    "mc16a": true
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
    "weight": {
      "var": "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*HGamEventInfoAuxDyn.weightFJvt",
      "bins": {
        "nbins": 200,
        "lbins": -10,
        "ubins": 10
      }
    }
  },
  "selections": {
    "weight": "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*HGamEventInfoAuxDyn.weightFJvt",
    "btag77_withTop_BCal_tightScore_HMass": "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.passCrackVetoCleaning  == 1 &&  HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 1))   "
},
  "lumi": {
    "mc16a": 36209.04
  },
  "samples": {
    "HH": {
      "datafiles": {
        "mc16a": "mc16a.PowhegH7_HHbbyy_cHHH01d0.root"
      },
      "histoName": "CutFlow_PowhegH7_HHbbyy_cHHH01d0_noDalitz_weighted"
    }
  }
}