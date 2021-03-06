///Largely inherithed from here: https://gitlab.cern.ch/lbnl/Hmumu/analysis (H. Yang)
///Adapted to HH->bbyy by V.Cairo & J.Pearkes

#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "RooCBShape.h"
#include "RooBukinPdf.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TTree.h"
#include "TH1D.h"
#include "TRandom.h"
#include "RooTwoSidedCBShape.h"
#include "RooTwoSidedCBShape.cxx"
#include "RooExpGaussExpShape.h"
#include "RooExpGaussExpShape.cxx"
#include "RooExponential.h"

#include "CommonFunc.h"
#include "CommonFunc.cxx"

#include "../../bbyyPlotter/atlasstyle-00-03-05/AtlasStyle.C"
#include "../../bbyyPlotter/atlasstyle-00-03-05/AtlasLabels.C"
#include "../../bbyyPlotter/atlasstyle-00-03-05/AtlasUtils.C"

using namespace RooFit ;

#include <sstream>
#include <vector>



// !!!Please pay attention to this range, it can change your fit results (some functions, like Bukin, are particularly sensitive to it))
// For mbb this depends on the signal you are fitting
//For HH
const double xmin = 20, xmax = 200;

//const double xmin=0, xmax=300;


TH1D* readSignal(TString categoryName, TString sigNames[], int nSig, TString histName) {
    TH1D *hSig = NULL;

    double yield[nSig];
    // Loop through the samples to fit
    for (int i = 0; i < nSig; i++) {

        // Open data file and get the histogram we want
        TString fileName = "data/" + sigNames[i] + "_" + categoryName + ".root";
        std::cout << "FileName = " << fileName << std::endl;
        TFile f(fileName);

        TH1D *h = (TH1D*)f.Get(histName);
        h = CommonFunc::RerangeTH1D(h, xmin, xmax, sigNames[i]); // TODO: figure out what this does
        h->SetDirectory(0); // ?
        f.Close();

        if (!hSig)
            hSig = (TH1D*)h->Clone(histName + "_merge");
        else
            hSig->Add(h);
        h->Print();
        hSig->Print();
        cout << hSig->GetNbinsX() << " " << h->GetNbinsX() << endl;
        yield[i] = h->Integral();
        cout << sigNames[i] << " " << yield[i] << endl;
    }
    return hSig;
}


// for double values
void AddText(double x = 0.0, double y = 0.0, TString string = "dummy", double value = 0.0) {

    TLatex* text = new TLatex();
    text->SetNDC();
    text->SetTextFont(42);
    text->SetTextSize(0.04);
    text->SetTextColor(kBlack);
    text->DrawLatex(x, y, Form(string, value));

}

// for int values
void AddText(double x = 0.0, double y = 0.0, TString string = "dummy", int value = 0) {

    TLatex* text = new TLatex();
    text->SetNDC();
    text->SetTextFont(42);
    text->SetTextSize(0.04);
    text->SetTextColor(kBlack);
    text->DrawLatex(x, y, Form(string, value));

}




// TString* parseInputStrings( TString sigString){
//     // TODO: is there a better way to do this in C/C++?
//     vector<TString> sigNames;
//     stringstream s_stream(sigString); //create string stream from the string
//     while(s_stream.good()) {
//       TString substr;
//       getline(s_stream, substr, ','); //get first string delimited by comma
//       sigNames.push_back(substr);
//    }
//    cout << sigNames[0];
//    //TString* sigNamesC = sigNames.c_array();
//    TString sigNamesC[sigNames.size()];
//    std::copy(sigNames.begin(), sigNames.end(), sigNamesC);
//     for (int i: sigNamesC) {
//         std::cout << i << ' ';
//     }
//    return sigNamesC;

// }

void Modelling_bbyy_mjj( TString xmlDir = "xml/config/v8/", bool binned = true)
{
    RooMsgService::instance().getStream(1).removeTopic(RooFit::NumIntegration) ;
    RooMsgService::instance().getStream(1).removeTopic(RooFit::Fitting) ;
    RooMsgService::instance().getStream(1).removeTopic(RooFit::Minimization) ;
    RooMsgService::instance().getStream(1).removeTopic(RooFit::InputArguments) ;
    RooMsgService::instance().getStream(1).removeTopic(RooFit::Eval) ;
    RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);
    TH1::SetDefaultSumw2(kTRUE);
    gStyle->SetOptStat(11111);
    gStyle->SetOptFit(11111);
    system("mkdir -vp " + xmlDir + "/model");

    double totalSignal = 0;
    int n_param = 0;
    int n_bins = 0;
    int ndf = 0;

    // Set up signal files to run over  --------------------
    TString filePrefixName = "data/";
    //TString sigNames[] = parseInputStrings(sigString);
    TString sigNames[] = {"HH"};
    //TString sigNames[] = {"HH", "VBF"};
    //TString sigNames[] = {"VBF"};
    //TString sigNames[]={"HH", "bbH", "ggH", "ggZH", "tHjb", "ttH","tWH","WmH","WpH","ZH"};
    const int nSig = sizeof(sigNames) / sizeof(*sigNames); // TODO: this is ugly, C! Should throw error if 0
    std::cout << "nSig = " << nSig << std::endl;

    // Set up the categories for the fit --------------------
    //const TString categoryNames[] = {"LM_A", "LM_B", "HM_A", "HM_B"}; // JP
    //const TString categoryNames[1]={"Validation"}; //to use when fitting mbb because the above categories have a cut in mbb, so not suitable for a fit

    //To check negative weights
    //const TString categoryNames[]={"LM_A", "LM_A_noNegWeights",  "Pass_yy", "Pass_yy_noNegWeights", "XGBoost_btag77_Nominal_looseScore_LMass", "XGBoost_btag77_Nominal_looseScore_LMass_noNegWeights", "Validation", "Validation_noNegWeights"};
  
    const TString categoryNames[]={"XGBoost_btag77_85_Nominal_looseScore_HMass"}; 

    //To check ggF and VBF
    //const TString categoryNames[]={"LM_A", "Pass_yy", "TEST", "Validation", "VBF_btag77", "VBF_btag77_85", "VBF_btag77_BCal", "VBF_btag77_85_BCal", "XGBoost_btag77_85_Nominal_BCal_looseScore_HMass", "XGBoost_btag77_85_Nominal_BCal_looseScore_LMass", "XGBoost_btag77_85_Nominal_BCal_tightScore_HMass", "XGBoost_btag77_85_Nominal_BCal_tightScore_LMass", "XGBoost_btag77_85_Nominal_looseScore_HMass", "XGBoost_btag77_85_Nominal_looseScore_LMass", "XGBoost_btag77_85_Nominal_tightScore_HMass", "XGBoost_btag77_85_Nominal_tightScore_LMass", "XGBoost_btag77_Nominal_BCal_looseScore_HMass", "XGBoost_btag77_Nominal_BCal_looseScore_LMass", "XGBoost_btag77_Nominal_BCal_tightScore_HMass", "XGBoost_btag77_Nominal_BCal_tightScore_LMass", "XGBoost_btag77_Nominal_looseScore_HMass", "XGBoost_btag77_Nominal_looseScore_LMass", "XGBoost_btag77_Nominal_tightScore_HMass", "XGBoost_btag77_Nominal_tightScore_LMass"};  

    const int nCat = sizeof(categoryNames) / sizeof(*categoryNames); // TODO: this is ugly, C! Should throw error if 0
    
    TString binningName;
    if (binned) binningName = "Binned";
    else binningName = "Unbinned";

    // Set up naming of output files -------------------
    // TODO: Change this so that it is more general than HH and H or sample name
    TString outputPrefix;
    if (nSig == 10) { outputPrefix = "HH_and_H"; }
    else if (nSig == 2) { outputPrefix = "ggF_and_VBF"; }
    else if (nSig == 1) { outputPrefix = sigNames[0]; }
    else outputPrefix = "Unknown";


    TString fitFunctions[] = {"DSCB","ExpGaussExp","Bukin","Exponential"};
    int nfitFunc = 4;

    // Do fit for the individual categories --------------------------------
    for (int icat = 0; icat < nCat; icat++) {


        TString categoryName = "CATEGORY_" + categoryNames[icat];
        TString histName = "sumHisto_m_jj_"+categoryNames[icat]; // to fit mbb
        std::cout << "histName = " << histName << std::endl;

        // Tree for unbinned fit
                // Open data file and get the histogram we want
        TString fileName = "data/" + sigNames[0] + "_" + categoryNames[icat]+ "_tree.root";
        std::cout << "FileName = " << fileName << std::endl;
        TFile fTree(fileName);
        TTree *tree = (TTree*) fTree.Get("CollectionTree");
        std::cout<< "tree name = " << tree->GetName() << std::endl;

        TH1D* MassInc = readSignal(categoryNames[icat], sigNames, nSig, histName);
        MassInc = CommonFunc::RerangeTH1D(MassInc, xmin, xmax);
        MassInc->SetDirectory(nullptr);
        //  MassInc->Draw();

        // Declare observable x
        RooRealVar x("x", "x", xmin, xmax) ; // for binned fit 
        RooRealVar weight("weight","weight",-1000,1000) ; // for unbinned fit 
        RooRealVar SF("SF","SF",-1000,1000) ; // for unbinned fit
        RooRealVar total_weight("total_weight","total_weight",-1000,1000) ; // for unbinned fit
        RooRealVar m_jj("m_jj","m_jj",xmin, xmax); 

        // Create a binned dataset that imports contents of TH1 and associates its contents to observable 'x'
        RooDataHist dh("dh", "dh", x, Import(*MassInc)) ; // for binned fit 
        dh.Print();
        n_bins=MassInc->GetNbinsX(); //this works for binned fits, needs to be implemented correctly for unbinned - i.e. bin the plots and measure the chi2 after that
        RooDataSet  ds("m_jj","m_jj",tree,RooArgSet(m_jj,total_weight),"","total_weight"); // for unbinned fit
       
        ds.Print(); 
      
        /*for (int i=0 ; i<ds.numEntries() ; i++) {
             ds.get(i) ;
             std::cout<< " weights = " << ds.weight() << ", fileName= " << fileName<< endl ; 
             std::cout<< " weights no Weights = " << ds_noWeights.weight() << endl ; 
        }*/


        // !!!Please pay attention to the initial parameters (for mbb they depend on the signal you are fitting as well as on the categories). Some functions, like Bukin, are particularly sensitive to it.
        // Crystal Ball Components
        const int NPAR_DSCB  = 6;
        RooRealVar CB_mean("CB_mean", "mean of CB", 100.0, 80, 130) ;
        RooRealVar CB_sigma("CB_sigma", "sigma of CB", 2.5, 0.5, 8.0) ;
        RooRealVar CB_alphaLo("CB_alphaLo", "alpha of CB", 1.8, 0., 5.) ;
        RooRealVar CB_alphaHi("CB_alphaHi", "alpha of CB", 1.8, 0., 5.) ;
        RooRealVar CB_nLo("CB_nLo", "n of CB", 3, 0, 100);
        RooRealVar CB_nHi("CB_nHi", "n of CB", 10, 0, 100);
        RooTwoSidedCBShape *sig_DSCB;
        RooTwoSidedCBShape sig_DSCB_histo("cb1", "Signal Component 2", x, CB_mean, CB_sigma, CB_alphaLo, CB_nLo, CB_alphaHi, CB_nHi); 
        RooTwoSidedCBShape sig_DSCB_tree("cb1", "Signal Component 2", m_jj, CB_mean, CB_sigma, CB_alphaLo, CB_nLo, CB_alphaHi, CB_nHi); 
        RooRealVar *varInName_DSCB[NPAR_DSCB] = {&CB_alphaLo, &CB_mean, &CB_nLo, &CB_sigma, &CB_alphaHi, &CB_nHi};
        TString varOutName_DSCB[NPAR_DSCB] = {"alphaCBLo", "meanNom", "nCBLo", "sigmaCBNom", "alphaCBHi", "nCBHi"};

        if (binned) sig_DSCB = &sig_DSCB_histo;
        else sig_DSCB = &sig_DSCB_tree;

        // ExpGaussExp Components
        const int NPAR_EGE   = 4;
        RooRealVar EGE_mean("EGE_mean", "mean of EGE", 100.0, 80, 130) ;
        RooRealVar EGE_sigma("EGE_sigma", "sigma of EGE", 2.5, 0.5, 8.0) ;
        RooRealVar EGE_kLo("EGE_kLo", "kLow of EGE", 2.5, 0.01, 10.0) ;
        RooRealVar EGE_kHi("EGE_kHi", "kHigh of EGE", 2.4, 0.01, 10.0) ;
        RooExpGaussExpShape *sig_EGE;
        RooExpGaussExpShape sig_EGE_histo("EGE1", "Signal Component EGE", x, EGE_mean, EGE_sigma, EGE_kLo, EGE_kHi); 
        RooExpGaussExpShape sig_EGE_tree("EGE1", "Signal Component EGE", m_jj, EGE_mean, EGE_sigma, EGE_kLo, EGE_kHi); 
        RooRealVar *varInName_EGE[NPAR_EGE] = {&EGE_mean, &EGE_sigma, &EGE_kLo, &EGE_kHi};
        TString varOutName_EGE[NPAR_EGE] = {"EGE_mean", "EGE_sigma", "EGE_kLo", "EGE_kHi"};

        if (binned) sig_EGE = &sig_EGE_histo;
        else sig_EGE = &sig_EGE_tree; 

        //Bukin - The RooBukinPdf implements the NovosibirskA function, Credits May 26, 2003. A.Bukin, Budker INP, Novosibirsk
        //The following seem to be good starting point parameters for mbb in HH signals - Be careful with setting sigp in particular.
        const int NPAR_BUKIN = 5;
        RooRealVar Bukin_Xp("Bukin_Xp", "The peak position", 100.0, 80, 130) ;
        RooRealVar Bukin_sigp("Bukin_sigp", "The peak width as FWHM divided by 2*sqrt(2*log(2))=2.35", 15, 0.01, 40.0) ;
        RooRealVar Bukin_xi("Bukin_xi", "Peak asymmetry", 0.0, -1, 1) ;
        RooRealVar Bukin_rho1("Bukin_rho1", "Left Tail", -0.1, -1.0, 0.0) ;
        RooRealVar Bukin_rho2("Bukin_rho2", "Right Tail", 0.0, 0.0, 1.0) ;
        RooBukinPdf *sig_Bukin;
        RooBukinPdf sig_Bukin_histo("Bukin1", "Signal Component Bukin", x, Bukin_Xp, Bukin_sigp, Bukin_xi, Bukin_rho1, Bukin_rho2); 
        RooBukinPdf sig_Bukin_tree("Bukin1", "Signal Component Bukin", m_jj, Bukin_Xp, Bukin_sigp, Bukin_xi, Bukin_rho1, Bukin_rho2); 
        RooRealVar *varInName_Bukin[NPAR_BUKIN] = {&Bukin_Xp, &Bukin_sigp, &Bukin_xi, &Bukin_rho1, &Bukin_rho2};
        TString varOutName_Bukin[NPAR_BUKIN] = {"Bukin_Xp", "Bukin_sigp", "Bukin_xi", "Bukin_rho1", "Bukin_rho2"};

        if (binned) sig_Bukin = &sig_Bukin_histo;
        else sig_Bukin = &sig_Bukin_tree;


        //Exponential components \mathrm{RooExponential}(x, c) = \mathcal{N} \cdot \exp(c\cdot x), where \f$ \mathcal{N} \f$ is a normalisation constant that depends on the range and values of the arguments
        const int NPAR_EXP = 1;
        RooRealVar Exp_c("Exp_c", "Exp_c", 1, -10, 10) ;
        RooExponential *sig_Exp;
        RooExponential sig_Exp_histo("Exp", "Exp", x, Exp_c);
        RooExponential sig_Exp_tree("Exp", "Exp", m_jj, Exp_c);
        RooRealVar *varInName_Exp[NPAR_BUKIN] = {&Exp_c};
        TString varOutName_Exp[NPAR_BUKIN] = {"Exp_c"};

        if (binned) sig_Exp = &sig_Exp_histo;
        else sig_Exp = &sig_Exp_tree;


        int NPAR_XML;

        // Loop over our fittings functions ------------------------------------
        for (int ifitFunc = 0; ifitFunc < nfitFunc; ifitFunc++) {


        	// Get the name of the fitting function used (to put on plot)
            TString fitFunctionName = fitFunctions[ifitFunc];
            cout << fitFunctionName << endl;

            RooFitResult* fitr;
            // Fit signal PDF to Data
            // There HAS to be a better way to do this for the multiple functions, running into problems with different classes for sig
            if (ifitFunc == 0) {
            	NPAR_XML = NPAR_DSCB;
                if (binned){
                    fitr = sig_DSCB->fitTo(dh,  Minos(kFALSE), Hesse(kTRUE), Save(),PrintLevel(1), RooFit::SumW2Error(true));
                    //fitr = sig_DSCB.fitTo(dh, Range(115,135), Minos(kTRUE),Save(),PrintLevel(-1));
                    
                }
                else{
                    fitr = sig_DSCB->fitTo(ds, Minos(kFALSE), Hesse(kTRUE), Save(),PrintLevel(-1), RooFit::SumW2Error(true));
                }
                sig_DSCB->Print();
                fitr->Print("v");
                n_param = fitr->floatParsFinal().getSize() + 1; // + 1 is there to account for the normalization that is done internally in RootFit, I am not explicitely floating it
            }
            else if (ifitFunc == 1) {
            	NPAR_XML = NPAR_EGE;
                if (binned){
                    fitr = sig_EGE->fitTo(dh, Minos(kFALSE), Hesse(kTRUE), Save(), PrintLevel(1), RooFit::SumW2Error(true));
                }
                else{
                    fitr = sig_EGE->fitTo(ds, Minos(kFALSE), Hesse(kTRUE), Save(), PrintLevel(-1), RooFit::SumW2Error(true));
                }
                sig_EGE->Print();
                fitr->Print("v"); 
                n_param = fitr->floatParsFinal().getSize() + 1; // + 1 is there to account for the normalization that is done internally in RootFit, I am not explicitely floating it
            }
            else if (ifitFunc == 2) {
            	NPAR_XML = NPAR_BUKIN;
                if (binned){
                    fitr = sig_Bukin->fitTo(dh,  Minos(kFALSE), Hesse(kTRUE), Save(), PrintLevel(1), RooFit::SumW2Error(true));
                }
                else{
                    fitr = sig_Bukin->fitTo(ds, Minos(kFALSE), Hesse(kTRUE), Save(), PrintLevel(-1), RooFit::SumW2Error(true));
                }
                sig_Bukin->Print();
                fitr->Print("v"); 
                n_param = fitr->floatParsFinal().getSize() + 1; // + 1 is there to account for the normalization that is done internally in RootFit, I am not explicitely floating it
            }
            else if (ifitFunc == 3) {
                NPAR_XML = NPAR_EXP;
                if (binned){
                    fitr = sig_Exp->fitTo(dh, Minos(kFALSE), Hesse(kTRUE), Save(),PrintLevel(1), RooFit::SumW2Error(true));

                }
                else{
                    fitr = sig_Exp->fitTo(ds, Minos(kFALSE), Hesse(kTRUE),  Save(), PrintLevel(-1), RooFit::SumW2Error(true));
                }
                sig_Exp->Print();
                fitr->Print("v");
                n_param = fitr->floatParsFinal().getSize() + 1; // + 1 is there to account for the normalization that is done internally in RootFit, I am not explicitely floating it
            } 
           

 
            
            double hintegral = MassInc->GetSumOfWeights();
            cout << "Data Integral = " << hintegral << endl;


            // Plot Fit results
            RooPlot* xframe;
            if (binned){
                xframe = x.frame(Title("Fit " + outputPrefix + " " + categoryNames[icat] + " " + fitFunctionName));
                dh.plotOn(xframe, MarkerColor(kBlack), DataError(RooAbsData::SumW2));
                //dh.statOn(xframe,Layout(0.50,0.90,0.80));
            }
            else {
                xframe = m_jj.frame(Title("Fit " + outputPrefix + " " + categoryNames[icat] + " " + fitFunctionName));
                ds.plotOn(xframe, MarkerColor(kBlack), DataError(RooAbsData::SumW2));
                //ds.statOn(xframe,Layout(0.50,0.90,0.80));
            }
            if (ifitFunc == 0) { // TODO: Again, has to be a better way 
            	sig_DSCB->plotOn(xframe, LineColor(kTeal + 3));
                sig_DSCB->paramOn(xframe, Format("NEA"));
                xframe->getAttText()->SetTextSize(0.02);
            }
            else if (ifitFunc == 1) {
                sig_EGE->plotOn(xframe, LineColor(kRed + 1));
                sig_EGE->paramOn(xframe, Format("NEA"));
                xframe->getAttText()->SetTextSize(0.02);
            }
            else if (ifitFunc == 2) {
                sig_Bukin->plotOn(xframe, LineColor(kBlue + 1));
                sig_Bukin->paramOn(xframe, Format("NEA"));
                xframe->getAttText()->SetTextSize(0.02);           
            }
            else if (ifitFunc == 3) {
                sig_Exp->plotOn(xframe, LineColor(800));
                sig_Exp->paramOn(xframe, Format("NEA"));
                xframe->getAttText()->SetTextSize(0.02);
            } 

            //the chi2 calculation has to be fixed for unbinned fits
            ndf = n_bins - n_param; 
            double signalchi_red = xframe->chiSquare(n_param);
            double signalchi = signalchi_red*ndf;
            double p_value = TMath::Prob(signalchi, ndf);
            cout << "chi^2/ndf = " << signalchi_red << ", Number of Floating Parameters + Normalization = " << n_param <<  ", Number of bins = "  << n_bins << ", ndf = " << ndf << ", chi^2 = " << signalchi << ", p_value = " << p_value <<endl;
            xframe->GetXaxis()->SetTitle("m_{bb}");
            
            // Construct a histogram with the residuals of the data w.r.t. the curve
            RooHist* hresid = xframe->residHist() ;
            double resintegral = hresid->Integral();
            cout << "Residuals Integral = " << resintegral << endl;
            cout << "Relative Signal Bias = " << resintegral / hintegral << endl;
            
            // Construct a histogram with the pulls of the data w.r.t the curve
            RooHist* hpull = xframe->pullHist();
            
            // Create a new frame to draw the residual distribution and add the distribution to the frame
            RooPlot* frame2 = x.frame(Title("Residual Distribution")) ;
            frame2->addPlotable(hresid, "P") ;
            frame2->GetXaxis()->SetTitle("m_{bb}");
            
            // Create a new frame to draw the pull distribution and add the distribution to the frame
            RooPlot* frame3 = x.frame(Title("Pull Distribution")) ;
            frame3->addPlotable(hpull, "P") ;
            frame3->GetXaxis()->SetTitle("m_{bb}");
            
            TCanvas* c = new TCanvas("chi2residpull", "chi2residpull", 1800, 900) ;
            c->Divide(3) ;
            c->cd(1) ; gPad->SetLeftMargin(0.15) ; xframe->GetYaxis()->SetTitleOffset(1.6) ; xframe->Draw() ;
            
            //add statistic info
            AddText(0.5, 0.52,"#chi^{2} = %f", signalchi);
            AddText(0.5, 0.47,"ndf = %d", ndf);
            AddText(0.5, 0.42,"#chi^{2}_{red} = %f", signalchi_red);
            AddText(0.5, 0.37,"p_{value} = %f", p_value);

            ATLASLabelSqrt(0.55, 0.32, "Internal", kBlack);

            c->cd(2) ; gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.6) ; frame2->Draw() ;
            c->cd(3) ; gPad->SetLeftMargin(0.15) ; frame3->GetYaxis()->SetTitleOffset(1.6) ; frame3->Draw() ;
            c->Update();
            c->Print(xmlDir + "/model/" + outputPrefix + "_" + categoryName +  "_" +fitFunctionName +"_" +binningName +".pdf");
            c->Print(xmlDir + "/model/" + outputPrefix + "_" + categoryName +  "_" +fitFunctionName +"_" +binningName +".png");
            //add a plot in log scale to look at the tails
            c->cd(1);
            xframe->GetYaxis()->SetRangeUser(0.000001, 0.3);
            gPad->SetLogy(1);
            c->Print(xmlDir + "/model/" + outputPrefix + "_" + categoryName +  "_" +fitFunctionName +"_" +binningName +"_logY.pdf");


            // Print out signal model XML file
            TString outputModelFileName = xmlDir + "/model/" + outputPrefix + "_" + categoryName + "_" +fitFunctionName +"_" +binningName + ".xml";
            cout << outputModelFileName; 

            ofstream fout(outputModelFileName);
            fout << "<!DOCTYPE Model SYSTEM 'AnaWSBuilder.dtd'>" << endl;
            fout << "<Model Type=\"UserDef\">" << endl;
            cout << NPAR_XML << endl; 
            
            for (int ivar = 0; ivar < NPAR_XML; ivar++) {
            	// TODO: Again, has to be a better way 
            	if (ifitFunc == 0) {fout << "  <Item Name=\"" + varOutName_DSCB[ivar] + Form("[%f]\"/>", varInName_DSCB[ivar]->getVal()) << endl;}
            	else if (ifitFunc == 1) {fout << "  <Item Name=\"" + varOutName_EGE[ivar] + Form("[%f]\"/>", varInName_EGE[ivar]->getVal()) << endl;}
            	else if (ifitFunc == 2) {fout << "  <Item Name=\"" + varOutName_Bukin[ivar] + Form("[%f]\"/>", varInName_Bukin[ivar]->getVal()) << endl;}
                else if (ifitFunc == 3) {fout << "  <Item Name=\"" + varOutName_Exp[ivar] + Form("[%f]\"/>", varInName_Exp[ivar]->getVal()) << endl; }
            }
            fout << Form("  <Item Name=\"expr::mean('@0+@1-125', meanNom, mH[125])\"/>") << endl;
            if (ifitFunc == 0) { // TODO: Again, has to be a better way 
                fout << Form("  <ModelItem Name=\"RooTwoSidedCBShape::signalPdf(:observable:, mean, sigmaCBNom, alphaCBLo, nCBLo, alphaCBHi, nCBHi)\"/>") << endl;
            }
            else if (ifitFunc == 1) {
                fout << Form("  <ModelItem Name=\"RooExpGaussExpShape::signalPdf(:observable:, mean, sigmaEGENom, kLo, kHi)\"/>") << endl; //VCAIRO
            }
            else if (ifitFunc == 2) {
                fout << Form("  <ModelItem Name=\"RooBukin::signalPdf(:observable:, Bukin_Xp, Bukin_sigp, Bukin_xi, Bukin_rho1, Bukin_rho2)\"/>") << endl;
            }
            else if (ifitFunc == 3) {
                fout << Form("  <ModelItem Name=\"RooExp:::signalPdf(:observable:, Exp_c)\"/>") << endl;
            }

            fout << "</Model>" << endl;
            fout.close();

            TString outputCateFileName = xmlDir + "/category_" + categoryName + ".xml";
            TString inputTemplateFileName = xmlDir + "/category_template.xml";
            ifstream fin(inputTemplateFileName);
            assert(fin);
            ofstream fout_category(outputCateFileName);
            
            // JP commented this background stuff, seems broken/not applicable?
            // std::string line;
            // TString bkgHistName=histName;
            // bkgHistName.ReplaceAll("sig","bkg");
            // TH1* bkgHist=(TH1*)f.Get(bkgHistName);
            // double bkgIntegral=bkgHist->Integral();

            // while(getline(fin, line)){
            //   TString l=line.c_str();
            //   l.ReplaceAll("#category#", categoryName);
            //   l.ReplaceAll("#sigYield#", Form("%f", hintegral));
            //   l.ReplaceAll("#inputHistFile#", fileName);
            //   l.ReplaceAll("#histName#", bkgHistName);
            //   l.ReplaceAll("#bkgYield#", Form("%f", bkgIntegral));
            //   fout_category<<l<<endl;
            // }
            totalSignal += hintegral;
        }
    }

    cout << endl << "TOTAL SIGNAL: " << totalSignal << endl;
}
