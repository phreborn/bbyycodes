{
  "sequencer":["VariablePlotter"],

    "directories":{
      "mc16a" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h026/mc16a/Nominal/",
      "mc16d" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h026/mc16d/Nominal/",
      "mc16e" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h026/mc16e/Nominal/"
 },

   "dumper":{

       "mc16a" : true,
       "mc16d" : false,
       "mc16e" : false

    },

    "variables":{
        "m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 55,"lbins" : 105,"ubins" : 160}},
        "weight" : {"var": "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10} }
    
    },

    "selections": { 

      "weight" : "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",      
      "Validation" : "HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6",
      "XGBoost_btag77_withTop_BCal_tightScore_HMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 1)   && HGamEventInfoAuxDyn.m_yy*0.001 > 120 && HGamEventInfoAuxDyn.m_yy*0.001 < 130 )",
      "XGBoost_btag77_withTop_BCal_looseScore_HMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 2)   && HGamEventInfoAuxDyn.m_yy*0.001 > 120 && HGamEventInfoAuxDyn.m_yy*0.001 < 130 )",
      "XGBoost_btag77_withTop_BCal_tightScore_LMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 3)   && HGamEventInfoAuxDyn.m_yy*0.001 > 120 && HGamEventInfoAuxDyn.m_yy*0.001 < 130 )",
      "XGBoost_btag77_withTop_BCal_looseScore_LMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat/1000) % 10) == 4)   && HGamEventInfoAuxDyn.m_yy*0.001 > 120 && HGamEventInfoAuxDyn.m_yy*0.001 < 130 )"

   },

    "lumi" : {
      "mc16a" : 36209.04,
      "mc16d" : 44385.7,
      "mc16e" : 58450.1
    },

    "samples" : {

      "X500tohh_bbyy":    {
        "datafiles" : {
          "mc16a" : "mc16a.MGH7_X500tohh_bbyy_AF2.MxAODDetailedNoSkim.e7251_a875_r9364_p4207_h026.root"
        },
        "histoName": "CutFlow_MGH7_X500tohh_bbyy_AF2_noDalitz_weighted"
      },

      "X500tohh_bbtautau_lephad":    {
        "datafiles" : {
          "mc16a" : "mc16a.MGH7_X500tohh_bbtautau_lephad_AF2.MxAODDetailedNoSkim.e7319_a875_r9364_p4207_h026.root"
        },
        "histoName": "CutFlow_MGH7_X500tohh_bbtautau_lephad_AF2_noDalitz_weighted"
      },
      
      "X500tohh_bbtautau_hadhad":    {
        "datafiles" : {
          "mc16a" : "mc16a.MGH7_X500tohh_bbtautau_hadhad_AF2.MxAODDetailedNoSkim.e7319_a875_r9364_p4207_h026.root"
        },
        "histoName" : "CutFlow_MGH7_X500tohh_bbtautau_hadhad_AF2_noDalitz_weighted"
      },

      "X500tohh_WWbb_2lep":    {
        "datafiles" : {
          "mc16a" : "mc16a.MGH7_X500tohh_WWbb_2lep_AF2.MxAODDetailedNoSkim.e7453_a875_r9364_p4207_h026.root"
        },
        "histoName" : "CutFlow_MGH7_X500tohh_WWbb_2lep_AF2_noDalitz_weighted"
      },

      "X500tohh_ttbb_2lep":    {
        "datafiles" : {
          "mc16a" : "mc16a.MGH7_X500tohh_ttbb_2lep_AF2.MxAODDetailedNoSkim.e8091_a875_r9364_p4207_h026.root"
        },
        "histoName" : "CutFlow_MGH7_X500tohh_ttbb_2lep_AF2_noDalitz_weighted"
      },


      "500tohh_bbZZllvv":    {
        "datafiles" : {
          "mc16a" : "mc16a.MGH7_X500tohh_bbZZllvv_AF2.MxAODDetailedNoSkim.e7452_a875_r9364_p4207_h026.root"
        },
        "histoName" : "CutFlow_MGH7_X500tohh_bbZZllvv_AF2_noDalitz_weighted"
      },


      "X1000tohh_bbyy":    {
        "datafiles" : {
          "mc16a" : "mc16a.MGH7_X1000tohh_bbyy_AF2.MxAODDetailedNoSkim.e7251_a875_r9364_p4207_h026.root"
        },
        "histoName" : "CutFlow_MGH7_X1000tohh_bbyy_AF2_noDalitz_weighted"
      },


      "X1000tohh_bbbb":    {
        "datafiles" : {
          "mc16a" : "mc16a.MGH7_X1000tohh_bbbb.MxAODDetailedNoSkim.e7352_s3126_r9364_p4207_h026.root"
        },
        "histoName" : "CutFlow_MGH7_X1000tohh_bbbb_noDalitz_weighted"
      },

      "HHbbtautauLepHad":    {
        "datafiles" : {
          "mc16a" : "mc16a.PhH7_HHbbtautauLepHad_cHHH01d0.MxAODDetailedNoSkim.e7954_s3126_r9364_p4207_h026.root"
        },
        "histoName" : "CutFlow_PhH7_HHbbtautauLepHad_cHHH01d0_noDalitz_weighted"
      },


      "HHbbtautauHadHad":    {
        "datafiles" : {
          "mc16a" : "mc16a.PhH7_HHbbtautauHadHad_cHHH01d0.MxAODDetailedNoSkim.e7954_s3126_r9364_p4207_h026.root"
        },
        "histoName" : "CutFlow_PhH7_HHbbtautauHadHad_cHHH01d0_noDalitz_weighted"
      },

      "HHbbtt2L":    {
        "datafiles" : {
          "mc16a" : "mc16a.PhH7_HHbbtt2L_cHHH01d0.MxAODDetailedNoSkim.e7954_s3126_r9364_p4207_h026.root"
        },
        "histoName" : "CutFlow_PhH7_HHbbtt2L_cHHH01d0_noDalitz_weighted"
      },

       "HHbbWW2L":    {
        "datafiles" : {
          "mc16a" : "mc16a.PhH7_HHbbWW2L_cHHH01d0.MxAODDetailedNoSkim.e7954_s3126_r9364_p4207_h026.root"
        },
        "histoName" : "CutFlow_PhH7_HHbbWW2L_cHHH01d0_noDalitz_weighted"
      },

       "HHbbZZ2L":    {
        "datafiles" : {
          "mc16a" : "mc16a.PhH7_HHbbZZ2L_cHHH01d0.MxAODDetailedNoSkim.e7954_s3126_r9364_p4207_h026.root"
        },
        "histoName" : "CutFlow_PhH7_HHbbZZ2L_cHHH01d0_noDalitz_weighted"
      },

      "hh_bbWW":    {
        "datafiles" : {
          "mc16a" : "mc16a.aMCnloH7_hh_bbWW_AF2.MxAODDetailedNoSkim.e7426_a875_r9364_p4207_h026.root"
        },
        "histoName" : "CutFlow_aMCnloH7_hh_bbWW_AF2_noDalitz_weighted"
      }

     
     }

}
