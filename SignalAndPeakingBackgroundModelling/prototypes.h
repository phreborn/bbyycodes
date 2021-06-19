//prototypes
//to rename without Signal since there is also 1-H

//--------------------------------------------------------
//tool for addin sumw2 to RooMinimizer

class RooMinimizerExt : public RooMinimizer
{
public:
  RooMinimizerExt(RooAbsReal& function) : RooMinimizer(function){}
  void applyCovarianceMatrixExt(TMatrixDSym& V){applyCovarianceMatrix(V);}
  int getNPar(){return fitterFcn()->NDim();}
};

void AddSumw2(RooAbsReal *nll,RooMinimizerExt *roominimize);
//--------------------------------------------------------
vector<string> CreateList_HH_non_resonant_kappa_lambda();
string Return_string_target_kappa(double numerical_target_kappa);
float Return_numerical_target_kappa(string string_target_kappa);
float ReturnCrossSectionTimesBR(float kappa_lambda);

void FillListProcessNonResonant();
void FillListProcessResonant();
void FillListCategories();

//to rename with suffix process
double ReturnCharacteristic(string string_process);
double ReturnCharacteristic_category(string string_category);

void Draw_observable_f_characteristic(string string_category,string string_finalDV,string string_observable_f_characteristic,vector<string> vec_string_characteristic,vector<double> vec_observable_f_characteristic,vector<double> vec_err_observable_f_characteristic);

bool IsCategoryCompatibleToProcess(string string_category,string string_process);
string ReturnResonantCorrespondingCategory(string string_process);

TChain *ReturnSampleSignal(string string_process,string string_category);
//void ReturnWindowFromDataset(float percentage,TChain *chain_process,string string_process,string string_finalDV,double *preferred_low_x,double *preferred_high_x);
void ReturnWindowFromDatasetInitFitParameters(float percentage,TChain *chain_process,string string_process,string string_finalDV,double *preferred_low_x,double *preferred_high_x);
void ReturnWindow(float percentage,RooAbsPdf *pdf_signal,string string_finalDV,float mResonance,double *preferred_left_side,double *preferred_right_side);


//keep index category, in order to be transparent for the exportation to HGam coupling suffixes
int Signal_given_category(int string_category,string string_process,result_f_process &current_results_f_process);

void PrintOverviewResultsShape(result_f_process current_results_f_process,string string_category);

void PrintHeaderResults(FILE **fsp,string string_process,string string_category,bool sorted);
void PrintTailResults(FILE **fpp,string string_process,string string_category);
void PrintResultYieldEfficiency(string string_yield_efficiency);
double GetCrossSectionTimesBR(string string_process);

bool IsFinalDV_in_list(string string_finalDV);

RooAbsPdf *ReturnPdfSignal(string string_functional_form,int index_finalDV,string string_category);

//keep in order to compute FWHM and effective sigma
void ComputeChi2_ndf(double &chi2,int &ndfs,int &nbins,int &nparams,RooDataSet *dataset,RooAbsPdf *pdf);

//shitzpair<double,double> GetYield_given_process(TChain *chain,string string_category);
pair<double,double> GetYield_given_process(string string_process,TChain *chain,string string_category);
void SetExtensionFinalDV(string string_process,string string_category);

void PDG_rounding(double &val,double &err,int &nb_significant_digits);
