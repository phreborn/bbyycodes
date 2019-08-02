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
	const std::vector<std::string> cutFlows={"Selection"};
	
	mytest::JSONData& document=Controller::GetDocument();
		
	std::string logging;
	
	std::map<std::string,TH1F*,std::less<std::string> > sumhistoMap;
		
	for (auto iSample:document.samples.samples) {
	     mytest::aSample thisSample=document.samples.samples[iSample.first];
	     const std::string sampleName=iSample.first;
	     for (auto iCut: cutFlows){
			std::vector<double> integrals;
			double xsec_br_eff=0;
			double total_yield=0;
		 
			for (auto ikk:document.variables.varMap)
			{
				std::string variableName=ikk.first;
				std::string variableValue=(ikk.second).first;
				int nbins=(ikk.second).second.nBins;
				double lowerBin=(ikk.second).second.lowerBin;
				double upperBin=(ikk.second).second.upperBin;
				std::string histoName="sumHisto_"+variableName+"_"+sampleName+"_"+iCut;
				TH1F *sumHisto==new TH1F(histoName.c_str(),histoName.c_str(),nbins,lowerBin,upperBin);
				sumhistoMap[histoName]=sumHisto;
			}

		  
			for (auto iMC: mcCampaigns){
				const std::string mc=iMC;
				logging=sampleName+"_"+mc+"_"+iCut;
				// selection first 
				std::string select=document.selections.selMap[iCut];
				// variable

				for(auto iVar : document.variables.varMap){
					std::string var = iVar.second;
					std::string varName = iVar.first;

					
					// data dir
					std::string dataDir=document.directories.dirMap[iMC];
					// file name, this is going to look disgusting
					std::string fileName=thisSample.sampleMap[iMC];
					//////////////// bleah!
					// This part is a place holder until we have all MC. We are duplicating mc16d with the luminosity of mc16d and mc16e!!
					if (fileName=="mc16d.MGPy8_ttgamma_nonallhadronic_AF2.MxAODDetailed.e6155_a875_r10201_p3703.h024.root")
					dataDir="root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/phys-higgs/HSG1/MxAOD/h024/mc16d/Nominal/";
					if (fileName=="yy_mc16a.root")
					dataDir="root://eosatlas.cern.ch//eos/atlas/user/a/altaylor/bbgg/h024/";
					if (fileName=="yy_mc16d.root")
					dataDir="root://eosatlas.cern.ch//eos/atlas/user/a/altaylor/bbgg/h024/";
					if (fileName=="yy_mc16e.root")
					dataDir="root://eosatlas.cern.ch//eos/atlas/user/a/altaylor/bbgg/h024/";
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
					std::string hName=varName+logging;

					

					if(varName == "m_yy_var"){

						TH1F* his=new TH1F(hName.c_str(),hName.c_str(),55,105,160);

						std::string vvar=var+" >> "+hName;
						tree->Draw(vvar.c_str(),select.c_str(),"HIST");
						double lumi=document.luminosity.lumiMap[iMC];
						his->Scale(lumi/sum_weights);
						
						sumHisto_m_yy->Add(his);

						integrals.push_back(his->Integral());
						//doing it only for MC16a - why???
						if (!xsec_br_eff){
							tree->Draw("HGamEventInfoAuxDyn.crossSectionBRfilterEff");
							double *xsec_br_eff_array=tree->GetVal(0);
							xsec_br_eff = xsec_br_eff_array[0];
						}
						total_yield+= lumi*xsec_br_eff;

					}

					if(varName == "m_jj_var"){

						TH1F* his=new TH1F(hName.c_str(),hName.c_str(),24,60,180);

						std::string vvar=var+" >> "+hName;
						tree->Draw(vvar.c_str(),select.c_str(),"HIST");
						double lumi=document.luminosity.lumiMap[iMC];
						his->Scale(lumi/sum_weights);
						
						sumHisto_m_jj->Add(his);

						integrals.push_back(his->Integral());
						//doing it only for MC16a - why???
						if (!xsec_br_eff){
							tree->Draw("HGamEventInfoAuxDyn.crossSectionBRfilterEff");
							double *xsec_br_eff_array=tree->GetVal(0);
							xsec_br_eff = xsec_br_eff_array[0];
						}
						total_yield+= lumi*xsec_br_eff;

					}

					if(varName == "m_yyjj_tilde_var"){

						TH1F* his=new TH1F(hName.c_str(),hName.c_str(),30,250,1000);

						std::string vvar=var+" >> "+hName;
						tree->Draw(vvar.c_str(),select.c_str(),"HIST");
						double lumi=document.luminosity.lumiMap[iMC];
						his->Scale(lumi/sum_weights);
						
						sumHisto_m_yyjj_tilde->Add(his);

						integrals.push_back(his->Integral());
						//doing it only for MC16a - why???
						if (!xsec_br_eff){
							tree->Draw("HGamEventInfoAuxDyn.crossSectionBRfilterEff");
							double *xsec_br_eff_array=tree->GetVal(0);
							xsec_br_eff = xsec_br_eff_array[0];
						}
						total_yield+= lumi*xsec_br_eff;

					}

					if(varName == "m_yyjj_tilde_HM_var"){

						TH1F* his=new TH1F(hName.c_str(),hName.c_str(),26,350,1000);

						std::string vvar=var+" >> "+hName;
						tree->Draw(vvar.c_str(),select.c_str(),"HIST");
						double lumi=document.luminosity.lumiMap[iMC];
						his->Scale(lumi/sum_weights);
						
						sumHisto_m_yyjj_tilde_HM->Add(his);

						integrals.push_back(his->Integral());
						//doing it only for MC16a - why???
						if (!xsec_br_eff){
							tree->Draw("HGamEventInfoAuxDyn.crossSectionBRfilterEff");
							double *xsec_br_eff_array=tree->GetVal(0);
							xsec_br_eff = xsec_br_eff_array[0];
						}
						total_yield+= lumi*xsec_br_eff;

					}

					if(varName == "deltaR_yy_var"){

						TH1F* his=new TH1F(hName.c_str(),hName.c_str(),25,0,5);

						std::string vvar=var+" >> "+hName;
						tree->Draw(vvar.c_str(),select.c_str(),"HIST");
						double lumi=document.luminosity.lumiMap[iMC];
						his->Scale(lumi/sum_weights);
						
						sumHisto_deltaR_yy->Add(his);

						integrals.push_back(his->Integral());
						//doing it only for MC16a - why???
						if (!xsec_br_eff){
							tree->Draw("HGamEventInfoAuxDyn.crossSectionBRfilterEff");
							double *xsec_br_eff_array=tree->GetVal(0);
							xsec_br_eff = xsec_br_eff_array[0];
						}
						total_yield+= lumi*xsec_br_eff;

					}

					if(varName == "deltaR_jj_var"){

						TH1F* his=new TH1F(hName.c_str(),hName.c_str(),25,0,5);

						std::string vvar=var+" >> "+hName;
						tree->Draw(vvar.c_str(),select.c_str(),"HIST");
						double lumi=document.luminosity.lumiMap[iMC];
						his->Scale(lumi/sum_weights);
						
						sumHisto_deltaR_jj->Add(his);

						integrals.push_back(his->Integral());
						//doing it only for MC16a - why???
						if (!xsec_br_eff){
							tree->Draw("HGamEventInfoAuxDyn.crossSectionBRfilterEff");
							double *xsec_br_eff_array=tree->GetVal(0);
							xsec_br_eff = xsec_br_eff_array[0];
						}
						total_yield+= lumi*xsec_br_eff;

					}

					if(varName == "deltaR_yyjj_var"){

						TH1F* his=new TH1F(hName.c_str(),hName.c_str(),30,0,6);

						std::string vvar=var+" >> "+hName;
						tree->Draw(vvar.c_str(),select.c_str(),"HIST");
						double lumi=document.luminosity.lumiMap[iMC];
						his->Scale(lumi/sum_weights);
						
						sumHisto_deltaR_yyjj->Add(his);

						integrals.push_back(his->Integral());
						//doing it only for MC16a - why???
						if (!xsec_br_eff){
							tree->Draw("HGamEventInfoAuxDyn.crossSectionBRfilterEff");
							double *xsec_br_eff_array=tree->GetVal(0);
							xsec_br_eff = xsec_br_eff_array[0];
						}
						total_yield+= lumi*xsec_br_eff;

					}

					if(varName == "MET_var"){

						TH1F* his=new TH1F(hName.c_str(),hName.c_str(),15,0,150);

						std::string vvar=var+" >> "+hName;
						tree->Draw(vvar.c_str(),select.c_str(),"HIST");
						double lumi=document.luminosity.lumiMap[iMC];
						his->Scale(lumi/sum_weights);
						
						sumHisto_MET->Add(his);

						integrals.push_back(his->Integral());
						//doing it only for MC16a - why???
						if (!xsec_br_eff){
							tree->Draw("HGamEventInfoAuxDyn.crossSectionBRfilterEff");
							double *xsec_br_eff_array=tree->GetVal(0);
							xsec_br_eff = xsec_br_eff_array[0];
						}
						total_yield+= lumi*xsec_br_eff;

					}

					if(varName == "N_j_var"){

						TH1F* his=new TH1F(hName.c_str(),hName.c_str(),8,0,8);

						std::string vvar=var+" >> "+hName;
						tree->Draw(vvar.c_str(),select.c_str(),"HIST");
						double lumi=document.luminosity.lumiMap[iMC];
						his->Scale(lumi/sum_weights);
						
						sumHisto_N_j->Add(his);

						integrals.push_back(his->Integral());
						//doing it only for MC16a - why???
						if (!xsec_br_eff){
							tree->Draw("HGamEventInfoAuxDyn.crossSectionBRfilterEff");
							double *xsec_br_eff_array=tree->GetVal(0);
							xsec_br_eff = xsec_br_eff_array[0];
						}
						total_yield+= lumi*xsec_br_eff;

					}

					if(varName == "N_j_central_var"){

						TH1F* his=new TH1F(hName.c_str(),hName.c_str(),8,0,8);

						std::string vvar=var+" >> "+hName;
						tree->Draw(vvar.c_str(),select.c_str(),"HIST");
						double lumi=document.luminosity.lumiMap[iMC];
						his->Scale(lumi/sum_weights);
						
						sumHisto_N_j_central->Add(his);

						integrals.push_back(his->Integral());
						//doing it only for MC16a - why???
						if (!xsec_br_eff){
							tree->Draw("HGamEventInfoAuxDyn.crossSectionBRfilterEff");
							double *xsec_br_eff_array=tree->GetVal(0);
							xsec_br_eff = xsec_br_eff_array[0];
						}
						total_yield+= lumi*xsec_br_eff;

					}

					if(varName == "btag_score_var"){

						TH1F* his=new TH1F(hName.c_str(),hName.c_str(),8,0,8);

						std::string vvar=var+" >> "+hName;
						tree->Draw(vvar.c_str(),select.c_str(),"HIST");
						double lumi=document.luminosity.lumiMap[iMC];
						his->Scale(lumi/sum_weights);
						
						sumHisto_btag_score->Add(his);

						integrals.push_back(his->Integral());
						//doing it only for MC16a - why???
						if (!xsec_br_eff){
							tree->Draw("HGamEventInfoAuxDyn.crossSectionBRfilterEff");
							double *xsec_br_eff_array=tree->GetVal(0);
							xsec_br_eff = xsec_br_eff_array[0];
						}
						total_yield+= lumi*xsec_br_eff;

					}

				}
			}
        
			DIR* dir = opendir("plots");
			if (!dir) const int dir_err = mkdir("plots", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);                   
				TFile outfile (("plots/"+sampleName+"_"+iCut+".root").c_str(),"recreate");
			sumHisto_m_yy->Write();
			sumHisto_m_jj->Write();
			sumHisto_m_yyjj_tilde->Write();
			sumHisto_m_yyjj_tilde_HM->Write();
			sumHisto_deltaR_yy->Write();
			sumHisto_deltaR_jj->Write();
			sumHisto_deltaR_yyjj->Write();
			sumHisto_MET->Write();
			sumHisto_N_j->Write();
			sumHisto_N_j_central->Write();
			sumHisto_btag_score->Write();
				outfile.ls();
				outfile.Close();
			sumHisto_m_yy=0;
			sumHisto_m_jj=0;
			sumHisto_m_yyjj_tilde=0;
			sumHisto_m_yyjj_tilde_HM=0;
			sumHisto_deltaR_yy=0;
			sumHisto_deltaR_jj=0;
			sumHisto_deltaR_yyjj=0;
			sumHisto_MET=0;
			sumHisto_N_j=0;
			sumHisto_N_j_central=0;
			sumHisto_btag_score=0;

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

