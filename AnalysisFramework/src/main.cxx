#include "JSONParser.h"
#include "YieldIterator.h"

int main (int argc, char* argv[]) {

  std::cout << "start processing..." << std::endl;
  std::string fileName="samples.js";
  if (argc>1)
	fileName=argv[1];

  JSONParser jp(fileName);
  jp.setIterator(new YieldIterator);
  jp.parseAndIterate();

  std::cout << "DONE! exiting with return code 0 " << std::endl;
  return 0;
}
