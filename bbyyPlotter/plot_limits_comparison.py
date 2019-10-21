#modified from https://gitlab.cern.ch/hartman/dihiggs4b/blob/master/PFlow-Topo/Limit-Comparisons.ipynb by Nicole Hartman

import numpy as np
import matplotlib.pyplot as plt
import collections

stdText = '$\mathbf{ATLAS}$ Internal\n'
stdText += r'$\sqrt{s} = $ 13 TeV, 139fb$^{-1}$'+'\n'
stdText += r'$HH\rightarrow \gamma\gamma bb$'
stdText += '\nStats only limit'

#the -2sigma, -1sigma, central value, +1sigma, +2sigma points
#from quickCLs or somewhere else
#maybe figure out a way to read this automatically in the future

limits = collections.OrderedDict()
limits.update([

    ('36ifb \npaper', [4.71, 6.32, 8.78, 12.65, 18.02]),
    ('BDT [h021]', [2.66, 3.57, 4.96, 7.25, 10.55]),
    ('BDT [h024]', [2.72, 3.65, 5.07, 7.42, 10.85]),
    ('BDT [h024] \n[no spurious \nsignal]', [2.68, 3.60, 5.00, 7.34, 10.74]),

    ])

fig, ax = plt.subplots(1,1,figsize=(8,6))

eps = .1
exp_bands = limits.values()
print exp_bands

for i,(ymin, cls_exp) in enumerate(zip(np.arange(len(limits))[::-1],
                                       exp_bands)):
    
    
    plt.fill_between([cls_exp[0],cls_exp[-1]], [ymin+eps]*2,[ymin+1-eps]*2, 
                     facecolor = 'yellow', 
                     label='Expected $\pm 1\sigma$' if i==0 else None)
    plt.fill_between([cls_exp[1],cls_exp[-2]], [ymin+eps]*2,[ymin+1-eps]*2, 
                     facecolor = 'lime', 
                     label='Expected $\pm 2\sigma$' if i==0 else None)
    
    plt.plot([cls_exp[2]]*2,[ymin+eps,ymin+1-eps],'k--',
             label='Expected' if i==0 else None)
       
ax.set_yticks(np.arange(len(limits))+0.5)
ax.set_yticklabels(limits.keys()[::-1])   
 
'''
Put some text on the top of the figure corresponding 
to the signal that we're looking at.
'''
plt.ylim(0,len(limits) + 2)
plt.text(0.05,0.95,stdText,ha='left',va='top',transform=ax.transAxes)
plt.legend(loc='upper right')
    
plt.xlabel(r'95% CL upper limit of $\sigma_{ggF}(pp \rightarrow HH)$ normalized to $\sigma_{ggF}^{SM}$')

plt.savefig('smnr_statsLimit.pdf',bbox_inches='tight')

plt.show() 
