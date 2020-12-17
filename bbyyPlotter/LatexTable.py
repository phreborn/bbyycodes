'''
Script to make a latex table from the yield.js file, output of AnalysisFramework YieldIterator.

Created by laura.pereira.sanchez@cern.ch 

'''
import os
import sys
import ROOT as r
from array import array
import collections
from math import sqrt
from PyPlotter import *
from histoDictionary import *
from PlottingList import *
import json
import argparse,shlex

parser = argparse.ArgumentParser()
parser.add_argument("-p", "--path", help="path to income json file", default="../AnalysisFramework/run/")
parser.add_argument("-n", "--name", help="name of income json file", default="yields.js")
parser.add_argument("-o", "--output", help="path to output", default="")
parser.add_argument("-SH", "--separateSingleHiggs", help="separate single Higgs backgrounds", action="store_true", default=True)
parser.add_argument("-yyjj", "--separateyyjets", help="separate di-photon + jets backgrounds", action="store_true", default=False)
parser.add_argument("-ttyy", "--mergettyy", help="merge ttbar di-photon backgrounds", action="store_false", default=False)
parser.add_argument("-d", "--decimals", help="Number of decimals to round to", default=3)


opts = parser.parse_args()

separateHiggsBackgrounds = opts.separateSingleHiggs
separateyyjetsBackgrounds = opts.separateyyjets
mergettyyBackgrounds = opts.mergettyy

File = opts.path+opts.name
out = opts.output
n = opts.decimals

# Single Higgs backgrounds
SingleHiggs = ['ggH', 'VBF','WpH','WmH','ZH','ggZH','ttH','bbH','tWH','tHjb']

yyjets = ['yyjj'] 

ttyy = ['ttyy_had', 'ttyy_nohad']

print("Generating latex table from "+File)

Bkg = []
Reg = []
columns = ""
F = open(File, "r") 
yields = json.load(F)

for i in yields.keys():    
    Bkg.append(i)
n_bkg =  len(Bkg)

for j in yields[Bkg[0]].keys():
    Reg.append(j)
    columns+="l"

n_reg = len(Reg)

Total_SM = []
Total_SM_unc = []

for r in Reg:
    SM = 0
    SM_unc = 0
    for b in Bkg:
        SM += yields[b][r][0]
        SM_unc += yields[b][r][1]**2
    Total_SM.append(SM)
    Total_SM_unc.append(sqrt(SM_unc))

if not separateyyjetsBackgrounds:
    yyjets, yyjets_unc, NojjyyBkg =  MergeBackgrounds(yyjets, Reg, Bkg, yields)
    Bkg = NojjyyBkg

if mergettyyBackgrounds:
    ttyy, ttyy_unc, NottyyBkg = MergeBackgrounds(ttyy, Reg, Bkg, yields)
    Bkg = NottyyBkg

if not separateHiggsBackgrounds:
    SingleH, SingleH_unc, NoHBkg =  MergeBackgrounds(SingleHiggs, Reg, Bkg, yields)

##################################
# Writting latex file
#################################

Tex = open(out+"YieldTable.tex", "w")
Tex.write("\n \\begin{table} \n \\begin{center} \n \setlength{\\tabcolsep}{0.0pc} \n \\begin{tabular*}{\\textwidth}{@{\extracolsep{\\fill}}l"+columns+"} \n \\noalign{\smallskip}\hline\\noalign{\smallskip} \n {\\bf Yield Table} ")


# Header line
for r in Reg:
    reg_name = r.replace("_","\\_")
    Tex.write(" & "+reg_name)
Tex.write(" \\\ \n \\noalign{\smallskip}\hline\\noalign{\smallskip}")

# Main body
if not separateHiggsBackgrounds: Bkg = NoHBkg
for b in Bkg:
    bkg_name = b.replace("_"," ")
    Tex.write(" \n "+bkg_name+" ")
    for r in Reg:
        Tex.write(" & $"+str(round(yields[b][r][0],n))+" \pm "+str(round(yields[b][r][1],n))+"$ ")
    Tex.write(" \\\ ")

if mergettyyBackgrounds:
    Tex.write(" \n ttyy ")
    for r in Reg:
        Tex.write(" & $"+str(round(ttyy[Reg.index(r)],n))+" \pm "+str(round(ttyy_unc[Reg.index(r)],n))+"$ ")
    Tex.write(" \\\ ")

if not separateHiggsBackgrounds: 
    Tex.write(" \n Single Higgs ")
    for r in Reg:
        Tex.write(" & $"+str(round(SingleH[Reg.index(r)],n))+" \pm "+str(round(SingleH_unc[Reg.index(r)],n))+"$ ")
    Tex.write(" \\\ ")

if not separateyyjetsBackgrounds:
    Tex.write(" \n yy+jets ")
    for r in Reg:
        Tex.write(" & $"+str(round(yyjets[Reg.index(r)],n))+" \pm "+str(round(yyjets_unc[Reg.index(r)],n))+"$ ")
    Tex.write(" \\\ ")

Tex.write(" \hline ")                                                               
Tex.write(" \n Total SM ")
for r in Reg:
    Tex.write(" & $"+str(round(Total_SM[Reg.index(r)],n))+" \pm "+str(round(Total_SM_unc[Reg.index(r)],n))+"$ ")
Tex.write(" \\\ ")
if "data" in Bkg:
    Tex.write(" \n Data ")
    for r in Reg:
        Tex.write(" & $"+str(round(yields["data"][r][0],n))+" \pm "+str(round(yields["data"][r][1],n))+"$ ")
    Tex.write(" \\\ ")


# Finish up                                                                
Tex.write("\n \\noalign{\smallskip}\hline\\noalign{\smallskip} \n \end{tabular*} \n \end{center}")
# Tex.write("\n \\caption{Yield Table for "+histo.replace("_","\_")+" in the different regions} \n \label{YieldTable_"+histo.replace("_","\_")+"}")
Tex.write("\n  \end{table}")
print ("Done!")
print("Output written to YieldTable.tex")

