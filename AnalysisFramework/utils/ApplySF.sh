var="m_yy"
target="yybb yyrr"
#target="yy jj yj yybb yyrr"
data="15_to_18_data"
ttyyall="ttyy_allhad"
ttyyno="ttyy_noallhad"
region="Validation_2bjet XGBoost_btag77_withTop_BCal_looseScore_HMass XGBoost_btag77_withTop_BCal_looseScore_LMass XGBoost_btag77_withTop_BCal_tightScore_HMass XGBoost_btag77_withTop_BCal_tightScore_LMass"

for v in $var;do
for t in $target;do
for re in $region;do
./ApplySF $re $t $data $ttyyall $ttyyno $v
done
done
done
