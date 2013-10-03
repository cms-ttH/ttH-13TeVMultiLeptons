#ifndef _LeptonIDAndIsoScaleFactors_h
#define _LeptonIDAndIsoScaleFactors_h

///////////////////////////////////////////////////////
//
//    Lepton Scale factors
//
////////////////////////////////////////////////////

class LeptonIDAndIsoScaleFactors: public KinematicVariable<double> {

public:

  // for now you have to specify your selection
  LeptonIDAndIsoScaleFactors(HelperLeptonCore *in,
                     muonID::muonID mt,
                     muonID::muonID ml,
                     electronID::electronID et,
                     electronID::electronID el);
  void evaluate ();

  HelperLeptonCore * myHelper;
  muonID::muonID muonTightID;
  muonID::muonID muonLooseID;
  electronID::electronID electronTightID;
  electronID::electronID electronLooseID;

};

///////////////////////////////////////////////////////////////////////
LeptonIDAndIsoScaleFactors::LeptonIDAndIsoScaleFactors  (HelperLeptonCore *in,
                                         muonID::muonID mt,
                                         muonID::muonID ml,
                                         electronID::electronID et,
                                         electronID::electronID el):
  myHelper(in),
  muonTightID(mt),
  muonLooseID(ml),
  electronTightID(et),
  electronLooseID(el)

{

  branches["lepIDAndIsoSF"] = BranchInfo<double>("lepIDAndIsoSF");

  this->resetVal = KinematicVariableConstants::DOUBLE_INIT;
}

void LeptonIDAndIsoScaleFactors::evaluate () {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  BEANhelper * beanHelper = &(myHelper->bHelp);

  double IDAndIsoSF = 1.0;

  for (BNmuonCollection::iterator iMuon = this->blocks->tightMuonCollection->begin();
       iMuon != this->blocks->tightMuonCollection->end();
       iMuon ++ ){
    IDAndIsoSF *= beanHelper->GetMuonSF((*iMuon), muonTightID);
  }

  for (BNmuonCollection::iterator iMuon = this->blocks->looseMuonCollection->begin();
       iMuon != this->blocks->looseMuonCollection->end();
       iMuon ++ ){
    IDAndIsoSF *= beanHelper->GetMuonSF((*iMuon), muonLooseID);
  }

  for (BNelectronCollection::iterator iElectron = this->blocks->tightElectronCollection->begin();
       iElectron != this->blocks->tightElectronCollection->end();
       iElectron ++ ){
    IDAndIsoSF *= beanHelper->GetElectronSF((*iElectron), electronTightID);
  }

  for (BNelectronCollection::iterator iElectron = this->blocks->looseElectronCollection->begin();
       iElectron != this->blocks->looseElectronCollection->end();
       iElectron ++ ){
    IDAndIsoSF *= beanHelper->GetElectronSF((*iElectron), electronLooseID);
  }

  branches["lepIDAndIsoSF"].branchVal = IDAndIsoSF;
}

#endif
