#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include <map>

using nlohmann::json;

//typedef std::map< std::string , std::pair<double,double> , std::less<std::string> > fits;

namespace mytest {
  

        struct Dir {
               std::map <std::string, std::string, std::less<std::string> > dirMap;
        };

 
        struct Var {
               std::string variable; 
        };

        struct Sel {
               std::map <std::string, std::string, std::less<std::string> > selMap;
        };


        struct Lumi {
               std::map <std::string, double, std::less<std::string> > lumiMap;
        };

        struct Bins {
 	       int nBins=55;
               double lowerBin=105;
               double upperBin=160;	
        };

	struct aSample {
	       std::map <std::string, std::string, std::less<std::string> > sampleMap;
	       std::string histoName;
	};

        struct MCSamples {
       
               std::map <std::string,aSample, std::less<std::string> > samples;

        };


        struct JSONData {
                Dir directories;
                Var variables;
                Sel selections;
                Lumi luminosity;
                Bins bins;
                MCSamples samples;
        };
 

	struct Sample {
		std::string name;
		std::string file1Name;
		std::string file2Name;
		std::string cut_flow_histo_name;
		std::string output_fileName;
		std::string selection;
		std::string variable;

		int nBins=22;
		double lowerBin=105;
		double upperBin=160;

		std::string type="dummy";
	};

}

//std::map <std::string , mytest::Sample, std::less<std::string> > Samples;

