#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"
#include "statistics.hh"
//#include "HggTwoSidedCBPdf.hh"
using namespace std;
using namespace RooFit;
using namespace RooStats;
using namespace CommonFunc;
/*This script comes from Hongtao. He used this for the 750 GeV analysis. I made quick and dirty changes to make it work for SM H coupling analysis.
-Haichen
search HW for comments I made about the specifics of this script working for the coupling analysis
*/

// JD adding all the strings for the truth bins
TString truthbins[52] = {"gg2H_0J", "gg2H_1J_ptH_0_60", "gg2H_1J_ptH_60_120", "gg2H_1J_ptH_120_200", "gg2H_ge2J_ptH_0_60",
			 "gg2H_ge2J_ptH_60_120", "gg2H_ge2J_ptH_120_200", "gg2H_VBFtopo_jet3veto", "gg2H_VBFtopo_jet3",
			 "VBF_qq2Hqq_VBFtopo_jet3veto", "VBF_qq2Hqq_VBFtopo_jet3", "VBF_qq2Hqq_VH2jet", "VBF_qq2Hqq_rest",
			 "gg2H_1J_ptH_gt200", "gg2H_ge2J_ptH_gt200", "VBF_qq2Hqq_pTjet1_gt200", "ggZH_gg2H_1J_ptH_gt200",
			 "ggZH_gg2H_ge2J_ptH_gt200", "WH_qq2Hqq_pTjet1_gt200", "ZH_qq2Hqq_pTjet1_gt200", 
			 "WH_qq2Hqq_VBFtopo_jet3veto", "WH_qq2Hqq_VBFtopo_jet3", "WH_qq2Hqq_VH2jet", "WH_qq2Hqq_rest",
			 "ZH_qq2Hqq_VBFtopo_jet3veto", "ZH_qq2Hqq_VBFtopo_jet3", "ZH_qq2Hqq_VH2jet", "ZH_qq2Hqq_rest",
			 "ggZH_gg2H_0J", "ggZH_gg2H_1J_ptH_0_60", "ggZH_gg2H_1J_ptH_60_120", "ggZH_gg2H_1J_ptH_120_200",
			 "ggZH_gg2H_ge2J_ptH_0_60", "ggZH_gg2H_ge2J_ptH_60_120", "ggZH_gg2H_ge2J_ptH_120_200",
			 "ggZH_gg2H_VBFtopo_jet3veto", "ggZH_gg2H_VBFtopo_jet3", "qq2Hlnu_pTV_0_150", 
			 "qq2Hlnu_pTV_150_250_0J", "qq2Hlnu_pTV_150_250_ge1J", "qq2Hlnu_pTV_gt250", "qq2Hll_pTV_0_150", 
			 "qq2Hll_pTV_150_250_0J", "qq2Hll_pTV_150_250_ge1J", "qq2Hll_pTV_gt250", "gg2Hll_pTV_0_150",
			 "gg2Hll_pTV_gct150_0J", "gg2Hll_pTV_gt150_ge1J", "ttH", "tHqb", "tHW", "bbH"};

// JD assigns a process to each truth bin
// 1 = ggF, 2 = VBF, 3 = VH, 4 = top
int procbins[52] = {1, 1, 1, 1, 1,
		    1, 1, 1, 1,
		    2, 2, 2, 2,
		    1, 1, 2, 3,
		    3, 3, 3,
		    3, 3, 3, 3,
		    3, 3, 3, 3,
		    3, 3, 3, 3,
		    3, 3, 3,
		    3, 3, 3,
		    3, 3, 3, 3,
		    3, 3, 3, 3,
		    3, 3, 4, 4, 4, 1};

//JD adds this after unblinding:
double best_fit_mu = 1.06;

double minimize(ModelConfig *mc, RooAbsData *data){
  unique_ptr<RooAbsReal> nll(mc->GetPdf()->createNLL(*data, Constrain(*mc->GetNuisanceParameters()), GlobalObservables(*mc->GetGlobalObservables())));
  nll->enableOffsetting(true);
  RooMinimizer minim(*nll);
  minim.setStrategy(0);
  minim.setPrintLevel(1);
  minim.setEps(1);
  // minim.optimizeConst(2);
  int status=minim.minimize("Minuit2");
  return nll->getVal();
}

TString categoryTranslator(TString channelname){
  if(channelname=="BB_13TeV") return "barrel-barrel";
  if(channelname=="nonBB_13TeV") return "non-barrel-barrel";
  if(channelname=="CC_13TeV") return "central-central";
  if(channelname=="nonCC_13TeV") return "non-central-central";
  return "";
}

// JD moves this code to a separate function
double integral(int i, RooWorkspace* w, RooRealVar* x, int mode){
  
  ModelConfig *mc=(ModelConfig*)w->obj("ModelConfig");
  RooDataSet* m_data = (RooDataSet*)w->data("combData");
  RooSimultaneous* m_pdf = (RooSimultaneous*)mc->GetPdf();

  RooAbsCategoryLValue*  m_cat = (RooAbsCategoryLValue*)&m_pdf->indexCat();
  int numChannels = m_cat->numBins(0);

  // HW this is where I calculate the yields in a +/- 2 GeV window.
  // HW if we switch to 90% window, then we need to determine it, 
  // probably from a signal filled histogram, and then hard code the interval here
  // HW we integral the pdfs first, then multiply the fraction with the normalization
 

  m_cat->setBin(i);
  
  // HW Get individual category name, pdf, observable, data set
  TString channelname=m_cat->getLabel();
  
  double sig_tot = 0;
  double sig_ggF = 0;
  double sig_VBF = 0;
  double sig_VH = 0;
  double sig_top = 0;
  
  //Replaced const 4 GeV range with dynamic range that contains 90% of signal events for each category
  double intg_range[numChannels]={2.84, 3.625, 3.355, 3.185, 2.85, 2.43, 3.43, 3.205, 2.855, 2.505, 3.24, 2.875, 3.22, 2.93, 3.005, 2.655, 2.53, 3.43, 2.725, 3.225, 2.66, 2.94, 2.945, 2.91, 2.79, 2.465, 3.245, 3.055, 2.765};
  
  double muCB = w->var("muCBNom_"+channelname)->getVal();
  x->setRange("range_ninety_pc",muCB-intg_range[i],muCB+intg_range[i]);

  for(int i_bin=0; i_bin<52; i_bin++){
    

    if( !w->function("yield__"+truthbins[i_bin]+"_"+channelname) )
      continue;
    
    sig_tot += w->function("yield__"+truthbins[i_bin]+"_"+channelname)->getVal();
    if( procbins[i_bin] == 1 ) 
      sig_ggF += w->function("yield__"+truthbins[i_bin]+"_"+channelname)->getVal();
    if( procbins[i_bin] == 2 )
      sig_VBF += w->function("yield__"+truthbins[i_bin]+"_"+channelname)->getVal();
    if( procbins[i_bin] == 3 )
      sig_VH += w->function("yield__"+truthbins[i_bin]+"_"+channelname)->getVal();
    if( procbins[i_bin] == 4 )
      sig_top += w->function("yield__"+truthbins[i_bin]+"_"+channelname)->getVal();
  }
  
  RooAbsReal* integral_bkg =  dynamic_cast<RooAbsReal*>(w->pdf("pdf__background_"+channelname)->createIntegral(RooArgSet(*x), NormSet(*x), Range("range_ninety_pc"))) ;
  RooAbsReal* integral_sig =  dynamic_cast<RooAbsReal*>(w->pdf("pdf__commonSig_"+channelname)->createIntegral(RooArgSet(*x), NormSet(*x), Range("range_ninety_pc"))) ;
    
  // HW there are yields for continuum backgrounds, resonant background, 
  // which is defined differently depending on which signal is of interest, 
  // and ttH signal (which can be replaced by all signals, or ggH-only , VBF -only , etc.)
  double NB = (integral_bkg->getVal()*w->function("yield__background_"+channelname)->getVal());
  w->var("mu")->setVal(1);
  double NS = integral_sig->getVal();
  
  double s, b;
  //b = NB;
  
  if( mode == 1 )
    s = NS*(sig_ggF);
  else if( mode == 2 )
    s = NS*(sig_VBF);
  else if( mode == 3 )
    s = NS*(sig_VH);
  else if( mode == 4 )
    s = NS*(sig_top);
  else
    s = NS*(sig_tot);

  b = NB + (NS*sig_tot - s);

  fstream table_out;
  string proc;
  if (mode == 1) proc = "ggF";
  else if (mode == 2) proc = "VBF";
  else if (mode == 3) proc = "VH";
  else if (mode == 4) proc = "top";
  else  proc = "incl";

  table_out.open("table_out_"+proc+".txt", ios::out | ios::app);
  table_out<<channelname<<"   "<<s<<"   "<<b<<"   "<<log(1.0+1.0*s/b)<<endl;
  table_out.close();
  return log(1.0+1.0*s/b);
}

// JD moves this to be a separate function to be called on each production mode
void draw_weighted(TGraphAsymmErrors* hwt, RooWorkspace* w, RooRealVar* x, double* weights, double* integral_array,double* integral_array_proc, TString filename, TString proc){

  ModelConfig *mc=(ModelConfig*)w->obj("ModelConfig");
  RooDataSet* m_data = (RooDataSet*)w->data("combData");
  RooSimultaneous* m_pdf = (RooSimultaneous*)mc->GetPdf();

  RooAbsCategoryLValue*  m_cat = (RooAbsCategoryLValue*)&m_pdf->indexCat();
  int numChannels = m_cat->numBins(0);

  TList* m_dataList = m_data->split( *m_cat, true );

  RooArgSet* conbkgpdfs = new RooArgSet();
  RooArgSet* resbkgpdfs = new RooArgSet();
  RooArgSet* allSBpdfs = new RooArgSet();

  RooArgSet* conbkgNorm_weighted = new RooArgSet();
  RooArgSet* resbkgNorm_weighted = new RooArgSet();
  RooArgSet* allSBNorm_weighted = new RooArgSet();

  RooRealVar* ncon_weighted[numChannels];
  RooRealVar* nres_weighted[numChannels];
  RooRealVar* nsb_weighted[numChannels];

  //GO these hists are for the residual plot
  double binwidth = 1.0, xmax=160;
  double mass_val = x->getMin();
  double nres_weighted2[numChannels] = {};
  TGraphAsymmErrors* hwt_resid = new TGraphAsymmErrors(hwt->GetN()); 
  
  //Output file for table of signal, background, and weights
  
  double ConNorm_weighted = 0;
  double ResNorm_weighted = 0;
  double SBNorm_weighted = 0;
  
  double resonant = 0;
  
  
  // HW the loop below will calculate the normalization ( = unweighted normalization * category weight)
  // after the loop, the RooArSet for the pdfs should have 31 pdfs from the analysis,
  // and the RooArgSet for the normalziation should have 31 entries
  for( int i= 0; i < numChannels; i++ ) {
    //for ( int i= 28; i <numChannels ; i++ ) {

    m_cat->setBin(i);
    TString channelname=m_cat->getLabel();
   

    double allsig = 0;
    double ggFsig = 0;
    double VBFsig = 0;
    double VHsig = 0;
    double topsig = 0;

    double best_fit_mu_tmp_patch = 1.0 ;
    for(int i_bin=0; i_bin<52; i_bin++){
      

      if( !w->function("yield__"+truthbins[i_bin]+"_"+channelname) )
	continue;

      allsig += best_fit_mu_tmp_patch*w->function("yield__"+truthbins[i_bin]+"_"+channelname)->getVal();

      if( proc == "ggF" && procbins[i_bin] == 1 ){
	ggFsig += best_fit_mu_tmp_patch*w->function("yield__"+truthbins[i_bin]+"_"+channelname)->getVal();
      }
      else if( proc == "VBF" && procbins[i_bin] == 2 ){
	VBFsig += best_fit_mu_tmp_patch*w->function("yield__"+truthbins[i_bin]+"_"+channelname)->getVal();
      }
      else if( proc == "VH" && procbins[i_bin] == 3 ){
	VHsig += best_fit_mu_tmp_patch*w->function("yield__"+truthbins[i_bin]+"_"+channelname)->getVal();
      }
      else if( proc == "top" && procbins[i_bin] == 4 ){
	topsig += best_fit_mu_tmp_patch*w->function("yield__"+truthbins[i_bin]+"_"+channelname)->getVal();
      }

    }

    double non_ggFsig = allsig - ggFsig;
    double non_VBFsig = allsig - VBFsig;
    double non_VHsig = allsig - VHsig;
    double non_topsig = allsig - topsig;

    allSBpdfs->add( *w->pdf("_modelSB_"+channelname) );
    // HW NEED TO COME BACK TO THIS
    RooRealVar yield_resbkg("yield_resbkg","yield_resbkg",1);

    //conbkgpdfs->add( *w->pdf("pdf__background_"+channelname) );

    double sbnorm_weighted = ( allsig + w->function("yield__background_"+channelname)->getVal() ) * weights[i];
    double connorm_weighted = ( w->function("yield__background_"+channelname)->getVal() ) * weights[i];
    double resnorm_weighted = 0;
    // HW resonant background should be normalized to total continuum backgorund plus all Higgs signal subtracting the process of interest here
    if( proc == "ggF" ){
      resonant += non_ggFsig/allsig;
      resnorm_weighted = ( non_ggFsig + w->function("yield__background_"+channelname)->getVal() ) * weights[i]; 
      yield_resbkg.setVal(non_ggFsig);
    }
    else if( proc == "VBF" ){
      resonant += non_VBFsig/allsig;
      resnorm_weighted = ( non_VBFsig + w->function("yield__background_"+channelname)->getVal() ) * weights[i];
      yield_resbkg.setVal(non_VBFsig);
    }
    else if( proc == "VH" ){
      resonant += non_VHsig/allsig;
      resnorm_weighted = ( non_VHsig + w->function("yield__background_"+channelname)->getVal() ) * weights[i];
      yield_resbkg.setVal(non_VHsig);
      cout<<"Res_BKG_yield VH: "<<non_VHsig/allsig<<endl;
    }
    else if( proc == "top" ){
      resonant += non_topsig/allsig;
      resnorm_weighted = ( non_topsig + w->function("yield__background_"+channelname)->getVal() ) * weights[i];
      yield_resbkg.setVal(non_topsig);
    }

    RooRealVar* resbkgPDF_bkgnorm = new RooRealVar("resbkgPDF_bkgnorm","resbkgPDF_bkgnorm", w->function("yield__background_"+channelname)->getVal());
    RooAddPdf* resbkgPDF = new RooAddPdf("resbkgPDF"+channelname+"_"+proc,"resbkgPDF"+channelname+"_"+proc, RooArgSet( *w->pdf("pdf__commonSig_"+channelname) , *w->pdf("pdf__background_"+channelname)) ,RooArgSet( yield_resbkg,*resbkgPDF_bkgnorm) );
    w->import(*resbkgPDF);
    resbkgpdfs->add( *w->pdf("resbkgPDF"+channelname+"_"+proc) );

// GO Construction of non resonant background, including spurious signal, pdfs
  //================
    RooRealVar* conbkgPDF_bkgnorm = new RooRealVar("conbkgPDF_bkgnorm","conbkgPDF_bkgnorm", w->function("yield__background_"+channelname)->getVal());
    //GO product of NP (in terms of std) and nominal number of spurious events
    RooRealVar* conbkgPDF_spuriousnorm = new RooRealVar("conbkgPDF_spuriousnorm","conbkgPDF_spuriousnorm", w->var("ATLAS_Hgg_BIAS_"+channelname)->getVal()*w->var("uncertSymm__yield_ATLAS_Hgg_BIAS_"+channelname+"_spurious_"+channelname)->getVal());
    RooAddPdf* conbkgPDF = new RooAddPdf("conbkgPDF"+channelname+"_"+proc,"conbkgPDF"+channelname+"_"+proc, RooArgSet( *w->pdf("pdf__commonSig_"+channelname) , *w->pdf("pdf__background_"+channelname)) ,RooArgSet(*conbkgPDF_spuriousnorm,*conbkgPDF_bkgnorm) );
    w->import(*conbkgPDF);
    conbkgpdfs->add( *w->pdf("conbkgPDF"+channelname+"_"+proc) );
    //===========================

    nsb_weighted[i] = new RooRealVar("nsb_"+channelname+"_"+proc ,"nsb_"+channelname+"_"+proc ,sbnorm_weighted);
    // HW NEED TO COME BACK TO THIS
    nres_weighted[i] = new RooRealVar("nres_"+channelname+"_"+proc, "nres_"+channelname+"_"+proc, resnorm_weighted);
    ncon_weighted[i] = new RooRealVar("nbkg_"+channelname+"_"+proc, "nbkg_"+channelname+"_"+proc, connorm_weighted);
    

    allSBNorm_weighted->add( *nsb_weighted[i] );

    resbkgNorm_weighted->add( *nres_weighted[i] ); // HW 
    conbkgNorm_weighted->add( *ncon_weighted[i] );

    ConNorm_weighted += connorm_weighted;
    ResNorm_weighted += resnorm_weighted;
    SBNorm_weighted += sbnorm_weighted;

    delete conbkgPDF;
    delete resbkgPDF;
    delete resbkgPDF_bkgnorm;
    delete conbkgPDF_spuriousnorm;
    delete conbkgPDF_bkgnorm;

  }


  // HW Construct the extended pdfs, which is a weighted sum of 31 categories
  // JD add individual production modes
  RooAddPdf *weightedConPdf = new RooAddPdf("weightedConPdf","weightedConPdf", *conbkgpdfs, *conbkgNorm_weighted);
  RooAddPdf *weightedResPdf = new RooAddPdf("weightedResPdf","weightedResPdf", *resbkgpdfs, *resbkgNorm_weighted); // HW PDF for resonant background
  RooAddPdf *weightedSBPdf = new RooAddPdf("weightedSBPdf","weightedSBPdf", *allSBpdfs, *allSBNorm_weighted);




  mass_val = 105;
  int Nbins = hwt->GetN();
  double error, weight = 0;
  int value;  
  double xpt, ypt;
  double x_hi,x_lo,y_hi,y_lo;
  //GO second loop over bins, designed to subtract B from S for residual plots
  for ( int i= 0; i <Nbins; i++ ) {
    //GO here the residual hist is filled
    //x->setRange("range",mass_val,mass_val+binwidth);
    weight = 0;
    for(int ii= 0; ii<numChannels ; ii++)
      //for(int ii=28; ii<numChannels ; ii++)
      {
	//if(proc == "ggF" || proc == "VBF" || proc == "top" || proc == "VH")
	  //if(proc == "top")
	// {
	// weight += (integral_array[ii*Nbins+i]+integral_array_proc[ii*Nbins+i]*nres_weighted2[i])*weights[ii];
	// // weight += integral_array[ii*Nbins+i]*weights[ii];
	// value = hwt->GetBinContent(i+1);
	// error = hwt->GetBinError(i+1);
	// cout<<endl<<endl<<"weight: "<<weight<<endl<<endl;
	//}
	//else
	//{
	weight += integral_array[ii*Nbins+i]*weights[ii];
	
	//error = hwt->GetBinError(i+1);
	//	cout<<endl<<endl<<"weight: "<<weight<<endl<<endl;
	//}
      }
    value = hwt->GetPoint(i,xpt,ypt);
    x_hi = hwt->GetErrorXhigh(i);
    x_lo = hwt->GetErrorXlow(i);
    y_hi = hwt->GetErrorYhigh(i);
    y_lo = hwt->GetErrorYlow(i);
    cout<<"value of pt: "<<ypt<<endl;
    cout<<"value of bkg sum: "<<weight<<endl;
    if(value != -1){
      hwt_resid->SetPoint(i,xpt,ypt-weight);
      hwt_resid->SetPointError(i,x_lo,x_hi,y_lo,y_hi);
    }
    else
      cout<<"error not going to fill graph."<<endl;
      //mass_val+=binwidth;
    
    value = hwt_resid->GetPoint(i,xpt,ypt);
    cout<<"Value of residual point "<<ypt<<endl;
  }


  // HW - now draw data and pdf to the RooPlot
  // We always have to draw the RooDataSet first and then the RooAbs PDFs in order to have the pdfs noramlized correctly.


  TCanvas* c00 = new TCanvas();
  c00->cd();
  
  TPad *pad1 =  new TPad("pad1","pad1name",0.01,0.40,0.99,0.99);
  TPad *pad2 =  new TPad("pad2","pad2name",0.01,0.05,0.99,0.402);
  pad1->Draw();
  pad2->Draw();
  pad1->SetBottomMargin(0.);
  pad1->cd();
  
  
  // RooRealVar *x = new RooRealVar("x","x",105,160);
  //hwt->Sumw2();
  
  //int hwtbin = hwt->GetHistogram()->GetMaximumBin();
  double hwtmax = 1.6*( hwt->GetHistogram()->GetMaximum());// + hwt->GetHistogram()->GetBinError(hwtbin));
  cout<<"test 123:  "<<hwtmax<<endl;
  hwt->GetYaxis()->SetRangeUser(0.0001, hwtmax);
  hwt->GetXaxis()->SetRangeUser(105,160);
  cout<<"test 234"<<endl; 
  hwt->SetMaximum(hwtmax);
  
  hwt->GetYaxis()->SetTitle("Sum of Weights / 1.0 GeV");
  if( weights[0] == 1 )
    hwt->GetYaxis()->SetTitle("Events");
  // HW this is data, all histogram objects are data
  hwt->SetTitle("");
  //  TH1F* hdum = new TH1F("hdum","hdum",10,0,1);
  //  hdum -> GetXaxis()->SetRangeUser(105,160);
  //  hdum -> GetXaxis()->SetRangeUser(0.0001,hwtmax);
  //hdum ->Draw("axis");
  hwt->Draw("ap");

  RooPlot* frame = x->frame();
  frame->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");

  // HW Normalization () option should have the total yield (weighted or not) so that the PDF can be normalized correctly.
  // This is neccessary but not sufficient.
 

  cout<<"test 456"<<endl; 

  w->var("mu")->setVal(1);

  if( proc == "ggF" ){
    weightedResPdf->plotOn(frame,LineColor(kGreen),LineStyle(7),Normalization(ResNorm_weighted));
  }
  else if( proc == "VBF" ){
    weightedResPdf->plotOn(frame,LineColor(kGreen),LineStyle(7),Normalization(ResNorm_weighted));
  }
  else if( proc == "VH" ){
    weightedResPdf->plotOn(frame,LineColor(kGreen),LineStyle(7),Normalization(ResNorm_weighted));
  }
  else if( proc == "top" ){
    weightedResPdf->plotOn(frame,LineColor(kGreen),LineStyle(7),Normalization(ResNorm_weighted));
  }

  // HW this is the continuum background pdf
  weightedConPdf->plotOn(frame,LineColor(kBlue),LineStyle(kDashed),Normalization(ConNorm_weighted));
 w->var("mu")->setVal(best_fit_mu);
  weightedSBPdf->plotOn(frame,LineColor(kRed),Normalization(SBNorm_weighted));
  RooCurve* sig_curve = (RooCurve*)frame->getCurve("weightedSBPdf_Norm[atlas_invMass]");
  frame->Draw("same");
  RooCurve* bkg_curve = (RooCurve*)frame->getCurve("weightedConPdf_Norm[atlas_invMass]");
 

 
  frame->Print("v");
  hwt->SetTitle("");
  hwt->SetLineWidth(2);
  hwt->SetLineColor(1);
  hwt->Draw("psame");
w->var("mu")->setVal(1);
  
  RooCurve *SBminusB_curve = new RooCurve("SBminusB_curve","SBminusB_curve",*sig_curve,*bkg_curve,1,-1);
  
  

  TH1F* hdummyS = new TH1F("hdummyS","hdummyS",10,0,1);
  TH1F* h1 = new TH1F("h1","h1",10,0,1);
  TH1F* hdummyB = new TH1F("hdummyB","hdummyB",10,0,1);
  TH1F* hdummyRes = new TH1F("hdummyRes","hdummyRes",10,0,1);
  TH1F* hdummymuhat = new TH1F("hdummymuhat","hdummymuhat",10,0,1);
  hdummyS->SetLineColor(kRed);
  hdummyS->SetLineWidth(2);
  hdummyB->SetLineColor(kBlue);
  hdummyB->SetLineWidth(2);
  hdummyB->SetLineStyle(2);
  hdummyRes->SetLineColor(kGreen);
  hdummyRes->SetLineStyle(7);
  hdummymuhat->SetLineColor(7);
  hdummymuhat->SetLineWidth(2);

  TLegend* lg = new TLegend(0.18,0.68,0.58,0.93);
  lg->SetLineColor(0);
  lg->SetFillColor(0);
  lg->SetShadowColor(0);
  lg->SetTextSize(0.05);
  lg->AddEntry(h1,"Data","EP");
  lg->AddEntry(hdummyS,"Signal+Background","L");
  if( proc == "ggF" || proc == "VBF" || proc == "VH" || proc == "top" )
    lg->AddEntry(hdummyRes,"Total background","L");
  lg->AddEntry(hdummyB,"Continuum background","L");
  lg->Draw();

  TLatex* tex = new TLatex(0.55,0.88,"ATLAS");
  tex->SetNDC();
  tex->SetTextFont(72);
  tex->SetTextSize(0.05);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(0.65,0.88,"Internal");
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetLineWidth(2);
  tex->SetTextSize(0.05);
  tex->Draw();

  char lumitext[50];
  sprintf(lumitext, "#sqrt{s} = 13 TeV, %4.1f fb^{-1}",79.8);
  tex = new TLatex(0.58,0.82,lumitext);
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetLineWidth(2);
  tex->SetTextSize(0.05);
  tex->Draw();
  /*
    TString tag = proc;
    tex = new TLatex(0.58,0.76,tag);
    tex->SetNDC();
    tex->SetTextFont(42);
    tex->SetLineWidth(2);
    tex->SetTextSize(0.05);
    tex->Draw();
  */
  tex = new TLatex(0.58,0.76,"m_{H} = 125.09 GeV");
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetLineWidth(2);
  tex->SetTextSize(0.05);
  tex->Draw();
  
  if(proc =="ggF" || proc =="VBF" || proc == "VH"){
    tex = new TLatex(0.58,0.70,"ln(1+S/B) Weighted Sum, S = "+proc);}
  else if(proc =="top")
    tex = new TLatex(0.58,0.70,"ln(1+S/B) Weighted Sum, S = H + "+proc);
 else
   tex = new TLatex(0.58,0.70,"Unweighted Sum, S = "+proc);
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetLineWidth(2);
  tex->SetTextSize(0.05);
  tex->Draw();

  pad2->SetTopMargin(0.);
  pad2->cd();
  hwt_resid->GetYaxis()->SetRangeUser(hwt_resid->GetHistogram()->GetMinimum()*1.5, hwt_resid->GetHistogram()->GetMaximum()*1.5);
  hwt_resid->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
  hwt_resid->GetYaxis()->SetTitle("Data - Cont. Bkg");
  hwt_resid->GetYaxis()->SetTitleSize(0.075);
  hwt_resid->GetYaxis()->SetTitleOffset(0.80);
  hwt_resid->GetYaxis()->SetLabelSize(0.075);
  hwt_resid->GetYaxis()->SetNdivisions(5);
  hwt_resid->GetXaxis()->SetRangeUser(105,160);
  hwt_resid->GetXaxis()->SetTitleSize(0.075);
  hwt_resid->GetXaxis()->SetTitleOffset(0.9);
  hwt_resid->GetXaxis()->SetLabelSize(0.075);
  hwt_resid->SetLineWidth(2);
  hwt_resid->SetLineColor(1);

  RooPlot* frameS = x->frame();//(Binning(Nbins));
  double Norm_for_plot;

  // Norm_for_plot = SBNorm_weighted-ConNorm_weighted;  
  
  //weightedSBminusBPdf->plotOn(frameS,LineColor(kRed),LineStyle(1),Normalization(Norm_for_plot));
  hwt_resid->SetTitle("");
  hwt_resid->Draw("ap");
  SBminusB_curve->SetLineColor(kRed);
  
  TLine* l = new TLine(x->getMin(),0,xmax,0);
  l->SetLineColor(kBlue);
  l->SetLineWidth(2);
  l->SetLineStyle(kDashed);
  l->Draw("same");
  SBminusB_curve->Draw("lsame");
  frameS->Draw("same");
  hwt_resid->Draw("psame");
  pad2->RedrawAxis();
  pad2->Update();

  PrintCanvas(c00,"fig/invmass/"+filename);

  TFile* Objects_Out =  TFile::Open("fig/invmass/"+filename+"Objects_Out.root","RECREATE");
  RooRealVar *resnormout = new RooRealVar("resnormout","resnormout",ResNorm_weighted);
  RooRealVar *connormout = new RooRealVar("connormout","connormout",ConNorm_weighted);
  RooRealVar *SBnormout = new RooRealVar("SBnormout","SBnormout",SBNorm_weighted);
  hwt_resid->Write("hwt_resid");
  weightedResPdf->Write("weightedResPdf");
  weightedSBPdf->Write("weightedSBPdf");
  weightedConPdf->Write("weightedConPdf");
  frame->Write("frame_up");
  frameS->Write("frame_low");
  Objects_Out->Write();
  Objects_Out->Close();

  //Histograms
  delete hdummyS;
  delete h1;
  delete hdummyB;
  delete hdummyRes; 
  delete hdummymuhat;
  delete hwt_resid;
  delete resnormout;
  delete connormout;
  delete SBnormout;
  //TObjects for drawing
  delete tex;
  delete l;
  return;
}

int main( int argc, char** argv ){
  if( argc<2 ){
    cout<<"Usage: "<<argv[0]<<" input_file"<<endl;
    exit(0);
  }
  
  //HW These are input arguments. The job is configured via a TString type option

  TString jobname=argv[1];
  TString proc=argv[2];
  TString inputWSFileName=argv[3];
  TString inputdatahists = argv[4];
  TString inputweighthists = argv[5];
  TString inputintegralhist = argv[6];
  TString option=argv[7];
  
  SetAtlasStyle();

  TFile* fin = TFile::Open(inputWSFileName);
  RooWorkspace* w = dynamic_cast<RooWorkspace*>(fin->Get("combWS"));
  ModelConfig *mc=(ModelConfig*)w->obj("ModelConfig");
  RooDataSet* m_data = (RooDataSet*)w->data("combData");
  RooSimultaneous* m_pdf = (RooSimultaneous*)mc->GetPdf();

  RooAbsCategoryLValue*  m_cat = (RooAbsCategoryLValue*)&m_pdf->indexCat();
  int numChannels = m_cat->numBins(0);
  
  TList* m_dataList = m_data->split( *m_cat, true );
  bool isBonly=false, doFit=false;

  //GO histogram dimensions, moved so could be used to setup output hists
  double binwidth = 1.0, xmax=160 , xmin = 105;
  const  int nbins = (xmax-xmin)/binwidth;
  //GO text files of weights
  /*
  TH1F *h_outweights = new TH1F("h_outweights","h_outweights",numChannels,0,numChannels);
  TH1F *h_outweights_ggF = new TH1F("h_outweights_ggF","h_outweights_ggF",numChannels,0,numChannels);
  TH1F *h_outweights_VBF = new TH1F("h_outweights_VBF","h_outweights_VBF",numChannels,0,numChannels);
  TH1F *h_outweights_VH = new TH1F("h_outweights_VH","h_outweights_VH",numChannels,0,numChannels);
  TH1F *h_outweights_top = new TH1F("h_outweights_top","h_outweights_top",numChannels,0,numChannels);*/
  //GO text file of 1 GeV integrals of the signal pdfs
  //TH1F *h_outintegral = new TH1F("h_outintegral","h_outintegral",numChannels*nbins,0,numChannels*nbins);
  //TH1F *h_outintegralA = new TH1F("h_outintegralA","h_outintegralA",numChannels*nbins,0,numChannels*nbins);
  
  //GO root file containing histograms
  //TFile *histoutfile = TFile::Open("hist_output_intg.root","RECREATE");
  
  TFile *datahistfile = TFile::Open(inputdatahists);
  TGraphAsymmErrors* h_in_hwt =(TGraphAsymmErrors*)datahistfile->Get("g") ; 
  TGraphAsymmErrors* h_in_hwt_ggF = (TGraphAsymmErrors*)datahistfile->Get("g_ggF");
  TGraphAsymmErrors* h_in_hwt_VBF = (TGraphAsymmErrors*)datahistfile->Get("g_VBF");
  TGraphAsymmErrors* h_in_hwt_VH =(TGraphAsymmErrors*)datahistfile->Get("g_VH") ; 
  TGraphAsymmErrors* h_in_hwt_top =(TGraphAsymmErrors*)datahistfile->Get("g_top");
  //TGraphAsymmErrors* h_in_hunwt = (TGraphAsymmErrors*)datahistfile->Get("h0_unwt"); 
  
  TGraphAsymmErrors* hwt = (TGraphAsymmErrors*)h_in_hwt->Clone();
  TGraphAsymmErrors* hwt_ggF = (TGraphAsymmErrors*)h_in_hwt_ggF->Clone();
  TGraphAsymmErrors* hwt_VBF = (TGraphAsymmErrors*)h_in_hwt_VBF->Clone();
  TGraphAsymmErrors* hwt_VH = (TGraphAsymmErrors*)h_in_hwt_VH->Clone();
  TGraphAsymmErrors* hwt_top = (TGraphAsymmErrors*)h_in_hwt_top->Clone();
  // TGraphAsymmErrors* hunwt = (TGraphAsymmErrors*)h_in_hunwt->Clone();
  //GO bringing in weights and filling weight arrays
  TFile *weights_histfile = new TFile(inputweighthists);
  TH1F *h_inweights =(TH1F*)weights_histfile->Get("h_outweights");
  TH1F *h_inweights_ggF =(TH1F*)weights_histfile->Get("h_outweights_ggF");
  TH1F *h_inweights_VBF =(TH1F*)weights_histfile->Get("h_outweights_VBF");
  TH1F *h_inweights_VH =(TH1F*)weights_histfile->Get("h_outweights_VH");
  TH1F *h_inweights_top =(TH1F*)weights_histfile->Get("h_outweights_top");
  
  
  double wtsb[numChannels]={};
  double wtsb_ggF[numChannels]={};
  double wtsb_VBF[numChannels]={};
  double wtsb_VH[numChannels]={};
  double wtsb_top[numChannels]={}; 
  double integral_array[numChannels*nbins]={};
  double integral_array_proc[numChannels*nbins] = {};
  for (int ii = 0; ii<numChannels; ii++)
    {
      wtsb[ii] = h_inweights->GetBinContent(ii);
      wtsb_ggF[ii] = h_inweights_ggF->GetBinContent(ii);
      wtsb_VBF[ii] = h_inweights_VBF->GetBinContent(ii);
      wtsb_VH[ii] = h_inweights_VH->GetBinContent(ii);
      wtsb_top[ii] = h_inweights_top->GetBinContent(ii);
      if(wtsb[ii]==0){
	cout<<endl<<endl<<"error"<<endl;
	break;}     
    }
  TFile *integral_histfile = new TFile(inputintegralhist);
  TH1F *h_inintegral = (TH1F*)integral_histfile->Get("h_outintegral");
  for (int ii = 0; ii<numChannels; ii++)
    { for(int i = 0; i<nbins; i++) integral_array[nbins*ii+i] =h_inintegral->GetBinContent(nbins*ii+i);}
  
  fin->cd();
  
  // HW load the snapshot of the NP values from muhat fit
  // we want to use the muhat fit NP values here as we have a real signal in the data set
  isBonly = false;
  if(doFit) minimize(mc,m_data);
  
  // HW arrays I used to count the signal, background, resonant signal yields
  // JD extends these arrays to 29 categories for full couplings
  double sh[numChannels], b[numChannels];
  double sh_ggf[numChannels], sh_vbf[numChannels], sh_vh[numChannels], sh_top[numChannels];

 
  
  // HW these are histograms where the unweighted and weighted data are saved 
  /*
  TH1F* hwt = new TH1F("hwt","hwt",nbins,105,xmax); hwt->Sumw2();
  TH1F* hwt_ggF = new TH1F("hwt_ggF","hwt_ggF",nbins,105,xmax); hwt_ggF->Sumw2();
  TH1F* hwt_VBF = new TH1F("hwt_VBF","hwt_VBF",nbins,105,xmax); hwt_VBF->Sumw2();
  TH1F* hwt_VH = new TH1F("hwt_VH","hwt_VH",nbins,105,xmax); hwt_VH->Sumw2();
  TH1F* hwt_top = new TH1F("hwt_top","hwt_top",nbins,105,xmax); hwt_top->Sumw2();
  TH1F* hunwt = new TH1F("hunwt","hunwt",nbins,105,xmax); hunwt->Sumw2();
  */
  
  
  //GO integral array, bin by by, for use in draw_weighted()
  // double integral_array[numChannels*nbins] = {};
  

  // HW load the snapshot of the NP values from muhat fit
  // we want to use the muhat fit NP values here as we have a real signal in the data set
  w->loadSnapshot("ucmles_mu");
  
  // HW the loop below is to deconstruct the RooSimultaneous to pdfs in individual categories
  // it loops over all categories
  // the individual category mass fit plot will be done here in this loop
  // the loop also counts event yields to calculate category weigh
  
  //file for tables of s90 b90 and weight90
  fstream table_out1;
  table_out1.open("table_out_ggF.txt",ios::out | ios::trunc);
  table_out1<<"Category   S90    B90    Weight90"<<endl;
  table_out1.close();

fstream table_out2;
  table_out2.open("table_out_VBF.txt",ios::out | ios::trunc);
  table_out2<<"Category   S90    B90    Weight90"<<endl;
  table_out2.close();

fstream table_out3;
  table_out3.open("table_out_VH.txt",ios::out | ios::trunc);
  table_out3<<"Category   S90    B90    Weight90"<<endl;
  table_out3.close();

fstream table_out4;
  table_out4.open("table_out_top.txt",ios::out | ios::trunc);
  table_out4<<"Category   S90    B90    Weight90"<<endl;
  table_out4.close();

  fstream table_out5;
  table_out5.open("table_out_incl.txt",ios::out | ios::trunc);
  table_out5<<"Category   S90    B90    Weight90"<<endl;
  table_out5.close();
  
  //for ( int i= 28; i < numChannels; i++ ) {
  for ( int i= 0; i < numChannels; i++ ) {
    m_cat->setBin(i);
    
    // HW Get individual category name, pdf, observable, data set
    TString channelname=m_cat->getLabel();
    RooAbsPdf* pdfi = m_pdf->getPdf(m_cat->getLabel());
    
    RooDataSet* datai = ( RooDataSet* )( m_dataList->At( i ) );
    RooRealVar *x= (RooRealVar*)pdfi->getObservables(datai)->first();
    
    const int Nbins = ( xmax-x->getMin() )/ binwidth;
    
    // HW now start to plot PDF and data set on the RooPlot
    // HW dummy histogram for setting up the axes 
    TH1D *hframe=new TH1D("hframe","hframe", Nbins*10, x->getMin(), xmax);
    hframe->GetYaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
    hframe->GetYaxis()->SetTitle(Form("Events / %.1f GeV",binwidth));
    x->setMax(xmax);
    x->setBins(Nbins);
    //    RooPlot* frame = x->frame(Binning(Nbins));
    RooPlot* frame = x->frame();
    RooPlot* frameChi2 = x->frame();
    frame->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
    frame->GetYaxis()->SetTitle(Form("Events / %.1f GeV",binwidth));
    
    //  //  JD implements new function to calculate weights
      //  // GO temp disabled to improve runtime
    
    wtsb[i] = integral(i,w,x,0);
    //h_outweights->SetBinContent(i,wtsb[i]);
    wtsb_ggF[i] = integral(i,w,x,1);
    //h_outweights_ggF->SetBinContent(i,wtsb_ggF[i]);
    wtsb_VBF[i] = integral(i,w,x,2);
    //h_outweights_VBF->SetBinContent(i,wtsb_VBF[i]);
    wtsb_VH[i] = integral(i,w,x,3);
    //h_outweights_VH->SetBinContent(i,wtsb_VH[i]);
    wtsb_top[i] = integral(i,w,x,4);
    //h_outweights_top->SetBinContent(i,wtsb_top[i]);
    
     //Dont Uncomment HERE
  
    // HW Set up the mu or mu_production_mode for the PDF (for the signal normalization function in the extended pdf )
   w->var("mu")->setVal(1);
    double allsig = 0;
    for(int i_bin=0; i_bin<52; i_bin++){
    

      if( !w->function("yield__"+truthbins[i_bin]+"_"+channelname) )
        continue;
      allsig += w->function("yield__"+truthbins[i_bin]+"_"+channelname)->getVal();
    }

    // HW plot the S+B pdf with mu = best fit value
    w->var("mu")->setVal(best_fit_mu);
    w->pdf("_modelSB_"+channelname)->plotOn(frame,LineColor(kRed),Normalization((best_fit_mu*allsig+w->function("yield__background_"+channelname)->getVal())));
    w->pdf("pdf__background_"+channelname)->plotOn(frame,LineStyle(kDashed),LineColor(kBlue),Normalization(w->function("yield__background_"+channelname)->getVal()));
    datai->plotOn(frame, Binning(Nbins), DataError(RooAbsData::Poisson));

    w->pdf("_modelSB_"+channelname)->plotOn(frameChi2,LineColor(kRed),Normalization((best_fit_mu*allsig+w->function("yield__background_"+channelname)->getVal())));
    datai->plotOn(frameChi2, Binning(Nbins), DataError(RooAbsData::Poisson));

    double chi2 = frameChi2->chiSquare();
    char c_chi2[50];
    sprintf(c_chi2, "#chi^{2} = %4.2f",chi2);

    // HW loop over the unbinned RooDataSet and fill the histograms
    TH1F* h1 = new TH1F("h1","h1",Nbins,x->getMin(),xmax); h1->Sumw2();
    TH1F* hdata = new TH1F("hdata","hdata",Nbins,x->getMin(),xmax); hdata->Sumw2();
    datai->fillHistogram(hdata,RooArgList(*x));
    // HW I think I have to do this step because otherwise there is only one weighted entry per bin in the TH1, and therefore the error sqrt(1)*weight
    //for( int k = 0 ; k < Nbins; k ++ ) hdata->SetBinError(k+1,sqrt(hdata->GetBinContent(k+1)));
    double mass_val = x->getMin();
  
    RooArgSet* obs = (RooArgSet*)datai->get();
    RooRealVar* xdata = (RooRealVar*)obs->find("atlas_invMass_"+channelname);
    
    // HW loop the RooDataSet and fill the weighted histogram and the unweighted histogram
    // the weights are calculated beforehands, in the last iteration, and then hard coded to the arrays declared earlier
    /*
    cout << "total number of events in datai " << datai->numEntries() << endl;
    for (int l=0 ; l<datai->numEntries() ; l++) {
      datai->get(l);

      if(  datai->weight() > 0.5){
	hwt->Fill( xdata->getVal() , wtsb[i] );
	hwt_ggF->Fill( xdata->getVal() , wtsb_ggF[i] );
	hwt_VBF->Fill( xdata->getVal() , wtsb_VBF[i] );
	hwt_VH->Fill( xdata->getVal() , wtsb_VH[i] );
	hwt_top->Fill( xdata->getVal() , wtsb_top[i] );
	hunwt->Fill( xdata->getVal() );
      }
    }
  */ //Dont Uncomment here
  
    double sumS = 0;
    double totalD = datai->sumEntries();
  
    for( int ii = 0 ; ii < Nbins; ii ++ ){
      x->setRange("range",mass_val,mass_val+binwidth);
      //RooAbsReal* integral =  dynamic_cast<RooAbsReal*>(w->pdf("pdf__background_"+channelname)->createIntegral(RooArgSet(*x), NormSet(*x), Range("range"))) ;
      double weight =0;// integral->getVal()*w->function("yield__background_"+channelname)->getVal();
      //integral_array[i*Nbins+ii]=weight;
      // h_outintegral->SetBinContent(i*Nbins+ii,weight);
      // RooAbsReal* integral_proc =  dynamic_cast<RooAbsReal*>(w->pdf("pdf__commonSig_"+channelname)->createIntegral(RooArgSet(*x), NormSet(*x), Range("range"))) ;
      // integral_array_proc[i*Nbins+ii] = integral_proc->getVal();
	
      // RooAbsReal* integralA = dynamic_cast<RooAbsReal*>(pdfi->createIntegral(RooArgSet(*x), NormSet(*x), Range("range"))) ;
      double weightA =0;// integralA->getVal()*totalD;
    sumS += weightA-weight;
    double value = hdata->GetBinContent(ii+1);
    double error = hdata->GetBinError(ii+1);

    if(value>0.5) {
      h1->SetBinContent(ii+1,value-weight);
      h1->SetBinError(ii+1,error);
    }
    mass_val+=binwidth;
  }

  h1->GetYaxis()->SetRangeUser(h1->GetMinimum()*1.5, h1->GetMaximum()*1.5);
  h1->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
  h1->GetYaxis()->SetTitle("Data - Bkg Fit");
  h1->GetYaxis()->SetTitleSize(0.075);
  h1->GetYaxis()->SetTitleOffset(0.80);
  h1->GetYaxis()->SetLabelSize(0.075);
  h1->GetXaxis()->SetTitleSize(0.075);
  h1->GetXaxis()->SetTitleOffset(0.9);
  h1->GetXaxis()->SetLabelSize(0.075);
  h1->SetLineWidth(1);
  RooPlot* frameS = x->frame();//(Binning(Nbins));
  if(!isBonly) w->pdf("pdf__commonSig_"+channelname)->plotOn(frameS,LineColor(kRed),Normalization(best_fit_mu*allsig));
 
  TH1F* hdummyS = new TH1F("hdummyS","hdummyS",Nbins,x->getMin(),xmax);
  TH1F* hdummyB = new TH1F("hdummyB","hdummyB",Nbins,x->getMin(),xmax);
  TH1F* hdummymuhat = new TH1F("hdummymuhat","hdummymuhat",Nbins,x->getMin(),xmax);
  hdummyS->SetLineColor(kRed);
  hdummyS->SetLineWidth(2);
  hdummyB->SetLineColor(kBlue);
  hdummyB->SetLineWidth(2);
  hdummyB->SetLineStyle(2);
  hdummymuhat->SetLineColor(kGreen);
  hdummymuhat->SetLineWidth(2);
  TLegend* lg = new TLegend(0.55,0.55,0.9,0.9);
  lg->SetLineColor(0);
  lg->SetFillColor(0);
  lg->SetTextSize(0.05);
  lg->AddEntry(h1,"Data","EP");
  lg->AddEntry(hdummyB,"Background-only","L");
  if(!isBonly) lg->AddEntry(hdummyS,"Signal+Background","L");

  TCanvas* c1 = new TCanvas("c1","c1",800,800);
  c1->cd();
  
  TPad *pad1 =  new TPad("pad1","pad1name",0.01,0.40,0.99,0.99);
  TPad *pad2 =  new TPad("pad2","pad2name",0.01,0.05,0.99,0.402);
  pad1->Draw();
  pad2->Draw();

  pad1->SetBottomMargin(0.);
  pad1->cd();
  //    pad1->SetLogy();
  //    hframe->GetYaxis()->SetRangeUser(0.002,datai->sumEntries());

  hframe->GetYaxis()->SetRangeUser(0.00,(hdata->GetBinContent(hdata->GetMaximumBin())+hdata->GetBinError(hdata->GetMaximumBin()))*1.9);
  hframe->Draw();
  frame->Draw("same");
  lg->Draw("same");
  pad1->RedrawAxis();
  pad1->Update();
  // HW legend and labeling 
  // a lot leftover from Hongtao's analysis

  TLatex* text = new TLatex();
  TString textString = "#bf{#it{ATLAS}} Internal";
  text->SetNDC();
  text->SetTextFont(42);
  text->SetTextColor(kBlack);
  text->SetTextSize(0.05);
  text->DrawLatex(0.2,0.88,textString);
  textString = "#sqrt{s}=13 TeV, 79.8 fb^{-1}";
  text->DrawLatex(0.2,0.81,textString);
  textString = channelname;
  text->DrawLatex(0.2,0.75,textString);
  text->DrawLatex(0.2,0.69,c_chi2);

  pad2->SetTopMargin(0.);
  pad2->cd();
  h1->Draw();
  TLine* l = new TLine(x->getMin(),0,xmax,0);
  l->SetLineColor(kBlue);
  l->SetLineWidth(2);
  l->Draw("same");
  frameS->Draw("same");
  pad2->RedrawAxis();
  pad2->Update();
  
   system("mkdir -vp fig/invmass/"+jobname);
  PrintCanvas(c1, "fig/invmass/"+jobname+"/"+channelname);
  
  delete hframe;
  delete h1;
  delete hdata;
  delete hdummyS;
  delete hdummyB ;
  delete hdummymuhat;
  }
  
// // HW we are done with individual categories 
  system("mkdir -vp fig/invmass/"+jobname);
  cout << "End loop over individual categories" << endl;

  // JD moves all of this to dedicated function
  RooRealVar *x ;
  
  // HW the loop below will calculate the normalization ( = unweighted normalization * category weight)
  // after the loop, the RooArSet for the pdfs should have 31 pdfs from the analysis, 
  // and the RooArgSet for the normalziation should have 31 entries 
  for ( int i= 0; i < numChannels; i++ ) {
    m_cat->setBin(i);
    TString channelname=m_cat->getLabel();
    RooAbsPdf* pdfi = m_pdf->getPdf(m_cat->getLabel());
    RooDataSet* datai = ( RooDataSet* )( m_dataList->At( i ) );
    x=(RooRealVar*)pdfi->getObservables(datai)->first();
    x->SetName("atlas_invMass");
    x->SetTitle("atlas_invMass");
  }   
   
 
  // hwt -> Write("hwt");
  // hwt_ggF -> Write("hwt_ggF");
  // hwt_VBF -> Write("hwt_VBF");
  // hwt_VH -> Write("hwt_VH");
  // hwt_top -> Write("hwt_top");
  // // hunwt -> Write("hunwt");
  // TFile *histoutfile = TFile::Open("hist_output_new.root","RECREATE");
  // histoutfile->cd(); 
  // h_outweights->Write("h_outweights");
  // h_outweights_ggF->Write("h_outweights_ggF");
  // h_outweights_VBF->Write("h_outweights_VBF");
  // h_outweights_VH->Write("h_outweights_VH");
  // h_outweights_top->Write("h_outweights_top");
  
  
  // //h_outintegral->Write("h_outintegral");
  // histoutfile->Write();
  // histoutfile->Close();
  
  fin->cd();
  // JD draw weighted plots by calling dedicated function
  TString name;
if(proc == "incl"){
  name = jobname+"/hwt";
  draw_weighted(hwt,w,x,wtsb,integral_array,integral_array_proc,name,"Inclusive");
  cout << "Drew weighted hist" << endl;
  }
  else if(proc == "ggF"){
  name = jobname+"/hwt_ggF";
  draw_weighted(hwt_ggF,w,x,wtsb_ggF,integral_array,integral_array_proc,name,"ggF");
  cout << "Drew ggF weighted hist" << endl;
  }
  else if(proc == "VBF")
    {
  name = jobname+"/hwt_VBF";
  draw_weighted(hwt_VBF,w,x,wtsb_VBF,integral_array,integral_array_proc,name,"VBF");
  cout << "Drew VBF weighted hist" << endl;
    }
  else if(proc == "VH"){
  name = jobname+"/hwt_VH";
  draw_weighted(hwt_VH,w,x,wtsb_VH,integral_array,integral_array_proc,name,"VH");
  cout << "Drew VH weighted hist" << endl;
  }
  else if(proc == "top"){
  name = jobname+"/hwt_top";
  draw_weighted(hwt_top,w,x,wtsb_top,integral_array,integral_array_proc,name,"top");
  cout << "Drew top weighted hist" << endl;
  }
/*
  double wt1[numChannels];
  for(int i=0; i<numChannels; i++){
    wt1[i] = 1;
  }
  name = jobname+"/hunwt";
  // draw_weighted(hunwt,w,x,wt1,integral_array,integral_array_proc,name,"Unweighted");
  cout << "Drew unweighted hist" << endl;
*/
  datahistfile->Close();
}
