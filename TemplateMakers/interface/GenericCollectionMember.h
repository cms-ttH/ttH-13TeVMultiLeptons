
#ifndef _GenericCollectionMember_h
#define _GenericCollectionMember_h

#include "ttHMultileptonAnalysis/TemplateMakers/interface/GenericCollectionMemberBase.h"


template <class branchDataType, class collectionType> 
class GenericCollectionMember: public GenericCollectionMemberBase<branchDataType, collectionType> {

public:
    collectionType ** selectedCollection;
    GenericCollectionMember(Reflex::Type rType, collectionType **selectedCollection, string mem, string storePrefix,  branchDataType defval, int max=1);
    virtual void evaluate () ;


};

/////////////////// Call the superclass version of this

template <class branchDataType, class collectionType>
GenericCollectionMember<branchDataType, collectionType>::GenericCollectionMember(Reflex::Type rType, collectionType **selCollection, string mem, string storePrefix,  branchDataType defval, int max)
  : GenericCollectionMemberBase<branchDataType, collectionType>(rType, mem, storePrefix, defval, max) {
    selectedCollection = selCollection;
}

template <class branchDataType, class collectionType>
void GenericCollectionMember<branchDataType, collectionType>::evaluate () {
    GenericCollectionMemberBase<branchDataType, collectionType>::evaluate (*selectedCollection);

}



#endif
