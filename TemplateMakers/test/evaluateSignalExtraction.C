//Charlie Mueller 4/7/2016
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
#include "DataFormats/Math/interface/deltaR.h"
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
/// usage: root -l evaluateSignalExtraction.C+
///
/////////////////////////////////////////


void run_it(TChain* chain, TFile* output_file)
{
  Float_t max_lep_eta_var;
  Float_t njets_var;
  Float_t dR_l1_j_var;
  Float_t dR_l2_j_var;
  Float_t MT_l1_met_var;
  Float_t met_var;
  Float_t avg_dr_jets_var;
  Float_t reco_score_var;
  Float_t lep1_pt_var;
  Float_t lep2_pt_var;

  Float_t csv1_branch;
  Float_t csv2_branch;

  Float_t spec0_var;
  Float_t spec1_var;
  Float_t spec2_var;

  TMVA::Reader* TMVAReader_ttbar_ = new TMVA::Reader( "!Color:!Silent" );
  TMVAReader_ttbar_->AddVariable( "max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))", &max_lep_eta_var );
  TMVAReader_ttbar_->AddVariable( "nJet25_Recl", &njets_var );
  TMVAReader_ttbar_->AddVariable( "mindr_lep1_jet", &dR_l1_j_var );
  TMVAReader_ttbar_->AddVariable( "mindr_lep2_jet", &dR_l2_j_var );
  TMVAReader_ttbar_->AddVariable( "min(met_pt,400)", &met_var );
  TMVAReader_ttbar_->AddVariable( "avg_dr_jet", &avg_dr_jets_var );
  TMVAReader_ttbar_->AddVariable( "MT_met_lep1", &MT_l1_met_var );
  TMVAReader_ttbar_->AddSpectator( "iF_Recl[0]", &spec0_var );
  TMVAReader_ttbar_->AddSpectator( "iF_Recl[1]", &spec1_var );
  TMVAReader_ttbar_->AddSpectator( "iF_Recl[2]", &spec2_var );
  //  TString ttbar_weights = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/classifiers/weights/TMVAClassification_BDTG.weights_ttbar_extraction_original_v2.xml";
  TString ttbar_weights = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/classifiers/weights/2lss_ttbar_BDTG.weights.xml";
  TMVAReader_ttbar_->BookMVA("BDTG method", ttbar_weights);

  // TMVAReader_ttbar_->AddVariable( "max_Lep_eta", &max_lep_eta_var );
  // TMVAReader_ttbar_->AddVariable( "numJets_float", &njets_var );
  // TMVAReader_ttbar_->AddVariable( "mindr_lep1_jet", &dR_l1_j_var );
  // TMVAReader_ttbar_->AddVariable( "mindr_lep2_jet", &dR_l2_j_var );
  // TMVAReader_ttbar_->AddVariable( "MT_met_lep1", &MT_l1_met_var );
  // TMVAReader_ttbar_->AddVariable( "met_double", &met_var );
  // TMVAReader_ttbar_->AddVariable( "avg_dr_jet", &avg_dr_jets_var );
  // TMVAReader_ttbar_->AddVariable( "csv2", &csv2_branch );
  // TString ttbar_weights = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/weights/TMVAClassification_BDTG.weights_csv2.xml";
  // TMVAReader_ttbar_->BookMVA("BDTG method", ttbar_weights);

  TMVA::Reader* TMVAReader_ttbar_recoBdt_ = new TMVA::Reader( "!Color:!Silent" );
  TMVAReader_ttbar_recoBdt_->AddVariable( "max_Lep_eta", &max_lep_eta_var );
  TMVAReader_ttbar_recoBdt_->AddVariable( "numJets_float", &njets_var );
  TMVAReader_ttbar_recoBdt_->AddVariable( "mindr_lep1_jet", &dR_l1_j_var );
  TMVAReader_ttbar_recoBdt_->AddVariable( "mindr_lep2_jet", &dR_l2_j_var );
  TMVAReader_ttbar_recoBdt_->AddVariable( "MT_met_lep1", &MT_l1_met_var );
  TMVAReader_ttbar_recoBdt_->AddVariable( "met_double", &met_var );
  TMVAReader_ttbar_recoBdt_->AddVariable( "avg_dr_jet", &avg_dr_jets_var );
  TMVAReader_ttbar_recoBdt_->AddVariable( "reco_score", &reco_score_var );
  TString ttbar_recoBdt_weights = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/weights/TMVAClassification_BDTG.weights_recoBdt.xml";
  TMVAReader_ttbar_recoBdt_->BookMVA("BDTG method", ttbar_recoBdt_weights);

  TMVA::Reader* TMVAReader_ttbar_recoBdt_bLoose_ = new TMVA::Reader( "!Color:!Silent" );
  TMVAReader_ttbar_recoBdt_bLoose_->AddVariable( "max_Lep_eta", &max_lep_eta_var );
  TMVAReader_ttbar_recoBdt_bLoose_->AddVariable( "numJets_float", &njets_var );
  TMVAReader_ttbar_recoBdt_bLoose_->AddVariable( "mindr_lep1_jet", &dR_l1_j_var );
  TMVAReader_ttbar_recoBdt_bLoose_->AddVariable( "mindr_lep2_jet", &dR_l2_j_var );
  TMVAReader_ttbar_recoBdt_bLoose_->AddVariable( "MT_met_lep1", &MT_l1_met_var );
  TMVAReader_ttbar_recoBdt_bLoose_->AddVariable( "met_double", &met_var );
  TMVAReader_ttbar_recoBdt_bLoose_->AddVariable( "avg_dr_jet", &avg_dr_jets_var );
  TMVAReader_ttbar_recoBdt_bLoose_->AddVariable( "reco_score", &reco_score_var );
  TString ttbar_recoBdt_bLoose_weights = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/weights/TMVAClassification_BDTG.weights_recoBdt_bloose.xml";
  TMVAReader_ttbar_recoBdt_bLoose_->BookMVA("BDTG method", ttbar_recoBdt_bLoose_weights);

  TMVA::Reader* TMVAReader_ttbar_recoBdt_bTight_ = new TMVA::Reader( "!Color:!Silent" );
  TMVAReader_ttbar_recoBdt_bTight_->AddVariable( "max_Lep_eta", &max_lep_eta_var );
  TMVAReader_ttbar_recoBdt_bTight_->AddVariable( "numJets_float", &njets_var );
  TMVAReader_ttbar_recoBdt_bTight_->AddVariable( "mindr_lep1_jet", &dR_l1_j_var );
  TMVAReader_ttbar_recoBdt_bTight_->AddVariable( "mindr_lep2_jet", &dR_l2_j_var );
  TMVAReader_ttbar_recoBdt_bTight_->AddVariable( "MT_met_lep1", &MT_l1_met_var );
  TMVAReader_ttbar_recoBdt_bTight_->AddVariable( "met_double", &met_var );
  TMVAReader_ttbar_recoBdt_bTight_->AddVariable( "avg_dr_jet", &avg_dr_jets_var );
  TMVAReader_ttbar_recoBdt_bTight_->AddVariable( "reco_score", &reco_score_var );
  TString ttbar_recoBdt_bTight_weights = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/weights/TMVAClassification_BDTG.weights_recoBdt_btight.xml";
  TMVAReader_ttbar_recoBdt_bTight_->BookMVA("BDTG method", ttbar_recoBdt_bTight_weights);

  TMVA::Reader* TMVAReader_ttV_ = new TMVA::Reader( "!Color:!Silent" );
  TMVAReader_ttV_->AddVariable( "max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))", &max_lep_eta_var );
  TMVAReader_ttV_->AddVariable( "MT_met_lep1", &MT_l1_met_var );
  TMVAReader_ttV_->AddVariable( "nJet25_Recl", &njets_var );
  TMVAReader_ttV_->AddVariable( "mindr_lep1_jet", &dR_l1_j_var );
  TMVAReader_ttV_->AddVariable( "mindr_lep2_jet", &dR_l2_j_var );
  TMVAReader_ttV_->AddVariable( "LepGood_conePt[iF_Recl[0]]", &lep1_pt_var );
  TMVAReader_ttV_->AddVariable( "LepGood_conePt[iF_Recl[1]]", &lep2_pt_var );
  TMVAReader_ttV_->AddSpectator( "iF_Recl[0]", &spec0_var );
  TMVAReader_ttV_->AddSpectator( "iF_Recl[1]", &spec1_var );
  TMVAReader_ttV_->AddSpectator( "iF_Recl[2]", &spec2_var );
  TString ttV_weights = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/simpleweights/reconstruction_bdt_weights/classifiers/weights/2lss_ttV_BDTG.weights.xml";
  TMVAReader_ttV_->BookMVA("BDTG method", ttV_weights);

  int chainentries = chain->GetEntries();   
  cout << "# events in tree: "<< chainentries << endl;  
  
  double mcwgt_intree = -999.;
  int eventnum_intree = -999;
  vector<ttH::Jet> *preselected_jets_intree=0;
  vector<ttH::Lepton> *tight_leptons_intree=0;
  vector<ttH::Tau> *selected_taus_intree=0;
  vector<ttH::MET> *met_intree=0;
  double reco_score_intree=-999.;

  chain->SetBranchStatus("*",0);
  chain->SetBranchStatus("eventnum",1);
  chain->SetBranchStatus("mcwgt",1);
  chain->SetBranchStatus("preselected_jets.*",1);
  chain->SetBranchStatus("selected_taus.*",1);
  chain->SetBranchStatus("tightMvaBased_leptons.*",1);
  chain->SetBranchStatus("met.*",1);
  chain->SetBranchStatus("reco_score",1);

  chain->SetBranchAddress("eventnum", &eventnum_intree);
  chain->SetBranchAddress("mcwgt", &mcwgt_intree);
  chain->SetBranchAddress("preselected_jets", &preselected_jets_intree);
  chain->SetBranchAddress("selected_taus", &selected_taus_intree);
  chain->SetBranchAddress("tightMvaBased_leptons", &tight_leptons_intree);
  chain->SetBranchAddress("met", &met_intree);
  chain->SetBranchAddress("reco_score", &reco_score_intree);

  double mcwgt_branch=-999.;
  double max_lep_eta_branch=-999.;
  double njets_branch=-999.;
  double dR_l1_j_branch=-999.;
  double dR_l2_j_branch=-999.;
  double met_branch=-999.;
  double avg_dr_jets_branch=-999.;
  double mt_lep1_met_branch=-999.;
  double l1_pt_branch=-999.;
  double l2_pt_branch=-999.;
  double reco_score_branch=-999.;
  double vs_ttbar_score=-999.;
  double vs_ttbar_bdtReco_score=-999.;
  double vs_ttv_score=-999.;
  bool isBtight_branch=false;
  bool isPositive_branch=false;
  bool isTau_branch=false;
  TString flavor_branch = "null";

  //  TTree *extraction_tree = (TTree*)chain->CloneTree(0);
  TTree *extraction_tree = new TTree("extraction_tree_recobdt_v1","tree containing signal extraction output");
  extraction_tree->Branch("mcwgt", &mcwgt_branch);
  extraction_tree->Branch("max_lep_eta", &max_lep_eta_branch);
  extraction_tree->Branch("nJets", &njets_branch);
  extraction_tree->Branch("dR_l1_j", &dR_l1_j_branch);
  extraction_tree->Branch("dR_l2_j", &dR_l2_j_branch);
  extraction_tree->Branch("met", &met_branch);
  extraction_tree->Branch("avg_dR_jets", &avg_dr_jets_branch);
  extraction_tree->Branch("MT_l1_met", &mt_lep1_met_branch);
  extraction_tree->Branch("l1_pt", &l1_pt_branch);
  extraction_tree->Branch("l2_pt", &l2_pt_branch);
  extraction_tree->Branch("reco_score", &reco_score_branch);
  extraction_tree->Branch("vs_ttbar_bdt_score", &vs_ttbar_score);
  extraction_tree->Branch("vs_ttbar_bdtReco_bdt_score", &vs_ttbar_bdtReco_score);
  extraction_tree->Branch("vs_ttv_bdt_score", &vs_ttv_score);
  extraction_tree->Branch("bTight_category", &isBtight_branch);
  extraction_tree->Branch("posCharge_category", &isPositive_branch);
  extraction_tree->Branch("tau_category", &isTau_branch);
  extraction_tree->Branch("flavor_category", &flavor_branch);

  Int_t cachesize = 250000000;   //250 MBytes
  chain->SetCacheSize(cachesize);
  chain->SetCacheLearnEntries(20);
  
  double starttime = get_wall_time();
  for (int i=0; i<chainentries; i++)
    {

      printProgress(i,chainentries);
      chain->GetEntry(i);

      auto lepton_collection_to_use = tight_leptons_intree;
      //      auto lepton_collection_to_use = loose_leptons_intree;
      
      //////////////////////////
      ////
      //// calculate new vars
      ////
      //////////////////////////


      ////////////////////////
      //
      // evaluate_categories
      //
      ////////////////////////
      double tight_wp = 0.8;
      int num_tight = 0;
      for (const auto & jet : *preselected_jets_intree)	if (jet.csv >= tight_wp) num_tight +=1; 

      if ( num_tight > 1 ) isBtight_branch = true;
      else isBtight_branch = false;

      if ((*lepton_collection_to_use)[0].charge > 0) isPositive_branch = true;
      else isPositive_branch = false;
      
      if ( selected_taus_intree->size() > 0) isTau_branch = true;
      else isTau_branch = false;
      
      if (abs((*lepton_collection_to_use)[0].pdgID) == 11 && abs((*lepton_collection_to_use)[1].pdgID) == 11) flavor_branch = "ee";
      else if (abs((*lepton_collection_to_use)[0].pdgID) == 13 && abs((*lepton_collection_to_use)[1].pdgID) == 13) flavor_branch = "mm";
      else flavor_branch = "em";

      ////////////////////////
      //
      // evaluate mva scores
      //
      ////////////////////////


      // max eta
      max_lep_eta_var = -1.;
      for (const auto & lep: *lepton_collection_to_use)	if (abs(lep.obj.eta()) > max_lep_eta_var) max_lep_eta_var = abs(lep.obj.eta());

      // njets
      njets_var = preselected_jets_intree->size();


      //csv
      auto csv_sorted_jets = *preselected_jets_intree;
      std::sort(csv_sorted_jets.begin(), csv_sorted_jets.end(), [] (ttH::Jet a, ttH::Jet b) { return a.csv > b.csv;});
      csv1_branch = csv_sorted_jets[0].csv;
      csv2_branch = max( csv_sorted_jets[1].csv, 0.);

      // find highest pt leptons
      ttH::Lepton lep1;
      ttH::Lepton lep2;
      if ((*lepton_collection_to_use)[0].obj.pt() > (*lepton_collection_to_use)[1].obj.pt())
	{
	  lep1 = (*lepton_collection_to_use)[0];
	  lep2 = (*lepton_collection_to_use)[1];
	}
      else
	{
	  lep1 = (*lepton_collection_to_use)[1];
	  lep2 = (*lepton_collection_to_use)[0];
	}
      lep1_pt_var = lep1.obj.pt();
      lep2_pt_var = lep2.obj.pt();

      ttH::Jet lep1_closest_jet = getClosestJet(*preselected_jets_intree, lep1);
      ttH::Jet lep2_closest_jet = getClosestJet(*preselected_jets_intree, lep2);
      dR_l1_j_var = getDeltaR(lep1_closest_jet, lep1);
      dR_l2_j_var = getDeltaR(lep2_closest_jet, lep2);

      // met
      met_var = min( (*met_intree)[0].obj.Pt(), 400. );

      TLorentzVector met_tlv = setTlv( (*met_intree)[0] );
      TLorentzVector lep1_t_tlv = setTlv( lep1 );
      lep1_t_tlv.SetPxPyPzE(lep1_t_tlv.Px(), lep1_t_tlv.Py(), 0., lep1_t_tlv.Pt());
      TLorentzVector lep1_met_t_tlv = met_tlv + lep1_t_tlv;
      MT_l1_met_var = lep1_met_t_tlv.M();

      //calculate avg dr jets
      int jet1_counter = 0;
      double dr_sum = 0.;
      int dr_denom = 0;
      for (const auto & jet1 : *preselected_jets_intree)
	{
	  int jet2_counter = -1;
	  for (const auto & jet2 : *preselected_jets_intree)
	    {
	      jet2_counter +=1;
	      if ( jet2_counter <= jet1_counter ) continue;
	      double delta_r = getDeltaR(jet1, jet2);
	      dr_sum += delta_r;
	      dr_denom +=1;
	    }
	  jet1_counter +=1;
	}
      
      avg_dr_jets_var = dr_sum/double(dr_denom);

      
      max_lep_eta_branch = max_lep_eta_var;
      njets_branch = njets_var;
      dR_l1_j_branch = dR_l1_j_var;
      dR_l2_j_branch = dR_l2_j_var;
      met_branch = met_var;
      avg_dr_jets_branch = avg_dr_jets_var;
      mt_lep1_met_branch = MT_l1_met_var;
      l1_pt_branch = lep1_pt_var;
      l2_pt_branch = lep2_pt_var;

      reco_score_var = reco_score_intree;
      reco_score_branch = reco_score_var;


      vs_ttbar_score = TMVAReader_ttbar_->EvaluateMVA( "BDTG method" );
      //if ( isBtight_branch ) vs_ttbar_bdtReco_score = TMVAReader_ttbar_recoBdt_bTight_->EvaluateMVA( "BDTG method" );
      if ( isBtight_branch ) vs_ttbar_bdtReco_score = TMVAReader_ttbar_recoBdt_->EvaluateMVA( "BDTG method" );
      else  vs_ttbar_bdtReco_score = TMVAReader_ttbar_recoBdt_bLoose_->EvaluateMVA( "BDTG method" );

      vs_ttv_score = TMVAReader_ttV_->EvaluateMVA( "BDTG method" );

      mcwgt_branch = mcwgt_intree;      
      extraction_tree->Fill();      
    }
  
  
  double endtime = get_wall_time();
  cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
  if (chainentries>0) cout << "an average of " << (endtime - starttime) / chainentries << " per event." << endl;
  
  extraction_tree->Write("",TObject::kOverwrite);
  output_file->Close();  
}

void evaluateSignalExtraction(void)
{

  vector<TString> samples;  
  // samples.push_back("/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/tth_aMC_old_2lss.root");
  // samples.push_back("/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/ttbar_semiLep_powheg_2lss.root");
  // samples.push_back("/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/ttW_aMCatNLO_2lss.root");
  // samples.push_back("/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/ttZ_aMCatNLO_2lss.root");
  // samples.push_back("/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/ttbar_diLep_madgraph_2lss.root");
  samples.push_back("/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/WWZ_rares_2lss.root");
  samples.push_back("/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/WW_diboson_2lss.root");
  samples.push_back("/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/WW_doublescatering_rares_2lss.root");
  samples.push_back("/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/WWqq_rares_2lss.root");
  samples.push_back("/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/WZZ_rares_2lss.root");
  samples.push_back("/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/WZ_diboson_2lss.root");
  samples.push_back("/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/ZZZ_rare_2lss.root");
  samples.push_back("/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/ZZ_diboson_2lss.root");
  samples.push_back("/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/tqZ_2lss.root");
  samples.push_back("/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_14/src/ttH-13TeVMultiLeptons/TemplateMakers/test/reco_bdt/output/tttt_2lss.root");

  for (const auto & sample : samples)
    {
      TFile *io_file = new TFile(sample, "UPDATE");
      TChain *chain = new TChain("ss2l_tree");
      chain->Add(sample);
      run_it(chain, io_file);     
    }

}
