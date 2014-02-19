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
  numAllLeptons.setCutMin(3);
  cutVars.push_back(&numAllLeptons);

  GenericCollectionSizeVariable<BNmuonCollection> numAllMuons(&(selectedCollections.tightLoosePreselectedMuonCollection), "numAllMuons");
  kinVars.push_back(&numAllMuons);

  GenericCollectionSizeVariable<BNelectronCollection> numAllElectrons(&(selectedCollections.tightLoosePreselectedElectronCollection), "numAllElectrons");
  kinVars.push_back(&numAllElectrons);

  GenericCollectionSizeVariable<BNleptonCollection> numTightZLeptons(&(selectedCollections.tightZLeptonCollection), "numTightZLeptons");
  kinVars.push_back(&numTightZLeptons);

  GenericCollectionSizeVariable<BNleptonCollection> numTightLooseZLeptons(&(selectedCollections.tightLooseZLeptonCollection), "numTightLooseZLeptons");
  kinVars.push_back(&numTightLooseZLeptons);

  GenericCollectionSizeVariable<BNleptonCollection> numAllZLeptons(&(selectedCollections.tightLoosePreselectedZLeptonCollection), "numAllZLeptons");
  kinVars.push_back(&numAllZLeptons);

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

  LeptonTriggerScaleFactors myLepTrig(&lepHelper);
  kinVars.push_back(&myLepTrig);

  TightChargeAndLepMVAScaleFactors myTightChargeAndLepMVASFs(2);
  kinVars.push_back(&myTightChargeAndLepMVASFs);

  CleanEventVars myClean (&lepHelper);
  kinVars.push_back(&myClean);

  CheckTwoLepTrigger checkTrig (&lepHelper);
  kinVars.push_back(&checkTrig);

  LepMVAs<BNleptonCollection> myLepMVAsAllLeptons(&lepHelper, &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 4);
  kinVars.push_back(&myLepMVAsAllLeptons);

  LepMVAs<BNleptonCollection> myLepMVAsAllZLeptons(&lepHelper, &(selectedCollections.tightLoosePreselectedZLeptonCollection), "allZ_leptons_by_pt", 2);
  kinVars.push_back(&myLepMVAsAllZLeptons);

  LepMVAs<BNleptonCollection> myLepMVAsAllNonZLeptons(&lepHelper, &(selectedCollections.tightLoosePreselectedNonZLeptonCollection), "allNonZ_leptons_by_pt", 2);
  kinVars.push_back(&myLepMVAsAllNonZLeptons);

  DataDrivenFR<BNleptonCollection> myDataDrivenFR3Tight(&lepHelper, &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                        3, 0.7, "FR_merged_data", "QF_data_el", "_3Tight");
  kinVars.push_back(&myDataDrivenFR3Tight);
  
  DataDrivenFR<BNleptonCollection> myDataDrivenFR3Loose(&lepHelper, &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                        3, -0.3, "FR_merged_data", "QF_data_el", "_3Loose");
  kinVars.push_back(&myDataDrivenFR3Loose);
  
  DataDrivenFR<BNleptonCollection> myDataDrivenFR4Loose(&lepHelper, &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                        4, -0.3, "FR_merged_data", "QF_data_el", "_4Loose");
  kinVars.push_back(&myDataDrivenFR4Loose);
  
  DataDrivenFR<BNleptonCollection> myDataDrivenFR2LooseZ(&lepHelper, &(selectedCollections.tightLoosePreselectedZLeptonCollection),
                                                         2, -0.3, "FR_merged_data", "QF_data_el", "_2LooseZ");
  kinVars.push_back(&myDataDrivenFR2LooseZ);
  
  DataDrivenFR<BNleptonCollection> myDataDrivenFR1TightNonZ(&lepHelper, &(selectedCollections.tightLoosePreselectedNonZLeptonCollection),
                                                            1, 0.7, "FR_merged_data", "QF_data_el", "_1TightNonZ");
  kinVars.push_back(&myDataDrivenFR1TightNonZ);
  
  DBCorrectedRelIsoDR04s myDBCorrectedRelIsoDR04s(&lepHelper, 4);
  kinVars.push_back(&myDBCorrectedRelIsoDR04s);

  HiggsDecayType myHiggsDecayType(&lepHelper);
  kinVars.push_back(&myHiggsDecayType);

  // Full event kinematics

  TwoObjectKinematic<BNleptonCollection,BNmetCollection> mySumLep1Lep2MetPt("pt", "sum", "sum_lep1pt_lep2pt_met",
                                                                            &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 2,
                                                                            &(selectedCollections.metCollection), "met", 1, 1);
  kinVars.push_back(&mySumLep1Lep2MetPt);

  TwoObjectKinematic<BNjetCollection,BNjetCollection> myWLikeDijetMass81("mass", "closest_to", "WLike_dijet_mass",
                                                                         &(selectedCollections.jetCollectionNotMediumCSV), "medium_untags_by_pt", 1, 99,
                                                                         &(selectedCollections.jetCollectionNotMediumCSV), "medium_untags_by_pt", 1, 99,
                                                                         81);
  kinVars.push_back(&myWLikeDijetMass81);

  TwoObjectKinematic<BNjetCollection,BNjetCollection> mySumJetPt("pt", "sum", "sum_jet_pt",
                                                                 &(selectedCollections.jetCollection), "jets_by_pt", 1, 99,
                                                                 &(selectedCollections.jetCollection), "jets_by_pt", 1, 99);
  kinVars.push_back(&mySumJetPt);

  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMinDeltaRLepLep("deltaR", "min", "min_deltaR_leplep",
                                                                                    &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99,
                                                                                    &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99);
  kinVars.push_back(&myMinDeltaRLepLep);
  
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMaxDeltaEtaLepLep("deltaEta", "maxAbs", "maxAbs_deltaEta_leplep",
                                                                                    &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99,
                                                                                    &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99);
  kinVars.push_back(&myMaxDeltaEtaLepLep);
  
  TwoObjectKinematic<BNleptonCollection,BNjetCollection> myMinDeltaRLepJet("deltaR", "min", "min_deltaR_lepjet",
                                                                               &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99,
                                                                               &(selectedCollections.jetCollection), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMinDeltaRLepJet);
  
  TwoObjectKinematic<BNjetCollection,BNjetCollection> myMinDeltaRJetJet("deltaR", "min", "min_deltaR_jetjet",
                                                                        &(selectedCollections.jetCollection), "jets_by_pt", 1, 99,
                                                                        &(selectedCollections.jetCollection), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMinDeltaRJetJet);
  
  TwoObjectKinematic<BNjetCollection,BNjetCollection> myMaxDeltaEtaJetJet("deltaEta", "maxAbs", "maxAbs_deltaEta_jetjet",
                                                                          &(selectedCollections.jetCollection), "jets_by_pt", 1, 99,
                                                                          &(selectedCollections.jetCollection), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMaxDeltaEtaJetJet);
  
  
  // Two lepton kinematics
  
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMinMassLepLepSFOS("mass", "min", "min_mass_leplep_SFOS",
                                                                                &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99,
                                                                                &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99,
                                                                                -99, "same_flavour", "opposite_sign");
  kinVars.push_back(&myMinMassLepLepSFOS);
  
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMinMassLepLep("mass", "min", "min_mass_leplep",
                                                                            &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99,
                                                                            &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99);
  kinVars.push_back(&myMinMassLepLep);
  
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZLikeMassLepLepSFOSTight("mass", "closest_to", "ZLike_mass_leplep_SFOS_tight",
                                                                                     &(selectedCollections.tightLeptonCollection), "tight_leptons_by_pt", 1, 99,
                                                                                     &(selectedCollections.tightLeptonCollection), "tight_leptons_by_pt", 1, 99,
                                                                                     91.2, "same_flavour", "opposite_sign");
  kinVars.push_back(&myZLikeMassLepLepSFOSTight);  

  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZLikeMassLepLepSFOSTightLoose("mass", "closest_to", "ZLike_mass_leplep_SFOS_loose",
                                                                                     &(selectedCollections.tightLooseLeptonCollection), "tightLoose_leptons_by_pt", 1, 99,
                                                                                     &(selectedCollections.tightLooseLeptonCollection), "tightLoose_leptons_by_pt", 1, 99,
                                                                                     91.2, "same_flavour", "opposite_sign");
  kinVars.push_back(&myZLikeMassLepLepSFOSTightLoose);  

  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZLikeMassLepLepSFOS("mass", "closest_to", "ZLike_mass_leplep_SFOS",
                                                                                     &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99,
                                                                                     &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99,
                                                                                     91.2, "same_flavour", "opposite_sign");
  kinVars.push_back(&myZLikeMassLepLepSFOS);  

  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZLikePtLepLepSFOS("vectPt", "max", "ZLike_pt_leplep_SFOS",
                                                                                &(selectedCollections.tightLoosePreselectedZLeptonCollection), "allZ_leptons_by_pt", 1, 99,
                                                                                &(selectedCollections.tightLoosePreselectedZLeptonCollection), "allZ_leptons_by_pt", 1, 99);
  kinVars.push_back(&myZLikePtLepLepSFOS);

  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZLikeEtaLepLepSFOSAll("vectEta", "max", "ZLike_eta_leplep_SFOS_all",
                                                                                &(selectedCollections.tightLoosePreselectedZLeptonCollection), "allZ_leptons_by_pt", 1, 99,
                                                                                &(selectedCollections.tightLoosePreselectedZLeptonCollection), "allZ_leptons_by_pt", 1, 99);
  kinVars.push_back(&myZLikeEtaLepLepSFOSAll);

  
//   //Variables for CERN same-sign dilepton BDT
  TwoObjectKinematic<BNleptonCollection,BNjetCollection> myMHT("pt", "vector_sum", "mht",
                                                               &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99,
                                                               &(selectedCollections.jetCollection), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMHT);
  
//   TwoObjectKinematic<BNleptonCollection,BNjetCollection> myMinDeltaRLep2Jet("deltaR", "min", "min_deltaR_lep2_jet",
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

  /////////////////////////////////
  //// Leptons
  /////////////////////////////////

  // pT
  
  GenericCollectionMember<double, BNleptonCollection> LeptonPt(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                                  "pt", "leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&LeptonPt);

  GenericCollectionMember<double, BNleptonCollection> ZLeptonPt(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedZLeptonCollection),
                                                                  "pt", "Z_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&ZLeptonPt);

  GenericCollectionMember<double, BNleptonCollection> NonZLeptonPt(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedNonZLeptonCollection),
                                                                  "pt", "NonZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&NonZLeptonPt);

  // eta
  
  GenericCollectionMember<double, BNleptonCollection> LeptonEta(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                                  "eta", "leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&LeptonEta);

  GenericCollectionMember<double, BNleptonCollection> ZLeptonEta(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedZLeptonCollection),
                                                                  "eta", "Z_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&ZLeptonEta);

  GenericCollectionMember<double, BNleptonCollection> NonZLeptonEta(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedNonZLeptonCollection),
                                                                  "eta", "NonZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&NonZLeptonEta);

  // isMuon / isElectron
  
  GenericCollectionMember<int, BNleptonCollection> NonZLeptonIsMuon(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedNonZLeptonCollection),
                                                                       "isMuon", "NonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&NonZLeptonIsMuon);

  GenericCollectionMember<int, BNleptonCollection> NonZLeptonIsElectron(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedNonZLeptonCollection),
                                                                       "isElectron", "NonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&NonZLeptonIsElectron);

  // tkCharge
  
  GenericCollectionMember<int, BNleptonCollection> LeptonTkCharge(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                                  "tkCharge", "leptons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&LeptonTkCharge);

  GenericCollectionMember<int, BNleptonCollection> NonZLeptonTkCharge(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedNonZLeptonCollection),
                                                                  "tkCharge", "NonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&NonZLeptonTkCharge);

//   if (myConfig.sampleName.find("QF_sideband") == std::string::npos) { //All samples except QF_sideband
//     //Cut to require same-sign leptons
//     auto tkChargeCut = [] (vector<BranchInfo<int>> vars) { return ((vars[0].branchVal * vars[1].branchVal) > 0); };
//     allLeptonTkCharge.setCut(tkChargeCut);
//   }
//   else if (myConfig.sampleName.find("QF_sideband") != std::string::npos) { //QF_sideband samples
//     //Cut to require opposite-sign leptons
//     auto tkChargeCut = [] (vector<BranchInfo<int>> vars) { return ((vars[0].branchVal * vars[1].branchVal) < 0); };
//     allLeptonTkCharge.setCut(tkChargeCut);
//   }
//   cutVars.push_back(&allLeptonTkCharge);

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

  /////////////////////////////////
  //// Jets
  /////////////////////////////////


  ////////// all jets //////////
  GenericCollectionMember<double, BNjetCollection> allJetPt(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetCollection),
                                                            "pt", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetPt);

//   GenericCollectionMember<double, BNjetCollection> allJetEta(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetCollection),
//                                                              "eta", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
//   kinVars.push_back(&allJetEta);

  GenericCollectionMember<double, BNjetCollection> allJetCSV(Reflex::Type::ByName("BNjet"),  &(selectedCollections.jetCollection),
                                                             "btagCombinedSecVertex", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetCSV);

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

  ////////// met //////////
  GenericCollectionMember<double, BNmetCollection> metPt(Reflex::Type::ByName("BNmet"),  &(selectedCollections.metCollection),
                                                         "pt", "met",  KinematicVariableConstants::FLOAT_INIT, 1);
  kinVars.push_back(&metPt);

//   ////////// mc particles ////////
// //   GenericCollectionMember<double, BNmcparticleCollection> allMcParticlePt(Reflex::Type::ByName("BNmcparticle"), &(selectedCollections.mcParticleCollection),
// //                                                                   "pt", "mcParticles_by_pt",  KinematicVariableConstants::FLOAT_INIT, 20);
// //   kinVars.push_back(&allMcParticlePt);

//   GenericCollectionMember<int, BNmcparticleCollection> allMcParticleId(Reflex::Type::ByName("BNmcparticle"), &(selectedCollections.mcParticleCollection),
//                                                                   "id", "mcParticles_by_pt",  KinematicVariableConstants::INT_INIT, 10);
//   kinVars.push_back(&allMcParticleId);

  int numExtraPartons = -99;
  summaryTree->Branch("numExtraPartons", &numExtraPartons);

  ////////// event info //////////
  GenericCollectionMember<unsigned, BNeventCollection> runNumber(Reflex::Type::ByName("BNevent"), &(selectedCollections.eventCollection),
                                                                 "run", "eventInfo",  KinematicVariableConstants::UINT_INIT, 1);
  kinVars.push_back(&runNumber);

  GenericCollectionMember<unsigned, BNeventCollection> lumiBlock(Reflex::Type::ByName("BNevent"), &(selectedCollections.eventCollection),
                                                                 "lumi", "eventInfo",  KinematicVariableConstants::UINT_INIT, 1);
  kinVars.push_back(&lumiBlock);

  // this is a long inside BNevent
  // just using keyword long won't work
  // needs to be Long64_t 
  GenericCollectionMember<Long64_t, BNeventCollection> eventNumber(Reflex::Type::ByName("BNevent"),  &(selectedCollections.eventCollection),
                                                                   "evt", "eventInfo",  KinematicVariableConstants::INT_INIT, 1);
  kinVars.push_back(&eventNumber);

  MetLD myMetLD(&myMHT, &metPt);
  kinVars.push_back(&myMetLD);

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
  int printEvery = 1000;

  for (ev.toBegin(); !ev.atEnd(); ++ev){
    numEvents++;

    if ((numEvents > myConfig.maxEvents) && myConfig.maxEvents != -1) break;

    if (numEvents == 1 || numEvents % printEvery == 0 )
      cout << "Processing event.... " << numEvents << endl;

    if (debug > 9) cout << "---------->>>>>> Event " << numEvents << endl;

    lepHelper.initializeInputCollections(ev, true, selectedCollections);
    lepHelper.applyRochesterCorrections(*(lepHelper.rawCollections.rawMuonCollection));

    if (!lepHelper.isData) {
      lepHelper.fillMCMatchAny(*(lepHelper.rawCollections.rawMuonCollection), 0.3);
      lepHelper.fillMCMatchAny(*(lepHelper.rawCollections.rawElectronCollection), 0.3);
      lepHelper.fillMCMatchID(*(lepHelper.rawCollections.rawMuonCollection), 1.2);
      lepHelper.fillMCMatchID(*(lepHelper.rawCollections.rawElectronCollection), 1.2);

      lepHelper.scaleMCCollectionDZ(*(lepHelper.rawCollections.rawElectronCollection));
      lepHelper.scaleMCCollectionDZ(*(lepHelper.rawCollections.rawMuonCollection));
      lepHelper.scaleMCCollectionDXY(*(lepHelper.rawCollections.rawElectronCollection));
      lepHelper.scaleMCCollectionDXY(*(lepHelper.rawCollections.rawMuonCollection));
    }
    bool applySmearing = !(lepHelper.isData);
    lepHelper.fillSIP(*(lepHelper.rawCollections.rawMuonCollection), applySmearing);
    lepHelper.fillSIP(*(lepHelper.rawCollections.rawElectronCollection), applySmearing);
    lepHelper.fillLepJetPtRatio(*(lepHelper.rawCollections.rawMuonCollection), *(lepHelper.rawCollections.jetsForLepMVACollection), applySmearing);
    lepHelper.fillLepJetPtRatio(*(lepHelper.rawCollections.rawElectronCollection), *(lepHelper.rawCollections.jetsForLepMVACollection), applySmearing);
    lepHelper.fillLepJetDeltaR(*(lepHelper.rawCollections.rawMuonCollection), *(lepHelper.rawCollections.jetsForLepMVACollection), applySmearing);
    lepHelper.fillLepJetDeltaR(*(lepHelper.rawCollections.rawElectronCollection), *(lepHelper.rawCollections.jetsForLepMVACollection), applySmearing);
    lepHelper.fillLepJetBTagCSV(*(lepHelper.rawCollections.rawMuonCollection), *(lepHelper.rawCollections.jetsForLepMVACollection));
    lepHelper.fillLepJetBTagCSV(*(lepHelper.rawCollections.rawElectronCollection), *(lepHelper.rawCollections.jetsForLepMVACollection));

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
                                                    &myZLikeMassLepLepSFOSTightLoose, &myZLikeMassLepLepSFOS);

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
    passAllCuts = passAllCuts;

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
