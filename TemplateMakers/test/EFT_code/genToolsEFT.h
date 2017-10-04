#ifndef GENTOOLSEFT_H_
#define GENTOOLSEFT_H_

#include <vector>

#include "TLorentzVector.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/src/classes.h"

// Maps a pdg_id to a specific particle name
TString getParticleName(int pdg_id) {
    pdg_id = abs(pdg_id);
    if (pdg_id == 11) {
        return TString("Electron");
    } else if (pdg_id == 12) {
        return TString("Neutrino (ele)");
    } else if (pdg_id == 13) {
        return TString("Muon");
    } else if (pdg_id == 14) {
        return TString("Neutrino (mu)");
    } else if (pdg_id == 15) {
        return TString("Tau");
    } else if (pdg_id == 16) {
        return TString("Neutrino (tau)");
    } else if (pdg_id == 21) {
        return TString("Gluon");
    } else if (pdg_id == 22) {
        return TString("Photon");
    } else if (pdg_id == 23) {
        return TString("Z0");
    } else if (pdg_id == 24) {
        return TString("W");
    } else if (pdg_id == 1) {
        return TString("d Quark");
    } else if (pdg_id == 2) {
        return TString("u Quark");
    } else if (pdg_id == 3) {
        return TString("s Quark");
    } else if (pdg_id == 4) {
        return TString("c Quark");
    } else if (pdg_id == 5) {
        return TString("b Quark");
    } else if (pdg_id == 6) {
        return TString("t Quark");
    } else if (pdg_id == 111) {
        return TString("Pi0 Meson");
    } else if (pdg_id == 211) {
        return TString("Pi+ Meson");
    } else if (pdg_id == 310) {
        return TString("K0_S Meson");
    } else if (pdg_id == 413) {
        return TString("D*(2010)+ Meson");
    } else if (pdg_id == 421) {
        return TString("D0 Meson");
    } else if (pdg_id == 423) {
        return TString("D*(2007)0 Meson");
    } else if (pdg_id == 445) {
        return TString("Xc2(1P) Meson");
    } else if (pdg_id == 511) {
        return TString("B0 Meson");
    } else if (pdg_id == 523) {
        return TString("B+ Meson");
    } else if (pdg_id == 2212) {
        return TString("Proton");
    } else {
        return TString(std::to_string(pdg_id));
    }
}

TString getIndentString(int depth = 0) {
    TString indent = "";
    for (int i = 0; i < depth; i++) {
        indent += "\t";
    }
    return indent;
}

// Returns a vector of all gen_particles with the corresponding pdg_id
vector<ttH::GenParticle> getParticlesByID(int id,vector<ttH::GenParticle> gen_particles) {
    vector<ttH::GenParticle> particles;
    for (auto &gen_particle: gen_particles) {
        int pdg_ID = abs(gen_particle.pdgID);
        if (pdg_ID != id) {
            continue;
        }
        particles.push_back(gen_particle);
    }
    return particles;
}

ttH::GenParticle getMotherParticle(ttH::GenParticle gen_particle, vector<ttH::GenParticle> gen_particles) {
    ttH::GenParticle mother_particle = gen_particles.at(gen_particle.mother);
    return mother_particle;
}

ttH::GenParticle getChildParticle(ttH::GenParticle gen_particle, vector<ttH::GenParticle> gen_particles, int child_choice = 0) {
    ttH::GenParticle child_particle;
    if (child_choice == 0) {
        child_particle = gen_particles.at(gen_particle.child0);
    } else {
        child_particle = gen_particles.at(gen_particle.child1);
    }
    return child_particle;
}

// Read various properties of a specific gen_particle object
void readParticleInfo(ttH::GenParticle gen_particle, int particle_index, int depth = 0) {
    TString indent = getIndentString(depth);

    TString particle_name = getParticleName(gen_particle.pdgID);

    cout << indent << "Particle: " << particle_name << endl;
    cout << indent << "\tIndex:   " << particle_index << endl;
    cout << indent << "\tpdgID:   " << gen_particle.pdgID << endl;
    cout << indent << "\tCharge:  " << gen_particle.charge << endl;
    cout << indent << "\tStatus:  " << gen_particle.status << endl;
    cout << indent << "\tPrompt:  " << gen_particle.isPromptFinalState << endl;
    cout << indent << "\tObj:     " << gen_particle.obj << endl;
    cout << indent << "\tM():     " << gen_particle.obj.M() << endl;
    cout << indent << "\tPt():    " << gen_particle.obj.Pt() << endl;
    cout << indent << "\tP():     " << gen_particle.obj.P() << endl;
    cout << indent << "\tE():     " << gen_particle.obj.E() << endl;
    cout << indent << "\tMother:  " << gen_particle.mother << endl;
    cout << indent << "\tGMother: " << gen_particle.grandmother << endl;
    cout << indent << "\tChild0:  " << gen_particle.child0 << endl;
    cout << indent << "\tChild1:  " << gen_particle.child1 << endl;
}

// Prints out various object properties for each object in the collection
template <typename inObj> void readCollectionInfo(vector<inObj> collection, int depth = 0) {
    TString indent = getIndentString(depth);

    for (auto &particle: collection) {
        cout << indent << "Particle: " << getParticleName(particle.genPdgID) << endl;
        cout << indent << "\tMother:   " << getParticleName(particle.genMotherPdgID) << endl;
        cout << indent << "\tGMother:  " << getParticleName(particle.genGrandMotherPdgID) << endl;
    }
}

// Determines if the given particle (index) corresponds directly to the mother's children
bool isOriginal(uint particle_index, ttH::GenParticle mother_particle) {
    if (particle_index == mother_particle.child0 || particle_index == mother_particle.child1) {
        return true;
    } else {
        return false;
    }
}

#endif
/* GENTOOLSEFT */