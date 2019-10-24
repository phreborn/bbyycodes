#include "VariablePlotter.h"
#include "JSONDoc.h"
#include "Controller.h"
#include "ROOTHelper.h"
#include "TROOT.h"

DECLARE_ALGORITHM( VariablePlotter , VariablePlotter )

void VariablePlotter::execute()
{

  // Fetch the JSON 
  mytest::JSONData& document=Controller::GetDocument();

  // First extract selections from the JSON
  // Full parsing is handled by the serializer.h
  std::vector<std::string> cutFlows={};
  for (auto is:document.selections.selMap)
  {
    std::cout << " new selection being added to the list "<<is.first<<std::endl;
    cutFlows.push_back(is.first);
  }

  // Now extract the desired MC campaigns to run on
  std::vector<std::string> mcCampaigns={};
  for (auto is:document.luminosity.lumiMap)
  {
    std::cout << " MC campaigns being added to the list "<<is.first<<std::endl;
    mcCampaigns.push_back(is.first);
  }
  
  // For logging purposes, used later
  std::string logging;

  std::map<std::string,TH1F*,std::less<std::string> > sumhistoMap;

  for (auto iSample:document.samples.samples) {
    mytest::aSample thisSample=document.samples.samples[iSample.first];
    const std::string sampleName=iSample.first;
    for (auto iCut: cutFlows){
      for (auto ikk:document.variables.varMap)
      {
        std::string variableName=ikk.first;
        std::string variableValue=(ikk.second).first;
        int nbins=(ikk.second).second.nBins;
        double lowerBin=(ikk.second).second.lowerBin;
        double upperBin=(ikk.second).second.upperBin;
        std::string his="sumHisto_"+variableName+"_"+iCut;
        TH1F *sumHisto=new TH1F(his.c_str(),his.c_str(),nbins,lowerBin,upperBin);
        sumhistoMap[his]=sumHisto;
      }

      for (auto iMC: mcCampaigns){
        const std::string mc=iMC;
        logging=sampleName+"_"+mc+"_"+iCut;

        // Pick up the selections for each of the different categories
        std::string select=document.selections.selMap[iCut];
        
        if (sampleName=="data") select=document.selections.dataSel;
        // Below removed to now
        //if (document.selections.weight.empty()) select+="*"+document.selections.weight;
        
        // Pick up the luminosity 
        double lumi=document.luminosity.lumiMap[iMC];
        // Data and MC directories from JSON
        std::string dataDir=document.directories.dirMap[iMC];
        if (sampleName=="data") dataDir=document.directories.dataDir;
        
        // File name
        std::string fileName=thisSample.sampleMap[iMC];

        //////////////// Below is a hack until we have a proper fix
        // This part is a place holder until we have all MC. We are duplicating mc16d with the luminosity of mc16d and mc16e!!
        if (fileName=="mc16d.PowhegPy8_NNPDF30_VBFH125.MxAODDetailed.e6636_s3126_r10201_p3665.h024.root")
          dataDir="root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h024/mc16d/Nominal/";
        if (fileName=="mc16d.aMCnloHwpp_hh_yybb_AF2.MxAODDetailed.e4419_a875_r10201_p3629.h024.root")
          dataDir="root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h024/mc16d/Nominal/";
        if (fileName=="mc16d.MGPy8_ttgamma_nonallhadronic_AF2.MxAODDetailed.e6155_a875_r10201_p3703.h024.root")
          dataDir="root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h024/mc16d/Nominal/";
        //if (fileName=="yy_mc16a.root")
        //  dataDir="root://eosatlas.cern.ch//eos/atlas/user/a/altaylor/bbgg/h024/";
        //if (fileName=="yy_mc16e.root")
        //  dataDir="root://eosatlas.cern.ch//eos/atlas/user/a/altaylor/bbgg/h024/";
        if (fileName=="mc16a_hh_yybb_NLO.root" || fileName=="mc16d_hh_yybb_NLO.root" || fileName=="mc16e_hh_yybb_NLO.root")
          dataDir="root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples/";
        if (fileName=="15_16_data.root" || fileName=="17_data.root" || fileName=="18_data.root")
          dataDir="root://eosatlas.cern.ch//eos/atlas/user/a/altaylor/bbgg/h024/";
        ////////////////
       
       
 
        TFile* file=ROOTHelper::GetTFile(sampleName,mc,dataDir+fileName);
        std::string histoName=thisSample.histoName;
        TH1* histo=dynamic_cast<TH1*>(file->Get(histoName.c_str()));
        double sum1=0,sum2=0,sum3=0;
        if (histo) {
          sum1=histo->GetBinContent(1);
          sum2=histo->GetBinContent(2);
          sum3=histo->GetBinContent(3);
        }
        // First, determine the sum of weights from the MxAOD object
        double sum_weights=(sum1/sum2)*sum3;
        TTree* tree=(TTree*)file->Get("CollectionTree");
  
        // Now loop over the variables, scale to the appropriate lumi, and add the histogram
        // to the histo map.
        for(auto iVar : document.variables.varMap){
          std::string var = iVar.second.first;
          std::string varName = iVar.first;

          std::string hName=varName+"_"+logging;

          std::string hN="sumHisto_"+varName+"_"+iCut;					
          int nbins=(iVar.second).second.nBins;
          double lowerBin=(iVar.second).second.lowerBin;
          double upperBin=(iVar.second).second.upperBin;
          std::cout<<"   ++++ bins "<<nbins<<" "<<lowerBin<<" "<<upperBin<<" hname "<<hName<<std::endl;
          TH1F *his=new TH1F(hName.c_str(),hName.c_str(),nbins,lowerBin,upperBin);
          std::string vvar=var+" >> "+hName;
          tree->Draw(vvar.c_str(),select.c_str(),"HIST");
          his->Scale(lumi/sum_weights);
          sumhistoMap[hN]->Add(his);
        }
      }

      // Write to the plotting directory 
      DIR* dir = opendir("plots");
      if (!dir) const int dir_err = mkdir("plots", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);                   
      TFile outfile (("plots/"+sampleName+"_"+iCut+".root").c_str(),"recreate");
      for (auto iy:sumhistoMap)
        iy.second->Write();
      sumhistoMap.clear();
      outfile.ls();
      outfile.Close();
    }
  }

  std::cout<<std::endl<<std::endl<<" VariablePlotter::execute() done !!!! "<<std::endl<<std::endl;
}
