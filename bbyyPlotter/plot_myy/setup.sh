#taken from xmlAnaWSBuilder; need > ROOT 6.18 for the latest version

export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase # use your path
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh
lsetup "root 6.18.04-x86_64-centos7-gcc8-opt"

#for RooDSCB
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/afs/cern.ch/user/a/alwang/work/quickFit_coupling2020/RooFitExtensions

ulimit -s unlimited
