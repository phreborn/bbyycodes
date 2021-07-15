#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"

using namespace std;
using namespace CommonFunc;
using namespace RooStats;

double const epsilon = 1e-4;
double const start_point=500;
double const end_point=3000;

int const npoints = 21;
  
double mass[npoints];

void fillMass(){
  vector<int> temp;
  for(int Mass=500;Mass<2000;Mass+=100) temp.push_back(Mass);
  for(int Mass=2000;Mass<=3000;Mass+=200) temp.push_back(Mass);
  for( int b = 0 ; b < npoints ; b ++  ) mass[b]= temp[b];
}

// Remember to change input format in this function
pair<double, double> readInput(TString inputDir, double array[npoints]){
  double minmH=-1, minp0=1;
  ofstream fout(inputDir+"/summary.txt");
  fout<<"Mass [GeV] \t NLLfix \t NLLhat \t muhat \t pvalue \t sig "<<endl;
  for(int i=0;i<npoints;i++){
    double Mass=mass[i];
    TString inputFilefix=inputDir+Form("/%.0f_mufix.root",Mass);
    TString inputFilehat=inputDir+Form("/%.0f_muhat.root",Mass);

    double nllfix, nllhat, muhat;
    int statusfix, statushat;

    array[i]=0.5;
    
    unique_ptr<TChain> cfix(new TChain("toys/nllscan"));
    if(!cfix->AddFile(inputFilefix,-1)){
      cerr<<"WARNING: file "<<inputFilefix<<" does not exist...Press any key to continue"<<endl;
      continue;
    }
    cfix->SetBranchAddress("nll",&nllfix);
    cfix->SetBranchAddress("status",&statusfix);
    cfix->GetEntry(0);
    unique_ptr<TChain> chat(new TChain("toys/nllscan"));
    if(!chat->AddFile(inputFilehat,-1)){
      cerr<<"WARNING: file "<<inputFilefix<<" does not exist...Press any key to continue"<<endl;
      continue;
    }
    chat->SetBranchAddress("nll",&nllhat);
    chat->SetBranchAddress("mu",&muhat);
    chat->SetBranchAddress("status",&statushat);
    chat->GetEntry(0);

    double DNLL=2*(nllfix-nllhat);
    if(DNLL<0&&fabs(DNLL)<4e-3) DNLL=0;
    
    double pvalue=1;
    if(muhat<0) pvalue=ROOT::Math::normal_cdf(sqrt(DNLL),1,0);
    else pvalue=1-ROOT::Math::normal_cdf(sqrt(DNLL),1,0);
    if(!isfinite(pvalue)||statusfix>1||statushat>1){
      cerr<<"WARNING: fit "<<inputFilefix<<" at "<<Mass<<" is not converging. p-value="<<pvalue
	  <<", DNLL="<<DNLL
	  <<", muhat="<<muhat
	  <<", status hat="<<statushat
	  <<", status fix="<<statusfix
	  <<"...Press any key to continue"<<endl;
      // getchar();
      pvalue=0.5;
    }
    array[i]=pvalue;
    fout<<Form("%.1f \t %.2f \t %.2f \t %.2f \t %.2e \t %.1f", Mass, nllfix, nllhat, muhat, pvalue, RooStats::PValueToSignificance(pvalue))<<endl;
    if(pvalue<minp0){
      minp0=pvalue;
      minmH=Mass;
    }
  }
  pair<double, double> output;
  output.first=minmH;
  output.second=RooStats::PValueToSignificance(minp0);
  fout<<"Max: "<<minp0<<" at "<<minmH<<" GeV"<<endl;
  fout.close();
  return output;
}

int main(int argc, char** argv) 
{
  SetAtlasStyle();
  fillMass();
  int Max = npoints;
  float  mu120[Max] ;
  float median120[Max];
  float  left120[Max];
  float  right120[Max];
  float  mu130[Max] ;
  float  median130[Max];
  float  left130[Max];
  float  right130[Max];
  float  mu140[Max] ;
  float  median140[Max];
  float  left140[Max];
  float  right140[Max];
  float cl95[Max] ;

  float datam ;
  float datal ;
  float datar ;

  int i = 0 ;

  TCanvas* c1 = new TCanvas("c1","CL_{s+b}%",0,0,800,600);
  c1->SetTickx(1);
  c1->SetTicky(1);
  //c1 -> SetLogy();
  c1 -> SetFillColor(0) ;

  Int_t ax=npoints;

  double median[npoints] ;//  = { 23.5, 22.0, 21.1, 22.1, 26.5};
  double mediancls[npoints] ;//  = { 23.5, 22.0, 21.1, 22.1, 26.5};
  double OneSigma_plus[npoints];//  = { 13.7, 12.8, 11.7, 12.4, 14.6 };
  double OneSigma_minus[npoints] ;//= { 37.4, 34.9, 33.1, 34.5, 44.5 }  ; 
  double TwoSigma_plus[npoints]  ;//= { 7.7, 7.4, 6.8, 6.7, 6.3 };
  double TwoSigma_minus[npoints] ;//= { 49.9 , 49.0, 47.2, 49.8 , 64.3 };
  double data[npoints], exp[npoints];//= { 22.2 , 42.5 , 30.8 , 14.7 , 13.2  };
  double datacls[npoints] ;//= { 22.2 , 42.5 , 30.8 , 14.7 , 13.2  };
  double data2[npoints],exp2[npoints];
  double data3[npoints],exp3[npoints];

  pair<double, double> maxdata=readInput("pvalue/qqqq_RSG_WW_20160126",data);
  double Z = maxdata.second;
  double M_minimum = maxdata.first;

  pair<double, double> maxdata2=readInput("pvalue/lvqq_RSG_WW_20160126",data2);
  double Z2 = maxdata2.second;
  double M2_minimum = maxdata2.first;

  pair<double, double> maxdata3=readInput("pvalue/combined_VV_RSG_WW_20160126",data3);
  double Z3 = maxdata3.second;
  double M3_minimum = maxdata3.first;

  double zero[npoints] = {0.};
  // double SM[npoints] = {1.,1.,1.};

  //  double d0e[npoints] = {17.5,18.3 ,21.7 };
  TGraph* g_med=new TGraph(npoints,mass,exp);
  g_med->SetLineColor(1);
  g_med->SetLineWidth(2);
  g_med->SetLineStyle(2);

  TGraph* g_data=new TGraph(ax,mass,data);
  g_data->SetLineWidth(2);
  g_data->GetXaxis()->SetTitle("m_{G*} [GeV]");
  g_data->GetXaxis()->SetTitleSize(0.06);
  g_data->GetYaxis()->SetTitle("Local #it{p}_{0}");
  g_data->GetYaxis()->SetTitleSize(0.06);
  g_data->GetXaxis()->SetLimits(start_point-0.5,end_point+0.5);
  g_data->SetMaximum(1e1);
  g_data->SetMinimum(1.0e-4);
  
  g_data -> SetLineStyle(1);
  g_data -> SetLineColor(2);
  g_data -> SetLineWidth(2);
  g_data -> SetMarkerSize(4);
  g_data -> SetMarkerStyle(1);

  g_data -> Draw("al");
  // g_med->Draw("l");

  TGraph* g_data2=new TGraph(ax,mass,data2);
  g_data2->SetLineWidth(2);
  g_data2->SetLineColor(kOrange+1);
  g_data2->SetLineStyle(1);
  g_data2 -> Draw("l");

  TGraph* g_data3=new TGraph(ax,mass,data3);
  g_data3->SetLineWidth(2);
  g_data3->SetLineColor(4);
  g_data3->SetLineStyle(1);
  g_data3 -> Draw("l");

  TLegend *leg=FastLegend(0.20,0.76,0.45,0.93,0.05);

  leg->AddEntry(g_data,"qqqq","L");
  leg->AddEntry(g_data2,"lvqq","L");
  leg->AddEntry(g_data3,"Combined","L");

  leg->Draw();


  TLegend leg2(0.20,0.175,0.405,0.38);
  leg2.SetLineColor(0);
  leg2.SetFillStyle(0);
  leg2.SetShadowColor(0);
  leg2.SetTextSize(0.04);
  leg2.SetBorderSize(0);

  leg2.SetFillColor(0);
  // leg2.Draw();


  TLatex l; //l.SetTextAlign(12); l.SetTextSize(tsize);
  l.SetNDC();
  l.SetTextColor(1);
  l.SetTextSize(0.045);

  l.SetTextSize(0.06);

  TLatex la; //l.SetTextAlign(12); l.SetTextSize(tsize);
  la.SetNDC();
  la.SetTextFont(72);
  la.SetTextColor(1);

  TLatex lp;
  lp.SetNDC();
  lp.SetTextFont(42);
  lp.SetTextColor(1);

  la.DrawLatex(0.60,0.88,"ATLAS");
  lp.DrawLatex(0.74,0.88,"Internal");
  lp.DrawLatex(0.60,0.82,"#sqrt{#it{s}} = 13 TeV, 3.2 fb^{-1}");
  // lp.DrawLatex(0.60,0.76,"#sqrt{#it{s}} = 8 TeV, 20.3 fb^{-1}");

  lp.SetTextColor(2);
  char sig_print[20];
  sprintf (sig_print, "Z_{max} = %4.1f #sigma", Z);
  //lp.DrawLatex(0.22,0.215,sig_print);

  char mH_print[20];
  sprintf (mH_print, "m_{H} = %4.1f GeV", M_minimum);
  //lp.DrawLatex(0.22,0.170,mH_print);


  TLine * l1=new TLine( start_point , SignificanceToPValue(1),end_point, SignificanceToPValue(1)); 
  l1 -> SetLineWidth(2);
  l1 -> SetLineColor(kGreen+1);
  l1 -> SetLineStyle(5);
  l1->Draw("same");

  TLatex l1sigma;
  l1sigma.SetTextFont(42);
  l1sigma.DrawLatex(end_point+0.55,0.1,"1#sigma");

  TLine * l2=new TLine( start_point , SignificanceToPValue(2), end_point, SignificanceToPValue(2)); 
  l2 -> SetLineWidth(2);
  l2 -> SetLineColor(kGreen+1);
  l2 -> SetLineStyle(5);
  l2->Draw("same");

  TLatex l2sigma;
  l2sigma.SetTextFont(42);
  l2sigma.DrawLatex(end_point+0.55,0.013,"2#sigma");

  TLine * l3=new TLine( start_point ,SignificanceToPValue(3), end_point,SignificanceToPValue(3)); 
  l3 -> SetLineWidth(2);
  l3 -> SetLineColor(kGreen+1);
  l3 -> SetLineStyle(5);
  l3->Draw("same");

  TLatex l3sigma;
  l3sigma.SetTextFont(42);
  l3sigma.DrawLatex(end_point+0.55,9e-4,"3#sigma");

  g_data -> Draw("l");
  // g_med->Draw("l");

  c1->SetLogy();
  c1->RedrawAxis();

  system("mkdir -vp fig/plot_p0/combined_VV_RSG_WW/");
  PrintCanvas(c1,"fig/plot_p0/combined_VV_RSG_WW/pvalue");
  // c1->SaveAs("clbin2GeVlimit_finer_binning.C");

  cout<<"WZ: "<<maxdata.second<<" sigma at "<<maxdata.first<<" GeV"<<endl;
  cout<<"WW: "<<maxdata2.second<<" sigma at "<<maxdata2.first<<" GeV"<<endl;
  cout<<"WZ+WW: "<<maxdata3.second<<" sigma at "<<maxdata3.first<<" GeV"<<endl;

  return 0;


}
