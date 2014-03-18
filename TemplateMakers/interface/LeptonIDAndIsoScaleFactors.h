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
                             electronID::electronID el,
                             BNmuonCollection **tightMuons,
                             BNmuonCollection **looseMuons,
                             BNelectronCollection **tightElectrons,
                             BNelectronCollection **looseElectrons);
  void evaluate ();

  HelperLeptonCore * myHelper;
  muonID::muonID muonTightID;
  muonID::muonID muonLooseID;
  electronID::electronID electronTightID;
  electronID::electronID electronLooseID;
  BNmuonCollection **tightMuons;
  BNmuonCollection **looseMuons;
  BNelectronCollection **tightElectrons;
  BNelectronCollection **looseElectrons;

};

///////////////////////////////////////////////////////////////////////
LeptonIDAndIsoScaleFactors::LeptonIDAndIsoScaleFactors  (HelperLeptonCore *in,
                                                         muonID::muonID mt,
                                                         muonID::muonID ml,
                                                         electronID::electronID et,
                                                         electronID::electronID el,
                                                         BNmuonCollection **tightMuons,
                                                         BNmuonCollection **looseMuons,
                                                         BNelectronCollection **tightElectrons,
                                                         BNelectronCollection **looseElectrons):
  myHelper(in),
  muonTightID(mt),
  muonLooseID(ml),
  electronTightID(et),
  electronLooseID(el),
  tightMuons(tightMuons),
  looseMuons(looseMuons),
  tightElectrons(tightElectrons),
  looseElectrons(looseElectrons)

{

  branches["lepIDAndIsoSF"] = BranchInfo<double>("lepIDAndIsoSF");

  this->resetVal = KinematicVariableConstants::DOUBLE_INIT;
}

void LeptonIDAndIsoScaleFactors::evaluate () {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  BEANhelper * beanHelper = &(myHelper->bHelp);

  double IDAndIsoSF = 1.0;

  for (BNmuonCollection::iterator iMuon = (*tightMuons)->begin();
       iMuon != (*tightMuons)->end();
       iMuon ++ ){
    IDAndIsoSF *= beanHelper->GetMuonSF((*iMuon), muonTightID);
  }

  for (BNmuonCollection::iterator iMuon = (*looseMuons)->begin();
       iMuon != (*looseMuons)->end();
       iMuon ++ ){
    IDAndIsoSF *= beanHelper->GetMuonSF((*iMuon), muonLooseID);
  }

  for (BNelectronCollection::iterator iElectron = (*tightElectrons)->begin();
       iElectron != (*tightElectrons)->end();
       iElectron ++ ){
    IDAndIsoSF *= beanHelper->GetElectronSF((*iElectron), electronTightID);
  }

  for (BNelectronCollection::iterator iElectron = (*looseElectrons)->begin();
       iElectron != (*looseElectrons)->end();
       iElectron ++ ){
    IDAndIsoSF *= beanHelper->GetElectronSF((*iElectron), electronLooseID);
  }

  branches["lepIDAndIsoSF"].branchVal = IDAndIsoSF;
}

#endif
