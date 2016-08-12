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
/// usage: root -l makeBtightBLooseTree.C+
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

  vector<ttH::Jet> *preselected_jets_intree=0;

  chain->SetBranchAddress("preselected_jets", &preselected_jets_intree);  

  TFile *copiedfile = new TFile(output_file, "RECREATE"); //"UPDATE"); // #, 'test' ) // "RECREATE");

  TTree *b_tight_tree = (TTree*)chain->CloneTree(0);
  b_tight_tree->SetName("bTight_tree");
  TTree *b_loose_tree = (TTree*)chain->CloneTree(0);
  b_loose_tree->SetName("bLoose_tree");


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

      vector<ttH::Jet> sorted_jets = *preselected_jets_intree;

      std::sort(sorted_jets.begin(), sorted_jets.end(), [] (ttH::Jet a, ttH::Jet b) { return a.csv > b.csv;});      

      if ( (*preselected_jets_intree)[1].csv >= 0.8 ) b_tight_tree->Fill();
      else b_loose_tree->Fill();
      
      
    }
  
  
  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (chainentries>0) cout << "an average of " << (endtime - starttime) / chainentries << " per event." << endl;
  
  b_tight_tree->Write();
  b_loose_tree->Write();
  copiedfile->Close();  
}

void makeBtightBLooseTree(void)
{
  TString output_file = "ttH_aMCatNLO_2lss_bTightLoose_selection_tree_test.root";
  TChain *chain = new TChain("ss2l_tree");
  //  chain->Add("selection_trees/ttbar-semiLep-madgraph_selection_tree_2l_ss.root");
  chain->Add("/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v1p5_bTightLoose/ttH_aMCatNLO_bdtEval__good.root");
  run_it(chain,output_file);
}
