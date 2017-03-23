#ifndef _signalExtractionTreeMaker_h
#define _signalExtractionTreeMaker_h

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
#include "TMVA/Config.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#include <cmath>
#include "TLorentzVector.h"
  
class signalExtractionTreeMaker
{
 private:
  Float_t max_lep_eta_branch;
  Float_t njets_branch;
  Float_t dR_l1_j_branch;
  Float_t dR_l2_j_branch;
  Float_t met_branch;
  Float_t avg_dr_jets_branch;
  Float_t mt_lep1_met_branch;
  Float_t l1_pt_branch;
  Float_t l2_pt_branch;
  Float_t reco_score_branch;
  Float_t hadtop_mass_branch;
  Float_t hj_branch;

  //final sig extraction stuff
  TMVA::Reader* TMVAReader_ttbar_;
  TMVA::Reader* TMVAReader_ttbar_recoBdt_;
  TMVA::Reader* TMVAReader_ttbar_recoBdt_bLoose_;
  TMVA::Reader* TMVAReader_ttbar_recoBdt_bTight_;

  TMVA::Reader* TMVAReader_ttV_;
  Float_t spec0_var;
  Float_t spec1_var;
  Float_t spec2_var;
  double vs_ttbar_score; //traditional
  double vs_ttbar_bdtReco_score; //btight-btight, bloose-bloose
  double vs_ttbar_bdtReco_bti_blbl_score; //btight-incl, bloose-bloose this is what you found originally worked well
  double vs_ttbar_bdtReco_bti_bli_score; //btight-incl, bloose-incl
  double vs_ttv_score;
  bool evaluate_signal_extraction = false;
  bool isBtight_branch=false;
  bool isPositive_branch=false;
  bool isTau_branch=false;
  TString flavor_branch = "null";

 public:
  signalExtractionTreeMaker(TTree *ttbar_tree, TTree *ttv_tree, TTree *ss2l_tree, bool evaluateSignalExtraction){
    
    ttbar_tree->Branch("max_Lep_eta", &max_lep_eta_branch);
    ttbar_tree->Branch("numJets_float", &njets_branch);
    ttbar_tree->Branch("mindr_lep1_jet", &dR_l1_j_branch);
    ttbar_tree->Branch("mindr_lep2_jet", &dR_l2_j_branch);
    ttbar_tree->Branch("met_double", &met_branch);  
    ttbar_tree->Branch("avg_dr_jet", &avg_dr_jets_branch);
    ttbar_tree->Branch("MT_met_lep1", &mt_lep1_met_branch);

    ttv_tree->Branch("max_Lep_eta", &max_lep_eta_branch);
    ttv_tree->Branch("numJets_float", &njets_branch);
    ttv_tree->Branch("mindr_lep1_jet", &dR_l1_j_branch);
    ttv_tree->Branch("mindr_lep2_jet", &dR_l2_j_branch);
    ttv_tree->Branch("MT_met_lep1", &mt_lep1_met_branch);
    ttv_tree->Branch("l1_pt", &l1_pt_branch);
    ttv_tree->Branch("l2_pt", &l2_pt_branch);

    if ( evaluateSignalExtraction )
      {
	evaluate_signal_extraction = true;

	ttbar_tree->Branch("reco_score", &reco_score_branch);
	ss2l_tree->Branch("vs_ttbar_score", &vs_ttbar_score);
	ss2l_tree->Branch("vs_ttbar_withRecoBdt_score", &vs_ttbar_bdtReco_score);

	ss2l_tree->Branch("vs_ttbar_withRecoBdt_bti_blbl_score", &vs_ttbar_bdtReco_bti_blbl_score);
	ss2l_tree->Branch("vs_ttbar_withRecoBdt_bti_bli_score", &vs_ttbar_bdtReco_bti_bli_score);

	ss2l_tree->Branch("vs_ttv_score", &vs_ttv_score);
	ss2l_tree->Branch("bTight_category", &isBtight_branch);
	ss2l_tree->Branch("posCharge_category", &isPositive_branch);
	ss2l_tree->Branch("tau_category", &isTau_branch);
	ss2l_tree->Branch("flavor_category", &flavor_branch);
	
	TMVAReader_ttbar_ = new TMVA::Reader( "!Color:!Silent" );
	TMVAReader_ttbar_->AddVariable( "max(abs(LepGood_eta[iLepFO_Recl[0]]),abs(LepGood_eta[iLepFO_Recl[1]]))", &max_lep_eta_branch );
	TMVAReader_ttbar_->AddVariable( "nJet25_Recl", &njets_branch );
	TMVAReader_ttbar_->AddVariable( "mindr_lep1_jet", &dR_l1_j_branch );
	TMVAReader_ttbar_->AddVariable( "mindr_lep2_jet", &dR_l2_j_branch );
	TMVAReader_ttbar_->AddVariable( "MT_met_lep1", &mt_lep1_met_branch );
	TMVAReader_ttbar_->AddSpectator( "iLepFO_Recl[0]", &spec0_var );
	TMVAReader_ttbar_->AddSpectator( "iLepFO_Recl[1]", &spec1_var );
	TMVAReader_ttbar_->AddSpectator( "iLepFO_Recl[2]", &spec2_var );
	TString ttbar_weights = "../../simpleweights/moriond17_signalExtraction/2lss_ttbar_BDTG.weights.xml";
	/* TMVAReader_ttbar_->AddVariable( "max_Lep_eta", &max_lep_eta_branch ); */
	/* TMVAReader_ttbar_->AddVariable( "numJets_float", &njets_branch ); */
	/* TMVAReader_ttbar_->AddVariable( "mindr_lep1_jet", &dR_l1_j_branch ); */
	/* TMVAReader_ttbar_->AddVariable( "mindr_lep2_jet", &dR_l2_j_branch ); */
	/* TMVAReader_ttbar_->AddVariable( "MT_met_lep1", &mt_lep1_met_branch ); */
	/* TMVAReader_ttbar_->AddVariable( "met_double", &met_branch ); */
	/* TMVAReader_ttbar_->AddVariable( "avg_dr_jet", &avg_dr_jets_branch ); */
	/* TString ttbar_weights = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_20/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/weights/TMVAClassification_BDTG_jan25_ICHEP.weights.xml"; */

	TMVAReader_ttbar_->BookMVA("BDTG method", ttbar_weights);
	
	TMVAReader_ttbar_recoBdt_ = new TMVA::Reader( "!Color:!Silent" );
	TMVAReader_ttbar_recoBdt_->AddVariable( "max_Lep_eta", &max_lep_eta_branch );
	TMVAReader_ttbar_recoBdt_->AddVariable( "numJets_float", &njets_branch );
	TMVAReader_ttbar_recoBdt_->AddVariable( "mindr_lep1_jet", &dR_l1_j_branch );
	TMVAReader_ttbar_recoBdt_->AddVariable( "mindr_lep2_jet", &dR_l2_j_branch );
	TMVAReader_ttbar_recoBdt_->AddVariable( "MT_met_lep1", &mt_lep1_met_branch );
	TMVAReader_ttbar_recoBdt_->AddVariable( "met_double", &met_branch );
	TMVAReader_ttbar_recoBdt_->AddVariable( "avg_dr_jet", &avg_dr_jets_branch );
	TMVAReader_ttbar_recoBdt_->AddVariable( "reco_score", &reco_score_branch );
	//TMVAReader_ttbar_recoBdt_->AddVariable( "hadTop_bdt.M()", &hadtop_mass_branch );
	//TString ttbar_recoBdt_weights = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/weights/TMVAClassification_BDTG.weights_ichepTraining_withRecoBdt.xml";
	TString ttbar_recoBdt_weights = "../../simpleweights/reconstruction_bdt_weights/weights/TMVAClassification_BDTG.weights_ichepTraining_withFactorizedRecoBdt.xml";
	//TString ttbar_recoBdt_weights = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_20/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/weights/TMVAClassification_BDTG_jan25_v1_incl.weights.xml";
	//TString ttbar_recoBdt_weights = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_20/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/weights/TMVAClassification_BDTG_jan25_ICHEP_reco_incl.weights.xml";
	TMVAReader_ttbar_recoBdt_->BookMVA("BDTG method", ttbar_recoBdt_weights);
	
	TMVAReader_ttbar_recoBdt_bLoose_ = new TMVA::Reader( "!Color:!Silent" );
	TMVAReader_ttbar_recoBdt_bLoose_->AddVariable( "max_Lep_eta", &max_lep_eta_branch );
	TMVAReader_ttbar_recoBdt_bLoose_->AddVariable( "numJets_float", &njets_branch );
	TMVAReader_ttbar_recoBdt_bLoose_->AddVariable( "mindr_lep1_jet", &dR_l1_j_branch );
	TMVAReader_ttbar_recoBdt_bLoose_->AddVariable( "mindr_lep2_jet", &dR_l2_j_branch );
	TMVAReader_ttbar_recoBdt_bLoose_->AddVariable( "MT_met_lep1", &mt_lep1_met_branch );
	TMVAReader_ttbar_recoBdt_bLoose_->AddVariable( "met_double", &met_branch );
	TMVAReader_ttbar_recoBdt_bLoose_->AddVariable( "avg_dr_jet", &avg_dr_jets_branch );
	TMVAReader_ttbar_recoBdt_bLoose_->AddVariable( "reco_score", &reco_score_branch );
	//TMVAReader_ttbar_recoBdt_bLoose_->AddVariable( "hadTop_bdt.M()", &hadtop_mass_branch );
	//TString ttbar_recoBdt_bLoose_weights = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/weights/TMVAClassification_BDTG.weights_ichepTraining_withRecoBdt_bloose.xml";
	TString ttbar_recoBdt_bLoose_weights = "../../simpleweights/reconstruction_bdt_weights/weights/TMVAClassification_BDTG.weights_ichepTraining_withFactorizedRecoBdt_bloose.xml";
	//TString ttbar_recoBdt_bLoose_weights = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_20/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/weights/TMVAClassification_BDTG_jan25_v1_bloose.weights.xml";
	//TString ttbar_recoBdt_bLoose_weights = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_20/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/weights/TMVAClassification_BDTG_jan25_ICHEP_reco_bLoose.weights.xml";
	TMVAReader_ttbar_recoBdt_bLoose_->BookMVA("BDTG method", ttbar_recoBdt_bLoose_weights);
	
	TMVAReader_ttbar_recoBdt_bTight_ = new TMVA::Reader( "!Color:!Silent" );
	TMVAReader_ttbar_recoBdt_bTight_->AddVariable( "max_Lep_eta", &max_lep_eta_branch );
	TMVAReader_ttbar_recoBdt_bTight_->AddVariable( "numJets_float", &njets_branch );
	TMVAReader_ttbar_recoBdt_bTight_->AddVariable( "mindr_lep1_jet", &dR_l1_j_branch );
	TMVAReader_ttbar_recoBdt_bTight_->AddVariable( "mindr_lep2_jet", &dR_l2_j_branch );
	TMVAReader_ttbar_recoBdt_bTight_->AddVariable( "MT_met_lep1", &mt_lep1_met_branch );
	TMVAReader_ttbar_recoBdt_bTight_->AddVariable( "met_double", &met_branch );
	TMVAReader_ttbar_recoBdt_bTight_->AddVariable( "avg_dr_jet", &avg_dr_jets_branch );
	TMVAReader_ttbar_recoBdt_bTight_->AddVariable( "reco_score", &reco_score_branch );
	//	TMVAReader_ttbar_recoBdt_bTight_->AddVariable( "hadTop_bdt.M()", &hadtop_mass_branch );
	//TString ttbar_recoBdt_bTight_weights = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/weights/TMVAClassification_BDTG.weights_ichepTraining_withRecoBdt_btight.xml";
	TString ttbar_recoBdt_bTight_weights = "../../simpleweights/reconstruction_bdt_weights/weights/TMVAClassification_BDTG.weights_ichepTraining_withFactorizedRecoBdt_btight.xml";
	//TString ttbar_recoBdt_bTight_weights = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_20/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/weights/TMVAClassification_BDTG_jan25_v1_btight.weights.xml";
	//TString ttbar_recoBdt_bTight_weights = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_20/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/weights/TMVAClassification_BDTG_jan25_ICHEP_reco_bTight.weights.xml";
	TMVAReader_ttbar_recoBdt_bTight_->BookMVA("BDTG method", ttbar_recoBdt_bTight_weights);
	
	TMVAReader_ttV_ = new TMVA::Reader( "!Color:!Silent" );
	TMVAReader_ttV_->AddVariable( "max(abs(LepGood_eta[iLepFO_Recl[0]]),abs(LepGood_eta[iLepFO_Recl[1]]))", &max_lep_eta_branch );
	TMVAReader_ttV_->AddVariable( "nJet25_Recl", &njets_branch );
	TMVAReader_ttV_->AddVariable( "mindr_lep1_jet", &dR_l1_j_branch );
	TMVAReader_ttV_->AddVariable( "mindr_lep2_jet", &dR_l2_j_branch );
	TMVAReader_ttV_->AddVariable( "MT_met_lep1", &mt_lep1_met_branch );
	TMVAReader_ttV_->AddVariable( "LepGood_conePt[iLepFO_Recl[1]]", &l2_pt_branch );
	TMVAReader_ttV_->AddVariable( "LepGood_conePt[iLepFO_Recl[0]]", &l1_pt_branch );
	TMVAReader_ttV_->AddVariable( "max(-1.1,BDTv8_eventReco_Hj_score)", &hj_branch );
	TMVAReader_ttV_->AddSpectator( "iLepFO_Recl[0]", &spec0_var );
	TMVAReader_ttV_->AddSpectator( "iLepFO_Recl[1]", &spec1_var );
	TMVAReader_ttV_->AddSpectator( "iLepFO_Recl[2]", &spec2_var );
	TString ttV_weights = "../../simpleweights/moriond17_signalExtraction/2lss_ttV_withHj_BDTG.weights.xml";
	TMVAReader_ttV_->BookMVA("BDTG method", ttV_weights);	
      }
    
    //add friends
    ttbar_tree->AddFriend(ss2l_tree);
    ttv_tree->AddFriend(ss2l_tree);

  } // default constructor

  void clear(void)
  {
    max_lep_eta_branch = -99.;
    njets_branch = -99.;
    dR_l1_j_branch = -99.;
    dR_l2_j_branch = -99.;
    met_branch = -99.;
    avg_dr_jets_branch = -99.;
    mt_lep1_met_branch = -99.;
    l1_pt_branch = -99.;
    l2_pt_branch = -99.;
    hj_branch = -2.;
  }

  void initialize(vector<ttH::Jet> *jets_input, const vector<ttH::Lepton> *leptons_in, const ttH::MET met_in, vector<ttH::Tau> *taus_in, eventReconstructor bdtReconstructor, hTagger higgsJetTagger)
  {
    clear(); //reset all output vars

    // max eta
    max_lep_eta_branch = -1.;
    for (const auto & lep: *leptons_in)
      {
	if (abs(lep.obj.eta()) > max_lep_eta_branch)
	  {
	    max_lep_eta_branch = abs(lep.obj.eta());
	  }
      }
    
    // njets
    njets_branch = jets_input->size();
    
    // find highest pt leptons
    ttH::Lepton lep1;
    ttH::Lepton lep2;
    //if ((*leptons_in)[0].obj.pt() > (*leptons_in)[1].obj.pt())

    if ((*leptons_in)[0].correctedPt > (*leptons_in)[1].correctedPt)
      {
	lep1 = (*leptons_in)[0];
	lep2 = (*leptons_in)[1];
      }
    else
      {
	lep1 = (*leptons_in)[1];
	lep2 = (*leptons_in)[0];
      }

    l1_pt_branch = lep1.correctedPt;
    l2_pt_branch = lep2.correctedPt;
    
    ttH::Jet lep1_closest_jet = getClosestJet(*jets_input, lep1);
    ttH::Jet lep2_closest_jet = getClosestJet(*jets_input, lep2);
    dR_l1_j_branch = getDeltaR(lep1_closest_jet, lep1);
    dR_l2_j_branch = getDeltaR(lep2_closest_jet, lep2);
    
    // met
    met_branch = min(met_in.obj.Pt(),400.);

    TLorentzVector met_tlv = setTlv( met_in );
    TLorentzVector lep1_t_tlv = setTlv( lep1 );
    
    mt_lep1_met_branch = sqrt(2*lep1.correctedPt*met_branch*(1-cos(lep1.obj.phi()- met_in.obj.phi() )));

    //calculate avg dr jets
    int jet1_counter = 0;
    double dr_sum = 0.;
    int dr_denom = 0;
    int num_tight = 0;
    for (const auto & jet1 : *jets_input)
      {
	if ( jet1.csv >= 0.8 ) num_tight +=1;
	int jet2_counter = -1;
	for (const auto & jet2 : *jets_input)
	  {
	    jet2_counter +=1;
	    if ( jet2_counter <= jet1_counter ) continue;
	    double delta_r = getDeltaR(jet1, jet2);
	    dr_sum += delta_r;
	    dr_denom +=1;
	  }
	jet1_counter +=1;
      }
    avg_dr_jets_branch = dr_sum/double(dr_denom);

    reco_score_branch = bdtReconstructor.reco_score_intree;
    hadtop_mass_branch = bdtReconstructor.hadTop_tlv_bdt_intree.M();
    bool zero_hadtop_nulls = (bdtReconstructor.b_from_hadtop_bdt_intree->obj.pt()
			      *bdtReconstructor.q1_from_hadtop_bdt_intree->obj.pt()
			      *bdtReconstructor.q2_from_hadtop_bdt_intree->obj.pt() > 0);

    if ( evaluate_signal_extraction )
      {
	
	isBtight_branch = ( num_tight > 1 );	
	isPositive_branch =  (lep1.charge > 0 );
	isTau_branch = ( taus_in->size() > 0 );

	if (abs( lep1.pdgID ) == 11 && abs( lep2.pdgID ) == 11) flavor_branch = "ee";
	else if (abs(lep1.pdgID) == 13 && abs(lep2.pdgID) == 13) flavor_branch = "mm";
	else flavor_branch = "em";


	vs_ttbar_score = TMVAReader_ttbar_->EvaluateMVA( "BDTG method" );
	vs_ttbar_bdtReco_bti_bli_score = TMVAReader_ttbar_recoBdt_->EvaluateMVA( "BDTG method" ); 

	if ( isBtight_branch )
	  {
	    //vs_ttbar_bdtReco_score = TMVAReader_ttbar_recoBdt_->EvaluateMVA( "BDTG method" );
	    vs_ttbar_bdtReco_score = TMVAReader_ttbar_recoBdt_bTight_->EvaluateMVA( "BDTG method" );
	    vs_ttbar_bdtReco_bti_blbl_score = TMVAReader_ttbar_recoBdt_->EvaluateMVA( "BDTG method" );
	  }
	else
	  {
	    vs_ttbar_bdtReco_score = TMVAReader_ttbar_recoBdt_bLoose_->EvaluateMVA( "BDTG method" );
	    vs_ttbar_bdtReco_bti_blbl_score = TMVAReader_ttbar_recoBdt_bLoose_->EvaluateMVA( "BDTG method" );
	  }


	hj_branch = max(-1.1, higgsJetTagger.hj_bdt_scores_intree->at(0));

	vs_ttv_score = TMVAReader_ttV_->EvaluateMVA( "BDTG method" );

      }


  }
  
  //  virtual ~signalExtractionTreeMaker(){};
};

#endif // _signalExtractionTreeMaker_h
