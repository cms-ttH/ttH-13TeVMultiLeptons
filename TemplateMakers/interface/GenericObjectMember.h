
#ifndef _GenericObjectMember_h
#define _GenericObjectMember_h

#include "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BranchInfo.h"
#include "Reflex/Object.h"
#include "Reflex/Type.h"
#include "Reflex/Member.h"
#include "Reflex/Kernel.h"


template <class branchDataType> 
class GenericObjectMember: public KinematicVariable {


public:  
  BranchInfo<branchDataType> myVar;

  Reflex::Object inputObject;
  void * rInstance;

  Reflex::Type myClass;
  //Reflex::Object dynamicLookupBEANFileInterface;
  
  bool evaluatedThisEvent;

  string memberName;
  string storePrefix;


  branchDataType threshold;
  branchDataType resetVal;




  // at this time, no sensible default exists
  // GenericObjectMember();

  // constructor requires an instance of the class you want to fill
  GenericObjectMember(Reflex::Type rType, void * obj, string mem, string storePrefix,  branchDataType defval );

  void evaluate ();
  void attachToTree (TTree * inTree);
  void reset ();

  bool passCut ();

  void setCut (branchDataType cutVal);

  void print ();

  void listAvailableMembers ();

};

template <class branchDataType>
GenericObjectMember<branchDataType>::GenericObjectMember  ( Reflex::Type rType,  void * obj, string mem, string prefix,  branchDataType defval):
  myClass(rType),
  memberName(mem),
  storePrefix(prefix),
  resetVal(defval)
{

  // do this to make sure you get the inherited ones
  myClass.DataMemberSize(Reflex::INHERITEDMEMBERS_ALSO);
  inputObject = Reflex::Object(myClass, obj);
  
  myVar.branchName = (prefix+"_"+mem).c_str();  
  
  reset();
  
}

template <class branchDataType>
void GenericObjectMember<branchDataType>::reset  () {

  myVar.branchVal = resetVal;
  evaluatedThisEvent = false;

}

template <class branchDataType>
void GenericObjectMember<branchDataType>::attachToTree  (TTree * inTree) {

  inTree->Branch(myVar.branchName, &myVar.branchVal);

}

template <class branchDataType>
void GenericObjectMember<branchDataType>::evaluate () {

  if (evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  branchDataType * tempValPtr = (branchDataType*) (inputObject.Get(memberName).Address());
  
  myVar.branchVal = *tempValPtr;
  

}

template <class branchDataType>
bool GenericObjectMember<branchDataType>::passCut () {


  return true;

}

template <class branchDataType>
void GenericObjectMember<branchDataType>::setCut (branchDataType cutVal) {

  threshold = cutVal;
  
}

template <class branchDataType>
void GenericObjectMember<branchDataType>::print () {

  cout << "Printing GenericObjectMember .... " 
       << "   memberName " << memberName
       << "   storePrefix " << storePrefix
       << "   value  " << myVar.branchVal;
       

}

template <class branchDataType>
void GenericObjectMember<branchDataType>::listAvailableMembers () {

  
  cout << "Data member size  " << myClass.DataMemberSize() << endl;


    
  for (unsigned iMem = 0 ;
       iMem < myClass.DataMemberSize();
       iMem ++){

    cout << "---Member " << myClass.DataMemberAt(iMem).Name() << endl;
  }


  
}


#endif
