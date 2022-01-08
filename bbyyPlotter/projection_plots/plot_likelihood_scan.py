# Use this script for plotting likelihood scans (all four systematic scenarios) for klambda = 1 and klambda = 0
# With some simple modififications (included as comments below), this can also produce the likelihood scan with BDT categories

import os
import numpy as np
import pandas as pd
import uproot
import matplotlib.pyplot as plt
import json
import atlas_mpl_style as ampl
import matplotlib.gridspec as gridspec
import matplotlib.patches as patches
import matplotlib.lines as lines
import argparse

# Keyword arguments are input, output, and the desired name of the plot

parser = argparse.ArgumentParser()

parser.add_argument("-i", "--input", help="Input directory")
parser.add_argument("-o", "--output", help="Output directory")
parser.add_argument("-n", "--name", help="Plot name")
args = parser.parse_args()

ampl.use_atlas_style()

plt.rcParams['figure.dpi'] = 100

# Read ROOT files in the format found in /afs/cern.ch/work/a/alwang/public/forJake

def loadROOT(path):
    with uproot.open(path) as nll_output:
        nll = nll_output["nllscan"]["nll"].array(library="np")
        kl = nll_output["nllscan"]["klambda"].array(library="np")
        min_nll = min(nll)
        for num, entry in enumerate(nll):
            nll[num] = 2.0 * (entry - min_nll)
        sorted_pairs = sorted(zip(kl, nll))
        tuples = zip(*sorted_pairs)
    kl, nll = [np.array(tup) for tup in tuples]
    return pd.DataFrame({"kl" : kl, "nll" : nll})

# As a cross-check, this script can also calculate exclusion intervals

def intersections(df, npoints):
    x,y = df['kl'],df['nll'] 
    fx = np.linspace(-2,10,num=npoints)
    fy = np.interp(fx, x, y)

    onesigma = np.linspace(1,1,num=npoints)
    twosigma = np.linspace(4,4,num=npoints)

    idx_onesigma = np.argwhere(np.diff(np.sign(fy - onesigma))).flatten()
    idx_twosigma = np.argwhere(np.diff(np.sign(fy - twosigma))).flatten()
    return fx[idx_onesigma],fx[idx_twosigma]

input_path = args.input

# Change the following paths to match the correct path for each systematic scenario

statOnly_path = input_path + '/scan_klambda_statonly_WS-yybb-nonresonant_BDT_h026_v7_3000ifb_param_mu.root/output.root'
baseline_path = input_path + '/scan_klambda_all_WS-yybb-nonresonant_BDT_h026_v7_3000ifb_param_mu.root/output.root'
halfTheo_path = input_path + '/scan_klambda_all_WS-yybb-nonresonant_BDT_h026_v9_3000ifb_Reducethsyst_param_mu_asimovData/output.root'
run2sys_path  = input_path + '/scan_klambda_all_WS-yybb-nonresonant_BDT_h026_v9_3000ifb_Run2syst_param_mu_asimovData/output.root'

df_statOnly = loadROOT(statOnly_path)
df_baseline = loadROOT(baseline_path)
df_halfTheo = loadROOT(halfTheo_path)
df_run2sys  = loadROOT(run2sys_path)

# Set up figure
fig = plt.figure(figsize=(8, 6))

# Specify colors and markers for each scenario (HH color scheme)

DataList = [df_statOnly, df_baseline,df_halfTheo, df_run2sys]
colorList = ['#343844','#f2385a','#fdc536','#36b1bf']
lstyle = ['P-','o-','s-','d-']

# If you are plotting the likelihood scan with BDT categories, use the following lines instead to load files and specify colors
 
# all_path = input_path + '/scan_klambda_all_WS-yybb-nonresonant_BDT_h026_v7_3000ifb_param_mu.root/output.root'
# SM_path = input_path + '/scan_klambda_all_WS-yybb-nonresonant_BDT_h026_v7_3000ifb_param_mu_SM.root/output.root'
# BSM_path = input_path + '/scan_klambda_all_WS-yybb-nonresonant_BDT_h026_v7_3000ifb_param_mu_BSM.root/output.root'

# load data in dataframes 
# df_all = loadROOT(all_path)
# df_SM = loadROOT(SM_path)
# df_BSM = loadROOT(BSM_path)

# DataList = [df_all, df_SM, df_BSM]
# colorList = ['#343844','#f2385a','#fdc536']
# lstyle = ['P-','o-','s-']

for i in range(len(DataList)):
    plt.plot(DataList[i]['kl'], DataList[i]['nll'], lstyle[i], c = colorList[i], markersize=4)

ax = plt.gca()
ax.set_xlim(-12,10)
ax.set_ylim(0,10)
plt.xticks(np.arange(-12,12,2))
plt.yticks(np.arange(0,13,2))

# Plot horizontal lines at sigma = 1 and sigma = 4 for all likelihood scans

ax.axhline(1, color="grey", linestyle="--")
ax.axhline(4, color="grey", linestyle="--")

ampl.set_ylabel("-2$\Delta$ln(L)",fontsize= 20)
ampl.set_xlabel("$\mathrm{\kappa_\lambda}$", fontsize= 20)

border_leg = patches.Rectangle((0, 0), 1, 1, facecolor = 'none', edgecolor = 'black', linewidth = 1)

handles,labels = ax.get_legend_handles_labels()

ampl.draw_atlas_label(0.05, 0.95, ax, status = 'prelim', energy = '14 TeV', lumi = 3000, desc = r"$HH \rightarrow$ $\mathrm{b\overline{b}\gamma\gamma}$ \\ Projection from Run 2 data", fontsize = 14)
plt.axhline(y=1., color='0.8', linestyle='--')
plt.axhline(y=4., color='0.8', linestyle='--')
l1 = ax.legend(handles[0:2]+handles[5:], labels[0:2]+labels[5:], loc=(0.52,0.62),fontsize = 12, frameon = False)
ax.add_artist(l1)

line1 = lines.Line2D([],[],color="#343844",label=r'No syst. unc.',linestyle="-",marker='P')
line2 = lines.Line2D([],[],color="#F2385A",label=r'Baseline',linestyle="-",marker='o')
line3 = lines.Line2D([],[],color="#FDC536",label=r'Theoretical unc. halved',linestyle="-",marker='s')
line4 = lines.Line2D([],[],color="#36B1BF",label=r'Run 2 syst. unc.',linestyle='-',marker='d')

fig.legend(bbox_to_anchor=(0.3, 0.67), loc='upper center',fontsize = 12 ,handles=[line1,line2,line3,line4], frameon = False)

# If you are plotting the likelihood scan with BDT categories, use the following lines instead

# line1 = lines.Line2D([],[],color="#343844",label=r'All categories',linestyle="-",marker='P')
# line2 = lines.Line2D([],[],color="#F2385A",label=r'High mass categories',linestyle="-",marker='o')
# line3 = lines.Line2D([],[],color="#FDC536",label=r'Low mass categories',linestyle="-",marker='s')

# fig.legend(bbox_to_anchor=(0.3, 0.67), loc='upper center',fontsize = 12 ,handles=[line1,line2,line3], frameon = False)

# Save the plot to the specified directory and name; we typically use nll_kl1p0.pdf (resp. nll_kl10p0.pdf) for this one

plt.savefig(args.output + "/" + args.name + ".pdf")

# If you are cross-checking exclusion intervals, uncomment the following lines to output the results

# npoints = 2000

# fx_statOnly_sigma1,fx_statOnly_sigma2 = intersections(df_statOnly, npoints)
# fx_baseline_sigma1,fx_baseline_sigma2 = intersections(df_baseline, npoints)
# fx_halfTheo_sigma1,fx_halfTheo_sigma2 = intersections(df_halfTheo, npoints)
# fx_run2sys_sigma1,fx_run2sys_sigma2   = intersections(df_run2sys, npoints)

# print("statOnly: 1 sigma interval: {} , 2 sigma interval: {}".format(fx_statOnly_sigma1,fx_statOnly_sigma2))
# print("baseline: 1 sigma interval: {} , 2 sigma interval: {}".format(fx_baseline_sigma1,fx_baseline_sigma2))
# print("halfTheo: 1 sigma interval: {} , 2 sigma interval: {}".format(fx_halfTheo_sigma1,fx_halfTheo_sigma2))
# print("run2sys:  1 sigma interval: {} , 2 sigma interval: {}".format(fx_run2sys_sigma1,fx_run2sys_sigma2))
