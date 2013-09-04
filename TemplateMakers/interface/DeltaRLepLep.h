
#ifndef _DeltaRLepLep_h
#define _DeltaRLepLep_h


#include  "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"

//
//
//  Loops over lepton collections
//  calculates DR lep lep for all pairs of leptons
//
//  By default stores the minimum
//  But it could easily store more values

class DeltaRLepLep: public KinematicVariable<double> {

public:
  
  DeltaRLepLep();

  void evaluate ();
  bool passCut ();
  
  
};

DeltaRLepLep::DeltaRLepLep ()
{

  branches["min_dR_leplep"] = BranchInfo<double>("min_dR_leplep");
  this->resetVal = KinematicVariableConstants::DOUBLE_INIT;
}

void DeltaRLepLep::evaluate () {

  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  //--------

  BNleptonCollection tightLoosePreselectedLeptons = this->blocks->preselectedLeptonCollection;

  double drResult = 10000.0;

  if (tightLoosePreselectedLeptons.size() < 2) {
    massResult = this->resetVal;
  } else {

    // Algorithm:
    // Start with first letpon.
    // Iterate through the rest of the leptons
    //   starting with first+1
    // Calculate the DR
    // store the minimum.
    
    for (unsigned firstIndex = 0;
         firstIndex < tightLoosePreselectedLeptons.size();
         firstIndex++){

      BNlepton * temp1 = tightLoosePreselectedLeptons.at(firstIndex);

      
      for (unsigned secondIndex = firstIndex+1;
           secondIndex < tightLoosePreselectedLeptons.size();
           secondIndex++ ) {


        BNlepton * temp2 = tightLoosePreselectedLeptons.at(secondIndex);

        // where is this defined? who knows...
        tempDR = deltaR(temp1->phi, temp1->eta, temp2->phi, temp2->eta);
        
        if ( tempDR < massResult )
          drResult = tempDR;
                
      }// end second loop
    
    }// end first loop
        
  }// end if size >=2

  branches["min_dR_leplep"].branchVal = drResult;
  
  
  
}


bool DeltaRLepLep::passCut() {

  evaluate();
  
  if (branches["min_dR_leplep"].branchVal > 0.2)
    return true;
  return false;

}



#endif 
