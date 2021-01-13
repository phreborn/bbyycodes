import os


output_dir = "NonRes"
path = "../run/plots/" # Where are your input files?  default = "data"

#samples = ["ttH","ZH","ggH","bbH","tHjb","tWH","ggZH","WmH","WpH","VBFH","VBF"]
samples= ["singleH","HH_ggF_VBF","yy","HH_H"]

selections = ["loose_HMass","loose_LMass","tight_HMass","tight_LMass"]

for cat in selections:
    
    for sp  in samples:    

        if os.path.isfile("../run/plots/"+sp+"_"+cat+".root"):
            print("Found file")
        else:
            print("WARNING, file does not exist!")  
            ToMerge = []

            if (sp =="singleH"):
                ToMerge = ["ttH","ZH","ggH","bbH","tHjb","tWH","ggZH","WmH","WpH","VBFH"]
            
            if (sp =="HH_ggF_VBF"):
                ToMerge = ["HH","VBF"]

            if (sp =="HH_H"):
                ToMerge = ["HH","VBF","ttH","ZH","ggH","bbH","tHjb","tWH","ggZH","WmH","WpH","VBFH"]

            tree_files = "hadd "+path+sp+"_"+cat+"_tree.root "
            histo_files = "hadd "+path+sp+"_"+cat+".root "
            for p in ToMerge:
                tree_files+= path+p+"_"+cat+"_tree.root "
                histo_files+= path+p+"_"+cat+".root "
                    
            print(tree_files)
            os.system(tree_files)
            
            print(histo_files)
            os.system(histo_files)
            
            

        if (sp != "yy"):
            print("Running "+sp+" with DSCB")
            os.system('root -l \"Modelling_bbyy.C(\\"projects/HHbbyy/signalModels/HH/config/'+output_dir+'/\\",false,\\"'+sp+'\\",\\"'+cat+'\\",\\"'+path+'\\",\\"DSCB\\")\" -q -b')
            
        else:

            print("Running "+sp+" with Exponential function")
            os.system('root -l \"Modelling_bbyy.C(\\"projects/HHbbyy/signalModels/HH/config/'+output_dir+'/\\",false,\\"yy\\",\\"'+cat+'\\",\\"'+path+'\\",\\"Exponential\\",105,160)\" -q -b')

