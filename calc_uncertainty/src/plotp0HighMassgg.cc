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
  Opt["PR1D"]=false;
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
  double luminosity2016=12.2;
  double luminosity2015=3.2;
  // double luminosity2016=0.1788;
  // double luminosity2016=0.410;

  //************************************************************************************==
  if(Opt["2D"]){
    if(argc<4){
      cout<<"Usage: "<<argv[0]<<" plot <jobname> <poiNamex,startx,endx,binwx> <poiNamey,starty,endy,binwy> <option>"<<endl;
      return 0;
    }
    TString jobname=argv[2];
    TString inputXVar=argv[3];
    TString inputYVar=argv[4];
    TString option=argv[5];
    
    bool m_textright=option.Contains("textright");
    bool m_textlow=option.Contains("textlow");
    bool m_textmiddle=option.Contains("textmiddle");

    bool m_legright=option.Contains("legright");
    bool m_legleft=option.Contains("legleft");
    bool m_legmiddle=option.Contains("legmiddle");

    bool m_fine=option.Contains("fine");
    bool m_2sigma=option.Contains("2sigma");
    //bool m_nominfile=option.Contains("nominfile");
    bool m_extend=option.Contains("extend");
    bool m_asimov=option.Contains("asimov");
    bool m_noerrlo=option.Contains("noerrlo");
    bool m_noerrhi=option.Contains("noerrhi");
    bool m_negative=option.Contains("negative");
    bool m_rigorous=option.Contains("rigorous");
    bool m_right=option.Contains("right");
    bool m_noleg=option.Contains("noleg");

    vector<TString> inputXList=SplitString(inputXVar,',');
    vector<TString> inputYList=SplitString(inputYVar,',');

    TString poi1Name=inputXList[0], poi2Name=inputYList[0];
    double xmin=inputXList[1].Atof(), ymin=inputYList[1].Atof();
    double xmax=inputXList[2].Atof(), ymax=inputYList[2].Atof();
    double binwx=inputXList[3].Atof(), binwy=inputYList[3].Atof();
    int npointx=int((xmax-xmin+epsilon)/binwx)+1, npointy=int((ymax-ymin+epsilon)/binwy)+1;
    TCanvas* c = CreateCanvas("c", "2dpvalue",800,600);
    c->SetRightMargin(0.15);
    c->SetBottomMargin(0.12);
    c->SetTopMargin(0.10);
    double x1,y1,x2,y2;
    GetX1Y1X2Y2(c,x1,y1,x2,y2);

    const Int_t NRGBs = 5;
    const Int_t NCont = 255;

    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle->SetNumberContours(NCont);
    
    TH2D *hframe = new TH2D(jobname,  jobname,
			    npointx, xmin-binwx/2, xmax+binwx/2, npointy, ymin-binwy/2, ymax+binwy/2);
    
    hframe->GetXaxis()->SetTitle(title[poi1Name]);
    hframe->GetXaxis()->SetRangeUser(xmin,xmax);
    hframe->GetYaxis()->SetTitle(title[poi2Name]);
    if(option.Contains("scalar"))  hframe->GetYaxis()->SetTitle("#Gamma_{X}/m_{X}");
    hframe->GetXaxis()->SetTitleSize(0.06);
    hframe->GetYaxis()->SetTitleSize(0.06);
    hframe->GetXaxis()->SetTitleOffset(0.85);
    hframe->GetYaxis()->SetTitleOffset(0.95);
    hframe->GetYaxis()->SetRangeUser(ymin,ymax);
    hframe->GetZaxis()->SetTitle("Local significance [#sigma]");
    hframe->GetZaxis()->SetTitleOffset(1.2);
    c->SetRightMargin(0.18);
    
    TString outputDir="fig/pvalue/"+jobname;
    system("mkdir -vp fig/pvalue/"+jobname);

    hframe->Draw();

    double pvalue[1000][1000];
    double maxsignif=-1, maxmG=0, maxGkM=0;
    double maxsignif2nd=-1, maxmG2nd=0, maxGkM2nd=0;

    ofstream fout("fig/pvalue/"+jobname+"/summary.txt");
    
    for (Int_t i = 0; i < npointx; i++) {
      fout<<xmin+i*binwx<<" ";
      for(Int_t j = 0; j < npointy; j++){
	pvalue[i][j]=0;
	double poi1Value=xmin+i*binwx;
	double poi2Value=ymin+j*binwy;
	TChain* tfix = NULL;
	TChain* that = NULL;
	double nllfix, nllhat, xs, mG=poi1Value, GkM=poi2Value;
	int statusfix=0, statushat=0;

	if(option.Contains("txt")){
	  TString inputFixName="pvalue/"+jobname+Form("/%s=%.2f_%s=%.2f_mufix.txt",poi1Name.Data(),poi1Value,poi2Name.Data(),poi2Value);
	  TString inputHatName="pvalue/"+jobname+Form("/%s=%.2f_%s=%.2f_muhat.txt",poi1Name.Data(),poi1Value,poi2Name.Data(),poi2Value);

	  if(option.Contains("scalar")){
	    poi2Value*=poi1Value;
	    if(poi2Value<epsilon) poi2Value=0.004;
	    inputFixName="pvalue/"+jobname+Form("/%s=%.2f_%s=%.4f_mufix.txt",poi1Name.Data(),poi1Value,poi2Name.Data(),poi2Value);
	    inputHatName="pvalue/"+jobname+Form("/%s=%.2f_%s=%.4f_muhat.txt",poi1Name.Data(),poi1Value,poi2Name.Data(),poi2Value);
	  }
	  ifstream finfix(inputFixName), finhat(inputHatName);
	  if(!finfix||!finhat){
	    cout<<"Point "<<poi1Value<<":"<<poi2Value<<" does not exist."<<endl;
	    cout<<inputFixName<<" "<<inputHatName<<endl;
	    if(m_rigorous) getchar();
	    continue;
	  }
	  finfix>>xs>>nllfix>>statusfix;
	  finhat>>xs>>nllhat>>statushat;
	  finfix.close();
	  finhat.close();
	}
	else{
	  tfix = new TChain("toys/nllscan");
	  that = new TChain("toys/nllscan");

	  TString inputFixName="pvalue/"+jobname+Form("/*%s=%.2f*%s=%.2f*_mufix.root",poi1Name.Data(),poi1Value,poi2Name.Data(),poi2Value);
	  TString inputHatName="pvalue/"+jobname+Form("/*%s=%.2f*%s=%.2f*_muhat.root",poi1Name.Data(),poi1Value,poi2Name.Data(),poi2Value);

	  if(option.Contains("scalar")){
	    poi2Value*=poi1Value;
	    if(poi2Value<epsilon) poi2Value=0.004;
	    inputFixName="pvalue/"+jobname+Form("/*%s=%.2f*%s=%.4f*_mufix.root",poi1Name.Data(),poi1Value,poi2Name.Data(),poi2Value);
	    inputHatName="pvalue/"+jobname+Form("/*%s=%.2f*%s=%.4f*_muhat.root",poi1Name.Data(),poi1Value,poi2Name.Data(),poi2Value);
	    // cout<<inputHatName<<" "<<inputFixName<<endl;
	  }

	  if(tfix->Add(inputFixName)!=1||that->Add(inputHatName)!=1){
	    cout<<"Point "<<poi1Value<<":"<<poi2Value<<" does not exist."<<endl;
	    if(m_rigorous) getchar();
	    continue;
	  }

	  tfix->SetBranchAddress("nll", &nllfix);
	  tfix->SetBranchAddress("xs", &xs);
	  tfix->SetBranchAddress(poi1Name, &mG);
	  tfix->SetBranchAddress(poi2Name, &GkM);
	  tfix->SetBranchAddress("status", &statusfix);
	
	  tfix->GetEntry(0);

	  that->SetBranchAddress("nll", &nllhat);
	  that->SetBranchAddress("xs", &xs);
	  that->SetBranchAddress(poi1Name, &mG);
	  that->SetBranchAddress(poi2Name, &GkM);
	  that->SetBranchAddress("status", &statushat);
	
	  that->GetEntry(0);
	}
	cout<<"++++++++++++ Fixed fit ++++++++++++++++"<<endl;
	cout<<"xs"<<" = "<<xs<<endl;
	cout<<poi1Name<<" = "<<mG<<endl;
	cout<<poi2Name<<" = "<<GkM<<endl;
	cout<<"NLL = "<<nllfix<<endl;
	cout<<"+++++++++++++++++++++++++++++++++++++++"<<endl;


	cout<<"++++++++++++ Float fit ++++++++++++++++"<<endl;
	cout<<"xs"<<" = "<<xs<<endl;
	cout<<poi1Name<<" = "<<mG<<endl;
	cout<<poi2Name<<" = "<<GkM<<endl;
	cout<<"NLL = "<<nllhat<<endl;
	cout<<"+++++++++++++++++++++++++++++++++++++++"<<endl;
	if((statusfix!=0&&statusfix!=1)||(statushat!=0&&statushat!=1)){
	  cout<<"Fitting problem with point "
	      <<poi1Name<<"="<<mG<<" "
	      <<poi2Name<<"="<<GkM
	      <<endl;
	  cout<<"Status fix "<<statusfix<<", status hat "<<statushat<<endl;
	  if(m_rigorous){
	    // system("mkdir -vp pvalue/"+jobname+"/junk");
	    // system("mv -v "+inputFixName+" pvalue/"+jobname+"/junk");
	    // system("mv -v "+inputHatName+" pvalue/"+jobname+"/junk");
	    getchar();
	  }
	  continue;
	}
	double DNLL=2*(nllfix-nllhat);
	int sign=(xs>0)?1:-1;
	pvalue[i][j]=1-ROOT::Math::normal_cdf(sign*sqrt(DNLL),1,0);
	// pvalue[i][j]=1-ROOT::Math::normal_cdf(sqrt(DNLL),1,0);
	if(!isfinite(pvalue[i][j])) pvalue[i][j]=0.5;
	
	pvalue[i][j]=RooStats::PValueToSignificance(pvalue[i][j]);

	fout<<pvalue[i][j]<<" ";
	if(pvalue[i][j]<epsilon){
	  pvalue[i][j]=epsilon;
	}
	hframe->SetBinContent(i+1,j+1,pvalue[i][j]);
	if(pvalue[i][j]>maxsignif){
	  maxsignif=pvalue[i][j];
	  maxmG=mG;
	  maxGkM=GkM;
	}
	if(pvalue[i][j]>maxsignif2nd&&mG>700&&mG<800){
	  maxsignif2nd=pvalue[i][j];
	  maxmG2nd=mG;
	  maxGkM2nd=GkM;
	}

	if(!option.Contains("txt")){
	  SafeDelete(tfix);
	  SafeDelete(that);
	}
      }
      fout<<endl;
    }
    c->cd();
    hframe->Draw("COLZ");
    // hframe->GetXaxis()->SetAxisColor(2,0.5);
    // hframe->GetYaxis()->SetAxisColor(2,0.5);
    hframe->GetZaxis()->SetRangeUser(0,maxsignif>3.5?5:3.5);
    vector<TString> pavetext1,pavetext2;
    if(option.Contains("8tev")){
      pavetext1.push_back("#sqrt{#it{s}} = 8 TeV, 20.3 fb^{-1}");
      // pavetext2.push_back("#sqrt{#it{s}} = 13 TeV, 3.2 fb^{-1}");
    }
    else{
      TString lumiStr="";
      if(option.Contains("2015")) lumiStr=Form("%.1f fb^{-1}", luminosity2015);
      if(option.Contains("2016")) lumiStr=Form("%.1f fb^{-1}", luminosity2016);
      if(option.Contains("1516")) lumiStr=Form("%.1f fb^{-1}", luminosity2015+luminosity2016);
      if(option.Contains("gravitonloose")){
	if(option.Contains("1516")) pavetext1.push_back(Form("#sqrt{#it{s}} = 13 TeV, %s Spin-2 Loose Selection", lumiStr.Data()));
	else pavetext1.push_back(Form("#sqrt{#it{s}} = 13 TeV, %s Spin-2 Loose Selection", lumiStr.Data()));
      }
      else if(option.Contains("graviton")){
	// if(option.Contains("1516")) pavetext1.push_back(Form("#sqrt{#it{s}} = 13 TeV, %s Spin-2 Selection", lumiStr.Data()));
	// else 
	  pavetext1.push_back(Form("#sqrt{#it{s}} = 13 TeV, %s    Spin-2 Selection", lumiStr.Data()));
      }
      
      if(option.Contains("scalar")) pavetext1.push_back(Form("#sqrt{#it{s}} = 13 TeV, %s    Spin-0 Selection", lumiStr.Data()));
    }
    
    //pavetext1.push_back("#bf{#it{ATLAS}} preliminary");
    //     pavetext1.push_back("H#rightarrow#gamma#gamma");
    //pavetext1.push_back("2011-2012");
    //pavetext1.push_back("#it{m}_{#it{H}} = 125.4 GeV");
    //    pavetext1.push_back(Form("#hat{#mu}_{#it{ggF+ttH}}#timesB/B_{SM}=%.1f, #hat{#mu}_{#it{VBF+VH}}#timesB/B_{SM}=%.1f",mu_tH,mu_VH));

    //pavetext2.push_back("2011-2012");
    if(option.Contains("atlaspub")) pavetext2.push_back("#bf{#it{ATLAS}}");
    else if(option.Contains("atlasnote")) pavetext2.push_back("#bf{#it{ATLAS}} Preliminary");
    else if(option.Contains("asimov")) pavetext2.push_back("#bf{#it{ATLAS}} simulation internal");
    else pavetext2.push_back("#bf{#it{ATLAS}} internal");

    // TPaveText* text1=CreatePaveText(x1+0.01,y1+0.01,x1+0.4,y1+0.25,pavetext1,0.045);
    TPaveText* text1=CreatePaveText(x1+0.2,y2+0.01,x2-0.03,y2+0.07,pavetext1,0.05);
    if(// option.Contains("1516")||
       option.Contains("gravitonloose")){
      text1=CreatePaveText(x1+0.15,y2+0.01,x2-0.03,y2+0.07,pavetext1,0.045);
    }
    //TPaveText* text2=CreatePaveText(x2-0.4,y2-0.2,x2-0.01,y2-0.03,pavetext2,0.045);
    TPaveText* text2=CreatePaveText(x1-0.13,y2+0.01,x1+0.3,y2+0.07,pavetext2,0.05);
    if(option.Contains("atlaspub")){
      text2=CreatePaveText(x1-0.05,y2+0.01,x1+0.3,y2+0.07,pavetext2,0.05);
    }
    // legend->AddEntry(&markerSM, "SM","P");
    c->cd();
    text1->Draw("same");
    text2->Draw("same");
    c->Update();
    //c->SetGrid();
    system("mkdir -vp fig/pvalue/"+jobname);
    PrintCanvas(c,"fig/pvalue/"+jobname+"/2dpvalue_"+poi1Name+"_"+poi2Name);

    cout<<"Maximum significance: "<<maxsignif<<" at mG="<<maxmG<<" and GkM="<<maxGkM<<endl;
    fout<<"Maximum significance: "<<maxsignif<<" at mG="<<maxmG<<" and GkM="<<maxGkM<<endl;
    cout<<"2nd maximum significance: "<<maxsignif2nd<<" at mG="<<maxmG2nd<<" and GkM="<<maxGkM2nd<<endl;
    fout<<"2nd maximum significance: "<<maxsignif2nd<<" at mG="<<maxmG2nd<<" and GkM="<<maxGkM2nd<<endl;

    fout.close();
    // conts->SaveAs("test.root");
  }
  //************************************************************************************==
  if(Opt["1D"]){
    if(argc<4){
      cout<<"Usage: "<<argv[0]<<" "<<argv[1]<<" <jobname> <kappa> <input file 1> <input file 2> ... <option>"<<endl;
      return 0;
    }
    TString jobname=argv[2];
    double kappa=atof(argv[3]);
    vector<TString> inputSamples, legText;
    vector<int> lineColor;
    if(argc>5){
      for(int i=4; i<argc-1; i++){
	vector<TString> splitStr=CommonFunc::SplitString(argv[i],',');
	splitStr[1]=splitStr[1].ReplaceAll("~"," ");
	inputSamples.push_back(splitStr[0]);
	legText.push_back(splitStr[1]);
	lineColor.push_back(splitStr[2].Atoi());
      }
    }
    else{
      inputSamples.push_back(jobname);
      legText.push_back("Observed");
      lineColor.push_back(kBlack);
    }
    TString option=argv[argc-1];    
    int nsample=inputSamples.size();

    bool m_rigorous=option.Contains("rigorous");
    
    vector<double> massPoints;

    int massmin=200, massmax=2500, massstep=5;
    if(option.Contains("8tev")){
      if(option.Contains("scalar")){
	massmin=200;
	massmax=2000;
	massstep=10;
      }
      else if(option.Contains("graviton")){
	massmin=500;
	massmax=1000;
	massstep=5;
      }
    }
    else{
      if(option.Contains("scalar")){
	massmin=200;
	massstep=option.Contains("liron")?5:10;
	if(option.Contains("2015")||option.Contains("ekeimekhi")) massmax=2000;
	else massmax=2500;
      }
      else if(option.Contains("graviton")){
	massmin=500;
	massstep=option.Contains("liron")?5:10;
	if(option.Contains("2015")||option.Contains("ekeimekhi")) massmax=2000;
	else massmax=2500;
      }
    }

    for(int mass=massmin; mass<=massmax; mass+=massstep) massPoints.push_back(mass);
    
    double xmin=massPoints[0], xmax=massPoints.back();

    int npointx=massPoints.size();
    
    TCanvas* c = CreateCanvas("c", "pvalue",800,600);
    // c->SetRightMargin(0.1);
    double x1,y1,x2,y2;
    GetX1Y1X2Y2(c,x1,y1,x2,y2);

    TH1D *hframe = new TH1D(jobname, jobname, npointx, xmin-120, xmax+120);

    TString xLabel="", yLabel="";
    if(option.Contains("scalar")){
      xLabel="m_{X} [GeV]";
    }
    else if(option.Contains("graviton")){
      xLabel="m_{G*} [GeV]";
    }
    
    hframe->GetXaxis()->SetTitle(xLabel);
    // hframe->GetYaxis()->SetTitle("Local #it{p}_{0}");
    hframe->GetYaxis()->SetTitle("p-value");
    hframe->GetXaxis()->SetTitleSize(0.06);
    hframe->GetYaxis()->SetTitleSize(0.06);
    hframe->GetXaxis()->SetTitleOffset(1);
    hframe->GetYaxis()->SetTitleOffset(0.95);
    hframe->SetLineWidth(0);
    hframe->SetMaximum(2);
    hframe->SetMinimum(1e-5);
    if(option.Contains("jes_exp")||option.Contains("extend")){
      hframe->SetMinimum(1e-10);
      hframe->SetMaximum(1e2);
    }
    if(option.Contains("8tev")){
      hframe->SetMaximum(5);
      hframe->SetMinimum(1e-2);
    }
    if(option.Contains("5sigma")) hframe->SetMinimum(RooStats::SignificanceToPValue(5));
    TString outputDir="fig/pvalue/"+jobname;
    system("mkdir -vp fig/pvalue/"+jobname);

    hframe->Draw();

    double pvalue[5][10000], mX[5][10000];
    int npoint[5];

    ofstream fout(Form("fig/pvalue/"+jobname+"/summary_%.2f.txt", kappa));
    double maxSignif=0, maxMass;
    for(int jj=0;jj<nsample;jj++){
      int realidx=0;
      double maxsignif=1, maxmG=0, maxGkM=0;
      TChain* tfix = NULL;
      TChain* that = NULL;
      for(Int_t i = 0; i < npointx; i++){
	mX[jj][realidx]=massPoints[i];
	TString inputFixName="pvalue/"+inputSamples[jj]+Form("/mG=%.2f_GkM=%.2f_mufix.root",mX[jj][realidx], kappa);
	TString inputHatName="pvalue/"+inputSamples[jj]+Form("/mG=%.2f_GkM=%.2f_muhat.root",mX[jj][realidx], kappa);
	double nllfix, nllhat, mufix, muhat, xs;
	int statusfix=0, statushat=0;

	if(option.Contains("scalar")){
	  double actualWidth=kappa*mX[jj][realidx];
	  if(kappa==0) actualWidth=0.004;
	  inputFixName="pvalue/"+inputSamples[jj]+Form("/mX=%.2f_wX=%.4f_mufix.root",mX[jj][realidx], actualWidth);
	  inputHatName="pvalue/"+inputSamples[jj]+Form("/mX=%.2f_wX=%.4f_muhat.root",mX[jj][realidx], actualWidth);
	}

	if(option.Contains("txt")){
	  inputFixName.ReplaceAll(".root",".txt");
	  inputHatName.ReplaceAll(".root",".txt");

	  ifstream finfix(inputFixName), finhat(inputHatName);
	  if(!finfix||!finhat){
	    cout<<"Point "<<mX[jj][realidx]<<" does not exist."<<endl;
	    cout<<inputFixName<<" "<<inputHatName<<endl;
	    if(m_rigorous) getchar();
	    continue;
	  }
	  finfix>>xs>>nllfix>>statusfix;
	  finhat>>xs>>nllhat>>statushat;
	  finfix.close();
	  finhat.close();
	}
	else{
	  tfix = new TChain("toys/nllscan");
	  that = new TChain("toys/nllscan");

	  cout<<inputFixName<<endl;
	  cout<<inputHatName<<endl;
	  tfix->Add(inputFixName);
	  that->Add(inputHatName);
	  tfix->SetBranchAddress("nll", &nllfix);
	  tfix->SetBranchAddress("xs", &mufix);
	  tfix->SetBranchAddress("status", &statusfix);
	  
	  int fixSuccess=tfix->GetEntry(0);
	  
	  that->SetBranchAddress("nll", &nllhat);
	  that->SetBranchAddress("xs", &muhat);
	  that->SetBranchAddress("status", &statushat);
	  
	  int hatSuccess=that->GetEntry(0);

	  if(fixSuccess<=0||hatSuccess<=0){
	    cout<<"Point "<<mX[jj][realidx]<<" does not exist."<<endl;
	    if(m_rigorous) getchar();
	    continue;
	  }
	}
	cout<<"mX = "<<mX[jj][realidx]<<endl; 
	
	cout<<"++++++++++++ Fixed fit ++++++++++++++++"<<endl;
	cout<<"xs"<<" = "<<mufix<<endl;
	cout<<"NLL = "<<nllfix<<endl;
	cout<<"+++++++++++++++++++++++++++++++++++++++"<<endl;


	cout<<"++++++++++++ Float fit ++++++++++++++++"<<endl;
	cout<<"xs"<<" = "<<muhat<<endl;
	cout<<"NLL = "<<nllhat<<endl;
	cout<<"+++++++++++++++++++++++++++++++++++++++"<<endl;

	if((statusfix!=0&&statusfix!=1)||(statushat!=0&&statushat!=1)){
	  cout<<"Fitting problem with mass point "<<mX[jj][realidx]<<" in "<<inputSamples[jj]<<endl;
	  cout<<"Status fix "<<statusfix<<", status hat "<<statushat<<endl;
	  if(m_rigorous) getchar();
	  continue;
	}
	double DNLL=2*(nllfix-nllhat);
	int sign=(muhat>0)?1:-1;
	pvalue[jj][realidx]=1-ROOT::Math::normal_cdf(sign*sqrt(DNLL),1,0);
	if(!isfinite(pvalue[jj][realidx])) pvalue[jj][realidx]=0.5;
	if(option.Contains("capped") && pvalue[jj][realidx]>0.5) pvalue[jj][realidx]=0.5;
	// pvalue[jj][realidx]=RooStats::PValueToSignificance(pvalue[jj][realidx]);

	fout<<mX[jj][realidx]<<" "<<pvalue[jj][realidx]<<" "<<RooStats::PValueToSignificance(pvalue[jj][realidx])<<endl;

	if(pvalue[jj][realidx]<maxsignif){
	  maxsignif=pvalue[jj][realidx];
	  maxmG=mX[jj][realidx];
	}
	realidx++;
	SafeDelete(tfix);
	SafeDelete(that);
      }
      cout<<"Maximum significance: "<<maxsignif<<" at mX="<<maxmG<<" "<<RooStats::PValueToSignificance(maxsignif)<<endl;
      fout<<"Maximum significance: "<<maxsignif<<" at mX="<<maxmG<<" "<<RooStats::PValueToSignificance(maxsignif)<<endl;
      fout<<endl;
      npoint[jj]=realidx;
      if(RooStats::PValueToSignificance(maxsignif)>maxSignif){
	maxSignif=RooStats::PValueToSignificance(maxsignif);
	maxMass=maxmG;
      }
    }
    fout.close();
    c->cd();

    TGraph *gr[5];

    TLegend *leg=NULL;
    if(option.Contains("graviton")){
      // leg=FastLegend(x1+0.42, y1+0.07, x2-0.03, y1+0.12,0.04);
      leg=FastLegend(x1+0.25, y1+0.32, x1+0.45, y1+0.48, 0.045);
    }
    if(option.Contains("scalar")){
      leg=FastLegend(x1+0.03, y1+0.1, x1+0.25, y1+0.25,0.04);
    }
    if(option.Contains("hvt")) leg=FastLegend(x1+0.05, y1+0.1, x1+0.35, y1+0.25,0.045);
    if(option.Contains("jes")) leg=FastLegend(x2-0.35, y1+0.1, x2-0.05, y1+0.4,0.045);
    
    for(int jj=0;jj<nsample;jj++){
      gr[jj]=new TGraph(npoint[jj],mX[jj],pvalue[jj]);
      gr[jj]->SetLineColor(lineColor[jj]);
      if(jj==0){
	gr[jj]->SetLineStyle(1);
	gr[jj]->SetLineWidth(2);
	gr[jj]->SetMarkerSize(4);
	gr[jj]->SetMarkerStyle(1);
      }
      else{
	gr[jj]->SetLineStyle(2);
	gr[jj]->SetLineWidth(2);
	gr[jj]->SetMarkerSize(4);
	gr[jj]->SetMarkerStyle(1);
      }
      leg->AddEntry(gr[jj],legText[jj],"l");
      gr[jj]->Draw("L");
    }
    
    vector<TString> pavetext,pavetext2,pavetext3;

    if(option.Contains("atlaspub")) pavetext.push_back("#bf{#it{ATLAS}}");
    else if(option.Contains("atlasnote")) pavetext.push_back("#bf{#it{ATLAS}} Preliminary");
    else if(option.Contains("asimov")) pavetext.push_back("#bf{#it{ATLAS}} simulation internal");
    else pavetext.push_back("#bf{#it{ATLAS}} internal");

    if(option.Contains("8tev")){
      pavetext2.push_back("#sqrt{#it{s}} = 8 TeV, 20.3 fb^{-1}");
      // pavetext2.push_back("#sqrt{#it{s}} = 13 TeV, 3.2 fb^{-1}");
    }
    else if(option.Contains("1516")){
      pavetext2.push_back(Form("2015 - 2016"));
      pavetext2.push_back(Form("#sqrt{#it{s}} = 13 TeV, %.1f + %.1f fb^{-1}", luminosity2015, luminosity2016));
    }
    else if(option.Contains("2016")){
      pavetext2.push_back(Form("2016"));
      pavetext2.push_back(Form("#sqrt{#it{s}} = 13 TeV, %.1f fb^{-1}", luminosity2016));
    }
    else if(option.Contains("2015")){
      pavetext2.push_back(Form("2015"));
      pavetext2.push_back(Form("#sqrt{#it{s}} = 13 TeV, %.1f fb^{-1}", luminosity2015));
    }

    if(option.Contains("graviton")){
      if(option.Contains("loose")) pavetext2.push_back(Form("Spin-2 loose Selection"));
      else pavetext2.push_back(Form("Spin-2 Selection"));
      pavetext2.push_back(Form("G*#rightarrow#gamma#gamma, #it{k}/#bar{M}_{Pl} = %.2f", kappa));
    }
    else if(option.Contains("scalar")){
      pavetext2.push_back(Form("Spin-0 Selection"));
      if(kappa==0) pavetext2.push_back(Form("X#rightarrow#gamma#gamma, NWA"));
      else pavetext2.push_back(Form("X#rightarrow#gamma#gamma, #Gamma_{X} = %.0f%%m_{X}", kappa*100));
    }
    if(option.Contains("showmax")) pavetext3.push_back(Form("Max. significance %.1f#sigma at %.0f GeV", maxSignif, maxMass));    
    TLatex lsigma;
    lsigma.SetTextFont(42);
    lsigma.SetTextSize(0.04);
    // lsigma.SetTextColor(kRed);
    lsigma.DrawLatex(xmin-70, RooStats::SignificanceToPValue(0)*1.1, "0#sigma");
    lsigma.DrawLatex(xmin-70, RooStats::SignificanceToPValue(1)*1.1, "1#sigma");
    lsigma.DrawLatex(xmin-70, RooStats::SignificanceToPValue(2)*1.1, "2#sigma");
    
    CommonFunc::DrawConstantLine(c, RooStats::SignificanceToPValue(0), xmin, xmax, kGray, 5, 2);
    CommonFunc::DrawConstantLine(c, RooStats::SignificanceToPValue(1), xmin, xmax, kGray, 5, 2);
    CommonFunc::DrawConstantLine(c, RooStats::SignificanceToPValue(2), xmin, xmax, kGray, 5, 2);

    if(!option.Contains("8tev")){
      lsigma.DrawLatex(xmin-70, RooStats::SignificanceToPValue(3)*1.1, "3#sigma");
      lsigma.DrawLatex(xmin-70, RooStats::SignificanceToPValue(4)*1.1, "4#sigma");
      // lsigma.DrawLatex(xmax+20, RooStats::SignificanceToPValue(5)*0.8, "5#sigma");
      
      CommonFunc::DrawConstantLine(c, RooStats::SignificanceToPValue(3), xmin, xmax, kGray, 5, 2);
      CommonFunc::DrawConstantLine(c, RooStats::SignificanceToPValue(4), xmin, xmax, kGray, 5, 2);
      // CommonFunc::DrawConstantLine(c, RooStats::SignificanceToPValue(5), xmin, xmax, kGreen+1, 5, 2);
    }
    // TPaveText* text1=CreatePaveText(x1+0.01,y1+0.01,x1+0.4,y1+0.25,pavetext1,0.045);
    TPaveText* text1=CreatePaveText(x1+0.4,y1+0.3,x2-0.03,y1+0.35,pavetext,0.04);
    //TPaveText* text2=CreatePaveText(x2-0.4,y2-0.2,x2-0.01,y2-0.03,pavetext2,0.045);
    // TPaveText* text2=CreatePaveText(x1+0.03,y2-0.2,x1+0.4,y2-0.05,pavetext2,0.045);
    TPaveText* text2=CreatePaveText(x1+0.4,y1+0.08,x2-0.03,y1+0.29,pavetext2,0.04);
    TPaveText* text3=CreatePaveText(x1+0.3,y1+0.02,x2-0.03,y1+0.06,pavetext3,0.04);

    // legend->AddEntry(&markerSM, "SM","P");
    c->cd();
    c->SetLogy();
    text1->Draw("same");
    text2->Draw("same");
    text3->Draw("same");
    leg->Draw("same");
    c->Update();
    c->RedrawAxis();
    //c->SetGrid();
    if(option.Contains("logx")){
      hframe->GetXaxis()->SetNdivisions(1010);
      c->SetLogx();
    }
    system("mkdir -vp fig/pvalue/"+jobname);
    PrintCanvas(c, Form("fig/pvalue/"+jobname+"/pvalue_plot_%.2f", kappa));

  }
  //************************************************************************************==
  if(Opt["PR1D"]){
    if(argc<4){
      cout<<"Usage: "<<argv[0]<<" "<<argv[1]<<" <jobname> <kappa> <analysis> <option>"<<endl;
      return 0;
    }
    TString jobname=argv[2];
    double kappa=atof(argv[3]);
    TString analysis=argv[4];
    TString option=argv[5];
    
    vector<TString> inputSamples, legText;
    vector<int> lineColor, lineStyle;
    vector<double> lineWidth;

    if(analysis=="graviton"){
      if(option.Contains("mt")){
	inputSamples.push_back("high_mass_diphoton_2015_Graviton_13TeV_histfactory_EKHI_v19_207_2dpvalue_binned_strat0");
	legText.push_back("2015");
	lineColor.push_back(kBlue);
	lineWidth.push_back(2.5);
	lineStyle.push_back(1);
	
	inputSamples.push_back("high_mass_diphoton_2016_Graviton_13TeV_histfactory_EKHI_v19_207_2dpvalue_binned_strat0");
	legText.push_back("2016");
	lineColor.push_back(kRed);
	lineWidth.push_back(2.5);
	lineStyle.push_back(1);
	
	if(option.Contains("combined")){
	  inputSamples.push_back("high_mass_diphoton_1516_Graviton_13TeV_histfactory_EKHI_v19_207_2dpvalue_binned_strat0");
	  legText.push_back("Combined");
	  lineColor.push_back(kBlack);
	  lineWidth.push_back(3);
	  lineStyle.push_back(1);
	}
      }
      if(option.Contains("fb")){
	inputSamples.push_back("high_mass_diphoton_2015_Graviton_13TeV_2D_EKHI_v19_2dpvalue");
	legText.push_back("2015");
	lineColor.push_back(kBlue);
	lineWidth.push_back(2.5);
	lineStyle.push_back(1);
	
	inputSamples.push_back("high_mass_diphoton_2016_Graviton_13TeV_2D_EKHI_v19_2dpvalue");
	legText.push_back("2016");
	lineColor.push_back(kRed);
	lineWidth.push_back(2.5);
	lineStyle.push_back(1);
	
	if(option.Contains("combined")){
	  inputSamples.push_back("high_mass_diphoton_1516_Graviton_13TeV_2D_EKHI_v19_2dpvalue");
	  legText.push_back("Combined");
	  lineColor.push_back(kBlack);
	  lineWidth.push_back(3);
	  lineStyle.push_back(1);
	}
      }
    }
    else if(analysis=="gravitonloose"){
      if(option.Contains("mt")){
	inputSamples.push_back("high_mass_diphoton_2015_Graviton_13TeV_histfactory_EKEI_v19_2dpvalue_binned_strat0");
	legText.push_back("2015");
	lineColor.push_back(kBlue);
	lineWidth.push_back(2.5);
	lineStyle.push_back(1);
	
	inputSamples.push_back("high_mass_diphoton_2016_Graviton_13TeV_histfactory_EKEI_v19_2dpvalue_binned_strat0");
	legText.push_back("2016");
	lineColor.push_back(kRed);
	lineWidth.push_back(2.5);
	lineStyle.push_back(1);
	
	if(option.Contains("combined")){
	  inputSamples.push_back("high_mass_diphoton_1516_Graviton_13TeV_histfactory_EKEI_v19_2dpvalue_binned_strat0");
	  legText.push_back("Combined");
	  lineColor.push_back(kBlack);
	  lineWidth.push_back(3);
	  lineStyle.push_back(1);
	}
      }
      if(option.Contains("fb")){
	inputSamples.push_back("high_mass_diphoton_2015_Graviton_13TeV_2D_EKEI_v19_2dpvalue");
	legText.push_back("2015");
	lineColor.push_back(kBlue);
	lineWidth.push_back(2.5);
	lineStyle.push_back(1);
	
	inputSamples.push_back("high_mass_diphoton_2016_Graviton_13TeV_2D_EKEI_v19_2dpvalue");
	legText.push_back("2016");
	lineColor.push_back(kRed);
	lineWidth.push_back(2.5);
	lineStyle.push_back(1);
	
	if(option.Contains("combined")){
	  inputSamples.push_back("high_mass_diphoton_1516_Graviton_13TeV_2D_EKEI_v19_2dpvalue");
	  legText.push_back("Combined");
	  lineColor.push_back(kBlack);
	  lineWidth.push_back(3);
	  lineStyle.push_back(1);
	}
      }
    }
    else if(analysis=="scalar"){
      if(option.Contains("fb")){
	inputSamples.push_back("high_mass_diphoton_2015_Scalar_13TeV_2D_v14_2dpvalue");
	legText.push_back("2015");
	lineColor.push_back(kBlue);
	lineWidth.push_back(2.5);
	lineStyle.push_back(1);
      
	inputSamples.push_back("high_mass_diphoton_2016_Scalar_13TeV_2D_v14_2dpvalue");
	legText.push_back("2016");
	lineColor.push_back(kRed);
	lineWidth.push_back(2.5);
	lineStyle.push_back(1);

	if(option.Contains("combined")){
	  inputSamples.push_back("high_mass_diphoton_1516_Scalar_13TeV_2D_v14_2dpvalue");
	  legText.push_back("Combined");
	  lineColor.push_back(kBlack);
	  lineWidth.push_back(3);
	  lineStyle.push_back(1);
	}
      }
      if(option.Contains("mt")){
	inputSamples.push_back("high_mass_diphoton_2015_Scalar_13TeV_histfactory_HKHI_v14_2dpvalue");
	legText.push_back("2015");
	lineColor.push_back(kBlue);
	lineWidth.push_back(2.5);
	lineStyle.push_back(1);
      
	inputSamples.push_back("high_mass_diphoton_2016_Scalar_13TeV_histfactory_HKHI_v14_2dpvalue");
	legText.push_back("2016");
	lineColor.push_back(kRed);
	lineWidth.push_back(2.5);
	lineStyle.push_back(1);

	if(option.Contains("combined")){
	  inputSamples.push_back("high_mass_diphoton_1516_Scalar_13TeV_histfactory_HKHI_v14_2dpvalue");
	  legText.push_back("Combined");
	  lineColor.push_back(kBlack);
	  lineWidth.push_back(3);
	  lineStyle.push_back(1);
	}
      }
    }
    else{
      cerr<<"Unknown analysis type "<<analysis<<". Exiting..."<<endl;
      return -1;
    }

    int nsample=inputSamples.size();

    bool m_rigorous=option.Contains("rigorous");
    
    vector<double> massPoints;

    if(analysis.Contains("scalar")){
      if(option.Contains("mt")) for(int mass=250; mass<=2000; mass+=10) massPoints.push_back(mass);
      else for(int mass=200; mass<=2000; mass+=10) massPoints.push_back(mass);
    }
    else if(analysis.Contains("graviton")) for(int mass=500; mass<=2000; mass+=10) massPoints.push_back(mass);

    double xmin=massPoints[0], xmax=massPoints.back();

    int npointx=massPoints.size();
    
    TCanvas* c = CreateCanvas("c", "pvalue",800,600);
    // c->SetRightMargin(0.1);
    double x1,y1,x2,y2;
    GetX1Y1X2Y2(c,x1,y1,x2,y2);

    TH1D *hframe = new TH1D(jobname, jobname, npointx, xmin-120, xmax+120);

    TString xLabel="", yLabel="";
    if(analysis.Contains("scalar")){
      xLabel="m_{X} [GeV]";
    }
    else if(analysis.Contains("graviton")){
      xLabel="m_{G*} [GeV]";
    }
    
    hframe->GetXaxis()->SetTitle(xLabel);
    // hframe->GetYaxis()->SetTitle("Local #it{p}_{0}");
    hframe->GetYaxis()->SetTitle("p-value");
    hframe->GetXaxis()->SetTitleSize(0.06);
    hframe->GetYaxis()->SetTitleSize(0.06);
    hframe->GetXaxis()->SetTitleOffset(1);
    hframe->GetYaxis()->SetTitleOffset(0.95);
    hframe->SetLineWidth(0);
    hframe->SetMaximum(2);
    hframe->SetMinimum(1e-5);
    if(option.Contains("5sigma")) hframe->SetMinimum(RooStats::SignificanceToPValue(5));
    TString outputDir="fig/pvalue/"+jobname;
    system("mkdir -vp fig/pvalue/"+jobname);

    hframe->Draw();

    double pvalue[5][10000], mX[5][10000];
    int npoint[5];

    ofstream fout(Form("fig/pvalue/"+jobname+"/summary_%.2f.txt", kappa));

    double maxSignif=-1;
    for(int jj=0;jj<nsample;jj++){
      int realidx=0;
      double maxsignif=1, maxmG=0, maxGkM=0;
      for(Int_t i = 0; i < npointx; i++){
	mX[jj][realidx]=massPoints[i];

	TChain* tfix = new TChain("toys/nllscan");
	TChain* that = new TChain("toys/nllscan");

	TString inputFixName="pvalue/"+inputSamples[jj]+Form("/mG=%.2f_GkM=%.2f_mufix.root",mX[jj][realidx], kappa);
	TString inputHatName="pvalue/"+inputSamples[jj]+Form("/mG=%.2f_GkM=%.2f_muhat.root",mX[jj][realidx], kappa);

	if(analysis.Contains("scalar")){
	  double actualWidth=kappa*mX[jj][realidx];
	  if(kappa==0) actualWidth=0.004;
	  inputFixName="pvalue/"+inputSamples[jj]+Form("/mX=%.2f_wX=%.4f_mufix.root",mX[jj][realidx], actualWidth);
	  inputHatName="pvalue/"+inputSamples[jj]+Form("/mX=%.2f_wX=%.4f_muhat.root",mX[jj][realidx], actualWidth);
	}
	cout<<inputFixName<<endl;
	cout<<inputHatName<<endl;
	tfix->Add(inputFixName);
	that->Add(inputHatName);
	double nllfix, nllhat, mufix, muhat;
	int statusfix, statushat;
	tfix->SetBranchAddress("nll", &nllfix);
	tfix->SetBranchAddress("xs", &mufix);
	tfix->SetBranchAddress("status", &statusfix);
	
	int fixSuccess=tfix->GetEntry(0);

	that->SetBranchAddress("nll", &nllhat);
	that->SetBranchAddress("xs", &muhat);
	that->SetBranchAddress("status", &statushat);
	
	int hatSuccess=that->GetEntry(0);

	if(fixSuccess<=0||hatSuccess<=0){
	  cout<<"Point "<<mX[jj][realidx]<<" does not exist."<<endl;
	  if(m_rigorous) getchar();
	  continue;
	}
	cout<<"mX = "<<mX[jj][realidx]<<endl; 
	
	cout<<"++++++++++++ Fixed fit ++++++++++++++++"<<endl;
	cout<<"xs"<<" = "<<mufix<<endl;
	cout<<"NLL = "<<nllfix<<endl;
	cout<<"+++++++++++++++++++++++++++++++++++++++"<<endl;


	cout<<"++++++++++++ Float fit ++++++++++++++++"<<endl;
	cout<<"xs"<<" = "<<muhat<<endl;
	cout<<"NLL = "<<nllhat<<endl;
	cout<<"+++++++++++++++++++++++++++++++++++++++"<<endl;

	if((statusfix!=0&&statusfix!=1)||(statushat!=0&&statushat!=1)){
	  cout<<"Fitting problem with mass point "<<mX[jj][realidx]<<" in "<<inputSamples[jj]<<endl;
	  cout<<"Status fix "<<statusfix<<", status hat "<<statushat<<endl;
	  if(m_rigorous) getchar();
	  continue;
	}
	double DNLL=2*(nllfix-nllhat);
	int sign=(muhat>0)?1:-1;
	pvalue[jj][realidx]=1-ROOT::Math::normal_cdf(sign*sqrt(DNLL),1,0);
	if(!isfinite(pvalue[jj][realidx])) pvalue[jj][realidx]=0.5;
	if(option.Contains("capped") && pvalue[jj][realidx]>0.5) pvalue[jj][realidx]=0.5;
	// pvalue[jj][realidx]=RooStats::PValueToSignificance(pvalue[jj][realidx]);

	fout<<mX[jj][realidx]<<" "<<pvalue[jj][realidx]<<endl;

	if(pvalue[jj][realidx]<maxsignif){
	  maxsignif=pvalue[jj][realidx];
	  maxmG=mX[jj][realidx];
	}
	realidx++;
	SafeDelete(tfix);
	SafeDelete(that);
      }
      cout<<"Maximum significance: "<<maxsignif<<" at mX="<<maxmG<<" "<<RooStats::PValueToSignificance(maxsignif)<<endl;
      fout<<"Maximum significance: "<<maxsignif<<" at mX="<<maxmG<<" "<<RooStats::PValueToSignificance(maxsignif)<<endl;
      fout<<endl;
      npoint[jj]=realidx;
      if(RooStats::PValueToSignificance(maxsignif)>maxSignif) maxSignif=RooStats::PValueToSignificance(maxsignif);
    }
    fout.close();
    c->cd();

    TGraph *gr[5];

    TLegend *leg=NULL;
    if(analysis.Contains("graviton")){
      // leg=FastLegend(x1+0.42, y1+0.07, x2-0.03, y1+0.12,0.04);
      leg=FastLegend(x1+0.25, y1+0.32, x1+0.45, y1+0.48, 0.05);
    }
    if(analysis.Contains("scalar")){
      leg=FastLegend(x1+0.05, y1+0.1, x1+0.25, y1+0.25,0.05);
    }
    
    for(int jj=0;jj<nsample;jj++){
      gr[jj]=new TGraph(npoint[jj],mX[jj],pvalue[jj]);
      gr[jj]->SetLineColor(lineColor[jj]);
      gr[jj]->SetLineStyle(lineStyle[jj]);
      gr[jj]->SetLineWidth(lineWidth[jj]);
      leg->AddEntry(gr[jj],legText[jj],"l");
      gr[jj]->Draw("L");
    }
    
    vector<TString> pavetext,pavetext2;


    if(analysis=="graviton"){
      pavetext.push_back(Form("Spin-2 Selection"));
      pavetext.push_back(Form("G*#rightarrow#gamma#gamma, #it{k}/#bar{M}_{Pl} = %.2f", kappa));

      if(option.Contains("atlaspub")) pavetext2.push_back("#bf{#it{ATLAS}}");
      else if(option.Contains("atlasnote")) pavetext2.push_back("#bf{#it{ATLAS}} Preliminary");
      else if(option.Contains("asimov")) pavetext2.push_back("#bf{#it{ATLAS}} simulation internal");
      else pavetext2.push_back("#bf{#it{ATLAS}} internal");

      pavetext2.push_back(Form("Data 2015, #sqrt{#it{s}} = 13 TeV, %.1f fb^{-1}", luminosity2015));
      pavetext2.push_back(Form("Data 2016, #sqrt{#it{s}} = 13 TeV, %.1f fb^{-1}", luminosity2016));

    }
    else if(analysis=="gravitonloose"){
      if(option.Contains("atlaspub")) pavetext.push_back("#bf{#it{ATLAS}}");
      else if(option.Contains("atlasnote")) pavetext.push_back("#bf{#it{ATLAS}} Preliminary");
      else if(option.Contains("asimov")) pavetext.push_back("#bf{#it{ATLAS}} simulation internal");
      else pavetext.push_back("#bf{#it{ATLAS}} internal");
      pavetext2.push_back(Form("Data 2015, #sqrt{#it{s}} = 13 TeV, %.1f fb^{-1}", luminosity2015));
      pavetext2.push_back(Form("Data 2016, #sqrt{#it{s}} = 13 TeV, %.1f fb^{-1}", luminosity2016));
      pavetext2.push_back(Form("Spin-2 Loose Selection"));
      pavetext.push_back(Form("G*#rightarrow#gamma#gamma, #it{k}/#bar{M}_{Pl} = %.2f", kappa));
    }

    else if(analysis=="scalar"){
      if(option.Contains("atlaspub")) pavetext.push_back("#bf{#it{ATLAS}}");
      else if(option.Contains("atlasnote")) pavetext.push_back("#bf{#it{ATLAS}} Preliminary");
      else if(option.Contains("asimov")) pavetext.push_back("#bf{#it{ATLAS}} simulation internal");
      else pavetext.push_back("#bf{#it{ATLAS}} internal");
      pavetext2.push_back(Form("Data 2015, #sqrt{#it{s}} = 13 TeV, %.1f fb^{-1}", luminosity2015));
      pavetext2.push_back(Form("Data 2016, #sqrt{#it{s}} = 13 TeV, %.1f fb^{-1}", luminosity2016));
      pavetext2.push_back(Form("Spin-0 Selection"));
      if(kappa==0) pavetext2.push_back(Form("X#rightarrow#gamma#gamma, NWA"));
      else pavetext2.push_back(Form("X#rightarrow#gamma#gamma, #Gamma_{X} = %.0f%%m_{X}", kappa*100));
    }
    
    TLatex lsigma;
    lsigma.SetTextFont(42);
    lsigma.SetTextSize(0.04);
    // lsigma.SetTextColor(kRed);
    lsigma.DrawLatex(xmin-70, RooStats::SignificanceToPValue(0)*1.1, "0#sigma");
    lsigma.DrawLatex(xmin-70, RooStats::SignificanceToPValue(1)*1.1, "1#sigma");
    lsigma.DrawLatex(xmin-70, RooStats::SignificanceToPValue(2)*1.1, "2#sigma");
    lsigma.DrawLatex(xmin-70, RooStats::SignificanceToPValue(3)*1.1, "3#sigma");
    lsigma.DrawLatex(xmin-70, RooStats::SignificanceToPValue(4)*1.1, "4#sigma");
    
    CommonFunc::DrawConstantLine(c, RooStats::SignificanceToPValue(0), xmin, xmax, kGray, 5, 2);
    CommonFunc::DrawConstantLine(c, RooStats::SignificanceToPValue(1), xmin, xmax, kGray, 5, 2);
    CommonFunc::DrawConstantLine(c, RooStats::SignificanceToPValue(2), xmin, xmax, kGray, 5, 2);
    CommonFunc::DrawConstantLine(c, RooStats::SignificanceToPValue(3), xmin, xmax, kGray, 5, 2);
    CommonFunc::DrawConstantLine(c, RooStats::SignificanceToPValue(4), xmin, xmax, kGray, 5, 2);

    TPaveText* text1=NULL, *text2=NULL;
    if(analysis=="scalar"){
      text1=CreatePaveText(x1+0.35,y1+0.3,x2-0.03,y1+0.35,pavetext,0.04);
      text2=CreatePaveText(x1+0.35,y1+0.08,x2-0.03,y1+0.29,pavetext2,0.04);
    }
    if(analysis=="gravitonloose"){
      text1=CreatePaveText(x1+0.35,y1+0.2,x2-0.03,y1+0.3,pavetext,0.04);
      text2=CreatePaveText(x1+0.35,y1+0.04,x2-0.03,y1+0.2,pavetext2,0.04);
    }
    else if(analysis.Contains("graviton")){
      text1=CreatePaveText(x1+0.05,y1+0.08,x2-0.03,y1+0.2,pavetext,0.04);
      text2=CreatePaveText(x1+0.35,y1+0.08,x2-0.03,y1+0.25,pavetext2,0.04);
    }
    c->cd();
    c->SetLogy();
    text1->Draw("same");
    text2->Draw("same");
    leg->Draw("same");
    c->Update();
    c->RedrawAxis();
    //c->SetGrid();
    if(option.Contains("logx")){
      hframe->GetXaxis()->SetNdivisions(1010);
      c->SetLogx();
    }
    system("mkdir -vp fig/pvalue/"+jobname);
    TString outputCanvas=Form("fig/pvalue/"+jobname+"/pvalue_summary_plot_%.2f", kappa);
    if(option.Contains("combined")) outputCanvas+="_combined";
    PrintCanvas(c, outputCanvas);

  }
  //************************************************************************************==
}
