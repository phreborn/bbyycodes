#modified from https://gitlab.cern.ch/hartman/dihiggs4b/blob/master/PFlow-Topo/Limit-Comparisons.ipynb by Nicole Hartman
#requires python3 to use atlas_mpl_style

import numpy as np
import math
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import atlas_mpl_style as ampl
import collections
import json

ampl.use_atlas_style()

'''
#cross sections for kl = 0, 1, 10
#values from LO samples in  https://gitlab.cern.ch/atlas-hgam-sw/HGamCore/blob/master/HGamAnalysisFramework/data/MCSamples.config
#divided by branching ratio
#1.29 derived from LO to NLO for kl = 1

BR = 5.809E-01 * 2.27E-03 * 2
xsec0 = 3.0565E-02 * 7.8677E-03 / BR / 1.29
xsec1 = 1.4412E-02 * 7.8752E-03 / BR / 1.29
xsec10 = 2.5161E-01 * 7.8568E-03 / BR / 1.29
def reweight_yybb(a0, a1, a10, kl):

    #aX is the amplitude square of the signal with lambda = X

    a = a0 * (90 + 9*kl**2 - 99*kl)/90 + a1 * (100*kl - 10*kl**2) / 90 + a10 * (kl**2 - kl)/90
    return a
'''

#Now using values from LHCWHGHHHXGGBGGGXXX
SCALE_GGF = 31.02/31.0358   #correct to xs at mH = 125.09 
SCALE_VBF = 1.723/(4.581-4.245+1.359)

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
    return xs_ggF(kl) * math.sqrt((max(72.0744-51.7362*kl+11.3712*kl**2, 70.9286-51.5708*kl+11.4497*kl**2) * SCALE_GGF / xs_ggF(kl) - 1)**2 + 0.03**2 + 0.026**2)
    
def sigma_upper_VBF(kl):
    #from klambda = 1
    return xs_VBF(kl) * math.sqrt(0.0003**2 + 0.021**2)

def sigma_upper_HH(kl):
    return math.sqrt(sigma_upper_ggF(kl)**2 + sigma_upper_VBF(kl)**2)
    
def xs_upper_HH(kl):
    return xs_HH(kl) + sigma_upper_HH(kl)

def sigma_lower_ggF(kl):
    #https://twiki.cern.ch/twiki/bin/view/LHCPhysics/LHCHWGHH?redirectedfrom=LHCPhysics.LHCHXSWGHH#Latest_recommendations_for_gluon
    #add the std on ggF HH due to qcd scale, PDF, and mtop in quadrature
    return xs_ggF(kl) * math.sqrt((min(66.0621-46.7458*kl+10.1673*kl**2, 66.7581-47.721*kl+10.4535*kl**2) * SCALE_GGF / xs_ggF(kl) - 1)**2 + 0.03**2 + 0.026**2)

def sigma_lower_VBF(kl):
    return xs_VBF(kl) * math.sqrt(0.0004**2 + 0.021**2)

def sigma_lower_HH(kl):
    return math.sqrt(sigma_lower_ggF(kl)**2 + sigma_lower_VBF(kl)**2)
    
def xs_lower_HH(kl):
    return xs_HH(kl) - sigma_lower_HH(kl)

#Input: json file with the following format
#["kappa_lambda": [-2sigma, -1sigma, expected, +1sigma, +2sigma, observed]

limits = json.load(open('2021_03_09_yybb_param_withsyst/limits.json'), object_pairs_hook=collections.OrderedDict)

lambdas = [float(kl) for kl in limits.keys()]

#the cross sections (reweighted)
n = [xs_HH(kl) for kl in lambdas]

limit_bands = {i:[x[i+2] for x in limits.values()] for i in range(-2, 4)}

#limits = json.load(open('2021_02_18_yybb_param_nosyst/limits.json'), object_pairs_hook=collections.OrderedDict)
#limit2_bands = {i:[x[i+2] for x in limits.values()] for i in range(-2, 3)}

fig = plt.figure(figsize=(8, 6))

add_subplot = 0

if (add_subplot):
	gs = gridspec.GridSpec(4,1)
	ax = fig.add_subplot(gs[:3,0])
	ax2 = fig.add_subplot(gs[3:,0],sharex=ax)
else: 
        gs = gridspec.GridSpec(4,1)
        ax = fig.add_subplot(gs[:4,0])


ax.semilogy(lambdas, n * np.array(limit_bands[3]),'k',label='Observed')
ax.semilogy(lambdas, n * np.array(limit_bands[0]),'k--',label='Expected')

ax.fill_between(lambdas, n * np.array(limit_bands[-2]), n * np.array(limit_bands[2]),  facecolor = 'yellow', label='Expected $\pm 2\sigma$')
ax.fill_between(lambdas, n * np.array(limit_bands[-1]), n * np.array(limit_bands[1]),  facecolor = 'lime', label='Expected $\pm 1\sigma$')

# The extra bands that I wanted to add
#ax.semilogy(lambdas, n * np.array(limit2_bands[0]),color='r',linestyle='--',label='Stat only')

ax.plot(lambdas,n,'C4', color = 'darkred', label='Theory prediction')
th_band = ax.fill_between(lambdas, [xs_lower_HH(kl) for kl in lambdas], [xs_upper_HH(kl) for kl in lambdas],  facecolor = 'r')


ylim = [.001,10]#for xsecbr
ylim = [10, 100000]

#ax.plot([1]*2,ylim,'grey')
ax.set_ylim(ylim)

#get the intersection between expected and theory prediction
limitm1 = np.array(limit_bands[0]) - 1
idx = np.argwhere(np.diff(np.sign(limitm1))).flatten()
#linear interpolation: x = x1 + (x2-x1)/(y2-y1) * (y-y1)
#y = 0 -> x = x1 - (x2-x1)/(y2-y1) * y1
intersections = [lambdas[x] - (lambdas[x+1] - lambdas[x])/(limitm1[x+1] - limitm1[x]) * limitm1[x] for x in idx]
print ('limits:', intersections)
#for x in intersections:
#	ax.plot([x]*2,ylim,'blue')

#observed
limitm1 = np.array(limit_bands[3]) - 1
idx = np.argwhere(np.diff(np.sign(limitm1))).flatten()
intersections = [lambdas[x] - (lambdas[x+1] - lambdas[x])/(limitm1[x+1] - limitm1[x]) * limitm1[x] for x in idx]
print ('limits:', intersections)


#for the second one
#get the intersection between expected and theory prediction
#limitm1 = np.array(limit2_bands[0]) - 1
#idx = np.argwhere(np.diff(np.sign(limitm1))).flatten()
#linear interpolation: x = x1 + (x2-x1)/(y2-y1) * (y-y1)
#y = 0 -> x = x1 - (x2-x1)/(y2-y1) * y1
#intersections = [lambdas[x] - (lambdas[x+1] - lambdas[x])/(limitm1[x+1] - limitm1[x]) * limitm1[x] for x in idx]
#print 'limits:', intersections
#for x in intersections:
#        ax.plot([x]*2,ylim,'blue')

ax.xaxis.set_ticks(np.arange(min(lambdas), max(lambdas) + 1, 2))

ampl.set_ylabel('$\sigma_{ggF+VBF}$ [fb]', fontsize=16)

#reorder the legend
handles,labels = ax.get_legend_handles_labels()
handles = [handles[0], handles[1], handles[3], handles[4], (th_band, handles[2])]
labels = [labels[0], labels[1], labels[3], labels[4], labels[2]]

ax.legend(handles, labels, loc='upper right', fontsize = 'small', frameon = False)

if (add_subplot):
	ax2.plot(lambdas,np.array(limit2_bands[0])/np.array(limit_bands[0]),color='r',linestyle='--')

	ax2.plot(lambdas,np.ones_like(lambdas),'k--')

	ax2.set_xlabel('$\kappa_\lambda$ = $\lambda_{HHH}$ / $\lambda_{SM}$', fontsize=16)
	ax2.set_ylabel('Limit ratio')
	ax2.set_ylim(0.5,1.5)
else:
        ampl.set_xlabel('$\kappa_\lambda$ = $\lambda_{HHH}$ / $\lambda_{SM}$', fontsize=16)

ampl.draw_atlas_label(0.05, 0.95, ax, status = 'int', energy = '13 TeV', lumi = 139, desc = '')

plt.xlim([-10, 10])

plt.savefig('kappa_lambda_scan_ratio_param_obs_v4.pdf')

plt.show()
