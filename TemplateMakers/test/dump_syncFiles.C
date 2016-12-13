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
#include "ttH-13TeVMultiLeptons/TemplateMakers/src/classes.h"
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
	 <<mu.jet_nCharged_tracks<< " "
	 <<mu.miniIso<< " "
	 <<mu.miniAbsIsoCharged / mu.obj.Pt()<< " "
	 <<mu.miniAbsIsoNeutralcorr / mu.obj.Pt()<< " "
	 <<mu.jetPtRel<< " "
	 <<mu.csv<< " "
	 <<mu.jetPtRatio<< " "
	 <<mu.sip3D<< " "
	 <<mu.dxy<< " "
	 <<mu.dz<< " "
	 <<mu.segCompatibility<< " "
         <<mu.lepMVA<< endl;
}

void dump_electrons(std::ofstream& output, vector<ttH::Electron> *preselected_electrons, int event)
{
  if (preselected_electrons->size() == 0) return;

  ttH::Electron ele = (*preselected_electrons)[0];
  output << setiosflags(ios::fixed) << setprecision(5);
  output << event << " "
	 <<ele.obj.Pt()<< " "
	 <<ele.obj.Eta()<< " "
	 <<ele.obj.Phi()<< " "
	 <<ele.obj.E()<< " "
	 <<ele.pdgID<< " "
	 <<ele.charge<< " "
	 <<ele.jet_nCharged_tracks<< " "
	 <<ele.miniIso<< " "
	 <<ele.miniAbsIsoCharged / ele.obj.Pt() << " "
	 <<ele.miniAbsIsoNeutralcorr / ele.obj.Pt()  << " "
	 <<ele.jetPtRel<< " "
	 <<ele.csv<< " "
	 <<ele.jetPtRatio<< " "
	 <<ele.sip3D<< " "
	 <<ele.dxy<< " "
	 <<ele.dz<< " "
	 <<ele.mvaID<< " "
         <<ele.lepMVA<<endl;
}

void dump_taus(std::ofstream& output, vector<ttH::Tau> *preselected_taus, int event)
{
  if (preselected_taus->size() == 0) return;

  ttH::Tau tau = (*preselected_taus)[0];
  output << setiosflags(ios::fixed) << setprecision(5);
  output << event << " "
	 <<tau.obj.Pt()<< " "
	 <<tau.obj.Eta()<< " "
	 <<tau.obj.Phi()<< " "
	 <<tau.obj.E()<< " "
	 <<tau.charge<< " "
	 <<tau.dxy<< " "
	 <<tau.dz<< " "
	 <<tau.decayModeFinding<< " "
	 <<tau.mvaID<<endl;
}

void dump_jets(std::ofstream& output, vector<ttH::Jet> *preselected_jets, vector<ttH::MET> *input_met, int event)
{
  if (preselected_jets->size() == 0 || input_met->size()==0) return;

  ttH::Jet jet = (*preselected_jets)[0];
  ttH::MET met = (*input_met)[0];
  output << setiosflags(ios::fixed) << setprecision(5);
  output << event << " "
	 <<jet.obj.Pt()<< " "
	 <<jet.obj.Eta()<< " "
	 <<jet.obj.Phi()<< " "
	 <<jet.obj.E()<< " "
	 <<jet.csv<< " "
	 <<met.pt_forSync<< " "
	 <<met.phi_forSync<<endl;
}

void run_it(TChain* chain)
{
  
  std::ofstream ele_output; ele_output.open("electron_dump.txt");
  std::ofstream mu_output; mu_output.open("muon_dump.txt");
  std::ofstream tau_output; tau_output.open("tau_dump.txt");
  std::ofstream jet_output; jet_output.open("jet_dump.txt");
  
  int chainentries = chain->GetEntries();   
  cout << "# events in tree: "<< chainentries << endl;  
  
  double mcwgt_intree = -999.;
  int eventnum_intree = -999;
  
  vector<ttH::Lepton> *preselected_leptons_intree=0;
  vector<ttH::Electron> *raw_electrons_intree=0;               
  vector<ttH::Electron> *preselected_electrons_intree=0;
  vector<ttH::Muon> *raw_muons_intree=0;
  vector<ttH::Muon> *preselected_muons_intree=0;
  vector<ttH::Jet> *preselected_jets_intree=0;
  vector<ttH::Tau> *selected_taus_intree=0;
  vector<ttH::MET> *met_intree=0;

  //only enable some branches
  chain->SetBranchStatus("*",0);
  chain->SetBranchStatus("mcwgt",1);
  chain->SetBranchStatus("eventnum",1);
  chain->SetBranchStatus("preselected_electrons.*",1);
  chain->SetBranchStatus("preselected_muons.*",1);
  chain->SetBranchStatus("preselected_jets.*",1);
  chain->SetBranchStatus("preselected_taus.*",1);
  chain->SetBranchStatus("met.*",1);

  chain->SetBranchAddress("mcwgt", &mcwgt_intree);
  chain->SetBranchAddress("eventnum", &eventnum_intree);
  chain->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
  chain->SetBranchAddress("preselected_muons", &preselected_muons_intree);
  chain->SetBranchAddress("preselected_jets", &preselected_jets_intree);
  chain->SetBranchAddress("preselected_taus", &selected_taus_intree);
  chain->SetBranchAddress("met", &met_intree);

  double starttime = get_wall_time();
  for (int i=0; i<chainentries; i++)  //// main loop
    {
      
      if (i%7000 == 0)
	{
	  float fraction = 100.*i/chainentries;
	  cout << fraction << " % complete" << endl;
	  cout << i << endl;
	}
      chain->GetEntry(i);

      dump_muons(mu_output, preselected_muons_intree, eventnum_intree);
      dump_electrons(ele_output, preselected_electrons_intree, eventnum_intree);
      dump_taus(tau_output, selected_taus_intree, eventnum_intree);
      dump_jets(jet_output, preselected_jets_intree, met_intree, eventnum_intree);
      
    }
  
  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (chainentries>0) cout << "an average of " << (endtime - starttime) / chainentries << " per event." << endl;

  mu_output.close();
  ele_output.close();
  tau_output.close();
  jet_output.close();
  
}

void dump_syncFiles(void)
{

  TChain *chain = new TChain("OSTwoLepAna/summaryTree");
  chain->Add("output_tree.root");
  run_it(chain);

}
