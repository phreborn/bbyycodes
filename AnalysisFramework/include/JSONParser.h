#pragma once

#include <nlohmann/json.hpp>
#include <string>

class algorithm;

using json = nlohmann::json;


class JSONParser {
public:
	JSONParser(std::string f);
	void setAlgorithm(algorithm* i);
        void parseAndIterate(); 
	void parse();
	void CreateDocument(json& jj);
private:
	std::vector<algorithm*> algorithms;
	std::string fileName;

};
