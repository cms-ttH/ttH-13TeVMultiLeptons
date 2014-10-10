#ifndef _GenericCollectionMember_h
#define _GenericCollectionMember_h

#include <functional>
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

// //Anna's fix to make BNleptonCollection work just like any other collection
// //Template defined in BEAN/BEANMaker/BEANmaker/interface/BEANhelper.h
// template<typename T>
// T * ptr(T & obj) { return &obj; } //turn reference into pointer!
// template<typename T>
// T * ptr(T * obj) { return obj; } //obj is already pointer, return it!

template <class branchDataType, class collectionType>
class GenericCollectionMember: public KinematicVariable<branchDataType> {
public:
  vector< BranchInfo<branchDataType> > myVars;
  collectionType ** selectedCollection;
  Reflex::Object inputObject;
  Reflex::Type myClass;
  bool evaluatedThisEvent;
  string memberName;
  string storePrefix;
  int maxObjInColl;
  std::function<bool (vector< BranchInfo<branchDataType> > )> cutFunction;

  GenericCollectionMember(Reflex::Type rType, collectionType **selColl, string mem, string storePrefix,  branchDataType defval, int max = 1);
  void reset ();
  void attachToTree (TTree * inTree);
  virtual void evaluate ();// there is already a version of this in the super class
  bool passCut ();
  template <typename functionType> void setCut (functionType function);
  void print ();
  void listAvailableMembers ();
  bool checkForMember (Reflex::Type myType);
  //Reflex::Object getBaseObject (Reflex::Object& object, int index);
};


//////////////////////////////////////////////////////////////////
////
////
////
//////////////////////////////////////////////////////////////////


template <class branchDataType, class collectionType>
GenericCollectionMember<branchDataType, collectionType>::GenericCollectionMember (Reflex::Type rType, collectionType **selColl, string mem, string prefix,  branchDataType defval, int max):
  myClass(rType),
  memberName(mem),
  storePrefix(prefix),
  maxObjInColl(max)
{
  selectedCollection = selColl;
  this->resetVal = defval;
  //cout << "Blocks is " << hex << blocks << dec << endl;
  //cout <<"myclass = " << myClass.Name() << endl;
  // do this to make sure you get the inherited ones
  myClass.DataMemberSize(Reflex::INHERITEDMEMBERS_ALSO);
  
  string st = mem.substr(0,mem.size()-1);

  for (int iVar = 0; iVar  < maxObjInColl; iVar++) {
    TString bName = Form("%s_%d", prefix.c_str(), iVar+1);//, mem.c_str());
    myVars.push_back(BranchInfo<branchDataType>(bName));
    }

  reset();
}

//////////////////////////////////////////////////////////////////
////
////
////
//////////////////////////////////////////////////////////////////

template <class branchDataType, class collectionType>
void GenericCollectionMember<branchDataType, collectionType>::reset () {
  for (unsigned iVar = 0; iVar < myVars.size(); iVar++){
    myVars[iVar].branchVal = this->resetVal;
  }
  evaluatedThisEvent = false;
}
//////////////////////////////////////////////////////////////////
////
////
////
//////////////////////////////////////////////////////////////////
template <class branchDataType, class collectionType>
void GenericCollectionMember<branchDataType, collectionType>::attachToTree  (TTree * inTree) {
  for (unsigned iVar = 0; iVar < myVars.size(); iVar++){
    inTree->Branch(myVars[iVar].branchName, &myVars[iVar].branchVal);
  }
}
//////////////////////////////////////////////////////////////////
////
////
////
//////////////////////////////////////////////////////////////////
template <class branchDataType, class collectionType>
void GenericCollectionMember<branchDataType, collectionType>::evaluate () {
  if (evaluatedThisEvent ) return;
  evaluatedThisEvent = true;

  unsigned numObjs = (*selectedCollection)->size();
  unsigned loopMax = (unsigned(maxObjInColl) < numObjs) ? unsigned(maxObjInColl) : numObjs;
  for (unsigned iObj = 0; iObj < loopMax; iObj++ ){
    Reflex::Object object(myClass, &(*selectedCollection)->at(iObj));//ptr
    //listAvailableMembers();
    //print();
    if (checkForMember(object.TypeOf())) {
      branchDataType * tempValPtr = (branchDataType*) (object.Address());
      myVars[iObj].branchVal = *tempValPtr;
      cout << "branch val" << myVars[iObj].branchVal << endl;
    }
  }
}
//////////////////////////////////////////////////////////////////
////
////
////
//////////////////////////////////////////////////////////////////
template <class branchDataType, class collectionType>
bool GenericCollectionMember<branchDataType, collectionType>::passCut () {
  return cutFunction(myVars);
}
//////////////////////////////////////////////////////////////////
////
////
////
//////////////////////////////////////////////////////////////////
template <class branchDataType, class collectionType>
template <typename functionType>
void GenericCollectionMember<branchDataType, collectionType>::setCut (functionType function) {
  cutFunction = function;
}
//////////////////////////////////////////////////////////////////
////
////
////
//////////////////////////////////////////////////////////////////
template <class branchDataType, class collectionType>
void GenericCollectionMember<branchDataType, collectionType>::print () {
  cout << "Printing GenericCollectionMember .... "
       << "   memberName " << memberName
       << "   storePrefix " << storePrefix
       << "   values:  ";

  for (unsigned iVar = 0; iVar < myVars.size(); iVar++){
    cout << " [ " << iVar << "] " <<  myVars[iVar].branchVal;
  }
  cout << endl;
}
//////////////////////////////////////////////////////////////////
////
////
////
//////////////////////////////////////////////////////////////////
template <class branchDataType, class collectionType>
void GenericCollectionMember<branchDataType, collectionType>::listAvailableMembers () {
  cout << "Data member size  " << myClass.DataMemberSize() << endl;
  cout << "Data member name  " << myClass.Name() << endl;

  for (unsigned iMem = 0;
       iMem < myClass.DataMemberSize();
       iMem ++){

    cout << "---Member " << myClass.DataMemberAt(iMem).Name() << endl;
  }
}

//If the object is a BNlepton, figure out if it's a muon (electron) and return a new muon (electron) object
//Otherwise, just return the object
/* template <class branchDataType, class collectionType> */
/* Reflex::Object GenericCollectionMember<branchDataType, collectionType>::getBaseObject (R { */
/*   //if (myClass.Name()=="BNlepton") { */
/*   //Reflex::Type leptonType; */
/*   //int * isMuon = (int*) (object.Get("isMuon").Address()); */
/*   //if (*isMuon==1) { */
/*   // leptonType = Reflex::Type::ByName("BNmuon"); */
/*   //} else { */
/*   // leptonType = Reflex::Type::ByName("BNelectron"); */
/*   //} */
/*   Reflex::Object baseObject(leptonType, ptr((*selectedCollection)->at(index))); */
/*   object = baseObject; */

/*   return object; */
/* } */

template <class branchDataType, class collectionType>
bool GenericCollectionMember<branchDataType, collectionType>::checkForMember (Reflex::Type classToCheck) {
  bool hasMember = false;
  //cout << "DATA MEMBER SIZE " << classToCheck.DataMemberSize() << endl;
  for (unsigned iMem = 0; iMem < classToCheck.DataMemberSize(); iMem ++) {

    if (classToCheck.DataMemberAt(iMem).Name() == memberName) hasMember = true;
  }
  return hasMember;
}

#endif
