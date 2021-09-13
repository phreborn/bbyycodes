#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"

using namespace std;
using namespace RooFit;
using namespace RooStats;
using namespace CommonFunc;

double minimize(ModelConfig *mc, RooAbsData *data){
  unique_ptr<RooAbsReal> nll(mc->GetPdf()->createNLL(*data, Constrain(*mc->GetNuisanceParameters()), GlobalObservables(*mc->GetGlobalObservables())));
  nll->enableOffsetting(true);
  RooMinimizer minim(*nll);
  minim.setStrategy(0);
  minim.setPrintLevel(-1);
  minim.setEps(1);
  // minim.optimizeConst(2);
  int status=minim.minimize("Minuit2");
  return nll->getVal();
}

void unfoldConstraints(RooArgSet& initial, RooArgSet& final, RooArgSet& obs, RooArgSet& nuis, int& counter)
{
  if (counter > 50)
  {
    cout << "ERROR::Couldn't unfold constraints!" << endl;
    cout << "Initial: " << endl;
    initial.Print("v");
    cout << endl;
    cout << "Final: " << endl;
    final.Print("v");
    exit(1);
  }
  TIterator* itr = initial.createIterator();
  RooAbsPdf* pdf;
  while ((pdf = (RooAbsPdf*)itr->Next()))
  {
    RooArgSet nuis_tmp = nuis;
    RooArgSet constraint_set(*pdf->getAllConstraints(obs, nuis_tmp, false));
    //if (constraint_set.getSize() > 1)
    //{
    string className(pdf->ClassName());
    if (className != "RooGaussian" && className != "RooLognormal" && className != "RooGamma" && className != "RooPoisson" && className != "RooBifurGauss")
    {
      counter++;
      unfoldConstraints(constraint_set, final, obs, nuis, counter);
    }
    else
    {
      final.add(*pdf);
    }
  }
  delete itr;
}

RooAbsData* generateAsimov(ModelConfig *mc){
  RooAbsPdf *combPdf=mc->GetPdf();
  RooArgSet mc_obs = *mc->GetObservables();
  RooArgSet mc_globs = *mc->GetGlobalObservables();
  RooArgSet mc_nuis = *mc->GetNuisanceParameters();

//pair the nuisance parameter to the global observable
  RooArgSet mc_nuis_tmp = mc_nuis;
  RooArgList nui_list("ordered_nuis");
  RooArgList glob_list("ordered_globs");
  RooArgSet constraint_set_tmp(*combPdf->getAllConstraints(mc_obs, mc_nuis_tmp, false));
  RooArgSet constraint_set;
  int counter_tmp = 0;
  unfoldConstraints(constraint_set_tmp, constraint_set, mc_obs, mc_nuis_tmp, counter_tmp);

  TIterator* cIter = constraint_set.createIterator();
  RooAbsArg* arg;
  while ((arg = (RooAbsArg*)cIter->Next()))
  {
    RooAbsPdf* pdf = (RooAbsPdf*)arg;
    if (!pdf) continue;
//     cout << "Printing pdf" << endl;
//     pdf->Print();
//     cout << "Done" << endl;
    TIterator* nIter = mc_nuis.createIterator();
    RooRealVar* thisNui = NULL;
    RooAbsArg* nui_arg;
    while ((nui_arg = (RooAbsArg*)nIter->Next()))
    {
      if (pdf->dependsOn(*nui_arg))
      {
	thisNui = (RooRealVar*)nui_arg;
	break;
      }
    }
    delete nIter;

    //RooRealVar* thisNui = (RooRealVar*)pdf->getObservables();


//need this incase the observable isn't fundamental. 
//in this case, see which variable is dependent on the nuisance parameter and use that.
    RooArgSet* components = pdf->getComponents();
//     cout << "\nPrinting components" << endl;
//     components->Print();
//     cout << "Done" << endl;
    components->remove(*pdf);
    if (components->getSize())
    {
      TIterator* itr1 = components->createIterator();
      RooAbsArg* arg1;
      while ((arg1 = (RooAbsArg*)itr1->Next()))
      {
	TIterator* itr2 = components->createIterator();
	RooAbsArg* arg2;
	while ((arg2 = (RooAbsArg*)itr2->Next()))
	{
	  if (arg1 == arg2) continue;
	  if (arg2->dependsOn(*arg1))
	  {
	    components->remove(*arg1);
	  }
	}
	delete itr2;
      }
      delete itr1;
    }
    if (components->getSize() > 1)
    {
      cout << "ERROR::Couldn't isolate proper nuisance parameter" << endl;
      return NULL;
    }
    else if (components->getSize() == 1)
    {
      thisNui = (RooRealVar*)components->first();
    }



    TIterator* gIter = mc_globs.createIterator();
    RooRealVar* thisGlob = NULL;
    RooAbsArg* glob_arg;
    while ((glob_arg = (RooAbsArg*)gIter->Next()))
    {
      if (pdf->dependsOn(*glob_arg))
      {
	thisGlob = (RooRealVar*)glob_arg;
	break;
      }
    }
    delete gIter;

    if (!thisNui || !thisGlob)
    {
      cout << "WARNING::Couldn't find nui or glob for constraint: " << pdf->GetName() << endl;
      //return;
      continue;
    }

    // cout << "Pairing nui: " << thisNui->GetName() << ", with glob: " << thisGlob->GetName() << ", from constraint: " << pdf->GetName() << endl;

    nui_list.add(*thisNui);
    glob_list.add(*thisGlob);

  }
  int nrNuis = nui_list.getSize();
  if (nrNuis != glob_list.getSize())
    {
      cout << "ERROR::nui_list.getSize() != glob_list.getSize()!" << endl;
      return NULL;
    }

  for (int i=0;i<nrNuis;i++)
    {
      RooRealVar* nui = (RooRealVar*)nui_list.at(i);
      RooRealVar* glob = (RooRealVar*)glob_list.at(i);

      //cout << "nui: " << nui << ", glob: " << glob << endl;
      //cout << "Setting glob: " << glob->GetName() << ", which had previous val: " << glob->getVal() << ", to conditional val: " << nui->getVal() << endl;

      glob->setVal(nui->getVal());
    }
  return AsymptoticCalculator::GenerateAsimovData( *mc->GetPdf(), *mc->GetObservables());
}

int main(int argc, char** argv){
  RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
  TString inputWSFileName=argv[1];
  TString inputSetup=argv[2];
  vector<TString> inputSetupArr=SplitString(inputSetup,',');
  vector<pair<TString, double> > inputVar;

  for(auto item : inputSetupArr){
    vector<TString> inputVarArr=SplitString(item,'=');
    inputVar.push_back(make_pair(inputVarArr[0],inputVarArr[1].Atof()));
  }
  
  TFile *f=TFile::Open(inputWSFileName);
  RooWorkspace *w=(RooWorkspace*)f->Get("combWS");
  ModelConfig *mc=(ModelConfig*)w->obj("ModelConfig");
  RooAbsPdf *pdf=mc->GetPdf();
  RooAbsData *data=w->data("combData");
  ofstream fout(inputWSFileName.ReplaceAll(".root",".inj"));
  
  // w->saveSnapshot("nominalNuis",*mc->GetNuisanceParameters());
  // w->saveSnapshot("nominalGlobs",*mc->GetGlobalObservables());
  
  for(vector<pair<TString, double> >::iterator itr=inputVar.begin(); itr!=inputVar.end(); itr++){
    w->var(itr->first)->setVal(itr->second);
    w->var(itr->first)->setConstant(true);
  }
  double nllinj_obs=minimize(mc, data);
  unique_ptr<RooAbsData> asimovData(generateAsimov(mc));
  
  cout<<"With injected ";
  fout<<"With injected ";
  for(vector<pair<TString, double> >::iterator itr=inputVar.begin(); itr!=inputVar.end(); itr++){
    cout<<itr->first<<"="<<itr->second<<" ";
    fout<<itr->first<<"="<<itr->second<<" ";
  }
  cout<<endl;
  fout<<endl;
  // Now calculating expected p0
  w->var("xs")->setConstant(false);
  w->var("xs")->setRange(0,100);

  double nllhat_exp=minimize(mc,asimovData.get());

  w->var("xs")->setVal(0);
  w->var("xs")->setConstant(true);

  double nllfix_exp=minimize(mc,asimovData.get());

  double pvalue_exp=1-ROOT::Math::normal_cdf(sqrt(2*(nllfix_exp-nllhat_exp)),1,0);

  cout<<"The expected significance is "<<PValueToSignificance(pvalue_exp)<<endl;
  fout<<"The expected significance is "<<PValueToSignificance(pvalue_exp)<<endl;
  w->loadSnapshot("nominalNuis");
  w->loadSnapshot("nominalGlobs");
  // Now calculating observed p0
  w->var("xs")->setConstant(false);
  w->var("xs")->setRange(0,100);

  double nllhat_obs=minimize(mc,data);

  w->var("xs")->setVal(0);
  w->var("xs")->setConstant(true);

  double nllfix_obs=minimize(mc,data);

  double pvalue_obs=1-ROOT::Math::normal_cdf(sqrt(2*(nllfix_obs-nllhat_obs)),1,0);

  cout<<"The observed significance is "<<PValueToSignificance(pvalue_obs)<<endl;
  fout<<"The observed significance is "<<PValueToSignificance(pvalue_obs)<<endl;

  // The tension between expected and observed
  double pvalue_tension=ROOT::Math::chisquared_cdf_c(2*(nllinj_obs-nllhat_obs),1);
  cout<<"The tension significance is "<<PValueToSignificance(pvalue_tension/2)<<endl;
  fout<<"The tension significance is "<<PValueToSignificance(pvalue_tension/2)<<endl;
  cout<<sqrt(2*(nllinj_obs-nllhat_obs))<<endl;
}

