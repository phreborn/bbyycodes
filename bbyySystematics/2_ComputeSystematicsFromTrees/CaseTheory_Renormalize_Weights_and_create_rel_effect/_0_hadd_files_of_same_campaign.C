int _0_hadd_files_of_same_campaign()
{
cout << "do hadd of same files of a same campaign" << endl;
return 0;
}

#check that there is no .root file, else you will delete it

export string_path=/sps/atlas/e/escalier/ATLAS_HGam/Outputs_syst_yield_shape/trees_and_hist/subjobs/to_correct_weights/Theory

#----------------------------
#ggH

#mc16a
rm -f ${string_path}/h026_mc16a_PowhegPy8_NNLOPS_ggH125_PhotonSys.root
mylist=( `ls ${string_path}/ | grep h026 |grep ggH |grep mc16a` )
hadd ${string_path}/h026_mc16a_PowhegPy8_NNLOPS_ggH125_PhotonSys.root `for i in $mylist ; do echo "${string_path}/$i" ; done`

#mc16d
rm -f ${string_path}/h026_mc16d_PowhegPy8_NNLOPS_ggH125_PhotonSys.root
mylist=( `ls ${string_path}/ | grep h026 |grep ggH |grep mc16d` )
hadd ${string_path}/h026_mc16d_PowhegPy8_NNLOPS_ggH125_PhotonSys.root `for i in $mylist ; do echo "${string_path}/$i" ; done`

#mc16e
rm -f ${string_path}/h026_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys.root
mylist=( `ls ${string_path}/ | grep h026 |grep ggH |grep mc16e` )
hadd ${string_path}/h026_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys.root `for i in $mylist ; do echo "${string_path}/$i" ; done`
#----------------------------
#ZH : merge the ZH125J, since the other is a single file

#mc16a
rm -f ${string_path}/h026_mc16a_PowhegPy8_ZH125J_PhotonSys.root
mylist=( `ls ${string_path}/ | grep h026 |grep _ZH125J |grep mc16a` )
hadd ${string_path}/h026_mc16a_PowhegPy8_ZH125J_PhotonSys.root `for i in $mylist ; do echo "${string_path}/$i" ; done`

#mc16d
rm -f ${string_path}/h026_mc16d_PowhegPy8_ZH125J_PhotonSys.root
mylist=( `ls ${string_path}/ | grep h026 |grep _ZH125J |grep mc16d` )
hadd ${string_path}/h026_mc16d_PowhegPy8_ZH125J_PhotonSys.root `for i in $mylist ; do echo "${string_path}/$i" ; done`

#mc16e
rm -f ${string_path}/h026_mc16e_PowhegPy8_ZH125J_PhotonSys.root
mylist=( `ls ${string_path}/ | grep h026 |grep _ZH125J |grep mc16e` )
hadd ${string_path}/h026_mc16e_PowhegPy8_ZH125J_PhotonSys.root `for i in $mylist ; do echo "${string_path}/$i" ; done`
#----------------------------
#ttH

#mc16a
rm -f ${string_path}/h026_mc16a_PowhegPy8_ttH125_fixweight_PhotonSys.root
mylist=( `ls ${string_path}/ | grep h026 |grep ttH125 |grep mc16a` )
hadd ${string_path}/h026_mc16a_PowhegPy8_ttH125_fixweight_PhotonSys.root `for i in $mylist ; do echo "${string_path}/$i" ; done`

#mc16d
rm -f ${string_path}/h026_mc16d_PowhegPy8_ttH125_fixweight_PhotonSys.root
mylist=( `ls ${string_path}/ | grep h026 |grep ttH125 |grep mc16d` )
hadd ${string_path}/h026_mc16d_PowhegPy8_ttH125_fixweight_PhotonSys.root `for i in $mylist ; do echo "${string_path}/$i" ; done`

#mc16e
rm -f ${string_path}/h026_mc16e_PowhegPy8_ttH125_fixweight_PhotonSys.root
mylist=( `ls ${string_path}/ | grep h026 |grep ttH125 |grep mc16d` )
hadd ${string_path}/h026_mc16e_PowhegPy8_ttH125_fixweight_PhotonSys.root `for i in $mylist ; do echo "${string_path}/$i" ; done`
#----------------------------
#----------------------------
#----------------------------
#----------------------------
#----------------------------


#================================================
#================================================
#================================================

#HH : already one file per campaign, so no need

#1-H : to do

#ggH
rm -f h026_mc16a_PowhegPy8_NNLOPS_ggH125_PhotonSys.root
hadd h026_mc16a_PowhegPy8_NNLOPS_ggH125_PhotonSys.root h026_mc16a_PowhegPy8_NNLOPS_ggH125_PhotonSys_1.root h026_mc16a_PowhegPy8_NNLOPS_ggH125_PhotonSys_2.root h026_mc16a_PowhegPy8_NNLOPS_ggH125_PhotonSys_3.root h026_mc16a_PowhegPy8_NNLOPS_ggH125_PhotonSys_4.root

rm -f h026_mc16d_PowhegPy8_NNLOPS_ggH125_PhotonSys.root
hadd h026_mc16d_PowhegPy8_NNLOPS_ggH125_PhotonSys.root h026_mc16d_PowhegPy8_NNLOPS_ggH125_PhotonSys_1.root h026_mc16d_PowhegPy8_NNLOPS_ggH125_PhotonSys_2.root h026_mc16d_PowhegPy8_NNLOPS_ggH125_PhotonSys_3.root

rm -f h026_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys.root
hadd h026_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys.root h026_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys_1.root h026_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys_2.root h026_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys_3.root h026_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys_4.root h026_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys_5.root h026_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys_6.root h026_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys_7.root
#-----
#ZH
#no need : single files

#-----
#ttH

rm -f h026_mc16a_PowhegPy8_ttH125_fixweight_PhotonSys.root
hadd h026_mc16a_PowhegPy8_ttH125_fixweight_PhotonSys.root h026_mc16a_PowhegPy8_ttH125_fixweight_PhotonSys_1.root h026_mc16a_PowhegPy8_ttH125_fixweight_PhotonSys_2.root

rm -f h026_mc16d_PowhegPy8_ttH125_fixweight_PhotonSys.root
hadd h026_mc16d_PowhegPy8_ttH125_fixweight_PhotonSys.root h026_mc16d_PowhegPy8_ttH125_fixweight_PhotonSys_1.root h026_mc16d_PowhegPy8_ttH125_fixweight_PhotonSys_2.root

rm -f h026_mc16e_PowhegPy8_ttH125_fixweight_PhotonSys.root
hadd h026_mc16e_PowhegPy8_ttH125_fixweight_PhotonSys.root h026_mc16e_PowhegPy8_ttH125_fixweight_PhotonSys_1.root h026_mc16e_PowhegPy8_ttH125_fixweight_PhotonSys_2.root h026_mc16e_PowhegPy8_ttH125_fixweight_PhotonSys_3.root


exit(1)

//Do the Hadd of below in the directory
//subjobs/to_correct_weights/Theory
//do the merging per campaign : by all mean, do not merge the various campaigns (mc16a, mc16d, mc16e) here, since one need afterwards to run the next program, in order to rescale in an appropriate way

rm -f h025_mc16a_PowhegPy8_NNLOPS_ggH125_PhotonSys.root
hadd h025_mc16a_PowhegPy8_NNLOPS_ggH125_PhotonSys.root h025_mc16a_PowhegPy8_NNLOPS_ggH125_PhotonSys_1.root h025_mc16a_PowhegPy8_NNLOPS_ggH125_PhotonSys_2.root h025_mc16a_PowhegPy8_NNLOPS_ggH125_PhotonSys_3.root h025_mc16a_PowhegPy8_NNLOPS_ggH125_PhotonSys_4.root h025_mc16a_PowhegPy8_NNLOPS_ggH125_PhotonSys_5.root

rm -f h025_mc16d_PowhegPy8_NNLOPS_ggH125_PhotonSys.root
hadd h025_mc16d_PowhegPy8_NNLOPS_ggH125_PhotonSys.root h025_mc16d_PowhegPy8_NNLOPS_ggH125_PhotonSys_1.root h025_mc16d_PowhegPy8_NNLOPS_ggH125_PhotonSys_2.root h025_mc16d_PowhegPy8_NNLOPS_ggH125_PhotonSys_3.root h025_mc16d_PowhegPy8_NNLOPS_ggH125_PhotonSys_4.root

ls *ggH* |grep mc16e
rm -f tree_h025_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys.root
hadd h025_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys.root h025_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys_1.root h025_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys_2.root h025_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys_3.root h025_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys_4.root h025_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys_5.root h025_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys_6.root

rm -f h025_mc16a_PowhegPy8_ttH125_fixweight_PhotonSys.root
hadd h025_mc16a_PowhegPy8_ttH125_fixweight_PhotonSys.root h025_mc16a_PowhegPy8_ttH125_fixweight_PhotonSys_1.root h025_mc16a_PowhegPy8_ttH125_fixweight_PhotonSys_2.root h025_mc16a_PowhegPy8_ttH125_fixweight_PhotonSys_3.root

rm -f h025_mc16d_PowhegPy8_ttH125_fixweight_PhotonSys.root
hadd h025_mc16d_PowhegPy8_ttH125_fixweight_PhotonSys.root h025_mc16d_PowhegPy8_ttH125_fixweight_PhotonSys_1.root h025_mc16d_PowhegPy8_ttH125_fixweight_PhotonSys_2.root h025_mc16d_PowhegPy8_ttH125_fixweight_PhotonSys_3.root

rm -f h025_mc16e_PowhegPy8_ttH125_fixweight_PhotonSys.root
hadd h025_mc16e_PowhegPy8_ttH125_fixweight_PhotonSys.root h025_mc16e_PowhegPy8_ttH125_fixweight_PhotonSys_1.root h025_mc16e_PowhegPy8_ttH125_fixweight_PhotonSys_2.root h025_mc16e_PowhegPy8_ttH125_fixweight_PhotonSys_3.root






=================================
OLD
rm h025_mc16a_PhotonSys_PowhegPy8_NNLOPS_ggH125.root
hadd h025_mc16a_PhotonSys_PowhegPy8_NNLOPS_ggH125.root h025_mc16a_PhotonSys_PowhegPy8_NNLOPS_ggH125_1.root h025_mc16a_PhotonSys_PowhegPy8_NNLOPS_ggH125_2.root h025_mc16a_PhotonSys_PowhegPy8_NNLOPS_ggH125_3.root h025_mc16a_PhotonSys_PowhegPy8_NNLOPS_ggH125_4.root h025_mc16a_PhotonSys_PowhegPy8_NNLOPS_ggH125_5.root

ls *ggH* |grep mc16d
rm h025_mc16d_PhotonSys_PowhegPy8_NNLOPS_ggH125.root
hadd h025_mc16d_PhotonSys_PowhegPy8_NNLOPS_ggH125.root h025_mc16d_PhotonSys_PowhegPy8_NNLOPS_ggH125_1.root h025_mc16d_PhotonSys_PowhegPy8_NNLOPS_ggH125_2.root h025_mc16d_PhotonSys_PowhegPy8_NNLOPS_ggH125_3.root h025_mc16d_PhotonSys_PowhegPy8_NNLOPS_ggH125_4.root
ls *ggH* |grep mc16e
rm tree_h025_mc16e_PhotonSys_PowhegPy8_NNLOPS_ggH125.root
hadd h025_mc16e_PhotonSys_PowhegPy8_NNLOPS_ggH125.root h025_mc16e_PhotonSys_PowhegPy8_NNLOPS_ggH125_1.root h025_mc16e_PhotonSys_PowhegPy8_NNLOPS_ggH125_2.root h025_mc16e_PhotonSys_PowhegPy8_NNLOPS_ggH125_3.root h025_mc16e_PhotonSys_PowhegPy8_NNLOPS_ggH125_4.root h025_mc16e_PhotonSys_PowhegPy8_NNLOPS_ggH125_5.root h025_mc16e_PhotonSys_PowhegPy8_NNLOPS_ggH125_6.root




rm h025_mc16a_PhotonSys_PowhegPy8_ttH125_fixweight.root
hadd h025_mc16a_PhotonSys_PowhegPy8_ttH125_fixweight.root h025_mc16a_PhotonSys_PowhegPy8_ttH125_fixweight_1.root h025_mc16a_PhotonSys_PowhegPy8_ttH125_fixweight_2.root h025_mc16a_PhotonSys_PowhegPy8_ttH125_fixweight_3.root

rm h025_mc16d_PhotonSys_PowhegPy8_ttH125_fixweight.root
hadd h025_mc16d_PhotonSys_PowhegPy8_ttH125_fixweight.root h025_mc16d_PhotonSys_PowhegPy8_ttH125_fixweight_1.root h025_mc16d_PhotonSys_PowhegPy8_ttH125_fixweight_2.root h025_mc16d_PhotonSys_PowhegPy8_ttH125_fixweight_3.root

rm h025_mc16e_PhotonSys_PowhegPy8_ttH125_fixweight.root
hadd h025_mc16e_PhotonSys_PowhegPy8_ttH125_fixweight.root h025_mc16e_PhotonSys_PowhegPy8_ttH125_fixweight_1.root h025_mc16e_PhotonSys_PowhegPy8_ttH125_fixweight_2.root h025_mc16e_PhotonSys_PowhegPy8_ttH125_fixweight_3.root

