#ifndef GRL_H
#define GRL_H
#include "CommonHead.h"

using namespace std;

class Block : public TObject{
 public:
  Block(){}
  Block(int _run){SetRun(_run);}
  ~Block(){/* SafeDelete(_lb_) */;}
  void SetRun(int _run){_run_=_run;}
  void AddLB(pair<int,int> _lb){_lb_.push_back(_lb);}
  int GetLBSize(){return _lb_.size();}
  int GetRun(){return _run_;}
  bool Check(int _lb);
 public:
  int _run_;
  vector< pair<int,int> > _lb_;

  ClassDef(Block,1);
};

class MyGRL : public TObject{
 public:
  MyGRL(){}
  MyGRL(const char* _grl){InitMyGRL(_grl);}
  ~MyGRL(){/* SafeDelete(_map_) */;}
  void InitMyGRL(const char* _grl);
  bool GoodEvent(int _run,int _lb);
  int SearchRun(int _run);
  bool CheckLumi(int _idx,int _lb);
  void PrintMap();
  vector<TString> SplitString(const TString& theOpt, const char separator );
 public:
  vector<Block> _map_;
  ClassDef(MyGRL,2);
};
#endif
