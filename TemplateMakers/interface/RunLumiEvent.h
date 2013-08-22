
#ifndef _RunLumiEvent_h
#define _RunLumiEvent_h

#include "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BranchInfo.h"


class RunLumiEvent: public KinematicVariable {


public:  
  BranchInfo<unsigned> runNumber;
  BranchInfo<unsigned> lumiBlock;
  BranchInfo<unsigned> eventNumber;

  // pass if >= threshold  

  bool evaluatedThisEvent;

  RunLumiEvent();


  void evaluate ();
  void attachToTree (TTree * inTree);
  void reset ();

  bool passCut ();

  void setCut ();

  void print ();

};




#endif
