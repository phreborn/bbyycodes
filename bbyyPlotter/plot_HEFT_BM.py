#modified from Nicole Hartman's plot_limits_comparison.py by Laura Pereira

import numpy as np
import matplotlib.pyplot as plt
import ROOT as r
import collections

stdText = '$\mathbf{ATLAS}$ Internal\n'
stdText += r'$\sqrt{s} = $ 13 TeV, 139fb$^{-1}$'+'\n'
stdText += r'$HH\rightarrow \gamma\gamma bb$'
stdText += '\nStats only limit'

#the -2sigma, -1sigma, central value, +1sigma, +2sigma points
#from quickCLs or somewhere else
#maybe figure out a way to read this automatically in the future

u =  1000 #limits in fb (1 = pb)

path = "../../quickFit/"
samples = ["BM_SM","BM_1","BM_2","BM_3","BM_4","BM_5","BM_6","BM_7"]
#samples = ["CMS_BM_1","CMS_BM_2","CMS_BM_3","CMS_BM_4","CMS_BM_5","CMS_BM_6","CMS_BM_7","CMS_BM_8","CMS_BM_9","CMS_BM_10","CMS_BM_11","CMS_BM_12"]

samples.reverse()

#limit_values =  []
limits = collections.OrderedDict()

for s in samples:
    name = path+"HH_HEFT_"+s+".root"
    print(name)
    h = r.TH1F()
    f = r.TFile.Open(name)
    r.gROOT.cd()
    h = f.Get("limit")
    median = h.GetBinContent(2)*u
    p_2sigma = h.GetBinContent(3)*u
    p_1sigma = h.GetBinContent(4)*u
    n_1sigma = h.GetBinContent(5)*u
    n_2sigma = h.GetBinContent(6)*u
    #limit_values.append([n_2sigma,n_1sigma,median,p_1sigma,p_2sigma])

    sp = s.split("_")[-1]

    limits.update([
        (sp,[n_2sigma,n_1sigma,median,p_1sigma,p_2sigma]),
              ])


print(limits)    

fig, ax = plt.subplots(1,1,figsize=(8,6))


eps = 0.3
exp_bands = limits.values()
print exp_bands

for i,(ymin, cls_exp) in enumerate(zip(np.arange(len(limits))[::-1],
                                       exp_bands)):

    ymin = ymin+1

    plt.fill_between( [ymin-eps,ymin+eps], [cls_exp[0]]*2,[cls_exp[-1]]*2,
                     facecolor = 'gold', 
                    label='Expected $\pm 1\sigma$' if i==0 else None)
    plt.fill_between([ymin-eps,ymin+eps], [cls_exp[1]]*2,[cls_exp[-2]]*2,
                     facecolor = 'lime', 
                     label='Expected $\pm 2\sigma$' if i==0 else None)
    
    plt.plot([ymin]*2,[cls_exp[2]]*2, 'k o',
             label='Expected' if i==0 else None)
       
ax.set_xticks(np.arange(len(limits))+1)
ax.set_xticklabels(limits.keys()[::-1])   
ax.set_yscale('log') 

plt.ylim(0.05, 50)

plt.xlim(0,len(samples)+1)
plt.text(0.05,0.95,stdText,ha='left',va='top',transform=ax.transAxes)
plt.legend(loc='upper right')
    


plt.ylabel(r'$\sigma_{ggF}(pp \rightarrow HH)$ $\times$ BR($\gamma \gamma bb$) (fb)')

plt.xlabel('Shape benchmarks')

plt.savefig('Shape_BMs_stats.pdf',bbox_inches='tight')

print("show!!!")
plt.show() 


