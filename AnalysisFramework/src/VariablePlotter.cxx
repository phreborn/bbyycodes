#include "VariablePlotter.h"
#include "JSONDoc.h"
#include "Controller.h"
#include "ROOTHelper.h"
#include "TROOT.h"
#include <memory>
#include <chrono>


DECLARE_ALGORITHM( VariablePlotter , VariablePlotter )

void VariablePlotter::execute()
{
  
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  
  // Fetch the JSON 
  mytest::JSONData& document=Controller::GetDocument();
  

  bool dumpNtuple = false;

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
  
  float theXStimesBR = 1.0;
  // Add a map for the resonant singnal x-section * BR
  std::map<std::string, float> XStimesBR; // in fb, and normalised to 1 fb^-1
  XStimesBR["X251toHH"] = 0.960;
  XStimesBR["X260toHH"] = 0.960;
  XStimesBR["X280toHH"] = 1.039;
  XStimesBR["X300toHH"] = 0.964;
  XStimesBR["X325toHH"] = 0.718;
  XStimesBR["X350toHH"] = 0.553;
  XStimesBR["X400toHH"] = 0.411;
  XStimesBR["X450toHH"] = 0.228;
  XStimesBR["X500toHH"] = 0.182;
  XStimesBR["X550toHH"] = 0.156;
  XStimesBR["X600toHH"] = 0.104;
  XStimesBR["X700toHH"] = 0.068;
  XStimesBR["X800toHH"] = 0.052;
  XStimesBR["X900toHH"] = 0.041;
  XStimesBR["X1000toHH"] = 0.033;
  XStimesBR["X2000toHH"] = 0.009;
  XStimesBR["X3000toHH"] = 0.008;

  std::vector< std::string > treeList ;

  DIR* dir = opendir("plots");
  if (!dir) const int dir_err = mkdir("plots", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

  for (auto iSample:document.samples.samples) {
    mytest::aSample thisSample=document.samples.samples[iSample.first];
    const std::string sampleName=iSample.first;
    for (auto iCut: cutFlows){
      TFile outfile (("plots/"+sampleName+"_"+iCut+".root").c_str(),"RECREATE");
   
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

      // Adding an additional truth-matching feature, which we only need when
      // running on the yy samples to get the yycj, yybj, yyjj separation
      std::string truthMatch = "";        
      if (sampleName == "yybj") truthMatch = " && HGamAntiKt4EMTopoJetsAuxDyn.HadronConeExclTruthLabelID[0]==5";
      if (sampleName == "yycj") truthMatch = " && HGamAntiKt4EMTopoJetsAuxDyn.HadronConeExclTruthLabelID[0]==4";
      if (sampleName == "yyjj") truthMatch = " && (HGamAntiKt4EMTopoJetsAuxDyn.HadronConeExclTruthLabelID[0]!=4 && HGamAntiKt4EMTopoJetsAuxDyn.HadronConeExclTruthLabelID[0]!=5)";

      // Have a specific XStimesBR if we are running on a resonant signal
      if (sampleName.find("toHH") != std::string::npos) theXStimesBR = XStimesBR[sampleName];
	
      for (auto iMC: mcCampaigns){
        const std::string mc=iMC;
        logging=sampleName+"_"+mc+"_"+iCut;

        // Pick up the selections for each of the different categories
        std::string select=document.selections.selMap[iCut];
        select = select.std::string::replace(select.find("HGamEventInfoAuxDyn.isPassed"), std::string("HGamEventInfoAuxDyn.isPassed").length(), "HGamEventInfoAuxDyn.isPassed"+truthMatch);
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
          dataDir="root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples/";
        ////////////////

        TFile* file=ROOTHelper::GetTFile(sampleName,mc,dataDir+fileName);
        std::string histoName=thisSample.histoName;
        TH1* histo=dynamic_cast<TH1*>(file->Get(histoName.c_str()));
        double sum1=0,sum2=0,sum3=0;
	if (histo) {
           sum1=histo->GetBinContent(1);//“N_{xAOD}
           //sum1=histo->GetBinContent(4);//No_Duplicate -- this is a temporary solution to avoid usage of duplicate events which are present both in h024 and h025
           sum2=histo->GetBinContent(2);//N_{DxAOD}
           sum3=histo->GetBinContent(3);//AllEvents
        }
        //First, determine the sum of weights from the MxAOD object
        double sum_weights=(sum1/sum2)*sum3; //AllEvent*(NxAOD/DxAOD) -- for signal samples it does not matter since the number of events in the DxAOD is the same as the number in MxAOD, but it does matter for backgrounds, which have skimming applied at the DxAOD level 
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
	  std::shared_ptr<TH1F> his = std::make_shared<TH1F>(hName.c_str(),hName.c_str(),nbins,lowerBin,upperBin);
	  std::string vvar=var+" >> "+hName;
          std::cout << "Drawing with selection: " << select.c_str() << std::endl;
          tree->Draw(vvar.c_str(),select.c_str(),"HIST");
	  //auto his = df_filter.Histo1D({hName.c_str(),hName.c_str(),nbins,lowerBin,upperBin},var.c_str());
          std::cout << "HIST ENTRIES ===== " << his->GetEntries() << std::endl;
	  his->Scale(lumi*theXStimesBR/sum_weights);
          std::cout<< "Scale by = "<< lumi*theXStimesBR/sum_weights << std::endl;
          //sumhistoMap[hN]->Add(his.GetPtr());
	  sumhistoMap[hN]->Add(his.get());
          std::cout<< "added histo =====" << std::endl;
          std::cout<< "VAR = " << var << ",     VAR NAME = " << varName << std::endl;
        }//iVar
	
	if (dumpNtuple) {
          
	  ROOT::RDataFrame df(*tree);      
	  auto df_filter = df.Filter(select);
	  std::cout <<  "DF ENTRIES ===== " << *(df_filter.Count()) << std::endl;
	  double df_weight = lumi*theXStimesBR/sum_weights;
          auto df_out = df_filter.Define("weight", std::to_string(df_weight)).Define("m_yy", "HGamEventInfoAuxDyn.m_yy*0.001").Define("m_jj", "HGamEventInfoAuxDyn.yybb_m_jj*0.001");
	  treeList = {"weight","m_yy","m_jj"};
          /*
          auto df_out = df_filter.Define("weight", std::to_string(df_weight));
          treeList.push_back("weight","m_yy","m_jj");
          for(auto iVar : document.variables.varMap) {
	    std::string var = iVar.second.first;
            std::string varName = iVar.first;
            if ( varName == "m_yy" || varName == "m_jj" ) {
              std::cout<< "varName =======" << varName << ", var ======" << var << std::endl;
              df_out.Define(varName, var);
              treeList.push_back(varName);
              std::cout<< "Print after custom Define" << std::endl;
	    }
          }
          
          //auto defColNames = df.GetDefinedColumnNames();
          //auto defColNames = df_filter.GetColumnNames();
          //for (auto &&defColName : defColNames) std::cout << defColName << std::endl;
          //auto df_out = df_filter.Define("m_yy", "HGamEventInfoAuxDyn.m_yy*0.001").Define("weight", std::to_string(df_weight)).Define("m_jj", "HGamEventInfoAuxDyn.yybb_m_jj*0.001");
          ROOT::RDF::RSnapshotOptions opts;
	  opts.fMode="RECREATE";
          //df_out.Snapshot(tree->GetName(),"plots/"+sampleName+"_"+mc+"_"+iCut+"_tree.root",treeList,opts);
	  df_out.Snapshot(tree->GetName(),"plots/"+sampleName+"_"+mc+"_"+iCut+"_tree.root",treeList, opts);
          */ //commented out while waiting for Danilo
          ROOT::RDF::RSnapshotOptions opts;
          opts.fMode="RECREATE";
          df_out.Snapshot(tree->GetName(),"plots/"+sampleName+"_"+mc+"_"+iCut+"_tree.root",treeList, opts);
	}
      }//mcCampaigns
      // Write to the plotting directory 
      //iDIR* dir = opendir("plots");
      //if (!dir) const int dir_err = mkdir("plots", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);                   
      //TFile outfile (("plots/"+sampleName+"_"+iCut+".root").c_str(),"RECREATE");
      outfile.cd();
      for (auto iy:sumhistoMap)
        iy.second->Write();
      sumhistoMap.clear();
      outfile.ls();
      outfile.Close();
      if (dumpNtuple) {
        std::string outName = sampleName+"_"+iCut+"_tree.root";
        std::string hadd = "cd plots/; hadd -f "+outName+" "+sampleName+"_*_"+iCut+"_tree.root; rm *mc16*_tree.root; cd -";
        system(hadd.c_str());
      }
    } 
  }
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  std::cout << "Execution time difference = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "[s]" << std::endl;
  std::cout<<std::endl<<std::endl<<" VariablePlotter::execute() done !!!! "<<std::endl<<std::endl;
}
