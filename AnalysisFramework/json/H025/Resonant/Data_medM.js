{
  "sequencer":["DataAnalysis"],
    
    "directories":{
        "data1" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/",
        "data2" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/",
        "data3" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/",
	"data4" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/"

    },

    "variables":{
        "m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 30,"lbins" : 102,"ubins" : 162}},
        "N_j" :{"var": "HGamEventInfoAuxDyn.N_j","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "N_j_central" :{"var": "HGamEventInfoAuxDyn.N_j_central","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "m_jj" :{"var":"HGamEventInfoAuxDyn.yybb_m_jj*0.001","bins":{"nbins" : 20,"lbins" : 25,"ubins" : 225}},
        "m_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj*0.001","bins":{"nbins" : 25,"lbins" : 300,"ubins" : 800}},
        "m_yyjj_cnstrnd" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_cnstrnd*0.001","bins":{"nbins" : 25,"lbins" : 300,"ubins" : 800}},
        "m_yyjj_tilde" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_tilde*0.001","bins":{"nbins" : 25,"lbins" : 300,"ubins" : 800}},
        "deltaR_yy" :{"var": "HGamEventInfoAuxDyn.yybb_deltaR_yy","bins":{"nbins" : 20,"lbins" : 1,"ubins" : 5}},
        "deltaR_jj" :{"var": "HGamEventInfoAuxDyn.yybb_deltaR_jj","bins":{"nbins" : 20,"lbins" : 1,"ubins" : 5}},
        "deltaR_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_deltaR_yyjj","bins":{"nbins" : 25,"lbins" : 0,"ubins" : 5}},
        "MET" :{"var": "HGamEventInfoAuxDyn.met_TST*0.001","bins":{"nbins" : 15,"lbins" : 0,"ubins" : 150}},
        "pT_jj" :{"var":"HGamEventInfoAuxDyn.pT_jj","bins":{"nbins" : 30,"lbins" : 50000,"ubins" : 350000}},
        "pT_yy" :{"var":"HGamEventInfoAuxDyn.pT_yy","bins":{"nbins" : 30,"lbins" : 50000,"ubins" : 350000}}

   },

    "selections": {
   
	
        "Resonant_BDT_450" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((445.429-2*13.3727)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((445.429+2*13.3727)*1000) && (HGamEventInfoAuxDyn.m_yy*0.001 < 120 || HGamEventInfoAuxDyn.m_yy*0.001 > 130) )",


        "Resonant_BDT_500" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.80 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((494.862-2*15.0873)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((494.862+2*15.0873)*1000) && (HGamEventInfoAuxDyn.m_yy*0.001 < 120 || HGamEventInfoAuxDyn.m_yy*0.001 > 130) )",

        "Resonant_BDT_550" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.65 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((544.569-2*16.507)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((544.569+2*16.507)*1000) && (HGamEventInfoAuxDyn.m_yy*0.001 < 120 || HGamEventInfoAuxDyn.m_yy*0.001 > 130) )",


        "Resonant_BDT_600" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.50 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((594.803-2*17.6)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((594.803+2*17.6)*1000) && (HGamEventInfoAuxDyn.m_yy*0.001 < 120 || HGamEventInfoAuxDyn.m_yy*0.001 > 130) )"

    
 
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
