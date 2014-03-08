
#ifndef _PUWeights_h
#define _PUWeights_h



///////////////////////////////////////////////////////
//
//
//  PU Weights
//
//
////////////////////////////////////////////////////

class PUWeights: public KinematicVariable<double> {

public:
  
  PUWeights(HelperLeptonCore *in, string input_option_1 = "none");


  void evaluate ();
  bool passCut ();

  HelperLeptonCore * myHelper;
  string option_1;

};

///////////////////////////////////////////////////////////////////////

PUWeights::PUWeights  (HelperLeptonCore *in, string input_option_1) :
  myHelper(in), option_1(input_option_1)
{

  branches["weight_PU"] = BranchInfo<double>("weight_PU");
  if (option_1 != "skipSyst") {
    branches["weight_PUUp"] = BranchInfo<double>("weight_PUUp");
    branches["weight_PUDown"] = BranchInfo<double>("weight_PUDown");
  }
  
  this->resetVal = KinematicVariableConstants::DOUBLE_INIT;
  
}

/////////////////////////////////////////////////////////
//
//   PU reweighting from helper_dilpeton.C
//   The components from anything other than 2012_53x
//   remains entirely untested
//
//
////////////////////////////////////////////////////////


void PUWeights::evaluate () {
  
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  bool isData = myHelper->isData;
  string selectionYearStr = myHelper->analysisYear;
  string sampleName = myHelper->sampleName;

  BEANhelper * beanHelper = &(myHelper->bHelp);

  // default weight is 1.0
  double weight_PUNominal = 1.0, weight_PUUp = 1.0, weight_PUDown = 1.0;

  BNevent iEvent = this->blocks->eventCollection->at(0);

  double numTruePV = iEvent.numTruePV;
  double numGenPV = iEvent.numGenPV;
  

  // data doesn't need a reweight
  if(!isData){

    // legacy stuff
    if(selectionYearStr == "2011") {
      if ((TString(sampleName).Contains("ttH")) || (sampleName=="ttbarW") || (sampleName=="ttbarZ")) {
        weight_PUNominal = beanHelper->GetPUweight(numGenPV);
        weight_PUUp = beanHelper->GetPUweightUp(numGenPV);
        weight_PUDown = beanHelper->GetPUweightDown(numGenPV);
      }
      else {
        weight_PUNominal = beanHelper->GetPUweight(numTruePV);
        weight_PUUp = beanHelper->GetPUweightUp(numTruePV);
        weight_PUDown = beanHelper->GetPUweightDown(numTruePV);
      }
    }
    else if(selectionYearStr == "2012_52x" || selectionYearStr == "2012_53x") {
      weight_PUNominal = beanHelper->GetPUweight(numTruePV);
      weight_PUUp = beanHelper->GetPUweightUp(numTruePV);
      weight_PUDown = beanHelper->GetPUweightDown(numTruePV);
    }
    else {
      assert (selectionYearStr == "Inside PUWeights.h -- either 2012_52x, 2012_53x, or 2011");
    }
  }

  branches["weight_PU"].branchVal = weight_PUNominal;
  if (option_1 != "skipSyst") { 
    branches["weight_PUUp"].branchVal = weight_PUUp;
    branches["weight_PUDown"].branchVal = weight_PUDown;
  }

}


bool PUWeights::passCut() {

  return true;

}

#endif
