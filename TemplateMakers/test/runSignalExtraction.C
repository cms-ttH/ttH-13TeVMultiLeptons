//Charlie Mueller 2/24/2016
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
//#include "ttH-13TeVMultiLeptons/TemplateMakers/test/eventReconstructor.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/test/eventReconstructor_factorized.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/test/hTaggerBDT.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/test/signalExtractionTreeMaker.h"
#include "selection.h"
#include "loadSamples.h"


/////////////////////////////////////////
///
/// usage: root -l runSignalExtraction.C+
///
/////////////////////////////////////////


void run_it(TString sample_name, TTree* chain, TFile *output_file_, int events_per_job, int job_no, TString systematic="")
{

  int total_entries = chain->GetEntries();

  int min_tree_entry;
  int max_tree_entry;
  if (events_per_job > -1 && job_no > -1)
    {
      min_tree_entry = job_no*events_per_job;
      max_tree_entry = job_no*events_per_job + events_per_job-1;
      if ( max_tree_entry > total_entries ) max_tree_entry = total_entries;
      if ( min_tree_entry > max_tree_entry ) return;
    }
  else
    {
      min_tree_entry = 0;
      max_tree_entry = total_entries;   
    }
  cout << "# events in tree: "<< max_tree_entry - min_tree_entry << endl;  

  double mcwgt_intree = -999.;
  int eventnum_intree = -999;  
  vector<ttH::Electron> *preselected_electrons_intree=0;
  vector<ttH::Muon> *preselected_muons_intree=0;
  vector<ttH::Lepton> *preselected_leptons_intree=0;
  vector<ttH::Lepton> *fakeable_leptons_intree=0;
  vector<ttH::Jet> *preselected_jets_intree=0;
  vector<ttH::Jet> *preselected_jets_jecUp_intree=0;
  vector<ttH::Jet> *preselected_jets_jecDown_intree=0;
  vector<ttH::MET> *met_intree=0;
  vector<ttH::Lepton> *tight_leptons_intree=0;
  vector<ttH::Electron> *tight_electrons_intree=0;
  vector<ttH::Muon> *tight_muons_intree=0;
  vector<ttH::Tau> *selected_taus_intree=0;

  //new stuff
  ttH::Lepton *lep_from_higgs_truth_intree=0;
  ttH::Lepton *lep_from_leptop_truth_intree=0;
  ttH::Jet *b_from_leptop_truth_intree=0;
  ttH::Jet *b_from_hadtop_truth_intree=0;
  ttH::Jet *q1_from_hadtop_truth_intree=0;
  ttH::Jet *q2_from_hadtop_truth_intree=0;
  ttH::Jet *q1_from_higgs_truth_intree=0;
  ttH::Jet *q2_from_higgs_truth_intree=0;
  TString *higgs_final_state_intree=0;
  TString *ttbar_final_state_intree=0;
  
  chain->SetBranchAddress("mcwgt", &mcwgt_intree);
  chain->SetBranchAddress("eventnum", &eventnum_intree);
  chain->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
  chain->SetBranchAddress("preselected_muons", &preselected_muons_intree);
  chain->SetBranchAddress("preselected_leptons", &preselected_leptons_intree);
  chain->SetBranchAddress("preselected_jets", &preselected_jets_intree);
  chain->SetBranchAddress("preselected_jets_JECup", &preselected_jets_jecUp_intree);
  chain->SetBranchAddress("preselected_jets_JECdown", &preselected_jets_jecDown_intree);
  chain->SetBranchAddress("fakeable_leptons", &fakeable_leptons_intree);
  chain->SetBranchAddress("tight_leptons", &tight_leptons_intree);
  chain->SetBranchAddress("tight_electrons", &tight_electrons_intree);
  chain->SetBranchAddress("tight_muons", &tight_muons_intree);    
  chain->SetBranchAddress("met", &met_intree);

  // chain->SetBranchAddress("higgs_final_state", &higgs_final_state_intree);
  // chain->SetBranchAddress("ttbar_final_state", &ttbar_final_state_intree);
  // chain->SetBranchAddress("lep_from_higgs_reco_truth.", &lep_from_higgs_truth_intree);
  // chain->SetBranchAddress("lep_from_leptop_reco_truth.", &lep_from_leptop_truth_intree);
  // chain->SetBranchAddress("b_from_leptop_reco_truth.", &b_from_leptop_truth_intree);
  // chain->SetBranchAddress("b_from_hadtop_reco_truth.", &b_from_hadtop_truth_intree);
  // chain->SetBranchAddress("q1_from_hadtop_reco_truth.", &q1_from_hadtop_truth_intree);
  // chain->SetBranchAddress("q2_from_hadtop_reco_truth.", &q2_from_hadtop_truth_intree);
  // chain->SetBranchAddress("q1_from_higgs_reco_truth.", &q1_from_higgs_truth_intree);
  // chain->SetBranchAddress("q2_from_higgs_reco_truth.", &q2_from_higgs_truth_intree);

  eventReconstructor bdtReconstructor;
  hTagger higgsJetTagger;

  double time_per_event_intree = -1.;
  TLorentzVector hadtop_tlv_intree;
  TLorentzVector w_hadtop_tlv_intree;
  TLorentzVector higgs_tlv_intree;

  TTree *ss2l_tree = (TTree*)chain->CloneTree(0);
  TString tree_name = "ss2l_tree";
  if (systematic != "") tree_name += "_"+systematic;
  ss2l_tree->SetName(tree_name);
  ss2l_tree->SetDirectory(output_file_);

  ss2l_tree->Branch("time_per_event_signalExtraction", &time_per_event_intree);

  bdtReconstructor.initializeTree(ss2l_tree);
  higgsJetTagger.initializeTree(ss2l_tree);
  
  signalExtractionTreeMaker mySigExtrTreeMaker(ss2l_tree);

  Int_t cachesize = 250000000;   //250 MBytes
  chain->SetCacheSize(cachesize);
  double starttime = get_wall_time();

  //  max_tree_entry = 3000.;
  for (int i=min_tree_entry; i<max_tree_entry; i++)
    {      
      printProgress(i,max_tree_entry);
      clock_t startTime = clock();
      chain->GetEntry(i);

      /////////////////////
      /////
      ///// evaluation loop 
      /////
      /////////////////////
      
      // TLorentzVector b_from_hadtop_tlv = setTlv(*b_from_hadtop_truth_intree);
      // TLorentzVector q1_from_hadtop_tlv = setTlv(*q1_from_hadtop_truth_intree);
      // TLorentzVector q2_from_hadtop_tlv = setTlv(*q2_from_hadtop_truth_intree);
      // TLorentzVector q1_from_higgs_tlv = setTlv(*q1_from_higgs_truth_intree);
      // TLorentzVector q2_from_higgs_tlv = setTlv(*q2_from_higgs_truth_intree);
      // TLorentzVector lep_from_higgs_tlv = setTlv(*lep_from_higgs_truth_intree);

      // w_hadtop_tlv_intree = q1_from_hadtop_tlv + q2_from_hadtop_tlv;
      // hadtop_tlv_intree = w_hadtop_tlv_intree + b_from_hadtop_tlv;
      // higgs_tlv_intree = q1_from_higgs_tlv + q2_from_higgs_tlv + lep_from_higgs_tlv;

      // auto lep_collection = preselected_leptons_intree;
      vector<ttH::Lepton> *lep_collection;
      if (sample_name == "fakes") lep_collection = fakeable_leptons_intree;
      else lep_collection = tight_leptons_intree;
      std::sort(lep_collection->begin(), lep_collection->end(), [] (ttH::Lepton a, ttH::Lepton b) { return a.correctedPt > b.correctedPt;});
      

      vector<ttH::Jet> *jet_collection=0; jet_collection = preselected_jets_intree;
      if (systematic == "jes_up") jet_collection = preselected_jets_jecUp_intree;
      else if (systematic == "jes_down") jet_collection = preselected_jets_jecDown_intree;

      bdtReconstructor.initialize(jet_collection, lep_collection, (*met_intree)[0]);

      // bdtReconstructor.evaluateBdtMatching(lep_from_leptop_truth_intree,
      // 					   lep_from_higgs_truth_intree,
      // 					   b_from_leptop_truth_intree,
      // 					   b_from_hadtop_truth_intree,
      // 					   q1_from_hadtop_truth_intree,
      // 					   q2_from_hadtop_truth_intree,
      // 					   q1_from_higgs_truth_intree,
      // 					   q2_from_higgs_truth_intree ); //order of arguments matters here..
      
      //////////////////////////////
      ///
      /// apply hadtop jet removal for higgs tagger:
      ///
      //////////////////////////////
      
      vector<ttH::Jet> jets_for_higgsTagger;
      for (const auto & jet : *jet_collection)
      	{
      	  if (jet.obj.pt() == bdtReconstructor.b_from_hadtop_bdt_intree->obj.pt()) continue;
      	  else if (jet.obj.pt() == bdtReconstructor.q1_from_hadtop_bdt_intree->obj.pt()) continue;
      	  else if (jet.obj.pt() == bdtReconstructor.q2_from_hadtop_bdt_intree->obj.pt()) continue;
      	  else jets_for_higgsTagger.push_back(jet);
      	}	  
      higgsJetTagger.initialize(&jets_for_higgsTagger, lep_collection, (*met_intree)[0]);
      mySigExtrTreeMaker.initialize(jet_collection, lep_collection, (*met_intree)[0], bdtReconstructor, higgsJetTagger);
      
      time_per_event_intree = double( clock() - startTime ) / (double)CLOCKS_PER_SEC;
      ss2l_tree->Fill();
    }
  
  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (max_tree_entry>0) cout << "an average of " << (endtime - starttime) / (max_tree_entry-min_tree_entry) << " per event." << endl;
  
  ss2l_tree->Write();
}

void runSignalExtraction(string sample_name="ttZ_M10", int events_per_job=-1, int job_no=-1)
{
  Sample sample(sample_name);
    
  //if (sample_name == "") sample_name = "output_test";
  TString output_dir = "/scratch365/cmuelle2/extraction_trees/june14_test/";
  //  TString output_dir = "";
  TString output_file_name = output_dir+sample_name;
  if (events_per_job > -1 && job_no > -1) output_file_name += "_" + std::to_string(job_no);
  output_file_name += ".root";
  TFile *output_file = new TFile(output_file_name, "RECREATE"); //"UPDATE");

  if (job_no < 1 && sample_name != "fakes" && sample_name != "flips" && sample_name != "data")
    {
      TFile* input_file = new TFile(sample.input_file_name,"READONLY");
      TH1D* event_hist = (TH1D*)input_file->Get("numInitialWeightedMCevents");
      output_file->cd();
      event_hist->Write();
      input_file->Close();
    }

  run_it(sample_name,sample.getTree(),output_file,events_per_job,job_no);

  bool systs = true;
  if (systs && sample_name != "fakes" && sample_name != "flips" && sample_name != "data")
    {
      run_it(sample_name,sample.getTree("ss2l_tree_jes_up"),output_file,events_per_job,job_no, "jes_up");
      run_it(sample_name,sample.getTree("ss2l_tree_jes_down"),output_file,events_per_job,job_no, "jes_down");
    }
  
  gDirectory->Purge();
  output_file->Close();  
}

