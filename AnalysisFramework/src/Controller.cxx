#include "Controller.h"
#include "JSONDoc.h"
#include "algorithm.h"

mytest::JSONData Controller::document;

Controller* Controller::getController()
{
	static Controller* controller=new Controller;
	return controller;
}

mytest::JSONData& Controller::GetDocument()
{
	return document;
}

void Controller::setAlgorithm(std::string name, algorithm* it)
{
	std::cout<< " Controller::setAlgorithm: registering algorithm "<<name<<std::endl;
	algorithmMap[name]=it;
}
algorithm* Controller::getAlgorithm(std::string name)
{
	if (algorithmMap.find(name)!=algorithmMap.end())
		return algorithmMap[name];
	else
		return 0;
}
