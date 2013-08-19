
#ifndef _NumJets_h
#define _NumJets_h

#include "ttH-Multileptons/TemplateMakers/interface/KinematicVariable.h"

class NumJets: public KinematicVariable {


public:  
  int numJets;

  NumJets();

  TString branchName;
  TString branchType;

  void evaluate ();
  void attachToTree (TTree * inTree);
  void reset ();



};

#endif
