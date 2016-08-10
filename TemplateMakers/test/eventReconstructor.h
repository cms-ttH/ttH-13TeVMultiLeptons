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
  Float_t LepTop_HadTop_MT_var;
  Float_t LepTop_Higgs_MT_var;
  Float_t ttH_MT_var;
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
  
  void bookMVA(void)
  {
    TMVAReader_ = new TMVA::Reader( "!Color:!Silent" );
    
    TMVAReader_->AddVariable( "b_from_leptop_bdt.csv", &bJet_fromLepTop_CSV_var );
    TMVAReader_->AddVariable( "b_from_hadtop_bdt.csv", &bJet_fromHadTop_CSV_var );
    TMVAReader_->AddVariable( "hadTop_tlv_bdt.Pt()", &HadTop_pT_var );
    TMVAReader_->AddVariable( "w_from_hadtop_tlv_bdt.M()", &W_fromHadTop_mass_var );
    TMVAReader_->AddVariable( "hadTop_tlv_bdt.M()", &HadTop_mass_var );
    TMVAReader_->AddVariable( "higgs_tlv_bdt.M()", &Higgs_mass_var );
    //    TMVAReader_->AddVariable( "dR_lepTop_hadTop", &LepTop_HadTop_dR_var );
    TMVAReader_->AddVariable( "lep_from_higgs_bdt.obj.pt()", &lep_fromW_fromHiggs_pT_var );
    TMVAReader_->AddVariable( "lep_from_leptop_bdt.obj.pt()", &lep_fromW_fromTop_pT_var );
    TMVAReader_->AddVariable( "lep_from_leptop_bdt.obj.pt()/lep_from_higgs_bdt.obj.pt()", &lep_pt_ratio_var );
    


    //    TMVAReader_->AddVariable( "qJet1_fromW_fromHadTop_CSV", &qJet1_fromW_fromHadTop_CSV_var );
    //    TMVAReader_->AddVariable( "W_fromHiggs_mass", &W_fromHiggs_mass_var );
    /* TMVAReader_->AddVariable( "LepTop_pT", &LepTop_pT_var ); */
    /* TMVAReader_->AddVariable( "LepTop_mass", &LepTop_mass_var ); */
    /* TMVAReader_->AddVariable( "LepTop_lep_bJet_dR", &LepTop_lep_bJet_dR_var ); */
    /* TMVAReader_->AddVariable( "qJet1_fromW_fromHadTop_pT", &qJet1_fromW_fromHadTop_pT_var ); */
    /* TMVAReader_->AddVariable( "W_fromHadTop_q1_q2_dR", &W_fromHadTop_q1_q2_dR_var ); */
    /* TMVAReader_->AddVariable( "qJet1_fromW_fromHiggs_CSV", &qJet1_fromW_fromHiggs_CSV_var ); */
    /* TMVAReader_->AddVariable( "Higgs_lep_W_dR", &Higgs_lep_W_dR_var ); */
    /* TMVAReader_->AddVariable( "Higgs_lep_W_dPhi", &Higgs_lep_W_dPhi_var ); */
    /* TMVAReader_->AddVariable( "LepTop_Higgs_mass", &LepTop_Higgs_mass_var ); */
    /* TMVAReader_->AddVariable( "HadTop_Higgs_mass", &HadTop_Higgs_mass_var ); */
    /* TMVAReader_->AddVariable( "HadTop_Higgs_MT_mass_ratio", &HadTop_Higgs_MT_mass_ratio_var ); */
    /* TMVAReader_->AddVariable( "ttH_MT_mass_ratio", &ttH_MT_mass_ratio_var ); */
    /* TMVAReader_->AddVariable( "LepTop_HadTop_dPhi", &LepTop_HadTop_dPhi_var ); */
    //    TMVAReader_->AddVariable( "(lep_fromTop.obj.pt()-lep_fromHiggs.obj.pt())/(lep_fromTop.obj.pt()+lep_fromHiggs.obj.pt())", &LepAsym_var );

    const char* env_p = std::getenv("CMSSW_BASE");
    std::string weight_file = env_p;
    std::string file_str = "/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/classifiers/weights/TMVAClassification_BDTG_v1p5.weights.xml"; 
    //    std::string file_str = "/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/weights/TMVAClassification_BDTG_July12_1541.weights.xml"; 
    weight_file += file_str;

    TMVAReader_->BookMVA("BDTG method", weight_file);

  }
  
  double reco_score_intree;
  vector<ttH::Jet> *unmatched_jets_bdt_intree=0;
  vector<ttH::Jet> *matched_jets_bdt_intree=0;
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
  double dR_b_W_lepTop_bdt_intree;
  double dR_lepTop_hadTop_bdt_intree;
  double dR_W1_W2_fromHiggs_bdt_intree;
  int null_jets_added_bdt_intree;


 public:
  eventReconstructor(){
    bookMVA();
  } // default constructor

  vector<int> *match_results_bdt_intree=0;

  void clear(void)
  {
    reco_score_intree = -1.;
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

    input_tree->Branch("unmatched_jets_bdt", &unmatched_jets_bdt_intree);
    input_tree->Branch("matched_jets_bdt", &matched_jets_bdt_intree);

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
  }


  void initialize(vector<ttH::Jet> *jets_input, const vector<ttH::Lepton> *leptons_in)
  {
    clear(); //reset all output vars

    vector<ttH::Jet> jets_in = *jets_input;

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
	
	bjet_fromLepTop_count = -1;
	for (const auto & bjet_fromLepTop : jets_in)
	  {
	    bjet_fromLepTop_count +=1;
	    
	    if (bjet_fromHadTop_count == bjet_fromLepTop_count) continue;
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

				    double mva_value = TMVAReader_->EvaluateMVA( "BDTG method" );

				    if ( mva_value > reco_score_intree )
				      {
					reco_score_intree = mva_value;

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
    //// matching results legened:
    ////  5 = correct matched real-bdt to real-truth object
    ////  4 = correctly matched to null-bdt to null-truth object
    ////  3 = incorrectly matched real-bdt to real-truth object
    ////  2 = incorrectly matched real-bdt to null-truth object 
    ////  1 = incorrectly matched null-bdt to real-truth object
    ////

    //leptons
    if ((*lep_from_leptop_bdt_intree).obj.pt() == (*lep_from_top_truth).obj.pt()) match_results_bdt_intree->push_back(5);
    else match_results_bdt_intree->push_back(3);
    
    //bjet from hadronic top
    if ((*b_from_hadtop_bdt_intree).obj.pt() > 0)
      {
	if ((*b_from_hadtop_bdt_intree).obj.pt() == (*b_from_hadtop_truth).obj.pt()) match_results_bdt_intree->push_back(5);
	else if ((*b_from_hadtop_truth).obj.pt() > 0) match_results_bdt_intree->push_back(3); 
	else match_results_bdt_intree->push_back(2);
      }
    else
      {
	if ((*b_from_hadtop_bdt_intree).obj.pt() == (*b_from_hadtop_truth).obj.pt()) match_results_bdt_intree->push_back(4);
	else match_results_bdt_intree->push_back(1);
      }
    
    //bjet from leptonic top
    if ((*b_from_leptop_bdt_intree).obj.pt() > 0)
      {
	if ((*b_from_leptop_bdt_intree).obj.pt() == (*b_from_leptop_truth).obj.pt()) match_results_bdt_intree->push_back(5);
	else if ((*b_from_leptop_truth).obj.pt() > 0) match_results_bdt_intree->push_back(3); 
	else match_results_bdt_intree->push_back(2);
      }
    else
      {
	if ((*b_from_leptop_bdt_intree).obj.pt() == (*b_from_leptop_truth).obj.pt()) match_results_bdt_intree->push_back(4);
	else match_results_bdt_intree->push_back(1);
      }
    
    //wjet1 from hadronic top
    if ((*q1_from_hadtop_bdt_intree).obj.pt() > 0)
      {
	if ((*q1_from_hadtop_bdt_intree).obj.pt() == (*q1_from_hadtop_truth).obj.pt() || (*q1_from_hadtop_bdt_intree).obj.pt() == (*q2_from_hadtop_truth).obj.pt()) match_results_bdt_intree->push_back(5);
	else if ((*q1_from_hadtop_truth).obj.pt() > 0 || (*q2_from_hadtop_truth).obj.pt() > 0) match_results_bdt_intree->push_back(3); 
	else match_results_bdt_intree->push_back(2);
      }
    else
      {
	if ((*q1_from_hadtop_bdt_intree).obj.pt() == (*q1_from_hadtop_truth).obj.pt() || (*q1_from_hadtop_bdt_intree).obj.pt() == (*q2_from_hadtop_truth).obj.pt()) match_results_bdt_intree->push_back(4);
	else match_results_bdt_intree->push_back(1);
      }
    //wjet2 from hadronic top
    if ((*q2_from_hadtop_bdt_intree).obj.pt() > 0)
      {
	if ((*q2_from_hadtop_bdt_intree).obj.pt() == (*q2_from_hadtop_truth).obj.pt() || (*q2_from_hadtop_bdt_intree).obj.pt() == (*q1_from_hadtop_truth).obj.pt()) match_results_bdt_intree->push_back(5);
	else if ((*q2_from_hadtop_truth).obj.pt() > 0 || (*q1_from_hadtop_truth).obj.pt() > 0) match_results_bdt_intree->push_back(3); 
	else match_results_bdt_intree->push_back(2);
      }
    else
      {
	if ((*q2_from_hadtop_bdt_intree).obj.pt() == (*q2_from_hadtop_truth).obj.pt() || (*q2_from_hadtop_bdt_intree).obj.pt() == (*q1_from_hadtop_truth).obj.pt()) match_results_bdt_intree->push_back(4);
	else match_results_bdt_intree->push_back(1);
      }
    
    //wjet1 from higgs
    if ((*q1_from_higgs_bdt_intree).obj.pt() > 0)
      {
	if ((*q1_from_higgs_bdt_intree).obj.pt() == (*q1_from_higgs_truth).obj.pt() || (*q1_from_higgs_bdt_intree).obj.pt() == (*q2_from_higgs_truth).obj.pt()) match_results_bdt_intree->push_back(5);
	else if ((*q1_from_higgs_truth).obj.pt() > 0 || (*q2_from_higgs_truth).obj.pt() > 0) match_results_bdt_intree->push_back(3); 
	else match_results_bdt_intree->push_back(2);
      }
    else
      {
	if ((*q1_from_higgs_bdt_intree).obj.pt() == (*q1_from_higgs_truth).obj.pt() || (*q1_from_higgs_bdt_intree).obj.pt() == (*q2_from_higgs_truth).obj.pt()) match_results_bdt_intree->push_back(4);
	else match_results_bdt_intree->push_back(1);
      }
    //wjet2 from higgs
    if ((*q2_from_higgs_bdt_intree).obj.pt() > 0)
      {
	if ((*q2_from_higgs_bdt_intree).obj.pt() == (*q2_from_higgs_truth).obj.pt() || (*q2_from_higgs_bdt_intree).obj.pt() == (*q1_from_higgs_truth).obj.pt()) match_results_bdt_intree->push_back(5);
	else if ((*q2_from_higgs_truth).obj.pt() > 0 || (*q1_from_higgs_truth).obj.pt() > 0) match_results_bdt_intree->push_back(3); 
	else match_results_bdt_intree->push_back(2);
      }
    else
      {
	if ((*q2_from_higgs_bdt_intree).obj.pt() == (*q2_from_higgs_truth).obj.pt() || (*q2_from_higgs_bdt_intree).obj.pt() == (*q1_from_higgs_truth).obj.pt()) match_results_bdt_intree->push_back(4);
	else match_results_bdt_intree->push_back(1);
      }
    
  }

  
  //  virtual ~eventReconstructor(){};
};

#endif // _eventReconstructor_h
