//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Aug 17 11:12:47 2017 by ROOT version 5.34/36
// from TTree test/test
// found on file: hadronic_rnn/ttH_hadronic_test.root
//////////////////////////////////////////////////////////

#ifndef test_h
#define test_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class test {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Float_t         random_number;
   Float_t         mass_yy;
   Float_t         weight;
   Int_t           flag_passedIso;
   Int_t           flag_passedPID;
   Int_t           relpt_cut;
   Int_t           dirpt_cut1;
   Int_t           dirpt_cut2;
   Float_t         nnweight;

   // List of branches
   TBranch        *b_random_number;   //!
   TBranch        *b_mass_yy;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_flag_passedIso;   //!
   TBranch        *b_flag_passedPID;   //!
   TBranch        *b_relpt_cut;   //!
   TBranch        *b_dirpt_cut1;   //!
   TBranch        *b_dirpt_cut2;   //!
   TBranch        *b_nnweight;   //!

   test(TTree *tree=0);
   virtual ~test();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef test_cxx
test::test(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("hadronic_rnn/ttH_hadronic_test.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("hadronic_rnn/ttH_hadronic_test.root");
      }
      f->GetObject("test",tree);

   }
   Init(tree);
}

test::~test()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t test::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t test::LoadTree(Long64_t entry)
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

void test::Init(TTree *tree)
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

   fChain->SetBranchAddress("random_number", &random_number, &b_random_number);
   fChain->SetBranchAddress("mass_yy", &mass_yy, &b_mass_yy);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("flag_passedIso", &flag_passedIso, &b_flag_passedIso);
   fChain->SetBranchAddress("flag_passedPID", &flag_passedPID, &b_flag_passedPID);
   fChain->SetBranchAddress("relpt_cut", &relpt_cut, &b_relpt_cut);
   fChain->SetBranchAddress("dirpt_cut1", &dirpt_cut1, &b_dirpt_cut1);
   fChain->SetBranchAddress("dirpt_cut2", &dirpt_cut2, &b_dirpt_cut2);
   fChain->SetBranchAddress("nnweight", &nnweight, &b_nnweight);
   Notify();
}

Bool_t test::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void test::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t test::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef test_cxx
