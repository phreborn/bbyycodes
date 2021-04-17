TO PUT THE GOOD OPTIONS

exit(1)

#for mode bootstrap : 
#bool do_syst_shape=1;
#int mode_shape_MakeAndStoreFits=1;
#int mode_shape_ReadFits_previously_made=0;


function_name()
{
  CurrentScript=/sps/atlas/e/escalier/scratch/scriptPublication.${string_observable}_${string_MxAOD}.cat_${index_category}_toys_${index_start_toy}_${index_stop_toy}
#to replace with ccenv root 6.18.00 ?
  echo "cd /pbs/home/e/escalier" > ${CurrentScript}
  echo "pwd" >> ${CurrentScript}
  echo "ls" >> ${CurrentScript}
  echo "ccenv root 6.18.00" >> ${CurrentScript}
  echo "root -b -q" >> ${CurrentScript}
  echo "pwd" >> ${CurrentScript}
  echo "cd /pbs/home/e/escalier/public/ATLAS_HGam/HHyybb/Systematics_Yields_Shape/Run2" >> ${CurrentScript}
  echo "pwd" >> ${CurrentScript}
  echo "ls" >> ${CurrentScript}

#added compilation : **mandatory** (else does not compile nor work) 
#  echo "root -b -q \"ReviewEffectSystematics.C+(${index_category},\\\"${string_observable}\\\",\\\"${string_MxAOD}\\\",${index_start_toy},${index_stop_toy})\"" >> ${CurrentScript}
  echo "root -b -q \"ReviewEffectSystematics.C+(${index_category},\\\"${string_observable}\\\",\\\"${string_MxAOD}\\\",${index_start_toy},${index_stop_toy})\"" >> ${CurrentScript}
  
#at least 75 hours for inclusive

#32 hours<=>17 toys for fits...
#qsub -P P_atlas -m e -M escalier@lal.in2p3.fr -l ct=32:00:00 -l h_rss=2G -l vmem=3G,sps=1 -N j.${string_observable}.${string_MxAOD}.${index_category}_toys_${index_start_toy}_${index_stop_toy} -o /sps/atlas/e/escalier/scratch/Log_HH_syst_shape_${string_observable}_${string_MxAOD}_${index_category}_toys_${index_start_toy}_${index_stop_toy}.OU -e /sps/atlas/e/escalier/scratch/Log_HH_syst_shape_${string_observable}_${string_MxAOD}_${index_category}_toys_${index_start_toy}_${index_stop_toy}.ER ${CurrentScript}

#qsub -P P_atlas -m e -M escalier@lal.in2p3.fr -l ct=100:00:00 -l h_rss=2G -l vmem=3G,sps=1 -N j.${string_observable}.${string_MxAOD}.${index_category}_toys_${index_start_toy}_${index_stop_toy} -o /sps/atlas/e/escalier/scratch/Log_HH_syst_shape_${string_observable}_${string_MxAOD}_${index_category}_toys_${index_start_toy}_${index_stop_toy}.OU -e /sps/atlas/e/escalier/scratch/Log_HH_syst_shape_${string_observable}_${string_MxAOD}_${index_category}_toys_${index_start_toy}_${index_stop_toy}.ER ${CurrentScript}

#for one systematic
#qsub -P P_atlas -m e -M escalier@lal.in2p3.fr -l ct=2:00:00 -l h_rss=2G -l vmem=3G,sps=1 -N j.${string_observable}.${string_MxAOD}.${index_category}_toys_${index_start_toy}_${index_stop_toy} -o /sps/atlas/e/escalier/scratch/Log_HH_syst_shape_${string_observable}_${string_MxAOD}_${index_category}_toys_${index_start_toy}_${index_stop_toy}.OU -e /sps/atlas/e/escalier/scratch/Log_HH_syst_shape_${string_observable}_${string_MxAOD}_${index_category}_toys_${index_start_toy}_${index_stop_toy}.ER ${CurrentScript}

#qsub -P P_atlas -m e -M escalier@lal.in2p3.fr -l sps=1 -l h_cpu=03:00:00 -l h_rss=2G -l vmem=3G -N j.${string_observable}.${string_MxAOD}.${index_category}_toys_${index_start_toy}_${index_stop_toy} -o /sps/atlas/e/escalier/scratch/Log_HH_syst_shape_${string_observable}_${string_MxAOD}_${index_category}_toys_${index_start_toy}_${index_stop_toy}.OU -e /sps/atlas/e/escalier/scratch/Log_HH_syst_shape_${string_observable}_${string_MxAOD}_${index_category}_toys_${index_start_toy}_${index_stop_toy}.ER ${CurrentScript}

#qsub -P P_atlas -m e -M escalier@lal.in2p3.fr -l sps=1 -q interactive -l h_cpu=03:00:00 -l h_rss=2G -l vmem=3G -N j.${string_observable}.${string_MxAOD}.${index_category}_toys_${index_start_toy}_${index_stop_toy} -o /sps/atlas/e/escalier/scratch/Log_HH_syst_shape_${string_observable}_${string_MxAOD}_${index_category}_toys_${index_start_toy}_${index_stop_toy}.OU -e /sps/atlas/e/escalier/scratch/Log_HH_syst_shape_${string_observable}_${string_MxAOD}_${index_category}_toys_${index_start_toy}_${index_stop_toy}.ER ${CurrentScript}


#qsub -P P_atlas -m e -M escalier@lal.in2p3.fr -l sps=1 -l h_cpu=03:00:00 -l h_rss=2G -l vmem=3G -N j.${string_observable}.${string_MxAOD}.${index_category}_toys_${index_start_toy}_${index_stop_toy} -o /sps/atlas/e/escalier/scratch/Log_HH_syst_shape_${string_observable}_${string_MxAOD}_${index_category}_toys_${index_start_toy}_${index_stop_toy}.OU -e /sps/atlas/e/escalier/scratch/Log_HH_syst_shape_${string_observable}_${string_MxAOD}_${index_category}_toys_${index_start_toy}_${index_stop_toy}.ER ${CurrentScript}


#qsub -P P_atlas -m e -M escalier@lal.in2p3.fr -q long -l sps=1 -l h_cpu=03:00:00 -l h_rss=2G -l vmem=3G -N j.${string_observable}.${string_MxAOD}.${index_category}_toys_${index_start_toy}_${index_stop_toy} -o /sps/atlas/e/escalier/scratch/Log_HH_syst_shape_${string_observable}_${string_MxAOD}_${index_category}_toys_${index_start_toy}_${index_stop_toy}.OU -e /sps/atlas/e/escalier/scratch/Log_HH_syst_shape_${string_observable}_${string_MxAOD}_${index_category}_toys_${index_start_toy}_${index_stop_toy}.ER ${CurrentScript}

#3 hours too short

qsub -P P_atlas -m e -M escalier@lal.in2p3.fr -q long -l sps=1 -l h_cpu=04:00:00 -l h_rss=2G -l vmem=3G -N j.${string_observable}.${string_MxAOD}.${index_category}_toys_${index_start_toy}_${index_stop_toy} -o /sps/atlas/e/escalier/scratch/Log_HH_syst_shape_${string_observable}_${string_MxAOD}_${index_category}_toys_${index_start_toy}_${index_stop_toy}.OU -e /sps/atlas/e/escalier/scratch/Log_HH_syst_shape_${string_observable}_${string_MxAOD}_${index_category}_toys_${index_start_toy}_${index_stop_toy}.ER ${CurrentScript}

#-q interactive

#30 seconds is too short : interference
 
#  sleep 60
#  sleep 90
#  sleep 80
  sleep 90
}

for string_observable in m_yy
#for string_observable in m_bb
#for string_MxAOD in h024_mc16a h024_mc16d
#for string_MxAOD in h024_mc16e
  
#for string_MxAOD in h024_mc16d h024_mc16a h024_mc16e
#for string_MxAOD in h024_mc16d
#for string_MxAOD in h024_mc16a_h024_mc16d_h024_mc16e
for string_MxAOD in h025_mc16d
  do
  
# size_block=50
  size_block=100
  
for index_category in 0
#for index_category in 2
#for index_category in 0 1 2 3 4
#for index_category in 0 1 2 3 4
#for index_category in 4
#for index_category in 3
#for index_category in 1 2 3
#for index_category in 4
    do
    
    echo "---------------------------------------------------------------------------------------"
#DO max 1000: enough

#    index_start_toy=0
#	index_start_toy=450
#	index_start_toy=100
#	index_start_toy=200
#	index_start_toy=300
#	index_start_toy=400
#	index_start_toy=500
#	index_start_toy=150
#	index_start_toy=600
#	index_start_toy=650
#	index_start_toy=300
#	index_start_toy=800
#    index_start_toy=1500
    index_start_toy=1000
    
#     while [ $index_start_toy -lt 100 ]
#     while [ $index_start_toy -lt 200 ]
#     while [ $index_start_toy -lt 300 ]
#    while [ $index_start_toy -lt 1000 ]
#    while [ $index_start_toy -lt 400 ]
#    while [ $index_start_toy -lt 500 ]
#    while [ $index_start_toy -lt 50 ]
#    while [ $index_start_toy -lt 900 ]
#    while [ $index_start_toy -lt 650 ]

#1500 is the maximum for double [...]
#    while [ $index_start_toy -lt 1500 ]
#    while [ $index_start_toy -lt 1000 ]
#    while [ $index_start_toy -lt 900 ]
    while [ $index_start_toy -lt 2000 ]

#   while [ $index_start_toy -lt 150 ]
#    while [ $index_start_toy -lt 150 ]
#    while [ $index_start_toy -lt 500 ]
#    while [ $index_start_toy -lt 1 ]
      do
      index_stop_toy=`expr $index_start_toy + $size_block`
      
      function_name index_category string_observable string_MxAOD index_start_toy index_stop_toy
      
      index_start_toy=`expr $index_start_toy + $size_block`
    done
  done
done
