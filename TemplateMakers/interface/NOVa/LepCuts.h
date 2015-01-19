#ifndef _LepCuts_h
#define _LepCuts_h

#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/KinematicVariable.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/BranchInfo.h" 
#include <typeinfo>

template <class collectionType>
class LepCuts: public KinematicVariable<int> {

public:
  //Store branch values so they are accessible to other classes
  vector<BranchInfo<int>> myVars;

  BEANhelper * beanHelper;
  collectionType **selCollection;
  string branch_name;
  unsigned int maxLeptons;

  TString branchName;

  LepCuts(BEANhelper * _beanHelper, collectionType **_selCollection,
          string _branch_name, int _maxLeptons);

  void evaluate ();

//   int computeLepCut(double _pt, int _isElectron, int _isMuon,
//                     double _jetBTagCSV, double _chargedHadronIsoDR04,
//                     double _IP, double _SIP, double _jetPtRatio);

};

template <class collectionType>
LepCuts<collectionType>::LepCuts(BEANhelper * _beanHelper, collectionType **_selCollection,
                                 string _branch_name, int _maxLeptons):
  beanHelper(_beanHelper), selCollection(_selCollection),
  branch_name(_branch_name), maxLeptons(_maxLeptons)
{
  this->resetVal = KinematicVariableConstants::INT_INIT;

  for (unsigned int i=0; i<maxLeptons; i++) {
    branchName = Form("%s_%d_lepCut", branch_name.c_str(), i+1);
    branches[branchName] = BranchInfo<int>(branchName);
    branches[branchName].branchVal = this->resetVal;
  }

}

template <class collectionType>
void LepCuts<collectionType>::evaluate () {

  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  //--------

  for (unsigned int iObj = 0; iObj < (*selCollection)->size(); iObj++) {
    if (iObj < maxLeptons) {
      branchName = Form("%s_%d_lepCut", branch_name.c_str(), iObj+1);

      if (ptr((*selCollection)->at(iObj))->isElectron) {
        branches[branchName].branchVal = beanHelper->GetElectronLepCut(*(BNelectron*)ptr((*selCollection)->at(iObj))); }
      else {
        branches[branchName].branchVal = beanHelper->GetMuonLepCut(*(BNmuon*)ptr((*selCollection)->at(iObj))); }

//       branches[branchName].branchVal = computeLepCut(ptr((*selCollection)->at(iObj))->pt,
//                                                      ptr((*selCollection)->at(iObj))->isElectron,
//                                                      ptr((*selCollection)->at(iObj))->isMuon,
//                                                      ptr((*selCollection)->at(iObj))->jetBTagCSV,
//                                                      ptr((*selCollection)->at(iObj))->chargedHadronIsoDR04,
//                                                      ptr((*selCollection)->at(iObj))->IP,
//                                                      ptr((*selCollection)->at(iObj))->SIP,
//                                                      ptr((*selCollection)->at(iObj))->jetPtRatio);

    }//End if ( iObj < maxLeptons )
  }//End for iObj

  //Clean out values from last event
  myVars.clear();

  for (typename map<TString, BranchInfo<int>>::iterator iBranch = branches.begin();
       iBranch != branches.end(); iBranch++ ) {
    myVars.push_back(iBranch->second);
  }
}

// template <class collectionType>
// int LepCuts<collectionType>::computeLepCut(double pt, int isElectron, int isMuon,
//                   double jetBTagCSV, double chargedHadronIsoDR04,
//                   double IP, double SIP, double jetPtRatio) {

//   int lepCut = -2;
  
//   if (isElectron) {
    
//     if ( jetBTagCSV > 0.679 ) {
//       lepCut = -1; }
//     else if ( chargedHadronIsoDR04 < 0 || // < -1 does nothing; < 0 eliminates some
//               chargedHadronIsoDR04 / pt > 0.15 ) {
//       lepCut = 0; }
//     else if ( abs(IP) > 0.015 ||
//               chargedHadronIsoDR04 / pt > 0.05 ||
//               jetPtRatio < 0.6 ) {
//       lepCut = 1; }
//     else lepCut = 2;
    
//   }
  
//   else if (isMuon) {
    
//     if ( jetBTagCSV > 0.679 ) {
//       lepCut = -1; }
//     else if ( abs(SIP) > 4 || 
//               chargedHadronIsoDR04 / pt > 0.20 ) {
//       lepCut = 0; }
//     else if ( chargedHadronIsoDR04 / pt > 0.10 ||
//               jetPtRatio < 0.6 ) {
//       lepCut = 1; }
//     else lepCut = 2;
//   }

//   return lepCut;
// }

#endif
