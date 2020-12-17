import os

Signals  = ["260","300","325","350","400","280","450","500","550","600","700","800","900","1000"]

print("Running plotter for signals with HH resonances at (GeV): ")
print(Signals)

for S in Signals:
    os.system("python plottingScheduler.py -s X"+S+"toHH -r Resonant_BDT_"+S)
