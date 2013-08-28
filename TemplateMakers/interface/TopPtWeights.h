
#ifndef _TopPtWeights_h
#define _TopPtWeights_h



///////////////////////////////////////////////////////
//
//
//   Top Pt reweight 
//   Stores the nominal weight and the shifted up
//   weight.
//   The shift down is just no weight at all
//
////////////////////////////////////////////////////

class TopPtWeights: public KinematicVariable<double> {

public:
  
  TopPtWeights(HelperLeptonCore *in);


  void evaluate ();
  bool passCut ();

  HelperLeptonCore * myHelper;

};

///////////////////////////////////////////////////////////////////////

TopPtWeights::TopPtWeights  (HelperLeptonCore *in) :
  myHelper(in)
{

  branches["topPtWgt"] = BranchInfo<double>("topPtWgt");
  branches["topPtWgtUp"] = BranchInfo<double>("topPtWgtUp");

  this->resetVal = KinematicVariableConstants::DOUBLE_INIT;
  
}

void TopPtWeights::evaluate () {
  
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;


  BEANhelper * beanHelper = &(myHelper->bHelp);

  double weight = beanHelper->GetTopPtweight( *(this->blocks->mcParticleCollection) );
  double weightUp = 2*(weight-1)+1;

  branches["topPtWgt"].branchVal = weight;
  branches["topPtWgtUp"].branchVal = weightUp;

  

}


bool TopPtWeights::passCut() {

  return true;

}

#endif
