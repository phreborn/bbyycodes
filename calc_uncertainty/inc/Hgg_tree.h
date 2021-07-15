//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Mar  8 16:50:04 2016 by ROOT version 5.34/32
// from TTree Hgg_tree/Hgg_tree
// found on file: root://eosatlas//eos/atlas/unpledged/group-wisc/xrootd/user/fwang/Hgg_output/AC_HighMass_ScalarIso_data12_8TeV_p1344/single_files/list_data12_8TeV.00216432.physics_Egamma.merge.NTUP_PHOTON.f507_m1271_p1341_p1344_p1345_tid01142798_00_0.root
//////////////////////////////////////////////////////////

#ifndef Hgg_tree_h
#define Hgg_tree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.
using namespace std;

class Hgg_tree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Char_t          SampleName;
   Int_t           LHCEnergy;
   Int_t           NEVENT;
   Double_t        NEVENT_weighted;
   Int_t           NEVENT_Dalitz;
   Double_t        NEVENT_Dalitz_weighted;
   Int_t           Run;
   Int_t           RandomRunNumber;
   Int_t           RandomLumiBlockNumber;
   Int_t           LB;
   Int_t           Event;
   Int_t           mcevt_pdf_id1;
   Int_t           mcevt_pdf_id2;
   Double_t        mcevt_pdf_x1;
   Double_t        mcevt_pdf_x2;
   Double_t        mcevt_pdf_scale;
   Double_t        mcevt_pdf1;
   Double_t        mcevt_pdf2;
   Int_t           NPV;
   Int_t           NPV_all;
   Int_t           Ntruthjets;
   Bool_t          TYPE_DATA;
   Int_t           MCtype;
   Float_t         AvgIntPerXing;
   Float_t         ActIntPerXing;
   Bool_t          flag_initial;
   Bool_t          flag_trigger;
   Bool_t          flag_GRL;
   Bool_t          flag_lar;
   Bool_t          flag_PV;
   Bool_t          flag_pre;
   Bool_t          flag_pre_graviton;
   Bool_t          flag_pt;
   Bool_t          flag_pt_graviton;
   Bool_t          flag_PID;
   Bool_t          flag_isEM;
   Bool_t          flag_NNPID;
   Bool_t          flag_iso;
   Bool_t          flag_iso_graviton;
   Bool_t          flag_iso_scalar;
   Bool_t          flag_mgg;
   Bool_t          flag_mgg_150;
   Bool_t          flag_BCHClean;
   Bool_t          flag_all;
   Bool_t          flag_noDalitz;
   Bool_t          flag_cleanMET;
   Bool_t          flag_DiEle;
   Bool_t          flag_DiMuo;
   Bool_t          flag_RelPt_35_25;
   Bool_t          flag_RelPt_40_30;
   Double_t        mass_jj;
   Double_t        mass_ggjj;
   Double_t        mass_ggj;
   Double_t        mass_uncorr;
   Double_t        mass_PV_EM;
   Double_t        mass_grav_corr;
   Double_t        PT;
   Double_t        Eta;
   Double_t        Phi;
   Double_t        phi_diff;
   Double_t        CosThetaStar;
   Double_t        costhetastar_CS;
   Double_t        pt_t;
   Double_t        pt_l;
   Double_t        eta_Zeppenfeld;
   Double_t        deltaRMinGJ;
   Double_t        deltaRMinGJ_for_BDT;
   Double_t        delta_eta_photons;
   Double_t        delta_phi_photons;
   vector<double>  *PV_z;
   Double_t        z_mc_truth_vertex;
   Double_t        zcommon;
   Double_t        zcommon_sumPt;
   Double_t        zcommon_Pointing;
   Double_t        zcommon_Likelihood;
   Int_t           index_PV_ID;
   Int_t           index_PV_ID_WithMoreThan2Tracks;
   Int_t           index_PV_ID_LH;
   Int_t           index_PV_ID_WithMoreThan2Tracks_LH;
   Int_t           index_PV_Likelihood;
   Double_t        MCweight;
   Double_t        PUweight;
   Double_t        ZVTXweight;
   Double_t        pT_weight;
   Double_t        pT_weightError;
   Double_t        interference_weight;
   Double_t        interference_weight_coupling;
   vector<double>  *interference_percentage;
   Double_t        interference_weight_CTS;
   Double_t        JHUPTweight;
   Double_t        selected_weight;
   Double_t        initial_weight;
   Double_t        mass_category_weight;
   Double_t        final_weight;
   vector<TString> *weight_graviton_labels;
   vector<double>  *weight_graviton_values;
   Double_t        Higgs_truth_pt;
   Int_t           Higgs_truth_mass;
   Int_t           Graviton_truth_mass;
   Double_t        Graviton_mc_mass;
   Double_t        xsection;
   Double_t        branching_ratio;
   Bool_t          is_gg_not_qq;
   Int_t           Nphotons;
   Int_t           ph_index_1st;
   Int_t           ph_index_2nd;
   Double_t        ph_pt_1st;
   Double_t        ph_pt_2nd;
   Double_t        ph_pt_corr_1st;
   Double_t        ph_pt_corr_2nd;
   Double_t        ph_E_1st;
   Double_t        ph_E_2nd;
   Double_t        ph_E_real_1st;
   Double_t        ph_E_real_2nd;
   Double_t        ph_Es_1st;
   Double_t        ph_Es_2nd;
   Double_t        ph_Ecorr_1st;
   Double_t        ph_Ecorr_2nd;
   Double_t        ph_eta_1st;
   Double_t        ph_eta_2nd;
   Double_t        ph_etas2_1st;
   Double_t        ph_etas2_2nd;
   Double_t        ph_etas1_1st;
   Double_t        ph_etas1_2nd;
   Double_t        ph_phi_1st;
   Double_t        ph_phi_2nd;
   Double_t        ph_SF_1st;
   Double_t        ph_SF_2nd;
   Double_t        ph_cl_pt_1st;
   Double_t        ph_cl_pt_2nd;
   Double_t        ph_cl_eta_1st;
   Double_t        ph_cl_eta_2nd;
   Double_t        ph_cl_phi_1st;
   Double_t        ph_cl_phi_2nd;
   Double_t        ph_cl_E_1st;
   Double_t        ph_cl_E_2nd;
   Bool_t          ph_convFlag_1st;
   Bool_t          ph_convFlag_2nd;
   Double_t        ph_conversion_radius_1st;
   Double_t        ph_conversion_radius_2nd;
   Int_t           ph_convBit_1st;
   Int_t           ph_convBit_2nd;
   Int_t           ph_isEM_1st;
   Int_t           ph_isEM_2nd;
   Int_t           ph_isEMtight_1st;
   Int_t           ph_isEMtight_2nd;
   Int_t           ph_LoosePrime_1st;
   Int_t           ph_LoosePrime_2nd;
   Bool_t          ph_isNN_1st;
   Bool_t          ph_isNN_2nd;
   Float_t         ph_NNresponse_1st;
   Float_t         ph_NNresponse_2nd;
   Float_t         ph_NNdiscrcut_1st;
   Float_t         ph_NNdiscrcut_2nd;
   Bool_t          ph_is_el_mediumPP_1st;
   Bool_t          ph_is_el_mediumPP_2nd;
   Bool_t          ph_is_el_LHloose_1st;
   Bool_t          ph_is_el_LHloose_2nd;
   Bool_t          ph_BL_1st;
   Bool_t          ph_BL_2nd;
   Bool_t          ph_expBL_1st;
   Bool_t          ph_expBL_2nd;
   Bool_t          ph_isIso_scalar_1st;
   Bool_t          ph_isIso_scalar_2nd;
   Double_t        ph_etcone40_ptcorr_1st;
   Double_t        ph_etcone40_ptcorr_2nd;
   Double_t        ph_etcone40_corr_1st;
   Double_t        ph_etcone40_corr_2nd;
   Double_t        ph_etcone40_PtED_corr_1st;
   Double_t        ph_etcone40_PtED_corr_2nd;
   Double_t        ph_etcone40_graviton_1st;
   Double_t        ph_etcone40_graviton_2nd;
   Double_t        ph_TopoEtcone40_1st;
   Double_t        ph_TopoEtcone40_2nd;
   Double_t        ph_TrackIso_corr_1st;
   Double_t        ph_TrackIso_corr_2nd;
   Double_t        ph_dr_1st;
   Double_t        ph_dr_2nd;
   Double_t        ph_rawcl_Es0_1st;
   Double_t        ph_rawcl_Es0_2nd;
   Double_t        ph_rawcl_Es1_1st;
   Double_t        ph_rawcl_Es1_2nd;
   Double_t        ph_rawcl_Es2_1st;
   Double_t        ph_rawcl_Es2_2nd;
   Double_t        ph_rawcl_Es3_1st;
   Double_t        ph_rawcl_Es3_2nd;
   Double_t        ph_cl_etaCalo_1st;
   Double_t        ph_cl_etaCalo_2nd;
   Double_t        ph_cl_phiCalo_1st;
   Double_t        ph_cl_phiCalo_2nd;
   Double_t        ph_ptconv_1st;
   Double_t        ph_ptconv_2nd;
   Int_t           ph_convtrk1nPixHits_1st;
   Int_t           ph_convtrk1nPixHits_2nd;
   Int_t           ph_convtrk1nSCTHits_1st;
   Int_t           ph_convtrk1nSCTHits_2nd;
   Int_t           ph_convtrk2nPixHits_1st;
   Int_t           ph_convtrk2nPixHits_2nd;
   Int_t           ph_convtrk2nSCTHits_1st;
   Int_t           ph_convtrk2nSCTHits_2nd;
   Double_t        ph_pt1conv_1st;
   Double_t        ph_pt1conv_2nd;
   Double_t        ph_pt2conv_1st;
   Double_t        ph_pt2conv_2nd;
   Int_t           ph_rawconvFlag_1st;
   Int_t           ph_rawconvFlag_2nd;
   Int_t           ph_truth_matched_1st;
   Int_t           ph_truth_matched_2nd;
   Int_t           ph_truth_isConv_1st;
   Int_t           ph_truth_isConv_2nd;
   Int_t           ph_truth_isBrem_1st;
   Int_t           ph_truth_isBrem_2nd;
   Int_t           ph_truth_isPhotonFromHardProc_1st;
   Int_t           ph_truth_isPhotonFromHardProc_2nd;
   Int_t           ph_truth_mothertype_1st;
   Int_t           ph_truth_mothertype_2nd;
   Int_t           ph_truth_type_1st;
   Int_t           ph_truth_type_2nd;
   Double_t        ph_truth_pt_1st;
   Double_t        ph_truth_pt_2nd;
   Double_t        ph_truth_eta_1st;
   Double_t        ph_truth_eta_2nd;
   Double_t        ph_truth_phi_1st;
   Double_t        ph_truth_phi_2nd;
   Double_t        ph_truth_E_1st;
   Double_t        ph_truth_E_2nd;
   Double_t        diphoton_truth_pt;
   Double_t        diphoton_truth_eta;
   Double_t        diphoton_truth_phi;
   Double_t        diphoton_truth_E;
   Double_t        diphoton_truth_costhetastar_CS;
   Double_t        diphoton_truth_mass;
   Double_t        mcdiphoton_truth_mass;
   Double_t        mcph_truth_pt_1st;
   Double_t        mcph_truth_pt_2nd;
   Double_t        mcph_truth_eta_1st;
   Double_t        mcph_truth_eta_2nd;
   Double_t        mcph_truth_phi_1st;
   Double_t        mcph_truth_phi_2nd;
   Double_t        mcph_truth_etcone40_EDcorr_1st;
   Double_t        mcph_truth_etcone40_EDcorr_2nd;
   Int_t           Nelectrons;
   vector<double>  *el_truth_pt;
   vector<double>  *el_truth_eta;
   vector<double>  *el_truth_phi;
   vector<double>  *el_truth_E;
   vector<int>     *el_truth_matched;
   vector<int>     *el_truth_type;
   vector<int>     *el_truth_mothertype;
   Double_t        event_el_SF;
   Int_t           el_index_leading;
   Int_t           el_index_subleading;
   vector<double>  *el_pt;
   vector<double>  *el_trk_eta;
   vector<double>  *el_trk_phi;
   vector<double>  *el_E;
   vector<double>  *el_cl_pt;
   vector<double>  *el_cl_eta;
   vector<double>  *el_cl_phi;
   vector<double>  *el_cl_E;
   vector<int>     *el_index;
   vector<double>  *el_ptcone20;
   vector<double>  *el_etcone40;
   vector<double>  *el_TopoETcone40;
   vector<bool>    *el_isLoosePP;
   vector<bool>    *el_isMediumPP;
   vector<bool>    *el_isTightPP;
   vector<bool>    *el_isLHLoose;
   vector<int>     *el_charge;
   vector<double>  *el_SF;
   Int_t           Nmuons;
   vector<double>  *mu_truth_pt;
   vector<double>  *mu_truth_eta;
   vector<double>  *mu_truth_phi;
   vector<int>     *mu_truth_matched;
   vector<int>     *mu_truth_type;
   vector<int>     *mu_truth_mothertype;
   Double_t        event_mu_SF;
   Int_t           mu_index_leading;
   Int_t           mu_index_subleading;
   vector<double>  *mu_pt;
   vector<double>  *mu_eta;
   vector<double>  *mu_phi;
   vector<int>     *mu_index;
   vector<double>  *mu_ptcone20;
   vector<double>  *mu_etcone40;
   vector<bool>    *mu_isLoose;
   vector<bool>    *mu_isMedium;
   vector<bool>    *mu_isTight;
   vector<int>     *mu_charge;
   vector<double>  *mu_SF;
   Int_t           Njets;
   Int_t           Njets_NoEtaCut;
   Int_t           nb_jets_30G;
   Int_t           nb_jets_25G;
   Int_t           nb_jetsB_30G_60;
   Int_t           nb_jetsB_30G_70;
   Int_t           nb_jetsB_30G_80;
   Int_t           nb_jetsB_25G_80;
   Int_t           nb_jetsB_25G_85;
   Int_t           nb_jets_25GeV_passingBCH;
   Int_t           nb_jets_30GeV_passingBCH;
   Int_t           nb_jetsB_25GeV_80_passingBCH;
   Int_t           nb_jetsB_30GeV_70_passingBCH;
   Int_t           nb_jetsB_30GeV_60_passingBCH;
   Double_t        weight_jets;
   Int_t           jet_index_1st;
   Int_t           jet_index_2nd;
   Double_t        jet_pt_1st;
   Double_t        jet_pt_2nd;
   Double_t        jet_eta_1st;
   Double_t        jet_eta_2nd;
   Double_t        jet_phi_1st;
   Double_t        jet_phi_2nd;
   Double_t        jet_E_1st;
   Double_t        jet_E_2nd;
   Double_t        delta_eta_jet;
   Double_t        eta1_eta2;
   Double_t        phi_jj;
   Double_t        jet_jvtxf_1st;
   Double_t        jet_jvtxf_2nd;
   Double_t        jet_mv1_1st;
   Double_t        jet_mv1_2nd;
   Double_t        jet_mv1c_1st;
   Double_t        jet_mv1c_2nd;
   Double_t        jet_badBCH_1st;
   Double_t        jet_badBCH_2nd;
   vector<double>  *jet_pt;
   vector<double>  *jet_E;
   vector<double>  *jet_eta;
   vector<double>  *jet_eta_emscale;
   vector<double>  *jet_phi;
   vector<double>  *jet_jvf;
   vector<double>  *jet_mv1;
   vector<double>  *jet_mv1c;
   vector<bool>    *jet_badBCH;
   vector<int>     *jet_flavor_truth_label;
   vector<int>     *jet_index;
   vector<double>  *jet_el_dr;
   vector<int>     *jet_el_matched;
   vector<double>  *jet_mu_dr;
   vector<int>     *jet_mu_matched;
   vector<bool>    *jet_MatchedToPhoton;
   vector<double>  *jet_truth_pt;
   vector<double>  *jet_truth_eta;
   vector<double>  *jet_truth_phi;
   vector<double>  *jet_truth_E;
   Double_t        flag_METBadDueToBCH;
   Double_t        MET_Truth_NonInt_etx;
   Double_t        MET_Truth_NonInt_ety;
   Double_t        MET_Truth_NonInt_phi;
   Double_t        MET_Truth_NonInt_et;
   Double_t        MET_Truth_NonInt_sumet;
   Double_t        MET_PhotonTight_Calib_OR_stdvert_RefFinal_etx;
   Double_t        MET_PhotonTight_Calib_OR_stdvert_RefFinal_ety;
   Double_t        MET_PhotonTight_Calib_OR_stdvert_RefFinal_phi;
   Double_t        MET_PhotonTight_Calib_OR_stdvert_RefFinal_et;
   Double_t        MET_PhotonTight_Calib_OR_stdvert_RefFinal_sumet;
   Double_t        MET_PhotonTight_Calib_OR_stdvert_RefFinal_STVF_etx;
   Double_t        MET_PhotonTight_Calib_OR_stdvert_RefFinal_STVF_ety;
   Double_t        MET_PhotonTight_Calib_OR_stdvert_RefFinal_STVF_phi;
   Double_t        MET_PhotonTight_Calib_OR_stdvert_RefFinal_STVF_et;
   Double_t        MET_PhotonTight_Calib_OR_stdvert_RefFinal_STVF_sumet;
   Double_t        MET_PhotonTight_Calib_OR_stdvert_Muon_Total_Staco_etx;
   Double_t        MET_PhotonTight_Calib_OR_stdvert_Muon_Total_Staco_ety;
   Double_t        MET_PhotonTight_Calib_OR_stdvert_Muon_Total_Staco_phi;
   Double_t        MET_PhotonTight_Calib_OR_stdvert_Muon_Total_Staco_et;
   Double_t        MET_PhotonTight_Calib_OR_stdvert_Muon_Total_Staco_sumet;
   Double_t        MET_PhotonTight_Calib_OR_stdvert_significance;
   Double_t        MET_PhotonTight_Corrected_RefFinal_etx;
   Double_t        MET_PhotonTight_Corrected_RefFinal_ety;
   Double_t        MET_PhotonTight_Corrected_RefMuon_etx;
   Double_t        MET_PhotonTight_Corrected_RefMuon_ety;
   Double_t        MET_NNTight_Calib_OR_stdvert_RefFinal_etx;
   Double_t        MET_NNTight_Calib_OR_stdvert_RefFinal_ety;
   Double_t        MET_NNTight_Calib_OR_stdvert_RefFinal_phi;
   Double_t        MET_NNTight_Calib_OR_stdvert_RefFinal_et;
   Double_t        MET_NNTight_Calib_OR_stdvert_RefFinal_sumet;
   Double_t        MET_NNTight_Calib_OR_stdvert_RefFinal_STVF_etx;
   Double_t        MET_NNTight_Calib_OR_stdvert_RefFinal_STVF_ety;
   Double_t        MET_NNTight_Calib_OR_stdvert_RefFinal_STVF_phi;
   Double_t        MET_NNTight_Calib_OR_stdvert_RefFinal_STVF_et;
   Double_t        MET_NNTight_Calib_OR_stdvert_RefFinal_STVF_sumet;
   Double_t        MET_NNTight_Calib_OR_stdvert_Muon_Total_Staco_etx;
   Double_t        MET_NNTight_Calib_OR_stdvert_Muon_Total_Staco_ety;
   Double_t        MET_NNTight_Calib_OR_stdvert_Muon_Total_Staco_phi;
   Double_t        MET_NNTight_Calib_OR_stdvert_Muon_Total_Staco_et;
   Double_t        MET_NNTight_Calib_OR_stdvert_Muon_Total_Staco_sumet;
   Double_t        MET_NNTight_Calib_OR_stdvert_significance;
   Double_t        MT_muMET;
   Double_t        MT_elMET;
   Double_t        DPhi_ggMET_NNTight_RefFinal;
   Double_t        DPhi_ggMET_PhotonTight_RefFinal;
   Double_t        MET_NNTight_Calib_OR_RefFinal_et;
   Int_t           EPScategory;
   Int_t           PTTcategory;
   Int_t           JETPTTcategory;
   Int_t           GBJcategory;
   Int_t           HighPttEtaConvVBFcategory;
   Int_t           HighPttGoodBadVBFcategory;
   Int_t           Conversioncategory;
   Int_t           PaperPttEtacategory;
   Int_t           VH_HCPcategory;
   Int_t           category_MoriondCut;
   Int_t           category_MoriondMVA;
   Int_t           category_PaperMass;
   Int_t           category_PaperCoupling;
   Bool_t          cat_vh_lepton;
   Bool_t          cat_vh_dijet;
   Bool_t          cat_vh_MET;
   Bool_t          cat_vh_dilepton;
   Bool_t          cat_vbf_mva1;
   Bool_t          cat_vbf_mva2;
   Bool_t          cat_vbf_cut1;
   Bool_t          cat_vbf_cut2;
   Bool_t          cat_ttH_had;
   Bool_t          cat_ttH_lep;
   Bool_t          moriond_cat_vbf_mva1;
   Bool_t          moriond_cat_vbf_mva2;
   Bool_t          cat_ptt;
   Double_t        cat_vbf_bdt_response;
   Double_t        mass_egamma_ClosestToZ;
   Bool_t          Zveto;
   Bool_t          Zveto_TTH;

   // List of branches
   TBranch        *b_SampleName;   //!
   TBranch        *b_LHCEnergy;   //!
   TBranch        *b_NEVENT;   //!
   TBranch        *b_NEVENT_weighted;   //!
   TBranch        *b_NEVENT_Dalitz;   //!
   TBranch        *b_NEVENT_Dalitz_weighted;   //!
   TBranch        *b_Run;   //!
   TBranch        *b_RandomRunNumber;   //!
   TBranch        *b_RandomLumiBlockNumber;   //!
   TBranch        *b_LB;   //!
   TBranch        *b_Event;   //!
   TBranch        *b_mcevt_pdf_id1;   //!
   TBranch        *b_mcevt_pdf_id2;   //!
   TBranch        *b_mcevt_pdf_x1;   //!
   TBranch        *b_mcevt_pdf_x2;   //!
   TBranch        *b_mcevt_pdf_scale;   //!
   TBranch        *b_mcevt_pdf1;   //!
   TBranch        *b_mcevt_pdf2;   //!
   TBranch        *b_NPV;   //!
   TBranch        *b_NPV_all;   //!
   TBranch        *b_Ntruthjets;   //!
   TBranch        *b_TYPE_DATA;   //!
   TBranch        *b_MCtype;   //!
   TBranch        *b_AvgIntPerXing;   //!
   TBranch        *b_ActIntPerXing;   //!
   TBranch        *b_flag_initial;   //!
   TBranch        *b_flag_trigger;   //!
   TBranch        *b_flag_GRL;   //!
   TBranch        *b_flag_lar;   //!
   TBranch        *b_flag_PV;   //!
   TBranch        *b_flag_pre;   //!
   TBranch        *b_flag_pre_graviton;   //!
   TBranch        *b_flag_pt;   //!
   TBranch        *b_flag_pt_graviton;   //!
   TBranch        *b_flag_PID;   //!
   TBranch        *b_flag_isEM;   //!
   TBranch        *b_flag_NNPID;   //!
   TBranch        *b_flag_iso;   //!
   TBranch        *b_flag_iso_graviton;   //!
   TBranch        *b_flag_iso_scalar;   //!
   TBranch        *b_flag_mgg;   //!
   TBranch        *b_flag_mgg_150;   //!
   TBranch        *b_flag_BCHClean;   //!
   TBranch        *b_flag_all;   //!
   TBranch        *b_flag_noDalitz;   //!
   TBranch        *b_flag_cleanMET;   //!
   TBranch        *b_flag_DiEle;   //!
   TBranch        *b_flag_DiMuo;   //!
   TBranch        *b_flag_RelPt_35_25;   //!
   TBranch        *b_flag_RelPt_40_30;   //!
   TBranch        *b_mass_jj;   //!
   TBranch        *b_mass_ggjj;   //!
   TBranch        *b_mass_ggj;   //!
   TBranch        *b_mass_uncorr;   //!
   TBranch        *b_mass_PV_EM;   //!
   TBranch        *b_mass_grav_corr;   //!
   TBranch        *b_PT;   //!
   TBranch        *b_Eta;   //!
   TBranch        *b_Phi;   //!
   TBranch        *b_phi_diff;   //!
   TBranch        *b_CosThetaStar;   //!
   TBranch        *b_costhetastar_CS;   //!
   TBranch        *b_pt_t;   //!
   TBranch        *b_pt_l;   //!
   TBranch        *b_eta_Zeppenfeld;   //!
   TBranch        *b_deltaRMinGJ;   //!
   TBranch        *b_deltaRMinGJ_for_BDT;   //!
   TBranch        *b_delta_eta_photons;   //!
   TBranch        *b_delta_phi_photons;   //!
   TBranch        *b_PV_z;   //!
   TBranch        *b_z_mc_truth_vertex;   //!
   TBranch        *b_zcommon;   //!
   TBranch        *b_zcommon_sumPt;   //!
   TBranch        *b_zcommon_Pointing;   //!
   TBranch        *b_zcommon_Likelihood;   //!
   TBranch        *b_index_PV_ID;   //!
   TBranch        *b_index_PV_ID_WithMoreThan2Tracks;   //!
   TBranch        *b_index_PV_ID_LH;   //!
   TBranch        *b_index_PV_ID_WithMoreThan2Tracks_LH;   //!
   TBranch        *b_index_PV_Likelihood;   //!
   TBranch        *b_MCweight;   //!
   TBranch        *b_PUweight;   //!
   TBranch        *b_ZVTXweight;   //!
   TBranch        *b_pT_weight;   //!
   TBranch        *b_pT_weightError;   //!
   TBranch        *b_interference_weight;   //!
   TBranch        *b_interference_weight_coupling;   //!
   TBranch        *b_interference_percentage;   //!
   TBranch        *b_interference_weight_CTS;   //!
   TBranch        *b_JHUPTweight;   //!
   TBranch        *b_selected_weight;   //!
   TBranch        *b_initial_weight;   //!
   TBranch        *b_mass_category_weight;   //!
   TBranch        *b_final_weight;   //!
   TBranch        *b_weight_graviton_labels;   //!
   TBranch        *b_weight_graviton_values;   //!
   TBranch        *b_Higgs_truth_pt;   //!
   TBranch        *b_Higgs_truth_mass;   //!
   TBranch        *b_Graviton_truth_mass;   //!
   TBranch        *b_Graviton_mc_mass;   //!
   TBranch        *b_xsection;   //!
   TBranch        *b_branching_ratio;   //!
   TBranch        *b_is_gg_not_qq;   //!
   TBranch        *b_Nphotons;   //!
   TBranch        *b_ph_index_1st;   //!
   TBranch        *b_ph_index_2nd;   //!
   TBranch        *b_ph_pt_1st;   //!
   TBranch        *b_ph_pt_2nd;   //!
   TBranch        *b_ph_pt_corr_1st;   //!
   TBranch        *b_ph_pt_corr_2nd;   //!
   TBranch        *b_ph_E_1st;   //!
   TBranch        *b_ph_E_2nd;   //!
   TBranch        *b_ph_E_real_1st;   //!
   TBranch        *b_ph_E_real_2nd;   //!
   TBranch        *b_ph_Es_1st;   //!
   TBranch        *b_ph_Es_2nd;   //!
   TBranch        *b_ph_Ecorr_1st;   //!
   TBranch        *b_ph_Ecorr_2nd;   //!
   TBranch        *b_ph_eta_1st;   //!
   TBranch        *b_ph_eta_2nd;   //!
   TBranch        *b_ph_etas2_1st;   //!
   TBranch        *b_ph_etas2_2nd;   //!
   TBranch        *b_ph_etas1_1st;   //!
   TBranch        *b_ph_etas1_2nd;   //!
   TBranch        *b_ph_phi_1st;   //!
   TBranch        *b_ph_phi_2nd;   //!
   TBranch        *b_ph_SF_1st;   //!
   TBranch        *b_ph_SF_2nd;   //!
   TBranch        *b_ph_cl_pt_1st;   //!
   TBranch        *b_ph_cl_pt_2nd;   //!
   TBranch        *b_ph_cl_eta_1st;   //!
   TBranch        *b_ph_cl_eta_2nd;   //!
   TBranch        *b_ph_cl_phi_1st;   //!
   TBranch        *b_ph_cl_phi_2nd;   //!
   TBranch        *b_ph_cl_E_1st;   //!
   TBranch        *b_ph_cl_E_2nd;   //!
   TBranch        *b_ph_convFlag_1st;   //!
   TBranch        *b_ph_convFlag_2nd;   //!
   TBranch        *b_ph_conversion_radius_1st;   //!
   TBranch        *b_ph_conversion_radius_2nd;   //!
   TBranch        *b_ph_convBit_1st;   //!
   TBranch        *b_ph_convBit_2nd;   //!
   TBranch        *b_ph_isEM_1st;   //!
   TBranch        *b_ph_isEM_2nd;   //!
   TBranch        *b_ph_isEMtight_1st;   //!
   TBranch        *b_ph_isEMtight_2nd;   //!
   TBranch        *b_ph_LoosePrime_1st;   //!
   TBranch        *b_ph_LoosePrime_2nd;   //!
   TBranch        *b_ph_isNN_1st;   //!
   TBranch        *b_ph_isNN_2nd;   //!
   TBranch        *b_ph_NNresponse_1st;   //!
   TBranch        *b_ph_NNresponse_2nd;   //!
   TBranch        *b_ph_NNdiscrcut_1st;   //!
   TBranch        *b_ph_NNdiscrcut_2nd;   //!
   TBranch        *b_ph_is_el_mediumPP_1st;   //!
   TBranch        *b_ph_is_el_mediumPP_2nd;   //!
   TBranch        *b_ph_is_el_LHloose_1st;   //!
   TBranch        *b_ph_is_el_LHloose_2nd;   //!
   TBranch        *b_ph_BL_1st;   //!
   TBranch        *b_ph_BL_2nd;   //!
   TBranch        *b_ph_expBL_1st;   //!
   TBranch        *b_ph_expBL_2nd;   //!
   TBranch        *b_ph_isIso_scalar_1st;   //!
   TBranch        *b_ph_isIso_scalar_2nd;   //!
   TBranch        *b_ph_etcone40_ptcorr_1st;   //!
   TBranch        *b_ph_etcone40_ptcorr_2nd;   //!
   TBranch        *b_ph_etcone40_corr_1st;   //!
   TBranch        *b_ph_etcone40_corr_2nd;   //!
   TBranch        *b_ph_etcone40_PtED_corr_1st;   //!
   TBranch        *b_ph_etcone40_PtED_corr_2nd;   //!
   TBranch        *b_ph_etcone40_graviton_1st;   //!
   TBranch        *b_ph_etcone40_graviton_2nd;   //!
   TBranch        *b_ph_TopoEtcone40_1st;   //!
   TBranch        *b_ph_TopoEtcone40_2nd;   //!
   TBranch        *b_ph_TrackIso_corr_1st;   //!
   TBranch        *b_ph_TrackIso_corr_2nd;   //!
   TBranch        *b_ph_dr_1st;   //!
   TBranch        *b_ph_dr_2nd;   //!
   TBranch        *b_ph_rawcl_Es0_1st;   //!
   TBranch        *b_ph_rawcl_Es0_2nd;   //!
   TBranch        *b_ph_rawcl_Es1_1st;   //!
   TBranch        *b_ph_rawcl_Es1_2nd;   //!
   TBranch        *b_ph_rawcl_Es2_1st;   //!
   TBranch        *b_ph_rawcl_Es2_2nd;   //!
   TBranch        *b_ph_rawcl_Es3_1st;   //!
   TBranch        *b_ph_rawcl_Es3_2nd;   //!
   TBranch        *b_ph_cl_etaCalo_1st;   //!
   TBranch        *b_ph_cl_etaCalo_2nd;   //!
   TBranch        *b_ph_cl_phiCalo_1st;   //!
   TBranch        *b_ph_cl_phiCalo_2nd;   //!
   TBranch        *b_ph_ptconv_1st;   //!
   TBranch        *b_ph_ptconv_2nd;   //!
   TBranch        *b_ph_convtrk1nPixHits_1st;   //!
   TBranch        *b_ph_convtrk1nPixHits_2nd;   //!
   TBranch        *b_ph_convtrk1nSCTHits_1st;   //!
   TBranch        *b_ph_convtrk1nSCTHits_2nd;   //!
   TBranch        *b_ph_convtrk2nPixHits_1st;   //!
   TBranch        *b_ph_convtrk2nPixHits_2nd;   //!
   TBranch        *b_ph_convtrk2nSCTHits_1st;   //!
   TBranch        *b_ph_convtrk2nSCTHits_2nd;   //!
   TBranch        *b_ph_pt1conv_1st;   //!
   TBranch        *b_ph_pt1conv_2nd;   //!
   TBranch        *b_ph_pt2conv_1st;   //!
   TBranch        *b_ph_pt2conv_2nd;   //!
   TBranch        *b_ph_rawconvFlag_1st;   //!
   TBranch        *b_ph_rawconvFlag_2nd;   //!
   TBranch        *b_ph_truth_matched_1st;   //!
   TBranch        *b_ph_truth_matched_2nd;   //!
   TBranch        *b_ph_truth_isConv_1st;   //!
   TBranch        *b_ph_truth_isConv_2nd;   //!
   TBranch        *b_ph_truth_isBrem_1st;   //!
   TBranch        *b_ph_truth_isBrem_2nd;   //!
   TBranch        *b_ph_truth_isPhotonFromHardProc_1st;   //!
   TBranch        *b_ph_truth_isPhotonFromHardProc_2nd;   //!
   TBranch        *b_ph_truth_mothertype_1st;   //!
   TBranch        *b_ph_truth_mothertype_2nd;   //!
   TBranch        *b_ph_truth_type_1st;   //!
   TBranch        *b_ph_truth_type_2nd;   //!
   TBranch        *b_ph_truth_pt_1st;   //!
   TBranch        *b_ph_truth_pt_2nd;   //!
   TBranch        *b_ph_truth_eta_1st;   //!
   TBranch        *b_ph_truth_eta_2nd;   //!
   TBranch        *b_ph_truth_phi_1st;   //!
   TBranch        *b_ph_truth_phi_2nd;   //!
   TBranch        *b_ph_truth_E_1st;   //!
   TBranch        *b_ph_truth_E_2nd;   //!
   TBranch        *b_diphoton_truth_pt;   //!
   TBranch        *b_diphoton_truth_eta;   //!
   TBranch        *b_diphoton_truth_phi;   //!
   TBranch        *b_diphoton_truth_E;   //!
   TBranch        *b_diphoton_truth_costhetastar_CS;   //!
   TBranch        *b_diphoton_truth_mass;   //!
   TBranch        *b_mcdiphoton_truth_mass;   //!
   TBranch        *b_mcph_truth_pt_1st;   //!
   TBranch        *b_mcph_truth_pt_2nd;   //!
   TBranch        *b_mcph_truth_eta_1st;   //!
   TBranch        *b_mcph_truth_eta_2nd;   //!
   TBranch        *b_mcph_truth_phi_1st;   //!
   TBranch        *b_mcph_truth_phi_2nd;   //!
   TBranch        *b_mcph_truth_etcone40_EDcorr_1st;   //!
   TBranch        *b_mcph_truth_etcone40_EDcorr_2nd;   //!
   TBranch        *b_Nelectrons;   //!
   TBranch        *b_el_truth_pt;   //!
   TBranch        *b_el_truth_eta;   //!
   TBranch        *b_el_truth_phi;   //!
   TBranch        *b_el_truth_E;   //!
   TBranch        *b_el_truth_matched;   //!
   TBranch        *b_el_truth_type;   //!
   TBranch        *b_el_truth_mothertype;   //!
   TBranch        *b_event_el_SF;   //!
   TBranch        *b_el_index_leading;   //!
   TBranch        *b_el_index_subleading;   //!
   TBranch        *b_el_pt;   //!
   TBranch        *b_el_trk_eta;   //!
   TBranch        *b_el_trk_phi;   //!
   TBranch        *b_el_E;   //!
   TBranch        *b_el_cl_pt;   //!
   TBranch        *b_el_cl_eta;   //!
   TBranch        *b_el_cl_phi;   //!
   TBranch        *b_el_cl_E;   //!
   TBranch        *b_el_index;   //!
   TBranch        *b_el_ptcone20;   //!
   TBranch        *b_el_etcone40;   //!
   TBranch        *b_el_TopoETcone40;   //!
   TBranch        *b_el_isLoosePP;   //!
   TBranch        *b_el_isMediumPP;   //!
   TBranch        *b_el_isTightPP;   //!
   TBranch        *b_el_isLHLoose;   //!
   TBranch        *b_el_charge;   //!
   TBranch        *b_el_SF;   //!
   TBranch        *b_Nmuons;   //!
   TBranch        *b_mu_truth_pt;   //!
   TBranch        *b_mu_truth_eta;   //!
   TBranch        *b_mu_truth_phi;   //!
   TBranch        *b_mu_truth_matched;   //!
   TBranch        *b_mu_truth_type;   //!
   TBranch        *b_mu_truth_mothertype;   //!
   TBranch        *b_event_mu_SF;   //!
   TBranch        *b_mu_index_leading;   //!
   TBranch        *b_mu_index_subleading;   //!
   TBranch        *b_mu_pt;   //!
   TBranch        *b_mu_eta;   //!
   TBranch        *b_mu_phi;   //!
   TBranch        *b_mu_index;   //!
   TBranch        *b_mu_ptcone20;   //!
   TBranch        *b_mu_etcone40;   //!
   TBranch        *b_mu_isLoose;   //!
   TBranch        *b_mu_isMedium;   //!
   TBranch        *b_mu_isTight;   //!
   TBranch        *b_mu_charge;   //!
   TBranch        *b_mu_SF;   //!
   TBranch        *b_Njets;   //!
   TBranch        *b_Njets_NoEtaCut;   //!
   TBranch        *b_nb_jets_30G;   //!
   TBranch        *b_nb_jets_25G;   //!
   TBranch        *b_nb_jetsB_30G_60;   //!
   TBranch        *b_nb_jetsB_30G_70;   //!
   TBranch        *b_nb_jetsB_30G_80;   //!
   TBranch        *b_nb_jetsB_25G_80;   //!
   TBranch        *b_nb_jetsB_25G_85;   //!
   TBranch        *b_nb_jets_25GeV_passingBCH;   //!
   TBranch        *b_nb_jets_30GeV_passingBCH;   //!
   TBranch        *b_nb_jetsB_25GeV_80_passingBCH;   //!
   TBranch        *b_nb_jetsB_30GeV_70_passingBCH;   //!
   TBranch        *b_nb_jetsB_30GeV_60_passingBCH;   //!
   TBranch        *b_weight_jets;   //!
   TBranch        *b_jet_index_1st;   //!
   TBranch        *b_jet_index_2nd;   //!
   TBranch        *b_jet_pt_1st;   //!
   TBranch        *b_jet_pt_2nd;   //!
   TBranch        *b_jet_eta_1st;   //!
   TBranch        *b_jet_eta_2nd;   //!
   TBranch        *b_jet_phi_1st;   //!
   TBranch        *b_jet_phi_2nd;   //!
   TBranch        *b_jet_E_1st;   //!
   TBranch        *b_jet_E_2nd;   //!
   TBranch        *b_delta_eta_jet;   //!
   TBranch        *b_eta1_eta2;   //!
   TBranch        *b_phi_jj;   //!
   TBranch        *b_jet_jvtxf_1st;   //!
   TBranch        *b_jet_jvtxf_2nd;   //!
   TBranch        *b_jet_mv1_1st;   //!
   TBranch        *b_jet_mv1_2nd;   //!
   TBranch        *b_jet_mv1c_1st;   //!
   TBranch        *b_jet_mv1c_2nd;   //!
   TBranch        *b_jet_badBCH_1st;   //!
   TBranch        *b_jet_badBCH_2nd;   //!
   TBranch        *b_jet_pt;   //!
   TBranch        *b_jet_E;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_jet_eta_emscale;   //!
   TBranch        *b_jet_phi;   //!
   TBranch        *b_jet_jvf;   //!
   TBranch        *b_jet_mv1;   //!
   TBranch        *b_jet_mv1c;   //!
   TBranch        *b_jet_badBCH;   //!
   TBranch        *b_jet_flavor_truth_label;   //!
   TBranch        *b_jet_index;   //!
   TBranch        *b_jet_el_dr;   //!
   TBranch        *b_jet_el_matched;   //!
   TBranch        *b_jet_mu_dr;   //!
   TBranch        *b_jet_mu_matched;   //!
   TBranch        *b_jet_MatchedToPhoton;   //!
   TBranch        *b_jet_truth_pt;   //!
   TBranch        *b_jet_truth_eta;   //!
   TBranch        *b_jet_truth_phi;   //!
   TBranch        *b_jet_truth_E;   //!
   TBranch        *b_flag_METBadDueToBCH;   //!
   TBranch        *b_MET_Truth_NonInt_etx;   //!
   TBranch        *b_MET_Truth_NonInt_ety;   //!
   TBranch        *b_MET_Truth_NonInt_phi;   //!
   TBranch        *b_MET_Truth_NonInt_et;   //!
   TBranch        *b_MET_Truth_NonInt_sumet;   //!
   TBranch        *b_MET_PhotonTight_Calib_OR_stdvert_RefFinal_etx;   //!
   TBranch        *b_MET_PhotonTight_Calib_OR_stdvert_RefFinal_ety;   //!
   TBranch        *b_MET_PhotonTight_Calib_OR_stdvert_RefFinal_phi;   //!
   TBranch        *b_MET_PhotonTight_Calib_OR_stdvert_RefFinal_et;   //!
   TBranch        *b_MET_PhotonTight_Calib_OR_stdvert_RefFinal_sumet;   //!
   TBranch        *b_MET_PhotonTight_Calib_OR_stdvert_RefFinal_STVF_etx;   //!
   TBranch        *b_MET_PhotonTight_Calib_OR_stdvert_RefFinal_STVF_ety;   //!
   TBranch        *b_MET_PhotonTight_Calib_OR_stdvert_RefFinal_STVF_phi;   //!
   TBranch        *b_MET_PhotonTight_Calib_OR_stdvert_RefFinal_STVF_et;   //!
   TBranch        *b_MET_PhotonTight_Calib_OR_stdvert_RefFinal_STVF_sumet;   //!
   TBranch        *b_MET_PhotonTight_Calib_OR_stdvert_Muon_Total_Staco_etx;   //!
   TBranch        *b_MET_PhotonTight_Calib_OR_stdvert_Muon_Total_Staco_ety;   //!
   TBranch        *b_MET_PhotonTight_Calib_OR_stdvert_Muon_Total_Staco_phi;   //!
   TBranch        *b_MET_PhotonTight_Calib_OR_stdvert_Muon_Total_Staco_et;   //!
   TBranch        *b_MET_PhotonTight_Calib_OR_stdvert_Muon_Total_Staco_sumet;   //!
   TBranch        *b_MET_PhotonTight_Calib_OR_stdvert_significance;   //!
   TBranch        *b_MET_PhotonTight_Corrected_RefFinal_etx;   //!
   TBranch        *b_MET_PhotonTight_Corrected_RefFinal_ety;   //!
   TBranch        *b_MET_PhotonTight_Corrected_RefMuon_etx;   //!
   TBranch        *b_MET_PhotonTight_Corrected_RefMuon_ety;   //!
   TBranch        *b_MET_NNTight_Calib_OR_stdvert_RefFinal_etx;   //!
   TBranch        *b_MET_NNTight_Calib_OR_stdvert_RefFinal_ety;   //!
   TBranch        *b_MET_NNTight_Calib_OR_stdvert_RefFinal_phi;   //!
   TBranch        *b_MET_NNTight_Calib_OR_stdvert_RefFinal_et;   //!
   TBranch        *b_MET_NNTight_Calib_OR_stdvert_RefFinal_sumet;   //!
   TBranch        *b_MET_NNTight_Calib_OR_stdvert_RefFinal_STVF_etx;   //!
   TBranch        *b_MET_NNTight_Calib_OR_stdvert_RefFinal_STVF_ety;   //!
   TBranch        *b_MET_NNTight_Calib_OR_stdvert_RefFinal_STVF_phi;   //!
   TBranch        *b_MET_NNTight_Calib_OR_stdvert_RefFinal_STVF_et;   //!
   TBranch        *b_MET_NNTight_Calib_OR_stdvert_RefFinal_STVF_sumet;   //!
   TBranch        *b_MET_NNTight_Calib_OR_stdvert_Muon_Total_Staco_etx;   //!
   TBranch        *b_MET_NNTight_Calib_OR_stdvert_Muon_Total_Staco_ety;   //!
   TBranch        *b_MET_NNTight_Calib_OR_stdvert_Muon_Total_Staco_phi;   //!
   TBranch        *b_MET_NNTight_Calib_OR_stdvert_Muon_Total_Staco_et;   //!
   TBranch        *b_MET_NNTight_Calib_OR_stdvert_Muon_Total_Staco_sumet;   //!
   TBranch        *b_MET_NNTight_Calib_OR_stdvert_significance;   //!
   TBranch        *b_MT_muMET;   //!
   TBranch        *b_MT_elMET;   //!
   TBranch        *b_DPhi_ggMET_NNTight_RefFinal;   //!
   TBranch        *b_DPhi_ggMET_PhotonTight_RefFinal;   //!
   TBranch        *b_MET_NNTight_Calib_OR_RefFinal_et;   //!
   TBranch        *b_EPScategory;   //!
   TBranch        *b_PTTcategory;   //!
   TBranch        *b_JETPTTcategory;   //!
   TBranch        *b_GBJcategory;   //!
   TBranch        *b_HighPttEtaConvVBFcategory;   //!
   TBranch        *b_HighPttGoodBadVBFcategory;   //!
   TBranch        *b_Conversioncategory;   //!
   TBranch        *b_PaperPttEtacategory;   //!
   TBranch        *b_VH_HCPcategory;   //!
   TBranch        *b_category_MoriondCut;   //!
   TBranch        *b_category_MoriondMVA;   //!
   TBranch        *b_category_PaperMass;   //!
   TBranch        *b_category_PaperCoupling;   //!
   TBranch        *b_cat_vh_lepton;   //!
   TBranch        *b_cat_vh_dijet;   //!
   TBranch        *b_cat_vh_MET;   //!
   TBranch        *b_cat_vh_dilepton;   //!
   TBranch        *b_cat_vbf_mva1;   //!
   TBranch        *b_cat_vbf_mva2;   //!
   TBranch        *b_cat_vbf_cut1;   //!
   TBranch        *b_cat_vbf_cut2;   //!
   TBranch        *b_cat_ttH_had;   //!
   TBranch        *b_cat_ttH_lep;   //!
   TBranch        *b_moriond_cat_vbf_mva1;   //!
   TBranch        *b_moriond_cat_vbf_mva2;   //!
   TBranch        *b_cat_ptt;   //!
   TBranch        *b_cat_vbf_bdt_response;   //!
   TBranch        *b_mass_egamma_ClosestToZ;   //!
   TBranch        *b_Zveto;   //!
   TBranch        *b_Zveto_TTH;   //!

   Hgg_tree(TTree *tree=0);
   virtual ~Hgg_tree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Hgg_tree_cxx
Hgg_tree::Hgg_tree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("root://eosatlas//eos/atlas/unpledged/group-wisc/xrootd/user/fwang/Hgg_output/AC_HighMass_ScalarIso_data12_8TeV_p1344/single_files/list_data12_8TeV.00216432.physics_Egamma.merge.NTUP_PHOTON.f507_m1271_p1341_p1344_p1345_tid01142798_00_0.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("root://eosatlas//eos/atlas/unpledged/group-wisc/xrootd/user/fwang/Hgg_output/AC_HighMass_ScalarIso_data12_8TeV_p1344/single_files/list_data12_8TeV.00216432.physics_Egamma.merge.NTUP_PHOTON.f507_m1271_p1341_p1344_p1345_tid01142798_00_0.root");
      }
      f->GetObject("Hgg_tree",tree);

   }
   Init(tree);
}

Hgg_tree::~Hgg_tree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Hgg_tree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Hgg_tree::LoadTree(Long64_t entry)
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

void Hgg_tree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   PV_z = 0;
   interference_percentage = 0;
   weight_graviton_labels = 0;
   weight_graviton_values = 0;
   el_truth_pt = 0;
   el_truth_eta = 0;
   el_truth_phi = 0;
   el_truth_E = 0;
   el_truth_matched = 0;
   el_truth_type = 0;
   el_truth_mothertype = 0;
   el_pt = 0;
   el_trk_eta = 0;
   el_trk_phi = 0;
   el_E = 0;
   el_cl_pt = 0;
   el_cl_eta = 0;
   el_cl_phi = 0;
   el_cl_E = 0;
   el_index = 0;
   el_ptcone20 = 0;
   el_etcone40 = 0;
   el_TopoETcone40 = 0;
   el_isLoosePP = 0;
   el_isMediumPP = 0;
   el_isTightPP = 0;
   el_isLHLoose = 0;
   el_charge = 0;
   el_SF = 0;
   mu_truth_pt = 0;
   mu_truth_eta = 0;
   mu_truth_phi = 0;
   mu_truth_matched = 0;
   mu_truth_type = 0;
   mu_truth_mothertype = 0;
   mu_pt = 0;
   mu_eta = 0;
   mu_phi = 0;
   mu_index = 0;
   mu_ptcone20 = 0;
   mu_etcone40 = 0;
   mu_isLoose = 0;
   mu_isMedium = 0;
   mu_isTight = 0;
   mu_charge = 0;
   mu_SF = 0;
   jet_pt = 0;
   jet_E = 0;
   jet_eta = 0;
   jet_eta_emscale = 0;
   jet_phi = 0;
   jet_jvf = 0;
   jet_mv1 = 0;
   jet_mv1c = 0;
   jet_badBCH = 0;
   jet_flavor_truth_label = 0;
   jet_index = 0;
   jet_el_dr = 0;
   jet_el_matched = 0;
   jet_mu_dr = 0;
   jet_mu_matched = 0;
   jet_MatchedToPhoton = 0;
   jet_truth_pt = 0;
   jet_truth_eta = 0;
   jet_truth_phi = 0;
   jet_truth_E = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("SampleName", &SampleName, &b_SampleName);
   fChain->SetBranchAddress("LHCEnergy", &LHCEnergy, &b_LHCEnergy);
   fChain->SetBranchAddress("NEVENT", &NEVENT, &b_NEVENT);
   fChain->SetBranchAddress("NEVENT_weighted", &NEVENT_weighted, &b_NEVENT_weighted);
   fChain->SetBranchAddress("NEVENT_Dalitz", &NEVENT_Dalitz, &b_NEVENT_Dalitz);
   fChain->SetBranchAddress("NEVENT_Dalitz_weighted", &NEVENT_Dalitz_weighted, &b_NEVENT_Dalitz_weighted);
   fChain->SetBranchAddress("Run", &Run, &b_Run);
   fChain->SetBranchAddress("RandomRunNumber", &RandomRunNumber, &b_RandomRunNumber);
   fChain->SetBranchAddress("RandomLumiBlockNumber", &RandomLumiBlockNumber, &b_RandomLumiBlockNumber);
   fChain->SetBranchAddress("LB", &LB, &b_LB);
   fChain->SetBranchAddress("Event", &Event, &b_Event);
   fChain->SetBranchAddress("mcevt_pdf_id1", &mcevt_pdf_id1, &b_mcevt_pdf_id1);
   fChain->SetBranchAddress("mcevt_pdf_id2", &mcevt_pdf_id2, &b_mcevt_pdf_id2);
   fChain->SetBranchAddress("mcevt_pdf_x1", &mcevt_pdf_x1, &b_mcevt_pdf_x1);
   fChain->SetBranchAddress("mcevt_pdf_x2", &mcevt_pdf_x2, &b_mcevt_pdf_x2);
   fChain->SetBranchAddress("mcevt_pdf_scale", &mcevt_pdf_scale, &b_mcevt_pdf_scale);
   fChain->SetBranchAddress("mcevt_pdf1", &mcevt_pdf1, &b_mcevt_pdf1);
   fChain->SetBranchAddress("mcevt_pdf2", &mcevt_pdf2, &b_mcevt_pdf2);
   fChain->SetBranchAddress("NPV", &NPV, &b_NPV);
   fChain->SetBranchAddress("NPV_all", &NPV_all, &b_NPV_all);
   fChain->SetBranchAddress("Ntruthjets", &Ntruthjets, &b_Ntruthjets);
   fChain->SetBranchAddress("TYPE_DATA", &TYPE_DATA, &b_TYPE_DATA);
   fChain->SetBranchAddress("MCtype", &MCtype, &b_MCtype);
   fChain->SetBranchAddress("AvgIntPerXing", &AvgIntPerXing, &b_AvgIntPerXing);
   fChain->SetBranchAddress("ActIntPerXing", &ActIntPerXing, &b_ActIntPerXing);
   fChain->SetBranchAddress("flag_initial", &flag_initial, &b_flag_initial);
   fChain->SetBranchAddress("flag_trigger", &flag_trigger, &b_flag_trigger);
   fChain->SetBranchAddress("flag_GRL", &flag_GRL, &b_flag_GRL);
   fChain->SetBranchAddress("flag_lar", &flag_lar, &b_flag_lar);
   fChain->SetBranchAddress("flag_PV", &flag_PV, &b_flag_PV);
   fChain->SetBranchAddress("flag_pre", &flag_pre, &b_flag_pre);
   fChain->SetBranchAddress("flag_pre_graviton", &flag_pre_graviton, &b_flag_pre_graviton);
   fChain->SetBranchAddress("flag_pt", &flag_pt, &b_flag_pt);
   fChain->SetBranchAddress("flag_pt_graviton", &flag_pt_graviton, &b_flag_pt_graviton);
   fChain->SetBranchAddress("flag_PID", &flag_PID, &b_flag_PID);
   fChain->SetBranchAddress("flag_isEM", &flag_isEM, &b_flag_isEM);
   fChain->SetBranchAddress("flag_NNPID", &flag_NNPID, &b_flag_NNPID);
   fChain->SetBranchAddress("flag_iso", &flag_iso, &b_flag_iso);
   fChain->SetBranchAddress("flag_iso_graviton", &flag_iso_graviton, &b_flag_iso_graviton);
   fChain->SetBranchAddress("flag_iso_scalar", &flag_iso_scalar, &b_flag_iso_scalar);
   fChain->SetBranchAddress("flag_mgg", &flag_mgg, &b_flag_mgg);
   fChain->SetBranchAddress("flag_mgg_150", &flag_mgg_150, &b_flag_mgg_150);
   fChain->SetBranchAddress("flag_BCHClean", &flag_BCHClean, &b_flag_BCHClean);
   fChain->SetBranchAddress("flag_all", &flag_all, &b_flag_all);
   fChain->SetBranchAddress("flag_noDalitz", &flag_noDalitz, &b_flag_noDalitz);
   fChain->SetBranchAddress("flag_cleanMET", &flag_cleanMET, &b_flag_cleanMET);
   fChain->SetBranchAddress("flag_DiEle", &flag_DiEle, &b_flag_DiEle);
   fChain->SetBranchAddress("flag_DiMuo", &flag_DiMuo, &b_flag_DiMuo);
   fChain->SetBranchAddress("flag_RelPt_35_25", &flag_RelPt_35_25, &b_flag_RelPt_35_25);
   fChain->SetBranchAddress("flag_RelPt_40_30", &flag_RelPt_40_30, &b_flag_RelPt_40_30);
   fChain->SetBranchAddress("mass_jj", &mass_jj, &b_mass_jj);
   fChain->SetBranchAddress("mass_ggjj", &mass_ggjj, &b_mass_ggjj);
   fChain->SetBranchAddress("mass_ggj", &mass_ggj, &b_mass_ggj);
   fChain->SetBranchAddress("mass_uncorr", &mass_uncorr, &b_mass_uncorr);
   fChain->SetBranchAddress("mass_PV_EM", &mass_PV_EM, &b_mass_PV_EM);
   fChain->SetBranchAddress("mass_grav_corr", &mass_grav_corr, &b_mass_grav_corr);
   fChain->SetBranchAddress("PT", &PT, &b_PT);
   fChain->SetBranchAddress("Eta", &Eta, &b_Eta);
   fChain->SetBranchAddress("Phi", &Phi, &b_Phi);
   fChain->SetBranchAddress("phi_diff", &phi_diff, &b_phi_diff);
   fChain->SetBranchAddress("CosThetaStar", &CosThetaStar, &b_CosThetaStar);
   fChain->SetBranchAddress("costhetastar_CS", &costhetastar_CS, &b_costhetastar_CS);
   fChain->SetBranchAddress("pt_t", &pt_t, &b_pt_t);
   fChain->SetBranchAddress("pt_l", &pt_l, &b_pt_l);
   fChain->SetBranchAddress("eta_Zeppenfeld", &eta_Zeppenfeld, &b_eta_Zeppenfeld);
   fChain->SetBranchAddress("deltaRMinGJ", &deltaRMinGJ, &b_deltaRMinGJ);
   fChain->SetBranchAddress("deltaRMinGJ_for_BDT", &deltaRMinGJ_for_BDT, &b_deltaRMinGJ_for_BDT);
   fChain->SetBranchAddress("delta_eta_photons", &delta_eta_photons, &b_delta_eta_photons);
   fChain->SetBranchAddress("delta_phi_photons", &delta_phi_photons, &b_delta_phi_photons);
   fChain->SetBranchAddress("PV_z", &PV_z, &b_PV_z);
   fChain->SetBranchAddress("z_mc_truth_vertex", &z_mc_truth_vertex, &b_z_mc_truth_vertex);
   fChain->SetBranchAddress("zcommon", &zcommon, &b_zcommon);
   fChain->SetBranchAddress("zcommon_sumPt", &zcommon_sumPt, &b_zcommon_sumPt);
   fChain->SetBranchAddress("zcommon_Pointing", &zcommon_Pointing, &b_zcommon_Pointing);
   fChain->SetBranchAddress("zcommon_Likelihood", &zcommon_Likelihood, &b_zcommon_Likelihood);
   fChain->SetBranchAddress("index_PV_ID", &index_PV_ID, &b_index_PV_ID);
   fChain->SetBranchAddress("index_PV_ID_WithMoreThan2Tracks", &index_PV_ID_WithMoreThan2Tracks, &b_index_PV_ID_WithMoreThan2Tracks);
   fChain->SetBranchAddress("index_PV_ID_LH", &index_PV_ID_LH, &b_index_PV_ID_LH);
   fChain->SetBranchAddress("index_PV_ID_WithMoreThan2Tracks_LH", &index_PV_ID_WithMoreThan2Tracks_LH, &b_index_PV_ID_WithMoreThan2Tracks_LH);
   fChain->SetBranchAddress("index_PV_Likelihood", &index_PV_Likelihood, &b_index_PV_Likelihood);
   fChain->SetBranchAddress("MCweight", &MCweight, &b_MCweight);
   fChain->SetBranchAddress("PUweight", &PUweight, &b_PUweight);
   fChain->SetBranchAddress("ZVTXweight", &ZVTXweight, &b_ZVTXweight);
   fChain->SetBranchAddress("pT_weight", &pT_weight, &b_pT_weight);
   fChain->SetBranchAddress("pT_weightError", &pT_weightError, &b_pT_weightError);
   fChain->SetBranchAddress("interference_weight", &interference_weight, &b_interference_weight);
   fChain->SetBranchAddress("interference_weight_coupling", &interference_weight_coupling, &b_interference_weight_coupling);
   fChain->SetBranchAddress("interference_percentage", &interference_percentage, &b_interference_percentage);
   fChain->SetBranchAddress("interference_weight_CTS", &interference_weight_CTS, &b_interference_weight_CTS);
   fChain->SetBranchAddress("JHUPTweight", &JHUPTweight, &b_JHUPTweight);
   fChain->SetBranchAddress("selected_weight", &selected_weight, &b_selected_weight);
   fChain->SetBranchAddress("initial_weight", &initial_weight, &b_initial_weight);
   fChain->SetBranchAddress("mass_category_weight", &mass_category_weight, &b_mass_category_weight);
   fChain->SetBranchAddress("final_weight", &final_weight, &b_final_weight);
   fChain->SetBranchAddress("weight_graviton_labels", &weight_graviton_labels, &b_weight_graviton_labels);
   fChain->SetBranchAddress("weight_graviton_values", &weight_graviton_values, &b_weight_graviton_values);
   fChain->SetBranchAddress("Higgs_truth_pt", &Higgs_truth_pt, &b_Higgs_truth_pt);
   fChain->SetBranchAddress("Higgs_truth_mass", &Higgs_truth_mass, &b_Higgs_truth_mass);
   fChain->SetBranchAddress("Graviton_truth_mass", &Graviton_truth_mass, &b_Graviton_truth_mass);
   fChain->SetBranchAddress("Graviton_mc_mass", &Graviton_mc_mass, &b_Graviton_mc_mass);
   fChain->SetBranchAddress("xsection", &xsection, &b_xsection);
   fChain->SetBranchAddress("branching_ratio", &branching_ratio, &b_branching_ratio);
   fChain->SetBranchAddress("is_gg_not_qq", &is_gg_not_qq, &b_is_gg_not_qq);
   fChain->SetBranchAddress("Nphotons", &Nphotons, &b_Nphotons);
   fChain->SetBranchAddress("ph_index_1st", &ph_index_1st, &b_ph_index_1st);
   fChain->SetBranchAddress("ph_index_2nd", &ph_index_2nd, &b_ph_index_2nd);
   fChain->SetBranchAddress("ph_pt_1st", &ph_pt_1st, &b_ph_pt_1st);
   fChain->SetBranchAddress("ph_pt_2nd", &ph_pt_2nd, &b_ph_pt_2nd);
   fChain->SetBranchAddress("ph_pt_corr_1st", &ph_pt_corr_1st, &b_ph_pt_corr_1st);
   fChain->SetBranchAddress("ph_pt_corr_2nd", &ph_pt_corr_2nd, &b_ph_pt_corr_2nd);
   fChain->SetBranchAddress("ph_E_1st", &ph_E_1st, &b_ph_E_1st);
   fChain->SetBranchAddress("ph_E_2nd", &ph_E_2nd, &b_ph_E_2nd);
   fChain->SetBranchAddress("ph_E_real_1st", &ph_E_real_1st, &b_ph_E_real_1st);
   fChain->SetBranchAddress("ph_E_real_2nd", &ph_E_real_2nd, &b_ph_E_real_2nd);
   fChain->SetBranchAddress("ph_Es_1st", &ph_Es_1st, &b_ph_Es_1st);
   fChain->SetBranchAddress("ph_Es_2nd", &ph_Es_2nd, &b_ph_Es_2nd);
   fChain->SetBranchAddress("ph_Ecorr_1st", &ph_Ecorr_1st, &b_ph_Ecorr_1st);
   fChain->SetBranchAddress("ph_Ecorr_2nd", &ph_Ecorr_2nd, &b_ph_Ecorr_2nd);
   fChain->SetBranchAddress("ph_eta_1st", &ph_eta_1st, &b_ph_eta_1st);
   fChain->SetBranchAddress("ph_eta_2nd", &ph_eta_2nd, &b_ph_eta_2nd);
   fChain->SetBranchAddress("ph_etas2_1st", &ph_etas2_1st, &b_ph_etas2_1st);
   fChain->SetBranchAddress("ph_etas2_2nd", &ph_etas2_2nd, &b_ph_etas2_2nd);
   fChain->SetBranchAddress("ph_etas1_1st", &ph_etas1_1st, &b_ph_etas1_1st);
   fChain->SetBranchAddress("ph_etas1_2nd", &ph_etas1_2nd, &b_ph_etas1_2nd);
   fChain->SetBranchAddress("ph_phi_1st", &ph_phi_1st, &b_ph_phi_1st);
   fChain->SetBranchAddress("ph_phi_2nd", &ph_phi_2nd, &b_ph_phi_2nd);
   fChain->SetBranchAddress("ph_SF_1st", &ph_SF_1st, &b_ph_SF_1st);
   fChain->SetBranchAddress("ph_SF_2nd", &ph_SF_2nd, &b_ph_SF_2nd);
   fChain->SetBranchAddress("ph_cl_pt_1st", &ph_cl_pt_1st, &b_ph_cl_pt_1st);
   fChain->SetBranchAddress("ph_cl_pt_2nd", &ph_cl_pt_2nd, &b_ph_cl_pt_2nd);
   fChain->SetBranchAddress("ph_cl_eta_1st", &ph_cl_eta_1st, &b_ph_cl_eta_1st);
   fChain->SetBranchAddress("ph_cl_eta_2nd", &ph_cl_eta_2nd, &b_ph_cl_eta_2nd);
   fChain->SetBranchAddress("ph_cl_phi_1st", &ph_cl_phi_1st, &b_ph_cl_phi_1st);
   fChain->SetBranchAddress("ph_cl_phi_2nd", &ph_cl_phi_2nd, &b_ph_cl_phi_2nd);
   fChain->SetBranchAddress("ph_cl_E_1st", &ph_cl_E_1st, &b_ph_cl_E_1st);
   fChain->SetBranchAddress("ph_cl_E_2nd", &ph_cl_E_2nd, &b_ph_cl_E_2nd);
   fChain->SetBranchAddress("ph_convFlag_1st", &ph_convFlag_1st, &b_ph_convFlag_1st);
   fChain->SetBranchAddress("ph_convFlag_2nd", &ph_convFlag_2nd, &b_ph_convFlag_2nd);
   fChain->SetBranchAddress("ph_conversion_radius_1st", &ph_conversion_radius_1st, &b_ph_conversion_radius_1st);
   fChain->SetBranchAddress("ph_conversion_radius_2nd", &ph_conversion_radius_2nd, &b_ph_conversion_radius_2nd);
   fChain->SetBranchAddress("ph_convBit_1st", &ph_convBit_1st, &b_ph_convBit_1st);
   fChain->SetBranchAddress("ph_convBit_2nd", &ph_convBit_2nd, &b_ph_convBit_2nd);
   fChain->SetBranchAddress("ph_isEM_1st", &ph_isEM_1st, &b_ph_isEM_1st);
   fChain->SetBranchAddress("ph_isEM_2nd", &ph_isEM_2nd, &b_ph_isEM_2nd);
   fChain->SetBranchAddress("ph_isEMtight_1st", &ph_isEMtight_1st, &b_ph_isEMtight_1st);
   fChain->SetBranchAddress("ph_isEMtight_2nd", &ph_isEMtight_2nd, &b_ph_isEMtight_2nd);
   fChain->SetBranchAddress("ph_LoosePrime_1st", &ph_LoosePrime_1st, &b_ph_LoosePrime_1st);
   fChain->SetBranchAddress("ph_LoosePrime_2nd", &ph_LoosePrime_2nd, &b_ph_LoosePrime_2nd);
   fChain->SetBranchAddress("ph_isNN_1st", &ph_isNN_1st, &b_ph_isNN_1st);
   fChain->SetBranchAddress("ph_isNN_2nd", &ph_isNN_2nd, &b_ph_isNN_2nd);
   fChain->SetBranchAddress("ph_NNresponse_1st", &ph_NNresponse_1st, &b_ph_NNresponse_1st);
   fChain->SetBranchAddress("ph_NNresponse_2nd", &ph_NNresponse_2nd, &b_ph_NNresponse_2nd);
   fChain->SetBranchAddress("ph_NNdiscrcut_1st", &ph_NNdiscrcut_1st, &b_ph_NNdiscrcut_1st);
   fChain->SetBranchAddress("ph_NNdiscrcut_2nd", &ph_NNdiscrcut_2nd, &b_ph_NNdiscrcut_2nd);
   fChain->SetBranchAddress("ph_is_el_mediumPP_1st", &ph_is_el_mediumPP_1st, &b_ph_is_el_mediumPP_1st);
   fChain->SetBranchAddress("ph_is_el_mediumPP_2nd", &ph_is_el_mediumPP_2nd, &b_ph_is_el_mediumPP_2nd);
   fChain->SetBranchAddress("ph_is_el_LHloose_1st", &ph_is_el_LHloose_1st, &b_ph_is_el_LHloose_1st);
   fChain->SetBranchAddress("ph_is_el_LHloose_2nd", &ph_is_el_LHloose_2nd, &b_ph_is_el_LHloose_2nd);
   fChain->SetBranchAddress("ph_BL_1st", &ph_BL_1st, &b_ph_BL_1st);
   fChain->SetBranchAddress("ph_BL_2nd", &ph_BL_2nd, &b_ph_BL_2nd);
   fChain->SetBranchAddress("ph_expBL_1st", &ph_expBL_1st, &b_ph_expBL_1st);
   fChain->SetBranchAddress("ph_expBL_2nd", &ph_expBL_2nd, &b_ph_expBL_2nd);
   fChain->SetBranchAddress("ph_isIso_scalar_1st", &ph_isIso_scalar_1st, &b_ph_isIso_scalar_1st);
   fChain->SetBranchAddress("ph_isIso_scalar_2nd", &ph_isIso_scalar_2nd, &b_ph_isIso_scalar_2nd);
   fChain->SetBranchAddress("ph_etcone40_ptcorr_1st", &ph_etcone40_ptcorr_1st, &b_ph_etcone40_ptcorr_1st);
   fChain->SetBranchAddress("ph_etcone40_ptcorr_2nd", &ph_etcone40_ptcorr_2nd, &b_ph_etcone40_ptcorr_2nd);
   fChain->SetBranchAddress("ph_etcone40_corr_1st", &ph_etcone40_corr_1st, &b_ph_etcone40_corr_1st);
   fChain->SetBranchAddress("ph_etcone40_corr_2nd", &ph_etcone40_corr_2nd, &b_ph_etcone40_corr_2nd);
   fChain->SetBranchAddress("ph_etcone40_PtED_corr_1st", &ph_etcone40_PtED_corr_1st, &b_ph_etcone40_PtED_corr_1st);
   fChain->SetBranchAddress("ph_etcone40_PtED_corr_2nd", &ph_etcone40_PtED_corr_2nd, &b_ph_etcone40_PtED_corr_2nd);
   fChain->SetBranchAddress("ph_etcone40_graviton_1st", &ph_etcone40_graviton_1st, &b_ph_etcone40_graviton_1st);
   fChain->SetBranchAddress("ph_etcone40_graviton_2nd", &ph_etcone40_graviton_2nd, &b_ph_etcone40_graviton_2nd);
   fChain->SetBranchAddress("ph_TopoEtcone40_1st", &ph_TopoEtcone40_1st, &b_ph_TopoEtcone40_1st);
   fChain->SetBranchAddress("ph_TopoEtcone40_2nd", &ph_TopoEtcone40_2nd, &b_ph_TopoEtcone40_2nd);
   fChain->SetBranchAddress("ph_TrackIso_corr_1st", &ph_TrackIso_corr_1st, &b_ph_TrackIso_corr_1st);
   fChain->SetBranchAddress("ph_TrackIso_corr_2nd", &ph_TrackIso_corr_2nd, &b_ph_TrackIso_corr_2nd);
   fChain->SetBranchAddress("ph_dr_1st", &ph_dr_1st, &b_ph_dr_1st);
   fChain->SetBranchAddress("ph_dr_2nd", &ph_dr_2nd, &b_ph_dr_2nd);
   fChain->SetBranchAddress("ph_rawcl_Es0_1st", &ph_rawcl_Es0_1st, &b_ph_rawcl_Es0_1st);
   fChain->SetBranchAddress("ph_rawcl_Es0_2nd", &ph_rawcl_Es0_2nd, &b_ph_rawcl_Es0_2nd);
   fChain->SetBranchAddress("ph_rawcl_Es1_1st", &ph_rawcl_Es1_1st, &b_ph_rawcl_Es1_1st);
   fChain->SetBranchAddress("ph_rawcl_Es1_2nd", &ph_rawcl_Es1_2nd, &b_ph_rawcl_Es1_2nd);
   fChain->SetBranchAddress("ph_rawcl_Es2_1st", &ph_rawcl_Es2_1st, &b_ph_rawcl_Es2_1st);
   fChain->SetBranchAddress("ph_rawcl_Es2_2nd", &ph_rawcl_Es2_2nd, &b_ph_rawcl_Es2_2nd);
   fChain->SetBranchAddress("ph_rawcl_Es3_1st", &ph_rawcl_Es3_1st, &b_ph_rawcl_Es3_1st);
   fChain->SetBranchAddress("ph_rawcl_Es3_2nd", &ph_rawcl_Es3_2nd, &b_ph_rawcl_Es3_2nd);
   fChain->SetBranchAddress("ph_cl_etaCalo_1st", &ph_cl_etaCalo_1st, &b_ph_cl_etaCalo_1st);
   fChain->SetBranchAddress("ph_cl_etaCalo_2nd", &ph_cl_etaCalo_2nd, &b_ph_cl_etaCalo_2nd);
   fChain->SetBranchAddress("ph_cl_phiCalo_1st", &ph_cl_phiCalo_1st, &b_ph_cl_phiCalo_1st);
   fChain->SetBranchAddress("ph_cl_phiCalo_2nd", &ph_cl_phiCalo_2nd, &b_ph_cl_phiCalo_2nd);
   fChain->SetBranchAddress("ph_ptconv_1st", &ph_ptconv_1st, &b_ph_ptconv_1st);
   fChain->SetBranchAddress("ph_ptconv_2nd", &ph_ptconv_2nd, &b_ph_ptconv_2nd);
   fChain->SetBranchAddress("ph_convtrk1nPixHits_1st", &ph_convtrk1nPixHits_1st, &b_ph_convtrk1nPixHits_1st);
   fChain->SetBranchAddress("ph_convtrk1nPixHits_2nd", &ph_convtrk1nPixHits_2nd, &b_ph_convtrk1nPixHits_2nd);
   fChain->SetBranchAddress("ph_convtrk1nSCTHits_1st", &ph_convtrk1nSCTHits_1st, &b_ph_convtrk1nSCTHits_1st);
   fChain->SetBranchAddress("ph_convtrk1nSCTHits_2nd", &ph_convtrk1nSCTHits_2nd, &b_ph_convtrk1nSCTHits_2nd);
   fChain->SetBranchAddress("ph_convtrk2nPixHits_1st", &ph_convtrk2nPixHits_1st, &b_ph_convtrk2nPixHits_1st);
   fChain->SetBranchAddress("ph_convtrk2nPixHits_2nd", &ph_convtrk2nPixHits_2nd, &b_ph_convtrk2nPixHits_2nd);
   fChain->SetBranchAddress("ph_convtrk2nSCTHits_1st", &ph_convtrk2nSCTHits_1st, &b_ph_convtrk2nSCTHits_1st);
   fChain->SetBranchAddress("ph_convtrk2nSCTHits_2nd", &ph_convtrk2nSCTHits_2nd, &b_ph_convtrk2nSCTHits_2nd);
   fChain->SetBranchAddress("ph_pt1conv_1st", &ph_pt1conv_1st, &b_ph_pt1conv_1st);
   fChain->SetBranchAddress("ph_pt1conv_2nd", &ph_pt1conv_2nd, &b_ph_pt1conv_2nd);
   fChain->SetBranchAddress("ph_pt2conv_1st", &ph_pt2conv_1st, &b_ph_pt2conv_1st);
   fChain->SetBranchAddress("ph_pt2conv_2nd", &ph_pt2conv_2nd, &b_ph_pt2conv_2nd);
   fChain->SetBranchAddress("ph_rawconvFlag_1st", &ph_rawconvFlag_1st, &b_ph_rawconvFlag_1st);
   fChain->SetBranchAddress("ph_rawconvFlag_2nd", &ph_rawconvFlag_2nd, &b_ph_rawconvFlag_2nd);
   fChain->SetBranchAddress("ph_truth_matched_1st", &ph_truth_matched_1st, &b_ph_truth_matched_1st);
   fChain->SetBranchAddress("ph_truth_matched_2nd", &ph_truth_matched_2nd, &b_ph_truth_matched_2nd);
   fChain->SetBranchAddress("ph_truth_isConv_1st", &ph_truth_isConv_1st, &b_ph_truth_isConv_1st);
   fChain->SetBranchAddress("ph_truth_isConv_2nd", &ph_truth_isConv_2nd, &b_ph_truth_isConv_2nd);
   fChain->SetBranchAddress("ph_truth_isBrem_1st", &ph_truth_isBrem_1st, &b_ph_truth_isBrem_1st);
   fChain->SetBranchAddress("ph_truth_isBrem_2nd", &ph_truth_isBrem_2nd, &b_ph_truth_isBrem_2nd);
   fChain->SetBranchAddress("ph_truth_isPhotonFromHardProc_1st", &ph_truth_isPhotonFromHardProc_1st, &b_ph_truth_isPhotonFromHardProc_1st);
   fChain->SetBranchAddress("ph_truth_isPhotonFromHardProc_2nd", &ph_truth_isPhotonFromHardProc_2nd, &b_ph_truth_isPhotonFromHardProc_2nd);
   fChain->SetBranchAddress("ph_truth_mothertype_1st", &ph_truth_mothertype_1st, &b_ph_truth_mothertype_1st);
   fChain->SetBranchAddress("ph_truth_mothertype_2nd", &ph_truth_mothertype_2nd, &b_ph_truth_mothertype_2nd);
   fChain->SetBranchAddress("ph_truth_type_1st", &ph_truth_type_1st, &b_ph_truth_type_1st);
   fChain->SetBranchAddress("ph_truth_type_2nd", &ph_truth_type_2nd, &b_ph_truth_type_2nd);
   fChain->SetBranchAddress("ph_truth_pt_1st", &ph_truth_pt_1st, &b_ph_truth_pt_1st);
   fChain->SetBranchAddress("ph_truth_pt_2nd", &ph_truth_pt_2nd, &b_ph_truth_pt_2nd);
   fChain->SetBranchAddress("ph_truth_eta_1st", &ph_truth_eta_1st, &b_ph_truth_eta_1st);
   fChain->SetBranchAddress("ph_truth_eta_2nd", &ph_truth_eta_2nd, &b_ph_truth_eta_2nd);
   fChain->SetBranchAddress("ph_truth_phi_1st", &ph_truth_phi_1st, &b_ph_truth_phi_1st);
   fChain->SetBranchAddress("ph_truth_phi_2nd", &ph_truth_phi_2nd, &b_ph_truth_phi_2nd);
   fChain->SetBranchAddress("ph_truth_E_1st", &ph_truth_E_1st, &b_ph_truth_E_1st);
   fChain->SetBranchAddress("ph_truth_E_2nd", &ph_truth_E_2nd, &b_ph_truth_E_2nd);
   fChain->SetBranchAddress("diphoton_truth_pt", &diphoton_truth_pt, &b_diphoton_truth_pt);
   fChain->SetBranchAddress("diphoton_truth_eta", &diphoton_truth_eta, &b_diphoton_truth_eta);
   fChain->SetBranchAddress("diphoton_truth_phi", &diphoton_truth_phi, &b_diphoton_truth_phi);
   fChain->SetBranchAddress("diphoton_truth_E", &diphoton_truth_E, &b_diphoton_truth_E);
   fChain->SetBranchAddress("diphoton_truth_costhetastar_CS", &diphoton_truth_costhetastar_CS, &b_diphoton_truth_costhetastar_CS);
   fChain->SetBranchAddress("diphoton_truth_mass", &diphoton_truth_mass, &b_diphoton_truth_mass);
   fChain->SetBranchAddress("mcdiphoton_truth_mass", &mcdiphoton_truth_mass, &b_mcdiphoton_truth_mass);
   fChain->SetBranchAddress("mcph_truth_pt_1st", &mcph_truth_pt_1st, &b_mcph_truth_pt_1st);
   fChain->SetBranchAddress("mcph_truth_pt_2nd", &mcph_truth_pt_2nd, &b_mcph_truth_pt_2nd);
   fChain->SetBranchAddress("mcph_truth_eta_1st", &mcph_truth_eta_1st, &b_mcph_truth_eta_1st);
   fChain->SetBranchAddress("mcph_truth_eta_2nd", &mcph_truth_eta_2nd, &b_mcph_truth_eta_2nd);
   fChain->SetBranchAddress("mcph_truth_phi_1st", &mcph_truth_phi_1st, &b_mcph_truth_phi_1st);
   fChain->SetBranchAddress("mcph_truth_phi_2nd", &mcph_truth_phi_2nd, &b_mcph_truth_phi_2nd);
   fChain->SetBranchAddress("mcph_truth_etcone40_EDcorr_1st", &mcph_truth_etcone40_EDcorr_1st, &b_mcph_truth_etcone40_EDcorr_1st);
   fChain->SetBranchAddress("mcph_truth_etcone40_EDcorr_2nd", &mcph_truth_etcone40_EDcorr_2nd, &b_mcph_truth_etcone40_EDcorr_2nd);
   fChain->SetBranchAddress("Nelectrons", &Nelectrons, &b_Nelectrons);
   fChain->SetBranchAddress("el_truth_pt", &el_truth_pt, &b_el_truth_pt);
   fChain->SetBranchAddress("el_truth_eta", &el_truth_eta, &b_el_truth_eta);
   fChain->SetBranchAddress("el_truth_phi", &el_truth_phi, &b_el_truth_phi);
   fChain->SetBranchAddress("el_truth_E", &el_truth_E, &b_el_truth_E);
   fChain->SetBranchAddress("el_truth_matched", &el_truth_matched, &b_el_truth_matched);
   fChain->SetBranchAddress("el_truth_type", &el_truth_type, &b_el_truth_type);
   fChain->SetBranchAddress("el_truth_mothertype", &el_truth_mothertype, &b_el_truth_mothertype);
   fChain->SetBranchAddress("event_el_SF", &event_el_SF, &b_event_el_SF);
   fChain->SetBranchAddress("el_index_leading", &el_index_leading, &b_el_index_leading);
   fChain->SetBranchAddress("el_index_subleading", &el_index_subleading, &b_el_index_subleading);
   fChain->SetBranchAddress("el_pt", &el_pt, &b_el_pt);
   fChain->SetBranchAddress("el_trk_eta", &el_trk_eta, &b_el_trk_eta);
   fChain->SetBranchAddress("el_trk_phi", &el_trk_phi, &b_el_trk_phi);
   fChain->SetBranchAddress("el_E", &el_E, &b_el_E);
   fChain->SetBranchAddress("el_cl_pt", &el_cl_pt, &b_el_cl_pt);
   fChain->SetBranchAddress("el_cl_eta", &el_cl_eta, &b_el_cl_eta);
   fChain->SetBranchAddress("el_cl_phi", &el_cl_phi, &b_el_cl_phi);
   fChain->SetBranchAddress("el_cl_E", &el_cl_E, &b_el_cl_E);
   fChain->SetBranchAddress("el_index", &el_index, &b_el_index);
   fChain->SetBranchAddress("el_ptcone20", &el_ptcone20, &b_el_ptcone20);
   fChain->SetBranchAddress("el_etcone40", &el_etcone40, &b_el_etcone40);
   fChain->SetBranchAddress("el_TopoETcone40", &el_TopoETcone40, &b_el_TopoETcone40);
   fChain->SetBranchAddress("el_isLoosePP", &el_isLoosePP, &b_el_isLoosePP);
   fChain->SetBranchAddress("el_isMediumPP", &el_isMediumPP, &b_el_isMediumPP);
   fChain->SetBranchAddress("el_isTightPP", &el_isTightPP, &b_el_isTightPP);
   fChain->SetBranchAddress("el_isLHLoose", &el_isLHLoose, &b_el_isLHLoose);
   fChain->SetBranchAddress("el_charge", &el_charge, &b_el_charge);
   fChain->SetBranchAddress("el_SF", &el_SF, &b_el_SF);
   fChain->SetBranchAddress("Nmuons", &Nmuons, &b_Nmuons);
   fChain->SetBranchAddress("mu_truth_pt", &mu_truth_pt, &b_mu_truth_pt);
   fChain->SetBranchAddress("mu_truth_eta", &mu_truth_eta, &b_mu_truth_eta);
   fChain->SetBranchAddress("mu_truth_phi", &mu_truth_phi, &b_mu_truth_phi);
   fChain->SetBranchAddress("mu_truth_matched", &mu_truth_matched, &b_mu_truth_matched);
   fChain->SetBranchAddress("mu_truth_type", &mu_truth_type, &b_mu_truth_type);
   fChain->SetBranchAddress("mu_truth_mothertype", &mu_truth_mothertype, &b_mu_truth_mothertype);
   fChain->SetBranchAddress("event_mu_SF", &event_mu_SF, &b_event_mu_SF);
   fChain->SetBranchAddress("mu_index_leading", &mu_index_leading, &b_mu_index_leading);
   fChain->SetBranchAddress("mu_index_subleading", &mu_index_subleading, &b_mu_index_subleading);
   fChain->SetBranchAddress("mu_pt", &mu_pt, &b_mu_pt);
   fChain->SetBranchAddress("mu_eta", &mu_eta, &b_mu_eta);
   fChain->SetBranchAddress("mu_phi", &mu_phi, &b_mu_phi);
   fChain->SetBranchAddress("mu_index", &mu_index, &b_mu_index);
   fChain->SetBranchAddress("mu_ptcone20", &mu_ptcone20, &b_mu_ptcone20);
   fChain->SetBranchAddress("mu_etcone40", &mu_etcone40, &b_mu_etcone40);
   fChain->SetBranchAddress("mu_isLoose", &mu_isLoose, &b_mu_isLoose);
   fChain->SetBranchAddress("mu_isMedium", &mu_isMedium, &b_mu_isMedium);
   fChain->SetBranchAddress("mu_isTight", &mu_isTight, &b_mu_isTight);
   fChain->SetBranchAddress("mu_charge", &mu_charge, &b_mu_charge);
   fChain->SetBranchAddress("mu_SF", &mu_SF, &b_mu_SF);
   fChain->SetBranchAddress("Njets", &Njets, &b_Njets);
   fChain->SetBranchAddress("Njets_NoEtaCut", &Njets_NoEtaCut, &b_Njets_NoEtaCut);
   fChain->SetBranchAddress("nb_jets_30G", &nb_jets_30G, &b_nb_jets_30G);
   fChain->SetBranchAddress("nb_jets_25G", &nb_jets_25G, &b_nb_jets_25G);
   fChain->SetBranchAddress("nb_jetsB_30G_60", &nb_jetsB_30G_60, &b_nb_jetsB_30G_60);
   fChain->SetBranchAddress("nb_jetsB_30G_70", &nb_jetsB_30G_70, &b_nb_jetsB_30G_70);
   fChain->SetBranchAddress("nb_jetsB_30G_80", &nb_jetsB_30G_80, &b_nb_jetsB_30G_80);
   fChain->SetBranchAddress("nb_jetsB_25G_80", &nb_jetsB_25G_80, &b_nb_jetsB_25G_80);
   fChain->SetBranchAddress("nb_jetsB_25G_85", &nb_jetsB_25G_85, &b_nb_jetsB_25G_85);
   fChain->SetBranchAddress("nb_jets_25GeV_passingBCH", &nb_jets_25GeV_passingBCH, &b_nb_jets_25GeV_passingBCH);
   fChain->SetBranchAddress("nb_jets_30GeV_passingBCH", &nb_jets_30GeV_passingBCH, &b_nb_jets_30GeV_passingBCH);
   fChain->SetBranchAddress("nb_jetsB_25GeV_80_passingBCH", &nb_jetsB_25GeV_80_passingBCH, &b_nb_jetsB_25GeV_80_passingBCH);
   fChain->SetBranchAddress("nb_jetsB_30GeV_70_passingBCH", &nb_jetsB_30GeV_70_passingBCH, &b_nb_jetsB_30GeV_70_passingBCH);
   fChain->SetBranchAddress("nb_jetsB_30GeV_60_passingBCH", &nb_jetsB_30GeV_60_passingBCH, &b_nb_jetsB_30GeV_60_passingBCH);
   fChain->SetBranchAddress("weight_jets", &weight_jets, &b_weight_jets);
   fChain->SetBranchAddress("jet_index_1st", &jet_index_1st, &b_jet_index_1st);
   fChain->SetBranchAddress("jet_index_2nd", &jet_index_2nd, &b_jet_index_2nd);
   fChain->SetBranchAddress("jet_pt_1st", &jet_pt_1st, &b_jet_pt_1st);
   fChain->SetBranchAddress("jet_pt_2nd", &jet_pt_2nd, &b_jet_pt_2nd);
   fChain->SetBranchAddress("jet_eta_1st", &jet_eta_1st, &b_jet_eta_1st);
   fChain->SetBranchAddress("jet_eta_2nd", &jet_eta_2nd, &b_jet_eta_2nd);
   fChain->SetBranchAddress("jet_phi_1st", &jet_phi_1st, &b_jet_phi_1st);
   fChain->SetBranchAddress("jet_phi_2nd", &jet_phi_2nd, &b_jet_phi_2nd);
   fChain->SetBranchAddress("jet_E_1st", &jet_E_1st, &b_jet_E_1st);
   fChain->SetBranchAddress("jet_E_2nd", &jet_E_2nd, &b_jet_E_2nd);
   fChain->SetBranchAddress("delta_eta_jet", &delta_eta_jet, &b_delta_eta_jet);
   fChain->SetBranchAddress("eta1_eta2", &eta1_eta2, &b_eta1_eta2);
   fChain->SetBranchAddress("phi_jj", &phi_jj, &b_phi_jj);
   fChain->SetBranchAddress("jet_jvtxf_1st", &jet_jvtxf_1st, &b_jet_jvtxf_1st);
   fChain->SetBranchAddress("jet_jvtxf_2nd", &jet_jvtxf_2nd, &b_jet_jvtxf_2nd);
   fChain->SetBranchAddress("jet_mv1_1st", &jet_mv1_1st, &b_jet_mv1_1st);
   fChain->SetBranchAddress("jet_mv1_2nd", &jet_mv1_2nd, &b_jet_mv1_2nd);
   fChain->SetBranchAddress("jet_mv1c_1st", &jet_mv1c_1st, &b_jet_mv1c_1st);
   fChain->SetBranchAddress("jet_mv1c_2nd", &jet_mv1c_2nd, &b_jet_mv1c_2nd);
   fChain->SetBranchAddress("jet_badBCH_1st", &jet_badBCH_1st, &b_jet_badBCH_1st);
   fChain->SetBranchAddress("jet_badBCH_2nd", &jet_badBCH_2nd, &b_jet_badBCH_2nd);
   fChain->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
   fChain->SetBranchAddress("jet_E", &jet_E, &b_jet_E);
   fChain->SetBranchAddress("jet_eta", &jet_eta, &b_jet_eta);
   fChain->SetBranchAddress("jet_eta_emscale", &jet_eta_emscale, &b_jet_eta_emscale);
   fChain->SetBranchAddress("jet_phi", &jet_phi, &b_jet_phi);
   fChain->SetBranchAddress("jet_jvf", &jet_jvf, &b_jet_jvf);
   fChain->SetBranchAddress("jet_mv1", &jet_mv1, &b_jet_mv1);
   fChain->SetBranchAddress("jet_mv1c", &jet_mv1c, &b_jet_mv1c);
   fChain->SetBranchAddress("jet_badBCH", &jet_badBCH, &b_jet_badBCH);
   fChain->SetBranchAddress("jet_flavor_truth_label", &jet_flavor_truth_label, &b_jet_flavor_truth_label);
   fChain->SetBranchAddress("jet_index", &jet_index, &b_jet_index);
   fChain->SetBranchAddress("jet_el_dr", &jet_el_dr, &b_jet_el_dr);
   fChain->SetBranchAddress("jet_el_matched", &jet_el_matched, &b_jet_el_matched);
   fChain->SetBranchAddress("jet_mu_dr", &jet_mu_dr, &b_jet_mu_dr);
   fChain->SetBranchAddress("jet_mu_matched", &jet_mu_matched, &b_jet_mu_matched);
   fChain->SetBranchAddress("jet_MatchedToPhoton", &jet_MatchedToPhoton, &b_jet_MatchedToPhoton);
   fChain->SetBranchAddress("jet_truth_pt", &jet_truth_pt, &b_jet_truth_pt);
   fChain->SetBranchAddress("jet_truth_eta", &jet_truth_eta, &b_jet_truth_eta);
   fChain->SetBranchAddress("jet_truth_phi", &jet_truth_phi, &b_jet_truth_phi);
   fChain->SetBranchAddress("jet_truth_E", &jet_truth_E, &b_jet_truth_E);
   fChain->SetBranchAddress("flag_METBadDueToBCH", &flag_METBadDueToBCH, &b_flag_METBadDueToBCH);
   fChain->SetBranchAddress("MET_Truth_NonInt_etx", &MET_Truth_NonInt_etx, &b_MET_Truth_NonInt_etx);
   fChain->SetBranchAddress("MET_Truth_NonInt_ety", &MET_Truth_NonInt_ety, &b_MET_Truth_NonInt_ety);
   fChain->SetBranchAddress("MET_Truth_NonInt_phi", &MET_Truth_NonInt_phi, &b_MET_Truth_NonInt_phi);
   fChain->SetBranchAddress("MET_Truth_NonInt_et", &MET_Truth_NonInt_et, &b_MET_Truth_NonInt_et);
   fChain->SetBranchAddress("MET_Truth_NonInt_sumet", &MET_Truth_NonInt_sumet, &b_MET_Truth_NonInt_sumet);
   fChain->SetBranchAddress("MET_PhotonTight_Calib_OR_stdvert_RefFinal_etx", &MET_PhotonTight_Calib_OR_stdvert_RefFinal_etx, &b_MET_PhotonTight_Calib_OR_stdvert_RefFinal_etx);
   fChain->SetBranchAddress("MET_PhotonTight_Calib_OR_stdvert_RefFinal_ety", &MET_PhotonTight_Calib_OR_stdvert_RefFinal_ety, &b_MET_PhotonTight_Calib_OR_stdvert_RefFinal_ety);
   fChain->SetBranchAddress("MET_PhotonTight_Calib_OR_stdvert_RefFinal_phi", &MET_PhotonTight_Calib_OR_stdvert_RefFinal_phi, &b_MET_PhotonTight_Calib_OR_stdvert_RefFinal_phi);
   fChain->SetBranchAddress("MET_PhotonTight_Calib_OR_stdvert_RefFinal_et", &MET_PhotonTight_Calib_OR_stdvert_RefFinal_et, &b_MET_PhotonTight_Calib_OR_stdvert_RefFinal_et);
   fChain->SetBranchAddress("MET_PhotonTight_Calib_OR_stdvert_RefFinal_sumet", &MET_PhotonTight_Calib_OR_stdvert_RefFinal_sumet, &b_MET_PhotonTight_Calib_OR_stdvert_RefFinal_sumet);
   fChain->SetBranchAddress("MET_PhotonTight_Calib_OR_stdvert_RefFinal_STVF_etx", &MET_PhotonTight_Calib_OR_stdvert_RefFinal_STVF_etx, &b_MET_PhotonTight_Calib_OR_stdvert_RefFinal_STVF_etx);
   fChain->SetBranchAddress("MET_PhotonTight_Calib_OR_stdvert_RefFinal_STVF_ety", &MET_PhotonTight_Calib_OR_stdvert_RefFinal_STVF_ety, &b_MET_PhotonTight_Calib_OR_stdvert_RefFinal_STVF_ety);
   fChain->SetBranchAddress("MET_PhotonTight_Calib_OR_stdvert_RefFinal_STVF_phi", &MET_PhotonTight_Calib_OR_stdvert_RefFinal_STVF_phi, &b_MET_PhotonTight_Calib_OR_stdvert_RefFinal_STVF_phi);
   fChain->SetBranchAddress("MET_PhotonTight_Calib_OR_stdvert_RefFinal_STVF_et", &MET_PhotonTight_Calib_OR_stdvert_RefFinal_STVF_et, &b_MET_PhotonTight_Calib_OR_stdvert_RefFinal_STVF_et);
   fChain->SetBranchAddress("MET_PhotonTight_Calib_OR_stdvert_RefFinal_STVF_sumet", &MET_PhotonTight_Calib_OR_stdvert_RefFinal_STVF_sumet, &b_MET_PhotonTight_Calib_OR_stdvert_RefFinal_STVF_sumet);
   fChain->SetBranchAddress("MET_PhotonTight_Calib_OR_stdvert_Muon_Total_Staco_etx", &MET_PhotonTight_Calib_OR_stdvert_Muon_Total_Staco_etx, &b_MET_PhotonTight_Calib_OR_stdvert_Muon_Total_Staco_etx);
   fChain->SetBranchAddress("MET_PhotonTight_Calib_OR_stdvert_Muon_Total_Staco_ety", &MET_PhotonTight_Calib_OR_stdvert_Muon_Total_Staco_ety, &b_MET_PhotonTight_Calib_OR_stdvert_Muon_Total_Staco_ety);
   fChain->SetBranchAddress("MET_PhotonTight_Calib_OR_stdvert_Muon_Total_Staco_phi", &MET_PhotonTight_Calib_OR_stdvert_Muon_Total_Staco_phi, &b_MET_PhotonTight_Calib_OR_stdvert_Muon_Total_Staco_phi);
   fChain->SetBranchAddress("MET_PhotonTight_Calib_OR_stdvert_Muon_Total_Staco_et", &MET_PhotonTight_Calib_OR_stdvert_Muon_Total_Staco_et, &b_MET_PhotonTight_Calib_OR_stdvert_Muon_Total_Staco_et);
   fChain->SetBranchAddress("MET_PhotonTight_Calib_OR_stdvert_Muon_Total_Staco_sumet", &MET_PhotonTight_Calib_OR_stdvert_Muon_Total_Staco_sumet, &b_MET_PhotonTight_Calib_OR_stdvert_Muon_Total_Staco_sumet);
   fChain->SetBranchAddress("MET_PhotonTight_Calib_OR_stdvert_significance", &MET_PhotonTight_Calib_OR_stdvert_significance, &b_MET_PhotonTight_Calib_OR_stdvert_significance);
   fChain->SetBranchAddress("MET_PhotonTight_Corrected_RefFinal_etx", &MET_PhotonTight_Corrected_RefFinal_etx, &b_MET_PhotonTight_Corrected_RefFinal_etx);
   fChain->SetBranchAddress("MET_PhotonTight_Corrected_RefFinal_ety", &MET_PhotonTight_Corrected_RefFinal_ety, &b_MET_PhotonTight_Corrected_RefFinal_ety);
   fChain->SetBranchAddress("MET_PhotonTight_Corrected_RefMuon_etx", &MET_PhotonTight_Corrected_RefMuon_etx, &b_MET_PhotonTight_Corrected_RefMuon_etx);
   fChain->SetBranchAddress("MET_PhotonTight_Corrected_RefMuon_ety", &MET_PhotonTight_Corrected_RefMuon_ety, &b_MET_PhotonTight_Corrected_RefMuon_ety);
   fChain->SetBranchAddress("MET_NNTight_Calib_OR_stdvert_RefFinal_etx", &MET_NNTight_Calib_OR_stdvert_RefFinal_etx, &b_MET_NNTight_Calib_OR_stdvert_RefFinal_etx);
   fChain->SetBranchAddress("MET_NNTight_Calib_OR_stdvert_RefFinal_ety", &MET_NNTight_Calib_OR_stdvert_RefFinal_ety, &b_MET_NNTight_Calib_OR_stdvert_RefFinal_ety);
   fChain->SetBranchAddress("MET_NNTight_Calib_OR_stdvert_RefFinal_phi", &MET_NNTight_Calib_OR_stdvert_RefFinal_phi, &b_MET_NNTight_Calib_OR_stdvert_RefFinal_phi);
   fChain->SetBranchAddress("MET_NNTight_Calib_OR_stdvert_RefFinal_et", &MET_NNTight_Calib_OR_stdvert_RefFinal_et, &b_MET_NNTight_Calib_OR_stdvert_RefFinal_et);
   fChain->SetBranchAddress("MET_NNTight_Calib_OR_stdvert_RefFinal_sumet", &MET_NNTight_Calib_OR_stdvert_RefFinal_sumet, &b_MET_NNTight_Calib_OR_stdvert_RefFinal_sumet);
   fChain->SetBranchAddress("MET_NNTight_Calib_OR_stdvert_RefFinal_STVF_etx", &MET_NNTight_Calib_OR_stdvert_RefFinal_STVF_etx, &b_MET_NNTight_Calib_OR_stdvert_RefFinal_STVF_etx);
   fChain->SetBranchAddress("MET_NNTight_Calib_OR_stdvert_RefFinal_STVF_ety", &MET_NNTight_Calib_OR_stdvert_RefFinal_STVF_ety, &b_MET_NNTight_Calib_OR_stdvert_RefFinal_STVF_ety);
   fChain->SetBranchAddress("MET_NNTight_Calib_OR_stdvert_RefFinal_STVF_phi", &MET_NNTight_Calib_OR_stdvert_RefFinal_STVF_phi, &b_MET_NNTight_Calib_OR_stdvert_RefFinal_STVF_phi);
   fChain->SetBranchAddress("MET_NNTight_Calib_OR_stdvert_RefFinal_STVF_et", &MET_NNTight_Calib_OR_stdvert_RefFinal_STVF_et, &b_MET_NNTight_Calib_OR_stdvert_RefFinal_STVF_et);
   fChain->SetBranchAddress("MET_NNTight_Calib_OR_stdvert_RefFinal_STVF_sumet", &MET_NNTight_Calib_OR_stdvert_RefFinal_STVF_sumet, &b_MET_NNTight_Calib_OR_stdvert_RefFinal_STVF_sumet);
   fChain->SetBranchAddress("MET_NNTight_Calib_OR_stdvert_Muon_Total_Staco_etx", &MET_NNTight_Calib_OR_stdvert_Muon_Total_Staco_etx, &b_MET_NNTight_Calib_OR_stdvert_Muon_Total_Staco_etx);
   fChain->SetBranchAddress("MET_NNTight_Calib_OR_stdvert_Muon_Total_Staco_ety", &MET_NNTight_Calib_OR_stdvert_Muon_Total_Staco_ety, &b_MET_NNTight_Calib_OR_stdvert_Muon_Total_Staco_ety);
   fChain->SetBranchAddress("MET_NNTight_Calib_OR_stdvert_Muon_Total_Staco_phi", &MET_NNTight_Calib_OR_stdvert_Muon_Total_Staco_phi, &b_MET_NNTight_Calib_OR_stdvert_Muon_Total_Staco_phi);
   fChain->SetBranchAddress("MET_NNTight_Calib_OR_stdvert_Muon_Total_Staco_et", &MET_NNTight_Calib_OR_stdvert_Muon_Total_Staco_et, &b_MET_NNTight_Calib_OR_stdvert_Muon_Total_Staco_et);
   fChain->SetBranchAddress("MET_NNTight_Calib_OR_stdvert_Muon_Total_Staco_sumet", &MET_NNTight_Calib_OR_stdvert_Muon_Total_Staco_sumet, &b_MET_NNTight_Calib_OR_stdvert_Muon_Total_Staco_sumet);
   fChain->SetBranchAddress("MET_NNTight_Calib_OR_stdvert_significance", &MET_NNTight_Calib_OR_stdvert_significance, &b_MET_NNTight_Calib_OR_stdvert_significance);
   fChain->SetBranchAddress("MT_muMET", &MT_muMET, &b_MT_muMET);
   fChain->SetBranchAddress("MT_elMET", &MT_elMET, &b_MT_elMET);
   fChain->SetBranchAddress("DPhi_ggMET_NNTight_RefFinal", &DPhi_ggMET_NNTight_RefFinal, &b_DPhi_ggMET_NNTight_RefFinal);
   fChain->SetBranchAddress("DPhi_ggMET_PhotonTight_RefFinal", &DPhi_ggMET_PhotonTight_RefFinal, &b_DPhi_ggMET_PhotonTight_RefFinal);
   fChain->SetBranchAddress("MET_NNTight_Calib_OR_RefFinal_et", &MET_NNTight_Calib_OR_RefFinal_et, &b_MET_NNTight_Calib_OR_RefFinal_et);
   fChain->SetBranchAddress("EPScategory", &EPScategory, &b_EPScategory);
   fChain->SetBranchAddress("PTTcategory", &PTTcategory, &b_PTTcategory);
   fChain->SetBranchAddress("JETPTTcategory", &JETPTTcategory, &b_JETPTTcategory);
   fChain->SetBranchAddress("GBJcategory", &GBJcategory, &b_GBJcategory);
   fChain->SetBranchAddress("HighPttEtaConvVBFcategory", &HighPttEtaConvVBFcategory, &b_HighPttEtaConvVBFcategory);
   fChain->SetBranchAddress("HighPttGoodBadVBFcategory", &HighPttGoodBadVBFcategory, &b_HighPttGoodBadVBFcategory);
   fChain->SetBranchAddress("Conversioncategory", &Conversioncategory, &b_Conversioncategory);
   fChain->SetBranchAddress("PaperPttEtacategory", &PaperPttEtacategory, &b_PaperPttEtacategory);
   fChain->SetBranchAddress("VH_HCPcategory", &VH_HCPcategory, &b_VH_HCPcategory);
   fChain->SetBranchAddress("category_MoriondCut", &category_MoriondCut, &b_category_MoriondCut);
   fChain->SetBranchAddress("category_MoriondMVA", &category_MoriondMVA, &b_category_MoriondMVA);
   fChain->SetBranchAddress("category_PaperMass", &category_PaperMass, &b_category_PaperMass);
   fChain->SetBranchAddress("category_PaperCoupling", &category_PaperCoupling, &b_category_PaperCoupling);
   fChain->SetBranchAddress("cat_vh_lepton", &cat_vh_lepton, &b_cat_vh_lepton);
   fChain->SetBranchAddress("cat_vh_dijet", &cat_vh_dijet, &b_cat_vh_dijet);
   fChain->SetBranchAddress("cat_vh_MET", &cat_vh_MET, &b_cat_vh_MET);
   fChain->SetBranchAddress("cat_vh_dilepton", &cat_vh_dilepton, &b_cat_vh_dilepton);
   fChain->SetBranchAddress("cat_vbf_mva1", &cat_vbf_mva1, &b_cat_vbf_mva1);
   fChain->SetBranchAddress("cat_vbf_mva2", &cat_vbf_mva2, &b_cat_vbf_mva2);
   fChain->SetBranchAddress("cat_vbf_cut1", &cat_vbf_cut1, &b_cat_vbf_cut1);
   fChain->SetBranchAddress("cat_vbf_cut2", &cat_vbf_cut2, &b_cat_vbf_cut2);
   fChain->SetBranchAddress("cat_ttH_had", &cat_ttH_had, &b_cat_ttH_had);
   fChain->SetBranchAddress("cat_ttH_lep", &cat_ttH_lep, &b_cat_ttH_lep);
   fChain->SetBranchAddress("moriond_cat_vbf_mva1", &moriond_cat_vbf_mva1, &b_moriond_cat_vbf_mva1);
   fChain->SetBranchAddress("moriond_cat_vbf_mva2", &moriond_cat_vbf_mva2, &b_moriond_cat_vbf_mva2);
   fChain->SetBranchAddress("cat_ptt", &cat_ptt, &b_cat_ptt);
   fChain->SetBranchAddress("cat_vbf_bdt_response", &cat_vbf_bdt_response, &b_cat_vbf_bdt_response);
   fChain->SetBranchAddress("mass_egamma_ClosestToZ", &mass_egamma_ClosestToZ, &b_mass_egamma_ClosestToZ);
   fChain->SetBranchAddress("Zveto", &Zveto, &b_Zveto);
   fChain->SetBranchAddress("Zveto_TTH", &Zveto_TTH, &b_Zveto_TTH);
   Notify();
}

Bool_t Hgg_tree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Hgg_tree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Hgg_tree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Hgg_tree_cxx
