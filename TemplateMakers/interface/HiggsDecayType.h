#ifndef _HiggsDecayType_h
#define _HiggsDecayType_h

#include  "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"

//
//  Loops over selected leptons and saves the lepMVA value for each.  For now I'm attaching to tree inside the constructor
//  instead of in a separate function-- I'm not sure we'd ever want this value without saving it. --AW
//

class HiggsDecayType: public KinematicVariable<int> {

public:
    HelperLeptonCore * myHelper;

    HiggsDecayType(HelperLeptonCore *in);
    void evaluate ();
  
};

HiggsDecayType::HiggsDecayType (HelperLeptonCore *in): myHelper(in) {
    this->resetVal = KinematicVariableConstants::INT_INIT;
    
    branches["higgs_decay_type"] = BranchInfo<int>("higgs_decay_type");
    branches["higgs_decay_type"].branchVal = this->resetVal;
}

void HiggsDecayType::evaluate () {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  //--------
  BEANhelper * beanHelper = &(myHelper->bHelp);
  if (!(myHelper->isData)) {
      branches["higgs_decay_type"].branchVal = beanHelper->GetHdecayType(*(this->blocks->mcParticleCollection));
  }
}



#endif 
