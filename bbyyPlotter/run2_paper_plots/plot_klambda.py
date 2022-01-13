import ROOT
from ROOT import *
ROOT.gROOT.LoadMacro("aux/AtlasStyle.C")
ROOT.SetAtlasStyle()
#ROOT.gROOT.LoadMacro("aux/AtlasLabels.C")
gStyle.SetPalette(kRainBow)

colors = [1, 2, 801, 4, 6, 8, 28]
#sigs = ['minus_lambda06', 'lambda00', 'plus_lambda01', 'plus_lambda02', 'plus_lambda04', 'plus_lambda06', 'plus_lambda10']
sigs = ['minus_lambda06', 'lambda00', 'plus_lambda01', 'plus_lambda02', 'plus_lambda10']

#lambdas = [-6, 0, 1, 2, 4, 6, 10]
lambdas = [-6, 0, 1, 2, 10]

hists = []

for sig in sigs:
	if sig == 'plus_lambda01':
		file = ROOT.TFile('/afs/cern.ch/user/a/alwang/work/eos/alwang/2021_02_07_h026_new_lumi/PowhegPy8/HHbbyy_cHHH01d0.root')
		tree = file.Get('output')
		hists.append(ROOT.TH1F(sig, sig, 25, 250, 750))
		tree.Draw('mass_yybb_bcal_mod / 1000.>> %s' %sig, '(isPassed && N_lep == 0 && N_jet_cen < 6 && N_bjet_fixed77 == 2) * weight', 'goff')
		hists[-1].SetDirectory(0)
	else:
		point = int(sig.split('lambda')[1])
		if 'minus' in sig: point = point * -1
                file = ROOT.TFile('/afs/cern.ch/user/a/alwang/work/eos/alwang/2021_02_07_h026_new_lumi/PowhegPy8/klambda_weighted_HHbbyy.root')
                tree = file.Get('output')
                hists.append(ROOT.TH1F(sig, sig, 25, 250, 750))
                tree.Draw('mass_yybb_bcal_mod / 1000.>> %s' %sig, '(isPassed && N_lep == 0 && N_jet_cen < 6 && N_bjet_fixed77 == 2) * weight / (8.181e-5) * crossSectionBR_%s%dp0 * kappa_lambda_weight_10GeV_%s%dp0' %('n' if point < 0 else '', abs(point), 'n' if point < 0 else '', abs(point)), 'goff')
                hists[-1].SetDirectory(0)		

print 'drawing histograms'

c1 = TCanvas('', '', 1200, 900)
c1.cd()
gStyle.SetOptStat(0)
#ROOT.ATLASLabel(0.69,0.876,"Internal")
tl = ROOT.TLatex()
tl.SetNDC()
tl.SetTextSize(0.05)
#tl.DrawLatex(0.65,0.86,"#bf{#it{ATLAS}} Internal")

#c2 = TCanvas('', '', 1200, 900)
#c2.cd()
leg = TLegend(0.62, 0.38, 0.92, 0.73)
leg.SetTextSize(0.05)
leg.SetBorderSize(0)
#hists[0].Draw("histSAME")

for i in range(len(sigs)):
	hists[i].Scale(1 / hists[i].Integral())
	#hists[i].Draw("Histsame")
	if i == 0: 
		hists[i].Draw("histsame")
		hists[i].SetLineColor(kGreen+3)
	else: hists[i].Draw("PLChistsame")
	#hists[i].SetLineColor(colors[i])
	hists[i].SetLineWidth(3)
	leg.AddEntry(hists[i], '#kappa_{#lambda} = %s' %lambdas[i], "l")

c1.SetLeftMargin(0.15)
c1.SetBottomMargin(0.20)

hists[0].SetTitle('')

hists[0].GetXaxis().SetTitleSize(0.05)
hists[0].GetXaxis().SetTitleOffset(0)

hists[0].GetYaxis().SetTitleSize(0.05)

hists[0].GetXaxis().SetTitle('m*#kern[-0.25]{_{b#bar{b}#gamma#gamma}} [GeV]')
#hists[0].GetXaxis().SetTitle('{m*}_{b#bar{b}#gamma#gamma} [GeV]')
#hists[0].GetXaxis().SetTitle('#kern[3.0]{*}m_{b#bar{b}#gamma#gamma} [GeV]')
hists[0].GetYaxis().SetTitle('Fraction of events / 20 GeV')
hists[0].GetYaxis().SetRangeUser(0.001, 0.25)

tl.DrawLatex(0.42,0.85,"#bf{#it{ATLAS}} Simulation")
tl.DrawLatex(0.42,0.80,"#sqrt{s} = 13 TeV" )
tl.DrawLatex(0.42,0.75,"HH#rightarrowb#bar{b}#gamma#gamma ggF")

insertline = ROOT.TLine(350, hists[0].GetMinimum(), 350, hists[0].GetMaximum())
insertline.SetLineStyle(2)
insertline.SetLineColor(kBlack)
insertline.SetLineWidth(2)
insertline.Draw("same")

leg.Draw()
c1.SaveAs('yybb_v10.pdf')
c1.SaveAs('yybb_v10.eps')
c1.SaveAs('yybb_v10.C')
c1.SaveAs('yybb_v10.png')
#raw_input('enter')
