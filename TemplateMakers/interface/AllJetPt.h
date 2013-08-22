


#ifndef _AllJetPt_h
#define _AllJetPt_h

#include "ttHMultileptonAnalysis/TemplateMakers/interface/BranchInfo.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"

class AllJetPt: public KinematicVariable {


public:  
  vector< BranchInfo<float> > branchInfos;

  int maxJets;

  AllJetPt ();
  AllJetPt (int max);

  void evaluate ();
  void attachToTree (TTree * inTree);
  void reset ();
  void print ();


};

#endif
