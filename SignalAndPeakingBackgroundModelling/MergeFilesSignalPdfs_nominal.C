void MergeFilesSignalPdfs_nominal()
{
  gROOT->ProcessLine(".L HggTwoSidedCBPdf.cxx+");
  cout << "compile ExpGausExpPDF" << endl;
  gROOT->ProcessLine(".L ExpGausExpPDF.cxx+");
  gSystem->Load("HggTwoSidedCBPdf_cxx.so");
  gSystem->Load("ExpGausExpPDF_cxx.so");
  //--------------------------------------------
  vector<string> vec_string_category={"NonResonant_LooseLowMass","NonResonant_TightLowMass","NonResonant_LooseHighMass","NonResonant_TightHighMass","NonResonant_Inclusive"};

  //vector<string> vec_string_category={"NonResonant_LooseLowMass"};

  
  TFile *file_merged=new TFile("/sps/atlas/e/escalier/ATLAS_HGam/Outputs_syst_shape_Run2/Pdf_nominal/PdfSignal_NonResonant_Run2.root","recreate");

  for (int index_category=0;index_category<vec_string_category.size();index_category++) {
    cout << "---------------------------" << endl;
    cout << "index_category=" << index_category << endl;
    TFile *current_file=new TFile((string("/sps/atlas/e/escalier/ATLAS_HGam/Outputs_syst_shape_Run2/Pdf_nominal/")+vec_string_category[index_category]+string("/h024_mc16a_h024_mc16d_h024_mc16e/NonResonantPlusSingle/")+string("Pdf_h024_mc16a_h024_mc16d_h024_mc16e_NonResonantPlusSingle_")+vec_string_category[index_category]+".root").c_str());
    current_file->ls();
    
    RooAbsPdf *pdf=(RooAbsPdf *)current_file->Get((string("Pdf_Signal_m_yy_")+vec_string_category[index_category]).c_str());
    //pdf->Print();
    file_merged->cd();
    pdf->Write();
    current_file->Close();
    delete current_file;
    
  } //end loop on categories
  
  file_merged->Close();
}
