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
/// usage: root -l makeFlatTreesForKevin.C
///
/////////////////////////////////////////


void run_it(TChain* tree, TString csv_file_str, double weight, int evt_class)
{

  int treeentries = tree->GetEntries();   
  cout << "# events in tree: "<< treeentries << endl;  

  double mcwgt_intree = -999.;
  double wallTimePerEvent_intree = -99.;  
  int eventnum_intree = -999;
  int lumiBlock_intree = -999;
  int runNumber_intree = -999;

  float max_lep_eta_input = -99.;
  float njets_input = -99.;
  float min_dr_l1j_input = -99.;
  float min_dr_l2j_input = -99.;
  float mt_met_l1_input = -99.;

  float l1pt = -99.;
  float l2pt = -99.;
  double vs_ttbar_output = -99.;
  double vs_ttv_output = -99.;
  int final_output = -99;

  double hj_score_input = -99.;
  double hadtop_score_input = -99.;
  bool btight = false;
  bool pluscat = false;
  TString *flavor=0;

  vector<ttH::Lepton> *preselected_leptons_intree=0;
  vector<ttH::Lepton> *fakeable_leptons_intree=0;
  vector<ttH::Jet> *preselected_jets_intree=0;
  vector<ttH::Lepton> *tight_leptons_intree=0;
  vector<ttH::MET> *met_intree=0;  

  // tree->SetBranchStatus("*",0);
  // tree->SetBranchStatus("mcwgt",1);
  // tree->SetBranchStatus("wallTimePerEvent",1);
  // tree->SetBranchStatus("eventnum",1);
  // tree->SetBranchStatus("lumiBlock",1);
  // tree->SetBranchStatus("preselected_leptons.*",1);
  // tree->SetBranchStatus("preselected_jets.*",1);
  // tree->SetBranchStatus("fakeable_leptons.*",1);

  tree->SetBranchAddress("mcwgt", &mcwgt_intree);
  tree->SetBranchAddress("wallTimePerEvent", &wallTimePerEvent_intree);
  tree->SetBranchAddress("eventnum", &eventnum_intree);
  tree->SetBranchAddress("lumiBlock", &lumiBlock_intree);
  tree->SetBranchAddress("preselected_leptons", &preselected_leptons_intree);
  tree->SetBranchAddress("fakeable_leptons", &fakeable_leptons_intree);
  tree->SetBranchAddress("preselected_jets", &preselected_jets_intree);
  tree->SetBranchAddress("met", &met_intree);
  //engineered vars
  tree->SetBranchAddress("hj_score_best", &hj_score_input);
  tree->SetBranchAddress("max_Lep_eta", &max_lep_eta_input);
  tree->SetBranchAddress("numJets_float", &njets_input);
  tree->SetBranchAddress("mindr_lep1_jet", &min_dr_l1j_input);
  tree->SetBranchAddress("mindr_lep2_jet", &min_dr_l2j_input);
  tree->SetBranchAddress("MT_met_lep1", &mt_met_l1_input);
  tree->SetBranchAddress("reco_score", &hadtop_score_input);
  tree->SetBranchAddress("l1_pt", &l1pt);
  tree->SetBranchAddress("l2_pt", &l2pt);
  //discriminating outputs
  tree->SetBranchAddress("vs_ttbar_withRecoBdt_score", &vs_ttbar_output);
  tree->SetBranchAddress("vs_ttv_score", &vs_ttv_output);
  tree->SetBranchAddress("final_shape_BDTv8", &final_output);

  tree->SetBranchAddress("bTight_category", &btight);
  tree->SetBranchAddress("plus_category", &pluscat);
  tree->SetBranchAddress("flavor_category", &flavor);



  Int_t cachesize = 250000000;   //250 MBytes
  tree->SetCacheSize(cachesize);
  tree->SetCacheLearnEntries(20); 

  // fout<<setiosflags(ios::fixed)<<setprecision(5);
  ofstream csv_file;
  csv_file.open(csv_file_str);
  // signal_ptsorted_file <<"signal (1) / bkg (0), eventnum, ";  
  // signal_ptsorted_file<<"jet1 pT, jet1 eta, jet1 phi, jet1 mass, ";
  // signal_ptsorted_file<<"lep2 pT, lep2 eta, lep2 phi, lep2 mass \n";

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

      //////////////////////////
      ////
      //// calculation of new vars etc
      ////
      //////////////////////////

      //write csv files
      csv_file << eventnum_intree <<", ";  
      
      int lepcount = 0;
      for (const auto & lep : *fakeable_leptons_intree)
	{
	  if (lepcount >=2) break;
	  csv_file << lep.obj.pt() << ", " << lep.obj.eta() <<", "<< lep.obj.phi() <<", "<< lep.charge <<", " << lep.pdgID <<", ";
	  lepcount +=1;
	}  
      
      int jet_count=0;
      for (const auto & jet : *preselected_jets_intree)
	{
	  if (jet_count >= 8) break;
	  csv_file << jet.obj.pt() << ", " << jet.obj.eta() <<", "<< jet.obj.phi() <<", " <<  jet.obj.M() <<", " << jet.csv <<", " << jet.qgid <<", ";      
	  jet_count +=1;
	}
      while (jet_count < 8)
	{
	  csv_file << 0 << ", " << -9 <<", "<< -9 <<", "<< 0 <<", " << -9 <<", " << -9 <<", ";      
	  jet_count +=1;
	}

      csv_file << (*met_intree)[0].pt_forSync << ", " << (*met_intree)[0].phi_forSync <<", ";  
      
      //engineered vars
      csv_file << hj_score_input << ", " << hadtop_score_input << ", " << max_lep_eta_input << ", " << njets_input << ", " << min_dr_l1j_input << ", " << min_dr_l2j_input << ", " << mt_met_l1_input << ", " << l1pt << ", " << l2pt << ", ";
      csv_file << vs_ttbar_output << ", " << vs_ttv_output << ", " << final_output << ", "; 
      
      
      unsigned int flavor_int = 0;
      int bin_multiplier = -1;
      if (flavor->CompareTo("ee")==0)
	{
	  flavor_int = 1;
	  if (pluscat) bin_multiplier = 0;
	  else bin_multiplier = 1;
	}
      else if (flavor->CompareTo("em")==0)
	{
	  flavor_int = 2;
	  if (btight)
	    {
	      if (pluscat) bin_multiplier = 2;
	      else bin_multiplier = 3;
	    }
	  else
	    {
	      if (pluscat) bin_multiplier = 4;
	      else bin_multiplier = 5;
	    }
	}
      else if (flavor->CompareTo("mm") ==0)
	{
	  flavor_int = 3;
	  if (btight)
	    {
	      if (pluscat) bin_multiplier = 6;
	      else bin_multiplier = 7;
	    }
	  else
	    {
	      if (pluscat) bin_multiplier = 8;
	      else bin_multiplier = 9;
	    }
	}


      csv_file << btight << ", " << pluscat << ", " << flavor_int << ", "; 


      unsigned int fine_bin = bin_multiplier*10 + int(final_output);
      csv_file << fine_bin  << ", " << weight <<", "; 
      csv_file << evt_class <<"\n";
    }
  
  
  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (treeentries>0) cout << "an average of " << (endtime - starttime) / treeentries << " per event." << endl;
  
  csv_file.close();

}

void makeFlatTreesForKevin(TString sample="")
{

  TString input_file = "/scratch365/cmuelle2/bdt_test/aug28_deep_learning/tth_powheg.root";
  //TString input_file = "/scratch365/cmuelle2/bdt_test/aug28_deep_learning/ttW_LO.root";
  //TString input_file = "/scratch365/cmuelle2/bdt_test/aug28_deep_learning/ttZ_LO.root";
  //TString input_file = "/scratch365/cmuelle2/bdt_test/aug28_deep_learning/ttjets_semilep.root";
  //TString input_file = "/scratch365/cmuelle2/bdt_test/aug28_deep_learning/ttjets_dilep.root";
  
  TChain *tth_chain = new TChain("ss2l_tree");    
  tth_chain->Add(input_file);

  TString csv_file_str_tth = "ttH.csv";
  TString csv_file_str_ttw = "ttW.csv";
  TString csv_file_str_ttz = "ttz.csv";
  TString csv_file_str_ttbar_dl = "ttbar_dilep.csv";
  TString csv_file_str_ttbar_sl = "ttbar_semilep.csv";

  //https://github.com/peruzzim/cmgtools-lite/blob/80X_M17/TTHAnalysis/macros/finalMVA/train_kinMVA_2D_2lss_3l.cxx#L167
  double weight_tth = 0.5085*(1-0.577)/3824936.0;
  double weight_ttw = 0.2043/85407.061152;
  double weight_ttz = 0.2529/100112.251834;
  double weight_ttbar_dl = 831.76*((3*0.108)*(3*0.108))/5927992.0;
  double weight_ttbar_sl = 831.76*(3*0.108)*(1-3*0.108)/11643834.5;

  run_it(tth_chain,csv_file_str_tth, weight_tth, 0);
  //run_it(tth_chain,csv_file_str_ttw, weight_ttw, 1);
  //run_it(tth_chain,csv_file_str_ttz, weight_ttz, 1);
  //run_it(tth_chain,csv_file_str_ttbar_sl, weight_ttbar_sl, 2);
  //run_it(tth_chain,csv_file_str_ttbar_dl, weight_ttbar_dl, 2);


}
