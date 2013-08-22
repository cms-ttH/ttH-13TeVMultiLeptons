
#ifndef _NumTightLooseMuons_h
#define _NumTightLooseMuons_h

#include "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BranchInfo.h"

class NumTightLooseMuons: public KinematicVariable {


public:  
  BranchInfo<int> numTightMuons;
  BranchInfo<int> numLooseMuons;
  BranchInfo<int> passTwoMuon;

  // pass if >= threshold
  int minTight;
  int maxTight;
  int minLoose;
  int maxLoose;
  int totalTightPlusLoose;

  
  bool useSumTightLoose;
  


  bool evaluatedThisEvent;

  NumTightLooseMuons();

  void evaluate ();
  void attachToTree (TTree * inTree);
  void reset ();

  bool passCut ();

  void setCut (int minT, int maxT, int minL, int maxL);

  void setCutOnSumTightLoose (int minT, int total);

  void print ();

};




#endif
