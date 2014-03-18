#ifndef _GenericCollection_h
#include <functional>
#include "BEAN/BEANmaker/interface/BEANhelper.h"

#define _GenericCollection_h

template <class collectionType>
class GenericCollection {

public:
  sysType::sysType jetEnergyShift;
  BEANhelper * bHelp;
  collectionType rawItems;
  collectionType items;
  collectionType * ptrToItems;
  std::function<bool (collectionType)> selectionFunction;
  //std::unique_ptr<collectionType> items(new collectionType);

  GenericCollection(BEANhelper * bHelp);
  void initializeRawItems(edm::EventBase& event, string rawCollectionLabel, string rawCollectionInstance);
  void initializeRawItems(collectionType collection);
  void initializeRawItemsSortedByPt(edm::EventBase& event, string rawCollectionLabel, string rawCollectionInstance);
  void initializeRawItemsSortedByPt(collectionType collection);
  void initializeRawItemsSortedByCSV(edm::EventBase& event, string rawCollectionLabel, string rawCollectionInstance);
  void initializeRawItemsSortedByCSV(collectionType collection);
  template <typename functionType> void keepSelectedParticles(functionType selectionFunction);
  void keepSelectedParticles(electronID::electronID& ID);
  void keepSelectedParticles(muonID::muonID& ID);
  void keepSelectedParticles(tauID::tauID& ID);
  void keepSelectedDifference(electronID::electronID& topID, electronID::electronID& bottomID);
  void keepSelectedDifference(muonID::muonID& topID, muonID::muonID& bottomID);
  void addUnion(std::initializer_list<collectionType> collections);
  void pushBack(std::initializer_list<BNelectronCollection> collections);
  void pushBack(std::initializer_list<BNmuonCollection> collections);
  void pushBack(BNelectronCollection& electrons);
  void pushBack(BNmuonCollection& muons);
  void resetAndPushBack(BNelectronCollection& electrons);
  void resetAndPushBack(BNmuonCollection& muons);
  void pushBackAndSort(BNelectronCollection& electrons);
  void pushBackAndSort(BNmuonCollection& muons);
  void cleanJets(BNleptonCollection& leptons);
  void correctRawJets();
  void keepSelectedJets(const double ptCut, const double etaCut, const jetID::jetID ID, const char csvWP);
  void getCorrectedMet(GenericCollection<BNjetCollection> jets, sysType::sysType shift=sysType::NA);
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
void GenericCollection<collectionType>::initializeRawItems(collectionType collection) {
  reset();

  rawItems = collection;
  items = rawItems;

  ptrToItems = &items;
}

template<class collectionType>
void GenericCollection<collectionType>::initializeRawItemsSortedByPt(edm::EventBase& event, string rawCollectionLabel, string rawCollectionInstance) {
  initializeRawItems(event, rawCollectionLabel, rawCollectionInstance);

  items = bHelp->GetSortedByPt(items);

  ptrToItems = &items;
}

template<class collectionType>
void GenericCollection<collectionType>::initializeRawItemsSortedByPt(collectionType collection) {
  reset();

  rawItems = collection;
  items = rawItems;
  items = bHelp->GetSortedByPt(items);

  ptrToItems = &items;
}

template<class collectionType>
void GenericCollection<collectionType>::initializeRawItemsSortedByCSV(edm::EventBase& event, string rawCollectionLabel, string rawCollectionInstance) {
  initializeRawItems(event, rawCollectionLabel, rawCollectionInstance);

  items = bHelp->GetSortedByCSV(items);

  ptrToItems = &items;
}

template<class collectionType>
void GenericCollection<collectionType>::initializeRawItemsSortedByCSV(collectionType collection) {
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
    if (selectionFunction(particle)) selectedParticles.push_back(particle);
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

template<class BNleptonCollection>
void GenericCollection<BNleptonCollection>::pushBack(BNelectronCollection& electrons) {
    items.push_back(electrons);

    ptrToItems = &items;
}

template<class BNleptonCollection>
void GenericCollection<BNleptonCollection>::pushBack(BNmuonCollection& muons) {
  items.push_back(muons);

  ptrToItems = &items;
}

template<class BNleptonCollection>
void GenericCollection<BNleptonCollection>::resetAndPushBack(BNelectronCollection& electrons) {
  reset();
  items.push_back(electrons);

  ptrToItems = &items;
}

template<class BNleptonCollection>
void GenericCollection<BNleptonCollection>::resetAndPushBack(BNmuonCollection& muons) {
  reset();
  items.push_back(muons);

  ptrToItems = &items;
}

template<class BNleptonCollection>
void GenericCollection<BNleptonCollection>::pushBackAndSort(BNelectronCollection& electrons) {
  items.push_back(electrons);
  items.sort();

  ptrToItems = &items;
}

template<class BNleptonCollection>
void GenericCollection<BNleptonCollection>::pushBackAndSort(BNmuonCollection& muons) {
  items.push_back(muons);
  items.sort();

  ptrToItems = &items;
}

template<class BNjetCollection>
void GenericCollection<BNjetCollection>::cleanJets(BNleptonCollection& leptons) {
  items = bHelp->GetCleanJets(items, leptons, 0.5);

  ptrToItems = &items;
}

template<class BNjetCollection>
void GenericCollection<BNjetCollection>::correctRawJets() {
  rawItems = bHelp->GetCorrectedJets(rawItems, jetEnergyShift);

  ptrToItems = &items;
}

template<class BNjetCollection>
void GenericCollection<BNjetCollection>::keepSelectedJets(const double ptCut, const double etaCut, const jetID::jetID ID, const char csvWP) {
  items = bHelp->GetSelectedJets(rawItems, ptCut, etaCut, ID, csvWP);

  ptrToItems = &items;
}

template<class BNmetCollection>
void GenericCollection<BNmetCollection>::getCorrectedMet(GenericCollection<BNjetCollection> jets, sysType::sysType shift) {
  items.clear();
  //take the GenericCollection instead of the BNjetCollection to ensure we don't accidentally use the corrected jets
  BNmet tmpMet = bHelp->GetCorrectedMET(rawItems.at(0), jets.rawItems, shift);
  items.push_back(tmpMet);

  ptrToItems = &items;
}

#endif
