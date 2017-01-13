//Charlie Mueller 1/13/2017
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
#include "treeTools.h"

/////////////////////////////////////////
///
/// usage: root -l dump_eventSyncFiles.C+
///
/////////////////////////////////////////

void dumpToFile(std::ofstream& output, int event, vector<ttH::Lepton> *leptons, vector<ttH::Jet> *jets, vector<ttH::MET> *met)
{  
  
  //max lep eta
  double max_lep_eta = -1.;
  for (const auto & lep: *leptons)
    {
      if (abs(lep.obj.eta()) > max_lep_eta)
	{
	  max_lep_eta = abs(lep.obj.eta());
	}
    }
  
  //min dr lep1,2
  ttH::Lepton lep1 = (*leptons)[0];
  ttH::Lepton lep2 = (*leptons)[1];
  ttH::Jet lep1_closest_jet = getClosestJet(*jets, lep1);
  ttH::Jet lep2_closest_jet = getClosestJet(*jets, lep2);
  double min_dr_lep1_jet = getDeltaR(lep1_closest_jet, lep1);
  double min_dr_lep2_jet = getDeltaR(lep2_closest_jet, lep2);

  //met
  double met_var = min((*met)[0].obj.pt(), 400.);
  double mt_met_lep1 = sqrt(2*lep1.obj.pt()*met_var*(1-cos(lep1.obj.phi()-(*met)[0].obj.phi() )));
  
  //avg dr jets
  int jet1_counter = 0;
  double dr_sum = 0.;
  int dr_denom = 0;
  for (const auto & jet1 : *jets)
    {
      int jet2_counter = -1;
      for (const auto & jet2 : *jets)
	{
	  jet2_counter +=1;
	  if ( jet2_counter <= jet1_counter ) continue;
	  double delta_r = getDeltaR(jet1, jet2);
	  dr_sum += delta_r;
	  dr_denom +=1;
	}
      jet1_counter +=1;
    }
  double avg_dr_jets = dr_sum/double(dr_denom);
  
  

  output << setiosflags(ios::fixed) << setprecision(5);
  output << event << " "
	 << 999.0 << " "
	 << max_lep_eta << " "
	 << jets->size() << " "
	 << min_dr_lep1_jet << " "
	 << min_dr_lep2_jet << " "
	 << met_var << " "
	 << avg_dr_jets << " "
	 << mt_met_lep1 << " "
	 << lep1.obj.pt() << " "
	 << lep2.obj.pt() << " "
	 << 999.0 << " "
	 << 999.0 << endl;
}


void run_it(TChain* chain)
{  
  std::ofstream sr_2lss_ee_output; sr_2lss_ee_output.open("event_dump_2lss_ee_sr.txt");
  std::ofstream sr_2lss_em_output; sr_2lss_em_output.open("event_dump_2lss_em_sr.txt");
  std::ofstream sr_2lss_mm_output; sr_2lss_mm_output.open("event_dump_2lss_mm_sr.txt");
  
  int chainentries = chain->GetEntries();   
  cout << "# events in tree: "<< chainentries << endl;  
  
  double mcwgt_intree = -999.;
  int eventnum_intree = -999;
  
  vector<ttH::Lepton> *preselected_leptons_intree=0;
 vector<ttH::Lepton> *tight_leptons_intree=0;
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
  chain->SetBranchStatus("tight_leptons.*",1);
  chain->SetBranchStatus("met.*",1);

  chain->SetBranchAddress("mcwgt", &mcwgt_intree);
  chain->SetBranchAddress("eventnum", &eventnum_intree);
  chain->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
  chain->SetBranchAddress("preselected_muons", &preselected_muons_intree);
  chain->SetBranchAddress("preselected_jets", &preselected_jets_intree);
  chain->SetBranchAddress("preselected_taus", &selected_taus_intree);
  chain->SetBranchAddress("met", &met_intree);
  chain->SetBranchAddress("tight_leptons", &tight_leptons_intree);

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
      
      
      if (abs((*tight_leptons_intree)[0].pdgID) == 11 && abs((*tight_leptons_intree)[1].pdgID) == 11)
	{
	  dumpToFile(sr_2lss_ee_output, eventnum_intree, tight_leptons_intree, preselected_jets_intree, met_intree);
	}
      else if (abs((*tight_leptons_intree)[0].pdgID) == 13 && abs((*tight_leptons_intree)[1].pdgID) == 13)
	{
	  dumpToFile(sr_2lss_mm_output, eventnum_intree, tight_leptons_intree, preselected_jets_intree, met_intree);
	}
      else
	{
	  dumpToFile(sr_2lss_em_output, eventnum_intree, tight_leptons_intree, preselected_jets_intree, met_intree);
	}

    }
  
  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (chainentries>0) cout << "an average of " << (endtime - starttime) / chainentries << " per event." << endl;

  sr_2lss_ee_output.close();
  sr_2lss_em_output.close();
  sr_2lss_mm_output.close();
}

void dump_eventSyncFiles(void)
{

  TChain *chain = new TChain("ss2l_tree");
  chain->Add("ttw_sync_file.root");
  run_it(chain);
  
}
