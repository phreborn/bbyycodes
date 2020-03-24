#include <string>
#include <iostream>
#include "Plotting.h"
#include "JSONDoc.h"
#include "Controller.h"
#include "../../bbyyPlotter/atlasstyle-00-03-05/AtlasStyle.C"
#include "../../bbyyPlotter/atlasstyle-00-03-05/AtlasLabels.C"
#include "../../bbyyPlotter/atlasstyle-00-03-05/AtlasUtils.C"



void Plotting::DoPlots(std::string histoName,std::string yaxislabel,std::string xaxislabel){
  SetAtlasStyle();

  TCanvas *c1 =  new TCanvas("canvas","canvas",600,600);
  TPad *padhigh = new TPad("padhigh","padhigh",0.,0.28,1.,1.,0);

  padhigh->Draw();
  padhigh->cd();
  padhigh->SetGrid(0,0);
  padhigh->SetBottomMargin(0.05);
  padhigh->Update();
  padhigh->Modified();

  THStack *stack = new THStack();
  TH1F *h_sum_MC = new TH1F();
  TH1F *hratio = new TH1F();

  auto leg = TLegend(0.70,0.70,0.85,0.90);
  leg.SetLineColor(kWhite);
  leg.SetFillColor(kWhite);
  leg.SetTextSize(0.05);
  leg.SetBorderSize(0);

  leg.SetTextSize(0.04);
  leg.SetTextFont(42);

  mytest::JSONData& document=Controller::GetDocument();

  std::string logging;

  const std::vector<std::string> cutFlows={"Selection"};

  for (auto iSample:document.samples.samples) {
    mytest::aSample thisSample=document.samples.samples[iSample.first];
    const std::string sampleName=iSample.first;
    std::cout<<" sampleName "<<sampleName<<std::endl;

    for (auto iCut: cutFlows){
      std::string fileDir = "plots/"+sampleName+"_"+iCut+".root";
      std::cout<<" fileDir "<<fileDir<<std::endl;
      std::string legendEntry=thisSample.legendEntry;
      double color=stod(thisSample.color);

      TFile *file = new TFile(fileDir.c_str());
      std::cout<<" file opened "<<file<<std::endl;
      TH1F *histo = (TH1F*)file->Get(histoName.c_str());
      std::cout<<" histogram "<<histoName<<" pointer "<<histo<<std::endl;           
      int nbin = histo -> GetNbinsX();
      double ubin = histo -> GetXaxis()->GetXmax();
      double lbin = histo -> GetXaxis()->GetXmin();
      hratio -> SetBins(nbin,lbin,ubin);
      h_sum_MC -> SetBins(nbin,lbin,ubin);
      if(sampleName != "data"){

        std::cout << "Processing MC" << std::endl;
        histo->SetFillColor(color);
        histo->SetMarkerColor(color);
        histo->SetLineColor(kBlack);
        stack->Add(histo);
        stack->Draw("HIST SAME");
        leg.AddEntry(histo, legendEntry.c_str(), "f");
        h_sum_MC->Add(histo);
        std::cout<< " done Processing MC" << std::endl;
      }else{

        std::cout << "Processing Data" << std::endl;
        std::cout << " +++ IN THE DATA PART " << std::endl;
        //leg.AddEntry(histo, legendEntry.c_str(), "pl");
        histo->Draw("E0 SAME");
        stack->SetMaximum(1.35*histo->GetMaximum());
        hratio->Add(histo);
        std::cout<< " done Processing Data" << std::endl;
      }



    }

  }

  c1->cd();
  leg.Draw();
  std::cout << "x-axis label: " << xaxislabel.c_str() << std::endl;
  //stack->GetXaxis()->SetTitle("Events / GeV"); 
  //stack->GetYaxis()->SetTitle(yaxislabel.c_str());
  stack->GetXaxis()->SetLabelSize(0);

  //stack->SetMaximum(1.35*stack->GetMaximum());

  std::cout << " before TLatex "<<std::endl;
  TLatex l;
  l.SetNDC();
  l.SetTextColor(kBlack);
  l.SetTextFont(42);
  l.SetTextSize(0.04);

  ATLAS_LABEL(0.2,0.88); myText(0.32,0.88,1,"Internal");
  l.SetTextFont(42);
  l.SetTextSize(0.04);
  l.DrawLatex(0.2, 0.83, Form("#scale[0.7]{#int}Ldt = 139.7 fb^{-1}"));



  //c1->cd();

  TPad *padlow = new TPad("padlow","padlow",0.,0.,1.,0.33,0);
  padlow->SetFillStyle(4000);
  padlow->SetGrid(1,1);
  padlow->SetTopMargin(0.05);
  padlow->SetBottomMargin(0.3);
  padlow->Draw();
  padlow->cd();

  std::cout<< "here1"<<std::endl;

  hratio->GetXaxis()->SetLabelFont(43);
  hratio->GetXaxis()->SetLabelSize(24); 
  hratio->GetXaxis()->SetTitleOffset(0.98);
  hratio->GetXaxis()->SetTitleSize(0.12);
  hratio->GetYaxis()->SetLabelFont(43);
  hratio->GetYaxis()->SetLabelSize(17); 
  hratio->GetYaxis()->SetTitleOffset(0.6);
  hratio->GetYaxis()->SetTitleSize(0.13);
  hratio->GetYaxis()->SetTitle("Data/MC");
  hratio->GetXaxis()->SetTitle(yaxislabel.c_str());
  hratio->SetMarkerStyle(20);
  hratio->Sumw2();
  hratio->Divide(h_sum_MC);

  std::cout<< "here2"<<std::endl;
  // hratio->SetMaximum(1.99);
  // hratio->SetMinimum(0.01);

  hratio->Draw("ep");

  TLine *rl = new TLine();
  rl->SetLineColor(2);
  rl->DrawLine(hratio->GetBinLowEdge(1), 1., hratio->GetBinLowEdge(hratio->GetNbinsX()+1), 1.);

  std::cout<< "here3 "<<c1<<std::endl;

  std::string FileNamePNG = histoName + ".png";
  std::string FileNamePDF = histoName + ".pdf";
  std::cout<< "FileNamePNG.c_str()" << FileNamePNG.c_str() << std::endl;

  //c1->Print(FileNamePNG.c_str());
  //c1->SaveAs(FileNamePNG.c_str());
  c1->Print(FileNamePDF.c_str());

  std::cout<< "here4"<<std::endl;
}




/*
   DoPlots("sumHisto_m_yy_Selection","m_{#gamma#gamma} [GeV]", "Events / GeV"); 
   Plotter("sumHisto_m_jj_Selection","m_{bb} [GeV]", "Events / 5 GeV");
   Plotter("sumHisto_m_yyjj_tilde_Selection", "M*_{X} [GeV]", "Events / 25 GeV");
   Plotter("sumHisto_deltaR_yy_Selection", "#DeltaR(#gamma,#gamma)", "Events / 0.2");
   Plotter("sumHisto_deltaR_jj_Selection", "#DeltaR(b,b)", "Events / 0.2");
   Plotter("sumHisto_deltaR_yyjj_Selection", "#DeltaR(#gamma#gamma,bb)", "Events / 0.2");
   Plotter("sumHisto_N_j_Selection", "N_{jets}", "Events");
   Plotter("sumHisto_N_j_central_Selection", "N_{cen jets}", "Events");
   Plotter("sumHisto_btag_score_Selection", "sum of b-tag scores of 2 jets", "Events");
   Plotter("sumHisto_m_yyjj_tilde_HM_Selection", "M*_{x} [GeV]", "Events / 25 GeV");
   Plotter("sumHisto_MET_Selection", "MET [GeV]", "Events / 25 GeV");
   */

/*
   void Plotting::DoPlots(){
   mytest::JSONData& document=Controller::GetDocument();

   const std::vector<std::string> cutFlows={"Selection"};

   for (auto iCut: cutFlows){
   for (auto iVar: document.variables.variables){
   mytest::aVar thisVar=document.variables.variables[iVar.first];
   const std::string varName=iVar.first;



   }
   }

   }

*/
