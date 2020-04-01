'''
  Script to stage the various different plots and
  plotting confirguriations, based on the other dictionaries
  and functions defined in this package.

  M. Nelson, 2019 <michael.edward.nelson@cern.ch>
'''

# Laura: XsubRange is not yet fully implemented - leave commented out. I am trying to make it zoom in some part of the plot with new xmin, xmax if needed 

import os
import sys
import ROOT as r
from array import array
import collections
from math import sqrt
from PyPlotter import *
from histoDictionary import *
from PlottingList import*

# ROOT global plot settings
r.gROOT.LoadMacro("./atlasstyle-00-03-05/AtlasStyle.C")
r.gROOT.LoadMacro("./atlasstyle-00-03-05/AtlasLabels.C")
r.gROOT.LoadMacro("./atlasstyle-00-03-05/AtlasUtils.C")
r.SetAtlasStyle()

r.gROOT.SetBatch(1)
r.gStyle.SetPalette(56) 
r.gStyle.SetPadLeftMargin(0.15) 
r.gStyle.SetPadRightMargin(0.10)
r.gStyle.SetPadBottomMargin(0.15)
r.gStyle.SetPadTopMargin(0.05)
r.gStyle.SetNumberContours(999)

# Lists of keys (samples, variables & regions) can be found in PlottingList.py

# Global path to histos within input file
path = ""

# Get the histo and sample dictionaries 
histoDict = PlottingDict()
sampleDict = SampleDict()
selectionDict = SelectionDict()
signalDict = SignalDict()

debug = True
#XsubRange = False
 
def main(plotDump=False,UNBLIND=False,mcOnly=False,logOn=False,separateHiggsBackgrounds=False,inputPath="",outputPath="./Plots/"):
    
    if UNBLIND: print 'WARNING: You have unblinded the analysis! Are you sure you want to do this?'

    for selection in selections:

        for histo in histosToPlot:
            # Create the upper pad
            canv =  r.TCanvas("canvas","canvas",600,600)
            if mcOnly and logOn : canv.SetLogy()
            canv.cd()
            
            if mcOnly: 
                r.gStyle.SetPadLeftMargin(0.20)
                padhigh = r.TPad("padhigh","padhigh",0.0,0.0,0.85,1.)
                padhigh.SetBottomMargin(0.15)
            if not mcOnly: 
                padhigh = r.TPad("padhigh","padhigh",0.,0.30,0.85,1.)
                padhigh.SetBottomMargin(0.02)
            padhigh.SetGrid(0,0)
            if logOn: padhigh.SetLogy()
            padhigh.Draw()
            padhigh.cd()
            
            # Add the selection
            histoOrig = histo
            histo = histo + selection

            theHisto = r.TH1F()
            stackHist = r.THStack()
            sigHist = r.THStack()
            ratioHist = r.TH1F()
            dataHist = r.TH1F() # For the ratio
            dataGraph = r.TGraphErrors()

            x1, y1, x2, y2 = 0.10, 0.55, 0.90, 0.95 
            if separateHiggsBackgrounds or len(signals)>6: y1 = 0.35
            if len(signals)>10: y1 = 0.15
            theLegend = initializeLegend(x1, y1, x2, y2)
            sumHist = r.TH1F()

            for sample in samplesToStack:
                # Loop over the samples, adding them to the THStack
                infile = r.TFile.Open(inDir  + sample + '_' + selection + '.root')
                if mcOnly and sample == '15_to_18_data': continue # Skip the data if running on MC only
                theHisto = infile.Get(path + histo)                
                if ((sample == samplesToStack[0]) or (mcOnly and sample == samplesToStack[1])):                     
                    y_title = GetYtitle(theHisto, histoDict[str(histoOrig)]['rebin'], histoDict[histoOrig]['units'])                    
                #XsubRange = CheckXrange(theHisto, histoDict[histoOrig]['x-min'], histoDict[histoOrig]['x-max'])
                theHisto.Rebin(histoDict[str(histoOrig)]['rebin'])                
                #if XsubRange: theHisto.GetXaxis().SetRangeUser(histoDict[histoOrig]['x-min'],histoDict[histoOrig]['x-max'])            

                r.gROOT.cd()                
                if sample == '15_to_18_data':                    
                    dataHist = theHisto.Clone()  # Get the data
                    if not UNBLIND and 'm_yyjj' in histo: # Blind the m_yyjj for the resonant search
                        for xbin in range(0, dataHist.GetNbinsX()+1):
                            if dataHist.GetXaxis().GetBinCenter(xbin) > 120: 
                                dataHist.SetBinContent(xbin,0) 
                                dataHist.SetBinError(xbin,0.0001) 
                    # Transfer the histo information to a TGraph for upper pad plotting
                    for xbin in range(0, dataHist.GetNbinsX()+1):
                        if dataHist.GetBinContent(xbin) > 0.: # Don't plot markers for zero-valued data points
                          dataGraph.SetPoint(xbin, dataHist.GetXaxis().GetBinCenter(xbin), dataHist.GetBinContent(xbin))
                          dataGraph.SetPointError(xbin, 0, dataHist.GetBinError(xbin))

                    #if XsubRange :dataGraph.GetXaxis().SetRangeUser(histoDict[histoOrig]['x-min'],histoDict[histoOrig]['x-max'])
                    
                    dataGraph.SetMarkerColor(r.kBlack)
                    dataGraph.SetMarkerStyle(r.kFullDotLarge)
                    dataGraph.SetLineColor(r.kBlack)
                    dataGraph.SetLineWidth(2)
                    dataHist.SetMarkerColor(r.kBlack)                    
                    ratioHist = dataHist.Clone()
                    #theLegend.AddEntry(dataHist,"Data", "lep")
                    theLegend.AddEntry(dataGraph,"Data", "lep")
                else:
                  newHisto = theHisto.Clone()
                  if separateHiggsBackgrounds:
                      addStack(newHisto, stackHist, sampleDict[str(sample)]['color'], theLegend, sampleDict[str(sample)]['legend description'])  
                      getSumHist(newHisto, sumHist)
                      continue 
                  elif ('H' in sample and 'HH' not in sample) or sample == 'VBF': continue # To avoid double-counting the single Higgs backgrounds
                  else:                                                                                         

                      if debug : print "Adding "+sample
                      addStack(newHisto, stackHist, sampleDict[str(sample)]['color'], theLegend, sampleDict[str(sample)]['legend description']) 
                      getSumHist(newHisto, sumHist)
                      

            # Combine the single Higgs backgrounds, unless specified otherwise                                                                    
            if not separateHiggsBackgrounds:
                higgsHist = r.TH1F()
                for sample in samplesToStack:
                    if ('H' in sample and 'HH' not in sample) or sample == 'VBF':
                        infile = r.TFile.Open(inDir  + sample + '_' + selection + '.root')
                        theHisto = infile.Get(path + histo)
                        theHisto.Rebin(histoDict[str(histoOrig)]['rebin'])
                        #if XsubRange: theHisto.GetXaxis().SetRangeUser(histoDict[histoOrig]['x-min'],histoDict[histoOrig]['x-max'])
                        newHisto = theHisto.Clone()
                        getSumHist(newHisto, higgsHist)                        
                # Add the combined single Higgs backgrounds back in, unless specified otherwise
                if debug : print "Adding single Higgs"
                addStack(higgsHist, stackHist, 4, theLegend, 'Single Higgs')   
                getSumHist(higgsHist, sumHist)
            
            # Divide and get the ratio
            if not mcOnly: ratioHist.Divide(sumHist)

            # Apply nice ATLAS-style plotting here
            stackHist.ls()
            stackHist.Draw("HIST")
            if mcOnly: 
                stackHist.GetXaxis().SetTitle(histoDict[str(histoOrig)]['x-axis title'])
                stackHist.GetYaxis().SetTitleOffset(2)
            stackHist.GetYaxis().SetTitle(y_title)
            stackHist.GetXaxis().SetNdivisions(306)
            stackHist.SetMaximum(1.45*stackHist.GetMaximum())

            if not mcOnly : 
                   stackHist.GetXaxis().SetLabelOffset(999)
                   stackHist.GetXaxis().SetLabelSize(0)
                   if 'm_yyjj' in histo:
                      stackHist.SetMaximum(1.45*stackHist.GetMaximum())
                   else:
                      stackHist.SetMaximum(1.45*dataHist.GetMaximum())


            #for nbin in range(0,sumHist.GetNbinsX()):
                #sumHist.SetBinError(nbin, sumHist.GetBinError(nbin)) #Laura

            sumHist.SetMarkerSize(0)
            sumHist.SetFillColor(12)
            sumHist.SetFillStyle(3357)
            theLegend.AddEntry(sumHist,"Total SM", "f")

            sumHist.Draw("E2 SAME") 
            # Draw the relevant data 
            if not mcOnly: 
                dataGraph.Draw("EP SAME")
            
            # Inject the relevant signals
            for sample in signals:                
                if debug: print ("Signal = ",sample)
                infile = r.TFile.Open(inDir  + sample + '_' + selection + '.root')
                theHisto = infile.Get(path + histo)
                if (sample == signals[0]):
                    y_title = GetYtitle(theHisto, histoDict[str(histoOrig)]['rebin'], histoDict[histoOrig]['units'])
                theHisto.Rebin(histoDict[str(histoOrig)]['rebin'])
                #if XsubRange : theHisto.GetXaxis().SetRangeUser(histoDict[histoOrig]['x-min'],histoDict[histoOrig]['x-max'])
                r.gROOT.cd()
                newHisto = theHisto.Clone()
                addSignalStack(newHisto, sigHist, signalDict[str(sample)]['color'], theLegend, signalDict[str(sample)]['legend description'])

            sigHist.Draw("HIST nostack SAME")
            # Set up latex and the ATLAS label
            l = r.TLatex()
            l.SetNDC()
            l.SetTextColor(r.kBlack)

            l1, l2 = 0.55, 0.88
            if mcOnly: l1, l2 = 0.45, 0.88
            r.ATLASLabel(l1,l2,"Internal")
            l.SetTextFont(42)
            l.SetTextSize(0.04)
            l.DrawLatex(l1, 0.84, "#sqrt{#it{s}} = 13 TeV, 139.7 fb^{-1}")
            l.DrawLatex(l1, 0.80, selectionDict[str(selection)]['legend upper'])
            l.DrawLatex(l1, 0.76, selectionDict[str(selection)]['legend lower'])
            
            # Add the legend to a separare, sideways pad
            canv.cd()
            padside = r.TPad("padside","padside",0.75,0.0,0.98,1.)
            padside.SetFillStyle(4000)
            padside.SetGrid(0,0)
            padside.Draw()
            padside.cd()
            theLegend.Draw("SAME")

            # Set up the lower pad
            if not mcOnly:
              canv.cd()
              padlow = r.TPad("padlow","padlow",0.,0.0,0.85,0.30)
              padlow.SetFillStyle(4000)
              padlow.SetGrid(0,0)
              padlow.SetTopMargin(0.05)
              padlow.SetBottomMargin(0.30)
              padlow.Draw()
              padlow.cd()
              
              # A few additional aesthetics for the ratio
              ratioHist.GetYaxis().SetTitle("Data/Pred.")
              ratioHist.GetYaxis().CenterTitle()
              ratioHist.GetYaxis().SetNdivisions(306)
              ratioHist.GetYaxis().SetTitleOffset(0.5)
              ratioHist.GetYaxis().SetTitleSize(0.12)
              ratioHist.GetYaxis().SetLabelSize(0.10)
              ratioHist.GetXaxis().SetNdivisions(306)
              ratioHist.GetXaxis().SetTitle(histoDict[str(histoOrig)]['x-axis title'])
              ratioHist.GetXaxis().SetTitleSize(0.10)
              ratioHist.GetXaxis().SetLabelFont(43)
              ratioHist.GetXaxis().SetLabelSize(20)
              ratioHist.Draw("EP") 

            # Add line to the ratio plot
            rl = r.TLine()
            rl.SetLineColor(r.kRed)
            rl.SetLineWidth(3)
            if not mcOnly: rl.DrawLine(ratioHist.GetBinLowEdge(1), 1., ratioHist.GetBinLowEdge(ratioHist.GetNbinsX()+1), 1.)
            
            # Save canvas to png, pdf, eps, and C
            extra = ''
            if mcOnly: extra = '_onlyMC'
            if separateHiggsBackgrounds: extra = '_separateSingleHiggsBkgs'
            if separateHiggsBackgrounds and mcOnly : extra = '_separateSingleHiggsBkgs_SumMC'

            if plotDump:
                canv.Print(outDir + histo + extra + ".C", "C")
                canv.Print(outDir + histo + extra + ".png", "png")
                canv.Print(outDir + histo + extra + ".pdf", "pdf")
                canv.Print(outDir + histo + extra + ".eps", "eps")
                canv.Print(outDir + histo + extra + ".root", "root")
            else:
                canv.Print(outDir + histo + extra + ".pdf", "pdf")
                    
if __name__ == "__main__":
    
    # Adding an argument parser, which we might want to use 
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument("-m", "--mcOnly", help="", action="store_true", default=False)
    parser.add_argument("-H", "--separateHiggsBackgrounds", help="", action="store_true", default=False)
    parser.add_argument("-l", "--logOn", help="", action="store_true", default=False)
    parser.add_argument("-i", "--inputPath", help="Path to the input directory.",default="../AnalysisFramework/run/plots/")
    parser.add_argument("-o", "--outputPath", help="Path to the output directory.",default="./Plots/") 
    parser.add_argument("-p", "--plotDump", help="Option for making plots in different formats.", action="store_true", default=False) 
    parser.add_argument("-UB", "--UNBLIND", help="",action="store_true",default=False) 
  
    options = parser.parse_args()

    # Input and output directories
    inDir = options.inputPath
    outDir = options.outputPath
    if not os.path.exists(outDir):
           os.makedirs(outDir)
           print "The output directory did not exist, I have just created one: ", outDir   


    # Defining dictionary to be passed to the main function
    option_dict = dict( (k, v) for k, v in vars(options).iteritems() if v is not None)
    print option_dict
    main(**option_dict)
