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
#include "TMVA/Config.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#include "../selection.h"
#include "../loadSamples_80x.h"

/////////////////////////////////////////
///
/// usage: root -l evaluateRecoBdt.C+
///
/////////////////////////////////////////


void run_it(TChain* chain, TFile *output_file_)
{

  int chainentries = chain->GetEntries();   
  cout << "# events in tree: "<< chainentries << endl;  
  
  double mcwgt_intree = -999.;
  int eventnum_intree = -999;  
  vector<ttH::Electron> *preselected_electrons_intree=0;
  vector<ttH::Muon> *preselected_muons_intree=0;
  vector<ttH::Lepton> *preselected_leptons_intree=0;
  vector<ttH::Lepton> *loose_leptons_intree=0;
  vector<ttH::Jet> *preselected_jets_intree=0;
  vector<ttH::MET> *met_intree=0;
  vector<ttH::Lepton> *tight_leptons_intree=0;
  vector<ttH::Electron> *tight_electrons_intree=0;
  vector<ttH::Muon> *tight_muons_intree=0;

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
  chain->SetBranchStatus("looseMvaBased_leptons.*",1);
  chain->SetBranchStatus("tightMvaBased_leptons.*",1);
  chain->SetBranchStatus("tightMvaBased_electrons.*",1);
  chain->SetBranchStatus("tightMvaBased_muons.*",1);
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
  chain->SetBranchAddress("looseMvaBased_leptons", &loose_leptons_intree);
  chain->SetBranchAddress("preselected_jets", &preselected_jets_intree);
  chain->SetBranchAddress("tightMvaBased_leptons", &tight_leptons_intree);
  chain->SetBranchAddress("tightMvaBased_electrons", &tight_electrons_intree);
  chain->SetBranchAddress("tightMvaBased_muons", &tight_muons_intree);    
  //  chain->SetBranchAddress("met", &met_intree);

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
  TTree *signal_tree = (TTree*)chain->CloneTree(0);
  signal_tree->SetName("ss2l_tree");
  signal_tree->Branch("time_per_event", &time_per_event_intree);
  bdtReconstructor.initializeTree(signal_tree);
  

  Int_t cachesize = 250000000;   //250 MBytes
  chain->SetCacheSize(cachesize);
  // chain->SetCacheLearnEntries(20); 

  double starttime = get_wall_time();

  //  chainentries = 1000;
  for (int i=0; i<chainentries; i++)
    {
      printProgress(i,chainentries);

      clock_t startTime = clock();
      chain->GetEntry(i);

      /////////////////////
      /////
      ///// evaluation loop 
      /////
      /////////////////////
      

      //      bdtReconstructor.initialize(preselected_jets_intree, tight_leptons_intree);
      bdtReconstructor.initialize(preselected_jets_intree, loose_leptons_intree);
      bdtReconstructor.evaluateBdtMatching(lep_from_leptop_truth_intree,
					   lep_from_higgs_truth_intree,
					   b_from_leptop_truth_intree,
					   b_from_hadtop_truth_intree,
					   q1_from_hadtop_truth_intree,
					   q2_from_hadtop_truth_intree,
					   q1_from_higgs_truth_intree,
					   q2_from_higgs_truth_intree ); //order of arguments matters here..
      
      auto match_results = bdtReconstructor.match_results_bdt_intree;

      for (unsigned int i=1; i<= match_results->size()+1; i++)
	{
	  if ((*match_results)[i-1] == 5 || (*match_results)[i-1] == 4) match_eff_hist->Fill( i-1, 1. / chainentries );
	}

      time_per_event_intree = double( clock() - startTime ) / (double)CLOCKS_PER_SEC;

      signal_tree->Fill();

    }
  
  
  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (chainentries>0) cout << "an average of " << (endtime - starttime) / chainentries << " per event." << endl;

  match_eff_hist->Write();
  signal_tree->Write();
  output_file_->Close();
  
}

void evaluateRecoBdt(void)
{

  //  TString output_dir = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/bdt_v1p5_bTightLoose/";
  TString output_dir = "/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/signal_extraction/training/";

  //  TString output_file_name = output_dir+"ttbar_bdtEval.root";
  TString output_file_name = output_dir+"ttbar_mg5MLM_forSigExtractionTraingLoosenedSelection_bdtEval_v1p5.root";
  TFile *output_file = new TFile(output_file_name, "RECREATE"); //"UPDATE");

  TChain *tth_chain = new TChain("ss2l_tree;");
  //  tth_chain->Add("/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/ttV_selection_tree_2l_ss.root");
  //  tth_chain->Add("/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/ttH-powheg_selection_tree_2l_ss.root");
  //  tth_chain->Add("/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/ttH-aMC@NLO_selection_tree_2l_ss.root");
  //  tth_chain->Add("/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/ttbar-semiLep-powheg_selection_tree_2l_ss.root");
  //  tth_chain->Add("/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/ttbar-semiLep-madgraph_selection_tree_2l_ss.root");
  tth_chain->Add("/afs/cern.ch/user/m/muell149/work/CMSSW_8_0_13/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/ttbar-semiLep-madgraph_relaxedTrainSelection_tree_2lss.root");
  run_it(tth_chain,output_file);

}
