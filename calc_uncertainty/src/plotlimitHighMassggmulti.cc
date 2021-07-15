#include "frame.h"

using namespace std;
using namespace CommonFunc;
using namespace RooStats;

double epsilon=1e-6;

int findIdx(int nmass, double *mass, double value){
  int idx=-1;
  for(int imass=0;imass<nmass;imass++){
    if(fabs(mass[imass]-value)<epsilon){ idx=imass; break;}
  }
  return idx;
}

void convertToPb(int nmass, double *mass){
  for(int imass=0;imass<nmass;imass++){
    mass[imass]/=1000.;
  }
}

void mergeXS(int nmass, double *massTot, double *mass1, double *mass2){
  for(int imass=0;imass<nmass;imass++){
    massTot[imass]=mass1[imass]+mass2[imass];
  }
}

// let's make a 6sigma plot
int main(int argc, char **argv){
  //============================ Global booking and setting ==========================
  //   gErrorIgnoreLevel = kError+1;
  map<string,bool> Opt;
  Opt["LIMIT"]=false;

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
  //================================= Draw Limit Band ====================================
  if(Opt["LIMIT"]){
    if(argc<4){
      cout<<"Usage: "<<argv[0]<<" "<<argv[1]<<" <jobname> <option>"<<endl;
      exit(0);
    }
    TString jobname=argv[2];
    Double_t kappa=atof(argv[3]);
    TString option=argv[4];
    
    option.ToLower();

    TString type;
    TString fileName[5], legText[5], scaleOpt[5];
    Color_t color[5];
    int nsample=1;

    double mass[5][200], mass_for_plot[5][200];
    double N2S[5][200],N1S[5][200],P1S[5][200],P2S[5][200],Median[5][200],Zero[5][200],Observed[5][200];
    vector<int> temp;
    TCanvas *cv = CreateCanvas("canvas", "",800,600);
    double x1,y1,x2,y2;
    GetX1Y1X2Y2(cv,x1,y1,x2,y2);

    int nmass[5];
    double xmin, xmax, ymin, ymax;

    vector<TString> pavetext, pavetext2;

    pavetext.push_back(Form("G*#rightarrow#gamma#gamma, #it{k}/#bar{M}_{Pl}=%.2f", kappa));
    
    pavetext2.push_back("#bf{#it{ATLAS}} internal");
    pavetext2.push_back("#sqrt{#it{s}} = 13 TeV, 3.2 fb^{-1}");

    for(int Mass=500;Mass<=3500;Mass+=20) temp.push_back(Mass);
    nmass[0]=temp.size();
    for(int i=0;i<nmass[0];i++) mass[0][i]=temp[i];
    
    xmin=mass[0][0];
    xmax=mass[0][nmass[0]-1];

    ymin=8e-1;
    ymax=5e1;

    if(option.Contains("obs")){
      ymin=8e-1;
      ymax=1e2;
    }
    nsample=2;
    fileName[0]="high_mass_diphoton_Graviton_13TeV_histfactory_EKEI_v4_2dlimit_binned";          legText[0]="Loose isolation";      scaleOpt[0]="hvt_wz";  color[0]=kRed;
    fileName[1]="high_mass_diphoton_Graviton_13TeV_histfactory_EKHI_v6_2dlimit_binned";          legText[1]="Tight isolation";      scaleOpt[1]="hvt_wz";  color[1]=kBlue;

    for(int isample=0;isample<nsample;isample++){
      nmass[isample]=temp.size();
      for(int i=0;i<nmass[0];i++) mass[isample][i]=temp[i];
    }
    

    system(Form("mkdir -vp fig/limit_plot/%s",jobname.Data()));
    ofstream fout(Form("fig/limit_plot/%s/limit.txt",jobname.Data()),ios::out);
    fout<<Form("Mass \t Obs \t Med \t -1S \t -2S \t +1S \t +2S")<<endl;
    double max=0;

    for(int jj=0;jj<nsample;jj++){
      Info("Frame: LIMIT","%d mass points will be processed.",nmass[jj]);
      int realidx=0;
      for(int idx=0;idx<nmass[jj];idx++){

	TString infile=Form("limit/%s/%s_%.2f_%.2f.txt", fileName[jj].Data(), fileName[jj].Data(), mass[jj][idx], kappa);
	cout<<infile<<endl;
	ifstream fin(infile.Data(),ios::in);
	if(!fin){
	  cerr<<"File "<<infile.Data()<<" does not exist."<<endl;
	  if(option.Contains("rigorous")) getchar();
	  continue;
	}
	double n2s,n1s,median,p1s,p2s,observed;
	TString dummy;
	fin>>dummy>>observed>>median>>p2s>>p1s>>n1s>>n2s;
	fin.close();

	cout << "Mass "<<mass[jj][idx]<<" GeV"<<endl; mass_for_plot[jj][realidx]=mass[jj][idx];
	cout << "-2 sigma  band " << n2s << endl; N2S[jj][realidx]=median-n2s;
	cout << "-1 sigma  band " << n1s << endl; N1S[jj][realidx]=median-n1s;
	cout << "Median of band " << median << endl; Median[jj][realidx]=median;
	cout << "+1 sigma  band " << p1s << endl; P1S[jj][realidx]=p1s-median;
	cout << "+2 sigma  band " << p2s << endl; P2S[jj][realidx]=p2s-median;
	cout << "Observed "<<observed<<endl;Observed[jj][realidx]=observed;
	Zero[jj][realidx]=0;

	fout<<Form("%.1f \t %.2f \t %.2f \t %.2f \t %.2f \t %.2f \t %.2f",mass[jj][realidx],observed,median,n1s,n2s,p1s,p2s)<<endl;
	realidx++;
      }
      nmass[jj]=realidx;
    }
    
    cout<<"All info has been retrieved."<<endl;
    TGraph *likelihd_limit_d[5];
    TGraph *likelihd_limit_c[5];
    TGraphAsymmErrors *likelihd_limit_1sigma[5];
    TGraphAsymmErrors *likelihd_limit_2sigma[5];

    TString xLabel="m_{G*} [GeV]", yLabel="95% CL limits on #sigma#timesBR(G*#rightarrow#gamma#gamma) [fb]";
    
    TH1D *hframe=new TH1D("hframe","hframe",1000,xmin-50,xmax+50);
    hframe->SetMaximum(ymax);
    hframe->SetMinimum(ymin);
    hframe->GetXaxis()->SetTitle(xLabel);
    hframe->GetYaxis()->SetTitle(yLabel);
    hframe->GetXaxis()->SetTitleSize(0.05);
    hframe->GetXaxis()->SetTitleOffset(1.3);
    hframe->GetYaxis()->SetLabelSize(0.045);
    hframe->GetYaxis()->SetTitleSize(0.05);
    hframe->SetLineWidth(0);
    hframe->Draw();
    // TMultiGraph *likelihd_limit = new TMultiGraph("Exclusion at 95% CL_{s}","CL_{S} Exclusion Limits ;"+xLabel+"; "+yLabel+"");
    TLegend *leg=FastLegend(0.53,0.65,0.92,0.92,0.045);
    TLegend *leg2=FastLegend(0.53,0.4,0.93,0.6,0.045);
    TPaveText* text=CreatePaveText(x1+0.4,y1+0.4,x1+0.9,y1+0.6,pavetext,0.05);
    TPaveText* text2=CreatePaveText(x1+0.4,y1+0.6,x2-0.03,y2-0.05,pavetext2,0.05);

    leg->SetNColumns(2);

    leg->SetFillColor(0);
    leg2->SetFillColor(0);
    for(int jj=0;jj<nsample;jj++){	// WSN...
      likelihd_limit_d[jj] = new TGraph(nmass[jj],mass_for_plot[jj],Observed[jj]);
      likelihd_limit_c[jj] = new TGraph(nmass[jj],mass_for_plot[jj],Median[jj]);

      int lineStyle=1;
      if(jj!=0) lineStyle=7;
      
      likelihd_limit_c[jj]->SetLineStyle(lineStyle);
      likelihd_limit_d[jj]->SetLineWidth(3);
      likelihd_limit_c[jj]->SetLineWidth(3);

      likelihd_limit_d[jj]->SetLineStyle(1); 
      likelihd_limit_d[jj]->SetMarkerSize(0.9);
      likelihd_limit_d[jj]->SetLineColor(color[jj]);
      likelihd_limit_c[jj]->SetLineColor(color[jj]);

      likelihd_limit_1sigma[jj] = new TGraphAsymmErrors(nmass[jj],mass_for_plot[jj],Median[jj],Zero[jj],Zero[jj],N1S[jj],P1S[jj]);
      likelihd_limit_1sigma[jj]->SetFillColor(kGreen);
      likelihd_limit_1sigma[jj]->SetLineColor(kGreen);

      likelihd_limit_2sigma[jj] = new TGraphAsymmErrors(nmass[jj],mass_for_plot[jj],Median[jj],Zero[jj],Zero[jj],N2S[jj],P2S[jj]);

      likelihd_limit_2sigma[jj]->SetFillColor(kYellow);
      likelihd_limit_2sigma[jj]->SetLineColor(kYellow);

      // likelihd_limit->Add(likelihd_limit_2sigma[jj],"E3");  
      // likelihd_limit->Add(likelihd_limit_1sigma[jj],"E3");
      // likelihd_limit_2sigma[jj]->Draw("E3");  
      // likelihd_limit_1sigma[jj]->Draw("E3");
      if(option.Contains("exp")){
	likelihd_limit_c[jj]->Draw("L");
	leg2->AddEntry(likelihd_limit_c[jj],legText[jj]+"","l");
	
      }
      if(option.Contains("obs")){
	leg2->AddEntry(likelihd_limit_d[jj],legText[jj]+"","l");
	likelihd_limit_d[jj]->Draw("L");
      }
    }

    // Theory curves
    // if(option.Contains("rsg")) text=CreatePaveText(x1+0.4,y1+0.05,x1+0.9,y1+0.23,pavetext,0.05);
    cv->cd();

    // likelihd_limit->Draw("A");
    // likelihd_limit->GetXaxis()->SetRangeUser(xmin,xmax);
    // likelihd_limit->SetMaximum(ymax);
    // likelihd_limit->SetMinimum(ymin);

    leg->Draw("same");
    leg2->Draw("same");

    text->Draw("same");
    text2->Draw("same");

    if(option.Contains("logy")) cv->SetLogy();
    cv->RedrawAxis();
    TString outputCanvasName=Form("fig/limit_plot/%s/limitplot_multi_%.2f", jobname.Data(), kappa);
    if(option.Contains("exp")) outputCanvasName+="_exp";
    if(option.Contains("obs")) outputCanvasName+="_obs";
    PrintCanvas(cv, outputCanvasName);
    fout.close();
  }// 
  //======================================================================================
}
