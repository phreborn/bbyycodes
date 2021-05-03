//to rename observables
//in finalDV
using namespace std;
#include <boost/algorithm/string/replace.hpp>

//#include "global.h"

void PrintTableSignalPdf_nominal()
{
  gROOT->ProcessLine(".L HggTwoSidedCBPdf.cxx+");
  cout << "compile ExpGausExpPDF" << endl;
  gROOT->ProcessLine(".L ExpGausExpPDF.cxx+");
  gSystem->Load("HggTwoSidedCBPdf_cxx.so");
  gSystem->Load("ExpGausExpPDF_cxx.so");
  //--------------------------------------------
  
  TFile *file_pdfs=new TFile("/sps/atlas/e/escalier/ATLAS_HGam/Outputs_syst_shape_Run2/Pdf_nominal/PdfSignal_NonResonant_Run2.root");
  
  for (int index_category=0;index_category<vec_string_category.size();index_category++) {
    //    cout << "---------------------------" << endl;
    //    cout << "index_category=" << index_category << endl;
    cout << endl << endl;

    RooAbsPdf *pdf=(RooAbsPdf *)file_pdfs->Get((string("Pdf_Signal_m_yy_")+vec_string_category[index_category]).c_str());

    
    RooRealVar *roorealvar_m_yy=new RooRealVar("m_yy","m_yy",0,1000);
    RooRealVar *roorealvar_m_bb=new RooRealVar("m_bb","m_bb",0,1000);
    RooRealVar *roorealvar_m_yybb=new RooRealVar("m_yybb","m_yybb",0,1000);
    
    RooArgSet argset_observables(*roorealvar_m_yy,*roorealvar_m_bb,*roorealvar_m_yybb);
    
    RooArgSet *argset_parameters=pdf->getParameters(argset_observables);

    printf("\\begin{table}[h!]\n");
    printf("\\begin{tabular}{|l|l|}\n");
    printf("\\hline\n");
    printf("Parameter              & value\\\\\n");
    printf("\\hline\n");
    printf("\\hline\n");
    printf("$\\mu_{CB}$            & $%4.4f$\\\\\n",((RooRealVar *) argset_parameters->selectByName("*muCB*")->first())->getVal());
    printf("\\hline\n");
    printf("$\\sigma_{CB}$         & $%4.4f$\\\\\n",((RooRealVar *) argset_parameters->selectByName("*sigmaCB*")->first())->getVal());
    printf("\\hline\n");
    printf("$\\alpha_{CB}\\ Low$    & $%4.4f$\\\\\n",((RooRealVar *) argset_parameters->selectByName("*alphaCB_Low*")->first())->getVal());
    printf("\\hline\n");
    printf("$n_{CB}\\ Low$         & $%4.4f$\\\\\n",((RooRealVar *) argset_parameters->selectByName("*nCB_Low*")->first())->getVal());
    printf("\\hline\n");
    printf("$\\alpha_{CB}\\ High$   & $%4.4f$\\\\\n",((RooRealVar *) argset_parameters->selectByName("*alphaCB_High*")->first())->getVal());
    printf("\\hline\n");
    printf("$n_{CB}\\ High$        & $%4.4f$\\\\\n",((RooRealVar *) argset_parameters->selectByName("*nCB_High*")->first())->getVal());
    printf("\\hline\n");
    printf("\\end{tabular}\n");
    
    string string_category=vec_string_category[index_category];
    boost::replace_all(string_category,"_","\\_");
    printf("%s",(string("\\caption{")+string_category+string("}\n")).c_str());
    printf("%s",(string("\\label{")+vec_string_category[index_category]+string("}\n")).c_str());
    printf("\\end{table}\n");
    
  } //end loop on categories
  file_pdfs->Close();
  

  
  delete file_pdfs;
}
