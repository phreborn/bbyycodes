#include "frame.h"

using namespace std;
using namespace CommonFunc;
using namespace RooStats;

double epsilon=1e-6;

double mass_RSG[12]={500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000};
double zero[12]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
double xs[5][12]={
  {0.3467, 0.01231,    0.00138,    0.0002471,  5.704e-05,  1.528e-05,  4.497e-06,  1.395e-06,  4.456e-07,  1.454e-07,  4.798e-08,  1.583e-08},
  {8.7,       0.3083,    0.03451,   0.006176,  0.001424,  0.0003815, 0.0001121, 3.489e-05, 1.116e-05, 3.647e-06, 1.205e-06, 4.002e-07},
  {34.96,     1.231,     0.1374,     0.02471,   0.005645,  0.001512,  0.0004448, 0.0001387, 4.472e-05, 1.474e-05, 4.88e-06,  1.647e-06},
  {144.9,     4.9,       0.5413,    0.09527,   0.02191,   0.005887,  0.001741,  0.0005457, 0.0001791, 6.041e-05, 2.083e-05, 7.341e-06},
  {342.8,     11.01,     1.179,     0.2069,    0.04736,   0.01278,   0.00379,   0.001205,  0.0004075, 0.0001415, 5.104e-05, 1.93e-05}
}; 
double xs_dn[5][12]={
  {0.3347 ,      0.01154 ,      0.001266 ,    0.0002227 ,   5.022e-05 ,   1.313e-05 ,   3.785e-06 ,   1.159e-06 ,   3.744e-07 ,   1.184e-07 ,   3.732e-08 ,   1.224e-08 },
  {8.402 ,       0.2886 ,      0.03169 ,     0.00556 ,     0.001254 ,    0.0003279 ,   9.441e-05 ,   2.894e-05 ,   9.366e-06 ,   2.966e-06 ,   9.371e-07 ,   2.997e-07 },
  {33.75 ,       1.153 ,       0.1259 ,      0.02227 ,     0.004969 ,    0.001298 ,    0.0003752 ,   0.0001153 ,   3.753e-05 ,   1.196e-05 ,    3.799e-06 ,   1.252e-06 },
  {139.7 ,       4.598 ,       0.4955 ,      0.08571 ,     0.01933 ,     0.005078 ,    0.001471 ,    0.0004554 ,   0.0001505 ,   5.013e-05 ,   1.634e-05 ,   5.619e-06 },
  {331.2 ,       10.34 ,       1.079 ,       0.1852 ,      0.04186 ,      0.01103 ,     0.00322 ,     0.001009 ,    0.000341 ,    0.0001189 ,   4.134e-05 ,    1.51e-05 }
};
    
double xs_up[5][12]={
  {0.3585   ,     0.01308  ,     0.001505 ,     0.0002773,     6.595e-05,     1.768e-05,     5.21e-06 ,     1.616e-06,     5.197e-07,     1.702e-07,     5.636e-08,     2.162e-08},
  {9.008    ,     0.327    ,     0.0376   ,     0.006931 ,	     0.001633 ,     0.0004409,     0.0001298,     4.038e-05,     1.297e-05,     4.234e-06,     1.414e-06,     4.881e-07},
  {36.3     ,     1.306    ,     0.1504   ,     0.02792  ,     0.006529 ,     0.001757 ,     0.0005156,     0.0001606,     5.182e-05,     1.704e-05,     5.753e-06,     2.013e-06},
  {150.5    ,     5.193    ,     0.5891   ,     0.1069   ,     0.02509  ,     0.006802 ,     0.002016 ,     0.0006337,     0.0002071,     7.015e-05,     2.476e-05,     8.783e-06},
  {354.6    ,     11.67    ,     1.288    ,     0.2321   ,     0.05414  ,     0.01476  ,     0.004388 ,     0.00139  ,     0.0004716,     0.0001639,	     5.952e-05,     2.315e-05}
};

void convertTofb(int nmass, double *mass){
  for(int imass=0;imass<nmass;imass++){
    mass[imass]*=1000.;
  }
}

void takeDiff(int nmass, double *mass, double *mass_base){
  for(int imass=0;imass<nmass;imass++){
    mass[imass]=fabs(mass[imass]-mass_base[imass]);
  }
}

int GkMToIdx(double GkM){
  if(GkM==0.01) return 0;
  if(GkM==0.05) return 1;
  if(GkM==0.1)  return 2;
  if(GkM==0.2)  return 3;
  if(GkM==0.3)  return 4;
  return -1;
}

double BinarySearch(TGraph *s, double target, double xmin, double xmax, double tolerance=1e-3){
  // if(xmin<s->GetXmin()){
  //   cout<<"Warning: input range is too wide. Use the range of the input spline: "
  // 	<<s->GetXmin()<<" "<<s->GetXmax()<<endl;
  //   xmin=s->GetXmin();
  // }
  // if(xmax>s->GetXmax()){
  //   cout<<"Warning: input range is too wide. Use the range of the input spline: "
  // 	<<s->GetXmin()<<" "<<s->GetXmax()<<endl;
  //   xmax=s->GetXmax();
  // }
  if(xmin>xmax){
    cout<<"wrong input."<<endl;
    cout<<"xmin: "<<xmin<<", xmax: "<<xmax<<endl;
    abort();
  }
  // start binary search

  double begin = xmin;
  double end = xmax;
  double median=(end-begin)/2;
  double thisUL=s->Eval(begin);
  int counter=0;
  while(fabs(thisUL-target)>tolerance){
    median=(end+begin)/2;
//     cout<<"begin = "<<begin<<" "<<s->Eval(begin)
// 	<<" end = "<<end<<" "<<s->Eval(end)
// 	<<" median = "<<median<<" "<<s->Eval(median)
// 	<<endl;
//     getchar();
    thisUL=s->Eval(median);
    if((thisUL-target)*(s->Eval(end)-target)<0) begin=median;
    else if((thisUL-target)*(s->Eval(begin)-target)<0) end=median;
    counter++;
  }
  return counter<1e3?median:-998;//   return median;
}

int findIdx(int nmass, double *mass, double value){
  int idx=-1;
  for(int imass=0;imass<nmass;imass++){
    if(fabs(mass[imass]-value)<epsilon){ idx=imass; break;}
  }
  return idx;
}

void mergeXS(int nmass, double *massTot, double *mass1, double *mass2){
  for(int imass=0;imass<nmass;imass++){
    massTot[imass]=mass1[imass]+mass2[imass];
  }
}

double findCrossingPoint(TGraph *experiment, TGraph *theory, double xmin, double xmax, double step=10){
  if(xmin>xmax){
    cout<<"wrong input."<<endl;
    cout<<"xmin: "<<xmin<<", xmax: "<<xmax<<endl;
    abort();
  }
  const int nstep=int((xmax-xmin)/step)+1;
  
  double expArry[nstep], theArry[nstep], diffArry[nstep], posArry[nstep];
  
  for(int istep=0;istep<nstep;istep++){
    double position=xmin+istep*step;
    if(position>xmax) position=xmax;
    posArry[istep]=position;
    expArry[istep]=experiment->Eval(position);
    theArry[istep]=theory->Eval(position);
    diffArry[istep]=expArry[istep]-theArry[istep];
  }

  TGraph difference(nstep, posArry, diffArry);
  return BinarySearch(&difference, 0, xmin, xmax);
}

void set_palette(TString name="palette", int ncontours=999){
  double stops[5] = {0};
  double red[5] = {0};
  double green[5] = {0};
  double blue[5] = {0};
  if (name.Contains("gray")){
    stops[0] = 0.00; stops[1] = 0.34; stops[2] = 0.61; stops[3] = 0.84; stops[4] = 1.00;
    red[0] = 1.00; red[1] = 0.84; red[2] = 0.61; red[3] = 0.34; red[4] = 0.00;
    green[0] = 1.00; green[1] = 0.84; green[2] = 0.61; green[3] = 0.34; green[4] = 0.00;
    blue[0] = 1.00; blue[1] = 0.84; blue[2] = 0.61; blue[3] = 0.34; blue[4] = 0.00;
  }
  else{
    stops[0] = 0.00; stops[1] = 0.34; stops[2] = 0.61; stops[3] = 0.84; stops[4] = 1.00;
    red[0] = 0.00; red[1] = 0.00; red[2] = 0.87; red[3] = 1.00; red[4] = 0.51;
    green[0] = 0.00; green[1] = 0.81; green[2] = 1.00; green[3] = 0.20; green[4] = 0.00;
    blue[0] = 0.51; blue[1] = 1.00; blue[2] = 0.12; blue[3] = 0.00; blue[4] = 0.00;
  }

  int npoints = 5;
  TColor::CreateGradientColorTable(npoints, stops, red, green, blue, ncontours);
  gStyle->SetNumberContours(ncontours);
}

int main(int argc, char **argv){
  //============================ Global booking and setting ==========================
  //   gErrorIgnoreLevel = kError+1;
  map<string,bool> Opt;
  Opt["1D"]=false;
  Opt["2D"]=false;

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
  if(Opt["1D"]){
    if(argc<4){
      cout<<"Usage: "<<argv[0]<<" "<<argv[1]<<" <jobname> <coupling> <option>"<<endl;
      exit(0);
    }
    TString jobname=argv[2];
    double kappa=atof(argv[3]);
    TString option=argv[4];
    option.ToLower();

    for(int ikappa=0;ikappa<5;ikappa++){
      convertTofb(12, xs[ikappa]);
      convertTofb(12, xs_up[ikappa]);
      convertTofb(12, xs_dn[ikappa]);
      takeDiff(12, xs_up[ikappa], xs[ikappa]);
      takeDiff(12, xs_dn[ikappa], xs[ikappa]);
    }
    
    TString type;
    string fileName[5];
    int nsample=1;
    fileName[0]=jobname.Data();

    double mass[5][200], mass_for_plot[5][200];
    double N2S[5][200],N1S[5][200],P1S[5][200],P2S[5][200],Median[5][200],Zero[5][200],Observed[5][200];
    vector<int> temp;
    TCanvas *cv = CreateCanvas("canvas", "",800,600);
    double x1,y1,x2,y2;
    GetX1Y1X2Y2(cv,x1,y1,x2,y2);

    int nmass[5];
    double xmin, xmax, ymin, ymax;

    vector<TString> pavetext, pavetext2;

    if(option.Contains("graviton")){
      pavetext.push_back("Spin-2 Selection");
      pavetext.push_back(Form("G*#rightarrow#gamma#gamma, #it{k}/#bar{M}_{Pl} = %.2f", kappa));
    }
    if(option.Contains("scalar")){
      pavetext.push_back("Spin-0 Selection");
      if(option.Contains("nwa")){
	pavetext.push_back(Form("X#rightarrow#gamma#gamma, NWA"));
      }
      else{
	pavetext.push_back(Form("X#rightarrow#gamma#gamma, #Gamma_{X} = %.0f%%m_{X}", kappa*100));
      }
    }
    // pavetext2.push_back("#bf{#it{ATLAS}} internal");
    if(option.Contains("atlaspub")) pavetext2.push_back("#bf{#it{ATLAS}}");
    else if(option.Contains("atlasnote")) pavetext2.push_back("#bf{#it{ATLAS}} preliminary");
    else if(option.Contains("asimov")) pavetext2.push_back("#bf{#it{ATLAS}} simulation internal");
    else pavetext2.push_back("#bf{#it{ATLAS}} internal");

    if(option.Contains("8tev")) pavetext2.push_back("#sqrt{#it{s}} = 8 TeV, 20.3 fb^{-1}");
    else pavetext2.push_back("#sqrt{#it{s}} = 13 TeV, 3.2 fb^{-1}");

    nsample=1;
    if(option.Contains("8tev")) for(int Mass=500;Mass<=3000;Mass+=20) temp.push_back(Mass);
    else if(option.Contains("scalar")) for(int Mass=200;Mass<=1700;Mass+=10) temp.push_back(Mass);
    else for(int Mass=500;Mass<=5000;Mass+=20) temp.push_back(Mass);
    nmass[0]=temp.size();
    for(int i=0;i<nmass[0];i++) mass[0][i]=temp[i];
    
    xmin=mass[0][0];
    xmax=mass[0][nmass[0]-1];

    if(option.Contains("logy")){
      ymin=4e-1;
      ymax=1e3;
    }
    else{
      ymin=0;
      ymax=80;
    }
    if(option.Contains("8tev")) {
      ymin=1e-1;
      ymax=200;
    }

    if(option.Contains("scalar")) {
      ymin=5e-1;
      ymax=1.5e3;
    }

    system(Form("mkdir -vp fig/limit_plot/%s",jobname.Data()));
    ofstream fout(Form("fig/limit_plot/%s/limit_%.2f.txt",jobname.Data(),kappa),ios::out);
    fout<<Form("Mass \t Obs \t\t Med \t\t -1S \t\t -2S \t\t +1S \t\t +2S")<<endl;
    double max=0;

    for(int jj=0;jj<nsample;jj++){
      Info("Frame: LIMIT","%d mass points will be processed.",nmass[jj]);
      int realidx=0;
      for(int idx=0;idx<nmass[jj];idx++){

	string infile=Form("limit/%s/%s_%.2f_%.2f.txt", fileName[jj].c_str(), fileName[jj].c_str(), mass[jj][idx], kappa);
	ifstream fin(infile.c_str(),ios::in);
	if(!fin){
	  cerr<<"File "<<infile.c_str()<<" does not exist."<<endl;
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

	if(p2s>max)max=p2s;
	if(observed>max)max=observed;
	
	fout<<Form("%.1f \t %.5f \t %.5f \t %.5f \t %.5f \t %.5f \t %.5f",mass_for_plot[jj][realidx],observed,median,n1s,n2s,p1s,p2s)<<endl;
	// fout<<Form("%.1f \t %.4f \t %.4f \t %.4f \t %.4f \t %.4f \t %.4f \t %.1f \%.4e",mass[jj][realidx],Obser,median,n1s,n2s,p1s,p2s,mass_RSG_XS[xsidx],RSG_XS_ZZ[xsidx])<<endl;
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
    if(option.Contains("scalar")){
      xLabel="m_{X} [GeV]";
      yLabel="95% CL limits on #sigma_{fid}#timesBR [fb]";
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
    // TLegend *leg=FastLegend(0.2,0.62,0.55,0.92,0.045);
    TLegend *leg=FastLegend(0.2,0.68,0.55,0.92,0.045);
    TPaveText* text=CreatePaveText(x1+0.4,y1+0.52,x1+0.9,y1+0.64,pavetext,0.045);
    TPaveText* text2=CreatePaveText(x1+0.4,y1+0.64,x2-0.03,y2-0.05,pavetext2,0.045);

    leg->SetFillColor(0);

    
    for(int jj=0;jj<nsample;jj++){	// WSN...
      likelihd_limit_d[jj] = new TGraph(nmass[jj],mass_for_plot[jj],Observed[jj]);

      likelihd_limit_d[jj]->SetLineWidth(3);
      likelihd_limit_d[jj]->SetLineStyle(1); 
      likelihd_limit_d[jj]->SetMarkerSize(0.9);

      likelihd_limit_c[jj] = new TGraph(nmass[jj],mass_for_plot[jj],Median[jj]);
      likelihd_limit_c[jj]->SetLineWidth(2);
      likelihd_limit_c[jj]->SetLineStyle(2);

      // likelihd_limit_c[jj]->SetLineStyle(1);
      likelihd_limit_c[jj]->SetLineStyle(7);
      likelihd_limit_c[jj]->SetLineWidth(3);
      // likelihd_limit_c[jj]->SetLineColor(kRed);
      likelihd_limit_c[jj]->SetLineColor(kBlue);

      likelihd_limit_1sigma[jj] = new TGraphAsymmErrors(nmass[jj],mass_for_plot[jj],Median[jj],Zero[jj],Zero[jj],N1S[jj],P1S[jj]);
      likelihd_limit_1sigma[jj]->SetFillColor(kGreen);
      likelihd_limit_1sigma[jj]->SetLineColor(kGreen);

      likelihd_limit_2sigma[jj] = new TGraphAsymmErrors(nmass[jj],mass_for_plot[jj],Median[jj],Zero[jj],Zero[jj],N2S[jj],P2S[jj]);

      likelihd_limit_2sigma[jj]->SetFillColor(kYellow);
      likelihd_limit_2sigma[jj]->SetLineColor(kYellow);

      // likelihd_limit->Add(likelihd_limit_2sigma[jj],"E3");  
      // likelihd_limit->Add(likelihd_limit_1sigma[jj],"E3");
      likelihd_limit_2sigma[jj]->Draw("E3");  
      likelihd_limit_1sigma[jj]->Draw("E3");
      leg->AddEntry(likelihd_limit_d[jj],"Observed #it{CL_{s}} limit","l");
      leg->AddEntry(likelihd_limit_c[jj],"Expected #it{CL_{s}} limit","l");
      
      leg->AddEntry(likelihd_limit_1sigma[jj] ,"Expected #pm 1#sigma","f");
      leg->AddEntry(likelihd_limit_2sigma[jj],"Expected #pm 2#sigma","f");
      
      // likelihd_limit->Add(likelihd_limit_d[jj], "L");
      // likelihd_limit->Add(likelihd_limit_c[jj], "L");
      if(option.Contains("graviton")){
	TGraphAsymmErrors *gr_RSG_band=new TGraphAsymmErrors(12, mass_RSG, xs[GkMToIdx(kappa)], zero, zero, xs_up[GkMToIdx(kappa)], xs_dn[GkMToIdx(kappa)]);
	gr_RSG_band->SetLineColor(kRed);
	gr_RSG_band->SetLineStyle(1);
	gr_RSG_band->SetLineWidth(3);
	gr_RSG_band->SetFillColor(kGray);
	// gr_RSG_band->SetFillStyle(3244);
	
	gr_RSG_band->Draw("E3");
	TGraph *gr_RSG=new TGraph(12, mass_RSG, xs[GkMToIdx(kappa)]);
	gr_RSG->SetLineColor(kRed);
	gr_RSG->SetLineStyle(1);
	gr_RSG->SetLineWidth(3);
	gr_RSG->Draw("L");
	
	leg->AddEntry(gr_RSG_band,"pp#rightarrowG*#rightarrow#gamma#gamma","lf");
      }

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

    TBox *box = new TBox (xmin, 70, xmax, ymax);
    box->SetFillStyle(1001);
    box->SetFillColor(0);
    box->Draw();
    
    leg->Draw();

    text->Draw("same");
    text2->Draw("same");

    if(option.Contains("logy")) cv->SetLogy();
    if(option.Contains("logx")){
      cout<<"Set log x"<<endl;
      cv->SetLogx();
    }
    cv->RedrawAxis();
    TString outputCanvasName=Form("fig/limit_plot/%s/limitplot_%.2f", jobname.Data(), kappa);
    if(option.Contains("logy")) outputCanvasName+="_logy";
    
    PrintCanvas(cv, outputCanvasName);
    fout.close();
  }// 
  //======================================================================================
  if(Opt["2D"]){
    if(argc<4){
      cout<<"Usage: "<<argv[0]<<" "<<argv[1]<<" <jobname> <option>"<<endl;
      exit(0);
    }
    TString jobname=argv[2];
    TString option=argv[3];
    set_palette();

    TString tag="";
    if(option.Contains("obs")) tag="obs";
    if(option.Contains("exp")) tag="exp";

    vector<Double_t> mass,coup;
    if(option.Contains("8tev")){
      for(Double_t m=500; m<=3000.1; m+=20 ) mass.push_back(m);
    }
    else if(option.Contains("scalar")){
      for(Double_t m=200; m<=1700.1; m+=10 ) mass.push_back(m);
    }
    else{
      for(Double_t m=500; m<=3500.1; m+=20 ) mass.push_back(m);
    }

    if(option.Contains("graviton")){
      for(Double_t c=0.0; c<=0.301; c+=0.01 ) coup.push_back(c);
    }
    else if(option.Contains("scalar")){
      for(Double_t c=0.0; c<=0.101; c+=0.01 ) coup.push_back(c);
    }
    
    TGraph2D* g = new TGraph2D();

    ifstream input;
    string dummy;
    double obslim;
    double explim;
    int ipoint = 0;
    for( auto m : mass){
      for( auto c: coup ){
	TString filename = Form("limit/%s/%s_%.2f_%.2f.txt",jobname.Data(),jobname.Data(),m,c);
	cout<<filename<<endl;
	input.open(filename.Data());
	    
	if( !input.is_open() ) continue;
	input>>dummy>>obslim>>explim;
	input.close();
	if(option.Contains("obs")) g->SetPoint(ipoint,m,c,obslim);
	if(option.Contains("exp")) g->SetPoint(ipoint,m,c,explim);
	ipoint++;
      }
    }

    TCanvas* c1 = new TCanvas();
    c1->cd();
    c1->SetLogx();
    c1->SetLogz();
    gPad->SetRightMargin(0.18);

    int bins = 400;
    TH2D* h_tmp= g->GetHistogram();
    TH2D* h_int = new TH2D("h_int","",bins,h_tmp->GetXaxis()->GetXmin(),h_tmp->GetXaxis()->GetXmax(),bins,h_tmp->GetYaxis()->GetXmin(),h_tmp->GetYaxis()->GetXmax());
    //TH2D* h_int = new TH2D("h_int","",bins,400,1600,bins,h_tmp->GetYaxis()->GetXmin(),h_tmp->GetYaxis()->GetXmax());
    TString xTitle="", yTitle="";
    if(option.Contains("scalar")){
      xTitle="m_{X} [GeV]";
      yTitle="#Gamma_{X}/m_{X} [%]";
    }
    else if(option.Contains("graviton")){
      xTitle="m_{G*} [GeV]";
      yTitle="#it{k}/#bar{M}_{Pl}";
    }
    h_int->GetXaxis()->SetTitle(xTitle);
    h_int->GetYaxis()->SetTitle(yTitle);
    h_int->SetZTitle("95\%CL upper limit on #sigma_{"+tag+"} [fb]");
    
    h_int->GetZaxis()->SetTitleOffset(1.2);

    g->SetHistogram(h_int);
    g->Draw("colz");
    h_int = g->GetHistogram();

    h_int->GetXaxis()->SetNdivisions(5);
    h_int->Draw("colz");
    TLatex l;
    l.SetNDC(kFALSE);
    l.DrawLatex(455,-0.013,"5#times10^{2}");
    l.DrawLatex(1825,-0.013,"2#times10^{3}");

    double x1,y1,x2,y2;
    CommonFunc::GetX1Y1X2Y2(c1,x1,y1,x2,y2);
    vector<TString> pavetext1,pavetext2;
    if(option.Contains("atlaspub")) pavetext2.push_back("#bf{#it{ATLAS}}");
    else if(option.Contains("atlasnote")) pavetext2.push_back("#bf{#it{ATLAS}} preliminary");
    else if(option.Contains("asimov")) pavetext2.push_back("#bf{#it{ATLAS}} simulation internal");
    else pavetext2.push_back("#bf{#it{ATLAS}} internal");
    TPaveText* text2=CreatePaveText(x1+0.03,y1-0.15,x1+0.4,y1-0.08,pavetext2,0.045);
    text2->Draw("same");
    system("mkdir -vp fig/limit_plot/"+jobname);
    CommonFunc::PrintCanvas(c1,"fig/limit_plot/"+jobname+"/2Dlimit_"+tag);
  }
}
