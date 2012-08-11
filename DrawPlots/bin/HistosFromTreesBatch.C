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

#include "TFile.h"
#include "TChain.h"
#include "TH1.h"
#include "TH3.h"
#include "TH2F.h"
#include "TF1.h"
#include "TF2.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TPaveStats.h"
#include "TAxis.h"
#include "TMath.h"
#include "TRandom3.h"
#include <iostream>
#include <vector>
#include <cmath> 
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include "TGraphAsymmErrors.h"

#include "FWCore/FWLite/interface/AutoLibraryLoader.h"


#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/FWLite/interface/ChainEvent.h"


// headers for python config processing

#include "FWCore/PythonParameterSet/interface/PythonProcessDesc.h"
#include "FWCore/ParameterSet/interface/ProcessDesc.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"


using std::string;
using std::cout;
using std::endl;


class varInfo {

public:
  TString var;
  TString hName;
  TString hTitle;
  int nBins;
  double min;
  double max;

  
  varInfo(): var(""), hName(""), hTitle(""), nBins(0), min(0), max(0) {}

  varInfo(TString varName, TString histName, TString histTitle, int numBins, double binMin, double binMax) : 
    var(varName), hName(histName), hTitle(histTitle), nBins(numBins), min(binMin), max(binMax) {}

};

int main ( int argc, char ** argv )
{


  //////////////////////////////////////////////////////////////////
   //
   // Get the python configuration
   //
   // Configuration will have
   //   1. a process object that everyhting is attached to
   //   2. various parameter sets, including input and output
   //  
   /////////////////////////////////////////////////////////////////////
   
   cout << "Unpacking configuation parameters." << endl;
   PythonProcessDesc builder(argv[1],argc,argv);

   edm::ParameterSet const& inputs = builder.processDesc()->getProcessPSet()->getParameter<edm::ParameterSet>("inputs");
   //edm::ParameterSet const& outputs = builder.processDesc()->getProcessPSet()->getParameter<edm::ParameterSet>("outputs");
   edm::ParameterSet const& anaParams = builder.processDesc()->getProcessPSet()->getParameter<edm::ParameterSet>("dilAnalysis");

   std::string treeFileNameNominal = inputs.getParameter< std::string >("fileName");
   std::string treeFileNameJESUp = inputs.getParameter< std::string >("fileNameJESUp");
   std::string treeFileNameJESDown = inputs.getParameter< std::string >("fileNameJESDown");
   std::string treeFileNameJERUp = inputs.getParameter< std::string >("fileNameJERUp");
   std::string treeFileNameJERDown = inputs.getParameter< std::string >("fileNameJERDown");
   std::string inputYear = inputs.getParameter< std::string >("inputYear");
   std::string inputZmask = inputs.getParameter< std::string >("inputZmask");
   

   

   //JES
   //int jes = anaParams.getParameter<int> ("jes");
   //int jer = anaParams.getParameter<int> ("jer");
   std::string sampleName = anaParams.getParameter<string>("sampleName");

   //std::cout <<"CONFIG: using jes = " << jes << " jer = " << jer << std::endl;

   // std::string JesJerStr = "";
   //    if (jes == 1) {
   //      JesJerStr = "_JesUp";
   //    }
   //    if (jes == -1) {
   //      JesJerStr = "_JesDown";
   //    }
   //    if (jer == 1) {
   //      JesJerStr = "_JerUp";
   //    }
   //    if (jer == -1) {
   //      JesJerStr = "_JerDown";
   //    }

   

   //int maxNentries = inputs.getParameter<int> ("maxEvents");

  

  //----------------------------------
  //
  //  Global job params
  //  File names, etc
  //---------------------------------
  
  std::string OutputDirectory = "holder/";

  //////////
  std::vector<string> JetTagReqs;
  JetTagReqs.push_back("eq1t");
  JetTagReqs.push_back("eq2jeq2t");
  JetTagReqs.push_back("eq3jeq2t");
  JetTagReqs.push_back("ge4jeq2t");
  JetTagReqs.push_back("ge3t");

  const unsigned int nJetTagReqs = JetTagReqs.size();

  ////////  sub lepton category
  std::vector<string> lepCatList;
  lepCatList.push_back("TwoMuon"); 
  lepCatList.push_back("TwoEle");
  lepCatList.push_back("MuonEle");
  
  ///////   systematics
  std::vector< TString > sysList ;
  sysList.push_back("CMS_scale_jUp");
  sysList.push_back("CMS_scale_jDown");
  sysList.push_back("");
  sysList.push_back("PUUp");
  sysList.push_back("PUDown");
  sysList.push_back("CMS_eff_bUp");
  sysList.push_back("CMS_eff_bDown");
  sysList.push_back("CMS_fake_bUp");
  sysList.push_back("CMS_fake_bDown");
  const unsigned int NumSys = sysList.size();

  ////////// prepare the weight
  vector<std::string> weight(NumSys, std::string(""));
  weight[0] = "weight*prob*"  ;
  weight[1] = "weight*prob*"  ;
  weight[2] = "weight*prob*"  ;
  
  weight[3] = "weight_PUup*prob*"  ;
  weight[4] = "weight_PUdown*prob*"  ;
  
  weight[5] = "weight*prob_hfSFup*";
  weight[6] = "weight*prob_hfSFdown*";
  weight[7] = "weight*prob_lfSFup*";
  weight[8] = "weight*prob_lfSFdown*";


  /////////// samples
  std::vector<string> InputFileNames;
  InputFileNames.push_back(sampleName);
  


  ////////////////////
  std::vector<varInfo*> varList;
  double pival = 3.14;
  
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
  varInfo *CFMlpANN_e2je2t = new varInfo("CFMlpANN_e2je2t", "CFMlpANN_e2je2t", "CFMlpANN_e2je2t", 1000, 0.007, 0.008);
  varList.push_back(CFMlpANN_e2je2t);
  varInfo *CFMlpANN_ge3t = new varInfo("CFMlpANN_ge3t", "CFMlpANN_ge3t", "CFMlpANN_ge3t", 1000, 0, 1);
  varList.push_back(CFMlpANN_ge3t);
  varInfo *CFMlpANN_ge3t_new = new varInfo("CFMlpANN_ge3t_new", "CFMlpANN_ge3t_new", "CFMlpANN_ge3t_new", 1000, 0, 1);
  varList.push_back(CFMlpANN_ge3t_new);
  varInfo *CFMlpANN_e3je2t = new varInfo("CFMlpANN_e3je2t", "CFMlpANN_e3je2t", "CFMlpANN_e3je2t", 1000, 0, 1);
  varList.push_back(CFMlpANN_e3je2t);
  varInfo *CFMlpANN_ge4je2t = new varInfo("CFMlpANN_ge4je2t", "CFMlpANN_ge4je2t", "CFMlpANN_ge4je2t", 1000, 0, 1);
  varList.push_back(CFMlpANN_ge4je2t);
  varInfo *CFMlpANN_var_best8 = new varInfo("CFMlpANN_var_best8", "CFMlpANN_var_best8", "CFMlpANN_var_best8", 1000, 0, 1);
  varList.push_back(CFMlpANN_var_best8);
  varInfo *closest_tagged_dijet_mass = new varInfo("closest_tagged_dijet_mass", "closest_tagged_dijet_mass", "closest_tagged_dijet_mass", 1000, 0, 1000);
  varList.push_back(closest_tagged_dijet_mass);
  varInfo *correctedDZ_leplep = new varInfo("correctedDZ_leplep", "correctedDZ_leplep", "correctedDZ_leplep", 1000, -0.5, 0.5);
  varList.push_back(correctedDZ_leplep);
  varInfo *dEta_leplep = new varInfo("dEta_leplep", "dEta_leplep", "dEta_leplep", 1000, -5, 5);
  varList.push_back(dEta_leplep);
  varInfo *dPhi_leplep = new varInfo("dPhi_leplep", "dPhi_leplep", "dPhi_leplep", 1000, -1*pival, pival);
  varList.push_back(dPhi_leplep);
  varInfo *dijet_mass_first = new varInfo("dijet_mass_first", "dijet_mass_first", "dijet_mass_first", 1000, 0, 1000);
  varList.push_back(dijet_mass_first);
  varInfo *dijet_mass_m2H = new varInfo("dijet_mass_m2H", "dijet_mass_m2H", "dijet_mass_m2H", 1000, 0, 1000);
  varList.push_back(dijet_mass_m2H);
  varInfo *dijet_mass_second = new varInfo("dijet_mass_second", "dijet_mass_second", "dijet_mass_second", 1000, 0, 1000);
  varList.push_back(dijet_mass_second);
  varInfo *dijet_mass_third = new varInfo("dijet_mass_third", "dijet_mass_third", "dijet_mass_third", 1000, 0, 1000);
  varList.push_back(dijet_mass_third);
  varInfo *dR_leplep = new varInfo("dR_leplep", "dR_leplep", "dR_leplep", 1000, 0, 10);
  varList.push_back(dR_leplep);
  varInfo *dev_from_avg_disc_btags = new varInfo("dev_from_avg_disc_btags", "dev_from_avg_disc_btags", "dev_from_avg_disc_btags", 1000, 0, 1);
  varList.push_back(dev_from_avg_disc_btags);
  varInfo *first_dibjet_mass = new varInfo("first_dibjet_mass", "first_dibjet_mass", "first_dibjet_mass", 1000, 0, 1000);
  varList.push_back(first_dibjet_mass);
  varInfo *first_highest_btag = new varInfo("first_highest_btag", "first_highest_btag", "first_highest_btag", 1000, 0, 1);
  varList.push_back(first_highest_btag);
  varInfo *first_jet_eta = new varInfo("first_jet_eta", "first_jet_eta", "first_jet_eta", 1000, -5, 5);
  varList.push_back(first_jet_eta);
  varInfo *first_jet_pt = new varInfo("first_jet_pt", "first_jet_pt", "first_jet_pt", 1000, 0, 1000);
  varList.push_back(first_jet_pt);
  varInfo *fourth_allJet_pt = new varInfo("fourth_allJet_pt", "fourth_allJet_pt", "fourth_allJet_pt", 1000, 0, 1000);
  varList.push_back(fourth_allJet_pt);
  varInfo *fourth_jet_eta = new varInfo("fourth_jet_eta", "fourth_jet_eta", "fourth_jet_eta", 1000, -5, 5);
  varList.push_back(fourth_jet_eta);
  varInfo *fourth_jet_pt = new varInfo("fourth_jet_pt", "fourth_jet_pt", "fourth_jet_pt", 1000, 0, 1000);
  varList.push_back(fourth_jet_pt);
  varInfo *higgsLike_dijet_mass = new varInfo("higgsLike_dijet_mass", "higgsLike_dijet_mass", "higgsLike_dijet_mass", 1000, 0, 1000);
  varList.push_back(higgsLike_dijet_mass);
  varInfo *higgsLike_allDijet_mass = new varInfo("higgsLike_allDijet_mass", "higgsLike_allDijet_mass", "higgsLike_allDijet_mass", 1000, 0, 1000);
  varList.push_back(higgsLike_allDijet_mass);
  varInfo *Ht = new varInfo("Ht", "Ht", "Ht", 1000, 0, 10000);
  varList.push_back(Ht);
  //   varInfo *isTriggerPass = new varInfo("isTriggerPass", "isTriggerPass", "isTriggerPass", 2, 0, 2);
//   varList.push_back(isTriggerPass);
//   varInfo *isCleanEvent = new varInfo("isCleanEvent", "isCleanEvent", "isCleanEvent", 2, 0, 2);
//   varList.push_back(isCleanEvent);
  varInfo *lep1Eta = new varInfo("lep1Eta", "lep1Eta", "lep1Eta", 1000, -5, 5);
  varList.push_back(lep1Eta);
  varInfo *lep1Phi = new varInfo("lep1Phi", "lep1Phi", "lep1Phi", 1000, -1*pival, pival);
  varList.push_back(lep1Phi);
  varInfo *lep1Pt = new varInfo("lep1Pt", "lep1Pt", "lep1Pt", 1000, 0, 1000);
  varList.push_back(lep1Pt);
  varInfo *lep2Eta = new varInfo("lep2Eta", "lep2Eta", "lep2Eta", 1000, -5, 5);
  varList.push_back(lep2Eta);
  varInfo *lep2Phi = new varInfo("lep2Phi", "lep2Phi", "lep2Phi", 1000, -1*pival, pival);
  varList.push_back(lep2Phi);
  varInfo *lep2Pt = new varInfo("lep2Pt", "lep2Pt", "lep2Pt", 1000, 0, 1000);
  varList.push_back(lep2Pt);
  varInfo *lowest_btag = new varInfo("lowest_btag", "lowest_btag", "lowest_btag", 1000, 0, 1);
  varList.push_back(lowest_btag);
  varInfo *m2H_btag = new varInfo("m2H_btag", "m2H_btag", "m2H_btag", 1000, 0, 1000);
  varList.push_back(m2H_btag);
  varInfo *mass_leplep = new varInfo("mass_leplep", "mass_leplep", "mass_leplep", 1000, 0, 1000);
  varList.push_back(mass_leplep);
  varInfo *mass_MHT = new varInfo("mass_MHT", "mass_MHT", "mass_MHT", 10000, 0, 10000);
  varList.push_back(mass_MHT);
  //varInfo *mass_of_everything = new varInfo("mass_of_everything", "mass_of_everything", "mass_of_everything", 10000, 0, 10000);
  //varList.push_back(mass_of_everything);
  varInfo *mass_of_leps_and_allJets = new varInfo("mass_of_leps_and_allJets", "mass_of_leps_and_allJets", "mass_of_leps_and_allJets", 10000, 0, 10000);
  varList.push_back(mass_of_leps_and_allJets);
  varInfo *met = new varInfo("met", "met", "met", 1000, 0, 1000);
  varList.push_back(met);
  varInfo *MHT = new varInfo("MHT", "MHT", "MHT", 1000, 0, 1000);
  varList.push_back(MHT);
  varInfo *min_dr_tagged_jets = new varInfo("min_dr_tagged_jets", "min_dr_tagged_jets", "min_dr_tagged_jets", 1000, 0, 10);
  varList.push_back(min_dr_tagged_jets);
  varInfo *mindr_lep1_jet = new varInfo("mindr_lep1_jet", "mindr_lep1_jet", "mindr_lep1_jet", 1000, 0, 10);
  varList.push_back(mindr_lep1_jet);
  varInfo *mindr_lep2_jet = new varInfo("mindr_lep2_jet", "mindr_lep2_jet", "mindr_lep2_jet", 1000, 0, 10);
  varList.push_back(mindr_lep2_jet);
  varInfo *numAllJets = new varInfo("numAllJets", "numAllJets", "numAllJets", 20, 0, 20);
  varList.push_back(numAllJets);
  varInfo *numBadJets = new varInfo("numBadJets", "numBadJets", "numBadJets", 20, 0, 20);
  varList.push_back(numBadJets);
  varInfo *numJets = new varInfo("numJets", "numJets", "numJets", 10, 0, 10);
  varList.push_back(numJets);
//   varInfo *numLooseElectrons = new varInfo("numLooseElectrons", "numLooseElectrons", "numLooseElectrons", 10, 0, 10);
//   varList.push_back(numLooseElectrons);
//   varInfo *numLooseMuons = new varInfo("numLooseMuons", "numLooseMuons", "numLooseMuons", 10, 0, 10);
//   varList.push_back(numLooseMuons);
  varInfo *numNonTaggedJets = new varInfo("numNonTaggedJets", "numNonTaggedJets", "numNonTaggedJets", 10, 0, 10);
  varList.push_back(numNonTaggedJets);
  varInfo *numPV = new varInfo("numPV", "numPV", "numPV", 50, 0, 50);
  varList.push_back(numPV);
  varInfo *numTaggedJets = new varInfo("numTaggedJets", "numTaggedJets", "numTaggedJets", 10, 0, 10);
  varList.push_back(numTaggedJets);
//   varInfo *numTightElectrons = new varInfo("numTightElectrons", "numTightElectrons", "numTightElectrons", 10, 0, 10);
//   varList.push_back(numTightElectrons);
//   varInfo *numTightMuons = new varInfo("numTightMuons", "numTightMuons", "numTightMuons", 10, 0, 10);
//   varList.push_back(numTightMuons);
//   varInfo *prob1 = new varInfo("prob1", "prob1", "prob1", 1000, 0, 10);
//   varList.push_back(prob1);
//   varInfo *prob2 = new varInfo("prob2", "prob2", "prob2", 1000, 0, 10);
//   varList.push_back(prob2);
//   varInfo *probge3 = new varInfo("probge3", "probge3", "probge3", 1000, 0, 10);
//   varList.push_back(probge3);
  varInfo *pt_leplep = new varInfo("pt_leplep", "pt_leplep", "pt_leplep", 1000, 0, 1000);
  varList.push_back(pt_leplep);
  //varInfo *pt_of_everything = new varInfo("pt_of_everything", "pt_of_everything", "pt_of_everything", 10000, 0, 10000);
  //varList.push_back(pt_of_everything);
  varInfo *pt_of_leps_and_allJets = new varInfo("pt_of_leps_and_allJets", "pt_of_leps_and_allJets", "pt_of_leps_and_allJets", 10000, 0, 10000);
  varList.push_back(pt_of_leps_and_allJets);
  varInfo *second_dibjet_mass = new varInfo("second_dibjet_mass", "second_dibjet_mass", "second_dibjet_mass", 1000, 0, 1000);
  varList.push_back(second_dibjet_mass);
  varInfo *second_highest_btag = new varInfo("second_highest_btag", "second_highest_btag", "second_highest_btag", 1000, 0, 1);
  varList.push_back(second_highest_btag);
  varInfo *second_jet_eta = new varInfo("second_jet_eta", "second_jet_eta", "second_jet_eta", 1000, -5, 5);
  varList.push_back(second_jet_eta);
  varInfo *second_jet_pt = new varInfo("second_jet_pt", "second_jet_pt", "second_jet_pt", 1000, 0, 1000);
  varList.push_back(second_jet_pt);
  //  varInfo *sndElePt = new varInfo("sndElePt", "sndElePt", "sndElePt", 1000, 0, 1000);
  //  varList.push_back(sndElePt);
  //  varInfo *sndMuPt = new varInfo("sndMuPt", "sndMuPt", "sndMuPt", 1000, 0, 1000);
  //  varList.push_back(sndMuPt);
  varInfo *sum_pt = new varInfo("sum_pt", "sum_pt", "sum_pt", 10000, 0, 10000);
  varList.push_back(sum_pt);
  varInfo *third_dibjet_mass = new varInfo("third_dibjet_mass", "third_dibjet_mass", "third_dibjet_mass", 1000, 0, 1000);
  varList.push_back(third_dibjet_mass);
  varInfo *third_jet_eta = new varInfo("third_jet_eta", "third_jet_eta", "third_jet_eta", 1000, -5, 5);
  varList.push_back(third_jet_eta);
  varInfo *third_jet_pt = new varInfo("third_jet_pt", "third_jet_pt", "third_jet_pt", 1000, 0, 1000);
  varList.push_back(third_jet_pt);
  //  varInfo *unc_met = new varInfo("unc_met", "unc_met", "unc_met", 1000, 0, 1000);
  //  varList.push_back(unc_met);
//   varInfo *weight = new varInfo("weight", "weight", "weight", 1000, 0, 10);
//   varList.push_back(weight);

  std::string OutputParams = "";
  //std::string TightLepStr = "(numTightMuons + numTightElectrons == 2) && "; //Only tight leptons
  //std::string TightLepStr = "(numTightMuons + numTightElectrons != 2) && "; //Only tight+loose events
  std::string OppositeLepStr = "(oppositeLepCharge == 1) && "; //Leptons have opposite charge
  //std::string OppositeLepStr = "(oppositeLepCharge == 0) && "; //Leptons have same charge
  //std::string OppositeLepStr = "(oppositeGenLepCharge == 0) && "; //GenLeptons have same charge
  //std::string OppositeLepStr = "(lep1TkCharge != lep1GenCharge) && "; //Lep1 wrong charge
  
  std::string ZmaskStr = "";
  std::string TightLepStr = "";
  
  if (inputZmask == "noZmask") {
    OutputParams = OutputParams+"noZmask";
    ZmaskStr = "";
  }
  if (inputZmask == "Zmask") {
    OutputParams = OutputParams+"Zmask";
    ZmaskStr = "PassZmask == 1 && "; //Events outside the mask (reduced Zjets)
  }
  if (inputZmask == "Zpeak") {
    OutputParams = OutputParams+"Zpeak";
    std::string ZmaskStr = "PassZmask == 0 && "; //Events inside the mask (mostly Zjets)
  }
  
  if (OppositeLepStr == "(oppositeLepCharge == 0) && ") OutputParams = OutputParams+"SameCharge";
  if (OppositeLepStr == "(oppositeGenLepCharge == 0) && ") OutputParams = OutputParams+"SameGenCharge";
  if (OppositeLepStr == "(lep1TkCharge != lep1GenCharge) && ") OutputParams = OutputParams+"WrongCharge";

  std::map<TString, TFile*> outputRootFiles;
  for (unsigned iTag = 0; iTag < JetTagReqs.size(); iTag++){
    for (unsigned iLep = 0; iLep < lepCatList.size(); iLep++){
      std::string JetTagReq = JetTagReqs[iTag];
      OutputDirectory = lepCatList[iLep];
      std::string InputFileLabel = InputFileNames[0];
      ////////  book only a few histogram folders
      TString OutputFileName = "../" + OutputDirectory + "/" + InputFileLabel + "_" + inputYear + "_" + OutputParams + "_" + JetTagReq + "_" + OutputDirectory + ".root";
      TFile * OutputFile = new TFile(OutputFileName, "RECREATE");
      std::cout << "Storing root file named " << OutputFileName << std::endl;
      outputRootFiles[OutputFileName] = OutputFile;
    }
  }


  ////////// start sample loop
  const unsigned int nInputFiles = InputFileNames.size();
  for( unsigned int i = 0; i < nInputFiles; i++) {
    
    std::string InputFileLabel = InputFileNames[i];

    std::cout << "==== Processing Sample " << InputFileLabel << " ====" << std::endl;

    bool isData = false;
    
    if (std::string::npos != InputFileLabel.find("DoubleMu") ||
        std::string::npos != InputFileLabel.find("DoubleEle") ||
        std::string::npos != InputFileLabel.find("MuEG") ||
        std::string::npos != InputFileLabel.find("data") ) {
      isData = true;
    }

    for (unsigned int ksys = 0 ; ksys < NumSys ; ++ksys ){
      if (isData && ksys!=2) continue;
      TString syst = sysList[ksys];
      std::cout << "  == start systematic " << syst << " ==  " << std::endl;

      TString InputFileName = treeFileNameNominal;

      if (ksys == 0 ) {
        //InputFileName = "_JESUp.root" ;
        InputFileName = treeFileNameJESUp;
      }
      else if (ksys == 1 ) {
        //InputFileName += "_JESDown.root" ;
        InputFileName = treeFileNameJESDown;
      }
      //else  InputFileName += ".root" ;
      
      std::cout << "Looking for file " << InputFileName << std::endl;
      TFile * DileptonFile = new TFile(InputFileName);

      if (DileptonFile->IsZombie()) {
        std::cout << "ERROR: Can't find the file," << InputFileName <<  ", sorry... quitting" << std::endl;
        return -22;
      }
    
    TTree * DileptonSummaryTree = (TTree *) DileptonFile->Get("summaryTree");


    ///////////////////////// start category loop    
    for( unsigned int k = 0; k < nJetTagReqs; k++) {
      
      std::string JetTagReq = JetTagReqs[k];
      std::cout << "  ==>start category " << JetTagReq.c_str() << std::endl;
      
      std::string JetReq = "holder";
      std::string TagReq = "holder";
      //      std::string ProbStr = "holder";
      std::string WeightStr = "holder";


      std::string EffStr = "holder";
      std::string TrigStr = "holder";
      
      if (JetTagReq == "eq1t") {
        JetReq = "numJets >= 2";
        TagReq = "numTaggedJets == 1";
      }
      else if (JetTagReq == "eq2jeq2t") {
        JetReq = "numJets == 2";
        TagReq = "numTaggedJets == 2";
      }
      else if (JetTagReq == "eq3jeq2t") {
        JetReq = "numJets == 3";
        TagReq = "numTaggedJets == 2";
      }
      else if (JetTagReq == "ge4jeq2t") {
        JetReq = "numJets >= 4";
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

      //      ProbStr = "prob * ";
      WeightStr = weight[ksys] ;

      /////// start sub-lepton category loop    
      const unsigned int nlepCatList = lepCatList.size();
      for( unsigned int j = 0; j < nlepCatList; j++) {
        OutputDirectory = lepCatList[j];
        std::cout << "    ==>start sub-lep category " << OutputDirectory.c_str() << std::endl;
        if (OutputDirectory == "TwoMuon" ) {
          EffStr = "0.987 * 0.987 * ";
          TrigStr = "0.9885 * 0.9885 * ";
        }
        else if (OutputDirectory ==  "TwoEle" ) {
          EffStr = "1.004 * 1.004 * ";
          TrigStr = "";
        }
        else if (OutputDirectory ==  "MuonEle"  ) {
          EffStr = "0.987 * 1.004 * ";
          TrigStr = "0.9885 * ";
        }
	
        ////////////// no weight, SF for data
        if (isData) {

          //	if (std::string::npos != InputFileLabel.find("data")){
          //	  ProbStr = "";
          WeightStr = "";
          EffStr = "";
          TrigStr = "";
          std::cout << "DATA DETECTED: Set prob, weight, and eff to 1" << std::endl;
        }
    

        ////////  book only a few histogram folders
        //TString OutputFileName = "holder";
        //OutputFileName = "../" + OutputParams + OutputDirectory + "/" + InputFileLabel + "_" + inputYear + "_" + JetTagReq + "_" + OutputDirectory + ".root";
        //TFile * OutputFile = new TFile(OutputFileName, "UPDATE");
        TString OutputFileName = "../" + OutputDirectory + "/" + InputFileLabel + "_" + inputYear + "_" + OutputParams + "_" + JetTagReq + "_" + OutputDirectory + ".root";
        TFile * OutputFile = outputRootFiles[OutputFileName];

        cout << "Switching to output file" << OutputFile->GetName() << std::endl;
        OutputFile->cd();

        ///// start variables loop
        for(std::vector<varInfo*>::iterator tIter1 = varList.begin(); tIter1 != varList.end(); tIter1++) {

          varInfo *u = *tIter1;
          int nBins = u->nBins;
          double Xmin = u->min;
          double Xmax = u->max;
          TString histName = u->hName ;
          TString variableName = u->hName ;

          //update the histogram name based on systematic
          if (ksys != 2){
            histName = histName + TString("_") + syst;
          }

          ///// selection cuts
          //Selection string
          std::string SelectionStr = "holder";
          std::string CleanTrig = "holder";
          CleanTrig = "(isTriggerPass == 1) && ";
          if (inputYear == "2011") {
            CleanTrig = "(isCleanEvent == 1) && (isTriggerPass == 1) && ";
          }
          if (OutputDirectory == "MuonEle") {
            ZmaskStr = "";
          }
          SelectionStr = WeightStr+EffStr+TrigStr +"(" + OppositeLepStr + ZmaskStr + TightLepStr + " ("+ OutputDirectory +") && (dR_leplep > 0.2) && (mass_leplep > 12) && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
	  	    
          if (SelectionStr == "holder") {
            std::cout << "SelectionStr == holder" << std::endl;
            continue;
          }

          TH1F *histTemp = new TH1F(histName, histName , nBins, Xmin, Xmax);
          TString varSig =  variableName + ">>" + histName;

          DileptonSummaryTree->Draw(varSig, SelectionStr.c_str(), "goff");
          //	  DileptonSummaryTree->Draw(u->hName+">>"+u->hName+"("+n3+","+n4+","+n5+")",SelectionStr.c_str(),"goff");
          //      	  std::cout << "Drawing histogram " << histName << std::endl;
          histTemp->SetDirectory(OutputFile);
        } // end var loop
      } // end sub-lep cat loop
      std::cout << '\n' ;
    }// end Cat loop

    DileptonFile->Close();
    
    std::cout << "  == End systematic " << syst << " ==  " << std::endl;
    } // end sys
  } // end sample loop

  //Close all the files
  for (unsigned iTag = 0; iTag < JetTagReqs.size(); iTag++){
    for (unsigned iLep = 0; iLep < lepCatList.size(); iLep++){
      std::string JetTagReq = JetTagReqs[iTag];
      OutputDirectory = lepCatList[iLep];
      std::string InputFileLabel = InputFileNames[0];
      ////////  book only a few histogram folders
      TString OutputFileName = "../" + OutputDirectory + "/" + InputFileLabel + "_" + inputYear + "_" + OutputParams + "_" + JetTagReq + "_" + OutputDirectory + ".root";
      
      std::cout << "Closing root file named " << OutputFileName << std::endl;
      outputRootFiles[OutputFileName]->Write();
      outputRootFiles[OutputFileName]->Close();
      
      
    }
  }
}// end main
