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
/// usage: root -l makeSelectionTreesForTraining.C+
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
  double isNearestLepton_intree = 0.;
  double isHighestLepton_intree = 0.;
  double deltaPt_intree = 0;
  double met_dr_intree = -1.;

  TLorentzVector lephiggs_vect_intree;
  TLorentzVector bjet_lephiggs_vect_intree;
  bjet_lephiggs_vect_intree.SetPxPyPzE(0,0,0,0);
  lephiggs_vect_intree.SetPxPyPzE(0,0,0,0);
  double bjet_lephiggs_dR_intree = -1.;

  TFile *copiedfile = new TFile(output_file, "RECREATE"); //"UPDATE"); // #, 'test' ) // "RECREATE");

  TTree *top_present_tree = (TTree*)chain->CloneTree(0);
  top_present_tree->SetName("top_present_tree");
  top_present_tree->Branch("bJet", &bJet_intree);
  top_present_tree->Branch("bjet_lep_dR", &bjet_lep_dR_intree);
  top_present_tree->Branch("bjet_lep_tlv", &bjet_lep_vect_intree);
  top_present_tree->Branch("lep_tlv", &lep_vect_intree);
  top_present_tree->Branch("isNearestLep", &isNearestLepton_intree);
  top_present_tree->Branch("isHighestLep", &isHighestLepton_intree);
  top_present_tree->Branch("deltaPt", &deltaPt_intree);
  top_present_tree->Branch("met_top_dr", &met_dr_intree);

  top_present_tree->Branch("bjet_lephiggs_dR", &bjet_lephiggs_dR_intree);
  top_present_tree->Branch("bjet_lephiggs_tlv", &bjet_lephiggs_vect_intree);
  top_present_tree->Branch("lephiggs_tlv", &lephiggs_vect_intree);

  top_present_tree->Branch("weight", &bkg_weight_intree);

  TTree *top_absent_tree = (TTree*)chain->CloneTree(0);
  top_absent_tree->SetName("top_absent_tree");
  top_absent_tree->Branch("bJet", &bJet_intree);
  top_absent_tree->Branch("bjet_lep_dR", &bjet_lep_dR_intree);
  top_absent_tree->Branch("bjet_lep_tlv", &bjet_lep_vect_intree);
  top_absent_tree->Branch("lep_tlv", &lep_vect_intree);
  top_absent_tree->Branch("isNearestLep", &isNearestLepton_intree);
  top_absent_tree->Branch("isHighestLep", &isHighestLepton_intree);
  top_absent_tree->Branch("deltaPt", &deltaPt_intree);
  top_absent_tree->Branch("met_top_dr", &met_dr_intree);

  top_absent_tree->Branch("bjet_lephiggs_dR", &bjet_lephiggs_dR_intree);
  top_absent_tree->Branch("bjet_lephiggs_tlv", &bjet_lephiggs_vect_intree);
  top_absent_tree->Branch("lephiggs_tlv", &lephiggs_vect_intree);

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
      double best_mva_value = -1.;
      TLorentzVector bjet_vect;
      TLorentzVector lep_vect;
      TLorentzVector bjet_lep_vect;
      TLorentzVector met_vect;
      bjet_lep_vect.SetPxPyPzE(0,0,0,0);
      lep_vect.SetPxPyPzE(0,0,0,0);
      bjet_vect.SetPxPyPzE(0,0,0,0);
      met_vect.SetPtEtaPhiE((*met_intree)[0].obj.pt(), (*met_intree)[0].obj.eta(), (*met_intree)[0].obj.phi(), (*met_intree)[0].obj.E());


      for (const auto & jet : *preselected_jets_intree)
 	{
	  bjet_vect_intree.SetPtEtaPhiE(jet.obj.pt(), jet.obj.eta(), jet.obj.phi(), jet.obj.E());
	  bjet_vect.SetPtEtaPhiE(jet.obj.pt(), jet.obj.eta(), jet.obj.phi(), jet.obj.E());


	  //	  if (jet.csv < 0.5) continue;

	  //find out if the lepton choosen is the nearest.
	  double min_dR = 10;
	  for (const auto & lep : *tight_leptons_intree)
	    {
	      lep_vect_intree.SetPtEtaPhiE(lep.obj.pt(), lep.obj.eta(), lep.obj.phi(), lep.obj.E());
	      double dR = bjet_vect_intree.DeltaR( lep_vect_intree );
	      if ( dR < min_dR)
		{
		  min_dR = dR;
		} 
	    }
	  
	  int lep_count = 0;
	  for (const auto & lep : *tight_leptons_intree)
	    {


	      bJet_intree = jet;
	      lep_vect_intree.SetPtEtaPhiE(lep.obj.pt(), lep.obj.eta(), lep.obj.phi(), lep.obj.E());
	      bjet_lep_vect_intree = bjet_vect_intree+lep_vect_intree;
	      bjet_lep_dR_intree = bjet_vect_intree.DeltaR( lep_vect_intree );


	      met_dr_intree = met_vect.DeltaR( bjet_lep_vect_intree );

	      TLorentzVector lep_vect;
	      if (lep_count == 0)
		{
		  isHighestLepton_intree = lep.obj.pt()/(*tight_leptons_intree)[1].obj.pt();
		  
		  lep_vect.SetPtEtaPhiE((*tight_leptons_intree)[1].obj.pt(), (*tight_leptons_intree)[1].obj.eta(), (*tight_leptons_intree)[1].obj.phi(), (*tight_leptons_intree)[1].obj.E());
		  isNearestLepton_intree = bjet_lep_dR_intree / bjet_vect_intree.DeltaR( lep_vect ) ;

		  lephiggs_vect_intree = lep_vect;
		  bjet_lephiggs_vect_intree = bjet_vect_intree+lephiggs_vect_intree;
		  bjet_lephiggs_dR_intree = bjet_vect_intree.DeltaR( lephiggs_vect_intree );

		}
	      else
		{
		  isHighestLepton_intree = lep.obj.pt()/(*tight_leptons_intree)[0].obj.pt();

		  lep_vect.SetPtEtaPhiE((*tight_leptons_intree)[0].obj.pt(), (*tight_leptons_intree)[0].obj.eta(), (*tight_leptons_intree)[0].obj.phi(), (*tight_leptons_intree)[0].obj.E());
		  isNearestLepton_intree = bjet_lep_dR_intree / bjet_vect_intree.DeltaR( lep_vect ) ;

		  lephiggs_vect_intree = lep_vect;
		  bjet_lephiggs_vect_intree = bjet_vect_intree+lephiggs_vect_intree;
		  bjet_lephiggs_dR_intree = bjet_vect_intree.DeltaR( lephiggs_vect_intree );

		}


	      deltaPt_intree = ( lep.obj.pt() - (*tight_leptons_intree)[tight_leptons_intree->size()-1].obj.pt() );

	      if (jet.genMotherPdgID == lep.genGrandMotherPdgID && abs(jet.genMotherPdgID) == 6 && abs(jet.genPdgID) == 5)
		{
		  top_present_tree->Fill();
		}
	      else
		{
		  // lep_vect.SetPtEtaPhiE(lep.obj.pt(), lep.obj.eta(), lep.obj.phi(), lep.obj.E());
		  // bjet_lep_vect = bjet_vect+lep_vect;
		  // bjet_lep_dr_var = bjet_vect.DeltaR( lep_vect );
		  // bjet_csv_var = jet.csv;
		  // bjet_lep_mass_var = bjet_lep_vect.M();
		  // bjet_lep_pt_var = bjet_lep_vect.Pt();
		  // bjet_lep_ptratio_var = bjet_lep_vect.Pt()/(lep.obj.pt()+jet.obj.pt());
		  // double mva_value = TMVAReader_lepTop_->EvaluateMVA( "BDTG method" );	  
		  
		  // if (mva_value > best_mva_value)
		  //   {
		  //     best_mva_value = mva_value;
		  //     bJet_intree = jet;
		  //     lep_vect_intree.SetPtEtaPhiE(lep.obj.pt(), lep.obj.eta(), lep.obj.phi(), lep.obj.E());
		  //     bjet_lep_vect_intree = bjet_vect_intree+lep_vect_intree;
		  //     bjet_lep_dR_intree = bjet_vect_intree.DeltaR( lep_vect_intree );
		  //     isNearestLepton_intree = ( min_dR == bjet_lep_dR_intree );
		  //     isHighestLepton_intree = ( lep.obj.pt() > (*tight_leptons_intree)[tight_leptons_intree->size()-1].obj.pt() );
		  //     deltaPt_intree = ( lep.obj.pt() - (*tight_leptons_intree)[tight_leptons_intree->size()-1].obj.pt() );		      
		  //   }
		  top_absent_tree->Fill();
		}
	      lep_count +=1;
	    }
	}

      
      //      top_absent_tree->Fill();

      
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

  TChain *tth_chain = loadFiles("ttH");
  run_it(tth_chain,"ttH_lepTop_BDTtraining.root");

}
