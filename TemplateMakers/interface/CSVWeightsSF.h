#ifndef _CSVWeightsSF_h
#define _CSVWeightsSF_h

///////////////////////////////////////////////////////
//
//  Books the 18 variables necessary for
//  producing the proper CSV weights in your jets
//
//  Note that the weighting doesn't depend on
//  which btag cut you make: it applies for all
//  CSV values.
//
////////////////////////////////////////////////////

class CSVWeightsSF: public KinematicVariable<double> {

public:
  BEANhelper * beanHelper;
  BNjetCollection **jets;
  HelperLeptonCore * myHelper;
  string option;

  CSVWeightsSF(BEANhelper * beanHelper, BNjetCollection** jets, string _option="none");
  void evaluate();
  bool passCut();

};

CSVWeightsSF::CSVWeightsSF(BEANhelper * beanHelper, BNjetCollection **jets, string _option) :
  beanHelper(beanHelper),
  jets(jets),
  option(_option)
{
  this->resetVal = KinematicVariableConstants::DOUBLE_INIT;

  branches["csvWgtlf"] = BranchInfo<double>("csvWgtlf");
  branches["csvWgthf"] = BranchInfo<double>("csvWgthf");
}

void CSVWeightsSF::evaluate () {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  vector<double> nominalWeights = beanHelper->GetCSVweights(*(*(jets)), sysType::NA);

  branches["csvWgtlf"].branchVal = nominalWeights[1];
  branches["csvWgthf"].branchVal = nominalWeights[0];
}


bool CSVWeightsSF::passCut() {
  return true;
}

#endif
