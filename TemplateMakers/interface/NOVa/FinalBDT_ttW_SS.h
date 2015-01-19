#ifndef _FinalBDT_ttW_SS_h
#define _FinalBDT_ttW_SS_h

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/KinematicVariable.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/BranchInfo.h"
#include <typeinfo>

class FinalBDT_ttW_SS: public KinematicVariable<double> {

public:
  //Store branch values so they are accessible to other classes
  vector<BranchInfo<double>> myVars;

  Float_t varMatch_ttW_SS_Bb;
  Float_t varMatch_ttW_SS_Bq;
  Float_t varMatch_ttW_SS_bq;
  Float_t varttbar_fake_SS_top_mass_blep_qq;
  Float_t varMatch_ttW_SS_Bbq;
  Float_t varMatch_ttW_SS_Bbqq;
  Float_t varMatch_ttbar_fake_SS_Bq;
  Float_t varMatch_ttbar_fake_SS_Bqq;
  Float_t varmet_ld;
  Float_t varjets_by_CSV_2_btagCombinedSecVertex;
  Float_t varMT_of_everything;

  vector<TMVA::Reader *> reader;

  MatchTester_ttW_SS * myMatchTester_ttW_SS;
  MatchTester_ttbar_fake_SS * myMatchTester_ttbar_fake_SS;
  MetLD * myMetLD;
  BNjetCollection **jetsByCSV; 
  ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection> * myMTOfEverything;

  FinalBDT_ttW_SS(MatchTester_ttW_SS * _myMatchTester_ttW_SS,
                  MatchTester_ttbar_fake_SS * _myMatchTester_ttbar_fake_SS,
                  MetLD * _myMetLD,
                  BNjetCollection **_jetsByCSV,
                  ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection> * _myMTOfEverything);

  void evaluate();

};

FinalBDT_ttW_SS::FinalBDT_ttW_SS(MatchTester_ttW_SS * _myMatchTester_ttW_SS,
                                 MatchTester_ttbar_fake_SS * _myMatchTester_ttbar_fake_SS,
                                 MetLD * _myMetLD,
                                 BNjetCollection **_jetsByCSV,
                                 ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection> * _myMTOfEverything):
  myMatchTester_ttW_SS(_myMatchTester_ttW_SS), myMatchTester_ttbar_fake_SS(_myMatchTester_ttbar_fake_SS),
  myMetLD(_myMetLD), jetsByCSV(_jetsByCSV), myMTOfEverything(_myMTOfEverything) {

  //std::cout << "Setting up FinalBDT_ttW_SS" << std::endl;
  
  branches["FinalBDT_ttW_SS"] = BranchInfo<double>("FinalBDT_ttW_SS");
  branches["FinalBDT_ttW_SS_QCD"] = BranchInfo<double>("FinalBDT_ttW_SS_QCD");
  
  std::vector< TString >catList;
  catList.push_back("eq2j"); //0
  catList.push_back("eq3j"); //1
  catList.push_back("ge4j"); //2
  catList.push_back("eq2j_QCD"); //3
  catList.push_back("eq3j_QCD"); //4
  catList.push_back("ge4j_QCD"); //5

  for( unsigned int jj = 0 ; jj < 6 ; ++jj ) { //6 readers for 6 BDTs
    
    //std::cout << "Setting up reader " << jj << std::endl;

    reader.push_back( new TMVA::Reader( "!Color:!Silent" ));

    if (jj == 0) {
      reader[jj]->AddVariable( "Match_ttW_SS_Bb", &varMatch_ttW_SS_Bb );
      reader[jj]->AddVariable( "Match_ttW_SS_Bq", &varMatch_ttW_SS_Bq );
      reader[jj]->AddVariable( "Match_ttW_SS_bq", &varMatch_ttW_SS_bq ); 
      reader[jj]->AddVariable( "Match_ttbar_fake_SS_Bq", &varMatch_ttbar_fake_SS_Bq ); }
    if (jj == 1) {
      reader[jj]->AddVariable( "ttbar_fake_SS_top_mass_blep_qq", &varttbar_fake_SS_top_mass_blep_qq ); }
    if (jj == 1 || jj == 2) {
      reader[jj]->AddVariable( "Match_ttW_SS_Bbq", &varMatch_ttW_SS_Bbq ); }
    if (jj == 2) {
      reader[jj]->AddVariable( "Match_ttW_SS_Bbqq", &varMatch_ttW_SS_Bbqq ); }
    if (jj == 1 || jj == 2) {
      reader[jj]->AddVariable( "Match_ttbar_fake_SS_Bqq", &varMatch_ttbar_fake_SS_Bqq ); }
    reader[jj]->AddVariable( "met_ld", &varmet_ld );
    reader[jj]->AddVariable( "jets_by_CSV_2_btagCombinedSecVertex", &varjets_by_CSV_2_btagCombinedSecVertex );
    reader[jj]->AddVariable( "MT_of_everything", &varMT_of_everything );
    
    TString dir = (string(getenv("CMSSW_BASE"))+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/NOVa/BDT_weights_ttW_SS/").c_str();
    TString label = catList[jj];
    TString file_name = "TMVAClassification_BDTG.weights.xml";
    //TString file_name = "TMVAClassification_CFMlpANN.weights.xml";
    TString weight_file_name = dir + label + "/" + file_name;
    
    reader[jj]->BookMVA( "BDTG method", weight_file_name );
    //reader[jj]->BookMVA( "CFMlpANN method", weight_file_name );
    
    std::cout << "Loading weight file " << weight_file_name << std::endl;
  }

}

void FinalBDT_ttW_SS::evaluate() {
  if (this->evaluatedThisEvent) return;
  if ((*jetsByCSV)->size() < 2) return;
  evaluatedThisEvent = true;

  //std::cout << "Inside FinalBDT_ttW_SS::evaluate()" << std::endl;
  
  myMatchTester_ttW_SS->evaluate();
  myMatchTester_ttbar_fake_SS->evaluate();
  myMetLD->evaluate();
  myMTOfEverything->evaluate();

  varmet_ld = (*myMetLD).myVars[0].branchVal;
  varjets_by_CSV_2_btagCombinedSecVertex = (*jetsByCSV)->at(1).btagCombinedSecVertex;
  varMT_of_everything = (*myMTOfEverything).myVars[0].branchVal;

  std::string branchName = "";
  for (unsigned int ii = 0; ii < (*myMatchTester_ttW_SS).myVars.size(); ii++) {
    branchName = (*myMatchTester_ttW_SS).myVars[ii].branchName;
    if (branchName == "Match_ttW_SS_Bb") varMatch_ttW_SS_Bb = (*myMatchTester_ttW_SS).myVars[ii].branchVal;
    if (branchName == "Match_ttW_SS_Bq") varMatch_ttW_SS_Bq = (*myMatchTester_ttW_SS).myVars[ii].branchVal;
    if (branchName == "Match_ttW_SS_bq") varMatch_ttW_SS_bq = (*myMatchTester_ttW_SS).myVars[ii].branchVal;
    if (branchName == "Match_ttW_Bbq") varMatch_ttW_SS_Bbq = (*myMatchTester_ttW_SS).myVars[ii].branchVal;
    if (branchName == "Match_ttW_SS_Bbqq") varMatch_ttW_SS_Bbqq = (*myMatchTester_ttW_SS).myVars[ii].branchVal;
  }
  for (unsigned int ii = 0; ii < (*myMatchTester_ttbar_fake_SS).myVars.size(); ii++) {
    branchName = (*myMatchTester_ttbar_fake_SS).myVars[ii].branchName;
    if (branchName == "ttbar_fake_SS_top_mass_blep_qq") varttbar_fake_SS_top_mass_blep_qq = (*myMatchTester_ttbar_fake_SS).myVars[ii].branchVal;
    if (branchName == "Match_ttbar_fake_SS_Bq") varMatch_ttbar_fake_SS_Bq = (*myMatchTester_ttbar_fake_SS).myVars[ii].branchVal;
    if (branchName == "Match_ttbar_fake_SS_Bqq") varMatch_ttbar_fake_SS_Bqq = (*myMatchTester_ttbar_fake_SS).myVars[ii].branchVal;
  }

  for( unsigned int jj = 0 ; jj < 6 ; ++jj ) {
    
    TMVA::Reader  *tmpReader = reader[jj];
    TString mvaName = "BDTG";
    //TString mvaName = "CFMlpANN";

    TString methodName = mvaName + TString(" method");
    Float_t annOut  = tmpReader->EvaluateMVA( methodName );

    if (jj == 0 && (*jetsByCSV)->size() == 2) branches["FinalBDT_ttW_SS"].branchVal = annOut;
    if (jj == 1 && (*jetsByCSV)->size() == 3) branches["FinalBDT_ttW_SS"].branchVal = annOut;
    if (jj == 2 && (*jetsByCSV)->size() >= 4) branches["FinalBDT_ttW_SS"].branchVal = annOut;
    if (jj == 3 && (*jetsByCSV)->size() == 2) branches["FinalBDT_ttW_SS_QCD"].branchVal = annOut;
    if (jj == 4 && (*jetsByCSV)->size() == 3) branches["FinalBDT_ttW_SS_QCD"].branchVal = annOut;
    if (jj == 5 && (*jetsByCSV)->size() >= 4) branches["FinalBDT_ttW_SS_QCD"].branchVal = annOut;

  }

  //Clean out values from last event
  myVars.clear();

  for (typename map<TString, BranchInfo<double>>::iterator iBranch = branches.begin();
       iBranch != branches.end(); iBranch++) {
    myVars.push_back(iBranch->second);
  }
  
}
  

#endif 
