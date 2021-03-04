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

debug = True # Set to true to see added samples
#rebin = True # Set to false if you want to use the original binning and edges of the TH1F used as input. Else set to true if you want to use histoDictionary to set the plot edges and the rebin value.
rebin = False # Set to false if you want to use the original binning and edges of the TH1F used as input. Else set to true if you want to use histoDictionary to set the plot edges and the rebin value.
include_ratio = False

def createUpperPad(mcOnly=True, logOn=False):
  if mcOnly or not include_ratio: 
  #    r.gStyle.SetPadLeftMargin(0.20)
      padhigh = r.TPad("padhigh","padhigh",0.0,0.0,0.85,1.)
      padhigh.SetBottomMargin(0.15)
  if include_ratio: 
      padhigh = r.TPad("padhigh","padhigh",0.0,0.3,0.85,1.)
      padhigh.SetBottomMargin(0.02)

  if logOn: 
      padhigh.SetLogy()
  return padhigh

def main(plotDump=False, UNBLIND=False, mcOnly=False, logOn=False, separateHiggsBackgrounds=False, inputPath="", outputPath="./Plots/"):
              
  XsubRange = False 

  if UNBLIND:
      print('WARNING: You have unblinded the analysis! Are you sure you want to do this?')

  for selection in selections: # selections defined in PlottingList.py (LM_Tight etc)
      print("Number of histograms to plot:"+str(len(histosToPlot)))
      for histo in histosToPlot:
          print("Plotting"+histo+selection)

          # Create the canvas 
          canv =  r.TCanvas("canvas","canvas",600,600)
          canv.cd()
          
          # Create the upper pad, leaving room for ratio plot if including data
          padhigh = createUpperPad(mcOnly,logOn)
          padhigh.Draw()
          padhigh.SetGrid(0,0)
          padhigh.cd()

          theHisto = r.TH1F()
          stackHist = r.THStack()
          sigHist = r.THStack()
          ratioHist = r.TH1F()
          dataHist = r.TH1F() # For the ratio
          sumHist = r.TH1F()
          dihiggsHist = r.TH1F()
          ttyyHist = r.TH1F()
          dataGraph = r.TGraphErrors()
          dataGraph.SetMarkerColor(r.kBlack)
          dataGraph.SetMarkerStyle(r.kFullDotLarge)
          dataGraph.SetLineColor(r.kBlack)
          dataGraph.SetLineWidth(2)
          ratioGraph = r.TGraphErrors()

          # Set up legend
          theLegend = initializeLegend(separateHiggsBackgrounds, len(signals))
          
          y_title = None
          XsubRange = None

          # Loop over the samples, adding them to the THStack 
          for sample in samplesToStack: 
              infile = r.TFile.Open(inDir+sample+'_'+selection+'.root')
              theHisto = infile.Get(path+histo+selection)
              print(sample)
              print(path+histo+selection) 
              r.gROOT.cd() 
              
              if rebin: 
                  theHisto.Rebin(histoDict[str(histo)]['rebin'])                   
                  XsubRange = CheckXrange(theHisto, histoDict[histo]['x-min'], histoDict[histo]['x-max'])
                  if XsubRange:
                      low_edge = theHisto.GetBinLowEdge(theHisto.GetXaxis().FindBin(histoDict[histo]['x-min']))
                      high_edge = theHisto.GetBinLowEdge(theHisto.GetXaxis().FindBin(histoDict[histo]['x-max']))
		      print('ZIHANG========')
		      print(low_edge, high_edge)
              
              if y_title == None:     
                  y_title = GetYtitle(theHisto, histoDict[str(histo)]['rebin'], histoDict[histo]['units'])                    
              
              if sample == '15_to_18_data' and not mcOnly:                    
                  dataHist = theHisto.Clone()  # Get the data, not sure why cloning
                  
                  # Blind the m_yy, m_jj and m_yy_jj
                  #dataHist = setBlindedValuestoZero(dataHist, histo, True) 
                  dataHist = setBlindedValuestoZero(dataHist, histo, UNBLIND) 

                  # Transfer the histo information to a TGraph for upper pad plotting.
                  i = 0 # counter for datapoints on graph
                  for xbin in range(0, dataHist.GetNbinsX()+1):  
                      if dataHist.GetBinContent(xbin) > 0.0: #Plot markers unless data points are zero-valued 
                        print("bin:"+str(xbin)+ "content:"+str(dataHist.GetBinContent(xbin))) 
                        dataGraph.SetPoint(i, dataHist.GetXaxis().GetBinCenter(xbin), dataHist.GetBinContent(xbin))
                        dataGraph.SetPointError(i, 0.0, dataHist.GetBinError(xbin))
                        i += 1 # next datapoint
                  #dataGraph.Print()

                  ratioHist = dataHist.Clone()
                  theLegend.AddEntry(dataGraph,"Data", "EP")

              elif sample != '15_to_18_data': # Sample is MC
                newHisto = theHisto.Clone()
                if separateHiggsBackgrounds:
                    addStack(newHisto, stackHist, sampleDict[str(sample)]['color'], theLegend, sampleDict[str(sample)]['legend description'])  
                    getSumHist(newHisto, sumHist)
                else:
                  if not('H' in sample) or ('HH' in sample): # single Higgs will be merged seperately below
                    if ('VBF' in sample) or ('HH' in sample): # Merge VBF HH and HH
                      print(sample + 'HH ZIHANG')
                      getSumHist(newHisto, dihiggsHist)
                    elif ("ttyy" in sample): # Merge ttyy had and non-had
                      getSumHist(newHisto, ttyyHist)
                    else:
                      print(sample + 'others ZIHANG')
                      addStack(newHisto, stackHist, sampleDict[str(sample)]['color'], theLegend, sampleDict[str(sample)]['legend description'])  
                      getSumHist(newHisto, sumHist)

	  print('====================')
          addStack(ttyyHist, stackHist,(102, 105, 112), theLegend, '#it{t#bar{t}#gamma#gamma}')
          getSumHist(ttyyHist, sumHist)
          # New loop to combine the single Higgs backgrounds                                                                     
          if not separateHiggsBackgrounds:
              higgsHist = r.TH1F()
              for sample in samplesToStack:
                  if ('H' in sample) and not('HH' in sample): 
                      infile = r.TFile.Open(inDir  + sample + '_' + selection + '.root')
                      theHisto = infile.Get(path + histo+selection)
                      if rebin: theHisto.Rebin(histoDict[str(histo)]['rebin'])
                      newHisto = theHisto.Clone()
                      getSumHist(newHisto, higgsHist)                        

              # Add the combined single Higgs backgrounds back in, unless specified otherwise
              addStack(higgsHist, stackHist, (52, 56, 68), theLegend, 'Single Higgs')   
              getSumHist(higgsHist, sumHist)

          # Add HH last
          addStack(dihiggsHist, stackHist, (242, 56, 90), theLegend, 'HH (SM)')
          getSumHist(dihiggsHist, sumHist)
          

          # Plot the MC Stack (stackHist)
          stackHist.ls()
          stackHist.Draw("HIST")
          if XsubRange : 
              stackHist.GetXaxis().SetLimits(low_edge,high_edge)
          stackHist.Draw("HIST")

          if mcOnly: 
              stackHist.GetXaxis().SetTitle(histoDict[str(histo)]['x-axis title'])
              stackHist.GetYaxis().SetTitleOffset(2)
          y_title = GetYtitle(theHisto, histoDict[str(histo)]['rebin'], histoDict[histo]['units'])
          stackHist.GetYaxis().SetTitle(y_title)
          stackHist.GetXaxis().SetNdivisions(306)
          stackHist.SetMaximum(1.5*stackHist.GetMaximum())

          if not include_ratio:
            stackHist.GetXaxis().SetTitle(histoDict[str(histo)]['x-axis title'])
            #stackHist.GetXaxis().SetTitleSize(100)
            stackHist.GetXaxis().SetTitleOffset(1)
            stackHist.GetXaxis().SetLabelFont(43)
            stackHist.GetXaxis().SetLabelSize(20)
            stackHist.GetYaxis().SetLabelFont(43)
            stackHist.GetYaxis().SetLabelSize(20) 
          if include_ratio:  
            stackHist.GetXaxis().SetTitleOffset(99)
            stackHist.GetXaxis().SetLabelSize(0)

          if not mcOnly: 
                 #stackHist.GetXaxis().SetLabelOffset(999)
                 #stackHist.GetXaxis().SetLabelSize(0)
                 if ('m_yyjj' in histo) or ('m_jj' in histo):
                    stackHist.SetMaximum(1.5*stackHist.GetMaximum())
                 else:
                    stackHist.SetMaximum(1.5*dataHist.GetMaximum())

          if rebin: 
            sumHist.SetAxisRange(low_edge,high_edge, 'X')


          # Draw the relevant data 
          if not mcOnly: 
              if XsubRange : 
                dataGraph.GetXaxis().SetLimits(low_edge,high_edge)
              #dataGraph.Draw("EP SAME") #JP
              dataGraph.Draw("EP")

          # Inject the non SM-HH/VBF signals

          for sample in signals:                
              if debug: 
                print ("Signal = ",sample)
                if (selection == 'Validation_2bjet'):
                        infile = r.TFile.Open(inDir  + 'Resonance_' + sample + '_' + selection + '.root')
                        theHisto = infile.Get(path + histo+ sample + '_'  + selection)
                else:
                  infile = r.TFile.Open(inDir  + 'Resonance_' + selection + '.root')
                  theHisto = infile.Get(path + histo+ selection)
                #if (sample == signals[0]):
                y_title = GetYtitle(theHisto, histoDict[str(histo)]['rebin'], histoDict[histo]['units'])
                #print('ZIHANG' + inDir + 'Resonance_' + selection + '.root')
                #print('ZIHANG' + path + histo + selection)
                print('ZIHANG' + histo + selection)
                if rebin: theHisto.Rebin(histoDict[str(histo)]['rebin'])
                r.gROOT.cd()
                newHisto = theHisto.Clone()
                if (selection == 'Validation_2bjet'):
                      addSignalStack(newHisto, sigHist, signalDict[str('Resonance_' +sample)]['color'], theLegend, signalDict[str('Resonance_' +sample)]['legend description'])
                else:
                      print('Resonance_' +selection)
                      addSignalStack(newHisto, sigHist, signalDict[str('Resonance_' +selection)]['color'], theLegend, signalDict[str('Resonance_' +selection)]['legend description'])
                sigHist.Draw("HIST nostack SAME")
          
          # Set up ATLAS label
          l = r.TLatex()
          l.SetNDC()
          l.SetTextColor(r.kBlack)
          l1, l2 = 0.55, 0.88
          l.SetTextFont(42)
          l.SetTextSize(0.04)
          if mcOnly or not include_ratio: 
            l1, l2 = 0.5, 0.88

          r.ATLASLabel(l1,l2,"Internal")
          l.DrawLatex(l1, 0.84, "#sqrt{#it{s}} = 13 TeV, 139 fb^{-1}")
          l.DrawLatex(l1, 0.80, selectionDict[str(selection)]['legend upper'])
          l.DrawLatex(l1, 0.76, selectionDict[str(selection)]['legend lower'])


          
          # Add the legend to a separate, pad on the side
          canv.cd()
          padside = r.TPad("padside","padside",0.75,0.0,0.98,1.)
          padside.SetFillStyle(4000)
          padside.SetGrid(0,0)
          padside.Draw()
          padside.cd()
          theLegend.Draw("SAME")

          # Set up the lower pad for the ratio plot
          
          if include_ratio:
            canv.cd()
            padlow = r.TPad("padlow","padlow",0.,0.0,0.85,0.30)
            padlow.SetFillStyle(4000)
            padlow.SetGrid(0,0)
            padlow.SetTopMargin(0.05)
            padlow.SetBottomMargin(0.30)
            padlow.Draw()
            padlow.cd()
            
            # Trying blind
            if XsubRange : ratioGraph.GetXaxis().SetLimits(low_edge,high_edge)
            
            # Set up ratio plot 
            ratioHist.Divide(sumHist) 
            #ratioHist = setBlindedValuestoZero(ratioHist, histo, True) 
            ratioHist = setBlindedValuestoZero(ratioHist, histo, UNBLIND) 

            i = 0 # counter for datapoints on graph
            for xbin in range(0, ratioHist.GetNbinsX()+1):
                    if ratioHist.GetBinContent(xbin) > 0.0: # Don't plot markers for zero-valued data points
                      ratioGraph.SetPoint(i, ratioHist.GetXaxis().GetBinCenter(xbin), ratioHist.GetBinContent(xbin))
                      ratioGraph.SetPointError(i, 0.0, ratioHist.GetBinError(xbin))
                      i += 1 # next datapoint

            ratioHist.GetYaxis().SetTitle("Data/Pred.")
            ratioHist.GetYaxis().CenterTitle()
            ratioHist.GetYaxis().SetNdivisions(306)
            ratioHist.GetYaxis().SetTitleOffset(0.5)
            ratioHist.GetYaxis().SetTitleSize(0.12)
            ratioHist.GetYaxis().SetLabelSize(0.10)
            ratioHist.GetXaxis().SetNdivisions(306)
            ratioHist.GetXaxis().SetTitle(histoDict[str(histo)]['x-axis title'])
            ratioHist.GetXaxis().SetTitleSize(0.10)
            ratioHist.GetXaxis().SetLabelFont(43)
            ratioHist.GetXaxis().SetLabelSize(20)


            #ratioHist.SetMarkerColor(r.kBlack)
            #ratioHist.SetMarkerStyle(r.kFullDotLarge)
            #ratioHist.SetMarkerSize(0)

            ratioGraph.SetMarkerColor(r.kBlack)
            ratioGraph.SetMarkerStyle(r.kFullDotLarge)
            ratioGraph.SetLineColor(r.kBlack)
            ratioGraph.SetLineWidth(2)

            if rebin: 
              ratioHist.SetAxisRange(low_edge,high_edge, 'X')
              ratioGraph.GetXaxis().SetRangeUser(low_edge,high_edge) ##ZIHANG 

            ratioHist.Draw("AXIS")
            ratioGraph.Draw("EP SAME")

            # Add horizontal line at y=1 to the ratio plot
            rl = r.TLine()
            rl.SetLineColor(r.kBlack)
            rl.SetLineWidth(2)
            rl.SetLineStyle(7) # dashed
            #rl.DrawLine(low_edge, 1., high_edge , 1.)
            rl.DrawLine(ratioHist.GetBinLowEdge(1), 1., ratioHist.GetBinLowEdge(ratioHist.GetNbinsX()+1), 1.)
            

          # Name plots 
          extra = ''
          if mcOnly: 
            extra += '_onlyMC'
          if separateHiggsBackgrounds: 
            extra += '_separateSingleHiggsBkgs'

          # Save plots
          if plotDump:
              #canv.Print(outDir + histo + selection + extra + ".C", "C")
              canv.Print(outDir + histo + selection + extra + ".png", "png")
              canv.Print(outDir + histo + selection+ extra + ".pdf", "pdf")
              canv.Print(outDir + histo  + selection+ extra + ".eps", "eps")
              canv.Print(outDir + histo  + selection+ extra + ".C", "C")
              #canv.Print(outDir + histo + selection+ extra + ".root", "root")
          else:
              print('OKKKK' + outDir + histo+ selection + extra + ".pdf")
              canv.Print(outDir + histo+ selection + extra + ".pdf", "pdf")

          # del canv
          # del padhigh
          # del theHisto
          # del stackHist
          # del sigHist
          # del ratioHist
          # del dataHist
          # del sumHist
          # del dataGraph
          # del ratioGraph
                  
if __name__ == "__main__":
  
  # Adding an argument parser, which we might want to use  a
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
  option_dict = dict((k, v) for k, v in vars(options).iteritems() if v is not None)
  print option_dict
  main(**option_dict)







