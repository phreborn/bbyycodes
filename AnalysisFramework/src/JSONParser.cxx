#include "JSONParser.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

#include "JSONDoc.h"
#include "serializers.h"

#include "modelIterator.h"
#include "Controller.h"

using json = nlohmann::json;


JSONParser::JSONParser(std::string f):fileName(f) {;}
void JSONParser::setIterator(modelIterator* i) {iterator=i;}
void JSONParser::parseAndIterate() {
	std::ifstream fileIn(fileName);
	json j = json::parse(fileIn);

	json &jj=j;
	CreateDocument(jj);
	iterator->IterateModel(jj);
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
        if (key == "bins") {
        	document.bins = pp;
        }
        else if (key == "directories") {
            document.directories = pp;
        }
        else if (key == "lumi") {
            document.luminosity = pp;
        }
        else if (key == "myy_var") {
            document.variables.variable = it.value();
        }
        else if (key == "samples") {
            document.samples = pp;
        }
        else if (key == "selections") {
            document.selections = pp;
        }

    }	
}

