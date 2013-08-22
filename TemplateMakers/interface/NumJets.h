
#ifndef _NumJets_h
#define _NumJets_h

#include "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"

class NumJets: public KinematicVariable {


public:  
  int numJets;

  // pass if >= threshold
  int threshold;

  bool evaluatedThisEvent;

  NumJets();

  TString branchName;
  TString branchType;

  void evaluate ();
  void attachToTree (TTree * inTree);
  void reset ();

  bool passCut ();

  void setCut (int th);

  void print ();

};




#endif
