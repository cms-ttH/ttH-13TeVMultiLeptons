#ifndef _FinalBDT_ttW_3l_h
#define _FinalBDT_ttW_3l_h

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

#include "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BranchInfo.h"
#include <typeinfo>

class FinalBDT_ttW_3l: public KinematicVariable<double> {

public:
  //Store branch values so they are accessible to other classes
  vector<BranchInfo<double>> myVars;
  
  Float_t varnumMediumBJets;
  Float_t varMT_of_everything;
  Float_t varMT_over_mass_of_everything;
  Float_t varttbar_fake_3l_top_mass_lep_blep;
  Float_t varttW_3l_ttbar_MT_mass_ratio_B_b;
  Float_t varMatch_ttbar_fake_3l_B;
  Float_t varMatch_ttbar_fake_3l_b;
  Float_t varMatch_ttW_3l_B;
  Float_t varMatch_ttW_3l_b;
  Float_t varMatch_ttW_3l_Bb;
  
  vector<TMVA::Reader *> reader;

  BNjetCollection **jets;
  BNjetCollection **mediumCSVJets;
  ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection> * myMTOfEverything;
  ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection> * myMassOfEverything;
  MatchTester_ttbar_fake_3l * myMatchTester_ttbar_fake_3l;
  MatchTester_ttW_3l * myMatchTester_ttW_3l;

  FinalBDT_ttW_3l(BNjetCollection **_jets,
                  BNjetCollection **_mediumCSVJets,
                  ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection> * _myMTOfEverything,
                  ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection> * _myMassOfEverything,
                  MatchTester_ttbar_fake_3l * _myMatchTester_ttbar_fake_3l,
                  MatchTester_ttW_3l * _myMatchTester_ttW_3l);

  void evaluate();

};

FinalBDT_ttW_3l::FinalBDT_ttW_3l(BNjetCollection **_jets,
                                 BNjetCollection **_mediumCSVJets,
                                 ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection> * _myMTOfEverything,
                                 ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection> * _myMassOfEverything,
                                 MatchTester_ttbar_fake_3l * _myMatchTester_ttbar_fake_3l,
                                 MatchTester_ttW_3l * _myMatchTester_ttW_3l):
  jets(_jets), mediumCSVJets(_mediumCSVJets), myMTOfEverything(_myMTOfEverything), myMassOfEverything(_myMassOfEverything),
  myMatchTester_ttbar_fake_3l(_myMatchTester_ttbar_fake_3l), myMatchTester_ttW_3l(_myMatchTester_ttW_3l) {

  //std::cout << "Setting up FinalBDT_ttW_3l" << std::endl;
  
  branches["FinalBDT_ttW_3l"] = BranchInfo<double>("FinalBDT_ttW_3l");
  
  std::vector< TString >catList;
  catList.push_back("eq1j"); //0
  catList.push_back("ge2j"); //1

  for( unsigned int jj = 0 ; jj < 2 ; ++jj ) { //2 readers for 2 BDTs
    
    //std::cout << "Setting up reader " << jj << std::endl;

    reader.push_back( new TMVA::Reader( "!Color:!Silent" ));
    
    if (jj == 1) {
      reader[jj]->AddVariable( "numMediumBJets", &varnumMediumBJets ); 
      reader[jj]->AddVariable( "MT_of_everything", &varMT_of_everything );
      reader[jj]->AddVariable( "MT_over_mass_of_everything", &varMT_over_mass_of_everything );
      reader[jj]->AddVariable( "ttbar_fake_3l_top_mass_lep_blep", &varttbar_fake_3l_top_mass_lep_blep );
      reader[jj]->AddVariable( "ttW_3l_ttbar_MT_mass_ratio_B_b", &varttW_3l_ttbar_MT_mass_ratio_B_b ); }
    reader[jj]->AddVariable( "Match_ttbar_fake_3l_B", &varMatch_ttbar_fake_3l_B );
    reader[jj]->AddVariable( "Match_ttbar_fake_3l_b", &varMatch_ttbar_fake_3l_b ); 
    if (jj == 0) {
      reader[jj]->AddVariable( "Match_ttW_3l_B", &varMatch_ttW_3l_B );
      reader[jj]->AddVariable( "Match_ttW_3l_b", &varMatch_ttW_3l_b ); }
    if (jj == 1) {
      reader[jj]->AddVariable( "Match_ttW_3l_Bb", &varMatch_ttW_3l_Bb ); }
    
    TString dir = (string(getenv("CMSSW_BASE"))+"/src/ttHMultileptonAnalysis/TemplateMakers/data/NOVa/BDT_weights_ttW_3l/").c_str();
    TString label = catList[jj];
    TString file_name = "TMVAClassification_BDTG.weights.xml";
    //TString file_name = "TMVAClassification_CFMlpANN.weights.xml";
    TString weight_file_name = dir + label + "/" + file_name;
    
    reader[jj]->BookMVA( "BDTG method", weight_file_name );
    //reader[jj]->BookMVA( "CFMlpANN method", weight_file_name );
    
    std::cout << "Loading weight file " << weight_file_name << std::endl;
  }

}

void FinalBDT_ttW_3l::evaluate() {
  if (this->evaluatedThisEvent) return;
  if ((*jets)->size() < 1) return;
  evaluatedThisEvent = true;

  //std::cout << "Inside FinalBDT_ttW_3l::evaluate()" << std::endl;
  
  myMTOfEverything->evaluate();
  myMassOfEverything->evaluate();
  myMatchTester_ttbar_fake_3l->evaluate();
  myMatchTester_ttW_3l->evaluate();

  varnumMediumBJets = (*mediumCSVJets)->size()*1.0;
  varMT_of_everything = (*myMTOfEverything).myVars[0].branchVal;
  varMT_over_mass_of_everything = (*myMTOfEverything).myVars[0].branchVal/(*myMassOfEverything).myVars[0].branchVal;

  std::string branchName = "";
  for (unsigned int ii = 0; ii < (*myMatchTester_ttbar_fake_3l).myVars.size(); ii++) {
    branchName = (*myMatchTester_ttbar_fake_3l).myVars[ii].branchName;
    if (branchName == "ttbar_fake_3l_top_mass_lep_blep") varttbar_fake_3l_top_mass_lep_blep = (*myMatchTester_ttbar_fake_3l).myVars[ii].branchVal;
    if (branchName == "Match_ttbar_fake_3l_B") varMatch_ttbar_fake_3l_B = max((*myMatchTester_ttbar_fake_3l).myVars[ii].branchVal,-6.0);
    if (branchName == "Match_ttbar_fake_3l_b") varMatch_ttbar_fake_3l_b = max((*myMatchTester_ttbar_fake_3l).myVars[ii].branchVal,-6.0);
  }
  for (unsigned int ii = 0; ii < (*myMatchTester_ttW_3l).myVars.size(); ii++) {
    branchName = (*myMatchTester_ttW_3l).myVars[ii].branchName;
    if (branchName == "ttW_3l_ttbar_MT_mass_ratio_B_b") varttW_3l_ttbar_MT_mass_ratio_B_b = (*myMatchTester_ttW_3l).myVars[ii].branchVal;
    if (branchName == "Match_ttW_3l_B") varMatch_ttW_3l_B = (*myMatchTester_ttW_3l).myVars[ii].branchVal;
    if (branchName == "Match_ttW_3l_b") varMatch_ttW_3l_b = (*myMatchTester_ttW_3l).myVars[ii].branchVal;
    if (branchName == "Match_ttW_3l_Bb") varMatch_ttW_3l_Bb = (*myMatchTester_ttW_3l).myVars[ii].branchVal;
  }

  for( unsigned int jj = 0 ; jj < 2 ; ++jj ) {
    
    TMVA::Reader  *tmpReader = reader[jj];
    TString mvaName = "BDTG";
    //TString mvaName = "CFMlpANN";

    TString methodName = mvaName + TString(" method");
    Float_t annOut  = tmpReader->EvaluateMVA( methodName );

    if (jj == 0 && (*jets)->size() == 1) branches["FinalBDT_ttW_3l"].branchVal = annOut;
    if (jj == 1 && (*jets)->size() >= 2) branches["FinalBDT_ttW_3l"].branchVal = annOut;

  }

  //Clean out values from last event
  myVars.clear();

  for (typename map<TString, BranchInfo<double>>::iterator iBranch = branches.begin();
       iBranch != branches.end(); iBranch++) {
    myVars.push_back(iBranch->second);
  }
  
}
  

#endif 
