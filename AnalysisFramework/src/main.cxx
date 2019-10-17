#include "JSONParser.h"
#include <iostream>
#include "Controller.h"

int main (int argc, char* argv[]) {

  std::cout << "start processing..." << std::endl;
  std::string fileName="samples.js";
  if (argc>1)
    fileName=argv[1];

  JSONParser jp(fileName);
  jp.parseAndIterate();

  std::cout << "DONE! exiting with return code 0 " << std::endl;
  return 0;
}
