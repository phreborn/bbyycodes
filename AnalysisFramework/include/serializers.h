#pragma once

#include <string>
#include <iostream>
#include <nlohmann/json.hpp>
#include <map>

using nlohmann::json;

namespace mytest {
  

        void from_json(const json& j, Dir& p)
        {
                for (auto it = j.begin(); it != j.end(); ++it) {
                    p.dirMap [it.key()]=it.value();
                }

        }
 

        void from_json(const json& j, Var& p)
        {
                if (j.find("myy_var")!=j.end())
                        p.variable=j.at("myy_var").get<std::string>();
        }


        void from_json(const json& j, Sel& p)
        {
                for (auto it = j.begin(); it != j.end(); ++it) {
                    p.selMap [it.key()]=it.value();
                }

        }



        void from_json(const json& j, Lumi& p)
        {
		for (auto it = j.begin(); it != j.end(); ++it) {
		    p.lumiMap [it.key()]=it.value();
		}	
		
		}


        void from_json(const json& j, Bins& p)
        {
                if (j.find("nbins_myy")!=j.end())
                	p.nBins=j.at("nbins_myy").get<int>();
                if (j.find("lbins_myy")!=j.end())
                        p.lowerBin=j.at("lbins_myy").get<double>();
                if (j.find("ubins_myy")!=j.end())
                        p.upperBin=j.at("ubins_myy").get<double>();
        }

        void from_json(const json& j, MCSamples& p)
        {      
                for (auto it = j.begin(); it != j.end(); ++it) {
 		 const json& jjj = it.value();
                 std::cout<< "it.key = " << it.key() << std::endl;
		 aSample x;
 		 if (jjj.find("datafiles")!=jjj.end()) {
		  	 std::cout<< "in data files" << std::endl;
                         const json& jj = jjj.at("datafiles");
 		 	 for (auto ik = jj.begin(); ik != jj.end(); ++ik) {
		 	   x.sampleMap [ik.key()]=ik.value();
                         }
		 }
                 if (jjj.find("histoName")!=jjj.end())
                         x.histoName=jjj.at("histoName").get<std::string>();
			 
		 p.samples[it.key()]=x;
        
               } 

       }


	void to_json(json& j, const Sample& p)
	{
	//	j=json{{"root",p.root},{"file",p.file},{"NLL",p.nll}};
	}
	void from_json(const json& j, Sample& p) 
	{       
		static std::string selection_ref="";
		static std::string variable_ref="";
		static int nBins_ref=p.nBins;
		static int lowerBin_ref=p.lowerBin;
		static int upperBin_ref=p.upperBin;

		bool data1=false,data2=false,mc1=false,mc2=false;

		if (j.find("name")!=j.end()) p.name=(j.at("name").get<std::string>());
		std::cout<<" +++++ p.name = "<<p.name<<std::endl;
                if (j.find("mc16a_fileName")!=j.end())
		{
                    p.file1Name	        =(j.at("mc16a_fileName").get<std::string>());
		    mc1=true;
		}
		if (j.find("mc16d_fileName")!=j.end())
		{
		    p.file2Name	        =(j.at("mc16d_fileName").get<std::string>());
		    mc2=true;
		}
		if (j.find("data_file1Name")!=j.end())
                {
                    p.file1Name         =(j.at("data_file1Name").get<std::string>());
                    data1=true;
                }
                if (j.find("data_file2Name")!=j.end())
                {
                    p.file2Name         =(j.at("data_file2Name").get<std::string>());
                    data2=true;
                }
		if (mc1 && mc2) p.type="MC";
		else if (data1 && data2) p.type="data";
		else if ((mc1||mc2) || (data1||data2))
			std::cout <<" uhm.... there must be some confusion with the data samples!!!!"<<std::endl;
                std::cout<<" +++++ p.file1Name = "<<p.file1Name<<std::endl;
		std::cout<<" +++++ p.file2Name = "<<p.file2Name<<std::endl;
		if (j.find("cut_flow_histo_name")!=j.end()) p.cut_flow_histo_name	=(j.at("cut_flow_histo_name").get<std::string>());
		std::cout<<" +++++ p.cut_flow_histo_name = "<<p.cut_flow_histo_name<<std::endl;
		if (j.find("output_fileName")!=j.end()) p.output_fileName	=(j.at("output_fileName").get<std::string>());
		std::cout<<" +++++ p.output_fileName = "<<p.output_fileName<<std::endl;
		if (j.find("selection")!=j.end())
			selection_ref=j.at("selection").get<std::string>();
		p.selection=selection_ref;
		std::cout<<" +++++ p.selection = "<<p.selection<<std::endl;
		if (j.find("variable")!=j.end())
                        variable_ref=j.at("variable").get<std::string>();
                p.variable=variable_ref;
                std::cout<<" +++++ p.variable = "<<p.variable<<std::endl;
 		if (j.find("nBins")!=j.end())
			nBins_ref=j.at("nBins").get<int>();
		p.nBins=nBins_ref;
		std::cout<<" +++++ p.nBins = "<<p.nBins<<std::endl;
		if (j.find("lowerBin")!=j.end())
                        lowerBin_ref=j.at("lowerBin").get<double>();
                p.lowerBin=lowerBin_ref;
                std::cout<<" +++++ p.lowerBin = "<<p.lowerBin<<std::endl;
		if (j.find("upperBin")!=j.end())
                        upperBin_ref=j.at("upperBin").get<double>();
                p.upperBin=upperBin_ref;
                std::cout<<" +++++ p.upperBin = "<<p.upperBin<<std::endl;
	}

}
