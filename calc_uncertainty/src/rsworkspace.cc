#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"
#include "statistics.hh"

using namespace std;
using namespace RooFit;
using namespace RooStats;
using namespace CommonFunc;

void ReleaseTheGhost(RooDataSet *data, RooRealVar *x, RooRealVar *w, int nbin=120, double ghostwt=1e-8);

int main(int argc, char** argv){
  //***************************= Global booking and setting ************************==
  //   gErrorIgnoreLevel = kError+1;
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
  // ************************** Bootstrap resampling ***********************************
  if(Opt["BOOTSTRAP"]){
    if(argc<7){
      cout<<"Usage: "<<argv[0]<<" "<<argv[1]<<" <input ws> <input data> <seed> <sample size> <option>"<<endl;
      cout<<"For option, choose between scalar and graviton"<<endl;
      return 0;
    }

    TString wname="combWS";
    TString mname="ModelConfig";
    TString dname="combData";
    
    TString inputWSName=argv[2];
    TString inputDataName=argv[3];
    int seed=atoi(argv[4]);
    int sampleSize=atoi(argv[5]);	
    TString option=argv[6];
    option.ToLower();
    
    unique_ptr<TFile> fin(TFile::Open(inputWSName,"r"));

    RooWorkspace *win=dynamic_cast<RooWorkspace*>(fin->Get(wname));
    ModelConfig* mcin = dynamic_cast<ModelConfig*>(win->obj(mname));
    RooSimultaneous *pdfin=dynamic_cast<RooSimultaneous*>(mcin->GetPdf());
    RooDataSet *datain=dynamic_cast<RooDataSet*>(win->data(dname));

    RooRealVar *obsArr[50];
    RooRealVar *wtArr[50];
    RooDataSet *dataArr[50];
    TString cNameArr[50];
    RooAbsPdf *pdfArr[50];

    RooAbsCategoryLValue*  catin = (RooAbsCategoryLValue*)&pdfin->indexCat();
    int numChannels = catin->numBins(0);

    unique_ptr<TList> datainList(datain->split( *catin, true ));
    
    for ( int icat=0; icat < numChannels; icat++ ) {
      catin->setBin(icat);
      TString channelname=catin->getLabel();
      RooDataSet* datai = dynamic_cast<RooDataSet*>(datainList->At(icat));
      RooAbsPdf* pdfi = pdfin->getPdf(catin->getLabel());
      cout<<"Channel name:"<<channelname<<" "<<icat<<" pdf address: "<<pdfi<<endl;

      RooRealVar *x=dynamic_cast<RooRealVar*>(pdfi->getObservables(datai)->first());
      obsArr[icat]=x;
      cNameArr[icat]=channelname;
      pdfArr[icat]=pdfi;
    }

    // Recreate the PDF and dataset: try to start building a new workspace
    RooCategory catout("channellist","channellist");
    RooArgSet obsout;
    RooSimultaneous CombinedPdf("CombinedPdf","",catout) ;
    map<string,RooDataSet*> datasetMap;

    bool ucmlesExist=win->loadSnapshot("ucmles"); // A snapshot saving best fit results. If you do not have it, do not worry.
    cout<<"Creating resampled workspace"<<endl;

    // Prepare the channellist and combined pdf
    for(int icat=0;icat<numChannels;icat++){
      cout<<"Category name: "<<cNameArr[icat]<<", PDF name: "<<pdfArr[icat]->GetName()<<endl;
      catout.defineType(cNameArr[icat]);
      CombinedPdf.addPdf(*pdfArr[icat],cNameArr[icat]);
    }

    RooWorkspace wout(wname);

    wout.import(CombinedPdf, Silence());

    statistics::duplicateSet(&wout,(RooArgSet*)mcin->GetNuisanceParameters(),"nuisanceParameters");
    statistics::duplicateSet(&wout,(RooArgSet*)mcin->GetGlobalObservables(),"globalObservables");
    statistics::duplicateSet(&wout,(RooArgSet*)mcin->GetParametersOfInterest(),"poi");
    
    RooSimultaneous* pdfout=dynamic_cast<RooSimultaneous*>(wout.pdf("CombinedPdf"));

    // Remap the pointer addresses to the ones in output workspace
    for ( int icat = 0; icat < numChannels; icat++ ) {
      catout.setBin(icat);
      RooAbsPdf* pdfi = pdfout->getPdf(catout.getLabel());
      RooRealVar *x=wout.var(obsArr[icat]->GetName());
      obsArr[icat]=x;
      wtArr[icat]=new RooRealVar(Form("wt_%d",icat),Form("wt_%d",icat),1);
      dataArr[icat]=new RooDataSet(Form("resample_%d",icat),Form("resample_%d",icat),RooArgSet(*x, *wtArr[icat]), WeightVar(*wtArr[icat]));
      pdfArr[icat]=pdfi;
    }

    // Resampling
    // First read in dataset. Let's use a text file
    ifstream fData(inputDataName,ios::in);
    
    int Run;
    ULong64_t Event;
    bool PassScalar, PassGraviton;
    double Mass;

    vector<int> run, event, passScalar, passGraviton;
    vector<double> mass;

    cout<<"Start filling the dataset"<<endl;
    while(fData>>Run>>Event>>Mass>>PassScalar>>PassGraviton){
      run.push_back(Run);
      event.push_back(Event);
      mass.push_back(Mass);
      passScalar.push_back(PassScalar);
      passGraviton.push_back(PassGraviton);
    }
    cout<<"Finish filling dataset."<<endl;
    fData.close();

    int nevent=run.size();

    TRandom3 *rndm=new TRandom3(seed);
    int ivictim=rndm->Integer(nevent);

    int nblock=nevent/sampleSize;
    int residual=nevent%sampleSize;

    cout<<"There are "<<nevent<<" events to be divided into "
	<<nblock<<" blocks. "
	<<residual<<" events will then be picked up randomly"<<endl;

    for(int iblk=0;iblk<nblock;iblk++){
      int blkidx=rndm->Integer(nblock);
      for(int ievt=sampleSize*blkidx;ievt<sampleSize*(blkidx+1);ievt++){
	if(((option.Contains("scalar")&&passScalar[ievt])||(option.Contains("graviton")&&passGraviton[ievt]))&&
	   mass[ievt]>obsArr[0]->getMin()&&mass[ievt]<obsArr[0]->getMax() // Cannot fill events out of the observable window
	   ){
	  obsArr[0]->setVal(mass[ievt]); // There is only one category in this case, so idx 0
	  dataArr[0]->add(*obsArr[0]);
	}
      }   
    }
    // ***************************************************
    // The size of the entire dataset is not always a integer
    // multiplication of the sample size we give. so let's pick
    // up some luck ones to make the total number correct
    // N.B. by "total number" I mean total number of scalar U graviton dataset
    // Number of data events in each analysis can fluctuate
    // ***************************************************
    for(int ires=0;ires<residual;ires++){
      int ievt=rndm->Integer(nevent);
      if((option.Contains("scalar")&&passScalar[ievt])||(option.Contains("graviton")&&passGraviton[ievt])){
	obsArr[0]->setVal(mass[ievt]);
	dataArr[0]->add(*obsArr[0]);
      }
    }
    
    for(int icat=0;icat<numChannels;icat++){
      // Inject ghost events to make the fit stable
      ReleaseTheGhost(dataArr[icat],obsArr[icat],wtArr[icat],200,1e-9);
      datasetMap[cNameArr[icat].Data()]=dataArr[icat];
      obsout.add(*obsArr[icat]);
    }

    RooRealVar wt("wt","wt",1);//,0,10000);

    RooArgSet argsout;
    argsout.add(obsout);
    argsout.add(wt);

    RooDataSet rsData(dname,"resampled data ", argsout, Index(catout), Import(datasetMap) ,WeightVar(wt));

    cout<<"++++++++++++++++++++ input data ++++++++++++++++++++"<<endl;
    cout<<"SumEntries: "<<datain->sumEntries()<<endl;
    datain->Print("v");
    cout<<"++++++++++++++++++++ resampled data ++++++++++++++++++++"<<endl;
    cout<<"SumEntries: "<<rsData.sumEntries()<<endl;
    rsData.Print("v");
    wout.import(rsData);
    cout<<"Importing ModelConfig:"<<endl;
    ModelConfig mcout(mname,&wout);
    mcout.SetPdf(*pdfout);
    mcout.SetObservables(obsout);
    mcout.SetParametersOfInterest( *wout.set("poi") );
    mcout.SetNuisanceParameters( (*wout.set("nuisanceParameters")) );
    mcout.SetGlobalObservables( (*wout.set("globalObservables")) );
    wout.import(mcout);

    // Save the best fit snapshot
    cout<<"Saving snapshot"<<endl;
    RooArgSet* poiAndNuis=new RooArgSet();
    poiAndNuis->add(*mcout.GetNuisanceParameters());
    poiAndNuis->add(*mcout.GetParametersOfInterest());
    if(ucmlesExist) wout.saveSnapshot("ucmles",*poiAndNuis);

    TString tag="";
    if(option.Contains("scalar")) tag="scalar";
    if(option.Contains("graviton")) tag="graviton";
    // wout.importClassCode(); // Not good habit: make sure the code is there by yourself
    fData.close();
    wout.writeToFile("ws_resample_"+tag+".root");
  }
}

void ReleaseTheGhost(RooDataSet *obsdata, RooRealVar *x, RooRealVar *w, int nbin, double ghostwt){
  TH1F* h_data = new TH1F("h_data","",nbin,x->getMin(),x->getMax());
  RooArgSet* obs = (RooArgSet*)obsdata->get();
  RooRealVar* xdata = (RooRealVar*)obs->find(x->GetName());
  int nevt1=obsdata->numEntries();
  for (int i=0 ; i<nevt1 ; i++) {
    obsdata->get(i) ;
//     cout<<xdata->GetName()<<" "<<xdata->getVal()<<endl;
//     cout<<x<<" "<<xdata<<endl;getchar();
    h_data->Fill( xdata->getVal() );
  }
  for( int ibin = 1 ; ibin < nbin ; ibin++) {
    // 240 bins -> 0.25 GeV per bin
    if(h_data->GetBinContent(ibin)==0){
      x->setVal(h_data->GetBinCenter(ibin));
      w->setVal(ghostwt);
      obsdata -> add( RooArgSet(*x,*w), ghostwt);
    }
  }
  int nevt2=obsdata->numEntries();
  cout<<nevt1<<" "<<nevt2<<endl;
//   for (int i=0 ; i<nevt2 ; i++) {
//     obsdata->get(i) ;
//     cout<<xdata->GetName()<<" "<<xdata->getVal()<<" "<<obsdata->weight()<<endl;
// //     cout<<x<<" "<<xdata<<endl;getchar();
//     h_data->Fill( xdata->getVal() );
//   }
//   getchar();
  obsdata->Print();
  delete h_data;
}
