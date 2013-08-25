
#ifndef _GenericCollectionMember_h
#define _GenericCollectionMember_h

#include "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BranchInfo.h"
#include "Reflex/Object.h"
#include "Reflex/Type.h"
#include "Reflex/Member.h"
#include "Reflex/Kernel.h"


template <class branchDataType, class collectionType> 
class GenericCollectionMember: public KinematicVariable {


public:  
  vector< BranchInfo<branchDataType> > myVars;

  Reflex::Object inputObject;
  void * rInstance;

  Reflex::Type myClass;
  
  
  bool evaluatedThisEvent;

  string memberName;
  string storePrefix;

  //string collectionName;

  branchDataType threshold;
  branchDataType resetVal;

  int maxObjInColl;


  // at this time, no sensible default exists
  // GenericCollectionMember();

  // constructor requires an instance of the class you want to fill
  GenericCollectionMember(Reflex::Type rType, string mem, string storePrefix,  branchDataType defval, int max = 1);

  void evaluate ();
  void attachToTree (TTree * inTree);
  void reset ();

  bool passCut ();

  void setCut (branchDataType cutVal);

  void print ();

  void listAvailableMembers ();

};

template <class branchDataType, class collectionType>
GenericCollectionMember<branchDataType, collectionType>::GenericCollectionMember  ( Reflex::Type rType,  string mem, string prefix,  branchDataType defval, int max):
  myClass(rType),  
  memberName(mem),
  storePrefix(prefix),
  resetVal(defval),
  maxObjInColl(max)
{

  // do this to make sure you get the inherited ones
  myClass.DataMemberSize(Reflex::INHERITEDMEMBERS_ALSO);  

  for (int iVar = 0; iVar  < maxObjInColl; iVar++) {
    TString bName = Form("%s_%d_%s", prefix.c_str(), iVar+1, mem.c_str());
    myVars.push_back(BranchInfo<branchDataType>(bName, ""));
  }
  reset();
  
}

template <class branchDataType, class collectionType>
void GenericCollectionMember<branchDataType, collectionType>::reset  () {

  for (unsigned iVar = 0; iVar < myVars.size(); iVar++){
    myVars[iVar].branchVal = resetVal;
  }
  evaluatedThisEvent = false;

}

template <class branchDataType, class collectionType>
void GenericCollectionMember<branchDataType, collectionType>::attachToTree  (TTree * inTree) {

  for (unsigned iVar = 0; iVar < myVars.size(); iVar++){
    inTree->Branch(myVars[iVar].branchName, &myVars[iVar].branchVal);
  }
  
  

}

///////////////////  Generically, doesn't work

template <class branchDataType, class collectionType>
void GenericCollectionMember<branchDataType, collectionType>::evaluate () {

  cout << "You're calling something that you're not supposed to." << endl
       << "GenericCollection member only works for a few kinds of classes" << endl
       << "Sorry! " << endl;
  assert (false);
  
}


//////////////////  Specification: muon collection

template <class branchDataType>
void GenericCollectionMember<branchDataType, BNmuonCollection>::evaluate () {

  unsigned nMuons = blocks->muonCollection->size();
  unsigned loopMax = (unsigned (maxObjInColl) < nMuons ) ? unsigned(maxObjInColl) : nMuons;

  for (unsigned iVar = 0; iVar < loopMax; iVar++){

    Reflex::Object tmpObj = Reflex::Object(myClass, &blocks->muonCollection->at(iVar));
    branchDataType* tempValPtr = (branchDataType*) (tmpObj.Get(memberName).Address())
    myVars[iVar].branchVal = *tempValPtr;
  }

  
}

    
    
    
template <class branchDataType, class collectionType>
bool GenericCollectionMember<branchDataType, collectionType>::passCut () {


  return true;

}

template <class branchDataType, class collectionType>
void GenericCollectionMember<branchDataType, collectionType>::setCut (branchDataType cutVal) {

  threshold = cutVal;
  
}

template <class branchDataType, class collectionType>
void GenericCollectionMember<branchDataType, collectionType>::print () {

  cout << "Printing GenericCollectionMember .... " 
       << "   memberName " << memberName
       << "   storePrefix " << storePrefix
       << "   values:  ";

  for (unsigned iVar = 0; iVar < myVars.size(); iVar++){
    cout << "[ " << iVar << "] " <<  myVars[iVar].branchVal;
  }

  //cout << endl;
       

}

template <class branchDataType, class collectionType>
void GenericCollectionMember<branchDataType, collectionType>::listAvailableMembers () {

  
  cout << "Data member size  " << myClass.DataMemberSize() << endl;


    
  for (unsigned iMem = 0 ;
       iMem < myClass.DataMemberSize();
       iMem ++){

    cout << "---Member " << myClass.DataMemberAt(iMem).Name() << endl;
  }


  
}


#endif
