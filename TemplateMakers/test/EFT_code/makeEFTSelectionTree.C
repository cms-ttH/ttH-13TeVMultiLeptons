#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <string>

#include <chrono>

#include "TApplication.h"
#include "TSystem.h"
#include "TH1.h"
#include "TChain.h"
#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TLorentzVector.h"

#include "helperToolsEFT.h"
// #include "loadEFTSamples.h"
#include "selectionEFT.h"

#include "stopwatch.h"

/////////////////////////////////////////
///
/// usage: root -l makeEFTSelectionTree.C+
///
/////////////////////////////////////////

Stopwatch my_stopwatch;

const bool USE_STOPWATCH = true;

void printProgress(int current_index, int total_entries) {
    int interval = 5;
    if (current_index % max(int(total_entries*interval/100.),interval) == 0) {
        float fraction = 100.*current_index/total_entries;
        cout << int(fraction) << " % processed " << endl;
    }
}

std::map<TString,SelectionParameters> getSelectionParameters() {
    std::map<TString,SelectionParameters> selection_map;

    SelectionParameters base_selection;
    base_selection.type          = "base_selection";
    base_selection.lep_req       = 2;
    base_selection.jet_req       = 0;
    base_selection.b_jet_req     = 1;       // Base: 1
    base_selection.lep_eta       = 2.4;     // Base: 2.4
    base_selection.jet_eta       = 2.4;     // Base: 2.4
    base_selection.lep_pt_veto   = 20.0;    // Base: 10.0 --> removed this check in pass_selection()
    base_selection.dilep_m_veto  = -1;
    base_selection.sign          = 0;
    base_selection.z_window      = 10.0;
    base_selection.req_exact_lep = true;
    base_selection.req_exact_jet = true;
    base_selection.req_zmass     = false;

    base_selection.lep_pt_gen    = 20.0;
    base_selection.lep_pt_reco   = 20.0;
    base_selection.jet_pt_gen    = 30.0;
    base_selection.jet_pt_reco   = 30.0;

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

    // 2los_sfz
    base_selection.req_zmass = true;

    new_selection = base_selection;
    new_selection.type          = "2los_sfz_0jets";
    new_selection.jet_req       = 0;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type          = "2los_sfz_1jets";
    new_selection.jet_req       = 1;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type          = "2los_sfz_2jets";
    new_selection.jet_req       = 2;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type          = "2los_sfz_3jets";
    new_selection.jet_req       = 3;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type          = "2los_sfz_4jets";
    new_selection.jet_req       = 4;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type          = "2los_sfz_5jets";
    new_selection.jet_req       = 5;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type          = "2los_sfz_6jets";
    new_selection.jet_req       = 6;
    new_selection.req_exact_jet = false;
    selection_map[new_selection.type] = new_selection;

    // 2lss_p
    base_selection.sign = 1;
    base_selection.req_zmass = false;

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

    // 3l_ppm_sfz
    base_selection.req_zmass = true;

    new_selection = base_selection;
    new_selection.type = "3l_ppm_sfz_0jets";
    new_selection.jet_req = 0;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type = "3l_ppm_sfz_1jets";
    new_selection.jet_req = 1;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type = "3l_ppm_sfz_2jets";
    new_selection.jet_req = 2;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type = "3l_ppm_sfz_3jets";
    new_selection.jet_req = 3;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type = "3l_ppm_sfz_4jets";
    new_selection.jet_req = 4;
    new_selection.req_exact_jet = false;
    selection_map[new_selection.type] = new_selection;


    // 3l_mmp
    base_selection.lep_req = 3;
    base_selection.sign = -1;
    base_selection.req_zmass = false;

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

    // 3l_mmp_sfz
    base_selection.req_zmass = true;

    new_selection = base_selection;
    new_selection.type = "3l_mmp_sfz_0jets";
    new_selection.jet_req = 0;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type = "3l_mmp_sfz_1jets";
    new_selection.jet_req = 1;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type = "3l_mmp_sfz_2jets";
    new_selection.jet_req = 2;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type = "3l_mmp_sfz_3jets";
    new_selection.jet_req = 3;
    selection_map[new_selection.type] = new_selection;

    new_selection = base_selection;
    new_selection.type = "3l_mmp_sfz_4jets";
    new_selection.jet_req = 4;
    new_selection.req_exact_jet = false;
    selection_map[new_selection.type] = new_selection;


    // 4l
    base_selection.lep_req = 4;
    base_selection.sign = 0;
    base_selection.req_zmass = false;

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

void makeEFTSelectionTree(TString output_filename, std::vector<TString> input_filenames) {
    if (USE_STOPWATCH) my_stopwatch.startTimer("load_files");
    TChain chain("OSTwoLepAna/summaryTree");
    TH1D hsum("numInitialWeightedMCevents","numInitialWeightedMCevents",1,1,2);

    for (const auto& fname: input_filenames) {
        chain.Add(fname);

        auto file = TFile::Open(fname,"READONLY");
        if (file->IsOpen()) {
            TH1D *hist;
            file->GetObject("OSTwoLepAna/numInitialWeightedMCevents", hist);
            hsum.Add(hist);
        }
        delete file;
    }
    if (USE_STOPWATCH) my_stopwatch.updateTimer("load_files");


    int total_count = hsum.GetBinContent(1);
    int chainentries = chain.GetEntries();
    int last_entry = chainentries;
    int first_entry = 0;

    if (chainentries == 0) {
        return;
    }

    cout << "chainentries: " << chainentries << endl;
    cout << "first entry: " << first_entry << endl;
    cout << "last entry: " << last_entry << endl;

    vector<ttH::GenParticle> *pruned_genParticles_intree = 0;
    vector<ttH::GenParticle> *genJets_intree = 0;

    vector<ttH::Electron> *tight_electrons_intree = 0;
    vector<ttH::Muon>     *tight_muons_intree = 0;
    vector<ttH::Jet>      *loose_jets_intree = 0;
    vector<ttH::Electron> *raw_electrons_intree = 0;
    vector<ttH::Muon>     *raw_muons_intree = 0;
    vector<ttH::Jet>      *raw_jets_intree = 0;

    double mcwgt_intree = -999.;

    bool skim = false;
    bool reclean = false;
    
    // Geoff's trees
    //skim = true;
    chain.SetBranchAddress("mcwgt",               &mcwgt_intree);
    chain.SetBranchAddress("pruned_genParticles", &pruned_genParticles_intree);
    chain.SetBranchAddress("genJets",             &genJets_intree);
    chain.SetBranchAddress("loose_jets",          &loose_jets_intree);
    chain.SetBranchAddress("tight_electrons",     &tight_electrons_intree);
    chain.SetBranchAddress("tight_muons",         &tight_muons_intree);
    chain.SetBranchAddress("raw_electrons",       &raw_electrons_intree);
    chain.SetBranchAddress("raw_muons",           &raw_muons_intree);
    chain.SetBranchAddress("raw_jets",            &raw_jets_intree);

    Int_t cachesize = 250000000;   //500 MBytes
    //  Int_t cachesize = 1024000000;   //1 GBytes
    chain.SetCacheSize(cachesize);

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

        "2los_sfz_0jets",
        "2los_sfz_1jets",
        "2los_sfz_2jets",
        "2los_sfz_3jets",
        "2los_sfz_4jets",
        "2los_sfz_5jets",
        "2los_sfz_6jets",

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

        "3l_ppm_sfz_0jets",
        "3l_ppm_sfz_1jets",
        "3l_ppm_sfz_2jets",
        "3l_ppm_sfz_3jets",
        "3l_ppm_sfz_4jets",

        "3l_mmp_0jets",
        "3l_mmp_1jets",
        "3l_mmp_2jets",
        "3l_mmp_3jets",
        "3l_mmp_4jets",

        "3l_mmp_sfz_0jets",
        "3l_mmp_sfz_1jets",
        "3l_mmp_sfz_2jets",
        "3l_mmp_sfz_3jets",
        "3l_mmp_sfz_4jets",

        "4l_0jets",
        "4l_1jets",
        "4l_2jets",

        "5l_njets"
    };

    double bin_offset = 0.5;

    // Event map histograms
    TH2D* bin_mapping_hist = new TH2D(
        "event_map",
        "Event Pass Mapping",
        bin_name_map.size(),0 - bin_offset,bin_name_map.size() - bin_offset,
        bin_name_map.size(),0 - bin_offset,bin_name_map.size() - bin_offset
    );

    std::map<TString,SelectionParameters> selection_map = getSelectionParameters();

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
    //last_entry = 1000;
    //last_entry = 100000;
    //last_entry = chainentries;

    if (USE_STOPWATCH) my_stopwatch.updateTimer("code_setup");

    for (int i = first_entry; i <= last_entry; i++) {
        if (USE_STOPWATCH) my_stopwatch.startTimer("event_loop");
        printProgress(i - first_entry,last_entry - first_entry);
        if (USE_STOPWATCH) my_stopwatch.startTimer("get_entry");
        chain.GetEntry(i);
        if (USE_STOPWATCH) my_stopwatch.updateTimer("get_entry");


        //if (USE_STOPWATCH) my_stopwatch.startTimer("get_objects");

        vector<ttH::Jet> cleaned_reco_jets   = *loose_jets_intree;
        vector<ttH::Electron> reco_electrons = *tight_electrons_intree;
        vector<ttH::Muon> reco_muons         = *tight_muons_intree;

        //////////////////////////////
        // Re-clean (raw) collections
        //////////////////////////////
        if (reclean) {
            cleaned_reco_jets  = *raw_jets_intree;
            reco_electrons     = *raw_electrons_intree;
            reco_muons         = *raw_muons_intree;

            reco_electrons = applyGeoffCuts(reco_electrons);
            reco_muons     = applyGeoffCuts(reco_muons);

            reco_electrons = cleanCollection(reco_electrons,reco_muons,0.05);

            cleaned_reco_jets = cleanCollection(cleaned_reco_jets,reco_muons,0.4);
            cleaned_reco_jets = cleanCollection(cleaned_reco_jets,reco_electrons,0.4);
        }

        //////////////////////////////
        // Get Event Objects
        //////////////////////////////
        vector<ttH::GenParticle> gen_leptons = getGenLeptons(*pruned_genParticles_intree);
        vector<ttH::Lepton> reco_leptons     = getRecoLeptons(reco_electrons,reco_muons);
        //if (USE_STOPWATCH) my_stopwatch.updateTimer("get_objects"); 

        //////////////////////////////
        // Clean Objects
        //////////////////////////////
        //if (USE_STOPWATCH) my_stopwatch.startTimer("clean_objects");
        vector<ttH::GenParticle> cleaned_gen_jets = cleanCollection(*genJets_intree,gen_leptons,0.01);        
        //cleaned_reco_jets = cleanCollection(*preselected_jets_intree,reco_leptons,-0.4);
        //cleaned_reco_jets = cleanCollection(*raw_jets_intree,reco_leptons,0.1);
        //if (USE_STOPWATCH) my_stopwatch.updateTimer("clean_objects");

        //////////////////////////////
        // Run GEN-->RECO Event Mapping
        //////////////////////////////
        if (USE_STOPWATCH) my_stopwatch.startTimer("map_events");
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

        //////////////////////////////
        // Customized low-level checking code
        //////////////////////////////
        /*
        if (bin_mapping_result[0] == 2 && bin_mapping_result[1] > 2) {
            gen_leptons  = applyPtCut(gen_leptons,20);
            gen_leptons  = applyEtaCut(gen_leptons,2.4);
            reco_leptons = applyPtCut(reco_leptons,20);
            reco_leptons = applyEtaCut(reco_leptons,2.4);

            cout << "Event: " << i+first_entry << endl;
            cout << "#### GEN ####" << endl;
            for (auto lep: gen_leptons) {
                cout << "\tLepton: " << lep.pdgID << endl;
                cout << "\t\tMass:   " << lep.obj.M() << endl;
                cout << "\t\tPt():   " << lep.obj.Pt() << endl;
                cout << "\t\tCharge: " << lep.charge << endl;
            }
            cout << "#### RECO ####" << endl;
            for (auto lep: reco_leptons) {
                cout << "\tLepton: " << lep.pdgID << endl;
                cout << "\t\tMass:    " << lep.obj.M() << endl;
                cout << "\t\tPt():    " << lep.obj.Pt() << endl;
                cout << "\t\tCharge:  " << lep.charge << endl;
                cout << "\t\tIDLoose: " << lep.idLoosePOG << endl;
            }
        }
        */
        bin_mapping_hist->Fill(bin_mapping_result[0],bin_mapping_result[1],1*mcwgt_intree);

        //cout << "Mapping: " << bin_mapping_result[0] << " --> " << bin_mapping_result[1] << endl;
        if (USE_STOPWATCH) my_stopwatch.updateTimer("event_loop");
    }

    double scale_factor = 1.0/float(total_count);
    bin_mapping_hist->Scale(scale_factor);

    cout << "Total Counts: " << total_count << endl;
    cout << "Scale Factor: " << scale_factor << endl;


    //if (USE_STOPWATCH) my_stopwatch.startTimer("write_files");
    // Create event map files
    {
        TFile out(output_filename, "NEW");
        assert(out.IsOpen());
        bin_mapping_hist->Write();
    }
    //if (USE_STOPWATCH) my_stopwatch.updateTimer("write_files");

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
