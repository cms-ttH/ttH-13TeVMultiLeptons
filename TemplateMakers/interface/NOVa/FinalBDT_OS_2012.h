#ifndef _FinalBDT_OS_2012_h
#define _FinalBDT_OS_2012_h

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

#include "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BranchInfo.h"
#include <typeinfo>

class FinalBDT_OS_2012: public KinematicVariable<double> {

public:

  double BDT_eq3jeq2t;
  double BDT_ge4jeq2t;
  double BDT_ge3tt;

  //Input variables for SS dilepton
  Float_t varmin_dr_jets;
  Float_t varsum_pt;
  Float_t varavg_btag_disc_btags;
  Float_t varavg_btag_disc_non_btags;
  Float_t varhiggsLike_dijet_mass;
  Float_t varhiggsLike_dijet_mass2;
  Float_t varnumJets_float;
  Float_t varnumHiggsLike_dijet_15_float;
  
  vector<TMVA::Reader *> reader;

  TwoObjectKinematic<BNjetCollection,BNjetCollection> * myMinDrJets;
  TwoObjectKinematic<BNleptonCollection,BNjetCollection> * mySumPt;
  TwoJetVariables * myAvgBtagDiscBtags;
  TwoJetVariables * myAvgBtagDiscNonBtags;
  TwoObjectKinematic<BNjetCollection,BNjetCollection> * myHiggsLikeDijetMass;
  TwoObjectKinematic<BNjetCollection,BNjetCollection> * myHiggsLikeDijetMass2;
  TwoObjectKinematic<BNjetCollection,BNjetCollection> * myNumJetsFloat;
  TwoObjectKinematic<BNjetCollection,BNjetCollection> * myNumHiggsLikeDijet15;
  
  FinalBDT_OS_2012(TwoObjectKinematic<BNjetCollection,BNjetCollection> * _myMinDrJets,
                   TwoObjectKinematic<BNleptonCollection,BNjetCollection> * _mySumPt,
                   TwoJetVariables * _myAvgBtagDiscBtags,
                   TwoJetVariables * _myAvgBtagDiscNonBtags,
                   TwoObjectKinematic<BNjetCollection,BNjetCollection> * _myHiggsLikeDijetMass,
                   TwoObjectKinematic<BNjetCollection,BNjetCollection> * _myHiggsLikeDijetMass2,
                   TwoObjectKinematic<BNjetCollection,BNjetCollection> * _myNumJetsFloat,
                   TwoObjectKinematic<BNjetCollection,BNjetCollection> * _myNumHiggsLikeDijet15);

  void evaluate();

};

FinalBDT_OS_2012::FinalBDT_OS_2012(TwoObjectKinematic<BNjetCollection,BNjetCollection> * _myMinDrJets,
                                   TwoObjectKinematic<BNleptonCollection,BNjetCollection> * _mySumPt,
                                   TwoJetVariables * _myAvgBtagDiscBtags,
                                   TwoJetVariables * _myAvgBtagDiscNonBtags,
                                   TwoObjectKinematic<BNjetCollection,BNjetCollection> * _myHiggsLikeDijetMass,
                                   TwoObjectKinematic<BNjetCollection,BNjetCollection> * _myHiggsLikeDijetMass2,
                                   TwoObjectKinematic<BNjetCollection,BNjetCollection> * _myNumJetsFloat,
                                   TwoObjectKinematic<BNjetCollection,BNjetCollection> * _myNumHiggsLikeDijet15):
  myMinDrJets(_myMinDrJets), mySumPt(_mySumPt), myAvgBtagDiscBtags(_myAvgBtagDiscBtags),
  myAvgBtagDiscNonBtags(_myAvgBtagDiscNonBtags), myHiggsLikeDijetMass(_myHiggsLikeDijetMass),
  myHiggsLikeDijetMass2(_myHiggsLikeDijetMass2), myNumJetsFloat(_myNumJetsFloat), myNumHiggsLikeDijet15(_myNumHiggsLikeDijet15) {
  
  branches["BDT_eq3jeq2t"] = BranchInfo<double>("BDT_eq3jeq2t");
  branches["BDT_ge4jeq2t"] = BranchInfo<double>("BDT_ge4jeq2t");
  branches["BDT_ge3t"] = BranchInfo<double>("BDT_ge3t");
  
  std::vector< TString >catList;
  catList.push_back("eq3jeq2t");
  catList.push_back("ge4jeq2t");
  catList.push_back("ge3t");
  
  for( unsigned int j = 0 ; j < 3 ; ++j ) { //3 readers for 3 BDTs

    reader.push_back( new TMVA::Reader( "!Color:!Silent" ));
    
    reader[j]->AddVariable( "min_dr_jets", &varmin_dr_jets );
    if ( j == 1 || j == 2 ) reader[j]->AddVariable( "higgsLike_dijet_mass", &varhiggsLike_dijet_mass );
    if ( j == 1 || j == 2 ) reader[j]->AddVariable( "higgsLike_dijet_mass2", &varhiggsLike_dijet_mass2 );
    if ( j == 1           ) reader[j]->AddVariable( "numJets_float", &varnumJets_float );
    if ( j == 2           ) reader[j]->AddVariable( "numHiggsLike_dijet_15_float", &varnumHiggsLike_dijet_15_float );
    reader[j]->AddVariable( "sum_pt", &varsum_pt );
    if ( j == 0 || j == 2 ) reader[j]->AddVariable( "avg_btag_disc_btags", &varavg_btag_disc_btags );
    if ( j == 0 || j == 1 ) reader[j]->AddVariable( "avg_btag_disc_non_btags", &varavg_btag_disc_btags );


    TString dir = (string(getenv("CMSSW_BASE"))+"/src/ttHMultileptonAnalysis/TemplateMakers/data/NOVa/BDT_weights_OS_2012/").c_str();
    TString label = catList[j];
    TString file_name = "TMVAClassification_BDTG.weights.xml";
    //TString file_name = "TMVAClassification_CFMlpANN.weights.xml";
    TString weight_file_name = dir + label + "/" + file_name;

    reader[j]->BookMVA( "BDTG method", weight_file_name );
    //reader[j]->BookMVA( "CFMlpANN method", weight_file_name );

    std::cout << "Loading weight file " << weight_file_name << std::endl;
  }

}

void FinalBDT_OS_2012::evaluate() {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;
  
  //--------
  
  myMinDrJets->evaluate();
  mySumPt->evaluate();
  myAvgBtagDiscBtags->evaluate();
  myAvgBtagDiscNonBtags->evaluate();
  myHiggsLikeDijetMass->evaluate();
  myHiggsLikeDijetMass2->evaluate();
  myNumJetsFloat->evaluate();
  myNumHiggsLikeDijet15->evaluate();
    
  varmin_dr_jets = (*myMinDrJets).myVars[0].branchVal;
  varsum_pt = (*mySumPt).myVars[0].branchVal;
  varavg_btag_disc_btags = (*myAvgBtagDiscBtags).myVars[0].branchVal;
  varavg_btag_disc_non_btags = (*myAvgBtagDiscNonBtags).myVars[0].branchVal;
  varhiggsLike_dijet_mass = (*myHiggsLikeDijetMass).myVars[0].branchVal;
  varhiggsLike_dijet_mass2 = (*myHiggsLikeDijetMass2).myVars[0].branchVal;
  varnumJets_float = (*myNumJetsFloat).myVars[0].branchVal;
  varnumHiggsLike_dijet_15_float = (*myNumHiggsLikeDijet15).myVars[0].branchVal;

  for( unsigned int j = 0 ; j < 3 ; ++j ) {
    
    TMVA::Reader  *tmpReader = reader[j];
    TString mvaName = "BDTG";
    //TString mvaName = "CFMlpANN";

    //TString bName = mvaName + TString("_") + catList[j];
    TString bName = "";
    if (j==0) bName = "BDT_eq3jeq2t";
    if (j==1) bName = "BDT_ge4jeq2t";
    if (j==2) bName = "BDT_ge3t";
    
    TString methodName = mvaName + TString(" method");
    Float_t annOut  = tmpReader->EvaluateMVA( methodName );
    
    branches[bName].branchVal = annOut;
  }
  
}
  

#endif 
