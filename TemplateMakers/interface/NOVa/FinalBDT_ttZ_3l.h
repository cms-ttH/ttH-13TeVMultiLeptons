#ifndef _FinalBDT_ttZ_3l_h
#define _FinalBDT_ttZ_3l_h

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

#include "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BranchInfo.h"
#include <typeinfo>

class FinalBDT_ttZ_3l: public KinematicVariable<double> {

public:
  //Store branch values so they are accessible to other classes
  vector<BranchInfo<double>> myVars;
  
  //Input variables for SS dilepton
  Float_t varnumJets;
  Float_t varnumMediumBJets;
  Float_t varMatch_ttZ_3l_Bb;
  Float_t varMatch_ttZ_3l_Bq;
  Float_t varMatch_ttZ_3l_bq;
  Float_t varMatch_ttZ_3l_Bbq;
  Float_t varMatch_ttZ_3l_Bqq;
  Float_t varMatch_ttZ_3l_bqq;
  Float_t varMatch_ttZ_3l_Bbqq;
  Float_t varZLike_mass_leplep_SFOS_all;
  
  vector<TMVA::Reader *> reader;

  BNjetCollection **jets;
  BNjetCollection **mediumCSVJets;
  MatchTester_ttZ_3l * myMatchTester_ttZ_3l;
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> * myZLikeMassLepLepSFOSAll;

  FinalBDT_ttZ_3l(BNjetCollection **_jets,
                  BNjetCollection **_mediumCSVJets,
                  MatchTester_ttZ_3l * _myMatchTester_ttZ_3l,
                  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> * _myZLikeMassLepLepSFOSAll);

  void evaluate();

};

FinalBDT_ttZ_3l::FinalBDT_ttZ_3l(BNjetCollection **_jets,
                                 BNjetCollection **_mediumCSVJets,
                                 MatchTester_ttZ_3l * _myMatchTester_ttZ_3l,
                                 TwoObjectKinematic<BNleptonCollection,BNleptonCollection> * _myZLikeMassLepLepSFOSAll):
  jets(_jets), mediumCSVJets(_mediumCSVJets), myMatchTester_ttZ_3l(_myMatchTester_ttZ_3l),
  myZLikeMassLepLepSFOSAll(_myZLikeMassLepLepSFOSAll) {

  //std::cout << "Setting up FinalBDT_ttZ_3l" << std::endl;
  
  branches["FinalBDT_ttZ_3l"] = BranchInfo<double>("FinalBDT_ttZ_3l");
  
  std::vector< TString >catList;
  catList.push_back("eq3j"); //0
  catList.push_back("ge4j"); //1

  for( unsigned int jj = 0 ; jj < 2 ; ++jj ) { //2 readers for 2 BDTs
    
    //std::cout << "Setting up reader " << jj << std::endl;

    reader.push_back( new TMVA::Reader( "!Color:!Silent" ));

    if (jj == 1) {
      reader[jj]->AddVariable( "numJets", &varnumJets ); }
    reader[jj]->AddVariable( "numMediumBJets", &varnumMediumBJets );
    if (jj == 0) {
      reader[jj]->AddVariable( "Match_ttZ_3l_Bb", &varMatch_ttZ_3l_Bb );
      reader[jj]->AddVariable( "Match_ttZ_3l_Bq", &varMatch_ttZ_3l_Bq );
      reader[jj]->AddVariable( "Match_ttZ_3l_bq", &varMatch_ttZ_3l_bq ); }
    reader[jj]->AddVariable( "Match_ttZ_3l_Bbq", &varMatch_ttZ_3l_Bbq );
    reader[jj]->AddVariable( "Match_ttZ_3l_Bqq", &varMatch_ttZ_3l_Bqq );
    reader[jj]->AddVariable( "Match_ttZ_3l_bqq", &varMatch_ttZ_3l_bqq );
    if (jj == 1) {
      reader[jj]->AddVariable( "Match_ttZ_3l_Bbqq", &varMatch_ttZ_3l_Bbqq ); }
    reader[jj]->AddVariable( "ZLike_mass_leplep_SFOS_all", &varZLike_mass_leplep_SFOS_all );

    TString dir = (string(getenv("CMSSW_BASE"))+"/src/ttHMultileptonAnalysis/TemplateMakers/data/NOVa/BDT_weights_ttZ_3l/").c_str();
    TString label = catList[jj];
    TString file_name = "TMVAClassification_BDTG.weights.xml";
    //TString file_name = "TMVAClassification_CFMlpANN.weights.xml";
    TString weight_file_name = dir + label + "/" + file_name;

    reader[jj]->BookMVA( "BDTG method", weight_file_name );
    //reader[jj]->BookMVA( "CFMlpANN method", weight_file_name );

    std::cout << "Loading weight file " << weight_file_name << std::endl;
  }

}

void FinalBDT_ttZ_3l::evaluate() {
  if (this->evaluatedThisEvent) return;
  if ((*jets)->size() < 3) return;
  evaluatedThisEvent = true;

  //std::cout << "Inside FinalBDT_ttZ_3l::evaluate()" << std::endl;
  
  myMatchTester_ttZ_3l->evaluate();
  myZLikeMassLepLepSFOSAll->evaluate();
  varnumJets = (*jets)->size()*1.0;
  varnumMediumBJets = (*mediumCSVJets)->size()*1.0;

  std::string branchName = "";
  for (unsigned int ii = 0; ii < (*myMatchTester_ttZ_3l).myVars.size(); ii++) {
    branchName = (*myMatchTester_ttZ_3l).myVars[ii].branchName;
    //std::cout << branchName << std::endl;
    if (branchName == "Match_ttZ_3l_Bb") varMatch_ttZ_3l_Bb = (*myMatchTester_ttZ_3l).myVars[ii].branchVal;
    if (branchName == "Match_ttZ_3l_Bq") varMatch_ttZ_3l_Bq = (*myMatchTester_ttZ_3l).myVars[ii].branchVal;
    if (branchName == "Match_ttZ_3l_bq") varMatch_ttZ_3l_bq = (*myMatchTester_ttZ_3l).myVars[ii].branchVal;
    if (branchName == "Match_ttZ_3l_Bbq") varMatch_ttZ_3l_Bbq = (*myMatchTester_ttZ_3l).myVars[ii].branchVal;
    if (branchName == "Match_ttZ_3l_Bqq") varMatch_ttZ_3l_Bqq = (*myMatchTester_ttZ_3l).myVars[ii].branchVal;
    if (branchName == "Match_ttZ_3l_bqq") varMatch_ttZ_3l_bqq = (*myMatchTester_ttZ_3l).myVars[ii].branchVal;
    if (branchName == "Match_ttZ_3l_Bbqq") varMatch_ttZ_3l_Bbqq = (*myMatchTester_ttZ_3l).myVars[ii].branchVal;
  }
  //std::cout << "Here" << std::endl;
  varZLike_mass_leplep_SFOS_all = (*myZLikeMassLepLepSFOSAll).myVars[0].branchVal;

//   std::cout << "varnumJets: " << varnumJets << std::endl;
//   std::cout << "varnumMediumBJets: " << varnumMediumBJets << std::endl;
//   std::cout << "varMatch_ttZ_3l_Bb: " << varMatch_ttZ_3l_Bb << std::endl;
//   std::cout << "varMatch_ttZ_3l_Bq: " << varMatch_ttZ_3l_Bq << std::endl;
//   std::cout << "varMatch_ttZ_3l_bq: " << varMatch_ttZ_3l_bq << std::endl;
//   std::cout << "varMatch_ttZ_3l_Bbq: " << varMatch_ttZ_3l_Bbq << std::endl;
//   std::cout << "varMatch_ttZ_3l_Bqq: " << varMatch_ttZ_3l_Bqq << std::endl;
//   std::cout << "varMatch_ttZ_3l_bqq: " << varMatch_ttZ_3l_bqq << std::endl;
//   std::cout << "varMatch_ttZ_3l_Bbqq: " << varMatch_ttZ_3l_Bbqq << std::endl;
//   std::cout << "varZLike_mass_leplep_SFOS_all: " << varZLike_mass_leplep_SFOS_all << std::endl;

  for( unsigned int jj = 0 ; jj < 2 ; ++jj ) {
    
    TMVA::Reader  *tmpReader = reader[jj];
    TString mvaName = "BDTG";
    //TString mvaName = "CFMlpANN";

    TString methodName = mvaName + TString(" method");
    Float_t annOut  = tmpReader->EvaluateMVA( methodName );

    if (jj == 0 && (*jets)->size() == 3) branches["FinalBDT_ttZ_3l"].branchVal = annOut;
    if (jj == 1 && (*jets)->size() >= 4) branches["FinalBDT_ttZ_3l"].branchVal = annOut;

  }

  //Clean out values from last event
  myVars.clear();

  for (typename map<TString, BranchInfo<double>>::iterator iBranch = branches.begin();
       iBranch != branches.end(); iBranch++) {
    myVars.push_back(iBranch->second);
  }
  
}
  

#endif 
