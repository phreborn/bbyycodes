import os

# Files will run on series, so for higher efficiency when running many jsons you should consider using the SubmitCondor.py script instead of this.

Dir = ["Non-Resonant"]
jsons = ["Backgrounds","PhotonJetBkg","Data","Signals"]

extra = "" #string to use if you have a sub-file with some small changes ex. Backgrounds2.js may only have 1 variable which you want to test without disturbing the original file.

for x in Dir:
    for name in jsons:
        os.system("nohup ./hhbbyy "+x+"/"+name+extra+".js > out_"+x+"_"+name+extra+".txt &") 

