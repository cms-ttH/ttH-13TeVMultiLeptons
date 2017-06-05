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

  Float_t hj_mva_min_dr;
  Float_t hj_mva_jet_csv;
  Float_t hj_mva_jet_qg;
  Float_t hj_mva_max_dr;
  Float_t hj_mva_jet_pt;

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

public:
  hTagger(void)
  {
    hj_mva = bookHJMVA("/src/ttH-13TeVMultiLeptons/simpleweights/higgs_tagger/Hj_csv_BDTG.weights.xml");
  }

  ~hTagger(){}
  
  vector<ttH::Jet> *hj_bdt_jets_intree=0;    // Both of these vectors are of length 2
  vector<double> *hj_bdt_scores_intree=0;    // Both of these vectors are of length 2

  void clear(void)
  {
    hj_bdt_jets_intree->clear();
    hj_bdt_scores_intree->clear();
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



  void initializeTree(TTree *input_tree)
  {
    input_tree->Branch("hj_bdt_jets",&hj_bdt_jets_intree);
    input_tree->Branch("hj_bdt_scores",&hj_bdt_scores_intree);
  }


  void initialize(vector<ttH::Jet> *jets_in, const vector<ttH::Lepton> *leptons_in, const ttH::MET met_in)
  {
    clear();
    vector<ttH::Jet> jets_input = *jets_in;

    // Find the best hj scores amongst all possible jets
    double hj_mva_value = -2;
    vector<std::tuple<ttH::Jet,double>> hj_jet_tuple;
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
      }
    }
    /* Sort by bdt score */
    std::sort(hj_jet_tuple.begin(), hj_jet_tuple.end(), [](std::tuple<ttH::Jet,double> &t1, std::tuple<ttH::Jet,double> &t2) {
      return std::get<1>(t1) > std::get<1>(t2);
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
  }


};

#endif
/* HTAGGERBDT */
