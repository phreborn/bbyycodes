#pragma once

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
#include "algorithm.h"
#include "ROOT/RDataFrame.hxx"
#include "ROOT/RSnapshotOptions.hxx"

class DataAnalysis: public algorithm {
public:
	DataAnalysis(std::string name):algorithm(name) {;}
	void execute() final override;
};
