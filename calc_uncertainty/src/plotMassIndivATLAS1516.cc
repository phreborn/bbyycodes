#include "CommonHead.h"
#include "CommonFunc.h"
#include "LEPEntry.h"

using namespace std;
using namespace CommonFunc;

double luminosity=4.22;
const double epsilon=1e-7;

vector<double> readInputs(TString inputSet, double mass);

const char* GetErrStr(double errLo, double errHi){
  TString error=Form("%4.2f",(errLo+errHi)/2);
  return Form(" #pm %-4s",error.Data());
}

int main(int argc, char **argv){

  //============================ Global booking and setting ==========================
  //   gErrorIgnoreLevel = kError+1;
  map<string,bool> Opt;
  Opt["SUMMARY"]=false;

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
  // *********************************************************************************
  if(Opt["SUMMARY"]){
    if(argc<3){
      cout<<"Usage: "<<argv[0]<<" "<<argv[1]<<" <jobname> <option>"<<endl;
      return 0;
    }
    TString jobname=argv[2];
    TString option=argv[3];
    gStyle->SetEndErrorSize(8);
    // gStyle->SetLineWidth(2);
    // gStyle->SetFrameLineWidth(2);
    
    TString outputDir="fig/"+jobname;
    system("mkdir -vp "+outputDir);
    vector<double> mean;
    vector<double> err_lo,err_lo_the,err_lo_sys,err_lo_stat;
    vector<double> err_hi,err_hi_the,err_hi_sys,err_hi_stat;
    vector<TString> name;
    vector<TString> name2,tag;

    double xmin=123.5,xmax=128;
    vector<TString> inputs;
    vector<bool> cutoff;

    inputs.push_back("ATLAS_combined_obs"); name.push_back("#bf{Combined}");     tag.push_back("mH"); cutoff.push_back(false);
    mean.push_back(124.98); err_hi.push_back(0.28);  err_lo.push_back(0.28); err_hi_stat.push_back(0.19); err_lo_stat.push_back(0.19);  err_hi_sys.push_back(0.21); err_lo_sys.push_back(0.21);

    inputs.push_back("ATLAS_hgg_obs"); name.push_back("#it{H#rightarrow#gamma#gamma}");     tag.push_back("mH"); cutoff.push_back(false);
    mean.push_back(125.11); err_hi.push_back(0.42);  err_lo.push_back(0.42); err_hi_stat.push_back(0.21); err_lo_stat.push_back(0.21);  err_hi_sys.push_back(0.36); err_lo_sys.push_back(0.36);

    inputs.push_back("ATLAS_hzz_obs"); name.push_back("#it{H#rightarrowZZ*#rightarrow}4#font[12]{l}");      tag.push_back("mH"); cutoff.push_back(false);
    mean.push_back(124.875); err_hi.push_back(0.37);  err_lo.push_back(0.37); err_hi_stat.push_back(0.367); err_lo_stat.push_back(0.367);  err_hi_sys.push_back(0.047); err_lo_sys.push_back(0.047);
	
    inputs.push_back("LHC_combined_obs_run1"); name.push_back("LHC Run 1");           tag.push_back("mH"); cutoff.push_back(false);
    mean.push_back(125.09457); err_hi.push_back(0.23746);  err_lo.push_back(0.23395); err_hi_stat.push_back(0.20876); err_lo_stat.push_back(0.20772);  err_hi_sys.push_back(0.11315); err_lo_sys.push_back(0.10763);

    int nslice=name.size();

    double txtsize_(0.05);
    int    align_(12);
    double markerSize_(1.2);
    double lineWidth_(2.5);
    double boxLineWidth_(1.2);
    double statBoxSize_(0.24);
    double systBoxSize_(0.16);

    if(!option.Contains("printnum")){
      if(option.Contains("noexp")){
	statBoxSize_=0.18;
	systBoxSize_=0.13;
      }
      if(option.Contains("nochannel")){
	statBoxSize_=0.13;
	systBoxSize_=0.09;
      }
      if(option.Contains("onlyexp")||option.Contains("onlychannel")){
	statBoxSize_=0.10;
	systBoxSize_=0.08;
      }
    }
    vector<TString> results;

    TCanvas *c=new TCanvas("summary","summary",800,600);
    TPad *pad1 =  new TPad("pad1","pad1name",0.2,0.0,1.00,1.00);
    pad1->SetLeftMargin(0.12);

    if(option.Contains("printnum")){
      c=new TCanvas("summary","summary",1200,600);
      pad1 =  new TPad("pad1","pad1name",0.,0.,1.,1.);
      xmin = 123.801; xmax=126.701;
      pad1->SetLeftMargin(0.05);
    }
//     c->SetLeftMargin(0.05);
    pad1->Draw();

    pad1->cd();

    TH1F* h0 = new TH1F("h0","h0",10000,xmin,xmax);
    // h0->SetMinimum(0.001);
    h0->SetMinimum(0.001);
    h0->SetLineWidth(0);
    h0->SetLineColor(0);
    if(option.Contains("printnum")){
      h0->SetMaximum(nslice+2);
      h0->SetMinimum(-0.5);
    }
    else{
      h0->SetMaximum(nslice);
    }
    h0->GetXaxis()->SetTitle("#it{m_{H}} [GeV]");
    h0->GetXaxis()->SetTitleSize(0.055);
    h0->GetYaxis()->SetLabelOffset(1);
    h0->GetXaxis()->SetLabelSize(0.055);
    h0->GetYaxis()->SetNdivisions(1);
    if(option.Contains("figure5")){
      int N1=(xmax-xmin)/1.+5;
      int N2=10;
      h0->GetXaxis()->SetNdivisions(N1+100*N2);
    }

    if(option.Contains("onlyexp")||option.Contains("onlychannel")){
      int N1=(xmax-xmin)/0.5+3;
      int N2=5;
      h0->GetXaxis()->SetNdivisions(N1+100*N2);
    }
    
    h0->SetLineWidth(0);
    h0->Draw();

    TLine * l1=new TLine(h0->GetXaxis()->GetXmin(), 1,h0->GetXaxis()->GetXmax() , 1); 
    l1 -> SetLineWidth(2);
    l1 -> SetLineColor(kGray+2);
    l1 -> SetLineStyle(kDashed);

    TLine * l2=new TLine(h0->GetXaxis()->GetXmin(), 3,h0->GetXaxis()->GetXmax() , 3); 
    l2 -> SetLineWidth(2);
    l2 -> SetLineColor(kGray+2);
    l2 -> SetLineStyle(kDashed);


    TLine * l3=new TLine(h0->GetXaxis()->GetXmin(), 5,h0->GetXaxis()->GetXmax() , 5); 
    l3 -> SetLineWidth(2);
    l3 -> SetLineColor(kBlue);
    l3 -> SetLineStyle(4);

    double mHhat=mean[0];
    double mHErrLo=err_lo[0];
    double mHErrHi=err_hi[0];
    // TBox *box = new TBox (mean[0]-err_lo[0], 0.0, mean[0]+err_hi[0], mean.size());
    TBox *box = new TBox (mHhat-mHErrLo, 0.0, mHhat+mHErrHi, nslice);
    
    box->SetFillStyle(1001);
    box->SetFillColor(kGray);
    box->SetLineColor(kGray);
    box->SetLineWidth(0);
    box->Draw("l");

    TLine *lband_=new TLine(mHhat, 0., mHhat, nslice);
    lband_->SetLineWidth(2);
    lband_->SetLineColor(2);
    lband_->Draw("same");
    
    // l1->Draw("same");
    if(!option.Contains("nochannel")&&!option.Contains("onlyexp")&&!option.Contains("onlychannel")) l2->Draw("same");
    if(!option.Contains("noexp")&&!option.Contains("onlyexp")&&!option.Contains("onlychannel")) l3->Draw("same");

    for(int islice=0;islice<nslice;islice++){
      TString printStr=Form("%30s", name[islice].Data());

      printStr+=Form("\t %.3f \t +%.3f \t -%.3f \t +%.3f \t -%.3f \t +%.3f \t -%.3f", mean[islice],err_hi[islice],err_lo[islice],err_hi_stat[islice],err_lo_stat[islice],err_hi_sys[islice],err_lo_sys[islice]);

      if(option.Contains("printnum")){
	TString central=Form("%6.2f", mean[islice]);
	printStr=Form("%-6s%s (%s%s) GeV", central.Data(), GetErrStr(err_lo[islice], err_hi[islice]), GetErrStr(err_lo_stat[islice], err_hi_stat[islice]), GetErrStr(err_lo_sys[islice], err_hi_sys[islice]));
	results.push_back(printStr);
      }

      cout<<printStr<<endl;

      LEPEntry entry( "", "GeV", "" );
      entry.setStatName("");
      entry.setVal(  mean[islice] );
      entry.setAsymmTot( err_lo[islice], err_hi[islice] );
      entry.setAsymmSyst( err_lo_sys[islice], err_hi_sys[islice] );
      entry.setAsymmStat( err_lo_stat[islice], err_hi_stat[islice] );
      entry.setNdigit( 2 );      
      entry.setStyle( kFullCircle, markerSize_, kBlack, 42, txtsize_, align_, lineWidth_ );
      entry.setX( xmin, xmax );      
      entry.setY( islice+0.5, islice+0.5 ); 
      entry.setScale(0 );
      entry.writeResult(1);

      entry.setBoxLineWidth(boxLineWidth_);
      entry.setStatBoxSize(statBoxSize_);
      entry.setSystBoxSize(systBoxSize_);
      
      entry.draw();
    }

    
    TLatex la; //l.SetTextAlign(12); l.SetTextSize(tsize);
    la.SetNDC();
    la.SetTextFont(72);
    la.SetTextColor(1);
    la.SetTextSize(0.04);

    TLatex lp;
    lp.SetNDC();
    lp.SetTextFont(42);
    lp.SetTextColor(1);
    lp.SetTextSize(0.04);

    TLatex l; //l.SetTextAlign(12); l.SetTextSize(tsize);
    l.SetNDC();
    l.SetTextColor(1);
    l.SetTextSize(0.04);

    

    TLine* linex[100];
    for(int i=0; i<int(mean.size()); i++){
      if( cutoff.at(i)==1 ){
	linex[i] = new TLine( mean.at(i)-err_lo.at(i), i,  mean.at(i)-err_lo.at(i), i+1 );
	linex[i] -> SetLineWidth(2);
	linex[i] -> SetLineColor(kBlack);
	linex[i] -> SetLineStyle(kDashed);
	linex[i] -> Draw("same");
      }
    }

    double x1,y1,x2,y2;
    GetX1Y1X2Y2(pad1,x1,y1,x2,y2);

    vector<TString> pavetext1,pavetext2;

    if(option.Contains("note")){
      if(option.Contains("printnum")){
	pavetext2.push_back("#bf{#it{ATLAS}} preliminary");
      }
      else{
	pavetext2.push_back("#bf{#it{ATLAS}}");
	pavetext2.push_back("preliminary");
      }
    }
    else if(option.Contains("paper")) pavetext2.push_back("#bf{#it{ATLAS}}");
    else{
      if(option.Contains("printnum")){
	pavetext2.push_back("#bf{#it{ATLAS}} internal");
      }
      else{
	pavetext2.push_back("#bf{#it{ATLAS}}");
	pavetext2.push_back("internal");
      }
    }

    pavetext2.push_back("#sqrt{#it{s}} = 13 TeV, 36.1 fb^{-1}");

    TPaveText* text1=CreatePaveText(x2-0.5,y1+0.01,x2-0.01,y1+0.18,pavetext1,0.05);
    TPaveText* text2=CreatePaveText(x2-0.4,y1+0.05,x2-0.01,y1+0.15,pavetext2,0.05);
    if(option.Contains("noexp")){
      if(option.Contains("note") || !option.Contains("paper")) text2=CreatePaveText(x2-0.4,y1+0.03,x2-0.01,y1+0.23,pavetext2,0.05);
      else text2=CreatePaveText(x2-0.4,y1+0.03,x2-0.01,y1+0.20,pavetext2,0.05);
    }
    if(option.Contains("nochannel")||option.Contains("onlychannel")||option.Contains("onlyexp")){
      if(option.Contains("note") || !option.Contains("paper"))
	text2=CreatePaveText(x2-0.4,y1+0.02,x2-0.01,y1+0.2,pavetext2,0.05);
      else text2=CreatePaveText(x2-0.4,y1+0.05,x2-0.01,y1+0.21,pavetext2,0.05);
    }
    if(option.Contains("printnum")){
      text2=CreatePaveText(x1+0.03,y2-0.18,x1+0.4,y2-0.05,pavetext2,0.05);
    }

    LEPEntry totleg("Total");
    totleg.setStyle( kFullCircle, markerSize_, kBlack, 42, txtsize_, align_, lineWidth_ );
    LEPEntry systleg("Syst.");
    systleg.setStyle( kFullCircle, 0, kBlack, 42, txtsize_, align_, lineWidth_ );
    systleg.setSystBoxSize(systBoxSize_);
    systleg.setBoxLineWidth(boxLineWidth_);

    LEPEntry statleg("Stat.");
    statleg.setStyle( kFullCircle, 0, kBlack, 42, txtsize_, align_, lineWidth_ );
    statleg.setStatBoxSize(statBoxSize_);
    statleg.setBoxLineWidth(boxLineWidth_);

    if(option.Contains("printnum")){
      float xleg_, yleg_, eleg_, tleg_;
      yleg_ = nslice+1.2;
      xleg_ = xmax-1.4;   
      eleg_ = 0.10;  
      tleg_ = xleg_+0.15;

      totleg.setVal( xleg_ );
      totleg.setTot( eleg_ );

      totleg.setX( tleg_ );
      totleg.setY( yleg_ ); 
      totleg.draw();

      xleg_ += 0.5;

      tleg_ = xleg_+0.15;

      statleg.setVal( xleg_ );
      statleg.setStat( 1.0*eleg_ );

      statleg.setX( tleg_ );
      statleg.setY( yleg_ );
      statleg.draw();
    
      xleg_ += 0.5;

      tleg_ = xleg_+0.15;

      systleg.setVal( xleg_ );
      systleg.setSyst( 0.75*eleg_ );

      systleg.setX( tleg_ );
      systleg.setY( yleg_ );
      systleg.draw();
    }
    else{
      float xleg_, yleg_, eleg_, tleg_;
      yleg_ = nslice-0.5;
      xleg_ = xmax-1;

      double increment=0.8*nslice/7.;
      // if(nslice==7) increment=0.8;
      // else if(nslice==5) increment=0.5;
      // else increment=0.4;

      eleg_ = 0.15;

      if(nslice==3){
	yleg_=nslice-1;
	xleg_=xmax-0.5;
	eleg_=0.08;
      }
      tleg_ = xleg_+0.25;

      totleg.setVal( xleg_ );
      totleg.setTot( eleg_ );
      totleg.setX( tleg_ );

      totleg.setY( yleg_ ); 

      totleg.draw();

      yleg_ -= increment;

      //    tleg_ = xleg_+0.25;
      statleg.setVal( xleg_ );
      statleg.setStat( 1.0*eleg_ );
      statleg.setX( tleg_ );
      statleg.setY( yleg_ ); 
      statleg.draw();
    
      yleg_ -= increment;

      //    tleg_ = xleg_+0.25;
      systleg.setVal( xleg_ );
      systleg.setSyst( 0.75*eleg_ );
      systleg.setX( tleg_ );
      systleg.setY( yleg_ ); 
      systleg.draw();
    }
    
    text1->Draw("same");
    text2->Draw("same");

    pad1->RedrawAxis();
    pad1->Update();

    c->cd();
    TLatex lx; 
    lx.SetNDC();
    lx.SetTextColor(1);

    if(option.Contains("printnum")){
      lx.SetTextSize(0.048);
      lx.DrawLatex(0.67,0.12+(nslice+0.6)*0.79/(double)(nslice+2), Form("\t\tTotal      Stat.   Syst."));
    }
    lx.SetTextSize(0.05);
    for(int i=0; i<nslice; i++){
      if(option.Contains("printnum")){
	lx.SetTextSize(0.05);
	lx.DrawLatex(0.09,0.185+(i+0.6)*0.76/(double)(nslice+2), Form("%s",name.at(i).Data()));

	cout<<name.at(i)<<endl;
	if(i==0){
	  lx.SetTextSize(0.048);
	  lx.DrawLatex(0.595,0.185+(i+0.6)*0.76/(double)(nslice+2), Form("#bf{#color[2]{%s}}",results.at(i).Data()));
	}
	else if (i==1 || i==2){
	  lx.SetTextSize(0.048);
	  lx.DrawLatex(0.595,0.185+(i+0.6)*0.76/(double)(nslice+2), Form("#color[4]{%s}",results.at(i).Data()));
	}
	else{
	  lx.SetTextSize(0.048);
	  lx.DrawLatex(0.595,0.185+(i+0.6)*0.76/(double)(nslice+2), Form("%s",results.at(i).Data()));
	}
      }
      else{
	lx.DrawLatex(0.03,0.14+(i+0.6)*0.79/(double)(nslice), Form("%s",name.at(i).Data()));
      }
    }

    TLatex lexplain; 
    lexplain.SetNDC();
    lexplain.SetTextColor(1);
    lexplain.SetTextSize(0.028);
    if(!option.Contains("printnum")){
      if(!option.Contains("noexp")&&!option.Contains("nochannel")){
	lexplain.DrawLatex(0.68,0.065+(3+0.6)*0.79/(double)(nslice), "#bf{Per-channel combination}");
	lexplain.DrawLatex(0.68,0.065+(5+0.6)*0.79/(double)(nslice), "#bf{Per-experiment combination}");
      }
    }
    c->RedrawAxis();
    TString outputCanvas=c->GetName();
    
    if(option.Contains("printnum")) outputCanvas+="_printnum";
    if(option.Contains("noexp")) outputCanvas+="_noexp";
    if(option.Contains("nochannel")) outputCanvas+="_nochannel";

    if(option.Contains("onlyexp")) outputCanvas+="_onlyexp";
    if(option.Contains("onlychannel")) outputCanvas+="_onlychannel";
    
    if(option.Contains("note")) outputCanvas+="_prelim";
    if(option.Contains("paper")) outputCanvas+="_final";

    PrintCanvas(c,outputDir+"/"+outputCanvas);
  }
}
