#ifndef _LepTrackCharges_h
#define _LepTrackCharges_h

#include  "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"

//
//  Loops over tightLoosePreselected leptons and saves the track charge for each. I'm not using the
//  generic object approach because the generic cut wouldn't work for cutting on SS.
//  I'm using the tightLoosePreselected lepton collection because that's what the CERN goup uses--
//  we should probably make the input collection and branch name string into function parameters,
//  so this can be used more generally. --AW
//

class LepTrackCharges: public KinematicVariable<int> {

public:
    unsigned int maxLeptons;
    string chargeCut;

    LepTrackCharges(unsigned int max);
    void evaluate ();
    void setCut (string cut);
    bool passCut ();
};

LepTrackCharges::LepTrackCharges (unsigned int max): maxLeptons(max) {
    this->resetVal = KinematicVariableConstants::INT_INIT;

    for (unsigned int i=0; i<maxLeptons; i++) {
        TString branchName = Form("all_leptons_by_pt_%d_tkCharge", i+1);
        branches[branchName] = BranchInfo<int>(branchName);
        branches[branchName].branchVal = this->resetVal;
    }
}

void LepTrackCharges::evaluate () {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  //--------
  BNleptonCollection * tightLoosePreselectedLeptons = this->blocks->tightLoosePreselectedLeptonCollection;
  TString branchName;
  unsigned loopMax = (unsigned (maxLeptons) < tightLoosePreselectedLeptons->size()) ? unsigned(maxLeptons) : tightLoosePreselectedLeptons->size();

  for (unsigned int i = 0; i < loopMax; i++) {
      BNlepton * iLepton = tightLoosePreselectedLeptons->at(i);
      branchName = Form("all_leptons_by_pt_%d_tkCharge", i+1);
      branches[branchName].branchVal = iLepton->tkCharge;
  }
}

void LepTrackCharges::setCut(string cut) {
    chargeCut = cut;
}

bool LepTrackCharges::passCut() {
    evaluate();
    if ((chargeCut == "SS") && (branches["all_leptons_by_pt_1_tkCharge"].branchVal * branches["all_leptons_by_pt_2_tkCharge"].branchVal) > 0) {
        return true;
    }
    else if ((chargeCut == "OS") && (branches["all_leptons_by_pt_1_tkCharge"].branchVal * branches["all_leptons_by_pt_2_tkCharge"].branchVal) < 0) {
        return true;
    }

    return false;
}
#endif 
