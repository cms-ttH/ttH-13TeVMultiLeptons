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


/////////////////////////////////////////
///
/// usage: root -l updateTree.C+
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

  vector<double> *deltaR_PF_matching_intree = 0;
  vector<double> *deltaR_charlie_matching_intree = 0;


  
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

  chain->SetBranchStatus("*",0);
  chain->SetBranchStatus("eventnum",1);
  chain->SetBranchStatus("preselected_jets.*",1);
  chain->SetBranchStatus("pruned_genParticles.*",1);
  
  chain->SetBranchAddress("eventnum", &eventnum_intree);
  chain->SetBranchAddress("pruned_genParticles", &pruned_genParticles_intree);   
  chain->SetBranchAddress("preselected_jets", &preselected_jets_intree);  

  TFile *copiedfile = new TFile(output_file, "RECREATE"); //"UPDATE"); // #, 'test' ) // "RECREATE");

  TTree *signal_tree = (TTree*)chain->CloneTree(0);
  signal_tree->SetName("ps_jet_tree");
  signal_tree->Branch("preselected_jets_genMatch", &preselected_jets_genMatch_intree);
  signal_tree->Branch("deltaR_pflow_genJet_matching", &deltaR_PF_matching_intree);
  signal_tree->Branch("deltaR_charlie_genJet_matching", &deltaR_charlie_matching_intree);

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

      preselected_jets_genMatch_intree->clear();
      deltaR_PF_matching_intree->clear();
      deltaR_charlie_matching_intree->clear();
      
      double this_deltaR;
      double min_deltaR = 99.;
      ttH::GenParticle gen_preselected_jet;
      ttH::Jet genMatched_reco_jet;
      
      for (const auto & reco_jet : *preselected_jets_intree)
	{
	  min_deltaR = 99.;
	  if (reco_jet.genPdgID < 9999.)
	    {
	      for (const auto & gen_jet : *pruned_genParticles_intree)
		{
		  if ( reco_jet.genPdgID == gen_jet.pdgID)
		    {
		      this_deltaR = reco::deltaR( reco_jet.obj.eta(), reco_jet.obj.phi(), gen_jet.obj.eta(), gen_jet.obj.phi() );
		      if (min_deltaR > this_deltaR ) min_deltaR = this_deltaR;
		    }
		}
	      deltaR_PF_matching_intree->push_back(min_deltaR);
	      continue;
	    }	      
	  for (const auto & gen_jet : *pruned_genParticles_intree)
	    {
	      this_deltaR = reco::deltaR( reco_jet.obj.eta(), reco_jet.obj.phi(), gen_jet.obj.eta(), gen_jet.obj.phi() );
	      if (this_deltaR < 0.4 && min_deltaR > this_deltaR )
		{
		  if (gen_jet.pdgID == 21 && (*pruned_genParticles_intree)[gen_jet.mother].pdgID < 2000) continue; //find a better match
		  if ( abs(gen_jet.pdgID) == 24 || abs(gen_jet.pdgID) == 25 || abs(gen_jet.pdgID) == 6 ) continue; //find a better match
		  if ( abs(gen_jet.pdgID) == 16 || abs(gen_jet.pdgID) == 12 || abs(gen_jet.pdgID) == 14 ) continue; //find a better match
		  min_deltaR = this_deltaR;
		  gen_preselected_jet = gen_jet;
		}
	    }
	  deltaR_charlie_matching_intree->push_back(min_deltaR);
	  genMatched_reco_jet = reco_jet;
	  genMatched_reco_jet.genPdgID = gen_preselected_jet.pdgID;
	  if (gen_preselected_jet.mother < 9999.) genMatched_reco_jet.genMotherPdgID = (*pruned_genParticles_intree)[gen_preselected_jet.mother].pdgID;
	  if (gen_preselected_jet.grandmother < 9999.) genMatched_reco_jet.genGrandMotherPdgID = (*pruned_genParticles_intree)[gen_preselected_jet.grandmother].pdgID;
	  preselected_jets_genMatch_intree->push_back(genMatched_reco_jet);	  
	} 

      signal_tree->Fill();
      
    }
  
  
  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (chainentries>0) cout << "an average of " << (endtime - starttime) / chainentries << " per event." << endl;
  
  signal_tree->Write();
  copiedfile->Close();  
}

void updateTree(void)
{
  TString output_file = "ttH_psJetGenParentStudy_softGluVeto.root";
  TChain *chain = new TChain("ss2l_tree");
  chain->Add("tth_tree_newVars.root");
  run_it(chain,output_file);
}
