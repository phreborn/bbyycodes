''' 
  A python directory summarising the plotting properties
  of each histogram produced for the final plots

  M. Nelson, 2019 <michael.edward.nelson@cern.ch>
'''

import ROOT as r 

def PlottingDict():
    dict = {
        'sumHisto_m_yy_': { # Name of histogram as defined in input root file
            'x-axis title': '#it{m}_{#gamma#gamma} [GeV]',
            'y-axis title': 'Events / GeV',
            'x-min' : 105,
            'x-max' : 160,
            'nBinsX' : 10 # Might want to perform a rebinning
        },
        'sumHisto_m_jj_': { 
            'x-axis title': '#it{m_{jj}} [GeV]',
            'y-axis title': 'Events / 5 GeV',
            'x-min' : 105,
            'x-max' : 160,
            'nBinsX' : 10
        },
        'sumHisto_pT_yy_': {
            'x-axis title': '#it{p_{T}}_{#gamma#gamma} [GeV]',
            'y-axis title': 'Events / 5 GeV',
            'x-min' : 500,
            'x-max' : 500500,
            'nBinsX' : 100
        },
        'sumHisto_pT_jj_': {
            'x-axis title': '#it{p_{T}}_{jj} [GeV]',
            'y-axis title': 'Events / 5 GeV',
            'x-min' : 500,
            'x-max' : 500500,
            'nBinsX' : 100
        },
        'sumHisto_m_yyjj_tilde_': { 
            'x-axis title': '#it{m}_{#gamma#gamma#it{jj}} [GeV]',
            'y-axis title': 'Events / 25 GeV',
            'x-min' : 200,
            'x-max' : 500,
            'nBinsX' : 15
        },
        'sumHisto_pT_yy_div_m_yyjj_tilde_': {
            'x-axis title': '#it{p_{T}}_{#gamma#gamma} / Mtilde',
            'y-axis title': 'Events / 5 GeV',
            'x-min' : 0,
            'x-max' : 1000,
            'nBinsX' : 100
        },
        'sumHisto_pT_jj_div_m_yyjj_tilde_': {
            'x-axis title': '#it{p_{T}}_{jj} / Mtilde',
            'y-axis title': 'Events / 5 GeV',
            'x-min' : 0,
            'x-max' : 1000,
            'nBinsX' : 100
        },
        'sumHisto_pT_yy_div_m_yy_': {
            'x-axis title': '#it{p_{T}}_{#gamma#gamma} / #it{m}_{#gamma#gamma}',
            'y-axis title': 'Events',
            'x-min' : 0,
            'x-max' : 5000,
            'nBinsX' : 100
        },
        'sumHisto_pT_jj_div_m_jj_': {
            'x-axis title': '#it{p_{T}}_{jj} / #it{m}_{jj}',
            'y-axis title': 'Events',
            'x-min' : 0,
            'x-max' : 5000,
            'nBinsX' : 100
        },

        'sumHisto_deltaR_yy_': { 
            'x-axis title': '#Delta#it{R}(#gamma,#gamma)',
            'y-axis title': 'Events / 0.2',
            'x-min' : 0.0,
            'x-max' : 3.0,
            'nBinsX' : 10
        },
        'sumHisto_deltaR_jj_': { 
            'x-axis title': '#Delta#it{R}(j,j)',
            'y-axis title': 'Events / 0.2',
            'x-min' : 0.0,
            'x-max' : 3.0,
            'nBinsX' : 10
        },
        'sumHisto_deltaR_yyjj_': { 
            'x-axis title': '#Delta#it{R}(#gamma,#gamma,j,j)',
            'y-axis title': 'Events / 0.2',
            'x-min' : 0.0,
            'x-max' : 3.0,
            'nBinsX' : 10
        },
        'sumHisto_N_j_': { 
            'x-axis title': '#it{N}_{jets}',
            'y-axis title': 'Events',
            'x-min' : 0,
            'x-max' : 15,
            'nBinsX' : 15
        },
        'sumHisto_N_j_central_': { 
            'x-axis title': '#it{N}_{central jets}',
            'y-axis title': 'Events',
            'x-min' : 0,
            'x-max' : 15,
            'nBinsX' : 15
        },
        'sumHisto_btag_score_': { 
            'x-axis title': 'Sum of #it{b}-tag scores of 2 jets',
            'y-axis title': 'Events',
            'x-min' : 0,
            'x-max' : 20,
            'nBinsX' : 40 
        },
        'sumHisto_m_yyjj_tilde_HM_': { 
            'x-axis title': '#it{m}_{#gamma#gamma#it{jj}} (High-mass) [GeV]',
            'y-axis title': 'Events / 25 GeV',
            'x-min' : 200,
            'x-max' : 500,
            'nBinsX' : 30
        },
        'sumHisto_MET_': { 
            'x-axis title': '#it{E}_{T}^{miss} [GeV]',
            'y-axis title': 'Events / 25 GeV',
            'x-min' : 0,
            'x-max' : 500,
            'nBinsX' : 20
        },
    }

    return dict

def SampleDict():
    dict = {
        'tty_nohad': { # Name of sample
            'color': 3,
            'legend description': '#it{t#bar{t}#gamma}',
        },
        'ttyy_nohad': {
            'color': 2,
            'legend description': 'Non-had #it{t#bar{t}#gamma#gamma}',
        },
        'ttyy_had': { 
            'color': 1,
            'legend description': 'Hadronic #it{t#bar{t}#gamma#gamma}',
        },
        'yy': { 
            'color': 5,
            'legend description': 'SM #it{#gamma#gamma}',
        },
        'yybb': { 
            'color': 6,
            'legend description': 'SM #it{#gamma#gammab#bar{b}}',
        },
        'HH': { 
            'color': 7,
            'legend description': '#it{HH}',
        },
        'ggH': { 
            'color': 28,
            'legend description': '#it{ggH}',
        },
        'VBF': { 
            'color': 30,
            'legend description': 'VBF #it{H}',
        },
        'WpH': { 
            'color': 10,
            'legend description': '#it{W^{+}H}',
        },
        'WmH': { 
            'color': 12,
            'legend description': '#it{W^{-}H}',
        },
        'ZH': { 
            'color': 8,
            'legend description': '#it{ZH}',
        },
        'ggZH': { 
            'color': 9,
            'legend description': '#it{ggZH}',
        },
        'ttH': { 
            'color': 40,
            'legend description': '#it{ttH}',
        },
        'bbH': { 
            'color': 41 ,
            'legend description': '#it{bbH}',
        },
        'tWH': { 
            'color': 42,
            'legend description': '#it{tWH}',
        },
        'tHjb': { 
            'color': 43,
            'legend description': '#it{tHb}+#it{j}',
        },
    }

    return dict

def SelectionDict():
    dict = {
        'Continuum': { 
            'legend upper': 'Continuum bkg. selection',
            'legend lower': '',
        },
        'LM_A': { 
            'legend upper': '#it{M_{X}} < 350 GeV',
            'legend lower': '#it{b}-tag loose',
        },
        'LM_B': { 
            'legend upper': '#it{M_{X}} < 350 GeV',
            'legend lower': '#it{b}-tag tight',
        },
        'HM_A': { 
            'legend upper': '#it{M_{X}} #geq 350 GeV',
            'legend lower': '#it{b}-tag loose',
        },
        'HM_B': { 
            'legend upper': '#it{M_{X}} #geq 350 GeV',
            'legend lower': '#it{b}-tag tight',
        },
    }

    return dict
