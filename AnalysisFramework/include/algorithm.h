#pragma once

#include <string>
#include "Controller.h"

class algorithm {
public:
	algorithm() {;}
	algorithm(std::string name) {Controller::getController()->setAlgorithm(name,this);}
	virtual ~algorithm() {;}
	virtual void execute() = 0;
};

#define DECLARE_ALGORITHM(type,name) static type x( #name );

