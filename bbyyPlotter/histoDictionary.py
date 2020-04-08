''' 
  A python directory summarising the plotting properties
  of each histogram produced for the final plots

  M. Nelson, 2019 <michael.edward.nelson@cern.ch>
'''


import ROOT as r 

def PlottingDict():
    # y-axis title is not being used in plottingScheduler.py
    dict = {
        'sumHisto_m_yy_': { # Name of histogram as defined in input root file
            'x-axis title': '#it{m}_{#gamma#gamma} [GeV]',
            'y-axis title': 'Events / GeV',
            'units' : 'GeV',
            'x-min' : 105,
            'x-max' : 160,
            'rebin' : 1
        },
        'sumHisto_m_jj_': { 
            'x-axis title': '#it{m_{jj}} [GeV]',
            'y-axis title': 'Events / 5 GeV',
            'units' : 'GeV',
            'x-min' : 105,
            'x-max' : 160,
            'rebin' : 1

        },
        'sumHisto_pT_yy_': {
            'x-axis title': '#it{p_{T}}_{#gamma#gamma} [GeV]',
            'y-axis title': 'Events / 5 GeV',
            'units' : 'GeV',
            'x-min' : 500,
            'x-max' : 500500,
            'rebin' : 5,

        },
        'sumHisto_pT_jj_': {
            'x-axis title': '#it{p_{T}}_{jj} [GeV]',
            'y-axis title': 'Events / 5 GeV',
            'units' : 'GeV',
            'x-min' : 500,
            'x-max' : 500500,
            'rebin' : 5

        },
        'sumHisto_m_yyjj_tilde_': { 
            'x-axis title': '#it{m}_{#gamma#gamma#it{jj}} [GeV]',
            'y-axis title': 'Events / 25 GeV',
            'units' : 'GeV',
            'x-min' : 200,
            'x-max' : 500,
            'rebin' : 5

        },
        'sumHisto_pT_yy_div_m_yyjj_tilde_': {
            'x-axis title': '#it{p_{T}}_{#gamma#gamma} / Mtilde',
            'y-axis title': 'Events / 5 GeV',
            'units' : 'GeV',
            'x-min' : 0,
            'x-max' : 1000,
            'rebin' : 5

        },
        'sumHisto_pT_jj_div_m_yyjj_tilde_': {
            'x-axis title': '#it{p_{T}}_{jj} / Mtilde',
            'y-axis title': 'Events / 5 GeV',
            'units' : 'GeV', 
            'x-min' : 0,
            'x-max' : 5000,
            'rebin' : 5

        },
        'sumHisto_pT_yy_div_m_yy_': {
            'x-axis title': '#it{p_{T}}_{#gamma#gamma} / #it{m}_{#gamma#gamma}',
            'y-axis title': 'Events',
            'units' : '',
            'x-min' : 1,
            'x-max' : 1500,
            'rebin' : 5

        },
        'sumHisto_pT_jj_div_m_jj_': {
            'x-axis title': '#it{p_{T}}_{jj} / #it{m}_{jj}',
            'y-axis title': 'Events',
            'units' : '',
            'x-min' : 0,
            'x-max' : 5000,
            'rebin' : 5

        },
        'sumHisto_deltaR_yy_': { 
            'x-axis title': '#Delta#it{R}(#gamma,#gamma)',
            'y-axis title': 'Events / 0.2',
            'units' : '',
            'x-min' : 0.0,
            'x-max' : 3.0,
            'rebin' : 5

        },
        'sumHisto_deltaR_jj_': { 
            'x-axis title': '#Delta#it{R}(j,j)',
            'y-axis title': 'Events / 0.2',
            'units' : '',
            'x-min' : 0.0,
            'x-max' : 3.0,
            'rebin' : 1

        },
        'sumHisto_deltaR_yyjj_': { 
            'x-axis title': '#Delta#it{R}(#gamma,#gamma,j,j)',
            'y-axis title': 'Events / 0.2',
            'units' : '',
            'x-min' : 0.0,
            'x-max' : 3.0,            
            'rebin' : 1
        },
        'sumHisto_N_j_': { 
            'x-axis title': '#it{N}_{jets}',
            'y-axis title': 'Events',
            'units' : '',
            'x-min' : 0,
            'x-max' : 15,
            'rebin' : 1

        },
        'sumHisto_N_j_central_': { 
            'x-axis title': '#it{N}_{central jets}',
            'y-axis title': 'Events',
            'units' : '',
            'x-min' : 0,
            'x-max' : 15,
            'rebin' : 1

        },
        'sumHisto_btag_score_': { 
            'x-axis title': 'Sum of #it{b}-tag scores of 2 jets',
            'y-axis title': 'Events',
            'units' : '',
            'x-min' : 0,
            'x-max' : 20,
            'rebin' : 2

        },
        'sumHisto_m_yyjj_tilde_HM_': { 
            'x-axis title': '#it{m}_{#gamma#gamma#it{jj}} (High-mass) [GeV]',
            'y-axis title': 'Events / 25 GeV',
            'units' : 'GeV',
            'x-min' : 200,
            'x-max' : 500,
            'rebin' : 2

        },
        'sumHisto_MET_': { 
            'x-axis title': '#it{E}_{T}^{miss} [GeV]',
            'y-axis title': 'Events / 25 GeV',
            'units' : 'GeV',
            'x-min' : 0,
            'x-max' : 500,
            'rebin' : 1

        },

        'sumHisto_m_yyjj_': {
            'x-axis title': '#it{m}_{#gamma#gamma#it{jj}} (std) [GeV]',
            'y-axis title': 'Events / 25 GeV',
            'units' : 'GeV',
            'x-min' : 200,
            'x-max' : 500,
            'rebin' : 1

        },
        'sumHisto_m_yyjj_HM_': {
            'x-axis title': '#it{m}_{#gamma#gamma#it{jj}} (std, High-mass) [GeV]',
            'y-axis title': 'Events / 25 GeV',
            'units' : 'GeV',
            'x-min' : 200,
            'x-max' : 500,
            'rebin' : 1

        },

        'sumHisto_m_yyjj_cnstrnd_': {
            'x-axis title': '#it{m}_{#gamma#gamma#it{jj}} (constr) [GeV]',
            'y-axis title': 'Events / 25 GeV',
            'units' : 'GeV',
            'x-min' : 200,
            'x-max' : 500,
            'rebin' : 1

        },
        'sumHisto_m_yyjj_cnstrnd_HM_': {
            'x-axis title': '#it{m}_{#gamma#gamma#it{jj}} (constr, High-mass) [GeV]',
            'y-axis title': 'Events / 25 GeV',
            'units' : 'GeV',
            'x-min' : 200,
            'x-max' : 500,
            'rebin' : 1

        }


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

        'yycj': {
            'color': 46,
            'legend description': '#it{#gamma#gammacj}',
        },
        'yyjj': {
            'color': 5,
            'legend description': '#it{#gamma#gamma+jj}',
        },
        'yybj': {
            'color': 38,
            'legend description': '#it{#gamma#gammabj}',
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
            'color': 6,
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
        }
    }
    return dict

def SignalDict():
    dict = {

        'ZH': {
            'color': 6,
            'legend description': '#it{ZH}',
            },

        'HHlamPlus10': {
            'color': 4,
            'legend description': '#it{HH} #kappa_{#lambda} = 10',
        },
        'HHlamMinus10': {
            'color': 64,
            'legend description': '#it{HH} #kappa_{#lambda} = -10',
        },
        'HHlamPlus4': {
            'color': 51,
            'legend description': '#it{HH} #kappa_{#lambda} = 4',
        },
        'HHlamMinus4': {
            'color': 87,
            'legend description': '#it{HH} #kappa_{#lambda} = -4',
        },
        'HHlamPlus2': {
            'color': 92,
            'legend description': '#it{HH} #kappa_{#lambda} = 2',
        },
        'HHlamMinus2': {
            'color': 97,
            'legend description': '#it{HH} #kappa_{#lambda} = -2',
        },

        'X251toHH': {
            'color': 6,
            'legend description': '#it{X}(251)#it{HH} ',
            },
         
        'X260toHH': {
            'color': 12,
            'legend description': '#it{X}(260)#it{HH} ',
            },

        'X280toHH': {
            'color': 11,
            'legend description': '#it{X}(280)#it{HH} ',
            },

        'X300toHH': {
            'color': 1,
            'legend description': '#it{X}(300)#it{HH} ',
            },

        'X325toHH': {
            'color': 40,
            'legend description': '#it{X}(325)#it{HH} ',
            },

        'X350toHH': {
            'color': 36,
            'legend description': '#it{X}(350)#it{HH} ',
            },

        'X400toHH': {
            'color': 3,
            'legend description': '#it{X}(400)#it{HH} ',
        },
        'X450toHH': {
            'color': 30,
            'legend description': '#it{X}(450)#it{HH} ',
        },
        'X500toHH': {
            'color': 7,
            'legend description': '#it{X}(500)#it{HH} ',
        },
        'X550toHH': {
            'color': 28,
            'legend description': '#it{X}(550)#it{HH} ',
        },
        'X600toHH': {
            'color': 8,
            'legend description': '#it{X}(600)#it{HH} ',
        },
        'X700toHH': {
            'color': 2,
            'legend description': '#it{X}(700)#it{HH} ',
        },
       'X800toHH': {
            'color': 9,
            'legend description': '#it{X}(800)#it{HH} ',
        },

       'X900toHH': {
            'color': 16,
            'legend description': '#it{X}(900)#it{HH} ',
        },

        'X1000toHH': {
            'color': 5,
            'legend description': '#it{X}(1000)#it{HH} ',
        },
        'X2000toHH': {
            'color': 29,
            'legend description': '#it{X}(2000)#it{HH} ',
        },
        'X3000toHH': {
            'color': 46,
            'legend description': '#it{X}(3000)#it{HH} ',
        }
    }
    return dict 

def SelectionDict():
    dict = {
        'Continuum_CR': {
            'legend upper': 'Continuum bkg. CR selection',
            'legend lower': '',
        },
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

       'Resonant': {
            'legend upper': 'Resonant selection',
            'legend lower': '',

        },        

       'Resonant_Zbb_window': {
            'legend upper': 'Resonant for ZH',
            'legend lower': '',

        },

       'Presel_Zbb_window': {
            'legend upper': 'Presel for ZH',
            'legend lower': '',

        },

       'Presel': {
            'legend upper': 'Preselection',
            'legend lower': '',

        },


        'Continuum_CR': {
            'legend upper': 'Continuum bkg CR',
            'legend lower': '',

            },

       'Continuum_CR_Zbb_window': {
            'legend upper': 'Continuum bkg CR for ZH',
            'legend lower': '',
           }

    }

    return dict
