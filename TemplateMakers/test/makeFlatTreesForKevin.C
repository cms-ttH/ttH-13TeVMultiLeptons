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
#include "treeTools.h"

/////////////////////////////////////////
///
/// usage: root -l makeSelectionTrees.C+
///
/////////////////////////////////////////


void write_csv(std::ofstream& in_file, vector<ttH::Jet> in_jets, vector<ttH::Lepton> in_leps, int event_num, int ls_num)
{
  in_file << 0 << ", " << event_num <<", " << ls_num <<", ";  

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

void run_it(TChain* tree, TString output_file, TString sorted_file, TString ptsorted_file)
{

  int treeentries = tree->GetEntries();   
  cout << "# events in tree: "<< treeentries << endl;  

  double mcwgt_intree = -999.;
  double wallTimePerEvent_intree = -99.;  
  int eventnum_intree = -999;
  int lumiBlock_intree = -999;
  int runNumber_intree = -999;
  
  vector<ttH::Lepton> *preselected_leptons_intree=0;
  vector<ttH::Jet> *preselected_jets_intree=0;
  vector<ttH::Lepton> *tight_leptons_intree=0;
  
  //gen-matched objs
  ttH::Lepton *lep_from_higgs_truth_intree=0;
  ttH::Lepton *lep_from_leptop_truth_intree=0;
  ttH::Jet *b_from_leptop_truth_intree=0;
  ttH::Jet *b_from_hadtop_truth_intree=0;
  ttH::Jet *q1_from_hadtop_truth_intree=0;
  ttH::Jet *q2_from_hadtop_truth_intree=0;
  ttH::Jet *q1_from_higgs_truth_intree=0;
  ttH::Jet *q2_from_higgs_truth_intree=0;

  tree->SetBranchStatus("*",0);
  tree->SetBranchStatus("mcwgt",1);
  tree->SetBranchStatus("wallTimePerEvent",1);
  tree->SetBranchStatus("eventnum",1);
  tree->SetBranchStatus("lumiBlock",1);
  tree->SetBranchStatus("preselected_leptons.*",1);
  tree->SetBranchStatus("preselected_jets.*",1);
  tree->SetBranchStatus("lep_from_higgs_reco_truth*",1);
  tree->SetBranchStatus("lep_from_leptop_reco_truth*",1);
  tree->SetBranchStatus("b_from_leptop_reco_truth*",1);
  tree->SetBranchStatus("b_from_hadtop_reco_truth*",1);
  tree->SetBranchStatus("q1_from_hadtop_reco_truth*",1);
  tree->SetBranchStatus("q2_from_hadtop_reco_truth*",1);
  tree->SetBranchStatus("q1_from_higgs_reco_truth*",1);
  tree->SetBranchStatus("q2_from_higgs_reco_truth*",1);


  tree->SetBranchAddress("mcwgt", &mcwgt_intree);
  tree->SetBranchAddress("wallTimePerEvent", &wallTimePerEvent_intree);
  tree->SetBranchAddress("eventnum", &eventnum_intree);
  tree->SetBranchAddress("lumiBlock", &lumiBlock_intree);
  tree->SetBranchAddress("preselected_leptons", &preselected_leptons_intree);
  // tree->SetBranchAddress("tight_leptons", &tight_leptons_intree);
  tree->SetBranchAddress("preselected_jets", &preselected_jets_intree);
  //gen-matched objs
  tree->SetBranchAddress("lep_from_higgs_reco_truth.", &lep_from_higgs_truth_intree);
  tree->SetBranchAddress("lep_from_leptop_reco_truth.", &lep_from_leptop_truth_intree);
  tree->SetBranchAddress("b_from_leptop_reco_truth.", &b_from_leptop_truth_intree);
  tree->SetBranchAddress("b_from_hadtop_reco_truth.", &b_from_hadtop_truth_intree);
  tree->SetBranchAddress("q1_from_hadtop_reco_truth.", &q1_from_hadtop_truth_intree);
  tree->SetBranchAddress("q2_from_hadtop_reco_truth.", &q2_from_hadtop_truth_intree);
  tree->SetBranchAddress("q1_from_higgs_reco_truth.", &q1_from_higgs_truth_intree);
  tree->SetBranchAddress("q2_from_higgs_reco_truth.", &q2_from_higgs_truth_intree);


  TFile *copiedfile = new TFile(output_file, "RECREATE"); //"UPDATE"); // #, 'test' ) // "RECREATE");

  TTree *summary_tree = (TTree*)tree->CloneTree(0);
  summary_tree->SetName("ss2l_tree");
  Int_t cachesize = 250000000;   //250 MBytes
  tree->SetCacheSize(cachesize);
  tree->SetCacheLearnEntries(20); 

  // fout<<setiosflags(ios::fixed)<<setprecision(5);
  ofstream signal_ptsorted_file;
  ofstream signal_sorted_file;
  signal_ptsorted_file.open(ptsorted_file);
  signal_sorted_file.open(sorted_file);

  //ptsorted
  // signal_ptsorted_file <<"signal (1) / bkg (0), eventnum, ";  
  // signal_ptsorted_file<<"jet1 pT, jet1 eta, jet1 phi, jet1 mass, ";
  // signal_ptsorted_file<<"jet2 pT, jet2 eta, jet2 phi, jet2 mass, ";
  // signal_ptsorted_file<<"jet3 pT, jet3 eta, jet3 phi, jet3 mass, ";
  // signal_ptsorted_file<<"jet4 pT, jet4 eta, jet4 phi, jet4 mass, ";
  // signal_ptsorted_file<<"jet5 pT, jet5 eta, jet5 phi, jet5 mass, ";
  // signal_ptsorted_file<<"jet6 pT, jet6 eta, jet6 phi, jet6 mass, ";
  // signal_ptsorted_file<<"jet7 pT, jet7 eta, jet7 phi, jet7 mass, ";
  // signal_ptsorted_file<<"jet8 pT, jet8 eta, jet8 phi, jet8 mass, ";
  // signal_ptsorted_file<<"jet9 pT, jet9 eta, jet9 phi, jet9 mass, ";
  // signal_ptsorted_file<<"lep1 pT, lep1 eta, lep1 phi, lep1 mass, ";
  // signal_ptsorted_file<<"lep2 pT, lep2 eta, lep2 phi, lep2 mass \n";

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
  //  treeentries = 1000000;
  for (int i=0; i<treeentries; i++)
    {

      printProgress(i,treeentries);
      tree->GetEntry(i);

      //////////////////////////
      ////
      //// selection, vetos etc
      ////
      //////////////////////////

      // bool passesCommon = passCommon(*tight_electrons_intree, *preselected_electrons_intree, *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree);
      // if (!passesCommon) continue;
      // bool passes2lss = pass2lss(*tight_electrons_intree, *preselected_electrons_intree, *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree, *met_intree);
      // if ( !passes2lss ) continue;

      //////////////////////////
      ////
      //// calculation of new vars etc
      ////
      //////////////////////////

      //sorted info
      vector<ttH::Jet> matched_jets_truth;
      matched_jets_truth.push_back(*b_from_hadtop_truth_intree);
      matched_jets_truth.push_back(*b_from_leptop_truth_intree);
      matched_jets_truth.push_back(*q1_from_hadtop_truth_intree);
      matched_jets_truth.push_back(*q2_from_hadtop_truth_intree);
      matched_jets_truth.push_back(*q1_from_higgs_truth_intree);
      matched_jets_truth.push_back(*q2_from_higgs_truth_intree);
      
      //////////////////////////
      ////
      //// Add unmatched jets to end of matched-jets vector
      ////
      //////////////////////////      
      bool is_matched;    
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
      //////////////////////////
      //////////////////////////      
      //////////////////////////      
      //////////////////////////      

      int num_jets_added = 9 - matched_jets_truth.size();
      ttH::Jet empty_jet;
      for (int i=1; i<= num_jets_added; i++) matched_jets_truth.push_back(empty_jet);

      ttH::Lepton lep1 = (*preselected_leptons_intree)[0];
      ttH::Lepton lep2 = (*preselected_leptons_intree)[1];
      vector<ttH::Lepton> pt_sorted_leptons = { lep1, lep2 }; 


      // if we're mising leptons, try to add them in order of pt
      if ( (*lep_from_leptop_truth_intree).obj.pt() == 0 )
	{
	  if ( (*lep_from_higgs_truth_intree).obj.pt() != lep1.obj.pt() ) *lep_from_leptop_truth_intree = lep1;
	  else 	*lep_from_leptop_truth_intree = lep2;
	}
      else if ( (*lep_from_higgs_truth_intree).obj.pt() == 0 )
	{
	  if ( (*lep_from_leptop_truth_intree).obj.pt() != lep2.obj.pt() ) *lep_from_higgs_truth_intree = lep2;
	  else 	*lep_from_higgs_truth_intree = lep1;
	}
      
      vector<ttH::Lepton> matched_leptons_truth = { *lep_from_leptop_truth_intree, *lep_from_higgs_truth_intree };

      ///sorted jets
      num_jets_added = 9 - preselected_jets_intree->size();
      for (int i=1; i<= num_jets_added; i++) preselected_jets_intree->push_back(empty_jet);

      //write csv files
      write_csv(signal_sorted_file, matched_jets_truth, matched_leptons_truth, eventnum_intree, lumiBlock_intree);
      write_csv(signal_ptsorted_file, *preselected_jets_intree, pt_sorted_leptons, eventnum_intree, lumiBlock_intree);
      
      summary_tree->Fill();
    }
  
  
  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (treeentries>0) cout << "an average of " << (endtime - starttime) / treeentries << " per event." << endl;
  
  summary_tree->Write();
  copiedfile->Close();
  signal_sorted_file.close();
  signal_ptsorted_file.close();

}

void makeFlatTreesForKevin(TString sample="")
{

  TString output_dir = "";
  TString input_file;
  
  if (sample =="")
    {
      //input_file = getSelectionFile( "tth_powheg_genFilterTraining" );
      input_file = getSelectionFile( "ttbar_semiLep_genFilterTraining" );
      //input_file = getSelectionFile( "ttw_genFilterTraining" );
      sample = "ttbar";
    }
  else 
    {
      input_file = getSelectionFile( sample );
    }
  
  TString output_file = output_dir+sample + "_treeForDeepLearning.root";
  TChain *tth_chain = new TChain("ss2l_tree");    
  tth_chain->Add(input_file);

  TString sorted_file_csv = output_dir+sample + "_sorted_tree.csv";
  TString ptsorted_file_csv = output_dir+sample + "_ptsorted_tree.csv";

  run_it(tth_chain,output_file,sorted_file_csv,ptsorted_file_csv);

}
