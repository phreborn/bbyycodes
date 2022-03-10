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
from XS_func import *

ampl.use_atlas_style()


# YIELD

def gghh_loose_HM(c):
    return (3.686143*c**2-0.895186*c+0.358902)*31.02/31.05

def gghh_tight_HM(c):
    return (11.931959*c**2-1.443647*c+0.874201)*31.02/31.05

def gghh_loose_LM(c):
    return (1.331425*c**2-0.537917*c+0.073610)*31.02/31.05

def gghh_tight_LM(c):
    return (0.769938*c**2-0.337978*c+0.047141)*31.02/31.05


def tthh_loose_HM(c):
    return (4.115418*c**2-2.137455*c+0.358902)*31.02/31.05

def tthh_tight_HM(c):
    return (11.763624*c**2-5.468562*c+0.874203)*31.02/31.05

def tthh_loose_LM(c):
    return (1.162726*c**2-0.539422*c+0.073610)*31.02/31.05

def tthh_tight_LM(c):
    return (0.688946*c**2-0.338800*c+0.047141)*31.02/31.05


def seq(start, stop, step=1):
    n = int(round((stop - start)/float(step)))
    if n > 1:
        return([start + step*i for i in range(n+1)])
    elif n == 1:
        return([start])
    else:
        return([])

# Get the cross sections!
eff_tthh_loose_HM = []
eff_gghh_loose_HM = []

eff_tthh_loose_LM = []
eff_gghh_loose_LM = []

eff_tthh_tight_LM = []
eff_gghh_tight_LM = []

eff_tthh_tight_HM = []
eff_gghh_tight_HM = []

couplings = []

NF = 100/(138965.16*0.002637286)*1000  #fb

for c in seq(-1.2, 1.225, 0.025):
    #if c == 0.1 or c == 0.3 or c == 0.4:
    print(c, " -> ", tthh_tight_HM(c)/xs_ggF_ctthh(c)*NF)


    eff_tthh_loose_HM.append(tthh_loose_HM(c)/xs_ggF_ctthh(c)*NF)        
    eff_gghh_loose_HM.append(gghh_loose_HM(c)/xs_ggF_cgghh(c)*NF)

    eff_tthh_loose_LM.append(tthh_loose_LM(c)/xs_ggF_ctthh(c)*NF)
    eff_gghh_loose_LM.append(gghh_loose_LM(c)/xs_ggF_cgghh(c)*NF)

    eff_tthh_tight_LM.append(tthh_tight_LM(c)/xs_ggF_ctthh(c)*NF)
    eff_gghh_tight_LM.append(gghh_tight_LM(c)/xs_ggF_cgghh(c)*NF)

    eff_tthh_tight_HM.append(tthh_tight_HM(c)/xs_ggF_ctthh(c)*NF)
    eff_gghh_tight_HM.append(gghh_tight_HM(c)/xs_ggF_cgghh(c)*NF )

    couplings.append(c)

print(couplings)
print(eff_tthh_tight_HM)

# Set up figure
#fig= plt.figure(figsize=(8, 6))
#gs = gridspec.GridSpec(4,1)0
#ax = fig.add_subplot(gs[:4,0])

fig, ax = plt.subplots(1,1,figsize=(8,6))

ax.plot(couplings,  eff_tthh_tight_HM, color='#F2385A',label='HM Tight')
ax.plot(couplings,  eff_tthh_loose_HM, color='#36B1BF',label='HM Loose')
ax.plot(couplings,  eff_tthh_tight_LM, color='#FDC536',label='LM Tight') #00CC00
ax.plot(couplings,  eff_tthh_loose_LM, color='#343844',label='LM Loose')

ampl.set_ylabel(r'Acceptance $\times$ Efficiency [%]', fontsize= 20)
ampl.set_xlabel(r'$c_{tthh}$', fontsize=20)
ampl.draw_atlas_label(0.05, 0.95, ax, status = 'int', simulation=True,  energy = '13 TeV', lumi = 139, desc = r'$HH \rightarrow b\bar{b} \gamma \gamma$')

plt.ylim(0,15)
ax.xaxis.set_ticks(np.arange(-1.2, 1.2+0.4, 0.4))
plt.xlim(-1.2, 1.2)

# reorder the legend
handles,labels = ax.get_legend_handles_labels()
ax.legend(handles, labels, loc = 'upper right', fontsize = 'x-small', frameon = False)

plt.savefig('Eff_tthh.pdf',bbox_inches='tight')
#plt.show()
