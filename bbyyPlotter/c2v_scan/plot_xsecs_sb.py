# Plots cross-sections and signal-to-background
# ratios as a function of c2v

# Written by David Wendt

import numpy as np
import matplotlib.pyplot as plt

# c2v values used
c2vs = [0, 0.5, 1, 1.5, 2, 4]

# These values are the (non-reweighted) xsecs from 
# https://indico.cern.ch/event/945922/contributions/3976127/attachments/2087239/3506646/yybb_VHHContamination_12August2020_VMMCAIRO_DWENDT.pdf
# slide 12, 125.09 Higgs mass point
xsecs = np.array([5.80822E-05,
                  2.0989E-05,
                  4.54404E-06,
                  8.79087E-06,
                  3.37047E-05,
                  0.000340078]) * 1000

# s/b ratios as outputted in yields.json from hist_to_json.py
sb = {"l1cvv0cv1": 0.11441760019983056,
	"l1cvv4cv1": 0.7545261942116388,
	"l1cvv1p5cv1": 0.01646508338238322,
	"l1cvv2cv1": 0.07544323513067973,
	"l1cvv1cv1": 0.002954343974466316,
	"l1cvv0p5cv1": 0.03664500420617591}

# Convert dictionary to array
sb_list = []
for i,c2v in enumerate(c2vs):
    c2v_str = str(c2v).replace(".", "p")
    coupling = "l1cvv" + c2v_str + "cv1"
    sb_list.append(sb[coupling])
    print(i, xsecs[i] / sb_list[i])

sb_arr = np.array(sb_list)

print(c2vs)
print(xsecs)
print(sb_arr)

# Plot xsecs and sb arrays
# From here down is adapted from https://matplotlib.org/gallery/api/two_scales.html
fig, ax1 = plt.subplots()

color = 'tab:red'
ax1.set_xlabel('$c_{2V}$', fontsize = 16)
ax1.set_ylabel('$\sigma_{VBF}$ (pp -> HH -> bbyy) (fb)', color=color, fontsize = 16)
ax1.set_yscale("log") # optional log scale
ax1.plot(c2vs, xsecs, color=color)
ax1.tick_params(axis='y', labelcolor=color)

ax2 = ax1.twinx()  # instantiate a second axes that shares the same x-axis

color = 'tab:blue'
ax2.set_ylabel('signal / background', color=color, fontsize = 16)  # we already handled the x-label with ax1
ax2.set_yscale("log") # optional log scale
ax2.plot(c2vs, sb_arr, color=color)
ax2.tick_params(axis='y', labelcolor=color)

fig.tight_layout()  # otherwise the right y-label is slightly clipped
plt.show()

plt.savefig("xsec_sb_log_plot.png")
