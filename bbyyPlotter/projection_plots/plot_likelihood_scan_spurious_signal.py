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

parser = argparse.ArgumentParser()

parser.add_argument("-i", "--input", help="Input directory")
parser.add_argument("-o", "--output", help="Output directory")
parser.add_argument("-n", "--name", help="Plot name")
args = parser.parse_args()

ampl.use_atlas_style()

plt.rcParams['figure.dpi'] = 100

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

def intersections(df, npoints):
    x,y = df['kl'],df['nll'] #
    fx = np.linspace(-2,10,num=npoints)
    fy = np.interp(fx, x, y)

    onesigma = np.linspace(1,1,num=npoints)
    twosigma = np.linspace(4,4,num=npoints)

    idx_onesigma = np.argwhere(np.diff(np.sign(fy - onesigma))).flatten()
    idx_twosigma = np.argwhere(np.diff(np.sign(fy - twosigma))).flatten()
    return fx[idx_onesigma],fx[idx_twosigma]

input_path = args.input

# Change the following paths to match the correct path for each systematic scenario

ssBaseline = input_path + '/scan_klambda_all_WS-yybb-nonresonant_BDT_h026_v8_3000ifb_param_mu.root/output.root'
ss1 = input_path + '/scan_klambda_SS1_WS-yybb-nonresonant_BDT_h026_v8_3000ifb_param_mu.root/output.root'
ss2  = input_path + '/scan_klambda_SS2_WS-yybb-nonresonant_BDT_h026_v8_3000ifb_param_mu.root/output.root'
ss4 = input_path + '/scan_klambda_SS4_WS-yybb-nonresonant_BDT_h026_v8_3000ifb_param_mu.root/output.root'
ss10 = input_path + '/scan_klambda_SS10_WS-yybb-nonresonant_BDT_h026_v8_3000ifb_param_mu.root/output.root'
ss20  = input_path + '/scan_klambda_SS20_WS-yybb-nonresonant_BDT_h026_v8_3000ifb_param_mu.root/output.root'
ssRun2  = input_path + '/scan_klambda_SSRun2_WS-yybb-nonresonant_BDT_h026_v9_3000ifb_param_mu_asimovData_kl1p0/output.root'

# Load data in dataframes 

df_baseline = loadROOT(ssBaseline)
df_ss1 = loadROOT(ss1)
df_ss2 = loadROOT(ss2)
df_ss4 = loadROOT(ss4)
df_ss10 = loadROOT(ss10)
df_ss20 = loadROOT(ss20)
df_ssRun2 = loadROOT(ssRun2)

# Set up figure
fig = plt.figure(figsize=(8, 6))

# Specify colors and markers, following the HH color scheme

DataList = [df_baseline, df_ss1, df_ss2, df_ss4, df_ss10, df_ss20, df_ssRun2]
colorList = ['#343844','#f2385a','#fa7e61','#fdc536','#047cbc','#36b1bf','#4ad9d9']
lstyle = ['-P','-o','-s','-d','-x','-h','-8']

# Create plots

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

line1 = lines.Line2D([], [], color="#343844", label=r'0 $\times$ Run 2 spurious signal', marker='P')
line2 = lines.Line2D([], [], color="#f2385a", label=r'1 $\times$ Run 2 spurious signal', marker='o')
line3 = lines.Line2D([], [], color="#fa7e61", label=r'2 $\times$ Run 2 spurious signal', marker='s')
line4 = lines.Line2D([], [], color="#fdc536", label=r'4 $\times$ Run 2 spurious signal', marker='d')
line5 = lines.Line2D([], [], color="#047cbc", label=r'10 $\times$ Run 2 spurious signal', marker='x')
line6 = lines.Line2D([], [], color="#36b1bf", label=r'20 $\times$ Run 2 spurious signal', marker='h')
line7 = lines.Line2D([], [], color="#4ad9d9", label=r'25 $\times$ Run 2 spurious signal', marker='8')

fig.legend(bbox_to_anchor=(0.32, 0.7), loc='upper center',fontsize = 12 ,handles=[line1,line2,line3,line4,line5,line6,line7], frameon = False)

# Save the plot to the specified directory and name; we typically use nll_spurious_signal.pdf for this one

plt.savefig(args.output + "/" + args.name + ".pdf")
