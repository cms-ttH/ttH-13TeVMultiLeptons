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
#include "TMVA/Config.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/test/variables.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/test/treeTools.h"
#include "trainingTreeHelper.h"

/////////////////////////////////////////
///
/// usage: root -l trainRecoBdt.C+
///
/////////////////////////////////////////


void run_it(TChain* chain, TString output_file)
{

  TrainingTreeHelper signal_treeHelper;
  TrainingTreeHelper background_treeHelper;

  int chainentries = chain->GetEntries();   
  cout << "# events in tree: "<< chainentries << endl;  
  
  double mcwgt_intree = -999.;
  int eventnum_intree = -999;
  
  vector<ttH::Lepton> *preselected_leptons_intree=0;
  vector<ttH::Electron> *raw_electrons_intree=0;               
  vector<ttH::Electron> *preselected_electrons_intree=0;
  vector<ttH::Muon> *preselected_muons_intree=0;
  vector<ttH::Jet> *preselected_jets_intree=0;
  vector<ttH::MET> *met_intree=0;
  vector<ttH::Lepton> *tight_leptons_intree=0;
  vector<ttH::Lepton> *loose_leptons_intree=0;
  vector<ttH::Electron> *tight_electrons_intree=0;
  vector<ttH::Muon> *tight_muons_intree=0;
  TString *higgs_final_state_intree=0;
  TString *ttbar_final_state_intree=0;
  int higgs_decay_intree = -9999;
  ttH::Lepton *lep_from_higgs_intree=0;
  ttH::Lepton *lep_from_leptop_intree=0;
  ttH::Jet *b_from_leptop_intree=0;
  ttH::Jet *b_from_hadtop_intree=0;
  ttH::Jet *q1_from_hadtop_intree=0;
  ttH::Jet *q2_from_hadtop_intree=0;
  ttH::Jet *q1_from_higgs_intree=0;
  ttH::Jet *q2_from_higgs_intree=0;

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
  chain->SetBranchAddress("preselected_leptons", &preselected_leptons_intree);
  chain->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
  chain->SetBranchAddress("preselected_muons", &preselected_muons_intree);
  chain->SetBranchAddress("preselected_jets", &preselected_jets_intree);
  chain->SetBranchAddress("looseMvaBased_leptons", &loose_leptons_intree);
  chain->SetBranchAddress("tightMvaBased_leptons", &tight_leptons_intree);
  chain->SetBranchAddress("tightMvaBased_electrons", &tight_electrons_intree);
  chain->SetBranchAddress("tightMvaBased_muons", &tight_muons_intree);    
  chain->SetBranchAddress("met", &met_intree);
  chain->SetBranchAddress("higgs_final_state", &higgs_final_state_intree);
  chain->SetBranchAddress("ttbar_final_state", &ttbar_final_state_intree);
  chain->SetBranchAddress("higgs_decay", &higgs_decay_intree);
  chain->SetBranchAddress("lep_from_higgs_reco_truth.", &lep_from_higgs_intree);
  chain->SetBranchAddress("lep_from_leptop_reco_truth.", &lep_from_leptop_intree);
  chain->SetBranchAddress("b_from_leptop_reco_truth.", &b_from_leptop_intree);
  chain->SetBranchAddress("b_from_hadtop_reco_truth.", &b_from_hadtop_intree);
  chain->SetBranchAddress("q1_from_hadtop_reco_truth.", &q1_from_hadtop_intree);
  chain->SetBranchAddress("q2_from_hadtop_reco_truth.", &q2_from_hadtop_intree);
  chain->SetBranchAddress("q1_from_higgs_reco_truth.", &q1_from_higgs_intree);
  chain->SetBranchAddress("q2_from_higgs_reco_truth.", &q2_from_higgs_intree);

  TFile *copiedfile = new TFile(output_file, "RECREATE"); //"UPDATE"); // #, 'test' ) // "RECREATE");

  vector<ttH::Jet> *matched_reco_jets_nonNull_truth_intree=0;

  TTree *signal_tree = (TTree*)chain->CloneTree(0);
  signal_tree->SetName("signal_tree");
  signal_tree->Branch("matched_reco_jets_nonNull_truth", &matched_reco_jets_nonNull_truth_intree);
  signal_treeHelper.initializeTree(signal_tree);

  TTree *background_tree = (TTree*)chain->CloneTree(0);
  background_tree->SetName("background_tree");
  background_tree->Branch("matched_reco_jets_nonNull_truth", &matched_reco_jets_nonNull_truth_intree);
  background_treeHelper.initializeTree(background_tree);
  
  Int_t cachesize = 250000000;   //250 MBytes
  chain->SetCacheSize(cachesize);
  //chain->SetCacheLearnEntries(20); 
  
  double starttime = get_wall_time();
  //  chainentries = 1000000;
  for (int i=0; i<chainentries; i++)
    {
      printProgress(i,chainentries);
      chain->GetEntry(i);

      //////////////////////////
      ////
      //// calculation of new vars etc
      ////
      //////////////////////////

      ttH::Lepton lep_fromTop_bdtInput_intree = *lep_from_leptop_intree;
      ttH::Lepton lep_fromHiggs_bdtInput_intree = *lep_from_higgs_intree;

      //      if ( abs( lep_fromTop_bdtInput_intree.genGrandMotherPdgID ) != 6 || abs( lep_fromHiggs_bdtInput_intree.genGrandMotherPdgID ) != 25 ) continue;

      ttH::Jet bjet_fromHadTop_truth = *b_from_hadtop_intree;
      ttH::Jet bjet_fromLepTop_truth = *b_from_leptop_intree;
      ttH::Jet wjet1_fromHadTop_truth = *q1_from_hadtop_intree;
      ttH::Jet wjet2_fromHadTop_truth = *q2_from_hadtop_intree;
      ttH::Jet wjet1_fromHiggs_truth = *q1_from_higgs_intree;
      ttH::Jet wjet2_fromHiggs_truth = *q2_from_higgs_intree;

      vector<ttH::Jet> matched_jets_truth;
      matched_reco_jets_nonNull_truth_intree->clear();
      matched_jets_truth.push_back(bjet_fromHadTop_truth);
      matched_jets_truth.push_back(bjet_fromLepTop_truth);
      matched_jets_truth.push_back(wjet1_fromHadTop_truth);
      matched_jets_truth.push_back(wjet2_fromHadTop_truth);
      matched_jets_truth.push_back(wjet1_fromHiggs_truth);
      matched_jets_truth.push_back(wjet2_fromHiggs_truth);

      for (const auto & non_null_jet : matched_jets_truth)
	{
	  if (non_null_jet.obj.pt() > 0) matched_reco_jets_nonNull_truth_intree->push_back(non_null_jet);
	}

      /////////////////////
      /////
      ///// signal 
      /////
      /////////////////////
      
      signal_treeHelper.lep_from_higgs_bdt_intree = lep_fromHiggs_bdtInput_intree;
      signal_treeHelper.lep_from_leptop_bdt_intree = lep_fromTop_bdtInput_intree;
      signal_treeHelper.b_from_leptop_bdt_intree = bjet_fromLepTop_truth;
      signal_treeHelper.b_from_hadtop_bdt_intree = bjet_fromHadTop_truth;
      signal_treeHelper.q1_from_hadtop_bdt_intree = wjet1_fromHadTop_truth;
      signal_treeHelper.q2_from_hadtop_bdt_intree = wjet2_fromHadTop_truth;
      signal_treeHelper.q1_from_higgs_bdt_intree = wjet1_fromHiggs_truth;
      signal_treeHelper.q2_from_higgs_bdt_intree = wjet2_fromHiggs_truth;
      signal_treeHelper.calculateInputs();

      //don't count signal if matched jets < 4
      if ( matched_reco_jets_nonNull_truth_intree->size() >= 3 && higgs_decay_intree == 24 && higgs_final_state_intree->CompareTo("semiLeptonic") == 0 && ttbar_final_state_intree->CompareTo("semiLeptonic") == 0 )
	{
	  signal_tree->Fill();
	}
      signal_treeHelper.resetVars();

      /////////////////////
      /////
      ///// background 
      /////
      /////////////////////

      //final state objs

      TLorentzVector lep_fromTop_tlv;
      TLorentzVector lep_fromTop_T_tlv;

      TLorentzVector lep_fromHiggs_tlv;
      TLorentzVector lep_fromHiggs_T_tlv;

      TLorentzVector bjet_fromHadTop_tlv;
      TLorentzVector bjet_fromHadTop_T_tlv;

      TLorentzVector bjet_fromLepTop_tlv;
      TLorentzVector bjet_fromLepTop_T_tlv;

      TLorentzVector wjet1_fromHadTop_tlv;
      TLorentzVector wjet1_fromHadTop_T_tlv;

      TLorentzVector wjet2_fromHadTop_tlv;
      TLorentzVector wjet2_fromHadTop_T_tlv;

      TLorentzVector wjet1_fromHiggs_tlv;
      TLorentzVector wjet1_fromHiggs_T_tlv;

      TLorentzVector wjet2_fromHiggs_tlv;
      TLorentzVector wjet2_fromHiggs_T_tlv;

      //intermediate objs

      TLorentzVector w_fromHadTop_tlv;
      TLorentzVector w_fromHadTop_T_tlv;

      TLorentzVector w_fromHiggs_tlv;
      TLorentzVector w_fromHiggs_T_tlv;

      //initial objs

      TLorentzVector higgs_tlv;
      TLorentzVector higgs_T_tlv;

      TLorentzVector hadTop_tlv;
      TLorentzVector hadTop_T_tlv;

      TLorentzVector lepTop_tlv;
      TLorentzVector lepTop_T_tlv;

      //misc final state objs

      TLorentzVector lepTop_higgs_tlv;
      TLorentzVector lepTop_higgs_T_tlv;

      TLorentzVector hadTop_higgs_tlv;
      TLorentzVector hadTop_higgs_T_tlv;

      TLorentzVector lepTop_hadTop_tlv;
      TLorentzVector lepTop_hadTop_T_tlv;

      TLorentzVector tth_tlv;
      TLorentzVector tth_T_tlv;
      

      //only add the same number of empty jets as there are fakes
      ttH::Jet null_jet;
      
      vector<ttH::Jet> jets_collection = *preselected_jets_intree;

      if (preselected_jets_intree->size() <=7)
	{
	  jets_collection.push_back(null_jet);
	  jets_collection.push_back(null_jet);
	  jets_collection.push_back(null_jet);
	}
      else if (preselected_jets_intree->size() ==8)
	{
	  jets_collection.push_back(null_jet);
	  jets_collection.push_back(null_jet);
	}
      else 
	{
	  jets_collection.push_back(null_jet);
	}

      //traditional loop
      //      int rand_cut = 70; //standard v1p5
      int rand_cut = 50;
      
      //      auto lep_collection = *tight_leptons_intree;
      auto lep_collection = *loose_leptons_intree;

      int lep_fromTop_count = -1;
      for (const auto & lep_fromTop : lep_collection)
      	{
      	  lep_fromTop_count +=1;
	  if (rand() % 100+1 > rand_cut) continue;
	  //if (lep_fromTop.obj.pt() == lep_fromTop_truth.obj.pt()) continue; //train only against incorrect lepton backgrounds
	  
      	  lep_fromTop_tlv = setTlv(lep_fromTop);
	  
      	  int lep_fromHiggs_count = -1;
      	  for (const auto & lep_fromHiggs : lep_collection)
      	    {
      	      lep_fromHiggs_count +=1;  
	      if (lep_fromTop_count == lep_fromHiggs_count) continue;
	      if (rand() % 100+1 > rand_cut) continue;

      	      lep_fromHiggs_tlv = setTlv(lep_fromHiggs);

      	      int bjet_fromHadTop_count = -1;
      	      for (const auto & bjet_fromHadTop : jets_collection)
      		{
      		  bjet_fromHadTop_count +=1;
		  if (rand() % 100+1 > rand_cut) continue;
      		  bjet_fromHadTop_tlv = setTlv(bjet_fromHadTop);

      		  int bjet_fromLepTop_count = -1;
      		  for (const auto & bjet_fromLepTop : jets_collection)
      		    {
      		      bjet_fromLepTop_count +=1;
		      if (rand() % 100+1 > rand_cut) continue;
      		      if (bjet_fromHadTop_count == bjet_fromLepTop_count) continue;
      		      if ( !( (bjet_fromHadTop.csv > 0.8 || bjet_fromLepTop.csv > 0.8) || (bjet_fromHadTop.csv > 0.4 && bjet_fromLepTop.csv > 0.4) ) ) continue;

      		      bjet_fromLepTop_tlv = setTlv(bjet_fromLepTop);
      		      lepTop_tlv = lep_fromTop_tlv + bjet_fromLepTop_tlv;

      		      if ( lepTop_tlv.M() > 180 ) continue;
		      
      		      int wjet1_fromHadTop_count = -1;
      		      for (const auto & wjet1_fromHadTop : jets_collection)
      			{
      			  wjet1_fromHadTop_count +=1;
			  if (rand() % 100+1 > rand_cut) continue;
      			  if (wjet1_fromHadTop_count == bjet_fromLepTop_count) continue;
      			  if (wjet1_fromHadTop_count == bjet_fromHadTop_count) continue;
			  
      			  wjet1_fromHadTop_tlv = setTlv(wjet1_fromHadTop);
			  
      			  int wjet2_fromHadTop_count = -1;
      			  for (const auto & wjet2_fromHadTop : jets_collection)
      			    {
      			      wjet2_fromHadTop_count +=1;
			      if (rand() % 100+1 > rand_cut) continue;
				  
      			      if (wjet2_fromHadTop_count == bjet_fromLepTop_count) continue;
      			      if (wjet2_fromHadTop_count == bjet_fromHadTop_count) continue;
      			      if (wjet2_fromHadTop_count <= wjet1_fromHadTop_count) continue; //don't need both orderings 

      			      wjet2_fromHadTop_tlv = setTlv(wjet2_fromHadTop); 
			      
      			      w_fromHadTop_tlv = wjet1_fromHadTop_tlv + wjet2_fromHadTop_tlv;
			      
      			      if (w_fromHadTop_tlv.M() > 120 ) continue; 

      			      hadTop_tlv = w_fromHadTop_tlv + bjet_fromHadTop_tlv;
			      
      			      if ( hadTop_tlv.M() > 220 ) continue;

      			      int wjet1_fromHiggs_count = -1;
      			      for (const auto & wjet1_fromHiggs : jets_collection)
      				{
      				  wjet1_fromHiggs_count +=1;
			  	  if (rand() % 100+1 > rand_cut) continue;
				  
      				  if (wjet1_fromHiggs_count == bjet_fromLepTop_count) continue;
      				  if (wjet1_fromHiggs_count == bjet_fromHadTop_count) continue;
      				  if (wjet1_fromHiggs_count == wjet1_fromHadTop_count) continue;
      				  if (wjet1_fromHiggs_count == wjet2_fromHadTop_count) continue;
				  
      				  wjet1_fromHiggs_tlv = setTlv(wjet1_fromHiggs); 
				  
      				  int wjet2_fromHiggs_count = -1;
      				  for (const auto & wjet2_fromHiggs : jets_collection)
      				    {
      				      wjet2_fromHiggs_count +=1;
				      if (rand() % 100+1 > rand_cut) continue;
				  
      				      if (wjet2_fromHiggs_count == bjet_fromLepTop_count) continue;
      				      if (wjet2_fromHiggs_count == bjet_fromHadTop_count) continue;
      				      if (wjet2_fromHiggs_count == wjet1_fromHadTop_count) continue;
      				      if (wjet2_fromHiggs_count == wjet2_fromHadTop_count) continue;
      				      if (wjet2_fromHiggs_count <= wjet1_fromHiggs_count) continue;
				      
      				      wjet2_fromHiggs_tlv = setTlv(wjet2_fromHiggs);

      				      w_fromHiggs_tlv = wjet1_fromHiggs_tlv + wjet2_fromHiggs_tlv;
				      
      				      if (w_fromHiggs_tlv.M() > 120 ) continue; 
				      
      				      higgs_tlv = w_fromHiggs_tlv + lep_fromHiggs_tlv;
				      
				      if (higgs_tlv.M() > 130 ) continue; 

				      background_treeHelper.lep_from_higgs_bdt_intree = lep_fromHiggs;
				      background_treeHelper.lep_from_leptop_bdt_intree = lep_fromTop;
				      background_treeHelper.b_from_leptop_bdt_intree = bjet_fromLepTop;
				      background_treeHelper.b_from_hadtop_bdt_intree = bjet_fromHadTop;
				      background_treeHelper.q1_from_hadtop_bdt_intree = wjet1_fromHadTop;
				      background_treeHelper.q2_from_hadtop_bdt_intree = wjet2_fromHadTop;
				      background_treeHelper.q1_from_higgs_bdt_intree = wjet1_fromHiggs;
				      background_treeHelper.q2_from_higgs_bdt_intree = wjet2_fromHiggs;
				      background_treeHelper.calculateInputs();
				      
				      background_tree->Fill();
      				    }
      				}
      			    }
      			}
      		    }
      		}
      	    }
      	}
      background_treeHelper.resetVars();
      
    }
  
  
  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (chainentries>0) cout << "an average of " << (endtime - starttime) / chainentries << " per event." << endl;
  
  //  signal_tree->Write();
  background_tree->Write();
  copiedfile->Close();
  
}

void trainRecoBdt(void)
{

  TString output_dir = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/training/";
  TString output_file = output_dir+"ttbar_semilep_madgraph_recoBdtTraining.root";
  TChain *chain_ = new TChain("ss2l_tree");
  chain_->Add("/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/selection_trees/ttbar-semiLep-madgraph_relaxed_2lss.root");
  run_it(chain_,output_file);

}
