#ifndef _LepMVA_h
#define _LepMVA_h

#include  "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"

//
//  Loops over selected leptons and saves the lepMVA value for each.  For now I'm attaching to tree inside the constructor
//  instead of in a separate function-- I'm not sure we'd ever want this value without saving it. --AW
//

class LepMVAs: public KinematicVariable<double> {

public:
    unsigned int maxLeptonsTight;
    unsigned int maxLeptonsLoose;
    unsigned int maxLeptonsPreselected;
    unsigned int maxLeptonsTightLoose;
    unsigned int maxLeptonsLoosePreselected;
    unsigned int maxLeptonsTightLoosePreselected;
    HelperLeptonCore * myHelper;

  LepMVAs(HelperLeptonCore *in, int maxTight, int maxLoose, int maxPreselected, int maxTightLoose, int maxLoosePreselected, int maxTightLoosePreselected);
    void evaluate ();
  
};

LepMVAs::LepMVAs (HelperLeptonCore *in, int maxTight, int maxLoose, int maxPreselected, int maxTightLoose, int maxLoosePreselected, int maxTightLoosePreselected):
  myHelper(in),
  maxLeptonsTight(maxTight),
  maxLeptonsLoose(maxLoose),
  maxLeptonsPreselected(maxPreselected),
  maxLeptonsTightLoose(maxTightLoose),
  maxLeptonsLoosePreselected(maxLoosePreselected),
  maxLeptonsTightLoosePreselected(maxTightLoosePreselected)
{
    this->resetVal = KinematicVariableConstants::DOUBLE_INIT;
    
    for (unsigned int i=0; i<maxLeptonsTight; i++) {
        TString branchName = Form("tight_leptons_by_pt_%d_lepMVA", i+1);
        branches[branchName] = BranchInfo<double>(branchName);
        branches[branchName].branchVal = this->resetVal;
    }

    for (unsigned int i=0; i<maxLeptonsLoose; i++) {
        TString branchName = Form("loose_leptons_by_pt_%d_lepMVA", i+1);
        branches[branchName] = BranchInfo<double>(branchName);
        branches[branchName].branchVal = this->resetVal;
    }

    for (unsigned int i=0; i<maxLeptonsPreselected; i++) {
        TString branchName = Form("preselected_leptons_by_pt_%d_lepMVA", i+1);
        branches[branchName] = BranchInfo<double>(branchName);
        branches[branchName].branchVal = this->resetVal;
    }

    for (unsigned int i=0; i<maxLeptonsTightLoose; i++) {
        TString branchName = Form("tightLoose_leptons_by_pt_%d_lepMVA", i+1);
        branches[branchName] = BranchInfo<double>(branchName);
        branches[branchName].branchVal = this->resetVal;
    }

    for (unsigned int i=0; i<maxLeptonsLoosePreselected; i++) {
        TString branchName = Form("loosePreselected_leptons_by_pt_%d_lepMVA", i+1);
        branches[branchName] = BranchInfo<double>(branchName);
        branches[branchName].branchVal = this->resetVal;
    }

    for (unsigned int i=0; i<maxLeptonsTightLoosePreselected; i++) {
        TString branchName = Form("all_leptons_by_pt_%d_lepMVA", i+1);
        branches[branchName] = BranchInfo<double>(branchName);
        branches[branchName].branchVal = this->resetVal;
    }
}

void LepMVAs::evaluate () {

  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  //--------

  BNleptonCollection * tightLeptons = this->blocks->tightLeptonCollection;
  BNleptonCollection * looseLeptons = this->blocks->looseLeptonCollection;
  BNleptonCollection * preselectedLeptons = this->blocks->preselectedLeptonCollection;
  BNleptonCollection * tightLooseLeptons = this->blocks->tightLooseLeptonCollection;
  BNleptonCollection * loosePreselectedLeptons = this->blocks->loosePreselectedLeptonCollection;
  BNleptonCollection * tightLoosePreselectedLeptons = this->blocks->tightLoosePreselectedLeptonCollection;
  BEANhelper * beanHelper = &(myHelper->bHelp);
  TString branchName;

  unsigned loopMaxTight = (unsigned (maxLeptonsTight) < tightLeptons->size())
    ? unsigned(maxLeptonsTight) : tightLeptons->size();
  unsigned loopMaxLoose = (unsigned (maxLeptonsLoose) < looseLeptons->size())
    ? unsigned(maxLeptonsLoose) : looseLeptons->size();
  unsigned loopMaxPreselected = (unsigned (maxLeptonsPreselected) < preselectedLeptons->size())
    ? unsigned(maxLeptonsPreselected) : preselectedLeptons->size();
  unsigned loopMaxTightLoose = (unsigned (maxLeptonsTightLoose) < tightLooseLeptons->size())
    ? unsigned(maxLeptonsTightLoose) : tightLooseLeptons->size();
  unsigned loopMaxLoosePreselected = (unsigned (maxLeptonsLoosePreselected) < loosePreselectedLeptons->size())
    ? unsigned(maxLeptonsLoosePreselected) : loosePreselectedLeptons->size();
  unsigned loopMaxTightLoosePreselected = (unsigned (maxLeptonsTightLoosePreselected) < tightLoosePreselectedLeptons->size())
    ? unsigned(maxLeptonsTightLoosePreselected) : tightLoosePreselectedLeptons->size();

  for (unsigned int i=0; i<loopMaxTight; i++) {
      BNlepton * iLepton = tightLeptons->at(i);
      branchName = Form("tight_leptons_by_pt_%d_lepMVA", i+1);

      if (iLepton->isElectron) {
          branches[branchName].branchVal = beanHelper->GetElectronLepMVA(*(BNelectron*)iLepton, this->blocks->jetsForLepMVACollection);
      } else {
          branches[branchName].branchVal = beanHelper->GetMuonLepMVA(*(BNmuon*)iLepton, this->blocks->jetsForLepMVACollection);
      }      
  }

  for (unsigned int i=0; i<loopMaxLoose; i++) {
      BNlepton * iLepton = looseLeptons->at(i);
      branchName = Form("loose_leptons_by_pt_%d_lepMVA", i+1);

      if (iLepton->isElectron) {
          branches[branchName].branchVal = beanHelper->GetElectronLepMVA(*(BNelectron*)iLepton, this->blocks->jetsForLepMVACollection);
      } else {
          branches[branchName].branchVal = beanHelper->GetMuonLepMVA(*(BNmuon*)iLepton, this->blocks->jetsForLepMVACollection);
      }      
  }

  for (unsigned int i=0; i<loopMaxPreselected; i++) {
      BNlepton * iLepton = preselectedLeptons->at(i);
      branchName = Form("preselected_leptons_by_pt_%d_lepMVA", i+1);

      if (iLepton->isElectron) {
          branches[branchName].branchVal = beanHelper->GetElectronLepMVA(*(BNelectron*)iLepton, this->blocks->jetsForLepMVACollection);
      } else {
          branches[branchName].branchVal = beanHelper->GetMuonLepMVA(*(BNmuon*)iLepton, this->blocks->jetsForLepMVACollection);
      }      
  }

  for (unsigned int i=0; i<loopMaxTightLoose; i++) {
      BNlepton * iLepton = tightLooseLeptons->at(i);
      branchName = Form("tightLoose_leptons_by_pt_%d_lepMVA", i+1);

      if (iLepton->isElectron) {
          branches[branchName].branchVal = beanHelper->GetElectronLepMVA(*(BNelectron*)iLepton, this->blocks->jetsForLepMVACollection);
      } else {
          branches[branchName].branchVal = beanHelper->GetMuonLepMVA(*(BNmuon*)iLepton, this->blocks->jetsForLepMVACollection);
      }      
  }

  for (unsigned int i=0; i<loopMaxLoosePreselected; i++) {
      BNlepton * iLepton = loosePreselectedLeptons->at(i);
      branchName = Form("loosePreselected_leptons_by_pt_%d_lepMVA", i+1);

      if (iLepton->isElectron) {
          branches[branchName].branchVal = beanHelper->GetElectronLepMVA(*(BNelectron*)iLepton, this->blocks->jetsForLepMVACollection);
      } else {
          branches[branchName].branchVal = beanHelper->GetMuonLepMVA(*(BNmuon*)iLepton, this->blocks->jetsForLepMVACollection);
      }      
  }

  for (unsigned int i=0; i<loopMaxTightLoosePreselected; i++) {
      BNlepton * iLepton = tightLoosePreselectedLeptons->at(i);
      branchName = Form("all_leptons_by_pt_%d_lepMVA", i+1);

      if (iLepton->isElectron) {
          branches[branchName].branchVal = beanHelper->GetElectronLepMVA(*(BNelectron*)iLepton, this->blocks->jetsForLepMVACollection);
      } else {
          branches[branchName].branchVal = beanHelper->GetMuonLepMVA(*(BNmuon*)iLepton, this->blocks->jetsForLepMVACollection);
      }      
  }

}


#endif 
