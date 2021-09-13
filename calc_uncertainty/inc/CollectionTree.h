//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Nov 24 18:27:41 2017 by ROOT version 5.34/36
// from TTree CollectionTree/xAOD event tree
// found on file: MxAOD/ttH/ttH_9.root
//////////////////////////////////////////////////////////

#ifndef CollectionTree_h
#define CollectionTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>

using namespace std;

// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t kMaxHGamPhotonsAux = 1;
   const Int_t kMaxHGamElectronsAux = 1;
   const Int_t kMaxHGamAntiKt4EMTopoJetsAux = 1;
   const Int_t kMaxHGamMuonsAux = 1;
   const Int_t kMaxHGamMET_Reference_AntiKt4EMTopoAux = 1;
   const Int_t kMaxHGamEventInfoAux = 1;
   const Int_t kMaxHGamTruthPhotonsAux = 1;
   const Int_t kMaxHGamTruthElectronsAux = 1;
   const Int_t kMaxHGamTruthMuonsAux = 1;
   const Int_t kMaxHGamAntiKt4TruthJetsAux = 1;
   const Int_t kMaxHGamMET_TruthAux = 1;
   const Int_t kMaxHGamTruthHiggsBosonsAux = 1;
   const Int_t kMaxTruthEventsAux = 1;
   const Int_t kMaxHGamTruthEventInfoAux = 1;
   const Int_t kMaxEventInfoAux = 1;

class CollectionTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   DataVector<xAOD::Photon_v1> *HGamPhotons;
   xAOD::AuxContainerBase *HGamPhotonsAux_;
   vector<int>     *HGamPhotonsAuxDyn_truthOrigin;
   vector<float>   *HGamPhotonsAuxDyn_zvertex;
   vector<int>     *HGamPhotonsAuxDyn_truthType;
   vector<float>   *HGamPhotonsAuxDyn_weta1;
   vector<float>   *HGamPhotonsAuxDyn_weta2;
   vector<float>   *HGamPhotonsAuxDyn_wtots1;
   vector<float>   *HGamPhotonsAuxDyn_scaleFactor;
   vector<float>   *HGamPhotonsAuxDyn_DeltaE;
   vector<float>   *HGamPhotonsAuxDyn_eta_s2;
   vector<char>    *HGamPhotonsAuxDyn_isTight;
   vector<float>   *HGamPhotonsAuxDyn_pt;
   vector<float>   *HGamPhotonsAuxDyn_eta;
   vector<float>   *HGamPhotonsAuxDyn_phi;
   vector<float>   *HGamPhotonsAuxDyn_f1;
   vector<float>   *HGamPhotonsAuxDyn_m;
   vector<float>   *HGamPhotonsAuxDyn_fracs1;
   vector<float>   *HGamPhotonsAuxDyn_cl_E;
   vector<float>   *HGamPhotonsAuxDyn_Eratio;
   vector<unsigned int> *HGamPhotonsAuxDyn_isEMTight;
   vector<float>   *HGamPhotonsAuxDyn_maxEcell_energy;
   vector<int>     *HGamPhotonsAuxDyn_maxEcell_gain;
   vector<unsigned long> *HGamPhotonsAuxDyn_maxEcell_onlId;
   vector<float>   *HGamPhotonsAuxDyn_maxEcell_time;
   vector<char>    *HGamPhotonsAuxDyn_isTight_nofudge;
   vector<float>   *HGamPhotonsAuxDyn_maxEcell_x;
   vector<unsigned int> *HGamPhotonsAuxDyn_isEMTight_nofudge;
   vector<float>   *HGamPhotonsAuxDyn_maxEcell_y;
   vector<float>   *HGamPhotonsAuxDyn_maxEcell_z;
   vector<float>   *HGamPhotonsAuxDyn_Reta;
   vector<int>     *HGamPhotonsAuxDyn_conversionType;
   vector<float>   *HGamPhotonsAuxDyn_Rhad;
   vector<float>   *HGamPhotonsAuxDyn_Rconv;
   vector<float>   *HGamPhotonsAuxDyn_zconv;
   vector<float>   *HGamPhotonsAuxDyn_Rhad1;
   vector<float>   *HGamPhotonsAuxDyn_Rphi;
   vector<float>   *HGamPhotonsAuxDyn_truthRconv;
   vector<unsigned short> *HGamPhotonsAuxDyn_author;
   vector<float>   *HGamPhotonsAuxDyn_ptcone20;
   vector<float>   *HGamPhotonsAuxDyn_ptcone40;
   vector<float>   *HGamPhotonsAuxDyn_maxEcell_eta;
   vector<float>   *HGamPhotonsAuxDyn_maxEcell_phi;
   vector<float>   *HGamPhotonsAuxDyn_topoetcone20_DDcorr;
   vector<float>   *HGamPhotonsAuxDyn_topoetcone40_DDcorr;
   vector<char>    *HGamPhotonsAuxDyn_isIsoFixedCutLoose;
   vector<char>    *HGamPhotonsAuxDyn_isIsoFixedCutTight;
   vector<char>    *HGamPhotonsAuxDyn_isIsoFixedCutTightCaloOnly;
   vector<char>    *HGamPhotonsAuxDyn_isIsoFixedCutLooseCaloOnly;
   vector<float>   *HGamPhotonsAuxDyn_topoetcone20;
   vector<float>   *HGamPhotonsAuxDyn_e277;
   vector<float>   *HGamPhotonsAuxDyn_topoetcone40;
   DataVector<xAOD::Electron_v1> *HGamElectrons;
   xAOD::AuxContainerBase *HGamElectronsAux_;
   DataVector<xAOD::Jet_v1> *HGamAntiKt4EMTopoJets;
   xAOD::AuxContainerBase *HGamAntiKt4EMTopoJetsAux_;
   vector<float>   *HGamAntiKt4EMTopoJetsAuxDyn_SF_MV2c10_FixedCutBEff_60;
   vector<char>    *HGamAntiKt4EMTopoJetsAuxDyn_MV2c10_FixedCutBEff_70;
   vector<double>  *HGamAntiKt4EMTopoJetsAuxDyn_MV2c10_discriminant;
   vector<float>   *HGamAntiKt4EMTopoJetsAuxDyn_Eff_MV2c10_FixedCutBEff_70;
   vector<float>   *HGamAntiKt4EMTopoJetsAuxDyn_InEff_MV2c10_FixedCutBEff_70;
   vector<float>   *HGamAntiKt4EMTopoJetsAuxDyn_SF_MV2c10_FixedCutBEff_70;
   vector<char>    *HGamAntiKt4EMTopoJetsAuxDyn_MV2c10_FixedCutBEff_77;
   vector<float>   *HGamAntiKt4EMTopoJetsAuxDyn_Eff_MV2c10_FixedCutBEff_77;
   vector<float>   *HGamAntiKt4EMTopoJetsAuxDyn_InEff_MV2c10_FixedCutBEff_77;
   vector<float>   *HGamAntiKt4EMTopoJetsAuxDyn_SF_MV2c10_FixedCutBEff_77;
   vector<char>    *HGamAntiKt4EMTopoJetsAuxDyn_MV2c10_FixedCutBEff_85;
   vector<float>   *HGamAntiKt4EMTopoJetsAuxDyn_Eff_MV2c10_FixedCutBEff_85;
   vector<float>   *HGamAntiKt4EMTopoJetsAuxDyn_InEff_MV2c10_FixedCutBEff_85;
   vector<float>   *HGamAntiKt4EMTopoJetsAuxDyn_SF_MV2c10_FixedCutBEff_85;
   vector<char>    *HGamAntiKt4EMTopoJetsAuxDyn_passFJVT;
   vector<float>   *HGamAntiKt4EMTopoJetsAuxDyn_SF_jvt;
   vector<int>     *HGamAntiKt4EMTopoJetsAuxDyn_HadronConeExclTruthLabelID;
   vector<float>   *HGamAntiKt4EMTopoJetsAuxDyn_DetectorEta;
   vector<float>   *HGamAntiKt4EMTopoJetsAuxDyn_pt;
   vector<float>   *HGamAntiKt4EMTopoJetsAuxDyn_Jvt;
   vector<float>   *HGamAntiKt4EMTopoJetsAuxDyn_eta;
   vector<float>   *HGamAntiKt4EMTopoJetsAuxDyn_phi;
   vector<float>   *HGamAntiKt4EMTopoJetsAuxDyn_m;
   vector<char>    *HGamAntiKt4EMTopoJetsAuxDyn_MV2c10_FixedCutBEff_60;
   vector<float>   *HGamAntiKt4EMTopoJetsAuxDyn_Eff_MV2c10_FixedCutBEff_60;
   vector<float>   *HGamAntiKt4EMTopoJetsAuxDyn_InEff_MV2c10_FixedCutBEff_60;
   DataVector<xAOD::Muon_v1> *HGamMuons;
   xAOD::AuxContainerBase *HGamMuonsAux_;
   xAOD::MissingETContainer_v1 *HGamMET_Reference_AntiKt4EMTopo;
   xAOD::AuxContainerBase *HGamMET_Reference_AntiKt4EMTopoAux_;
   vector<double>  *HGamMET_Reference_AntiKt4EMTopoAuxDyn_sumet;
   vector<string>  *HGamMET_Reference_AntiKt4EMTopoAuxDyn_name;
   vector<double>  *HGamMET_Reference_AntiKt4EMTopoAuxDyn_mpx;
   vector<double>  *HGamMET_Reference_AntiKt4EMTopoAuxDyn_mpy;
   vector<ULong64_t> *HGamMET_Reference_AntiKt4EMTopoAuxDyn_source;
   xAOD::EventInfo_v1 *HGamEventInfo;
   xAOD::AuxInfoBase *HGamEventInfoAux_;
   Float_t         HGamEventInfoAuxDyn_m_yy_resolution;
   Char_t          HGamEventInfoAuxDyn_isPassedBasic;
   Int_t           HGamEventInfoAuxDyn_NLoosePhotons;
   Char_t          HGamEventInfoAuxDyn_isPassed;
   Float_t         HGamEventInfoAuxDyn_met_hardVertexTST;
   Char_t          HGamEventInfoAuxDyn_isPassedJetEventClean;
   Float_t         HGamEventInfoAuxDyn_sumet_hardVertexTST;
   Float_t         HGamEventInfoAuxDyn_phi_hardVertexTST;
   Char_t          HGamEventInfoAuxDyn_isPassedIsolationLowHighMyy;
   Char_t          HGamEventInfoAuxDyn_isDalitz;
   Char_t          HGamEventInfoAuxDyn_isPassedRelPtCutsLowHighMyy;
   Int_t           HGamEventInfoAuxDyn_cutFlow;
   Char_t          HGamEventInfoAuxDyn_isPassedLowHighMyy;
   Float_t         HGamEventInfoAuxDyn_weightInitial;
   Char_t          HGamEventInfoAuxDyn_isPassedIsolationExotic;
   Float_t         HGamEventInfoAuxDyn_weight;
   Char_t          HGamEventInfoAuxDyn_isPassedlPtCutsExotic;
   Float_t         HGamEventInfoAuxDyn_weightSF;
   Char_t          HGamEventInfoAuxDyn_isPassedExotic;
   Float_t         HGamEventInfoAuxDyn_vertexWeight;
   Char_t          HGamEventInfoAuxDyn_isPassedExoticTight;
   Float_t         HGamEventInfoAuxDyn_pileupWeight;
   Char_t          HGamEventInfoAuxDyn_isPassedPreselection;
   Float_t         HGamEventInfoAuxDyn_weightCatCoup_Moriond2017;
   Char_t          HGamEventInfoAuxDyn_isPassedTriggerMatch;
   Float_t         HGamEventInfoAuxDyn_weightCatCoup_SFMoriond2017;
   Char_t          HGamEventInfoAuxDyn_isPassedPID;
   Int_t           HGamEventInfoAuxDyn_catCoup_Moriond2017;
   Char_t          HGamEventInfoAuxDyn_isPassedIsolation;
   Float_t         HGamEventInfoAuxDyn_weightCatCoup_Moriond2017BDT;
   Char_t          HGamEventInfoAuxDyn_isPassedRelPtCuts;
   Float_t         HGamEventInfoAuxDyn_weightCatCoup_SFMoriond2017BDT;
   Char_t          HGamEventInfoAuxDyn_isPassedMassCut;
   Int_t           HGamEventInfoAuxDyn_catCoup_Moriond2017BDT;
   Float_t         HGamEventInfoAuxDyn_m_yy_hardestVertex;
   Float_t         HGamEventInfoAuxDyn_weightCatCoup_Moriond2017BDTMET;
   Float_t         HGamEventInfoAuxDyn_m_yy_truthVertex;
   Float_t         HGamEventInfoAuxDyn_weightCatCoup_SFMoriond2017BDTMET;
   Float_t         HGamEventInfoAuxDyn_m_yy_zCommon;
   Float_t         HGamEventInfoAuxDyn_pileupWeight2015;
   Int_t           HGamEventInfoAuxDyn_catCoup_Moriond2017BDTMET;
   vector<float>   *HGamEventInfoAuxDyn_PrimaryVerticesZ;
   Float_t         HGamEventInfoAuxDyn_pileupWeight2016;
   Char_t          HGamEventInfoAuxDyn_catXS_VBF;
   vector<float>   *HGamEventInfoAuxDyn_PrimaryVerticesScore;
   Float_t         HGamEventInfoAuxDyn_pileupWeight15_16iTS;
   Int_t           HGamEventInfoAuxDyn_numberOfPrimaryVertices;
   Float_t         HGamEventInfoAuxDyn_selectedVertexZ;
   Float_t         HGamEventInfoAuxDyn_crossSectionBRfilterEff;
   Float_t         HGamEventInfoAuxDyn_hardestVertexZ;
   Float_t         HGamEventInfoAuxDyn_pileupVertexSumPt2;
   Float_t         HGamEventInfoAuxDyn_pileupVertexZ;
   Float_t         HGamEventInfoAuxDyn_zCommon;
   Float_t         HGamEventInfoAuxDyn_truthVertexZ;
   Int_t           HGamEventInfoAuxDyn_truthCategory;
   Float_t         HGamEventInfoAuxDyn_mu;
   Char_t          HGamEventInfoAuxDyn_isVyyOverlap;
   Float_t         HGamEventInfoAuxDyn_yAbs_yy;
   Float_t         HGamEventInfoAuxDyn_pTt_yy;
   Float_t         HGamEventInfoAuxDyn_m_yy;
   Char_t          HGamEventInfoAuxDyn_passMeyCut;
   Float_t         HGamEventInfoAuxDyn_pT_yy;
   Float_t         HGamEventInfoAuxDyn_pT_y1;
   Float_t         HGamEventInfoAuxDyn_pT_y2;
   Float_t         HGamEventInfoAuxDyn_E_y1;
   Float_t         HGamEventInfoAuxDyn_E_y2;
   Float_t         HGamEventInfoAuxDyn_pT_hard;
   Float_t         HGamEventInfoAuxDyn_cosTS_yy;
   Float_t         HGamEventInfoAuxDyn_phiStar_yy;
   Float_t         HGamEventInfoAuxDyn_Dy_y_y;
   Int_t           HGamEventInfoAuxDyn_N_e;
   Int_t           HGamEventInfoAuxDyn_N_mu;
   Int_t           HGamEventInfoAuxDyn_N_lep;
   Int_t           HGamEventInfoAuxDyn_N_lep_15;
   Float_t         HGamEventInfoAuxDyn_weightN_lep_15;
   Int_t           HGamEventInfoAuxDyn_N_j;
   Int_t           HGamEventInfoAuxDyn_N_j_30;
   Int_t           HGamEventInfoAuxDyn_N_j_50;
   Int_t           HGamEventInfoAuxDyn_N_j_central;
   Int_t           HGamEventInfoAuxDyn_N_j_central30;
   Float_t         HGamEventInfoAuxDyn_pT_j1_30;
   Float_t         HGamEventInfoAuxDyn_yybb_highMass_MVA_score;
   Float_t         HGamEventInfoAuxDyn_pT_j1;
   Float_t         HGamEventInfoAuxDyn_yybb_highMass_m_bb_uncnstrnd;
   Float_t         HGamEventInfoAuxDyn_pT_j2_30;
   Float_t         HGamEventInfoAuxDyn_yybb_highMass_m_yybb;
   Float_t         HGamEventInfoAuxDyn_pT_j2;
   Float_t         HGamEventInfoAuxDyn_yybb_highMass_pT_j1;
   Float_t         HGamEventInfoAuxDyn_pT_j3_30;
   Float_t         HGamEventInfoAuxDyn_yybb_highMass_pT_j2;
   Float_t         HGamEventInfoAuxDyn_yybb_highMass_weight;
   Float_t         HGamEventInfoAuxDyn_yAbs_j1_30;
   Float_t         HGamEventInfoAuxDyn_yybb_highMass_weight_discreteSFs;
   Float_t         HGamEventInfoAuxDyn_yybb_lowMass_MVA_score;
   Float_t         HGamEventInfoAuxDyn_yAbs_j2_30;
   Float_t         HGamEventInfoAuxDyn_yybb_lowMass_m_bb_uncnstrnd;
   Float_t         HGamEventInfoAuxDyn_pT_jj;
   Float_t         HGamEventInfoAuxDyn_yybb_lowMass_m_yybb;
   Float_t         HGamEventInfoAuxDyn_yybb_lowMass_pT_j1;
   Float_t         HGamEventInfoAuxDyn_m_jj;
   Float_t         HGamEventInfoAuxDyn_yybb_lowMass_pT_j2;
   Float_t         HGamEventInfoAuxDyn_yybb_lowMass_weight;
   Float_t         HGamEventInfoAuxDyn_m_jj_30;
   Float_t         HGamEventInfoAuxDyn_yybb_lowMass_weight_discreteSFs;
   Float_t         HGamEventInfoAuxDyn_Dy_j_j;
   Float_t         HGamEventInfoAuxDyn_Deta_j_j;
   Int_t           HGamEventInfoAuxDyn_yybb_bTagCat;
   Int_t           HGamEventInfoAuxDyn_yybb_highMass_cutFlow;
   Float_t         HGamEventInfoAuxDyn_Dy_j_j_30;
   Int_t           HGamEventInfoAuxDyn_yybb_highMass_truth_label_j1;
   Float_t         HGamEventInfoAuxDyn_Dy_yy_jj;
   Int_t           HGamEventInfoAuxDyn_yybb_highMass_truth_label_j2;
   Float_t         HGamEventInfoAuxDyn_Dy_yy_jj_30;
   Int_t           HGamEventInfoAuxDyn_yybb_lowMass_cutFlow;
   Float_t         HGamEventInfoAuxDyn_Dphi_j_j;
   Int_t           HGamEventInfoAuxDyn_yybb_lowMass_truth_label_j1;
   Float_t         HGamEventInfoAuxDyn_Dphi_j_j_30;
   Int_t           HGamEventInfoAuxDyn_yybb_lowMass_truth_label_j2;
   Float_t         HGamEventInfoAuxDyn_Dphi_j_j_30_signed;
   Int_t           HGamEventInfoAuxDyn_met_cat;
   Float_t         HGamEventInfoAuxDyn_Dphi_yy_jj;
   Float_t         HGamEventInfoAuxDyn_met_weight;
   Float_t         HGamEventInfoAuxDyn_Dphi_yy_jj_30;
   Float_t         HGamEventInfoAuxDyn_fcnc_etm;
   Float_t         HGamEventInfoAuxDyn_fcnc_mT;
   Float_t         HGamEventInfoAuxDyn_fcnc_phim;
   Float_t         HGamEventInfoAuxDyn_pT_yyjj_30;
   Float_t         HGamEventInfoAuxDyn_fcnc_weight;
   Float_t         HGamEventInfoAuxDyn_m_ee;
   Int_t           HGamEventInfoAuxDyn_fcnc_cat;
   Float_t         HGamEventInfoAuxDyn_m_mumu;
   Int_t           HGamEventInfoAuxDyn_fcnc_cutFlow;
   Float_t         HGamEventInfoAuxDyn_DRmin_y_j;
   Int_t           HGamEventInfoAuxDyn_fcnc_idLep;
   Float_t         HGamEventInfoAuxDyn_DRmin_y_j_2;
   Int_t           HGamEventInfoAuxDyn_fcnc_njet;
   Float_t         HGamEventInfoAuxDyn_DR_y_y;
   Int_t           HGamEventInfoAuxDyn_fcnc_njet30;
   Float_t         HGamEventInfoAuxDyn_Zepp;
   Int_t           HGamEventInfoAuxDyn_fcnc_ntopc;
   Float_t         HGamEventInfoAuxDyn_cosTS_yyjj;
   vector<int>     *HGamEventInfoAuxDyn_fcnc_nbTop2;
   Float_t         HGamEventInfoAuxDyn_sumTau_yyj_30;
   vector<float>   *HGamEventInfoAuxDyn_fcnc_mTop1;
   Float_t         HGamEventInfoAuxDyn_maxTau_yyj_30;
   vector<float>   *HGamEventInfoAuxDyn_fcnc_mTop2;
   Float_t         HGamEventInfoAuxDyn_met_TST;
   Float_t         HGamEventInfoAuxDyn_weightJvt;
   Float_t         HGamEventInfoAuxDyn_sumet_TST;
   Float_t         HGamEventInfoAuxDyn_weightJvt_30;
   Float_t         HGamEventInfoAuxDyn_phi_TST;
   Float_t         HGamEventInfoAuxDyn_weightJvt_50;
   Int_t           HGamEventInfoAuxDyn_N_j_btag;
   Float_t         HGamEventInfoAuxDyn_HT_30;
   Int_t           HGamEventInfoAuxDyn_N_j_btag30;
   Float_t         HGamEventInfoAuxDyn_HTall_30;
   Float_t         HGamEventInfoAuxDyn_m_alljet_30;
   Char_t          HGamEventInfoAuxDyn_catXS_ttH;
   Float_t         HGamEventInfoAuxDyn_weightCatXS_ttH;
   Float_t         HGamEventInfoAuxDyn_m_alljet;
   DataVector<xAOD::TruthParticle_v1> *HGamTruthPhotons;
   xAOD::AuxContainerBase *HGamTruthPhotonsAux_;
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
   DataVector<xAOD::TruthParticle_v1> *HGamTruthElectrons;
   xAOD::AuxContainerBase *HGamTruthElectronsAux_;
   DataVector<xAOD::TruthParticle_v1> *HGamTruthMuons;
   xAOD::AuxContainerBase *HGamTruthMuonsAux_;
   DataVector<xAOD::Jet_v1> *HGamAntiKt4TruthJets;
   xAOD::AuxContainerBase *HGamAntiKt4TruthJetsAux_;
   vector<float>   *HGamAntiKt4TruthJetsAuxDyn_pt;
   vector<float>   *HGamAntiKt4TruthJetsAuxDyn_eta;
   vector<int>     *HGamAntiKt4TruthJetsAuxDyn_HadronConeExclTruthLabelID;
   vector<float>   *HGamAntiKt4TruthJetsAuxDyn_phi;
   vector<float>   *HGamAntiKt4TruthJetsAuxDyn_m;
   DataVector<xAOD::MissingET_v1> *HGamMET_Truth;
   xAOD::AuxContainerBase *HGamMET_TruthAux_;
   vector<double>  *HGamMET_TruthAuxDyn_sumet;
   vector<string>  *HGamMET_TruthAuxDyn_name;
   vector<double>  *HGamMET_TruthAuxDyn_mpx;
   vector<double>  *HGamMET_TruthAuxDyn_mpy;
   vector<ULong64_t> *HGamMET_TruthAuxDyn_source;
   DataVector<xAOD::TruthParticle_v1> *HGamTruthHiggsBosons;
   xAOD::AuxContainerBase *HGamTruthHiggsBosonsAux_;
   vector<float>   *HGamTruthHiggsBosonsAuxDyn_pt;
   vector<float>   *HGamTruthHiggsBosonsAuxDyn_eta;
   vector<float>   *HGamTruthHiggsBosonsAuxDyn_px;
   vector<float>   *HGamTruthHiggsBosonsAuxDyn_m;
   vector<float>   *HGamTruthHiggsBosonsAuxDyn_py;
   vector<float>   *HGamTruthHiggsBosonsAuxDyn_pz;
   vector<float>   *HGamTruthHiggsBosonsAuxDyn_e;
   DataVector<xAOD::TruthEvent_v1> *TruthEvents;
   xAOD::AuxContainerBase *TruthEventsAux_;
   vector<vector<float> > *TruthEventsAuxDyn_weights;
   vector<int>     *TruthEventsAuxDyn_PDFID1;
   vector<int>     *TruthEventsAuxDyn_PDFID2;
   vector<int>     *TruthEventsAuxDyn_PDGID1;
   vector<int>     *TruthEventsAuxDyn_PDGID2;
   vector<float>   *TruthEventsAuxDyn_Q;
   vector<float>   *TruthEventsAuxDyn_X1;
   vector<float>   *TruthEventsAuxDyn_X2;
   vector<float>   *TruthEventsAuxDyn_XF1;
   vector<float>   *TruthEventsAuxDyn_XF2;
   xAOD::EventInfo_v1 *HGamTruthEventInfo;
   xAOD::AuxInfoBase *HGamTruthEventInfoAux_;
   Float_t         HGamTruthEventInfoAuxDyn_HTall_30;
   Char_t          HGamTruthEventInfoAuxDyn_isFiducial;
   Char_t          HGamTruthEventInfoAuxDyn_isFiducialKinOnly;
   Int_t           HGamTruthEventInfoAuxDyn_N_j_btag30;
   Char_t          HGamTruthEventInfoAuxDyn_catXS_VBF;
   Float_t         HGamTruthEventInfoAuxDyn_pT_h1;
   Char_t          HGamTruthEventInfoAuxDyn_catXS_ttH;
   Float_t         HGamTruthEventInfoAuxDyn_pT_h2;
   Float_t         HGamTruthEventInfoAuxDyn_y_h1;
   Float_t         HGamTruthEventInfoAuxDyn_y_h2;
   Float_t         HGamTruthEventInfoAuxDyn_m_h1;
   Float_t         HGamTruthEventInfoAuxDyn_m_h2;
   Float_t         HGamTruthEventInfoAuxDyn_yAbs_yy;
   Float_t         HGamTruthEventInfoAuxDyn_pTt_yy;
   Float_t         HGamTruthEventInfoAuxDyn_m_yy;
   Char_t          HGamTruthEventInfoAuxDyn_passMeyCut;
   Int_t           HGamTruthEventInfoAuxDyn_truthCategory;
   Float_t         HGamTruthEventInfoAuxDyn_pT_yy;
   Int_t           HGamTruthEventInfoAuxDyn_truthProcess;
   Float_t         HGamTruthEventInfoAuxDyn_pT_y1;
   Float_t         HGamTruthEventInfoAuxDyn_pT_y2;
   Char_t          HGamTruthEventInfoAuxDyn_isVyyOverlap;
   Float_t         HGamTruthEventInfoAuxDyn_E_y1;
   Float_t         HGamTruthEventInfoAuxDyn_E_y2;
   Float_t         HGamTruthEventInfoAuxDyn_pT_hard;
   Float_t         HGamTruthEventInfoAuxDyn_cosTS_yy;
   Float_t         HGamTruthEventInfoAuxDyn_phiStar_yy;
   Float_t         HGamTruthEventInfoAuxDyn_Dy_y_y;
   Int_t           HGamTruthEventInfoAuxDyn_N_e;
   Int_t           HGamTruthEventInfoAuxDyn_N_mu;
   Int_t           HGamTruthEventInfoAuxDyn_N_lep;
   Int_t           HGamTruthEventInfoAuxDyn_N_lep_15;
   Int_t           HGamTruthEventInfoAuxDyn_N_j;
   Int_t           HGamTruthEventInfoAuxDyn_N_j_30;
   Int_t           HGamTruthEventInfoAuxDyn_N_j_50;
   Int_t           HGamTruthEventInfoAuxDyn_N_j_central;
   Int_t           HGamTruthEventInfoAuxDyn_N_j_central30;
   Float_t         HGamTruthEventInfoAuxDyn_pT_j1_30;
   Float_t         HGamTruthEventInfoAuxDyn_pT_j1;
   Float_t         HGamTruthEventInfoAuxDyn_pT_j2_30;
   Float_t         HGamTruthEventInfoAuxDyn_pT_j2;
   Float_t         HGamTruthEventInfoAuxDyn_pT_j3_30;
   Float_t         HGamTruthEventInfoAuxDyn_met_NonInt;
   Float_t         HGamTruthEventInfoAuxDyn_yAbs_j1_30;
   Float_t         HGamTruthEventInfoAuxDyn_sumet_Int;
   Float_t         HGamTruthEventInfoAuxDyn_met_NonHad;
   Float_t         HGamTruthEventInfoAuxDyn_yAbs_j2_30;
   Char_t          HGamTruthEventInfoAuxDyn_isFiducialLowHighMyy;
   Float_t         HGamTruthEventInfoAuxDyn_pT_jj;
   Char_t          HGamTruthEventInfoAuxDyn_isFiducialExotic;
   Float_t         HGamTruthEventInfoAuxDyn_m_jj;
   Float_t         HGamTruthEventInfoAuxDyn_m_jj_30;
   Float_t         HGamTruthEventInfoAuxDyn_Dy_j_j;
   Float_t         HGamTruthEventInfoAuxDyn_Dy_j_j_30;
   Float_t         HGamTruthEventInfoAuxDyn_Dy_yy_jj_30;
   Float_t         HGamTruthEventInfoAuxDyn_Dphi_j_j;
   Float_t         HGamTruthEventInfoAuxDyn_Dphi_j_j_30;
   Float_t         HGamTruthEventInfoAuxDyn_Dphi_j_j_30_signed;
   Float_t         HGamTruthEventInfoAuxDyn_Dphi_yy_jj;
   Float_t         HGamTruthEventInfoAuxDyn_Dphi_yy_jj_30;
   Float_t         HGamTruthEventInfoAuxDyn_pT_yyjj_30;
   Float_t         HGamTruthEventInfoAuxDyn_m_ee;
   Float_t         HGamTruthEventInfoAuxDyn_m_mumu;
   Float_t         HGamTruthEventInfoAuxDyn_DRmin_y_j;
   Float_t         HGamTruthEventInfoAuxDyn_DR_y_y;
   Float_t         HGamTruthEventInfoAuxDyn_Zepp;
   Float_t         HGamTruthEventInfoAuxDyn_cosTS_yyjj;
   Float_t         HGamTruthEventInfoAuxDyn_sumTau_yyj_30;
   Float_t         HGamTruthEventInfoAuxDyn_maxTau_yyj_30;
   Float_t         HGamTruthEventInfoAuxDyn_HT_30;
   xAOD::EventInfo_v1 *EventInfo;
 //xAOD::EventAuxInfo_v1 *EventInfoAux_;
 //xAOD::EventAuxInfo_v1 *EventInfoAux_xAOD__AuxInfoBase;
   UInt_t          EventInfoAux_runNumber;
   ULong64_t       EventInfoAux_eventNumber;
   UInt_t          EventInfoAux_lumiBlock;
   UInt_t          EventInfoAux_timeStamp;
   UInt_t          EventInfoAux_timeStampNSOffset;
   UInt_t          EventInfoAux_bcid;
   UInt_t          EventInfoAux_detectorMask0;
   UInt_t          EventInfoAux_detectorMask1;
   UInt_t          EventInfoAux_detectorMask2;
   UInt_t          EventInfoAux_detectorMask3;
 //vector<pair<string,string> > EventInfoAux_detDescrTags;
   UInt_t          EventInfoAux_eventTypeBitmask;
   UInt_t          EventInfoAux_statusElement;
   UInt_t          EventInfoAux_extendedLevel1ID;
   UShort_t        EventInfoAux_level1TriggerType;
   vector<string>  EventInfoAux_streamTagNames;
   vector<string>  EventInfoAux_streamTagTypes;
   vector<char>    EventInfoAux_streamTagObeysLumiblock;
   Float_t         EventInfoAux_actualInteractionsPerCrossing;
   Float_t         EventInfoAux_averageInteractionsPerCrossing;
   UInt_t          EventInfoAux_pixelFlags;
   UInt_t          EventInfoAux_sctFlags;
   UInt_t          EventInfoAux_trtFlags;
   UInt_t          EventInfoAux_larFlags;
   UInt_t          EventInfoAux_tileFlags;
   UInt_t          EventInfoAux_muonFlags;
   UInt_t          EventInfoAux_forwardDetFlags;
   UInt_t          EventInfoAux_coreFlags;
   UInt_t          EventInfoAux_backgroundFlags;
   UInt_t          EventInfoAux_lumiFlags;
   Float_t         EventInfoAux_beamPosX;
   Float_t         EventInfoAux_beamPosY;
   Float_t         EventInfoAux_beamPosZ;
   Float_t         EventInfoAux_beamPosSigmaX;
   Float_t         EventInfoAux_beamPosSigmaY;
   Float_t         EventInfoAux_beamPosSigmaZ;
   Float_t         EventInfoAux_beamPosSigmaXY;
   Float_t         EventInfoAux_beamTiltXZ;
   Float_t         EventInfoAux_beamTiltYZ;
   UInt_t          EventInfoAux_beamStatus;
   vector<float>   *EventInfoAuxDyn_mcEventWeights;
   Int_t           EventInfoAuxDyn_HTXS_Stage1_Category_pTjet30;
   Int_t           EventInfoAuxDyn_HTXS_Stage1_FineIndex_pTjet25;
   Int_t           EventInfoAuxDyn_HTXS_Stage1_FineIndex_pTjet30;
   vector<float>   *EventInfoAuxDyn_HTXS_V_jets30_eta;
   Char_t          EventInfoAuxDyn_passTrig_HLT_g35_loose_g25_loose;
   vector<float>   *EventInfoAuxDyn_HTXS_V_jets30_m;
   vector<float>   *EventInfoAuxDyn_HTXS_V_jets30_phi;
   vector<float>   *EventInfoAuxDyn_HTXS_V_jets30_pt;
   Float_t         EventInfoAuxDyn_HTXS_V_pt;
   Char_t          EventInfoAuxDyn_passTrig_HLT_g35_medium_g25_medium;
   Int_t           EventInfoAuxDyn_HTXS_errorCode;
   Int_t           EventInfoAuxDyn_HTXS_Njets_pTjet25;
   Char_t          EventInfoAuxDyn_passTrig_HLT_2g50_loose;
   Int_t           EventInfoAuxDyn_HTXS_prodMode;
   Int_t           EventInfoAuxDyn_HTXS_Njets_pTjet30;
   UInt_t          EventInfoAuxDyn_mcChannelNumber;
   Int_t           EventInfoAuxDyn_HTXS_Stage0_Category;
   Int_t           EventInfoAuxDyn_HTXS_Stage1_Category_pTjet25;
   vector<ElementLink<DataVector<xAOD::IParticle> > > *HGamPhotonsAuxDyn_truthLink;
   vector<int>     *HGamPhotonsAuxDyn_parentPdgId;
   vector<int>     *HGamPhotonsAuxDyn_pdgId;
   vector<ElementLink<DataVector<xAOD::IParticle> > > *HGamTruthPhotonsAuxDyn_recoLink;
   vector<float>   *HGamElectronsAuxDyn_scaleFactor;
   vector<float>   *HGamElectronsAuxDyn_ptvarcone20;
   vector<float>   *HGamElectronsAuxDyn_pt;
   vector<float>   *HGamElectronsAuxDyn_eta;
   vector<float>   *HGamElectronsAuxDyn_topoetcone20;
   vector<float>   *HGamElectronsAuxDyn_phi;
   vector<float>   *HGamElectronsAuxDyn_m;
   vector<float>   *HGamElectronsAuxDyn_eta_s2;
   vector<float>   *HGamElectronsAuxDyn_charge;
   vector<char>    *HGamElectronsAuxDyn_isTight;
   vector<int>     *HGamTruthElectronsAuxDyn_truthOrigin;
   vector<float>   *HGamTruthElectronsAuxDyn_pt;
   vector<int>     *HGamTruthElectronsAuxDyn_truthType;
   vector<float>   *HGamTruthElectronsAuxDyn_eta;
   vector<float>   *HGamTruthElectronsAuxDyn_px;
   vector<float>   *HGamTruthElectronsAuxDyn_m;
   vector<float>   *HGamTruthElectronsAuxDyn_py;
   vector<float>   *HGamTruthElectronsAuxDyn_pz;
   vector<float>   *HGamTruthElectronsAuxDyn_e;
   vector<ElementLink<DataVector<xAOD::IParticle> > > *HGamElectronsAuxDyn_truthLink;
   vector<ElementLink<DataVector<xAOD::IParticle> > > *HGamTruthElectronsAuxDyn_recoLink;
   vector<int>     *HGamTruthMuonsAuxDyn_truthOrigin;
   vector<float>   *HGamTruthMuonsAuxDyn_pt;
   vector<int>     *HGamTruthMuonsAuxDyn_truthType;
   vector<float>   *HGamTruthMuonsAuxDyn_eta;
   vector<float>   *HGamTruthMuonsAuxDyn_px;
   vector<float>   *HGamTruthMuonsAuxDyn_m;
   vector<float>   *HGamTruthMuonsAuxDyn_py;
   vector<float>   *HGamTruthMuonsAuxDyn_pz;
   vector<float>   *HGamTruthMuonsAuxDyn_e;
   vector<float>   *HGamMuonsAuxDyn_scaleFactor;
   vector<float>   *HGamMuonsAuxDyn_ptvarcone20;
   vector<float>   *HGamMuonsAuxDyn_pt;
   vector<char>    *HGamMuonsAuxDyn_isBad;
   vector<char>    *HGamMuonsAuxDyn_passIPCut;
   vector<float>   *HGamMuonsAuxDyn_eta;
   vector<float>   *HGamMuonsAuxDyn_topoetcone20;
   vector<float>   *HGamMuonsAuxDyn_phi;
   vector<unsigned short> *HGamMuonsAuxDyn_muonType;
   vector<float>   *HGamMuonsAuxDyn_charge;
   vector<char>    *HGamMuonsAuxDyn_isTight;
   Float_t         HGamEventInfoAuxDyn_pT_yyjj;

   // List of branches
   TBranch        *b_HGamPhotons;   //!
   TBranch        *b_HGamPhotonsAux_;   //!
   TBranch        *b_HGamPhotonsAuxDyn_truthOrigin;   //!
   TBranch        *b_HGamPhotonsAuxDyn_zvertex;   //!
   TBranch        *b_HGamPhotonsAuxDyn_truthType;   //!
   TBranch        *b_HGamPhotonsAuxDyn_weta1;   //!
   TBranch        *b_HGamPhotonsAuxDyn_weta2;   //!
   TBranch        *b_HGamPhotonsAuxDyn_wtots1;   //!
   TBranch        *b_HGamPhotonsAuxDyn_scaleFactor;   //!
   TBranch        *b_HGamPhotonsAuxDyn_DeltaE;   //!
   TBranch        *b_HGamPhotonsAuxDyn_eta_s2;   //!
   TBranch        *b_HGamPhotonsAuxDyn_isTight;   //!
   TBranch        *b_HGamPhotonsAuxDyn_pt;   //!
   TBranch        *b_HGamPhotonsAuxDyn_eta;   //!
   TBranch        *b_HGamPhotonsAuxDyn_phi;   //!
   TBranch        *b_HGamPhotonsAuxDyn_f1;   //!
   TBranch        *b_HGamPhotonsAuxDyn_m;   //!
   TBranch        *b_HGamPhotonsAuxDyn_fracs1;   //!
   TBranch        *b_HGamPhotonsAuxDyn_cl_E;   //!
   TBranch        *b_HGamPhotonsAuxDyn_Eratio;   //!
   TBranch        *b_HGamPhotonsAuxDyn_isEMTight;   //!
   TBranch        *b_HGamPhotonsAuxDyn_maxEcell_energy;   //!
   TBranch        *b_HGamPhotonsAuxDyn_maxEcell_gain;   //!
   TBranch        *b_HGamPhotonsAuxDyn_maxEcell_onlId;   //!
   TBranch        *b_HGamPhotonsAuxDyn_maxEcell_time;   //!
   TBranch        *b_HGamPhotonsAuxDyn_isTight_nofudge;   //!
   TBranch        *b_HGamPhotonsAuxDyn_maxEcell_x;   //!
   TBranch        *b_HGamPhotonsAuxDyn_isEMTight_nofudge;   //!
   TBranch        *b_HGamPhotonsAuxDyn_maxEcell_y;   //!
   TBranch        *b_HGamPhotonsAuxDyn_maxEcell_z;   //!
   TBranch        *b_HGamPhotonsAuxDyn_Reta;   //!
   TBranch        *b_HGamPhotonsAuxDyn_conversionType;   //!
   TBranch        *b_HGamPhotonsAuxDyn_Rhad;   //!
   TBranch        *b_HGamPhotonsAuxDyn_Rconv;   //!
   TBranch        *b_HGamPhotonsAuxDyn_zconv;   //!
   TBranch        *b_HGamPhotonsAuxDyn_Rhad1;   //!
   TBranch        *b_HGamPhotonsAuxDyn_Rphi;   //!
   TBranch        *b_HGamPhotonsAuxDyn_truthRconv;   //!
   TBranch        *b_HGamPhotonsAuxDyn_author;   //!
   TBranch        *b_HGamPhotonsAuxDyn_ptcone20;   //!
   TBranch        *b_HGamPhotonsAuxDyn_ptcone40;   //!
   TBranch        *b_HGamPhotonsAuxDyn_maxEcell_eta;   //!
   TBranch        *b_HGamPhotonsAuxDyn_maxEcell_phi;   //!
   TBranch        *b_HGamPhotonsAuxDyn_topoetcone20_DDcorr;   //!
   TBranch        *b_HGamPhotonsAuxDyn_topoetcone40_DDcorr;   //!
   TBranch        *b_HGamPhotonsAuxDyn_isIsoFixedCutLoose;   //!
   TBranch        *b_HGamPhotonsAuxDyn_isIsoFixedCutTight;   //!
   TBranch        *b_HGamPhotonsAuxDyn_isIsoFixedCutTightCaloOnly;   //!
   TBranch        *b_HGamPhotonsAuxDyn_isIsoFixedCutLooseCaloOnly;   //!
   TBranch        *b_HGamPhotonsAuxDyn_topoetcone20;   //!
   TBranch        *b_HGamPhotonsAuxDyn_e277;   //!
   TBranch        *b_HGamPhotonsAuxDyn_topoetcone40;   //!
   TBranch        *b_HGamElectrons;   //!
   TBranch        *b_HGamElectronsAux_;   //!
   TBranch        *b_HGamAntiKt4EMTopoJets;   //!
   TBranch        *b_HGamAntiKt4EMTopoJetsAux_;   //!
   TBranch        *b_HGamAntiKt4EMTopoJetsAuxDyn_SF_MV2c10_FixedCutBEff_60;   //!
   TBranch        *b_HGamAntiKt4EMTopoJetsAuxDyn_MV2c10_FixedCutBEff_70;   //!
   TBranch        *b_HGamAntiKt4EMTopoJetsAuxDyn_MV2c10_discriminant;   //!
   TBranch        *b_HGamAntiKt4EMTopoJetsAuxDyn_Eff_MV2c10_FixedCutBEff_70;   //!
   TBranch        *b_HGamAntiKt4EMTopoJetsAuxDyn_InEff_MV2c10_FixedCutBEff_70;   //!
   TBranch        *b_HGamAntiKt4EMTopoJetsAuxDyn_SF_MV2c10_FixedCutBEff_70;   //!
   TBranch        *b_HGamAntiKt4EMTopoJetsAuxDyn_MV2c10_FixedCutBEff_77;   //!
   TBranch        *b_HGamAntiKt4EMTopoJetsAuxDyn_Eff_MV2c10_FixedCutBEff_77;   //!
   TBranch        *b_HGamAntiKt4EMTopoJetsAuxDyn_InEff_MV2c10_FixedCutBEff_77;   //!
   TBranch        *b_HGamAntiKt4EMTopoJetsAuxDyn_SF_MV2c10_FixedCutBEff_77;   //!
   TBranch        *b_HGamAntiKt4EMTopoJetsAuxDyn_MV2c10_FixedCutBEff_85;   //!
   TBranch        *b_HGamAntiKt4EMTopoJetsAuxDyn_Eff_MV2c10_FixedCutBEff_85;   //!
   TBranch        *b_HGamAntiKt4EMTopoJetsAuxDyn_InEff_MV2c10_FixedCutBEff_85;   //!
   TBranch        *b_HGamAntiKt4EMTopoJetsAuxDyn_SF_MV2c10_FixedCutBEff_85;   //!
   TBranch        *b_HGamAntiKt4EMTopoJetsAuxDyn_passFJVT;   //!
   TBranch        *b_HGamAntiKt4EMTopoJetsAuxDyn_SF_jvt;   //!
   TBranch        *b_HGamAntiKt4EMTopoJetsAuxDyn_HadronConeExclTruthLabelID;   //!
   TBranch        *b_HGamAntiKt4EMTopoJetsAuxDyn_DetectorEta;   //!
   TBranch        *b_HGamAntiKt4EMTopoJetsAuxDyn_pt;   //!
   TBranch        *b_HGamAntiKt4EMTopoJetsAuxDyn_Jvt;   //!
   TBranch        *b_HGamAntiKt4EMTopoJetsAuxDyn_eta;   //!
   TBranch        *b_HGamAntiKt4EMTopoJetsAuxDyn_phi;   //!
   TBranch        *b_HGamAntiKt4EMTopoJetsAuxDyn_m;   //!
   TBranch        *b_HGamAntiKt4EMTopoJetsAuxDyn_MV2c10_FixedCutBEff_60;   //!
   TBranch        *b_HGamAntiKt4EMTopoJetsAuxDyn_Eff_MV2c10_FixedCutBEff_60;   //!
   TBranch        *b_HGamAntiKt4EMTopoJetsAuxDyn_InEff_MV2c10_FixedCutBEff_60;   //!
   TBranch        *b_HGamMuons;   //!
   TBranch        *b_HGamMuonsAux_;   //!
   TBranch        *b_HGamMET_Reference_AntiKt4EMTopo;   //!
   TBranch        *b_HGamMET_Reference_AntiKt4EMTopoAux_;   //!
   TBranch        *b_HGamMET_Reference_AntiKt4EMTopoAuxDyn_sumet;   //!
   TBranch        *b_HGamMET_Reference_AntiKt4EMTopoAuxDyn_name;   //!
   TBranch        *b_HGamMET_Reference_AntiKt4EMTopoAuxDyn_mpx;   //!
   TBranch        *b_HGamMET_Reference_AntiKt4EMTopoAuxDyn_mpy;   //!
   TBranch        *b_HGamMET_Reference_AntiKt4EMTopoAuxDyn_source;   //!
   TBranch        *b_HGamEventInfo;   //!
   TBranch        *b_HGamEventInfoAux_;   //!
   TBranch        *b_HGamEventInfoAuxDyn_m_yy_resolution;   //!
   TBranch        *b_HGamEventInfoAuxDyn_isPassedBasic;   //!
   TBranch        *b_HGamEventInfoAuxDyn_NLoosePhotons;   //!
   TBranch        *b_HGamEventInfoAuxDyn_isPassed;   //!
   TBranch        *b_HGamEventInfoAuxDyn_met_hardVertexTST;   //!
   TBranch        *b_HGamEventInfoAuxDyn_isPassedJetEventClean;   //!
   TBranch        *b_HGamEventInfoAuxDyn_sumet_hardVertexTST;   //!
   TBranch        *b_HGamEventInfoAuxDyn_phi_hardVertexTST;   //!
   TBranch        *b_HGamEventInfoAuxDyn_isPassedIsolationLowHighMyy;   //!
   TBranch        *b_HGamEventInfoAuxDyn_isDalitz;   //!
   TBranch        *b_HGamEventInfoAuxDyn_isPassedRelPtCutsLowHighMyy;   //!
   TBranch        *b_HGamEventInfoAuxDyn_cutFlow;   //!
   TBranch        *b_HGamEventInfoAuxDyn_isPassedLowHighMyy;   //!
   TBranch        *b_HGamEventInfoAuxDyn_weightInitial;   //!
   TBranch        *b_HGamEventInfoAuxDyn_isPassedIsolationExotic;   //!
   TBranch        *b_HGamEventInfoAuxDyn_weight;   //!
   TBranch        *b_HGamEventInfoAuxDyn_isPassedlPtCutsExotic;   //!
   TBranch        *b_HGamEventInfoAuxDyn_weightSF;   //!
   TBranch        *b_HGamEventInfoAuxDyn_isPassedExotic;   //!
   TBranch        *b_HGamEventInfoAuxDyn_vertexWeight;   //!
   TBranch        *b_HGamEventInfoAuxDyn_isPassedExoticTight;   //!
   TBranch        *b_HGamEventInfoAuxDyn_pileupWeight;   //!
   TBranch        *b_HGamEventInfoAuxDyn_isPassedPreselection;   //!
   TBranch        *b_HGamEventInfoAuxDyn_weightCatCoup_Moriond2017;   //!
   TBranch        *b_HGamEventInfoAuxDyn_isPassedTriggerMatch;   //!
   TBranch        *b_HGamEventInfoAuxDyn_weightCatCoup_SFMoriond2017;   //!
   TBranch        *b_HGamEventInfoAuxDyn_isPassedPID;   //!
   TBranch        *b_HGamEventInfoAuxDyn_catCoup_Moriond2017;   //!
   TBranch        *b_HGamEventInfoAuxDyn_isPassedIsolation;   //!
   TBranch        *b_HGamEventInfoAuxDyn_weightCatCoup_Moriond2017BDT;   //!
   TBranch        *b_HGamEventInfoAuxDyn_isPassedRelPtCuts;   //!
   TBranch        *b_HGamEventInfoAuxDyn_weightCatCoup_SFMoriond2017BDT;   //!
   TBranch        *b_HGamEventInfoAuxDyn_isPassedMassCut;   //!
   TBranch        *b_HGamEventInfoAuxDyn_catCoup_Moriond2017BDT;   //!
   TBranch        *b_HGamEventInfoAuxDyn_m_yy_hardestVertex;   //!
   TBranch        *b_HGamEventInfoAuxDyn_weightCatCoup_Moriond2017BDTMET;   //!
   TBranch        *b_HGamEventInfoAuxDyn_m_yy_truthVertex;   //!
   TBranch        *b_HGamEventInfoAuxDyn_weightCatCoup_SFMoriond2017BDTMET;   //!
   TBranch        *b_HGamEventInfoAuxDyn_m_yy_zCommon;   //!
   TBranch        *b_HGamEventInfoAuxDyn_pileupWeight2015;   //!
   TBranch        *b_HGamEventInfoAuxDyn_catCoup_Moriond2017BDTMET;   //!
   TBranch        *b_HGamEventInfoAuxDyn_PrimaryVerticesZ;   //!
   TBranch        *b_HGamEventInfoAuxDyn_pileupWeight2016;   //!
   TBranch        *b_HGamEventInfoAuxDyn_catXS_VBF;   //!
   TBranch        *b_HGamEventInfoAuxDyn_PrimaryVerticesScore;   //!
   TBranch        *b_HGamEventInfoAuxDyn_pileupWeight15_16iTS;   //!
   TBranch        *b_HGamEventInfoAuxDyn_numberOfPrimaryVertices;   //!
   TBranch        *b_HGamEventInfoAuxDyn_selectedVertexZ;   //!
   TBranch        *b_HGamEventInfoAuxDyn_crossSectionBRfilterEff;   //!
   TBranch        *b_HGamEventInfoAuxDyn_hardestVertexZ;   //!
   TBranch        *b_HGamEventInfoAuxDyn_pileupVertexSumPt2;   //!
   TBranch        *b_HGamEventInfoAuxDyn_pileupVertexZ;   //!
   TBranch        *b_HGamEventInfoAuxDyn_zCommon;   //!
   TBranch        *b_HGamEventInfoAuxDyn_truthVertexZ;   //!
   TBranch        *b_HGamEventInfoAuxDyn_truthCategory;   //!
   TBranch        *b_HGamEventInfoAuxDyn_mu;   //!
   TBranch        *b_HGamEventInfoAuxDyn_isVyyOverlap;   //!
   TBranch        *b_HGamEventInfoAuxDyn_yAbs_yy;   //!
   TBranch        *b_HGamEventInfoAuxDyn_pTt_yy;   //!
   TBranch        *b_HGamEventInfoAuxDyn_m_yy;   //!
   TBranch        *b_HGamEventInfoAuxDyn_passMeyCut;   //!
   TBranch        *b_HGamEventInfoAuxDyn_pT_yy;   //!
   TBranch        *b_HGamEventInfoAuxDyn_pT_y1;   //!
   TBranch        *b_HGamEventInfoAuxDyn_pT_y2;   //!
   TBranch        *b_HGamEventInfoAuxDyn_E_y1;   //!
   TBranch        *b_HGamEventInfoAuxDyn_E_y2;   //!
   TBranch        *b_HGamEventInfoAuxDyn_pT_hard;   //!
   TBranch        *b_HGamEventInfoAuxDyn_cosTS_yy;   //!
   TBranch        *b_HGamEventInfoAuxDyn_phiStar_yy;   //!
   TBranch        *b_HGamEventInfoAuxDyn_Dy_y_y;   //!
   TBranch        *b_HGamEventInfoAuxDyn_N_e;   //!
   TBranch        *b_HGamEventInfoAuxDyn_N_mu;   //!
   TBranch        *b_HGamEventInfoAuxDyn_N_lep;   //!
   TBranch        *b_HGamEventInfoAuxDyn_N_lep_15;   //!
   TBranch        *b_HGamEventInfoAuxDyn_weightN_lep_15;   //!
   TBranch        *b_HGamEventInfoAuxDyn_N_j;   //!
   TBranch        *b_HGamEventInfoAuxDyn_N_j_30;   //!
   TBranch        *b_HGamEventInfoAuxDyn_N_j_50;   //!
   TBranch        *b_HGamEventInfoAuxDyn_N_j_central;   //!
   TBranch        *b_HGamEventInfoAuxDyn_N_j_central30;   //!
   TBranch        *b_HGamEventInfoAuxDyn_pT_j1_30;   //!
   TBranch        *b_HGamEventInfoAuxDyn_yybb_highMass_MVA_score;   //!
   TBranch        *b_HGamEventInfoAuxDyn_pT_j1;   //!
   TBranch        *b_HGamEventInfoAuxDyn_yybb_highMass_m_bb_uncnstrnd;   //!
   TBranch        *b_HGamEventInfoAuxDyn_pT_j2_30;   //!
   TBranch        *b_HGamEventInfoAuxDyn_yybb_highMass_m_yybb;   //!
   TBranch        *b_HGamEventInfoAuxDyn_pT_j2;   //!
   TBranch        *b_HGamEventInfoAuxDyn_yybb_highMass_pT_j1;   //!
   TBranch        *b_HGamEventInfoAuxDyn_pT_j3_30;   //!
   TBranch        *b_HGamEventInfoAuxDyn_yybb_highMass_pT_j2;   //!
   TBranch        *b_HGamEventInfoAuxDyn_yybb_highMass_weight;   //!
   TBranch        *b_HGamEventInfoAuxDyn_yAbs_j1_30;   //!
   TBranch        *b_HGamEventInfoAuxDyn_yybb_highMass_weight_discreteSFs;   //!
   TBranch        *b_HGamEventInfoAuxDyn_yybb_lowMass_MVA_score;   //!
   TBranch        *b_HGamEventInfoAuxDyn_yAbs_j2_30;   //!
   TBranch        *b_HGamEventInfoAuxDyn_yybb_lowMass_m_bb_uncnstrnd;   //!
   TBranch        *b_HGamEventInfoAuxDyn_pT_jj;   //!
   TBranch        *b_HGamEventInfoAuxDyn_yybb_lowMass_m_yybb;   //!
   TBranch        *b_HGamEventInfoAuxDyn_yybb_lowMass_pT_j1;   //!
   TBranch        *b_HGamEventInfoAuxDyn_m_jj;   //!
   TBranch        *b_HGamEventInfoAuxDyn_yybb_lowMass_pT_j2;   //!
   TBranch        *b_HGamEventInfoAuxDyn_yybb_lowMass_weight;   //!
   TBranch        *b_HGamEventInfoAuxDyn_m_jj_30;   //!
   TBranch        *b_HGamEventInfoAuxDyn_yybb_lowMass_weight_discreteSFs;   //!
   TBranch        *b_HGamEventInfoAuxDyn_Dy_j_j;   //!
   TBranch        *b_HGamEventInfoAuxDyn_Deta_j_j;   //!
   TBranch        *b_HGamEventInfoAuxDyn_yybb_bTagCat;   //!
   TBranch        *b_HGamEventInfoAuxDyn_yybb_highMass_cutFlow;   //!
   TBranch        *b_HGamEventInfoAuxDyn_Dy_j_j_30;   //!
   TBranch        *b_HGamEventInfoAuxDyn_yybb_highMass_truth_label_j1;   //!
   TBranch        *b_HGamEventInfoAuxDyn_Dy_yy_jj;   //!
   TBranch        *b_HGamEventInfoAuxDyn_yybb_highMass_truth_label_j2;   //!
   TBranch        *b_HGamEventInfoAuxDyn_Dy_yy_jj_30;   //!
   TBranch        *b_HGamEventInfoAuxDyn_yybb_lowMass_cutFlow;   //!
   TBranch        *b_HGamEventInfoAuxDyn_Dphi_j_j;   //!
   TBranch        *b_HGamEventInfoAuxDyn_yybb_lowMass_truth_label_j1;   //!
   TBranch        *b_HGamEventInfoAuxDyn_Dphi_j_j_30;   //!
   TBranch        *b_HGamEventInfoAuxDyn_yybb_lowMass_truth_label_j2;   //!
   TBranch        *b_HGamEventInfoAuxDyn_Dphi_j_j_30_signed;   //!
   TBranch        *b_HGamEventInfoAuxDyn_met_cat;   //!
   TBranch        *b_HGamEventInfoAuxDyn_Dphi_yy_jj;   //!
   TBranch        *b_HGamEventInfoAuxDyn_met_weight;   //!
   TBranch        *b_HGamEventInfoAuxDyn_Dphi_yy_jj_30;   //!
   TBranch        *b_HGamEventInfoAuxDyn_fcnc_etm;   //!
   TBranch        *b_HGamEventInfoAuxDyn_fcnc_mT;   //!
   TBranch        *b_HGamEventInfoAuxDyn_fcnc_phim;   //!
   TBranch        *b_HGamEventInfoAuxDyn_pT_yyjj_30;   //!
   TBranch        *b_HGamEventInfoAuxDyn_fcnc_weight;   //!
   TBranch        *b_HGamEventInfoAuxDyn_m_ee;   //!
   TBranch        *b_HGamEventInfoAuxDyn_fcnc_cat;   //!
   TBranch        *b_HGamEventInfoAuxDyn_m_mumu;   //!
   TBranch        *b_HGamEventInfoAuxDyn_fcnc_cutFlow;   //!
   TBranch        *b_HGamEventInfoAuxDyn_DRmin_y_j;   //!
   TBranch        *b_HGamEventInfoAuxDyn_fcnc_idLep;   //!
   TBranch        *b_HGamEventInfoAuxDyn_DRmin_y_j_2;   //!
   TBranch        *b_HGamEventInfoAuxDyn_fcnc_njet;   //!
   TBranch        *b_HGamEventInfoAuxDyn_DR_y_y;   //!
   TBranch        *b_HGamEventInfoAuxDyn_fcnc_njet30;   //!
   TBranch        *b_HGamEventInfoAuxDyn_Zepp;   //!
   TBranch        *b_HGamEventInfoAuxDyn_fcnc_ntopc;   //!
   TBranch        *b_HGamEventInfoAuxDyn_cosTS_yyjj;   //!
   TBranch        *b_HGamEventInfoAuxDyn_fcnc_nbTop2;   //!
   TBranch        *b_HGamEventInfoAuxDyn_sumTau_yyj_30;   //!
   TBranch        *b_HGamEventInfoAuxDyn_fcnc_mTop1;   //!
   TBranch        *b_HGamEventInfoAuxDyn_maxTau_yyj_30;   //!
   TBranch        *b_HGamEventInfoAuxDyn_fcnc_mTop2;   //!
   TBranch        *b_HGamEventInfoAuxDyn_met_TST;   //!
   TBranch        *b_HGamEventInfoAuxDyn_weightJvt;   //!
   TBranch        *b_HGamEventInfoAuxDyn_sumet_TST;   //!
   TBranch        *b_HGamEventInfoAuxDyn_weightJvt_30;   //!
   TBranch        *b_HGamEventInfoAuxDyn_phi_TST;   //!
   TBranch        *b_HGamEventInfoAuxDyn_weightJvt_50;   //!
   TBranch        *b_HGamEventInfoAuxDyn_N_j_btag;   //!
   TBranch        *b_HGamEventInfoAuxDyn_HT_30;   //!
   TBranch        *b_HGamEventInfoAuxDyn_N_j_btag30;   //!
   TBranch        *b_HGamEventInfoAuxDyn_HTall_30;   //!
   TBranch        *b_HGamEventInfoAuxDyn_m_alljet_30;   //!
   TBranch        *b_HGamEventInfoAuxDyn_catXS_ttH;   //!
   TBranch        *b_HGamEventInfoAuxDyn_weightCatXS_ttH;   //!
   TBranch        *b_HGamEventInfoAuxDyn_m_alljet;   //!
   TBranch        *b_HGamTruthPhotons;   //!
   TBranch        *b_HGamTruthPhotonsAux_;   //!
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
   TBranch        *b_HGamTruthElectrons;   //!
   TBranch        *b_HGamTruthElectronsAux_;   //!
   TBranch        *b_HGamTruthMuons;   //!
   TBranch        *b_HGamTruthMuonsAux_;   //!
   TBranch        *b_HGamAntiKt4TruthJets;   //!
   TBranch        *b_HGamAntiKt4TruthJetsAux_;   //!
   TBranch        *b_HGamAntiKt4TruthJetsAuxDyn_pt;   //!
   TBranch        *b_HGamAntiKt4TruthJetsAuxDyn_eta;   //!
   TBranch        *b_HGamAntiKt4TruthJetsAuxDyn_HadronConeExclTruthLabelID;   //!
   TBranch        *b_HGamAntiKt4TruthJetsAuxDyn_phi;   //!
   TBranch        *b_HGamAntiKt4TruthJetsAuxDyn_m;   //!
   TBranch        *b_HGamMET_Truth;   //!
   TBranch        *b_HGamMET_TruthAux_;   //!
   TBranch        *b_HGamMET_TruthAuxDyn_sumet;   //!
   TBranch        *b_HGamMET_TruthAuxDyn_name;   //!
   TBranch        *b_HGamMET_TruthAuxDyn_mpx;   //!
   TBranch        *b_HGamMET_TruthAuxDyn_mpy;   //!
   TBranch        *b_HGamMET_TruthAuxDyn_source;   //!
   TBranch        *b_HGamTruthHiggsBosons;   //!
   TBranch        *b_HGamTruthHiggsBosonsAux_;   //!
   TBranch        *b_HGamTruthHiggsBosonsAuxDyn_pt;   //!
   TBranch        *b_HGamTruthHiggsBosonsAuxDyn_eta;   //!
   TBranch        *b_HGamTruthHiggsBosonsAuxDyn_px;   //!
   TBranch        *b_HGamTruthHiggsBosonsAuxDyn_m;   //!
   TBranch        *b_HGamTruthHiggsBosonsAuxDyn_py;   //!
   TBranch        *b_HGamTruthHiggsBosonsAuxDyn_pz;   //!
   TBranch        *b_HGamTruthHiggsBosonsAuxDyn_e;   //!
   TBranch        *b_TruthEvents;   //!
   TBranch        *b_TruthEventsAux_;   //!
   TBranch        *b_TruthEventsAuxDyn_weights;   //!
   TBranch        *b_TruthEventsAuxDyn_PDFID1;   //!
   TBranch        *b_TruthEventsAuxDyn_PDFID2;   //!
   TBranch        *b_TruthEventsAuxDyn_PDGID1;   //!
   TBranch        *b_TruthEventsAuxDyn_PDGID2;   //!
   TBranch        *b_TruthEventsAuxDyn_Q;   //!
   TBranch        *b_TruthEventsAuxDyn_X1;   //!
   TBranch        *b_TruthEventsAuxDyn_X2;   //!
   TBranch        *b_TruthEventsAuxDyn_XF1;   //!
   TBranch        *b_TruthEventsAuxDyn_XF2;   //!
   TBranch        *b_HGamTruthEventInfo;   //!
   TBranch        *b_HGamTruthEventInfoAux_;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_HTall_30;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_isFiducial;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_isFiducialKinOnly;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_N_j_btag30;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_catXS_VBF;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_pT_h1;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_catXS_ttH;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_pT_h2;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_y_h1;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_y_h2;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_m_h1;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_m_h2;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_yAbs_yy;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_pTt_yy;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_m_yy;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_passMeyCut;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_truthCategory;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_pT_yy;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_truthProcess;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_pT_y1;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_pT_y2;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_isVyyOverlap;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_E_y1;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_E_y2;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_pT_hard;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_cosTS_yy;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_phiStar_yy;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_Dy_y_y;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_N_e;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_N_mu;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_N_lep;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_N_lep_15;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_N_j;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_N_j_30;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_N_j_50;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_N_j_central;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_N_j_central30;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_pT_j1_30;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_pT_j1;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_pT_j2_30;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_pT_j2;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_pT_j3_30;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_met_NonInt;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_yAbs_j1_30;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_sumet_Int;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_met_NonHad;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_yAbs_j2_30;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_isFiducialLowHighMyy;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_pT_jj;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_isFiducialExotic;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_m_jj;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_m_jj_30;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_Dy_j_j;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_Dy_j_j_30;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_Dy_yy_jj_30;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_Dphi_j_j;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_Dphi_j_j_30;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_Dphi_j_j_30_signed;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_Dphi_yy_jj;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_Dphi_yy_jj_30;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_pT_yyjj_30;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_m_ee;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_m_mumu;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_DRmin_y_j;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_DR_y_y;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_Zepp;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_cosTS_yyjj;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_sumTau_yyj_30;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_maxTau_yyj_30;   //!
   TBranch        *b_HGamTruthEventInfoAuxDyn_HT_30;   //!
   TBranch        *b_EventInfo;   //!
   TBranch        *b_EventInfoAux_runNumber;   //!
   TBranch        *b_EventInfoAux_eventNumber;   //!
   TBranch        *b_EventInfoAux_lumiBlock;   //!
   TBranch        *b_EventInfoAux_timeStamp;   //!
   TBranch        *b_EventInfoAux_timeStampNSOffset;   //!
   TBranch        *b_EventInfoAux_bcid;   //!
   TBranch        *b_EventInfoAux_detectorMask0;   //!
   TBranch        *b_EventInfoAux_detectorMask1;   //!
   TBranch        *b_EventInfoAux_detectorMask2;   //!
   TBranch        *b_EventInfoAux_detectorMask3;   //!
   TBranch        *b_EventInfoAux_eventTypeBitmask;   //!
   TBranch        *b_EventInfoAux_statusElement;   //!
   TBranch        *b_EventInfoAux_extendedLevel1ID;   //!
   TBranch        *b_EventInfoAux_level1TriggerType;   //!
   TBranch        *b_EventInfoAux_streamTagNames;   //!
   TBranch        *b_EventInfoAux_streamTagTypes;   //!
   TBranch        *b_EventInfoAux_streamTagObeysLumiblock;   //!
   TBranch        *b_EventInfoAux_actualInteractionsPerCrossing;   //!
   TBranch        *b_EventInfoAux_averageInteractionsPerCrossing;   //!
   TBranch        *b_EventInfoAux_pixelFlags;   //!
   TBranch        *b_EventInfoAux_sctFlags;   //!
   TBranch        *b_EventInfoAux_trtFlags;   //!
   TBranch        *b_EventInfoAux_larFlags;   //!
   TBranch        *b_EventInfoAux_tileFlags;   //!
   TBranch        *b_EventInfoAux_muonFlags;   //!
   TBranch        *b_EventInfoAux_forwardDetFlags;   //!
   TBranch        *b_EventInfoAux_coreFlags;   //!
   TBranch        *b_EventInfoAux_backgroundFlags;   //!
   TBranch        *b_EventInfoAux_lumiFlags;   //!
   TBranch        *b_EventInfoAux_beamPosX;   //!
   TBranch        *b_EventInfoAux_beamPosY;   //!
   TBranch        *b_EventInfoAux_beamPosZ;   //!
   TBranch        *b_EventInfoAux_beamPosSigmaX;   //!
   TBranch        *b_EventInfoAux_beamPosSigmaY;   //!
   TBranch        *b_EventInfoAux_beamPosSigmaZ;   //!
   TBranch        *b_EventInfoAux_beamPosSigmaXY;   //!
   TBranch        *b_EventInfoAux_beamTiltXZ;   //!
   TBranch        *b_EventInfoAux_beamTiltYZ;   //!
   TBranch        *b_EventInfoAux_beamStatus;   //!
   TBranch        *b_EventInfoAuxDyn_mcEventWeights;   //!
   TBranch        *b_EventInfoAuxDyn_HTXS_Stage1_Category_pTjet30;   //!
   TBranch        *b_EventInfoAuxDyn_HTXS_Stage1_FineIndex_pTjet25;   //!
   TBranch        *b_EventInfoAuxDyn_HTXS_Stage1_FineIndex_pTjet30;   //!
   TBranch        *b_EventInfoAuxDyn_HTXS_V_jets30_eta;   //!
   TBranch        *b_EventInfoAuxDyn_passTrig_HLT_g35_loose_g25_loose;   //!
   TBranch        *b_EventInfoAuxDyn_HTXS_V_jets30_m;   //!
   TBranch        *b_EventInfoAuxDyn_HTXS_V_jets30_phi;   //!
   TBranch        *b_EventInfoAuxDyn_HTXS_V_jets30_pt;   //!
   TBranch        *b_EventInfoAuxDyn_HTXS_V_pt;   //!
   TBranch        *b_EventInfoAuxDyn_passTrig_HLT_g35_medium_g25_medium;   //!
   TBranch        *b_EventInfoAuxDyn_HTXS_errorCode;   //!
   TBranch        *b_EventInfoAuxDyn_HTXS_Njets_pTjet25;   //!
   TBranch        *b_EventInfoAuxDyn_passTrig_HLT_2g50_loose;   //!
   TBranch        *b_EventInfoAuxDyn_HTXS_prodMode;   //!
   TBranch        *b_EventInfoAuxDyn_HTXS_Njets_pTjet30;   //!
   TBranch        *b_EventInfoAuxDyn_mcChannelNumber;   //!
   TBranch        *b_EventInfoAuxDyn_HTXS_Stage0_Category;   //!
   TBranch        *b_EventInfoAuxDyn_HTXS_Stage1_Category_pTjet25;   //!
   TBranch        *b_HGamPhotonsAuxDyn_truthLink;   //!
   TBranch        *b_HGamPhotonsAuxDyn_parentPdgId;   //!
   TBranch        *b_HGamPhotonsAuxDyn_pdgId;   //!
   TBranch        *b_HGamTruthPhotonsAuxDyn_recoLink;   //!
   TBranch        *b_HGamElectronsAuxDyn_scaleFactor;   //!
   TBranch        *b_HGamElectronsAuxDyn_ptvarcone20;   //!
   TBranch        *b_HGamElectronsAuxDyn_pt;   //!
   TBranch        *b_HGamElectronsAuxDyn_eta;   //!
   TBranch        *b_HGamElectronsAuxDyn_topoetcone20;   //!
   TBranch        *b_HGamElectronsAuxDyn_phi;   //!
   TBranch        *b_HGamElectronsAuxDyn_m;   //!
   TBranch        *b_HGamElectronsAuxDyn_eta_s2;   //!
   TBranch        *b_HGamElectronsAuxDyn_charge;   //!
   TBranch        *b_HGamElectronsAuxDyn_isTight;   //!
   TBranch        *b_HGamTruthElectronsAuxDyn_truthOrigin;   //!
   TBranch        *b_HGamTruthElectronsAuxDyn_pt;   //!
   TBranch        *b_HGamTruthElectronsAuxDyn_truthType;   //!
   TBranch        *b_HGamTruthElectronsAuxDyn_eta;   //!
   TBranch        *b_HGamTruthElectronsAuxDyn_px;   //!
   TBranch        *b_HGamTruthElectronsAuxDyn_m;   //!
   TBranch        *b_HGamTruthElectronsAuxDyn_py;   //!
   TBranch        *b_HGamTruthElectronsAuxDyn_pz;   //!
   TBranch        *b_HGamTruthElectronsAuxDyn_e;   //!
   TBranch        *b_HGamElectronsAuxDyn_truthLink;   //!
   TBranch        *b_HGamTruthElectronsAuxDyn_recoLink;   //!
   TBranch        *b_HGamTruthMuonsAuxDyn_truthOrigin;   //!
   TBranch        *b_HGamTruthMuonsAuxDyn_pt;   //!
   TBranch        *b_HGamTruthMuonsAuxDyn_truthType;   //!
   TBranch        *b_HGamTruthMuonsAuxDyn_eta;   //!
   TBranch        *b_HGamTruthMuonsAuxDyn_px;   //!
   TBranch        *b_HGamTruthMuonsAuxDyn_m;   //!
   TBranch        *b_HGamTruthMuonsAuxDyn_py;   //!
   TBranch        *b_HGamTruthMuonsAuxDyn_pz;   //!
   TBranch        *b_HGamTruthMuonsAuxDyn_e;   //!
   TBranch        *b_HGamMuonsAuxDyn_scaleFactor;   //!
   TBranch        *b_HGamMuonsAuxDyn_ptvarcone20;   //!
   TBranch        *b_HGamMuonsAuxDyn_pt;   //!
   TBranch        *b_HGamMuonsAuxDyn_isBad;   //!
   TBranch        *b_HGamMuonsAuxDyn_passIPCut;   //!
   TBranch        *b_HGamMuonsAuxDyn_eta;   //!
   TBranch        *b_HGamMuonsAuxDyn_topoetcone20;   //!
   TBranch        *b_HGamMuonsAuxDyn_phi;   //!
   TBranch        *b_HGamMuonsAuxDyn_muonType;   //!
   TBranch        *b_HGamMuonsAuxDyn_charge;   //!
   TBranch        *b_HGamMuonsAuxDyn_isTight;   //!
   TBranch        *b_HGamEventInfoAuxDyn_pT_yyjj;   //!

   CollectionTree(TTree *tree=0);
   virtual ~CollectionTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef CollectionTree_cxx
CollectionTree::CollectionTree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("MxAOD/ttH/ttH_9.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("MxAOD/ttH/ttH_9.root");
      }
      f->GetObject("CollectionTree",tree);

   }
   Init(tree);
}

CollectionTree::~CollectionTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t CollectionTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t CollectionTree::LoadTree(Long64_t entry)
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

void CollectionTree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   HGamPhotons = 0;
   HGamPhotonsAux_ = 0;
   HGamPhotonsAuxDyn_truthOrigin = 0;
   HGamPhotonsAuxDyn_zvertex = 0;
   HGamPhotonsAuxDyn_truthType = 0;
   HGamPhotonsAuxDyn_weta1 = 0;
   HGamPhotonsAuxDyn_weta2 = 0;
   HGamPhotonsAuxDyn_wtots1 = 0;
   HGamPhotonsAuxDyn_scaleFactor = 0;
   HGamPhotonsAuxDyn_DeltaE = 0;
   HGamPhotonsAuxDyn_eta_s2 = 0;
   HGamPhotonsAuxDyn_isTight = 0;
   HGamPhotonsAuxDyn_pt = 0;
   HGamPhotonsAuxDyn_eta = 0;
   HGamPhotonsAuxDyn_phi = 0;
   HGamPhotonsAuxDyn_f1 = 0;
   HGamPhotonsAuxDyn_m = 0;
   HGamPhotonsAuxDyn_fracs1 = 0;
   HGamPhotonsAuxDyn_cl_E = 0;
   HGamPhotonsAuxDyn_Eratio = 0;
   HGamPhotonsAuxDyn_isEMTight = 0;
   HGamPhotonsAuxDyn_maxEcell_energy = 0;
   HGamPhotonsAuxDyn_maxEcell_gain = 0;
   HGamPhotonsAuxDyn_maxEcell_onlId = 0;
   HGamPhotonsAuxDyn_maxEcell_time = 0;
   HGamPhotonsAuxDyn_isTight_nofudge = 0;
   HGamPhotonsAuxDyn_maxEcell_x = 0;
   HGamPhotonsAuxDyn_isEMTight_nofudge = 0;
   HGamPhotonsAuxDyn_maxEcell_y = 0;
   HGamPhotonsAuxDyn_maxEcell_z = 0;
   HGamPhotonsAuxDyn_Reta = 0;
   HGamPhotonsAuxDyn_conversionType = 0;
   HGamPhotonsAuxDyn_Rhad = 0;
   HGamPhotonsAuxDyn_Rconv = 0;
   HGamPhotonsAuxDyn_zconv = 0;
   HGamPhotonsAuxDyn_Rhad1 = 0;
   HGamPhotonsAuxDyn_Rphi = 0;
   HGamPhotonsAuxDyn_truthRconv = 0;
   HGamPhotonsAuxDyn_author = 0;
   HGamPhotonsAuxDyn_ptcone20 = 0;
   HGamPhotonsAuxDyn_ptcone40 = 0;
   HGamPhotonsAuxDyn_maxEcell_eta = 0;
   HGamPhotonsAuxDyn_maxEcell_phi = 0;
   HGamPhotonsAuxDyn_topoetcone20_DDcorr = 0;
   HGamPhotonsAuxDyn_topoetcone40_DDcorr = 0;
   HGamPhotonsAuxDyn_isIsoFixedCutLoose = 0;
   HGamPhotonsAuxDyn_isIsoFixedCutTight = 0;
   HGamPhotonsAuxDyn_isIsoFixedCutTightCaloOnly = 0;
   HGamPhotonsAuxDyn_isIsoFixedCutLooseCaloOnly = 0;
   HGamPhotonsAuxDyn_topoetcone20 = 0;
   HGamPhotonsAuxDyn_e277 = 0;
   HGamPhotonsAuxDyn_topoetcone40 = 0;
   HGamElectrons = 0;
   HGamElectronsAux_ = 0;
   HGamAntiKt4EMTopoJets = 0;
   HGamAntiKt4EMTopoJetsAux_ = 0;
   HGamAntiKt4EMTopoJetsAuxDyn_SF_MV2c10_FixedCutBEff_60 = 0;
   HGamAntiKt4EMTopoJetsAuxDyn_MV2c10_FixedCutBEff_70 = 0;
   HGamAntiKt4EMTopoJetsAuxDyn_MV2c10_discriminant = 0;
   HGamAntiKt4EMTopoJetsAuxDyn_Eff_MV2c10_FixedCutBEff_70 = 0;
   HGamAntiKt4EMTopoJetsAuxDyn_InEff_MV2c10_FixedCutBEff_70 = 0;
   HGamAntiKt4EMTopoJetsAuxDyn_SF_MV2c10_FixedCutBEff_70 = 0;
   HGamAntiKt4EMTopoJetsAuxDyn_MV2c10_FixedCutBEff_77 = 0;
   HGamAntiKt4EMTopoJetsAuxDyn_Eff_MV2c10_FixedCutBEff_77 = 0;
   HGamAntiKt4EMTopoJetsAuxDyn_InEff_MV2c10_FixedCutBEff_77 = 0;
   HGamAntiKt4EMTopoJetsAuxDyn_SF_MV2c10_FixedCutBEff_77 = 0;
   HGamAntiKt4EMTopoJetsAuxDyn_MV2c10_FixedCutBEff_85 = 0;
   HGamAntiKt4EMTopoJetsAuxDyn_Eff_MV2c10_FixedCutBEff_85 = 0;
   HGamAntiKt4EMTopoJetsAuxDyn_InEff_MV2c10_FixedCutBEff_85 = 0;
   HGamAntiKt4EMTopoJetsAuxDyn_SF_MV2c10_FixedCutBEff_85 = 0;
   HGamAntiKt4EMTopoJetsAuxDyn_passFJVT = 0;
   HGamAntiKt4EMTopoJetsAuxDyn_SF_jvt = 0;
   HGamAntiKt4EMTopoJetsAuxDyn_HadronConeExclTruthLabelID = 0;
   HGamAntiKt4EMTopoJetsAuxDyn_DetectorEta = 0;
   HGamAntiKt4EMTopoJetsAuxDyn_pt = 0;
   HGamAntiKt4EMTopoJetsAuxDyn_Jvt = 0;
   HGamAntiKt4EMTopoJetsAuxDyn_eta = 0;
   HGamAntiKt4EMTopoJetsAuxDyn_phi = 0;
   HGamAntiKt4EMTopoJetsAuxDyn_m = 0;
   HGamAntiKt4EMTopoJetsAuxDyn_MV2c10_FixedCutBEff_60 = 0;
   HGamAntiKt4EMTopoJetsAuxDyn_Eff_MV2c10_FixedCutBEff_60 = 0;
   HGamAntiKt4EMTopoJetsAuxDyn_InEff_MV2c10_FixedCutBEff_60 = 0;
   HGamMuons = 0;
   HGamMuonsAux_ = 0;
   HGamMET_Reference_AntiKt4EMTopo = 0;
   HGamMET_Reference_AntiKt4EMTopoAux_ = 0;
   HGamMET_Reference_AntiKt4EMTopoAuxDyn_sumet = 0;
   HGamMET_Reference_AntiKt4EMTopoAuxDyn_name = 0;
   HGamMET_Reference_AntiKt4EMTopoAuxDyn_mpx = 0;
   HGamMET_Reference_AntiKt4EMTopoAuxDyn_mpy = 0;
   HGamMET_Reference_AntiKt4EMTopoAuxDyn_source = 0;
   HGamEventInfo = 0;
   HGamEventInfoAux_ = 0;
   HGamEventInfoAuxDyn_PrimaryVerticesZ = 0;
   HGamEventInfoAuxDyn_PrimaryVerticesScore = 0;
   HGamEventInfoAuxDyn_fcnc_nbTop2 = 0;
   HGamEventInfoAuxDyn_fcnc_mTop1 = 0;
   HGamEventInfoAuxDyn_fcnc_mTop2 = 0;
   HGamTruthPhotons = 0;
   HGamTruthPhotonsAux_ = 0;
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
   HGamTruthElectrons = 0;
   HGamTruthElectronsAux_ = 0;
   HGamTruthMuons = 0;
   HGamTruthMuonsAux_ = 0;
   HGamAntiKt4TruthJets = 0;
   HGamAntiKt4TruthJetsAux_ = 0;
   HGamAntiKt4TruthJetsAuxDyn_pt = 0;
   HGamAntiKt4TruthJetsAuxDyn_eta = 0;
   HGamAntiKt4TruthJetsAuxDyn_HadronConeExclTruthLabelID = 0;
   HGamAntiKt4TruthJetsAuxDyn_phi = 0;
   HGamAntiKt4TruthJetsAuxDyn_m = 0;
   HGamMET_Truth = 0;
   HGamMET_TruthAux_ = 0;
   HGamMET_TruthAuxDyn_sumet = 0;
   HGamMET_TruthAuxDyn_name = 0;
   HGamMET_TruthAuxDyn_mpx = 0;
   HGamMET_TruthAuxDyn_mpy = 0;
   HGamMET_TruthAuxDyn_source = 0;
   HGamTruthHiggsBosons = 0;
   HGamTruthHiggsBosonsAux_ = 0;
   HGamTruthHiggsBosonsAuxDyn_pt = 0;
   HGamTruthHiggsBosonsAuxDyn_eta = 0;
   HGamTruthHiggsBosonsAuxDyn_px = 0;
   HGamTruthHiggsBosonsAuxDyn_m = 0;
   HGamTruthHiggsBosonsAuxDyn_py = 0;
   HGamTruthHiggsBosonsAuxDyn_pz = 0;
   HGamTruthHiggsBosonsAuxDyn_e = 0;
   TruthEvents = 0;
   TruthEventsAux_ = 0;
   TruthEventsAuxDyn_weights = 0;
   TruthEventsAuxDyn_PDFID1 = 0;
   TruthEventsAuxDyn_PDFID2 = 0;
   TruthEventsAuxDyn_PDGID1 = 0;
   TruthEventsAuxDyn_PDGID2 = 0;
   TruthEventsAuxDyn_Q = 0;
   TruthEventsAuxDyn_X1 = 0;
   TruthEventsAuxDyn_X2 = 0;
   TruthEventsAuxDyn_XF1 = 0;
   TruthEventsAuxDyn_XF2 = 0;
   HGamTruthEventInfo = 0;
   HGamTruthEventInfoAux_ = 0;
   EventInfo = 0;
   EventInfoAuxDyn_mcEventWeights = 0;
   EventInfoAuxDyn_HTXS_V_jets30_eta = 0;
   EventInfoAuxDyn_HTXS_V_jets30_m = 0;
   EventInfoAuxDyn_HTXS_V_jets30_phi = 0;
   EventInfoAuxDyn_HTXS_V_jets30_pt = 0;
   HGamPhotonsAuxDyn_truthLink = 0;
   HGamPhotonsAuxDyn_parentPdgId = 0;
   HGamPhotonsAuxDyn_pdgId = 0;
   HGamTruthPhotonsAuxDyn_recoLink = 0;
   HGamElectronsAuxDyn_scaleFactor = 0;
   HGamElectronsAuxDyn_ptvarcone20 = 0;
   HGamElectronsAuxDyn_pt = 0;
   HGamElectronsAuxDyn_eta = 0;
   HGamElectronsAuxDyn_topoetcone20 = 0;
   HGamElectronsAuxDyn_phi = 0;
   HGamElectronsAuxDyn_m = 0;
   HGamElectronsAuxDyn_eta_s2 = 0;
   HGamElectronsAuxDyn_charge = 0;
   HGamElectronsAuxDyn_isTight = 0;
   HGamTruthElectronsAuxDyn_truthOrigin = 0;
   HGamTruthElectronsAuxDyn_pt = 0;
   HGamTruthElectronsAuxDyn_truthType = 0;
   HGamTruthElectronsAuxDyn_eta = 0;
   HGamTruthElectronsAuxDyn_px = 0;
   HGamTruthElectronsAuxDyn_m = 0;
   HGamTruthElectronsAuxDyn_py = 0;
   HGamTruthElectronsAuxDyn_pz = 0;
   HGamTruthElectronsAuxDyn_e = 0;
   HGamElectronsAuxDyn_truthLink = 0;
   HGamTruthElectronsAuxDyn_recoLink = 0;
   HGamTruthMuonsAuxDyn_truthOrigin = 0;
   HGamTruthMuonsAuxDyn_pt = 0;
   HGamTruthMuonsAuxDyn_truthType = 0;
   HGamTruthMuonsAuxDyn_eta = 0;
   HGamTruthMuonsAuxDyn_px = 0;
   HGamTruthMuonsAuxDyn_m = 0;
   HGamTruthMuonsAuxDyn_py = 0;
   HGamTruthMuonsAuxDyn_pz = 0;
   HGamTruthMuonsAuxDyn_e = 0;
   HGamMuonsAuxDyn_scaleFactor = 0;
   HGamMuonsAuxDyn_ptvarcone20 = 0;
   HGamMuonsAuxDyn_pt = 0;
   HGamMuonsAuxDyn_isBad = 0;
   HGamMuonsAuxDyn_passIPCut = 0;
   HGamMuonsAuxDyn_eta = 0;
   HGamMuonsAuxDyn_topoetcone20 = 0;
   HGamMuonsAuxDyn_phi = 0;
   HGamMuonsAuxDyn_muonType = 0;
   HGamMuonsAuxDyn_charge = 0;
   HGamMuonsAuxDyn_isTight = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("HGamPhotons", &HGamPhotons, &b_HGamPhotons);
   fChain->SetBranchAddress("HGamPhotonsAux.", &HGamPhotonsAux_, &b_HGamPhotonsAux_);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.truthOrigin", &HGamPhotonsAuxDyn_truthOrigin, &b_HGamPhotonsAuxDyn_truthOrigin);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.zvertex", &HGamPhotonsAuxDyn_zvertex, &b_HGamPhotonsAuxDyn_zvertex);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.truthType", &HGamPhotonsAuxDyn_truthType, &b_HGamPhotonsAuxDyn_truthType);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.weta1", &HGamPhotonsAuxDyn_weta1, &b_HGamPhotonsAuxDyn_weta1);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.weta2", &HGamPhotonsAuxDyn_weta2, &b_HGamPhotonsAuxDyn_weta2);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.wtots1", &HGamPhotonsAuxDyn_wtots1, &b_HGamPhotonsAuxDyn_wtots1);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.scaleFactor", &HGamPhotonsAuxDyn_scaleFactor, &b_HGamPhotonsAuxDyn_scaleFactor);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.DeltaE", &HGamPhotonsAuxDyn_DeltaE, &b_HGamPhotonsAuxDyn_DeltaE);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.eta_s2", &HGamPhotonsAuxDyn_eta_s2, &b_HGamPhotonsAuxDyn_eta_s2);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.isTight", &HGamPhotonsAuxDyn_isTight, &b_HGamPhotonsAuxDyn_isTight);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.pt", &HGamPhotonsAuxDyn_pt, &b_HGamPhotonsAuxDyn_pt);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.eta", &HGamPhotonsAuxDyn_eta, &b_HGamPhotonsAuxDyn_eta);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.phi", &HGamPhotonsAuxDyn_phi, &b_HGamPhotonsAuxDyn_phi);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.f1", &HGamPhotonsAuxDyn_f1, &b_HGamPhotonsAuxDyn_f1);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.m", &HGamPhotonsAuxDyn_m, &b_HGamPhotonsAuxDyn_m);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.fracs1", &HGamPhotonsAuxDyn_fracs1, &b_HGamPhotonsAuxDyn_fracs1);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.cl_E", &HGamPhotonsAuxDyn_cl_E, &b_HGamPhotonsAuxDyn_cl_E);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.Eratio", &HGamPhotonsAuxDyn_Eratio, &b_HGamPhotonsAuxDyn_Eratio);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.isEMTight", &HGamPhotonsAuxDyn_isEMTight, &b_HGamPhotonsAuxDyn_isEMTight);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.maxEcell_energy", &HGamPhotonsAuxDyn_maxEcell_energy, &b_HGamPhotonsAuxDyn_maxEcell_energy);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.maxEcell_gain", &HGamPhotonsAuxDyn_maxEcell_gain, &b_HGamPhotonsAuxDyn_maxEcell_gain);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.maxEcell_onlId", &HGamPhotonsAuxDyn_maxEcell_onlId, &b_HGamPhotonsAuxDyn_maxEcell_onlId);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.maxEcell_time", &HGamPhotonsAuxDyn_maxEcell_time, &b_HGamPhotonsAuxDyn_maxEcell_time);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.isTight_nofudge", &HGamPhotonsAuxDyn_isTight_nofudge, &b_HGamPhotonsAuxDyn_isTight_nofudge);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.maxEcell_x", &HGamPhotonsAuxDyn_maxEcell_x, &b_HGamPhotonsAuxDyn_maxEcell_x);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.isEMTight_nofudge", &HGamPhotonsAuxDyn_isEMTight_nofudge, &b_HGamPhotonsAuxDyn_isEMTight_nofudge);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.maxEcell_y", &HGamPhotonsAuxDyn_maxEcell_y, &b_HGamPhotonsAuxDyn_maxEcell_y);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.maxEcell_z", &HGamPhotonsAuxDyn_maxEcell_z, &b_HGamPhotonsAuxDyn_maxEcell_z);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.Reta", &HGamPhotonsAuxDyn_Reta, &b_HGamPhotonsAuxDyn_Reta);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.conversionType", &HGamPhotonsAuxDyn_conversionType, &b_HGamPhotonsAuxDyn_conversionType);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.Rhad", &HGamPhotonsAuxDyn_Rhad, &b_HGamPhotonsAuxDyn_Rhad);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.Rconv", &HGamPhotonsAuxDyn_Rconv, &b_HGamPhotonsAuxDyn_Rconv);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.zconv", &HGamPhotonsAuxDyn_zconv, &b_HGamPhotonsAuxDyn_zconv);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.Rhad1", &HGamPhotonsAuxDyn_Rhad1, &b_HGamPhotonsAuxDyn_Rhad1);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.Rphi", &HGamPhotonsAuxDyn_Rphi, &b_HGamPhotonsAuxDyn_Rphi);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.truthRconv", &HGamPhotonsAuxDyn_truthRconv, &b_HGamPhotonsAuxDyn_truthRconv);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.author", &HGamPhotonsAuxDyn_author, &b_HGamPhotonsAuxDyn_author);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.ptcone20", &HGamPhotonsAuxDyn_ptcone20, &b_HGamPhotonsAuxDyn_ptcone20);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.ptcone40", &HGamPhotonsAuxDyn_ptcone40, &b_HGamPhotonsAuxDyn_ptcone40);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.maxEcell_eta", &HGamPhotonsAuxDyn_maxEcell_eta, &b_HGamPhotonsAuxDyn_maxEcell_eta);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.maxEcell_phi", &HGamPhotonsAuxDyn_maxEcell_phi, &b_HGamPhotonsAuxDyn_maxEcell_phi);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.topoetcone20_DDcorr", &HGamPhotonsAuxDyn_topoetcone20_DDcorr, &b_HGamPhotonsAuxDyn_topoetcone20_DDcorr);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.topoetcone40_DDcorr", &HGamPhotonsAuxDyn_topoetcone40_DDcorr, &b_HGamPhotonsAuxDyn_topoetcone40_DDcorr);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.isIsoFixedCutLoose", &HGamPhotonsAuxDyn_isIsoFixedCutLoose, &b_HGamPhotonsAuxDyn_isIsoFixedCutLoose);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.isIsoFixedCutTight", &HGamPhotonsAuxDyn_isIsoFixedCutTight, &b_HGamPhotonsAuxDyn_isIsoFixedCutTight);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.isIsoFixedCutTightCaloOnly", &HGamPhotonsAuxDyn_isIsoFixedCutTightCaloOnly, &b_HGamPhotonsAuxDyn_isIsoFixedCutTightCaloOnly);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.isIsoFixedCutLooseCaloOnly", &HGamPhotonsAuxDyn_isIsoFixedCutLooseCaloOnly, &b_HGamPhotonsAuxDyn_isIsoFixedCutLooseCaloOnly);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.topoetcone20", &HGamPhotonsAuxDyn_topoetcone20, &b_HGamPhotonsAuxDyn_topoetcone20);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.e277", &HGamPhotonsAuxDyn_e277, &b_HGamPhotonsAuxDyn_e277);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.topoetcone40", &HGamPhotonsAuxDyn_topoetcone40, &b_HGamPhotonsAuxDyn_topoetcone40);
   fChain->SetBranchAddress("HGamElectrons", &HGamElectrons, &b_HGamElectrons);
   fChain->SetBranchAddress("HGamElectronsAux.", &HGamElectronsAux_, &b_HGamElectronsAux_);
   fChain->SetBranchAddress("HGamAntiKt4EMTopoJets", &HGamAntiKt4EMTopoJets, &b_HGamAntiKt4EMTopoJets);
   fChain->SetBranchAddress("HGamAntiKt4EMTopoJetsAux.", &HGamAntiKt4EMTopoJetsAux_, &b_HGamAntiKt4EMTopoJetsAux_);
   fChain->SetBranchAddress("HGamAntiKt4EMTopoJetsAuxDyn.SF_MV2c10_FixedCutBEff_60", &HGamAntiKt4EMTopoJetsAuxDyn_SF_MV2c10_FixedCutBEff_60, &b_HGamAntiKt4EMTopoJetsAuxDyn_SF_MV2c10_FixedCutBEff_60);
   fChain->SetBranchAddress("HGamAntiKt4EMTopoJetsAuxDyn.MV2c10_FixedCutBEff_70", &HGamAntiKt4EMTopoJetsAuxDyn_MV2c10_FixedCutBEff_70, &b_HGamAntiKt4EMTopoJetsAuxDyn_MV2c10_FixedCutBEff_70);
   fChain->SetBranchAddress("HGamAntiKt4EMTopoJetsAuxDyn.MV2c10_discriminant", &HGamAntiKt4EMTopoJetsAuxDyn_MV2c10_discriminant, &b_HGamAntiKt4EMTopoJetsAuxDyn_MV2c10_discriminant);
   fChain->SetBranchAddress("HGamAntiKt4EMTopoJetsAuxDyn.Eff_MV2c10_FixedCutBEff_70", &HGamAntiKt4EMTopoJetsAuxDyn_Eff_MV2c10_FixedCutBEff_70, &b_HGamAntiKt4EMTopoJetsAuxDyn_Eff_MV2c10_FixedCutBEff_70);
   fChain->SetBranchAddress("HGamAntiKt4EMTopoJetsAuxDyn.InEff_MV2c10_FixedCutBEff_70", &HGamAntiKt4EMTopoJetsAuxDyn_InEff_MV2c10_FixedCutBEff_70, &b_HGamAntiKt4EMTopoJetsAuxDyn_InEff_MV2c10_FixedCutBEff_70);
   fChain->SetBranchAddress("HGamAntiKt4EMTopoJetsAuxDyn.SF_MV2c10_FixedCutBEff_70", &HGamAntiKt4EMTopoJetsAuxDyn_SF_MV2c10_FixedCutBEff_70, &b_HGamAntiKt4EMTopoJetsAuxDyn_SF_MV2c10_FixedCutBEff_70);
   fChain->SetBranchAddress("HGamAntiKt4EMTopoJetsAuxDyn.MV2c10_FixedCutBEff_77", &HGamAntiKt4EMTopoJetsAuxDyn_MV2c10_FixedCutBEff_77, &b_HGamAntiKt4EMTopoJetsAuxDyn_MV2c10_FixedCutBEff_77);
   fChain->SetBranchAddress("HGamAntiKt4EMTopoJetsAuxDyn.Eff_MV2c10_FixedCutBEff_77", &HGamAntiKt4EMTopoJetsAuxDyn_Eff_MV2c10_FixedCutBEff_77, &b_HGamAntiKt4EMTopoJetsAuxDyn_Eff_MV2c10_FixedCutBEff_77);
   fChain->SetBranchAddress("HGamAntiKt4EMTopoJetsAuxDyn.InEff_MV2c10_FixedCutBEff_77", &HGamAntiKt4EMTopoJetsAuxDyn_InEff_MV2c10_FixedCutBEff_77, &b_HGamAntiKt4EMTopoJetsAuxDyn_InEff_MV2c10_FixedCutBEff_77);
   fChain->SetBranchAddress("HGamAntiKt4EMTopoJetsAuxDyn.SF_MV2c10_FixedCutBEff_77", &HGamAntiKt4EMTopoJetsAuxDyn_SF_MV2c10_FixedCutBEff_77, &b_HGamAntiKt4EMTopoJetsAuxDyn_SF_MV2c10_FixedCutBEff_77);
   fChain->SetBranchAddress("HGamAntiKt4EMTopoJetsAuxDyn.MV2c10_FixedCutBEff_85", &HGamAntiKt4EMTopoJetsAuxDyn_MV2c10_FixedCutBEff_85, &b_HGamAntiKt4EMTopoJetsAuxDyn_MV2c10_FixedCutBEff_85);
   fChain->SetBranchAddress("HGamAntiKt4EMTopoJetsAuxDyn.Eff_MV2c10_FixedCutBEff_85", &HGamAntiKt4EMTopoJetsAuxDyn_Eff_MV2c10_FixedCutBEff_85, &b_HGamAntiKt4EMTopoJetsAuxDyn_Eff_MV2c10_FixedCutBEff_85);
   fChain->SetBranchAddress("HGamAntiKt4EMTopoJetsAuxDyn.InEff_MV2c10_FixedCutBEff_85", &HGamAntiKt4EMTopoJetsAuxDyn_InEff_MV2c10_FixedCutBEff_85, &b_HGamAntiKt4EMTopoJetsAuxDyn_InEff_MV2c10_FixedCutBEff_85);
   fChain->SetBranchAddress("HGamAntiKt4EMTopoJetsAuxDyn.SF_MV2c10_FixedCutBEff_85", &HGamAntiKt4EMTopoJetsAuxDyn_SF_MV2c10_FixedCutBEff_85, &b_HGamAntiKt4EMTopoJetsAuxDyn_SF_MV2c10_FixedCutBEff_85);
   fChain->SetBranchAddress("HGamAntiKt4EMTopoJetsAuxDyn.passFJVT", &HGamAntiKt4EMTopoJetsAuxDyn_passFJVT, &b_HGamAntiKt4EMTopoJetsAuxDyn_passFJVT);
   fChain->SetBranchAddress("HGamAntiKt4EMTopoJetsAuxDyn.SF_jvt", &HGamAntiKt4EMTopoJetsAuxDyn_SF_jvt, &b_HGamAntiKt4EMTopoJetsAuxDyn_SF_jvt);
   fChain->SetBranchAddress("HGamAntiKt4EMTopoJetsAuxDyn.HadronConeExclTruthLabelID", &HGamAntiKt4EMTopoJetsAuxDyn_HadronConeExclTruthLabelID, &b_HGamAntiKt4EMTopoJetsAuxDyn_HadronConeExclTruthLabelID);
   fChain->SetBranchAddress("HGamAntiKt4EMTopoJetsAuxDyn.DetectorEta", &HGamAntiKt4EMTopoJetsAuxDyn_DetectorEta, &b_HGamAntiKt4EMTopoJetsAuxDyn_DetectorEta);
   fChain->SetBranchAddress("HGamAntiKt4EMTopoJetsAuxDyn.pt", &HGamAntiKt4EMTopoJetsAuxDyn_pt, &b_HGamAntiKt4EMTopoJetsAuxDyn_pt);
   fChain->SetBranchAddress("HGamAntiKt4EMTopoJetsAuxDyn.Jvt", &HGamAntiKt4EMTopoJetsAuxDyn_Jvt, &b_HGamAntiKt4EMTopoJetsAuxDyn_Jvt);
   fChain->SetBranchAddress("HGamAntiKt4EMTopoJetsAuxDyn.eta", &HGamAntiKt4EMTopoJetsAuxDyn_eta, &b_HGamAntiKt4EMTopoJetsAuxDyn_eta);
   fChain->SetBranchAddress("HGamAntiKt4EMTopoJetsAuxDyn.phi", &HGamAntiKt4EMTopoJetsAuxDyn_phi, &b_HGamAntiKt4EMTopoJetsAuxDyn_phi);
   fChain->SetBranchAddress("HGamAntiKt4EMTopoJetsAuxDyn.m", &HGamAntiKt4EMTopoJetsAuxDyn_m, &b_HGamAntiKt4EMTopoJetsAuxDyn_m);
   fChain->SetBranchAddress("HGamAntiKt4EMTopoJetsAuxDyn.MV2c10_FixedCutBEff_60", &HGamAntiKt4EMTopoJetsAuxDyn_MV2c10_FixedCutBEff_60, &b_HGamAntiKt4EMTopoJetsAuxDyn_MV2c10_FixedCutBEff_60);
   fChain->SetBranchAddress("HGamAntiKt4EMTopoJetsAuxDyn.Eff_MV2c10_FixedCutBEff_60", &HGamAntiKt4EMTopoJetsAuxDyn_Eff_MV2c10_FixedCutBEff_60, &b_HGamAntiKt4EMTopoJetsAuxDyn_Eff_MV2c10_FixedCutBEff_60);
   fChain->SetBranchAddress("HGamAntiKt4EMTopoJetsAuxDyn.InEff_MV2c10_FixedCutBEff_60", &HGamAntiKt4EMTopoJetsAuxDyn_InEff_MV2c10_FixedCutBEff_60, &b_HGamAntiKt4EMTopoJetsAuxDyn_InEff_MV2c10_FixedCutBEff_60);
   fChain->SetBranchAddress("HGamMuons", &HGamMuons, &b_HGamMuons);
   fChain->SetBranchAddress("HGamMuonsAux.", &HGamMuonsAux_, &b_HGamMuonsAux_);
   fChain->SetBranchAddress("HGamMET_Reference_AntiKt4EMTopo", &HGamMET_Reference_AntiKt4EMTopo, &b_HGamMET_Reference_AntiKt4EMTopo);
   fChain->SetBranchAddress("HGamMET_Reference_AntiKt4EMTopoAux.", &HGamMET_Reference_AntiKt4EMTopoAux_, &b_HGamMET_Reference_AntiKt4EMTopoAux_);
   fChain->SetBranchAddress("HGamMET_Reference_AntiKt4EMTopoAuxDyn.sumet", &HGamMET_Reference_AntiKt4EMTopoAuxDyn_sumet, &b_HGamMET_Reference_AntiKt4EMTopoAuxDyn_sumet);
   fChain->SetBranchAddress("HGamMET_Reference_AntiKt4EMTopoAuxDyn.name", &HGamMET_Reference_AntiKt4EMTopoAuxDyn_name, &b_HGamMET_Reference_AntiKt4EMTopoAuxDyn_name);
   fChain->SetBranchAddress("HGamMET_Reference_AntiKt4EMTopoAuxDyn.mpx", &HGamMET_Reference_AntiKt4EMTopoAuxDyn_mpx, &b_HGamMET_Reference_AntiKt4EMTopoAuxDyn_mpx);
   fChain->SetBranchAddress("HGamMET_Reference_AntiKt4EMTopoAuxDyn.mpy", &HGamMET_Reference_AntiKt4EMTopoAuxDyn_mpy, &b_HGamMET_Reference_AntiKt4EMTopoAuxDyn_mpy);
   fChain->SetBranchAddress("HGamMET_Reference_AntiKt4EMTopoAuxDyn.source", &HGamMET_Reference_AntiKt4EMTopoAuxDyn_source, &b_HGamMET_Reference_AntiKt4EMTopoAuxDyn_source);
   fChain->SetBranchAddress("HGamEventInfo", &HGamEventInfo, &b_HGamEventInfo);
   fChain->SetBranchAddress("HGamEventInfoAux.", &HGamEventInfoAux_, &b_HGamEventInfoAux_);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.m_yy_resolution", &HGamEventInfoAuxDyn_m_yy_resolution, &b_HGamEventInfoAuxDyn_m_yy_resolution);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.isPassedBasic", &HGamEventInfoAuxDyn_isPassedBasic, &b_HGamEventInfoAuxDyn_isPassedBasic);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.NLoosePhotons", &HGamEventInfoAuxDyn_NLoosePhotons, &b_HGamEventInfoAuxDyn_NLoosePhotons);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.isPassed", &HGamEventInfoAuxDyn_isPassed, &b_HGamEventInfoAuxDyn_isPassed);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.met_hardVertexTST", &HGamEventInfoAuxDyn_met_hardVertexTST, &b_HGamEventInfoAuxDyn_met_hardVertexTST);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.isPassedJetEventClean", &HGamEventInfoAuxDyn_isPassedJetEventClean, &b_HGamEventInfoAuxDyn_isPassedJetEventClean);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.sumet_hardVertexTST", &HGamEventInfoAuxDyn_sumet_hardVertexTST, &b_HGamEventInfoAuxDyn_sumet_hardVertexTST);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.phi_hardVertexTST", &HGamEventInfoAuxDyn_phi_hardVertexTST, &b_HGamEventInfoAuxDyn_phi_hardVertexTST);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.isPassedIsolationLowHighMyy", &HGamEventInfoAuxDyn_isPassedIsolationLowHighMyy, &b_HGamEventInfoAuxDyn_isPassedIsolationLowHighMyy);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.isDalitz", &HGamEventInfoAuxDyn_isDalitz, &b_HGamEventInfoAuxDyn_isDalitz);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.isPassedRelPtCutsLowHighMyy", &HGamEventInfoAuxDyn_isPassedRelPtCutsLowHighMyy, &b_HGamEventInfoAuxDyn_isPassedRelPtCutsLowHighMyy);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.cutFlow", &HGamEventInfoAuxDyn_cutFlow, &b_HGamEventInfoAuxDyn_cutFlow);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.isPassedLowHighMyy", &HGamEventInfoAuxDyn_isPassedLowHighMyy, &b_HGamEventInfoAuxDyn_isPassedLowHighMyy);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.weightInitial", &HGamEventInfoAuxDyn_weightInitial, &b_HGamEventInfoAuxDyn_weightInitial);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.isPassedIsolationExotic", &HGamEventInfoAuxDyn_isPassedIsolationExotic, &b_HGamEventInfoAuxDyn_isPassedIsolationExotic);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.weight", &HGamEventInfoAuxDyn_weight, &b_HGamEventInfoAuxDyn_weight);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.isPassedlPtCutsExotic", &HGamEventInfoAuxDyn_isPassedlPtCutsExotic, &b_HGamEventInfoAuxDyn_isPassedlPtCutsExotic);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.weightSF", &HGamEventInfoAuxDyn_weightSF, &b_HGamEventInfoAuxDyn_weightSF);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.isPassedExotic", &HGamEventInfoAuxDyn_isPassedExotic, &b_HGamEventInfoAuxDyn_isPassedExotic);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.vertexWeight", &HGamEventInfoAuxDyn_vertexWeight, &b_HGamEventInfoAuxDyn_vertexWeight);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.isPassedExoticTight", &HGamEventInfoAuxDyn_isPassedExoticTight, &b_HGamEventInfoAuxDyn_isPassedExoticTight);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.pileupWeight", &HGamEventInfoAuxDyn_pileupWeight, &b_HGamEventInfoAuxDyn_pileupWeight);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.isPassedPreselection", &HGamEventInfoAuxDyn_isPassedPreselection, &b_HGamEventInfoAuxDyn_isPassedPreselection);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.weightCatCoup_Moriond2017", &HGamEventInfoAuxDyn_weightCatCoup_Moriond2017, &b_HGamEventInfoAuxDyn_weightCatCoup_Moriond2017);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.isPassedTriggerMatch", &HGamEventInfoAuxDyn_isPassedTriggerMatch, &b_HGamEventInfoAuxDyn_isPassedTriggerMatch);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.weightCatCoup_SFMoriond2017", &HGamEventInfoAuxDyn_weightCatCoup_SFMoriond2017, &b_HGamEventInfoAuxDyn_weightCatCoup_SFMoriond2017);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.isPassedPID", &HGamEventInfoAuxDyn_isPassedPID, &b_HGamEventInfoAuxDyn_isPassedPID);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.catCoup_Moriond2017", &HGamEventInfoAuxDyn_catCoup_Moriond2017, &b_HGamEventInfoAuxDyn_catCoup_Moriond2017);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.isPassedIsolation", &HGamEventInfoAuxDyn_isPassedIsolation, &b_HGamEventInfoAuxDyn_isPassedIsolation);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.weightCatCoup_Moriond2017BDT", &HGamEventInfoAuxDyn_weightCatCoup_Moriond2017BDT, &b_HGamEventInfoAuxDyn_weightCatCoup_Moriond2017BDT);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.isPassedRelPtCuts", &HGamEventInfoAuxDyn_isPassedRelPtCuts, &b_HGamEventInfoAuxDyn_isPassedRelPtCuts);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.weightCatCoup_SFMoriond2017BDT", &HGamEventInfoAuxDyn_weightCatCoup_SFMoriond2017BDT, &b_HGamEventInfoAuxDyn_weightCatCoup_SFMoriond2017BDT);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.isPassedMassCut", &HGamEventInfoAuxDyn_isPassedMassCut, &b_HGamEventInfoAuxDyn_isPassedMassCut);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.catCoup_Moriond2017BDT", &HGamEventInfoAuxDyn_catCoup_Moriond2017BDT, &b_HGamEventInfoAuxDyn_catCoup_Moriond2017BDT);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.m_yy_hardestVertex", &HGamEventInfoAuxDyn_m_yy_hardestVertex, &b_HGamEventInfoAuxDyn_m_yy_hardestVertex);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.weightCatCoup_Moriond2017BDTMET", &HGamEventInfoAuxDyn_weightCatCoup_Moriond2017BDTMET, &b_HGamEventInfoAuxDyn_weightCatCoup_Moriond2017BDTMET);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.m_yy_truthVertex", &HGamEventInfoAuxDyn_m_yy_truthVertex, &b_HGamEventInfoAuxDyn_m_yy_truthVertex);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.weightCatCoup_SFMoriond2017BDTMET", &HGamEventInfoAuxDyn_weightCatCoup_SFMoriond2017BDTMET, &b_HGamEventInfoAuxDyn_weightCatCoup_SFMoriond2017BDTMET);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.m_yy_zCommon", &HGamEventInfoAuxDyn_m_yy_zCommon, &b_HGamEventInfoAuxDyn_m_yy_zCommon);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.pileupWeight2015", &HGamEventInfoAuxDyn_pileupWeight2015, &b_HGamEventInfoAuxDyn_pileupWeight2015);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.catCoup_Moriond2017BDTMET", &HGamEventInfoAuxDyn_catCoup_Moriond2017BDTMET, &b_HGamEventInfoAuxDyn_catCoup_Moriond2017BDTMET);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.PrimaryVerticesZ", &HGamEventInfoAuxDyn_PrimaryVerticesZ, &b_HGamEventInfoAuxDyn_PrimaryVerticesZ);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.pileupWeight2016", &HGamEventInfoAuxDyn_pileupWeight2016, &b_HGamEventInfoAuxDyn_pileupWeight2016);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.catXS_VBF", &HGamEventInfoAuxDyn_catXS_VBF, &b_HGamEventInfoAuxDyn_catXS_VBF);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.PrimaryVerticesScore", &HGamEventInfoAuxDyn_PrimaryVerticesScore, &b_HGamEventInfoAuxDyn_PrimaryVerticesScore);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.pileupWeight15_16iTS", &HGamEventInfoAuxDyn_pileupWeight15_16iTS, &b_HGamEventInfoAuxDyn_pileupWeight15_16iTS);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.numberOfPrimaryVertices", &HGamEventInfoAuxDyn_numberOfPrimaryVertices, &b_HGamEventInfoAuxDyn_numberOfPrimaryVertices);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.selectedVertexZ", &HGamEventInfoAuxDyn_selectedVertexZ, &b_HGamEventInfoAuxDyn_selectedVertexZ);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.crossSectionBRfilterEff", &HGamEventInfoAuxDyn_crossSectionBRfilterEff, &b_HGamEventInfoAuxDyn_crossSectionBRfilterEff);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.hardestVertexZ", &HGamEventInfoAuxDyn_hardestVertexZ, &b_HGamEventInfoAuxDyn_hardestVertexZ);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.pileupVertexSumPt2", &HGamEventInfoAuxDyn_pileupVertexSumPt2, &b_HGamEventInfoAuxDyn_pileupVertexSumPt2);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.pileupVertexZ", &HGamEventInfoAuxDyn_pileupVertexZ, &b_HGamEventInfoAuxDyn_pileupVertexZ);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.zCommon", &HGamEventInfoAuxDyn_zCommon, &b_HGamEventInfoAuxDyn_zCommon);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.truthVertexZ", &HGamEventInfoAuxDyn_truthVertexZ, &b_HGamEventInfoAuxDyn_truthVertexZ);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.truthCategory", &HGamEventInfoAuxDyn_truthCategory, &b_HGamEventInfoAuxDyn_truthCategory);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.mu", &HGamEventInfoAuxDyn_mu, &b_HGamEventInfoAuxDyn_mu);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.isVyyOverlap", &HGamEventInfoAuxDyn_isVyyOverlap, &b_HGamEventInfoAuxDyn_isVyyOverlap);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.yAbs_yy", &HGamEventInfoAuxDyn_yAbs_yy, &b_HGamEventInfoAuxDyn_yAbs_yy);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.pTt_yy", &HGamEventInfoAuxDyn_pTt_yy, &b_HGamEventInfoAuxDyn_pTt_yy);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.m_yy", &HGamEventInfoAuxDyn_m_yy, &b_HGamEventInfoAuxDyn_m_yy);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.passMeyCut", &HGamEventInfoAuxDyn_passMeyCut, &b_HGamEventInfoAuxDyn_passMeyCut);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.pT_yy", &HGamEventInfoAuxDyn_pT_yy, &b_HGamEventInfoAuxDyn_pT_yy);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.pT_y1", &HGamEventInfoAuxDyn_pT_y1, &b_HGamEventInfoAuxDyn_pT_y1);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.pT_y2", &HGamEventInfoAuxDyn_pT_y2, &b_HGamEventInfoAuxDyn_pT_y2);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.E_y1", &HGamEventInfoAuxDyn_E_y1, &b_HGamEventInfoAuxDyn_E_y1);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.E_y2", &HGamEventInfoAuxDyn_E_y2, &b_HGamEventInfoAuxDyn_E_y2);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.pT_hard", &HGamEventInfoAuxDyn_pT_hard, &b_HGamEventInfoAuxDyn_pT_hard);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.cosTS_yy", &HGamEventInfoAuxDyn_cosTS_yy, &b_HGamEventInfoAuxDyn_cosTS_yy);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.phiStar_yy", &HGamEventInfoAuxDyn_phiStar_yy, &b_HGamEventInfoAuxDyn_phiStar_yy);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.Dy_y_y", &HGamEventInfoAuxDyn_Dy_y_y, &b_HGamEventInfoAuxDyn_Dy_y_y);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.N_e", &HGamEventInfoAuxDyn_N_e, &b_HGamEventInfoAuxDyn_N_e);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.N_mu", &HGamEventInfoAuxDyn_N_mu, &b_HGamEventInfoAuxDyn_N_mu);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.N_lep", &HGamEventInfoAuxDyn_N_lep, &b_HGamEventInfoAuxDyn_N_lep);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.N_lep_15", &HGamEventInfoAuxDyn_N_lep_15, &b_HGamEventInfoAuxDyn_N_lep_15);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.weightN_lep_15", &HGamEventInfoAuxDyn_weightN_lep_15, &b_HGamEventInfoAuxDyn_weightN_lep_15);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.N_j", &HGamEventInfoAuxDyn_N_j, &b_HGamEventInfoAuxDyn_N_j);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.N_j_30", &HGamEventInfoAuxDyn_N_j_30, &b_HGamEventInfoAuxDyn_N_j_30);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.N_j_50", &HGamEventInfoAuxDyn_N_j_50, &b_HGamEventInfoAuxDyn_N_j_50);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.N_j_central", &HGamEventInfoAuxDyn_N_j_central, &b_HGamEventInfoAuxDyn_N_j_central);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.N_j_central30", &HGamEventInfoAuxDyn_N_j_central30, &b_HGamEventInfoAuxDyn_N_j_central30);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.pT_j1_30", &HGamEventInfoAuxDyn_pT_j1_30, &b_HGamEventInfoAuxDyn_pT_j1_30);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.yybb_highMass_MVA_score", &HGamEventInfoAuxDyn_yybb_highMass_MVA_score, &b_HGamEventInfoAuxDyn_yybb_highMass_MVA_score);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.pT_j1", &HGamEventInfoAuxDyn_pT_j1, &b_HGamEventInfoAuxDyn_pT_j1);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.yybb_highMass_m_bb_uncnstrnd", &HGamEventInfoAuxDyn_yybb_highMass_m_bb_uncnstrnd, &b_HGamEventInfoAuxDyn_yybb_highMass_m_bb_uncnstrnd);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.pT_j2_30", &HGamEventInfoAuxDyn_pT_j2_30, &b_HGamEventInfoAuxDyn_pT_j2_30);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.yybb_highMass_m_yybb", &HGamEventInfoAuxDyn_yybb_highMass_m_yybb, &b_HGamEventInfoAuxDyn_yybb_highMass_m_yybb);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.pT_j2", &HGamEventInfoAuxDyn_pT_j2, &b_HGamEventInfoAuxDyn_pT_j2);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.yybb_highMass_pT_j1", &HGamEventInfoAuxDyn_yybb_highMass_pT_j1, &b_HGamEventInfoAuxDyn_yybb_highMass_pT_j1);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.pT_j3_30", &HGamEventInfoAuxDyn_pT_j3_30, &b_HGamEventInfoAuxDyn_pT_j3_30);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.yybb_highMass_pT_j2", &HGamEventInfoAuxDyn_yybb_highMass_pT_j2, &b_HGamEventInfoAuxDyn_yybb_highMass_pT_j2);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.yybb_highMass_weight", &HGamEventInfoAuxDyn_yybb_highMass_weight, &b_HGamEventInfoAuxDyn_yybb_highMass_weight);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.yAbs_j1_30", &HGamEventInfoAuxDyn_yAbs_j1_30, &b_HGamEventInfoAuxDyn_yAbs_j1_30);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.yybb_highMass_weight_discreteSFs", &HGamEventInfoAuxDyn_yybb_highMass_weight_discreteSFs, &b_HGamEventInfoAuxDyn_yybb_highMass_weight_discreteSFs);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.yybb_lowMass_MVA_score", &HGamEventInfoAuxDyn_yybb_lowMass_MVA_score, &b_HGamEventInfoAuxDyn_yybb_lowMass_MVA_score);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.yAbs_j2_30", &HGamEventInfoAuxDyn_yAbs_j2_30, &b_HGamEventInfoAuxDyn_yAbs_j2_30);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.yybb_lowMass_m_bb_uncnstrnd", &HGamEventInfoAuxDyn_yybb_lowMass_m_bb_uncnstrnd, &b_HGamEventInfoAuxDyn_yybb_lowMass_m_bb_uncnstrnd);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.pT_jj", &HGamEventInfoAuxDyn_pT_jj, &b_HGamEventInfoAuxDyn_pT_jj);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.yybb_lowMass_m_yybb", &HGamEventInfoAuxDyn_yybb_lowMass_m_yybb, &b_HGamEventInfoAuxDyn_yybb_lowMass_m_yybb);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.yybb_lowMass_pT_j1", &HGamEventInfoAuxDyn_yybb_lowMass_pT_j1, &b_HGamEventInfoAuxDyn_yybb_lowMass_pT_j1);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.m_jj", &HGamEventInfoAuxDyn_m_jj, &b_HGamEventInfoAuxDyn_m_jj);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.yybb_lowMass_pT_j2", &HGamEventInfoAuxDyn_yybb_lowMass_pT_j2, &b_HGamEventInfoAuxDyn_yybb_lowMass_pT_j2);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.yybb_lowMass_weight", &HGamEventInfoAuxDyn_yybb_lowMass_weight, &b_HGamEventInfoAuxDyn_yybb_lowMass_weight);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.m_jj_30", &HGamEventInfoAuxDyn_m_jj_30, &b_HGamEventInfoAuxDyn_m_jj_30);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.yybb_lowMass_weight_discreteSFs", &HGamEventInfoAuxDyn_yybb_lowMass_weight_discreteSFs, &b_HGamEventInfoAuxDyn_yybb_lowMass_weight_discreteSFs);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.Dy_j_j", &HGamEventInfoAuxDyn_Dy_j_j, &b_HGamEventInfoAuxDyn_Dy_j_j);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.Deta_j_j", &HGamEventInfoAuxDyn_Deta_j_j, &b_HGamEventInfoAuxDyn_Deta_j_j);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.yybb_bTagCat", &HGamEventInfoAuxDyn_yybb_bTagCat, &b_HGamEventInfoAuxDyn_yybb_bTagCat);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.yybb_highMass_cutFlow", &HGamEventInfoAuxDyn_yybb_highMass_cutFlow, &b_HGamEventInfoAuxDyn_yybb_highMass_cutFlow);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.Dy_j_j_30", &HGamEventInfoAuxDyn_Dy_j_j_30, &b_HGamEventInfoAuxDyn_Dy_j_j_30);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.yybb_highMass_truth_label_j1", &HGamEventInfoAuxDyn_yybb_highMass_truth_label_j1, &b_HGamEventInfoAuxDyn_yybb_highMass_truth_label_j1);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.Dy_yy_jj", &HGamEventInfoAuxDyn_Dy_yy_jj, &b_HGamEventInfoAuxDyn_Dy_yy_jj);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.yybb_highMass_truth_label_j2", &HGamEventInfoAuxDyn_yybb_highMass_truth_label_j2, &b_HGamEventInfoAuxDyn_yybb_highMass_truth_label_j2);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.Dy_yy_jj_30", &HGamEventInfoAuxDyn_Dy_yy_jj_30, &b_HGamEventInfoAuxDyn_Dy_yy_jj_30);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.yybb_lowMass_cutFlow", &HGamEventInfoAuxDyn_yybb_lowMass_cutFlow, &b_HGamEventInfoAuxDyn_yybb_lowMass_cutFlow);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.Dphi_j_j", &HGamEventInfoAuxDyn_Dphi_j_j, &b_HGamEventInfoAuxDyn_Dphi_j_j);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.yybb_lowMass_truth_label_j1", &HGamEventInfoAuxDyn_yybb_lowMass_truth_label_j1, &b_HGamEventInfoAuxDyn_yybb_lowMass_truth_label_j1);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.Dphi_j_j_30", &HGamEventInfoAuxDyn_Dphi_j_j_30, &b_HGamEventInfoAuxDyn_Dphi_j_j_30);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.yybb_lowMass_truth_label_j2", &HGamEventInfoAuxDyn_yybb_lowMass_truth_label_j2, &b_HGamEventInfoAuxDyn_yybb_lowMass_truth_label_j2);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.Dphi_j_j_30_signed", &HGamEventInfoAuxDyn_Dphi_j_j_30_signed, &b_HGamEventInfoAuxDyn_Dphi_j_j_30_signed);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.met_cat", &HGamEventInfoAuxDyn_met_cat, &b_HGamEventInfoAuxDyn_met_cat);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.Dphi_yy_jj", &HGamEventInfoAuxDyn_Dphi_yy_jj, &b_HGamEventInfoAuxDyn_Dphi_yy_jj);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.met_weight", &HGamEventInfoAuxDyn_met_weight, &b_HGamEventInfoAuxDyn_met_weight);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.Dphi_yy_jj_30", &HGamEventInfoAuxDyn_Dphi_yy_jj_30, &b_HGamEventInfoAuxDyn_Dphi_yy_jj_30);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.fcnc_etm", &HGamEventInfoAuxDyn_fcnc_etm, &b_HGamEventInfoAuxDyn_fcnc_etm);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.fcnc_mT", &HGamEventInfoAuxDyn_fcnc_mT, &b_HGamEventInfoAuxDyn_fcnc_mT);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.fcnc_phim", &HGamEventInfoAuxDyn_fcnc_phim, &b_HGamEventInfoAuxDyn_fcnc_phim);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.pT_yyjj_30", &HGamEventInfoAuxDyn_pT_yyjj_30, &b_HGamEventInfoAuxDyn_pT_yyjj_30);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.fcnc_weight", &HGamEventInfoAuxDyn_fcnc_weight, &b_HGamEventInfoAuxDyn_fcnc_weight);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.m_ee", &HGamEventInfoAuxDyn_m_ee, &b_HGamEventInfoAuxDyn_m_ee);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.fcnc_cat", &HGamEventInfoAuxDyn_fcnc_cat, &b_HGamEventInfoAuxDyn_fcnc_cat);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.m_mumu", &HGamEventInfoAuxDyn_m_mumu, &b_HGamEventInfoAuxDyn_m_mumu);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.fcnc_cutFlow", &HGamEventInfoAuxDyn_fcnc_cutFlow, &b_HGamEventInfoAuxDyn_fcnc_cutFlow);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.DRmin_y_j", &HGamEventInfoAuxDyn_DRmin_y_j, &b_HGamEventInfoAuxDyn_DRmin_y_j);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.fcnc_idLep", &HGamEventInfoAuxDyn_fcnc_idLep, &b_HGamEventInfoAuxDyn_fcnc_idLep);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.DRmin_y_j_2", &HGamEventInfoAuxDyn_DRmin_y_j_2, &b_HGamEventInfoAuxDyn_DRmin_y_j_2);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.fcnc_njet", &HGamEventInfoAuxDyn_fcnc_njet, &b_HGamEventInfoAuxDyn_fcnc_njet);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.DR_y_y", &HGamEventInfoAuxDyn_DR_y_y, &b_HGamEventInfoAuxDyn_DR_y_y);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.fcnc_njet30", &HGamEventInfoAuxDyn_fcnc_njet30, &b_HGamEventInfoAuxDyn_fcnc_njet30);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.Zepp", &HGamEventInfoAuxDyn_Zepp, &b_HGamEventInfoAuxDyn_Zepp);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.fcnc_ntopc", &HGamEventInfoAuxDyn_fcnc_ntopc, &b_HGamEventInfoAuxDyn_fcnc_ntopc);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.cosTS_yyjj", &HGamEventInfoAuxDyn_cosTS_yyjj, &b_HGamEventInfoAuxDyn_cosTS_yyjj);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.fcnc_nbTop2", &HGamEventInfoAuxDyn_fcnc_nbTop2, &b_HGamEventInfoAuxDyn_fcnc_nbTop2);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.sumTau_yyj_30", &HGamEventInfoAuxDyn_sumTau_yyj_30, &b_HGamEventInfoAuxDyn_sumTau_yyj_30);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.fcnc_mTop1", &HGamEventInfoAuxDyn_fcnc_mTop1, &b_HGamEventInfoAuxDyn_fcnc_mTop1);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.maxTau_yyj_30", &HGamEventInfoAuxDyn_maxTau_yyj_30, &b_HGamEventInfoAuxDyn_maxTau_yyj_30);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.fcnc_mTop2", &HGamEventInfoAuxDyn_fcnc_mTop2, &b_HGamEventInfoAuxDyn_fcnc_mTop2);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.met_TST", &HGamEventInfoAuxDyn_met_TST, &b_HGamEventInfoAuxDyn_met_TST);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.weightJvt", &HGamEventInfoAuxDyn_weightJvt, &b_HGamEventInfoAuxDyn_weightJvt);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.sumet_TST", &HGamEventInfoAuxDyn_sumet_TST, &b_HGamEventInfoAuxDyn_sumet_TST);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.weightJvt_30", &HGamEventInfoAuxDyn_weightJvt_30, &b_HGamEventInfoAuxDyn_weightJvt_30);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.phi_TST", &HGamEventInfoAuxDyn_phi_TST, &b_HGamEventInfoAuxDyn_phi_TST);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.weightJvt_50", &HGamEventInfoAuxDyn_weightJvt_50, &b_HGamEventInfoAuxDyn_weightJvt_50);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.N_j_btag", &HGamEventInfoAuxDyn_N_j_btag, &b_HGamEventInfoAuxDyn_N_j_btag);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.HT_30", &HGamEventInfoAuxDyn_HT_30, &b_HGamEventInfoAuxDyn_HT_30);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.N_j_btag30", &HGamEventInfoAuxDyn_N_j_btag30, &b_HGamEventInfoAuxDyn_N_j_btag30);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.HTall_30", &HGamEventInfoAuxDyn_HTall_30, &b_HGamEventInfoAuxDyn_HTall_30);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.m_alljet_30", &HGamEventInfoAuxDyn_m_alljet_30, &b_HGamEventInfoAuxDyn_m_alljet_30);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.catXS_ttH", &HGamEventInfoAuxDyn_catXS_ttH, &b_HGamEventInfoAuxDyn_catXS_ttH);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.weightCatXS_ttH", &HGamEventInfoAuxDyn_weightCatXS_ttH, &b_HGamEventInfoAuxDyn_weightCatXS_ttH);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.m_alljet", &HGamEventInfoAuxDyn_m_alljet, &b_HGamEventInfoAuxDyn_m_alljet);
   fChain->SetBranchAddress("HGamTruthPhotons", &HGamTruthPhotons, &b_HGamTruthPhotons);
   fChain->SetBranchAddress("HGamTruthPhotonsAux.", &HGamTruthPhotonsAux_, &b_HGamTruthPhotonsAux_);
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
   fChain->SetBranchAddress("HGamTruthElectrons", &HGamTruthElectrons, &b_HGamTruthElectrons);
   fChain->SetBranchAddress("HGamTruthElectronsAux.", &HGamTruthElectronsAux_, &b_HGamTruthElectronsAux_);
   fChain->SetBranchAddress("HGamTruthMuons", &HGamTruthMuons, &b_HGamTruthMuons);
   fChain->SetBranchAddress("HGamTruthMuonsAux.", &HGamTruthMuonsAux_, &b_HGamTruthMuonsAux_);
   fChain->SetBranchAddress("HGamAntiKt4TruthJets", &HGamAntiKt4TruthJets, &b_HGamAntiKt4TruthJets);
   fChain->SetBranchAddress("HGamAntiKt4TruthJetsAux.", &HGamAntiKt4TruthJetsAux_, &b_HGamAntiKt4TruthJetsAux_);
   fChain->SetBranchAddress("HGamAntiKt4TruthJetsAuxDyn.pt", &HGamAntiKt4TruthJetsAuxDyn_pt, &b_HGamAntiKt4TruthJetsAuxDyn_pt);
   fChain->SetBranchAddress("HGamAntiKt4TruthJetsAuxDyn.eta", &HGamAntiKt4TruthJetsAuxDyn_eta, &b_HGamAntiKt4TruthJetsAuxDyn_eta);
   fChain->SetBranchAddress("HGamAntiKt4TruthJetsAuxDyn.HadronConeExclTruthLabelID", &HGamAntiKt4TruthJetsAuxDyn_HadronConeExclTruthLabelID, &b_HGamAntiKt4TruthJetsAuxDyn_HadronConeExclTruthLabelID);
   fChain->SetBranchAddress("HGamAntiKt4TruthJetsAuxDyn.phi", &HGamAntiKt4TruthJetsAuxDyn_phi, &b_HGamAntiKt4TruthJetsAuxDyn_phi);
   fChain->SetBranchAddress("HGamAntiKt4TruthJetsAuxDyn.m", &HGamAntiKt4TruthJetsAuxDyn_m, &b_HGamAntiKt4TruthJetsAuxDyn_m);
   fChain->SetBranchAddress("HGamMET_Truth", &HGamMET_Truth, &b_HGamMET_Truth);
   fChain->SetBranchAddress("HGamMET_TruthAux.", &HGamMET_TruthAux_, &b_HGamMET_TruthAux_);
   fChain->SetBranchAddress("HGamMET_TruthAuxDyn.sumet", &HGamMET_TruthAuxDyn_sumet, &b_HGamMET_TruthAuxDyn_sumet);
   fChain->SetBranchAddress("HGamMET_TruthAuxDyn.name", &HGamMET_TruthAuxDyn_name, &b_HGamMET_TruthAuxDyn_name);
   fChain->SetBranchAddress("HGamMET_TruthAuxDyn.mpx", &HGamMET_TruthAuxDyn_mpx, &b_HGamMET_TruthAuxDyn_mpx);
   fChain->SetBranchAddress("HGamMET_TruthAuxDyn.mpy", &HGamMET_TruthAuxDyn_mpy, &b_HGamMET_TruthAuxDyn_mpy);
   fChain->SetBranchAddress("HGamMET_TruthAuxDyn.source", &HGamMET_TruthAuxDyn_source, &b_HGamMET_TruthAuxDyn_source);
   fChain->SetBranchAddress("HGamTruthHiggsBosons", &HGamTruthHiggsBosons, &b_HGamTruthHiggsBosons);
   fChain->SetBranchAddress("HGamTruthHiggsBosonsAux.", &HGamTruthHiggsBosonsAux_, &b_HGamTruthHiggsBosonsAux_);
   fChain->SetBranchAddress("HGamTruthHiggsBosonsAuxDyn.pt", &HGamTruthHiggsBosonsAuxDyn_pt, &b_HGamTruthHiggsBosonsAuxDyn_pt);
   fChain->SetBranchAddress("HGamTruthHiggsBosonsAuxDyn.eta", &HGamTruthHiggsBosonsAuxDyn_eta, &b_HGamTruthHiggsBosonsAuxDyn_eta);
   fChain->SetBranchAddress("HGamTruthHiggsBosonsAuxDyn.px", &HGamTruthHiggsBosonsAuxDyn_px, &b_HGamTruthHiggsBosonsAuxDyn_px);
   fChain->SetBranchAddress("HGamTruthHiggsBosonsAuxDyn.m", &HGamTruthHiggsBosonsAuxDyn_m, &b_HGamTruthHiggsBosonsAuxDyn_m);
   fChain->SetBranchAddress("HGamTruthHiggsBosonsAuxDyn.py", &HGamTruthHiggsBosonsAuxDyn_py, &b_HGamTruthHiggsBosonsAuxDyn_py);
   fChain->SetBranchAddress("HGamTruthHiggsBosonsAuxDyn.pz", &HGamTruthHiggsBosonsAuxDyn_pz, &b_HGamTruthHiggsBosonsAuxDyn_pz);
   fChain->SetBranchAddress("HGamTruthHiggsBosonsAuxDyn.e", &HGamTruthHiggsBosonsAuxDyn_e, &b_HGamTruthHiggsBosonsAuxDyn_e);
   fChain->SetBranchAddress("TruthEvents", &TruthEvents, &b_TruthEvents);
   fChain->SetBranchAddress("TruthEventsAux.", &TruthEventsAux_, &b_TruthEventsAux_);
   fChain->SetBranchAddress("TruthEventsAuxDyn.weights", &TruthEventsAuxDyn_weights, &b_TruthEventsAuxDyn_weights);
   fChain->SetBranchAddress("TruthEventsAuxDyn.PDFID1", &TruthEventsAuxDyn_PDFID1, &b_TruthEventsAuxDyn_PDFID1);
   fChain->SetBranchAddress("TruthEventsAuxDyn.PDFID2", &TruthEventsAuxDyn_PDFID2, &b_TruthEventsAuxDyn_PDFID2);
   fChain->SetBranchAddress("TruthEventsAuxDyn.PDGID1", &TruthEventsAuxDyn_PDGID1, &b_TruthEventsAuxDyn_PDGID1);
   fChain->SetBranchAddress("TruthEventsAuxDyn.PDGID2", &TruthEventsAuxDyn_PDGID2, &b_TruthEventsAuxDyn_PDGID2);
   fChain->SetBranchAddress("TruthEventsAuxDyn.Q", &TruthEventsAuxDyn_Q, &b_TruthEventsAuxDyn_Q);
   fChain->SetBranchAddress("TruthEventsAuxDyn.X1", &TruthEventsAuxDyn_X1, &b_TruthEventsAuxDyn_X1);
   fChain->SetBranchAddress("TruthEventsAuxDyn.X2", &TruthEventsAuxDyn_X2, &b_TruthEventsAuxDyn_X2);
   fChain->SetBranchAddress("TruthEventsAuxDyn.XF1", &TruthEventsAuxDyn_XF1, &b_TruthEventsAuxDyn_XF1);
   fChain->SetBranchAddress("TruthEventsAuxDyn.XF2", &TruthEventsAuxDyn_XF2, &b_TruthEventsAuxDyn_XF2);
   fChain->SetBranchAddress("HGamTruthEventInfo", &HGamTruthEventInfo, &b_HGamTruthEventInfo);
   fChain->SetBranchAddress("HGamTruthEventInfoAux.", &HGamTruthEventInfoAux_, &b_HGamTruthEventInfoAux_);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.HTall_30", &HGamTruthEventInfoAuxDyn_HTall_30, &b_HGamTruthEventInfoAuxDyn_HTall_30);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.isFiducial", &HGamTruthEventInfoAuxDyn_isFiducial, &b_HGamTruthEventInfoAuxDyn_isFiducial);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.isFiducialKinOnly", &HGamTruthEventInfoAuxDyn_isFiducialKinOnly, &b_HGamTruthEventInfoAuxDyn_isFiducialKinOnly);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.N_j_btag30", &HGamTruthEventInfoAuxDyn_N_j_btag30, &b_HGamTruthEventInfoAuxDyn_N_j_btag30);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.catXS_VBF", &HGamTruthEventInfoAuxDyn_catXS_VBF, &b_HGamTruthEventInfoAuxDyn_catXS_VBF);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.pT_h1", &HGamTruthEventInfoAuxDyn_pT_h1, &b_HGamTruthEventInfoAuxDyn_pT_h1);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.catXS_ttH", &HGamTruthEventInfoAuxDyn_catXS_ttH, &b_HGamTruthEventInfoAuxDyn_catXS_ttH);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.pT_h2", &HGamTruthEventInfoAuxDyn_pT_h2, &b_HGamTruthEventInfoAuxDyn_pT_h2);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.y_h1", &HGamTruthEventInfoAuxDyn_y_h1, &b_HGamTruthEventInfoAuxDyn_y_h1);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.y_h2", &HGamTruthEventInfoAuxDyn_y_h2, &b_HGamTruthEventInfoAuxDyn_y_h2);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.m_h1", &HGamTruthEventInfoAuxDyn_m_h1, &b_HGamTruthEventInfoAuxDyn_m_h1);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.m_h2", &HGamTruthEventInfoAuxDyn_m_h2, &b_HGamTruthEventInfoAuxDyn_m_h2);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.yAbs_yy", &HGamTruthEventInfoAuxDyn_yAbs_yy, &b_HGamTruthEventInfoAuxDyn_yAbs_yy);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.pTt_yy", &HGamTruthEventInfoAuxDyn_pTt_yy, &b_HGamTruthEventInfoAuxDyn_pTt_yy);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.m_yy", &HGamTruthEventInfoAuxDyn_m_yy, &b_HGamTruthEventInfoAuxDyn_m_yy);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.passMeyCut", &HGamTruthEventInfoAuxDyn_passMeyCut, &b_HGamTruthEventInfoAuxDyn_passMeyCut);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.truthCategory", &HGamTruthEventInfoAuxDyn_truthCategory, &b_HGamTruthEventInfoAuxDyn_truthCategory);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.pT_yy", &HGamTruthEventInfoAuxDyn_pT_yy, &b_HGamTruthEventInfoAuxDyn_pT_yy);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.truthProcess", &HGamTruthEventInfoAuxDyn_truthProcess, &b_HGamTruthEventInfoAuxDyn_truthProcess);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.pT_y1", &HGamTruthEventInfoAuxDyn_pT_y1, &b_HGamTruthEventInfoAuxDyn_pT_y1);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.pT_y2", &HGamTruthEventInfoAuxDyn_pT_y2, &b_HGamTruthEventInfoAuxDyn_pT_y2);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.isVyyOverlap", &HGamTruthEventInfoAuxDyn_isVyyOverlap, &b_HGamTruthEventInfoAuxDyn_isVyyOverlap);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.E_y1", &HGamTruthEventInfoAuxDyn_E_y1, &b_HGamTruthEventInfoAuxDyn_E_y1);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.E_y2", &HGamTruthEventInfoAuxDyn_E_y2, &b_HGamTruthEventInfoAuxDyn_E_y2);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.pT_hard", &HGamTruthEventInfoAuxDyn_pT_hard, &b_HGamTruthEventInfoAuxDyn_pT_hard);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.cosTS_yy", &HGamTruthEventInfoAuxDyn_cosTS_yy, &b_HGamTruthEventInfoAuxDyn_cosTS_yy);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.phiStar_yy", &HGamTruthEventInfoAuxDyn_phiStar_yy, &b_HGamTruthEventInfoAuxDyn_phiStar_yy);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.Dy_y_y", &HGamTruthEventInfoAuxDyn_Dy_y_y, &b_HGamTruthEventInfoAuxDyn_Dy_y_y);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.N_e", &HGamTruthEventInfoAuxDyn_N_e, &b_HGamTruthEventInfoAuxDyn_N_e);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.N_mu", &HGamTruthEventInfoAuxDyn_N_mu, &b_HGamTruthEventInfoAuxDyn_N_mu);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.N_lep", &HGamTruthEventInfoAuxDyn_N_lep, &b_HGamTruthEventInfoAuxDyn_N_lep);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.N_lep_15", &HGamTruthEventInfoAuxDyn_N_lep_15, &b_HGamTruthEventInfoAuxDyn_N_lep_15);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.N_j", &HGamTruthEventInfoAuxDyn_N_j, &b_HGamTruthEventInfoAuxDyn_N_j);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.N_j_30", &HGamTruthEventInfoAuxDyn_N_j_30, &b_HGamTruthEventInfoAuxDyn_N_j_30);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.N_j_50", &HGamTruthEventInfoAuxDyn_N_j_50, &b_HGamTruthEventInfoAuxDyn_N_j_50);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.N_j_central", &HGamTruthEventInfoAuxDyn_N_j_central, &b_HGamTruthEventInfoAuxDyn_N_j_central);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.N_j_central30", &HGamTruthEventInfoAuxDyn_N_j_central30, &b_HGamTruthEventInfoAuxDyn_N_j_central30);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.pT_j1_30", &HGamTruthEventInfoAuxDyn_pT_j1_30, &b_HGamTruthEventInfoAuxDyn_pT_j1_30);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.pT_j1", &HGamTruthEventInfoAuxDyn_pT_j1, &b_HGamTruthEventInfoAuxDyn_pT_j1);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.pT_j2_30", &HGamTruthEventInfoAuxDyn_pT_j2_30, &b_HGamTruthEventInfoAuxDyn_pT_j2_30);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.pT_j2", &HGamTruthEventInfoAuxDyn_pT_j2, &b_HGamTruthEventInfoAuxDyn_pT_j2);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.pT_j3_30", &HGamTruthEventInfoAuxDyn_pT_j3_30, &b_HGamTruthEventInfoAuxDyn_pT_j3_30);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.met_NonInt", &HGamTruthEventInfoAuxDyn_met_NonInt, &b_HGamTruthEventInfoAuxDyn_met_NonInt);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.yAbs_j1_30", &HGamTruthEventInfoAuxDyn_yAbs_j1_30, &b_HGamTruthEventInfoAuxDyn_yAbs_j1_30);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.sumet_Int", &HGamTruthEventInfoAuxDyn_sumet_Int, &b_HGamTruthEventInfoAuxDyn_sumet_Int);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.met_NonHad", &HGamTruthEventInfoAuxDyn_met_NonHad, &b_HGamTruthEventInfoAuxDyn_met_NonHad);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.yAbs_j2_30", &HGamTruthEventInfoAuxDyn_yAbs_j2_30, &b_HGamTruthEventInfoAuxDyn_yAbs_j2_30);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.isFiducialLowHighMyy", &HGamTruthEventInfoAuxDyn_isFiducialLowHighMyy, &b_HGamTruthEventInfoAuxDyn_isFiducialLowHighMyy);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.pT_jj", &HGamTruthEventInfoAuxDyn_pT_jj, &b_HGamTruthEventInfoAuxDyn_pT_jj);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.isFiducialExotic", &HGamTruthEventInfoAuxDyn_isFiducialExotic, &b_HGamTruthEventInfoAuxDyn_isFiducialExotic);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.m_jj", &HGamTruthEventInfoAuxDyn_m_jj, &b_HGamTruthEventInfoAuxDyn_m_jj);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.m_jj_30", &HGamTruthEventInfoAuxDyn_m_jj_30, &b_HGamTruthEventInfoAuxDyn_m_jj_30);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.Dy_j_j", &HGamTruthEventInfoAuxDyn_Dy_j_j, &b_HGamTruthEventInfoAuxDyn_Dy_j_j);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.Dy_j_j_30", &HGamTruthEventInfoAuxDyn_Dy_j_j_30, &b_HGamTruthEventInfoAuxDyn_Dy_j_j_30);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.Dy_yy_jj_30", &HGamTruthEventInfoAuxDyn_Dy_yy_jj_30, &b_HGamTruthEventInfoAuxDyn_Dy_yy_jj_30);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.Dphi_j_j", &HGamTruthEventInfoAuxDyn_Dphi_j_j, &b_HGamTruthEventInfoAuxDyn_Dphi_j_j);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.Dphi_j_j_30", &HGamTruthEventInfoAuxDyn_Dphi_j_j_30, &b_HGamTruthEventInfoAuxDyn_Dphi_j_j_30);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.Dphi_j_j_30_signed", &HGamTruthEventInfoAuxDyn_Dphi_j_j_30_signed, &b_HGamTruthEventInfoAuxDyn_Dphi_j_j_30_signed);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.Dphi_yy_jj", &HGamTruthEventInfoAuxDyn_Dphi_yy_jj, &b_HGamTruthEventInfoAuxDyn_Dphi_yy_jj);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.Dphi_yy_jj_30", &HGamTruthEventInfoAuxDyn_Dphi_yy_jj_30, &b_HGamTruthEventInfoAuxDyn_Dphi_yy_jj_30);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.pT_yyjj_30", &HGamTruthEventInfoAuxDyn_pT_yyjj_30, &b_HGamTruthEventInfoAuxDyn_pT_yyjj_30);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.m_ee", &HGamTruthEventInfoAuxDyn_m_ee, &b_HGamTruthEventInfoAuxDyn_m_ee);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.m_mumu", &HGamTruthEventInfoAuxDyn_m_mumu, &b_HGamTruthEventInfoAuxDyn_m_mumu);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.DRmin_y_j", &HGamTruthEventInfoAuxDyn_DRmin_y_j, &b_HGamTruthEventInfoAuxDyn_DRmin_y_j);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.DR_y_y", &HGamTruthEventInfoAuxDyn_DR_y_y, &b_HGamTruthEventInfoAuxDyn_DR_y_y);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.Zepp", &HGamTruthEventInfoAuxDyn_Zepp, &b_HGamTruthEventInfoAuxDyn_Zepp);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.cosTS_yyjj", &HGamTruthEventInfoAuxDyn_cosTS_yyjj, &b_HGamTruthEventInfoAuxDyn_cosTS_yyjj);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.sumTau_yyj_30", &HGamTruthEventInfoAuxDyn_sumTau_yyj_30, &b_HGamTruthEventInfoAuxDyn_sumTau_yyj_30);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.maxTau_yyj_30", &HGamTruthEventInfoAuxDyn_maxTau_yyj_30, &b_HGamTruthEventInfoAuxDyn_maxTau_yyj_30);
   fChain->SetBranchAddress("HGamTruthEventInfoAuxDyn.HT_30", &HGamTruthEventInfoAuxDyn_HT_30, &b_HGamTruthEventInfoAuxDyn_HT_30);
   fChain->SetBranchAddress("EventInfo", &EventInfo, &b_EventInfo);
   fChain->SetBranchAddress("EventInfoAux.runNumber", &EventInfoAux_runNumber, &b_EventInfoAux_runNumber);
   fChain->SetBranchAddress("EventInfoAux.eventNumber", &EventInfoAux_eventNumber, &b_EventInfoAux_eventNumber);
   fChain->SetBranchAddress("EventInfoAux.lumiBlock", &EventInfoAux_lumiBlock, &b_EventInfoAux_lumiBlock);
   fChain->SetBranchAddress("EventInfoAux.timeStamp", &EventInfoAux_timeStamp, &b_EventInfoAux_timeStamp);
   fChain->SetBranchAddress("EventInfoAux.timeStampNSOffset", &EventInfoAux_timeStampNSOffset, &b_EventInfoAux_timeStampNSOffset);
   fChain->SetBranchAddress("EventInfoAux.bcid", &EventInfoAux_bcid, &b_EventInfoAux_bcid);
   fChain->SetBranchAddress("EventInfoAux.detectorMask0", &EventInfoAux_detectorMask0, &b_EventInfoAux_detectorMask0);
   fChain->SetBranchAddress("EventInfoAux.detectorMask1", &EventInfoAux_detectorMask1, &b_EventInfoAux_detectorMask1);
   fChain->SetBranchAddress("EventInfoAux.detectorMask2", &EventInfoAux_detectorMask2, &b_EventInfoAux_detectorMask2);
   fChain->SetBranchAddress("EventInfoAux.detectorMask3", &EventInfoAux_detectorMask3, &b_EventInfoAux_detectorMask3);
   fChain->SetBranchAddress("EventInfoAux.eventTypeBitmask", &EventInfoAux_eventTypeBitmask, &b_EventInfoAux_eventTypeBitmask);
   fChain->SetBranchAddress("EventInfoAux.statusElement", &EventInfoAux_statusElement, &b_EventInfoAux_statusElement);
   fChain->SetBranchAddress("EventInfoAux.extendedLevel1ID", &EventInfoAux_extendedLevel1ID, &b_EventInfoAux_extendedLevel1ID);
   fChain->SetBranchAddress("EventInfoAux.level1TriggerType", &EventInfoAux_level1TriggerType, &b_EventInfoAux_level1TriggerType);
   fChain->SetBranchAddress("EventInfoAux.streamTagNames", &EventInfoAux_streamTagNames, &b_EventInfoAux_streamTagNames);
   fChain->SetBranchAddress("EventInfoAux.streamTagTypes", &EventInfoAux_streamTagTypes, &b_EventInfoAux_streamTagTypes);
   fChain->SetBranchAddress("EventInfoAux.streamTagObeysLumiblock", &EventInfoAux_streamTagObeysLumiblock, &b_EventInfoAux_streamTagObeysLumiblock);
   fChain->SetBranchAddress("EventInfoAux.actualInteractionsPerCrossing", &EventInfoAux_actualInteractionsPerCrossing, &b_EventInfoAux_actualInteractionsPerCrossing);
   fChain->SetBranchAddress("EventInfoAux.averageInteractionsPerCrossing", &EventInfoAux_averageInteractionsPerCrossing, &b_EventInfoAux_averageInteractionsPerCrossing);
   fChain->SetBranchAddress("EventInfoAux.pixelFlags", &EventInfoAux_pixelFlags, &b_EventInfoAux_pixelFlags);
   fChain->SetBranchAddress("EventInfoAux.sctFlags", &EventInfoAux_sctFlags, &b_EventInfoAux_sctFlags);
   fChain->SetBranchAddress("EventInfoAux.trtFlags", &EventInfoAux_trtFlags, &b_EventInfoAux_trtFlags);
   fChain->SetBranchAddress("EventInfoAux.larFlags", &EventInfoAux_larFlags, &b_EventInfoAux_larFlags);
   fChain->SetBranchAddress("EventInfoAux.tileFlags", &EventInfoAux_tileFlags, &b_EventInfoAux_tileFlags);
   fChain->SetBranchAddress("EventInfoAux.muonFlags", &EventInfoAux_muonFlags, &b_EventInfoAux_muonFlags);
   fChain->SetBranchAddress("EventInfoAux.forwardDetFlags", &EventInfoAux_forwardDetFlags, &b_EventInfoAux_forwardDetFlags);
   fChain->SetBranchAddress("EventInfoAux.coreFlags", &EventInfoAux_coreFlags, &b_EventInfoAux_coreFlags);
   fChain->SetBranchAddress("EventInfoAux.backgroundFlags", &EventInfoAux_backgroundFlags, &b_EventInfoAux_backgroundFlags);
   fChain->SetBranchAddress("EventInfoAux.lumiFlags", &EventInfoAux_lumiFlags, &b_EventInfoAux_lumiFlags);
   fChain->SetBranchAddress("EventInfoAux.beamPosX", &EventInfoAux_beamPosX, &b_EventInfoAux_beamPosX);
   fChain->SetBranchAddress("EventInfoAux.beamPosY", &EventInfoAux_beamPosY, &b_EventInfoAux_beamPosY);
   fChain->SetBranchAddress("EventInfoAux.beamPosZ", &EventInfoAux_beamPosZ, &b_EventInfoAux_beamPosZ);
   fChain->SetBranchAddress("EventInfoAux.beamPosSigmaX", &EventInfoAux_beamPosSigmaX, &b_EventInfoAux_beamPosSigmaX);
   fChain->SetBranchAddress("EventInfoAux.beamPosSigmaY", &EventInfoAux_beamPosSigmaY, &b_EventInfoAux_beamPosSigmaY);
   fChain->SetBranchAddress("EventInfoAux.beamPosSigmaZ", &EventInfoAux_beamPosSigmaZ, &b_EventInfoAux_beamPosSigmaZ);
   fChain->SetBranchAddress("EventInfoAux.beamPosSigmaXY", &EventInfoAux_beamPosSigmaXY, &b_EventInfoAux_beamPosSigmaXY);
   fChain->SetBranchAddress("EventInfoAux.beamTiltXZ", &EventInfoAux_beamTiltXZ, &b_EventInfoAux_beamTiltXZ);
   fChain->SetBranchAddress("EventInfoAux.beamTiltYZ", &EventInfoAux_beamTiltYZ, &b_EventInfoAux_beamTiltYZ);
   fChain->SetBranchAddress("EventInfoAux.beamStatus", &EventInfoAux_beamStatus, &b_EventInfoAux_beamStatus);
   fChain->SetBranchAddress("EventInfoAuxDyn.mcEventWeights", &EventInfoAuxDyn_mcEventWeights, &b_EventInfoAuxDyn_mcEventWeights);
   fChain->SetBranchAddress("EventInfoAuxDyn.HTXS_Stage1_Category_pTjet30", &EventInfoAuxDyn_HTXS_Stage1_Category_pTjet30, &b_EventInfoAuxDyn_HTXS_Stage1_Category_pTjet30);
   fChain->SetBranchAddress("EventInfoAuxDyn.HTXS_Stage1_FineIndex_pTjet25", &EventInfoAuxDyn_HTXS_Stage1_FineIndex_pTjet25, &b_EventInfoAuxDyn_HTXS_Stage1_FineIndex_pTjet25);
   fChain->SetBranchAddress("EventInfoAuxDyn.HTXS_Stage1_FineIndex_pTjet30", &EventInfoAuxDyn_HTXS_Stage1_FineIndex_pTjet30, &b_EventInfoAuxDyn_HTXS_Stage1_FineIndex_pTjet30);
   fChain->SetBranchAddress("EventInfoAuxDyn.HTXS_V_jets30_eta", &EventInfoAuxDyn_HTXS_V_jets30_eta, &b_EventInfoAuxDyn_HTXS_V_jets30_eta);
   fChain->SetBranchAddress("EventInfoAuxDyn.passTrig_HLT_g35_loose_g25_loose", &EventInfoAuxDyn_passTrig_HLT_g35_loose_g25_loose, &b_EventInfoAuxDyn_passTrig_HLT_g35_loose_g25_loose);
   fChain->SetBranchAddress("EventInfoAuxDyn.HTXS_V_jets30_m", &EventInfoAuxDyn_HTXS_V_jets30_m, &b_EventInfoAuxDyn_HTXS_V_jets30_m);
   fChain->SetBranchAddress("EventInfoAuxDyn.HTXS_V_jets30_phi", &EventInfoAuxDyn_HTXS_V_jets30_phi, &b_EventInfoAuxDyn_HTXS_V_jets30_phi);
   fChain->SetBranchAddress("EventInfoAuxDyn.HTXS_V_jets30_pt", &EventInfoAuxDyn_HTXS_V_jets30_pt, &b_EventInfoAuxDyn_HTXS_V_jets30_pt);
   fChain->SetBranchAddress("EventInfoAuxDyn.HTXS_V_pt", &EventInfoAuxDyn_HTXS_V_pt, &b_EventInfoAuxDyn_HTXS_V_pt);
   fChain->SetBranchAddress("EventInfoAuxDyn.passTrig_HLT_g35_medium_g25_medium", &EventInfoAuxDyn_passTrig_HLT_g35_medium_g25_medium, &b_EventInfoAuxDyn_passTrig_HLT_g35_medium_g25_medium);
   fChain->SetBranchAddress("EventInfoAuxDyn.HTXS_errorCode", &EventInfoAuxDyn_HTXS_errorCode, &b_EventInfoAuxDyn_HTXS_errorCode);
   fChain->SetBranchAddress("EventInfoAuxDyn.HTXS_Njets_pTjet25", &EventInfoAuxDyn_HTXS_Njets_pTjet25, &b_EventInfoAuxDyn_HTXS_Njets_pTjet25);
   fChain->SetBranchAddress("EventInfoAuxDyn.passTrig_HLT_2g50_loose", &EventInfoAuxDyn_passTrig_HLT_2g50_loose, &b_EventInfoAuxDyn_passTrig_HLT_2g50_loose);
   fChain->SetBranchAddress("EventInfoAuxDyn.HTXS_prodMode", &EventInfoAuxDyn_HTXS_prodMode, &b_EventInfoAuxDyn_HTXS_prodMode);
   fChain->SetBranchAddress("EventInfoAuxDyn.HTXS_Njets_pTjet30", &EventInfoAuxDyn_HTXS_Njets_pTjet30, &b_EventInfoAuxDyn_HTXS_Njets_pTjet30);
   fChain->SetBranchAddress("EventInfoAuxDyn.mcChannelNumber", &EventInfoAuxDyn_mcChannelNumber, &b_EventInfoAuxDyn_mcChannelNumber);
   fChain->SetBranchAddress("EventInfoAuxDyn.HTXS_Stage0_Category", &EventInfoAuxDyn_HTXS_Stage0_Category, &b_EventInfoAuxDyn_HTXS_Stage0_Category);
   fChain->SetBranchAddress("EventInfoAuxDyn.HTXS_Stage1_Category_pTjet25", &EventInfoAuxDyn_HTXS_Stage1_Category_pTjet25, &b_EventInfoAuxDyn_HTXS_Stage1_Category_pTjet25);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.truthLink", &HGamPhotonsAuxDyn_truthLink, &b_HGamPhotonsAuxDyn_truthLink);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.parentPdgId", &HGamPhotonsAuxDyn_parentPdgId, &b_HGamPhotonsAuxDyn_parentPdgId);
   fChain->SetBranchAddress("HGamPhotonsAuxDyn.pdgId", &HGamPhotonsAuxDyn_pdgId, &b_HGamPhotonsAuxDyn_pdgId);
   fChain->SetBranchAddress("HGamTruthPhotonsAuxDyn.recoLink", &HGamTruthPhotonsAuxDyn_recoLink, &b_HGamTruthPhotonsAuxDyn_recoLink);
   fChain->SetBranchAddress("HGamElectronsAuxDyn.scaleFactor", &HGamElectronsAuxDyn_scaleFactor, &b_HGamElectronsAuxDyn_scaleFactor);
   fChain->SetBranchAddress("HGamElectronsAuxDyn.ptvarcone20", &HGamElectronsAuxDyn_ptvarcone20, &b_HGamElectronsAuxDyn_ptvarcone20);
   fChain->SetBranchAddress("HGamElectronsAuxDyn.pt", &HGamElectronsAuxDyn_pt, &b_HGamElectronsAuxDyn_pt);
   fChain->SetBranchAddress("HGamElectronsAuxDyn.eta", &HGamElectronsAuxDyn_eta, &b_HGamElectronsAuxDyn_eta);
   fChain->SetBranchAddress("HGamElectronsAuxDyn.topoetcone20", &HGamElectronsAuxDyn_topoetcone20, &b_HGamElectronsAuxDyn_topoetcone20);
   fChain->SetBranchAddress("HGamElectronsAuxDyn.phi", &HGamElectronsAuxDyn_phi, &b_HGamElectronsAuxDyn_phi);
   fChain->SetBranchAddress("HGamElectronsAuxDyn.m", &HGamElectronsAuxDyn_m, &b_HGamElectronsAuxDyn_m);
   fChain->SetBranchAddress("HGamElectronsAuxDyn.eta_s2", &HGamElectronsAuxDyn_eta_s2, &b_HGamElectronsAuxDyn_eta_s2);
   fChain->SetBranchAddress("HGamElectronsAuxDyn.charge", &HGamElectronsAuxDyn_charge, &b_HGamElectronsAuxDyn_charge);
   fChain->SetBranchAddress("HGamElectronsAuxDyn.isTight", &HGamElectronsAuxDyn_isTight, &b_HGamElectronsAuxDyn_isTight);
   fChain->SetBranchAddress("HGamTruthElectronsAuxDyn.truthOrigin", &HGamTruthElectronsAuxDyn_truthOrigin, &b_HGamTruthElectronsAuxDyn_truthOrigin);
   fChain->SetBranchAddress("HGamTruthElectronsAuxDyn.pt", &HGamTruthElectronsAuxDyn_pt, &b_HGamTruthElectronsAuxDyn_pt);
   fChain->SetBranchAddress("HGamTruthElectronsAuxDyn.truthType", &HGamTruthElectronsAuxDyn_truthType, &b_HGamTruthElectronsAuxDyn_truthType);
   fChain->SetBranchAddress("HGamTruthElectronsAuxDyn.eta", &HGamTruthElectronsAuxDyn_eta, &b_HGamTruthElectronsAuxDyn_eta);
   fChain->SetBranchAddress("HGamTruthElectronsAuxDyn.px", &HGamTruthElectronsAuxDyn_px, &b_HGamTruthElectronsAuxDyn_px);
   fChain->SetBranchAddress("HGamTruthElectronsAuxDyn.m", &HGamTruthElectronsAuxDyn_m, &b_HGamTruthElectronsAuxDyn_m);
   fChain->SetBranchAddress("HGamTruthElectronsAuxDyn.py", &HGamTruthElectronsAuxDyn_py, &b_HGamTruthElectronsAuxDyn_py);
   fChain->SetBranchAddress("HGamTruthElectronsAuxDyn.pz", &HGamTruthElectronsAuxDyn_pz, &b_HGamTruthElectronsAuxDyn_pz);
   fChain->SetBranchAddress("HGamTruthElectronsAuxDyn.e", &HGamTruthElectronsAuxDyn_e, &b_HGamTruthElectronsAuxDyn_e);
   fChain->SetBranchAddress("HGamElectronsAuxDyn.truthLink", &HGamElectronsAuxDyn_truthLink, &b_HGamElectronsAuxDyn_truthLink);
   fChain->SetBranchAddress("HGamTruthElectronsAuxDyn.recoLink", &HGamTruthElectronsAuxDyn_recoLink, &b_HGamTruthElectronsAuxDyn_recoLink);
   fChain->SetBranchAddress("HGamTruthMuonsAuxDyn.truthOrigin", &HGamTruthMuonsAuxDyn_truthOrigin, &b_HGamTruthMuonsAuxDyn_truthOrigin);
   fChain->SetBranchAddress("HGamTruthMuonsAuxDyn.pt", &HGamTruthMuonsAuxDyn_pt, &b_HGamTruthMuonsAuxDyn_pt);
   fChain->SetBranchAddress("HGamTruthMuonsAuxDyn.truthType", &HGamTruthMuonsAuxDyn_truthType, &b_HGamTruthMuonsAuxDyn_truthType);
   fChain->SetBranchAddress("HGamTruthMuonsAuxDyn.eta", &HGamTruthMuonsAuxDyn_eta, &b_HGamTruthMuonsAuxDyn_eta);
   fChain->SetBranchAddress("HGamTruthMuonsAuxDyn.px", &HGamTruthMuonsAuxDyn_px, &b_HGamTruthMuonsAuxDyn_px);
   fChain->SetBranchAddress("HGamTruthMuonsAuxDyn.m", &HGamTruthMuonsAuxDyn_m, &b_HGamTruthMuonsAuxDyn_m);
   fChain->SetBranchAddress("HGamTruthMuonsAuxDyn.py", &HGamTruthMuonsAuxDyn_py, &b_HGamTruthMuonsAuxDyn_py);
   fChain->SetBranchAddress("HGamTruthMuonsAuxDyn.pz", &HGamTruthMuonsAuxDyn_pz, &b_HGamTruthMuonsAuxDyn_pz);
   fChain->SetBranchAddress("HGamTruthMuonsAuxDyn.e", &HGamTruthMuonsAuxDyn_e, &b_HGamTruthMuonsAuxDyn_e);
   fChain->SetBranchAddress("HGamMuonsAuxDyn.scaleFactor", &HGamMuonsAuxDyn_scaleFactor, &b_HGamMuonsAuxDyn_scaleFactor);
   fChain->SetBranchAddress("HGamMuonsAuxDyn.ptvarcone20", &HGamMuonsAuxDyn_ptvarcone20, &b_HGamMuonsAuxDyn_ptvarcone20);
   fChain->SetBranchAddress("HGamMuonsAuxDyn.pt", &HGamMuonsAuxDyn_pt, &b_HGamMuonsAuxDyn_pt);
   fChain->SetBranchAddress("HGamMuonsAuxDyn.isBad", &HGamMuonsAuxDyn_isBad, &b_HGamMuonsAuxDyn_isBad);
   fChain->SetBranchAddress("HGamMuonsAuxDyn.passIPCut", &HGamMuonsAuxDyn_passIPCut, &b_HGamMuonsAuxDyn_passIPCut);
   fChain->SetBranchAddress("HGamMuonsAuxDyn.eta", &HGamMuonsAuxDyn_eta, &b_HGamMuonsAuxDyn_eta);
   fChain->SetBranchAddress("HGamMuonsAuxDyn.topoetcone20", &HGamMuonsAuxDyn_topoetcone20, &b_HGamMuonsAuxDyn_topoetcone20);
   fChain->SetBranchAddress("HGamMuonsAuxDyn.phi", &HGamMuonsAuxDyn_phi, &b_HGamMuonsAuxDyn_phi);
   fChain->SetBranchAddress("HGamMuonsAuxDyn.muonType", &HGamMuonsAuxDyn_muonType, &b_HGamMuonsAuxDyn_muonType);
   fChain->SetBranchAddress("HGamMuonsAuxDyn.charge", &HGamMuonsAuxDyn_charge, &b_HGamMuonsAuxDyn_charge);
   fChain->SetBranchAddress("HGamMuonsAuxDyn.isTight", &HGamMuonsAuxDyn_isTight, &b_HGamMuonsAuxDyn_isTight);
   fChain->SetBranchAddress("HGamEventInfoAuxDyn.pT_yyjj", &HGamEventInfoAuxDyn_pT_yyjj, &b_HGamEventInfoAuxDyn_pT_yyjj);
   Notify();
}

Bool_t CollectionTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void CollectionTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t CollectionTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef CollectionTree_cxx
