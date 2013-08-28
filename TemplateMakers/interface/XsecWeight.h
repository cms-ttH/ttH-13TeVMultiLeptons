
#ifndef _XsecWeight_h
#define _XsecWeight_h




///////////////////////////////////////////////////////
//
//
//    Cross section weight is for samples
//    that are split by num partons or by
//    lep decay mode.
//
//    The actual calculation is in HelperLeptonCore.cc
//
//
////////////////////////////////////////////////////

class XsecWeight: public KinematicVariable<double> {

public:
  
  XsecWeight(HelperLeptonCore *in);


  void evaluate ();
  bool passCut ();

  HelperLeptonCore * myHelper;

};

///////////////////////////////////////////////////////////////////////

XsecWeight::XsecWeight  (HelperLeptonCore *in) :
  myHelper(in)
{

  branches["weight_Xsec"] = BranchInfo<double>("weight_Xsec");
  this->resetVal = KinematicVariableConstants::DOUBLE_INIT;
}

void XsecWeight::evaluate () {
  
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;



  branches["weight_Xsec"].branchVal = myHelper->weight_Xsec;


  

}


bool XsecWeight::passCut() {

  return true;

}

#endif
