# Method to add data-driven yj+jj into data/MC plots

## Step 1 

**First produce the histograms in AnalysisFramework:**

cd AnalysisFramework

cd run

./hhbbyy H026/Non_Resonant/xxx.js

./hhbbyy H026/Resonant/xxx.js


**== Non-resonant case ==**

all MC samples, nominal selections = Baseline_skimmed_2bjet.js

data samples, nominal selections = Data_skimmed_2bjet.js

data samples, jj events = Data_jj_2bjet.js

data samples, yj events = Data_yj_2bjet.js

yy samples, nominal selections, flavor decomposition = yy_Flavor.js



**== Resonant case ==**

all MC samples(except yy), nominal selections = h026_MGH7_X###tohh.js

data samples, nominal selections = Data_skimmed_2bjet.js

data samples, jj events, before m_yyjj cut = Data_jj_2bjet_m_yyjj.js

data samples, yj events, before m_yyjj cut = Data_yj_2bjet_m_yyjj.js

yy samples, nominal selections = yy.js


## Step 2

**Then scale the data-driven yj and jj by the purities we get from 2x2D sideband method using this package: [HGamBackgroundStudies](https://gitlab.cern.ch/zijia/bbyy_bkg_2x2d/-/tree/master/source/HGamCore/HGamBackgroundStudies).**

**Purities are saved in Nonresonant_purity.root and Resonant_purity.root.**

**In Resonant case, the purities are obtianed before m_yyjj cut to avoid low statistics.**

**The yj(jj) components are scaled to ( MC yy / yy_purity ) * yj(jj)_purity.**

cd AnalysisFramework/utils

**== Non-resonant case ==**

This will produce the new histograms that can be directly used in bbyyPlotter.

./compile.sh ApplySF 

./ApplySF.sh



**== Resonant case ==**

This will print out the SFs to be added By Hand into the new json files.

./compile.sh ApplySF_Resonant

./ApplySF_Resonant.sh



## Step 3 (For resonant case)

**Go to AnalysisFramework and produce the hostograms again using new json files where SFs are applied to the weights.**

**Now nominal cuts are applied, adding m_yyjj cut back.**

data samples, jj events = Data_jj_2bjet.js

data samples, yj events = Data_yj_2bjet.js



## Step 4

**Now we have all the histograms we need. Plot the data/MC plots in bbyyPlotter**

**Modify the "samplesToStack" and "selections" in PlottingList.py, to choose the components to be drawn, then**

python plottingScheduler.py
