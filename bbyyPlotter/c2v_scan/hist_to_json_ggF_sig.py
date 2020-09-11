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

	with open('VBF_' + coupling + '_five_cats.json', 'w') as outfile: json.dump( mod_spec , outfile )


path = "/afs/cern.ch/user/j/jpearkes/work/public/selection_histograms_myy_120_130_aug24/" # five categories
#path = "/afs/cern.ch/user/j/jpearkes/work/public/selection_histograms_myy_120_130_noVBF_sept_3/" # four categories
# signal = "VBF_rescale" # What we want to run over: rescaled histograms
# signal = "VBF" # What we want to run over: non-rescaled histograms
bkgs = ["WmH_PowhegPy8", "WpH_PowhegPy8", "ZH_PowhegPy8", "bbH", "ggH_PowhegPy8", "ggZH_PowhegPy8", "tHjb", "tWH", "ttH_PowhegPy8", "ttyy_allhad", "ttyy_noallhad", "yy"]

# Find available VBF couplings
# signals = glob.glob(path+signal+"_l1cvv*cv1_*"+"Validation.root")
#couplings = [coupling.replace(path+signal+"_", '').replace("_Validation.root","") for coupling in signals]
#couplings.append("l1cvv1cv1")
couplings = ["l1cvv1cv1"]
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
bkg_header = "Rows are categories: "
for category in categories:
	# bkg_header += "\n\t"
	bkg_header += category
	bkg_header += ", "

bkg_header += "\nColumns are backgrounds: "
for bkg in bkgs:
	# bkg_header += "\n\t"
	bkg_header += bkg
	bkg_header += ", "

np.savetxt('bkg_yields_five_cats.txt', bkg_yields, header = bkg_header)

obs_dat = bkg_dat # Currently setting observation = background
# Change this line to use a proper observed data set

# Run over signal samples (i.e. different c2v couplings)
# to read their myy histograms into jsons and calculate yields
VBF_sig_yields = []
ggF_sig_yields = []
# print("Writing json for coupling " + coupling)
sig_dat = {}
for category in categories:
    to_read = "sumHisto_"+disc_variable+"_"+category
    VBFfilename = "VBF_" + category + ".root"
    ggFfilename = "HH_" + category + ".root"

    # Read myy histogram for each category
    VBFfile = uproot.open(path+VBFfilename)
    ggFfile = uproot.open(path+ggFfilename)
    VBF_sig_dat = VBFfile[to_read].values[15:25]
    ggF_sig_dat = ggFfile[to_read].values[15:25]
    sig_dat[category] = (VBF_sig_dat + ggF_sig_dat).tolist()
    
    VBF_sig_yields.append(sum(VBF_sig_dat))
    ggF_sig_yields.append(sum(ggF_sig_dat))

sig_yields = np.array([VBF_sig_yields, ggF_sig_yields])
# Write histograms to json
make_json(categories, sig_dat, bkg_dat, bkg_uncert, obs_dat, couplings[0])

# Write signal yields to text
np.savetxt('sig_yields_five_cats.txt', sig_yields, 
           header = "Rows are signals: \nVBF, ggF"
               + "\nColumns are categories: \n"
               + "XGBoost_btag77_withTop_BCal_looseScore_HMass, "
               + "XGBoost_btag77_withTop_BCal_looseScore_LMass, "
               + "XGBoost_btag77_withTop_BCal_tightScore_HMass, "
               + "XGBoost_btag77_withTop_BCal_tightScore_LMass, "
               + "VBF_btag77_withTop_BCal"
           )
