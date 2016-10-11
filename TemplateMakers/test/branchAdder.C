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
/// usage: root -l branchAdder.C+
///
/////////////////////////////////////////



void run_it(TTree* tree)
{

  int treeentries = tree->GetEntries();   
  cout << "# events in tree: "<< treeentries << endl;  
  
  double wgt_intree = -999.;
  double wallTimePerEvent_intree = -99.;  
  int eventnum_intree = -999;
  int higgs_decay_intree = -9999;
  int lumiBlock_intree = -999;
  int runNumber_intree = -999;
  bool isBtight = false;
  vector<ttH::Jet> *btight_jets_intree=0;
  vector<ttH::Jet> *bloose_jets_intree=0;


  vector<ttH::Jet> *preselected_jets_intree=0;
  tree->SetBranchAddress("preselected_jets", &preselected_jets_intree);  


  TFile* output_file = new TFile("new_file.root","RECREATE");
  TTree *new_tree = tree->CloneTree(0);
  new_tree->Branch("bTight_jets",&btight_jets_intree);
  new_tree->Branch("bLoose_jets",&bloose_jets_intree);

  Int_t cachesize = 250000000;   //250 MBytes
  tree->SetCacheSize(cachesize);
  tree->SetCacheLearnEntries(20); 
  
  double starttime = get_wall_time();
  //  treeentries = 10000;
  for (int i=0; i<treeentries; i++)
    {
      btight_jets_intree->clear();
      bloose_jets_intree->clear();

      printProgress(i,treeentries);
      tree->GetEntry(i);
      
      //////////////////////////
      ////
      //// calculate new vars
      ////
      //////////////////////////

      for (const auto & jet : *preselected_jets_intree)
	{
	  if (jet.csv >= 0.8 ) btight_jets_intree->push_back(jet);
	  else if (jet.csv >= 0.46 ) bloose_jets_intree->push_back(jet);
	}

      new_tree->Fill();
      
    }
  
  
  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (treeentries>0) cout << "an average of " << (endtime - starttime) / treeentries << " per event." << endl;
  
  new_tree->Write("",TObject::kOverwrite);
  output_file->Close();
}

void branchAdder(void)
{
  TString file_name = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/tth_powheg_old_selection_tree_2lss.root";
  TFile* file = new TFile(file_name,"READONLY");
  TTree *tree = (TTree*)file->Get("ss2l_tree");
  run_it(tree);
  file->Close();
}
