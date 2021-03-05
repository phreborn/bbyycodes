cp PlottingList_Res.py PlottingList.py
python plottingScheduler.py -p -o Plots/Blind/Resonant/
python plottingScheduler.py -UB -p -o Plots/Unblind/Resonant/


cp PlottingList_m_yyjj.py PlottingList.py
python plottingScheduler.py -p -l -o Plots/m_yybb/Stop_1_TeV/Blind/
python plottingScheduler.py -UB -p -l -o Plots/m_yybb/Stop_1_TeV/Unblind/
