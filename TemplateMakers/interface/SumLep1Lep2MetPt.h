
#ifndef _SumLep1Lep2MetPt_h
#define _SumLep1Lep2MetPt_h


#include  "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"

//
//  Calculate lep1pt + lep2pt + met  
//  If there is less than two leptons, store met + nlep pt
//


class SumLep1Lep2MetPt: public KinematicVariable<double> {

public:
  
  SumLep1Lep2MetPt();

  void evaluate ();
    
};

SumLep1Lep2MetPt::SumLep1Lep2MetPt ()

{


  branches["sum_lep1pt_lep2pt_met"] = BranchInfo<double>("sum_lep1pt_lep2pt_met");
  
}

void SumLep1Lep2MetPt::evaluate () {

  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  //--------

  BNleptonCollection* tightLoosePreselectedLeptons = this->blocks->tightLoosePreselectedLeptonCollection;
  BNmet & theMet = this->blocks->metCollection->at(0);

  double metVal = theMet.pt;
 
  double result = metVal;

  unsigned numLeps = tightLoosePreselectedLeptons->size();
  unsigned loopMax = (numLeps < 2) ? numLeps : 2;

  
  for (unsigned firstIndex = 0;
       firstIndex < loopMax;
       firstIndex++){

    BNlepton * temp1 = tightLoosePreselectedLeptons->at(firstIndex);
    result += temp1->pt;
    
  }// end first loop
        


  branches["sum_lep1pt_lep2pt_met"].branchVal = result;
  
  
  
}



#endif 
