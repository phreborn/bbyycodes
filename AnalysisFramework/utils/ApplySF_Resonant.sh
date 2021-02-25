var="m_yy"
target="yy jj yj"
RES="251 260 280 300 325 350 400 450 500 550 600 700 800 900 1000"
#RES="550"
data="15_to_18_data_m_yyjj"
ttyyall="ttyy_allhad_m_yyjj"
ttyyno="ttyy_noallhad_m_yyjj"
region="BDT_Selection_h026_optimized"

for v in $var;do
for t in $target;do
for re in $region;do
for x in $RES;do
./ApplySF_Resonant $re X${x}toHH $t $data $ttyyall $ttyyno $v
done
done
done
done
