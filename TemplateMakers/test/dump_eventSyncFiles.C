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

    if (region == "2lss_SR") {
        sr_2lss_ee_output.open("event_dump_2lss_ee_sr.txt");
        sr_2lss_em_output.open("event_dump_2lss_em_sr.txt");
        sr_2lss_mm_output.open("event_dump_2lss_mm_sr.txt");
        sr_2lss_tau_output.open("event_dump_2lss_tau_sr.txt");
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
                dumpToFile(
                    sr_2lss_ee_output,
                    eventnum_intree,
                    tight_leptons_intree,
                    preselected_leptons_intree,
                    preselected_jets_intree,
                    met_intree,
                    region
                );
            } else if (abs((*tight_leptons_intree)[0].pdgID) == 13 && abs((*tight_leptons_intree)[1].pdgID) == 13 && (*selected_taus_intree).size() == 0) {
                dumpToFile(
                    sr_2lss_mm_output,
                    eventnum_intree,
                    tight_leptons_intree,
                    preselected_leptons_intree,
                    preselected_jets_intree,
                    met_intree,
                    region
                );
            } else if (((abs((*tight_leptons_intree)[0].pdgID) == 13 && abs((*tight_leptons_intree)[1].pdgID) == 11) || (abs((*tight_leptons_intree)[0].pdgID) == 11 && abs((*tight_leptons_intree)[1].pdgID) == 13)) && (*selected_taus_intree).size() == 0) {
                dumpToFile(
                    sr_2lss_em_output,
                    eventnum_intree,
                    tight_leptons_intree,
                    preselected_leptons_intree,
                    preselected_jets_intree,
                    met_intree,
                    region
                );
            } else if ((*selected_taus_intree).size() == 1) {
                dumpToFile(
                    sr_2lss_tau_output,
                    eventnum_intree,
                    tight_leptons_intree,
                    preselected_leptons_intree,
                    preselected_jets_intree,
                    met_intree,
                    region
                );
            }
        } else if (region == "2lss_AR") {
            if (abs((*fakeable_leptons_intree)[0].pdgID) == 11 && abs((*fakeable_leptons_intree)[1].pdgID) == 11 && (*selected_taus_intree).size() == 0) {
                dumpToFile(
                    ar_2lss_ee_output,
                    eventnum_intree,
                    fakeable_leptons_intree,
                    preselected_leptons_intree,
                    preselected_jets_intree,
                    met_intree,
                    region
                );
            } else if (abs((*fakeable_leptons_intree)[0].pdgID) == 13 && abs((*fakeable_leptons_intree)[1].pdgID) == 13 && (*selected_taus_intree).size() == 0) {
                dumpToFile(
                    ar_2lss_mm_output,
                    eventnum_intree,
                    fakeable_leptons_intree,
                    preselected_leptons_intree,
                    preselected_jets_intree,
                    met_intree,
                    region
                );
            } else if (((abs((*fakeable_leptons_intree)[0].pdgID) == 13 && abs((*fakeable_leptons_intree)[1].pdgID) == 11) || (abs((*fakeable_leptons_intree)[0].pdgID) == 11 && abs((*fakeable_leptons_intree)[1].pdgID) == 13)) && (*selected_taus_intree).size() == 0) {
                dumpToFile(
                    ar_2lss_em_output,
                    eventnum_intree,
                    fakeable_leptons_intree,
                    preselected_leptons_intree,
                    preselected_jets_intree,
                    met_intree,
                    region
                );
            } else if ((*selected_taus_intree).size() == 1) {
                dumpToFile(
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
                dumpToFile(
                    ar_2los_ee_output,
                    eventnum_intree,
                    tight_leptons_intree,
                    preselected_leptons_intree,
                    preselected_jets_intree,
                    met_intree,
                    region
                );
            } else if (abs((*tight_leptons_intree)[0].pdgID) == 13 && abs((*tight_leptons_intree)[1].pdgID) == 13 && (*selected_taus_intree).size() == 0) {
                dumpToFile(
                    ar_2los_mm_output,
                    eventnum_intree,
                    tight_leptons_intree,
                    preselected_leptons_intree,
                    preselected_jets_intree,
                    met_intree,
                    region
                );
            } else if (((abs((*tight_leptons_intree)[0].pdgID) == 13 && abs((*tight_leptons_intree)[1].pdgID) == 11) || (abs((*tight_leptons_intree)[0].pdgID) == 11 && abs((*tight_leptons_intree)[1].pdgID) == 13)) && (*selected_taus_intree).size() == 0) {
                dumpToFile(
                    ar_2los_em_output,
                    eventnum_intree,
                    tight_leptons_intree,
                    preselected_leptons_intree,
                    preselected_jets_intree,
                    met_intree,
                    region
                );
            } else if ((*selected_taus_intree).size() == 1) {
                dumpToFile(
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
    }

}

void dump_eventSyncFiles(void)
{
    TString region = "2lss_AR";
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
    }
    run_it(chain,region);

    //chain->Scan("raw_electrons.obj.pt():raw_electrons.dxy:raw_electrons.dz","eventnum==4986460")
    //chain->Scan("eventnum:tight_leptons.pdgID:@tight_leptons.size():@fakeable_leptons.size()","@fakeable_leptons.size() > 2");
  
}
