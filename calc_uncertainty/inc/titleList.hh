using namespace std;

map<TString, TString> createTitleList(){
  map<TString, TString> title;   
  title["C"] = "#kappa";
  title["CV"] = "#kappa_{V}";
  title["CZ"] = "#kappa_{Z}";
  title["CF"] = "#kappa_{F}";
  title["Cq"] = "#kappa_{q}";
  title["CGl"] = "#kappa_{g}";
  title["CGa"] = "#kappa_{#gamma}";
  title["BRinv"] = "B_{i,u}";
  title["RFv"] = "#lambda_{FV}";
  title["RGv"] = "#lambda_{#gammaV}";
  title["RVVh"] = "#kappa_{VV}";
  title["RWz"] = "#lambda_{WZ}";
  title["RFz"] = "#lambda_{FZ}";
  title["RGz"] = "#lambda_{#gammaZ}";
  title["RZZh"] = "#kappa_{ZZ}";
  title["Rdu"] = "#lambda_{du}";
  title["Cu"] = "#kappa_{u}";
  title["RVu"] = "#lambda_{Vu}";
  title["Ruuh"] = "#kappa_{uu}";
  title["Rqqh"] = "#kappa_{qq}";
  title["Rlq"] = "#lambda_{lq}";
  title["RVq"] = "#lambda_{Vq}";
  title["RVg"] = "#lambda_{Vg}";
  title["RGav"] = "#lambda_{#gammaV}";
  title["RGlVh"] = "#kappa_{gV}";
  title["vbf_o_ggf"] = "#mu_{VBF}/#mu_{ggF}";
  title["vbf_o_ggf_ww"] = "#mu_{VBF}/#mu_{ggH}";
  title["vbf_o_ggf_tt"] = "#mu_{#it{VBF}}/#mu_{#it{ggH}}";
  title["vh_o_ggf"] = "#mu_{#it{VH}}/#mu_{ggF}";
  title["tth_o_ggf"] = "#mu_{#it{t#bar{t}H}}/#mu_{ggF}";
  title["mu_ggF"] = "#mu_{ggF}";
  title["mu_ggH"] = "#mu_{ggH}";
  title["mu_VBF"] = "#mu_{VBF}";
  title["mu_WH"] = "#mu_{WH}";
  title["mu_ZH"] = "#mu_{ZH}";
  title["mu_ttH"] = "#mu_{ttH}";
  title["mu_ggf"] = "#mu_{ggF}";
  title["mu_vbf"] = "#mu_{VBF}";
  title["mu_vh"] = "#mu_{WH+ZH}";
  title["mu_tth"] = "#mu_{ttH}";
  title["mu"] = "#mu";
  title["muF_gg"] = "#mu_{ggF+ttH(+bbH)}^{#gamma#gamma}";
  title["muV_gg"] = "#mu_{VBF+VH}^{#gamma#gamma}";
  title["mu_ZZ"] = "#mu^{ZZ}";
  title["mu_Hc"] = "BR(t#rightarrowHc) [%]";
  title["mu_Hu"] = "BR(t#rightarrowHu) [%]";

  title["m_H"] = "m_{H} [GeV]";
  title["mH"] = "m_{H} [GeV]";
  title["mX"] = "m_{X} [GeV]";
  title["wX"] = "#Gamma_{X} [GeV]";
  title["MH"] = "m_{H} [GeV]";
  title["CT"] = "#kappa_{t}";
  title["mu_rest"] = "#mu_{non-ggF}";
  title["dMH"] = "#Deltam_{H} [GeV]";
  title["dmH_gZ"] = "#Deltam_{H}(#gamma#gamma-ZZ*) [GeV]";
  title["dmH_exp"] = "#Deltam_{H}(ATLAS-CMS) [GeV]";
  title["lambda_muF_gg"] = "#mu_{ggF+ttH+bbH}^{#gamma#gamma ATLAS}/#mu_{ggF+ttH}^{#gamma#gamma CMS}";
  title["lambda_mu_ZZ"] = "#mu^{ZZ ATLAS}/#mu^{ZZ CMS}";

  title["mG"] = "m_{G*} [GeV]";
  title["GkM"] = "#it{k}/#bar{M}_{Pl}";
  title["dxs"] = "#Delta#sigma#timesBR [fb]";
  title["xs"] = "#sigma#timesBR [fb]";
  title["ratio"] = "#sigma#timesBR_{8 TeV}/#sigma#timesBR_{13 TeV}";
  
  return title;
}

bool getMinFile(TChain *tmin, TString jobname, TString poiName){
  TString minFile="root/"+jobname+Form("/opt_%s=1_-5_5_*.root",poiName.Data());
  bool m_nominfile=!(tmin->Add(minFile)==1);

  if(m_nominfile){
    minFile="root/"+jobname+Form("/opt_*%s=1_0_5_*.root",poiName.Data());
    m_nominfile=!(tmin->Add(minFile)==1);
  }
  if(m_nominfile){
    minFile="root/"+jobname+Form("/opt_*%s=0_0_1_*.root",poiName.Data());
    m_nominfile=!(tmin->Add(minFile)==1);
  }
  if(m_nominfile){
    minFile="root/"+jobname+Form("/opt_%s=0_-20_20_*.root",poiName.Data());
    m_nominfile=!(tmin->Add(minFile)==1);
  }
  if(m_nominfile){
    minFile="root/"+jobname+Form("/opt_*%s=45_0_100_*.root",poiName.Data());
    m_nominfile=!(tmin->Add(minFile)==1);
  }

  if(m_nominfile){
    minFile="root/"+jobname+Form("/opt_*%s=10_0_100_*.root",poiName.Data());
    m_nominfile=!(tmin->Add(minFile)==1);
  }
  if(m_nominfile){
    minFile="root/"+jobname+Form("/opt_*%s=0._-5_5_*.root",poiName.Data());
    m_nominfile=!(tmin->Add(minFile)==1);
  }

  if(m_nominfile){
    minFile="root/"+jobname+Form("/opt_%s=0._-0.5_0.5*.root",poiName.Data());
    m_nominfile=!(tmin->Add(minFile)==1);
  }
  if(m_nominfile){
    minFile="root/"+jobname+Form("/opt_*%s=0_-2_2_*.root",poiName.Data());
    m_nominfile=!(tmin->Add(minFile)==1);
  }
  if(m_nominfile){
    minFile="root/"+jobname+Form("/opt_%s=1_0_2_*.root",poiName.Data());
    m_nominfile=!(tmin->Add(minFile)==1);
  }

  if(m_nominfile){
    minFile="root/"+jobname+Form("/opt_%s=-100_*.root",poiName.Data());
    m_nominfile=!(tmin->Add(minFile)==1);
  }
  if(m_nominfile){
    minFile="root/"+jobname+Form("/opt_%s=0.2_0_0.5*.root",poiName.Data());
    m_nominfile=!(tmin->Add(minFile)==1);
  }
  if(m_nominfile){
    minFile="root/"+jobname+Form("/opt_%s=0.002_-0.002_0.01*.root",poiName.Data());
    m_nominfile=!(tmin->Add(minFile)==1);
  }
  if(m_nominfile){
    minFile="root/"+jobname+Form("/opt_%s=0_-5_5*.root",poiName.Data());
    m_nominfile=!(tmin->Add(minFile)==1);
  }
  // still not found? give another try
  if(m_nominfile){
    minFile="root/"+jobname+Form("/opt_%s=125_120_130_*.root",poiName.Data());
    m_nominfile=!(tmin->Add(minFile)==1);
    // cout<<"Here! "<<m_nominfile<<endl; getchar();
  }
  if(m_nominfile){
    minFile="root/"+jobname+Form("/opt_%s=750_700_800_*.root",poiName.Data());
    m_nominfile=!(tmin->Add(minFile)==1);
    // cout<<"Here! "<<m_nominfile<<endl; getchar();
  }
  if(m_nominfile){
    minFile="root/"+jobname+Form("/opt_%s=750_740_760_*.root",poiName.Data());
    m_nominfile=!(tmin->Add(minFile)==1);
    // cout<<"Here! "<<m_nominfile<<endl; getchar();
  }

  // still not found? give another try
  if(m_nominfile){
    minFile="root/"+jobname+Form("/opt_%s=126_125_127_*.root",poiName.Data());
    m_nominfile=!(tmin->Add(minFile)==1);
    // cout<<"Here! "<<m_nominfile<<endl; getchar();
  }
  if(m_nominfile){
    minFile="root/"+jobname+Form("/opt_%s=0_-0.5_0.5*.root",poiName.Data());
    m_nominfile=!(tmin->Add(minFile)==1);
    // cout<<"Here! "<<m_nominfile<<endl; getchar();
  }

  if(m_nominfile){
    minFile="root/"+jobname+Form("/opt_%s=*_123_127_*.root",poiName.Data());
    m_nominfile=!(tmin->Add(minFile)==1);
  }
  if(m_nominfile){
    minFile="root/"+jobname+Form("/opt_%s=125_123_127_*.root",poiName.Data());
    m_nominfile=!(tmin->Add(minFile)==1);
  }
  if(m_nominfile){
    minFile="root/"+jobname+Form("/opt_%s=750_720_780_*.root",poiName.Data());
    m_nominfile=!(tmin->Add(minFile)==1);
  }
  if(m_nominfile){
    minFile="root/"+jobname+Form("/opt_*%s=-100_*.root",poiName.Data());
    m_nominfile=!(tmin->Add(minFile)==1);
  }
  if(m_nominfile){
    minFile="root/"+jobname+Form("/opt_*%s=1_*.root",poiName.Data());
    m_nominfile=!(tmin->Add(minFile)==1);
  }
  if(m_nominfile){
    minFile="root/"+jobname+Form("/opt_*%s=-100*.root",poiName.Data());
    m_nominfile=!(tmin->Add(minFile)==1);
  }
  cout<<minFile<<endl;
  return m_nominfile;
}
