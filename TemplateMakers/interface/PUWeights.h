
#ifndef _PUWeights_h
#define _PUWeights_h



///////////////////////////////////////////////////////
//
//
//  Books the 18 variables necessary for 
//  producing the proper CSV weights in your jets
//
//  Note that the weighting doesn't depend on
//  which btag cut you make: it applies for all 
//  CSV values.
//
//
////////////////////////////////////////////////////

class PUWeights: public KinematicVariable<double> {

public:
  
  PUWeights(HelperLeptonCore *in);


  void evaluate ();
  bool passCut ();

  HelperLeptonCore * myHelper;

};

///////////////////////////////////////////////////////////////////////

PUWeights::PUWeights  (HelperLeptonCore *in) :
  myHelper(in)
{

  branches["weight_PU"] = BranchInfo<double>("weight_PU");
  branches["weight_PUup"] = BranchInfo<double>("weight_PUup");
  branches["weight_PUdown"] = BranchInfo<double>("weight_PUdown");
  
  
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
  double weight_PUnominal = 1.0, weight_PUup = 1.0, weight_PUdown = 1.0;

  BNevent iEvent = this->blocks->eventCollection->at(0);

  double numTruePV = iEvent.numTruePV;
  double numGenPV = iEvent.numGenPV;
  

  // data doesn't need a reweight
  if(!isData){

    // legacy stuff
    if(selectionYearStr == "2011") {
      if ((TString(sampleName).Contains("ttH")) || (sampleName=="ttbarW") || (sampleName=="ttbarZ")) {
        weight_PUnominal = beanHelper->GetPUweight(numGenPV);
        weight_PUup = beanHelper->GetPUweightUp(numGenPV);
        weight_PUdown = beanHelper->GetPUweightDown(numGenPV);
      }
      else {
        weight_PUnominal = beanHelper->GetPUweight(numTruePV);
        weight_PUup = beanHelper->GetPUweightUp(numTruePV);
        weight_PUdown = beanHelper->GetPUweightDown(numTruePV);
      }
    }
    else if(selectionYearStr == "2012_52x" || selectionYearStr == "2012_53x") {
      weight_PUnominal = beanHelper->GetPUweight(numTruePV);
      weight_PUup = beanHelper->GetPUweightUp(numTruePV);
      weight_PUdown = beanHelper->GetPUweightDown(numTruePV);
    }
    else {
      assert (selectionYearStr == "Inside PUWeights.h -- either 2012_52x, 2012_53x, or 2011");
    }
  }

  branches["weight_PU"].branchVal = weight_PUnominal;
  branches["weight_PUup"].branchVal = weight_PUup;
  branches["weight_PUdown"].branchVal = weight_PUdown;
  

}


bool PUWeights::passCut() {

  return true;

}

#endif
