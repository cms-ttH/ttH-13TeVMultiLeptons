#ifndef _SSLeptonTriggerScaleFactors_h
#define _SSLeptonTriggerScaleFactors_h

///////////////////////////////////////////////////////
//
//    Lepton Trigger Scale factors
//    Right now only for lepton trigger
//
////////////////////////////////////////////////////

class SSLeptonTriggerScaleFactors: public KinematicVariable<double> {

public:
  // for now you have to specify your selection
  SSLeptonTriggerScaleFactors(HelperLeptonCore *in );
  void evaluate ();
  bool passCut ();

  HelperLeptonCore * myHelper;
};

///////////////////////////////////////////////////////////////////////
SSLeptonTriggerScaleFactors::SSLeptonTriggerScaleFactors (HelperLeptonCore *in): myHelper(in) {

  branches["twoMuonTriggerSF"] = BranchInfo<double>("twoMuonTriggerSF");
  branches["twoElectronTriggerSF"] = BranchInfo<double>("twoElectronTriggerSF");
  branches["muonElectronTriggerSF"] = BranchInfo<double>("muonElectronTriggerSF");
  branches["triggerSF"] = BranchInfo<double>("triggerSF");

  this->resetVal = KinematicVariableConstants::DOUBLE_INIT;
}

void SSLeptonTriggerScaleFactors::evaluate () {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  BEANhelper * beanHelper = &(myHelper->bHelp);

  double muonSF = 1.0, electronSF = 1.0, muonElectronSF = 1.0, triggerSF = 1.0;

  unsigned numTightLoosePreselectedMuons = this->blocks->tightLoosePreselectedMuonCollection->size();
  unsigned numTightLoosePreselectedElectrons = this->blocks->tightLoosePreselectedElectronCollection->size();
  unsigned numTightLoosePreselectedLeptons = this->blocks->tightLoosePreselectedLeptonCollection->size();

  // I'm creating a new collection because tightLoosePreselected is sorted by pT
  BNmuonCollection bestMuons;
  bestMuons.insert(bestMuons.end(), this->blocks->tightMuonCollection->begin(), this->blocks->tightMuonCollection->end());
  bestMuons.insert(bestMuons.end(), this->blocks->looseMuonCollection->begin(), this->blocks->looseMuonCollection->end());
  bestMuons.insert(bestMuons.end(), this->blocks->preselectedMuonCollection->begin(), this->blocks->preselectedMuonCollection->end());

  BNelectronCollection bestElectrons;
  bestElectrons.insert(bestElectrons.end(), this->blocks->tightElectronCollection->begin(), this->blocks->tightElectronCollection->end());
  bestElectrons.insert(bestElectrons.end(), this->blocks->looseElectronCollection->begin(), this->blocks->looseElectronCollection->end());
  bestElectrons.insert(bestElectrons.end(), this->blocks->preselectedElectronCollection->begin(), this->blocks->preselectedElectronCollection->end());

  if (numTightLoosePreselectedMuons >= 2) {
    muonSF = beanHelper->GetDoubleMuonTriggerSF(bestMuons.at(0), bestMuons.at(1));
  }

  if (numTightLoosePreselectedElectrons >= 2) {
    electronSF = beanHelper->GetDoubleElectronTriggerSF(bestElectrons.at(0), bestElectrons.at(1));
  }

  if (numTightLoosePreselectedMuons >=1 && numTightLoosePreselectedElectrons >= 1) {
    muonElectronSF = beanHelper->GetMuonEleTriggerSF (bestMuons.at(0), bestElectrons.at(0));
  }

  branches["twoMuonTriggerSF"].branchVal = muonSF;
  branches["twoElectronTriggerSF"].branchVal = electronSF;
  branches["muonElectronTriggerSF"].branchVal = muonElectronSF;
  branches["triggerSF"].branchVal = muonSF * electronSF * muonElectronSF;

}

bool SSLeptonTriggerScaleFactors::passCut() {
  return true;
}

#endif
