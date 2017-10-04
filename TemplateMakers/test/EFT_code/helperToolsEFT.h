#ifndef HELPERTOOLSEFT_H_
#define HELPERTOOLSEFT_H_

#include <vector>
#include <typeinfo>

#include "genToolsEFT.h"

#include "TLorentzVector.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/src/classes.h"
#include "DataFormats/Math/interface/deltaR.h"

TString padLeft(TString str,char pad_char,int pad_num=0) {
    int length = str.Length();
    if (length >= pad_num) {
        return str;
    }
    TString padded_str(pad_char,pad_num - length);
    padded_str = padded_str + str;
    return padded_str;
}

TString padRight(TString str,char pad_char,int pad_num=0) {
    int length = str.Length();
    if (length >= pad_num) {
        return str;
    }
    TString padded_str(pad_char,pad_num - length);
    padded_str = str + padded_str;
    return padded_str;
}

//vector<ttH::GenParticle> sortGenParticles(vector<ttH::GenParticle> gen_particles) {
//    vector<ttH::GenParticle> gen_list(gen_particles.begin(),gen_particles.end());
//    std::sort(gen_list.begin(), gen_list.end(), [] (ttH::GenParticle a, ttH::GenParticle b) {return a.obj.Pt() > b.obj.Pt();});
//    return gen_list;
//}

template <typename T> vector<T> sortParticles(vector<T> particles) {
    vector<T> sorted_particles(particles.begin(),particles.end());
    std::sort(sorted_particles.begin(),sorted_particles.end(), [] (T a, T b) {return a.obj.Pt() > b.obj.Pt();});
    return sorted_particles;
}

template <typename T> int getSign(T val) {
    return (T(0) < val) - (val < T(0));
}

template <typename inObj> TLorentzVector setTlv(const inObj inputObj ) {
  TLorentzVector tlv; 
  tlv.SetPxPyPzE( inputObj.obj.px(), inputObj.obj.py(), inputObj.obj.pz(), inputObj.obj.E() );
  return tlv;
}

template <typename inObj1, typename inObj2> double getDeltaR(const inObj1 obj1, const inObj2 obj2) {
    TLorentzVector obj1_tlv = setTlv(obj1);
    TLorentzVector obj2_tlv = setTlv(obj2);
    if (obj1_tlv.Pt()*obj2_tlv.Pt() <= 1e-10) {
        return -1.;
    }

    return obj1_tlv.DeltaR( obj2_tlv );
}

vector<ttH::GenParticle> getGenLeptons(vector<ttH::GenParticle> gen_particles) {
    vector<ttH::GenParticle> leptons;
    for (auto &gen_particle: gen_particles) {
        // Must be prompt lepton
        if (gen_particle.isPromptFinalState || gen_particle.isDirectPromptTauDecayProductFinalState) {        
            int pdg_ID = fabs(gen_particle.pdgID);

            // Must be electron or muon
            if (pdg_ID != 11 && pdg_ID != 13) {
                continue;
            }

            leptons.push_back(gen_particle);
        }
    }

    leptons = sortParticles(leptons);
    
    return leptons;
}

template <typename inObj1, typename inObj2> vector<ttH::Lepton> getRecoLeptons(const vector<inObj1> collection_1, const vector<inObj2> collection_2) {
    vector<ttH::Lepton> lep_collection(collection_1.begin(),collection_1.end());
    lep_collection.insert(lep_collection.end(),collection_2.begin(),collection_2.end());
    lep_collection = sortParticles(lep_collection);
    return lep_collection;
    //std::sort(lep_collection.begin(), lep_collection.end(), [] (ttH::Lepton a, ttH::Lepton b) {
    //    return a.obj.Pt() > b.obj.Pt();
    //});
    //return lep_collection;
}

// Returns objects from the dirty collection that ARE NOT in the scrub collection
template <typename T1, typename T2> vector<T1> cleanCollection(const vector<T1> dirty_collection, const vector<T2> scrub_collection, double deltaR_cut) {
    vector<T1> cleaned_collection;

    for (auto &dirty_obj: dirty_collection) {
        bool is_clean = true;
        for (auto &scrub_obj: scrub_collection) {
            double dr = getDeltaR(dirty_obj,scrub_obj);
            if (dr < 0) {
                continue;
            }

            if (dr < deltaR_cut) {
                is_clean = false;
                break;
            }
        }

        if (is_clean) {
            cleaned_collection.push_back(dirty_obj);
        }
    }

    return cleaned_collection;
}

template <typename inObj> vector<inObj> applyPtCut(const vector<inObj> particles, double pt_cut) {
    vector<inObj> selected_particles;
    for (auto &particle: particles) {
        if (particle.obj.Pt() < pt_cut) {
            continue;
        }
        selected_particles.push_back(particle);
    }
    return selected_particles;
}

template <typename inObj> vector<inObj> applyEtaCut(const vector<inObj> particles, double eta_cut) {
    vector<inObj> selected_particles;
    for (auto &particle: particles) {
        if (fabs(particle.obj.Eta()) > eta_cut) {
            continue;
        }
        selected_particles.push_back(particle);
    }
    return selected_particles;
}

vector<ttH::GenParticle> getPromptParticles(vector<ttH::GenParticle> gen_particles) {
    vector<ttH::GenParticle> prompt_particles;
    for (auto &gen_particle: gen_particles) {
        if (!gen_particle.isPromptFinalState) {
            continue;
        }
        prompt_particles.push_back(gen_particle);
    }
    return prompt_particles;
}

// Attempts to match the jet object to its corresponding gen object
template <typename T> ttH::GenParticle matchGenObject(T jet, vector<ttH::GenParticle> gen_particles) {
    double min_dr = 999.;
    ttH::GenParticle best_gen_object = gen_particles.at(0);
    for (auto &gen_particle: gen_particles) {
        double dr = getDeltaR(gen_particle,jet);
        if (dr < 0) {
            continue;
        } else if (dr < min_dr) {
            min_dr = dr;
            best_gen_object = gen_particle;
        }
    }

    if (min_dr == 999.) {
        cout << "WARNING: Unable to match gen object!" << endl;
    }

    return best_gen_object;
}

// Attempts to match an object to some object in the specified collection
template <typename T1, typename T2> T2* matchObject(T1 target_particle, vector<T2> matching_collection) {
    double min_dr = 999.;
    T2 best_match = matching_collection.at(0);
    for (auto &match_obj: matching_collection) {
        double dr = getDeltaR(match_obj,target_particle);
        if (dr < 0) {
            continue;
        } else if (dr < min_dr) {
            min_dr = dr;
            best_match = match_obj;
        }
    }

    if (min_dr == 999.) {
        cout << "WARNING: Unable to match object!" << endl;
        return nullptr;
    }

    return &best_match;
}

// Returns b-jets matched to their gen_particle counterparts
template <typename T> vector<T> getBJets(vector<ttH::GenParticle> gen_particles, vector<T> jets) {
    double deltaR_cut = 0.4;
    vector<T> b_jets;
    for (auto &gen_jet: jets) {
        int index = 0;
        for (auto &gen_particle: gen_particles) {
            double delta_r = getDeltaR(gen_jet,gen_particle);
            if (delta_r > deltaR_cut || delta_r < 0) {
                index += 1;
                continue;
            }

            if (fabs(gen_particle.pdgID) == 5) {
                b_jets.push_back(gen_jet);
                break;
            }
            index += 1;
        }
    }
    return b_jets;
}

// Returns the calculated invariant W mass of the event (if possible)
double getInvWMass(vector<ttH::GenParticle> gen_particles) {
    double inv_w_mass = -999.;
    for (uint i = 0; i < gen_particles.size(); i++) {
        uint particle_index = i;
        ttH::GenParticle gen_particle = gen_particles.at(i);

        if (fabs(gen_particle.pdgID) != 24) {
            // Only look at W's
            continue;
        }

        if (gen_particle.mother == 9999) {
            // The particle has no mother
            continue;
        }

        ttH::GenParticle mother_particle = getMotherParticle(gen_particle,gen_particles);
        
        if (fabs(mother_particle.pdgID) == 6) {
            // Ignore W's from decaying top
            continue;
        }

        if (!isOriginal(particle_index,mother_particle)) {
            // This particle wasn't the original one spawned from the mother
            continue;
        }

        inv_w_mass = gen_particle.obj.M();
        break;
    }

    return inv_w_mass;
}

// Returns jets from base_collection that have been matched to a jet in matching_collection
template <typename T1, typename T2> vector<T1> getMatchedJets(
    vector<T1> base_collection,
    vector<T2> matching_collection,
    double min_dr_cut
) {
    vector<T1> matched_jets;

    if (base_collection.size() < 1) {
        return matched_jets;
    } else if (matching_collection.size() < 1) {
        return matched_jets;
    }

    for (auto &base_jet: base_collection) {
        double min_dr = 999.;
        T2 best_matched_jet = matching_collection.at(0);
        for (auto &matching_jet: matching_collection) {
            double delta_r = getDeltaR(base_jet,matching_jet);
            if (delta_r < 0) {
                continue;
            } else if (delta_r < min_dr) {
                min_dr = delta_r;
                best_matched_jet = matching_jet;
            }
        }

        if (min_dr > min_dr_cut) {
            continue;
        }

        matched_jets.push_back(base_jet);
    }

    return matched_jets;
}

#endif
/* HELPERTOOLSEFT */