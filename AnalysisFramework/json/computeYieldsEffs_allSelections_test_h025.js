{
  "sequencer":["YieldCalculator","VariablePlotter"],

    "directories":{
      "mc16a" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h025/mc16a/Nominal/",
      "mc16d" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h025/mc16d/Nominal/",
      "mc16e" : "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h025/mc16e/Nominal/"
    },

    "variables":{
	"m_yy": {"var":"HGamEventInfoAuxDyn.m_yy*0.001","bins":{"nbins" : 55,"lbins" : 105,"ubins" : 160}}
    },

    "selections": {
  
      "LM_A" : "(HGamEventInfoAuxDyn.isPassed && HGamEventInfoAuxDyn.yybb_nonRes_cutBased_btag77_KF_Cat == 1)*HGamEventInfoAuxDyn.crossSectionBRfilterEff*HGamEventInfoAuxDyn.weight*HGamEventInfoAuxDyn.yybb_weight"

    },

    "lumi" : {

      "mc16a" : 36209,
      "mc16d" : 44386,
      "mc16e" : 58450
    },

    "samples" : {

      "ttH":	{
        "datafiles" : { 
          "mc16a" : "mc16a.PowhegPy8_ttH125_fixweight.MxAODDetailed.e7488_s3126_r9364_p4097_h025.root",
          "mc16d" : "mc16d.PowhegPy8_ttH125_fixweight.MxAODDetailed.e7488_s3126_r10201_p4097_h025.root",
          "mc16e" : "mc16e.PowhegPy8_ttH125_fixweight.MxAODDetailed.e7488_s3126_r10724_p4097_h025.root"
        },
        "histoName" : "CutFlow_PowhegPy8_ttH125_fixweight_noDalitz_weighted"
      }
     }

}
