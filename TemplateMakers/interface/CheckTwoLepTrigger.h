
#ifndef _CheckTwoLepTrigger_h
#define _CheckTwoLepTrigger_h


#include  "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"
#include <set>
#include "TRegexp.h"

//
//
//  Checks the double lepton triggers
//  Fills a variable for each class of triggers
//  Also fills a variable that is an 'or' of 
//  the three classes
//
//
//

class CheckTwoLepTrigger: public KinematicVariable<int> {

public:
  
  CheckTwoLepTrigger(HelperLeptonCore * in);

  void evaluate ();
  bool passCut ();

  std::string removeVersion (std::string);
  
  HelperLeptonCore * myHelper;

  std::set <string> doubleMuonTriggerNames;
  std::set <string> doubleEleTriggerNames;
  std::set <string> muonEleTriggerNames;


  
};

CheckTwoLepTrigger::CheckTwoLepTrigger (HelperLeptonCore * in):
  myHelper(in)
{

  this->resetVal = KinematicVariableConstants::INT_INIT;

  branches["isDoubleMuTriggerPass"] = BranchInfo<int>("isDoubleMuTriggerPass");
  branches["isDoubleElectronTriggerPass"] = BranchInfo<int>("isDoubleElectronTriggerPass");
  branches["isMuEGTriggerPass"] = BranchInfo<int> ("isMuEGTriggerPass");

  if( myHelper->analysisYear == "2011"){
    doubleMuonTriggerNames.insert("HLT_DoubleMu7_v");
    doubleMuonTriggerNames.insert("HLT_Mu13_Mu8_v");
    doubleMuonTriggerNames.insert("HLT_Mu17_Mu8_v");
    
    doubleEleTriggerNames.insert("HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v");
    doubleEleTriggerNames.insert("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
    doubleEleTriggerNames.insert("HLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_v");
   
     muonEleTriggerNames.insert("HLT_Mu17_Ele8_CaloIdL_v");
     muonEleTriggerNames.insert("HLT_Mu8_Ele17_CaloIdL_v");
     muonEleTriggerNames.insert("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_v");
     muonEleTriggerNames.insert("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_v");
     
  }
  else if( myHelper->analysisYear == "2012_52x" || myHelper->analysisYear == "2012_53x") {
    doubleMuonTriggerNames.insert("HLT_Mu17_Mu8_v");
    doubleMuonTriggerNames.insert("HLT_Mu17_TkMu8_v");
    doubleEleTriggerNames.insert("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");

    muonEleTriggerNames.insert("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
    muonEleTriggerNames.insert("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
    //     mc_hlt_MET_trigger_collection.push_back("HLT_DiCentralPFJet30_PFMET80_BTagCSV07_v");
    //     mc_hlt_MET_trigger_collection.push_back("HLT_MET120_HBHENoiseCleaned_v");
    //     mc_hlt_MET_trigger_collection.push_back("HLT_MET200_v");
    //     mc_hlt_MET_trigger_collection.push_back("HLT_PFMET150_v");
  }

  

  
}

void CheckTwoLepTrigger::evaluate () {

  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  // algorithm
  // for each triger in the event's trigger table
  //   remove the version number from the name
  //   see if you can find the name w/o the version
  //   in your set of candidate triggers
  //
  //

  bool twoMuonTrigFired = false;
  bool twoEleTrigFired = false;
  bool muonEleTrigFired = false;

  
  for ( BNtriggerCollection::iterator iTrig = blocks->hltCollection->begin();
        iTrig != blocks->hltCollection->end();
        iTrig ++) {

    std::string trigName = removeVersion(iTrig->name);

    if (doubleMuonTriggerNames.find(trigName) != doubleMuonTriggerNames.end()) {

      //------------- 
      //cout << "Found a match for trigger " << trigName
      //     << " pass = " << iTrig->pass << endl;
      
      if (iTrig->pass == 1) {
        twoMuonTrigFired = true;
      }

      //---------------
      
    } // end if 2 muon trigger

    if (doubleEleTriggerNames.find(trigName) != doubleEleTriggerNames.end()) {
      if (iTrig->pass == 1)
        twoEleTrigFired = true;
    }// end if 2 ele trigger


    if (muonEleTriggerNames.find(trigName) != muonEleTriggerNames.end()) {
      if (iTrig->pass ==1)
        muonEleTrigFired = true;
    }
    

  }// end for each trigger


  branches["isDoubleMuTriggerPass"].branchVal = twoMuonTrigFired ? 1 : 0;
  branches["isDoubleElectronTriggerPass"].branchVal = twoEleTrigFired ? 1 : 0;
  branches["isMuEGTriggerPass"].branchVal = muonEleTrigFired ? 1 : 0;
    
  
}

std::string CheckTwoLepTrigger::removeVersion (std::string input) {

    TRegexp version("_v[0-9]+");
    TString tempName (input.c_str());
    unsigned removeAfter = tempName.Index(version);
    removeAfter+=2;
    tempName.Remove(removeAfter);
    return std::string(tempName.Data());
    
}

bool CheckTwoLepTrigger::passCut() {

  evaluate();
  
  if (branches["isDoubleMuTriggerPass"].branchVal == 1
      || branches["isDoubleElectronTriggerPass"].branchVal == 1
      || branches["isMuEGTriggerPass"].branchVal == 1)
    return true;
  return false;

}



#endif 
