#include "JSONParser.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

#include "JSONDoc.h"
#include "serializers.h"

#include "algorithm.h"
#include "Controller.h"

using json = nlohmann::json;


JSONParser::JSONParser(std::string f):fileName(f) {;}
void JSONParser::setAlgorithm(algorithm* i) {algorithms.push_back(i);}
void JSONParser::parseAndIterate() {
  std::ifstream fileIn(fileName);
  json j = json::parse(fileIn);

  json &jj=j;
  CreateDocument(jj);
  for (auto it:algorithms)
    it->execute();
}
void JSONParser::parse() {
  std::ifstream fileIn(fileName);
  json j = json::parse(fileIn);

  json &jj=j;
  CreateDocument(jj);
}
void JSONParser::CreateDocument(json& jj)
{
  mytest::JSONData& document=Controller::GetDocument();

  for (auto it = jj.begin(); it != jj.end(); ++it)
  {
    json &val = it.value();
    json pp=val;

    std::string key = it.key();
    if (key == "sequencer") {
      document.algorithms = pp;
      for (auto it:document.algorithms.items)
      {
        std::cout << " setting algorithm "<<it<<std::endl;
        setAlgorithm(Controller::getController()->getAlgorithm(it));
      }
    }
    else if (key == "bins") {
      document.bins = pp;
    }
    else if (key == "directories") {
      document.directories = pp;
    }
    else if (key == "lumi") {
      document.luminosity = pp;
    }
    else if (key == "variables") {
      document.variables = pp;
    }
    else if (key == "samples") {
      document.samples = pp;
    }
    else if (key == "selections") {
      document.selections = pp;
    }
    else if (key == "dumper") {
      document.dumper = pp;
    }

  }	
}

