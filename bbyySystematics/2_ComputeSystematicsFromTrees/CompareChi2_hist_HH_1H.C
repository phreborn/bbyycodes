void ComputeChi2(TH1F *hist1,TH1F *hist2,double &chi2,int &ndf);

void CompareChi2_HH_1H()
{
  //comparison between aMCnloHwpp_hh_yybb_AF2 and SingleHiggs
  
  vector<string> vec_string_category={"NonResonant_LooseLowMass","NonResonant_TightLowMass","NonResonant_LooseHighMass","NonResonant_TightHighMass","NonResonant_Inclusive"};
  //vector<string> vec_string_category={"NonResonant_LooseLowMass"};
  
  //  vector<string> vec_string_campaign={"h024_mc16a","h024_mc16d","h024_mc16e","h024_mc16a_h024_mc16d","h024_mc16a_h024_mc16d_h024_mc16e"};
  //  vector<string> vec_string_campaign={"h024_mc16d"};
  vector<string> vec_string_campaign={"h024_mc16a_h024_mc16d_h024_mc16e"};

  

  for (int index_category=0;index_category<vec_string_category.size();index_category++) {

    string string_category=vec_string_category[index_category];
    
    for (int index_campaign=0;index_campaign<vec_string_campaign.size();index_campaign++) {
      string string_campaign_MxAOD=vec_string_campaign[index_campaign];
      
      string string_process;

      string_process="SingleHiggs";
      TFile *file_1H=new TFile((string("/sps/atlas/e/escalier/ATLAS_HGam/Outputs_syst_shape_Run2/hist_nominal/")+string_category+"/"+string_campaign_MxAOD+"/"+string_process+"/hist_"+string_campaign_MxAOD+"_"+string_process+"_"+string_category+".root").c_str());
      TH1F *hist_1H=(TH1F *)file_1H->Get("hist_nominal_for_chi2_comparison");
      hist_1H->SetMarkerStyle(20);
      hist_1H->SetMarkerSize(1.0);
      hist_1H->SetMarkerColor(kBlue+2);
      hist_1H->SetLineColor(kBlue+2);
      hist_1H->Scale(1./hist_1H->Integral());
      
      string_process="aMCnloHwpp_hh_yybb_AF2";
      TFile *file_HH=new TFile((string("/sps/atlas/e/escalier/ATLAS_HGam/Outputs_syst_shape_Run2/hist_nominal/")+string_category+"/"+string_campaign_MxAOD+"/"+string_process+"/hist_"+string_campaign_MxAOD+"_"+string_process+"_"+string_category+".root").c_str());
      TH1F *hist_HH=(TH1F *)file_HH->Get("hist_nominal_for_chi2_comparison");
      hist_HH->SetMarkerStyle(20);
      hist_HH->SetMarkerSize(1.0);
      hist_HH->SetMarkerColor(kGreen+2);
      hist_HH->SetLineColor(kGreen+2);
      hist_HH->Scale(1./hist_HH->Integral());

      int ndf;
      double chi2;
      ComputeChi2(hist_HH,hist_1H,chi2,ndf);

      double pvalue=TMath::Prob(chi2,ndf);

      double Z=-TMath::NormQuantile(pvalue/2); //division by 2 because chi2 counts also the deficit as an uncertainty
      
//       cout << "chi2=" << chi2 << endl;
//       cout << "chi2/ndf=" << chi2/ndf << endl;
//       cout << "pvalue=" << pvalue << endl;
//       cout << "Z=" << Z << endl;

//       cout << "chi2 WW=" << hist_1H->Chi2Test(hist_HH,"WW") << endl;
//       cout << "chi2/ndf=" << hist_1H->Chi2Test(hist_HH,"WWCHI2/NDF") << endl;
//       cout << "p value=" << hist_1H->Chi2Test(hist_HH,"WWP") << endl;
//       cout << "Z=" << -TMath::NormQuantile(0.5*hist_1H->Chi2Test(hist_HH,"WWP")) << endl;
      
      TCanvas *canvas=new TCanvas((string("canvas_")+string_campaign_MxAOD+"_"+string_process+"_"+string_category).c_str(),
				  (string("canvas_")+string_campaign_MxAOD+"_"+string_process+"_"+string_category).c_str(),
				  800,600);
      canvas->SetRightMargin(0.02);
      canvas->SetTopMargin(0.04);

      TH1F *hist_dummy=canvas->DrawFrame(hist_HH->GetXaxis()->GetXmin(),1e-3,hist_HH->GetXaxis()->GetXmax(),0.22);
      hist_dummy->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
      char buffer[50];
      sprintf(buffer,"Entries / %4.2f",hist_1H->GetBinWidth(1));
      hist_dummy->GetYaxis()->SetTitle(buffer);
      
      hist_1H->Draw("same");
      hist_HH->Draw("same");

      float horizontal_position=0.68;
      
      TLatex latex;
      latex.SetNDC(0);
      latex.SetTextSize(0.04); //0.045 is std
      latex.SetTextColor(kBlack);
      latex.SetTextFont(42); //put back the font
      
      latex.SetTextColor(kBlack);
      latex.SetNDC();
      latex.SetTextSize(0.04); //0.045 is std
      latex.SetTextFont(72);
      latex.DrawLatex(horizontal_position,0.92,"ATLAS");
      latex.SetTextFont(42); //put back the font
      latex.DrawLatex(horizontal_position+0.1,0.92,"internal");

      latex.SetTextColor(kGreen+2);
      latex.DrawLatex(horizontal_position,0.83,"HH");

      latex.SetTextColor(kBlue+2);
      latex.DrawLatex(horizontal_position,0.78,"1-H");

      latex.SetTextColor(kBlack);

      latex.SetTextSize(0.02);
      
      latex.DrawLatex(horizontal_position,0.73,string_campaign_MxAOD.c_str());

      latex.SetTextSize(0.03);      
      latex.DrawLatex(horizontal_position,0.68,string_category.c_str());
      




      sprintf(buffer,"#chi^{2}/ndf=%4.2f (%4.2f / %d)",chi2/ndf,chi2,ndf);
      latex.DrawLatex(horizontal_position,0.60,buffer);

      sprintf(buffer,"p=%4.2f",pvalue);
      latex.DrawLatex(horizontal_position,0.55,buffer);

      sprintf(buffer,"Z=%4.2f",Z);
      latex.DrawLatex(horizontal_position,0.50,buffer);

      canvas->SaveAs((string("/sps/atlas/e/escalier/ATLAS_HGam/Outputs_syst_shape_Run2/hist_nominal/")+string("cmp_1H_HH_")+string_campaign_MxAOD+"_"+string_process+"_"+string_category+".png").c_str());
    }
    
  } //end loop on categories
  
  return;
}

void ComputeChi2(TH1F *hist1,TH1F *hist2,double &chi2,int &ndf)
{
  chi2=0;
  ndf=0;
  
  for (int index_bin=1;index_bin<=hist1->GetNbinsX();index_bin++) {
    float content1=hist1->GetBinContent(index_bin);
    if (content1==0) {
      //      cout << "hist1: index_bin=" << index_bin << "empty" << endl;
      continue;
    }
    
    float content2=hist2->GetBinContent(index_bin);
    if (content2==0) {
      //      cout << "hist2: index_bin=" << index_bin << "empty" << endl;
      continue;
    }
    
    float error1=hist1->GetBinError(index_bin);
    float error2=hist2->GetBinError(index_bin);

    chi2+=(content1-content2)*(content1-content2)/(error1*error1+error2*error2);
    ndf++;
  } //end loop on bins
}

