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
  vector<ttH::Electron> *preselected_electrons_intree=0;
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

  chain->SetBranchStatus("*",0);
  chain->SetBranchStatus("eventnum",1);
  chain->SetBranchStatus("mcwgt",1);
  chain->SetBranchStatus("preselected_jets.*",1);
  chain->SetBranchStatus("looseMvaBased_leptons.*",1);
  chain->SetBranchStatus("tightMvaBased_leptons.*",1);
  chain->SetBranchStatus("met.*",1);
  chain->SetBranchStatus("reco_score",1);
  
  chain->SetBranchAddress("preselected_jets", &preselected_jets_intree);
  chain->SetBranchAddress("looseMvaBased_leptons", &loose_leptons_intree);
  chain->SetBranchAddress("tightMvaBased_leptons", &tight_leptons_intree);
  chain->SetBranchAddress("met", &met_intree);
  
  double max_lep_eta_branch;
  double njets_branch;
  double dR_l1_j_branch;
  double dR_l2_j_branch;
  double met_branch;
  double avg_dr_jets_branch;
  double mt_lep1_met_branch;
  double l1_pt_branch;
  double l2_pt_branch;

  TTree *ttH_vs_ttbar_tree = (TTree*)chain->CloneTree(0);
  ttH_vs_ttbar_tree->SetName("tth_vs_ttbar_tree");
  ttH_vs_ttbar_tree->Branch("max_lep_eta", &max_lep_eta_branch);
  ttH_vs_ttbar_tree->Branch("nJets", &njets_branch);
  ttH_vs_ttbar_tree->Branch("dR_l1_j", &dR_l1_j_branch);
  ttH_vs_ttbar_tree->Branch("dR_l2_j", &dR_l2_j_branch);
  ttH_vs_ttbar_tree->Branch("met", &met_branch);  
  ttH_vs_ttbar_tree->Branch("avg_dR_jets", &avg_dr_jets_branch);
  ttH_vs_ttbar_tree->Branch("MT_l1_met", &mt_lep1_met_branch);

  TTree *ttH_vs_ttV_tree = (TTree*)chain->CloneTree(0);
  ttH_vs_ttV_tree->SetName("tth_vs_ttV_tree");
  ttH_vs_ttV_tree->Branch("max_lep_eta", &max_lep_eta_branch);
  ttH_vs_ttV_tree->Branch("nJets", &njets_branch);
  ttH_vs_ttV_tree->Branch("dR_l1_j", &dR_l1_j_branch);
  ttH_vs_ttV_tree->Branch("dR_l2_j", &dR_l2_j_branch);
  ttH_vs_ttV_tree->Branch("MT_l1_met", &mt_lep1_met_branch);
  ttH_vs_ttV_tree->Branch("l1_pt", &l1_pt_branch);
  ttH_vs_ttV_tree->Branch("l2_pt", &l2_pt_branch);

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

      auto lepton_collection_to_use = tight_leptons_intree;
      //      auto lepton_collection_to_use = loose_leptons_intree;

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

      ttH::Jet lep1_closest_jet = getClosestJet(*preselected_jets_intree, lep1);
      ttH::Jet lep2_closest_jet = getClosestJet(*preselected_jets_intree, lep2);
      dR_l1_j_branch = getDeltaR(lep1_closest_jet, lep1);
      dR_l2_j_branch = getDeltaR(lep2_closest_jet, lep2);

      // met
      met_branch = (*met_intree)[0].obj.Pt();

      TLorentzVector met_tlv = setTlv( (*met_intree)[0] );
      TLorentzVector lep1_t_tlv = setTlv( lep1 );
      lep1_t_tlv.SetPxPyPzE(lep1_t_tlv.Px(), lep1_t_tlv.Py(), 0., lep1_t_tlv.Pt());
      TLorentzVector lep1_met_t_tlv = met_tlv + lep1_t_tlv;
      mt_lep1_met_branch = lep1_met_t_tlv.M();

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
  //  TString output_file = "signal_extraction/training/ttbar-semiLep-madgraph_relaxedTrainSelection_tree_2lss.root";
  TString output_file = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/signal_extraction/testing/ttH_aMCatNLO_bdtEval.root";
  //  TString output_file = "signal_extraction/training/ttH_powhegForSigExtraction_bdtEval_v1p5.root";
  TFile *io_file = new TFile(output_file, "UPDATE"); // #, 'test' ) // "RECREATE");
  TChain *chain = new TChain("ss2l_tree");
  chain->Add(output_file);
  run_it(chain,io_file);
}
