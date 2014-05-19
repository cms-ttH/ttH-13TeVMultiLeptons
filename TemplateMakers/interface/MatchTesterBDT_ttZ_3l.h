#ifndef _MatchTesterBDT_ttZ_3l_h
#define _MatchTesterBDT_ttZ_3l_h

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

#include "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BranchInfo.h"
//#include <typeinfo>

class MatchTesterBDT_ttZ_3l: public KinematicVariable<double> {

public:

  //Store branch values so they are accessible to other classes
  vector<BranchInfo<double>> myVars;

  BNleptonCollection **leptons;
  BNjetCollection **jets;
  BNmetCollection **mets;

  double MatchBDT_ttZ_3l_Bb;
  double MatchBDT_ttZ_3l_Bq;
  double MatchBDT_ttZ_3l_bq;
  double MatchBDT_ttZ_3l_Bbq;
  double MatchBDT_ttZ_3l_Bqq;
  double MatchBDT_ttZ_3l_bqq;
  double MatchBDT_ttZ_3l_Bbqq;

  Float_t varnumJets;
  Float_t varlepTop_jet_CSV;
  Float_t varlepTop_jet_charge;
  Float_t vartop_mass_lep_B;
  Float_t vartop_MT_met_lep_B;
  Float_t varhadTop_jet_CSV;
  Float_t varhadTop_jet_charge;
  Float_t varW_jet_1_CSV;
  Float_t vartop_mass_b_q;
  Float_t varW_jet_2_CSV;
  Float_t varW_sum_charge_qq;
  Float_t varW_mass_qq;
  Float_t vartop_mass_b_qq;
  Float_t varttbar_MT_mass_ratio_B_b_qq;

  vector<TMVA::Reader *> reader;


  MatchTesterBDT_ttZ_3l(BNleptonCollection **_leptons, BNjetCollection **_jets, BNmetCollection **_mets);
  ~MatchTesterBDT_ttZ_3l();
  void evaluate();
};

MatchTesterBDT_ttZ_3l::MatchTesterBDT_ttZ_3l(BNleptonCollection **_leptons, BNjetCollection **_jets, BNmetCollection **_mets):
  leptons(_leptons), jets(_jets), mets(_mets) {

  //std::cout << "Initializing MatchTesterBDT_ttZ_3l" << std::endl;

  //this->resetVal = 0.0; //What does this do?
  this->resetVal = KinematicVariableConstants::FLOAT_INIT; //What does this do?

  branches["MatchBDT_ttZ_3l_Bb"] = BranchInfo<double>("MatchBDT_ttZ_3l_Bb");
  branches["MatchBDT_ttZ_3l_Bq"] = BranchInfo<double>("MatchBDT_ttZ_3l_Bq");
  branches["MatchBDT_ttZ_3l_bq"] = BranchInfo<double>("MatchBDT_ttZ_3l_bq");
  branches["MatchBDT_ttZ_3l_Bbq"] = BranchInfo<double>("MatchBDT_ttZ_3l_Bbq");
  branches["MatchBDT_ttZ_3l_Bqq"] = BranchInfo<double>("MatchBDT_ttZ_3l_Bqq");
  branches["MatchBDT_ttZ_3l_bqq"] = BranchInfo<double>("MatchBDT_ttZ_3l_bqq");
  branches["MatchBDT_ttZ_3l_Bbqq"] = BranchInfo<double>("MatchBDT_ttZ_3l_Bbqq");

  branches["Full_matchBDT_ttZ_3l_Bb"] = BranchInfo<double>("Full_matchBDT_ttZ_3l_Bb");
  branches["Full_matchBDT_ttZ_3l_Bq"] = BranchInfo<double>("Full_matchBDT_ttZ_3l_Bq");
  branches["Full_matchBDT_ttZ_3l_bq"] = BranchInfo<double>("Full_matchBDT_ttZ_3l_bq");
  branches["Full_matchBDT_ttZ_3l_Bbq"] = BranchInfo<double>("Full_matchBDT_ttZ_3l_Bbq");
  branches["Full_matchBDT_ttZ_3l_Bqq"] = BranchInfo<double>("Full_matchBDT_ttZ_3l_Bqq");
  branches["Full_matchBDT_ttZ_3l_bqq"] = BranchInfo<double>("Full_matchBDT_ttZ_3l_bqq");
  branches["Full_matchBDT_ttZ_3l_Bbqq"] = BranchInfo<double>("Full_matchBDT_ttZ_3l_Bbqq");

  branches["BDT_ttZ_3l_B_CSV"] = BranchInfo<double>("BDT_ttZ_3l_B_CSV");
  branches["BDT_ttZ_3l_b_CSV"] = BranchInfo<double>("BDT_ttZ_3l_b_CSV");
  branches["BDT_ttZ_3l_q_1_CSV"] = BranchInfo<double>("BDT_ttZ_3l_q_1_CSV");
  branches["BDT_ttZ_3l_q_2_CSV"] = BranchInfo<double>("BDT_ttZ_3l_q_2_CSV");
  branches["BDT_ttZ_3l_B_charge"] = BranchInfo<double>("BDT_ttZ_3l_B_charge");
  branches["BDT_ttZ_3l_b_charge"] = BranchInfo<double>("BDT_ttZ_3l_b_charge");
  branches["BDT_ttZ_3l_W_mass_qq"] = BranchInfo<double>("BDT_ttZ_3l_W_mass_qq");
  branches["BDT_ttZ_3l_W_sum_charge_qq"] = BranchInfo<double>("BDT_ttZ_3l_W_sum_charge_qq");
  branches["BDT_ttZ_3l_top_mass_lep_B"] = BranchInfo<double>("BDT_ttZ_3l_top_mass_lep_B");
  branches["BDT_ttZ_3l_top_mass_b_q"] = BranchInfo<double>("BDT_ttZ_3l_top_mass_b_q");
  branches["BDT_ttZ_3l_top_mass_b_qq"] = BranchInfo<double>("BDT_ttZ_3l_top_mass_b_qq");
  branches["BDT_ttZ_3l_ttbar_MT_mass_ratio_B_b_qq"] = BranchInfo<double>("BDT_ttZ_3l_ttbar_MT_mass_ratio_B_b_qq");

  branches["MatchBDT_ttZ_3l_Bb"].branchVal = KinematicVariableConstants::FLOAT_INIT; 
  branches["MatchBDT_ttZ_3l_Bq"].branchVal = KinematicVariableConstants::FLOAT_INIT; 
  branches["MatchBDT_ttZ_3l_bq"].branchVal = KinematicVariableConstants::FLOAT_INIT; 
  branches["MatchBDT_ttZ_3l_Bbq"].branchVal = KinematicVariableConstants::FLOAT_INIT; 
  branches["MatchBDT_ttZ_3l_Bqq"].branchVal = KinematicVariableConstants::FLOAT_INIT; 
  branches["MatchBDT_ttZ_3l_bqq"].branchVal = KinematicVariableConstants::FLOAT_INIT; 
  branches["MatchBDT_ttZ_3l_Bbqq"].branchVal = KinematicVariableConstants::FLOAT_INIT; 

  branches["Full_matchBDT_ttZ_3l_Bb"].branchVal = 0.0; 
  branches["Full_matchBDT_ttZ_3l_Bq"].branchVal = 0.0; 
  branches["Full_matchBDT_ttZ_3l_bq"].branchVal = 0.0; 
  branches["Full_matchBDT_ttZ_3l_Bbq"].branchVal = 0.0; 
  branches["Full_matchBDT_ttZ_3l_Bqq"].branchVal = 0.0; 
  branches["Full_matchBDT_ttZ_3l_bqq"].branchVal = 0.0; 
  branches["Full_matchBDT_ttZ_3l_Bbqq"].branchVal = 0.0; 

  branches["BDT_ttZ_3l_B_CSV"].branchVal = KinematicVariableConstants::FLOAT_INIT; 
  branches["BDT_ttZ_3l_b_CSV"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["BDT_ttZ_3l_q_1_CSV"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["BDT_ttZ_3l_q_2_CSV"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["BDT_ttZ_3l_B_charge"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["BDT_ttZ_3l_b_charge"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["BDT_ttZ_3l_W_mass_qq"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["BDT_ttZ_3l_W_sum_charge_qq"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["BDT_ttZ_3l_top_mass_lep_B"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["BDT_ttZ_3l_top_mass_b_q"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["BDT_ttZ_3l_top_mass_b_qq"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["BDT_ttZ_3l_ttbar_MT_mass_ratio_B_b_qq"].branchVal = KinematicVariableConstants::FLOAT_INIT;

  std::vector< TString >catList;
  catList.push_back("Bb"); //0
  catList.push_back("Bq"); //1
  catList.push_back("bq"); //2
  catList.push_back("Bbq"); //3
  catList.push_back("Bqq"); //4
  catList.push_back("bqq"); //5
  catList.push_back("Bbqq"); //6

  //std::cout << "About to book readers" << std::endl;

  for( unsigned int jj = 0; jj < 7; ++jj ) {

    //std::cout << "Booking reader " << jj << std::endl;

    reader.push_back( new TMVA::Reader( "!Color:!Silent" ));

    //std::cout << "Pushed back reader" << std::endl;

    reader[jj]->AddVariable("numJets", &varnumJets );
    //std::cout << "Here" << std::endl;
    if (jj == 0 || jj == 1 || jj == 3 || jj == 4 || jj == 6) {
      reader[jj]->AddVariable("lepTop_jet_CSV", &varlepTop_jet_CSV );
      reader[jj]->AddVariable("lepTop_jet_charge", &varlepTop_jet_charge );
      reader[jj]->AddVariable("top_mass_lep_B", &vartop_mass_lep_B );
      reader[jj]->AddVariable("top_MT_met_lep_B", &vartop_MT_met_lep_B ); }
    //std::cout << "Here" << std::endl;
    if (jj == 0 || jj == 2 || jj == 3 || jj == 5 || jj == 6) {
    reader[jj]->AddVariable("hadTop_jet_CSV", &varhadTop_jet_CSV );
    reader[jj]->AddVariable("hadTop_jet_charge", &varhadTop_jet_charge ); }
    //std::cout << "Here" << std::endl;
    if (jj > 0) {
      reader[jj]->AddVariable("W_jet_1_CSV", &varW_jet_1_CSV ); }
    //std::cout << "Here" << std::endl;
    if (jj == 2 || jj == 3) {
      reader[jj]->AddVariable("top_mass_b_q", &vartop_mass_b_q ); }
    //std::cout << "Here" << std::endl;
    if (jj > 3) {
      reader[jj]->AddVariable("W_jet_2_CSV", &varW_jet_2_CSV );
      reader[jj]->AddVariable("W_sum_charge_qq", &varW_sum_charge_qq );
      reader[jj]->AddVariable("W_mass_qq", &varW_mass_qq ); }
    //std::cout << "Here" << std::endl;
    if (jj > 4) {
      reader[jj]->AddVariable("top_mass_b_qq", &vartop_mass_b_qq ); }
    //std::cout << "Here" << std::endl;
    if (jj == 6) {
      reader[jj]->AddVariable("ttbar_MT_mass_ratio_B_b_qq", &varttbar_MT_mass_ratio_B_b_qq ); }

    //std::cout << "Here" << std::endl;
    TString dir = (string(getenv("CMSSW_BASE"))+"/src/ttHMultileptonAnalysis/TemplateMakers/data/NOVa/matchbox/ttbarZ_3l_BDT/").c_str();
    //std::cout << "Here" << std::endl;
    TString label = catList[jj];
    //std::cout << "Here" << std::endl;
    TString file_name = "TMVAClassification_BDTG.weights.xml";
    //TString file_name = "TMVAClassification_CFMlpANN.weights.xml";
    //std::cout << "Here" << std::endl;
    TString weight_file_name = dir + "/" + label + "/" + file_name;

    //std::cout << "Here" << std::endl;
    reader[jj]->BookMVA( "BDTG method", weight_file_name );
    //reader[jj]->BookMVA( "CFMlpANN method", weight_file_name );

    //std::cout << "Loading weight file " << weight_file_name << std::endl;

  }

}

void MatchTesterBDT_ttZ_3l::evaluate() {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;
  
  ////std::cout << "Evaluating MatchTesterBDT_ttZ_3l" << std::endl;
  
  if ( (*leptons)->size() != 1) return;
  if ( (*jets)->size() < 2) return;

  ////std::cout << "There's at least one lepton" << std::endl;
  
  TLorentzVector lep_vect;
  TLorentzVector met_vect;
  TLorentzVector jet1_vect;
  TLorentzVector jet2_vect;
  TLorentzVector jet3_vect;
  TLorentzVector jet4_vect;

  TLorentzVector lep_vect_trans;
  TLorentzVector jet1_vect_trans;
  TLorentzVector jet2_vect_trans;
  TLorentzVector jet3_vect_trans;
  TLorentzVector jet4_vect_trans;

  lep_vect.SetPtEtaPhiE((*leptons)->at(0)->pt, (*leptons)->at(0)->eta, (*leptons)->at(0)->phi, (*leptons)->at(0)->energy);
  lep_vect_trans.SetPtEtaPhiE((*leptons)->at(0)->pt, 0.0, (*leptons)->at(0)->phi, (*leptons)->at(0)->pt);
  met_vect.SetPtEtaPhiE((*mets)->at(0).pt, 0.0, (*mets)->at(0).phi, (*mets)->at(0).pt);

  TLorentzVector lep_B_vect;
  TLorentzVector met_lep_B_vect_trans;
  TLorentzVector b_q_vect;
  TLorentzVector qq_vect;
  TLorentzVector b_qq_vect;
  TLorentzVector B_b_qq_vect;
  TLorentzVector B_b_qq_vect_trans;

  double BDT_Bb = -2.0;
  double BDT_Bq = -2.0;
  double BDT_bq = -2.0;
  double BDT_Bbq = -2.0;
  double BDT_Bqq = -2.0;
  double BDT_bqq = -2.0;
  double BDT_Bbqq = -2.0;

  int lep_charge = std::max((*leptons)->at(0)->tkCharge, -1);

  TMVA::Reader *tmpReader;
      
  //B is the b from a leptonic top
  //b is the b from the hardonic top
  //q is a jet from the W
  
  ////std::cout << "About to enter jet loop" << std::endl;
  
  for (unsigned int iJet1 = 0; iJet1 < (*jets)->size(); iJet1++) {    
    ////std::cout << "iJet1 = " << iJet1 << std::endl;    
    jet1_vect.SetPtEtaPhiE((*jets)->at(iJet1).pt, (*jets)->at(iJet1).eta, (*jets)->at(iJet1).phi, (*jets)->at(iJet1).energy);
    jet1_vect_trans.SetPtEtaPhiE((*jets)->at(iJet1).pt, 0.0, (*jets)->at(iJet1).phi, (*jets)->at(iJet1).pt);

    for (unsigned int iJet2 = 0; iJet2 < (*jets)->size(); iJet2++) {
      if (iJet2 == iJet1) continue;
      ////std::cout << "iJet2 = " << iJet1 << std::endl;      
      jet2_vect.SetPtEtaPhiE((*jets)->at(iJet2).pt, (*jets)->at(iJet2).eta, (*jets)->at(iJet2).phi, (*jets)->at(iJet2).energy);
      jet2_vect_trans.SetPtEtaPhiE((*jets)->at(iJet2).pt, 0, (*jets)->at(iJet2).phi, (*jets)->at(iJet2).pt);

      //BDT_Bb
      lep_B_vect = lep_vect+jet1_vect;
      met_lep_B_vect_trans = met_vect+lep_vect_trans+jet1_vect_trans;

      varnumJets = (*jets)->size();
      varlepTop_jet_CSV = (*jets)->at(iJet1).btagCombinedSecVertex;
      varlepTop_jet_charge = lep_charge*(*jets)->at(iJet1).charge;
      vartop_mass_lep_B = lep_B_vect.M();
      vartop_MT_met_lep_B = met_lep_B_vect_trans.M();
      varhadTop_jet_CSV = (*jets)->at(iJet2).btagCombinedSecVertex;
      varhadTop_jet_charge = lep_charge*(*jets)->at(iJet2).charge;

      //std::cout << "Making tmpReader = reader[0]" << std::endl;
      tmpReader = reader[0];
      BDT_Bb = tmpReader->EvaluateMVA( "BDTG method" );
      //std::cout << "Evaluated BDT" << std::endl;

      if (BDT_Bb > branches["MatchBDT_ttZ_3l_Bb"].branchVal) {
        branches["MatchBDT_ttZ_3l_Bb"].branchVal = BDT_Bb;
        branches["Full_matchBDT_ttZ_3l_Bb"].branchVal = ((*jets)->at(iJet1).genPartonMotherId == 6*lep_charge &&
                                                      (*jets)->at(iJet2).genPartonMotherId == -6*lep_charge);
        branches["BDT_ttZ_3l_B_CSV"].branchVal = (*jets)->at(iJet1).btagCombinedSecVertex;
        branches["BDT_ttZ_3l_b_CSV"].branchVal = (*jets)->at(iJet2).btagCombinedSecVertex;
        branches["BDT_ttZ_3l_B_charge"].branchVal = lep_charge*(*jets)->at(iJet1).charge;
        branches["BDT_ttZ_3l_b_charge"].branchVal = lep_charge*(*jets)->at(iJet2).charge;
        branches["BDT_ttZ_3l_top_mass_lep_B"].branchVal = vartop_mass_lep_B;
      }
      
      //BDT_Bq
      lep_B_vect = lep_vect+jet1_vect;
      met_lep_B_vect_trans = met_vect+lep_vect_trans+jet1_vect_trans;

      varnumJets = (*jets)->size();
      varlepTop_jet_CSV = (*jets)->at(iJet1).btagCombinedSecVertex;
      varlepTop_jet_charge = lep_charge*(*jets)->at(iJet1).charge;
      vartop_mass_lep_B = lep_B_vect.M();
      vartop_MT_met_lep_B = met_lep_B_vect_trans.M();
      varW_jet_1_CSV = (*jets)->at(iJet2).btagCombinedSecVertex;

      //std::cout << "Making tmpReader = reader[1]" << std::endl;
      tmpReader = reader[1];
      BDT_Bq = tmpReader->EvaluateMVA( "BDTG method" );
      //std::cout << "Evaluated BDT" << std::endl;
      
      if (BDT_Bq > branches["MatchBDT_ttZ_3l_Bq"].branchVal) {
        branches["MatchBDT_ttZ_3l_Bq"].branchVal = BDT_Bq;
        branches["Full_matchBDT_ttZ_3l_Bq"].branchVal = ((*jets)->at(iJet1).genPartonMotherId == 6*lep_charge &&
                                                      abs((*jets)->at(iJet2).genPartonMotherId) == 24);
        branches["BDT_ttZ_3l_B_CSV"].branchVal = (*jets)->at(iJet1).btagCombinedSecVertex;
        branches["BDT_ttZ_3l_q_1_CSV"].branchVal = (*jets)->at(iJet2).btagCombinedSecVertex;
        branches["BDT_ttZ_3l_B_charge"].branchVal = lep_charge*(*jets)->at(iJet1).charge;
        branches["BDT_ttZ_3l_top_mass_lep_B"].branchVal = vartop_mass_lep_B;
      }
      
      //BDT_bq
      b_q_vect = jet1_vect+jet2_vect;
      
      varnumJets = (*jets)->size();
      varhadTop_jet_CSV = (*jets)->at(iJet1).btagCombinedSecVertex;
      varhadTop_jet_charge = lep_charge*(*jets)->at(iJet1).charge;
      varW_jet_1_CSV = (*jets)->at(iJet2).btagCombinedSecVertex;
      vartop_mass_b_q = b_q_vect.M();

      //std::cout << "Making tmpReader = reader[2]" << std::endl;
      tmpReader = reader[2];
      BDT_bq = tmpReader->EvaluateMVA( "BDTG method" );
      //std::cout << "Evaluated BDT" << std::endl;

      if (BDT_bq > branches["MatchBDT_ttZ_3l_bq"].branchVal) {
        branches["MatchBDT_ttZ_3l_bq"].branchVal = BDT_bq;
        branches["Full_matchBDT_ttZ_3l_bq"].branchVal = ((*jets)->at(iJet1).genPartonMotherId == -6*lep_charge &&
                                                      abs((*jets)->at(iJet2).genPartonMotherId) == 24);
        branches["BDT_ttZ_3l_b_CSV"].branchVal = (*jets)->at(iJet1).btagCombinedSecVertex;
        branches["BDT_ttZ_3l_q_1_CSV"].branchVal = (*jets)->at(iJet2).btagCombinedSecVertex;
        branches["BDT_ttZ_3l_b_charge"].branchVal = lep_charge*(*jets)->at(iJet1).charge;
        branches["BDT_ttZ_3l_top_mass_b_q"].branchVal = vartop_mass_b_q;
      }
      
      for (unsigned int iJet3 = 0; iJet3 < (*jets)->size(); iJet3++) {
        if (iJet3 == iJet1 || iJet3 == iJet1) continue;
        ////std::cout << "iJet3 = " << iJet1 << std::endl;
        jet3_vect.SetPtEtaPhiE((*jets)->at(iJet3).pt, (*jets)->at(iJet3).eta, (*jets)->at(iJet3).phi, (*jets)->at(iJet3).energy);
        jet3_vect_trans.SetPtEtaPhiE((*jets)->at(iJet3).pt, 0, (*jets)->at(iJet3).phi, (*jets)->at(iJet3).pt);

        //BDT_Bbq
        b_q_vect = jet2_vect+jet3_vect;

        varnumJets = (*jets)->size();
        varlepTop_jet_CSV = (*jets)->at(iJet1).btagCombinedSecVertex;
        varlepTop_jet_charge = lep_charge*(*jets)->at(iJet1).charge;
        vartop_mass_lep_B = lep_B_vect.M();
        vartop_MT_met_lep_B = met_lep_B_vect_trans.M();
        varhadTop_jet_CSV = (*jets)->at(iJet2).btagCombinedSecVertex;
        varhadTop_jet_charge = lep_charge*(*jets)->at(iJet2).charge;
        varW_jet_1_CSV = (*jets)->at(iJet3).btagCombinedSecVertex;
        vartop_mass_b_q = b_q_vect.M();

        //std::cout << "Making tmpReader = reader[3]" << std::endl;
        tmpReader = reader[3];
        BDT_Bbq = tmpReader->EvaluateMVA( "BDTG method" );
        //std::cout << "Evaluated BDT" << std::endl;

        if (BDT_Bbq > branches["MatchBDT_ttZ_3l_Bbq"].branchVal) {
          branches["MatchBDT_ttZ_3l_Bbq"].branchVal = BDT_Bbq;
          branches["Full_matchBDT_ttZ_3l_Bbq"].branchVal = ((*jets)->at(iJet1).genPartonMotherId == 6*lep_charge &&
                                                         (*jets)->at(iJet2).genPartonMotherId == -6*lep_charge &&
                                                         abs((*jets)->at(iJet3).genPartonMotherId) == 24);
          branches["BDT_ttZ_3l_B_CSV"].branchVal = (*jets)->at(iJet1).btagCombinedSecVertex;
          branches["BDT_ttZ_3l_b_CSV"].branchVal = (*jets)->at(iJet2).btagCombinedSecVertex;
          branches["BDT_ttZ_3l_q_1_CSV"].branchVal = (*jets)->at(iJet3).btagCombinedSecVertex;
          branches["BDT_ttZ_3l_B_charge"].branchVal = lep_charge*(*jets)->at(iJet1).charge;
          branches["BDT_ttZ_3l_b_charge"].branchVal = lep_charge*(*jets)->at(iJet2).charge;
          branches["BDT_ttZ_3l_top_mass_lep_B"].branchVal = vartop_mass_lep_B;
          branches["BDT_ttZ_3l_top_mass_b_q"].branchVal = vartop_mass_b_q;
        }

        //BDT_Bqq
        qq_vect = jet2_vect+jet3_vect;

        varnumJets = (*jets)->size();
        varlepTop_jet_CSV = (*jets)->at(iJet1).btagCombinedSecVertex;
        varlepTop_jet_charge = lep_charge*(*jets)->at(iJet1).charge;
        vartop_mass_lep_B = lep_B_vect.M();
        vartop_MT_met_lep_B = met_lep_B_vect_trans.M();
        varW_jet_1_CSV = (*jets)->at(iJet2).btagCombinedSecVertex;
        varW_jet_2_CSV = (*jets)->at(iJet3).btagCombinedSecVertex;
        varW_sum_charge_qq = lep_charge*((*jets)->at(iJet2).charge + (*jets)->at(iJet3).charge);
        varW_mass_qq = qq_vect.M();

        //std::cout << "Making tmpReader = reader[4]" << std::endl;
        tmpReader = reader[4];
        BDT_Bqq = tmpReader->EvaluateMVA( "BDTG method" );
        //std::cout << "Evaluated BDT" << std::endl;
      
        if (BDT_Bqq > branches["MatchBDT_ttZ_3l_Bqq"].branchVal) {
          branches["MatchBDT_ttZ_3l_Bqq"].branchVal = BDT_Bqq;
          branches["Full_matchBDT_ttZ_3l_Bqq"].branchVal = ((*jets)->at(iJet1).genPartonMotherId == 6*lep_charge &&
                                                         abs((*jets)->at(iJet2).genPartonMotherId) == 24 &&
                                                         abs((*jets)->at(iJet3).genPartonMotherId) == 24);
          branches["BDT_ttZ_3l_B_CSV"].branchVal = (*jets)->at(iJet1).btagCombinedSecVertex;
          branches["BDT_ttZ_3l_q_1_CSV"].branchVal = (*jets)->at(iJet2).btagCombinedSecVertex;
          branches["BDT_ttZ_3l_q_2_CSV"].branchVal = (*jets)->at(iJet3).btagCombinedSecVertex;
          branches["BDT_ttZ_3l_B_charge"].branchVal = lep_charge*(*jets)->at(iJet1).charge;
          branches["BDT_ttZ_3l_top_mass_lep_B"].branchVal = vartop_mass_lep_B;
          branches["BDT_ttZ_3l_W_mass_qq"].branchVal = varW_mass_qq;
          branches["BDT_ttZ_3l_W_sum_charge_qq"].branchVal = varW_sum_charge_qq;
        }

        //BDT_bqq
        qq_vect = jet2_vect+jet3_vect;
        b_q_vect = jet1_vect+jet2_vect;
        b_qq_vect = jet1_vect+jet2_vect+jet3_vect;

        varnumJets = (*jets)->size();
        varhadTop_jet_CSV = (*jets)->at(iJet1).btagCombinedSecVertex;
        varhadTop_jet_charge = lep_charge*(*jets)->at(iJet1).charge;
        varW_jet_1_CSV = (*jets)->at(iJet2).btagCombinedSecVertex;
        varW_jet_2_CSV = (*jets)->at(iJet3).btagCombinedSecVertex;
        varW_sum_charge_qq = lep_charge*((*jets)->at(iJet2).charge + (*jets)->at(iJet3).charge);
        varW_mass_qq = qq_vect.M();
        vartop_mass_b_qq = b_qq_vect.M();        
        
        //std::cout << "Making tmpReader = reader[5]" << std::endl;
        tmpReader = reader[5];
        BDT_bqq = tmpReader->EvaluateMVA( "BDTG method" );
        //std::cout << "Evaluated BDT" << std::endl;

        if (BDT_bqq > branches["MatchBDT_ttZ_3l_bqq"].branchVal) {
          branches["MatchBDT_ttZ_3l_bqq"].branchVal = BDT_bqq;
          branches["Full_matchBDT_ttZ_3l_bqq"].branchVal = ((*jets)->at(iJet1).genPartonMotherId == -6*lep_charge &&
                                                   abs((*jets)->at(iJet2).genPartonMotherId) == 24 &&
                                                   abs((*jets)->at(iJet3).genPartonMotherId) == 24);
          branches["BDT_ttZ_3l_b_CSV"].branchVal = (*jets)->at(iJet1).btagCombinedSecVertex;
          branches["BDT_ttZ_3l_q_1_CSV"].branchVal = (*jets)->at(iJet2).btagCombinedSecVertex;
          branches["BDT_ttZ_3l_q_2_CSV"].branchVal = (*jets)->at(iJet3).btagCombinedSecVertex;
          branches["BDT_ttZ_3l_b_charge"].branchVal = lep_charge*(*jets)->at(iJet1).charge;
          branches["BDT_ttZ_3l_W_mass_qq"].branchVal = varW_mass_qq;
          branches["BDT_ttZ_3l_W_sum_charge_qq"].branchVal = varW_sum_charge_qq;
          branches["BDT_ttZ_3l_top_mass_b_qq"].branchVal = vartop_mass_b_qq;
        }

        
        for (unsigned int iJet4 = 0; iJet4 < (*jets)->size(); iJet4++) { 
          if (iJet4 == iJet1 || iJet4 == iJet2 || iJet4 == iJet3) continue;
          ////std::cout << "iJet4 = " << iJet1 << std::endl;
          jet4_vect.SetPtEtaPhiE((*jets)->at(iJet4).pt, (*jets)->at(iJet4).eta, (*jets)->at(iJet4).phi, (*jets)->at(iJet4).energy);
          jet4_vect_trans.SetPtEtaPhiE((*jets)->at(iJet4).pt, 0, (*jets)->at(iJet4).phi, (*jets)->at(iJet4).pt);

          //BDT_Bbqq
          qq_vect = jet3_vect+jet4_vect;
          b_q_vect = jet2_vect+jet3_vect;
          b_qq_vect = jet2_vect+jet3_vect+jet4_vect;
          B_b_qq_vect = jet1_vect+jet2_vect+jet3_vect+jet4_vect;
          B_b_qq_vect_trans = jet1_vect_trans+jet2_vect_trans+jet3_vect_trans+jet4_vect_trans;
          
          varnumJets = (*jets)->size();
          varlepTop_jet_CSV = (*jets)->at(iJet1).btagCombinedSecVertex;
          varlepTop_jet_charge = lep_charge*(*jets)->at(iJet1).charge;
          vartop_mass_lep_B = lep_B_vect.M();
          vartop_MT_met_lep_B = met_lep_B_vect_trans.M();
          varhadTop_jet_CSV = (*jets)->at(iJet2).btagCombinedSecVertex;
          varhadTop_jet_charge = lep_charge*(*jets)->at(iJet2).charge;
          varW_jet_1_CSV = (*jets)->at(iJet3).btagCombinedSecVertex;
          varW_jet_2_CSV = (*jets)->at(iJet4).btagCombinedSecVertex;
          varW_sum_charge_qq = lep_charge*((*jets)->at(iJet3).charge + (*jets)->at(iJet4).charge);
          varW_mass_qq = qq_vect.M();
          vartop_mass_b_qq = b_qq_vect.M();
          varttbar_MT_mass_ratio_B_b_qq = B_b_qq_vect_trans.M()/B_b_qq_vect.M();

          //std::cout << "Making tmpReader = reader[6]" << std::endl;
          tmpReader = reader[6];
          BDT_Bbqq = tmpReader->EvaluateMVA( "BDTG method" );
          //std::cout << "Evaluated BDT" << std::endl;

          if (BDT_Bbqq > branches["MatchBDT_ttZ_3l_Bbqq"].branchVal) {
            branches["MatchBDT_ttZ_3l_Bbqq"].branchVal = BDT_Bbqq;
            branches["Full_matchBDT_ttZ_3l_Bbqq"].branchVal = ((*jets)->at(iJet1).genPartonMotherId == 6*lep_charge &&
                                                            (*jets)->at(iJet2).genPartonMotherId == -6*lep_charge &&
                                                            abs((*jets)->at(iJet3).genPartonMotherId) == 24 &&
                                                            abs((*jets)->at(iJet4).genPartonMotherId) == 24);
            branches["BDT_ttZ_3l_B_CSV"].branchVal = (*jets)->at(iJet1).btagCombinedSecVertex;
            branches["BDT_ttZ_3l_b_CSV"].branchVal = (*jets)->at(iJet2).btagCombinedSecVertex;
            branches["BDT_ttZ_3l_q_1_CSV"].branchVal = (*jets)->at(iJet3).btagCombinedSecVertex;
            branches["BDT_ttZ_3l_q_2_CSV"].branchVal = (*jets)->at(iJet4).btagCombinedSecVertex;
            branches["BDT_ttZ_3l_B_charge"].branchVal = lep_charge*(*jets)->at(iJet1).charge;
            branches["BDT_ttZ_3l_b_charge"].branchVal = lep_charge*(*jets)->at(iJet2).charge;
            branches["BDT_ttZ_3l_top_mass_lep_B"].branchVal = vartop_mass_lep_B;
            branches["BDT_ttZ_3l_W_mass_qq"].branchVal = varW_mass_qq;
            branches["BDT_ttZ_3l_W_sum_charge_qq"].branchVal = varW_sum_charge_qq;
            branches["BDT_ttZ_3l_top_mass_b_qq"].branchVal = vartop_mass_b_qq;
            branches["BDT_ttZ_3l_ttbar_MT_mass_ratio_B_b_qq"].branchVal = varttbar_MT_mass_ratio_B_b_qq;
          }
        } //end iJet4
      } //end iJet3
    } //end iJet2
  } //end iJet1

  //std::cout << "Finished jet loop" << std::endl;
  
  myVars.clear();
  
  for (typename map<TString, BranchInfo<double>>::iterator iBranch = branches.begin();
       iBranch != branches.end(); iBranch++) {
    myVars.push_back(iBranch->second);
  }

}

MatchTesterBDT_ttZ_3l::~MatchTesterBDT_ttZ_3l() {

  //Delete histograms BEFORE closing file
  
  //delete reader;

}


#endif
