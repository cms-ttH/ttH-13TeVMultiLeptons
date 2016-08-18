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

  TMVA::Reader* TMVAReader_ttbar_ = new TMVA::Reader( "!Color:!Silent" );
  TMVAReader_ttbar_->AddVariable( "max_lep_eta", &max_lep_eta_var );
  TMVAReader_ttbar_->AddVariable( "nJets", &njets_var );
  TMVAReader_ttbar_->AddVariable( "dR_l1_j", &dR_l1_j_var );
  TMVAReader_ttbar_->AddVariable( "dR_l2_j", &dR_l2_j_var );
  TMVAReader_ttbar_->AddVariable( "MT_l1_met", &MT_l1_met_var );
  TMVAReader_ttbar_->AddVariable( "met", &met_var );
  TMVAReader_ttbar_->AddVariable( "avg_dR_jets", &avg_dr_jets_var );
  //  TMVAReader_ttbar_->AddVariable( "reco_score", &reco_score_var );
  TString ttbar_weights = "";
  TMVAReader_ttbar_->BookMVA("BDTG method", ttbar_weights);


  TMVA::Reader* TMVAReader_ttV_ = new TMVA::Reader( "!Color:!Silent" );
  TMVAReader_ttV_->AddVariable( "max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))", &max_lep_eta_var );
  TMVAReader_ttV_->AddVariable( "MT_met_lep1", &MT_l1_met_var );
  TMVAReader_ttV_->AddVariable( "nJet25_Recl", &njets_var );
  TMVAReader_ttV_->AddVariable( "mindr_lep1_jet", &dR_l1_j_var );
  TMVAReader_ttV_->AddVariable( "mindr_lep2_jet", &dR_l2_j_var );
  TMVAReader_ttV_->AddVariable( "LepGood_conePt[iF_Recl[0]]", &lep1_pt_var );
  TMVAReader_ttV_->AddVariable( "LepGood_conePt[iF_Recl[1]]", &lep2_pt_var );
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

  TFile *copiedfile = new TFile(output_file, "RECREATE"); //"UPDATE"); // #, 'test' ) // "RECREATE");

  double max_lep_eta_branch=-999.;
  double njets_branch=-999.;
  double dR_l1_j_branch=-999.;
  double dR_l2_j_branch=-999.;
  double met_branch=-999.;
  double avg_dr_jets_branch=-999.;
  double mt_lep1_met_branch=-999.;
  double l1_pt_branch=-999.;
  double l2_pt_branch=-999.;
  double vs_ttbar_score=-999.;
  double vs_ttv_score=-999.;
  bool isBtight=false;
  bool isPositive=false;
  bool isTau=false;
  bool isEE=false;
  bool isEM=false;
  bool isMM=false;

  //  TTree *extraction_tree = (TTree*)chain->CloneTree(0);
  TTree *extraction_tree = new TTree("extraction_tree","tree containing signal extraction output");
  //  extraction_tree->SetName("extraction_tree");
  extraction_tree->Branch("max_lep_eta", &max_lep_eta_branch);
  extraction_tree->Branch("nJets", &njets_branch);
  extraction_tree->Branch("dR_l1_j", &dR_l1_j_branch);
  extraction_tree->Branch("dR_l2_j", &dR_l2_j_branch);
  extraction_tree->Branch("met", &met_branch);
  extraction_tree->Branch("avg_dR_jets", &avg_dr_jets_branch);
  extraction_tree->Branch("MT_l1_met", &mt_lep1_met_branch);
  extraction_tree->Branch("l1_pt", &l1_pt_branch);
  extraction_tree->Branch("l2_pt", &l2_pt_branch);
  extraction_tree->Branch("vs_ttbar_bdt_score", &vs_ttbar_score);
  extraction_tree->Branch("vs_ttv_bdt_score", &vs_ttv_score);
  extraction_tree->Branch("bTight_category", &isBtight);
  extraction_tree->Branch("posCharge_category", &isPositive);
  extraction_tree->Branch("tau_category", &isTau);
  extraction_tree->Branch("ee_category", &isEE);
  extraction_tree->Branch("em_category", &isEM);
  extraction_tree->Branch("mm_category", &isMM);

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
      for (const auto & jet : *preselected_jets_intree)
	{
	  if (jet.csv >= tight_wp) num_tight +=1; 
	}
      if ( num_tight > 1 ) isBtight = true;
      else isBtight = false;
      
      if ((*lepton_collection_to_use)[0].charge > 0) isPositive = true;
      else isPositive = false;
      
      if ( selected_taus_intree->size() > 0) isTau = true;
      else isTau = false;

      isEE=false;
      isEM=false;
      isMM=false;
      if (abs((*lepton_collection_to_use)[0].pdgID) == 11 && abs((*lepton_collection_to_use)[1].pdgID) == 11) isEE = true;
      else if (abs((*lepton_collection_to_use)[0].pdgID) == 13 && abs((*lepton_collection_to_use)[1].pdgID) == 13) isMM = true;
      else isEM = true;
      

      ////////////////////////
      //
      // evaluate mva scores
      //
      ////////////////////////

      // max eta
      max_lep_eta_var = -1.;
      for (const auto & lep: *lepton_collection_to_use)
	{
	  if (abs(lep.obj.eta()) > max_lep_eta_var)
	    {
	      max_lep_eta_var = abs(lep.obj.eta());
	    }
	}

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
      met_var = (*met_intree)[0].obj.Pt();

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

      vs_ttbar_score = TMVAReader_ttbar_->EvaluateMVA( "BDTG method" );
      vs_ttV_score = TMVAReader_ttV_->EvaluateMVA( "BDTG method" );

      
      if ( vs_ttbar_score <= -0.2) final_shape_hist->Fill(1, mcwgt_intree);
      else if ( vs_ttbar_score <= 0.1) final_shape_hist->Fill(2, mcwgt_intree);
      else if ( vs_ttbar_score <= 0.4 )
	{
	  if ( vs_ttV_score <= 0.3 ) final_shape_hist->Fill(3, mcwgt_intree);
	  else final_shape_hist->Fill(4, mcwgt_intree);
	}
      else if ( vs_ttV_score <= 0.1 ) final_shape_hist->Fill(5, mcwgt_intree);
      else if ( vs_ttV_score <= 0.4 ) final_shape_hist->Fill(6, mcwgt_intree);
      else final_shape_hist->Fill(7, mcwgt_intree);

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
  TString output_file_name = "";
  TFile *io_file = new TFile(output_file_name, "UPDATE"); //"UPDATE");
  TChain *chain = new TChain("ss2l_tree");
  chain->Add(output_file_name);
  run_it(chain,io_file);
}
