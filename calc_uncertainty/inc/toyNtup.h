//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Mar 23 11:58:16 2016 by ROOT version 5.34/32
// from TTree toy/toy
// found on file: toy/high_mass_diphoton_EKHI_MT_vs_FB_FB_toy/high_mass_diphoton_EKHI_MT_vs_FB_FB_toy_1000_10_FB.root
//////////////////////////////////////////////////////////

#ifndef toy_h
#define toy_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>

using namespace std;
// Fixed size dimensions of array or collections stored in the TTree if any.

class toy {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Double_t        nllfix;
   Double_t        nllhat;
   Double_t        muhat;
   Double_t        GkM;
   Double_t        statusfix;
   Double_t        statushat;
   vector<double>  *valuenpfix;
   vector<double>  *valuenphat;
   Double_t        nevt;
   Int_t           seed;
   vector<string>  *namenp;

   // List of branches
   TBranch        *b_nllfix;   //!
   TBranch        *b_nllhat;   //!
   TBranch        *b_muhat;   //!
   TBranch        *b_GkM;   //!
   TBranch        *b_statusfix;   //!
   TBranch        *b_statushat;   //!
   TBranch        *b_valuenpfix;   //!
   TBranch        *b_valuenphat;   //!
   TBranch        *b_nevt;   //!
   TBranch        *b_seed;   //!
   TBranch        *b_namenp;   //!

   toy(TTree *tree=0);
   virtual ~toy();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef toy_cxx
toy::toy(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("toy/high_mass_diphoton_EKHI_MT_vs_FB_FB_toy/high_mass_diphoton_EKHI_MT_vs_FB_FB_toy_1000_10_FB.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("toy/high_mass_diphoton_EKHI_MT_vs_FB_FB_toy/high_mass_diphoton_EKHI_MT_vs_FB_FB_toy_1000_10_FB.root");
      }
      f->GetObject("toy",tree);

   }
   Init(tree);
}

toy::~toy()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t toy::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t toy::LoadTree(Long64_t entry)
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

void toy::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   valuenpfix = 0;
   valuenphat = 0;
   namenp = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("nllfix", &nllfix, &b_nllfix);
   fChain->SetBranchAddress("nllhat", &nllhat, &b_nllhat);
   fChain->SetBranchAddress("muhat", &muhat, &b_muhat);
   fChain->SetBranchAddress("GkM", &GkM, &b_GkM);
   fChain->SetBranchAddress("statusfix", &statusfix, &b_statusfix);
   fChain->SetBranchAddress("statushat", &statushat, &b_statushat);
   fChain->SetBranchAddress("valuenpfix", &valuenpfix, &b_valuenpfix);
   fChain->SetBranchAddress("valuenphat", &valuenphat, &b_valuenphat);
   fChain->SetBranchAddress("nevt", &nevt, &b_nevt);
   fChain->SetBranchAddress("seed", &seed, &b_seed);
   fChain->SetBranchAddress("namenp", &namenp, &b_namenp);
   Notify();
}

Bool_t toy::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void toy::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t toy::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef toy_cxx
