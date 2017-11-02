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
    std::map<TString,SelectionParameters> selection_map;

    SelectionParameters base_selection;
    base_selection.type          = "base_selection";
    base_selection.lep_req       = 2;
    base_selection.jet_req       = 6;
    base_selection.b_jet_req     = 1;
    base_selection.lep_pt        = 20.0;
    base_selection.lep_eta       = 2.4;
    base_selection.jet_pt        = 20.0;
    base_selection.jet_eta       = 2.4;
    base_selection.lep_pt_veto   = 10.0;
    base_selection.sign          = 0;
    base_selection.req_exact_lep = true;
    base_selection.req_exact_jet = false;

    SelectionParameters new_selection = base_selection;

    new_selection = base_selection;
    new_selection.type = "2los_6jets";
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type = "2lss_p_6jets";
    new_selection.sign = 1;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type = "2lss_m_6jets";
    new_selection.sign = -1;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type    = "3l_ppm_4jets";
    new_selection.lep_req = 3;
    new_selection.jet_req = 4;
    new_selection.sign    = 1;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type    = "3l_mmp_4jets";
    new_selection.lep_req = 3;
    new_selection.jet_req = 4;
    new_selection.sign    = -1;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type    = "4l_2jets";
    new_selection.lep_req = 4;
    new_selection.jet_req = 2;
    selection_map[new_selection.type] = new_selection;

    return selection_map;
}

std::map<TString,SelectionParameters> getSelectionParameters2() {
    std::map<TString,SelectionParameters> selection_map;

    SelectionParameters base_selection;
    base_selection.type          = "base_selection";
    base_selection.lep_req       = 2;
    base_selection.jet_req       = 0;
    base_selection.b_jet_req     = 1;       // Base: 0
    base_selection.lep_pt        = 20.0;    // Base: 20.0
    base_selection.lep_eta       = 2.4;     // Base: 2.4
    base_selection.jet_pt        = 30.0;
    base_selection.jet_eta       = 2.4;     // Base: 2.4
    base_selection.lep_pt_veto   = 20.0;    // Base: 10.0
    base_selection.sign          = 0;
    base_selection.req_exact_lep = true;
    base_selection.req_exact_jet = true;

    SelectionParameters new_selection = base_selection;

    new_selection = base_selection;
    new_selection.type = "0l_njets";
    new_selection.lep_req = 0;
    new_selection.jet_req = 0;
    new_selection.req_exact_jet = false;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type = "1l_njets";
    new_selection.lep_req = 1;
    new_selection.jet_req = 0;
    new_selection.req_exact_jet = false;
    selection_map[new_selection.type] = new_selection;

    // 2los
    new_selection = base_selection;
    new_selection.type = "2los_0jets";
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type    = "2los_1jets";
    new_selection.jet_req = 1;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type    = "2los_2jets";
    new_selection.jet_req = 2;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type    = "2los_3jets";
    new_selection.jet_req = 3;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type    = "2los_4jets";
    new_selection.jet_req = 4;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type    = "2los_5jets";
    new_selection.jet_req = 5;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type          = "2los_6jets";
    new_selection.jet_req       = 6;
    new_selection.req_exact_jet = false;
    selection_map[new_selection.type] = new_selection;

    // 2lss_p
    base_selection.sign = 1;

    new_selection = base_selection;
    new_selection.type    = "2lss_p_0jets";
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type    = "2lss_p_1jets";
    new_selection.jet_req = 1;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type    = "2lss_p_2jets";
    new_selection.jet_req = 2;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type    = "2lss_p_3jets";
    new_selection.jet_req = 3;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type    = "2lss_p_4jets";
    new_selection.jet_req = 4;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type    = "2lss_p_5jets";
    new_selection.jet_req = 5;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type          = "2lss_p_6jets";
    new_selection.jet_req       = 6;
    new_selection.req_exact_jet = false;
    selection_map[new_selection.type] = new_selection;

    // 2lss_m
    base_selection.sign = -1;

    new_selection = base_selection;
    new_selection.type    = "2lss_m_0jets";
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type    = "2lss_m_1jets";
    new_selection.jet_req = 1;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type    = "2lss_m_2jets";
    new_selection.jet_req = 2;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type    = "2lss_m_3jets";
    new_selection.jet_req = 3;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type    = "2lss_m_4jets";
    new_selection.jet_req = 4;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type    = "2lss_m_5jets";
    new_selection.jet_req = 5;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type          = "2lss_m_6jets";
    new_selection.jet_req       = 6;
    new_selection.req_exact_jet = false;
    selection_map[new_selection.type] = new_selection;

    // 3l_ppm
    base_selection.lep_req = 3;
    base_selection.sign = 1;

    new_selection = base_selection;
    new_selection.type = "3l_ppm_0jets";
    new_selection.jet_req = 0;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type = "3l_ppm_1jets";
    new_selection.jet_req = 1;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type = "3l_ppm_2jets";
    new_selection.jet_req = 2;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type = "3l_ppm_3jets";
    new_selection.jet_req = 3;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type = "3l_ppm_4jets";
    new_selection.jet_req = 4;
    new_selection.req_exact_jet = false;
    selection_map[new_selection.type] = new_selection;

    // 3l_mmp
    base_selection.lep_req = 3;
    base_selection.sign = -1;

    new_selection = base_selection;
    new_selection.type = "3l_mmp_0jets";
    new_selection.jet_req = 0;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type = "3l_mmp_1jets";
    new_selection.jet_req = 1;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type = "3l_mmp_2jets";
    new_selection.jet_req = 2;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type = "3l_mmp_3jets";
    new_selection.jet_req = 3;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type = "3l_mmp_4jets";
    new_selection.jet_req = 4;
    new_selection.req_exact_jet = false;
    selection_map[new_selection.type] = new_selection;

    // 4l
    base_selection.lep_req = 4;
    base_selection.sign = 0;

    new_selection = base_selection;
    new_selection.type = "4l_0jets";
    new_selection.jet_req = 0;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type = "4l_1jets";
    new_selection.jet_req = 1;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type = "4l_2jets";
    new_selection.jet_req = 2;
    new_selection.req_exact_jet = false;
    selection_map[new_selection.type] = new_selection;

    // 5l
    base_selection.lep_req = 5;

    new_selection = base_selection;
    new_selection.type = "5l_njets";
    new_selection.jet_req = 0;
    new_selection.req_exact_lep = false;
    new_selection.req_exact_jet = false;
    selection_map[new_selection.type] = new_selection;

    return selection_map;
}

void readSelectionMap(std::map<TString,SelectionParameters> s_map) {
    for (auto iter = s_map.begin(); iter != s_map.end(); ++iter) {
        auto key = iter->first;
        auto cur = s_map[key];

        cout << cur.type << ":" << endl;
        cout << "\tJet Pt: " << cur.jet_pt << endl;
        cout << "\tB Jets: " << cur.b_jet_req << endl;
        cout << "\tSign  : " << cur.sign << endl;
        cout << "\tEx Jet: " << cur.req_exact_jet << endl;
    }
}

void run_it(
    TString sample_name,
    vector<TString> bin_names,
    TString output_dir,
    TString output_file_name,
    int job_no,
    int total_jobs
) {
    if (USE_STOPWATCH) my_stopwatch.startTimer("code_setup");

    cout << "Sample: " << sample_name << endl;

    FileLoader file_loader(sample_name,-1);
    TChain* chain = file_loader.chain;

    int total_count = file_loader.total_count;
    int chainentries = chain->GetEntries();   
    int last_entry = chainentries;
    int first_entry = 0;

    if (chainentries == 0) {
        return;
    }

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
    vector<ttH::Lepton>   *preselected_leptons_intree = 0;
    vector<ttH::Electron> *preselected_electrons_intree = 0;
    vector<ttH::Muon>     *preselected_muons_intree = 0;
    vector<ttH::Jet>      *preselected_jets_intree = 0;
    vector<ttH::Electron> *raw_electrons_intree = 0;
    vector<ttH::Muon>     *raw_muons_intree = 0;
    vector<ttH::Jet>      *raw_jets_intree = 0;
    vector<ttH::Lepton>   *raw_leptons_intree = 0;

    double mcwgt_intree = -999.;

    bool skim = false;

    // Charlie's trees
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

    
    // Geoff's trees
    /*
    skim = true;
    chain->SetBranchAddress("mcwgt",                 &mcwgt_intree);
    chain->SetBranchAddress("pruned_genParticles",   &pruned_genParticles_intree);
    chain->SetBranchAddress("genJets",               &genJets_intree);
    chain->SetBranchAddress("preselected_jets",      &preselected_jets_intree);
    chain->SetBranchAddress("preselected_leptons",   &preselected_leptons_intree);
    chain->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
    chain->SetBranchAddress("preselected_muons",     &preselected_muons_intree);
    */

    Int_t cachesize = 250000000;   //500 MBytes
    //  Int_t cachesize = 1024000000;   //1 GBytes
    chain->SetCacheSize(cachesize);

    //vector<TString> bin_name_map = {
    //    "null",
    //    "2los_6jets",
    //    "2lss_p_6jets",
    //    "2lss_m_6jets",
    //    "3l_ppm_4jets",
    //    "3l_mmp_4jets",
    //    "4l_2jets"
    //};

    vector<TString> bin_name_map = {
        "null",

        "0l_njets",
        "1l_njets",

        "2los_0jets",
        "2los_1jets",
        "2los_2jets",
        "2los_3jets",
        "2los_4jets",
        "2los_5jets",
        "2los_6jets",

        "2lss_p_0jets",
        "2lss_p_1jets",
        "2lss_p_2jets",
        "2lss_p_3jets",
        "2lss_p_4jets",
        "2lss_p_5jets",
        "2lss_p_6jets",

        "2lss_m_0jets",
        "2lss_m_1jets",
        "2lss_m_2jets",
        "2lss_m_3jets",
        "2lss_m_4jets",
        "2lss_m_5jets",
        "2lss_m_6jets",

        "3l_ppm_0jets",
        "3l_ppm_1jets",
        "3l_ppm_2jets",
        "3l_ppm_3jets",
        "3l_ppm_4jets",

        "3l_mmp_0jets",
        "3l_mmp_1jets",
        "3l_mmp_2jets",
        "3l_mmp_3jets",
        "3l_mmp_4jets",

        "4l_0jets",
        "4l_1jets",
        "4l_2jets",

        "5l_njets"
    };

    double bin_offset = 0.5;

    // Event map histograms
    TH2D* bin_mapping_hist = new TH2D(
        "Event Pass Mapping",
        "Event Pass Mapping",
        bin_name_map.size(),0 - bin_offset,bin_name_map.size() - bin_offset,
        bin_name_map.size(),0 - bin_offset,bin_name_map.size() - bin_offset
    );

    //std::map<TString,SelectionParameters> selection_map = getSelectionParameters();
    std::map<TString,SelectionParameters> selection_map = getSelectionParameters2();

    for (auto bin: bin_name_map) {
        if (bin == "null") {
            continue;
        }
        if (selection_map.find(bin) == selection_map.end()) {
            cout << "ERROR: Unknown key in selection_map -- " << bin << endl;
            return;
        }
    }

    //readSelectionMap(selection_map);
    //return;

    //first_entry = 0;
    //last_entry = 15000;

    if (USE_STOPWATCH) my_stopwatch.updateTimer("code_setup");

    for (int i = first_entry; i <= last_entry; i++) {
        if (USE_STOPWATCH) my_stopwatch.startTimer("event_loop");

        printProgress(i - first_entry,last_entry - first_entry);
        if (USE_STOPWATCH) my_stopwatch.startTimer("get_entry");
        chain->GetEntry(i);
        if (USE_STOPWATCH) my_stopwatch.updateTimer("get_entry");

        if (skim) {        
            if (preselected_leptons_intree->size() < 2) {
                continue;
            }
        }

        if (USE_STOPWATCH) my_stopwatch.startTimer("get_objects");

        //vector<ttH::Electron> cleaned_electrons = {};
        //for (auto &ele: *preselected_electrons_intree) {
        //    if (ele.passConversioVeto) {
        //        cleaned_electrons.push_back(ele);
        //    }
        //}

        // Get Event Objects
        vector<ttH::GenParticle> gen_leptons   = getGenLeptons(*pruned_genParticles_intree);
        //vector<ttH::Lepton> reco_leptons = getRecoLeptons(*raw_electrons_intree,*raw_muons_intree);
        vector<ttH::Lepton> reco_leptons = getRecoLeptons(*preselected_electrons_intree,*preselected_muons_intree);
        //vector<ttH::Lepton> reco_leptons = getRecoLeptons(*fakeable_electrons_intree,*fakeable_muons_intree);
        //vector<ttH::Lepton> reco_leptons = getRecoLeptons(*tight_electrons_intree,*tight_muons_intree);
        if (USE_STOPWATCH) my_stopwatch.updateTimer("get_objects");

        if (USE_STOPWATCH) my_stopwatch.startTimer("clean_objects");
        // Clean Objects
        vector<ttH::GenParticle> cleaned_gen_jets = cleanCollection(*genJets_intree,gen_leptons,0.01);        
        vector<ttH::Jet> cleaned_reco_jets = cleanCollection(*preselected_jets_intree,reco_leptons,0.4);
        //vector<ttH::Jet> cleaned_reco_jets = cleanCollection(*raw_jets_intree,reco_leptons,0.1);
        if (USE_STOPWATCH) my_stopwatch.updateTimer("clean_objects");

        if (USE_STOPWATCH) my_stopwatch.startTimer("map_events");
        // Run GEN-->RECO Event Mapping
        vector<uint> bin_mapping_result = mapEventFeedDirections(
            gen_leptons,
            cleaned_gen_jets,
            reco_leptons,
            cleaned_reco_jets,
            *pruned_genParticles_intree,
            bin_name_map,
            selection_map
        );
        if (USE_STOPWATCH) my_stopwatch.updateTimer("map_events");

        //if (bin_mapping_result[0] > 0 || bin_mapping_result[1] > 0) {
        //    bin_mapping_hist->Fill(bin_mapping_result[0],bin_mapping_result[1],1*mcwgt_intree);
        //}
        bin_mapping_hist->Fill(bin_mapping_result[0],bin_mapping_result[1],1*mcwgt_intree);

        //cout << "Mapping: " << bin_mapping_result[0] << " --> " << bin_mapping_result[1] << endl;
        if (USE_STOPWATCH) my_stopwatch.updateTimer("event_loop");
    }

    cout << "Total Counts: " << total_count << endl;

    //return;

    if (USE_STOPWATCH) my_stopwatch.startTimer("write_files");
    // Create event map files
    createOutputRootFile(bin_mapping_hist,"event_map",sample_name,output_dir,job_no);
    if (USE_STOPWATCH) my_stopwatch.updateTimer("write_files");

    if (USE_STOPWATCH) my_stopwatch.readAllTimers();
    if (USE_STOPWATCH) cout << endl;
    if (USE_STOPWATCH) my_stopwatch.readAllTimers(1);
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

    vector<TString> bin_names {};
    //vector<TString> bin_names {"2los_6jets","2lss_p_6jets","2lss_m_6jets","3l_ppm_4jets","3l_mmp_4jets","4l_2jets"};

    run_it(sample_name,bin_names,output_dir,output_file_name,job_no,total_jobs);
}