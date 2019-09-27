'''
  A collection of functions for making publication-ready
  plots from root inputs.

  M. Nelson, 2019 <michael.edward.nelson@cern.ch
'''

import os
import sys
import ROOT as r
from array import array
import collections
from math import sqrt

def initializeLegend(x1=0.65, y1=0.70, x2=0.75, y2=0.73):
    aLegend = r.TLegend(x1, y1, x2, y2);
    aLegend.SetLineColor(r.kWhite);
    aLegend.SetFillColor(r.kWhite);
    aLegend.SetTextSize(0.030);
    aLegend.SetNColumns(2);
    aLegend.SetBorderSize(0);
    aLegend.SetTextFont(42) # Remove bold text
    
    return aLegend
       
def getScaledHistogram(name, theHistos, scale=1):
    histo = theHistos.Get(name)
    histo.Scale(1/scale)
  
    return histo

def addStack(histo, stack, color, legend, legendText):
    histo.SetFillColor(color)
    histo.SetMarkerColor(color)
    histo.SetLineColor(r.kBlack)
    
    stack.Add(histo)
    legend.AddEntry(histo, legendText, "f")

def shape(histo, color, legend, legendText):
    histo.SetFillColor(color)
    histo.SetMarkerColor(color)
    histo.SetLineColor(r.kBlack)
    legend.AddEntry(histo, legendText, "f")

def shape_alt(histo, color):
    histo.SetFillColor(color)
    histo.SetMarkerColor(color)
    histo.SetLineColor(r.kBlack)

def addRatio(ratioHist, numeratorHist, denominatorHist, xAxisTitle):
    ratioHist = numeratorHist.clone()
    ratioHist.GetXaxis().SetLabelFont(43)
    ratioHist.GetXaxis().SetLabelSize(24) 
    ratioHist.GetXaxis().SetTitleOffset(0.98)
    ratioHist.GetXaxis().SetTitleSize(0.12)
    ratioHist.GetYaxis().SetLabelFont(43)
    ratioHist.GetYaxis().SetLabelSize(17)
    ratioHist.GetYaxis().SetTitleOffset(0.6)
    ratioHist.GetYaxis().SetTitleSize(0.13)
    ratioHist.GetXaxis().SetTitle(xAxisTitle)
    ratioHist.GetYaxis().SetTitle("Data/MC")
    ratioHist.SetMarkerStyle(20)
    ratioHist.Sumw2()
    ratioHist.Divide(denominatorHist)
    
def getSumHist(histo, sumHist, color):
    nBins = histo.GetNbinsX()
    uBin = histo.GetXaxis().GetXmax()
    dBin = histo.GetYaxis().GetXmin()

    sumHist.SetBins(nBins, dBin, uBin)
    sumHist.Add(histo)

    return sumHist


def rebin_hist(histo, bins_array):
    newname = histo.GetName()+'_rebinned'
    newhist = histo.Rebin(len(bins_array)-1, newname, bins_array)
    newhist.SetDirectory(0)
    newhist.GetYaxis().SetRangeUser(0.1,100000)

    return newhist


def rebin_THStack(stack, bins_array):
    tempStack = THStack('Background stack rebinned','')
    histList = stack.GetHists()
    
    for hist in histList:
        if type(bins_array) == int:
            tempHist = hist.Rebin(bins_array)
        else:
            tempHist = rebin_plot(hist, bins_array)
        tempHist.SetDirectory(0)
        tempStack.Add(tempHist)
    
    return tempStack
