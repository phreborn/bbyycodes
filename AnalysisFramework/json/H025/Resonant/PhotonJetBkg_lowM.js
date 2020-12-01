{
  "sequencer":["VariablePlotter"],

    
    "directories":{
        "mc16a" : "/eos/user/l/lapereir/HH/Samples/",
        "mc16d" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/mc16d/",
        "mc16e" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/mc16e/"

    },

    "variables":{
        "m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 30,"lbins" : 102,"ubins" : 162}},
        "N_j" :{"var": "HGamEventInfoAuxDyn.N_j","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "N_j_central" :{"var": "HGamEventInfoAuxDyn.N_j_central","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "m_jj" :{"var":"HGamEventInfoAuxDyn.yybb_m_jj*0.001","bins":{"nbins" : 25,"lbins" : 25,"ubins" : 175}},
        "m_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj*0.001","bins":{"nbins" : 20,"lbins" : 100,"ubins" : 500}},
        "m_yyjj_cnstrnd" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_cnstrnd*0.001","bins":{"nbins" : 20,"lbins" : 100,"ubins" : 500}},
        "m_yyjj_tilde" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_tilde*0.001","bins":{"nbins" : 20,"lbins" : 100,"ubins" : 500}},
        "deltaR_yy" :{"var": "HGamEventInfoAuxDyn.yybb_deltaR_yy","bins":{"nbins" : 25,"lbins" : 0,"ubins" : 5}},
        "deltaR_jj" :{"var": "HGamEventInfoAuxDyn.yybb_deltaR_jj","bins":{"nbins" : 25,"lbins" : 0,"ubins" : 5}},
        "deltaR_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_deltaR_yyjj","bins":{"nbins" : 25,"lbins" : 0,"ubins" : 5}},
        "MET" :{"var": "HGamEventInfoAuxDyn.met_TST*0.001","bins":{"nbins" : 15,"lbins" : 0,"ubins" : 150}},
        "pT_jj" :{"var":"HGamEventInfoAuxDyn.pT_jj","bins":{"nbins" : 25,"lbins" : 0,"ubins" : 250000}},
        "pT_yy" :{"var":"HGamEventInfoAuxDyn.pT_yy","bins":{"nbins" : 25,"lbins" : 0,"ubins" : 250000}}


   },

    "selections": {
  
"weight" : "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",
 
        "Resonant_BDT_260" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_btag77_85_BCal_resonant_score_yy +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_btag77_85_BCal_resonant_score_ttH +1)/2,2) ) > 0.75 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((259.899-2*3.45878)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((259.899+2*3.45878)*1000))",

        "Resonant_BDT_280" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_btag77_85_BCal_resonant_score_yy +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_btag77_85_BCal_resonant_score_ttH +1)/2,2) ) > 0.85 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((278.598-2*5.93442)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((278.598+2*5.93442)*1000))",

        "Resonant_BDT_300" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_btag77_85_BCal_resonant_score_yy +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_btag77_85_BCal_resonant_score_ttH +1)/2,2) ) > 0.85 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((298.248-2*6.80417)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((298.248+2*6.80417)*1000))",

        "Resonant_BDT_325" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_btag77_85_BCal_resonant_score_yy  +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_btag77_85_BCal_resonant_score_ttH +1)/2,2) ) > 0.85 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((322.359-2*8.32443)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((322.359+2*8.32443)*1000))",

	
        "Resonant_BDT_350" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_btag77_85_BCal_resonant_score_yy  +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_btag77_85_BCal_resonant_score_ttH +1)/2,2) ) > 0.85 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((346.891-2*9.42102)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((346.891+2*9.42102)*1000))",

        "Resonant_BDT_400" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_btag77_85_BCal_resonant_score_yy  +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_btag77_85_BCal_resonant_score_ttH +1)/2,2) ) > 0.85 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((395.797-2*11.7374)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((395.797+2*11.7374)*1000))"
	
 
    },

  

    "lumi" : {
	
	"mc16a" : 36209.04,
	"mc16d" : 44385.7,
	"mc16e" : 58450.1
    },

    "samples" : {

        "yy":    {
            "datafiles" : {
                "mc16a" : "mc16a.Sherpa2_myy_90_175.root",
                "mc16d" : "mc16d.Sherpa2_myy_90_175.root",
                "mc16e" : "mc16e.Sherpa2_myy_90_175.root"
            },
            "histoName" : "CutFlow_Sherpa2_myy_90_175_noDalitz_weighted"
        }
	
    }
    
}
