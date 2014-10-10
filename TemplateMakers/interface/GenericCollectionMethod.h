#ifndef _GenericCollectionMethod_h
#define _GenericCollectionMethod_h

#include <functional>
#include <typeinfo>

#include "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BranchInfo.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/Lepton.h"

#include "Reflex/Object.h"
#include "Reflex/Type.h"
#include "Reflex/Member.h"
#include "Reflex/Kernel.h"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/GenericParticle.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/Lepton.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

template <class branchDataType, class collectionType>
class GenericCollectionMethod: public KinematicVariable<branchDataType> {
public:
  vector< BranchInfo<branchDataType> > myVars;
  Reflex::Type myClass;
  collectionType ** selectedCollection;
  string methodName;
  string methodParam;
  string storePrefix;
  int maxObjInColl;
  bool evaluatedThisEvent;
  std::function<bool (vector< BranchInfo<branchDataType> > )> cutFunction;
  std::vector<void*> args;

  GenericCollectionMethod(Reflex::Type myClass_, collectionType **selectedCollection_, string methodName_, string methodParam_, string storePrefix_, branchDataType defaultVal_, int maxObjInColl_ = 1);
  void reset ();
  void attachToTree (TTree * inTree);
  virtual void evaluate ();// there is already a version of this in the super class
  bool passCut ();
  template <typename functionType> void setCut (functionType function);

};

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
template <class branchDataType, class collectionType>
GenericCollectionMethod<branchDataType, collectionType>::GenericCollectionMethod (Reflex::Type myClass_, collectionType **selectedCollection_, string methodName_, string methodParam_, string storePrefix_, branchDataType defaultVal_, int maxObjInColl_):
  myClass(myClass_),
  selectedCollection(selectedCollection_),
  methodName(methodName_),
  methodParam(methodParam_),
  storePrefix(storePrefix_),
  maxObjInColl(maxObjInColl_)
{
  this->resetVal = defaultVal_;

  args.push_back(&methodParam);

  // do this to make sure you get the inherited ones
  myClass.DataMemberSize(Reflex::INHERITEDMEMBERS_ALSO);

  for (int iVar = 0; iVar  < maxObjInColl; iVar++) {
    TString bName = Form("%s_%d_%s", storePrefix.c_str(), iVar+1, methodName.c_str());
    myVars.push_back(BranchInfo<branchDataType>(bName));
    }

  reset();
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
template <class branchDataType, class collectionType>
void GenericCollectionMethod<branchDataType, collectionType>::reset () {
  for (unsigned iVar = 0; iVar < myVars.size(); iVar++){
    myVars[iVar].branchVal = this->resetVal;
  }
  evaluatedThisEvent = false;
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
template <class branchDataType, class collectionType>
void GenericCollectionMethod<branchDataType, collectionType>::attachToTree (TTree * inTree) {
  for (unsigned iVar = 0; iVar < myVars.size(); iVar++){
    inTree->Branch(myVars[iVar].branchName, &myVars[iVar].branchVal);
  }
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
template <class branchDataType, class collectionType>
void GenericCollectionMethod<branchDataType, collectionType>::evaluate () {
  if (evaluatedThisEvent ) return;
  evaluatedThisEvent = true;

  unsigned numObjs = (*selectedCollection)->size();
  unsigned loopMax = (unsigned(maxObjInColl) < numObjs) ? unsigned(maxObjInColl) : numObjs;
  for (unsigned iObj = 0; iObj < loopMax; iObj++ ){
      Reflex::Object object(myClass, &(*selectedCollection)->at(iObj));

      branchDataType * tempVal = new branchDataType();
      object.Invoke<branchDataType>(methodName, *tempVal, args);

      myVars[iObj].branchVal = *tempVal;
  }
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
template <class branchDataType, class collectionType>
bool GenericCollectionMethod<branchDataType, collectionType>::passCut () {
  return cutFunction(myVars);
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
template <class branchDataType, class collectionType>
template <typename functionType>
void GenericCollectionMethod<branchDataType, collectionType>::setCut (functionType function) {
  cutFunction = function;
}

#endif

