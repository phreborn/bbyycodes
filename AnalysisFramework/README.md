# AnalysisFramework for HH->bbyy analysis - SLAC group

## If you have any questions, please contact me valentina.maria.cairo@cern.ch


**To run the main program which produces yields.txt and histograms (based on the configurations applied in the JSON files) in a folder *plots*, please follow the instructions below after cloning this project:**

cd AnalysisFramework

source setup.sh

**Build the project:**

mkdir build

cd build

cmake ../

make -j

**This will create a *run* folder which contains the executable *hhbbyy*. Now go in the folder**

cd ../run

**You can now produce histograms by typing, for example:**

./hhbbyy computeYieldsEffs_allSelections_HHNLOBugFix.js

**or by using any of the JSON files linked through the *json* soft link (you will find two folders, namely H024 and H025, which contain configurations for the 2 production campaigns).**



## ========================================


To check if the samples used in the early Run 2 results (https://cds.cern.ch/record/2305127) still exist use utils/checkFile.cxx

(very basic macro just to make sure all the files used in the previous analysis still exist (MxAOD derivations))


setupATLAS

lsetup xrootd

voms-proxy-init -voms atlas

lsetup root

root -l 

.L checkFile.cxx+g

checkFile()
