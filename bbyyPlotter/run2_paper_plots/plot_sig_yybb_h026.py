import math
import numpy as np

import matplotlib.pyplot as plt

import oyaml as yaml
from collections import OrderedDict

import atlas_mpl_style as ampl
ampl.use_atlas_style()

#from cycler import cycler
#plt.rcParams['axes.prop_cycle'] = cycler(color='')
#from matplotlib import rc
#rc('text', usetex=True)

def plot(path, signal):

    # BDT #
    yield_dict = yaml.load(open('%s/yields.yaml' %path, 'r'), Loader=yaml.FullLoader)
    sig = []

    for cat_name, cat_dict in yield_dict.items():
        print(cat_name)
        s = cat_dict['HH_ggF_%s' %signal] + cat_dict['HH_VBF_%scvv1' %signal]
        b = cat_dict['data'] + cat_dict['ggH'] + cat_dict['ttH'] + cat_dict['ZH'] + cat_dict['WH'] + cat_dict['VBF'] + cat_dict['tWH'] + cat_dict['tHjb']
        #print(s+b)	
        print(signal, cat_name, math.sqrt(2*(((s+b)*math.log((s+b)/b)) - s)))
        sig.append(math.sqrt(2*(((s+b)*math.log((s+b)/b)) - s)))
    N = 4
    # BDT #
  
    ind = np.arange(N)    # the x locations for the groups
    width = 0.50       # the width of the bars: can also be len(x) sequence

    plt.figure (figsize = (8, 6))

    p6 = plt.bar(ind, sig, width, color = '#9467bd', edgecolor = 'black', linewidth = 1)
    
    #ampl.set_ylabel(r'$\sqrt{2((s+b)\log{(1+s/b)} - s)}$', fontsize = 15)
    ampl.set_ylabel('Expected significances (Z)', fontsize = 15)

    plt.xticks(ind, ('High mass \n BDT tight', 'High mass \n BDT loose', 'Low mass \n BDT tight', 'Low mass \n BDT loose'), fontsize = 15)
    plt.gca().axes.tick_params(axis = 'x', which = 'both', length = 0)

    #plt.yticks(np.arange(0, 12, 0.1))
    #plt.ylim(0, 1.2)

    if 'kl1p0' in signal:
        plt.annotate(r'Z = $\sqrt{2((s+b)\log{(1+s/b)} - s)}$ \\ s = HH, $\kappa_{\lambda} = 1$ \\ b = H + Continuum Bkg.', (0.55, 0.90), xycoords = 'axes fraction', fontsize = 15)
        #plt.legend([], [r's = HH, $\kappa_{\lambda} = 1$'], fontsize = 12, frameon = False)
        plt.yticks(np.arange(0, 12, 0.1))
        plt.ylim(0, 0.5)
    elif 'kl10p0' in signal:
        plt.annotate(r'Z = $\sqrt{2((s+b)\log{(1+s/b)} - s)}$ \\ s = HH, $\kappa_{\lambda} = 10$ \\ b = H + Continuum Bkg.', (0.55, 0.90), xycoords = 'axes fraction', fontsize = 15)
        plt.yticks(np.arange(0, 12, 0.5))
        plt.ylim(0, 3.5)

    ampl.draw_atlas_label(0.05, 0.95, status = '', energy = '13 TeV', lumi = 139, desc = '$m_{\gamma\gamma} \in [120, 130]$ GeV')
    plt.tight_layout()

#    plt.show()

    plt.savefig('%s/sig_%s_PAPER.pdf' %(path, signal))

    return 

def main():

    plot("yybb_h026_final_forplot", "kl1p0")
    plot("yybb_h026_final_forplot", "kl10p0")

    return

if __name__ == '__main__':
    main()

