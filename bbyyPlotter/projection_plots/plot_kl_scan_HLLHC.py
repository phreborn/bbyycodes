#modified from https://gitlab.cern.ch/hartman/dihiggs4b/blob/master/PFlow-Topo/Limit-Comparisons.ipynb by Nicole Hartman
#requires python3 to use atlas_mpl_style

import numpy as np
import math
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import matplotlib.patches as patches
import matplotlib.lines as lines
import atlas_mpl_style as ampl
import collections
import json

ampl.use_atlas_style()

#Now using values from LHCWHGHHHXGGBGGGXXX
SCALE_GGF = 31.02/31.0358 * 0.03665 / 0.03102 * 36.69 / 36.65  #correct to xs at mH = 125.00, 14TeV 
SCALE_VBF = 1.723/(4.581-4.245+1.359) * 2.052 / 1.723 * 2.055 / 2.052

def xs_ggF(kl):
    #https://twiki.cern.ch/twiki/bin/view/LHCPhysics/LHCHWGHH?redirectedfrom=LHCPhysics.LHCHXSWGHH#Latest_recommendations_for_gluon
    return (70.3874-50.4111*kl+11.0595*kl**2) * SCALE_GGF #XS in fb

def xs_VBF(kl):
    #https://indico.cern.ch/event/995807/contributions/4184798/attachments/2175756/3683303/VBFXSec.pdf
    return (4.581-4.245*kl+1.359*kl**2) * SCALE_VBF

def xs_HH(kl):
    return xs_ggF(kl) + xs_VBF(kl)

# When adding 2 independent Gaussians (e.g. ggF and VBF XS) we can simply add their means and add their sigmas in quadrature
def sigma_upper_ggF(kl):
    #https://twiki.cern.ch/twiki/bin/view/LHCPhysics/LHCHWGHH?redirectedfrom=LHCPhysics.LHCHXSWGHH#Latest_recommendations_for_gluon
    #add the std on ggF HH due to qcd scale, PDF, and mtop in quadrature
    #return xs_ggF(kl) * math.sqrt((max(72.0744-51.7362*kl+11.3712*kl**2, 70.9286-51.5708*kl+11.4497*kl**2) * SCALE_GGF / xs_ggF(kl) - 1)**2 + 0.03**2 + 0.026**2)
    #new mtop uncertainty:
    return xs_ggF(kl) * math.sqrt((max(76.6075 - 56.4818*kl + 12.635*kl**2, 75.4617 - 56.3164*kl + 12.7135*kl**2) * SCALE_GGF / xs_ggF(kl) - 1)**2 + 0.03**2)
    
def sigma_upper_VBF(kl):
    #from klambda = 1
    return xs_VBF(kl) * math.sqrt(0.0003**2 + 0.021**2)

def sigma_upper_HH(kl):
    return math.sqrt(sigma_upper_ggF(kl)**2 + sigma_upper_VBF(kl)**2)
    
def xs_upper_HH(kl):
    return xs_HH(kl) + sigma_upper_HH(kl) / 2 #reduced factor of 0.5 @ HL-LHC

def sigma_lower_ggF(kl):
    #https://twiki.cern.ch/twiki/bin/view/LHCPhysics/LHCHWGHH?redirectedfrom=LHCPhysics.LHCHXSWGHH#Latest_recommendations_for_gluon
    #add the std on ggF HH due to qcd scale, PDF, and mtop in quadrature
    #return xs_ggF(kl) * math.sqrt((min(66.0621-46.7458*kl+10.1673*kl**2, 66.7581-47.721*kl+10.4535*kl**2) * SCALE_GGF / xs_ggF(kl) - 1)**2 + 0.03**2 + 0.026**2)
    #new mtop uncertainty:
    return xs_ggF(kl) * math.sqrt((min(57.6809 - 42.9905*kl + 9.58474*kl**2, 58.3769 - 43.9657*kl + 9.87094*kl**2) * SCALE_GGF / xs_ggF(kl) - 1)**2 + 0.03**2)

def sigma_lower_VBF(kl):
    return xs_VBF(kl) * math.sqrt(0.0004**2 + 0.021**2)

def sigma_lower_HH(kl):
    return math.sqrt(sigma_lower_ggF(kl)**2 + sigma_lower_VBF(kl)**2)
    
def xs_lower_HH(kl):
    return xs_HH(kl) - sigma_lower_HH(kl) / 2 # reduced factor of 0.5 @ HL-LHC

print(xs_lower_HH(1), xs_HH(1), xs_upper_HH(1))
print(sigma_lower_ggF(1), xs_ggF(1), sigma_upper_ggF(1))
#Input: json file with the following format
#["kappa_lambda": [-2sigma, -1sigma, expected, +1sigma, +2sigma, observed]

limits = json.load(open('scan_WS-yybb-nonresonant_BDT_h026_v10_3000ifb_param_lim_syst/results.json'), object_pairs_hook=collections.OrderedDict)

lambdas = [float(kl) for kl in limits.keys()]

#the cross sections (reweighted)
n = [xs_HH(kl) for kl in lambdas]

limit_bands = {i:[x[i+2] for x in limits.values()] for i in range(-2, 4)}

fig = plt.figure(figsize=(8, 6))

add_subplot = 0

if (add_subplot):
	gs = gridspec.GridSpec(4,1)
	ax = fig.add_subplot(gs[:3,0])
	ax2 = fig.add_subplot(gs[3:,0],sharex=ax)
else: 
        gs = gridspec.GridSpec(4,1)
        ax = fig.add_subplot(gs[:4,0])


ax.semilogy(lambdas, n * np.array(limit_bands[0]),'k--',label='Expected limit (95\% CL)')

ax.fill_between(lambdas, n * np.array(limit_bands[-2]), n * np.array(limit_bands[2]),  facecolor = '#FDC536', label='Expected limit $\pm 2\sigma$')
ax.fill_between(lambdas, n * np.array(limit_bands[-1]), n * np.array(limit_bands[1]),  facecolor = '#4AD9D9', label='Expected limit $\pm 1\sigma$')

ax.plot(lambdas, n, color = 'darkred', label='Theory prediction (proj.)')
th_band = ax.fill_between(lambdas, [xs_lower_HH(kl) for kl in lambdas], [xs_upper_HH(kl) for kl in lambdas],  facecolor = '#F2385A')

#border for the legend
border_leg = patches.Rectangle((0, 0), 1, 1, facecolor = 'none', edgecolor = 'black', linewidth = 1)

#SM point
ax.plot(1, xs_HH(1), linewidth = 0, marker = '*', markersize = 20, color = '#E9F1DF', markeredgecolor = 'black', label = 'SM prediction')

ylim = [.001,10]#for xsecbr
ylim = [10, 1000]

#ax.plot([1]*2,ylim,'grey')
ax.set_ylim(ylim)

#get the intersection between expected and theory prediction (central value only)
limitm1 = n * np.array(limit_bands[0]) - n
#including lower th band
#limitm1 = n * np.array(limit_bands[0]) - [xs_lower_HH(kl) for kl in lambdas]
idx = np.argwhere(np.diff(np.sign(limitm1))).flatten()
#linear interpolation: x = x1 + (x2-x1)/(y2-y1) * (y-y1)
#y = 0 -> x = x1 - (x2-x1)/(y2-y1) * y1
intersections = [lambdas[x] - (lambdas[x+1] - lambdas[x])/(limitm1[x+1] - limitm1[x]) * limitm1[x] for x in idx]
print ('limits:', intersections)
plt.annotate(r'Expected: $\kappa_\lambda \in [%.1f, %.1f]$' %(intersections[0], intersections[1]), (0.04, 0.08), xycoords = 'axes fraction', fontsize = 15)
plt.annotate(r'Baseline scenario', (0.64, 0.08), xycoords = 'axes fraction', fontsize = 15)

ax.xaxis.set_ticks(np.arange(min(lambdas), max(lambdas) + 1, 2))

ampl.set_ylabel('$\sigma_{ggF+VBF}$ (HH) [fb]', fontsize=20)

#reorder the legend
handles,labels = ax.get_legend_handles_labels()
handles[2].set_linewidth(1.0)

handles = [handles[0], (handles[4], border_leg), (handles[3], border_leg), (th_band, handles[1], border_leg), handles[2]]
labels = [labels[0], labels[4], labels[3], labels[1], labels[2]]

ax.legend(handles, labels, loc='upper right', fontsize = 15, frameon = False)

if (add_subplot):
	ax2.plot(lambdas,np.array(limit2_bands[0])/np.array(limit_bands[0]),color='r',linestyle='--')

	ax2.plot(lambdas,np.ones_like(lambdas),'k--')

	ax2.set_xlabel('$\kappa_\lambda$ = $\lambda_{HHH}$ / $\lambda_{SM}$', fontsize=16)
	ax2.set_ylabel('Limit ratio')
	ax2.set_ylim(0.5,1.5)
else:
        ampl.set_xlabel('$\kappa_\lambda$', fontsize=20)

ampl.draw_atlas_label(0.05, 0.95, ax, status = 'prelim', energy = '14 TeV', lumi = 3000, desc = r'$HH \ {\rightarrow} \ b\bar{b} \gamma \gamma$' '\n' 'Projection from Run 2 data', fontsize = 15)

plt.xlim([-2, 6])

plt.savefig('kappa_lambda_scan_ratio_param_obs_HLLHC_v10_syst.pdf')

plt.show()
