#pragma once

#include <iostream>
#include "JSONDoc.h"
#include <string>
#include <map>

class algorithm;

class Controller {
  public:
    static Controller* getController();	
    static mytest::JSONData& GetDocument();
    algorithm* getAlgorithm(std::string);
    void setAlgorithm(std::string, algorithm*);
  private:
    Controller() {;}
    static mytest::JSONData document;
    std::map<std::string,algorithm*,std::less<std::string> > algorithmMap;
};

