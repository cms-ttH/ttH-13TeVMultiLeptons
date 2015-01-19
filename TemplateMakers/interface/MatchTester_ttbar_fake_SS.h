#ifndef _MatchTester_ttbar_fake_SS_h
#define _MatchTester_ttbar_fake_SS_h

#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/KinematicVariable.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/BranchInfo.h"
//#include <typeinfo>

class MatchTester_ttbar_fake_SS: public KinematicVariable<double> {

public:

  //Store branch values so they are accessible to other classes
  vector<BranchInfo<double>> myVars;

  BNleptonCollection **leptons;
  BNjetCollection **jets;
  BNmetCollection **mets;

  TFile * weight_file;
  TH1 * ratio_W_MT_met_lep;
  TH1 * ratio_top_jet_CSV;
  TH1 * ratio_W_jet_1_CSV;
  TH1 * ratio_W_jet_2_CSV;
  TH1 * ratio_top_jet_charge;
  TH1 * ratio_W_sum_charge_qq;
  TH1 * ratio_W_mass_qq;
  TH1 * ratio_top_mass_lep_B;
  TH1 * ratio_top_MT_met_lep_B;
  TH1 * ratio_top_mass_blep_q;
  TH1 * ratio_top_mass_blep_qq;
  TH1 * corr_top_MT_met_lep_B_top_mass_lep_B;
  TH1 * corr_top_mass_blep_qq_W_mass_qq;

  MatchTester_ttbar_fake_SS(BNleptonCollection **_leptons, BNjetCollection **_jets, BNmetCollection **_mets);
  ~MatchTester_ttbar_fake_SS();
  void evaluate();
};

MatchTester_ttbar_fake_SS::MatchTester_ttbar_fake_SS(BNleptonCollection **_leptons, BNjetCollection **_jets, BNmetCollection **_mets):
  leptons(_leptons), jets(_jets), mets(_mets) {

  //std::cout << "Initializing MatchTester_ttbar_fake_SS" << std::endl;

  //this->resetVal = 0.0; //What does this do?
  this->resetVal = KinematicVariableConstants::FLOAT_INIT; //What does this do?

  branches["Match_ttbar_fake_SS_Bq"] = BranchInfo<double>("Match_ttbar_fake_SS_Bq");
  branches["Match_ttbar_fake_SS_Bqq"] = BranchInfo<double>("Match_ttbar_fake_SS_Bqq");

  branches["Full_match_ttbar_fake_SS_Bq"] = BranchInfo<double>("Full_match_ttbar_fake_SS_Bq");
  branches["Full_match_ttbar_fake_SS_Bqq"] = BranchInfo<double>("Full_match_ttbar_fake_SS_Bqq");

  branches["ttbar_fake_SS_W_MT_met_lep"] = BranchInfo<double>("ttbar_fake_SS_W_MT_met_lep");
  branches["ttbar_fake_SS_B_CSV"] = BranchInfo<double>("ttbar_fake_SS_B_CSV");
  branches["ttbar_fake_SS_q_1_CSV"] = BranchInfo<double>("ttbar_fake_SS_q_1_CSV");
  branches["ttbar_fake_SS_q_2_CSV"] = BranchInfo<double>("ttbar_fake_SS_q_2_CSV");
  branches["ttbar_fake_SS_B_charge"] = BranchInfo<double>("ttbar_fake_SS_B_charge");
  branches["ttbar_fake_SS_W_sum_charge_qq"] = BranchInfo<double>("ttbar_fake_SS_W_sum_charge_qq");
  branches["ttbar_fake_SS_W_mass_qq"] = BranchInfo<double>("ttbar_fake_SS_W_mass_qq");
  branches["ttbar_fake_SS_top_mass_lep_B"] = BranchInfo<double>("ttbar_fake_SS_top_mass_lep_B");
  branches["ttbar_fake_SS_top_MT_met_lep_B"] = BranchInfo<double>("ttbar_fake_SS_top_MT_met_lep_B");
  branches["ttbar_fake_SS_top_mass_blep_q"] = BranchInfo<double>("ttbar_fake_SS_top_mass_blep_q");
  branches["ttbar_fake_SS_top_mass_blep_qq"] = BranchInfo<double>("ttbar_fake_SS_top_mass_blep_qq");

  branches["Match_ttbar_fake_SS_Bq"].branchVal = KinematicVariableConstants::FLOAT_INIT; 
  branches["Match_ttbar_fake_SS_Bqq"].branchVal = KinematicVariableConstants::FLOAT_INIT; 

  branches["Full_match_ttbar_fake_SS_Bq"].branchVal = 0.0; 
  branches["Full_match_ttbar_fake_SS_Bqq"].branchVal = 0.0; 

  branches["ttbar_fake_SS_W_MT_met_lep"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttbar_fake_SS_B_CSV"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttbar_fake_SS_q_1_CSV"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttbar_fake_SS_q_2_CSV"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttbar_fake_SS_B_charge"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttbar_fake_SS_W_sum_charge_qq"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttbar_fake_SS_W_mass_qq"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttbar_fake_SS_top_mass_lep_B"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttbar_fake_SS_top_MT_met_lep_B"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttbar_fake_SS_top_mass_blep_q"].branchVal = KinematicVariableConstants::FLOAT_INIT;
  branches["ttbar_fake_SS_top_mass_blep_qq"].branchVal = KinematicVariableConstants::FLOAT_INIT;

  //std::cout << "Getting weight file" << std::endl;
  string directory = (string(getenv("CMSSW_BASE"))+"/src/ttH-13TeVMultiLeptons/TemplateMakers/data/NOVa/matchbox/").c_str();
  TString weight_file_name = Form("%smatch_ttbar_lj_fake_SS.root", directory.c_str());
  weight_file = TFile::Open(weight_file_name);
  //std::cout << weight_file_name << std::endl;

  //std::cout << "Cloning histograms" << std::endl;
  
  ratio_W_MT_met_lep = (TH1*)weight_file->Get("ratio_W_MT_met_lep")->Clone();
  ratio_top_jet_CSV = (TH1*)weight_file->Get("ratio_top_jet_CSV")->Clone();
  ratio_W_jet_1_CSV = (TH1*)weight_file->Get("ratio_W_jet_1_CSV")->Clone();
  ratio_W_jet_2_CSV = (TH1*)weight_file->Get("ratio_W_jet_2_CSV")->Clone();
  ratio_top_jet_charge = (TH1*)weight_file->Get("ratio_top_jet_charge")->Clone();
  ratio_W_sum_charge_qq = (TH1*)weight_file->Get("ratio_W_sum_charge_qq")->Clone();
  ratio_W_mass_qq = (TH1*)weight_file->Get("ratio_W_mass_qq")->Clone();
  ratio_top_mass_lep_B = (TH1*)weight_file->Get("ratio_top_mass_lep_B")->Clone();
  ratio_top_MT_met_lep_B = (TH1*)weight_file->Get("ratio_top_MT_met_lep_B")->Clone();
  ratio_top_mass_blep_q = (TH1*)weight_file->Get("ratio_top_mass_blep_q")->Clone();
  ratio_top_mass_blep_qq = (TH1*)weight_file->Get("ratio_top_mass_blep_qq")->Clone();
  corr_top_MT_met_lep_B_top_mass_lep_B = (TH1*)weight_file->Get("corr_top_MT_met_lep_B_top_mass_lep_B")->Clone();
  corr_top_mass_blep_qq_W_mass_qq = (TH1*)weight_file->Get("corr_top_mass_blep_qq_W_mass_qq")->Clone();

  //std::cout << "Finished initializing MatchTester_ttbar_fake_SS" << std::endl;
}

void MatchTester_ttbar_fake_SS::evaluate() {
  if (this->evaluatedThisEvent) return;
  evaluatedThisEvent = true;

  //std::cout << "Evaluating MatchTester_ttbar_fake_SS" << std::endl;
  
  if ( (*leptons)->size() != 2) return;
  if ( (*jets)->size() < 2) return;

  //std::cout << "There's at least one lepton" << std::endl;
  
  TLorentzVector lep1_vect;
  TLorentzVector lep2_vect;
  TLorentzVector jet1_vect;
  TLorentzVector jet2_vect;
  TLorentzVector jet3_vect;
  
  TLorentzVector met_vect;
  met_vect.SetPtEtaPhiE((*mets)->at(0).pt, 0.0, (*mets)->at(0).phi, (*mets)->at(0).pt);
  TLorentzVector lep1_vect_trans;
  TLorentzVector jet1_vect_trans;

  TLorentzVector met_lep_vect_trans;
  TLorentzVector qq_vect;
  TLorentzVector lep_B_vect;
  TLorentzVector met_lep_B_vect_trans;
  TLorentzVector blep_q_vect;
  TLorentzVector blep_qq_vect;

  double ratio_Bq = 0.0000000001;
  double ratio_Bqq = 0.0000000001;

  int bin = 0;
  //Necessary for QF events
  int lep_charge = std::max((*leptons)->at(0)->tkCharge, -1);

  //lep1 is the lepton from the top
  //lep2 is the lepton from the b
  //jet1 is the hadronic b
  //jet2 is the first quark from a W
  //jet3 is the second quark from a W
  
  //std::cout << "About to enter jet loop" << std::endl;

  for (unsigned int iLep1 = 0; iLep1 < (*leptons)->size(); iLep1++) {
    for (unsigned int iLep2 = 0; iLep2 < (*leptons)->size(); iLep2++) {
      if (iLep1 == iLep2) continue;
      
      lep1_vect.SetPtEtaPhiE((*leptons)->at(iLep1)->pt, (*leptons)->at(iLep1)->eta, (*leptons)->at(iLep1)->phi, (*leptons)->at(iLep1)->energy);
      lep2_vect.SetPtEtaPhiE((*leptons)->at(iLep2)->pt, (*leptons)->at(iLep2)->eta, (*leptons)->at(iLep2)->phi, (*leptons)->at(iLep2)->energy);
      lep1_vect_trans.SetPtEtaPhiE((*leptons)->at(iLep1)->pt, 0.0, (*leptons)->at(iLep1)->phi, (*leptons)->at(iLep1)->pt);
      
      for (unsigned int iJet1 = 0; iJet1 < (*jets)->size(); iJet1++) {    
        //std::cout << "iJet1 = " << iJet1 << std::endl;    
        jet1_vect.SetPtEtaPhiE((*jets)->at(iJet1).pt, (*jets)->at(iJet1).eta, (*jets)->at(iJet1).phi, (*jets)->at(iJet1).energy);
        jet1_vect_trans.SetPtEtaPhiE((*jets)->at(iJet1).pt, 0.0, (*jets)->at(iJet1).phi, (*jets)->at(iJet1).pt);
        for (unsigned int iJet2 = 0; iJet2 < (*jets)->size(); iJet2++) {    
          if (iJet1 == iJet2) continue;
          //std::cout << "iJet2 = " << iJet2 << std::endl;    
          jet2_vect.SetPtEtaPhiE((*jets)->at(iJet2).pt, (*jets)->at(iJet2).eta, (*jets)->at(iJet2).phi, (*jets)->at(iJet2).energy);
          
          met_lep_vect_trans = met_vect+lep1_vect_trans;
          lep_B_vect = lep1_vect+jet1_vect;
          met_lep_B_vect_trans = met_vect+lep1_vect_trans+jet1_vect_trans;
          blep_q_vect = lep2_vect+jet2_vect;

          //ratio_Bq
          bin = std::max(1, std::min(ratio_W_MT_met_lep->GetNbinsX(), ratio_W_MT_met_lep->GetXaxis()->FindBin(met_lep_vect_trans.M())) );
          ratio_Bq = ratio_W_MT_met_lep->GetBinContent(bin);
          bin = std::max(1, std::min(ratio_top_jet_CSV->GetNbinsX(), ratio_top_jet_CSV->GetXaxis()->FindBin((*jets)->at(iJet1).btagCombinedSecVertex)) );
          ratio_Bq *= ratio_top_jet_CSV->GetBinContent(bin);
          bin = std::max(1, std::min(ratio_W_jet_1_CSV->GetNbinsX(), ratio_W_jet_1_CSV->GetXaxis()->FindBin((*jets)->at(iJet2).btagCombinedSecVertex)) );
          ratio_Bq *= ratio_W_jet_1_CSV->GetBinContent(bin);
          bin = std::max(1, std::min(ratio_top_jet_charge->GetNbinsX(), ratio_top_jet_charge->GetXaxis()->FindBin(lep_charge*(*jets)->at(iJet1).charge)) );
          ratio_Bq *= ratio_top_jet_charge->GetBinContent(bin);
          bin = std::max(1, std::min(ratio_top_mass_lep_B->GetNbinsX(), ratio_top_mass_lep_B->GetXaxis()->FindBin(lep_B_vect.M())) );
          ratio_Bq *= ratio_top_mass_lep_B->GetBinContent(bin);
          bin = std::max(1, std::min(ratio_top_MT_met_lep_B->GetNbinsX(), ratio_top_MT_met_lep_B->GetXaxis()->FindBin(met_lep_B_vect_trans.M())) );
          ratio_Bq *= ratio_top_MT_met_lep_B->GetBinContent(bin);
          bin = std::max(1, std::min(ratio_top_mass_blep_q->GetNbinsX(), ratio_top_mass_blep_q->GetXaxis()->FindBin(blep_q_vect.M())) );
          ratio_Bq *= ratio_top_mass_blep_q->GetBinContent(bin);
          bin = std::max(1, std::min(corr_top_MT_met_lep_B_top_mass_lep_B->GetNbinsX(), corr_top_MT_met_lep_B_top_mass_lep_B->GetXaxis()->FindBin(met_lep_B_vect_trans.M())) );
          ratio_Bq *= corr_top_MT_met_lep_B_top_mass_lep_B->GetBinContent(bin);
          
          if (log(ratio_Bq) > branches["Match_ttbar_fake_SS_Bq"].branchVal) {
            branches["Match_ttbar_fake_SS_Bq"].branchVal = log(ratio_Bq);
            branches["Full_match_ttbar_fake_SS_Bq"].branchVal = (abs((*jets)->at(iJet1).genPartonMotherId) == 6 && abs((*jets)->at(iJet2).genPartonMotherId) == 24);
            branches["ttbar_fake_SS_W_MT_met_lep"].branchVal = met_lep_vect_trans.M();
            branches["ttbar_fake_SS_B_CSV"].branchVal = (*jets)->at(iJet1).btagCombinedSecVertex;
            branches["ttbar_fake_SS_q_1_CSV"].branchVal = (*jets)->at(iJet2).btagCombinedSecVertex;
            branches["ttbar_fake_SS_B_charge"].branchVal = lep_charge*(*jets)->at(iJet1).charge;
            branches["ttbar_fake_SS_top_mass_lep_B"].branchVal = lep_B_vect.M();
            branches["ttbar_fake_SS_top_MT_met_lep_B"].branchVal = met_lep_B_vect_trans.M();
            branches["ttbar_fake_SS_top_mass_blep_q"].branchVal = blep_q_vect.M();
          }
          
          for (unsigned int iJet3 = 0; iJet3 < (*jets)->size(); iJet3++) {
            if (iJet3 == iJet1 || iJet3 == iJet2) continue;
            //std::cout << "iJet2 = " << iJet1 << std::endl;      
            jet3_vect.SetPtEtaPhiE((*jets)->at(iJet3).pt, (*jets)->at(iJet3).eta, (*jets)->at(iJet3).phi, (*jets)->at(iJet3).energy);

            //ratio_Bqq
            qq_vect = jet2_vect+jet3_vect;
            blep_qq_vect = lep2_vect+jet2_vect+jet3_vect;

            ratio_Bqq = ratio_Bq;
            
            bin = std::max(1, std::min(ratio_W_jet_2_CSV->GetNbinsX(), ratio_W_jet_2_CSV->GetXaxis()->FindBin((*jets)->at(iJet3).btagCombinedSecVertex)) );
            ratio_Bqq *= ratio_W_jet_2_CSV->GetBinContent(bin);
            bin = std::max(1, std::min(ratio_W_sum_charge_qq->GetNbinsX(), ratio_W_sum_charge_qq->GetXaxis()->FindBin(lep_charge*((*jets)->at(iJet2).charge+(*jets)->at(iJet3).charge))));
            ratio_Bqq *= ratio_W_sum_charge_qq->GetBinContent(bin);
            bin = std::max(1, std::min(ratio_W_mass_qq->GetNbinsX(), ratio_W_mass_qq->GetXaxis()->FindBin(qq_vect.M())));
            ratio_Bqq *= ratio_W_mass_qq->GetBinContent(bin);
            bin = std::max(1, std::min(ratio_top_mass_blep_q->GetNbinsX(), ratio_top_mass_blep_q->GetXaxis()->FindBin(blep_q_vect.M())) );
            ratio_Bqq *= (1/ratio_top_mass_blep_q->GetBinContent(bin));
            bin = std::max(1, std::min(ratio_top_mass_blep_qq->GetNbinsX(), ratio_top_mass_blep_qq->GetXaxis()->FindBin(blep_qq_vect.M())) );
            ratio_Bqq *= ratio_top_mass_blep_qq->GetBinContent(bin);
            bin = std::max(1, std::min(corr_top_mass_blep_qq_W_mass_qq->GetNbinsX(), corr_top_mass_blep_qq_W_mass_qq->GetXaxis()->FindBin(blep_qq_vect.M())) );
            ratio_Bqq *= corr_top_mass_blep_qq_W_mass_qq->GetBinContent(bin);

            if (log(ratio_Bqq) > branches["Match_ttbar_fake_SS_Bqq"].branchVal) {
              branches["Match_ttbar_fake_SS_Bqq"].branchVal = log(ratio_Bqq);
              branches["Full_match_ttbar_fake_SS_Bqq"].branchVal = (abs((*jets)->at(iJet1).genPartonMotherId) == 6 && abs((*jets)->at(iJet2).genPartonMotherId) == 24 && abs((*jets)->at(iJet3).genPartonMotherId) == 24);
              branches["ttbar_fake_SS_W_MT_met_lep"].branchVal = met_lep_vect_trans.M();
              branches["ttbar_fake_SS_B_CSV"].branchVal = (*jets)->at(iJet1).btagCombinedSecVertex;
              branches["ttbar_fake_SS_q_1_CSV"].branchVal = (*jets)->at(iJet2).btagCombinedSecVertex;
              branches["ttbar_fake_SS_q_2_CSV"].branchVal = (*jets)->at(iJet3).btagCombinedSecVertex;
              branches["ttbar_fake_SS_B_charge"].branchVal = lep_charge*(*jets)->at(iJet1).charge;
              branches["ttbar_fake_SS_W_sum_charge_qq"].branchVal = lep_charge*((*jets)->at(iJet2).charge + (*jets)->at(iJet3).charge);
              branches["ttbar_fake_SS_W_mass_qq"].branchVal = qq_vect.M();
              branches["ttbar_fake_SS_top_mass_lep_B"].branchVal = lep_B_vect.M();
              branches["ttbar_fake_SS_top_MT_met_lep_B"].branchVal = met_lep_B_vect_trans.M();
              branches["ttbar_fake_SS_top_mass_blep_qq"].branchVal = blep_qq_vect.M();
            }
            
          } //end for iJet3
        } //end for iJet2
      } //end for iJet1
    } //end for iLep2
  } //end for iLep1

  //std::cout << "Finished jet loop" << std::endl;

  myVars.clear();

  for (typename map<TString, BranchInfo<double>>::iterator iBranch = branches.begin();
       iBranch != branches.end(); iBranch++) {
    myVars.push_back(iBranch->second);
  }
  
}

MatchTester_ttbar_fake_SS::~MatchTester_ttbar_fake_SS() {

  //Delete histograms BEFORE closing file
  
  delete ratio_W_MT_met_lep;
  delete ratio_top_jet_CSV;
  delete ratio_W_jet_1_CSV;
  delete ratio_W_jet_2_CSV;
  delete ratio_top_jet_charge;
  delete ratio_W_sum_charge_qq;
  delete ratio_W_mass_qq;
  delete ratio_top_mass_lep_B;
  delete ratio_top_MT_met_lep_B;
  delete ratio_top_mass_blep_q;
  delete ratio_top_mass_blep_qq;
  delete corr_top_MT_met_lep_B_top_mass_lep_B;
  delete corr_top_mass_blep_qq_W_mass_qq;
  weight_file->Close();

}


#endif
