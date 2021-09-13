#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooStatsHead.h"
#include "titleList.hh"

using namespace std;
using namespace CommonFunc;
using namespace RooStats;
const double epsilon=1e-7;
const double LARGENUM=1e37;
map<TString, TString> title;

double translateFCNCBR(double mu){
  return 0.5*(1-sqrt(1-4*mu*0.01*(1-0.01)))*100;
}

double median(double NLL, double minNLL)
{

  double delta_NLL = 2*fabs( NLL-minNLL ) ;
  double pvalue =  ROOT::Math::chisquared_cdf(delta_NLL,2);

  return pvalue;
}

int main(int argc, char **argv){
  //============================ Global booking and setting ==========================
  //   gErrorIgnoreLevel = kError+1;
  map<string,bool> Opt;
  Opt["2D"]=false;
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

  //======================================================================================
  if(Opt["2D"]){
    if(argc<5){
      cout<<"Usage: "<<argv[0]<<" "<<argv[1]<<" <jobname> <poi1Name,start,end,binw> <po2Name,start,end,binw> <input file dir>"<<endl;
      return 0;
    }

    
    title=createTitleList();
    
    TString jobname=argv[2];
    TString input1=argv[3];
    TString input2=argv[4];
    TString option=argv[5];

    bool m_rigorous=option.Contains("rigorous");
    TString infile="root/"+jobname;

    vector<TString> inputlist1=SplitString(input1,',');
    TString poi1Name=inputlist1[0];
    double start1=atof(inputlist1[1]);
    double end1=atof(inputlist1[2]);
    double binw1=atof(inputlist1[3]);
    int npoint1=int((end1-start1+epsilon)/binw1)+1;

    vector<TString> inputlist2=SplitString(input2,',');
    TString poi2Name=inputlist2[0];
    double start2=atof(inputlist2[1]);
    double end2=atof(inputlist2[2]);
    double binw2=atof(inputlist2[3]);
    int npoint2=int((end2-start2+epsilon)/binw2)+1;

    double xmin1=start1, xmax1=end1;
    double xmin2=start2, xmax2=end2;

    double arrayX[1000], arrayY[1000];
    double arrayXp[1000], arrayYp[1000];
    
    if(option.Contains("fcnc")){
      for (Int_t i = 0; i < npoint1; i++) {
	double poi1Value=xmin1+i*binw1;
	arrayX[i]=translateFCNCBR(poi1Value);
	// arrayX[i]=poi1Value;
      }

      for(Int_t i = 0; i < npoint2; i++){
	double poi2Value=xmin2+i*binw2;
	arrayY[i]=translateFCNCBR(poi2Value);
	// arrayY[i]=poi2Value;
      }
      // shift the bins so that each bin's center is the input value
      double binwX=arrayX[1]-arrayX[0];
      arrayXp[0]=arrayX[0]-binwX/2;
      
      for (Int_t i = 1; i < npoint1; i++) {
	arrayXp[i]=arrayX[i-1]+binwX/2;
	cout<<xmin1+(i-1)*binw1<<" "<<arrayX[i-1]<<" "
	    <<arrayXp[i-1]<<" "<<arrayXp[i]<<" "
	    <<binwX<<endl;
	binwX=(arrayX[i]-arrayXp[i])*2;

      }
      // getchar();
      arrayXp[npoint1]=arrayX[npoint1-1]+binwX/2;
      
      double binwY=arrayY[1]-arrayY[0];
      arrayYp[0]=arrayY[0]-binwY/2;
      
      for (Int_t i = 1; i < npoint2; i++) {
	arrayYp[i]=arrayY[i-1]+binwY/2;
	cout<<xmin2+(i-1)*binw2<<" "<<arrayY[i-1]<<" "
	    <<arrayYp[i-1]<<" "<<arrayYp[i]<<" "
	    <<binwY<<endl;
	binwY=(arrayY[i]-arrayYp[i])*2;
      }
      // getchar();
      arrayYp[npoint2]=arrayY[npoint2-1]+binwY/2;

    }
    double NLL;
    map<pair<double,double>, double> mp;
    vector<double> scan1,scan2;
    double poi1, poi2;
    double bf1=0, bf2=0;

    TCanvas* c = CreateCanvas("c","Contour List",800,600);

    Int_t i, j, TotalConts;

    double array_poi1[1000], array_poi2[1000], nll[1000][1000];
    
    // Create Histogram
    TH2D *HistStreamFn = new TH2D(jobname,  jobname,
 				  npoint1, xmin1-binw1/2, xmax1+binw1/2, npoint2, xmin2-binw2/2, xmax2+binw2/2);

    TH2D *HistNLL = new TH2D("hist2dnll",  "hist2dnll",
			     npoint1, xmin1-binw1/2, xmax1+binw1/2, npoint2, xmin2-binw2/2, xmax2+binw2/2);

    double minNLL=LARGENUM;

    TString inputtag=jobname;
    if(option.Contains("nosys")) inputtag=inputtag.ReplaceAll("_nosys","");
    if(option.Contains("nothe")) inputtag=inputtag.ReplaceAll("_nothe","");
    if(option.Contains("nores")) inputtag=inputtag.ReplaceAll("_nores","");
    if(option.Contains("nomigr")) inputtag=inputtag.ReplaceAll("_nomigr","");
    if(option.Contains("nonorm")) inputtag=inputtag.ReplaceAll("_nonorm","");
    if(option.Contains("nospur")) inputtag=inputtag.ReplaceAll("_nospur","");
    if(option.Contains("noenl")) inputtag=inputtag.ReplaceAll("_noenl","");
    if(option.Contains("nolca")) inputtag=inputtag.ReplaceAll("_nolca","");
    if(option.Contains("nomat")) inputtag=inputtag.ReplaceAll("_nomat","");
    if(option.Contains("nolss")) inputtag=inputtag.ReplaceAll("_nolss","");
    if(option.Contains("nobgm")) inputtag=inputtag.ReplaceAll("_nobgm","");
    bool m_uplumi=option.Contains("uplumi");
    bool m_extend=option.Contains("extend");

    TChain *tmin=new TChain("toys/nllscan");
    bool m_nominfile=getMinFile(tmin, inputtag, poi1Name);

    if(option.Contains("nominfile")) m_nominfile=true;
    if(!m_nominfile){
      tmin->SetBranchAddress("nll", &minNLL);
      tmin->SetBranchAddress(poi1Name, &bf1);
      tmin->SetBranchAddress(poi2Name, &bf2);
      tmin->GetEntry(0);
      cout<<"Reading min file: "<<tmin->GetCurrentFile()->GetName()<<endl;
      cout<<bf1<<" "<<bf2<<endl;
    }
    else{
      cerr<<"Minimum file cannot be found. Press any key to continue..."<<endl;
      getchar();
    }

    for (Int_t i = 0; i < npoint1; i++) {
      for(Int_t j = 0; j < npoint2; j++){

	double poi1Value=xmin1+i*binw1;
	double poi2Value=xmin2+j*binw2;

	nll[i][j]=LARGENUM;
	TChain* t = new TChain("toys/nllscan");
	if(t->Add("root/"+jobname+Form("/*%s=%.2f*%s=%.2f*.root",poi1Name.Data(),poi1Value,poi2Name.Data(),poi2Value))!=1){
	  cout<<"root/"+jobname+Form("/*%s=%.2f*%s=%.2f*.root",poi1Name.Data(),poi1Value,poi2Name.Data(),poi2Value)<<endl;
	  cout<<"Point "<<poi1Value<<":"<<poi2Value<<" does not exist."<<endl;

	  if(m_rigorous) abort();
	  continue;
	}

	t->SetBranchAddress("nll", &NLL);
	t->SetBranchAddress(poi1Name, &poi1);
	t->SetBranchAddress(poi2Name, &poi2);
	t->GetEntry(0);

	if(m_nominfile&&NLL<minNLL){
	  minNLL=NLL;
	  bf1=poi1;
	  bf2=poi2;
	}
	
	cout<<"+++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<title[poi1Name]<<" = "<<poi1<<endl;
	cout<<title[poi2Name]<<" = "<<poi2<<endl;
	cout<<"NLL = "<<NLL<<endl;
	// cout<<"Pvalue = "<<Med<<endl;
	cout<<"+++++++++++++++++++++++++++++++++++++++"<<endl;
	if(!isfinite(NLL)){
	  cerr<<title[poi1Name]<<" = "<<poi1<<" is not finite. Please intervine. Aborting..."<<endl;
	  //abort();
	  NLL=LARGENUM;
	  // NLL=minNLL;
	  // getchar();
	}
	nll[i][j]=NLL;

	// f->Close();
	SafeDelete(t);
      }
    }
    for (Int_t i = 0; i < npoint1; i++) {
      for(Int_t j = 0; j < npoint2; j++){
	if(nll[i][j]==LARGENUM) nll[i][j]=(nll[i-1][j]+nll[i+1][j]+nll[i][j-1]+nll[i][j+1])/4;
	double Med=median(nll[i][j],minNLL);
	HistStreamFn->SetBinContent(i+1,j+1, Med);
	HistNLL->SetBinContent(i+1,j+1,2*fabs( nll[i][j]-minNLL ));
      }
    }

    const int ncontour=2;
    Double_t contours[ncontour];
    contours[0] = 0.68;
    contours[1] = 0.95;

    HistStreamFn->SetContour(ncontour, contours);

    // Draw contours as filled regions, and Save points
    HistStreamFn->Draw("CONTZ,LIST");
    // HistStreamFn->Draw("surf");
    // HistStreamFn->SaveAs("test.root");
    // return 1;
    c->Update(); // Needed to force the plotting and retrieve the contours in TGraphs

    // Get Contours
    TObjArray *conts = (TObjArray*)gROOT->GetListOfSpecials()->FindObject("contours");
    conts->SetOwner(true);
    TList* contLevel = NULL;
    TGraph* curv     = NULL;
    TGraph* gc[ncontour]       = {NULL};

    Int_t nGraphs    = 0;
    TotalConts = 0;

    if (conts == NULL){
      printf("*** No Contours Were Extracted!\n");
      TotalConts = 0;
      return -1;
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

    TCanvas* c1 = CreateCanvas("c1","Contour List",800,600);
    //    c1->SetTopMargin(0.15);
    TH2F *hr = new TH2F("hr","hr", 2, xmin1, xmax1, 2, xmin2, xmax2);
    if(m_extend)
      hr = new TH2F("hr","hr", 2, xmin1, xmax1+0.5, 2, xmin2, xmax2+0.5);
    hr->GetXaxis()->SetTitle(title[poi1Name]);
    hr->GetYaxis()->SetTitle(title[poi2Name]);
    hr->GetYaxis()->SetTitleOffset(1);
    hr->Draw();
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
	// 	if(i==0) gc[i]->SetLineColor(ColorWheel(2));
	// 	else if(i==1) gc[i]->SetLineColor(ColorWheel(1));
	if(i==0) gc[i]->SetLineStyle(1);
	else if(i==1) gc[i]->SetLineStyle(2);
	gc[i]->Draw("C");

	curv = (TGraph*)contLevel->After(curv); // Get Next graph
      }
    }
    //     c1->Update();
    printf("\n\n\tExtracted %d Contours and %d Graphs \n", TotalConts, nGraphs );
    TMarker marker;
    marker.SetMarkerStyle(2);
    marker.SetMarkerSize(3);
    //     marker.SetMarkerColor(kRed);
    marker.DrawMarker(bf1,bf2);

    TMarker markerSM;
    markerSM.SetMarkerStyle(5);
    markerSM.SetMarkerSize(3);
    //     marker.SetMarkerColor(kRed);
    // markerSM.DrawMarker(1,1);
    double x1,y1,x2,y2;
    GetX1Y1X2Y2(c1,x1,y1,x2,y2);
    vector<TString> pavetext1,pavetext2;
    // pavetext1.push_back("#bf{#it{ATLAS}} internal");
    //pavetext1.push_back("#bf{#it{ATLAS}} preliminary");
    //     pavetext1.push_back("H#rightarrow#gamma#gamma");
    //pavetext1.push_back("2011-2012");
    //pavetext1.push_back("#it{m}_{#it{H}} = 125.4 GeV");
    //    pavetext1.push_back(Form("#hat{#mu}_{#it{ggF+ttH}}#timesB/B_{SM}=%.1f, #hat{#mu}_{#it{VBF+VH}}#timesB/B_{SM}=%.1f",mu_tH,mu_VH));

    //pavetext2.push_back("2011-2012");
    if(option.Contains("atlaspub")) pavetext2.push_back("#bf{#it{ATLAS}}");
    else if(option.Contains("atlasnote")) pavetext2.push_back("#bf{#it{ATLAS}} preliminary");
    else if(option.Contains("asimov")) pavetext2.push_back("#bf{#it{ATLAS}} simulation internal");
    else pavetext2.push_back("#bf{#it{ATLAS}} internal");

    // if(option.Contains("runii")) pavetext2.push_back("#scale[0.6]{#int}Ldt = 10 fb^{-1}, #sqrt{#it{s}} = 13 TeV");
    // else{
    //   pavetext2.push_back("#scale[0.6]{#int}Ldt = 4.5 fb^{-1}, #sqrt{#it{s}} = 7 TeV");
    //   pavetext2.push_back("#scale[0.6]{#int}Ldt = 20.3 fb^{-1}, #sqrt{#it{s}} = 8 TeV");
    // }

    // pavetext2.push_back("#it{H #rightarrow #gamma#gamma}, #it{m}_{#it{H}} = 125.4 GeV");

    // TPaveText* text1=CreatePaveText(x1+0.01,y1+0.01,x1+0.4,y1+0.25,pavetext1,0.045);
    TPaveText* text1=CreatePaveText(x2-0.25,y1+0.01,x2-0.03,y1+0.25,pavetext1,0.045);
    //TPaveText* text2=CreatePaveText(x2-0.4,y2-0.2,x2-0.01,y2-0.03,pavetext2,0.045);
    TPaveText* text2=CreatePaveText(x1+0.03,y1+0.03,x1+0.4,y1+0.3,pavetext2,0.045);
    if(m_uplumi)
      text2=CreatePaveText(x2-0.4,y2-0.3,x2-0.01,y2-0.03,pavetext2,0.045);
    TLegend* legend=FastLegend(x2-0.3,y2-0.25,x2-0.03,y2-0.03,0.05);
    legend->AddEntry(&marker, "Best fit","P");
    legend->AddEntry(gc[0], "68% CL","L");
    legend->AddEntry(gc[1], "95% CL","L");
    // legend->AddEntry(&markerSM, "SM","P");
    c1->cd();
    text1->Draw("same");
    text2->Draw("same");
    legend->Draw("same");
    c1->Update();
    //c1->SetGrid();
    system("mkdir -vp fig/contour/"+jobname);
    PrintCanvas(c1,"fig/contour/"+jobname+"/"+poi1Name+"_"+poi2Name);

    // *********************************************
    // Only for LHC-HCG mass combination:
    // Save the best fit value of all POIs
    const int npoi=2;
    // double poiValue[npoi]={ -998,  0,         0,        1,        1,        1,       1,               1,               1,              1,    1};
    // double poiPos[npoi]={0};
    double poiValue[npoi]={bf1, bf2}, poiPos[npoi]={0,1};
    
    TGraph *gr_best=new TGraph(npoi,poiPos,poiValue);
    gr_best->SetName("Graph_best");
    // *********************************************
    TFile *fhist=TFile::Open("fig/contour/"+jobname+"/hist.root","recreate");
    // TTree *t=new TTree("bf","bf");
    // t->Branch(poi1Name,&bf1,poi1Name+"/D");
    // t->Branch(poi2Name,&bf2,poi2Name+"/D");
    // t->Branch("nll",&minNLL,"nll/D");
    // t->Fill();
    // t->Write();
    gr_best->Write();
    HistStreamFn->SetName("hist2d");
    HistStreamFn->Write();
    HistNLL->Write();
    // conts->Write("Model_"+jobname,1);

    fhist->Close();

    cout<<"Best fit:"<<poi1Name<<"="<<bf1<<" "<<poi2Name<<"="<<bf2<<endl;
    // conts->SaveAs("test.root");
  }
  //======================================================================================
}

