Scripts written (or adapted from other scripts) by David Wendt, 
a 2020 summer undergraduate student.


#`hist_to_json.py`

Description:
Reads signal and background histograms from the
path specified in the file and writes them to jsons
along with a json containing yields and signal/background.

Original file is `hist_to_json.py`. Two new files replace this 
depending on usage. `hist_to_json_VBF_only.py` processes the 
histograms by only using the VBF category and only using VBF
for signal, while `hist_to_json_ggF_sig.py` has ggF included
in signal as well, with the choice to use either 5 categories 
(with VBF) or 4 categories (without VBF).

Instructions:
```
setupATLAS
lsetup "root 6.20.06-x86_64-centos7-gcc8-opt"
python hist_to_json*.py
```
where `hist_to_json*.py` refers either to `hist_to_json_VBF_only.py`
or `hist_to_json_ggF_sig.py`.

#`c2v_scan.py`

Description:
Reads the signal and background json histograms written
by `hist_to_json.py` and uses pyhf to calculate upper limits,
then plots the upper limits along with the theory line.

Instructions:
```
python c2v_scan.py
```

#`plot_xsecs_sb.py`

Description:
Plots the theory cross-sections and the signal to background
ratio as functions of c2v (on the same plot with dual y axes).

Instructions:
```
python plot_xsecs_sb.py
```

#`plot_cutflow.C`

Description:
Reads and plots cut-flow from signal and background root files. 

Instructions:
```
setupATLAS
lsetup "root 6.20.06-x86_64-centos7-gcc8-opt"
asetup 21.2.113,AnalysisBase
root plot_cutflow.C
```
