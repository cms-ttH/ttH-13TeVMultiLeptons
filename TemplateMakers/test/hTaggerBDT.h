#ifndef HTAGGERBDT_H_
#define HTAGGERBDT_H_

#include <vector>
#include <typeinfo>
#include <tuple>
#include "TMVA/Reader.h"

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
  const char* env_p = std::getenv("CMSSW_BASE");

  TMVA::Reader* bookHJMVA(std::string weights_file_str)
  {
    TMVA::Reader* TMVAReader_internal_ = new TMVA::Reader("!Color:!Silent");
    TMVAReader_internal_->AddVariable("Jet_lepdrmin",&hj_mva_min_dr);
    TMVAReader_internal_->AddVariable("max(Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags,0.)",&hj_mva_jet_csv);
    TMVAReader_internal_->AddVariable("max(Jet_qg,0.)",&hj_mva_jet_qg);
    TMVAReader_internal_->AddVariable("Jet_lepdrmax",&hj_mva_max_dr);
    TMVAReader_internal_->AddVariable("Jet_pt",&hj_mva_jet_pt);

    std::string weight_file = env_p;
    weight_file += weights_file_str;
    TMVAReader_internal_->BookMVA("BDTG method", weight_file);
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

    std::string weight_file = env_p;
    weight_file += weights_file_str;
    TMVAReader_internal_->BookMVA("BDTG method", weight_file);
    return TMVAReader_internal_;
  }

public:
  hTagger(void)
  {
    hj_mva = bookHJMVA("/src/ttH-13TeVMultiLeptons/simpleweights/higgs_tagger/Hj_csv_BDTG.weights.xml");
    hjj_mva = bookHJJMVA("/src/ttH-13TeVMultiLeptons/simpleweights/higgs_tagger/Hjj_csv_BDTG.weights.xml");
  }

  ~hTagger(){}
  
  vector<ttH::Jet> *hj_bdt_jets_intree=0;    // Both of these vectors are of length 2
  vector<double> *hj_bdt_scores_intree=0;    // Both of these vectors are of length 2
  vector<ttH::Jet> *hjj_bdt_jets_intree=0;
  vector<double> *hjj_bdt_scores_intree=0;

  void clear(void)
  {
    hj_bdt_jets_intree->clear();
    hj_bdt_scores_intree->clear();
    hjj_bdt_jets_intree->clear();
    hjj_bdt_scores_intree->clear();
  }

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
    hj_mva_jet_csv = max(target_jet.csv,0.);
    hj_mva_jet_qg = max(target_jet.qgid,0.);
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







  void initializeTree(TTree *input_tree)
  {
    input_tree->Branch("hj_bdt_jets",&hj_bdt_jets_intree);
    input_tree->Branch("hj_bdt_scores",&hj_bdt_scores_intree);
    input_tree->Branch("hjj_bdt_jets",&hjj_bdt_jets_intree);
    input_tree->Branch("hjj_bdt_scores",&hjj_bdt_scores_intree);
  }


  void initialize(vector<ttH::Jet> *jets_in, const vector<ttH::Lepton> *leptons_in, const ttH::MET met_in)
  {
    clear();
    vector<ttH::Jet> jets_input = *jets_in;

    // Find the best hj/hjj scores amongst all possible jets
    double hj_mva_value = -2;
    double hjj_mva_value = -2;
    vector<std::tuple<ttH::Jet,double>> hj_jet_tuple;
    vector<std::tuple<ttH::Jet,ttH::Jet,double>> hjj_jet_tuple;
    for (unsigned int i = 0; i < jets_input.size(); i++) {
      ttH::Jet tmp_jet_1 = jets_input.at(i);
      hj_mva_value = getHJBDTOutput(tmp_jet_1,leptons_in);
      hj_jet_tuple.emplace_back(std::make_tuple(tmp_jet_1,hj_mva_value));
      for (unsigned int j = 0; j < jets_input.size(); j++) {
        ttH::Jet tmp_jet_2 = jets_input.at(j);
        if (i >= j) {
          /* Avoid double counting and self counting */
          continue;
        }
        hjj_mva_value = getHJJBDTOutput(tmp_jet_1,tmp_jet_2,&jets_input,leptons_in);
        hjj_jet_tuple.emplace_back(std::make_tuple(tmp_jet_1,tmp_jet_2,hjj_mva_value));
      }
    }
    /* Sort by bdt score */
    std::sort(hj_jet_tuple.begin(), hj_jet_tuple.end(), [](std::tuple<ttH::Jet,double> &t1, std::tuple<ttH::Jet,double> &t2) {
      return std::get<1>(t1) > std::get<1>(t2);
    });
    std::sort(hjj_jet_tuple.begin(), hjj_jet_tuple.end(), [](std::tuple<ttH::Jet,ttH::Jet,double> &t1, std::tuple<ttH::Jet,ttH::Jet,double> &t2) {
      return std::get<2>(t1) > std::get<2>(t2);
    });
    /* Store the best 2 hj_bdt jets and their scores */
    if (hj_jet_tuple.size() > 1) {
      /* At least 2 entries */
      hj_bdt_jets_intree->push_back(std::get<0>(hj_jet_tuple.at(0)));
      hj_bdt_jets_intree->push_back(std::get<0>(hj_jet_tuple.at(1)));
      hj_bdt_scores_intree->push_back(std::get<1>(hj_jet_tuple.at(0)));
      hj_bdt_scores_intree->push_back(std::get<1>(hj_jet_tuple.at(1)));
    } else if (hj_jet_tuple.size() > 0) {
      /* At least 1 entry */
      hj_bdt_jets_intree->push_back(std::get<0>(hj_jet_tuple.at(0)));
      hj_bdt_scores_intree->push_back(std::get<1>(hj_jet_tuple.at(0)));
      hj_bdt_scores_intree->push_back(-2.);
    } else {
      /* No entries */
      hj_bdt_scores_intree->push_back(-2.);
      hj_bdt_scores_intree->push_back(-2.);
    }
    /* Store the best hjj_bdt jets and the score */
    if (hjj_jet_tuple.size() > 0) {
      /* This check can fail if for instance we only have 4 jets in the event and 3 got put into the hadtop*/
      hjj_bdt_jets_intree->push_back(std::get<0>(hjj_jet_tuple.at(0)));
      hjj_bdt_jets_intree->push_back(std::get<1>(hjj_jet_tuple.at(0)));
      hjj_bdt_scores_intree->push_back(std::get<2>(hjj_jet_tuple.at(0)));
    } else {
      /* Fill the event with a default value */
      hjj_bdt_scores_intree->push_back(-2.);
    }
  }


};

#endif
/* HTAGGERBDT */
