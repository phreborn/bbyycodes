{
  "sequencer":["YieldCalculator"],

    "name":{
	"yields" : "HH_skimmed_yields"
    },
    
    "directories":{
        "mc16a" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h026_diphotonselection/mc16a/",
        "mc16d" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h026_diphotonselection/mc16d/",
        "mc16e" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h026_diphotonselection/mc16e/"

    },

    "variables":{
	"m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 55,"lbins" : 105,"ubins" : 160}}
   },

    "selections": {
  
	"weight" : "HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight*HGamEventInfoAuxDyn.weightFJvt",
 	
	"2btag_77" : "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow==6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] == 1 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] == 1)",

        "High_M" : "(HGamEventInfoAuxDyn.isPassed == 1 && HGamEventInfoAuxDyn.yybb_btag77_BCal_cutFlow==6 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet1_fix] == 1 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.DL1r_FixedCutBEff_77[HGamEventInfoAuxDyn.yybb_candidate_jet2_fix] == 1 && (HGamEventInfoAuxDyn.yybb_BCal_m_yyjj - HGamEventInfoAuxDyn.m_yy - HGamEventInfoAuxDyn.yybb_BCal_m_jj + 250e3) > 350e3)"
 
    },

  

    "lumi" : {
	
	"mc16a" : 36209.04,
	"mc16d" : 44385.7,
	"mc16e" : 58450.1
    },

    "samples" : {
	
	"HH":{
	    "datafiles":{
		"mc16a" : "mc16a.PowhegH7_HHbbyy_cHHH01d0.root",
		"mc16d" : "mc16d.PowhegH7_HHbbyy_cHHH01d0.root",
		"mc16e" : "mc16e.PowhegH7_HHbbyy_cHHH01d0.root"
	    },
	    
	 "histoName" : 	"CutFlow_PowhegH7_HHbbyy_cHHH01d0_noDalitz_weighted"
	}
	
    }
    
}
