
#ifndef _CSVWeights_h
#define _CSVWeights_h



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

class CSVWeights: public KinematicVariable<double> {

public:
  
  CSVWeights(BEANhelper *in);


  void evaluate ();
  bool passCut ();

  BEANhelper * myHelper;

};

CSVWeights::CSVWeights  (BEANhelper *in) :
  myHelper(in)
{

  branches["csvWgtlf"] = BranchInfo<double>("csvWgtlf");
  branches["csvWgtlf_HFUp"] = BranchInfo<double>("csvWgtlf_HFUp");
  branches["csvWgtlf_HFDown"] = BranchInfo<double>("csvWgtlf_HFDown");
  branches["csvWgtlf_Stats1Up"] = BranchInfo<double>("csvWgtlf_Stats1Up");
  branches["csvWgtlf_Stats1Down"] = BranchInfo<double>("csvWgtlf_Stats1Down");
  branches["csvWgtlf_Stats2Up"] = BranchInfo<double>("csvWgtlf_Stats2Up");
  branches["csvWgtlf_Stats2Down"] = BranchInfo<double>("csvWgtlf_Stats2Down");

  
  branches["csvWgthf"] = BranchInfo<double>("csvWgthf");
  branches["csvWgthf_LFUp"] = BranchInfo<double>("csvWgthf_LFUp");
  branches["csvWgthf_LFDown"] = BranchInfo<double>("csvWgthf_LFDown");
  branches["csvWgthf_Stats1Up"] = BranchInfo<double>("csvWgthf_Stats1Up");
  branches["csvWgthf_Stats1Down"] = BranchInfo<double>("csvWgthf_Stats1Down");
  branches["csvWgthf_Stats2Up"] = BranchInfo<double>("csvWgthf_Stats2Up");
  branches["csvWgthf_Stats2Down"] = BranchInfo<double>("csvWgthf_Stats2Down");

  branches["csvWgtc_Err1Up"] = BranchInfo<double>("csvWgtc_Err1Up");
  branches["csvWgtc_Err1Down"] = BranchInfo<double>("csvWgtc_Err1Down");
  branches["csvWgtc_Err2Up"] = BranchInfo<double>("csvWgtc_Err2Up");
  branches["csvWgtc_Err2Down"] = BranchInfo<double>("csvWgtc_Err2Down");
  
  
}

void CSVWeights::evaluate () {

  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  BNjetCollection * myJets = this->blocks->jetCollection;

  vector<double> nominalWeights = myHelper->GetCSVweights(*(myJets), sysType::NA);

  vector<double> csvWgtHFup = myHelper->GetCSVweights( *(myJets), sysType::CSVHFup );
  vector<double> csvWgtHFdown = myHelper->GetCSVweights( *(myJets), sysType::CSVHFdown );
  vector<double> csvWgtLFStats1up = myHelper->GetCSVweights( *(myJets), sysType::CSVLFStats1up );
  vector<double> csvWgtLFStats1down = myHelper->GetCSVweights( *(myJets), sysType::CSVLFStats1down );
  vector<double> csvWgtLFStats2up = myHelper->GetCSVweights( *(myJets), sysType::CSVLFStats2up );
  vector<double> csvWgtLFStats2down = myHelper->GetCSVweights( *(myJets), sysType::CSVLFStats2down );

  vector<double> csvWgtLFup = myHelper->GetCSVweights( *(myJets), sysType::CSVLFup );
  vector<double> csvWgtLFdown = myHelper->GetCSVweights( *(myJets), sysType::CSVLFdown );
  vector<double> csvWgtHFStats1up = myHelper->GetCSVweights( *(myJets), sysType::CSVHFStats1up );
  vector<double> csvWgtHFStats1down = myHelper->GetCSVweights( *(myJets), sysType::CSVHFStats1down );
  vector<double> csvWgtHFStats2up = myHelper->GetCSVweights( *(myJets), sysType::CSVHFStats2up );
  vector<double> csvWgtHFStats2down = myHelper->GetCSVweights( *(myJets), sysType::CSVHFStats2down );

  vector<double> csvWgtcErr1up = myHelper->GetCSVweights( *(myJets), sysType::CSVCErr1up );
  vector<double> csvWgtcErr1down = myHelper->GetCSVweights( *(myJets), sysType::CSVCErr1down );
  vector<double> csvWgtcErr2up = myHelper->GetCSVweights( *(myJets), sysType::CSVCErr2up );
  vector<double> csvWgtcErr2down = myHelper->GetCSVweights( *(myJets), sysType::CSVCErr2down );
      
  branches["csvWgtlf"].branchVal = nominalWeights[1];
  branches["csvWgtlf_HFUp"].branchVal = csvWgtHFup[1];
  branches["csvWgtlf_HFDown"].branchVal = csvWgtHFdown[1];
  branches["csvWgtlf_Stats1Up"].branchVal = csvWgtLFStats1up[1];
  branches["csvWgtlf_Stats1Down"].branchVal = csvWgtLFStats1down[1];
  branches["csvWgtlf_Stats2Up"].branchVal = csvWgtLFStats2up[1];
  branches["csvWgtlf_Stats2Down"].branchVal = csvWgtLFStats2down[1];

  
  branches["csvWgthf"].branchVal = nominalWeights[0];
  branches["csvWgthf_LFUp"].branchVal = csvWgtLFup[0];
  branches["csvWgthf_LFDown"].branchVal = csvWgtLFdown[0];
  branches["csvWgthf_Stats1Up"].branchVal = csvWgtHFStats1up[0];
  branches["csvWgthf_Stats1Down"].branchVal = csvWgtHFStats1down[0];
  branches["csvWgthf_Stats2Up"].branchVal = csvWgtHFStats2up[0];
  branches["csvWgthf_Stats2Down"].branchVal = csvWgtHFStats2down[0];

  branches["csvWgtc_Err1Up"].branchVal = csvWgtcErr1up[2];
  branches["csvWgtc_Err1Down"].branchVal = csvWgtcErr1down[2];
  branches["csvWgtc_Err2Up"].branchVal = csvWgtcErr2up[2];
  branches["csvWgtc_Err2Down"].branchVal = csvWgtcErr2down[2];

  

}


bool CSVWeights::passCut() {

  return true;

}

#endif
