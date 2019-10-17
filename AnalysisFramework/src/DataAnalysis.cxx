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

  // Fetch the JSON 
  mytest::JSONData& document=Controller::GetDocument();

  // First extract selections from the JSON
  // Full parsing is handled by the serializer.h
  std::vector<std::string> cutFlows={};
  for (auto is:document.selections.selMap)
  {
    std::cout << " New selection being added to the list "<<is.first<<std::endl;
    cutFlows.push_back(is.first);
  }

  // Loop over the datafiles, and add them to the total datafiles vector
  std::vector<std::string> Campaigns = {};
  for (auto is:document.directories.dirMap)
  {
    std::cout << " New datafile being added to the list "<<is.first<<std::endl;
    Campaigns.push_back(is.first);
  }


  // For logging purposes, used later
  std::string logging;

  for (auto iSample:document.samples.samples) {
    // As a matter of principle there is only one sample
    mytest::aSample thisSample=document.samples.samples[iSample.first];
    const std::string sampleName=iSample.first;
    std::cout << "Sample name "<<sampleName<<std::endl;

    TChain* nt = new TChain("CollectionTree");

    // String all of the separate data files together
    // into a single TChain
    for (auto iMC: Campaigns){
      const std::string mc=iMC;
      // Data directory
      std::string dataDir=document.directories.dirMap[iMC];
      // File name
      std::string fileName=thisSample.sampleMap[iMC];
      // Combine directory and file name 
      std::string file = dataDir+fileName;
      std::cout << "File: " << file.c_str() << std::endl;
      nt->Add(file.c_str());
    }

    // Now that the data files are merged, let's loop over the different
    // selections, and produce one root file per selection
    for (auto iCut: cutFlows){
      DIR* dir = opendir("plots");
      if (!dir) const int dir_err = mkdir("plots", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);            	
      std::string hFile="plots/" + iSample.second.histoName + "_" + iCut + ".root";
      TFile f_w(hFile.c_str(), "RECREATE" );
      std::cout<<"Histogram file being created "<<hFile<<std::endl;
      logging=sampleName+"_"+iCut;

      // Specify the actual selection string
      std::string select=document.selections.selMap[iCut];

      //if (document.selections.weight.empty()) select+="*"+document.selections.weight;		
      // Now loop over the variables
      for(auto iVar : document.variables.varMap){
        std::string var = iVar.second.first;
        std::string varName = iVar.first;

        std::string hName="sumHisto_"+varName+"_"+iCut;

        int nbins=(iVar.second).second.nBins;
        double lowerBin=(iVar.second).second.lowerBin;
        double upperBin=(iVar.second).second.upperBin;
        TH1F *his=new TH1F(hName.c_str(),hName.c_str(),nbins,lowerBin,upperBin);
        his->Sumw2();
        std::string s_a=var+" >> "+hName;
        nt->Draw(s_a.c_str(), select.c_str()); 

        TCanvas c1;
        std::string hN="sumHisto_"+varName+"_data_"+iCut;
        std::string canvasName("plots/"+hN);
        canvasName+=".png";
        c1.SaveAs(canvasName.c_str());
      } 
      // Write and close the root file
      f_w.Write();
      f_w.Close();
    }

  }

}

