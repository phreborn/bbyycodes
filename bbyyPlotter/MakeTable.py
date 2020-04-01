import os
import sys
import ROOT as r
from array import array
import collections
from math import sqrt
from PyPlotter import *
from histoDictionary import *
from PlottingList import *
import numpy

separateHiggsBackgrounds = False
inDir = "../AnalysisFramework/run/plots/"
UNBLIND = "False"
n = 4 #Number of decimals

sampleDict = SampleDict()
signalDict = SignalDict()

histosToPlot = [                  'sumHisto_m_yy_']
#                                  'sumHisto_m_yyjj_cnstrnd_',
#                                  'sumHisto_m_yyjj_',
#                                  'sumHisto_m_yyjj_']

regions = ""
for s in selections: regions = regions+"r"
    
if not separateHiggsBackgrounds:
    SingleHiggs =[]
    OtherBkgs = []
    for sample in samplesToStack:
        if ('H' in sample and 'HH' not in sample) or sample == 'VBF':
            SingleHiggs.append(sample)
        else:
            OtherBkgs.append(sample)
    Backgrounds = OtherBkgs
else:
    Backgrounds = samplesToStack
        
for histo in histosToPlot:
    h1 = r.TH1F()
    h2 = r.TH1F()
    h3 = r.TH1F()
    h4 = r.TH1F()
    h5 = r.TH1F()

    Tex = open("YieldTable_"+histo+".tex", "w")
    Tex.write("\n \\begin{table} \n \\begin{center} \n \setlength{\\tabcolsep}{0.0pc} \n \\begin{tabular*}{\\textwidth}{@{\extracolsep{\\fill}}l"+regions+"} \n \\noalign{\smallskip}\hline\\noalign{\smallskip} \n {\\bf "+histo.replace("_"," ")+"} ")
    for s in selections:
        reg = s.replace("_","")
        Tex.write(" & "+reg)
    Tex.write(" \\\ \n \\noalign{\smallskip}\hline\\noalign{\smallskip}")
    # Loop over all backgrounds (except single Higgs unless separateHiggsBackground == True)
    DataYield = []
    BkgYield = numpy.zeros((len(Backgrounds)-1, len(selections)))
    i = 0
    for sample in Backgrounds:
        if sample != '15_to_18_data':
            print "Sample: "+sample
            #Tex.write("\n "+sampleDict[sample]['legend description'].replace("#","\#")+" events ")
            Tex.write("\n "+sample.replace("_","\_"))
        j = 0

        for reg in selections:   
    
            infile = r.TFile.Open(inDir  + sample + '_' + reg + '.root')
            theHisto = infile.Get(histo+reg)
            if sample == '15_to_18_data':
                dataHist = theHisto.Clone()  # Get the data 
                print "Data here"
                
                if UNBLIND == "False" and 'm_yyjj' in histo: # Blind the m_yyjj for the resonant search           
                    for xbin in range(0, dataHist.GetNbinsX()+1):
                        if dataHist.GetXaxis().GetBinCenter(xbin) > 120:
                            print "I AM BLINDING ABOVE m_yyjj > 120"
                            dataHist.SetBinContent(xbin,0)
                            dataHist.SetBinError(xbin,0.0001)
                DataYield.append(round(dataHist.Integral()))
            else:
                BkgYield[i][j] = round(theHisto.Integral())
                theHisto.Rebin(theHisto.GetNbinsX())
                unc = theHisto.GetBinError(0)
                Tex.write(" & "+str(round(theHisto.Integral(),n))+" $\pm$ "+str(round(unc,n)))
                if reg == selections[0]: h1.Add(theHisto)
                if reg == selections[1]: h2.Add(theHisto)
                if len(selections) > 2 and reg == selections[2]: h3.Add(theHisto)
                if len(selections) > 3 and reg == selections[3]: h4.Add(theHisto)
                if len(selections) > 4 and reg == selections[4]: h5.Add(theHisto)

            j = j+1
        if sample != '15_to_18_data':
            Tex.write(" \\\ ")
            i = i+1

    # Calculate Yield for all Single Higgs bkgs together
    if not separateHiggsBackgrounds:
        print "Single Higgs "
        SingleHiggsYield=[]
        newHisto = r.TH1F()
        Tex.write("\n Single Higgs ")
        for reg in selections:
            higgsHist = r.TH1F()
            for sample in SingleHiggs:
                infile = r.TFile.Open(inDir  + sample + '_' + reg + '.root')
                theHisto = infile.Get(histo+reg)
                newHisto = theHisto.Clone()
                getSumHist(newHisto, higgsHist)                
                higgsHist.Rebin(higgsHist.GetNbinsX())
                unc = higgsHist.GetBinError(0)

            
            if reg == selections[0]: h1.Add(higgsHist)
            if reg == selections[1]:
                print "CHECK HERE"
                print h2.Integral()
                h2.Add(higgsHist)
                print h2.Integral()
            if len(selections) > 2 and reg == selections[2]: h3.Add(higgsHist)
            if len(selections) > 3 and reg == selections[3]: h4.Add(higgsHist)
            if len(selections) > 4 and reg == selections[4]: h5.Add(higgsHist)
            Tex.write(" & "+str(round(higgsHist.Integral(),n))+" $\pm$ "+str(round(unc,n)))
            SingleHiggsYield.append(round(higgsHist.Integral(),n))

        print "DONE REGIONS"
        Tex.write(" \\\ ")
    
    Tex.write(" \\hline ")

    #Get Bkg sum
    Tex.write("\n Total Background  ")
#    print "range: (0,"+str(len(selections))+")"
#    for j in range(0,len(selections)):
#        print j
#        TotalYield = 0
#        i=0
#        for sample in Backgrounds:
#            if sample != '15_to_18_data':
#                print i
#                TotalYield = TotalYield + BkgYield[i][j]
#                print "Indiv Background yield = "+str(BkgYield[i][j])        
#                i = i+1
        #print "Total Yield = "+str(TotalYield)
#        TotalYield = TotalYield +SingleHiggsYield[j]
#        print "COMPARE"+str(TotalYield)+" vs "+str(h2.Integral())

        #print "Adding H "+str(TotalYield)

    for reg in selections:
            if reg == selections[0]: 
                Total = h1.Integral()
                unc = h1.GetBinError(0)
            if reg == selections[1]:
                Total = h2.Integral()
                unc = h2.GetBinError(0)
            if len(selections) > 2 and reg == selections[2]:
                Total = h3.Integral()
                unc = h3.GetBinError(0)
            if len(selections) > 3 and reg == selections[3]:
                Total = h4.Integral()
                unc = h4.GetBinError(0)
            if len(selections) > 4 and reg == selections[4]: 
                Total = h5.Integral()
                unc = h5.GetBinError(0)
            Tex.write(" & "+str(round(Total,n))+" $\pm$ "+str(round(unc,n)))

    Tex.write(" \\\ ")

    # Add Data
    Tex.write(" \n Data ")
    for i in range(0,len(DataYield)):
        Tex.write(" & "+str(DataYield[i])+"  ")
    
    Tex.write(" \\\  \hline ")

    # Adding Signals

    for sample in signals:
        print "Signal: "+sample
        #Tex.write("\n "+signalDict[sample]['legend description'].replace("#","\#")+" events ")
        Tex.write("\n "+sample.replace("_","\_"))
        for reg in selections:
            print reg
            infile = r.TFile.Open(inDir  + sample + '_' + reg + '.root')
            theHisto = infile.Get(histo+reg)
            events = theHisto.Integral()
            theHisto.Rebin(theHisto.GetNbinsX())
            print theHisto.GetNbinsX()
            print theHisto.GetBinContent(0)
            print theHisto.GetBinError(0)
            print theHisto.GetBinContent(1)
            print theHisto.GetBinError(1)

            unc = theHisto.GetBinError(0)
            print str(events)+" +/- "+str(unc)
            Tex.write(" & "+str(round(events,n))+" $\pm$ "+str(round(unc,n)))
        Tex.write(" \\\ ")

    # Finish up                                                                                                                        
    Tex.write("\n \\noalign{\smallskip}\hline\\noalign{\smallskip} \n \end{tabular*} \n \end{center}")
#    Tex.write("\n \\caption{Yield Table for "+histo.replace("_","\_")+" in the different regions} \n \label{YieldTable_"+histo.replace("_","\_")+"}")
    Tex.write("\n  \end{table}")
        
    print "Done! File YieldTable_"+histo+".tex"
