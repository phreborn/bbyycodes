#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"
#include "titleList.hh"
#include "HggTwoSidedCBPdf.hh"
#include "HggGravitonLineShapePdf.hh"
#include "FlexibleInterpVarMkII.hh"
#include "statistics.hh"

using namespace std;
using namespace RooFit;
using namespace RooStats;
using namespace CommonFunc;

int main(int argc, char**argv){
    //============================ Global booking and setting ==========================
  //   gErrorIgnoreLevel = kError+1;
  map<string,bool> Opt;
  Opt["FIT"]=false;
  Opt["CALC"]=false;

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
  map<TString,TString> title=createTitleList();
  //================================= Do the fit ====================================
  if(Opt["FIT"]){
    TString jobname=argv[2];
    TString inputWSFileName=argv[3];
    // double mass=atof(argv[4]);
    // double width=atof(argv[5]);
    
    TString option=argv[4];
    
    TString wname="combWS", mname="ModelConfig", dname="combData";

    if(option.Contains("mt")) dname+="binned";
    if(option.Contains("asimov")) dname="asimovData_0";
    TFile *fws=TFile::Open(inputWSFileName);
    RooWorkspace *ws=(RooWorkspace*)fws->Get(wname);
    ModelConfig *mc=(ModelConfig*)ws->obj(mname);
    RooSimultaneous *pdf=(RooSimultaneous*)mc->GetPdf();
    RooDataSet *data=(RooDataSet*)ws->data(dname);
    RooAbsCategoryLValue*  m_cat = (RooAbsCategoryLValue*)&pdf->indexCat();
    RooArgSet *nuis=(RooArgSet*)mc->GetNuisanceParameters();
    
    int numChannels = m_cat->numBins(0);

    TList* m_dataList = data->split( *m_cat, true );

    RooArgSet *fullSet=new RooArgSet();
    RooArgSet *statSet=new RooArgSet();
    RooArgSet *fixSet=new RooArgSet();
    
    fullSet->add(*nuis);
    
    statSet->add(*nuis->selectByName("nbkg_ttH_*"));
    // statSet->add(*nuis->selectByName("ttH_a_*"));

    if(option.Contains("asimov")){
      ws->loadSnapshot("conditionalNuis_0");
      ws->loadSnapshot("conditionalGlobs_0");
    }

    if(option.Contains("asimov")||option.Contains("bonly")){
      if(option.Contains("bonly")) ws->loadSnapshot("ucmles_0");
    }
    else ws->loadSnapshot("ucmles");
    
    statistics::constSet(fixSet,true);

    cout<<"Summary of parameters:"<<endl;
    cout<<"Full set:"<<endl;
    fullSet->Print("V");
    cout<<"Stat set:"<<endl;
    statSet->Print("V");
    cout<<"Fix set:"<<endl;
    fixSet->Print("V");

    ws->var("mu_XS_ttH")->setConstant(false);
    RooFitResult* res=statistics::profileToData(mc, data, "Minuit2", 1, 1e-5, 1, true, false);
    statistics::setVal(ws->var("mu"), 0, true); // look only at background

    system("mkdir -vp fig/fit/"+jobname);
    TString outputFileName="fig/fit/"+jobname+Form("/output.root");
    TFile *fout=TFile::Open(outputFileName,"recreate");

    for ( int i= 0; i < numChannels; i++ ) {
      m_cat->setBin(i);
      TString channelname=m_cat->getLabel();
    
      RooAbsPdf* pdfi = pdf->getPdf(m_cat->getLabel());
      RooDataSet* datai = ( RooDataSet* )( m_dataList->At( i ) );
      std::cout << "\t\tIndex: " << i << ", Pdf: " << pdfi->GetName() << ", Data: " << datai->GetName()  << ", SumEntries: " << datai->sumEntries() << " NumEntries: "<< datai->numEntries() <<std::endl;
    
      RooRealVar *x=(RooRealVar*)pdfi->getObservables(datai)->first();

      unique_ptr<RooDataSet> asimovData((RooDataSet*)AsymptoticCalculator::GenerateAsimovData(*pdfi, RooArgSet(*x)));

      RooCurve *cenCurve=statistics::convertAsimovToCurve(asimovData.get(), x->GetName(), false);

      cenCurve->SetName("nominal_"+channelname);
      
      RooCurve* bandFull=statistics::createBand(cenCurve, pdfi, x, res, fullSet, 1, 1, false);
      bandFull->SetName("bandFull_"+channelname);
      
      RooCurve* bandStat=NULL;
      bandStat=statistics::createBand(cenCurve, pdfi, x, res, statSet, 1, 1, false);
      bandStat->SetName("bandStat_"+channelname);

      cenCurve->Write();
      bandFull->Write();
      bandStat->Write();
    }
    fout->Close();
  }
  if(Opt["CALC"]){
    RooMsgService::instance().getStream(1).removeTopic(RooFit::NumIntegration) ;
    RooMsgService::instance().getStream(1).removeTopic(RooFit::Fitting) ;
    RooMsgService::instance().getStream(1).removeTopic(RooFit::Minimization) ;
    RooMsgService::instance().getStream(1).removeTopic(RooFit::InputArguments) ;
    RooMsgService::instance().getStream(1).removeTopic(RooFit::Eval) ;

    RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);
    
    TString jobname=argv[2];
    TString inputWSFileName=argv[3];
    
    TFile *f=TFile::Open(inputWSFileName);

    TString wname="combWS", mname="ModelConfig", dname="combData";
    
    RooWorkspace *ws=(RooWorkspace*)f->Get(wname);
    ModelConfig *mc=(ModelConfig*)ws->obj(mname);
    RooSimultaneous *pdf=(RooSimultaneous*)mc->GetPdf();
    RooDataSet *data=(RooDataSet*)ws->data(dname);
    RooAbsCategoryLValue*  m_cat = (RooAbsCategoryLValue*)&pdf->indexCat();
    const int numChannels = m_cat->numBins(0);
    TList* m_dataList = data->split( *m_cat, true );

    ws->var("mu")->setVal(0);
    TString inputDir="fig/fit/"+jobname;
    TFile *fin=TFile::Open(inputDir+Form("/output.root"));
    cout<<inputDir+Form("/output.root")<<endl;

    TFile *fout=TFile::Open(inputDir+Form("/curves.root"), "recreate");

    double xmin[numChannels]={122.9015, 122.3758, 122.1479, 122.9198, 122.5932, 122.5125, 122.5274};
    double xmax[numChannels]={128.5467, 128.9637, 129.2055, 128.5588, 128.8743, 128.9520, 128.9209};
    double central_int[numChannels], central[numChannels], errHi[numChannels], errLo[numChannels], errHiStat[numChannels], errLoStat[numChannels], errHiSyst[numChannels], errLoSyst[numChannels], syst_int[numChannels], MC_stat[numChannels];
    for ( int i= 0; i < numChannels; i++ ) {
      m_cat->setBin(i);
      TString channelname=m_cat->getLabel();

      RooAbsPdf* pdfi = pdf->getPdf(m_cat->getLabel());
      RooDataSet* datai = ( RooDataSet* )( m_dataList->At( i ) );
      std::cout << "\t\tIndex: " << i << ", Pdf: " << pdfi->GetName() << ", Data: " << datai->GetName()  << ", SumEntries: " << datai->sumEntries() << " NumEntries: "<< datai->numEntries() <<std::endl;
    
      RooRealVar *obs=(RooRealVar*)pdfi->getObservables(datai)->first();
      RooRealVar *nbkg=(RooRealVar*)pdfi->getVariables()->selectByName("nbkg_*")->first();
      RooCurve *nominal=(RooCurve*)fin->Get("nominal_"+channelname);
      RooCurve *band=(RooCurve*)fin->Get("bandFull_"+channelname);
      RooCurve *band_nosys=(RooCurve*)fin->Get("bandStat_"+channelname);

      RooCurve *upper=new RooCurve();
      RooCurve *lower=new RooCurve();
      int npoint=band->GetN()/2;

      // Split the band into upper and lower errors
      for(int ipoint=0; ipoint<npoint; ipoint++){
	double x,y;
	band->GetPoint(ipoint,x,y);
	lower->addPoint(x,y);
	band->GetPoint(2*npoint-ipoint-1,x,y);
	upper->addPoint(x,y);
      }

      // if(inputWSFileName.Contains("histfactory")) insertMCStat(ws, nominal, upper, lower);
      RooCurve *upper_nosys=new RooCurve();
      RooCurve *lower_nosys=new RooCurve();
      int npoint_nosys=band_nosys->GetN()/2;

      // Split the band into upper and lower errors
      for(int ipoint=0; ipoint<npoint_nosys; ipoint++){
	double x,y;
	band_nosys->GetPoint(ipoint,x,y);
	lower_nosys->addPoint(x,y);
	band_nosys->GetPoint(2*npoint-ipoint-1,x,y);
	upper_nosys->addPoint(x,y);
      }

      fout->cd();

      nominal->Write();
      upper->Write();
      lower->Write();
      band->Write();

      obs->setRange("range",xmin[i],xmax[i]);
      double binw=(obs->getMax()-obs->getMin())/double(obs->numBins());
      RooAbsReal* integral =  (RooAbsReal*)(pdf->createIntegral(RooArgSet(*obs), NormSet(*obs) , Range("range"))) ;
      central_int[i]=nbkg->getVal()*integral->getVal();

      central[i]=nominal->average(xmin[i], xmax[i])*(xmax[i]-xmin[i])/binw;
    
      errHi[i]=upper->average(xmin[i], xmax[i])*(xmax[i]-xmin[i])/binw-central[i];
      errLo[i]=central[i]-lower->average(xmin[i], xmax[i])*(xmax[i]-xmin[i])/binw;

      errHiStat[i]=upper_nosys->average(xmin[i], xmax[i])*(xmax[i]-xmin[i])/binw-central[i];
      errLoStat[i]=central[i]-lower_nosys->average(xmin[i], xmax[i])*(xmax[i]-xmin[i])/binw;

      errHiSyst[i]=sqrt(errHi[i]*errHi[i]-errHiStat[i]*errHiStat[i]);
      errLoSyst[i]=sqrt(errLo[i]*errLo[i]-errLoStat[i]*errLoStat[i]);

      cout<<"For mass window ["<<xmin[i]<<", "<<xmax[i]<<"]:"<<endl;
      cout<<central[i]<<"+"<<errHi[i]<<"-"<<errLo[i]<<endl;
      cout<<central[i]<<"+"<<errHiStat[i]<<"-"<<errLoStat[i]<<"(stat.)+"<<errHiSyst[i]<<"-"<<errLoSyst[i]<<"(syst.)"<<endl;
      // cout<<central_int[i]<<endl;
      // cout<<syst_int[i]<<endl;
        
      // cout<<Form("%.0f\t%4.0f~%4.0f\t%.4f+%.4f-%.4f=%.4f+%.4f-%.4f(stat.)+%.4f-%.4f(syst.) %.4f", mass[i], xmin[i], xmax[i], central[i], errHi[i], errLo[i], central[i], errHiStat[i], errLoStat[i], errHiSyst[i], errLoSyst[i], MC_stat[i])<<endl;
    }
    
    fout->Close();
  }
}
