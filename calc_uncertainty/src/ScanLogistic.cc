#include "CommonHead.h"

using namespace std;

double logistic(double mean, double width, double _alpha, double _nu, double _sigma){
  return 1/pow(1+exp(-(x-(mean-_alpha*width))/(_sigma*width)),_nu);
}

int main(int argc, char**argv){
  double mean=1500, width=0.15*mean;
  
}
