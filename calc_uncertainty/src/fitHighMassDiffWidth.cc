#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"
#include "HggTwoSidedCBPdf.hh"

using namespace std;
using namespace RooFit;
using namespace RooStats;

const double epsilon=-1e-4;

int main(int argc, char **argv){
  if(argc<2){
    cout<<"Usage: "<<argv[0]<<" <jobname> <input file list> <option>"<<endl;
    exit(0);
  }
  CommonFunc::SetAtlasStyle();

  const int nsample=5;
  
  double widthFrac[nsample]={0,0.01,0.03,
			     0.06,0.10
  };
  double binWidth[nsample]={2,2,5,5,10
  };
  
  TString sampleName[nsample]={"NWA","W1p","W3p","W6p","W10p"
  };
  
  for(int isample=0;isample<nsample;isample++){
    TString inputWSFileName="fig/fit/"+sampleName[isample]+"/plot_750_ws.root";
    unique_ptr<TFile> fin(TFile::Open(inputWSFileName));
    TList* keys = fin->GetListOfKeys();
    TIter next(keys);
    TKey* obj;
    
    RooWorkspace *ws=NULL;

    while ((obj = (TKey*)next())) {
      std::string className = obj->GetClassName();
      if ( className.find("RooWorkspace")!=std::string::npos ) {
    	ws=dynamic_cast<RooWorkspace*>(obj->ReadObj());
      }
    }
    RooAbsPdf *pdf=ws->pdf("pdf_signal_inclusive_13TeV");
    RooRealVar *x=ws->var("atlas_invMass");
    RooAbsData *data=ws->data("MC_750");
    double width=0.004;
    if(sampleName[isample]!="NWA") width=750*widthFrac[isample];
    double xmax=x->getMax(), xmin=x->getMin();

    int nbin=int((xmax-xmin)/binWidth[isample]);
    x->setBins(nbin);
    
    unique_ptr<RooWorkspace> wfactory(new RooWorkspace("wfactory"));
    wfactory->import(*x);
    wfactory->import(*data);
    
    wfactory->factory("mX[750]");
    wfactory->factory(Form("wX[%f]",width));
    wfactory->factory("RooBreitWigner::truth(atlas_invMass, mX, wX)");
    wfactory->factory("expr::mnX('(@0 - 100.)/100.', mX)");

    wfactory->factory("dmuCB[1,-100,100]");
    wfactory->factory("expr::muCB('(@0+@1*@3+@2*@3*@3)*@4', a_muCBNom_ggH_c0[0.00136622],b_muCBNom_ggH_c0[-0.0630433],c_muCBNom_ggH_c0[0.00212715],mnX,dmuCB)");

    wfactory->factory("dsigmaCB[1,0.,2]");
    wfactory->factory("expr::sigmaCB('(@0+@1*@2)*@3', a_sigmaCBNom_ggH_c0[1.51109],b_sigmaCBNom_ggH_c0[0.591404],mnX,dsigmaCB)");

    wfactory->factory("dalphaCBLo[1,0.,2]");
    wfactory->factory("expr::alphaCBLo('(@0+@1/(@3+@2))*@4',a_alphaCBLo_ggH_c0[1.48373],b_alphaCBLo_ggH_c0[0.562869],c_alphaCBLo_ggH_c0[1.23897],mnX, dalphaCBLo)");

    wfactory->factory("dalphaCBHi[1,0.,5]");
    wfactory->factory("expr::alphaCBHi('(@0+@1/(@3+@2))*@4',a_alphaCBHi_ggH_c0[2.30745],b_alphaCBHi_ggH_c0[-0.245649],c_alphaCBHi_ggH_c0[1.99998],mnX,dalphaCBHi)");
    
    wfactory->factory("dnCBLo[1]");
    wfactory->factory("expr::nCBLo('@0*@1',nCBLoNom[5.95],dnCBLo)");
    
    wfactory->factory("dnCBHi[1]");
    wfactory->factory("expr::nCBHi('@0*@1',nCBHiNom[3.15],dnCBHi)");
    
    wfactory->factory("HggTwoSidedCBPdf::detector(atlas_invMass, muCB, sigmaCB, alphaCBLo, nCBLo, alphaCBHi, nCBHi)");

    wfactory->var("atlas_invMass")->setBins(10000,"cache");
    unique_ptr<RooFFTConvPdf> conv(new RooFFTConvPdf("convolution","convolution", *wfactory->var("atlas_invMass"), *wfactory->pdf("truth"), *wfactory->pdf("detector")));

    RooAbsReal *nll=conv->createNLL(*wfactory->data(data->GetName()));
    nll->enableOffsetting(true);
    RooMinimizer minim(*nll);
    minim.setStrategy(1);
    minim.setPrintLevel(0);
    minim.setProfile(); /* print out time */
    minim.setEps(1);
    // minim.optimizeConst(2);
    minim.minimize("Minuit2");

    unique_ptr<RooPlot> frame(wfactory->var("atlas_invMass")->frame());
    wfactory->data(data->GetName())->plotOn(frame.get());
    conv->plotOn(frame.get());
    conv->paramOn(frame.get());
    TCanvas c("c","c",800,600);
    frame->SetMaximum(frame->GetMaximum()*2);
    frame->Draw();

    system("mkdir -vp fig/fit/diffWidth/");
    CommonFunc::PrintCanvas(&c, "fig/fit/diffWidth/plot_"+sampleName[isample]);
    
  }
}
