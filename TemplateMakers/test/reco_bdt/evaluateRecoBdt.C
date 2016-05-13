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
#include "ttH-13TeVMultiLeptons/TemplateMakers/src/LinkDef.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/test/eventReconstructor.h"
#include "TMVA/Config.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#include "../selection.h"
#include "../loadSamples.h"

/////////////////////////////////////////
///
/// usage: root -l makeSelectionTrees.C+
///
/////////////////////////////////////////


void run_it(TChain* chain, TString output_file)
{

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

  TFile *copiedfile = new TFile(output_file, "RECREATE"); //"UPDATE"); // #, 'test' ) // "RECREATE");

  double reco_score_intree = -1.;
  vector<ttH::Jet> *unmatched_jets_intree=0;
  vector<ttH::Jet> *matched_jets_intree=0;
  vector<ttH::Jet> *matched_jets_truth_intree=0;
  ttH::Lepton lep_fromHiggs_intree;  
  ttH::Lepton lep_fromTop_intree;

  vector<int> *match_results_intree=0;

  vector<double> *reco_scores_intree=0;  

  TLorentzVector w_fromHadTop_tlv_intree;
  TLorentzVector w_fromHiggs_tlv_intree;
  TLorentzVector higgs_tlv_intree;
  TLorentzVector hadTop_tlv_intree;
  TLorentzVector lepTop_tlv_intree;
  
  double dR_b_W_hadTop_intree = -1.;
  double dR_b_W_lepTop_intree = -1.;
  double dR_H_lepTop_intree = -1.;
  double dR_H_hadTop_intree = -1.;
  double dR_lepTop_hadTop_intree = -1.;
  double dR_W1_W2_fromHiggs_intree = -1.;
  double dR_q1_q2_fromWfromHiggs_intree = -1.;
  double       background_weight_intree = -1.;
  double       num_matches_intree = -1.;
  double norm_score_sum_intree = 0.;
  int num_real_jetMatches = 0;

  w_fromHadTop_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);
  w_fromHiggs_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);
  higgs_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);
  hadTop_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);
  lepTop_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);

  TTree *signal_tree = (TTree*)chain->CloneTree(0);
  signal_tree->SetName("ss2l_tree");
  signal_tree->Branch("reco_score", &reco_score_intree);
  signal_tree->Branch("unmatched_jets", &unmatched_jets_intree);
  signal_tree->Branch("matched_jets", &matched_jets_intree);
  signal_tree->Branch("matched_jets_truth", &matched_jets_truth_intree);
  signal_tree->Branch("lep_fromTop", &lep_fromTop_intree);
  signal_tree->Branch("lep_fromHiggs", &lep_fromHiggs_intree);
  signal_tree->Branch("w_fromHadTop", &w_fromHadTop_tlv_intree);
  signal_tree->Branch("w_fromHiggs", &w_fromHiggs_tlv_intree);
  signal_tree->Branch("higgs", &higgs_tlv_intree);
  signal_tree->Branch("hadTop", &hadTop_tlv_intree);
  signal_tree->Branch("lepTop", &lepTop_tlv_intree);

  signal_tree->Branch("dR_b_W_hadTop", &dR_b_W_hadTop_intree);
  signal_tree->Branch("dR_b_W_lepTop", &dR_b_W_lepTop_intree);
  signal_tree->Branch("dR_H_lepTop", &dR_H_lepTop_intree);
  signal_tree->Branch("dR_H_hadTop", &dR_H_hadTop_intree);
  signal_tree->Branch("dR_lepTop_hadTop", &dR_lepTop_hadTop_intree);
  signal_tree->Branch("dR_W1_W2_fromHiggs", &dR_W1_W2_fromHiggs_intree);
  signal_tree->Branch("dR_q1_q2_fromWfromHiggs", &dR_q1_q2_fromWfromHiggs_intree);
  signal_tree->Branch("reco_scores", &reco_scores_intree);
  signal_tree->Branch("num_bdt_matches", &background_weight_intree);
  signal_tree->Branch("num_true_matches", &num_matches_intree);
  signal_tree->Branch("match_results", &match_results_intree);
  signal_tree->Branch("norm_score_sum", &norm_score_sum_intree);

  // Int_t cachesize = 250000000;   //250 MBytes
  // chain->SetCacheSize(cachesize);
  // chain->SetCacheLearnEntries(20); 

  eventReconstructor bdtReconstructor;

  
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
      //// selection, vetos etc
      ////
      //////////////////////////

      //      if ( (*preselected_jets_intree).size() < 3) continue; 
      bool passesCommon = passCommon(*tight_electrons_intree, *preselected_electrons_intree, *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree);
      if (!passesCommon) continue;
      bool passes2lss = pass2lss(*tight_electrons_intree, *preselected_electrons_intree, *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree, *met_intree);
      if ( !passes2lss ) continue;

      //////////////////////////
      ////
      //// calculation of new vars etc
      ////
      //////////////////////////



      // //final state objs

      // TLorentzVector lep_fromTop_tlv;
      // TLorentzVector lep_fromTop_T_tlv;

      // TLorentzVector lep_fromHiggs_tlv;
      // TLorentzVector lep_fromHiggs_T_tlv;

      // TLorentzVector bjet_fromHadTop_tlv;
      // TLorentzVector bjet_fromHadTop_T_tlv;

      // TLorentzVector bjet_fromLepTop_tlv;
      // TLorentzVector bjet_fromLepTop_T_tlv;

      // TLorentzVector wjet1_fromHadTop_tlv;
      // TLorentzVector wjet1_fromHadTop_T_tlv;

      // TLorentzVector wjet2_fromHadTop_tlv;
      // TLorentzVector wjet2_fromHadTop_T_tlv;

      // TLorentzVector wjet1_fromHiggs_tlv;
      // TLorentzVector wjet1_fromHiggs_T_tlv;

      // TLorentzVector wjet2_fromHiggs_tlv;
      // TLorentzVector wjet2_fromHiggs_T_tlv;

      // //intermediate objs

      // TLorentzVector w_fromHadTop_tlv;
      // TLorentzVector w_fromHadTop_T_tlv;

      // TLorentzVector w_fromHiggs_tlv;
      // TLorentzVector w_fromHiggs_T_tlv;

      // //initial objs

      // TLorentzVector higgs_tlv;
      // TLorentzVector higgs_T_tlv;

      // TLorentzVector hadTop_tlv;
      // TLorentzVector hadTop_T_tlv;

      // TLorentzVector lepTop_tlv;
      // TLorentzVector lepTop_T_tlv;

      // //misc final state objs

      // TLorentzVector lepTop_higgs_tlv;
      // TLorentzVector lepTop_higgs_T_tlv;

      // TLorentzVector hadTop_higgs_tlv;
      // TLorentzVector hadTop_higgs_T_tlv;

      // TLorentzVector lepTop_hadTop_tlv;
      // TLorentzVector lepTop_hadTop_T_tlv;

      // TLorentzVector tth_tlv;
      // TLorentzVector tth_T_tlv;
      

      //reset tree vars
      reco_score_intree = -1.;
      unmatched_jets_intree->clear();
      matched_jets_intree->clear();
      matched_jets_truth_intree->clear();
      lep_fromHiggs_intree.clear();  
      lep_fromTop_intree.clear();  
      w_fromHadTop_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);
      w_fromHiggs_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);
      higgs_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);
      hadTop_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);
      lepTop_tlv_intree.SetPxPyPzE(0.,0.,0.,0.);
      dR_b_W_hadTop_intree = -1.;
      dR_b_W_lepTop_intree = -1.;
      dR_H_lepTop_intree = -1.;
      dR_H_hadTop_intree = -1.;
      dR_lepTop_hadTop_intree = -1.;
      dR_W1_W2_fromHiggs_intree = -1.;
      dR_q1_q2_fromWfromHiggs_intree = -1.;
      background_weight_intree = -1.;
      reco_scores_intree->clear();

      /////////////////////
      /////
      ///// evaluation loop 
      /////
      /////////////////////
      
      bdtReconstructor.initialize(preselected_jets_intree, tight_leptons_intree, (*met_intree)[0]);

      reco_score_intree = bdtReconstructor.reco_score;
      *match_results_intree = bdtReconstructor.matching_results;
      norm_score_sum_intree = bdtReconstructor.norm_score_sum;
      
      *matched_jets_intree = bdtReconstructor.matched_jets;
      *matched_jets_truth_intree = bdtReconstructor.matched_jets_truth;

      lep_fromHiggs_intree = bdtReconstructor.lep_fromHiggs_bdt;
      lep_fromTop_intree = bdtReconstructor.lep_fromTop_bdt;

      w_fromHadTop_tlv_intree = bdtReconstructor.w_fromHadTop_bdt_tlv;
      w_fromHiggs_tlv_intree = bdtReconstructor.w_fromHiggs_bdt_tlv;
      higgs_tlv_intree = bdtReconstructor.higgs_bdt_tlv;
      hadTop_tlv_intree = bdtReconstructor.hadTop_bdt_tlv;
      lepTop_tlv_intree = bdtReconstructor.lepTop_bdt_tlv;

      num_real_jetMatches = bdtReconstructor.num_real_jets_bdt;

      signal_tree->Fill();

    }
  
  
  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (chainentries>0) cout << "an average of " << (endtime - starttime) / chainentries << " per event." << endl;
  
  signal_tree->Write();
  copiedfile->Close();
  
}

void evaluateRecoBdt(TString sample, int start_file=0, int end_file=0)
{

  //  TString output_dir = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/lxbatch_output/";
  TString output_dir = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/baseline_original_slimmed/";

  TString output_file = output_dir+sample + "_batch_bdtEval_"+to_string(start_file)+"-"+to_string(end_file)+".root";
  TChain *tth_chain = loadFiles(sample,start_file,end_file);  
  run_it(tth_chain,output_file);

}
