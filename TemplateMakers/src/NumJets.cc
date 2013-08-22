
#include "ttHMultileptonAnalysis/TemplateMakers/interface/NumJets.h"

NumJets::NumJets () : branchName("numJets"), branchType("numJets/I"), threshold(0) {

  reset();

}

void NumJets::attachToTree(TTree *inTree) {

  inTree->Branch(branchName, &numJets, branchType);
  
}

void NumJets::reset () {

  numJets = KinematicVariableConstants::INT_INIT;
  evaluatedThisEvent = false;
}

void NumJets::evaluate () {
  
  if (evaluatedThisEvent) return;
  if (! blocks->checkJets() ) return;


  numJets = int(blocks->jetCollection->size());
  
  //cout << "numJets = " << numJets << "  hex=  " <<std::hex <<  numJets << std::dec <<  endl;

  evaluatedThisEvent = true;

}

bool NumJets::passCut () {

  if (!evaluatedThisEvent) evaluate();
  
  return (numJets >= threshold);

}

void NumJets::setCut (int th) {
  threshold = th;
  
}

void NumJets::print () {

  cout << " numJets = " << numJets << endl;

}


