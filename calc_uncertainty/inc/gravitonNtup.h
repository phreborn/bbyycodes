//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Mar  9 01:27:43 2016 by ROOT version 6.04/02
// from TTree gravitonNtup/
// found on file: Output/Graviton/single_sample/mc15_m500_k01.root
//////////////////////////////////////////////////////////

#ifndef gravitonNtup_h
#define gravitonNtup_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "TLorentzVector.h"
#include "vector"

using namespace std;

class gravitonNtup {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Bool_t          all;
   Bool_t          pass_dalitz;
   Bool_t          pass_trigger;
   Bool_t          pass_grl;
   Bool_t          pass_detector_DQ;
   Bool_t          pass_PV;
   Bool_t          pass_preselection;
   Bool_t          pass_ld_subld_id;
   Bool_t          pass_ld_subld_isol;
   Bool_t          pass_ld_subld_Et;
   Bool_t          pass_ld_subld_rel_cuts;
   Bool_t          accepted;
   Bool_t          accepted_nominal;
   Int_t           category;
   Bool_t          pass_egamma_selection;
   Int_t           isEM_0_ld;
   Int_t           isEM_0_subld;
   Int_t           isEM_nofudge_0_ld;
   Int_t           isEM_1_ld;
   Int_t           isEM_1_subld;
   Int_t           isEM_nofudge_1_ld;
   Int_t           isEM_2_ld;
   Int_t           isEM_2_subld;
   Int_t           isEM_nofudge_2_ld;
   Int_t           isEM_3_ld;
   Int_t           isEM_3_subld;
   Int_t           isEM_nofudge_3_ld;
   Int_t           isEM_4_ld;
   Int_t           isEM_4_subld;
   Int_t           isEM_nofudge_4_ld;
   Int_t           isEM_5_ld;
   Int_t           isEM_5_subld;
   Int_t           isEM_nofudge_5_ld;
   Int_t           isEM_6_ld;
   Int_t           isEM_6_subld;
   Int_t           isEM_nofudge_6_ld;
   Int_t           isEM_7_ld;
   Int_t           isEM_7_subld;
   Int_t           isEM_nofudge_7_ld;
   Int_t           isEM_8_ld;
   Int_t           isEM_8_subld;
   Int_t           isEM_nofudge_8_ld;
   Int_t           isEM_9_ld;
   Int_t           isEM_9_subld;
   Int_t           isEM_nofudge_9_ld;
   Int_t           isEM_10_ld;
   Int_t           isEM_10_subld;
   Int_t           isEM_nofudge_10_ld;
   Int_t           isEM_11_ld;
   Int_t           isEM_11_subld;
   Int_t           isEM_nofudge_11_ld;
   Int_t           isEM_12_ld;
   Int_t           isEM_12_subld;
   Int_t           isEM_nofudge_12_ld;
   Int_t           isEM_13_ld;
   Int_t           isEM_13_subld;
   Int_t           isEM_nofudge_13_ld;
   Int_t           isEM_14_ld;
   Int_t           isEM_14_subld;
   Int_t           isEM_nofudge_14_ld;
   Int_t           isEM_15_ld;
   Int_t           isEM_15_subld;
   Int_t           isEM_nofudge_15_ld;
   Int_t           isEM_16_ld;
   Int_t           isEM_16_subld;
   Int_t           isEM_nofudge_16_ld;
   Int_t           isEM_17_ld;
   Int_t           isEM_17_subld;
   Int_t           isEM_nofudge_17_ld;
   Int_t           isEM_18_ld;
   Int_t           isEM_18_subld;
   Int_t           isEM_nofudge_18_ld;
   Int_t           isEM_19_ld;
   Int_t           isEM_19_subld;
   Int_t           isEM_nofudge_19_ld;
   Int_t           isEM_20_ld;
   Int_t           isEM_20_subld;
   Int_t           isEM_nofudge_20_ld;
   Int_t           isEM_21_ld;
   Int_t           isEM_21_subld;
   Int_t           isEM_nofudge_21_ld;
   Bool_t          pass_2g50_loose_trigger;
   Bool_t          pass_g35_g25_loose_trigger;
   Float_t         averageIntPerXing;
   Double_t        ED_central;
   Double_t        ED_forward;
   Int_t           run_number;
   ULong64_t       event_number;
   Int_t           lumiblock_number;
   Int_t           time_stamp;
   Int_t           bcid;
   Int_t           mc_channel_number;
   ULong64_t       mc_event_number;
   Int_t           nPV;
   Float_t         xs;
   Float_t         xs_ami;
   Float_t         filter_eff;
   Float_t         filter_eff_ami;
   Bool_t          one_photon;
   Bool_t          two_photons;
   Float_t         pileup_weight;
   Float_t         vertex_weight;
   Float_t         MC_weight;
   Float_t         xs_weight;
   Float_t         event_weight;
   Float_t         prel_weight;
   Float_t         total_weight;
   Int_t           total_events;
   Int_t           non_derived_total_events;
   Float_t         weight_sum_before;
   Float_t         SF_leading;
   Float_t         SF_unc_leading;
   Float_t         SF_subleading;
   Float_t         SF_unc_subleading;
   Float_t         SF_diphoton;
   Float_t         SF_1UP_diphoton;
   Float_t         SF_1DOWN_diphoton;
   Float_t         sumpt2_tracks;
   Float_t         mass_gev;
   Float_t         mass_MVA;
   Float_t         mgg;
   Float_t         mass_raw;
   Float_t         mass_egamma;
   Float_t         mass;
   Float_t         costhetastar;
   Double_t        deltaphi;
   TLorentzVector  *LV_leading;
   TLorentzVector  *LV_subleading;
   TLorentzVector  *LV_diphoton;
   TLorentzVector  *LV_egamma;
   Float_t         pt_subleading;
   Float_t         pt_leading;
   Float_t         phi_subleading;
   Float_t         phi_leading;
   Float_t         eta_subleading;
   Float_t         eta_leading;
   Int_t           author_leading;
   Int_t           author_subleading;
   Float_t         raw_energy_leading;
   Float_t         raw_energy_subleading;
   Float_t         raw_et_leading;
   Float_t         raw_et_subleading;
   Float_t         e_on_eraw_leading;
   Float_t         e_on_eraw_subleading;
   Float_t         deltaR;
   Int_t           max_cell_gain_leading;
   Float_t         max_cell_time_leading;
   Float_t         max_cell_e_leading;
   Int_t           max_cell_gain_subleading;
   Float_t         max_cell_time_subleading;
   Float_t         max_cell_e_subleading;
   Float_t         Rconv_leading;
   Float_t         Rconv_subleading;
   Float_t         E0_leading;
   Float_t         E1_leading;
   Float_t         E2_leading;
   Float_t         E3_leading;
   Float_t         E0_subleading;
   Float_t         E1_subleading;
   Float_t         E2_subleading;
   Float_t         E3_subleading;
   Float_t         Zconv_leading;
   Float_t         Zconv_subleading;
   Float_t         PVz;
   Float_t         topoetcone40_leading;
   Float_t         topoetcone40_DDcorrected_leading;
   Float_t         topoetcone40_rel17_leading;
   Float_t         topoetcone40_electron_leading;
   Float_t         topoetcone40_trouble_electron_leading;
   Float_t         topoetcone40_rel17_electron_leading;
   Int_t           author_electron_leading;
   Float_t         topoetcone40_subleading;
   Float_t         topoetcone40_DDcorrected_subleading;
   Float_t         topoetcone20_leading;
   Float_t         topoetcone20_subleading;
   Float_t         truth_etcone40_leading;
   Float_t         truth_etcone40_subleading;
   Float_t         truth_etcone20_leading;
   Float_t         truth_etcone20_subleading;
   Float_t         truth_local_etcone40_leading;
   Float_t         truth_local_etcone40_subleading;
   Float_t         truth_local_etcone20_leading;
   Float_t         truth_local_etcone20_subleading;
   Float_t         truth_etcone40_PUcorr_leading;
   Float_t         truth_etcone40_PUcorr_subleading;
   Float_t         truth_etcone20_PUcorr_leading;
   Float_t         truth_etcone20_PUcorr_subleading;
   Float_t         truth_ptcone40_leading;
   Float_t         truth_ptcone40_subleading;
   Float_t         truth_ptcone20_leading;
   Float_t         truth_ptcone20_subleading;
   Float_t         truth_ptcone40_PUcorr_leading;
   Float_t         truth_ptcone40_PUcorr_subleading;
   Float_t         truth_ptcone20_PUcorr_leading;
   Float_t         truth_ptcone20_PUcorr_subleading;
   Float_t         truth_rho_central;
   Float_t         truth_rho_forward;
   Int_t           tight_leading;
   Int_t           my_tight_leading;
   Int_t           loose_leading;
   Int_t           loose_prime_leading;
   Int_t           tight_subleading;
   Int_t           loose_subleading;
   Int_t           loose_prime_subleading;
   Bool_t          bg_truth_match_leading;
   Bool_t          bg_truth_match_origin_leading;
   Int_t           pdgID_leading;
   Int_t           parent_pdgID_leading;
   Int_t           type_leading;
   Int_t           origin_leading;
   Bool_t          truth_match_leading;
   Int_t           pdgID_subleading;
   Int_t           parent_pdgID_subleading;
   Int_t           type_subleading;
   Int_t           origin_subleading;
   Bool_t          truth_match_subleading;
   Int_t           conv_leading;
   Int_t           conv_subleading;
   UInt_t          isEM_leading;
   UInt_t          isEM_subleading;
   UInt_t          isEM_nofudge_leading;
   UInt_t          isEM_nofudge_subleading;
   Int_t           photonOQ_leading;
   Int_t           photonOQ_subleading;
   Float_t         Z_pointing_leading;
   Float_t         Z_pointing_subleading;
   Float_t         Rhad_leading;
   Float_t         e277_leading;
   Float_t         Reta_leading;
   Float_t         Rphi_leading;
   Float_t         weta2_leading;
   Float_t         f1_leading;
   Float_t         DeltaE_leading;
   Float_t         wtots1_leading;
   Float_t         fracs1_leading;
   Float_t         weta1_leading;
   Float_t         Eratio_leading;
   Float_t         Rhad_subleading;
   Float_t         e277_subleading;
   Float_t         Reta_subleading;
   Float_t         Rphi_subleading;
   Float_t         weta2_subleading;
   Float_t         f1_subleading;
   Float_t         DeltaE_subleading;
   Float_t         wtots1_subleading;
   Float_t         fracs1_subleading;
   Float_t         weta1_subleading;
   Float_t         Eratio_subleading;
   Float_t         Rhad_leading_nofudge;
   Float_t         e277_leading_nofudge;
   Float_t         Reta_leading_nofudge;
   Float_t         Rphi_leading_nofudge;
   Float_t         weta2_leading_nofudge;
   Float_t         f1_leading_nofudge;
   Float_t         DeltaE_leading_nofudge;
   Float_t         wtots1_leading_nofudge;
   Float_t         fracs1_leading_nofudge;
   Float_t         weta1_leading_nofudge;
   Float_t         Eratio_leading_nofudge;
   Float_t         Rhad_subleading_nofudge;
   Float_t         e277_subleading_nofudge;
   Float_t         Reta_subleading_nofudge;
   Float_t         Rphi_subleading_nofudge;
   Float_t         weta2_subleading_nofudge;
   Float_t         f1_subleading_nofudge;
   Float_t         DeltaE_subleading_nofudge;
   Float_t         wtots1_subleading_nofudge;
   Float_t         fracs1_subleading_nofudge;
   Float_t         weta1_subleading_nofudge;
   Float_t         Eratio_subleading_nofudge;
   Float_t         E1_E2_leading;
   Float_t         etaS2_leading;
   Float_t         etaS2_subleading;
   Float_t         ptvarcone20_leading;
   Float_t         ptcone20_leading;
   Float_t         ptvarcone40_leading;
   Float_t         ptcone40_leading;
   Float_t         topoetcone20_Pt_leading;
   Float_t         ptvarcone20_Pt_leading;
   Float_t         ptcone20_subleading;
   Float_t         ptcone40_subleading;
   Float_t         DD_corr_40_leading;
   Float_t         DD_corr_40_subleading;
   Float_t         DD_corr_20_leading;
   Float_t         DD_corr_20_subleading;
   vector<float>   *topoetcone40;
   vector<float>   *topoetcone30;
   vector<float>   *topoetcone20;
   vector<float>   *ptcone40;
   vector<float>   *ptcone30;
   vector<float>   *ptcone20;
   vector<float>   *ptvarcone40;
   vector<float>   *ptvarcone30;
   vector<float>   *ptvarcone20;
   Bool_t          FixedCutTightCaloOnly_ld;
   Bool_t          FixedCutTight_ld;
   Bool_t          FixedCutLoose_ld;
   Bool_t          FixedCutTightCaloOnly_subld;
   Bool_t          FixedCutTight_subld;
   Bool_t          FixedCutLoose_subld;
   Bool_t          pass_truth_match;
   Int_t           parent_pdgID_truth_ld;
   Int_t           parent_pdgID_truth_subld;
   Int_t           origin_truth_ld;
   Int_t           origin_truth_subld;
   vector<float>   *ph_pt;
   vector<float>   *ph_eta;
   vector<float>   *ph_etas2;
   vector<float>   *ph_phi;
   vector<float>   *ph_cl_phi;
   vector<int>     *ph_parent_pdgID;
   vector<bool>    *ph_tight;
   vector<bool>    *ph_matched;
   Bool_t          two_truth_photons;
   Bool_t          pass_eta_truth_analysis;
   TLorentzVector  *truth_leading_LV;
   TLorentzVector  *truth_subleading_LV;
   TLorentzVector  *truth_diphoton_LV;
   Bool_t          truth_leading_matched_leading_ph;
   Bool_t          truth_subleading_matched_subleading_ph;
   Float_t         mass_EG_RESOLUTION_ALL__1down;
   Float_t         mass_EG_RESOLUTION_ALL__1up;
   Float_t         mass_EG_SCALE_ALL__1down;
   Float_t         mass_EG_SCALE_ALL__1up;
   Float_t         mass_PH_EFF_ID_Uncertainty__1down;
   Float_t         mass_PH_EFF_ID_Uncertainty__1up;
   Float_t         mass_PH_EFF_TRKISO_Uncertainty__1down;
   Float_t         mass_PH_EFF_TRKISO_Uncertainty__1up;
   Float_t         mass_PH_Iso_DDonoff;
   Float_t         mass_PRW_DATASF__1down;
   Float_t         mass_PRW_DATASF__1up;
   Float_t         event_weight_EG_RESOLUTION_ALL__1down;
   Float_t         event_weight_EG_RESOLUTION_ALL__1up;
   Float_t         event_weight_EG_SCALE_ALL__1down;
   Float_t         event_weight_EG_SCALE_ALL__1up;
   Float_t         event_weight_PH_EFF_ID_Uncertainty__1down;
   Float_t         event_weight_PH_EFF_ID_Uncertainty__1up;
   Float_t         event_weight_PH_EFF_TRKISO_Uncertainty__1down;
   Float_t         event_weight_PH_EFF_TRKISO_Uncertainty__1up;
   Float_t         event_weight_PH_Iso_DDonoff;
   Float_t         event_weight_PRW_DATASF__1down;
   Float_t         event_weight_PRW_DATASF__1up;
   Int_t           accepted_EG_RESOLUTION_ALL__1down;
   Int_t           accepted_EG_RESOLUTION_ALL__1up;
   Int_t           accepted_EG_SCALE_ALL__1down;
   Int_t           accepted_EG_SCALE_ALL__1up;
   Int_t           accepted_PH_EFF_ID_Uncertainty__1down;
   Int_t           accepted_PH_EFF_ID_Uncertainty__1up;
   Int_t           accepted_PH_EFF_TRKISO_Uncertainty__1down;
   Int_t           accepted_PH_EFF_TRKISO_Uncertainty__1up;
   Int_t           accepted_PH_Iso_DDonoff;
   Int_t           accepted_PRW_DATASF__1down;
   Int_t           accepted_PRW_DATASF__1up;
   TLorentzVector  *leading_LV_EG_RESOLUTION_ALL__1down;
   TLorentzVector  *leading_LV_EG_RESOLUTION_ALL__1up;
   TLorentzVector  *leading_LV_EG_SCALE_ALL__1down;
   TLorentzVector  *leading_LV_EG_SCALE_ALL__1up;
   TLorentzVector  *leading_LV_PH_EFF_ID_Uncertainty__1down;
   TLorentzVector  *leading_LV_PH_EFF_ID_Uncertainty__1up;
   TLorentzVector  *leading_LV_PH_EFF_TRKISO_Uncertainty__1down;
   TLorentzVector  *leading_LV_PH_EFF_TRKISO_Uncertainty__1up;
   TLorentzVector  *leading_LV_PH_Iso_DDonoff;
   TLorentzVector  *leading_LV_PRW_DATASF__1down;
   TLorentzVector  *leading_LV_PRW_DATASF__1up;
   TLorentzVector  *subleading_LV_EG_RESOLUTION_ALL__1down;
   TLorentzVector  *subleading_LV_EG_RESOLUTION_ALL__1up;
   TLorentzVector  *subleading_LV_EG_SCALE_ALL__1down;
   TLorentzVector  *subleading_LV_EG_SCALE_ALL__1up;
   TLorentzVector  *subleading_LV_PH_EFF_ID_Uncertainty__1down;
   TLorentzVector  *subleading_LV_PH_EFF_ID_Uncertainty__1up;
   TLorentzVector  *subleading_LV_PH_EFF_TRKISO_Uncertainty__1down;
   TLorentzVector  *subleading_LV_PH_EFF_TRKISO_Uncertainty__1up;
   TLorentzVector  *subleading_LV_PH_Iso_DDonoff;
   TLorentzVector  *subleading_LV_PRW_DATASF__1down;
   TLorentzVector  *subleading_LV_PRW_DATASF__1up;
   TLorentzVector  *diphoton_LV_EG_RESOLUTION_ALL__1down;
   TLorentzVector  *diphoton_LV_EG_RESOLUTION_ALL__1up;
   TLorentzVector  *diphoton_LV_EG_SCALE_ALL__1down;
   TLorentzVector  *diphoton_LV_EG_SCALE_ALL__1up;
   TLorentzVector  *diphoton_LV_PH_EFF_ID_Uncertainty__1down;
   TLorentzVector  *diphoton_LV_PH_EFF_ID_Uncertainty__1up;
   TLorentzVector  *diphoton_LV_PH_EFF_TRKISO_Uncertainty__1down;
   TLorentzVector  *diphoton_LV_PH_EFF_TRKISO_Uncertainty__1up;
   TLorentzVector  *diphoton_LV_PH_Iso_DDonoff;
   TLorentzVector  *diphoton_LV_PRW_DATASF__1down;
   TLorentzVector  *diphoton_LV_PRW_DATASF__1up;
   Float_t         topoetcone40_leading_EG_RESOLUTION_ALL__1down;
   Float_t         topoetcone40_leading_EG_RESOLUTION_ALL__1up;
   Float_t         topoetcone40_leading_EG_SCALE_ALL__1down;
   Float_t         topoetcone40_leading_EG_SCALE_ALL__1up;
   Float_t         topoetcone40_leading_PH_EFF_ID_Uncertainty__1down;
   Float_t         topoetcone40_leading_PH_EFF_ID_Uncertainty__1up;
   Float_t         topoetcone40_leading_PH_EFF_TRKISO_Uncertainty__1down;
   Float_t         topoetcone40_leading_PH_EFF_TRKISO_Uncertainty__1up;
   Float_t         topoetcone40_leading_PH_Iso_DDonoff;
   Float_t         topoetcone40_leading_PRW_DATASF__1down;
   Float_t         topoetcone40_leading_PRW_DATASF__1up;
   Float_t         topoetcone40_subleading_EG_RESOLUTION_ALL__1down;
   Float_t         topoetcone40_subleading_EG_RESOLUTION_ALL__1up;
   Float_t         topoetcone40_subleading_EG_SCALE_ALL__1down;
   Float_t         topoetcone40_subleading_EG_SCALE_ALL__1up;
   Float_t         topoetcone40_subleading_PH_EFF_ID_Uncertainty__1down;
   Float_t         topoetcone40_subleading_PH_EFF_ID_Uncertainty__1up;
   Float_t         topoetcone40_subleading_PH_EFF_TRKISO_Uncertainty__1down;
   Float_t         topoetcone40_subleading_PH_EFF_TRKISO_Uncertainty__1up;
   Float_t         topoetcone40_subleading_PH_Iso_DDonoff;
   Float_t         topoetcone40_subleading_PRW_DATASF__1down;
   Float_t         topoetcone40_subleading_PRW_DATASF__1up;

   // List of branches
   TBranch        *b_all;   //!
   TBranch        *b_pass_dalitz;   //!
   TBranch        *b_pass_trigger;   //!
   TBranch        *b_pass_grl;   //!
   TBranch        *b_pass_detector_DQ;   //!
   TBranch        *b_pass_PV;   //!
   TBranch        *b_pass_preselection;   //!
   TBranch        *b_pass_ld_subld_id;   //!
   TBranch        *b_pass_ld_subld_isol;   //!
   TBranch        *b_pass_ld_subld_Et;   //!
   TBranch        *b_pass_ld_subld_rel_cuts;   //!
   TBranch        *b_accepted;   //!
   TBranch        *b_accepted_nominal;   //!
   TBranch        *b_category;   //!
   TBranch        *b_pass_egamma_selection;   //!
   TBranch        *b_isEM_0_ld;   //!
   TBranch        *b_isEM_0_subld;   //!
   TBranch        *b_isEM_nofudge_0_ld;   //!
   TBranch        *b_isEM_1_ld;   //!
   TBranch        *b_isEM_1_subld;   //!
   TBranch        *b_isEM_nofudge_1_ld;   //!
   TBranch        *b_isEM_2_ld;   //!
   TBranch        *b_isEM_2_subld;   //!
   TBranch        *b_isEM_nofudge_2_ld;   //!
   TBranch        *b_isEM_3_ld;   //!
   TBranch        *b_isEM_3_subld;   //!
   TBranch        *b_isEM_nofudge_3_ld;   //!
   TBranch        *b_isEM_4_ld;   //!
   TBranch        *b_isEM_4_subld;   //!
   TBranch        *b_isEM_nofudge_4_ld;   //!
   TBranch        *b_isEM_5_ld;   //!
   TBranch        *b_isEM_5_subld;   //!
   TBranch        *b_isEM_nofudge_5_ld;   //!
   TBranch        *b_isEM_6_ld;   //!
   TBranch        *b_isEM_6_subld;   //!
   TBranch        *b_isEM_nofudge_6_ld;   //!
   TBranch        *b_isEM_7_ld;   //!
   TBranch        *b_isEM_7_subld;   //!
   TBranch        *b_isEM_nofudge_7_ld;   //!
   TBranch        *b_isEM_8_ld;   //!
   TBranch        *b_isEM_8_subld;   //!
   TBranch        *b_isEM_nofudge_8_ld;   //!
   TBranch        *b_isEM_9_ld;   //!
   TBranch        *b_isEM_9_subld;   //!
   TBranch        *b_isEM_nofudge_9_ld;   //!
   TBranch        *b_isEM_10_ld;   //!
   TBranch        *b_isEM_10_subld;   //!
   TBranch        *b_isEM_nofudge_10_ld;   //!
   TBranch        *b_isEM_11_ld;   //!
   TBranch        *b_isEM_11_subld;   //!
   TBranch        *b_isEM_nofudge_11_ld;   //!
   TBranch        *b_isEM_12_ld;   //!
   TBranch        *b_isEM_12_subld;   //!
   TBranch        *b_isEM_nofudge_12_ld;   //!
   TBranch        *b_isEM_13_ld;   //!
   TBranch        *b_isEM_13_subld;   //!
   TBranch        *b_isEM_nofudge_13_ld;   //!
   TBranch        *b_isEM_14_ld;   //!
   TBranch        *b_isEM_14_subld;   //!
   TBranch        *b_isEM_nofudge_14_ld;   //!
   TBranch        *b_isEM_15_ld;   //!
   TBranch        *b_isEM_15_subld;   //!
   TBranch        *b_isEM_nofudge_15_ld;   //!
   TBranch        *b_isEM_16_ld;   //!
   TBranch        *b_isEM_16_subld;   //!
   TBranch        *b_isEM_nofudge_16_ld;   //!
   TBranch        *b_isEM_17_ld;   //!
   TBranch        *b_isEM_17_subld;   //!
   TBranch        *b_isEM_nofudge_17_ld;   //!
   TBranch        *b_isEM_18_ld;   //!
   TBranch        *b_isEM_18_subld;   //!
   TBranch        *b_isEM_nofudge_18_ld;   //!
   TBranch        *b_isEM_19_ld;   //!
   TBranch        *b_isEM_19_subld;   //!
   TBranch        *b_isEM_nofudge_19_ld;   //!
   TBranch        *b_isEM_20_ld;   //!
   TBranch        *b_isEM_20_subld;   //!
   TBranch        *b_isEM_nofudge_20_ld;   //!
   TBranch        *b_isEM_21_ld;   //!
   TBranch        *b_isEM_21_subld;   //!
   TBranch        *b_isEM_nofudge_21_ld;   //!
   TBranch        *b_pass_2g50_loose_trigger;   //!
   TBranch        *b_pass_g35_g25_loose_trigger;   //!
   TBranch        *b_averageIntPerXing;   //!
   TBranch        *b_ED_central;   //!
   TBranch        *b_ED_forward;   //!
   TBranch        *b_run_number;   //!
   TBranch        *b_event_number;   //!
   TBranch        *b_lumiblock_number;   //!
   TBranch        *b_time_stamp;   //!
   TBranch        *b_bcid;   //!
   TBranch        *b_mc_channel_number;   //!
   TBranch        *b_mc_event_number;   //!
   TBranch        *b_nPV;   //!
   TBranch        *b_xs;   //!
   TBranch        *b_xs_ami;   //!
   TBranch        *b_filter_eff;   //!
   TBranch        *b_filter_eff_ami;   //!
   TBranch        *b_one_photon;   //!
   TBranch        *b_two_photons;   //!
   TBranch        *b_pileup_weight;   //!
   TBranch        *b_vertex_weight;   //!
   TBranch        *b_MC_weight;   //!
   TBranch        *b_xs_weight;   //!
   TBranch        *b_event_weight;   //!
   TBranch        *b_prel_weight;   //!
   TBranch        *b_total_weight;   //!
   TBranch        *b_total_events;   //!
   TBranch        *b_non_derived_total_events;   //!
   TBranch        *b_weight_sum_before;   //!
   TBranch        *b_SF_leading;   //!
   TBranch        *b_SF_unc_leading;   //!
   TBranch        *b_SF_subleading;   //!
   TBranch        *b_SF_unc_subleading;   //!
   TBranch        *b_SF_diphoton;   //!
   TBranch        *b_SF_1UP_diphoton;   //!
   TBranch        *b_SF_1DOWN_diphoton;   //!
   TBranch        *b_sumpt2_tracks;   //!
   TBranch        *b_mass_gev;   //!
   TBranch        *b_mass_MVA;   //!
   TBranch        *b_mgg;   //!
   TBranch        *b_mass_raw;   //!
   TBranch        *b_mass_egamma;   //!
   TBranch        *b_mass;   //!
   TBranch        *b_costhetastar;   //!
   TBranch        *b_deltaphi;   //!
   TBranch        *b_LV_leading;   //!
   TBranch        *b_LV_subleading;   //!
   TBranch        *b_LV_diphoton;   //!
   TBranch        *b_LV_egamma;   //!
   TBranch        *b_pt_subleading;   //!
   TBranch        *b_pt_leading;   //!
   TBranch        *b_phi_subleading;   //!
   TBranch        *b_phi_leading;   //!
   TBranch        *b_eta_subleading;   //!
   TBranch        *b_eta_leading;   //!
   TBranch        *b_author_leading;   //!
   TBranch        *b_author_subleading;   //!
   TBranch        *b_raw_energy_leading;   //!
   TBranch        *b_raw_energy_subleading;   //!
   TBranch        *b_raw_et_leading;   //!
   TBranch        *b_raw_et_subleading;   //!
   TBranch        *b_e_on_eraw_leading;   //!
   TBranch        *b_e_on_eraw_subleading;   //!
   TBranch        *b_deltaR;   //!
   TBranch        *b_max_cell_gain_leading;   //!
   TBranch        *b_max_cell_time_leading;   //!
   TBranch        *b_max_cell_e_leading;   //!
   TBranch        *b_max_cell_gain_subleading;   //!
   TBranch        *b_max_cell_time_subleading;   //!
   TBranch        *b_max_cell_e_subleading;   //!
   TBranch        *b_Rconv_leading;   //!
   TBranch        *b_Rconv_subleading;   //!
   TBranch        *b_E0_leading;   //!
   TBranch        *b_E1_leading;   //!
   TBranch        *b_E2_leading;   //!
   TBranch        *b_E3_leading;   //!
   TBranch        *b_E0_subleading;   //!
   TBranch        *b_E1_subleading;   //!
   TBranch        *b_E2_subleading;   //!
   TBranch        *b_E3_subleading;   //!
   TBranch        *b_Zconv_leading;   //!
   TBranch        *b_Zconv_subleading;   //!
   TBranch        *b_PVz;   //!
   TBranch        *b_topoetcone40_leading;   //!
   TBranch        *b_topoetcone40_DDcorrected_leading;   //!
   TBranch        *b_topoetcone40_rel17_leading;   //!
   TBranch        *b_topoetcone40_electron_leading;   //!
   TBranch        *b_topoetcone40_trouble_electron_leading;   //!
   TBranch        *b_topoetcone40_rel17_electron_leading;   //!
   TBranch        *b_author_electron_leading;   //!
   TBranch        *b_topoetcone40_subleading;   //!
   TBranch        *b_topoetcone40_DDcorrected_subleading;   //!
   TBranch        *b_topoetcone20_leading;   //!
   TBranch        *b_topoetcone20_subleading;   //!
   TBranch        *b_truth_etcone40_leading;   //!
   TBranch        *b_truth_etcone40_subleading;   //!
   TBranch        *b_truth_etcone20_leading;   //!
   TBranch        *b_truth_etcone20_subleading;   //!
   TBranch        *b_truth_local_etcone40_leading;   //!
   TBranch        *b_truth_local_etcone40_subleading;   //!
   TBranch        *b_truth_local_etcone20_leading;   //!
   TBranch        *b_truth_local_etcone20_subleading;   //!
   TBranch        *b_truth_etcone40_PUcorr_leading;   //!
   TBranch        *b_truth_etcone40_PUcorr_subleading;   //!
   TBranch        *b_truth_etcone20_PUcorr_leading;   //!
   TBranch        *b_truth_etcone20_PUcorr_subleading;   //!
   TBranch        *b_truth_ptcone40_leading;   //!
   TBranch        *b_truth_ptcone40_subleading;   //!
   TBranch        *b_truth_ptcone20_leading;   //!
   TBranch        *b_truth_ptcone20_subleading;   //!
   TBranch        *b_truth_ptcone40_PUcorr_leading;   //!
   TBranch        *b_truth_ptcone40_PUcorr_subleading;   //!
   TBranch        *b_truth_ptcone20_PUcorr_leading;   //!
   TBranch        *b_truth_ptcone20_PUcorr_subleading;   //!
   TBranch        *b_truth_rho_central;   //!
   TBranch        *b_truth_rho_forward;   //!
   TBranch        *b_tight_leading;   //!
   TBranch        *b_my_tight_leading;   //!
   TBranch        *b_loose_leading;   //!
   TBranch        *b_loose_prime_leading;   //!
   TBranch        *b_tight_subleading;   //!
   TBranch        *b_loose_subleading;   //!
   TBranch        *b_loose_prime_subleading;   //!
   TBranch        *b_bg_truth_match_leading;   //!
   TBranch        *b_bg_truth_match_origin_leading;   //!
   TBranch        *b_pdgID_leading;   //!
   TBranch        *b_parent_pdgID_leading;   //!
   TBranch        *b_type_leading;   //!
   TBranch        *b_origin_leading;   //!
   TBranch        *b_truth_match_leading;   //!
   TBranch        *b_pdgID_subleading;   //!
   TBranch        *b_parent_pdgID_subleading;   //!
   TBranch        *b_type_subleading;   //!
   TBranch        *b_origin_subleading;   //!
   TBranch        *b_truth_match_subleading;   //!
   TBranch        *b_conv_leading;   //!
   TBranch        *b_conv_subleading;   //!
   TBranch        *b_isEM_leading;   //!
   TBranch        *b_isEM_subleading;   //!
   TBranch        *b_isEM_nofudge_leading;   //!
   TBranch        *b_isEM_nofudge_subleading;   //!
   TBranch        *b_photonOQ_leading;   //!
   TBranch        *b_photonOQ_subleading;   //!
   TBranch        *b_Z_pointing_leading;   //!
   TBranch        *b_Z_pointing_subleading;   //!
   TBranch        *b_Rhad_leading;   //!
   TBranch        *b_e277_leading;   //!
   TBranch        *b_Reta_leading;   //!
   TBranch        *b_Rphi_leading;   //!
   TBranch        *b_weta2_leading;   //!
   TBranch        *b_f1_leading;   //!
   TBranch        *b_DeltaE_leading;   //!
   TBranch        *b_wtots1_leading;   //!
   TBranch        *b_fracs1_leading;   //!
   TBranch        *b_weta1_leading;   //!
   TBranch        *b_Eratio_leading;   //!
   TBranch        *b_Rhad_subleading;   //!
   TBranch        *b_e277_subleading;   //!
   TBranch        *b_Reta_subleading;   //!
   TBranch        *b_Rphi_subleading;   //!
   TBranch        *b_weta2_subleading;   //!
   TBranch        *b_f1_subleading;   //!
   TBranch        *b_DeltaE_subleading;   //!
   TBranch        *b_wtots1_subleading;   //!
   TBranch        *b_fracs1_subleading;   //!
   TBranch        *b_weta1_subleading;   //!
   TBranch        *b_Eratio_subleading;   //!
   TBranch        *b_Rhad_leading_nofudge;   //!
   TBranch        *b_e277_leading_nofudge;   //!
   TBranch        *b_Reta_leading_nofudge;   //!
   TBranch        *b_Rphi_leading_nofudge;   //!
   TBranch        *b_weta2_leading_nofudge;   //!
   TBranch        *b_f1_leading_nofudge;   //!
   TBranch        *b_DeltaE_leading_nofudge;   //!
   TBranch        *b_wtots1_leading_nofudge;   //!
   TBranch        *b_fracs1_leading_nofudge;   //!
   TBranch        *b_weta1_leading_nofudge;   //!
   TBranch        *b_Eratio_leading_nofudge;   //!
   TBranch        *b_Rhad_subleading_nofudge;   //!
   TBranch        *b_e277_subleading_nofudge;   //!
   TBranch        *b_Reta_subleading_nofudge;   //!
   TBranch        *b_Rphi_subleading_nofudge;   //!
   TBranch        *b_weta2_subleading_nofudge;   //!
   TBranch        *b_f1_subleading_nofudge;   //!
   TBranch        *b_DeltaE_subleading_nofudge;   //!
   TBranch        *b_wtots1_subleading_nofudge;   //!
   TBranch        *b_fracs1_subleading_nofudge;   //!
   TBranch        *b_weta1_subleading_nofudge;   //!
   TBranch        *b_Eratio_subleading_nofudge;   //!
   TBranch        *b_E1_E2_leading;   //!
   TBranch        *b_etaS2_leading;   //!
   TBranch        *b_etaS2_subleading;   //!
   TBranch        *b_ptvarcone20_leading;   //!
   TBranch        *b_ptcone20_leading;   //!
   TBranch        *b_ptvarcone40_leading;   //!
   TBranch        *b_ptcone40_leading;   //!
   TBranch        *b_topoetcone20_Pt_leading;   //!
   TBranch        *b_ptvarcone20_Pt_leading;   //!
   TBranch        *b_ptcone20_subleading;   //!
   TBranch        *b_ptcone40_subleading;   //!
   TBranch        *b_DD_corr_40_leading;   //!
   TBranch        *b_DD_corr_40_subleading;   //!
   TBranch        *b_DD_corr_20_leading;   //!
   TBranch        *b_DD_corr_20_subleading;   //!
   TBranch        *b_topoetcone40;   //!
   TBranch        *b_topoetcone30;   //!
   TBranch        *b_topoetcone20;   //!
   TBranch        *b_ptcone40;   //!
   TBranch        *b_ptcone30;   //!
   TBranch        *b_ptcone20;   //!
   TBranch        *b_ptvarcone40;   //!
   TBranch        *b_ptvarcone30;   //!
   TBranch        *b_ptvarcone20;   //!
   TBranch        *b_FixedCutTightCaloOnly_ld;   //!
   TBranch        *b_FixedCutTight_ld;   //!
   TBranch        *b_FixedCutLoose_ld;   //!
   TBranch        *b_FixedCutTightCaloOnly_subld;   //!
   TBranch        *b_FixedCutTight_subld;   //!
   TBranch        *b_FixedCutLoose_subld;   //!
   TBranch        *b_pass_truth_match;   //!
   TBranch        *b_parent_pdgID_truth_ld;   //!
   TBranch        *b_parent_pdgID_truth_subld;   //!
   TBranch        *b_origin_truth_ld;   //!
   TBranch        *b_origin_truth_subld;   //!
   TBranch        *b_ph_pt;   //!
   TBranch        *b_ph_eta;   //!
   TBranch        *b_ph_etas2;   //!
   TBranch        *b_ph_phi;   //!
   TBranch        *b_ph_cl_phi;   //!
   TBranch        *b_ph_parent_pdgID;   //!
   TBranch        *b_ph_tight;   //!
   TBranch        *b_ph_matched;   //!
   TBranch        *b_two_truth_photons;   //!
   TBranch        *b_pass_eta_truth_analysis;   //!
   TBranch        *b_truth_leading_LV;   //!
   TBranch        *b_truth_subleading_LV;   //!
   TBranch        *b_truth_diphoton_LV;   //!
   TBranch        *b_truth_leading_matched_leading_ph;   //!
   TBranch        *b_truth_subleading_matched_subleading_ph;   //!
   TBranch        *b_mass_EG_RESOLUTION_ALL__1down;   //!
   TBranch        *b_mass_EG_RESOLUTION_ALL__1up;   //!
   TBranch        *b_mass_EG_SCALE_ALL__1down;   //!
   TBranch        *b_mass_EG_SCALE_ALL__1up;   //!
   TBranch        *b_mass_PH_EFF_ID_Uncertainty__1down;   //!
   TBranch        *b_mass_PH_EFF_ID_Uncertainty__1up;   //!
   TBranch        *b_mass_PH_EFF_TRKISO_Uncertainty__1down;   //!
   TBranch        *b_mass_PH_EFF_TRKISO_Uncertainty__1up;   //!
   TBranch        *b_mass_PH_Iso_DDonoff;   //!
   TBranch        *b_mass_PRW_DATASF__1down;   //!
   TBranch        *b_mass_PRW_DATASF__1up;   //!
   TBranch        *b_event_weight_EG_RESOLUTION_ALL__1down;   //!
   TBranch        *b_event_weight_EG_RESOLUTION_ALL__1up;   //!
   TBranch        *b_event_weight_EG_SCALE_ALL__1down;   //!
   TBranch        *b_event_weight_EG_SCALE_ALL__1up;   //!
   TBranch        *b_event_weight_PH_EFF_ID_Uncertainty__1down;   //!
   TBranch        *b_event_weight_PH_EFF_ID_Uncertainty__1up;   //!
   TBranch        *b_event_weight_PH_EFF_TRKISO_Uncertainty__1down;   //!
   TBranch        *b_event_weight_PH_EFF_TRKISO_Uncertainty__1up;   //!
   TBranch        *b_event_weight_PH_Iso_DDonoff;   //!
   TBranch        *b_event_weight_PRW_DATASF__1down;   //!
   TBranch        *b_event_weight_PRW_DATASF__1up;   //!
   TBranch        *b_accepted_EG_RESOLUTION_ALL__1down;   //!
   TBranch        *b_accepted_EG_RESOLUTION_ALL__1up;   //!
   TBranch        *b_accepted_EG_SCALE_ALL__1down;   //!
   TBranch        *b_accepted_EG_SCALE_ALL__1up;   //!
   TBranch        *b_accepted_PH_EFF_ID_Uncertainty__1down;   //!
   TBranch        *b_accepted_PH_EFF_ID_Uncertainty__1up;   //!
   TBranch        *b_accepted_PH_EFF_TRKISO_Uncertainty__1down;   //!
   TBranch        *b_accepted_PH_EFF_TRKISO_Uncertainty__1up;   //!
   TBranch        *b_accepted_PH_Iso_DDonoff;   //!
   TBranch        *b_accepted_PRW_DATASF__1down;   //!
   TBranch        *b_accepted_PRW_DATASF__1up;   //!
   TBranch        *b_leading_LV_EG_RESOLUTION_ALL__1down;   //!
   TBranch        *b_leading_LV_EG_RESOLUTION_ALL__1up;   //!
   TBranch        *b_leading_LV_EG_SCALE_ALL__1down;   //!
   TBranch        *b_leading_LV_EG_SCALE_ALL__1up;   //!
   TBranch        *b_leading_LV_PH_EFF_ID_Uncertainty__1down;   //!
   TBranch        *b_leading_LV_PH_EFF_ID_Uncertainty__1up;   //!
   TBranch        *b_leading_LV_PH_EFF_TRKISO_Uncertainty__1down;   //!
   TBranch        *b_leading_LV_PH_EFF_TRKISO_Uncertainty__1up;   //!
   TBranch        *b_leading_LV_PH_Iso_DDonoff;   //!
   TBranch        *b_leading_LV_PRW_DATASF__1down;   //!
   TBranch        *b_leading_LV_PRW_DATASF__1up;   //!
   TBranch        *b_subleading_LV_EG_RESOLUTION_ALL__1down;   //!
   TBranch        *b_subleading_LV_EG_RESOLUTION_ALL__1up;   //!
   TBranch        *b_subleading_LV_EG_SCALE_ALL__1down;   //!
   TBranch        *b_subleading_LV_EG_SCALE_ALL__1up;   //!
   TBranch        *b_subleading_LV_PH_EFF_ID_Uncertainty__1down;   //!
   TBranch        *b_subleading_LV_PH_EFF_ID_Uncertainty__1up;   //!
   TBranch        *b_subleading_LV_PH_EFF_TRKISO_Uncertainty__1down;   //!
   TBranch        *b_subleading_LV_PH_EFF_TRKISO_Uncertainty__1up;   //!
   TBranch        *b_subleading_LV_PH_Iso_DDonoff;   //!
   TBranch        *b_subleading_LV_PRW_DATASF__1down;   //!
   TBranch        *b_subleading_LV_PRW_DATASF__1up;   //!
   TBranch        *b_diphoton_LV_EG_RESOLUTION_ALL__1down;   //!
   TBranch        *b_diphoton_LV_EG_RESOLUTION_ALL__1up;   //!
   TBranch        *b_diphoton_LV_EG_SCALE_ALL__1down;   //!
   TBranch        *b_diphoton_LV_EG_SCALE_ALL__1up;   //!
   TBranch        *b_diphoton_LV_PH_EFF_ID_Uncertainty__1down;   //!
   TBranch        *b_diphoton_LV_PH_EFF_ID_Uncertainty__1up;   //!
   TBranch        *b_diphoton_LV_PH_EFF_TRKISO_Uncertainty__1down;   //!
   TBranch        *b_diphoton_LV_PH_EFF_TRKISO_Uncertainty__1up;   //!
   TBranch        *b_diphoton_LV_PH_Iso_DDonoff;   //!
   TBranch        *b_diphoton_LV_PRW_DATASF__1down;   //!
   TBranch        *b_diphoton_LV_PRW_DATASF__1up;   //!
   TBranch        *b_topoetcone40_leading_EG_RESOLUTION_ALL__1down;   //!
   TBranch        *b_topoetcone40_leading_EG_RESOLUTION_ALL__1up;   //!
   TBranch        *b_topoetcone40_leading_EG_SCALE_ALL__1down;   //!
   TBranch        *b_topoetcone40_leading_EG_SCALE_ALL__1up;   //!
   TBranch        *b_topoetcone40_leading_PH_EFF_ID_Uncertainty__1down;   //!
   TBranch        *b_topoetcone40_leading_PH_EFF_ID_Uncertainty__1up;   //!
   TBranch        *b_topoetcone40_leading_PH_EFF_TRKISO_Uncertainty__1down;   //!
   TBranch        *b_topoetcone40_leading_PH_EFF_TRKISO_Uncertainty__1up;   //!
   TBranch        *b_topoetcone40_leading_PH_Iso_DDonoff;   //!
   TBranch        *b_topoetcone40_leading_PRW_DATASF__1down;   //!
   TBranch        *b_topoetcone40_leading_PRW_DATASF__1up;   //!
   TBranch        *b_topoetcone40_subleading_EG_RESOLUTION_ALL__1down;   //!
   TBranch        *b_topoetcone40_subleading_EG_RESOLUTION_ALL__1up;   //!
   TBranch        *b_topoetcone40_subleading_EG_SCALE_ALL__1down;   //!
   TBranch        *b_topoetcone40_subleading_EG_SCALE_ALL__1up;   //!
   TBranch        *b_topoetcone40_subleading_PH_EFF_ID_Uncertainty__1down;   //!
   TBranch        *b_topoetcone40_subleading_PH_EFF_ID_Uncertainty__1up;   //!
   TBranch        *b_topoetcone40_subleading_PH_EFF_TRKISO_Uncertainty__1down;   //!
   TBranch        *b_topoetcone40_subleading_PH_EFF_TRKISO_Uncertainty__1up;   //!
   TBranch        *b_topoetcone40_subleading_PH_Iso_DDonoff;   //!
   TBranch        *b_topoetcone40_subleading_PRW_DATASF__1down;   //!
   TBranch        *b_topoetcone40_subleading_PRW_DATASF__1up;   //!

   gravitonNtup(TTree *tree=0);
   virtual ~gravitonNtup();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef gravitonNtup_cxx
gravitonNtup::gravitonNtup(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Output/Graviton/single_sample/mc15_m500_k01.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("Output/Graviton/single_sample/mc15_m500_k01.root");
      }
      f->GetObject("gravitonNtup",tree);

   }
   Init(tree);
}

gravitonNtup::~gravitonNtup()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t gravitonNtup::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t gravitonNtup::LoadTree(Long64_t entry)
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

void gravitonNtup::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   LV_leading = 0;
   LV_subleading = 0;
   LV_diphoton = 0;
   LV_egamma = 0;
   topoetcone40 = 0;
   topoetcone30 = 0;
   topoetcone20 = 0;
   ptcone40 = 0;
   ptcone30 = 0;
   ptcone20 = 0;
   ptvarcone40 = 0;
   ptvarcone30 = 0;
   ptvarcone20 = 0;
   ph_pt = 0;
   ph_eta = 0;
   ph_etas2 = 0;
   ph_phi = 0;
   ph_cl_phi = 0;
   ph_parent_pdgID = 0;
   ph_tight = 0;
   ph_matched = 0;
   truth_leading_LV = 0;
   truth_subleading_LV = 0;
   truth_diphoton_LV = 0;
   leading_LV_EG_RESOLUTION_ALL__1down = 0;
   leading_LV_EG_RESOLUTION_ALL__1up = 0;
   leading_LV_EG_SCALE_ALL__1down = 0;
   leading_LV_EG_SCALE_ALL__1up = 0;
   leading_LV_PH_EFF_ID_Uncertainty__1down = 0;
   leading_LV_PH_EFF_ID_Uncertainty__1up = 0;
   leading_LV_PH_EFF_TRKISO_Uncertainty__1down = 0;
   leading_LV_PH_EFF_TRKISO_Uncertainty__1up = 0;
   leading_LV_PH_Iso_DDonoff = 0;
   leading_LV_PRW_DATASF__1down = 0;
   leading_LV_PRW_DATASF__1up = 0;
   subleading_LV_EG_RESOLUTION_ALL__1down = 0;
   subleading_LV_EG_RESOLUTION_ALL__1up = 0;
   subleading_LV_EG_SCALE_ALL__1down = 0;
   subleading_LV_EG_SCALE_ALL__1up = 0;
   subleading_LV_PH_EFF_ID_Uncertainty__1down = 0;
   subleading_LV_PH_EFF_ID_Uncertainty__1up = 0;
   subleading_LV_PH_EFF_TRKISO_Uncertainty__1down = 0;
   subleading_LV_PH_EFF_TRKISO_Uncertainty__1up = 0;
   subleading_LV_PH_Iso_DDonoff = 0;
   subleading_LV_PRW_DATASF__1down = 0;
   subleading_LV_PRW_DATASF__1up = 0;
   diphoton_LV_EG_RESOLUTION_ALL__1down = 0;
   diphoton_LV_EG_RESOLUTION_ALL__1up = 0;
   diphoton_LV_EG_SCALE_ALL__1down = 0;
   diphoton_LV_EG_SCALE_ALL__1up = 0;
   diphoton_LV_PH_EFF_ID_Uncertainty__1down = 0;
   diphoton_LV_PH_EFF_ID_Uncertainty__1up = 0;
   diphoton_LV_PH_EFF_TRKISO_Uncertainty__1down = 0;
   diphoton_LV_PH_EFF_TRKISO_Uncertainty__1up = 0;
   diphoton_LV_PH_Iso_DDonoff = 0;
   diphoton_LV_PRW_DATASF__1down = 0;
   diphoton_LV_PRW_DATASF__1up = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("all", &all, &b_all);
   fChain->SetBranchAddress("pass_dalitz", &pass_dalitz, &b_pass_dalitz);
   fChain->SetBranchAddress("pass_trigger", &pass_trigger, &b_pass_trigger);
   fChain->SetBranchAddress("pass_grl", &pass_grl, &b_pass_grl);
   fChain->SetBranchAddress("pass_detector_DQ", &pass_detector_DQ, &b_pass_detector_DQ);
   fChain->SetBranchAddress("pass_PV", &pass_PV, &b_pass_PV);
   fChain->SetBranchAddress("pass_preselection", &pass_preselection, &b_pass_preselection);
   fChain->SetBranchAddress("pass_ld_subld_id", &pass_ld_subld_id, &b_pass_ld_subld_id);
   fChain->SetBranchAddress("pass_ld_subld_isol", &pass_ld_subld_isol, &b_pass_ld_subld_isol);
   fChain->SetBranchAddress("pass_ld_subld_Et", &pass_ld_subld_Et, &b_pass_ld_subld_Et);
   fChain->SetBranchAddress("pass_ld_subld_rel_cuts", &pass_ld_subld_rel_cuts, &b_pass_ld_subld_rel_cuts);
   fChain->SetBranchAddress("accepted", &accepted, &b_accepted);
   fChain->SetBranchAddress("accepted_nominal", &accepted_nominal, &b_accepted_nominal);
   fChain->SetBranchAddress("category", &category, &b_category);
   fChain->SetBranchAddress("pass_egamma_selection", &pass_egamma_selection, &b_pass_egamma_selection);
   fChain->SetBranchAddress("isEM_0_ld", &isEM_0_ld, &b_isEM_0_ld);
   fChain->SetBranchAddress("isEM_0_subld", &isEM_0_subld, &b_isEM_0_subld);
   fChain->SetBranchAddress("isEM_nofudge_0_ld", &isEM_nofudge_0_ld, &b_isEM_nofudge_0_ld);
   fChain->SetBranchAddress("isEM_1_ld", &isEM_1_ld, &b_isEM_1_ld);
   fChain->SetBranchAddress("isEM_1_subld", &isEM_1_subld, &b_isEM_1_subld);
   fChain->SetBranchAddress("isEM_nofudge_1_ld", &isEM_nofudge_1_ld, &b_isEM_nofudge_1_ld);
   fChain->SetBranchAddress("isEM_2_ld", &isEM_2_ld, &b_isEM_2_ld);
   fChain->SetBranchAddress("isEM_2_subld", &isEM_2_subld, &b_isEM_2_subld);
   fChain->SetBranchAddress("isEM_nofudge_2_ld", &isEM_nofudge_2_ld, &b_isEM_nofudge_2_ld);
   fChain->SetBranchAddress("isEM_3_ld", &isEM_3_ld, &b_isEM_3_ld);
   fChain->SetBranchAddress("isEM_3_subld", &isEM_3_subld, &b_isEM_3_subld);
   fChain->SetBranchAddress("isEM_nofudge_3_ld", &isEM_nofudge_3_ld, &b_isEM_nofudge_3_ld);
   fChain->SetBranchAddress("isEM_4_ld", &isEM_4_ld, &b_isEM_4_ld);
   fChain->SetBranchAddress("isEM_4_subld", &isEM_4_subld, &b_isEM_4_subld);
   fChain->SetBranchAddress("isEM_nofudge_4_ld", &isEM_nofudge_4_ld, &b_isEM_nofudge_4_ld);
   fChain->SetBranchAddress("isEM_5_ld", &isEM_5_ld, &b_isEM_5_ld);
   fChain->SetBranchAddress("isEM_5_subld", &isEM_5_subld, &b_isEM_5_subld);
   fChain->SetBranchAddress("isEM_nofudge_5_ld", &isEM_nofudge_5_ld, &b_isEM_nofudge_5_ld);
   fChain->SetBranchAddress("isEM_6_ld", &isEM_6_ld, &b_isEM_6_ld);
   fChain->SetBranchAddress("isEM_6_subld", &isEM_6_subld, &b_isEM_6_subld);
   fChain->SetBranchAddress("isEM_nofudge_6_ld", &isEM_nofudge_6_ld, &b_isEM_nofudge_6_ld);
   fChain->SetBranchAddress("isEM_7_ld", &isEM_7_ld, &b_isEM_7_ld);
   fChain->SetBranchAddress("isEM_7_subld", &isEM_7_subld, &b_isEM_7_subld);
   fChain->SetBranchAddress("isEM_nofudge_7_ld", &isEM_nofudge_7_ld, &b_isEM_nofudge_7_ld);
   fChain->SetBranchAddress("isEM_8_ld", &isEM_8_ld, &b_isEM_8_ld);
   fChain->SetBranchAddress("isEM_8_subld", &isEM_8_subld, &b_isEM_8_subld);
   fChain->SetBranchAddress("isEM_nofudge_8_ld", &isEM_nofudge_8_ld, &b_isEM_nofudge_8_ld);
   fChain->SetBranchAddress("isEM_9_ld", &isEM_9_ld, &b_isEM_9_ld);
   fChain->SetBranchAddress("isEM_9_subld", &isEM_9_subld, &b_isEM_9_subld);
   fChain->SetBranchAddress("isEM_nofudge_9_ld", &isEM_nofudge_9_ld, &b_isEM_nofudge_9_ld);
   fChain->SetBranchAddress("isEM_10_ld", &isEM_10_ld, &b_isEM_10_ld);
   fChain->SetBranchAddress("isEM_10_subld", &isEM_10_subld, &b_isEM_10_subld);
   fChain->SetBranchAddress("isEM_nofudge_10_ld", &isEM_nofudge_10_ld, &b_isEM_nofudge_10_ld);
   fChain->SetBranchAddress("isEM_11_ld", &isEM_11_ld, &b_isEM_11_ld);
   fChain->SetBranchAddress("isEM_11_subld", &isEM_11_subld, &b_isEM_11_subld);
   fChain->SetBranchAddress("isEM_nofudge_11_ld", &isEM_nofudge_11_ld, &b_isEM_nofudge_11_ld);
   fChain->SetBranchAddress("isEM_12_ld", &isEM_12_ld, &b_isEM_12_ld);
   fChain->SetBranchAddress("isEM_12_subld", &isEM_12_subld, &b_isEM_12_subld);
   fChain->SetBranchAddress("isEM_nofudge_12_ld", &isEM_nofudge_12_ld, &b_isEM_nofudge_12_ld);
   fChain->SetBranchAddress("isEM_13_ld", &isEM_13_ld, &b_isEM_13_ld);
   fChain->SetBranchAddress("isEM_13_subld", &isEM_13_subld, &b_isEM_13_subld);
   fChain->SetBranchAddress("isEM_nofudge_13_ld", &isEM_nofudge_13_ld, &b_isEM_nofudge_13_ld);
   fChain->SetBranchAddress("isEM_14_ld", &isEM_14_ld, &b_isEM_14_ld);
   fChain->SetBranchAddress("isEM_14_subld", &isEM_14_subld, &b_isEM_14_subld);
   fChain->SetBranchAddress("isEM_nofudge_14_ld", &isEM_nofudge_14_ld, &b_isEM_nofudge_14_ld);
   fChain->SetBranchAddress("isEM_15_ld", &isEM_15_ld, &b_isEM_15_ld);
   fChain->SetBranchAddress("isEM_15_subld", &isEM_15_subld, &b_isEM_15_subld);
   fChain->SetBranchAddress("isEM_nofudge_15_ld", &isEM_nofudge_15_ld, &b_isEM_nofudge_15_ld);
   fChain->SetBranchAddress("isEM_16_ld", &isEM_16_ld, &b_isEM_16_ld);
   fChain->SetBranchAddress("isEM_16_subld", &isEM_16_subld, &b_isEM_16_subld);
   fChain->SetBranchAddress("isEM_nofudge_16_ld", &isEM_nofudge_16_ld, &b_isEM_nofudge_16_ld);
   fChain->SetBranchAddress("isEM_17_ld", &isEM_17_ld, &b_isEM_17_ld);
   fChain->SetBranchAddress("isEM_17_subld", &isEM_17_subld, &b_isEM_17_subld);
   fChain->SetBranchAddress("isEM_nofudge_17_ld", &isEM_nofudge_17_ld, &b_isEM_nofudge_17_ld);
   fChain->SetBranchAddress("isEM_18_ld", &isEM_18_ld, &b_isEM_18_ld);
   fChain->SetBranchAddress("isEM_18_subld", &isEM_18_subld, &b_isEM_18_subld);
   fChain->SetBranchAddress("isEM_nofudge_18_ld", &isEM_nofudge_18_ld, &b_isEM_nofudge_18_ld);
   fChain->SetBranchAddress("isEM_19_ld", &isEM_19_ld, &b_isEM_19_ld);
   fChain->SetBranchAddress("isEM_19_subld", &isEM_19_subld, &b_isEM_19_subld);
   fChain->SetBranchAddress("isEM_nofudge_19_ld", &isEM_nofudge_19_ld, &b_isEM_nofudge_19_ld);
   fChain->SetBranchAddress("isEM_20_ld", &isEM_20_ld, &b_isEM_20_ld);
   fChain->SetBranchAddress("isEM_20_subld", &isEM_20_subld, &b_isEM_20_subld);
   fChain->SetBranchAddress("isEM_nofudge_20_ld", &isEM_nofudge_20_ld, &b_isEM_nofudge_20_ld);
   fChain->SetBranchAddress("isEM_21_ld", &isEM_21_ld, &b_isEM_21_ld);
   fChain->SetBranchAddress("isEM_21_subld", &isEM_21_subld, &b_isEM_21_subld);
   fChain->SetBranchAddress("isEM_nofudge_21_ld", &isEM_nofudge_21_ld, &b_isEM_nofudge_21_ld);
   fChain->SetBranchAddress("pass_2g50_loose_trigger", &pass_2g50_loose_trigger, &b_pass_2g50_loose_trigger);
   fChain->SetBranchAddress("pass_g35_g25_loose_trigger", &pass_g35_g25_loose_trigger, &b_pass_g35_g25_loose_trigger);
   fChain->SetBranchAddress("averageIntPerXing", &averageIntPerXing, &b_averageIntPerXing);
   fChain->SetBranchAddress("ED_central", &ED_central, &b_ED_central);
   fChain->SetBranchAddress("ED_forward", &ED_forward, &b_ED_forward);
   fChain->SetBranchAddress("run_number", &run_number, &b_run_number);
   fChain->SetBranchAddress("event_number", &event_number, &b_event_number);
   fChain->SetBranchAddress("lumiblock_number", &lumiblock_number, &b_lumiblock_number);
   fChain->SetBranchAddress("time_stamp", &time_stamp, &b_time_stamp);
   fChain->SetBranchAddress("bcid", &bcid, &b_bcid);
   fChain->SetBranchAddress("mc_channel_number", &mc_channel_number, &b_mc_channel_number);
   fChain->SetBranchAddress("mc_event_number", &mc_event_number, &b_mc_event_number);
   fChain->SetBranchAddress("nPV", &nPV, &b_nPV);
   fChain->SetBranchAddress("xs", &xs, &b_xs);
   fChain->SetBranchAddress("xs_ami", &xs_ami, &b_xs_ami);
   fChain->SetBranchAddress("filter_eff", &filter_eff, &b_filter_eff);
   fChain->SetBranchAddress("filter_eff_ami", &filter_eff_ami, &b_filter_eff_ami);
   fChain->SetBranchAddress("one_photon", &one_photon, &b_one_photon);
   fChain->SetBranchAddress("two_photons", &two_photons, &b_two_photons);
   fChain->SetBranchAddress("pileup_weight", &pileup_weight, &b_pileup_weight);
   fChain->SetBranchAddress("vertex_weight", &vertex_weight, &b_vertex_weight);
   fChain->SetBranchAddress("MC_weight", &MC_weight, &b_MC_weight);
   fChain->SetBranchAddress("xs_weight", &xs_weight, &b_xs_weight);
   fChain->SetBranchAddress("event_weight", &event_weight, &b_event_weight);
   fChain->SetBranchAddress("prel_weight", &prel_weight, &b_prel_weight);
   fChain->SetBranchAddress("total_weight", &total_weight, &b_total_weight);
   fChain->SetBranchAddress("total_events", &total_events, &b_total_events);
   fChain->SetBranchAddress("non_derived_total_events", &non_derived_total_events, &b_non_derived_total_events);
   fChain->SetBranchAddress("weight_sum_before", &weight_sum_before, &b_weight_sum_before);
   fChain->SetBranchAddress("SF_leading", &SF_leading, &b_SF_leading);
   fChain->SetBranchAddress("SF_unc_leading", &SF_unc_leading, &b_SF_unc_leading);
   fChain->SetBranchAddress("SF_subleading", &SF_subleading, &b_SF_subleading);
   fChain->SetBranchAddress("SF_unc_subleading", &SF_unc_subleading, &b_SF_unc_subleading);
   fChain->SetBranchAddress("SF_diphoton", &SF_diphoton, &b_SF_diphoton);
   fChain->SetBranchAddress("SF_1UP_diphoton", &SF_1UP_diphoton, &b_SF_1UP_diphoton);
   fChain->SetBranchAddress("SF_1DOWN_diphoton", &SF_1DOWN_diphoton, &b_SF_1DOWN_diphoton);
   fChain->SetBranchAddress("sumpt2_tracks", &sumpt2_tracks, &b_sumpt2_tracks);
   fChain->SetBranchAddress("mass_gev", &mass_gev, &b_mass_gev);
   fChain->SetBranchAddress("mass_MVA", &mass_MVA, &b_mass_MVA);
   fChain->SetBranchAddress("mgg", &mgg, &b_mgg);
   fChain->SetBranchAddress("mass_raw", &mass_raw, &b_mass_raw);
   fChain->SetBranchAddress("mass_egamma", &mass_egamma, &b_mass_egamma);
   fChain->SetBranchAddress("mass", &mass, &b_mass);
   fChain->SetBranchAddress("costhetastar", &costhetastar, &b_costhetastar);
   fChain->SetBranchAddress("deltaphi", &deltaphi, &b_deltaphi);
   fChain->SetBranchAddress("LV_leading", &LV_leading, &b_LV_leading);
   fChain->SetBranchAddress("LV_subleading", &LV_subleading, &b_LV_subleading);
   fChain->SetBranchAddress("LV_diphoton", &LV_diphoton, &b_LV_diphoton);
   fChain->SetBranchAddress("LV_egamma", &LV_egamma, &b_LV_egamma);
   fChain->SetBranchAddress("pt_subleading", &pt_subleading, &b_pt_subleading);
   fChain->SetBranchAddress("pt_leading", &pt_leading, &b_pt_leading);
   fChain->SetBranchAddress("phi_subleading", &phi_subleading, &b_phi_subleading);
   fChain->SetBranchAddress("phi_leading", &phi_leading, &b_phi_leading);
   fChain->SetBranchAddress("eta_subleading", &eta_subleading, &b_eta_subleading);
   fChain->SetBranchAddress("eta_leading", &eta_leading, &b_eta_leading);
   fChain->SetBranchAddress("author_leading", &author_leading, &b_author_leading);
   fChain->SetBranchAddress("author_subleading", &author_subleading, &b_author_subleading);
   fChain->SetBranchAddress("raw_energy_leading", &raw_energy_leading, &b_raw_energy_leading);
   fChain->SetBranchAddress("raw_energy_subleading", &raw_energy_subleading, &b_raw_energy_subleading);
   fChain->SetBranchAddress("raw_et_leading", &raw_et_leading, &b_raw_et_leading);
   fChain->SetBranchAddress("raw_et_subleading", &raw_et_subleading, &b_raw_et_subleading);
   fChain->SetBranchAddress("e_on_eraw_leading", &e_on_eraw_leading, &b_e_on_eraw_leading);
   fChain->SetBranchAddress("e_on_eraw_subleading", &e_on_eraw_subleading, &b_e_on_eraw_subleading);
   fChain->SetBranchAddress("deltaR", &deltaR, &b_deltaR);
   fChain->SetBranchAddress("max_cell_gain_leading", &max_cell_gain_leading, &b_max_cell_gain_leading);
   fChain->SetBranchAddress("max_cell_time_leading", &max_cell_time_leading, &b_max_cell_time_leading);
   fChain->SetBranchAddress("max_cell_e_leading", &max_cell_e_leading, &b_max_cell_e_leading);
   fChain->SetBranchAddress("max_cell_gain_subleading", &max_cell_gain_subleading, &b_max_cell_gain_subleading);
   fChain->SetBranchAddress("max_cell_time_subleading", &max_cell_time_subleading, &b_max_cell_time_subleading);
   fChain->SetBranchAddress("max_cell_e_subleading", &max_cell_e_subleading, &b_max_cell_e_subleading);
   fChain->SetBranchAddress("Rconv_leading", &Rconv_leading, &b_Rconv_leading);
   fChain->SetBranchAddress("Rconv_subleading", &Rconv_subleading, &b_Rconv_subleading);
   fChain->SetBranchAddress("E0_leading", &E0_leading, &b_E0_leading);
   fChain->SetBranchAddress("E1_leading", &E1_leading, &b_E1_leading);
   fChain->SetBranchAddress("E2_leading", &E2_leading, &b_E2_leading);
   fChain->SetBranchAddress("E3_leading", &E3_leading, &b_E3_leading);
   fChain->SetBranchAddress("E0_subleading", &E0_subleading, &b_E0_subleading);
   fChain->SetBranchAddress("E1_subleading", &E1_subleading, &b_E1_subleading);
   fChain->SetBranchAddress("E2_subleading", &E2_subleading, &b_E2_subleading);
   fChain->SetBranchAddress("E3_subleading", &E3_subleading, &b_E3_subleading);
   fChain->SetBranchAddress("Zconv_leading", &Zconv_leading, &b_Zconv_leading);
   fChain->SetBranchAddress("Zconv_subleading", &Zconv_subleading, &b_Zconv_subleading);
   fChain->SetBranchAddress("PVz", &PVz, &b_PVz);
   fChain->SetBranchAddress("topoetcone40_leading", &topoetcone40_leading, &b_topoetcone40_leading);
   fChain->SetBranchAddress("topoetcone40_DDcorrected_leading", &topoetcone40_DDcorrected_leading, &b_topoetcone40_DDcorrected_leading);
   fChain->SetBranchAddress("topoetcone40_rel17_leading", &topoetcone40_rel17_leading, &b_topoetcone40_rel17_leading);
   fChain->SetBranchAddress("topoetcone40_electron_leading", &topoetcone40_electron_leading, &b_topoetcone40_electron_leading);
   fChain->SetBranchAddress("topoetcone40_trouble_electron_leading", &topoetcone40_trouble_electron_leading, &b_topoetcone40_trouble_electron_leading);
   fChain->SetBranchAddress("topoetcone40_rel17_electron_leading", &topoetcone40_rel17_electron_leading, &b_topoetcone40_rel17_electron_leading);
   fChain->SetBranchAddress("author_electron_leading", &author_electron_leading, &b_author_electron_leading);
   fChain->SetBranchAddress("topoetcone40_subleading", &topoetcone40_subleading, &b_topoetcone40_subleading);
   fChain->SetBranchAddress("topoetcone40_DDcorrected_subleading", &topoetcone40_DDcorrected_subleading, &b_topoetcone40_DDcorrected_subleading);
   fChain->SetBranchAddress("topoetcone20_leading", &topoetcone20_leading, &b_topoetcone20_leading);
   fChain->SetBranchAddress("topoetcone20_subleading", &topoetcone20_subleading, &b_topoetcone20_subleading);
   fChain->SetBranchAddress("truth_etcone40_leading", &truth_etcone40_leading, &b_truth_etcone40_leading);
   fChain->SetBranchAddress("truth_etcone40_subleading", &truth_etcone40_subleading, &b_truth_etcone40_subleading);
   fChain->SetBranchAddress("truth_etcone20_leading", &truth_etcone20_leading, &b_truth_etcone20_leading);
   fChain->SetBranchAddress("truth_etcone20_subleading", &truth_etcone20_subleading, &b_truth_etcone20_subleading);
   fChain->SetBranchAddress("truth_local_etcone40_leading", &truth_local_etcone40_leading, &b_truth_local_etcone40_leading);
   fChain->SetBranchAddress("truth_local_etcone40_subleading", &truth_local_etcone40_subleading, &b_truth_local_etcone40_subleading);
   fChain->SetBranchAddress("truth_local_etcone20_leading", &truth_local_etcone20_leading, &b_truth_local_etcone20_leading);
   fChain->SetBranchAddress("truth_local_etcone20_subleading", &truth_local_etcone20_subleading, &b_truth_local_etcone20_subleading);
   fChain->SetBranchAddress("truth_etcone40_PUcorr_leading", &truth_etcone40_PUcorr_leading, &b_truth_etcone40_PUcorr_leading);
   fChain->SetBranchAddress("truth_etcone40_PUcorr_subleading", &truth_etcone40_PUcorr_subleading, &b_truth_etcone40_PUcorr_subleading);
   fChain->SetBranchAddress("truth_etcone20_PUcorr_leading", &truth_etcone20_PUcorr_leading, &b_truth_etcone20_PUcorr_leading);
   fChain->SetBranchAddress("truth_etcone20_PUcorr_subleading", &truth_etcone20_PUcorr_subleading, &b_truth_etcone20_PUcorr_subleading);
   fChain->SetBranchAddress("truth_ptcone40_leading", &truth_ptcone40_leading, &b_truth_ptcone40_leading);
   fChain->SetBranchAddress("truth_ptcone40_subleading", &truth_ptcone40_subleading, &b_truth_ptcone40_subleading);
   fChain->SetBranchAddress("truth_ptcone20_leading", &truth_ptcone20_leading, &b_truth_ptcone20_leading);
   fChain->SetBranchAddress("truth_ptcone20_subleading", &truth_ptcone20_subleading, &b_truth_ptcone20_subleading);
   fChain->SetBranchAddress("truth_ptcone40_PUcorr_leading", &truth_ptcone40_PUcorr_leading, &b_truth_ptcone40_PUcorr_leading);
   fChain->SetBranchAddress("truth_ptcone40_PUcorr_subleading", &truth_ptcone40_PUcorr_subleading, &b_truth_ptcone40_PUcorr_subleading);
   fChain->SetBranchAddress("truth_ptcone20_PUcorr_leading", &truth_ptcone20_PUcorr_leading, &b_truth_ptcone20_PUcorr_leading);
   fChain->SetBranchAddress("truth_ptcone20_PUcorr_subleading", &truth_ptcone20_PUcorr_subleading, &b_truth_ptcone20_PUcorr_subleading);
   fChain->SetBranchAddress("truth_rho_central", &truth_rho_central, &b_truth_rho_central);
   fChain->SetBranchAddress("truth_rho_forward", &truth_rho_forward, &b_truth_rho_forward);
   fChain->SetBranchAddress("tight_leading", &tight_leading, &b_tight_leading);
   fChain->SetBranchAddress("my_tight_leading", &my_tight_leading, &b_my_tight_leading);
   fChain->SetBranchAddress("loose_leading", &loose_leading, &b_loose_leading);
   fChain->SetBranchAddress("loose_prime_leading", &loose_prime_leading, &b_loose_prime_leading);
   fChain->SetBranchAddress("tight_subleading", &tight_subleading, &b_tight_subleading);
   fChain->SetBranchAddress("loose_subleading", &loose_subleading, &b_loose_subleading);
   fChain->SetBranchAddress("loose_prime_subleading", &loose_prime_subleading, &b_loose_prime_subleading);
   fChain->SetBranchAddress("bg_truth_match_leading", &bg_truth_match_leading, &b_bg_truth_match_leading);
   fChain->SetBranchAddress("bg_truth_match_origin_leading", &bg_truth_match_origin_leading, &b_bg_truth_match_origin_leading);
   fChain->SetBranchAddress("pdgID_leading", &pdgID_leading, &b_pdgID_leading);
   fChain->SetBranchAddress("parent_pdgID_leading", &parent_pdgID_leading, &b_parent_pdgID_leading);
   fChain->SetBranchAddress("type_leading", &type_leading, &b_type_leading);
   fChain->SetBranchAddress("origin_leading", &origin_leading, &b_origin_leading);
   fChain->SetBranchAddress("truth_match_leading", &truth_match_leading, &b_truth_match_leading);
   fChain->SetBranchAddress("pdgID_subleading", &pdgID_subleading, &b_pdgID_subleading);
   fChain->SetBranchAddress("parent_pdgID_subleading", &parent_pdgID_subleading, &b_parent_pdgID_subleading);
   fChain->SetBranchAddress("type_subleading", &type_subleading, &b_type_subleading);
   fChain->SetBranchAddress("origin_subleading", &origin_subleading, &b_origin_subleading);
   fChain->SetBranchAddress("truth_match_subleading", &truth_match_subleading, &b_truth_match_subleading);
   fChain->SetBranchAddress("conv_leading", &conv_leading, &b_conv_leading);
   fChain->SetBranchAddress("conv_subleading", &conv_subleading, &b_conv_subleading);
   fChain->SetBranchAddress("isEM_leading", &isEM_leading, &b_isEM_leading);
   fChain->SetBranchAddress("isEM_subleading", &isEM_subleading, &b_isEM_subleading);
   fChain->SetBranchAddress("isEM_nofudge_leading", &isEM_nofudge_leading, &b_isEM_nofudge_leading);
   fChain->SetBranchAddress("isEM_nofudge_subleading", &isEM_nofudge_subleading, &b_isEM_nofudge_subleading);
   fChain->SetBranchAddress("photonOQ_leading", &photonOQ_leading, &b_photonOQ_leading);
   fChain->SetBranchAddress("photonOQ_subleading", &photonOQ_subleading, &b_photonOQ_subleading);
   fChain->SetBranchAddress("Z_pointing_leading", &Z_pointing_leading, &b_Z_pointing_leading);
   fChain->SetBranchAddress("Z_pointing_subleading", &Z_pointing_subleading, &b_Z_pointing_subleading);
   fChain->SetBranchAddress("Rhad_leading", &Rhad_leading, &b_Rhad_leading);
   fChain->SetBranchAddress("e277_leading", &e277_leading, &b_e277_leading);
   fChain->SetBranchAddress("Reta_leading", &Reta_leading, &b_Reta_leading);
   fChain->SetBranchAddress("Rphi_leading", &Rphi_leading, &b_Rphi_leading);
   fChain->SetBranchAddress("weta2_leading", &weta2_leading, &b_weta2_leading);
   fChain->SetBranchAddress("f1_leading", &f1_leading, &b_f1_leading);
   fChain->SetBranchAddress("DeltaE_leading", &DeltaE_leading, &b_DeltaE_leading);
   fChain->SetBranchAddress("wtots1_leading", &wtots1_leading, &b_wtots1_leading);
   fChain->SetBranchAddress("fracs1_leading", &fracs1_leading, &b_fracs1_leading);
   fChain->SetBranchAddress("weta1_leading", &weta1_leading, &b_weta1_leading);
   fChain->SetBranchAddress("Eratio_leading", &Eratio_leading, &b_Eratio_leading);
   fChain->SetBranchAddress("Rhad_subleading", &Rhad_subleading, &b_Rhad_subleading);
   fChain->SetBranchAddress("e277_subleading", &e277_subleading, &b_e277_subleading);
   fChain->SetBranchAddress("Reta_subleading", &Reta_subleading, &b_Reta_subleading);
   fChain->SetBranchAddress("Rphi_subleading", &Rphi_subleading, &b_Rphi_subleading);
   fChain->SetBranchAddress("weta2_subleading", &weta2_subleading, &b_weta2_subleading);
   fChain->SetBranchAddress("f1_subleading", &f1_subleading, &b_f1_subleading);
   fChain->SetBranchAddress("DeltaE_subleading", &DeltaE_subleading, &b_DeltaE_subleading);
   fChain->SetBranchAddress("wtots1_subleading", &wtots1_subleading, &b_wtots1_subleading);
   fChain->SetBranchAddress("fracs1_subleading", &fracs1_subleading, &b_fracs1_subleading);
   fChain->SetBranchAddress("weta1_subleading", &weta1_subleading, &b_weta1_subleading);
   fChain->SetBranchAddress("Eratio_subleading", &Eratio_subleading, &b_Eratio_subleading);
   fChain->SetBranchAddress("Rhad_leading_nofudge", &Rhad_leading_nofudge, &b_Rhad_leading_nofudge);
   fChain->SetBranchAddress("e277_leading_nofudge", &e277_leading_nofudge, &b_e277_leading_nofudge);
   fChain->SetBranchAddress("Reta_leading_nofudge", &Reta_leading_nofudge, &b_Reta_leading_nofudge);
   fChain->SetBranchAddress("Rphi_leading_nofudge", &Rphi_leading_nofudge, &b_Rphi_leading_nofudge);
   fChain->SetBranchAddress("weta2_leading_nofudge", &weta2_leading_nofudge, &b_weta2_leading_nofudge);
   fChain->SetBranchAddress("f1_leading_nofudge", &f1_leading_nofudge, &b_f1_leading_nofudge);
   fChain->SetBranchAddress("DeltaE_leading_nofudge", &DeltaE_leading_nofudge, &b_DeltaE_leading_nofudge);
   fChain->SetBranchAddress("wtots1_leading_nofudge", &wtots1_leading_nofudge, &b_wtots1_leading_nofudge);
   fChain->SetBranchAddress("fracs1_leading_nofudge", &fracs1_leading_nofudge, &b_fracs1_leading_nofudge);
   fChain->SetBranchAddress("weta1_leading_nofudge", &weta1_leading_nofudge, &b_weta1_leading_nofudge);
   fChain->SetBranchAddress("Eratio_leading_nofudge", &Eratio_leading_nofudge, &b_Eratio_leading_nofudge);
   fChain->SetBranchAddress("Rhad_subleading_nofudge", &Rhad_subleading_nofudge, &b_Rhad_subleading_nofudge);
   fChain->SetBranchAddress("e277_subleading_nofudge", &e277_subleading_nofudge, &b_e277_subleading_nofudge);
   fChain->SetBranchAddress("Reta_subleading_nofudge", &Reta_subleading_nofudge, &b_Reta_subleading_nofudge);
   fChain->SetBranchAddress("Rphi_subleading_nofudge", &Rphi_subleading_nofudge, &b_Rphi_subleading_nofudge);
   fChain->SetBranchAddress("weta2_subleading_nofudge", &weta2_subleading_nofudge, &b_weta2_subleading_nofudge);
   fChain->SetBranchAddress("f1_subleading_nofudge", &f1_subleading_nofudge, &b_f1_subleading_nofudge);
   fChain->SetBranchAddress("DeltaE_subleading_nofudge", &DeltaE_subleading_nofudge, &b_DeltaE_subleading_nofudge);
   fChain->SetBranchAddress("wtots1_subleading_nofudge", &wtots1_subleading_nofudge, &b_wtots1_subleading_nofudge);
   fChain->SetBranchAddress("fracs1_subleading_nofudge", &fracs1_subleading_nofudge, &b_fracs1_subleading_nofudge);
   fChain->SetBranchAddress("weta1_subleading_nofudge", &weta1_subleading_nofudge, &b_weta1_subleading_nofudge);
   fChain->SetBranchAddress("Eratio_subleading_nofudge", &Eratio_subleading_nofudge, &b_Eratio_subleading_nofudge);
   fChain->SetBranchAddress("E1_E2_leading", &E1_E2_leading, &b_E1_E2_leading);
   fChain->SetBranchAddress("etaS2_leading", &etaS2_leading, &b_etaS2_leading);
   fChain->SetBranchAddress("etaS2_subleading", &etaS2_subleading, &b_etaS2_subleading);
   fChain->SetBranchAddress("ptvarcone20_leading", &ptvarcone20_leading, &b_ptvarcone20_leading);
   fChain->SetBranchAddress("ptcone20_leading", &ptcone20_leading, &b_ptcone20_leading);
   fChain->SetBranchAddress("ptvarcone40_leading", &ptvarcone40_leading, &b_ptvarcone40_leading);
   fChain->SetBranchAddress("ptcone40_leading", &ptcone40_leading, &b_ptcone40_leading);
   fChain->SetBranchAddress("topoetcone20_Pt_leading", &topoetcone20_Pt_leading, &b_topoetcone20_Pt_leading);
   fChain->SetBranchAddress("ptvarcone20_Pt_leading", &ptvarcone20_Pt_leading, &b_ptvarcone20_Pt_leading);
   fChain->SetBranchAddress("ptcone20_subleading", &ptcone20_subleading, &b_ptcone20_subleading);
   fChain->SetBranchAddress("ptcone40_subleading", &ptcone40_subleading, &b_ptcone40_subleading);
   fChain->SetBranchAddress("DD_corr_40_leading", &DD_corr_40_leading, &b_DD_corr_40_leading);
   fChain->SetBranchAddress("DD_corr_40_subleading", &DD_corr_40_subleading, &b_DD_corr_40_subleading);
   fChain->SetBranchAddress("DD_corr_20_leading", &DD_corr_20_leading, &b_DD_corr_20_leading);
   fChain->SetBranchAddress("DD_corr_20_subleading", &DD_corr_20_subleading, &b_DD_corr_20_subleading);
   fChain->SetBranchAddress("topoetcone40", &topoetcone40, &b_topoetcone40);
   fChain->SetBranchAddress("topoetcone30", &topoetcone30, &b_topoetcone30);
   fChain->SetBranchAddress("topoetcone20", &topoetcone20, &b_topoetcone20);
   fChain->SetBranchAddress("ptcone40", &ptcone40, &b_ptcone40);
   fChain->SetBranchAddress("ptcone30", &ptcone30, &b_ptcone30);
   fChain->SetBranchAddress("ptcone20", &ptcone20, &b_ptcone20);
   fChain->SetBranchAddress("ptvarcone40", &ptvarcone40, &b_ptvarcone40);
   fChain->SetBranchAddress("ptvarcone30", &ptvarcone30, &b_ptvarcone30);
   fChain->SetBranchAddress("ptvarcone20", &ptvarcone20, &b_ptvarcone20);
   fChain->SetBranchAddress("FixedCutTightCaloOnly_ld", &FixedCutTightCaloOnly_ld, &b_FixedCutTightCaloOnly_ld);
   fChain->SetBranchAddress("FixedCutTight_ld", &FixedCutTight_ld, &b_FixedCutTight_ld);
   fChain->SetBranchAddress("FixedCutLoose_ld", &FixedCutLoose_ld, &b_FixedCutLoose_ld);
   fChain->SetBranchAddress("FixedCutTightCaloOnly_subld", &FixedCutTightCaloOnly_subld, &b_FixedCutTightCaloOnly_subld);
   fChain->SetBranchAddress("FixedCutTight_subld", &FixedCutTight_subld, &b_FixedCutTight_subld);
   fChain->SetBranchAddress("FixedCutLoose_subld", &FixedCutLoose_subld, &b_FixedCutLoose_subld);
   fChain->SetBranchAddress("pass_truth_match", &pass_truth_match, &b_pass_truth_match);
   fChain->SetBranchAddress("parent_pdgID_truth_ld", &parent_pdgID_truth_ld, &b_parent_pdgID_truth_ld);
   fChain->SetBranchAddress("parent_pdgID_truth_subld", &parent_pdgID_truth_subld, &b_parent_pdgID_truth_subld);
   fChain->SetBranchAddress("origin_truth_ld", &origin_truth_ld, &b_origin_truth_ld);
   fChain->SetBranchAddress("origin_truth_subld", &origin_truth_subld, &b_origin_truth_subld);
   fChain->SetBranchAddress("ph_pt", &ph_pt, &b_ph_pt);
   fChain->SetBranchAddress("ph_eta", &ph_eta, &b_ph_eta);
   fChain->SetBranchAddress("ph_etas2", &ph_etas2, &b_ph_etas2);
   fChain->SetBranchAddress("ph_phi", &ph_phi, &b_ph_phi);
   fChain->SetBranchAddress("ph_cl_phi", &ph_cl_phi, &b_ph_cl_phi);
   fChain->SetBranchAddress("ph_parent_pdgID", &ph_parent_pdgID, &b_ph_parent_pdgID);
   fChain->SetBranchAddress("ph_tight", &ph_tight, &b_ph_tight);
   fChain->SetBranchAddress("ph_matched", &ph_matched, &b_ph_matched);
   fChain->SetBranchAddress("two_truth_photons", &two_truth_photons, &b_two_truth_photons);
   fChain->SetBranchAddress("pass_eta_truth_analysis", &pass_eta_truth_analysis, &b_pass_eta_truth_analysis);
   fChain->SetBranchAddress("truth_leading_LV", &truth_leading_LV, &b_truth_leading_LV);
   fChain->SetBranchAddress("truth_subleading_LV", &truth_subleading_LV, &b_truth_subleading_LV);
   fChain->SetBranchAddress("truth_diphoton_LV", &truth_diphoton_LV, &b_truth_diphoton_LV);
   fChain->SetBranchAddress("truth_leading_matched_leading_ph", &truth_leading_matched_leading_ph, &b_truth_leading_matched_leading_ph);
   fChain->SetBranchAddress("truth_subleading_matched_subleading_ph", &truth_subleading_matched_subleading_ph, &b_truth_subleading_matched_subleading_ph);
   fChain->SetBranchAddress("mass_EG_RESOLUTION_ALL__1down", &mass_EG_RESOLUTION_ALL__1down, &b_mass_EG_RESOLUTION_ALL__1down);
   fChain->SetBranchAddress("mass_EG_RESOLUTION_ALL__1up", &mass_EG_RESOLUTION_ALL__1up, &b_mass_EG_RESOLUTION_ALL__1up);
   fChain->SetBranchAddress("mass_EG_SCALE_ALL__1down", &mass_EG_SCALE_ALL__1down, &b_mass_EG_SCALE_ALL__1down);
   fChain->SetBranchAddress("mass_EG_SCALE_ALL__1up", &mass_EG_SCALE_ALL__1up, &b_mass_EG_SCALE_ALL__1up);
   fChain->SetBranchAddress("mass_PH_EFF_ID_Uncertainty__1down", &mass_PH_EFF_ID_Uncertainty__1down, &b_mass_PH_EFF_ID_Uncertainty__1down);
   fChain->SetBranchAddress("mass_PH_EFF_ID_Uncertainty__1up", &mass_PH_EFF_ID_Uncertainty__1up, &b_mass_PH_EFF_ID_Uncertainty__1up);
   fChain->SetBranchAddress("mass_PH_EFF_TRKISO_Uncertainty__1down", &mass_PH_EFF_TRKISO_Uncertainty__1down, &b_mass_PH_EFF_TRKISO_Uncertainty__1down);
   fChain->SetBranchAddress("mass_PH_EFF_TRKISO_Uncertainty__1up", &mass_PH_EFF_TRKISO_Uncertainty__1up, &b_mass_PH_EFF_TRKISO_Uncertainty__1up);
   fChain->SetBranchAddress("mass_PH_Iso_DDonoff", &mass_PH_Iso_DDonoff, &b_mass_PH_Iso_DDonoff);
   fChain->SetBranchAddress("mass_PRW_DATASF__1down", &mass_PRW_DATASF__1down, &b_mass_PRW_DATASF__1down);
   fChain->SetBranchAddress("mass_PRW_DATASF__1up", &mass_PRW_DATASF__1up, &b_mass_PRW_DATASF__1up);
   fChain->SetBranchAddress("event_weight_EG_RESOLUTION_ALL__1down", &event_weight_EG_RESOLUTION_ALL__1down, &b_event_weight_EG_RESOLUTION_ALL__1down);
   fChain->SetBranchAddress("event_weight_EG_RESOLUTION_ALL__1up", &event_weight_EG_RESOLUTION_ALL__1up, &b_event_weight_EG_RESOLUTION_ALL__1up);
   fChain->SetBranchAddress("event_weight_EG_SCALE_ALL__1down", &event_weight_EG_SCALE_ALL__1down, &b_event_weight_EG_SCALE_ALL__1down);
   fChain->SetBranchAddress("event_weight_EG_SCALE_ALL__1up", &event_weight_EG_SCALE_ALL__1up, &b_event_weight_EG_SCALE_ALL__1up);
   fChain->SetBranchAddress("event_weight_PH_EFF_ID_Uncertainty__1down", &event_weight_PH_EFF_ID_Uncertainty__1down, &b_event_weight_PH_EFF_ID_Uncertainty__1down);
   fChain->SetBranchAddress("event_weight_PH_EFF_ID_Uncertainty__1up", &event_weight_PH_EFF_ID_Uncertainty__1up, &b_event_weight_PH_EFF_ID_Uncertainty__1up);
   fChain->SetBranchAddress("event_weight_PH_EFF_TRKISO_Uncertainty__1down", &event_weight_PH_EFF_TRKISO_Uncertainty__1down, &b_event_weight_PH_EFF_TRKISO_Uncertainty__1down);
   fChain->SetBranchAddress("event_weight_PH_EFF_TRKISO_Uncertainty__1up", &event_weight_PH_EFF_TRKISO_Uncertainty__1up, &b_event_weight_PH_EFF_TRKISO_Uncertainty__1up);
   fChain->SetBranchAddress("event_weight_PH_Iso_DDonoff", &event_weight_PH_Iso_DDonoff, &b_event_weight_PH_Iso_DDonoff);
   fChain->SetBranchAddress("event_weight_PRW_DATASF__1down", &event_weight_PRW_DATASF__1down, &b_event_weight_PRW_DATASF__1down);
   fChain->SetBranchAddress("event_weight_PRW_DATASF__1up", &event_weight_PRW_DATASF__1up, &b_event_weight_PRW_DATASF__1up);
   fChain->SetBranchAddress("accepted_EG_RESOLUTION_ALL__1down", &accepted_EG_RESOLUTION_ALL__1down, &b_accepted_EG_RESOLUTION_ALL__1down);
   fChain->SetBranchAddress("accepted_EG_RESOLUTION_ALL__1up", &accepted_EG_RESOLUTION_ALL__1up, &b_accepted_EG_RESOLUTION_ALL__1up);
   fChain->SetBranchAddress("accepted_EG_SCALE_ALL__1down", &accepted_EG_SCALE_ALL__1down, &b_accepted_EG_SCALE_ALL__1down);
   fChain->SetBranchAddress("accepted_EG_SCALE_ALL__1up", &accepted_EG_SCALE_ALL__1up, &b_accepted_EG_SCALE_ALL__1up);
   fChain->SetBranchAddress("accepted_PH_EFF_ID_Uncertainty__1down", &accepted_PH_EFF_ID_Uncertainty__1down, &b_accepted_PH_EFF_ID_Uncertainty__1down);
   fChain->SetBranchAddress("accepted_PH_EFF_ID_Uncertainty__1up", &accepted_PH_EFF_ID_Uncertainty__1up, &b_accepted_PH_EFF_ID_Uncertainty__1up);
   fChain->SetBranchAddress("accepted_PH_EFF_TRKISO_Uncertainty__1down", &accepted_PH_EFF_TRKISO_Uncertainty__1down, &b_accepted_PH_EFF_TRKISO_Uncertainty__1down);
   fChain->SetBranchAddress("accepted_PH_EFF_TRKISO_Uncertainty__1up", &accepted_PH_EFF_TRKISO_Uncertainty__1up, &b_accepted_PH_EFF_TRKISO_Uncertainty__1up);
   fChain->SetBranchAddress("accepted_PH_Iso_DDonoff", &accepted_PH_Iso_DDonoff, &b_accepted_PH_Iso_DDonoff);
   fChain->SetBranchAddress("accepted_PRW_DATASF__1down", &accepted_PRW_DATASF__1down, &b_accepted_PRW_DATASF__1down);
   fChain->SetBranchAddress("accepted_PRW_DATASF__1up", &accepted_PRW_DATASF__1up, &b_accepted_PRW_DATASF__1up);
   fChain->SetBranchAddress("leading_LV_EG_RESOLUTION_ALL__1down", &leading_LV_EG_RESOLUTION_ALL__1down, &b_leading_LV_EG_RESOLUTION_ALL__1down);
   fChain->SetBranchAddress("leading_LV_EG_RESOLUTION_ALL__1up", &leading_LV_EG_RESOLUTION_ALL__1up, &b_leading_LV_EG_RESOLUTION_ALL__1up);
   fChain->SetBranchAddress("leading_LV_EG_SCALE_ALL__1down", &leading_LV_EG_SCALE_ALL__1down, &b_leading_LV_EG_SCALE_ALL__1down);
   fChain->SetBranchAddress("leading_LV_EG_SCALE_ALL__1up", &leading_LV_EG_SCALE_ALL__1up, &b_leading_LV_EG_SCALE_ALL__1up);
   fChain->SetBranchAddress("leading_LV_PH_EFF_ID_Uncertainty__1down", &leading_LV_PH_EFF_ID_Uncertainty__1down, &b_leading_LV_PH_EFF_ID_Uncertainty__1down);
   fChain->SetBranchAddress("leading_LV_PH_EFF_ID_Uncertainty__1up", &leading_LV_PH_EFF_ID_Uncertainty__1up, &b_leading_LV_PH_EFF_ID_Uncertainty__1up);
   fChain->SetBranchAddress("leading_LV_PH_EFF_TRKISO_Uncertainty__1down", &leading_LV_PH_EFF_TRKISO_Uncertainty__1down, &b_leading_LV_PH_EFF_TRKISO_Uncertainty__1down);
   fChain->SetBranchAddress("leading_LV_PH_EFF_TRKISO_Uncertainty__1up", &leading_LV_PH_EFF_TRKISO_Uncertainty__1up, &b_leading_LV_PH_EFF_TRKISO_Uncertainty__1up);
   fChain->SetBranchAddress("leading_LV_PH_Iso_DDonoff", &leading_LV_PH_Iso_DDonoff, &b_leading_LV_PH_Iso_DDonoff);
   fChain->SetBranchAddress("leading_LV_PRW_DATASF__1down", &leading_LV_PRW_DATASF__1down, &b_leading_LV_PRW_DATASF__1down);
   fChain->SetBranchAddress("leading_LV_PRW_DATASF__1up", &leading_LV_PRW_DATASF__1up, &b_leading_LV_PRW_DATASF__1up);
   fChain->SetBranchAddress("subleading_LV_EG_RESOLUTION_ALL__1down", &subleading_LV_EG_RESOLUTION_ALL__1down, &b_subleading_LV_EG_RESOLUTION_ALL__1down);
   fChain->SetBranchAddress("subleading_LV_EG_RESOLUTION_ALL__1up", &subleading_LV_EG_RESOLUTION_ALL__1up, &b_subleading_LV_EG_RESOLUTION_ALL__1up);
   fChain->SetBranchAddress("subleading_LV_EG_SCALE_ALL__1down", &subleading_LV_EG_SCALE_ALL__1down, &b_subleading_LV_EG_SCALE_ALL__1down);
   fChain->SetBranchAddress("subleading_LV_EG_SCALE_ALL__1up", &subleading_LV_EG_SCALE_ALL__1up, &b_subleading_LV_EG_SCALE_ALL__1up);
   fChain->SetBranchAddress("subleading_LV_PH_EFF_ID_Uncertainty__1down", &subleading_LV_PH_EFF_ID_Uncertainty__1down, &b_subleading_LV_PH_EFF_ID_Uncertainty__1down);
   fChain->SetBranchAddress("subleading_LV_PH_EFF_ID_Uncertainty__1up", &subleading_LV_PH_EFF_ID_Uncertainty__1up, &b_subleading_LV_PH_EFF_ID_Uncertainty__1up);
   fChain->SetBranchAddress("subleading_LV_PH_EFF_TRKISO_Uncertainty__1down", &subleading_LV_PH_EFF_TRKISO_Uncertainty__1down, &b_subleading_LV_PH_EFF_TRKISO_Uncertainty__1down);
   fChain->SetBranchAddress("subleading_LV_PH_EFF_TRKISO_Uncertainty__1up", &subleading_LV_PH_EFF_TRKISO_Uncertainty__1up, &b_subleading_LV_PH_EFF_TRKISO_Uncertainty__1up);
   fChain->SetBranchAddress("subleading_LV_PH_Iso_DDonoff", &subleading_LV_PH_Iso_DDonoff, &b_subleading_LV_PH_Iso_DDonoff);
   fChain->SetBranchAddress("subleading_LV_PRW_DATASF__1down", &subleading_LV_PRW_DATASF__1down, &b_subleading_LV_PRW_DATASF__1down);
   fChain->SetBranchAddress("subleading_LV_PRW_DATASF__1up", &subleading_LV_PRW_DATASF__1up, &b_subleading_LV_PRW_DATASF__1up);
   fChain->SetBranchAddress("diphoton_LV_EG_RESOLUTION_ALL__1down", &diphoton_LV_EG_RESOLUTION_ALL__1down, &b_diphoton_LV_EG_RESOLUTION_ALL__1down);
   fChain->SetBranchAddress("diphoton_LV_EG_RESOLUTION_ALL__1up", &diphoton_LV_EG_RESOLUTION_ALL__1up, &b_diphoton_LV_EG_RESOLUTION_ALL__1up);
   fChain->SetBranchAddress("diphoton_LV_EG_SCALE_ALL__1down", &diphoton_LV_EG_SCALE_ALL__1down, &b_diphoton_LV_EG_SCALE_ALL__1down);
   fChain->SetBranchAddress("diphoton_LV_EG_SCALE_ALL__1up", &diphoton_LV_EG_SCALE_ALL__1up, &b_diphoton_LV_EG_SCALE_ALL__1up);
   fChain->SetBranchAddress("diphoton_LV_PH_EFF_ID_Uncertainty__1down", &diphoton_LV_PH_EFF_ID_Uncertainty__1down, &b_diphoton_LV_PH_EFF_ID_Uncertainty__1down);
   fChain->SetBranchAddress("diphoton_LV_PH_EFF_ID_Uncertainty__1up", &diphoton_LV_PH_EFF_ID_Uncertainty__1up, &b_diphoton_LV_PH_EFF_ID_Uncertainty__1up);
   fChain->SetBranchAddress("diphoton_LV_PH_EFF_TRKISO_Uncertainty__1down", &diphoton_LV_PH_EFF_TRKISO_Uncertainty__1down, &b_diphoton_LV_PH_EFF_TRKISO_Uncertainty__1down);
   fChain->SetBranchAddress("diphoton_LV_PH_EFF_TRKISO_Uncertainty__1up", &diphoton_LV_PH_EFF_TRKISO_Uncertainty__1up, &b_diphoton_LV_PH_EFF_TRKISO_Uncertainty__1up);
   fChain->SetBranchAddress("diphoton_LV_PH_Iso_DDonoff", &diphoton_LV_PH_Iso_DDonoff, &b_diphoton_LV_PH_Iso_DDonoff);
   fChain->SetBranchAddress("diphoton_LV_PRW_DATASF__1down", &diphoton_LV_PRW_DATASF__1down, &b_diphoton_LV_PRW_DATASF__1down);
   fChain->SetBranchAddress("diphoton_LV_PRW_DATASF__1up", &diphoton_LV_PRW_DATASF__1up, &b_diphoton_LV_PRW_DATASF__1up);
   fChain->SetBranchAddress("topoetcone40_leading_EG_RESOLUTION_ALL__1down", &topoetcone40_leading_EG_RESOLUTION_ALL__1down, &b_topoetcone40_leading_EG_RESOLUTION_ALL__1down);
   fChain->SetBranchAddress("topoetcone40_leading_EG_RESOLUTION_ALL__1up", &topoetcone40_leading_EG_RESOLUTION_ALL__1up, &b_topoetcone40_leading_EG_RESOLUTION_ALL__1up);
   fChain->SetBranchAddress("topoetcone40_leading_EG_SCALE_ALL__1down", &topoetcone40_leading_EG_SCALE_ALL__1down, &b_topoetcone40_leading_EG_SCALE_ALL__1down);
   fChain->SetBranchAddress("topoetcone40_leading_EG_SCALE_ALL__1up", &topoetcone40_leading_EG_SCALE_ALL__1up, &b_topoetcone40_leading_EG_SCALE_ALL__1up);
   fChain->SetBranchAddress("topoetcone40_leading_PH_EFF_ID_Uncertainty__1down", &topoetcone40_leading_PH_EFF_ID_Uncertainty__1down, &b_topoetcone40_leading_PH_EFF_ID_Uncertainty__1down);
   fChain->SetBranchAddress("topoetcone40_leading_PH_EFF_ID_Uncertainty__1up", &topoetcone40_leading_PH_EFF_ID_Uncertainty__1up, &b_topoetcone40_leading_PH_EFF_ID_Uncertainty__1up);
   fChain->SetBranchAddress("topoetcone40_leading_PH_EFF_TRKISO_Uncertainty__1down", &topoetcone40_leading_PH_EFF_TRKISO_Uncertainty__1down, &b_topoetcone40_leading_PH_EFF_TRKISO_Uncertainty__1down);
   fChain->SetBranchAddress("topoetcone40_leading_PH_EFF_TRKISO_Uncertainty__1up", &topoetcone40_leading_PH_EFF_TRKISO_Uncertainty__1up, &b_topoetcone40_leading_PH_EFF_TRKISO_Uncertainty__1up);
   fChain->SetBranchAddress("topoetcone40_leading_PH_Iso_DDonoff", &topoetcone40_leading_PH_Iso_DDonoff, &b_topoetcone40_leading_PH_Iso_DDonoff);
   fChain->SetBranchAddress("topoetcone40_leading_PRW_DATASF__1down", &topoetcone40_leading_PRW_DATASF__1down, &b_topoetcone40_leading_PRW_DATASF__1down);
   fChain->SetBranchAddress("topoetcone40_leading_PRW_DATASF__1up", &topoetcone40_leading_PRW_DATASF__1up, &b_topoetcone40_leading_PRW_DATASF__1up);
   fChain->SetBranchAddress("topoetcone40_subleading_EG_RESOLUTION_ALL__1down", &topoetcone40_subleading_EG_RESOLUTION_ALL__1down, &b_topoetcone40_subleading_EG_RESOLUTION_ALL__1down);
   fChain->SetBranchAddress("topoetcone40_subleading_EG_RESOLUTION_ALL__1up", &topoetcone40_subleading_EG_RESOLUTION_ALL__1up, &b_topoetcone40_subleading_EG_RESOLUTION_ALL__1up);
   fChain->SetBranchAddress("topoetcone40_subleading_EG_SCALE_ALL__1down", &topoetcone40_subleading_EG_SCALE_ALL__1down, &b_topoetcone40_subleading_EG_SCALE_ALL__1down);
   fChain->SetBranchAddress("topoetcone40_subleading_EG_SCALE_ALL__1up", &topoetcone40_subleading_EG_SCALE_ALL__1up, &b_topoetcone40_subleading_EG_SCALE_ALL__1up);
   fChain->SetBranchAddress("topoetcone40_subleading_PH_EFF_ID_Uncertainty__1down", &topoetcone40_subleading_PH_EFF_ID_Uncertainty__1down, &b_topoetcone40_subleading_PH_EFF_ID_Uncertainty__1down);
   fChain->SetBranchAddress("topoetcone40_subleading_PH_EFF_ID_Uncertainty__1up", &topoetcone40_subleading_PH_EFF_ID_Uncertainty__1up, &b_topoetcone40_subleading_PH_EFF_ID_Uncertainty__1up);
   fChain->SetBranchAddress("topoetcone40_subleading_PH_EFF_TRKISO_Uncertainty__1down", &topoetcone40_subleading_PH_EFF_TRKISO_Uncertainty__1down, &b_topoetcone40_subleading_PH_EFF_TRKISO_Uncertainty__1down);
   fChain->SetBranchAddress("topoetcone40_subleading_PH_EFF_TRKISO_Uncertainty__1up", &topoetcone40_subleading_PH_EFF_TRKISO_Uncertainty__1up, &b_topoetcone40_subleading_PH_EFF_TRKISO_Uncertainty__1up);
   fChain->SetBranchAddress("topoetcone40_subleading_PH_Iso_DDonoff", &topoetcone40_subleading_PH_Iso_DDonoff, &b_topoetcone40_subleading_PH_Iso_DDonoff);
   fChain->SetBranchAddress("topoetcone40_subleading_PRW_DATASF__1down", &topoetcone40_subleading_PRW_DATASF__1down, &b_topoetcone40_subleading_PRW_DATASF__1down);
   fChain->SetBranchAddress("topoetcone40_subleading_PRW_DATASF__1up", &topoetcone40_subleading_PRW_DATASF__1up, &b_topoetcone40_subleading_PRW_DATASF__1up);
   Notify();
}

Bool_t gravitonNtup::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void gravitonNtup::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t gravitonNtup::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef gravitonNtup_cxx
