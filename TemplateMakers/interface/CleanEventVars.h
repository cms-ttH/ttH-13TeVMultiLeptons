
#ifndef _CleanEventVars_h
#define _CleanEventVars_h

//
//   isCleanEvent
//   has 3 different checks
//
//   1. A vertex passing qual cuts exists
//   2. The event is not flagged as scraping
//   3. The event passes the HBHE noise filter
//
//   Alternatively, if the event is MC,
//   then we just say pass.
//


class CleanEventVars: public KinematicVariable<int> {

public:
  
  CleanEventVars(HelperLeptonCore * in);

  void evaluate ();
  bool passCut ();
  void reset();
  //void setCut () ;

  int calculateNumGoodPVs (BNprimaryvertexCollection * pvCol);

  // Not stored, but calculated 
  bool passGoodVertex;
  bool passFilterOutScraping;
  bool passHBHENoiseFilter;  
  bool isData;
  
  HelperLeptonCore * myHelper;

  static constexpr float minNDOF = 4;
  static constexpr float maxAbsZ = 24;
  static constexpr float maxd0 = 2.;

  
};

CleanEventVars::CleanEventVars  (HelperLeptonCore *in ):
  myHelper(in)
{

  branches["isCleanEvent"] = BranchInfo<int>("isCleanEvent");
  
}

void CleanEventVars::evaluate () {

  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;


  isData = myHelper->isData;

  if (!isData) {

    // case MC: don't let any event fail
    passGoodVertex = true;
    passFilterOutScraping = true;
    passHBHENoiseFilter = true;
    branches["isCleanEvent"].branchVal = true;

  } else {

    BNevent & myEvent = blocks->eventCollection->at(0);
    
    int numPV = calculateNumGoodPVs(blocks->primaryVertexCollection);
    passGoodVertex =  (numPV >0) ? true : false;

    passFilterOutScraping = (myEvent.FilterOutScraping==1) ? true : false;

    passHBHENoiseFilter = (myEvent.HBHENoiseFilter==1) ? true : false;
    
    branches["isCleanEvent"].branchVal = (passGoodVertex && passFilterOutScraping && passHBHENoiseFilter) ? 1 : 0;
  }
  
    
  
}

void CleanEventVars::reset () {

  passGoodVertex = false;
  passFilterOutScraping = false;
  passHBHENoiseFilter = false;
  isData = false;
  
  
  // call the parent class reset
  KinematicVariable<int>::reset();
  
}

bool CleanEventVars::passCut() {

  evaluate();
  
  if (branches["isCleanEvent"].branchVal == 1)
    return true;
  return false;

}

int CleanEventVars::calculateNumGoodPVs(BNprimaryvertexCollection * pvCol) {

  int numGoodPVs = 0;
  for (int iPV = 0; iPV < (pvCol->size()); iPV++) {

    BNprimaryvertex & thisPV = pvCol->at(iPV);
    
    bool isGood = ( (thisPV.ndof >= minNDOF)
                    && (thisPV.z < maxAbsZ)
                    && (thisPV.rho < maxd0) );

    bool isFake = ( thisPV.isFake ==1);
    if( isGood && !isFake) numGoodPVs++;

  }
  return numGoodPVs;
  
}


#endif 
