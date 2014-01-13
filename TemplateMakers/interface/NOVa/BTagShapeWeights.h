#ifndef _BTagShapeWeights_h
#define _BTagShapeWeights_h

#include "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BranchInfo.h" 

class BTagShapeWeights: public KinematicVariable<double> {
  
public:
  //Store branch values so they are accessible to other classes
  vector<BranchInfo<double>> myVars;
  
  HelperLeptonCore * myHelper;
  BNjetCollection ** jetCollection;
  string branch_name;

  TString branchName;
  TString branchNameLF;
  TString branchNameHF;

  BTagShapeWeights(HelperLeptonCore *input_myHelper, BNjetCollection **input_jetCollection,
          string input_branch_name);

  void evaluate ();
  
};

BTagShapeWeights::BTagShapeWeights(HelperLeptonCore *input_myHelper, BNjetCollection **input_jetCollection,
                                 string input_branch_name):
  myHelper(input_myHelper), jetCollection(input_jetCollection),
  branch_name(input_branch_name)
{
  this->resetVal = KinematicVariableConstants::DOUBLE_INIT;

  branchName = branch_name.c_str();
  branchNameLF = Form("%s_LF", branch_name.c_str());
  branchNameHF = Form("%s_HF", branch_name.c_str());

  branches[branchName] = BranchInfo<double>(branchName);
  branches[branchNameLF] = BranchInfo<double>(branchNameLF);
  branches[branchNameHF] = BranchInfo<double>(branchNameHF);

}

void BTagShapeWeights::evaluate () {

  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  //--------

  BEANhelper * beanHelper = &(myHelper->bHelp);

  sysType::sysType iSysType = sysType::NA;

//   BNjetCollection const &selectedJets_unsorted  = beanHelper.GetSelectedJets( pfjetsSelected, 30., 2.4, jetID::jetLoose, '-' );
//   BNjetCollection const &selectedJets       = beanHelper.GetSortedByPt( selectedJets_unsorted );
  vdouble csvWgt = beanHelper->GetCSVweights( **jetCollection, iSysType );

  branchName = branch_name.c_str();
  branchNameLF = Form("%s_LF", branch_name.c_str());
  branchNameHF = Form("%s_HF", branch_name.c_str());

  branches[branchName].branchVal = csvWgt[0]*csvWgt[1];
  branches[branchNameLF].branchVal = csvWgt[1];
  branches[branchNameHF].branchVal = csvWgt[0];
  

  //Clean out values from last event
  myVars.clear();

  for ( typename map<TString, BranchInfo<double>>::iterator iBranch = branches.begin();
        iBranch != branches.end(); iBranch++ ) {
    myVars.push_back(iBranch->second);
  }
  
      
}


#endif 
