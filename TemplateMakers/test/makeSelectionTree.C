//Charlie Mueller 7/20/2016
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
#include "selection.h"
#include "loadSamples.h"
#include "treeTools.h"
#include "GenParticleHelper.h"
#include "FakeRateEvaluator.h"

/////////////////////////////////////////
///
/// usage: root -l makeSelectionTree.C+
///
/////////////////////////////////////////


void run_it(TString sample_name, TString selection, TString output_file, int job_no)
{
    FileLoader myLoader(sample_name, job_no);
    TChain *chain = myLoader.chain;

    //TFile* file = new TFile("output_tree.root","READONLY");
    //TTree *chain = (TTree*)file->Get("OSTwoLepAna/summaryTree");  

    int chainentries = chain->GetEntries();   
    int last_entry = chainentries;
    int first_entry = 0;
  
    cout << "job_no: " << job_no << endl;
    cout << "chainentries: " << chainentries << endl;
    cout << "first entry: " << first_entry << endl;
    cout << "last entry: " << last_entry << endl;

    double mcwgt_intree = -999.;
    int eventnum_intree = -999;  
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
    //adding these
    vector<ttH::Jet> *bTight_jets_intree=0;  
    vector<ttH::Jet> *bLoose_jets_intree=0;  

    if (sample_name == "data") {
        chain->SetBranchStatus("mcwgt",0);      
    } else {
        chain->SetBranchAddress("mcwgt", &mcwgt_intree);
    }
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
    chain->SetBranchAddress("met", &met_intree);
    chain->SetBranchAddress("pruned_genParticles", &pruned_genParticles_intree);

    FakeRateEvaluator lepFakeRateObject;
  
    TFile *copiedfile = new TFile(output_file, "RECREATE"); //"UPDATE"); // #, 'test' ) // "RECREATE");
    if (job_no == -1 || job_no == 0) {
        TH1D* event_hist = myLoader.hist_sum;
        event_hist->Write();
    }

    TTree *ss2l_tree = (TTree*)chain->CloneTree(0);
    ss2l_tree->SetName("ss2l_tree");
    if (sample_name == "data") ss2l_tree->Branch("mcwgt",&mcwgt_intree);

    GenParticleHelper myGenParticleHelper;
    myGenParticleHelper.initializeTree(ss2l_tree);

    //add new branches
    ss2l_tree->Branch("bTight_jets", &bTight_jets_intree);  
    ss2l_tree->Branch("bLoose_jets", &bLoose_jets_intree);

    Int_t cachesize = 250000000;   //500 MBytes
    //  Int_t cachesize = 1024000000;   //1 GBytes
    chain->SetCacheSize(cachesize);

    double starttime = get_wall_time();
    for (int i=first_entry; i<=last_entry; i++) {
        bTight_jets_intree->clear();
        bLoose_jets_intree->clear();
        for (const auto & jet : *preselected_jets_intree) {
            if (jet.csv >= 0.8 ) {
                bTight_jets_intree->push_back(jet);
            } else if (jet.csv >= 0.46 ) {
                bLoose_jets_intree->push_back(jet);
            }
        }

        printProgress(i,last_entry);

        clock_t startTime = clock();
        chain->GetEntry(i);

        //////////////////////////
        ////
        //// selection, vetos etc
        ////
        //////////////////////////

        bool passesCommon = passCommon(*preselected_electrons_intree, *preselected_muons_intree, *preselected_jets_intree);
        if (!passesCommon) {
            continue;
        }

        if (selection == "analysis") {
            //////////////////////////
            ////
            //// normal selection
            ////
            //////////////////////////

            //bool passes2lss = pass2lss(
            //        *tight_electrons_intree,
            //        *fakeable_electrons_intree,
            //        *preselected_electrons_intree,
            //        *tight_muons_intree,
            //        *fakeable_muons_intree,
            //        *preselected_muons_intree,
            //        *preselected_jets_intree,
            //        *met_intree
            //);

            bool passes2lss_lepMVA_AR = pass2lss_lepMVA_AR(
                    *tight_electrons_intree,
                    *fakeable_electrons_intree,
                    *preselected_electrons_intree,
                    *tight_muons_intree,
                    *fakeable_muons_intree,
                    *preselected_muons_intree,
                    *preselected_jets_intree,
                    *met_intree
            );

            // bool passes2los = pass2los(
            //     *tight_electrons_intree,
            //     *fakeable_electrons_intree,
            //     *preselected_electrons_intree,
            //     *tight_muons_intree,
            //     *fakeable_muons_intree,
            //     *preselected_muons_intree,
            //     *preselected_jets_intree,
            //     *met_intree
            // );

            // bool passes3l = pass3l(
            //     *tight_electrons_intree,
            //     *fakeable_electrons_intree,
            //     *preselected_electrons_intree,
            //     *tight_muons_intree,
            //     *fakeable_muons_intree,
            //     *preselected_muons_intree,
            //     *preselected_jets_intree,
            //     *met_intree
            // );

            // bool passes3l_lepMVA_AR = pass3l_lepMVA_AR(
            //     *tight_electrons_intree,
            //     *fakeable_electrons_intree,
            //     *preselected_electrons_intree,
            //     *tight_muons_intree,
            //     *fakeable_muons_intree,
            //     *preselected_muons_intree,
            //     *preselected_jets_intree,
            //     *met_intree
            // );

            if (passes2lss_lepMVA_AR) {
                if (sample_name == "data") {
                    mcwgt_intree = lepFakeRateObject.get_fr(*fakeable_leptons_intree);
                }
                else if (sample_name == "tth_aMC_old") {
                    myGenParticleHelper.clear();
                    myGenParticleHelper.matchReco2Gen(*tight_leptons_intree, *preselected_jets_intree, *pruned_genParticles_intree);
                }
                ss2l_tree->Fill();
                //cuts for os only 
                //    if ( myGenParticleHelper.higgs_final_state_intree.CompareTo("semiLeptonic") == 0 && myGenParticleHelper.ttbar_final_state_intree.CompareTo("semiLeptonic") == 0 )
                //   {
                //     ss2l_tree->Fill();
                //   }
            }
        } else {
            //////////////////////////
            ////
            //// bdt training selection
            ////
            //////////////////////////
          
            //fakeable
            // auto lep_collection = *fakeable_leptons_intree;
            // auto mu_collection = *fakeable_muons_intree;
            // auto ele_collection = *fakeable_electrons_intree;
          
            //preselected
            auto lep_collection = *preselected_leptons_intree;
            auto mu_collection = *preselected_muons_intree;
            auto ele_collection = *preselected_electrons_intree;
      
            bool passes2lss = pass2lss_bdtTraining(ele_collection, mu_collection, *preselected_jets_intree);
            if ( passes2lss ) {
                myGenParticleHelper.clear();
                myGenParticleHelper.matchReco2Gen(lep_collection, *preselected_jets_intree, *pruned_genParticles_intree);
                //cuts for os only 
                //if ( myGenParticleHelper.higgs_final_state_intree.CompareTo("semiLeptonic") == 0 && myGenParticleHelper.ttbar_final_state_intree.CompareTo("semiLeptonic") == 0 ) {
                ss2l_tree->Fill();
                //}
            }
        }
    }


    double endtime = get_wall_time();
    cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
    if ( (last_entry - first_entry) >0) cout << "an average of " << (endtime - starttime) / (last_entry - first_entry) << " per event." << endl;

    ss2l_tree->Write();
    copiedfile->Close();
}

void makeSelectionTree(TString sample="data", TString selection="analysis", int job_no=-1)
{
    //TString output_dir = "/afs/cern.ch/user/a/awightma/workspace/CMSSW_8_0_20/src/ttH-13TeVMultiLeptons/TemplateMakers/test/";
    TString output_dir = "/scratch365/cmuelle2/selection_trees/jan24_ichep_trees/";

    TString postfix;
    if (selection == "analysis") postfix = "_selection_tree_2lss.root";
    else  postfix = "_training_tree_2lss.root";

    TString output_file = output_dir + sample + postfix;
    if (job_no != -1) output_file = output_dir + sample + "_2lss_"+std::to_string(job_no)+".root";

    run_it(sample, selection, output_file, job_no);
}

