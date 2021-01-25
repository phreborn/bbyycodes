#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include <map>
#include <vector>

using nlohmann::json;

//typedef std::map< std::string , std::pair<double,double> , std::less<std::string> > fits;

namespace mytest {


  struct Sequences {
    std::vector<std::string> items;
  };

  struct Bins {
    int nBins=55;
    double lowerBin=105;
    double upperBin=160;
  };

  struct Dir {
    std::string dataDir="root://eosatlas.cern.ch///eos/atlas/atlascerngroupdisk/phys-hdbs/diHiggs/yybb/skimmed_samples_h025_diphotonpreselection//";
    std::map <std::string, std::string, std::less<std::string> > dirMap;
  };


  struct Var {
    std::map <std::string, std::pair<std::string,Bins>, std::less<std::string> > varMap; 
  };

  struct Sel {
    std::map <std::string, std::string, std::less<std::string> > selMap;
    std::string dataSel;
    std::string weight;
  };

  struct Name {
    std::map <std::string, std::string, std::less<std::string> > nameMap;
  };

  struct Reweight {
    std::map <std::string, std::string, std::less<std::string> > reweightMap;
  };

  struct Lumi {
    std::map <std::string, double, std::less<std::string> > lumiMap;
  };

  struct aSample {
    std::map <std::string, std::string, std::less<std::string> > sampleMap;
    std::string histoName;
    std::string color;
    std::string legendEntry;
  };

  struct MCSamples {

    std::map <std::string,aSample, std::less<std::string> > samples;

  };

  struct Dumper {
    std::map <std::string, bool, std::less<std::string> > dumperMap;
  };


  struct JSONData {
    Sequences algorithms;
    Dir directories;
    Var variables;
    Sel selections;
    Lumi luminosity;
    Name name;
    Reweight reweight;
    Bins bins;
    MCSamples samples;
    Dumper dumper;
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

