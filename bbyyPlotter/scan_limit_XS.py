import numpy as np
import math
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import matplotlib.patches as patches
import atlas_mpl_style as ampl
import collections
import json
from XS_func import *

ampl.use_atlas_style()

c = "ctthh"#"klambda" #chhh

processes="ggF"#+VBF"

# limits_json contains coupling value and limit but NOT coupling name, that is contained only in the name of the json.
#limits_json= "scan_"+c+"_all_WS-yybb-nonresonant_HEFT_"+c+"_1D_"+processes+"_v3.json"
#limits_json = "scan_"+c+"_all_WS-yybb-nonresonant_BDT_h026_v7_param_"+processes+".json"
limits_json= "scan_"+c+"_all_WS-yybb-nonresonant_HEFT_"+c+"_1D_"+processes+"_v3_SM_no_unc.json"

name = limits_json.split(".")[0]

#c = c+"_"+processes

limits = json.load(open(limits_json), object_pairs_hook=collections.OrderedDict)
c_value = [float(v) for v in limits.keys()]
limit_bands = {i:[x[i+2] for x in limits.values()] for i in range(-2, 4)}


print("Scanning ",c, " with values:")
print(c_value)


fig = plt.figure(figsize=(8, 6))

gs = gridspec.GridSpec(4,1)

ax = fig.add_subplot(gs[:4,0])

# Get precited xs                                                                                                                                                                                                                           
XS = [dic[c]["XS"](v) for v in c_value]

# Plot Observed and Expected limits 
ax.semilogy(c_value, XS * np.array(limit_bands[3]),'k',label='Observed limit (95% CL)')
ax.semilogy(c_value, XS * np.array(limit_bands[0]),'k--',label='Expected limit (95% CL)')
ax.fill_between(c_value, XS * np.array(limit_bands[-2]), XS * np.array(limit_bands[2]),  facecolor = '#FDC536', label='Expected limit $\pm 2\sigma$')
ax.fill_between(c_value, XS * np.array(limit_bands[-1]), XS * np.array(limit_bands[1]),  facecolor = '#4AD9D9', label='Expected limit $\pm 1\sigma$')


if "lower" in dic[c].keys():
    print("Adding theory band")
    ax.plot(c_value,XS, color = 'darkred', label='Theory prediction') 
    #ax.plot(c_value,[xs_ggF(kl) for kl in c_value],'C4', color = 'darkRed', label='$\kappa_{\lambda}$ theory prediction')
    th_band = ax.fill_between(c_value, [dic[c]["lower"](v) for v in c_value], [dic[c]["upper"](v) for v in c_value],  facecolor = '#F2385A')

else:

    ax.plot(c_value,XS, color = '#F2385A', label='Theory prediction') # 'darkred'                                                             

#border for the legend
border_leg = patches.Rectangle((0, 0), 1, 1, facecolor = 'none', edgecolor = 'black', linewidth = 1)

ylim = dic[c]["y-range"] 

ax.set_ylim(ylim)

# Mark SM prediction
print("X = ",dic[c]["SM"]," Y = ", dic[c]["XS"](dic[c]["SM"]))
 
ax.plot(dic[c]["SM"], dic[c]["XS"](dic[c]["SM"]), linewidth = 0, marker = '*', markersize = 20, color = '#E9F1DF', markeredgecolor = 'black', label = 'SM prediction')

# Obtain expected exclusion range
limitm1 = np.array(limit_bands[0]) - 1
idx = np.argwhere(np.diff(np.sign(limitm1))).flatten()
intersections = [c_value[x] - (c_value[x+1] - c_value[x])/(limitm1[x+1] - limitm1[x]) * limitm1[x] for x in idx]
print ('Expected limits:', intersections)
plt.annotate(r'Expected: '+dic[c]["label"]+'$\in [%.1f, %.1f]$' %(intersections[0], intersections[1]), (0.04, 0.10), xycoords = 'axes fraction', fontsize = 15)

#Obtain observed exclusion range
limitm1 = np.array(limit_bands[3]) - 1
idx = np.argwhere(np.diff(np.sign(limitm1))).flatten()
intersections = [c_value[x] - (c_value[x+1] - c_value[x])/(limitm1[x+1] - limitm1[x]) * limitm1[x] for x in idx]
print ('Observed limits:', intersections)
plt.annotate(r'Observed: '+dic[c]["label"]+'$\in [%.1f, %.1f]$' %(intersections[0], intersections[1]), (0.04, 0.18), xycoords = 'axes fraction', fontsize = 15)

ampl.set_ylabel('$\sigma_{'+processes+'}$ (HH) [fb]', fontsize=20)


#reorder the legend                                                                                                                                                                            
handles,labels = ax.get_legend_handles_labels()

if "lower" in dic[c].keys():
    handles = [handles[0], handles[1], (handles[4], border_leg), (handles[5], border_leg), (th_band, handles[2], border_leg), handles[3]]  #handles[3], handles[4], (th_band, handles[2])]                                             
    labels = [labels[0], labels[1], labels[4], labels[5], labels[2], labels[3]]

else:

    handles = [handles[0], handles[1], (handles[4], border_leg), (handles[5], border_leg), handles[2],  handles[3]]
    labels = [labels[0], labels[1], labels[4], labels[5], labels[2], labels[3]]

# Add final details
ax.legend(handles, labels, loc='upper right', fontsize = 15, frameon = False)

ampl.set_xlabel(dic[c]["label"], fontsize=20)

ampl.draw_atlas_label(0.05, 0.95, ax, status = 'int', energy = '13 TeV', lumi = 139, desc = r'$HH \rightarrow b\bar{b} \gamma \gamma$')

plt.xlim(-1.2, 1.2)#dic[c]["edges"])

fig_name = name+"_scan_XS_v3_SM_no_unc.pdf"

plt.savefig(fig_name)
print(fig_name)
