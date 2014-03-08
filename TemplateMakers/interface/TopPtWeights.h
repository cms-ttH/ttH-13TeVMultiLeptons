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
  TopPtWeights(HelperLeptonCore *in, string input_option_1 = "none");

  void evaluate ();
  bool passCut ();

  HelperLeptonCore * myHelper;
  string option_1;
};

///////////////////////////////////////////////////////////////////////
TopPtWeights::TopPtWeights  (HelperLeptonCore *in, string input_option_1):
  myHelper(in), option_1(input_option_1)
{
  branches["topPtWgt"] = BranchInfo<double>("topPtWgt");
  if (option_1 != "skipSyst") {
    branches["topPtWgtUp"] = BranchInfo<double>("topPtWgtUp");
  }

  this->resetVal = KinematicVariableConstants::DOUBLE_INIT;
}

void TopPtWeights::evaluate () {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  BEANhelper * beanHelper = &(myHelper->bHelp);

  double weight = beanHelper->GetTopPtweight( *(this->blocks->mcParticleCollection) );
  double weightUp = 2*(weight-1)+1;

  branches["topPtWgt"].branchVal = weight;
  if (option_1 != "skipSyst") {
    branches["topPtWgtUp"].branchVal = weightUp;
  }
  

}


bool TopPtWeights::passCut() {

  return true;

}

#endif
