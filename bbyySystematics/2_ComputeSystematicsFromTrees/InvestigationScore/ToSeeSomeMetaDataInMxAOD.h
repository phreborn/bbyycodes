//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Nov 26 16:13:01 2020 by ROOT version 6.22/02
// from TTree MetaData/xAOD metadata tree
// found on file: sample1.root
//////////////////////////////////////////////////////////

#ifndef ToSeeSomeMetaDataInMxAOD_h
#define ToSeeSomeMetaDataInMxAOD_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "string"

class ToSeeSomeMetaDataInMxAOD {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
   static constexpr Int_t kMaxTruthMetaDataAux = 1;
   static constexpr Int_t kMaxFileMetaDataAux = 1;

   // Declaration of leaf types
 //xAOD::EventFormat_v1 *EventFormat;
   vector<string>  m_branchNames;
   vector<string>  m_classNames;
   vector<string>  m_parentNames;
   vector<unsigned int> m_branchHashes;
 //xAOD::TruthMetaDataAuxContainer_v1 *TruthMetaDataAux_;
 //xAOD::TruthMetaDataAuxContainer_v1 *TruthMetaDataAux_xAOD__AuxContainerBase;
   vector<vector<string> > TruthMetaDataAux_weightNames;
   vector<unsigned int> TruthMetaDataAux_mcChannelNumber;
   vector<string>  TruthMetaDataAux_lhefGenerator;
   vector<string>  TruthMetaDataAux_generators;
   vector<string>  TruthMetaDataAux_evgenProcess;
   vector<string>  TruthMetaDataAux_evgenTune;
   vector<string>  TruthMetaDataAux_hardPDF;
   vector<string>  TruthMetaDataAux_softPDF;
  //DataVector<xAOD::TruthMetaData_v1> *TruthMetaData;
  //xAOD::FileMetaData_v1 *FileMetaData;
 //xAOD::FileMetaDataAuxInfo_v1 *FileMetaDataAux_;
 //xAOD::FileMetaDataAuxInfo_v1 *FileMetaDataAux_xAOD__AuxInfoBase;
   string          FileMetaDataAux_productionRelease;
   string          FileMetaDataAux_dataType;
   string          *FileMetaDataAuxDyn_amiTag;
   Float_t         FileMetaDataAuxDyn_beamEnergy;
   string          *FileMetaDataAuxDyn_beamType;
   string          *FileMetaDataAuxDyn_conditionsTag;
   string          *FileMetaDataAuxDyn_geometryVersion;
   Char_t          FileMetaDataAuxDyn_isDataOverlay;
   Float_t         FileMetaDataAuxDyn_mcProcID;
   string          *FileMetaDataAuxDyn_simFlavour;

   // List of branches
   TBranch        *b_EventFormat_m_branchNames;   //!
   TBranch        *b_EventFormat_m_classNames;   //!
   TBranch        *b_EventFormat_m_parentNames;   //!
   TBranch        *b_EventFormat_m_branchHashes;   //!
   TBranch        *b_TruthMetaDataAux_weightNames;   //!
   TBranch        *b_TruthMetaDataAux_mcChannelNumber;   //!
   TBranch        *b_TruthMetaDataAux_lhefGenerator;   //!
   TBranch        *b_TruthMetaDataAux_generators;   //!
   TBranch        *b_TruthMetaDataAux_evgenProcess;   //!
   TBranch        *b_TruthMetaDataAux_evgenTune;   //!
   TBranch        *b_TruthMetaDataAux_hardPDF;   //!
   TBranch        *b_TruthMetaDataAux_softPDF;   //!
   TBranch        *b_TruthMetaData;   //!
   TBranch        *b_FileMetaData;   //!
   TBranch        *b_FileMetaDataAux_productionRelease;   //!
   TBranch        *b_FileMetaDataAux_dataType;   //!
   TBranch        *b_FileMetaDataAuxDyn_amiTag;   //!
   TBranch        *b_FileMetaDataAuxDyn_beamEnergy;   //!
   TBranch        *b_FileMetaDataAuxDyn_beamType;   //!
   TBranch        *b_FileMetaDataAuxDyn_conditionsTag;   //!
   TBranch        *b_FileMetaDataAuxDyn_geometryVersion;   //!
   TBranch        *b_FileMetaDataAuxDyn_isDataOverlay;   //!
   TBranch        *b_FileMetaDataAuxDyn_mcProcID;   //!
   TBranch        *b_FileMetaDataAuxDyn_simFlavour;   //!

   ToSeeSomeMetaDataInMxAOD(TTree *tree=0);
   virtual ~ToSeeSomeMetaDataInMxAOD();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ToSeeSomeMetaDataInMxAOD_cxx
ToSeeSomeMetaDataInMxAOD::ToSeeSomeMetaDataInMxAOD(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("sample1.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("sample1.root");
      }
      f->GetObject("MetaData",tree);

   }
   Init(tree);
}

ToSeeSomeMetaDataInMxAOD::~ToSeeSomeMetaDataInMxAOD()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ToSeeSomeMetaDataInMxAOD::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ToSeeSomeMetaDataInMxAOD::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void ToSeeSomeMetaDataInMxAOD::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   //TruthMetaData = 0;
   //FileMetaData = 0;
   FileMetaDataAuxDyn_amiTag = 0;
   FileMetaDataAuxDyn_beamType = 0;
   FileMetaDataAuxDyn_conditionsTag = 0;
   FileMetaDataAuxDyn_geometryVersion = 0;
   FileMetaDataAuxDyn_simFlavour = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("m_branchNames", &m_branchNames, &b_EventFormat_m_branchNames);
   fChain->SetBranchAddress("m_classNames", &m_classNames, &b_EventFormat_m_classNames);
   fChain->SetBranchAddress("m_parentNames", &m_parentNames, &b_EventFormat_m_parentNames);
   fChain->SetBranchAddress("m_branchHashes", &m_branchHashes, &b_EventFormat_m_branchHashes);
   fChain->SetBranchAddress("TruthMetaDataAux.weightNames", &TruthMetaDataAux_weightNames, &b_TruthMetaDataAux_weightNames);
   fChain->SetBranchAddress("TruthMetaDataAux.mcChannelNumber", &TruthMetaDataAux_mcChannelNumber, &b_TruthMetaDataAux_mcChannelNumber);
   fChain->SetBranchAddress("TruthMetaDataAux.lhefGenerator", &TruthMetaDataAux_lhefGenerator, &b_TruthMetaDataAux_lhefGenerator);
   fChain->SetBranchAddress("TruthMetaDataAux.generators", &TruthMetaDataAux_generators, &b_TruthMetaDataAux_generators);
   fChain->SetBranchAddress("TruthMetaDataAux.evgenProcess", &TruthMetaDataAux_evgenProcess, &b_TruthMetaDataAux_evgenProcess);
   fChain->SetBranchAddress("TruthMetaDataAux.evgenTune", &TruthMetaDataAux_evgenTune, &b_TruthMetaDataAux_evgenTune);
   fChain->SetBranchAddress("TruthMetaDataAux.hardPDF", &TruthMetaDataAux_hardPDF, &b_TruthMetaDataAux_hardPDF);
   fChain->SetBranchAddress("TruthMetaDataAux.softPDF", &TruthMetaDataAux_softPDF, &b_TruthMetaDataAux_softPDF);
   //fChain->SetBranchAddress("TruthMetaData", &TruthMetaData, &b_TruthMetaData);
   //fChain->SetBranchAddress("FileMetaData", &FileMetaData, &b_FileMetaData);
   fChain->SetBranchAddress("FileMetaDataAux.productionRelease", &FileMetaDataAux_productionRelease, &b_FileMetaDataAux_productionRelease);
   fChain->SetBranchAddress("FileMetaDataAux.dataType", &FileMetaDataAux_dataType, &b_FileMetaDataAux_dataType);
   fChain->SetBranchAddress("FileMetaDataAuxDyn.amiTag", &FileMetaDataAuxDyn_amiTag, &b_FileMetaDataAuxDyn_amiTag);
   fChain->SetBranchAddress("FileMetaDataAuxDyn.beamEnergy", &FileMetaDataAuxDyn_beamEnergy, &b_FileMetaDataAuxDyn_beamEnergy);
   fChain->SetBranchAddress("FileMetaDataAuxDyn.beamType", &FileMetaDataAuxDyn_beamType, &b_FileMetaDataAuxDyn_beamType);
   fChain->SetBranchAddress("FileMetaDataAuxDyn.conditionsTag", &FileMetaDataAuxDyn_conditionsTag, &b_FileMetaDataAuxDyn_conditionsTag);
   fChain->SetBranchAddress("FileMetaDataAuxDyn.geometryVersion", &FileMetaDataAuxDyn_geometryVersion, &b_FileMetaDataAuxDyn_geometryVersion);
   fChain->SetBranchAddress("FileMetaDataAuxDyn.isDataOverlay", &FileMetaDataAuxDyn_isDataOverlay, &b_FileMetaDataAuxDyn_isDataOverlay);
   fChain->SetBranchAddress("FileMetaDataAuxDyn.mcProcID", &FileMetaDataAuxDyn_mcProcID, &b_FileMetaDataAuxDyn_mcProcID);
   fChain->SetBranchAddress("FileMetaDataAuxDyn.simFlavour", &FileMetaDataAuxDyn_simFlavour, &b_FileMetaDataAuxDyn_simFlavour);
   Notify();
}

Bool_t ToSeeSomeMetaDataInMxAOD::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ToSeeSomeMetaDataInMxAOD::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ToSeeSomeMetaDataInMxAOD::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ToSeeSomeMetaDataInMxAOD_cxx
