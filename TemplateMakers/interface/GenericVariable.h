#ifndef _GenericVariable_h
#define _GenericVariable_h
#include <functional>

#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/KinematicVariable.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/BranchInfo.h"

template <class branchDataType, class collectionType, typename functionType>
class GenericVariable: public KinematicVariable<branchDataType> {

public:
  GenericVariable(collectionType **_collection, string&& branchName, branchDataType&& resVal, functionType _function);
  void evaluate();

  collectionType ** collection;
  string branchName;
  branchDataType branchValue;
  functionType valueFunction;


};

template<class branchDataType, class collectionType, typename functionType>
GenericVariable<branchDataType, collectionType, functionType>::GenericVariable(collectionType **_collection, string&& _branchName, branchDataType&& resVal, functionType _function):
  collection(_collection), branchName(_branchName), valueFunction(_function) {

  this->resetVal = resVal;
  this->branches[branchName] = BranchInfo<branchDataType>(branchName);
  this->branches[branchName].branchVal = this->resetVal;

  this->reset();
}

template<class branchDataType, class collectionType, typename functionType>
void GenericVariable<branchDataType, collectionType, functionType>::evaluate() {
  if (this->evaluatedThisEvent) return;
  this->evaluatedThisEvent = true;

  this->branches[branchName].branchVal = valueFunction(collection);

}

#endif
