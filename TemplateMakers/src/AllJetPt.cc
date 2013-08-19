
#include "ttH-Multileptons/TemplateMakers/interface/AllJetPt.h"


//////////////////////////////////
//
//
//      Default constructor
//
//
////////////////////////////////

AllJetPt::AllJetPt ()  {

  // just call the regular constructor with a min and max

  //AllJetPt(6);

  maxJets = 6;

}


AllJetPt::AllJetPt (int max) : maxJets(max) {

  // create branch names and a space to store the results
  for (int iJet = 0; iJet <= maxJets; iJet++) {
    TString tmpBranchName = Form("jet_pt_%d_pt", (iJet+1));
    TString tmpBranchType = tmpBranchName + TString("/F");
    branchInfos.push_back(BranchInfo<float>(tmpBranchName, tmpBranchType));                          
 
  }

  // call reset
  reset();
}


void AllJetPt::reset () {

  for (unsigned iCat = 0; iCat < branchInfos.size(); iCat++ ) {

    branchInfos[iCat].branchVal = KinematicVariableConstants::FLOAT_INIT;
    
  }

}

void AllJetPt::attachToTree (TTree *inTree) {

  for (unsigned iCat = 0; iCat < branchInfos.size(); iCat++ ) {
    
    inTree->Branch(branchInfos[iCat].branchName, &branchInfos[iCat].branchVal, branchInfos[iCat].branchType);
       
  }

 
}

void AllJetPt::evaluate () {

  if (! blocks->checkJets() ) return;

  // Assume that the jet collection is already
  // ordered by pt. This is a reasonable assumption  
  
  unsigned numJets = blocks->jetCollection->size();

  // Two cases: you have more jets than variables,
  // in which case you fill to completion
  // Alternatively: you have more variables than jets,
  // in which case you leave the unfilled ones at their default
  // value
  unsigned loopMax = (unsigned(maxJets) < numJets) ? unsigned(maxJets) : numJets;
  
  for (unsigned iCat = 0; iCat < loopMax; iCat++ ) {
    
    branchInfos[iCat].branchVal = blocks->jetCollection->at(iCat).pt;
       
  }

}
