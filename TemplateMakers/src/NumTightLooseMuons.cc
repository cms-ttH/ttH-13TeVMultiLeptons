
#include "ttH-Multileptons/TemplateMakers/interface/NumTightLooseMuons.h"

NumTightLooseMuons::NumTightLooseMuons ()  {

  numTightMuons.branchName = "numTightMuons";
  numTightMuons.branchType = "numTightMuons/I";

  numLooseMuons.branchName = "numLooseMuons";
  numLooseMuons.branchType = "numLooseMuons/I";

  passTwoMuon.branchName = "passTwoMuon";
  passTwoMuon.branchType = "passTwoMuon/I";

  minTight = 0; // no cut
  maxTight = 100; // no cut effectively
  
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
  if (! blocks->checkMuons() ) return;


  numTightMuons.branchVal = int(blocks->muonCollection->size());
  numLooseMuons.branchVal = int(blocks->looseMuonCollection->size());

  passTwoMuon.branchVal = passCut() ? 1 : 0;
  

  evaluatedThisEvent = true;

}

bool NumTightLooseMuons::passCut () {

  if (!evaluatedThisEvent) evaluate();
  
  bool pass = false;

  if (numTightMuons.branchVal >= minTight
      && numTightMuons.branchVal < maxTight
      && numLooseMuons.branchVal >= minLoose
      && numLooseMuons.branchVal < maxLoose)
    pass = true;
  
  return pass;

}

void NumTightLooseMuons::setCut (int minT, int maxT, int minL, int maxL) {
  minTight = minT;
  maxTight = maxT;
  minLoose = minL;
  maxLoose = maxL;
  
}
