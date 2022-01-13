import ROOT
from ROOT import *
ROOT.gROOT.LoadMacro("aux/AtlasStyle.C")
ROOT.SetAtlasStyle()
#ROOT.gROOT.LoadMacro("aux/AtlasLabels.C")
gStyle.SetPalette(kRainBow)

colors = [1, 2, 801, 4, 6, 8, 28]
sigs = ['minus_lambda06', 'lambda00', 'plus_lambda01', 'plus_lambda02', 'plus_lambda04', 'plus_lambda06', 'plus_lambda10']
sigs = ['0', '1', '2', '10']
lambdas = [0, 1, 2, 10]

hists = []

for sig in sigs:
	file = ROOT.TFile('/afs/cern.ch/user/a/alwang/work/eos/alwang/2021_02_07_h026_new_lumi/hh_bbyy_vbf_l%scvv1cv1.root' %sig)
	tree = file.Get('output')
	hists.append(ROOT.TH1F(sig, sig, 25, 250, 750))
	tree.Draw('mass_yybb_bcal_mod / 1000.>> %s' %sig, '(isPassed && N_lep == 0 && N_jet_cen < 6 && N_bjet_fixed77 == 2) * weight', 'goff')
	hists[-1].SetDirectory(0)

print hists
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
	hists[i].Draw("PLChistsame")
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
hists[0].GetYaxis().SetTitle('Fraction of events / 20 GeV')
hists[0].GetYaxis().SetRangeUser(0.001, 0.25)

tl.DrawLatex(0.42,0.85,"#bf{#it{ATLAS}} Simulation")
tl.DrawLatex(0.42,0.80,"#sqrt{s} = 13 TeV" )
tl.DrawLatex(0.42,0.75,"HH#rightarrowb#bar{b}#gamma#gamma VBF")

insertline = ROOT.TLine(350, hists[0].GetMinimum(), 350, hists[0].GetMaximum())
insertline.SetLineStyle(2)
insertline.SetLineColor(kBlack)
insertline.SetLineWidth(2)
insertline.Draw("same")

leg.Draw()
c1.SaveAs('yybb_v10_VBF.pdf')
c1.SaveAs('yybb_v10_VBF.eps')
c1.SaveAs('yybb_v10_VBF.C')
c1.SaveAs('yybb_v10_VBF.png')
#raw_input('enter')
