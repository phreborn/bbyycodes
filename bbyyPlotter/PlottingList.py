
#LISTS OF:
# Variables, Samples, Regions & Signals

# List of keys from the histogramming dictionary                                                                                                               
histosToPlot = [
                  'sumHisto_m_yy_',
                  'sumHisto_m_jj_',
                  'sumHisto_m_yyjj_tilde_',
                  'sumHisto_m_yyjj_tilde_HM_',
                  'sumHisto_deltaR_yy_',
                  'sumHisto_deltaR_jj_',
                  'sumHisto_deltaR_yyjj_',
                  'sumHisto_N_j_',
                  'sumHisto_N_j_central_',
                  'sumHisto_btag_score_',
                  'sumHisto_MET_',
#                  'sumHisto_m_yyjj_',
#                  'sumHisto_m_yyjj_HM_',
#                  'sumHisto_m_yyjj_cnstrnd_',
#                  'sumHisto_m_yyjj_cnstrnd_HM_',
                  'sumHisto_pT_jj_',
                  'sumHisto_pT_jj_div_m_jj_',
                  'sumHisto_pT_jj_div_m_yyjj_tilde_',
                  'sumHisto_pT_yy_',
                  'sumHisto_pT_yy_div_m_yy_',
                  'sumHisto_pT_yy_div_m_yyjj_tilde_'
               ]

# List of keys from the samples dictionary                                                                             
samplesToStack = [
                    '15_to_18_data',
                    'ttyy_nohad',
                    'ttyy_had',
                    'yybj',
                    'yycj',
                    'yyjj',
                    'HH',
                    # Then all of the single H backgrounds (these are combined, by default)     
                    'ggH',
                    'VBF',
                    'WpH',
                    'WmH',
                    'ZH',
                    'ggZH',
                    'ttH',
                    'bbH',
                    'tWH',
                    'tHjb',
                 ]


# List of selections to plot                                                                                           
selections = [
#                'Continuum_CR_Zbb_window', # For the continuum CR        
#                'Resonant_Zbb_window',
#                'Presel_Zbb_window',
#                'Presel'
#                 'Continuum', # For the continuum backgrounds  (2-btag region)
#                 'Resonant',
                'LM_A', # Category 1                                         
               
                'LM_B', # Category 2                                          
         
                'HM_A', # Category 3                                         
      
                'HM_B', # Category 4                                        
                    
             ]


# List of signals to plot                                                                                                                      
signals = [#'ZH'
            'HHlamPlus10',
            'HHlamMinus10',
            'HHlamPlus4',
            'HHlamMinus4',
            'HHlamPlus2',
            'HHlamMinus2',
            #'X1000toHH',
            #'X2000toHH',
            #'X251toHH',
            #'X260toHH',
            #'X280toHH',
            #'X3000toHH',
            #'X300toHH',
            #'X325toHH',
            #'X350toHH',
            #'X400toHH',
            #'X450toHH',
            #'X500toHH',
            #'X550toHH',
            #'X600toHH',
            #'X700toHH',
            #'X800toHH',
            #'X900toHH',
             ]
