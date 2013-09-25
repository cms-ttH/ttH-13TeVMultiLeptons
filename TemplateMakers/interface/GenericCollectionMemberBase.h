#ifndef _GenericCollectionMemberBase_h
#define _GenericCollectionMemberBase_h

#include "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BranchInfo.h"
#include "Reflex/Object.h"
#include "Reflex/Type.h"
#include "Reflex/Member.h"
#include "Reflex/Kernel.h"

template <class branchDataType, class collectionType> 
class GenericCollectionMemberBase: public KinematicVariable<branchDataType> {

public:
  // for this class, it makes sense to have the variables
  // in an order and to overide the usual usage
  // the collection is a vector, and you want your data
  // to mirror the collection
  // So override the virtual stuff
  
  vector< BranchInfo<branchDataType> > myVars;

  Reflex::Object inputObject;
  void * rInstance;
  Reflex::Type myClass;
  
  bool evaluatedThisEvent;
  string memberName;
  string storePrefix;
  branchDataType threshold;

  int maxObjInColl;

  // at this time, no sensible default exists
  // GenericCollectionMemberBase();

  // constructor requires an instance of the class you want to fill
  GenericCollectionMemberBase(Reflex::Type rType, string mem, string storePrefix,  branchDataType defval, int max = 1);


  // there is already a version of this in the super class
  virtual void evaluate () ;
  
  void attachToTree (TTree * inTree);
  void reset ();

  bool passCut ();

  void setCut (branchDataType cutVal);

  void print ();

  void listAvailableMembers ();

  // a different version of evaluate
  // can be used in several ways 
  void evaluate (collectionType * inputCol);
  void evaluateLeptonCollection (collectionType * inputCol);

};

template <class branchDataType, class collectionType>
GenericCollectionMemberBase<branchDataType, collectionType>::GenericCollectionMemberBase  ( Reflex::Type rType,  string mem, string prefix,  branchDataType defval, int max):
  myClass(rType),  
  memberName(mem),
  storePrefix(prefix),
  maxObjInColl(max)
{

  this->resetVal = defval;
  //cout << "Blocks is " << hex << blocks << dec << endl;
  
  // do this to make sure you get the inherited ones
  myClass.DataMemberSize(Reflex::INHERITEDMEMBERS_ALSO);

  if (myClass.Name()=="BNevent" || myClass.Name()=="BNmet") {
      TString bName = Form("%s_%s", prefix.c_str(), mem.c_str());
      myVars.push_back(BranchInfo<branchDataType>(bName));      
  } else {
      for (int iVar = 0; iVar  < maxObjInColl; iVar++) {
          TString bName = Form("%s_%d_%s", prefix.c_str(), iVar+1, mem.c_str());
          //cout << "branch name " << iVar << " will be " << bName << endl;
          myVars.push_back(BranchInfo<branchDataType>(bName));
      }
  }

  reset();
  
}

template <class branchDataType, class collectionType>
void GenericCollectionMemberBase<branchDataType, collectionType>::reset  () {

  for (unsigned iVar = 0; iVar < myVars.size(); iVar++){
    myVars[iVar].branchVal = this->resetVal;
  }
  evaluatedThisEvent = false;

}

template <class branchDataType, class collectionType>
void GenericCollectionMemberBase<branchDataType, collectionType>::attachToTree  (TTree * inTree) {

  for (unsigned iVar = 0; iVar < myVars.size(); iVar++){
    inTree->Branch(myVars[iVar].branchName, &myVars[iVar].branchVal);
  }
  
  

}

///////////////////  Generically, doesn't work

template <class branchDataType, class collectionType>
void GenericCollectionMemberBase<branchDataType, collectionType>::evaluate () {

  cout << "You're calling something that you're not supposed to." << endl
       << "Evaluate is not well-defined for the  GenericCollectionMemberBase class" << endl
       << "Sorry! " << endl;
  assert (false);
  
}


template <class branchDataType, class collectionType>
void GenericCollectionMemberBase<branchDataType, collectionType>::evaluate (collectionType * inputCol) {

  if (evaluatedThisEvent ) return;
  evaluatedThisEvent = true;

  unsigned numObjs = inputCol->size();
  unsigned loopMax = (unsigned(maxObjInColl) < numObjs) ? unsigned(maxObjInColl) : numObjs;

  
  for (unsigned iObj = 0; iObj < loopMax; iObj++ ){
    // cout << "BASE:    Inside loop over objects, this is object " << iObj << endl;
    // cout << "The pointer is " << &(inputCol->at(iObj)) << endl
    //      << "The pt is " << inputCol->at(iObj).pt << endl;
    
    
    Reflex::Object targetObject(myClass, &(inputCol->at(iObj)));
    
    branchDataType * tempValPtr = (branchDataType*) (targetObject.Get(memberName).Address());

    //cout << "Storing value " << *tempValPtr << endl;
    
    myVars[iObj].branchVal = *tempValPtr;
    
  }
}

template <class branchDataType, class collectionType>
void GenericCollectionMemberBase<branchDataType, collectionType>::evaluateLeptonCollection (collectionType * inputCol) {
  if (evaluatedThisEvent ) return;
  evaluatedThisEvent = true;

  unsigned numObjs = inputCol->size();
  unsigned loopMax = (unsigned(maxObjInColl) < numObjs) ? unsigned(maxObjInColl) : numObjs;
  for (unsigned iObj = 0; iObj < loopMax; iObj++ ){
      Reflex::Object targetObject(myClass, &(*(inputCol->at(iObj))));
    
      branchDataType * tempValPtr = (branchDataType*) (targetObject.Get(memberName).Address());
      myVars[iObj].branchVal = *tempValPtr;
  }
}

template <class branchDataType, class collectionType>
bool GenericCollectionMemberBase<branchDataType, collectionType>::passCut () {


  return true;

}

template <class branchDataType, class collectionType>
void GenericCollectionMemberBase<branchDataType, collectionType>::setCut (branchDataType cutVal) {

  threshold = cutVal;
  
}

template <class branchDataType, class collectionType>
void GenericCollectionMemberBase<branchDataType, collectionType>::print () {

  cout << "Printing GenericCollectionMemberBase .... " 
       << "   memberName " << memberName
       << "   storePrefix " << storePrefix
       << "   values:  ";

  for (unsigned iVar = 0; iVar < myVars.size(); iVar++){
    cout << " [ " << iVar << "] " <<  myVars[iVar].branchVal;
  }

  //cout << endl;
       

}

template <class branchDataType, class collectionType>
void GenericCollectionMemberBase<branchDataType, collectionType>::listAvailableMembers () {

  
  cout << "Data member size  " << myClass.DataMemberSize() << endl;


    
  for (unsigned iMem = 0 ;
       iMem < myClass.DataMemberSize();
       iMem ++){

    cout << "---Member " << myClass.DataMemberAt(iMem).Name() << endl;
  }


  
}


#endif
