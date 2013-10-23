#ifndef _FinalBDT_h
#define _FinalBDT_h

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

#include "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BranchInfo.h"
#include <typeinfo>

class FinalBDT: public KinematicVariable<double> {

public:

  double FinalBDT_TwoMuon;
  double FinalBDT_MuonEle;
  double FinalBDT_TwoEle;

  //Input variables for SS dilepton
  Float_t varlep2AbsEta;
  Float_t varlep2Pt;
  Float_t varMHT;
  Float_t varmindr_lep2_jet;
  Float_t varMT_met_lep1;
  Float_t varsum_pt;
  
  vector<TMVA::Reader *> reader;

  GenericCollectionMember<double, BNleptonCollection> * tightLeptonEta;
  GenericCollectionMember<double, BNleptonCollection> * tightLeptonPt;
  TwoObjectKinematic<BNleptonCollection,BNjetCollection> * myMHT;
  TwoObjectKinematic<BNleptonCollection,BNjetCollection> *myMinDeltaRLep2Jet;
  TwoObjectKinematic<BNmetCollection,BNleptonCollection> *myMtMetLep;
  TwoObjectKinematic<BNleptonCollection,BNjetCollection> *mySumPt;

  FinalBDT(GenericCollectionMember<double, BNleptonCollection> * input_tightLeptonEta,
           GenericCollectionMember<double, BNleptonCollection> * input_tightLeptonPt,
           TwoObjectKinematic<BNleptonCollection,BNjetCollection> * input_myMHT,
           TwoObjectKinematic<BNleptonCollection,BNjetCollection> * input_myMinDeltaRLep2Jet,
           TwoObjectKinematic<BNmetCollection,BNleptonCollection> * input_myMtMetLep,
           TwoObjectKinematic<BNleptonCollection,BNjetCollection> * input_mySumPt);

  void evaluate();

};

FinalBDT::FinalBDT(GenericCollectionMember<double, BNleptonCollection> * input_tightLeptonEta,
                   GenericCollectionMember<double, BNleptonCollection> * input_tightLeptonPt,
                   TwoObjectKinematic<BNleptonCollection,BNjetCollection> * input_myMHT,
                   TwoObjectKinematic<BNleptonCollection,BNjetCollection> * input_myMinDeltaRLep2Jet,
                   TwoObjectKinematic<BNmetCollection,BNleptonCollection> * input_myMtMetLep,
                   TwoObjectKinematic<BNleptonCollection,BNjetCollection> * input_mySumPt):
  tightLeptonEta(input_tightLeptonEta), tightLeptonPt(input_tightLeptonPt), myMHT(input_myMHT),
  myMinDeltaRLep2Jet(input_myMinDeltaRLep2Jet), myMtMetLep(input_myMtMetLep), mySumPt(input_mySumPt) {
  
  branches["FinalBDT_TwoMuon"] = BranchInfo<double>("FinalBDT_TwoMuon");
  branches["FinalBDT_MuonElectron"] = BranchInfo<double>("FinalBDT_MuonElectron");
  branches["FinalBDT_TwoElectron"] = BranchInfo<double>("FinalBDT_TwoElectron");
  
  std::vector< TString >catList;
  catList.push_back("SS_ge4jge1t_useSide_2_6var_TwoMuon");
  catList.push_back("SS_ge4jge1t_useSide_2_6var_MuonEle");
  catList.push_back("SS_ge4jge1t_useSide_2_6var_TwoEle");
  
  for( unsigned int j = 0 ; j < 3 ; ++j ) { //3 readers for 3 BDTs

    reader.push_back( new TMVA::Reader( "!Color:!Silent" ));
    
    reader[j]->AddVariable( "lep2AbsEta", &varlep2AbsEta );
    reader[j]->AddVariable( "lep2Pt", &varlep2Pt );
    reader[j]->AddVariable( "MHT", &varMHT );
    reader[j]->AddVariable( "mindr_lep2_jet", &varmindr_lep2_jet );
    reader[j]->AddVariable( "MT_met_lep1", &varMT_met_lep1 );
    reader[j]->AddVariable( "sum_pt", &varsum_pt );
    
    TString dir = "../data/BDT_weights/";
    TString label = catList[j];
    TString file_name = "TMVAClassification_BDTG.weights.xml";
    //TString file_name = "TMVAClassification_CFMlpANN.weights.xml";
    TString weight_file_name = dir + label + "/" + file_name;

    reader[j]->BookMVA( "BDTG method", weight_file_name );
    //reader[j]->BookMVA( "CFMlpANN method", weight_file_name );

    std::cout << "Loading weight file " << weight_file_name << std::endl;
  }

}

void FinalBDT::evaluate() {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;
  
  //--------
  
  tightLeptonEta->evaluate();
  tightLeptonPt->evaluate();
  myMHT->evaluate();
  myMinDeltaRLep2Jet->evaluate();
  myMtMetLep->evaluate();
  mySumPt->evaluate();
  
  varlep2AbsEta = abs((*tightLeptonEta).myVars[1].branchVal); //Get the branch for the second lepton
  varlep2Pt = (*tightLeptonPt).myVars[1].branchVal; //Get the branch for the second lepton
  varMHT = (*myMHT).myVars[0].branchVal;
  varmindr_lep2_jet = (*myMinDeltaRLep2Jet).myVars[0].branchVal;
  varMT_met_lep1 = (*myMtMetLep).myVars[0].branchVal;
  varsum_pt = (*mySumPt).myVars[0].branchVal;

  for( unsigned int j = 0 ; j < 3 ; ++j ) {
    
    TMVA::Reader  *tmpReader = reader[j];
    TString mvaName = "BDTG";
    //TString mvaName = "CFMlpANN";

    //TString bName = mvaName + TString("_") + catList[j];
    TString bName = "";
    if (j==0) bName = "FinalBDT_TwoMuon";
    if (j==1) bName = "FinalBDT_MuonElectron";
    if (j==2) bName = "FinalBDT_TwoElectron";
    
    TString methodName = mvaName + TString(" method");
    Float_t annOut  = tmpReader->EvaluateMVA( methodName );
    
    branches[bName].branchVal = annOut;
  }
  
}
  

#endif 
