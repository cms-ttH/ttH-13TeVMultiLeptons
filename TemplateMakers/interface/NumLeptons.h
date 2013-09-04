#ifndef _NumLeptons_h
#define _NumLeptons_h


// just store the number of leptons

class NumLeptons: public KinematicVariable<int> {

public:
  
  NumLeptons();

  void evaluate ();


};

NumLeptons::NumLeptons  () {

  branches["numTightMuons"] = BranchInfo<int>("numTightMuons");
  branches["numLooseMuons"] = BranchInfo<int>("numLooseMuons");
  
  branches["numTightElectrons"] = BranchInfo<int>("numTightElectrons");
  branches["numLooseElectrons"] = BranchInfo<int>("numLooseElectrons");

  this->resetVal = KinematicVariableConstants::INT_INIT;
  
}

void NumLeptons::evaluate () {

  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;
  
  branches["numTightMuons"].branchVal = int(this->blocks->tightMuonCollection->size());
  branches["numLooseMuons"].branchVal = int(this->blocks->looseMuonCollection->size());

  branches["numTightElectrons"].branchVal = int(this->blocks->tightElectronCollection->size());
  branches["numLooseElectrons"].branchVal = int(this->blocks->looseElectronCollection->size());
  
}



#endif 
