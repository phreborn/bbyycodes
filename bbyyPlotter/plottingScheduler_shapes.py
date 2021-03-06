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
                  'sumHisto_pT_yy_',
                  'sumHisto_pT_jj_',
                  'sumHisto_m_yy_',
                  'sumHisto_m_jj_',
                  'sumHisto_m_yyjj_tilde_',
                  'sumHisto_pT_jj_div_m_yyjj_tilde_',
                  'sumHisto_pT_yy_div_m_yyjj_tilde_',
                  'sumHisto_pT_jj_div_m_jj_',
                  'sumHisto_pT_yy_div_m_yy_',
                  'sumHisto_deltaR_yy_',
                  'sumHisto_deltaR_jj_',
                  'sumHisto_deltaR_yyjj_',
                  'sumHisto_N_j_',
                  'sumHisto_N_j_central_',
                  'sumHisto_btag_score_',
                  'sumHisto_m_yyjj_tilde_HM_',
                  'sumHisto_MET_',
               ]

# List of keys from the samples dictionary
samplesToStack = [
                    #'tty_nohad',
                    #'ttyy_nohad',
                    #'ttyy_had',
                    'HH',
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


def main(mcOnly=False,inputPath="",outputPath="./Plots/"):
    for selection in selections:
        # Declare the data and ratio histograms once only
        dataHist = r.TH1F()

        for histo in histosToPlot:
            # Create the upper pad
            canv =  r.TCanvas("canvas","canvas",600,600)
            #canv.SetLogy()
            canv.cd()

            if not mcOnly:
              padhigh = r.TPad("padhigh","padhigh",0.,0.28,1.,1.,0)
              padhigh.SetGrid(0,0)
              padhigh.SetBottomMargin(0.05)
              padhigh.Draw()
              padhigh.cd()
            
            # Add the selection
            histoOrig = histo
            histo = histo + selection

            theHisto = r.TH1F()
            ratioHist = r.TH1F()
            gStyle = r.TStyle()
            theLegend = initializeLegend(0.60,0.45,0.85,0.75)
            sumHist = r.TH1F()
	    histos=[]
            for sample in samplesToStack:
                # Loop over the samples
                infile = r.TFile.Open(inDir  + sample + '_' + selection + '.root')
                #print sample
                #print "HISTO::::::::::::"+histo
                #print "Path::::::::::::"+path
                theHisto = infile.Get(path + histo)
		theHisto.SetDirectory(0)
                r.gROOT.cd()
                newHisto = theHisto.Clone()
		#newHisto = theHisto
                histos.append(newHisto)
                if 'data' in infile: 
                  dataHist = newHisto # Get the data
                else:
                  shape(newHisto, sampleDict[str(sample)]['color'], theLegend, sampleDict[str(sample)]['legend description'])
                  
                  #sumHist = getSumHist(newHisto, sumHist, sampleDict[str(sample)]['color'])
                  integral=newHisto.Integral()
                  #print "histo, path, integral+ " + histo + " " + path + " ", integral
                  if (integral >0) : 
                      newHisto.Scale(1/integral)
		  else:
                      newHisto.Scale(1/1)
                  #newHisto.Draw("same")
                  #theHisto.GetYaxis().SetRangeUser(0.0,0.7)
                  newHisto.GetXaxis().SetTitle(histoDict[str(histoOrig)]['x-axis title'])  
                  newHisto.GetYaxis().SetTitle(histoDict[str(histoOrig)]['y-axis title'])
                  newHisto.GetXaxis().Set(histoDict[str(histoOrig)]['nBinsX']+2, histoDict[str(histoOrig)]['x-min'], histoDict[str(histoOrig)]['x-max'])
                  newHisto.GetXaxis().SetNdivisions(306)
                  #theHisto.GetYaxis().SetLimits(0.0,0.7)
                  newHisto.Draw("same,hist")
                  newHisto.GetYaxis().SetRangeUser(0.0,0.7)
            #canv_h =  r.TCanvas("canv_h","canv_h",600,600)
            #canv.SetLogy()
            #canv_h.cd()
            #for h in histos:
	    #	shape(h, sampleDict[str(sample)]['color'], theLegend, sampleDict[str(sample)]['legend description'])
            #    h.DrawNormalized("same,hist")
            #canv_h.SaveAs(outDir + histo + "_shape_TEST.pdf");

            if not mcOnly: addRatio(ratioHist, dataHist, sumHist, histoDict[str(histoOrig)]['x-axis title']) # This needs fixing
            
            # Apply nice ATLAS-style plotting here
            #stackHist.ls()
            #stackHist.Draw("HIST")
            print histoDict[str(histoOrig)]['y-axis title']
            print histoDict[str(histoOrig)]['x-axis title']
            print histoDict[str(histoOrig)]['nBinsX']+2, histoDict[str(histoOrig)]['x-min'], histoDict[str(histoOrig)]['x-max']
            #if mcOnly: 
            #theHisto.GetXaxis().SetTitle(histoDict[str(histoOrig)]['x-axis title'])
            #theHisto.GetYaxis().SetTitle(histoDict[str(histoOrig)]['y-axis title'])
            #theHisto.GetXaxis().Set(histoDict[str(histoOrig)]['nBinsX']+2, histoDict[str(histoOrig)]['x-min'], histoDict[str(histoOrig)]['x-max'])
            #theHisto.GetXaxis().SetNdivisions(306)
            #theHisto.GetYaxis().SetRangeUser(0.0,0.7)    
        
            # Draw the relevant histograms
            if not mcOnly: 
             dataHist.Draw("E0 SAME")
             theLegend.AddEntry(dataHist, "Data 2015-2018", "f")
            theLegend.Draw("same")
            #theLegend.Draw()
            
            # Set up latex and the ATLAS label
            l = r.TLatex()
            l.SetNDC()
            l.SetTextColor(r.kBlack)
            l.SetTextFont(42)
            l.SetTextSize(0.04)

            r.ATLASLabel(0.493,0.88,"Internal")
            l.SetTextFont(42)
            l.SetTextSize(0.04)
            l.DrawLatex(0.493, 0.84, "#it{L} = 139 fb^{-1}")
            l.DrawLatex(0.493, 0.80, selectionDict[str(selection)]['legend upper'])
            l.DrawLatex(0.493, 0.76, selectionDict[str(selection)]['legend lower'])
            
            # Set up the lower pad
            if not mcOnly:
              padlow = r.TPad("padlow","padlow",0.,0.,1.,0.33,0)
              padlow.SetFillStyle(4000)
              padlow.SetGrid(1,1)
              padlow.SetTopMargin(0.05)
              padlow.SetBottomMargin(0.3)
              padlow.Draw()
              padlow.cd()
              ratioHist.Draw("ep")

            # Add line to the ratio plot
            rl = r.TLine()
            rl.SetLineColor(2)
            if not mcOnly: rl.DrawLine(ratioHist.GetBinLowEdge(1), 1., ratioHist.GetBinLowEdge(ratioHist.GetNbinsX()+1), 1.)
            
            #theLegend.Draw();
            # Save canvas to png, pdf, eps, and C
            canv.Print(outDir + histo + "_shape.C", "C")
            canv.Print(outDir + histo + "_shape.png", "png")
            canv.Print(outDir + histo + "_shape.pdf", "pdf")
	    #canvShape.Print("Test.pdf")
            canv.Print(outDir + histo + "_shape.eps", "eps")

        
if __name__ == "__main__":
    
    # Adding an argument parser, which we might want to use 
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument("-m", "--mcOnly", help="", action="store_true", default=False)
    parser.add_argument("-i", "--inputPath", help="Path to the input directory.",default="")
    parser.add_argument("-o", "--outputPath", help="Path to the output directory.",default="./Plots/") 
  
    options = parser.parse_args()

    # Input and output directories
    inDir = options.inputPath
    outDir = options.outputPath
    if not os.path.exists(outDir):
           os.makedirs(outDir)
           print("The output directlory did not exist, I have just created one: " + outDir)   
 
    #Defining dictionary to be passed to the main function
    option_dict = dict( (k, v) for k, v in vars(options).iteritems() if v is not None)
    print option_dict
    main(**option_dict)
