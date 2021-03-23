'''
  A collection of functions for making publication-ready
  plots from root inputs.

  M. Nelson, 2019 <michael.edward.nelson@cern.ch

'''

import os
import sys
import ROOT as r
from ROOT import gROOT
from array import array
import collections
from math import sqrt

def initializeLegend(separateHiggsBackgrounds,len_signals, x1=0.0, y1=0.55, x2=0.90, y2=0.95):
#def initializeLegend(separateHiggsBackgrounds,len_signals, x1=0.1, y1=0.55, x2=0.90, y2=0.95):

    if separateHiggsBackgrounds or len_signals>6: 
        y1 = 0.35
    if len_signals >10: 
        y1 = 0.15

    aLegend = r.TLegend(x1, y1, x2, y2);
    aLegend.SetLineColor(r.kWhite);
    aLegend.SetFillColor(r.kWhite);
    aLegend.SetNColumns(1);
    aLegend.SetTextSize(0.115);
    #aLegend.SetTextSize(0.12);
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
    if isinstance(color, tuple): # JP, use RGB values
        color1 = gROOT.GetColor(1)
        histo.SetFillColor(color1.GetColor(*color))
    else:
        histo.SetFillColor(color)
    histo.SetLineColor(r.kBlack)
    histo.SetLineWidth(0)
    stack.Add(histo)
    legend.AddEntry(histo, legendText, "f")

def addSignalStack(histo, stack, color, legend, legendText):
    histo.SetLineWidth(2)
    histo.SetLineStyle(r.kDashed)
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

def GetYtitle(theHisto, rebin, units):
    bins = theHisto.GetNbinsX()
    xmin = theHisto.GetXaxis().GetXmin()
    xmax = theHisto.GetXaxis().GetXmax()
    res = (xmax-xmin)/bins*rebin
    #if (res >= 1): res = int(res)
    y_title = "Events / "
    if (res==30):
        y_title += "30 "+units
    else:
        y_title += str(res)+" "+units
    #y_title += str(res)+" "+units

    return y_title

def CheckXrange(theHisto, new_xmin, new_xmax):
    xmin = theHisto.GetXaxis().GetXmin()
    xmax = theHisto.GetXaxis().GetXmax()
    status = False
    if ((new_xmin < xmin) or (new_xmax > xmax)):
        print("WARNING x-min and/or x-max is outside the histogram range. Using TH1F edges instead")
    elif ((new_xmin > xmin) or (new_xmax < xmax)):
        print("Zooming in a sub-range of the original TH1F using x-min and x-max edges")
        status = True

    return status


def MergeBackgrounds(MergeBkgList, Reg, Bkg, yields):

    Merge = []
    Merge_unc = []
    NoHBkg = []
    for r in Reg:
        events = 0
        unc = 0
        for b in Bkg:
            if (b in MergeBkgList):
                events += yields[b][r][0]
                unc +=  yields[b][r][1]**2

        Merge.append(events)
        Merge_unc.append(sqrt(unc))

    for b in Bkg:
        if (b not in MergeBkgList): NoHBkg.append(b)

    return (Merge, Merge_unc, NoHBkg)


def setBlindedValuestoZero(dataHist, histo, UNBLIND=False):
  if not UNBLIND and 'm_yyjj_' in histo: 
      for xbin in range(0, dataHist.GetNbinsX()+1):
          if dataHist.GetXaxis().GetBinCenter(xbin) > 0.0: 
              dataHist.SetBinContent(xbin,0.0) 
              dataHist.SetBinError(xbin,0.0) 
  if not UNBLIND and 'm_yy_' in histo: 
      for xbin in range(0, dataHist.GetNbinsX()+1):
          if dataHist.GetXaxis().GetBinCenter(xbin) > 120.0 and dataHist.GetXaxis().GetBinCenter(xbin) < 130.0: 
              dataHist.SetBinContent(xbin,0.0) 
              dataHist.SetBinError(xbin,0.0) 
  if not UNBLIND and 'm_jj_' in histo: 
      for xbin in range(0, dataHist.GetNbinsX()+1):
          if dataHist.GetXaxis().GetBinCenter(xbin) > 70.0 and dataHist.GetXaxis().GetBinCenter(xbin) < 140.0: 
              dataHist.SetBinContent(xbin,0.0) 
              dataHist.SetBinError(xbin,0.0) 
  return dataHist
