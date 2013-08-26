
#ifndef _GenericMuonCollectionMember_h
#define _GenericMuonCollectionMember_h

#include "ttHMultileptonAnalysis/TemplateMakers/interface/GenericCollectionMemberBase.h"



template <class branchDataType, class collectionType> 
class GenericMuonCollectionMember: public GenericCollectionMemberBase<branchDataType, collectionType> {


public:  

  // there is already a version of this in the super class
  virtual void evaluate () ;

  
  GenericMuonCollectionMember(Reflex::Type rType, string mem, string storePrefix,  branchDataType defval, int max = 1);

  

};

/////////////////// Call the superclass version of this

template <class branchDataType, class collectionType>
void GenericMuonCollectionMember<branchDataType, collectionType>::evaluate () {

  // blocks is inherited
  GenericCollectionMemberBase<branchDataType, collectionType>::evaluate (this->blocks->muonCollection);
   
}

template <class branchDataType, class collectionType>
GenericMuonCollectionMember<branchDataType, collectionType>::GenericMuonCollectionMember(Reflex::Type rType, string mem, string storePrefix,  branchDataType defval, int max)
  : GenericCollectionMemberBase<branchDataType, collectionType>(rType, mem, storePrefix, defval, max)
{  
  // nothing specific for this class.
}


#endif
