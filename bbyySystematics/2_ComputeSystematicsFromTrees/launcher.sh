#=========================================
#Yields (don't foret to put analytic)

#remark : for theory : don't forget to put envelop and pdf prescription

#next line : test
#root -b -q "Systematics_Yield_Shape.C+(\"PowhegPy8_HHbbyy_reweight_mHH_1p0_to_1p2\",\"yield\",\"do_not_care\",\"do_not_care\",\"XGBoost_btag77_withTop_BCal_looseScore_HMass\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" | tee log_1p2

#gg HH kappa lambda=1
root -b -q "Systematics_Yield_Shape.C+(\"gg_HH_non_resonant_kappa_lambda_01\",\"yield\",\"do_not_care\",\"do_not_care\",\"XGBoost_btag77_withTop_BCal_tightScore_HMass\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_yield_cat_XGBoost_btag77_withTop_BCal_tightScore_HMass
root -b -q "Systematics_Yield_Shape.C+(\"gg_HH_non_resonant_kappa_lambda_01\",\"yield\",\"do_not_care\",\"do_not_care\",\"XGBoost_btag77_withTop_BCal_looseScore_HMass\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_yield_cat_XGBoost_btag77_withTop_BCal_looseScore_HMass
root -b -q "Systematics_Yield_Shape.C+(\"gg_HH_non_resonant_kappa_lambda_01\",\"yield\",\"do_not_care\",\"do_not_care\",\"XGBoost_btag77_withTop_BCal_tightScore_LMass\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_yield_cat_XGBoost_btag77_withTop_BCal_tightScore_LMass
root -b -q "Systematics_Yield_Shape.C+(\"gg_HH_non_resonant_kappa_lambda_01\",\"yield\",\"do_not_care\",\"do_not_care\",\"XGBoost_btag77_withTop_BCal_looseScore_LMass\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_yield_cat_XGBoost_btag77_withTop_BCal_looseScore_LMass
exit(1)

#gg HH kappa lambda=10
#root -b -q "Systematics_Yield_Shape.C+(\"gg_HH_non_resonant_kappa_lambda_10\",\"yield\",\"do_not_care\",\"do_not_care\",\"XGBoost_btag77_withTop_BCal_tightScore_HMass\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_10_yield_cat_XGBoost_btag77_withTop_BCal_tightScore_HMass 
#root -b -q "Systematics_Yield_Shape.C+(\"gg_HH_non_resonant_kappa_lambda_10\",\"yield\",\"do_not_care\",\"do_not_care\",\"XGBoost_btag77_withTop_BCal_looseScore_HMass\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_10_yield_cat_XGBoost_btag77_withTop_BCal_looseScore_HMass 
#root -b -q "Systematics_Yield_Shape.C+(\"gg_HH_non_resonant_kappa_lambda_10\",\"yield\",\"do_not_care\",\"do_not_care\",\"XGBoost_btag77_withTop_BCal_tightScore_LMass\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_yield_cat_XGBoost_btag77_withTop_BCal_tightScore_LMass 
#root -b -q "Systematics_Yield_Shape.C+(\"gg_HH_non_resonant_kappa_lambda_10\",\"yield\",\"do_not_care\",\"do_not_care\",\"XGBoost_btag77_withTop_BCal_looseScore_LMass\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_yield_cat_XGBoost_btag77_withTop_BCal_looseScore_LMass
#exit(1)
# #vbf HH kappa lambda=1
#root -b -q "Systematics_Yield_Shape.C+(\"vbf_HH_non_resonant_kappa_lambda_01\",\"yield\",\"do_not_care\",\"do_not_care\",\"XGBoost_btag77_withTop_BCal_tightScore_HMass\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_yield_cat_XGBoost_btag77_withTop_BCal_tightScore_HMass
#root -b -q "Systematics_Yield_Shape.C+(\"vbf_HH_non_resonant_kappa_lambda_01\",\"yield\",\"do_not_care\",\"do_not_care\",\"XGBoost_btag77_withTop_BCal_looseScore_HMass\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_yield_cat_XGBoost_btag77_withTop_BCal_looseScore_HMass
#root -b -q "Systematics_Yield_Shape.C+(\"vbf_HH_non_resonant_kappa_lambda_01\",\"yield\",\"do_not_care\",\"do_not_care\",\"XGBoost_btag77_withTop_BCal_tightScore_LMass\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_yield_cat_XGBoost_btag77_withTop_BCal_tightScore_LMass
#root -b -q "Systematics_Yield_Shape.C+(\"vbf_HH_non_resonant_kappa_lambda_01\",\"yield\",\"do_not_care\",\"do_not_care\",\"XGBoost_btag77_withTop_BCal_looseScore_LMass\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_yield_cat_XGBoost_btag77_withTop_BCal_looseScore_LMass
#exit(1)
#----------------
#ggH
#root -b -q "Systematics_Yield_Shape.C+(\"PowhegPy8_NNLOPS_ggH125\",\"yield\",\"do_not_care\",\"do_not_care\",\"XGBoost_btag77_withTop_BCal_tightScore_HMass\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_yield_cat_tightScore_HMass
#root -b -q "Systematics_Yield_Shape.C+(\"PowhegPy8_NNLOPS_ggH125\",\"yield\",\"do_not_care\",\"do_not_care\",\"XGBoost_btag77_withTop_BCal_looseScore_HMass\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_yield_cat_tightScore_LMass
#root -b -q "Systematics_Yield_Shape.C+(\"PowhegPy8_NNLOPS_ggH125\",\"yield\",\"do_not_care\",\"do_not_care\",\"XGBoost_btag77_withTop_BCal_tightScore_LMass\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_yield_cat_looseScore_HMass
#root -b -q "Systematics_Yield_Shape.C+(\"PowhegPy8_NNLOPS_ggH125\",\"yield\",\"do_not_care\",\"do_not_care\",\"XGBoost_btag77_withTop_BCal_looseScore_LMass\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_yield_cat_looseScore_LMass

#ZH
#root -b -q "Systematics_Yield_Shape.C+(\"ZH125\",\"yield\",\"do_not_care\",\"do_not_care\",\"XGBoost_btag77_withTop_BCal_tightScore_HMass\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_ZH125_yield_cat_tightScore_HMass
#root -b -q "Systematics_Yield_Shape.C+(\"ZH125\",\"yield\",\"do_not_care\",\"do_not_care\",\"XGBoost_btag77_withTop_BCal_looseScore_HMass\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_ZH125_yield_cat_looseScore_HMass
#root -b -q "Systematics_Yield_Shape.C+(\"ZH125\",\"yield\",\"do_not_care\",\"do_not_care\",\"XGBoost_btag77_withTop_BCal_tightScore_LMass\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_ZH125_yield_cat_tightScore_LMass
#root -b -q "Systematics_Yield_Shape.C+(\"ZH125\",\"yield\",\"do_not_care\",\"do_not_care\",\"XGBoost_btag77_withTop_BCal_looseScore_LMass\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_ZH125_yield_cat_looseScore_LMass
#exit(1)
#ttH
#root -b -q "Systematics_Yield_Shape.C+(\"ttH125\",\"yield\",\"do_not_care\",\"do_not_care\",\"XGBoost_btag77_withTop_BCal_tightScore_HMass\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_ttH125_yield_cat_tightScore_HMass
#root -b -q "Systematics_Yield_Shape.C+(\"ttH125\",\"yield\",\"do_not_care\",\"do_not_care\",\"XGBoost_btag77_withTop_BCal_looseScore_HMass\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_ttH125_yield_cat_looseScore_HMass
#root -b -q "Systematics_Yield_Shape.C+(\"ttH125\",\"yield\",\"do_not_care\",\"do_not_care\",\"XGBoost_btag77_withTop_BCal_tightScore_LMass\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_ttH125_yield_cat_tightScore_LMass
#root -b -q "Systematics_Yield_Shape.C+(\"ttH125\",\"yield\",\"do_not_care\",\"do_not_care\",\"XGBoost_btag77_withTop_BCal_looseScore_LMass\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_ttH125_yield_cat_looseScore_LMass

#HH resonant, mX=260

for index_mX in X251 X260 X280 X300 X325 X350 X400 X450 X500 X550 X600 X700 X800 X900 X1000
do
root -b -q "Systematics_Yield_Shape.C+(\"MGH7_${index_mX}tohh_bbyy_AF2\",\"yield\",\"do_not_care\",\"do_not_care\",\"Resonant_m${index_mX}\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_proc_h026_mc16a_h026_mc16d_h026_mc16e_${index_mX}_yield_cat_Resonant${index_mX}
done

#example
#root -b -q "Systematics_Yield_Shape.C+(\"MGH7_X260tohh_bbyy_AF2\",\"yield\",\"do_not_care\",\"do_not_care\",\"Resonant_mX260\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee log_proc_h026_mc16a_h026_mc16d_h026_mc16e_X260_yield_cat_ResonantX260

#version bootstrap


#-------------------
#gg HH in HH resonant
#for index_mX in X251 X260 X280 X300 X325 X350 X400 X450 X500 X550 X600 X700 X800 X900 X1000
#do
#root -b -q "Systematics_Yield_Shape.C+(\"gg_HH_non_resonant_kappa_lambda_01\",\"yield\",\"do_not_care\",\"do_not_care\",\"Resonant_m${index_mX}\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_proc_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_yield_cat_Resonant${index_mX}
#done
#-------------------
#vbf HH in HH resonant
#for index_mX in X251 X260 X280 X300 X325 X350 X400 X450 X500 X550 X600 X700 X800 X900 X1000
#do
#root -b -q "Systematics_Yield_Shape.C+(\"vbf_HH_non_resonant_kappa_lambda_01\",\"yield\",\"do_not_care\",\"do_not_care\",\"Resonant_m${index_mX}\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_proc_h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_yield_cat_Resonant${index_mX}
#done

#-------------------
#ggH in HH resonant
#for index_mX in X251 X260 X280 X300 X325 X350 X400 X450 X500 X550 X600 X700 X800 X900 X1000
#do
#root -b -q "Systematics_Yield_Shape.C+(\"PowhegPy8_NNLOPS_ggH125\",\"yield\",\"do_not_care\",\"do_not_care\",\"Resonant_m${index_mX}\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_proc_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_yield_cat_Resonant${index_mX}
#done
#-------------------
#ZH in HH resonant
#for index_mX in X251 X260 X280 X300 X325 X350 X400 X450 X500 X550 X600 X700 X800 X900 X1000
#do
#root -b -q "Systematics_Yield_Shape.C+(\"ZH125\",\"yield\",\"do_not_care\",\"do_not_care\",\"Resonant_m${index_mX}\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_proc_h026_mc16a_h026_mc16d_h026_mc16e_ZH125_yield_cat_Resonant${index_mX}
#done
#-------------------
#ttH in HH resonant
#for index_mX in X251 X260 X280 X300 X325 X350 X400 X450 X500 X550 X600 X700 X800 X900 X1000
#do
#root -b -q "Systematics_Yield_Shape.C+(\"ttH125\",\"yield\",\"do_not_care\",\"do_not_care\",\"Resonant_m${index_mX}\",\"do_not_care\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee /sps/atlas/e/escalier/log_proc_h026_mc16a_h026_mc16d_h026_mc16e_ttH125_yield_cat_Resonant${index_mX}
#done

#exit(1)

#==========================================================================================================
#==========================================================================================================
#==========================================================================================================
#==========================================================================================================
#==========================================================================================================
#Shape

#Part theory: no toys : mean_IQR, individual: events are fully correlated, thus we could deduce the error wo/ toys
#DO NOT DO THIS BECAUSE CORRELATION FOR THEORY SO DO NOT DI INDIVIDUAL#No toys
#case mc16a, mc16d, mc16e
#root -b -q "Systematics_Yield_Shape.C+(\"shape\",\"mean_IQR\",\"individual\",\"XGBoost_btag77_withTop_BCal_tightScore_HMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee mylog_cat1;
#root -b -q "Systematics_Yield_Shape.C+(\"shape\",\"mean_IQR\",\"individual\",\"XGBoost_btag77_withTop_BCal_looseScore_HMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee mylog_cat2;
#root -b -q "Systematics_Yield_Shape.C+(\"shape\",\"mean_IQR\",\"individual\",\"XGBoost_btag77_withTop_BCal_tightScore_LMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee mylog_cat3;
#root -b -q "Systematics_Yield_Shape.C+(\"shape\",\"mean_IQR\",\"individual\",\"XGBoost_btag77_withTop_BCal_looseScore_LMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee mylog_cat4;
#exit(1)
#root -b -q "Systematics_Yield_Shape.C+(\"shape\",\"mean_IQR\",\"individual\",\"XGBoost_btag77_withTop_BCal_looseScore_LMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee mylog_cat4;
#exit(1)

#INDIVIDUAL=shit  : theory needs correlation !!!
#root -b -q "Systematics_Yield_Shape.C+(\"shape\",\"mean_IQR\",\"individual\",\"XGBoost_btag77_withTop_BCal_tightScore_HMass\",\"m_yy\",\"h025_mc16a_h025_mc16d_h025_mc16e\",0,1)" |tee mylog_cat1;
#root -b -q "Systematics_Yield_Shape.C+(\"shape\",\"mean_IQR\",\"individual\",\"XGBoost_btag77_withTop_BCal_looseScore_HMass\",\"m_yy\",\"h025_mc16a_h025_mc16d_h025_mc16e\",0,1)" |tee mylog_cat2;
#root -b -q "Systematics_Yield_Shape.C+(\"shape\",\"mean_IQR\",\"individual\",\"XGBoost_btag77_withTop_BCal_tightScore_LMass\",\"m_yy\",\"h025_mc16a_h025_mc16d_h025_mc16e\",0,1)" |tee mylog_cat3;
#root -b -q "Systematics_Yield_Shape.C+(\"shape\",\"mean_IQR\",\"individual\",\"XGBoost_btag77_withTop_BCal_looseScore_LMass\",\"m_yy\",\"h025_mc16a_h025_mc16d_h025_mc16e\",0,1)" |tee mylog_cat4;
#NO MORE#root -b -q "Systematics_Yield_Shape.C+(\"shape\",\"mean_IQR\",\"individual\",\"VBF_btag77_withTop_BCal\",\"m_yy\",\"h025_mc16a_h025_mc16d_h025_mc16e\",0,1)" |tee mylog_cat5;
#exit(1)
#Shape, case no bootstrap
#put mode_shape_MakeAndStoreFits=1
#if no batch : mode_shape_ReadFits_previously_made=1;
#root -b -q "Systematics_Yield_Shape.C+(0,\"m_yy\",\"h025_mc16d\",0,10)" |tee log_h025_mc16d_inclusive;
#root -b -q "Systematics_Yield_Shape.C+(0,\"m_yy\",\"h025_mc16d\",0,100)" |tee log_h025_mc16d_inclusive;

#Shape, bootstrap : store & fit
#time HHH01 : 1 : 3h30 ; 2 : 1h30 ; 3 : 20' ; 4 : 25'

#gg HH kappa lambda=1
#root -b -q "Systematics_Yield_Shape.C+(\"gg_HH_non_resonant_kappa_lambda_01\",\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_tightScore_HMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_shape_cat_tightScore_HMass
#root -b -q "Systematics_Yield_Shape.C+(\"gg_HH_non_resonant_kappa_lambda_01\",\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_looseScore_HMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_shape_cat_looseScore_HMass
#root -b -q "Systematics_Yield_Shape.C+(\"gg_HH_non_resonant_kappa_lambda_01\",\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_tightScore_LMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_shape_cat_tightScore_LMass
#root -b -q "Systematics_Yield_Shape.C+(\"gg_HH_non_resonant_kappa_lambda_01\",\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_looseScore_LMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_shape_cat_looseScore_LMass

#gg HH kappa lambda=10
#root -b -q "Systematics_Yield_Shape.C+(\"gg_HH_non_resonant_kappa_lambda_10\",\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_tightScore_HMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee log_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_10_shape_cat_tightScore_HMass
#root -b -q "Systematics_Yield_Shape.C+(\"gg_HH_non_resonant_kappa_lambda_10\",\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_looseScore_HMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee log_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_10_shape_cat_looseScore_HMass
#root -b -q "Systematics_Yield_Shape.C+(\"gg_HH_non_resonant_kappa_lambda_10\",\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_tightScore_LMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee log_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_10_shape_cat_tightScore_LMass
#root -b -q "Systematics_Yield_Shape.C+(\"gg_HH_non_resonant_kappa_lambda_10\",\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_looseScore_LMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee log_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_10_shape_cat_looseScore_LMass

#vbf HH kappa lambda=1
#root -b -q "Systematics_Yield_Shape.C+(\"vbf_HH_non_resonant_kappa_lambda_01\",\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_tightScore_HMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_shape_cat_tightScore_HMass
#root -b -q "Systematics_Yield_Shape.C+(\"vbf_HH_non_resonant_kappa_lambda_01\",\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_looseScore_HMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_shape_cat_looseScore_HMass
#root -b -q "Systematics_Yield_Shape.C+(\"vbf_HH_non_resonant_kappa_lambda_01\",\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_tightScore_LMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_shape_cat_tightScore_LMass
#root -b -q "Systematics_Yield_Shape.C+(\"vbf_HH_non_resonant_kappa_lambda_01\",\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_looseScore_LMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_shape_cat_looseScore_LMass

#----------------
#ggH

#root -b -q "Systematics_Yield_Shape.C+(\"PowhegPy8_NNLOPS_ggH125\",\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_tightScore_HMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_shape_cat_tightScore_HMass
#root -b -q "Systematics_Yield_Shape.C+(\"PowhegPy8_NNLOPS_ggH125\",\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_looseScore_HMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_shape_cat_looseScore_HMass
#root -b -q "Systematics_Yield_Shape.C+(\"PowhegPy8_NNLOPS_ggH125\",\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_tightScore_LMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_shape_cat_tightScore_LMass
#root -b -q "Systematics_Yield_Shape.C+(\"PowhegPy8_NNLOPS_ggH125\",\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_looseScore_LMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_shape_cat_looseScore_LMass
#----------------
#ZH
#root -b -q "Systematics_Yield_Shape.C+(\"ZH125\",\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_tightScore_HMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_ZH125_shape_cat_tightScore_HMass
#root -b -q "Systematics_Yield_Shape.C+(\"ZH125\",\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_looseScore_HMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_ZH125_shape_cat_looseScore_HMass
#root -b -q "Systematics_Yield_Shape.C+(\"ZH125\",\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_tightScore_LMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_ZH125_shape_cat_tightScore_LMass
#root -b -q "Systematics_Yield_Shape.C+(\"ZH125\",\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_looseScore_LMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_ZH125_shape_cat_looseScore_LMass

#ttH
#root -b -q "Systematics_Yield_Shape.C+(\"ttH125\",\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_tightScore_HMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_ttH125_shape_cat_tightScore_HMass
#root -b -q "Systematics_Yield_Shape.C+(\"ttH125\",\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_looseScore_HMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_ttH125_shape_cat_looseScore_HMass
#root -b -q "Systematics_Yield_Shape.C+(\"ttH125\",\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_tightScore_LMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_ttH125_shape_cat_tightScore_LMass
#root -b -q "Systematics_Yield_Shape.C+(\"ttH125\",\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_looseScore_LMass\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_ttH125_shape_cat_looseScore_LMass

#exit(1)

#HH Resonant

for index_mX in X251 X260 X280 X300 X325 X350 X400 X450 X500 X550 X600 X700 X800 X900 X1000
  do
root -b -q "Systematics_Yield_Shape.C+(\"MGH7_${index_mX}tohh_bbyy_AF2\",\"shape\",\"mean_IQR\",\"bootstrap\",\"Resonant_m${index_mX}\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee /sps/atlas/e/escalier/log_proc_h026_mc16a_h026_mc16d_h026_mc16e_${index_mX}_shape_cat_Resonant${index_mX}
done
exit(1)
#time root -b -q "Systematics_Yield_Shape.C+(\"MGH7_X260tohh_bbyy_AF2\",\"shape\",\"mean_IQR\",\"bootstrap\",\"Resonant_mX260\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,1)" |tee log_shape_MGH7_X260_cat_X260;
#example containing error message, with 2 toys { time root -b -q "Systematics_Yield_Shape.C+(\"MGH7_X260tohh_bbyy_AF2\",\"shape\",\"mean_IQR\",\"bootstrap\",\"Resonant_mX260\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,2)" } 2>&1 |tee -a log_shape_MGH7_X260_cat_X260;
#time root -b -q "Systematics_Yield_Shape.C+(\"MGH7_X260tohh_bbyy_AF2\",\"shape\",\"mean_IQR\",\"bootstrap\",\"Resonant_mX260\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee log_shape_MGH7_X260_cat_X260;
#-----------------------------------------------------------------------
#gg HH bkg in Resonant analysis

#for mX in 251 260 280 300 325 350 400 450 500 550 600 700 800 900 1000
#do 
#root -b -q "Systematics_Yield_Shape.C+(\"gg_HH_non_resonant_kappa_lambda_01\",\"shape\",\"mean_IQR\",\"bootstrap\",\"Resonant_mX${mX}\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_shape_cat_X${mX}
#done
#-----------------------------------------------------------------------
#vbf HH bkg in Resonant analysis

#for mX in 251 260 280 300 325 350 400 450 500 550 600 700 800 900 1000
#do 
#root -b -q "Systematics_Yield_Shape.C+(\"vbf_HH_non_resonant_kappa_lambda_01\",\"shape\",\"mean_IQR\",\"bootstrap\",\"Resonant_mX${mX}\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_shape_cat_X${mX}
#done


#-----------------------------------------------------------------------
#ggH in Resonant analysis

#for mX in 251 260 280 300 325 350 400 450 500 550 600 700 800 900 1000
#do 
#root -b -q "Systematics_Yield_Shape.C+(\"PowhegPy8_NNLOPS_ggH125\",\"shape\",\"mean_IQR\",\"bootstrap\",\"Resonant_mX${mX}\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_shape_cat_X${mX}
#done
#-----------------------------------------------------------------------
#ZH in Resonant analysis

#for mX in 251 260 280 300 325 350 400 450 500 550 600 700 800 900 1000
#do 
#root -b -q "Systematics_Yield_Shape.C+(\"ZH125\",\"shape\",\"mean_IQR\",\"bootstrap\",\"Resonant_mX${mX}\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_ZH125_shape_cat_X${mX}
#done
#-----------------------------------------------------------------------
#ttH in Resonant analysis
#for mX in 251 260 280 300 325 350 400 450 500 550 600 700 800 900 1000
#do 
#root -b -q "Systematics_Yield_Shape.C+(\"ttH125\",\"shape\",\"mean_IQR\",\"bootstrap\",\"Resonant_mX${mX}\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee /sps/atlas/e/escalier/log_h026_mc16a_h026_mc16d_h026_mc16e_ttH125_shape_cat_X${mX}
#done

exit(1)
#-----------------------------------------------------------------------

#example time root -b -q "Systematics_Yield_Shape.C+(\"MGH7_X280tohh_bbyy_AF2\",\"shape\",\"mean_IQR\",\"bootstrap\",\"Resonant_mX280\",\"m_yy\",\"h026_mc16a_h026_mc16d_h026_mc16e\",0,100)" |tee log_shape_MGH7_X280_cat_X280;

#case mc16d
#root -b -q "Systematics_Yield_Shape.C+(\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_tightScore_HMass\",\"m_yy\",\"h025_mc16d\",0,100)" |tee log_h025_mc16d_cat1
#root -b -q "Systematics_Yield_Shape.C+(\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_looseScore_HMass\",\"m_yy\",\"h025_mc16d\",0,100)" |tee log_h025_mc16d_cat2
#root -b -q "Systematics_Yield_Shape.C+(\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_tightScore_LMass\",\"m_yy\",\"h025_mc16d\",0,100)" |tee log_h025_mc16d_cat3
#root -b -q "Systematics_Yield_Shape.C+(\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_looseScore_LMass\",\"m_yy\",\"h025_mc16d\",0,100)" |tee log_h025_mc16d_cat4
#root -b -q "Systematics_Yield_Shape.C+(\"shape\",\"mean_IQR\",\"bootstrap\",\"VBF_btag77_withTop_BCal\",\"m_yy\",\"h025_mc16d\",0,100)" |tee log_h025_mc16d_cat5

#root -b -q "Systematics_Yield_Shape.C+(\"shape\",\"mean_IQR\",\"bootstrap\",\"Resonant_mX300\",\"m_yy\",\"h025_mc16d\",0,100)" |tee log_h025_mc16d_cat1

exit(1)

#case mc16a, mc16d, mc16e
#root -b -q "Systematics_Yield_Shape.C+(\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_tightScore_HMass\",\"m_yy\",\"h025_mc16a_h025_mc16d_h025_mc16e\",0,100)" |tee log_h025_mc16a_h025_mc16d_h025_mc16e_cat1
#root -b -q "Systematics_Yield_Shape.C+(\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_looseScore_HMass\",\"m_yy\",\"h025_mc16a_h025_mc16d_h025_mc16e\",0,100)" |tee log_h025_mc16a_h025_mc16d_h025_mc16e_cat2
#root -b -q "Systematics_Yield_Shape.C+(\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_tightScore_LMass\",\"m_yy\",\"h025_mc16a_h025_mc16d_h025_mc16e\",0,100)" |tee log_h025_mc16a_h025_mc16d_h025_mc16e_cat3
#root -b -q "Systematics_Yield_Shape.C+(\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_looseScore_LMass\",\"m_yy\",\"h025_mc16a_h025_mc16d_h025_mc16e\",0,100)" |tee log_h025_mc16a_h025_mc16d_h025_mc16e_cat4
#root -b -q "Systematics_Yield_Shape.C+(\"shape\",\"mean_IQR\",\"bootstrap\",\"VBF_btag77_withTop_BCal\",\"m_yy\",\"h025_mc16a_h025_mc16d_h025_mc16e\",0,100)" |tee log_h025_mc16a_h025_mc16d_h025_mc16e_cat5

exit(1)
#root -b -q "Systematics_Yield_Shape.C+(\"XGBoost_btag77_withTop_BCal_tightScore_HMass\",\"m_yy\",\"h025_mc16d\",0,200)" |tee log_h025_mc16d_cat1;

#root -b -q "Systematics_Yield_Shape.C+(\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_tightScore_HMass\",\"m_yy\",\"h025_mc16a\",0,100)" |tee log_h025_mc16d_cat1
#case mc16a, d, e
#root -b -q "Systematics_Yield_Shape.C+(\"shape\",\"mean_IQR\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_tightScore_HMass\",\"m_yy\",\"h025_mc16a_h025_mc16d_h025_mc16e\",0,100)" |tee log_h025_mc16d_cat1
#root -b -q "Systematics_Yield_Shape.C+(\"shape\",\"fit\",\"bootstrap\",\"XGBoost_btag77_withTop_BCal_tightScore_HMass\",\"m_yy\",\"h025_mc16a_h025_mc16d_h025_mc16e\",0,100)" |tee log_h025_mc16d_cat1
#root -b -q "Systematics_Yield_Shape.C+(\"XGBoost_btag77_withTop_BCal_looseScore_HMass\",\"m_yy\",\"h025_mc16a_h025_mc16d_h025_mc16e\",0,100)" |tee log_h025_mc16d_cat2
#root -b -q "Systematics_Yield_Shape.C+(\"XGBoost_btag77_withTop_BCal_tightScore_LMass\",\"m_yy\",\"h025_mc16a_h025_mc16d_h025_mc16e\",0,100)" |tee log_h025_mc16d_cat3
#root -b -q "Systematics_Yield_Shape.C+(\"XGBoost_btag77_withTop_BCal_looseScore_LMass\",\"m_yy\",\"h025_mc16a_h025_mc16d_h025_mc16e\",0,100)" |tee log_h025_mc16d_cat4
#root -b -q "Systematics_Yield_Shape.C+(\"VBF_btag77_withTop_BCal\",\"m_yy\",\"h025_mc16a_h025_mc16d_h025_mc16e\",0,100)" |tee log_h025_mc16d_cat5

exit(1)
#or fit

exit(1)

#Shape, bootstrap : read
#root -b -q "Systematics_Yield_Shape.C+(\"XGBoost_btag77_withTop_BCal_tightScore_HMass\",\"m_yy\",\"h025_mc16d\",0,1)" |tee log_h025_mc16d_cat1;

#root -b -q "Systematics_Yield_Shape.C+(0,\"m_yy\",\"h025_mc16d\",0,200)" |tee log_h025_mc16d_inclusive;
#root -b -q "Systematics_Yield_Shape.C+(0,\"m_yy\",\"h025_mc16d\",0,1)" |tee log_h025_mc16d_inclusive;
#root -b -q "Systematics_Yield_Shape.C+(0,\"m_yy\",\"h025_mc16d\",100,200)" |tee log_h025_mc16d_inclusive;
#root -b -q "Systematics_Yield_Shape.C+(0,\"m_yy\",\"h025_mc16d\",0,1000)" |tee log_h025_mc16d_inclusive;
#root -b -q "Systematics_Yield_Shape.C+(0,\"m_yy\",\"h025_mc16d\",0,100)" |tee log_h025_mc16d_inclusive;
#root -b -q "Systematics_Yield_Shape.C+(0,\"m_bb\",\"h025_mc16d\",0,100)" |tee log_h025_mc16d_inclusive;
#root -b -q "Systematics_Yield_Shape.C+(0,\"m_yybb_tilde\",\"h025_mc16d\",0,100)" |tee log_h025_mc16d_inclusive;

#root -b -q "Systematics_Yield_Shape.C+(0,\"m_yy\",\"h025_mc16d\",1001,1002)" |tee log_h025_mc16d_inclusive;
#root -b -q "Systematics_Yield_Shape.C+(0,\"m_yy\",\"h025_mc16d\",0,2000)" |tee log_h025_mc16d_inclusive;

#Shape, bootstrap read
#root -b -q "Systematics_Yield_Shape.C+(0,\"m_yy\",\"h025_mc16d\",0,1)" |tee log_h025_mc16d_inclusive;

#=========================================
exit(1)

#choice of sample : in global.h
#---------------------------------------------
#for nominal only, use flag : do_fit_only_nominal=1, and DO_bootstrap=0; and put Nominal only in Inputs/list_syst_all
#---------------------------------------------
#ALL SYS is considered in Systematics_Yield_Shape_Run2

#int mode_shape_MakeAndStoreFits=1;
#int mode_shape_ReadFits_previously_made=0;
#------------------------------------------
#nominal
#necessary to put 0, 1 in order to rescale to relevant statistics

#root -b -q "Systematics_Yield_Shape.C+(0,\"m_bb\",\"h024_mc16a_h024_mc16d_h024_mc16e\",0,1)" |tee myloga_0;
#root -b -q "Systematics_Yield_Shape.C+(1,\"m_bb\",\"h024_mc16a_h024_mc16d_h024_mc16e\",0,1)" |tee myloga_1;
#root -b -q "Systematics_Yield_Shape.C+(2,\"m_bb\",\"h024_mc16a_h024_mc16d_h024_mc16e\",0,1)" |tee myloga_2;
#root -b -q "Systematics_Yield_Shape.C+(3,\"m_bb\",\"h024_mc16a_h024_mc16d_h024_mc16e\",0,1)" |tee myloga_3;
#root -b -q "Systematics_Yield_Shape.C+(4,\"m_bb\",\"h024_mc16a_h024_mc16d_h024_mc16e\",0,1)" |tee myloga_m_gamgam_inclusive;

#echo call
#root -b -q "Systematics_Yield_Shape.C+(0,\"m_yy\",\"h024_mc16a_h024_mc16d_h024_mc16e\",0,1)" |tee myloga_0;
#root -b -q "Systematics_Yield_Shape.C+(1,\"m_yy\",\"h024_mc16a_h024_mc16d_h024_mc16e\",0,1)" |tee myloga_0;
#root -b -q "Systematics_Yield_Shape.C+(2,\"m_yy\",\"h024_mc16a_h024_mc16d_h024_mc16e\",0,1)" |tee myloga_0;
#root -b -q "Systematics_Yield_Shape.C+(3,\"m_yy\",\"h024_mc16a_h024_mc16d_h024_mc16e\",0,1)" |tee myloga_0;
#root -b -q "Systematics_Yield_Shape.C+(4,\"m_yy\",\"h024_mc16a_h024_mc16d_h024_mc16e\",0,1)" |tee myloga_0;

#root -b -q "Systematics_Yield_Shape.C+(4,\"m_yybb_tilde\",\"h024_mc16a_h024_mc16d_h024_mc16e\",0,1)" |tee myloga_4;

#exit(1)
#------------------------------------------
#for yield, don't forget first to merge the yields

#mode systematics yields : switch on the appropriate flags
#mode merging

#root -b -q "Systematics_Yield_Shape.C+(0,\"do_not_care\",\"h024_mc16a_h024_mc16d_h024_mc16e\",-1,1)" |tee mylogade_0;
#exit(1)
#miss variable ?
#root -b -q "Systematics_Yield_Shape.C+(0,\"m_yy\",\"h024_mc16a_h024_mc16d_h024_mc16e\",-1,-1)" |tee mylog0;
#root -b -q "Systematics_Yield_Shape.C+(1,\"m_yy\",\"h024_mc16a_h024_mc16d_h024_mc16e\",-1,-1)" |tee mylog0;
#root -b -q "Systematics_Yield_Shape.C+(2,\"m_yy\",\"h024_mc16a_h024_mc16d_h024_mc16e\",-1,-1)" |tee mylog0;
#root -b -q "Systematics_Yield_Shape.C+(3,\"m_yy\",\"h024_mc16a_h024_mc16d_h024_mc16e\",-1,-1)" |tee mylog0;
#root -b -q "Systematics_Yield_Shape.C+(4,\"m_yy\",\"h024_mc16a_h024_mc16d_h024_mc16e\",-1,-1)" |tee mylog0;
#exit(1)

#for reading 1-H
#root -b -q "Systematics_Yield_Shape.C+(0,\"m_yy\",\"h024_mc16a_h024_mc16d_h024_mc16e\",-1,-1)" |tee mylog0;
#root -b -q "Systematics_Yield_Shape.C+(1,\"m_yy\",\"h024_mc16a_h024_mc16d_h024_mc16e\",-1,-1)" |tee mylog0;
#root -b -q "Systematics_Yield_Shape.C+(2,\"m_yy\",\"h024_mc16a_h024_mc16d_h024_mc16e\",-1,-1)" |tee mylog0;
#root -b -q "Systematics_Yield_Shape.C+(3,\"m_yy\",\"h024_mc16a_h024_mc16d_h024_mc16e\",-1,-1)" |tee mylog0;
#root -b -q "Systematics_Yield_Shape.C+(4,\"m_yy\",\"h024_mc16a_h024_mc16d_h024_mc16e\",-1,-1)" |tee mylog0;

#for reading HH
#root -b -q "Systematics_Yield_Shape.C+(0,\"m_yy\",\"h024_mc16d\",-1,-1)" |tee mylog0;
#root -b -q "Systematics_Yield_Shape.C+(1,\"m_yy\",\"h024_mc16d\",-1,-1)" |tee mylog0;
#root -b -q "Systematics_Yield_Shape.C+(2,\"m_yy\",\"h024_mc16d\",-1,-1)" |tee mylog0;
#root -b -q "Systematics_Yield_Shape.C+(3,\"m_yy\",\"h024_mc16d\",-1,-1)" |tee mylog0;
#root -b -q "Systematics_Yield_Shape.C+(4,\"m_yy\",\"h024_mc16d\",-1,-1)" |tee mylog0;
#exit(1)


#root -b -q "Systematics_Yield_Shape.C+(0,\"m_yy\",\"h024_mc16a\",-1,-1)" |tee mylog0;
# root -b -q "Systematics_Yield_Shape.C+(1,\"m_yy\",\"h024_mc16a\",-1,-1)" |tee mylog1;
# root -b -q "Systematics_Yield_Shape.C+(2,\"m_yy\",\"h024_mc16a\",-1,-1)" |tee mylog2;
# root -b -q "Systematics_Yield_Shape.C+(3,\"m_yy\",\"h024_mc16a\",-1,-1)" |tee mylog3;
# root -b -q "Systematics_Yield_Shape.C+(4,\"m_yy\",\"h024_mc16a\",-1,-1)" |tee mylog4;

#root -b -q "Systematics_Yield_Shape.C+(0,\"m_yy\",\"h024_mc16d\",-1,-1)" |tee mylog0;
#root -b -q "Systematics_Yield_Shape.C+(1,\"m_yy\",\"h024_mc16d\",-1,-1)" |tee mylog1;
#root -b -q "Systematics_Yield_Shape.C+(2,\"m_yy\",\"h024_mc16d\",-1,-1)" |tee mylog2;
#root -b -q "Systematics_Yield_Shape.C+(3,\"m_yy\",\"h024_mc16d\",-1,-1)" |tee mylog3;
#root -b -q "Systematics_Yield_Shape.C+(4,\"m_yy\",\"h024_mc16d\",-1,-1)" |tee mylog4;

#root -b -q "Systematics_Yield_Shape.C+(0,\"m_yy\",\"h024_mc16e\",-1,-1)" |tee mylog0;
#root -b -q "Systematics_Yield_Shape.C+(1,\"m_yy\",\"h024_mc16e\",-1,-1)" |tee mylog1;
#root -b -q "Systematics_Yield_Shape.C+(2,\"m_yy\",\"h024_mc16e\",-1,-1)" |tee mylog2;
#root -b -q "Systematics_Yield_Shape.C+(3,\"m_yy\",\"h024_mc16e\",-1,-1)" |tee mylog3;
#root -b -q "Systematics_Yield_Shape.C+(4,\"m_yy\",\"h024_mc16e\",-1,-1)" |tee mylog4;

#exit(1)

#=========================================
#shape

#classic: no toys
#4 : inclusive
root -b -q "Systematics_Yield_Shape.C+(4,\"m_bb\",\"h024_mc16a_h024_mc16d_h024_mc16e\",-1,1)" |tee log_shape_m_bb_toys_classic_mc16ade_inclusive;
exit(1)

#with toys and bootstrap

#root -b -q "Systematics_Yield_Shape.C+(4,\"m_bb\",\"h024_mc16a_h024_mc16d_h024_mc16e\",0,100)" |tee log_shape_m_bb_toys_bootstrap_mc16ade_inclusive;

#reading toys of bootstrap created previously from batch

#root -b -q "Systematics_Yield_Shape.C+(0,\"m_yy\",\"h024_mc16a_h024_mc16d_h024_mc16e\",0,1)" |tee myloga_0;
#root -b -q "Systematics_Yield_Shape.C+(1,\"m_yy\",\"h024_mc16a_h024_mc16d_h024_mc16e\",0,1)" |tee myloga_1;
#root -b -q "Systematics_Yield_Shape.C+(2,\"m_yy\",\"h024_mc16a_h024_mc16d_h024_mc16e\",0,1)" |tee myloga_2;
#root -b -q "Systematics_Yield_Shape.C+(3,\"m_yy\",\"h024_mc16a_h024_mc16d_h024_mc16e\",0,1)" |tee myloga_3;
#root -b -q "Systematics_Yield_Shape.C+(4,\"m_yy\",\"h024_mc16a_h024_mc16d_h024_mc16e\",0,1)" |tee myloga_4;
#exit(1)



exit(1)


#ttest
#root -b -q "Systematics_Yield_Shape.C+(0,0,5)" |tee mylog1;

#root -b -q "Systematics_Yield_Shape.C+(0,0,10)" |tee mylog1;
#root -b -q "Systematics_Yield_Shape.C+(0,10,20)" |tee mylog2;
#root -b -q "Systematics_Yield_Shape.C+(0,-1,-1)" |tee mylog1;

#=========================================
#classical
#9 minutes
#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a\",-1,-1)" |tee myloga_0;
#root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16a\",-1,-1)" |tee myloga_1;
#root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16a\",-1,-1)" |tee myloga_2;
#root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16a\",-1,-1)" |tee myloga_3;
#root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16a\",-1,-1)" |tee myloga_4;
#exit(1)

#root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16d\",-1,-1)" |tee mylogd_1;
#root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16d\",-1,-1)" |tee mylogd_2;
#root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16d\",-1,-1)" |tee mylogd_3;
#root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16d\",-1,-1)" |tee mylogd_4;

#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16e\",-1,-1)" |tee myloge_0;
#root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16e\",-1,-1)" |tee myloge_1;
#root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16e\",-1,-1)" |tee myloge_2;
#root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16e\",-1,-1)" |tee myloge_3;
#root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16e\",-1,-1)" |tee myloge_4;

#FOR resonant : do inclusive since categories of non resonant have no reason to be fine for it, in particular it is either low or high mass
#root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16a_h024_mc16e\",-1,-1)" |tee myloga_e_4;
exit(1)




#=========================================
#jacknife
#27 minutes
#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",-1,-1)" |tee mylog0;
#exit(1)

# root -b -q "Systematics_Yield_Shape.C+(0,-1,-1)" |tee mylog0;
# root -b -q "Systematics_Yield_Shape.C+(1,-1,-1)" |tee mylog1;
# root -b -q "Systematics_Yield_Shape.C+(2,-1,-1)" |tee mylog2;
# root -b -q "Systematics_Yield_Shape.C+(3,-1,-1)" |tee mylog3;

#=========================================
#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a_h024_mc16d\",0,1)" |tee mylog_mc16d_0;
#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a_h024_mc16d\",0,50)" |tee mylog_mc16d_0;
#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",0,1)" |tee mylog_mc16d_0;
#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",0,50)" |tee mylog_mc16d_0;
#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",0,200)" |tee mylog_mc16d_0;
#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",0,2)" |tee mylog_mc16d_0;
#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",0,199)" |tee mylog_mc16d_0;
#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",0,200)" |tee mylog_mc16d_0;
#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",18,19)" |tee mylog_mc16d_0;

#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a\",0,1)" |tee mylog_mc16a_0;
#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a\",0,50)" |tee mylog_mc16a_0;
#exit(1)

#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a\",0,1)" |tee mylog_mc16a_0;
#root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16a\",0,1)" |tee mylog_mc16a_3;
#exit(1)


#root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16a\",0,200)" |tee mylog_mc16a_3;
#root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16a\",201,400)" |tee mylog_mc16a_3;
#root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16a\",401,600)" |tee mylog_mc16a_3;
#root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16a\",601,800)" |tee mylog_mc16a_3;
#root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16a\",801,1000)" |tee mylog_mc16a_3;
#exit(1)

#reader for shape, bootstrap
root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a_h024_mc16d_h024_mc16e\",0,1)" |tee mylogade_0;
root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16a_h024_mc16d_h024_mc16e\",0,1)" |tee mylogade_1;
root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16a_h024_mc16d_h024_mc16e\",0,1)" |tee mylogade_2;
root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16a_h024_mc16d_h024_mc16e\",0,1)" |tee mylogade_3;
root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16a_h024_mc16d_h024_mc16e\",0,1)" |tee mylogade_4;

exit(1)


#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a_h024_mc16d_h024_mc16e\",0,1)" |tee myloga_0;
#exit(1)
#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a_h024_mc16d_h024_mc16e\",0,100)" |tee myloga_0;
#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a_h024_mc16d_h024_mc16e\",101,200)" |tee myloga_0;
#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a_h024_mc16d_h024_mc16e\",101,150)" |tee myloga_0;
#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a_h024_mc16d_h024_mc16e\",201,300)" |tee myloga_0;
#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a_h024_mc16d_h024_mc16e\",301,400)" |tee myloga_0;
#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a_h024_mc16d_h024_mc16e\",401,500)" |tee myloga_0;
#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a_h024_mc16d_h024_mc16e\",501,600)" |tee myloga_0;
#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a_h024_mc16d_h024_mc16e\",601,700)" |tee myloga_0;
#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a_h024_mc16d_h024_mc16e\",701,800)" |tee myloga_0;
#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a_h024_mc16d_h024_mc16e\",801,900)" |tee myloga_0;
#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a_h024_mc16d_h024_mc16e\",901,1000)" |tee myloga_0;

#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a_h024_mc16d_h024_mc16e\",0,1)" |tee myloga_0;
#root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16a_h024_mc16d_h024_mc16e\",0,1)" |tee myloga_0;
#root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16a_h024_mc16d_h024_mc16e\",0,1)" |tee myloga_0;
#root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16a_h024_mc16d_h024_mc16e\",0,1)" |tee myloga_0;
#root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16a_h024_mc16d_h024_mc16e\",0,1)" |tee myloga_0;
exit(1)


root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a\",0,1000)" |tee mylog_mc16a_0;
root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16a\",0,1000)" |tee mylog_mc16a_1;
root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16a\",0,1000)" |tee mylog_mc16a_2;
root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16a\",0,1000)" |tee mylog_mc16a_3;
root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16a\",0,1000)" |tee mylog_mc16a_4;

root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",0,1000)" |tee mylog_mc16d_0;
root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16d\",0,1000)" |tee mylog_mc16d_1;
root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16d\",0,1000)" |tee mylog_mc16d_2;
root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16d\",0,1000)" |tee mylog_mc16d_3;
root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16d\",0,1000)" |tee mylog_mc16d_4;

root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16e\",0,1000)" |tee mylog_mc16e_0;
root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16e\",0,1000)" |tee mylog_mc16e_1;
root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16e\",0,1000)" |tee mylog_mc16e_2;
root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16e\",0,1000)" |tee mylog_mc16e_3;
root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16e\",0,1000)" |tee mylog_mc16e_4;

exit(1)
#bootstrap
#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a\",0,1500)" |tee mylog;
#root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16a\",0,1500)" |tee mylog;
#root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16a\",0,1500)" |tee mylog;
#root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16a\",0,1500)" |tee mylog;
#root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16a\",0,1500)" |tee mylog;

#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",0,1500)" |tee mylog;
#root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16d\",0,1500)" |tee mylog;
#root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16d\",0,1500)" |tee mylog;
#root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16d\",0,1500)" |tee mylog;
#root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16d\",0,1500)" |tee mylog;

#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16e\",0,1500)" |tee mylog;
#root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16e\",0,1500)" |tee mylog;
#root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16e\",0,1500)" |tee mylog;
#root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16e\",0,1500)" |tee mylog;
#root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16e\",0,1500)" |tee mylog;

#exit(1)
#root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16a\",200,300)" |tee mylog;



#root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16e\",0,50)" |tee mylog;


#root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16e\",17,18)" |tee mylog;




#root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",0,50)" |tee mylog;

#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",0,200)" |tee mylog;

#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",0,500)" |tee mylog;
#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",465,466)" |tee mylog;


#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",0,100)" |tee mylog;
#time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16d\",0,100)" |tee mylog;
#time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16d\",0,100)" |tee mylog;

#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",987,988)" |tee mylog;
#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",988,989)" |tee mylog;
#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",932,933)" |tee mylog;
#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",694,695)" |tee mylog;
#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",403,404)" |tee mylog;
#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",357,358)" |tee mylog;
#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",335,336)" |tee mylog;
#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",269,270)" |tee mylog;
#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",138,139)" |tee mylog;
#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",131,132)" |tee mylog;
#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",113,114)" |tee mylog;
#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",96,97)" |tee mylog;
#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",71,72)" |tee mylog;


#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",31,32)" |tee mylog;
#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",35,36)" |tee mylog;
#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",46,47)" |tee mylog;
#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",62,63)" |tee mylog;
#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",66,67)" |tee mylog;
#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",94,95)" |tee mylog;
#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",0,200)" |tee mylog;

#time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16d\",23,24)" |tee mylog_23_nothing;

#time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16d\",0,1)" |tee mylog0;
#time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16d\",1,2)" |tee mylog1;
#time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16d\",2,3)" |tee mylog2;
#time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16d\",2,3)" |tee mylog2;
#exit(1)

#time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16d\",1,2)" |tee mylog0;
#time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16d\",1238,1239)" |tee mylog0;

#time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16d\",0,8)" |tee mylog0;
#exit(1)

#time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16d\",0,100)" |tee mylog0;
#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",0,100)" |tee mylog0;
#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",0,1)" |tee mylog0;
#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",1,2)" |tee mylog0;




# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",0,100)" |tee mylogd_0;
# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",100,200)" |tee mylogd_1;
# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",200,300)" |tee mylogd_2;
# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",300,400)" |tee mylogd_3;
# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",400,500)" |tee mylogd_4;
# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",500,600)" |tee mylogd_5;
# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",600,700)" |tee mylogd_6;
# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",700,800)" |tee mylogd_7;
# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",800,900)" |tee mylogd_8;
# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",900,1000)" |tee mylogd_9;

# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16d\",0,100)" |tee mylogd_0;
# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16d\",100,200)" |tee mylogd_1;
# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16d\",200,300)" |tee mylogd_2;
# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16d\",300,400)" |tee mylogd_3;
# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16d\",400,500)" |tee mylogd_4;
# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16d\",500,600)" |tee mylogd_5;
# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16d\",600,700)" |tee mylogd_6;
# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16d\",700,800)" |tee mylogd_7;
# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16d\",800,900)" |tee mylogd_8;
# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16d\",900,1000)" |tee mylogd_9;

# time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16d\",0,100)" |tee mylogd_0;
# time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16d\",100,200)" |tee mylogd_1;
# time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16d\",200,300)" |tee mylogd_2;
# time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16d\",300,400)" |tee mylogd_3;
# time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16d\",400,500)" |tee mylogd_4;
# time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16d\",500,600)" |tee mylogd_5;
# time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16d\",600,700)" |tee mylogd_6;
# time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16d\",700,800)" |tee mylogd_7;
# time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16d\",800,900)" |tee mylogd_8;
# time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16d\",900,1000)" |tee mylogd_9;

# time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16d\",0,100)" |tee mylogd_1;
# time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16d\",100,200)" |tee mylogd_1;
# time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16d\",200,300)" |tee mylogd_2;
# time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16d\",300,400)" |tee mylogd_3;
# time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16d\",400,500)" |tee mylogd_4;
# time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16d\",500,600)" |tee mylogd_5;
# time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16d\",600,700)" |tee mylogd_6;
# time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16d\",700,800)" |tee mylogd_7;
# time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16d\",800,900)" |tee mylogd_8;
# time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16d\",900,1000)" |tee mylogd_9;

# time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16d\",0,100)" |tee mylogd_1;
# time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16d\",100,200)" |tee mylogd_1;
# time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16d\",200,300)" |tee mylogd_2;
# time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16d\",300,400)" |tee mylogd_3;
# time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16d\",400,500)" |tee mylogd_4;
# time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16d\",500,600)" |tee mylogd_5;
# time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16d\",600,700)" |tee mylogd_6;
# time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16d\",700,800)" |tee mylogd_7;
# time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16d\",800,900)" |tee mylogd_8;
# time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16d\",900,1000)" |tee mylogd_9;











 time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a\",0,100)" |tee myloga_0;
exit(1)
# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a\",100,200)" |tee myloga_1;
# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a\",200,300)" |tee myloga_2;
# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a\",300,400)" |tee myloga_3;
# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a\",400,500)" |tee myloga_4;
# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a\",500,600)" |tee myloga_5;
# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a\",600,700)" |tee myloga_6;
# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a\",700,800)" |tee myloga_7;
# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a\",800,900)" |tee myloga_8;
# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a\",900,1000)" |tee myloga_9;

# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16a\",0,100)" |tee myloga_0;
# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16a\",100,200)" |tee myloga_1;
# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16a\",200,300)" |tee myloga_2;
# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16a\",300,400)" |tee myloga_3;
# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16a\",400,500)" |tee myloga_4;
# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16a\",500,600)" |tee myloga_5;
# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16a\",600,700)" |tee myloga_6;
# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16a\",700,800)" |tee myloga_7;
# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16a\",800,900)" |tee myloga_8;
# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16a\",900,1000)" |tee myloga_9;

# time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16a\",0,100)" |tee myloga_0;
# time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16a\",100,200)" |tee myloga_1;
# time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16a\",200,300)" |tee myloga_2;
# time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16a\",300,400)" |tee myloga_3;
# time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16a\",400,500)" |tee myloga_4;
# time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16a\",500,600)" |tee myloga_5;
# time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16a\",600,700)" |tee myloga_6;
# time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16a\",700,800)" |tee myloga_7;
# time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16a\",800,900)" |tee myloga_8;
# time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16a\",900,1000)" |tee myloga_9;

# time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16a\",0,100)" |tee myloga_1;
# time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16a\",100,200)" |tee myloga_1;
# time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16a\",200,300)" |tee myloga_2;
# time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16a\",300,400)" |tee myloga_3;
# time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16a\",400,500)" |tee myloga_4;
# time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16a\",500,600)" |tee myloga_5;
# time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16a\",600,700)" |tee myloga_6;
# time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16a\",700,800)" |tee myloga_7;
# time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16a\",800,900)" |tee myloga_8;
# time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16a\",900,1000)" |tee myloga_9;

# time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16a\",0,100)" |tee myloga_1;
# time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16a\",100,200)" |tee myloga_1;
# time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16a\",200,300)" |tee myloga_2;
# time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16a\",300,400)" |tee myloga_3;
# time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16a\",400,500)" |tee myloga_4;
# time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16a\",500,600)" |tee myloga_5;
# time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16a\",600,700)" |tee myloga_6;
# time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16a\",700,800)" |tee myloga_7;
# time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16a\",800,900)" |tee myloga_8;
# time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16a\",900,1000)" |tee myloga_9;




# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16e\",0,100)" |tee myloge_0;
# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16e\",100,200)" |tee myloge_1;
# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16e\",200,300)" |tee myloge_2;
# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16e\",300,400)" |tee myloge_3;
# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16e\",400,500)" |tee myloge_4;
# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16e\",500,600)" |tee myloge_5;
# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16e\",600,700)" |tee myloge_6;
# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16e\",700,800)" |tee myloge_7;
# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16e\",800,900)" |tee myloge_8;
# time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16e\",900,1000)" |tee myloge_9;

#time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16e\",0,100)" |tee myloge_0;
# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16e\",100,200)" |tee myloge_1;
# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16e\",200,300)" |tee myloge_2;
# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16e\",300,400)" |tee myloge_3;
# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16e\",400,500)" |tee myloge_4;
# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16e\",500,600)" |tee myloge_5;
# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16e\",600,700)" |tee myloge_6;
# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16e\",700,800)" |tee myloge_7;
# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16e\",800,900)" |tee myloge_8;
# time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16e\",900,1000)" |tee myloge_9;

#time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16e\",0,100)" |tee myloge_0;
#time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16e\",100,200)" |tee myloge_1;
#time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16e\",200,300)" |tee myloge_2;
#time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16e\",300,400)" |tee myloge_3;
#time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16e\",400,500)" |tee myloge_4;
#time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16e\",500,600)" |tee myloge_5;
#time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16e\",600,700)" |tee myloge_6;
#time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16e\",700,800)" |tee myloge_7;
#time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16e\",800,900)" |tee myloge_8;
#time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16e\",900,1000)" |tee myloge_9;

#time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16e\",0,100)" |tee myloge_1;
#time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16e\",100,200)" |tee myloge_1;
#time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16e\",200,300)" |tee myloge_2;
#time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16e\",300,400)" |tee myloge_3;
#time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16e\",400,500)" |tee myloge_4;
#time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16e\",500,600)" |tee myloge_5;
#time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16e\",600,700)" |tee myloge_6;
#time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16e\",700,800)" |tee myloge_7;
#time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16e\",800,900)" |tee myloge_8;
#time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16e\",900,1000)" |tee myloge_9;

#time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16e\",0,100)" |tee myloge_1;
#time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16e\",100,200)" |tee myloge_1;
#time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16e\",200,300)" |tee myloge_2;
#time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16e\",300,400)" |tee myloge_3;
#time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16e\",400,500)" |tee myloge_4;
#time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16e\",500,600)" |tee myloge_5;
#time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16e\",600,700)" |tee myloge_6;
#time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16e\",700,800)" |tee myloge_7;
#time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16e\",800,900)" |tee myloge_8;
#time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16e\",900,1000)" |tee myloge_9;


#time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16d\",0,1)" |tee mylogd;
#with the problem time root -b -q "Systematics_Yield_Shape.C+(2,\"h024_mc16e\",400,500)" |tee mylog;
#time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16e\",100,200)" |tee mylog;
#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16a\",400,500)" |tee mylog;
#time root -b -q "Systematics_Yield_Shape.C+(0,\"h024_mc16d\",0,100)" |tee mylog;
#time root -b -q "Systematics_Yield_Shape.C+(4,\"h024_mc16d\",400,500)" |tee mylog;
#time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16d\",300,400)" |tee mylog;


#time root -b -q "Systematics_Yield_Shape.C+(1,\"h024_mc16d\",500,550)" |tee mylog;
#time root -b -q "Systematics_Yield_Shape.C+(3,\"h024_mc16d\",0,100)" |tee mylog14;
