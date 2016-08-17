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
/// usage: root -l branchCopier.C+
///
/////////////////////////////////////////



void run_it(TChain* original_chain, TChain* updated_chain)
{

  int original_chainentries = original_chain->GetEntries();   
  int updated_chainentries = updated_chain->GetEntries();   
  if (original_chainentries != updated_chainentries)
    {
      cout << "CANNOT COPY BRANCH WITH DIFFERENT NUM ENTRIES !!!!!" << endl;
      return;
    }
  cout << "# events in tree: "<< original_chainentries << endl;  
  
  vector<ttH::MET> *met_original_intree=0;
  vector<ttH::MET> *met_updated_intree=0;

  original_chain->SetBranchStatus("*",0);
  original_chain->SetBranchStatus("met.*",1);
  original_chain->SetBranchAddress("met", &met_original_intree);

  TTree *updated_tree = (TTree*)updated_chain->CloneTree(0);
  updated_tree->SetName("ss2l_tree");
  updated_tree->Branch("met", &met_updated_intree);

  Int_t cachesize = 250000000;   //250 MBytes
  original_chain->SetCacheSize(cachesize);
  original_chain->SetCacheLearnEntries(20); 
  
  double starttime = get_wall_time();
  for (int i=0; i<original_chainentries; i++)
    {      
      printProgress(i,original_chainentries);
      original_chain->GetEntry(i);
      updated_chain->GetEntry(i);
      
      //////////////////////////
      ////
      //// calculate new vars
      ////
      //////////////////////////

      met_updated_intree = met_original_intree;
      updated_tree->Fill();      
    }
    
  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (original_chainentries>0) cout << "an average of " << (endtime - starttime) / original_chainentries << " per event." << endl;
  
  updated_tree->Write("",TObject::kOverwrite);
}

void branchCopier(void)
{
  //  TString original_file_name = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/ttH-aMCatNLO_selection_tree_2lss.root";
  TString original_file_name = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/ttbar-semiLep-powheg_selection_tree_2lss.root";
  TChain *original_chain = new TChain("ss2l_tree");
  original_chain->Add(original_file_name);

  //  TString updated_file_name = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v1p5_bTightLoose/ttH_aMCatNLO_bdtEval.root";
  TString updated_file_name = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v1p5_bTightLoose/ttbar_powheg_bdtEval.root";
  TFile *updated_file = new TFile(updated_file_name, "UPDATE"); //"UPDATE"); // #, 'test' ) // "RECREATE");
  //  TFile *updated_file = new TFile("test.root", "RECREATE"); //"UPDATE"); // #, 'test' ) // "RECREATE");
  TChain *updated_chain = new TChain("ss2l_tree");
  updated_chain->Add(updated_file_name);
  run_it( original_chain, updated_chain );

  updated_file->Close();
}
