# AnalysisFramework for HH->bbyy analysis - SLAC group

## If you have any questions, please contact me valentina.maria.cairo@cern.ch


**To run the main program which produces yields.txt, yields.js and histograms (based on the configurations applied in the JSON files) in a folder *plots*, please follow the instructions below after cloning this project:**

cd AnalysisFramework

source setup.sh

**Build the project:**

mkdir build

cd build

cmake3 ../

make -j

**This will create a *run* folder which contains the executable *hhbbyy*. Now go in the folder**

cd ../run

**You can now produce histograms by typing, for example:**

./hhbbyy json/H026/Non_Resonant/Baseline_skimmed_2bjet.js
./hhbbyy json/H026/Non_Resonant/Data_skimmed_2bjet.js

**or by using any of the JSON files linked through the *json* soft link (you will find three folders, namely H024, H025, H026  which contain configurations for the 3 production campaigns).**

For the final paper results, please use the json files listed here: https://gitlab.cern.ch/atlas-physics/HDBS/DiHiggs/yybb/code/-/tree/master/AnalysisFramework/utils 

**You can also submit your jobs on condor, otherwise it takes quite some time to run over all the samples.**

python SubmitCondor.py

**this will write he output as usual in the plots/ folder. You can check the status of your jobs with**

condor_q

**you can kill them with**

condor_rm jobID



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
