//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Nov 16 10:44:00 2018 by ROOT version 6.04/16
// from TTree DiMuonNtuple/DiMuon Selection Ntuple
// found on file: Hmumu/eos/common_ntuples/v17/mc16d.363123.root
//////////////////////////////////////////////////////////

#ifndef DiMuonNtuple_h
#define DiMuonNtuple_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "TVectorT.h"
#include "TMatrixT.h"
#include "vector"
#include "vector"

class DiMuonNtuple {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           MetaData_IsFullSim;
   UInt_t          EventInfo_RunNumber;
   Int_t           EventInfo_ChannelNumber;
   Int_t           EventInfo_LumiBlock;
   ULong64_t       EventInfo_EventNumber;
   Float_t         Event_AverageMu;
   Float_t         Event_ActualMu;
   Float_t         EventWeight_PileupWeight;
   Float_t         EventWeight_MCEventWeight;
   Float_t         Muons_PT_Lead;
   Float_t         Muons_PT_Sub;
   Float_t         Muons_Eta_Lead;
   Float_t         Muons_Eta_Sub;
   Float_t         Muons_Phi_Lead;
   Float_t         Muons_Phi_Sub;
   Int_t           Muons_Charge_Lead;
   Int_t           Muons_Charge_Sub;
   Float_t         Muons_Type_Lead;
   Float_t         Muons_Type_Sub;
   Float_t         Muons_PassLoose_Lead;
   Float_t         Muons_PassLoose_Sub;
   Float_t         Muons_PassMedium_Lead;
   Float_t         Muons_PassMedium_Sub;
   Int_t           Muons_Multip;
   Float_t         Muons_MCPExpReso_NoSmear_Lead;
   Float_t         Muons_MCPExpReso_NoSmear_Sub;
   Float_t         Muons_MCPExpReso_NoSmear_Minv_MuMu_Sigma;
   Float_t         Muons_MCPExpReso_Smear_Lead;
   Float_t         Muons_MCPExpReso_Smear_Sub;
   Float_t         Muons_MCPExpReso_Smear_Minv_MuMu_Sigma;
   Float_t         Muons_Minv_MuMu;
   Float_t         Muons_Minv_MuMu_Fsr;
   Float_t         Muons_DeltaEta_MuMu;
   Float_t         Muons_DeltaPhi_MuMu;
   Float_t         Muons_DeltaR_MuMu;
   Float_t         Muons_CosThetaStar;
   TVectorD        *Muons_CombFit_FullVec_Lead;
   TVectorD        *Muons_CombFit_FullVec_Sub;
   TMatrixD        *Muons_CombFit_FullCov_Lead;
   TMatrixD        *Muons_CombFit_FullCov_Sub;
   Float_t         Muons_CombFit_Lead_QoverP;
   Float_t         Muons_CombFit_Sub_QoverP;
   Float_t         Muons_CombFit_Lead_QoverP_Sigma;
   Float_t         Muons_CombFit_Sub_QoverP_Sigma;
   Float_t         Muons_CombFit_Minv_MuMu;
   Float_t         Muons_CombFit_Minv_MuMu_Sigma;
   Float_t         Muons_CombFit_Lead_Smear_Reso;
   Float_t         Muons_CombFit_Sub_Smear_Reso;
   Float_t         Muons_CombFit_Minv_MuMu_Smear_Sigma;
   Float_t         FSR_Et;
   Float_t         FSR_Eta;
   Float_t         FSR_Phi;
   Float_t         FSR_f1;
   Float_t         FSR_DeltaR;
   Int_t           FSR_Type;
   Int_t           FSR_IsPhoton;
   Float_t         Jets_E_Lead;
   Float_t         Jets_E_Sub;
   Float_t         Jets_PT_Lead;
   Float_t         Jets_PT_Sub;
   Float_t         Jets_Eta_Lead;
   Float_t         Jets_Eta_Sub;
   Float_t         Jets_Phi_Lead;
   Float_t         Jets_Phi_Sub;
   Int_t           Jets_PassFJVT_Lead;
   Int_t           Jets_PassFJVT_Sub;
   Float_t         Jets_FJVT_Lead;
   Float_t         Jets_FJVT_Sub;
   Float_t         Jets_JVT_Lead;
   Float_t         Jets_JVT_Sub;
   Int_t           Jets_jetMultip;
   Float_t         Jets_PT_jj;
   Float_t         Jets_Minv_jj;
   Float_t         Jets_etaj1_x_etaj2;
   Float_t         Jets_DeltaEta_jj;
   Float_t         Jets_DeltaPhi_jj;
   Float_t         Jets_DeltaR_jj;
   Float_t         Z_PT;
   Float_t         Z_Eta;
   Float_t         Z_Phi;
   Float_t         Z_Y;
   Float_t         Z_PT_FSR;
   Float_t         Z_Eta_FSR;
   Float_t         Z_Phi_FSR;
   Float_t         Z_Y_FSR;
   Float_t         Event_Ht;
   Float_t         Event_MET;
   Float_t         Event_MET_Phi;
   Float_t         Event_MET_Sig;
   Float_t         Event_Centrality;
   Float_t         Event_PT_MuMujj;
   Float_t         Event_PT_MuMuj1;
   Float_t         Event_PT_MuMuj2;
   Float_t         Event_Y_MuMujj;
   Float_t         Event_Y_MuMuj1;
   Float_t         Event_Y_MuMuj2;
   Int_t           Event_HasBJet;
   Int_t           Event_OldCategory;
   Float_t         Truth_PT_Lead_Muon;
   Float_t         Truth_PT_Sub_Muon;
   Float_t         Truth_Eta_Lead_Muon;
   Float_t         Truth_Eta_Sub_Muon;
   Float_t         Truth_Phi_Lead_Muon;
   Float_t         Truth_Phi_Sub_Muon;
   Int_t           Truth_Status_Lead_Muon;
   Int_t           Truth_Status_Sub_Muon;
   Float_t         Truth_Minv_MuMu;
   Float_t         Truth_QoverP_Lead_Muon;
   Float_t         Truth_QoverP_Sub_Muon;
   vector<float>   *Muons_Pos_PT;
   vector<float>   *Muons_Pos_Eta;
   vector<float>   *Muons_Pos_Phi;
   vector<float>   *Muons_Pos_E;
   vector<float>   *Muons_Pos_PromptLeptonIso;
   vector<float>   *Muons_Pos_PromptLeptonVeto;
   vector<float>   *Muons_Neg_PT;
   vector<float>   *Muons_Neg_Eta;
   vector<float>   *Muons_Neg_Phi;
   vector<float>   *Muons_Neg_E;
   vector<float>   *Muons_Neg_PromptLeptonIso;
   vector<float>   *Muons_Neg_PromptLeptonVeto;
   vector<float>   *Electrons_Pos_PT;
   vector<float>   *Electrons_Pos_Eta;
   vector<float>   *Electrons_Pos_Phi;
   vector<float>   *Electrons_Pos_E;
   vector<float>   *Electrons_Pos_PromptLeptonIso;
   vector<float>   *Electrons_Pos_PromptLeptonVeto;
   vector<float>   *Electrons_Neg_PT;
   vector<float>   *Electrons_Neg_Eta;
   vector<float>   *Electrons_Neg_Phi;
   vector<float>   *Electrons_Neg_E;
   vector<float>   *Electrons_Neg_PromptLeptonIso;
   vector<float>   *Electrons_Neg_PromptLeptonVeto;
   vector<float>   *Jets_PT;
   vector<float>   *Jets_Eta;
   vector<float>   *Jets_Phi;
   vector<float>   *Jets_E;
   vector<int>     *Jets_LowestPassedBTagOP;
   Float_t         TotalWeight;
   Float_t         TriggerSFWeight;
   Float_t         MuonSFWeight;
   Float_t         ElectronSFWeight;
   Float_t         JetSFWeight;
   Float_t         GlobalWeight;

   // List of branches
   TBranch        *b_MetaData_IsFullSim;   //!
   TBranch        *b_EventInfo_RunNumber;   //!
   TBranch        *b_EventInfo_ChannelNumber;   //!
   TBranch        *b_EventInfo_LumiBlock;   //!
   TBranch        *b_EventInfo_EventNumber;   //!
   TBranch        *b_Event_AverageMu;   //!
   TBranch        *b_Event_ActualMu;   //!
   TBranch        *b_EventWeight_PileupWeight;   //!
   TBranch        *b_EventWeight_MCEventWeight;   //!
   TBranch        *b_Muons_PT_Lead;   //!
   TBranch        *b_Muons_PT_Sub;   //!
   TBranch        *b_Muons_Eta_Lead;   //!
   TBranch        *b_Muons_Eta_Sub;   //!
   TBranch        *b_Muons_Phi_Lead;   //!
   TBranch        *b_Muons_Phi_Sub;   //!
   TBranch        *b_Muons_Charge_Lead;   //!
   TBranch        *b_Muons_Charge_Sub;   //!
   TBranch        *b_Muons_Type_Lead;   //!
   TBranch        *b_Muons_Type_Sub;   //!
   TBranch        *b_Muons_PassLoose_Lead;   //!
   TBranch        *b_Muons_PassLoose_Sub;   //!
   TBranch        *b_Muons_PassMedium_Lead;   //!
   TBranch        *b_Muons_PassMedium_Sub;   //!
   TBranch        *b_Muons_Multip;   //!
   TBranch        *b_Muons_MCPExpReso_NoSmear_Lead;   //!
   TBranch        *b_Muons_MCPExpReso_NoSmear_Sub;   //!
   TBranch        *b_Muons_MCPExpReso_NoSmear_Minv_MuMu_Sigma;   //!
   TBranch        *b_Muons_MCPExpReso_Smear_Lead;   //!
   TBranch        *b_Muons_MCPExpReso_Smear_Sub;   //!
   TBranch        *b_Muons_MCPExpReso_Smear_Minv_MuMu_Sigma;   //!
   TBranch        *b_Muons_Minv_MuMu;   //!
   TBranch        *b_Muons_Minv_MuMu_Fsr;   //!
   TBranch        *b_Muons_DeltaEta_MuMu;   //!
   TBranch        *b_Muons_DeltaPhi_MuMu;   //!
   TBranch        *b_Muons_DeltaR_MuMu;   //!
   TBranch        *b_Muons_CosThetaStar;   //!
   TBranch        *b_Muons_CombFit_FullVec_Lead;   //!
   TBranch        *b_Muons_CombFit_FullVec_Sub;   //!
   TBranch        *b_Muons_CombFit_FullCov_Lead;   //!
   TBranch        *b_Muons_CombFit_FullCov_Sub;   //!
   TBranch        *b_Muons_CombFit_Lead_QoverP;   //!
   TBranch        *b_Muons_CombFit_Sub_QoverP;   //!
   TBranch        *b_Muons_CombFit_Lead_QoverP_Sigma;   //!
   TBranch        *b_Muons_CombFit_Sub_QoverP_Sigma;   //!
   TBranch        *b_Muons_CombFit_Minv_MuMu;   //!
   TBranch        *b_Muons_CombFit_Minv_MuMu_Sigma;   //!
   TBranch        *b_Muons_CombFit_Lead_Smear_Reso;   //!
   TBranch        *b_Muons_CombFit_Sub_Smear_Reso;   //!
   TBranch        *b_Muons_CombFit_Minv_MuMu_Smear_Sigma;   //!
   TBranch        *b_FSR_Et;   //!
   TBranch        *b_FSR_Eta;   //!
   TBranch        *b_FSR_Phi;   //!
   TBranch        *b_FSR_f1;   //!
   TBranch        *b_FSR_DeltaR;   //!
   TBranch        *b_FSR_Type;   //!
   TBranch        *b_FSR_IsPhoton;   //!
   TBranch        *b_Jets_E_Lead;   //!
   TBranch        *b_Jets_E_Sub;   //!
   TBranch        *b_Jets_PT_Lead;   //!
   TBranch        *b_Jets_PT_Sub;   //!
   TBranch        *b_Jets_Eta_Lead;   //!
   TBranch        *b_Jets_Eta_Sub;   //!
   TBranch        *b_Jets_Phi_Lead;   //!
   TBranch        *b_Jets_Phi_Sub;   //!
   TBranch        *b_Jets_PassFJVT_Lead;   //!
   TBranch        *b_Jets_PassFJVT_Sub;   //!
   TBranch        *b_Jets_FJVT_Lead;   //!
   TBranch        *b_Jets_FJVT_Sub;   //!
   TBranch        *b_Jets_JVT_Lead;   //!
   TBranch        *b_Jets_JVT_Sub;   //!
   TBranch        *b_Jets_jetMultip;   //!
   TBranch        *b_Jets_PT_jj;   //!
   TBranch        *b_Jets_Minv_jj;   //!
   TBranch        *b_Jets_etaj1_x_etaj2;   //!
   TBranch        *b_Jets_DeltaEta_jj;   //!
   TBranch        *b_Jets_DeltaPhi_jj;   //!
   TBranch        *b_Jets_DeltaR_jj;   //!
   TBranch        *b_Z_PT;   //!
   TBranch        *b_Z_Eta;   //!
   TBranch        *b_Z_Phi;   //!
   TBranch        *b_Z_Y;   //!
   TBranch        *b_Z_PT_FSR;   //!
   TBranch        *b_Z_Eta_FSR;   //!
   TBranch        *b_Z_Phi_FSR;   //!
   TBranch        *b_Z_Y_FSR;   //!
   TBranch        *b_Event_Ht;   //!
   TBranch        *b_Event_MET;   //!
   TBranch        *b_Event_MET_Phi;   //!
   TBranch        *b_Event_MET_Sig;   //!
   TBranch        *b_Event_Centrality;   //!
   TBranch        *b_Event_PT_MuMujj;   //!
   TBranch        *b_Event_PT_MuMuj1;   //!
   TBranch        *b_Event_PT_MuMuj2;   //!
   TBranch        *b_Event_Y_MuMujj;   //!
   TBranch        *b_Event_Y_MuMuj1;   //!
   TBranch        *b_Event_Y_MuMuj2;   //!
   TBranch        *b_Event_HasBJet;   //!
   TBranch        *b_Event_OldCategory;   //!
   TBranch        *b_Truth_PT_Lead_Muon;   //!
   TBranch        *b_Truth_PT_Sub_Muon;   //!
   TBranch        *b_Truth_Eta_Lead_Muon;   //!
   TBranch        *b_Truth_Eta_Sub_Muon;   //!
   TBranch        *b_Truth_Phi_Lead_Muon;   //!
   TBranch        *b_Truth_Phi_Sub_Muon;   //!
   TBranch        *b_Truth_Status_Lead_Muon;   //!
   TBranch        *b_Truth_Status_Sub_Muon;   //!
   TBranch        *b_Truth_Minv_MuMu;   //!
   TBranch        *b_Truth_QoverP_Lead_Muon;   //!
   TBranch        *b_Truth_QoverP_Sub_Muon;   //!
   TBranch        *b_Muons_Pos_PT;   //!
   TBranch        *b_Muons_Pos_Eta;   //!
   TBranch        *b_Muons_Pos_Phi;   //!
   TBranch        *b_Muons_Pos_E;   //!
   TBranch        *b_Muons_Pos_PromptLeptonIso;   //!
   TBranch        *b_Muons_Pos_PromptLeptonVeto;   //!
   TBranch        *b_Muons_Neg_PT;   //!
   TBranch        *b_Muons_Neg_Eta;   //!
   TBranch        *b_Muons_Neg_Phi;   //!
   TBranch        *b_Muons_Neg_E;   //!
   TBranch        *b_Muons_Neg_PromptLeptonIso;   //!
   TBranch        *b_Muons_Neg_PromptLeptonVeto;   //!
   TBranch        *b_Electrons_Pos_PT;   //!
   TBranch        *b_Electrons_Pos_Eta;   //!
   TBranch        *b_Electrons_Pos_Phi;   //!
   TBranch        *b_Electrons_Pos_E;   //!
   TBranch        *b_Electrons_Pos_PromptLeptonIso;   //!
   TBranch        *b_Electrons_Pos_PromptLeptonVeto;   //!
   TBranch        *b_Electrons_Neg_PT;   //!
   TBranch        *b_Electrons_Neg_Eta;   //!
   TBranch        *b_Electrons_Neg_Phi;   //!
   TBranch        *b_Electrons_Neg_E;   //!
   TBranch        *b_Electrons_Neg_PromptLeptonIso;   //!
   TBranch        *b_Electrons_Neg_PromptLeptonVeto;   //!
   TBranch        *b_Jets_PT;   //!
   TBranch        *b_Jets_Eta;   //!
   TBranch        *b_Jets_Phi;   //!
   TBranch        *b_Jets_E;   //!
   TBranch        *b_Jets_LowestPassedBTagOP;   //!
   TBranch        *b_TotalWeight;   //!
   TBranch        *b_TriggerSFWeight;   //!
   TBranch        *b_MuonSFWeight;   //!
   TBranch        *b_ElectronSFWeight;   //!
   TBranch        *b_JetSFWeight;   //!
   TBranch        *b_GlobalWeight;   //!

   DiMuonNtuple(TTree *tree=0);
   virtual ~DiMuonNtuple();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef DiMuonNtuple_cxx
DiMuonNtuple::DiMuonNtuple(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Hmumu/eos/common_ntuples/v17/mc16d.363123.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("Hmumu/eos/common_ntuples/v17/mc16d.363123.root");
      }
      f->GetObject("DiMuonNtuple",tree);

   }
   Init(tree);
}

DiMuonNtuple::~DiMuonNtuple()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t DiMuonNtuple::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t DiMuonNtuple::LoadTree(Long64_t entry)
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

void DiMuonNtuple::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   Muons_CombFit_FullVec_Lead = 0;
   Muons_CombFit_FullVec_Sub = 0;
   Muons_CombFit_FullCov_Lead = 0;
   Muons_CombFit_FullCov_Sub = 0;
   Muons_Pos_PT = 0;
   Muons_Pos_Eta = 0;
   Muons_Pos_Phi = 0;
   Muons_Pos_E = 0;
   Muons_Pos_PromptLeptonIso = 0;
   Muons_Pos_PromptLeptonVeto = 0;
   Muons_Neg_PT = 0;
   Muons_Neg_Eta = 0;
   Muons_Neg_Phi = 0;
   Muons_Neg_E = 0;
   Muons_Neg_PromptLeptonIso = 0;
   Muons_Neg_PromptLeptonVeto = 0;
   Electrons_Pos_PT = 0;
   Electrons_Pos_Eta = 0;
   Electrons_Pos_Phi = 0;
   Electrons_Pos_E = 0;
   Electrons_Pos_PromptLeptonIso = 0;
   Electrons_Pos_PromptLeptonVeto = 0;
   Electrons_Neg_PT = 0;
   Electrons_Neg_Eta = 0;
   Electrons_Neg_Phi = 0;
   Electrons_Neg_E = 0;
   Electrons_Neg_PromptLeptonIso = 0;
   Electrons_Neg_PromptLeptonVeto = 0;
   Jets_PT = 0;
   Jets_Eta = 0;
   Jets_Phi = 0;
   Jets_E = 0;
   Jets_LowestPassedBTagOP = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("MetaData_IsFullSim", &MetaData_IsFullSim, &b_MetaData_IsFullSim);
   fChain->SetBranchAddress("EventInfo_RunNumber", &EventInfo_RunNumber, &b_EventInfo_RunNumber);
   fChain->SetBranchAddress("EventInfo_ChannelNumber", &EventInfo_ChannelNumber, &b_EventInfo_ChannelNumber);
   fChain->SetBranchAddress("EventInfo_LumiBlock", &EventInfo_LumiBlock, &b_EventInfo_LumiBlock);
   fChain->SetBranchAddress("EventInfo_EventNumber", &EventInfo_EventNumber, &b_EventInfo_EventNumber);
   fChain->SetBranchAddress("Event_AverageMu", &Event_AverageMu, &b_Event_AverageMu);
   fChain->SetBranchAddress("Event_ActualMu", &Event_ActualMu, &b_Event_ActualMu);
   fChain->SetBranchAddress("EventWeight_PileupWeight", &EventWeight_PileupWeight, &b_EventWeight_PileupWeight);
   fChain->SetBranchAddress("EventWeight_MCEventWeight", &EventWeight_MCEventWeight, &b_EventWeight_MCEventWeight);
   fChain->SetBranchAddress("Muons_PT_Lead", &Muons_PT_Lead, &b_Muons_PT_Lead);
   fChain->SetBranchAddress("Muons_PT_Sub", &Muons_PT_Sub, &b_Muons_PT_Sub);
   fChain->SetBranchAddress("Muons_Eta_Lead", &Muons_Eta_Lead, &b_Muons_Eta_Lead);
   fChain->SetBranchAddress("Muons_Eta_Sub", &Muons_Eta_Sub, &b_Muons_Eta_Sub);
   fChain->SetBranchAddress("Muons_Phi_Lead", &Muons_Phi_Lead, &b_Muons_Phi_Lead);
   fChain->SetBranchAddress("Muons_Phi_Sub", &Muons_Phi_Sub, &b_Muons_Phi_Sub);
   fChain->SetBranchAddress("Muons_Charge_Lead", &Muons_Charge_Lead, &b_Muons_Charge_Lead);
   fChain->SetBranchAddress("Muons_Charge_Sub", &Muons_Charge_Sub, &b_Muons_Charge_Sub);
   fChain->SetBranchAddress("Muons_Type_Lead", &Muons_Type_Lead, &b_Muons_Type_Lead);
   fChain->SetBranchAddress("Muons_Type_Sub", &Muons_Type_Sub, &b_Muons_Type_Sub);
   fChain->SetBranchAddress("Muons_PassLoose_Lead", &Muons_PassLoose_Lead, &b_Muons_PassLoose_Lead);
   fChain->SetBranchAddress("Muons_PassLoose_Sub", &Muons_PassLoose_Sub, &b_Muons_PassLoose_Sub);
   fChain->SetBranchAddress("Muons_PassMedium_Lead", &Muons_PassMedium_Lead, &b_Muons_PassMedium_Lead);
   fChain->SetBranchAddress("Muons_PassMedium_Sub", &Muons_PassMedium_Sub, &b_Muons_PassMedium_Sub);
   fChain->SetBranchAddress("Muons_Multip", &Muons_Multip, &b_Muons_Multip);
   fChain->SetBranchAddress("Muons_MCPExpReso_NoSmear_Lead", &Muons_MCPExpReso_NoSmear_Lead, &b_Muons_MCPExpReso_NoSmear_Lead);
   fChain->SetBranchAddress("Muons_MCPExpReso_NoSmear_Sub", &Muons_MCPExpReso_NoSmear_Sub, &b_Muons_MCPExpReso_NoSmear_Sub);
   fChain->SetBranchAddress("Muons_MCPExpReso_NoSmear_Minv_MuMu_Sigma", &Muons_MCPExpReso_NoSmear_Minv_MuMu_Sigma, &b_Muons_MCPExpReso_NoSmear_Minv_MuMu_Sigma);
   fChain->SetBranchAddress("Muons_MCPExpReso_Smear_Lead", &Muons_MCPExpReso_Smear_Lead, &b_Muons_MCPExpReso_Smear_Lead);
   fChain->SetBranchAddress("Muons_MCPExpReso_Smear_Sub", &Muons_MCPExpReso_Smear_Sub, &b_Muons_MCPExpReso_Smear_Sub);
   fChain->SetBranchAddress("Muons_MCPExpReso_Smear_Minv_MuMu_Sigma", &Muons_MCPExpReso_Smear_Minv_MuMu_Sigma, &b_Muons_MCPExpReso_Smear_Minv_MuMu_Sigma);
   fChain->SetBranchAddress("Muons_Minv_MuMu", &Muons_Minv_MuMu, &b_Muons_Minv_MuMu);
   fChain->SetBranchAddress("Muons_Minv_MuMu_Fsr", &Muons_Minv_MuMu_Fsr, &b_Muons_Minv_MuMu_Fsr);
   fChain->SetBranchAddress("Muons_DeltaEta_MuMu", &Muons_DeltaEta_MuMu, &b_Muons_DeltaEta_MuMu);
   fChain->SetBranchAddress("Muons_DeltaPhi_MuMu", &Muons_DeltaPhi_MuMu, &b_Muons_DeltaPhi_MuMu);
   fChain->SetBranchAddress("Muons_DeltaR_MuMu", &Muons_DeltaR_MuMu, &b_Muons_DeltaR_MuMu);
   fChain->SetBranchAddress("Muons_CosThetaStar", &Muons_CosThetaStar, &b_Muons_CosThetaStar);
   fChain->SetBranchAddress("Muons_CombFit_FullVec_Lead", &Muons_CombFit_FullVec_Lead, &b_Muons_CombFit_FullVec_Lead);
   fChain->SetBranchAddress("Muons_CombFit_FullVec_Sub", &Muons_CombFit_FullVec_Sub, &b_Muons_CombFit_FullVec_Sub);
   fChain->SetBranchAddress("Muons_CombFit_FullCov_Lead", &Muons_CombFit_FullCov_Lead, &b_Muons_CombFit_FullCov_Lead);
   fChain->SetBranchAddress("Muons_CombFit_FullCov_Sub", &Muons_CombFit_FullCov_Sub, &b_Muons_CombFit_FullCov_Sub);
   fChain->SetBranchAddress("Muons_CombFit_Lead_QoverP", &Muons_CombFit_Lead_QoverP, &b_Muons_CombFit_Lead_QoverP);
   fChain->SetBranchAddress("Muons_CombFit_Sub_QoverP", &Muons_CombFit_Sub_QoverP, &b_Muons_CombFit_Sub_QoverP);
   fChain->SetBranchAddress("Muons_CombFit_Lead_QoverP_Sigma", &Muons_CombFit_Lead_QoverP_Sigma, &b_Muons_CombFit_Lead_QoverP_Sigma);
   fChain->SetBranchAddress("Muons_CombFit_Sub_QoverP_Sigma", &Muons_CombFit_Sub_QoverP_Sigma, &b_Muons_CombFit_Sub_QoverP_Sigma);
   fChain->SetBranchAddress("Muons_CombFit_Minv_MuMu", &Muons_CombFit_Minv_MuMu, &b_Muons_CombFit_Minv_MuMu);
   fChain->SetBranchAddress("Muons_CombFit_Minv_MuMu_Sigma", &Muons_CombFit_Minv_MuMu_Sigma, &b_Muons_CombFit_Minv_MuMu_Sigma);
   fChain->SetBranchAddress("Muons_CombFit_Lead_Smear_Reso", &Muons_CombFit_Lead_Smear_Reso, &b_Muons_CombFit_Lead_Smear_Reso);
   fChain->SetBranchAddress("Muons_CombFit_Sub_Smear_Reso", &Muons_CombFit_Sub_Smear_Reso, &b_Muons_CombFit_Sub_Smear_Reso);
   fChain->SetBranchAddress("Muons_CombFit_Minv_MuMu_Smear_Sigma", &Muons_CombFit_Minv_MuMu_Smear_Sigma, &b_Muons_CombFit_Minv_MuMu_Smear_Sigma);
   fChain->SetBranchAddress("FSR_Et", &FSR_Et, &b_FSR_Et);
   fChain->SetBranchAddress("FSR_Eta", &FSR_Eta, &b_FSR_Eta);
   fChain->SetBranchAddress("FSR_Phi", &FSR_Phi, &b_FSR_Phi);
   fChain->SetBranchAddress("FSR_f1", &FSR_f1, &b_FSR_f1);
   fChain->SetBranchAddress("FSR_DeltaR", &FSR_DeltaR, &b_FSR_DeltaR);
   fChain->SetBranchAddress("FSR_Type", &FSR_Type, &b_FSR_Type);
   fChain->SetBranchAddress("FSR_IsPhoton", &FSR_IsPhoton, &b_FSR_IsPhoton);
   fChain->SetBranchAddress("Jets_E_Lead", &Jets_E_Lead, &b_Jets_E_Lead);
   fChain->SetBranchAddress("Jets_E_Sub", &Jets_E_Sub, &b_Jets_E_Sub);
   fChain->SetBranchAddress("Jets_PT_Lead", &Jets_PT_Lead, &b_Jets_PT_Lead);
   fChain->SetBranchAddress("Jets_PT_Sub", &Jets_PT_Sub, &b_Jets_PT_Sub);
   fChain->SetBranchAddress("Jets_Eta_Lead", &Jets_Eta_Lead, &b_Jets_Eta_Lead);
   fChain->SetBranchAddress("Jets_Eta_Sub", &Jets_Eta_Sub, &b_Jets_Eta_Sub);
   fChain->SetBranchAddress("Jets_Phi_Lead", &Jets_Phi_Lead, &b_Jets_Phi_Lead);
   fChain->SetBranchAddress("Jets_Phi_Sub", &Jets_Phi_Sub, &b_Jets_Phi_Sub);
   fChain->SetBranchAddress("Jets_PassFJVT_Lead", &Jets_PassFJVT_Lead, &b_Jets_PassFJVT_Lead);
   fChain->SetBranchAddress("Jets_PassFJVT_Sub", &Jets_PassFJVT_Sub, &b_Jets_PassFJVT_Sub);
   fChain->SetBranchAddress("Jets_FJVT_Lead", &Jets_FJVT_Lead, &b_Jets_FJVT_Lead);
   fChain->SetBranchAddress("Jets_FJVT_Sub", &Jets_FJVT_Sub, &b_Jets_FJVT_Sub);
   fChain->SetBranchAddress("Jets_JVT_Lead", &Jets_JVT_Lead, &b_Jets_JVT_Lead);
   fChain->SetBranchAddress("Jets_JVT_Sub", &Jets_JVT_Sub, &b_Jets_JVT_Sub);
   fChain->SetBranchAddress("Jets_jetMultip", &Jets_jetMultip, &b_Jets_jetMultip);
   fChain->SetBranchAddress("Jets_PT_jj", &Jets_PT_jj, &b_Jets_PT_jj);
   fChain->SetBranchAddress("Jets_Minv_jj", &Jets_Minv_jj, &b_Jets_Minv_jj);
   fChain->SetBranchAddress("Jets_etaj1_x_etaj2", &Jets_etaj1_x_etaj2, &b_Jets_etaj1_x_etaj2);
   fChain->SetBranchAddress("Jets_DeltaEta_jj", &Jets_DeltaEta_jj, &b_Jets_DeltaEta_jj);
   fChain->SetBranchAddress("Jets_DeltaPhi_jj", &Jets_DeltaPhi_jj, &b_Jets_DeltaPhi_jj);
   fChain->SetBranchAddress("Jets_DeltaR_jj", &Jets_DeltaR_jj, &b_Jets_DeltaR_jj);
   fChain->SetBranchAddress("Z_PT", &Z_PT, &b_Z_PT);
   fChain->SetBranchAddress("Z_Eta", &Z_Eta, &b_Z_Eta);
   fChain->SetBranchAddress("Z_Phi", &Z_Phi, &b_Z_Phi);
   fChain->SetBranchAddress("Z_Y", &Z_Y, &b_Z_Y);
   fChain->SetBranchAddress("Z_PT_FSR", &Z_PT_FSR, &b_Z_PT_FSR);
   fChain->SetBranchAddress("Z_Eta_FSR", &Z_Eta_FSR, &b_Z_Eta_FSR);
   fChain->SetBranchAddress("Z_Phi_FSR", &Z_Phi_FSR, &b_Z_Phi_FSR);
   fChain->SetBranchAddress("Z_Y_FSR", &Z_Y_FSR, &b_Z_Y_FSR);
   fChain->SetBranchAddress("Event_Ht", &Event_Ht, &b_Event_Ht);
   fChain->SetBranchAddress("Event_MET", &Event_MET, &b_Event_MET);
   fChain->SetBranchAddress("Event_MET_Phi", &Event_MET_Phi, &b_Event_MET_Phi);
   fChain->SetBranchAddress("Event_MET_Sig", &Event_MET_Sig, &b_Event_MET_Sig);
   fChain->SetBranchAddress("Event_Centrality", &Event_Centrality, &b_Event_Centrality);
   fChain->SetBranchAddress("Event_PT_MuMujj", &Event_PT_MuMujj, &b_Event_PT_MuMujj);
   fChain->SetBranchAddress("Event_PT_MuMuj1", &Event_PT_MuMuj1, &b_Event_PT_MuMuj1);
   fChain->SetBranchAddress("Event_PT_MuMuj2", &Event_PT_MuMuj2, &b_Event_PT_MuMuj2);
   fChain->SetBranchAddress("Event_Y_MuMujj", &Event_Y_MuMujj, &b_Event_Y_MuMujj);
   fChain->SetBranchAddress("Event_Y_MuMuj1", &Event_Y_MuMuj1, &b_Event_Y_MuMuj1);
   fChain->SetBranchAddress("Event_Y_MuMuj2", &Event_Y_MuMuj2, &b_Event_Y_MuMuj2);
   fChain->SetBranchAddress("Event_HasBJet", &Event_HasBJet, &b_Event_HasBJet);
   fChain->SetBranchAddress("Event_OldCategory", &Event_OldCategory, &b_Event_OldCategory);
   fChain->SetBranchAddress("Truth_PT_Lead_Muon", &Truth_PT_Lead_Muon, &b_Truth_PT_Lead_Muon);
   fChain->SetBranchAddress("Truth_PT_Sub_Muon", &Truth_PT_Sub_Muon, &b_Truth_PT_Sub_Muon);
   fChain->SetBranchAddress("Truth_Eta_Lead_Muon", &Truth_Eta_Lead_Muon, &b_Truth_Eta_Lead_Muon);
   fChain->SetBranchAddress("Truth_Eta_Sub_Muon", &Truth_Eta_Sub_Muon, &b_Truth_Eta_Sub_Muon);
   fChain->SetBranchAddress("Truth_Phi_Lead_Muon", &Truth_Phi_Lead_Muon, &b_Truth_Phi_Lead_Muon);
   fChain->SetBranchAddress("Truth_Phi_Sub_Muon", &Truth_Phi_Sub_Muon, &b_Truth_Phi_Sub_Muon);
   fChain->SetBranchAddress("Truth_Status_Lead_Muon", &Truth_Status_Lead_Muon, &b_Truth_Status_Lead_Muon);
   fChain->SetBranchAddress("Truth_Status_Sub_Muon", &Truth_Status_Sub_Muon, &b_Truth_Status_Sub_Muon);
   fChain->SetBranchAddress("Truth_Minv_MuMu", &Truth_Minv_MuMu, &b_Truth_Minv_MuMu);
   fChain->SetBranchAddress("Truth_QoverP_Lead_Muon", &Truth_QoverP_Lead_Muon, &b_Truth_QoverP_Lead_Muon);
   fChain->SetBranchAddress("Truth_QoverP_Sub_Muon", &Truth_QoverP_Sub_Muon, &b_Truth_QoverP_Sub_Muon);
   fChain->SetBranchAddress("Muons_Pos_PT", &Muons_Pos_PT, &b_Muons_Pos_PT);
   fChain->SetBranchAddress("Muons_Pos_Eta", &Muons_Pos_Eta, &b_Muons_Pos_Eta);
   fChain->SetBranchAddress("Muons_Pos_Phi", &Muons_Pos_Phi, &b_Muons_Pos_Phi);
   fChain->SetBranchAddress("Muons_Pos_E", &Muons_Pos_E, &b_Muons_Pos_E);
   fChain->SetBranchAddress("Muons_Pos_PromptLeptonIso", &Muons_Pos_PromptLeptonIso, &b_Muons_Pos_PromptLeptonIso);
   fChain->SetBranchAddress("Muons_Pos_PromptLeptonVeto", &Muons_Pos_PromptLeptonVeto, &b_Muons_Pos_PromptLeptonVeto);
   fChain->SetBranchAddress("Muons_Neg_PT", &Muons_Neg_PT, &b_Muons_Neg_PT);
   fChain->SetBranchAddress("Muons_Neg_Eta", &Muons_Neg_Eta, &b_Muons_Neg_Eta);
   fChain->SetBranchAddress("Muons_Neg_Phi", &Muons_Neg_Phi, &b_Muons_Neg_Phi);
   fChain->SetBranchAddress("Muons_Neg_E", &Muons_Neg_E, &b_Muons_Neg_E);
   fChain->SetBranchAddress("Muons_Neg_PromptLeptonIso", &Muons_Neg_PromptLeptonIso, &b_Muons_Neg_PromptLeptonIso);
   fChain->SetBranchAddress("Muons_Neg_PromptLeptonVeto", &Muons_Neg_PromptLeptonVeto, &b_Muons_Neg_PromptLeptonVeto);
   fChain->SetBranchAddress("Electrons_Pos_PT", &Electrons_Pos_PT, &b_Electrons_Pos_PT);
   fChain->SetBranchAddress("Electrons_Pos_Eta", &Electrons_Pos_Eta, &b_Electrons_Pos_Eta);
   fChain->SetBranchAddress("Electrons_Pos_Phi", &Electrons_Pos_Phi, &b_Electrons_Pos_Phi);
   fChain->SetBranchAddress("Electrons_Pos_E", &Electrons_Pos_E, &b_Electrons_Pos_E);
   fChain->SetBranchAddress("Electrons_Pos_PromptLeptonIso", &Electrons_Pos_PromptLeptonIso, &b_Electrons_Pos_PromptLeptonIso);
   fChain->SetBranchAddress("Electrons_Pos_PromptLeptonVeto", &Electrons_Pos_PromptLeptonVeto, &b_Electrons_Pos_PromptLeptonVeto);
   fChain->SetBranchAddress("Electrons_Neg_PT", &Electrons_Neg_PT, &b_Electrons_Neg_PT);
   fChain->SetBranchAddress("Electrons_Neg_Eta", &Electrons_Neg_Eta, &b_Electrons_Neg_Eta);
   fChain->SetBranchAddress("Electrons_Neg_Phi", &Electrons_Neg_Phi, &b_Electrons_Neg_Phi);
   fChain->SetBranchAddress("Electrons_Neg_E", &Electrons_Neg_E, &b_Electrons_Neg_E);
   fChain->SetBranchAddress("Electrons_Neg_PromptLeptonIso", &Electrons_Neg_PromptLeptonIso, &b_Electrons_Neg_PromptLeptonIso);
   fChain->SetBranchAddress("Electrons_Neg_PromptLeptonVeto", &Electrons_Neg_PromptLeptonVeto, &b_Electrons_Neg_PromptLeptonVeto);
   fChain->SetBranchAddress("Jets_PT", &Jets_PT, &b_Jets_PT);
   fChain->SetBranchAddress("Jets_Eta", &Jets_Eta, &b_Jets_Eta);
   fChain->SetBranchAddress("Jets_Phi", &Jets_Phi, &b_Jets_Phi);
   fChain->SetBranchAddress("Jets_E", &Jets_E, &b_Jets_E);
   fChain->SetBranchAddress("Jets_LowestPassedBTagOP", &Jets_LowestPassedBTagOP, &b_Jets_LowestPassedBTagOP);
   fChain->SetBranchAddress("TotalWeight", &TotalWeight, &b_TotalWeight);
   fChain->SetBranchAddress("TriggerSFWeight", &TriggerSFWeight, &b_TriggerSFWeight);
   fChain->SetBranchAddress("MuonSFWeight", &MuonSFWeight, &b_MuonSFWeight);
   fChain->SetBranchAddress("ElectronSFWeight", &ElectronSFWeight, &b_ElectronSFWeight);
   fChain->SetBranchAddress("JetSFWeight", &JetSFWeight, &b_JetSFWeight);
   fChain->SetBranchAddress("GlobalWeight", &GlobalWeight, &b_GlobalWeight);
   Notify();
}

Bool_t DiMuonNtuple::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void DiMuonNtuple::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t DiMuonNtuple::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef DiMuonNtuple_cxx
