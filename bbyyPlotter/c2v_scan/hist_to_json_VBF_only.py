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

def make_json(category, sig_dat, bkg_dat, bkg_uncert, obs_dat, coupling):
	""" Make json files """
	
	# Define the workspace 

	mod_spec = { 'channels': [] , 'observations': [] , 'measurements': [] , 'version': "1.0.0"}
	
	channel = {  
		'name': category,
		'samples' : [
		{
			'name': category + ' signal',
			'data': sig_dat,
			'modifiers': [
				{'name': 'mu', 'type': 'normfactor', 'data': None } , 
			],
		},
		{
			'name': category + ' background',
			'data': bkg_dat,
			'modifiers': [
				{'name': category + ' uncorr_bkguncrt', 'type': 'shapesys', 'data': bkg_uncert } , 
			],
		},
		],
	}
	
	mod_spec['channels'].append(channel)
	
	obs = {  
		'name': category + ' singlechannel',
		'data': obs_dat 
	}
			
	mod_spec['observations'].append(obs)

	meas = { 
		"name": 'measurement', 
		"config": { "poi": 'mu', "parameters": [] } 
	}
	
	mod_spec['measurements'].append(meas)

	with open('VBF_' + coupling + '_VBF_only.json', 'w') as outfile: json.dump( mod_spec , outfile )


# path = "/afs/cern.ch/user/j/jpearkes/work/public/baseline_histograms_aug11/" # Where histograms are stored
# path = "/afs/cern.ch/user/j/jpearkes/work/public/selection_histograms_aug24/" # Where histograms are stored
path = "/afs/cern.ch/user/j/jpearkes/work/public/selection_histograms_myy_120_130_aug24/" # Where histograms are stored
signal = "VBF_rescale" # What we want to run over: rescaled histograms
# signal = "VBF" # What we want to run over: non-rescaled histograms
bkgs = ["HH", "WmH_PowhegPy8", "WpH_PowhegPy8", "ZH_PowhegPy8", "bbH", "ggH_PowhegPy8", "ggZH_PowhegPy8", "tHjb", "tWH", "ttH_PowhegPy8", "ttyy_allhad", "ttyy_noallhad", "yy"]

# Find available VBF couplings
signals = glob.glob(path+signal+"_l1cvv*cv1_*"+"Validation.root")
couplings = [coupling.replace(path+signal+"_", '').replace("_Validation.root","") for coupling in signals]
couplings.append("l1cvv1cv1")
print("Couplings: "+str(couplings))

# Categories used for the scan
category = "VBF_btag77_withTop_BCal"

# Discriminant variable
disc_variable = "m_yy"

# Read data from each background and each category
bkg_yields = {}
bkg_dat = [] # Background myy histograms
bkg_uncert = [] # Stat errors on bkg myy histograms

for bkg in bkgs:
	to_read = "sumHisto_"+disc_variable+"_"+category
        bkg_filename = bkg + "_" + category + ".root"
        bkg_file = uproot.open(path+bkg_filename)
        bkg_dat.append(bkg_file[to_read].values[15:25])
        bkg_uncert.append(np.sqrt(bkg_file[to_read].variances[15:25]))

        bkg_yields[bkg] = str(np.sum(bkg_dat[-1]))

bkg_dat = np.sum(np.array(bkg_dat), axis=0).tolist()
bkg_uncert = np.sum(np.array(bkg_uncert), axis=0).tolist()
    
# Write background yields to json
with open('bkg_yields_VBF_only.json', 'w') as outfile: json.dump( bkg_yields , outfile )


obs_dat = bkg_dat # Currently setting observation = background
# Change this line to use a proper observed data set

# Run over signal samples (i.e. different c2v couplings)
# to read their myy histograms into jsons and calculate yields
sig_yields = {}
couplings_str = ""
for coupling in couplings:
	couplings_str += coupling
	couplings_str += ", "
 	print("Writing json for coupling " + coupling)
	to_read = "sumHisto_"+disc_variable+"_"+category
		
	if coupling == "l1cvv1cv1":
            # SM sample has different naming convention
            filename = "VBF_" + category + ".root"
        else:
            filename = signal+"_"+coupling+"_"+category+".root"

        # Read myy histogram for each category
        file = uproot.open(path+filename)
        sig_dat = file[to_read].values[15:25].tolist()
        sig_yields[coupling] = str(sum(sig_dat))
    
	# Write histograms to json
	make_json(category, sig_dat, bkg_dat, bkg_uncert, obs_dat, coupling)

# Write background yields to json
with open('sig_yields_VBF_only.json', 'w') as outfile: json.dump( sig_yields , outfile )
