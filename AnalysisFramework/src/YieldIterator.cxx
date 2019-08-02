#include "YieldIterator.h"
#include "JSONDoc.h"
#include "Controller.h"
#include "ROOTHelper.h"
#include "TROOT.h"

DECLARE_ALGORITHM( YieldIterator , YieldCalculator )

void YieldIterator::execute()
{

	std::cout<<" entering YieldIterator::execute() "<<std::endl;
	std::ofstream fileOut;
	fileOut.open("yields.txt");

	mytest::JSONData& document=Controller::GetDocument();
	
	// let's roll
		
	const std::vector<std::string> mcCampaigns={"mc16a","mc16d","mc16e"};
	//const std::vector<std::string> cutFlows={"Selection"};
        //const std::vector<std::string> cutFlows={"LM_A","LM_B","HM_A","HM_B"};
	std::vector<std::string> cutFlows;
	for (auto is:document.selections.selMap)
	{
		std::cout << " new selection being added to the list "<<is.first<<std::endl;
		cutFlows.push_back(is.first);
	}
	
	std::string logging;
	
	for (auto iSample:document.samples.samples) {
	     mytest::aSample thisSample=document.samples.samples[iSample.first];
	     const std::string sampleName=iSample.first;
	     for (auto iCut: cutFlows){
			std::map<std::string,std::vector<double>,std::less<std::string> >  integrals;
			double xsec_br_eff=0;
			double total_yield=0;

			for (auto iMC: mcCampaigns){
				const std::string mc=iMC;
				logging=sampleName+"_"+mc+"_"+iCut;
				// selection first 
				std::string select=document.selections.selMap[iCut];
				if (sampleName=="data") select=document.selections.dataSel;
				// variable
				double lumi=document.luminosity.lumiMap[iMC];
				
				// data dir
				std::string dataDir=document.directories.dirMap[iMC];
				if (sampleName=="data") dataDir=document.directories.dataDir;
				// file name, this is going to look disgusting
				std::string fileName=thisSample.sampleMap[iMC];
				//////////////// bleah!
				// This part is a place holder until we have all MC. We are duplicating mc16d with the luminosity of mc16d and mc16e!!
				if (fileName=="mc16d.PowhegPy8_NNPDF30_VBFH125.MxAODDetailed.e6636_s3126_r10201_p3665.h024.root")
	   		        dataDir="root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h024/mc16d/Nominal/";
			        if (fileName=="mc16d.aMCnloHwpp_hh_yybb_AF2.MxAODDetailed.e4419_a875_r10201_p3629.h024.root")
			        dataDir="root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h024/mc16d/Nominal/";
				if (fileName=="mc16d.MGPy8_ttgamma_nonallhadronic_AF2.MxAODDetailed.e6155_a875_r10201_p3703.h024.root")
				dataDir="root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h024/mc16d/Nominal/";
				if (fileName=="yy_mc16a.root")
				dataDir="root://eosatlas.cern.ch//eos/atlas/user/a/altaylor/bbgg/h024/";
				if (fileName=="yy_mc16e.root")
				dataDir="root://eosatlas.cern.ch//eos/atlas/user/a/altaylor/bbgg/h024/";
				if (fileName=="15_16_data.root" || fileName=="17_data.root" || fileName=="18_data.root")
                                dataDir="root://eosatlas.cern.ch//eos/atlas/user/a/altaylor/bbgg/h024/";
                                std::cout<<"dataDir ========== "<< dataDir<< std::endl;
                                ////////////////
				std::cout<<"11111111111"<<std::endl;
				TFile* file=ROOTHelper::GetTFile(sampleName,mc,dataDir+fileName);
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
				
				std::cout<<"222222222222"<<std::endl;
	
				int nC=0;
				for(auto iVar : document.variables.varMap){
					if (nC) break;
					nC++;
					std::string var = iVar.second.first;
					std::string varName = iVar.first;
					
					std::string hName=varName+logging;

					std::string hN="sumHisto_"+varName+"_"+sampleName+"_"+iCut;					
					int nbins=(iVar.second).second.nBins;
                               		double lowerBin=(iVar.second).second.lowerBin;
                               		double upperBin=(iVar.second).second.upperBin;
                                       	TH1F *his=new TH1F(hName.c_str(),hName.c_str(),nbins,lowerBin,upperBin);
					std::string vvar=var+" >> "+hName;
					tree->Draw(vvar.c_str(),select.c_str(),"HIST");
					his->Scale(lumi/sum_weights);
					double integ=his->Integral();
					integrals[varName].push_back(integ);
				}
				std::cout<<"333333333333 "<<logging<<std::endl;
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
        		std::cout<<"44444444444444444 "<<logging<<std::endl;
			std::map<std::string,double,std::less<std::string> >  Yield;
			double acceptance_efficiency=0;
			fileOut<< "----------------------------------------- "<<std::endl;
			fileOut<<" sample + cut flow : "<<logging<<std::endl;
                        int nCount=0;
			for (auto ikx:integrals)
			{
				if (nCount) break;
				nCount++;
				std::string vnam=ikx.first;
				for (int i=0;i<ikx.second.size();i++)
					Yield[vnam]+=ikx.second.at(i);
				acceptance_efficiency=Yield[vnam]/total_yield;
				fileOut<<" Yield "<<Yield[vnam]<<" efficiency "<<acceptance_efficiency<<std::endl;
			}
			std::cout<<"555555555555555"<<std::endl;
			Yield.clear();
			integrals.clear();
	    }
	}
	fileOut.close();	
		
}

