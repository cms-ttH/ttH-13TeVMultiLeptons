#ifndef _MHT_h
#define _MHT_h

#include  "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"

class MHT: public KinematicVariable<double> {
public:
    MHT();
    void evaluate();
    void setCut(int cut);
    bool passCut();

    double threshold;
    double mht;
};

MHT::MHT() {
  mht = this->resetVal;    
  branches["mht"] = BranchInfo<double>("mht");
}

void MHT::evaluate() {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  BNleptonCollection* tightLeptons = this->blocks->tightLeptonCollection;
  BNjetCollection* selectedJets = this->blocks->jetCollection;
  TLorentzVector object_p4;
  TLorentzVector vector_sum;

  for (auto& lepton: (*tightLeptons)) {
      object_p4.SetPxPyPzE(lepton->px, lepton->py, lepton->pz, lepton->energy);

      vector_sum += object_p4;
  }

  for (auto& jet: (*selectedJets)) {
      object_p4.SetPxPyPzE(jet.px, jet.py, jet.pz, jet.energy);

      vector_sum += object_p4;
  }

  mht = vector_sum.Pt();

  branches["mht"].branchVal = mht;
}

void MHT::setCut(double cut) {
    threshold = cut;
}
   
bool MHT::passCut() {
  evaluate();
  
  if (branches["mht"].branchVal < threshold)
    return true;
  return false;
}


#endif 
