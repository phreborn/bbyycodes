//pdf->setNormRange("TheFitRange");

//if exact, would need shift to barycenter of the shift, thus a TGraph
//of fill with sum_i=1^N value_x / N = position

#include "FunctionalFormConfiguration.h"

#include <iostream>

#define STEP_VERTICAL 0.05
//#define STEP_VERTICAL 0.045
//#define STEP_VERTICAL 0.04
//#define STEP_VERTICAL 0.035
//###################################################################################################
FunctionalFormConfiguration::FunctionalFormConfiguration()
{
  cout << "constructor of FunctionalFormConfiguration" << endl;
}
//###################################################################################################
void FunctionalFormConfiguration::Draw_pdfs_current_category(string string_process,RooDataSet *current_dataset)
{
  //  cout << "Draw_pdfs_current_category phase 1" << endl;

  bool variante_graph=1;

  bool PLOT_DIFFERENCE=0;
  bool PLOT_RATIO=1;
  bool PLOT_RELATIVE_RATIO=0;
  
  //current_dataset already has the blinding, if relevent
  
  //two possible strategies :
  //(i) loop on all components
  //extract relevant components of prod pdf and plot it

  //(ii) split prod pdf in various components
  //loop on components and plot it

  //(i) is more flexible
  
  //Loop on all finalDVs

  char buffer[100];
    
  for (unsigned int index_finalDV=0;index_finalDV<argset_finalDV_noWeight.size();index_finalDV++) {
    cout << "prepare to draw index_finalDV=" << index_finalDV << endl;
    
    RooRealVar *roorealvar_finalDV=((RooRealVar *) RooArgList(argset_finalDV_noWeight).at(index_finalDV));
    
    cout << "roorealvar_finalDV=" << roorealvar_finalDV << endl;
    string string_finalDV=roorealvar_finalDV->GetName();

    float n_signal=0;

    RooAbsPdf *currentpdf_signal=pdf_total_current;

    currentpdf_signal->Print();
    
    //    sprintf(buffer,"canvas_string_process_%s_%s_%s",string_process.c_str(),string_category.c_str(),vec_string_functional_form[index_finalDV].c_str());
    
    //    TCanvas *canvas_current_category=new TCanvas(buffer,buffer,800,600);
    TCanvas *canvas_current_category=new TCanvas("canvas","canvas",800,600);
    canvas_current_category->SetLeftMargin(0.13);
    canvas_current_category->SetRightMargin(0.03);
    canvas_current_category->SetTopMargin(0.05);
    
    TPad *p_histo_mass_principal;
    
    if (PLOT_DIFFERENCE || PLOT_RATIO || PLOT_RELATIVE_RATIO) {
      p_histo_mass_principal=new TPad("p_histo_mass_principal","p_histo_mass_principal",0,0,1,1);
      p_histo_mass_principal->SetBottomMargin(0.3);
    }
    else 
      p_histo_mass_principal=new TPad("p_histo_mass_principal","p_histo_mass_principal",0,0,1,1);
    
    p_histo_mass_principal->cd();
    
    p_histo_mass_principal->SetLeftMargin(0.13);
    p_histo_mass_principal->SetRightMargin(0.03);
    p_histo_mass_principal->SetTopMargin(0.05);
    
    roorealvar_finalDV->Print();
    
    RooPlot *rooplot=0;
    
    if (do_MoriondQCD)
      rooplot=roorealvar_finalDV->frame(118,132,(132-118)/0.5);
    else
      rooplot=roorealvar_finalDV->frame();
    
    rooplot->SetTitle(""); //empty title to prevent printing "A RooPlot of ..."
    
    rooplot->SetXTitle((string("#it{")+string(roorealvar_finalDV->GetTitle())+"} ["+string(roorealvar_finalDV->getUnit())+"]").c_str());
    
    rooplot->GetYaxis()->SetTitleOffset(1.3);
    if (do_MoriondQCD)
      rooplot->GetYaxis()->SetTitleOffset(1.45);

    rooplot->GetYaxis()->SetTitleSize(0.05);
    if (do_MoriondQCD)
      rooplot->GetYaxis()->SetLabelSize(0.045);
    else
      rooplot->GetYaxis()->SetLabelSize(0.05);

    char buffer_dummy[200];
  
    sprintf(buffer_dummy,"Events / %4.2f %s",(rooplot->GetXaxis()->GetXmax()-rooplot->GetXaxis()->GetXmin())/rooplot->GetXaxis()->GetNbins(),roorealvar_finalDV->getUnit());
    rooplot->SetYTitle(buffer_dummy);

    bool DEBUGGING=0;
  
    if (DEBUGGING)
      current_dataset->plotOn(rooplot,RooFit::Name("roohist_absdata"),RooFit::DataError(RooAbsData::SumW2));
    else
      current_dataset->plotOn(rooplot,RooFit::DataError(RooAbsData::SumW2),RooFit::DrawOption("PZ"));
    //      current_dataset->plotOn(rooplot,RooFit::DataError(RooAbsData::SumW2));
    
    //  cout << "Draw_pdfs_current_category phase 8" << endl;

    //used both for determining the max of value + error bar for upper plot, and for substraction plot

    TH1D *hist_dataset=new TH1D("hist_dataset","hist_dataset",roorealvar_finalDV->numBins(),roorealvar_finalDV->getMin(),roorealvar_finalDV->getMax());
    current_dataset->fillHistogram(hist_dataset,RooArgList(*roorealvar_finalDV)); //error is taken correctly, considering the weight: check done

    int higher_granularity=10;

    bool do_hist_fine=0;
    
    TH1D *hist_dataset_fine=0;

    if (do_hist_fine)
      hist_dataset_fine=new TH1D("hist_dataset_fine","hist_dataset_fine",higher_granularity*roorealvar_finalDV->numBins(),roorealvar_finalDV->getMin(),roorealvar_finalDV->getMax());

    bool do_barycenter=0;

    TH1D *hist_dataset_x_weighted_position=0;
    TH1D *hist_dataset_x_weighted_position_sum_weights=0;

    if (do_barycenter) {
      hist_dataset_x_weighted_position=new TH1D("hist_dataset_x_weighted_position","hist_dataset_x_weighted_position",roorealvar_finalDV->numBins(),roorealvar_finalDV->getMin(),roorealvar_finalDV->getMax());
      hist_dataset_x_weighted_position_sum_weights=new TH1D("hist_dataset_x_weighted_position_sum_weights","hist_dataset_x_weighted_position_sum_weights",roorealvar_finalDV->numBins(),roorealvar_finalDV->getMin(),roorealvar_finalDV->getMax());
      
      //----------
      //computation of barycenter from dataset
      
      for (int index_entry=0;index_entry<current_dataset->numEntries();index_entry++) {
	
	RooArgSet *argset=(RooArgSet *)dataset_current_category->get(index_entry);
	
	double observable_value=argset->getRealValue(string_finalDV.c_str());
	double weight=dataset_current_category->weight();
	
	hist_dataset_x_weighted_position->Fill(observable_value,weight*observable_value);
	hist_dataset_x_weighted_position_sum_weights->Fill(observable_value,weight);
	
	//cout << "m_yy=" << observable_value << ", weight=" << weight << endl;
      }
      
      for (int index_bin=1;index_bin<=hist_dataset_x_weighted_position->GetNbinsX();index_bin++) {
	//cout << "index_bin=" << index_bin << ", standard center=" << hist_dataset->GetBinCenter(index_bin) << ", weighted position=" << hist_dataset_x_weighted_position->GetBinContent(index_bin) << endl;
      }
      
      //make the division
      for (int index_bin=1;index_bin<=hist_dataset_x_weighted_position->GetNbinsX();index_bin++) {
	hist_dataset_x_weighted_position->SetBinContent(index_bin,hist_dataset_x_weighted_position->GetBinContent(index_bin)/hist_dataset_x_weighted_position_sum_weights->GetBinContent(index_bin));
      }
      
      //dump for debugging
      for (int index_bin=1;index_bin<=hist_dataset_x_weighted_position->GetNbinsX();index_bin++) {
	//      cout << "index_bin=" << index_bin << ", standard center=" << hist_dataset->GetBinCenter(index_bin) << ", weighted position=" << hist_dataset_x_weighted_position->GetBinContent(index_bin) << endl;
      }
    }

    //----------
    //----------
    TH1D *hist_pdf_x_weighted_position=0;
    TH1D *hist_pdf_x_weighted_position_sum_weights=0;

    if (do_barycenter) {
      hist_pdf_x_weighted_position=new TH1D("hist_pdf_x_weighted_position","hist_pdf_x_weighted_position",roorealvar_finalDV->numBins(),roorealvar_finalDV->getMin(),roorealvar_finalDV->getMax());
      hist_pdf_x_weighted_position_sum_weights=new TH1D("hist_pdf_x_weighted_position_sum_weights","hist_pdf_x_weighted_position_sum_weights",roorealvar_finalDV->numBins(),roorealvar_finalDV->getMin(),roorealvar_finalDV->getMax());
      //----------
      //computation of barycenter from pdf
      cout << "computation of barycenter from pdf" << endl;
      
      n_signal=current_dataset->sumEntries();
      
      cout << "computation for pdf" << endl;

      for (int index_bin=1;index_bin<=hist_pdf_x_weighted_position->GetNbinsX();index_bin++) {
	
	//	int nb_precise_bins=10;
	
	int nb_precise_bins=20;

	for (int index_subbin=0;index_subbin<nb_precise_bins;index_subbin++) {
	  
	  double position=hist_pdf_x_weighted_position->GetBinLowEdge(index_bin)+(1.*index_subbin/nb_precise_bins)*hist_pdf_x_weighted_position->GetBinWidth(1);
	  
	  roorealvar_finalDV->setVal(position);
	  
	  double value_pdf=n_signal*currentpdf_signal->getVal(RooArgSet(*roorealvar_finalDV))*roorealvar_finalDV->getBinWidth(1);
	  
	  hist_pdf_x_weighted_position->Fill(position,value_pdf*position);
	  hist_pdf_x_weighted_position_sum_weights->Fill(position,value_pdf);
	  
	  //	  cout << "position=" << position << ", value_pdf fine=" << value_pdf << endl;

	}
	
      } //end loop on bins

      //make the division
      for (int index_bin=1;index_bin<=hist_pdf_x_weighted_position->GetNbinsX();index_bin++)
	hist_pdf_x_weighted_position->SetBinContent(index_bin,hist_pdf_x_weighted_position->GetBinContent(index_bin)/hist_pdf_x_weighted_position_sum_weights->GetBinContent(index_bin));
      
      //dump for debugging
      for (int index_bin=1;index_bin<=hist_pdf_x_weighted_position->GetNbinsX();index_bin++) {
	cout << "index_bin=" << index_bin << ", standard center=" << hist_pdf_x_weighted_position->GetBinCenter(index_bin) << ", weighted position=" << hist_pdf_x_weighted_position->GetBinContent(index_bin) << endl;
      }
      
      delete hist_pdf_x_weighted_position_sum_weights;
    }
    //----------
    //----------
    //    exit(1);

    if (do_hist_fine)
      current_dataset->fillHistogram(hist_dataset_fine,RooArgList(*roorealvar_finalDV));

    float minimum_y_axis_dataset=hist_dataset->GetBinContent(hist_dataset->GetMinimumBin())-hist_dataset->GetBinError(hist_dataset->GetMinimumBin());
    float maximum_y_axis_dataset=hist_dataset->GetBinContent(hist_dataset->GetMaximumBin())+hist_dataset->GetBinError(hist_dataset->GetMaximumBin());

    //maximum_y_axis_dataset*=3;
    //maximum_y_axis_dataset*=3.2;

    if (do_MoriondQCD)
      maximum_y_axis_dataset*=2.0;
    else
      //next line
      maximum_y_axis_dataset*=4.0;



    //    maximum_y_axis_dataset*=1.1;
    
    //other option would be to get maximum from rooplot immediately after ploting it : less flexible, since we use the error bar for max
  
    //see
    // https://github.com/root-project/root/blob/bbb30cd80f667cec588a461e413feef33b6c2cac/tutorials/roofit/rf212_rangesAndBlinding.C
    //and
    //https://sft.its.cern.ch/jira/browse/ROOT-10660
    
    //    pdf_total_current->plotOn(rooplot,LineColor(kBlue),Range("fitrange"),NormRange("fitrange"));

    //official
    pdf_total_current->plotOn(rooplot,LineColor(kBlue),Range("fitrange"),NormRange("fitrange"),RooFit::Name("roocurve_pdf_shape"));
    
    //pdf_total_current->plotOn(rooplot,LineColor(kBlue),RooFit::Name("roocurve_pdf_shape"));
    

    if (DEBUGGING) {
      rooplot->Print("v");
    
      current_dataset->Print();
    
      pdf_total_current->Print();
    
      int my_nb_param=( (RooArgSet *) pdf_total_current->getParameters(RooArgSet(*roorealvar_finalDV))->selectByAttrib("Constant",kFALSE) )->getSize();
      my_nb_param++; //for normalization
    
      cout << "my_nb_param=" << my_nb_param << endl;
    
      double here_chi2_over_ndf=rooplot->chiSquare("roocurve_pdf_shape","roohist_absdata",my_nb_param);
    
      //  int my_ndof=roorealvar_finalDV->numBins()-my_nb_param;
      int my_ndof=10-my_nb_param;
      cout << "my_ndof=" << my_ndof << endl;
      double mychi2=here_chi2_over_ndf*my_ndof;
      cout << "chi2 withi rooplot=" << mychi2/my_ndof << ", (" << mychi2 << " / " << my_ndof << " )" << endl;
    
      cout << "here_chi2_over_ndf=" << here_chi2_over_ndf << endl;
    
      RooCurve* curve = (RooCurve*) rooplot->findObject("roocurve_pdf_shape",RooCurve::Class()) ;
      if (!curve) {
	cout << "PROBLEM" << endl;
	exit(1);
      }
    
      cout << "curve=" << curve << endl;
    
      RooHist* hist = (RooHist*) rooplot->findObject("roohist_absdata",RooHist::Class()) ;
      if (!hist) {
	cout << "PROBLEM2" << endl;
	exit(1);
      }

      cout << "hist=" << hist << endl;
    
      //  curveDouble_t RooCurve::chiSquare(const RooHist& hist, Int_t nFitParam) const 
    
      Int_t i,np = hist->GetN() ;
    
      cout << "np=" << np << endl;
    
      Double_t x,y,eyl,eyh,exl,exh ;
    
      // Find starting and ending bin of histogram based on range of RooCurve
      Double_t xstart,xstop ;
    
      cout << "phase 1" << endl;
    
      curve->GetPoint(0,xstart,y) ;
      cout << "phase 2" << endl;
    
      curve->GetPoint(curve->GetN()-1,xstop,y) ;
      cout << "phase 3" << endl;
    
      Int_t nbin(0) ;
    
      Double_t chisq(0) ;

      cout << "np=" << np << endl;
      for (i=0 ; i<np ; i++) {   
      
	// Retrieve histogram contents
	hist->GetPoint(i,x,y) ;
	cout << "=====================================" << endl;
	cout << "i=" << i << ", x=" << x << ", y=" << y << endl;
      
	// Check if point is in range of curve
	if (x<xstart || x>xstop) continue ;
      
	eyl = hist->GetEYlow()[i] ;
	eyh = hist->GetEYhigh()[i] ;
	exl = hist->GetEXlow()[i] ;
	exh = hist->GetEXhigh()[i] ;
      
	double avg=0;
      
	// Integrate function over this bin
	//Double_t avg = curve->average(x-exl,x+exh) ;
	//--------------------------------------------
      
	cout << "curve->GetN()=" << curve->GetN() << endl;
      
	//code of average
	double xFirst=x-exl;
	double xLast=x+exl;
      
	// Find Y values and begin and end points
	Double_t yFirst = curve->interpolate(xFirst,1e-10) ;
	Double_t yLast = curve->interpolate(xLast,1e-10) ;
      
	// Find first and last mid points
	Int_t ifirst = curve->findPoint(xFirst,1e10) ;
	Int_t ilast  = curve->findPoint(xLast,1e10) ;
	Double_t xFirstPt,yFirstPt,xLastPt,yLastPt ;
      
	curve->GetPoint(ifirst,xFirstPt,yFirstPt) ;
	curve->GetPoint(ilast,xLastPt,yLastPt) ;
      
	cout << "ifirst=" << ifirst << endl;
	cout << "ilast=" << ilast << endl;
      
	cout << "xFirst=" << xFirst << endl;
	cout << "yFirst=" << yFirst << endl;
      
	cout << "xLast=" << xLast << endl;
	cout << "yLast=" << yLast << endl;
      
	cout << "xFirstPt=" << xFirstPt << endl;
	cout << "yFirstPt=" << yFirstPt << endl;
      
	cout << "xLastPt=" << xLastPt << endl;
	cout << "yLastPt=" << yLastPt << endl;
      
	Double_t tolerance=1e-3*(xLast-xFirst) ;
      
	// Handle trivial scenario -- no midway points, point only at or outside given range
	if (ilast-ifirst==1 &&(xFirstPt-xFirst)<-1*tolerance && (xLastPt-xLast)>tolerance) {
	  avg=0.5*(yFirst+yLast);
	  cout << "STOP" << endl;
	  exit(1);
	}
      
	// If first point closest to xFirst is at xFirst or before xFirst take the next point
	// as the first midway point   
	if ((xFirstPt-xFirst)<-1*tolerance) {
	  cout << "Decide to take next first point" << endl;
	  ifirst++ ;
	  curve->GetPoint(ifirst,xFirstPt,yFirstPt) ;
	}
      
	cout << "ifirst=" << ifirst << endl;
	cout << "xFirstPt=" << xFirstPt << ", yFirstPt=" << yFirstPt << endl;
      
	// If last point closest to yLast is at yLast or beyond yLast the the previous point
	// as the last midway point
	if ((xLastPt-xLast)>tolerance) {
	  ilast-- ;
	  curve->GetPoint(ilast,xLastPt,yLastPt) ;
	  cout << "Decide to take previous last point" << endl;
	}
      
	cout << "ilast=" << ilast << endl;
	cout << "xLastPt=" << xLastPt << ", yLastPt=" << yLastPt << endl;
      
	Double_t sum(0),x1,y1,x2,y2 ;
      
	cout << "sum=" << sum << endl;
	// Trapezoid integration from lower edge to first midpoint
	sum += (xFirstPt-xFirst)*(yFirst+yFirstPt)/2 ;
      
      
	cout << "phase 1, sum=" << sum << endl;
      
	// Trapezoid integration between midpoints
	Int_t j ;
	for (j=ifirst ; j<ilast ; j++) {
	  cout << "j=" << j << endl;
	
	  curve->GetPoint(j,x1,y1) ;
	  curve->GetPoint(j+1,x2,y2) ;
	
	  cout << "x1=" << x1 << ", y1=" << y1 << endl;
	  cout << "x2=" << x2 << ", y2=" << y2 << endl;
	
	  sum += (x2-x1)*(y1+y2)/2 ;
	
	  cout << "phase 2, sum=" << sum << endl;
	}
      
	cout << "last term" << endl;
	cout << "xLastPt=" << xLastPt << ", yLastPt=" << yLastPt << endl;
	cout << "xLast=" << xLast << ", yLast=" << yLast << endl;
      
      
	// Trapezoid integration from last midpoint to upper edge 
	sum += (xLast-xLastPt)*(yLastPt+yLast)/2 ;
      
	cout << "phase 3, sum=" << sum << endl;
      
	avg=sum/(xLast-xFirst);
	cout << "avg=" << avg << endl;
	//--------------------------------------------
	// Add pull^2 to chisq
	if (y!=0) {
	  Double_t pull = (y>avg) ? ((y-avg)/eyl) : ((y-avg)/eyh) ;
	
	  chisq += pull*pull ;
	
	  nbin++ ;
	
	  cout << "nbin=" << nbin << ", x=" << x << ", add chi2=" << pull*pull;
	
	  cout << ", with " << "y=" << y << ", avg=" << avg << ", exl=" << exl << ", exh=" << exh << ", eyl=" << eyl << ", eyh=" << eyh << endl;
	
	}
      } //end loop on np
    
      cout << "nbin=" << nbin << endl;
    
      cout << "chi2/ndf=" << chisq / (nbin-my_nb_param) << endl;
    } //end DEBUGGING

    cout << "phase A2" << endl;
  
    //  exit(1);

    //plot again so that data is put above the pdf
    //idea good, but following is the opposite !!!

    
    //  cout << "minimum_y_axis_dataset=" << minimum_y_axis_dataset << endl;
    //  cout << "maximum_y_axis_dataset=" << maximum_y_axis_dataset << endl;
  
    //rooplot->SetMinimum(1.e-5); //trick in order not to see the bins with 0  
    //rooplot->SetMinimum(minimum_y_axis_dataset);
    //  rooplot->SetMaximum(maximum_y_axis_dataset*3);
    //    rooplot->SetMaximum(maximum_y_axis_dataset*6);
    //  else
    //    rooplot->SetMaximum(maximum_y_axis_dataset*5);
  
    rooplot->SetMaximum(maximum_y_axis_dataset);
    //    rooplot->SetMinimum(0.001); //trick to avoid the 0 to be cut
    //    rooplot->SetMinimum(0.0001); //best trick to avoid the 0 to be cut

    //could not be lower to that, else the 0 appears, for example for X300
    rooplot->SetMinimum(0.0001); //best trick to avoid the 0 to be cut

    //test for Moriond QCD 2021
    rooplot->SetMinimum(0.00001); //best trick to avoid the 0 to be cut

    rooplot->Draw();

    TLatex mylatex;
    mylatex.SetNDC();
    mylatex.SetTextSize(0.040); //0.045 is std
    mylatex.SetTextFont(72);
  
    mylatex.DrawLatex(0.16,0.90,"ATLAS");
    mylatex.SetTextFont(42); //put back the font
    //    mylatex.DrawLatex(0.16+0.1,0.90,"Internal");
    //    mylatex.DrawLatex(0.16+0.1,0.90,"Simulation Internal");
    mylatex.DrawLatex(0.16+0.1,0.90,"Simulation Preliminary");
  
    char buffer_lumi[100];
    //    sprintf(buffer_lumi,"#sqrt{s}=13 TeV, #int L dt=%4.1f fb^{-1}\n",lumi);

    if (do_MoriondQCD)
      sprintf(buffer_lumi,"#sqrt{s}=13 TeV, %4.0f fb^{-1}\n",lumi); //choice Moriond QCD 2021
    else
      sprintf(buffer_lumi,"#sqrt{s}=13 TeV, #int L dt=%4.0f fb^{-1}\n",lumi); //choice Moriond QCD 2021
    mylatex.DrawLatex(0.16,0.82,buffer_lumi);
  
    double vertical_position=0.75;

    if (do_MoriondQCD) {
      mylatex.DrawLatex(0.16,vertical_position,"HH#rightarrowb#bar{b}#gamma#gamma");
      vertical_position-=STEP_VERTICAL;
    }

    if (!do_MoriondQCD) {
      mylatex.SetTextColor(kBlue);
      mylatex.SetTextSize(0.025); //0.045 is std
    }
    else
      mylatex.SetTextSize(0.040); //0.045 is std
      //      mylatex.SetTextSize(0.045); //0.045 is std

    string string_category_for_plot=string_category;
    
    if (string_category=="XGBoost_btag77_withTop_BCal_tightScore_HMass")
      string_category_for_plot="High mass BDT tight";
    else if (string_category=="XGBoost_btag77_withTop_BCal_looseScore_HMass")
      string_category_for_plot="High mass BDT loose";
    else if (string_category=="XGBoost_btag77_withTop_BCal_tightScore_LMass")
      string_category_for_plot="Low mass BDT tight";
    else if (string_category=="XGBoost_btag77_withTop_BCal_looseScore_LMass")
      string_category_for_plot="Low mass BDT loose";
    else if (string_category.find("Resonant")!=string::npos)
      string_category_for_plot="Resonant";
    
    //    mylatex.DrawLatex(0.16,0.75,string_category_for_plot.c_str());
    mylatex.DrawLatex(0.16,vertical_position,string_category_for_plot.c_str());
    mylatex.SetTextSize(0.040); //0.045 is std
      
    mylatex.SetTextColor(kBlack);
  
    //    float vertical_position=0.75;
    //    vertical_position=0.75;

    vertical_position-=STEP_VERTICAL;

    //put dataset first

    string string_process_for_plot=string_process;

    if (string_process=="gg_vbf_HH")
      string_process_for_plot="gg+VBF HH";

    else if (string_process=="gg_X251")
      string_process_for_plot="m_{X}=251 GeV";
    else if (string_process=="gg_X260")
      string_process_for_plot="m_{X}=260 GeV";
    else if (string_process=="gg_X280")
      string_process_for_plot="m_{X}=280 GeV";
    else if (string_process=="gg_X300")
      string_process_for_plot="m_{X}=300 GeV";
    else if (string_process=="gg_X325")
      string_process_for_plot="m_{X}=325 GeV";
    else if (string_process=="gg_X350")
      string_process_for_plot="m_{X}=350 GeV";
    else if (string_process=="gg_X400")
      string_process_for_plot="m_{X}=400 GeV";
    else if (string_process=="gg_X450")
      string_process_for_plot="m_{X}=450 GeV";
    else if (string_process=="gg_X500")
      string_process_for_plot="m_{X}=500 GeV";
    else if (string_process=="gg_X550")
      string_process_for_plot="m_{X}=550 GeV";
    else if (string_process=="gg_X600")
      string_process_for_plot="m_{X}=600 GeV";
    else if (string_process=="gg_X700")
      string_process_for_plot="m_{X}=700 GeV";
    else if (string_process=="gg_X700")
      string_process_for_plot="m_{X}=700 GeV";
    else if (string_process=="gg_X800")
      string_process_for_plot="m_{X}=800 GeV";
    else if (string_process=="gg_X900")
      string_process_for_plot="m_{X}=900 GeV";
    else if (string_process=="gg_X1000")
      string_process_for_plot="m_{X}=1000 GeV";
    
    //    mylatex.DrawLatex(0.16+0.03,vertical_position,string_process.c_str());
    mylatex.DrawLatex(0.16+0.03,vertical_position,string_process_for_plot.c_str());
    
    vertical_position-=STEP_VERTICAL;
  
    TLine legend_line_fit;
    legend_line_fit.SetLineWidth(2);
  
    legend_line_fit.SetLineColor(kBlue);
    legend_line_fit.DrawLineNDC(0.16,vertical_position+0.01,0.16+0.03,vertical_position+0.01); //to put vertical_position+0.01
    mylatex.DrawLatex(0.16+0.04,vertical_position,"pdf");
    
    vertical_position-=STEP_VERTICAL;
    
    cout << "roofitresult=" << roofitresult << endl;

    if (!do_MoriondQCD) {
      
      if (roofitresult) {
	mylatex.DrawLatex(0.16,vertical_position,(string("fit status=")+to_string(roofitresult->status())).c_str());
	
	vertical_position-=STEP_VERTICAL;
	
	mylatex.DrawLatex(0.16,vertical_position,(string("fit cov. qual=")+to_string(roofitresult->covQual())).c_str());
      }
      
      vertical_position-=STEP_VERTICAL;
      
      sprintf(buffer,"fit range : %s #in [%4.0f ; %4.0f]",roorealvar_finalDV->GetTitle(),roorealvar_finalDV->getRange("fitrange").first,roorealvar_finalDV->getRange("fitrange").second);
    
      mylatex.DrawLatex(0.16,vertical_position,buffer);
    }

    vertical_position-=STEP_VERTICAL;

    float x_position_parameters=0.60;
    float y_position_parameters=0.90;

    //  mylatex.SetTextSize(0.03); //0.045 is std
    mylatex.SetTextSize(0.028); //0.045 is std
    //was 0.025

    //TO DO shift a bit the x position

    if (!do_MoriondQCD) {
      //if (do_likelihood1_chi2fit2==1)
      mylatex.DrawLatex(x_position_parameters,y_position_parameters,"Fit: Likelihood: ");
      //  else if (do_likelihood1_chi2fit2==2)
      //    mylatex.DrawLatex(x_position_parameters,y_position_parameters,"Fit: #chi^{2}: ");
      
      string string_list_finalDV;
      
      for (unsigned int internal_index_finalDV=0;internal_index_finalDV<argset_finalDV_noWeight.size();internal_index_finalDV++) {
	string_list_finalDV+=((RooRealVar *) RooArgList(argset_finalDV_noWeight).at(internal_index_finalDV))->GetTitle();
	
	if (internal_index_finalDV+1<argset_finalDV_noWeight.size())
	  string_list_finalDV+=", ";
      }
      
      mylatex.DrawLatex(x_position_parameters+0.15,y_position_parameters,string_list_finalDV.c_str());
      
      y_position_parameters-=STEP_VERTICAL;
      
      if (argset_finalDV_noWeight.size()==1) {
	mylatex.DrawLatex(x_position_parameters,y_position_parameters,(string("func. form bkg: ")+vec_string_functional_form[index_finalDV]).c_str());  
	y_position_parameters-=STEP_VERTICAL;
      }
      else if (argset_finalDV_noWeight.size()==2) {
	for (unsigned int internal_index_finalDV=0;internal_index_finalDV<argset_finalDV_noWeight.size();internal_index_finalDV++) {
	  mylatex.DrawLatex(x_position_parameters,y_position_parameters,(string(((RooRealVar *) RooArgList(argset_finalDV_noWeight).at(internal_index_finalDV))->GetTitle())+string(": ")+string("func. form bkg: ")+vec_string_functional_form[internal_index_finalDV]).c_str());
	  y_position_parameters-=STEP_VERTICAL;
	}
      }
      
      //sprintf(buffer,"(MC-like stat) #chi^{2}/ndf=%4.2f (%4.2f/%d), p=%4.2f",chi2_over_ndf_MC_like_stat,chi2_MC_like_stat,ndf_MC_like_stat,p_value_MC_like_stat);
      sprintf(buffer,"(MC-like stat) #chi^{2}/ndf=%4.2f (%4.2f/%d)",chi2_over_ndf_MC_like_stat,chi2_MC_like_stat,ndf_MC_like_stat);
    }
    
    if (!do_MoriondQCD) {
      mylatex.DrawLatex(x_position_parameters,y_position_parameters,buffer);
      y_position_parameters-=STEP_VERTICAL;
    }

    //shape results

    //print all parameters together

    float y_position_parameters_backup=y_position_parameters;

    //    mylatex.DrawLatex(x_position_parameters,y_position_parameters,buffer);

    if (argset_finalDV_noWeight.size()==1)
      mylatex.SetTextSize(0.028); //0.045 is std
    else if (argset_finalDV_noWeight.size()==2)
      mylatex.SetTextSize(0.015); //0.045 is std



    
    for (unsigned int internal_index_finalDV=0;internal_index_finalDV<argset_finalDV_noWeight.size();internal_index_finalDV++) {

      y_position_parameters=y_position_parameters_backup;
      
      if (internal_index_finalDV==0)
	//	x_position_parameters=0.56;
	x_position_parameters=0.60;
      else if (internal_index_finalDV==1)
	x_position_parameters=0.75;

      RooArgList arglist_param;
      
      RooRealVar *internal_roorealvar_finalDV=((RooRealVar *) RooArgList(argset_finalDV_noWeight).at(internal_index_finalDV));
    
      string internal_string_finalDV=internal_roorealvar_finalDV->GetName();

      cout << "internal_index_finalDV=" << internal_index_finalDV << endl;
      cout << "vec_string_functional_form[internal_index_finalDV]=" << vec_string_functional_form[internal_index_finalDV] << endl;

      if (vec_string_functional_form[internal_index_finalDV]=="Gaussian") {
	arglist_param.add(* (RooRealVar *)vec_pdf_signal_model[internal_index_finalDV]->getVariables()->find((string("muGauss_")+internal_string_finalDV).c_str()));
	arglist_param.add(* (RooRealVar *)vec_pdf_signal_model[internal_index_finalDV]->getVariables()->find((string("sigmaGauss_")+internal_string_finalDV).c_str()));
      }
      else if (vec_string_functional_form[internal_index_finalDV]=="CrystalBall") {
	arglist_param.add(* (RooRealVar *)vec_pdf_signal_model[internal_index_finalDV]->getVariables()->find((string("mu_simple_CB_")+internal_string_finalDV).c_str()));
	arglist_param.add(* (RooRealVar *)vec_pdf_signal_model[internal_index_finalDV]->getVariables()->find((string("sigma_simple_CB_")+internal_string_finalDV).c_str()));
	arglist_param.add(* (RooRealVar *)vec_pdf_signal_model[internal_index_finalDV]->getVariables()->find((string("alphaCB_")+internal_string_finalDV).c_str()));
	arglist_param.add(* (RooRealVar *)vec_pdf_signal_model[internal_index_finalDV]->getVariables()->find((string("nCB_")+internal_string_finalDV).c_str()));
      }
      else if (vec_string_functional_form[internal_index_finalDV]=="DoubleCrystalBall") {
	arglist_param.add(* (RooRealVar *)vec_pdf_signal_model[internal_index_finalDV]->getVariables()->find((string("muCB_")+internal_string_finalDV+"_"+string_category).c_str()));
	arglist_param.add(* (RooRealVar *)vec_pdf_signal_model[internal_index_finalDV]->getVariables()->find((string("sigmaCB_")+internal_string_finalDV+"_"+string_category).c_str()));
	arglist_param.add(* (RooRealVar *)vec_pdf_signal_model[internal_index_finalDV]->getVariables()->find((string("alphaCB_Low_")+internal_string_finalDV+"_"+string_category).c_str()));
	arglist_param.add(* (RooRealVar *)vec_pdf_signal_model[internal_index_finalDV]->getVariables()->find((string("nCB_Low_")+internal_string_finalDV+"_"+string_category).c_str()));
	arglist_param.add(* (RooRealVar *)vec_pdf_signal_model[internal_index_finalDV]->getVariables()->find((string("alphaCB_High_")+internal_string_finalDV+"_"+string_category).c_str()));
	arglist_param.add(* (RooRealVar *)vec_pdf_signal_model[internal_index_finalDV]->getVariables()->find((string("nCB_High_")+internal_string_finalDV+"_"+string_category).c_str()));
      }
      else if (vec_string_functional_form[internal_index_finalDV]=="Bukin") {
	arglist_param.add(* (RooRealVar *)vec_pdf_signal_model[internal_index_finalDV]->getVariables()->find((string("muBukin_")+internal_string_finalDV).c_str()));
	arglist_param.add(* (RooRealVar *)vec_pdf_signal_model[internal_index_finalDV]->getVariables()->find((string("sigmaBukin_")+internal_string_finalDV).c_str()));
	arglist_param.add(* (RooRealVar *)vec_pdf_signal_model[internal_index_finalDV]->getVariables()->find((string("xiBukin_")+internal_string_finalDV).c_str()));
	arglist_param.add(* (RooRealVar *)vec_pdf_signal_model[internal_index_finalDV]->getVariables()->find((string("rho1Bukin_")+internal_string_finalDV).c_str()));
	arglist_param.add(* (RooRealVar *)vec_pdf_signal_model[internal_index_finalDV]->getVariables()->find((string("rho2Bukin_")+internal_string_finalDV).c_str()));
      }
      else if (vec_string_functional_form[internal_index_finalDV]=="ExpGausExp") {
	arglist_param.add(* (RooRealVar *)vec_pdf_signal_model[internal_index_finalDV]->getVariables()->find((string("muExpGausExp_")+internal_string_finalDV).c_str()));
	arglist_param.add(* (RooRealVar *)vec_pdf_signal_model[internal_index_finalDV]->getVariables()->find((string("sigmaExpGausExp_")+internal_string_finalDV).c_str()));
	arglist_param.add(* (RooRealVar *)vec_pdf_signal_model[internal_index_finalDV]->getVariables()->find((string("slopeExp_Low_")+internal_string_finalDV).c_str()));
	arglist_param.add(* (RooRealVar *)vec_pdf_signal_model[internal_index_finalDV]->getVariables()->find((string("slopeExp_High_")+internal_string_finalDV).c_str()));
      }
      else if (vec_string_functional_form[internal_index_finalDV]=="Novosibirsk") {
	arglist_param.add(* (RooRealVar *)vec_pdf_signal_model[internal_index_finalDV]->getVariables()->find((string("peak_Novosibirsk_")+internal_string_finalDV).c_str()));
	arglist_param.add(* (RooRealVar *)vec_pdf_signal_model[internal_index_finalDV]->getVariables()->find((string("width_Novosibirsk_")+internal_string_finalDV).c_str()));
	arglist_param.add(* (RooRealVar *)vec_pdf_signal_model[internal_index_finalDV]->getVariables()->find((string("tail_Novosibirsk_")+internal_string_finalDV).c_str()));
      }


      if (!do_MoriondQCD) {
	
	//shape parameters
	unsigned int index_param=0;
	for (;index_param<arglist_param.size();index_param++) {
	  
	  RooRealVar *roorealvar=(RooRealVar *)arglist_param.at(index_param);
	  
	  /*
	    string string_formatted;
	    string_formatted+="val=";
	    string_formatted+=to_string_with_precision(val,nb_digits);
	    string_formatted+=", err=";
	    string_formatted+=to_string_with_precision(err,nb_digits);
	  */
	  
	  if (!strcmp(roorealvar->getUnit(),"")) //no unit
	    sprintf(buffer,"%s=%4.3f +/- %4.3f",roorealvar->GetTitle(),roorealvar->getVal(),roorealvar->getError());
	  else
	    sprintf(buffer,"%s=%4.3f +/- %4.3f [%s]",roorealvar->GetTitle(),roorealvar->getVal(),roorealvar->getError(),roorealvar->getUnit());
	  
	  mylatex.DrawLatex(x_position_parameters,y_position_parameters,buffer);
	  y_position_parameters-=STEP_VERTICAL;
	}
	
	arglist_param.removeAll();
      }
    } //end loop on finalDV
  
    //arglist_param.Print();

    //    x_position_parameters=0.56;
    x_position_parameters=0.60;
    y_position_parameters=y_position_parameters_backup;

    //depend du nombre précédent
    y_position_parameters-=STEP_VERTICAL;
    y_position_parameters-=STEP_VERTICAL;
    y_position_parameters-=STEP_VERTICAL;

    mylatex.SetTextSize(0.028); //0.045 is std
  
    //    TMarker marker_data(0.175,0.71,20);
    TMarker marker_data(0.175,0.66,20);
    marker_data.SetNDC();
    marker_data.SetMarkerStyle(20);
    marker_data.SetMarkerSize(0.7);
    marker_data.SetMarkerColor(kBlack);
    marker_data.Draw();

    TPad *p_diff_or_ratio_or_relative_ratio=0;

    TH1D *hist_pdf_signal=0;
    TH1D *hist_pdf_signal_fine=0;

    RooCurve *curve_pdf; //for technique makeResidual
    RooDataHist *datahist_raw_dataset;

    if (PLOT_DIFFERENCE || PLOT_RATIO || PLOT_RELATIVE_RATIO) {
      p_diff_or_ratio_or_relative_ratio=new TPad("p_diff_or_ratio_or_relative_ratio","p_diff_or_ratio_or_relative_ratio",0,0.0,1,0.3);
      p_diff_or_ratio_or_relative_ratio->cd();
      p_diff_or_ratio_or_relative_ratio->SetGrid(0,1);
      p_diff_or_ratio_or_relative_ratio->SetTopMargin(0.0);
      p_diff_or_ratio_or_relative_ratio->SetBottomMargin(0.3);
      p_diff_or_ratio_or_relative_ratio->SetLeftMargin(0.13);
      p_diff_or_ratio_or_relative_ratio->SetRightMargin(0.03);
    
      //       TVectorD vec_x;
      //       TVectorD vec_y;
      //       TVectorD vec_err_x_low;
      //       TVectorD vec_err_x_high;
      //       TVectorD vec_err_y_low;
      //       TVectorD vec_err_y_high;
      
      //       TGraphAsymmErrors *graph;
      
      //       if (variante_graph) {
      // 	graph=new TGraphAsymmErrors(vec_x,vec_y,vec_err_x_low,vec_err_x_high,vec_err_y_low,vec_err_y_high);
      //       }

      RooPlot* rooplot_diff_or_ratio_or_relative_ratio=0;

      
    if (do_MoriondQCD)
      rooplot_diff_or_ratio_or_relative_ratio=roorealvar_finalDV->frame(118,132,(132-118)/0.5);
    else
      rooplot_diff_or_ratio_or_relative_ratio=roorealvar_finalDV->frame(roorealvar_finalDV->numBins());
        
      rooplot_diff_or_ratio_or_relative_ratio->SetTitle(""); //empty title to prevent printing "A RooPlot of ..."
      rooplot_diff_or_ratio_or_relative_ratio->SetXTitle((string("#it{")+string(roorealvar_finalDV->GetTitle())+"} ["+string(roorealvar_finalDV->getUnit())+"]").c_str());
    
      rooplot_diff_or_ratio_or_relative_ratio->GetXaxis()->SetTitleOffset(1.03);
      rooplot_diff_or_ratio_or_relative_ratio->GetXaxis()->SetTitleSize(0.13);
      rooplot_diff_or_ratio_or_relative_ratio->GetXaxis()->SetLabelSize(0.13);
      if (PLOT_DIFFERENCE)
	rooplot_diff_or_ratio_or_relative_ratio->SetYTitle("MC-Model");
      else if (PLOT_RATIO)
	rooplot_diff_or_ratio_or_relative_ratio->SetYTitle("MC/Model");
      else if (PLOT_RELATIVE_RATIO)
	rooplot_diff_or_ratio_or_relative_ratio->SetYTitle("(MC-Model)/MC");
      
      rooplot_diff_or_ratio_or_relative_ratio->GetYaxis()->SetTitleOffset(0.4);
      rooplot_diff_or_ratio_or_relative_ratio->GetYaxis()->SetTitleSize(0.11);
      rooplot_diff_or_ratio_or_relative_ratio->GetYaxis()->SetLabelSize(0.075);
    
      
 



      char buffer[100];
      sprintf(buffer,"pdf_signal_%s_%s",string_finalDV.c_str(),string_category.c_str());

      hist_pdf_signal=new TH1D(buffer,buffer,roorealvar_finalDV->numBins(),roorealvar_finalDV->getMin(),roorealvar_finalDV->getMax());

      if (do_hist_fine) {
	sprintf(buffer,"pdf_signal_%s_%s_fine",string_finalDV.c_str(),string_category.c_str());
	
	hist_pdf_signal_fine=new TH1D(buffer,buffer,higher_granularity*roorealvar_finalDV->numBins(),roorealvar_finalDV->getMin(),roorealvar_finalDV->getMax());
      }

      cout << "roorealvar_finalDV->numBins()=" << roorealvar_finalDV->numBins() << ", roorealvar_finalDV->getMin()=" << roorealvar_finalDV->getMin() << ", roorealvar_finalDV->getMax()=" << roorealvar_finalDV->getMax() << endl;
      //Sumw2 already managed fillHistogram

      //to manage blind here, only if fillHistogram is improved with the blinding option
      n_signal=current_dataset->sumEntries();
  
      currentpdf_signal->fillHistogram(hist_pdf_signal,RooArgList(*roorealvar_finalDV),n_signal,0,1,0,1);

      cout << "n_signal=" << n_signal << endl;

      if (do_barycenter) {
	//----------
	//Variation by taking at a different position
	
	cout << "hist_pdf_signal->GetNbinsX()=" << hist_pdf_signal->GetNbinsX() << endl;
	
	for (int index_bin=1;index_bin<=hist_pdf_signal->GetNbinsX();index_bin++) {
	  
	  roorealvar_finalDV->setVal(hist_dataset->GetBinCenter(index_bin));
	  
	  cout << "index_bin=" << index_bin << ", position center of bin=" << roorealvar_finalDV->getVal() << ", value data=" << hist_dataset->GetBinContent(index_bin) << ", value pdf at center of bin=" << n_signal*currentpdf_signal->getVal(RooArgSet(*roorealvar_finalDV))*roorealvar_finalDV->getBinWidth(1) << ", data-pdf=" << hist_dataset->GetBinContent(index_bin)-n_signal*currentpdf_signal->getVal(RooArgSet(*roorealvar_finalDV))*roorealvar_finalDV->getBinWidth(1);
	  
	  roorealvar_finalDV->setVal(hist_dataset_x_weighted_position->GetBinContent(index_bin));
	  
	  //	cout << ", weighted position of bin=" << roorealvar_finalDV->getVal() << ", value pdf at weighted position of bin=" << n_signal*currentpdf_signal->getVal(RooArgSet(*roorealvar_finalDV))*roorealvar_finalDV->getBinWidth(1) << ", value data=" << hist_dataset->GetBinContent(index_bin) << ", data-pdf=" << hist_dataset->GetBinContent(index_bin)-n_signal*currentpdf_signal->getVal(RooArgSet(*roorealvar_finalDV))*roorealvar_finalDV->getBinWidth(1);
	  
	  //roorealvar_finalDV->setVal(hist_pdf_x_weighted_position->GetBinContent(index_bin));
	  //using pdf
	  cout << ", position from pdf center of bin=" << roorealvar_finalDV->getVal() << ", value data=" << hist_dataset->GetBinContent(index_bin) << ", value pdf at center of bin=" << n_signal*currentpdf_signal->getVal(RooArgSet(*roorealvar_finalDV))*roorealvar_finalDV->getBinWidth(1) << ", data-pdf=" << hist_dataset->GetBinContent(index_bin)-n_signal*currentpdf_signal->getVal(RooArgSet(*roorealvar_finalDV))*roorealvar_finalDV->getBinWidth(1) << endl;
	  
	  hist_pdf_signal->SetBinContent(index_bin,n_signal*currentpdf_signal->getVal(RooArgSet(*roorealvar_finalDV))*roorealvar_finalDV->getBinWidth(1));
	}
	
	delete hist_pdf_x_weighted_position;
      }
      //----------
      bool do_integral_pdf=0;
      
      if (do_integral_pdf) {
	
	for (int index_bin=1;index_bin<=hist_pdf_signal->GetNbinsX();index_bin++) {
	  
	  double integral=0;
	  
	  int nb_precise_bins=20;
	  
	  cout << "index_bin=" << index_bin << endl;

	  for (int index_subbin=0;index_subbin<nb_precise_bins;index_subbin++) {
	    
	    double position=hist_pdf_signal->GetBinLowEdge(index_bin)+(1.*index_subbin/nb_precise_bins)*hist_pdf_signal->GetBinWidth(1);
	    
	    roorealvar_finalDV->setVal(position);
	    
	    double value_pdf=n_signal*currentpdf_signal->getVal(RooArgSet(*roorealvar_finalDV))*roorealvar_finalDV->getBinWidth(1);

	    cout << "index_subbin=" << index_subbin << ", position center of bin=" << roorealvar_finalDV->getVal() << ", value data=" << hist_dataset->GetBinContent(index_bin) << ", value pdf at subbin=" << n_signal*currentpdf_signal->getVal(RooArgSet(*roorealvar_finalDV))*roorealvar_finalDV->getBinWidth(1) << endl;
	    
	    integral+=(n_signal*currentpdf_signal->getVal(RooArgSet(*roorealvar_finalDV))*hist_pdf_signal->GetBinWidth(1)/nb_precise_bins);
	  } //end loop on subbins
	  
	  roorealvar_finalDV->setVal(hist_pdf_signal->GetBinCenter(index_bin));
	  
	  cout << ", position of bin=" << roorealvar_finalDV->getVal() << ", value pdf at center=" << hist_pdf_signal->GetBinContent(index_bin) << endl;
	  cout << "integral pdf for index_bin=" << index_bin << ", integral=" << integral << endl;
	  cout << "while hist_dataset=" << hist_dataset->GetBinContent(index_bin) << endl;
	  
	  hist_pdf_signal->SetBinContent(index_bin,integral);
	}
      } //end do_integral_pdf
      //      exit(1);
      //----------
      if (do_hist_fine)
	currentpdf_signal->fillHistogram(hist_pdf_signal_fine,RooArgList(*roorealvar_finalDV),n_signal,0,1,0,1);

      roorealvar_finalDV->Print();

      sprintf(buffer,"data_%s_%s",string_finalDV.c_str(),string_category.c_str());
      TH1D *hist_diff_or_ratio_or_relative_ratio=new TH1D(buffer,buffer,roorealvar_finalDV->numBins(),roorealvar_finalDV->getMin(),roorealvar_finalDV->getMax());

      TH1D *hist_diff_or_ratio_or_relative_ratio_fine=0;
      if (do_hist_fine) {
	sprintf(buffer,"data_%s_%s_fine",string_finalDV.c_str(),string_category.c_str());
	//      TH1D *hist_diff_or_ratio_or_relative_ratio_fine=new TH1D(buffer,buffer,10*roorealvar_finalDV->numBins(),roorealvar_finalDV->getMin(),roorealvar_finalDV->getMax());
	hist_diff_or_ratio_or_relative_ratio_fine=new TH1D(buffer,buffer,higher_granularity*roorealvar_finalDV->numBins(),roorealvar_finalDV->getMin(),roorealvar_finalDV->getMax());
      }

      //Sumw2 already managed fillHistogram

      //how to manage a condition, for blinding ? Meanwhile, do it by hand when doing the substraction
      current_dataset->fillHistogram(hist_diff_or_ratio_or_relative_ratio,RooArgList(*roorealvar_finalDV));

      if (do_hist_fine)
	current_dataset->fillHistogram(hist_diff_or_ratio_or_relative_ratio_fine,RooArgList(*roorealvar_finalDV));
      //TO DO, check if this manage the blinding directly

      string string_sideband_low;
      string string_sideband_high;
    
      if (string_finalDV=="m_yy") {
	string_sideband_low="sideband_low_m_yy";
	string_sideband_high="sideband_high_m_yy";
      }
      else if (string_finalDV=="m_yybb_tilde") {
	string_sideband_low="sideband_low_m_yybb_tilde";
	string_sideband_high="sideband_high_m_yybb_tilde";
      }
    
      //TO DO : rename index_bin by index_bin_finalDV

      //do the substraction    
      for (int index_bin=1;index_bin<=roorealvar_finalDV->numBins();index_bin++) {

	double value_finalDV=hist_dataset->GetBinCenter(index_bin);
      
	double value_data=hist_dataset->GetBinContent(index_bin); //here we indeed use the original data, without consideration of model, it is used as fit : no error on model

	if (PLOT_DIFFERENCE)
	  hist_diff_or_ratio_or_relative_ratio->SetBinContent(index_bin,value_data-hist_pdf_signal->GetBinContent(index_bin));
	else if (PLOT_RATIO)
	  hist_diff_or_ratio_or_relative_ratio->SetBinContent(index_bin,value_data/hist_pdf_signal->GetBinContent(index_bin));
	else if (PLOT_RELATIVE_RATIO)
	  hist_diff_or_ratio_or_relative_ratio->SetBinContent(index_bin,(value_data-hist_pdf_signal->GetBinContent(index_bin))/value_data);
	
	//	cout << "x=" << value_finalDV << ", value_data=" << value_data << ", hist_pdf_signal->GetBinContent(index_bin)=" << hist_pdf_signal->GetBinContent(index_bin) << ", diff=" << hist_diff_or_ratio_or_relative_ratio->GetBinCenter(index_bin) << endl;
      } //end loop on bins
      
      if (do_hist_fine) {
	
	for (int index_bin=1;index_bin<=higher_granularity*roorealvar_finalDV->numBins();index_bin++) {
	  //	cout << "index_bin with precision : " << index_bin << endl;
	  
	  double value_finalDV=hist_dataset_fine->GetBinCenter(index_bin);
	  
	  double value_data=hist_dataset_fine->GetBinContent(index_bin); //here we indeed use the original data, without consideration of model, it is used as fit : no error on model
	  
	  if (PLOT_DIFFERENCE)
	    hist_diff_or_ratio_or_relative_ratio_fine->SetBinContent(index_bin,value_data-hist_pdf_signal_fine->GetBinContent(index_bin));
	  else if (PLOT_RATIO)
	    hist_diff_or_ratio_or_relative_ratio_fine->SetBinContent(index_bin,value_data/hist_pdf_signal_fine->GetBinContent(index_bin));
	  else if (PLOT_RELATIVE_RATIO)
	    hist_diff_or_ratio_or_relative_ratio_fine->SetBinContent(index_bin,(value_data-hist_pdf_signal_fine->GetBinContent(index_bin))/value_data);
	  //cout << "x=" << value_finalDV << ", value_data=" << value_data << ", hist_pdf_signal->GetBinContent(index_bin)=" << hist_pdf_signal->GetBinContent(index_bin) << endl;
	} //end loop on bins
      }
      
      //hist_diff_or_ratio_or_relative_ratio_bkg->Add(hist_pdf_signal,-1);
      
      //mandatory to do it by hand, else error not computed properly
      
      TArrayD *array_dataset_sumw2=hist_dataset->GetSumw2();

      TArrayD *array_dataset_fine_sumw2;

      if (do_hist_fine)
	array_dataset_fine_sumw2=hist_dataset_fine->GetSumw2();
      
      //      cout << "DEBUG" << endl;

      for (int index_bin=1;index_bin<=roorealvar_finalDV->numBins();index_bin++) {
	double value_finalDV=hist_dataset->GetBinCenter(index_bin);
      
	double value_data=hist_dataset->GetBinContent(index_bin); //here we indeed use the original data, without consideration of model, it is used as fit : no error on model

	//cout << "index_bin=" << index_bin << ", value_finalDV=" << value_finalDV << ", value_data=" << value_data << ", hist_dataset->GetBinError(index_bin)=" << hist_dataset->GetBinError(index_bin) << ", other err=" << sqrt(array_dataset_sumw2->GetAt(index_bin)) << endl;
	
	//data-like uncertainty
	
	if (PLOT_DIFFERENCE)
	  hist_diff_or_ratio_or_relative_ratio->SetBinError(index_bin,sqrt(array_dataset_sumw2->GetAt(index_bin)));
	else if (PLOT_RATIO || PLOT_RELATIVE_RATIO)
	  hist_diff_or_ratio_or_relative_ratio->SetBinError(index_bin,sqrt(array_dataset_sumw2->GetAt(index_bin))/ (hist_pdf_signal->GetBinContent(index_bin)) );
	
      } //end loop on bins

      if (do_hist_fine) {
	
	for (int index_bin=1;index_bin<=higher_granularity*roorealvar_finalDV->numBins();index_bin++) {
	  
	  //	cout << "index_bin=" << index_bin << endl;
	  double value_finalDV=hist_dataset_fine->GetBinCenter(index_bin);
	  
	  double value_data=hist_dataset_fine->GetBinContent(index_bin); //here we indeed use the original data, without consideration of model, it is used as fit : no error on model
	  
	  //data-like uncertainty
	  
	  if (PLOT_DIFFERENCE)
	    hist_diff_or_ratio_or_relative_ratio_fine->SetBinError(index_bin,sqrt(array_dataset_fine_sumw2->GetAt(index_bin)));
	  else if (PLOT_RATIO || PLOT_RELATIVE_RATIO)
	    hist_diff_or_ratio_or_relative_ratio_fine->SetBinError(index_bin,sqrt(array_dataset_fine_sumw2->GetAt(index_bin))/ (hist_pdf_signal_fine->GetBinContent(index_bin)) );
	  
	} //end loop on bins
      }
      

      bool do_technique_standard=1;

      bool do_technique_makeResidual=0;
      
      RooHist *roohist_raw_dataset=0;
      RooHist *roohist_residual=0;
      
      //to make the deletes

      if (do_technique_makeResidual) {
	curve_pdf=(RooCurve*) rooplot->findObject("roocurve_pdf_shape",RooCurve::Class()) ;
	
	roohist_raw_dataset=new RooHist(*hist_dataset,0,1,RooAbsData::SumW2,1,kTRUE,1.);
	roohist_raw_dataset->Print();

	//to put false for first numerical parameter : normalize : in order not to normalize to error (see documentation)
	roohist_residual=roohist_raw_dataset->makeResidHist(*curve_pdf,0,1); //last 1 : average
	roohist_residual->SetMarkerStyle(20);
	roohist_residual->SetMarkerSize(0.7);
	
	//makePullHist

	//	TCanvas *canvas_residual=new TCanvas("canvas_residual","canvas_residual",800,600);
	//	canvas_residual->DrawFrame(114,-0.005,136,0.003);

	//roohist_raw_dataset->Draw();

	//	canvas_residual->SaveAs("figures/residual.png");

	//does not help : rooplot_diff_or_ratio_or_relative_ratio->addPlotable(roohist_residual);
      }
      
      //either clone or put bkg to 0;
      //or RooAddPdf on the fly
    
      RooDataHist dh_data_minus_pdf_bkg("dh_data_minus_pdf_bkg","dh_data_minus_pdf_bkg",*roorealvar_finalDV,RooFit::Import(*hist_diff_or_ratio_or_relative_ratio));

      //sounds like appropriate solution for all cases, even for Asimov
      if (do_technique_standard)
	dh_data_minus_pdf_bkg.plotOn(rooplot_diff_or_ratio_or_relative_ratio,RooFit::DataError(RooAbsData::SumW2),RooFit::MarkerColor(kBlack),RooFit::MarkerStyle(20),RooFit::DrawOption("PZ"));
      //dh_data_minus_pdf_bkg.plotOn(rooplot_diff_or_ratio_or_relative_ratio,RooFit::DataError(RooAbsData::SumW2),RooFit::MarkerColor(kBlack),RooFit::MarkerStyle(20),RooFit::DrawOption("PE0"));
      //	dh_data_minus_pdf_bkg.plotOn(rooplot_diff_or_ratio_or_relative_ratio,RooFit::DataError(RooAbsData::SumW2),RooFit::MarkerColor(kBlack),RooFit::MarkerStyle(20),RooFit::DrawOption("X0"));
      //	dh_data_minus_pdf_bkg.plotOn(rooplot_diff_or_ratio_or_relative_ratio,RooFit::DataError(RooAbsData::SumW2),RooFit::MarkerColor(kBlack),RooFit::MarkerStyle(20));
      
      if (do_hist_fine) {
	RooDataHist dh_data_minus_pdf_bkg_fine("dh_data_minus_pdf_bkg_fine","dh_data_minus_pdf_bkg_fine",*roorealvar_finalDV,RooFit::Import(*hist_diff_or_ratio_or_relative_ratio_fine));
	dh_data_minus_pdf_bkg_fine.plotOn(rooplot_diff_or_ratio_or_relative_ratio,RooFit::DataError(RooAbsData::SumW2),RooFit::MarkerColor(kRed),RooFit::LineColor(kRed),RooFit::MarkerSize(0.02),RooFit::MarkerStyle(20));
      }
      //(no possible to remove empty bins with roofit ?)

      //feature because it is limited to the range that was used for the fit
      //a trick would be to crease a new RooAbsPdf with cloging the parameters
      //if time available, to do
      //mandatory to normalize w/ absolute nb events, else normalization would be diluted with the different dataset

      //     //meanwhile, use the trick to use the total pdf, by putting bkg to 0
      //     ((RooRealVar *)arglist_coefs.at(index_pdf_bkg))->setVal(0);
    
      float maximum_y_axis_dataset_vs_fit=hist_diff_or_ratio_or_relative_ratio->GetBinContent(hist_diff_or_ratio_or_relative_ratio->GetMaximumBin())+hist_diff_or_ratio_or_relative_ratio->GetBinError(hist_diff_or_ratio_or_relative_ratio->GetMaximumBin());
      float minimum_y_axis_dataset_vs_fit=hist_diff_or_ratio_or_relative_ratio->GetBinContent(hist_diff_or_ratio_or_relative_ratio->GetMinimumBin())-hist_diff_or_ratio_or_relative_ratio->GetBinError(hist_diff_or_ratio_or_relative_ratio->GetMinimumBin());

      maximum_y_axis_dataset_vs_fit*=1.2;
      minimum_y_axis_dataset_vs_fit*=1.2;

      //       if (PLOT_DIFFERENCE) { //NEW
      // 	maximum_y_axis_dataset_vs_fit=0.01;
      // 	minimum_y_axis_dataset_vs_fit=-0.01;
      //       }

      if (PLOT_RATIO) {
	//	maximum_y_axis_dataset_vs_fit=1.5;
	maximum_y_axis_dataset_vs_fit=1.49; //in order to avoid overlapping text
	minimum_y_axis_dataset_vs_fit=0.5;
      }
      else if (PLOT_RELATIVE_RATIO) {
	maximum_y_axis_dataset_vs_fit=0.5;
	minimum_y_axis_dataset_vs_fit=-0.5;
      }

      if (do_technique_makeResidual) {
	p_diff_or_ratio_or_relative_ratio->cd();
	TH1F *hist_dummy=p_diff_or_ratio_or_relative_ratio->DrawFrame(roorealvar_finalDV->getMin(),minimum_y_axis_dataset_vs_fit,roorealvar_finalDV->getMax(),maximum_y_axis_dataset_vs_fit);
	hist_dummy->SetLineColor(kBlack);
	roohist_residual->Draw("Psame");
      }

      if (do_technique_standard) {     
	rooplot_diff_or_ratio_or_relative_ratio->GetYaxis()->SetRangeUser(minimum_y_axis_dataset_vs_fit,maximum_y_axis_dataset_vs_fit);
	rooplot_diff_or_ratio_or_relative_ratio->Draw();
	
	delete hist_diff_or_ratio_or_relative_ratio;
      }
    } //end plot_difference
    
    cout << "phase ___5" << endl;

    delete hist_dataset;
    if (do_hist_fine)
      delete hist_dataset_fine;
    if (do_barycenter) {
      delete hist_dataset_x_weighted_position;
      delete hist_dataset_x_weighted_position_sum_weights;
    }
    
    canvas_current_category->cd();
    p_histo_mass_principal->Draw();
  
    p_histo_mass_principal->cd();
    p_histo_mass_principal->Draw();
  
    if (PLOT_DIFFERENCE || PLOT_RATIO || PLOT_RELATIVE_RATIO)
      p_diff_or_ratio_or_relative_ratio->Draw();
  
    string string_saveas="figures/";
    string_saveas+=string_non_resonant_resonant;
    string_saveas+="/";
    string_saveas+=string_model.c_str();
    string_saveas+="/";
    string_saveas+=string_non_resonant_resonant;
    string_saveas+="_";
    string_saveas+=string_process;
  
    string_saveas+="_";
    string_saveas+="Fit_";
  
    string_saveas+="Model_";
    string_saveas+=string_model.c_str();
    string_saveas+="_";
  
    for (unsigned int internal_index_finalDV=0;internal_index_finalDV<argset_finalDV_noWeight.size();internal_index_finalDV++) {
      string_saveas+=vec_string_functional_form[internal_index_finalDV];
    
      if (internal_index_finalDV+1<argset_finalDV_noWeight.size())
	string_saveas+="_";
    }
  
    string_saveas+="_Projection_";
    string_saveas+=string_finalDV;
  
    string_saveas+="_";
    string_saveas+=string_category;
  
    canvas_current_category->SaveAs((string_saveas+".png").c_str());
    canvas_current_category->SaveAs((string_saveas+".pdf").c_str());
    canvas_current_category->SaveAs((string_saveas+".C").c_str());
  
    delete hist_pdf_signal;
  
    delete rooplot;
  
    delete canvas_current_category;
  } //end loop on finalDVs

  cout << "return from Draw_pdfs_current_category" << endl;
  return;
}
//###################################################################################################
void PDG_rounding(double &val,double &err,int &nb_significant_digits)
{
  int three_digits=1000*(err-(int)err);

  cout << "three_digits=" << three_digits << endl;

  if (three_digits>=100 and three_digits<=354)
    nb_significant_digits=2;
  else if (three_digits>=355 and three_digits<=949)
    nb_significant_digits=1;
  else if (three_digits>=950 and three_digits<=999) {
    err=1.+(int)err; //round error digits to 1000
    nb_significant_digits=2;
  }
  //decide to do a else instead of putting a logical OR in a previous condition, in order ot make it clear, and in case there would be a change in the prescription
  else //Strange : the authors of pdg rounding didn't anticipated the cas of three digits <100... Assume that we use 3 digits.
    nb_significant_digits=3;
}
//###################################################################################################
