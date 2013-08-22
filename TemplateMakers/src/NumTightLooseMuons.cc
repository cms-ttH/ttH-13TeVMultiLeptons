
#include "ttHMultileptonAnalysis/TemplateMakers/interface/NumTightLooseMuons.h"

NumTightLooseMuons::NumTightLooseMuons ()  {

  numTightMuons.branchName = "numTightMuons";
  numTightMuons.branchType = "numTightMuons/I";

  numLooseMuons.branchName = "numLooseMuons";
  numLooseMuons.branchType = "numLooseMuons/I";

  passTwoMuon.branchName = "TwoMuon";
  passTwoMuon.branchType = "TwoMuon/I";

  minTight = 0; // no cut
  maxTight = 100; // no cut effectively
  minLoose = 0; // no cut
  maxLoose = 0; // no loose allowed

  useSumTightLoose = false;
  
  reset();

}

void NumTightLooseMuons::attachToTree(TTree *inTree) {

  inTree->Branch(numTightMuons.branchName, &numTightMuons.branchVal, numTightMuons.branchType);
  inTree->Branch(numLooseMuons.branchName, &numLooseMuons.branchVal, numLooseMuons.branchType);
  inTree->Branch(passTwoMuon.branchName, &passTwoMuon.branchVal, passTwoMuon.branchType);
  
}

void NumTightLooseMuons::reset () {

  numTightMuons.branchVal = KinematicVariableConstants::INT_INIT;
  numLooseMuons.branchVal = KinematicVariableConstants::INT_INIT;
  passTwoMuon.branchVal = KinematicVariableConstants::INT_INIT;
  evaluatedThisEvent = false;
  
}

void NumTightLooseMuons::evaluate () {
  
  if (evaluatedThisEvent) return;

  // you've already entered this function
  // careful, there is a chance for infinite function calls
  evaluatedThisEvent = true;
  
  if (!blocks->checkMuons() || ! blocks->checkLooseMuons() ) {
    cout << "Muon collection pointer not initialized, but you request a number of muons" << endl;
    assert (false); // crash
  }


  numTightMuons.branchVal = int(blocks->muonCollection->size());
  numLooseMuons.branchVal = int(blocks->looseMuonCollection->size());

  passTwoMuon.branchVal = passCut() ? 1 : 0;
  

  

}

bool NumTightLooseMuons::passCut () {

  if (!evaluatedThisEvent) evaluate();
  
  bool pass = false;

  if (useSumTightLoose) {

    // At least min tight muons
    // tight plus loose is exactly total
    
    if (numTightMuons.branchVal >= minTight
        && (numTightMuons.branchVal + numLooseMuons.branchVal) == totalTightPlusLoose)
      pass = true;
    
    
  } else {
    
    if (numTightMuons.branchVal >= minTight
        && numTightMuons.branchVal < maxTight
        && numLooseMuons.branchVal >= minLoose
        && numLooseMuons.branchVal < maxLoose)
      pass = true;
  }
  
  return pass;

}

void NumTightLooseMuons::setCut (int minT, int maxT, int minL, int maxL) {
  minTight = minT;
  maxTight = maxT;
  minLoose = minL;
  maxLoose = maxL;

  useSumTightLoose = false;
}

void NumTightLooseMuons::setCutOnSumTightLoose(int minT, int total) {

  useSumTightLoose = true;
  minTight = minT;
  totalTightPlusLoose = total;
  

}

void NumTightLooseMuons::print () {

  cout << " numTightMuons = " << numTightMuons.branchVal
       << " numLoooseMuons = " << numLooseMuons.branchVal
       << " TwoMuon = " << passTwoMuon.branchVal;


  
}
