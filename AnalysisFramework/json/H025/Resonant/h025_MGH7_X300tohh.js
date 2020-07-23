{
  "sequencer":["VariablePlotter"],

    "directories":{
      "mc16d" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h025/mc16d/Nominal/"
    },

    "dumper":{
       "mc16d" : false
    
    },

    "variables":{
	"m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 55,"lbins" : 105,"ubins" : 160}},
        "N_j" :{"var": "HGamEventInfoAuxDyn.N_j","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "N_j_central" :{"var": "HGamEventInfoAuxDyn.N_j_central","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
        "m_jj" :{"var":"HGamEventInfoAuxDyn.yybb_m_jj*0.001","bins":{"nbins" : 30,"lbins" : 0,"ubins" : 300}},
        "m_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj*0.001","bins":{"nbins" : 160,"lbins" : 0,"ubins" : 1600}},
        "m_yyjj_cnstrnd" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_cnstrnd*0.001","bins":{"nbins" : 160,"lbins" : 0,"ubins" : 1600}},
        "m_yyjj_tilde" :{"var": "HGamEventInfoAuxDyn.yybb_m_yyjj_tilde*0.001","bins":{"nbins" : 160,"lbins" : 0,"ubins" : 1600}},
        "weight" : {"var": "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight", "bins":{"nbins" : 200,"lbins" : -10,"ubins" : 10} }

   },

    "selections": {
  
      "weight" : "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight",

      "Pass_yy" : "HGamEventInfoAuxDyn.isPassed",

      "TEST" : "HGamEventInfoAuxDyn.isPassedPreselection&&HGamEventInfoAuxDyn.isPassedTriggerMatch&&HGamEventInfoAuxDyn.isPassedPID&&HGamEventInfoAuxDyn.isPassedIsolation&&HGamEventInfoAuxDyn.isPassedRelPtCuts&&HGamEventInfoAuxDyn.isPassedMassCut&&EventInfoAuxDyn.passTrig_HLT_g35_medium_g25_medium_L12EM20VH",

      "Validation" : "HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_btag77_85_cutFlow == 6",
 
      "CutBased_Selection" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central >= 2 && HGamAntiKt4EMPFlowJets_BTagging201903AuxDyn.DL1r_bin[0]>=1 && HGamAntiKt4EMPFlowJets_BTagging201903AuxDyn.DL1r_bin[1]>=1 && HGamEventInfoAuxDyn.N_j_btag < 3 && HGamEventInfoAuxDyn.N_lep == 0 && HGamEventInfoAuxDyn.N_j < 6 && HGamEventInfoAuxDyn.yybb_m_jj > 80000 && HGamEventInfoAuxDyn.yybb_m_jj < 140000 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > 289030 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < 312060)",
 
      "BDT_Selection_h025" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(55,2)+pow(45,2) ) * sqrt( pow(55,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score +1)/2,2) + pow(45,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((298.248-2*6.80417)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((298.248+2*6.80417)*1000))",

      "BDT_Selection_h025_h024_optimized" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.N_j_central>=2 && HGamEventInfoAuxDyn.yybb_btag77_cutFlow==6 && 1/sqrt( pow(50,2)+pow(50,2) ) * sqrt( pow(50,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_yy_Score+1)/2,2) + pow(50,2)*pow((HGamEventInfoAuxDyn.yybb_Res_BDT_BCal_ttH_Score+1)/2,2) ) > 0.85 && HGamEventInfoAuxDyn.yybb_m_yyjj_tilde > ((298.248-2*6.80417)*1000) &&  HGamEventInfoAuxDyn.yybb_m_yyjj_tilde < ((298.248+2*6.80417)*1000))"
    
 
    },

  

    "lumi" : {
      "mc16d" : 44385.7
    },

    "samples" : {

      "X300toHH":	{
        "datafiles" : { 
          "mc16d" : "mc16d.MGH7_X300tohh_bbyy_AF2.MxAODDetailedNoSkim.e7251_a875_r10201_p4097_h025.root"
        },
        "histoName" : "CutFlow_MGH7_X300tohh_bbyy_AF2_noDalitz_weighted"
      }
     }

}
