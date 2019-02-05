#include "Controller.h"
#include "JSONDoc.h"

mytest::JSONData Controller::document;

mytest::JSONData& Controller::GetDocument()
{
	return document;
}
