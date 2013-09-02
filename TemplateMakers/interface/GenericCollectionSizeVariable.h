
#ifndef _GenericCollectionSizeVariable_h
#define _GenericCollectionSizeVariable_h

#include "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BranchInfo.h"

template <class collectionType> 
class GenericCollectionSizeVariable: public KinematicVariable<int> {

public:
    collectionType ** collection;
    int collectionSize;
    int threshold;
    string branch_name;
    bool evaluatedThisEvent;
    int resetVal;

    GenericCollectionSizeVariable(string b_name, collectionType **coll);
    void reset();
    void evaluate();
    bool passCut();
    void setCut(int cut);
};

template<class collectionType>
GenericCollectionSizeVariable<collectionType>::GenericCollectionSizeVariable(string b_name, collectionType **coll): branch_name(b_name) {
    collection = coll;

    branches[branch_name] = BranchInfo<int>(branch_name);

    resetVal = KinematicVariableConstants::INT_INIT;
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

    branches[branch_name].branchVal = int((*collection)->size());

}

template<class collectionType>
void GenericCollectionSizeVariable<collectionType>::setCut(int cut) {
    threshold = cut;
}

template<class collectionType>
bool GenericCollectionSizeVariable<collectionType>::passCut() {
  evaluate();
  
  if (branches[branch_name].branchVal >= threshold)
    return true;
  return false;

}


#endif 
