{
    "sequencer":["YieldCalculator","VariablePlotter"],

    "directories":{
    			"mc16a" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h024/mc16a/Nominal/",
    			"mc16d" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h024/mc16d/Nominal/",
    			"mc16e" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h024/mc16e/Nominal/"
    },

	"variables":{
		"m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 55,"lbins" : 105,"ubins" : 160}},
		"m_jj" :{"var":"HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_jj","bins":{"nbins" : 24,"lbins" : 60,"ubins" : 180}},
		"m_yyjj_tilde" :{"var": "HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_yyjj_tilde","bins":{"nbins" : 30,"lbins" : 250,"ubins" : 1000}},
		"m_yyjj_tilde_HM" :{"var": "HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_yyjj_tilde","bins":{"nbins" : 26,"lbins" : 350,"ubins" : 1000}},
		"deltaR_yy" :{"var": "HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_deltaR_yy","bins":{"nbins" : 25,"lbins" : 0,"ubins" : 5}},
		"deltaR_jj" :{"var": "HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_deltaR_jj","bins":{"nbins" : 25,"lbins" : 0,"ubins" : 5}},
		"deltaR_yyjj" :{"var": "HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_deltaR_yyjj","bins":{"nbins" : 30,"lbins" : 0,"ubins" : 6}},
		"MET" :{"var": "HGamEventInfoAuxDyn.met_TST*0.001","bins":{"nbins" : 15,"lbins" : 0,"ubins" : 150}},
		"N_j" :{"var": "HGamEventInfoAuxDyn.N_j","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
		"N_j_central" :{"var": "HGamEventInfoAuxDyn.N_j_central","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}},
		"btag_score" :{"var": "yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[0].MV2c10bin+yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[1].MV2c10bin","bins":{"nbins" : 8,"lbins" : 0,"ubins" : 8}}
	},

    
    "selections": {
    
    	"Selection" : "(HGamEventInfoAuxDyn.isPassed && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[0].MV2c10bin >= 1 && yybbAntiKt4EMTopoJets_discreteMV2c10pTAuxDyn[1].MV2c10bin >= 1 && HGamEventInfoAuxDyn.N_lep == 0 && HGamEventInfoAuxDyn.N_j_central < 6 && HGamEventInfoAuxDyn.N_j_btag < 3 && HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_jj >= 70.0 && HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_m_jj <= 180.0  )*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_discreteMV2c10pT_weight"

    }, 

    "lumi" : {
  
    	"mc16a" : 36100,
    	"mc16d" : 43700,
     	"mc16e" : 59900
    },

    "samples" : {
			
		"tty_nohad": 	{
			"datafiles" : { 
			"mc16a" : "mc16a.MGPy8_ttgamma_nonallhadronic_AF2.MxAODDetailed.e6155_a875_r9364_p3703.h024.root",
			"mc16d" : "mc16d.MGPy8_ttgamma_nonallhadronic_AF2.MxAODDetailed.e6155_a875_r10201_p3703.h024.root",
			"mc16e" : "mc16d.MGPy8_ttgamma_nonallhadronic_AF2.MxAODDetailed.e6155_a875_r10201_p3703.h024.root"
			},
			"histoName" : "CutFlow_MGPy8_ttgamma_nonallhadronic_noDalitz_weighted"
			},
		
		"ttyy_nohad":	{
			"datafiles" : { 	
			"mc16a" : "mc16a.MGPy8_ttgammagamma_noallhad_AF2.MxAODDetailed.e6542_a875_r9364_p3703.h024.root",
			"mc16d" : "mc16d.MGPy8_ttgammagamma_noallhad_AF2.MxAODDetailed.e6542_a875_r10201_p3703.h024.root",
			"mc16e" : "mc16e.MGPy8_ttgammagamma_noallhad_AF2.MxAODDetailed.e6542_a875_r10724_p3703.h024.root"
			},
			"histoName" : "CutFlow_MGPy8_ttgammagamma_noallhad_AF2_noDalitz_weighted"
			}, 
			
		"ttyy_had":	{
			"datafiles" : { 
			"mc16a" : "mc16a.MGPy8_ttgammagamma_allhad_AF2.MxAODDetailed.e6542_a875_r9364_p3703.h024.root",
			"mc16d" : "mc16d.MGPy8_ttgammagamma_allhad_AF2.MxAODDetailed.e6542_a875_r10201_p3703.h024.root",
			"mc16e" : "mc16e.MGPy8_ttgammagamma_allhad_AF2.MxAODDetailed.e6542_a875_r10724_p3703.h024.root"
			},
			"histoName" : "CutFlow_MGPy8_ttgammagamma_allhad_AF2_noDalitz_weighted"
			},

		"yy":	{
			"datafiles" : { 
			"mc16a" : "yy_mc16a.root",
			"mc16d" : "yy_mc16d.root",
			"mc16e" : "yy_mc16e.root"
			},
			"histoName" : "CutFlow_Sherpa2_myy_90_175_noDalitz_weighted"
			}

    }


}
