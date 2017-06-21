//Charlie Mueller 7/20/2016
#include <iostream>
#include <cmath>
#include <vector>
#include "TH1.h"
#include "TChain.h"
#include "TSystem.h"
#include "TString.h"
#include "TH1D.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "selection.h"
#include "loadSamples.h"
#include "treeTools.h"
#include "ScaleFactorApplicator.h"
//#include "GenParticleHelper.h"
#include "CSVReweight.h"
#include "Fertilizer.h"
//for signal extraction piece
#include "ttH-13TeVMultiLeptons/TemplateMakers/test/eventReconstructor_factorized.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/test/hTaggerBDT.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/test/signalExtractionTreeMaker.h"


/////////////////////////////////////////
///
/// usage: root -l runChain.C+
///
/////////////////////////////////////////
class EventSelector
{
 private:
  TChain *chain;
  FileLoader myLoader;
  
  double mcwgt_intree = -999.;
  int eventnum_intree = -999;  
  int lumiBlock_intree = -999;
  int runNumber_intree = -999;
  
  std::vector<std::string> *passTrigger_intree=0;
  vector<ttH::Electron> *preselected_electrons_intree=0;
  vector<ttH::Muon> *preselected_muons_intree=0;
  vector<ttH::Lepton> *preselected_leptons_intree=0;
  vector<ttH::Jet> *preselected_jets_intree=0;
  vector<ttH::Jet> *preselected_jets_jecUp_intree=0;
  vector<ttH::Jet> *preselected_jets_jecDown_intree=0;
  vector<ttH::MET> *met_intree=0;
  vector<ttH::Lepton> *fakeable_leptons_intree=0;
  vector<ttH::Muon> *fakeable_muons_intree=0;
  vector<ttH::Electron> *fakeable_electrons_intree=0;
  vector<ttH::Lepton> *tight_leptons_intree=0;
  vector<ttH::Electron> *tight_electrons_intree=0;
  vector<ttH::Muon> *tight_muons_intree=0;
  vector<ttH::GenParticle> *pruned_genParticles_intree=0;
  vector<ttH::Tau> *preselected_taus_intree=0;
  vector<ttH::Tau> *selected_taus_intree=0;

  void select(TString selection, TTree *tree, vector<ttH::Jet> *jet_collection, CSVReweight& csvReweighter_, Fertilizer& fertilizer_, LeptonSF& lepSFs_, signalExtractionTreeMaker& sigExtractionMaker_, eventReconstructor& bdtReconstructor_, hTagger& higgsJetTagger_)
  {
    bool passes = false;
    vector<ttH::Lepton> *lep_collection=0;
    
    if ( selection=="2lss_sr" )
      {
	passes =  pass2lss(
			   *tight_electrons_intree,
			   *fakeable_electrons_intree,
			   *preselected_electrons_intree,
			   *tight_muons_intree,
			   *fakeable_muons_intree,
			   *preselected_muons_intree,
			   *jet_collection,
			   *met_intree
			   );
	lep_collection = tight_leptons_intree;
      }
    else if (selection=="2lss_lepMVA_ar")
      {
	passes = pass2lss_lepMVA_AR(	  
				    *tight_electrons_intree,
				    *fakeable_electrons_intree,
				    *preselected_electrons_intree,
				    *tight_muons_intree,
				    *fakeable_muons_intree,
				    *preselected_muons_intree,
				    *jet_collection,
				    *met_intree
					  ); 
	lep_collection = fakeable_leptons_intree;
      }
    else if (selection=="2los_ar")
      {
	passes = pass2los(
			  *tight_electrons_intree,
			  *fakeable_electrons_intree,
			  *preselected_electrons_intree,
			  *tight_muons_intree,
			  *fakeable_muons_intree,
			  *preselected_muons_intree,
			  *jet_collection,
			  *met_intree
			  );
	lep_collection = tight_leptons_intree;
      }
    else if (selection=="3l_sr")
      {
	passes = pass3l(
			*tight_electrons_intree,
			*fakeable_electrons_intree,
			*preselected_electrons_intree,
			*tight_muons_intree,
			*fakeable_muons_intree,
			*preselected_muons_intree,
			*jet_collection,
			*met_intree
			);
	lep_collection = tight_leptons_intree;
      }
    else if (selection=="3l_lepMVA_ar")
      {
	passes = pass3l_lepMVA_AR(
				  *tight_electrons_intree,
				  *fakeable_electrons_intree,
				  *preselected_electrons_intree,
				  *tight_muons_intree,
				  *fakeable_muons_intree,
				  *preselected_muons_intree,
				  *jet_collection,
				  *met_intree
				  );
	lep_collection = fakeable_leptons_intree;
      }
    else if (selection=="2lss_training_loose")
      {
	passes = pass2lss_bdtTraining(
				      *preselected_electrons_intree,
				      *preselected_muons_intree,
				      *jet_collection);
	lep_collection = preselected_leptons_intree;
      }
    else if (selection=="2lss_training_fo")
      {
	passes = pass2lss_bdtTraining(
				      *fakeable_electrons_intree,
				      *fakeable_muons_intree,
				      *jet_collection);
	lep_collection = fakeable_leptons_intree;
      }
    
    bool passes_trig = passesTrigger(*passTrigger_intree, *lep_collection);
    if ( passes && passes_trig)
      {	  
	fertilizer_.growTreeBranches(*lep_collection,*jet_collection,*preselected_leptons_intree,*met_intree);
	lepSFs_.addTriggerSF(lep_collection);
	lepSFs_.addLeptonSF(lep_collection);
	csvReweighter_.applySFs(*jet_collection);
	
	//only for gen-matching studies//
	//myGenParticleHelper.clear();
	//myGenParticleHelper.matchReco2Gen(*lep_collection, jet_collection, *pruned_genParticles_intree);

	//////////////////////////////
	///
	/// apply hadtop jet removal for higgs tagger:
	///
	//////////////////////////////

	bdtReconstructor_.initialize(jet_collection, lep_collection, (*met_intree)[0]);	
	
	vector<ttH::Jet> jets_for_higgsTagger;
	for (const auto & jet : *jet_collection)
	  {
	    if (jet.obj.pt() == bdtReconstructor_.b_from_hadtop_bdt_intree->obj.pt()) continue;
	    else if (jet.obj.pt() == bdtReconstructor_.q1_from_hadtop_bdt_intree->obj.pt()) continue;
	    else if (jet.obj.pt() == bdtReconstructor_.q2_from_hadtop_bdt_intree->obj.pt()) continue;
	    else jets_for_higgsTagger.push_back(jet);
	  }	  
	higgsJetTagger_.initialize(&jets_for_higgsTagger, lep_collection, (*met_intree)[0]);
	sigExtractionMaker_.initialize(jet_collection, lep_collection, (*met_intree)[0], bdtReconstructor_, higgsJetTagger_);
	
	tree->Fill();
      }
  }
  

 public:
  EventSelector(TString sample_name, TString selection, TString output_dir, int job_no, bool batch_run)
    {

      if (batch_run)
	{
	  myLoader.loadFiles(sample_name, job_no);
	  chain = myLoader.chain;
	}
      else
	{
	  TFile* file = new TFile("/hadoop/store/user/muell149/lobster_test_may22_Moriond17/ttH_nonbb_powheg/output_tree_38039.root","READONLY");
	  // TTree *chain = (TTree*)file->Get("ss2l_tree");  
	  chain = (TChain*)file->Get("OSTwoLepAna/summaryTree");  
	}

      TString postfix = selection+"_tree";
      TString output_file = output_dir + sample_name + postfix + ".root";
      if (job_no != -1) output_file = output_dir + sample_name + postfix + std::to_string(job_no)+".root";
      TFile *outputfile = new TFile(output_file, "RECREATE");
      
      int chainentries = chain->GetEntries();   
      int last_entry = chainentries;
      int first_entry = 0;
      
      cout << "job_no: " << job_no << endl;
      cout << "chainentries: " << chainentries << endl;
      cout << "first entry: " << first_entry << endl;
      cout << "last entry: " << last_entry << endl;
      
      chain->SetBranchAddress("mcwgt", &mcwgt_intree);
      chain->SetBranchAddress("eventnum", &eventnum_intree);
      chain->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
      chain->SetBranchAddress("preselected_muons", &preselected_muons_intree);
      chain->SetBranchAddress("preselected_leptons", &preselected_leptons_intree);
      chain->SetBranchAddress("preselected_jets", &preselected_jets_intree);
      chain->SetBranchAddress("preselected_jets_JECup", &preselected_jets_jecUp_intree);
      chain->SetBranchAddress("preselected_jets_JECdown", &preselected_jets_jecDown_intree);
      chain->SetBranchAddress("fakeable_leptons", &fakeable_leptons_intree);
      chain->SetBranchAddress("fakeable_muons", &fakeable_muons_intree);
      chain->SetBranchAddress("fakeable_electrons", &fakeable_electrons_intree);
      chain->SetBranchAddress("tight_leptons", &tight_leptons_intree);
      chain->SetBranchAddress("tight_electrons", &tight_electrons_intree);
      chain->SetBranchAddress("tight_muons", &tight_muons_intree);    
      chain->SetBranchAddress("preselected_taus", &preselected_taus_intree);
      chain->SetBranchAddress("selected_taus", &selected_taus_intree);
      chain->SetBranchAddress("met", &met_intree);
      chain->SetBranchAddress("pruned_genParticles", &pruned_genParticles_intree);
      chain->SetBranchAddress("passTrigger", &passTrigger_intree);

      CSVReweight csvReweighter;
      CSVReweight csvReweighter_jes_up;
      CSVReweight csvReweighter_jes_down;
      Fertilizer fertilizer;
      Fertilizer fertilizer_jes_up;
      Fertilizer fertilizer_jes_down;
      LeptonSF lepSFs;
      LeptonSF lepSFs_jes_up;
      LeptonSF lepSFs_jes_down;
      //GenParticleHelper myGenParticleHelper;
      eventReconstructor bdtReconstructor;
      eventReconstructor bdtReconstructor_jes_up;
      eventReconstructor bdtReconstructor_jes_down;
      hTagger higgsJetTagger;
      hTagger higgsJetTagger_jes_up;
      hTagger higgsJetTagger_jes_down;

      outputfile->cd();
      if (batch_run && (job_no == -1 || job_no == 0))
	{
	  TH1D* event_hist = myLoader.hist_sum;
	  event_hist->Write();
	  delete event_hist;
	}    
        
      TTree *ss2l_tree = (TTree*)chain->CloneTree(0);
      ss2l_tree->SetName("ss2l_tree");
      ss2l_tree->SetDirectory(outputfile);
      bdtReconstructor.initializeTree(ss2l_tree);
      higgsJetTagger.initializeTree(ss2l_tree);
      signalExtractionTreeMaker mySigExtrTreeMaker(ss2l_tree);
      csvReweighter.initializeTree(ss2l_tree);
      fertilizer.initializeTree(ss2l_tree);
      lepSFs.initializeTree(ss2l_tree);
      //myGenParticleHelper.initializeTree(ss2l_tree);

      TTree *ss2l_tree_jes_up = (TTree*)chain->CloneTree(0);
      ss2l_tree_jes_up->SetName("ss2l_tree_jes_up");
      ss2l_tree_jes_up->SetDirectory(outputfile);
      bdtReconstructor_jes_up.initializeTree(ss2l_tree_jes_up);
      higgsJetTagger_jes_up.initializeTree(ss2l_tree_jes_up);
      signalExtractionTreeMaker mySigExtrTreeMaker_jes_up(ss2l_tree_jes_up);
      csvReweighter_jes_up.initializeTree(ss2l_tree_jes_up);
      fertilizer_jes_up.initializeTree(ss2l_tree_jes_up);
      lepSFs_jes_up.initializeTree(ss2l_tree_jes_up);

      TTree *ss2l_tree_jes_down = (TTree*)chain->CloneTree(0);
      ss2l_tree_jes_down->SetName("ss2l_tree_jes_down");
      ss2l_tree_jes_down->SetDirectory(outputfile);
      bdtReconstructor_jes_down.initializeTree(ss2l_tree_jes_down);
      higgsJetTagger_jes_down.initializeTree(ss2l_tree_jes_down);
      signalExtractionTreeMaker mySigExtrTreeMaker_jes_down(ss2l_tree_jes_down);
      csvReweighter_jes_down.initializeTree(ss2l_tree_jes_down);
      fertilizer_jes_down.initializeTree(ss2l_tree_jes_down);
      lepSFs_jes_down.initializeTree(ss2l_tree_jes_down);
      
      Int_t cachesize = 250000000;   //500 MBytes
      chain->SetCacheSize(cachesize);
      
      double starttime = get_wall_time();
      for (int i=first_entry; i<=last_entry; i++)
	{
	  
	  clock_t startTime = clock();
	  chain->GetEntry(i);
	  printProgress(i,last_entry);
	  
	  //if (eventnum_intree != 1658366) continue;
	  
	  //////////////////////////
	  ////
	  //// selection, vetos etc
	  ////
	  //////////////////////////
	  
	  if (selected_taus_intree->size() > 0) continue; //veto any and all taus
	  
	  //////////////////////////
	  ////
	  //// normal selection
	  ////
	  //////////////////////////
	  
	  select(selection, ss2l_tree, preselected_jets_intree, csvReweighter, fertilizer, lepSFs,mySigExtrTreeMaker,bdtReconstructor,higgsJetTagger);


	  // if (sample_name != "fakes" and sample_name != "flips" and sample_name != "data")
	  //   {
	  //     select(selection, ss2l_tree_jes_up, preselected_jets_jecUp_intree, csvReweighter_jes_up, fertilizer_jes_up, lepSFs_jes_up,mySigExtrTreeMaker_jes_up,bdtReconstructor_jes_up,higgsJetTagger_jes_up);
	  //     select(selection, ss2l_tree_jes_down, preselected_jets_jecDown_intree, csvReweighter_jes_down, fertilizer_jes_down, lepSFs_jes_down,mySigExtrTreeMaker_jes_down,bdtReconstructor_jes_down,higgsJetTagger_jes_down);
	  //   }
	  
	}
      
      
      double endtime = get_wall_time();
      cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
      if ( (last_entry - first_entry) >0) cout << "an average of " << (endtime - starttime) / (last_entry - first_entry) << " per event." << endl;
      
      ss2l_tree->Write();
      if (sample_name != "fakes" and sample_name != "flips" and sample_name != "data")
	{
	  ss2l_tree_jes_up->Write();      
	  ss2l_tree_jes_down->Write();
	}
      gDirectory->Purge();
      outputfile->Write();
      outputfile->Close();    
    }

  virtual ~EventSelector(){};
};

void runChain(TString sample="ttZ_M10", TString selection="2lss_sr", int job_no=-1)
{
  TString output_dir;
  bool batch_run = true; //switch for batch vs. local commandline running

  if (batch_run) output_dir = "/scratch365/cmuelle2/extraction_trees/june14_test/";
  else output_dir = "";
  //  else output_dir = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_26_patch1/src/ttH-13TeVMultiLeptons/TemplateMakers/test/";

  //////////// available selections //////////////
  //EventSelector run_it0(sample, selection, output_dir, job_no, batch_run);
  EventSelector run_it1(sample, "2lss_sr", output_dir, job_no, batch_run);  

  if (sample == "data")
    {
      EventSelector run_it2(sample, "2lss_lepMVA_ar", output_dir, job_no, batch_run);
      EventSelector run_it3(sample, "2los_ar", output_dir, job_no, batch_run);
    }
  

  //EventSelector run_it4(sample, "3l_sr", output_dir, job_no, batch_run);
  //EventSelector run_it5(sample, "3l_lepMVA_ar", output_dir, job_no, batch_run);
  //EventSelector run_it6(sample, "2lss_training_loose", output_dir, job_no, batch_run);
  //EventSelector run_it7(sample, "2lss_training_fo", output_dir, job_no, batch_run);
  //EventSelector run_it8(sample, "4l_sr", output_dir, job_no, batch_run);
  
}


//  LocalWords:  fakeable
