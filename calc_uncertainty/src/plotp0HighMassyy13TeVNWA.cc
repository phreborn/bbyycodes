#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"

using namespace std;
using namespace CommonFunc;
using namespace RooStats;

double const epsilon = 1e-4;
double const start_point=200;
double const end_point=1700;
double const stepsize=5;
int const npoints = int((end_point-start_point+epsilon)/stepsize);

// Remember to change input format in this function
pair<double, double> readInput(TString inputDir, double array[npoints]){
  double minmH=-1, minp0=1;
  ofstream fout(inputDir+"/summary.txt");
  fout<<"Mass [GeV] \t NLLfix \t NLLhat \t muhat \t pvalue \t sig "<<endl;
  for(int i=0;i<npoints;i++){
    double mass=start_point+i*stepsize;
    TString inputFilefix=inputDir+Form("/mX_%.2f_mufix.root",mass);
    TString inputFilehat=inputDir+Form("/mX_%.2f_muhat.root",mass);

    double nllfix, nllhat, muhat;
    TChain *cfix=new TChain("toys/nllscan");
    cfix->Add(inputFilefix);
    cfix->SetBranchAddress("nll",&nllfix);
    cfix->GetEntry(0);
    TChain *chat=new TChain("toys/nllscan");
    chat->Add(inputFilehat);
    chat->SetBranchAddress("nll",&nllhat);
    chat->SetBranchAddress("mu",&muhat);
    chat->GetEntry(0);

    double DNLL=2*(nllfix-nllhat);
    double pvalue=1;
    if(muhat<0) pvalue=0.5;
    else pvalue=1-ROOT::Math::normal_cdf(sqrt(DNLL),1,0);
    if(!isfinite(pvalue)) pvalue=0.5;
    array[i]=pvalue;
    fout<<Form("%.1f \t %.2f \t %.2f \t %.2f \t %.2e \t %.1f", mass, nllfix, nllhat, muhat, pvalue, RooStats::PValueToSignificance(pvalue))<<endl;
    if(pvalue<minp0){
      minp0=pvalue;
      minmH=mass;
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
  double mass[npoints];
  for( int b = 0 ; b < npoints ; b ++  )
    {

      mass[b]= start_point+b*stepsize;

    }

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

  pair<double, double> maxdata=readInput("pvalue/high_mass_diphoton_EOYE/",data);
  double Z = maxdata.second;
  double M_minimum = maxdata.first;

  ofstream myfile;
  myfile.open ("./notep0obs.txt");
  myfile.setf(ios::showpoint) ;
  myfile.setf(ios::fixed) ;
  myfile.precision(3) ;
  ofstream myfile2;
  myfile2.open ("./notep0exp.txt");
  myfile2.setf(ios::showpoint) ;
  myfile2.setf(ios::fixed) ;
  myfile2.precision(3) ;



  for ( int i = 0 ; i < npoints ; i ++ )
    {
      myfile << " & " << exp[i] ;
      myfile2 << " & " << data[i] ;
      if(mass[i] == 119 || mass[i] == 129 || mass[i] == 139)
        {
          myfile << endl;
          myfile2 << endl;
        }

    }

  double zero[npoints] = {0.};
  // double SM[npoints] = {1.,1.,1.};

  //  double d0e[npoints] = {17.5,18.3 ,21.7 };
  TGraph* g_med=new TGraph(npoints,mass,exp);
  g_med->SetLineColor(1);
  g_med->SetLineWidth(3);
  g_med->SetLineStyle(2);

  TGraph* g_data=new TGraph(ax,mass,data);
  g_data->SetLineWidth(3);


  TGraph* g_2=new TGraphAsymmErrors(ax,mass,median,zero,zero,TwoSigma_plus,TwoSigma_minus);
  g_2->SetFillColor(5);
  g_2->SetLineColor(5);
  g_2->SetLineStyle(2);
  g_data->GetXaxis()->SetTitle("m_{X} [GeV]");
  //g_data -> SetTitle(" Exclusion at 95% CL_{s+b}, 7TeV, 37pb^{-1}");
  g_data->GetYaxis()->SetTitle("Local #it{p}_{0}");
  g_data->GetXaxis()->SetLimits(start_point-0.5,end_point+0.5);
  TGraph* g_1=new TGraphAsymmErrors(ax,mass,median,zero,zero,OneSigma_plus,OneSigma_minus);
  g_1->SetFillColor(3);
  g_1->SetLineColor(3);
  g_1->SetLineStyle(2);
  //g_data->SetMaximum(35.);
  g_data->SetMaximum(1e1);
  g_data->SetMinimum(1.0e-4);
  //g_2->Draw("ae3");
  //g_1->Draw("e3");

  //  g_sm ->Draw("l");
  g_data -> SetLineStyle(1);
  g_data -> SetMarkerSize(4);
  g_data -> SetMarkerStyle(1);



  g_data -> Draw("al");
  g_med->Draw("l");

  // TBox *box = new TBox (125.4-0.4, gPad->GetUymin(), 125.4+0.4, 0.5);

  // box->SetFillStyle(3001);
  // box->SetFillColor(kGreen+2);
  // box->SetLineColor(kGreen+2);
  // box->SetLineWidth(1);
  // box->Draw("l");
  // TLine *vert = new TLine();
  // vert->SetLineWidth(4);
  // vert->SetLineColor(kGreen+2);
  // vert->SetLineStyle(2);
  // vert->DrawLine(125.4, gPad->GetUymin(), 125.4, 0.5);

  //    g_ES->Draw("LP");

  TLegend *leg=FastLegend(0.20,0.76,0.4,0.92,0.05);


  TGraph *graph_dummy = new TGraph();
  graph_dummy->SetLineColor(kGreen+2);
  graph_dummy->SetLineStyle(2);
  graph_dummy->SetLineWidth(4);
  graph_dummy->SetFillColor(kGreen+2);
  graph_dummy->SetFillStyle(3001);
  // leg->AddEntry(g_med,"SM expected","L");
  leg->AddEntry(g_data,"Observed","L");


  // leg->AddEntry(graph_dummy, "#it{m}_{#it{H}} = 125.4 #pm 0.4 GeV", "lf");

  //leg->AddEntry(g_ES,"Observed p_{0} (with energy scale uncertainty)","LP");
  //leg->AddEntry(g_med,"Median","l");
  g_1->SetLineWidth(0);
  g_2->SetLineWidth(0);

  //leg->AddEntry(g_1,"#pm 1#sigma","f");
  //leg->AddEntry(g_2,"#pm 2#sigma","f");
  // leg->AddEntry(g_d0,"DZERO Exclusion","l");
  // leg->AddEntry(g_cdf,"CDF Exclusion","l");


  // leg->AddEntry(g_d0e,"Dzero Expected","l");
  leg->Draw();


  TLegend leg2(0.20,0.175,0.405,0.38);
  leg2.SetLineColor(0);
  leg2.SetFillStyle(0);
  leg2.SetShadowColor(0);
  leg2.SetTextSize(0.04);
  leg2.SetBorderSize(0);

  // leg2.AddEntry(g_data2,"Obs. 2011","L");
  // leg2.AddEntry(g_med2,"Exp. 2011","L");

  // leg2.AddEntry(g_data3,"Obs. 2012","L");
  // leg2.AddEntry(g_med3,"Exp. 2012","L");
  leg2.SetFillColor(0);
  // leg2.Draw();


  TLatex l; //l.SetTextAlign(12); l.SetTextSize(tsize);
  l.SetNDC();
  l.SetTextColor(1);
  l.SetTextSize(0.045);


  //l.DrawLatex(0.56,0.52,"Data 2011 #sqrt{s} = 7 TeV");
  //l.DrawLatex(0.56,0.30,"#scale[0.6]{#int}Ldt = 4.5 fb^{-1}, #sqrt{#it{s}} = 7 TeV");
  // l.DrawLatex(0.19,0.278,"#scale[0.6]{#int}Ldt = 4.5 fb^{-1}, #sqrt{#it{s}} = 7 TeV");

  //l.DrawLatex(0.56,0.35,"Data 2012 #sqrt{s} = 8 TeV");
  //l.DrawLatex(0.56,0.23,"#scale[0.6]{#int}Ldt = 20.3 fb^{-1}, #sqrt{#it{s}} = 8 TeV");
  // l.DrawLatex(0.19,0.208,"#scale[0.6]{#int}Ldt = 20.3 fb^{-1}, #sqrt{#it{s}} = 8 TeV");

  l.SetTextSize(0.06);
  // l.DrawLatex(0.66,0.23,"June 4th, 2012");
  // l.DrawLatex(0.18,0.05,"Combination of 2011 and 2012");
  // l.DrawLatex(0.2,0.2,"no look-elsewhere effect included");    

  TLatex la; //l.SetTextAlign(12); l.SetTextSize(tsize);
  la.SetNDC();
  la.SetTextFont(72);
  la.SetTextColor(1);

  TLatex lp;
  lp.SetNDC();
  lp.SetTextFont(42);
  lp.SetTextColor(1);

  la.DrawLatex(0.63,0.88,"ATLAS");
  lp.DrawLatex(0.775,0.88,"Internal");
  //lp.DrawLatex(0.755,0.88,"Preliminary");
  // lp.DrawLatex(0.63,0.83,"#it{H #rightarrow #gamma#gamma}");

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

  // TLine * l4=new TLine( start_point , SignificanceToPValue(4), end_point, SignificanceToPValue(4));
  // l4 -> SetLineWidth(2);
  // l4 -> SetLineColor(kGreen+1);
  // l4 -> SetLineStyle(5);
  // l4->Draw("same");

  // TLatex l4sigma;
  // l4sigma.SetTextFont(42);
  // l4sigma.DrawLatex(end_point+0.55,2e-5,"4#sigma");


  // TLine * l5=new TLine( start_point , SignificanceToPValue(5), end_point, SignificanceToPValue(5));
  // l5 -> SetLineWidth(2);
  // l5 -> SetLineColor(kGreen+1);
  // l5 -> SetLineStyle(5);
  // l5->Draw("same");

  // TLatex l5sigma;
  // l5sigma.SetTextFont(42);
  // l5sigma.DrawLatex(end_point+0.55,1.7e-7,"5#sigma");

  // TLine * l6=new TLine( start_point , 9.855e-10,end, 9.855e-10);
  // l6 -> SetLineWidth(2);
  // l6 -> SetLineColor(kGreen+1);
  // l6 -> SetLineStyle(5);
  // l6->Draw("same");

  // TLine * l7=new TLine( start_point , 1.275e-12,end, 1.275e-12);
  // l7 -> SetLineWidth(2);
  // l7 -> SetLineColor(kGreen+1);
  // l7 -> SetLineStyle(5);
  // l7->Draw("same");


  // TLatex l6sigma;
  // l6sigma.SetTextFont(42);
  // l6sigma.DrawLatex(end+0.55,1e-9,"6#sigma");

  // TLatex l7sigma;
  // l7sigma.SetTextFont(42);
  // l7sigma.DrawLatex(end+0.55,3.275e-12,"7#sigma");

  g_data -> Draw("l");
  g_med->Draw("l");

  c1->SetLogy();
  c1->RedrawAxis();

  system("mkdir -vp fig/plot_p0/high_mass_diphoton/");
  PrintCanvas(c1,"fig/plot_p0/high_mass_diphoton/pvalue_wisc_param");
  // c1->SaveAs("clbin2GeVlimit_finer_binning.C");

  cout<<"Combined: "<<maxdata.second<<" sigma at "<<maxdata.first<<" GeV"<<endl;
  // cout<<"7 TeV: "<<maxdata2.second<<" sigma at "<<maxdata2.first<<" GeV"<<endl;
  // cout<<"8 TeV: "<<maxdata3.second<<" sigma at "<<maxdata3.first<<" GeV"<<endl;

  return 0;


}
