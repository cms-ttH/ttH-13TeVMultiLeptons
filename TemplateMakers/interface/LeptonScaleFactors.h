
#ifndef _LeptonScaleFactors_h
#define _LeptonScaleFactors_h



///////////////////////////////////////////////////////
//
//
//    Lepton Scale factors
//
//
////////////////////////////////////////////////////

class LeptonScaleFactors: public KinematicVariable<double> {

public:

  // for now you have to specify your selection
  LeptonScaleFactors(HelperLeptonCore *in,
                     muonID::muonID mt,
                     muonID::muonID ml,
                     electronID::electronID et,
                     electronID::electronID el);


  void evaluate ();
  bool passCut ();

  HelperLeptonCore * myHelper;

  muonID::muonID muonTightID;
  muonID::muonID muonLooseID;

  electronID::electronID electronTightID;
  electronID::electronID electronLooseID;
  

};

///////////////////////////////////////////////////////////////////////

LeptonScaleFactors::LeptonScaleFactors  (HelperLeptonCore *in,
                                         muonID::muonID mt,
                                         muonID::muonID ml,
                                         electronID::electronID et,
                                         electronID::electronID el) :  
  myHelper(in),
  muonTightID(mt),
  muonLooseID(ml),
  electronTightID(et),
  electronLooseID(el)

{

  branches["lepTotalSF"] = BranchInfo<double>("lepTotalSF");

  this->resetVal = KinematicVariableConstants::DOUBLE_INIT;
  
}

void LeptonScaleFactors::evaluate () {
  
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  BEANhelper * beanHelper = &(myHelper->bHelp);
  
  double totalSF = 1.0;

  for (BNmuonCollection::iterator iMuon = this->blocks->tightMuonCollection->begin();
       iMuon != this->blocks->tightMuonCollection->end();
       iMuon ++ ){
    totalSF *= beanHelper->GetMuonSF((*iMuon), muonTightID);
  }

  for (BNmuonCollection::iterator iMuon = this->blocks->looseMuonCollection->begin();
       iMuon != this->blocks->looseMuonCollection->end();
       iMuon ++ ){
    totalSF *= beanHelper->GetMuonSF((*iMuon), muonLooseID);
  }

  for (BNelectronCollection::iterator iElectron = this->blocks->tightElectronCollection->begin();
       iElectron != this->blocks->tightElectronCollection->end();
       iElectron ++ ){
    totalSF *= beanHelper->GetElectronSF((*iElectron), electronTightID);
  }
  
  for (BNelectronCollection::iterator iElectron = this->blocks->looseElectronCollection->begin();
       iElectron != this->blocks->looseElectronCollection->end();
       iElectron ++ ){
    totalSF *= beanHelper->GetElectronSF((*iElectron), electronLooseID);
  }
  
  branches["lepTotalSF"].branchVal = totalSF;

}


bool LeptonScaleFactors::passCut() {

  return true;

}

#endif
