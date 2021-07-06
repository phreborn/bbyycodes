var="m_yy"
#target="yy jj yj"
target="yybb yyrr"
#target="yy"
RES="251 260 270 280 290 300 3125 325 3375 350 375 400 425 450 475 500 550 600 700 800 900 1000"
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
