import os


output_dir = "NonRes"

#samples = ["ttH","ZH","ggH","bbH","tHjb","tWH","ggZH","WmH","WpH","VBF"]
samples = ["HH","singleHiggs","yyjj"]

selections = ["loose_HMass","loose_LMass","tight_HMass","tight_LMass"]

for cat in selections:
    for sp  in samples:    
        print("Running "+sp+" with DSCB")
        os.system('root -l \"Modelling_bbyy.C(\\"projects/HHbbyy/signalModels/HH/config/'+output_dir+'/\\",false,\\"'+sp+'\\",\\"'+cat+'\\")\" -q -b')


    print("Running "+sp+" with Exponential function")

    os.system('root -l \"Modelling_bbyy.C(\\"projects/HHbbyy/signalModels/HH/config/'+output_dir+'/\\",false,\\"yyjj\\",\\"'+cat+'\\",\\"Exponential\\")\" -q -b')
