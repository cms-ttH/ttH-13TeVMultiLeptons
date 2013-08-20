
#ifndef _NumTightLooseMuons_h
#define _NumTightLooseMuons_h

#include "ttH-Multileptons/TemplateMakers/interface/KinematicVariable.h"
#include "ttH-Multileptons/TemplateMakers/interface/BranchInfo.h"

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

  bool evaluatedThisEvent;

  NumTightLooseMuons();

  void evaluate ();
  void attachToTree (TTree * inTree);
  void reset ();

  bool passCut ();

  void setCut (int minT, int maxT, int minL, int maxL);


};




#endif
