#include "ttHMultileptonAnalysis/TemplateMakers/interface/BEANFileInterface.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/HelperLeptonCore.h"

///-------------- Kinematic Variables ------------------
#include "ttHMultileptonAnalysis/TemplateMakers/interface/EveryVariable.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/JobParameters.h"

#include "BEAN/BEANmaker/interface/BtagWeight.h"
#include "BEAN/BEANmaker/interface/BEANhelper.h"

#include "Reflex/Object.h"
#include "Reflex/Type.h"
#include "Reflex/Member.h"
#include "Reflex/Kernel.h"

//----------  Use python utilities to configure
#include "FWCore/PythonParameterSet/interface/PythonProcessDesc.h"
#include "FWCore/ParameterSet/interface/ProcessDesc.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"

bool LeptonCutThisAnalysis (BEANFileInterface * inputCollections) {

  bool passTwoLepton = false;

//   //Collection definitions set by muonID::muonID and electronID::electronID inside main function
//   unsigned numTightMuons = inputCollections->tightMuonCollection->size();
// //   unsigned numLooseMuons = inputCollections->looseMuonCollection->size();
// //   unsigned numAllMuons = inputCollections->tightLoosePreselectedMuonCollection->size();

//   unsigned numTightElectrons = inputCollections->tightElectronCollection->size();
// //   unsigned numLooseElectrons = inputCollections->looseElectronCollection->size();
// //   unsigned numAllElectrons = inputCollections->tightLoosePreselectedElectronCollection->size();

// //   unsigned numTightLeptons = inputCollections->tightLeptonCollection->size();
// //   unsigned numTightLooseLeptons = inputCollections->tightLooseLeptonCollection->size();

// //   unsigned numTightZLeptons = inputCollections->tightZLeptonCollection->size();
// //   unsigned numTightLooseZLeptons = inputCollections->tightLooseZLeptonCollection->size();
// //   unsigned numAllZLeptons = inputCollections->tightLoosePreselectedZLeptonCollection->size();

// //   unsigned numTightNonZLeptons = inputCollections->tightNonZLeptonCollection->size();
// //   unsigned numTightLooseNonZLeptons = inputCollections->tightLooseNonZLeptonCollection->size();
// //   unsigned numAllNonZLeptons = inputCollections->tightLoosePreselectedNonZLeptonCollection->size();

//   if (numTightMuons ==2 || numTightElectrons==2 || (numTightMuons==1 && numTightElectrons==1))
//     passTwoLepton = true;

  unsigned numAllLeptons = inputCollections->tightLoosePreselectedLeptonCollection->size();
  if (numAllLeptons >= 2)
    passTwoLepton = true;

//   return passTwoLepton;
  return true;
}

// void LeptonVarsThisAnalysis(BEANFileInterface * inputCollections, bool passTwoLepton, int & TwoMuon, int & TwoElectron, int & MuonElectron) {
//   //Collection definitions set by muonID::muonID and electronID::electronID inside main function
//   unsigned numTightMuons = inputCollections->tightMuonCollection->size();
//   unsigned numTightElectrons = inputCollections->tightElectronCollection->size();

//   TwoMuon = 0;
//   TwoElectron = 0;
//   MuonElectron = 0;

//   if (!passTwoLepton){
//     return;
//   }

//   if (numTightMuons == 2 ) {
//     TwoMuon = 1;
//     return;
//   }

//   if (numTightElectrons == 2 ) {
//     TwoElectron = 1;
//     return;
//   }

//   if ( numTightElectrons ==1 && numTightMuons==1 ) {
//     MuonElectron = 1;
//     return;
//   }
// }

void getNumExtraPartons(BEANhelper * beanHelper, BEANFileInterface selectedCollections, int & numExtraPartons) {

  numExtraPartons = beanHelper->GetNumExtraPartons(*(selectedCollections.mcParticleCollection));

  return;
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

  return myConfig;
}

int main (int argc, char** argv) {
  // load framework libraries
  gSystem->Load( "libFWCoreFWLite" );
  //gSystem->Load("libNtupleMakerBEANmaker.so");
  AutoLibraryLoader::enable();

  int debug = 0; // levels of debug, 10 is large

  JobParameters myConfig = parseJobOptions(argc, argv);

  TFile * outputFile = new TFile (myConfig.outputFileName.c_str(), "RECREATE");

  outputFile->cd();

  TTree * summaryTree = new TTree("summaryTree", "Summary Event Values");

  fwlite::ChainEvent ev(myConfig.inputFileNames);

  HelperLeptonCore lepHelper;

  // setup the analysis
  // it comes from the lepHelper
  BEANhelper * beanHelper = lepHelper.setupAnalysisParameters("2012_53x", myConfig.sampleName);

  // ---------------------------------------------
  // Note for future development: should these be
  // saved inside the lepHelper somewhere?
  // For now they are ok here
  // ---------------------------------------------

  muonID::muonID muonTightID = muonID::muonSideTightMVA;
  muonID::muonID muonLooseID = muonID::muonSideLooseMVA;
  muonID::muonID muonPreselectedID = muonID::muonSide;
  electronID::electronID electronTightID = electronID::electronSideTightMVA;
  electronID::electronID electronLooseID = electronID::electronSideLooseMVA;
  electronID::electronID electronPreselectedID = electronID::electronSide;

  // declare your kinematic variables that you want
  // to be written out into the tree
  vector<ArbitraryVariable*> kinVars;
  vector<ArbitraryVariable*> cutVars;

  BEANFileInterface selectedCollections;

  GenericCollectionSizeVariable<BNjetCollection> numJets(&(selectedCollections.jetCollection), "numJets");
  kinVars.push_back(&numJets);
  numJets.setCutMin(2);
  //cutVars.push_back(&numJets);

  GenericCollectionSizeVariable<BNjetCollection> numLooseBJets(&(selectedCollections.jetCollectionLooseCSV), "numLooseBJets");
  kinVars.push_back(&numLooseBJets);

  GenericCollectionSizeVariable<BNjetCollection> numMediumBJets(&(selectedCollections.jetCollectionMediumCSV), "numMediumBJets");
  kinVars.push_back(&numMediumBJets);

  GenericCollectionSizeVariable<BNjetCollection> numTightBJets(&(selectedCollections.jetCollectionTightCSV), "numTightBJets");
  kinVars.push_back(&numTightBJets);

  GenericCollectionSizeVariable<BNleptonCollection> numTightLeptons(&(selectedCollections.tightLeptonCollection), "numTightLeptons");
  kinVars.push_back(&numTightLeptons);
  
  GenericCollectionSizeVariable<BNleptonCollection> numTightLooseLeptons(&(selectedCollections.tightLooseLeptonCollection), "numTightLooseLeptons");
  kinVars.push_back(&numTightLooseLeptons);

  GenericCollectionSizeVariable<BNleptonCollection> numAllLeptons(&(selectedCollections.tightLoosePreselectedLeptonCollection), "numAllLeptons");
  kinVars.push_back(&numAllLeptons);
  numAllLeptons.setCutMin(2);
  cutVars.push_back(&numAllLeptons);

  GenericCollectionSizeVariable<BNmuonCollection> numTightMuons(&(selectedCollections.tightMuonCollection), "numTightMuons");
  kinVars.push_back(&numTightMuons);
  
  GenericCollectionSizeVariable<BNmuonCollection> numTightLooseMuons(&(selectedCollections.tightLooseMuonCollection), "numTightLooseMuons");
  kinVars.push_back(&numTightLooseMuons);

  GenericCollectionSizeVariable<BNmuonCollection> numAllMuons(&(selectedCollections.tightLoosePreselectedMuonCollection), "numAllMuons");
  kinVars.push_back(&numAllMuons);

  GenericCollectionSizeVariable<BNelectronCollection> numTightElectrons(&(selectedCollections.tightElectronCollection), "numTightElectrons");
  kinVars.push_back(&numTightElectrons);
  
  GenericCollectionSizeVariable<BNelectronCollection> numTightLooseElectrons(&(selectedCollections.tightLooseElectronCollection), "numTightLooseElectrons");
  kinVars.push_back(&numTightLooseElectrons);

  GenericCollectionSizeVariable<BNelectronCollection> numAllElectrons(&(selectedCollections.tightLoosePreselectedElectronCollection), "numAllElectrons");
  kinVars.push_back(&numAllElectrons);

  GenericCollectionSizeVariable<BNleptonCollection> numTightZLeptons(&(selectedCollections.tightZLeptonCollection), "numTightZLeptons");
  kinVars.push_back(&numTightZLeptons);

  GenericCollectionSizeVariable<BNleptonCollection> numTightLooseZLeptons(&(selectedCollections.tightLooseZLeptonCollection), "numTightLooseZLeptons");
  kinVars.push_back(&numTightLooseZLeptons);

  GenericCollectionSizeVariable<BNleptonCollection> numAllZLeptons(&(selectedCollections.tightLoosePreselectedZLeptonCollection), "numAllZLeptons");
  kinVars.push_back(&numAllZLeptons);

  GenericCollectionSizeVariable<BNleptonCollection> numTightNonZLeptons(&(selectedCollections.tightNonZLeptonCollection), "numTightNonZLeptons");
  kinVars.push_back(&numTightNonZLeptons);

  GenericCollectionSizeVariable<BNleptonCollection> numTightLooseNonZLeptons(&(selectedCollections.tightLooseNonZLeptonCollection), "numTightLooseNonZLeptons");
  kinVars.push_back(&numTightLooseNonZLeptons);

  GenericCollectionSizeVariable<BNleptonCollection> numAllNonZLeptons(&(selectedCollections.tightLoosePreselectedNonZLeptonCollection), "numAllNonZLeptons");
  kinVars.push_back(&numAllNonZLeptons);

// //   GenericCollectionSizeVariable<BNleptonCollection> numTightLeptons(&(selectedCollections.tightLeptonCollection), "numTightLeptons");
// //   kinVars.push_back(&numTightLeptons);
//   if (myConfig.sampleName.find("NP_sideband") == std::string::npos) { //All samples except NP_sideband
//     std::cout << "Sample is not a sideband" << std::endl;
//     numTightLeptons.setCutMin(2);
//   }
//   else if (myConfig.sampleName.find("NP_sideband") != std::string::npos) { //NP_sideband samples
//     std::cout << "Sample is a sideband" << std::endl;
//     //Cut to require opposite-sign leptons
//     numTightLeptons.setCutMin(1);
//   }
//   cutVars.push_back(&numTightLeptons);

  //ttH hadrons reweighting
  CSVWeights myCSV(&lepHelper);
  kinVars.push_back(&myCSV);

  //Btag POG reweighting
  vector<pair<string, double>> WPs = {make_pair("CSVT", 0.898), make_pair("CSVM", 0.679), make_pair("CSVL", 0.244)};
  BTagWeights myBTagWeights(WPs);
  kinVars.push_back(&myBTagWeights);

  PUWeights myPU(&lepHelper);
  kinVars.push_back(&myPU);

  TopPtWeights myTopPt(&lepHelper);
  kinVars.push_back(&myTopPt);

  LeptonIDAndIsoScaleFactors myLepIDAndIsoSF(&lepHelper, muonTightID, muonLooseID, electronTightID, electronLooseID);
  kinVars.push_back(&myLepIDAndIsoSF);

  SSLeptonTriggerScaleFactors myLepTrig(&lepHelper);
  kinVars.push_back(&myLepTrig);

  TightChargeAndLepMVAScaleFactors myTightChargeAndLepMVASFs(2);
  kinVars.push_back(&myTightChargeAndLepMVASFs);

  CleanEventVars myClean (&lepHelper);
  kinVars.push_back(&myClean);

  CheckTwoLepTrigger checkTrig (&lepHelper);
  kinVars.push_back(&checkTrig);

//   LepMVAs<BNleptonCollection> myLepMVAsTightLeptons(&lepHelper, &(selectedCollections.tightLeptonCollection), "tight_leptons_by_pt", 4);
//   kinVars.push_back(&myLepMVAsTightLeptons);

//   LepMVAs<BNleptonCollection> myLepMVAsTightLooseLeptons(&lepHelper, &(selectedCollections.tightLooseLeptonCollection), "tightLoose_leptons_by_pt", 4);
//   kinVars.push_back(&myLepMVAsTightLooseLeptons);

  LepMVAs<BNleptonCollection> myLepMVAsAllLeptons(&lepHelper, &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 4);
  kinVars.push_back(&myLepMVAsAllLeptons);

//   LepMVAs<BNleptonCollection> myLepMVAsTightZLeptons(&lepHelper, &(selectedCollections.tightZLeptonCollection), "tightZ_leptons_by_pt", 2);
//   kinVars.push_back(&myLepMVAsTightZLeptons);

//   LepMVAs<BNleptonCollection> myLepMVAsTightLooseZLeptons(&lepHelper, &(selectedCollections.tightLooseZLeptonCollection), "tightLooseZ_leptons_by_pt", 2);
//   kinVars.push_back(&myLepMVAsTightLooseZLeptons);

  LepMVAs<BNleptonCollection> myLepMVAsAllZLeptons(&lepHelper, &(selectedCollections.tightLoosePreselectedZLeptonCollection), "allZ_leptons_by_pt", 2);
  kinVars.push_back(&myLepMVAsAllZLeptons);

//   LepMVAs<BNleptonCollection> myLepMVAsTightNonZLeptons(&lepHelper, &(selectedCollections.tightNonZLeptonCollection), "tightNonZ_leptons_by_pt", 2);
//   kinVars.push_back(&myLepMVAsTightNonZLeptons);

//   LepMVAs<BNleptonCollection> myLepMVAsTightLooseNonZLeptons(&lepHelper, &(selectedCollections.tightLooseNonZLeptonCollection), "tightLooseNonZ_leptons_by_pt", 2);
//   kinVars.push_back(&myLepMVAsTightLooseNonZLeptons);

  LepMVAs<BNleptonCollection> myLepMVAsAllNonZLeptons(&lepHelper, &(selectedCollections.tightLoosePreselectedNonZLeptonCollection), "allNonZ_leptons_by_pt", 2);
  kinVars.push_back(&myLepMVAsAllNonZLeptons);

//   DataDrivenFR<BNleptonCollection> myDataDrivenFR2Tight(&lepHelper, &(selectedCollections.tightLoosePreselectedLeptonCollection),
//                                                         2, 0.7, "FR_merged_data", "QF_data_el", "_2Tight");
//   kinVars.push_back(&myDataDrivenFR2Tight);
  
//   DataDrivenFR<BNleptonCollection> myDataDrivenFR2Loose(&lepHelper, &(selectedCollections.tightLoosePreselectedLeptonCollection),
//                                                         2, -0.3, "FR_merged_data", "QF_data_el", "_2Loose");
//   kinVars.push_back(&myDataDrivenFR2Loose);
  
//   DataDrivenFR<BNleptonCollection> myDataDrivenFR3Tight(&lepHelper, &(selectedCollections.tightLoosePreselectedLeptonCollection),
//                                                         3, 0.7, "FR_merged_data", "QF_data_el", "_3Tight");
//   kinVars.push_back(&myDataDrivenFR3Tight);
  
//   DataDrivenFR<BNleptonCollection> myDataDrivenFR3Loose(&lepHelper, &(selectedCollections.tightLoosePreselectedLeptonCollection),
//                                                         3, -0.3, "FR_merged_data", "QF_data_el", "_3Loose");
//   kinVars.push_back(&myDataDrivenFR3Loose);
  
//   DataDrivenFR<BNleptonCollection> myDataDrivenFR4Tight(&lepHelper, &(selectedCollections.tightLoosePreselectedLeptonCollection),
//                                                         4, 0.7, "FR_merged_data", "QF_data_el", "_4Tight");
//   kinVars.push_back(&myDataDrivenFR4Tight);
  
//   DataDrivenFR<BNleptonCollection> myDataDrivenFR4Loose(&lepHelper, &(selectedCollections.tightLoosePreselectedLeptonCollection),
//                                                         4, -0.3, "FR_merged_data", "QF_data_el", "_4Loose");
//   kinVars.push_back(&myDataDrivenFR4Loose);
  
//   DataDrivenFR<BNleptonCollection> myDataDrivenFR2LooseZ(&lepHelper, &(selectedCollections.tightLoosePreselectedZLeptonCollection),
//                                                          2, -0.3, "FR_merged_data", "QF_data_el", "_2LooseZ");
//   kinVars.push_back(&myDataDrivenFR2LooseZ);
  
//   DataDrivenFR<BNleptonCollection> myDataDrivenFR1TightNonZ(&lepHelper, &(selectedCollections.tightLoosePreselectedNonZLeptonCollection),
//                                                             1, 0.7, "FR_merged_data", "QF_data_el", "_1TightNonZ");
//   kinVars.push_back(&myDataDrivenFR1TightNonZ);
  
  DBCorrectedRelIsoDR04s myDBCorrectedRelIsoDR04s(&lepHelper, 4);
  kinVars.push_back(&myDBCorrectedRelIsoDR04s);

//   HiggsDecayType myHiggsDecayType(&lepHelper);
//   kinVars.push_back(&myHiggsDecayType);

//   // Full event kinematics

//   TwoObjectKinematic<BNleptonCollection,BNmetCollection> mySumLep1Lep2MetPt("pt", "sum", "sum_lep1pt_lep2pt_met",
//                                                                             &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 2,
//                                                                             &(selectedCollections.metCollection), "met", 1, 1);
//   kinVars.push_back(&mySumLep1Lep2MetPt);

//   TwoObjectKinematic<BNjetCollection,BNjetCollection> myWLikeDijetMass81("mass", "closest_to", "WLike_dijet_mass",
//                                                                          &(selectedCollections.jetCollectionNotMediumCSV), "medium_untags_by_pt", 1, 99,
//                                                                          &(selectedCollections.jetCollectionNotMediumCSV), "medium_untags_by_pt", 1, 99,
//                                                                          81);
//   kinVars.push_back(&myWLikeDijetMass81);

//   TwoObjectKinematic<BNjetCollection,BNjetCollection> mySumJetPt("pt", "sum", "sum_jet_pt",
//                                                                  &(selectedCollections.jetCollection), "jets_by_pt", 1, 99,
//                                                                  &(selectedCollections.jetCollection), "jets_by_pt", 1, 99);
//   kinVars.push_back(&mySumJetPt);

// //   TwoObjectKinematic<BNjetCollection,BNjetCollection> myMassOfJets("mass", "vector_sum", "mass_of_jets",
// //                                                                    &(selectedCollections.jetCollection), "jets_by_pt", 1, 99,
// //                                                                    &(selectedCollections.jetCollection), "jets_by_pt", 1, 99);
// //   kinVars.push_back(&myMassOfJets);
  
// //   TwoObjectKinematic<BNleptonCollection,BNjetCollection> myMassOfEverything_tight("mass", "vector_sum", "mass_of_everything_tight",
// //                                                                                   &(selectedCollections.tightLeptonCollection), "tight_leptons_by_pt", 1, 99,
// //                                                                                   &(selectedCollections.jetCollection), "jets_by_pt", 1, 99);
// //   kinVars.push_back(&myMassOfEverything_tight);
  
// //   TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMinDeltaRLepLep_tight("deltaR", "min", "min_deltaR_leplep_tight",
// //                                                                                     &(selectedCollections.tightLeptonCollection), "tight_leptons_by_pt", 1, 99,
// //                                                                                     &(selectedCollections.tightLeptonCollection), "tight_leptons_by_pt", 1, 99);
// //   kinVars.push_back(&myMinDeltaRLepLep_tight);
  
// //   TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMinDeltaRLepLep_tightLoose("deltaR", "min", "min_deltaR_leplep_tightLoose",
// //                                                                                     &(selectedCollections.tightLooseLeptonCollection), "tightLoose_leptons_by_pt", 1, 99,
// //                                                                                     &(selectedCollections.tightLooseLeptonCollection), "tightLoose_leptons_by_pt", 1, 99);
// //   kinVars.push_back(&myMinDeltaRLepLep_tightLoose);
  
//   TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMinDeltaRLepLep_all("deltaR", "min", "min_deltaR_leplep_all",
//                                                                                     &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99,
//                                                                                     &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99);
//   kinVars.push_back(&myMinDeltaRLepLep_all);
  
// //   TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMaxDeltaEtaLepLep_tight("deltaEta", "maxAbs", "maxAbs_deltaEta_leplep_tight",
// //                                                                                     &(selectedCollections.tightLeptonCollection), "tight_leptons_by_pt", 1, 99,
// //                                                                                     &(selectedCollections.tightLeptonCollection), "tight_leptons_by_pt", 1, 99);
// //   kinVars.push_back(&myMaxDeltaEtaLepLep_tight);
  
// //   TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMaxDeltaEtaLepLep_tightLoose("deltaEta", "maxAbs", "maxAbs_deltaEta_leplep_tightLoose",
// //                                                                                     &(selectedCollections.tightLooseLeptonCollection), "tightLoose_leptons_by_pt", 1, 99,
// //                                                                                     &(selectedCollections.tightLooseLeptonCollection), "tightLoose_leptons_by_pt", 1, 99);
// //   kinVars.push_back(&myMaxDeltaEtaLepLep_tightLoose);
  
//   TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMaxDeltaEtaLepLep_all("deltaEta", "maxAbs", "maxAbs_deltaEta_leplep_all",
//                                                                                     &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99,
//                                                                                     &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99);
//   kinVars.push_back(&myMaxDeltaEtaLepLep_all);
  
//   TwoObjectKinematic<BNleptonCollection,BNjetCollection> myMinDeltaRLepJet_all("deltaR", "min", "min_deltaR_lepjet_all",
//                                                                                &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99,
//                                                                                &(selectedCollections.jetCollection), "jets_by_pt", 1, 99);
//   kinVars.push_back(&myMinDeltaRLepJet_all);
  
//   TwoObjectKinematic<BNjetCollection,BNjetCollection> myMinDeltaRJetJet("deltaR", "min", "min_deltaR_jetjet",
//                                                                         &(selectedCollections.jetCollection), "jets_by_pt", 1, 99,
//                                                                         &(selectedCollections.jetCollection), "jets_by_pt", 1, 99);
//   kinVars.push_back(&myMinDeltaRJetJet);
  
//   TwoObjectKinematic<BNjetCollection,BNjetCollection> myMaxDeltaEtaJetJet("deltaEta", "maxAbs", "maxAbs_deltaEta_jetjet",
//                                                                           &(selectedCollections.jetCollection), "jets_by_pt", 1, 99,
//                                                                           &(selectedCollections.jetCollection), "jets_by_pt", 1, 99);
//   kinVars.push_back(&myMaxDeltaEtaJetJet);
  
  
//   // Two lepton kinematics
  
// //   TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMinMassLepLepSFOSTight("mass", "min", "min_mass_leplep_SFOS_tight",
// //                                                                                      &(selectedCollections.tightLeptonCollection), "tight_leptons_by_pt", 1, 99,
// //                                                                                      &(selectedCollections.tightLeptonCollection), "tight_leptons_by_pt", 1, 99,
// //                                                                                      -99, "same_flavour", "opposite_sign");
// //   kinVars.push_back(&myMinMassLepLepSFOSTight);
  
// //   TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMinMassLepLepSFOSTightLoose("mass", "min", "min_mass_leplep_SFOS_tightLoose",
// //                                                                                           &(selectedCollections.tightLooseLeptonCollection), "tightLoose_leptons_by_pt", 1, 99,
// //                                                                                           &(selectedCollections.tightLooseLeptonCollection), "tightLoose_leptons_by_pt", 1, 99,
// //                                                                                           -99, "same_flavour", "opposite_sign");
// //   kinVars.push_back(&myMinMassLepLepSFOSTightLoose);
  
//   TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMinMassLepLepSFOSAll("mass", "min", "min_mass_leplep_SFOS_all",
//                                                                                 &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99,
//                                                                                 &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99,
//                                                                                 -99, "same_flavour", "opposite_sign");
//   kinVars.push_back(&myMinMassLepLepSFOSAll);

//   TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMinMassLepLep("mass", "min", "min_mass_leplep_all",
//                                                                             &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99,
//                                                                             &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99);
//   kinVars.push_back(&myMinMassLepLep);

  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZLikeMassLepLepSFOSTight("mass", "closest_to", "ZLike_mass_leplep_SFOS_tight",
                                                                                  &(selectedCollections.tightLeptonCollection), "tight_leptons_by_pt", 1, 99,
                                                                                  &(selectedCollections.tightLeptonCollection), "tight_leptons_by_pt", 1, 99,
                                                                                  91.2, "same_flavour", "opposite_sign");
  kinVars.push_back(&myZLikeMassLepLepSFOSTight);  

  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZLikeMassLepLepSFOSTightLoose("mass", "closest_to", "ZLike_mass_leplep_SFOS_tightLoose",
                                                                                            &(selectedCollections.tightLooseLeptonCollection), "tightLoose_leptons_by_pt", 1, 99,
                                                                                            &(selectedCollections.tightLooseLeptonCollection), "tightLoose_leptons_by_pt", 1, 99,
                                                                                            91.2, "same_flavour", "opposite_sign");
  kinVars.push_back(&myZLikeMassLepLepSFOSTightLoose);  

  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZLikeMassLepLepSFOSAll("mass", "closest_to", "ZLike_mass_leplep_SFOS_all",
                                                                                     &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99,
                                                                                     &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99,
                                                                                     91.2, "same_flavour", "opposite_sign");
  kinVars.push_back(&myZLikeMassLepLepSFOSAll);  

//   TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZLikePtLepLepSFOSTight("vectPt", "max", "ZLike_pt_leplep_SFOS_tight",
//                                                                                           &(selectedCollections.tightZLeptonCollection), "tightZ_leptons_by_pt", 1, 99,
//                                                                                           &(selectedCollections.tightZLeptonCollection), "tightZ_leptons_by_pt", 1, 99);
//   kinVars.push_back(&myZLikePtLepLepSFOSTight);

// //   TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZLikePtLepLepSFOSTightLoose("vectPt", "max", "ZLike_pt_leplep_SFOS_tightLoose",
// //                                                                                           &(selectedCollections.tightLooseZLeptonCollection), "tightLooseZ_leptons_by_pt", 1, 99,
// //                                                                                           &(selectedCollections.tightLooseZLeptonCollection), "tightLooseZ_leptons_by_pt", 1, 99);
// //   kinVars.push_back(&myZLikePtLepLepSFOSTightLoose);

//   TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZLikePtLepLepSFOSAll("vectPt", "max", "ZLike_pt_leplep_SFOS_all",
//                                                                                 &(selectedCollections.tightLoosePreselectedZLeptonCollection), "allZ_leptons_by_pt", 1, 99,
//                                                                                 &(selectedCollections.tightLoosePreselectedZLeptonCollection), "allZ_leptons_by_pt", 1, 99);
//   kinVars.push_back(&myZLikePtLepLepSFOSAll);

// //   TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZLikeEtaLepLepSFOSTight("vectEta", "max", "ZLike_eta_leplep_SFOS_tight",
// //                                                                                           &(selectedCollections.tightZLeptonCollection), "tightZ_leptons_by_pt", 1, 99,
// //                                                                                           &(selectedCollections.tightZLeptonCollection), "tightZ_leptons_by_pt", 1, 99);
// //   kinVars.push_back(&myZLikeEtaLepLepSFOSTight);

// //   TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZLikeEtaLepLepSFOSTightLoose("vectEta", "max", "ZLike_eta_leplep_SFOS_tightLoose",
// //                                                                                           &(selectedCollections.tightLooseZLeptonCollection), "tightLooseZ_leptons_by_pt", 1, 99,
// //                                                                                           &(selectedCollections.tightLooseZLeptonCollection), "tightLooseZ_leptons_by_pt", 1, 99);
// //   kinVars.push_back(&myZLikeEtaLepLepSFOSTightLoose);

//   TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZLikeEtaLepLepSFOSAll("vectEta", "max", "ZLike_eta_leplep_SFOS_all",
//                                                                                 &(selectedCollections.tightLoosePreselectedZLeptonCollection), "allZ_leptons_by_pt", 1, 99,
//                                                                                 &(selectedCollections.tightLoosePreselectedZLeptonCollection), "allZ_leptons_by_pt", 1, 99);
//   kinVars.push_back(&myZLikeEtaLepLepSFOSAll);

  
//   //Variables for CERN same-sign dilepton BDT
//   TwoObjectKinematic<BNleptonCollection,BNjetCollection> myMHT("pt", "vector_sum", "mht",
//                                                                &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99,
//                                                                &(selectedCollections.jetCollection), "jets_by_pt", 1, 99);
//   kinVars.push_back(&myMHT);
  
//   TwoObjectKinematic<BNleptonCollection,BNjetCollection> myMinDeltaRLep2Jet("deltaR", "min", "mindr_lep2_jet",
//                                                                             &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 2, 2,
//                                                                             &(selectedCollections.jetCollection), "jets_by_pt", 1, 99);
//   kinVars.push_back(&myMinDeltaRLep2Jet);

//   TwoObjectKinematic<BNmetCollection,BNleptonCollection> myMtMetLep("MT", "all_pairs", "",
//                                                                     &(selectedCollections.metCollection), "met", 1, 1,
//                                                                     &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 2);
//   kinVars.push_back(&myMtMetLep);

//   TwoObjectKinematic<BNleptonCollection,BNjetCollection> mySumPt("pt", "sum", "sum_pt",
//                                                                  &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99,
//                                                                  &(selectedCollections.jetCollection), "jets_by_pt", 1, 99);
//   kinVars.push_back(&mySumPt);

//   TightCharges myTightCharges(&(selectedCollections.tightLoosePreselectedLeptonCollection), "CERN_tight_charge", "all_leptons_by_pt", 2);
//   kinVars.push_back(&myTightCharges);
//   //myTightCharges.setCut("pass");

// //   int TwoMuon = 0;
// //   int TwoElectron = 0;
// //   int MuonElectron = 0;

// //   summaryTree->Branch("TwoMuon", &TwoMuon);
// //   summaryTree->Branch("TwoElectron", &TwoElectron);
// //   summaryTree->Branch("MuonElectron", &MuonElectron);

//   /////////////////////////////////
//   //// Leptons
//   /////////////////////////////////

//   // pT
  
// //   GenericCollectionMember<double, BNleptonCollection> tightLeptonPt(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLeptonCollection),
// //                                                                   "pt", "tight_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
// //   kinVars.push_back(&tightLeptonPt);

// //   GenericCollectionMember<double, BNleptonCollection> tightLooseLeptonPt(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLooseLeptonCollection),
// //                                                                   "pt", "tightLoose_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
// //   kinVars.push_back(&tightLooseLeptonPt);

  GenericCollectionMember<double, BNleptonCollection> allLeptonPt(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                                  "pt", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonPt);

// //   GenericCollectionMember<double, BNleptonCollection> tightZLeptonPt(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightZLeptonCollection),
// //                                                                   "pt", "tightZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
// //   kinVars.push_back(&tightZLeptonPt);

// //   GenericCollectionMember<double, BNleptonCollection> tightLooseZLeptonPt(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLooseZLeptonCollection),
// //                                                                   "pt", "tightLooseZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
// //   kinVars.push_back(&tightLooseZLeptonPt);

//   GenericCollectionMember<double, BNleptonCollection> allZLeptonPt(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedZLeptonCollection),
//                                                                   "pt", "allZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&allZLeptonPt);

// //   GenericCollectionMember<double, BNleptonCollection> tightNonZLeptonPt(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightNonZLeptonCollection),
// //                                                                   "pt", "tightNonZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
// //   kinVars.push_back(&tightNonZLeptonPt);

// //   GenericCollectionMember<double, BNleptonCollection> tightLooseNonZLeptonPt(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLooseNonZLeptonCollection),
// //                                                                   "pt", "tightLooseNonZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
// //   kinVars.push_back(&tightLooseNonZLeptonPt);

//   GenericCollectionMember<double, BNleptonCollection> allNonZLeptonPt(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedNonZLeptonCollection),
//                                                                   "pt", "allNonZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&allNonZLeptonPt);

//   // eta
  
// //   GenericCollectionMember<double, BNleptonCollection> tightLeptonEta(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLeptonCollection),
// //                                                                   "eta", "tight_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
// //   kinVars.push_back(&tightLeptonEta);

// //   GenericCollectionMember<double, BNleptonCollection> tightLooseLeptonEta(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLooseLeptonCollection),
// //                                                                   "eta", "tightLoose_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
// //   kinVars.push_back(&tightLooseLeptonEta);

  GenericCollectionMember<double, BNleptonCollection> allLeptonEta(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                                  "eta", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonEta);

// //   GenericCollectionMember<double, BNleptonCollection> tightZLeptonEta(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightZLeptonCollection),
// //                                                                   "eta", "tightZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
// //   kinVars.push_back(&tightZLeptonEta);

// //   GenericCollectionMember<double, BNleptonCollection> tightLooseZLeptonEta(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLooseZLeptonCollection),
// //                                                                   "eta", "tightLooseZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
// //   kinVars.push_back(&tightLooseZLeptonEta);

//   GenericCollectionMember<double, BNleptonCollection> allZLeptonEta(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedZLeptonCollection),
//                                                                   "eta", "allZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&allZLeptonEta);

// //   GenericCollectionMember<double, BNleptonCollection> tightNonZLeptonEta(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightNonZLeptonCollection),
// //                                                                   "eta", "tightNonZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
// //   kinVars.push_back(&tightNonZLeptonEta);

// //   GenericCollectionMember<double, BNleptonCollection> tightLooseNonZLeptonEta(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLooseNonZLeptonCollection),
// //                                                                   "eta", "tightLooseNonZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
// //   kinVars.push_back(&tightLooseNonZLeptonEta);

//   GenericCollectionMember<double, BNleptonCollection> allNonZLeptonEta(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedNonZLeptonCollection),
//                                                                   "eta", "allNonZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&allNonZLeptonEta);

//   // isMuon / isElectron
  
// //   GenericCollectionMember<int, BNleptonCollection> tightNonZLeptonIsMuon(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightNonZLeptonCollection),
// //                                                                        "isMuon", "tightNonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
// //   kinVars.push_back(&tightNonZLeptonIsMuon);

// //   GenericCollectionMember<int, BNleptonCollection> tightLooseNonZLeptonIsMuon(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLooseNonZLeptonCollection),
// //                                                                        "isMuon", "tightLooseNonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
// //   kinVars.push_back(&tightLooseNonZLeptonIsMuon);

  GenericCollectionMember<int, BNleptonCollection> allNonZLeptonIsMuon(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedNonZLeptonCollection),
                                                                       "isMuon", "allNonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allNonZLeptonIsMuon);

// //   GenericCollectionMember<int, BNleptonCollection> tightNonZLeptonIsElectron(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightNonZLeptonCollection),
// //                                                                        "isElectron", "tightNonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
// //   kinVars.push_back(&tightNonZLeptonIsElectron);

// //   GenericCollectionMember<int, BNleptonCollection> tightLooseNonZLeptonIsElectron(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLooseNonZLeptonCollection),
// //                                                                        "isElectron", "tightLooseNonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
// //   kinVars.push_back(&tightLooseNonZLeptonIsElectron);

  GenericCollectionMember<int, BNleptonCollection> allNonZLeptonIsElectron(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedNonZLeptonCollection),
                                                                       "isElectron", "allNonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allNonZLeptonIsElectron);

//   // tkCharge
  
// //   GenericCollectionMember<int, BNleptonCollection> tightLeptonTkCharge(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLeptonCollection),
// //                                                                   "tkCharge", "tight_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
// //   kinVars.push_back(&tightLeptonTkCharge);

// //   GenericCollectionMember<int, BNleptonCollection> tightLooseLeptonTkCharge(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLooseLeptonCollection),
// //                                                                   "tkCharge", "tightLoose_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
// //   kinVars.push_back(&tightLooseLeptonTkCharge);

//   GenericCollectionMember<int, BNleptonCollection> allLeptonTkCharge(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),
//                                                                   "tkCharge", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
//   kinVars.push_back(&allLeptonTkCharge);

// //   GenericCollectionMember<int, BNleptonCollection> tightNonZLeptonTkCharge(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightNonZLeptonCollection),
// //                                                                   "tkCharge", "tightNonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
// //   kinVars.push_back(&tightNonZLeptonTkCharge);

// //   GenericCollectionMember<int, BNleptonCollection> tightLooseNonZLeptonTkCharge(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLooseNonZLeptonCollection),
// //                                                                   "tkCharge", "tightLooseNonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
// //   kinVars.push_back(&tightLooseNonZLeptonTkCharge);

//   GenericCollectionMember<int, BNleptonCollection> allNonZLeptonTkCharge(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedNonZLeptonCollection),
//                                                                   "tkCharge", "allNonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
//   kinVars.push_back(&allNonZLeptonTkCharge);

// //   if (myConfig.sampleName.find("QF_sideband") == std::string::npos) { //All samples except QF_sideband
// //     //Cut to require same-sign leptons
// //     auto tkChargeCut = [] (vector<BranchInfo<int>> vars) { return ((vars[0].branchVal * vars[1].branchVal) > 0); };
// //     allLeptonTkCharge.setCut(tkChargeCut);
// //   }
// //   else if (myConfig.sampleName.find("QF_sideband") != std::string::npos) { //QF_sideband samples
// //     //Cut to require opposite-sign leptons
// //     auto tkChargeCut = [] (vector<BranchInfo<int>> vars) { return ((vars[0].branchVal * vars[1].branchVal) < 0); };
// //     allLeptonTkCharge.setCut(tkChargeCut);
// //   }
// //   cutVars.push_back(&allLeptonTkCharge);

  GenericCollectionMember<double, BNleptonCollection> allLeptonSIP(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                                   "SIP", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonSIP);

  GenericCollectionMember<double, BNleptonCollection> allLeptonD0(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                                  "correctedD0Vertex", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonD0);

  GenericCollectionMember<double, BNleptonCollection> allLeptonDZ(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                                  "correctedDZ", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonDZ);

  GenericCollectionMember<double, BNleptonCollection> allLeptonIP(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                                               "IP", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonIP);

  GenericCollectionMember<double, BNleptonCollection> allLeptonIPError(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                                                    "IPError", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonIPError);

// //   /////////////////////////////////
// //   //// Muons
// //   /////////////////////////////////

// //   GenericCollectionMember<double, BNmuonCollection> allMuonPt(Reflex::Type::ByName("BNmuon"), &(selectedCollections.tightLoosePreselectedMuonCollection),
// //                                                               "pt", "all_muons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
// //   kinVars.push_back(&allMuonPt);

// //   GenericCollectionMember<double, BNmuonCollection> allMuonEta(Reflex::Type::ByName("BNmuon"), &(selectedCollections.tightLoosePreselectedMuonCollection),
// //                                                                "eta", "all_muons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
// //   kinVars.push_back(&allMuonEta);

//   /////////////////////////////////
//   //// Electrons
//   /////////////////////////////////

// //   GenericCollectionMember<int, BNelectronCollection> tightElectronNumExpInnerHits(Reflex::Type::ByName("BNelectron"), &(selectedCollections.tightElectronCollection),
// //                                                                                 "numberOfExpectedInnerHits", "tight_electrons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
// //   kinVars.push_back(&tightElectronNumExpInnerHits);

// //   GenericCollectionMember<int, BNelectronCollection> tightElectronPassConvVeto(Reflex::Type::ByName("BNelectron"), &(selectedCollections.tightElectronCollection),
// //                                                                              "passConvVeto", "tight_electrons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
// //   kinVars.push_back(&tightElectronPassConvVeto);

// // //   GenericCollectionMember<double, BNelectronCollection> allElectronEta(Reflex::Type::ByName("BNelectron"), &(selectedCollections.tightLoosePreselectedElectronCollection),
// // //                                                                        "eta", "all_electrons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
// // //   kinVars.push_back(&allElectronEta);

// // //   GenericCollectionMember<double, BNelectronCollection> allElectronPt(Reflex::Type::ByName("BNelectron"), &(selectedCollections.tightLoosePreselectedElectronCollection),
// // //                                                                       "pt", "all_electrons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
// // //   kinVars.push_back(&allElectronPt);

  /////////////////////////////////////
  //// REQUIRED - Properties of muons and electrons for lepton selection
  /////////////////////////////////////

  GenericCollectionMember<int, BNmuonCollection> allMuonPFmuon(Reflex::Type::ByName("BNmuon"), &(selectedCollections.tightLoosePreselectedMuonCollection),
                                                               "isPFMuon", "all_muons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allMuonPFmuon);

  GenericCollectionMember<int, BNmuonCollection> allMuonGlobalMuon(Reflex::Type::ByName("BNmuon"), &(selectedCollections.tightLoosePreselectedMuonCollection),
                                                                   "isGlobalMuon", "all_muons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allMuonGlobalMuon);

  GenericCollectionMember<int, BNmuonCollection> allMuonTrackerMuon(Reflex::Type::ByName("BNmuon"), &(selectedCollections.tightLoosePreselectedMuonCollection),
                                                                    "isTrackerMuon", "all_muons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allMuonTrackerMuon);

  GenericCollectionMember<int, BNelectronCollection> allElectronNumExpInnerHits(Reflex::Type::ByName("BNelectron"), &(selectedCollections.tightLoosePreselectedElectronCollection),
                                                                                "numberOfExpectedInnerHits", "all_electrons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allElectronNumExpInnerHits);

  GenericCollectionMember<int, BNelectronCollection> allElectronPassConvVeto(Reflex::Type::ByName("BNelectron"), &(selectedCollections.tightLoosePreselectedElectronCollection),
                                                                             "passConvVeto", "all_electrons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allElectronPassConvVeto);

  /////////////////////////////////////
  //// END REQUIRED - Properties of muons and electrons for lepton selection
  ///////////////////////////////////// 

//   /////////////////////////////////
//   //// Jets
//   /////////////////////////////////


//   ////////// all jets //////////
//   GenericCollectionMember<double, BNjetCollection> allJetPt(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetCollection),
//                                                             "pt", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
//   kinVars.push_back(&allJetPt);

//   GenericCollectionMember<double, BNjetCollection> allJetEta(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetCollection),
//                                                              "eta", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
//   kinVars.push_back(&allJetEta);

//   GenericCollectionMember<double, BNjetCollection> allJetCSV(Reflex::Type::ByName("BNjet"),  &(selectedCollections.jetCollection),
//                                                              "btagCombinedSecVertex", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
//   kinVars.push_back(&allJetCSV);

//   GenericCollectionMember<double, BNjetCollection> mediumBJetPt(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetCollectionMediumCSV),
//                                                             "pt", "medium_tags_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&mediumBJetPt);

//   GenericCollectionMember<double, BNjetCollection> mediumBJetEta(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetCollectionMediumCSV),
//                                                              "eta", "medium_tags_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&mediumBJetEta);

//   GenericCollectionMember<double, BNjetCollection> notMediumBJetPt(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetCollectionNotMediumCSV),
//                                                             "pt", "medium_untags_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&notMediumBJetPt);

//   GenericCollectionMember<double, BNjetCollection> notMediumBJetEta(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetCollectionNotMediumCSV),
//                                                              "eta", "medium_untags_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&notMediumBJetEta);

//   ////////// met //////////
//   GenericCollectionMember<double, BNmetCollection> metPt(Reflex::Type::ByName("BNmet"),  &(selectedCollections.metCollection),
//                                                          "pt", "met",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&metPt);

// //   ////////// mc particles ////////
// // //   GenericCollectionMember<double, BNmcparticleCollection> allMcParticlePt(Reflex::Type::ByName("BNmcparticle"), &(selectedCollections.mcParticleCollection),
// // //                                                                   "pt", "mcParticles_by_pt",  KinematicVariableConstants::FLOAT_INIT, 20);
// // //   kinVars.push_back(&allMcParticlePt);

// //   GenericCollectionMember<int, BNmcparticleCollection> allMcParticleId(Reflex::Type::ByName("BNmcparticle"), &(selectedCollections.mcParticleCollection),
// //                                                                   "id", "mcParticles_by_pt",  KinematicVariableConstants::INT_INIT, 10);
// //   kinVars.push_back(&allMcParticleId);

  int numExtraPartons = -99;
  summaryTree->Branch("numExtraPartons", &numExtraPartons);

//   ////////// event info //////////
//   GenericCollectionMember<unsigned, BNeventCollection> runNumber(Reflex::Type::ByName("BNevent"), &(selectedCollections.eventCollection),
//                                                                  "run", "eventInfo",  KinematicVariableConstants::UINT_INIT, 1);
//   kinVars.push_back(&runNumber);

//   GenericCollectionMember<unsigned, BNeventCollection> lumiBlock(Reflex::Type::ByName("BNevent"), &(selectedCollections.eventCollection),
//                                                                  "lumi", "eventInfo",  KinematicVariableConstants::UINT_INIT, 1);
//   kinVars.push_back(&lumiBlock);

//   // this is a long inside BNevent
//   // just using keyword long won't work
//   // needs to be Long64_t 
//   GenericCollectionMember<Long64_t, BNeventCollection> eventNumber(Reflex::Type::ByName("BNevent"),  &(selectedCollections.eventCollection),
//                                                                    "evt", "eventInfo",  KinematicVariableConstants::INT_INIT, 1);
//   kinVars.push_back(&eventNumber);

//   MetLD myMetLD(&myMHT, &metPt);
//   kinVars.push_back(&myMetLD);

//   FinalBDT myFinalBDT(&allLeptonEta, &allLeptonPt, &myMHT, &myMinDeltaRLep2Jet, &myMtMetLep, &mySumPt);
//   kinVars.push_back(&myFinalBDT);

  if (debug > 9) { cout << "Hooking variables to tree" << endl;}
  for (vector<ArbitraryVariable*>::iterator iVar = kinVars.begin();
       iVar != kinVars.end();
       iVar++) {

    (*iVar)->attachToTree (summaryTree);
  }

  int numEvents = 0;
  int numEventsFailCuts = 0;
  int numEventsPassCuts = 0;
  int printEvery = 10000;

  for (ev.toBegin(); !ev.atEnd(); ++ev){
    numEvents++;

    if ((numEvents > myConfig.maxEvents) && myConfig.maxEvents != -1) break;

    if (numEvents == 1 || numEvents % printEvery == 0 )
      cout << "Processing event.... " << numEvents << endl;

    if (debug > 9) cout << "---------->>>>>> Event " << numEvents << endl;

    lepHelper.initializeInputCollections(ev, true, selectedCollections);

//     bool applySmearing = !(lepHelper.isData);
    bool applySmearing = false;
    lepHelper.fillSIP(*(lepHelper.rawCollections.rawMuonCollection), applySmearing);
    lepHelper.fillSIP(*(lepHelper.rawCollections.rawElectronCollection), applySmearing);
    lepHelper.fillLepJetPtRatio(*(lepHelper.rawCollections.rawMuonCollection), *(lepHelper.rawCollections.jetsForLepMVACollection), applySmearing);
    lepHelper.fillLepJetPtRatio(*(lepHelper.rawCollections.rawElectronCollection), *(lepHelper.rawCollections.jetsForLepMVACollection), applySmearing);
    lepHelper.fillLepJetDeltaR(*(lepHelper.rawCollections.rawMuonCollection), *(lepHelper.rawCollections.jetsForLepMVACollection), applySmearing);
    lepHelper.fillLepJetDeltaR(*(lepHelper.rawCollections.rawElectronCollection), *(lepHelper.rawCollections.jetsForLepMVACollection), applySmearing);
    lepHelper.fillLepJetBTagCSV(*(lepHelper.rawCollections.rawMuonCollection), *(lepHelper.rawCollections.jetsForLepMVACollection));
    lepHelper.fillLepJetBTagCSV(*(lepHelper.rawCollections.rawElectronCollection), *(lepHelper.rawCollections.jetsForLepMVACollection));
    if (!lepHelper.isData) {
      lepHelper.fillMCMatchAny(*(lepHelper.rawCollections.rawMuonCollection), 0.3);
      lepHelper.fillMCMatchAny(*(lepHelper.rawCollections.rawElectronCollection), 0.3);
      lepHelper.fillMCMatchID(*(lepHelper.rawCollections.rawMuonCollection), 1.2);
      lepHelper.fillMCMatchID(*(lepHelper.rawCollections.rawElectronCollection), 1.2);

//       lepHelper.scaleMCCollectionDZ(*(lepHelper.rawCollections.rawElectronCollection));
//       lepHelper.scaleMCCollectionDZ(*(lepHelper.rawCollections.rawMuonCollection));
//       lepHelper.scaleMCCollectionDXY(*(lepHelper.rawCollections.rawElectronCollection));
//       lepHelper.scaleMCCollectionDXY(*(lepHelper.rawCollections.rawMuonCollection));
    }

    /////////////////////////////////////////////////////////////
    //
    //    Apply object ids
    //
    //////////////////////////////////////////////////////////////

    //------------  Electrons
    if (debug > 9) cout << "Getting electrons "  << endl;
    lepHelper.getTightLoosePreselectedElectrons(electronTightID, electronLooseID, electronPreselectedID, &selectedCollections);

    //-----------    Muons
    if (debug > 9) cout << "Getting muons "  << endl;
    lepHelper.getTightLoosePreselectedMuons(muonTightID, muonLooseID, muonPreselectedID, &selectedCollections);

    //----------    MET
    if (debug > 9) cout << "Getting met "  << endl;
    lepHelper.getCorrectedMet(&selectedCollections);

    //--------- fill up the lepton collections
    if (debug >9) cout << "Filling lepton collections" << endl;
    lepHelper.fillLepCollectionWithSelectedLeptons(&selectedCollections);
    lepHelper.fillZLepCollectionWithSelectedLeptons(&selectedCollections, &myZLikeMassLepLepSFOSTight,
                                                    &myZLikeMassLepLepSFOSTightLoose, &myZLikeMassLepLepSFOSAll);

    //------------    Jets
    *(lepHelper.rawCollections.jetCollection) = beanHelper->GetCleanJets(*(lepHelper.rawCollections.jetCollection), *(selectedCollections.tightLoosePreselectedLeptonCollection), 0.5);

    if (debug > 9) cout << "Getting jets "  << endl;
	lepHelper.getTightCorrectedJets(25.0, 2.4, jetID::jetLoose, &selectedCollections);

    // reset all the vars
    if (debug > 9) cout << "Resetting "  << endl;
    for (vector<ArbitraryVariable*>::iterator iVar = kinVars.begin();
         iVar != kinVars.end();
         iVar++) {

      (*iVar)->reset();
      (*iVar)->assignCollections(&selectedCollections);
    }

    bool passAllCuts = true;

    if (debug > 9) cout << "Checking cuts "  << endl;

    for (vector<ArbitraryVariable*>::iterator iCut = cutVars.begin();
         iCut != cutVars.end();
         iCut++ ) {

      (*iCut)->evaluate();
      passAllCuts = passAllCuts && (*iCut)->passCut();

    }

    // do the lepton cut
    passAllCuts = passAllCuts &&  LeptonCutThisAnalysis(&selectedCollections);

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

//     LeptonVarsThisAnalysis(&selectedCollections, LeptonCutThisAnalysis(&selectedCollections), TwoMuon, TwoElectron, MuonElectron);

    getNumExtraPartons(beanHelper, selectedCollections, numExtraPartons);
    if (myConfig.sampleName.find("_0p") != std::string::npos) { //0 parton samples
    //Cut to require 0 partons
      if (numExtraPartons != 0) {
        numEventsFailCuts++;
        numEventsPassCuts--;
        continue;
      }
    }
      
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
