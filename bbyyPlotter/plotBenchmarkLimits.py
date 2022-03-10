#!/usr/bin/env python

import os
import numpy as np
#import atlas_mpl_style as ampl
import pandas as pd
import json
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import matplotlib.patches as patches
import matplotlib.lines as lines
import atlas_mpl_style as ampl

ampl.use_atlas_style()

sf  = 1000 #fb

benchmarks = ["0", "1", "2", "3", "4", "5", "6", "7"]
benchmarks_name = ["SM", "1", "2", "3", "4", "5", "6", "7"]
#for benchmark in benchmarks:
#    loadLimits(benchmark)
f = open('ggF_HH_HEFT_Benchmarks_v3.json')
data = json.load(f)

#### Plotting now ####

fig, ax = plt.subplots(1,1,figsize=(8,6))

eps=0.3


for bm in benchmarks:    
    pos = int(bm)
    print("-2sigma: ",data[bm][1]," +2sigma ",  data[bm][5])

    ax.fill_between([pos-eps,pos+eps], np.array(data[bm][1])*sf, np.array(data[bm][5])*sf,  facecolor = '#FDC536', label='Expected limit $\pm 2\sigma$')
    ax.fill_between([pos-eps,pos+eps], np.array(data[bm][2])*sf, np.array(data[bm][4])*sf,  facecolor = '#4AD9D9', label='Expected limit $\pm 1\sigma$')

    ax.scatter(x=bm,y=data[bm][3]*sf, edgecolors='black', facecolors='none', label='Expected limit (95% CL)')
    ax.scatter(x=bm,y=data[bm][0]*sf, color='black', label='Observed limit (95% CL)')

#ax.plot( [-0.5,7.5],[31.02, 31.02], color= '#F2385A', label=r'$\sigma^{\mathrm{SM}}_{\mathrm{ggF\, HH}}$')
ax.set_yscale("log")
ax.set_xlim(-0.5,7.5)
ax.set_ylim(20,3000) 
ax.set_xticks(np.arange(0,8,1))
ax.set_xticklabels(benchmarks_name)

ampl.draw_atlas_label(0.06, 0.95, ax, status = 'int', energy = '13 TeV', lumi = 139, desc = r"$HH \rightarrow$ $\mathrm{b\bar{b} \gamma \gamma}$")
ampl.set_ylabel("$\sigma_{\mathrm{ggF}}$ (HH) [fb]",fontsize= 20)
ampl.set_xlabel("Shape benchmark", fontsize= 20)

handles,labels = ax.get_legend_handles_labels()
handles = [handles[3], handles[2], handles[1], handles[0]]
labels  = [labels[3], labels[2], labels[1], labels[0]]


l1 = ax.legend(handles, labels,loc=(0.51,0.68),fontsize = 15, frameon = False)
plt.gca().add_artist(l1)
plt.savefig("HEFTbenchmarks.pdf")
print("Saved figure as HEFTbenchmarks.pdf")

plt.show();
