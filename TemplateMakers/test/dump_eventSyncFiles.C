//Charlie Mueller 1/13/2017
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include "TSystem.h"
#include "TH1.h"
#include "TChain.h"
#include "TString.h"
#include "TH1D.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/src/classes.h"
#include "variables.h"
#include "treeTools.h"
#include "TMVA/Reader.h"
#include "hTaggerBDT.h"

/////////////////////////////////////////
///
/// usage: root -l dump_eventSyncFiles.C+
///
/////////////////////////////////////////

//Merge the two vectors, and sort by highest pt
vector<ttH::Lepton> get_collection_ll(vector<ttH::Lepton> lepObjs_1, vector<ttH::Lepton> lepObjs_2)
{
  vector<ttH::Lepton> lepCollection(lepObjs_1.begin(),lepObjs_1.end());
  lepCollection.insert(lepCollection.end(),lepObjs_2.begin(),lepObjs_2.end());
  std::sort(lepCollection.begin(), lepCollection.end(), [] (ttH::Lepton a, ttH::Lepton b) { return a.obj.Pt() > b.obj.Pt();});
  return lepCollection;
}

void dumpToFile(
    std::ofstream& output,
    int event,
    vector<ttH::Lepton> *leptons,
    vector<ttH::Lepton> *psLeps,
    vector<ttH::Jet> *jets,
    vector<ttH::MET> *met,
    TString region
)
{
    if (region == "3l_lepMVA_AR" || region == "2lss_AR") {// Sort by correctedPt
        std::sort(leptons->begin(),leptons->end(),[] (ttH::Lepton a, ttH::Lepton b) {return a.correctedPt > b.correctedPt;});
    }

    //max lep eta
    double max_lep_eta = -1.;
    int count = 0;
    for (const auto & lep: *leptons) {
        count++;
        if (count >= 3) {//Only check leading 2 leptons
            continue;
        }
        if (abs(lep.obj.eta()) > max_lep_eta) {
            max_lep_eta = abs(lep.obj.eta());
        }
    }
  
    //min dr lep1,2
    ttH::Lepton lep1 = (*leptons)[0];
    ttH::Lepton lep2 = (*leptons)[1];
    ttH::Jet lep1_closest_jet = getClosestJet(*jets, lep1);
    ttH::Jet lep2_closest_jet = getClosestJet(*jets, lep2);
    double min_dr_lep1_jet = getDeltaR(lep1_closest_jet, lep1);
    double min_dr_lep2_jet = getDeltaR(lep2_closest_jet, lep2);

    ttH::Lepton lep3;
    ttH::Jet lep3_closest_jet;
    double min_dr_lep3_jet;
    if (region == "3l_SR" || region == "3l_lepMVA_AR") {
        lep3 = (*leptons)[2];
        lep3_closest_jet = getClosestJet(*jets,lep3);
        min_dr_lep3_jet = getDeltaR(lep3_closest_jet,lep3);
    }

    //mht
    auto objs_for_mht = getsumTLV(*psLeps,*jets);
    double mht_var = objs_for_mht.Pt();

    //met
    double met_var = min((*met)[0].obj.pt(), 400.);
    double mt_met_lep1 = sqrt(2*lep1.obj.pt()*met_var*(1-cos(lep1.obj.phi()-(*met)[0].obj.phi() )));
    if (region == "3l_lepMVA_AR" || "2lss_AR") {
        mt_met_lep1 = sqrt(2*lep1.correctedPt*met_var*(1-cos(lep1.obj.phi()-(*met)[0].obj.phi() )));
    }
  
    //avg dr jets
    int jet1_counter = 0;
    double dr_sum = 0.;
    int dr_denom = 0;
    for (const auto & jet1 : *jets) {
        int jet2_counter = -1;
        for (const auto & jet2 : *jets) {
            jet2_counter +=1;
            if ( jet2_counter <= jet1_counter ) continue;
            double delta_r = getDeltaR(jet1, jet2);
            dr_sum += delta_r;
            dr_denom +=1;
        }
        jet1_counter +=1;
    }
    double avg_dr_jets = dr_sum/double(dr_denom);

    output << setiosflags(ios::fixed) << setprecision(5);
    if (region == "3l_SR" || region == "3l_lepMVA_AR") {
        output << event << " "//1
               << 999.0 << " "//2
               << max_lep_eta << " "//3
               << mt_met_lep1 << " "//4
               << jets->size() << " "//5
               << mht_var << " "//6
               << avg_dr_jets << " "//7
               << min_dr_lep1_jet << " "//8
               << min_dr_lep2_jet << " "//9
               << lep1.correctedPt << " "//10
               << lep3.correctedPt << " "//11
               << 999.0 << " "//12
               << 999.0 << endl;//13
    } else {    
        output << event << " "
               << 999.0 << " "
               << max_lep_eta << " "
               << jets->size() << " "
               << min_dr_lep1_jet << " "
               << min_dr_lep2_jet << " "
               << met_var << " "
               << avg_dr_jets << " "
               << mt_met_lep1 << " "
               << lep1.correctedPt << " "
               << lep2.correctedPt << " "
               << 999.0 << " "
               << 999.0 << endl;
    }
}

void dumpHTagger(
    std::ofstream& output,
    int event,
    vector<ttH::Lepton> *leptons,
    vector<ttH::Lepton> *psLeps,
    vector<ttH::Jet> *jets,
    vector<ttH::MET> *met,
    hTagger* h_tagger,
    TString region
)
{
    ttH::Jet jet_1 = jets->at(0);
    ttH::Jet jet_2 = jets->at(1);

    double min_dr_jet = getDeltaR(jet_1,leptons->at(0));
    double max_dr_jet = getDeltaR(jet_1,leptons->at(0));
    for (auto &lep: *leptons) {
        double dr_jet = getDeltaR(jet_1,lep);
        if (dr_jet < min_dr_jet) {
            min_dr_jet = dr_jet;
        }
        if (dr_jet > max_dr_jet) {
            max_dr_jet = dr_jet;
        }
    }

    ttH::Jet jj_system;
    jj_system.obj = jet_1.obj+jet_2.obj;

    ttH::Lepton closest_lep = leptons->at(0);
    double jj_lep_mass = (jj_system.obj+closest_lep.obj).M();
    for (auto & lep: *leptons) {
        if (getDeltaR(lep,jj_system) < getDeltaR(closest_lep,jj_system)) {
            closest_lep = lep;
            jj_lep_mass = (jj_system.obj+lep.obj).M();
        }
    }

    double min_resid_jet_dr = 999.0;
    double max_resid_jet_dr = -999.0;
    for (auto & jet: *jets) {
        if (jet.obj.Pt() == jet_1.obj.Pt() || jet.obj.Pt() == jet_2.obj.Pt()) {
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

    double hj_bdt_score_1 = h_tagger->getHJBDTOutput(jet_1,leptons);
    double hj_bdt_score_2 = h_tagger->getHJBDTOutput(jet_2,leptons);
    double hj_bdt_sum = hj_bdt_score_1 + hj_bdt_score_2;

    double hjj_bdt_score = h_tagger->getHJJBDTOutput(jets,leptons);

    output << setiosflags(ios::fixed) << setprecision(5);
    output << event << " "                                // 1
           << min_dr_jet << " "                           // 2
           << jet_1.csv << " "                            // 3
           << jet_1.qgid << " "                           // 4
           << max_dr_jet << " "                           // 5
           << jet_1.obj.Pt() << " "                       // 6
           << hj_bdt_score_1 << " "                       // 7
           << jj_lep_mass << " "                          // 8
           << hj_bdt_sum << " "                           // 9
           << getDeltaR(jet_1,jet_2) << " "               // 10
           << min_resid_jet_dr << " "                     // 11
           << jj_system.obj.M() << " "                    // 12
           << (min_resid_jet_dr / max_resid_jet_dr) << " "// 13
           << hjj_bdt_score << endl;                      // 14
}

void dumpHadTopTagger(
    std::ofstream& output,
    int event,
    double reco_score,
    ttH::Jet b_from_hadtop,
    ttH::Jet b_from_leptop,
    ttH::Jet q1_from_hadtop,
    ttH::Jet q2_from_hadtop,
    TLorentzVector hadTop_tlv,
    TLorentzVector w_from_hadtop_tlv,
    ttH::Lepton lep_from_leptop,
    ttH::Lepton lep_from_higgs,
    double dr_lepFromTop_bFromLepTop,
    double dr_lepFromTop_bFromHadTop,
    double dr_lepFromHiggs_bFromLepTop

)
{
    vector<ttH::Jet> jet_collection = {b_from_hadtop,q1_from_hadtop,q2_from_hadtop};
    std::sort(jet_collection.begin(),jet_collection.end(), [] (ttH::Jet a, ttH::Jet b) {return a.obj.Pt() > b.obj.Pt();});

    double lep_pt_ratio = lep_from_leptop.correctedPt/lep_from_higgs.correctedPt;

    output << setiosflags(ios::fixed) << setprecision(5);
    output << event << " "
           << jet_collection[0].obj.Pt() << " "
           << jet_collection[1].obj.Pt() << " "
           << jet_collection[2].obj.Pt() << " "
           << b_from_hadtop.csv << " "
           << b_from_leptop.csv << " "
           << hadTop_tlv.M() << " "
           << hadTop_tlv.Pt() << " "
           << w_from_hadtop_tlv.M() << " "
           << lep_pt_ratio << " "
           << dr_lepFromTop_bFromLepTop << " "
           << dr_lepFromTop_bFromHadTop << " "
           << dr_lepFromHiggs_bFromLepTop << " "
           << reco_score << endl;

}

void run_it(TChain* chain,TString region)
{  
    std::ofstream sr_2lss_ee_output;
    std::ofstream sr_2lss_em_output;
    std::ofstream sr_2lss_mm_output;
    std::ofstream sr_2lss_tau_output;

    std::ofstream ar_2lss_ee_output;
    std::ofstream ar_2lss_em_output;
    std::ofstream ar_2lss_mm_output;
    std::ofstream ar_2lss_tau_output;

    std::ofstream ar_2los_ee_output;
    std::ofstream ar_2los_em_output;
    std::ofstream ar_2los_mm_output;
    std::ofstream ar_2los_tau_output;

    std::ofstream sr_3l_output;
    std::ofstream ar_3l_lepMVA_output;

    std::ofstream sr_2lss_htag_output;
    std::ofstream sr_2lss_hadtoptag_output;

    if (region == "2lss_SR") {
        sr_2lss_ee_output.open("event_dump_2lss_ee_sr.txt");
        sr_2lss_em_output.open("event_dump_2lss_em_sr.txt");
        sr_2lss_mm_output.open("event_dump_2lss_mm_sr.txt");
        sr_2lss_tau_output.open("event_dump_2lss_tau_sr.txt");
        sr_2lss_htag_output.open("event_dump_2lss_htag_sr.txt");
    } else if (region == "2lss_AR") {
        ar_2lss_ee_output.open("event_dump_2lss_ee_ar.txt");
        ar_2lss_em_output.open("event_dump_2lss_em_ar.txt");
        ar_2lss_mm_output.open("event_dump_2lss_mm_ar.txt");
        ar_2lss_tau_output.open("event_dump_2lss_tau_ar.txt");
    } else if (region == "2los_AR") {
        ar_2los_ee_output.open("event_dump_2los_ee_ar.txt");
        ar_2los_em_output.open("event_dump_2los_em_ar.txt");
        ar_2los_mm_output.open("event_dump_2los_mm_ar.txt");
        ar_2los_tau_output.open("event_dump_2los_tau_ar.txt");
    } else if (region == "3l_SR") {
        sr_3l_output.open("event_dump_3l_sr.txt");
    } else if (region == "3l_lepMVA_AR") {
        ar_3l_lepMVA_output.open("event_dump_3l_lepMVA_ar.txt");
    } else if (region == "2lss_SR_hadtop_tagger") {
        sr_2lss_hadtoptag_output.open("event_dump_2lss_hadtop_tagger_sr.txt");
    }
  
    int chainentries = chain->GetEntries();   
    cout << "# events in tree: "<< chainentries << endl;  
  
    double mcwgt_intree = -999.;
    int eventnum_intree = -999;
  
    vector<ttH::Lepton> *preselected_leptons_intree=0;
    vector<ttH::Lepton> *tight_leptons_intree=0;
    vector<ttH::Lepton> *fakeable_leptons_intree=0;
    vector<ttH::Electron> *raw_electrons_intree=0;               
    vector<ttH::Electron> *preselected_electrons_intree=0;
    vector<ttH::Muon> *raw_muons_intree=0;
    vector<ttH::Muon> *preselected_muons_intree=0;
    vector<ttH::Jet> *preselected_jets_intree=0;
    vector<ttH::Tau> *selected_taus_intree=0;
    vector<ttH::MET> *met_intree=0;

    double reco_score_intree = -2;
    ttH::Jet* b_from_hadtop_bdt_intree=0;
    ttH::Jet* b_from_leptop_bdt_intree=0;
    ttH::Jet* q1_from_hadtop_bdt_intree=0;
    ttH::Jet* q2_from_hadtop_bdt_intree=0;
    TLorentzVector* hadTop_tlv_bdt_intree=0;
    TLorentzVector* w_from_hadtop_tlv_bdt_intree=0;
    ttH::Lepton* lep_from_leptop_bdt_intree=0;
    ttH::Lepton* lep_from_higgs_bdt_intree=0;
    double dr_lepFromTop_bFromLepTop_intree;
    double dr_lepFromTop_bFromHadTop_intree;
    double dr_lepFromHiggs_bFromLepTop_intree;

    //only enable some branches
    chain->SetBranchStatus("*",0);
    chain->SetBranchStatus("mcwgt",1);
    chain->SetBranchStatus("eventnum",1);
    chain->SetBranchStatus("preselected_electrons.*",1);
    chain->SetBranchStatus("preselected_muons.*",1);
    chain->SetBranchStatus("preselected_jets.*",1);
    chain->SetBranchStatus("selected_taus.*",1);
    chain->SetBranchStatus("tight_leptons.*",1);
    chain->SetBranchStatus("fakeable_leptons.*",1);
    chain->SetBranchStatus("preselected_leptons.*",1);
    chain->SetBranchStatus("met.*",1);

    chain->SetBranchAddress("mcwgt", &mcwgt_intree);
    chain->SetBranchAddress("eventnum", &eventnum_intree);
    chain->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
    chain->SetBranchAddress("preselected_muons", &preselected_muons_intree);
    chain->SetBranchAddress("preselected_jets", &preselected_jets_intree);
    chain->SetBranchAddress("selected_taus", &selected_taus_intree);
    chain->SetBranchAddress("met", &met_intree);
    chain->SetBranchAddress("tight_leptons", &tight_leptons_intree);
    chain->SetBranchAddress("fakeable_leptons", &fakeable_leptons_intree);
    chain->SetBranchAddress("preselected_leptons",&preselected_leptons_intree);

    if (region == "2lss_SR_hadtop_tagger") {
        /* Get branches that only appear in output of hadtop_reco_bdt*/
        chain->SetBranchStatus("reco_score",1);
        chain->SetBranchStatus("b_from_hadtop_bdt.*",1);
        chain->SetBranchStatus("b_from_leptop_bdt.*",1);
        chain->SetBranchStatus("q1_from_hadtop_bdt.*",1);
        chain->SetBranchStatus("q2_from_hadtop_bdt.*",1);

        chain->SetBranchStatus("hadTop_bdt",1);
        chain->SetBranchStatus("w_from_hadtop_bdt",1);
        chain->SetBranchStatus("lep_from_leptop_bdt.*",1);
        chain->SetBranchStatus("lep_from_higgs_bdt.*",1);

        chain->SetBranchStatus("dR_lepFromTop_bFromLepTop",1);
        chain->SetBranchStatus("dR_lepFromTop_bFromHadTop",1);
        chain->SetBranchStatus("dR_lepFromHiggs_bFromLepTop",1);

        chain->SetBranchAddress("reco_score",&reco_score_intree);
        chain->SetBranchAddress("b_from_hadtop_bdt.",&b_from_hadtop_bdt_intree);
        chain->SetBranchAddress("b_from_leptop_bdt.",&b_from_leptop_bdt_intree);
        chain->SetBranchAddress("q1_from_hadtop_bdt.",&q1_from_hadtop_bdt_intree);
        chain->SetBranchAddress("q2_from_hadtop_bdt.",&q2_from_hadtop_bdt_intree);

        chain->SetBranchAddress("hadTop_bdt", &hadTop_tlv_bdt_intree);
        chain->SetBranchAddress("w_from_hadtop_bdt", &w_from_hadtop_tlv_bdt_intree);
        chain->SetBranchAddress("lep_from_leptop_bdt.", &lep_from_leptop_bdt_intree);
        chain->SetBranchAddress("lep_from_higgs_bdt.", &lep_from_higgs_bdt_intree);

        chain->SetBranchAddress("dR_lepFromTop_bFromLepTop", &dr_lepFromTop_bFromLepTop_intree);
        chain->SetBranchAddress("dR_lepFromTop_bFromHadTop", &dr_lepFromTop_bFromHadTop_intree);
        chain->SetBranchAddress("dR_lepFromHiggs_bFromLepTop", &dr_lepFromHiggs_bFromLepTop_intree);
    }

    hTagger* h_tagger = new hTagger(
        "/afs/cern.ch/user/a/awightma/workspace/misc_code/Hj_csv_BDTG.weights.xml",
        "/afs/cern.ch/user/a/awightma/workspace/misc_code/Hjj_csv_BDTG.weights.xml"
    );

    double starttime = get_wall_time();
    for (int i=0; i<chainentries; i++)  //// main loop
    {
      
        if (i%7000 == 0) {
            float fraction = 100.*i/chainentries;
            cout << fraction << " % complete" << endl;
            cout << i << endl;
        }

        chain->GetEntry(i);

        //11 == electron, 13 == muon
        if (region == "2lss_SR") {    
            if (abs((*tight_leptons_intree)[0].pdgID) == 11 && abs((*tight_leptons_intree)[1].pdgID) == 11 && (*selected_taus_intree).size() == 0) {
                dumpToFile(//ee
                    sr_2lss_ee_output,
                    eventnum_intree,
                    tight_leptons_intree,
                    preselected_leptons_intree,
                    preselected_jets_intree,
                    met_intree,
                    region
                );
            } else if (abs((*tight_leptons_intree)[0].pdgID) == 13 && abs((*tight_leptons_intree)[1].pdgID) == 13 && (*selected_taus_intree).size() == 0) {
                dumpToFile(//mm
                    sr_2lss_mm_output,
                    eventnum_intree,
                    tight_leptons_intree,
                    preselected_leptons_intree,
                    preselected_jets_intree,
                    met_intree,
                    region
                );
            } else if (((abs((*tight_leptons_intree)[0].pdgID) == 13 && abs((*tight_leptons_intree)[1].pdgID) == 11) || (abs((*tight_leptons_intree)[0].pdgID) == 11 && abs((*tight_leptons_intree)[1].pdgID) == 13)) && (*selected_taus_intree).size() == 0) {
                dumpToFile(//em
                    sr_2lss_em_output,
                    eventnum_intree,
                    tight_leptons_intree,
                    preselected_leptons_intree,
                    preselected_jets_intree,
                    met_intree,
                    region
                );
            } else if ((*selected_taus_intree).size() == 1) {
                dumpToFile(//tau
                    sr_2lss_tau_output,
                    eventnum_intree,
                    tight_leptons_intree,
                    preselected_leptons_intree,
                    preselected_jets_intree,
                    met_intree,
                    region
                );
            }

            if ((*selected_taus_intree).size() == 0) {            
                dumpHTagger(//htagger
                    sr_2lss_htag_output,
                    eventnum_intree,
                    tight_leptons_intree,
                    preselected_leptons_intree,
                    preselected_jets_intree,
                    met_intree,
                    h_tagger,
                    region
                );
            }
        } else if (region == "2lss_AR") {
            if (abs((*fakeable_leptons_intree)[0].pdgID) == 11 && abs((*fakeable_leptons_intree)[1].pdgID) == 11 && (*selected_taus_intree).size() == 0) {
                dumpToFile(//ee
                    ar_2lss_ee_output,
                    eventnum_intree,
                    fakeable_leptons_intree,
                    preselected_leptons_intree,
                    preselected_jets_intree,
                    met_intree,
                    region
                );
            } else if (abs((*fakeable_leptons_intree)[0].pdgID) == 13 && abs((*fakeable_leptons_intree)[1].pdgID) == 13 && (*selected_taus_intree).size() == 0) {
                dumpToFile(//mm
                    ar_2lss_mm_output,
                    eventnum_intree,
                    fakeable_leptons_intree,
                    preselected_leptons_intree,
                    preselected_jets_intree,
                    met_intree,
                    region
                );
            } else if (((abs((*fakeable_leptons_intree)[0].pdgID) == 13 && abs((*fakeable_leptons_intree)[1].pdgID) == 11) || (abs((*fakeable_leptons_intree)[0].pdgID) == 11 && abs((*fakeable_leptons_intree)[1].pdgID) == 13)) && (*selected_taus_intree).size() == 0) {
                dumpToFile(//em
                    ar_2lss_em_output,
                    eventnum_intree,
                    fakeable_leptons_intree,
                    preselected_leptons_intree,
                    preselected_jets_intree,
                    met_intree,
                    region
                );
            } else if ((*selected_taus_intree).size() == 1) {
                dumpToFile(//tau
                    ar_2lss_tau_output,
                    eventnum_intree,
                    fakeable_leptons_intree,
                    preselected_leptons_intree,
                    preselected_jets_intree,
                    met_intree,
                    region
                );
            }
        } else if (region == "2los_AR") {
            if (abs((*tight_leptons_intree)[0].pdgID) == 11 && abs((*tight_leptons_intree)[1].pdgID) == 11 && (*selected_taus_intree).size() == 0) {
                dumpToFile(//ee
                    ar_2los_ee_output,
                    eventnum_intree,
                    tight_leptons_intree,
                    preselected_leptons_intree,
                    preselected_jets_intree,
                    met_intree,
                    region
                );
            } else if (abs((*tight_leptons_intree)[0].pdgID) == 13 && abs((*tight_leptons_intree)[1].pdgID) == 13 && (*selected_taus_intree).size() == 0) {
                dumpToFile(//mm
                    ar_2los_mm_output,
                    eventnum_intree,
                    tight_leptons_intree,
                    preselected_leptons_intree,
                    preselected_jets_intree,
                    met_intree,
                    region
                );
            } else if (((abs((*tight_leptons_intree)[0].pdgID) == 13 && abs((*tight_leptons_intree)[1].pdgID) == 11) || (abs((*tight_leptons_intree)[0].pdgID) == 11 && abs((*tight_leptons_intree)[1].pdgID) == 13)) && (*selected_taus_intree).size() == 0) {
                dumpToFile(//em
                    ar_2los_em_output,
                    eventnum_intree,
                    tight_leptons_intree,
                    preselected_leptons_intree,
                    preselected_jets_intree,
                    met_intree,
                    region
                );
            } else if ((*selected_taus_intree).size() == 1) {
                dumpToFile(//tau
                    ar_2los_tau_output,
                    eventnum_intree,
                    tight_leptons_intree,
                    preselected_leptons_intree,
                    preselected_jets_intree,
                    met_intree,
                    region
                );
            }
        } else if (region == "3l_SR") {
            dumpToFile(
                sr_3l_output,
                eventnum_intree,
                tight_leptons_intree,
                preselected_leptons_intree,
                preselected_jets_intree,
                met_intree,
                region
            );
        } else if (region == "3l_lepMVA_AR") {
            dumpToFile(
                ar_3l_lepMVA_output,
                eventnum_intree,
                fakeable_leptons_intree,
                preselected_leptons_intree,
                preselected_jets_intree,
                met_intree,
                region
            );
        } else if (region == "2lss_SR_hadtop_tagger") {
            if ((*selected_taus_intree).size() == 0) {            
                dumpHadTopTagger(//hadtop tagger
                    sr_2lss_hadtoptag_output,
                    eventnum_intree,
                    reco_score_intree,
                    *b_from_hadtop_bdt_intree,
                    *b_from_leptop_bdt_intree,
                    *q1_from_hadtop_bdt_intree,
                    *q2_from_hadtop_bdt_intree,
                    *hadTop_tlv_bdt_intree,
                    *w_from_hadtop_tlv_bdt_intree,
                    *lep_from_leptop_bdt_intree,
                    *lep_from_higgs_bdt_intree,
                    dr_lepFromTop_bFromLepTop_intree,
                    dr_lepFromTop_bFromHadTop_intree,
                    dr_lepFromHiggs_bFromLepTop_intree
                );
            }
        }
    }
  
    double endtime = get_wall_time();
    cout << "Elapsed time: " << endtime - starttime << " seconds, " << endl;
    if (chainentries>0) cout << "an average of " << (endtime - starttime) / chainentries << " per event." << endl;

    if (region == "2lss_SR") {    
        sr_2lss_ee_output.close();
        sr_2lss_em_output.close();
        sr_2lss_mm_output.close();
        sr_2lss_tau_output.close();
        sr_2lss_htag_output.close();
    } else if (region == "2lss_AR") {
        ar_2lss_ee_output.close();
        ar_2lss_em_output.close();
        ar_2lss_mm_output.close();
        ar_2lss_tau_output.close();
    } else if (region == "2los_AR") {
        ar_2los_ee_output.close();
        ar_2los_em_output.close();
        ar_2los_mm_output.close();
        ar_2los_tau_output.close();
    } else if (region == "3l_SR") {
        sr_3l_output.close();
    } else if (region == "3l_lepMVA_AR") {
        ar_3l_lepMVA_output.close();
    } else if (region == "2lss_SR_hadtop_tagger") {
        sr_2lss_hadtoptag_output.close();
    }
}

void dump_eventSyncFiles(void)
{
    TString region = "2lss_SR_hadtop_tagger";
    TChain *chain = new TChain("ss2l_tree");

    if (region == "2lss_SR") {
        chain->Add("sync_2lss_SR_selection_tree_2lss.root");
    } else if (region == "2lss_AR") {
        chain->Add("sync_2lss_AR_selection_tree_2lss.root");
    } else if (region == "2los_AR") {
        chain->Add("sync_2los_AR_selection_tree_2lss.root");
    } else if (region == "3l_SR") {
        chain->Add("sync_3l_SR_selection_tree_2lss.root");
    } else if (region == "3l_lepMVA_AR") {
        chain->Add("sync_3l_lepMVA_AR_selection_tree_2lss.root");
    } else if (region == "2lss_SR_hadtop_tagger") {
        chain->Add("output_tree_2lss_SR_sync.root");
    }
    run_it(chain,region);

    //chain->Scan("raw_electrons.obj.pt():raw_electrons.dxy:raw_electrons.dz","eventnum==4986460")
    //chain->Scan("eventnum:tight_leptons.pdgID:@tight_leptons.size():@fakeable_leptons.size()","@fakeable_leptons.size() > 2");
  
}


