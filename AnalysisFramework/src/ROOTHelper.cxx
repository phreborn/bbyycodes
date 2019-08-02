#include "ROOTHelper.h"
#include <map>
#include <string>
#include "TFile.h"

TFile* ROOTHelper::GetTFile(std::string sample,std::string mcset, std::string fileName)
{
        static std::map<std::string,TFile*,std::less<std::string> > tfileMap;
        std::string temp=sample+"_"+mcset;
        if (tfileMap.find(temp) != tfileMap.end())
                return tfileMap[temp];
        else
        {
                TFile* tf=new TFile(fileName.c_str());
                tfileMap[temp]=tf;
                return tf;
        }
}

