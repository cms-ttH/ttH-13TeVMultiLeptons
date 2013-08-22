#include "ttHMultileptonAnalysis/TemplateMakers/interface/TTreeWrapper.h"

using namespace std;



//

TTreeWrapper::TTreeWrapper ( ) : myTree(0)
{}


///

void TTreeWrapper::addBranch(string bName, string type){

  // for some reason, the branch declaration didn't like
  // c strings and perfers to have TStrings
  TString tempTypeDeclare(bName.c_str());
  tempTypeDeclare += TString(type.c_str());
 

  if (myVerboseFlag) cout << "Echoing add branch " << bName << " type " << type << "   both   " << tempTypeDeclare << endl;
  
  if (type == "/I"){
    intBranches[bName] = new int (0);
    //myTree->Branch(bName.c_str(), intBranches[bName]);
    myTree->Branch(bName.c_str(), intBranches[bName], tempTypeDeclare);
  } else if (type == "/F") {
    floatBranches[bName] = new float(0.0);
    //myTree->Branch(bName.c_str(), floatBranches[bName]);
    myTree->Branch(bName.c_str(), floatBranches[bName], tempTypeDeclare);
  } else if (type == "/i") {
    uintBranches[bName] = new unsigned (0);
    //myTree->Branch(bName.c_str(), uintBranches[bName]);
    myTree->Branch(bName.c_str(), uintBranches[bName], tempTypeDeclare);
  } else {
    cout << "Inside TTreeWrapper, Oopps, don't recognize type " << type << endl;
    assert (false);
  }

  return;
  
}

void TTreeWrapper::fillBranch (string bName, float val) {

  if (floatBranches.find(bName) != floatBranches.end() ){
    *(floatBranches[bName]) = val;
  } else {
    cout << "You asked to fill branch " << bName << " with a float, but I can't find that branch" << endl;
    assert (false);
  }

  return;
  
}

void TTreeWrapper::fillBranch (string bName, int val) {

  if (myVerboseFlag) cout << "Filling int branch " << bName << " with  " << val << endl;
  
  if (intBranches.find(bName) != intBranches.end() ){
    *(intBranches[bName]) = val;
  } else {
    cout << "You asked to fill branch " << bName << " with a int, but I can't find that branch" << endl;
    assert (false);
  }

  return;
  
}

void TTreeWrapper::fillBranch (string bName, unsigned val) {

  if (uintBranches.find(bName) != uintBranches.end() ){
    *(uintBranches[bName]) = val;
  } else {
    cout << "You asked to fill branch " << bName << " with a uint, but I can't find that branch" << endl;
    assert (false);
  }

  return;
  
}

void TTreeWrapper::initializeTree (TTree * inputTree) {

  // shallow copy only
  // we're not responsible for this, but we will modify it
  myTree = inputTree;  
  
}

bool TTreeWrapper::checkInit () {

  if (myTree)
    return true;

  return false;
  
}

void TTreeWrapper::resetBranches () {

  map<string, int*>::iterator iterIntBranch;
  map<string, float*>::iterator  iterFloatBranch;
  map<string, unsigned*>::iterator iterUintBranch;

  
  for (iterIntBranch = intBranches.begin();
       iterIntBranch != intBranches.end();
       iterIntBranch++){

    *(iterIntBranch->second) = dInt;
  }

  for (iterFloatBranch = floatBranches.begin();
       iterFloatBranch != floatBranches.end();
       iterFloatBranch++){

    *(iterFloatBranch->second) = dFloat;

  }

  for (iterUintBranch = uintBranches.begin();
       iterUintBranch != uintBranches.end();
       iterUintBranch++) {

    *(iterUintBranch->second) = 1234567;

  }

  return;
  
}

void TTreeWrapper::dumpBranches () {

  map<string, int*>::iterator iterIntBranch;
  map<string, float*>::iterator  iterFloatBranch;
  map<string, unsigned*>::iterator iterUintBranch;

  
  for (iterIntBranch = intBranches.begin();
       iterIntBranch != intBranches.end();
       iterIntBranch++){

    cout << iterIntBranch->first  << "   " <<  *(iterIntBranch->second) << endl;
  }

  for (iterFloatBranch = floatBranches.begin();
       iterFloatBranch != floatBranches.end();
       iterFloatBranch++){

    cout << iterFloatBranch->first << "   " << *(iterFloatBranch->second) << endl;

  }

  for (iterUintBranch = uintBranches.begin();
       iterUintBranch != uintBranches.end();
       iterUintBranch++) {

    cout << iterUintBranch->first << "    " << *(iterUintBranch->second) << endl;

  }

  return;
  
}



void TTreeWrapper::fillTree () {

  myTree->Fill();

}
