{
  "sequencer":["DataAnalysis"],

    "directories":{
      "data1" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/",
      "data2" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/",
      "data3" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/"
    },

    "variables":{
                "m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 500,"lbins" : 0,"ubins" : 500}}
    },

    "selections": {

        "yy_sel" : "(HGamEventInfoAuxDyn.isPassed)",

        "yy_btag_77_sel" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_btag77_cutFlow >=6)",

        "yy_btag_77_85_sel" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_btag77_85_cutFlow >=6)",

        "yy_btag_77_Zbb_window" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_btag77_cutFlow >=6 && HGamEventInfoAuxDyn.yybb_m_jj*0.001 > 60.0 && HGamEventInfoAuxDyn.yybb_m_jj*0.001 < 110.0)",

        "yy_btag_77_85_Zbb_window" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_btag77_85_cutFlow >=6 && HGamEventInfoAuxDyn.yybb_m_jj*0.001 > 60.0 && HGamEventInfoAuxDyn.yybb_m_jj*0.001 < 110.0)"

    }, 

    "samples" : {

      "data": 	{
        "datafiles" : {
          "data1" : "data1516.root",
          "data2" : "data17.root",
          "data3" : "data18.root"
        },
        "histoName" : "15_to_18_data"
      }

    }


}
