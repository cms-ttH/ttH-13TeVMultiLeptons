#ifndef HTAGGERBDT_H_
#define HTAGGERBDT_H_

#include <vector>
#include <string>
//#include <algorithm>
#include "TMVA/Reader.h"
//#include "TLorentzVector.h"

#include "treeTools.h" 
#include "ttH-13TeVMultiLeptons/TemplateMakers/src/classes.h"

class hTagger
{
private:
  TMVA::Reader* hj_mva;
  TMVA::Reader* hjj_mva;

  Float_t hj_mva_min_dr;
  Float_t hj_mva_jet_csv;
  Float_t hj_mva_jet_qg;
  Float_t hj_mva_max_dr;
  Float_t hj_mva_jet_pt;

  Float_t hjj_mva_jj_lep_mass;
  Float_t hjj_mva_hj_sum_bdt;
  Float_t hjj_mva_jj_dr;
  Float_t hjj_mva_min_jet_dr;
  Float_t hjj_mva_jj_mass;
  Float_t hjj_mva_jj_dr_ratio;

  //vector<ttH::Lepton> *tight_leptons_intree;
  //vector<ttH::Jet> *preselected_jets_intree;

  TMVA::Reader* bookHJMVA(std::string weights_file_str)
  {
    TMVA::Reader* TMVAReader_internal_ = new TMVA::Reader("!Color:!Silent");
    TMVAReader_internal_->AddVariable("Jet_lepdrmin",&hj_mva_min_dr);
    TMVAReader_internal_->AddVariable("Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags",&hj_mva_jet_csv);
    TMVAReader_internal_->AddVariable("Jet_qg",&hj_mva_jet_qg);
    TMVAReader_internal_->AddVariable("Jet_lepdrmax",&hj_mva_max_dr);
    TMVAReader_internal_->AddVariable("Jet_pt",&hj_mva_jet_pt);

    TMVAReader_internal_->BookMVA("BDTG method", weights_file_str);
    return TMVAReader_internal_;
  }

  TMVA::Reader* bookHJJMVA(std::string weights_file_str)
  {
    TMVA::Reader *TMVAReader_internal_ = new TMVA::Reader("!Color:!Silent");
    TMVAReader_internal_->AddVariable("bdtJetPair_minlepmass",&hjj_mva_jj_lep_mass);
    TMVAReader_internal_->AddVariable("bdtJetPair_sumbdt",&hjj_mva_hj_sum_bdt);
    TMVAReader_internal_->AddVariable("bdtJetPair_dr",&hjj_mva_jj_dr);
    TMVAReader_internal_->AddVariable("bdtJetPair_minjdr",&hjj_mva_min_jet_dr);
    TMVAReader_internal_->AddVariable("bdtJetPair_mass",&hjj_mva_jj_mass);
    TMVAReader_internal_->AddVariable("bdtJetPair_minjOvermaxjdr",&hjj_mva_jj_dr_ratio);

    TMVAReader_internal_->BookMVA("BDTG method", weights_file_str);
    return TMVAReader_internal_;
  }

public:
  hTagger(std::string hj_weights_file_str, std::string hjj_weights_file_str)
  {
    hj_mva = bookHJMVA(hj_weights_file_str);
    hjj_mva = bookHJJMVA(hjj_weights_file_str);
  }

  ~hTagger()
  {}

  double getHJBDTOutput(
    ttH::Jet target_jet,
    const vector<ttH::Lepton> *tight_leptons
  )
  {
    double min_dr_jet = getDeltaR(target_jet,tight_leptons->at(0));
    double max_dr_jet = getDeltaR(target_jet,tight_leptons->at(0));
    for (auto &lep: *tight_leptons) {
        double dr_jet = getDeltaR(target_jet,lep);
        if (dr_jet < min_dr_jet) {
            min_dr_jet = dr_jet;
        }
        if (dr_jet > max_dr_jet) {
            max_dr_jet = dr_jet;
        }
    }

    hj_mva_min_dr = min_dr_jet;
    hj_mva_jet_csv = target_jet.csv;
    hj_mva_jet_qg = target_jet.qgid;
    hj_mva_max_dr = max_dr_jet;
    hj_mva_jet_pt = target_jet.obj.Pt();

    double output = hj_mva->EvaluateMVA("BDTG method");

    return output;
  }

  double getHJJBDTOutput(
    ttH::Jet target_jet_1,
    ttH::Jet target_jet_2,
    const vector<ttH::Jet> *ps_jets,
    const vector<ttH::Lepton> *tight_leptons
  )
  {
    //ttH::Jet target_jet_1 = ps_jets->at(0);
    //ttH::Jet target_jet_2 = ps_jets->at(1);

    double min_dr_jet = getDeltaR(target_jet_1,tight_leptons->at(0));
    double max_dr_jet = getDeltaR(target_jet_1,tight_leptons->at(0));
    for (auto &lep: *tight_leptons) {
        double dr_jet = getDeltaR(target_jet_1,lep);
        if (dr_jet < min_dr_jet) {
            min_dr_jet = dr_jet;
        }
        if (dr_jet > max_dr_jet) {
            max_dr_jet = dr_jet;
        }
    }

    ttH::Jet jj_system;
    jj_system.obj = target_jet_1.obj+target_jet_2.obj;

    ttH::Lepton closest_lep = tight_leptons->at(0);
    double jj_lep_mass = (jj_system.obj+closest_lep.obj).M();
    for (auto & lep: *tight_leptons) {
        if (getDeltaR(lep,jj_system) < getDeltaR(closest_lep,jj_system)) {
            closest_lep = lep;
            jj_lep_mass = (jj_system.obj+lep.obj).M();
        }
    }

    double min_resid_jet_dr = 999.0;
    double max_resid_jet_dr = -999.0;
    for (auto & jet: *ps_jets) {
        if (jet.obj.Pt() == target_jet_1.obj.Pt() || jet.obj.Pt() == target_jet_2.obj.Pt()) {
            /* Ignore self jets */
            continue;
        }
        double jet_dr = getDeltaR(jj_system,jet);
        if (jet_dr < min_resid_jet_dr) {
            min_resid_jet_dr = jet_dr;
        }
        if (jet_dr > max_resid_jet_dr) {
            max_resid_jet_dr = jet_dr;
        }
    }

    double hj_bdt_score_1 = getHJBDTOutput(target_jet_1,tight_leptons);
    double hj_bdt_score_2 = getHJBDTOutput(target_jet_2,tight_leptons);
    double hj_bdt_sum = hj_bdt_score_1 + hj_bdt_score_2;

    hjj_mva_jj_lep_mass = jj_lep_mass;
    hjj_mva_hj_sum_bdt = hj_bdt_sum;
    hjj_mva_jj_dr = getDeltaR(target_jet_1,target_jet_2);
    hjj_mva_min_jet_dr = min_resid_jet_dr;
    hjj_mva_jj_mass = jj_system.obj.M();
    hjj_mva_jj_dr_ratio = (min_resid_jet_dr / max_resid_jet_dr);

    double output = hjj_mva->EvaluateMVA("BDTG method");

    return output;
  }
};

#endif
/* HTAGGERBDT */
