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

  vector<ttH::Jet> *csvSorted_jets_intree=0;
  ttH::Jet nearestJet_intree;
  ttH::Lepton lepHiggs_intree;
  ttH::Lepton lepTop_intree;
  double min_dR_bl_intree = 0;
  double max_dR_bl_intree = 0;
  TLorentzVector hadTop_tlv_intree;  
  TLorentzVector lepTop_tlv_intree;  
  //test variables


  TTree *signal_tree = (TTree*)chain->CloneTree(0);
  signal_tree->SetName("signal_tree");
  signal_tree->Branch("csv_sorted_jets", &csvSorted_jets_intree);
  signal_tree->Branch("min_dR_bl", &min_dR_bl_intree);
  signal_tree->Branch("max_dR_bl", &max_dR_bl_intree);
  signal_tree->Branch("hadTop_tlv", &hadTop_tlv_intree);
  signal_tree->Branch("lepTop_tlv", &lepTop_tlv_intree);
  signal_tree->Branch("lepFromTop", &lepTop_intree);
  signal_tree->Branch("lepFromHiggs", &lepHiggs_intree);
  signal_tree->Branch("nearestBJet", &nearestJet_intree);

  TTree *background_tree = (TTree*)chain->CloneTree(0);
  background_tree->SetName("background_tree");
  background_tree->Branch("csv_sorted_jets", &csvSorted_jets_intree);
  background_tree->Branch("min_dR_bl", &min_dR_bl_intree);
  background_tree->Branch("max_dR_bl", &max_dR_bl_intree);
  background_tree->Branch("hadTop_tlv", &hadTop_tlv_intree);
  background_tree->Branch("lepTop_tlv", &lepTop_tlv_intree);
  background_tree->Branch("lepFromTop", &lepTop_intree);
  background_tree->Branch("lepFromHiggs", &lepHiggs_intree);
  background_tree->Branch("nearestBJet", &nearestJet_intree);


  Int_t cachesize = 250000000;   //250 MBytes
  chain->SetCacheSize(cachesize);
  chain->SetCacheLearnEntries(20); 
  
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
      //// calculate new vars
      ////
      //////////////////////////

      *csvSorted_jets_intree = *preselected_jets_intree;
      std::sort(csvSorted_jets_intree->begin(), csvSorted_jets_intree->end(), [] (ttH::Jet a, ttH::Jet b) { return a.csv > b.csv;});
      ttH::Jet bJet1 = (*csvSorted_jets_intree)[0];
      ttH::Jet bJet2 = (*csvSorted_jets_intree)[1];

      TLorentzVector bjet1_tlv;
      TLorentzVector bjet2_tlv;
      TLorentzVector lepTop_tlv;
      TLorentzVector lepHiggs_tlv;
      bjet1_tlv.SetPxPyPzE(bJet1.obj.px(),bJet1.obj.py(),bJet1.obj.pz(),bJet1.obj.E());
      bjet2_tlv.SetPxPyPzE(bJet2.obj.px(),bJet2.obj.py(),bJet2.obj.pz(),bJet2.obj.E());

      ///signal
      if ( abs((*tight_leptons_intree)[0].genGrandMotherPdgID) ==6 || abs((*tight_leptons_intree)[1].genGrandMotherPdgID) ==25)
	{
	  lepTop_intree = (*tight_leptons_intree)[0];
	  lepHiggs_intree = (*tight_leptons_intree)[1];
	}
      else if ( abs((*tight_leptons_intree)[0].genGrandMotherPdgID) ==25 || abs((*tight_leptons_intree)[1].genGrandMotherPdgID) ==6)
	{
	  lepTop_intree = (*tight_leptons_intree)[1];
	  lepHiggs_intree = (*tight_leptons_intree)[0];
	}

      lepTop_tlv.SetPxPyPzE(lepTop_intree.obj.px(),lepTop_intree.obj.py(),lepTop_intree.obj.pz(),lepTop_intree.obj.E());
      lepHiggs_tlv.SetPxPyPzE(lepHiggs_intree.obj.px(),lepHiggs_intree.obj.py(),lepHiggs_intree.obj.pz(),lepHiggs_intree.obj.E());

      min_dR_bl_intree = lepTop_tlv.DeltaR ( bjet1_tlv );
      max_dR_bl_intree = lepTop_tlv.DeltaR ( bjet2_tlv );
      nearestJet_intree = bJet1;
      if ( max_dR_bl_intree < min_dR_bl_intree)
	{
	  min_dR_bl_intree = lepTop_tlv.DeltaR ( bjet2_tlv );
	  max_dR_bl_intree = lepTop_tlv.DeltaR ( bjet1_tlv );
	  nearestJet_intree = bJet2;
	}

      signal_tree->Fill();
      //background
      if ( abs((*tight_leptons_intree)[0].genGrandMotherPdgID) ==6 || abs((*tight_leptons_intree)[1].genGrandMotherPdgID) ==25)
	{
	  lepTop_intree = (*tight_leptons_intree)[1];
	  lepHiggs_intree = (*tight_leptons_intree)[0];
	}
      else if ( abs((*tight_leptons_intree)[0].genGrandMotherPdgID) ==25 || abs((*tight_leptons_intree)[1].genGrandMotherPdgID) ==6)
	{
	  lepTop_intree = (*tight_leptons_intree)[0];
	  lepHiggs_intree = (*tight_leptons_intree)[1];
	}

      lepTop_tlv.SetPxPyPzE(lepTop_intree.obj.px(),lepTop_intree.obj.py(),lepTop_intree.obj.pz(),lepTop_intree.obj.E());
      lepHiggs_tlv.SetPxPyPzE(lepHiggs_intree.obj.px(),lepHiggs_intree.obj.py(),lepHiggs_intree.obj.pz(),lepHiggs_intree.obj.E());

      min_dR_bl_intree = lepTop_tlv.DeltaR ( bjet1_tlv );
      max_dR_bl_intree = lepTop_tlv.DeltaR ( bjet2_tlv );
      nearestJet_intree = bJet1;
      if ( max_dR_bl_intree < min_dR_bl_intree)
	{
	  min_dR_bl_intree = lepTop_tlv.DeltaR ( bjet2_tlv );
	  max_dR_bl_intree = lepTop_tlv.DeltaR ( bjet1_tlv );
	  nearestJet_intree = bJet2;
	}
      
      background_tree->Fill();
    }
  
  
  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (chainentries>0) cout << "an average of " << (endtime - starttime) / chainentries << " per event." << endl;
  
  signal_tree->Write();
  background_tree->Write();
  copiedfile->Close();  
}

void updateTree(void)
{
  TString output_file = "ttbar_new_tree.root";
  TChain *chain = new TChain("ss2l_tree");
  chain->Add("comparison_bdt_weightedBkgSq/ttbar_sum_v2.root");
  run_it(chain,output_file);
}
