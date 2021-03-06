#ifndef _CommonFunc_h_
#define _CommonFunc_h_
#include "CommonHead.h"
//#include "RooFitHead.h"

//using namespace RooFit;

namespace CommonFunc{
  TH1F* CreateHist(TString title="hist",TString tag="",TString axisx="",TString axisy="",int nbin=100,double xmin=0,double xmax=100,double min=0);
  TH1D* CreateTH1D(TString title="hist",TString tag="",TString axisx="",TString axisy="",int nbin=100,double xmin=0,double xmax=100,double min=0);
  TCanvas* CreateCanvas(TString title="canvas",TString tag="",int ww=800,int wh=600);
  TPad* CreatePad(TString title="pad",TString tag="",double x1=0,double y1=0.,double x2=1,double y2=1);
  THStack* CreateStack(TString title="stack",TString tag="");
  TFile* OpenFile(TString fileName="",TString option="read");
  void PrintCanvas(TCanvas* c, TString name);
  bool IsNaN(double var);
  bool IsEven(int num);
  bool IsOdd(int num);
  void GetX1Y1X2Y2(TVirtualPad *c,double x[4]);
  void GetX1Y1X2Y2(TVirtualPad *c,double &x1,double &y1,double &x2,double &y2);
  TLegend* CreateLegend(double x_low, double y_low, double x_up, double y_up, TList* h_list, std::vector<TString> text, std::vector<TString> option,double textsize);
  TLegend* FastLegend(double x_low, double y_low, double x_up, double y_up,double textsize);
  void DrawConstantLine(TVirtualPad *c, double value,double *mass,int nmass,Color_t color=2, int linestyle=2, double linewidth=3);
  TLine* DrawConstantLine(TVirtualPad *c, double value, double x1, double x2 ,Color_t color=2, int linestyle=2, double linewidth=3);
  TLine* DrawVerticalLine(TVirtualPad *c, double value, double y1, double y2 ,Color_t color=2, int linestyle=2, double linewidth=3);
  TPaveText* CreatePaveText(double x1,double y1,double x2,double y2,std::vector<TString> text,double textsize);
  TStyle* AtlasStyle();
  void SetAtlasStyle();
  void ScaleToOne(TH1*, bool m_width=false, bool m_flow=false);
  void ScaleTo(TH1*, double, bool m_width=false, bool m_flow=false);
  void SetAllHistColor(TH1*, Color_t);
  std::vector<TString> SplitString(const TString& theOpt, const char separator );
  double Cone(double,double,double,double);
  double Cone(TLorentzVector, TLorentzVector);
  double DiffPhi(double,double);
  double DiffPhi(double);
  void Report(const char* ,const char*);
  TChain* MakeChain(const char*, TString, TString, bool isroot=false);
  bool descending_on_Pt(TLorentzVector, TLorentzVector);
  int FindBin(TH1 *h, double lowedge);
  TH1F* TH1DtoTH1F(TH1D *hd);
  TH1D* TH1FtoTH1D(TH1F *hf);
  TH1D* ExpandTH1D(TH1D *hold, double xmin_new, double xmax_new);
  int sign(double x);
  Color_t ColorWheel(int idx);
  Int_t MarkerWheel(int idx);
/*   bool descending(int i, int j); */
  bool descending(double i, double j);
  //TTree* GetTree(RooDataSet*);
  void CopyFileContent(TFile *input, TFile* target);
  TH1D *VectorToHist(std::vector<double> vec, TString name, double xmin, double xmax, int nbin);
  double CostsCS(TLorentzVector v1, TLorentzVector v2);
  
  const double GeV=1e3;
};


#endif
