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
    aLegend.SetNColumns(1);
    aLegend.SetTextSize(0.12);
    aLegend.SetBorderSize(0);
    aLegend.SetTextFont(42) # Remove bold text
    
    return aLegend
       
def getScaledHistogram(name, theHistos, scale=1):
    histo = theHistos.Get(name)
    histo.Scale(1/scale)
  
    return histo

def shape(histo, color, legend, legendText):
    histo.SetFillColor(color)
    histo.SetMarkerColor(color)
    histo.SetLineColor(r.kBlack)
    legend.AddEntry(histo, legendText, "f")

def shape_alt(histo, color):
    histo.SetFillColor(color)
    histo.SetMarkerColor(color)
    histo.SetLineColor(r.kBlack)


def addStack(histo, stack, color, legend, legendText):
    histo.SetFillColor(color)
    histo.SetLineColor(r.kBlack)
    stack.Add(histo)
    legend.AddEntry(histo, legendText, "f")

def addSignalStack(histo, stack, color, legend, legendText):
    histo.SetLineWidth(5)
    histo.SetLineColor(color)
    stack.Add(histo)
    legend.AddEntry(histo, legendText, "l")

def addRatio(ratioHist, numeratorHist, denominatorHist):
    ratioHist = numeratorHist.Clone()
    ratioHist.Divide(denominatorHist)
    #ratioHist.Sumw2()
    
def getSumHist(histo, sumHist):
    nBins = histo.GetNbinsX()
    uBin = histo.GetXaxis().GetXmax()
    dBin = histo.GetXaxis().GetXmin()
    sumHist.SetBins(nBins, dBin, uBin)
    sumHist.Add(histo)


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
