#!/usr/bin/env python
import os


version = "H024" #H025
Dir = ["Resonant"] #["Non_Resonant","ZH"]
jsons = ["Backgrounds","PhotonJetBkg","Data","Signals"]

extra = "" #string to use if you have a sub-file with some small changes ex. Backgrounds2.js may only have 1 variable which you want to test without disturbing the original file.


for d in Dir:

    for j in jsons:

        output_name = "out_"+d+"_"+j
        localCMD = "./hhbbyy json/"+version+"/"+d+"/"+j+".js"
        CMD = './RunCondor.sh \'%s\' %s ' % (localCMD, output_name)

    print (CMD)
    os.system(CMD)
    
