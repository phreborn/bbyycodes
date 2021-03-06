#include "CommonFunc.h"

using namespace std;

const double epsilon=1e-6;

int CommonFunc::sign(double x){return int(fabs(x)/x);}
bool CommonFunc::IsNaN(double var){volatile double d=var;return d!=d;}
bool CommonFunc::IsEven(int num){return num%2==0;}
bool CommonFunc::IsOdd(int num){return num%2==1;}
TH1F* CommonFunc::CreateHist(TString name,TString title,TString axisx,TString axisy,int nbin,double xmin,double xmax,double min){
  TH1F *h=new TH1F(name,title,nbin,xmin,xmax);
  h->GetXaxis()->SetTitle(axisx);
  h->GetYaxis()->SetTitle(axisy);
  h->Sumw2();
  if(min>=0) h->SetMinimum(min);
  return h;
}

TH1D* CommonFunc::CreateTH1D(TString name,TString title,TString axisx,TString axisy,int nbin,double xmin,double xmax,double min){
//   TString histname=title;
//   if(tag!="") histname.Append(Form("_%s",tag.Data()));

//   TH1D *h=new TH1D(histname,histname,nbin,xmin,xmax);
  TH1D *h=new TH1D(name,title,nbin,xmin,xmax);
  h->GetXaxis()->SetTitle(axisx);
  h->GetYaxis()->SetTitle(axisy);
  h->Sumw2();
  if(min>=0) h->SetMinimum(min);
  return h;
}

THStack* CommonFunc::CreateStack(TString title,TString tag){
  TString stackname=title;
  if(tag!="") stackname.Append(Form("_%s",tag.Data()));
  THStack *hs=new THStack(stackname.Data(),stackname.Data());
  return hs;
}

TCanvas* CommonFunc::CreateCanvas(TString title,TString tag,int ww,int wh){
  TString canvasname=title;
  if(tag!="") canvasname.Append(Form("_%s",tag.Data()));
  TCanvas *c=new TCanvas(canvasname,canvasname,0,0,ww,wh);
  return c;
}

TPad* CommonFunc::CreatePad(TString title,TString tag,double x1,double y1,double x2,double y2){
  TString padname=title;
  if(tag!="") padname.Append(Form("_%s",tag.Data()));
  TPad *p=new TPad(padname,padname,x1,y1,x2,y2);
  p->Draw();
  p->cd();
  p->Modified();
  p->SetFillStyle(0);

  return p;
}

TFile* CommonFunc::OpenFile(TString fileName,TString option){
  TFile* f=new TFile(fileName.Data(),option.Data());
  TDirectory *readdir = gDirectory;
  if (f && f->IsZombie()) SafeDelete(f);
  readdir->cd();
  if(!f){
    Error("OpenFile","Cannot open file %s",fileName.Data());
    return NULL;
  }
  return f;
}

void CommonFunc::PrintCanvas(TCanvas *c, TString name){
  c->Print(Form("%s.root",name.Data()));
  c->Print(Form("%s.eps",name.Data()));
  c->Print(Form("%s.png",name.Data()));
  c->Print(Form("%s.pdf",name.Data()));
  c->Print(Form("%s.C",name.Data()));
}

void CommonFunc::GetX1Y1X2Y2(TVirtualPad *c,double x[4]){
  x[0]=c->GetFrame()->GetX1()+c->GetLeftMargin();
  x[1]=c->GetFrame()->GetY1()+c->GetBottomMargin();
  x[2]=c->GetFrame()->GetX2()-c->GetRightMargin();
  x[3]=c->GetFrame()->GetY2()-c->GetTopMargin();
}

void CommonFunc::GetX1Y1X2Y2(TVirtualPad *c,double &x1,double &y1,double &x2,double &y2){
  x1=c->GetFrame()->GetX1()+c->GetLeftMargin();
  y1=c->GetFrame()->GetY1()+c->GetBottomMargin();
  x2=c->GetFrame()->GetX2()-c->GetRightMargin();
  y2=c->GetFrame()->GetY2()-c->GetTopMargin();
}
TLegend* CommonFunc::CreateLegend(double x_low, double y_low, double x_up, double y_up, TList* h_list, vector<TString> text, vector<TString> option,double textsize)
{
    TLegend *legend = new TLegend(x_low,y_low,x_up,y_up);
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(textsize);
    legend->SetFillStyle(0);
    legend->SetFillColor(0);
    legend->SetLineColor(0);

    TIter next(h_list);
    TObject *obj = 0;
    int i=0;

    while((obj = next()))
      {
	legend->AddEntry(obj, text[i].Data(), option[i].Data());
	i++;
      }

    return legend;
}

TLegend* CommonFunc::FastLegend(double x_low, double y_low, double x_up, double y_up, double textsize)
{
    TLegend *legend = new TLegend(x_low,y_low,x_up,y_up);
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(textsize);
    legend->SetFillStyle(0);
    legend->SetFillColor(0);
    legend->SetLineColor(0);

    return legend;
}

void CommonFunc::DrawConstantLine(TVirtualPad *c, double value,double *mass,int nmass, Color_t color, int linestyle, double linewidth){
  Double_t oney[1000]; for(Int_t e=0;e<nmass;e++) oney[e]=value;
  TGraph *one = new TGraph(nmass,mass,oney);
  one->SetLineColor(color);
  one->SetLineWidth(linewidth);
  one->SetLineStyle(linestyle);
  c->cd();
  one->Draw("same");
}

TLine* CommonFunc::DrawConstantLine(TVirtualPad *c, double value, double x1, double x2, Color_t color, int linestyle, double linewidth){
  TLine *one=new TLine(x1,value,x2,value);
  one->SetLineColor(color);
  one->SetLineWidth(linewidth);
  one->SetLineStyle(linestyle);
  c->cd();
  one->Draw("same");
  return one;
}

TPaveText* CommonFunc::CreatePaveText(double x1,double y1,double x2,double y2,vector<TString> text,double textsize){
  TPaveText *tex=new TPaveText();
  tex->SetFillColor(0);tex->SetTextSize(0.05);
  tex->SetFillStyle(0);tex->SetBorderSize(0);
  int n=text.size();
  // for(int i=n-1;i>=0;i--) tex->AddText(text[i].Data());
  for(int i=0;i<n;i++) tex->AddText(text[i].Data());
  tex->SetX1NDC(x1);
  tex->SetY1NDC(y1);
  tex->SetX2NDC(x2);
  tex->SetY2NDC(y2);
  tex->SetTextSize(textsize);
  return tex;
}

void CommonFunc::ScaleToOne(TH1 *h, bool m_width, bool m_flow){
  h->Sumw2();
  TString option=m_width?"width":"";
  if(m_flow){
    int nbin=h->GetNbinsX();
    double area=h->Integral(0,nbin+1,option);
    h->Scale(1/area);
  }
  else{
    double area=h->Integral(option);
    h->Scale(1/area);
  }
}

void CommonFunc::ScaleTo(TH1 *h, double norm, bool m_width, bool m_flow){
  h->Sumw2();
  TString option=m_width?"width":"";
  if(m_flow){
    int nbin=h->GetNbinsX();
    double area=h->Integral(0,nbin+1,option);
    h->Scale(norm/area);
  }
  else{
    double area=h->Integral(option);
    h->Scale(norm/area);
  }
}

TStyle* CommonFunc::AtlasStyle() 
{
  TStyle *atlasStyle = new TStyle("ATLAS","Atlas style");

  // use plain black on white colors
  Int_t icol=0; // WHITE
  atlasStyle->SetFrameBorderMode(icol);
  atlasStyle->SetFrameFillColor(icol);
  atlasStyle->SetCanvasBorderMode(icol);
  atlasStyle->SetCanvasColor(icol);
  atlasStyle->SetPadBorderMode(icol);
  atlasStyle->SetPadColor(icol);
  atlasStyle->SetStatColor(icol);
  //atlasStyle->SetFillColor(icol); // don't use: white fill color for *all* objects

  // set the paper & margin sizes
  atlasStyle->SetPaperSize(20,26);

  // set margin sizes
  atlasStyle->SetPadTopMargin(0.05);
  atlasStyle->SetPadRightMargin(0.05);
  atlasStyle->SetPadBottomMargin(0.16);
  atlasStyle->SetPadLeftMargin(0.16);

  // set title offsets (for axis label)
  atlasStyle->SetTitleXOffset(1.1);
  atlasStyle->SetTitleYOffset(1.3);

  // use large fonts
  //Int_t font=72; // Helvetica italics
  Int_t font=42; // Helvetica
  Double_t tsize=0.05; // originally 0.05
  atlasStyle->SetTextFont(font);

  atlasStyle->SetTextSize(tsize);
  atlasStyle->SetLabelFont(font,"x");
  atlasStyle->SetTitleFont(font,"x");
  atlasStyle->SetLabelFont(font,"y");
  atlasStyle->SetTitleFont(font,"y");
  atlasStyle->SetLabelFont(font,"z");
  atlasStyle->SetTitleFont(font,"z");
  
  atlasStyle->SetLabelSize(tsize,"x");
  atlasStyle->SetTitleSize(tsize,"x");
  atlasStyle->SetLabelSize(tsize,"y");
  atlasStyle->SetTitleSize(tsize,"y");
  atlasStyle->SetLabelSize(tsize,"z");
  atlasStyle->SetTitleSize(tsize,"z");

  // use bold lines and markers
  atlasStyle->SetMarkerStyle(20);
  atlasStyle->SetMarkerSize(1.2);
  atlasStyle->SetHistLineWidth((Width_t)3.0);
  atlasStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

  // get rid of X error bars 
  //atlasStyle->SetErrorX(0.001);
  // get rid of error bar caps
  atlasStyle->SetEndErrorSize(0.);

  // do not display any of the standard histogram decorations
  atlasStyle->SetOptTitle(0);
  //atlasStyle->SetOptStat(1111);
  atlasStyle->SetOptStat(0);
  //atlasStyle->SetOptFit(1111);
  atlasStyle->SetOptFit(0);

  // put tick marks on top and RHS of plots
  atlasStyle->SetPadTickX(1);
  atlasStyle->SetPadTickY(1);

  return atlasStyle;

}

void CommonFunc::SetAtlasStyle()
{
  std::cout << "\nApplying ATLAS style settings...\n" << std::endl ;
  TStyle* atlasStyle = AtlasStyle();
  gROOT->SetStyle("ATLAS");
  gROOT->ForceStyle();
}

vector<TString> CommonFunc::SplitString(const TString& theOpt, const char separator )
{
   // splits the option string at 'separator' and fills the list
   // 'splitV' with the primitive strings
   vector<TString> splitV;
   TString splitOpt(theOpt);
   splitOpt.ReplaceAll("\n"," ");
   splitOpt = splitOpt.Strip(TString::kBoth,separator);
   while (splitOpt.Length()>0) {
      if ( !splitOpt.Contains(separator) ) {
         splitV.push_back(splitOpt);
         break;
      }
      else {
         TString toSave = splitOpt(0,splitOpt.First(separator));
         splitV.push_back(toSave);
         splitOpt = splitOpt(splitOpt.First(separator),splitOpt.Length());
      }
      splitOpt = splitOpt.Strip(TString::kLeading,separator);
   }
   return splitV;
}

TLine* CommonFunc::DrawVerticalLine(TVirtualPad *c, double value, double y1, double y2, Color_t color, int linestyle, double linewidth){
  TLine *one=new TLine(value,y1,value,y2);
  one->SetLineColor(color);
  one->SetLineWidth(linewidth);
  one->SetLineStyle(linestyle);
  c->cd();
  one->Draw("same");
  return one;
}

void CommonFunc::SetAllHistColor(TH1* h, Color_t c){
  h->SetLineColor(c);
  h->SetFillColor(c);
  h->SetMarkerColor(c);
}

double CommonFunc::Cone(double eta_t, double phi_t, double eta_l, double phi_l){
  Double_t DR = sqrt( ((eta_t - eta_l)*(eta_t - eta_l)) 
		      +(DiffPhi(phi_t - phi_l))*(DiffPhi(phi_t - phi_l)));
  return DR;
}

double CommonFunc::Cone(TLorentzVector p_t, TLorentzVector p_l){
  return Cone(p_t.Eta(),p_t.Phi(),p_l.Eta(),p_l.Phi());
}

double CommonFunc::DiffPhi(double dPhi) {
  if (fabs(dPhi) > M_PI) return fabs(2.*M_PI-fabs(dPhi));
  return fabs(dPhi);
}

double CommonFunc::DiffPhi(double phi1,double phi2){
  return DiffPhi(phi1-phi2);
}

void CommonFunc::Report(const char* _filename_,const char *_output_){
  ofstream fout(_output_,ios::app | ios::out);
  if(!!fout){
    fout<<_filename_<<endl;
    fout.close();
  }
  else Error("Report","cannot open badfiles");
}

TChain* CommonFunc::MakeChain(const char* _treename_, TString _listname_, TString _logname_, bool isroot){
  TChain *fchain=new TChain(_treename_);
  if(isroot){
    fchain->Add(_listname_);
    return fchain;
  }
  TString filename;
  ifstream fin(_listname_.Data(),ios::in);
  if(!fin){
    Error("MakeChain","Cannot open list file %s.",_listname_.Data());
    return NULL;
  }
  Int_t n=0;
  int nbad=0;

  cout<<" DATA SETS:"<<endl;
  while(fin>>filename){
    if (!filename.BeginsWith("#")) {
      /// protection for data
      int status=fchain->AddFile(filename,-1);
      if(!status){
// 	ofstream fout(_logname_,ios::out);    /// make sure that the old file is deleted
// 	if(!fout){
// 	  Error("MakeChain","Cannot open log file %s.",_logname_);
// 	}
// 	fout.close();
	Report(filename.Data(),_logname_.Data());nbad++;
      }
      else n++;
      if(n%1000==0)
      cout<<"Chaining "<<n<<"th file..."<<filename.Data()<<", "<<nbad<<" files are removed out of them."<<endl;
    }
  }
  cout<<n<<" files are chained."<<endl;
  if(nbad>0) cout<<nbad<<" files are bad. Please check "<<_logname_<<endl;
  cout<<"--------------"<<endl;
  fin.close();
  return fchain;
}

bool CommonFunc::descending_on_Pt(TLorentzVector a, TLorentzVector b){
  return a.Pt()>b.Pt();
}

int CommonFunc::FindBin(TH1 *h, double lowedge){
  double binw=h->GetBinWidth(1);
  int nbin=h->GetNbinsX();
  if(lowedge<h->GetBinLowEdge(1)-epsilon) return 0;
  if(lowedge>h->GetBinLowEdge(nbin)+epsilon) return nbin+1;
  for(int ibin=1;ibin<=nbin;ibin++){
    double temp=h->GetBinLowEdge(ibin);
    if(fabs(temp-lowedge)<epsilon) return ibin;
  }
  return -1;
}

TH1F* CommonFunc::TH1DtoTH1F(TH1D *hd){
  int nbin=hd->GetNbinsX();
  int xmin=hd->GetXaxis()->GetXmin();
  int xmax=hd->GetXaxis()->GetXmax();
  TString title=hd->GetTitle();
  TString axisx=hd->GetXaxis()->GetTitle();
  TString axisy=hd->GetYaxis()->GetTitle();
  TH1F* hf=CreateHist(title,"",axisx,axisy,nbin,xmin,xmax,0);
  for(int ibin=1;ibin<=nbin;ibin++){
    double content=hd->GetBinContent(ibin);
    double error=hd->GetBinError(ibin);
    hf->SetBinContent(ibin,content);
    hf->SetBinError(ibin,error);
  }
  return hf;
}


TH1D* CommonFunc::TH1FtoTH1D(TH1F *hf){
  int nbin=hf->GetNbinsX();
  int xmin=hf->GetXaxis()->GetXmin();
  int xmax=hf->GetXaxis()->GetXmax();
  TString name=hf->GetName();
  TString title=hf->GetTitle();
  TString axisx=hf->GetXaxis()->GetTitle();
  TString axisy=hf->GetYaxis()->GetTitle();
  TH1D* hd=CreateTH1D(name+"_th1d",title+"_th1d",axisx,axisy,nbin,xmin,xmax,0);
  for(int ibin=1;ibin<=nbin;ibin++){
    double content=hf->GetBinContent(ibin);
    double error=hd->GetBinError(ibin);
    hd->SetBinContent(ibin,content);
    hd->SetBinError(ibin,error);
  }
  return hd;
}

TH1D* CommonFunc::RerangeTH1D(TH1D *hold, double xmin_new, double xmax_new, TString tag){
  if(!hold){
    cerr<<"Error: NULL pointer provided as input."<<endl;
    abort();
  }
  int xmin=hold->GetXaxis()->GetXmin();
  int xmax=hold->GetXaxis()->GetXmax();
  if(fabs(xmin-xmin_new)<epsilon && fabs(xmax-xmax_new)<epsilon) return hold;

  int nbin=hold->GetNbinsX();
  TString name=hold->GetName();
  TString title=hold->GetTitle();
  TString axisx=hold->GetXaxis()->GetTitle();
  TString axisy=hold->GetYaxis()->GetTitle();
  double binw=hold->GetBinWidth(1);
  int nbin_new=int((xmax_new-xmin_new+epsilon)/binw);
  TH1D* hnew=CreateTH1D(name+"_expand"+tag,title+"_expand"+tag,axisx,axisy,nbin_new,xmin_new,xmax_new,0);  
  for(int ibin=1;ibin<=nbin;ibin++){
    double content=hold->GetBinContent(ibin);
    double error=hold->GetBinError(ibin);
    double binlowedge=hold->GetBinLowEdge(ibin);

    int ibin_new=FindBin(hnew,binlowedge);
    // cout<<ibin_new<<" "<<content<<endl;
    hnew->SetBinContent(ibin_new,content);
    hnew->SetBinError(ibin_new,error);
  }  
  return hnew;
}

Color_t CommonFunc::ColorWheel(int idx){
  switch(idx){
  case 0: return kBlack;
  case 1: return kRed;
  case 2: return kBlue;
  case 3: return kGreen+2;
  case 4: return kOrange+1;
  case 5: return kMagenta;
  case 6: return kCyan+1;
  case 7: return kSpring-7;
  case 8: return 9;
  case 9: return 11;
  case 10: return 30;
  case 11: return 40;
  case 12: return 41;
  case 13: return 46;
  default: return 1;
  }
}

Int_t CommonFunc::MarkerWheel(int idx){
  switch(idx){
  case 0: return 24;
  case 1: return 25;
  case 2: return 26;
  case 3: return 27;
  case 4: return 28;
  case 5: return 30;
  case 6: return 32;
  default: return 20;
  }
}

// bool CommonFunc::descending(int i, int j){ return i>j;}

bool CommonFunc::descending(double i, double j){ return i>j;}

//TTree* CommonFunc::GetTree(RooDataSet* data){
//   assert((data) && "The data pointer is NULL...");
//   // std::cout << "Name" << data->GetName() << std::endl;
//   if ( RooAbsData::defaultStorageType != RooAbsData::Vector ) {
//     return const_cast<TTree*>(data->tree());
//   } else {
//     std::string treeName = data->GetName();
//     std::map<std::string, double> brMap;
//     TTree* tree = new TTree((treeName+"_tree").c_str(), (treeName+"_tree").c_str());
//     const RooArgSet* set = data->get();
//     std::auto_ptr<TIterator> iter(set->createIterator());
//     for ( RooRealVar* v = (RooRealVar*)iter->Next(); v!=0; v = (RooRealVar*)iter->Next() ) {
//       brMap[v->GetName()] = 0;
//       /* add branch */
//       tree->Branch(v->GetName(), &brMap[v->GetName()]);
//     }

//     int nEntries = data->numEntries();
//     int index = 0;
//     for ( index = 0; index < nEntries; index++ ) {
//       const RooArgSet* tmp = data->get(index);
//       std::auto_ptr<TIterator> iter(tmp->createIterator());
//       for ( RooRealVar* v = (RooRealVar*)iter->Next(); v!=0; v = (RooRealVar*)iter->Next() ) {
// 	brMap[v->GetName()] = v->getVal();
//       }
//       // if ( index/1000==0 ) {
//       //     std::cout << "index: " << index << std::endl;
//       // }
//       tree->Fill();
//     }

//     return tree;
//   }
//}

void CommonFunc::CopyFileContent(TFile *input, TFile* target){
  TList* keys=input->GetListOfKeys();
  int nkeys=keys->GetEntries();
  for(int ikey=0;ikey<nkeys;ikey++){
    TString name=keys->At(ikey)->GetName();
    TObject* obj=input->Get(name);
    target->cd();
    obj->Write();
  }
}

TH1D *CommonFunc::VectorToHist(vector<double> vec, TString name, double xmin, double xmax, int nbin)
{
  TH1D *h=new TH1D(name,name,nbin,xmin,xmax);
  for(vector<double>::iterator it=vec.begin();it!=vec.end();++it){
    h->Fill(*it);
  }
  return h;
}

double CommonFunc::CostsCS(TLorentzVector v1, TLorentzVector v2){
  TLorentzVector Vdiphoton  = v1 + v2;

  Double_t Q=Vdiphoton.M();
  Double_t Qt=Vdiphoton.Pt(); 
  Double_t costs=TMath::Abs( 1/(Q*sqrt(Q*Q+Qt*Qt))*( (v1.E()+v1.Z())*(v2.E()-v2.Z()) - (v1.E()-v1.Z())*(v2.E()+v2.Z()) ) );

  return costs;
}

void CommonFunc::AddGraphs(TGraph* gr1, TGraph* gr2) {
  if (!(gr1->GetN() == gr2->GetN())) {
    std::cout << "ERROR: different number of bins" << std::endl;
    return;
  }
  for (int i = 0; i < gr1->GetN(); i ++) {
    if (!(gr1->GetX()[i] == gr2->GetX()[i])) {
      std::cout << "ERROR: different bin center" << std::endl;
      return;
    }
    gr1->SetPoint(i, gr1->GetX()[i], gr1->GetY()[i] + gr2->GetY()[i]);
  }
}

void CommonFunc::AddGraphsError(TGraphErrors* gr1, TGraphErrors* gr2) {
  if (!(gr1->GetN() == gr2->GetN())) {
    std::cout << "ERROR: different number of bins" << std::endl;
    return;
  }
  for (int i = 0; i < gr1->GetN(); i ++) {
    if (!(gr1->GetX()[i] == gr2->GetX()[i])) {
      std::cout << "ERROR: different bin center" << std::endl;
      return;
    }
    gr1->SetPoint(i, gr1->GetX()[i], gr1->GetY()[i] + gr2->GetY()[i]);
    gr1->SetPointError(i, 0, sqrt(gr1->GetY()[i]));
  }
}

TGraphErrors* CommonFunc::HistoToGraph(TH1D* h) {
  TGraphErrors* gr = new TGraphErrors();
  for (int i = 1; i < h->GetNbinsX()+1; i++) {
    gr->SetPoint(gr->GetN(), h->GetBinCenter(i), h->GetBinContent(i));
    gr->SetPointError(gr->GetN()-1, 0, h->GetBinError(i));
  }
  return gr;
}

TGraph* CommonFunc::scaledGraph(TGraph* g, double w) {
  TGraph* gr = new TGraph();
  for (int i = 0; i < g->GetN(); i ++) {
    gr->SetPoint(gr->GetN(), g->GetX()[i], w*g->GetY()[i]);
  }
  return gr;
}

double CommonFunc::getChi2(TH1D* h, TGraph* gr) {
  double myChi2 = 0;
  if (!(h->GetNbinsX() == gr->GetN())) {
    std::cout << "ERROR: different number of bins" << std::endl;
    return -1;
  }
  for (int i = 0; i < gr->GetN(); i++) {
    double y = h->GetBinContent(i+1);
    if (y > 0.1) {
      double diff = gr->GetY()[i] - y;
      myChi2 += (diff*diff)/(h->GetBinError(i+1)*h->GetBinError(i+1));
      std::cout << i << " " << myChi2 << std::endl;
    }
  }
  return myChi2;
}

TString CommonFunc::readNumFromOption(TString opt, TString key){
  if(opt.Contains(key)){
    return opt(opt.First(key)+key.Length(), opt.Length());
  }
  else return "";
}
