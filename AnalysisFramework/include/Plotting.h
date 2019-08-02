#pragma once

#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "TFile.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TLine.h"


class Plotting {
public:
    void DoPlots(std::string histoName,std::string yaxislabel,std::string xaxislabel);
};