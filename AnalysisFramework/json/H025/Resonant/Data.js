{
  "sequencer":["DataAnalysis"],
    
    "directories":{
        "data1" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/",
        "data2" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/",
        "data3" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonselection/"

    },

    "variables":{
	"m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 55,"lbins" : 105,"ubins" : 160}},
        "N_j" :{"var": "HGamEventInfoAuxDyn.N_j","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "N_j_central" :{"var": "HGamEventInfoAuxDyn.N_j_central","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "m_jj" :{"var":"HGamEventInfoAuxDyn.yybb_m_jj*0.001","bins":{"nbins" : 30,"lbins" : 0,"ubins" : 300}},
        "m_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj*0.001","bins":{"nbins" : 160,"lbins" : 0,"ubins" : 1600}},
        "m_yyjj_cnstrnd" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_cnstrnd*0.001","bins":{"nbins" : 160,"lbins" : 0,"ubins" : 1600}},
        "m_yyjj_tilde" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_tilde*0.001","bins":{"nbins" : 160,"lbins" : 0,"ubins" : 1600}},
	"deltaR_yy" :{"var": "HGamEventInfoAuxDyn.yybb_deltaR_yy","bins":{"nbins" : 25,"lbins" : 0,"ubins" : 5}},
        "deltaR_jj" :{"var": "HGamEventInfoAuxDyn.yybb_deltaR_jj","bins":{"nbins" : 25,"lbins" : 0,"ubins" : 5}},
        "deltaR_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_deltaR_yyjj","bins":{"nbins" : 30,"lbins" : 0,"ubins" : 6}},
        "MET" :{"var": "HGamEventInfoAuxDyn.met_TST*0.001","bins":{"nbins" : 15,"lbins" : 0,"ubins" : 150}},        
        "pT_jj" :{"var":"HGamEventInfoAuxDyn.pT_jj","bins":{"nbins" : 100,"lbins" : 500,"ubins" : 500500}},
        "pT_yy" :{"var":"HGamEventInfoAuxDyn.pT_yy","bins":{"nbins" : 100,"lbins" : 500,"ubins" : 500500}}

   },

    "selections": {
   
        "Resonant_BDT_260" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.75 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((259.899-2*3.45878)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((259.899+2*3.45878)*1000))",

        "Resonant_BDT_280" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((278.598-2*5.93442)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((278.598+2*5.93442)*1000))",

        "Resonant_BDT_300" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((298.248-2*6.80417)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((298.248+2*6.80417)*1000))",

        "Resonant_BDT_325" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((322.359-2*8.32443)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((322.359+2*8.32443)*1000))",

	
        "Resonant_BDT_350" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((346.891-2*9.42102)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((346.891+2*9.42102)*1000))",

        "Resonant_BDT_400" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((395.797-2*11.7374)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((395.797+2*11.7374)*1000))",
	
        "Resonant_BDT_450" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((445.429-2*13.3727)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((445.429+2*13.3727)*1000))",


        "Resonant_BDT_500" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.80 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((494.862-2*15.0873)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((494.862+2*15.0873)*1000))",

        "Resonant_BDT_550" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.65 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((544.569-2*16.507)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((544.569+2*16.507)*1000))",


        "Resonant_BDT_600" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.50 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((594.803-2*17.6)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((594.803+2*17.6)*1000))",

        "Resonant_BDT_700" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.30 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((694.781-2*19.9737)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((694.781+2*19.9737)*1000))",

	"Resonant_BDT_800" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.25 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((794.196-2*22.3182)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((794.196+2*22.3182)*1000))",

	"Resonant_BDT_900" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.07 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((894.305-2*24.2746)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((894.305+2*24.2746)*1000))",

	"Resonant_BDT_1000" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.10 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((998.186-4*24.2607)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((998.186+4*24.2607)*1000))"

    
 
    },

    "samples" : {

        "data":    {
            "datafiles" : {
                "data1" : "data1516.root",
                "data2" : "data17.root",
                "data3" : "data18.root"
            },
            "histoName" : "15_to_18_data"

	}


	
    }
    
}
