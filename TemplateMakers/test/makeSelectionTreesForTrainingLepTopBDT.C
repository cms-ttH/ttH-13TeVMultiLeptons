#include <iostream>
#include "TSystem.h"
#include <vector>
#include "TH1.h"
#include "TChain.h"
#include <string>
#include "TString.h"
#include "TH1D.h"
#include "TFile.h"
#include <cmath>
#include "TLorentzVector.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/src/LinkDef.h"
#include "TMVA/Config.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#include "selection.h"

/////////////////////////////////////////
///
/// usage: root -l makeSelectionTreesForTraining.C+
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
  vector<ttH::Lepton> *tightMvaBased_leptons_intree=0;
  vector<ttH::Electron> *raw_electrons_intree=0;               
  vector<ttH::Electron> *preselected_electrons_intree=0;
  vector<ttH::Electron> *tightMvaBased_electrons_intree=0;
  vector<ttH::Muon> *raw_muons_intree=0;
  vector<ttH::Muon> *preselected_muons_intree=0;
  vector<ttH::Muon> *tightMvaBased_muons_intree=0;            
  vector<ttH::Jet> *preselected_jets_intree=0;
  vector<ttH::MET> *met_intree=0;
  vector<ttH::GenParticle> *pruned_genParticles_intree=0;
  vector<ttH::Lepton> *tight_leptons_intree=0;
  vector<ttH::Electron> *tight_electrons_intree=0;
  vector<ttH::Muon> *tight_muons_intree=0;
  
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

  double bkg_weight_intree = 1.;

  TLorentzVector bjet_vect_intree;
  TLorentzVector lep_vect_intree;
  TLorentzVector bjet_lep_vect_intree;
  bjet_lep_vect_intree.SetPxPyPzE(0,0,0,0);
  lep_vect_intree.SetPxPyPzE(0,0,0,0);
  bjet_vect_intree.SetPxPyPzE(0,0,0,0);
  ttH::Jet bJet_intree;
  double bjet_lep_dR_intree = -1.;

  TFile *copiedfile = new TFile(output_file, "RECREATE"); //"UPDATE"); // #, 'test' ) // "RECREATE");

  TTree *top_present_tree = (TTree*)chain->CloneTree(0);
  top_present_tree->SetName("top_present_tree");
  top_present_tree->Branch("bJet", &bJet_intree);
  top_present_tree->Branch("bjet_lep_dR", &bjet_lep_dR_intree);
  top_present_tree->Branch("bjet_lep_tlv", &bjet_lep_vect_intree);
  top_present_tree->Branch("lep_tlv", &lep_vect_intree);
  top_present_tree->Branch("weight", &bkg_weight_intree);

  TTree *top_absent_tree = (TTree*)chain->CloneTree(0);
  top_absent_tree->SetName("top_absent_tree");
  top_absent_tree->Branch("bJet", &bJet_intree);
  top_absent_tree->Branch("bjet_lep_dR", &bjet_lep_dR_intree);
  top_absent_tree->Branch("bjet_lep_tlv", &bjet_lep_vect_intree);
  top_absent_tree->Branch("lep_tlv", &lep_vect_intree);
  top_absent_tree->Branch("weight", &bkg_weight_intree);

  Int_t cachesize = 200000000;   //200 MBytes
  chain->SetCacheSize(cachesize);
  chain->SetCacheLearnEntries(20); 
  
  double starttime = get_wall_time();
  chainentries = 100000;
  for (int i=0; i<chainentries; i++)
    {
      
      if (i%4000 == 0)
	{
	  float fraction = 100.*i/chainentries;
	  cout << fraction << " % complete" << endl;
	  cout << i << endl;
	}
      
      chain->GetEntry(i);
      
      //      if ( (*preselected_jets_intree).size() < 3) continue; 
      bool passesCommon = passCommon(*tight_electrons_intree, *preselected_electrons_intree, *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree);
      if (!passesCommon) continue;
      bool passes2lss = pass2lss(*tight_electrons_intree, *preselected_electrons_intree, *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree, *met_intree);
      bool passes3l = pass3l(*tight_electrons_intree, *preselected_electrons_intree, *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree, *met_intree);
      if ( !(passes2lss || passes3l) ) continue;
      //      if ( (*preselected_jets_intree).size() < 4 ) continue;
      
    
      int num_jets = (*preselected_jets_intree).size();
      bkg_weight_intree = 1. / ( num_jets );
      //      bkg_weight_intree = 1. / ((num_jets*( num_jets - 1 )*( num_jets - 2))-1);

      for (const auto & jet : *preselected_jets_intree)
	{
	  bjet_vect_intree.SetPtEtaPhiE(jet.obj.pt(), jet.obj.eta(), jet.obj.phi(), jet.obj.E());
	  bJet_intree = jet;
	  for (const auto & lep : *tight_leptons_intree)
	    {
	      lep_vect_intree.SetPtEtaPhiE(lep.obj.pt(), lep.obj.eta(), lep.obj.phi(), lep.obj.E());
	      bjet_lep_vect_intree = bjet_vect_intree+lep_vect_intree;
	      bjet_lep_dR_intree = bjet_vect_intree.DeltaR( lep_vect_intree );

	      if (jet.genMotherPdgID == lep.genGrandMotherPdgID && abs(jet.genMotherPdgID) == 6 && abs(jet.genPdgID) == 5)
		{
		  top_present_tree->Fill();
		}
	      else
		{
		  top_absent_tree->Fill();
		}
	    }
	}
      
    }
  double endtime = get_wall_time();
  
  cout << "took " << endtime - starttime << " seconds, " << endl;
  if (chainentries>0) cout << "an average of " << (endtime - starttime) / chainentries << " per event." << endl;
  
  top_present_tree->Write();
  top_absent_tree->Write();
  copiedfile->Close();
  
}

void makeSelectionTreesForTrainingLepTopBDT(void)
{
  //  TChain *ttw_chain = new TChain("OSTwoLepAna/summaryTree");
  TChain *tth_chain = new TChain("OSTwoLepAna/summaryTree");
  //  TChain *tt_chain = new TChain("OSTwoLepAna/summaryTree");
  
  //  TString ttw_file = "ttw_trees_bdt_top_ratio.root";
  TString tth_file = "ttH_lepTop_BDTtraining.root";
  //  TString tt_file = "tt_trees_bdt_top_ratio.root";

  // ttw_chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/qgid/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_ttW/160128_162243/0000/tree_BDT_1.root");
  // ttw_chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/qgid/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_ttW/160128_162243/0000/tree_BDT_2.root");    
  // ttw_chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/qgid/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_ttW/160128_162243/0000/tree_BDT_3.root");    
  // ttw_chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/qgid/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_ttW/160128_162243/0000/tree_BDT_4.root");    
  // ttw_chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/qgid/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_ttW/160128_162243/0000/tree_BDT_5.root");    
  // ttw_chain->Add("root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/qgid/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_ttW/160128_162243/0000/tree_BDT_6.root");    

  for (int i=1; i < 83; i++)
    {
      char filePath[512];
      sprintf(filePath,"root://eoscms.cern.ch//eos/cms/store/user/muell149/ttH-leptons_Skims/76X_remake/ttHToNonbb_M125_13TeV_powheg_pythia8/crab_ttH125_powheg/160219_093036/0000/tree_BDT2_orig_%d.root",i);
      tth_chain->Add(filePath);
    }
  

  // run_it(ttw_chain,ttw_file);
  run_it(tth_chain,tth_file);
  //  run_it(tt_chain,tt_file);
}
