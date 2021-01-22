{
  "sequencer":["DataAnalysis"],

    "directories":{
      "data1" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/",
      "data2" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/",
      "data3" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/"
    },

    "variables":{
                "m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 500,"lbins" : 0,"ubins" : 500}},
                "m_jj" :{"var":"HGamEventInfoAuxDyn.yybb_m_jj*0.001","bins":{"nbins" :  500,"lbins" : 0,"ubins" : 500}},
                "pT_jj" :{"var":"HGamEventInfoAuxDyn.pT_jj*0.001","bins":{"nbins" : 500,"lbins" : 0,"ubins" : 500}},
                "pT_yy" :{"var":"HGamEventInfoAuxDyn.pT_yy*0.001","bins":{"nbins" : 500,"lbins" : 0,"ubins" : 500}},
                "m_yyjj_tilde" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_tilde*0.001","bins":{"nbins" : 1000,"lbins" : 0,"ubins" : 1000}},
                "pT_jj_div_m_yyjj_tilde" :{"var":"HGamEventInfoAuxDyn.pT_jj/(HGamEventInfoAuxDyn.yybb_m_yyjj_tilde*0.001)","bins":{"nbins" : 1000,"lbins" : 0,"ubins" : 1000}},
                "pT_yy_div_m_yyjj_tilde" :{"var":"HGamEventInfoAuxDyn.pT_yy/(HGamEventInfoAuxDyn.yybb_m_yyjj_tilde*0.001)","bins":{"nbins" : 1000,"lbins" : 0,"ubins" : 1000}},
                "pT_jj_div_m_jj" :{"var":"HGamEventInfoAuxDyn.pT_jj/(HGamEventInfoAuxDyn.yybb_m_jj*0.001)","bins":{"nbins" : 500,"lbins" : 0,"ubins" : 5000}},
                "pT_yy_div_m_yy" :{"var":"HGamEventInfoAuxDyn.pT_yy/(HGamEventInfoAuxDyn.m_yy*0.001)","bins":{"nbins" : 500,"lbins" : 0,"ubins" : 5000}},
		"MET" :{"var": "HGamEventInfoAuxDyn.met_TST*0.001","bins":{"nbins" : 500,"lbins" : 0,"ubins" : 500}},
		"MET_phi" :{"var": "HGamEventInfoAuxDyn.phi_TST","bins":{"nbins" : 400,"lbins" : -4,"ubins" : 4}},
		"N_j" :{"var": "HGamEventInfoAuxDyn.N_j","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
		"N_j_central" :{"var": "HGamEventInfoAuxDyn.N_j_central","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
		"N_j_btag" :{"var": "HGamEventInfoAuxDyn.N_j_btag","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}}

    },

    "selections": {

        "yy_sel" : "(HGamEventInfoAuxDyn.isPassed)",

        "yy_btag_77_sel" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_btag77_cutFlow >=6)",

        "yy_btag_77_85_sel" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_btag77_85_cutFlow >=6)",

        "yy_btag_77_85_Zbb_window" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_btag77_85_cutFlow >=6 && HGamEventInfoAuxDyn.yybb_m_jj*0.001 > 60.0 && HGamEventInfoAuxDyn.yybb_m_jj*0.001 < 110.0)",

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
