#pragma once

#include <iostream>
#include "JSONDoc.h"

class Controller {
public:
	static mytest::JSONData& GetDocument();
	Controller() {;}
private:
	static mytest::JSONData document;

};

