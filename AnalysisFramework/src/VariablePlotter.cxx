#include "VariablePlotter.h"
#include "JSONDoc.h"
#include "Controller.h"
#include "ROOTHelper.h"
#include "TROOT.h"
#include <memory>
#include <chrono>

DECLARE_ALGORITHM( VariablePlotter , VariablePlotter )


void ReplaceAll(std::string &str, const std::string& from, const std::string& to)
{

   size_t start_pos = 0;
   while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
   }
}

bool hasEnding (std::string const &fullString, std::string const &ending) {
  if (fullString.length() >= ending.length()) {
    return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
  } else {
    return false;
  }
}



void VariablePlotter::execute()
{
  
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  
  // Fetch the JSON 
  mytest::JSONData& document=Controller::GetDocument();
  

  bool dumpNtuple = false; //ntuple dumper is off by default, add a line in the JSON file if you want to activate it

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
  // Add a map for the resonant signal x-section * BR
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

  //variables you want to save in the flat ntuple - this could be generalised and read in from the json
  std::vector< std::string > treeList = {"SF", "weight", "total_weight", "m_yy", "m_jj"};

  std::string truthMatch = "";
 
  int MC_counter = 0;

  TFile *outfile;
  std::vector< std::string > outName;
  std::vector< std::string > outNameMerge;
  ROOT::RDF::RSnapshotOptions opts;
  //opts.fLazy = true;  
  opts.fMode="RECREATE";
  using SnapRet_t = ROOT::RDF::RResultPtr<ROOT::RDF::RInterface<ROOT::Detail::RDF::RLoopManager>>;

  DIR* dir =  opendir("plots");
  if (!dir) const int dir_err = mkdir("plots", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

  for (auto iSample:document.samples.samples) {
    mytest::aSample thisSample=document.samples.samples[iSample.first];
    const std::string sampleName=iSample.first;


    for (auto iCut: cutFlows){

        for (auto ikk:document.variables.varMap) {
          std::string variableName=ikk.first;
          std::string variableValue=(ikk.second).first;
          int nbins=(ikk.second).second.nBins;
          double lowerBin=(ikk.second).second.lowerBin;
          double upperBin=(ikk.second).second.upperBin;
          std::string his="sumHisto_"+variableName+"_"+iCut;
          TH1F *sumHisto=new TH1F(his.c_str(),his.c_str(),nbins,lowerBin,upperBin);
          std::cout<< "his = " << his << std::endl;
          sumhistoMap[his]=sumHisto;
        }
   }

    
    for (auto iMC: mcCampaigns){
      const std::string mc=iMC;
      MC_counter++;
      for (auto iCut: cutFlows){
        outfile = new TFile(("plots/"+sampleName+"_"+iCut+".root").c_str(),"RECREATE");
  
        std::cout<< "in CUT FLOWS" << std::endl;
 
        // Adding an additional truth-matching feature, which we only need when
        // running on the yy samples to get the yycj, yybj, yyjj separation
        //std::string truthMatch = "";        
        if (sampleName == "yybj") truthMatch = " && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.HadronConeExclTruthLabelID[0]==5";
        if (sampleName == "yycj") truthMatch = " && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.HadronConeExclTruthLabelID[0]==4";
        if (sampleName == "yyjj") truthMatch = " && (HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.HadronConeExclTruthLabelID[0]!=4 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.HadronConeExclTruthLabelID[0]!=5)";

        // Have a specific XStimesBR if we are running on a resonant signal
        if (sampleName.find("toHH") != std::string::npos) {
         std::string sampleNameShort; 
         sampleNameShort = sampleName;
         int pos = sampleNameShort.find("toHH")+4; // not beautiful, should be changed
         sampleNameShort.erase(pos,-1); //erase everything that comes after "toHH". This allows to attach strings in the names of the resonant samples in the json files, which might be useful for making the validation plots, and at the same time keep the same mapping for the XS.
         theXStimesBR = XStimesBR[sampleNameShort];
        }
        
        logging=sampleName+"_"+mc+"_"+iCut;

        // Pick up the selections for each of the different categories
        std::string select=document.selections.selMap[iCut];
        select = select.std::string::replace(select.find("HGamEventInfoAuxDyn.isPassed"), std::string("HGamEventInfoAuxDyn.isPassed").length(), "HGamEventInfoAuxDyn.isPassed"+truthMatch);
        if (sampleName=="data") select=document.selections.dataSel;
        // Below removed to now
        //if (document.selections.weight.empty()) select+="*"+document.selections.weight;

        // Specify weight
        std::string weight = document.selections.weight;
        std::string weighted_selection="("+select+")*("+weight+")";

        // Pick up the luminosity 
        double lumi=document.luminosity.lumiMap[iMC];
        
        //Decide if you want to dump the ntuple
        dumpNtuple=document.dumper.dumperMap[iMC];

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
        double sum_weights=(sum1/sum2)*sum3; //AllEvents*(NxAOD/DxAOD) -- for signal samples it does not matter since the number of events in the DxAOD is the same as the number in MxAOD, but it does matter for backgrounds, which have skimming applied at the DxAOD level 
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
          std::cout << "Drawing with selection: " << select.c_str() << " and weight: " << weight.c_str() << " and weighted selection " << weighted_selection.c_str() << std::endl;
          //tree->Draw(vvar.c_str(),select.c_str(),"HIST");
          tree->Draw(vvar.c_str(),weighted_selection.c_str(),"HIST");
          //tree->Draw(vvar.c_str(),"","HIST");
	  //auto his = df_filter.Histo1D({hName.c_str(),hName.c_str(),nbins,lowerBin,upperBin},var.c_str());
          //std::cout << "HIST ENTRIES ===== " << his->GetEntries() << std::endl;
	  his->Scale(lumi*theXStimesBR/sum_weights);
          //std::cout<< "Scale by = "<< lumi*theXStimesBR/sum_weights << std::endl;
          //sumhistoMap[hN]->Add(his.GetPtr());
          //std::cout<< "Before adding histo =====, hn=" << hN << ", his name "<< his.get()->GetName() << std::endl;
          //std::cout<< "sumhistoMap: " <<  sumhistoMap[hN] <<std::endl;
	  sumhistoMap[hN]->Add(his.get());
          //std::cout<< "added histo =====" << std::endl;
          //std::cout<< "VAR = " << var << ",     VAR NAME = " << varName << ", iMC = " << iMC << std::endl;
        }//iVar
	
	if (dumpNtuple) {
     
          std::cout <<"In DUMP NTUPLE" <<std::endl;
          
	  ROOT::RDataFrame df(*tree);
          
          std::string select_clean;
          select_clean = select; 
          ReplaceAll(select_clean,"@","");
             
	  auto df_filter = df.Filter(select_clean);
	  //std::cout <<  "DF ENTRIES ===== " << *(df_filter.Count()) << std::endl;
	  double df_SF = lumi*theXStimesBR/sum_weights;
          auto df_out = df_filter.Define("SF", std::to_string(df_SF));
          ROOT::RDF::RNode df_with_defines(df_out);  
          for(auto iVar : document.variables.varMap) {
	    std::string var = iVar.second.first;
            std::string varName = iVar.first;
            for (auto j : treeList) {
              if ( varName == j ) {
		//std::cout<< "In dump ntuple, varName =======" << varName << ", var ======" << var << std::endl;
		df_with_defines = df_with_defines.Define(varName, var);
                if (j == "weight") {
                 auto df_total_weight = std::to_string(df_SF) + "*" + var;
                 df_with_defines = df_with_defines.Define("total_weight", df_total_weight);
		}
                //std::cout<< "Print after custom Define, I have just added variable " << varName <<std::endl;   
              }
            }
          }
	  
          for (auto j : treeList) {
            std::cout<< "print treeList:" << j <<std::endl;
          } 
	  df_with_defines.Snapshot(tree->GetName(),"plots/"+sampleName+"_"+mc+"_"+iCut+"_tree.root",treeList, opts);
          std::cout<< "I have just created a snapshot for " << "plots/"+sampleName+"_"+mc+"_"+iCut+"_tree.root" <<  std::endl;
        
          if (MC_counter == 1) { 
            outName.push_back(sampleName+"_"+iCut+"_tree.root");
            outNameMerge.push_back(sampleName+"_*_"+iCut+"_tree.root");
          }
	}
        outfile->cd();
        //std::cout<< "Before Loop to write histos  ===== " << std::endl;
        for (auto iy:sumhistoMap){
          //std::cout<< "In Loop to write histos  ===== " << std::endl;
	  if (hasEnding(iy.first,iCut))  // this checks if the seletion string ends with iCut - if you want to add variations of a certain selection make sure the final part if unique!
	    iy.second->Write();
          //std::cout<< "check ===== " << iy.first << " " << hasEnding(iy.first,iCut) <<std::endl;
        }
	outfile->ls();
        outfile->Close();
      }//CutFlows
    } // MCCampaigns
    if (dumpNtuple) { //merge trees per MC campaign
       for (int i=0; i<outName.size(); i++) {
         //std::cout<< "In loop for hadd  ===== " << std::endl;
         //std::cout<< "Before Merging  ===== " << std::endl;
         //std::cout<< "=======THIS IS OUTNAME: " << outName.at(i) << ", and this is OUTNAMEMERGE: " << outNameMerge.at(i) << std::endl;
         std::string hadd = "hadd -f ./plots/"+outName.at(i)+" ./plots/"+outNameMerge.at(i);
         std::cout<< "I am about to execute this:" << hadd << std::endl;
         system(hadd.c_str());
       }
       system("rm ./plots/*mc16*_tree.root");    
     } 
   
    outName.clear();
    outNameMerge.clear();
    MC_counter = 0; 
    //std::cout<< "Before clear map ===== " << std::endl;
    sumhistoMap.clear();
    //std::cout<< "After clear map ===== " << std::endl;

  }//samples
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  std::cout << "Execution time difference = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "[s]" << std::endl;
  std::cout<<std::endl<<std::endl<<" VariablePlotter::execute() done !!!! "<<std::endl<<std::endl;
}
