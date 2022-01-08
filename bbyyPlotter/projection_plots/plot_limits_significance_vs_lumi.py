import numpy as np
import math
import sys
import matplotlib.pyplot as plt
import matplotlib.ticker
from matplotlib.ticker import NullFormatter
import matplotlib.gridspec as gridspec
import atlas_mpl_style as ampl
import collections
from collections import defaultdict
import json
import argparse

parser = argparse.ArgumentParser()

# As a keyword argument, specify whether you are plotting lumi vs. limits or lumi vs. significances

parser.add_argument("-t", "--type", choices=['limits', 'significances'], help="Specify limits or significances")
parser.add_argument("-n", "--name", help="Plot name")

args = parser.parse_args()

ampl.use_atlas_style()

# Setup plot 
fig = plt.figure(figsize=(8, 6))
gs = gridspec.GridSpec(4,1)
ax = fig.add_subplot(gs[:4,0])

lumi_values = [1000, 1500, 2000, 2500, 3000]

# Input your limits/significances (in ascending order of lumi)

# Most recent limit values

stat_only = [1.5500911474029697, 1.2417526212924526, 1.0624323061741365, 0.9430312502688855, 0.8554440246147544]
hl_lhc = [1.6228677398018967, 1.3133443272361192, 1.1350484045098375, 1.0158301450281915, 0.9295421574664217]
theory_uncert = [2.1635752025667694, 1.9530283925971155, 1.84453751125015, 1.7785322991414136, 1.7342514271331009]
run2_uncert = [2.3486880932999528, 2.129109124981229, 2.0158565699713793, 1.946894433045926, 1.9005538482146656]

# Most recent significance values

# stat_only = [1.3485768173785468, 1.650926304056646, 1.9063258744856835, 2.131337631443774, 2.3347636075727016]
# hl_lhc = [1.315028146884455, 1.5885845140913322, 1.8098835435500074, 1.9960076141066114, 2.1563412314855697]
# theory_uncert = [0.9259180908560997, 1.01248533722427, 1.0669853437067216, 1.1048496194989967, 1.132094409826189]
# run2_uncert = [0.9032809768752215, 0.9829969209339215, 1.0318626414813181, 1.0660809587393154, 1.0901662039174105]

# Specify color scheme

DFs = [stat_only, hl_lhc, theory_uncert, run2_uncert]
colorList = ['#343844','#f2385a','#fdc536','#36b1bf']
lstyle = ['P-','o-','s-','d-']

for i in range(len(DFs)):
    plt.plot(lumi_values, DFs[i], lstyle[i], c = colorList[i], markersize=4)

ax.set_xlim([800, 3200])
ax.set_ylim([0.7, 3.5])

ax.set_xticks(np.arange(1000, 3500, step=500))
ax.set_yticks(np.arange(1, 4, step=1))

border_leg = patches.Rectangle((0, 0), 1, 1, facecolor = 'none', edgecolor = 'black', linewidth = 1)

handles,labels = ax.get_legend_handles_labels()

l1 = ax.legend(handles[0:2]+handles[5:], labels[0:2]+labels[5:], loc=(0.52,0.62),fontsize = 12, frameon = False)
plt.gca().add_artist(l1)

line1 = lines.Line2D([],[],color="#343844",label=r'No syst. unc.',linestyle="-",marker='P')
line2 = lines.Line2D([],[],color="#F2385A",label=r'Baseline',linestyle="-",marker='o')
line3 = lines.Line2D([],[],color="#FDC536",label=r'Theoretical unc. halved',linestyle="-",marker='s')
line4 = lines.Line2D([],[],color="#36B1BF",label=r'Run 2 syst. unc.',linestyle='-',marker='d')

# Based on the input type, print the correct axis labels

if args.type == "limits":
    ampl.set_ylabel('95\% CL Upper Limit on Signal Strength', fontsize=18)
elif args.type == "significances":
    ampl.set_ylabel('Significance [$\sigma$]', fontsize=18)
else:
    sys.exit("Error message")
    
ampl.set_xlabel('Integrated Luminosity [$fb^{-1}$]', fontsize=18)
ampl.draw_atlas_label(0.05, 0.95, ax, status = 'prelim', energy = '14 TeV $\phantom{\textsf{{fb}}^{{-1}}}$', desc = r"$HH \rightarrow$ $\mathrm{b\overline{b}\gamma\gamma}$ \\ Projection from Run 2 data", fontsize = 14)

fig.legend(bbox_to_anchor=(0.70, 0.85), loc='upper center',fontsize = 12 ,handles=[line1,line2,line3,line4], frameon = False)

# Save the plot to the specified directory and name; we typically use limits_vs_lumi.pdf (resp. significance_vs_lumi.pdf) for this one

plt.savefig(args.output + "/" + args.name + ".pdf")
