#include "MyGRL.h"

ClassImp(Block);
ClassImp(MyGRL);

bool Block::Check(int lb){
  int n=GetLBSize();
  if(n==0){
    cerr<<"Error: No lumiblock info for run "<<_run_<<"."<<endl;
  }
  for(int i=0;i<n;i++)
    if(lb>=_lb_[i].first && lb <=_lb_[i].second) return true;
  return false;
}

void MyGRL::InitMyGRL(const char* grl){
  cout<<"Good run list input file: "<<grl<<endl;
  ifstream GRLFile;
  GRLFile.open(grl,ios::in);
  assert(GRLFile.is_open());
  string line;
  while(getline(GRLFile, line)){
    TString tline=line.c_str();
    if(tline.BeginsWith("<Run>")){
      tline.ReplaceAll("</Run>","");
      tline.ReplaceAll("<Run>","");
      Block bl(tline.Atoi());
      while(1){
	getline(GRLFile,line);
	TString tline=line.c_str();
	if( tline.Contains("</LumiBlockCollection>") ) break;
	pair<int,int> lumirange;
	vector<TString> components=SplitString(tline, '\"');
	lumirange.first=components[1].Atoi();
	lumirange.second=components[3].Atoi();
	bl.AddLB(lumirange);
      }
      _map_.push_back(bl);
    } 
  }
  GRLFile.close();
  cout<<"Good run list initialization finished."<<endl;
}

int MyGRL::SearchRun(int _run){
  int n=_map_.size();
  if(n==0){
    cerr<<"Error: Empty map."<<endl;
    return -1;
  }
  for(int idx=0;idx<n;idx++)
    if(_run==_map_[idx].GetRun()) return idx;
  return -1;
}

bool MyGRL::CheckLumi(int idx, int lb){
  return _map_[idx].Check(lb);
}

bool MyGRL::GoodEvent(int r,int l){
  int idx=SearchRun(r);
  if(idx<0){
//     cerr<<"Error: Run "<<r<<" could not be found in the map."<<endl;
    return false;
  }
  return CheckLumi(idx,l);
}

void MyGRL::PrintMap(){
  int n=_map_.size();
  for(int i=0;i<n;i++){
    cout<<"Run "<<_map_[i].GetRun()<<endl;
    for(int j=0;j<_map_[i].GetLBSize();j++){
      cout<<"LB"<<j<<": "<<_map_[i]._lb_[j].first<<" "<<_map_[i]._lb_[j].second<<endl;
    }
    cout<<endl;
  }
}

vector<TString> MyGRL::SplitString(const TString& theOpt, const char separator )
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

