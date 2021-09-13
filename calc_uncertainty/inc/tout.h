//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Apr 25 12:42:32 2016 by ROOT version 5.34/32
// from TTree tout/recreate
// found on file: Output/sample/mc/Sherpa_gamgam_2DP20.root
//////////////////////////////////////////////////////////

#ifndef tout_h
#define tout_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class tout {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Float_t         pt_1st;
   Float_t         eta_1st;
   Float_t         eta_s2_1st;
   Float_t         phi_1st;
   Float_t         scaleFactor_1st;
   Int_t           conversionType_1st;
   Float_t         pt_2nd;
   Float_t         eta_2nd;
   Float_t         eta_s2_2nd;
   Float_t         phi_2nd;
   Float_t         scaleFactor_2nd;
   Int_t           conversionType_2nd;
   Bool_t          isPassHKHI;
   Bool_t          isPassEKHI;
   Int_t           mcChannelNumber;
   Float_t         vertexWeight;
   Float_t         pileupWeight;
   Float_t         crossSectionBRfilterEff;
   Float_t         m_yy;
   Float_t         m_yy_resolution;
   Float_t         totalEvents;

   // List of branches
   TBranch        *b_pt_1st;   //!
   TBranch        *b_eta_1st;   //!
   TBranch        *b_eta_s2_1st;   //!
   TBranch        *b_phi_1st;   //!
   TBranch        *b_scaleFactor_1st;   //!
   TBranch        *b_conversionType_1st;   //!
   TBranch        *b_pt_2nd;   //!
   TBranch        *b_eta_2nd;   //!
   TBranch        *b_eta_s2_2nd;   //!
   TBranch        *b_phi_2nd;   //!
   TBranch        *b_scaleFactor_2nd;   //!
   TBranch        *b_conversionType_2nd;   //!
   TBranch        *b_isPassHKHI;   //!
   TBranch        *b_isPassEKHI;   //!
   TBranch        *b_mcChannelNumber;   //!
   TBranch        *b_vertexWeight;   //!
   TBranch        *b_pileupWeight;   //!
   TBranch        *b_crossSectionBRfilterEff;   //!
   TBranch        *b_m_yy;   //!
   TBranch        *b_m_yy_resolution;   //!
   TBranch        *b_totalEvents;   //!

   tout(TTree *tree=0);
   virtual ~tout();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef tout_cxx
tout::tout(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Output/sample/mc/Sherpa_gamgam_2DP20.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("Output/sample/mc/Sherpa_gamgam_2DP20.root");
      }
      f->GetObject("tout",tree);

   }
   Init(tree);
}

tout::~tout()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t tout::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t tout::LoadTree(Long64_t entry)
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

void tout::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("pt_1st", &pt_1st, &b_pt_1st);
   fChain->SetBranchAddress("eta_1st", &eta_1st, &b_eta_1st);
   fChain->SetBranchAddress("eta_s2_1st", &eta_s2_1st, &b_eta_s2_1st);
   fChain->SetBranchAddress("phi_1st", &phi_1st, &b_phi_1st);
   fChain->SetBranchAddress("scaleFactor_1st", &scaleFactor_1st, &b_scaleFactor_1st);
   fChain->SetBranchAddress("conversionType_1st", &conversionType_1st, &b_conversionType_1st);
   fChain->SetBranchAddress("pt_2nd", &pt_2nd, &b_pt_2nd);
   fChain->SetBranchAddress("eta_2nd", &eta_2nd, &b_eta_2nd);
   fChain->SetBranchAddress("eta_s2_2nd", &eta_s2_2nd, &b_eta_s2_2nd);
   fChain->SetBranchAddress("phi_2nd", &phi_2nd, &b_phi_2nd);
   fChain->SetBranchAddress("scaleFactor_2nd", &scaleFactor_2nd, &b_scaleFactor_2nd);
   fChain->SetBranchAddress("conversionType_2nd", &conversionType_2nd, &b_conversionType_2nd);
   fChain->SetBranchAddress("isPassHKHI", &isPassHKHI, &b_isPassHKHI);
   fChain->SetBranchAddress("isPassEKHI", &isPassEKHI, &b_isPassEKHI);
   fChain->SetBranchAddress("mcChannelNumber", &mcChannelNumber, &b_mcChannelNumber);
   fChain->SetBranchAddress("vertexWeight", &vertexWeight, &b_vertexWeight);
   fChain->SetBranchAddress("pileupWeight", &pileupWeight, &b_pileupWeight);
   fChain->SetBranchAddress("crossSectionBRfilterEff", &crossSectionBRfilterEff, &b_crossSectionBRfilterEff);
   fChain->SetBranchAddress("m_yy", &m_yy, &b_m_yy);
   fChain->SetBranchAddress("m_yy_resolution", &m_yy_resolution, &b_m_yy_resolution);
   fChain->SetBranchAddress("totalEvents", &totalEvents, &b_totalEvents);
   Notify();
}

Bool_t tout::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void tout::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t tout::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef tout_cxx
