#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>

#include <chrono>

#include "TSystem.h"
#include "TH1.h"
#include "TChain.h"
#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TLorentzVector.h"

#include "helperToolsEFT.h"
#include "loadEFTSamples.h"
#include "selectionEFT.h"

#include "stopwatch.h"

/////////////////////////////////////////
///
/// usage: root -l makeEFTSelectionTree.C+
///
/////////////////////////////////////////

Stopwatch my_stopwatch;

const bool USE_STOPWATCH = false;

void printProgress(int current_index, int total_entries) {
    if (current_index % max(int(total_entries/100.),1) == 0) {
        float fraction = 100.*current_index/total_entries;
        cout << int(fraction) << " % processed" << endl;
    }
}

template <typename H> void createOutputRootFile(
    H output_histogram,
    TString file_suffix_name,
    TString sample_name,
    TString output_dir,
    int job_no
) {
    TString output_root_file = sample_name + "_" + file_suffix_name + ".root";
    if (job_no > -1) {
        output_root_file = sample_name + "_" + file_suffix_name + "_" + std::to_string(job_no) + ".root";
    }
    cout << "Output File: " << output_dir + output_root_file << endl;
    TFile* out_f = new TFile(output_dir + output_root_file,"RECREATE");
    output_histogram->Write();
    out_f->Close();

    return;
}

//NOTE: Some of these settings get overriden in the mapEventFeedDirections() function
std::map<TString,SelectionParameters> getSelectionParameters() {
    int b_jet_req = 1;
    double lep_pt_cut = 20.0;
    double lep_eta_cut = 2.4;
    double jet_pt_cut = 20.0;
    double jet_eta_cut = 2.4;
    double lep_pt_veto = 10.0;
    bool req_exact_lep = true;
    bool req_exact_jet = false;

    SelectionParameters selection_2los_6jets;
    selection_2los_6jets.type          = "2los_6jets";
    selection_2los_6jets.lep_req       = 2;
    selection_2los_6jets.jet_req       = 6;
    selection_2los_6jets.b_jet_req     = b_jet_req;
    selection_2los_6jets.lep_pt        = lep_pt_cut;
    selection_2los_6jets.lep_eta       = lep_eta_cut;
    selection_2los_6jets.jet_pt        = jet_pt_cut;
    selection_2los_6jets.jet_eta       = jet_eta_cut;
    selection_2los_6jets.lep_pt_veto   = lep_pt_veto;
    selection_2los_6jets.sign          = 0;
    selection_2los_6jets.req_exact_lep = req_exact_lep;
    selection_2los_6jets.req_exact_jet = req_exact_jet;

    SelectionParameters selection_2lss_p_6jets;
    selection_2lss_p_6jets.type          = "2lss_p_6jets";
    selection_2lss_p_6jets.lep_req       = 2;
    selection_2lss_p_6jets.jet_req       = 6;
    selection_2lss_p_6jets.b_jet_req     = b_jet_req;
    selection_2lss_p_6jets.lep_pt        = lep_pt_cut;
    selection_2lss_p_6jets.lep_eta       = lep_eta_cut;
    selection_2lss_p_6jets.jet_pt        = jet_pt_cut;
    selection_2lss_p_6jets.jet_eta       = jet_eta_cut;
    selection_2lss_p_6jets.lep_pt_veto   = lep_pt_veto;
    selection_2lss_p_6jets.sign          = 1;
    selection_2lss_p_6jets.req_exact_lep = req_exact_lep;
    selection_2lss_p_6jets.req_exact_jet = req_exact_jet;

    SelectionParameters selection_2lss_m_6jets;
    selection_2lss_m_6jets.type          = "2lss_m_6jets";
    selection_2lss_m_6jets.lep_req       = 2;
    selection_2lss_m_6jets.jet_req       = 6;
    selection_2lss_m_6jets.b_jet_req     = b_jet_req;
    selection_2lss_m_6jets.lep_pt        = lep_pt_cut;
    selection_2lss_m_6jets.lep_eta       = lep_eta_cut;
    selection_2lss_m_6jets.jet_pt        = jet_pt_cut;
    selection_2lss_m_6jets.jet_eta       = jet_eta_cut;
    selection_2lss_m_6jets.lep_pt_veto   = lep_pt_veto;
    selection_2lss_m_6jets.sign          = -1;
    selection_2lss_m_6jets.req_exact_lep = req_exact_lep;
    selection_2lss_m_6jets.req_exact_jet = req_exact_jet;

    SelectionParameters selection_3l_ppm_4jets;
    selection_3l_ppm_4jets.type          = "3l_ppm_4jets";
    selection_3l_ppm_4jets.lep_req       = 3;
    selection_3l_ppm_4jets.jet_req       = 4;
    selection_3l_ppm_4jets.b_jet_req     = b_jet_req;
    selection_3l_ppm_4jets.lep_pt        = lep_pt_cut;
    selection_3l_ppm_4jets.lep_eta       = lep_eta_cut;
    selection_3l_ppm_4jets.jet_pt        = jet_pt_cut;
    selection_3l_ppm_4jets.jet_eta       = jet_eta_cut;
    selection_3l_ppm_4jets.lep_pt_veto   = lep_pt_veto;
    selection_3l_ppm_4jets.sign          = 1;
    selection_3l_ppm_4jets.req_exact_lep = req_exact_lep;
    selection_3l_ppm_4jets.req_exact_jet = req_exact_jet;

    SelectionParameters selection_3l_mmp_4jets;
    selection_3l_mmp_4jets.type          = "3l_mmp_4jets";
    selection_3l_mmp_4jets.lep_req       = 3;
    selection_3l_mmp_4jets.jet_req       = 4;
    selection_3l_mmp_4jets.b_jet_req     = b_jet_req;
    selection_3l_mmp_4jets.lep_pt        = lep_pt_cut;
    selection_3l_mmp_4jets.lep_eta       = lep_eta_cut;
    selection_3l_mmp_4jets.jet_pt        = jet_pt_cut;
    selection_3l_mmp_4jets.jet_eta       = jet_eta_cut;
    selection_3l_mmp_4jets.lep_pt_veto   = lep_pt_veto;
    selection_3l_mmp_4jets.sign          = -1;
    selection_3l_mmp_4jets.req_exact_lep = req_exact_lep;
    selection_3l_mmp_4jets.req_exact_jet = req_exact_jet;

    SelectionParameters selection_4l_2jets;
    selection_4l_2jets.type          = "4l_2jets";
    selection_4l_2jets.lep_req       = 4;
    selection_4l_2jets.jet_req       = 2;
    selection_4l_2jets.b_jet_req     = b_jet_req;
    selection_4l_2jets.lep_pt        = lep_pt_cut;
    selection_4l_2jets.lep_eta       = lep_eta_cut;
    selection_4l_2jets.jet_pt        = jet_pt_cut;
    selection_4l_2jets.jet_eta       = jet_eta_cut;
    selection_4l_2jets.lep_pt_veto   = lep_pt_veto;
    selection_4l_2jets.sign          = 0;
    selection_4l_2jets.req_exact_lep = req_exact_lep;
    selection_4l_2jets.req_exact_jet = req_exact_jet;

    std::map<TString,SelectionParameters> selection_map;
    selection_map[selection_2los_6jets.type]   = selection_2los_6jets;
    selection_map[selection_2lss_p_6jets.type] = selection_2lss_p_6jets;
    selection_map[selection_2lss_m_6jets.type] = selection_2lss_m_6jets;
    selection_map[selection_3l_ppm_4jets.type] = selection_3l_ppm_4jets;
    selection_map[selection_3l_mmp_4jets.type] = selection_3l_mmp_4jets;
    selection_map[selection_4l_2jets.type]     = selection_4l_2jets;

    return selection_map;
}

void run_it(
    TString sample_name,
    vector<TString> bin_names,
    TString output_dir,
    TString output_file_name,
    int job_no,
    int total_jobs
) {
    FileLoader file_loader(sample_name,-1);
    TChain* chain = file_loader.chain;

    int total_count = file_loader.total_count;
    int chainentries = chain->GetEntries();   
    int last_entry = chainentries;
    int first_entry = 0;

    if (job_no > -1) {
        int entries_per_job = ceil(float(chainentries)/float(total_jobs));
        first_entry = job_no*entries_per_job;
        last_entry = (job_no+1)*entries_per_job;
        if (last_entry > chainentries) {
            last_entry = chainentries;
        }
    }

    cout << "job_no: " << job_no << endl;
    cout << "chainentries: " << chainentries << endl;
    cout << "first entry: " << first_entry << endl;
    cout << "last entry: " << last_entry << endl;

    vector<ttH::GenParticle> *pruned_genParticles_intree = 0;
    vector<ttH::GenParticle> *genJets_intree = 0;

    vector<ttH::Electron> *tight_electrons_intree = 0;
    vector<ttH::Muon>     *tight_muons_intree = 0;
    vector<ttH::Electron> *fakeable_electrons_intree = 0;
    vector<ttH::Muon>     *fakeable_muons_intree = 0;
    vector<ttH::Electron> *preselected_electrons_intree = 0;
    vector<ttH::Muon>     *preselected_muons_intree = 0;
    vector<ttH::Jet>      *preselected_jets_intree = 0;
    vector<ttH::Electron> *raw_electrons_intree = 0;
    vector<ttH::Muon>     *raw_muons_intree = 0;
    vector<ttH::Jet>      *raw_jets_intree = 0;

    double mcwgt_intree = -999.;

    chain->SetBranchAddress("mcwgt",                 &mcwgt_intree);
    chain->SetBranchAddress("pruned_genParticles",   &pruned_genParticles_intree);
    chain->SetBranchAddress("genJets",               &genJets_intree);
    chain->SetBranchAddress("tight_electrons",       &tight_electrons_intree);
    chain->SetBranchAddress("tight_muons",           &tight_muons_intree);
    chain->SetBranchAddress("fakeable_electrons",    &fakeable_electrons_intree);
    chain->SetBranchAddress("fakeable_muons",        &fakeable_muons_intree);
    chain->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
    chain->SetBranchAddress("preselected_muons",     &preselected_muons_intree);
    chain->SetBranchAddress("preselected_jets",      &preselected_jets_intree);
    chain->SetBranchAddress("raw_electrons",         &raw_electrons_intree);
    chain->SetBranchAddress("raw_muons",             &raw_muons_intree);
    chain->SetBranchAddress("raw_jets",              &raw_jets_intree);

    Int_t cachesize = 250000000;   //500 MBytes
    //  Int_t cachesize = 1024000000;   //1 GBytes
    chain->SetCacheSize(cachesize);

    // Event map histograms
    TH2D* bin_mapping_hist = new TH2D("Event Pass Mapping"   ,"Event Pass Mapping"   ,7,-0.5,6.5,7,-0.5,6.5);

    // Gen lepton dr histograms
    TH1D* gen_lep_dr_hist = new TH1D("Gen Lepton dr","Gen Lepton dr",200,-0.5,5.5);

    // Jet pt distributions
    TH1D* gen_jet_pt_hist  = new TH1D("Gen Jet Pt","Gen Jet Pt",100,-0.5,99.5);
    TH1D* reco_jet_pt_hist = new TH1D("Reco Jet Pt","Reco Jet Pt",100,-0.5,99.5);
    
    // Jet eta distributions
    TH1D* gen_jet_eta_hist = new TH1D("Gen Jet Eta","Gen Jet Eta",75,-2.5,2.5);
    TH1D* reco_jet_eta_hist = new TH1D("Reco Jet Eta","Reco Jet Eta",75,-2.5,2.5);

    // Gen2Reco Match Jet pt distribution
    TH1D* gen_to_reco_match_jet_pt_hist = new TH1D("Gen2Reco Jet Match Pt","Gen2Reco Jet Match Pt",100,-0.5,99.5);
    TH1D* gen_to_reco_match_jet_eta_hist = new TH1D("Gen2Reco Jet Match Eta","Gen2Reco Jet Match Eta",75,-2.5,2.5);

    vector<TString> bin_name_map = {
        "null",
        "2los_6jets",
        "2lss_p_6jets",
        "2lss_m_6jets",
        "3l_ppm_4jets",
        "3l_mmp_4jets",
        "4l_2jets"
    };

    uint jet_bin_tests[][2] = {
        {1,0},
        {1,1},
        {0,1}
    };

    // Jet bin histograms
    vector<TH2D*> jet_bin_histograms;
    for (auto &bin_names_map: jet_bin_tests) {
        TString bin_name_1 = bin_name_map.at(bin_names_map[0]);
        TString bin_name_2 = bin_name_map.at(bin_names_map[1]);
        TString hist_name = bin_name_1 + " vs. " + bin_name_2;

        //cout << "Hist Name: " << hist_name << endl;

        TH2D* tmp_histogram = new TH2D(hist_name,hist_name,16,-0.5,15.5,16,-0.5,15.5);
        jet_bin_histograms.push_back(tmp_histogram);
    }


    // GEN to RECO Jet pt histograms
    TH2D* gen_reco_dr_pt_hist = new TH2D("GEN Pt vs. RECO Pt","GEN Pt vs. RECO Pt",100,-0.5,99.5,100,-0.5,99.5);
    TH2D* gen_reco_dr_diff_pt_hist = new TH2D("GEN Pt vs. (RECO - GEN) Pt","GEN Pt vs. (RECO - GEN) Pt",100,-0.5,99.5,100,-30.0,30.0);  // Old low/high: -15.0/50.0
    TH2D* gen_reco_dr_ratio_pt_hist = new TH2D("GEN Pt vs. (RECO - GEN)/GEN Pt","GEN Pt vs. (RECO - GEN)/GEN Pt",100,-0.5,99.5,100,-2.0,2.0);

    // Matched vs. Un-matched Jet histograms
    TH2D* matched_unmatched_jet_hist = new TH2D("Matched vs. Unmatched Jets","Matched vs. Unmatched Jets",20,-0.5,19.5,20,-0.5,19.5);

    // Number of matched jets histograms
    TH1D* gen_to_reco_match_hist = new TH1D("Gen2Reco Matched","Gen2Reco Matched",20,-0.5,19.5);
    TH1D* reco_to_gen_match_hist = new TH1D("Reco2Gen Matched","Reco2Gen Matched",20,-0.5,19.5);
    TH1D* gen_to_reco_unmatched_hist = new TH1D("Gen2Reco Un-Matched","Gen2Reco Un-Matched",20,-0.5,19.5);
    TH1D* reco_to_gen_unmatched_hist = new TH1D("Reco2Gen Un-Matched","Reco2Gen Un-Matched",20,-0.5,19.5);

    TString cutflow_var = "Pt";
    //vector<double> cutflow_points {10,12,14,16,18,20,22,24,25,26,28,30};
    vector<double> cutflow_points {20};
    std::map<TString,std::map<int,double> > cutflow_counts;
    for (auto &bin_name: bin_names) {
        for (auto &cutflow_point: cutflow_points) {
            cutflow_counts[bin_name][cutflow_point] = 0;
        }
    }

    std::map<TString,SelectionParameters> selection_map = getSelectionParameters();

    //first_entry = 0;
    //last_entry = 50;

    for (int i = first_entry; i <= last_entry; i++) {
        if (USE_STOPWATCH) my_stopwatch.startTimer("event_loop");

        printProgress(i - first_entry,last_entry - first_entry);
        chain->GetEntry(i);

        vector<ttH::GenParticle> gen_leptons   = getGenLeptons(*pruned_genParticles_intree);
        vector<ttH::Lepton> reco_raw_leptons   = getRecoLeptons(*raw_electrons_intree,*raw_muons_intree);
        vector<ttH::Lepton> reco_ps_leptons    = getRecoLeptons(*preselected_electrons_intree,*preselected_muons_intree);
        vector<ttH::Lepton> reco_loose_leptons = getRecoLeptons(*fakeable_electrons_intree,*fakeable_muons_intree);
        vector<ttH::Lepton> reco_tight_leptons = getRecoLeptons(*tight_electrons_intree,*tight_muons_intree);

        //for (auto &gen_lepton: gen_leptons) {
        //    double min_dr = 999.;
        //    for (auto &gen_jet: *genJets_intree) {
        //        double delta_r = getDeltaR(gen_lepton,gen_jet);
        //        if (delta_r < 0) {
        //            continue;
        //        } else if (delta_r < min_dr) {
        //            min_dr = delta_r;
        //        }
        //    }
        //    gen_lep_dr_hist->Fill(min_dr,1*mcwgt_intree);
        //}

        ////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////

        /*
        //if (preselected_jets_intree->size() < 1) {
        //    continue;
        //}
        
        vector<ttH::GenParticle> cleaned_gen_jets = cleanCollection(*genJets_intree,gen_leptons,0.01);
        vector<ttH::Jet> cleaned_reco_jets = cleanCollection(*preselected_jets_intree,reco_raw_leptons,-1.00);
        //vector<ttH::Jet> cleaned_reco_jets = cleanCollection(*raw_jets_intree,reco_raw_leptons,-1.00);

        // Adjust the gen jet cuts to match the preselected jets (only for when we use the preselected collection)
        cleaned_gen_jets = applyPtCut(cleaned_gen_jets,25);
        //cleaned_gen_jets = applyEtaCut(cleaned_gen_jets,2.4);

        if (cleaned_gen_jets.size() < 1) {
            continue;
        } else if (cleaned_reco_jets.size() < 1) {
            continue;
        }

        //vector<ttH::GenParticle> cleaned_gen_particles = applyPtCut(*pruned_genParticles_intree,1.0);
        //vector<ttH::GenParticle> matched_b_jets = getBJets(cleaned_gen_particles,cleaned_gen_jets);
        //if (matched_b_jets.size() < 1) {
        //    continue;
        //}

        //cleaned_gen_jets = cleanCollection(cleaned_gen_jets,matched_b_jets,0.1);

        // Get GEN Jet Pt dist
        for (auto &gen_jet: cleaned_gen_jets) {
            gen_jet_pt_hist->Fill(gen_jet.obj.Pt(),1*mcwgt_intree);
            gen_jet_eta_hist->Fill(gen_jet.obj.Eta(),1*mcwgt_intree);
        }

        // Get RECO Jet Pt dist
        for (auto &reco_jet: cleaned_reco_jets) {
            reco_jet_pt_hist->Fill(reco_jet.obj.Pt(),1*mcwgt_intree);
            reco_jet_eta_hist->Fill(reco_jet.obj.Eta(),1*mcwgt_intree);
        }

        // Match Gen --> Reco jets
        auto gen2reco_jets = getMatchedJets(cleaned_gen_jets,cleaned_reco_jets,0.4);
        //gen_to_reco_match_hist->Fill(gen2reco_jets.size(),1*mcwgt_intree);
        //gen_to_reco_unmatched_hist->Fill(cleaned_gen_jets.size() - gen2reco_jets.size(),1*mcwgt_intree);

        // Match Reco --> Gen jets
        //auto reco2gen_jets = getMatchedJets(cleaned_reco_jets,cleaned_gen_jets,0.4);
        //reco_to_gen_match_hist->Fill(reco2gen_jets.size(),1*mcwgt_intree);
        //reco_to_gen_unmatched_hist->Fill(cleaned_reco_jets.size() - reco2gen_jets.size(),1*mcwgt_intree);


        for (auto &matched_jet: gen2reco_jets) {
            gen_to_reco_match_jet_pt_hist->Fill(matched_jet.obj.Pt(),1*mcwgt_intree);
            gen_to_reco_match_jet_eta_hist->Fill(matched_jet.obj.Eta(),1*mcwgt_intree);
        }

        for (auto &gen_jet: cleaned_gen_jets) {
            double min_dr = 999.;
            ttH::Jet best_reco_jet = cleaned_reco_jets.at(0);
            for (auto &reco_jet: cleaned_reco_jets) {
                double delta_r = getDeltaR(gen_jet,reco_jet);
                if (delta_r < 0) {
                    continue;
                } else if (delta_r < min_dr) {
                    min_dr = delta_r;
                    best_reco_jet = reco_jet;
                }
            }

            if (min_dr == 999.) {
                cout << "No reco jet found!" << endl;
                continue;
            }

            if (min_dr > 0.4) {
                continue;
            }

            double diff_pt = best_reco_jet.obj.Pt() - gen_jet.obj.Pt();
            double ratio_pt = (best_reco_jet.obj.Pt() - gen_jet.obj.Pt())/gen_jet.obj.Pt();

            gen_reco_dr_pt_hist->Fill(gen_jet.obj.Pt(),best_reco_jet.obj.Pt(),1*mcwgt_intree);
            gen_reco_dr_diff_pt_hist->Fill(gen_jet.obj.Pt(),diff_pt,1*mcwgt_intree);
            gen_reco_dr_ratio_pt_hist->Fill(gen_jet.obj.Pt(),ratio_pt,1*mcwgt_intree);
        }
        */

        ////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////

        vector<ttH::GenParticle> cleaned_gen_jets = cleanCollection(*genJets_intree,gen_leptons,0.01);
        vector<ttH::Jet> cleaned_reco_jets = cleanCollection(*preselected_jets_intree,reco_ps_leptons,-1.00);
        //vector<ttH::Jet> cleaned_reco_jets = cleanCollection(*raw_jets_intree,reco_raw_leptons,-1.00);

        if (USE_STOPWATCH) my_stopwatch.startTimer("map_events");
        vector<uint> bin_mapping_result = mapEventFeedDirections(
            gen_leptons,
            cleaned_gen_jets,
            //reco_raw_leptons,
            reco_ps_leptons,
            //reco_loose_leptons,
            //reco_tight_leptons,
            cleaned_reco_jets,
            *pruned_genParticles_intree,
            selection_map
        );
        if (USE_STOPWATCH) my_stopwatch.updateTimer("map_events");

        // Only fill histogram with events where we have at least 1 bin pass
        if (bin_mapping_result[0] > 0 || bin_mapping_result[1] > 0) {
            bin_mapping_hist->Fill(bin_mapping_result[0],bin_mapping_result[1],1*mcwgt_intree);
        }

        //cout << "Mapping: " << bin_mapping_result[0] << " --> " << bin_mapping_result[1] << endl;

        /*
        if (USE_STOPWATCH) my_stopwatch.startTimer("bin_jet_dist");
        for (uint j = 0; j < jet_bin_histograms.size(); j++) {
            if (bin_mapping_result[0] == jet_bin_tests[j][0] && bin_mapping_result[1] == jet_bin_tests[j][1]) {
                TString bin_name_1 = bin_name_map.at(jet_bin_tests[j][0]);
                TString bin_name_2 = bin_name_map.at(jet_bin_tests[j][1]);        
                vector<uint> bin_jet_counts = getBinJetCounts(
                    cleaned_gen_jets,
                    cleaned_reco_jets,
                    bin_name_1,
                    bin_name_2,
                    selection_map
                );

                //cout << "\tBin " << bin_name_1 << ": " << bin_jet_counts[0]<< endl;
                //cout << "\tBin " << bin_name_2 << ": " << bin_jet_counts[1]<< endl;

                jet_bin_histograms.at(j)->Fill(bin_jet_counts[0],bin_jet_counts[1],1*mcwgt_intree);
            }
        }
        if (USE_STOPWATCH) my_stopwatch.updateTimer("bin_jet_dist");
        */

        ////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////

        /*
        //vector<ttH::GenParticle> input_leptons = getGenLeptons(*pruned_genParticles_intree);
        vector<ttH::Lepton> input_leptons = reco_tight_leptons;
        //vector<ttH::Lepton> input_leptons = reco_ps_leptons;

        //vector<ttH::GenParticle> input_jets = *genJets_intree;
        vector<ttH::Jet> input_jets = *preselected_jets_intree;

        // Fill acceptance tables for each bin_name
        for (auto &bin_name: bin_names) {
            if (selection_map.find(bin_name) == selection_map.end()) {
                // We don't have a selection set for this bin!
                continue;
            }
            SelectionParameters current_selection = selection_map[bin_name];

            //cout << "Type: " << current_selection.type << endl;
            //cout << "\tJet Req.: " << current_selection.jet_req << endl;

            for (auto &cutflow_point: cutflow_points) {
                double lep_pt_cut = cutflow_point;
                bool passes = false;
                current_selection.lep_pt = lep_pt_cut;
                passes = pass_selection(
                    input_leptons,
                    input_jets,
                    *pruned_genParticles_intree,
                    current_selection
                );
                if (passes) {
                    cutflow_counts[bin_name][cutflow_point] += 1*mcwgt_intree;
                }
            }
        }
        */
        if (USE_STOPWATCH) my_stopwatch.updateTimer("event_loop");
    }

    cout << "Total Counts: " << total_count << endl;

    if (USE_STOPWATCH) my_stopwatch.readAllTimers();
    if (USE_STOPWATCH) cout << endl;
    if (USE_STOPWATCH) my_stopwatch.readAllTimers(1);

    //return;

    // Create Matched Jet histogram files
    //createOutputRootFile(gen_to_reco_match_hist,"matched_jets_gen2reco",sample_name,output_dir,job_no);
    //createOutputRootFile(reco_to_gen_match_hist,"matched_jets_reco2gen",sample_name,output_dir,job_no);

    //createOutputRootFile(gen_to_reco_unmatched_hist,"unmatched_jets_gen2reco",sample_name,output_dir,job_no);
    //createOutputRootFile(reco_to_gen_unmatched_hist,"unmatched_jets_reco2gen",sample_name,output_dir,job_no);

    // Create Jet Pt/Eta files
    //createOutputRootFile(gen_jet_pt_hist,"base_gen_jet_pt",sample_name,output_dir,job_no);
    //createOutputRootFile(reco_jet_pt_hist,"base_reco_jet_pt",sample_name,output_dir,job_no);
    //createOutputRootFile(gen_jet_eta_hist,"base_gen_jet_eta",sample_name,output_dir,job_no);
    //createOutputRootFile(reco_jet_eta_hist,"base_reco_jet_eta",sample_name,output_dir,job_no);
    //createOutputRootFile(gen_to_reco_match_jet_pt_hist,"matched_gen_jet_pt",sample_name,output_dir,job_no);
    //createOutputRootFile(gen_to_reco_match_jet_eta_hist,"matched_gen_jet_eta",sample_name,output_dir,job_no);

    // Create GEN to RECO Pt files
    //reateOutputRootFile(gen_reco_dr_pt_hist,"gen_reco_base",sample_name,output_dir,job_no);
    //reateOutputRootFile(gen_reco_dr_diff_pt_hist,"gen_reco_diff",sample_name,output_dir,job_no);
    //reateOutputRootFile(gen_reco_dr_ratio_pt_hist,"gen_reco_ratio",sample_name,output_dir,job_no);

    // Create event map files
    createOutputRootFile(bin_mapping_hist,"event_map",sample_name,output_dir,job_no);
    //for (uint i = 0; i < jet_bin_histograms.size(); i++) {
    //    TString bin_name_1 = bin_name_map.at(jet_bin_tests[i][0]);
    //    TString bin_name_2 = bin_name_map.at(jet_bin_tests[i][1]);
    //    TString file_suffix = bin_name_1 + "_vs_" + bin_name_2 + "_nJet_dist";
    //    createOutputRootFile(jet_bin_histograms.at(i),file_suffix,sample_name,output_dir,job_no);
    //}

    // Create jet bin histograms
    /*
    for (uint i = 0; i < jet_bin_histograms.size(); i++) {
        TString bin_name_1 = bin_name_map.at(jet_bin_tests[i][0]);
        TString bin_name_2 = bin_name_map.at(jet_bin_tests[i][1]);

        output_root_file = sample_name + "_" + bin_name_1 + "_vs_" + bin_name_2 + "_nJet_dist.root";
        if (job_no > -1) {
            output_root_file = sample_name + "_" + bin_name_1 + "_vs_" + bin_name_2 + "_nJet_dist_" + std::to_string(job_no) + ".root";
        }
        cout << "Output File: " << output_dir + output_root_file << endl;
        out_f = new TFile(output_dir + output_root_file,"RECREATE");
        jet_bin_histograms.at(i)->Write();
        out_f->Close();
    }
    */
    // Create acceptance table files
    /*
    cout << "Saving file... " << output_file_name << endl;
    std::ofstream ofile(output_file_name);
    ofile << "Total: " << total_count << endl;
    ofile << "Sample: " << sample_name << endl;
    for (auto &bin_name: bin_names) {
        ofile << "Bin Name: " << bin_name << endl;
        for (auto &cutflow_point: cutflow_points) {
            ofile << "\t" << cutflow_var << " " << cutflow_point << ": " << cutflow_counts[bin_name][cutflow_point] << endl;
        }
    }
    ofile.close();
    */
}

/*
    2los_6jets
    2lss_p_6jets
    2lss_m_6jets
    3l_ppm_4jets
    3l_mmp_4jets
    4l_2jets

    5l_p_0bjets
    5l_m_0bjets
    6l_0bjets
*/

void makeEFTSelectionTree(TString sample_name="ttW",int job_no=-1,int total_jobs=0) {
    TString output_dir = "/afs/crc.nd.edu/user/a/awightma/Public/";
    TString output_file_name = output_dir + sample_name + "_acceptance_table.txt";
    if (job_no > -1) {
        output_dir = "/afs/crc.nd.edu/user/a/awightma/Public/condor_output/";
        output_file_name = output_dir + sample_name + "_acceptance_table_" + std::to_string(job_no) + ".txt";
    }

    //vector<TString> bin_names {};
    vector<TString> bin_names {"2los_6jets","2lss_p_6jets","2lss_m_6jets","3l_ppm_4jets","3l_mmp_4jets","4l_2jets"};

    run_it(sample_name,bin_names,output_dir,output_file_name,job_no,total_jobs);
}