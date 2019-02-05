#pragma once

#include <nlohmann/json.hpp>
#include <string>

class modelIterator;

using json = nlohmann::json;


class JSONParser {
public:
	JSONParser(std::string f);
	void setIterator(modelIterator* i);
        void parseAndIterate(); 
	void parse();
	void CreateDocument(json& jj);
private:
	modelIterator* iterator;
	std::string fileName;

};
