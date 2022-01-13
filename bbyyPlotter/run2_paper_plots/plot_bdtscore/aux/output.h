//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jun  9 15:25:38 2017 by ROOT version 5.34/36
// from TTree output/output
// found on file: all_inputs/data.root
//////////////////////////////////////////////////////////

#ifndef output_h
#define output_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
using namespace std;

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class output {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   UInt_t          mcChannelNumber;
   UInt_t          runNumber;
   ULong64_t       eventNumber;
   Float_t         weight;
   Float_t         weight_BDT;
   Float_t         mass_yy;
   Float_t         pTt_yy;
   Float_t         pt_yy;
   Float_t         pt_hard;
   Float_t         cosTS_yy;
   Float_t         phiStar_yy;
   Float_t         ph_E1;
   Float_t         ph_E2;
   Float_t         ph_pt1;
   Float_t         ph_pt2;
   Float_t         ph_eta1;
   Float_t         ph_eta2;
   Float_t         ph_phi1;
   Float_t         ph_phi2;
   Float_t         ph_cos_eta2_1;
   Float_t         ph_cos_phi2_1;
   Bool_t          flag_passedIso;
   Bool_t          flag_passedPID;
   Float_t         sigmet_TST;
   Float_t         pt_lep_met;
   Float_t         mt_lep_met;
   Float_t         pt_lep_met_mxaod;
   Float_t         mt_lep_met_mxaod;
   Int_t           N_lep;
   Int_t           N_lep15;
   Int_t           N_jet25;
   Int_t           N_jet30;
   Int_t           N_jet35;
   Int_t           N_jet25_fwd;
   Int_t           N_jet30_fwd;
   Int_t           N_jet35_fwd;
   Int_t           N_jet25_cen;
   Int_t           N_jet30_cen;
   Int_t           N_jet35_cen;
   Int_t           N_bjet25_fixed60;
   Int_t           N_bjet25_fixed70;
   Int_t           N_bjet25_fixed77;
   Int_t           N_bjet25_fixed85;
   Int_t           N_bjet30_fixed60;
   Int_t           N_bjet30_fixed70;
   Int_t           N_bjet30_fixed77;
   Int_t           N_bjet30_fixed85;
   Int_t           N_bjet35_fixed60;
   Int_t           N_bjet35_fixed70;
   Int_t           N_bjet35_fixed77;
   Int_t           N_bjet35_fixed85;
   Float_t         mass_jet25;
   Float_t         mass_jet30;
   Float_t         mass_jet35;
   Float_t         HT_jet25;
   Float_t         HT_jet30;
   Float_t         HT_jet35;
   Float_t         random_number;
   Int_t           catCoup_Moriond2017BDT;

   // List of branches
   TBranch        *b_mcChannelNumber;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_weight_BDT;   //!
   TBranch        *b_mass_yy;   //!
   TBranch        *b_pTt_yy;   //!
   TBranch        *b_pt_yy;   //!
   TBranch        *b_pt_hard;   //!
   TBranch        *b_cosTS_yy;   //!
   TBranch        *b_phiStar_yy;   //!
   TBranch        *b_ph_E1;   //!
   TBranch        *b_ph_E2;   //!
   TBranch        *b_ph_pt1;   //!
   TBranch        *b_ph_pt2;   //!
   TBranch        *b_ph_eta1;   //!
   TBranch        *b_ph_eta2;   //!
   TBranch        *b_ph_phi1;   //!
   TBranch        *b_ph_phi2;   //!
   TBranch        *b_ph_cos_eta2_1;   //!
   TBranch        *b_ph_cos_phi2_1;   //!
   TBranch        *b_flag_passedIso;   //!
   TBranch        *b_flag_passedPID;   //!
   TBranch        *b_sigmet_TST;   //!
   TBranch        *b_pt_lep_met;   //!
   TBranch        *b_mt_lep_met;   //!
   TBranch        *b_pt_lep_met_mxaod;   //!
   TBranch        *b_mt_lep_met_mxaod;   //!
   TBranch        *b_N_lep;   //!
   TBranch        *b_N_lep15;   //!
   TBranch        *b_N_jet25;   //!
   TBranch        *b_N_jet30;   //!
   TBranch        *b_N_jet35;   //!
   TBranch        *b_N_jet25_fwd;   //!
   TBranch        *b_N_jet30_fwd;   //!
   TBranch        *b_N_jet35_fwd;   //!
   TBranch        *b_N_jet25_cen;   //!
   TBranch        *b_N_jet30_cen;   //!
   TBranch        *b_N_jet35_cen;   //!
   TBranch        *b_N_bjet25_fixed60;   //!
   TBranch        *b_N_bjet25_fixed70;   //!
   TBranch        *b_N_bjet25_fixed77;   //!
   TBranch        *b_N_bjet25_fixed85;   //!
   TBranch        *b_N_bjet30_fixed60;   //!
   TBranch        *b_N_bjet30_fixed70;   //!
   TBranch        *b_N_bjet30_fixed77;   //!
   TBranch        *b_N_bjet30_fixed85;   //!
   TBranch        *b_N_bjet35_fixed60;   //!
   TBranch        *b_N_bjet35_fixed70;   //!
   TBranch        *b_N_bjet35_fixed77;   //!
   TBranch        *b_N_bjet35_fixed85;   //!
   TBranch        *b_mass_jet25;   //!
   TBranch        *b_mass_jet30;   //!
   TBranch        *b_mass_jet35;   //!
   TBranch        *b_HT_jet25;   //!
   TBranch        *b_HT_jet30;   //!
   TBranch        *b_HT_jet35;   //!
   TBranch        *b_random_number;   //!
   TBranch        *b_catCoup_Moriond2017BDT;   //!

   output(TTree *tree=0);
   virtual ~output();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef output_cxx
output::output(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("all_inputs/data.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("all_inputs/data.root");
      }
      f->GetObject("output",tree);

   }
   Init(tree);
}

output::~output()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t output::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t output::LoadTree(Long64_t entry)
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

void output::Init(TTree *tree)
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

   fChain->SetBranchAddress("mcChannelNumber", &mcChannelNumber, &b_mcChannelNumber);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("weight_BDT", &weight_BDT, &b_weight_BDT);
   fChain->SetBranchAddress("mass_yy", &mass_yy, &b_mass_yy);
   fChain->SetBranchAddress("pTt_yy", &pTt_yy, &b_pTt_yy);
   fChain->SetBranchAddress("pt_yy", &pt_yy, &b_pt_yy);
   fChain->SetBranchAddress("pt_hard", &pt_hard, &b_pt_hard);
   fChain->SetBranchAddress("cosTS_yy", &cosTS_yy, &b_cosTS_yy);
   fChain->SetBranchAddress("phiStar_yy", &phiStar_yy, &b_phiStar_yy);
   fChain->SetBranchAddress("ph_E1", &ph_E1, &b_ph_E1);
   fChain->SetBranchAddress("ph_E2", &ph_E2, &b_ph_E2);
   fChain->SetBranchAddress("ph_pt1", &ph_pt1, &b_ph_pt1);
   fChain->SetBranchAddress("ph_pt2", &ph_pt2, &b_ph_pt2);
   fChain->SetBranchAddress("ph_eta1", &ph_eta1, &b_ph_eta1);
   fChain->SetBranchAddress("ph_eta2", &ph_eta2, &b_ph_eta2);
   fChain->SetBranchAddress("ph_phi1", &ph_phi1, &b_ph_phi1);
   fChain->SetBranchAddress("ph_phi2", &ph_phi2, &b_ph_phi2);
   fChain->SetBranchAddress("ph_cos_eta2_1", &ph_cos_eta2_1, &b_ph_cos_eta2_1);
   fChain->SetBranchAddress("ph_cos_phi2_1", &ph_cos_phi2_1, &b_ph_cos_phi2_1);
   fChain->SetBranchAddress("flag_passedIso", &flag_passedIso, &b_flag_passedIso);
   fChain->SetBranchAddress("flag_passedPID", &flag_passedPID, &b_flag_passedPID);
   fChain->SetBranchAddress("sigmet_TST", &sigmet_TST, &b_sigmet_TST);
   fChain->SetBranchAddress("pt_lep_met", &pt_lep_met, &b_pt_lep_met);
   fChain->SetBranchAddress("mt_lep_met", &mt_lep_met, &b_mt_lep_met);
   fChain->SetBranchAddress("pt_lep_met_mxaod", &pt_lep_met_mxaod, &b_pt_lep_met_mxaod);
   fChain->SetBranchAddress("mt_lep_met_mxaod", &mt_lep_met_mxaod, &b_mt_lep_met_mxaod);
   fChain->SetBranchAddress("N_lep", &N_lep, &b_N_lep);
   fChain->SetBranchAddress("N_lep15", &N_lep15, &b_N_lep15);
   fChain->SetBranchAddress("N_jet25", &N_jet25, &b_N_jet25);
   fChain->SetBranchAddress("N_jet30", &N_jet30, &b_N_jet30);
   fChain->SetBranchAddress("N_jet35", &N_jet35, &b_N_jet35);
   fChain->SetBranchAddress("N_jet25_fwd", &N_jet25_fwd, &b_N_jet25_fwd);
   fChain->SetBranchAddress("N_jet30_fwd", &N_jet30_fwd, &b_N_jet30_fwd);
   fChain->SetBranchAddress("N_jet35_fwd", &N_jet35_fwd, &b_N_jet35_fwd);
   fChain->SetBranchAddress("N_jet25_cen", &N_jet25_cen, &b_N_jet25_cen);
   fChain->SetBranchAddress("N_jet30_cen", &N_jet30_cen, &b_N_jet30_cen);
   fChain->SetBranchAddress("N_jet35_cen", &N_jet35_cen, &b_N_jet35_cen);
   fChain->SetBranchAddress("N_bjet25_fixed60", &N_bjet25_fixed60, &b_N_bjet25_fixed60);
   fChain->SetBranchAddress("N_bjet25_fixed70", &N_bjet25_fixed70, &b_N_bjet25_fixed70);
   fChain->SetBranchAddress("N_bjet25_fixed77", &N_bjet25_fixed77, &b_N_bjet25_fixed77);
   fChain->SetBranchAddress("N_bjet25_fixed85", &N_bjet25_fixed85, &b_N_bjet25_fixed85);
   fChain->SetBranchAddress("N_bjet30_fixed60", &N_bjet30_fixed60, &b_N_bjet30_fixed60);
   fChain->SetBranchAddress("N_bjet30_fixed70", &N_bjet30_fixed70, &b_N_bjet30_fixed70);
   fChain->SetBranchAddress("N_bjet30_fixed77", &N_bjet30_fixed77, &b_N_bjet30_fixed77);
   fChain->SetBranchAddress("N_bjet30_fixed85", &N_bjet30_fixed85, &b_N_bjet30_fixed85);
   fChain->SetBranchAddress("N_bjet35_fixed60", &N_bjet35_fixed60, &b_N_bjet35_fixed60);
   fChain->SetBranchAddress("N_bjet35_fixed70", &N_bjet35_fixed70, &b_N_bjet35_fixed70);
   fChain->SetBranchAddress("N_bjet35_fixed77", &N_bjet35_fixed77, &b_N_bjet35_fixed77);
   fChain->SetBranchAddress("N_bjet35_fixed85", &N_bjet35_fixed85, &b_N_bjet35_fixed85);
   fChain->SetBranchAddress("mass_jet25", &mass_jet25, &b_mass_jet25);
   fChain->SetBranchAddress("mass_jet30", &mass_jet30, &b_mass_jet30);
   fChain->SetBranchAddress("mass_jet35", &mass_jet35, &b_mass_jet35);
   fChain->SetBranchAddress("HT_jet25", &HT_jet25, &b_HT_jet25);
   fChain->SetBranchAddress("HT_jet30", &HT_jet30, &b_HT_jet30);
   fChain->SetBranchAddress("HT_jet35", &HT_jet35, &b_HT_jet35);
   fChain->SetBranchAddress("random_number", &random_number, &b_random_number);
   fChain->SetBranchAddress("catCoup_Moriond2017BDT", &catCoup_Moriond2017BDT, &b_catCoup_Moriond2017BDT);
   Notify();
}

Bool_t output::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void output::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t output::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef output_cxx
