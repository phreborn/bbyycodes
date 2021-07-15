#!bin/bash

declare -a WSs=(
		WS-yybb-nonresonant_BDT_h026_v7_kl1p0_mu_blind.root
		WS-yybb-nonresonant_BDT_h026_v7_kl10p0_mu_blind.root
		)

declare -a opts=(
		BKG HH_ALL HH_ggF HH_VBF H_ALL H_ggH H_ttH H_ZH H_REST
		)
for WS in "${WSs[@]}"
do
	for opt in "${opts[@]}"
	do
		./bin/calcNbkgHighMassgg FIT yybb_${opt}_${WS} ${WS} asimov_${opt}
	done
done
