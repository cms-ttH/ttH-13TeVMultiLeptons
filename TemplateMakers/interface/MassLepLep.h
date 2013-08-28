
#ifndef _MassLepLep_h
#define _MassLepLep_h


#include  "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"

//
//
//  Loops over lepton collections
//  calculates mass lep lep for all pairs of leptons
//
//  By default stores the minimum
//  But it could easily store more values

class MassLepLep: public KinematicVariable<double> {

public:
  
  MassLepLep();

  void evaluate ();
  bool passCut ();
  
  //HelperLeptonCore * myHelper;

  // --- moved to HelperLeptonCore
  //void mergeTightLooseLeptons (BNleptonCollection & resultCollection);
  
  
};

MassLepLep::MassLepLep ()

{


  branches["min_mass_leplep"] = BranchInfo<double>("min_mass_leplep");
  
}

void MassLepLep::evaluate () {

  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  //--------

  BNleptonCollection* tightAndLooseLeptons = this->blocks->mergedLeptonCollection;
  

  double massResult = 10000.0;

  if (tightAndLooseLeptons->size() < 2) {
    massResult = this->resetVal;
  } else {

    // Algorithm:
    // Start with first letpon.
    // Iterate through the rest of the leptons
    //   starting with first+1
    // Calculate the mass
    // store the minimum.
    
    for (unsigned firstIndex = 0;
         firstIndex < tightAndLooseLeptons->size();
         firstIndex++){

      BNlepton * temp1 = tightAndLooseLeptons->at(firstIndex);
      TLorentzVector firstLep(temp1->px, temp1->py, temp1->pz, temp1->energy);
      
      for (unsigned secondIndex = firstIndex+1;
           secondIndex < tightAndLooseLeptons->size();
           secondIndex++ ) {


        BNlepton * temp2 = tightAndLooseLeptons->at(secondIndex);
        TLorentzVector secondLep (temp2->px, temp2->py, temp2->pz, temp2->energy);

        TLorentzVector comboLep = firstLep + secondLep;

        double tempMass = comboLep.M();

        if ( tempMass < massResult )
          massResult = tempMass;
                
      }// end second loop
    
    }// end first loop
        
  }// end if size >=2

  branches["min_mass_leplep"].branchVal = massResult;
  
  
  
}



bool MassLepLep::passCut() {

  evaluate();
  
  if (branches["min_mass_leplep"].branchVal > 12)
    return true;
  return false;

}



#endif 
