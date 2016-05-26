//Charlie Mueller 2/24/2016
#include <iostream>
#include <fstream>
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
#include "loadSamples.h"

/////////////////////////////////////////
///
/// usage: root -l makeSelectionTrees.C+
///
/////////////////////////////////////////


void write_csv(std::ofstream& in_file, vector<ttH::Jet> in_jets, vector<ttH::Lepton> in_leps, int event_num)
{
  in_file << 0 << ", " << event_num <<", ";  

  int jet_count=1;
  for (const auto & jet : in_jets)
    {
      if (jet_count > 9) break;
      in_file<< jet.obj.pt() << ", " << jet.obj.eta() <<", "<< jet.obj.phi() <<", "<< jet.obj.M() <<", ";      
      jet_count +=1;
    }
  
  for (const auto & lep : in_leps)
    {
      in_file<< lep.obj.pt() << ", " << lep.obj.eta() <<", "<< lep.obj.phi() <<", "<< 0. <<", ";      
    }  
  in_file<<"\n";

}

void run_it(TChain* chain, TString output_file, TString sorted_file, TString unsorted_file)
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

  TTree *summary_tree = (TTree*)chain->CloneTree(0);
  summary_tree->SetName("ss2l_tree");
  // Int_t cachesize = 250000000;   //250 MBytes
  // chain->SetCacheSize(cachesize);
  // chain->SetCacheLearnEntries(20); 

  // fout<<setiosflags(ios::fixed)<<setprecision(5);
  ofstream signal_unsorted_file;
  ofstream signal_sorted_file;
  signal_unsorted_file.open(unsorted_file);
  signal_sorted_file.open(sorted_file);

  //unsorted
  // signal_unsorted_file <<"signal (1) / bkg (0), eventnum, ";  
  // signal_unsorted_file<<"jet1 pT, jet1 eta, jet1 phi, jet1 mass, ";
  // signal_unsorted_file<<"jet2 pT, jet2 eta, jet2 phi, jet2 mass, ";
  // signal_unsorted_file<<"jet3 pT, jet3 eta, jet3 phi, jet3 mass, ";
  // signal_unsorted_file<<"jet4 pT, jet4 eta, jet4 phi, jet4 mass, ";
  // signal_unsorted_file<<"jet5 pT, jet5 eta, jet5 phi, jet5 mass, ";
  // signal_unsorted_file<<"jet6 pT, jet6 eta, jet6 phi, jet6 mass, ";
  // signal_unsorted_file<<"jet7 pT, jet7 eta, jet7 phi, jet7 mass, ";
  // signal_unsorted_file<<"jet8 pT, jet8 eta, jet8 phi, jet8 mass, ";
  // signal_unsorted_file<<"jet9 pT, jet9 eta, jet9 phi, jet9 mass, ";
  // signal_unsorted_file<<"lep1 pT, lep1 eta, lep1 phi, lep1 mass, ";
  // signal_unsorted_file<<"lep2 pT, lep2 eta, lep2 phi, lep2 mass \n";

  // //sorted file
  // signal_sorted_file <<"signal (1) / bkg (0), eventnum, ";  
  // signal_sorted_file<<"bjet (hadTop) pT, bjet (hadTop) eta, bjet (hadTop) phi, bjet (hadTop) mass, ";
  // signal_sorted_file<<"bjet (lepTop) pT, bjet (lepTop) eta, bjet (lepTop) phi, bjet (lepTop) mass, ";
  // signal_sorted_file<<"wjet1 (hadTop) pT, wjet1 (hadTop) eta, wjet1 (hadTop) phi, wjet1 (hadTop) mass, ";
  // signal_sorted_file<<"wjet2 (hadTop) pT, wjet2 (hadTop) eta, wjet2 (hadTop) phi, wjet2 (hadTop) mass, ";
  // signal_sorted_file<<"wjet1 (higgs) pT, wjet1 (higgs) eta, wjet1 (higgs) phi, wjet1 (higgs) mass, ";
  // signal_sorted_file<<"wjet2 (higgs) pT, wjet2 (higgs) eta, wjet2 (higgs) phi, wjet2 (higgs) mass, ";
  // signal_sorted_file<<"extra jet1 pT, extra jet1 eta, extra jet1 phi, extra jet1 mass, ";
  // signal_sorted_file<<"extra jet2 pT, extra jet2 eta, extra jet2 phi, extra jet2 mass, ";
  // signal_sorted_file<<"extra jet3 pT, extra jet3 eta, extra jet3 phi, extra jet3 mass, ";
  // signal_sorted_file<<"lep (top) pT, lep (top) eta, lep (top) phi, lep (top) mass, ";
  // signal_sorted_file<<"lep (higgs) pT, lep (higgs) eta, lep (higgs) phi, lep (higgs) mass \n";


  
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


      //sorted info
      vector<ttH::Jet> matched_jets_truth;
      ttH::Jet bjet_fromHadTop_truth;
      ttH::Jet bjet_fromLepTop_truth;
      ttH::Jet wjet1_fromHadTop_truth;
      ttH::Jet wjet2_fromHadTop_truth;
      ttH::Jet wjet1_fromHiggs_truth;
      ttH::Jet wjet2_fromHiggs_truth;

      
      // for (const auto & jet : *preselected_jets_intree)
      // 	{
      // 	  if (abs(jet.genPdgID) == 5)
      // 	    {
      // 	      if (jet.genPdgID*(*tight_leptons_intree)[0].charge < 0) bjet_fromHadTop_truth = jet;
      // 	      else bjet_fromLepTop_truth = jet;
      // 	    }
      // 	  else if ( jet.genGrandMotherPdgID == 25 )
      // 	    {
      // 	      if (wjet1_fromHiggs_truth.obj.pt() == 0) wjet1_fromHiggs_truth = jet;
      // 	      else wjet2_fromHiggs_truth = jet;
      // 	    }
      // 	  else if ( abs(jet.genGrandMotherPdgID) == 6 )
      // 	    {
      // 	      if (wjet1_fromHadTop_truth.obj.pt() == 0) wjet1_fromHadTop_truth = jet;
      // 	      else wjet2_fromHadTop_truth = jet;
      // 	    }
      // 	}

      for (const auto & jet : *preselected_jets_intree)
	{
	  if (abs(jet.genPdgID) == 5)
	    {
	      if (jet.genPdgID*(*tight_leptons_intree)[0].charge < 0) bjet_fromHadTop_truth = jet;
	      else bjet_fromLepTop_truth = jet;
	    }
	  else if ( abs(jet.genGrandMotherPdgID) == 6 && jet.genGrandMotherPdgID*(*tight_leptons_intree)[0].charge < 0 )
	    {
	      if (wjet1_fromHadTop_truth.obj.pt() == 0) wjet1_fromHadTop_truth = jet;
	      else wjet2_fromHadTop_truth = jet;
	    }
	}

      
      matched_jets_truth.push_back(bjet_fromHadTop_truth);
      matched_jets_truth.push_back(bjet_fromLepTop_truth);
      matched_jets_truth.push_back(wjet1_fromHadTop_truth);
      matched_jets_truth.push_back(wjet2_fromHadTop_truth);
      matched_jets_truth.push_back(wjet1_fromHiggs_truth);
      matched_jets_truth.push_back(wjet2_fromHiggs_truth);

      bool is_matched = false;    
      for (const auto & jet : *preselected_jets_intree)
	{
	  is_matched =false;
	  for (const auto & matched_jet : matched_jets_truth)
	    {
	      if (jet.obj.pt() == matched_jet.obj.pt())
		{
		  is_matched = true;
		  break;
		}
	    }
	  if ( !is_matched ) matched_jets_truth.push_back(jet);
	}
      
      int num_jets_added = 9 - matched_jets_truth.size();
      ttH::Jet empty_jet;
      for (int i=1; i<= num_jets_added; i++) matched_jets_truth.push_back(empty_jet);
      
      ttH::Lepton lep_fromTop_truth = (*tight_leptons_intree)[0];
      ttH::Lepton lep_fromHiggs_truth = (*tight_leptons_intree)[1];
      
      if (abs(lep_fromTop_truth.genGrandMotherPdgID) == 25 || abs(lep_fromHiggs_truth.genGrandMotherPdgID) == 6 )
	{
	  lep_fromTop_truth = (*tight_leptons_intree)[1];
	  lep_fromHiggs_truth = (*tight_leptons_intree)[0];
	}
      vector<ttH::Lepton> matched_leptons_truth;
      matched_leptons_truth.push_back(lep_fromTop_truth);
      matched_leptons_truth.push_back(lep_fromHiggs_truth);
      
      ///sorted
      num_jets_added = 9 - preselected_jets_intree->size();
      for (int i=1; i<= num_jets_added; i++) preselected_jets_intree->push_back(empty_jet);

      //write csv files
      write_csv(signal_sorted_file, matched_jets_truth, matched_leptons_truth, eventnum_intree);
      write_csv(signal_unsorted_file, *preselected_jets_intree, *tight_leptons_intree, eventnum_intree);
      
      summary_tree->Fill();
    }
  
  
  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (chainentries>0) cout << "an average of " << (endtime - starttime) / chainentries << " per event." << endl;
  
  summary_tree->Write();
  copiedfile->Close();
  signal_sorted_file.close();
  signal_unsorted_file.close();

}

void makeFlatTreesForKevin(TString sample, int start_file=0, int end_file=0)
{

  TString output_dir = "/afs/cern.ch/user/m/muell149/work/CMSSW_7_6_3/src/ttH-13TeVMultiLeptons/TemplateMakers/test/forKevin/";

  TString output_file = output_dir+sample + "_treeForKevin_"+to_string(start_file)+"-"+to_string(end_file)+".root";
  TChain *tth_chain = loadFiles(sample,start_file,end_file);  

  TString sorted_file_csv = output_dir+sample + "_sorted_treeForKevin_"+to_string(start_file)+"-"+to_string(end_file)+".csv";
  TString unsorted_file_csv = output_dir+sample + "_unsorted_treeForKevin_"+to_string(start_file)+"-"+to_string(end_file)+".csv";

  run_it(tth_chain,output_file,sorted_file_csv,unsorted_file_csv);

}
