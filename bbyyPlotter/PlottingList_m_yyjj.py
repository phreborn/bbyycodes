
#LISTS OF:
# Variables, Samples, Regions & Signals

# List of keys from the histogramming dictionary                                                                                                               
histosToPlot = [
                  #'sumHisto_m_yy_',
                  #'sumHisto_m_jj_',
                  'sumHisto_m_yyjj_tilde_',
                  #'sumHisto_m_yyjj_tilde_HM_',
                  #'sumHisto_deltaR_yy_',
                  #'sumHisto_deltaR_jj_',
                  #'sumHisto_deltaR_yyjj_',
                  #'sumHisto_dR_yy_',
                  #'sumHisto_N_j_',
                  #'sumHisto_N_j_central_',
                  ##'sumHisto_btag_score_',
                  ##'sumHisto_MET_',
                  #'sumHisto_m_yyjj_',
#                 ##'sumHisto_m_yyjj_HM_',
                  #'sumHisto_m_yyjj_cnstrnd_',
#                 ##'sumHisto_m_yyjj_cnstrnd_HM_',
                  ##'sumHisto_pT_jj_',
                  ##'sumHisto_pT_jj_div_m_jj_',
                  ##'sumHisto_pT_jj_div_m_yyjj_tilde_',
                  ##'sumHisto_pT_yy_',
                  ##'sumHisto_pT_yy_div_m_yy_',
                  ##'sumHisto_pT_yy_div_m_yyjj_tilde_'
                 #"sumHisto_nonRes_XGBoost_btag77_BCal_withTop_lowMass_Score_",
                 #"sumHisto_nonRes_XGBoost_btag77_BCal_withTop_highMass_Score_"
                  
               ]

# List of keys from the samples dictionary                                                                             
samplesToStack = [
                    '15_to_18_data',
                    #'15_to_18_data_SB',
                    #'15_to_18_data_jj',   # Resonant case, SF applied in weight
                    #'15_to_18_data_yj',   # Resonant case, SF applied in weight
                    'jj_reweighted',   #calculate yield Non-resonant case
                    'yj_reweighted',   #calculate yield Non-resonant case
                    
		    #'ttyy_allhad_SB',     #calculate yield
		    #'ttyy_noallhad_SB',   #calculate yield

                   'yybb_reweighted',
                   'yyrr_reweighted',
                   #'yybj_reweighted',
                   #'yycj_reweighted',
                   #'yylj_reweighted',
                   #'yybj',
                   #'yycj',
                   #'yylj',
                    
                    #'yy',   # Resonant case, SF applied in weight
                    #'yy',   #commented by ZIHANG
                    #'yy_reweighted',   #commented by ZIHANG

                    # Then all of the single H backgrounds (these are combined, by default)     
                    #'ggH',
                    #'WpH',
                    #'WmH',
                    #'ZH',
                    #'ggZH',
                    #'ttH',
                    #'bbH',
                    #'tWH',
                    #'tHjb',


                    # h025 -----------------
                    #'ttH_PowhegPy8',
                    #'ZH_PowhegPy8',
                    #'ttyy_allhad',
                    #'ttyy_noallhad',
                    #"VBFH_PowhegPy8",
                    #"WmH_PowhegPy8",
                    #"WpH_PowhegPy8",
                    #"ggZH_PowhegPy8",
                    #"ggH_PowhegPy8",
                    #"bbH",
                    #"tHjb",
                    #"tWH",
                    ## signal
                    #'HH',
                    #'VBF',

                    # h026
                    'ttH_PowhegPy8',
                    'ZH_PowhegPy8',
                    'ttyy_allhad',
                    'ttyy_noallhad',
                    "VBFH_PowhegPy8",
                    "WmH_PowhegPy8",
                    "WpH_PowhegPy8",
                    "ggZH_PowhegPy8",
                    "ggH_PowhegPy8",
                    "bbH",
                    "tHjb",
                    "tWH",
                    # signal
                    'HH',
                    'VBF',

		    #'Resonance',

                 ]


# List of selections to plot                                                                                           
selections = [
#                'Continuum_CR_Zbb_window', # For the continuum CR        
#                'Resonant_Zbb_window',
#                'Presel_Zbb_window',
#                'Presel'
#                 'Continuum', # For the continuum backgrounds  (2-btag region)
#                 'Resonant',
                #'LM_A', # Category 1                                                       
#                'LM_B', # Category 2                                                   
#                'HM_A', # Category 3                                         
#                'HM_B', # Category 4  
#
#=========== Non-resonant ==============
"Validation_2bjet",
#"XGBoost_btag77_withTop_BCal_tightScore_HMass",
#"XGBoost_btag77_withTop_BCal_tightScore_LMass",
#"XGBoost_btag77_withTop_BCal_looseScore_HMass",
#"XGBoost_btag77_withTop_BCal_looseScore_LMass",
#"X260toHH_BDT_Selection_h026_optimized",
#"X280toHH_BDT_Selection_h026_optimized",
#"X300toHH_BDT_Selection_h026_optimized",
#"X325toHH_BDT_Selection_h026_optimized",
#"X350toHH_BDT_Selection_h026_optimized",
#"X400toHH_BDT_Selection_h026_optimized",
#"X450toHH_BDT_Selection_h026_optimized",
#"X500toHH_BDT_Selection_h026_optimized",
#"X550toHH_BDT_Selection_h026_optimized",
#"X600toHH_BDT_Selection_h026_optimized",
#"X700toHH_BDT_Selection_h026_optimized",
#"X800toHH_BDT_Selection_h026_optimized",
#"X900toHH_BDT_Selection_h026_optimized",
#"X1000toHH_BDT_Selection_h026_optimized",
             ]


# List of signals to plot                                                                                                                      
signals = [#'ZH_x10'
 #           'HHlamPlus10',
 #           'HHlamMinus10',
 #           'HHlamPlus4',
#            'HHlamMinus4',
 #           'HHlamPlus2',
 #           'HHlamMinus2',
#            'X1000toHH',
#            'X2000toHH',
#            'X251toHH',
#            'X260toHH',
#            'X280toHH',
#            'X3000toHH',
            'X300toHH_BDT_Selection_h026_optimized',
#            'X325toHH',
#            'X350toHH',
#            'X400toHH',
#            'X450toHH',
            'X500toHH_BDT_Selection_h026_optimized',
#            'X550toHH',
#            'X600toHH',
#            'X700toHH',
#            'X800toHH',
#            'X900toHH',
           ]
