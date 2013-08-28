
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

  BNleptonCollection tightAndLooseLeptons = this->blocks->mergedLeptonCollection;



  double drResult = 10000.0;

  if (tightAndLooseLeptons.size() < 2) {
    massResult = this->resetVal;
  } else {

    // Algorithm:
    // Start with first letpon.
    // Iterate through the rest of the leptons
    //   starting with first+1
    // Calculate the DR
    // store the minimum.
    
    for (unsigned firstIndex = 0;
         firstIndex < tightAndLooseLeptons.size();
         firstIndex++){

      BNlepton * temp1 = tightAndLooseLeptons.at(firstIndex);

      
      for (unsigned secondIndex = firstIndex+1;
           secondIndex < tightAndLooseLeptons.size();
           secondIndex++ ) {


        BNlepton * temp2 = tightAndLooseLeptons.at(secondIndex);

        // where is this defined? who knows...
        tempDR = deltaR(temp1->phi, temp1->eta, temp2->phi, temp2->eta);
        
        if ( tempDR < massResult )
          drResult = tempDR;
                
      }// end second loop
    
    }// end first loop
        
  }// end if size >=2

  branches["min_dR_leplep"].branchVal = drResult;
  
  
  
}


//
//  Recall that a BNleptonCollection is actually pointers to 
//  leptons and not lepton instances
//
//  Stuff everything into a single collection so it is easier to work with.
//
//

void DeltaRLepLep::mergeTightLooseLeptons ( BNleptonCollection & resultCollection) {


  resultCollection.clear();

  for ( BNleptonCollection::iterator iLep = this->blocks->leptonCollection->begin();
        iLep != this->blocks->leptonCollection->end();
        iLep ++ ) {

    resultCollection.push_back((*iLep));

  }

  //---- 
  
  for ( BNleptonCollection::iterator iLep = this->blocks->looseLeptonCollection->begin();
        iLep != this->blocks->looseLeptonCollection->end();
        iLep ++ ) {

    resultCollection.push_back((*iLep));

  }


  

}



bool DeltaRLepLep::passCut() {

  evaluate();
  
  if (branches["min_dR_leplep"].branchVal > 0.2)
    return true;
  return false;

}



#endif 
