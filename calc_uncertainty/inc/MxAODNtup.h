//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Apr 25 12:42:32 2016 by ROOT version 5.34/32
// from TTree tout/recreate
// found on file: Output/sample/mc/Sherpa_gamgam_2DP20.root
//////////////////////////////////////////////////////////

#ifndef MxAODNtup_h
#define MxAODNtup_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <iostream>
// Header file for the classes stored in the TTree if any.
using namespace std;
// Fixed size dimensions of array or collections stored in the TTree if any.

class MxAODNtup {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   UInt_t runNumber;
   ULong64_t eventNumber;
   UInt_t lumiBlock;
   Float_t         m_yy;
   Float_t         m_yy_truth;
   Float_t         cosTS_yy;
   Float_t         weight;
   Float_t         vertexWeight;
   Char_t isPassedLowHighMyy;
   Char_t isPassedLowHighMyyMoriond;
   Char_t isPassedExotic;
   Char_t isDalitz;
   Char_t isPassedIsolation;
   Char_t isPassedIsolationLowHighMyy;
   Char_t isPassedPID;
   Char_t isPassedBasic;
   UInt_t          mcChannelNumber;

   vector<float>   *conversionType;
   vector<float>   *eta_s2;
   vector<float>   *eta;
   vector<float>   *phi;
   vector<float>   *pt;
   vector<float>   *mcEventWeights;
   vector<int>     *truthType;
   vector<int>     *truthOrigin;

   /* Electrons */
   vector<float>   *HGamElectronsAuxDyn_pt;
   vector<float>   *HGamElectronsAuxDyn_eta;
   vector<float>   *HGamElectronsAuxDyn_topoetcone20;
   vector<float>   *HGamElectronsAuxDyn_phi;
   vector<float>   *HGamElectronsAuxDyn_m;
   vector<float>   *HGamElectronsAuxDyn_eta_s2;
   vector<float>   *HGamElectronsAuxDyn_charge;
   vector<char>    *HGamElectronsAuxDyn_isTight;

   /* Muons */
   vector<float>   *HGamMuonsAuxDyn_pt;
   vector<char>    *HGamMuonsAuxDyn_isBad;
   vector<char>    *HGamMuonsAuxDyn_passIPCut;
   vector<float>   *HGamMuonsAuxDyn_eta;
   vector<float>   *HGamMuonsAuxDyn_topoetcone20;
   vector<float>   *HGamMuonsAuxDyn_phi;

   /* Truth photon */
   vector<char>    *HGamTruthPhotonsAuxDyn_isIsolated;
   vector<float>   *HGamTruthPhotonsAuxDyn_etcone20;
   vector<int>     *HGamTruthPhotonsAuxDyn_truthOrigin;
   vector<float>   *HGamTruthPhotonsAuxDyn_etcone40;
   vector<float>   *HGamTruthPhotonsAuxDyn_ptcone20;
   vector<int>     *HGamTruthPhotonsAuxDyn_truthType;
   vector<float>   *HGamTruthPhotonsAuxDyn_ptcone40;
   vector<float>   *HGamTruthPhotonsAuxDyn_pt;
   vector<float>   *HGamTruthPhotonsAuxDyn_partonetcone20;
   vector<float>   *HGamTruthPhotonsAuxDyn_px;
   vector<float>   *HGamTruthPhotonsAuxDyn_eta;
   vector<float>   *HGamTruthPhotonsAuxDyn_partonetcone40;
   vector<float>   *HGamTruthPhotonsAuxDyn_py;
   vector<float>   *HGamTruthPhotonsAuxDyn_pz;
   vector<float>   *HGamTruthPhotonsAuxDyn_m;
   vector<float>   *HGamTruthPhotonsAuxDyn_e;

   /* Truth electron and muons */
   vector<int>     *HGamTruthElectronsAuxDyn_truthOrigin;
   vector<float>   *HGamTruthElectronsAuxDyn_pt;
   vector<int>     *HGamTruthElectronsAuxDyn_truthType;
   vector<float>   *HGamTruthElectronsAuxDyn_eta;
   vector<float>   *HGamTruthElectronsAuxDyn_px;
   vector<float>   *HGamTruthElectronsAuxDyn_m;
   vector<float>   *HGamTruthElectronsAuxDyn_py;
   vector<float>   *HGamTruthElectronsAuxDyn_pz;
   vector<float>   *HGamTruthElectronsAuxDyn_e;
   vector<int>     *HGamTruthMuonsAuxDyn_truthOrigin;
   vector<float>   *HGamTruthMuonsAuxDyn_pt;
   vector<int>     *HGamTruthMuonsAuxDyn_truthType;
   vector<float>   *HGamTruthMuonsAuxDyn_eta;
   vector<float>   *HGamTruthMuonsAuxDyn_px;
   vector<float>   *HGamTruthMuonsAuxDyn_m;
   vector<float>   *HGamTruthMuonsAuxDyn_py;
   vector<float>   *HGamTruthMuonsAuxDyn_pz;
   vector<float>   *HGamTruthMuonsAuxDyn_e;

   // List of branches
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_lumiBlock;   //!
   TBranch        *b_m_yy;   //!
   TBranch        *b_m_yy_truth;   //!
   TBranch        *b_cosTS_yy;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_conversionType;   //!
   TBranch        *b_eta_s2;   //!
   TBranch        *b_eta;   //!
   TBranch        *b_phi;   //!
   TBranch        *b_pt;   //!
   TBranch        *b_isPassedLowHighMyy;   //!
   TBranch        *b_isPassedLowHighMyyMoriond;   //!
   TBranch        *b_isPassedExotic;   //!
   TBranch        *b_isDalitz;   //!
   TBranch        *b_isPassedIsolation;   //!
   TBranch        *b_isPassedIsolationLowHighMyy;   //!
   TBranch        *b_mcChannelNumber;   //!
   TBranch        *b_vertexWeight;   //!
   TBranch        *b_isPassedPID;   //!
   TBranch        *b_isPassedBasic;   //!
   TBranch        *b_mcEventWeights;   //!
   TBranch        *b_truthOrigin;   //!
   TBranch        *b_truthType;   //!

   /* Electrons */
   TBranch        *b_HGamElectronsAuxDyn_pt;   //!
   TBranch        *b_HGamElectronsAuxDyn_eta;   //!
   TBranch        *b_HGamElectronsAuxDyn_topoetcone20;   //!
   TBranch        *b_HGamElectronsAuxDyn_phi;   //!
   TBranch        *b_HGamElectronsAuxDyn_m;   //!
   TBranch        *b_HGamElectronsAuxDyn_eta_s2;   //!
   TBranch        *b_HGamElectronsAuxDyn_charge;   //!
   TBranch        *b_HGamElectronsAuxDyn_isTight;   //!

   /* Muons */
   TBranch        *b_HGamMuonsAuxDyn_pt;   //!
   TBranch        *b_HGamMuonsAuxDyn_isBad;   //!
   TBranch        *b_HGamMuonsAuxDyn_passIPCut;   //!
   TBranch        *b_HGamMuonsAuxDyn_eta;   //!
   TBranch        *b_HGamMuonsAuxDyn_topoetcone20;   //!
   TBranch        *b_HGamMuonsAuxDyn_phi;   //!

   /* Truth photon */
   TBranch        *b_HGamTruthPhotonsAuxDyn_isIsolated;   //!
   TBranch        *b_HGamTruthPhotonsAuxDyn_etcone20;   //!
   TBranch        *b_HGamTruthPhotonsAuxDyn_truthOrigin;   //!
   TBranch        *b_HGamTruthPhotonsAuxDyn_etcone40;   //!
   TBranch        *b_HGamTruthPhotonsAuxDyn_ptcone20;   //!
   TBranch        *b_HGamTruthPhotonsAuxDyn_truthType;   //!
   TBranch        *b_HGamTruthPhotonsAuxDyn_ptcone40;   //!
   TBranch        *b_HGamTruthPhotonsAuxDyn_pt;   //!
   TBranch        *b_HGamTruthPhotonsAuxDyn_partonetcone20;   //!
   TBranch        *b_HGamTruthPhotonsAuxDyn_px;   //!
   TBranch        *b_HGamTruthPhotonsAuxDyn_eta;   //!
   TBranch        *b_HGamTruthPhotonsAuxDyn_partonetcone40;   //!
   TBranch        *b_HGamTruthPhotonsAuxDyn_py;   //!
   TBranch        *b_HGamTruthPhotonsAuxDyn_pz;   //!
   TBranch        *b_HGamTruthPhotonsAuxDyn_m;   //!
   TBranch        *b_HGamTruthPhotonsAuxDyn_e;   //!

   /* Truth electron and muon */
   TBranch        *b_HGamTruthElectronsAuxDyn_truthOrigin;   //!
   TBranch        *b_HGamTruthElectronsAuxDyn_pt;   //!
   TBranch        *b_HGamTruthElectronsAuxDyn_truthType;   //!
   TBranch        *b_HGamTruthElectronsAuxDyn_eta;   //!
   TBranch        *b_HGamTruthElectronsAuxDyn_px;   //!
   TBranch        *b_HGamTruthElectronsAuxDyn_m;   //!
   TBranch        *b_HGamTruthElectronsAuxDyn_py;   //!
   TBranch        *b_HGamTruthElectronsAuxDyn_pz;   //!
   TBranch        *b_HGamTruthElectronsAuxDyn_e;   //!
   TBranch        *b_HGamTruthMuonsAuxDyn_truthOrigin;   //!
   TBranch        *b_HGamTruthMuonsAuxDyn_pt;   //!
   TBranch        *b_HGamTruthMuonsAuxDyn_truthType;   //!
   TBranch        *b_HGamTruthMuonsAuxDyn_eta;   //!
   TBranch        *b_HGamTruthMuonsAuxDyn_px;   //!
   TBranch        *b_HGamTruthMuonsAuxDyn_m;   //!
   TBranch        *b_HGamTruthMuonsAuxDyn_py;   //!
   TBranch        *b_HGamTruthMuonsAuxDyn_pz;   //!
   TBranch        *b_HGamTruthMuonsAuxDyn_e;   //!

   MxAODNtup(TTree *tree=0);
   virtual ~MxAODNtup();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef MxAODNtup_cxx
MxAODNtup::MxAODNtup(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Output/sample/mc/Sherpa_gamgam_2DP20.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("Output/sample/mc/Sherpa_gamgam_2DP20.root");
      }
      f->GetObject("CollectionTree",tree);

   }
   Init(tree);
}

MxAODNtup::~MxAODNtup()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MxAODNtup::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MxAODNtup::LoadTree(Long64_t entry)
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

void MxAODNtup::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).
  conversionType=0;
  eta_s2=0;
  eta=0;
  phi=0;
  pt=0;
  mcEventWeights = 0;
   truthOrigin = 0;
   truthType = 0;

   /* Electrons */
   HGamElectronsAuxDyn_pt = 0;
   HGamElectronsAuxDyn_eta = 0;
   HGamElectronsAuxDyn_topoetcone20 = 0;
   HGamElectronsAuxDyn_phi = 0;
   HGamElectronsAuxDyn_m = 0;
   HGamElectronsAuxDyn_eta_s2 = 0;
   HGamElectronsAuxDyn_charge = 0;
   HGamElectronsAuxDyn_isTight = 0;

   /* Muons */
   HGamMuonsAuxDyn_pt = 0;
   HGamMuonsAuxDyn_isBad = 0;
   HGamMuonsAuxDyn_passIPCut = 0;
   HGamMuonsAuxDyn_eta = 0;
   HGamMuonsAuxDyn_topoetcone20 = 0;
   HGamMuonsAuxDyn_phi = 0;

   /* Truth photons */
   HGamTruthPhotonsAuxDyn_isIsolated = 0;
   HGamTruthPhotonsAuxDyn_etcone20 = 0;
   HGamTruthPhotonsAuxDyn_truthOrigin = 0;
   HGamTruthPhotonsAuxDyn_etcone40 = 0;
   HGamTruthPhotonsAuxDyn_ptcone20 = 0;
   HGamTruthPhotonsAuxDyn_truthType = 0;
   HGamTruthPhotonsAuxDyn_ptcone40 = 0;
   HGamTruthPhotonsAuxDyn_pt = 0;
   HGamTruthPhotonsAuxDyn_partonetcone20 = 0;
   HGamTruthPhotonsAuxDyn_px = 0;
   HGamTruthPhotonsAuxDyn_eta = 0;
   HGamTruthPhotonsAuxDyn_partonetcone40 = 0;
   HGamTruthPhotonsAuxDyn_py = 0;
   HGamTruthPhotonsAuxDyn_pz = 0;
   HGamTruthPhotonsAuxDyn_m = 0;
   HGamTruthPhotonsAuxDyn_e = 0;

   /* Truth electron and muon */
   HGamTruthElectronsAuxDyn_truthOrigin = 0;
   HGamTruthElectronsAuxDyn_pt = 0;
   HGamTruthElectronsAuxDyn_truthType = 0;
   HGamTruthElectronsAuxDyn_eta = 0;
   HGamTruthElectronsAuxDyn_px = 0;
   HGamTruthElectronsAuxDyn_m = 0;
   HGamTruthElectronsAuxDyn_py = 0;
   HGamTruthElectronsAuxDyn_pz = 0;
   HGamTruthElectronsAuxDyn_e = 0;
   HGamTruthMuonsAuxDyn_truthOrigin = 0;
   HGamTruthMuonsAuxDyn_pt = 0;
   HGamTruthMuonsAuxDyn_truthType = 0;
   HGamTruthMuonsAuxDyn_eta = 0;
   HGamTruthMuonsAuxDyn_px = 0;
   HGamTruthMuonsAuxDyn_m = 0;
   HGamTruthMuonsAuxDyn_py = 0;
   HGamTruthMuonsAuxDyn_pz = 0;
   HGamTruthMuonsAuxDyn_e = 0;

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);
   if(fChain->GetListOfBranches()->FindObject("EventInfoAuxDyn.runNumber")){
     std::cout<<"Can find run number branch in old pattern"<<std::endl;
     fChain->SetBranchAddress("EventInfoAuxDyn.runNumber", &runNumber, &b_runNumber);
   }
   else{
     std::cout<<"Use run number branch in new pattern"<<std::endl;
     fChain->SetBranchAddress("EventInfoAux.runNumber", &runNumber, &b_runNumber);
   }
   if(fChain->GetListOfBranches()->FindObject("EventInfoAuxDyn.eventNumber")) fChain->SetBranchAddress("EventInfoAuxDyn.eventNumber", &eventNumber, &b_eventNumber);
   else fChain->SetBranchAddress("EventInfoAux.eventNumber", &eventNumber, &b_eventNumber);
   if(fChain->GetListOfBranches()->FindObject("EventInfoAuxDyn.lumiBlock")) fChain->SetBranchAddress("EventInfoAuxDyn.lumiBlock", &lumiBlock, &b_lumiBlock);
   else fChain->SetBranchAddress("EventInfoAux.lumiBlock", &lumiBlock, &b_lumiBlock);

   fChain->SetBranchAddress("HGamEventInfoAuxDyn.m_yy", &m_yy, &b_m_yy);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.m_yy", &m_yy_truth, &b_m_yy_truth);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.cosTS_yy", &cosTS_yy, &b_cosTS_yy);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.weight", &weight, &b_weight);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.isPassedLowHighMyy", &isPassedLowHighMyy, &b_isPassedLowHighMyy);
   /* fChain->SetBranchAddress("HGamEventInfoAuxDyn.isPassedLowHighMyyMoriond", &isPassedLowHighMyyMoriond, &b_isPassedLowHighMyyMoriond); */
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.isPassedExotic", &isPassedExotic, &b_isPassedExotic);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.isDalitz", &isDalitz, &b_isDalitz);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.isPassedIsolationLowHighMyy", &isPassedIsolationLowHighMyy, &b_isPassedIsolationLowHighMyy);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.isPassedIsolation", &isPassedIsolation, &b_isPassedIsolation);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.eta_s2", &eta_s2, &b_eta_s2);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.eta", &eta, &b_eta);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.phi", &phi, &b_phi);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.pt", &pt, &b_pt);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.conversionType", &conversionType, &b_conversionType);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.truthOrigin", &truthOrigin, &b_truthOrigin);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.truthType", &truthType, &b_truthType);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.vertexWeight", &vertexWeight, &b_vertexWeight);
   fChain->SetBranchAddress("EventInfoAuxDyn.mcEventWeights", &mcEventWeights, &b_mcEventWeights);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.isPassedPID", &isPassedPID, &b_isPassedPID);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.isPassedBasic", &isPassedBasic, &b_isPassedBasic);
   fChain->SetBranchAddress("EventInfoAuxDyn.mcChannelNumber", &mcChannelNumber, &b_mcChannelNumber);

   /* Electrons */
   fChain->SetBranchAddress("HGamElectronsAuxDyn.pt", &HGamElectronsAuxDyn_pt, &b_HGamElectronsAuxDyn_pt);
   fChain->SetBranchAddress("HGamElectronsAuxDyn.eta", &HGamElectronsAuxDyn_eta, &b_HGamElectronsAuxDyn_eta);
   fChain->SetBranchAddress("HGamElectronsAuxDyn.topoetcone20", &HGamElectronsAuxDyn_topoetcone20, &b_HGamElectronsAuxDyn_topoetcone20);
   fChain->SetBranchAddress("HGamElectronsAuxDyn.phi", &HGamElectronsAuxDyn_phi, &b_HGamElectronsAuxDyn_phi);
   fChain->SetBranchAddress("HGamElectronsAuxDyn.m", &HGamElectronsAuxDyn_m, &b_HGamElectronsAuxDyn_m);
   fChain->SetBranchAddress("HGamElectronsAuxDyn.eta_s2", &HGamElectronsAuxDyn_eta_s2, &b_HGamElectronsAuxDyn_eta_s2);
   fChain->SetBranchAddress("HGamElectronsAuxDyn.charge", &HGamElectronsAuxDyn_charge, &b_HGamElectronsAuxDyn_charge);
   fChain->SetBranchAddress("HGamElectronsAuxDyn.isTight", &HGamElectronsAuxDyn_isTight, &b_HGamElectronsAuxDyn_isTight);

   /* Muons */
   fChain->SetBranchAddress("HGamMuonsAuxDyn.pt", &HGamMuonsAuxDyn_pt, &b_HGamMuonsAuxDyn_pt);
   fChain->SetBranchAddress("HGamMuonsAuxDyn.isBad", &HGamMuonsAuxDyn_isBad, &b_HGamMuonsAuxDyn_isBad);
   fChain->SetBranchAddress("HGamMuonsAuxDyn.passIPCut", &HGamMuonsAuxDyn_passIPCut, &b_HGamMuonsAuxDyn_passIPCut);
   fChain->SetBranchAddress("HGamMuonsAuxDyn.eta", &HGamMuonsAuxDyn_eta, &b_HGamMuonsAuxDyn_eta);
   fChain->SetBranchAddress("HGamMuonsAuxDyn.topoetcone20", &HGamMuonsAuxDyn_topoetcone20, &b_HGamMuonsAuxDyn_topoetcone20);
   fChain->SetBranchAddress("HGamMuonsAuxDyn.phi", &HGamMuonsAuxDyn_phi, &b_HGamMuonsAuxDyn_phi);

   /* Truth photons */
   fChain->SetBranchAddress("HGamTruthPhotonsAuxDyn.isIsolated", &HGamTruthPhotonsAuxDyn_isIsolated, &b_HGamTruthPhotonsAuxDyn_isIsolated);
   fChain->SetBranchAddress("HGamTruthPhotonsAuxDyn.etcone20", &HGamTruthPhotonsAuxDyn_etcone20, &b_HGamTruthPhotonsAuxDyn_etcone20);
   fChain->SetBranchAddress("HGamTruthPhotonsAuxDyn.truthOrigin", &HGamTruthPhotonsAuxDyn_truthOrigin, &b_HGamTruthPhotonsAuxDyn_truthOrigin);
   fChain->SetBranchAddress("HGamTruthPhotonsAuxDyn.etcone40", &HGamTruthPhotonsAuxDyn_etcone40, &b_HGamTruthPhotonsAuxDyn_etcone40);
   fChain->SetBranchAddress("HGamTruthPhotonsAuxDyn.ptcone20", &HGamTruthPhotonsAuxDyn_ptcone20, &b_HGamTruthPhotonsAuxDyn_ptcone20);
   fChain->SetBranchAddress("HGamTruthPhotonsAuxDyn.truthType", &HGamTruthPhotonsAuxDyn_truthType, &b_HGamTruthPhotonsAuxDyn_truthType);
   fChain->SetBranchAddress("HGamTruthPhotonsAuxDyn.ptcone40", &HGamTruthPhotonsAuxDyn_ptcone40, &b_HGamTruthPhotonsAuxDyn_ptcone40);
   fChain->SetBranchAddress("HGamTruthPhotonsAuxDyn.pt", &HGamTruthPhotonsAuxDyn_pt, &b_HGamTruthPhotonsAuxDyn_pt);
   fChain->SetBranchAddress("HGamTruthPhotonsAuxDyn.partonetcone20", &HGamTruthPhotonsAuxDyn_partonetcone20, &b_HGamTruthPhotonsAuxDyn_partonetcone20);
   fChain->SetBranchAddress("HGamTruthPhotonsAuxDyn.px", &HGamTruthPhotonsAuxDyn_px, &b_HGamTruthPhotonsAuxDyn_px);
   fChain->SetBranchAddress("HGamTruthPhotonsAuxDyn.eta", &HGamTruthPhotonsAuxDyn_eta, &b_HGamTruthPhotonsAuxDyn_eta);
   fChain->SetBranchAddress("HGamTruthPhotonsAuxDyn.partonetcone40", &HGamTruthPhotonsAuxDyn_partonetcone40, &b_HGamTruthPhotonsAuxDyn_partonetcone40);
   fChain->SetBranchAddress("HGamTruthPhotonsAuxDyn.py", &HGamTruthPhotonsAuxDyn_py, &b_HGamTruthPhotonsAuxDyn_py);
   fChain->SetBranchAddress("HGamTruthPhotonsAuxDyn.pz", &HGamTruthPhotonsAuxDyn_pz, &b_HGamTruthPhotonsAuxDyn_pz);
   fChain->SetBranchAddress("HGamTruthPhotonsAuxDyn.m", &HGamTruthPhotonsAuxDyn_m, &b_HGamTruthPhotonsAuxDyn_m);
   fChain->SetBranchAddress("HGamTruthPhotonsAuxDyn.e", &HGamTruthPhotonsAuxDyn_e, &b_HGamTruthPhotonsAuxDyn_e);

   /* Truth electron and muon */
   fChain->SetBranchAddress("HGamTruthElectronsAuxDyn.truthOrigin", &HGamTruthElectronsAuxDyn_truthOrigin, &b_HGamTruthElectronsAuxDyn_truthOrigin);
   fChain->SetBranchAddress("HGamTruthElectronsAuxDyn.pt", &HGamTruthElectronsAuxDyn_pt, &b_HGamTruthElectronsAuxDyn_pt);
   fChain->SetBranchAddress("HGamTruthElectronsAuxDyn.truthType", &HGamTruthElectronsAuxDyn_truthType, &b_HGamTruthElectronsAuxDyn_truthType);
   fChain->SetBranchAddress("HGamTruthElectronsAuxDyn.eta", &HGamTruthElectronsAuxDyn_eta, &b_HGamTruthElectronsAuxDyn_eta);
   fChain->SetBranchAddress("HGamTruthElectronsAuxDyn.px", &HGamTruthElectronsAuxDyn_px, &b_HGamTruthElectronsAuxDyn_px);
   fChain->SetBranchAddress("HGamTruthElectronsAuxDyn.m", &HGamTruthElectronsAuxDyn_m, &b_HGamTruthElectronsAuxDyn_m);
   fChain->SetBranchAddress("HGamTruthElectronsAuxDyn.py", &HGamTruthElectronsAuxDyn_py, &b_HGamTruthElectronsAuxDyn_py);
   fChain->SetBranchAddress("HGamTruthElectronsAuxDyn.pz", &HGamTruthElectronsAuxDyn_pz, &b_HGamTruthElectronsAuxDyn_pz);
   fChain->SetBranchAddress("HGamTruthElectronsAuxDyn.e", &HGamTruthElectronsAuxDyn_e, &b_HGamTruthElectronsAuxDyn_e);
   fChain->SetBranchAddress("HGamTruthMuonsAuxDyn.truthOrigin", &HGamTruthMuonsAuxDyn_truthOrigin, &b_HGamTruthMuonsAuxDyn_truthOrigin);
   fChain->SetBranchAddress("HGamTruthMuonsAuxDyn.pt", &HGamTruthMuonsAuxDyn_pt, &b_HGamTruthMuonsAuxDyn_pt);
   fChain->SetBranchAddress("HGamTruthMuonsAuxDyn.truthType", &HGamTruthMuonsAuxDyn_truthType, &b_HGamTruthMuonsAuxDyn_truthType);
   fChain->SetBranchAddress("HGamTruthMuonsAuxDyn.eta", &HGamTruthMuonsAuxDyn_eta, &b_HGamTruthMuonsAuxDyn_eta);
   fChain->SetBranchAddress("HGamTruthMuonsAuxDyn.px", &HGamTruthMuonsAuxDyn_px, &b_HGamTruthMuonsAuxDyn_px);
   fChain->SetBranchAddress("HGamTruthMuonsAuxDyn.m", &HGamTruthMuonsAuxDyn_m, &b_HGamTruthMuonsAuxDyn_m);
   fChain->SetBranchAddress("HGamTruthMuonsAuxDyn.py", &HGamTruthMuonsAuxDyn_py, &b_HGamTruthMuonsAuxDyn_py);
   fChain->SetBranchAddress("HGamTruthMuonsAuxDyn.pz", &HGamTruthMuonsAuxDyn_pz, &b_HGamTruthMuonsAuxDyn_pz);
   fChain->SetBranchAddress("HGamTruthMuonsAuxDyn.e", &HGamTruthMuonsAuxDyn_e, &b_HGamTruthMuonsAuxDyn_e);
   Notify();

   /* Only open branches which are needed */
   fChain->SetBranchStatus("*",0);
   fChain->SetBranchStatus("HGamEventInfoAuxDyn.m_yy", 1);
   fChain->SetBranchStatus("HGamTruthEventInfoAuxDyn.m_yy", 1);
   fChain->SetBranchStatus("HGamEventInfoAuxDyn.cosTS_yy", 1);
   fChain->SetBranchStatus("HGamEventInfoAuxDyn.weight", 1);
   fChain->SetBranchStatus("HGamEventInfoAuxDyn.isPassedLowHighMyy", 1);
   /* fChain->SetBranchStatus("HGamEventInfoAuxDyn.isPassedLowHighMyyMoriond", 1); */
   fChain->SetBranchStatus("HGamEventInfoAuxDyn.isPassedExotic", 1);
   fChain->SetBranchStatus("HGamEventInfoAuxDyn.isDalitz", 1);
   fChain->SetBranchStatus("HGamEventInfoAuxDyn.isPassedIsolationLowHighMyy", 1);
   fChain->SetBranchStatus("HGamEventInfoAuxDyn.isPassedIsolation", 1);
   fChain->SetBranchStatus("HGamPhotonsAuxDyn.eta_s2", 1);
   fChain->SetBranchStatus("HGamPhotonsAuxDyn.eta", 1);
   fChain->SetBranchStatus("HGamPhotonsAuxDyn.phi", 1);
   fChain->SetBranchStatus("HGamPhotonsAuxDyn.pt", 1);
   fChain->SetBranchStatus("HGamPhotonsAuxDyn.conversionType", 1);
   fChain->SetBranchStatus("HGamEventInfoAuxDyn.vertexWeight", 1);
   fChain->SetBranchStatus("EventInfoAuxDyn.mcEventWeights", 1);
   fChain->SetBranchStatus("HGamEventInfoAuxDyn.isPassedPID", 1);
   fChain->SetBranchStatus("HGamEventInfoAuxDyn.isPassedBasic", 1);
   fChain->SetBranchStatus("EventInfoAuxDyn.mcChannelNumber", 1);
   fChain->SetBranchStatus("HGamPhotonsAuxDyn.truthOrigin", 1);
   fChain->SetBranchStatus("HGamPhotonsAuxDyn.truthType", 1);
   fChain->SetBranchStatus("HGamElectronsAuxDyn.pt", 1);
   fChain->SetBranchStatus("HGamElectronsAuxDyn.eta", 1);
   fChain->SetBranchStatus("HGamMuonsAuxDyn.pt", 1);
   fChain->SetBranchStatus("HGamMuonsAuxDyn.isBad", 1);
   fChain->SetBranchStatus("HGamMuonsAuxDyn.passIPCut", 1);
   fChain->SetBranchStatus("HGamMuonsAuxDyn.eta", 1);
   fChain->SetBranchStatus("HGamTruthPhotonsAuxDyn.isIsolated", 1);
   fChain->SetBranchStatus("HGamTruthPhotonsAuxDyn.etcone20", 1);
   fChain->SetBranchStatus("HGamTruthPhotonsAuxDyn.truthOrigin", 1);
   fChain->SetBranchStatus("HGamTruthPhotonsAuxDyn.etcone40", 1);
   fChain->SetBranchStatus("HGamTruthPhotonsAuxDyn.ptcone20", 1);
   fChain->SetBranchStatus("HGamTruthPhotonsAuxDyn.truthType", 1);
   fChain->SetBranchStatus("HGamTruthPhotonsAuxDyn.ptcone40", 1);
   fChain->SetBranchStatus("HGamTruthPhotonsAuxDyn.pt", 1);
   fChain->SetBranchStatus("HGamTruthPhotonsAuxDyn.partonetcone20", 1);
   fChain->SetBranchStatus("HGamTruthPhotonsAuxDyn.px", 1);
   fChain->SetBranchStatus("HGamTruthPhotonsAuxDyn.eta", 1);
   fChain->SetBranchStatus("HGamTruthPhotonsAuxDyn.partonetcone40", 1);
   fChain->SetBranchStatus("HGamTruthPhotonsAuxDyn.py", 1);
   fChain->SetBranchStatus("HGamTruthPhotonsAuxDyn.pz", 1);
   fChain->SetBranchStatus("HGamTruthPhotonsAuxDyn.m", 1);
   fChain->SetBranchStatus("HGamTruthPhotonsAuxDyn.e", 1);
   fChain->SetBranchStatus("HGamTruthElectronsAuxDyn.truthOrigin", 1);
   fChain->SetBranchStatus("HGamTruthElectronsAuxDyn.pt", 1);
   fChain->SetBranchStatus("HGamTruthElectronsAuxDyn.truthType", 1);
   fChain->SetBranchStatus("HGamTruthElectronsAuxDyn.eta", 1);
   fChain->SetBranchStatus("HGamTruthElectronsAuxDyn.px", 1);
   fChain->SetBranchStatus("HGamTruthElectronsAuxDyn.m", 1);
   fChain->SetBranchStatus("HGamTruthElectronsAuxDyn.py", 1);
   fChain->SetBranchStatus("HGamTruthElectronsAuxDyn.pz", 1);
   fChain->SetBranchStatus("HGamTruthElectronsAuxDyn.e", 1);
   fChain->SetBranchStatus("HGamTruthMuonsAuxDyn.truthOrigin", 1);
   fChain->SetBranchStatus("HGamTruthMuonsAuxDyn.pt", 1);
   fChain->SetBranchStatus("HGamTruthMuonsAuxDyn.truthType", 1);
   fChain->SetBranchStatus("HGamTruthMuonsAuxDyn.eta", 1);
   fChain->SetBranchStatus("HGamTruthMuonsAuxDyn.px", 1);
   fChain->SetBranchStatus("HGamTruthMuonsAuxDyn.m", 1);
   fChain->SetBranchStatus("HGamTruthMuonsAuxDyn.py", 1);
   fChain->SetBranchStatus("HGamTruthMuonsAuxDyn.pz", 1);
   fChain->SetBranchStatus("HGamTruthMuonsAuxDyn.e", 1);
   fChain->SetBranchStatus("HGamElectronsAuxDyn.topoetcone20", 1);
   fChain->SetBranchStatus("HGamElectronsAuxDyn.phi", 1);
   fChain->SetBranchStatus("HGamElectronsAuxDyn.m", 1);
   fChain->SetBranchStatus("HGamElectronsAuxDyn.eta_s2", 1);
   fChain->SetBranchStatus("HGamElectronsAuxDyn.charge", 1);
   fChain->SetBranchStatus("HGamElectronsAuxDyn.isTight", 1);
   fChain->SetBranchStatus("HGamMuonsAuxDyn.topoetcone20", 1);
   fChain->SetBranchStatus("HGamMuonsAuxDyn.phi", 1);
}

Bool_t MxAODNtup::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MxAODNtup::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MxAODNtup::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef MxAODNtup_cxx
