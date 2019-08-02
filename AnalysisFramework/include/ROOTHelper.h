#pragma once

#include <string>
class TFile;

class ROOTHelper {
public:
	static TFile *GetTFile(std::string sample,std::string mcset, std::string fileName);
	static void setATLASStyle();
};
