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
#include "ttH-13TeVMultiLeptons/TemplateMakers/test/eventReconstructor.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/test/signalExtractionTreeMaker.h"
#include "TMVA/Config.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#include "../selection.h"
#include "../loadSamples.h"


/////////////////////////////////////////
///
/// usage: root -l evaluateRecoBdt.C+
///
/////////////////////////////////////////


void run_it(TChain* chain, TFile *output_file_, int events_per_job, int job_no)
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
  vector<ttH::MET> *met_intree=0;
  vector<ttH::Lepton> *tight_leptons_intree=0;
  vector<ttH::Electron> *tight_electrons_intree=0;
  vector<ttH::Muon> *tight_muons_intree=0;
  vector<ttH::Tau> *selected_taus_intree=0;

  //new stuff
  vector<ttH::Jet> *matched_reco_jets_intree=0;
  vector<ttH::Jet> *unmatched_reco_jets_intree=0;
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
  
  chain->SetBranchStatus("*",0);
  chain->SetBranchStatus("mcwgt",1);
  chain->SetBranchStatus("eventnum",1);
  chain->SetBranchStatus("preselected_electrons.*",1);
  chain->SetBranchStatus("preselected_muons.*",1);
  chain->SetBranchStatus("preselected_leptons.*",1);
  chain->SetBranchStatus("preselected_jets.*",1);

  chain->SetBranchStatus("fakeable_leptons.*",1);
  chain->SetBranchStatus("fakeable_electrons.*",1);
  chain->SetBranchStatus("fakeable_muons.*",1);
  chain->SetBranchStatus("tight_leptons.*",1);
  chain->SetBranchStatus("tight_electrons.*",1);
  chain->SetBranchStatus("tight_muons.*",1);

  // chain->SetBranchStatus("looseMvaBased_leptons.*",1);
  // chain->SetBranchStatus("looseMvaBased_electrons.*",1);
  // chain->SetBranchStatus("looseMvaBased_muons.*",1);
  // chain->SetBranchStatus("tightMvaBased_leptons.*",1);
  // chain->SetBranchStatus("tightMvaBased_electrons.*",1);
  // chain->SetBranchStatus("tightMvaBased_muons.*",1);


  chain->SetBranchStatus("selected_taus.*",1);
  chain->SetBranchStatus("met.*",1);
  chain->SetBranchStatus("higgs_final_state",1);
  chain->SetBranchStatus("ttbar_final_state",1);
  chain->SetBranchStatus("higgs_decay",1);
  chain->SetBranchStatus("matched_reco_jets.*",1);
  chain->SetBranchStatus("unmatched_reco_jets.*",1);
  chain->SetBranchStatus("lep_from_higgs_reco_truth*",1);
  chain->SetBranchStatus("lep_from_leptop_reco_truth*",1);
  chain->SetBranchStatus("b_from_leptop_reco_truth*",1);
  chain->SetBranchStatus("b_from_hadtop_reco_truth*",1);
  chain->SetBranchStatus("q1_from_hadtop_reco_truth*",1);
  chain->SetBranchStatus("q2_from_hadtop_reco_truth*",1);
  chain->SetBranchStatus("q1_from_higgs_reco_truth*",1);
  chain->SetBranchStatus("q2_from_higgs_reco_truth*",1);

  chain->SetBranchAddress("mcwgt", &mcwgt_intree);
  chain->SetBranchAddress("eventnum", &eventnum_intree);
  chain->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
  chain->SetBranchAddress("preselected_muons", &preselected_muons_intree);
  chain->SetBranchAddress("preselected_leptons", &preselected_leptons_intree);
  chain->SetBranchAddress("preselected_jets", &preselected_jets_intree);

  chain->SetBranchAddress("fakeable_leptons", &fakeable_leptons_intree);
  chain->SetBranchAddress("tight_leptons", &tight_leptons_intree);
  chain->SetBranchAddress("tight_electrons", &tight_electrons_intree);
  chain->SetBranchAddress("tight_muons", &tight_muons_intree);    

  // chain->SetBranchAddress("looseMvaBased_leptons", &fakeable_leptons_intree);
  // chain->SetBranchAddress("tightMvaBased_leptons", &tight_leptons_intree);
  // chain->SetBranchAddress("tightMvaBased_electrons", &tight_electrons_intree);
  // chain->SetBranchAddress("tightMvaBased_muons", &tight_muons_intree);    

  chain->SetBranchAddress("met", &met_intree);
  chain->SetBranchAddress("selected_taus", &selected_taus_intree);

  chain->SetBranchAddress("higgs_final_state", &higgs_final_state_intree);
  chain->SetBranchAddress("ttbar_final_state", &ttbar_final_state_intree);
  chain->SetBranchAddress("matched_reco_jets", &matched_reco_jets_intree);
  chain->SetBranchAddress("unmatched_reco_jets", &unmatched_reco_jets_intree);

  chain->SetBranchAddress("lep_from_higgs_reco_truth.", &lep_from_higgs_truth_intree);
  chain->SetBranchAddress("lep_from_leptop_reco_truth.", &lep_from_leptop_truth_intree);
  chain->SetBranchAddress("b_from_leptop_reco_truth.", &b_from_leptop_truth_intree);
  chain->SetBranchAddress("b_from_hadtop_reco_truth.", &b_from_hadtop_truth_intree);
  chain->SetBranchAddress("q1_from_hadtop_reco_truth.", &q1_from_hadtop_truth_intree);
  chain->SetBranchAddress("q2_from_hadtop_reco_truth.", &q2_from_hadtop_truth_intree);
  chain->SetBranchAddress("q1_from_higgs_reco_truth.", &q1_from_higgs_truth_intree);
  chain->SetBranchAddress("q2_from_higgs_reco_truth.", &q2_from_higgs_truth_intree);

  TH1D* match_eff_hist = new TH1D("Matching efficiency","matchingEff",7,0,7);
  match_eff_hist->GetXaxis()->SetBinLabel(1,"leptons");
  match_eff_hist->GetXaxis()->SetBinLabel(2,"b hadtop");
  match_eff_hist->GetXaxis()->SetBinLabel(3,"b leptop");
  match_eff_hist->GetXaxis()->SetBinLabel(4,"q1 hadtop");
  match_eff_hist->GetXaxis()->SetBinLabel(5,"q2 hadtop");
  match_eff_hist->GetXaxis()->SetBinLabel(6,"q1 higgs");
  match_eff_hist->GetXaxis()->SetBinLabel(7,"q2 higgs");
  match_eff_hist->GetYaxis()->SetTitle("matching efficiency");
  match_eff_hist->GetXaxis()->SetTitle("object");

  eventReconstructor bdtReconstructor;
  double time_per_event_intree = -1.;
  TLorentzVector hadtop_tlv_intree;
  TLorentzVector w_hadtop_tlv_intree;
  TLorentzVector higgs_tlv_intree;

  TTree *ss2l_tree = (TTree*)chain->CloneTree(0);
  ss2l_tree->SetName("ss2l_tree");
  ss2l_tree->Branch("time_per_event", &time_per_event_intree);

  ss2l_tree->Branch("hadtop_reco_truth", &hadtop_tlv_intree);
  ss2l_tree->Branch("w_hadtop_reco_truth", &w_hadtop_tlv_intree);
  ss2l_tree->Branch("higgs_reco_truth", &higgs_tlv_intree);

  bdtReconstructor.initializeTree(ss2l_tree);
  
  //new stuff for bdt trainin/evaluation. 
  TTree *ttH_vs_ttbar_tree = new TTree("tth_vs_ttbar_tree","tth_vs_ttbar_tree");
  TTree *ttH_vs_ttV_tree = new TTree("tth_vs_ttv_tree","tth_vs_ttv_tree");

  bool evaluateSignalExtraction = true;
  signalExtractionTreeMaker mySigExtrTreeMaker(ttH_vs_ttbar_tree, ttH_vs_ttV_tree, ss2l_tree, evaluateSignalExtraction);
  
  Int_t cachesize = 250000000;   //250 MBytes
  chain->SetCacheSize(cachesize);
  //  chain->SetCacheLearnEntries(20);
  //  gEnv->SetValue("TFile.AsyncPrefetching",1.);
  double starttime = get_wall_time();

  //  max_tree_entry = 1000;
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
      
      TLorentzVector b_from_hadtop_tlv = setTlv(*b_from_hadtop_truth_intree);
      TLorentzVector q1_from_hadtop_tlv = setTlv(*q1_from_hadtop_truth_intree);
      TLorentzVector q2_from_hadtop_tlv = setTlv(*q2_from_hadtop_truth_intree);
      TLorentzVector q1_from_higgs_tlv = setTlv(*q1_from_higgs_truth_intree);
      TLorentzVector q2_from_higgs_tlv = setTlv(*q2_from_higgs_truth_intree);
      TLorentzVector lep_from_higgs_tlv = setTlv(*lep_from_higgs_truth_intree);

      w_hadtop_tlv_intree = q1_from_hadtop_tlv + q2_from_hadtop_tlv;
      hadtop_tlv_intree = w_hadtop_tlv_intree + b_from_hadtop_tlv;
      higgs_tlv_intree = q1_from_higgs_tlv + q2_from_higgs_tlv + lep_from_higgs_tlv;

      // auto lep_collection = preselected_leptons_intree;
      //      auto lep_collection = fakeable_leptons_intree;
      auto lep_collection = tight_leptons_intree;

      bdtReconstructor.initialize(preselected_jets_intree, lep_collection, (*met_intree)[0]);
      bdtReconstructor.evaluateBdtMatching(lep_from_leptop_truth_intree,
					   lep_from_higgs_truth_intree,
					   b_from_leptop_truth_intree,
					   b_from_hadtop_truth_intree,
					   q1_from_hadtop_truth_intree,
					   q2_from_hadtop_truth_intree,
					   q1_from_higgs_truth_intree,
					   q2_from_higgs_truth_intree ); //order of arguments matters here..
      
      auto match_results = bdtReconstructor.match_results_bdt_intree;
      mySigExtrTreeMaker.initialize(preselected_jets_intree, lep_collection, (*met_intree)[0], selected_taus_intree, bdtReconstructor.reco_score_intree);
      
      time_per_event_intree = double( clock() - startTime ) / (double)CLOCKS_PER_SEC;
      ss2l_tree->Fill();
      ttH_vs_ttbar_tree->Fill();
      ttH_vs_ttV_tree->Fill();

    }
    
  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (max_tree_entry>0) cout << "an average of " << (endtime - starttime) / (max_tree_entry-min_tree_entry) << " per event." << endl;

  match_eff_hist->Write();
  ss2l_tree->Write();
  ttH_vs_ttbar_tree->Write();
  ttH_vs_ttV_tree->Write();
  output_file_->Close();
  
}

void evaluateRecoBdt(string sample_name="tth_training_2lssos", int events_per_job=-1, int job_no=-1)
{
  TString input_file_name = getSelectionFile(sample_name);
  TFile *input_file = new TFile(input_file_name, "READONLY");

  if (sample_name == "") sample_name = "output_test";
  TString output_dir = "/scratch365/cmuelle2/extraction_trees/nov22_ICHEP_trees_with_WgtHist/";
  TString output_file_name = output_dir+sample_name;
  if (events_per_job > -1 && job_no > -1) output_file_name += "_"+std::to_string(job_no);
  output_file_name += ".root";
  TFile *output_file = new TFile(output_file_name, "RECREATE"); //"UPDATE");

  if (job_no < 1)
    {
      TH1D* event_hist = (TH1D*)input_file->Get("numInitialWeightedMCevents");
      event_hist->Write();
    }
  
  TChain *chain_ = new TChain("ss2l_tree");
  chain_->Add(input_file_name);
  run_it(chain_,output_file,events_per_job,job_no);

}
