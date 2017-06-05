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
#include "JsonFilter.h"
#include "FakeRateEvaluator.h"

/////////////////////////////////////////
///
/// usage: root -l jsonDataSkimmer.C
///
/////////////////////////////////////////

void run_it(TChain* chain, TString output_file)
{

  int chainentries = chain->GetEntries();   
  cout << "# events in tree: "<< chainentries << endl;  
  
  double mcwgt_intree = -999.;
  double wallTimePerEvent_intree = -99.;  
  int eventnum_intree = -999;
  int higgs_decay_intree = -9999;
  int lumiBlock_intree = -999;
  int runNumber_intree = -999;

  std::vector<std::string> *passTrigger_intree=0;
  vector<ttH::Lepton> *preselected_leptons_intree=0;
  vector<ttH::Electron> *raw_electrons_intree=0;               
  vector<ttH::Electron> *preselected_electrons_intree=0;
  vector<ttH::Muon> *raw_muons_intree=0;
  vector<ttH::Muon> *preselected_muons_intree=0;
  vector<ttH::Jet> *preselected_jets_intree=0;
  vector<ttH::MET> *met_intree=0;
  vector<ttH::GenParticle> *pruned_genParticles_intree=0;
  vector<ttH::Lepton> *tight_leptons_intree=0;
  vector<ttH::Lepton> *fakeable_leptons_intree=0;
  vector<ttH::Electron> *tight_electrons_intree=0;
  vector<ttH::Electron> *fakeable_electrons_intree=0;
  vector<ttH::Muon> *tight_muons_intree=0;
  vector<ttH::Muon> *fakeable_muons_intree=0;
  ttH::Jet *b_from_leptop_intree=0;


  chain->SetBranchStatus("mcwgt",0);
  // chain->SetBranchStatus("eventnum",1);
  
  chain->SetBranchAddress("eventnum", &eventnum_intree);
  chain->SetBranchAddress("runNumber", &runNumber_intree);
  chain->SetBranchAddress("lumiBlock", &lumiBlock_intree);
  chain->SetBranchAddress("passTrigger", &passTrigger_intree);
  chain->SetBranchAddress("tight_leptons",&tight_leptons_intree);
  chain->SetBranchAddress("tight_muons",&tight_muons_intree);
  chain->SetBranchAddress("fakeable_leptons",&fakeable_leptons_intree);
  chain->SetBranchAddress("fakeable_muons",&fakeable_muons_intree);
  chain->SetBranchAddress("fakeable_electrons",&fakeable_electrons_intree);
  chain->SetBranchAddress("preselected_jets", &preselected_jets_intree);

  FakeRateEvaluator lepFakeRateObject;
  lepFakeRateObject.loadWeights();
  
  TFile *copiedfile = new TFile(output_file, "RECREATE"); //"UPDATE"); // #, 'test' ) // "RECREATE");

  TTree *signal_tree = (TTree*)chain->CloneTree(0);
  signal_tree->Branch("mcwgt", &mcwgt_intree);  

  Int_t cachesize = 250000000;   //250 MBytes
  chain->SetCacheSize(cachesize);
  chain->SetCacheLearnEntries(20); 
  
  JsonFilter my_json_filter;
  vector<double> events;
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

      bool no_duplicate = (std::find(events.begin(),events.end(),eventnum_intree) == events.end());
      bool golden_json = my_json_filter.isValid(runNumber_intree,lumiBlock_intree);


      //if (no_duplicate and golden_json and abs((*tight_leptons_intree)[0].pdgID)+abs((*tight_leptons_intree)[1].pdgID)!=26 )
      if (no_duplicate and golden_json )
	{
	  events.push_back(eventnum_intree);
	  //mcwgt_intree = lepFakeRateObject.flipProb(*tight_leptons_intree);
	  mcwgt_intree = lepFakeRateObject.get_fr(*fakeable_leptons_intree,*fakeable_electrons_intree, *fakeable_muons_intree);
	  //mcwgt_intree = 1.;
	  signal_tree->Fill();
	}
    }
  
  
  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (chainentries>0) cout << "an average of " << (endtime - starttime) / chainentries << " per event." << endl;
  
  signal_tree->Write();
  copiedfile->Close();  
}

void jsonDataSkimmer(void)
{
  TString output_file = "fakes_noMuTightCharge.root";
  TChain *chain = new TChain("ss2l_tree");
  chain->Add("/scratch365/cmuelle2/selection_trees/may10_fakeTests/data2lss_lepMVA_ar.root");
  run_it(chain,output_file);
}
