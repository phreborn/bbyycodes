#!/bin/bash

# Read arguments
CMD=$1
OutputName=$2

ExeFile="${OutputName}_job.sh"
JobFile="job"

# main Optimization code directory
BasePath="$PWD/"

#mkdir -p "${BasePath}/condor"

JobDir="${BasePath}/condor/"

HistFitterDir="${HISTFITTER}"

#==================================
#
# Make all the needed directories
#
#==================================
echo ""
echo "Making output directories ..."
echo "============================="
mkdir -p $JobDir

#================================
#
# Create Condor job  
#
#================================
echo 
echo "Creating condor job $JobDir/$JobFile ... "
echo "========================================="
  
# the following gets output-ed in the condor run file called "job" 
echo "Executable    = ${JobDir}/${ExeFile}"              > $JobDir/$JobFile
echo "Error         = ${JobDir}/${OutputName}.err"      >> $JobDir/$JobFile
echo "Output        = ${JobDir}/${OutputName}.out"      >> $JobDir/$JobFile
echo "Log           = ${JobDir}/${OutputName}.log"      >> $JobDir/$JobFile
echo                                                    >> $JobDir/$JobFile

echo '+JobFlavour = "workday"'                        >> $JobDir/$JobFile
## Set maximum run time in seconds
# echo "+MaxRuntime   = 259200"                           >> $JobDir/$JobFile

echo 'Queue'                                            >> $JobDir/$JobFile
echo                                                    >> $JobDir/$JobFile 


#================================
#
# Create runscript file  
#
#================================

# this is what the condor job will run
echo 
echo "Creating runscript file $JobDir/$ExeFile ..."
echo "============================================"
 

echo "#!/bin/bash"                                            > $JobDir/$ExeFile
echo ''                                                      >> $JobDir/$ExeFile
echo "export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase"  >> $JobDir/$ExeFile
echo "source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh" >> $JobDir/$ExeFile
echo "setupATLAS"                                            >> $JobDir/$ExeFile
echo 'lsetup "root 6.14.04-x86_64-slc6-gcc62-opt"'            >> $JobDir/$ExeFile
echo "cd $BasePath"                                          >> $JobDir/$ExeFile
echo                                                         >> $JobDir/$ExeFile
echo "${CMD}"                                                >> $JobDir/$ExeFile
chmod a+x $JobDir/$ExeFile



#================================
#
# Launch onto Condor!   
#
#================================
echo 
echo "Launching jobs onto Condor!"
echo "==========================="
condor_submit $JobDir/$JobFile

echo 
echo "Done"
echo 

