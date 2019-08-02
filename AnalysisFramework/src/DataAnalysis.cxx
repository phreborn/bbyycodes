#include "DataAnalysis.h"
#include "JSONDoc.h"
#include "Controller.h"
#include "ROOTHelper.h"
#include "TROOT.h"

#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

DECLARE_ALGORITHM(DataAnalysis , DataAnalysis)

void DataAnalysis::execute()
{
	
	// let's roll
		
	const std::vector<std::string> Campaigns={"data1","data2"};
	
	mytest::JSONData& document=Controller::GetDocument();
		
	std::string logging;
	
	for (auto iSample:document.samples.samples) {
	     // as a matter of principle there is only one sample
		 std::string hFile=iSample.second.histoName;
		 TFile f_w(hFile.c_str(), "recreate" );
		 std::cout<<"histogram file being created "<<hFile<<std::endl;
		 
	     mytest::aSample thisSample=document.samples.samples[iSample.first];
	     const std::string sampleName=iSample.first;
		 std::cout << "sample name "<<sampleName<<std::endl;

		 TChain* nt = new TChain("CollectionTree");
		 
		 for (auto iMC: Campaigns){
			const std::string mc=iMC;
			logging=sampleName;
									
			// data dir
			std::string dataDir=document.directories.dirMap[iMC];
			// file name, this is going to look disgusting
			std::string fileName=thisSample.sampleMap[iMC];
			// combine directory and file name 
			std::string file = dataDir+"/"+fileName;

			nt->Add(file.c_str());
		}
		// selection first 
		std::string select=document.selections.selMap["Selection"];
		if (document.selections.weight.empty()) select+="*"+document.selections.weight;		

		for(auto iVar : document.variables.varMap){
			std::string var = iVar.second.first;
			std::string varName = iVar.first;
					
			std::string hName="h_"+varName+logging;
					
			int nbins=(iVar.second).second.nBins;
            		double lowerBin=(iVar.second).second.lowerBin;
            		double upperBin=(iVar.second).second.upperBin;
            		TH1F *his=new TH1F(hName.c_str(),hName.c_str(),nbins,lowerBin,upperBin);
			his->Sumw2();
			std::string s_a=var+" >> "+hName;
			nt->Draw(s_a.c_str(), select.c_str());
		
			DIR* dir = opendir("plots");
			if (!dir) const int dir_err = mkdir("plots", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);            	
			TCanvas c1;
    			std::string canvasName("plots/"+hName);
    			canvasName+=".png";
    			c1.SaveAs(canvasName.c_str());
		}
		f_w.Write();
    	f_w.Close();
	    
	}
		
}

