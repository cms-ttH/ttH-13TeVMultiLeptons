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
  Float_t nJets_var;
  
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

    TMVAReader_->AddVariable( "bJet_fromLepTop_CSV", &bJet_fromLepTop_CSV_var );
    TMVAReader_->AddVariable( "bJet_fromHadTop_CSV", &bJet_fromHadTop_CSV_var );
    TMVAReader_->AddVariable( "HadTop_pT", &HadTop_pT_var );
    TMVAReader_->AddVariable( "W_fromHadTop_mass", &W_fromHadTop_mass_var );
    TMVAReader_->AddVariable( "HadTop_mass", &HadTop_mass_var );
    TMVAReader_->AddVariable( "Higgs_mass", &Higgs_mass_var );
    TMVAReader_->AddVariable( "LepTop_HadTop_dR", &LepTop_HadTop_dR_var );
    TMVAReader_->AddVariable( "lep_fromW_fromHiggs_pT", &lep_fromW_fromHiggs_pT_var );

    //    TMVAReader_->AddVariable( "qJet1_fromW_fromHadTop_CSV", &qJet1_fromW_fromHadTop_CSV_var );
    //    TMVAReader_->AddVariable( "W_fromHiggs_mass", &W_fromHiggs_mass_var );
    //    TMVAReader_->AddVariable( "numJets", &nJets_var );
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
    std::string file_str = "/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/TMVAClassification_BDTG_v0.weights.xml"; 
    //    std::string file_str = "/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/weights/TMVAClassification_BDTG_July12_1541.weights.xml"; 
    weight_file += file_str;

    TMVAReader_->BookMVA("BDTG method", weight_file);

  }

  void clear(void)
  {
    reco_score = -1.;
    num_jet_matches_truth = 0;
    num_real_jets_bdt = 0;
    norm_score_sum = 0.;
    matching_results.clear();
    matched_jets.clear();
    matched_jets_truth.clear();
  }
  
 public:
  eventReconstructor(){
    bookMVA();
    clear();
  } // default constructor
  
  double reco_score;
  double norm_score_sum;
  int num_jet_matches_truth;
  int num_real_jets_bdt;

  vector<ttH::Jet> matched_jets_truth;
  vector<ttH::Jet> matched_jets;
  ttH::Lepton lep_fromTop_truth;
  ttH::Lepton lep_fromHiggs_truth;
  ttH::Lepton lep_fromTop_bdt;
  ttH::Lepton lep_fromHiggs_bdt;
  vector<int> matching_results;

  TLorentzVector lep_fromTop_bdt_tlv;
  TLorentzVector lep_fromHiggs_bdt_tlv;
  TLorentzVector bjet_fromHadTop_bdt_tlv;
  TLorentzVector bjet_fromLepTop_bdt_tlv;
  TLorentzVector wjet1_fromHadTop_bdt_tlv;    
  TLorentzVector wjet2_fromHadTop_bdt_tlv;
  TLorentzVector wjet1_fromHiggs_bdt_tlv;  
  TLorentzVector wjet2_fromHiggs_bdt_tlv;
  TLorentzVector w_fromHadTop_bdt_tlv;    
  TLorentzVector w_fromHiggs_bdt_tlv;
  TLorentzVector higgs_bdt_tlv;
  TLorentzVector hadTop_bdt_tlv;
  TLorentzVector lepTop_bdt_tlv;
  TLorentzVector lepTop_higgs_bdt_tlv;
  TLorentzVector hadTop_higgs_bdt_tlv;
  TLorentzVector lepTop_hadTop_bdt_tlv;
  TLorentzVector tth_bdt_tlv;
    
  void initialize(vector<ttH::Jet> *jets_input, const vector<ttH::Lepton> *leptons_in)
  {
    clear(); //reset all output vars

    vector<ttH::Jet> *jets_in = jets_input;

    ///////////////////////////
    /////
    ///// calculate truth info 
    /////
    ///////////////////////////

    //find truth leptons first    
    ttH::Lepton lep_fromTop_truth = (*leptons_in)[0];
    ttH::Lepton lep_fromHiggs_truth = (*leptons_in)[1];
    
    if (abs(lep_fromTop_truth.genGrandMotherPdgID) == 25 || abs(lep_fromHiggs_truth.genGrandMotherPdgID) == 6 )
      {
	lep_fromTop_truth = (*leptons_in)[1];
	lep_fromHiggs_truth = (*leptons_in)[0];
      }

    int lep_charge = lep_fromTop_truth.charge;

    //truth jets
    vector<ttH::Jet> matched_jets_truth;
    ttH::Jet bjet_fromHadTop_truth;
    ttH::Jet bjet_fromLepTop_truth;
    ttH::Jet wjet1_fromHadTop_truth;
    ttH::Jet wjet2_fromHadTop_truth;
    ttH::Jet wjet1_fromHiggs_truth;
    ttH::Jet wjet2_fromHiggs_truth;
    
    for (const auto & jet : *jets_in)
      {
	if (abs(jet.genPdgID) == 5)
	  {
	    if (jet.genPdgID*lep_charge < 0) bjet_fromHadTop_truth = jet;
	    else bjet_fromLepTop_truth = jet;
	  }
	else if ( jet.genGrandMotherPdgID == 25 )
	  {
	    if (wjet1_fromHiggs_truth.obj.pt() == 0) wjet1_fromHiggs_truth = jet;
	    else wjet2_fromHiggs_truth = jet;
	  }
	else if ( abs(jet.genGrandMotherPdgID) == 6 )
	  {
	    if (wjet1_fromHadTop_truth.obj.pt() == 0) wjet1_fromHadTop_truth = jet;
	    else wjet2_fromHadTop_truth = jet;
	  }
      }
    
    matched_jets_truth.push_back(bjet_fromHadTop_truth);
    matched_jets_truth.push_back(bjet_fromLepTop_truth);
    matched_jets_truth.push_back(wjet1_fromHadTop_truth);
    matched_jets_truth.push_back(wjet2_fromHadTop_truth);
    matched_jets_truth.push_back(wjet1_fromHiggs_truth);
    matched_jets_truth.push_back(wjet2_fromHiggs_truth);
    
    for (const auto & jet : matched_jets_truth)
      {
	if (jet.obj.pt() > 0) num_jet_matches_truth +=1;
      }
    
    ///////////////////////////
    /////
    ///// loop setup
    /////
    ///////////////////////////

    //Andrew's fix for -1 csv values to make range easier to see.
    for (unsigned int j =0; j< jets_in->size(); j++)
      {
	double csv = (*jets_in)[j].csv;
	(*jets_in)[j].csv = max(-.1,csv);
      }
    
    //final state objs
    TLorentzVector lep_fromTop_tlv;
    TLorentzVector lep_fromTop_T_tlv;
    
    TLorentzVector lep_fromHiggs_tlv;
    TLorentzVector lep_fromHiggs_T_tlv;
    
    TLorentzVector bjet_fromHadTop_tlv;
    TLorentzVector bjet_fromHadTop_T_tlv;
    
    TLorentzVector bjet_fromLepTop_tlv;
    TLorentzVector bjet_fromLepTop_T_tlv;
    
    TLorentzVector wjet1_fromHadTop_tlv;
    TLorentzVector wjet1_fromHadTop_T_tlv;
    
    TLorentzVector wjet2_fromHadTop_tlv;
    TLorentzVector wjet2_fromHadTop_T_tlv;
    
    TLorentzVector wjet1_fromHiggs_tlv;
    TLorentzVector wjet1_fromHiggs_T_tlv;
    
    TLorentzVector wjet2_fromHiggs_tlv;
    TLorentzVector wjet2_fromHiggs_T_tlv;
    
    //intermediate objs

    TLorentzVector w_fromHadTop_tlv;
    TLorentzVector w_fromHadTop_T_tlv;
    
    TLorentzVector w_fromHiggs_tlv;
    TLorentzVector w_fromHiggs_T_tlv;
    
    //initial objs
    
    TLorentzVector higgs_tlv;
    TLorentzVector higgs_T_tlv;
    
    TLorentzVector hadTop_tlv;
    TLorentzVector hadTop_T_tlv;

    TLorentzVector lepTop_tlv;
    TLorentzVector lepTop_T_tlv;
    
    //misc final state objs
    
    TLorentzVector lepTop_higgs_tlv;
    TLorentzVector lepTop_higgs_T_tlv;
    
    TLorentzVector hadTop_higgs_tlv;
    TLorentzVector hadTop_higgs_T_tlv;
    
    TLorentzVector lepTop_hadTop_tlv;
    TLorentzVector lepTop_hadTop_T_tlv;
    
    TLorentzVector tth_tlv;
    TLorentzVector tth_T_tlv;
    
    //only add the same number of empty jets as there are fakes
    
    int num_jets_var = jets_in->size();
    nJets_var = jets_in->size();

    ttH::Jet null_jet;
    if (num_jets_var <= 7)
      {
	(*jets_in).push_back(null_jet);
	(*jets_in).push_back(null_jet);
	(*jets_in).push_back(null_jet);
      }
    else if (num_jets_var == 8)
      {
	(*jets_in).push_back(null_jet);
	(*jets_in).push_back(null_jet);
      }
    else (*jets_in).push_back(null_jet);


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
    for (const auto & bjet_fromHadTop : *jets_in)
      {
	bjet_fromHadTop_count +=1;
	
	bjet_fromLepTop_count = -1;
	for (const auto & bjet_fromLepTop : *jets_in)
	  {
	    bjet_fromLepTop_count +=1;
	    
	    if (bjet_fromHadTop_count == bjet_fromLepTop_count) continue;
	    if ( !( (bjet_fromHadTop.csv > 0.8 || bjet_fromLepTop.csv > 0.8) || (bjet_fromHadTop.csv > 0.4 && bjet_fromLepTop.csv > 0.4) ) ) continue;
	    
	    wjet1_fromHadTop_count = -1;	    
	    for (const auto & wjet1_fromHadTop : *jets_in)
	      {
		wjet1_fromHadTop_count +=1;
		
		if (wjet1_fromHadTop_count == bjet_fromLepTop_count) continue;
		if (wjet1_fromHadTop_count == bjet_fromHadTop_count) continue;
		
		wjet2_fromHadTop_count = -1;
		for (const auto & wjet2_fromHadTop : *jets_in)
		  {
		    wjet2_fromHadTop_count +=1;
		    
		    if (wjet2_fromHadTop_count == bjet_fromLepTop_count) continue;
		    if (wjet2_fromHadTop_count == bjet_fromHadTop_count) continue;
		    if (wjet2_fromHadTop_count <= wjet1_fromHadTop_count) continue; //don't need both orderings 

		    bjet_fromHadTop_tlv.SetPxPyPzE(bjet_fromHadTop.obj.px(),bjet_fromHadTop.obj.py(),bjet_fromHadTop.obj.pz(),bjet_fromHadTop.obj.E());
		    bjet_fromHadTop_T_tlv.SetPxPyPzE(bjet_fromHadTop.obj.px(),bjet_fromHadTop.obj.py(), 0. ,bjet_fromHadTop.obj.pt());
	
		    bjet_fromLepTop_tlv.SetPxPyPzE(bjet_fromLepTop.obj.px(),bjet_fromLepTop.obj.py(),bjet_fromLepTop.obj.pz(),bjet_fromLepTop.obj.E());
		    bjet_fromLepTop_T_tlv.SetPxPyPzE(bjet_fromLepTop.obj.px(),bjet_fromLepTop.obj.py(), 0. ,bjet_fromLepTop.obj.pt());	    

		    wjet1_fromHadTop_tlv.SetPxPyPzE(wjet1_fromHadTop.obj.px(),wjet1_fromHadTop.obj.py(),wjet1_fromHadTop.obj.pz(),wjet1_fromHadTop.obj.E());
		    wjet1_fromHadTop_T_tlv.SetPxPyPzE(wjet1_fromHadTop.obj.px(),wjet1_fromHadTop.obj.py(), 0. ,wjet1_fromHadTop.obj.pt());
		    
		    wjet2_fromHadTop_tlv.SetPxPyPzE(wjet2_fromHadTop.obj.px(),wjet2_fromHadTop.obj.py(),wjet2_fromHadTop.obj.pz(),wjet2_fromHadTop.obj.E());
		    wjet2_fromHadTop_T_tlv.SetPxPyPzE(wjet2_fromHadTop.obj.px(),wjet2_fromHadTop.obj.py(), 0. ,wjet2_fromHadTop.obj.pt());
		    
		    w_fromHadTop_tlv = wjet1_fromHadTop_tlv + wjet2_fromHadTop_tlv;
		    w_fromHadTop_T_tlv = wjet1_fromHadTop_T_tlv + wjet2_fromHadTop_T_tlv;
		    
		    if (w_fromHadTop_tlv.M() > 120 ) continue; 
		    
		    hadTop_tlv = w_fromHadTop_tlv + bjet_fromHadTop_tlv;
		    hadTop_T_tlv = w_fromHadTop_T_tlv + bjet_fromHadTop_T_tlv;
		    
		    if ( hadTop_tlv.M() > 220 ) continue;

		    wjet1_fromHiggs_count = -1;
		    for (const auto & wjet1_fromHiggs : *jets_in)
		      {
			wjet1_fromHiggs_count +=1;
			
			if (wjet1_fromHiggs_count == bjet_fromLepTop_count) continue;
			if (wjet1_fromHiggs_count == bjet_fromHadTop_count) continue;
			if (wjet1_fromHiggs_count == wjet1_fromHadTop_count) continue;
			if (wjet1_fromHiggs_count == wjet2_fromHadTop_count) continue;
			
			wjet1_fromHiggs_tlv.SetPxPyPzE(wjet1_fromHiggs.obj.px(),wjet1_fromHiggs.obj.py(),wjet1_fromHiggs.obj.pz(),wjet1_fromHiggs.obj.E());
			wjet1_fromHiggs_T_tlv.SetPxPyPzE(wjet1_fromHiggs.obj.px(),wjet1_fromHiggs.obj.py(), 0. ,wjet1_fromHiggs.obj.pt());
			
			wjet2_fromHiggs_count = -1;
			for (const auto & wjet2_fromHiggs : *jets_in)
			  {
			    wjet2_fromHiggs_count +=1;
			    
			    if (wjet2_fromHiggs_count == bjet_fromLepTop_count) continue;
			    if (wjet2_fromHiggs_count == bjet_fromHadTop_count) continue;
			    if (wjet2_fromHiggs_count == wjet1_fromHadTop_count) continue;
			    if (wjet2_fromHiggs_count == wjet2_fromHadTop_count) continue;
			    if (wjet2_fromHiggs_count <= wjet1_fromHiggs_count) continue;
			    
			    wjet2_fromHiggs_tlv.SetPxPyPzE(wjet2_fromHiggs.obj.px(),wjet2_fromHiggs.obj.py(),wjet2_fromHiggs.obj.pz(),wjet2_fromHiggs.obj.E());
			    wjet2_fromHiggs_T_tlv.SetPxPyPzE(wjet2_fromHiggs.obj.px(),wjet2_fromHiggs.obj.py(), 0. ,wjet2_fromHiggs.obj.pt());
			    
			    w_fromHiggs_tlv = wjet1_fromHiggs_tlv + wjet2_fromHiggs_tlv;
			    w_fromHiggs_T_tlv = wjet1_fromHiggs_T_tlv + wjet2_fromHiggs_T_tlv;
			    
			    if (w_fromHiggs_tlv.M() > 120 ) continue; 
			    
			    //////////////////////////////////////////////////////////////////////////////
			    
			    lep_fromTop_count = -1;
			    for (const auto & lep_fromTop : *leptons_in)
			      {
				lep_fromTop_count +=1;
				
				lep_fromTop_tlv.SetPxPyPzE(lep_fromTop.obj.px(),lep_fromTop.obj.py(),lep_fromTop.obj.pz(),lep_fromTop.obj.E());
				lep_fromTop_T_tlv.SetPxPyPzE(lep_fromTop.obj.px(),lep_fromTop.obj.py(), 0. ,lep_fromTop.obj.pt());
				
				lep_fromHiggs_count = -1;
				for (const auto & lep_fromHiggs : *leptons_in)
				  {
				    lep_fromHiggs_count +=1;  
				    if (lep_fromTop_count == lep_fromHiggs_count) continue;
				    
				    lep_fromHiggs_tlv.SetPxPyPzE(lep_fromHiggs.obj.px(),lep_fromHiggs.obj.py(),lep_fromHiggs.obj.pz(),lep_fromHiggs.obj.E());
				    lep_fromHiggs_T_tlv.SetPxPyPzE(lep_fromHiggs.obj.px(),lep_fromHiggs.obj.py(), 0. ,lep_fromHiggs.obj.pt());
				    
				    lepTop_tlv = lep_fromTop_tlv + bjet_fromLepTop_tlv;
				    lepTop_T_tlv = lep_fromTop_T_tlv + bjet_fromLepTop_T_tlv;
				    
				    if ( lepTop_tlv.M() > 180 ) continue;
				    

				    higgs_tlv = w_fromHiggs_tlv + lep_fromHiggs_tlv;
				    higgs_T_tlv = w_fromHiggs_T_tlv + lep_fromHiggs_T_tlv;
				    
				    if (higgs_tlv.M() > 130 ) continue; 
				    
				    lepTop_higgs_tlv = higgs_tlv + lepTop_tlv;
				    lepTop_higgs_T_tlv = higgs_T_tlv + lepTop_T_tlv;
				    
				    hadTop_higgs_tlv = higgs_tlv + hadTop_tlv;
				    hadTop_higgs_T_tlv = higgs_T_tlv + hadTop_T_tlv;
				    
				    lepTop_hadTop_tlv = hadTop_tlv + lepTop_tlv;
				    lepTop_hadTop_T_tlv = hadTop_T_tlv + lepTop_T_tlv;
				    
				    tth_tlv = higgs_tlv + hadTop_tlv + lepTop_tlv;
				    tth_T_tlv = higgs_T_tlv + hadTop_T_tlv + lepTop_T_tlv;
				    
				    
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
				    numMatchedJets_var =  ( (bjet_fromHadTop.obj.pt() > 0)
							    + (bjet_fromLepTop.obj.pt() > 0)
							    + (wjet1_fromHadTop.obj.pt() > 0)
							    + (wjet2_fromHadTop.obj.pt() > 0)
							    + (wjet1_fromHiggs.obj.pt() > 0)
							    + (wjet2_fromHiggs.obj.pt() > 0)
							    );
				    LepTop_Higgs_mass_var = lepTop_higgs_tlv.M();
				    HadTop_Higgs_mass_var = hadTop_higgs_tlv.M();
				    LepTop_HadTop_MT_var = lepTop_hadTop_T_tlv.M();
				    LepTop_Higgs_MT_var = lepTop_higgs_T_tlv.M();
				    ttH_MT_var = tth_T_tlv.M();
				    HadTop_Higgs_MT_mass_ratio_var = hadTop_higgs_T_tlv.M() / hadTop_higgs_tlv.M();
				    ttH_MT_mass_ratio_var = tth_T_tlv.M()/tth_tlv.M();
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
				    lepTop_charge_var = lep_fromTop_truth.charge + bjet_fromLepTop.charge;
				    hadTop_charge_var = bjet_fromHadTop.charge + W_fromHadTop_charge_var;
				    Higgs_charge_var = lep_charge_var + W_fromHiggs_charge_var;
				    ttH_charge_var = lepTop_charge_var + hadTop_charge_var + Higgs_charge_var;
				    bJet_fromHadTop_charge_correct_var = (bjet_fromHadTop.charge != 0.) ? (bJet_fromHadTop_charge_var*lep_charge_var > 0) : -1;
				    bJet_fromLepTop_charge_correct_var = (bjet_fromHadTop.charge != 0.) ? (bJet_fromLepTop_charge_var*lep_charge_var < 0) : -1;
				    W_fromHadTop_charge_correct_var = (W_fromHadTop_charge_var*lep_charge_var < 0);
				    W_fromHiggs_charge_correct_var = (W_fromHiggs_charge_var*lep_charge_var < 0);
				    
				    LepAsym_var = (lep_fromTop.obj.pt()-lep_fromHiggs.obj.pt())/(lep_fromTop.obj.pt()+lep_fromHiggs.obj.pt());

				    double mva_value = TMVAReader_->EvaluateMVA( "BDTG method" );
				    //				    reco_scores_intree->push_back( mva_value );
				    norm_score_sum += mva_value;
				    if ( mva_value > reco_score )
				      {
					reco_score = mva_value;
					matched_jets.clear();
					

					lep_fromTop_bdt = lep_fromTop;
					lep_fromHiggs_bdt = lep_fromHiggs;

					matched_jets.push_back(bjet_fromHadTop);
					matched_jets.push_back(bjet_fromLepTop);
					matched_jets.push_back(wjet1_fromHadTop);
					matched_jets.push_back(wjet2_fromHadTop);
					matched_jets.push_back(wjet1_fromHiggs);
					matched_jets.push_back(wjet2_fromHiggs);
					
					
					lep_fromTop_bdt_tlv = lep_fromTop_tlv;
					lep_fromHiggs_bdt_tlv = lep_fromHiggs_tlv;
					bjet_fromHadTop_bdt_tlv = bjet_fromHadTop_tlv;
					bjet_fromLepTop_bdt_tlv = bjet_fromLepTop_tlv;
					wjet1_fromHadTop_bdt_tlv = wjet1_fromHadTop_tlv;    
					wjet2_fromHadTop_bdt_tlv = wjet2_fromHadTop_tlv;
					wjet1_fromHiggs_bdt_tlv = wjet1_fromHiggs_tlv;  
					wjet2_fromHiggs_bdt_tlv = wjet2_fromHiggs_tlv;
					w_fromHadTop_bdt_tlv = w_fromHadTop_tlv;    
					w_fromHiggs_bdt_tlv = w_fromHiggs_tlv;
					higgs_bdt_tlv = higgs_tlv;
					hadTop_bdt_tlv = hadTop_tlv;
					lepTop_bdt_tlv = lepTop_tlv;
					lepTop_higgs_bdt_tlv = lepTop_higgs_tlv;
					hadTop_higgs_bdt_tlv = hadTop_higgs_tlv;
					lepTop_hadTop_bdt_tlv = lepTop_hadTop_tlv;
					tth_bdt_tlv = tth_tlv;


					/* w_fromHadTop_tlv_intree = w_fromHadTop_tlv; */
					/* w_fromHiggs_tlv_intree = w_fromHiggs_tlv; */
					/* higgs_tlv_intree = higgs_tlv; */
					/* hadTop_tlv_intree = hadTop_tlv; */
					/* lepTop_tlv_intree = lepTop_tlv; */
					
					/* dR_b_W_hadTop_intree = bjet_fromHadTop_tlv.DeltaR( w_fromHadTop_tlv ); */
					/* dR_b_W_lepTop_intree = bjet_fromLepTop_tlv.DeltaR( lep_fromTop_tlv ); */
					/* dR_H_lepTop_intree = higgs_tlv.DeltaR( lepTop_tlv ); */
					/* dR_H_hadTop_intree = higgs_tlv.DeltaR( hadTop_tlv ); */
					/* dR_lepTop_hadTop_intree = hadTop_tlv.DeltaR( lepTop_tlv ); */
					/* dR_W1_W2_fromHiggs_intree = w_fromHiggs_tlv.DeltaR( lep_fromHiggs_tlv ); */
					/* dR_q1_q2_fromWfromHiggs_intree = wjet1_fromHiggs_tlv.DeltaR( wjet2_fromHiggs_tlv ); */
					
				      }
				  }
			      }
			  }
		      }
		  }
	      }
	  }
      }

    norm_score_sum = norm_score_sum/jets_in->size();


    ttH::Jet bjet_fromHadTop = matched_jets[0];
    ttH::Jet bjet_fromLepTop = matched_jets[1];
    ttH::Jet wjet1_fromHadTop = matched_jets[2];
    ttH::Jet wjet2_fromHadTop = matched_jets[3];
    ttH::Jet wjet1_fromHiggs = matched_jets[4];
    ttH::Jet wjet2_fromHiggs = matched_jets[5];

    ////
    //// matching results legened:
    ////  5 = correct matched to real truth object
    ////  4 = correctly matched to null truth object
    ////  3 = incorrectly matched real object to real truth object
    ////  2 = incorrectly matched real object to null truth object 
    ////  1 = incorrectly matched null object to real truth object
    ////

    //leptons
    if (lep_fromTop_bdt.obj.pt() == lep_fromTop_truth.obj.pt())	matching_results.push_back(5);
    else matching_results.push_back(3);

    
    //bjet from hadronic top
    if (bjet_fromHadTop.obj.pt() > 0)
      {
	num_real_jets_bdt +=1;
	if (bjet_fromHadTop.obj.pt() == bjet_fromHadTop_truth.obj.pt()) matching_results.push_back(5);
	else if (bjet_fromHadTop_truth.obj.pt() > 0) matching_results.push_back(3); 
	else matching_results.push_back(2);
      }
    else
      {
	if (bjet_fromHadTop.obj.pt() == bjet_fromHadTop_truth.obj.pt()) matching_results.push_back(4);
	else matching_results.push_back(1);
      }
    
    //bjet from leptonic top
    if (bjet_fromLepTop.obj.pt() > 0)
      {
	num_real_jets_bdt +=1;
	if (bjet_fromLepTop.obj.pt() == bjet_fromLepTop_truth.obj.pt()) matching_results.push_back(5);
	else if (bjet_fromLepTop_truth.obj.pt() > 0) matching_results.push_back(3); 
	else matching_results.push_back(2);
      }
    else
      {
	if (bjet_fromLepTop.obj.pt() == bjet_fromLepTop_truth.obj.pt()) matching_results.push_back(4);
	else matching_results.push_back(1);
      }
    
    //wjet1 from hadronic top
    if (wjet1_fromHadTop.obj.pt() > 0)
      {
	num_real_jets_bdt +=1;
	if (wjet1_fromHadTop.obj.pt() == wjet1_fromHadTop_truth.obj.pt() || wjet1_fromHadTop.obj.pt() == wjet2_fromHadTop_truth.obj.pt()) matching_results.push_back(5);
	else if (wjet1_fromHadTop_truth.obj.pt() > 0 || wjet2_fromHadTop_truth.obj.pt() > 0) matching_results.push_back(3); 
	else matching_results.push_back(2);
      }
    else
      {
	if (wjet1_fromHadTop.obj.pt() == wjet1_fromHadTop_truth.obj.pt() || wjet1_fromHadTop.obj.pt() == wjet2_fromHadTop_truth.obj.pt()) matching_results.push_back(4);
	else matching_results.push_back(1);
      }
    //wjet2 from hadronic top
    if (wjet2_fromHadTop.obj.pt() > 0)
      {
	num_real_jets_bdt +=1;
	if (wjet2_fromHadTop.obj.pt() == wjet2_fromHadTop_truth.obj.pt() || wjet2_fromHadTop.obj.pt() == wjet1_fromHadTop_truth.obj.pt()) matching_results.push_back(5);
	else if (wjet2_fromHadTop_truth.obj.pt() > 0 || wjet1_fromHadTop_truth.obj.pt() > 0) matching_results.push_back(3); 
	else matching_results.push_back(2);
      }
    else
      {
	if (wjet2_fromHadTop.obj.pt() == wjet2_fromHadTop_truth.obj.pt() || wjet2_fromHadTop.obj.pt() == wjet1_fromHadTop_truth.obj.pt()) matching_results.push_back(4);
	else matching_results.push_back(1);
      }
    
    //wjet1 from higgs
    if (wjet1_fromHiggs.obj.pt() > 0)
      {
	num_real_jets_bdt +=1;
	if (wjet1_fromHiggs.obj.pt() == wjet1_fromHiggs_truth.obj.pt() || wjet1_fromHiggs.obj.pt() == wjet2_fromHiggs_truth.obj.pt()) matching_results.push_back(5);
	else if (wjet1_fromHiggs_truth.obj.pt() > 0 || wjet2_fromHiggs_truth.obj.pt() > 0) matching_results.push_back(3); 
	else matching_results.push_back(2);
      }
    else
      {
	if (wjet1_fromHiggs.obj.pt() == wjet1_fromHiggs_truth.obj.pt() || wjet1_fromHiggs.obj.pt() == wjet2_fromHiggs_truth.obj.pt()) matching_results.push_back(4);
	else matching_results.push_back(1);
      }
    //wjet2 from higgs
    if (wjet2_fromHiggs.obj.pt() > 0)
      {
	num_real_jets_bdt +=1;
	if (wjet2_fromHiggs.obj.pt() == wjet2_fromHiggs_truth.obj.pt() || wjet2_fromHiggs.obj.pt() == wjet1_fromHiggs_truth.obj.pt()) matching_results.push_back(5);
	else if (wjet2_fromHiggs_truth.obj.pt() > 0 || wjet1_fromHiggs_truth.obj.pt() > 0) matching_results.push_back(3); 
	else matching_results.push_back(2);
      }
    else
      {
	if (wjet2_fromHiggs.obj.pt() == wjet2_fromHiggs_truth.obj.pt() || wjet2_fromHiggs.obj.pt() == wjet1_fromHiggs_truth.obj.pt()) matching_results.push_back(4);
	else matching_results.push_back(1);
      }
    
  }
  
  //  virtual ~eventReconstructor(){};
};

#endif // _eventReconstructor_h
