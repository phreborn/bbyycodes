#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class modelIterator {
public:
	modelIterator() {;}
	virtual ~modelIterator() {;}
	virtual void IterateModel(json&) = 0;
};

