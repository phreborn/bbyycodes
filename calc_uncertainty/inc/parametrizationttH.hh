/////////////////////////////////////////
//                                     //
//  Author: Fuquan Wang                //
//  Modified: Andrew Hard              //
//  Date: 25/6/2012                    //
//                                     //
//  Used by:                           //
//    Fitting.cc                       //
/////////////////////////////////////////

#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "statistics.hh"

using namespace std;
using namespace RooFit;
using namespace CommonFunc;

// Only put stable functions which are not likely to be modified here

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
////////// OutputProcess:

void OutputProcess( TString outDir, int cat_number, int mass, double ggf_w, double vbf_w, double wh_w, double zh_w, double tth_w, double thjb_w, double wth_w, double mu, double sigma, double alphaLo, double nLo, double alphaHi, double nHi )
{
  ofstream outfile;
  double truthmass=double(mass)/10.;
  outfile.open(Form("%s/ggf/ggf_cate_fit_%d_%d.txt",outDir.Data(),mass,cat_number),ios::out);
  outfile<<truthmass<<"\t"<<ggf_w<<"\t"<<mu<<"\t"<<sigma<<"\t"<<alphaLo<<"\t"<<nLo<<"\t"<<alphaHi<<"\t"<<nHi<<endl;
  outfile.close();
  
  outfile.open(Form("%s/vbf/vbf_cate_fit_%d_%d.txt",outDir.Data(),mass,cat_number),ios::out);
  outfile<<truthmass<<"\t"<<vbf_w<<"\t"<<mu<<"\t"<<sigma<<"\t"<<alphaLo<<"\t"<<nLo<<"\t"<<alphaHi<<"\t"<<nHi<<endl;
  outfile.close();
  
  outfile.open(Form("%s/wh/wh_cate_fit_%d_%d.txt",outDir.Data(),mass,cat_number),ios::out);
  outfile<<truthmass<<"\t"<<wh_w<<"\t"<<mu<<"\t"<<sigma<<"\t"<<alphaLo<<"\t"<<nLo<<"\t"<<alphaHi<<"\t"<<nHi<<endl;
  outfile.close();
  
  outfile.open(Form("%s/zh/zh_cate_fit_%d_%d.txt",outDir.Data(),mass,cat_number),ios::out);
  outfile<<truthmass<<"\t"<<zh_w<<"\t"<<mu<<"\t"<<sigma<<"\t"<<alphaLo<<"\t"<<nLo<<"\t"<<alphaHi<<"\t"<<nHi<<endl;
  outfile.close();

  outfile.open(Form("%s/tth/tth_cate_fit_%d_%d.txt",outDir.Data(),mass,cat_number),ios::out);
  outfile<<truthmass<<"\t"<<tth_w<<"\t"<<mu<<"\t"<<sigma<<"\t"<<alphaLo<<"\t"<<nLo<<"\t"<<alphaHi<<"\t"<<nHi<<endl;
  outfile.close();

  outfile.open(Form("%s/thjb/thjb_cate_fit_%d_%d.txt",outDir.Data(),mass,cat_number),ios::out);
  outfile<<truthmass<<"\t"<<thjb_w<<"\t"<<mu<<"\t"<<sigma<<"\t"<<alphaLo<<"\t"<<nLo<<"\t"<<alphaHi<<"\t"<<nHi<<endl;
  outfile.close();

  outfile.open(Form("%s/wth/wth_cate_fit_%d_%d.txt",outDir.Data(),mass,cat_number),ios::out);
  outfile<<truthmass<<"\t"<<wth_w<<"\t"<<mu<<"\t"<<sigma<<"\t"<<alphaLo<<"\t"<<nLo<<"\t"<<alphaHi<<"\t"<<nHi<<endl;
  outfile.close();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
////////// PrintMassCate:

void PrintMassCate(Int_t mass, TString channelname, Color_t color=kBlack,Double_t x = 0.2,Double_t y = 0.85) 
{
  TLatex l;
  l.SetNDC();
  l.SetTextFont(42);
  l.SetTextColor(color);
  l.DrawLatex(x,y,Form("m_{H}=%dGeV %s", mass, channelname.Data()));
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
////////// GetYield:

double GetYield( double mass, double p0, double p1, double p2, double p3 )
{
  double result = p0 + (p1*mass) + (p2*mass*mass) + (p3*mass*mass*mass);
  return result;
}

void InterpolateSignal( int cat_number, TString directory )
{
  //--------------------------------------//
  // Open files to get inclusive parameters:
  // parameterized from -25 to 25, not 100-150;
  ifstream infile;
  infile.open(Form("%s/param_%d.txt",directory.Data(),cat_number),ios::in);
  double null, a_mu, b_mu, a_sigma, b_sigma, alpha, n, k_ga, frac;
  infile>>null>>a_mu>>b_mu>>a_sigma>>b_sigma>>alpha>>n>>k_ga>>frac;
  infile.close();
  
  ifstream yield_file;
  yield_file.open(Form("%s/all/yield_%d.txt",directory.Data(),cat_number),ios::in);
  double p0, p1, p2, p3;
  yield_file>>null>>p0>>p1>>p2>>p3;
  yield_file.close();
  //--------------------------------------//
  // Inputs per process:
  ifstream ggf_yield_file;
  ggf_yield_file.open(Form("%s/ggf/ggf_yield_%d.txt",directory.Data(),cat_number),ios::in);
  cout<<Form("%s/ggf/ggf_yield_%d.txt",directory.Data(),cat_number)<<endl;
  assert(ggf_yield_file);
  double ggf_p0, ggf_p1, ggf_p2, ggf_p3;
  ggf_yield_file>>null>>ggf_p0>>ggf_p1>>ggf_p2>>ggf_p3;
  ggf_yield_file.close();

  ifstream vbf_yield_file;
  vbf_yield_file.open(Form("%s/vbf/vbf_yield_%d.txt",directory.Data(),cat_number),ios::in);
  assert(vbf_yield_file);
  double vbf_p0, vbf_p1, vbf_p2, vbf_p3;
  vbf_yield_file>>null>>vbf_p0>>vbf_p1>>vbf_p2>>vbf_p3;
  vbf_yield_file.close();
  
  ifstream tth_yield_file;
  tth_yield_file.open(Form("%s/tth/tth_yield_%d.txt",directory.Data(),cat_number),ios::in);
  assert(tth_yield_file);
  double tth_p0, tth_p1, tth_p2, tth_p3;
  tth_yield_file>>null>>tth_p0>>tth_p1>>tth_p2>>tth_p3;
  tth_yield_file.close();

  ifstream wh_yield_file;
  wh_yield_file.open(Form("%s/wh/wh_yield_%d.txt",directory.Data(),cat_number),ios::in);
  assert(wh_yield_file);
  double wh_p0, wh_p1, wh_p2, wh_p3;
  wh_yield_file>>null>>wh_p0>>wh_p1>>wh_p2>>wh_p3;
  wh_yield_file.close();
  
  ifstream zh_yield_file;
  zh_yield_file.open(Form("%s/zh/zh_yield_%d.txt",directory.Data(),cat_number),ios::in);
  assert(zh_yield_file);
  double zh_p0, zh_p1, zh_p2, zh_p3;
  zh_yield_file>>null>>zh_p0>>zh_p1>>zh_p2>>zh_p3;
  zh_yield_file.close();
  
  // ofstream outfile;
  // ofstream ggf_outfile;
  // ofstream vbf_outfile;
  // ofstream tth_outfile;
  // ofstream wh_outfile;
  // ofstream zh_outfile;
  
  // //--------------------------------------//
  // // Interpolate for masses in steps of 0.5:
  // for( float mass = 100; mass < 150.5; mass += 0.5 )
  // {
  //   int mass_print = (int)(10*mass);
  //   double mass_fit = mass - 125.0;
  //   double mu_print = mass + a_mu + (b_mu * mass_fit);
  //   double sigma_print = a_sigma + (b_sigma * mass_fit);
  //   if( mass != (int)mass )
  //   {
  //     outfile.open(Form("%s/all/cate_fit_%i_%i.txt",directory.Data(),mass_print,cat_number),ios::out);
  //     outfile<<mass<<"\t"<<GetYield(mass,p0,p1,p2,p3)<<"\t"<<mu_print<<"\t"<<sigma_print<<"\t"<<alpha<<"\t"<<n<<"\t"<<mu_print<<"\t"<<k_ga*(sigma_print)<<"\t"<<frac<<endl;
  //     outfile.close();
      
  //     ggf_outfile.open(Form("%s/ggf/ggf_cate_fit_%i_%i.txt",directory.Data(),mass_print,cat_number),ios::out);
  //     ggf_outfile<<mass<<"\t"<<GetYield(mass,ggf_p0,ggf_p1,ggf_p2,ggf_p3)<<"\t"<<mu_print<<"\t"<<sigma_print<<"\t"<<alpha<<"\t"<<n<<"\t"<<mu_print<<"\t"<<k_ga*(sigma_print)<<"\t"<<frac<<endl;
  //     ggf_outfile.close();
      
  //     vbf_outfile.open(Form("%s/vbf/vbf_cate_fit_%i_%i.txt",directory.Data(),mass_print,cat_number),ios::out);
  //     vbf_outfile<<mass<<"\t"<<GetYield(mass,vbf_p0,vbf_p1,vbf_p2,vbf_p3)<<"\t"<<mu_print<<"\t"<<sigma_print<<"\t"<<alpha<<"\t"<<n<<"\t"<<mu_print<<"\t"<<k_ga*(sigma_print)<<"\t"<<frac<<endl;
  //     vbf_outfile.close();
      
  //     tth_outfile.open(Form("%s/tth/tth_cate_fit_%i_%i.txt",directory.Data(),mass_print,cat_number),ios::out);
  //     tth_outfile<<mass<<"\t"<<GetYield(mass,tth_p0,tth_p1,tth_p2,tth_p3)<<"\t"<<mu_print<<"\t"<<sigma_print<<"\t"<<alpha<<"\t"<<n<<"\t"<<mu_print<<"\t"<<k_ga*(sigma_print)<<"\t"<<frac<<endl;
  //     tth_outfile.close();
      
  //     wh_outfile.open(Form("%s/wh/wh_cate_fit_%i_%i.txt",directory.Data(),mass_print,cat_number),ios::out);
  //     wh_outfile<<mass<<"\t"<<GetYield(mass,wh_p0,wh_p1,wh_p2,wh_p3)<<"\t"<<mu_print<<"\t"<<sigma_print<<"\t"<<alpha<<"\t"<<n<<"\t"<<mu_print<<"\t"<<k_ga*(sigma_print)<<"\t"<<frac<<endl;
  //     wh_outfile.close();
      
  //     zh_outfile.open(Form("%s/zh/zh_cate_fit_%i_%i.txt",directory.Data(),mass_print,cat_number),ios::out);
  //     zh_outfile<<mass<<"\t"<<GetYield(mass,zh_p0,zh_p1,zh_p2,zh_p3)<<"\t"<<mu_print<<"\t"<<sigma_print<<"\t"<<alpha<<"\t"<<n<<"\t"<<mu_print<<"\t"<<k_ga*(sigma_print)<<"\t"<<frac<<endl;
  //     zh_outfile.close();
  //   }
  //   else
  //   {
  //     outfile.open(Form("%s/all/cate_fit_%i_%i.txt",directory.Data(),mass_print,cat_number),ios::out);
  //     outfile<<mass<<"\t"<<GetYield(mass,p0,p1,p2,p3)<<"\t"<<mu_print<<"\t"<<sigma_print<<"\t"<<alpha<<"\t"<<n<<"\t"<<mu_print<<"\t"<<k_ga*(sigma_print)<<"\t"<<frac<<endl;
  //     outfile.close();
      
  //     ggf_outfile.open(Form("%s/ggf/ggf_cate_fit_%i_%i.txt",directory.Data(),mass_print,cat_number),ios::out);
  //     ggf_outfile<<mass<<"\t"<<GetYield(mass,ggf_p0,ggf_p1,ggf_p2,ggf_p3)<<"\t"<<mu_print<<"\t"<<sigma_print<<"\t"<<alpha<<"\t"<<n<<"\t"<<mu_print<<"\t"<<k_ga*(sigma_print)<<"\t"<<frac<<endl;
  //     ggf_outfile.close();
      
  //     vbf_outfile.open(Form("%s/vbf/vbf_cate_fit_%i_%i.txt",directory.Data(),mass_print,cat_number),ios::out);
  //     vbf_outfile<<mass<<"\t"<<GetYield(mass,vbf_p0,vbf_p1,vbf_p2,vbf_p3)<<"\t"<<mu_print<<"\t"<<sigma_print<<"\t"<<alpha<<"\t"<<n<<"\t"<<mu_print<<"\t"<<k_ga*(sigma_print)<<"\t"<<frac<<endl;
  //     vbf_outfile.close();
      
  //     tth_outfile.open(Form("%s/tth/tth_cate_fit_%i_%i.txt",directory.Data(),mass_print,cat_number),ios::out);
  //     tth_outfile<<mass<<"\t"<<GetYield(mass,tth_p0,tth_p1,tth_p2,tth_p3)<<"\t"<<mu_print<<"\t"<<sigma_print<<"\t"<<alpha<<"\t"<<n<<"\t"<<mu_print<<"\t"<<k_ga*(sigma_print)<<"\t"<<frac<<endl;
  //     tth_outfile.close();
      
  //     wh_outfile.open(Form("%s/wh/wh_cate_fit_%i_%i.txt",directory.Data(),mass_print,cat_number),ios::out);
  //     wh_outfile<<mass<<"\t"<<GetYield(mass,wh_p0,wh_p1,wh_p2,wh_p3)<<"\t"<<mu_print<<"\t"<<sigma_print<<"\t"<<alpha<<"\t"<<n<<"\t"<<mu_print<<"\t"<<k_ga*(sigma_print)<<"\t"<<frac<<endl;
  //     wh_outfile.close();
      
  //     zh_outfile.open(Form("%s/zh/zh_cate_fit_%i_%i.txt",directory.Data(),mass_print,cat_number),ios::out);
  //     zh_outfile<<mass<<"\t"<<GetYield(mass,zh_p0,zh_p1,zh_p2,zh_p3)<<"\t"<<mu_print<<"\t"<<sigma_print<<"\t"<<alpha<<"\t"<<n<<"\t"<<mu_print<<"\t"<<k_ga*(sigma_print)<<"\t"<<frac<<endl;
  //     zh_outfile.close();
  //   }
  // }
  // outfile.close();
  // ggf_outfile.close();
  // vbf_outfile.close();
  // tth_outfile.close();
  // wh_outfile.close();
  // zh_outfile.close();
}


bool PassMassWin(double mass){
  // mass should be in GeV.
  // narrow: 105-160 GeV. normal: 100-160 GeV. Usually it is narrow
  double mwin_low=105, mwin_high=160;
  if(mass<mwin_low||mass>mwin_high) return false;
  else return true;
}
