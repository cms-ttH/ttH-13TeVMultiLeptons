#ifndef _eventReconstructor_h
#define _eventReconstructor_h

#include <vector>
#include "TObject.h"
#include <iostream>
#include "TSystem.h"
#include <vector>
#include "TH1.h"
#include "TChain.h"
#include <string>
#include <algorithm>
#include "TString.h"
#include "TH1D.h"
#include "TFile.h"
#include <cmath>
#include "TLorentzVector.h"
#include "TMVA/Config.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#include "treeTools.h"

class eventReconstructor
{
 private:
  TMVA::Reader* TMVAReader_;
  TMVA::Reader* TMVAReader_bTight_;
  TMVA::Reader* TMVAReader_bLoose_;

  Float_t bJet_fromLepTop_csv_var;
  Float_t bJet_fromHadTop_csv_var;
  Float_t hadTop_pt_var;
  Float_t w_fromHadTop_mass_var;
  Float_t hadTop_mass_var;
  Float_t lep_fromHiggs_pT_var;
  Float_t lep_fromTop_pT_var;
  Float_t lep_pt_ratio_var;
  Float_t dr_lepFromHiggs_bFromHadTop_var;
  Float_t dr_lepFromTop_bFromLepTop_var;
  Float_t dr_lepFromTop_bFromHadTop_var;
  Float_t dr_lepFromHiggs_bFromLepTop_var;
  Float_t q1_fromHadTop_csv_var;
  Float_t q2_fromHadTop_csv_var;
  const char* env_p = std::getenv("CMSSW_BASE");

  TMVA::Reader* bookMVA(std::string weights_file_str)
  {
    TMVA::Reader* TMVAReader_internal_ = new TMVA::Reader( "!Color:!Silent" );
    
    TMVAReader_internal_->AddVariable( "b_from_leptop_bdt.csv", &bJet_fromLepTop_csv_var );
    TMVAReader_internal_->AddVariable( "b_from_hadtop_bdt.csv", &bJet_fromHadTop_csv_var );
    TMVAReader_internal_->AddVariable( "hadTop_tlv_bdt.Pt()", &hadTop_pt_var );
    TMVAReader_internal_->AddVariable( "w_from_hadtop_tlv_bdt.M()", &w_fromHadTop_mass_var );
    TMVAReader_internal_->AddVariable( "hadTop_tlv_bdt.M()", &hadTop_mass_var );
    //TMVAReader_internal_->AddVariable( "lep_from_higgs_bdt.obj.pt()", &lep_fromHiggs_pT_var );
    //TMVAReader_internal_->AddVariable( "lep_from_leptop_bdt.obj.pt()", &lep_fromTop_pT_var );
    //TMVAReader_internal_->AddVariable( "(lep_from_leptop_bdt.obj.pt()-lep_from_higgs_bdt.obj.pt())/(lep_from_leptop_bdt.obj.pt()+lep_from_higgs_bdt.obj.pt())", &lep_pt_ratio_var );
    TMVAReader_internal_->AddVariable( "lep_from_leptop_bdt.obj.pt()/lep_from_higgs_bdt.obj.pt()", &lep_pt_ratio_var );//PORTED FROM: test/reco_bdt/bdt_fw_integration
    
    //TMVAReader_internal_->AddVariable( "q1_from_hadtop_bdt.csv", &q1_fromHadTop_csv_var );
    //TMVAReader_internal_->AddVariable( "q2_from_hadtop_bdt.csv", &q2_fromHadTop_csv_var );

    TMVAReader_internal_->AddVariable( "dr_lepFromTop_bFromLepTop", &dr_lepFromTop_bFromLepTop_var );
    TMVAReader_internal_->AddVariable( "dr_lepFromTop_bFromHadTop", &dr_lepFromTop_bFromHadTop_var );
    TMVAReader_internal_->AddVariable( "dr_lepFromHiggs_bFromLepTop", &dr_lepFromHiggs_bFromLepTop_var );

    std::string weight_file = env_p;
    weight_file += weights_file_str;
    TMVAReader_internal_->BookMVA("BDTG method", weight_file);

    return TMVAReader_internal_;
  }
  
  vector<double> best_combo_vec_intree;
  vector<double> all_combo_vec_intree;
  vector<ttH::Jet> *unmatched_jets_bdt_intree=0;
  vector<ttH::Jet> *matched_jets_bdt_intree=0;
  vector<ttH::Jet> *btight_jets_intree=0;
  vector<ttH::Jet> *bloose_jets_intree=0;
  ttH::Lepton *lep_from_higgs_bdt_intree=0;  
  ttH::Lepton *lep_from_leptop_bdt_intree=0;
  ttH::Jet *b_from_leptop_bdt_intree=0;
  
  TLorentzVector w_from_hadtop_tlv_bdt_intree;
  TLorentzVector lepTop_tlv_bdt_intree;
  
  int null_jets_added_bdt_intree;

  int lepton_matching_intree;
  int b_from_hadtop_matching_intree;
  int b_from_leptop_matching_intree;
  int W_from_hadtop_matching_intree;

 public:
  eventReconstructor(void){
    /* TMVAReader_bTight_ = bookMVA("/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/classifiers/weights/TMVAClassification_BDTG_v1p5_bTight.weights.xml"); */
    /* TMVAReader_bLoose_ = bookMVA("/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/classifiers/weights/TMVAClassification_BDTG_v1p5_bLoose.weights.xml"); */
    //TMVAReader_bTight_ = bookMVA("/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/weights/TMVAClassification_BDTG.weights_factorized_bTight.xml");
    //TMVAReader_bLoose_ = bookMVA("/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/weights/TMVAClassification_BDTG.weights_factorized_bLoose.xml");
    TMVAReader_bTight_ = bookMVA("/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/jan25_weights/TMVAClassification_btight_BDTG.weights.xml");
    TMVAReader_bLoose_ = bookMVA("/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/jan25_weights/TMVAClassification_bloose_BDTG.weights.xml");

    //8020 genfilter samples
    /* TMVAReader_bTight_ = bookMVA("/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/weights/TMVAClassification_BDTG.weights_factorized_genFilter_bTight.xml"); */
    /* TMVAReader_bLoose_ = bookMVA("/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/weights/TMVAClassification_BDTG.weights_factorized_genFilter_bLoose.xml"); */

    //Feb11 ttW signal test
    //TMVAReader_bTight_ = bookMVA("/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/feb10_weights_recoBdt_weights_factorized/TMVAClassification_btight_BDTG.weights.xml");
    //TMVAReader_bLoose_ = bookMVA("/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/feb10_weights_recoBdt_weights_factorized/TMVAClassification_bloose_BDTG.weights.xml");
    
    //Feb14 only hadtop objs test
    //TMVAReader_bTight_ = bookMVA("/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/feb14_weights_recoBdt_weights_factorized/TMVAClassification_inclusive_BDTG.weights.xml");
    //TMVAReader_bLoose_ = bookMVA("/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/feb14_weights_recoBdt_weights_factorized/TMVAClassification_inclusive_BDTG.weights.xml");
    
  } // default constructor


  vector<int> *match_results_bdt_intree=0;
  double reco_score_intree;
  TLorentzVector hadTop_tlv_bdt_intree;
  ttH::Jet *b_from_hadtop_bdt_intree=0;
  ttH::Jet *q1_from_hadtop_bdt_intree=0;
  ttH::Jet *q2_from_hadtop_bdt_intree=0;
  
  double dr_lepFromHiggs_bFromHadTop_intree;
  double dr_lepFromTop_bFromLepTop_intree;
  double dr_lepFromTop_bFromHadTop_intree;
  double dr_lepFromHiggs_bFromLepTop_intree;

  void clear(void)
  {
    lepton_matching_intree = -1;
    b_from_hadtop_matching_intree = -1;
    b_from_leptop_matching_intree = -1;
    W_from_hadtop_matching_intree = -1;
   
    btight_jets_intree->clear();
    bloose_jets_intree->clear();

    reco_score_intree = -2.;
    best_combo_vec_intree.clear();
    all_combo_vec_intree.clear();
    lep_from_higgs_bdt_intree->clear();  
    lep_from_leptop_bdt_intree->clear();
    b_from_leptop_bdt_intree->clear();
    b_from_hadtop_bdt_intree->clear();
    q1_from_hadtop_bdt_intree->clear();
    q2_from_hadtop_bdt_intree->clear();
    w_from_hadtop_tlv_bdt_intree.SetPxPyPzE(0.,0.,0.,0.);
    hadTop_tlv_bdt_intree.SetPxPyPzE(0.,0.,0.,0.);
    lepTop_tlv_bdt_intree.SetPxPyPzE(0.,0.,0.,0.);

    dr_lepFromHiggs_bFromHadTop_intree = -99.;
    dr_lepFromTop_bFromLepTop_intree = -99.;
    dr_lepFromTop_bFromHadTop_intree = -99.;
    dr_lepFromHiggs_bFromLepTop_intree = -99.;

    null_jets_added_bdt_intree = 0;
    unmatched_jets_bdt_intree->clear();
    matched_jets_bdt_intree->clear();
    match_results_bdt_intree->clear();

  }
    
    void initializeTree(TTree *input_tree)
    {
    input_tree->Branch("reco_score", &reco_score_intree);
    input_tree->Branch("best_score_vec", &best_combo_vec_intree);
    input_tree->Branch("all_score_vec", &all_combo_vec_intree);
    input_tree->Branch("unmatched_jets_bdt", &unmatched_jets_bdt_intree);
    input_tree->Branch("matched_jets_bdt", &matched_jets_bdt_intree);
    input_tree->Branch("bTight_jets", &btight_jets_intree);
    input_tree->Branch("bLoose_jets", &bloose_jets_intree);
    input_tree->Branch("lep_from_leptop_bdt.", &lep_from_leptop_bdt_intree);
    input_tree->Branch("lep_from_higgs_bdt.", &lep_from_higgs_bdt_intree);
    input_tree->Branch("b_from_hadtop_bdt.", &b_from_hadtop_bdt_intree);
    input_tree->Branch("b_from_leptop_bdt.", &b_from_leptop_bdt_intree);
    input_tree->Branch("q1_from_hadtop_bdt.", &q1_from_hadtop_bdt_intree);
    input_tree->Branch("q2_from_hadtop_bdt.", &q2_from_hadtop_bdt_intree);
    input_tree->Branch("w_from_hadtop_bdt", &w_from_hadtop_tlv_bdt_intree);
    input_tree->Branch("hadTop_bdt", &hadTop_tlv_bdt_intree);
    input_tree->Branch("lepTop_bdt", &lepTop_tlv_bdt_intree);

    input_tree->Branch("dR_lepFromTop_bFromLepTop", &dr_lepFromTop_bFromLepTop_intree);
    input_tree->Branch("dR_lepFromTop_bFromHadTop", &dr_lepFromTop_bFromHadTop_intree);
    input_tree->Branch("dR_lepFromHiggs_bFromLepTop", &dr_lepFromHiggs_bFromLepTop_intree);
    input_tree->Branch("dR_lepFromHiggs_bFromHadTop", &dr_lepFromHiggs_bFromHadTop_intree);

    input_tree->Branch("match_results_bdt", &match_results_bdt_intree);    
    input_tree->Branch("null_jets_added_bdt", &null_jets_added_bdt_intree);

    input_tree->Branch("lepton_matching", &lepton_matching_intree);
    input_tree->Branch("b_from_hadtop_matching", &b_from_hadtop_matching_intree);
    input_tree->Branch("b_from_leptop_matching", &b_from_leptop_matching_intree);
    input_tree->Branch("W_from_hadtop_matching", &W_from_hadtop_matching_intree);

  }


  void initialize(vector<ttH::Jet> *jets_input, const vector<ttH::Lepton> *leptons_in, const ttH::MET met_in)
  {
    clear(); //reset all output vars

    vector<ttH::Jet> jets_in = *jets_input;

    //determine which weights file to use...
    for (const auto & jet : jets_in)
    {
      if (jet.csv >= 0.8) btight_jets_intree->push_back(jet);
      else if (jet.csv >= 0.46) bloose_jets_intree->push_back(jet);
    }
    
    bool is_bTight = false;
    if ( btight_jets_intree->size() > 1 ) is_bTight = true;

    if ( is_bTight ) TMVAReader_ = TMVAReader_bTight_;
    else             TMVAReader_ = TMVAReader_bLoose_;

    ///////////////////////////
    /////
    ///// loop setup
    /////
    ///////////////////////////

    //final state objs
    TLorentzVector lep_fromTop_tlv;
    TLorentzVector lep_fromHiggs_tlv;
    TLorentzVector bjet_fromHadTop_tlv;
    TLorentzVector bjet_fromLepTop_tlv;
    TLorentzVector wjet1_fromHadTop_tlv;
    TLorentzVector wjet2_fromHadTop_tlv;
    
    //intermediate objs
    TLorentzVector w_fromHadTop_tlv;
    
    //initial objs
    TLorentzVector hadTop_tlv;
    TLorentzVector lepTop_tlv;
    
    //misc final state objs
    TLorentzVector lepTop_hadTop_tlv;    
    
    //misc final state objs with met
    TLorentzVector leptop_T_tlv_intree;

    TLorentzVector lep_from_leptop_T_tlv;
    TLorentzVector lep_from_higgs_T_tlv;
    TLorentzVector b_from_leptop_T_tlv;
    TLorentzVector b_from_hadtop_T_tlv;
    TLorentzVector q1_from_hadtop_T_tlv;
    TLorentzVector q2_from_hadtop_T_tlv;
    TLorentzVector met_tlv = setTlv( met_in );   
   
    //NULL JET ADDITION RECIPE
    //for 7-jet (and fewer events), add 3 nulls
    //for 8-jet events, add 2 nulls
    //for >=9jet events, add 1 null
    ttH::Jet null_jet;
    if (jets_in.size() <= 7)
    {
      jets_in.push_back(null_jet);
      jets_in.push_back(null_jet);
      jets_in.push_back(null_jet);
      null_jets_added_bdt_intree = 3;
    } else if (jets_in.size() == 8) {
      jets_in.push_back(null_jet);
      jets_in.push_back(null_jet);
      null_jets_added_bdt_intree = 2;
    } else {
      jets_in.push_back(null_jet);
      null_jets_added_bdt_intree = 1;
    }
    

    ///////////////////////////
    /////
    ///// loop over reconstruction permutations
    /////
    ///////////////////////////

    int bjet_fromLepTop_count;
    int bjet_fromHadTop_count;
    int wjet1_fromHadTop_count;             
    int wjet2_fromHadTop_count;
    int lep_fromTop_count;
    int lep_fromHiggs_count;

    bool null_check_1;
    bool null_check_2;
    bool null_check_3;
    bool null_jet_check;

    bjet_fromHadTop_count = -1;
    for (const auto & bjet_fromHadTop : jets_in)
    {
      bjet_fromHadTop_count +=1;
      if (bjet_fromHadTop.obj.pt()==0 && jets_in[bjet_fromHadTop_count-1].obj.pt()==0) continue; //skip useless empty b-jet iterations (skip all perms with 2 null bjets)
      if ( is_bTight && bjet_fromHadTop.csv < 0.8) continue; //speed improvement
      if ( bjet_fromHadTop.csv > 0 && bjet_fromHadTop.csv < 0.46 ) continue; //speed improvement

      bjet_fromLepTop_count = -1;
      for (const auto & bjet_fromLepTop : jets_in)
      {
        bjet_fromLepTop_count +=1;
      
        if (bjet_fromHadTop_count == bjet_fromLepTop_count) continue;
        if (bjet_fromLepTop.obj.pt()==0 && jets_in[bjet_fromLepTop_count-1].obj.pt()==0) continue; //skip useless empty b-jet iterations (skip all perms with 2 null bjets)
        if ( is_bTight && bjet_fromLepTop.csv < 0.8) continue; //speed improvement
        if ( bjet_fromLepTop.csv > 0 && bjet_fromLepTop.csv < 0.46 ) continue; //speed improvement

        if ( !( (bjet_fromHadTop.csv > 0.8 || bjet_fromLepTop.csv > 0.8) || (bjet_fromHadTop.csv > 0.46 && bjet_fromLepTop.csv > 0.46) ) ) continue;
      
        wjet1_fromHadTop_count = -1;        
        for (const auto & wjet1_fromHadTop : jets_in)
        {
          wjet1_fromHadTop_count +=1;
      
          if (wjet1_fromHadTop_count == bjet_fromLepTop_count) continue;
          if (wjet1_fromHadTop_count == bjet_fromHadTop_count) continue;
      
          wjet2_fromHadTop_count = -1;
          for (const auto & wjet2_fromHadTop : jets_in)
          {
            wjet2_fromHadTop_count +=1;
        
            if (wjet2_fromHadTop_count == bjet_fromLepTop_count) continue;
            if (wjet2_fromHadTop_count == bjet_fromHadTop_count) continue;
            if (wjet2_fromHadTop_count <= wjet1_fromHadTop_count) continue; //skip duplicates  

            bjet_fromHadTop_tlv = setTlv(bjet_fromHadTop);  
            bjet_fromLepTop_tlv = setTlv(bjet_fromLepTop);
            wjet1_fromHadTop_tlv = setTlv(wjet1_fromHadTop);
            wjet2_fromHadTop_tlv = setTlv(wjet2_fromHadTop);
            w_fromHadTop_tlv = wjet1_fromHadTop_tlv + wjet2_fromHadTop_tlv;
        
            if (w_fromHadTop_tlv.M() > 120 ) continue; 
        
            hadTop_tlv = w_fromHadTop_tlv + bjet_fromHadTop_tlv;
        
            if ( hadTop_tlv.M() > 220 ) continue;
        
            lep_fromTop_count = -1;
            for (const auto & lep_fromTop : *leptons_in)
            {
              lep_fromTop_count +=1;
        
              lep_fromHiggs_count = -1;
              for (const auto & lep_fromHiggs : *leptons_in)
              {
                lep_fromHiggs_count +=1;  
                if (lep_fromTop_count == lep_fromHiggs_count) continue;
                
                lep_fromTop_tlv = setTlv(lep_fromTop);
                lep_fromHiggs_tlv = setTlv(lep_fromHiggs);
                lepTop_tlv = lep_fromTop_tlv + bjet_fromLepTop_tlv;
          
                if ( lepTop_tlv.M() > 180 ) continue;
          
                //calculate all your *new* variables
                bJet_fromLepTop_csv_var = bjet_fromLepTop.csv;
                bJet_fromHadTop_csv_var = bjet_fromHadTop.csv;

		q1_fromHadTop_csv_var = wjet1_fromHadTop.csv;
		q2_fromHadTop_csv_var = wjet2_fromHadTop.csv;

                hadTop_pt_var = hadTop_tlv.Pt();
                w_fromHadTop_mass_var = w_fromHadTop_tlv.M();
                hadTop_mass_var = hadTop_tlv.M();
                lep_fromHiggs_pT_var = lep_fromHiggs.correctedPt;
                //lep_pt_ratio_var = (lep_fromTop.correctedPt-lep_fromHiggs.correctedPt)/(lep_fromTop.correctedPt+lep_fromHiggs.correctedPt);
                lep_pt_ratio_var = lep_fromTop.correctedPt/lep_fromHiggs.correctedPt;
                lep_fromTop_pT_var = lep_fromTop.correctedPt;
          
                lep_from_leptop_T_tlv = setTlv_T(lep_fromTop);
                lep_from_higgs_T_tlv = setTlv_T(lep_fromHiggs);
                b_from_leptop_T_tlv = setTlv_T(bjet_fromLepTop);
                b_from_hadtop_T_tlv = setTlv_T(bjet_fromHadTop);
                q1_from_hadtop_T_tlv = setTlv_T(wjet1_fromHadTop);
                q2_from_hadtop_T_tlv = setTlv_T(wjet2_fromHadTop);
                leptop_T_tlv_intree = lep_from_leptop_T_tlv + b_from_leptop_T_tlv + met_tlv;

                //PLEASE NOTE: Set any dR with a null jet = -1. 
                dr_lepFromHiggs_bFromHadTop_var = getDeltaR(bjet_fromHadTop, lep_fromHiggs);
                dr_lepFromTop_bFromLepTop_var = getDeltaR(bjet_fromLepTop, lep_fromTop);
                dr_lepFromTop_bFromHadTop_var = getDeltaR(bjet_fromHadTop, lep_fromTop);
                dr_lepFromHiggs_bFromLepTop_var = getDeltaR(bjet_fromLepTop, lep_fromHiggs);
          
                double mva_value = TMVAReader_->EvaluateMVA( "BDTG method" );

                
                all_combo_vec_intree.push_back(mva_value);
          
                if ( mva_value > reco_score_intree )
                {
                  reco_score_intree = mva_value;
                  best_combo_vec_intree.push_back(mva_value);
                  *lep_from_leptop_bdt_intree = lep_fromTop;
                  *lep_from_higgs_bdt_intree = lep_fromHiggs;
                  *b_from_hadtop_bdt_intree = bjet_fromHadTop;
                  *b_from_leptop_bdt_intree = bjet_fromLepTop;
                  *q1_from_hadtop_bdt_intree = wjet1_fromHadTop;
                  *q2_from_hadtop_bdt_intree = wjet2_fromHadTop;
                  w_from_hadtop_tlv_bdt_intree = w_fromHadTop_tlv;

                  dr_lepFromHiggs_bFromHadTop_intree = dr_lepFromHiggs_bFromHadTop_var;
                  dr_lepFromTop_bFromLepTop_intree = dr_lepFromTop_bFromLepTop_var;
                  dr_lepFromTop_bFromHadTop_intree = dr_lepFromTop_bFromHadTop_var;
                  dr_lepFromHiggs_bFromLepTop_intree = dr_lepFromHiggs_bFromLepTop_var;

                  hadTop_tlv_bdt_intree = hadTop_tlv;
                  lepTop_tlv_bdt_intree = lepTop_tlv;
                }
              }
            }
          }
        }
      }
    }


    if ((*b_from_hadtop_bdt_intree).obj.pt() > 0.) matched_jets_bdt_intree->push_back(*b_from_hadtop_bdt_intree);
    if ((*b_from_leptop_bdt_intree).obj.pt() > 0.) matched_jets_bdt_intree->push_back(*b_from_leptop_bdt_intree);
    if ((*q1_from_hadtop_bdt_intree).obj.pt() > 0.) matched_jets_bdt_intree->push_back(*q1_from_hadtop_bdt_intree);
    if ((*q2_from_hadtop_bdt_intree).obj.pt() > 0.) matched_jets_bdt_intree->push_back(*q2_from_hadtop_bdt_intree);
  }

  void evaluateBdtMatching(const ttH::Lepton *lep_from_top_truth, const ttH::Lepton *lep_from_higgs_truth, const ttH::Jet *b_from_leptop_truth, const ttH::Jet *b_from_hadtop_truth, const ttH::Jet *q1_from_hadtop_truth, const ttH::Jet *q2_from_hadtop_truth, const ttH::Jet *q1_from_higgs_truth, const ttH::Jet *q2_from_higgs_truth )
  {
    ////
    //// matching results legened for b-jets:
    ////  5 = correct matched real-bdt to real-truth object
    ////  4 = correctly matched to null-bdt to null-truth object
    ////  3 = incorrectly matched real-bdt to real-truth object
    ////  2 = incorrectly matched real-bdt to null-truth object 
    ////  1 = incorrectly matched null-bdt to real-truth object
    ////

    //legend for composite objects
    // 5 = fully correct
    // 4 = 1/2 correct
    // 3 = fully incorrect

    //leptons
    if ((*lep_from_leptop_bdt_intree).obj.pt() == (*lep_from_top_truth).obj.pt()) lepton_matching_intree = 5;
    else lepton_matching_intree = 3;
    
    //bjet from hadronic top
    if ((*b_from_hadtop_bdt_intree).obj.pt() > 0)
    {
      if ((*b_from_hadtop_bdt_intree).obj.pt() == (*b_from_hadtop_truth).obj.pt()) b_from_hadtop_matching_intree = 5;
      else if ((*b_from_hadtop_truth).obj.pt() > 0) b_from_hadtop_matching_intree = 3; 
      else b_from_hadtop_matching_intree = 2;
    } else {
      if ((*b_from_hadtop_bdt_intree).obj.pt() == (*b_from_hadtop_truth).obj.pt()) b_from_hadtop_matching_intree = 4;
      else b_from_hadtop_matching_intree = 1;
    }
    
    //bjet from leptonic top
    if ((*b_from_leptop_bdt_intree).obj.pt() > 0)
    {
      if ((*b_from_leptop_bdt_intree).obj.pt() == (*b_from_leptop_truth).obj.pt()) b_from_leptop_matching_intree = 5;
      else if ((*b_from_leptop_truth).obj.pt() > 0) b_from_leptop_matching_intree = 3; 
      else b_from_leptop_matching_intree = 2;
    } else {
      if ((*b_from_leptop_bdt_intree).obj.pt() == (*b_from_leptop_truth).obj.pt()) b_from_leptop_matching_intree = 4;
      else b_from_leptop_matching_intree = 1;
    }

    //////////// new
    TLorentzVector W_hadtop_bdt = setTlv(*q1_from_hadtop_bdt_intree) + setTlv(*q2_from_hadtop_bdt_intree);
    TLorentzVector W_hadtop_truth = setTlv(*q1_from_hadtop_truth) + setTlv(*q2_from_hadtop_truth);
    
    if (W_hadtop_bdt.M() == W_hadtop_truth.M())
    {
      W_from_hadtop_matching_intree = 5;
    } else {
      if ((*q1_from_hadtop_bdt_intree).obj.pt() == (*q1_from_hadtop_truth).obj.pt() || (*q1_from_hadtop_bdt_intree).obj.pt() == (*q2_from_hadtop_truth).obj.pt()) W_from_hadtop_matching_intree = 4;
      else if ((*q2_from_hadtop_bdt_intree).obj.pt() == (*q2_from_hadtop_truth).obj.pt() || (*q2_from_hadtop_bdt_intree).obj.pt() == (*q1_from_hadtop_truth).obj.pt()) W_from_hadtop_matching_intree = 4;
      else W_from_hadtop_matching_intree = 3;
    }
  }

  
  //  virtual ~eventReconstructor(){};
};

#endif // _eventReconstructor_h
