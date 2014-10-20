#ifndef _SingleObjectVariable_h
#define _SingleObjectVariable_h

#include "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BranchInfo.h"
#include <typeinfo>

//Takes two collections; may be the same, or different
template <class value>
class SingleObjectVariable: public KinematicVariable<double> {

public:
  //Store branch values so they are accessible to other classes
  vector<BranchInfo<double>> myVars;

  value *objectValue; 
  string bName;
  SingleObjectVariable(value *objectValue, string bName);
  void evaluate();
  void reset();

};

template <class value>
SingleObjectVariable<value>::SingleObjectVariable(value *object_value, string branchName):
objectValue(object_value),
  bName(branchName)
{

  branches[bName] = BranchInfo<double>(bName);

  this->resetVal = KinematicVariableConstants::DOUBLE_INIT;

}

template <class value>
void SingleObjectVariable<value>::evaluate() {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;
  branches[bName].branchVal = *objectValue;
  //Clean out values from last event
  myVars.clear();
  
  for (typename map<TString, BranchInfo<double>>::iterator iBranch = branches.begin();
       iBranch != branches.end(); iBranch++) {
    myVars.push_back(iBranch->second);
  }
  
}

template <class value>
void SingleObjectVariable<value>::reset() {

  KinematicVariable::reset();

}
 

#endif
