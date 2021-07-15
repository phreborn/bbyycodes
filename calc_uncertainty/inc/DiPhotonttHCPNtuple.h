//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Nov  4 17:25:12 2018 by ROOT version 5.34/38
// from TTree output/output
// found on file: ttHCP/ntuple/topreco/had1had2/ttH_aMCnloPy8r.root
//////////////////////////////////////////////////////////

#ifndef DiPhotonttHCPNtuple_h
#define DiPhotonttHCPNtuple_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

using namespace std;
// Header file for the classes stored in the TTree if any.
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.

class DiPhotonttHCPNtuple {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           m_mcChannelNumber;
   Int_t           runNumber;
   ULong64_t       eventNumber;
   Double_t        RNDM;
   Double_t        mu;
   Int_t           m_nlep;
   Int_t           m_nmu;
   Int_t           m_nmu15;
   Int_t           m_nel;
   Int_t           m_njet;
   Int_t           m_njet30;
   Int_t           m_njet35;
   Int_t           m_njet_fwd;
   Int_t           m_njet30_fwd;
   Int_t           m_njet35_fwd;
   Int_t           m_njet_cen;
   Int_t           m_njet30_cen;
   Int_t           m_njet35_cen;
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
   vector<double>  *m_jet_MV2c10;
   vector<int>     *m_jet_PCbtag;
   Double_t        m_mgg;
   Double_t        m_mass_multijet;
   Double_t        m_HT_multijet;
   Double_t        m_HT_30;
   Double_t        m_met;
   Double_t        m_met_x;
   Double_t        m_met_y;
   Double_t        m_sumet;
   Double_t        m_pTlepEtmiss;
   Double_t        m_mT;
   Double_t        m_weight;
   Double_t        weight_1ifb;
   Double_t        m_lumiXsecWeight;
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
   Bool_t          flag_passedPID;
   Bool_t          isPassed;
   Bool_t          flag_passedZey;
   vector<double>  *m_jet_pt;
   vector<double>  *m_jet_E;
   vector<double>  *m_jet_eta;
   vector<double>  *m_jet_phi;
   vector<double>  *m_jet_m;
   vector<bool>    *m_jet_btag60;
   vector<bool>    *m_jet_btag70;
   vector<bool>    *m_jet_btag77;
   vector<bool>    *m_jet_btag85;
   vector<double>  *m_mu_pt;
   vector<double>  *m_mu_eta;
   vector<double>  *m_mu_phi;
   vector<double>  *m_el_pt;
   vector<double>  *m_el_eta;
   vector<double>  *m_el_phi;
   Int_t           m_cateindex;
   Int_t           m_cateindex_wisc;
   Int_t           m_cateindex_h019topReco;
   Double_t        m_mxAODweight;
   Double_t        m_mxAODweight_wisc;
   Double_t        m_mxAODweight_h019topReco;
   Int_t           N_lep;
   Int_t           N_j;
   Int_t           N_j_central;
   Int_t           N_j_30;
   Int_t           N_j_btag30;
   Int_t           N_j_btag;
   Int_t           N_j_central30;
   Int_t           N_bjet_WP70;
   Double_t        m_yy;
   Double_t        m_alljet;
   Double_t        met;
   Double_t        HT_30;
   Double_t        HT;
   Double_t        sumet;
   Double_t        pT_y1;
   Double_t        pT_y2;
   Double_t        TST_met;
   Double_t        TST_sumet;
   Int_t           m_ntruthjet;
   Int_t           m_ntruthjet30;
   Int_t           m_ntruthjet35;
   Int_t           m_ntruthjet_fwd;
   Int_t           m_ntruthjet30_fwd;
   Int_t           m_ntruthjet35_fwd;
   Int_t           m_ntruthjet_cen;
   Int_t           m_ntruthjet30_cen;
   Int_t           m_ntruthjet35_cen;
   vector<double>  *m_truthjet_pt;
   vector<double>  *m_truthjet_E;
   vector<double>  *m_truthjet_eta;
   vector<double>  *m_truthjet_phi;
   vector<double>  *m_truthjet_m;
   Double_t        m_truthmet;
   Double_t        m_truthmet_x;
   Double_t        m_truthmet_y;
   Double_t        m_truthsumet;
   Int_t           m_ntop;
   Int_t           m_ntop_had;
   Int_t           m_ntop_lep;
   Int_t           m_ntop_lep_e;
   Int_t           m_ntop_lep_mu;
   Int_t           m_ntop_lep_tau;
   Int_t           m_ntop_weird;
   Int_t           m_nHiggs;
   vector<double>  *m_top_pt;
   vector<double>  *m_top_eta;
   vector<double>  *m_top_phi;
   vector<double>  *m_top_m;
   vector<double>  *m_top_E;
   vector<double>  *m_W_pt;
   vector<double>  *m_W_eta;
   vector<double>  *m_W_phi;
   vector<double>  *m_W_m;
   vector<double>  *m_W_E;
   vector<double>  *m_b_pt;
   vector<double>  *m_b_eta;
   vector<double>  *m_b_phi;
   vector<double>  *m_b_m;
   vector<double>  *m_b_E;
   vector<double>  *m_Wfrac_1;
   vector<double>  *m_Wfrac_2;
   vector<double>  *m_bfrac_1;
   vector<double>  *m_WdRrt_1;
   vector<double>  *m_WdRrt_2;
   vector<double>  *m_bdRrt_1;
   vector<double>  *m_WdRpt_1;
   vector<double>  *m_WdRpt_2;
   vector<double>  *m_bdRpt_1;
   vector<double>  *m_WdRpr_1;
   vector<double>  *m_WdRpr_2;
   vector<double>  *m_bdRpr_1;
   vector<double>  *m_H_pt;
   vector<double>  *m_H_eta;
   vector<double>  *m_H_phi;
   vector<double>  *m_H_E;
   vector<double>  *m_H_m;
   vector<int>     *truth_triplet_1;
   vector<int>     *truth_triplet_2;
   vector<int>     *truth_triplet_3;
   vector<int>     *truth_triplet_4;
   vector<int>     *reco_triplet_1;
   vector<int>     *reco_triplet_2;
   vector<int>     *reco_triplet_3;
   vector<int>     *reco_triplet_4;
   vector<int>     *truth_blep_1;
   vector<int>     *truth_blep_2;
   vector<int>     *reco_blep_1;
   vector<int>     *reco_blep_2;
   Double_t        ME_gg_ttxh_cosa1;
   Double_t        ME_uux_ttxh_cosa1;
   Double_t        ME_tot_ttxh_cosa1;
   Double_t        ME_gg_ttxh_cosasqrt2;
   Double_t        ME_uux_ttxh_cosasqrt2;
   Double_t        ME_tot_ttxh_cosasqrt2;
   Double_t        ME_gg_ttxh_cosa0;
   Double_t        ME_uux_ttxh_cosa0;
   Double_t        ME_tot_ttxh_cosa0;
   Double_t        had1top_score;
   Double_t        had1top_pt;
   Double_t        had1top_eta;
   Double_t        had1top_phi;
   Double_t        had1top_m;
   Double_t        had1top_E;
   Double_t        had1W_pt;
   Double_t        had1W_eta;
   Double_t        had1W_phi;
   Double_t        had1W_m;
   Double_t        had1W_E;
   Double_t        had2top_score;
   Double_t        had2top_pt;
   Double_t        had2top_eta;
   Double_t        had2top_phi;
   Double_t        had2top_m;
   Double_t        had2top_E;
   Double_t        had2W_pt;
   Double_t        had2W_eta;
   Double_t        had2W_phi;
   Double_t        had2W_m;
   Double_t        had2W_E;
   Double_t        hadtop_score;
   Double_t        hadtop_pt;
   Double_t        hadtop_eta;
   Double_t        hadtop_phi;
   Double_t        hadtop_m;
   Double_t        hadtop_E;
   Double_t        hadW_pt;
   Double_t        hadW_eta;
   Double_t        hadW_phi;
   Double_t        hadW_m;
   Double_t        hadW_E;  
   Double_t        leptop_score;
   Double_t        leptop_pt;
   Double_t        leptop_eta;
   Double_t        leptop_phi;
   Double_t        leptop_m;
   Double_t        leptop_E;
   Double_t        lepW_pt;
   Double_t        lepW_eta;
   Double_t        lepW_phi;
   Double_t        lepW_m;
   Double_t        lepW_E;
   Double_t        weight;
   Double_t        pT_H_true;
   Double_t        eta_H_true;
   Double_t        pT_t_true;
   Double_t        eta_t_true;
   Double_t        pT_tx_true;
   Double_t        eta_tx_true;
   Double_t        delta_eta_top_true;
   Double_t        delta_phi_top_true;
   Double_t        m_ttH_true;
   Double_t        m_tH_true;
   Double_t        m_txH_true;
   Double_t        m_tt_true;
   Double_t        m_ttHall_true;
   Double_t        m_ttall_true;
   Double_t        pT_t_ttrest_true;
   Double_t        pT_tx_ttrest_true;
   Double_t        eta_t_ttrest_true;
   Double_t        eta_tx_ttrest_true;
   Double_t        pT_t_ttHrest_true;
   Double_t        pT_tx_ttHrest_true;
   Double_t        eta_t_ttHrest_true;
   Double_t        eta_tx_ttHrest_true;
   Double_t        delta_eta_b_true;
   Double_t        delta_phi_b_true;
   Double_t        pT_H;
   Double_t        eta_H;
   Double_t        pT_had1t;
   Double_t        eta_had1t;
   Double_t        m_had1tH;
   Double_t        pT_had2t;
   Double_t        eta_had2t;
   Double_t        m_had2tH;
   Double_t        delta_eta_top;
   Double_t        delta_phi_top;
   Double_t        m_ttH;
   Double_t        m_tt;
   Double_t        m_ttHall;
   Double_t        m_ttall;
   Double_t        pT_had1t_ttrest;
   Double_t        pT_had2t_ttrest;
   Double_t        eta_had1t_ttrest;
   Double_t        eta_had2t_ttrest;
   Double_t        pT_had1t_ttHrest;
   Double_t        pT_had2t_ttHrest;
   Double_t        eta_had1t_ttHrest;
   Double_t        eta_had2t_ttHrest;
   Double_t        delta_eta_b;
   Double_t        delta_phi_b;
   Bool_t          had1top_isCorrect;
   Bool_t          had2top_isCorrect;
   Bool_t          hadtop_isCorrect;  
   Bool_t          leptop_isCorrect;

   // List of branches
   TBranch        *b_m_mcChannelNumber;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_RNDM;   //!
   TBranch        *b_mu;   //!
   TBranch        *b_m_nlep;   //!
   TBranch        *b_m_nmu;   //!
   TBranch        *b_m_nmu15;   //!
   TBranch        *b_m_nel;   //!
   TBranch        *b_m_njet;   //!
   TBranch        *b_m_njet30;   //!
   TBranch        *b_m_njet35;   //!
   TBranch        *b_m_njet_fwd;   //!
   TBranch        *b_m_njet30_fwd;   //!
   TBranch        *b_m_njet35_fwd;   //!
   TBranch        *b_m_njet_cen;   //!
   TBranch        *b_m_njet30_cen;   //!
   TBranch        *b_m_njet35_cen;   //!
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
   TBranch        *b_m_jet_MV2c10;   //!
   TBranch        *b_m_jet_PCbtag;   //!
   TBranch        *b_m_mgg;   //!
   TBranch        *b_m_mass_multijet;   //!
   TBranch        *b_m_HT_multijet;   //!
   TBranch        *b_m_HT_30;   //!
   TBranch        *b_m_met;   //!
   TBranch        *b_m_met_x;   //!
   TBranch        *b_m_met_y;   //!
   TBranch        *b_m_sumet;   //!
   TBranch        *b_m_pTlepEtmiss;   //!
   TBranch        *b_m_mT;   //!
   TBranch        *b_m_weight;   //!
   TBranch        *b_weight_1ifb;   //!
   TBranch        *b_m_lumiXsecWeight;   //!
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
   TBranch        *b_flag_passedPID;   //!
   TBranch        *b_isPassed;   //!
   TBranch        *b_flag_passedZey;   //!
   TBranch        *b_m_jet_pt;   //!
   TBranch        *b_m_jet_E;   //!
   TBranch        *b_m_jet_eta;   //!
   TBranch        *b_m_jet_phi;   //!
   TBranch        *b_m_jet_m;   //!
   TBranch        *b_m_jet_btag60;   //!
   TBranch        *b_m_jet_btag70;   //!
   TBranch        *b_m_jet_btag77;   //!
   TBranch        *b_m_jet_btag85;   //!
   TBranch        *b_m_mu_pt;   //!
   TBranch        *b_m_mu_eta;   //!
   TBranch        *b_m_mu_phi;   //!
   TBranch        *b_m_el_pt;   //!
   TBranch        *b_m_el_eta;   //!
   TBranch        *b_m_el_phi;   //!
   TBranch        *b_m_cateindex;   //!
   TBranch        *b_m_cateindex_wisc;   //!
   TBranch        *b_m_cateindex_h019topReco;   //!
   TBranch        *b_m_mxAODweight;   //!
   TBranch        *b_m_mxAODweight_wisc;   //!
   TBranch        *b_m_mxAODweight_h019topReco;   //!
   TBranch        *b_N_lep;   //!
   TBranch        *b_N_j;   //!
   TBranch        *b_N_j_central;   //!
   TBranch        *b_N_j_30;   //!
   TBranch        *b_N_j_btag30;   //!
   TBranch        *b_N_j_btag;   //!
   TBranch        *b_N_j_central30;   //!
   TBranch        *b_N_bjet_WP70;   //!
   TBranch        *b_m_yy;   //!
   TBranch        *b_m_alljet;   //!
   TBranch        *b_met;   //!
   TBranch        *b_HT_30;   //!
   TBranch        *b_HT;   //!
   TBranch        *b_sumet;   //!
   TBranch        *b_pT_y1;   //!
   TBranch        *b_pT_y2;   //!
   TBranch        *b_TST_met;   //!
   TBranch        *b_TST_sumet;   //!
   TBranch        *b_m_ntruthjet;   //!
   TBranch        *b_m_ntruthjet30;   //!
   TBranch        *b_m_ntruthjet35;   //!
   TBranch        *b_m_ntruthjet_fwd;   //!
   TBranch        *b_m_ntruthjet30_fwd;   //!
   TBranch        *b_m_ntruthjet35_fwd;   //!
   TBranch        *b_m_ntruthjet_cen;   //!
   TBranch        *b_m_ntruthjet30_cen;   //!
   TBranch        *b_m_ntruthjet35_cen;   //!
   TBranch        *b_m_truthjet_pt;   //!
   TBranch        *b_m_truthjet_E;   //!
   TBranch        *b_m_truthjet_eta;   //!
   TBranch        *b_m_truthjet_phi;   //!
   TBranch        *b_m_truthjet_m;   //!
   TBranch        *b_m_truthmet;   //!
   TBranch        *b_m_truthmet_x;   //!
   TBranch        *b_m_truthmet_y;   //!
   TBranch        *b_m_truthsumet;   //!
   TBranch        *b_m_ntop;   //!
   TBranch        *b_m_ntop_had;   //!
   TBranch        *b_m_ntop_lep;   //!
   TBranch        *b_m_ntop_lep_e;   //!
   TBranch        *b_m_ntop_lep_mu;   //!
   TBranch        *b_m_ntop_lep_tau;   //!
   TBranch        *b_m_ntop_weird;   //!
   TBranch        *b_m_nHiggs;   //!
   TBranch        *b_m_top_pt;   //!
   TBranch        *b_m_top_eta;   //!
   TBranch        *b_m_top_phi;   //!
   TBranch        *b_m_top_m;   //!
   TBranch        *b_m_top_E;   //!
   TBranch        *b_m_W_pt;   //!
   TBranch        *b_m_W_eta;   //!
   TBranch        *b_m_W_phi;   //!
   TBranch        *b_m_W_m;   //!
   TBranch        *b_m_W_E;   //!
   TBranch        *b_m_b_pt;   //!
   TBranch        *b_m_b_eta;   //!
   TBranch        *b_m_b_phi;   //!
   TBranch        *b_m_b_m;   //!
   TBranch        *b_m_b_E;   //!
   TBranch        *b_m_Wfrac_1;   //!
   TBranch        *b_m_Wfrac_2;   //!
   TBranch        *b_m_bfrac_1;   //!
   TBranch        *b_m_WdRrt_1;   //!
   TBranch        *b_m_WdRrt_2;   //!
   TBranch        *b_m_bdRrt_1;   //!
   TBranch        *b_m_WdRpt_1;   //!
   TBranch        *b_m_WdRpt_2;   //!
   TBranch        *b_m_bdRpt_1;   //!
   TBranch        *b_m_WdRpr_1;   //!
   TBranch        *b_m_WdRpr_2;   //!
   TBranch        *b_m_bdRpr_1;   //!
   TBranch        *b_m_H_pt;   //!
   TBranch        *b_m_H_eta;   //!
   TBranch        *b_m_H_phi;   //!
   TBranch        *b_m_H_E;   //!
   TBranch        *b_m_H_m;   //!
   TBranch        *b_truth_triplet_1;   //!
   TBranch        *b_truth_triplet_2;   //!
   TBranch        *b_truth_triplet_3;   //!
   TBranch        *b_truth_triplet_4;   //!
   TBranch        *b_reco_triplet_1;   //!
   TBranch        *b_reco_triplet_2;   //!
   TBranch        *b_reco_triplet_3;   //!
   TBranch        *b_reco_triplet_4;   //!
   TBranch        *b_truth_blep_1;   //!
   TBranch        *b_truth_blep_2;   //!
   TBranch        *b_reco_blep_1;   //!
   TBranch        *b_reco_blep_2;   //!
   TBranch        *b_ME_gg_ttxh_cosa1;   //!
   TBranch        *b_ME_uux_ttxh_cosa1;   //!
   TBranch        *b_ME_tot_ttxh_cosa1;   //!
   TBranch        *b_ME_gg_ttxh_cosasqrt2;   //!
   TBranch        *b_ME_uux_ttxh_cosasqrt2;   //!
   TBranch        *b_ME_tot_ttxh_cosasqrt2;   //!
   TBranch        *b_ME_gg_ttxh_cosa0;   //!
   TBranch        *b_ME_uux_ttxh_cosa0;   //!
   TBranch        *b_ME_tot_ttxh_cosa0;   //!
   TBranch        *b_had1top_score;   //!
   TBranch        *b_had1top_pt;   //!
   TBranch        *b_had1top_eta;   //!
   TBranch        *b_had1top_phi;   //!
   TBranch        *b_had1top_m;   //!
   TBranch        *b_had1top_E;   //!
   TBranch        *b_had1W_pt;   //!
   TBranch        *b_had1W_eta;   //!
   TBranch        *b_had1W_phi;   //!
   TBranch        *b_had1W_m;   //!
   TBranch        *b_had1W_E;   //!
   TBranch        *b_had2top_score;   //!
   TBranch        *b_had2top_pt;   //!
   TBranch        *b_had2top_eta;   //!
   TBranch        *b_had2top_phi;   //!
   TBranch        *b_had2top_m;   //!
   TBranch        *b_had2top_E;   //!
   TBranch        *b_had2W_pt;   //!
   TBranch        *b_had2W_eta;   //!
   TBranch        *b_had2W_phi;   //!
   TBranch        *b_had2W_m;   //!
   TBranch        *b_had2W_E;   //!
   TBranch        *b_hadtop_score;   //!
   TBranch        *b_hadtop_pt;   //!
   TBranch        *b_hadtop_eta;   //!
   TBranch        *b_hadtop_phi;   //!
   TBranch        *b_hadtop_m;   //!
   TBranch        *b_hadtop_E;   //!
   TBranch        *b_hadW_pt;   //!
   TBranch        *b_hadW_eta;   //!
   TBranch        *b_hadW_phi;   //!
   TBranch        *b_hadW_m;   //!
   TBranch        *b_hadW_E;   //!  
   TBranch        *b_leptop_score;   //!
   TBranch        *b_leptop_pt;   //!
   TBranch        *b_leptop_eta;   //!
   TBranch        *b_leptop_phi;   //!
   TBranch        *b_leptop_m;   //!
   TBranch        *b_leptop_E;   //!
   TBranch        *b_lepW_pt;   //!
   TBranch        *b_lepW_eta;   //!
   TBranch        *b_lepW_phi;   //!
   TBranch        *b_lepW_m;   //!
   TBranch        *b_lepW_E;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_pT_H_true;   //!
   TBranch        *b_eta_H_true;   //!
   TBranch        *b_pT_t_true;   //!
   TBranch        *b_eta_t_true;   //!
   TBranch        *b_pT_tx_true;   //!
   TBranch        *b_eta_tx_true;   //!
   TBranch        *b_delta_eta_top_true;   //!
   TBranch        *b_delta_phi_top_true;   //!
   TBranch        *b_m_ttH_true;   //!
   TBranch        *b_m_tH_true;   //!
   TBranch        *b_m_txH_true;   //!
   TBranch        *b_m_tt_true;   //!
   TBranch        *b_m_ttHall_true;   //!
   TBranch        *b_m_ttall_true;   //!
   TBranch        *b_pT_t_ttrest_true;   //!
   TBranch        *b_pT_tx_ttrest_true;   //!
   TBranch        *b_eta_t_ttrest_true;   //!
   TBranch        *b_eta_tx_ttrest_true;   //!
   TBranch        *b_pT_t_ttHrest_true;   //!
   TBranch        *b_pT_tx_ttHrest_true;   //!
   TBranch        *b_eta_t_ttHrest_true;   //!
   TBranch        *b_eta_tx_ttHrest_true;   //!
   TBranch        *b_delta_eta_b_true;   //!
   TBranch        *b_delta_phi_b_true;   //!
   TBranch        *b_pT_H;   //!
   TBranch        *b_eta_H;   //!
   TBranch        *b_pT_had1t;   //!
   TBranch        *b_eta_had1t;   //!
   TBranch        *b_m_had1tH;   //!
   TBranch        *b_pT_had2t;   //!
   TBranch        *b_eta_had2t;   //!
   TBranch        *b_m_had2tH;   //!
   TBranch        *b_delta_eta_top;   //!
   TBranch        *b_delta_phi_top;   //!
   TBranch        *b_m_ttH;   //!
   TBranch        *b_m_tt;   //!
   TBranch        *b_m_ttHall;   //!
   TBranch        *b_m_ttall;   //!
   TBranch        *b_pT_had1t_ttrest;   //!
   TBranch        *b_pT_had2t_ttrest;   //!
   TBranch        *b_eta_had1t_ttrest;   //!
   TBranch        *b_eta_had2t_ttrest;   //!
   TBranch        *b_pT_had1t_ttHrest;   //!
   TBranch        *b_pT_had2t_ttHrest;   //!
   TBranch        *b_eta_had1t_ttHrest;   //!
   TBranch        *b_eta_had2t_ttHrest;   //!
   TBranch        *b_delta_eta_b;   //!
   TBranch        *b_delta_phi_b;   //!
   TBranch        *b_had1top_isCorrect;   //!
   TBranch        *b_had2top_isCorrect;   //!
   TBranch        *b_hadtop_isCorrect;   //!
   TBranch        *b_leptop_isCorrect;   //!
  
   DiPhotonttHCPNtuple(TTree *tree=0);
   virtual ~DiPhotonttHCPNtuple();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef DiPhotonttHCPNtuple_cxx
DiPhotonttHCPNtuple::DiPhotonttHCPNtuple(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("ttHCP/ntuple/topreco/had1had2/ttH_aMCnloPy8r.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("ttHCP/ntuple/topreco/had1had2/ttH_aMCnloPy8r.root");
      }
      f->GetObject("output",tree);

   }
   Init(tree);
}

DiPhotonttHCPNtuple::~DiPhotonttHCPNtuple()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t DiPhotonttHCPNtuple::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t DiPhotonttHCPNtuple::LoadTree(Long64_t entry)
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

void DiPhotonttHCPNtuple::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   m_jet_MV2c10 = 0;
   m_jet_PCbtag = 0;
   m_jet_pt = 0;
   m_jet_E = 0;
   m_jet_eta = 0;
   m_jet_phi = 0;
   m_jet_m = 0;
   m_jet_btag60 = 0;
   m_jet_btag70 = 0;
   m_jet_btag77 = 0;
   m_jet_btag85 = 0;
   m_mu_pt = 0;
   m_mu_eta = 0;
   m_mu_phi = 0;
   m_el_pt = 0;
   m_el_eta = 0;
   m_el_phi = 0;
   m_truthjet_pt = 0;
   m_truthjet_E = 0;
   m_truthjet_eta = 0;
   m_truthjet_phi = 0;
   m_truthjet_m = 0;
   m_top_pt = 0;
   m_top_eta = 0;
   m_top_phi = 0;
   m_top_m = 0;
   m_top_E = 0;
   m_W_pt = 0;
   m_W_eta = 0;
   m_W_phi = 0;
   m_W_m = 0;
   m_W_E = 0;
   m_b_pt = 0;
   m_b_eta = 0;
   m_b_phi = 0;
   m_b_m = 0;
   m_b_E = 0;
   m_Wfrac_1 = 0;
   m_Wfrac_2 = 0;
   m_bfrac_1 = 0;
   m_WdRrt_1 = 0;
   m_WdRrt_2 = 0;
   m_bdRrt_1 = 0;
   m_WdRpt_1 = 0;
   m_WdRpt_2 = 0;
   m_bdRpt_1 = 0;
   m_WdRpr_1 = 0;
   m_WdRpr_2 = 0;
   m_bdRpr_1 = 0;
   m_H_pt = 0;
   m_H_eta = 0;
   m_H_phi = 0;
   m_H_E = 0;
   m_H_m = 0;
   truth_triplet_1 = 0;
   truth_triplet_2 = 0;
   truth_triplet_3 = 0;
   truth_triplet_4 = 0;
   reco_triplet_1 = 0;
   reco_triplet_2 = 0;
   reco_triplet_3 = 0;
   reco_triplet_4 = 0;
   truth_blep_1 = 0;
   truth_blep_2 = 0;
   reco_blep_1 = 0;
   reco_blep_2 = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("m_mcChannelNumber", &m_mcChannelNumber, &b_m_mcChannelNumber);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("RNDM", &RNDM, &b_RNDM);
   fChain->SetBranchAddress("mu", &mu, &b_mu);
   fChain->SetBranchAddress("m_nlep", &m_nlep, &b_m_nlep);
   fChain->SetBranchAddress("m_nmu", &m_nmu, &b_m_nmu);
   fChain->SetBranchAddress("m_nmu15", &m_nmu15, &b_m_nmu15);
   fChain->SetBranchAddress("m_nel", &m_nel, &b_m_nel);
   fChain->SetBranchAddress("m_njet", &m_njet, &b_m_njet);
   fChain->SetBranchAddress("m_njet30", &m_njet30, &b_m_njet30);
   fChain->SetBranchAddress("m_njet35", &m_njet35, &b_m_njet35);
   fChain->SetBranchAddress("m_njet_fwd", &m_njet_fwd, &b_m_njet_fwd);
   fChain->SetBranchAddress("m_njet30_fwd", &m_njet30_fwd, &b_m_njet30_fwd);
   fChain->SetBranchAddress("m_njet35_fwd", &m_njet35_fwd, &b_m_njet35_fwd);
   fChain->SetBranchAddress("m_njet_cen", &m_njet_cen, &b_m_njet_cen);
   fChain->SetBranchAddress("m_njet30_cen", &m_njet30_cen, &b_m_njet30_cen);
   fChain->SetBranchAddress("m_njet35_cen", &m_njet35_cen, &b_m_njet35_cen);
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
   fChain->SetBranchAddress("m_jet_MV2c10", &m_jet_MV2c10, &b_m_jet_MV2c10);
   fChain->SetBranchAddress("m_jet_PCbtag", &m_jet_PCbtag, &b_m_jet_PCbtag);
   fChain->SetBranchAddress("m_mgg", &m_mgg, &b_m_mgg);
   fChain->SetBranchAddress("m_mass_multijet", &m_mass_multijet, &b_m_mass_multijet);
   fChain->SetBranchAddress("m_HT_multijet", &m_HT_multijet, &b_m_HT_multijet);
   fChain->SetBranchAddress("m_HT_30", &m_HT_30, &b_m_HT_30);
   fChain->SetBranchAddress("m_met", &m_met, &b_m_met);
   fChain->SetBranchAddress("m_met_x", &m_met_x, &b_m_met_x);
   fChain->SetBranchAddress("m_met_y", &m_met_y, &b_m_met_y);
   fChain->SetBranchAddress("m_sumet", &m_sumet, &b_m_sumet);
   fChain->SetBranchAddress("m_pTlepEtmiss", &m_pTlepEtmiss, &b_m_pTlepEtmiss);
   fChain->SetBranchAddress("m_mT", &m_mT, &b_m_mT);
   fChain->SetBranchAddress("m_weight", &m_weight, &b_m_weight);
   fChain->SetBranchAddress("weight_1ifb", &weight_1ifb, &b_weight_1ifb);
   fChain->SetBranchAddress("m_lumiXsecWeight", &m_lumiXsecWeight, &b_m_lumiXsecWeight);
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
   fChain->SetBranchAddress("flag_passedPID", &flag_passedPID, &b_flag_passedPID);
   fChain->SetBranchAddress("isPassed", &isPassed, &b_isPassed);
   fChain->SetBranchAddress("flag_passedZey", &flag_passedZey, &b_flag_passedZey);
   fChain->SetBranchAddress("m_jet_pt", &m_jet_pt, &b_m_jet_pt);
   fChain->SetBranchAddress("m_jet_E", &m_jet_E, &b_m_jet_E);
   fChain->SetBranchAddress("m_jet_eta", &m_jet_eta, &b_m_jet_eta);
   fChain->SetBranchAddress("m_jet_phi", &m_jet_phi, &b_m_jet_phi);
   fChain->SetBranchAddress("m_jet_m", &m_jet_m, &b_m_jet_m);
   fChain->SetBranchAddress("m_jet_btag60", &m_jet_btag60, &b_m_jet_btag60);
   fChain->SetBranchAddress("m_jet_btag70", &m_jet_btag70, &b_m_jet_btag70);
   fChain->SetBranchAddress("m_jet_btag77", &m_jet_btag77, &b_m_jet_btag77);
   fChain->SetBranchAddress("m_jet_btag85", &m_jet_btag85, &b_m_jet_btag85);
   fChain->SetBranchAddress("m_mu_pt", &m_mu_pt, &b_m_mu_pt);
   fChain->SetBranchAddress("m_mu_eta", &m_mu_eta, &b_m_mu_eta);
   fChain->SetBranchAddress("m_mu_phi", &m_mu_phi, &b_m_mu_phi);
   fChain->SetBranchAddress("m_el_pt", &m_el_pt, &b_m_el_pt);
   fChain->SetBranchAddress("m_el_eta", &m_el_eta, &b_m_el_eta);
   fChain->SetBranchAddress("m_el_phi", &m_el_phi, &b_m_el_phi);
   fChain->SetBranchAddress("m_cateindex", &m_cateindex, &b_m_cateindex);
   fChain->SetBranchAddress("m_cateindex_wisc", &m_cateindex_wisc, &b_m_cateindex_wisc);
   fChain->SetBranchAddress("m_cateindex_h019topReco", &m_cateindex_h019topReco, &b_m_cateindex_h019topReco);
   fChain->SetBranchAddress("m_mxAODweight", &m_mxAODweight, &b_m_mxAODweight);
   fChain->SetBranchAddress("m_mxAODweight_wisc", &m_mxAODweight_wisc, &b_m_mxAODweight_wisc);
   fChain->SetBranchAddress("m_mxAODweight_h019topReco", &m_mxAODweight_h019topReco, &b_m_mxAODweight_h019topReco);
   fChain->SetBranchAddress("N_lep", &N_lep, &b_N_lep);
   fChain->SetBranchAddress("N_j", &N_j, &b_N_j);
   fChain->SetBranchAddress("N_j_central", &N_j_central, &b_N_j_central);
   fChain->SetBranchAddress("N_j_30", &N_j_30, &b_N_j_30);
   fChain->SetBranchAddress("N_j_btag30", &N_j_btag30, &b_N_j_btag30);
   fChain->SetBranchAddress("N_j_btag", &N_j_btag, &b_N_j_btag);
   fChain->SetBranchAddress("N_j_central30", &N_j_central30, &b_N_j_central30);
   fChain->SetBranchAddress("N_bjet_WP70", &N_bjet_WP70, &b_N_bjet_WP70);
   fChain->SetBranchAddress("m_yy", &m_yy, &b_m_yy);
   fChain->SetBranchAddress("m_alljet", &m_alljet, &b_m_alljet);
   fChain->SetBranchAddress("met", &met, &b_met);
   fChain->SetBranchAddress("HT_30", &HT_30, &b_HT_30);
   fChain->SetBranchAddress("HT", &HT, &b_HT);
   fChain->SetBranchAddress("sumet", &sumet, &b_sumet);
   fChain->SetBranchAddress("pT_y1", &pT_y1, &b_pT_y1);
   fChain->SetBranchAddress("pT_y2", &pT_y2, &b_pT_y2);
   fChain->SetBranchAddress("TST_met", &TST_met, &b_TST_met);
   fChain->SetBranchAddress("TST_sumet", &TST_sumet, &b_TST_sumet);
   fChain->SetBranchAddress("m_ntruthjet", &m_ntruthjet, &b_m_ntruthjet);
   fChain->SetBranchAddress("m_ntruthjet30", &m_ntruthjet30, &b_m_ntruthjet30);
   fChain->SetBranchAddress("m_ntruthjet35", &m_ntruthjet35, &b_m_ntruthjet35);
   fChain->SetBranchAddress("m_ntruthjet_fwd", &m_ntruthjet_fwd, &b_m_ntruthjet_fwd);
   fChain->SetBranchAddress("m_ntruthjet30_fwd", &m_ntruthjet30_fwd, &b_m_ntruthjet30_fwd);
   fChain->SetBranchAddress("m_ntruthjet35_fwd", &m_ntruthjet35_fwd, &b_m_ntruthjet35_fwd);
   fChain->SetBranchAddress("m_ntruthjet_cen", &m_ntruthjet_cen, &b_m_ntruthjet_cen);
   fChain->SetBranchAddress("m_ntruthjet30_cen", &m_ntruthjet30_cen, &b_m_ntruthjet30_cen);
   fChain->SetBranchAddress("m_ntruthjet35_cen", &m_ntruthjet35_cen, &b_m_ntruthjet35_cen);
   fChain->SetBranchAddress("m_truthjet_pt", &m_truthjet_pt, &b_m_truthjet_pt);
   fChain->SetBranchAddress("m_truthjet_E", &m_truthjet_E, &b_m_truthjet_E);
   fChain->SetBranchAddress("m_truthjet_eta", &m_truthjet_eta, &b_m_truthjet_eta);
   fChain->SetBranchAddress("m_truthjet_phi", &m_truthjet_phi, &b_m_truthjet_phi);
   fChain->SetBranchAddress("m_truthjet_m", &m_truthjet_m, &b_m_truthjet_m);
   fChain->SetBranchAddress("m_truthmet", &m_truthmet, &b_m_truthmet);
   fChain->SetBranchAddress("m_truthmet_x", &m_truthmet_x, &b_m_truthmet_x);
   fChain->SetBranchAddress("m_truthmet_y", &m_truthmet_y, &b_m_truthmet_y);
   fChain->SetBranchAddress("m_truthsumet", &m_truthsumet, &b_m_truthsumet);
   fChain->SetBranchAddress("m_ntop", &m_ntop, &b_m_ntop);
   fChain->SetBranchAddress("m_ntop_had", &m_ntop_had, &b_m_ntop_had);
   fChain->SetBranchAddress("m_ntop_lep", &m_ntop_lep, &b_m_ntop_lep);
   fChain->SetBranchAddress("m_ntop_lep_e", &m_ntop_lep_e, &b_m_ntop_lep_e);
   fChain->SetBranchAddress("m_ntop_lep_mu", &m_ntop_lep_mu, &b_m_ntop_lep_mu);
   fChain->SetBranchAddress("m_ntop_lep_tau", &m_ntop_lep_tau, &b_m_ntop_lep_tau);
   fChain->SetBranchAddress("m_ntop_weird", &m_ntop_weird, &b_m_ntop_weird);
   fChain->SetBranchAddress("m_nHiggs", &m_nHiggs, &b_m_nHiggs);
   fChain->SetBranchAddress("m_top_pt", &m_top_pt, &b_m_top_pt);
   fChain->SetBranchAddress("m_top_eta", &m_top_eta, &b_m_top_eta);
   fChain->SetBranchAddress("m_top_phi", &m_top_phi, &b_m_top_phi);
   fChain->SetBranchAddress("m_top_m", &m_top_m, &b_m_top_m);
   fChain->SetBranchAddress("m_top_E", &m_top_E, &b_m_top_E);
   fChain->SetBranchAddress("m_W_pt", &m_W_pt, &b_m_W_pt);
   fChain->SetBranchAddress("m_W_eta", &m_W_eta, &b_m_W_eta);
   fChain->SetBranchAddress("m_W_phi", &m_W_phi, &b_m_W_phi);
   fChain->SetBranchAddress("m_W_m", &m_W_m, &b_m_W_m);
   fChain->SetBranchAddress("m_W_E", &m_W_E, &b_m_W_E);
   fChain->SetBranchAddress("m_b_pt", &m_b_pt, &b_m_b_pt);
   fChain->SetBranchAddress("m_b_eta", &m_b_eta, &b_m_b_eta);
   fChain->SetBranchAddress("m_b_phi", &m_b_phi, &b_m_b_phi);
   fChain->SetBranchAddress("m_b_m", &m_b_m, &b_m_b_m);
   fChain->SetBranchAddress("m_b_E", &m_b_E, &b_m_b_E);
   fChain->SetBranchAddress("m_Wfrac_1", &m_Wfrac_1, &b_m_Wfrac_1);
   fChain->SetBranchAddress("m_Wfrac_2", &m_Wfrac_2, &b_m_Wfrac_2);
   fChain->SetBranchAddress("m_bfrac_1", &m_bfrac_1, &b_m_bfrac_1);
   fChain->SetBranchAddress("m_WdRrt_1", &m_WdRrt_1, &b_m_WdRrt_1);
   fChain->SetBranchAddress("m_WdRrt_2", &m_WdRrt_2, &b_m_WdRrt_2);
   fChain->SetBranchAddress("m_bdRrt_1", &m_bdRrt_1, &b_m_bdRrt_1);
   fChain->SetBranchAddress("m_WdRpt_1", &m_WdRpt_1, &b_m_WdRpt_1);
   fChain->SetBranchAddress("m_WdRpt_2", &m_WdRpt_2, &b_m_WdRpt_2);
   fChain->SetBranchAddress("m_bdRpt_1", &m_bdRpt_1, &b_m_bdRpt_1);
   fChain->SetBranchAddress("m_WdRpr_1", &m_WdRpr_1, &b_m_WdRpr_1);
   fChain->SetBranchAddress("m_WdRpr_2", &m_WdRpr_2, &b_m_WdRpr_2);
   fChain->SetBranchAddress("m_bdRpr_1", &m_bdRpr_1, &b_m_bdRpr_1);
   fChain->SetBranchAddress("m_H_pt", &m_H_pt, &b_m_H_pt);
   fChain->SetBranchAddress("m_H_eta", &m_H_eta, &b_m_H_eta);
   fChain->SetBranchAddress("m_H_phi", &m_H_phi, &b_m_H_phi);
   fChain->SetBranchAddress("m_H_E", &m_H_E, &b_m_H_E);
   fChain->SetBranchAddress("m_H_m", &m_H_m, &b_m_H_m);
   fChain->SetBranchAddress("truth_triplet_1", &truth_triplet_1, &b_truth_triplet_1);
   fChain->SetBranchAddress("truth_triplet_2", &truth_triplet_2, &b_truth_triplet_2);
   fChain->SetBranchAddress("truth_triplet_3", &truth_triplet_3, &b_truth_triplet_3);
   fChain->SetBranchAddress("truth_triplet_4", &truth_triplet_4, &b_truth_triplet_4);
   fChain->SetBranchAddress("reco_triplet_1", &reco_triplet_1, &b_reco_triplet_1);
   fChain->SetBranchAddress("reco_triplet_2", &reco_triplet_2, &b_reco_triplet_2);
   fChain->SetBranchAddress("reco_triplet_3", &reco_triplet_3, &b_reco_triplet_3);
   fChain->SetBranchAddress("reco_triplet_4", &reco_triplet_4, &b_reco_triplet_4);
   fChain->SetBranchAddress("truth_blep_1", &truth_blep_1, &b_truth_blep_1);
   fChain->SetBranchAddress("truth_blep_2", &truth_blep_2, &b_truth_blep_2);
   fChain->SetBranchAddress("reco_blep_1", &reco_blep_1, &b_reco_blep_1);
   fChain->SetBranchAddress("reco_blep_2", &reco_blep_2, &b_reco_blep_2);
   fChain->SetBranchAddress("ME_gg_ttxh_cosa1", &ME_gg_ttxh_cosa1, &b_ME_gg_ttxh_cosa1);
   fChain->SetBranchAddress("ME_uux_ttxh_cosa1", &ME_uux_ttxh_cosa1, &b_ME_uux_ttxh_cosa1);
   fChain->SetBranchAddress("ME_tot_ttxh_cosa1", &ME_tot_ttxh_cosa1, &b_ME_tot_ttxh_cosa1);
   fChain->SetBranchAddress("ME_gg_ttxh_cosasqrt2", &ME_gg_ttxh_cosasqrt2, &b_ME_gg_ttxh_cosasqrt2);
   fChain->SetBranchAddress("ME_uux_ttxh_cosasqrt2", &ME_uux_ttxh_cosasqrt2, &b_ME_uux_ttxh_cosasqrt2);
   fChain->SetBranchAddress("ME_tot_ttxh_cosasqrt2", &ME_tot_ttxh_cosasqrt2, &b_ME_tot_ttxh_cosasqrt2);
   fChain->SetBranchAddress("ME_gg_ttxh_cosa0", &ME_gg_ttxh_cosa0, &b_ME_gg_ttxh_cosa0);
   fChain->SetBranchAddress("ME_uux_ttxh_cosa0", &ME_uux_ttxh_cosa0, &b_ME_uux_ttxh_cosa0);
   fChain->SetBranchAddress("ME_tot_ttxh_cosa0", &ME_tot_ttxh_cosa0, &b_ME_tot_ttxh_cosa0);
   fChain->SetBranchAddress("had1top_score", &had1top_score, &b_had1top_score);
   fChain->SetBranchAddress("had1top_pt", &had1top_pt, &b_had1top_pt);
   fChain->SetBranchAddress("had1top_eta", &had1top_eta, &b_had1top_eta);
   fChain->SetBranchAddress("had1top_phi", &had1top_phi, &b_had1top_phi);
   fChain->SetBranchAddress("had1top_m", &had1top_m, &b_had1top_m);
   fChain->SetBranchAddress("had1top_E", &had1top_E, &b_had1top_E);
   fChain->SetBranchAddress("had1W_pt", &had1W_pt, &b_had1W_pt);
   fChain->SetBranchAddress("had1W_eta", &had1W_eta, &b_had1W_eta);
   fChain->SetBranchAddress("had1W_phi", &had1W_phi, &b_had1W_phi);
   fChain->SetBranchAddress("had1W_m", &had1W_m, &b_had1W_m);
   fChain->SetBranchAddress("had1W_E", &had1W_E, &b_had1W_E);
   fChain->SetBranchAddress("had2top_score", &had2top_score, &b_had2top_score);
   fChain->SetBranchAddress("had2top_pt", &had2top_pt, &b_had2top_pt);
   fChain->SetBranchAddress("had2top_eta", &had2top_eta, &b_had2top_eta);
   fChain->SetBranchAddress("had2top_phi", &had2top_phi, &b_had2top_phi);
   fChain->SetBranchAddress("had2top_m", &had2top_m, &b_had2top_m);
   fChain->SetBranchAddress("had2top_E", &had2top_E, &b_had2top_E);
   fChain->SetBranchAddress("had2W_pt", &had2W_pt, &b_had2W_pt);
   fChain->SetBranchAddress("had2W_eta", &had2W_eta, &b_had2W_eta);
   fChain->SetBranchAddress("had2W_phi", &had2W_phi, &b_had2W_phi);
   fChain->SetBranchAddress("had2W_m", &had2W_m, &b_had2W_m);
   fChain->SetBranchAddress("had2W_E", &had2W_E, &b_had2W_E);
   fChain->SetBranchAddress("hadtop_score", &hadtop_score, &b_hadtop_score);
   fChain->SetBranchAddress("hadtop_pt", &hadtop_pt, &b_hadtop_pt);
   fChain->SetBranchAddress("hadtop_eta", &hadtop_eta, &b_hadtop_eta);
   fChain->SetBranchAddress("hadtop_phi", &hadtop_phi, &b_hadtop_phi);
   fChain->SetBranchAddress("hadtop_m", &hadtop_m, &b_hadtop_m);
   fChain->SetBranchAddress("hadtop_E", &hadtop_E, &b_hadtop_E);
   fChain->SetBranchAddress("hadW_pt", &hadW_pt, &b_hadW_pt);
   fChain->SetBranchAddress("hadW_eta", &hadW_eta, &b_hadW_eta);
   fChain->SetBranchAddress("hadW_phi", &hadW_phi, &b_hadW_phi);
   fChain->SetBranchAddress("hadW_m", &hadW_m, &b_hadW_m);
   fChain->SetBranchAddress("hadW_E", &hadW_E, &b_hadW_E);
   fChain->SetBranchAddress("leptop_score", &leptop_score, &b_leptop_score);
   fChain->SetBranchAddress("leptop_pt", &leptop_pt, &b_leptop_pt);
   fChain->SetBranchAddress("leptop_eta", &leptop_eta, &b_leptop_eta);
   fChain->SetBranchAddress("leptop_phi", &leptop_phi, &b_leptop_phi);
   fChain->SetBranchAddress("leptop_m", &leptop_m, &b_leptop_m);
   fChain->SetBranchAddress("leptop_E", &leptop_E, &b_leptop_E);
   fChain->SetBranchAddress("lepW_pt", &lepW_pt, &b_lepW_pt);
   fChain->SetBranchAddress("lepW_eta", &lepW_eta, &b_lepW_eta);
   fChain->SetBranchAddress("lepW_phi", &lepW_phi, &b_lepW_phi);
   fChain->SetBranchAddress("lepW_m", &lepW_m, &b_lepW_m);
   fChain->SetBranchAddress("lepW_E", &lepW_E, &b_lepW_E);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("pT_H_true", &pT_H_true, &b_pT_H_true);
   fChain->SetBranchAddress("eta_H_true", &eta_H_true, &b_eta_H_true);
   fChain->SetBranchAddress("pT_t_true", &pT_t_true, &b_pT_t_true);
   fChain->SetBranchAddress("eta_t_true", &eta_t_true, &b_eta_t_true);
   fChain->SetBranchAddress("pT_tx_true", &pT_tx_true, &b_pT_tx_true);
   fChain->SetBranchAddress("eta_tx_true", &eta_tx_true, &b_eta_tx_true);
   fChain->SetBranchAddress("delta_eta_top_true", &delta_eta_top_true, &b_delta_eta_top_true);
   fChain->SetBranchAddress("delta_phi_top_true", &delta_phi_top_true, &b_delta_phi_top_true);
   fChain->SetBranchAddress("m_ttH_true", &m_ttH_true, &b_m_ttH_true);
   fChain->SetBranchAddress("m_tH_true", &m_tH_true, &b_m_tH_true);
   fChain->SetBranchAddress("m_txH_true", &m_txH_true, &b_m_txH_true);
   fChain->SetBranchAddress("m_tt_true", &m_tt_true, &b_m_tt_true);
   fChain->SetBranchAddress("m_ttHall_true", &m_ttHall_true, &b_m_ttHall_true);
   fChain->SetBranchAddress("m_ttall_true", &m_ttall_true, &b_m_ttall_true);
   fChain->SetBranchAddress("pT_t_ttrest_true", &pT_t_ttrest_true, &b_pT_t_ttrest_true);
   fChain->SetBranchAddress("pT_tx_ttrest_true", &pT_tx_ttrest_true, &b_pT_tx_ttrest_true);
   fChain->SetBranchAddress("eta_t_ttrest_true", &eta_t_ttrest_true, &b_eta_t_ttrest_true);
   fChain->SetBranchAddress("eta_tx_ttrest_true", &eta_tx_ttrest_true, &b_eta_tx_ttrest_true);
   fChain->SetBranchAddress("pT_t_ttHrest_true", &pT_t_ttHrest_true, &b_pT_t_ttHrest_true);
   fChain->SetBranchAddress("pT_tx_ttHrest_true", &pT_tx_ttHrest_true, &b_pT_tx_ttHrest_true);
   fChain->SetBranchAddress("eta_t_ttHrest_true", &eta_t_ttHrest_true, &b_eta_t_ttHrest_true);
   fChain->SetBranchAddress("eta_tx_ttHrest_true", &eta_tx_ttHrest_true, &b_eta_tx_ttHrest_true);
   fChain->SetBranchAddress("delta_eta_b_true", &delta_eta_b_true, &b_delta_eta_b_true);
   fChain->SetBranchAddress("delta_phi_b_true", &delta_phi_b_true, &b_delta_phi_b_true);
   fChain->SetBranchAddress("pT_H", &pT_H, &b_pT_H);
   fChain->SetBranchAddress("eta_H", &eta_H, &b_eta_H);
   fChain->SetBranchAddress("pT_had1t", &pT_had1t, &b_pT_had1t);
   fChain->SetBranchAddress("eta_had1t", &eta_had1t, &b_eta_had1t);
   fChain->SetBranchAddress("m_had1tH", &m_had1tH, &b_m_had1tH);
   fChain->SetBranchAddress("pT_had2t", &pT_had2t, &b_pT_had2t);
   fChain->SetBranchAddress("eta_had2t", &eta_had2t, &b_eta_had2t);
   fChain->SetBranchAddress("m_had2tH", &m_had2tH, &b_m_had2tH);
   fChain->SetBranchAddress("delta_eta_top", &delta_eta_top, &b_delta_eta_top);
   fChain->SetBranchAddress("delta_phi_top", &delta_phi_top, &b_delta_phi_top);
   fChain->SetBranchAddress("m_ttH", &m_ttH, &b_m_ttH);
   fChain->SetBranchAddress("m_tt", &m_tt, &b_m_tt);
   fChain->SetBranchAddress("m_ttHall", &m_ttHall, &b_m_ttHall);
   fChain->SetBranchAddress("m_ttall", &m_ttall, &b_m_ttall);
   fChain->SetBranchAddress("pT_had1t_ttrest", &pT_had1t_ttrest, &b_pT_had1t_ttrest);
   fChain->SetBranchAddress("pT_had2t_ttrest", &pT_had2t_ttrest, &b_pT_had2t_ttrest);
   fChain->SetBranchAddress("eta_had1t_ttrest", &eta_had1t_ttrest, &b_eta_had1t_ttrest);
   fChain->SetBranchAddress("eta_had2t_ttrest", &eta_had2t_ttrest, &b_eta_had2t_ttrest);
   fChain->SetBranchAddress("pT_had1t_ttHrest", &pT_had1t_ttHrest, &b_pT_had1t_ttHrest);
   fChain->SetBranchAddress("pT_had2t_ttHrest", &pT_had2t_ttHrest, &b_pT_had2t_ttHrest);
   fChain->SetBranchAddress("eta_had1t_ttHrest", &eta_had1t_ttHrest, &b_eta_had1t_ttHrest);
   fChain->SetBranchAddress("eta_had2t_ttHrest", &eta_had2t_ttHrest, &b_eta_had2t_ttHrest);
   fChain->SetBranchAddress("delta_eta_b", &delta_eta_b, &b_delta_eta_b);
   fChain->SetBranchAddress("delta_phi_b", &delta_phi_b, &b_delta_phi_b);
   fChain->SetBranchAddress("had1top_isCorrect", &had1top_isCorrect, &b_had1top_isCorrect);
   fChain->SetBranchAddress("had2top_isCorrect", &had2top_isCorrect, &b_had2top_isCorrect);
   fChain->SetBranchAddress("hadtop_isCorrect", &hadtop_isCorrect, &b_hadtop_isCorrect);
   fChain->SetBranchAddress("leptop_isCorrect", &leptop_isCorrect, &b_leptop_isCorrect);   
   Notify();
}

Bool_t DiPhotonttHCPNtuple::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void DiPhotonttHCPNtuple::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t DiPhotonttHCPNtuple::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef DiPhotonttHCPNtuple_cxx
