#ifndef _GenericCollectionSizeVariable2_h
#define _GenericCollectionSizeVariable2_h

#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/KinematicVariable.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/BranchInfo.h"

template <class collectionType> 
class GenericCollectionSizeVariable2: public KinematicVariable<int> {

public:
    collectionType * selectedCollection;
    int thresholdMin;
    int thresholdMax;
    string branch_name;
    bool evaluatedThisEvent;
    unsigned int resetVal;

    GenericCollectionSizeVariable2(collectionType * selColl, string _branch_name);
    void reset();
    void evaluate();
    bool passCut();
    void setCutMin(int cutMin);
    void setCutMax(int cutMax);
};

template<class collectionType>
GenericCollectionSizeVariable2<collectionType>::GenericCollectionSizeVariable2(collectionType * selColl, string _branch_name):
    selectedCollection(selColl),
    branch_name(_branch_name) {

    branches[branch_name] = BranchInfo<int>(branch_name);
    resetVal = KinematicVariableConstants::INT_INIT;

    //Default threshold values
    thresholdMin = 0;
    thresholdMax = 999999;

    reset();
}

template<class collectionType>
void GenericCollectionSizeVariable2<collectionType>::reset() {
  cout << "1"<< endl;
  branches[branch_name].branchVal = resetVal;
  cout << "2"<< endl;
  evaluatedThisEvent = false;
  cout << "3"<< endl;
}

template<class collectionType>
void GenericCollectionSizeVariable2<collectionType>::evaluate() {
  if (evaluatedThisEvent) return;
  evaluatedThisEvent = true;
  
  //  branches[branch_name].branchVal = (*selectedCollection)->size();
  branches[branch_name].branchVal = selectedCollection->size();
    
}

template<class collectionType>
void GenericCollectionSizeVariable2<collectionType>::setCutMin(int cutMin) {
    thresholdMin = cutMin;
}

template<class collectionType>
void GenericCollectionSizeVariable2<collectionType>::setCutMax(int cutMax) {
    thresholdMax = cutMax;
}

template<class collectionType>
bool GenericCollectionSizeVariable2<collectionType>::passCut() {
  evaluate();
  
  if (branches[branch_name].branchVal >= thresholdMin
      && branches[branch_name].branchVal <= thresholdMax)
    return true;
  return false;
  
}


#endif 
