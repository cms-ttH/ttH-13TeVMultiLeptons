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

/////////////////////////////////////////
///
/// usage: root -l makeSelectionTree.C+
///
/////////////////////////////////////////

void run_it(TString sample_name, TString selection, TString output_dir, int job_no, bool batch_run)
{
  TString postfix = selection+"_tree";
  TString output_file = output_dir + sample_name + postfix + ".root";
  if (job_no != -1) output_file = output_dir + sample_name + postfix + std::to_string(job_no)+".root";

  TChain *chain;
  FileLoader myLoader;
  if (batch_run)
    {
      myLoader.loadFiles(sample_name, job_no);
      chain = myLoader.chain;
    }
  else
    {
      TFile* file = new TFile("output_M17_sync_tree_muonConePt.root","READONLY");
      // TTree *chain = (TTree*)file->Get("ss2l_tree");  
      chain = (TChain*)file->Get("OSTwoLepAna/summaryTree");  
    }

    TFile *outputfile = new TFile(output_file, "RECREATE");

    int chainentries = chain->GetEntries();   
    int last_entry = chainentries;
    int first_entry = 0;
  
    cout << "job_no: " << job_no << endl;
    cout << "chainentries: " << chainentries << endl;
    cout << "first entry: " << first_entry << endl;
    cout << "last entry: " << last_entry << endl;

    double mcwgt_intree = -999.;
    int eventnum_intree = -999;  
    int lumiBlock_intree = -999;
    int runNumber_intree = -999;

    std::vector<std::string> *passTrigger_intree=0;
    vector<ttH::Electron> *preselected_electrons_intree=0;
    vector<ttH::Muon> *preselected_muons_intree=0;
    vector<ttH::Lepton> *preselected_leptons_intree=0;
    vector<ttH::Jet> *preselected_jets_intree=0;
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

    chain->SetBranchAddress("mcwgt", &mcwgt_intree);
    chain->SetBranchAddress("eventnum", &eventnum_intree);
    chain->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
    chain->SetBranchAddress("preselected_muons", &preselected_muons_intree);
    chain->SetBranchAddress("preselected_leptons", &preselected_leptons_intree);
    chain->SetBranchAddress("preselected_jets", &preselected_jets_intree);
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
    Fertilizer fertilizer;
    LeptonSF lepSFs;
    //GenParticleHelper myGenParticleHelper;


    if (batch_run && (job_no == -1 || job_no == 0))
      {
        TH1D* event_hist = myLoader.hist_sum;
	outputfile->cd();
        event_hist->Write();
	delete event_hist;
      }    

    TTree *ss2l_tree = (TTree*)chain->CloneTree(0);
    ss2l_tree->SetName("ss2l_tree");
    ss2l_tree->SetDirectory(outputfile);

    csvReweighter.initializeTree(ss2l_tree);
    fertilizer.initializeTree(ss2l_tree);
    lepSFs.initializeTree(ss2l_tree);
    //myGenParticleHelper.initializeTree(ss2l_tree);

    Int_t cachesize = 250000000;   //500 MBytes
    chain->SetCacheSize(cachesize);

    double starttime = get_wall_time();
    for (int i=first_entry; i<=last_entry; i++) {
      
      clock_t startTime = clock();
      chain->GetEntry(i);
      printProgress(i,last_entry);

      //if (eventnum_intree != 1658366) continue;
      
      //////////////////////////
      ////
      //// selection, vetos etc
      ////
      //////////////////////////
      
      bool passesCommon = passCommon(*preselected_electrons_intree, *preselected_muons_intree, *preselected_jets_intree);
      if (!passesCommon) continue;
      if (selected_taus_intree->size() > 0) continue; //veto any and all taus

      //////////////////////////
      ////
      //// normal selection
      ////
      //////////////////////////

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
			     *preselected_jets_intree,
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
				      *preselected_jets_intree,
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
			    *preselected_jets_intree,
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
			  *preselected_jets_intree,
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
				    *preselected_jets_intree,
				    *met_intree
				    );
	  lep_collection = fakeable_leptons_intree;
	}
      else if (selection=="2lss_training_loose")
	{
	  passes = pass2lss_bdtTraining(
					*preselected_electrons_intree,
					*preselected_muons_intree,
					*preselected_jets_intree);
	  lep_collection = preselected_leptons_intree;
	}
      else if (selection=="2lss_training_fo")
	{
	  passes = pass2lss_bdtTraining(
					*fakeable_electrons_intree,
					*fakeable_muons_intree,
					*preselected_jets_intree);
	  lep_collection = fakeable_leptons_intree;
	}

      bool passes_trig = passesTrigger(*passTrigger_intree, *lep_collection);

      if ( passes && passes_trig)
	{	  

	  fertilizer.growTreeBranches(*lep_collection,*preselected_jets_intree,*preselected_leptons_intree,*met_intree);
	  // lepSFs.addTriggerSF(lep_collection);
	  // lepSFs.addLeptonSF(lep_collection);
	  // csvReweighter.applySFs(*preselected_jets_intree);
	  
	  //only for gen-matching studies//
	  //myGenParticleHelper.clear();
	  //myGenParticleHelper.matchReco2Gen(*lep_collection, *preselected_jets_intree, *pruned_genParticles_intree);
	  
	  ss2l_tree->Fill();
	}
      
    }
    

    double endtime = get_wall_time();
    cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
    if ( (last_entry - first_entry) >0) cout << "an average of " << (endtime - starttime) / (last_entry - first_entry) << " per event." << endl;
    
    outputfile->cd();
    ss2l_tree->Write();
    outputfile->Close();
}

void makeSelectionTree(TString sample="sync", TString selection="2lss_sr", int job_no=-1)
{
  TString output_dir;
  bool batch_run = true; //switch for batch vs. local commandline running

  if (batch_run) output_dir = "/scratch365/cmuelle2/selection_trees/may22_kaitlinRemake/";
  else output_dir = "/afs/crc.nd.edu/user/c/cmuelle2/CMSSW_8_0_26_patch1/src/ttH-13TeVMultiLeptons/TemplateMakers/test/";

  //////////// available selections //////////////
  run_it(sample, selection, output_dir, job_no, batch_run);
  //run_it(sample, "2lss_sr", output_dir, job_no, batch_run);
  //run_it(sample, "2lss_lepMVA_ar", output_dir, job_no, batch_run);
  //run_it(sample, "2los_ar", output_dir, job_no, batch_run);
  // run_it(sample, "3l_sr", output_dir, job_no, batch_run);
  // run_it(sample, "3l_lepMVA_ar", output_dir, job_no, batch_run);
  //run_it(sample, "2lss_training_loose", output_dir, job_no, batch_run);
  // run_it(sample, "2lss_training_fo", output_dir, job_no, batch_run);
  // run_it(sample, "4l_sr", output_dir, job_no, batch_run);
}

