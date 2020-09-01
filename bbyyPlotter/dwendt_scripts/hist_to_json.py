# Script to read myy histograms from a .root file and store
# them as jsons

# Adapted by David Wendt from a plotter script by Jannicke Pearkes

import math
from pprint import *
import numpy as np
import pandas as pd
# import matplotlib
# import matplotlib.pyplot as plt
# matplotlib.rcParams['figure.dpi']= 150
import uproot
import glob
import seaborn as sns
sns.set_style(style = "ticks")
sns.set_palette(sns.color_palette())
sns.set_color_codes()
import json

def make_json(categories, sig_dat, bkg_dat, bkg_uncert, obs_dat, coupling):
	""" Make json files """
	
	# Define the workspace 

	mod_spec = { 'channels': [] , 'observations': [] , 'measurements': [] , 'version': "1.0.0"}

	for category in categories:
		cat_sig_dat = sig_dat[category]
		cat_bkg_dat = bkg_dat[category]
		cat_bkg_uncert = bkg_uncert[category]
		cat_obs_dat = obs_dat[category]
	
		channel = {  
			'name': category,
			'samples' : [
			{
				'name': category + ' signal',
				'data': cat_sig_dat,
				'modifiers': [
					{'name': 'mu', 'type': 'normfactor', 'data': None } , 
				],
			},
			{
				'name': category + ' background',
				'data': cat_bkg_dat,
				'modifiers': [
					{'name': category + ' uncorr_bkguncrt', 'type': 'shapesys', 'data': cat_bkg_uncert } , 
				],
			},
			],
		}
	
		mod_spec['channels'].append(channel)
	
		obs = {  
			'name': category + ' singlechannel',
			'data': cat_obs_dat 
		}
			
		mod_spec['observations'].append(obs)

	meas = { 
		"name": 'measurement', 
		"config": { "poi": 'mu', "parameters": [] } 
	}
	
	mod_spec['measurements'].append(meas)

	with open('VBF_' + coupling + '_all_cats.json', 'w') as outfile: json.dump( mod_spec , outfile )


# path = "/afs/cern.ch/user/j/jpearkes/work/public/baseline_histograms_aug11/" # Where histograms are stored
# path = "/afs/cern.ch/user/j/jpearkes/work/public/selection_histograms_aug24/" # Where histograms are stored
path = "/afs/cern.ch/user/j/jpearkes/work/public/selection_histograms_myy_120_130_aug24/" # Where histograms are stored
signal = "VBF_rescale" # What we want to run over: rescaled histograms
# signal = "VBF" # What we want to run over: non-rescaled histograms
bkgs = ["yy", "ZH_PowhegPy8", "ttyy_noallhad", "ttH_PowhegPy8", "HH"] # different backgrounds

# Find available VBF couplings
signals = glob.glob(path+signal+"_l1cvv*cv1_*"+"Validation.root")
couplings = [coupling.replace(path+signal+"_", '').replace("_Validation.root","") for coupling in signals]
couplings.append("l1cvv1cv1")
print("Couplings: "+str(couplings))

# Categories used for the scan
# category = "VBF_btag77_withTop_BCal"
categories = [
	# "Validation",
	"XGBoost_btag77_withTop_BCal_looseScore_HMass",
	"XGBoost_btag77_withTop_BCal_looseScore_LMass",
	"XGBoost_btag77_withTop_BCal_tightScore_HMass",
	"XGBoost_btag77_withTop_BCal_tightScore_LMass",
	"VBF_btag77_withTop_BCal"
]

# Discriminant variable
disc_variable = "m_yy"

# Read data from each background and each category
bkg_yields = []
bkg_dat = {} # Backgruond myy histograms
bkg_uncert = {} # Stat errors on bkg myy histograms
for category in categories:
    bkgs_dat = []
    bkgs_uncert = []
    cat_bkg_yields = []
    for bkg in bkgs:
        to_read = "sumHisto_"+disc_variable+"_"+category
        bkg_filename = bkg + "_" + category + ".root"
        bkg_file = uproot.open(path+bkg_filename)
        bkg_dat_i = bkg_file[to_read].values[15:25]
        bkg_uncert_i = np.sqrt(bkg_file[to_read].variances[15:25])

        bkgs_dat.append(bkg_dat_i)
        bkgs_uncert.append(bkg_uncert_i)
        cat_bkg_yields.append(np.sum(bkg_dat_i))

    bkg_dat[category] = np.sum(np.array(bkgs_dat), axis=0).tolist()
    bkg_uncert[category] = np.sum(np.array(bkgs_uncert), axis=0).tolist()
    bkg_yields.append(cat_bkg_yields)
    
# Write background yields to text
np.savetxt('bkg_yields.txt', bkg_yields, 
           header = "Rows are categories: \n#"
               + "XGBoost_btag77_withTop_BCal_looseScore_HMass, "
               + "XGBoost_btag77_withTop_BCal_looseScore_LMass, "
               + "XGBoost_btag77_withTop_BCal_tightScore_HMass, "
               + "XGBoost_btag77_withTop_BCal_tightScore_LMass, "
               + "VBF_btag77_withTop_BCal \n#"
               + "Columns are backgrounds: \n#"
               + "yy, ZH_PowhegPy8, ttyy_noallhad, ttH_PowhegPy8, HH"
           )

obs_dat = bkg_dat # Currently setting observation = background
# Change this line to use a proper observed data set

# Run over signal samples (i.e. different c2v couplings)
# to read their myy histograms into jsons and calculate yields
sig_yields = []
couplings_str = ""
for coupling in couplings:
    couplings_str += coupling
    couplings_str += ", "
    # print("Writing json for coupling " + coupling)
    sig_dat = {}
    coup_sig_yields = []
    for category in categories:
        to_read = "sumHisto_"+disc_variable+"_"+category
		
        if coupling == "l1cvv1cv1":
            # SM sample has different naming convention
            filename = "VBF_" + category + ".root"
        else:
            filename = signal+"_"+coupling+"_"+category+".root"

        # Read myy histogram for each category
        file = uproot.open(path+filename)
        sig_dat[category] = file[to_read].values[15:25].tolist()
        coup_sig_yields.append(sum(sig_dat[category]))
    
    sig_yields.append(coup_sig_yields)
    # Write histograms to json
    make_json(categories, sig_dat, bkg_dat, bkg_uncert, obs_dat, coupling)

# Write signal yields to text
np.savetxt('sig_yields.txt', sig_yields, 
           header = "Rows are couplings: \n#"
               + couplings_str[:-2]
               + "\n#Columns are categories: \n#"
               + "XGBoost_btag77_withTop_BCal_looseScore_HMass, "
               + "XGBoost_btag77_withTop_BCal_looseScore_LMass, "
               + "XGBoost_btag77_withTop_BCal_tightScore_HMass, "
               + "XGBoost_btag77_withTop_BCal_tightScore_LMass, "
               + "VBF_btag77_withTop_BCal"
           )