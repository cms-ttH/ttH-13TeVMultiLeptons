
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
  BranchInfo<branchDataType> myVar;

  Reflex::Object inputObject;
  void * rInstance;

  Reflex::Type myClass;
  Reflex::Object dynamicLookupBEANFileInterface;
  
  bool evaluatedThisEvent;

  string memberName;
  string storePrefix;

  string collectionName;

  branchDataType threshold;
  branchDataType resetVal;

  bool eachObjInColl;


  // at this time, no sensible default exists
  // GenericCollectionMember();

  // constructor requires an instance of the class you want to fill
  GenericCollectionMember(Reflex::Type rType, string mem, string storePrefix, string collName, branchDataType defval, bool allObjs = false);

  void evaluate ();
  void attachToTree (TTree * inTree);
  void reset ();

  bool passCut ();

  void setCut (branchDataType cutVal);

  void print ();

  void listAvailableMembers ();

};

template <class branchDataType, class collectionType>
GenericCollectionMember<branchDataType, collectionType>::GenericCollectionMember  ( Reflex::Type rType,  string mem, string prefix, string collName, branchDataType defval, bool allObjs):
  myClass(rType),
  dynamicLookupBEANFileInterface(Reflex::Type::ByName("BEANFileInterface"), blocks),
  memberName(mem),
  storePrefix(prefix),
  collectionName(collName),
  resetVal(defval),
  eachObjInColl(allObjs)
{

  // do this to make sure you get the inherited ones
  myClass.DataMemberSize(Reflex::INHERITEDMEMBERS_ALSO);  
  
  myVar.branchName = (prefix+"_"+mem).c_str();  
  
  reset();
  
}

template <class branchDataType, class collectionType>
void GenericCollectionMember<branchDataType, collectionType>::reset  () {

  myVar.branchVal = resetVal;
  evaluatedThisEvent = false;

}

template <class branchDataType, class collectionType>
void GenericCollectionMember<branchDataType, collectionType>::attachToTree  (TTree * inTree) {

  inTree->Branch(myVar.branchName, &myVar.branchVal);

}

template <class branchDataType, class collectionType>
void GenericCollectionMember<branchDataType, collectionType>::evaluate () {

  if (evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  Reflex::Object tmpVectorPtr = dynamicLookupBEANFileInterface.Get(collectionName);
  collectionType** collectionPtr = static_cast<collectionType**> (tmpVectorPtr.Address());

  if (collectionPtr == 0) {
    cout << "..null pointer detected" << endl;
  }

  cout << "De-referencing collection to see its size " << endl;
  unsigned collSize = (*collectionPtr)->size(); // double de-reference

  cout << "Coll size " << collSize << endl;

  if (collSize  > 0) {
    void * objInColl = &((*collectionPtr)->at(0));
    cout << "Is there a pointer to the object?" << hex << objInColl << dec << endl;
    Reflex::Object targetObject(myClass, objInColl );
    branchDataType * tempValPtr = (branchDataType*) (targetObject.Get(memberName).Address());

    myVar.branchVal = *tempValPtr;
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
       << "   value  " << myVar.branchVal;
       

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
