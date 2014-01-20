#ifndef _GenericVariable_h
#define _GenericVariable_h

#include "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BranchInfo.h"

template <class branchDataType>
class GenericVariable: public KinematicVariable<branchDataType> {

public:
  string branchName;
  branchDataType branchValue;

  GenericVariable(branchDataType& bValue, string bName, branchDataType resVal);
  void evaluate ();
};

template <class branchDataType>
GenericVariable<branchDataType>::GenericVariable(branchDataType& bValue, string bName, branchDataType resVal):
  branchName(bName), branchValue(bValue) {

  this->resetVal = resVal;
  this->branches[bName] = BranchInfo<branchDataType>(bName);

  this->reset();
}

template <class branchDataType>
void GenericVariable<branchDataType>::evaluate() {
  if (this->evaluatedThisEvent) return;
  this->evaluatedThisEvent = true;

  this->branches[branchName].branchVal = branchValue;
}

#endif
