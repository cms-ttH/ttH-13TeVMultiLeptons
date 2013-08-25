
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

  electronID::electronID eleTightID;
  electronID::electronID eleLooseID;
  

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
  eleTightID(et),
  eleLooseID(el)

{

  branches["lepTotalSF"] = BranchInfo<double>("lepTotalSF");
  
   
}

void LeptonScaleFactors::evaluate () {
  
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  BEANhelper * beanHelper = &(myHelper->bHelp);
  
  double totalSF = 1.0;

  for (BNmuonCollection::iterator iMuon = this->blocks->muonCollection->begin();
       iMuon != this->blocks->muonCollection->end();
       iMuon ++ ){
    totalSF *= beanHelper->GetMuonSF((*iMuon), muonTightID);
  }

  for (BNmuonCollection::iterator iMuon = this->blocks->looseMuonCollection->begin();
       iMuon != this->blocks->looseMuonCollection->end();
       iMuon ++ ){
    totalSF *= beanHelper->GetMuonSF((*iMuon), muonLooseID);
  }

  for (BNelectronCollection::iterator iEle = this->blocks->eleCollection->begin();
       iEle != this->blocks->eleCollection->end();
       iEle ++ ){
    totalSF *= beanHelper->GetElectronSF((*iEle), eleTightID);
  }
  
  for (BNelectronCollection::iterator iEle = this->blocks->looseEleCollection->begin();
       iEle != this->blocks->looseEleCollection->end();
       iEle ++ ){
    totalSF *= beanHelper->GetElectronSF((*iEle), eleLooseID);
  }
  
  branches["lepTotalSF"].branchVal = totalSF;

}


bool LeptonScaleFactors::passCut() {

  return true;

}

#endif
