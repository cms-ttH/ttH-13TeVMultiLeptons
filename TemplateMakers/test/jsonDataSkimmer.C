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
#include "treeTools.h"
#include "JsonFilter.h"
#include "FakeRateEvaluator.h"

/////////////////////////////////////////
///
/// usage: root -l jsonDataSkimmer.C
///
/////////////////////////////////////////

void run_it(TTree* tree, TString output_file)
{

  int treeentries = tree->GetEntries();   
  cout << "# events in tree: "<< treeentries << endl;  
  
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
  //vector<ttH::Jet> *bTight_jets_intree=0;  
  //vector<ttH::Jet> *bLoose_jets_intree=0;   

  //tree->SetBranchStatus("bTight_jets.*",1);
  //tree->SetBranchStatus("bLoose_jets.*",1);
  // tree->SetBranchStatus("eventnum",1);  
  tree->SetBranchAddress("eventnum", &eventnum_intree);
  tree->SetBranchAddress("runNumber", &runNumber_intree);
  tree->SetBranchAddress("lumiBlock", &lumiBlock_intree);
  tree->SetBranchAddress("passTrigger", &passTrigger_intree);
  tree->SetBranchAddress("tight_leptons",&tight_leptons_intree);
  tree->SetBranchAddress("tight_muons",&tight_muons_intree);
  tree->SetBranchAddress("fakeable_leptons",&fakeable_leptons_intree);
  tree->SetBranchAddress("fakeable_muons",&fakeable_muons_intree);
  tree->SetBranchAddress("fakeable_electrons",&fakeable_electrons_intree);
  tree->SetBranchAddress("preselected_jets", &preselected_jets_intree);
  //tree->SetBranchAddress("bTight_jets", &bTight_jets_intree);  
  //tree->SetBranchAddress("bLoose_jets", &bLoose_jets_intree);


  FakeRateEvaluator fakeRateHelper;
  
  TFile *copiedfile = new TFile(output_file+".root", "RECREATE"); //"UPDATE"); // #, 'test' ) // "RECREATE");

  TTree *signal_tree = (TTree*)tree->CloneTree(0);
  fakeRateHelper.initializeTree(signal_tree);
  
  //Int_t cachesize = 250000000;   //250 MBytes
  //tree->SetCacheSize(cachesize);
  //tree->SetCacheLearnEntries(20); 
  
  JsonFilter my_json_filter;
  vector<double> events;
  double starttime = get_wall_time();
  for (int i=0; i<treeentries; i++)
    {
      
      printProgress(i,treeentries);
      tree->GetEntry(i);
      
      //////////////////////////
      ////
      //// calculate new vars
      ////
      //////////////////////////

      bool no_duplicate = (std::find(events.begin(),events.end(),eventnum_intree) == events.end());
      bool golden_json = my_json_filter.isValid(runNumber_intree,lumiBlock_intree);

      if (output_file == "data" and no_duplicate and golden_json)
	{
	  events.push_back(eventnum_intree);
	  signal_tree->Fill();
	}
      else if (output_file == "fakes" and no_duplicate and golden_json )
	{
	  events.push_back(eventnum_intree);
	  fakeRateHelper.addFakeRates(*fakeable_leptons_intree);
	  signal_tree->Fill();
	}

      else if (output_file =="flips" and no_duplicate and golden_json and abs((*tight_leptons_intree)[0].pdgID)+abs((*tight_leptons_intree)[1].pdgID)!=26 )
	{
	  events.push_back(eventnum_intree);
	  fakeRateHelper.addFlipRates(*tight_leptons_intree);
	  signal_tree->Fill();
	}

    }
  
  
  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (treeentries>0) cout << "an average of " << (endtime - starttime) / treeentries << " per event." << endl;
  
  signal_tree->Write();
  gDirectory->Purge();
  copiedfile->Write();
  copiedfile->Close();  
}

void jsonDataSkimmer(void)
{
  TString output_file_prefix_data = "data";
  TFile* input_file = new TFile("/scratch365/cmuelle2/extraction_trees/june14_test/data2lss_sr.root","READONLY");
  TTree* tree_data = (TTree*)input_file->Get("ss2l_tree");
  run_it(tree_data,output_file_prefix_data);
  
  TString output_file_prefix_fakes = "fakes";
  TFile* input_file_fakes = new TFile("/scratch365/cmuelle2/extraction_trees/june14_test/data2lss_lepMVA_ar.root","READONLY");
  TTree* tree_fakes = (TTree*)input_file_fakes->Get("ss2l_tree");
  run_it(tree_fakes,output_file_prefix_fakes);

  TString output_file_prefix_flips = "flips";
  TFile* input_file_flips = new TFile("/scratch365/cmuelle2/extraction_trees/june14_test/data2los_ar.root","READONLY");
  TTree* tree_flips = (TTree*)input_file_flips->Get("ss2l_tree");
  run_it(tree_flips,output_file_prefix_flips);

}
