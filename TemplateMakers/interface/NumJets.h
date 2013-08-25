
#ifndef _NumJets_h
#define _NumJets_h

class NumJets: public KinematicVariable<int> {

public:
  
  NumJets();

  void evaluate ();
  bool passCut ();
  void setCut (int cut) ;

  int threshold;

};

NumJets::NumJets  () {

  branches["numJets"] = BranchInfo<int>("numJets");
  
}

void NumJets::evaluate () {

  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;
  
  branches["numJets"].branchVal = int(this->blocks->jetCollection->size());
  
}

void NumJets::setCut (int cut) {

  threshold = cut;
  
}

bool NumJets::passCut() {

  evaluate();
  
  if (branches["numJets"].branchVal >= threshold)
    return true;
  return false;

}


#endif 
