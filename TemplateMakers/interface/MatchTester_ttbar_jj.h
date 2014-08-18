#ifndef _MatchTester_ttbar_jj_h
#define _MatchTester_ttbar_jj_h

#include "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BranchInfo.h"
//#include <typeinfo>

class MatchTester_ttbar_jj: public KinematicVariable<double> {

public:

  //Store branch values so they are accessible to other classes
  vector<BranchInfo<double>> myVars;

  BNjetCollection **jets;

  TFile * weight_file;
  TH1 * ratio_top_jet_CSV_ge6j;
  TH1 * ratio_W_jet_1_CSV_ge6j;
  TH1 * ratio_W_jet_2_CSV_ge6j;
  TH1 * ratio_top_jet_charge;
  TH1 * ratio_antiTop_jet_charge;
  TH1 * ratio_W_mass_qq_ge6j;
  TH1 * ratio_W_sum_charge_qq;
  TH1 * ratio_top_mass_b_q_ge6j;
  TH1 * ratio_top_mass_b_qq_ge6j;
  TH1 * corr_top_mass_b_qq_W_mass_qq_ge6j;

  MatchTester_ttbar_jj(BNjetCollection **_jets);
  ~MatchTester_ttbar_jj();
  void evaluate();
};

MatchTester_ttbar_jj::MatchTester_ttbar_jj(BNjetCollection **_jets):
  jets(_jets) {

  //std::cout << "Initializing MatchTester_ttbar_jj" << std::endl;

  //this->resetVal = 0.0; //What does this do?
  this->resetVal = KinematicVariableConstants::FLOAT_INIT; //What does this do?

  branches["Match_ttbar_jj_Bqq_bq"] = BranchInfo<double>("Match_ttbar_jj_Bqq_bq");
  branches["Match_ttbar_jj_Bq_bqq"] = BranchInfo<double>("Match_ttbar_jj_Bq_bqq");
  branches["Match_ttbar_jj_Bqq_bqq"] = BranchInfo<double>("Match_ttbar_jj_Bqq_bqq");

  branches["Full_match_ttbar_jj_Bqq_bq"] = BranchInfo<double>("Full_match_ttbar_jj_Bqq_bq");
  branches["Full_match_ttbar_jj_Bq_bqq"] = BranchInfo<double>("Full_match_ttbar_jj_Bq_bqq");
  branches["Full_match_ttbar_jj_Bqq_bqq"] = BranchInfo<double>("Full_match_ttbar_jj_Bqq_bqq");

  branches["ttbar_jj_B_CSV"] = BranchInfo<double>("ttbar_jj_B_CSV");
  branches["ttbar_jj_b_CSV"] = BranchInfo<double>("ttbar_jj_b_CSV");
  branches["ttbar_jj_q_1_CSV"] = BranchInfo<double>("ttbar_jj_q_1_CSV");
  branches["ttbar_jj_q_2_CSV"] = BranchInfo<double>("ttbar_jj_q_2_CSV");
  branches["ttbar_jj_q_3_CSV"] = BranchInfo<double>("ttbar_jj_q_3_CSV");
  branches["ttbar_jj_q_4_CSV"] = BranchInfo<double>("ttbar_jj_q_4_CSV");
  branches["ttbar_jj_B_charge"] = BranchInfo<double>("ttbar_jj_B_charge");
  branches["ttbar_jj_b_charge"] = BranchInfo<double>("ttbar_jj_b_charge");
  branches["ttbar_jj_Wplus_sum_charge_qq"] = BranchInfo<double>("ttbar_jj_Wplus_sum_charge_qq");
  branches["ttbar_jj_Wminus_sum_charge_qq"] = BranchInfo<double>("ttbar_jj_Wminus_sum_charge_qq");
  branches["ttbar_jj_Wplus_mass_qq"] = BranchInfo<double>("ttbar_jj_Wplus_mass_qq");
  branches["ttbar_jj_Wminus_mass_qq"] = BranchInfo<double>("ttbar_jj_Wminus_mass_qq");
  branches["ttbar_jj_top_mass_b_q"] = BranchInfo<double>("ttbar_jj_top_mass_b_q");
  branches["ttbar_jj_antiTop_mass_b_q"] = BranchInfo<double>("ttbar_jj_antiTop_mass_b_q");
  branches["ttbar_jj_top_mass_b_qq"] = BranchInfo<double>("ttbar_jj_top_mass_b_qq");
  branches["ttbar_jj_antiTop_mass_b_qq"] = BranchInfo<double>("ttbar_jj_antiTop_mass_b_qq");

  branches["Match_ttbar_jj_Bqq_bq"].branchVal = KinematicVariableConstants::FLOAT_INIT; 
  branches["Match_ttbar_jj_Bq_bqq"].branchVal = KinematicVariableConstants::FLOAT_INIT; 
  branches["Match_ttbar_jj_Bqq_bqq"].branchVal = KinematicVariableConstants::FLOAT_INIT; 

  branches["Full_match_ttbar_jj_Bqq_bq"].branchVal = 0.0; 
  branches["Full_match_ttbar_jj_Bq_bqq"].branchVal = 0.0; 
  branches["Full_match_ttbar_jj_Bqq_bqq"].branchVal = 0.0; 

  branches["ttbar_jj_B_CSV"].branchVal = KinematicVariableConstants::FLOAT_INIT; 
  branches["ttbar_jj_b_CSV"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttbar_jj_q_1_CSV"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttbar_jj_q_2_CSV"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttbar_jj_q_3_CSV"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttbar_jj_q_4_CSV"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttbar_jj_B_charge"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttbar_jj_b_charge"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttbar_jj_Wplus_sum_charge_qq"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttbar_jj_Wminus_sum_charge_qq"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttbar_jj_Wplus_mass_qq"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttbar_jj_Wminus_mass_qq"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttbar_jj_top_mass_b_q"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttbar_jj_antiTop_mass_b_q"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttbar_jj_top_mass_b_qq"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttbar_jj_antiTop_mass_b_qq"].branchVal = KinematicVariableConstants::FLOAT_INIT;

  //std::cout << "Getting weight file" << std::endl;
  string directory = (string(getenv("CMSSW_BASE"))+"/src/ttHMultileptonAnalysis/TemplateMakers/data/NOVa/matchbox/").c_str();
  //TString weight_file_name = Form("%smatch_ttbarZ_3l.root", directory.c_str());
  //TString weight_file_name = Form("%smatch_ttbar_lj.root", directory.c_str());
  TString weight_file_name = Form("%smatch_ttbar_lj_by_nJet.root", directory.c_str());
  weight_file = TFile::Open(weight_file_name);
  //std::cout << weight_file_name << std::endl;

  //std::cout << "Cloning histograms" << std::endl;  
  ratio_top_jet_CSV_ge6j = (TH1*)weight_file->Get("ratio_top_jet_CSV_ge6j")->Clone();
  ratio_W_jet_1_CSV_ge6j = (TH1*)weight_file->Get("ratio_W_jet_1_CSV_ge6j")->Clone();
  ratio_W_jet_2_CSV_ge6j = (TH1*)weight_file->Get("ratio_W_jet_2_CSV_ge6j")->Clone();
  ratio_top_jet_charge = (TH1*)weight_file->Get("ratio_lepTop_jet_charge")->Clone();
  ratio_antiTop_jet_charge = (TH1*)weight_file->Get("ratio_hadTop_jet_charge")->Clone();
  ratio_W_mass_qq_ge6j = (TH1*)weight_file->Get("ratio_W_mass_qq_ge6j")->Clone();
  ratio_W_sum_charge_qq = (TH1*)weight_file->Get("ratio_W_sum_charge_qq")->Clone();
  ratio_top_mass_b_q_ge6j = (TH1*)weight_file->Get("ratio_top_mass_b_q_ge6j")->Clone();
  ratio_top_mass_b_qq_ge6j = (TH1*)weight_file->Get("ratio_top_mass_b_qq_ge6j")->Clone();
  corr_top_mass_b_qq_W_mass_qq_ge6j = (TH1*)weight_file->Get("corr_top_mass_b_qq_W_mass_qq_ge6j")->Clone();

  //std::cout << "Finished initializing MatchTester_ttbar_jj" << std::endl;
}

void MatchTester_ttbar_jj::evaluate() {
  //std::cout << "this->evaluatedThisEvent is " << this->evaluatedThisEvent << std::endl;
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  //std::cout << "Evaluating MatchTester_ttbar_jj with " << (*leptons)->size() << " and " << (*jets)->size() << " jets" << std::endl;
  
  if ( (*jets)->size() < 5) return;

  TLorentzVector jet1_vect;
  TLorentzVector jet2_vect;
  TLorentzVector jet3_vect;
  TLorentzVector jet4_vect;
  TLorentzVector jet5_vect;
  TLorentzVector jet6_vect;

  TLorentzVector B_q_vect;
  TLorentzVector b_q_vect;
  TLorentzVector qq_plus_vect;
  TLorentzVector qq_minus_vect;
  TLorentzVector B_qq_vect;
  TLorentzVector b_qq_vect;

  double ratio_Bbqqq = 0.0000000001;
  double ratio_Bqq_bq = 0.0000000001;
  double ratio_Bq_bqq = 0.0000000001;
  double ratio_Bqq_bqq = 0.0000000001;

  int bin = 0;

  //B is the b from the top
  //b is the b from the anti-top
  //q is a jet from the Wplus or Wminus

  //jet1 is the B
  //jet2 is the b
  //jet3 is the first q from the Wplus
  //jet4 is the first q from the Wminus
  //jet5 is the second q from the Wplus or Wminus
  //jet6 is the second q from the Wminus or Wplus
  
  //std::cout << "About to enter jet loop" << std::endl;
  
  for (unsigned int iJet1 = 0; iJet1 < (*jets)->size(); iJet1++) {    
    //std::cout << "iJet1 = " << iJet1 << std::endl;    
    jet1_vect.SetPtEtaPhiE((*jets)->at(iJet1).pt, (*jets)->at(iJet1).eta, (*jets)->at(iJet1).phi, (*jets)->at(iJet1).energy);

  for (unsigned int iJet2 = 0; iJet2 < (*jets)->size(); iJet2++) {
    if (iJet2 == iJet1) continue;
    //std::cout << "iJet2 = " << iJet2 << std::endl;      
    jet2_vect.SetPtEtaPhiE((*jets)->at(iJet2).pt, (*jets)->at(iJet2).eta, (*jets)->at(iJet2).phi, (*jets)->at(iJet2).energy);

  for (unsigned int iJet3 = 0; iJet3 < (*jets)->size(); iJet3++) {
    if (iJet3 == iJet1 || iJet3 == iJet2) continue;
    //std::cout << "iJet3 = " << iJet3 << std::endl;      
    jet3_vect.SetPtEtaPhiE((*jets)->at(iJet3).pt, (*jets)->at(iJet3).eta, (*jets)->at(iJet3).phi, (*jets)->at(iJet3).energy);

  for (unsigned int iJet4 = 0; iJet4 < (*jets)->size(); iJet4++) {
    if (iJet4 == iJet1 || iJet4 == iJet2 || iJet4 == iJet3) continue;
    //std::cout << "iJet4 = " << iJet4 << std::endl;      
    jet4_vect.SetPtEtaPhiE((*jets)->at(iJet4).pt, (*jets)->at(iJet4).eta, (*jets)->at(iJet4).phi, (*jets)->at(iJet4).energy);

  for (unsigned int iJet5 = 0; iJet5 < (*jets)->size(); iJet5++) {
    if (iJet5 == iJet1 || iJet5 == iJet2 || iJet5 == iJet3 || iJet5 == iJet4) continue;
    //std::cout << "iJet5 = " << iJet5 << std::endl;      
    jet5_vect.SetPtEtaPhiE((*jets)->at(iJet5).pt, (*jets)->at(iJet5).eta, (*jets)->at(iJet5).phi, (*jets)->at(iJet5).energy);

    //ratio_Bbqqq (base ratio)
    bin = std::max(1, std::min(ratio_top_jet_CSV_ge6j->GetNbinsX(), ratio_top_jet_CSV_ge6j->GetXaxis()->FindBin((*jets)->at(iJet1).btagCombinedSecVertex)) );
    ratio_Bbqqq = ratio_top_jet_CSV_ge6j->GetBinContent(bin);
    bin = std::max(1, std::min(ratio_top_jet_CSV_ge6j->GetNbinsX(), ratio_top_jet_CSV_ge6j->GetXaxis()->FindBin((*jets)->at(iJet2).btagCombinedSecVertex)) );
    ratio_Bbqqq *= ratio_top_jet_CSV_ge6j->GetBinContent(bin);
    bin = std::max(1, std::min(ratio_W_jet_1_CSV_ge6j->GetNbinsX(), ratio_W_jet_1_CSV_ge6j->GetXaxis()->FindBin((*jets)->at(iJet3).btagCombinedSecVertex)) );
    ratio_Bbqqq *= ratio_W_jet_1_CSV_ge6j->GetBinContent(bin);
    bin = std::max(1, std::min(ratio_W_jet_1_CSV_ge6j->GetNbinsX(), ratio_W_jet_1_CSV_ge6j->GetXaxis()->FindBin((*jets)->at(iJet4).btagCombinedSecVertex)) );
    ratio_Bbqqq *= ratio_W_jet_1_CSV_ge6j->GetBinContent(bin);
    bin = std::max(1, std::min(ratio_W_jet_2_CSV_ge6j->GetNbinsX(), ratio_W_jet_2_CSV_ge6j->GetXaxis()->FindBin((*jets)->at(iJet5).btagCombinedSecVertex)) );
    ratio_Bbqqq *= ratio_W_jet_2_CSV_ge6j->GetBinContent(bin);
    bin = std::max(1, std::min(ratio_top_jet_charge->GetNbinsX(), ratio_top_jet_charge->GetXaxis()->FindBin((*jets)->at(iJet1).charge-0.035)) );
    ratio_Bbqqq *= ratio_top_jet_charge->GetBinContent(bin);
    bin = std::max(1, std::min(ratio_antiTop_jet_charge->GetNbinsX(), ratio_antiTop_jet_charge->GetXaxis()->FindBin((*jets)->at(iJet2).charge-0.035)) );
    ratio_Bbqqq *= ratio_antiTop_jet_charge->GetBinContent(bin);

    //ratio_Bqq_bq
    qq_plus_vect = jet3_vect+jet5_vect;
    B_qq_vect = jet1_vect+qq_plus_vect;
    b_q_vect = jet2_vect+jet4_vect;

    ratio_Bqq_bq = ratio_Bbqqq;
    bin = std::max(1, std::min(ratio_W_sum_charge_qq->GetNbinsX(), ratio_W_sum_charge_qq->GetXaxis()->FindBin(-1.0*((*jets)->at(iJet3).charge+(*jets)->at(iJet5).charge-0.07))) );
    ratio_Bqq_bq *= ratio_W_sum_charge_qq->GetBinContent(bin);
    bin = std::max(1, std::min(ratio_W_mass_qq_ge6j->GetNbinsX(), ratio_W_mass_qq_ge6j->GetXaxis()->FindBin(qq_plus_vect.M())) );
    ratio_Bqq_bq *= ratio_W_mass_qq_ge6j->GetBinContent(bin);
    bin = std::max(1, std::min(ratio_top_mass_b_qq_ge6j->GetNbinsX(), ratio_top_mass_b_qq_ge6j->GetXaxis()->FindBin(B_qq_vect.M())) );
    ratio_Bqq_bq *= ratio_top_mass_b_qq_ge6j->GetBinContent(bin);
    bin = std::max(1, std::min(ratio_top_mass_b_q_ge6j->GetNbinsX(), ratio_top_mass_b_q_ge6j->GetXaxis()->FindBin(b_q_vect.M())) );
    ratio_Bqq_bq *= ratio_top_mass_b_q_ge6j->GetBinContent(bin);
    bin = std::max(1, std::min(corr_top_mass_b_qq_W_mass_qq_ge6j->GetNbinsX(), corr_top_mass_b_qq_W_mass_qq_ge6j->GetXaxis()->FindBin(B_qq_vect.M())) );
    ratio_Bqq_bq *= corr_top_mass_b_qq_W_mass_qq_ge6j->GetBinContent(bin);

    if (log(ratio_Bqq_bq) > branches["Match_ttbar_jj_Bqq_bq"].branchVal) {
      
      branches["Match_ttbar_jj_Bqq_bq"].branchVal = log(ratio_Bqq_bq);

      branches["Full_match_ttbar_jj_Bqq_bq"].branchVal = ((*jets)->at(iJet1).genPartonMotherId == 6 &&
                                                          (*jets)->at(iJet2).genPartonMotherId == -6 &&
                                                          (*jets)->at(iJet3).genPartonMotherId == 24 &&
                                                          (*jets)->at(iJet4).genPartonMotherId == -24 &&
                                                          (*jets)->at(iJet5).genPartonMotherId == 24);

      branches["ttbar_jj_B_CSV"].branchVal = (*jets)->at(iJet1).btagCombinedSecVertex; 
      branches["ttbar_jj_b_CSV"].branchVal = (*jets)->at(iJet2).btagCombinedSecVertex;
      branches["ttbar_jj_q_1_CSV"].branchVal = (*jets)->at(iJet3).btagCombinedSecVertex;
      branches["ttbar_jj_q_2_CSV"].branchVal = (*jets)->at(iJet4).btagCombinedSecVertex;
      branches["ttbar_jj_q_3_CSV"].branchVal = (*jets)->at(iJet5).btagCombinedSecVertex;
      branches["ttbar_jj_B_charge"].branchVal = (*jets)->at(iJet1).charge;
      branches["ttbar_jj_b_charge"].branchVal = (*jets)->at(iJet2).charge;
      branches["ttbar_jj_Wplus_sum_charge_qq"].branchVal = (*jets)->at(iJet3).charge+(*jets)->at(iJet5).charge;
      branches["ttbar_jj_Wplus_mass_qq"].branchVal = qq_plus_vect.M();
      branches["ttbar_jj_top_mass_b_qq"].branchVal = B_qq_vect.M();
      branches["ttbar_jj_antiTop_mass_b_q"].branchVal = b_q_vect.M();
    }
    
    //ratio_Bq_bqq
    qq_minus_vect = jet4_vect+jet5_vect;
    b_qq_vect = jet2_vect+qq_minus_vect;
    B_q_vect = jet1_vect+jet3_vect;

    ratio_Bq_bqq = ratio_Bbqqq;
    bin = std::max(1, std::min(ratio_W_sum_charge_qq->GetNbinsX(), ratio_W_sum_charge_qq->GetXaxis()->FindBin((*jets)->at(iJet4).charge+(*jets)->at(iJet5).charge-0.07)) );
    ratio_Bq_bqq *= ratio_W_sum_charge_qq->GetBinContent(bin);
    bin = std::max(1, std::min(ratio_W_mass_qq_ge6j->GetNbinsX(), ratio_W_mass_qq_ge6j->GetXaxis()->FindBin(qq_minus_vect.M())) );
    ratio_Bq_bqq *= ratio_W_mass_qq_ge6j->GetBinContent(bin);
    bin = std::max(1, std::min(ratio_top_mass_b_qq_ge6j->GetNbinsX(), ratio_top_mass_b_qq_ge6j->GetXaxis()->FindBin(b_qq_vect.M())) );
    ratio_Bq_bqq *= ratio_top_mass_b_qq_ge6j->GetBinContent(bin);
    bin = std::max(1, std::min(ratio_top_mass_b_q_ge6j->GetNbinsX(), ratio_top_mass_b_q_ge6j->GetXaxis()->FindBin(B_q_vect.M())) );
    ratio_Bq_bqq *= ratio_top_mass_b_q_ge6j->GetBinContent(bin);
    bin = std::max(1, std::min(corr_top_mass_b_qq_W_mass_qq_ge6j->GetNbinsX(), corr_top_mass_b_qq_W_mass_qq_ge6j->GetXaxis()->FindBin(b_qq_vect.M())) );
    ratio_Bq_bqq *= corr_top_mass_b_qq_W_mass_qq_ge6j->GetBinContent(bin);

    if (log(ratio_Bq_bqq) > branches["Match_ttbar_jj_Bq_bqq"].branchVal) {
      
      branches["Match_ttbar_jj_Bq_bqq"].branchVal = log(ratio_Bq_bqq);

      branches["Full_match_ttbar_jj_Bq_bqq"].branchVal = ((*jets)->at(iJet1).genPartonMotherId == 6 &&
                                                          (*jets)->at(iJet2).genPartonMotherId == -6 &&
                                                          (*jets)->at(iJet3).genPartonMotherId == 24 &&
                                                          (*jets)->at(iJet4).genPartonMotherId == -24 &&
                                                          (*jets)->at(iJet5).genPartonMotherId == -24);

      //Use values from the better incomplete match
      if (log(ratio_Bq_bqq) > branches["Match_ttbar_jj_Bqq_bq"].branchVal) {
        branches["ttbar_jj_B_CSV"].branchVal = (*jets)->at(iJet1).btagCombinedSecVertex; 
        branches["ttbar_jj_b_CSV"].branchVal = (*jets)->at(iJet2).btagCombinedSecVertex;
        branches["ttbar_jj_q_1_CSV"].branchVal = (*jets)->at(iJet3).btagCombinedSecVertex;
        branches["ttbar_jj_q_2_CSV"].branchVal = (*jets)->at(iJet4).btagCombinedSecVertex;
        branches["ttbar_jj_q_3_CSV"].branchVal = (*jets)->at(iJet5).btagCombinedSecVertex;
        branches["ttbar_jj_B_charge"].branchVal = (*jets)->at(iJet1).charge;
        branches["ttbar_jj_b_charge"].branchVal = (*jets)->at(iJet2).charge;
      }
      branches["ttbar_jj_Wminus_sum_charge_qq"].branchVal = (*jets)->at(iJet4).charge+(*jets)->at(iJet5).charge;
      branches["ttbar_jj_Wminus_mass_qq"].branchVal = qq_minus_vect.M();
      branches["ttbar_jj_top_mass_b_qq"].branchVal = b_qq_vect.M();
      branches["ttbar_jj_antiTop_mass_b_q"].branchVal = B_q_vect.M();
    }
    

    for (unsigned int iJet6 = 0; iJet6 < (*jets)->size(); iJet6++) {
      if (iJet6 == iJet1 || iJet6 == iJet2 || iJet6 == iJet3 || iJet6 == iJet4 || iJet6 == iJet5) continue;
      //std::cout << "iJet6 = " << iJet6 << std::endl;      
      jet6_vect.SetPtEtaPhiE((*jets)->at(iJet6).pt, (*jets)->at(iJet6).eta, (*jets)->at(iJet6).phi, (*jets)->at(iJet6).energy);


      //ratio_Bqq_bqq
      qq_plus_vect = jet3_vect+jet5_vect;
      qq_minus_vect = jet4_vect+jet6_vect;
      B_qq_vect = jet1_vect+qq_plus_vect;
      b_qq_vect = jet2_vect+qq_minus_vect;

      ratio_Bqq_bqq = ratio_Bqq_bq;
      bin = std::max(1, std::min(ratio_top_mass_b_q_ge6j->GetNbinsX(), ratio_top_mass_b_q_ge6j->GetXaxis()->FindBin(b_q_vect.M())) );
      ratio_Bqq_bqq *= 1.0/(ratio_top_mass_b_q_ge6j->GetBinContent(bin));
      bin = std::max(1, std::min(ratio_W_sum_charge_qq->GetNbinsX(), ratio_W_sum_charge_qq->GetXaxis()->FindBin((*jets)->at(iJet4).charge+(*jets)->at(iJet6).charge-0.07)) );
      ratio_Bqq_bqq *= ratio_W_sum_charge_qq->GetBinContent(bin);
      bin = std::max(1, std::min(ratio_W_mass_qq_ge6j->GetNbinsX(), ratio_W_mass_qq_ge6j->GetXaxis()->FindBin(qq_minus_vect.M())) );
      ratio_Bqq_bqq *= ratio_W_mass_qq_ge6j->GetBinContent(bin);
      bin = std::max(1, std::min(ratio_top_mass_b_qq_ge6j->GetNbinsX(), ratio_top_mass_b_qq_ge6j->GetXaxis()->FindBin(b_qq_vect.M())) );
      ratio_Bqq_bqq *= ratio_top_mass_b_qq_ge6j->GetBinContent(bin);
      bin = std::max(1, std::min(corr_top_mass_b_qq_W_mass_qq_ge6j->GetNbinsX(), corr_top_mass_b_qq_W_mass_qq_ge6j->GetXaxis()->FindBin(b_qq_vect.M())) );
      ratio_Bqq_bqq *= corr_top_mass_b_qq_W_mass_qq_ge6j->GetBinContent(bin);

    
    if (log(ratio_Bqq_bqq) > branches["Match_ttbar_jj_Bqq_bqq"].branchVal) {
      
      branches["Match_ttbar_jj_Bqq_bqq"].branchVal = log(ratio_Bqq_bqq);

      branches["Full_match_ttbar_jj_Bqq_bqq"].branchVal = ((*jets)->at(iJet1).genPartonMotherId == 6 &&
                                                           (*jets)->at(iJet2).genPartonMotherId == -6 &&
                                                           (*jets)->at(iJet3).genPartonMotherId == 24 &&
                                                           (*jets)->at(iJet4).genPartonMotherId == -24 &&
                                                           (*jets)->at(iJet5).genPartonMotherId == 24 &&
                                                           (*jets)->at(iJet6).genPartonMotherId == -24);
      
      branches["ttbar_jj_B_CSV"].branchVal = (*jets)->at(iJet1).btagCombinedSecVertex; 
      branches["ttbar_jj_b_CSV"].branchVal = (*jets)->at(iJet2).btagCombinedSecVertex;
      branches["ttbar_jj_q_1_CSV"].branchVal = (*jets)->at(iJet3).btagCombinedSecVertex;
      branches["ttbar_jj_q_2_CSV"].branchVal = (*jets)->at(iJet4).btagCombinedSecVertex;
      branches["ttbar_jj_q_3_CSV"].branchVal = (*jets)->at(iJet5).btagCombinedSecVertex;
      branches["ttbar_jj_q_4_CSV"].branchVal = (*jets)->at(iJet6).btagCombinedSecVertex;
      branches["ttbar_jj_B_charge"].branchVal = (*jets)->at(iJet1).charge;
      branches["ttbar_jj_b_charge"].branchVal = (*jets)->at(iJet2).charge;
      branches["ttbar_jj_Wplus_sum_charge_qq"].branchVal = (*jets)->at(iJet3).charge+(*jets)->at(iJet5).charge;
      branches["ttbar_jj_Wminus_sum_charge_qq"].branchVal = (*jets)->at(iJet4).charge+(*jets)->at(iJet6).charge;
      branches["ttbar_jj_Wplus_mass_qq"].branchVal = qq_plus_vect.M();
      branches["ttbar_jj_Wminus_mass_qq"].branchVal = qq_minus_vect.M();
      branches["ttbar_jj_top_mass_b_qq"].branchVal = B_qq_vect.M();
      branches["ttbar_jj_antiTop_mass_b_qq"].branchVal = b_qq_vect.M();
    }

    } // end iJet6
  } // end iJet5
  } // end iJet4
  } // end iJet3
  } // end iJet2
  } // end iJet1
    
  //std::cout << "Finished jet loop" << std::endl;

  myVars.clear();

  for (typename map<TString, BranchInfo<double>>::iterator iBranch = branches.begin();
       iBranch != branches.end(); iBranch++) {
    myVars.push_back(iBranch->second);
  }
  
}

MatchTester_ttbar_jj::~MatchTester_ttbar_jj() {


  //Delete histograms BEFORE closing file  
  delete ratio_top_jet_CSV_ge6j;
  delete ratio_W_jet_1_CSV_ge6j;
  delete ratio_W_jet_2_CSV_ge6j;
  delete ratio_top_jet_charge;
  delete ratio_antiTop_jet_charge;
  delete ratio_W_sum_charge_qq;
  delete ratio_W_mass_qq_ge6j;
  delete ratio_top_mass_b_q_ge6j;
  delete ratio_top_mass_b_qq_ge6j;
  delete corr_top_mass_b_qq_W_mass_qq_ge6j;

  weight_file->Close();

}


#endif
