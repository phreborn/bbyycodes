#include "CommonHead.h"
#include "CommonFunc.h"
#include "LEPEntry.h"

using namespace std;
using namespace CommonFunc;

double luminosity=4.22;
const double epsilon=1e-7;

vector<double> readInputs(TString inputSet, double mass);

const char* GetErrStr(double errLo, double errHi, bool isAsym=false){
  if(!isfinite(errLo)) errLo=0;
  
  if(isAsym){
    if(fabs(errLo-errHi)<0.01){
      TString error=Form("%4.2f",(errLo+errHi)/2);
      return Form(" #pm %-4s",error.Data());
    }
    else return Form(" #splitline{+ %4.2f}{#minus %4.2f}",errHi, errLo);
  }
  else{
    TString error=Form("%4.2f",(errLo+errHi)/2);
    return Form(" #pm %-4s",error.Data());
  }
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
    vector<TString> name2,tag, poi;

    double xmin=-1.2,xmax=6;
    if(option.Contains("hu")) xmin=-0.6;
    vector<TString> inputs;
    vector<bool> cutoff;

    name.push_back("#mu");       tag.push_back("mu");    poi.push_back("mu");     cutoff.push_back(false);
    name.push_back("#mu_{ggH}"); tag.push_back("muggh"); poi.push_back("mu_ggH"); cutoff.push_back(false);
    name.push_back("#mu_{VBF}"); tag.push_back("muvbf"); poi.push_back("mu_VBF"); cutoff.push_back(false);
    name.push_back("#mu_{WH}");  tag.push_back("muwh");  poi.push_back("mu_WH");  cutoff.push_back(false);
    name.push_back("#mu_{ZH}");  tag.push_back("muzh");  poi.push_back("mu_ZH");  cutoff.push_back(true);
    name.push_back("#mu_{ttH}"); tag.push_back("mutth"); poi.push_back("mu_ttH"); cutoff.push_back(false);

    for(auto tagName : tag){
      inputs.push_back(jobname+"_"+tagName);
    }

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

    h0->GetXaxis()->SetTitle("Signal strength");
    
    h0->GetYaxis()->SetLabelOffset(1);
    h0->GetXaxis()->SetLabelSize(0.045);
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

    l1->Draw("same");

    DrawVerticalLine(pad1,1,0,nslice,4,2,2);

    for(int islice=0;islice<nslice;islice++){
      double muhat,errlo,errhi,dummy;
      double errlo_nothe,errhi_nothe,errlo_nosys,errhi_nosys;
      double errlo_the,errhi_the,errlo_sys,errhi_sys;
      TString input="fig/nllscan/"+inputs[islice]+"/nllscan_"+poi[islice]+".txt";
      ifstream finall(input,ios::in);
      cout<<input<<endl;
      assert(finall);
      finall>>muhat>>errlo>>errhi;

      mean.push_back(muhat);
      err_lo.push_back(errlo);
      err_hi.push_back(errhi);
      cout<<setprecision(3);
      // cout<<errlo<<" "<<errhi<<endl;

      ifstream finnosys("fig/nllscan/"+inputs[islice]+"_nosys/nllscan_"+poi[islice]+".txt",ios::in);
      assert(finnosys);
      finnosys>>muhat>>errlo_nosys>>errhi_nosys;
      
      errlo_sys=sqrt(errlo*errlo-errlo_nosys*errlo_nosys);
      errhi_sys=sqrt(errhi*errhi-errhi_nosys*errhi_nosys);      

      err_lo_stat.push_back(errlo_nosys);
      err_hi_stat.push_back(errhi_nosys);

      err_lo_sys.push_back(errlo_sys);
      err_hi_sys.push_back(errhi_sys);

      // CMS H->gamgam total uncertainty be 0.34 instead of 0.35
      
      if(inputs[islice]=="CMS_hgg_obs_unblind_check"){
	err_hi[islice]=0.34;
	err_lo[islice]=0.34;
      }
      TString printStr=Form("%30s", name[islice].Data());

      printStr+=Form("\t %.3f \t +%.3f \t -%.3f \t +%.3f \t -%.3f \t +%.3f \t -%.3f", mean[islice],err_hi[islice],err_lo[islice],err_hi_stat[islice],err_lo_stat[islice],err_hi_sys[islice],err_lo_sys[islice]);

      if(option.Contains("printnum")){
	TString central=Form("%6.2f", mean[islice]);
	printStr=Form("%-6s%s (%s%s)", central.Data(), GetErrStr(err_lo[islice], err_hi[islice], option.Contains("asym")), GetErrStr(err_lo_stat[islice], err_hi_stat[islice], option.Contains("asym")), GetErrStr(err_lo_sys[islice], err_hi_sys[islice], option.Contains("asym")));
	results.push_back(printStr);
      }

      cout<<printStr<<endl;
      finall.close();
      finnosys.close();

      LEPEntry entry( "", "%", "" );
      entry.setStatName("");
      entry.setVal(  mean[islice] );
      entry.setAsymmTot( err_lo[islice], err_hi[islice] );
      // entry.setAsymmSyst( err_lo_sys[islice], err_hi_sys[islice] );
      entry.setAsymmSyst( 0, 0 );
      entry.setAsymmStat( err_lo_stat[islice], err_hi_stat[islice] );
      entry.setNdigit( 2 );      
      entry.setStyle( kFullCircle, markerSize_, kBlack, 42, txtsize_, align_, lineWidth_ );
      entry.setX( xmin, xmax );      
      entry.setY( islice+0.5, islice+0.5 ); 
      entry.setScale(0 );
      entry.writeResult(1);

      entry.setBoxLineWidth(boxLineWidth_);
      entry.setStatBoxSize(statBoxSize_);
      // entry.setSystBoxSize(systBoxSize_);
      entry.setSystBoxSize(0);
      
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
    // pavetext1.push_back("#scale[0.6]{#int}Ldt = 4.5 fb^{-1}, #sqrt{#it{s}} = 7 TeV");
    // pavetext1.push_back("#scale[0.6]{#int}Ldt = 20.3 fb^{-1}, #sqrt{#it{s}} = 8 TeV");


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
	pavetext2.push_back("#bf{#it{ATLAS}} simulation internal");
      }
      else{
	pavetext2.push_back("#bf{#it{ATLAS}}");
	pavetext2.push_back("internal");
      }
    }
    // pavetext2.push_back("2011-2012");

    pavetext1.push_back("#sqrt{#it{s}} = 7 TeV, 4.5 fb^{-1}");
    pavetext1.push_back("#sqrt{#it{s}} = 8 TeV, 20.3 fb^{-1}");

    TPaveText* text1=CreatePaveText(x1+0.3,y2-0.18,x2-0.01,y2-0.08,pavetext1,0.045);
    TPaveText* text2=CreatePaveText(x1+0.03,y2-0.15,x1+0.35,y2-0.05,pavetext2,0.05);

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

    float xleg_, yleg_, eleg_, tleg_;
    yleg_ = nslice+1.;
    xleg_ = xmax-2;   
    eleg_ = 0.04;  
    tleg_ = xleg_+0.05;

    totleg.setVal( xleg_ +0.3);
    totleg.setTot( 0.12);
    totleg.setX( tleg_ -0.3);
    totleg.setY( yleg_ ); 
    totleg.draw();

    xleg_ += 1;

    tleg_ = xleg_+0.05;

    statleg.setVal( xleg_ +0.3);
    statleg.setStat( 0.12);
    statleg.setX( tleg_ -0.3);
    statleg.setY( yleg_ );
    statleg.draw();
    
    xleg_ += 0.2;

    tleg_ = xleg_+0.05;

    systleg.setVal( xleg_ );
    systleg.setSyst( 0.75*eleg_ );

    systleg.setX( tleg_ );
    systleg.setY( yleg_ );
    systleg.setX( tleg_ -0.3);
    systleg.setY( yleg_ );
    // systleg.draw();
    
    text1->Draw("same");
    text2->Draw("same");

    pad1->RedrawAxis();
    pad1->Update();

    c->cd();
    TLatex lx; 
    lx.SetNDC();
    lx.SetTextColor(1);

    if(option.Contains("printnum")){
      lx.SetTextSize(0.04);
      lx.DrawLatex(0.74,0.12+(nslice+0.6)*0.79/(double)(nslice+2), Form("\t\t\t\t\tTotal     Stat.    Syst."));
      // lx.DrawLatex(0.67,0.12+(nslice+0.6)*0.79/(double)(nslice+2), Form("\t\t\tTotal     Stat.    Syst."));
    }
    lx.SetTextSize(0.04);
    // if(option.Contains("asym")) lx.SetTextSize(0.05);

    for(int i=0; i<nslice; i++){
      if(option.Contains("printnum")){
	// lx.DrawLatex(0.075,0.175+(i+0.75)*0.73/(double)(nslice+2), Form("%s",name.at(i).Data()));
	lx.DrawLatexNDC(0.075,0.175+(i*0.98+0.75)*0.75/(double)(nslice+2), Form("%s",name.at(i).Data()));

	cout<<name.at(i)<<endl;
	if(i==0){
	  lx.DrawLatexNDC(0.7,0.175+(i*0.98+0.75)*0.75/(double)(nslice+2), Form("#bf{#color[2]{%s}}",results.at(i).Data()));
	  //lx.DrawLatex(0.63,0.175+(i+0.75)*0.73/(double)(nslice+2), Form("#color[2]{%s}",results.at(i).Data()));
	}
	else{
	  lx.DrawLatexNDC(0.7,0.175+(i*0.98+0.75)*0.75/(double)(nslice+2), Form("%s",results.at(i).Data()));
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
