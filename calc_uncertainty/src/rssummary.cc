#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"
#include "statistics.hh"
#include "titleList.hh"

using namespace std;
using namespace RooFit;
using namespace RooStats;

const int ncatOld=14;
const int ncatNew=12;

const double epsilon=1e-6;
const double LARGENUM=1e37;

double GetMean(double *array, int size){
  double sum=0;
  for(int i=0;i<size;i++) sum+=array[i];
  return sum/double(size);
}

double GetMean(vector<double> array){
  int size=array.size();
  double sum=0;
  for(int i=0;i<size;i++) sum+=array[i];
  return sum/double(size);
}

double GetMedian(vector<double> array){
  vector<double> temp=array;
  //cout<<"Sorting array"<<endl;
  sort(temp.begin(),temp.end());
  //cout<<temp.size()<<endl;
  return temp[temp.size()/2];
}

double GetDeviation(vector<double> array, double value){
  vector<double> temp=array;
  //cout<<"Sorting array"<<endl;
  sort(temp.begin(),temp.end());
  //cout<<temp.size()<<endl;
  int num=temp.size();
  double frac=0;
  for(int index=0;index<num;index++){
    if(temp[index]>value) break;
    frac = double(index)/double(num);
  }
  return frac;
}

double GetJackVar2(double *array, double mean, int size){
  double sum=0;
  for(int i=0;i<size;i++) sum+=(array[i]-mean)*(array[i]-mean);
  return sum*double(size-1)/double(size);
}

double GetJackVar(double *array, double mean, int size){
  return sqrt(GetJackVar2(array,mean,size));
}

map<TString, double> GetBootVar(vector<double> array){
  vector<double> temp=array;

  sort(temp.begin(),temp.end());
  map<TString, double> results;
  int num=temp.size();
  double n2s, n1s, median, p1s, p2s;
  for(int index=0;index<num;index++){
    double frac = double(index)/double(num);
    if (frac < LB2S)
      {
	n2s = temp[index];
      }
    if (frac < LB1S)
      {
	n1s = temp[index];
      }
    if (frac < B0S)
      {
	median = temp[index];
      }
    if (frac < UB1S)
      {
	p1s = temp[index];
      }
    if (frac < UB2S)
      {
	p2s = temp[index];
      }
  }

  results["n2s"]=median-n2s;
  results["n1s"]=median-n1s;
  results["med"]=median;
  results["p1s"]=p1s-median;
  results["p2s"]=p2s-median;

  return results;
}

double GetRho(double *x, double *y, int size){
  double xMean=GetMean(x,size);
  double yMean=GetMean(y,size);

  double covxy=0,varx=0,vary=0;
  for(int i=0;i<size;i++){
    covxy+=(x[i]-xMean)*(y[i]-yMean);
    varx+=(x[i]-xMean)*(x[i]-xMean);
    vary+=(y[i]-yMean)*(y[i]-yMean);
  }

  covxy=covxy/double(size);
  varx=sqrt(varx/double(size));
  vary=sqrt(vary/double(size));

  return covxy/(varx*vary);
}

double GetRho(vector<double> x, vector<double> y){
  int size=x.size();
  double xMean=GetMean(x);
  double yMean=GetMean(y);

  double covxy=0,varx=0,vary=0;
  for(int i=0;i<size;i++){
    covxy+=(x[i]-xMean)*(y[i]-yMean);
    varx+=(x[i]-xMean)*(x[i]-xMean);
    vary+=(y[i]-yMean)*(y[i]-yMean);
  }

  covxy=covxy/double(size);
  varx=sqrt(varx/double(size));
  vary=sqrt(vary/double(size));

  return covxy/(varx*vary);
}

int main(int argc, char** argv){
  //***************************= Global booking and setting ************************==
  //   gErrorIgnoreLevel = kError+1;
  SetAtlasStyle();
  map<string,bool> Opt;
  Opt["BOOTSTRAP"]=false;
  
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
  // ************************** Interpret results from jackknife method ***********************************
  if(Opt["BOOTSTRAP"]){
    if(argc<6){
      cout<<"Usage: "<<argv[0]<<" plot <jobname> <poiName> <input scalar toy ntuple> <input graviton toy ntuple> <option>"<<endl;
      return 0;
    }
    TString jobname=argv[2];
    TString poiName=argv[3];

    TString inputScalarToyName=argv[4];
    TString inputGravitonToyName=argv[5];
    
    TString option=argv[6];
    
    map<TString, TString> xtitle=createTitleList();   

    vector<double> muScalar, nllScalar, muGraviton, nllGraviton, deltamu;
    
    double minNLL=LARGENUM;
    double NLLScalar,poiScalar,bfScalar=0;
    double NLLGraviton,poiGraviton,bfGraviton=0;

    TString inputtag=jobname;

    double NLL_one=LARGENUM;
    double NLL_zero=LARGENUM;

    int realidx=0;

    TH1D *hGraviton=new TH1D("hGraviton","hGraviton",50,0.5,2.5);
    TH1D *hScalar=new TH1D("hScalar","hScalar",50,0.5,2.5);
    TH1D *hdel=new TH1D("hdel","hdel",50,-0.5,1.5);

    system("mkdir -vp fig/"+jobname);
    TString outputFile="fig/"+jobname+"/summary_"+poiName;
    unique_ptr<TFile> f(TFile::Open(outputFile+".root","recreate"));
    unique_ptr<TTree> t(new TTree("TreeAna","TreeAna"));

    ofstream fout(outputFile+".txt",ios::out);
    double _muGraviton, _muScalar, _nllGraviton, _nllScalar;
    t->Branch("muGraviton",&_muGraviton,"muGraviton/D");
    t->Branch("muScalar",&_muScalar,"muScalar/D");
    t->Branch("nllGraviton",&_nllGraviton,"nllGraviton/D");
    t->Branch("nllScalar",&_nllScalar,"nllScalar/D");

    TString outputDetail="fig/"+jobname+"/detail_"+poiName;
    ofstream fdetail(outputDetail+".txt",ios::out);


    unique_ptr<TChain> cScalar(CommonFunc::MakeChain("toy",inputScalarToyName,"badfile_scalar",inputScalarToyName.Contains(".root")));

    int ntoyScalar=cScalar->GetEntries();
    
    for (Int_t itoy = 0; itoy < ntoy; itoy++) {
	cout<<"root/"+jobname+Form("/*_%d_Scalar.root",i)<<endl;

	if(tScalar->Add("root/"+jobname+Form("/*_%d_Scalar.root",i))!=1){
	  cout<<"Point "<<poiValue<<" does not exist."<<endl;
	  if(m_rigorous) abort();
	  else continue;
	}

	tScalar->SetBranchAddress("nll", &NLLScalar);
	tScalar->SetBranchAddress(poiName, &poiScalar);
	tScalar->GetEntry(0);
	cout<<"+++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<xtitle[poiName]<<" = "<<poiScalar<<endl;
	cout<<"NLL = "<<NLLScalar<<endl;
	fdetail<<poiScalar<<"\t"<<NLLScalar<<endl;
	// if(poiScalar<0.5){
	// 	cout<<tScalar->GetCurrentFile()->GetName()<<endl; getchar();
	// }
	cout<<"+++++++++++++++++++++++++++++++++++++++"<<endl;
	if(!isfinite(NLLScalar)){
	  cerr<<xtitle[poiName]<<" = "<<poiScalar<<" is not finite. Please intervine. Aborting..."<<endl;
	  abort();
	}

	muScalar[realidx]=poiScalar;
	nllScalar[realidx]=NLLScalar;

	SafeDelete(tScalar);
      }

      nllGraviton[i]=LARGENUM;
      TChain* tGraviton = new TChain("toys/nllscan");
      cout<<"root/"+jobname+Form("/*_%d_Graviton.root",i)<<endl;

      if(m_onlyScalar){
	muGraviton[realidx]=0;
      }
      else{
	if(tGraviton->Add("root/"+jobname+Form("/*_%d_Graviton.root",i),-1)!=1){
	  cout<<"Point "<<poiValue<<" does not exist."<<endl;
	  if(m_rigorous) abort();
	  else continue;
	}

	tGraviton->SetBranchAddress("nll", &NLLGraviton);
	tGraviton->SetBranchAddress(poiName, &poiGraviton);
	tGraviton->GetEntry(0);
	cout<<"+++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<xtitle[poiName]<<" = "<<poiGraviton<<endl;
	cout<<"NLL = "<<NLLGraviton<<endl;
	fdetail<<poiGraviton<<"\t"<<NLLGraviton<<endl;
	cout<<"+++++++++++++++++++++++++++++++++++++++"<<endl;
	if(!isfinite(NLLGraviton)){
	  cerr<<xtitle[poiName]<<" = "<<poiGraviton<<" is not finite. Please intervine. Aborting..."<<endl;
	  abort();
	}

	muGraviton[realidx]=poiGraviton;
	nllGraviton[realidx]=NLLGraviton;

	SafeDelete(tGraviton);
      }

      deltamu[realidx]=muGraviton[realidx]-muScalar[realidx];

      hGraviton->Fill(muGraviton[realidx]);
      hScalar->Fill(muScalar[realidx]);
      hdel->Fill(deltamu[realidx]);

      _muGraviton=muGraviton[realidx];
      _muScalar=muScalar[realidx];
      _nllGraviton=nllGraviton[realidx];
      _nllScalar=nllScalar[realidx];

      t->Fill();
      realidx++;
    }

    fdetail.close();

    ntoy=realidx;
    nllGraviton.resize(ntoy);
    nllScalar.resize(ntoy);
    muGraviton.resize(ntoy);
    muScalar.resize(ntoy);
    deltamu.resize(ntoy);

    cout<<"Get median values...";
    cout<<muScalar.size()<<endl;
    double muScalarMean=GetMedian(muScalar);
    double muGravitonMean=GetMedian(muGraviton);
    double deltamuMean=GetMedian(deltamu);
    cout<<"Done"<<endl;
    map<TString, double> muScalarVar=GetBootVar(muScalar);
    map<TString, double> muGravitonVar=GetBootVar(muGraviton);
    map<TString, double> deltamuVar=GetBootVar(deltamu);

    double rho=GetRho(muGraviton,muScalar);

    //double pvalue=ROOT::Math::gaussian_cdf(0,deltamuVar,0.39362);
    //double pvalue=ROOT::Math::gaussian_cdf(0,deltamuVar,0.592);
    double pvalue=GetDeviation(deltamu,0);
    double sigma=RooStats::PValueToSignificance(pvalue);
    cout<<"Difference="<<diff<<", ntoy="<<ntoy<<endl;
    cout<<"Error: Graviton= -"<<muGravitonVar["n1s"]<<"+"<<muGravitonVar["p1s"]<<", Scalar=-"<<muScalarVar["n1s"]<<"+"<<muScalarVar["p1s"]<<endl;
    cout<<"rho: "<<rho<<", var(deltamu): -"<<deltamuVar["n1s"]<<"+"<<deltamuVar["p1s"]<<", sigma: "<<sigma<<endl;

    fout<<"Median Graviton="<<muGravitonMean<<", Median Scalar="<<muScalarMean<<endl;
    fout<<"Difference="<<diff<<", ntoy="<<ntoy<<endl;
    fout<<"Error: Graviton= -"<<muGravitonVar["n1s"]<<"+"<<muGravitonVar["p1s"]<<", Scalar=-"<<muScalarVar["n1s"]<<"+"<<muScalarVar["p1s"]<<endl;
    fout<<"rho="<<rho<<", var(deltamu)=-"<<deltamuVar["n1s"]<<"+"<<deltamuVar["p1s"]<<", sigma="<<sigma<<endl;

    fout.close();
    // for (Int_t i = 0; i < ntoy; i++){
    //   nll[i]=2*(nll[i]-minNLL);
    //   cout<<nll[i]<<" "<<mu[i]<<endl;
    // }
    gStyle->SetOptStat("nemr");
    gROOT->ForceStyle();

    TCanvas *c=new TCanvas("c","c",800,600);
    c->Divide(2,2);
    c->cd(1);
    hGraviton->SetMarkerSize(0.8);
    hGraviton->SetLineColor(kRed);
    hGraviton->SetMarkerColor(kRed);
    hGraviton->SetStats(true);

    hGraviton->GetXaxis()->SetTitle("#mu");
    hGraviton->Draw("E");

    c->cd(2);
    hScalar->SetMarkerSize(0.8);
    hScalar->SetLineColor(kBlue);
    hScalar->SetMarkerColor(kBlue);
    hScalar->SetStats(true);

    hScalar->GetXaxis()->SetTitle("#mu");
    hScalar->Draw("E");

    c->cd(3);
    //hdel->SetMarkerStyle(21);
    hdel->SetMarkerSize(0.8);
    hdel->GetXaxis()->SetTitle("#Delta#mu");
    hdel->Draw("E");


    TLine *line=new TLine(0,0,0,hdel->GetMaximum());
    line->SetLineColor(2);
    line->SetLineWidth(2);
    line->Draw("same");

    c->cd(4);
    TLegend *leg=FastLegend(0.2,0.2,0.8,0.8,0.07);
    leg->AddEntry(hGraviton,"Graviton analysis","lep");
    leg->AddEntry(hScalar,"Scalar analysis","lep");
    leg->AddEntry(hdel,"#Delta#mu = #mu_{Graviton}-#mu_{Scalar}","lep");
    leg->Draw();

    PrintCanvas(c,"fig/"+jobname+"/plot");
    f->cd();
    t->Write();
    hGraviton->Write();
    hScalar->Write();
    hdel->Write();
    f->Close();
  }
}

