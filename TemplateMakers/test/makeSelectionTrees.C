//Charlie Mueller 2/24/2016
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
#include "loadSamples.h"

/////////////////////////////////////////
///
/// usage: root -l makeSelectionTrees.C+
///
/////////////////////////////////////////


void run_it(TChain* chain, TString output_file)
{


  TMVA::Reader* TMVAReader_lepTop_;
  Float_t bjet_lep_dr_var;
  Float_t bjet_csv_var;
  Float_t bjet_lep_mass_var;
  Float_t bjet_lep_pt_var;
  Float_t bjet_lep_ptratio_var;

  TMVAReader_lepTop_ = new TMVA::Reader( "!Color:!Silent" );
  TMVAReader_lepTop_->AddVariable( "bjet_lep_dR", &bjet_lep_dr_var );
  TMVAReader_lepTop_->AddVariable( "bJet.csv", &bjet_csv_var );
  TMVAReader_lepTop_->AddVariable( "bjet_lep_tlv.M()", &bjet_lep_mass_var);
  TMVAReader_lepTop_->AddVariable( "bjet_lep_tlv.Pt()", &bjet_lep_pt_var );
  TMVAReader_lepTop_->AddVariable( "bjet_lep_tlv.Pt()/(lep_tlv.Pt()+bJet.obj.pt())", &bjet_lep_ptratio_var );
  TMVAReader_lepTop_->BookMVA("BDTG method", "/afs/cern.ch/user/m/muell149/work/CMSSW_7_2_3/src/TMVA-v4.2.0/test/weights/TMVAClassification_BDTG_lepTop.weights.xml");

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

  double lepTop_BDT_intree = -2.;
  ttH::Jet bJet_intree;
  vector<ttH::Lepton> *lepton_intree=0;
  bool isLepTopPresent_intree = false;
  bool correctLepTopMatch_intree = false;

  TFile *copiedfile = new TFile(output_file, "RECREATE"); //"UPDATE"); // #, 'test' ) // "RECREATE");
  TTree *three_lep_tree = (TTree*)chain->CloneTree(0);
  three_lep_tree->SetName("threelep_tree");
  three_lep_tree->Branch("lepTop_score", &lepTop_BDT_intree);
  three_lep_tree->Branch("bJet", &bJet_intree);
  three_lep_tree->Branch("lep", &lepton_intree);
  three_lep_tree->Branch("isLepTopPresent", &isLepTopPresent_intree);
  three_lep_tree->Branch("isCorrectLepTopMatch", &correctLepTopMatch_intree);


  TTree *two_lep_tree = (TTree*)chain->CloneTree(0);
  two_lep_tree->SetName("ss2l_tree");
  two_lep_tree->Branch("lepTop_BDT", &lepTop_BDT_intree);
  two_lep_tree->Branch("lepTop_score", &lepTop_BDT_intree);
  two_lep_tree->Branch("bJet", &bJet_intree);
  two_lep_tree->Branch("lep", &lepton_intree);
  two_lep_tree->Branch("isLepTopPresent", &isLepTopPresent_intree);
  two_lep_tree->Branch("isCorrectLepTopMatch", &correctLepTopMatch_intree);
  
  Int_t cachesize = 250000000;   //250 MBytes
  chain->SetCacheSize(cachesize);
  chain->SetCacheLearnEntries(20); 
  
  double starttime = get_wall_time();
  //  chainentries = 100000;
  for (int i=0; i<chainentries; i++)
    {
      
      if (i%10000 == 0)
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
      bool passes3l = pass3l(*tight_electrons_intree, *preselected_electrons_intree, *tight_muons_intree, *preselected_muons_intree, *preselected_jets_intree, *met_intree);
      if ( !(passes2lss || passes3l) ) continue;

      //////////////////////////
      ////
      //// calculation of new vars etc
      ////
      //////////////////////////

      correctLepTopMatch_intree = false;
      isLepTopPresent_intree = false;
      ttH::Lepton lep_best;
      TLorentzVector bject_vect;
      TLorentzVector lep_vect;
      TLorentzVector bjet_lep_vect;
      bjet_lep_vect.SetPxPyPzE(0,0,0,0);
      lep_vect.SetPxPyPzE(0,0,0,0);
      bject_vect.SetPxPyPzE(0,0,0,0);
      bJet_intree.clear();
      lepTop_BDT_intree = -2.;
      
      for (const auto & jet : *preselected_jets_intree)
	{
	  bject_vect.SetPtEtaPhiE(jet.obj.pt(), jet.obj.eta(), jet.obj.phi(), jet.obj.E());
	  for (const auto & lep : *tight_leptons_intree)
	    {
	      lep_vect.SetPtEtaPhiE(lep.obj.pt(), lep.obj.eta(), lep.obj.phi(), lep.obj.E());
	      bjet_lep_vect = bject_vect+lep_vect;

	      bjet_lep_dr_var = bject_vect.DeltaR( lep_vect );
	      bjet_csv_var = jet.csv;
	      bjet_lep_mass_var = bjet_lep_vect.M();
	      bjet_lep_pt_var = bjet_lep_vect.Pt();
	      bjet_lep_ptratio_var = bjet_lep_vect.Pt()/(lep.obj.pt()+jet.obj.pt());
	      double mva_value = TMVAReader_lepTop_->EvaluateMVA( "BDTG method" );	  
      
	      if (mva_value > lepTop_BDT_intree)
		{
		  lepTop_BDT_intree = mva_value;
		  lep_best = lep;
		  bJet_intree = jet;		  
		}
	      
	      if (jet.genMotherPdgID == lep.genGrandMotherPdgID && abs(jet.genMotherPdgID) == 6 && abs(jet.genPdgID) == 5)
		{
		  isLepTopPresent_intree = true;
		}

	    }
	}

      lepton_intree->clear();
      lepton_intree->push_back(lep_best);
      
      if (bJet_intree.genMotherPdgID == lep_best.genGrandMotherPdgID && abs(bJet_intree.genMotherPdgID) == 6 && abs(bJet_intree.genPdgID) == 5)
	{
	  correctLepTopMatch_intree = true;
	}

      if ( passes2lss ) two_lep_tree->Fill();
      else if ( passes3l ) three_lep_tree->Fill();
    }
  
  
  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (chainentries>0) cout << "an average of " << (endtime - starttime) / chainentries << " per event." << endl;
  
  three_lep_tree->Write();
  two_lep_tree->Write();
  copiedfile->Close();

}

void makeSelectionTrees(void)
{

  TChain *tth_chain = loadFiles("ttH");  
  run_it(tth_chain,"ttH_lepTopBDTResults.root");

  // TChain *ttw_chain = loadFiles("ttW");
  // TChain *ttbar_chain = loadFiles("ttbar");

}
