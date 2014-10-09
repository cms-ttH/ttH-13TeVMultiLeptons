//new include items for miniAOD compatibility

#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/GenericParticle.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"
#include "DataFormats/PatCandidates/interface/Tau.h"

#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
#include <TRandom3.h>
#include <vector>
#include "ttHMultileptonAnalysis/TemplateMakers/interface/GenericCollectionMember.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/GenericCollectionSizeVariable.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/GenericCollection.h"
//#include "ttHMultileptonAnalysis/TemplateMakers/interface/Lepton.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BTagDiscrim.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/GenPt.h"

///-------------- Kinematic Variables ------------------
//done
#include "ttHMultileptonAnalysis/TemplateMakers/interface/JobParameters.h"
//needs work
#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"

#include "Reflex/Object.h"
#include "Reflex/Type.h"
#include "Reflex/Member.h"
#include "Reflex/Kernel.h"

//----------  Use python utilities to configure
#include "FWCore/PythonParameterSet/interface/PythonProcessDesc.h"
#include "FWCore/ParameterSet/interface/ProcessDesc.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"

//define some global variables (probs not the best idea)!! 
bool isData;
string analysisYear = "2012_53x";
string sampleName;
int sampleNumber;

void detectData(string sampleName) {
  isData = false;
  string dataset = "MC";

  if (TString(sampleName).Contains("DoubleElectron")) dataset = "DoubleElectron";
  if (TString(sampleName).Contains("DoubleMu")) dataset = "DoubleMu";
  if (TString(sampleName).Contains("MuEG")) dataset = "MuEG";
  if (TString(sampleName).Contains("MET")) dataset = "MET";

  if (dataset != "MC") {
    std::cout << "CONFIG: DATA detected for sample " << sampleName << std::endl;
    isData = true;
  }
}

int convertSampleNameToNumber(string sampleName) {
  sampleNumber = 999999;
  double weight_Xsec = 1.0;
  int nGen = 1;
  float Xsec = 1.0;

  // make a TString version of this so you can use it for contains
  TString tmpName (sampleName);

  if (analysisYear == "2011") {
    if (isData) sampleNumber = -1;
    else if (sampleName == "zjets" || tmpName.Contains("zjets_part")) sampleNumber = 2300; 
    else if (sampleName == "zjets_lowmass") sampleNumber = 2310; 
    else if (sampleName == "wjets") sampleNumber = 2400; 
    else if (sampleName == "ttbar" || tmpName.Contains("ttbar_part")) sampleNumber = 2500;
    else if (sampleName == "ttbar_bb" ) sampleNumber = 2555; 
    else if (sampleName == "ttbar_cc") sampleNumber = 2544; 
    else if (tmpName.Contains("scaleup_ttbar")) sampleNumber = 2510; 
    else if (tmpName.Contains("scaledown_ttbar")) sampleNumber = 2511; 
    else if (sampleName == "ttbarZ") sampleNumber = 2523; 
    else if (sampleName == "ttbarW") sampleNumber = 2524; 
    else if (tmpName.Contains("singlet")) sampleNumber = 2600; 
    else if (sampleName == "ww") sampleNumber = 2700; 
    else if (sampleName == "wz") sampleNumber = 2701; 
    else if (sampleName == "zz") sampleNumber = 2702; 
    else if (tmpName.Contains("ttH")) sampleNumber = 120;
    else assert (sampleName == "sampleName is not in the approved list");
  }
  else if (analysisYear == "2012_52x" || analysisYear == "2012_53x") {
    if (isData) sampleNumber = -1;
    else if (sampleName == "ttbar" || tmpName.Contains("ttbar_part")) { sampleNumber = 2500;
      nGen = 6912438+1362471; Xsec = 245.8; }
    else if (sampleName == "ttbar_bb" || tmpName.Contains("ttbar_bb_part")) { sampleNumber = 2555;
      nGen = 6912438+1362471; Xsec = 245.8; }
    else if (sampleName == "ttbar_cc" || tmpName.Contains("ttbar_cc_part")) { sampleNumber = 2544;
      nGen = 6912438+1362471; Xsec = 245.8; }
    else if (sampleName == "ttbar_scaleup") sampleNumber = 2511; 
    else if (sampleName == "ttbar_scaledown") sampleNumber = 2510; 
    else if (sampleName == "ttbar_matchingup") sampleNumber = 2513; 
    else if (sampleName == "ttbar_matchingdown") sampleNumber = 2512; 
    else if (sampleName == "ttbar_jj" || tmpName.Contains("ttbar_jj_part")) { sampleNumber = 2566;
      nGen = 31111456; Xsec = 0.457*245.8;
      weight_Xsec = ( 0.457 / 31111456 ) / ( 1.0 / ( 6912438 + 1362471 )); }
    else if (sampleName == "ttbar_lj" || tmpName.Contains("ttbar_lj_part")) { sampleNumber = 2563;
      nGen = 25327478; Xsec = 0.438*245.8;
      weight_Xsec = ( 0.438 / 25327478 ) / ( 1.0 / ( 6912438 + 1362471 )); }
    else if (sampleName == "ttbar_ll" || tmpName.Contains("ttbar_ll_part")) { sampleNumber = 2533;
      nGen = 12100452; Xsec = 0.105*245.8;
      weight_Xsec = ( 0.105 / 12100452 ) / ( 1.0 / ( 6912438 + 1362471 )); }
    else if (sampleName == "ttbar_cc_jj" || tmpName.Contains("ttbar_cc_jj_part")) { sampleNumber = 2576;
      nGen = 31111456; Xsec = 0.457*245.8;
      weight_Xsec = ( 0.457 / 31111456 ) / ( 1.0 / ( 6912438 + 1362471 )); }
    else if (sampleName == "ttbar_cc_lj" || tmpName.Contains("ttbar_cc_lj_part")) { sampleNumber = 2573;
      nGen = 25327478; Xsec = 0.438*245.8;
      weight_Xsec = ( 0.438 / 25327478 ) / ( 1.0 / ( 6912438 + 1362471 )); }
    else if (sampleName == "ttbar_cc_ll" || tmpName.Contains("ttbar_cc_ll_part")) { sampleNumber = 2543;
      nGen = 12100452; Xsec = 0.105*245.8;
      weight_Xsec = ( 0.105 / 12100452 ) / ( 1.0 / ( 6912438 + 1362471 )); }
    else if (sampleName == "ttbar_bb_jj" || tmpName.Contains("ttbar_bb_jj_part")) { sampleNumber = 2586;
      nGen = 31111456; Xsec = 0.457*245.8;
      weight_Xsec = ( 0.457 / 31111456 ) / ( 1.0 / ( 6912438 + 1362471 )); }
    else if (sampleName == "ttbar_bb_lj" || tmpName.Contains("ttbar_bb_lj_part")) { sampleNumber = 2583;
      nGen = 25327478; Xsec = 0.438*245.8;
      weight_Xsec = ( 0.438 / 25327478 ) / ( 1.0 / ( 6912438 + 1362471 )); }
    else if (sampleName == "ttbar_bb_ll" || tmpName.Contains("ttbar_bb_ll_part")) { sampleNumber = 2553;
      nGen = 12100452; Xsec = 0.105*245.8;
      weight_Xsec = ( 0.105 / 12100452 ) / ( 1.0 / ( 6912438 + 1362471 )); }
    else if (sampleName == "ttbar_b_jj" || tmpName.Contains("ttbar_b_jj_part")) { sampleNumber = 2596;
      nGen = 31111456; Xsec = 0.457*245.8;
      weight_Xsec = ( 0.457 / 31111456 ) / ( 1.0 / ( 6912438 + 1362471 )); }
    else if (sampleName == "ttbar_b_lj" || tmpName.Contains("ttbar_b_lj_part")) { sampleNumber = 2593;
      nGen = 25327478; Xsec = 0.438*245.8;
      weight_Xsec = ( 0.438 / 25327478 ) / ( 1.0 / ( 6912438 + 1362471 )); }
    else if (sampleName == "ttbar_b_ll" || tmpName.Contains("ttbar_b_ll_part")) { sampleNumber = 2599;
      nGen = 12100452; Xsec = 0.105*245.8;
      weight_Xsec = ( 0.105 / 12100452 ) / ( 1.0 / ( 6912438 + 1362471 )); }
    else if (sampleName == "wjets" || tmpName.Contains("wjets_part")) { sampleNumber = 2400;
      nGen = 57536319; Xsec = 36257; }
    else if (sampleName == "wjets_0p" || tmpName.Contains("wjets_0p_part")) { sampleNumber = 2400;
      nGen = 57536319; Xsec = 36257; }
    else if (sampleName == "wjets_1p" || tmpName.Contains("wjets_1p_part")) { sampleNumber = 2400;
      nGen = 23134881; Xsec = 6440.4;
      weight_Xsec = ( 5400.0 / 23134881 ) / ( 30400.0 / 57536319 ); }
    else if (sampleName == "wjets_2p" || tmpName.Contains("wjets_2p_part")) { sampleNumber = 2400;
      nGen = 33933328; Xsec = 2087.2;
      weight_Xsec = ( 1750.0 / 339333285 ) / ( 30400.0 / 57536319 ); }
    else if (sampleName == "wjets_3p" || tmpName.Contains("wjets_3p_part")) { sampleNumber = 2400;
      nGen = 15463420; Xsec = 619.0;
      weight_Xsec = ( 519.0 / 15463420 ) / ( 30400.0 / 57536319 ); }
    else if (sampleName == "wjets_4p" || tmpName.Contains("wjets_4p_part")) { sampleNumber = 2400;
      nGen = 13365439; Xsec = 255.2;
      weight_Xsec = ( 214.0 / 13365439 ) / ( 30400.0 / 57536319 ); } 
    else if (sampleName == "zjets_lowmass" || tmpName.Contains("zjets_lowmass_part")) { sampleNumber = 2850;
      nGen = 37828841; Xsec = 14702; }
    else if (sampleName == "zjets_lowmass_1p" || tmpName.Contains("zjets_lowmass_1p_part")) { sampleNumber = 2851;
      weight_Xsec = ( 716.0 / 8039604 ) / ( 11050.0 / 37828841 ); }
    else if (sampleName == "zjets_lowmass_2p" || tmpName.Contains("zjets_lowmass_2p_part")) { sampleNumber = 2852;
      weight_Xsec = ( 309.7 / 30684442 ) / ( 11050.0 / 37828841 ); }
    else if (sampleName == "zjets" || tmpName.Contains("zjets_part")) { sampleNumber = 2800;
      nGen =  30072710; Xsec = 3505.7; }
    else if (sampleName == "zjets_0p" || tmpName.Contains("zjets_0p_part")) { sampleNumber = 2800;
      nGen =  30072710; Xsec = 3505.7; }
    else if (sampleName == "zjets_1p" || tmpName.Contains("zjets_1p_part")) { sampleNumber = 2801;
      nGen = 24032562; Xsec = 666.7;
      weight_Xsec = ( 561.0 / 24032562 ) / ( 2950.0 /  30072710 ); }
    else if (sampleName == "zjets_2p" || tmpName.Contains("zjets_2p_part")) { sampleNumber = 2802;
      nGen = 2350806; Xsec = 215.1;
      weight_Xsec = ( 181.0 / 2350806 ) / ( 2950.0 /  30072710 ); }
    else if (sampleName == "zjets_3p" || tmpName.Contains("zjets_3p_part")) { sampleNumber = 2803;
      nGen = 10753491; Xsec = 66.07;
      weight_Xsec = ( 55.6 / 10753491 ) / ( 2950.0 /  30072710 ); }
    else if (sampleName == "zjets_4p" || tmpName.Contains("zjets_4p_part")) { sampleNumber = 2804;
      nGen = 6370630; Xsec = 27.38;
      weight_Xsec = ( 23.04 /6370630 ) / ( 2950.0 /  30072710 ); }
    else if (sampleName == "singlet_s") { sampleNumber = 2600;
      nGen = 259657; Xsec = 3.79; }
    else if (sampleName == "singlet_s_ll") sampleNumber = 2630;
    else if (sampleName == "singletbar_s") { sampleNumber = 2601;
      nGen = 139835; Xsec = 1.76; }
    else if (sampleName == "singletbar_s_ll") sampleNumber = 2631; 
    else if (sampleName == "singlet_t") { sampleNumber = 2602;
      nGen = 3744404; Xsec = 56.4; }
    else if (sampleName == "singlet_t_ll") sampleNumber = 2632; 
    else if (sampleName == "singletbar_t") { sampleNumber = 2603;
      nGen = 1933504; Xsec = 30.7; }
    else if (sampleName == "singletbar_t_ll") sampleNumber = 2633; 
    else if (sampleName == "singlet_tW") { sampleNumber = 2604;
      nGen = 496918; Xsec = 11.1; }
    else if (sampleName == "singlet_tW_lj") sampleNumber = 2654; 
    else if (sampleName == "singlet_tW_jl") sampleNumber = 2664; 
    else if (sampleName == "singlet_tW_ll") sampleNumber = 2634; 
    else if (sampleName == "singletbar_tW") { sampleNumber = 2605;
      nGen = 492779; Xsec = 7.87; }
    else if (sampleName == "singletbar_tW_lj") sampleNumber = 2655; 
    else if (sampleName == "singletbar_tW_jl") sampleNumber = 2665; 
    else if (sampleName == "singletbar_tW_ll") sampleNumber = 2635; 
    else if (sampleName == "ww") { sampleNumber = 2700;
      nGen = 9955089; Xsec = 54.8; }
    else if (sampleName == "ww_ll") { sampleNumber = 2700;
      nGen = 1931931; Xsec = 54.8*0.324*0.324; }
    else if (sampleName == "www") { sampleNumber = 2710;
      nGen = 220040; Xsec =  0.08217; }
    else if (sampleName == "wwz") { sampleNumber = 2720;
      nGen = 221576; Xsec = 0.0633; }
    else if (sampleName == "wwG") { sampleNumber = 2720;
      nGen = 94500; Xsec = 0.0000001; } //AWB incorrect values
    else if (tmpName.Contains("wz") && !(tmpName.Contains("_ll") || tmpName.Contains("_lj"))) { sampleNumber = 2701;      
      nGen = 9931257; Xsec = 32.3; }
    else if (tmpName.Contains("wz") && tmpName.Contains("lll")) { sampleNumber = 2731;
      nGen = 1987010; Xsec = 1.057*1.10; } 
    else if (tmpName.Contains("wz") && tmpName.Contains("lljj")) { sampleNumber = 2761;
      nGen = 3212461; Xsec = 32.3*0.101*(1-0.324); }
    else if (tmpName.Contains("wz") && tmpName.Contains("ljj")) { sampleNumber = 2791;
      nGen = 2906320; Xsec = 32.3*0.324*0.699; }
    else if (sampleName == "wzz") { sampleNumber = 2721;
      nGen = 219835; Xsec = 0.01922; } 
    else if (tmpName.Contains("zz") && !tmpName.Contains("_ll")) { sampleNumber = 2702;
      nGen = 9755621; Xsec = 7.7; }
    else if (tmpName.Contains("zz") && tmpName.Contains("llll")) { sampleNumber = 2732;
      nGen = 4804217; Xsec = 0.157*1.21; } //why is it not (7.7*0.101*0.101) * 1.21?
    else if (tmpName.Contains("zz") && tmpName.Contains("lowmll")) { sampleNumber = 2732;
      nGen = 4804217; Xsec = 0.157*1.21; } //Incorrect nGen and Xsec
    else if (tmpName.Contains("zz") && tmpName.Contains("lljj")) { sampleNumber = 2762;
      nGen = 1934806; Xsec = 7.7*2*0.101*0.699; }
    else if (sampleName == "zzz") { sampleNumber = 2722;
      nGen = 224519; Xsec = 0.004587; }
    else if (sampleName == "ttbarW") { sampleNumber = 2524;
      nGen = 195396; Xsec = 0.249; }
    else if (sampleName == "ttbarWW") { sampleNumber = 2534;
      nGen = 216867; Xsec = 0.002037; }
    else if (sampleName == "ttbarZ") { sampleNumber = 2523;
      nGen = 209512; Xsec = 0.206; }
    else if (sampleName == "ttbarG") { sampleNumber = 2560;
      nGen = 71405; Xsec = 1.444*1.8; } 
    else if (sampleName == "ttbarGStar_ee") { sampleNumber = 2567;
      nGen = 13517; Xsec = 1.5*0.02724*0.104; } 
    else if (sampleName == "ttbarGStar_mm") { sampleNumber = 2568;
      nGen = 8019; Xsec = 1.5*0.01233*0.141; }
    else if (sampleName == "ttbarGStar_tt") { sampleNumber = 2569;
      nGen = 17289; Xsec = 1.5*0.00133*0.038; } 
    else if (sampleName == "tttt") { sampleNumber = 2525;
      nGen = 99994; Xsec = 0.000716; }
    else if (sampleName == "tbZ_ll") { sampleNumber = 2000;
      nGen = 148158; Xsec = 0.0114; }
    else if (sampleName == "WpWpqq") { sampleNumber = 2001;
      nGen = 99700; Xsec = 0.2482; }
    else if (sampleName == "WmWmqq") { sampleNumber = 2002;
      nGen = 1; Xsec = 0.0889; } //Not yet processed
    else if (sampleName == "WWDPI") { sampleNumber = 2003;
      nGen = 833755; Xsec = 0.5879; }
    else if (sampleName == "VH_tautau") { sampleNumber = 2915;
      nGen = 200124; Xsec = 0.07717352; } 
    else if (sampleName == "VH_TauMu") { sampleNumber = 2915; 
      nGen = 200124; Xsec = 0.07717352; }
    else if (sampleName == "VH_ZZ") { sampleNumber = 2923;
      nGen = 500409; Xsec = 0.03223704; } 
    else if (sampleName == "VH_WW") { sampleNumber = 2924;
      nGen = 200408; Xsec = 0.2625365; } 
    else if (tmpName.Contains("ttH") && analysisYear == "2012_52x") {
      if (tmpName.Contains("FullSim")) sampleNumber = 8120;
      else sampleNumber = 9120;
    }
    // hack hack hack to allow me to keep a separate list
    // treat this as a regular sample
    else if (sampleName == "ttbar_lj_passMva")  { sampleNumber = 2500;
      nGen = 25165429; Xsec = 98.65;
      weight_Xsec = ( 0.438 / 25165429 ) / ( 1.0 / ( 6889624 + 1362471 ));
    } 
    else if (tmpName.Contains("ttH") && analysisYear == "2012_53x") {
      if (tmpName.Contains("_tautau")) { sampleNumber = 7120;
        nGen = 992997; Xsec = 0.1302*0.1302; }
      else if (tmpName.Contains("_bb")) { sampleNumber = 8120;
        nGen = 980931; Xsec = 0.1302*0.577; }
      else { sampleNumber = 9120;
        nGen = 992997; Xsec = 0.1302; }
    }
    else assert (sampleName == "sampleName is not in the approved list");
  }
  else {
    assert (analysisYear == "either 2012_52x, 2012_53x, or 2011");
  }

  if (tmpName.Contains("wz") || tmpName.Contains("zz")) {
    if (tmpName.Contains("_lf")) sampleNumber = sampleNumber*10 + 1;
    if (tmpName.Contains("_cc")) sampleNumber = sampleNumber*10 + 2;
    if (tmpName.Contains("_bb")) sampleNumber = sampleNumber*10 + 4;
    else if (tmpName.Contains("_b")) sampleNumber = sampleNumber*10 + 3;
  }

  std::cout << "CONFIG: Sample Name = " << sampleName
            << ", sample Number = " << sampleNumber << endl;
  
  std::cout << weight_Xsec << nGen << Xsec << endl;
  return sampleNumber;
}

void safetyCheckJobOptions (int argc, char** argv) {
  std::cout << "--->Num argments provided at command line...  " << argc << std::endl;
  if (argc < 2) {
    std::cout << "Usage: " << std::endl
              << argv[0] << " jobParams.py " << " sampleName "
              << std::endl;

    std::cout << "You provided " << argc
              << " arguments, which is less than 2, quitting"
              << endl;
    exit (3);
  }
  return;
}

JobParameters parseJobOptions (int argc, char** argv) {
  JobParameters myConfig;
  safetyCheckJobOptions (argc, argv);
  PythonProcessDesc builder(argv[1],argc,argv);

  edm::ParameterSet const & inputs = builder.processDesc()->getProcessPSet()->getParameter<edm::ParameterSet>("inputs");
  edm::ParameterSet const & outputs = builder.processDesc()->getProcessPSet()->getParameter<edm::ParameterSet>("outputs");
  edm::ParameterSet const & analysis = builder.processDesc()->getProcessPSet()->getParameter<edm::ParameterSet>("analysis");

  myConfig.inputFileNames = inputs.getParameter< vector<string> > ("fileNames");
  myConfig.maxEvents = inputs.getParameter < int > ("maxEvents");
  myConfig.outputFileName = outputs.getParameter < string > ("fileName");
  myConfig.sampleName = analysis.getParameter < string > ("sampleName");
  myConfig.jetSyst = inputs.getParameter < string > ("jetSyst");
  return myConfig;
}

int main (int argc, char** argv) {
  // load framework libraries
  gSystem->Load( "libFWCoreFWLite" );
  AutoLibraryLoader::enable();

  int debug = 0; // levels of debug, 10 is large

  JobParameters myConfig = parseJobOptions(argc, argv);

  TFile * outputFile = new TFile (myConfig.outputFileName.c_str(), "RECREATE");

  outputFile->cd();

  TTree * summaryTree = new TTree("summaryTree", "Summary Event Values");

  fwlite::ChainEvent ev(myConfig.inputFileNames);

  // setup the analysis
  // it comes from the lepHelper

  sampleName = myConfig.sampleName;
  detectData(sampleName);
  convertSampleNameToNumber(sampleName);
  // initializePUReweighting();
  
  
  MiniAODHelper * miniAODhelper = new MiniAODHelper();
  miniAODhelper->SetUp(analysisYear, sampleNumber, analysisType::DIL, isData);

  miniAODhelper->SetFactorizedJetCorrector();
  
  fwlite::Handle<double> rhoHandle;
  rhoHandle.getByLabel(ev,"fixedGridRhoFastjetAll");//"fixedGridRhoAll");
  double rho = *rhoHandle;
  
  miniAODhelper->SetRho(rho);

  sysType::sysType jetSyst = sysType::NA;
  if (myConfig.jetSyst == "NA") jetSyst = sysType::NA;
  else if (myConfig.jetSyst == "JESUp") jetSyst = sysType::JESup;
  else if (myConfig.jetSyst == "JESDown") jetSyst = sysType::JESdown;
  else std::cout << "No valid JES corrections specified - using nominal" << std::endl;
  
  std::cout << jetSyst << std::endl;

  // ---------------------------------------------
  // Note for future development: should these be
  // saved inside the lepHelper somewhere?
  // For now they are ok here
  // ---------------------------------------------

  
  electronID::electronID electronTightID = electronID::electronTight;
  electronID::electronID electronLooseID = electronID::electronLoose;
  electronID::electronID electronPreselectedID = electronID::electronNoCuts;
  
  muonID::muonID muonTightID = muonID::muonTight;
  muonID::muonID muonLooseID = muonID::muonLoose;
  muonID::muonID muonPreselectedID = muonID::muonNoCuts;

  tauID::tauID tauTightID = tauID::tauMedium;
  // tauID::tauID tauLooseID = tauID::tauVLoose;
  tauID::tauID tauPreselectedID = tauID::tauNonIso;


  //collections
  GenericCollection<pat::ElectronCollection> tightElectrons(miniAODhelper);
  GenericCollection<pat::ElectronCollection> looseElectrons(miniAODhelper);
  GenericCollection<pat::ElectronCollection> preselectedElectrons(miniAODhelper);
  GenericCollection<pat::ElectronCollection> tightLooseElectrons(miniAODhelper);
  GenericCollection<pat::ElectronCollection> loosePreselectedElectrons(miniAODhelper);
  GenericCollection<pat::ElectronCollection> tightLoosePreselectedElectrons(miniAODhelper);
  
  GenericCollection<pat::MuonCollection> tightMuons(miniAODhelper);
  GenericCollection<pat::MuonCollection> looseMuons(miniAODhelper);
  GenericCollection<pat::MuonCollection> preselectedMuons(miniAODhelper);
  GenericCollection<pat::MuonCollection> tightLooseMuons(miniAODhelper);
  GenericCollection<pat::MuonCollection> tightLoosePreselectedMuons(miniAODhelper);

  GenericCollection<pat::TauCollection> tightTaus(miniAODhelper);
  GenericCollection<pat::TauCollection> tightLooseTaus(miniAODhelper);
  GenericCollection<pat::TauCollection> tightLoosePreselectedTaus(miniAODhelper);

  GenericCollection<std::vector<reco::LeafCandidate>> tightLeptons(miniAODhelper);  

  GenericCollection<std::vector<reco::LeafCandidate>> looseLeptons(miniAODhelper);
  GenericCollection<std::vector<reco::LeafCandidate>> preselectedLeptons(miniAODhelper);
  GenericCollection<std::vector<reco::LeafCandidate>> tightLooseLeptons(miniAODhelper);
  GenericCollection<std::vector<reco::LeafCandidate>> tightLoosePreselectedLeptons(miniAODhelper);
  
  GenericCollection<pat::JetCollection> jets(miniAODhelper);
  GenericCollection<pat::JetCollection> jets_30(miniAODhelper);
  GenericCollection<pat::JetCollection> jetsByCSV(miniAODhelper);

  GenericCollection<reco::VertexCollection> primaryVertices(miniAODhelper);

  //GenericCollection<pat::PackedGenParticleCollection> genTopParticles(miniAODhelper);
  GenericCollection<reco::GenParticleCollection> genParticles(miniAODhelper);
  GenericCollection<reco::GenParticleCollection> genTopParticles(miniAODhelper);
  GenericCollection<reco::GenParticleCollection> genHiggsParticles(miniAODhelper);
  
  vector<ArbitraryVariable*> kinVars;
  vector<ArbitraryVariable*> cutVars;

  //////////////////////////////////////////////////////////////////////////////
  ////
  //// Add vars to tree
  ////
  //////////////////////////////////////////////////////////////////////////////

  // GenericCollectionMember<float,std::vector<pat::Muon>> 
  //   allMuonPt(Reflex::Type::ByName("pat::Muon"), &(tightLooseMuons.ptrToItems),
  //             "pt_", "muons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  // kinVars.push_back(&allMuonPt);

  // GenericCollectionMember<float,std::vector<pat::Electron>> 
  //   allElectronPt(Reflex::Type::ByName("pat::Electron"), &(tightLooseElectrons.ptrToItems),
  // 		  "pt_", "electrons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  // kinVars.push_back(&allElectronPt);

  // GenericCollectionMember<float,std::vector<reco::LeafCandidate>> 
  //   allLeptonPt(Reflex::Type::ByName("reco::LeafCandidate"), &(tightLooseLeptons.ptrToItems),
  // 		  "pt_", "leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  // kinVars.push_back(&allLeptonPt);

  // GenericCollectionMember<float,std::vector<pat::Jet>> 
  //   allJetPt(Reflex::Type::ByName("pat::Jet"), &(jets.ptrToItems),
  // 		  "pt_", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  // kinVars.push_back(&allJetPt);

  GenericCollectionMember<float,std::vector<pat::Jet>> 
    allJetCSV(Reflex::Type::ByName("pat::Jet"), &(jets.ptrToItems),
  		  "pt_", "jets_by_csv",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allJetCSV);

  // GenPt<std::vector<reco::GenParticle>>
  //   topPt(&(genTopParticles.ptrToItems),"genTopPt");
  // kinVars.push_back(&topPt);

  // GenPt<std::vector<pat::Muon>>
  //   muPt(&(tightLooseMuons.ptrToItems),"muonPt");
  // kinVars.push_back(&muPt);

  // GenPt<std::vector<reco::GenParticle>>
  //   higgsPt(&(genHiggsParticles.ptrToItems),"genHiggsPt");
  // kinVars.push_back(&higgsPt);
  
  // BTagDiscrim<std::vector<pat::Jet>>
  //   JetCSV(&(jets.ptrToItems));
  // kinVars.push_back(&JetCSV);

  // GenericCollectionSizeVariable<std::vector<pat::Muon>>
  //   numTightMuons(&(tightMuons.ptrToItems), "numTightMuons");
  // kinVars.push_back(&numTightMuons);

  // GenericCollectionSizeVariable<std::vector<pat::Electron>>
  //   numTightElectrons(&(tightElectrons.ptrToItems), "numTightElectrons");
  // kinVars.push_back(&numTightElectrons);

  // GenericCollectionSizeVariable<std::vector<pat::Jet>>
  //   numJets(&(jets.ptrToItems), "numJets");
  // kinVars.push_back(&numJets);
  // numJets.setCutMin(2);

  // GenericCollectionSizeVariable<std::vector<reco::LeafCandidate>>
  //   numLeptons(&(tightLooseLeptons.ptrToItems), "numTightLooseLeptons");
  // kinVars.push_back(&numLeptons);
  //numLeptons.setCutMin(2);

  if (debug > 9) { cout << "Hooking variables to tree" << endl;}
  for (vector<ArbitraryVariable*>::iterator iVar = kinVars.begin();
       iVar != kinVars.end();
       iVar++) {

    (*iVar)->attachToTree (summaryTree);
  }

  int numEvents = 0;
  int numEventsFailCuts = 0;
  int numEventsPassCuts = 0;
  int printEvery = 100;
  
  //vars for vertex loop
  reco::Vertex vertex;
  double minNDOF = 4.0;
  double maxAbsZ = 24.0;
  double maxd0 = 2.;
  int numpv = 0;


  for (ev.toBegin(); !ev.atEnd(); ++ev){
    numEvents++;

    if ((numEvents > myConfig.maxEvents) && myConfig.maxEvents != -1) break;

    if (numEvents == 1 || numEvents % printEvery == 0 )
      cout << "Processing event.... " << numEvents << endl;

    if (debug > 9) cout << "---------->>>>>> Event " << numEvents << endl;
    ////////////////////////////////////////////////////////////
    //
    // count pvs for miniAODhelper
    //
    ////////////////////////////////////////////////////////////
    primaryVertices.initializeRawItems(ev,"offlineSlimmedPrimaryVertices");
    numpv = 0;
    for (reco::VertexCollection::const_iterator iPV = primaryVertices.ptrToItems->begin(); iPV != primaryVertices.ptrToItems->end(); ++iPV){
      bool isGood = ( !(iPV->isFake()) &&
		     (iPV->ndof() >= minNDOF) &&
		     (abs(iPV->z()) <= maxAbsZ) &&
		     (abs(iPV->position().Rho()) <= maxd0)
		     );
      if ( !isGood ) continue;
      if ( numpv == 0 ) vertex = *iPV;
      numpv++;
    }
    
    //cout << "numpv = " << numpv << endl;
    if ( numpv > 0 ){
      //cout << "setting vertex, numpv > 0" << endl;
      miniAODhelper->SetVertex(vertex);
    }
    /////////////////////////////////////////////////////////////
    //
    //    Initialize collections and apply object ids
    //
    //////////////////////////////////////////////////////////////   
    //    events.initializeRawItems(ev,"generator");
    tightLoosePreselectedElectrons.initializeRawItemsSortedByPt(ev,"slimmedElectrons");
    tightLoosePreselectedElectrons.keepSelectedParticles(electronPreselectedID);
    tightElectrons.initializeRawItems(tightLoosePreselectedElectrons.rawItems);
    tightElectrons.keepSelectedParticles(electronTightID);
    tightLooseElectrons.initializeRawItems(tightLoosePreselectedElectrons.rawItems);
    tightLooseElectrons.keepSelectedParticles(electronLooseID);
    looseElectrons.initializeRawItems(tightLoosePreselectedElectrons.rawItems);
    looseElectrons.keepSelectedDifference(electronLooseID, electronTightID);
    preselectedElectrons.initializeRawItems(tightLoosePreselectedElectrons.rawItems);
    preselectedElectrons.keepSelectedDifference(electronPreselectedID, electronLooseID);
    loosePreselectedElectrons.initializeRawItems(tightLoosePreselectedElectrons.rawItems);
    loosePreselectedElectrons.addUnion({looseElectrons.items, preselectedElectrons.items});
    
    tightLoosePreselectedMuons.initializeRawItemsSortedByPt(ev, "slimmedMuons");
    tightLoosePreselectedMuons.keepSelectedParticles(muonPreselectedID);
    tightMuons.initializeRawItems(tightLoosePreselectedMuons.rawItems);
    tightMuons.keepSelectedParticles(muonTightID);
    looseMuons.initializeRawItems(tightLoosePreselectedMuons.rawItems);
    looseMuons.keepSelectedDifference(muonLooseID, muonTightID);
    preselectedMuons.initializeRawItems(tightLoosePreselectedMuons.rawItems);
    preselectedMuons.keepSelectedDifference(muonPreselectedID, muonLooseID);
    tightLooseMuons.initializeRawItems(tightLoosePreselectedMuons.rawItems);
    tightLooseMuons.keepSelectedParticles(muonLooseID);

    // for (pat::MuonCollection::const_iterator iMu = tightMuons.ptrToItems->begin(); iMu != tightMuons.ptrToItems->end(); ++iMu){
    //   leptons->push_back(*iMu);
    // }
    // for (pat::ElectronCollection::const_iterator iMu = tightElectrons.ptrToItems->begin(); iMu != tightElectrons.ptrToItems->end(); ++iMu){
    //   leptons->push_back(*iMu);
    // }

    tightTaus.initializeRawItemsSortedByPt(ev, "slimmedTaus");
    tightTaus.keepSelectedParticles(tauTightID);
    tightLooseTaus.initializeRawItems(tightTaus.rawItems);
    tightLooseTaus.keepSelectedParticles(tauTightID);
    tightLoosePreselectedTaus.initializeRawItems(tightTaus.rawItems);
    tightLoosePreselectedTaus.keepSelectedParticles(tauPreselectedID);

    tightLeptons.resetAndPushBack(tightElectrons.items);
    tightLeptons.pushBackAndSort(tightMuons.items);
    looseLeptons.resetAndPushBack(looseElectrons.items);
    looseLeptons.pushBackAndSort(looseMuons.items);
    preselectedLeptons.resetAndPushBack(preselectedElectrons.items);
    preselectedLeptons.pushBackAndSort(preselectedMuons.items);
    tightLooseLeptons.resetAndPushBack(tightLooseElectrons.items);
    tightLooseLeptons.pushBackAndSort(tightLooseMuons.items);
    tightLoosePreselectedLeptons.resetAndPushBack(tightLoosePreselectedElectrons.items);
    tightLoosePreselectedLeptons.pushBackAndSort(tightLoosePreselectedMuons.items);

    jets.initializeRawItemsSortedByPt(ev, "slimmedJets");
    jets.cleanJets(tightLoosePreselectedMuons.items);
    jets.cleanJets(tightLoosePreselectedElectrons.items);
    

    jets.keepSelectedJets(30.0, 2.4, jetID::jetLoose, '-');
    jetsByCSV.initializeRawItemsSortedByCSV(jets.items);

    jets_30.initializeRawItems(jets.items);
    jets_30.keepSelectedJets(30.0, 2.4, jetID::jetLoose, '-');

    genTopParticles.initializeRawItems(ev,"prunedGenParticles");
    auto topPDGID = [] (reco::GenParticle p) { return (p.pdgId() == 6 ); };
    genTopParticles.keepSelectedParticles(topPDGID);

    genHiggsParticles.initializeRawItems(ev,"prunedGenParticles");
    auto higgsPDGID = [] (reco::GenParticle p) { return (p.pdgId() == 25 ); };
    genHiggsParticles.keepSelectedParticles(higgsPDGID);


    // reset all the vars
    if (debug > 9) cout << "Resetting "  << endl;
    for (vector<ArbitraryVariable*>::iterator iVar = kinVars.begin();
         iVar != kinVars.end();
         iVar++) {

      (*iVar)->reset();
    }

    bool passAllCuts = true;

    if (debug > 9) cout << "Checking cuts "  << endl;

    for (vector<ArbitraryVariable*>::iterator iCut = cutVars.begin();
         iCut != cutVars.end();
         iCut++ ) {

      (*iCut)->evaluate();
      passAllCuts = passAllCuts && (*iCut)->passCut();

    }

    if (!passAllCuts) {
      numEventsFailCuts++;
      continue; //!!!!    Skip The event  ///////////////

    } else {
      numEventsPassCuts++;
    }

    // Now  evaluate the vars
    if (debug > 9) cout << "Evaluating vars "  << endl;

    for (vector<ArbitraryVariable*>::iterator iVar = kinVars.begin();
         iVar != kinVars.end();
         iVar++) {
      (*iVar)->evaluate();
    }

    if (debug > 9) {
      for (vector<ArbitraryVariable*>::iterator iVar = kinVars.begin();
           iVar != kinVars.end();
           iVar++) {

        (*iVar)->print();
        cout << endl;
      }
    }

    // Fill the trees
    if (debug > 9) cout << "Filling tree "  << endl;
    summaryTree->Fill();
    if (debug > 9) cout << "Done with event  " << numEvents  << endl;
  }// end for each event

  cout << "Num Events processed " << numEvents << endl
       << "Passed cuts " << numEventsPassCuts << endl
       << "Failed cuts " << numEventsFailCuts << endl ;

  outputFile->Write();
  outputFile->Close();
}
