//.L InvestivateFrancesco.C
//InvestigateFrancesco(260,230,280)

//for m_bbgamgam fit (resonant analysis)
//the range is the following
//low mass : 245-610 GeV
//high mass : 335-1500 GeV


int nmax=100;
int i=0;


#include <math.h>

double exponentialIntegral(double tmin, double tmax, double k)
{
  return (TMath::Exp(0.5 * k * k + k * tmax) - TMath::Exp(0.5 * k * k + k * tmin)) / k;
}

double gaussianIntegral(double tmin, double tmax)
{
  return sqrt(TMath::TwoPi()) * (ROOT::Math::gaussian_cdf(tmax) - ROOT::Math::gaussian_cdf(tmin));
}


Double_t ExpGausExp(Double_t *x, Double_t *par){

   Double_t std=(x[0]-par[0])/par[1];
   Double_t result=0;
   
   if (std>par[2])
     result=exp(par[2]*par[2]/2.-par[2]*std);
   else if (std<=par[2] && std>-par[3])
     result=exp(-0.5*pow(std, 2));
   else if (std<=-par[3])
     result=exp(par[3]*par[3]/2.+par[3]*std);
   
   //   cout << "TMath::Exp(-par[2]*par[2]/2.)/par[2] + TMath::Exp(-par[3]*par[3]/2.)/par[3]=" << TMath::Exp(-par[2]*par[2]/2.)/par[2] + TMath::Exp(-par[3]*par[3]/2.)/par[3] << endl;

   double sig = par[1];

   //---------------------
   //integral of left exp

   double kLo=par[3];
   
   double integral_exp_left=0;


   //low mass : 245-610 GeV
   //high mass : 335-1500 GeV

   double tmin_left_exp = (0-par[0])/par[1];
   //double tmin_left_exp = (245-par[0])/par[1];
   
   double tmax_left_exp=(1000000-par[0])/par[1]; //min with -kLo is taken afterwhile
   
   //   cout << "tmin_left_exp=" << tmin_left_exp << ", -kLo=" << -kLo << endl;
   if (tmin_left_exp < -kLo) {
     integral_exp_left += exponentialIntegral(tmin_left_exp, TMath::Min(tmax_left_exp, -kLo), kLo);
   }


   //---------------------
   //integral of right exp

   double kHi=par[2];
   
   double integral_exp_right=0;

   //low mass : 245-610 GeV
   //high mass : 335-1500 GeV

   double tmin_right_exp = (0-par[0])/par[1]; //min with -kHi is taken afterwhile
   //double tmin_right_exp = (245-par[0])/par[1]; //min with -kHi is taken afterwhile

   double tmax_right_exp = (1000000-par[0])/par[1];
   //double tmax_right_exp = (610-par[0])/par[1];
   
   //    cout << "tmin_right_exp=" << tmin_right_exp << ", kHi=" << kHi << endl;
   //    cout << "tmax_right_exp=" << tmax_right_exp << endl;
   //    cout << "kHi=" << kHi << endl;
   //    cout << "TMath::Min(-tmin_right_exp,-kHi)=" << TMath::Min(-tmin_right_exp,-kHi) << endl;
   
   if (tmax_right_exp>kHi) {
     integral_exp_right += exponentialIntegral(-tmax_right_exp, TMath::Min(-tmin_right_exp,-kHi),kHi);
   }

   double integral_gauss=0;

   double tmin_gauss = (0-par[0])/par[1]; //min with -kHi is taken afterwhile
   double tmax_gauss = (1000000-par[0])/par[1];

   if (tmax_gauss>=-kLo && tmin_gauss<=kHi) {
     integral_gauss += gaussianIntegral(TMath::Max(tmin_gauss, -kLo), TMath::Min(tmax_gauss, kHi));
   }
   
   //    cout << "---" << endl;
   //    cout << "integral_exp_left=" << integral_exp_left << endl;
   //    cout << "integral left according to Francesco's formula : " << TMath::Exp(-par[3]*par[3]/2.)/par[3] << endl;
   //    cout << "integral_exp_right=" << integral_exp_right << endl;
   //    cout << "integral right according to Francesco's formula : " << TMath::Exp(-par[2]*par[2]/2.)/par[2] << endl;
   
   //    cout << "integral_gaus=" << integral_gauss << endl;
   //    cout << "integral gauss according to Francesco's formula: " << sqrt(2*3.1415927) * (TMath::Erf(sqrt(0.5)*par[2]) + TMath::Erf(sqrt(0.5)*par[3]) )/2. << endl;
   
   /*
   cout << "par[4]=" << par[4] << endl;
   cout << "INTEGRAL=" << sqrt(2*3.1415927) * (TMath::Erf(sqrt(0.5)*par[2]) + TMath::Erf(sqrt(0.5)*par[3]))/2.
     +
     
     //integral of exponential terms
     (
      TMath::Exp(-par[2]*par[2]/2.)/par[2] + TMath::Exp(-par[3]*par[3]/2.)/par[3]
      )
	<< endl;
   */



   /*
   cout << "VALUE=" <<  (result * par[4] ) / 
     (
      //integral of gaussian term
      sqrt(2*3.1415927) * (TMath::Erf(sqrt(0.5)*par[2]) + TMath::Erf(sqrt(0.5)*par[3]))/2.
      +
      
      //integral of exponential terms
      (
       TMath::Exp(-par[2]*par[2]/2.)/par[2] + TMath::Exp(-par[3]*par[3]/2.)/par[3]
       )
      ) << endl;
   */

   i++;

   /*   
   if (i>nmax)
     exit(1);
   */

   //---------------------

   //instable: high variation with range, due to correlations
   //return result*(par[4] / par[1]) / (sqrt(2*3.1415927));


   //version stable with no correlations of parameters
   //expressed in units of sigma, just to be stable for changes of yields with luminosity
   return (result * par[4] / par[1]) / 
     
     //expressed in absolute value
     //	  return (result * par[4] ) / 
     (
      //integral of gaussian term
      sqrt(2*3.1415927) * (TMath::Erf(sqrt(0.5)*par[2]) + TMath::Erf(sqrt(0.5)*par[3]))/2.
      +
      
      //integral of exponential terms
      (
       TMath::Exp(-par[2]*par[2]/2.)/par[2] + TMath::Exp(-par[3]*par[3]/2.)/par[3]
       )
      );
   
   //remark: result / [ integral...] is the normalized pdf
}

int InvestigateFrancesco(Long_t mass, double xmin, double xmax){

  gStyle->SetOptFit(1);

  TString masscat="high";
  if (mass<500) masscat="low";

  TFile *_file0 = TFile::Open(TString("mc15c.aMcAtNloHwpp_Xhh_m")+mass+"_yybb.MxAODJetAllSys1.p2815.h015d.root");
  gDirectory->cd(masscat+"Mass/2Tag");
  
  TH1F* href = (TH1F*) gDirectory->Get("2Tag_HGamEventInfoAuxDyn.yybb_"+masscat+"Mass_m_yybb");
  double int_ref=href->Integral(href->GetBin(xmin),href->GetBin(xmax));
  TH1F* hsys = (TH1F*) gDirectory->Get("2Tag_HGamEventInfo_JET_JER_SINGLE_NP__1upAuxDyn.yybb_"+masscat+"Mass_m_yybb");
  double int_sys=hsys->Integral(hsys->GetBin(xmin),hsys->GetBin(xmax));

  std::cout<<"Integral in range ("<<xmin<<","<<xmax<<"): int_ref="<<int_ref<<"; int_JER="<<int_sys<<"; variation_rel="<<(int_ref-int_sys)/int_ref*100.<<std::endl;

  int_ref=href->Integral();
  int_sys=hsys->Integral();
  std::cout<<"Integral in full range: int_ref="<<int_ref<<"; int_JER="<<int_sys<<"; variation_rel="<<(int_ref-int_sys)/int_ref*100.<<std::endl;

  TF1 *f_EGE = new TF1( "ExpGausExp", ExpGausExp, xmin, xmax, 5);
  

  f_EGE->SetParameters(mass, mass/30., 1., 1., 60.); //Francesco

  //  f_EGE->SetParameters(mass, mass/30., 1., 1., 9); //Marc
  f_EGE->SetNpx(100000);

  //f_EGE->SetParLimits(2, 0.1, 15);
  //f_EGE->SetParLimits(3, 0.1, 15);

  href->Fit("ExpGausExp", "R");
  double norm_ref=f_EGE->GetParameter(4);
  double chi2=f_EGE->GetChisquare();
  double ndf=f_EGE->GetNDF();

  hsys->GetXaxis()->SetRangeUser(0.8*xmin,1.2*xmax);
  hsys->Fit("ExpGausExp", "R");
  double norm_sys=f_EGE->GetParameter(4);
  
  std::cout<<"chi2/ndf="<<chi2<<"/"<<ndf<<"; norm_ref="<<norm_ref<<"; norm_JER="<<norm_sys<<"; variation_rel="<<(norm_ref-norm_sys)/norm_ref*100.<<std::endl;

  return 0;

}
