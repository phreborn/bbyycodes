#Here you can find the instructions on how to use the modelling scripts.

##For questions, please contact valentina.maria.cairo@cern.ch & jannicke.pearkes@cern.ch


Same setup used for the other scripts, i.e. from the AnalysisFramework folder:

```bash
setupATLAS

source setup.sh
```

Create the following symlink:
```bash
ln -s -T path_to_your_input_files  data
```
A set of inputs files you can use currently exists here: /afs/cern.ch/work/v/vcairo/public/bbyyHistos_March31/

(for the checks on the negative weights, use: /afs/cern.ch/work/v/vcairo/public/bbyyHistos_March31/plots_checkNegativeWeights)

To run binned fit on myy: 
```bash
root -l "Modelling_bbyy.C(\"projects/HHbbyy/signalModels/HH/config/v1_myy/\",true)" -q -b 
```


To run binned fit on mjj:
```bash
root -l "Modelling_bbyy_mjj.C(\"projects/HHbbyy/signalModels/HH/config/v1_mjj/\",true)" -q -b
```


To run unbinned fit on myy: 
```bash
root -l "Modelling_bbyy.C(\"projects/HHbbyy/signalModels/HH/config/v1/\",false)" -q -b 
```

To run unbinned fit on mjj:
```bash
root -l "Modelling_bbyy_mjj.C(\"projects/HHbbyy/signalModels/HH/config/v1_mjj/\",false)" -q -b
```




