#modified from https://gitlab.cern.ch/hartman/dihiggs4b/blob/master/PFlow-Topo/Limit-Comparisons.ipynb by Nicole Hartman

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import collections

stdText = '$\mathbf{ATLAS}$ Internal\n'
stdText += r'$\sqrt{s} = $ 13 TeV, 139fb$^{-1}$'+'\n'
stdText += r'$HH\rightarrow \gamma\gamma bb$'
stdText += '\nStats only limit'

lambdas = [-10, -6, -4, -2, -1, 0, 1, 2, 4, 6, 10]
n = [0.005172, 0.002393, 0.001408, 0.0006942, 0.0004329, 0.0002405, 0.00008811, 0.00005308, 0.0001331, 0.0004808, 0.001977]
#from xsecbrfilteff in MxAOD

#each row corresponds to klambda \in [-10, 10]
#each column corresponds to the [-2sigma, -1sigma, 0, 1sigma, 2sigma] values
#maybe figure out a way to read this automatically in the future

limits = np.array([
		[0.0774045, 0.103916, 0.144216, 0.207587, 0.295326],
		[0.162096, 0.217614, 0.302009, 0.434717, 0.61905],
		[0.266459, 0.357721, 0.496452, 0.715424, 1.02017],
		[0.510784, 0.685728, 0.951666, 1.37748, 1.97156],
		[0.773692, 1.03868, 1.4415, 2.08988, 2.99698],
		[1.22086, 1.639, 2.27464, 3.31403, 4.792],
		[2.7202, 3.65187, 5.06814, 7.42414, 10.8466],
		[3.52686, 4.73481, 6.57106, 9.64854, 14.1562],
		[2.81598, 3.78046, 5.24659, 7.55848, 10.7721],
		[0.859403, 1.15375, 1.6012, 2.30621, 3.2885],
		[0.213485, 0.286604, 0.397754, 0.57201, 0.814043],
		])

limit_bands = {i:limits[:,i+2] for i in range(-2, 3)}
limit2_bands = limit_bands

fig = plt.figure(figsize=(8, 6))

add_subplot = 0

if (add_subplot):
	gs = gridspec.GridSpec(4,1)
	ax = fig.add_subplot(gs[:3,0])
	ax2 = fig.add_subplot(gs[3:,0],sharex=ax)
else: 
        gs = gridspec.GridSpec(4,1)
        ax = fig.add_subplot(gs[:4,0])


ax.semilogy(lambdas, n * np.array(limit_bands[0]),'k--',label='BDT')

ax.fill_between(lambdas, n * np.array(limit_bands[-2]), n * np.array(limit_bands[2]),  facecolor = 'yellow')
ax.fill_between(lambdas, n * np.array(limit_bands[-1]), n * np.array(limit_bands[1]),  facecolor = 'lime')

# The extra bands that I wanted to add
#ax.semilogy(lambdas, n * np.array(limit2_bands[0]),color='b',linestyle='--',label='PFlow')

ax.plot(lambdas,n,'C4',label='theory prediction')

ylim = [.00001,2]
ax.plot([1]*2,ylim,'grey')
ax.set_ylim(ylim)

ax.set_ylabel('95% upper limit on $\sigma_{ggF} * BR$ [pb]', fontsize=16)
ax.legend(loc='lower left')

if (add_subplot):
	ax2.plot(lambdas,np.array(limit2_bands[0])/np.array(limit_bands[0]),color='b',linestyle='--')

	ax2.plot(lambdas,np.ones_like(lambdas),'k--')

	ax2.set_xlabel('$\kappa_\lambda$ = $\lambda_{HHH}$ / $\lambda_{SM}$', fontsize=16)
	ax2.set_ylabel('1 / baseline')
	ax2.set_ylim(0.5,1.5)
else:
        ax.set_xlabel('$\kappa_\lambda$ = $\lambda_{HHH}$ / $\lambda_{SM}$', fontsize=16)


ax.text(0.025,.975,stdText,ha='left',va='top',transform=ax.transAxes)

plt.savefig('kappa_lambda_scan_ratio.pdf')

plt.show()
