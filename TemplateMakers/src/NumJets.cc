
#include "ttH-Multileptons/TemplateMakers/interface/NumJets.h"

NumJets::NumJets () : branchName("numJets"), branchType("numJets/I"){

  reset();

}

void NumJets::attachToTree(TTree *inTree) {

  inTree->Branch(branchName, &numJets, branchType);
  
}

void NumJets::reset () {

  numJets = KinematicVariableConstants::INT_INIT;
  
}

void NumJets::evaluate () {

  if (! blocks->checkJets() ) return;

  numJets = int(blocks->jetCollection->size());
  
  //cout << "numJets = " << numJets << "  hex=  " <<std::hex <<  numJets << std::dec <<  endl;
  

}
