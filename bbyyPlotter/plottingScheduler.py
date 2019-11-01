'''
  Script to stage the various different plots and
  plotting confirguriations, based on the other dictionaries
  and functions defined in this package.

  M. Nelson, 2019 <michael.edward.nelson@cern.ch>
'''

import os
import sys
import ROOT as r
from array import array
import collections
from math import sqrt
from PyPlotter import *
from histoDictionary import *

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

# List of keys from the histogramming dictionary
histosToPlot = [
                  'sumHisto_m_yy_',
                  'sumHisto_m_jj_',
                  'sumHisto_m_yyjj_tilde_',
                  'sumHisto_deltaR_yy_',
                  'sumHisto_deltaR_jj_',
                  'sumHisto_deltaR_yyjj_',
                  'sumHisto_N_j_',
                  'sumHisto_N_j_central_',
                  'sumHisto_btag_score_',
                  'sumHisto_m_yyjj_tilde_',
                  'sumHisto_MET_',
               ]

# List of keys from the samples dictionary
samplesToStack = [
                    '15_to_18_data',
                    'tty_nohad',
                    'ttyy_nohad',
                    'ttyy_had',
                    'yy',
                    'yybb',
                    'HH',
                    # Then all of the single H backgrounds (these are combined, by default)
                    'ggH',
                    'VBF',
                    'WpH',
                    'WmH',
                    'ZH',
                    'ggZH',
                    'ttH',
                    'bbH',
                    'tWH',
                    'tHjb',
                 ]

# List of selections to plot
selections = [
                'Continuum', # For the continuum backgrounds
                'LM_A', # Category 1
                'LM_B', # Category 2
                'HM_A', # Category 3
                'HM_B', # Category 4
             ]

# Global path to histos within input file
path = ''

# Get the histo and sample dictionaries 
histoDict = PlottingDict()
sampleDict = SampleDict()
selectionDict = SelectionDict()


def main(mcOnly=False,logOn=False,separateHiggsBackgrounds=False,inputPath="",outputPath="./Plots/"):
    
    for selection in selections:

        for histo in histosToPlot:
            # Create the upper pad
            canv =  r.TCanvas("canvas","canvas",600,600)
            if mcOnly and logOn : canv.SetLogy()
            canv.cd()
            
            if not mcOnly:
              padhigh = r.TPad("padhigh","padhigh",0.,0.30,0.90,1.)
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
            ratioHist = r.TH1F()
            dataHist = r.TH1F() # For the ratio
            
            x1, y1, x2, y2 = 0.10, 0.75, 0.90, 0.95
            if separateHiggsBackgrounds: x1, y1, x2, y2 = 0.10, 0.45, 0.90, 0.95
            theLegend = initializeLegend(x1, y1, x2, y2)
            sumHist = r.TH1F()
            
            # Combine the single Higgs backgrounds, unless specified otherwise
            if not separateHiggsBackgrounds: 
                higgsHist = r.TH1F()
                for sample in samplesToStack:
                    if ('H' in sample and 'HH' not in sample) or sample == 'VBF':
                      infile = r.TFile.Open(inDir  + sample + '_' + selection + '.root')
                      theHisto = infile.Get(path + histo)
                      newHisto = theHisto.Clone()
                      getSumHist(newHisto, higgsHist)

            for sample in samplesToStack:
                # Loop over the samples, adding them to the THStack
                infile = r.TFile.Open(inDir  + sample + '_' + selection + '.root')
                if mcOnly and sample == '15_to_18_data': continue # Skip the data if running on MC only
                theHisto = infile.Get(path + histo)
                r.gROOT.cd()
                if sample == '15_to_18_data': 
                    dataHist = theHisto.Clone()  # Get the data
                    dataHist.SetMarkerColor(r.kBlack)
                    ratioHist = dataHist.Clone()
                    theLegend.AddEntry(dataHist,"Data", "lep")
                else:
                  newHisto = theHisto.Clone()
                  if separateHiggsBackgrounds:
                      addStack(newHisto, stackHist, sampleDict[str(sample)]['color'], theLegend, sampleDict[str(sample)]['legend description'])   
                      getSumHist(newHisto, sumHist)
                      continue 
                  elif ('H' in sample and 'HH' not in sample) or sample == 'VBF': continue # To avoid double-counting the single Higgs backgrounds
                  else:                                                                                         
                      addStack(newHisto, stackHist, sampleDict[str(sample)]['color'], theLegend, sampleDict[str(sample)]['legend description'])   
                      getSumHist(newHisto, sumHist)

            # Add the combined single Higgs backgrounds back in, unless specified otherwise
            if not separateHiggsBackgrounds:
                addStack(higgsHist, stackHist, 4, theLegend, 'Single Higgs')   
                getSumHist(higgsHist, sumHist)

            # Divide and get the ratio
            ratioHist.Divide(sumHist)

            # Apply nice ATLAS-style plotting here
            stackHist.ls()
            stackHist.Draw("HIST")
            if mcOnly: stackHist.GetXaxis().SetTitle(histoDict[str(histoOrig)]['x-axis title'])
            stackHist.GetYaxis().SetTitle(histoDict[str(histoOrig)]['y-axis title'])
            #stackHist.GetXaxis().Set(histoDict[str(histoOrig)]['nBinsX']+2, histoDict[str(histoOrig)]['x-min'], histoDict[str(histoOrig)]['x-max'])
            stackHist.GetXaxis().SetNdivisions(306)
            stackHist.SetMaximum(1.45*stackHist.GetMaximum())
            if not mcOnly : 
                   stackHist.GetXaxis().SetLabelOffset(999)
                   stackHist.GetXaxis().SetLabelSize(0)
                   stackHist.SetMaximum(1.45*dataHist.GetMaximum())
         
            # Draw the relevant data 
            if not mcOnly: 
              dataHist.Draw("E0 SAME")

            # Set up latex and the ATLAS label
            l = r.TLatex()
            l.SetNDC()
            l.SetTextColor(r.kBlack)

            r.ATLASLabel(0.55,0.88,"Internal")
            l.SetTextFont(42)
            l.SetTextSize(0.04)
            l.DrawLatex(0.55, 0.84, "#sqrt{#it{s}} = 13 TeV, 139.7 fb^{-1}")
            l.DrawLatex(0.55, 0.80, selectionDict[str(selection)]['legend upper'])
            l.DrawLatex(0.55, 0.76, selectionDict[str(selection)]['legend lower'])
            
            # Add the legend to a separare, sideways pad
            canv.cd()
            padside = r.TPad("padside","padside",0.80,0.0,0.95,1.)
            if mcOnly : padside = r.TPad("padside","padside",0.85,0.0,0.98,1.)
            padside.SetFillStyle(4000)
            padside.SetGrid(0,0)
            padside.Draw()
            padside.cd()
            theLegend.Draw("SAME")
            
            # Set up the lower pad
            if not mcOnly:
              canv.cd()
              padlow = r.TPad("padlow","padlow",0.,0.0,0.90,0.30)
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
            if mcOnly: extra = '_SumMC'
            if separateHiggsBackgrounds: extra = '_separateSingleHiggsBkgs'
            #canv.Print(outDir + histo + extra + ".C", "C")
            #canv.Print(outDir + histo + extra + ".png", "png")
            canv.Print(outDir + histo + extra + ".pdf", "pdf")
            #canv.Print(outDir + histo + extra + ".eps", "eps")
        
if __name__ == "__main__":
    
    # Adding an argument parser, which we might want to use 
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument("-m", "--mcOnly", help="", action="store_true", default=False)
    parser.add_argument("-H", "--separateHiggsBackgrounds", help="", action="store_true", default=False)
    parser.add_argument("-l", "--logOn", help="", action="store_true", default=False)
    parser.add_argument("-i", "--inputPath", help="Path to the input directory.",default="")
    parser.add_argument("-o", "--outputPath", help="Path to the output directory.",default="./Plots/") 
  
    options = parser.parse_args()

    # Input and output directories
    inDir = options.inputPath
    outDir = options.outputPath
    if not os.path.exists(outDir):
           os.makedirs(outDir)
           print "The output directlory did not exist, I have just created one: ", outDir   
 
    # Defining dictionary to be passed to the main function
    option_dict = dict( (k, v) for k, v in vars(options).iteritems() if v is not None)
    print option_dict
    main(**option_dict)
