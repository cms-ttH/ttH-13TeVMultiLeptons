#ifndef _FinalBDT_3l_h
#define _FinalBDT_3l_h

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

#include "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BranchInfo.h"
#include <typeinfo>

class FinalBDT_3l: public KinematicVariable<double> {

public:

  double FinalBDT_ThreeLepton;

  //Input variables for SS dilepton
  Float_t varbestMTopHad;
  Float_t varnJet25;
  Float_t varJet1_pt;
  Float_t varmax_Lep_eta;
  Float_t varminDrllAFOS;
  Float_t varhtJet25;
  Float_t varhtJet25ratio1224Lep;
  
  vector<TMVA::Reader *> reader;

  ThreeObjectKinematic<BNjetCollection,BNjetCollection,BNjetCollection> * myTopLikeTrijetMass;
  GenericCollectionSizeVariable<BNjetCollection> * numJets;
  GenericCollectionMember<double, BNjetCollection> * allJetByCSVPt;
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> * myMaxLepAbsEta;
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> * myMinDeltaRLepLepAFOS;
  TwoObjectKinematic<BNleptonCollection,BNjetCollection> * mySumPt;
  TwoObjectKinematic<BNleptonCollection,BNjetCollection> * mySumPtCentral;

  FinalBDT_3l(ThreeObjectKinematic<BNjetCollection,BNjetCollection,BNjetCollection> * input_myTopLikeTrijetMass,
              GenericCollectionSizeVariable<BNjetCollection> * input_numJets,
              GenericCollectionMember<double, BNjetCollection> * input_allJetByCSVPt,
              TwoObjectKinematic<BNleptonCollection,BNleptonCollection> * input_myMaxLepAbsEta,
              TwoObjectKinematic<BNleptonCollection,BNleptonCollection> * input_myMinDeltaRLepLepAFOS,
              TwoObjectKinematic<BNleptonCollection,BNjetCollection> * input_mySumPt,
              TwoObjectKinematic<BNleptonCollection,BNjetCollection> * input_mySumPtCentral);

  void evaluate();

};

FinalBDT_3l::FinalBDT_3l(ThreeObjectKinematic<BNjetCollection,BNjetCollection,BNjetCollection> * input_myTopLikeTrijetMass,
                         GenericCollectionSizeVariable<BNjetCollection> * input_numJets,
                         GenericCollectionMember<double, BNjetCollection> * input_allJetByCSVPt,
                         TwoObjectKinematic<BNleptonCollection,BNleptonCollection> * input_myMaxLepAbsEta,
                         TwoObjectKinematic<BNleptonCollection,BNleptonCollection> * input_myMinDeltaRLepLepAFOS,
                         TwoObjectKinematic<BNleptonCollection,BNjetCollection> * input_mySumPt,
                         TwoObjectKinematic<BNleptonCollection,BNjetCollection> * input_mySumPtCentral):
  myTopLikeTrijetMass(input_myTopLikeTrijetMass), numJets(input_numJets), allJetByCSVPt(input_allJetByCSVPt), myMaxLepAbsEta(input_myMaxLepAbsEta),
  myMinDeltaRLepLepAFOS(input_myMinDeltaRLepLepAFOS), mySumPt(input_mySumPt), mySumPtCentral(input_mySumPtCentral) {
  
  branches["FinalBDT_ThreeLepton"] = BranchInfo<double>("FinalBDT_ThreeLepton");

  std::vector< TString >catList;
  catList.push_back("0_finalmva_3l");

  for( unsigned int jj = 0 ; jj < 1 ; ++jj ) { //1 readers for 1 BDTs

    reader.push_back( new TMVA::Reader( "!Color:!Silent" ));
    
    reader[jj]->AddVariable( "bestMTopHad", &varbestMTopHad );
    reader[jj]->AddVariable( "nJet25", &varnJet25 );
    reader[jj]->AddVariable( "Jet1_pt", &varJet1_pt );
    reader[jj]->AddVariable( "max_Lep_eta", &varmax_Lep_eta );
    reader[jj]->AddVariable( "minDrllAFOS", &varminDrllAFOS );
    reader[jj]->AddVariable( "htJet25", &varhtJet25 );
    reader[jj]->AddVariable( "htJet25ratio1224Lep", &varhtJet25ratio1224Lep );

    TString dir = (string(getenv("CMSSW_BASE"))+"/src/ttHMultileptonAnalysis/TemplateMakers/data/CERN/BDT_weights/").c_str();
    TString label = catList[jj];
    TString file_name = "3l_mix_BDTG.weights.xml";
    //TString file_name = "TMVAClassification_BDTG.weights.xml";
    //TString file_name = "TMVAClassification_CFMlpANN.weights.xml";
    TString weight_file_name = dir + label + "/" + file_name;

    reader[jj]->BookMVA( "BDTG method", weight_file_name );
    //reader[jj]->BookMVA( "CFMlpANN method", weight_file_name );

    std::cout << "Loading weight file " << weight_file_name << std::endl;
  }

}

void FinalBDT_3l::evaluate() {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;
  
  //--------
  
  myTopLikeTrijetMass->evaluate();
  numJets->evaluate();
  allJetByCSVPt->evaluate();
  myMaxLepAbsEta->evaluate();
  myMinDeltaRLepLepAFOS->evaluate();
  mySumPt->evaluate();
  mySumPtCentral->evaluate();
  
  varbestMTopHad = abs((*myTopLikeTrijetMass).myVars[0].branchVal); 
  varnJet25 = (*numJets).branches["numJets"].branchVal * 1.0; 
  varJet1_pt = (*allJetByCSVPt).myVars[0].branchVal; //First jet pT
  varmax_Lep_eta = (*myMaxLepAbsEta).myVars[0].branchVal;
  varminDrllAFOS = (*myMinDeltaRLepLepAFOS).myVars[0].branchVal;
  varhtJet25 = (*mySumPt).myVars[0].branchVal;
  varhtJet25ratio1224Lep = (*mySumPtCentral).myVars[0].branchVal / (*mySumPt).myVars[0].branchVal;

  for( unsigned int jj = 0 ; jj < 1 ; ++jj ) {
    
    TMVA::Reader  *tmpReader = reader[jj];
    TString mvaName = "BDTG";
    //TString mvaName = "CFMlpANN";

    //TString bName = mvaName + TString("_") + catList[jj];
    TString bName = "";
    if (jj==0) bName = "FinalBDT_ThreeLepton";
    
    TString methodName = mvaName + TString(" method");
    Float_t annOut  = tmpReader->EvaluateMVA( methodName );
    
    branches[bName].branchVal = annOut;
  }
  
}
  

#endif 
