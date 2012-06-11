#include <cmath>      //necessary for absolute function fabs()     
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include "math.h"
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <sstream>

//Root includes                                   
#include "TROOT.h"
#include "Riostream.h"
#include "TFile.h"
#include "TH1.h"
#include "TH1F.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TTree.h"
#include "TString.h"
#include "TMath.h"
#include "TAxis.h"

class varInfo {

public:
  TString var;
  TString hName;
  TString hTitle;
  int nBins;
  int min;
  int max;

  
  varInfo(): var(""), hName(""), hTitle(""), nBins(0), min(0), max(0) {}

  varInfo(TString varName, TString histName, TString histTitle, int numBins, int binMin, int binMax) : 
    var(varName), hName(histName), hTitle(histTitle), nBins(numBins), min(binMin), max(binMax) {}

};

void HistosFromTrees () {

  //----------------------------------
  //
  //  Global job params
  //  File names, etc
  //---------------------------------
  
  std::vector<string> InputFileNames;
  std::vector<string> OutputDirectories;
  std::vector<string> JetTagReqs;
  
  std::string InputDirName = "treeFiles/";

//   OutputDirectories.push_back("rootDiMuon/");
//   OutputDirectories.push_back("rootDiEle/");
//   OutputDirectories.push_back("rootMuEG/");
//   OutputDirectories.push_back("rootDiMuonLoose/");
//   OutputDirectories.push_back("rootDiEleLoose/");
//   OutputDirectories.push_back("rootMuEGLoose/");
//   OutputDirectories.push_back("rootDiMuonZmask10/");
//   OutputDirectories.push_back("rootDiEleZmask10/");
//   OutputDirectories.push_back("rootDiMuonLooseZmask10/");
//   OutputDirectories.push_back("rootDiEleLooseZmask10/"); 

  OutputDirectories.push_back("rootDiMuonAll/");
  OutputDirectories.push_back("rootDiEleAll/");
  OutputDirectories.push_back("rootMuEGAll/");
  
  std::string OutputDirectory = "holder";

  //InputFileName format: InputDirName+InputFileName+".root"
  
  InputFileNames.push_back("singlet_s_JESDown_new");
  InputFileNames.push_back("singlet_s_JESUp_new");
  InputFileNames.push_back("singlet_s_nominal_new");
  InputFileNames.push_back("singlet_tW_JESDown_new");
  InputFileNames.push_back("singlet_tW_JESUp_new");
  InputFileNames.push_back("singlet_tW_nominal_new");
  InputFileNames.push_back("singlet_t_JESDown_new");
  InputFileNames.push_back("singlet_t_JESUp_new");
  InputFileNames.push_back("singlet_t_nominal_new");
  InputFileNames.push_back("singletbar_s_JESDown_new");
  InputFileNames.push_back("singletbar_s_JESUp_new");
  InputFileNames.push_back("singletbar_s_nominal_new");
  InputFileNames.push_back("singletbar_tW_JESDown_new");
  InputFileNames.push_back("singletbar_tW_JESUp_new");
  InputFileNames.push_back("singletbar_tW_nominal_new");
  InputFileNames.push_back("singletbar_t_JESDown_new");
  InputFileNames.push_back("singletbar_t_JESUp_new");
  InputFileNames.push_back("singletbar_t_nominal_new");
  InputFileNames.push_back("ttH120_JESDown_new");
  InputFileNames.push_back("ttH120_JESUp_new");
  InputFileNames.push_back("ttH120_nominal_new");
  InputFileNames.push_back("ttbarW_JESDown_new");
  InputFileNames.push_back("ttbarW_JESUp_new");
  InputFileNames.push_back("ttbarW_nominal_new");
  InputFileNames.push_back("ttbarZ_JESDown_new");
  InputFileNames.push_back("ttbarZ_JESUp_new");
  InputFileNames.push_back("ttbarZ_nominal_new");
  InputFileNames.push_back("ttbar_JESDown_new");
  InputFileNames.push_back("ttbar_JESUp_new");
  InputFileNames.push_back("ttbar_nominal_new");
  InputFileNames.push_back("ttbar_bb_JESDown_new");
  InputFileNames.push_back("ttbar_bb_JESUp_new");
  InputFileNames.push_back("ttbar_bb_nominal_new");
  InputFileNames.push_back("ttbar_cc_JESDown_new");
  InputFileNames.push_back("ttbar_cc_JESUp_new");
  InputFileNames.push_back("ttbar_cc_nominal_new");
  InputFileNames.push_back("wjets_JESDown_new");
  InputFileNames.push_back("wjets_JESUp_new");
  InputFileNames.push_back("wjets_nominal_new");
  InputFileNames.push_back("ww_JESDown_new");
  InputFileNames.push_back("ww_JESUp_new");
  InputFileNames.push_back("ww_nominal_new");
  InputFileNames.push_back("wz_JESDown_new");
  InputFileNames.push_back("wz_JESUp_new");
  InputFileNames.push_back("wz_nominal_new");
  InputFileNames.push_back("zjets_JESDown_new");
  InputFileNames.push_back("zjets_JESUp_new");
  InputFileNames.push_back("zjets_nominal_new");
  InputFileNames.push_back("zz_JESDown_new");
  InputFileNames.push_back("zz_JESUp_new");
  InputFileNames.push_back("zz_nominal_new");
  
  //InputFileName format: "../batchBEAN/"+InputFileName+"/test_beans_v1_"+InputFileName+"_ALL.root"
  
//   //InputFileNames.push_back("doubleMu2012_testTree_job_1_");
//   InputFileNames.push_back("DoubleMu_Run2011-v1_");
//   InputFileNames.push_back("DoubleElectron_Run2011-v1_");
//   InputFileNames.push_back("MuEG_Run2011-v1_");
//   //InputFileNames.push_back("doubleEle2012_week02_52Xonly_testTree");
  
//   InputFileNames.push_back("DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_");
//   InputFileNames.push_back("DYJetsToLL_M-10To50_TuneZ2_7TeV-madgraph_v1_PUTAG");
//   //InputFileNames.push_back("TTJets_TuneZ2_7TeV-madgraph-tauola_");
//   InputFileNames.push_back("WW_TuneZ2_7TeV_pythia6_tauola_");
//   InputFileNames.push_back("WZ_TuneZ2_7TeV_pythia6_tauola_");
//   InputFileNames.push_back("ZZ_TuneZ2_7TeV_pythia6_tauola_");
//   InputFileNames.push_back("T_TuneZ2_s-channel_7TeV-powheg-tauola_PUTAG");
//   InputFileNames.push_back("Tbar_TuneZ2_s-channel_7TeV-powheg-tauola_PUTAG");
//   InputFileNames.push_back("T_TuneZ2_t-channel_7TeV-powheg-tauola_PUTAG");
//   InputFileNames.push_back("Tbar_TuneZ2_t-channel_7TeV-powheg-tauola_PUTAG");
//   InputFileNames.push_back("T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola_PUTAG");
//   InputFileNames.push_back("Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola_PUTAG");
//   //  InputFileNames.push_back("TTH_HtoAll_M_120_7TeV_pythia6_");
//   InputFileNames.push_back("ttH_m120_PUTAG");
//   InputFileNames.push_back("tt");
//   InputFileNames.push_back("ttbb");
//   InputFileNames.push_back("ttcc");
//   InputFileNames.push_back("WJets");
//   InputFileNames.push_back("TTW_TuneZ2_7TeV-madgraph_PUTAG");
//   InputFileNames.push_back("TTZ_TuneZ2_7TeV-madgraph_PUTAG");


  //  InputFileNames.push_back("Lannon_PUTAG");

  std::vector<varInfo*> varList;
  double pival = 3.14159;
  
  varInfo *Ht = new varInfo("Ht", "Ht", "Ht", 1000, 0, 10000);
  varList.push_back(Ht);
  //  varInfo *M2_of_closest_tagged_jets = new varInfo("M2_of_closest_tagged_jets", "M2_of_closest_tagged_jets", "M2_of_closest_tagged_jets", 1000, 0, 100000);
  //  varList.push_back(M2_of_closest_tagged_jets);  
  //  varInfo *MuonEle = new varInfo("MuonEle", "MuonEle", "MuonEle", 2, 0, 2);
  //  varList.push_back(MuonEle);
  //  varInfo *PassTwoLepton = new varInfo("PassTwoLepton", "PassTwoLepton", "PassTwoLepton", 2, 0, 2);
  //  varList.push_back(PassTwoLepton);
  //  varInfo *TwoEle = new varInfo("TwoEle", "TwoEle", "TwoEle", 2, 0, 2);
  //  varList.push_back(TwoEle);
  //  varInfo *TwoMuon = new varInfo("TwoMuon", "TwoMuon", "TwoMuon", 2, 0, 2);
  //  varList.push_back(TwoMuon);
  varInfo *all_sum_pt = new varInfo("all_sum_pt", "all_sum_pt", "all_sum_pt", 10000, 0, 10000);
  varList.push_back(all_sum_pt);
  varInfo *avg_btag_disc_btags = new varInfo("avg_btag_disc_btags", "avg_btag_disc_btags", "avg_btag_disc_btags", 1000, 0, 1);
  varList.push_back(avg_btag_disc_btags);
  //  varInfo *avg_btag_disc_non_btags = new varInfo("avg_btag_disc_non_btags", "avg_btag_disc_non_btags", "avg_btag_disc_non_btags", 1000, 0, 1);
  //  varList.push_back(avg_btag_disc_non_btags);
  varInfo *avg_dr_tagged_jets = new varInfo("avg_dr_tagged_jets", "avg_dr_tagged_jets", "avg_dr_tagged_jets", 1000, 0, 10);
  varList.push_back(avg_dr_tagged_jets);
  varInfo *avg_tagged_dijet_mass = new varInfo("avg_tagged_dijet_mass", "avg_tagged_dijet_mass", "avg_tagged_dijet_mass", 1000, 0, 1000);
  varList.push_back(avg_tagged_dijet_mass);
  //  varInfo *avg_untagged_dijet_mass = new varInfo("avg_untagged_dijet_mass", "avg_untagged_dijet_mass", "avg_untagged_dijet_mass", 1000, 0, 1000);
  //  varList.push_back(avg_untagged_dijet_mass);
  //varInfo *CFMlpANN_e2je2t = new varInfo("CFMlpANN_e2je2t", "CFMlpANN_e2je2t", "CFMlpANN_e2je2t", 1000, 70, 80);
  //varList.push_back(CFMlpANN_e2je2t);
  //varInfo *CFMlpANN_ge3t = new varInfo("CFMlpANN_ge3t", "CFMlpANN_ge3t", "CFMlpANN_ge3t", 1000, 0, 1);
  //varList.push_back(CFMlpANN_ge3t);
  varInfo *closest_tagged_dijet_mass = new varInfo("closest_tagged_dijet_mass", "closest_tagged_dijet_mass", "closest_tagged_dijet_mass", 1000, 0, 1000);
  varList.push_back(closest_tagged_dijet_mass);
  //  varInfo *dPhi_leplep = new varInfo("dPhi_leplep", "dPhi_leplep", "dPhi_leplep", 1000, 0, pival);
  //  varList.push_back(dPhi_leplep);
  varInfo *dR_leplep = new varInfo("dR_leplep", "dR_leplep", "dR_leplep", 1000, 0, 10);
  varList.push_back(dR_leplep);
  varInfo *dev_from_avg_disc_btags = new varInfo("dev_from_avg_disc_btags", "dev_from_avg_disc_btags", "dev_from_avg_disc_btags", 1000, 0, 1);
  varList.push_back(dev_from_avg_disc_btags);
  varInfo *first_highest_btag = new varInfo("first_highest_btag", "first_highest_btag", "first_highest_btag", 1000, 0, 1);
  varList.push_back(first_highest_btag);
  varInfo *first_jet_pt = new varInfo("first_jet_pt", "first_jet_pt", "first_jet_pt", 1000, 0, 1000);
  varList.push_back(first_jet_pt);
  //  varInfo *fourth_jet_pt = new varInfo("fourth_jet_pt", "fourth_jet_pt", "fourth_jet_pt", 1000, 0, 1000);
  //  varList.push_back(fourth_jet_pt);
  //  varInfo *fstElePt = new varInfo("fstElePt", "fstElePt", "fstElePt", 1000, 0, 1000);
  //  varList.push_back(fstElePt);
  //  varInfo *fstMuPt = new varInfo("fstMuPt", "fstMuPt", "fstMuPt", 1000, 0, 1000);
  //  varList.push_back(fstMuPt);
  varInfo *isTriggerPass = new varInfo("isTriggerPass", "isTriggerPass", "isTriggerPass", 2, 0, 2);
  varList.push_back(isTriggerPass);
  varInfo *isCleanEvent = new varInfo("isCleanEvent", "isCleanEvent", "isCleanEvent", 2, 0, 2);
  varList.push_back(isCleanEvent);
  varInfo *lep1Eta = new varInfo("lep1Eta", "lep1Eta", "lep1Eta", 1000, -5, 5);
  varList.push_back(lep1Eta);
  varInfo *lep1Phi = new varInfo("lep1Phi", "lep1Phi", "lep1Phi", 1000, -pival, pival);
  varList.push_back(lep1Phi);
  varInfo *lep1Pt = new varInfo("lep1Pt", "lep1Pt", "lep1Pt", 1000, 0, 1000);
  varList.push_back(lep1Pt);
  varInfo *lep2Eta = new varInfo("lep2Eta", "lep2Eta", "lep2Eta", 1000, -5, 5);
  varList.push_back(lep2Eta);
  varInfo *lep2Phi = new varInfo("lep2Phi", "lep2Phi", "lep2Phi", 1000, -pival, pival);
  varList.push_back(lep2Phi);
  varInfo *lep2Pt = new varInfo("lep2Pt", "lep2Pt", "lep2Pt", 1000, 0, 1000);
  varList.push_back(lep2Pt);
  varInfo *lowest_btag = new varInfo("lowest_btag", "lowest_btag", "lowest_btag", 1000, 0, 1);
  varList.push_back(lowest_btag);
  varInfo *mass_leplep = new varInfo("mass_leplep", "mass_leplep", "mass_leplep", 1000, 0, 1000);
  varList.push_back(mass_leplep);
  varInfo *mass_of_everything = new varInfo("mass_of_everything", "mass_of_everything", "mass_of_everything", 10000, 0, 10000);
  varList.push_back(mass_of_everything);
  varInfo *met = new varInfo("met", "met", "met", 1000, 0, 1000);
  varList.push_back(met);
  varInfo *min_dr_tagged_jets = new varInfo("min_dr_tagged_jets", "min_dr_tagged_jets", "min_dr_tagged_jets", 1000, 0, 10);
  varList.push_back(min_dr_tagged_jets);
  varInfo *mindr_lep1_jet = new varInfo("mindr_lep1_jet", "mindr_lep1_jet", "mindr_lep1_jet", 1000, 0, 10);
  varList.push_back(mindr_lep1_jet);
  varInfo *mindr_lep2_jet = new varInfo("mindr_lep2_jet", "mindr_lep2_jet", "mindr_lep2_jet", 1000, 0, 10);
  varList.push_back(mindr_lep2_jet);
  varInfo *numJets = new varInfo("numJets", "numJets", "numJets", 10, 0, 10);
  varList.push_back(numJets);
  varInfo *numLooseElectrons = new varInfo("numLooseElectrons", "numLooseElectrons", "numLooseElectrons", 10, 0, 10);
  varList.push_back(numLooseElectrons);
  varInfo *numLooseMuons = new varInfo("numLooseMuons", "numLooseMuons", "numLooseMuons", 10, 0, 10);
  varList.push_back(numLooseMuons);
  //  varInfo *numNonTaggedJets = new varInfo("numNonTaggedJets", "numNonTaggedJets", "numNonTaggedJets", 10, 0, 10);
  //  varList.push_back(numNonTaggedJets);
  varInfo *numPV = new varInfo("numPV", "numPV", "numPV", 50, 0, 50);
  varList.push_back(numPV);
  varInfo *numTaggedJets = new varInfo("numTaggedJets", "numTaggedJets", "numTaggedJets", 10, 0, 10);
  varList.push_back(numTaggedJets);
  varInfo *numTightElectrons = new varInfo("numTightElectrons", "numTightElectrons", "numTightElectrons", 10, 0, 10);
  varList.push_back(numTightElectrons);
  varInfo *numTightMuons = new varInfo("numTightMuons", "numTightMuons", "numTightMuons", 10, 0, 10);
  varList.push_back(numTightMuons);
//   varInfo *prob1 = new varInfo("prob1", "prob1", "prob1", 1000, 0, 10);
//   varList.push_back(prob1);
//   varInfo *prob2 = new varInfo("prob2", "prob2", "prob2", 1000, 0, 10);
//   varList.push_back(prob2);
//   varInfo *probge3 = new varInfo("probge3", "probge3", "probge3", 1000, 0, 10);
//   varList.push_back(probge3);
  varInfo *prob = new varInfo("prob", "prob", "prob", 1000, 0, 10);
  varList.push_back(prob);
  varInfo *pt_leplep = new varInfo("pt_leplep", "pt_leplep", "pt_leplep", 1000, 0, 1000);
  varList.push_back(pt_leplep);
  varInfo *pt_of_everything = new varInfo("pt_of_everything", "pt_of_everything", "pt_of_everything", 10000, 0, 10000);
  varList.push_back(pt_of_everything);
  varInfo *second_highest_btag = new varInfo("second_highest_btag", "second_highest_btag", "second_highest_btag", 1000, 0, 1);
  varList.push_back(second_highest_btag);
  varInfo *second_jet_pt = new varInfo("second_jet_pt", "second_jet_pt", "second_jet_pt", 1000, 0, 1000);
  varList.push_back(second_jet_pt);
  //  varInfo *sndElePt = new varInfo("sndElePt", "sndElePt", "sndElePt", 1000, 0, 1000);
  //  varList.push_back(sndElePt);
  //  varInfo *sndMuPt = new varInfo("sndMuPt", "sndMuPt", "sndMuPt", 1000, 0, 1000);
  //  varList.push_back(sndMuPt);
  varInfo *sum_pt = new varInfo("sum_pt", "sum_pt", "sum_pt", 10000, 0, 10000);
  varList.push_back(sum_pt);
  //  varInfo *third_jet_pt = new varInfo("third_jet_pt", "third_jet_pt", "third_jet_pt", 1000, 0, 1000);
  //  varList.push_back(third_jet_pt);
  //  varInfo *unc_met = new varInfo("unc_met", "unc_met", "unc_met", 1000, 0, 1000);
  //  varList.push_back(unc_met);
  varInfo *weight = new varInfo("weight", "weight", "weight", 1000, 0, 10);
  varList.push_back(weight);

  JetTagReqs.push_back("eq1t");
  JetTagReqs.push_back("eq2jeq2t");
  JetTagReqs.push_back("ge3jeq2t");
  JetTagReqs.push_back("ge3t");

  const unsigned int nJetTagReqs = JetTagReqs.size();

  for( unsigned int k = 0; k < nJetTagReqs; k++) {

    std::string JetTagReq = JetTagReqs[k];

      std::string JetReq = "holder";
      std::string TagReq = "holder";
      std::string ProbStr = "holder";
      std::string EffStr = "holder";
      std::string TrigStr = "holder";
      std::string WeightStr = "holder";
      
      if (JetTagReq == "eq1t") {
        JetReq = "numJets >= 2";
        TagReq = "numTaggedJets == 1";
      }
      else if (JetTagReq == "eq2jeq2t") {
        JetReq = "numJets == 2";
        TagReq = "numTaggedJets == 2";
      }
      else if (JetTagReq == "ge3jeq2t") {
        JetReq = "numJets >= 3";
        TagReq = "numTaggedJets == 2";
      }
      else if (JetTagReq == "ge3t") {
        JetReq = "numJets >= 3";
        TagReq = "numTaggedJets >= 3";
      }
      
      if (JetReq == "holder" || TagReq == "holder") {
        std::cout << "JetReq or TagReq == holder" << std::endl;
        continue;
      }
      
      const unsigned int nOutputDirectories = OutputDirectories.size();
      for( unsigned int j = 0; j < nOutputDirectories; j++) {
        OutputDirectory = OutputDirectories[j];
      
  const unsigned int nInputFiles = InputFileNames.size();
  for( unsigned int i = 0; i < nInputFiles; i++) {

    std::string InputFileLabel = InputFileNames[i];

    if (std::string::npos != InputFileLabel.find("201")) {
      ProbStr = "";
      EffStr = "";
      TrigStr = "";
      WeightStr = "";
      std::cout << "Set prob and weightto 1" << std::endl;
    }
    else {
      WeightStr = "weight * ";
      ProbStr = "prob * ";
//       if (TagReq == "numTaggedJets == 0" || TagReq == "numTaggedJets >= 0") {
//         ProbStr = "prob * ";
//       }
//       else if (TagReq == "numTaggedJets == 1" || TagReq == "numTaggedJets >= 1") {
//         ProbStr = "prob1 * ";
//       }
//       else if (TagReq == "numTaggedJets == 2" || TagReq == "numTaggedJets >= 2") {
//         ProbStr = "prob2 * ";
//       }
//       else if (TagReq == "numTaggedJets == 3" || TagReq == "numTaggedJets >= 3") {
//         ProbStr = "probge3 * ";
//       }
//       else if (TagReq == "numTaggedJets == 4" || TagReq == "numTaggedJets >= 4") {
//         ProbStr == "probge4 * ";
//       }
//       else {
//         std::cout << "No options for ProbStr! continue ..." << std::endl;
//         continue;
//       }
      
      if (OutputDirectory == "rootDiMuonAll/" || "rootDiMuon/" || OutputDirectory == "rootDiMuonLoose/" || OutputDirectory ==  "rootDiMuonZmask10/" || OutputDirectory == "rootDiMuonLooseZmask10/") {
        EffStr = "0.987 * 0.987 * ";
        TrigStr = "0.9885 * 0.9885 * ";
      }
      else if (OutputDirectory ==  "rootDiEleAll/" || "rootDiEle/" || OutputDirectory ==  "rootDiEleLoose/" || OutputDirectory ==  "rootDiEleZmask10/" || OutputDirectory == "rootDiEleLooseZmask10/") {
        EffStr = "1.004 * 1.004 * ";
        TrigStr = "";
      }
      else if (OutputDirectory ==  "rootMuEGAll/" || "rootMuEG/" || OutputDirectory ==  "rootMuEGLoose/" ) {
        EffStr = "0.987 * 1.004 * ";
        TrigStr = "0.9885 * ";
      }
      else {
        std::cout << "No options for EffStr! continue ..." << std::endl;
        continue;
      }
    } 
    
    //TString InputFileName = InputDirName+InputFileLabel+"/test_beans_v1_"+InputFileLabel+"_ALL.root";
    TString InputFileName = InputDirName+InputFileLabel+".root";
    
    std::cout << "==== Processing File " << InputFileLabel << " ==== " << std::endl;
    TFile * DileptonFile = new TFile(InputFileName);
    TTree * DileptonSummaryTree = (TTree *) DileptonFile->Get("summaryTree");

    TString OutputFileName = "holder";
    OutputFileName = OutputDirectory+InputFileLabel+"_"+JetTagReq+"_.root";
    if (OutputFileName == "holder") {
      std::cout << "OutputFileName == holder" << std::endl;
      continue;
    }

    TFile * OutputFile = new TFile(OutputFileName, "RECREATE");

    //double Dilepton_numEvents = DileptonSummaryTree->GetEntries();

    OutputFile->cd();

    for(std::vector<varInfo*>::iterator tIter1 = varList.begin(); tIter1 != varList.end(); tIter1++) {
     
      // Pass a pointer to variable info
      varInfo *u = *tIter1;

      //Selection string: ==2 tags or >=3 tags; DiMu, DiEle, MuEG, or DiMuZmask10
      std::string SelectionStr = "holder";
      std::string CleanTrig = "holder";
      if (u->hName == "isCleanEvent" || u->hName == "isTriggerPass") {
        CleanTrig = "";
      }
      else {
        CleanTrig = "(isCleanEvent == 1) && (isTriggerPass == 1) && ";
      }

      if (OutputDirectory == "rootDiMuon/") {
        SelectionStr = WeightStr+ProbStr+EffStr+TrigStr+"( (numTightMuons == 2) && (numLooseMuons == 0) && (numTightElectrons == 0) && (numLooseElectrons == 0) && (dR_leplep > 0.2) && (mass_leplep > 12) && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
      }
      else if (OutputDirectory == "rootDiMuonLoose/") {
        SelectionStr = WeightStr+ProbStr+EffStr+TrigStr+"( (numTightMuons == 1) && (numLooseMuons == 1) && (numTightElectrons == 0) && (numLooseElectrons == 0) && (dR_leplep > 0.2) && (mass_leplep > 12) && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
      }
      else if (OutputDirectory == "rootDiMuonAll/") {
        SelectionStr = WeightStr+ProbStr+EffStr+TrigStr+"( (numTightMuons >= 1) && (numTightMuons + numLooseMuons == 2) && (numTightElectrons == 0) && (numLooseElectrons == 0) && (dR_leplep > 0.2) && (mass_leplep > 12) && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
      }
      else if (OutputDirectory == "rootDiEle/") {
        SelectionStr = WeightStr+ProbStr+EffStr+TrigStr+"( (numTightMuons == 0) && (numLooseMuons == 0) && (numTightElectrons == 2) && (numLooseElectrons == 0) && (dR_leplep > 0.2) && (mass_leplep > 12) && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
      }
      else if (OutputDirectory == "rootDiEleLoose/") {
        SelectionStr = WeightStr+ProbStr+EffStr+TrigStr+"( (numTightMuons == 0) && (numLooseMuons == 0) && (numTightElectrons == 1) && (numLooseElectrons == 1) && (dR_leplep > 0.2) && (mass_leplep > 12) && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
      }
      else if (OutputDirectory == "rootDiEleAll/") {
        SelectionStr = WeightStr+ProbStr+EffStr+TrigStr+"( (numTightMuons == 0) && (numLooseMuons == 0) && (numTightElectrons >= 1) && (numTightElectrons + numLooseElectrons == 2) && (dR_leplep > 0.2) && (mass_leplep > 12) && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
      }
      else if (OutputDirectory == "rootMuEG/") {
        SelectionStr = WeightStr+ProbStr+EffStr+TrigStr+"( (numTightMuons == 1) && (numLooseMuons == 0) && (numTightElectrons == 1) && (numLooseElectrons == 0) && (dR_leplep > 0.2) && (mass_leplep > 12) && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
      }
      else if (OutputDirectory == "rootMuEGLoose/") {
        SelectionStr = WeightStr+ProbStr+EffStr+TrigStr+"( (numTightMuons + numTightElectrons == 1) && (numLooseMuons + numLooseElectrons == 1) && (numTightMuons != numLooseMuons)  && (dR_leplep > 0.2) && (mass_leplep > 12) && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
      }
      else if (OutputDirectory == "rootMuEGAll/") {
        SelectionStr = WeightStr+ProbStr+EffStr+TrigStr+"( (numTightMuons + numLooseMuons == 1) && (numTightElectrons + numLooseElectrons == 1) && (numTightMuons + numTightElectrons >= 1)  && (dR_leplep > 0.2) && (mass_leplep > 12) && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
      }     
      else if (OutputDirectory == "rootDiMuonZmask10/") {
        SelectionStr = WeightStr+ProbStr+EffStr+TrigStr+"( ((mass_leplep <= 81.2) || (mass_leplep >= 101.2))  && (numTightMuons == 2) && (numLooseMuons == 0) && (numTightElectrons == 0) && (numLooseElectrons == 0) && (dR_leplep > 0.2) && (mass_leplep > 12) && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
      }
      else if (OutputDirectory == "rootDiEleZmask10/") {
        SelectionStr = WeightStr+ProbStr+EffStr+TrigStr+"( ((mass_leplep <= 81.2) || (mass_leplep >= 101.2))  && (numTightMuons == 0) && (numLooseMuons == 0) && (numTightElectrons == 2) && (dR_leplep > 0.2) && (mass_leplep > 12) && (numLooseElectrons == 0) && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
      }
      else if (OutputDirectory == "rootDiMuonLooseZmask10/") {
        SelectionStr = WeightStr+ProbStr+EffStr+TrigStr+"( ((mass_leplep <= 81.2) || (mass_leplep >= 101.2))  && (numTightMuons == 1) && (numLooseMuons == 1) && (numTightElectrons == 0) && (numLooseElectrons == 0) && (dR_leplep > 0.2) && (mass_leplep > 12) && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
      }
      else if (OutputDirectory == "rootDiEleLooseZmask10/") {
        SelectionStr = WeightStr+ProbStr+EffStr+TrigStr+"( ((mass_leplep <= 81.2) || (mass_leplep >= 101.2))  && (numTightMuons == 0) && (numLooseMuons == 0) && (numTightElectrons == 1) && (numLooseElectrons ==1) && (dR_leplep > 0.2) && (mass_leplep > 12) && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
      }

      if (SelectionStr == "holder") {
        std::cout << "SelectionStr == holder" << std::endl;
        continue;
      }

      std::stringstream s3;
      std::stringstream s4;
      std::stringstream s5;
      s3 << u->nBins;
      s4 << u->min;
      s5 << u->max;
      TString n3 = s3.str();
      TString n4 = s4.str();
      TString n5 = s5.str();

      //double Integral = 0;
      //SelectionStr = "(isTriggerPass >= 0)";
      DileptonSummaryTree->Draw(u->hName+">>"+u->hName+"("+n3+","+n4+","+n5+")",SelectionStr.c_str(),"goff");
      //std::cout << OutputFileName << "  " << Integral << std::endl;
      
      std::cout << "Drawing histogram " << u->hName << std::endl;
    }

    OutputFile->Write();
    std::cout << "Wrote out " << OutputFileName << std::endl;
    OutputFile->Close();
  } // end files loop
      }// end OutputDirectories loop
} // end JetTagReqs loop
  // Write and close output file
}
