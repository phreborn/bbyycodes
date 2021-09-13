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

const double epsilon=1e-5;
const double LARGENUM=1e37;
const double minimizerTolerance=1e-3;

double median(double NLL, double minNLL)
{

  double delta_NLL = 2*fabs( NLL-minNLL ) ;
  double pvalue =  ROOT::Math::chisquared_cdf(delta_NLL,2);

  return pvalue;
}

double BinarySearch(TSpline *s, double target, double xmin, double xmax, double tolerance=1e-3){
  if(xmin<s->GetXmin()){
    cout<<"Warning: input range is too wide. Use the range of the input spline: "
	<<s->GetXmin()<<" "<<xmax<<endl;
    xmin=s->GetXmin();
  }
  if(xmax>s->GetXmax()){
    cout<<"Warning: input range is too wide. Use the range of the input spline: "
	<<xmin<<" "<<s->GetXmax()<<endl;
    xmax=s->GetXmax();
  }
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
  return median;//   return median;
}

double GetMinimum(TSpline *s, double xmin, double xmax, double tolerance=1e-3){
  if(xmin<s->GetXmin()||xmax>s->GetXmax()){
    cout<<"Warning: input range is too wide. Use the range of the input spline: "
	<<s->GetXmin()<<" "<<s->GetXmax()<<endl;
    xmin=s->GetXmin(); xmax=s->GetXmax();
  }
  if(xmin>xmax){
    cout<<"Wrong input."<<endl;
    abort();
  }
  // start binary search
  double thisUL=998,preUL=998;
  for(double position=xmin;position<xmax;position+=tolerance){
    thisUL=s->Eval(position);
    if(thisUL>preUL) return position-tolerance;
    preUL=thisUL;
  }
  return -1;
}

int main(int argc, char **argv){
  //***************************= Global booking and setting ************************==
  //   gErrorIgnoreLevel = kError+1;
  map<string,bool> Opt;
  Opt["NLL"]=false;

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
  if(Opt["NLL"]){
    cout<<setprecision(10);
    if(argc<4){
      cout<<"Usage: "<<argv[0]<<" plot <jobname> <poiName,start,end,binw> <option>"<<endl;
      return 0;
    }
    TString jobname=argv[2];
    TString input=argv[3];
    TString option=argv[4];
    
    double luminosity=20.3;
    map<TString, TString> xtitle=createTitleList();   

    cout<<input<<endl;

    TCanvas* c = CreateCanvas("c","NLL Scan",800,600);
    if(option.Contains("wide")) c = CreateCanvas("c","NLL Scan",1200,600);
    bool m_right=option.Contains("right");
    bool m_middle=option.Contains("middle");
    bool m_2sigma=option.Contains("2sigma");
    //bool m_nominfile=option.Contains("nominfile");
    bool m_extend=option.Contains("extend");
    bool m_asimov=option.Contains("asimov");
    bool m_noerrlo=option.Contains("noerrlo");
    bool m_noerrhi=option.Contains("noerrhi");
    bool m_negative=option.Contains("negative");
    bool m_rigorous=option.Contains("rigorous");
    bool m_nobf=option.Contains("nobf");
    
    if(option.Contains("fine")){
      m_noerrlo=true;
      m_noerrhi=true;
      option+=",nominfile";
    }

    vector<TString> inputlist=SplitString(input,',');
    TString poiName=inputlist[0];
    double start=atof(inputlist[1]);
    double end=atof(inputlist[2]);
    double binw=atof(inputlist[3]);
    int npoint=int((end-start+epsilon)/binw)+1;

    cout<<poiName<<" "<<start<<" "<<end<<" "<<binw<<endl;
    Int_t i, j, TotalConts;

    double mu[1000]={0}, nll[1000]={0};
    
    double xmin=start,xmax=end;
    
    double minNLL=LARGENUM;
    double NLL,poi,bf=0;

    TChain *tmin=new TChain("toys/nllscan");


    // if(poiName=="m_H") minFile="root/"+jobname+Form("/opt_%s=*_120_130_*.root",poiName.Data());

    TString inputtag=jobname;
    if(option.Contains("nosys")) inputtag=inputtag.ReplaceAll("_nosys","");
    if(option.Contains("noessthe")) inputtag=inputtag.ReplaceAll("_noessthe","");
    if(option.Contains("noess")) inputtag=inputtag.ReplaceAll("_noess","");

    if(option.Contains("nooffset")) inputtag=inputtag.ReplaceAll("_nooffset","");
    if(option.Contains("nothe")) inputtag=inputtag.ReplaceAll("_nothe","");
    if(option.Contains("noatlas")) inputtag=inputtag.ReplaceAll("_noatlas","");
    if(option.Contains("nocms")) inputtag=inputtag.ReplaceAll("_nocms","");
    if(option.Contains("nores")) inputtag=inputtag.ReplaceAll("_nores","");
    if(option.Contains("nomigr")) inputtag=inputtag.ReplaceAll("_nomigr","");
    if(option.Contains("nonorm")) inputtag=inputtag.ReplaceAll("_nonorm","");
    if(option.Contains("nospur")) inputtag=inputtag.ReplaceAll("_nospur","");
    if(option.Contains("noenl")) inputtag=inputtag.ReplaceAll("_noenl","");
    if(option.Contains("nolca")) inputtag=inputtag.ReplaceAll("_nolca","");
    if(option.Contains("nomat")) inputtag=inputtag.ReplaceAll("_nomat","");
    if(option.Contains("nolss")) inputtag=inputtag.ReplaceAll("_nolss","");
    if(option.Contains("nobgm")) inputtag=inputtag.ReplaceAll("_nobgm","");
    if(option.Contains("strat2")) inputtag=inputtag.ReplaceAll("_strat2","");
    if(option.Contains("minuit")) inputtag=inputtag.ReplaceAll("_minuit","");
    if(option.Contains("july2013_profile")) inputtag=inputtag.ReplaceAll("_july2013_profile","");

    bool m_nominfile=getMinFile(tmin, jobname, poiName);

    if(option.Contains("nominfile")) m_nominfile=true;
    if(!m_nominfile){
      tmin->SetBranchAddress("nll", &minNLL);
      tmin->SetBranchAddress(poiName, &bf);
      tmin->GetEntry(0);
      cout<<"Reading min file: "<<tmin->GetCurrentFile()->GetName()<<endl;
      // getchar();
    }
    else{
      cerr<<"Minimum file cannot be found. Press any key to continue..."<<endl;
      getchar();
    }
    double NLL_one=LARGENUM;
    double NLL_zero=LARGENUM;

    int realidx=0;
    for (Int_t i = 0; i < npoint; i++) {
      double poiValue=start+i*binw;
      nll[realidx]=LARGENUM;
      TChain* t = new TChain("toys/nllscan");
      TString inputScanFile="root/"+jobname+Form("/*%s=%.2f_.*.root",poiName.Data(),poiValue);

      if(option.Contains("fine")||option.Contains("scalelumi")) inputScanFile="root/"+jobname+Form("/*%s=%.4f_.*.root",poiName.Data(),poiValue);
      cout<<inputScanFile<<endl;
      if(t->Add(inputScanFile)!=1){
	cout<<"Point "<<poiValue<<" does not exist."<<endl;
	if(m_rigorous) abort();
	else continue;
      }

      t->SetBranchAddress("nll", &NLL);
      t->SetBranchAddress(poiName, &poi);
      t->GetEntry(0);
      cout<<"+++++++++++++++++++++++++++++++++++++++"<<endl;
      cout<<xtitle[poiName]<<" = "<<poi<<endl;
      cout<<"NLL = "<<NLL<<endl;
      cout<<"+++++++++++++++++++++++++++++++++++++++"<<endl;
      if(!isfinite(NLL)){
	cerr<<xtitle[poiName]<<" = "<<poi<<" is not finite. Please intervine. Aborting..."<<endl;
	abort();
      }
      if(m_nominfile&&NLL<minNLL){
	minNLL=NLL;
	bf=poi;
      }
      mu[realidx]=poi;
      nll[realidx]=NLL;
      if(fabs(mu[realidx]-1)<epsilon) NLL_one=NLL;
      if(option.Contains("devcutoff")){
	if(realidx==0) NLL_zero=NLL;
      }
      else{
	if(fabs(mu[realidx]-0)<epsilon) NLL_zero=NLL;
      }
      SafeDelete(t);
      realidx++;
      if(!m_nominfile&&bf>poiValue&&bf<poiValue+binw&&!m_nobf){
	// If the difference between two points is very small (like 1e-6)
	// Then TSpline interpolation would do something crazy.
	// In this case we simply don't put the best fit point as it would not help improve the interpolation
	if(fabs(bf-poiValue)<epsilon){
	  cout<<setprecision(10);
	  cout<<"Difference: "<<bf-poiValue<<" "<<NLL-minNLL<<endl;
	  cout<<"Warning: The best fit point and scan point is too close. Watch out for Zigzag in the interpolation. Do you still want to include the best fit point? [y/n]"<<endl;
	  TString answer=getchar();
	  answer.ToLower();
	  if(answer.Contains("n")) continue;
	}
	
	mu[realidx]=bf;			
	nll[realidx]=minNLL;
	realidx++;
	cout<<"Insert best fit point"<<endl;

      }
    }

    npoint=realidx;

    double negativeNLL=998, negativeNLLmu=-998;

    for (Int_t i = 0; i < npoint; i++){
      nll[i]=2*(nll[i]-minNLL);
      cout<<nll[i]<<" "<<mu[i]<<endl;

      if(nll[i]<0&&nll[i]<negativeNLL){
	negativeNLL=nll[i]/2;
	negativeNLLmu=mu[i];
      }
    }

    c->cd();
    TGraph *gr=new TGraph(npoint,mu,nll);


    TH1F* hframe=new TH1F("hframe","",10000,xmin,xmax);
    hframe->GetYaxis()->SetTitle("-2#Deltaln(L)");
    hframe->GetXaxis()->SetTitle(xtitle[poiName]);
    hframe->GetXaxis()->SetLabelSize(0.04);
    hframe->SetMaximum(4);
    if(m_extend) hframe->SetMaximum(5);
    if(option.Contains("extend2")) hframe->SetMaximum(25);
    // if(option.Contains("fine")) hframe->SetMaximum(0.00002);
    if(option.Contains("fine")) hframe->SetMaximum(0.0002);
    hframe->SetMinimum(0);
    hframe->SetLineWidth(0);
    hframe->Draw();

    gr->SetLineWidth(2);
    gr->Draw("L");


    TSpline5 *s=new TSpline5("grs",gr);
    s->SetLineWidth(2);
    s->SetLineColor(2);
    if(!option.Contains("fine")&&!option.Contains("nospline")) s->Draw("same");


    double errLo=xmin;
    double errHi=xmax;
    if(!m_noerrlo) errLo=BinarySearch(s,1,xmin,bf,1e-5);
    if(!m_noerrhi) errHi=BinarySearch(s,1,bf,xmax,1e-5);

    double slopeLo=(s->Eval(errLo+1e-3)-s->Eval(errLo))/(1e-3);
    double slopeHi=(s->Eval(errHi)-s->Eval(errHi-1e-3))/(1e-3);
    if(m_2sigma){
      errLo=BinarySearch(s,4,s->GetXmin(),bf,1e-5);
      errHi=BinarySearch(s,4,bf,s->GetXmax(),1e-5);
    }

    if(m_nominfile){
      if(s->Eval(GetMinimum(s,bf,errHi,1e-5))>s->Eval(GetMinimum(s,errLo,bf,1e-5))) bf=GetMinimum(s,errLo,bf,1e-5);
      else bf=GetMinimum(s,bf,errHi,1e-5);
    }
    errLo=bf-errLo;
    errHi=errHi-bf;

    double err=(errLo+errHi)/2;

    cout<<"mu with minimum NLL: "<<bf<<endl;
    cout<<"Error low: "<<errLo<<" , slope low: "<<slopeLo<<endl;
    cout<<"Error high: "<<errHi<<", slope high: "<<slopeHi<<endl;
    DrawConstantLine(c,1,xmin,xmax,1,2,1);
    DrawConstantLine(c,4,xmin,xmax,1,2,1);
    if(option.Contains("2sigma")) DrawConstantLine(c,4,xmin,xmax,1,2,1);
    TLine *ErrLo=new TLine(bf-errLo,0,bf-errLo,hframe->GetMaximum());
    TLine *ErrHi=new TLine(bf+errHi,0,bf+errHi,hframe->GetMaximum());
    TLine *SM=new TLine(1,0,1,hframe->GetMaximum());
    TLine *bOnly=new TLine(0,0,0,hframe->GetMaximum());
    ErrLo->SetLineColor(2);ErrLo->SetLineWidth(2);
    ErrHi->SetLineColor(2);ErrHi->SetLineWidth(2);
    SM->SetLineColor(2);SM->SetLineWidth(2);SM->SetLineStyle(2);
    bOnly->SetLineColor(1);bOnly->SetLineWidth(1);
    // ErrLo->Draw("same");
    // ErrHi->Draw("same");
    // SM->Draw("same");
    if(!option.Contains("nobonly")) bOnly->Draw("same");
    double x1,y1,x2,y2;
    GetX1Y1X2Y2(c,x1,y1,x2,y2);
    vector<TString> pavetext;
    // if(option.Contains("atlas")){
    //   if(option.Contains("atlaspub")) pavetext.push_back("#bf{#it{ATLAS}}");
    //   else if(option.Contains("asimov")) pavetext.push_back("#bf{#it{ATLAS}} simulation internal");
    //   else pavetext.push_back("#bf{#it{ATLAS}} internal");
    // }

    // else 
      pavetext.push_back("#bf{#it{LHC-HCG}} internal");
    //pavetext.push_back("#bf{#it{ATLAS}} Preliminary");
    if(!option.Contains("runii")) pavetext.push_back("2011-2012");
    pavetext.push_back("");
    if(option.Contains("cms")){
      if(option.Contains("combination")) pavetext.push_back("#bf{#it{CMS}} combination");
      
      pavetext.push_back("#scale[0.6]{#int}Ldt = 5.1 fb^{-1}, #sqrt{#it{s}} = 7 TeV");
      pavetext.push_back("#scale[0.6]{#int}Ldt = 19.7 fb^{-1}, #sqrt{#it{s}} = 8 TeV");
    }
    else if(option.Contains("atlas")){
      if(option.Contains("combination")) pavetext.push_back("#bf{#it{ATLAS}} combination");
      
      if(option.Contains("runii")){
	pavetext.push_back("#scale[0.6]{#int}Ldt = 10 fb^{-1}, #sqrt{#it{s}} = 13 TeV");
      }
      else{
	pavetext.push_back("#scale[0.6]{#int}Ldt = 4.5 fb^{-1}, #sqrt{#it{s}} = 7 TeV");
	pavetext.push_back("#scale[0.6]{#int}Ldt = 20.3 fb^{-1}, #sqrt{#it{s}} = 8 TeV");
      }
    }
    else{
      if(option.Contains("hgg")) pavetext.push_back("LHC #it{H #rightarrow #gamma#gamma}");
      if(option.Contains("hzz")) pavetext.push_back("LHC #it{H #rightarrow ZZ #rightarrow 4l}");
      if(option.Contains("combination")) pavetext.push_back("LHC combination");
    }
    pavetext.push_back(" ");
    //pavetext.push_back(Form("%s=%.2f^{+%.2f}_{-%.2f}",xtitle[poiName].Data(),bf,errHi,errLo));
    if(option.Contains("printmass")) pavetext.push_back(Form("#it{m}_{#it{H}} = 125.4 GeV"));
    TPaveText* text=NULL;
    if(m_right) {
      text=CreatePaveText(x2-0.45,y2-0.45,x2-0.05,y2-0.05,pavetext,0.05);
      text->SetTextAlign(31);
    }
    else if(m_middle) //text=CreatePaveText(x2-0.7,y1+0.2,x2-0.01,y1+0.4,pavetext,0.045);
      text=CreatePaveText(x2-0.6,y2-0.45,x2-0.01,y2-0.05,pavetext,0.05);
    else text=CreatePaveText(x1+0.02,y2-0.45,x1+0.60,y2-0.05,pavetext,0.05);

    c->cd();
    text->Draw("same");

    c->Update();
    system("mkdir -vp fig/nllscan/"+jobname);
    TString outputCanvas="fig/nllscan/"+jobname+"/nllscan_"+poiName;
    // if(poiName="CV"){
    //   if(m_negative) outputCanvas+="_negative";
    //   else outputCanvas+="_positive";
    // }
    PrintCanvas(c,outputCanvas);

    // *********************************************
    // Only for LHC-HCG mass combination:
    // Save the best fit value of all POIs
    const int npoi=11;
    TString poiBRName[npoi]={"mH", "dmH_exp", "dmH_gZ", "muF_gg", "muV_gg", "mu_ZZ", "lambda_muF_gg", "lambda_muV_gg", "lambda_mu_ZZ", "mu", "lambda_mu"};
    double poiValue[npoi]={ -998,  0,         0,        1,        1,        1,       1,               1,               1,              1,    1};
    double poiPos[npoi]={0};

    for(int ipoi=0;ipoi<npoi;ipoi++){
      tmin->SetBranchAddress(poiBRName[ipoi].Data(),&poiValue[ipoi]);
      poiPos[ipoi]=ipoi;
    }
    tmin->GetEntry(0);
    TGraph *gr_best=new TGraph(npoi,poiPos,poiValue);
    gr_best->SetName("Graph_best");
    // *********************************************
    TString outputDir="fig/nllscan/"+jobname+"/";
    TFile *fgraph=TFile::Open(outputDir+"/graph_"+poiName+".root","recreate");
    gr->Write();
    gr_best->Write();
    fgraph->Close();
    double pvalue_one=1-ROOT::Math::normal_cdf(sqrt(2*(NLL_one-minNLL)));
    double pvalue_zero=1-ROOT::Math::normal_cdf(sqrt(2*(NLL_zero-minNLL)));

    ofstream fout("fig/nllscan/"+jobname+"/nllscan_"+poiName+".txt",ios::out);
    fout<<setprecision(10)<<bf<<" "<<errLo<<" "<<errHi<<endl;
    if(negativeNLL<0){
      TString warningMsg=fabs(negativeNLL)<minimizerTolerance? "This is probably numerical fluctuation":"Larger than minimizer tolerance. Please double check!!!!";
      fout<<"There is negatvie dNLL point: "<<xtitle[poiName]<<"="<<negativeNLLmu
	  <<", dNLL="<<negativeNLL<<". "
	  <<warningMsg<<endl;
      cout<<"There is negatvie dNLL point: "<<xtitle[poiName]<<"="<<negativeNLLmu
	  <<", dNLL="<<negativeNLL<<". "
	  <<warningMsg<<endl;
      if(fabs(negativeNLL)>minimizerTolerance){
	cout<<"Press any key to continue..."<<endl;
	getchar();
      }
    }
    fout<<"Consistency with SM: "<<pvalue_one<<" "<<RooStats::PValueToSignificance(pvalue_one)<<"\\sigma"<<endl;
    fout<<"Consistency with B-only: "<<pvalue_zero<<" "<<RooStats::PValueToSignificance(pvalue_zero)<<"\\sigma"<<endl;
    fout.close();

    cout<<"Consistency with SM: "<<pvalue_one<<" "<<RooStats::PValueToSignificance(pvalue_one)<<"\\sigma"<<endl;
    cout<<"Consistency with B-only: "<<pvalue_zero<<" "<<RooStats::PValueToSignificance(pvalue_zero)<<"\\sigma"<<endl;

  }
  //************************************************************************************==
}
