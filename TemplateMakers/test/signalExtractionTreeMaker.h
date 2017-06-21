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
#include "GetBinning.C"
  
class signalExtractionTreeMaker
{
 private:
  Float_t max_lep_eta_branch;
  Float_t njets_branch;
  Float_t dR_l1_j_branch;
  Float_t dR_l2_j_branch;
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
  double vs_ttbar_score;
  double vs_ttbar_bdtReco_score;
  double vs_ttv_score;
  Int_t final_shape;
  Int_t final_shape_BDTv8;

 public:
  signalExtractionTreeMaker(TTree *ss2l_tree){
    
    ss2l_tree->Branch("max_Lep_eta", &max_lep_eta_branch);
    ss2l_tree->Branch("numJets_float", &njets_branch);
    ss2l_tree->Branch("mindr_lep1_jet", &dR_l1_j_branch);
    ss2l_tree->Branch("mindr_lep2_jet", &dR_l2_j_branch);
    ss2l_tree->Branch("MT_met_lep1", &mt_lep1_met_branch);
    ss2l_tree->Branch("l1_pt", &l1_pt_branch);
    ss2l_tree->Branch("l2_pt", &l2_pt_branch);
    ss2l_tree->Branch("vs_ttbar_score", &vs_ttbar_score);
    ss2l_tree->Branch("vs_ttbar_withRecoBdt_score", &vs_ttbar_bdtReco_score);
    ss2l_tree->Branch("vs_ttv_score", &vs_ttv_score);
    ss2l_tree->Branch("final_shape", &final_shape);
    ss2l_tree->Branch("final_shape_BDTv8", &final_shape_BDTv8);
    
    const std::string base = std::string(getenv("CMSSW_BASE")) + "/src/ttH-13TeVMultiLeptons/TemplateMakers/data/CERN/BDT_weights/moriond2017";
    
    TMVAReader_ttbar_ = new TMVA::Reader( "!Color:!Silent" );
    TMVAReader_ttbar_->AddVariable( "max(abs(LepGood_eta[iLepFO_Recl[0]]),abs(LepGood_eta[iLepFO_Recl[1]]))", &max_lep_eta_branch );
    TMVAReader_ttbar_->AddVariable( "nJet25_Recl", &njets_branch );
    TMVAReader_ttbar_->AddVariable( "mindr_lep1_jet", &dR_l1_j_branch );
    TMVAReader_ttbar_->AddVariable( "mindr_lep2_jet", &dR_l2_j_branch );
    TMVAReader_ttbar_->AddVariable( "MT_met_lep1", &mt_lep1_met_branch );
    TMVAReader_ttbar_->AddSpectator( "iLepFO_Recl[0]", &spec0_var );
    TMVAReader_ttbar_->AddSpectator( "iLepFO_Recl[1]", &spec1_var );
    TMVAReader_ttbar_->AddSpectator( "iLepFO_Recl[2]", &spec2_var );
    TMVAReader_ttbar_->BookMVA("BDTG method", base + "/2lss_ttbar_BDTG.weights.xml");
    
    TMVAReader_ttbar_recoBdt_ = new TMVA::Reader( "!Color:!Silent" );
    TMVAReader_ttbar_recoBdt_->AddVariable( "max(abs(LepGood_eta[iLepFO_Recl[0]]),abs(LepGood_eta[iLepFO_Recl[1]]))", &max_lep_eta_branch );
    TMVAReader_ttbar_recoBdt_->AddVariable( "nJet25_Recl", &njets_branch );
    TMVAReader_ttbar_recoBdt_->AddVariable( "mindr_lep1_jet", &dR_l1_j_branch );
    TMVAReader_ttbar_recoBdt_->AddVariable( "mindr_lep2_jet", &dR_l2_j_branch );
    TMVAReader_ttbar_recoBdt_->AddVariable( "MT_met_lep1", &mt_lep1_met_branch );
    TMVAReader_ttbar_recoBdt_->AddVariable( "max(-1.1,BDTv8_eventReco_mvaValue)", &reco_score_branch );
    TMVAReader_ttbar_recoBdt_->AddSpectator( "iLepFO_Recl[0]", &spec0_var );
    TMVAReader_ttbar_recoBdt_->AddSpectator( "iLepFO_Recl[1]", &spec1_var );
    TMVAReader_ttbar_recoBdt_->AddSpectator( "iLepFO_Recl[2]", &spec2_var );
    TMVAReader_ttbar_recoBdt_->BookMVA("BDTG method", base + "/2lss_ttbar_withBDTv8_BDTG.weights.xml");
    
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
    TMVAReader_ttV_->BookMVA("BDTG method", base + "/2lss_ttV_withHj_BDTG.weights.xml");
  } // default constructor

  void clear(void)
  {
    max_lep_eta_branch = -99.;
    njets_branch = -99.;
    dR_l1_j_branch = -99.;
    dR_l2_j_branch = -99.;
    mt_lep1_met_branch = -99.;
    l1_pt_branch = -99.;
    l2_pt_branch = -99.;
    hj_branch = -2.;
  }

  void initialize(vector<ttH::Jet> *jets_input, const vector<ttH::Lepton> *leptons_in, const ttH::MET met_in, eventReconstructor bdtReconstructor, hTagger higgsJetTagger)
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
    
    TLorentzVector met_tlv = setTlv( met_in );
    TLorentzVector lep1_t_tlv = setTlv( lep1 );
    
    double met_ = std::min(met_tlv.Pt(), 400.);

    mt_lep1_met_branch = sqrt(2*lep1.correctedPt*met_*(1-cos(lep1.obj.phi()- met_in.obj.phi() )));

    reco_score_branch = bdtReconstructor.reco_score_intree;
    hadtop_mass_branch = bdtReconstructor.hadTop_tlv_bdt_intree.M();
    bool zero_hadtop_nulls = (bdtReconstructor.b_from_hadtop_bdt_intree->obj.pt()
			      *bdtReconstructor.q1_from_hadtop_bdt_intree->obj.pt()
			      *bdtReconstructor.q2_from_hadtop_bdt_intree->obj.pt() > 0);

    
    vs_ttbar_score = max(-1.1,TMVAReader_ttbar_->EvaluateMVA( "BDTG method" ));
    vs_ttbar_bdtReco_score = TMVAReader_ttbar_recoBdt_->EvaluateMVA( "BDTG method" ); 
    hj_branch = max(-1.1, higgsJetTagger.hj_bdt_scores_intree->at(0));
    vs_ttv_score = TMVAReader_ttV_->EvaluateMVA( "BDTG method" );
    final_shape = OurBin2l(vs_ttbar_score,vs_ttv_score);
    final_shape_BDTv8 = OurBin2l(vs_ttbar_bdtReco_score,vs_ttv_score);
  }
  
  //  virtual ~signalExtractionTreeMaker(){};
};

#endif // _signalExtractionTreeMaker_h
