#ifndef _DBCorrectedRelIsoDR04_h
#define _DBCorrectedRelIsoDR04_h

#include  "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"

//
//  Loops over selected leptons and saves the lepMVA value for each.  For now I'm attaching to tree inside the constructor
//  instead of in a separate function-- I'm not sure we'd ever want this value without saving it. --AW
//

class DBCorrectedRelIsoDR04s: public KinematicVariable<double> {

public:
    unsigned int maxLeptons;
    HelperLeptonCore * myHelper;

    DBCorrectedRelIsoDR04s(HelperLeptonCore *in, int max);
    void evaluate ();
  
};

DBCorrectedRelIsoDR04s::DBCorrectedRelIsoDR04s (HelperLeptonCore *in, int max): myHelper(in), maxLeptons(max) {
    this->resetVal = KinematicVariableConstants::DOUBLE_INIT;
    
    for (unsigned int i=0; i<maxLeptons; i++) {
        TString branchName = Form("preselected_leptons_by_pt_%d_DBCorrectedRelIsoDR04", i+1);
        branches[branchName] = BranchInfo<double>(branchName);
        branches[branchName].branchVal = this->resetVal;
    }
}

void DBCorrectedRelIsoDR04s::evaluate () {

  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  //--------

  BNleptonCollection * preselectedLeptons = this->blocks->mergedLeptonCollection;
  BEANhelper * beanHelper = &(myHelper->bHelp);
  TString branchName;

  unsigned loopMax = (unsigned (maxLeptons) < preselectedLeptons->size()) ? unsigned(maxLeptons) : preselectedLeptons->size();

  for (unsigned int i=0; i<loopMax; i++) {
      BNlepton * iLepton = preselectedLeptons->at(i);
      branchName = Form("preselected_leptons_by_pt_%d_DBCorrectedRelIsoDR04", i+1);
      branches[branchName].branchVal = beanHelper->GetDBCorrectedRelIsoDR04(*iLepton, 0.5);
  }
}



#endif 
