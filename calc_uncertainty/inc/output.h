//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Nov 23 14:34:08 2016 by ROOT version 5.34/36
// from TTree output/output
// found on file: ttH_Hgamgam/ntuple_haichen/20161121/ggHw.root
//////////////////////////////////////////////////////////

#ifndef output_h
#define output_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>

using namespace std;

// Fixed size dimensions of array or collections stored in the TTree if any.

class output {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           m_mcChannelNumber;
   Int_t           m_nlep;
   Int_t           m_njet;
   Int_t           m_njet30;
   Int_t           m_njet35;
   Int_t           m_njet_fwd;
   Int_t           m_nbjet_fixed60;
   Int_t           m_nbjet_fixed70;
   Int_t           m_nbjet_fixed80;
   Int_t           m_nbjet_fixed85;
   Int_t           m_nbjet30_fixed60;
   Int_t           m_nbjet30_fixed70;
   Int_t           m_nbjet30_fixed80;
   Int_t           m_nbjet30_fixed85;
   Int_t           m_nbjet35_fixed60;
   Int_t           m_nbjet35_fixed70;
   Int_t           m_nbjet35_fixed80;
   Int_t           m_nbjet35_fixed85;
   Double_t        m_mgg;
   Double_t        m_mass_multijet;
   Double_t        m_HT_multijet;
   Double_t        m_HT_all;
   Double_t        m_HT_event;
   Double_t        m_met;
   Double_t        m_sumet;
   Double_t        m_mT;
   Double_t        m_mT_top;
   Double_t        m_mtop;
   Double_t        m_met_sig;
   Double_t        m_weight;
   Double_t        ph_E1;
   Double_t        ph_E2;
   Double_t        ph_pt1;
   Double_t        ph_pt2;
   Double_t        ph_eta1;
   Double_t        ph_eta2;
   Double_t        ph_phi1;
   Double_t        ph_phi2;
   Int_t           ph_convType1;
   Int_t           ph_convType2;
   Bool_t          ph_isTight1;
   Bool_t          ph_isTight2;
   Bool_t          ph_iso1;
   Bool_t          ph_iso2;
   Bool_t          flag_passedIso;
   Int_t           cutFlow;
   Bool_t          flag_passedPID;
   vector<double>  *m_jet_pt;
   vector<double>  *m_jet_eta;
   vector<double>  *m_jet_phi;
   Int_t           m_cateindex;
   Int_t           m_cateindex_dev;
   Float_t         RNDM;
   Float_t         BDTG;

   // List of branches
   TBranch        *b_m_mcChannelNumber;   //!
   TBranch        *b_m_nlep;   //!
   TBranch        *b_m_njet;   //!
   TBranch        *b_m_njet30;   //!
   TBranch        *b_m_njet35;   //!
   TBranch        *b_m_njet_fwd;   //!
   TBranch        *b_m_nbjet_fixed60;   //!
   TBranch        *b_m_nbjet_fixed70;   //!
   TBranch        *b_m_nbjet_fixed80;   //!
   TBranch        *b_m_nbjet_fixed85;   //!
   TBranch        *b_m_nbjet30_fixed60;   //!
   TBranch        *b_m_nbjet30_fixed70;   //!
   TBranch        *b_m_nbjet30_fixed80;   //!
   TBranch        *b_m_nbjet30_fixed85;   //!
   TBranch        *b_m_nbjet35_fixed60;   //!
   TBranch        *b_m_nbjet35_fixed70;   //!
   TBranch        *b_m_nbjet35_fixed80;   //!
   TBranch        *b_m_nbjet35_fixed85;   //!
   TBranch        *b_m_mgg;   //!
   TBranch        *b_m_mass_multijet;   //!
   TBranch        *b_m_HT_multijet;   //!
   TBranch        *b_m_HT_all;   //!
   TBranch        *b_m_HT_event;   //!
   TBranch        *b_m_met;   //!
   TBranch        *b_m_sumet;   //!
   TBranch        *b_m_mT;   //!
   TBranch        *b_m_mT_top;   //!
   TBranch        *b_m_mtop;   //!
   TBranch        *b_m_met_sig;   //!
   TBranch        *b_m_weight;   //!
   TBranch        *b_ph_E1;   //!
   TBranch        *b_ph_E2;   //!
   TBranch        *b_ph_pt1;   //!
   TBranch        *b_ph_pt2;   //!
   TBranch        *b_ph_eta1;   //!
   TBranch        *b_ph_eta2;   //!
   TBranch        *b_ph_phi1;   //!
   TBranch        *b_ph_phi2;   //!
   TBranch        *b_ph_convType1;   //!
   TBranch        *b_ph_convType2;   //!
   TBranch        *b_ph_isTight1;   //!
   TBranch        *b_ph_isTight2;   //!
   TBranch        *b_ph_iso1;   //!
   TBranch        *b_ph_iso2;   //!
   TBranch        *b_flag_passedIso;   //!
   TBranch        *b_cutFlow;   //!
   TBranch        *b_flag_passedPID;   //!
   TBranch        *b_m_jet_pt;   //!
   TBranch        *b_m_jet_eta;   //!
   TBranch        *b_m_jet_phi;   //!
   TBranch        *b_m_cateindex;   //!
   TBranch        *b_m_cateindex_dev;   //!
   TBranch        *b_RNDM;   //!
   TBranch        *b_BDTG;   //!

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
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("ttH_Hgamgam/ntuple_haichen/20161121/ggHw.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("ttH_Hgamgam/ntuple_haichen/20161121/ggHw.root");
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

   // Set object pointer
   m_jet_pt = 0;
   m_jet_eta = 0;
   m_jet_phi = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("m_mcChannelNumber", &m_mcChannelNumber, &b_m_mcChannelNumber);
   fChain->SetBranchAddress("m_nlep", &m_nlep, &b_m_nlep);
   fChain->SetBranchAddress("m_njet", &m_njet, &b_m_njet);
   fChain->SetBranchAddress("m_njet30", &m_njet30, &b_m_njet30);
   fChain->SetBranchAddress("m_njet35", &m_njet35, &b_m_njet35);
   fChain->SetBranchAddress("m_njet_fwd", &m_njet_fwd, &b_m_njet_fwd);
   fChain->SetBranchAddress("m_nbjet_fixed60", &m_nbjet_fixed60, &b_m_nbjet_fixed60);
   fChain->SetBranchAddress("m_nbjet_fixed70", &m_nbjet_fixed70, &b_m_nbjet_fixed70);
   fChain->SetBranchAddress("m_nbjet_fixed80", &m_nbjet_fixed80, &b_m_nbjet_fixed80);
   fChain->SetBranchAddress("m_nbjet_fixed85", &m_nbjet_fixed85, &b_m_nbjet_fixed85);
   fChain->SetBranchAddress("m_nbjet30_fixed60", &m_nbjet30_fixed60, &b_m_nbjet30_fixed60);
   fChain->SetBranchAddress("m_nbjet30_fixed70", &m_nbjet30_fixed70, &b_m_nbjet30_fixed70);
   fChain->SetBranchAddress("m_nbjet30_fixed80", &m_nbjet30_fixed80, &b_m_nbjet30_fixed80);
   fChain->SetBranchAddress("m_nbjet30_fixed85", &m_nbjet30_fixed85, &b_m_nbjet30_fixed85);
   fChain->SetBranchAddress("m_nbjet35_fixed60", &m_nbjet35_fixed60, &b_m_nbjet35_fixed60);
   fChain->SetBranchAddress("m_nbjet35_fixed70", &m_nbjet35_fixed70, &b_m_nbjet35_fixed70);
   fChain->SetBranchAddress("m_nbjet35_fixed80", &m_nbjet35_fixed80, &b_m_nbjet35_fixed80);
   fChain->SetBranchAddress("m_nbjet35_fixed85", &m_nbjet35_fixed85, &b_m_nbjet35_fixed85);
   fChain->SetBranchAddress("m_mgg", &m_mgg, &b_m_mgg);
   fChain->SetBranchAddress("m_mass_multijet", &m_mass_multijet, &b_m_mass_multijet);
   fChain->SetBranchAddress("m_HT_multijet", &m_HT_multijet, &b_m_HT_multijet);
   fChain->SetBranchAddress("m_HT_all", &m_HT_all, &b_m_HT_all);
   fChain->SetBranchAddress("m_HT_event", &m_HT_event, &b_m_HT_event);
   fChain->SetBranchAddress("m_met", &m_met, &b_m_met);
   fChain->SetBranchAddress("m_sumet", &m_sumet, &b_m_sumet);
   fChain->SetBranchAddress("m_mT", &m_mT, &b_m_mT);
   fChain->SetBranchAddress("m_mT_top", &m_mT_top, &b_m_mT_top);
   fChain->SetBranchAddress("m_mtop", &m_mtop, &b_m_mtop);
   fChain->SetBranchAddress("m_met_sig", &m_met_sig, &b_m_met_sig);
   fChain->SetBranchAddress("m_weight", &m_weight, &b_m_weight);
   fChain->SetBranchAddress("ph_E1", &ph_E1, &b_ph_E1);
   fChain->SetBranchAddress("ph_E2", &ph_E2, &b_ph_E2);
   fChain->SetBranchAddress("ph_pt1", &ph_pt1, &b_ph_pt1);
   fChain->SetBranchAddress("ph_pt2", &ph_pt2, &b_ph_pt2);
   fChain->SetBranchAddress("ph_eta1", &ph_eta1, &b_ph_eta1);
   fChain->SetBranchAddress("ph_eta2", &ph_eta2, &b_ph_eta2);
   fChain->SetBranchAddress("ph_phi1", &ph_phi1, &b_ph_phi1);
   fChain->SetBranchAddress("ph_phi2", &ph_phi2, &b_ph_phi2);
   fChain->SetBranchAddress("ph_convType1", &ph_convType1, &b_ph_convType1);
   fChain->SetBranchAddress("ph_convType2", &ph_convType2, &b_ph_convType2);
   fChain->SetBranchAddress("ph_isTight1", &ph_isTight1, &b_ph_isTight1);
   fChain->SetBranchAddress("ph_isTight2", &ph_isTight2, &b_ph_isTight2);
   fChain->SetBranchAddress("ph_iso1", &ph_iso1, &b_ph_iso1);
   fChain->SetBranchAddress("ph_iso2", &ph_iso2, &b_ph_iso2);
   fChain->SetBranchAddress("flag_passedIso", &flag_passedIso, &b_flag_passedIso);
   fChain->SetBranchAddress("cutFlow", &cutFlow, &b_cutFlow);
   fChain->SetBranchAddress("flag_passedPID", &flag_passedPID, &b_flag_passedPID);
   fChain->SetBranchAddress("m_jet_pt", &m_jet_pt, &b_m_jet_pt);
   fChain->SetBranchAddress("m_jet_eta", &m_jet_eta, &b_m_jet_eta);
   fChain->SetBranchAddress("m_jet_phi", &m_jet_phi, &b_m_jet_phi);
   fChain->SetBranchAddress("m_cateindex", &m_cateindex, &b_m_cateindex);
   fChain->SetBranchAddress("m_cateindex_dev", &m_cateindex_dev, &b_m_cateindex_dev);
   fChain->SetBranchAddress("RNDM", &RNDM, &b_RNDM);
   fChain->SetBranchAddress("BDTG", &BDTG, &b_BDTG);
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
