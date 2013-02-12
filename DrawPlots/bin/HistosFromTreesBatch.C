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
#include "TStopwatch.h"
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

class accInfo {

public:
  
  TString categoryName;
  TString cutString;
  TString weightString;
  double numPassUnweighted;
  double  numPassWeighted;

  //////////////////////////////////////////////////////////////////////////
  
  accInfo() : categoryName (""), cutString (""), weightString (""),
            numPassUnweighted (0), numPassWeighted (0)
  {};

  ///////////////////////////////////////////////////////////////////////////
  
  accInfo (TString cat, TString cut, TString w,  double npu = 0, double npw = 0):
    categoryName(cat),
    cutString (cut),
    weightString(w),
    numPassUnweighted(npu),
    numPassWeighted(npw)
  {};
  
  ////////////////////////////////////////////////////////////////

};


TString removeLogicalAnd (TString inputString){

  //  remove whitespace
  //  if there is no whitespace at the end,
  //  this does nothing
  inputString.Remove(TString::EStripType::kTrailing, ' ');

  // now get rid of the &&
  // it will remove all copies
  inputString.Remove(TString::EStripType::kTrailing, '&');
  
  
  return inputString;
  
}


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

   // grab input files  with btag up/down selections
   std::string treeFileNamebtagHFUp = inputs.getParameter< std::string >("fileNamebtagHFUp");
   std::string treeFileNamebtagHFDown = inputs.getParameter< std::string >("fileNamebtagHFDown");
   std::string treeFileNamebtagLFUp = inputs.getParameter< std::string >("fileNamebtagLFUp");
   std::string treeFileNamebtagLFDown = inputs.getParameter< std::string >("fileNamebtagLFDown");

   std::string inputYear = inputs.getParameter< std::string >("inputYear");
   std::string inputZmask = inputs.getParameter< std::string >("inputZmask");
   std::string inputPV = inputs.getParameter< std::string >("inputPV");
   
   std::string sampleName = anaParams.getParameter<string>("sampleName");
   bool skipSystematics = anaParams.getParameter<bool>("skipSystematics");
   bool printDrawString = anaParams.getParameter<bool>("printDrawString");
   bool printAccTables = anaParams.getParameter<bool>("printAccTables");

   if (skipSystematics) {

     std::cout << "==================================\n\n" 
               << "CONFIG: Skipping systematics\n"
               << "==================================\n\n"
               << endl;
     
   }

   bool makeCorePlots = anaParams.getParameter<bool>("corePlots");
   bool makeLepPlots = anaParams.getParameter<bool>("lepPlots");
   bool makeJetPlots = anaParams.getParameter<bool>("jetPlots");
   bool makeKinPlots = anaParams.getParameter<bool>("kinPlots");
   bool makeOnePlot = anaParams.getParameter<bool>("onePlot");

   std::cout << "CONFIG: corePlots = " << makeCorePlots << std::endl
             << "CONFIG: lepPlots = " << makeLepPlots << std::endl
             << "CONFIG: jetPlots = " << makeJetPlots << std::endl
             << "CONFIG: kinPlots = " << makeKinPlots << std::endl
             << std::endl;
        
   //int maxNentries = inputs.getParameter<int> ("maxEvents");

  //----------------------------------
  //
  //  Global job params
  //  File names, etc
  //---------------------------------
  
  std::string OutputDirectory = "holder/";

  //////////
  std::vector<string> JetTagReqs;
  //JetTagReqs.push_back("eq1t");
  JetTagReqs.push_back("eq2jeq2t");
  //JetTagReqs.push_back("eq3jeq2t");
  //JetTagReqs.push_back("ge4jeq2t");
  JetTagReqs.push_back("ge3t");
  //JetTagReqs.push_back("ge2t");

  const unsigned int nJetTagReqs = JetTagReqs.size();

  ////////  sub lepton category
  std::vector<string> lepCatList;
  lepCatList.push_back("TwoMuon"); 
  lepCatList.push_back("TwoEle");
  lepCatList.push_back("MuonEle");
  
  ///////   systematics
  std::vector< TString > sysList ;
  sysList.push_back("CMS_scale_jUp");  // 0
  sysList.push_back("CMS_scale_jDown"); // 1
  sysList.push_back(""); // 2
  sysList.push_back("PUUp"); // 3
  sysList.push_back("PUDown"); // 4
  sysList.push_back("CMS_eff_bUp"); // 5
  sysList.push_back("CMS_eff_bDown"); // 6
  sysList.push_back("CMS_fake_bUp"); // 7 
  sysList.push_back("CMS_fake_bDown"); //8
  sysList.push_back("CMS_ttH_PUcorrUp");  //rwt //9
  sysList.push_back("CMS_ttH_PUcorrDown"); //10
  sysList.push_back("Q2scale_ttH"); //11 
  sysList.push_back("Q2scale_ttH"); //12
  const unsigned int NumSys = sysList.size();

  ////////// prepare the weight
  vector<std::string> weight(NumSys, std::string(""));
  weight[0] = "weight*"  ;
  weight[1] = "weight*"  ;
  weight[2] = "weight*"  ;
  
  weight[3] = "weight_PUup*"  ;
  weight[4] = "weight_PUdown*"  ;
  
  weight[5] = "weight*";
  weight[6] = "weight*";
  weight[7] = "weight*";
  weight[8] = "weight*";

  weight[9] = "weight*"  ;  ///rwt
  weight[10] = "weight*"  ;

  if (inputYear == "2012_52x" || inputYear == "2012_53x") {
    weight[11] = "weight*Q2ScaleUpWgt*1.403*"  ;     
    weight[12] = "weight*Q2ScaleDownWgt*0.683*"  ;  
  }
  else { ///no Q2scale wgt for ttbar for now
//     weight[11] = "weight*"  ;     
//     weight[12] = "weight*"  ;  
  // for 2011
    weight[11] = "weight*Q2ScaleUpWgt*1.4065*"  ;     
    weight[12] = "weight*Q2ScaleDownWgt*0.6808*"  ;  
  }

  /////////// samples
  std::vector<string> InputFileNames;
  InputFileNames.push_back(sampleName);

  ////////////////////
  std::vector<varInfo*> varList;
  //double pival = 3.14;

  if (makeCorePlots) {

    //MVA output variables
    varInfo *CFMlpANN_e2je2t = new varInfo("CFMlpANN_e2je2t", "CFMlpANN_e2je2t", "CFMlpANN_e2je2t", 1000, 0.45, 0.55);
    varList.push_back(CFMlpANN_e2je2t);
    varInfo *CFMlpANN_e3je2t = new varInfo("CFMlpANN_e3je2t", "CFMlpANN_e3je2t", "CFMlpANN_e3je2t", 1000, 0, 1);
    varList.push_back(CFMlpANN_e3je2t);
    varInfo *CFMlpANN_ge4je2t = new varInfo("CFMlpANN_ge4je2t", "CFMlpANN_ge4je2t", "CFMlpANN_ge4je2t", 1000, 0, 1);
    varList.push_back(CFMlpANN_ge4je2t);
    varInfo *CFMlpANN_ge3t = new varInfo("CFMlpANN_ge3t", "CFMlpANN_ge3t", "CFMlpANN_ge3t", 1000, 0, 1);
    varList.push_back(CFMlpANN_ge3t);
    
    //ANN neural net inputs
    varInfo *avg_btag_disc_btags = new varInfo("avg_btag_disc_btags", "avg_btag_disc_btags", "avg_btag_disc_btags", 1000, 0, 1);
    varList.push_back(avg_btag_disc_btags);
    varInfo *Ht = new varInfo("Ht", "Ht", "Ht", 5000, 0, 5000);
    varList.push_back(Ht);
    varInfo *mass_of_everything = new varInfo("mass_of_everything", "mass_of_everything", "mass_of_everything", 5000, 0, 5000);
    varList.push_back(mass_of_everything);
    varInfo *min_dr_tagged_jets = new varInfo("min_dr_tagged_jets", "min_dr_tagged_jets", "min_dr_tagged_jets", 1000, 0, 10);
    varList.push_back(min_dr_tagged_jets);
    varInfo *mindr_lep1_jet = new varInfo("mindr_lep1_jet", "mindr_lep1_jet", "mindr_lep1_jet", 1000, 0, 10);
    varList.push_back(mindr_lep1_jet);
    
    //met
    varInfo *met = new varInfo("met", "met", "met", 1000, 0, 1000);
    varList.push_back(met);
    varInfo *MHT = new varInfo("MHT", "MHT", "MHT", 1000, 0, 1000);
    varList.push_back(MHT);
    
    //event variables
    varInfo *numJets = new varInfo("numJets", "numJets", "numJets", 20, 0, 20);
    varList.push_back(numJets);
    varInfo *numTaggedJets = new varInfo("numTaggedJets", "numTaggedJets", "numTaggedJets", 10, 0, 10);
    varList.push_back(numTaggedJets);
    varInfo *numPV = new varInfo("numPV", "numPV", "numPV", 50, 0, 50);
    varList.push_back(numPV);

  } //end if makeCorePlots


  if (makeLepPlots) {
    
    varInfo *numTightMuons = new varInfo("numTightMuons", "numTightMuons", "numTightMuons", 10, 0, 10);
    varList.push_back(numTightMuons);
    varInfo *numLooseMuons = new varInfo("numLooseMuons", "numLooseMuons", "numLooseMuons", 10, 0, 10);
    varList.push_back(numLooseMuons);
    varInfo *numTightElectrons = new varInfo("numTightElectrons", "numTightElectrons", "numTightElectrons", 10, 0, 10);
    varList.push_back(numTightElectrons);
    varInfo *numLooseElectrons = new varInfo("numLooseElectrons", "numLooseElectrons", "numLooseElectrons", 10, 0, 10);
    varList.push_back(numLooseElectrons);

    //lepton variables
    varInfo *lep1Pt = new varInfo("lep1Pt", "lep1Pt", "lep1Pt", 1000, 0, 1000);
    varList.push_back(lep1Pt);
    varInfo *lep2Pt = new varInfo("lep2Pt", "lep2Pt", "lep2Pt", 1000, 0, 1000);
    varList.push_back(lep2Pt);
    varInfo *lep1Eta = new varInfo("lep1Eta", "lep1Eta", "lep1Eta", 1000, -5, 5);
    varList.push_back(lep1Eta);
    varInfo *lep2Eta = new varInfo("lep2Eta", "lep2Eta", "lep2Eta", 1000, -5, 5);
    varList.push_back(lep2Eta);
    varInfo *lep1Iso = new varInfo("lep1Iso", "lep1Iso", "lep1Iso", 2000, 0, 0.2);
    varList.push_back(lep1Iso);
    varInfo *lep2Iso = new varInfo("lep2Iso", "lep2Iso", "lep2Iso", 2000, 0, 0.2);
    varList.push_back(lep2Iso);

  } // end if makeLepPlots

  if (makeJetPlots) {
    
    //jet variables
    varInfo *first_jet_pt = new varInfo("first_jet_pt", "first_jet_pt", "first_jet_pt", 1000, 0, 1000);
    varList.push_back(first_jet_pt);
    varInfo *second_jet_pt = new varInfo("second_jet_pt", "second_jet_pt", "second_jet_pt", 1000, 0, 1000);
    varList.push_back(second_jet_pt);
    varInfo *third_jet_pt = new varInfo("third_jet_pt", "third_jet_pt", "third_jet_pt", 1000, 0, 1000);
    varList.push_back(third_jet_pt);
    varInfo *first_jet_eta = new varInfo("first_jet_eta", "first_jet_eta", "first_jet_eta", 1000, -5, 5);
    varList.push_back(first_jet_eta);
    varInfo *second_jet_eta = new varInfo("second_jet_eta", "second_jet_eta", "second_jet_eta", 1000, -5, 5);
    varList.push_back(second_jet_eta);
    varInfo *third_jet_eta = new varInfo("third_jet_eta", "third_jet_eta", "third_jet_eta", 1000, -5, 5);
    varList.push_back(third_jet_eta);

  } // end if makeJetPlots

  if (makeKinPlots) {
    
    //kinematic variables

    varInfo *mass_leplep = new varInfo("mass_leplep", "mass_leplep", "mass_leplep", 1000, 0, 1000);
    varList.push_back(mass_leplep);
    varInfo *sum_pt = new varInfo("sum_pt", "sum_pt", "sum_pt", 3000, 0, 3000);
    varList.push_back(sum_pt);
    varInfo *sum_jet_pt = new varInfo("sum_jet_pt", "sum_jet_pt", "sum_jet_pt", 3000, 0, 3000);
    varList.push_back(sum_jet_pt);

  } // end if makeKinPlots

  if (makeOnePlot) {
    //event variables
    varInfo *numJets = new varInfo("numJets", "numJets", "numJets", 20, 0, 20);
    varList.push_back(numJets);
  }

//   varInfo *all_sum_pt = new varInfo("all_sum_pt", "all_sum_pt", "all_sum_pt", 10000, 0, 10000);
//   varList.push_back(all_sum_pt);
//   varInfo *avg_dr_tagged_jets = new varInfo("avg_dr_tagged_jets", "avg_dr_tagged_jets", "avg_dr_tagged_jets", 1000, 0, 10);
//   varList.push_back(avg_dr_tagged_jets);
//   varInfo *avg_tagged_dijet_mass = new varInfo("avg_tagged_dijet_mass", "avg_tagged_dijet_mass", "avg_tagged_dijet_mass", 1000, 0, 1000);
//   varList.push_back(avg_tagged_dijet_mass);
//   varInfo *avg_tagged_dijet_mass = new varInfo("avg_tagged_dijet_mass", "avg_tagged_dijet_mass", "avg_tagged_dijet_mass", 1000, 0, 1000);
//   varList.push_back(avg_tagged_dijet_mass);
//   varInfo *avg_untagged_dijet_mass = new varInfo("avg_untagged_dijet_mass", "avg_untagged_dijet_mass", "avg_untagged_dijet_mass", 1000, 0, 1000);
//   varList.push_back(avg_untagged_dijet_mass);
//   varInfo *CFMlpANN_ge3t_new = new varInfo("CFMlpANN_ge3t_new", "CFMlpANN_ge3t_new", "CFMlpANN_ge3t_new", 1000, 0, 1);
//   varList.push_back(CFMlpANN_ge3t_new);
//   varInfo *CFMlpANN_var_best8 = new varInfo("CFMlpANN_var_best8", "CFMlpANN_var_best8", "CFMlpANN_var_best8", 1000, 0, 1);
//   varList.push_back(CFMlpANN_var_best8);
//   varInfo *closest_tagged_dijet_mass = new varInfo("closest_tagged_dijet_mass", "closest_tagged_dijet_mass", "closest_tagged_dijet_mass", 1000, 0, 1000);
//   varList.push_back(closest_tagged_dijet_mass);
//   varInfo *correctedDZ_leplep = new varInfo("correctedDZ_leplep", "correctedDZ_leplep", "correctedDZ_leplep", 1000, -0.5, 0.5);
//   varList.push_back(correctedDZ_leplep);
//   varInfo *dEta_leplep = new varInfo("dEta_leplep", "dEta_leplep", "dEta_leplep", 1000, -5, 5);
//   varList.push_back(dEta_leplep);
//   varInfo *dPhi_leplep = new varInfo("dPhi_leplep", "dPhi_leplep", "dPhi_leplep", 1000, -1*pival, pival);
//   varList.push_back(dPhi_leplep);
//   varInfo *dijet_mass_first = new varInfo("dijet_mass_first", "dijet_mass_first", "dijet_mass_first", 1000, 0, 1000);
//   varList.push_back(dijet_mass_first);
//   varInfo *dijet_mass_m2H = new varInfo("dijet_mass_m2H", "dijet_mass_m2H", "dijet_mass_m2H", 1000, 0, 1000);
//   varList.push_back(dijet_mass_m2H);
//   varInfo *dijet_mass_second = new varInfo("dijet_mass_second", "dijet_mass_second", "dijet_mass_second", 1000, 0, 1000);
//   varList.push_back(dijet_mass_second);
//   varInfo *dijet_mass_third = new varInfo("dijet_mass_third", "dijet_mass_third", "dijet_mass_third", 1000, 0, 1000);
//   varList.push_back(dijet_mass_third);
//   varInfo *dR_leplep = new varInfo("dR_leplep", "dR_leplep", "dR_leplep", 1000, 0, 10);
//   varList.push_back(dR_leplep);
//   varInfo *dev_from_avg_disc_btags = new varInfo("dev_from_avg_disc_btags", "dev_from_avg_disc_btags", "dev_from_avg_disc_btags", 1000, 0, 1);
//   varList.push_back(dev_from_avg_disc_btags);
//   varInfo *first_dibjet_mass = new varInfo("first_dibjet_mass", "first_dibjet_mass", "first_dibjet_mass", 1000, 0, 1000);
//   varList.push_back(first_dibjet_mass);
//   varInfo *second_dibjet_mass = new varInfo("second_dibjet_mass", "second_dibjet_mass", "second_dibjet_mass", 1000, 0, 1000);
//   varList.push_back(second_dibjet_mass);
//   varInfo *third_dibjet_mass = new varInfo("third_dibjet_mass", "third_dibjet_mass", "third_dibjet_mass", 1000, 0, 1000);
//   varList.push_back(third_dibjet_mass);
//   varInfo *first_highest_btag = new varInfo("first_highest_btag", "first_highest_btag", "first_highest_btag", 1000, 0, 1);
//   varList.push_back(first_highest_btag);
//   varInfo *first_jet_CHEF = new varInfo("first_jet_CHEF", "first_jet_CHEF", "first_jet_CHEF", 1000, 0, 1);
//   varList.push_back(first_jet_CHEF);
//   varInfo *fourth_allJet_pt = new varInfo("fourth_allJet_pt", "fourth_allJet_pt", "fourth_allJet_pt", 1000, 0, 1000);
//   varList.push_back(fourth_allJet_pt);
//   varInfo *fourth_jet_eta = new varInfo("fourth_jet_eta", "fourth_jet_eta", "fourth_jet_eta", 1000, -5, 5);
//   varList.push_back(fourth_jet_eta);
//   varInfo *fourth_jet_pt = new varInfo("fourth_jet_pt", "fourth_jet_pt", "fourth_jet_pt", 1000, 0, 1000);
//   varList.push_back(fourth_jet_pt);
//   varInfo *fourth_jet_pt = new varInfo("fourth_jet_pt", "fourth_jet_pt", "fourth_jet_pt", 1000, 0, 1000);
//   varList.push_back(fourth_jet_pt);
//   varInfo *higgsLike_dijet_mass = new varInfo("higgsLike_dijet_mass", "higgsLike_dijet_mass", "higgsLike_dijet_mass", 1000, 0, 1000);
//   varList.push_back(higgsLike_dijet_mass);
//   varInfo *higgsLike_allDijet_mass = new varInfo("higgsLike_allDijet_mass", "higgsLike_allDijet_mass", "higgsLike_allDijet_mass", 1000, 0, 1000);
//   varList.push_back(higgsLike_allDijet_mass);
//   varInfo *lep1Phi = new varInfo("lep1Phi", "lep1Phi", "lep1Phi", 1000, -1*pival, pival);
//   varList.push_back(lep1Phi);
//   varInfo *lep2Phi = new varInfo("lep2Phi", "lep2Phi", "lep2Phi", 1000, -1*pival, pival);
//   varList.push_back(lep2Phi);
//   varInfo *lowest_btag = new varInfo("lowest_btag", "lowest_btag", "lowest_btag", 1000, 0, 1);
//   varList.push_back(lowest_btag);
//   varInfo *lep2Phi = new varInfo("lep2Phi", "lep2Phi", "lep2Phi", 1000, -1*pival, pival);
//   varList.push_back(lep2Phi);
//   varInfo *lowest_btag = new varInfo("lowest_btag", "lowest_btag", "lowest_btag", 1000, 0, 1);
//   varList.push_back(lowest_btag);
//   varInfo *m2H_btag = new varInfo("m2H_btag", "m2H_btag", "m2H_btag", 1000, 0, 1000);
//   varList.push_back(m2H_btag);
//   varInfo *mass_MHT = new varInfo("mass_MHT", "mass_MHT", "mass_MHT", 5000, 0, 5000);
//   varList.push_back(mass_MHT);
//   varInfo *mass_of_leps_and_allJets = new varInfo("mass_of_leps_and_allJets", "mass_of_leps_and_allJets", "mass_of_leps_and_allJets", 6000, 0, 6000);
//   varList.push_back(mass_of_leps_and_allJets);
//   varInfo *mindr_lep2_jet = new varInfo("mindr_lep2_jet", "mindr_lep2_jet", "mindr_lep2_jet", 1000, 0, 10);
//   varList.push_back(mindr_lep2_jet);
//   varInfo *numAllJets = new varInfo("numAllJets", "numAllJets", "numAllJets", 20, 0, 20);
//   varList.push_back(numAllJets);
//   varInfo *numBadJets = new varInfo("numBadJets", "numBadJets", "numBadJets", 20, 0, 20);
//   varList.push_back(numBadJets);
//   varInfo *numNonTaggedJets = new varInfo("numNonTaggedJets", "numNonTaggedJets", "numNonTaggedJets", 10, 0, 10);
//   varList.push_back(numNonTaggedJets);
//   varInfo *prob = new varInfo("prob", "prob", "prob", 1000, 0, 10);
//   varList.push_back(prob);
//   varInfo *pt_leplep = new varInfo("pt_leplep", "pt_leplep", "pt_leplep", 1000, 0, 1000);
//   varList.push_back(pt_leplep);
//   varInfo *pt_of_everything = new varInfo("pt_of_everything", "pt_of_everything", "pt_of_everything", 1000, 0, 1000);
//   varList.push_back(pt_of_everything);
//   varInfo *pt_of_ttbar = new varInfo("pt_of_ttbar", "pt_of_ttbar", "pt_of_ttbar", 1000, 0, 1000);
//   varList.push_back(pt_of_ttbar);
//   varInfo *pt_of_leps_and_allJets = new varInfo("pt_of_leps_and_allJets", "pt_of_leps_and_allJets", "pt_of_leps_and_allJets", 10000, 0, 10000);
//   varList.push_back(pt_of_leps_and_allJets);
//   varInfo *second_highest_btag = new varInfo("second_highest_btag", "second_highest_btag", "second_highest_btag", 1000, 0, 1);
//   varList.push_back(second_highest_btag);
//   varInfo *second_jet_CHEF = new varInfo("second_jet_CHEF", "second_jet_CHEF", "second_jet_CHEF", 1000, 0, 1);
//   varList.push_back(second_jet_CHEF);
//   varInfo *third_jet_CHEF = new varInfo("third_jet_CHEF", "third_jet_CHEF", "third_jet_CHEF", 1000, 0, 1);
//   varList.push_back(third_jet_CHEF);
//   varInfo *unc_met = new varInfo("unc_met", "unc_met", "unc_met", 1000, 0, 1000);
//   varList.push_back(unc_met);
//   varInfo *PUweight = new varInfo("weight", "weight", "weight", 1000, 0, 10);
//   varList.push_back(PUweight);


  std::string OutputParams = "";
  //std::string TightLepStr = "(numTightMuons + numTightElectrons == 2) && "; //Only tight leptons
  //std::string TightLepStr = "(numTightMuons + numTightElectrons != 2) && "; //Only tight+loose events
  std::string OppositeLepStr = "(oppositeLepCharge == 1) && "; //Leptons have opposite charge
  //std::string OppositeLepStr = "(oppositeLepCharge == 0) && "; //Leptons have same charge
  //std::string OppositeLepStr = "(oppositeGenLepCharge == 0) && "; //GenLeptons have same charge
  //std::string OppositeLepStr = "(lep1TkCharge != lep1GenCharge) && "; //Lep1 wrong charge
  
  std::string ZmaskStr = "holder";
  std::string ZmaskStrSaver = "holder";
  std::string TightLepStr = "";
  std::string PVStr = "";

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
    ZmaskStr = "PassZmask == 0 && "; //Events inside the mask (mostly Zjets)
  }
  
  ////////  numPV division
  if (inputPV == "lowPV") {
    OutputParams = OutputParams+"_lowPV";
    if (inputYear == "2012_52x" || inputYear == "2012_53x")  PVStr = "numPV<11 &&";
    else  PVStr = "numPV<6 &&";
  }
  else if (inputPV == "medPV") {
    OutputParams = OutputParams+"_medPV";
    if (inputYear == "2012_52x" || inputYear == "2012_53x")  PVStr = "10<numPV && numPV<16 &&";
    else  PVStr = "5<numPV && numPV<9 &&";
  }
  else if (inputPV == "highPV") {
    OutputParams = OutputParams+"_highPV";
    if (inputYear == "2012_52x" || inputYear == "2012_53x")  PVStr = "15<numPV &&";
    else  PVStr = "8<numPV &&";
  }
  else {
    PVStr = "";
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
      //TString OutputFileName = "../" + inputYear + "/" + OutputDirectory + "/" + InputFileLabel + "_" + inputYear + "_" + OutputParams + "_" + JetTagReq + "_" + OutputDirectory + ".root";
      TString OutputFileName = "../" + OutputDirectory + "/" + InputFileLabel + "_" + inputYear + "_" + OutputParams + "_" + JetTagReq + "_" + OutputDirectory + ".root";
      TFile * OutputFile = new TFile(OutputFileName, "RECREATE");
      std::cout << "Storing root file named " << OutputFileName << std::endl;
      outputRootFiles[OutputFileName] = OutputFile;
    }
  }


  std::map<TString,accInfo> categoryAcceptances;
  
  /////////////// Debuging root file

  TFile * debugOutput = new TFile (std::string("batchBEAN/timer/" + InputFileNames[0] + "_debugTimer.root").c_str(), "RECREATE");

  debugOutput->cd();
  TH1F * drawTimesReal = new TH1F ("drawTimesReal", "drawTimesReal", 5000, 0, 1);
  TH1F * drawTimesCPU = new TH1F ("drawTimesCPU", "drawTimesCPU", 5000, 0, 1);
  TH1F * numDraws    = new TH1F ("numDraws", "numDraws", 1, 0.5, 1.5);

  //unsigned numDraws = 0;
   

  ////////// start sample loop
  const unsigned int nInputFiles = InputFileNames.size();
  for( unsigned int i = 0; i < nInputFiles; i++) {
    
    std::string InputFileLabel = InputFileNames[i];
    TString tmpName = InputFileLabel ;

    std::cout << "==== Processing Sample " << InputFileLabel << " ====" << std::endl;

    bool isData = false;
    
    if (std::string::npos != InputFileLabel.find("DoubleMu") ||
        std::string::npos != InputFileLabel.find("DoubleEle") ||
        std::string::npos != InputFileLabel.find("MuEG") ||
        std::string::npos != InputFileLabel.find("data") ) {
      isData = true;
    }

    for (unsigned int ksys = 0 ; ksys < NumSys ; ++ksys ){
      if ( (isData || skipSystematics) && ksys!=2) continue;

      if (!tmpName.Contains("ttbar_") && ksys > 10) continue; /// rwt

      TString syst = sysList[ksys];
      //////// rwt
      if (tmpName.Contains("ttbar_part")
          || tmpName.Contains("ttbar_ll_part")
          || tmpName.Contains("ttbar_lj_part")
          || tmpName.Contains("ttbar_jj_part")
          ){
        if (ksys == 11) syst += "_ttbarUp";
        if (ksys == 12) syst += "_ttbarDown";
      }
      if (tmpName.Contains("ttbar_bb")){
        if (ksys == 11) syst += "_ttbar_bbUp";
        if (ksys == 12) syst += "_ttbar_bbDown";
      }
      if (tmpName.Contains("ttbar_cc")){
        if (ksys == 11) syst += "_ttbar_ccUp";
        if (ksys == 12) syst += "_ttbar_ccDown";
      }

      std::cout << "  == start systematic " << syst << " ==  " << std::endl;

      TString InputFileName = treeFileNameNominal;

      if (ksys == 0 ) {
        //InputFileName = "_JESUp.root" ;
        InputFileName = treeFileNameJESUp;
      }
      else if (ksys == 1 ) {
        //InputFileName += "_JESDown.root" ;
        InputFileName = treeFileNameJESDown;
      } else if (ksys == 5) {
        InputFileName = treeFileNamebtagHFUp;
      } else if (ksys == 6) {
        InputFileName = treeFileNamebtagHFDown;
      } else if (ksys == 7) {
        InputFileName = treeFileNamebtagLFUp;
      } else if (ksys == 8) {
        InputFileName = treeFileNamebtagLFDown;
      }
      //else  InputFileName += ".root" ;
      
      std::cout << "Looking for file " << InputFileName << std::endl;
      TFile * DileptonFile = new TFile(InputFileName);

      if (DileptonFile->IsZombie()) {
        std::cout << "GREP_STATUS: Can't find the file," << InputFileName <<  ", sorry... quitting" << std::endl;
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
      std::string XsecStr = "holder";

      std::string EffStr = "holder";
      std::string TrigStr = "holder";

      // Convention: selections end with a logical AND and a space
      std::string cutDrLepLep = " (dR_leplep > 0.2) && ";
      std::string cutMassLepLep = " (mass_leplep > 12) && ";
      
      
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
      else if (JetTagReq == "ge2t") {
        JetReq = "numJets >= 2";
        TagReq = "numTaggedJets >= 2";
      }
      
      if (JetReq == "holder" || TagReq == "holder" || ZmaskStr == "holder") {
        std::cout << "JetReq or TagReq or ZmaskStr == holder" << std::endl;
        continue;
      }

      //      ProbStr = "prob * ";
      //// rwt
      if (ksys == 9) WeightStr = weight[ksys] + "HtWgtUp*" ;
      else if (ksys == 10) WeightStr = weight[ksys] ;
      else WeightStr = weight[ksys] + "HtWgt*" ;
//       else WeightStr = weight[ksys] ;

      /////// start sub-lepton category loop    
      const unsigned int nlepCatList = lepCatList.size();
      for( unsigned int j = 0; j < nlepCatList; j++) {
        OutputDirectory = lepCatList[j];
        std::cout << "    ==>start sub-lep category " << OutputDirectory.c_str() << std::endl;
        if (inputYear == "2011") {
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
        }
        else {
        if (OutputDirectory == "TwoMuon" ) {
          TrigStr = "1.0035 * (1 + (abs(lep1Eta) > 1.31 && abs(lep1Eta) < 1.65)*0.061) * (1 + (abs(lep2Eta) > 1.31 && abs(lep2Eta) < 1.65)*0.061) * ";
        }
        else if (OutputDirectory ==  "TwoEle" ) {
          TrigStr = "0.964 * ";
        }
        else if (OutputDirectory ==  "MuonEle"  ) {
          TrigStr = "0.983 * (1 + (abs(lep1Eta) > 1.31 && abs(lep1Eta) < 1.65)*0.072) * ";
        }
	EffStr = "lepTotalSF * ";
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
        if (inputYear == "2012_53x") XsecStr = "weight_Xsec*";
        else XsecStr = "";

          ///// selection cuts
          //Selection string
          std::string SelectionStr = "holder";
          std::string CleanTrig = "holder";

          if (OutputDirectory == "TwoMuon") CleanTrig = "(isCleanEvent == 1) && (isDoubleMuTriggerPass == 1) && ";
          if (OutputDirectory == "TwoEle") CleanTrig =  "(isCleanEvent == 1) && (isDoubleElectronTriggerPass == 1) && ";
          if (OutputDirectory == "MuonEle") CleanTrig = "(isCleanEvent == 1) && (isMuEGTriggerPass == 1) && ";

//           if (inputYear == "2011") {
//             CleanTrig = "(isCleanEvent == 1) && (isTriggerPass == 1) && ";
//           }
          ZmaskStrSaver = ZmaskStr;
          if (OutputDirectory == "MuonEle") {
            ZmaskStr = "";
          }
          
          //SelectionStr = WeightStr+EffStr+TrigStr+XsecStr+"(" + OppositeLepStr + ZmaskStr + PVStr + TightLepStr
          //  + " ("+ OutputDirectory +") && (dR_leplep > 0.2) && (mass_leplep > 12) && "
          //  +CleanTrig+"("+JetReq+") && ("+TagReq+") )";

          SelectionStr = WeightStr+EffStr+TrigStr+XsecStr+"(" + OppositeLepStr + ZmaskStr + PVStr + TightLepStr
            + " ("+ OutputDirectory +") && " + cutDrLepLep + cutMassLepLep
            +CleanTrig+"("+JetReq+") && ("+TagReq+") )";
          

          if (printAccTables){


            TString weightNoHtReweight = weight[ksys];
            
            TH1F * tempHistForIntegral = new TH1F ("tempHistForIntegral", "tempHistForIntegral", 20, 0, 20);            

            TString CleanTrigAsEnd = removeLogicalAnd(CleanTrig);

            ////////////////////////////////////////////////////////////////////////

            accInfo lepSelectionInfo;            
            lepSelectionInfo.categoryName = OutputDirectory;
            lepSelectionInfo.weightString = weightNoHtReweight + EffStr + TrigStr+XsecStr;
            lepSelectionInfo.cutString = "("+OppositeLepStr + ZmaskStr + PVStr
              + TightLepStr + "(" +OutputDirectory +") && " + cutDrLepLep + cutMassLepLep
              + CleanTrigAsEnd + ")";

            lepSelectionInfo.numPassUnweighted = DileptonSummaryTree->Draw("numJets >> tempHistForIntegral",
                                                                           lepSelectionInfo.weightString
                                                                           + lepSelectionInfo.cutString,
                                                                           "goff");
            
            lepSelectionInfo.numPassWeighted = tempHistForIntegral->Integral();

            if (categoryAcceptances.find(lepSelectionInfo.categoryName) == categoryAcceptances.end())
              categoryAcceptances[lepSelectionInfo.categoryName] = lepSelectionInfo;

            ///////////////////////////////////////////////////////////////////////
            

            accInfo jetSelectionInfo;

            TString JetReqAsEnd  = removeLogicalAnd(JetReq);
            jetSelectionInfo.categoryName = OutputDirectory + " " + JetReq;
            jetSelectionInfo.weightString = weightNoHtReweight + EffStr + TrigStr+XsecStr;
            

            jetSelectionInfo.cutString = "("+OppositeLepStr + ZmaskStr + PVStr
              + TightLepStr + "(" +OutputDirectory + ") && "  + cutDrLepLep + cutMassLepLep
              + CleanTrig + "("+JetReqAsEnd+")" +")";

            jetSelectionInfo.numPassUnweighted = DileptonSummaryTree->Draw("numJets >> tempHistForIntegral",
                                                                           jetSelectionInfo.weightString
                                                                           + jetSelectionInfo.cutString,
                                                                           "goff");

            jetSelectionInfo.numPassWeighted = tempHistForIntegral->Integral();

            if (categoryAcceptances.find(jetSelectionInfo.categoryName) == categoryAcceptances.end())
              categoryAcceptances[jetSelectionInfo.categoryName] = jetSelectionInfo;            

            
            //////////////////////////////////////////////////////////////////////////

            
            accInfo tagJetLepSelectionInfo;
            tagJetLepSelectionInfo.categoryName = OutputDirectory + " " + JetReq + " " + TagReq;
            tagJetLepSelectionInfo.weightString = weightNoHtReweight + EffStr + TrigStr+XsecStr;

            tagJetLepSelectionInfo.cutString = "("+OppositeLepStr + ZmaskStr + PVStr
              + TightLepStr + "(" +OutputDirectory + ") && "  + cutDrLepLep + cutMassLepLep
              + CleanTrig + "("+JetReq+") && ("+TagReq+")"+")";



            tagJetLepSelectionInfo.numPassUnweighted = DileptonSummaryTree->Draw("numJets >> tempHistForIntegral",
                                                                           tagJetLepSelectionInfo.weightString
                                                                              + tagJetLepSelectionInfo.cutString,
                                                                           "goff");
            
            tagJetLepSelectionInfo.numPassWeighted = tempHistForIntegral->Integral();

            if (categoryAcceptances.find(tagJetLepSelectionInfo.categoryName) == categoryAcceptances.end())
              categoryAcceptances[tagJetLepSelectionInfo.categoryName] = tagJetLepSelectionInfo;
            
              
          }
          
          
          if (SelectionStr == "holder") {
            std::cout << "SelectionStr == holder" << std::endl;
            continue;
          }

	  std::string SelectionOrig = weight[ksys]+EffStr+TrigStr+XsecStr+"(" + OppositeLepStr + ZmaskStr + PVStr + TightLepStr + " ("+ OutputDirectory +") && (dR_leplep > 0.2) && (mass_leplep > 12) && "+CleanTrig+"("+JetReq+") && ("+TagReq+") )";
	  if (isData) SelectionOrig = SelectionStr ;

	  //// get the correct normalization
	  TString nameTmp = "njets_" + TString(JetTagReq + "_" + OutputDirectory) + syst;
          TH1F *normTemp = new TH1F(nameTmp, "number of jets", 20,0,20);
	  DileptonSummaryTree->Draw("numJets>>"+nameTmp, SelectionOrig.c_str(), "goff");
	  double totNorm = normTemp->Integral();
	  //	  std::cout<< " --> original norm is " << totNorm << std::endl;
          ZmaskStr = ZmaskStrSaver; 

        ////////  book only a few histogram folders
        //TString OutputFileName = "holder";
        //OutputFileName = "../" + OutputParams + OutputDirectory + "/" + InputFileLabel + "_" + inputYear + "_" + JetTagReq + "_" + OutputDirectory + ".root";
        //TFile * OutputFile = new TFile(OutputFileName, "UPDATE");
        //TString OutputFileName = "../" + inputYear + "/" + OutputDirectory + "/" + InputFileLabel + "_" + inputYear + "_" + OutputParams + "_" + JetTagReq + "_" + OutputDirectory + ".root";
        TString OutputFileName = "../" + OutputDirectory + "/" + InputFileLabel + "_" + inputYear + "_" + OutputParams + "_" + JetTagReq + "_" + OutputDirectory + ".root";
        TFile * OutputFile = outputRootFiles[OutputFileName];

        cout << "Switching to output file" << OutputFile->GetName() << std::endl;
        OutputFile->cd();

        
        if (printDrawString) {
            cout << "DEBUG: Draw command was made like this selection string" << endl 
                 << "DEBUG: " << SelectionStr 
                 << endl;
            
        }

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


          TH1F *histTemp = new TH1F(histName, histName , nBins, Xmin, Xmax);
	  histTemp->Sumw2();  //// sumw2
          TString varSig =  variableName + ">>" + histName;
          TStopwatch myTime; // this starts the timer
          DileptonSummaryTree->Draw(varSig, SelectionStr.c_str(), "goff");
          myTime.Stop();
          drawTimesReal->Fill(myTime.RealTime());
          drawTimesCPU->Fill(myTime.CpuTime());
          numDraws->Fill(1);

	  //	  if ( variableName == "Ht" )std::cout << " --> draw norm is " << histTemp->Integral() <<  std::endl;
          //	  DileptonSummaryTree->Draw(u->hName+">>"+u->hName+"("+n3+","+n4+","+n5+")",SelectionStr.c_str(),"goff");
          //      	  std::cout << "Drawing histogram " << histName << std::endl;


          ///////////////////////////////////////////////////////
          //
          //  Critical - renormalize histogram for HT reweight
          //
          ////////////////////////////////////////////////////////

          
          if(!isData && histTemp->Integral()!=0) histTemp->Scale(totNorm/histTemp->Integral());
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
      //TString OutputFileName = "../" + inputYear + "/" + OutputDirectory + "/" + InputFileLabel + "_" + inputYear + "_" + OutputParams + "_" + JetTagReq + "_" + OutputDirectory + ".root";
      TString OutputFileName = "../" + OutputDirectory + "/" + InputFileLabel + "_" + inputYear + "_" + OutputParams + "_" + JetTagReq + "_" + OutputDirectory + ".root";
      
      std::cout << "Closing root file named " << OutputFileName << std::endl;
      outputRootFiles[OutputFileName]->Write();
      outputRootFiles[OutputFileName]->Close();
      
      
    }
  }


  debugOutput->Write();
  debugOutput->Close();

  ///////////////////////////////////////////////////////
  //
  //
  //  Just print your tables
  //
  //
  ////////////////////////////////////////////////////////  

  if (printAccTables) {

    std::map<TString, bool> printedCategories;

    for (std::map<TString, accInfo>::iterator iTable = categoryAcceptances.begin();
         iTable != categoryAcceptances.end();
         iTable++){

//       cout << "=================================" << endl
//            << "Table = " << iTable->categoryName << endl
//            << "Cuts = " << iTable->cutString << endl
//            << "Weights = "  << iTable->weightString << endl
//            << "numPassWeighted = " << iTable->numPassWeighted << endl
//            << "numPassUnweighted = " << iTable->numPassUnweighted << endl
//            << endl;

      TString tempLabel = iTable->second.categoryName;
      
      if (printedCategories.find(tempLabel) == printedCategories.end()){      
        cout << "GREP_ACC, " << tempLabel << " W, " << iTable->second.numPassWeighted << endl
             << "GREP_ACC, " << tempLabel << " U, " << iTable->second.numPassUnweighted << endl;
        
        printedCategories[tempLabel] = true;
      } else {
        cout << "Skipped category " << tempLabel
             << " because we already saw that one" << endl;
        
      }
      
      
    }

  }

  

  std::cout << "GREP_STATUS OK" << std::endl;

}// end main
