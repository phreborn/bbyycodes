import math
import numpy as np

import matplotlib.pyplot as plt

import oyaml as yaml
from collections import OrderedDict

import atlas_mpl_style as ampl
ampl.use_atlas_style()

#from cycler import cycler
#plt.rcParams['axes.prop_cycle'] = cycler(color='')

def plot(path, signal):

# BDT #
    yield_dict = yaml.load(open('%s/yields.yaml' %path, 'r'), Loader=yaml.FullLoader)
    HH = []
    yy = []
    ggH = []
    ttH = []
    ZH = []
    otherH = []

    print(signal)
    for cat_name, cat_dict in yield_dict.items():
        print(cat_name)
        total_yield = cat_dict['HH_ggF_%s' %signal] + cat_dict['HH_VBF_%scvv1' %signal] + cat_dict['ggH'] + cat_dict['ttH'] + cat_dict['ZH'] + cat_dict['WH'] + cat_dict['VBF'] + cat_dict['tWH'] + cat_dict['tHjb']
        #print(total_yield)	
        HH.append((cat_dict['HH_ggF_%s' %signal] + cat_dict['HH_VBF_%scvv1' %signal])/total_yield)
        ggH.append(cat_dict['ggH'] / total_yield)
        ttH.append(cat_dict['ttH'] / total_yield)
        ZH.append(cat_dict['ZH'] / total_yield)
        otherH.append((cat_dict['WH'] + cat_dict['VBF'] + cat_dict['tWH'] + cat_dict['tHjb']) / total_yield)

        print('HH', (cat_dict['HH_ggF_%s' %signal] + cat_dict['HH_VBF_%scvv1' %signal])/total_yield)
        print('ggH', cat_dict['ggH'] / total_yield)
        print('ttH', cat_dict['ttH'] / total_yield)
        print('ZH', cat_dict['ZH'] / total_yield)
        print('otherH', (cat_dict['WH'] + cat_dict['VBF'] + cat_dict['tWH'] + cat_dict['tHjb']) / total_yield)
        print()
    
    N = 4
# BDT #
  
    ind = np.arange(N)    # the x locations for the groups
    width = 0.50       # the width of the bars: can also be len(x) sequence

    plt.figure (figsize = (8, 6))

    p1 = plt.bar(ind, ggH, width, color = '#1f77b4', edgecolor = 'black', linewidth = 1)
    p2 = plt.bar(ind, ttH, width, bottom= np.array(ggH), color = '#ff7f0e', edgecolor = 'black', linewidth = 1)
    p3 = plt.bar(ind, ZH, width, bottom= np.array(ggH) + np.array(ttH), color = '#2ca02c', edgecolor = 'black', linewidth = 1)
    p4 = plt.bar(ind, otherH, width, bottom= np.array(ggH) + np.array(ttH) + np.array(ZH), color = '#bcbd22', edgecolor = 'black', linewidth = 1)
    p5 = plt.bar(ind, HH, width, bottom= np.array(ggH) + np.array(ttH) + np.array(ZH) + np.array(otherH), color = '#9467bd', edgecolor = 'black', linewidth = 1)
    
    ampl.set_ylabel('Expected purities', fontsize = 15)

    plt.xticks(ind, ('High mass \n BDT tight', 'High mass \n BDT loose', 'Low mass \n BDT tight', 'Low mass \n BDT loose'), fontsize = 15)
    plt.gca().axes.tick_params(axis = 'x', which = 'both', length = 0)
    plt.yticks(np.arange(0, 10, 0.2))
    plt.ylim(0, 1.5)

    if 'kl1p0' in signal:
        plt.legend((p5[0], p4[0], p3[0], p2[0], p1[0]), (r'HH, $\kappa_{\lambda} = 1$', 'Other H', 'ZH', 'ttH', 'ggH'), fontsize = 12, frameon = False)
    elif 'kl10p0' in signal:
        plt.legend((p5[0], p4[0], p3[0], p2[0], p1[0]), (r'HH, $\kappa_{\lambda} = 10$', 'Other H', 'ZH', 'ttH', 'ggH'), fontsize = 12, frameon = False)
    
    ampl.draw_atlas_label(0.05, 0.95, status = '', simulation = True, energy = '13 TeV', lumi = 139, desc = '$m_{\gamma\gamma} \in [120, 130]$ GeV')
    plt.tight_layout()

#    plt.show()

    plt.savefig('%s/purities_%s_PAPER.pdf' %(path, signal))

    return 

def main():

    plot("yybb_h026_final_forplot", "kl1p0")
    plot("yybb_h026_final_forplot", "kl10p0")

    return

if __name__ == '__main__':
    main()

