import os
import numpy as np
import pandas as pd
import json
import matplotlib.pyplot as plt
import atlas_mpl_style as ampl
import matplotlib.gridspec as gridspec
import matplotlib.patches as patches
import matplotlib.lines as lines
import argparse

parser = argparse.ArgumentParser()

# Keyword arguments are input, output, and the desired name of the plot

parser.add_argument("-i", "--input", help="Input directory")
parser.add_argument("-o", "--output", help="Output directory")
parser.add_argument("-n", "--name", help="Plot name")
args = parser.parse_args()

ampl.use_atlas_style()

plt.rcParams['figure.dpi'] = 100

def loadJSON(path):
    with open(path,'r') as f:
         nll = json.load(f)
    # Put in dataframe
    df = pd.DataFrame(nll)
    df = df.T.reset_index()
    df = df.rename(columns={"index": "kl", "dnll": "nll"})
    return df[["kl", "significance"]].astype({'kl': 'float64'})

# Change the following paths to match the correct path for each systematic scenario

input_path = args.input

statOnly_path = input_path + '/scan_WS-yybb-nonresonant_BDT_h026_v9_3000ifb_param_mu_sig_statonly/results.json'
baseline_path = input_path + '/scan_WS-yybb-nonresonant_BDT_h026_v9_3000ifb_param_mu_sig_syst/results.json'
halfTheo_path = input_path + '/scan_WS-yybb-nonresonant_BDT_h026_v9_3000ifb_Reducethsyst_param_mu_sig_syst/results.json'
run2sys_path  = input_path + '/scan_WS-yybb-nonresonant_BDT_h026_v9_3000ifb_Run2syst_param_mu_sig_syst/results.json'

#load data in dataframes 

df_statOnly = loadJSON(statOnly_path)
df_baseline = loadJSON(baseline_path)
df_halfTheo = loadJSON(halfTheo_path)
df_run2sys  = loadJSON(run2sys_path)

# Set up figure

fig = plt.figure(figsize=(8, 6))

#df.plot(x="kl",y="nll",legend=None, use_index=True)

# Specify colors and markers for each scenario (HH color scheme)

DFs = [df_statOnly,df_baseline,df_halfTheo,df_run2sys]
colorList = ['#343844','#f2385a','#fdc536','#36b1bf']
lstyle = ['P-','o-','s-','d-']

# Add a vertical line at klambda = 1 for consistency with bbtautau

plt.axvline(x=1., color='0.8', linestyle='-')

# Plot all scenarios

for i in range(len(DFs)):
    plt.plot(DFs[i]['kl'], DFs[i]['significance'], lstyle[i],  c=colorList[i], markersize=4)

# ax.set_xticklabels([-2,10,40])

ax = plt.gca()
ax.set_xlim(-2,8)
ax.set_ylim(0,12)
plt.xticks(np.arange(-2,10,2))
plt.yticks(np.arange(1,13,2))

# Add horizontal lines to mark sigma = 3 and sigma = 5 in the significance scan

ax.axhline(3, color="grey", linestyle="--")
ax.axhline(5, color="grey", linestyle="--")

ampl.set_ylabel("Significance [$\mathrm{\sigma}$]",fontsize= 20)
ampl.set_xlabel("$\mathrm{\kappa_\lambda}$", fontsize= 20)

border_leg = patches.Rectangle((0, 0), 1, 1, facecolor = 'none', edgecolor = 'black', linewidth = 1)

handles,labels = ax.get_legend_handles_labels()

ampl.draw_atlas_label(0.4, 0.95, ax, status = 'prelim', energy = '14 TeV', lumi = 3000, desc = r"$HH \rightarrow$ $\mathrm{b\overline{b}\gamma\gamma}$ \\ Projection from Run 2 data", fontsize = 15)

plt.axhline(y=3., color='0.8', linestyle='--')
plt.axhline(y=5., color='0.8', linestyle='--')
l1 = ax.legend(handles[0:2]+handles[5:], labels[0:2]+labels[5:], loc=(0.52,0.62),fontsize = 12, frameon = False)
plt.gca().add_artist(l1)

# Same color scheme as above for the legend

line1 = lines.Line2D([],[],color="#343844",label=r'No syst. unc.',linestyle="-",marker='P')
line2 = lines.Line2D([],[],color="#F2385A",label=r'Baseline',linestyle="-",marker='o')
line3 = lines.Line2D([],[],color="#FDC536",label=r'Theoretical unc. halved',linestyle="-",marker='s')
line4 = lines.Line2D([],[],color="#36B1BF",label=r'Run 2 syst. unc.',linestyle='-',marker='d')

fig.legend(bbox_to_anchor=(0.575, 0.67), loc='upper center',fontsize = 12 ,handles=[line1,line2,line3,line4], frameon = False)

# Save the plot to the specified directory and name; we typically use significance_vs_klambda.pdf for this one

plt.savefig(args.output + "/" + args.name + ".pdf")
