#ifndef _LepGenInfo_h
#define _LepGenInfo_h

#include  "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"

//
//  Loops over selected leptons and saves generator level info for each.  For now I'm attaching to tree inside the constructor
//  instead of in a separate function-- I'm not sure we'd ever want this value without saving it. --AW
//

class LepGenInfos: public KinematicVariable<double> {

public:
    unsigned int maxLeptonsTight;
    unsigned int maxLeptonsLoose;
    unsigned int maxLeptonsPreselected;
    unsigned int maxLeptonsTightLoose;
    unsigned int maxLeptonsLoosePreselected;
    unsigned int maxLeptonsTightLoosePreselected;
    HelperLeptonCore * myHelper;

  LepGenInfos(HelperLeptonCore *in, int maxTight, int maxLoose, int maxPreselected, int maxTightLoose, int maxLoosePreselected, int maxTightLoosePreselected);
    void evaluate ();
  
};

LepGenInfos::LepGenInfos (HelperLeptonCore *in, int maxTight, int maxLoose, int maxPreselected, int maxTightLoose, int maxLoosePreselected, int maxTightLoosePreselected):
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
        TString branchName1 = Form("tight_leptons_by_pt_%d_genId", i+1);
        branches[branchName1] = BranchInfo<double>(branchName1);
        branches[branchName1].branchVal = this->resetVal;

        TString branchName2 = Form("tight_leptons_by_pt_%d_genMotherId", i+1);
        branches[branchName2] = BranchInfo<double>(branchName2);
        branches[branchName2].branchVal = this->resetVal;
    }

    for (unsigned int i=0; i<maxLeptonsLoose; i++) {
        TString branchName1 = Form("loose_leptons_by_pt_%d_genId", i+1);
        branches[branchName1] = BranchInfo<double>(branchName1);
        branches[branchName1].branchVal = this->resetVal;

        TString branchName2 = Form("loose_leptons_by_pt_%d_genMotherId", i+1);
        branches[branchName2] = BranchInfo<double>(branchName2);
        branches[branchName2].branchVal = this->resetVal;
    }

    for (unsigned int i=0; i<maxLeptonsPreselected; i++) {
        TString branchName1 = Form("preselected_leptons_by_pt_%d_genId", i+1);
        branches[branchName1] = BranchInfo<double>(branchName1);
        branches[branchName1].branchVal = this->resetVal;

        TString branchName2 = Form("preselected_leptons_by_pt_%d_genMotherId", i+1);
        branches[branchName2] = BranchInfo<double>(branchName2);
        branches[branchName2].branchVal = this->resetVal;
    }
    
    for (unsigned int i=0; i<maxLeptonsTightLoose; i++) {
        TString branchName1 = Form("tightLoose_leptons_by_pt_%d_genId", i+1);
        branches[branchName1] = BranchInfo<double>(branchName1);
        branches[branchName1].branchVal = this->resetVal;

        TString branchName2 = Form("tightLoose_leptons_by_pt_%d_genMotherId", i+1);
        branches[branchName2] = BranchInfo<double>(branchName2);
        branches[branchName2].branchVal = this->resetVal;
    }

//     for (unsigned int i=0; i<maxLeptonsLoosePreselected; i++) {
//         TString branchName1 = Form("loosePreselected_leptons_by_pt_%d_genId", i+1);
//         branches[branchName1] = BranchInfo<double>(branchName1);
//         branches[branchName1].branchVal = this->resetVal;

//         TString branchName2 = Form("loosePreselected_leptons_by_pt_%d_genMotherId", i+1);
//         branches[branchName2] = BranchInfo<double>(branchName2);
//         branches[branchName2].branchVal = this->resetVal;
//     }

    for (unsigned int i=0; i<maxLeptonsTightLoosePreselected; i++) {
        TString branchName1 = Form("all_leptons_by_pt_%d_genId", i+1);
        branches[branchName1] = BranchInfo<double>(branchName1);
        branches[branchName1].branchVal = this->resetVal;

        TString branchName2 = Form("all_leptons_by_pt_%d_genMotherId", i+1);
        branches[branchName2] = BranchInfo<double>(branchName2);
        branches[branchName2].branchVal = this->resetVal;
    }

}

void LepGenInfos::evaluate () {

  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  //--------

  BNleptonCollection * tightLeptons = this->blocks->tightLeptonCollection;
  BNleptonCollection * looseLeptons = this->blocks->looseLeptonCollection;
  BNleptonCollection * preselectedLeptons = this->blocks->preselectedLeptonCollection;
  BNleptonCollection * tightLooseLeptons = this->blocks->tightLooseLeptonCollection;
//   BNleptonCollection * loosePreselectedLeptons = this->blocks->loosePreselectedLeptonCollection;
  BNleptonCollection * tightLoosePreselectedLeptons = this->blocks->tightLoosePreselectedLeptonCollection;
  BEANhelper * beanHelper = &(myHelper->bHelp);
  TString branchName1;
  TString branchName2;
  BNmcparticle genMatch;

  unsigned loopMaxTight = (unsigned (maxLeptonsTight) < tightLeptons->size())
    ? unsigned(maxLeptonsTight) : tightLeptons->size();
  unsigned loopMaxLoose = (unsigned (maxLeptonsLoose) < looseLeptons->size())
    ? unsigned(maxLeptonsLoose) : looseLeptons->size();
  unsigned loopMaxPreselected = (unsigned (maxLeptonsPreselected) < preselectedLeptons->size())
    ? unsigned(maxLeptonsPreselected) : preselectedLeptons->size();
  unsigned loopMaxTightLoose = (unsigned (maxLeptonsTightLoose) < tightLooseLeptons->size())
    ? unsigned(maxLeptonsTightLoose) : tightLooseLeptons->size();
//   unsigned loopMaxLoosePreselected = (unsigned (maxLeptonsLoosePreselected) < loosePreselectedLeptons->size())
//     ? unsigned(maxLeptonsLoosePreselected) : loosePreselectedLeptons->size();
  unsigned loopMaxTightLoosePreselected = (unsigned (maxLeptonsTightLoosePreselected) < tightLoosePreselectedLeptons->size())
    ? unsigned(maxLeptonsTightLoosePreselected) : tightLoosePreselectedLeptons->size();

//   std::cout << "Inside evaluate" << std::endl;

//   for (unsigned int i=0; i<loopMaxTightLoosePreselected; i++) {
//     BNlepton * iLepton = tightLoosePreselectedLeptons->at(i);
//     std::cout << "iLepton->genId: " << iLepton->genId << std::endl;
//     std::cout << "iLepton->genMotherId: " << iLepton->genMotherId << std::endl;
    
//     std::cout << "Getting matched MC particle" << std::endl;
//     genMatch = beanHelper->GetMatchedMCparticle(*(this->blocks->mcParticleCollection), *(BNlepton*)iLepton, 0.1);
//     std::cout << "Got matched MC particle" << std::endl;
//     std::cout << "genMatch.id: " << genMatch.id << std::endl;
//     std::cout << "genMatch.motherId: " << genMatch.motherId << std::endl;
//   }

  for (unsigned int i=0; i<loopMaxTight; i++) {
      BNlepton * iLepton = tightLeptons->at(i);
      branchName1 = Form("tight_leptons_by_pt_%d_genId", i+1);
      branchName2 = Form("tight_leptons_by_pt_%d_genMotherId", i+1);

      if (iLepton->genId != -99) {
        branches[branchName1].branchVal = iLepton->genId;
        branches[branchName2].branchVal = iLepton->genMotherId;

        if ( (abs(iLepton->genId/100)%10 == 5) || (abs(iLepton->genId/1000)%10 == 5))      branches[branchName1].branchVal = 1*iLepton->genId/abs(iLepton->genId);
        else if ( (abs(iLepton->genId/100)%10 == 4) || (abs(iLepton->genId/1000)%10 == 4)) branches[branchName1].branchVal = 2*iLepton->genId/abs(iLepton->genId);
        else if ( (abs(iLepton->genId/100)%10 == 3) || (abs(iLepton->genId/1000)%10 == 3)) branches[branchName1].branchVal = 3*iLepton->genId/abs(iLepton->genId);
        else if ( (abs(iLepton->genId/100)%10 == 2) || (abs(iLepton->genId/1000)%10 == 2)) branches[branchName1].branchVal = 4*iLepton->genId/abs(iLepton->genId);
        else if ( (abs(iLepton->genId/100)%10 == 1) || (abs(iLepton->genId/1000)%10 == 1)) branches[branchName1].branchVal = 5*iLepton->genId/abs(iLepton->genId);
        
        if ( (abs(iLepton->genMotherId/100)%10 == 5) || (abs(iLepton->genMotherId/1000)%10 == 5))      branches[branchName2].branchVal = 1*iLepton->genMotherId/abs(iLepton->genMotherId);
        else if ( (abs(iLepton->genMotherId/100)%10 == 4) || (abs(iLepton->genMotherId/1000)%10 == 4)) branches[branchName2].branchVal = 2*iLepton->genMotherId/abs(iLepton->genMotherId);
        else if ( (abs(iLepton->genMotherId/100)%10 == 3) || (abs(iLepton->genMotherId/1000)%10 == 3)) branches[branchName2].branchVal = 3*iLepton->genMotherId/abs(iLepton->genMotherId);
        else if ( (abs(iLepton->genMotherId/100)%10 == 2) || (abs(iLepton->genMotherId/1000)%10 == 2)) branches[branchName2].branchVal = 4*iLepton->genMotherId/abs(iLepton->genMotherId);
        else if ( (abs(iLepton->genMotherId/100)%10 == 1) || (abs(iLepton->genMotherId/1000)%10 == 1)) branches[branchName2].branchVal = 5*iLepton->genMotherId/abs(iLepton->genMotherId);                
      }
      else {
        genMatch = beanHelper->GetMatchedMCparticle(*(this->blocks->mcParticleCollection), *(BNlepton*)iLepton, 0.1);
        branches[branchName1].branchVal = genMatch.id;
        branches[branchName2].branchVal = genMatch.motherId;

        if ( (abs(genMatch.id/100)%10 == 5) || (abs(genMatch.id/1000)%10 == 5))      branches[branchName1].branchVal = 1*genMatch.id/abs(genMatch.id);
        else if ( (abs(genMatch.id/100)%10 == 4) || (abs(genMatch.id/1000)%10 == 4)) branches[branchName1].branchVal = 2*genMatch.id/abs(genMatch.id);
        else if ( (abs(genMatch.id/100)%10 == 3) || (abs(genMatch.id/1000)%10 == 3)) branches[branchName1].branchVal = 3*genMatch.id/abs(genMatch.id);
        else if ( (abs(genMatch.id/100)%10 == 2) || (abs(genMatch.id/1000)%10 == 2)) branches[branchName1].branchVal = 4*genMatch.id/abs(genMatch.id);
        else if ( (abs(genMatch.id/100)%10 == 1) || (abs(genMatch.id/1000)%10 == 1)) branches[branchName1].branchVal = 5*genMatch.id/abs(genMatch.id);
        
        if ( (abs(genMatch.motherId/100)%10 == 5) || (abs(genMatch.motherId/1000)%10 == 5))      branches[branchName2].branchVal = 1*genMatch.motherId/abs(genMatch.motherId);
        else if ( (abs(genMatch.motherId/100)%10 == 4) || (abs(genMatch.motherId/1000)%10 == 4)) branches[branchName2].branchVal = 2*genMatch.motherId/abs(genMatch.motherId);
        else if ( (abs(genMatch.motherId/100)%10 == 3) || (abs(genMatch.motherId/1000)%10 == 3)) branches[branchName2].branchVal = 3*genMatch.motherId/abs(genMatch.motherId);
        else if ( (abs(genMatch.motherId/100)%10 == 2) || (abs(genMatch.motherId/1000)%10 == 2)) branches[branchName2].branchVal = 4*genMatch.motherId/abs(genMatch.motherId);
        else if ( (abs(genMatch.motherId/100)%10 == 1) || (abs(genMatch.motherId/1000)%10 == 1)) branches[branchName2].branchVal = 5*genMatch.motherId/abs(genMatch.motherId);                
      }
  }

  for (unsigned int i=0; i<loopMaxLoose; i++) {
      BNlepton * iLepton = looseLeptons->at(i);
      branchName1 = Form("loose_leptons_by_pt_%d_genId", i+1);
      branchName2 = Form("loose_leptons_by_pt_%d_genMotherId", i+1);

      if (iLepton->genId != -99) {
        branches[branchName1].branchVal = iLepton->genId;
        branches[branchName2].branchVal = iLepton->genMotherId;

        if ( (abs(iLepton->genId/100)%10 == 5) || (abs(iLepton->genId/1000)%10 == 5))      branches[branchName1].branchVal = 1*iLepton->genId/abs(iLepton->genId);
        else if ( (abs(iLepton->genId/100)%10 == 4) || (abs(iLepton->genId/1000)%10 == 4)) branches[branchName1].branchVal = 2*iLepton->genId/abs(iLepton->genId);
        else if ( (abs(iLepton->genId/100)%10 == 3) || (abs(iLepton->genId/1000)%10 == 3)) branches[branchName1].branchVal = 3*iLepton->genId/abs(iLepton->genId);
        else if ( (abs(iLepton->genId/100)%10 == 2) || (abs(iLepton->genId/1000)%10 == 2)) branches[branchName1].branchVal = 4*iLepton->genId/abs(iLepton->genId);
        else if ( (abs(iLepton->genId/100)%10 == 1) || (abs(iLepton->genId/1000)%10 == 1)) branches[branchName1].branchVal = 5*iLepton->genId/abs(iLepton->genId);
        
        if ( (abs(iLepton->genMotherId/100)%10 == 5) || (abs(iLepton->genMotherId/1000)%10 == 5))      branches[branchName2].branchVal = 1*iLepton->genMotherId/abs(iLepton->genMotherId);
        else if ( (abs(iLepton->genMotherId/100)%10 == 4) || (abs(iLepton->genMotherId/1000)%10 == 4)) branches[branchName2].branchVal = 2*iLepton->genMotherId/abs(iLepton->genMotherId);
        else if ( (abs(iLepton->genMotherId/100)%10 == 3) || (abs(iLepton->genMotherId/1000)%10 == 3)) branches[branchName2].branchVal = 3*iLepton->genMotherId/abs(iLepton->genMotherId);
        else if ( (abs(iLepton->genMotherId/100)%10 == 2) || (abs(iLepton->genMotherId/1000)%10 == 2)) branches[branchName2].branchVal = 4*iLepton->genMotherId/abs(iLepton->genMotherId);
        else if ( (abs(iLepton->genMotherId/100)%10 == 1) || (abs(iLepton->genMotherId/1000)%10 == 1)) branches[branchName2].branchVal = 5*iLepton->genMotherId/abs(iLepton->genMotherId);
      }
      else {
        genMatch = beanHelper->GetMatchedMCparticle(*(this->blocks->mcParticleCollection), *(BNlepton*)iLepton, 0.1);
        branches[branchName1].branchVal = genMatch.id;
        branches[branchName2].branchVal = genMatch.motherId;

        if ( (abs(genMatch.id/100)%10 == 5) || (abs(genMatch.id/1000)%10 == 5))      branches[branchName1].branchVal = 1*genMatch.id/abs(genMatch.id);
        else if ( (abs(genMatch.id/100)%10 == 4) || (abs(genMatch.id/1000)%10 == 4)) branches[branchName1].branchVal = 2*genMatch.id/abs(genMatch.id);
        else if ( (abs(genMatch.id/100)%10 == 3) || (abs(genMatch.id/1000)%10 == 3)) branches[branchName1].branchVal = 3*genMatch.id/abs(genMatch.id);
        else if ( (abs(genMatch.id/100)%10 == 2) || (abs(genMatch.id/1000)%10 == 2)) branches[branchName1].branchVal = 4*genMatch.id/abs(genMatch.id);
        else if ( (abs(genMatch.id/100)%10 == 1) || (abs(genMatch.id/1000)%10 == 1)) branches[branchName1].branchVal = 5*genMatch.id/abs(genMatch.id);
        
        if ( (abs(genMatch.motherId/100)%10 == 5) || (abs(genMatch.motherId/1000)%10 == 5))      branches[branchName2].branchVal = 1*genMatch.motherId/abs(genMatch.motherId);
        else if ( (abs(genMatch.motherId/100)%10 == 4) || (abs(genMatch.motherId/1000)%10 == 4)) branches[branchName2].branchVal = 2*genMatch.motherId/abs(genMatch.motherId);
        else if ( (abs(genMatch.motherId/100)%10 == 3) || (abs(genMatch.motherId/1000)%10 == 3)) branches[branchName2].branchVal = 3*genMatch.motherId/abs(genMatch.motherId);
        else if ( (abs(genMatch.motherId/100)%10 == 2) || (abs(genMatch.motherId/1000)%10 == 2)) branches[branchName2].branchVal = 4*genMatch.motherId/abs(genMatch.motherId);
        else if ( (abs(genMatch.motherId/100)%10 == 1) || (abs(genMatch.motherId/1000)%10 == 1)) branches[branchName2].branchVal = 5*genMatch.motherId/abs(genMatch.motherId);
      }
  }

  for (unsigned int i=0; i<loopMaxPreselected; i++) {
      BNlepton * iLepton = preselectedLeptons->at(i);
      branchName1 = Form("preselected_leptons_by_pt_%d_genId", i+1);
      branchName2 = Form("preselected_leptons_by_pt_%d_genMotherId", i+1);

      if (iLepton->genId != -99) {
        branches[branchName1].branchVal = iLepton->genId;
        branches[branchName2].branchVal = iLepton->genMotherId;

        if ( (abs(iLepton->genId/100)%10 == 5) || (abs(iLepton->genId/1000)%10 == 5))      branches[branchName1].branchVal = 1*iLepton->genId/abs(iLepton->genId);
        else if ( (abs(iLepton->genId/100)%10 == 4) || (abs(iLepton->genId/1000)%10 == 4)) branches[branchName1].branchVal = 2*iLepton->genId/abs(iLepton->genId);
        else if ( (abs(iLepton->genId/100)%10 == 3) || (abs(iLepton->genId/1000)%10 == 3)) branches[branchName1].branchVal = 3*iLepton->genId/abs(iLepton->genId);
        else if ( (abs(iLepton->genId/100)%10 == 2) || (abs(iLepton->genId/1000)%10 == 2)) branches[branchName1].branchVal = 4*iLepton->genId/abs(iLepton->genId);
        else if ( (abs(iLepton->genId/100)%10 == 1) || (abs(iLepton->genId/1000)%10 == 1)) branches[branchName1].branchVal = 5*iLepton->genId/abs(iLepton->genId);
        
        if ( (abs(iLepton->genMotherId/100)%10 == 5) || (abs(iLepton->genMotherId/1000)%10 == 5))      branches[branchName2].branchVal = 1*iLepton->genMotherId/abs(iLepton->genMotherId);
        else if ( (abs(iLepton->genMotherId/100)%10 == 4) || (abs(iLepton->genMotherId/1000)%10 == 4)) branches[branchName2].branchVal = 2*iLepton->genMotherId/abs(iLepton->genMotherId);
        else if ( (abs(iLepton->genMotherId/100)%10 == 3) || (abs(iLepton->genMotherId/1000)%10 == 3)) branches[branchName2].branchVal = 3*iLepton->genMotherId/abs(iLepton->genMotherId);
        else if ( (abs(iLepton->genMotherId/100)%10 == 2) || (abs(iLepton->genMotherId/1000)%10 == 2)) branches[branchName2].branchVal = 4*iLepton->genMotherId/abs(iLepton->genMotherId);
        else if ( (abs(iLepton->genMotherId/100)%10 == 1) || (abs(iLepton->genMotherId/1000)%10 == 1)) branches[branchName2].branchVal = 5*iLepton->genMotherId/abs(iLepton->genMotherId);
      }
      else {
        genMatch = beanHelper->GetMatchedMCparticle(*(this->blocks->mcParticleCollection), *(BNlepton*)iLepton, 0.1);
        branches[branchName1].branchVal = genMatch.id;
        branches[branchName2].branchVal = genMatch.motherId;

        if ( (abs(genMatch.id/100)%10 == 5) || (abs(genMatch.id/1000)%10 == 5))      branches[branchName1].branchVal = 1*genMatch.id/abs(genMatch.id);
        else if ( (abs(genMatch.id/100)%10 == 4) || (abs(genMatch.id/1000)%10 == 4)) branches[branchName1].branchVal = 2*genMatch.id/abs(genMatch.id);
        else if ( (abs(genMatch.id/100)%10 == 3) || (abs(genMatch.id/1000)%10 == 3)) branches[branchName1].branchVal = 3*genMatch.id/abs(genMatch.id);
        else if ( (abs(genMatch.id/100)%10 == 2) || (abs(genMatch.id/1000)%10 == 2)) branches[branchName1].branchVal = 4*genMatch.id/abs(genMatch.id);
        else if ( (abs(genMatch.id/100)%10 == 1) || (abs(genMatch.id/1000)%10 == 1)) branches[branchName1].branchVal = 5*genMatch.id/abs(genMatch.id);
        
        if ( (abs(genMatch.motherId/100)%10 == 5) || (abs(genMatch.motherId/1000)%10 == 5))      branches[branchName2].branchVal = 1*genMatch.motherId/abs(genMatch.motherId);
        else if ( (abs(genMatch.motherId/100)%10 == 4) || (abs(genMatch.motherId/1000)%10 == 4)) branches[branchName2].branchVal = 2*genMatch.motherId/abs(genMatch.motherId);
        else if ( (abs(genMatch.motherId/100)%10 == 3) || (abs(genMatch.motherId/1000)%10 == 3)) branches[branchName2].branchVal = 3*genMatch.motherId/abs(genMatch.motherId);
        else if ( (abs(genMatch.motherId/100)%10 == 2) || (abs(genMatch.motherId/1000)%10 == 2)) branches[branchName2].branchVal = 4*genMatch.motherId/abs(genMatch.motherId);
        else if ( (abs(genMatch.motherId/100)%10 == 1) || (abs(genMatch.motherId/1000)%10 == 1)) branches[branchName2].branchVal = 5*genMatch.motherId/abs(genMatch.motherId);
      }
  }

  for (unsigned int i=0; i<loopMaxTightLoose; i++) {
      BNlepton * iLepton = tightLooseLeptons->at(i);
      branchName1 = Form("tightLoose_leptons_by_pt_%d_genId", i+1);
      branchName2 = Form("tightLoose_leptons_by_pt_%d_genMotherId", i+1);

      if (iLepton->genId != -99) {
        branches[branchName1].branchVal = iLepton->genId;
        branches[branchName2].branchVal = iLepton->genMotherId;

        if ( (abs(iLepton->genId/100)%10 == 5) || (abs(iLepton->genId/1000)%10 == 5))      branches[branchName1].branchVal = 1*iLepton->genId/abs(iLepton->genId);
        else if ( (abs(iLepton->genId/100)%10 == 4) || (abs(iLepton->genId/1000)%10 == 4)) branches[branchName1].branchVal = 2*iLepton->genId/abs(iLepton->genId);
        else if ( (abs(iLepton->genId/100)%10 == 3) || (abs(iLepton->genId/1000)%10 == 3)) branches[branchName1].branchVal = 3*iLepton->genId/abs(iLepton->genId);
        else if ( (abs(iLepton->genId/100)%10 == 2) || (abs(iLepton->genId/1000)%10 == 2)) branches[branchName1].branchVal = 4*iLepton->genId/abs(iLepton->genId);
        else if ( (abs(iLepton->genId/100)%10 == 1) || (abs(iLepton->genId/1000)%10 == 1)) branches[branchName1].branchVal = 5*iLepton->genId/abs(iLepton->genId);
        
        if ( (abs(iLepton->genMotherId/100)%10 == 5) || (abs(iLepton->genMotherId/1000)%10 == 5))      branches[branchName2].branchVal = 1*iLepton->genMotherId/abs(iLepton->genMotherId);
        else if ( (abs(iLepton->genMotherId/100)%10 == 4) || (abs(iLepton->genMotherId/1000)%10 == 4)) branches[branchName2].branchVal = 2*iLepton->genMotherId/abs(iLepton->genMotherId);
        else if ( (abs(iLepton->genMotherId/100)%10 == 3) || (abs(iLepton->genMotherId/1000)%10 == 3)) branches[branchName2].branchVal = 3*iLepton->genMotherId/abs(iLepton->genMotherId);
        else if ( (abs(iLepton->genMotherId/100)%10 == 2) || (abs(iLepton->genMotherId/1000)%10 == 2)) branches[branchName2].branchVal = 4*iLepton->genMotherId/abs(iLepton->genMotherId);
        else if ( (abs(iLepton->genMotherId/100)%10 == 1) || (abs(iLepton->genMotherId/1000)%10 == 1)) branches[branchName2].branchVal = 5*iLepton->genMotherId/abs(iLepton->genMotherId);
      }
      else {
        genMatch = beanHelper->GetMatchedMCparticle(*(this->blocks->mcParticleCollection), *(BNlepton*)iLepton, 0.1);
        branches[branchName1].branchVal = genMatch.id;
        branches[branchName2].branchVal = genMatch.motherId;

        if ( (abs(genMatch.id/100)%10 == 5) || (abs(genMatch.id/1000)%10 == 5))      branches[branchName1].branchVal = 1*genMatch.id/abs(genMatch.id);
        else if ( (abs(genMatch.id/100)%10 == 4) || (abs(genMatch.id/1000)%10 == 4)) branches[branchName1].branchVal = 2*genMatch.id/abs(genMatch.id);
        else if ( (abs(genMatch.id/100)%10 == 3) || (abs(genMatch.id/1000)%10 == 3)) branches[branchName1].branchVal = 3*genMatch.id/abs(genMatch.id);
        else if ( (abs(genMatch.id/100)%10 == 2) || (abs(genMatch.id/1000)%10 == 2)) branches[branchName1].branchVal = 4*genMatch.id/abs(genMatch.id);
        else if ( (abs(genMatch.id/100)%10 == 1) || (abs(genMatch.id/1000)%10 == 1)) branches[branchName1].branchVal = 5*genMatch.id/abs(genMatch.id);
        
        if ( (abs(genMatch.motherId/100)%10 == 5) || (abs(genMatch.motherId/1000)%10 == 5))      branches[branchName2].branchVal = 1*genMatch.motherId/abs(genMatch.motherId);
        else if ( (abs(genMatch.motherId/100)%10 == 4) || (abs(genMatch.motherId/1000)%10 == 4)) branches[branchName2].branchVal = 2*genMatch.motherId/abs(genMatch.motherId);
        else if ( (abs(genMatch.motherId/100)%10 == 3) || (abs(genMatch.motherId/1000)%10 == 3)) branches[branchName2].branchVal = 3*genMatch.motherId/abs(genMatch.motherId);
        else if ( (abs(genMatch.motherId/100)%10 == 2) || (abs(genMatch.motherId/1000)%10 == 2)) branches[branchName2].branchVal = 4*genMatch.motherId/abs(genMatch.motherId);
        else if ( (abs(genMatch.motherId/100)%10 == 1) || (abs(genMatch.motherId/1000)%10 == 1)) branches[branchName2].branchVal = 5*genMatch.motherId/abs(genMatch.motherId);
      }
  }

//   for (unsigned int i=0; i<loopMaxLoosePreselected; i++) {
//       BNlepton * iLepton = loosePreselectedLeptons->at(i);
//       branchName1 = Form("loosePreselected_leptons_by_pt_%d_genId", i+1);
//       branchName2 = Form("loosePreselected_leptons_by_pt_%d_genMotherId", i+1);

//       if (iLepton->genId != -99) {
//         branches[branchName1].branchVal = iLepton->genId;
//         branches[branchName2].branchVal = iLepton->genMotherId;

//         if ( (abs(iLepton->genId/100)%10 == 5) || (abs(iLepton->genId/1000)%10 == 5))      branches[branchName1].branchVal = 1*iLepton->genId/abs(iLepton->genId);
//         else if ( (abs(iLepton->genId/100)%10 == 4) || (abs(iLepton->genId/1000)%10 == 4)) branches[branchName1].branchVal = 2*iLepton->genId/abs(iLepton->genId);
//         else if ( (abs(iLepton->genId/100)%10 == 3) || (abs(iLepton->genId/1000)%10 == 3)) branches[branchName1].branchVal = 3*iLepton->genId/abs(iLepton->genId);
//         else if ( (abs(iLepton->genId/100)%10 == 2) || (abs(iLepton->genId/1000)%10 == 2)) branches[branchName1].branchVal = 4*iLepton->genId/abs(iLepton->genId);
//         else if ( (abs(iLepton->genId/100)%10 == 1) || (abs(iLepton->genId/1000)%10 == 1)) branches[branchName1].branchVal = 5*iLepton->genId/abs(iLepton->genId);
        
//         if ( (abs(iLepton->genMotherId/100)%10 == 5) || (abs(iLepton->genMotherId/1000)%10 == 5))      branches[branchName2].branchVal = 1*iLepton->genMotherId/abs(iLepton->genMotherId);
//         else if ( (abs(iLepton->genMotherId/100)%10 == 4) || (abs(iLepton->genMotherId/1000)%10 == 4)) branches[branchName2].branchVal = 2*iLepton->genMotherId/abs(iLepton->genMotherId);
//         else if ( (abs(iLepton->genMotherId/100)%10 == 3) || (abs(iLepton->genMotherId/1000)%10 == 3)) branches[branchName2].branchVal = 3*iLepton->genMotherId/abs(iLepton->genMotherId);
//         else if ( (abs(iLepton->genMotherId/100)%10 == 2) || (abs(iLepton->genMotherId/1000)%10 == 2)) branches[branchName2].branchVal = 4*iLepton->genMotherId/abs(iLepton->genMotherId);
//         else if ( (abs(iLepton->genMotherId/100)%10 == 1) || (abs(iLepton->genMotherId/1000)%10 == 1)) branches[branchName2].branchVal = 5*iLepton->genMotherId/abs(iLepton->genMotherId);
//       }
//       else {
//         genMatch = beanHelper->GetMatchedMCparticle(*(this->blocks->mcParticleCollection), *(BNlepton*)iLepton, 0.1);
//         branches[branchName1].branchVal = genMatch.id;
//         branches[branchName2].branchVal = genMatch.motherId;

//         if ( (abs(genMatch.id/100)%10 == 5) || (abs(genMatch.id/1000)%10 == 5))      branches[branchName1].branchVal = 1*genMatch.id/abs(genMatch.id);
//         else if ( (abs(genMatch.id/100)%10 == 4) || (abs(genMatch.id/1000)%10 == 4)) branches[branchName1].branchVal = 2*genMatch.id/abs(genMatch.id);
//         else if ( (abs(genMatch.id/100)%10 == 3) || (abs(genMatch.id/1000)%10 == 3)) branches[branchName1].branchVal = 3*genMatch.id/abs(genMatch.id);
//         else if ( (abs(genMatch.id/100)%10 == 2) || (abs(genMatch.id/1000)%10 == 2)) branches[branchName1].branchVal = 4*genMatch.id/abs(genMatch.id);
//         else if ( (abs(genMatch.id/100)%10 == 1) || (abs(genMatch.id/1000)%10 == 1)) branches[branchName1].branchVal = 5*genMatch.id/abs(genMatch.id);
        
//         if ( (abs(genMatch.motherId/100)%10 == 5) || (abs(genMatch.motherId/1000)%10 == 5))      branches[branchName2].branchVal = 1*genMatch.motherId/abs(genMatch.motherId);
//         else if ( (abs(genMatch.motherId/100)%10 == 4) || (abs(genMatch.motherId/1000)%10 == 4)) branches[branchName2].branchVal = 2*genMatch.motherId/abs(genMatch.motherId);
//         else if ( (abs(genMatch.motherId/100)%10 == 3) || (abs(genMatch.motherId/1000)%10 == 3)) branches[branchName2].branchVal = 3*genMatch.motherId/abs(genMatch.motherId);
//         else if ( (abs(genMatch.motherId/100)%10 == 2) || (abs(genMatch.motherId/1000)%10 == 2)) branches[branchName2].branchVal = 4*genMatch.motherId/abs(genMatch.motherId);
//         else if ( (abs(genMatch.motherId/100)%10 == 1) || (abs(genMatch.motherId/1000)%10 == 1)) branches[branchName2].branchVal = 5*genMatch.motherId/abs(genMatch.motherId);
//       }
//   }

  for (unsigned int i=0; i<loopMaxTightLoosePreselected; i++) {
      BNlepton * iLepton = tightLoosePreselectedLeptons->at(i);
      branchName1 = Form("all_leptons_by_pt_%d_genId", i+1);
      branchName2 = Form("all_leptons_by_pt_%d_genMotherId", i+1);

      if (iLepton->genId != -99) {
        branches[branchName1].branchVal = iLepton->genId;
        branches[branchName2].branchVal = iLepton->genMotherId;

        if ( (abs(iLepton->genId/100)%10 == 5) || (abs(iLepton->genId/1000)%10 == 5))      branches[branchName1].branchVal = 1*iLepton->genId/abs(iLepton->genId);
        else if ( (abs(iLepton->genId/100)%10 == 4) || (abs(iLepton->genId/1000)%10 == 4)) branches[branchName1].branchVal = 2*iLepton->genId/abs(iLepton->genId);
        else if ( (abs(iLepton->genId/100)%10 == 3) || (abs(iLepton->genId/1000)%10 == 3)) branches[branchName1].branchVal = 3*iLepton->genId/abs(iLepton->genId);
        else if ( (abs(iLepton->genId/100)%10 == 2) || (abs(iLepton->genId/1000)%10 == 2)) branches[branchName1].branchVal = 4*iLepton->genId/abs(iLepton->genId);
        else if ( (abs(iLepton->genId/100)%10 == 1) || (abs(iLepton->genId/1000)%10 == 1)) branches[branchName1].branchVal = 5*iLepton->genId/abs(iLepton->genId);
        
        if ( (abs(iLepton->genMotherId/100)%10 == 5) || (abs(iLepton->genMotherId/1000)%10 == 5))      branches[branchName2].branchVal = 1*iLepton->genMotherId/abs(iLepton->genMotherId);
        else if ( (abs(iLepton->genMotherId/100)%10 == 4) || (abs(iLepton->genMotherId/1000)%10 == 4)) branches[branchName2].branchVal = 2*iLepton->genMotherId/abs(iLepton->genMotherId);
        else if ( (abs(iLepton->genMotherId/100)%10 == 3) || (abs(iLepton->genMotherId/1000)%10 == 3)) branches[branchName2].branchVal = 3*iLepton->genMotherId/abs(iLepton->genMotherId);
        else if ( (abs(iLepton->genMotherId/100)%10 == 2) || (abs(iLepton->genMotherId/1000)%10 == 2)) branches[branchName2].branchVal = 4*iLepton->genMotherId/abs(iLepton->genMotherId);
        else if ( (abs(iLepton->genMotherId/100)%10 == 1) || (abs(iLepton->genMotherId/1000)%10 == 1)) branches[branchName2].branchVal = 5*iLepton->genMotherId/abs(iLepton->genMotherId);
      }
      else {
        genMatch = beanHelper->GetMatchedMCparticle(*(this->blocks->mcParticleCollection), *(BNlepton*)iLepton, 0.1);
        branches[branchName1].branchVal = genMatch.id;
        branches[branchName2].branchVal = genMatch.motherId;

        if ( (abs(genMatch.id/100)%10 == 5) || (abs(genMatch.id/1000)%10 == 5))      branches[branchName1].branchVal = 1*genMatch.id/abs(genMatch.id);
        else if ( (abs(genMatch.id/100)%10 == 4) || (abs(genMatch.id/1000)%10 == 4)) branches[branchName1].branchVal = 2*genMatch.id/abs(genMatch.id);
        else if ( (abs(genMatch.id/100)%10 == 3) || (abs(genMatch.id/1000)%10 == 3)) branches[branchName1].branchVal = 3*genMatch.id/abs(genMatch.id);
        else if ( (abs(genMatch.id/100)%10 == 2) || (abs(genMatch.id/1000)%10 == 2)) branches[branchName1].branchVal = 4*genMatch.id/abs(genMatch.id);
        else if ( (abs(genMatch.id/100)%10 == 1) || (abs(genMatch.id/1000)%10 == 1)) branches[branchName1].branchVal = 5*genMatch.id/abs(genMatch.id);
        
        if ( (abs(genMatch.motherId/100)%10 == 5) || (abs(genMatch.motherId/1000)%10 == 5))      branches[branchName2].branchVal = 1*genMatch.motherId/abs(genMatch.motherId);
        else if ( (abs(genMatch.motherId/100)%10 == 4) || (abs(genMatch.motherId/1000)%10 == 4)) branches[branchName2].branchVal = 2*genMatch.motherId/abs(genMatch.motherId);
        else if ( (abs(genMatch.motherId/100)%10 == 3) || (abs(genMatch.motherId/1000)%10 == 3)) branches[branchName2].branchVal = 3*genMatch.motherId/abs(genMatch.motherId);
        else if ( (abs(genMatch.motherId/100)%10 == 2) || (abs(genMatch.motherId/1000)%10 == 2)) branches[branchName2].branchVal = 4*genMatch.motherId/abs(genMatch.motherId);
        else if ( (abs(genMatch.motherId/100)%10 == 1) || (abs(genMatch.motherId/1000)%10 == 1)) branches[branchName2].branchVal = 5*genMatch.motherId/abs(genMatch.motherId);
      }
  }

}


#endif 
