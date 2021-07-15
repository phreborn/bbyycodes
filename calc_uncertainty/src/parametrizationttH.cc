#include "parametrizationttH.hh"
#include "MxAODNtup.h"
#include "test.h"
#include "RooTwoSidedCBShape.h"

RooFitResult* fit(RooAbsPdf *pdf, RooAbsData *data){
  RooAbsReal *nll = pdf->createNLL(*data);
  nll->enableOffsetting(1);
  RooMinimizer minim(*nll);
  minim.setStrategy(1);
  minim.setPrintLevel(0);
  minim.setProfile(); /* print out time */
  minim.setEps(0.001);
  minim.optimizeConst(2);
  int status=minim.minimize("Minuit2");
  return minim.save();
}

void constSet(RooArgSet set, bool flag){
  TIterator *iter = set.createIterator();
  RooRealVar* parg = NULL;
  while((parg=(RooRealVar*)iter->Next()) ){
    parg->setConstant(flag); 
  }
  SafeDelete(iter);
}

int getttHHadBDTCat(test *p){
  const int stopper = 300;
  const int n_scans = 1000;
  const int boundary_0 = 0, boundary_1 = 3, boundary_2 = 7, boundary_3 = 15, boundary_4 = 59;

  if ((1-p->bdtweight_ttH)<=(boundary_1/float(n_scans))) return 1;
  else if ((1-p->bdtweight_ttH)<=(boundary_2/float(n_scans))) return 2;
  else if ((1-p->bdtweight_ttH)<=(boundary_3/float(n_scans))) return 3;
  else if ((1-p->bdtweight_ttH)<=(boundary_4/float(n_scans))) return 4;
  return -1;
}

int getttHLepBDTCat(test *p){
  const int stopper = 300;
  const int n_scans = 1000;
  const int boundary_0 = 13, boundary_1 = 58, boundary_2 = 295;
  
  if ((1-p->bdtweight_ttH)<=(boundary_0/float(n_scans))) return 3;
  else if ((1-p->bdtweight_ttH)<=(boundary_1/float(n_scans))) return 2;
  else if ((1-p->bdtweight_ttH)<=(boundary_2/float(n_scans))) return 1;
  return -1;
}

void translateMCTypeAndMass(int mcChannelNumber, int &MCtype, int &Higgs_truth_mass){
  if(mcChannelNumber==343981) MCtype = 0; // ggF
  else if(mcChannelNumber==345041) MCtype = 1; // VBF
  else if(mcChannelNumber==345317||mcChannelNumber==345318) MCtype = 2; // WH
  else if(mcChannelNumber==345319||mcChannelNumber==345061) MCtype = 3; // ZH
  else if(mcChannelNumber==343436) MCtype = 4; // ttH
  else if(mcChannelNumber==342097||mcChannelNumber==342098) MCtype = 5; // bbH
  else if(mcChannelNumber==343267) MCtype = 6;				 // tHjb
  else if(mcChannelNumber==341998) MCtype = 7;				 // WtH
  else MCtype = -1;							 // Not a known signal process
  Higgs_truth_mass = 125;	// Not considering interpolations/extrapolations yet
}

void translateMCTypeAndMass(TString fileName, int &MCtype, int &Higgs_truth_mass){
  fileName=(CommonFunc::SplitString(fileName,'/')).back();
  if(fileName.BeginsWith("ggH")) MCtype = 0; // ggF
  else if(fileName.BeginsWith("VBF"))  MCtype = 1; // VBF
  else if(fileName.BeginsWith("WH"))   MCtype = 2; // WH
  else if(fileName.BeginsWith("ZH"))   MCtype = 3; // ZH
  else if(fileName.BeginsWith("ttH"))  MCtype = 4; // ttH
  else if(fileName.BeginsWith("bbH"))  MCtype = 5; // bbH
  else if(fileName.BeginsWith("tHjb")) MCtype = 6; // tHjb
  else if(fileName.BeginsWith("tWH"))  MCtype = 7; // WtH
  else MCtype = -1;				   // Not a known signal process
  Higgs_truth_mass = 125;	// Not considering interpolations/extrapolations yet
}

int main (int argc, char **argv)
{
  //--------------------------------------//
  // Define cut values for jets:
  
  double lumi = 1;

  const int nprocess=8;

  vector<int> signalmass = {125};
  const int nmasspoint=signalmass.size();  

  //--------------------------------------//
  // Root macros:
  // SetGangnamStyle();
  SetAtlasStyle();
  
  //--------------------------------------//
  // Check arguments:
  if( argc < 3 )
  {
    printf("\nUsage: %s <jobname> <input list> <options>\n\n",argv[0]);
    exit(0);
  }
  
  TString cate_name = argv[1];
  TString list = argv[2];

  TString option=argv[3];
  int ncat=-1;
  
  vector<double> bound;

  cout<<option<<endl;

  bool m_debug=option.Contains("debug");
  bool m_inclusive=option.Contains("inclusive");
  bool m_cutbase=option.Contains("cutbase");
  bool m_tthhadbdt=option.Contains("tthhadbdt");
  bool m_tthlepbdt=option.Contains("tthlepbdt");
  
  if(m_inclusive) ncat=0;
  else if(m_tthhadbdt) ncat=4;
  else if(m_tthlepbdt) ncat=3;
  else{				// Machine learning
    cerr<<"Please specify one option."<<endl;
    return 0;
  }

  int cat_start=1;
  if(m_inclusive) cat_start=0;
  int mode=0;
  cout<<"Number of categories: "<<ncat<<endl;
  // TChain* chain=MakeChain("CollectionTree", list, "badfile",list.Contains(".root"));
  TChain* chain=MakeChain("test", list, "badfile",list.Contains(".root"));
  
  // MxAODNtup *p = new MxAODNtup(chain);
  test *p = new test(chain);
  int numev = p->fChain->GetEntries();
  
  if(m_debug) numev=1e4;
  
  //--------------------------------------//
  // Create TTrees for each mass point:
  TTree* tree[50][nmasspoint];
  double mass[50], weight[50];
  
  for(int icat=0; icat<=ncat;icat++){
    for( int t = 0; t < nmasspoint; t++ ){
      TString tname=Form("t_%d_%d",icat,signalmass[t]);
      tree[icat][t] = new TTree(tname,tname);
      tree[icat][t]->SetDirectory(0);
      tree[icat][t]->Branch("mass", &mass[icat], "mass/D");
      tree[icat][t]->Branch("weight", &weight[icat], "weight/D");
    }
  }
  
  double all_w[50][nmasspoint];
  double mode_w[50][nprocess][nmasspoint];
  
  //--------------------------------------//
  // Counting for mH=125:
  double counter[50][nprocess];
  
  // Initialize all the arrays

  for(int i=0; i<50; i++){
    for(int j=0; j<nmasspoint; j++){
      for(int k=0;k<nprocess; k++){
	mode_w[i][k][j]=0;
	counter[i][k]=0;
	all_w[i][j]=0;
      }
    }
  }

  //--------------------------------------//
  // Loop over events:
  cout << "We have "<< numev << " evnets to be processed." << endl;

  for( int index = 0; index < numev; index++ )
  {
    p->fChain->GetEntry(index);
    if( index%10000 == 0 )std::cout << "Processed " << 100.*(double(index)/double(numev)) << "% of the events...\r" << std::flush;
    int MCtype, Higgs_truth_mass;
    // translateMCTypeAndMass(p->mcChannelNumber, MCtype, Higgs_truth_mass);
    TString fileName=p->fChain->GetCurrentFile()->GetName();
    translateMCTypeAndMass(fileName, MCtype, Higgs_truth_mass);
    if(MCtype<0) abort();

    if(!p->flag_passedIso) continue;
    if(!p->flag_passedPID) continue;
    if(!p->relpt_cut) continue;
    if(p->mass_yy<105000. || p->mass_yy>160000.) continue;
 
    int icat=-1;
    if(m_inclusive) icat=0;
    else if(m_tthhadbdt) icat=getttHHadBDTCat(p);
    else if(m_tthlepbdt) icat=getttHLepBDTCat(p);
    if(icat<0) continue;
    // mass[icat] = p->m_yy/GeV;
    mass[icat] = p->mass_yy/GeV;

    double addwt=1;
    // if(m_reweight) addwt*=p->weight_Powheg2HRes;
    if(MCtype==4 && p->event_number%100 < 80) continue;
    if(MCtype==4 && p->event_number%100 >= 100) continue;

    if(MCtype==4)
      weight[icat] = p->weight*(10./2.);
    else
      weight[icat] = p->weight;

    mass[0] = mass[icat];
    weight[0] = weight[icat];

    for( int m = 0; m < nmasspoint; m++ )
    {
      int mass_used = signalmass[m];

      if( Higgs_truth_mass == mass_used )
      {
	tree[icat][m]->Fill();

	if(PassMassWin(mass[icat])){
	  all_w[icat][m] += weight[icat];
	  mode_w[icat][MCtype][m] += weight[icat];
	}
	if(!m_inclusive){
	  tree[0][m]->Fill();
	  if(PassMassWin(mass[icat])){
	    all_w[0][m] += weight[0];
	    mode_w[0][MCtype][m] += weight[0];
	  }
	}
      }
    }
  }

  system(Form("mkdir -vp Input/param/%s/",cate_name.Data()));
  system(Form("mkdir -vp Input/param/%s/Plots",cate_name.Data())); 
  system(Form("cp -v src/parametrizationttH.cc inc/parametrizationttH.hh Input/param/%s/",cate_name.Data()));

  for(int icat=cat_start;icat<=ncat;icat++){
    // Observables:
    RooRealVar v_mass("mass","mass",80,180);
    RooRealVar v_weight("weight","weight",-1e20,1e20);
  
    // RooDataSets
    RooDataSet *data[nmasspoint];
    for( int n = 0; n < nmasspoint; n++ ){
      int mass_used2 = signalmass[n];
      char nameRD[20];
      sprintf(nameRD,"data%i",mass_used2);
      data[n] = new RooDataSet(nameRD, "", RooArgSet( v_mass, v_weight ), WeightVar( v_weight ), Import(*tree[icat][n]) ) ;
    }
  
    //--------------------------------------//
    // Roo variables:
    RooRealVar a_alphaLo("a_alphaLo","a_alphaLo", 2., 0.5, 5.);
    RooRealVar b_alphaLo("b_alphaLo","b_alphaLo", 0);
    RooRealVar c_alphaLo("c_alphaLo","c_alphaLo", 0);
    RooRealVar a_alphaHi("a_alphaHi","a_alphaHi", 2., 0.5, 5.);
    RooRealVar b_alphaHi("b_alphaHi","b_alphaHi", 0);
    RooRealVar c_alphaHi("c_alphaHi","c_alphaHi", 0);
    RooRealVar nLo("nLo", "nLo", 10.,0,20);
    RooRealVar nHi("nHi", "nHi", 10.,0,20);
    RooRealVar a_mu("a_mu", "a_mu", 0., -1, 1.);
    RooRealVar b_mu("b_mu", "b_mu", 0);
    RooRealVar c_mu("c_mu", "b_mu", 0);
    RooRealVar a_sigma("a_sigma","a_sigma",1.5, 0.5, 5);
    RooRealVar b_sigma("b_sigma","b_sigma",0);
    // RooRealVar c_sigma("c_sigma","c_sigma",1.5, 0.5, 5);

    //--------------------------------------//
    // For each mass point:
    RooFormulaVar *mu[nmasspoint], *sigma[nmasspoint], *alphaLo[nmasspoint], *alphaHi[nmasspoint], *camila[nmasspoint];
    RooRealVar *mH[nmasspoint];
    RooTwoSidedCBShape *Signal[nmasspoint];
    double x_points[nmasspoint];

    for(int i=0;i<nmasspoint;i++){
      x_points[i]=signalmass[i];
      mH[i]=new RooRealVar(Form("mH_%d",signalmass[i]), Form("mH_%d",signalmass[i]), signalmass[i]);
      camila[i]=new RooFormulaVar(Form("camila_%d",signalmass[i]), "@0-125", RooArgList(*mH[i]));
      mu[i]=new RooFormulaVar(Form("mu_%d",signalmass[i]), "@0+@2+@3*@1", RooArgList(*mH[i], *camila[i], a_mu, b_mu));
      sigma[i]=new RooFormulaVar(Form("sigma_%d",signalmass[i]), "@1+@2*@0", RooArgList(*camila[i], a_sigma, b_sigma));
      alphaLo[i]=new RooFormulaVar(Form("alphaLo_%d",signalmass[i]), "@1+@2*@0",RooArgList(*camila[i], a_alphaLo, b_alphaLo));
      alphaHi[i]=new RooFormulaVar(Form("alphaHi_%d",signalmass[i]), "@1+@2*@0",RooArgList(*camila[i], a_alphaHi, b_alphaHi));
      Signal[i]=new RooTwoSidedCBShape(Form("Signal_%d",signalmass[i]), Form("Signal_%d",signalmass[i]), v_mass, *mu[i], *sigma[i], *alphaLo[i], nLo, *alphaHi[i], nHi);
    }
  
    RooCategory sample("sample", "sample");
    map<string,RooDataSet*> dataMap;
  
    for( int s = 0; s < nmasspoint; s++ ){
      int massval = signalmass[s];
      string massname=Form("m_%i",massval);
      sample.defineType(Form("m_%i",massval));
      dataMap[massname] = data[s];
    }
  
    RooDataSet combData("combData", "combData", RooArgSet(v_mass, v_weight), WeightVar(v_weight), Index(sample), Import(dataMap));
  
    RooSimultaneous simPdf("simPdf","simultaneous pdf",sample);

    for(int s=0;s<nmasspoint;s++)
      simPdf.addPdf( *Signal[s], Form("m_%d",signalmass[s]) );
  
    combData.Print();
    simPdf.Print();
  
    statistics::setDefaultPrintLevel(0);
    RooFitResult *res=fit(&simPdf, &combData);

    // Plot interpolation of yields
    // TF1* f_tot = new TF1("f_tot","pol3",100,150);
    // TGraph* tot_graph = new TGraph(nmasspoint, x_points, all_w[icat]);
    // tot_graph->Fit(f_tot);
    // TCanvas *c_tot=new TCanvas("c_tot","c_tot",800,600);
    // tot_graph->Draw("APL");
    // f_tot->Draw("same");
    // TString outputCanvas_tot=Form("Input/param/%s/Plots/yield_tot_%d",cate_name.Data(),icat);
    // PrintCanvas(c_tot,outputCanvas_tot);

    // TF1* f_ggf = new TF1("f_ggf","pol3",100,150);
    // TGraph* ggf_graph = new TGraph(nmasspoint, x_points, mode_w[icat][0]);
    // ggf_graph->Fit(f_ggf);
    // TCanvas *c_ggf=new TCanvas("c_ggf","c_ggf",800,600);
    // ggf_graph->Draw("APL");
    // f_ggf->Draw("same");
    // TString outputCanvas_ggf=Form("Input/param/%s/Plots/yield_ggf_%d",cate_name.Data(),icat);
    // PrintCanvas(c_ggf,outputCanvas_ggf);

    // TF1* f_vbf = new TF1("f_vbf","pol3",100,150);
    // TGraph* vbf_graph = new TGraph(nmasspoint, x_points, mode_w[icat][1]);
    // vbf_graph->Fit(f_vbf);
    // TCanvas *c_vbf=new TCanvas("c_vbf","c_vbf",800,600);
    // vbf_graph->Draw("APL");
    // f_vbf->Draw("same");
    // TString outputCanvas_vbf=Form("Input/param/%s/Plots/yield_vbf_%d",cate_name.Data(),icat);  
    // PrintCanvas(c_vbf,outputCanvas_vbf);

    // TF1* f_wh = new TF1("f_wh","pol3",100,150);
    // TGraph* wh_graph = new TGraph(nmasspoint, x_points, mode_w[icat][2]);
    // wh_graph->Fit(f_wh);
    // TCanvas *c_wh=new TCanvas("c_wh","c_wh",800,600);
    // wh_graph->Draw("APL");
    // f_wh->Draw("same");
    // TString outputCanvas_wh=Form("Input/param/%s/Plots/yield_wh_%d",cate_name.Data(),icat);  
    // PrintCanvas(c_wh,outputCanvas_wh);
  
    // TF1* f_zh = new TF1("f_zh","pol3",100,150);
    // TGraph* zh_graph = new TGraph(nmasspoint, x_points, mode_w[icat][3]);
    // zh_graph->Fit(f_zh);
    // TCanvas *c_zh=new TCanvas("c_zh","c_zh",800,600);
    // zh_graph->Draw("APL");
    // f_zh->Draw("same");
    // TString outputCanvas_zh=Form("Input/param/%s/Plots/yield_zh_%d",cate_name.Data(),icat);  
    // PrintCanvas(c_zh,outputCanvas_zh);

    // TF1* f_tth = new TF1("f_tth","pol3",100,150);
    // TGraph* tth_graph = new TGraph(nmasspoint, x_points, mode_w[icat][4]);
    // tth_graph->Fit(f_tth);
    // TCanvas *c_tth=new TCanvas("c_tth","c_tth",800,600);
    // tth_graph->Draw("APL");
    // f_tth->Draw("same");
    // TString outputCanvas_tth=Form("Input/param/%s/Plots/yield_tth_%d",cate_name.Data(),icat);  
    // PrintCanvas(c_tth,outputCanvas_tth);
  
    // TF1* f_thjb = new TF1("f_thjb","pol3",100,150);
    // TGraph* thjb_graph = new TGraph(nmasspoint, x_points, mode_w[icat][4]);
    // thjb_graph->Fit(f_thjb);
    // TCanvas *c_thjb=new TCanvas("c_thjb","c_thjb",800,600);
    // thjb_graph->Draw("APL");
    // f_thjb->Draw("same");
    // TString outputCanvas_thjb=Form("Input/param/%s/Plots/yield_thjb_%d",cate_name.Data(),icat);  
    // PrintCanvas(c_thjb,outputCanvas_thjb);

    // TF1* f_wth = new TF1("f_wth","pol3",100,150);
    // TGraph* wth_graph = new TGraph(nmasspoint, x_points, mode_w[icat][4]);
    // wth_graph->Fit(f_wth);
    // TCanvas *c_wth=new TCanvas("c_wth","c_wth",800,600);
    // wth_graph->Draw("APL");
    // f_wth->Draw("same");
    // TString outputCanvas_wth=Form("Input/param/%s/Plots/yield_wth_%d",cate_name.Data(),icat);  
    // PrintCanvas(c_wth,outputCanvas_wth);

    // Plot interpolation of resolution
    double sigmaval[nmasspoint], sigmaerr[nmasspoint], zero[nmasspoint];
    for(int imass=0;imass<nmasspoint; imass++){
      sigmaval[imass]=sigma[imass]->getVal();
      sigmaerr[imass]=sigma[imass]->getPropagatedError(*res);
      zero[imass]=0;
    }

    TGraphErrors* sigma_graph=new TGraphErrors(nmasspoint, x_points, sigmaval,zero,sigmaerr);
    sigma_graph->GetXaxis()->SetTitle("m_{#gamma#gamma} [GeV]");
    sigma_graph->GetYaxis()->SetTitle("#sigma_{CB} [GeV]");

    TCanvas *c_sigma=new TCanvas("c_sigma","c_sigma",800,600);
    gStyle->SetEndErrorSize(5);
    sigma_graph->SetLineWidth(2);
    //sigma_graph->SetLineStyle(2);
    sigma_graph->SetMarkerColor(kBlue);
    sigma_graph->SetMarkerStyle(21);
    sigma_graph->SetFillColor(4);
    sigma_graph->SetFillStyle(3005);

    sigma_graph->Draw("a3");
    sigma_graph->Draw("p");
    TString outputCanvas_sigma=Form("Input/param/%s/Plots/param_sigma_%d",cate_name.Data(),icat);  
    PrintCanvas(c_sigma, outputCanvas_sigma);

    cout << "The number of events in each tree are: \n";
    for( int o = 0; o < nmasspoint; o++ )
      {
  	int massp = signalmass[o];
  	string pout=Form("M=%iGeV",massp);
  	cout << pout << tree[icat][o]->GetEntries() << endl;
      }
  
    int nbin = 50;
    TCanvas* c1 = new TCanvas("c1","c1");
    c1->cd();

  
    RooPlot* frame[nmasspoint];
    for( int imass = 0; imass < nmasspoint; imass++ )
      {
  	int mass_bin = signalmass[imass];
  	char cutname2[10];
  	sprintf(cutname2,"Mass_%i",mass_bin);
  	frame[imass] = v_mass.frame(Bins(nbin), Title(cutname2),Range(mass_bin-10,mass_bin+10) );
  	char cutname[30];
  	sprintf(cutname,"sample==sample::m_%i",mass_bin);
  	combData.plotOn(frame[imass],Cut(cutname));
  	char cutname3[10];
  	sprintf(cutname3,"m_%i",mass_bin);
  	simPdf.plotOn(frame[imass],Slice(sample,cutname3),ProjWData(sample,combData)) ;
  	//simPdf.paramOn(frame[f]);
  	frame[imass]->GetXaxis()->SetTitle("m_{#gamma#gamma}[GeV]");
  	frame[imass]->Draw();
  	TString channelname="";
  	// if(icat==1) channelname="Leptonic category";
  	// if(icat==2) channelname="Hadronic category";

  	PrintMassCate(mass_bin,channelname);
  	vector<TString> pavetext;
  	// pavetext.push_back("Fit parameters:");
  	// pavetext.push_back(Form("#mu_{CB}=(%.2f#pm%.2f) GeV",mu_CB[imass]->getVal(), mu_CB[imass]->getPropagatedError(*res)));
  	// pavetext.push_back(Form("#sigma_{CB}=(%.2f#pm%.2f) GeV",sigma[imass]->getVal(), sigma[imass]->getPropagatedError(*res)));
  	// pavetext.push_back(Form("#alpha_{CB}=(%.2f#pm%.2f)",alpha.getVal(), alpha.getError()));
  	// pavetext.push_back(Form("n_{CB}=10.00 (fixed)"));
  	// pavetext.push_back(Form("#mu_{Gauss}=(%.2f#pm%.2f) GeV",mu_GA[imass]->getVal(), mu_GA[imass]->getPropagatedError(*res)));
  	// pavetext.push_back(Form("#sigma_{Gauss}=(%.2f#pm%.2f) GeV",sGA[imass]->getVal(), sGA[imass]->getPropagatedError(*res)));
  	// pavetext.push_back(Form("frac_{CB}=(%.2f#pm%.2f)",frac.getVal(), frac.getError()));

  	double x1,y1,x2,y2;
  	GetX1Y1X2Y2(c1,x1,y1,x2,y2);
  	TPaveText *text=CreatePaveText(x2-0.3,y1+0.7,x2-0.01,y1+0.2,pavetext,0.035);
  	text->Draw("same");
  	TString outputCanvas=Form("Input/param/%s/Plots/m_%i_%d",cate_name.Data(),mass_bin,icat);
  	PrintCanvas(c1, outputCanvas);
      }
  
    ofstream outfile;
    //system(Form("mkdir -vp param/%s",cate_name.Data()));
    system("mkdir -vp Input/param/"+cate_name+"/all");
    system("mkdir -vp Input/param/"+cate_name+"/ggf");
    system("mkdir -vp Input/param/"+cate_name+"/vbf");
    system("mkdir -vp Input/param/"+cate_name+"/wh");
    system("mkdir -vp Input/param/"+cate_name+"/zh");
    system("mkdir -vp Input/param/"+cate_name+"/tth");
    system("mkdir -vp Input/param/"+cate_name+"/bbh");
    system("mkdir -vp Input/param/"+cate_name+"/thjb");
    system("mkdir -vp Input/param/"+cate_name+"/wth");

    for(int i=0;i<nmasspoint;i++){
      outfile.open(Form("Input/param/%s/all/cate_fit_%d_%d.txt",cate_name.Data(),signalmass[i]*10,icat),ios::out);
      outfile<<Form("%d\t",signalmass[i])<<all_w[icat][i]<<"\t"<<mu[i]->getVal()<<"\t"<<sigma[i]->getVal()<<"\t"<<alphaLo[i]->getVal()<<"\t"<<nLo.getVal()<<"\t"<<alphaHi[i]->getVal()<<"\t"<<nHi.getVal()<<endl;
      outfile.close();
      OutputProcess(Form("Input/param/%s",cate_name.Data()),icat,signalmass[i]*10,mode_w[icat][0][i],mode_w[icat][1][i],mode_w[icat][2][i],mode_w[icat][3][i],mode_w[icat][4][i],mode_w[icat][6][i],mode_w[icat][7][i],mu[i]->getVal(),sigma[i]->getVal(),alphaLo[i]->getVal(),nLo.getVal(),alphaHi[i]->getVal(),nHi.getVal());
    }

    // Save the results in a workspace
    TString outputWSName=Form("Input/param/"+cate_name+"/model_%d.root", icat);
    RooWorkspace *ws=new RooWorkspace("signalWS");
    ws->import(simPdf);
    constSet(ws->allVars(), true);
    RooRealVar yield("yield","yield", all_w[icat][0]); // Special treatment: only one mass point. Will be more complicated if multiple mass points are involved.
    ws->import(yield);
    ws->importClassCode(RooTwoSidedCBShape::Class(),true);
    ws->writeToFile(outputWSName);
  }

  cout << " " << endl;
  cout << "Parameterization Complete. Printing yield information." << endl;
  cout << " " << endl;
  double sum[10] = {0};
  for( int c = 1; c <= ncat; c++ )
  {
    cout << "  Category: " << c << endl;
    for( int m = 0; m < nprocess; m++ )
    {
      cout << "    Process " << m << " " << counter[c][m]*35 << endl;
      sum[m] += counter[c][m];
    }
  }
  cout << " " << endl;
  cout << "Sum per process: " << endl;
  for( int m = 0; m < nprocess; m++ )
  {
    cout << "  Process " << m << " " << sum[m] << endl;
  }
  cout << " " << endl;

  //--------------------------------------//
  // Do the interpolation as a last step:
  // cout << "Beginning interpolation loop." << endl;
  // for( int i_c = 1; i_c <= ncat; i_c++ )
  // {
  //   InterpolateSignal( i_c, Form("Input/param/%s/",cate_name.Data()) );
  // }
  return 0;
}
