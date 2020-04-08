# Plotting scripts for  HH->bbyy analysis
#
# If you have any questions, please contact us: valentina.maria.cairo@cern.ch, michael.edward.nelson@cern.ch, laura.pereira.sanchez@gmail.com


#Structure:

PyPlotter.py =  A collection of functions for making stack plots from root inputs

histoDictionary.py = A python directory summarising the plotting properties of each histogram produced for the final plots (add your new histograms here)

plottingScheduler.py = Script to stage the various different plots and plotting confirguriations, based on the other dictionaries and functions defined in this package. It reads various arguments from command line (please see below for details and defaults)

PlottingList.py = List of backgrounds, regions and variables to be plotted by plottingScheduler.py.

Histograms generated at the AnalysisFramework step are added to a THStack to make final plots. Currently the x axis limits are defined at previous steps. A rebinning option has been implemented in bbyyPlotter linked to histoDictionary.py option 'rebin'.

#Instructions:

cd bbyyPlotter

setupATLAS

lsetup "root 6.14.04-x86_64-slc6-gcc62-opt"

python plottingScheduler.py 

The various options and default values are:
    parser.add_argument("-m", "--mcOnly", help="", action="store_true", default=False)
    parser.add_argument("-H", "--separateHiggsBackgrounds", help="", action="store_true", default=False)
    parser.add_argument("-l", "--logOn", help="", action="store_true", default=False)
    parser.add_argument("-i", "--inputPath", help="Path to the input directory.",default="../AnalysisFramework/run/plots/")
    parser.add_argument("-o", "--outputPath", help="Path to the output directory.",default="./Plots/")
    parser.add_argument("-p", "--plotDump", help="Option for making plots in different formats.", action="store_true", default=False)
    parser.add_argument("-UB", "--UNBLIND", help="",action="store_true",default=False)

Example commands:

Q: How do I generate data/MC plots, .pdf format only, with the single Higgs backgrounds separated?

A: Run "python plottingScheduler.py -i path_to_inputs -o path_to_output -H".

Q: How do I generate MC-only plots, all plotting formats (.C, .eps, .root, .pdf) with the single Higgs backgrounds separated?

A: Run "python plottingScheduler.py -i path_to_inputs -o path_to_output -H -m -p".

Also note that three signals have currently been added to the histoDictionary, corresponding to a non-resonant signal and two resonant scalar signals. The code can be easily modified to include additional signals by adding the MC name to the histoDictionary and including the signal in the signal list specified in the plottingScheduler. 

# Blinding:

Please note that the "-UB"  option corresponds to unblinding the m(yyjj) plot used in the resonant analysis, which is currently blinded in data above 120 GeV by default. The blinding of m(yy) between 120 GeV and 130 GeV is instead applied at the histogramming level, in AnalysisFramework. The m(yyjj) > 120 GeV blinding only applies to that plot; so, for example, if one was to plot the number of central jets then events with m(yyjj) > 120 GeV would still be added to that plot; they are only hidden in the m(yyjj) plot itself which one typically uses for a resonant bump hunt. This is not the official blinding policy for the analysis at present and is subject to change. 

Q: How do I make all data/MC plots, in all plotting formats, with merged single Higgs backgrounds, the log scale activated, and the data unblinded in m(yyjj)?

A: Run "python plottingScheduler.py -i path_to_inputs -o path_to_output -p -l -UB" (if you dare, naturally).
