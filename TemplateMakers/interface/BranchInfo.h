
#ifndef _BranchInfo_h
#define _BranchInfo_h

#include "TString.h"


template <class valClass>

class BranchInfo {

public :
  TString branchName;
  TString branchType;
  valClass branchVal;
  BranchInfo() {} ;
  BranchInfo (TString name, TString type):
    branchName(name), branchType(type)
  {};

};


#endif 
