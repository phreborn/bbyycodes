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
        "m_jj" :{"var":"HGamEventInfoAuxDyn.yybb_m_jj*0.001","bins":{"nbins" : 25,"lbins" : 0,"ubins" : 500}},
        "m_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj*0.001","bins":{"nbins" : 25,"lbins" : 400,"ubins" : 1600}},
        "m_yyjj_cnstrnd" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_cnstrnd*0.001","bins":{"nbins" : 25,"lbins" : 400,"ubins" : 1600}},
        "m_yyjj_tilde" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_tilde*0.001","bins":{"nbins" : 25,"lbins" : 400,"ubins" : 1600}},
        "deltaR_yy" :{"var": "HGamEventInfoAuxDyn.yybb_deltaR_yy","bins":{"nbins" : 20,"lbins" : 0,"ubins" : 6}},
        "deltaR_jj" :{"var": "HGamEventInfoAuxDyn.yybb_deltaR_jj","bins":{"nbins" : 20,"lbins" : 0,"ubins" : 5}},
        "deltaR_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_deltaR_yyjj","bins":{"nbins" : 25,"lbins" : 1,"ubins" : 7}},
        "MET" :{"var": "HGamEventInfoAuxDyn.met_TST*0.001","bins":{"nbins" : 15,"lbins" : 0,"ubins" : 150}},
        "pT_jj" :{"var":"HGamEventInfoAuxDyn.pT_jj","bins":{"nbins" : 20,"lbins" : 0,"ubins" : 600000}},
        "pT_yy" :{"var":"HGamEventInfoAuxDyn.pT_yy","bins":{"nbins" : 20,"lbins" : 0,"ubins" : 600000}}


   },

    "selections": {
  
	"weight" : "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

        "Resonant_BDT_700" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_btag77_85_BCal_resonant_score_yy +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_btag77_85_BCal_resonant_score_ttH+1)/2,2) ) > 0.30 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((694.781-2*19.9737)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((694.781+2*19.9737)*1000))",

	"Resonant_BDT_800" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_btag77_85_BCal_resonant_score_yy +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_btag77_85_BCal_resonant_score_ttH+1)/2,2) ) > 0.25 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((794.196-2*22.3182)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((794.196+2*22.3182)*1000))",

	"Resonant_BDT_900" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_btag77_85_BCal_resonant_score_yy +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_btag77_85_BCal_resonant_score_ttH+1)/2,2) ) > 0.07 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((894.305-2*24.2746)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((894.305+2*24.2746)*1000))",

	"Resonant_BDT_1000" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_btag77_85_BCal_resonant_score_yy +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_btag77_85_BCal_resonant_score_ttH+1)/2,2) ) > 0.10 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((998.186-4*24.2607)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((998.186+4*24.2607)*1000))"

    
 
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
