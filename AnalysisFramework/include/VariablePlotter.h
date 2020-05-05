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
#include "ROOT/RDataFrame.hxx"
#include "ROOT/RSnapshotOptions.hxx"


#include "algorithm.h"

class VariablePlotter: public algorithm {
public:
	VariablePlotter(std::string name):algorithm(name) {;}
	void execute() final override;
};
