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
  CSVWeightsSF(HelperLeptonCore *in, string input_option_1 = "none");

  void evaluate ();
  bool passCut ();

  HelperLeptonCore * myHelper;
  string option_1;
};

CSVWeightsSF::CSVWeightsSF  (HelperLeptonCore *in, string input_option_1) :
  myHelper(in), option_1(input_option_1)
{
  this->resetVal = KinematicVariableConstants::DOUBLE_INIT;

  branches["csvWgtlf"] = BranchInfo<double>("csvWgtlf");
  branches["csvWgthf"] = BranchInfo<double>("csvWgthf");

}

void CSVWeightsSF::evaluate () {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  BNjetCollection * myJets = this->blocks->jetCollection;
  BEANhelper * beanHelper = &(myHelper->bHelp);

  vector<double> nominalWeights = beanHelper->GetCSVweights(*(myJets), sysType::NA);


  branches["csvWgtlf"].branchVal = nominalWeights[1];
  branches["csvWgthf"].branchVal = nominalWeights[0];

}


bool CSVWeightsSF::passCut() {
  return true;
}

#endif
