#include "frame.h"

using namespace std;
using namespace CommonFunc;
using namespace RooStats;

double epsilon=1e-6;

double mass_HVT_Agv1_XS[25]={500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2200,2400,2600,2800,3000,3500,4000,4500,5000};
double HVT_Agv1_XS_WW[25]={4394,2039,1065,604.8,365.0,230.7,151.2,102.1,70.63,49.84,35.79,26.08,19.24,14.36,10.82,8.227,4.861,2.943,1.818,1.141,0.7256,0.2439,0.08185,0.03025,0.01083};
double HVT_Agv1_XS_ZH[25]={3556,1743,946,551.7,339.6,217.9,144.6,98.55,68.71,48.81,35.25,25.81,19.13,14.34,10.84,8.271,4.916,2.994,1.859,1.173,0.7497,0.25538,0.09049,0.03274,0.01198};
double HVT_Agv1_XS_WZ[25]={9159,4225,2201,1248,753.9,477.7,314.1,212.7,147.7,104.7,75.5,55.2,40.9,30.6,23.14,17.65,10.48,6.37,3.95,2.48,1.58,0.5305,0.1842,0.06487,0.02297};
double HVT_Agv1_XS_WH[25]={6532,3280,1813,1073,668.4,433.4,290.1,199.5,140.1,100.2,72.83,53.67,39.99,30.12,22.89,17.53,10.49,6.427,4.008,2.537,1.624,0.5534,0.1953,0.07015,0.02543};

double HVT_Agv1_XS_VV[25];

double mass_HVT_Bgv3_XS[21]={900,1000,1100,1200,
			     1300,1400,1500,1600,1700,
			     1800,1900,2000,2200,2400,
			     2600,2800,3000,3500,4000,4500,5000};
double HVT_Bgv3_XS_WW[21]={302.5,230.0,170.0,125.0,92.19,68.40,51.10,38.45,29.14,22.22,17.04,13.149,7.940,4.876,3.035,1.9106,1.2134,0.40156,0.13610,0.046519,0.015831};
double HVT_Bgv3_XS_ZH[21]={367.7,264.1,188.8,135.8,98.64,72.36,53.60,40.06,30.20,22.92,17.52,13.479,8.102,4.958,3.078,1.9337,1.2261,0.40461,0.13689,0.046730,0.015889};
double HVT_Bgv3_XS_WZ[21]={592.5,454.6,338.3,250.5,186.1,139.0,104.6,79.30,60.51,46.47,35.90,27.871,17.04,10.57,6.637,4.2057,2.6831,0.88812,0.29604,0.097651,0.031427};
double HVT_Bgv3_XS_WH[21]={685.7,501.6,363.4,264.6,194.3,144.0,107.7,81.28,61.81,47.33,36.48,28.271,17.23,10.67,6.689,4.2336,2.6984,0.89176,0.29695,0.097886,0.031487};

double HVT_Bgv3_XS_VV[21];

double mass_RSG_XS[25]={500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2200,2400,2600,2800,3000,3500,4000,4500,5000};
double RSG_XS_WW[25]={4.63,1.565,0.6438,0.3011,0.1544,0.08461,0.04883,0.02936,0.01827,0.01169,0.007655,0.005113,0.003474,0.002397,0.001676,0.001185,0.0006115,0.0003263,0.0001788,0.0001,5.703e-05,1.486e-05,4.114e-06,1.189e-06,3.579e-07};
double RSG_XS_ZZ[25]={2.474,0.822,0.3339,0.155,0.07899,0.0431,0.02481,0.01488,0.009243,0.005904,0.003863,0.002577,0.001749,0.001206,0.0008427,0.0005957,0.0003071,0.0001638,8.966e-05,5.016e-05,2.859e-05,7.447e-06,2.06e-06,5.955e-07,1.793e-07};

double RSG_XS_VV[25];

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

    TString option=argv[3];
    option.ToLower();

    convertToPb(25, HVT_Agv1_XS_WZ);
    convertToPb(25, HVT_Agv1_XS_WW);
    
    convertToPb(21, HVT_Bgv3_XS_WZ);
    convertToPb(21, HVT_Bgv3_XS_WW);

    mergeXS(25, HVT_Agv1_XS_VV, HVT_Agv1_XS_WZ, HVT_Agv1_XS_WW);
    mergeXS(21, HVT_Bgv3_XS_VV, HVT_Bgv3_XS_WZ, HVT_Bgv3_XS_WW);

    mergeXS(25, RSG_XS_VV, RSG_XS_WW, RSG_XS_ZZ);
    
    TString type;
    TString fileName[5], legText[5], scaleOpt[5];
    int nsample=1;

    double mass[5][200], mass_for_plot[5][200];
    double N2S[5][200],N1S[5][200],P1S[5][200],P2S[5][200],Median[5][200],Zero[5][200],Observed[5][200];
    vector<int> temp;
    TCanvas *cv = CreateCanvas("canvas", "",800,600);
    double x1,y1,x2,y2;
    GetX1Y1X2Y2(cv,x1,y1,x2,y2);

    int nmass[5];
    double xmin, xmax, ymin, ymax;

    TGraph *gr_HVT_Agv1_XS_WZ=new TGraph(25, mass_HVT_Agv1_XS, HVT_Agv1_XS_WZ); gr_HVT_Agv1_XS_WZ->SetLineColor(kRed); gr_HVT_Agv1_XS_WZ->SetLineStyle(1); gr_HVT_Agv1_XS_WZ->SetLineWidth(3);
    TGraph *gr_HVT_Agv1_XS_WW=new TGraph(25, mass_HVT_Agv1_XS, HVT_Agv1_XS_WW); gr_HVT_Agv1_XS_WW->SetLineColor(kRed); gr_HVT_Agv1_XS_WW->SetLineStyle(1); gr_HVT_Agv1_XS_WW->SetLineWidth(3);
    TGraph *gr_HVT_Agv1_XS_VV=new TGraph(25, mass_HVT_Agv1_XS, HVT_Agv1_XS_VV); gr_HVT_Agv1_XS_VV->SetLineColor(kRed); gr_HVT_Agv1_XS_VV->SetLineStyle(1); gr_HVT_Agv1_XS_VV->SetLineWidth(3);

    TGraph *gr_HVT_Bgv3_XS_WZ=new TGraph(21, mass_HVT_Bgv3_XS, HVT_Bgv3_XS_WZ); gr_HVT_Bgv3_XS_WZ->SetLineColor(kMagenta+2); gr_HVT_Bgv3_XS_WZ->SetLineStyle(1); gr_HVT_Bgv3_XS_WZ->SetLineWidth(3);
    TGraph *gr_HVT_Bgv3_XS_WW=new TGraph(21, mass_HVT_Bgv3_XS, HVT_Bgv3_XS_WW); gr_HVT_Bgv3_XS_WW->SetLineColor(kMagenta+2); gr_HVT_Bgv3_XS_WW->SetLineStyle(1); gr_HVT_Bgv3_XS_WW->SetLineWidth(3);
    TGraph *gr_HVT_Bgv3_XS_VV=new TGraph(21, mass_HVT_Bgv3_XS, HVT_Bgv3_XS_VV); gr_HVT_Bgv3_XS_VV->SetLineColor(kMagenta+2); gr_HVT_Bgv3_XS_VV->SetLineStyle(1); gr_HVT_Bgv3_XS_VV->SetLineWidth(3);

    TGraph *gr_RSG_XS_WW=new TGraph(25, mass_RSG_XS, RSG_XS_WW); gr_RSG_XS_WW->SetLineColor(kRed); gr_RSG_XS_WW->SetLineStyle(1); gr_RSG_XS_WW->SetLineWidth(3);
    TGraph *gr_RSG_XS_ZZ=new TGraph(25, mass_RSG_XS, RSG_XS_ZZ); gr_RSG_XS_ZZ->SetLineColor(kRed); gr_RSG_XS_ZZ->SetLineStyle(1); gr_RSG_XS_ZZ->SetLineWidth(3);
    TGraph *gr_RSG_XS_VV=new TGraph(25, mass_RSG_XS, RSG_XS_VV); gr_RSG_XS_VV->SetLineColor(kRed); gr_RSG_XS_VV->SetLineStyle(1); gr_RSG_XS_VV->SetLineWidth(3);

    vector<TString> pavetext, pavetext2;

    if(option.Contains("hvt_wz")){
      pavetext.push_back("HVT#rightarrowWZ");
      pavetext.push_back("llqq+lvqq+vvqq+qqqq");
    }
    else if(option.Contains("hvt_ww")){
      pavetext.push_back("HVT#rightarrowWW");
      pavetext.push_back("lvqq");
    }
    else if(option.Contains("hvt_comb")){
      pavetext.push_back("HVT#rightarrowWZ/WW");
      pavetext.push_back("llqq+lvqq+vvqq+qqqq");
    }
    else if(option.Contains("rsg_ww")){
      if(option.Contains("scalexs")){
	pavetext.push_back("G#rightarrowWW");
	pavetext.push_back("lvqq+qqqq");
      }
      else{
	pavetext.push_back("G#rightarrowWW  lvqq+qqqq");
      }
    }
    else if(option.Contains("rsg_zz")){
      if(option.Contains("scalexs")){
	pavetext.push_back("G#rightarrowZZ");
	pavetext.push_back("llqq+vvqq+qqqq");
      }
      else{
	pavetext.push_back("G#rightarrowZZ  llqq+vvqq+qqqq");
      }
    }
    else if(option.Contains("rsg_comb")){
      if(option.Contains("scalexs")){
	pavetext.push_back("G#rightarrowWW/ZZ");
	pavetext.push_back("llqq+lvqq+vvqq+qqqq");
      }
      else{
	pavetext.push_back("G#rightarrowWW/ZZ  llqq+lvqq+vvqq+qqqq");
      }
    }
    if(option.Contains("note")){
      if(option.Contains("printnum")){
	pavetext2.push_back("#bf{#it{ATLAS}}");
	pavetext2.push_back("preliminary");
      }
      else{
	pavetext2.push_back("#bf{#it{ATLAS}} preliminary");
      }
    }
    else if(option.Contains("paper")) pavetext2.push_back("#bf{#it{ATLAS}}");
    else{
      if(option.Contains("printnum")){
	pavetext2.push_back("#bf{#it{ATLAS}}");
	pavetext2.push_back("internal");
      }
      else{
	pavetext2.push_back("#bf{#it{ATLAS}} internal");
      }
    }
    pavetext2.push_back("#sqrt{#it{s}} = 13 TeV, 3.2 fb^{-1}");

    for(int Mass=500;Mass<2000;Mass+=100) temp.push_back(Mass);
    for(int Mass=2000;Mass<=3000;Mass+=200) temp.push_back(Mass);

    xmin=500;
    xmax=3000;
      
    if(option.Contains("hvt")){
      ymin=1e-3;
      ymax=1.1e2;
      if(option.Contains("scalexs")){
	ymin=5e-3;
	ymax=10;
      }
      if(option.Contains("hvt_wz")){
	fileName[0]="lvqq_HVT_WZ_20160216";          legText[0]="\"W/o smoothing\"";      scaleOpt[0]="hvt_wz";
	fileName[1]="lvqq_HVT_WZ_smooth_20160216";   legText[1]="\"W/ smoothing\"";          scaleOpt[1]="hvt_wz";
	nsample=2;
      }
      if(option.Contains("hvt_ww")){
	fileName[0]="lvqq_HVT_WW_20160224";          legText[0]="\"W/o smoothing\"";      scaleOpt[0]="hvt_wz";
	fileName[1]="lvqq_HVT_WW_smooth_20160224";   legText[1]="\"W/ smoothing\"";          scaleOpt[1]="hvt_wz";
	nsample=2;				     			       
      }						     			       
      if(option.Contains("hvt_comb")){
	fileName[0]="llqq_HVT_WZ_20160126";          legText[0]="llqq";          scaleOpt[0]="hvt_comb";
	fileName[1]="lvqq_HVT_comb_20160126";	     legText[1]="l#nuqq";        scaleOpt[1]="hvt_comb";
	fileName[2]="vvqq_HVT_WZ_20160126";	     legText[2]="#nu#nuqq";      scaleOpt[2]="hvt_comb";
	fileName[3]="qqqq_HVT_comb_20160126";	     legText[3]="qqqq";          scaleOpt[3]="hvt_comb";
	fileName[4]="combined_VV_HVT_comb_20160126"; legText[4]="Combined";      scaleOpt[4]="hvt_comb";
	nsample=5;
      }
    }
    else if(option.Contains("rsg")){
      ymin=0.1;
      ymax=5e3;
      if(option.Contains("scalexs")){
	ymin=5e-3;
	ymax=10;
      }
      if(option.Contains("rsg_zz")){
	fileName[0]="llqq_RSG_ZZ_20160126";            legText[0]="llqq";          scaleOpt[0]="rsg_zz";
	// fileName[1]="vvqq_RSG_ZZ_20160126";	       legText[1]="#nu#nuqq";      scaleOpt[1]="rsg_zz";
	fileName[1]="qqqq_RSG_ZZ_20160126";	       legText[1]="qqqq";          scaleOpt[1]="rsg_zz";
	fileName[2]="combined_VV_RSG_ZZ_20160126";     legText[2]="Combined";      scaleOpt[2]="rsg_zz";  
	nsample=3;				       			       
      }
      if(option.Contains("rsg_ww")){
	fileName[0]="lvqq_RSG_WW_20160126";            legText[0]="l#nuqq";        scaleOpt[0]="rsg_ww";
	fileName[1]="qqqq_RSG_WW_20160126";	       legText[1]="qqqq";          scaleOpt[1]="rsg_ww";
	fileName[2]="combined_VV_RSG_WW_20160126";     legText[2]="Combined";      scaleOpt[2]="rsg_ww";
	nsample=3;				       			       
      }						       			       
      if(option.Contains("rsg_comb")){
	fileName[0]="llqq_RSG_ZZ_20160126";            legText[0]="llqq";              scaleOpt[0]="rsg_comb";
	fileName[1]="lvqq_RSG_WW_20160126";	       legText[1]="l#nuqq";  	       scaleOpt[1]="rsg_comb";
	// fileName[2]="vvqq_RSG_ZZ_20160126";	       legText[2]="#nu#nuqq";	       scaleOpt[2]="rsg_comb";
	fileName[2]="qqqq_RSG_comb_20160126";	       legText[2]="qqqq";    	       scaleOpt[2]="rsg_comb";
	fileName[3]="combined_VV_RSG_comb_20160126";   legText[3]="Combined";	       scaleOpt[3]="rsg_comb";
	nsample=4;
      }
    }

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

	TString infile=Form("limit/%s/%s_%3.3d.txt", fileName[jj].Data(), fileName[jj].Data(), (int)mass[jj][idx]);
	ifstream fin(infile.Data(),ios::in);
	if(!fin){
	  cerr<<"File "<<infile.Data()<<" does not exist."<<endl;
	  continue;
	}
	double n2s,n1s,median,p1s,p2s,observed,dummy;
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

	if(option.Contains("scalexs")){
	  int idx=-1;
	  if(option.Contains("hvt")){
	    idx=findIdx(25, mass_HVT_Agv1_XS, mass_for_plot[jj][realidx]);
	    if(scaleOpt[jj].Contains("hvt_wz")){
	      N2S[jj][realidx]*=HVT_Agv1_XS_WZ[idx];
	      N1S[jj][realidx]*=HVT_Agv1_XS_WZ[idx];
	      P1S[jj][realidx]*=HVT_Agv1_XS_WZ[idx];
	      P2S[jj][realidx]*=HVT_Agv1_XS_WZ[idx];
	      Median[jj][realidx]*=HVT_Agv1_XS_WZ[idx];
	      Observed[jj][realidx]*=HVT_Agv1_XS_WZ[idx];
	    }
	    else if(scaleOpt[jj].Contains("hvt_ww")){
	      N2S[jj][realidx]*=HVT_Agv1_XS_WW[idx];
	      N1S[jj][realidx]*=HVT_Agv1_XS_WW[idx];
	      P1S[jj][realidx]*=HVT_Agv1_XS_WW[idx];
	      P2S[jj][realidx]*=HVT_Agv1_XS_WW[idx];
	      Median[jj][realidx]*=HVT_Agv1_XS_WW[idx];
	      Observed[jj][realidx]*=HVT_Agv1_XS_WW[idx];
	    }
	    else if(scaleOpt[jj].Contains("hvt_comb")){
	      N2S[jj][realidx]*=HVT_Agv1_XS_VV[idx];
	      N1S[jj][realidx]*=HVT_Agv1_XS_VV[idx];
	      P1S[jj][realidx]*=HVT_Agv1_XS_VV[idx];
	      P2S[jj][realidx]*=HVT_Agv1_XS_VV[idx];
	      Median[jj][realidx]*=HVT_Agv1_XS_VV[idx];
	      Observed[jj][realidx]*=HVT_Agv1_XS_VV[idx];
	    }
	  }
	  else if(option.Contains("rsg")){
	    idx=findIdx(25, mass_RSG_XS, mass_for_plot[jj][realidx]);
	    if(scaleOpt[jj].Contains("rsg_ww")){
	      N2S[jj][realidx]*=RSG_XS_WW[idx];
	      N1S[jj][realidx]*=RSG_XS_WW[idx];
	      P1S[jj][realidx]*=RSG_XS_WW[idx];
	      P2S[jj][realidx]*=RSG_XS_WW[idx];
	      Median[jj][realidx]*=RSG_XS_WW[idx];
	      Observed[jj][realidx]*=RSG_XS_WW[idx];
	    }
	    else if(scaleOpt[jj].Contains("rsg_zz")){
	      N2S[jj][realidx]*=RSG_XS_ZZ[idx];
	      N1S[jj][realidx]*=RSG_XS_ZZ[idx];
	      P1S[jj][realidx]*=RSG_XS_ZZ[idx];
	      P2S[jj][realidx]*=RSG_XS_ZZ[idx];
	      Median[jj][realidx]*=RSG_XS_ZZ[idx];
	      Observed[jj][realidx]*=RSG_XS_ZZ[idx];
	    }
	    if(scaleOpt[jj].Contains("rsg_comb")){
	      N2S[jj][realidx]*=RSG_XS_VV[idx];
	      N1S[jj][realidx]*=RSG_XS_VV[idx];
	      P1S[jj][realidx]*=RSG_XS_VV[idx];
	      P2S[jj][realidx]*=RSG_XS_VV[idx];
	      Median[jj][realidx]*=RSG_XS_VV[idx];
	      Observed[jj][realidx]*=RSG_XS_VV[idx];
	    }
	  }
	}
	  
	if(p2s>max)max=p2s;
	if(observed>max)max=observed;
	
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

    TString xLabel="", yLabel="";
    if(option.Contains("hvt")){
      xLabel="m_{HVT} [GeV]";
      yLabel="95% CL limit on signal strength";
      if(option.Contains("scalexs")){
	if(option.Contains("hvt_wz")) yLabel="#sigma(pp#rightarrowHVT#rightarrowWZ) [pb]";
	else if(option.Contains("hvt_ww")) yLabel="#sigma(pp#rightarrowHVT#rightarrowWW) [pb]";
	else if(option.Contains("hvt_comb")) yLabel="#sigma(pp#rightarrowHVT#rightarrowVV) [pb]";
      }
    }
    else if(option.Contains("rsg")){
      xLabel="m_{G*} [GeV]";
      yLabel="95% CL limit on signal strength";
      if(option.Contains("scalexs")){
	if(option.Contains("rsg_ww")) yLabel="#sigma(pp#rightarrowG*#rightarrowWW) [pb]";
	else if(option.Contains("rsg_zz")) yLabel="#sigma(pp#rightarrowG*#rightarrowZZ) [pb]";
	else if(option.Contains("rsg_comb")) yLabel="#sigma(pp#rightarrowG*#rightarrowVV) [pb]";
      }
    }

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
    TLegend *leg2=FastLegend(0.53,0.52,0.92,0.65,0.045);
    TPaveText* text=CreatePaveText(x1+0.03,y1+0.03,x1+0.4,y1+0.18,pavetext,0.05);
    TPaveText* text2=CreatePaveText(x1+0.03,y1+0.6,x1+0.4,y2-0.05,pavetext2,0.05);

    // leg->SetNColumns(2);

    leg->SetFillColor(0);
    leg2->SetFillColor(0);
    for(int jj=0;jj<nsample;jj++){	// WSN...
      likelihd_limit_d[jj] = new TGraph(nmass[jj],mass_for_plot[jj],Observed[jj]);
      likelihd_limit_c[jj] = new TGraph(nmass[jj],mass_for_plot[jj],Median[jj]);
      
      if(jj==nsample-1){
	likelihd_limit_d[jj]->SetLineWidth(3);
	likelihd_limit_c[jj]->SetLineWidth(3);
	likelihd_limit_c[jj]->SetLineStyle(9);
      }
      else{
	likelihd_limit_c[jj]->SetLineStyle(7);
	likelihd_limit_d[jj]->SetLineWidth(2);
	likelihd_limit_c[jj]->SetLineWidth(3);
      }
      likelihd_limit_d[jj]->SetLineStyle(1); 
      likelihd_limit_d[jj]->SetMarkerSize(0.9);
      likelihd_limit_d[jj]->SetLineColor(ColorWheel(nsample-jj-1));
      likelihd_limit_c[jj]->SetLineColor(ColorWheel(nsample-jj-1));

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
      // if(jj<nsample-1){
	// leg->AddEntry(likelihd_limit_d[jj],legText[jj]+" obs.","l");
	leg->AddEntry(likelihd_limit_c[jj],legText[jj]+" exp.","l");
      // }
      // else{
      // 	leg2->AddEntry(likelihd_limit_d[jj],legText[jj]+" observed","l");
      // 	leg2->AddEntry(likelihd_limit_c[jj],legText[jj]+" expected","l");
      // }
      // leg->AddEntry(likelihd_limit_1sigma[jj] ,"Expected #pm 1#sigma","f");
      // leg->AddEntry(likelihd_limit_2sigma[jj],"Expected #pm 2#sigma","f");
      
      // likelihd_limit->Add(likelihd_limit_d[jj], "L");
      // likelihd_limit->Add(likelihd_limit_c[jj], "L");
      likelihd_limit_d[jj]->Draw("L");
      likelihd_limit_c[jj]->Draw("L");
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
    if(!option.Contains("scalexs")) DrawConstantLine(cv,1,mass_for_plot[0],nmass[0],2,5,3.);
    if(option.Contains("logy")) cv->SetLogy();
    cv->RedrawAxis();
    TString outputCanvasName=Form("fig/limit_plot/%s/limitplot_multi", jobname.Data());
    if(option.Contains("scalexs")) outputCanvasName+="_scalexs";
    PrintCanvas(cv, outputCanvasName);
    fout.close();
  }// 
  //======================================================================================
}
