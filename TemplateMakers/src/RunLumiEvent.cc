
#include "ttHMultileptonAnalysis/TemplateMakers/interface/RunLumiEvent.h"

RunLumiEvent::RunLumiEvent() {

  runNumber.branchName = "runNumber";
  runNumber.branchType = "runNumber/i";

  lumiBlock.branchName = "luminosityBlock";
  lumiBlock.branchType = "luminosityBlock/i";

  eventNumber.branchName = "eventNumber";
  eventNumber.branchType = "eventNumber/i";

  reset();
  
}

void RunLumiEvent::reset () {

  evaluatedThisEvent = false;
  runNumber.branchVal = KinematicVariableConstants::UINT_INIT;
  lumiBlock.branchVal = KinematicVariableConstants::UINT_INIT;
  eventNumber.branchVal = KinematicVariableConstants::UINT_INIT;
  
}

void RunLumiEvent::evaluate () {

  if (evaluatedThisEvent) return;

  evaluatedThisEvent = true;

  BNevent eventInfo = blocks->eventCollection->at(0);

  runNumber.branchVal = eventInfo.run;
  lumiBlock.branchVal = eventInfo.lumi;
  eventNumber.branchVal = unsigned(eventInfo.evt);
  
  
}
void RunLumiEvent::attachToTree (TTree * inTree) {

  inTree->Branch(runNumber.branchName, &runNumber.branchVal, runNumber.branchType);
  inTree->Branch(lumiBlock.branchName, &lumiBlock.branchVal, lumiBlock.branchType);
  inTree->Branch(eventNumber.branchName, &eventNumber.branchVal, eventNumber.branchType);

}

bool RunLumiEvent::passCut () {

  // I suppose this could be fancier at some point
  // like cutting on events in a list
  // but for now it is fine to leave it boring
  
  return true;
  
}

void RunLumiEvent::setCut () {

  // placeholder for future development 
  
}

void RunLumiEvent::print () {

  cout << " " <<  runNumber.branchName << " " << runNumber.branchVal
       << " " <<  lumiBlock.branchName << " " << lumiBlock.branchVal
       << " " <<  eventNumber.branchName << " " << eventNumber.branchVal;

 
}

