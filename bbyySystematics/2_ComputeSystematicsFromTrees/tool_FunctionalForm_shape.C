#ifndef TOOL_FUNCTIONALFORM_SHAPE_C
#define TOOL_FUNCTIONALFORM_SHAPE_C

//to move in another tool_functional_shape
//from HGamTool/HggTwoSidedCBPdf

Double_t DoubleCrystalBall(Double_t*x,Double_t*par)
{
  double a,b;
  double_t t=(x[0]-par[0])/par[1];
  
  //par[0]=mean CB
  //par[1]=sigma CB
  //par[2]=alpha_Low
  //par[3]=n_Low
  //par[4]=alpha_High
  //par[5]=n_High
  //par[6]=normalization
  
  //from HggTwoSidedCBPdf
  
  if (t<-par[2]) {
    a=exp(-0.5*par[2]*par[2]);
    b=par[3]/par[2]-par[2];
    return par[6]*a/pow(par[2]/par[3] * (b-t),par[3]);
  }
  else if (t>par[4]) {
    a=exp(-0.5*par[4]*par[4]);
    b=par[5]/par[4]-par[4];
    return par[6]*a/pow(par[4]/par[5] * (b+t),par[5]);
  }

  return par[6]*exp(-0.5*t*t);
  
  //to investigate the potential correlation between yields and shape parameters
  //divide by intgral ?
}

/*
  double cristall(double *x,double *par)
  {
  double A,B,C,D,N;
  double result=0;
  
  //par[0]=mean CB
  //par[1]=

  //par[2]=alpha
  //par[3]=nCB

  A=pow(par[3]/abs(par[2]),par[3])*exp(-pow(abs(par[2]),2)/2);

  //big bug!!
  B=par[3]/abs(par[2])-abs(par[2]);
  C=(par[3]*exp(-pow(abs(par[2]),2)/2))/(abs(par[2])*(par[3]-1));
  D=sqrt(3.14159265/2.)*(1+erf(abs(par[2])/sqrt(2)));
  N=1/(par[1]*(C+D));
  
  if((x[0]-par[0])<=-par[2]*par[1]){
  result=A*pow((B-(x[0]-par[0])/par[1]),-par[3]);    
  }
  else {
  //    if((x[0]-par[0])>-par[2]*par[1]){
  result=exp(-(x[0]-par[0])*(x[0]-par[0])/(2*par[1]*par[1]));
  }
  
  //  return N*result;
  return par[4]*result;
  }
*/

double exponentialIntegral(double tmin, double tmax, double k)
{
  return (TMath::Exp(0.5 * k * k + k * tmax) - TMath::Exp(0.5 * k * k + k * tmin)) / k;
}

double gaussianIntegral(double tmin, double tmax)
{
  return sqrt(TMath::TwoPi()) * (ROOT::Math::gaussian_cdf(tmax) - ROOT::Math::gaussian_cdf(tmin));
}

Double_t ExpGausExp(Double_t *x, Double_t *par)
{
  Double_t std=(x[0]-par[0])/par[1];
  Double_t result=0;

  //par[0]=mean Gauss
  //par[1]=sigma Gauss
  //par[2]=kHi
  //par[3]=kLo
  //par[4]=normalization
  
  if (std>par[2])
    result=exp(par[2]*par[2]/2.-par[2]*std);
  else if (std<=par[2] && std>-par[3])
    result=exp(-0.5*std*std);
  else if (std<=-par[3])
    result=exp(par[3]*par[3]/2.+par[3]*std);
  
  //   cout << "TMath::Exp(-par[2]*par[2]/2.)/par[2] + TMath::Exp(-par[3]*par[3]/2.)/par[3]=" << TMath::Exp(-par[2]*par[2]/2.)/par[2] + TMath::Exp(-par[3]*par[3]/2.)/par[3] << endl;
  
  double sig=par[1];
  
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
  //---------------------
  
  //classical normalization
  return result*par[4];
  //would be (?) instable: high variation with range, due to correlations
  
  //variante
  // / par[1]) / (sqrt(2*3.1415927))
  
  //version a la Francesco Costanza, that would be stable with no correlations of parameters
  //expressed in units of sigma, just to be stable for changes of yields with luminosity
  //   return (result * par[4] / par[1]) / 
    
  //     //expressed in absolute value
  //     //	  return (result * par[4] ) / 
  //     (
  //      //integral of gaussian term
  //      sqrt(2*3.1415927) * (TMath::Erf(sqrt(0.5)*par[2]) + TMath::Erf(sqrt(0.5)*par[3]))/2.
  //      +
  
  //      //integral of exponential terms
  //      (
  //       TMath::Exp(-par[2]*par[2]/2.)/par[2] + TMath::Exp(-par[3]*par[3]/2.)/par[3]
  //       )
  //      );
  //remark: result / [ integral...] is the normalized pdf
}

#endif
