# Method to add data-driven yj+jj into data/MC plots

## Step 1 

**First produce the histograms in AnalysisFramework:**

```
cd AnalysisFramework

cd run

./hhbbyy H026/Bkg_decomp/Non_Resonant/xxx.js

./hhbbyy H026/Bkg_decomp/Resonant/xxx.js
```

**== Non-resonant case ==**

all MC samples, nominal selections = Baseline_skimmed_2bjet.js

data samples, nominal selections = Data_skimmed_2bjet.js

yy samples, nominal selections, flavor decomposition = yy_Flavor.js



**== Resonant case ==**

all MC samples(except yy), nominal selections = h026_MGH7_X###tohh.js

data samples, nominal selections = Data_skimmed_2bjet.js

data samples, remove m_yyjj cut = Data_m_yyjj.js

yy samples, nominal selections = yy.js

yy samples, remove m_yyjj cut = yy_m_yyjj.js

ttyy samples, remove m_yyjj cut = ttyy_m_yyjj.js

*newly added resonant mass points use yybb_btag77_cutFlow instead of yybb_btag77_BCal_cutFlow, so they use the files in new_mX/*


## Step 2

**Then construct the data-driven yj and jj and yy by the purities we get from 2x2D sideband method using this package: [HGamBackgroundStudies](https://gitlab.cern.ch/zijia/bbyy_bkg_2x2d/-/tree/master/source/HGamCore/HGamBackgroundStudies).**

Purities are saved in Nonresonant_purity.root and Resonant_purity.root.

**In Resonant case, the purities are obtianed before m_yyjj cut to avoid low statistics.**

Now we are using MC yy shape as the basis, and scale it respectiely to be the new yj, jj, yy. Therefore we do not rely on NTNI(N=not, T=tight identification, I=isolation) data with low statistics, avoiding statistical fluctuations.

Scale factors are estimated from SB:

SF_yy = ( purity_yy * Data SB - ttyy SB ) / MC_yy SB

SF_yj = purity_jy * Data SB / MC_yy SB

SF_jj = purity_jj * Data SB / MC_yy SB


`cd AnalysisFramework/utils`

**== Non-resonant case ==**

This will produce the new histograms that can be directly used in bbyyPlotter.

```
./compile.sh ApplySF

./ApplySF.sh
```

**== Resonant case ==**

This will produce the new histograms that can be directly used in bbyyPlotter.

```
./compile.sh ApplySF_Resonant

./ApplySF_Resonant.sh
```

## Step 3

**Now we have all the histograms we need. Plot the data/MC plots in bbyyPlotter**

Modify the "samplesToStack" and "selections" in PlottingList.py, to choose the components to be drawn, then

`python plottingScheduler.py`

some examples are: PlottingList_NonRes.py PlottingList_m_yyjj.py PlottingList_Res.py
