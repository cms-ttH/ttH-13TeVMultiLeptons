//Charlie Mueller 7/20/2016
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
#include "loadSamples_triggerStudies_80X.h"

/////////////////////////////////////////
///
/// usage: root -l makeSelectionTree.C+\("\"ttH-powheg\"",1,3\)
///        root -l makeSelectionTree.C+\("\"ttH-powheg\""\)
///
/////////////////////////////////////////


void run_it(TChain* chain, TString output_file)
{

  int chainentries = chain->GetEntries();   
  cout << "# events in tree: "<< chainentries << endl;  
  
  double mcwgt_intree = -999.;
  int eventnum_intree = -999;  
  vector<ttH::Electron> *preselected_electrons_intree=0;
  vector<ttH::Muon> *preselected_muons_intree=0;
  vector<ttH::Jet> *preselected_jets_intree=0;
  vector<ttH::MET> *met_intree=0;
  vector<ttH::Lepton> *tight_leptons_intree=0;
  vector<ttH::Electron> *tight_electrons_intree=0;
  vector<ttH::Muon> *tight_muons_intree=0;
  
  // chain->SetBranchStatus("*",0);
  // chain->SetBranchStatus("mcwgt",1);
  // chain->SetBranchStatus("eventnum",1);
  // chain->SetBranchStatus("preselected_electrons.*",1);
  // chain->SetBranchStatus("preselected_muons.*",1);
  // chain->SetBranchStatus("preselected_jets.*",1);
  // chain->SetBranchStatus("tightMvaBased_leptons.*",1);
  // chain->SetBranchStatus("tightMvaBased_electrons.*",1);
  // chain->SetBranchStatus("tightMvaBased_muons.*",1);
  // chain->SetBranchStatus("met.*",1);

  chain->SetBranchAddress("mcwgt", &mcwgt_intree);
  chain->SetBranchAddress("eventnum", &eventnum_intree);
  chain->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
  chain->SetBranchAddress("preselected_muons", &preselected_muons_intree);
  chain->SetBranchAddress("preselected_jets", &preselected_jets_intree);
  chain->SetBranchAddress("tightMvaBased_leptons", &tight_leptons_intree);
  chain->SetBranchAddress("tightMvaBased_electrons", &tight_electrons_intree);
  chain->SetBranchAddress("tightMvaBased_muons", &tight_muons_intree);    
  chain->SetBranchAddress("met", &met_intree);

  TFile *copiedfile = new TFile(output_file, "RECREATE"); //"UPDATE"); // #, 'test' ) // "RECREATE");

  TTree *ss2l_tree = (TTree*)chain->CloneTree(0);
  TTree *l3_tree = (TTree*)chain->CloneTree(0);
  ss2l_tree->SetName("ss2l_tree");
  l3_tree->SetName("l3_tree");

  Int_t cachesize = 250000000;   //250 MBytes
  chain->SetCacheSize(cachesize);
  // chain->SetCacheLearnEntries(20); 

  double starttime = get_wall_time();

  //  chainentries = 3000;
  for (int i=0; i<chainentries; i++)
    {
      if (i%int(chainentries/100) == 0)
	{
	  float fraction = 100.*i/chainentries;
	  cout << fraction << " % complete" << endl;
	  cout << i << endl;
	}
      clock_t startTime = clock();
      chain->GetEntry(i);

      //////////////////////////
      ////
      //// selection, vetos etc
      ////
      //////////////////////////

      bool passesCommon = passCommon(*tight_electrons_intree, *preselected_electrons_intree, *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree);
      if (!passesCommon) continue;
      bool passes2lss = pass2lss(*tight_electrons_intree, *preselected_electrons_intree, *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree, *met_intree);
      if ( passes2lss ) ss2l_tree->Fill();
      else
	{ 
	  bool passes3l = pass3l(*tight_electrons_intree, *preselected_electrons_intree, *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree, *met_intree);
	  if ( passes3l ) l3_tree->Fill();
	}


    }
  
  
  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (chainentries>0) cout << "an average of " << (endtime - starttime) / chainentries << " per event." << endl;
  
  ss2l_tree->Write();
  l3_tree->Write();
  copiedfile->Close();
  
}

void makeSelectionTree(TString sample, int start_file=0, int end_file=0)
{

  TString output_dir = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/";

  TString output_file = "ttH_tree_event_selection_triggerStudies_July21_25_15_eeCuts.root";
  TChain *tth_chain = loadFiles(sample,start_file,end_file);  
  run_it(tth_chain,output_file);

}
