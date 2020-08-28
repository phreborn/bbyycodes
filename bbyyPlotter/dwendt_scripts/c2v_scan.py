# Performs a c2v scan by reading myy histograms from jsons,
# calculating xsec upper limits using pyhf, and plotting
# against theory line

# Adapted by David Wendt from 
# https://gitlab.cern.ch/atlas-physics/HDBS/DiHiggs/yybb/code/-/blob/v_6.0/bbyyPlotter/plot_kl_scan.py by (?) Alex Wang
# and https://gitlab.cern.ch/rahynema/hh4b-vbf-limits/-/tree/master by Rachel Hyneman

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import collections
import json
import pyhf 
import sys

# Find bounds on mu
def invert_interval(test_mus, hypo_tests, test_size=0.05):
    cls_obs = np.array([test[0] for test in hypo_tests]).flatten()
    cls_exp = [
        np.array([test[1][i] for test in hypo_tests]).flatten() for i in range(5)
    ]
    crossing_test_stats = {"exp": [], "obs": None}
    for cls_exp_sigma in cls_exp:
        crossing_test_stats["exp"].append(
            np.interp(
                test_size, list(reversed(cls_exp_sigma)), list(reversed(test_mus))
            )
        )
    crossing_test_stats["obs"] = np.interp(
        test_size, list(reversed(cls_obs)), list(reversed(test_mus))
    )
    return crossing_test_stats

stdText = '$\mathbf{ATLAS}$ Internal\n'
stdText += r'$\sqrt{s} = $ 13 TeV, 139fb$^{-1}$'+'\n'
stdText += r'$HH\rightarrow \gamma\gamma bb$'
stdText += '\nStats only limit'

# c2v values that we use
c2vs = [0, 0.5, 1, 1.5, 2, 4]

# These values are the (non-reweighted) xsecs from 
# https://indico.cern.ch/event/945922/contributions/3976127/attachments/2087239/3506646/yybb_VHHContamination_12August2020_VMMCAIRO_DWENDT.pdf
# slide 12, 125.09 Higgs mass point
n = np.array([5.80822E-05,
              2.0989E-05,
              4.54404E-06,
              8.79087E-06,
              3.37047E-05,
              0.000340078]) * 1000

path = "" # Wherever the json histograms (from hist_to_json.py) are stored
# Note: these histograms should have filenames in the format "VBF_[coupling].json" 
# (or otherwise change the line below that opens the json)

exp_limits = []
obs_limits = []

# Calculate upper limits for each c2v value
for i,c2v in enumerate(c2vs):
    c2v_str = str(c2v).replace(".", "p")
    
    nTests = 201 
    mu_tests = np.linspace(0.01,650.,nTests)
    while( mu_tests[1] - mu_tests[0] > 1.0 ): 
        nTests += 100
        mu_tests = np.linspace(.01,650.,nTests)
        

    f = open(path + "VBF_l1cvv" + c2v_str + "cv1.json")
    inWSspec = json.load(f)
    
    inWS = pyhf.workspace.Workspace(inWSspec)
    inModel = inWS.model(poi_name='mu')
			
    inits = inModel.config.suggested_init()
    inits[ inModel.config.poi_index ] = 0.0
    bounds = inModel.config.suggested_bounds()
    bounds[0] = (0, 650.5)
    expected_bkg = inModel.expected_data( inits )			
									
    hypo_tests = [] 
    for mu in mu_tests:
        hypo_tests.append( pyhf.infer.hypotest(
                mu,
                expected_bkg,
                inModel, 
                init_pars=inits,
                par_bounds=bounds,
                return_expected_set=True,
                qtilde=True ) )
        
    hypo_test_res_p2s = np.zeros( len(mu_tests) , 'd' )
    hypo_test_res_p1s = np.zeros( len(mu_tests) , 'd' )
    hypo_test_res_exp = np.zeros( len(mu_tests) , 'd' )
    hypo_test_res_m1s = np.zeros( len(mu_tests) , 'd' )
    hypo_test_res_m2s = np.zeros( len(mu_tests) , 'd' )
    hypo_test_res_obs = np.zeros( len(mu_tests) , 'd' )
    	
    for imu in range(len(mu_tests)): 
        hypo_test_res_m2s[imu] =  hypo_tests[imu][1][0]
        hypo_test_res_m1s[imu] = hypo_tests[imu][1][1]
        hypo_test_res_exp[imu] = hypo_tests[imu][1][2]
        hypo_test_res_p1s[imu] = hypo_tests[imu][1][3]
        hypo_test_res_p2s[imu] = hypo_tests[imu][1][4]
        hypo_test_res_obs[imu] = hypo_tests[imu][0]
	
    # (optional) Plot CL_s as a function of mu 
    fig, ax = plt.subplots()
    fig.set_size_inches(7, 5)
    ax.set_xlabel(r"$\mu$ (POI)")
    ax.set_ylabel(r"$\mathrm{CL}_{s}$")
    ax.set_title("c2v = " + str(c2v) + " CLs")
    ax.fill_between(mu_tests, hypo_test_res_m2s, hypo_test_res_p2s,  facecolor = 'yellow')
    ax.fill_between(mu_tests, hypo_test_res_m1s, hypo_test_res_p1s,  facecolor = 'lime')
    ax.plot(mu_tests, hypo_test_res_exp)
    ax.plot(mu_tests, [0.05] * len(mu_tests))
    plt.savefig("cvv" + c2v_str + "CLs.pdf")
    
    # Calculate upper limits from CLs
    limits = invert_interval(mu_tests, hypo_tests, test_size=0.05) 
    print("c2v = " + str(c2v) + " limits: ", limits) 

    exp_limits.append(limits["exp"])
    obs_limits.append(limits["obs"])

# From here down is plotting the limits
limits = np.array(exp_limits)
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


ax.semilogy(c2vs, n * np.array(limit_bands[0]),'k--',label='expected')

ax.fill_between(c2vs, n * np.array(limit_bands[-2]), n * np.array(limit_bands[2]),  facecolor = 'yellow')
ax.fill_between(c2vs, n * np.array(limit_bands[-1]), n * np.array(limit_bands[1]),  facecolor = 'lime')

# The two commented lines below were inherited
# The extra bands that I wanted to add
#ax.semilogy(lambdas, n * np.array(limit2_bands[0]),color='b',linestyle='--',label='PFlow')

ax.plot(c2vs,n,'C4',label='theory prediction')

ylim = [.001,20]
ax.plot([1]*2,ylim,'grey')
ax.set_ylim(ylim)

ax.set_ylabel('95% upper limit on $\sigma_{VBF} * BR$ [pb]', fontsize=16)
ax.legend(loc='lower right')

if (add_subplot):
    ax2.plot(c2vs,np.array(limit2_bands[0])/np.array(limit_bands[0]),color='b',linestyle='--')

    ax2.plot(c2vs,np.ones_like(c2vs),'k--')

    ax2.set_xlabel('$c_{2V}$', fontsize=16)
    ax2.set_ylabel('1 / baseline')
    ax2.set_ylim(0.5,1.5)
else:
    ax.set_xlabel('$c_{2V}$', fontsize=16)


ax.text(0.025,.975,stdText,ha='left',va='top',transform=ax.transAxes)

plt.savefig('c2v_scan.pdf')
