#taken from xmlAnaWSBuilder; need > ROOT 6.18 for the latest version
#export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase # use your path
#source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh
#lsetup "root 6.18.04-x86_64-centos7-gcc8-opt"

#taken from quickFit
source /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/CMake/3.14.3/x86_64-centos7-gcc8-opt/CMake-env.sh
source /cvmfs/sft.cern.ch/lcg/releases/LCG_97_ATLAS_1/ROOT/v6.20.02/x86_64-centos7-gcc8-opt/ROOT-env.sh
source /cvmfs/sft.cern.ch/lcg/releases/LCG_96b/Boost/1.70.0/x86_64-centos7-gcc8-opt/Boost-env.sh

#for RooDSCB
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/afs/cern.ch/user/a/alwang/work/quickFit_coupling2020/RooFitExtensions

ulimit -s unlimited
