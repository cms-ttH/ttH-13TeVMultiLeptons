#ifndef _TopPtWeights_h
#define _TopPtWeights_h

///////////////////////////////////////////////////////
//
//
//   Top Pt reweight
//   Stores the nominal weight and the shifted up weight.
//   The shift down is just no weight at all
//
////////////////////////////////////////////////////

class TopPtWeights: public KinematicVariable<double> {

public:
  HelperLeptonCore * myHelper;
  BNmcparticleCollection ** mcParticles;
  string option;

  TopPtWeights(HelperLeptonCore *_myHelper, BNmcparticleCollection **_mcParticles, string _option="none");
  void evaluate ();
};

///////////////////////////////////////////////////////////////////////
TopPtWeights::TopPtWeights(HelperLeptonCore *_myHelper, BNmcparticleCollection **_mcParticles, string _option):
  myHelper(_myHelper),
  mcParticles(_mcParticles),
  option(_option)
{
  branches["topPtWgt"] = BranchInfo<double>("topPtWgt");
  if (option != "skipSyst") {
    branches["topPtWgtUp"] = BranchInfo<double>("topPtWgtUp");
  }

  this->resetVal = KinematicVariableConstants::DOUBLE_INIT;
}

void TopPtWeights::evaluate() {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  BEANhelper * beanHelper = &(myHelper->bHelp);

  double weight = beanHelper->GetTopPtweight(*(*mcParticles));
  double weightUp = 2*(weight-1)+1;

  branches["topPtWgt"].branchVal = weight;
  if (option != "skipSyst") {
    branches["topPtWgtUp"].branchVal = weightUp;
  }
}


#endif
