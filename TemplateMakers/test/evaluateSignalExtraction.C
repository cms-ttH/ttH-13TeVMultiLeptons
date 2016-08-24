//Charlie Mueller 4/7/2016
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
#include "DataFormats/Math/interface/deltaR.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/src/classes.h"
#include "TMVA/Config.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#include "selection.h"
#include "loadSamples.h"
#include "treeTools.h"


/////////////////////////////////////////
///
/// usage: root -l evaluateSignalExtraction.C+
///
/////////////////////////////////////////


void run_it(TChain* chain, TFile* output_file)
{
  Float_t max_lep_eta_var;
  Float_t njets_var;
  Float_t dR_l1_j_var;
  Float_t dR_l2_j_var;
  Float_t MT_l1_met_var;
  Float_t met_var;
  Float_t avg_dr_jets_var;
  Float_t reco_score_var;
  Float_t lep1_pt_var;
  Float_t lep2_pt_var;

  Float_t spec0_var;
  Float_t spec1_var;
  Float_t spec2_var;

  TMVA::Reader* TMVAReader_ttbar_ = new TMVA::Reader( "!Color:!Silent" );
  TMVAReader_ttbar_->AddVariable( "max_lep_eta", &max_lep_eta_var );
  TMVAReader_ttbar_->AddVariable( "nJets", &njets_var );
  TMVAReader_ttbar_->AddVariable( "dR_l1_j", &dR_l1_j_var );
  TMVAReader_ttbar_->AddVariable( "dR_l2_j", &dR_l2_j_var );
  TMVAReader_ttbar_->AddVariable( "MT_l1_met", &MT_l1_met_var );
  TMVAReader_ttbar_->AddVariable( "min(met,400)", &met_var );
  TMVAReader_ttbar_->AddVariable( "avg_dR_jets", &avg_dr_jets_var );
  //  TString ttbar_weights = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/classifiers/weights/TMVAClassification_BDTG.weights_ttbar_extraction_original.xml";
  TString ttbar_weights = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/classifiers/weights/TMVAClassification_BDTG.weights_ttbar_extraction_original_v2.xml";
  TMVAReader_ttbar_->BookMVA("BDTG method", ttbar_weights);

  TMVA::Reader* TMVAReader_ttbar_recoBdt_ = new TMVA::Reader( "!Color:!Silent" );
  TMVAReader_ttbar_recoBdt_->AddVariable( "max_lep_eta", &max_lep_eta_var );
  TMVAReader_ttbar_recoBdt_->AddVariable( "nJets", &njets_var );
  TMVAReader_ttbar_recoBdt_->AddVariable( "dR_l1_j", &dR_l1_j_var );
  TMVAReader_ttbar_recoBdt_->AddVariable( "dR_l2_j", &dR_l2_j_var );
  TMVAReader_ttbar_recoBdt_->AddVariable( "MT_l1_met", &MT_l1_met_var );
  TMVAReader_ttbar_recoBdt_->AddVariable( "min(met,400)", &met_var );
  TMVAReader_ttbar_recoBdt_->AddVariable( "avg_dR_jets", &avg_dr_jets_var );
  TMVAReader_ttbar_recoBdt_->AddVariable( "reco_score", &reco_score_var );
  TString ttbar_recoBdt_weights = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/classifiers/weights/TMVAClassification_BDTG.weights_ttbar_extraction_reco.xml";
  TMVAReader_ttbar_recoBdt_->BookMVA("BDTG method", ttbar_recoBdt_weights);

  TMVA::Reader* TMVAReader_ttbar_recoBdt_bLoose_ = new TMVA::Reader( "!Color:!Silent" );
  TMVAReader_ttbar_recoBdt_bLoose_->AddVariable( "max_lep_eta", &max_lep_eta_var );
  TMVAReader_ttbar_recoBdt_bLoose_->AddVariable( "nJets", &njets_var );
  TMVAReader_ttbar_recoBdt_bLoose_->AddVariable( "dR_l1_j", &dR_l1_j_var );
  TMVAReader_ttbar_recoBdt_bLoose_->AddVariable( "dR_l2_j", &dR_l2_j_var );
  TMVAReader_ttbar_recoBdt_bLoose_->AddVariable( "MT_l1_met", &MT_l1_met_var );
  TMVAReader_ttbar_recoBdt_bLoose_->AddVariable( "min(met,400)", &met_var );
  TMVAReader_ttbar_recoBdt_bLoose_->AddVariable( "avg_dR_jets", &avg_dr_jets_var );
  TMVAReader_ttbar_recoBdt_bLoose_->AddVariable( "reco_score", &reco_score_var );
  TString ttbar_recoBdt_bLoose_weights = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/classifiers/weights/TMVAClassification_BDTG.weights_ttbar_extraction_reco_bLoose_v2.xml";
  TMVAReader_ttbar_recoBdt_bLoose_->BookMVA("BDTG method", ttbar_recoBdt_bLoose_weights);

  TMVA::Reader* TMVAReader_ttbar_recoBdt_bTight_ = new TMVA::Reader( "!Color:!Silent" );
  TMVAReader_ttbar_recoBdt_bTight_->AddVariable( "max_lep_eta", &max_lep_eta_var );
  TMVAReader_ttbar_recoBdt_bTight_->AddVariable( "nJets", &njets_var );
  TMVAReader_ttbar_recoBdt_bTight_->AddVariable( "dR_l1_j", &dR_l1_j_var );
  TMVAReader_ttbar_recoBdt_bTight_->AddVariable( "dR_l2_j", &dR_l2_j_var );
  TMVAReader_ttbar_recoBdt_bTight_->AddVariable( "MT_l1_met", &MT_l1_met_var );
  TMVAReader_ttbar_recoBdt_bTight_->AddVariable( "min(met,400)", &met_var );
  TMVAReader_ttbar_recoBdt_bTight_->AddVariable( "avg_dR_jets", &avg_dr_jets_var );
  TMVAReader_ttbar_recoBdt_bTight_->AddVariable( "reco_score", &reco_score_var );
  TString ttbar_recoBdt_bTight_weights = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/classifiers/weights/TMVAClassification_BDTG.weights_ttbar_extraction_reco_bTight_v2.xml";
  TMVAReader_ttbar_recoBdt_bTight_->BookMVA("BDTG method", ttbar_recoBdt_bTight_weights);

  TMVA::Reader* TMVAReader_ttV_ = new TMVA::Reader( "!Color:!Silent" );
  TMVAReader_ttV_->AddVariable( "max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))", &max_lep_eta_var );
  TMVAReader_ttV_->AddVariable( "MT_met_lep1", &MT_l1_met_var );
  TMVAReader_ttV_->AddVariable( "nJet25_Recl", &njets_var );
  TMVAReader_ttV_->AddVariable( "mindr_lep1_jet", &dR_l1_j_var );
  TMVAReader_ttV_->AddVariable( "mindr_lep2_jet", &dR_l2_j_var );
  TMVAReader_ttV_->AddVariable( "LepGood_conePt[iF_Recl[0]]", &lep1_pt_var );
  TMVAReader_ttV_->AddVariable( "LepGood_conePt[iF_Recl[1]]", &lep2_pt_var );
  TMVAReader_ttV_->AddSpectator( "iF_Recl[0]", &spec0_var );
  TMVAReader_ttV_->AddSpectator( "iF_Recl[1]", &spec1_var );
  TMVAReader_ttV_->AddSpectator( "iF_Recl[2]", &spec2_var );
  TString ttV_weights = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/simpleweights/final_BDT_forApproval/weights/2lss_ttV_BDTG.weights.xml";
  TMVAReader_ttV_->BookMVA("BDTG method", ttV_weights);

  int chainentries = chain->GetEntries();   
  cout << "# events in tree: "<< chainentries << endl;  
  
  double mcwgt_intree = -999.;
  int eventnum_intree = -999;
  vector<ttH::Jet> *preselected_jets_intree=0;
  vector<ttH::Lepton> *tight_leptons_intree=0;
  vector<ttH::Tau> *selected_taus_intree=0;
  vector<ttH::MET> *met_intree=0;
  double reco_score_intree=-999.;

  chain->SetBranchStatus("*",0);
  chain->SetBranchStatus("eventnum",1);
  chain->SetBranchStatus("mcwgt",1);
  chain->SetBranchStatus("preselected_jets.*",1);
  chain->SetBranchStatus("selected_taus.*",1);
  chain->SetBranchStatus("tightMvaBased_leptons.*",1);
  chain->SetBranchStatus("met.*",1);
  chain->SetBranchStatus("reco_score",1);

  chain->SetBranchAddress("eventnum", &eventnum_intree);
  chain->SetBranchAddress("mcwgt", &mcwgt_intree);
  chain->SetBranchAddress("preselected_jets", &preselected_jets_intree);
  chain->SetBranchAddress("selected_taus", &selected_taus_intree);
  chain->SetBranchAddress("tightMvaBased_leptons", &tight_leptons_intree);
  chain->SetBranchAddress("met", &met_intree);
  chain->SetBranchAddress("reco_score", &reco_score_intree);

  double mcwgt_branch=-999.;
  double max_lep_eta_branch=-999.;
  double njets_branch=-999.;
  double dR_l1_j_branch=-999.;
  double dR_l2_j_branch=-999.;
  double met_branch=-999.;
  double avg_dr_jets_branch=-999.;
  double mt_lep1_met_branch=-999.;
  double l1_pt_branch=-999.;
  double l2_pt_branch=-999.;
  double reco_score_branch=-999.;
  double vs_ttbar_score=-999.;
  double vs_ttbar_bdtReco_score=-999.;
  double vs_ttv_score=-999.;
  bool isBtight_branch=false;
  bool isPositive_branch=false;
  bool isTau_branch=false;
  TString flavor_branch = "null";

  //  TTree *extraction_tree = (TTree*)chain->CloneTree(0);
  TTree *extraction_tree = new TTree("extraction_tree_v3","tree containing signal extraction output");
  extraction_tree->Branch("mcwgt", &mcwgt_branch);
  extraction_tree->Branch("max_lep_eta", &max_lep_eta_branch);
  extraction_tree->Branch("nJets", &njets_branch);
  extraction_tree->Branch("dR_l1_j", &dR_l1_j_branch);
  extraction_tree->Branch("dR_l2_j", &dR_l2_j_branch);
  extraction_tree->Branch("met", &met_branch);
  extraction_tree->Branch("avg_dR_jets", &avg_dr_jets_branch);
  extraction_tree->Branch("MT_l1_met", &mt_lep1_met_branch);
  extraction_tree->Branch("l1_pt", &l1_pt_branch);
  extraction_tree->Branch("l2_pt", &l2_pt_branch);
  extraction_tree->Branch("reco_score", &reco_score_branch);
  extraction_tree->Branch("vs_ttbar_bdt_score", &vs_ttbar_score);
  extraction_tree->Branch("vs_ttbar_bdtReco_bdt_score", &vs_ttbar_bdtReco_score);
  extraction_tree->Branch("vs_ttv_bdt_score", &vs_ttv_score);
  extraction_tree->Branch("bTight_category", &isBtight_branch);
  extraction_tree->Branch("posCharge_category", &isPositive_branch);
  extraction_tree->Branch("tau_category", &isTau_branch);
  extraction_tree->Branch("flavor_category", &flavor_branch);


  Int_t cachesize = 250000000;   //250 MBytes
  chain->SetCacheSize(cachesize);
  chain->SetCacheLearnEntries(20); 
  
  double starttime = get_wall_time();
  //  chainentries = 10000;
  for (int i=0; i<chainentries; i++)
    {
      
      printProgress(i,chainentries);
      chain->GetEntry(i);
      auto lepton_collection_to_use = tight_leptons_intree;
      //      auto lepton_collection_to_use = loose_leptons_intree;

      
      //////////////////////////
      ////
      //// calculate new vars
      ////
      //////////////////////////

      ////////////////////////
      //
      // evaluate_categories
      //
      ////////////////////////
      double tight_wp = 0.8;
      int num_tight = 0;
      for (const auto & jet : *preselected_jets_intree)	if (jet.csv >= tight_wp) num_tight +=1; 

      if ( num_tight > 1 ) isBtight_branch = true;
      else isBtight_branch = false;
      
      if ((*lepton_collection_to_use)[0].charge > 0) isPositive_branch = true;
      else isPositive_branch = false;
      
      if ( selected_taus_intree->size() > 0) isTau_branch = true;
      else isTau_branch = false;
      
      if (abs((*lepton_collection_to_use)[0].pdgID) == 11 && abs((*lepton_collection_to_use)[1].pdgID) == 11) flavor_branch = "ee";
      else if (abs((*lepton_collection_to_use)[0].pdgID) == 13 && abs((*lepton_collection_to_use)[1].pdgID) == 13) flavor_branch = "mm";
      else flavor_branch = "em";

      ////////////////////////
      //
      // evaluate mva scores
      //
      ////////////////////////

      // max eta
      max_lep_eta_var = -1.;
      for (const auto & lep: *lepton_collection_to_use)	if (abs(lep.obj.eta()) > max_lep_eta_var) max_lep_eta_var = abs(lep.obj.eta());

      // njets
      njets_var = preselected_jets_intree->size();
      
      // find highest pt leptons
      ttH::Lepton lep1;
      ttH::Lepton lep2;
      if ((*lepton_collection_to_use)[0].obj.pt() > (*lepton_collection_to_use)[1].obj.pt())
	{
	  lep1 = (*lepton_collection_to_use)[0];
	  lep2 = (*lepton_collection_to_use)[1];
	}
      else
	{
	  lep1 = (*lepton_collection_to_use)[1];
	  lep2 = (*lepton_collection_to_use)[0];
	}
      lep1_pt_var = lep1.obj.pt();
      lep2_pt_var = lep2.obj.pt();

      ttH::Jet lep1_closest_jet = getClosestJet(*preselected_jets_intree, lep1);
      ttH::Jet lep2_closest_jet = getClosestJet(*preselected_jets_intree, lep2);
      dR_l1_j_var = getDeltaR(lep1_closest_jet, lep1);
      dR_l2_j_var = getDeltaR(lep2_closest_jet, lep2);

      // met
      met_var = min( (*met_intree)[0].obj.Pt(), 400. );

      TLorentzVector met_tlv = setTlv( (*met_intree)[0] );
      TLorentzVector lep1_t_tlv = setTlv( lep1 );
      lep1_t_tlv.SetPxPyPzE(lep1_t_tlv.Px(), lep1_t_tlv.Py(), 0., lep1_t_tlv.Pt());
      TLorentzVector lep1_met_t_tlv = met_tlv + lep1_t_tlv;
      MT_l1_met_var = lep1_met_t_tlv.M();

      //calculate avg dr jets
      int jet1_counter = 0;
      double dr_sum = 0.;
      int dr_denom = 0;
      for (const auto & jet1 : *preselected_jets_intree)
	{
	  int jet2_counter = -1;
	  for (const auto & jet2 : *preselected_jets_intree)
	    {
	      jet2_counter +=1;
	      if ( jet2_counter <= jet1_counter ) continue;
	      double delta_r = getDeltaR(jet1, jet2);
	      dr_sum += delta_r;
	      dr_denom +=1;
	    }
	  jet1_counter +=1;
	}
      
      avg_dr_jets_var = dr_sum/double(dr_denom);

      
      max_lep_eta_branch = max_lep_eta_var;
      njets_branch = njets_var;
      dR_l1_j_branch = dR_l1_j_var;
      dR_l2_j_branch = dR_l2_j_var;
      met_branch = met_var;
      avg_dr_jets_branch = avg_dr_jets_var;
      mt_lep1_met_branch = MT_l1_met_var;
      l1_pt_branch = lep1_pt_var;
      l2_pt_branch = lep2_pt_var;

      reco_score_var = reco_score_intree;
      reco_score_branch = reco_score_var;

      vs_ttbar_score = TMVAReader_ttbar_->EvaluateMVA( "BDTG method" );
      //      if ( isBtight_branch ) vs_ttbar_bdtReco_score = TMVAReader_ttbar_recoBdt_bTight_->EvaluateMVA( "BDTG method" );
      if ( isBtight_branch ) vs_ttbar_bdtReco_score = TMVAReader_ttbar_recoBdt_->EvaluateMVA( "BDTG method" );
      else  vs_ttbar_bdtReco_score = TMVAReader_ttbar_recoBdt_bLoose_->EvaluateMVA( "BDTG method" );
      vs_ttv_score = TMVAReader_ttV_->EvaluateMVA( "BDTG method" );

      mcwgt_branch = mcwgt_intree;      
      extraction_tree->Fill();      
    }
  
  
  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (chainentries>0) cout << "an average of " << (endtime - starttime) / chainentries << " per event." << endl;
  
  extraction_tree->Write("",TObject::kOverwrite);
  output_file->Close();  
}

void evaluateSignalExtraction(void)
{
  // TString output_file_name1 = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v1p5_bTightLoose/ttH_aMCatNLO_bdtEval.root";
  // //  TString output_file_name1 = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v1p5_bTightLoose/ttbar_powheg_bdtEval__test.root";
  // TFile *io_file1 = new TFile(output_file_name1, "UPDATE"); //"UPDATE");
  // TChain *chain1 = new TChain("ss2l_tree");
  // chain1->Add(output_file_name1);
  // run_it(chain1,io_file1);

  // TString output_file_name2 = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v1p5_bTightLoose/ttbar_powheg_bdtEval.root";
  // TFile *io_file2 = new TFile(output_file_name2, "UPDATE"); //"UPDATE");
  // TChain *chain2 = new TChain("ss2l_tree");
  // chain2->Add(output_file_name2);
  // run_it(chain2,io_file2);

  // TString output_file_name3 = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v1p5_bTightLoose/ttw_aMCatNLO_2lss_bdtEval_v1p5.root";
  // TFile *io_file3 = new TFile(output_file_name3, "UPDATE"); //"UPDATE");
  // TChain *chain3 = new TChain("ss2l_tree");
  // chain3->Add(output_file_name3);
  // run_it(chain3,io_file3);

  // TString output_file_name4 = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v1p5_bTightLoose/ttz_aMCatNLO_2lss_bdtEval_v1p5.root";
  // TFile *io_file4 = new TFile(output_file_name4, "UPDATE"); //"UPDATE");
  // TChain *chain4 = new TChain("ss2l_tree");
  // chain4->Add(output_file_name4);
  // run_it(chain4,io_file4);

  TString output_file_name5 = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v1p5_bTightLoose/ttbar_dilep_mg5mlm_2lss_bdtEval_v1p5.root";
  TFile *io_file5 = new TFile(output_file_name5, "UPDATE"); //"UPDATE");
  TChain *chain5 = new TChain("ss2l_tree");
  chain5->Add(output_file_name5);
  run_it(chain5,io_file5);
}
