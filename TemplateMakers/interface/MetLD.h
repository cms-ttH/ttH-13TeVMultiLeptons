#ifndef _MetLD_h
#define _MetLD_h

#include  "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"
#include  "ttHMultileptonAnalysis/TemplateMakers/interface/TwoObjectKinematic.h"

class MetLD: public KinematicVariable<double> {
  
public:
  MetLD(TwoObjectKinematic<BNleptonCollection,BNjetCollection> * input_myMHT,
        GenericCollectionMember<double, BNmetCollection> * input_myMet);
  void evaluate();
  
  TwoObjectKinematic<BNleptonCollection,BNjetCollection> * myMHT;
  GenericCollectionMember<double, BNmetCollection> * myMet;
};

MetLD::MetLD(TwoObjectKinematic<BNleptonCollection,BNjetCollection> * input_myMHT,
             GenericCollectionMember<double, BNmetCollection> * input_myMet):
  myMHT(input_myMHT), myMet(input_myMet) {
  
    branches["met_ld"] = BranchInfo<double>("met_ld");
    
}

void MetLD::evaluate() {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  //--------

  myMet->evaluate();
  myMHT->evaluate();

  float met = (*myMet).myVars[0].branchVal;
  float mht = (*myMHT).myVars[0].branchVal;

  float met_ld = met * 0.00397 + mht * 0.00265;

  branches["met_ld"].branchVal = met_ld;

}


#endif 
