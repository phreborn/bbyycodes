import os

Signals = ["260","300","325","350","400"]

print("Running plotter for signals with HH resonances at (GeV): ")
print(Signals)

for S in Signals:
    os.system("python plottingScheduler.py -s X"+S+"toHH -r Resonant_BDT_"+S)
