//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Sep 30 14:16:55 2018 by ROOT version 6.04/16
// from TTree output/output
// found on file: test.root
//////////////////////////////////////////////////////////

#ifndef truth_h
#define truth_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"

using namespace std;

class truth {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           m_mcChannelNumber;
   Int_t           runNumber;
   Int_t           eventNumber;
   Double_t        weight;
   Int_t           njets;
   Int_t           ntops;
   Int_t           nHiggs;
   Int_t           ny;
   vector<double>  *m_t_pt;
   vector<double>  *m_t_eta;
   vector<double>  *m_t_phi;
   vector<double>  *m_t_m;
   vector<double>  *m_t_E;
   vector<double>  *m_tx_pt;
   vector<double>  *m_tx_eta;
   vector<double>  *m_tx_phi;
   vector<double>  *m_tx_m;
   vector<double>  *m_tx_E;
   vector<double>  *m_W_pt;
   vector<double>  *m_W_eta;
   vector<double>  *m_W_phi;
   vector<double>  *m_W_m;
   vector<double>  *m_W_E;
   vector<double>  *m_Wx_pt;
   vector<double>  *m_Wx_eta;
   vector<double>  *m_Wx_phi;
   vector<double>  *m_Wx_m;
   vector<double>  *m_Wx_E;
   vector<double>  *m_b_pt;
   vector<double>  *m_b_eta;
   vector<double>  *m_b_phi;
   vector<double>  *m_b_m;
   vector<double>  *m_b_E;
   vector<double>  *m_bx_pt;
   vector<double>  *m_bx_eta;
   vector<double>  *m_bx_phi;
   vector<double>  *m_bx_m;
   vector<double>  *m_bx_E;
   vector<double>  *m_Wq_pt;
   vector<double>  *m_Wq_eta;
   vector<double>  *m_Wq_phi;
   vector<double>  *m_Wq_m;
   vector<double>  *m_Wq_E;
   vector<double>  *m_Wq_pdgId;
   vector<double>  *m_Wxq_pt;
   vector<double>  *m_Wxq_eta;
   vector<double>  *m_Wxq_phi;
   vector<double>  *m_Wxq_m;
   vector<double>  *m_Wxq_E;
   vector<double>  *m_Wxq_pdgId;
   vector<double>  *m_Wl_pt;
   vector<double>  *m_Wl_eta;
   vector<double>  *m_Wl_phi;
   vector<double>  *m_Wl_m;
   vector<double>  *m_Wl_E;
   vector<double>  *m_Wl_pdgId;
   vector<double>  *m_Wxl_pt;
   vector<double>  *m_Wxl_eta;
   vector<double>  *m_Wxl_phi;
   vector<double>  *m_Wxl_m;
   vector<double>  *m_Wxl_E;
   vector<double>  *m_Wxl_pdgId;
   vector<double>  *m_Wnu_pt;
   vector<double>  *m_Wnu_eta;
   vector<double>  *m_Wnu_phi;
   vector<double>  *m_Wnu_m;
   vector<double>  *m_Wnu_E;
   vector<double>  *m_Wnu_pdgId;
   vector<double>  *m_Wxnu_pt;
   vector<double>  *m_Wxnu_eta;
   vector<double>  *m_Wxnu_phi;
   vector<double>  *m_Wxnu_m;
   vector<double>  *m_Wxnu_E;
   vector<double>  *m_Wxnu_pdgId;
   vector<double>  *m_H_pt;
   vector<double>  *m_H_eta;
   vector<double>  *m_H_phi;
   vector<double>  *m_H_m;
   vector<double>  *m_H_E;
   vector<double>  *m_y_pt;
   vector<double>  *m_y_eta;
   vector<double>  *m_y_phi;
   vector<double>  *m_y_m;
   vector<double>  *m_y_E;
   vector<double>  *m_jet_pt;
   vector<double>  *m_jet_eta;
   vector<double>  *m_jet_phi;
   vector<double>  *m_jet_m;
   vector<double>  *m_jet_E;
   Double_t        delta_eta_top;
   Double_t        delta_phi_top;
   Double_t        m_ttH;
   Double_t        m_tH;
   Double_t        m_txH;
   Double_t        m_tt;

   // List of branches
   TBranch        *b_m_mcChannelNumber;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_njets;   //!
   TBranch        *b_ntops;   //!
   TBranch        *b_nHiggs;   //!
   TBranch        *b_ny;   //!
   TBranch        *b_m_t_pt;   //!
   TBranch        *b_m_t_eta;   //!
   TBranch        *b_m_t_phi;   //!
   TBranch        *b_m_t_m;   //!
   TBranch        *b_m_t_E;   //!
   TBranch        *b_m_tx_pt;   //!
   TBranch        *b_m_tx_eta;   //!
   TBranch        *b_m_tx_phi;   //!
   TBranch        *b_m_tx_m;   //!
   TBranch        *b_m_tx_E;   //!
   TBranch        *b_m_W_pt;   //!
   TBranch        *b_m_W_eta;   //!
   TBranch        *b_m_W_phi;   //!
   TBranch        *b_m_W_m;   //!
   TBranch        *b_m_W_E;   //!
   TBranch        *b_m_Wx_pt;   //!
   TBranch        *b_m_Wx_eta;   //!
   TBranch        *b_m_Wx_phi;   //!
   TBranch        *b_m_Wx_m;   //!
   TBranch        *b_m_Wx_E;   //!
   TBranch        *b_m_b_pt;   //!
   TBranch        *b_m_b_eta;   //!
   TBranch        *b_m_b_phi;   //!
   TBranch        *b_m_b_m;   //!
   TBranch        *b_m_b_E;   //!
   TBranch        *b_m_bx_pt;   //!
   TBranch        *b_m_bx_eta;   //!
   TBranch        *b_m_bx_phi;   //!
   TBranch        *b_m_bx_m;   //!
   TBranch        *b_m_bx_E;   //!
   TBranch        *b_m_Wq_pt;   //!
   TBranch        *b_m_Wq_eta;   //!
   TBranch        *b_m_Wq_phi;   //!
   TBranch        *b_m_Wq_m;   //!
   TBranch        *b_m_Wq_E;   //!
   TBranch        *b_m_Wq_pdgId;   //!
   TBranch        *b_m_Wxq_pt;   //!
   TBranch        *b_m_Wxq_eta;   //!
   TBranch        *b_m_Wxq_phi;   //!
   TBranch        *b_m_Wxq_m;   //!
   TBranch        *b_m_Wxq_E;   //!
   TBranch        *b_m_Wxq_pdgId;   //!
   TBranch        *b_m_Wl_pt;   //!
   TBranch        *b_m_Wl_eta;   //!
   TBranch        *b_m_Wl_phi;   //!
   TBranch        *b_m_Wl_m;   //!
   TBranch        *b_m_Wl_E;   //!
   TBranch        *b_m_Wl_pdgId;   //!
   TBranch        *b_m_Wxl_pt;   //!
   TBranch        *b_m_Wxl_eta;   //!
   TBranch        *b_m_Wxl_phi;   //!
   TBranch        *b_m_Wxl_m;   //!
   TBranch        *b_m_Wxl_E;   //!
   TBranch        *b_m_Wxl_pdgId;   //!
   TBranch        *b_m_Wnu_pt;   //!
   TBranch        *b_m_Wnu_eta;   //!
   TBranch        *b_m_Wnu_phi;   //!
   TBranch        *b_m_Wnu_m;   //!
   TBranch        *b_m_Wnu_E;   //!
   TBranch        *b_m_Wnu_pdgId;   //!
   TBranch        *b_m_Wxnu_pt;   //!
   TBranch        *b_m_Wxnu_eta;   //!
   TBranch        *b_m_Wxnu_phi;   //!
   TBranch        *b_m_Wxnu_m;   //!
   TBranch        *b_m_Wxnu_E;   //!
   TBranch        *b_m_Wxnu_pdgId;   //!
   TBranch        *b_m_H_pt;   //!
   TBranch        *b_m_H_eta;   //!
   TBranch        *b_m_H_phi;   //!
   TBranch        *b_m_H_m;   //!
   TBranch        *b_m_H_E;   //!
   TBranch        *b_m_y_pt;   //!
   TBranch        *b_m_y_eta;   //!
   TBranch        *b_m_y_phi;   //!
   TBranch        *b_m_y_m;   //!
   TBranch        *b_m_y_E;   //!
   TBranch        *b_m_jet_pt;   //!
   TBranch        *b_m_jet_eta;   //!
   TBranch        *b_m_jet_phi;   //!
   TBranch        *b_m_jet_m;   //!
   TBranch        *b_m_jet_E;   //!
   TBranch        *b_delta_eta_top;   //!
   TBranch        *b_delta_phi_top;   //!
   TBranch        *b_m_ttH;   //!
   TBranch        *b_m_tH;   //!
   TBranch        *b_m_txH;   //!
   TBranch        *b_m_tt;   //!

   truth(TTree *tree=0);
   virtual ~truth();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef truth_cxx
truth::truth(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("test.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("test.root");
      }
      f->GetObject("output",tree);

   }
   Init(tree);
}

truth::~truth()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t truth::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t truth::LoadTree(Long64_t entry)
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

void truth::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   m_t_pt = 0;
   m_t_eta = 0;
   m_t_phi = 0;
   m_t_m = 0;
   m_t_E = 0;
   m_tx_pt = 0;
   m_tx_eta = 0;
   m_tx_phi = 0;
   m_tx_m = 0;
   m_tx_E = 0;
   m_W_pt = 0;
   m_W_eta = 0;
   m_W_phi = 0;
   m_W_m = 0;
   m_W_E = 0;
   m_Wx_pt = 0;
   m_Wx_eta = 0;
   m_Wx_phi = 0;
   m_Wx_m = 0;
   m_Wx_E = 0;
   m_b_pt = 0;
   m_b_eta = 0;
   m_b_phi = 0;
   m_b_m = 0;
   m_b_E = 0;
   m_bx_pt = 0;
   m_bx_eta = 0;
   m_bx_phi = 0;
   m_bx_m = 0;
   m_bx_E = 0;
   m_Wq_pt = 0;
   m_Wq_eta = 0;
   m_Wq_phi = 0;
   m_Wq_m = 0;
   m_Wq_E = 0;
   m_Wq_pdgId = 0;
   m_Wxq_pt = 0;
   m_Wxq_eta = 0;
   m_Wxq_phi = 0;
   m_Wxq_m = 0;
   m_Wxq_E = 0;
   m_Wxq_pdgId = 0;
   m_Wl_pt = 0;
   m_Wl_eta = 0;
   m_Wl_phi = 0;
   m_Wl_m = 0;
   m_Wl_E = 0;
   m_Wl_pdgId = 0;
   m_Wxl_pt = 0;
   m_Wxl_eta = 0;
   m_Wxl_phi = 0;
   m_Wxl_m = 0;
   m_Wxl_E = 0;
   m_Wxl_pdgId = 0;
   m_Wnu_pt = 0;
   m_Wnu_eta = 0;
   m_Wnu_phi = 0;
   m_Wnu_m = 0;
   m_Wnu_E = 0;
   m_Wnu_pdgId = 0;
   m_Wxnu_pt = 0;
   m_Wxnu_eta = 0;
   m_Wxnu_phi = 0;
   m_Wxnu_m = 0;
   m_Wxnu_E = 0;
   m_Wxnu_pdgId = 0;
   m_H_pt = 0;
   m_H_eta = 0;
   m_H_phi = 0;
   m_H_m = 0;
   m_H_E = 0;
   m_y_pt = 0;
   m_y_eta = 0;
   m_y_phi = 0;
   m_y_m = 0;
   m_y_E = 0;
   m_jet_pt = 0;
   m_jet_eta = 0;
   m_jet_phi = 0;
   m_jet_m = 0;
   m_jet_E = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("m_mcChannelNumber", &m_mcChannelNumber, &b_m_mcChannelNumber);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("njets", &njets, &b_njets);
   fChain->SetBranchAddress("ntops", &ntops, &b_ntops);
   fChain->SetBranchAddress("nHiggs", &nHiggs, &b_nHiggs);
   fChain->SetBranchAddress("ny", &ny, &b_ny);
   fChain->SetBranchAddress("m_t_pt", &m_t_pt, &b_m_t_pt);
   fChain->SetBranchAddress("m_t_eta", &m_t_eta, &b_m_t_eta);
   fChain->SetBranchAddress("m_t_phi", &m_t_phi, &b_m_t_phi);
   fChain->SetBranchAddress("m_t_m", &m_t_m, &b_m_t_m);
   fChain->SetBranchAddress("m_t_E", &m_t_E, &b_m_t_E);
   fChain->SetBranchAddress("m_tx_pt", &m_tx_pt, &b_m_tx_pt);
   fChain->SetBranchAddress("m_tx_eta", &m_tx_eta, &b_m_tx_eta);
   fChain->SetBranchAddress("m_tx_phi", &m_tx_phi, &b_m_tx_phi);
   fChain->SetBranchAddress("m_tx_m", &m_tx_m, &b_m_tx_m);
   fChain->SetBranchAddress("m_tx_E", &m_tx_E, &b_m_tx_E);
   fChain->SetBranchAddress("m_W_pt", &m_W_pt, &b_m_W_pt);
   fChain->SetBranchAddress("m_W_eta", &m_W_eta, &b_m_W_eta);
   fChain->SetBranchAddress("m_W_phi", &m_W_phi, &b_m_W_phi);
   fChain->SetBranchAddress("m_W_m", &m_W_m, &b_m_W_m);
   fChain->SetBranchAddress("m_W_E", &m_W_E, &b_m_W_E);
   fChain->SetBranchAddress("m_Wx_pt", &m_Wx_pt, &b_m_Wx_pt);
   fChain->SetBranchAddress("m_Wx_eta", &m_Wx_eta, &b_m_Wx_eta);
   fChain->SetBranchAddress("m_Wx_phi", &m_Wx_phi, &b_m_Wx_phi);
   fChain->SetBranchAddress("m_Wx_m", &m_Wx_m, &b_m_Wx_m);
   fChain->SetBranchAddress("m_Wx_E", &m_Wx_E, &b_m_Wx_E);
   fChain->SetBranchAddress("m_b_pt", &m_b_pt, &b_m_b_pt);
   fChain->SetBranchAddress("m_b_eta", &m_b_eta, &b_m_b_eta);
   fChain->SetBranchAddress("m_b_phi", &m_b_phi, &b_m_b_phi);
   fChain->SetBranchAddress("m_b_m", &m_b_m, &b_m_b_m);
   fChain->SetBranchAddress("m_b_E", &m_b_E, &b_m_b_E);
   fChain->SetBranchAddress("m_bx_pt", &m_bx_pt, &b_m_bx_pt);
   fChain->SetBranchAddress("m_bx_eta", &m_bx_eta, &b_m_bx_eta);
   fChain->SetBranchAddress("m_bx_phi", &m_bx_phi, &b_m_bx_phi);
   fChain->SetBranchAddress("m_bx_m", &m_bx_m, &b_m_bx_m);
   fChain->SetBranchAddress("m_bx_E", &m_bx_E, &b_m_bx_E);
   fChain->SetBranchAddress("m_Wq_pt", &m_Wq_pt, &b_m_Wq_pt);
   fChain->SetBranchAddress("m_Wq_eta", &m_Wq_eta, &b_m_Wq_eta);
   fChain->SetBranchAddress("m_Wq_phi", &m_Wq_phi, &b_m_Wq_phi);
   fChain->SetBranchAddress("m_Wq_m", &m_Wq_m, &b_m_Wq_m);
   fChain->SetBranchAddress("m_Wq_E", &m_Wq_E, &b_m_Wq_E);
   fChain->SetBranchAddress("m_Wq_pdgId", &m_Wq_pdgId, &b_m_Wq_pdgId);
   fChain->SetBranchAddress("m_Wxq_pt", &m_Wxq_pt, &b_m_Wxq_pt);
   fChain->SetBranchAddress("m_Wxq_eta", &m_Wxq_eta, &b_m_Wxq_eta);
   fChain->SetBranchAddress("m_Wxq_phi", &m_Wxq_phi, &b_m_Wxq_phi);
   fChain->SetBranchAddress("m_Wxq_m", &m_Wxq_m, &b_m_Wxq_m);
   fChain->SetBranchAddress("m_Wxq_E", &m_Wxq_E, &b_m_Wxq_E);
   fChain->SetBranchAddress("m_Wxq_pdgId", &m_Wxq_pdgId, &b_m_Wxq_pdgId);
   fChain->SetBranchAddress("m_Wl_pt", &m_Wl_pt, &b_m_Wl_pt);
   fChain->SetBranchAddress("m_Wl_eta", &m_Wl_eta, &b_m_Wl_eta);
   fChain->SetBranchAddress("m_Wl_phi", &m_Wl_phi, &b_m_Wl_phi);
   fChain->SetBranchAddress("m_Wl_m", &m_Wl_m, &b_m_Wl_m);
   fChain->SetBranchAddress("m_Wl_E", &m_Wl_E, &b_m_Wl_E);
   fChain->SetBranchAddress("m_Wl_pdgId", &m_Wl_pdgId, &b_m_Wl_pdgId);
   fChain->SetBranchAddress("m_Wxl_pt", &m_Wxl_pt, &b_m_Wxl_pt);
   fChain->SetBranchAddress("m_Wxl_eta", &m_Wxl_eta, &b_m_Wxl_eta);
   fChain->SetBranchAddress("m_Wxl_phi", &m_Wxl_phi, &b_m_Wxl_phi);
   fChain->SetBranchAddress("m_Wxl_m", &m_Wxl_m, &b_m_Wxl_m);
   fChain->SetBranchAddress("m_Wxl_E", &m_Wxl_E, &b_m_Wxl_E);
   fChain->SetBranchAddress("m_Wxl_pdgId", &m_Wxl_pdgId, &b_m_Wxl_pdgId);
   fChain->SetBranchAddress("m_Wnu_pt", &m_Wnu_pt, &b_m_Wnu_pt);
   fChain->SetBranchAddress("m_Wnu_eta", &m_Wnu_eta, &b_m_Wnu_eta);
   fChain->SetBranchAddress("m_Wnu_phi", &m_Wnu_phi, &b_m_Wnu_phi);
   fChain->SetBranchAddress("m_Wnu_m", &m_Wnu_m, &b_m_Wnu_m);
   fChain->SetBranchAddress("m_Wnu_E", &m_Wnu_E, &b_m_Wnu_E);
   fChain->SetBranchAddress("m_Wnu_pdgId", &m_Wnu_pdgId, &b_m_Wnu_pdgId);
   fChain->SetBranchAddress("m_Wxnu_pt", &m_Wxnu_pt, &b_m_Wxnu_pt);
   fChain->SetBranchAddress("m_Wxnu_eta", &m_Wxnu_eta, &b_m_Wxnu_eta);
   fChain->SetBranchAddress("m_Wxnu_phi", &m_Wxnu_phi, &b_m_Wxnu_phi);
   fChain->SetBranchAddress("m_Wxnu_m", &m_Wxnu_m, &b_m_Wxnu_m);
   fChain->SetBranchAddress("m_Wxnu_E", &m_Wxnu_E, &b_m_Wxnu_E);
   fChain->SetBranchAddress("m_Wxnu_pdgId", &m_Wxnu_pdgId, &b_m_Wxnu_pdgId);
   fChain->SetBranchAddress("m_H_pt", &m_H_pt, &b_m_H_pt);
   fChain->SetBranchAddress("m_H_eta", &m_H_eta, &b_m_H_eta);
   fChain->SetBranchAddress("m_H_phi", &m_H_phi, &b_m_H_phi);
   fChain->SetBranchAddress("m_H_m", &m_H_m, &b_m_H_m);
   fChain->SetBranchAddress("m_H_E", &m_H_E, &b_m_H_E);
   fChain->SetBranchAddress("m_y_pt", &m_y_pt, &b_m_y_pt);
   fChain->SetBranchAddress("m_y_eta", &m_y_eta, &b_m_y_eta);
   fChain->SetBranchAddress("m_y_phi", &m_y_phi, &b_m_y_phi);
   fChain->SetBranchAddress("m_y_m", &m_y_m, &b_m_y_m);
   fChain->SetBranchAddress("m_y_E", &m_y_E, &b_m_y_E);
   fChain->SetBranchAddress("m_jet_pt", &m_jet_pt, &b_m_jet_pt);
   fChain->SetBranchAddress("m_jet_eta", &m_jet_eta, &b_m_jet_eta);
   fChain->SetBranchAddress("m_jet_phi", &m_jet_phi, &b_m_jet_phi);
   fChain->SetBranchAddress("m_jet_m", &m_jet_m, &b_m_jet_m);
   fChain->SetBranchAddress("m_jet_E", &m_jet_E, &b_m_jet_E);
   fChain->SetBranchAddress("delta_eta_top", &delta_eta_top, &b_delta_eta_top);
   fChain->SetBranchAddress("delta_phi_top", &delta_phi_top, &b_delta_phi_top);
   fChain->SetBranchAddress("m_ttH", &m_ttH, &b_m_ttH);
   fChain->SetBranchAddress("m_tH", &m_tH, &b_m_tH);
   fChain->SetBranchAddress("m_txH", &m_txH, &b_m_txH);
   fChain->SetBranchAddress("m_tt", &m_tt, &b_m_tt);
   Notify();
}

Bool_t truth::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void truth::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t truth::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef truth_cxx
