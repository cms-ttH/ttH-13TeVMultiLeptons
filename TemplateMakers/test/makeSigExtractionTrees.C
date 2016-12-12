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
#include "ttH-13TeVMultiLeptons/TemplateMakers/test/signalExtractionTreeMaker.h"

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

  vector<ttH::Lepton> *preselected_leptons_intree=0;
  vector<ttH::Lepton> *fakeable_leptons_intree=0;
  vector<ttH::Jet> *preselected_jets_intree=0;
  vector<ttH::MET> *met_intree=0;
  vector<ttH::Lepton> *tight_leptons_intree=0;

  chain->SetBranchStatus("*",0);
  chain->SetBranchStatus("eventnum",1);
  chain->SetBranchStatus("mcwgt",1);
  chain->SetBranchStatus("preselected_jets.*",1);
  chain->SetBranchStatus("fakeable_leptons.*",1);
  chain->SetBranchStatus("preselected_leptons.*",1);
  chain->SetBranchStatus("tight_leptons.*",1);
  chain->SetBranchStatus("met.*",1);
  
  chain->SetBranchAddress("preselected_jets", &preselected_jets_intree);
  chain->SetBranchAddress("fakeable_leptons", &fakeable_leptons_intree);
  chain->SetBranchAddress("preselected_leptons", &preselected_leptons_intree);
  chain->SetBranchAddress("tight_leptons", &tight_leptons_intree);
  chain->SetBranchAddress("met", &met_intree);
  
  TTree *ttH_vs_ttbar_tree = new TTree("tth_vs_ttbar_tree","tth_vs_ttbar_tree");
  TTree *ttH_vs_ttV_tree = new TTree("tth_vs_ttv_tree","tth_vs_ttv_tree");
  signalExtractionTreeMaker mySigExtrTreeMaker(ttH_vs_ttbar_tree, ttH_vs_ttV_tree, ss2l_tree);
 
  Int_t cachesize = 250000000;   //250 MBytes
  chain->SetCacheSize(cachesize);
  chain->SetCacheLearnEntries(20); 
  
  double starttime = get_wall_time();
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
      //      auto lepton_collection_to_use = fakeable_leptons_intree;
      auto lepton_collection_to_use = preselected_leptons_intree;

      mySigExtrTreeMaker.initialize(preselected_jets_intree, lep_collection_to_use, (*met_intree)[0]);
      
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

  TString input_file1 = "selection_trees/nov8_trees/tth_aMC_old_2lss.root";
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
