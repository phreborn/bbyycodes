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

def make_json(sig_dat, bkg_dat, bkg_uncert, obs_dat, coupling):
	""" Make json files """

	mod_spec = { 'channels': [] , 'observations': [] , 'measurements': [] , 'version': "1.0.0"}
	
	# Define the workspace 
	
	channel = {  
		'name': 'singlechannel',
		'samples' : [
		{
			'name': 'signal',
			'data': sig_dat,
			'modifiers': [
				{'name': 'mu', 'type': 'normfactor', 'data': None } , 
			],
		},
		{
			'name': 'background',
			'data': bkg_dat,
			'modifiers': [
				{'name': 'uncorr_bkguncrt', 'type': 'shapesys', 'data': bkg_uncert } , 
			],
		},
		],
	}
	
	mod_spec['channels'].append(channel)
	
	obs = {  
		'name': 'singlechannel',
		'data': obs_dat 
	}
			
	mod_spec['observations'].append(obs)

	meas = { 
		"name": 'measurement', 
		"config": { "poi": 'mu', "parameters": [] } 
	}
	
	mod_spec['measurements'].append(meas)

	with open('VBF_' + coupling + '.json', 'w') as outfile: json.dump( mod_spec , outfile )


# path = "/afs/cern.ch/user/j/jpearkes/work/public/baseline_histograms_aug11/" # Where histograms are stored
# path = "/afs/cern.ch/user/j/jpearkes/work/public/selection_histograms_aug24/" # Where histograms are stored
path = "/afs/cern.ch/user/j/jpearkes/work/public/selection_histograms_myy_120_130_aug24/"
signal = "VBF_rescale" # What we want to run over: rescaled histograms
# signal = "VBF" # What we want to run over: non-rescaled histograms
bkgs = ["yy_VBF_btag77_withTop_BCal.root", "ZH_PowhegPy8_VBF_btag77_withTop_BCal.root",
	"ttyy_noallhad_VBF_btag77_withTop_BCal.root", "ttH_PowhegPy8_VBF_btag77_withTop_BCal.root",
	"HH_VBF_btag77_withTop_BCal.root"]

# Find available VBF couplings
signals = glob.glob(path+signal+"_l1cvv*cv1_*"+"Validation.root")
couplings = [coupling.replace(path+signal+"_", '').replace("_Validation.root","") for coupling in signals]
couplings.append("l1cvv1cv1")
print("Couplings: "+str(couplings))

# Category used for the scan
category = "VBF_btag77_withTop_BCal"

# Discriminant variable
disc_variable = "m_yy"

to_read = "sumHisto_"+disc_variable+"_"+category

bkg_yields = {}

bkgs_dat = []
bkgs_uncert = []
for bkg in bkgs:
	bkg_file = uproot.open(path+bkg)
	bkg_dat = bkg_file[to_read].values[15:25]
	bkg_uncert = np.sqrt(bkg_file[to_read].variances[15:25])

	bkgs_dat.append(bkg_dat)
	bkgs_uncert.append(bkg_uncert)

	bkg_yields[bkg] = sum(bkg_dat)	

	print(bkg)
	print("yield = " + str(sum(bkg_dat)))

bkg_dat = np.sum(np.array(bkgs_dat), axis=0).tolist()
bkg_uncert = np.sum(np.array(bkgs_uncert), axis=0).tolist()
bkg_yield = sum(bkg_dat)
bkg_yields["total"] = bkg_yield

print("total background yield = " + str(bkg_yield))

obs_dat = bkg_dat

sig_yields = {}
sbs = {}
for coupling in couplings:
	# print("Writing json for coupling " + coupling)
	if coupling == "l1cvv1cv1":
		filename = "VBF_VBF_btag77_withTop_BCal.root"
	else:
		filename = signal+"_"+coupling+"_"+category+".root"

	file = uproot.open(path+filename)
	sig_dat = file[to_read].values[15:25].tolist()
	sig_yield = sum(sig_dat)
	sig_yields[coupling] = sig_yield
	sbs[coupling] = sig_yield/bkg_yield

	print("\t--- " + coupling + " ---")
	print("signal yield = " + str(sig_yield))
	print("s/b (total) = " + str(sig_yield / bkg_yield)) 

	make_json(sig_dat, bkg_dat, bkg_uncert, obs_dat, coupling)

yield_spec = {"bkg_yields" : [bkg_yields], "sig_yields" : [sig_yields], "s/b" : [sbs]} 
with open('yields.json', 'w') as outfile: json.dump( yield_spec , outfile )
