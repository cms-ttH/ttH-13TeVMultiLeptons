#ifndef _MetLD_h
#define _MetLD_h

#include  "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"

class MetLD: public KinematicVariable<double> {

public:
    MetLD(MHT * mht, GenericCollectionMember<double, BNmetCollection> * met);
    void evaluate();

    MHT * myMht;
    GenericCollectionMember<double, BNmetCollection> * myMet;
};

MetLD::MetLD(MHT * mht, GenericCollectionMember<double, BNmetCollection> * met): myMht(mht), myMet(met) {
    branches["met_ld"] = BranchInfo<double>("met_ld");
}

void MetLD::evaluate() {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  //--------

  myMet->evaluate();
  myMht->evaluate();

  float met = (*myMet).myVars[0].branchVal;
  float mht = myMht->mht;

  float met_ld = met * 0.00397 + mht * 0.00265;

  branches["met_ld"].branchVal = met_ld;

}


#endif 
