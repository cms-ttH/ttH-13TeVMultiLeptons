#ifndef _GenericCollection_h
#include <functional>
#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"


//miniAOD
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/GenericParticle.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"
#include "DataFormats/PatCandidates/interface/Tau.h"

#define _GenericCollection_h

template <class collectionType>
class GenericCollection {

public:
  MiniAODHelper * mHelp;
  collectionType rawItems;
  collectionType items;
  collectionType * ptrToItems;
  std::function<bool (collectionType)> selectionFunction;

  GenericCollection(MiniAODHelper * mHelp);
  void initializeRawItems(edm::EventBase& event, string rawCollectionInstance);
  void initializeRawItems(const collectionType& collection);
  void initializeRawItems(std::initializer_list<collectionType> collections);
  void initializeRawItemsSortedByPt(edm::EventBase& event, string rawCollectionInstance);


  //  void initializeRawItemsSortedByPt(const collectionType& collection);

  //  template <typename functionType> void keepSelectedParticles(functionType selectionFunction);
  //  template <typename functionType, typename paramType> void keepSelectedParticles(functionType selectionFunction, paramType i);
  //  template <typename functionType, typename paramType1, typename paramType2> void keepSelectedParticles(functionType selectionFunction, paramType1 i, paramType2 j);
  //template <typename functionType, typename paramType1, typename paramType2, typename paramType3> void keepSelectedParticles(functionType selectionFunction, paramType1 i, paramType2 j, paramType3 k);
  void keepSelectedParticles(electronID::electronID& ID);
  void keepSelectedParticles(muonID::muonID& ID);
  //  void keepSelectedParticles(tauID::tauID& ID);
  void keepSelectedDifference(electronID::electronID& topID, electronID::electronID& bottomID);
  void keepSelectedDifference(muonID::muonID& topID, muonID::muonID& bottomID);
  void addUnion(std::initializer_list<collectionType> collections);
  //  void pushBack(std::initializer_list<BNelectronCollection> collections);
  //  void pushBack(std::initializer_list<BNmuonCollection> collections);
  //  void pushBack(std::initializer_list<BNleptonCollection> collections);
  //  void pushBack(const BNelectronCollection& electrons);
  //  void pushBack(const BNmuonCollection& muons);
  //  void pushBack(const BNleptonCollection& leptons);
  //  void resetAndPushBack(const BNelectronCollection& electrons);
  //  void resetAndPushBack(const BNmuonCollection& muons);
  //  void resetAndPushBack(const BNleptonCollection& leptons);
  //  void pushBackAndSort(const BNelectronCollection& electrons);
  //  void pushBackAndSort(const BNmuonCollection& muons);
  //  void pushBackAndSort(const BNleptonCollection& leptons);
  //  void cleanJets(const BNleptonCollection& leptons, const double drCut);
  //  void cleanJets_cProj(const BNleptonCollection& leptons, const double drCut);
  //  void correctRawJets(sysType::sysType jetSyst=sysType::NA);
  //  void keepSelectedJets(const double ptCut, const double etaCut, const jetID::jetID ID, const char csvWP);
  //  void getCorrectedMet(GenericCollection<BNjetCollection> jets, sysType::sysType jetSyst=sysType::NA);
  void reset();

private:
  collectionType topCollection;
  collectionType bottomCollection;
};

template<class collectionType>
GenericCollection<collectionType>::GenericCollection(MiniAODHelper * mHelp) : mHelp(mHelp) {
  reset();
}

template<class collectionType>
void GenericCollection<collectionType>::reset() {
  rawItems.clear();
  items.clear();
}

template<class collectionType>
void GenericCollection<collectionType>::initializeRawItems(edm::EventBase& event, string rawCollectionInstance) {
  reset();

  edm::InputTag tag(rawCollectionInstance);
  edm::Handle<collectionType> handle;
  event.getByLabel(tag, handle);
  rawItems = *handle;
  items = rawItems;
  //  cout << "items size = " << items.size() <<endl;
  ptrToItems = &items;
}

template<class collectionType>
void GenericCollection<collectionType>::initializeRawItems(const collectionType& collection) {
  reset();

  rawItems = collection;
  items = rawItems;

  ptrToItems = &items;
}

/* template<class collectionType> */
/* void GenericCollection<collectionType>::initializeRawItems(std::initializer_list<collectionType> collections) { */
/*   reset(); */

/*   addUnion(collections); */

/* } */

template<class collectionType>
void GenericCollection<collectionType>::initializeRawItemsSortedByPt(edm::EventBase& event, string rawCollectionInstance) {
  reset();
  initializeRawItems(event, rawCollectionInstance);

  items = mHelp->GetSortedByPt(items);

  ptrToItems = &items;
}

/* template<class collectionType> */
/* void GenericCollection<collectionType>::initializeRawItemsSortedByPt(const collectionType& collection) { */
/*   reset(); */

/*   rawItems = collection; */
/*   items = mHelp->GetSortedByPt(collection); */

/*   ptrToItems = &items; */
/* } */

/* template<class collectionType> */
/* template<typename functionType> */
/* void GenericCollection<collectionType>::keepSelectedParticles(functionType selectionFunction) { */
/*   collectionType selectedParticles; */

/*   for (auto& particle: items) { */
/*     if (selectionFunction(*(ptr(particle)))) selectedParticles.push_back(particle); */
/*   } */

/*   items = selectedParticles; */

/*   ptrToItems = &items; */
/* } */

/* template<class collectionType> */
/* template<typename functionType, typename paramType> */
/* void GenericCollection<collectionType>::keepSelectedParticles(functionType selectionFunction, paramType i) { */
/*   collectionType selectedParticles; */

/*   for (auto& particle: items) { */
/*     if (selectionFunction(*(ptr(particle)), i)) selectedParticles.push_back(particle); */
/*   } */

/*   items = selectedParticles; */

/*   ptrToItems = &items; */
/* } */

/* template<class collectionType> */
/* template<typename functionType, typename paramType1, typename paramType2> */
/* void GenericCollection<collectionType>::keepSelectedParticles(functionType selectionFunction, paramType1 i, paramType2 j) { */
/*   collectionType selectedParticles; */

/*   for (auto& particle: items) { */
/*     if (selectionFunction(*(ptr(particle)), i, j)) selectedParticles.push_back(particle); */
/*   } */

/*   items = selectedParticles; */

/*   ptrToItems = &items; */
/* } */

/* template<class collectionType> */
/* template<typename functionType, typename paramType1, typename paramType2, typename paramType3> */
/* void GenericCollection<collectionType>::keepSelectedParticles(functionType selectionFunction, paramType1 i, paramType2 j, paramType3 k) { */
/*   collectionType selectedParticles; */

/*   for (auto& particle: items) { */
/*     if (selectionFunction(*(ptr(particle)), i, j, k)) selectedParticles.push_back(particle); */
/*   } */

/*   items = selectedParticles; */

/*   ptrToItems = &items; */
/* } */

template<class collectionType>
void GenericCollection<collectionType>::keepSelectedParticles(electronID::electronID& ID) {

  items = mHelp->GetSelectedElectrons(rawItems,0., ID);

  ptrToItems = &items;
}

template<class collectionType>
void GenericCollection<collectionType>::keepSelectedParticles(muonID::muonID& ID) {

  //  items = mHelp->GetSelectedMuons(rawItems, ID);
  //  std::float minPt = 0.;
  
  items = mHelp->GetSelectedMuons(rawItems,0., ID);

  ptrToItems = &items;
}

/* template<class BNtauCollection> */
/* void GenericCollection<BNtauCollection>::keepSelectedParticles(tauID::tauID& ID) { */

/*   items = mHelp->GetSelectedTaus(rawItems, ID); */

/*   ptrToItems = &items; */
/* } */

template<class collectionType>
void GenericCollection<collectionType>::keepSelectedDifference(electronID::electronID& topID, electronID::electronID& bottomID) {
  topCollection = mHelp->GetSelectedElectrons(rawItems,0., topID);
  bottomCollection = mHelp->GetSelectedElectrons(rawItems,0., bottomID);
  
  items = mHelp->GetDifference(topCollection, bottomCollection);

  ptrToItems = &items;
}

template<class collectionType>
void GenericCollection<collectionType>::keepSelectedDifference(muonID::muonID& topID, muonID::muonID& bottomID) {
  topCollection = mHelp->GetSelectedMuons(rawItems,0., topID);
  bottomCollection = mHelp->GetSelectedMuons(rawItems,0., bottomID);

  items = mHelp->GetDifference(topCollection, bottomCollection);

  ptrToItems = &items;
}

template<class collectionType>
void GenericCollection<collectionType>::addUnion(std::initializer_list<collectionType> collections) {
  for (auto& collection: collections) {
    items = mHelp->GetUnion(items, collection);
  }
  ptrToItems = &items;
}

/* template<class BNleptonCollection> */
/* void GenericCollection<BNleptonCollection>::pushBack(std::initializer_list<BNelectronCollection> collections) { */
/*   for (auto& collection: collections) { */
/*     items.push_back(collection); */
/*   } */

/*   ptrToItems = &items; */
/* } */

/* template<class BNleptonCollection> */
/* void GenericCollection<BNleptonCollection>::pushBack(std::initializer_list<BNmuonCollection> collections) { */
/*   for (auto& collection: collections) { */
/*     items.push_back(collection); */
/*   } */

/*   ptrToItems = &items; */
/* } */

/* template<class BNcollection> */
/* void GenericCollection<BNcollection>::pushBack(std::initializer_list<BNleptonCollection> collections) { */
/*   for (auto& collection: collections) { */
/*     items.push_back(collection); */
/*   } */

/*   ptrToItems = &items; */
/* } */

/* template<class BNleptonCollection> */
/* void GenericCollection<BNleptonCollection>::pushBack(const BNelectronCollection& electrons) { */
/*     items.push_back(electrons); */

/*     ptrToItems = &items; */
/* } */

/* template<class BNleptonCollection> */
/* void GenericCollection<BNleptonCollection>::pushBack(const BNmuonCollection& muons) { */
/*   items.push_back(muons); */

/*   ptrToItems = &items; */
/* } */

/* template<class BNcollection> */
/* void GenericCollection<BNcollection>::pushBack(const BNleptonCollection& leptons) { */
/*   items.push_back(leptons); */

/*   ptrToItems = &items; */
/* } */

/* template<class BNleptonCollection> */
/* void GenericCollection<BNleptonCollection>::resetAndPushBack(const BNelectronCollection& electrons) { */
/*   reset(); */
/*   items.push_back(electrons); */

/*   ptrToItems = &items; */
/* } */

/* template<class BNleptonCollection> */
/* void GenericCollection<BNleptonCollection>::resetAndPushBack(const BNmuonCollection& muons) { */
/*   reset(); */
/*   items.push_back(muons); */

/*   ptrToItems = &items; */
/* } */

/* template<class BNcollection> */
/* void GenericCollection<BNcollection>::resetAndPushBack(const BNleptonCollection& leptons) { */
/*   reset(); */
/*   items.push_back(leptons); */

/*   ptrToItems = &items; */
/* } */

/* template<class BNleptonCollection> */
/* void GenericCollection<BNleptonCollection>::pushBackAndSort(const BNelectronCollection& electrons) { */
/*   items.push_back(electrons); */
/*   items.sort(); */

/*   ptrToItems = &items; */
/* } */

/* template<class BNleptonCollection> */
/* void GenericCollection<BNleptonCollection>::pushBackAndSort(const BNmuonCollection& muons) { */
/*   items.push_back(muons); */
/*   items.sort(); */

/*   ptrToItems = &items; */
/* } */

/* template<class BNcollection> */
/* void GenericCollection<BNcollection>::pushBackAndSort(const BNleptonCollection& leptons) { */
/*   items.push_back(leptons); */
/*   items.sort(); */

/*   ptrToItems = &items; */
/* } */

/* template<class BNjetCollection> */
/* void GenericCollection<BNjetCollection>::cleanJets(const BNleptonCollection& leptons, const double drCut = 0.5) { */
/*   rawItems = mHelp->GetCleanJets(rawItems, leptons, drCut); */
/*   ptrToItems = &items; */
/* } */

/* template<class BNjetCollection> */
/* void GenericCollection<BNjetCollection>::cleanJets_cProj(const BNleptonCollection& leptons, const double drCut = 0.5) { */
/*   rawItems = mHelp->GetCleanJets_cProj(rawItems, leptons, drCut); */
/*   ptrToItems = &items; */
/* } */

/* template<class BNjetCollection> */
/* void GenericCollection<BNjetCollection>::correctRawJets(sysType::sysType jetSyst) { */
/*   rawItems = mHelp->GetCorrectedJets(rawItems, jetSyst); */

/*   ptrToItems = &items; */
/* } */

/* template<class BNjetCollection> */
/* void GenericCollection<BNjetCollection>::keepSelectedJets(const double ptCut, const double etaCut, const jetID::jetID ID, const char csvWP) { */
/*   items = mHelp->GetSelectedJets(rawItems, ptCut, etaCut, ID, csvWP); */

/*   ptrToItems = &items; */
/* } */

/* template<class BNmetCollection> */
/* void GenericCollection<BNmetCollection>::getCorrectedMet(GenericCollection<BNjetCollection> jets, sysType::sysType jetSyst) { */
/*   items.clear(); */
/*   //take the GenericCollection instead of the BNjetCollection to ensure we don't accidentally use the corrected jets */
/*   BNmet tmpMet = mHelp->GetCorrectedMET(rawItems.at(0), jets.rawItems, jetSyst); */
/*   items.push_back(tmpMet); */

//  ptrToItems = &items;
//}

#endif
