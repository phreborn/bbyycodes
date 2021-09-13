#include "CommonHead.h"
#include "CommonFunc.h"
#include "MxAODNtup.h"
#include "tout.h"

using namespace std;

int main(int argc, char** argv){
  map<string,bool> Opt;
  Opt["DATA"]=false;
  Opt["MC"]=false;

  TString myOptList="";
  if(argc>1) myOptList=argv[1];
  myOptList.ToUpper();
  if (myOptList != "") {
    for (std::map<std::string,bool>::iterator it = Opt.begin(); it != Opt.end(); it++) it->second = false;

    std::vector<TString> olist = CommonFunc::SplitString( myOptList, ',' );
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
  //************************************************************************************==
  if(Opt["DATA"]){
    CommonFunc::SetAtlasStyle();
    TString inputFileName=argv[2];
    TString outputFileName=argv[3];
    TString selection=argv[4];
  
    TChain *c=CommonFunc::MakeChain("CollectionTree", inputFileName, "badfile", inputFileName.Contains(".root"));

    int nevt=c->GetEntries();

    MxAODNtup *p=new MxAODNtup(c);
  
    // Scan the pT cut in following step sizes: 35, 45, 55, 65, 75, 85, 95
    // const int ncut=7;
    const int ncut=4;
    TH1F *hData[ncut];
    double pTCut[ncut]={35, 55, 75, 95};

    for(int icut=0;icut<ncut;icut++){
      hData[icut]=new TH1F(Form("hcut_%.0f", pTCut[icut]),Form("hcut_%.0f", pTCut[icut]),40, 200, 1000);
      hData[icut]->Sumw2();
      hData[icut]->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
      hData[icut]->GetYaxis()->SetTitle("Events / 20 GeV");
      hData[icut]->SetLineColor(CommonFunc::ColorWheel(icut));
      hData[icut]->SetMarkerColor(CommonFunc::ColorWheel(icut));
      hData[icut]->SetMarkerStyle(CommonFunc::MarkerWheel(icut));
    }
  
    for(int ievt=0;ievt<nevt;ievt++){
      c->GetEntry(ievt);
      if(!(p->isPassedPID&&p->isPassedIsolationLowHighMyy&&p->m_yy>200*CommonFunc::GeV)) continue;
      if(fabs(p->cosTS_yy)<0.8) continue;

      for(int icut=0;icut<ncut;icut++){
	if(p->pt->at(0)>pTCut[icut]*CommonFunc::GeV&&p->pt->at(1)>pTCut[icut]*CommonFunc::GeV) hData[icut]->Fill(p->m_yy/CommonFunc::GeV);
      }
    }

    TCanvas *cv=new TCanvas("cv","cv",800,600);
    TLegend *leg=CommonFunc::FastLegend(0.5,0.73,0.9,0.93,0.04);
    leg->SetFillStyle(1001);
    leg->SetNColumns(2);
    for(int icut=0;icut<ncut;icut++){
      hData[icut]->Draw("same,E");
      leg->AddEntry(hData[icut],Form("p_{T}>%.0f GeV",pTCut[icut]),"p");
    }
    // TLine left (675, hData[0]->GetMinimum(), 675, hData[0]->GetMaximum());
    // TLine right(775, hData[0]->GetMinimum(), 775, hData[0]->GetMaximum());

    TLine left (600, hData[0]->GetMinimum(), 600, hData[0]->GetMaximum());
    TLine right(800, hData[0]->GetMinimum(), 800, hData[0]->GetMaximum());

    left.SetLineColor(kRed);
    right.SetLineColor(kRed);
    left.SetLineStyle(4); left.SetLineWidth(2);
    right.SetLineStyle(4); right.SetLineWidth(2);

    left.Draw("same");
    right.Draw("same");
  
    leg->Draw("same");
    cv->SetLogy();
    // cv->SetGrid();
    cv->RedrawAxis();
    CommonFunc::PrintCanvas(cv,outputFileName);
  }
  //************************************************************************************==
  if(Opt["MC"]){
    CommonFunc::SetAtlasStyle();
    TString inputFileName=argv[2];
    TString outputFileName=argv[3];
    TString selection=argv[4];
  
    TChain *c=CommonFunc::MakeChain("tout", inputFileName, "badfile", inputFileName.Contains(".root"));

    int nevt=c->GetEntries();

    tout *p=new tout(c);
  
    // Scan the pT cut in following step sizes: 35, 45, 55, 65, 75, 85, 95
    const int ncut=7;
    TH1F *hData[ncut];
    // double pTCut[ncut]=selection=="EE"?{55, 65, 75, 85, 90, 95, 100}:{55, 95, 135, 175, 215, 255, 295};
    double pTCut[ncut]={55, 80, 90, 100, 110, 120, 130};

    for(int icut=0;icut<ncut;icut++){
      hData[icut]=new TH1F(Form("hcut_%.0f", pTCut[icut]),Form("hcut_%.0f", pTCut[icut]),40, 200, 1000);
      hData[icut]->Sumw2();
      hData[icut]->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
      hData[icut]->GetYaxis()->SetTitle("A. U. / 20 GeV");
      hData[icut]->SetLineColor(CommonFunc::ColorWheel(icut));
      hData[icut]->SetMarkerColor(CommonFunc::ColorWheel(icut));
      hData[icut]->SetMarkerStyle(CommonFunc::MarkerWheel(icut));
    }
  
    for(int ievt=0;ievt<nevt;ievt++){
      c->GetEntry(ievt);
      if(!p->isPassEKHI) continue;
      if(selection=="EE"){
	if(!((p->eta_s2_1st>1.45&&p->eta_s2_2nd<-1.45)||(p->eta_s2_1st<-1.45&&p->eta_s2_2nd>1.45))) continue;
      }
      for(int icut=0;icut<ncut;icut++){
	if(p->pt_1st>pTCut[icut]*CommonFunc::GeV&&p->pt_2nd>pTCut[icut]*CommonFunc::GeV) hData[icut]->Fill(p->m_yy/CommonFunc::GeV, p->vertexWeight*p->crossSectionBRfilterEff/p->totalEvents);
      }
    }

    TCanvas *cv=new TCanvas("cv","cv",800,600);
    TLegend *leg=CommonFunc::FastLegend(0.5,0.73,0.9,0.93,0.04);
    leg->SetFillStyle(1001);
    leg->SetNColumns(2);
    for(int icut=0;icut<ncut;icut++){
      hData[icut]->Draw("same,E");
      leg->AddEntry(hData[icut],Form("p_{T}>%.0f GeV",pTCut[icut]),"p");
    }
    // TLine left (675, hData[0]->GetMinimum(), 675, hData[0]->GetMaximum());
    // TLine right(775, hData[0]->GetMinimum(), 775, hData[0]->GetMaximum());

    hData[0]->SetMaximum(hData[0]->GetMaximum()*10);
    TLine left (600, hData[0]->GetMinimum(), 600, hData[0]->GetMaximum());
    TLine right(800, hData[0]->GetMinimum(), 800, hData[0]->GetMaximum());

    left.SetLineColor(kRed);
    right.SetLineColor(kRed);
    left.SetLineStyle(4); left.SetLineWidth(2);
    right.SetLineStyle(4); right.SetLineWidth(2);

    left.Draw("same");
    right.Draw("same");
  
    leg->Draw("same");
    cv->SetLogy();
    // cv->SetGrid();
    cv->RedrawAxis();
    CommonFunc::PrintCanvas(cv,outputFileName);
  }
}

