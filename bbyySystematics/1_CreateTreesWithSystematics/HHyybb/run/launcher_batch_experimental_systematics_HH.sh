#================================================
#important : one should have compiled the program first

#===================================================================================================================================
#function that will be called by various configurations
function_name()
{
    CurrentScript=/sps/atlas/e/escalier/scratch/script_ExperimSystematics.${current_sample}

    echo "dealing with sample : ${current_sample}"
    
    echo "echo BEGINBEGINBEGINBEGINBEGINBEGINBEGINBEGINBEGINBEGIN" > ${CurrentScript}
    echo "date" >> ${CurrentScript}
    echo "cd /pbs/home/e/escalier" >> ${CurrentScript}

    echo "echo phase A" >> ${CurrentScript}
    echo "echo $PATH" >> ${CurrentScript}
    echo "echo $LD_LIBRARY_PATH" >> ${CurrentScript}

    echo "export KRB5_CONFIG=/pbs/home/e/escalier/private/krb5.conf" >> ${CurrentScript}
    echo "kinit -k -t /pbs/home/e/escalier/private/ThePassword.keytab escalier@CERN.CH" >> ${CurrentScript}
    echo "aklog -c CERN.CH -k CERN.CH" >> ${CurrentScript}
    echo "echo Shell Used is " >> ${CurrentScript}
    echo "echo $SHELL" >> ${CurrentScript}
    echo "pwd" >> ${CurrentScript}
#by all means, do not do source setuATLAS because buggy    echo "source setupATLAS" >> ${CurrentScript}
    echo "export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase" >> ${CurrentScript}
    echo "source $ATLAS_LOCAL_ROOT_BASE/user/atlasLocalSetup.sh" >> ${CurrentScript}

    echo "echo phase 2" >> ${CurrentScript}
    echo "echo phase try new instruction" >> ${CurrentScript}

    echo "print phase 1, which root" >> ${CurrentScript}
    echo "which root" >> ${CurrentScript}
    echo "print phase 1, which xrootd" >> ${CurrentScript}
    echo "which xrootd" >> ${CurrentScript}

    echo "print phase 2, which root" >> ${CurrentScript}
    echo "which root" >> ${CurrentScript}
    echo "print phase 2, which xrootd" >> ${CurrentScript}
    echo "which xrootd" >> ${CurrentScript}

    #go in directory of program and configure
    echo "cd /sps/atlas/e/escalier/ATLAS_HGam/Framework_h026/source/" >> ${CurrentScript}
    echo "echo phase 3" >> ${CurrentScript}
    echo "pwd" >> ${CurrentScript}

    echo "echo phase B" >> ${CurrentScript}
    echo "echo $PATH" >> ${CurrentScript}
    echo "echo $LD_LIBRARY_PATH" >> ${CurrentScript}

    echo "echo $PATH" >> ${CurrentScript}

    echo "asetup AnalysisBase,21.2.131,here" >> ${CurrentScript}
    
    echo "echo phase C" >> ${CurrentScript}
    echo "echo $PATH" >> ${CurrentScript}
    echo "echo $LD_LIBRARY_PATH" >> ${CurrentScript}

#  echo "cd ../build" >> ${CurrentScript}
#  echo "cmake ../source" >> ${CurrentScript}
    echo "pwd" >> ${CurrentScript}
#no need to compile ?    echo "cmake --build ." >> ${CurrentScript}
    
    echo "echo TestArea is :" >> ${CurrentScript}
    echo "echo $TestArea" >> ${CurrentScript}
    echo "echo next command decoding is : $TestArea/../build/$AnalysisBase_PLATFORM/setup.sh" >> ${CurrentScript}
    echo "source $TestArea/../build/$AnalysisBase_PLATFORM/setup.sh" >> ${CurrentScript}
    echo "echo explicite command juste in case" >> ${CurrentScript}
    echo "source /cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBaseExternals/21.2.131/InstallArea/x86_64-centos7-gcc8-opt/setup.sh" >> ${CurrentScript}
    echo "cd ../run" >> ${CurrentScript}
    echo "pwd" >> ${CurrentScript}


    echo "print phase 9, which root" >> ${CurrentScript}
    echo "which root" >> ${CurrentScript}
    echo "print phase 9, which xrootd" >> ${CurrentScript}
    echo "which xrootd" >> ${CurrentScript}


    echo "print phase 10, which root" >> ${CurrentScript}
    echo "which root" >> ${CurrentScript}
    echo "print phase 10, which xrootd" >> ${CurrentScript}
    echo "which xrootd" >> ${CurrentScript}
    echo "echo $PATH" >> ${CurrentScript}
    echo "echo $DATAPATH" >> ${CurrentScript}

  #initialization of GRID
  #echo "voms-proxy-init -voms atlas -pwstdin < /afs/in2p3.fr/home/e/escalier/private/.pas" >> ${CurrentScript}
    
    echo "echo phase D" >> ${CurrentScript}
    echo "echo $PATH" >> ${CurrentScript}
    echo "echo $LD_LIBRARY_PATH" >> ${CurrentScript}

    echo "echo phase SETUP2" >> ${CurrentScript}
    echo "export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase" >> ${CurrentScript}
    echo "source $ATLAS_LOCAL_ROOT_BASE/user/atlasLocalSetup.sh" >> ${CurrentScript}

    echo "echo StartProgNow for ${current_sample}" >> ${CurrentScript}
    
    echo "runtool_Experimental_Systematics InputFileList: /sps/atlas/e/escalier/ATLAS_HGam/txt_MxAODs/Systematics/${current_sample}.sh SampleName: ${current_sample} OutputDir: tool_Experimental_Systematics_${current_sample} HHyybb/tool_Experimental_Systematics_$1_h026.config" >> ${CurrentScript}
    
#good one
    qsub -P P_atlas -m e -M escalier@lal.in2p3.fr -l h_cpu=40:00:00 -l vmem=4G,fsize=4G,sps=1 -N j_exp.${current_sample} -o /sps/atlas/e/escalier/scratch/Log_exp_sys_HH_${current_sample}.OU -e /sps/atlas/e/escalier/scratch/Log_exp_sys_HH_${current_sample}.ER ${CurrentScript}

#    qsub -P P_atlas -m e -M escalier@lal.in2p3.fr -l h_cpu=22:00:00 -l vmem=4G,fsize=4G,sps=1 -N j_exp.${current_sample} -o /sps/atlas/e/escalier/scratch/Log_exp_sys_HH_${current_sample}.OU -e /sps/atlas/e/escalier/scratch/Log_exp_sys_HH_${current_sample}.ER ${CurrentScript}

#to improve with correct flags, and forcing queue long

    #cat ${CurrentScript}

    #sleep 60
}

#=================================================================================================================================
#Don't forget to delete old directories in the run directory
#=================================================================================================================================

export do_gg_HH_non_resonant_kappa_lambda_01="false"
export do_HH_non_resonant_kappa_lambda_10="false"

export do_vbf_HH_non_resonant_kappa_lambda_01="false"

export do_ggH="false"
export do_ZH="false"
export do_ttH="false"

export do_HH_resonant="true"

#for current_sample in testForAnthony_PhotonSys 
#function_name PhotonSys
#exit(1)

# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
if [ ${do_gg_HH_non_resonant_kappa_lambda_01} = "true" ]
    then

#=====================
#Py8

#---------------
#PhotonSys
#    for current_sample in h026_mc16a_PowhegPy8_HHbbyy_cHHH01d0_PhotonSys h026_mc16d_PowhegPy8_HHbbyy_cHHH01d0_PhotonSys h026_mc16e_PowhegPy8_HHbbyy_cHHH01d0_PhotonSys h026_mc16a_PowhegPy8_HHbbyy_cHHH10d0_PhotonSys h026_mc16d_PowhegPy8_HHbbyy_cHHH10d0_PhotonSys h026_mc16e_PowhegPy8_HHbbyy_cHHH10d0_PhotonSys
#    function_name PhotonSys
#---------------
#JetSys1
#    for current_sample in h026_mc16a_PowhegPy8_HHbbyy_cHHH01d0_JetSys1 h026_mc16d_PowhegPy8_HHbbyy_cHHH01d0_JetSys1 h026_mc16e_PowhegPy8_HHbbyy_cHHH01d0_JetSys1 h026_mc16a_PowhegPy8_HHbbyy_cHHH10d0_JetSys1 h026_mc16d_PowhegPy8_HHbbyy_cHHH10d0_JetSys1 h026_mc16e_PowhegPy8_HHbbyy_cHHH10d0_JetSys1
#    function_name JetSys1

#    for current_sample in h026_mc16d_PowhegPy8_HHbbyy_cHHH01d0_JetSys1 h026_mc16e_PowhegPy8_HHbbyy_cHHH01d0_JetSys1
#    function_name JetSys1

exit(1)

#---------------
#JetSys2
    for current_sample in h026_mc16a_PowhegPy8_HHbbyy_cHHH01d0_JetSys2 h026_mc16d_PowhegPy8_HHbbyy_cHHH01d0_JetSys2 h026_mc16e_PowhegPy8_HHbbyy_cHHH01d0_JetSys2 h026_mc16a_PowhegPy8_HHbbyy_cHHH10d0_JetSys2 h026_mc16d_PowhegPy8_HHbbyy_cHHH10d0_JetSys2 h026_mc16e_PowhegPy8_HHbbyy_cHHH10d0_JetSys2
    function_name JetSys2
#---------------
#JetSys3
    for current_sample in h026_mc16a_PowhegPy8_HHbbyy_cHHH01d0_JetSys3 h026_mc16d_PowhegPy8_HHbbyy_cHHH01d0_JetSys3 h026_mc16e_PowhegPy8_HHbbyy_cHHH01d0_JetSys3 h026_mc16a_PowhegPy8_HHbbyy_cHHH10d0_JetSys3 h026_mc16d_PowhegPy8_HHbbyy_cHHH10d0_JetSys3 h026_mc16e_PowhegPy8_HHbbyy_cHHH10d0_JetSys3
    function_name JetSys3
#---------------
#JetSys4
    for current_sample in h026_mc16a_PowhegPy8_HHbbyy_cHHH01d0_JetSys4 h026_mc16d_PowhegPy8_HHbbyy_cHHH01d0_JetSys4 h026_mc16e_PowhegPy8_HHbbyy_cHHH01d0_JetSys4 h026_mc16a_PowhegPy8_HHbbyy_cHHH10d0_JetSys4 h026_mc16d_PowhegPy8_HHbbyy_cHHH10d0_JetSys4 h026_mc16e_PowhegPy8_HHbbyy_cHHH10d0_JetSys4
function_name JetSys4    
#---------------
#FlavorSys
    for current_sample in h026_mc16a_PowhegPy8_HHbbyy_cHHH01d0_FlavorSys h026_mc16d_PowhegPy8_HHbbyy_cHHH01d0_FlavorSys h026_mc16e_PowhegPy8_HHbbyy_cHHH01d0_FlavorSys h026_mc16a_PowhegPy8_HHbbyy_cHHH10d0_FlavorSys h026_mc16d_PowhegPy8_HHbbyy_cHHH10d0_FlavorSys h026_mc16e_PowhegPy8_HHbbyy_cHHH10d0_FlavorSys
    function_name FlavorSys
#---------------
#LeptonMETSys
#for current_sample in 
#function_name LeptonMETSys
#---------------
#=====================
#H7

#---------------
#PhotonSys    
#    for current_sample in h026_mc16a_PowhegH7_HHbbyy_cHHH01d0_PhotonSys h026_mc16d_PowhegH7_HHbbyy_cHHH01d0_PhotonSys h026_mc16e_PowhegH7_HHbbyy_cHHH01d0_PhotonSys 
#    function_name PhotonSys
#---------------
#JetSys1
#    for current_sample in h026_mc16a_PowhegH7_HHbbyy_cHHH01d0_JetSys1 h026_mc16d_PowhegH7_HHbbyy_cHHH01d0_JetSys1 h026_mc16e_PowhegH7_HHbbyy_cHHH01d0_JetSys1
#    function_name JetSys1
#---------------
#JetSys2
#    for current_sample in h026_mc16a_PowhegH7_HHbbyy_cHHH01d0_JetSys2 h026_mc16d_PowhegH7_HHbbyy_cHHH01d0_JetSys2
#    function_name JetSys2
#---------------
#JetSys3
#    for current_sample in h026_mc16a_PowhegH7_HHbbyy_cHHH01d0_JetSys3 h026_mc16d_PowhegH7_HHbbyy_cHHH01d0_JetSys3
#    function_name JetSys3
#---------------
#JetSys4
#    for current_sample in h026_mc16d_PowhegH7_HHbbyy_cHHH01d0_JetSys4 h026_mc16e_PowhegH7_HHbbyy_cHHH01d0_JetSys4
#    function_name JetSys4    
#---------------
#FlavorSys
#    for current_sample in h026_mc16a_PowhegH7_HHbbyy_cHHH01d0_FlavorSys h026_mc16d_PowhegH7_HHbbyy_cHHH01d0_FlavorSys h026_mc16e_PowhegH7_HHbbyy_cHHH01d0_FlavorSys
#    function_name FlavorSys
#---------------
#LeptonMETSys
#for current_sample in h026_mc16a_PowhegH7_HHbbyy_cHHH01d0_LeptonMETSys h026_mc16e_PowhegH7_HHbbyy_cHHH01d0_LeptonMETSys_1 h026_mc16e_PowhegH7_HHbbyy_cHHH01d0_LeptonMETSys_2 h026_mc16d_PowhegH7_HHbbyy_cHHH01d0_LeptonMETSys
#function_name LeptonMETSys
#---------------
#=====================
fi
# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
if [ ${do_HH_non_resonant_kappa_lambda_10} = "true" ]
    then
#---------------
#PhotonSys
    for current_sample in h026_mc16a_PowhegH7_HHbbyy_cHHH10d0_PhotonSys h026_mc16d_PowhegH7_HHbbyy_cHHH10d0_PhotonSys h026_mc16e_PowhegH7_HHbbyy_cHHH10d0_PhotonSys
    function_name PhotonSys
#---------------
#JetSys1
    for current_sample in h026_mc16a_PowhegH7_HHbbyy_cHHH10d0_JetSys1 h026_mc16d_PowhegH7_HHbbyy_cHHH10d0_JetSys1 h026_mc16e_PowhegH7_HHbbyy_cHHH10d0_JetSys1
    function_name JetSys1
#---------------
#JetSys2
    for current_sample in h026_mc16a_PowhegH7_HHbbyy_cHHH10d0_JetSys2 h026_mc16d_PowhegH7_HHbbyy_cHHH10d0_JetSys2
    function_name JetSys2
#---------------
#JetSys3
    for current_sample in h026_mc16a_PowhegH7_HHbbyy_cHHH10d0_JetSys3 h026_mc16d_PowhegH7_HHbbyy_cHHH10d0_JetSys3
    function_name JetSys3
#---------------
#JetSys4
    for current_sample in h026_mc16a_PowhegH7_HHbbyy_cHHH10d0_JetSys4 h026_mc16d_PowhegH7_HHbbyy_cHHH10d0_JetSys4 h026_mc16e_PowhegH7_HHbbyy_cHHH10d0_JetSys4
    function_name JetSys4
#---------------
#FlavorSys
    for current_sample in h026_mc16a_PowhegH7_HHbbyy_cHHH10d0_FlavorSys h026_mc16d_PowhegH7_HHbbyy_cHHH10d0_FlavorSys h026_mc16e_PowhegH7_HHbbyy_cHHH10d0_FlavorSys
    function_name FlavorSys
#---------------
#LeptonMETSys
#for current_sample in h026_mc16a_PowhegH7_HHbbyy_cHHH10d0_LeptonMETSys h026_mc16d_PowhegH7_HHbbyy_cHHH10d0_LeptonMETSys h026_mc16e_PowhegH7_HHbbyy_cHHH10d0_LeptonMETSys
#function_name LeptonMETSys
#---------------
fi
# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
#should use MGPy8, because the MGH7 contains VH events, even if it does not pass the selection, it is better to use Py8
if [ ${do_vbf_HH_non_resonant_kappa_lambda_01} = "true" ]
    then
#---------------
#PhotonSys    
    for current_sample in h026_mc16a_MGPy8_hh_bbyy_vbf_l1cvv1cv1_PhotonSys h026_mc16d_MGPy8_hh_bbyy_vbf_l1cvv1cv1_PhotonSys h026_mc16e_MGPy8_hh_bbyy_vbf_l1cvv1cv1_PhotonSys
    function_name PhotonSys
#---------------
#JetSys1
    for current_sample in h026_mc16a_MGPy8_hh_bbyy_vbf_l1cvv1cv1_JetSys1 h026_mc16d_MGPy8_hh_bbyy_vbf_l1cvv1cv1_JetSys1 h026_mc16e_MGPy8_hh_bbyy_vbf_l1cvv1cv1_JetSys1
    function_name JetSys1
#---------------
#JetSys2
    for current_sample in h026_mc16a_MGPy8_hh_bbyy_vbf_l1cvv1cv1_JetSys2 h026_mc16d_MGPy8_hh_bbyy_vbf_l1cvv1cv1_JetSys2
    function_name JetSys2
#---------------
#JetSys3
    for current_sample in h026_mc16a_MGPy8_hh_bbyy_vbf_l1cvv1cv1_JetSys3 h026_mc16e_MGPy8_hh_bbyy_vbf_l1cvv1cv1_JetSys3
    function_name JetSys3
#---------------
#JetSys4
    for current_sample in h026_mc16a_MGPy8_hh_bbyy_vbf_l1cvv1cv1_JetSys4 h026_mc16d_MGPy8_hh_bbyy_vbf_l1cvv1cv1_JetSys4 h026_mc16e_MGPy8_hh_bbyy_vbf_l1cvv1cv1_JetSys4
    function_name JetSys4
#---------------
#FlavorSys
    for current_sample in h026_mc16a_MGPy8_hh_bbyy_vbf_l1cvv1cv1_FlavorSys h026_mc16d_MGPy8_hh_bbyy_vbf_l1cvv1cv1_FlavorSys h026_mc16e_MGPy8_hh_bbyy_vbf_l1cvv1cv1_FlavorSys
    function_name FlavorSys
#---------------



fi
# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
if [ ${do_ggH} = "true" ]
    then
#---------------
#PhotonSys
#    for current_sample in h026_mc16a_PowhegPy8_NNLOPS_ggH125_PhotonSys_1 h026_mc16a_PowhegPy8_NNLOPS_ggH125_PhotonSys_2 h026_mc16a_PowhegPy8_NNLOPS_ggH125_PhotonSys_3 h026_mc16d_PowhegPy8_NNLOPS_ggH125_PhotonSys_1 h026_mc16d_PowhegPy8_NNLOPS_ggH125_PhotonSys_2 h026_mc16d_PowhegPy8_NNLOPS_ggH125_PhotonSys_3 h026_mc16d_PowhegPy8_NNLOPS_ggH125_PhotonSys_4 h026_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys_1 h026_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys_2 h026_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys_3 h026_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys_4 h026_mc16e_PowhegPy8_NNLOPS_ggH125_PhotonSys_5
#    function_name PhotonSys
#---------------
#JetSys1
#    for current_sample in h026_mc16a_PowhegPy8_NNLOPS_ggH125_JetSys1_1 h026_mc16a_PowhegPy8_NNLOPS_ggH125_JetSys1_2 h026_mc16a_PowhegPy8_NNLOPS_ggH125_JetSys1_3 h026_mc16a_PowhegPy8_NNLOPS_ggH125_JetSys1_4 h026_mc16a_PowhegPy8_NNLOPS_ggH125_JetSys1_5 h026_mc16a_PowhegPy8_NNLOPS_ggH125_JetSys1_6 h026_mc16a_PowhegPy8_NNLOPS_ggH125_JetSys1_7 h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys1_1 h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys1_2 h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys1_3 h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys1_4 h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys1_5 h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys1_6 h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys1_7 h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys1_8 h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys1_9 h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys1_10 h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys1_11 h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys1_12 h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys1_13 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys1_1 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys1_2 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys1_3 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys1_4 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys1_5 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys1_6 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys1_7 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys1_8 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys1_9
#    function_name JetSys1
#---------------
#JetSys2
#    for current_sample in h026_mc16a_PowhegPy8_NNLOPS_ggH125_JetSys2_1 h026_mc16a_PowhegPy8_NNLOPS_ggH125_JetSys2_2 h026_mc16a_PowhegPy8_NNLOPS_ggH125_JetSys2_3 h026_mc16a_PowhegPy8_NNLOPS_ggH125_JetSys2_4 h026_mc16a_PowhegPy8_NNLOPS_ggH125_JetSys2_5 h026_mc16a_PowhegPy8_NNLOPS_ggH125_JetSys2_6 h026_mc16a_PowhegPy8_NNLOPS_ggH125_JetSys2_7 h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys2_1 h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys2_2 h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys2_3 h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys2_4 h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys2_5 h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys2_6 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys2_1 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys2_2 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys2_3 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys2_4 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys2_5 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys2_6 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys2_7 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys2_8 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys2_9 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys2_10 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys2_11 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys2_12 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys2_13 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys2_14 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys2_15
#    function_name JetSys2
#---------------
#JetSys3
#    for current_sample in h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys3_1 h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys3_2 h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys3_3 h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys3_4 h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys3_5
#    function_name JetSys3

    for current_sample in h026_mc16a_PowhegPy8_NNLOPS_ggH125_JetSys3_1 h026_mc16a_PowhegPy8_NNLOPS_ggH125_JetSys3_2 h026_mc16a_PowhegPy8_NNLOPS_ggH125_JetSys3_3 h026_mc16a_PowhegPy8_NNLOPS_ggH125_JetSys3_4 h026_mc16a_PowhegPy8_NNLOPS_ggH125_JetSys3_5 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys3_1 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys3_2 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys3_3 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys3_4 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys3_5 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys3_6 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys3_7 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys3_8 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys3_9
    function_name JetSys3
#---------------
#JetSys4
#    for current_sample in h026_mc16a_PowhegPy8_NNLOPS_ggH125_JetSys4_1 h026_mc16a_PowhegPy8_NNLOPS_ggH125_JetSys4_2 h026_mc16a_PowhegPy8_NNLOPS_ggH125_JetSys4_3 h026_mc16a_PowhegPy8_NNLOPS_ggH125_JetSys4_4 h026_mc16a_PowhegPy8_NNLOPS_ggH125_JetSys4_5 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys4_1 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys4_2 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys4_3 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys4_4 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys4_5 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys4_6 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys4_7 h026_mc16e_PowhegPy8_NNLOPS_ggH125_JetSys4_8
#    function_name JetSys4    
#    for current_sample in h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys4_1 h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys4_2 h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys4_3 h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys4_4 h026_mc16d_PowhegPy8_NNLOPS_ggH125_JetSys4_5
#    function_name JetSys4
#---------------
#FlavorSys
#    for current_sample in h026_mc16a_PowhegPy8_NNLOPS_ggH125_FlavorSys_1 h026_mc16a_PowhegPy8_NNLOPS_ggH125_FlavorSys_2 h026_mc16a_PowhegPy8_NNLOPS_ggH125_FlavorSys_3 h026_mc16a_PowhegPy8_NNLOPS_ggH125_FlavorSys_4 h026_mc16a_PowhegPy8_NNLOPS_ggH125_FlavorSys_5 h026_mc16d_PowhegPy8_NNLOPS_ggH125_FlavorSys_1 h026_mc16d_PowhegPy8_NNLOPS_ggH125_FlavorSys_2 h026_mc16d_PowhegPy8_NNLOPS_ggH125_FlavorSys_3 h026_mc16d_PowhegPy8_NNLOPS_ggH125_FlavorSys_4 h026_mc16d_PowhegPy8_NNLOPS_ggH125_FlavorSys_5 h026_mc16e_PowhegPy8_NNLOPS_ggH125_FlavorSys_1 h026_mc16e_PowhegPy8_NNLOPS_ggH125_FlavorSys_2 h026_mc16e_PowhegPy8_NNLOPS_ggH125_FlavorSys_3 h026_mc16e_PowhegPy8_NNLOPS_ggH125_FlavorSys_4 h026_mc16e_PowhegPy8_NNLOPS_ggH125_FlavorSys_5 h026_mc16e_PowhegPy8_NNLOPS_ggH125_FlavorSys_6 h026_mc16e_PowhegPy8_NNLOPS_ggH125_FlavorSys_7 h026_mc16e_PowhegPy8_NNLOPS_ggH125_FlavorSys_8
#    function_name FlavorSys
#---------------
#LeptonMETSys
#for current_sample in h026_mc16a_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_1 h026_mc16a_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_2 h026_mc16a_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_3 h026_mc16a_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_4 h026_mc16a_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_5 h026_mc16a_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_6 h026_mc16a_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_7 h026_mc16d_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_1 h026_mc16d_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_2 h026_mc16d_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_3 h026_mc16d_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_4 h026_mc16d_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_5 h026_mc16d_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_6 h026_mc16d_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_7 h026_mc16e_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_1 h026_mc16e_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_2 h026_mc16e_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_3 h026_mc16e_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_4 h026_mc16e_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_5 h026_mc16e_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_6 h026_mc16e_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_7 h026_mc16e_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_8 h026_mc16e_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_9 h026_mc16e_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_10 h026_mc16e_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_11 h026_mc16e_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_12 h026_mc16e_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_13 h026_mc16e_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_14 h026_mc16e_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_15 h026_mc16e_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_16 h026_mc16e_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_17 h026_mc16e_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_18 h026_mc16e_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_19 h026_mc16e_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_20 h026_mc16e_PowhegPy8_NNLOPS_ggH125_LeptonMETSys_21
#function_name LeptonMETSys
#---------------
fi
# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
if [ ${do_ZH} = "true" ]
    then
#qqZH
#---------------
#PhotonSys
#    for current_sample in h026_mc16a_PowhegPy8_ZH125J_PhotonSys_1 h026_mc16a_PowhegPy8_ZH125J_PhotonSys_2 h026_mc16d_PowhegPy8_ZH125J_PhotonSys_1 h026_mc16d_PowhegPy8_ZH125J_PhotonSys_2 h026_mc16e_PowhegPy8_ZH125J_PhotonSys_1 h026_mc16e_PowhegPy8_ZH125J_PhotonSys_2
#    function_name PhotonSys
#---------------
#JetSys1
#    for current_sample in h026_mc16a_PowhegPy8_ZH125J_JetSys1_1 h026_mc16a_PowhegPy8_ZH125J_JetSys1_2 h026_mc16a_PowhegPy8_ZH125J_JetSys1_3 h026_mc16d_PowhegPy8_ZH125J_JetSys1_1 h026_mc16d_PowhegPy8_ZH125J_JetSys1_2 h026_mc16d_PowhegPy8_ZH125J_JetSys1_3 h026_mc16e_PowhegPy8_ZH125J_JetSys1_1 h026_mc16e_PowhegPy8_ZH125J_JetSys1_2 h026_mc16e_PowhegPy8_ZH125J_JetSys1_3 h026_mc16e_PowhegPy8_ZH125J_JetSys1_4 h026_mc16e_PowhegPy8_ZH125J_JetSys1_5
#    function_name JetSys1
#---------------
#JetSys2
#    for current_sample in  h026_mc16a_PowhegPy8_ZH125J_JetSys2_1 h026_mc16a_PowhegPy8_ZH125J_JetSys2_2 h026_mc16a_PowhegPy8_ZH125J_JetSys2_3 h026_mc16d_PowhegPy8_ZH125J_JetSys2_1 h026_mc16d_PowhegPy8_ZH125J_JetSys2_2 h026_mc16d_PowhegPy8_ZH125J_JetSys2_3 h026_mc16d_PowhegPy8_ZH125J_JetSys2_4
#    function_name JetSys2

#    for current_sample in h026_mc16e_PowhegPy8_ZH125J_JetSys2_1 h026_mc16e_PowhegPy8_ZH125J_JetSys2_2 h026_mc16e_PowhegPy8_ZH125J_JetSys2_3 h026_mc16e_PowhegPy8_ZH125J_JetSys2_4 h026_mc16e_PowhegPy8_ZH125J_JetSys2_5
#    function_name JetSys2
#---------------
#JetSys3
#    for current_sample in h026_mc16d_PowhegPy8_ZH125J_JetSys3_1 h026_mc16d_PowhegPy8_ZH125J_JetSys3_2 h026_mc16d_PowhegPy8_ZH125J_JetSys3_3
#   function_name JetSys3

#    for current_sample in h026_mc16a_PowhegPy8_ZH125J_JetSys3_1 h026_mc16a_PowhegPy8_ZH125J_JetSys3_2 h026_mc16e_PowhegPy8_ZH125J_JetSys3_1 h026_mc16e_PowhegPy8_ZH125J_JetSys3_2 h026_mc16e_PowhegPy8_ZH125J_JetSys3_3 h026_mc16e_PowhegPy8_ZH125J_JetSys3_4
#    function_name JetSys3
#-------------
#JetSys4
#   for current_sample in h026_mc16a_PowhegPy8_ZH125J_JetSys4_1 h026_mc16a_PowhegPy8_ZH125J_JetSys4_2 h026_mc16e_PowhegPy8_ZH125J_JetSys4_1 h026_mc16e_PowhegPy8_ZH125J_JetSys4_2 h026_mc16e_PowhegPy8_ZH125J_JetSys4_3 h026_mc16e_PowhegPy8_ZH125J_JetSys4_4
#   function_name JetSys4

#for current_sample in h026_mc16d_PowhegPy8_ZH125J_JetSys4_1 h026_mc16d_PowhegPy8_ZH125J_JetSys4_2 h026_mc16d_PowhegPy8_ZH125J_JetSys4_3
#function_name JetSys4
#---------------
#FlavorSys
#    for current_sample in h026_mc16a_PowhegPy8_ZH125J_FlavorSys_1 h026_mc16a_PowhegPy8_ZH125J_FlavorSys_2 h026_mc16a_PowhegPy8_ZH125J_FlavorSys_3 h026_mc16d_PowhegPy8_ZH125J_FlavorSys_1 h026_mc16d_PowhegPy8_ZH125J_FlavorSys_2 h026_mc16d_PowhegPy8_ZH125J_FlavorSys_3 h026_mc16e_PowhegPy8_ZH125J_FlavorSys_1 h026_mc16e_PowhegPy8_ZH125J_FlavorSys_2 h026_mc16e_PowhegPy8_ZH125J_FlavorSys_3 h026_mc16e_PowhegPy8_ZH125J_FlavorSys_4
#    function_name FlavorSys
#---------------
#LeptonMETSys
#for current_sample in h026_mc16d_PowhegPy8_ZH125J_LeptonMETSys h026_mc16d_PowhegPy8_ggZH125_LeptonMETSys
#function_name LeptonMETSys
#---------------
#ggZH

#---------------
#PhotonSys
#    for current_sample in h026_mc16a_PowhegPy8_ggZH125_PhotonSys h026_mc16d_PowhegPy8_ggZH125_PhotonSys h026_mc16e_PowhegPy8_ggZH125_PhotonSys
#    function_name PhotonSys
#---------------
#JetSys1
#    for current_sample in h026_mc16a_PowhegPy8_ggZH125_JetSys1 h026_mc16d_PowhegPy8_ggZH125_JetSys1 h026_mc16e_PowhegPy8_ggZH125_JetSys1
#    function_name JetSys1
#---------------
#JetSys2
#    for current_sample in h026_mc16a_PowhegPy8_ggZH125_JetSys2 h026_mc16d_PowhegPy8_ggZH125_JetSys2
#    function_name JetSys2

    for current_sample in h026_mc16e_PowhegPy8_ggZH125_JetSys2
    function_name JetSys2
#---------------
#JetSys3
#    for current_sample in h026_mc16d_PowhegPy8_ggZH125_JetSys3
#    function_name JetSys3

    for current_sample in h026_mc16a_PowhegPy8_ggZH125_JetSys3 h026_mc16e_PowhegPy8_ggZH125_JetSys3
    function_name JetSys3
#---------------
#JetSys4
#    for current_sample in h026_mc16a_PowhegPy8_ggZH125_JetSys4 h026_mc16e_PowhegPy8_ggZH125_JetSys4
#    function_name JetSys4

    for current_sample in h026_mc16d_PowhegPy8_ggZH125_JetSys4
    function_name JetSys4
#---------------
#FlavorSys
#    for current_sample in h026_mc16a_PowhegPy8_ggZH125_FlavorSys h026_mc16d_PowhegPy8_ggZH125_FlavorSys h026_mc16e_PowhegPy8_ggZH125_FlavorSys
#    function_name FlavorSys
#---------------
#LeptonMETSys
#for current_sample in h026_mc16e_PowhegPy8_ZH125J_LeptonMETSys_1 h026_mc16e_PowhegPy8_ZH125J_LeptonMETSys_2 h026_mc16e_PowhegPy8_ggZH125_LeptonMETSys
#function_name LeptonMETSys
#---------------
fi
# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
if [ ${do_ttH} = "true" ]
    then
#---------------
#PhotonSys
#    for current_sample in h026_mc16a_PowhegPy8_ttH125_fixweight_PhotonSys_1 h026_mc16a_PowhegPy8_ttH125_fixweight_PhotonSys_2 h026_mc16d_PowhegPy8_ttH125_fixweight_PhotonSys_1 h026_mc16d_PowhegPy8_ttH125_fixweight_PhotonSys_2 h026_mc16d_PowhegPy8_ttH125_fixweight_PhotonSys_3 h026_mc16e_PowhegPy8_ttH125_fixweight_PhotonSys_1 h026_mc16e_PowhegPy8_ttH125_fixweight_PhotonSys_2 h026_mc16e_PowhegPy8_ttH125_fixweight_PhotonSys_3
#   function_name PhotonSys
#---------------
#JetSys1
#    for current_sample in h026_mc16a_PowhegPy8_ttH125_fixweight_JetSys1_1 h026_mc16a_PowhegPy8_ttH125_fixweight_JetSys1_2 h026_mc16a_PowhegPy8_ttH125_fixweight_JetSys1_3 h026_mc16d_PowhegPy8_ttH125_fixweight_JetSys1_1 h026_mc16d_PowhegPy8_ttH125_fixweight_JetSys1_2 h026_mc16d_PowhegPy8_ttH125_fixweight_JetSys1_3 h026_mc16d_PowhegPy8_ttH125_fixweight_JetSys1_4 h026_mc16e_PowhegPy8_ttH125_fixweight_JetSys1_1 h026_mc16e_PowhegPy8_ttH125_fixweight_JetSys1_2 h026_mc16e_PowhegPy8_ttH125_fixweight_JetSys1_3 h026_mc16e_PowhegPy8_ttH125_fixweight_JetSys1_4 h026_mc16e_PowhegPy8_ttH125_fixweight_JetSys1_5
#    function_name JetSys1
#---------------
#JetSys2
#    for current_sample in h026_mc16a_PowhegPy8_ttH125_fixweight_JetSys2_1 h026_mc16a_PowhegPy8_ttH125_fixweight_JetSys2_2 h026_mc16a_PowhegPy8_ttH125_fixweight_JetSys2_3 h026_mc16a_PowhegPy8_ttH125_fixweight_JetSys2_4 h026_mc16e_PowhegPy8_ttH125_fixweight_JetSys2_1 h026_mc16e_PowhegPy8_ttH125_fixweight_JetSys2_2 h026_mc16e_PowhegPy8_ttH125_fixweight_JetSys2_3 h026_mc16e_PowhegPy8_ttH125_fixweight_JetSys2_4 h026_mc16e_PowhegPy8_ttH125_fixweight_JetSys2_5
#    function_name JetSys2

    for current_sample in h026_mc16d_PowhegPy8_ttH125_fixweight_JetSys2_1 h026_mc16d_PowhegPy8_ttH125_fixweight_JetSys2_2 h026_mc16d_PowhegPy8_ttH125_fixweight_JetSys2_3 h026_mc16d_PowhegPy8_ttH125_fixweight_JetSys2_4
    function_name JetSys2
#---------------
#JetSys3
#    for current_sample in h026_mc16d_PowhegPy8_ttH125_fixweight_JetSys3_1 h026_mc16d_PowhegPy8_ttH125_fixweight_JetSys3_2 h026_mc16d_PowhegPy8_ttH125_fixweight_JetSys3_3 h026_mc16d_PowhegPy8_ttH125_fixweight_JetSys3_4 h026_mc16e_PowhegPy8_ttH125_fixweight_JetSys3_1 h026_mc16e_PowhegPy8_ttH125_fixweight_JetSys3_2 h026_mc16e_PowhegPy8_ttH125_fixweight_JetSys3_3 h026_mc16e_PowhegPy8_ttH125_fixweight_JetSys3_4
#    function_name JetSys3
    
    for current_sample in h026_mc16a_PowhegPy8_ttH125_fixweight_JetSys3_1 h026_mc16a_PowhegPy8_ttH125_fixweight_JetSys3_2 h026_mc16a_PowhegPy8_ttH125_fixweight_JetSys3_3
    function_name JetSys3
#---------------
#JetSys4
#    for current_sample in h026_mc16a_PowhegPy8_ttH125_fixweight_JetSys4_1 h026_mc16a_PowhegPy8_ttH125_fixweight_JetSys4_2 h026_mc16a_PowhegPy8_ttH125_fixweight_JetSys4_3 h026_mc16d_PowhegPy8_ttH125_fixweight_JetSys4_1 h026_mc16d_PowhegPy8_ttH125_fixweight_JetSys4_2 h026_mc16d_PowhegPy8_ttH125_fixweight_JetSys4_3 h026_mc16d_PowhegPy8_ttH125_fixweight_JetSys4_4 h026_mc16e_PowhegPy8_ttH125_fixweight_JetSys4_1 h026_mc16e_PowhegPy8_ttH125_fixweight_JetSys4_2 h026_mc16e_PowhegPy8_ttH125_fixweight_JetSys4_3 h026_mc16e_PowhegPy8_ttH125_fixweight_JetSys4_4
#    function_name JetSys4
#---------------
#FlavorSys
#    for current_sample in h026_mc16d_PowhegPy8_ttH125_fixweight_FlavorSys_1 h026_mc16d_PowhegPy8_ttH125_fixweight_FlavorSys_2 h026_mc16d_PowhegPy8_ttH125_fixweight_FlavorSys_3 h026_mc16d_PowhegPy8_ttH125_fixweight_FlavorSys_4 h026_mc16e_PowhegPy8_ttH125_fixweight_FlavorSys_1 h026_mc16e_PowhegPy8_ttH125_fixweight_FlavorSys_2 h026_mc16e_PowhegPy8_ttH125_fixweight_FlavorSys_3 h026_mc16e_PowhegPy8_ttH125_fixweight_FlavorSys_4 h026_mc16e_PowhegPy8_ttH125_fixweight_FlavorSys_5
#    function_name FlavorSys

    for current_sample in h026_mc16a_PowhegPy8_ttH125_fixweight_FlavorSys_1 h026_mc16a_PowhegPy8_ttH125_fixweight_FlavorSys_2 h026_mc16a_PowhegPy8_ttH125_fixweight_FlavorSys_3
    function_name FlavorSys
#---------------
#LeptonMETSys
#for current_sample in h026_mc16e_PowhegPy8_ttH125_fixweight_LeptonMETSys_1 h026_mc16e_PowhegPy8_ttH125_fixweight_LeptonMETSys_2 h026_mc16e_PowhegPy8_ttH125_fixweight_LeptonMETSys_3 h026_mc16e_PowhegPy8_ttH125_fixweight_LeptonMETSys_4 h026_mc16e_PowhegPy8_ttH125_fixweight_LeptonMETSys_5 h026_mc16e_PowhegPy8_ttH125_fixweight_LeptonMETSys_6
#function_name LeptonMETSys 

fi
# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
#HH resonant

if [ ${do_HH_resonant} = "true" ]
    then

#---------------
#PhotonSys
    
#mc16a
#    for current_sample in h026_mc16a_MGH7_X251tohh_bbyy_AF2_PhotonSys h026_mc16a_MGH7_X260tohh_bbyy_AF2_PhotonSys h026_mc16a_MGH7_X280tohh_bbyy_AF2_PhotonSys h026_mc16a_MGH7_X300tohh_bbyy_AF2_PhotonSys h026_mc16a_MGH7_X325tohh_bbyy_AF2_PhotonSys h026_mc16a_MGH7_X350tohh_bbyy_AF2_PhotonSys h026_mc16a_MGH7_X400tohh_bbyy_AF2_PhotonSys h026_mc16a_MGH7_X450tohh_bbyy_AF2_PhotonSys h026_mc16a_MGH7_X500tohh_bbyy_AF2_PhotonSys h026_mc16a_MGH7_X550tohh_bbyy_AF2_PhotonSys h026_mc16a_MGH7_X600tohh_bbyy_AF2_PhotonSys h026_mc16a_MGH7_X700tohh_bbyy_AF2_PhotonSys h026_mc16a_MGH7_X800tohh_bbyy_AF2_PhotonSys h026_mc16a_MGH7_X900tohh_bbyy_AF2_PhotonSys h026_mc16a_MGH7_X1000tohh_bbyy_AF2_PhotonSys
#    function_name PhotonSys

#mc16d
#    for current_sample in h026_mc16d_MGH7_X251tohh_bbyy_AF2_PhotonSys h026_mc16d_MGH7_X260tohh_bbyy_AF2_PhotonSys h026_mc16d_MGH7_X280tohh_bbyy_AF2_PhotonSys h026_mc16d_MGH7_X300tohh_bbyy_AF2_PhotonSys h026_mc16d_MGH7_X325tohh_bbyy_AF2_PhotonSys h026_mc16d_MGH7_X350tohh_bbyy_AF2_PhotonSys h026_mc16d_MGH7_X400tohh_bbyy_AF2_PhotonSys h026_mc16d_MGH7_X450tohh_bbyy_AF2_PhotonSys h026_mc16d_MGH7_X500tohh_bbyy_AF2_PhotonSys h026_mc16d_MGH7_X550tohh_bbyy_AF2_PhotonSys h026_mc16d_MGH7_X600tohh_bbyy_AF2_PhotonSys h026_mc16d_MGH7_X700tohh_bbyy_AF2_PhotonSys h026_mc16d_MGH7_X800tohh_bbyy_AF2_PhotonSys h026_mc16d_MGH7_X900tohh_bbyy_AF2_PhotonSys h026_mc16d_MGH7_X1000tohh_bbyy_AF2_PhotonSys
#    function_name PhotonSys
    
#mc16e
#    for current_sample in h026_mc16e_MGH7_X251tohh_bbyy_AF2_PhotonSys h026_mc16e_MGH7_X260tohh_bbyy_AF2_PhotonSys h026_mc16e_MGH7_X280tohh_bbyy_AF2_PhotonSys h026_mc16e_MGH7_X300tohh_bbyy_AF2_PhotonSys h026_mc16e_MGH7_X325tohh_bbyy_AF2_PhotonSys h026_mc16e_MGH7_X350tohh_bbyy_AF2_PhotonSys h026_mc16e_MGH7_X400tohh_bbyy_AF2_PhotonSys h026_mc16e_MGH7_X450tohh_bbyy_AF2_PhotonSys h026_mc16e_MGH7_X500tohh_bbyy_AF2_PhotonSys h026_mc16e_MGH7_X550tohh_bbyy_AF2_PhotonSys h026_mc16e_MGH7_X600tohh_bbyy_AF2_PhotonSys h026_mc16e_MGH7_X700tohh_bbyy_AF2_PhotonSys h026_mc16e_MGH7_X800tohh_bbyy_AF2_PhotonSys h026_mc16e_MGH7_X900tohh_bbyy_AF2_PhotonSys h026_mc16e_MGH7_X1000tohh_bbyy_AF2_PhotonSys
#    function_name PhotonSys
#---------------
#JetSys1
    
#mc16a
#    for current_sample in h026_mc16a_MGH7_X251tohh_bbyy_AF2_JetSys1 h026_mc16a_MGH7_X260tohh_bbyy_AF2_JetSys1 h026_mc16a_MGH7_X280tohh_bbyy_AF2_JetSys1 h026_mc16a_MGH7_X300tohh_bbyy_AF2_JetSys1 h026_mc16a_MGH7_X325tohh_bbyy_AF2_JetSys1 h026_mc16a_MGH7_X350tohh_bbyy_AF2_JetSys1 h026_mc16a_MGH7_X400tohh_bbyy_AF2_JetSys1 h026_mc16a_MGH7_X450tohh_bbyy_AF2_JetSys1 h026_mc16a_MGH7_X500tohh_bbyy_AF2_JetSys1 h026_mc16a_MGH7_X550tohh_bbyy_AF2_JetSys1 h026_mc16a_MGH7_X600tohh_bbyy_AF2_JetSys1 h026_mc16a_MGH7_X700tohh_bbyy_AF2_JetSys1 h026_mc16a_MGH7_X800tohh_bbyy_AF2_JetSys1 h026_mc16a_MGH7_X900tohh_bbyy_AF2_JetSys1 h026_mc16a_MGH7_X1000tohh_bbyy_AF2_JetSys1
#    function_name JetSys1
    
#mc16d
#    for current_sample in h026_mc16d_MGH7_X251tohh_bbyy_AF2_JetSys1 h026_mc16d_MGH7_X260tohh_bbyy_AF2_JetSys1 h026_mc16d_MGH7_X280tohh_bbyy_AF2_JetSys1 h026_mc16d_MGH7_X300tohh_bbyy_AF2_JetSys1 h026_mc16d_MGH7_X325tohh_bbyy_AF2_JetSys1 h026_mc16d_MGH7_X350tohh_bbyy_AF2_JetSys1 h026_mc16d_MGH7_X400tohh_bbyy_AF2_JetSys1 h026_mc16d_MGH7_X450tohh_bbyy_AF2_JetSys1 h026_mc16d_MGH7_X500tohh_bbyy_AF2_JetSys1 h026_mc16d_MGH7_X550tohh_bbyy_AF2_JetSys1 h026_mc16d_MGH7_X600tohh_bbyy_AF2_JetSys1 h026_mc16d_MGH7_X700tohh_bbyy_AF2_JetSys1 h026_mc16d_MGH7_X800tohh_bbyy_AF2_JetSys1 h026_mc16d_MGH7_X900tohh_bbyy_AF2_JetSys1 h026_mc16d_MGH7_X1000tohh_bbyy_AF2_JetSys1
#    function_name JetSys1
    
#mc16e
#    for current_sample in h026_mc16e_MGH7_X251tohh_bbyy_AF2_JetSys1 h026_mc16e_MGH7_X260tohh_bbyy_AF2_JetSys1 h026_mc16e_MGH7_X280tohh_bbyy_AF2_JetSys1 h026_mc16e_MGH7_X300tohh_bbyy_AF2_JetSys1 h026_mc16e_MGH7_X325tohh_bbyy_AF2_JetSys1 h026_mc16e_MGH7_X350tohh_bbyy_AF2_JetSys1 h026_mc16e_MGH7_X400tohh_bbyy_AF2_JetSys1 h026_mc16e_MGH7_X450tohh_bbyy_AF2_JetSys1 h026_mc16e_MGH7_X500tohh_bbyy_AF2_JetSys1 h026_mc16e_MGH7_X550tohh_bbyy_AF2_JetSys1 h026_mc16e_MGH7_X600tohh_bbyy_AF2_JetSys1 h026_mc16e_MGH7_X700tohh_bbyy_AF2_JetSys1 h026_mc16e_MGH7_X800tohh_bbyy_AF2_JetSys1 h026_mc16e_MGH7_X900tohh_bbyy_AF2_JetSys1 h026_mc16e_MGH7_X1000tohh_bbyy_AF2_JetSys1
#    function_name JetSys1
#---------------
#JetSys2
    
#mc16a
#    for current_sample in h026_mc16a_MGH7_X450tohh_bbyy_AF2_JetSys2
#    function_name JetSys2

#    for current_sample in h026_mc16e_MGH7_X800tohh_bbyy_AF2_JetSys2
#    function_name JetSys2

#    for current_sample in h026_mc16a_MGH7_X251tohh_bbyy_AF2_JetSys2 h026_mc16a_MGH7_X260tohh_bbyy_AF2_JetSys2 h026_mc16a_MGH7_X280tohh_bbyy_AF2_JetSys2 h026_mc16a_MGH7_X300tohh_bbyy_AF2_JetSys2 h026_mc16a_MGH7_X325tohh_bbyy_AF2_JetSys2 h026_mc16a_MGH7_X350tohh_bbyy_AF2_JetSys2 h026_mc16a_MGH7_X400tohh_bbyy_AF2_JetSys2  h026_mc16a_MGH7_X500tohh_bbyy_AF2_JetSys2 h026_mc16a_MGH7_X550tohh_bbyy_AF2_JetSys2 h026_mc16a_MGH7_X600tohh_bbyy_AF2_JetSys2 h026_mc16a_MGH7_X700tohh_bbyy_AF2_JetSys2 h026_mc16a_MGH7_X800tohh_bbyy_AF2_JetSys2 h026_mc16a_MGH7_X900tohh_bbyy_AF2_JetSys2 h026_mc16a_MGH7_X1000tohh_bbyy_AF2_JetSys2
#    function_name JetSys2
    
#mc16d
#    for current_sample in h026_mc16d_MGH7_X251tohh_bbyy_AF2_JetSys2 h026_mc16d_MGH7_X260tohh_bbyy_AF2_JetSys2 h026_mc16d_MGH7_X280tohh_bbyy_AF2_JetSys2 h026_mc16d_MGH7_X300tohh_bbyy_AF2_JetSys2 h026_mc16d_MGH7_X325tohh_bbyy_AF2_JetSys2 h026_mc16d_MGH7_X350tohh_bbyy_AF2_JetSys2 h026_mc16d_MGH7_X400tohh_bbyy_AF2_JetSys2 h026_mc16d_MGH7_X450tohh_bbyy_AF2_JetSys2 h026_mc16d_MGH7_X500tohh_bbyy_AF2_JetSys2 h026_mc16d_MGH7_X550tohh_bbyy_AF2_JetSys2 h026_mc16d_MGH7_X600tohh_bbyy_AF2_JetSys2 h026_mc16d_MGH7_X700tohh_bbyy_AF2_JetSys2 h026_mc16d_MGH7_X800tohh_bbyy_AF2_JetSys2 h026_mc16d_MGH7_X900tohh_bbyy_AF2_JetSys2 h026_mc16d_MGH7_X1000tohh_bbyy_AF2_JetSys2
#    function_name JetSys2
    
#mc16e
#    for current_sample in h026_mc16e_MGH7_X251tohh_bbyy_AF2_JetSys2 h026_mc16e_MGH7_X260tohh_bbyy_AF2_JetSys2 h026_mc16e_MGH7_X280tohh_bbyy_AF2_JetSys2 h026_mc16e_MGH7_X300tohh_bbyy_AF2_JetSys2 h026_mc16e_MGH7_X325tohh_bbyy_AF2_JetSys2 h026_mc16e_MGH7_X350tohh_bbyy_AF2_JetSys2 h026_mc16e_MGH7_X400tohh_bbyy_AF2_JetSys2 h026_mc16e_MGH7_X450tohh_bbyy_AF2_JetSys2 h026_mc16e_MGH7_X500tohh_bbyy_AF2_JetSys2 h026_mc16e_MGH7_X550tohh_bbyy_AF2_JetSys2 h026_mc16e_MGH7_X600tohh_bbyy_AF2_JetSys2 h026_mc16e_MGH7_X700tohh_bbyy_AF2_JetSys2 h026_mc16e_MGH7_X900tohh_bbyy_AF2_JetSys2 h026_mc16e_MGH7_X1000tohh_bbyy_AF2_JetSys2
#    function_name JetSys2
#---------------
#JetSys3
    
#    for current_sample in h026_mc16a_MGH7_X260tohh_bbyy_AF2_JetSys3 h026_mc16a_MGH7_X300tohh_bbyy_AF2_JetSys3 h026_mc16a_MGH7_X325tohh_bbyy_AF2_JetSys3 h026_mc16a_MGH7_X550tohh_bbyy_AF2_JetSys3 h026_mc16a_MGH7_X600tohh_bbyy_AF2_JetSys3 h026_mc16a_MGH7_X900tohh_bbyy_AF2_JetSys3
#    function_name JetSys3

#mc16a
#    for current_sample in h026_mc16a_MGH7_X251tohh_bbyy_AF2_JetSys3 h026_mc16a_MGH7_X280tohh_bbyy_AF2_JetSys3 h026_mc16a_MGH7_X350tohh_bbyy_AF2_JetSys3 h026_mc16a_MGH7_X400tohh_bbyy_AF2_JetSys3 h026_mc16a_MGH7_X450tohh_bbyy_AF2_JetSys3 h026_mc16a_MGH7_X500tohh_bbyy_AF2_JetSys3 h026_mc16a_MGH7_X700tohh_bbyy_AF2_JetSys3 h026_mc16a_MGH7_X800tohh_bbyy_AF2_JetSys3 h026_mc16a_MGH7_X1000tohh_bbyy_AF2_JetSys3
#    function_name JetSys3
    
#mc16d
#    for current_sample in h026_mc16d_MGH7_X280tohh_bbyy_AF2_JetSys3 h026_mc16d_MGH7_X325tohh_bbyy_AF2_JetSys3 h026_mc16d_MGH7_X350tohh_bbyy_AF2_JetSys3 h026_mc16d_MGH7_X450tohh_bbyy_AF2_JetSys3 h026_mc16d_MGH7_X550tohh_bbyy_AF2_JetSys3 h026_mc16d_MGH7_X600tohh_bbyy_AF2_JetSys3 h026_mc16d_MGH7_X1000tohh_bbyy_AF2_JetSys3
#    function_name JetSys3

#    for current_sample in h026_mc16d_MGH7_X251tohh_bbyy_AF2_JetSys3 h026_mc16d_MGH7_X260tohh_bbyy_AF2_JetSys3 h026_mc16d_MGH7_X300tohh_bbyy_AF2_JetSys3 h026_mc16d_MGH7_X400tohh_bbyy_AF2_JetSys3  h026_mc16d_MGH7_X500tohh_bbyy_AF2_JetSys3 h026_mc16d_MGH7_X700tohh_bbyy_AF2_JetSys3 h026_mc16d_MGH7_X800tohh_bbyy_AF2_JetSys3 h026_mc16d_MGH7_X900tohh_bbyy_AF2_JetSys3
#    function_name JetSys3
    
#mc16e
#    for current_sample in h026_mc16e_MGH7_X251tohh_bbyy_AF2_JetSys3 h026_mc16e_MGH7_X260tohh_bbyy_AF2_JetSys3 h026_mc16e_MGH7_X280tohh_bbyy_AF2_JetSys3 h026_mc16e_MGH7_X300tohh_bbyy_AF2_JetSys3 h026_mc16e_MGH7_X325tohh_bbyy_AF2_JetSys3 h026_mc16e_MGH7_X350tohh_bbyy_AF2_JetSys3 h026_mc16e_MGH7_X400tohh_bbyy_AF2_JetSys3 h026_mc16e_MGH7_X450tohh_bbyy_AF2_JetSys3 h026_mc16e_MGH7_X500tohh_bbyy_AF2_JetSys3 h026_mc16e_MGH7_X550tohh_bbyy_AF2_JetSys3 h026_mc16e_MGH7_X600tohh_bbyy_AF2_JetSys3 h026_mc16e_MGH7_X700tohh_bbyy_AF2_JetSys3
#    function_name JetSys3

#    for current_sample in h026_mc16e_MGH7_X800tohh_bbyy_AF2_JetSys3 h026_mc16e_MGH7_X900tohh_bbyy_AF2_JetSys3 h026_mc16e_MGH7_X1000tohh_bbyy_AF2_JetSys3
#    function_name JetSys3
#---------------
#JetSys4
    
#mc16a
#    for current_sample in h026_mc16a_MGH7_X251tohh_bbyy_AF2_JetSys4 h026_mc16a_MGH7_X260tohh_bbyy_AF2_JetSys4 h026_mc16a_MGH7_X280tohh_bbyy_AF2_JetSys4 h026_mc16a_MGH7_X300tohh_bbyy_AF2_JetSys4 h026_mc16a_MGH7_X325tohh_bbyy_AF2_JetSys4 h026_mc16a_MGH7_X350tohh_bbyy_AF2_JetSys4 h026_mc16a_MGH7_X400tohh_bbyy_AF2_JetSys4 h026_mc16a_MGH7_X450tohh_bbyy_AF2_JetSys4 h026_mc16a_MGH7_X500tohh_bbyy_AF2_JetSys4 h026_mc16a_MGH7_X550tohh_bbyy_AF2_JetSys4 h026_mc16a_MGH7_X600tohh_bbyy_AF2_JetSys4 h026_mc16a_MGH7_X700tohh_bbyy_AF2_JetSys4 h026_mc16a_MGH7_X800tohh_bbyy_AF2_JetSys4 h026_mc16a_MGH7_X900tohh_bbyy_AF2_JetSys4 h026_mc16a_MGH7_X1000tohh_bbyy_AF2_JetSys4
#    function_name JetSys4
    
#mc16d
    
    for current_sample in h026_mc16d_MGH7_X500tohh_bbyy_AF2_JetSys4
    function_name JetSys4
exit(1)

    for current_sample in h026_mc16d_MGH7_X251tohh_bbyy_AF2_JetSys4 h026_mc16d_MGH7_X260tohh_bbyy_AF2_JetSys4 h026_mc16d_MGH7_X280tohh_bbyy_AF2_JetSys4 h026_mc16d_MGH7_X300tohh_bbyy_AF2_JetSys4 h026_mc16d_MGH7_X325tohh_bbyy_AF2_JetSys4 h026_mc16d_MGH7_X350tohh_bbyy_AF2_JetSys4 h026_mc16d_MGH7_X400tohh_bbyy_AF2_JetSys4 h026_mc16d_MGH7_X450tohh_bbyy_AF2_JetSys4  h026_mc16d_MGH7_X550tohh_bbyy_AF2_JetSys4 h026_mc16d_MGH7_X600tohh_bbyy_AF2_JetSys4 h026_mc16d_MGH7_X700tohh_bbyy_AF2_JetSys4 h026_mc16d_MGH7_X800tohh_bbyy_AF2_JetSys4 h026_mc16d_MGH7_X900tohh_bbyy_AF2_JetSys4 h026_mc16d_MGH7_X1000tohh_bbyy_AF2_JetSys4
    function_name JetSys4
    
#mc16e
    for current_sample in h026_mc16e_MGH7_X251tohh_bbyy_AF2_JetSys4 h026_mc16e_MGH7_X260tohh_bbyy_AF2_JetSys4 h026_mc16e_MGH7_X280tohh_bbyy_AF2_JetSys4 h026_mc16e_MGH7_X300tohh_bbyy_AF2_JetSys4 h026_mc16e_MGH7_X325tohh_bbyy_AF2_JetSys4 h026_mc16e_MGH7_X350tohh_bbyy_AF2_JetSys4 h026_mc16e_MGH7_X400tohh_bbyy_AF2_JetSys4 h026_mc16e_MGH7_X450tohh_bbyy_AF2_JetSys4 h026_mc16e_MGH7_X500tohh_bbyy_AF2_JetSys4 h026_mc16e_MGH7_X550tohh_bbyy_AF2_JetSys4 h026_mc16e_MGH7_X600tohh_bbyy_AF2_JetSys4 h026_mc16e_MGH7_X700tohh_bbyy_AF2_JetSys4 h026_mc16e_MGH7_X800tohh_bbyy_AF2_JetSys4 h026_mc16e_MGH7_X900tohh_bbyy_AF2_JetSys4 h026_mc16e_MGH7_X1000tohh_bbyy_AF2_JetSys4
    function_name JetSys4
#---------------
#FlavorSys
    
#mc16a
    for current_sample in h026_mc16a_MGH7_X251tohh_bbyy_AF2_FlavorSys h026_mc16a_MGH7_X260tohh_bbyy_AF2_FlavorSys h026_mc16a_MGH7_X280tohh_bbyy_AF2_FlavorSys h026_mc16a_MGH7_X300tohh_bbyy_AF2_FlavorSys h026_mc16a_MGH7_X325tohh_bbyy_AF2_FlavorSys h026_mc16a_MGH7_X350tohh_bbyy_AF2_FlavorSys h026_mc16a_MGH7_X400tohh_bbyy_AF2_FlavorSys h026_mc16a_MGH7_X450tohh_bbyy_AF2_FlavorSys h026_mc16a_MGH7_X500tohh_bbyy_AF2_FlavorSys h026_mc16a_MGH7_X550tohh_bbyy_AF2_FlavorSys h026_mc16a_MGH7_X600tohh_bbyy_AF2_FlavorSys h026_mc16a_MGH7_X700tohh_bbyy_AF2_FlavorSys h026_mc16a_MGH7_X800tohh_bbyy_AF2_FlavorSys h026_mc16a_MGH7_X900tohh_bbyy_AF2_FlavorSys h026_mc16a_MGH7_X1000tohh_bbyy_AF2_FlavorSys
    function_name FlavorSys
    
#mc16d
    for current_sample in h026_mc16d_MGH7_X251tohh_bbyy_AF2_FlavorSys h026_mc16d_MGH7_X260tohh_bbyy_AF2_FlavorSys h026_mc16d_MGH7_X280tohh_bbyy_AF2_FlavorSys h026_mc16d_MGH7_X300tohh_bbyy_AF2_FlavorSys h026_mc16d_MGH7_X325tohh_bbyy_AF2_FlavorSys h026_mc16d_MGH7_X350tohh_bbyy_AF2_FlavorSys h026_mc16d_MGH7_X400tohh_bbyy_AF2_FlavorSys h026_mc16d_MGH7_X450tohh_bbyy_AF2_FlavorSys h026_mc16d_MGH7_X500tohh_bbyy_AF2_FlavorSys h026_mc16d_MGH7_X550tohh_bbyy_AF2_FlavorSys h026_mc16d_MGH7_X600tohh_bbyy_AF2_FlavorSys h026_mc16d_MGH7_X700tohh_bbyy_AF2_FlavorSys h026_mc16d_MGH7_X800tohh_bbyy_AF2_FlavorSys h026_mc16d_MGH7_X900tohh_bbyy_AF2_FlavorSys h026_mc16d_MGH7_X1000tohh_bbyy_AF2_FlavorSys
    function_name FlavorSys
    
#mc16e
    for current_sample in h026_mc16e_MGH7_X251tohh_bbyy_AF2_FlavorSys h026_mc16e_MGH7_X260tohh_bbyy_AF2_FlavorSys h026_mc16e_MGH7_X280tohh_bbyy_AF2_FlavorSys h026_mc16e_MGH7_X300tohh_bbyy_AF2_FlavorSys h026_mc16e_MGH7_X325tohh_bbyy_AF2_FlavorSys h026_mc16e_MGH7_X350tohh_bbyy_AF2_FlavorSys h026_mc16e_MGH7_X400tohh_bbyy_AF2_FlavorSys h026_mc16e_MGH7_X450tohh_bbyy_AF2_FlavorSys h026_mc16e_MGH7_X500tohh_bbyy_AF2_FlavorSys h026_mc16e_MGH7_X550tohh_bbyy_AF2_FlavorSys h026_mc16e_MGH7_X600tohh_bbyy_AF2_FlavorSys h026_mc16e_MGH7_X700tohh_bbyy_AF2_FlavorSys h026_mc16e_MGH7_X800tohh_bbyy_AF2_FlavorSys h026_mc16e_MGH7_X900tohh_bbyy_AF2_FlavorSys h026_mc16e_MGH7_X1000tohh_bbyy_AF2_FlavorSys
    function_name FlavorSys
fi

exit(1)
# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
