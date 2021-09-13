#include "CommonHead.h"
#include "CommonFunc.h"
#include "statistics.hh"

using namespace std;
using namespace CommonFunc;

// 125	0.258994	124.651	1.73635	1.57575	10	124.651	7.11372	0.991516
// 125	0.39106	      124.669	1.65755	1.59406	10	124.669	5.58971	0.987137
// 125	0.163182	124.726	1.64297	1.56973	10	124.726	8.19872	0.990758
// 125	0.0623911	124.649	1.77729	1.65738	10	124.649	8.88195	0.982721
// 125	0.14261	 124.601	1.85327	1.6732	10	124.601	9.26485	0.982252
// 125	2.52465	  124.73	1.49081	2.02765	10	124.73	7.45348	0.997718
// 125	0.377238	124.783	1.3903	1.94892	10	124.783	6.94901	0.996274
// 125	5.24196	 124.599	1.81528	1.89983	10	124.599	9.07595	0.997233
// 125	0.771544	124.666	1.72724	4.25007	10	124.666	8.63532	0.991715
// 125	1.62932	 124.502	1.6808	1.54314	10	124.502	8.35168	0.997467
// 125	0.250185	124.665	1.54351	1.75973	10	124.665	7.71394	0.996758
// 125	4.77435	   124.5	2.02352	1.48689	10	124.5	10.1173	0.997096
// 125	0.684086	124.599	1.86957	1.61888	10	124.599	9.34772	0.99359
// 125	1.93662	  124.501	2.61872	1.3415	10	124.501	13.0911	0.995851

int main(int argc, char** argv){
  //************************************= Global booking and setting **********************************
  //   gErrorIgnoreLevel = kError+1;
  map<string,bool> Opt;
  Opt["ETA"]=false;
  Opt["COSTS"]=false;

  TString myOptList="";
  if(argc>1) myOptList=argv[1];
  myOptList.ToUpper();
  if (myOptList != "") {
    for (std::map<std::string,bool>::iterator it = Opt.begin(); it != Opt.end(); it++) it->second = false;

    std::vector<TString> olist = TMVA::gTools().SplitString( myOptList, ',' );
    for (UInt_t i=0; i<olist.size(); i++) {
      std::string Option(olist[i]);
      
      if (Opt.find(Option) == Opt.end()) {
	std::cout << "Option \"" << Option << "\" not known in DrawFrame under this name. Choose among the following:" << std::endl;
	for (std::map<std::string,bool>::iterator it = Opt.begin(); it != Opt.end(); it++) std::cout << it->first << " ";
	std::cout << std::endl;
	return 1;
      }
      Opt[Option] = true;
    }
  }
  SetAtlasStyle();
  //******************************************************************************************************************
  if(Opt["ETA"]){
    if(argc<3){
      cout<<"Usage: "<<argv[0]<<" "<<argv[1]<<" <jobname> <option>"<<endl;
      exit(0);
    }
    TString sigModel=argv[2];

    double xmin=0.5, xmax=1.4;
    const int nsi=4;
    
    TString selection[nsi]={"EKHI","HKHI","EKHI_inclusive_norm","HKHI_inclusive_norm"}, selectionName[nsi]={"Spin-2 sele.", "Spin-0 sele.", "Spin-2 sele.", "Spin-0 sele."};
    double injectedNsig[nsi], baseline;
    if(sigModel=="scalar") {injectedNsig[0]=injectedNsig[2]=30.12117;injectedNsig[1]=injectedNsig[3]=22.4362;baseline=3.72382;}
    if(sigModel=="graviton") {injectedNsig[0]=injectedNsig[2]=25.2663;injectedNsig[1]=injectedNsig[3]=14.62665;baseline=2.79338;}
    
    TCanvas *cv1 = CreateCanvas("canvas1", "",800,600);
    double x1,y1,x2,y2;
    GetX1Y1X2Y2(cv1,x1,y1,x2,y2);
    
    TLegend *leg=FastLegend(x2-0.55,y1+0.07,x2-0.01,y1+0.3,0.03);

    double eta_max=0, signif_max=0, signif_min=100;

    TH1F *hframe=new TH1F("hframe","",100,xmin-0.05,xmax+0.05);
    hframe->GetXaxis()->SetTitle("|#eta_{s2}| division point");
    hframe->GetYaxis()->SetTitle("Number counting significance");
    hframe->SetLineWidth(0);
    hframe->SetMinimum(baseline*0.95);
    hframe->SetMaximum(baseline*1.05);
    hframe->Draw();
    
    for(int is=0;is<nsi;is++){
      const int ncat=2;
      double eta[100], significance[100];
    
      vector<TString> fileName, fileName_fixrest;
      vector<int> etacut; 

      int idx=0;
      for(double eta_tmp=xmin; eta_tmp<=xmax+0.01; eta_tmp+=0.05){
	fileName.push_back(Form("Output/optimization/%s/summary_%s_%.2f_%.4f.txt", selection[is].Data(), sigModel.Data(), eta_tmp, injectedNsig[is]));
	eta[idx]=eta_tmp;
	idx++;
      }
    
      int neta=fileName.size();

      vector<int> temp;

      for(int idx=0;idx<neta;idx++){
	TString input=fileName[idx];
	ifstream f(input,ios::in);
	cout<<input<<endl;
	assert(f);
	double dummy;
	f>>dummy>>dummy>>significance[idx];
      
	if(significance[idx]>signif_max){
	  signif_max=significance[idx];
	  eta_max=eta[idx];
	}
	if(significance[idx]<signif_min){
	  signif_min=significance[idx];
	}
	f.close();
      }

      TGraph *plot_signif = new TGraph(neta,eta,significance);
      plot_signif->SetLineWidth(3);
      //plot_signif->SetLineStyle(2);
      //plot_signif->SetLineColor(kRed);
      //plot_signif->SetMarkerColor(kRed);

      cv1->cd();
      plot_signif->Draw("PL");
      //       plot_errlo_stat[1]->Draw("PL");
      plot_signif->GetXaxis()->SetTitleSize(0.05);
      plot_signif->GetXaxis()->SetTitleOffset(1.3);
      plot_signif->GetYaxis()->SetLabelSize(0.045);
      plot_signif->GetYaxis()->SetTitleSize(0.05);
      if(plot_signif->GetMinimum()>baseline) plot_signif->SetMinimum(baseline*0.995);
      plot_signif->SetLineColor(CommonFunc::ColorWheel((is)%2+2));
      plot_signif->SetMarkerColor(CommonFunc::ColorWheel((is)%2+2));
      TString normMethod="norm. to each cate.";
      if(is/2>0){
	plot_signif->SetLineStyle(2);
	plot_signif->SetMarkerStyle(25);
	normMethod="norm. to inclusive";
      }
      leg->AddEntry(plot_signif, selectionName[is]+", 2-#eta cate., "+normMethod,"lp");
    }
    if(signif_min<baseline) hframe->SetMinimum(signif_min*0.995);
    hframe->SetMaximum(signif_max*1.005);
    cv1->SetGridy();
    vector<TString> pavetext;
    pavetext.push_back("#bf{#it{ATLAS}} internal, "+sigModel+" signal");
    TPaveText* text=CreatePaveText(x1+0.01,y2,x1+0.4,y2+0.03,pavetext,0.045);
    text->Draw();
    TLine *line=new TLine(xmin, baseline, xmax, baseline);
    line->SetLineColor(kRed);
    line->SetLineWidth(3);
    line->SetLineStyle(4);
    line->Draw("same");
    leg->AddEntry(line,TString(sigModel=="scalar"?"Spin-0 selection":"Spin-2 selection")+", inclusive","l");
    leg->SetFillColor(0);
    leg->Draw();
    
    TString outputPlot=Form("fig/counting/summary_%s",sigModel.Data());
    cout<<"Maximum significance: "<<signif_max<<" with eta="<<eta_max
	<<", improvement="<<(signif_max-baseline)/baseline*100<<"%"
	<<endl;

    PrintCanvas(cv1,outputPlot);
  }
  //******************************************************************************************************************
  if(Opt["COSTS"]){
    if(argc<3){
      cout<<"Usage: "<<argv[0]<<" "<<argv[1]<<" <jobname> <option>"<<endl;
      exit(0);
    }
    TString sigModel=argv[2];

    double xmin=0.1, xmax=0.9;
    const int nsi=4;
    
    TString selection[nsi]={"EKHI","HKHI","EKHI_inclusive_norm","HKHI_inclusive_norm"}, selectionName[nsi]={"Abs. p_{T}", "Rel. p_{T}", "Abs. p_{T}", "Rel. p_{T}"};
    double injectedNsig[nsi], baseline;
    if(sigModel=="scalar") {injectedNsig[0]=injectedNsig[2]=30.12117;injectedNsig[1]=injectedNsig[3]=22.4362;baseline=3.72382;}
    if(sigModel=="graviton") {injectedNsig[0]=injectedNsig[2]=25.2663;injectedNsig[1]=injectedNsig[3]=14.62665;baseline=2.79338;}
    
    TCanvas *cv1 = CreateCanvas("canvas1", "",800,600);
    double x1,y1,x2,y2;
    GetX1Y1X2Y2(cv1,x1,y1,x2,y2);
    
    TLegend *leg=FastLegend(x2-0.55,y1+0.07,x2-0.01,y1+0.3,0.03);

    double costs_max=0, signif_max=0, signif_min=100;

    TH1F *hframe=new TH1F("hframe","",100,xmin-0.05,xmax+0.05);
    hframe->GetXaxis()->SetTitle("|cos#theta*| division point");
    hframe->GetYaxis()->SetTitle("Number counting significance");
    hframe->SetLineWidth(0);
    hframe->SetMinimum(baseline*0.95);
    hframe->SetMaximum(baseline*1.05);
    hframe->Draw();
    
    for(int is=0;is<nsi;is++){
      const int ncat=2;
      double costs[100], significance[100];
    
      vector<TString> fileName, fileName_fixrest;
      vector<int> costscut; 

      int idx=0;
      for(double costs_tmp=xmin; costs_tmp<=xmax+0.01; costs_tmp+=0.1){
	fileName.push_back(Form("Output/optimization/%s/summary_%s_costs_%.2f_%.4f.txt", selection[is].Data(), sigModel.Data(), costs_tmp, injectedNsig[is]));
	costs[idx]=costs_tmp;
	idx++;
      }
    
      int ncosts=fileName.size();

      vector<int> temp;

      for(int idx=0;idx<ncosts;idx++){
	TString input=fileName[idx];
	ifstream f(input,ios::in);
	cout<<input<<endl;
	assert(f);
	double dummy;
	f>>dummy>>dummy>>significance[idx];
      
	if(significance[idx]>signif_max){
	  signif_max=significance[idx];
	  costs_max=costs[idx];
	}
	if(significance[idx]<signif_min){
	  signif_min=significance[idx];
	}
	f.close();
      }

      TGraph *plot_signif = new TGraph(ncosts,costs,significance);
      plot_signif->SetLineWidth(3);
      //plot_signif->SetLineStyle(2);
      //plot_signif->SetLineColor(kRed);
      //plot_signif->SetMarkerColor(kRed);

      cv1->cd();
      plot_signif->Draw("PL");
      //       plot_errlo_stat[1]->Draw("PL");
      plot_signif->GetXaxis()->SetTitleSize(0.05);
      plot_signif->GetXaxis()->SetTitleOffset(1.3);
      plot_signif->GetYaxis()->SetLabelSize(0.045);
      plot_signif->GetYaxis()->SetTitleSize(0.05);
      if(plot_signif->GetMinimum()>baseline) plot_signif->SetMinimum(baseline*0.995);
      plot_signif->SetLineColor(CommonFunc::ColorWheel((is)%2+2));
      plot_signif->SetMarkerColor(CommonFunc::ColorWheel((is)%2+2));
      TString normMethod="norm. to each cate.";
      if(is/2>0){
	plot_signif->SetLineStyle(2);
	plot_signif->SetMarkerStyle(25);
	normMethod="norm. to inclusive";
      }
      leg->AddEntry(plot_signif, selectionName[is]+", 2-cos#theta* cate., "+normMethod,"lp");
    }
    if(signif_min<baseline) hframe->SetMinimum(signif_min*0.995);
    hframe->SetMaximum(signif_max*1.005);
    cv1->SetGridy();
    vector<TString> pavetext;
    pavetext.push_back("#bf{#it{ATLAS}} internal, "+sigModel+" signal");
    TPaveText* text=CreatePaveText(x1+0.01,y2,x1+0.4,y2+0.03,pavetext,0.045);
    text->Draw();
    TLine *line=new TLine(xmin, baseline, xmax, baseline);
    line->SetLineColor(kRed);
    line->SetLineWidth(3);
    line->SetLineStyle(4);
    line->Draw("same");
    leg->AddEntry(line,TString(sigModel=="scalar"?"Spin-0 selection":"Spin-2 selection")+", inclusive","l");
    leg->SetFillColor(0);
    leg->Draw();
    
    TString outputPlot=Form("fig/counting/summary_costs_%s",sigModel.Data());
    cout<<"Maximum significance: "<<signif_max<<" with costs="<<costs_max
	<<", improvement="<<(signif_max-baseline)/baseline*100<<"%"
	<<endl;

    PrintCanvas(cv1,outputPlot);
  }
  //******************************************************************************************************************
}
