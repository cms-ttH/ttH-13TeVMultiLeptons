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
#include <math.h>
#include "TLorentzVector.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/src/classes.h"
#include "TMVA/Config.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#include "selection.h"
#include "treeTools.h"


/////////////////////////////////////////
///
/// usage: root -l makeSigExtractionTrees.C+
///
/////////////////////////////////////////


void run_it(TChain* chain, TFile *io_file_)
{

  int chainentries = chain->GetEntries();   
  cout << "# events in tree: "<< chainentries << endl;  
  
  double wgt_intree = -999.;
  double wallTimePerEvent_intree = -99.;  
  int eventnum_intree = -999;
  int higgs_decay_intree = -9999;
  int lumiBlock_intree = -999;
  int runNumber_intree = -999;

  vector<ttH::Lepton> *preselected_leptons_intree=0;
  vector<ttH::Lepton> *loose_leptons_intree=0;
  vector<ttH::Electron> *raw_electrons_intree=0;               
  vector<ttH::Electron> *loose_electrons_intree=0;
  vector<ttH::Muon> *raw_muons_intree=0;
  vector<ttH::Muon> *preselected_muons_intree=0;
  vector<ttH::Jet> *preselected_jets_intree=0;
  vector<ttH::Jet> *preselected_jets_genMatch_intree=0;
  vector<ttH::MET> *met_intree=0;
  vector<ttH::GenParticle> *pruned_genParticles_intree=0;
  vector<ttH::Lepton> *tight_leptons_intree=0;
  vector<ttH::Electron> *tight_electrons_intree=0;
  vector<ttH::Muon> *tight_muons_intree=0;


  ttH::Jet *b_from_leptop_intree=0;
  ttH::Jet *b_from_hadtop_intree=0;
  ttH::Lepton *lep_from_leptop_intree=0;
  ttH::Lepton *lep_from_higgs_intree=0;

  TLorentzVector *higgs_intree=0;
  TLorentzVector *lepTop_intree=0;
  TLorentzVector *hadTop_intree=0;

  //  double reco_score_intree;
  //  double reco_score_tr1_inclusivebloose_intree;
  //  double reco_score_tr1_btightloose_intree;

  chain->SetBranchStatus("*",0);
  chain->SetBranchStatus("eventnum",1);
  chain->SetBranchStatus("mcwgt",1);
  chain->SetBranchStatus("preselected_jets.*",1);
  chain->SetBranchStatus("looseMvaBased_leptons.*",1);
  chain->SetBranchStatus("preselected_leptons.*",1);
  chain->SetBranchStatus("looseMvaBased_electrons.*",1);
  chain->SetBranchStatus("tightMvaBased_leptons.*",1);
  chain->SetBranchStatus("met.*",1);
  chain->SetBranchStatus("reco_score",1);
  chain->SetBranchStatus("reco_score_tr1_btightloose",1);
  chain->SetBranchStatus("reco_score_tr1_inclusivebloose",1);
  
  chain->SetBranchAddress("preselected_jets", &preselected_jets_intree);
  chain->SetBranchAddress("looseMvaBased_leptons", &loose_leptons_intree);
  chain->SetBranchAddress("preselected_leptons", &preselected_leptons_intree);
  chain->SetBranchAddress("looseMvaBased_electrons", &loose_electrons_intree);
  chain->SetBranchAddress("tightMvaBased_leptons", &tight_leptons_intree);
  chain->SetBranchAddress("met", &met_intree);
  //  chain->SetBranchAddress("reco_score", &reco_score_intree);
  
  double max_lep_eta_branch;
  double njets_branch;
  double dR_l1_j_branch;
  double dR_l2_j_branch;
  double met_branch;
  double avg_dr_jets_branch;
  double mt_lep1_met_branch;
  double l1_pt_branch;
  double l2_pt_branch;
  bool bTight_branch;

  double l1_conePt_branch;
  double csv1_branch;
  double csv2_branch;

  TTree *ttH_vs_ttbar_tree = (TTree*)chain->CloneTree(0);
  ttH_vs_ttbar_tree->SetName("tth_vs_ttbar_tree");
  ttH_vs_ttbar_tree->Branch("max_Lep_eta", &max_lep_eta_branch);
  ttH_vs_ttbar_tree->Branch("numJets_float", &njets_branch);
  ttH_vs_ttbar_tree->Branch("mindr_lep1_jet", &dR_l1_j_branch);
  ttH_vs_ttbar_tree->Branch("mindr_lep2_jet", &dR_l2_j_branch);
  ttH_vs_ttbar_tree->Branch("met_double", &met_branch);  
  ttH_vs_ttbar_tree->Branch("avg_dr_jet", &avg_dr_jets_branch);
  ttH_vs_ttbar_tree->Branch("MT_met_lep1", &mt_lep1_met_branch);
  ttH_vs_ttbar_tree->Branch("isBtight", &bTight_branch);
  ttH_vs_ttbar_tree->Branch("lep1_conePt", &l1_conePt_branch);
  ttH_vs_ttbar_tree->Branch("lep1_Pt", &l1_pt_branch);
  ttH_vs_ttbar_tree->Branch("csv1", &csv1_branch);
  ttH_vs_ttbar_tree->Branch("csv2", &csv2_branch);
 

  TTree *ttH_vs_ttV_tree = (TTree*)chain->CloneTree(0);
  ttH_vs_ttV_tree->SetName("tth_vs_ttV_tree");
  ttH_vs_ttV_tree->Branch("max_Lep_eta", &max_lep_eta_branch);
  ttH_vs_ttV_tree->Branch("numJets_float", &njets_branch);
  ttH_vs_ttV_tree->Branch("mindr_lep1_jet", &dR_l1_j_branch);
  ttH_vs_ttV_tree->Branch("mindr_lep2_jet", &dR_l2_j_branch);
  ttH_vs_ttV_tree->Branch("MT_met_lep1", &mt_lep1_met_branch);
  ttH_vs_ttV_tree->Branch("l1_pt", &l1_pt_branch);
  ttH_vs_ttV_tree->Branch("l2_pt", &l2_pt_branch);
  ttH_vs_ttV_tree->Branch("isBtight", &bTight_branch);
  ttH_vs_ttV_tree->Branch("csv1", &csv1_branch);
  ttH_vs_ttV_tree->Branch("csv2", &csv2_branch);
 
  Int_t cachesize = 250000000;   //250 MBytes
  chain->SetCacheSize(cachesize);
  chain->SetCacheLearnEntries(20); 
  
  double starttime = get_wall_time();
  //  chainentries = 10000;
  for (int i=0; i<chainentries; i++)
    {
      
      printProgress(i,chainentries);
      chain->GetEntry(i);
      
      //////////////////////////
      ////
      //// calculate new vars
      ////
      //////////////////////////

      ///////////////////////////////////////
      ///////////////////////////////////////
      ////// choose lepton collection
      ///////////////////////////////////////
      ///////////////////////////////////////

      //      auto lepton_collection_to_use = tight_leptons_intree;
      //      auto lepton_collection_to_use = loose_leptons_intree;
      auto lepton_collection_to_use = preselected_leptons_intree;

      ///////////////////////////////////////
      ///////////////////////////////////////
      ///////////////////////////////////////
      ///////////////////////////////////////


      // max eta
      max_lep_eta_branch = -1.;
      for (const auto & lep: *lepton_collection_to_use)
	{
	  if (abs(lep.obj.eta()) > max_lep_eta_branch)
	    {
	      max_lep_eta_branch = abs(lep.obj.eta());
	    }
	}

      // njets
      njets_branch = preselected_jets_intree->size();
      
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
      l1_pt_branch = lep1.obj.pt();
      l2_pt_branch = lep2.obj.pt();


      // bool skip_event = false;
      // for (const auto & ele : *loose_electrons_intree)
      // 	{
      // 	  if ( (lep1.obj.pt() == ele.obj.pt() || lep2.obj.pt() == ele.obj.pt()) && ele.numMissingInnerHits > 0)
      // 	    {
      // 	      skip_event = true;
      // 	      break;
      // 	    }
      // 	}
      // if ( skip_event ) continue;

      auto csv_sorted_jets = *preselected_jets_intree;
      std::sort(csv_sorted_jets.begin(), csv_sorted_jets.end(), [] (ttH::Jet a, ttH::Jet b) { return a.csv > b.csv;});
      csv1_branch = csv_sorted_jets[0].csv;
      csv2_branch = max( csv_sorted_jets[1].csv, 0.);

      ttH::Jet lep1_closest_jet = getClosestJet(*preselected_jets_intree, lep1);
      ttH::Jet lep2_closest_jet = getClosestJet(*preselected_jets_intree, lep2);
      dR_l1_j_branch = getDeltaR(lep1_closest_jet, lep1);
      dR_l2_j_branch = getDeltaR(lep2_closest_jet, lep2);

      // met
      met_branch = min((*met_intree)[0].obj.Pt(),400.);

      TLorentzVector met_tlv = setTlv( (*met_intree)[0] );
      TLorentzVector lep1_t_tlv = setTlv( lep1 );

      bool isTight = true;
      // bool isTight = false;
      // for (const auto & lep: *tight_leptons_intree)
      // 	{
      // 	  if (lep1.obj.pt() == lep.obj.pt())
      // 	    {
      // 	      isTight = true;
      // 	      break;
      // 	    }
      // 	}

      if ( !isTight )
	{
	  l1_conePt_branch = lep1.obj.pt()/lep1.jetPtRatio*0.85;
	}
      else 
	{
	  l1_conePt_branch = lep1.obj.pt();
	}

      mt_lep1_met_branch = sqrt(2*l1_conePt_branch*met_branch*(1-cos(lep1.obj.phi()-(*met_intree)[0].obj.phi())));

      //calculate avg dr jets
      int jet1_counter = 0;
      double dr_sum = 0.;
      int dr_denom = 0;
      int num_tight = 0;
      for (const auto & jet1 : *preselected_jets_intree)
	{
	  if ( jet1.csv >= 0.8 ) num_tight +=1;
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
      bTight_branch = ( num_tight > 1);
      avg_dr_jets_branch = dr_sum/double(dr_denom);

      ttH_vs_ttbar_tree->Fill();
      ttH_vs_ttV_tree->Fill();
      
    }
  
  
  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (chainentries>0) cout << "an average of " << (endtime - starttime) / chainentries << " per event." << endl;
  
  ttH_vs_ttbar_tree->Write("", TObject::kOverwrite);
  ttH_vs_ttV_tree->Write("", TObject::kOverwrite);
  io_file_->Close();  
}

void makeSigExtractionTrees(void)
{

  TString input_file1 = "selection_trees/genFilter_tests/ttbar_semiLep_jetClean_test_training_tree_2lss.root";
  TFile *io_file1 = new TFile(input_file1, "UPDATE"); // #, 'test' ) // "RECREATE");
  TChain *chain1 = new TChain("ss2l_tree");
  chain1->Add(input_file1);
  run_it(chain1,io_file1);

  // TString input_file2 = "reco_bdt/training2_tests/tth_powheg_old_relaxed_training_2lss.root";
  // TFile *io_file2 = new TFile(input_file2, "UPDATE"); // #, 'test' ) // "RECREATE");
  // TChain *chain2 = new TChain("ss2l_tree");
  // chain2->Add(input_file2);
  // run_it(chain2,io_file2);
}
