{
  "sequencer":["DataAnalysis"],

    "directories":{
      "data1" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/",
      "data2" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/",
      "data3" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/",
      "data4" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/"
    },

   "dumper":{

       "data1" : false,
       "data2" : false,
       "data3" : false,
       "data4" : false

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
        "deltaR_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_deltaR_yyjj","bins":{"nbins" : 40,"lbins" : 0,"ubins" : 4}}
    
    },

    "selections": {

      "Validation" : "HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow == 6",
      "XGBoost_btag77_Nominal_BCal_tightScore_HMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat) % 10) == 1)   && HGamEventInfoAuxDyn.m_yy*0.001 > 120 && HGamEventInfoAuxDyn.m_yy*0.001 < 130 )",
      "XGBoost_btag77_Nominal_BCal_looseScore_HMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat) % 10) == 2)   && HGamEventInfoAuxDyn.m_yy*0.001 > 120 && HGamEventInfoAuxDyn.m_yy*0.001 < 130 )",
      "XGBoost_btag77_Nominal_BCal_tightScore_LMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat) % 10) == 3)   && HGamEventInfoAuxDyn.m_yy*0.001 > 120 && HGamEventInfoAuxDyn.m_yy*0.001 < 130 )",
      "XGBoost_btag77_Nominal_BCal_looseScore_LMass"    : "(HGamEventInfoAuxDyn.isPassed == 1 && (((HGamEventInfoAuxDyn.yybb_nonRes_XGBoost_btag77_BCal_Cat) % 10) == 4)   && HGamEventInfoAuxDyn.m_yy*0.001 > 120 && HGamEventInfoAuxDyn.m_yy*0.001 < 130 )"




   },

    "lumi" : {
      "data1" : 1,
      "data2" : 1,
      "data3" : 1,
      "data4" : 1
    },

    "samples" : {

      "data":    {
        "datafiles" : {
          "data1" : "data15.root",
          "data2" : "data16.root",
          "data3" : "data17.root",
          "data4" : "data18.root"
        },
        "histoName" : "15_to_18_data"
      }

     
     }

}
