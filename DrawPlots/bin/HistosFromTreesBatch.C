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

   std::string treeFile = inputs.getParameter< std::string >("fileName");

   //JES
   int jes = anaParams.getParameter<int> ("jes");
   int jer = anaParams.getParameter<int> ("jer");
   std::string sampleName = anaParams.getParameter<string>("sampleName");

   std::cout <<"CONFIG: using jes = " << jes << " jer = " << jer << std::endl;


   

   //int maxNentries = inputs.getParameter<int> ("maxEvents");

  

  //----------------------------------
  //
  //  Global job params
  //  File names, etc
  //---------------------------------
  
  std::string InputDirName = "../treeFiles/";

  std::string OutputDirectory = "holder/";

  //////////
  std::vector<string> JetTagReqs;
  JetTagReqs.push_back("eq1t");
  JetTagReqs.push_back("eq2jeq2t");
  JetTagReqs.push_back("ge3t");

  const unsigned int nJetTagReqs = JetTagReqs.size();

  ////////  sub lepton category
  std::vector<string> lepCatList;
  lepCatList.push_back("TwoMuon"); 
  lepCatList.push_back("TwoEle");
  lepCatList.push_back("MuonEle");
  

  /////////// samples
  std::vector<string> InputFileNames;
  InputFileNames.push_back(sampleName);
  
  // InputFileNames.push_back("DoubleElectron_Run2011A-05Aug2011-v1");
//   InputFileNames.push_back("DoubleElectron_Run2011A-May10ReReco-v1");
//   InputFileNames.push_back("DoubleElectron_Run2011A-PromptReco-v4");
//   InputFileNames.push_back("DoubleElectron_Run2011A-PromptReco-v6");
//   InputFileNames.push_back("DoubleElectron_Run2011B-PromptReco-v1");
//   InputFileNames.push_back("DoubleMu_Run2011A-05Aug2011-v1");
//   InputFileNames.push_back("DoubleMu_Run2011A-May10ReReco-v1");
//   InputFileNames.push_back("DoubleMu_Run2011A-PromptReco-v4");
//   InputFileNames.push_back("DoubleMu_Run2011A-PromptReco-v6");
//   InputFileNames.push_back("DoubleMu_Run2011B-PromptReco-v1");
//   InputFileNames.push_back("MuEG_Run2011A-05Aug2011-v1");
//   InputFileNames.push_back("MuEG_Run2011A-May10ReReco-v1");
//   InputFileNames.push_back("MuEG_Run2011A-PromptReco-v4");
//   InputFileNames.push_back("MuEG_Run2011A-PromptReco-v6");
//   InputFileNames.push_back("MuEG_Run2011B-PromptReco-v1");
//   InputFileNames.push_back("scaledown_ttbar");
//   InputFileNames.push_back("scaledown_ttbar_bb");
//   InputFileNames.push_back("scaledown_ttbar_cc");
//   InputFileNames.push_back("scaleup_ttbar");
//   InputFileNames.push_back("scaleup_ttbar_bb");
//   InputFileNames.push_back("scaleup_ttbar_cc");
//   InputFileNames.push_back("singlet_s");
//   InputFileNames.push_back("singlet_t");
//   InputFileNames.push_back("singlet_tW");
//   InputFileNames.push_back("singletbar_s");
//   InputFileNames.push_back("singletbar_t");
//   InputFileNames.push_back("singletbar_tW");
//   InputFileNames.push_back("ttH100");
//   InputFileNames.push_back("ttH105");
//   InputFileNames.push_back("ttH110");
//   InputFileNames.push_back("ttH115");
//   InputFileNames.push_back("ttH120");
//   InputFileNames.push_back("ttH125");
//   InputFileNames.push_back("ttH130");
//   InputFileNames.push_back("ttH135");
//   InputFileNames.push_back("ttH140");
//   InputFileNames.push_back("ttbar");
//   InputFileNames.push_back("ttbarW");
//   InputFileNames.push_back("ttbarZ");
//   InputFileNames.push_back("ttbar_bb");
//   InputFileNames.push_back("ttbar_cc");
//   InputFileNames.push_back("wjets");
//   InputFileNames.push_back("ww");
//   InputFileNames.push_back("wz");
//   InputFileNames.push_back("zjets");
//   InputFileNames.push_back("zjets_lowmass");
//   InputFileNames.push_back("zz");


  //InputFileNames.push_back("ttH125");
  //InputFileNames.push_back("ttH125_JESUp");
  //InputFileNames.push_back("ttH125_JESDown");

  //InputFileNames.push_back("ttH130");
  //InputFileNames.push_back("ttH130_JESUp");
  //InputFileNames.push_back("ttH130_JESDown");

//   InputFileNames.push_back("ttH120");
//   InputFileNames.push_back("ttH120_JESUp");
//   InputFileNames.push_back("ttH120_JESDown");

//   InputFileNames.push_back("ttbar");
//   InputFileNames.push_back("ttbar_JESUp");
//   InputFileNames.push_back("ttbar_JESDown");

//   InputFileNames.push_back("ttbarPlusBBbar");
//   InputFileNames.push_back("ttbarPlusBBbar_JESUp");
//   InputFileNames.push_back("ttbarPlusBBbar_JESDown");

//   InputFileNames.push_back("ttbarPlusCCbar");
//   InputFileNames.push_back("ttbarPlusCCbar_JESUp");
//   InputFileNames.push_back("ttbarPlusCCbar_JESDown");

//   InputFileNames.push_back("ttbarW");
//   InputFileNames.push_back("ttbarW_JESUp");
//   InputFileNames.push_back("ttbarW_JESDown");

//   InputFileNames.push_back("ttbarZ");
//   InputFileNames.push_back("ttbarZ_JESUp");
//   InputFileNames.push_back("ttbarZ_JESDown");

//   InputFileNames.push_back("wjets");
//   InputFileNames.push_back("wjets_JESUp");
//   InputFileNames.push_back("wjets_JESDown");

//   InputFileNames.push_back("zjets_h");
//   InputFileNames.push_back("zjets_h_JESUp");
//   InputFileNames.push_back("zjets_h_JESDown");

//   InputFileNames.push_back("zjets_lowmass");
//   InputFileNames.push_back("zjets_lowmass_JESUp");
//   InputFileNames.push_back("zjets_lowmass_JESDown");

//   InputFileNames.push_back("singlet_s");
//   InputFileNames.push_back("singlet_s_JESUp");
//   InputFileNames.push_back("singlet_s_JESDown");

//   InputFileNames.push_back("singlet_t");
//   InputFileNames.push_back("singlet_t_JESUp");
//   InputFileNames.push_back("singlet_t_JESDown");

//   InputFileNames.push_back("singlet_tW");
//   InputFileNames.push_back("singlet_tW_JESUp");
//   InputFileNames.push_back("singlet_tW_JESDown");

//   InputFileNames.push_back("singletbar_s");
//   InputFileNames.push_back("singletbar_s_JESUp");
//   InputFileNames.push_back("singletbar_s_JESDown");

//   InputFileNames.push_back("singletbar_t");
//   InputFileNames.push_back("singletbar_t_JESUp");
//   InputFileNames.push_back("singletbar_t_JESDown");

//   InputFileNames.push_back("singletbar_tW");
//   InputFileNames.push_back("singletbar_tW_JESUp");
//   InputFileNames.push_back("singletbar_tW_JESDown");

//   InputFileNames.push_back("WW");
//   InputFileNames.push_back("WW_JESUp");
//   InputFileNames.push_back("WW_JESDown");

//   InputFileNames.push_back("WZ");
//   InputFileNames.push_back("WZ_JESUp");
//   InputFileNames.push_back("WZ_JESDown");

//   InputFileNames.push_back("ZZ");
//   InputFileNames.push_back("ZZ_JESUp");
//   InputFileNames.push_back("ZZ_JESDown");

  
//   InputFileNames.push_back("data_DiMuon");
//   InputFileNames.push_back("data_DiEle");
//   InputFileNames.push_back("data_MuEG");

  ////////////////////
  std::vector<varInfo*> varList;
  double pival = 3.14;
  
  varInfo *Ht = new varInfo("Ht", "Ht", "Ht", 1000, 0, 10000);
  varList.push_back(Ht);

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
  //varInfo *CFMlpANN_e2je2t = new varInfo("CFMlpANN_e2je2t", "CFMlpANN_e2je2t", "CFMlpANN_e2je2t", 1000, 0.007, 0.008);
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
  varInfo *fourth_jet_pt = new varInfo("fourth_jet_pt", "fourth_jet_pt", "fourth_jet_pt", 1000, 0, 1000);
  varList.push_back(fourth_jet_pt);
  //  varInfo *fstElePt = new varInfo("fstElePt", "fstElePt", "fstElePt", 1000, 0, 1000);
  //  varList.push_back(fstElePt);
  //  varInfo *fstMuPt = new varInfo("fstMuPt", "fstMuPt", "fstMuPt", 1000, 0, 1000);
  //  varList.push_back(fstMuPt);
//   varInfo *isTriggerPass = new varInfo("isTriggerPass", "isTriggerPass", "isTriggerPass", 2, 0, 2);
//   varList.push_back(isTriggerPass);
//   varInfo *isCleanEvent = new varInfo("isCleanEvent", "isCleanEvent", "isCleanEvent", 2, 0, 2);
//   varList.push_back(isCleanEvent);
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
//   varInfo *numLooseElectrons = new varInfo("numLooseElectrons", "numLooseElectrons", "numLooseElectrons", 10, 0, 10);
//   varList.push_back(numLooseElectrons);
//   varInfo *numLooseMuons = new varInfo("numLooseMuons", "numLooseMuons", "numLooseMuons", 10, 0, 10);
//   varList.push_back(numLooseMuons);
  //  varInfo *numNonTaggedJets = new varInfo("numNonTaggedJets", "numNonTaggedJets", "numNonTaggedJets", 10, 0, 10);
  //  varList.push_back(numNonTaggedJets);
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
  varInfo *third_jet_pt = new varInfo("third_jet_pt", "third_jet_pt", "third_jet_pt", 1000, 0, 1000);
  varList.push_back(third_jet_pt);
  //  varInfo *unc_met = new varInfo("unc_met", "unc_met", "unc_met", 1000, 0, 1000);
  //  varList.push_back(unc_met);
//   varInfo *weight = new varInfo("weight", "weight", "weight", 1000, 0, 10);
//   varList.push_back(weight);

  


  ////////// start sample loop
  const unsigned int nInputFiles = InputFileNames.size();
  for( unsigned int i = 0; i < nInputFiles; i++) {
    
    std::string InputFileLabel = InputFileNames[i];

    TString InputFileName = treeFile;

    std::cout << "==== Processing File " << InputFileLabel << " ==== " << std::endl;
    TFile * DileptonFile = new TFile(InputFileName);
    TTree * DileptonSummaryTree = (TTree *) DileptonFile->Get("summaryTree");


    ///////////////////////// start category loop    
    for( unsigned int k = 0; k < nJetTagReqs; k++) {
      
      std::string JetTagReq = JetTagReqs[k];
      std::cout << "  ==>start category " << JetTagReq.c_str() << std::endl;
      
      std::string JetReq = "holder";
      std::string TagReq = "holder";
      std::string ProbStr = "holder";
      std::string WeightStr = "holder";

      std::string EffStr = "holder";
      std::string TrigStr = "holder";
      
      if (JetTagReq == "eq1t") {
        JetReq = "numJets >= 2";
        TagReq = "numTaggedJets == 1";
	ProbStr = "prob * ";
      }
      else if (JetTagReq == "eq2jeq2t") {
        JetReq = "numJets == 2";
        TagReq = "numTaggedJets == 2";
	ProbStr = "prob * ";
      }
      else if (JetTagReq == "ge3t") {
        JetReq = "numJets >= 3";
        TagReq = "numTaggedJets >= 3";
	ProbStr = "prob * ";
      }
      
      if (JetReq == "holder" || TagReq == "holder") {
        std::cout << "JetReq or TagReq == holder" << std::endl;
        continue;
      }

      WeightStr = "weight * ";

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
	if (std::string::npos != InputFileLabel.find("data")) {
	  ProbStr = "";
	  WeightStr = "";
	  EffStr = "";
	  TrigStr = "";
	  std::cout << "Set prob2/probge3 to 1" << std::endl;
	}
    
	////////
	TString OutputFileName = "holder";
	OutputFileName = OutputDirectory + "/" + InputFileLabel + "_" + JetTagReq + "_" + OutputDirectory + ".root";
	TFile * OutputFile = new TFile(OutputFileName, "RECREATE");

	OutputFile->cd();

	///// start variables loop
	for(std::vector<varInfo*>::iterator tIter1 = varList.begin(); tIter1 != varList.end(); tIter1++) {

	  varInfo *u = *tIter1;
	  int nBins = u->nBins;
	  double Xmin = u->min;
	  double Xmax = u->max;
	  TString histName = u->hName ;

	  ///// selection cuts
	  //Selection string: ==2 tags or >=3 tags; DiMu, DiEle, MuEG, or DiMuZmask10
	  std::string SelectionStr = "holder";
	  std::string CleanTrig = "holder";
	  CleanTrig = "(isCleanEvent == 1) && (isTriggerPass == 1) && ";
	  
	  SelectionStr = WeightStr+ProbStr+EffStr+TrigStr +"( ("+ OutputDirectory +") && (dR_leplep > 0.2) && (mass_leplep > 12) && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
	  	    
	  if (SelectionStr == "holder") {
	    std::cout << "SelectionStr == holder" << std::endl;
	    continue;
	  }

	  TH1F *histTemp = new TH1F(histName, histName , nBins, Xmin, Xmax);
	  TString varSig =  histName + ">>" + histName;
	  
	  DileptonSummaryTree->Draw(varSig, SelectionStr.c_str(), "goff");
	  //	  DileptonSummaryTree->Draw(u->hName+">>"+u->hName+"("+n3+","+n4+","+n5+")",SelectionStr.c_str(),"goff");
	  //      	  std::cout << "Drawing histogram " << histName << std::endl;
	  histTemp->SetDirectory(OutputFile);
	} // end var loop
	
	OutputFile->Write();
	std::cout << "    Wrote out " << OutputFileName << std::endl;

	OutputFile->Close();

      } // end sub-lep cat loop
	std::cout << '\n' ;
    }// end Cat loop

    DileptonFile->Close();

  } // end sample loop

}// end main
