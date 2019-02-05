#include "YieldIterator.h"
#include "JSONDoc.h"
#include "Controller.h"

TFile* YieldIterator::GetTFile(std::string sample,std::string mcset, std::string fileName)
{
	static std::map<std::string,TFile*,std::less<std::string> > tfileMap;
	std::string temp=sample+"_"+mcset;
	if (tfileMap.find(temp) != tfileMap.end())
		return tfileMap[temp];
	else
	{
		TFile* tf=new TFile(fileName.c_str());
		tfileMap[temp]=tf;
		return tf;
	}
}

void YieldIterator::IterateModel(json& jj)
{

	std::ofstream fileOut;
	fileOut.open("yields.txt");
	
	// let's roll
		
	const std::vector<std::string> mcCampaigns={"mc16a","mc16d","mc16e"};
	const std::vector<std::string> cutFlows={"LM_A","LM_B","HM_A","HM_B"};
	
	mytest::JSONData& document=Controller::GetDocument();
		
	std::string logging;
		
	for (auto iSample:document.samples.samples) {
	     mytest::aSample thisSample=document.samples.samples[iSample.first];
	     const std::string sampleName=iSample.first;
	     for (auto iCut: cutFlows){
	          std::vector<double> integrals;
		  double xsec_br_eff=0;
		  double total_yield=0;
		  
		  TH1F *sumHisto=new TH1F(("sumHisto_"+sampleName+"_"+iCut).c_str(),("sumHisto_"+sampleName+"_"+iCut).c_str(),document.bins.nBins,document.bins.lowerBin,document.bins.upperBin);
		  
		  
		  
		  for (auto iMC: mcCampaigns){
		        const std::string mc=iMC;
		        logging=sampleName+"_"+mc+"_"+iCut;
		        // selection first 
		        std::string select=document.selections.selMap[iCut];
		        // variable
		        std::string var = document.variables.variable;
		        // data dir
		        std::string dataDir=document.directories.dirMap[iMC];
		        // file name, this is going to look disgusting
			std::string fileName=thisSample.sampleMap[iMC];
			//////////////// bleah!
			if (fileName=="mc16d.PowhegPy8_NNPDF30_VBFH125.MxAODDetailed.e6636_s3126_r10201_p3665.h024.root")
			   dataDir="root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h024/mc16d/Nominal/";
			if (fileName=="mc16d.aMCnloHwpp_hh_yybb_AF2.MxAODDetailed.e4419_a875_r10201_p3629.h024.root")
			   dataDir="root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h024/mc16d/Nominal/";
			////////////////
			TFile* file=GetTFile(sampleName,mc,dataDir+fileName);
			std::string histoName=thisSample.histoName;
			TH1* histo=dynamic_cast<TH1*>(file->Get(histoName.c_str()));
			double sum1=0,sum2=0,sum3=0;
			if (histo) {
				sum1=histo->GetBinContent(1);
				sum2=histo->GetBinContent(2);
				sum3=histo->GetBinContent(3);
			}
			double sum_weights=(sum1/sum2)*sum3;
			TTree* tree=(TTree*)file->Get("CollectionTree");
			std::string hName="h_myy_"+logging;
			TH1F* his=new TH1F(hName.c_str(),hName.c_str(),document.bins.nBins,document.bins.lowerBin,document.bins.upperBin);
			std::string vvar=var+" >> "+hName;
			tree->Draw(vvar.c_str(),select.c_str());
			double lumi=document.luminosity.lumiMap[iMC];
			his->Scale(lumi/sum_weights);
			sumHisto->Add(his);
			integrals.push_back(his->Integral());
			//doing it only for MC16a - why???
			if (!xsec_br_eff){
				tree->Draw("HGamEventInfoAuxDyn.crossSectionBRfilterEff");
				double *xsec_br_eff_array=tree->GetVal(0);
				xsec_br_eff = xsec_br_eff_array[0];
			}
			total_yield+= lumi*xsec_br_eff;
		   }
        
                   DIR* dir = opendir("plots");
		   if (!dir) const int dir_err = mkdir("plots", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);                   
                   TFile outfile (("plots/"+sampleName+"_"+iCut+".root").c_str(),"recreate");
		   sumHisto->Write();
    	  	   outfile.ls();
    		   outfile.Close();
		   sumHisto=0;
		   
		   double Yield=0;
		   double acceptance_efficiency=0;
		   for (int i=0;i<integrals.size();i++)
			Yield+=integrals[i];
		   integrals.clear();
		   acceptance_efficiency=Yield/total_yield;
		   fileOut<< "----------------------------------------- "<<std::endl;
		   fileOut<<" sample + cut flow : "<<logging<<std::endl;
		   fileOut<<"Yield = "<<Yield<<" efficiency "<<acceptance_efficiency<<std::endl;
	     }
	}
		
	fileOut.close();	
		
}

