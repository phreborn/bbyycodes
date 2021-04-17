
TO SEE DATES FILES BEFORE HADDING !!


#TO MAKE A SCRIPT WITH AWK FOR AUTOMATIZING THAT STUFF FASTER
#exists already for ttH : to copy on other places !!

!/bin/bash
#see https://fr.wikipedia.org/wiki/Shebang

#done per thematic, separately

#For trees shape: to merge all various thematics together

export string_path=/sps/atlas/e/escalier/ATLAS_HGam/Outputs_syst_yield_shape

echo ${string_path}

#remark : hadd does not tell if the structure is different

#exit(1)


#see : https://unix.stackexchange.com/questions/628400/why-is-my-unix-basic-script-does-not-do-what-i-try-to-how-to-write-abc-1-abc/628429#628429

#################################################################################
#Theory systematics

#================================================================================
#HH kappa_lambda=1
rename in gg_HH

rm -f ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_nominal.root

mylist=( `ls ${string_path}/trees_and_hist/Theory/ | grep h026 |grep PowhegH7_HHbbyy_cHHH01d0_nominal` )

hadd ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_nominal.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/Theory/$i" ; done`

#================================================================================
#HH kappa_lambda=10

rm -f ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_10_nominal.root

mylist=( `ls ${string_path}/trees_and_hist/Theory/ | grep h026 |grep PowhegH7_HHbbyy_cHHH10d0_nominal` )

hadd ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_10_nominal.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/Theory/$i" ; done`
#================================================================================
#ggH : shit : new name

rm -f ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys.root
mylist=( `ls ${string_path}/trees_and_hist/Theory/ | grep h026 |grep ggH125` )
hadd ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/Theory/$i" ; done`
#================================================================================
#ZH

rm -f ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_ZH125_PhotonSys.root

mylist=( `ls ${string_path}/trees_and_hist/Theory/ | grep h026 |grep ZH125` )
hadd ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_ZH125_PhotonSys.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/Theory/$i" ; done`
#================================================================================
#ttH

rm -f ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_ttH125_PhotonSys.root

mylist=( `ls ${string_path}/trees_and_hist/Theory/ | grep h026 |grep ttH125` )
hadd ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_ttH125_PhotonSys.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/Theory/$i" ; done`
#================================================================================
#HH resonant

list_mX=(X251 X260 X280 X300 X325 X350 X400 X450 X500 X550 X600 X700 X800 X900 X1000)
list_MxAODSys=(nominal)

for index_mX in $list_mX
  do
  
  echo "==============================="
  echo Deal with MGH7_${index_mX}
  
  for index_MxAODSys in $list_MxAODSys
    do
    
    echo "-------------------------------"
    echo Deal with MxAODSyst : ${index_MxAODSys}
    
    rm -f ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_${index_mX}tohh_bbyy_AF2_${index_MxAODSys}.root
    
    list_samples=( `ls ${string_path}/trees_and_hist/Theory/ | grep h026 |grep ${index_mX}` )
    
    echo $list_samples
    
    hadd ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_${index_mX}tohh_bbyy_AF2_${index_MxAODSys}.root `for index_sample in $list_samples ; do echo "${string_path}/trees_and_hist/Theory/$index_sample" ; done`
    
  done
done
#################################################################################
#Experimental systematics

#================================================================================
#HH non resonant, kappa_lambda=1 (Py8)
#----
#PhotonSys

rm -f ${string_path}/trees_and_hist/PhotonSys/h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_PhotonSys.root

mylist=( `ls ${string_path}/trees_and_hist/PhotonSys/ | grep h026 |grep PowhegPy8_HHbbyy_cHHH01d0 |grep PhotonSys` )

hadd ${string_path}/trees_and_hist/PhotonSys/h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_PhotonSys.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/PhotonSys/$i" ; done`
#----
#JetSys1

rm -f ${string_path}/trees_and_hist/JetSys1/h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_JetSys1.root

mylist=( `ls ${string_path}/trees_and_hist/JetSys1/ | grep h026 |grep PowhegPy8_HHbbyy_cHHH01d0 |grep JetSys1` )

hadd ${string_path}/trees_and_hist/JetSys1/h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_JetSys1.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/JetSys1/$i" ; done`
#----
#JetSys2

rm -f ${string_path}/trees_and_hist/JetSys2/h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_JetSys2.root

mylist=( `ls ${string_path}/trees_and_hist/JetSys2/ | grep h026 |grep PowhegPy8_HHbbyy_cHHH01d0 |grep JetSys2` )

hadd ${string_path}/trees_and_hist/JetSys2/h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_JetSys2.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/JetSys2/$i" ; done`
#----
#JetSys3

rm -f ${string_path}/trees_and_hist/JetSys3/h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_JetSys3.root

mylist=( `ls ${string_path}/trees_and_hist/JetSys3/ | grep h026 |grep PowhegPy8_HHbbyy_cHHH01d0 |grep JetSys3` )

hadd ${string_path}/trees_and_hist/JetSys3/h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_JetSys3.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/JetSys3/$i" ; done`
#----
#JetSys4

rm -f ${string_path}/trees_and_hist/JetSys4/h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_JetSys4.root

mylist=( `ls ${string_path}/trees_and_hist/JetSys4/ | grep h026 |grep PowhegPy8_HHbbyy_cHHH01d0 |grep JetSys4` )

hadd ${string_path}/trees_and_hist/JetSys4/h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_JetSys4.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/JetSys4/$i" ; done`
#----
#FlavorSys

rm -f ${string_path}/trees_and_hist/FlavorSys/h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_FlavorSys.root

mylist=( `ls ${string_path}/trees_and_hist/FlavorSys/ | grep h026 |grep PowhegPy8_HHbbyy_cHHH01d0 |grep FlavorSys` )

hadd ${string_path}/trees_and_hist/FlavorSys/h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_01_FlavorSys.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/FlavorSys/$i" ; done`
#================================================================================
#HH non resonant, kappa_lambda=10
#----
#PhotonSys

rm -f ${string_path}/trees_and_hist/PhotonSys/h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_10_PhotonSys.root

mylist=( `ls ${string_path}/trees_and_hist/PhotonSys/ | grep h026 |grep PowhegPy8_HHbbyy_cHHH10d0 |grep PhotonSys` )

hadd ${string_path}/trees_and_hist/PhotonSys/h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_10_PhotonSys.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/PhotonSys/$i" ; done`
#----
#JetSys1

rm -f ${string_path}/trees_and_hist/JetSys1/h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_10_JetSys1.root

mylist=( `ls ${string_path}/trees_and_hist/JetSys1/ | grep h026 |grep PowhegPy8_HHbbyy_cHHH10d0 |grep JetSys1` )

hadd ${string_path}/trees_and_hist/JetSys1/h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_10_JetSys1.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/JetSys1/$i" ; done`
#----
#JetSys2

rm -f ${string_path}/trees_and_hist/JetSys2/h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_10_JetSys2.root

mylist=( `ls ${string_path}/trees_and_hist/JetSys2/ | grep h026 |grep PowhegPy8_HHbbyy_cHHH10d0 |grep JetSys2` )

hadd ${string_path}/trees_and_hist/JetSys2/h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_10_JetSys2.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/JetSys2/$i" ; done`
#----
#JetSys3

rm -f ${string_path}/trees_and_hist/JetSys3/h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_10_JetSys3.root

mylist=( `ls ${string_path}/trees_and_hist/JetSys3/ | grep h026 |grep PowhegPy8_HHbbyy_cHHH10d0 |grep JetSys3` )

hadd ${string_path}/trees_and_hist/JetSys3/h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_10_JetSys3.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/JetSys3/$i" ; done`
#----
#JetSys4

rm -f ${string_path}/trees_and_hist/JetSys4/h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_10_JetSys4.root

mylist=( `ls ${string_path}/trees_and_hist/JetSys4/ | grep h026 |grep PowhegPy8_HHbbyy_cHHH10d0 |grep JetSys4` )

hadd ${string_path}/trees_and_hist/JetSys4/h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_10_JetSys4.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/JetSys4/$i" ; done`
#----
#FlavorSys

rm -f ${string_path}/trees_and_hist/FlavorSys/h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_10_FlavorSys.root

mylist=( `ls ${string_path}/trees_and_hist/FlavorSys/ | grep h026 |grep PowhegPy8_HHbbyy_cHHH10d0 |grep FlavorSys` )

hadd ${string_path}/trees_and_hist/FlavorSys/h026_mc16a_h026_mc16d_h026_mc16e_gg_HH_non_resonant_kappa_lambda_10_FlavorSys.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/FlavorSys/$i" ; done`
#================================================================================
#vbf HH non resonant, kappa_lambda=1
#----
#PhotonSys

rm -f ${string_path}/trees_and_hist/PhotonSys/h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_PhotonSys.root

mylist=( `ls ${string_path}/trees_and_hist/PhotonSys/ | grep h026 |grep MGPy8_hh_bbyy_vbf_l1cvv1cv1 |grep PhotonSys` )

hadd ${string_path}/trees_and_hist/PhotonSys/h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_PhotonSys.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/PhotonSys/$i" ; done`
#----
#JetSys1

rm -f ${string_path}/trees_and_hist/JetSys1/h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_JetSys1.root

mylist=( `ls ${string_path}/trees_and_hist/JetSys1/ | grep h026 |grep MGPy8_hh_bbyy_vbf_l1cvv1cv1 |grep JetSys1` )

hadd ${string_path}/trees_and_hist/JetSys1/h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_JetSys1.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/JetSys1/$i" ; done`
#----
#JetSys2

rm -f ${string_path}/trees_and_hist/JetSys2/h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_JetSys2.root

mylist=( `ls ${string_path}/trees_and_hist/JetSys2/ | grep h026 |grep MGPy8_hh_bbyy_vbf_l1cvv1cv1 |grep JetSys2` )

hadd ${string_path}/trees_and_hist/JetSys2/h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_JetSys2.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/JetSys2/$i" ; done`
#----
#JetSys3

rm -f ${string_path}/trees_and_hist/JetSys3/h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_JetSys3.root

mylist=( `ls ${string_path}/trees_and_hist/JetSys3/ | grep h026 |grep MGPy8_hh_bbyy_vbf_l1cvv1cv1 |grep JetSys3` )

hadd ${string_path}/trees_and_hist/JetSys3/h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_JetSys3.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/JetSys3/$i" ; done`
#----
#JetSys4

rm -f ${string_path}/trees_and_hist/JetSys4/h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_JetSys4.root

mylist=( `ls ${string_path}/trees_and_hist/JetSys4/ | grep h026 |grep MGPy8_hh_bbyy_vbf_l1cvv1cv1 |grep JetSys4` )

hadd ${string_path}/trees_and_hist/JetSys4/h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_JetSys4.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/JetSys4/$i" ; done`
#----
#FlavorSys

rm -f ${string_path}/trees_and_hist/FlavorSys/h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_FlavorSys.root

mylist=( `ls ${string_path}/trees_and_hist/FlavorSys/ | grep h026 |grep MGPy8_hh_bbyy_vbf_l1cvv1cv1 |grep FlavorSys` )

hadd ${string_path}/trees_and_hist/FlavorSys/h026_mc16a_h026_mc16d_h026_mc16e_vbf_HH_non_resonant_kappa_lambda_01_FlavorSys.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/FlavorSys/$i" ; done`
#================================================================================
#================================================================================
#ggH

#----
#PhotonSys
rm -f ${string_path}/trees_and_hist/PhotonSys/h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys.root

mylist=( `ls ${string_path}/trees_and_hist/PhotonSys/ | grep h026 |grep PowhegPy8_NNLOPS_ggH125 |grep PhotonSys` )

hadd ${string_path}/trees_and_hist/PhotonSys/h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/PhotonSys/$i" ; done`
#----
#JetSys1

rm -f ${string_path}/trees_and_hist/JetSys1/h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys1.root

mylist=( `ls ${string_path}/trees_and_hist/JetSys1/ | grep h026 |grep PowhegPy8_NNLOPS_ggH125 |grep JetSys1` )

hadd ${string_path}/trees_and_hist/JetSys1/h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys1.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/JetSys1/$i" ; done`
#----
#JetSys2

rm -f ${string_path}/trees_and_hist/JetSys2/h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys2.root

mylist=( `ls ${string_path}/trees_and_hist/JetSys2/ | grep h026 |grep PowhegPy8_NNLOPS_ggH125 |grep JetSys2` )

hadd ${string_path}/trees_and_hist/JetSys2/h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys2.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/JetSys2/$i" ; done`
#----
#JetSys3

rm -f ${string_path}/trees_and_hist/JetSys3/h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys3.root

mylist=( `ls ${string_path}/trees_and_hist/JetSys3/ | grep h026 |grep PowhegPy8_NNLOPS_ggH125 |grep JetSys3` )

hadd ${string_path}/trees_and_hist/JetSys3/h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys3.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/JetSys3/$i" ; done`
#----
#JetSys4

rm -f ${string_path}/trees_and_hist/JetSys4/h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys4.root

mylist=( `ls ${string_path}/trees_and_hist/JetSys4/ | grep h026 |grep PowhegPy8_NNLOPS_ggH125 |grep JetSys4` )

hadd ${string_path}/trees_and_hist/JetSys4/h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys4.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/JetSys4/$i" ; done`
#----
#FlavorSys

rm -f ${string_path}/trees_and_hist/FlavorSys/h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_FlavorSys.root

mylist=( `ls ${string_path}/trees_and_hist/FlavorSys/ | grep h026 |grep PowhegPy8_NNLOPS_ggH125 |grep FlavorSys` )

hadd ${string_path}/trees_and_hist/FlavorSys/h026_mc16a_h026_mc16d_h026_mc16e_PowhegPy8_NNLOPS_ggH125_FlavorSys.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/FlavorSys/$i" ; done`
#----
#================================================================================
#ZH (qq+gg)
#----
#PhotonSys
rm -f ${string_path}/trees_and_hist/PhotonSys/h026_mc16a_h026_mc16d_h026_mc16e_ZH125_PhotonSys.root

mylist=( `ls ${string_path}/trees_and_hist/PhotonSys/ | grep h026 |grep ZH125 |grep PhotonSys` )

hadd ${string_path}/trees_and_hist/PhotonSys/h026_mc16a_h026_mc16d_h026_mc16e_ZH125_PhotonSys.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/PhotonSys/$i" ; done`
#----
#JetSys1

rm -f ${string_path}/trees_and_hist/JetSys1/h026_mc16a_h026_mc16d_h026_mc16e_ZH125_JetSys1.root

mylist=( `ls ${string_path}/trees_and_hist/JetSys1/ | grep h026 |grep ZH125 |grep JetSys1` )

hadd ${string_path}/trees_and_hist/JetSys1/h026_mc16a_h026_mc16d_h026_mc16e_ZH125_JetSys1.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/JetSys1/$i" ; done`
#----
#JetSys2

rm -f ${string_path}/trees_and_hist/JetSys2/h026_mc16a_h026_mc16d_h026_mc16e_ZH125_JetSys2.root

mylist=( `ls ${string_path}/trees_and_hist/JetSys2/ | grep h026 |grep ZH125 |grep JetSys2` )

hadd ${string_path}/trees_and_hist/JetSys2/h026_mc16a_h026_mc16d_h026_mc16e_ZH125_JetSys2.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/JetSys2/$i" ; done`
#----
#JetSys3

rm -f ${string_path}/trees_and_hist/JetSys3/h026_mc16a_h026_mc16d_h026_mc16e_ZH125_JetSys3.root

mylist=( `ls ${string_path}/trees_and_hist/JetSys3/ | grep h026 |grep ZH125 |grep JetSys3` )

hadd ${string_path}/trees_and_hist/JetSys3/h026_mc16a_h026_mc16d_h026_mc16e_ZH125_JetSys3.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/JetSys3/$i" ; done`
#----
#JetSys4

rm -f ${string_path}/trees_and_hist/JetSys4/h026_mc16a_h026_mc16d_h026_mc16e_ZH125_JetSys4.root

mylist=( `ls ${string_path}/trees_and_hist/JetSys4/ | grep h026 |grep ZH125 |grep JetSys4` )

hadd ${string_path}/trees_and_hist/JetSys4/h026_mc16a_h026_mc16d_h026_mc16e_ZH125_JetSys4.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/JetSys4/$i" ; done`
#----
#FlavorSys

rm -f ${string_path}/trees_and_hist/FlavorSys/h026_mc16a_h026_mc16d_h026_mc16e_ZH125_FlavorSys.root

mylist=( `ls ${string_path}/trees_and_hist/FlavorSys/ | grep h026 |grep ZH125 |grep FlavorSys` )

hadd ${string_path}/trees_and_hist/FlavorSys/h026_mc16a_h026_mc16d_h026_mc16e_ZH125_FlavorSys.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/FlavorSys/$i" ; done`
#----
#================================================================================
#ttH
#----
#PhotonSys
rm -f ${string_path}/trees_and_hist/PhotonSys/h026_mc16a_h026_mc16d_h026_mc16e_ttH125_PhotonSys.root

mylist=( `ls ${string_path}/trees_and_hist/PhotonSys/ | grep h026 |grep ttH125 |grep PhotonSys` )

hadd ${string_path}/trees_and_hist/PhotonSys/h026_mc16a_h026_mc16d_h026_mc16e_ttH125_PhotonSys.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/PhotonSys/$i" ; done`
#----
#JetSys1

rm -f ${string_path}/trees_and_hist/JetSys1/h026_mc16a_h026_mc16d_h026_mc16e_ttH125_JetSys1.root

mylist=( `ls ${string_path}/trees_and_hist/JetSys1/ | grep h026 |grep ttH125 |grep JetSys1` )

hadd ${string_path}/trees_and_hist/JetSys1/h026_mc16a_h026_mc16d_h026_mc16e_ttH125_JetSys1.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/JetSys1/$i" ; done`
#----
#JetSys2

rm -f ${string_path}/trees_and_hist/JetSys2/h026_mc16a_h026_mc16d_h026_mc16e_ttH125_JetSys2.root

mylist=( `ls ${string_path}/trees_and_hist/JetSys2/ | grep h026 |grep ttH125 |grep JetSys2` )

hadd ${string_path}/trees_and_hist/JetSys2/h026_mc16a_h026_mc16d_h026_mc16e_ttH125_JetSys2.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/JetSys2/$i" ; done`
#----
#JetSys3

rm -f ${string_path}/trees_and_hist/JetSys3/h026_mc16a_h026_mc16d_h026_mc16e_ttH125_JetSys3.root

mylist=( `ls ${string_path}/trees_and_hist/JetSys3/ | grep h026 |grep ttH125 |grep JetSys3` )

hadd ${string_path}/trees_and_hist/JetSys3/h026_mc16a_h026_mc16d_h026_mc16e_ttH125_JetSys3.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/JetSys3/$i" ; done`
#----
#JetSys4

rm -f ${string_path}/trees_and_hist/JetSys4/h026_mc16a_h026_mc16d_h026_mc16e_ttH125_JetSys4.root

mylist=( `ls ${string_path}/trees_and_hist/JetSys4/ | grep h026 |grep ttH125 |grep JetSys4` )

hadd ${string_path}/trees_and_hist/JetSys4/h026_mc16a_h026_mc16d_h026_mc16e_ttH125_JetSys4.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/JetSys4/$i" ; done`
#----
#FlavorSys

rm -f ${string_path}/trees_and_hist/FlavorSys/h026_mc16a_h026_mc16d_h026_mc16e_ttH125_FlavorSys.root

mylist=( `ls ${string_path}/trees_and_hist/FlavorSys/ | grep h026 |grep ttH125 |grep FlavorSys` )

hadd ${string_path}/trees_and_hist/FlavorSys/h026_mc16a_h026_mc16d_h026_mc16e_ttH125_FlavorSys.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/FlavorSys/$i" ; done`
#----




#================================================================================
#HH resonant

#norm to have error sometimes, because in some cases, none of the sample if available
list_mX=(X251 X260 X280 X300 X325 X350 X400 X450 X500 X550 X600 X700 X800 X900 X1000)

#list_mX=(X251 X260 X280 X300 X325)
#list_mX=(X251 X260 X280 X300)
#list_mX=(X325)
list_MxAODSys=(PhotonSys JetSys1 JetSys2 JetSys3 JetSys4 FlavorSys)
#list_MxAODSys=(PhotonSys)
#list_MxAODSys=(JetSys1)
#list_MxAODSys=(JetSys2)
#list_MxAODSys=(JetSys3)

for index_mX in $list_mX
  do
  
  echo "==============================="
  echo Deal with MGH7_${index_mX}
  
  for index_MxAODSys in $list_MxAODSys
    do
    
    echo "-------------------------------"
    echo Deal with MxAODSyst : ${index_MxAODSys}
    
    rm -f ${string_path}/trees_and_hist/${index_MxAODSys}/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_${index_mX}tohh_bbyy_AF2_${index_MxAODSys}.root
    
    list_samples=( `ls ${string_path}/trees_and_hist/${index_MxAODSys}/ | grep h026 |grep ${index_mX}` )
    
    echo $list_samples
    
    hadd ${string_path}/trees_and_hist/${index_MxAODSys}/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_${index_mX}tohh_bbyy_AF2_${index_MxAODSys}.root `for index_sample in $list_samples ; do echo "${string_path}/trees_and_hist/${index_MxAODSys}/$index_sample" ; done`
    
  done
done


#END
# for index_mX in X260 X280
# do
# echo Hello MGH7_${index_mX}
# done
# Hello MGH7_X260
# Hello MGH7_X280
# works
#===============================
#HH resonant
#================================================================================
#Theory systematics

#to do a script with a loop on mX !

#vector<int> vec_mX={251,260,280,300,325,350,400,450,500,550,600,700,800,900,1000}; //for categories

rm -f ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X260tohh_bbyy_AF2_nominal.root
mylist=( `ls ${string_path}/trees_and_hist/Theory/ | grep h026 |grep MGH7_X260` )
hadd ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X260tohh_bbyy_AF2_nominal.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/Theory/$i" ; done`

rm -f ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X280tohh_bbyy_AF2_nominal.root
mylist=( `ls ${string_path}/trees_and_hist/Theory/ | grep h026 |grep MGH7_X280` )
hadd ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X280tohh_bbyy_AF2_nominal.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/Theory/$i" ; done`

rm -f ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X300tohh_bbyy_AF2_nominal.root
mylist=( `ls ${string_path}/trees_and_hist/Theory/ | grep h026 |grep MGH7_X300` )
hadd ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X300tohh_bbyy_AF2_nominal.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/Theory/$i" ; done`

rm -f ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X325tohh_bbyy_AF2_nominal.root
mylist=( `ls ${string_path}/trees_and_hist/Theory/ | grep h026 |grep MGH7_X325` )
hadd ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X325tohh_bbyy_AF2_nominal.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/Theory/$i" ; done`

rm -f ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X350tohh_bbyy_AF2_nominal.root
mylist=( `ls ${string_path}/trees_and_hist/Theory/ | grep h026 |grep MGH7_X350` )
hadd ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X350tohh_bbyy_AF2_nominal.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/Theory/$i" ; done`

rm -f ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X400tohh_bbyy_AF2_nominal.root
mylist=( `ls ${string_path}/trees_and_hist/Theory/ | grep h026 |grep MGH7_X400` )
hadd ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X400tohh_bbyy_AF2_nominal.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/Theory/$i" ; done`

rm -f ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X450tohh_bbyy_AF2_nominal.root
mylist=( `ls ${string_path}/trees_and_hist/Theory/ | grep h026 |grep MGH7_X450` )
hadd ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X450tohh_bbyy_AF2_nominal.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/Theory/$i" ; done`

rm -f ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X500tohh_bbyy_AF2_nominal.root
mylist=( `ls ${string_path}/trees_and_hist/Theory/ | grep h026 |grep MGH7_X500` )
hadd ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X500tohh_bbyy_AF2_nominal.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/Theory/$i" ; done`

rm -f ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X550tohh_bbyy_AF2_nominal.root
mylist=( `ls ${string_path}/trees_and_hist/Theory/ | grep h026 |grep MGH7_X550` )
hadd ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X550tohh_bbyy_AF2_nominal.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/Theory/$i" ; done`

rm -f ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X600tohh_bbyy_AF2_nominal.root
mylist=( `ls ${string_path}/trees_and_hist/Theory/ | grep h026 |grep MGH7_X600` )
hadd ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X600tohh_bbyy_AF2_nominal.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/Theory/$i" ; done`

rm -f ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X700tohh_bbyy_AF2_nominal.root
mylist=( `ls ${string_path}/trees_and_hist/Theory/ | grep h026 |grep MGH7_X700` )
hadd ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X700tohh_bbyy_AF2_nominal.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/Theory/$i" ; done`

rm -f ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X800tohh_bbyy_AF2_nominal.root
mylist=( `ls ${string_path}/trees_and_hist/Theory/ | grep h026 |grep MGH7_X800` )
hadd ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X800tohh_bbyy_AF2_nominal.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/Theory/$i" ; done`

rm -f ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X900tohh_bbyy_AF2_nominal.root
mylist=( `ls ${string_path}/trees_and_hist/Theory/ | grep h026 |grep MGH7_X900` )
hadd ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X900tohh_bbyy_AF2_nominal.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/Theory/$i" ; done`

rm -f ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X1000tohh_bbyy_AF2_nominal.root
mylist=( `ls ${string_path}/trees_and_hist/Theory/ | grep h026 |grep MGH7_X1000` )
hadd ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_MGH7_X1000tohh_bbyy_AF2_nominal.root `for i in $mylist ; do echo "${string_path}/trees_and_hist/Theory/$i" ; done`

#================================================================================


EOF
EOF


#Theory systematics

rm -f ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_10_nominal.root

hadd \
    ${string_path}/trees_and_hist/Theory/h026_mc16a_h026_mc16d_h026_mc16e_HH_non_resonant_kappa_lambda_10_nominal.root \
    \
    ${string_path}/trees_and_hist/Theory/h026_mc16a_PowhegH7_HHbbyy_cHHH10d0_nominal.root \
    ${string_path}/trees_and_hist/Theory/h026_mc16d_PowhegH7_HHbbyy_cHHH10d0_nominal.root \
    ${string_path}/trees_and_hist/Theory/h026_mc16e_PowhegH7_HHbbyy_cHHH10d0_nominal.root






bonjour
EOF
#================================================================================








#================================================================================
FIN

#JetSys1

rm -f ${string_path}/trees_and_hist/JetSys1/h025_mc16d_HH_non_resonant_kappa_lambda_01_JetSys1.root

hadd \
    ${string_path}/trees_and_hist/JetSys1/h025_mc16d_HH_non_resonant_kappa_lambda_01_JetSys1.root \
    \
    ${string_path}/trees_and_hist/JetSys1/h025_mc16d_aMCnloHwpp_hh_yybb_JetSys1.root \
    ${string_path}/trees_and_hist/JetSys1/h025_mc16d_MGH7_hh_bbyy_vbf_l1cvv1cv1_JetSys1.root
#----
#JetSys2

rm -f ${string_path}/trees_and_hist/JetSys2/h025_mc16d_HH_non_resonant_kappa_lambda_01_JetSys2.root

hadd \
    ${string_path}/trees_and_hist/JetSys2/h025_mc16d_HH_non_resonant_kappa_lambda_01_JetSys2.root \
    \
    ${string_path}/trees_and_hist/JetSys2/h025_mc16d_aMCnloHwpp_hh_yybb_JetSys2.root \
    ${string_path}/trees_and_hist/JetSys2/h025_mc16d_MGH7_hh_bbyy_vbf_l1cvv1cv1_JetSys2.root
#----
#JetSys3

rm -f ${string_path}/trees_and_hist/JetSys3/h025_mc16d_HH_non_resonant_kappa_lambda_01_JetSys3.root

hadd \
    ${string_path}/trees_and_hist/JetSys3/h025_mc16d_HH_non_resonant_kappa_lambda_01_JetSys3.root \
    \
    ${string_path}/trees_and_hist/JetSys3/h025_mc16d_aMCnloHwpp_hh_yybb_JetSys3.root \
    ${string_path}/trees_and_hist/JetSys3/h025_mc16d_MGH7_hh_bbyy_vbf_l1cvv1cv1_JetSys3.root
#----
#JetSys4

rm -f ${string_path}/trees_and_hist/JetSys4/h025_mc16d_HH_non_resonant_kappa_lambda_01_JetSys4.root

hadd \
    ${string_path}/trees_and_hist/JetSys4/h025_mc16d_HH_non_resonant_kappa_lambda_01_JetSys4.root \
    \
    ${string_path}/trees_and_hist/JetSys4/h025_mc16d_aMCnloHwpp_hh_yybb_JetSys4.root \
    ${string_path}/trees_and_hist/JetSys4/h025_mc16d_MGH7_hh_bbyy_vbf_l1cvv1cv1_JetSys4.root
#----
#FlavorSys

rm -f ${string_path}/trees_and_hist/FlavorSys/h025_mc16d_HH_non_resonant_kappa_lambda_01_FlavorSys.root

hadd \
    ${string_path}/trees_and_hist/FlavorSys/h025_mc16d_HH_non_resonant_kappa_lambda_01_FlavorSys.root \
    \
    ${string_path}/trees_and_hist/FlavorSys/h025_mc16d_aMCnloHwpp_hh_yybb_FlavorSys.root \
    ${string_path}/trees_and_hist/FlavorSys/h025_mc16d_MGH7_hh_bbyy_vbf_l1cvv1cv1_FlavorSys.root
#================================================================================








#h025

#================================================================================
