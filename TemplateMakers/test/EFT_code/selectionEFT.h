#include "helperToolsEFT.h"

bool pass_2los_6jets(
    vector<ttH::GenParticle> gen_particles,
    vector<ttH::GenParticle> gen_jets,
    double lep_pt_cut,
    double lep_eta_cut,
    double jet_pt_cut,
    double jet_eta_cut
) {
    vector<ttH::GenParticle> selected_leptons = getLeptons(gen_particles);

    selected_leptons = applyPtCut(selected_leptons,lep_pt_cut);
    selected_leptons = applyEtaCut(selected_leptons,lep_eta_cut);

    if (selected_leptons.size() != 2) {
        // Exactly 2 leptons
        return false;
    }

    if (selected_leptons[0].charge == selected_leptons[1].charge) {
        // Want OS leptons
        return false;
    }

    vector<ttH::GenParticle> selected_jets = getJets(gen_jets);

    selected_jets = applyPtCut(selected_jets,jet_pt_cut);
    selected_jets = applyEtaCut(selected_jets,jet_eta_cut);

    if (selected_jets.size() != 6) {
        // Exactly 6 jets
        return false;
    }
    return true;
}

bool pass_2lss_p_6jets(
    vector<ttH::GenParticle> gen_particles,
    vector<ttH::GenParticle> gen_jets,
    double lep_pt_cut,
    double lep_eta_cut,
    double jet_pt_cut,
    double jet_eta_cut
) {
    vector<ttH::GenParticle> selected_leptons = getLeptons(gen_particles);

    if (selected_leptons.size() > 2) {
        // Apply lepton veto
        selected_leptons = sortGenParticles(selected_leptons);
        double veto_cut = 10.0;
        if (selected_leptons.at(2).obj.Pt() > veto_cut) {
            //The 3rd lepton is above our veto cut
            return false;
        }
    }

    selected_leptons = applyPtCut(selected_leptons,lep_pt_cut);
    selected_leptons = applyEtaCut(selected_leptons,lep_eta_cut);
    if (selected_leptons.size() != 2) {
        // Exactly 2 leptons
        return false;
    }


    if (selected_leptons[0].charge != selected_leptons[1].charge) {
        // Want SS leptons
        return false;
    }


    if (selected_leptons[0].charge + selected_leptons[1].charge < 0) {
        // Want ++ leptons
        return false;
    }

    vector<ttH::GenParticle> selected_jets = getJets(gen_jets);

    selected_jets = applyPtCut(selected_jets,jet_pt_cut);
    selected_jets = applyEtaCut(selected_jets,jet_eta_cut);

    if (selected_jets.size() != 6) {
        // Exactly 6 jets
        return false;
    }

    //vector<ttH::GenParticle> b_jets = getBJets(selected_jets);
    //if (b_jets.size() < 1) {
    //    // At least 1 b-jet
    //    return false;
    //}

    return true;
}

bool pass_2lss_m_6jets(
    vector<ttH::GenParticle> gen_particles,
    vector<ttH::GenParticle> gen_jets,
    double lep_pt_cut,
    double lep_eta_cut,
    double jet_pt_cut,
    double jet_eta_cut
) {
    vector<ttH::GenParticle> selected_leptons = getLeptons(gen_particles);

    if (selected_leptons.size() > 2) {
        // Apply lepton veto
        selected_leptons = sortGenParticles(selected_leptons);
        double veto_cut = 10.0;
        if (selected_leptons.at(2).obj.Pt() > veto_cut) {
            //The 3rd lepton is above our veto cut
            return false;
        }
    }

    selected_leptons = applyPtCut(selected_leptons,lep_pt_cut);
    selected_leptons = applyEtaCut(selected_leptons,lep_eta_cut);

    if (selected_leptons.size() != 2) {
        // Exactly 2 leptons
        return false;
    }

    if (selected_leptons[0].charge != selected_leptons[1].charge) {
        // Want SS leptons
        return false;
    }

    if (selected_leptons[0].charge + selected_leptons[1].charge > 0) {
        // Want -- leptons
        return false;
    }

    vector<ttH::GenParticle> selected_jets = getJets(gen_jets);

    selected_jets = applyPtCut(selected_jets,jet_pt_cut);
    selected_jets = applyEtaCut(selected_jets,jet_eta_cut);

    if (selected_jets.size() != 6) {
        // Exactly 6 jets
        return false;
    }

    //vector<ttH::GenParticle> b_jets = getBJets(selected_jets);
    //if (b_jets.size() < 1) {
    //    // At least 1 b-jet
    //    return false;
    //}

    return true;
}

bool pass_3l_ppm_4jets(
    vector<ttH::GenParticle> gen_particles,
    vector<ttH::GenParticle> gen_jets,
    double lep_pt_cut,
    double lep_eta_cut,
    double jet_pt_cut,
    double jet_eta_cut
) {
    vector<ttH::GenParticle> selected_leptons = getLeptons(gen_particles);

    if (selected_leptons.size() > 3) {
        // Apply lepton veto
        selected_leptons = sortGenParticles(selected_leptons);
        double veto_cut = 10.0;
        if (selected_leptons.at(3).obj.Pt() > veto_cut) {
            //The 4th lepton is above our veto cut
            return false;
        }
    }

    selected_leptons = applyPtCut(selected_leptons,lep_pt_cut);
    selected_leptons = applyEtaCut(selected_leptons,lep_eta_cut);

    if (selected_leptons.size() != 3) {
        // Exactly 2 leptons
        return false;
    }

    if (selected_leptons[0].charge + selected_leptons[1].charge + selected_leptons[2].charge < 0) {
        // Want ++- leptons
        return false;
    }

    vector<ttH::GenParticle> selected_jets = getJets(gen_jets);

    selected_jets = applyPtCut(selected_jets,jet_pt_cut);
    selected_jets = applyEtaCut(selected_jets,jet_eta_cut);

    if (selected_jets.size() != 4) {
        // Exactly 4 jets
        return false;
    }

    //vector<ttH::GenParticle> b_jets = getBJets(selected_jets);
    //if (b_jets.size() < 1) {
    //    // At least 1 b-jet
    //    return false;
    //}

    return true;
}

bool pass_3l_mmp_4jets(
    vector<ttH::GenParticle> gen_particles,
    vector<ttH::GenParticle> gen_jets,
    double lep_pt_cut,
    double lep_eta_cut,
    double jet_pt_cut,
    double jet_eta_cut
) {
    vector<ttH::GenParticle> selected_leptons = getLeptons(gen_particles);

    if (selected_leptons.size() > 3) {
        // Apply lepton veto
        selected_leptons = sortGenParticles(selected_leptons);
        double veto_cut = 10.0;
        if (selected_leptons.at(3).obj.Pt() > veto_cut) {
            //The 4th lepton is above our veto cut
            return false;
        }
    }

    selected_leptons = applyPtCut(selected_leptons,lep_pt_cut);
    selected_leptons = applyEtaCut(selected_leptons,lep_eta_cut);

    if (selected_leptons.size() != 3) {
        // Exactly 2 leptons
        return false;
    }

    if (selected_leptons[0].charge + selected_leptons[1].charge + selected_leptons[2].charge > 0) {
        // Want --+ leptons
        return false;
    }

    vector<ttH::GenParticle> selected_jets = getJets(gen_jets);

    selected_jets = applyPtCut(selected_jets,jet_pt_cut);
    selected_jets = applyEtaCut(selected_jets,jet_eta_cut);

    if (selected_jets.size() != 4) {
        // Exactly 4 jets
        return false;
    }

    //vector<ttH::GenParticle> b_jets = getBJets(selected_jets);
    //if (b_jets.size() < 1) {
    //    // At least 1 b-jet
    //    return false;
    //}

    return true;
}

bool pass_4l_2jets(
    vector<ttH::GenParticle> gen_particles,
    vector<ttH::GenParticle> gen_jets,
    double lep_pt_cut,
    double lep_eta_cut,
    double jet_pt_cut,
    double jet_eta_cut
) {
    vector<ttH::GenParticle> selected_leptons = getLeptons(gen_particles);

    selected_leptons = applyPtCut(selected_leptons,lep_pt_cut);
    selected_leptons = applyEtaCut(selected_leptons,lep_eta_cut);

    if (selected_leptons.size() < 4) {
        // At least 4 leptons
        return false;
    }

    vector<ttH::GenParticle> selected_jets = getJets(gen_jets);

    selected_jets = applyPtCut(selected_jets,jet_pt_cut);
    selected_jets = applyEtaCut(selected_jets,jet_eta_cut);

    if (selected_jets.size() != 2) {
        // At least 2 jets
        return false;
    }

    //vector<ttH::GenParticle> b_jets = getBJets(selected_jets);
    //if (b_jets.size() < 1) {
    //    // At least 1 b-jet
    //    return false;
    //}

    return true;
}

bool pass_selection(
    vector<ttH::GenParticle> gen_particles,
    vector<ttH::GenParticle> gen_jets,
    double lep_pt_cut,
    double lep_eta_cut,
    double jet_pt_cut,
    double jet_eta_cut,
    int lep_req,
    int jet_req,
    int b_jet_req,
    bool req_exact_lep,
    bool req_exact_jet
) {
    vector<ttH::GenParticle> selected_leptons = getLeptons(gen_particles);

    selected_leptons = applyPtCut(selected_leptons,lep_pt_cut);
    selected_leptons = applyEtaCut(selected_leptons,lep_eta_cut);

    if (req_exact_lep) {
        if (selected_leptons.size() != lep_req) {
            // Exact number of leptons
            return false;
        }
    } else {
        if (selected_leptons.size() < lep_req) {
            // At least have number of leptons
            return false;
        }
    }

    vector<ttH::GenParticle> selected_jets = applyPtCut(gen_jets,jet_pt_cut);
    selected_jets = applyEtaCut(selected_jets,jet_eta_cut);

    if (req_exact_jet) {
        if (selected_jets.size() != jet_req) {
            return false;
        }
    } else {
        if (selected_jets.size() < jet_req) {
            return false;
        }
    }

    vector<ttH::GenParticle> cleaned_particles = applyPtCut(gen_particles,1.0);

    vector<ttH::GenParticle> matched_b_jets = getBJets(cleaned_particles,selected_jets);

    if (matched_b_jets.size() < b_jet_req) {
        return false;
    }

    return true;
}