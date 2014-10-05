#ifndef _GenPt_h
#define _GenPt_h

#include "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BranchInfo.h"
#include <typeinfo>

// //Anna's fix to make BNleptonCollection work just like any other collection
// //Template defined in BEAN/BEANMaker/BEANmaker/interface/BEANhelper.h
// template<typename T>
// T * ptr(T & obj) { return &obj; } //turn reference into pointer!
// template<typename T>
// T * ptr(T * obj) { return obj; } //obj is already pointer, return it!

//Takes two collections; may be the same, or different
template <class collectionType>
class GenPt: public KinematicVariable<double> {

public:
  //Store branch values so they are accessible to other classes
  vector<BranchInfo<double>> myVars;

  collectionType **collection; //first selected collection
  string bName;

  GenPt(collectionType **_collection, string bName);

  void evaluate();
  void reset();

};

template <class collectionType>
GenPt<collectionType>::GenPt(collectionType **_collection, string branchName):
  collection(_collection),
  bName(branchName)
       
{
  //TString bName = TString("topPt");
  branches[bName] = BranchInfo<double>(bName);

  this->resetVal = KinematicVariableConstants::DOUBLE_INIT;

}

template <class collectionType>
void GenPt<collectionType>::evaluate() {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;
  //TString bName = TString("topPt");
  double thisPairValue = KinematicVariableConstants::DOUBLE_INIT; //Values of each pair of objects

  for (unsigned int iObj1 = 0; iObj1 < (*collection)->size(); iObj1++) {

    thisPairValue = ((*collection)->at(iObj1)).pt();//.bDiscriminator("combinedSecondaryVertexBJetTags");
    
    // --Fill the branches--
    branches[bName].branchVal = thisPairValue;
    
  } //End loop over object1
  
  //Clean out values from last event
  myVars.clear();
  
  for (typename map<TString, BranchInfo<double>>::iterator iBranch = branches.begin();
       iBranch != branches.end(); iBranch++) {
    myVars.push_back(iBranch->second);
  }

}

template <class collectionType>
void GenPt<collectionType>::reset() {

  KinematicVariable::reset();

}
 

#endif
