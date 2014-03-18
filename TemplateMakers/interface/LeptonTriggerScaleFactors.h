#ifndef _LeptonTriggerScaleFactors_h
#define _LeptonTriggerScaleFactors_h

///////////////////////////////////////////////////////
//
//    Lepton Trigger Scale factors
//    Right now only for lepton trigger
//
////////////////////////////////////////////////////

class LeptonTriggerScaleFactors: public KinematicVariable<double> {

public:
  // for now you have to specify your selection
  LeptonTriggerScaleFactors(HelperLeptonCore *in,
                            BNmuonCollection **_tightMuons,
                            BNmuonCollection **_looseMuons,
                            BNmuonCollection **_preselectedMuons,
                            BNelectronCollection **_tightElectrons,
                            BNelectronCollection **_looseElectrons,
                            BNelectronCollection **_preselectedElectrons);
  void evaluate ();
  bool passCut ();

  HelperLeptonCore * myHelper;
  BNmuonCollection **tightMuons;
  BNmuonCollection **looseMuons;
  BNmuonCollection **preselectedMuons;
  BNelectronCollection **tightElectrons;
  BNelectronCollection **looseElectrons;
  BNelectronCollection **preselectedElectrons;
};

///////////////////////////////////////////////////////////////////////
LeptonTriggerScaleFactors::LeptonTriggerScaleFactors (HelperLeptonCore *in,
                                                      BNmuonCollection **_tightMuons,
                                                      BNmuonCollection **_looseMuons,
                                                      BNmuonCollection **_preselectedMuons,
                                                      BNelectronCollection **_tightElectrons,
                                                      BNelectronCollection **_looseElectrons,
                                                      BNelectronCollection **_preselectedElectrons) :
  myHelper(in),
  tightMuons(_tightMuons),
  looseMuons(_looseMuons),
  preselectedMuons(_preselectedMuons),
  tightElectrons(_tightElectrons),
  looseElectrons(_looseElectrons),
  preselectedElectrons(_preselectedElectrons)
{

  branches["twoMuonTriggerSF"] = BranchInfo<double>("twoMuonTriggerSF");
  branches["twoElectronTriggerSF"] = BranchInfo<double>("twoElectronTriggerSF");
  branches["muonElectronTriggerSF"] = BranchInfo<double>("muonElectronTriggerSF");

  this->resetVal = KinematicVariableConstants::DOUBLE_INIT;
}

void LeptonTriggerScaleFactors::evaluate () {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  BEANhelper * beanHelper = &(myHelper->bHelp);

  double muonSF = 1.0, electronSF = 1.0, muonElectronSF = 1.0;
  //double triggerSF = 1.0;

  unsigned numTightLoosePreselectedMuons = (*tightMuons)->size()+(*looseMuons)->size()+(*preselectedMuons)->size();
  unsigned numTightLoosePreselectedElectrons = (*tightElectrons)->size()+(*looseElectrons)->size()+(*preselectedElectrons)->size();
  //unsigned numTightLoosePreselectedLeptons = this->blocks->tightLoosePreselectedLeptonCollection->size();

  // I'm creating a new collection because tightLoosePreselected is sorted by pT
  BNmuonCollection bestMuons;
  bestMuons.insert(bestMuons.end(), (*tightMuons)->begin(), (*tightMuons)->end());
  bestMuons.insert(bestMuons.end(), (*looseMuons)->begin(), (*looseMuons)->end());
  bestMuons.insert(bestMuons.end(), (*preselectedMuons)->begin(), (*preselectedMuons)->end());

  BNelectronCollection bestElectrons;
  bestElectrons.insert(bestElectrons.end(), (*tightElectrons)->begin(), (*tightElectrons)->end());
  bestElectrons.insert(bestElectrons.end(), (*looseElectrons)->begin(), (*looseElectrons)->end());
  bestElectrons.insert(bestElectrons.end(), (*preselectedElectrons)->begin(), (*preselectedElectrons)->end());

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

}

bool LeptonTriggerScaleFactors::passCut() {
  return true;
}

#endif
