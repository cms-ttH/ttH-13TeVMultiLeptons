#ifndef _GenericCollection_h
#include <functional>
#include "BEAN/BEANmaker/interface/BEANhelper.h"

#define _GenericCollection_h

template <class collectionType>
class GenericCollection {

public:
  BEANhelper * bHelp;
  collectionType rawItems;
  collectionType items;
  collectionType * ptrToItems;
  std::function<bool (collectionType)> selectionFunction;

  GenericCollection(BEANhelper * bHelp);
  void initializeRawItems(edm::EventBase& event, string rawCollectionLabel, string rawCollectionInstance);
  void initializeRawItems(const collectionType& collection);
  void initializeRawItems(std::initializer_list<collectionType> collections);
  void initializeRawItemsSortedByPt(edm::EventBase& event, string rawCollectionLabel, string rawCollectionInstance);
  void initializeRawItemsSortedByPt(const collectionType& collection);
  void initializeRawItemsSortedByCSV(edm::EventBase& event, string rawCollectionLabel, string rawCollectionInstance);
  void initializeRawItemsSortedByCSV(const collectionType& collection);
  template <typename functionType> void keepSelectedParticles(functionType selectionFunction);
  template <typename functionType, typename paramType> void keepSelectedParticles(functionType selectionFunction, paramType i);
  template <typename functionType, typename paramType1, typename paramType2> void keepSelectedParticles(functionType selectionFunction, paramType1 i, paramType2 j);
  template <typename functionType, typename paramType1, typename paramType2, typename paramType3> void keepSelectedParticles(functionType selectionFunction, paramType1 i, paramType2 j, paramType3 k);
  void keepSelectedParticles(electronID::electronID& ID);
  void keepSelectedParticles(muonID::muonID& ID);
  void keepSelectedParticles(tauID::tauID& ID);
  void keepSelectedDifference(electronID::electronID& topID, electronID::electronID& bottomID);
  void keepSelectedDifference(muonID::muonID& topID, muonID::muonID& bottomID);
  void addUnion(std::initializer_list<collectionType> collections);
  void pushBack(std::initializer_list<BNelectronCollection> collections);
  void pushBack(std::initializer_list<BNmuonCollection> collections);
  void pushBack(std::initializer_list<BNleptonCollection> collections);
  void pushBack(const BNelectronCollection& electrons);
  void pushBack(const BNmuonCollection& muons);
  void pushBack(const BNleptonCollection& leptons);
  void resetAndPushBack(const BNelectronCollection& electrons);
  void resetAndPushBack(const BNmuonCollection& muons);
  void resetAndPushBack(const BNleptonCollection& leptons);
  void pushBackAndSort(const BNelectronCollection& electrons);
  void pushBackAndSort(const BNmuonCollection& muons);
  void pushBackAndSort(const BNleptonCollection& leptons);
  void cleanJets(const BNleptonCollection& leptons, const double drCut);
  void cleanJets_cProj(const BNleptonCollection& leptons, const double drCut);
  void correctRawJets(sysType::sysType jetSyst=sysType::NA);
  void keepSelectedJets(const double ptCut, const double etaCut, const jetID::jetID ID, const char csvWP);
  void getCorrectedMet(GenericCollection<BNjetCollection> jets, sysType::sysType jetSyst=sysType::NA);
  void reset();

private:
  collectionType topCollection;
  collectionType bottomCollection;
};

template<class collectionType>
GenericCollection<collectionType>::GenericCollection(BEANhelper * bHelp) : bHelp(bHelp) {
  reset();
}

template<class collectionType>
void GenericCollection<collectionType>::reset() {
  rawItems.clear();
  items.clear();
}

template<class collectionType>
void GenericCollection<collectionType>::initializeRawItems(edm::EventBase& event, string rawCollectionLabel, string rawCollectionInstance) {
  reset();

  edm::InputTag tag(rawCollectionLabel, rawCollectionInstance);
  edm::Handle<collectionType> handle;
  event.getByLabel(tag, handle);
  rawItems = *handle;
  items = rawItems;

  ptrToItems = &items;
}

template<class collectionType>
void GenericCollection<collectionType>::initializeRawItems(const collectionType& collection) {
  reset();

  rawItems = collection;
  items = rawItems;

  ptrToItems = &items;
}

template<class collectionType>
void GenericCollection<collectionType>::initializeRawItems(std::initializer_list<collectionType> collections) {
  reset();

  addUnion(collections);

}

template<class collectionType>
void GenericCollection<collectionType>::initializeRawItemsSortedByPt(edm::EventBase& event, string rawCollectionLabel, string rawCollectionInstance) {
  reset();
  initializeRawItems(event, rawCollectionLabel, rawCollectionInstance);

  items = bHelp->GetSortedByPt(items);

  ptrToItems = &items;
}

template<class collectionType>
void GenericCollection<collectionType>::initializeRawItemsSortedByPt(const collectionType& collection) {
  reset();

  rawItems = collection;
  items = bHelp->GetSortedByPt(collection);

  ptrToItems = &items;
}

template<class collectionType>
void GenericCollection<collectionType>::initializeRawItemsSortedByCSV(edm::EventBase& event, string rawCollectionLabel, string rawCollectionInstance) {
  reset();
  initializeRawItems(event, rawCollectionLabel, rawCollectionInstance);

  items = bHelp->GetSortedByCSV(items);

  ptrToItems = &items;
}

template<class collectionType>
void GenericCollection<collectionType>::initializeRawItemsSortedByCSV(const collectionType& collection) {
  reset();

  rawItems = collection;
  rawItems = bHelp->GetSortedByCSV(rawItems);
  items = rawItems;

  ptrToItems = &items;
}

template<class collectionType>
template<typename functionType>
void GenericCollection<collectionType>::keepSelectedParticles(functionType selectionFunction) {
  collectionType selectedParticles;

  for (auto& particle: items) {
    if (selectionFunction(*(ptr(particle)))) selectedParticles.push_back(particle);
  }

  items = selectedParticles;

  ptrToItems = &items;
}

template<class collectionType>
template<typename functionType, typename paramType>
void GenericCollection<collectionType>::keepSelectedParticles(functionType selectionFunction, paramType i) {
  collectionType selectedParticles;

  for (auto& particle: items) {
    if (selectionFunction(*(ptr(particle)), i)) selectedParticles.push_back(particle);
  }

  items = selectedParticles;

  ptrToItems = &items;
}

template<class collectionType>
template<typename functionType, typename paramType1, typename paramType2>
void GenericCollection<collectionType>::keepSelectedParticles(functionType selectionFunction, paramType1 i, paramType2 j) {
  collectionType selectedParticles;

  for (auto& particle: items) {
    if (selectionFunction(*(ptr(particle)), i, j)) selectedParticles.push_back(particle);
  }

  items = selectedParticles;

  ptrToItems = &items;
}

template<class collectionType>
template<typename functionType, typename paramType1, typename paramType2, typename paramType3>
void GenericCollection<collectionType>::keepSelectedParticles(functionType selectionFunction, paramType1 i, paramType2 j, paramType3 k) {
  collectionType selectedParticles;

  for (auto& particle: items) {
    if (selectionFunction(*(ptr(particle)), i, j, k)) selectedParticles.push_back(particle);
  }

  items = selectedParticles;

  ptrToItems = &items;
}

template<class BNelectronCollection>
void GenericCollection<BNelectronCollection>::keepSelectedParticles(electronID::electronID& ID) {

  items = bHelp->GetSelectedElectrons(rawItems, ID);

  ptrToItems = &items;
}

template<class BNmuonCollection>
void GenericCollection<BNmuonCollection>::keepSelectedParticles(muonID::muonID& ID) {

  items = bHelp->GetSelectedMuons(rawItems, ID);

  ptrToItems = &items;
}

template<class BNtauCollection>
void GenericCollection<BNtauCollection>::keepSelectedParticles(tauID::tauID& ID) {

  items = bHelp->GetSelectedTaus(rawItems, ID);

  ptrToItems = &items;
}

template<class BNelectronCollection>
void GenericCollection<BNelectronCollection>::keepSelectedDifference(electronID::electronID& topID, electronID::electronID& bottomID) {
  topCollection = bHelp->GetSelectedElectrons(rawItems, topID);
  bottomCollection = bHelp->GetSelectedElectrons(rawItems, bottomID);

  items = bHelp->GetDifference(topCollection, bottomCollection);

  ptrToItems = &items;
}

template<class BNmuonCollection>
void GenericCollection<BNmuonCollection>::keepSelectedDifference(muonID::muonID& topID, muonID::muonID& bottomID) {
  topCollection = bHelp->GetSelectedMuons(rawItems, topID);
  bottomCollection = bHelp->GetSelectedMuons(rawItems, bottomID);

  items = bHelp->GetDifference(topCollection, bottomCollection);

  ptrToItems = &items;
}

template<class collectionType>
void GenericCollection<collectionType>::addUnion(std::initializer_list<collectionType> collections) {
  for (auto& collection: collections) {
    items = bHelp->GetUnion(items, collection);
  }

  ptrToItems = &items;
}

template<class BNleptonCollection>
void GenericCollection<BNleptonCollection>::pushBack(std::initializer_list<BNelectronCollection> collections) {
  for (auto& collection: collections) {
    items.push_back(collection);
  }

  ptrToItems = &items;
}

template<class BNleptonCollection>
void GenericCollection<BNleptonCollection>::pushBack(std::initializer_list<BNmuonCollection> collections) {
  for (auto& collection: collections) {
    items.push_back(collection);
  }

  ptrToItems = &items;
}

template<class BNcollection>
void GenericCollection<BNcollection>::pushBack(std::initializer_list<BNleptonCollection> collections) {
  for (auto& collection: collections) {
    items.push_back(collection);
  }

  ptrToItems = &items;
}

template<class BNleptonCollection>
void GenericCollection<BNleptonCollection>::pushBack(const BNelectronCollection& electrons) {
    items.push_back(electrons);

    ptrToItems = &items;
}

template<class BNleptonCollection>
void GenericCollection<BNleptonCollection>::pushBack(const BNmuonCollection& muons) {
  items.push_back(muons);

  ptrToItems = &items;
}

template<class BNcollection>
void GenericCollection<BNcollection>::pushBack(const BNleptonCollection& leptons) {
  items.push_back(leptons);

  ptrToItems = &items;
}

template<class BNleptonCollection>
void GenericCollection<BNleptonCollection>::resetAndPushBack(const BNelectronCollection& electrons) {
  reset();
  items.push_back(electrons);

  ptrToItems = &items;
}

template<class BNleptonCollection>
void GenericCollection<BNleptonCollection>::resetAndPushBack(const BNmuonCollection& muons) {
  reset();
  items.push_back(muons);

  ptrToItems = &items;
}

template<class BNcollection>
void GenericCollection<BNcollection>::resetAndPushBack(const BNleptonCollection& leptons) {
  reset();
  items.push_back(leptons);

  ptrToItems = &items;
}

template<class BNleptonCollection>
void GenericCollection<BNleptonCollection>::pushBackAndSort(const BNelectronCollection& electrons) {
  items.push_back(electrons);
  items.sort();

  ptrToItems = &items;
}

template<class BNleptonCollection>
void GenericCollection<BNleptonCollection>::pushBackAndSort(const BNmuonCollection& muons) {
  items.push_back(muons);
  items.sort();

  ptrToItems = &items;
}

template<class BNcollection>
void GenericCollection<BNcollection>::pushBackAndSort(const BNleptonCollection& leptons) {
  items.push_back(leptons);
  items.sort();

  ptrToItems = &items;
}

template<class BNjetCollection>
void GenericCollection<BNjetCollection>::cleanJets(const BNleptonCollection& leptons, const double drCut = 0.5) {
  rawItems = bHelp->GetCleanJets(rawItems, leptons, drCut);
  ptrToItems = &items;
}

template<class BNjetCollection>
void GenericCollection<BNjetCollection>::cleanJets_cProj(const BNleptonCollection& leptons, const double drCut = 0.5) {
  rawItems = bHelp->GetCleanJets_cProj(rawItems, leptons, drCut);
  ptrToItems = &items;
}

template<class BNjetCollection>
void GenericCollection<BNjetCollection>::correctRawJets(sysType::sysType jetSyst) {
  rawItems = bHelp->GetCorrectedJets(rawItems, jetSyst);

  ptrToItems = &items;
}

template<class BNjetCollection>
void GenericCollection<BNjetCollection>::keepSelectedJets(const double ptCut, const double etaCut, const jetID::jetID ID, const char csvWP) {
  items = bHelp->GetSelectedJets(rawItems, ptCut, etaCut, ID, csvWP);

  ptrToItems = &items;
}

template<class BNmetCollection>
void GenericCollection<BNmetCollection>::getCorrectedMet(GenericCollection<BNjetCollection> jets, sysType::sysType jetSyst) {
  items.clear();
  //take the GenericCollection instead of the BNjetCollection to ensure we don't accidentally use the corrected jets
  BNmet tmpMet = bHelp->GetCorrectedMET(rawItems.at(0), jets.rawItems, jetSyst);
  items.push_back(tmpMet);

  ptrToItems = &items;
}

#endif
