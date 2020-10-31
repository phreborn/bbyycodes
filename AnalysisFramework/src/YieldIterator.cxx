#include "YieldIterator.h"
#include "JSONDoc.h"
#include "Controller.h"
#include "ROOTHelper.h"
#include "TROOT.h"

DECLARE_ALGORITHM( YieldIterator , YieldCalculator )

void YieldIterator::execute()
{

  std::cout<<" Entering YieldIterator::execute() "<<std::endl;

  // Fetch the JSON 
  mytest::JSONData& document=Controller::GetDocument();

  //Specify name for yields output
  std::string file_name = "yields";
  for (auto is:document.name.nameMap)
    {
      file_name = is.second;
    }

  std::ofstream fileOut;
  std::ofstream jsonOut;
  std::cout << "Yield fila name: " << file_name << std::endl;
  fileOut.open(file_name+".txt");                                                                                                                           
  jsonOut.open(file_name+".js");                                                                                                                            
  jsonOut<<"{"<<std::endl;

  // First extract selections from the JSON
  // Full parsing is handled by the serializer.h
  std::vector<std::string> cutFlows={};
  for (auto is:document.selections.selMap)
  {
    std::cout << " New selection being added to the list "<<is.first<<std::endl;
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

  std::string sampleCommaIfInternal =",";
  //for (auto iSample:document.samples.samples) {
  for (auto iSample=document.samples.samples.begin();iSample!=document.samples.samples.end();iSample++){ //Remaking this into iterator loop to be able to construct the json
    const std::string sampleName=iSample->first;
    if (std::next(iSample) == document.samples.samples.end()){ //Trick to get internal commas on correct positions
      sampleCommaIfInternal = "";
    }
    jsonOut<<"\""<<(sampleName)<<"\":{"<<std::endl;
    mytest::aSample thisSample=document.samples.samples[iSample->first];
    std::string cutCommaIfInternal = ",";
    for (auto iCut=cutFlows.begin();iCut!=cutFlows.end();++iCut){ //Remaking this into iterator loop to be able to construct the json
      if (std::next(iCut) == cutFlows.end()){
	cutCommaIfInternal = "";
      }
      //for (auto iCut: cutFlows){
      int total_counts = 0;
      std::map<std::string,std::vector<double>,std::less<std::string> >  integrals;
      std::map<std::string,std::vector<double>,std::less<std::string> >  errors;
      double xsec_br_eff=0;
      double total_yield=0;

      // Adding an additional truth-matching feature, which we only need when
      // running on the yy samples to get the yycj, yybj, yyjj separation
      std::string truthMatch = "";        
      if (sampleName == "yybj") truthMatch = " && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.HadronConeExclTruthLabelID[0]==5";
      if (sampleName == "yycj") truthMatch = " && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.HadronConeExclTruthLabelID[0]==4";
      if (sampleName == "yyjj") truthMatch = " && (HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.HadronConeExclTruthLabelID[0]!=4 && HGamAntiKt4PFlowCustomVtxHggJetsAuxDyn.HadronConeExclTruthLabelID[0]!=5)";
      for (auto iMC: mcCampaigns){
        const std::string mc=iMC;
        logging=sampleName+"_"+mc+"_"+(*iCut);
        
        // Specify the actual selection string

        std::string select=document.selections.selMap[(*iCut)];
	// Specify weight
	std::string weight = document.selections.weight;
	if(select.find("HGamEventInfoAuxDyn.isPassed")!=std::string::npos){
	    select = select.std::string::replace(select.find("HGamEventInfoAuxDyn.isPassed"), std::string("HGamEventInfoAuxDyn.isPassed").length(), "HGamEventInfoAuxDyn.isPassed"+truthMatch);
	}
	std::string weighted_selection="("+select+")*("+weight+")";
        // Get luminosity from the MC information
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
        // First, determine the sum of weights from the MxAOD object
        double sum_weights=(sum1/sum2)*sum3; //AllEvent*(NxAOD/DxAOD) -- for signal samples it does not matter since the number of events in the DxAOD is the same as the number in MxAOD, but it does matter for backgrounds, which have skimming applied at the DxAOD level 
        TTree* tree=(TTree*)file->Get("CollectionTree");
        // Now loop over the variables specified in the JSON
        int nC=0;
        for(auto iVar : document.variables.varMap){
          if (nC) break;
          nC++;
          std::string var = iVar.second.first;
          std::string varName = iVar.first;
          std::string hName=varName+logging;
          std::string hN="sumHisto_"+varName+"_"+sampleName+"_"+(*iCut);					
         
	  
          int nbins=(iVar.second).second.nBins;
          double lowerBin=(iVar.second).second.lowerBin;
          double upperBin=(iVar.second).second.upperBin;
          TH1F *his=new TH1F(hName.c_str(),hName.c_str(),nbins,lowerBin,upperBin);
	  std::cout<<hName.c_str()<<nbins<<" "<<lowerBin<<" "<<upperBin<<std::endl;
          std::string vvar=var+" >> "+hName;
          // Draw histogram and apply luminosity scaling
          tree->Draw(vvar.c_str(),weighted_selection.c_str(),"HIST");

          //his->Scale(lumi/sum_weights);
          float theXStimesBR = 1.0;
          // Have a specific XStimesBR if we are running on a resonant signal
         if (sampleName.find("toHH") != std::string::npos) {
           std::string sampleNameShort;
           sampleNameShort = sampleName;
           int pos = sampleNameShort.find("toHH")+4; // not beautiful, should be changed
           sampleNameShort.erase(pos,-1); //erase everything that comes after "toHH". This allows to attach strings in the names of the resonant samples in the json files, which might be useful for making the validation plots, and at the same time keep the same mapping for the XS.
           theXStimesBR = XStimesBR[sampleNameShort];
          }

          his->Scale(lumi*theXStimesBR/sum_weights);
	  
	  double e;
	  double integ = his->IntegralAndError(0,his->GetNbinsX(),e);
	  total_counts+=tree->GetEntries(select.c_str());
	       
	  integrals[varName].push_back(integ);
	  errors[varName].push_back(e);
        }
        if (sampleName=="data") continue;
        //doing it only for MC16a - why???
        if (!xsec_br_eff)
        {
          tree->Draw("HGamEventInfoAuxDyn.crossSectionBRfilterEff");
          double *xsec_br_eff_array=tree->GetVal(0);
          xsec_br_eff = xsec_br_eff_array[0];
        }
        total_yield+= lumi*xsec_br_eff;
      }
      // Finally, get and store the yields and efficiencies
      std::map<std::string,double,std::less<std::string> >  Yield;
      std::map<std::string,double,std::less<std::string> >  Unc;
      double acceptance_efficiency=0;
      fileOut<< "----------------------------------------- "<<std::endl;
      fileOut<<" Sample + cut flow : "<<logging<<std::endl;
      fileOut<<" Total counts : "<< total_counts<<std::endl;
      
      int nCount = 0;
      for (auto ikx:integrals)
	{
	  if (nCount) break;
	  nCount++;
	  std::string vnam=ikx.first;
	  for (int i=0;i<ikx.second.size();i++){
	    Yield[vnam]+=ikx.second.at(i);
	    Unc[vnam]+=pow(errors[vnam].at(i),2);
	  }
	  Unc[vnam] = sqrt(Unc[vnam]);
        acceptance_efficiency=Yield[vnam]/total_yield;
        fileOut <<" Yield "<<Yield[vnam]<<" +/- "<< Unc[vnam] <<" efficiency "<<acceptance_efficiency<<std::endl;
	jsonOut <<"\""<<(*iCut)<<"\":["<<Yield[vnam]<<","<<Unc[vnam]<<"]"<<cutCommaIfInternal<<std::endl;
	}
      Yield.clear();
      integrals.clear();
      errors.clear();
    }
    jsonOut<<"}"<<sampleCommaIfInternal<<std::endl;
  }
  fileOut.close();
  jsonOut<<"}"<<std::endl;
  jsonOut.close();
}

