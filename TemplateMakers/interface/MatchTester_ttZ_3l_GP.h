#ifndef _MatchTester_ttZ_3l_GP_h
#define _MatchTester_ttZ_3l_GP_h

#include "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BranchInfo.h"
//#include <typeinfo>

class MatchTester_ttZ_3l_GP: public KinematicVariable<double> {

public:

  //Store branch values so they are accessible to other classes
  vector<BranchInfo<double>> myVars;

  BNleptonCollection **leptons;
  BNjetCollection **jets;
  BNmetCollection **mets;

  TFile * weight_file;
  TH1 * ratio_top_jet_CSV_le3j;
  TH1 * ratio_top_jet_CSV_eq4j;
  TH1 * ratio_top_jet_CSV_eq5j;
  TH1 * ratio_top_jet_CSV_ge6j;
  TH1 * ratio_W_jet_1_CSV_le3j;
  TH1 * ratio_W_jet_1_CSV_eq4j;
  TH1 * ratio_W_jet_1_CSV_eq5j;
  TH1 * ratio_W_jet_1_CSV_ge6j;
  TH1 * ratio_W_jet_2_CSV_le3j;
  TH1 * ratio_W_jet_2_CSV_eq4j;
  TH1 * ratio_W_jet_2_CSV_eq5j;
  TH1 * ratio_W_jet_2_CSV_ge6j;
  TH1 * ratio_lepTop_jet_charge;
  TH1 * ratio_hadTop_jet_charge;
  TH1 * ratio_top_mass_lep_B_le3j;
  TH1 * ratio_top_mass_lep_B_eq4j;
  TH1 * ratio_top_mass_lep_B_eq5j;
  TH1 * ratio_top_mass_lep_B_ge6j;
  TH1 * ratio_top_MT_met_lep_B_le3j;
  TH1 * ratio_top_MT_met_lep_B_eq4j;
  TH1 * ratio_top_MT_met_lep_B_eq5j;
  TH1 * ratio_top_MT_met_lep_B_ge6j;
  TH1 * ratio_W_mass_qq_le3j;
  TH1 * ratio_W_mass_qq_eq4j;
  TH1 * ratio_W_mass_qq_eq5j;
  TH1 * ratio_W_mass_qq_ge6j;
  TH1 * ratio_W_sum_charge_qq;
  TH1 * ratio_top_mass_b_q_le3j;
  TH1 * ratio_top_mass_b_q_eq4j;
  TH1 * ratio_top_mass_b_q_eq5j;
  TH1 * ratio_top_mass_b_q_ge6j;
  TH1 * ratio_top_mass_b_qq_le3j;
  TH1 * ratio_top_mass_b_qq_eq4j;
  TH1 * ratio_top_mass_b_qq_eq5j;
  TH1 * ratio_top_mass_b_qq_ge6j;
  TH1 * ratio_ttbar_2j_MT_mass_ratio_le3j;
  TH1 * ratio_ttbar_2j_MT_mass_ratio_ge4j;
  TH1 * ratio_ttbar_3j_MT_mass_ratio_le3j;
  TH1 * ratio_ttbar_3j_MT_mass_ratio_eq4j;
  TH1 * ratio_ttbar_3j_MT_mass_ratio_ge5j;
  TH1 * ratio_ttbar_4j_MT_mass_ratio_eq4j;
  TH1 * ratio_ttbar_4j_MT_mass_ratio_eq5j;
  TH1 * ratio_ttbar_4j_MT_mass_ratio_ge6j;
  TH1 * corr_top_mass_b_qq_W_mass_qq_le3j;
  TH1 * corr_top_mass_b_qq_W_mass_qq_eq4j;
  TH1 * corr_top_mass_b_qq_W_mass_qq_eq5j;
  TH1 * corr_top_mass_b_qq_W_mass_qq_ge6j;
  TH1 * corr_top_MT_met_lep_B_top_mass_lep_B_le3j;
  TH1 * corr_top_MT_met_lep_B_top_mass_lep_B_eq4j;
  TH1 * corr_top_MT_met_lep_B_top_mass_lep_B_eq5j;
  TH1 * corr_top_MT_met_lep_B_top_mass_lep_B_ge6j;

  MatchTester_ttZ_3l_GP(BNleptonCollection **_leptons, BNjetCollection **_jets, BNmetCollection **_mets);
  ~MatchTester_ttZ_3l_GP();
  void evaluate();
};

MatchTester_ttZ_3l_GP::MatchTester_ttZ_3l_GP(BNleptonCollection **_leptons, BNjetCollection **_jets, BNmetCollection **_mets):
  leptons(_leptons), jets(_jets), mets(_mets) {

  //std::cout << "Initializing MatchTester_ttZ_3l_GP" << std::endl;

  //this->resetVal = 0.0; //What does this do?
  this->resetVal = KinematicVariableConstants::FLOAT_INIT; //What does this do?

  branches["Match_ttZ_3l_GP_Bb"] = BranchInfo<double>("Match_ttZ_3l_GP_Bb");
  branches["Match_ttZ_3l_GP_Bq"] = BranchInfo<double>("Match_ttZ_3l_GP_Bq");
  branches["Match_ttZ_3l_GP_bq"] = BranchInfo<double>("Match_ttZ_3l_GP_bq");
  branches["Match_ttZ_3l_GP_Bbq"] = BranchInfo<double>("Match_ttZ_3l_GP_Bbq");
  branches["Match_ttZ_3l_GP_Bqq"] = BranchInfo<double>("Match_ttZ_3l_GP_Bqq");
  branches["Match_ttZ_3l_GP_bqq"] = BranchInfo<double>("Match_ttZ_3l_GP_bqq");
  branches["Match_ttZ_3l_GP_Bbqq"] = BranchInfo<double>("Match_ttZ_3l_GP_Bbqq");

  branches["Full_match_ttZ_3l_GP_Bb"] = BranchInfo<double>("Full_match_ttZ_3l_GP_Bb");
  branches["Full_match_ttZ_3l_GP_Bq"] = BranchInfo<double>("Full_match_ttZ_3l_GP_Bq");
  branches["Full_match_ttZ_3l_GP_bq"] = BranchInfo<double>("Full_match_ttZ_3l_GP_bq");
  branches["Full_match_ttZ_3l_GP_Bbq"] = BranchInfo<double>("Full_match_ttZ_3l_GP_Bbq");
  branches["Full_match_ttZ_3l_GP_Bqq"] = BranchInfo<double>("Full_match_ttZ_3l_GP_Bqq");
  branches["Full_match_ttZ_3l_GP_bqq"] = BranchInfo<double>("Full_match_ttZ_3l_GP_bqq");
  branches["Full_match_ttZ_3l_GP_Bbqq"] = BranchInfo<double>("Full_match_ttZ_3l_GP_Bbqq");

  branches["ttZ_3l_GP_B_CSV"] = BranchInfo<double>("ttZ_3l_GP_B_CSV");
  branches["ttZ_3l_GP_b_CSV"] = BranchInfo<double>("ttZ_3l_GP_b_CSV");
  branches["ttZ_3l_GP_q_1_CSV"] = BranchInfo<double>("ttZ_3l_GP_q_1_CSV");
  branches["ttZ_3l_GP_q_2_CSV"] = BranchInfo<double>("ttZ_3l_GP_q_2_CSV");
  branches["ttZ_3l_GP_B_charge"] = BranchInfo<double>("ttZ_3l_GP_B_charge");
  branches["ttZ_3l_GP_b_charge"] = BranchInfo<double>("ttZ_3l_GP_b_charge");
  branches["ttZ_3l_GP_W_mass_qq"] = BranchInfo<double>("ttZ_3l_GP_W_mass_qq");
  branches["ttZ_3l_GP_W_sum_charge_qq"] = BranchInfo<double>("ttZ_3l_GP_W_sum_charge_qq");
  branches["ttZ_3l_GP_top_mass_lep_B"] = BranchInfo<double>("ttZ_3l_GP_top_mass_lep_B");
  branches["ttZ_3l_GP_top_mass_b_q"] = BranchInfo<double>("ttZ_3l_GP_top_mass_b_q");
  branches["ttZ_3l_GP_top_mass_b_qq"] = BranchInfo<double>("ttZ_3l_GP_top_mass_b_qq");
  branches["ttZ_3l_GP_ttbar_2j_MT_mass_ratio_Bb"] = BranchInfo<double>("ttZ_3l_GP_ttbar_2j_MT_mass_ratio_Bb");
  branches["ttZ_3l_GP_ttbar_2j_MT_mass_ratio_Bq"] = BranchInfo<double>("ttZ_3l_GP_ttbar_2j_MT_mass_ratio_Bq");
  branches["ttZ_3l_GP_ttbar_2j_MT_mass_ratio_bq"] = BranchInfo<double>("ttZ_3l_GP_ttbar_2j_MT_mass_ratio_bq");
  branches["ttZ_3l_GP_ttbar_3j_MT_mass_ratio_Bbq"] = BranchInfo<double>("ttZ_3l_GP_ttbar_3j_MT_mass_ratio_Bbq");
  branches["ttZ_3l_GP_ttbar_3j_MT_mass_ratio_Bqq"] = BranchInfo<double>("ttZ_3l_GP_ttbar_3j_MT_mass_ratio_Bqq");
  branches["ttZ_3l_GP_ttbar_3j_MT_mass_ratio_bqq"] = BranchInfo<double>("ttZ_3l_GP_ttbar_3j_MT_mass_ratio_bqq");
  branches["ttZ_3l_GP_ttbar_4j_MT_mass_ratio_Bbqq"] = BranchInfo<double>("ttZ_3l_GP_ttbar_4j_MT_mass_ratio_Bbqq");

  branches["Match_ttZ_3l_GP_Bb"].branchVal = KinematicVariableConstants::FLOAT_INIT; 
  branches["Match_ttZ_3l_GP_Bq"].branchVal = KinematicVariableConstants::FLOAT_INIT; 
  branches["Match_ttZ_3l_GP_bq"].branchVal = KinematicVariableConstants::FLOAT_INIT; 
  branches["Match_ttZ_3l_GP_Bbq"].branchVal = KinematicVariableConstants::FLOAT_INIT; 
  branches["Match_ttZ_3l_GP_Bqq"].branchVal = KinematicVariableConstants::FLOAT_INIT; 
  branches["Match_ttZ_3l_GP_bqq"].branchVal = KinematicVariableConstants::FLOAT_INIT; 
  branches["Match_ttZ_3l_GP_Bbqq"].branchVal = KinematicVariableConstants::FLOAT_INIT; 

  branches["Full_match_ttZ_3l_GP_Bb"].branchVal = 0.0; 
  branches["Full_match_ttZ_3l_GP_Bq"].branchVal = 0.0; 
  branches["Full_match_ttZ_3l_GP_bq"].branchVal = 0.0; 
  branches["Full_match_ttZ_3l_GP_Bbq"].branchVal = 0.0; 
  branches["Full_match_ttZ_3l_GP_Bqq"].branchVal = 0.0; 
  branches["Full_match_ttZ_3l_GP_bqq"].branchVal = 0.0; 
  branches["Full_match_ttZ_3l_GP_Bbqq"].branchVal = 0.0; 

  branches["ttZ_3l_GP_B_CSV"].branchVal = KinematicVariableConstants::FLOAT_INIT; 
  branches["ttZ_3l_GP_b_CSV"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttZ_3l_GP_q_1_CSV"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttZ_3l_GP_q_2_CSV"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttZ_3l_GP_B_charge"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttZ_3l_GP_b_charge"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttZ_3l_GP_W_mass_qq"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttZ_3l_GP_W_sum_charge_qq"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttZ_3l_GP_top_mass_lep_B"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttZ_3l_GP_top_mass_b_q"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttZ_3l_GP_top_mass_b_qq"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttZ_3l_GP_ttbar_2j_MT_mass_ratio_Bb"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttZ_3l_GP_ttbar_2j_MT_mass_ratio_Bq"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttZ_3l_GP_ttbar_2j_MT_mass_ratio_bq"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttZ_3l_GP_ttbar_3j_MT_mass_ratio_Bbq"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttZ_3l_GP_ttbar_3j_MT_mass_ratio_Bqq"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttZ_3l_GP_ttbar_3j_MT_mass_ratio_bqq"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttZ_3l_GP_ttbar_4j_MT_mass_ratio_Bbqq"].branchVal = KinematicVariableConstants::FLOAT_INIT;

  //std::cout << "Getting weight file" << std::endl;
  string directory = (string(getenv("CMSSW_BASE"))+"/src/ttHMultileptonAnalysis/TemplateMakers/data/NOVa/matchbox/").c_str();
  //TString weight_file_name = Form("%smatch_ttbarZ_3l.root", directory.c_str());
  //TString weight_file_name = Form("%smatch_ttbar_lj.root", directory.c_str());
  TString weight_file_name = Form("%smatch_ttbar_lj_by_nJet_genPresent.root", directory.c_str());
  weight_file = TFile::Open(weight_file_name);
  //std::cout << weight_file_name << std::endl;

  //std::cout << "Cloning histograms" << std::endl;  
  ratio_top_jet_CSV_le3j = (TH1*)weight_file->Get("ratio_top_jet_CSV_le3j")->Clone();
  ratio_top_jet_CSV_eq4j = (TH1*)weight_file->Get("ratio_top_jet_CSV_eq4j")->Clone();
  ratio_top_jet_CSV_eq5j = (TH1*)weight_file->Get("ratio_top_jet_CSV_eq5j")->Clone();
  ratio_top_jet_CSV_ge6j = (TH1*)weight_file->Get("ratio_top_jet_CSV_ge6j")->Clone();
  ratio_W_jet_1_CSV_le3j = (TH1*)weight_file->Get("ratio_W_jet_1_CSV_le3j")->Clone();
  ratio_W_jet_1_CSV_eq4j = (TH1*)weight_file->Get("ratio_W_jet_1_CSV_eq4j")->Clone();
  ratio_W_jet_1_CSV_eq5j = (TH1*)weight_file->Get("ratio_W_jet_1_CSV_eq5j")->Clone();
  ratio_W_jet_1_CSV_ge6j = (TH1*)weight_file->Get("ratio_W_jet_1_CSV_ge6j")->Clone();
  ratio_W_jet_2_CSV_le3j = (TH1*)weight_file->Get("ratio_W_jet_2_CSV_le3j")->Clone();
  ratio_W_jet_2_CSV_eq4j = (TH1*)weight_file->Get("ratio_W_jet_2_CSV_eq4j")->Clone();
  ratio_W_jet_2_CSV_eq5j = (TH1*)weight_file->Get("ratio_W_jet_2_CSV_eq5j")->Clone();
  ratio_W_jet_2_CSV_ge6j = (TH1*)weight_file->Get("ratio_W_jet_2_CSV_ge6j")->Clone();
  ratio_lepTop_jet_charge = (TH1*)weight_file->Get("ratio_lepTop_jet_charge")->Clone();
  ratio_hadTop_jet_charge = (TH1*)weight_file->Get("ratio_hadTop_jet_charge")->Clone();
  ratio_top_mass_lep_B_le3j = (TH1*)weight_file->Get("ratio_top_mass_lep_B_le3j")->Clone();
  ratio_top_mass_lep_B_eq4j = (TH1*)weight_file->Get("ratio_top_mass_lep_B_eq4j")->Clone();
  ratio_top_mass_lep_B_eq5j = (TH1*)weight_file->Get("ratio_top_mass_lep_B_eq5j")->Clone();
  ratio_top_mass_lep_B_ge6j = (TH1*)weight_file->Get("ratio_top_mass_lep_B_ge6j")->Clone();
  ratio_top_MT_met_lep_B_le3j = (TH1*)weight_file->Get("ratio_top_MT_met_lep_B_le3j")->Clone();
  ratio_top_MT_met_lep_B_eq4j = (TH1*)weight_file->Get("ratio_top_MT_met_lep_B_eq4j")->Clone();
  ratio_top_MT_met_lep_B_eq5j = (TH1*)weight_file->Get("ratio_top_MT_met_lep_B_eq5j")->Clone();
  ratio_top_MT_met_lep_B_ge6j = (TH1*)weight_file->Get("ratio_top_MT_met_lep_B_ge6j")->Clone();
  ratio_W_mass_qq_le3j = (TH1*)weight_file->Get("ratio_W_mass_qq_le3j")->Clone();
  ratio_W_mass_qq_eq4j = (TH1*)weight_file->Get("ratio_W_mass_qq_eq4j")->Clone();
  ratio_W_mass_qq_eq5j = (TH1*)weight_file->Get("ratio_W_mass_qq_eq5j")->Clone();
  ratio_W_mass_qq_ge6j = (TH1*)weight_file->Get("ratio_W_mass_qq_ge6j")->Clone();
  ratio_W_sum_charge_qq = (TH1*)weight_file->Get("ratio_W_sum_charge_qq")->Clone();
  ratio_top_mass_b_q_le3j = (TH1*)weight_file->Get("ratio_top_mass_b_q_le3j")->Clone();
  ratio_top_mass_b_q_eq4j = (TH1*)weight_file->Get("ratio_top_mass_b_q_eq4j")->Clone();
  ratio_top_mass_b_q_eq5j = (TH1*)weight_file->Get("ratio_top_mass_b_q_eq5j")->Clone();
  ratio_top_mass_b_q_ge6j = (TH1*)weight_file->Get("ratio_top_mass_b_q_ge6j")->Clone();
  ratio_top_mass_b_qq_le3j = (TH1*)weight_file->Get("ratio_top_mass_b_qq_le3j")->Clone();
  ratio_top_mass_b_qq_eq4j = (TH1*)weight_file->Get("ratio_top_mass_b_qq_eq4j")->Clone();
  ratio_top_mass_b_qq_eq5j = (TH1*)weight_file->Get("ratio_top_mass_b_qq_eq5j")->Clone();
  ratio_top_mass_b_qq_ge6j = (TH1*)weight_file->Get("ratio_top_mass_b_qq_ge6j")->Clone();
  ratio_ttbar_2j_MT_mass_ratio_le3j = (TH1*)weight_file->Get("ratio_ttbar_2j_MT_mass_ratio_le3j")->Clone();
  ratio_ttbar_2j_MT_mass_ratio_ge4j = (TH1*)weight_file->Get("ratio_ttbar_2j_MT_mass_ratio_ge4j")->Clone();
  ratio_ttbar_3j_MT_mass_ratio_le3j = (TH1*)weight_file->Get("ratio_ttbar_3j_MT_mass_ratio_le3j")->Clone();
  ratio_ttbar_3j_MT_mass_ratio_eq4j = (TH1*)weight_file->Get("ratio_ttbar_3j_MT_mass_ratio_eq4j")->Clone();
  ratio_ttbar_3j_MT_mass_ratio_ge5j = (TH1*)weight_file->Get("ratio_ttbar_3j_MT_mass_ratio_ge5j")->Clone();
  ratio_ttbar_4j_MT_mass_ratio_eq4j = (TH1*)weight_file->Get("ratio_ttbar_4j_MT_mass_ratio_eq4j")->Clone();
  ratio_ttbar_4j_MT_mass_ratio_eq5j = (TH1*)weight_file->Get("ratio_ttbar_4j_MT_mass_ratio_eq5j")->Clone();
  ratio_ttbar_4j_MT_mass_ratio_ge6j = (TH1*)weight_file->Get("ratio_ttbar_4j_MT_mass_ratio_ge6j")->Clone();
  corr_top_mass_b_qq_W_mass_qq_le3j = (TH1*)weight_file->Get("corr_top_mass_b_qq_W_mass_qq_le3j")->Clone();
  corr_top_mass_b_qq_W_mass_qq_eq4j = (TH1*)weight_file->Get("corr_top_mass_b_qq_W_mass_qq_eq4j")->Clone();
  corr_top_mass_b_qq_W_mass_qq_eq5j = (TH1*)weight_file->Get("corr_top_mass_b_qq_W_mass_qq_eq5j")->Clone();
  corr_top_mass_b_qq_W_mass_qq_ge6j = (TH1*)weight_file->Get("corr_top_mass_b_qq_W_mass_qq_ge6j")->Clone();
  corr_top_MT_met_lep_B_top_mass_lep_B_le3j = (TH1*)weight_file->Get("corr_top_MT_met_lep_B_top_mass_lep_B_le3j")->Clone();
  corr_top_MT_met_lep_B_top_mass_lep_B_eq4j = (TH1*)weight_file->Get("corr_top_MT_met_lep_B_top_mass_lep_B_eq4j")->Clone();
  corr_top_MT_met_lep_B_top_mass_lep_B_eq5j = (TH1*)weight_file->Get("corr_top_MT_met_lep_B_top_mass_lep_B_eq5j")->Clone();
  corr_top_MT_met_lep_B_top_mass_lep_B_ge6j = (TH1*)weight_file->Get("corr_top_MT_met_lep_B_top_mass_lep_B_ge6j")->Clone();

//   ratio_top_jet_CSV = (TH1*)weight_file->Get("ratio_top_jet_CSV")->Clone();
//   ratio_W_jet_1_CSV = (TH1*)weight_file->Get("ratio_W_jet_1_CSV")->Clone();
//   ratio_W_jet_2_CSV = (TH1*)weight_file->Get("ratio_W_jet_2_CSV")->Clone();
//   ratio_lepTop_jet_charge = (TH1*)weight_file->Get("ratio_lepTop_jet_charge")->Clone();
//   ratio_hadTop_jet_charge = (TH1*)weight_file->Get("ratio_hadTop_jet_charge")->Clone();
//   ratio_W_mass_qq = (TH1*)weight_file->Get("ratio_W_mass_qq")->Clone();
//   ratio_W_sum_charge_qq = (TH1*)weight_file->Get("ratio_W_sum_charge_qq")->Clone();
//   ratio_top_mass_lep_B = (TH1*)weight_file->Get("ratio_top_mass_lep_B")->Clone();
//   ratio_top_MT_met_lep_B = (TH1*)weight_file->Get("ratio_top_MT_met_lep_B")->Clone();
//   ratio_top_mass_b_q = (TH1*)weight_file->Get("ratio_top_mass_b_q")->Clone();
//   ratio_top_mass_b_qq = (TH1*)weight_file->Get("ratio_top_mass_b_qq")->Clone();
//   ratio_ttbar_MT_mass_ratio_B_b_qq = (TH1*)weight_file->Get("ratio_ttbar_MT_mass_ratio_B_b_qq")->Clone();
//   corr_top_MT_met_lep_B_top_mass_lep_B = (TH1*)weight_file->Get("corr_top_MT_met_lep_B_top_mass_lep_B")->Clone();
//   corr_top_mass_b_qq_W_mass_qq = (TH1*)weight_file->Get("corr_top_mass_b_qq_W_mass_qq")->Clone();

  //std::cout << "Finished initializing MatchTester_ttZ_3l_GP" << std::endl;
}

void MatchTester_ttZ_3l_GP::evaluate() {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  //std::cout << "Evaluating MatchTester_ttZ_3l_GP" << std::endl;
  
  if ( (*leptons)->size() != 1) return;
  if ( (*jets)->size() < 2) return;

  TH1 * ratio_top_jet_CSV;
  TH1 * ratio_W_jet_1_CSV;
  TH1 * ratio_W_jet_2_CSV;
  //TH1 * ratio_lepTop_jet_charge;
  //TH1 * ratio_hadTop_jet_charge;
  TH1 * ratio_W_mass_qq;
  //TH1 * ratio_W_sum_charge_qq;
  TH1 * ratio_top_mass_lep_B;
  TH1 * ratio_top_MT_met_lep_B;
  TH1 * ratio_top_mass_b_q;
  TH1 * ratio_top_mass_b_qq;
  TH1 * ratio_ttbar_2j_MT_mass_ratio;
  TH1 * ratio_ttbar_3j_MT_mass_ratio;
  TH1 * ratio_ttbar_4j_MT_mass_ratio;
  TH1 * corr_top_mass_b_qq_W_mass_qq;
  TH1 * corr_top_MT_met_lep_B_top_mass_lep_B;

  if ( (*jets)->size() <= 3) {
    ratio_top_jet_CSV = ratio_top_jet_CSV_le3j;
    ratio_W_jet_1_CSV = ratio_W_jet_1_CSV_le3j;
    ratio_W_jet_2_CSV = ratio_W_jet_2_CSV_le3j;
    ratio_W_mass_qq = ratio_W_mass_qq_le3j;
    ratio_top_mass_lep_B = ratio_top_mass_lep_B_le3j;
    ratio_top_MT_met_lep_B = ratio_top_MT_met_lep_B_le3j;
    ratio_top_mass_b_q = ratio_top_mass_b_q_le3j;
    ratio_top_mass_b_qq = ratio_top_mass_b_qq_le3j;
    ratio_ttbar_2j_MT_mass_ratio = ratio_ttbar_2j_MT_mass_ratio_le3j;
    ratio_ttbar_3j_MT_mass_ratio = ratio_ttbar_3j_MT_mass_ratio_le3j;
    //ratio_ttbar_4j_MT_mass_ratio = ratio_ttbar_4j_MT_mass_ratio;
    corr_top_mass_b_qq_W_mass_qq = corr_top_mass_b_qq_W_mass_qq_le3j;
    corr_top_MT_met_lep_B_top_mass_lep_B = corr_top_MT_met_lep_B_top_mass_lep_B_le3j; }
  if ( (*jets)->size() == 4) {
    ratio_top_jet_CSV = ratio_top_jet_CSV_eq4j;
    ratio_W_jet_1_CSV = ratio_W_jet_1_CSV_eq4j;
    ratio_W_jet_2_CSV = ratio_W_jet_2_CSV_eq4j;
    ratio_W_mass_qq = ratio_W_mass_qq_eq4j;
    ratio_top_mass_lep_B = ratio_top_mass_lep_B_eq4j;
    ratio_top_MT_met_lep_B = ratio_top_MT_met_lep_B_eq4j;
    ratio_top_mass_b_q = ratio_top_mass_b_q_eq4j;
    ratio_top_mass_b_qq = ratio_top_mass_b_qq_eq4j;
    ratio_ttbar_2j_MT_mass_ratio = ratio_ttbar_2j_MT_mass_ratio_ge4j;
    ratio_ttbar_3j_MT_mass_ratio = ratio_ttbar_3j_MT_mass_ratio_eq4j;
    ratio_ttbar_4j_MT_mass_ratio = ratio_ttbar_4j_MT_mass_ratio_eq4j;
    corr_top_mass_b_qq_W_mass_qq = corr_top_mass_b_qq_W_mass_qq_eq4j;
    corr_top_MT_met_lep_B_top_mass_lep_B = corr_top_MT_met_lep_B_top_mass_lep_B_eq4j; }
  if ( (*jets)->size() == 5) {
    ratio_top_jet_CSV = ratio_top_jet_CSV_eq5j;
    ratio_W_jet_1_CSV = ratio_W_jet_1_CSV_eq5j;
    ratio_W_jet_2_CSV = ratio_W_jet_2_CSV_eq5j;
    ratio_W_mass_qq = ratio_W_mass_qq_eq5j;
    ratio_top_mass_lep_B = ratio_top_mass_lep_B_eq5j;
    ratio_top_MT_met_lep_B = ratio_top_MT_met_lep_B_eq5j;
    ratio_top_mass_b_q = ratio_top_mass_b_q_eq5j;
    ratio_top_mass_b_qq = ratio_top_mass_b_qq_eq5j;
    ratio_ttbar_2j_MT_mass_ratio = ratio_ttbar_2j_MT_mass_ratio_ge4j;
    ratio_ttbar_3j_MT_mass_ratio = ratio_ttbar_3j_MT_mass_ratio_ge5j;
    ratio_ttbar_4j_MT_mass_ratio = ratio_ttbar_4j_MT_mass_ratio_eq5j;
    corr_top_mass_b_qq_W_mass_qq = corr_top_mass_b_qq_W_mass_qq_eq5j;
    corr_top_MT_met_lep_B_top_mass_lep_B = corr_top_MT_met_lep_B_top_mass_lep_B_eq5j; }
  else {
    ratio_top_jet_CSV = ratio_top_jet_CSV_ge6j;
    ratio_W_jet_1_CSV = ratio_W_jet_1_CSV_ge6j;
    ratio_W_jet_2_CSV = ratio_W_jet_2_CSV_ge6j;
    ratio_W_mass_qq = ratio_W_mass_qq_ge6j;
    ratio_top_mass_lep_B = ratio_top_mass_lep_B_ge6j;
    ratio_top_MT_met_lep_B = ratio_top_MT_met_lep_B_ge6j;
    ratio_top_mass_b_q = ratio_top_mass_b_q_ge6j;
    ratio_top_mass_b_qq = ratio_top_mass_b_qq_ge6j;
    ratio_ttbar_2j_MT_mass_ratio = ratio_ttbar_2j_MT_mass_ratio_ge4j;
    ratio_ttbar_3j_MT_mass_ratio = ratio_ttbar_3j_MT_mass_ratio_ge5j;
    ratio_ttbar_4j_MT_mass_ratio = ratio_ttbar_4j_MT_mass_ratio_ge6j;
    corr_top_mass_b_qq_W_mass_qq = corr_top_mass_b_qq_W_mass_qq_ge6j;
    corr_top_MT_met_lep_B_top_mass_lep_B = corr_top_MT_met_lep_B_top_mass_lep_B_ge6j; }

  //std::cout << "There's at least one lepton" << std::endl;
  
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
  TLorentzVector jet_12_vect;
  TLorentzVector jet_12_vect_trans;
  TLorentzVector jet_123_vect;
  TLorentzVector jet_123_vect_trans;

  double top_mass_lep_B = 0.0;
  double top_MT_met_lep_B = 0.0;
  double W_mass_qq = 0.0;
  double W_sum_charge_qq = 0.0;
  double top_mass_b_q = 0.0;
  double top_mass_b_qq = 0.0;
  double ttbar_4j_MT_mass_ratio = 0.0;

  double ratio_Bb = 0.0000000001;
  double ratio_Bq = 0.0000000001;
  double ratio_bq = 0.0000000001;
  double ratio_Bbq = 0.0000000001;
  double ratio_Bqq = 0.0000000001;
  double ratio_bqq = 0.0000000001;
  double ratio_Bbqq = 0.0000000001;

  int bin = 0;
  int lep_charge = std::max((*leptons)->at(0)->tkCharge, -1);

  //B is the b from a leptonic top
  //b is the b from the hardonic top
  //q is a jet from the W
  
  //std::cout << "About to enter jet loop" << std::endl;
  
  for (unsigned int iJet1 = 0; iJet1 < (*jets)->size(); iJet1++) {    
    //std::cout << "iJet1 = " << iJet1 << std::endl;    
    jet1_vect.SetPtEtaPhiE((*jets)->at(iJet1).pt, (*jets)->at(iJet1).eta, (*jets)->at(iJet1).phi, (*jets)->at(iJet1).energy);
    jet1_vect_trans.SetPtEtaPhiE((*jets)->at(iJet1).pt, 0.0, (*jets)->at(iJet1).phi, (*jets)->at(iJet1).pt);

    for (unsigned int iJet2 = 0; iJet2 < (*jets)->size(); iJet2++) {
      if (iJet2 == iJet1) continue;
      //std::cout << "iJet2 = " << iJet1 << std::endl;      
      jet2_vect.SetPtEtaPhiE((*jets)->at(iJet2).pt, (*jets)->at(iJet2).eta, (*jets)->at(iJet2).phi, (*jets)->at(iJet2).energy);
      jet2_vect_trans.SetPtEtaPhiE((*jets)->at(iJet2).pt, 0, (*jets)->at(iJet2).phi, (*jets)->at(iJet2).pt);
      jet_12_vect = jet1_vect+jet2_vect;
      jet_12_vect_trans = jet1_vect_trans+jet2_vect_trans;

      //ratio_Bb
      lep_B_vect = lep_vect+jet1_vect;
      met_lep_B_vect_trans = met_vect+lep_vect_trans+jet1_vect_trans;
      top_mass_lep_B = lep_B_vect.M();
      top_MT_met_lep_B = met_lep_B_vect_trans.M();

      bin = std::max(1, std::min(ratio_top_jet_CSV->GetNbinsX(), ratio_top_jet_CSV->GetXaxis()->FindBin((*jets)->at(iJet1).btagCombinedSecVertex)) );
      ratio_Bb = ratio_top_jet_CSV->GetBinContent(bin);
      bin = std::max(1, std::min(ratio_top_jet_CSV->GetNbinsX(), ratio_top_jet_CSV->GetXaxis()->FindBin((*jets)->at(iJet2).btagCombinedSecVertex)) );
      ratio_Bb *= ratio_top_jet_CSV->GetBinContent(bin);
      bin = std::max(1, std::min(ratio_lepTop_jet_charge->GetNbinsX(), ratio_lepTop_jet_charge->GetXaxis()->FindBin(lep_charge*(*jets)->at(iJet1).charge)) );
      ratio_Bb *= ratio_lepTop_jet_charge->GetBinContent(bin);
      bin = std::max(1, std::min(ratio_hadTop_jet_charge->GetNbinsX(), ratio_hadTop_jet_charge->GetXaxis()->FindBin(lep_charge*(*jets)->at(iJet2).charge)) );
      ratio_Bb *= ratio_hadTop_jet_charge->GetBinContent(bin);
      bin = std::max(1, std::min(ratio_top_mass_lep_B->GetNbinsX(), ratio_top_mass_lep_B->GetXaxis()->FindBin(top_mass_lep_B)) );
      ratio_Bb *= ratio_top_mass_lep_B->GetBinContent(bin);
      bin = std::max(1, std::min(ratio_top_MT_met_lep_B->GetNbinsX(), ratio_top_MT_met_lep_B->GetXaxis()->FindBin(top_MT_met_lep_B)) );
      ratio_Bb *= ratio_top_MT_met_lep_B->GetBinContent(bin);
      bin = std::max(1, std::min(ratio_ttbar_2j_MT_mass_ratio->GetNbinsX(), ratio_ttbar_2j_MT_mass_ratio->GetXaxis()->FindBin(jet_12_vect_trans.M()/jet_12_vect.M())) );
      ratio_Bb *= ratio_ttbar_2j_MT_mass_ratio->GetBinContent(bin);
      bin = std::max(1, std::min(corr_top_MT_met_lep_B_top_mass_lep_B->GetNbinsX(), corr_top_MT_met_lep_B_top_mass_lep_B->GetXaxis()->FindBin(top_MT_met_lep_B)) );
      ratio_Bb *= (corr_top_MT_met_lep_B_top_mass_lep_B->GetBinContent(bin));

      if (log(ratio_Bb) > branches["Match_ttZ_3l_GP_Bb"].branchVal) {
        branches["Match_ttZ_3l_GP_Bb"].branchVal = log(ratio_Bb);
        branches["Full_match_ttZ_3l_GP_Bb"].branchVal = ((*jets)->at(iJet1).genPartonMotherId == 6*lep_charge &&
                                                      (*jets)->at(iJet2).genPartonMotherId == -6*lep_charge);
        branches["ttZ_3l_GP_B_CSV"].branchVal = (*jets)->at(iJet1).btagCombinedSecVertex;
        branches["ttZ_3l_GP_b_CSV"].branchVal = (*jets)->at(iJet2).btagCombinedSecVertex;
        branches["ttZ_3l_GP_B_charge"].branchVal = lep_charge*(*jets)->at(iJet1).charge;
        branches["ttZ_3l_GP_b_charge"].branchVal = lep_charge*(*jets)->at(iJet2).charge;
        branches["ttZ_3l_GP_top_mass_lep_B"].branchVal = top_mass_lep_B;
        branches["ttZ_3l_GP_ttbar_2j_MT_mass_ratio_Bb"].branchVal = jet_12_vect_trans.M()/jet_12_vect.M();
      }
      
      //ratio_Bq
      lep_B_vect = lep_vect+jet1_vect;
      met_lep_B_vect_trans = met_vect+lep_vect_trans+jet1_vect_trans;
      top_mass_lep_B = lep_B_vect.M();
      top_MT_met_lep_B = met_lep_B_vect_trans.M();
      
      bin = std::max(1, std::min(ratio_top_jet_CSV->GetNbinsX(), ratio_top_jet_CSV->GetXaxis()->FindBin((*jets)->at(iJet1).btagCombinedSecVertex)) );
      ratio_Bq = ratio_top_jet_CSV->GetBinContent(bin);
      bin = std::max(1, std::min(ratio_lepTop_jet_charge->GetNbinsX(), ratio_lepTop_jet_charge->GetXaxis()->FindBin(lep_charge*(*jets)->at(iJet1).charge)) );
      ratio_Bq *= ratio_lepTop_jet_charge->GetBinContent(bin);
      bin = std::max(1, std::min(ratio_W_jet_1_CSV->GetNbinsX(), ratio_W_jet_1_CSV->GetXaxis()->FindBin((*jets)->at(iJet2).btagCombinedSecVertex)) );
      ratio_Bq *= ratio_W_jet_1_CSV->GetBinContent(bin);
      bin = std::max(1, std::min(ratio_top_mass_lep_B->GetNbinsX(), ratio_top_mass_lep_B->GetXaxis()->FindBin(top_mass_lep_B)) );
      ratio_Bq *= ratio_top_mass_lep_B->GetBinContent(bin);
      bin = std::max(1, std::min(ratio_top_MT_met_lep_B->GetNbinsX(), ratio_top_MT_met_lep_B->GetXaxis()->FindBin(top_MT_met_lep_B)) );
      ratio_Bq *= ratio_top_MT_met_lep_B->GetBinContent(bin);
      bin = std::max(1, std::min(ratio_ttbar_2j_MT_mass_ratio->GetNbinsX(), ratio_ttbar_2j_MT_mass_ratio->GetXaxis()->FindBin(jet_12_vect_trans.M()/jet_12_vect.M())) );
      ratio_Bq *= ratio_ttbar_2j_MT_mass_ratio->GetBinContent(bin);
      bin = std::max(1, std::min(corr_top_MT_met_lep_B_top_mass_lep_B->GetNbinsX(), corr_top_MT_met_lep_B_top_mass_lep_B->GetXaxis()->FindBin(top_MT_met_lep_B)) );
      ratio_Bq *= (corr_top_MT_met_lep_B_top_mass_lep_B->GetBinContent(bin));

      if (log(ratio_Bq) > branches["Match_ttZ_3l_GP_Bq"].branchVal) {
        branches["Match_ttZ_3l_GP_Bq"].branchVal = log(ratio_Bq);
        branches["Full_match_ttZ_3l_GP_Bq"].branchVal = ((*jets)->at(iJet1).genPartonMotherId == 6*lep_charge &&
                                                      abs((*jets)->at(iJet2).genPartonMotherId) == 24);
        branches["ttZ_3l_GP_B_CSV"].branchVal = (*jets)->at(iJet1).btagCombinedSecVertex;
        branches["ttZ_3l_GP_q_1_CSV"].branchVal = (*jets)->at(iJet2).btagCombinedSecVertex;
        branches["ttZ_3l_GP_B_charge"].branchVal = lep_charge*(*jets)->at(iJet1).charge;
        branches["ttZ_3l_GP_top_mass_lep_B"].branchVal = top_mass_lep_B;
        branches["ttZ_3l_GP_ttbar_2j_MT_mass_ratio_Bq"].branchVal = jet_12_vect_trans.M()/jet_12_vect.M();
      }
      
      //ratio_bq
      b_q_vect = jet1_vect+jet2_vect;
      top_mass_b_q = b_q_vect.M();
      
      bin = std::max(1, std::min(ratio_top_jet_CSV->GetNbinsX(), ratio_top_jet_CSV->GetXaxis()->FindBin((*jets)->at(iJet1).btagCombinedSecVertex)) );
      ratio_bq = ratio_top_jet_CSV->GetBinContent(bin);
      bin = std::max(1, std::min(ratio_hadTop_jet_charge->GetNbinsX(), ratio_hadTop_jet_charge->GetXaxis()->FindBin(lep_charge*(*jets)->at(iJet1).charge)) );
      ratio_bq *= ratio_hadTop_jet_charge->GetBinContent(bin);
      bin = std::max(1, std::min(ratio_W_jet_1_CSV->GetNbinsX(), ratio_W_jet_1_CSV->GetXaxis()->FindBin((*jets)->at(iJet2).btagCombinedSecVertex)) );
      ratio_bq *= ratio_W_jet_1_CSV->GetBinContent(bin);
      bin = std::max(1, std::min(ratio_top_mass_b_q->GetNbinsX(), ratio_top_mass_b_q->GetXaxis()->FindBin(top_mass_b_q)) );
      ratio_bq *= ratio_top_mass_b_q->GetBinContent(bin);
      bin = std::max(1, std::min(ratio_ttbar_2j_MT_mass_ratio->GetNbinsX(), ratio_ttbar_2j_MT_mass_ratio->GetXaxis()->FindBin(jet_12_vect_trans.M()/jet_12_vect.M())) );
      ratio_bq *= ratio_ttbar_2j_MT_mass_ratio->GetBinContent(bin);

      if (log(ratio_bq) > branches["Match_ttZ_3l_GP_bq"].branchVal) {
        branches["Match_ttZ_3l_GP_bq"].branchVal = log(ratio_bq);
        branches["Full_match_ttZ_3l_GP_bq"].branchVal = ((*jets)->at(iJet1).genPartonMotherId == -6*lep_charge &&
                                                      abs((*jets)->at(iJet2).genPartonMotherId) == 24);
        branches["ttZ_3l_GP_b_CSV"].branchVal = (*jets)->at(iJet1).btagCombinedSecVertex;
        branches["ttZ_3l_GP_q_1_CSV"].branchVal = (*jets)->at(iJet2).btagCombinedSecVertex;
        branches["ttZ_3l_GP_b_charge"].branchVal = lep_charge*(*jets)->at(iJet1).charge;
        branches["ttZ_3l_GP_top_mass_b_q"].branchVal = top_mass_b_q;
        branches["ttZ_3l_GP_ttbar_2j_MT_mass_ratio_bq"].branchVal = jet_12_vect_trans.M()/jet_12_vect.M();
      }
      
      for (unsigned int iJet3 = 0; iJet3 < (*jets)->size(); iJet3++) {
        if (iJet3 == iJet1 || iJet3 == iJet1) continue;
        //std::cout << "iJet3 = " << iJet1 << std::endl;
        jet3_vect.SetPtEtaPhiE((*jets)->at(iJet3).pt, (*jets)->at(iJet3).eta, (*jets)->at(iJet3).phi, (*jets)->at(iJet3).energy);
        jet3_vect_trans.SetPtEtaPhiE((*jets)->at(iJet3).pt, 0, (*jets)->at(iJet3).phi, (*jets)->at(iJet3).pt);
        jet_123_vect = jet1_vect+jet2_vect+jet3_vect;
        jet_123_vect_trans = jet1_vect_trans+jet2_vect_trans+jet3_vect_trans;

        //ratio_Bbq
        b_q_vect = jet2_vect+jet3_vect;
        top_mass_b_q = b_q_vect.M();

        ratio_Bbq = ratio_Bb;
        bin = std::max(1, std::min(ratio_W_jet_1_CSV->GetNbinsX(), ratio_W_jet_1_CSV->GetXaxis()->FindBin((*jets)->at(iJet3).btagCombinedSecVertex)) );
        ratio_Bbq *= ratio_W_jet_1_CSV->GetBinContent(bin);
        bin = std::max(1, std::min(ratio_top_mass_b_q->GetNbinsX(), ratio_top_mass_b_q->GetXaxis()->FindBin(top_mass_b_q)) );
        ratio_Bbq *= ratio_top_mass_b_q->GetBinContent(bin);
        bin = std::max(1, std::min(ratio_ttbar_2j_MT_mass_ratio->GetNbinsX(), ratio_ttbar_2j_MT_mass_ratio->GetXaxis()->FindBin(jet_12_vect_trans.M()/jet_12_vect.M())) );
        ratio_Bbq *= (1/ratio_ttbar_2j_MT_mass_ratio->GetBinContent(bin));
        bin = std::max(1, std::min(ratio_ttbar_3j_MT_mass_ratio->GetNbinsX(), ratio_ttbar_3j_MT_mass_ratio->GetXaxis()->FindBin(jet_123_vect_trans.M()/jet_123_vect.M())) );
        ratio_Bbq *= ratio_ttbar_3j_MT_mass_ratio->GetBinContent(bin);

        if (log(ratio_Bbq) > branches["Match_ttZ_3l_GP_Bbq"].branchVal) {
          branches["Match_ttZ_3l_GP_Bbq"].branchVal = log(ratio_Bbq);
          branches["Full_match_ttZ_3l_GP_Bbq"].branchVal = ((*jets)->at(iJet1).genPartonMotherId == 6*lep_charge &&
                                                         (*jets)->at(iJet2).genPartonMotherId == -6*lep_charge &&
                                                         abs((*jets)->at(iJet3).genPartonMotherId) == 24);
          branches["ttZ_3l_GP_B_CSV"].branchVal = (*jets)->at(iJet1).btagCombinedSecVertex;
          branches["ttZ_3l_GP_b_CSV"].branchVal = (*jets)->at(iJet2).btagCombinedSecVertex;
          branches["ttZ_3l_GP_q_1_CSV"].branchVal = (*jets)->at(iJet3).btagCombinedSecVertex;
          branches["ttZ_3l_GP_B_charge"].branchVal = lep_charge*(*jets)->at(iJet1).charge;
          branches["ttZ_3l_GP_b_charge"].branchVal = lep_charge*(*jets)->at(iJet2).charge;
          branches["ttZ_3l_GP_top_mass_lep_B"].branchVal = top_mass_lep_B;
          branches["ttZ_3l_GP_top_mass_b_q"].branchVal = top_mass_b_q;
          branches["ttZ_3l_GP_ttbar_3j_MT_mass_ratio_Bbq"].branchVal = jet_123_vect_trans.M()/jet_123_vect.M();
        }

        //ratio_Bqq
        qq_vect = jet2_vect+jet3_vect;
        W_mass_qq = qq_vect.M();
        W_sum_charge_qq = lep_charge*((*jets)->at(iJet2).charge + (*jets)->at(iJet3).charge);

        ratio_Bqq = ratio_Bq;
        bin = std::max(1, std::min(ratio_W_jet_2_CSV->GetNbinsX(), ratio_W_jet_2_CSV->GetXaxis()->FindBin((*jets)->at(iJet3).btagCombinedSecVertex)) );
        ratio_Bqq *= ratio_W_jet_2_CSV->GetBinContent(bin);
        bin = std::max(1, std::min(ratio_W_mass_qq->GetNbinsX(), ratio_W_mass_qq->GetXaxis()->FindBin(W_mass_qq)) );
        ratio_Bqq *= ratio_W_mass_qq->GetBinContent(bin);
        bin = std::max(1, std::min(ratio_W_sum_charge_qq->GetNbinsX(), ratio_W_sum_charge_qq->GetXaxis()->FindBin(W_sum_charge_qq)) );
        ratio_Bqq *= ratio_W_sum_charge_qq->GetBinContent(bin);
        bin = std::max(1, std::min(ratio_ttbar_2j_MT_mass_ratio->GetNbinsX(), ratio_ttbar_2j_MT_mass_ratio->GetXaxis()->FindBin(jet_12_vect_trans.M()/jet_12_vect.M())) );
        ratio_Bqq *= (1/ratio_ttbar_2j_MT_mass_ratio->GetBinContent(bin));
        bin = std::max(1, std::min(ratio_ttbar_3j_MT_mass_ratio->GetNbinsX(), ratio_ttbar_3j_MT_mass_ratio->GetXaxis()->FindBin(jet_123_vect_trans.M()/jet_123_vect.M())) );
        ratio_Bqq *= ratio_ttbar_3j_MT_mass_ratio->GetBinContent(bin);

        if (log(ratio_Bqq) > branches["Match_ttZ_3l_GP_Bqq"].branchVal) {
          branches["Match_ttZ_3l_GP_Bqq"].branchVal = log(ratio_Bqq);
          branches["Full_match_ttZ_3l_GP_Bqq"].branchVal = ((*jets)->at(iJet1).genPartonMotherId == 6*lep_charge &&
                                                         abs((*jets)->at(iJet2).genPartonMotherId) == 24 &&
                                                         abs((*jets)->at(iJet3).genPartonMotherId) == 24);
          branches["ttZ_3l_GP_B_CSV"].branchVal = (*jets)->at(iJet1).btagCombinedSecVertex;
          branches["ttZ_3l_GP_q_1_CSV"].branchVal = (*jets)->at(iJet2).btagCombinedSecVertex;
          branches["ttZ_3l_GP_q_2_CSV"].branchVal = (*jets)->at(iJet3).btagCombinedSecVertex;
          branches["ttZ_3l_GP_B_charge"].branchVal = lep_charge*(*jets)->at(iJet1).charge;
          branches["ttZ_3l_GP_top_mass_lep_B"].branchVal = top_mass_lep_B;
          branches["ttZ_3l_GP_W_mass_qq"].branchVal = W_mass_qq;
          branches["ttZ_3l_GP_W_sum_charge_qq"].branchVal = W_sum_charge_qq;
          branches["ttZ_3l_GP_ttbar_3j_MT_mass_ratio_Bqq"].branchVal = jet_123_vect_trans.M()/jet_123_vect.M();
        }

        //ratio_bqq
        qq_vect = jet2_vect+jet3_vect;
        W_mass_qq = qq_vect.M();
        W_sum_charge_qq = lep_charge*((*jets)->at(iJet2).charge + (*jets)->at(iJet3).charge);
        b_q_vect = jet1_vect+jet2_vect;
        top_mass_b_q = b_q_vect.M();
        b_qq_vect = jet1_vect+jet2_vect+jet3_vect;
        top_mass_b_qq = b_qq_vect.M();

        ratio_bqq = ratio_bq;
        bin = std::max(1, std::min(ratio_W_jet_2_CSV->GetNbinsX(), ratio_W_jet_2_CSV->GetXaxis()->FindBin((*jets)->at(iJet3).btagCombinedSecVertex)) );
        ratio_bqq *= ratio_W_jet_2_CSV->GetBinContent(bin);
        bin = std::max(1, std::min(ratio_W_mass_qq->GetNbinsX(), ratio_W_mass_qq->GetXaxis()->FindBin(W_mass_qq)) );
        ratio_bqq *= ratio_W_mass_qq->GetBinContent(bin);
        bin = std::max(1, std::min(ratio_W_sum_charge_qq->GetNbinsX(), ratio_W_sum_charge_qq->GetXaxis()->FindBin(W_sum_charge_qq)) );
        ratio_bqq *= ratio_W_sum_charge_qq->GetBinContent(bin);
        bin = std::max(1, std::min(ratio_top_mass_b_q->GetNbinsX(), ratio_top_mass_b_q->GetXaxis()->FindBin(top_mass_b_q)) );
        ratio_bqq *= (1/ratio_top_mass_b_q->GetBinContent(bin));
        bin = std::max(1, std::min(ratio_top_mass_b_qq->GetNbinsX(), ratio_top_mass_b_qq->GetXaxis()->FindBin(top_mass_b_qq)) );
        ratio_bqq *= ratio_top_mass_b_qq->GetBinContent(bin);
        bin = std::max(1, std::min(ratio_ttbar_2j_MT_mass_ratio->GetNbinsX(), ratio_ttbar_2j_MT_mass_ratio->GetXaxis()->FindBin(jet_12_vect_trans.M()/jet_12_vect.M())) );
        ratio_bqq *= (1/ratio_ttbar_2j_MT_mass_ratio->GetBinContent(bin));
        bin = std::max(1, std::min(ratio_ttbar_3j_MT_mass_ratio->GetNbinsX(), ratio_ttbar_3j_MT_mass_ratio->GetXaxis()->FindBin(jet_123_vect_trans.M()/jet_123_vect.M())) );
        ratio_bqq *= ratio_ttbar_3j_MT_mass_ratio->GetBinContent(bin);
        bin = std::max(1, std::min(corr_top_mass_b_qq_W_mass_qq->GetNbinsX(), corr_top_mass_b_qq_W_mass_qq->GetXaxis()->FindBin(top_mass_b_qq)) );
        ratio_bqq *= corr_top_mass_b_qq_W_mass_qq->GetBinContent(bin);

        if (log(ratio_bqq) > branches["Match_ttZ_3l_GP_bqq"].branchVal) {
          branches["Match_ttZ_3l_GP_bqq"].branchVal = log(ratio_bqq);
          branches["Full_match_ttZ_3l_GP_bqq"].branchVal = ((*jets)->at(iJet1).genPartonMotherId == -6*lep_charge &&
                                                   abs((*jets)->at(iJet2).genPartonMotherId) == 24 &&
                                                   abs((*jets)->at(iJet3).genPartonMotherId) == 24);
          branches["ttZ_3l_GP_b_CSV"].branchVal = (*jets)->at(iJet1).btagCombinedSecVertex;
          branches["ttZ_3l_GP_q_1_CSV"].branchVal = (*jets)->at(iJet2).btagCombinedSecVertex;
          branches["ttZ_3l_GP_q_2_CSV"].branchVal = (*jets)->at(iJet3).btagCombinedSecVertex;
          branches["ttZ_3l_GP_b_charge"].branchVal = lep_charge*(*jets)->at(iJet1).charge;
          branches["ttZ_3l_GP_W_mass_qq"].branchVal = W_mass_qq;
          branches["ttZ_3l_GP_W_sum_charge_qq"].branchVal = W_sum_charge_qq;
          branches["ttZ_3l_GP_top_mass_b_qq"].branchVal = top_mass_b_qq;
          branches["ttZ_3l_GP_ttbar_3j_MT_mass_ratio_bqq"].branchVal = jet_123_vect_trans.M()/jet_123_vect.M();
        }

        
        for (unsigned int iJet4 = 0; iJet4 < (*jets)->size(); iJet4++) { 
          if (iJet4 == iJet1 || iJet4 == iJet2 || iJet4 == iJet3) continue;
          //std::cout << "iJet4 = " << iJet1 << std::endl;
          jet4_vect.SetPtEtaPhiE((*jets)->at(iJet4).pt, (*jets)->at(iJet4).eta, (*jets)->at(iJet4).phi, (*jets)->at(iJet4).energy);
          jet4_vect_trans.SetPtEtaPhiE((*jets)->at(iJet4).pt, 0, (*jets)->at(iJet4).phi, (*jets)->at(iJet4).pt);

          //ratio_Bbqq
          qq_vect = jet3_vect+jet4_vect;
          W_mass_qq = qq_vect.M();
          W_sum_charge_qq = lep_charge*((*jets)->at(iJet3).charge + (*jets)->at(iJet4).charge);
          b_q_vect = jet2_vect+jet3_vect;
          top_mass_b_q = b_q_vect.M();
          b_qq_vect = jet2_vect+jet3_vect+jet4_vect;
          top_mass_b_qq = b_qq_vect.M();
          B_b_qq_vect = jet1_vect+jet2_vect+jet3_vect+jet4_vect;
          B_b_qq_vect_trans = jet1_vect_trans+jet2_vect_trans+jet3_vect_trans+jet4_vect_trans;
          ttbar_4j_MT_mass_ratio = B_b_qq_vect_trans.M()/B_b_qq_vect.M();
          
          ratio_Bbqq = ratio_Bbq;
          bin = std::max(1, std::min(ratio_W_jet_2_CSV->GetNbinsX(), ratio_W_jet_2_CSV->GetXaxis()->FindBin((*jets)->at(iJet4).btagCombinedSecVertex)) );
          ratio_Bbqq *= ratio_W_jet_2_CSV->GetBinContent(bin);
          bin = std::max(1, std::min(ratio_W_mass_qq->GetNbinsX(), ratio_W_mass_qq->GetXaxis()->FindBin(W_mass_qq)) );
          ratio_Bbqq *= ratio_W_mass_qq->GetBinContent(bin);
          bin = std::max(1, std::min(ratio_W_sum_charge_qq->GetNbinsX(), ratio_W_sum_charge_qq->GetXaxis()->FindBin(W_sum_charge_qq)) );
          ratio_Bbqq *= ratio_W_sum_charge_qq->GetBinContent(bin);
          bin = std::max(1, std::min(ratio_top_mass_b_q->GetNbinsX(), ratio_top_mass_b_q->GetXaxis()->FindBin(top_mass_b_q)) );
          ratio_Bbqq *= (1/ratio_top_mass_b_q->GetBinContent(bin));
          bin = std::max(1, std::min(ratio_top_mass_b_qq->GetNbinsX(), ratio_top_mass_b_qq->GetXaxis()->FindBin(top_mass_b_qq)) );
          ratio_Bbqq *= ratio_top_mass_b_qq->GetBinContent(bin);
          bin = std::max(1, std::min(ratio_ttbar_3j_MT_mass_ratio->GetNbinsX(), ratio_ttbar_3j_MT_mass_ratio->GetXaxis()->FindBin(jet_123_vect_trans.M()/jet_123_vect.M())) );
          ratio_Bbqq *= (1/ratio_ttbar_3j_MT_mass_ratio->GetBinContent(bin));
          bin = std::max(1, std::min(ratio_ttbar_4j_MT_mass_ratio->GetNbinsX(), ratio_ttbar_4j_MT_mass_ratio->GetXaxis()->FindBin(ttbar_4j_MT_mass_ratio)) );
          ratio_Bbqq *= ratio_ttbar_4j_MT_mass_ratio->GetBinContent(bin);
          bin = std::max(1, std::min(corr_top_mass_b_qq_W_mass_qq->GetNbinsX(), corr_top_mass_b_qq_W_mass_qq->GetXaxis()->FindBin(top_mass_b_qq)) );
          ratio_Bbqq *= (corr_top_mass_b_qq_W_mass_qq->GetBinContent(bin));

          if (log(ratio_Bbqq) > branches["Match_ttZ_3l_GP_Bbqq"].branchVal) {
            branches["Match_ttZ_3l_GP_Bbqq"].branchVal = log(ratio_Bbqq);
            branches["Full_match_ttZ_3l_GP_Bbqq"].branchVal = ((*jets)->at(iJet1).genPartonMotherId == 6*lep_charge &&
                                                            (*jets)->at(iJet2).genPartonMotherId == -6*lep_charge &&
                                                            abs((*jets)->at(iJet3).genPartonMotherId) == 24 &&
                                                            abs((*jets)->at(iJet4).genPartonMotherId) == 24);
            branches["ttZ_3l_GP_B_CSV"].branchVal = (*jets)->at(iJet1).btagCombinedSecVertex;
            branches["ttZ_3l_GP_b_CSV"].branchVal = (*jets)->at(iJet2).btagCombinedSecVertex;
            branches["ttZ_3l_GP_q_1_CSV"].branchVal = (*jets)->at(iJet3).btagCombinedSecVertex;
            branches["ttZ_3l_GP_q_2_CSV"].branchVal = (*jets)->at(iJet4).btagCombinedSecVertex;
            branches["ttZ_3l_GP_B_charge"].branchVal = lep_charge*(*jets)->at(iJet1).charge;
            branches["ttZ_3l_GP_b_charge"].branchVal = lep_charge*(*jets)->at(iJet2).charge;
            branches["ttZ_3l_GP_top_mass_lep_B"].branchVal = top_mass_lep_B;
            branches["ttZ_3l_GP_W_mass_qq"].branchVal = W_mass_qq;
            branches["ttZ_3l_GP_W_sum_charge_qq"].branchVal = W_sum_charge_qq;
            branches["ttZ_3l_GP_top_mass_b_qq"].branchVal = top_mass_b_qq;
            branches["ttZ_3l_GP_ttbar_4j_MT_mass_ratio_Bbqq"].branchVal = ttbar_4j_MT_mass_ratio;
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

MatchTester_ttZ_3l_GP::~MatchTester_ttZ_3l_GP() {


  //Delete histograms BEFORE closing file  
  delete ratio_top_jet_CSV_le3j;
  delete ratio_top_jet_CSV_eq4j;
  delete ratio_top_jet_CSV_eq5j;
  delete ratio_top_jet_CSV_ge6j;
  delete ratio_W_jet_1_CSV_le3j;
  delete ratio_W_jet_1_CSV_eq4j;
  delete ratio_W_jet_1_CSV_eq5j;
  delete ratio_W_jet_1_CSV_ge6j;
  delete ratio_W_jet_2_CSV_le3j;
  delete ratio_W_jet_2_CSV_eq4j;
  delete ratio_W_jet_2_CSV_eq5j;
  delete ratio_W_jet_2_CSV_ge6j;
  delete ratio_lepTop_jet_charge;
  delete ratio_hadTop_jet_charge;
  delete ratio_top_mass_lep_B_le3j;
  delete ratio_top_mass_lep_B_eq4j;
  delete ratio_top_mass_lep_B_eq5j;
  delete ratio_top_mass_lep_B_ge6j;
  delete ratio_top_MT_met_lep_B_le3j;
  delete ratio_top_MT_met_lep_B_eq4j;
  delete ratio_top_MT_met_lep_B_eq5j;
  delete ratio_top_MT_met_lep_B_ge6j;
  delete ratio_W_mass_qq_le3j;
  delete ratio_W_mass_qq_eq4j;
  delete ratio_W_mass_qq_eq5j;
  delete ratio_W_mass_qq_ge6j;
  delete ratio_W_sum_charge_qq;
  delete ratio_top_mass_b_q_le3j;
  delete ratio_top_mass_b_q_eq4j;
  delete ratio_top_mass_b_q_eq5j;
  delete ratio_top_mass_b_q_ge6j;
  delete ratio_top_mass_b_qq_le3j;
  delete ratio_top_mass_b_qq_eq4j;
  delete ratio_top_mass_b_qq_eq5j;
  delete ratio_top_mass_b_qq_ge6j;
  delete ratio_ttbar_2j_MT_mass_ratio_le3j;
  delete ratio_ttbar_2j_MT_mass_ratio_ge4j;
  delete ratio_ttbar_3j_MT_mass_ratio_le3j;
  delete ratio_ttbar_3j_MT_mass_ratio_eq4j;
  delete ratio_ttbar_3j_MT_mass_ratio_ge5j;
  delete ratio_ttbar_4j_MT_mass_ratio_eq4j;
  delete ratio_ttbar_4j_MT_mass_ratio_eq5j;
  delete ratio_ttbar_4j_MT_mass_ratio_ge6j;
  delete corr_top_mass_b_qq_W_mass_qq_le3j;
  delete corr_top_mass_b_qq_W_mass_qq_eq4j;
  delete corr_top_mass_b_qq_W_mass_qq_eq5j;
  delete corr_top_mass_b_qq_W_mass_qq_ge6j;
  delete corr_top_MT_met_lep_B_top_mass_lep_B_le3j;
  delete corr_top_MT_met_lep_B_top_mass_lep_B_eq4j;
  delete corr_top_MT_met_lep_B_top_mass_lep_B_eq5j;
  delete corr_top_MT_met_lep_B_top_mass_lep_B_ge6j;

//   delete ratio_top_jet_CSV;
//   delete ratio_W_jet_1_CSV;
//   delete ratio_W_jet_2_CSV;
//   delete ratio_lepTop_jet_charge;
//   delete ratio_hadTop_jet_charge;
//   delete ratio_top_mass_lep_B;
//   delete ratio_top_MT_met_lep_B;
//   delete ratio_W_mass_qq;
//   delete ratio_W_sum_charge_qq;
//   delete ratio_top_mass_b_q;
//   delete ratio_top_mass_b_qq;
//   delete ratio_ttbar_MT_mass_ratio_B_b_qq;
//   delete corr_top_MT_met_lep_B_top_mass_lep_B;
//   delete corr_top_mass_b_qq_W_mass_qq;
  weight_file->Close();

}


#endif
