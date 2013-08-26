
#ifndef _GenericEventCollectionMember_h
#define _GenericEventCollectionMember_h

#include "ttHMultileptonAnalysis/TemplateMakers/interface/GenericCollectionMemberBase.h"



template <class branchDataType, class collectionType> 
class GenericEventCollectionMember: public GenericCollectionMemberBase<branchDataType, collectionType> {


public:  

  // there is already a version of this in the super class
  virtual void evaluate () ;

  
  GenericEventCollectionMember(Reflex::Type rType, string mem, string storePrefix,  branchDataType defval, int max = 6);

  

};

/////////////////// Call the superclass version of this

template <class branchDataType, class collectionType>
void GenericEventCollectionMember<branchDataType, collectionType>::evaluate () {

  // blocks is inherited, but requires a this statement
  // this calls the base class evaluate
  // and gives it the right collection
  GenericCollectionMemberBase<branchDataType, collectionType>::evaluate (this->blocks->eventCollection);
   
}

template <class branchDataType, class collectionType>
GenericEventCollectionMember<branchDataType, collectionType>::GenericEventCollectionMember(Reflex::Type rType, string mem, string storePrefix,  branchDataType defval, int max)
  : GenericCollectionMemberBase<branchDataType, collectionType>(rType, mem, storePrefix, defval, max)
{  
  // nothing specific for this class.
}


#endif
