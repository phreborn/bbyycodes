#explanations for systematics :
#http://archiv.ub.uni-heidelberg.de/volltextserver/28782/1/PrintedThesis_Fabrizio_Napolitano.pdf
#------------------------------------------------
#######################################################
# Theoretical Systematics
#
muR=0.5_muF=0.5
muR=0.5_muF=1.0
muR=1.0_muF=0.5
muR=1.0_muF=2.0
muR=2.0_muF=1.0
muR=2.0_muF=2.0
##careful : for 904xx : eigenvector : not to divide by N
##while for NNPDF : 260000, to compute rms : to divide by N
pdf_set_90401
pdf_set_90402
pdf_set_90403
pdf_set_90404
pdf_set_90405
pdf_set_90406
pdf_set_90407
pdf_set_90408
pdf_set_90409
pdf_set_90410
pdf_set_90411
pdf_set_90412
pdf_set_90413
pdf_set_90414
pdf_set_90415
pdf_set_90416
pdf_set_90417
pdf_set_90418
pdf_set_90419
pdf_set_90420
pdf_set_90421
pdf_set_90422
pdf_set_90423
pdf_set_90424
pdf_set_90425
pdf_set_90426
pdf_set_90427
pdf_set_90428
pdf_set_90429
pdf_set_90430
pdf_set_90431
pdf_set_90432
#------------------------------------------------
#######################################################
# Experimental Systematics
#
#PH_EFF_TRIGGER_Uncertainty
#PRW_DATASF
# #------------------------------------------------
# #either in PhotonSys or PhotonAllSys
# #put above, PH_EFF_TRIGGER_Uncertainty
# PH_EFF_ID_Uncertainty
# PH_EFF_ISO_Uncertainty
# #------------------------------------------------
# # #PhotonSys: 1-NP
#EG_SCALE_ALL
# # #this is for AF2 samples only, to be added to ALL, either PhotonSys or PhotonAllSys
#EG_SCALE_AF2
#EG_RESOLUTION_ALL
# # do not take EG_RESOLUTION_AF2 since already include in EG_RESOLUTION_ALL (while EG_SCALE_ALL does not contain EG_SCALE_AF2)
# #------------------------------------------------
# ########################################################
# # #PhotonAllSys: All-NPs
# # EG_SCALE_PEDESTAL
# # EG_SCALE_PS_BARREL_B12
# # EG_SCALE_PS__ETABIN0
# # EG_SCALE_PS__ETABIN1
# # EG_SCALE_PS__ETABIN2
# # EG_SCALE_PS__ETABIN3
# # EG_SCALE_PS__ETABIN4
# # EG_SCALE_PS__ETABIN5
# # EG_SCALE_PS__ETABIN6
# # EG_SCALE_PS__ETABIN7
# # EG_SCALE_PS__ETABIN8
# # EG_SCALE_E4SCINTILLATOR__ETABIN0
# # EG_SCALE_E4SCINTILLATOR__ETABIN1
# # EG_SCALE_E4SCINTILLATOR__ETABIN2
# # EG_SCALE_G4
# # EG_SCALE_L1GAIN
# # EG_SCALE_L2GAIN
# # EG_SCALE_LARCALIB__ETABIN0
# # EG_SCALE_LARCALIB__ETABIN1
# # EG_SCALE_LARELECCALIB
# # EG_SCALE_LARELECUNCONV__ETABIN0
# # EG_SCALE_LARELECUNCONV__ETABIN1
# # EG_SCALE_LARUNCONVCALIB__ETABIN0
# # EG_SCALE_LARUNCONVCALIB__ETABIN1
# # EG_SCALE_S12__ETABIN0
# # EG_SCALE_S12__ETABIN1
# # EG_SCALE_S12__ETABIN2
# # EG_SCALE_S12__ETABIN3
# # EG_SCALE_S12__ETABIN4
# # EG_SCALE_TOPOCLUSTER_THRES
# # EG_SCALE_WTOTS1
# # EG_SCALE_MATCALO__ETABIN0
# # EG_SCALE_MATCALO__ETABIN1
# # EG_SCALE_MATCALO__ETABIN2
# # EG_SCALE_MATCALO__ETABIN3
# # EG_SCALE_MATCALO__ETABIN4
# # EG_SCALE_MATCALO__ETABIN5
# # EG_SCALE_MATCALO__ETABIN6
# # EG_SCALE_MATCALO__ETABIN7
# # EG_SCALE_MATCALO__ETABIN8
# # EG_SCALE_MATCALO__ETABIN9
# # EG_SCALE_MATCALO__ETABIN10
# # EG_SCALE_MATCALO__ETABIN11
# # EG_SCALE_MATID__ETABIN0
# # EG_SCALE_MATID__ETABIN1
# # EG_SCALE_MATID__ETABIN2
# # EG_SCALE_MATID__ETABIN3
# # EG_SCALE_MATPP0__ETABIN0
# # EG_SCALE_MATPP0__ETABIN1
# # EG_SCALE_MATCRYO__ETABIN0
# # EG_SCALE_MATCRYO__ETABIN1
# # EG_SCALE_MATCRYO__ETABIN2
# # EG_SCALE_MATCRYO__ETABIN3
# # EG_SCALE_MATCRYO__ETABIN4
# # EG_SCALE_MATCRYO__ETABIN5
# # EG_SCALE_MATCRYO__ETABIN6
# # EG_SCALE_MATCRYO__ETABIN7
# # EG_SCALE_MATCRYO__ETABIN8
# # EG_SCALE_MATCRYO__ETABIN9
# # EG_SCALE_MATCRYO__ETABIN10
# # EG_SCALE_MATCRYO__ETABIN11
# # EG_SCALE_ZEESTAT
# # EG_SCALE_ZEESYST
# # PH_SCALE_CONVEFFICIENCY
# # PH_SCALE_CONVFAKERATE
# # PH_SCALE_CONVRADIUS
# # PH_SCALE_LEAKAGECONV
# # PH_SCALE_LEAKAGEUNCONV
# # #----------
# # EG_RESOLUTION_AF2
# # EG_RESOLUTION_MATERIALCALO
# # EG_RESOLUTION_MATERIALCRYO
# # EG_RESOLUTION_MATERIALGAP
# # EG_RESOLUTION_MATERIALIBL
# # EG_RESOLUTION_MATERIALID
# # EG_RESOLUTION_MATERIALPP0
# # EG_RESOLUTION_PILEUP
# # EG_RESOLUTION_SAMPLINGTERM
# # EG_RESOLUTION_ZSMEARING
# # #######################################################
#JetSys
#JetSys2
# JET_BJES_Response
# JET_EtaIntercalibration_Modelling
# JET_EtaIntercalibration_NonClosure_2018data
# JET_EtaIntercalibration_NonClosure_highE
# JET_EtaIntercalibration_NonClosure_negEta
# JET_EtaIntercalibration_NonClosure_posEta
# JET_EtaIntercalibration_TotalStat
# JET_Flavor_Composition
# JET_Flavor_Response
# JET_Pileup_OffsetMu
# JET_Pileup_OffsetNPV
# JET_Pileup_PtTerm
# JET_Pileup_RhoTopology
# JET_PunchThrough_MC16
# JET_PunchThrough_AFII
# JET_RelativeNonClosure_AFII
# JET_SingleParticle_HighPt
# JET_JvtEfficiency
# JET_fJvtEfficiency
#-----
#JetSys1
# JET_EffectiveNP_Detector1
# JET_EffectiveNP_Detector2
# JET_EffectiveNP_Mixed1
# JET_EffectiveNP_Mixed2
# JET_EffectiveNP_Mixed3
# JET_EffectiveNP_Modelling1
# JET_EffectiveNP_Modelling2
# JET_EffectiveNP_Modelling3
# JET_EffectiveNP_Modelling4
# JET_EffectiveNP_Statistical1
# JET_EffectiveNP_Statistical2
# JET_EffectiveNP_Statistical3
# JET_EffectiveNP_Statistical4
# JET_EffectiveNP_Statistical5
# JET_EffectiveNP_Statistical6
#-----
#cases splited in MCsmear and PDsmear
# JET_JER_DataVsMC_MC16_MCsmear
# JET_JER_DataVsMC_MC16_PDsmear
# JET_JER_DataVsMC_AFII_MCsmear
# JET_JER_DataVsMC_AFII_PDsmear
# JET_JER_EffectiveNP_1_MCsmear
# JET_JER_EffectiveNP_1_PDsmear
# JET_JER_EffectiveNP_2_MCsmear
# JET_JER_EffectiveNP_2_PDsmear
# JET_JER_EffectiveNP_3_MCsmear
# JET_JER_EffectiveNP_3_PDsmear
# JET_JER_EffectiveNP_4_MCsmear
# JET_JER_EffectiveNP_4_PDsmear
# JET_JER_EffectiveNP_5_MCsmear
# JET_JER_EffectiveNP_5_PDsmear
# JET_JER_EffectiveNP_6_MCsmear
# JET_JER_EffectiveNP_6_PDsmear
# JET_JER_EffectiveNP_7_MCsmear
# JET_JER_EffectiveNP_7_PDsmear
# JET_JER_EffectiveNP_8_MCsmear
# JET_JER_EffectiveNP_8_PDsmear
# JET_JER_EffectiveNP_9_MCsmear
# JET_JER_EffectiveNP_9_PDsmear
# JET_JER_EffectiveNP_10_MCsmear
# JET_JER_EffectiveNP_10_PDsmear
# JET_JER_EffectiveNP_11_MCsmear
# JET_JER_EffectiveNP_11_PDsmear
# JET_JER_EffectiveNP_12restTerm_MCsmear
# JET_JER_EffectiveNP_12restTerm_PDsmear
#-----
#######################################################
#FlavorSys
# FT_EFF_Eigen_B_0
# FT_EFF_Eigen_B_1
# FT_EFF_Eigen_B_2
# FT_EFF_extrapolation
# FT_EFF_Eigen_C_0
# FT_EFF_Eigen_C_1
# FT_EFF_Eigen_C_2
# FT_EFF_Eigen_C_3
# FT_EFF_extrapolation_from_charm
# FT_EFF_Eigen_Light_0
# FT_EFF_Eigen_Light_1
# FT_EFF_Eigen_Light_2
# FT_EFF_Eigen_Light_3
# FT_EFF_Eigen_Light_4
#######################################################
#LeptonMETSys
#-----
# EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR
# EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR
# EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR
#-----
# MUON_EFF_RECO_STAT
# MUON_EFF_RECO_STAT_LOWPT
# MUON_EFF_RECO_SYS
# MUON_EFF_RECO_SYS_LOWPT
# MUON_EFF_TTVA_STAT
# MUON_EFF_TTVA_SYS
# MUON_EFF_ISO_STAT
# MUON_EFF_ISO_SYS
# MUON_ID
# MUON_MS
# MUON_SAGITTA_RESBIAS
# MUON_SAGITTA_RHO
# MUON_SCALE
#-----
# TAUS_TRUEHADTAU_SME_TES_INSITUEXP
# TAUS_TRUEHADTAU_SME_TES_INSITUFIT
# TAUS_TRUEHADTAU_SME_TES_MODEL_CLOSURE
# TAUS_TRUEHADTAU_SME_TES_PHYSICSLIST
#-----
#MET_SoftTrk_Scale
#symmetric only
#MET_SoftTrk_ResoPara
#MET_SoftTrk_ResoPerp
#
#######################################################
#no more
#special with Up and Down instead of __1up and __1down
