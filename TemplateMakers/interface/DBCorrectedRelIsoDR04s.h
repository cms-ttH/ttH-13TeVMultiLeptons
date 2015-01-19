#ifndef _DBCorrectedRelIsoDR04_h
#define _DBCorrectedRelIsoDR04_h

#include  "ttH-13TeVMultiLeptons/TemplateMakers/interface/KinematicVariable.h"

//
//  Loops over selected leptons and saves the lepMVA value for each.  For now I'm attaching to tree inside the constructor
//  instead of in a separate function-- I'm not sure we'd ever want this value without saving it. --AW
//

class DBCorrectedRelIsoDR04s: public KinematicVariable<double> {
  
public:
  HelperLeptonCore * myHelper;
  BNleptonCollection **leptonsPtr;
  string label;
  unsigned int minLeptons;
  unsigned int maxLeptons;
  
  DBCorrectedRelIsoDR04s(HelperLeptonCore *in, BNleptonCollection **_leptonsPtr,
                         string _label, int min, int max);
  void evaluate ();
  
};

DBCorrectedRelIsoDR04s::DBCorrectedRelIsoDR04s (HelperLeptonCore *in, BNleptonCollection **_leptonsPtr,
                                                string _label, int min, int max):
  myHelper(in), leptonsPtr(_leptonsPtr), label(_label), minLeptons(min), maxLeptons(max) {
    this->resetVal = KinematicVariableConstants::DOUBLE_INIT;
    
    for (unsigned int i=0; (i+1)>=minLeptons && i<maxLeptons; i++) {
      TString branchName = Form("%s_%d_DBCorrectedRelIsoDR04", label.c_str(), i+1);
      branches[branchName] = BranchInfo<double>(branchName);
      branches[branchName].branchVal = this->resetVal;
    }
}

void DBCorrectedRelIsoDR04s::evaluate () {
  
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;
  
  //--------

  BNleptonCollection * leptons = *leptonsPtr;
  BEANhelper * beanHelper = &(myHelper->bHelp);
  TString branchName;
  
  for (unsigned int i=0; (i+1)>=minLeptons && i<maxLeptons && i<leptons->size(); i++) {
    BNlepton * iLepton = leptons->at(i);
    branchName = Form("%s_%d_DBCorrectedRelIsoDR04", label.c_str(), i+1);
    branches[branchName].branchVal = beanHelper->GetDBCorrectedRelIsoDR04(*iLepton, 0.5);
  }
}



#endif 
