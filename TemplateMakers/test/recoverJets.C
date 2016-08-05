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
#include "DataFormats/Math/interface/deltaR.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/src/classes.h"
#include "TMVA/Config.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#include "selection.h"
#include "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/treeTools.h"

/////////////////////////////////////////
///
/// usage: root -l recoverJets.C+
///
/////////////////////////////////////////



void run_it(TChain* chain, TString output_file)
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
  vector<ttH::Lepton> *tight_leptons_sortedByMiniIso_intree=0;  
  
  ttH::GenParticle *higgs_intree = 0;
  ttH::GenParticle *higgs_child_A_intree=0;
  ttH::GenParticle *higgs_child_B_intree=0;
  ttH::GenParticle *higgs_grandChild_A1_intree=0;
  ttH::GenParticle *higgs_grandChild_A2_intree=0;
  ttH::GenParticle *higgs_grandChild_B1_intree=0;
  ttH::GenParticle *higgs_grandChild_B2_intree=0;
  
  ttH::GenParticle *top_intree=0;
  ttH::GenParticle *top_b_intree=0;
  ttH::GenParticle *top_w_intree=0;
  ttH::GenParticle *top_w_child1_intree=0;
  ttH::GenParticle *top_w_child2_intree=0;
  
  ttH::GenParticle *antitop_intree=0;
  ttH::GenParticle *antitop_b_intree=0;
  ttH::GenParticle *antitop_w_intree=0;
  ttH::GenParticle *antitop_w_child1_intree=0;
  ttH::GenParticle *antitop_w_child2_intree=0;

  TString *higgs_final_state_intree=0;
  TString *ttbar_final_state_intree=0;
  
  // chain->SetBranchStatus("*",0);
  // chain->SetBranchStatus("eventnum",1);
  // chain->SetBranchStatus("preselected_jets.*",1);
  // chain->SetBranchStatus("pruned_genParticles.*",1);
  // chain->SetBranchStatus("higgs",1);
  // chain->SetBranchStatus("higgs_childA",1);
  // chain->SetBranchStatus("higgs_childB",1);
  // chain->SetBranchStatus("higgs_grandChild_A1.",1);
  // chain->SetBranchStatus("higgs_grandChild_A2",1);
  // chain->SetBranchStatus("higgs_grandChild_B1",1);
  // chain->SetBranchStatus("higgs_grandChild_B2",1);
  // chain->SetBranchStatus("top",1);
  // chain->SetBranchStatus("top_b",1);
  // chain->SetBranchStatus("top_w",1);
  // chain->SetBranchStatus("top_w_child1",1);
  // chain->SetBranchStatus("top_w_child2",1);
  // chain->SetBranchStatus("antitop",1);
  // chain->SetBranchStatus("antitop_b",1);
  // chain->SetBranchStatus("antitop_w",1);
  // chain->SetBranchStatus("antitop_w_child1",1);
  // chain->SetBranchStatus("antitop_w_child2",1);
  // chain->SetBranchStatus("higgs_final_state",1);
  // chain->SetBranchStatus("ttbar_final_state",1);

  chain->SetBranchAddress("higgs", &higgs_intree);
  chain->SetBranchAddress("higgs_childA", &higgs_child_A_intree);
  chain->SetBranchAddress("higgs_childB", &higgs_child_B_intree);
  chain->SetBranchAddress("higgs_grandChild_A1", &higgs_grandChild_A1_intree);
  chain->SetBranchAddress("higgs_grandChild_A2", &higgs_grandChild_A2_intree);
  chain->SetBranchAddress("higgs_grandChild_B1", &higgs_grandChild_B1_intree);
  chain->SetBranchAddress("higgs_grandChild_B2", &higgs_grandChild_B2_intree);
  
  chain->SetBranchAddress("top", &top_intree);
  chain->SetBranchAddress("top_b", &top_b_intree);
  chain->SetBranchAddress("top_w", &top_w_intree);
  chain->SetBranchAddress("top_w_child1", &top_w_child1_intree);
  chain->SetBranchAddress("top_w_child2", &top_w_child2_intree);
    
  chain->SetBranchAddress("antitop", &antitop_intree);
  chain->SetBranchAddress("antitop_b", &antitop_b_intree);
  chain->SetBranchAddress("antitop_w", &antitop_w_intree);
  chain->SetBranchAddress("antitop_w_child1", &antitop_w_child1_intree);
  chain->SetBranchAddress("antitop_w_child2", &antitop_w_child2_intree);

  chain->SetBranchAddress("higgs_final_state", &higgs_final_state_intree);
  chain->SetBranchAddress("ttbar_final_state", &ttbar_final_state_intree);

  chain->SetBranchAddress("eventnum", &eventnum_intree);
  chain->SetBranchAddress("pruned_genParticles", &pruned_genParticles_intree);   
  chain->SetBranchAddress("preselected_jets", &preselected_jets_intree);  
  chain->SetBranchAddress("tightMvaBased_leptons", &tight_leptons_intree);  

  TFile *copiedfile = new TFile(output_file, "RECREATE"); //"UPDATE"); // #, 'test' ) // "RECREATE");

  TTree *signal_tree = (TTree*)chain->CloneTree(0);

  vector<double> *deltaR_vec_intree=0;
  vector<ttH::Jet> *matched_reco_jets_intree=0;
  vector<ttH::Jet> *unmatched_reco_jets_intree=0;
  //  vector<ttH::Jet> *_reco_jets_intree=0;
  vector<ttH::GenParticle> *matched_gen_jets_intree=0;
  vector<ttH::GenParticle> *unmatched_gen_jets_intree=0;

  signal_tree->Branch("deltaR", &deltaR_vec_intree);
  signal_tree->Branch("matched_reco_jets", &matched_reco_jets_intree);
  signal_tree->Branch("unmatched_reco_jets", &unmatched_reco_jets_intree);
  signal_tree->Branch("matched_gen_jets", &matched_gen_jets_intree);
  signal_tree->Branch("unmatched_gen_jets", &unmatched_gen_jets_intree);

  Int_t cachesize = 250000000;   //250 MBytes
  chain->SetCacheSize(cachesize);
  chain->SetCacheLearnEntries(20); 
  
  double starttime = get_wall_time();
  //  chainentries = 10000;
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
      //// calculate new vars
      ////
      //////////////////////////

      deltaR_vec_intree->clear();
      matched_reco_jets_intree->clear();
      unmatched_reco_jets_intree->clear();
      matched_gen_jets_intree->clear();
      unmatched_gen_jets_intree->clear();

      vector<ttH::GenParticle> hardScatter_genParticles;
      if ( !isLepton( higgs_grandChild_A1_intree ) ) hardScatter_genParticles.push_back( *higgs_grandChild_A1_intree );
      if ( !isLepton( higgs_grandChild_A2_intree ) ) hardScatter_genParticles.push_back( *higgs_grandChild_A2_intree );
      if ( !isLepton( higgs_grandChild_B1_intree ) ) hardScatter_genParticles.push_back( *higgs_grandChild_B1_intree );
      if ( !isLepton( higgs_grandChild_B2_intree ) ) hardScatter_genParticles.push_back( *higgs_grandChild_B2_intree );
      if ( !isLepton( top_b_intree ) ) hardScatter_genParticles.push_back( *top_b_intree );
      if ( !isLepton( top_w_child1_intree ) ) hardScatter_genParticles.push_back( *top_w_child1_intree );
      if ( !isLepton( top_w_child2_intree ) ) hardScatter_genParticles.push_back( *top_w_child2_intree );
      if ( !isLepton( antitop_b_intree ) ) hardScatter_genParticles.push_back( *antitop_b_intree );
      if ( !isLepton( antitop_w_child1_intree ) ) hardScatter_genParticles.push_back( *antitop_w_child1_intree );
      if ( !isLepton( antitop_w_child2_intree ) ) hardScatter_genParticles.push_back( *antitop_w_child2_intree );


      std::vector<ttH::Jet> temp_unmatched_reco_jets;
      std::vector<ttH::GenParticle> temp_unmatched_gen_jets;

      for (const auto & jet : *preselected_jets_intree)
	{
	  if (jet.genPdgID == 9999)
	    {
	      temp_unmatched_reco_jets.push_back(jet);
	      continue;
	    }
	  for (const auto & gen_jet : hardScatter_genParticles)
	    {
	      double deltaR = getDeltaR(jet, gen_jet);
	      if ( jet.genPdgID == gen_jet.pdgID && deltaR <= 0.5  )
		{
		  deltaR_vec_intree->push_back(deltaR);
		  matched_reco_jets_intree->push_back(jet);
		  matched_gen_jets_intree->push_back(gen_jet);
		  break;
		}
	    }
	}
      
      *unmatched_gen_jets_intree = vector_difference<ttH::GenParticle>(*matched_gen_jets_intree, hardScatter_genParticles);

      for (const auto & gen_j : *unmatched_gen_jets_intree)
      	{
      	  if ( gen_j.obj.pt() > 30 && abs(gen_j.obj.eta()) < 2.4 ) temp_unmatched_gen_jets.push_back(gen_j);
      	}

      for (auto & reco_j : temp_unmatched_reco_jets)
      	{
      	  double min_dr = 99.;
      	  ttH::GenParticle matched_gen_j;
      	  for (const auto & gen_j : temp_unmatched_gen_jets)
      	    {
      	      double dr = getDeltaR(reco_j, gen_j);
      	      if (dr < min_dr)
      		{
      		  min_dr = dr;
      		  matched_gen_j = gen_j;
      		}
      	    }
      	  if (min_dr <= 0.4 && ( abs(1. - matched_gen_j.obj.pt()/reco_j.obj.pt()) < 0.5 ) )
      	    {
      	      reco_j.genPdgID = matched_gen_j.pdgID; 
      	      reco_j.genMotherPdgID = (*pruned_genParticles_intree)[matched_gen_j.mother].pdgID; 
      	      reco_j.genGrandMotherPdgID = (*pruned_genParticles_intree)[matched_gen_j.grandmother].pdgID; 
      	      matched_reco_jets_intree->push_back( reco_j );
      	      matched_gen_jets_intree->push_back( matched_gen_j );
	      
      	    }
      	}
      

      *unmatched_reco_jets_intree = vector_difference<ttH::Jet>(*matched_reco_jets_intree, *preselected_jets_intree);
      *unmatched_gen_jets_intree = vector_difference<ttH::GenParticle>(*matched_gen_jets_intree, hardScatter_genParticles);

      signal_tree->Fill();
      
    }
  
  
  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (chainentries>0) cout << "an average of " << (endtime - starttime) / chainentries << " per event." << endl;
  
  signal_tree->Write();
  copiedfile->Close();  
}

void recoverJets(void)
{
  TString output_file = "jet_study_JetRecovery_pt30_tree.root";
  TChain *chain = new TChain("ss2l_tree;");
  chain->Add("ttH-powheg_selection_tree__good.root");
  run_it(chain,output_file);
}
