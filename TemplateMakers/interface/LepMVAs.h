#ifndef _LepMVA_h
#define _LepMVA_h

#include  "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"

//
//  Loops over selected leptons
//  saves the lepMVA value for each
//

class LepMVAs: public KinematicVariable<double> {

public:
    unsigned int maxLeptons;
    HelperLeptonCore * myHelper;

    LepMVAs(HelperLeptonCore *in, int max);
    void evaluate ();
  
};

LepMVAs::LepMVAs (HelperLeptonCore *in, int max): myHelper(in), maxLeptons(max) {
    this->resetVal = KinematicVariableConstants::DOUBLE_INIT;
    
    for (unsigned int i=0; i<maxLeptons; i++) {
        TString branchName = Form("lepton_by_pt_%d_lepMVA", i+1);
        branches[branchName] = BranchInfo<double>(branchName);
        branches[branchName].branchVal = this->resetVal;
    }
}

void LepMVAs::evaluate () {

  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  //--------

  BNleptonCollection * tightLeptons = this->blocks->leptonCollection;
  BEANhelper * beanHelper = &(myHelper->bHelp);
  TString branchName;

  unsigned loopMax = (unsigned (maxLeptons) < tightLeptons->size()) ? unsigned(maxLeptons) : tightLeptons->size();

  for (unsigned int i=0; i<loopMax; i++) {
      BNlepton * iLepton = tightLeptons->at(i);
      branchName = Form("lepton_by_pt_%d_lepMVA", i+1);

      if (iLepton->isElectron) {
          branches[branchName].branchVal = beanHelper->GetElectronLepMVA(*(BNelectron*)iLepton, this->blocks->jetsForLepMVACollection);
      } else {
          branches[branchName].branchVal = beanHelper->GetMuonLepMVA(*(BNmuon*)iLepton, this->blocks->jetsForLepMVACollection);
      }      
  }

}


#endif 
