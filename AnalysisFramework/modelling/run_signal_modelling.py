import os


output_dir = "NonRes"
path = "../run/plots/" # Where are your input files?  default = "data"

#samples = ["ttH","ZH","ggH","bbH","tHjb","tWH","ggZH","WmH","WpH","VBF"]
samples = ["HH","singleHiggs","yy"]

selections = ["loose_HMass","loose_LMass","tight_HMass","tight_LMass"]

for cat in selections:
    for sp  in samples:    

        if (sp != "yy"):
            print("Running "+sp+" with DSCB")
            os.system('root -l \"Modelling_bbyy.C(\\"projects/HHbbyy/signalModels/HH/config/'+output_dir+'/\\",false,\\"'+sp+'\\",\\"'+cat+'\\",\\"'+path+'\\",\\"DSCB\\")\" -q -b')
            
        else:

            print("Running "+sp+" with Exponential function")
            os.system('root -l \"Modelling_bbyy.C(\\"projects/HHbbyy/signalModels/HH/config/'+output_dir+'/\\",false,\\"yy\\",\\"'+cat+'\\",\\"'+path+'\\",\\"Exponential\\")\" -q -b')
