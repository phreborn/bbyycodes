#ifndef FunctionalFormConfiguration_h
#define FunctionalFormConfiguration_h

#include <RooAbsPdf.h>

using namespace std;

class FunctionalFormConfiguration
{
 public :

  FunctionalFormConfiguration();

  void Draw_pdfs_current_category(string mResonance,RooDataSet *current_dataset);

  string string_category;

  RooAbsPdf *pdf_total_current;

  vector<string> vec_string_functional_form;

  vector<RooAbsPdf *> vec_pdf_signal_model;

  vector<int> vec_n_params;
  vector<double> vec_sigma68; //f(finalDV)
  //------------------
  //  int status_fit;
  RooFitResult *roofitresult;

  double chi2_over_ndf_MC_like_stat;
  double chi2_MC_like_stat;
  int ndf_MC_like_stat;
  double p_value_MC_like_stat;
};

#endif
