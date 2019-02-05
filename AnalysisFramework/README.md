#AnalysisFramework for HH->bbyy analysis - SLAC group

#If you have any questions, please contact me valentina.maria.cairo@cern.ch


To run the main program which produces yields.txt and plots/sample\_Low/HighMass\_Loose/TightBtagging:


cd AnalysisFramework

setupATLAS

lsetup "root 6.14.04-x86_64-slc6-gcc62-opt"

mkdir build

cd build

cmake ../

make -j

./hhbbyy computeYieldsEffs.js

========================================


To check if the samples used in the early Run 2 results (https://cds.cern.ch/record/2305127) still exist use utils/checkFile.cxx

(very basic macro just to make sure all the files used in the previous analysis still exist (MxAOD derivations))


setupATLAS

lsetup xrootd

voms-proxy-init -voms atlas

lsetup root

root -l 

.L checkFile.cxx+g

checkFile()
