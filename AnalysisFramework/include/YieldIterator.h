#pragma once

#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "TFile.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TTree.h"
#include "TChain.h"
#include "TCanvas.h"
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

#include "modelIterator.h"

using json = nlohmann::json;

class YieldIterator: public modelIterator {
	void IterateModel(json& j) final override;
        TFile *GetTFile(std::string sample,std::string mcset, std::string fileName);
};
