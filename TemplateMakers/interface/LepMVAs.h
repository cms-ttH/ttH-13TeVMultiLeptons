#ifndef _LepMVAs_h
#define _LepMVAs_h

#include "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BranchInfo.h" 
#include <typeinfo>

template <class collectionType> 
class LepMVAs: public KinematicVariable<double> {
  
public:
  //Store branch values so they are accessible to other classes
  vector<BranchInfo<double>> myVars;
  
  HelperLeptonCore * myHelper;
  collectionType **selCollection;
  string branch_name;
  unsigned int maxLeptons;

  TString branchName;

  LepMVAs(HelperLeptonCore *input_myHelper, collectionType **input_selCollection,
          string input_branch_name, int input_maxLeptons);

  void evaluate ();
  
};

template <class collectionType>
LepMVAs<collectionType>::LepMVAs(HelperLeptonCore *input_myHelper, collectionType **input_selCollection,
                                 string input_branch_name, int input_maxLeptons):
  myHelper(input_myHelper), selCollection(input_selCollection),
  branch_name(input_branch_name), maxLeptons(input_maxLeptons)
{
  this->resetVal = KinematicVariableConstants::DOUBLE_INIT;
  
  for (unsigned int i=0; i<maxLeptons; i++) {
    branchName = Form("%s_%d_lepMVA", branch_name.c_str(), i+1);
    branches[branchName] = BranchInfo<double>(branchName);
    branches[branchName].branchVal = this->resetVal;
  }

}

template <class collectionType>
void LepMVAs<collectionType>::evaluate () {

  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  //--------

  BEANhelper * beanHelper = &(myHelper->bHelp);

  for (unsigned int iObj = 0; iObj < (*selCollection)->size(); iObj++) {
    if ( iObj < maxLeptons ) {

      branchName = Form("%s_%d_lepMVA", branch_name.c_str(), iObj+1);
      
      if ( ptr((*selCollection)->at(iObj))->isElectron ) {
        branches[branchName].branchVal = beanHelper->GetElectronLepMVA(*(BNelectron*)ptr((*selCollection)->at(iObj)),
                                                                       this->blocks->jetsForLepMVACollection);
      }
      else if ( ptr((*selCollection)->at(iObj))->isMuon ) {
        branches[branchName].branchVal = beanHelper->GetMuonLepMVA(*(BNmuon*)ptr((*selCollection)->at(iObj)),
                                                                       this->blocks->jetsForLepMVACollection);
      }
      
    }//End if ( iObj < maxLeptons )
  }//End for iObj

  //Clean out values from last event
  myVars.clear();

  for ( typename map<TString, BranchInfo<double>>::iterator iBranch = branches.begin();
        iBranch != branches.end(); iBranch++ ) {
    myVars.push_back(iBranch->second);
  }
  
      
}


#endif 
