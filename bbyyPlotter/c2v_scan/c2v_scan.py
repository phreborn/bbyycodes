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
#c2vs = [1]

# These values are the (non-reweighted) xsecs from 
# https://indico.cern.ch/event/945922/contributions/3976127/attachments/2087239/3506646/yybb_VHHContamination_12August2020_VMMCAIRO_DWENDT.pdf
# slide 12, 125.09 Higgs mass point
n = np.array([5.80822E-05,
              2.0989E-05,
              4.54404E-06,
              8.79087E-06,
              3.37047E-05,
              0.000340078]) * 1000
    
# Rescale xsecs by SM VBF fraction
n /= 0.81771

path = "" # Wherever the json histograms (from hist_to_json.py) are stored
# Note: these histograms should have filenames in the format "VBF_[coupling]_VBF_only.json" 
# (or otherwise change the line below that opens the json)

exp_limits = []
obs_limits = []

all_sig_yields = []
all_bkg_yields = []
all_significances = []
tot_significances = []

mu_maxes = [20, 65, 700, 140, 30, 10]

# Calculate upper limits for each c2v value
for i,c2v in enumerate(c2vs):
    print("Starting c2v = ", c2v)
    c2v_str = str(c2v).replace(".", "p")

    f = open(path + "VBF_l1cvv" + c2v_str + "cv1_VBF_only.json")
    inWSspec = json.load(f)
    
    # Calculate yields and significances
    simple_significances = []
    s_yields = np.array([])
    b_yields = np.array([])
    s_cat_names = [] 
    b_cat_names = []
    for ichan in range(len(inWSspec['channels'])): 
        t_bkg_yield = 0.0 
        t_sig_yield = 0.0
        for isamp in range(len(inWSspec['channels'][ichan])):  
            if( 'signal' in inWSspec['channels'][ichan]['samples'][isamp]['name'] ): 
                s_yields = np.append( s_yields , np.sum( inWSspec['channels'][ichan]['samples'][isamp]['data'] ) )
                s_cat_names.append( inWSspec['channels'][ichan]['samples'][isamp]['name'] )
            elif( 'background' in inWSspec['channels'][ichan]['samples'][isamp]['name'] ):
                b_yields = np.append( b_yields , np.sum( inWSspec['channels'][ichan]['samples'][isamp]['data'] ) )
                b_cat_names.append( inWSspec['channels'][ichan]['samples'][isamp]['name'] )
								
    simple_significances = np.sqrt( 2.0*( (s_yields+b_yields)*np.log(1.0+s_yields/b_yields)-s_yields) ) 
    tot_simple_significance = np.sqrt( np.sum( simple_significances**2 ) )
        
    print('Signal Yields: ')
    for ic,catname in enumerate(s_cat_names): 
        print( catname , " : " , s_yields[ic])
    print('   Total = ',np.sum(s_yields))
    print('Background Yields: ')
    for ic,catname in enumerate(b_cat_names): 
        print( catname , " : " , b_yields[ic])
    print('   Total = ',np.sum(b_yields))
    print('Simple Significances: ')
    for ic,catname in enumerate(s_cat_names): 
        print( catname , " : " , simple_significances[ic])
    print('   Total (in quadrature) = ',tot_simple_significance)
    
    sig_scaling = 1.0
    # Uncomment this section to implement signal rescaling
    while( tot_simple_significance < 0.5 ): 
        sig_scaling *= 2.0 
        scaled_s_yields = sig_scaling*s_yields 
        simple_significances = np.sqrt( 2.0*( (scaled_s_yields+b_yields)*np.log(1.0+scaled_s_yields/b_yields)-scaled_s_yields) ) 
        tot_simple_significance = np.sqrt( np.sum( simple_significances**2 ) ) 
    while( tot_simple_significance > 1 ): 
        sig_scaling *= 0.5 
        scaled_s_yields = sig_scaling*s_yields 
        simple_significances = np.sqrt( 2.0*( (scaled_s_yields+b_yields)*np.log(1.0+scaled_s_yields/b_yields)-scaled_s_yields) ) 
        tot_simple_significance = np.sqrt( np.sum( simple_significances**2 ) ) 
			
#    mu_max = mu_maxes[i]
    mu_max = 10.0
								
    nTests = 201 
    mu_tests = np.linspace(.01,mu_max,nTests)
    scaled_mus = mu_tests * sig_scaling
    while( scaled_mus[1] - scaled_mus[0] > 5.0 ): 
        nTests += 100
        mu_tests = np.linspace(.01,mu_max,nTests)
        scaled_mus = mu_tests * sig_scaling			

    # Optional: print signal scaling
    print("Will apply scaling of ",sig_scaling," to signal input")


			###################################################
			### If scaling required, apply to signal 'data'
			
    if( sig_scaling != 1.0 ):
        for ichan in range(len(inWSspec['channels'])): 
            for isamp in range(len(inWSspec['channels'][ichan])):  
                if( 'signal' in inWSspec['channels'][ichan]['samples'][isamp]['name'] ): 
                    unscaled_data = np.array( inWSspec['channels'][ichan]['samples'][isamp]['data'] , 'd' ) 
                    scaled_data = sig_scaling * unscaled_data
                    scaled_data[ np.where(unscaled_data==1e-06) ] = 1e-09 * sig_scaling 
                    inWSspec['channels'][ichan]['samples'][isamp]['data'] = scaled_data.tolist()
									
			###################################################
			### Finally construct workspace from input spec and perform fit 	
    
    inWS = pyhf.workspace.Workspace(inWSspec)
    inModel = inWS.model(poi_name='mu')
            
    inits = inModel.config.suggested_init()
    inits[ inModel.config.poi_index ] = 0.0
    bounds = inModel.config.suggested_bounds()
#    bounds[0] = (0, mu_max + 0.5)
    expected_bkg = inModel.expected_data( inits )			
									
    hypo_tests = [] 
    for i, mu in enumerate(mu_tests):
        # Optional: give progress updates
#==============================================================================
#         if i % 100 == 0:
#             print("Hypothesis test for mu number ", i, 
#                   " out of ", len(mu_tests), ", c2v = ", c2v)
#==============================================================================
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
	
    
     # Calculate upper limits from CLs
    limits = invert_interval(scaled_mus, hypo_tests, test_size=0.05) 
    
#==============================================================================
#     # Optional: Plot CL_s as a function of mu 
#     fig, ax = plt.subplots()
#     fig.set_size_inches(7, 5)
#     ax.set_xlabel(r"$\mu$ (POI)")
#     ax.set_xlim(0, mu_max)
#     ax.set_ylabel(r"$\mathrm{CL}_{s}$")
#     ax.set_title("c2v = " + str(c2v) + " CLs")
#     ax.fill_between(mu_tests, hypo_test_res_m2s, hypo_test_res_p2s,  facecolor = 'yellow')
#     ax.fill_between(mu_tests, hypo_test_res_m1s, hypo_test_res_p1s,  facecolor = 'lime')
#     ax.plot(mu_tests, hypo_test_res_exp)
#     ax.plot(mu_tests, [0.05] * len(mu_tests))
#     plt.savefig("cvv" + c2v_str + "CLs_VBF_only_sig_scale_all_bkgs.pdf")
#==============================================================================
    
    # Print yields and significances
    print("")
    print("c2v = " + str(c2v) + " limits: ", limits)
    print("")

    exp_limits.append(limits["exp"])
    obs_limits.append(limits["obs"])
    all_sig_yields.append(s_yields)
    all_bkg_yields.append(b_yields)
    all_significances.append(simple_significances)
    tot_significances.append(tot_simple_significance)
    
# Save yields and significances as text files
sig_yields = np.array(all_sig_yields)
bkg_yields = np.array(all_bkg_yields)
significances = np.array(all_significances)
tot_significances = np.array(tot_significances)
#==============================================================================
# np.savetxt("significances_VBF_only2.txt", significances)
# np.savetxt("sig_yields_VBF_only2.txt", sig_yields)
# np.savetxt("bkg_yields__VBF_only2.txt", bkg_yields)
# np.savetxt("tot_significances_VBF_only2.txt", tot_significances)
#==============================================================================

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

# Plot xsec limits
ax.semilogy(c2vs, n * np.array(limit_bands[0]),'k--',label='expected')
ax.fill_between(c2vs, n * np.array(limit_bands[-2]), n * np.array(limit_bands[2]),  facecolor = 'yellow')
ax.fill_between(c2vs, n * np.array(limit_bands[-1]), n * np.array(limit_bands[1]),  facecolor = 'lime')
ax.plot(c2vs,n,'C4',label='theory prediction')
ax.set_ylabel('95% upper limit on $\sigma_{VBF} * BR$ [fb]', fontsize=16)

ylim = [.001,20]
ax.plot([1]*2,ylim,'grey')
ax.set_ylim(ylim)

#==============================================================================
# # Plot mu limits
# ax.semilogy(c2vs, np.array(limit_bands[0]),'k--',label='expected')
# ax.fill_between(c2vs, np.array(limit_bands[-2]), np.array(limit_bands[2]),  facecolor = 'yellow')
# ax.fill_between(c2vs, np.array(limit_bands[-1]), np.array(limit_bands[1]),  facecolor = 'lime')
# ax.set_ylabel('95% upper limit on $\mu$', fontsize=16)
#==============================================================================

# The two commented lines below were inherited
# The extra bands that I wanted to add
#ax.semilogy(lambdas, n * np.array(limit2_bands[0]),color='b',linestyle='--',label='PFlow')



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
