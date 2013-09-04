
#ifndef _LeptonTriggerScaleFactors_h
#define _LeptonTriggerScaleFactors_h



///////////////////////////////////////////////////////
//
//
//    Lepton Trigger Scale factors
//    Right now only for lepton trigger
//
////////////////////////////////////////////////////

class LeptonTriggerScaleFactors: public KinematicVariable<double> {

public:

  // for now you have to specify your selection
  LeptonTriggerScaleFactors(HelperLeptonCore *in );


  void evaluate ();
  bool passCut ();

  HelperLeptonCore * myHelper;

  

};

///////////////////////////////////////////////////////////////////////

LeptonTriggerScaleFactors::LeptonTriggerScaleFactors  (HelperLeptonCore *in) :  
  myHelper(in)

{

  branches["TwoMuonTriggerSF"] = BranchInfo<double>("TwoMuonTriggerSF");
  branches["TwoElectronTriggerSF"] = BranchInfo<double>("TwoElectronTriggerSF");
  branches["MuonElectronTriggerSF"] = BranchInfo<double>("MuonElectronTriggerSF");

  this->resetVal = KinematicVariableConstants::DOUBLE_INIT;
   
}

void LeptonTriggerScaleFactors::evaluate () {
  
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  BEANhelper * beanHelper = &(myHelper->bHelp);
  
  double muonSF = 1.0, electronSF = 1.0, muonElectronSF= 1.0;

  unsigned numTightMuons = this->blocks->tightMuonCollection->size();
  unsigned numLooseMuons = this->blocks->looseMuonCollection->size();
  unsigned numTightElectrons = this->blocks->tightElectronCollection->size();
  unsigned numLooseElectrons = this->blocks->looseElectronCollection->size();

  ////////////////////////////////////////////////////////
  // 
  // If you have two muons, evaluate the muon trigger sf
  // If you have two electrons
  //
  /////////////////////////////////////////////////////////

  if (numTightMuons + numLooseMuons >= 2) {

    BNmuonCollection bestMuons;
    
    for (BNmuonCollection::iterator iMuon = this->blocks->tightMuonCollection->begin();
         iMuon != this->blocks->tightMuonCollection->end();
         iMuon ++ ){
      bestMuons.push_back((*iMuon));
    }

    for (BNmuonCollection::iterator iMuon = this->blocks->looseMuonCollection->begin();
         iMuon != this->blocks->looseMuonCollection->end();
         iMuon ++ ){
      bestMuons.push_back((*iMuon));      
    }

    muonSF = beanHelper->GetDoubleMuonTriggerSF(bestMuons.at(0), bestMuons.at(1));    
  }// end if you have 2 muons
  

  if (numTightElectrons + numLooseElectrons >=2 ){

    BNelectronCollection bestElectrons;
    for (BNelectronCollection::iterator iElectron = this->blocks->tightElectronCollection->begin();
         iElectron != this->blocks->tightElectronCollection->end();
         iElectron ++ ){
      bestElectrons.push_back((*iElectron));
    }
  
    for (BNelectronCollection::iterator iElectron = this->blocks->looseElectronCollection->begin();
         iElectron != this->blocks->looseElectronCollection->end();
         iElectron ++ ){
      bestElectrons.push_back((*iElectron));
    }

    electronSF = beanHelper->GetDoubleElectronTriggerSF(bestElectrons.at(0), bestElectrons.at(1));
  }// end if you have two electrons


  // if you have some combiantion of muons and electrons
  if ( (numTightElectrons >=1 && numTightMuons >=1)
       || (numTightElectrons >=1 && numLooseMuons >=1 )
       || (numTightMuons >=1 && numLooseElectrons >=1) ){

    // It is tempting to loop through the leptons
    // But this will not get you the right behavior.
    // You need to pick the best muon for the first argument
    // then you need to pick the best electron for the second argument
    
    //     BNleptonCollection bestLeps;
    
    //     for (BNleptonCollection::iterator iLep = this->blocks->leptonCollection->begin();
    //          iLep != this->blocks->leptonCollection->end();
    //          iLep ++ ){
    //       bestLeps.push_back((*iLep));
    //     }
    
    //     for (BNleptonCollection::iterator iLep = this->blocks->looseLeptonCollection->begin();
    //          iLep != this->blocks->looseLeptonCollection->end();
    //          iLep ++ ){
    //       bestLeps.push_back((*iLep));
    //     }


    BNmuonCollection bestMuons;
    
    for (BNmuonCollection::iterator iMuon = this->blocks->tightMuonCollection->begin();
         iMuon != this->blocks->tightMuonCollection->end();
         iMuon ++ ){
      bestMuons.push_back((*iMuon));
    }

    for (BNmuonCollection::iterator iMuon = this->blocks->looseMuonCollection->begin();
         iMuon != this->blocks->looseMuonCollection->end();
         iMuon ++ ){
      bestMuons.push_back((*iMuon));      
    }

    BNelectronCollection bestElectrons;

    for (BNelectronCollection::iterator iElectron = this->blocks->tightElectronCollection->begin();
         iElectron != this->blocks->tightElectronCollection->end();
         iElectron ++ ){
      bestElectrons.push_back((*iElectron));
    }
  
    for (BNelectronCollection::iterator iElectron = this->blocks->looseElectronCollection->begin();
         iElectron != this->blocks->looseElectronCollection->end();
         iElectron ++ ){
      bestElectrons.push_back((*iElectron));
    }
    
    muonElectronSF = beanHelper->GetMuonEleTriggerSF ( bestMuons.at(0), bestElectrons.at(0));
    
  }// end if you have muons + electrons


  
  
  branches["TwoMuonTriggerSF"].branchVal = muonSF;
  branches["TwoElectronTriggerSF"].branchVal = electronSF;
  branches["MuonElectronTriggerSF"].branchVal = muonElectronSF;
  

}


bool LeptonTriggerScaleFactors::passCut() {

  return true;

}

#endif
