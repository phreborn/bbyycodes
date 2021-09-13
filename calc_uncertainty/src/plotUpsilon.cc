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
const double mHcomb_highprec=125.0945697;

TGraph *gc[50]={NULL};

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
    thisUL=s->Eval(median);
    if((thisUL-target)*(s->Eval(end)-target)<0) begin=median;
    else if((thisUL-target)*(s->Eval(begin)-target)<0) end=median;
    counter++;
  }
  return median;//   return median;
}

double derivative(TSpline *s, double mH){
  double nll_mh=s->Eval(mH);
  double nll_mh_eps=s->Eval(mH+epsilon);

  double derivative=(nll_mh_eps-nll_mh)/epsilon;

  return derivative;
}

TGraph* plotContour(TCanvas *c1, TH2D *HistStreamFn, int color, int style, double width, bool draw2sigma=true){

  TCanvas* temp = CreateCanvas("temp","Contour List",800,600);

  Int_t i, j, TotalConts;

  const int ncontour=2;
  Double_t contours[ncontour];
  contours[0] = 0.68;
  contours[1] = 0.95;

  HistStreamFn->SetContour(ncontour, contours);
  temp->cd();
  
  // Draw contours as filled regions, and Save points
  HistStreamFn->Draw("CONTZ,LIST");
  temp->Update(); // Needed to force the plotting and retrieve the contours in TGraphs

  // Get Contours
  TObjArray *conts = (TObjArray*)gROOT->GetListOfSpecials()->FindObject("contours");
  TList* contLevel = NULL;
  TGraph* curv     = NULL;

  Int_t nGraphs    = 0;
  TotalConts = 0;

  if (conts == NULL){
    printf("*** No Contours Were Extracted!\n");
    TotalConts = 0;
    return NULL;
  } else {
    TotalConts = conts->GetSize();
  }

  printf("TotalConts = %d\n", TotalConts);

  for(i = 0; i < TotalConts; i++){
    contLevel = (TList*)conts->At(i);
    printf("Contour %d has %d Graphs\n", i, contLevel->GetSize());
    nGraphs += contLevel->GetSize();
  }

  nGraphs = 0;

  c1->cd();
  // if(firstplot){
  //   TH2F *hr = new TH2F("hr","hr", 2, xmin1, xmax1, 2, xmin2, xmax2);
  //   hr->GetXaxis()->SetTitle(xtitle[poi1Name]);
  //   hr->GetYaxis()->SetTitle(xtitle[poi2Name]);
  //   hr->Draw();
  // }
  Double_t x0, y0, z0;

  for(i = 0; i < TotalConts; i++){
    contLevel = (TList*)conts->At(i);
    z0 = contours[i];
    printf("Z-Level Passed in as:  Z = %f\n", z0);

    // Get first graph from list on curves on this level
    curv = (TGraph*)contLevel->First();
    for(j = 0; j < contLevel->GetSize(); j++){
      curv->GetPoint(0, x0, y0);
      nGraphs ++;
      printf("\tGraph: %d  -- %d Elements\n", nGraphs,curv->GetN());

      // Draw clones of the graphs to avoid deletions in case the 1st
      // pad is redrawn.
      gc[i] = (TGraph*)curv->Clone();
      gc[i]->SetLineColor(color);
      gc[i]->SetLineStyle(style+i);
      gc[i]->SetLineWidth(width);
      // else if(i==1) gc[i]->SetLineColor(ColorWheel(1));
      // if(i==0) gc[i]->SetLineStyle(1);
      // else if(i==1) gc[i]->SetLineStyle(2);
      if(i==0||(i>0 && draw2sigma)) gc[i]->DrawClone("C");

      curv = (TGraph*)contLevel->After(curv); // Get Next graph
    }
  }
  c1->Update();
  printf("\n\n\tExtracted %d Contours and %d Graphs \n", TotalConts, nGraphs );
  delete temp;
  return gc[0];
}

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
      cout<<"Usage: "<<argv[0]<<" plot <jobname> <poiName,start,end,binw> <option>"<<endl;
      return 0;
    }
    TString jobname=argv[2];
    TString inputList=argv[3];
    TString option=argv[4];
    
    double luminosity=20.3;

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
    bool m_stat=option.Contains("stat");
    
    if(option.Contains("normmu")){
      gSystem->Load("lib/libCombinedLimit.so");
    }
    ifstream fin(inputList,ios::in);
    vector<TString> inputSet, inputArg;
    vector<TString> legtext,legopt;
    vector<int> style,color;
    vector<double> width;
    map<TString, pair<double, double> > errMap;
    
    TString fileName, argument, legName, optName, styleName, colorName, widthName;
    while(fin>>fileName>>argument>>legName>>optName>>styleName>>colorName>>widthName){
      legName.ReplaceAll("~", " ");

      legtext.push_back(legName);
      legopt.push_back(optName);
      
      inputSet.push_back(fileName);
      inputArg.push_back(argument);
      style.push_back(atoi(styleName));
      color.push_back(atoi(colorName));
      width.push_back(atof(widthName));
      if(m_stat){
	inputSet.push_back(fileName+"_nosys");
	inputArg.push_back(argument);
	style.push_back(atoi(styleName)+1);
	color.push_back(atoi(colorName));
	width.push_back(atof(widthName)-1);
      }
      if(m_asimov){
	inputSet.push_back(fileName+"_asimov");
	inputArg.push_back(argument);
	style.push_back(atoi(styleName)+3);
	color.push_back(atoi(colorName));
	width.push_back(atof(widthName)-1);
      }
      cout<<fileName<<endl;
    }

    fin.close();
    
    int nsample=inputSet.size();
    vector<TString> inputlist=SplitString(inputArg[0],',');
    TString poiName=inputlist[0];
    double xmin=atof(inputlist[1]);
    double xmax=atof(inputlist[2]);

    for(int isam=0;isam<nsample;isam++){
      vector<TString> inputlist=SplitString(inputArg[isam],',');
      double start=atof(inputlist[1]);
      double end=atof(inputlist[2]);

      if(start<xmin) xmin=start;
      if(end>xmax) xmax=end;
    }
    
    TCanvas* c = CreateCanvas("c","nllscan",800,600);

    double ymin=0, ymax=7;

    TH1D *hframe=new TH1D("hframe", "hframe", 1000, xmin, xmax);
    
    hframe->GetXaxis()->SetTitle("#sigma [GeV]");
    if(option.Contains("xsec")) hframe->GetXaxis()->SetTitle("#sigma#timesBR_{X}^{fid.} [fb]");
    hframe->GetXaxis()->SetRangeUser(xmin,xmax);
    hframe->GetYaxis()->SetTitle("-2#Deltaln(L)");
    hframe->SetMaximum(7);
    hframe->GetXaxis()->SetTitleSize(0.06);
    if(option.Contains("4sigma")){
      hframe->SetMaximum(25);
      ymax=100;
    }
    if(option.Contains("3sigma")){
      hframe->SetMaximum(15);
      ymax=100;
    }

    hframe->SetLineWidth(0);
    hframe->SetMinimum(0);
    hframe->Draw();
    
    double x1,y1,x2,y2;
    GetX1Y1X2Y2(c,x1,y1,x2,y2);
    TLegend *leg=FastLegend(x2-0.3,y2-0.15,x2-0.03,y2-0.05,0.04);
    TString outputDir="fig/nllscan/"+jobname;
    system("mkdir -vp fig/nllscan/"+jobname);
    TFile *fgraph=TFile::Open(outputDir+"/graph_"+poiName+".root","recreate");

    int legidx=0;
    TLegend *legmu=NULL;

    ofstream fout("fig/nllscan/"+jobname+"/nllscanmulti_"+poiName+".txt",ios::out);
    
    for(int isam=0;isam<nsample;isam++){
      vector<TString> inputlist=SplitString(inputArg[isam],',');
      poiName=inputlist[0];
      double start=atof(inputlist[1]);
      double end=atof(inputlist[2]);
      double binw=atof(inputlist[3]);
      int npoint=int((end-start+epsilon)/binw)+1;

      cout<<poiName<<" "<<start<<" "<<end<<" "<<binw<<endl;
      Int_t i, j, TotalConts;

      TChain *tmin=new TChain("toys/nllscan");

      TString inputtag=inputSet[isam];
      if(!option.Contains("noreplace")){
	if(inputtag.Contains("nosys")) inputtag=inputtag.ReplaceAll("_nosys","");
	if(inputtag.Contains("nothe")) inputtag=inputtag.ReplaceAll("_nothe","");
	if(inputtag.Contains("noatlas")) inputtag=inputtag.ReplaceAll("_noatlas","");
	if(inputtag.Contains("nocms")) inputtag=inputtag.ReplaceAll("_nocms","");
	if(inputtag.Contains("nores")) inputtag=inputtag.ReplaceAll("_nores","");
	if(inputtag.Contains("nomigr")) inputtag=inputtag.ReplaceAll("_nomigr","");
	if(inputtag.Contains("nonorm")) inputtag=inputtag.ReplaceAll("_nonorm","");
	if(inputtag.Contains("nospur")) inputtag=inputtag.ReplaceAll("_nospur","");
	if(inputtag.Contains("noess")) inputtag=inputtag.ReplaceAll("_noess","");
      }

      bool m_nominfile=getMinFile(tmin, inputtag, poiName);

      if(option.Contains("nominfile")) m_nominfile=true;
      else{
	if(m_nominfile ){
	  cerr<<"Minimium file cannot be found! Press any key to continue"<<endl;
	  getchar();
	}
      }
      double mH[1000]={0}, nll[1000]={0}, nllder[1000];
      double muF_gg[1000], muV_gg[1000], mu_ZZ[1000], mu[1000];
      double lambda_muF_gg[1000], lambda_muV_gg[1000], lambda_mu_ZZ[1000], lambda_mu[1000];
      double minNLL=LARGENUM;
      double NLL,poi,bf=0;
      double muF_gg_bf, muV_gg_bf, mu_ZZ_bf, mu_bf;
      double lambda_muF_gg_bf, lambda_muV_gg_bf, lambda_mu_ZZ_bf, lambda_mu_bf;

      double NLL_one=LARGENUM;
      double NLL_zero=LARGENUM;

      int nrealpoint=0;
      int realidx=0;

      if(!m_nominfile){
	tmin->SetBranchAddress("nll", &minNLL);
	tmin->SetBranchAddress(poiName, &bf);
	tmin->GetEntry(0);
	cout<<"Reading min file: "<<tmin->GetCurrentFile()->GetName()<<endl;
	// getchar();
      }

      for (Int_t i = 0; i < npoint; i++) {
	double poiValue=start+i*binw;
	nll[realidx]=LARGENUM;
	TChain* t = new TChain("toys/nllscan");
	TString inputScanFile="root/"+inputSet[isam]+Form("/*%s=%.4f_.*.root",poiName.Data(),poiValue);
	if(option.Contains("scalelumi")) inputScanFile="root/"+inputSet[isam]+Form("/*%s=%.4f_.*.root",poiName.Data(),poiValue);
	cout<<inputScanFile<<endl;
	if(t->Add(inputScanFile)!=1){
	  cout<<"Point "<<poiValue<<" does not exist."<<endl;
	  if(m_rigorous) abort();
	  else continue;
	}

	nrealpoint++;
	t->SetBranchAddress("nll", &NLL);
	t->SetBranchAddress(poiName, &poi);

	t->GetEntry(0);

	cout<<"+++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<title[poiName]<<" = "<<poi<<endl;
	cout<<"NLL = "<<NLL<<endl;
	cout<<"+++++++++++++++++++++++++++++++++++++++"<<endl;

	if(!isfinite(NLL)){
	  cerr<<title[poiName]<<" = "<<poi<<" is not finite. Please intervine. Aborting..."<<endl;
	  exit(0);
	}
	if(m_nominfile&&NLL<minNLL){
	  minNLL=NLL;
	  bf=poi;
	}

	mH[realidx]=poi;
	nll[realidx]=NLL;
	if(fabs(mH[realidx]-1)<epsilon) NLL_one=NLL;
	if(fabs(mH[realidx]-0)<epsilon) NLL_zero=NLL;
	SafeDelete(t);
	realidx++;
	if(!m_nominfile&&bf>poiValue&&bf<poiValue+binw){
	  // Here we are just making summary plot. Not need to be picky
	  if(fabs(bf-poiValue)<epsilon) continue;
	  mH[realidx]=bf;			
	  nll[realidx]=minNLL;

	  realidx++;
	}
      }

      npoint=realidx;

      for (Int_t i = 0; i < npoint; i++){
	nll[i]=2*(nll[i]-minNLL);
	cout<<nll[i]<<" "<<mH[i]<<endl;
      }
      c->cd();
      TGraph *gr=new TGraph(npoint,mH,nll);
      gr->SetName(inputtag);
      gr->SetMaximum(ymax);
      gr->SetMinimum(ymin);
      gr->SetLineColor(color[isam]);
      gr->SetLineStyle(style[isam]);
      gr->GetXaxis()->SetTitle("#sigma [GeV]");
      gr->GetXaxis()->SetRangeUser(xmin,xmax);
      gr->GetYaxis()->SetTitle("-2#Deltaln(L)");
      
      gr->SetLineWidth(width[isam]);
      gr->DrawClone("L");

      fgraph->cd();
      gr->Write();

      if((!m_stat||!inputSet[isam].Contains("nosys"))&&
	 (!m_asimov||!inputSet[isam].Contains("asimov"))){
	leg->AddEntry(gr, legtext[legidx], legopt[legidx]);
	legidx++;
      }

      // Check the change of mu as a function of mH
      TSpline5 *s=new TSpline5("grs",gr);
      s->SetLineWidth(2);
      //s->Draw("same");

      double errLo=xmin;
      double errHi=xmax;
      if(!option.Contains("noerrlo")) errLo=BinarySearch(s,1,xmin,bf,1e-5);
      if(!option.Contains("noerrhi")) errHi=BinarySearch(s,1,bf,xmax,1e-5);

      DrawConstantLine(c,1,xmin,xmax,1,2,1);
      DrawConstantLine(c,4,xmin,xmax,1,2,1);
      if(option.Contains("3sigma")) DrawConstantLine(c,9,xmin,xmax,1,2,1);
      if(option.Contains("4sigma")){
	DrawConstantLine(c,9,xmin,xmax,1,2,1);
	DrawConstantLine(c,16,xmin,xmax,1,2,1);
      }
      double slopeLo=(s->Eval(errLo+1e-3)-s->Eval(errLo))/(1e-3);
      double slopeHi=(s->Eval(errHi)-s->Eval(errHi-1e-3))/(1e-3);
      errLo=bf-errLo;
      errHi=errHi-bf;
      errMap[inputSet[isam]]=make_pair(errHi,errLo);
      
      fout<<setprecision(10)<<bf<<" "<<errLo<<" "<<errHi<<endl;
      fout<<"Compatibility with 0: "<<sqrt(s->Eval(0))<<endl;
      if(option.Contains("ratio")){
	fout<<"Compatibility with gg: "<<sqrt(s->Eval(1/4.693))<<endl;
	fout<<"Compatibility with qq: "<<sqrt(s->Eval(1/2.692))<<endl;
	TLine *ggLine=new TLine(1/4.693,0,1/4.693,16);
	TLine *qqbarLine=new TLine(1/2.692,0,1/2.692,16);
	ggLine->SetLineWidth(2);
	ggLine->SetLineStyle(4);
	ggLine->SetLineColor(2);
	ggLine->Draw("same");

	qqbarLine->SetLineWidth(2);
	qqbarLine->SetLineStyle(4);
	qqbarLine->SetLineColor(4);
	qqbarLine->Draw("same");

	if(isam==nsample-1){
	  leg->AddEntry(ggLine,"gg production","l");
	  leg->AddEntry(qqbarLine,"q#bar{q} production","l");
	  c->SetLogx();
	}

      }
      if(option.Contains("stat")&&inputSet[isam].Contains("nosys")){
	TString fullScanName=inputSet[isam];
	fullScanName=fullScanName.ReplaceAll("_nosys","");
	double errHiFull=errMap[fullScanName].first, errLoFull=errMap[fullScanName].second;
	double errHiStat=errHi,errLoStat=errLo;
	double errHiSyst=sqrt(errHiFull*errHiFull-errHiStat*errHiStat);
	double errLoSyst=sqrt(errLoFull*errLoFull-errLoStat*errLoStat);
	fout<<"Uncertainty split: "
	    <<Form("%s=%.4f+%.4f-%.4f=%.4f+%.4f-%.4f(stat.)+%.4f-%.4f(syst.)", poiName.Data(), bf, errHiFull, errLoFull, bf, errHiStat, errLoStat, errHiSyst, errLoSyst)
	    <<endl;
	cout<<"Uncertainty split: "
	    <<Form("%s=%.4f+%.4f-%.4f=%.4f+%.4f-%.4f(stat.)+%.4f-%.4f(syst.)", poiName.Data(), bf, errHiFull, errLoFull, bf, errHiStat, errLoStat, errHiSyst, errLoSyst)
	    <<endl;

      }
    }
    fgraph->Close();

    vector<TString> pavetext, pavetext2;
    pavetext.push_back("#bf{#it{ATLAS}} internal");
    if(option.Contains("Hu_fix")) pavetext2.push_back(title["mu_Hu"].ReplaceAll(" [%]","")+" = 0");
    if(option.Contains("Hc_fix")) pavetext2.push_back(title["mu_Hc"].ReplaceAll(" [%]","")+" = 0");
    if(option.Contains("Hu_free")) pavetext2.push_back(title["mu_Hu"].ReplaceAll(" [%]","")+" free");
    if(option.Contains("Hc_free")) pavetext2.push_back(title["mu_Hc"].ReplaceAll(" [%]","")+" free");
    // pavetext.push_back("2011-2012");
    // pavetext.push_back("#scale[0.6]{#int}Ldt = 4.5 fb^{-1}, #sqrt{#it{s}} = 7 TeV");
    // pavetext.push_back("#scale[0.6]{#int}Ldt = 20.3 fb^{-1}, #sqrt{#it{s}} = 8 TeV");
    
    if(option.Contains("2015")) pavetext.push_back("Data 2015, #sqrt{#it{s}} = 13 TeV, 3.2 fb^{-1}");
    if(option.Contains("2016")) pavetext.push_back("Data 2016, #sqrt{#it{s}} = 13 TeV, 12.2 fb^{-1}");
    if(option.Contains("8tev")) pavetext.push_back("#sqrt{#it{s}} = 8 TeV, 20.3 fb^{-1}");

    TPaveText* text=NULL, *text2=NULL;

    double x1p=0,x2p=0,y1p=0,y2p=0;

    TBox *box = NULL;
    if(option.Contains("4sigma")) box=new TBox (xmin, 17, xmax, 25);
    else box=new TBox (xmin, 4.2, xmax, 7);
    if(option.Contains("normmu")){
      box = new TBox (xmin, 4, xmax, 7);
    }
    box->SetFillStyle(1001);
    box->SetFillColor(0);
    if(!option.Contains("extend")&&!option.Contains("3sigma")&&!option.Contains("4sigma")) box->Draw("same");

    if(option.Contains("box")) box->Draw("same");
    x1p=x1+0.03;
    x2p=x1+0.3;
    y1p=y2-0.25;
    y2p=y2-0.03;
    
    text=CreatePaveText(x1p,y1p,x2p,y2p,pavetext,0.045);
    text2=CreatePaveText(x1p+0.02,y1p-0.08,x2p,y1p,pavetext2,0.038);
    // text2->SetFillStyle(1001);
    c->cd();
    text->Draw("same");
    text2->Draw("same");
    if(m_stat){
      TLine *nosysLine=new TLine(0,0,1,1);
      nosysLine->SetLineWidth(2);
      nosysLine->SetLineStyle(2);
      // leg->AddEntry(nosysLine, "Without systematics", "l");
      leg->AddEntry(nosysLine, "Stat. uncert. only", "l");
    }

    if(m_asimov){
      TLine *nosysLine=new TLine(0,0,1,1);
      nosysLine->SetLineWidth(2);
      nosysLine->SetLineStyle(4);
      // leg->AddEntry(nosysLine, "Without systematics", "l");
      leg->AddEntry(nosysLine, "Post-fit Asimov", "l");
    }

    if(option.Contains("box")) leg->SetFillStyle(1001);
    leg->Draw("same");

    if(option.Contains("bonly")) DrawVerticalLine(c,0,0,5,1,2,2);
    if(option.Contains("SM")) DrawVerticalLine(c,1,0,5,1,2,2);

    
    c->RedrawAxis();

    TString outputCanvas="fig/nllscan/"+jobname+"/nllscanmulti_"+poiName;
    if(m_stat) outputCanvas+="_stat";
    PrintCanvas(c,outputCanvas);
    fout.close();
  }
  //************************************************************************************==
  if(Opt["2D"]){
    if(argc<4){
      cout<<"Usage: "<<argv[0]<<" plot <jobname> <poiName,start,end,binw> <option>"<<endl;
      return 0;
    }
    TString jobname=argv[2];
    TString inputList=argv[3];
    TString option=argv[4];
    
    double luminosity=20.3;

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

    ifstream fin(inputList,ios::in);
    vector<TString> inputSet, inputArg;
    vector<TString> legtext,legopt;
    vector<int> style,color,markerStyle;
    vector<double> width;
    TString graphName, argument, legName, optName, styleName, colorName, widthName, markerName;
    while(fin>>graphName>>argument>>legName>>optName>>styleName>>colorName>>widthName>>markerName){
      legName.ReplaceAll("~", " ");
      inputSet.push_back(graphName);
      inputArg.push_back(argument);
      legtext.push_back(legName);
      legopt.push_back(optName);
      style.push_back(atoi(styleName));
      color.push_back(atoi(colorName));
      width.push_back(atof(widthName));
      markerStyle.push_back(atoi(markerName));
      
      cout<<graphName<<endl;
    }

    fin.close();


    TCanvas* c = CreateCanvas("c", "nllscan",800,600);

    double x1,y1,x2,y2;
    GetX1Y1X2Y2(c,x1,y1,x2,y2);
    TLegend *leg=FastLegend(x2-0.23,y2-0.2,x2-0.03,y2-0.03,0.04);
    if(option.Contains("legleft")) leg=FastLegend(x1+0.03,y2-0.15,x1+0.33,y2-0.03,0.04);
    if(option.Contains("split")) leg->SetNColumns(2);
    if(option.Contains("box")) leg->SetFillStyle(1001);
    int nsample=inputSet.size();

    vector<TString> inputlist=SplitString(inputArg[0],',');
    TString poiXName=inputlist[0];
    double xmin=atof(inputlist[1]);
    double xmax=atof(inputlist[2]);
    TString poiYName=inputlist[3];
    double ymin=atof(inputlist[4]);
    double ymax=atof(inputlist[5]);

    TH2D *hframe=new TH2D("hframe", "hframe", 1000, xmin, xmax, 1000, ymin, ymax);
    
    hframe->GetXaxis()->SetTitle("#sigma [GeV]");
    hframe->GetXaxis()->SetRangeUser(xmin,xmax);
    hframe->GetYaxis()->SetTitle(title[poiYName]);
    if(option.Contains("xsec")) hframe->GetXaxis()->SetTitle("#sigma#timesBR_{X}^{fid.} [fb]");
    hframe->GetXaxis()->SetTitleSize(0.06);
    hframe->GetYaxis()->SetTitleSize(0.06);
    hframe->GetYaxis()->SetTitleOffset(1);
    hframe->GetYaxis()->SetRangeUser(ymin,ymax);

    TString outputDir="fig/contour/"+jobname;
    system("mkdir -vp fig/contour/"+jobname);

    hframe->Draw();

    gStyle->SetMarkerSize(0.02);
    
    for(int isam=0;isam<nsample;isam++){
 
      TString atlasInputFileName="fig/contour/"+inputSet[isam]+"/hist.root";
      cout<<atlasInputFileName<<endl;

      TFile *atlasInputFile=TFile::Open(atlasInputFileName,"read");

      TH2D *histATLAS=(TH2D*)atlasInputFile->Get("hist2d");

      TGraph *grATLAS=plotContour(c, histATLAS, color[isam], style[isam], width[isam], !option.Contains("no2sigma"));

      TGraph *grATLASBest=(TGraph*)atlasInputFile->Get("Graph_best");
      
      double bfxATLAS, bfyATLAS, dummy;
      grATLASBest->GetPoint(0,dummy, bfxATLAS);
      grATLASBest->GetPoint(1,dummy, bfyATLAS);
      
      TMarker *mATLAS=new TMarker();
      // mATLAS.SetMarkerStyle(5);
      mATLAS->SetMarkerStyle(markerStyle[isam]);
      mATLAS->SetMarkerSize(3);
      mATLAS->SetMarkerColor(color[isam]);

      if(option.Contains("split")) leg->AddEntry(mATLAS, " ", "p");
      
      cout<<bfxATLAS<<" "<<bfyATLAS<<" "<<dummy<<endl;
      mATLAS->DrawMarker(bfxATLAS,bfyATLAS);
      
      leg->AddEntry(grATLAS, legtext[isam], legopt[isam]);

    }

    vector<TString> pavetext, pavetext2;
    pavetext.push_back("#bf{#it{ATLAS}} internal");
    // pavetext.push_back("2011-2012");
    // pavetext.push_back("#scale[0.6]{#int}Ldt = 4.5 fb^{-1}, #sqrt{#it{s}} = 7 TeV");
    // pavetext.push_back("#scale[0.6]{#int}Ldt = 20.3 fb^{-1}, #sqrt{#it{s}} = 8 TeV");
    pavetext.push_back("#sqrt{#it{s}} = 13 TeV, 3.2 fb^{-1}");
    if(option.Contains("combined")) pavetext2.push_back("Combined");
    
    TPaveText* text=NULL, *text2=NULL;

    double x1p=0,x2p=0,y1p=0,y2p=0;

    if(m_textright) {
      x1p=x2-0.45;
      x2p=x2-0.05;
    }
    else if(m_textmiddle){
      x1p=x1+0.2;
      x2p=x2-0.3;
    }
    else{
      x1p=x1+0.05;
      x2p=x1+0.45;
    }

    if(m_textlow){
      y1p=y1+0.05;
      y2p=y1+0.4;
    }
    else{
      y1p=y2-0.15;
      y2p=y2-0.03;
    }

    x1p=x1+0.03;
    x2p=x1+0.3;
    y1p=y2-0.2;
    y2p=y2-0.03;
    text=CreatePaveText(x1p,y1p,x2p,y2-0.05,pavetext,0.045);
    // if(option.Contains("right")) text=CreatePaveText(x2-0.43,y1p,x2-0.03,y2-0.04,pavetext,0.045);
    if(option.Contains("right")) text=CreatePaveText(x2-0.35,y1p,x2-0.03,y2-0.04,pavetext,0.045);

    text2=CreatePaveText(x2-0.35,y1p-0.07,x2-0.03,y1p,pavetext2,0.045);
    
    double xx[1], yy[1];
    TGraph *onesigmaLine=new TGraph(1,xx,yy);
    onesigmaLine->SetLineWidth(2);

    TGraph *twosigmaLine=new TGraph(1,xx,yy);
    twosigmaLine->SetLineWidth(2);
    twosigmaLine->SetLineStyle(2);

    TMarker null;
    if(option.Contains("null")){
      null.SetMarkerStyle(2);
      null.SetMarkerSize(3);
      null.DrawMarker(0,0);
    }
    
    TMarker marker;
    marker.SetMarkerStyle(5);
    marker.SetMarkerSize(3);
    
    c->cd();
    text->Draw("same");
    text2->Draw("same");

    TLegend* legend=FastLegend(x1+0.03,y1+0.02,x1+0.2,y1+0.23,0.045);
    if(option.Contains("narrowleg")) legend=FastLegend(x1+0.03,y1+0.02,x1+0.2,y1+0.15,0.045);
    if(option.Contains("legleft")) legend=FastLegend(x1+0.03,y1+0.03,x1+0.2,y1+0.25,0.045);
    if(option.Contains("legup")) legend=FastLegend(x1+0.5,y2-0.2,x2-0.05,y2-0.05,0.045);
    if(option.Contains("null")) legend->AddEntry(&null, "Standard Model","P");
    legend->AddEntry(&marker, "Best fit","P");
    if(!option.Contains("no1sigma")) legend->AddEntry(onesigmaLine, "68% CL","L");
    if(!option.Contains("no2sigma")) legend->AddEntry(twosigmaLine, "95% CL","L");
    
    if(!m_noleg){
      if(nsample>1) leg->Draw("same");
      legend->Draw("same");
      // legexp->Draw("same");
    }

    TString outputCanvas="fig/contour/"+jobname+"/contourmulti_"+poiXName+"_"+poiYName;

    c->Update();
    c->RedrawAxis();

    // if(poiName="CV"){
    //   if(m_negative) outputCanvas+="_negative";
    //   else outputCanvas+="_positive";
    // }
    PrintCanvas(c,outputCanvas);
  }
  //************************************************************************************==

}
