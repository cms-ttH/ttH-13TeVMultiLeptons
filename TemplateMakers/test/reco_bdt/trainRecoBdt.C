//Charlie Mueller 2/24/2016
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
#include "ttH-13TeVMultiLeptons/TemplateMakers/src/classes.h"
#include "TMVA/Config.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/test/selection.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/test/loadSamples.h"

/////////////////////////////////////////
///
/// usage: root -l trainRecoBdt.C+\(0,1\)
///
/////////////////////////////////////////


void run_it(TChain* chain, TString output_file)
{

  //  TMVA::Reader* TMVAReader_;
  Float_t num_jets_var;
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

  //not mva inputs...
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
  



  // TMVAReader_ = new TMVA::Reader( "!Color:!Silent" );
  // TMVAReader_->AddVariable( "numJets", &num_jets_var );
  // TMVAReader_->AddVariable( "bJet_fromLepTop_CSV", &bJet_fromLepTop_CSV_var );
  // TMVAReader_->AddVariable( "LepTop_pT", &LepTop_pT_var );
  // TMVAReader_->AddVariable( "LepTop_mass", &LepTop_mass_var );
  // TMVAReader_->AddVariable( "LepTop_lep_bJet_dR", &LepTop_lep_bJet_dR_var );
  // TMVAReader_->AddVariable( "bJet_fromHadTop_CSV", &bJet_fromHadTop_CSV_var );
  // TMVAReader_->AddVariable( "qJet1_fromW_fromHadTop_CSV", &qJet1_fromW_fromHadTop_CSV_var );
  // TMVAReader_->AddVariable( "qJet1_fromW_fromHadTop_pT", &qJet1_fromW_fromHadTop_pT_var );
  // TMVAReader_->AddVariable( "HadTop_pT", &HadTop_pT_var );
  // TMVAReader_->AddVariable( "W_fromHadTop_mass", &W_fromHadTop_mass_var );
  // TMVAReader_->AddVariable( "HadTop_mass", &HadTop_mass_var );
  // TMVAReader_->AddVariable( "W_fromHadTop_q1_q2_dR", &W_fromHadTop_q1_q2_dR_var );
  // TMVAReader_->AddVariable( "qJet1_fromW_fromHiggs_CSV", &qJet1_fromW_fromHiggs_CSV_var );
  // TMVAReader_->AddVariable( "lep_fromW_fromHiggs_pT", &lep_fromW_fromHiggs_pT_var );
  // TMVAReader_->AddVariable( "W_fromHiggs_mass", &W_fromHiggs_mass_var );
  // TMVAReader_->AddVariable( "Higgs_mass", &Higgs_mass_var );
  // TMVAReader_->AddVariable( "Higgs_lep_W_dR", &Higgs_lep_W_dR_var );
  // TMVAReader_->AddVariable( "Higgs_lep_W_dPhi", &Higgs_lep_W_dPhi_var );
  // TMVAReader_->AddVariable( "Higgs_lep_W_dEta", &Higgs_lep_W_dEta_var );
  // TMVAReader_->AddVariable( "numMatchedJets", &numMatchedJets_var );
  // TMVAReader_->AddVariable( "LepTop_Higgs_mass", &LepTop_Higgs_mass_var );
  // TMVAReader_->AddVariable( "HadTop_Higgs_mass", &HadTop_Higgs_mass_var );
  // TMVAReader_->AddVariable( "LepTop_HadTop_MT", &LepTop_HadTop_MT_var );
  // TMVAReader_->AddVariable( "LepTop_Higgs_MT", &LepTop_Higgs_MT_var );
  // TMVAReader_->AddVariable( "ttH_MT", &ttH_MT_var );
  // TMVAReader_->AddVariable( "HadTop_Higgs_MT_mass_ratio", &HadTop_Higgs_MT_mass_ratio_var );
  // TMVAReader_->AddVariable( "ttH_MT_mass_ratio", &ttH_MT_mass_ratio_var );
  // TMVAReader_->AddVariable( "LepTop_HadTop_dR", &LepTop_HadTop_dR_var );
  // TMVAReader_->AddVariable( "LepTop_HadTop_dPhi", &LepTop_HadTop_dPhi_var );
  // TMVAReader_->BookMVA("BDTG method", "/afs/cern.ch/work/a/abrinke1/public/ttH/tmva/weights/TMVAClassification_allVars_opt_v0_allVars_opt_v0_BDTG.weights.xml");

  int chainentries = chain->GetEntries();   
  cout << "# events in tree: "<< chainentries << endl;  
  
  double mcwgt_intree = -999.;
  double wgt_intree = -999.;
  double wallTimePerEvent_intree = -99.;  
  int eventnum_intree = -999;
  int higgs_decay_intree = -9999;
  int lumiBlock_intree = -999;
  int runNumber_intree = -999;
  
  vector<ttH::Lepton> *preselected_leptons_intree=0;
  vector<ttH::Electron> *raw_electrons_intree=0;               
  vector<ttH::Electron> *preselected_electrons_intree=0;
  vector<ttH::Muon> *raw_muons_intree=0;
  vector<ttH::Muon> *preselected_muons_intree=0;
  vector<ttH::Jet> *preselected_jets_intree=0;
  vector<ttH::MET> *met_intree=0;
  vector<ttH::GenParticle> *pruned_genParticles_intree=0;
  vector<ttH::Lepton> *tight_leptons_intree=0;
  vector<ttH::Electron> *tight_electrons_intree=0;
  vector<ttH::Muon> *tight_muons_intree=0;
  vector<ttH::Lepton> *tight_leptons_sortedByMiniIso_intree=0;  
  
  chain->SetBranchAddress("mcwgt", &mcwgt_intree);
  chain->SetBranchAddress("wgt", &wgt_intree);
  chain->SetBranchAddress("wallTimePerEvent", &wallTimePerEvent_intree);
  chain->SetBranchAddress("eventnum", &eventnum_intree);
  chain->SetBranchAddress("lumiBlock", &lumiBlock_intree);
  chain->SetBranchAddress("runNumber", &runNumber_intree);
  chain->SetBranchAddress("higgs_decay", &higgs_decay_intree);
  chain->SetBranchAddress("preselected_leptons", &preselected_leptons_intree);
  chain->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
  chain->SetBranchAddress("preselected_muons", &preselected_muons_intree);
  chain->SetBranchAddress("tightMvaBased_leptons", &tight_leptons_intree);
  chain->SetBranchAddress("tightMvaBased_electrons", &tight_electrons_intree);
  chain->SetBranchAddress("tightMvaBased_muons", &tight_muons_intree);    
  chain->SetBranchAddress("preselected_jets", &preselected_jets_intree);
  chain->SetBranchAddress("met", &met_intree);
  chain->SetBranchAddress("pruned_genParticles", &pruned_genParticles_intree);   

  TFile *copiedfile = new TFile(output_file, "RECREATE"); //"UPDATE"); // #, 'test' ) // "RECREATE");

  double reco_score_intree = -1.;
  vector<ttH::Jet> *unmatched_jets_intree=0;
  vector<ttH::Jet> *matched_jets_intree=0;
  ttH::Lepton lep_fromHiggs_intree;  
  ttH::Lepton lep_fromTop_intree;

  vector<double> *reco_scores_intree=0;  

  TLorentzVector w_fromHadTop_tlv_intree;
  TLorentzVector w_fromHiggs_tlv_intree;
  TLorentzVector higgs_tlv_intree;
  TLorentzVector hadTop_tlv_intree;
  TLorentzVector lepTop_tlv_intree;
  
  double dR_b_W_hadTop_intree = -1.;
  double dR_b_W_lepTop_intree = -1.;
  double dR_H_lepTop_intree = -1.;
  double dR_H_hadTop_intree = -1.;
  double dR_lepTop_hadTop_intree = -1.;
  double dR_W1_W2_fromHiggs_intree = -1.;
  double dR_q1_q2_fromWfromHiggs_intree = -1.;
  
  //Andrew Variables
  double highestNonBJetCsv_intree = 0.;
  double avg_dEta_gJet1_ttH_intree = 0.;
  
  
  w_fromHadTop_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);
  w_fromHiggs_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);
  higgs_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);
  hadTop_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);
  lepTop_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);

  TTree *signal_tree = (TTree*)chain->CloneTree(0);
  signal_tree->SetName("signal_tree");
  signal_tree->Branch("reco_score", &reco_score_intree);
  signal_tree->Branch("unmatched_jets", &unmatched_jets_intree);
  signal_tree->Branch("matched_jets", &matched_jets_intree);
  signal_tree->Branch("lep_fromTop", &lep_fromTop_intree);
  signal_tree->Branch("lep_fromHiggs", &lep_fromHiggs_intree);
  signal_tree->Branch("w_fromHadTop", &w_fromHadTop_tlv_intree);
  signal_tree->Branch("w_fromHiggs", &w_fromHiggs_tlv_intree);
  signal_tree->Branch("higgs", &higgs_tlv_intree);
  signal_tree->Branch("hadTop", &hadTop_tlv_intree);
  signal_tree->Branch("lepTop", &lepTop_tlv_intree);

  signal_tree->Branch("dR_b_W_hadTop", &dR_b_W_hadTop_intree);
  signal_tree->Branch("dR_b_W_lepTop", &dR_b_W_lepTop_intree);
  signal_tree->Branch("dR_H_lepTop", &dR_H_lepTop_intree);
  signal_tree->Branch("dR_H_hadTop", &dR_H_hadTop_intree);
  signal_tree->Branch("dR_lepTop_hadTop", &dR_lepTop_hadTop_intree);
  signal_tree->Branch("dR_W1_W2_fromHiggs", &dR_W1_W2_fromHiggs_intree);
  signal_tree->Branch("dR_q1_q2_fromWfromHiggs", &dR_q1_q2_fromWfromHiggs_intree);
  signal_tree->Branch("reco_scores", &reco_scores_intree);

  signal_tree->Branch( "numJets", &num_jets_var );
  signal_tree->Branch( "bJet_fromLepTop_CSV", &bJet_fromLepTop_CSV_var );
  signal_tree->Branch( "LepTop_pT", &LepTop_pT_var );
  signal_tree->Branch( "LepTop_mass", &LepTop_mass_var );
  signal_tree->Branch( "LepTop_lep_bJet_dR", &LepTop_lep_bJet_dR_var );
  signal_tree->Branch( "bJet_fromHadTop_CSV", &bJet_fromHadTop_CSV_var );
  signal_tree->Branch( "qJet1_fromW_fromHadTop_CSV", &qJet1_fromW_fromHadTop_CSV_var );
  signal_tree->Branch( "qJet1_fromW_fromHadTop_pT", &qJet1_fromW_fromHadTop_pT_var );
  signal_tree->Branch( "HadTop_pT", &HadTop_pT_var );
  signal_tree->Branch( "W_fromHadTop_mass", &W_fromHadTop_mass_var );
  signal_tree->Branch( "HadTop_mass", &HadTop_mass_var );
  signal_tree->Branch( "W_fromHadTop_q1_q2_dR", &W_fromHadTop_q1_q2_dR_var );
  signal_tree->Branch( "qJet1_fromW_fromHiggs_CSV", &qJet1_fromW_fromHiggs_CSV_var );
  signal_tree->Branch( "lep_fromW_fromHiggs_pT", &lep_fromW_fromHiggs_pT_var );
  signal_tree->Branch( "W_fromHiggs_mass", &W_fromHiggs_mass_var );
  signal_tree->Branch( "Higgs_mass", &Higgs_mass_var );
  signal_tree->Branch( "Higgs_lep_W_dR", &Higgs_lep_W_dR_var );
  signal_tree->Branch( "Higgs_lep_W_dPhi", &Higgs_lep_W_dPhi_var );
  signal_tree->Branch( "Higgs_lep_W_dEta", &Higgs_lep_W_dEta_var );
  signal_tree->Branch( "numMatchedJets", &numMatchedJets_var );
  signal_tree->Branch( "LepTop_Higgs_mass", &LepTop_Higgs_mass_var );
  signal_tree->Branch( "HadTop_Higgs_mass", &HadTop_Higgs_mass_var );
  signal_tree->Branch( "LepTop_HadTop_MT", &LepTop_HadTop_MT_var );
  signal_tree->Branch( "LepTop_Higgs_MT", &LepTop_Higgs_MT_var );
  signal_tree->Branch( "ttH_MT", &ttH_MT_var );
  signal_tree->Branch( "HadTop_Higgs_MT_mass_ratio", &HadTop_Higgs_MT_mass_ratio_var );
  signal_tree->Branch( "ttH_MT_mass_ratio", &ttH_MT_mass_ratio_var );
  signal_tree->Branch( "LepTop_HadTop_dR", &LepTop_HadTop_dR_var );
  signal_tree->Branch( "LepTop_HadTop_dPhi", &LepTop_HadTop_dPhi_var );

  signal_tree->Branch("lep_charge", &lep_charge_var );
  signal_tree->Branch("bJet_fromHadTop_charge", &bJet_fromHadTop_charge_var );
  signal_tree->Branch("bJet_fromLepTop_charge", &bJet_fromLepTop_charge_var );
  signal_tree->Branch("W_fromHadTop_charge", &W_fromHadTop_charge_var );
  signal_tree->Branch("W_fromHiggs_charge", &W_fromHiggs_charge_var );
  signal_tree->Branch("lepTop_charge", &lepTop_charge_var );
  signal_tree->Branch("hadTop_charge", &hadTop_charge_var );
  signal_tree->Branch("Higgs_charge", &Higgs_charge_var );
  signal_tree->Branch("ttH_charge", &ttH_charge_var );
  signal_tree->Branch("bJet_fromHadTop_charge_correct", &bJet_fromHadTop_charge_correct_var );
  signal_tree->Branch("bJet_fromLepTop_charge_correct", &bJet_fromLepTop_charge_correct_var );
  signal_tree->Branch("W_fromHadTop_charge_correct", &W_fromHadTop_charge_correct_var );
  signal_tree->Branch("W_fromHiggs_charge_correct", &W_fromHiggs_charge_correct_var );
  signal_tree->Branch("highestNonBJetCsv", &highestNonBJetCsv_intree );
  signal_tree->Branch("gJet1_ttHObj_avg_dEta", &avg_dEta_gJet1_ttH_intree );

  double background_weight_intree = -1.;
  double background_weight_realObjects_intree = -1.;
  TTree *background_tree = (TTree*)chain->CloneTree(0);
  background_tree->SetName("background_tree");
  background_tree->Branch("reco_score", &reco_score_intree);
  background_tree->Branch("unmatched_jets", &unmatched_jets_intree);
  background_tree->Branch("matched_jets", &matched_jets_intree);
  background_tree->Branch("lep_fromTop", &lep_fromTop_intree);
  background_tree->Branch("lep_fromHiggs", &lep_fromHiggs_intree);
  background_tree->Branch("w_fromHadTop", &w_fromHadTop_tlv_intree);
  background_tree->Branch("w_fromHiggs", &w_fromHiggs_tlv_intree);
  background_tree->Branch("higgs", &higgs_tlv_intree);
  background_tree->Branch("hadTop", &hadTop_tlv_intree);
  background_tree->Branch("lepTop", &lepTop_tlv_intree);

  background_tree->Branch("dR_b_W_hadTop", &dR_b_W_hadTop_intree);
  background_tree->Branch("dR_b_W_lepTop", &dR_b_W_lepTop_intree);
  background_tree->Branch("dR_H_lepTop", &dR_H_lepTop_intree);
  background_tree->Branch("dR_H_hadTop", &dR_H_hadTop_intree);
  background_tree->Branch("dR_lepTop_hadTop", &dR_lepTop_hadTop_intree);
  background_tree->Branch("dR_W1_W2_fromHiggs", &dR_W1_W2_fromHiggs_intree);
  background_tree->Branch("dR_q1_q2_fromWfromHiggs", &dR_q1_q2_fromWfromHiggs_intree);
  background_tree->Branch("reco_scores", &reco_scores_intree);

  background_tree->Branch( "numJets", &num_jets_var );
  background_tree->Branch( "bJet_fromLepTop_CSV", &bJet_fromLepTop_CSV_var );
  background_tree->Branch( "LepTop_pT", &LepTop_pT_var );
  background_tree->Branch( "LepTop_mass", &LepTop_mass_var );
  background_tree->Branch( "LepTop_lep_bJet_dR", &LepTop_lep_bJet_dR_var );
  background_tree->Branch( "bJet_fromHadTop_CSV", &bJet_fromHadTop_CSV_var );
  background_tree->Branch( "qJet1_fromW_fromHadTop_CSV", &qJet1_fromW_fromHadTop_CSV_var );
  background_tree->Branch( "qJet1_fromW_fromHadTop_pT", &qJet1_fromW_fromHadTop_pT_var );
  background_tree->Branch( "HadTop_pT", &HadTop_pT_var );
  background_tree->Branch( "W_fromHadTop_mass", &W_fromHadTop_mass_var );
  background_tree->Branch( "HadTop_mass", &HadTop_mass_var );
  background_tree->Branch( "W_fromHadTop_q1_q2_dR", &W_fromHadTop_q1_q2_dR_var );
  background_tree->Branch( "qJet1_fromW_fromHiggs_CSV", &qJet1_fromW_fromHiggs_CSV_var );
  background_tree->Branch( "lep_fromW_fromHiggs_pT", &lep_fromW_fromHiggs_pT_var );
  background_tree->Branch( "W_fromHiggs_mass", &W_fromHiggs_mass_var );
  background_tree->Branch( "Higgs_mass", &Higgs_mass_var );
  background_tree->Branch( "Higgs_lep_W_dR", &Higgs_lep_W_dR_var );
  background_tree->Branch( "Higgs_lep_W_dPhi", &Higgs_lep_W_dPhi_var );
  background_tree->Branch( "Higgs_lep_W_dEta", &Higgs_lep_W_dEta_var );
  background_tree->Branch( "numMatchedJets", &numMatchedJets_var );
  background_tree->Branch( "LepTop_Higgs_mass", &LepTop_Higgs_mass_var );
  background_tree->Branch( "HadTop_Higgs_mass", &HadTop_Higgs_mass_var );
  background_tree->Branch( "LepTop_HadTop_MT", &LepTop_HadTop_MT_var );
  background_tree->Branch( "LepTop_Higgs_MT", &LepTop_Higgs_MT_var );
  background_tree->Branch( "ttH_MT", &ttH_MT_var );
  background_tree->Branch( "HadTop_Higgs_MT_mass_ratio", &HadTop_Higgs_MT_mass_ratio_var );
  background_tree->Branch( "ttH_MT_mass_ratio", &ttH_MT_mass_ratio_var );
  background_tree->Branch( "LepTop_HadTop_dR", &LepTop_HadTop_dR_var );
  background_tree->Branch( "LepTop_HadTop_dPhi", &LepTop_HadTop_dPhi_var );

  background_tree->Branch("lep_charge", &lep_charge_var );
  background_tree->Branch("bJet_fromHadTop_charge", &bJet_fromHadTop_charge_var );
  background_tree->Branch("bJet_fromLepTop_charge", &bJet_fromLepTop_charge_var );
  background_tree->Branch("W_fromHadTop_charge", &W_fromHadTop_charge_var );
  background_tree->Branch("W_fromHiggs_charge", &W_fromHiggs_charge_var );
  background_tree->Branch("lepTop_charge", &lepTop_charge_var );
  background_tree->Branch("hadTop_charge", &hadTop_charge_var );
  background_tree->Branch("Higgs_charge", &Higgs_charge_var );
  background_tree->Branch("ttH_charge", &ttH_charge_var );
  background_tree->Branch("bJet_fromHadTop_charge_correct", &bJet_fromHadTop_charge_correct_var );
  background_tree->Branch("bJet_fromLepTop_charge_correct", &bJet_fromLepTop_charge_correct_var );
  background_tree->Branch("W_fromHadTop_charge_correct", &W_fromHadTop_charge_correct_var );
  background_tree->Branch("W_fromHiggs_charge_correct", &W_fromHiggs_charge_correct_var );
  background_tree->Branch("weight_allObjects", &background_weight_intree );
  background_tree->Branch("weight_realObjects", &background_weight_realObjects_intree );

  background_tree->Branch("highestNonBJetCsv", &highestNonBJetCsv_intree );
  signal_tree->Branch("gJet1_ttHObj_avg_dEta", &avg_dEta_gJet1_ttH_intree );
  
  // Int_t cachesize = 250000000;   //250 MBytes
  // chain->SetCacheSize(cachesize);
  // chain->SetCacheLearnEntries(20); 
  
  double starttime = get_wall_time();
  //  chainentries = 1000000;
  for (int i=0; i<chainentries; i++)
    {
      
      if (i%1000 == 0)
	{
	  float fraction = 100.*i/chainentries;
	  cout << fraction << " % complete" << endl;
	  cout << i << endl;
	}
      chain->GetEntry(i);

      //////////////////////////
      ////
      //// selection, vetos etc
      ////
      //////////////////////////

      //      if ( (*preselected_jets_intree).size() < 3) continue; 
      bool passesCommon = passCommon(*tight_electrons_intree, *preselected_electrons_intree, *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree);
      if (!passesCommon) continue;
      bool passes2lss = pass2lss(*tight_electrons_intree, *preselected_electrons_intree, *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree, *met_intree);
      if ( !passes2lss ) continue;

      //////////////////////////
      ////
      //// calculation of new vars etc
      ////
      //////////////////////////

      lep_fromHiggs_intree.clear();  
      lep_fromTop_intree.clear();  

      ttH::Lepton lep_fromTop_truth = (*tight_leptons_intree)[0];
      ttH::Lepton lep_fromHiggs_truth = (*tight_leptons_intree)[1];
      if (abs( lep_fromTop_truth.genGrandMotherPdgID ) == 25 || abs( lep_fromHiggs_truth.genGrandMotherPdgID ) == 6)
	{
	  lep_fromTop_truth = (*tight_leptons_intree)[1];
	  lep_fromHiggs_truth = (*tight_leptons_intree)[0];
	}
      if ( !(lep_fromHiggs_truth.obj.pt() > 0 && lep_fromTop_truth.obj.pt() >0) ) continue;

      lep_fromTop_intree = lep_fromTop_truth;
      lep_fromHiggs_intree = lep_fromHiggs_truth;


      //Andrew's fix for -1 csv values to make range easier to see.
      for (unsigned int j =0; j< preselected_jets_intree->size(); j++)
	{
	  double csv = (*preselected_jets_intree)[j].csv;
	  (*preselected_jets_intree)[j].csv = max(-.1,csv);
	}

      ttH::Jet bjet_fromHadTop_truth;
      ttH::Jet bjet_fromLepTop_truth;
      ttH::Jet wjet1_fromHadTop_truth;
      ttH::Jet wjet2_fromHadTop_truth;
      ttH::Jet wjet1_fromHiggs_truth;
      ttH::Jet wjet2_fromHiggs_truth;

      vector<ttH::Jet> matched_jets_truth;
      matched_jets_truth.push_back(bjet_fromHadTop_truth);
      matched_jets_truth.push_back(bjet_fromLepTop_truth);
      matched_jets_truth.push_back(wjet1_fromHadTop_truth);
      matched_jets_truth.push_back(wjet2_fromHadTop_truth);
      matched_jets_truth.push_back(wjet1_fromHiggs_truth);
      matched_jets_truth.push_back(wjet2_fromHiggs_truth);
      
      for (const auto & jet : *preselected_jets_intree)
	{
	  if (abs(jet.genPdgID) == 5)
	    {
	      if (jet.genPdgID*lep_fromTop_truth.charge < 0) bjet_fromHadTop_truth = jet;
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

      
      int num_matches = 0;
      for (const auto & jet : matched_jets_truth)
	{
	  if (jet.obj.pt() > 0) num_matches +=1;
	}

      int num_fake_jets = 6 - num_matches;
      matched_jets_truth.clear();
      matched_jets_truth.push_back(bjet_fromHadTop_truth);
      matched_jets_truth.push_back(bjet_fromLepTop_truth);
      matched_jets_truth.push_back(wjet1_fromHadTop_truth);
      matched_jets_truth.push_back(wjet2_fromHadTop_truth);
      matched_jets_truth.push_back(wjet1_fromHiggs_truth);
      matched_jets_truth.push_back(wjet2_fromHiggs_truth);

      //unmatched jet vector
      unmatched_jets_intree->clear();
      for (const auto & jet : *preselected_jets_intree)
	{
	  bool isFsrIsr = true;
	  for (const auto & matched_jet : matched_jets_truth)
	    {
	      if (jet.obj.pt() == matched_jet.obj.pt()) 
		{
		  isFsrIsr = false;
		  break;
		}
	    }
	  if ( isFsrIsr ) unmatched_jets_intree->push_back(jet);
	}
      std::sort(unmatched_jets_intree->begin(), unmatched_jets_intree->end(), [] (ttH::Jet a, ttH::Jet b) { return a.obj.pt() > b.obj.pt();});

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
      
      num_jets_var = preselected_jets_intree->size();

      //reset tree vars
      reco_score_intree = -1.;
      matched_jets_intree->clear();
      w_fromHadTop_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);
      w_fromHiggs_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);
      higgs_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);
      hadTop_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);
      lepTop_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);

      dR_b_W_hadTop_intree = -1.;
      dR_b_W_lepTop_intree = -1.;
      dR_H_lepTop_intree = -1.;
      dR_H_hadTop_intree = -1.;
      dR_lepTop_hadTop_intree = -1.;
      dR_W1_W2_fromHiggs_intree = -1.;
      dR_q1_q2_fromWfromHiggs_intree = -1.;

      background_weight_intree = -1.;
      background_weight_realObjects_intree = -1.;
      avg_dEta_gJet1_ttH_intree = 0.;
      
      reco_scores_intree->clear();


      /////////////////////
      /////
      ///// signal 
      /////
      /////////////////////
      
      ttH::Jet bjet_fromHadTop = bjet_fromHadTop_truth;
      ttH::Jet bjet_fromLepTop = bjet_fromLepTop_truth;
      ttH::Jet wjet1_fromHadTop = wjet1_fromHadTop_truth;
      ttH::Jet wjet2_fromHadTop = wjet2_fromHadTop_truth;
      ttH::Jet wjet1_fromHiggs = wjet1_fromHiggs_truth;
      ttH::Jet wjet2_fromHiggs = wjet2_fromHiggs_truth;

      lep_fromTop_tlv.SetPxPyPzE(lep_fromTop_truth.obj.px(),lep_fromTop_truth.obj.py(),lep_fromTop_truth.obj.pz(),lep_fromTop_truth.obj.E());
      lep_fromTop_T_tlv.SetPxPyPzE(lep_fromTop_truth.obj.px(),lep_fromTop_truth.obj.py(), 0. ,lep_fromTop_truth.obj.pt());
      lep_fromHiggs_tlv.SetPxPyPzE(lep_fromHiggs_truth.obj.px(),lep_fromHiggs_truth.obj.py(),lep_fromHiggs_truth.obj.pz(),lep_fromHiggs_truth.obj.E());
      lep_fromHiggs_T_tlv.SetPxPyPzE(lep_fromHiggs_truth.obj.px(),lep_fromHiggs_truth.obj.py(), 0. ,lep_fromHiggs_truth.obj.pt());
      bjet_fromHadTop_tlv.SetPxPyPzE(bjet_fromHadTop.obj.px(),bjet_fromHadTop.obj.py(),bjet_fromHadTop.obj.pz(),bjet_fromHadTop.obj.E());
      bjet_fromHadTop_T_tlv.SetPxPyPzE(bjet_fromHadTop.obj.px(),bjet_fromHadTop.obj.py(), 0. ,bjet_fromHadTop.obj.pt());
      
      bjet_fromLepTop_tlv.SetPxPyPzE(bjet_fromLepTop.obj.px(),bjet_fromLepTop.obj.py(),bjet_fromLepTop.obj.pz(),bjet_fromLepTop.obj.E());
      bjet_fromLepTop_T_tlv.SetPxPyPzE(bjet_fromLepTop.obj.px(),bjet_fromLepTop.obj.py(), 0. ,bjet_fromLepTop.obj.pt());
      
      lepTop_tlv = lep_fromTop_tlv + bjet_fromLepTop_tlv;
      lepTop_T_tlv = lep_fromTop_T_tlv + bjet_fromLepTop_T_tlv;
      
      wjet1_fromHadTop_tlv.SetPxPyPzE(wjet1_fromHadTop.obj.px(),wjet1_fromHadTop.obj.py(),wjet1_fromHadTop.obj.pz(),wjet1_fromHadTop.obj.E());
      wjet1_fromHadTop_T_tlv.SetPxPyPzE(wjet1_fromHadTop.obj.px(),wjet1_fromHadTop.obj.py(), 0. ,wjet1_fromHadTop.obj.pt());
      
      wjet2_fromHadTop_tlv.SetPxPyPzE(wjet2_fromHadTop.obj.px(),wjet2_fromHadTop.obj.py(),wjet2_fromHadTop.obj.pz(),wjet2_fromHadTop.obj.E());
      wjet2_fromHadTop_T_tlv.SetPxPyPzE(wjet2_fromHadTop.obj.px(),wjet2_fromHadTop.obj.py(), 0. ,wjet2_fromHadTop.obj.pt());
      
      w_fromHadTop_tlv = wjet1_fromHadTop_tlv + wjet2_fromHadTop_tlv;
      w_fromHadTop_T_tlv = wjet1_fromHadTop_T_tlv + wjet2_fromHadTop_T_tlv;
      
      hadTop_tlv = w_fromHadTop_tlv + bjet_fromHadTop_tlv;
      hadTop_T_tlv = w_fromHadTop_T_tlv + bjet_fromHadTop_T_tlv;
      
      wjet1_fromHiggs_tlv.SetPxPyPzE(wjet1_fromHiggs.obj.px(),wjet1_fromHiggs.obj.py(),wjet1_fromHiggs.obj.pz(),wjet1_fromHiggs.obj.E());
      wjet1_fromHiggs_T_tlv.SetPxPyPzE(wjet1_fromHiggs.obj.px(),wjet1_fromHiggs.obj.py(), 0. ,wjet1_fromHiggs.obj.pt());
      
      wjet2_fromHiggs_tlv.SetPxPyPzE(wjet2_fromHiggs.obj.px(),wjet2_fromHiggs.obj.py(),wjet2_fromHiggs.obj.pz(),wjet2_fromHiggs.obj.E());
      wjet2_fromHiggs_T_tlv.SetPxPyPzE(wjet2_fromHiggs.obj.px(),wjet2_fromHiggs.obj.py(), 0. ,wjet2_fromHiggs.obj.pt());
      
      w_fromHiggs_tlv = wjet1_fromHiggs_tlv + wjet2_fromHiggs_tlv;
      w_fromHiggs_T_tlv = wjet1_fromHiggs_T_tlv + wjet2_fromHiggs_T_tlv;
      
      higgs_tlv = w_fromHiggs_tlv + lep_fromHiggs_tlv;
      higgs_T_tlv = w_fromHiggs_T_tlv + lep_fromHiggs_T_tlv;
      
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
      lep_fromW_fromHiggs_pT_var = lep_fromHiggs_truth.obj.pt();
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
			      ) ;
      LepTop_Higgs_mass_var = lepTop_higgs_tlv.M();
      HadTop_Higgs_mass_var = hadTop_higgs_tlv.M();
      LepTop_HadTop_MT_var = lepTop_hadTop_T_tlv.M();
      LepTop_Higgs_MT_var = lepTop_higgs_T_tlv.M();
      ttH_MT_var = tth_T_tlv.M();
      HadTop_Higgs_MT_mass_ratio_var = hadTop_higgs_T_tlv.M() / hadTop_higgs_tlv.M();
      ttH_MT_mass_ratio_var = tth_T_tlv.M()/tth_tlv.M();

      LepTop_HadTop_dR_var = lepTop_tlv.DeltaR( hadTop_tlv );
      LepTop_HadTop_dPhi_var = lepTop_tlv.DeltaPhi( hadTop_tlv );


      lep_charge_var = lep_fromTop_truth.charge;
      bJet_fromHadTop_charge_var = bjet_fromHadTop.charge;
      bJet_fromLepTop_charge_var = bjet_fromLepTop.charge;
      W_fromHadTop_charge_var = wjet1_fromHadTop.charge + wjet2_fromHadTop.charge;
      W_fromHiggs_charge_var = wjet1_fromHiggs.charge + wjet2_fromHiggs.charge;
      lepTop_charge_var = lep_fromTop_truth.charge + bjet_fromLepTop.charge;
      hadTop_charge_var = bjet_fromHadTop.charge + W_fromHadTop_charge_var;
      Higgs_charge_var = lep_charge_var + W_fromHiggs_charge_var;
      ttH_charge_var = lepTop_charge_var + hadTop_charge_var + Higgs_charge_var;
      bJet_fromHadTop_charge_correct_var = (bjet_fromHadTop.charge != 0.) ? bJet_fromHadTop_charge_var*lep_charge_var : -1;
      bJet_fromLepTop_charge_correct_var = (bjet_fromHadTop.charge != 0.) ? bJet_fromLepTop_charge_var*lep_charge_var : -1;
      W_fromHadTop_charge_correct_var = W_fromHadTop_charge_var*lep_charge_var;
      W_fromHiggs_charge_correct_var = W_fromHiggs_charge_var*lep_charge_var;

      
      if (bjet_fromLepTop_tlv.Pt() == 0) LepTop_lep_bJet_dR_var = -1.;
      if (wjet1_fromHadTop_tlv.Pt() == 0 || wjet2_fromHadTop_tlv.Pt() == 0) W_fromHadTop_q1_q2_dR_var = -1.; 
      if (w_fromHiggs_tlv.Pt() ==0 )
	{ 
	  Higgs_lep_W_dR_var = -1.;
	  Higgs_lep_W_dPhi_var = -4.0;
	  Higgs_lep_W_dEta_var = -6.0;
	}
      
      //Andrew Variable
      highestNonBJetCsv_intree = 0.;
      for (int i=2; i <= 5; i++)
	{
	  if (matched_jets_truth[i].csv > highestNonBJetCsv_intree) highestNonBJetCsv_intree = matched_jets_truth[i].csv;
	}

      //don't count signal if matched jets < 4
      if ( numMatchedJets_var >= 3) signal_tree->Fill();

      //reset tree vars
      reco_score_intree = -1.;
      matched_jets_intree->clear();
      w_fromHadTop_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);
      w_fromHiggs_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);
      higgs_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);
      hadTop_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);
      lepTop_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);

      dR_b_W_hadTop_intree = -1.;
      dR_b_W_lepTop_intree = -1.;
      dR_H_lepTop_intree = -1.;
      dR_H_hadTop_intree = -1.;
      dR_lepTop_hadTop_intree = -1.;
      dR_W1_W2_fromHiggs_intree = -1.;
      dR_q1_q2_fromWfromHiggs_intree = -1.;

      background_weight_intree = -1.;
      background_weight_realObjects_intree = -1.;
      avg_dEta_gJet1_ttH_intree = 0.;
      
      /////////////////////
      /////
      ///// background 
      /////
      /////////////////////

      //only add the same number of empty jets as there are fakes
      ttH::Jet null_jet;
      if (num_jets_var <=7)
	{
	  (*preselected_jets_intree).push_back(null_jet);
	  (*preselected_jets_intree).push_back(null_jet);
	  (*preselected_jets_intree).push_back(null_jet);
	}
      else if (num_jets_var ==8)
	{
	  (*preselected_jets_intree).push_back(null_jet);
	  (*preselected_jets_intree).push_back(null_jet);
	}
      else 
	{
	  (*preselected_jets_intree).push_back(null_jet);
	}

      //traditional loop
      int tries = 0;
      int rand_cut = 50;

      int lep_fromTop_count = -1;
      for (const auto & lep_fromTop : *tight_leptons_intree)
      	{
      	  lep_fromTop_count +=1;
	  if (rand() % 100+1 > rand_cut) continue;
	  //if (lep_fromTop.obj.pt() == lep_fromTop_truth.obj.pt()) continue; //train only against incorrect lepton backgrounds

      	  lep_fromTop_tlv.SetPxPyPzE(lep_fromTop.obj.px(),lep_fromTop.obj.py(),lep_fromTop.obj.pz(),lep_fromTop.obj.E());
      	  lep_fromTop_T_tlv.SetPxPyPzE(lep_fromTop.obj.px(),lep_fromTop.obj.py(), 0. ,lep_fromTop.obj.pt());
	  
      	  int lep_fromHiggs_count = -1;
      	  for (const auto & lep_fromHiggs : *tight_leptons_intree)
      	    {
      	      lep_fromHiggs_count +=1;  
	      if (lep_fromTop_count == lep_fromHiggs_count) continue;
	      if (rand() % 100+1 > rand_cut) continue;

      	      lep_fromHiggs_tlv.SetPxPyPzE(lep_fromHiggs.obj.px(),lep_fromHiggs.obj.py(),lep_fromHiggs.obj.pz(),lep_fromHiggs.obj.E());
      	      lep_fromHiggs_T_tlv.SetPxPyPzE(lep_fromHiggs.obj.px(),lep_fromHiggs.obj.py(), 0. ,lep_fromHiggs.obj.pt());

      	      int bjet_fromHadTop_count = -1;
      	      for (const auto & bjet_fromHadTop : *preselected_jets_intree)
      		{
      		  bjet_fromHadTop_count +=1;
		  if (rand() % 100+1 > rand_cut) continue;
      		  bjet_fromHadTop_tlv.SetPxPyPzE(bjet_fromHadTop.obj.px(),bjet_fromHadTop.obj.py(),bjet_fromHadTop.obj.pz(),bjet_fromHadTop.obj.E());
      		  bjet_fromHadTop_T_tlv.SetPxPyPzE(bjet_fromHadTop.obj.px(),bjet_fromHadTop.obj.py(), 0. ,bjet_fromHadTop.obj.pt());

      		  int bjet_fromLepTop_count = -1;
      		  for (const auto & bjet_fromLepTop : *preselected_jets_intree)
      		    {
      		      bjet_fromLepTop_count +=1;
		      if (rand() % 100+1 > rand_cut) continue;
      		      if (bjet_fromHadTop_count == bjet_fromLepTop_count) continue;
      		      if ( !( (bjet_fromHadTop.csv > 0.8 || bjet_fromLepTop.csv > 0.8) || (bjet_fromHadTop.csv > 0.4 && bjet_fromLepTop.csv > 0.4) ) ) continue;

      		      bjet_fromLepTop_tlv.SetPxPyPzE(bjet_fromLepTop.obj.px(),bjet_fromLepTop.obj.py(),bjet_fromLepTop.obj.pz(),bjet_fromLepTop.obj.E());
      		      bjet_fromLepTop_T_tlv.SetPxPyPzE(bjet_fromLepTop.obj.px(),bjet_fromLepTop.obj.py(), 0. ,bjet_fromLepTop.obj.pt());

      		      lepTop_tlv = lep_fromTop_tlv + bjet_fromLepTop_tlv;
      		      lepTop_T_tlv = lep_fromTop_T_tlv + bjet_fromLepTop_T_tlv;

      		      if ( lepTop_tlv.M() > 180 ) continue;
		      
		      //Andrews Variable
		      highestNonBJetCsv_intree = 0.;
		      for (const auto & nonBjet : *preselected_jets_intree)
			{
			  if (nonBjet.csv == bjet_fromHadTop.csv || nonBjet.csv == bjet_fromHadTop.csv) continue;
			  else if (nonBjet.csv > highestNonBJetCsv_intree) highestNonBJetCsv_intree = nonBjet.csv;
			}

      		      int wjet1_fromHadTop_count = -1;
      		      for (const auto & wjet1_fromHadTop : *preselected_jets_intree)
      			{
      			  wjet1_fromHadTop_count +=1;
			  if (rand() % 100+1 > rand_cut) continue;
      			  if (wjet1_fromHadTop_count == bjet_fromLepTop_count) continue;
      			  if (wjet1_fromHadTop_count == bjet_fromHadTop_count) continue;

      			  wjet1_fromHadTop_tlv.SetPxPyPzE(wjet1_fromHadTop.obj.px(),wjet1_fromHadTop.obj.py(),wjet1_fromHadTop.obj.pz(),wjet1_fromHadTop.obj.E());
      			  wjet1_fromHadTop_T_tlv.SetPxPyPzE(wjet1_fromHadTop.obj.px(),wjet1_fromHadTop.obj.py(), 0. ,wjet1_fromHadTop.obj.pt());

      			  int wjet2_fromHadTop_count = -1;
      			  for (const auto & wjet2_fromHadTop : *preselected_jets_intree)
      			    {
      			      wjet2_fromHadTop_count +=1;
			      if (rand() % 100+1 > rand_cut) continue;
				  
      			      if (wjet2_fromHadTop_count == bjet_fromLepTop_count) continue;
      			      if (wjet2_fromHadTop_count == bjet_fromHadTop_count) continue;
      			      if (wjet2_fromHadTop_count <= wjet1_fromHadTop_count) continue; //don't need both orderings 

      			      wjet2_fromHadTop_tlv.SetPxPyPzE(wjet2_fromHadTop.obj.px(),wjet2_fromHadTop.obj.py(),wjet2_fromHadTop.obj.pz(),wjet2_fromHadTop.obj.E());
      			      wjet2_fromHadTop_T_tlv.SetPxPyPzE(wjet2_fromHadTop.obj.px(),wjet2_fromHadTop.obj.py(), 0. ,wjet2_fromHadTop.obj.pt());
			      
      			      w_fromHadTop_tlv = wjet1_fromHadTop_tlv + wjet2_fromHadTop_tlv;
      			      w_fromHadTop_T_tlv = wjet1_fromHadTop_T_tlv + wjet2_fromHadTop_T_tlv;
			      
      			      if (w_fromHadTop_tlv.M() > 120 ) continue; 

      			      hadTop_tlv = w_fromHadTop_tlv + bjet_fromHadTop_tlv;
      			      hadTop_T_tlv = w_fromHadTop_T_tlv + bjet_fromHadTop_T_tlv;

      			      if ( hadTop_tlv.M() > 220 ) continue;

      			      int wjet1_fromHiggs_count = -1;
      			      for (const auto & wjet1_fromHiggs : *preselected_jets_intree)
      				{
      				  wjet1_fromHiggs_count +=1;
			  	  if (rand() % 100+1 > rand_cut) continue;
				  
      				  if (wjet1_fromHiggs_count == bjet_fromLepTop_count) continue;
      				  if (wjet1_fromHiggs_count == bjet_fromHadTop_count) continue;
      				  if (wjet1_fromHiggs_count == wjet1_fromHadTop_count) continue;
      				  if (wjet1_fromHiggs_count == wjet2_fromHadTop_count) continue;
				  
      				  wjet1_fromHiggs_tlv.SetPxPyPzE(wjet1_fromHiggs.obj.px(),wjet1_fromHiggs.obj.py(),wjet1_fromHiggs.obj.pz(),wjet1_fromHiggs.obj.E());
      				  wjet1_fromHiggs_T_tlv.SetPxPyPzE(wjet1_fromHiggs.obj.px(),wjet1_fromHiggs.obj.py(), 0. ,wjet1_fromHiggs.obj.pt());
				  
      				  int wjet2_fromHiggs_count = -1;
      				  for (const auto & wjet2_fromHiggs : *preselected_jets_intree)
      				    {
      				      wjet2_fromHiggs_count +=1;
				      if (rand() % 100+1 > rand_cut) continue;
				  
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

				      //Extra Jet variables
				      unmatched_jets_intree->clear();
				      for (const auto & xtra_jet : *preselected_jets_intree)
					{
					  if (!(xtra_jet.obj.pt() > 0)) continue;
					  if ( xtra_jet.obj.pt() == bjet_fromLepTop.obj.pt() ) continue;
					  else if ( xtra_jet.obj.pt() == bjet_fromHadTop.obj.pt() ) continue;
					  else if ( xtra_jet.obj.pt() == wjet1_fromHadTop.obj.pt() ) continue;
					  else if ( xtra_jet.obj.pt() == wjet2_fromHadTop.obj.pt() ) continue;
					  else if ( xtra_jet.obj.pt() == wjet1_fromHiggs.obj.pt() ) continue;
					  else if ( xtra_jet.obj.pt() == wjet2_fromHiggs.obj.pt() ) continue;
					  else 
					    {
					      unmatched_jets_intree->push_back(xtra_jet);
					    }
					}
				      std::sort(unmatched_jets_intree->begin(), unmatched_jets_intree->end(), [] (ttH::Jet a, ttH::Jet b) { return a.obj.pt() > b.obj.pt();});


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
      							      ) ;
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
				      
				      //set background weight according to # of matches
				      background_weight_intree = 1 + (bjet_fromHadTop.obj.pt() == bjet_fromHadTop_truth.obj.pt()) + 
					(bjet_fromLepTop.obj.pt() == bjet_fromLepTop_truth.obj.pt()) + 
					(wjet1_fromHadTop.obj.pt() == wjet1_fromHadTop_truth.obj.pt() || wjet1_fromHadTop.obj.pt() == wjet2_fromHadTop_truth.obj.pt()) +
					(wjet2_fromHadTop.obj.pt() == wjet2_fromHadTop_truth.obj.pt() || wjet2_fromHadTop.obj.pt() == wjet1_fromHadTop_truth.obj.pt()) +
					(wjet1_fromHiggs.obj.pt() == wjet1_fromHiggs_truth.obj.pt() || wjet1_fromHiggs.obj.pt() == wjet2_fromHiggs_truth.obj.pt()) +
					(wjet2_fromHiggs.obj.pt() == wjet2_fromHiggs_truth.obj.pt() || wjet2_fromHiggs.obj.pt() == wjet1_fromHiggs_truth.obj.pt()) +
					(lep_fromTop.obj.pt() == lep_fromTop_truth.obj.pt()) +
					(lep_fromHiggs.obj.pt() == lep_fromHiggs_truth.obj.pt());
				      

				      background_weight_realObjects_intree = 1+
					// (bjet_fromLepTop.obj.pt() == bjet_fromHadTop_truth.obj.pt() && bjet_fromHadTop.obj.pt() > 0) + 
					// (bjet_fromLepTop.obj.pt() == bjet_fromHadTop_truth.obj.pt() && bjet_fromLepTop.obj.pt() > 0) +
					(bjet_fromLepTop.obj.pt() == bjet_fromHadTop_truth.obj.pt() && bjet_fromLepTop.obj.pt() == bjet_fromHadTop_truth.obj.pt()) +
					(lep_fromHiggs.obj.pt() == lep_fromTop_truth.obj.pt());
				      
				      
				      //skip correct matches

				      lep_fromTop_intree = lep_fromTop;
				      lep_fromHiggs_intree = lep_fromHiggs;

				      if (background_weight_intree == 9) continue;
				      
				      bJet_fromHadTop_charge_var = bjet_fromHadTop.charge;
				      bJet_fromLepTop_charge_var = bjet_fromLepTop.charge;
				      W_fromHadTop_charge_var = wjet1_fromHadTop.charge + wjet2_fromHadTop.charge;
				      W_fromHiggs_charge_var = wjet1_fromHiggs.charge + wjet2_fromHiggs.charge;
				      lepTop_charge_var = lep_fromTop_truth.charge + bjet_fromLepTop.charge;
				      hadTop_charge_var = bjet_fromHadTop.charge + W_fromHadTop_charge_var;
				      Higgs_charge_var = lep_charge_var + W_fromHiggs_charge_var;
				      ttH_charge_var = lepTop_charge_var + hadTop_charge_var + Higgs_charge_var;
				      bJet_fromHadTop_charge_correct_var = (bjet_fromHadTop.charge != 0.) ? bJet_fromHadTop_charge_var*lep_charge_var : -1;
				      bJet_fromLepTop_charge_correct_var = (bjet_fromHadTop.charge != 0.) ? bJet_fromLepTop_charge_var*lep_charge_var : -1;
				      W_fromHadTop_charge_correct_var = W_fromHadTop_charge_var*lep_charge_var;
				      W_fromHiggs_charge_correct_var = W_fromHiggs_charge_var*lep_charge_var;

				      background_tree->Fill();

      				      //double mva_value = TMVAReader_->EvaluateMVA( "BDTG method" );
      				      //reco_scores_intree->push_back( mva_value );
      				      // if ( mva_value > reco_score_intree )
      				      // 	{
      				      // 	  reco_score_intree = mva_value;
      				      // 	  matched_jets_intree->clear();
      				      // 	  lep_fromHiggs_intree->clear();  
      				      // 	  lep_fromTop_intree->clear();  

      				      // 	  matched_jets_intree->push_back(bjet_fromHadTop);
      				      // 	  matched_jets_intree->push_back(bjet_fromLepTop);
      				      // 	  matched_jets_intree->push_back(wjet1_fromHadTop);
      				      // 	  matched_jets_intree->push_back(wjet2_fromHadTop);
      				      // 	  matched_jets_intree->push_back(wjet1_fromHiggs);
      				      // 	  matched_jets_intree->push_back(wjet2_fromHiggs);
					  

      				      // 	  lep_fromHiggs_intree->push_back(lep_fromHiggs);  
      				      // 	  lep_fromTop_intree->push_back(lep_fromTop);  

      				      // 	  w_fromHadTop_tlv_intree = w_fromHadTop_tlv;
      				      // 	  w_fromHiggs_tlv_intree = w_fromHiggs_tlv;
      				      // 	  higgs_tlv_intree = higgs_tlv;
      				      // 	  hadTop_tlv_intree = hadTop_tlv;
      				      // 	  lepTop_tlv_intree = lepTop_tlv;


      				      // 	  dR_b_W_hadTop_intree = bjet_fromHadTop_tlv.DeltaR( w_fromHadTop_tlv );
      				      // 	  dR_b_W_lepTop_intree = bjet_fromLepTop_tlv.DeltaR( lep_fromTop_tlv );
      				      // 	  dR_H_lepTop_intree = higgs_tlv.DeltaR( lepTop_tlv );
      				      // 	  dR_H_hadTop_intree = higgs_tlv.DeltaR( hadTop_tlv );
      				      // 	  dR_lepTop_hadTop_intree = hadTop_tlv.DeltaR( lepTop_tlv );
      				      // 	  dR_W1_W2_fromHiggs_intree = w_fromHiggs_tlv.DeltaR( lep_fromHiggs_tlv );
      				      // 	  dR_q1_q2_fromWfromHiggs_intree = wjet1_fromHiggs_tlv.DeltaR( wjet2_fromHiggs_tlv );

      				      // 	}
      				      //				      cout << "# tries: " << tries << endl;
      				      tries +=1;
      				    }
      				}
      			    }
      			}
      		    }
      		}
      	    }
      	}
      
      
    }
  
  
  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (chainentries>0) cout << "an average of " << (endtime - starttime) / chainentries << " per event." << endl;
  
  signal_tree->Write();
  background_tree->Write();
  copiedfile->Close();
  
}

void trainRecoBdt(TString sample, int start_file=0, int end_file=0)
{

  TString output_dir = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/";
  TString output_file = output_dir+sample + "_bdtTraining_v2_"+to_string(start_file)+"-"+to_string(end_file)+".root";
  TChain *tth_chain = loadFiles(sample,start_file,end_file);  
  run_it(tth_chain,output_file);

  // TChain *ttw_chain = loadFiles("ttW");  
  // run_it(ttw_chain,"ttW_full_recoBDT_results.root");

  // TChain *ttbar_chain = loadFiles("ttbar");  
  // run_it(ttbar_chain,"ttbar_full_recoBDT_results.root");

}
