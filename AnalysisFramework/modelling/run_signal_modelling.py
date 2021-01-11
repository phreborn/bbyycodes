import os


output_dir = "NonRes_v1"

samples = ["HH","ttH","ZH","ggH","bbH","tHjb","tWH","ggZH","WmH","WpH","VBF"]

for sp  in samples:
    print("Running "+sp+" with DSCB")
    os.system('root -l \"Modelling_bbyy.C(\\"projects/HHbbyy/signalModels/HH/config/'+output_dir+'/\\",false,\\"'+sp+'\\")\" -q -b')


print("Running "+sp+" with Exponential function")

os.system('root -l \"Modelling_bbyy.C(\\"projects/HHbbyy/signalModels/HH/config/'+output_dir+'/\\",false,\\"yyjj\\",\\"Exponential\\")\" -q -b')
