#ifndef _KinematicVariable_h
#define _KinematicVariable_h

#include "TFile.h"
#include "TChain.h"
#include "TH1.h"
#include "TH3.h"
#include "TH2F.h"
#include "TF1.h"
#include "TF2.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TPaveStats.h"
#include "TAxis.h"
#include "TMath.h"
#include "TRandom3.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <exception>
#include <cmath>
#include <random>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include "TGraphAsymmErrors.h"
#include "TLorentzVector.h"
//Root includes
#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
#include "FWCore/FWLite/interface/AutoLibraryLoader.h"

#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/FWLite/interface/ChainEvent.h"

//Headers for the data items
/* #include "BEAN/Collections/interface/BNelectron.h" */
/* #include "BEAN/Collections/interface/BNevent.h" */
/* #include "BEAN/Collections/interface/BNjet.h" */
/* #include "BEAN/Collections/interface/BNmcparticle.h" */
/* #include "BEAN/Collections/interface/BNmet.h" */
/* #include "BEAN/Collections/interface/BNmuon.h" */
/* #include "BEAN/Collections/interface/BNphoton.h" */
/* #include "BEAN/Collections/interface/BNsupercluster.h" */
/* #include "BEAN/Collections/interface/BNtrack.h" */
/* #include "BEAN/Collections/interface/BNtrigger.h" */
/* #include "BEAN/Collections/interface/BNskimbits.h" */
/* #include "BEAN/Collections/interface/BNtrigobj.h" */
/* #include "BEAN/Collections/interface/BNprimaryvertex.h" */

#include "ttHMultileptonAnalysis/TemplateMakers/interface/Lepton.h"

// headers for python config processing

//#include "BEAN/BEANmaker/interface/BtagWeight.h"
//#include "BEAN/BEANmaker/interface/BEANhelper.h"

#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"

//#include "BEAN/BEANmaker/interface/AnglesUtil.h"
#include "PhysicsTools/Utilities/interface/LumiReweightingStandAlone.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"


//#include "ttHMultileptonAnalysis/TemplateMakers/interface/BEANFileInterface.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BranchInfo.h"

using namespace std;

///////////////////////////////////////////////////
// 
//   Parent class describing how each kinematic
//     variable will work
//
//  The reason you have this base class is that you 
//    want to take advantage of it's polymorphic
//    properties and make a loop that goes 
//    over each Arbitrary variable without 
//    worrying about which template type it has
//
//  
//
//
//////////////////////////////////////////////////


class ArbitraryVariable {

public:
  
  ArbitraryVariable() {};

  virtual void evaluate () {};

  
  virtual void attachToTree (TTree *) {};
  
  virtual void reset () {};

  virtual bool passCut () {
    return true;
  };


  virtual void print () {};
  
  
};




template <class branchDataType> 
class KinematicVariable: public ArbitraryVariable {


public:

  // Do nothing
  KinematicVariable ();

  //  BEANFileInterface *blocks;

  branchDataType resetVal;

  // all of the things you want to store
  map<TString, BranchInfo<branchDataType> > branches;

  bool evaluatedThisEvent;

  virtual void evaluate ();

  virtual void attachToTree (TTree *);
  
  virtual void reset ();

  virtual bool passCut ();


  virtual void print ();

};


// Default constructor
// Don't do anything 

template <class branchDataType>
KinematicVariable<branchDataType>::KinematicVariable() {

  
}

template <class branchDataType>
void KinematicVariable<branchDataType>::attachToTree(TTree * inTree ) {


  for ( typename map<TString, BranchInfo<branchDataType> >::iterator iBranch = branches.begin();
        iBranch != branches.end();
        iBranch++ ) {
    BranchInfo<branchDataType> * iInfo = &(iBranch->second);
    inTree->Branch(iInfo->branchName, &iInfo->branchVal);
  }
  
}

template <class branchDataType>
void KinematicVariable<branchDataType>::reset() {

  evaluatedThisEvent = false;
  for ( typename map<TString, BranchInfo<branchDataType> >::iterator iBranch = branches.begin();
        iBranch != branches.end();
        iBranch++ ) {
    BranchInfo<branchDataType> * iInfo = &(iBranch->second);
    iInfo->branchVal = resetVal;
  }  
  
}

template <class branchDataType>
void KinematicVariable<branchDataType>::print() {

  for ( typename map<TString, BranchInfo<branchDataType> >::iterator iBranch = branches.begin();
        iBranch != branches.end();
        iBranch++ ) {
    BranchInfo<branchDataType> * iInfo = &(iBranch->second);
    cout << "     "  << iInfo->branchName << "  " <<  iInfo->branchVal;
  }
  
  
}


template <class branchDataType>
void KinematicVariable<branchDataType>::evaluate() {

  cout << "Error, you called evaluate for KinematicVariable, which is just a base class"
       << endl;
  assert(false);
  
}

template <class branchDataType>
bool KinematicVariable<branchDataType>::passCut() {

  cout << "Error, you called passCut for KinematicVariable, which is just a base class"
       << endl;
  assert(false);
  
}


namespace KinematicVariableConstants {

  const float FLOAT_INIT = -9.0e20;
  const int INT_INIT = -99999999;
  const unsigned UINT_INIT = 987654;
  const double DOUBLE_INIT = -9.0e20;
}

#endif // KinematicVariable
