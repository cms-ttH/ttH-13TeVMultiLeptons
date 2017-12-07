#include <map>
#include "helperToolsEFT.h"

struct SelectionParameters {
    TString type;
    double lep_pt;
    double lep_pt_gen;
    double lep_pt_reco;
    double lep_eta;
    double jet_pt_gen;
    double jet_pt_reco;
    double jet_pt;
    double jet_eta;
    double lep_pt_veto;
    double dilep_m_veto;
    double z_window;
    int sign;               //NOTE: SS+ --> +1, SS- --> -1, OS --> 0
    bool req_exact_lep;
    bool req_exact_jet;
    bool req_zmass;
    uint lep_req;
    uint jet_req;
    uint b_jet_req;
};

template <typename T1, typename T2> bool pass_selection(
    vector<T1> input_leptons,
    vector<T2> input_jets,
    vector<ttH::GenParticle> gen_particles,
    SelectionParameters &params
) {
    vector<T1> selected_leptons = applyPtCut(input_leptons,params.lep_pt);
    selected_leptons = applyEtaCut(selected_leptons,params.lep_eta);

    if (params.req_exact_lep) {
        if (selected_leptons.size() != params.lep_req) {
            // Exact number of leptons
            return false;
        }

        if (params.lep_req == 2) {
            // Veto leptons with invariant mass below threshold
            double dilep_mass = getMinInvMass(selected_leptons);
            if (dilep_mass < params.dilep_m_veto) {
                return false;
            }
        }

        //vector<T1> lepton_veto_selection = applyPtCut(input_leptons,params.lep_pt_veto);
        //lepton_veto_selection = applyEtaCut(lepton_veto_selection,params.lep_eta);
        //if (lepton_veto_selection.size() != params.lep_req) {
        //    // We picked up extra leptons with the looser veto cut
        //    return false;
        //}
    } else {
        if (selected_leptons.size() < params.lep_req) {
            return false;
        }
    }

    if (params.lep_req == 2) {
        // We are in the 2l category
        int sum_sign = getSign(selected_leptons[0].charge + selected_leptons[1].charge);
        if (sum_sign != params.sign) {
            return false;
        }

        if (params.sign == 0) {
            // We are in OS category
            bool z_mass_res = hasSFZLeptons(selected_leptons,params.z_window);
            if (params.req_zmass && !z_mass_res) {
                // This event req. zmass check, but fails the SFZ check
                return false;
            }
            if (!params.req_zmass && z_mass_res) {
                // This event excludes zmass check, but passes the SFZ check
                return false;
            }
        }
    } else if (params.lep_req == 3) {
        // We are in the 3l category
        int sum_sign = getSign(selected_leptons[0].charge + selected_leptons[1].charge + selected_leptons[2].charge);
        if (sum_sign != params.sign) {
            return false;
        }
        
        bool z_mass_res = hasSFZLeptons(selected_leptons,params.z_window);
        if (params.req_zmass && !z_mass_res) {
            // This event req. zmass check, but fails the SFZ check
            return false;
        }
        if (!params.req_zmass && z_mass_res) {
            // This event excludes zmass check, but passes the SFZ check
            return false;
        }
    }

    vector<T2> selected_jets = applyPtCut(input_jets,params.jet_pt);
    selected_jets = applyEtaCut(selected_jets,params.jet_eta);

    if (params.req_exact_jet) {
        if (selected_jets.size() != params.jet_req) {
            // Exact number of jets
            return false;
        }
    } else {
        if (selected_jets.size() < params.jet_req) {
            return false;
        }
    }

    if (params.b_jet_req > 0 && params.jet_req >= params.b_jet_req) {
        // Only check for b-jets when we allow for at least that number of jets in the event
        vector<ttH::GenParticle> cleaned_particles = applyPtCut(gen_particles,1.0);
        vector<T2> matched_b_jets = getBJets(cleaned_particles,selected_jets);

        if (matched_b_jets.size() < params.b_jet_req) {
            return false;
        }
    }

    return true;
}

//NOTE: This function assumes any particular event can only ever pass ONE selection
vector<uint> mapEventFeedDirections(
    vector<ttH::GenParticle> gen_leptons,
    vector<ttH::GenParticle> gen_jets,
    vector<ttH::Lepton> reco_leptons,
    vector<ttH::Jet> reco_jets,
    vector<ttH::GenParticle> gen_particles,
    vector<TString> bin_names,
    std::map<TString,SelectionParameters> &selection_map
) {
    std::map<TString,uint> bin_map;
    for (uint i = 0; i < bin_names.size(); i++) {
        bin_map[bin_names.at(i)] = i;
    }

    uint gen_bin_pass  = bin_map["null"];   //Defaults to null bin
    uint reco_bin_pass = bin_map["null"];   //Defaults to null bin
    bool null_pass;

    // Gen-Level
    null_pass = true;
    for (auto bin: bin_names) {
        if (bin == "null") {
            continue;
        }

        // Set asym cuts
        selection_map[bin].lep_pt = selection_map[bin].lep_pt_gen;
        selection_map[bin].jet_pt = selection_map[bin].jet_pt_gen;
        selection_map[bin].b_jet_req = 0;

        bool passes = pass_selection(
            gen_leptons,
            gen_jets,
            gen_particles,
            selection_map[bin]
        );

        if (passes) {
            gen_bin_pass = bin_map[bin];
            break;
        }
    }

    // Reco-Level
    null_pass = true;
    for (auto bin: bin_names) {
        if (bin == "null") {
            continue;
        }

        // Set asym cuts
        selection_map[bin].lep_pt = selection_map[bin].lep_pt_reco;
        selection_map[bin].jet_pt = selection_map[bin].jet_pt_reco;
        selection_map[bin].b_jet_req = 1;

        bool passes = pass_selection(
            reco_leptons,
            reco_jets,
            gen_particles,
            selection_map[bin]
        );

        if (passes) {
            reco_bin_pass = bin_map[bin];
            break;
        }
    }

    vector<uint> bin_mapping {gen_bin_pass,reco_bin_pass};

    return bin_mapping;
}

vector<uint> getBinJetCounts(
    vector<ttH::GenParticle> gen_jets,
    vector<ttH::Jet> reco_jets,
    TString gen_bin_name,
    TString reco_bin_name,
    std::map<TString,SelectionParameters> &selection_map
) {
    if (gen_bin_name != "null" && selection_map.find(gen_bin_name) == selection_map.end()) {
        cout << "ERROR: Unknown key in selection_map -- " << gen_bin_name << endl;
        return {0,0};
    } else if (reco_bin_name != "null" && selection_map.find(reco_bin_name) == selection_map.end()) {
        cout << "ERROR: Unknown key in selection_map -- " << reco_bin_name << endl;
        return {0,0};
    }

    double gen_jet_pt = 30;
    double gen_jet_eta = 2.4;
    if (gen_bin_name != "null") {
        gen_jet_pt = selection_map[gen_bin_name].jet_pt;
        gen_jet_eta = selection_map[gen_bin_name].jet_eta;
    }

    double reco_jet_pt = 30;
    double reco_jet_eta = 2.4;
    if (reco_bin_name != "null") {
        reco_jet_pt = selection_map[reco_bin_name].jet_pt;
        reco_jet_eta = selection_map[reco_bin_name].jet_eta;
    }

    vector<ttH::GenParticle> selected_gen_jets = applyPtCut(gen_jets,gen_jet_pt);
    selected_gen_jets = applyEtaCut(selected_gen_jets,gen_jet_eta);

    vector<ttH::Jet> selected_reco_jets = applyPtCut(reco_jets,reco_jet_pt);
    selected_reco_jets = applyEtaCut(selected_reco_jets,reco_jet_eta);

    vector<uint> jet_counts;
    jet_counts.push_back(selected_gen_jets.size());
    jet_counts.push_back(selected_reco_jets.size());

    //vector<uint> jet_counts {selected_gen_jets.size(),selected_reco_jets.size()};
    
    return jet_counts;
}