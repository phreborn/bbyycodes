__doc__ = "To plot weighted gamma gamma spectrum"

import numpy as np

import math
from array import array
import yaml

import argparse
parser = argparse.ArgumentParser()
parser.add_argument('--weighted', type = int, action = 'store', help = 'weight categories by log(1+s/b)')
parser.add_argument('--category', action = 'store', help = 'plot specific category')
parser.add_argument('--subpanel', type = int, action = 'store', default = 1, help = 'add data - bkg subpanel')
args = parser.parse_args()

if args.category is not None and args.weighted == 1: 
  print "Cannot create weighted plot with only 1 category"
  exit()

import ROOT

#try:
#  import AtlasStyle
#except ImportError:
ROOT.gROOT.LoadMacro("AtlasStyle.C")
ROOT.SetAtlasStyle()

ROOT.gROOT.LoadMacro("AtlasLabels.C")

from ROOT import RooFit
Import = getattr(ROOT.RooWorkspace, 'import')

#ROOT.gSystem.Load("/afs/cern.ch/user/x/xju/public/diphoton_classes/HggTwoSidedCBPdf_cxx.so")

from scipy import stats
from scipy.optimize import brenth

ALPHA = (1 - 0.6826894921370859) / 2.

color1 = ROOT.gROOT.GetColor(2);
color1.SetRGB(242/255., 56/255., 90/255.);
color2 = ROOT.gROOT.GetColor(3);
color2.SetRGB(52/255., 56/255., 68/255.);
color3 = ROOT.gROOT.GetColor(4);
#color3.SetRGB(54/255., 177/255., 191/255.);
color3.SetRGB(36/255., 118/255., 127/255.); #default too light
color4 = ROOT.gROOT.GetColor(7);
color4.SetRGB(74/255., 217/255., 217/255.);
color5 = ROOT.gROOT.GetColor(6);
color5.SetRGB(233/255., 241/255., 223/255.);
color6 = ROOT.gROOT.GetColor(5);
color6.SetRGB(253/255., 197/255., 54/255.);


def scale_range(start, start1, start2, end1, end2):
    m = (end2 - end1) / float(start2 - start1)
    return end1 + m * (start - start1)


def compute_poisson_error(n):
    import ROOT
    a = ROOT.Double()
    b = ROOT.Double()
    if abs(n - np.round(n)) < 1E-5:
        ROOT.RooHistError.instance().getPoissonInterval(int(np.round(n)), a, b)
        return n - float(a), float(b) - n
    else:
        yfloor = np.floor(n).astype(int)
        yceil = yfloor + 1

        ROOT.RooHistError.instance().getPoissonInterval(int(yfloor), a, b)
        floor_error = n - a, b - n
        ROOT.RooHistError.instance().getPoissonInterval(int(yceil), a, b)
        ceil_error = n - a, b - n

        lo = scale_range(n, yfloor, yceil, floor_error[0], ceil_error[0])
        hi = scale_range(n, yfloor, yceil, floor_error[1], ceil_error[1])

        return lo, hi


def compute_poisson_error2(n):
    def compute_pvalue2(nobs, ntrue, left):
        if left:
            # the left case (<=) is the cdf
            return poisson_cdf(ntrue, nobs)
        else:
            return 1 - poisson_cdf(ntrue, nobs - 1)  # is this -1 correct ??

    nup = brenth(lambda x: compute_pvalue2(n, x, True) - ALPHA, n, n * 3)
    ndown = brenth(lambda x: compute_pvalue2(n, x, False) - ALPHA, 1E-5, n)

    return n - ndown, nup - n


def compute_scaled_poisson_errorbar(nevents, weights):
    """
    nevents = list of number of evets for each category
    weights = list of weights for each category
    return central value, error down (negative), error up
    """
    nevents = np.asarray(nevents)
    weights = np.asarray(weights)

    nw = float(np.sum(nevents * weights, axis=0))
    nw2 = float(np.sum(nevents * weights ** 2, axis=0))
    lambda_tilde = nw ** 2 / nw2
    scale = nw2 / nw

    e = compute_poisson_error(lambda_tilde)
    return nw, -e[0] * scale, e[1] * scale


def poisson_cdf(l, n):
    """
    continuous implementation of the cdf of the poisson distribution
    l: expected value
    n: observed value
    """
    return 1 - stats.gamma(n + 1).cdf(l)


def compute_scaled_poisson_errorbar2(nevents, weights):
    """
    nevents = list of number of evets for each category
    weights = list of weights for each category
    return central value, error down (negative), error up
    """
    nevents = np.asarray(nevents)
    weights = np.asarray(weights)

    nw = float(np.sum(nevents * weights, axis=0))
    nw2 = float(np.sum(nevents * weights ** 2, axis=0))
    lambda_tilde = nw ** 2 / nw2
    scale = nw2 / nw

    e = compute_poisson_error2(lambda_tilde)
    return nw, -e[0] * scale, e[1] * scale



def test():
  "For testing: return dictionary to be used directly with getWeightedWorkspace"
  w = ROOT.RooWorkspace('w')
  eG = w.factory('ExtendPdf::eG(Gaussian::G(x[-5,5], 0, 1), nG[100])')
  eU = w.factory('ExtendPdf::eU(Uniform::U(y[-5,5]), 1000)')
  pdf = w.factory('SIMUL::pdf( cat[a,b], a=eG, b=eU )')

  w.defineSet('aset', 'cat,x,y')
  dataG = eG.generate(ROOT.RooArgSet(w.obj('x')))
  dataU = eU.generate(ROOT.RooArgSet(w.obj('y')))
  data = ROOT.RooDataSet("combData","combined data", w.set('aset'),
    RooFit.Index(w.obj('cat')),RooFit.Import("a", dataG),RooFit.Import("b",dataU))

  catInfo = dict(
    a = dict( weight = 0.2, pdfName = 'eG', observable = 'x' ),
    b = dict( weight = 0.1, pdfName = 'eU', observable = 'y' )
  )
  return dict(w=w, data=data, catVariable='cat', catInfo=catInfo, newObs='mgg', nBins=55) #20

def getInfoCouplings(fName='WS-yybb-nonresonant_BDT_h026_v6_kl1p0.root', snapshot='ucmles_0', noWeights = False, nBins=55, subset=args.category):
  """return info for getWeightedWorkspace. <subset> can be ggH, VBF, VH or ttH"""
  f = ROOT.TFile(fName)
  w = f.combWS
  if snapshot: w.loadSnapshot(snapshot)

  '''
  weight_dict = yaml.load(open('weights.yaml', 'r'), Loader=yaml.FullLoader)
  
  catInfo = {}
  for i in range(0,88):
    catName = 'hybrid%s' %i
    catInfo[catName] = {}
    catInfo[catName]['weight'] = weight_dict[catName]
    print catName, 'weight:', weight_dict[catName]
    catInfo[catName]['pdfName'] = '_model_%s' %catName
    catInfo[catName]['observable'] = 'atlas_invMass_%s' %catName
  '''
  
  catInfo = {
    "SM_1": {
      "weight": 1,
      "pdfName": "_model_SM_1",
      "observable": "atlas_invMass_SM_1"
    },
    "SM_2": {
      "weight": 1,
      "pdfName": "_model_SM_2",
      "observable": "atlas_invMass_SM_2"
    },
    "BSM_1": {
      "weight": 1,
      "pdfName": "_model_BSM_1",
      "observable": "atlas_invMass_BSM_1"
    },
    "BSM_2": {
      "weight": 1,
      "pdfName": "_model_BSM_2",
      "observable": "atlas_invMass_BSM_2"
    },
   }
  
  if subset:
    catInfo = dict( (key, value) for key, value in catInfo.iteritems() if subset == key)

  if noWeights: # Set all weights to 1
    for d in catInfo.values(): d['weight'] = 1

  return dict(w=w, catInfo=catInfo, data = w.obj('combData'), catVariable = 'channellist', nBins = nBins, newObs = 'mgg')


def getLegend(frame, labels, position=[0.57, 0.63, 0.87, 0.87], plot_options={}, add=True):
  """getLegend(frame, labels, position=[0.24, 0.2, 0.55, 0.45], plot_options={}, add=True) -->
  Create and return a legend. <plot_options> is a dictionary with the plot option
  for each object ('PL' for data, 'L' otherwise if not given)
  """
  legend = ROOT.TLegend(*position)
  legend.SetBorderSize(0)
  legend.SetFillColor(0)

  for i, label in enumerate(labels):
    obj = frame.getObject(i)
    # Set default plot options
    if isinstance(obj, (ROOT.RooAbsData, ROOT.RooHist)):
      plot_options.setdefault(obj, 'PE')
    else:
      plot_options.setdefault(obj, 'L')
    # Add entry
    legend.AddEntry(obj, label, plot_options[obj])

  if add:
    frame.addObject(legend)
  return legend


def getNewWorkspace(w, data, catVariable, catInfo, name='w1', newObs='mgg', nBins=55,
  dataName='dataW', pdfName='pdfW', newWorkspace=None, addData = True):
  """getNewWorkspace(w, data, catVariable, catInfo, newObs='mgg', nBins=55) -->
  return a workspace with dataName and pdfName that represent the weighted sum
  of data and pdfs in the categories (catVariable).
  catInfo is a dictionary (catName, info) like:
    catInfo = dict(
      a = dict( weight = 0.2, pdfName = 'eG', observable = 'x' ),
      b = dict( weight = 0.1, pdfName = 'eU', observable = 'y' )
    )
  """
  # Create new workspace and observable, using the overlapping range of all observables
  w1 = newWorkspace or ROOT.RooWorkspace(name)
  if not w1.allVars().find(newObs):
    obs = w1.factory('{0}[{1}, {2}]'.format(
      newObs,
      max(w.obj(d['observable']).getMin() for d in catInfo.values() ),
      min(w.obj(d['observable']).getMax() for d in catInfo.values() )
    ) )
    obs.setBins(nBins)

  # Change observable name and create combined dataHist
  if addData:
    h = ROOT.TH1F('h', '', nBins, obs.getMin(), obs.getMax())
    hl = ROOT.TH1F('hl', '', nBins, obs.getMin(), obs.getMax())
    hh = ROOT.TH1F('hh', '', nBins, obs.getMin(), obs.getMax())
    hAll = h.Clone('hAll')
    hAlll = hl.Clone('hAlll')
    hAllh = hh.Clone('hAllh')
    hAll.Sumw2()
    hAlll.Sumw2()
    hAllh.Sumw2()

    for catName, d in catInfo.iteritems():
      print catVariable, catName
      print '{0} == {0}::{1}'.format(catVariable, catName)
      dcat = data.reduce('{0} == {0}::{1}'.format(catVariable, catName) )
      alist = ROOT.RooArgList( data.get().selectByName(d['observable']) )
      _ = dcat.fillHistogram(h, alist)
      _ = hAll.Add(h, d['weight'])
      h.Reset()
      #hl.Reset()
      #hh.Reset()

    for j in range(1,h.GetNbinsX()+1) :
      nevents=[]
      weights=[]
      for catName, d in catInfo.iteritems():
        dcat = data.reduce('{0} == {0}::{1}'.format(catVariable, catName) )
        alist = ROOT.RooArgList( data.get().selectByName(d['observable']) )
        _ = dcat.fillHistogram(h, alist)
        nevents.append(h.GetBinContent(j))
        weights.append(d['weight'])
        h.Reset()
      c,a,b=compute_scaled_poisson_errorbar(nevents,weights)
      hAlll.SetBinContent(j,a*a)
      hAllh.SetBinContent(j,b*b)
      hAll.SetBinError(j,0.001)

    dataW = ROOT.RooDataHist(dataName, dataName, ROOT.RooArgList(obs), hAll)
    Import(w1, dataW)

    dataWl = ROOT.RooDataHist(dataName+'l', dataName+'l', ROOT.RooArgList(obs), hAlll)
    Import(w1, dataWl)

    dataWh = ROOT.RooDataHist(dataName+'h', dataName+'h', ROOT.RooArgList(obs), hAllh)
    Import(w1, dataWh)

  # Add expected events to catInfo and
  # import pdf of each category, changing the name of the observable
  for catName, d in catInfo.iteritems():
    pdfCat = w.obj(d['pdfName'])
    d['norm'] = pdfCat.expectedEvents( data.get() )
    Import(w1, pdfCat, RooFit.RenameVariable(d['observable'], newObs), RooFit.RecycleConflictNodes() )

  # Create sum of pdfs
  _ = ', '.join('{w} * {pdf}'.format(w=d['weight']*d['norm'], pdf=d['pdfName']) for d in catInfo.values())
  pdfW = w1.factory('SUM::{0}( {1} )'.format(pdfName, _) )
  print 'pdfW:', pdfW
  return w1

def plot(w1, noWeights=False, label='All categories', canvasName='c', canvasTitle='c', nBins = 55, subpanel = 1, ss_name = ''):

  c = ROOT.TCanvas(canvasName, canvasTitle)
  c.Divide(1,2)
  if subpanel == 1:
    p1 = ROOT.TPad("pad1", "The pad 80% of the height",0.01,0.40-0.05,0.99,0.99)
    p2 = ROOT.TPad("pad2", "The pad 20% of the height",0.01,0.01,0.99,0.40*0.95)
  else: 
    p1 = ROOT.TPad("pad1", "The pad 80% of the height",0.01,0.01,0.99,0.99)
    p2 = ROOT.TPad("pad2", "The pad 20% of the height",0.01,0.01,0.99,0.01)
  c.cd()
  p1.Draw()
  p2.Draw()
  if subpanel == 1: p1.SetBottomMargin(0.05)
  else: p1.SetBottomMargin(0.15)
  p1.SetLeftMargin(0.12)
  #c.cd(1)
  p1.cd()
  mgg = w1.obj('mgg')
  binWidth = mgg.getBinWidth(0)
  frame = mgg.frame()
  w1.obj('dataW').plotOn(frame, RooFit.DrawOption("PEZ"), RooFit.MarkerStyle(20), RooFit.MarkerSize(1), RooFit.XErrorSize(0), ROOT.RooFit.DataError(ROOT.RooAbsData.SumW2))

  h = ROOT.TH1F('h', '', nBins, mgg.getMin(), mgg.getMax())
  alist = ROOT.RooArgList( w1.obj('dataW').get().selectByName('mgg') )
  _ = w1.obj('dataW').fillHistogram(h, alist)

  hl = ROOT.TH1F('hl', '', nBins, mgg.getMin(), mgg.getMax())
  alistl = ROOT.RooArgList( w1.obj('dataWl').get().selectByName('mgg') )
  _ = w1.obj('dataWl').fillHistogram(hl, alistl)

  hh = ROOT.TH1F('hh', '', nBins, mgg.getMin(), mgg.getMax())
  alisth = ROOT.RooArgList( w1.obj('dataWh').get().selectByName('mgg') )
  _ = w1.obj('dataWh').fillHistogram(hh, alisth)

  x, y = array( 'd' ), array( 'd' )
  xl, yl = array( 'd' ), array( 'd' )
  xh, yh = array( 'd' ), array( 'd' )
  for j in range(1,h.GetNbinsX()+1) :
    if h.GetBinContent(j)>=0.001:
      a,b=compute_poisson_error(h.GetBinContent(j))
      x.append(mgg.getMin()+(j-0.5)*binWidth)
      xl.append(0)
      xh.append(0)
      y.append(h.GetBinContent(j))
      yl.append(math.sqrt(hl.GetBinContent(j)))
      yh.append(math.sqrt(hh.GetBinContent(j)))

  gr = ROOT.TGraphAsymmErrors(nBins,x,y,xl,xh,yl,yh);
  gr.Print("all")

  #get best fit mu (should be 1) then set to 0 for the cont. bkg only component
  fitted_mu=w1.var('mu').getVal()
  w1.var('mu').setVal(0.0)

  fitted_SS=w1.var(ss_name).getVal()
  w1.var(ss_name).setVal(0)
  if not w1.allPdfs().find('pdfB'):
    pdfB = w1.obj('pdfW')
  else:
    pdfB = w1.obj('pdfB')
  pdfB.plotOn(frame, RooFit.LineStyle(3), RooFit.LineColor(4), RooFit.Normalization(1, ROOT.RooAbsReal.RelativeExpected))
  residHist = frame.residHist()
  pullHist = frame.pullHist()

  x_2, y_2 = array( 'd' ), array( 'd' )
  y_2_max,y_2_min=0,0
  for j in range(1,h.GetNbinsX()+1) :
    if h.GetBinContent(j)>=0.001:
      aa = ROOT.Double()
      bb = ROOT.Double()
      residHist.GetPoint(j-1,aa,bb)
      x_2.append(aa)
      y_2.append(bb)
      if bb>y_2_max: y_2_max=bb
      if bb<y_2_min: y_2_min=bb

  gr_2 = ROOT.TGraphAsymmErrors(nBins,x_2,y_2,xl,xh,yl,yh);
  gr_2.Print("all")

  NBg = pdfB.expectedEvents( w1.obj('dataW').get() )

  '''
  w1.var('mu').setVal(1.0)
  fitted_mu_ttH=w1.var('mu_ttH').getVal()
  w1.var('mu_ttH').setVal(0.0)
  if not w1.allPdfs().find('pdfB2'):
    pdfB2 = w1.obj('pdfW')
  else:
    pdfB2 = w1.obj('pdfB2')
  pdfB2.plotOn(frame, RooFit.LineStyle(7), RooFit.LineColor(ROOT.kGreen+2), RooFit.Normalization(1, ROOT.RooAbsReal.RelativeExpected))

  NBg2 = pdfB2.expectedEvents( w1.obj('dataW').get() )
  '''

  #get the total B now 
  print 'setting mu to ', fitted_mu
  print 'setting', ss_name, 'to', fitted_SS
  w1.var('mu').setVal(fitted_mu) #fitted_mu should be 1
  w1.var(ss_name).setVal(fitted_SS)
  w1.obj('pdfW').plotOn(frame, RooFit.LineStyle(1), RooFit.LineColor(2), RooFit.Normalization(1, ROOT.RooAbsReal.RelativeExpected))
  frame.SetMaximum((frame.GetMaximum() + 1.7 * math.sqrt(frame.GetMaximum()))*1.5)
  frame.SetMinimum(0.001)

  NSigPlusBg = w1.obj('pdfW').expectedEvents( w1.obj('dataW').get() )

  NSg = NSigPlusBg - NBg
  print 'NSg = ', NSigPlusBg, '-', NBg, '=', NSg
  #NSg2 = NBg2 - NBg
  #w1.factory('signalOnlyYield[1.0]')
  #w1.var('signalOnlyYield').setVal(NSg)

  
  nitr = ROOT.TIter(w1.allVars().selectByName("nbkg_*").createIterator())
  nuis = nitr()
  while nuis:
    varName = str(nuis.GetName())
    w1.var(varName).setVal(0.0)
    nuis = nitr()

  #w1.var('mu').setVal(0.0)
  #w1.obj('pdfW').plotOn(frame, RooFit.LineStyle(1), RooFit.LineColor(ROOT.kBlack), RooFit.Normalization( NSg,ROOT.RooAbsReal.NumEvent))


  textscale = 0.80
  if subpanel == 1: textscale = 1

  # Add legend
  legend = getLegend(frame, ['Data', 'Continuum Background', 'Total Background'], [0.13, 0.93 - 0.35 * textscale, 0.63, 0.93]) #0.18, 0.58, 0.63, 0.93
  #legend = getLegend(frame, ['Data', 'Background', 'Signal + Background'], [0.23, 0.75, 0.55, 0.93])

  frame.Draw()

  if subpanel == 1: frame.GetXaxis().SetLabelOffset(800)
  else: frame.GetXaxis().SetLabelOffset(0) #
  frame.GetYaxis().SetLabelSize(0.075 * textscale)
  frame.GetXaxis().SetLabelSize(0.075 * textscale)
  frame.GetYaxis().SetTitleOffset(0.8)
  if subpanel == 1: frame.GetXaxis().SetTitleOffset(0.8)
  else: frame.GetXaxis().SetTitleOffset(0.95)
  frame.GetYaxis().SetTitleSize(0.075 * textscale)
  frame.GetXaxis().SetTitleSize(0.075 * textscale)
#   frame.GetYaxis().SetTitle("#scale[0.7]{#sum} weights / %s" % ('GeV' if binWidth==1 else ' %s' % binWidth))
  if (not noWeights): frame.GetYaxis().SetTitle("Sum of Weights / %s" % ('GeV' if binWidth==1 else ' %s GeV' % binWidth))
  else: frame.GetYaxis().SetTitle("Events / %s" % ('GeV' if binWidth==1 else ' %s GeV' % binWidth))
  frame.GetXaxis().SetTitle("m_{#gamma#gamma} [GeV]")
  frame.GetYaxis().SetNdivisions(508)

  gr.SetLineColor( 1 )
  gr.SetLineWidth( 2 )
  gr.SetMarkerColor( 1 )
  gr.SetMarkerStyle( 20 )
  gr.SetMarkerSize( 1 )
  gr.Draw("PEZsame")

  #p1.Update()

  # Draw Labels
  #ROOT.ATLASLabel(0.69,0.876,"Internal")
  tl = ROOT.TLatex()
  tl.SetNDC()
  tl.SetTextSize(0.068 * textscale)
  #tl.DrawLatex(0.65,0.86,"#bf{#it{ATLAS}} Internal")
  tl.DrawLatex(0.60,0.86,"#bf{#it{ATLAS}} Preliminary")
  tl.DrawLatex(0.60,0.86 - 0.08 * textscale,"#sqrt{s} = 13 TeV, 139 fb^{-1}")
  tl.DrawLatex(0.60,0.86 - 0.08 * 2 * textscale,"HH#rightarrowb#bar{b}#gamma#gamma")
  #tl.DrawLatex(0.65,0.70,"m_{H} = 125.09 GeV")
  tl.DrawLatex(0.60,0.86 - 0.08 * 3 * textscale,label) #0.63, 0.58
  if (not noWeights):
    tl.DrawLatex(0.63,0.50,"ln(1+S/B) weighted sum")
    tl.DrawLatex(0.63,0.42,"S =	Inclusive")

  if subpanel == 1:
    p2.SetFillColor(0)
    p2.SetFillStyle(0)  
    p2.SetTopMargin(0.)
    p2.SetBottomMargin(0.33) #0.25
    p2.SetLeftMargin(0.12)
    #c.cd(2)
    p2.cd()

    frame2 = mgg.frame()
    #w1.obj('pdfW').plotOn(frame2, RooFit.LineStyle(7), RooFit.LineColor(ROOT.kGreen+2), RooFit.Normalization( NSg2,ROOT.RooAbsReal.NumEvent))
    w1.obj('pdfW').plotOn(frame2, RooFit.LineStyle(1), RooFit.LineColor(2), RooFit.Normalization( NSg,ROOT.RooAbsReal.NumEvent))
    pdfB.plotOn(frame2, RooFit.LineStyle(3), RooFit.LineColor(4), RooFit.Normalization(0, ROOT.RooAbsReal.NumEvent))
    #if args.weighted == 1:
    frame2.SetMaximum(5.)
    #else: 
      #frame2.SetMaximum(49.)
    frame2.SetMinimum(-0.5*frame2.GetMaximum())
    frame2.GetYaxis().SetLabelSize(0.13) #0.1
    frame2.GetXaxis().SetLabelSize(0.13) #0.1
    frame2.GetYaxis().SetTitleSize(0.13) #0.12
    frame2.GetYaxis().SetTitleOffset(0.46) #0.48
    frame2.GetXaxis().SetTitleSize(0.13) #0.12
    frame2.GetXaxis().SetTitleOffset(1.08) #0.88
    frame2.GetYaxis().SetTitle("Data #minus Bkg.")
    frame2.GetXaxis().SetTitle("m_{#gamma#gamma} [GeV]")
    frame2.GetYaxis().SetNdivisions(505)
    #frame2.addPlotable(residHist, "P");
    frame2.Draw()
    gr_2.SetLineColor( 1 )
    gr_2.SetLineWidth( 2 )
    gr_2.SetMarkerColor( 1 )
    gr_2.SetMarkerStyle( 20 )
    gr_2.SetMarkerSize( 1 )
    gr_2.Draw("PEZsame")
  
 
  ROOT.gPad.Update()
  return c, frame, legend, gr, tl, residHist, pullHist, gr_2


if __name__ == '__main__':

  info = getInfoCouplings(nBins=22, noWeights=1 - args.weighted, subset=args.category) #<- change this to change nBins 

  #get the plot for the ucmles fit
  w = getNewWorkspace(**info)

  #get the plot for the ucmles fit (cont bkg only component)
  info['w'].obj('mu').setVal(0)
  info['w'].obj('SPURIOUS_SM_1').setVal(0)
  info['w'].obj('SPURIOUS_SM_2').setVal(0)
  info['w'].obj('SPURIOUS_BSM_1').setVal(0)
  info['w'].obj('SPURIOUS_BSM_2').setVal(0)
  getNewWorkspace(newWorkspace=w, addData=False, pdfName='pdfB', **info)
  if args.category:
    if args.category == 'SM_1': label = 'High mass BDT tight'
    elif args.category == 'SM_2': label = 'High mass BDT loose'
    elif args.category == 'BSM_1': label = 'Low mass BDT tight'
    elif args.category == 'BSM_2': label = 'Low mass BDT loose'
    x = plot(w, noWeights=1-args.weighted, label=label, nBins = 22, subpanel = args.subpanel, ss_name = 'SPURIOUS_' + args.category)       #<- and also change this
  else: 
    x = plot(w, noWeights=1-args.weighted, label="All categories", nBins = 22, subpanel = args.subpanel)	#<- and also change this
  c = x[0]

  tag = 'v3'

  if args.category:
    c.SaveAs("plots/unweighted_yybb_%s%s_%s.pdf" %(args.category, '_subpanel' if args.subpanel == 1 else '', tag))
    c.SaveAs("plots/unweighted_yybb_%s%s_%s.eps" %(args.category, '_subpanel' if args.subpanel == 1 else '', tag))
    c.SaveAs("plots/unweighted_yybb_%s%s_%s.C" %(args.category, '_subpanel' if args.subpanel == 1 else '', tag))
    c.SaveAs("plots/unweighted_yybb_%s%s_%s.png" %(args.category, '_subpanel' if args.subpanel == 1 else '', tag))
  elif args.weighted == 1:
    c.SaveAs("plots/weighted_yybb_all%s_%s.pdf" %('_subpanel' if args.subpanel == 1 else '', tag))
    c.SaveAs("plots/weighted_yybb_all%s_%s.eps" %('_subpanel' if args.subpanel == 1 else '', tag))
    c.SaveAs("plots/weighted_yybb_all%s_%s.C" %('_subpanel' if args.subpanel == 1 else '', tag))
    c.SaveAs("plots/weighted_yybb_all%s_%s.png" %('_subpanel' if args.subpanel == 1 else '', tag))
  else:
    c.SaveAs("plots/unweighted_yybb_all%s_%s.pdf" %('_subpanel' if args.subpanel == 1 else '', tag))
    c.SaveAs("plots/unweighted_yybb_all%s_%s.eps" %('_subpanel' if args.subpanel == 1 else '', tag))
    c.SaveAs("plots/unweighted_yybb_all%s_%s.C" %('_subpanel' if args.subpanel == 1 else '', tag))
    c.SaveAs("plots/unweighted_yybb_all%s_%s.png" %('_subpanel' if args.subpanel == 1 else '', tag))
