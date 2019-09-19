# Plotting scripts for  HH->bbyy analysis
#
# If you have any questions, please contact us: valentina.maria.cairo@cern.ch, michael.edward.nelson@cern.ch


#Structure:

PyPlotter.py =  A collection of functions for making stack plots from root inputs

histoDictionary.py = A python directory summarising the plotting properties of each histogram produced for the final plots (add your new histograms here)

plottingScheduler.py = Script to stage the various different plots and plotting confirguriations, based on the other dictionaries and functions defined in this package. It reads 3 arguments from command line: -m for mcOnly usage (defaulted to false), -i for path_to_inputs (defaulted to ""), -o for path_to_output (defaulted to "./Plots/")


#Instructions:

cd bbyyPlotter

setupATLAS

lsetup "root 6.14.04-x86_64-slc6-gcc62-opt"

python plottingScheduler.py -m -i path_to_inputs -o path_to_output

