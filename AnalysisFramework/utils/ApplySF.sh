var="m_yy"
target="15_to_18_data_jj 15_to_18_data_yj"
data="15_to_18_data_SB"
ttyyall="ttyy_allhad_SB"
ttyyno="ttyy_noallhad_SB"
region="Validation_2bjet XGBoost_btag77_withTop_BCal_looseScore_HMass XGBoost_btag77_withTop_BCal_looseScore_LMass XGBoost_btag77_withTop_BCal_tightScore_HMass XGBoost_btag77_withTop_BCal_tightScore_LMass"
#region="XGBoost_btag77_withTop_BCal_looseScore_LMass"
#region="Validation_2bjet"

for v in $var;do
for t in $target;do
for re in $region;do
./ApplySF $re $t $data $ttyyall $ttyyno $v
done
done
done
