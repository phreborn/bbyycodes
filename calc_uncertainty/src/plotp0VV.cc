#include "CommonHead.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"
#include "CommonFunc.h"
#include "statistics.hh"
#include "titleList.hh"

using namespace std;
using namespace CommonFunc;
using namespace RooStats;
using namespace RooFit;

const double epsilon=1e-6;
const double LARGENUM=1e37;
const double mHcomb=125.1;

int main(int argc, char **argv){
  //***************************= Global booking and setting ************************==
  //   gErrorIgnoreLevel = kError+1;
  map<string,bool> Opt;
  Opt["1D"]=false;
  Opt["2D"]=false;
  map<TString, TString> title=createTitleList();

  TString myOptList="";
  if(argc>1) myOptList=argv[1];
  myOptList.ToUpper();
  if (myOptList != "") {
    for (std::map<std::string,bool>::iterator it = Opt.begin(); it != Opt.end(); it++) it->second = false;

    std::vector<TString> olist = SplitString( myOptList, ',' );
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

  //************************************************************************************==
  if(Opt["1D"]){
    if(argc<4){
      cout<<"Usage: "<<argv[0]<<" "<<argv[1]<<" <jobname> <option>"<<endl;
      return 0;
    }
    TString jobname=argv[2];
    TString option=argv[3];

    bool m_rigorous=option.Contains("rigorous");
    
    TString inputSamples[5], legText[5];

    int nsample=1;
    inputSamples[0]=jobname+"_pvalue_obs"; legText[0]="Observed";
    if(option.Contains("exp")){
      inputSamples[1]=jobname+"_pvalue_exp";
      if(option.Contains("prefit")) inputSamples[1]=jobname+"_prefit_pvalue_exp";
      if(option.Contains("hvt")) legText[1]="Expected (HVT Model A, g_{V}=1)";
      if(option.Contains("rsg")) legText[1]="Expected (Bulk-RS Graviton)";
      
      nsample=2;
    }
    if(option.Contains("jes_exp")){
      inputSamples[0]="combined_VV_HVT_WZ_default_20160206_pvalue_exp"; legText[0]="Default";
      inputSamples[1]="combined_VV_HVT_WZ_nominal_20160206_pvalue_exp";	legText[1]="Nominal";
      inputSamples[2]="combined_VV_HVT_WZ_jes_20160206_pvalue_exp";	legText[2]="JES";
      inputSamples[3]="combined_VV_HVT_WZ_largeR_20160206_pvalue_exp";  legText[3]="Large-R";
      nsample=4;
    }
    if(option.Contains("jes_obs")){
      inputSamples[0]="combined_VV_HVT_WZ_default_20160206_pvalue_obs";  legText[0]="Default";
      inputSamples[1]="combined_VV_HVT_WZ_nominal_20160206_pvalue_obs";	 legText[1]="Nominal";
      inputSamples[2]="combined_VV_HVT_WZ_jes_20160206_pvalue_obs";	 legText[2]="JES";    
      inputSamples[3]="combined_VV_HVT_WZ_largeR_20160206_pvalue_obs";	 legText[3]="Large-R";
      nsample=4;
    }
    double xmin=500, xmax=3000;

    vector<double> massPoints;

    for(int mass=500; mass<2000; mass+=100) massPoints.push_back(mass);
    for(int mass=2000; mass<=3000; mass+=200) massPoints.push_back(mass);
    
    int npointx=massPoints.size();
    
    TCanvas* c = CreateCanvas("c", "pvalue",800,600);
    c->SetRightMargin(0.1);
    double x1,y1,x2,y2;
    GetX1Y1X2Y2(c,x1,y1,x2,y2);

    TH1D *hframe = new TH1D(jobname, jobname, npointx, xmin, xmax);

    TString xLabel="", yLabel="";
    if(option.Contains("hvt")){
      xLabel="m_{HVT} [GeV]";
    }
    else if(option.Contains("rsg")){
      xLabel="m_{G*} [GeV]";
    }
    
    hframe->GetXaxis()->SetTitle(xLabel);
    hframe->GetYaxis()->SetTitle("Local #it{p}_{0}");
    hframe->GetXaxis()->SetTitleSize(0.06);
    hframe->GetYaxis()->SetTitleSize(0.06);
    hframe->GetXaxis()->SetTitleOffset(0.85);
    hframe->GetYaxis()->SetTitleOffset(0.95);
    hframe->SetLineWidth(0);
    hframe->SetMaximum(10);
    hframe->SetMinimum(1e-3);
    if(option.Contains("jes_exp")||option.Contains("extend")){
      hframe->SetMinimum(1e-10);
      hframe->SetMaximum(1e2);
    }
    TString outputDir="fig/pvalue/"+jobname;
    system("mkdir -vp fig/pvalue/"+jobname);

    hframe->Draw();

    double pvalue[5][1000], mX[5][1000];
    int npoint[5];
    
    ofstream fout("fig/pvalue/"+jobname+"/summary.txt");

    for(int jj=0;jj<nsample;jj++){
      int realidx=0;
      Double_t maxsignif=1, maxmG=0, maxGkM=0;
      fout<<inputSamples[jj]<<endl;
      for(Int_t i = 0; i < npointx; i++){
	mX[jj][realidx]=massPoints[i];

	TChain* tfix = new TChain("toys/nllscan");
	TChain* that = new TChain("toys/nllscan");

	TString inputFixName="pvalue/"+inputSamples[jj]+Form("/%.0f_mufix.root",mX[jj][realidx]);
	TString inputHatName="pvalue/"+inputSamples[jj]+Form("/%.0f_muhat.root",mX[jj][realidx]);

	tfix->Add(inputFixName);
	that->Add(inputHatName);
	double nllfix, nllhat, mufix, muhat;
	int statusfix, statushat;
	tfix->SetBranchAddress("nll", &nllfix);
	tfix->SetBranchAddress("mu", &mufix);
	tfix->SetBranchAddress("status", &statusfix);
	
	int fixSuccess=tfix->GetEntry(0);

	that->SetBranchAddress("nll", &nllhat);
	that->SetBranchAddress("mu", &muhat);
	that->SetBranchAddress("status", &statushat);
	
	int hatSuccess=that->GetEntry(0);

	if(fixSuccess<=0||hatSuccess<=0){
	  cout<<"Point "<<mX[jj][realidx]<<" does not exist."<<endl;
	  if(m_rigorous) getchar();
	  continue;
	}
	cout<<"mX = "<<mX[jj][realidx]<<endl; 
	
	cout<<"++++++++++++ Fixed fit ++++++++++++++++"<<endl;
	cout<<"mu"<<" = "<<mufix<<endl;
	cout<<"NLL = "<<nllfix<<endl;
	cout<<"+++++++++++++++++++++++++++++++++++++++"<<endl;


	cout<<"++++++++++++ Float fit ++++++++++++++++"<<endl;
	cout<<"mu"<<" = "<<muhat<<endl;
	cout<<"NLL = "<<nllhat<<endl;
	cout<<"+++++++++++++++++++++++++++++++++++++++"<<endl;

	if((statusfix!=0&&statusfix!=1)||(statushat!=0&&statushat!=1)){
	  cout<<"Fitting problem with mass point "<<mX[jj][realidx]<<" in "<<inputSamples[jj]<<endl;
	  cout<<"Status fix "<<statusfix<<", status hat "<<statushat<<endl;
	  if(m_rigorous) getchar();
	  continue;
	}
	double DNLL=2*(nllfix-nllhat);
	pvalue[jj][realidx]=1-ROOT::Math::normal_cdf(sqrt(DNLL),1,0);
	if(!isfinite(pvalue[jj][realidx])) pvalue[jj][realidx]=0.5;

	// pvalue[jj][realidx]=RooStats::PValueToSignificance(pvalue[jj][realidx]);

	fout<<mX[jj][realidx]<<" "<<pvalue[jj][realidx]<<endl;

	if(pvalue[jj][realidx]<maxsignif&&jj==0){
	  maxsignif=pvalue[jj][realidx];
	  maxmG=mX[jj][realidx];
	}
	realidx++;
	SafeDelete(tfix);
	SafeDelete(that);
      }
      cout<<"Maximum significance: "<<maxsignif<<" at mG="<<maxmG<<" "<<RooStats::PValueToSignificance(maxsignif)<<endl;
      fout<<"Maximum significance: "<<maxsignif<<" at mG="<<maxmG<<" "<<RooStats::PValueToSignificance(maxsignif)<<endl;
      fout<<endl;
      npoint[jj]=realidx;
    }

    c->cd();

    TGraph *gr[5];

    TLegend *leg=NULL;
    if(option.Contains("rsg")) leg=FastLegend(x2-0.35, y1+0.05, x2-0.05, y1+0.15,0.045);
    if(option.Contains("hvt")) leg=FastLegend(x2-0.35, y1+0.05, x2-0.05, y1+0.15,0.045);
    if(option.Contains("jes")) leg=FastLegend(x2-0.35, y1+0.05, x2-0.05, y1+0.15,0.045);
    
    for(int jj=0;jj<nsample;jj++){
      gr[jj]=new TGraph(npoint[jj],mX[jj],pvalue[jj]);
      if(option.Contains("jes")){
	gr[jj]->SetLineColor(CommonFunc::ColorWheel(jj+1));
	gr[jj]->SetLineWidth(2);
      }
      else{
	if(jj==0){
	  gr[jj]->SetLineStyle(1);
	  gr[jj]->SetLineColor(1);
	  gr[jj]->SetLineWidth(2);
	  gr[jj]->SetMarkerSize(4);
	  gr[jj]->SetMarkerStyle(1);
	}
	else{
	  gr[jj]->SetLineStyle(2);
	  gr[jj]->SetLineColor(1);
	  gr[jj]->SetLineWidth(2);
	  gr[jj]->SetMarkerSize(4);
	  gr[jj]->SetMarkerStyle(1);
	}
      }
      leg->AddEntry(gr[jj],legText[jj],"l");
      gr[jj]->Draw("L");
    }
    
    vector<TString> pavetext,pavetext2;
    if(option.Contains("hvt_wz")){
      pavetext.push_back("HVT#rightarrowWZ");
      pavetext.push_back("llqq+lvqq+vvqq+qqqq");
    }
    else if(option.Contains("hvt_ww")){
      pavetext.push_back("HVT#rightarrowWW");
      pavetext.push_back("lvqq+qqqq");
    }
    else if(option.Contains("hvt_comb")){
      pavetext.push_back("HVT#rightarrowWZ/WW");
      pavetext.push_back("llqq+lvqq+vvqq+qqqq");
    }
    else if(option.Contains("nwa_comb")){
      pavetext.push_back("NWA#rightarrowWW/ZZ");
      pavetext.push_back("llqq+lvqq+vvqq");
    }
    else if(option.Contains("rsg_ww")){
      pavetext.push_back("G#rightarrowWW");
      pavetext.push_back("lvqq+qqqq");
    }
    else if(option.Contains("rsg_zz")){
      pavetext.push_back("G#rightarrowZZ");
      pavetext.push_back("llqq+vvqq+qqqq");
    }
    else if(option.Contains("rsg_comb")){
      pavetext.push_back("G#rightarrowWW/ZZ");
      pavetext.push_back("llqq+lvqq+vvqq+qqqq");
    }

    if(option.Contains("atlaspub")) pavetext2.push_back("#bf{#it{ATLAS}}");
    else if(option.Contains("atlasnote")) pavetext2.push_back("#bf{#it{ATLAS}} Preliminary");
    else if(option.Contains("asimov")) pavetext2.push_back("#bf{#it{ATLAS}} simulation internal");
    else pavetext2.push_back("#bf{#it{ATLAS}} internal");

    pavetext2.push_back("#sqrt{#it{s}} = 13 TeV, 3.2 fb^{-1}");


    TLatex lsigma;
    lsigma.SetTextFont(42);
    lsigma.DrawLatex(xmax+20, RooStats::SignificanceToPValue(1)*0.8, "1#sigma");
    lsigma.DrawLatex(xmax+20, RooStats::SignificanceToPValue(2)*0.8, "2#sigma");
    lsigma.DrawLatex(xmax+20, RooStats::SignificanceToPValue(3)*0.8, "3#sigma");
    
    CommonFunc::DrawConstantLine(c, RooStats::SignificanceToPValue(0), xmin, xmax, kGreen+1, 5, 2);
    CommonFunc::DrawConstantLine(c, RooStats::SignificanceToPValue(1), xmin, xmax, kGreen+1, 5, 2);
    CommonFunc::DrawConstantLine(c, RooStats::SignificanceToPValue(2), xmin, xmax, kGreen+1, 5, 2);
    CommonFunc::DrawConstantLine(c, RooStats::SignificanceToPValue(3), xmin, xmax, kGreen+1, 5, 2);

    if(option.Contains("jes_exp")){
      CommonFunc::DrawConstantLine(c, RooStats::SignificanceToPValue(4), xmin, xmax, kGreen+1, 5, 2);
      CommonFunc::DrawConstantLine(c, RooStats::SignificanceToPValue(5), xmin, xmax, kGreen+1, 5, 2);
      CommonFunc::DrawConstantLine(c, RooStats::SignificanceToPValue(6), xmin, xmax, kGreen+1, 5, 2);
      lsigma.DrawLatex(xmax+20, RooStats::SignificanceToPValue(4)*0.8, "4#sigma");
      lsigma.DrawLatex(xmax+20, RooStats::SignificanceToPValue(5)*0.8, "5#sigma");
      lsigma.DrawLatex(xmax+20, RooStats::SignificanceToPValue(6)*0.8, "6#sigma");
    
    }
    // TPaveText* text1=CreatePaveText(x1+0.01,y1+0.01,x1+0.4,y1+0.25,pavetext1,0.045);
    TPaveText* text1=CreatePaveText(x2-0.35,y2-0.2,x2-0.03,y2-0.05,pavetext,0.045);
    //TPaveText* text2=CreatePaveText(x2-0.4,y2-0.2,x2-0.01,y2-0.03,pavetext2,0.045);
    TPaveText* text2=CreatePaveText(x1+0.03,y2-0.2,x1+0.4,y2-0.05,pavetext2,0.045);
    // legend->AddEntry(&markerSM, "SM","P");
    c->cd();
    c->SetLogy();
    text1->Draw("same");
    text2->Draw("same");
    leg->Draw("same");
    c->Update();
    c->RedrawAxis();
    //c->SetGrid();
    TString outputCanvasName="fig/pvalue/"+jobname+"/pvalue_plot";
    if(option.Contains("prefit")) outputCanvasName+="_prefit";
    system("mkdir -vp fig/pvalue/"+jobname);
    PrintCanvas(c,outputCanvasName);

    fout.close();
    // conts->SaveAs("test.root");
  }
  //************************************************************************************==

}
