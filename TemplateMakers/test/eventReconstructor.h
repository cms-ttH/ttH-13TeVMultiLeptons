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

  Float_t bJet_fromLepTop_CSV_var;
  Float_t LepTop_pT_var;
  Float_t LepTop_mass_var;
  Float_t LepTop_lep_bJet_dR_var;
  Float_t bJet_fromHadTop_CSV_var;
  Float_t qJet1_fromW_fromHadTop_CSV_var;
  Float_t qJet1_fromW_fromHadTop_pT_var;
  Float_t HadTop_pT_var;
  Float_t W_fromHadTop_mass_var;
  Float_t HadTop_mass_var;
  Float_t W_fromHadTop_q1_q2_dR_var;
  Float_t qJet1_fromW_fromHiggs_CSV_var;
  Float_t lep_fromW_fromHiggs_pT_var;
  Float_t lep_fromW_fromTop_pT_var;
  Float_t W_fromHiggs_mass_var;
  Float_t Higgs_mass_var;
  Float_t Higgs_lep_W_dR_var;
  Float_t Higgs_lep_W_dPhi_var;
  Float_t Higgs_lep_W_dEta_var;
  Float_t numMatchedJets_var;
  Float_t LepTop_Higgs_mass_var;
  Float_t HadTop_Higgs_mass_var;

  Float_t LepTop_Higgs_MT_var;

  Float_t HadTop_Higgs_MT_mass_ratio_var;
  Float_t ttH_MT_mass_ratio_var;
  Float_t LepTop_HadTop_dR_var;
  Float_t LepTop_HadTop_dPhi_var;
  Float_t LepAsym_var;
  Float_t lep_pt_ratio_var;

  //not yet mva inputs...
  Float_t lep_charge_var;
  Float_t bJet_fromHadTop_charge_var;
  Float_t bJet_fromLepTop_charge_var;
  Float_t W_fromHadTop_charge_var;
  Float_t W_fromHiggs_charge_var;
  Float_t lepTop_charge_var;
  Float_t hadTop_charge_var;
  Float_t Higgs_charge_var;
  Float_t ttH_charge_var;
  Float_t bJet_fromHadTop_charge_correct_var;
  Float_t bJet_fromLepTop_charge_correct_var;
  Float_t W_fromHadTop_charge_correct_var;
  Float_t W_fromHiggs_charge_correct_var;
  //my new vars
  Float_t dr_lepFromHiggs_bFromHadTop;
  Float_t dr_lepFromTop_bFromLepTop;
  Float_t dr_lepFromTop_bFromHadTop;
  Float_t dr_lepFromHiggs_bFromLepTop;

  TMVA::Reader* bookMVA(std::string weights_file_str)
  {
    TMVA::Reader* TMVAReader_internal_ = new TMVA::Reader( "!Color:!Silent" );
    
    TMVAReader_internal_->AddVariable( "b_from_leptop_bdt.csv", &bJet_fromLepTop_CSV_var );
    TMVAReader_internal_->AddVariable( "b_from_hadtop_bdt.csv", &bJet_fromHadTop_CSV_var );
    TMVAReader_internal_->AddVariable( "hadTop_tlv_bdt.Pt()", &HadTop_pT_var );
    TMVAReader_internal_->AddVariable( "w_from_hadtop_tlv_bdt.M()", &W_fromHadTop_mass_var );
    TMVAReader_internal_->AddVariable( "hadTop_tlv_bdt.M()", &HadTop_mass_var );
    //    TMVAReader_internal_->AddVariable( "higgs_tlv_bdt.M()", &Higgs_mass_var );
    TMVAReader_internal_->AddVariable( "lep_from_higgs_bdt.obj.pt()", &lep_fromW_fromHiggs_pT_var );
    TMVAReader_internal_->AddVariable( "lep_from_leptop_bdt.obj.pt()", &lep_fromW_fromTop_pT_var );
    TMVAReader_internal_->AddVariable( "lep_from_leptop_bdt.obj.pt()/lep_from_higgs_bdt.obj.pt()", &lep_pt_ratio_var );

    TMVAReader_internal_->AddVariable( "dr_lepFromHiggs_bFromHadTop", &dr_lepFromHiggs_bFromHadTop );
    TMVAReader_internal_->AddVariable( "dr_lepFromTop_bFromLepTop", &dr_lepFromTop_bFromLepTop );
    TMVAReader_internal_->AddVariable( "dr_lepFromTop_bFromHadTop", &dr_lepFromTop_bFromHadTop );
    TMVAReader_internal_->AddVariable( "dr_lepFromHiggs_bFromLepTop", &dr_lepFromHiggs_bFromLepTop );

    const char* env_p = std::getenv("CMSSW_BASE");
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
  ttH::Jet *b_from_hadtop_bdt_intree=0;
  ttH::Jet *q1_from_hadtop_bdt_intree=0;
  ttH::Jet *q2_from_hadtop_bdt_intree=0;
  ttH::Jet *q1_from_higgs_bdt_intree=0;
  ttH::Jet *q2_from_higgs_bdt_intree=0;
  
  TLorentzVector w_from_hadtop_tlv_bdt_intree;
  TLorentzVector w_from_higgs_tlv_bdt_intree;
  TLorentzVector higgs_tlv_bdt_intree;
  TLorentzVector hadTop_tlv_bdt_intree;
  TLorentzVector lepTop_tlv_bdt_intree;
  
  //simple hadtop reco
  TLorentzVector w_simple_intree;
  TLorentzVector top_simple_intree;
  ttH::Jet *b_from_hadtop_simple_intree=0;
  ttH::Jet *q1_from_hadtop_simple_intree=0;
  ttH::Jet *q2_from_hadtop_simple_intree=0;
  int b_simple_matching_intree;
  int w_simple_matching_intree;

  double dR_b_W_lepTop_bdt_intree;
  double dR_lepTop_hadTop_bdt_intree;
  double dR_W1_W2_fromHiggs_bdt_intree;
  int null_jets_added_bdt_intree;

  int lepton_matching_intree;
  int b_from_hadtop_matching_intree;
  int b_from_leptop_matching_intree;
  int W_from_hadtop_matching_intree;
  int W_from_higgs_matching_intree;

 public:
  eventReconstructor(){
    /* TMVAReader_bTight_ = bookMVA("/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/classifiers/weights/TMVAClassification_BDTG_v1p5_bTight.weights.xml"); */
    /* TMVAReader_bLoose_ = bookMVA("/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/classifiers/weights/TMVAClassification_BDTG_v1p5_bLoose.weights.xml"); */
    TMVAReader_bTight_ = bookMVA("/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/weights/TMVAClassification_BDTG.weights_v1p5_bTight__bjet_lep_dr.xml");
    TMVAReader_bLoose_ = bookMVA("/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/weights/TMVAClassification_BDTG.weights_v1p5_bLoose__bjet_lep_dr.xml");

  } // default constructor

  vector<int> *match_results_bdt_intree=0;
  double reco_score_intree;

  void clear(void)
  {
    //simple
    b_from_hadtop_simple_intree->clear();
    q1_from_hadtop_simple_intree->clear();
    q2_from_hadtop_simple_intree->clear();
    w_simple_intree.SetPxPyPzE(0.,0.,0.,0.);
    top_simple_intree.SetPxPyPzE(0.,0.,0.,0.);
    b_simple_matching_intree = -1;
    w_simple_matching_intree = -1;

    lepton_matching_intree = -1;
    b_from_hadtop_matching_intree = -1;
    b_from_leptop_matching_intree = -1;
    W_from_hadtop_matching_intree = -1;
    W_from_higgs_matching_intree = -1;
 
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
    q1_from_higgs_bdt_intree->clear();
    q2_from_higgs_bdt_intree->clear();
    w_from_hadtop_tlv_bdt_intree.SetPxPyPzE(0.,0.,0.,0.);
    w_from_higgs_tlv_bdt_intree.SetPxPyPzE(0.,0.,0.,0.);
    higgs_tlv_bdt_intree.SetPxPyPzE(0.,0.,0.,0.);
    hadTop_tlv_bdt_intree.SetPxPyPzE(0.,0.,0.,0.);
    lepTop_tlv_bdt_intree.SetPxPyPzE(0.,0.,0.,0.);
    dR_b_W_lepTop_bdt_intree=-1.;
    dR_lepTop_hadTop_bdt_intree=-1.;
    dR_W1_W2_fromHiggs_bdt_intree=-1.;
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
    input_tree->Branch("q1_from_higgs_bdt.", &q1_from_higgs_bdt_intree);
    input_tree->Branch("q2_from_higgs_bdt.", &q2_from_higgs_bdt_intree);

    input_tree->Branch("w_from_hadtop_bdt", &w_from_hadtop_tlv_bdt_intree);
    input_tree->Branch("w_from_higgs_bdt", &w_from_higgs_tlv_bdt_intree);
    input_tree->Branch("higgs_bdt", &higgs_tlv_bdt_intree);
    input_tree->Branch("hadTop_bdt", &hadTop_tlv_bdt_intree);
    input_tree->Branch("lepTop_bdt", &lepTop_tlv_bdt_intree);

    input_tree->Branch("match_results_bdt", &match_results_bdt_intree);
    
    input_tree->Branch("dR_b_W_lepTop_bdt", &dR_b_W_lepTop_bdt_intree);
    input_tree->Branch("dR_lepTop_hadTop_bdt", &dR_lepTop_hadTop_bdt_intree);
    input_tree->Branch("dR_W1_W2_fromHiggs_bdt", &dR_W1_W2_fromHiggs_bdt_intree);

    input_tree->Branch("null_jets_added_bdt", &null_jets_added_bdt_intree);

    //simple reconstruction
    input_tree->Branch("b_from_hadtop_simple", &b_from_hadtop_simple_intree);
    input_tree->Branch("q1_from_hadtop_simple", &q1_from_hadtop_simple_intree);
    input_tree->Branch("q2_from_hadtop_simple", &q2_from_hadtop_simple_intree);
    input_tree->Branch("hadtop_simple_tlv", &top_simple_intree);
    input_tree->Branch("w_simple_tlv", &w_simple_intree);

    input_tree->Branch("b_simple_matching", &b_simple_matching_intree);
    input_tree->Branch("w_simple_matching", &w_simple_matching_intree);
    
    input_tree->Branch("lepton_matching", &lepton_matching_intree);
    input_tree->Branch("b_from_hadtop_matching", &b_from_hadtop_matching_intree);
    input_tree->Branch("b_from_leptop_matching", &b_from_leptop_matching_intree);
    input_tree->Branch("W_from_hadtop_matching", &W_from_hadtop_matching_intree);
    input_tree->Branch("W_from_higgs_matching", &W_from_higgs_matching_intree);
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
    if ( btight_jets_intree->size() > 1 ) TMVAReader_ = TMVAReader_bTight_;
    else 	TMVAReader_ = TMVAReader_bLoose_;

    ////////////////////////////
    ////////
    ////////
    ////////  simple had top reconstruction
    ////////
    ////////
    ////////////////////////////
    
    int bjet_count = -1;
    int q1_count = -1;
    int q2_count = -1;
    TLorentzVector bjet_simple;
    TLorentzVector q1jet_simple;
    TLorentzVector q2jet_simple;
    TLorentzVector w_simple;
    TLorentzVector top_simple;
    double min_mass_diff = 100.;
    double mass_diff;

    for (const auto & bjet : jets_in)
      {
	bjet_count +=1;
	
	if (btight_jets_intree->size() > 1 && bjet.csv < 0.8 ) continue;
	else if (bjet.csv < 0.46 ) continue;
	bjet_simple = setTlv(bjet);

	q1_count = -1;
	for (const auto & q1jet : jets_in)
	  {
	    q1_count +=1;
	    if (q1jet.csv > 0.8 ) continue;
	    if (q1_count == bjet_count) continue;
	    q1jet_simple = setTlv(q1jet);

	    q2_count = -1;
	    for (const auto & q2jet : jets_in)
	      {
		q2_count +=1;
		if (q2jet.csv > 0.8 ) continue;
		if (q2_count == bjet_count) continue;
		if (q2_count <= q1_count) continue;
		q2jet_simple = setTlv(q2jet);
		w_simple = q1jet_simple + q2jet_simple;
		top_simple = w_simple + bjet_simple;
		mass_diff = abs(80.4-w_simple.M())+abs(172.-top_simple.M());
		if (mass_diff < min_mass_diff)
		  {
		    min_mass_diff = mass_diff;
		    w_simple_intree = w_simple;
		    top_simple_intree = top_simple;
		    *b_from_hadtop_simple_intree = bjet;
		    *q1_from_hadtop_simple_intree = q1jet;
		    *q2_from_hadtop_simple_intree = q2jet;
		  }

	      }
	  }
      }

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
    TLorentzVector wjet1_fromHiggs_tlv;
    TLorentzVector wjet2_fromHiggs_tlv;
    
    //intermediate objs
    TLorentzVector w_fromHadTop_tlv;
    TLorentzVector w_fromHiggs_tlv;
    
    //initial objs
    TLorentzVector higgs_tlv;
    TLorentzVector hadTop_tlv;
    TLorentzVector lepTop_tlv;
    
    //misc final state objs
    TLorentzVector lepTop_higgs_tlv;
    TLorentzVector hadTop_higgs_tlv;
    TLorentzVector lepTop_hadTop_tlv;    
    TLorentzVector tth_tlv;
    
    //misc final state objs with met
    TLorentzVector higgs_T_tlv_intree;
    TLorentzVector leptop_T_tlv_intree;
    TLorentzVector ttH_T_tlv_intree;

    TLorentzVector lep_from_leptop_T_tlv;
    TLorentzVector lep_from_higgs_T_tlv;
    TLorentzVector b_from_leptop_T_tlv;
    TLorentzVector b_from_hadtop_T_tlv;
    TLorentzVector q1_from_hadtop_T_tlv;
    TLorentzVector q2_from_hadtop_T_tlv;
    TLorentzVector q1_from_higgs_T_tlv;
    TLorentzVector q2_from_higgs_T_tlv;
    TLorentzVector met_tlv = setTlv( met_in );   
 
    //only add the same number of empty jets as there are fakes    
    ttH::Jet null_jet;
    if (jets_in.size() <= 7)
      {
	jets_in.push_back(null_jet);
	jets_in.push_back(null_jet);
	jets_in.push_back(null_jet);
	null_jets_added_bdt_intree = 3;
      }
    else if (jets_in.size() == 8)
      {
	jets_in.push_back(null_jet);
	jets_in.push_back(null_jet);
	null_jets_added_bdt_intree = 2;
      }
    else 
      {
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
    int wjet1_fromHiggs_count;
    int wjet2_fromHiggs_count;
    int lep_fromTop_count;
    int lep_fromHiggs_count;

    bjet_fromHadTop_count = -1;
    for (const auto & bjet_fromHadTop : jets_in)
      {
	bjet_fromHadTop_count +=1;
	if (bjet_fromHadTop.obj.pt()==0 && jets_in[bjet_fromHadTop_count-1].obj.pt()==0) continue; //skip useless empty b-jet iterations
	if ( btight_jets_intree->size() > 1 && bjet_fromHadTop.csv < 0.8) continue;
	//	if ( bjet_fromHadTop.csv > 0 && bjet_fromHadTop.csv < 0.46 ) continue;


	bjet_fromLepTop_count = -1;
	for (const auto & bjet_fromLepTop : jets_in)
	  {
	    bjet_fromLepTop_count +=1;
	    
	    if (bjet_fromHadTop_count == bjet_fromLepTop_count) continue;
	    if (bjet_fromLepTop.obj.pt()==0 && jets_in[bjet_fromLepTop_count-1].obj.pt()==0) continue; //skip useless empty b-jet iterations
	    if ( btight_jets_intree->size() > 1 && bjet_fromLepTop.csv < 0.8) continue;
	    //  if ( bjet_fromLepTop.csv > 0 && bjet_fromLepTop.csv < 0.46 ) continue;


	    if ( !( (bjet_fromHadTop.csv > 0.8 || bjet_fromLepTop.csv > 0.8) || (bjet_fromHadTop.csv > 0.4 && bjet_fromLepTop.csv > 0.4) ) ) continue;
	    
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
		    if (wjet2_fromHadTop_count <= wjet1_fromHadTop_count) continue; //don't need both orderings 

		    bjet_fromHadTop_tlv = setTlv(bjet_fromHadTop);	
		    bjet_fromLepTop_tlv = setTlv(bjet_fromLepTop);
		    wjet1_fromHadTop_tlv = setTlv(wjet1_fromHadTop);
		    wjet2_fromHadTop_tlv = setTlv(wjet2_fromHadTop);
		    w_fromHadTop_tlv = wjet1_fromHadTop_tlv + wjet2_fromHadTop_tlv;
		    
		    if (w_fromHadTop_tlv.M() > 120 ) continue; 
		    
		    hadTop_tlv = w_fromHadTop_tlv + bjet_fromHadTop_tlv;
		    
		    if ( hadTop_tlv.M() > 220 ) continue;

		    wjet1_fromHiggs_count = -1;
		    for (const auto & wjet1_fromHiggs : jets_in)
		      {
			wjet1_fromHiggs_count +=1;
			
			if (wjet1_fromHiggs_count == bjet_fromLepTop_count) continue;
			if (wjet1_fromHiggs_count == bjet_fromHadTop_count) continue;
			if (wjet1_fromHiggs_count == wjet1_fromHadTop_count) continue;
			if (wjet1_fromHiggs_count == wjet2_fromHadTop_count) continue;
			
			wjet2_fromHiggs_count = -1;
			for (const auto & wjet2_fromHiggs : jets_in)
			  {
			    wjet2_fromHiggs_count +=1;
			    
			    if (wjet2_fromHiggs_count == bjet_fromLepTop_count) continue;
			    if (wjet2_fromHiggs_count == bjet_fromHadTop_count) continue;
			    if (wjet2_fromHiggs_count == wjet1_fromHadTop_count) continue;
			    if (wjet2_fromHiggs_count == wjet2_fromHadTop_count) continue;
			    if (wjet2_fromHiggs_count <= wjet1_fromHiggs_count) continue;
			    
			    wjet1_fromHiggs_tlv = setTlv(wjet1_fromHiggs);
			    wjet2_fromHiggs_tlv = setTlv(wjet2_fromHiggs);
			    w_fromHiggs_tlv = wjet1_fromHiggs_tlv + wjet2_fromHiggs_tlv;
			    
			    if (w_fromHiggs_tlv.M() > 120 ) continue; 
			    
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
				    
				    higgs_tlv = w_fromHiggs_tlv + lep_fromHiggs_tlv;
				    
				    if (higgs_tlv.M() > 130 ) continue; 
				    
				    lepTop_higgs_tlv = higgs_tlv + lepTop_tlv;
				    hadTop_higgs_tlv = higgs_tlv + hadTop_tlv;
				    lepTop_hadTop_tlv = hadTop_tlv + lepTop_tlv;
				    tth_tlv = higgs_tlv + hadTop_tlv + lepTop_tlv;
				    
				    //mva evaluation
				    bJet_fromLepTop_CSV_var = bjet_fromLepTop.csv;
				    LepTop_pT_var = lepTop_tlv.Pt();
				    LepTop_mass_var = lepTop_tlv.M();
				    LepTop_lep_bJet_dR_var = lep_fromTop_tlv.DeltaR( bjet_fromLepTop_tlv );
				    bJet_fromHadTop_CSV_var = bjet_fromHadTop.csv;
				    qJet1_fromW_fromHadTop_CSV_var = wjet1_fromHadTop.csv;
				    qJet1_fromW_fromHadTop_pT_var = wjet1_fromHadTop.obj.pt();
				    HadTop_pT_var = hadTop_tlv.Pt();
				    W_fromHadTop_mass_var = w_fromHadTop_tlv.M();
				    HadTop_mass_var = hadTop_tlv.M();
				    W_fromHadTop_q1_q2_dR_var = wjet1_fromHadTop_tlv.DeltaR( wjet2_fromHadTop_tlv );
				    qJet1_fromW_fromHiggs_CSV_var = wjet1_fromHiggs.csv;
				    lep_fromW_fromHiggs_pT_var = lep_fromHiggs.obj.pt();
				    W_fromHiggs_mass_var = w_fromHiggs_tlv.M();
				    Higgs_mass_var = higgs_tlv.M();
				    Higgs_lep_W_dR_var = w_fromHiggs_tlv.DeltaR( lep_fromHiggs_tlv );
				    Higgs_lep_W_dPhi_var = lep_fromHiggs_tlv.DeltaPhi( w_fromHiggs_tlv );
				    Higgs_lep_W_dEta_var = lep_fromHiggs_tlv.Eta() - w_fromHiggs_tlv.Eta();
				    LepTop_Higgs_mass_var = lepTop_higgs_tlv.M();
				    HadTop_Higgs_mass_var = hadTop_higgs_tlv.M();
				    LepTop_HadTop_dR_var = lepTop_tlv.DeltaR( hadTop_tlv );
				    LepTop_HadTop_dPhi_var = lepTop_tlv.DeltaPhi( hadTop_tlv );
				    
				    if (bjet_fromLepTop_tlv.Pt() == 0) LepTop_lep_bJet_dR_var = -1.;
				    if (wjet1_fromHadTop_tlv.Pt() == 0 || wjet2_fromHadTop_tlv.Pt() == 0) W_fromHadTop_q1_q2_dR_var = -1.; 
				    if (w_fromHiggs_tlv.Pt() ==0 )
				      { 
					Higgs_lep_W_dR_var = -1.;
					Higgs_lep_W_dPhi_var = -4.0;
					Higgs_lep_W_dEta_var = -6.0;
				      }
				    
				    
				    bJet_fromHadTop_charge_var = bjet_fromHadTop.charge;
				    bJet_fromLepTop_charge_var = bjet_fromLepTop.charge;
				    W_fromHadTop_charge_var = wjet1_fromHadTop.charge + wjet2_fromHadTop.charge;
				    W_fromHiggs_charge_var = wjet1_fromHiggs.charge + wjet2_fromHiggs.charge;
				    
				    lepTop_charge_var = lep_fromTop.charge + bjet_fromLepTop.charge;
				    hadTop_charge_var = bjet_fromHadTop.charge + W_fromHadTop_charge_var;

				    Higgs_charge_var = lep_charge_var + W_fromHiggs_charge_var;
				    ttH_charge_var = lepTop_charge_var + hadTop_charge_var + Higgs_charge_var;
				    bJet_fromHadTop_charge_correct_var = (bjet_fromHadTop.charge != 0.) ? (bJet_fromHadTop_charge_var*lep_charge_var > 0) : -1;
				    bJet_fromLepTop_charge_correct_var = (bjet_fromHadTop.charge != 0.) ? (bJet_fromLepTop_charge_var*lep_charge_var < 0) : -1;
				    W_fromHadTop_charge_correct_var = (W_fromHadTop_charge_var*lep_charge_var < 0);
				    W_fromHiggs_charge_correct_var = (W_fromHiggs_charge_var*lep_charge_var < 0);
				    lep_pt_ratio_var =lep_fromTop.obj.pt()/lep_fromHiggs.obj.pt(); 
				    lep_fromW_fromTop_pT_var = lep_fromTop.obj.pt();
				    LepAsym_var = (lep_fromTop.obj.pt()-lep_fromHiggs.obj.pt())/(lep_fromTop.obj.pt()+lep_fromHiggs.obj.pt());
				    

				    //calculate all your *new* variables
				    lep_from_leptop_T_tlv = setTlv_T(lep_fromTop);
				    lep_from_higgs_T_tlv = setTlv_T(lep_fromHiggs);
				    b_from_leptop_T_tlv = setTlv_T(bjet_fromLepTop);
				    b_from_hadtop_T_tlv = setTlv_T(bjet_fromHadTop);
				    q1_from_hadtop_T_tlv = setTlv_T(wjet1_fromHadTop);
				    q2_from_hadtop_T_tlv = setTlv_T(wjet2_fromHadTop);
				    q1_from_higgs_T_tlv = setTlv_T(wjet1_fromHiggs);
				    q2_from_higgs_T_tlv = setTlv_T(wjet2_fromHiggs);
				    
				    higgs_T_tlv_intree = lep_from_higgs_T_tlv + met_tlv + q1_from_higgs_T_tlv + q2_from_higgs_T_tlv;
				    leptop_T_tlv_intree = lep_from_leptop_T_tlv + b_from_leptop_T_tlv + met_tlv;
				    ttH_T_tlv_intree = 
				      lep_from_leptop_T_tlv + met_tlv + b_from_leptop_T_tlv
				      + b_from_hadtop_T_tlv + q1_from_hadtop_T_tlv + q2_from_hadtop_T_tlv
				      + lep_from_higgs_T_tlv + q1_from_higgs_T_tlv + q2_from_higgs_T_tlv;
				    
				    dr_lepFromHiggs_bFromHadTop = getDeltaR(bjet_fromHadTop, lep_fromHiggs);
				    dr_lepFromTop_bFromLepTop = getDeltaR(bjet_fromLepTop, lep_fromTop);
				    dr_lepFromTop_bFromHadTop = getDeltaR(bjet_fromHadTop, lep_fromTop);
				    dr_lepFromHiggs_bFromLepTop = getDeltaR(bjet_fromLepTop, lep_fromHiggs);
				    

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
					*q1_from_higgs_bdt_intree = wjet1_fromHiggs;
					*q2_from_higgs_bdt_intree = wjet2_fromHiggs;
					
					w_from_hadtop_tlv_bdt_intree = w_fromHadTop_tlv;    
					w_from_higgs_tlv_bdt_intree = w_fromHiggs_tlv;
					higgs_tlv_bdt_intree = higgs_tlv;
					hadTop_tlv_bdt_intree = hadTop_tlv;
					lepTop_tlv_bdt_intree = lepTop_tlv;
					
					dR_b_W_lepTop_bdt_intree = LepTop_lep_bJet_dR_var;
					dR_lepTop_hadTop_bdt_intree = LepTop_HadTop_dR_var;
					dR_W1_W2_fromHiggs_bdt_intree = Higgs_lep_W_dR_var;

				      }
				  }
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
    if ((*q1_from_higgs_bdt_intree).obj.pt() > 0.) matched_jets_bdt_intree->push_back(*q1_from_higgs_bdt_intree);
    if ((*q2_from_higgs_bdt_intree).obj.pt() > 0.) matched_jets_bdt_intree->push_back(*q2_from_higgs_bdt_intree);


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
      }
    else
      {
	if ((*b_from_hadtop_bdt_intree).obj.pt() == (*b_from_hadtop_truth).obj.pt()) b_from_hadtop_matching_intree = 4;
	else b_from_hadtop_matching_intree = 1;
      }
    
    //bjet from leptonic top
    if ((*b_from_leptop_bdt_intree).obj.pt() > 0)
      {
	if ((*b_from_leptop_bdt_intree).obj.pt() == (*b_from_leptop_truth).obj.pt()) b_from_leptop_matching_intree = 5;
	else if ((*b_from_leptop_truth).obj.pt() > 0) b_from_leptop_matching_intree = 3; 
	else b_from_leptop_matching_intree = 2;
      }
    else
      {
	if ((*b_from_leptop_bdt_intree).obj.pt() == (*b_from_leptop_truth).obj.pt()) b_from_leptop_matching_intree = 4;
	else b_from_leptop_matching_intree = 1;
      }


    //////////// new
    TLorentzVector W_hadtop_bdt = setTlv(*q1_from_hadtop_bdt_intree) + setTlv(*q2_from_hadtop_bdt_intree);
    TLorentzVector W_hadtop_truth = setTlv(*q1_from_hadtop_truth) + setTlv(*q2_from_hadtop_truth);
    
    if (W_hadtop_bdt.M() == W_hadtop_truth.M())	W_from_hadtop_matching_intree = 5;
    else 
      {
	if ((*q1_from_hadtop_bdt_intree).obj.pt() == (*q1_from_hadtop_truth).obj.pt() || (*q1_from_hadtop_bdt_intree).obj.pt() == (*q2_from_hadtop_truth).obj.pt()) W_from_hadtop_matching_intree = 4;
	else if ((*q2_from_hadtop_bdt_intree).obj.pt() == (*q2_from_hadtop_truth).obj.pt() || (*q2_from_hadtop_bdt_intree).obj.pt() == (*q1_from_hadtop_truth).obj.pt()) W_from_hadtop_matching_intree = 4;
	else W_from_hadtop_matching_intree = 3;
      }


    TLorentzVector W_higgs_bdt = setTlv(*q1_from_higgs_bdt_intree) + setTlv(*q2_from_higgs_bdt_intree);
    TLorentzVector W_higgs_truth = setTlv(*q1_from_higgs_truth) + setTlv(*q2_from_higgs_truth);
    
    if (W_higgs_bdt.M() == W_higgs_truth.M())	W_from_higgs_matching_intree = 5;
    else 
      {
	if ((*q1_from_higgs_bdt_intree).obj.pt() == (*q1_from_higgs_truth).obj.pt() || (*q1_from_higgs_bdt_intree).obj.pt() == (*q2_from_higgs_truth).obj.pt()) W_from_higgs_matching_intree = 4;
	else if ((*q2_from_higgs_bdt_intree).obj.pt() == (*q2_from_higgs_truth).obj.pt() || (*q2_from_higgs_bdt_intree).obj.pt() == (*q1_from_higgs_truth).obj.pt()) W_from_higgs_matching_intree = 4;
	else W_from_higgs_matching_intree = 3;
      }


    //simple hadtop matching
    if ((*b_from_hadtop_simple_intree).obj.pt() == (*b_from_hadtop_truth).obj.pt())
      {
	b_simple_matching_intree = 5;
      }
    else 
      {
	if ((*b_from_hadtop_truth).obj.pt() > 0) b_simple_matching_intree = 3;
	else b_simple_matching_intree = 2;
      }
    
    if (w_simple_intree.M() == W_higgs_truth.M()) w_simple_matching_intree = 5;
    else 
      {
	if ((*q1_from_hadtop_simple_intree).obj.pt() == (*q1_from_hadtop_truth).obj.pt() || (*q1_from_hadtop_simple_intree).obj.pt() ==(*q2_from_hadtop_truth).obj.pt()) w_simple_matching_intree = 4; 
	else if ((*q2_from_hadtop_simple_intree).obj.pt() == (*q1_from_hadtop_truth).obj.pt() || (*q2_from_hadtop_simple_intree).obj.pt() ==(*q2_from_hadtop_truth).obj.pt()) w_simple_matching_intree = 4; 
	else w_simple_matching_intree = 3;
      }

  }

  
  //  virtual ~eventReconstructor(){};
};

#endif // _eventReconstructor_h
