//Charlie Mueller 2/24/2016
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include "TSystem.h"
#include "TH1.h"
#include "TChain.h"
#include "TString.h"
#include "TH1D.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/src/LinkDef.h"
#include "variables.h"

/////////////////////////////////////////
///
/// usage: root -l dump_syncFiles.C+
///
/////////////////////////////////////////

void dump_muons(std::ofstream& output, vector<ttH::Muon> *preselected_muons, int event)
{
  if (preselected_muons->size() == 0) return;

  ttH::Muon mu = (*preselected_muons)[0];
  output << setiosflags(ios::fixed) << setprecision(5);
  output << event << " "
	 <<mu.obj.Pt()<< " "
	 <<mu.obj.Eta()<< " "
	 <<mu.obj.Phi()<< " "
	 <<mu.obj.E()<< " "
	 <<mu.pdgID<< " "
	 <<mu.charge<< " "
	 <<mu.lepMVA<< " "
	 <<mu.miniIso<< " "
	 <<mu.miniAbsIsoCharged<< " "
	 <<mu.miniAbsIsoNeutral<< " "
	 <<mu.jetPtRel<< " "
	 <<mu.csv<< " "
	 <<mu.jetPtRatio<< " "
	 <<mu.sip3D<< " "
	 <<mu.dxy<< " "
	 <<mu.dz<< " "
	 <<mu.segCompatibility<<endl;
}

void run_it(TChain* chain)
{

  //  std::ofstream ele_output; ele_output.open("electron_dump.txt");
  std::ofstream mu_output; mu_output.open("muon_dump.txt");
  
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
      //// main loop
      ////
      //////////////////////////
      
      dump_muons(mu_output, preselected_muons_intree, eventnum_intree);
      
    }
  
  
  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (chainentries>0) cout << "an average of " << (endtime - starttime) / chainentries << " per event." << endl;

  mu_output.close();
  //  ele_output.close();
  
}

void dump_syncFiles(void)
{

  TChain *chain = new TChain("OSTwoLepAna/summaryTree");
  chain->Add("tree_BDT2_orig.root");
  run_it(chain);

}
