#ifndef _GenericCollectionSizeVariable_h
#define _GenericCollectionSizeVariable_h

#include "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BranchInfo.h"

template <class collectionType> 
class GenericCollectionSizeVariable: public KinematicVariable<int> {

public:
    collectionType ** selectedCollection;
    int thresholdMin;
    int thresholdMax;
    string branch_name;
    bool evaluatedThisEvent;
    unsigned int resetVal;

    GenericCollectionSizeVariable(collectionType ** selColl, string input_branch_name);
    void reset();
    void evaluate();
    bool passCut();
    void setCutMin(int cutMin);
    void setCutMax(int cutMax);
};

template<class collectionType>
GenericCollectionSizeVariable<collectionType>::GenericCollectionSizeVariable(collectionType ** selColl, string input_branch_name):
    selectedCollection(selColl),
    branch_name(input_branch_name) {

    branches[branch_name] = BranchInfo<int>(branch_name);
    resetVal = KinematicVariableConstants::INT_INIT;

    //Default threshold values
    thresholdMin = 0;
    thresholdMax = 999999;

    reset();
}

template<class collectionType>
void GenericCollectionSizeVariable<collectionType>::reset() {
  branches[branch_name].branchVal = resetVal;
  evaluatedThisEvent = false;
}

template<class collectionType>
void GenericCollectionSizeVariable<collectionType>::evaluate() {
  if (evaluatedThisEvent) return;
  evaluatedThisEvent = true;
  
  branches[branch_name].branchVal = (*selectedCollection)->size();
    
}

template<class collectionType>
void GenericCollectionSizeVariable<collectionType>::setCutMin(int cutMin) {
    thresholdMin = cutMin;
}

template<class collectionType>
void GenericCollectionSizeVariable<collectionType>::setCutMax(int cutMax) {
    thresholdMax = cutMax;
}

template<class collectionType>
bool GenericCollectionSizeVariable<collectionType>::passCut() {
  evaluate();
  
  if (branches[branch_name].branchVal >= thresholdMin
      && branches[branch_name].branchVal <= thresholdMax)
    return true;
  return false;
  
}


#endif 
