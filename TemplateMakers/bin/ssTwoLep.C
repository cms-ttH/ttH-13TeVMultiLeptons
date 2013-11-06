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
  //Collection definitions set by muonID::muonID and electronID::electronID inside main function
  unsigned numTightMuons = inputCollections->tightMuonCollection->size();
  unsigned numLooseMuons = inputCollections->looseMuonCollection->size();
  unsigned numTightElectrons = inputCollections->tightElectronCollection->size();
  unsigned numLooseElectrons = inputCollections->looseElectronCollection->size();
  unsigned numAllLeptons = inputCollections->tightLoosePreselectedLeptonCollection->size();

  bool passTwoLepton = false;

  //  if (numTightMuons ==2 || numTightElectrons==2 || (numTightMuons==1 && numTightElectrons==1))
  if (numAllLeptons >= 2)
      passTwoLepton = true;

  return passTwoLepton;
}

void LeptonVarsThisAnalysis(BEANFileInterface * inputCollections, bool passTwoLepton, int & TwoMuon, int & TwoElectron, int & MuonElectron) {
  //Collection definitions set by muonID::muonID and electronID::electronID inside main function
  unsigned numTightMuons = inputCollections->tightMuonCollection->size();
  unsigned numLooseMuons = inputCollections->looseMuonCollection->size();
  unsigned numTightElectrons = inputCollections->tightElectronCollection->size();
  unsigned numLooseElectrons = inputCollections->looseElectronCollection->size();

  TwoMuon = 0;
  TwoElectron = 0;
  MuonElectron = 0;

  if (!passTwoLepton){
    return;
  }

  if (numTightMuons == 2 ) {
    TwoMuon = 1;
    return;
  }

  if (numTightElectrons == 2 ) {
    TwoElectron = 1;
    return;
  }

  if ( numTightElectrons ==1 && numTightMuons==1 ) {
    MuonElectron = 1;
    return;
  }
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
  cutVars.push_back(&numJets);

  GenericCollectionSizeVariable<BNjetCollection> numLooseBJets(&(selectedCollections.jetCollectionLooseCSV), "numLooseBJets");
  kinVars.push_back(&numLooseBJets);

  GenericCollectionSizeVariable<BNjetCollection> numMediumBJets(&(selectedCollections.jetCollectionMediumCSV), "numMediumBJets");
  kinVars.push_back(&numMediumBJets);

  GenericCollectionSizeVariable<BNleptonCollection> numAllLeptons(&(selectedCollections.tightLoosePreselectedLeptonCollection), "numAllLeptons");
  kinVars.push_back(&numAllLeptons);

  GenericCollectionSizeVariable<BNmuonCollection> numTightMuons(&(selectedCollections.tightMuonCollection), "numTightMuons");
  kinVars.push_back(&numTightMuons);

  GenericCollectionSizeVariable<BNelectronCollection> numTightElectrons(&(selectedCollections.tightElectronCollection), "numTightElectrons");
  kinVars.push_back(&numTightElectrons);

  GenericCollectionSizeVariable<BNleptonCollection> numTightLeptons(&(selectedCollections.tightLeptonCollection), "numTightLeptons");
  kinVars.push_back(&numTightLeptons);
  if (myConfig.sampleName.find("NP_sideband") == std::string::npos) { //All samples except NP_sideband
    std::cout << "Sample is not a sideband" << std::endl;
    numTightLeptons.setCutMin(2);
  }
  else if (myConfig.sampleName.find("NP_sideband") != std::string::npos) { //NP_sideband samples
    std::cout << "Sample is a sideband" << std::endl;
    //Cut to require opposite-sign leptons
    numTightLeptons.setCutMax(1);
  }
  cutVars.push_back(&numTightLeptons);

  CSVWeights myCSV(&lepHelper);
  kinVars.push_back(&myCSV);

  //Btag POG version
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

  LepMVAs<BNleptonCollection> myLepMVAsTightLeptons(&lepHelper, &(selectedCollections.tightLeptonCollection), "tight_leptons_by_pt", 2);
  kinVars.push_back(&myLepMVAsTightLeptons);

  LepMVAs<BNleptonCollection> myLepMVAsLooseLeptons(&lepHelper, &(selectedCollections.looseLeptonCollection), "loose_leptons_by_pt", 2);
  kinVars.push_back(&myLepMVAsLooseLeptons);

  LepMVAs<BNleptonCollection> myLepMVAsPreselectedLeptons(&lepHelper, &(selectedCollections.preselectedLeptonCollection), "preselected_leptons_by_pt", 2);
  kinVars.push_back(&myLepMVAsPreselectedLeptons);

  LepMVAs<BNleptonCollection> myLepMVAsAllLeptons(&lepHelper, &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 3);
  kinVars.push_back(&myLepMVAsAllLeptons);

  LepMVAs<BNmuonCollection> myLepMVAsAllMuons(&lepHelper, &(selectedCollections.tightLoosePreselectedMuonCollection), "all_muons_by_pt", 3);
  kinVars.push_back(&myLepMVAsAllMuons);

  DataDrivenFR<BNleptonCollection> myDataDrivenFRAllLeptons(&lepHelper, &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                             2, 0.7, "FR_merged_data", "QF_data_el");
  kinVars.push_back(&myDataDrivenFRAllLeptons);

  DBCorrectedRelIsoDR04s myDBCorrectedRelIsoDR04s(&lepHelper, 4);
  kinVars.push_back(&myDBCorrectedRelIsoDR04s);

  HiggsDecayType myHiggsDecayType(&lepHelper);
  kinVars.push_back(&myHiggsDecayType);

  TwoObjectKinematic<BNmuonCollection,BNjetCollection> myMassMuonJetNew("mass", "all_pairs", -99, "",
                                                                        &(selectedCollections.tightMuonCollection), "tight_muons_by_pt", 1, 2,
                                                                        &(selectedCollections.jetCollection), "jets_by_pt", 1, 4);
  kinVars.push_back(&myMassMuonJetNew);

  TwoObjectKinematic<BNleptonCollection,BNmetCollection> mySumLep1Lep2MetPt("pt", "sum", -99, "sum_lep1pt_lep2pt_met",
                                                                            &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 2,
                                                                            &(selectedCollections.metCollection), "met", 1, 1);
  kinVars.push_back(&mySumLep1Lep2MetPt);

  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMinMassLepLep("mass", "min", -99, "min_mass_leplep",
                                                                            &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99,
                                                                            &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99);
  kinVars.push_back(&myMinMassLepLep);

  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMinDeltaRLepLep("deltaR", "min", -99, "min_dR_leplep",
                                                                              &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99,
                                                                              &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99);
  kinVars.push_back(&myMinDeltaRLepLep);

  TwoObjectKinematic<BNmuonCollection,BNjetCollection> myMassMuonJet100("mass", "closest_to", 100, "muon_jet_mass_closest_to_100",
                                                                        &(selectedCollections.tightMuonCollection), "tight_muons_by_pt", 1, 2,
                                                                        &(selectedCollections.jetCollection), "jets_by_pt", 1, 4);
  kinVars.push_back(&myMassMuonJet100);

  TwoObjectKinematic<BNjetCollection,BNjetCollection> myHiggsLikeDijetMass110("mass", "closest_to", 110, "higgsLike_dijet_mass",
                                                                              &(selectedCollections.jetCollectionMediumCSV), "medium_btags_by_pt", 1, 99,
                                                                              &(selectedCollections.jetCollectionMediumCSV), "medium_btags_by_pt", 1, 99);
  kinVars.push_back(&myHiggsLikeDijetMass110);

  //Variables for CERN same-sign dilepton BDT
  TwoObjectKinematic<BNleptonCollection,BNjetCollection> myMHT("pt", "vector_sum", -99, "mht",
                                                               &(selectedCollections.tightLeptonCollection), "tight_leptons_by_pt", 1, 99,
                                                               &(selectedCollections.jetCollection), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMHT);

  TwoObjectKinematic<BNleptonCollection,BNjetCollection> myMinDeltaRLep2Jet("deltaR", "min", -99, "mindr_lep2_jet",
                                                                            &(selectedCollections.tightLeptonCollection), "tight_leptons_by_pt", 2, 2,
                                                                            &(selectedCollections.jetCollection), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMinDeltaRLep2Jet);

  TwoObjectKinematic<BNmetCollection,BNleptonCollection> myMtMetLep("MT", "all_pairs", -99, "",
                                                                    &(selectedCollections.metCollection), "met", 1, 1,
                                                                    &(selectedCollections.tightLeptonCollection), "tight_leptons_by_pt", 1, 2);
  kinVars.push_back(&myMtMetLep);

  TwoObjectKinematic<BNleptonCollection,BNjetCollection> mySumPt("pt", "sum", -99, "sum_pt",
                                                                 &(selectedCollections.tightLeptonCollection), "tight_leptons_by_pt", 1, 99,
                                                                 &(selectedCollections.jetCollection), "jets_by_pt", 1, 99);
  kinVars.push_back(&mySumPt);

  // AWB Oct 17 - end new object functions
  TightCharges myTightCharges(&(selectedCollections.tightLoosePreselectedLeptonCollection), "CERN_tight_charge", "all_leptons_by_pt", 2);
  kinVars.push_back(&myTightCharges);
  myTightCharges.setCut("pass");

  int TwoMuon = 0;
  int TwoElectron = 0;
  int MuonElectron = 0;

  summaryTree->Branch("TwoMuon", &TwoMuon);
  summaryTree->Branch("TwoElectron", &TwoElectron);
  summaryTree->Branch("MuonElectron", &MuonElectron);

  ////////// all leptons //////////
  GenericCollectionMember<double, BNleptonCollection> allLeptonPt(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                                  "pt", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonPt);

  GenericCollectionMember<double, BNleptonCollection> allLeptonTkPT(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                                    "tkPT", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonTkPT);

  GenericCollectionMember<double, BNleptonCollection> allLeptonEta(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                                   "eta", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonEta);

  GenericCollectionMember<int, BNleptonCollection> allLeptonIsMuon(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                                   "isMuon", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonIsMuon);

  GenericCollectionMember<int, BNleptonCollection> allLeptonIsElectron(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                                       "isElectron", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonIsElectron);

  GenericCollectionMember<int, BNleptonCollection> allLeptonTkCharge(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                                     "tkCharge", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonTkCharge);
  if (myConfig.sampleName.find("QF_sideband") == std::string::npos) { //All samples except QF_sideband
    //Cut to require same-sign leptons
    auto tkChargeCut = [] (vector<BranchInfo<int>> vars) { return ((vars[0].branchVal * vars[1].branchVal) > 0); };
    allLeptonTkCharge.setCut(tkChargeCut);
  }
  else if (myConfig.sampleName.find("QF_sideband") != std::string::npos) { //QF_sideband samples
    //Cut to require opposite-sign leptons
    auto tkChargeCut = [] (vector<BranchInfo<int>> vars) { return ((vars[0].branchVal * vars[1].branchVal) < 0); };
    allLeptonTkCharge.setCut(tkChargeCut);
  }
  cutVars.push_back(&allLeptonTkCharge);

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

  GenericCollectionMember<double, BNleptonCollection> allLeptonPhi(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                                   "phi", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonPhi);

  GenericCollectionMember<int, BNleptonCollection> allLeptonGlobalMuon(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                                       "isGlobalMuon", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonGlobalMuon);

  ////////// all muons //////////
  GenericCollectionMember<int, BNmuonCollection> allMuonPFmuon(Reflex::Type::ByName("BNmuon"), &(selectedCollections.tightLoosePreselectedMuonCollection),
                                                               "isPFMuon", "all_muons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allMuonPFmuon);

  GenericCollectionMember<int, BNmuonCollection> allMuonGlobalMuon(Reflex::Type::ByName("BNmuon"), &(selectedCollections.tightLoosePreselectedMuonCollection),
                                                                   "isGlobalMuon", "all_muons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allMuonGlobalMuon);

  GenericCollectionMember<int, BNmuonCollection> allMuonTrackerMuon(Reflex::Type::ByName("BNmuon"), &(selectedCollections.tightLoosePreselectedMuonCollection),
                                                                    "isTrackerMuon", "all_muons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allMuonTrackerMuon);

  GenericCollectionMember<double, BNmuonCollection> allMuonPt(Reflex::Type::ByName("BNmuon"), &(selectedCollections.tightLoosePreselectedMuonCollection),
                                                              "pt", "all_muons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allMuonPt);

  GenericCollectionMember<double, BNmuonCollection> allMuonEta(Reflex::Type::ByName("BNmuon"), &(selectedCollections.tightLoosePreselectedMuonCollection),
                                                               "eta", "all_muons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allMuonEta);

  ////////// all electrons //////////
  GenericCollectionMember<int, BNelectronCollection> allElectronNumExpInnerHits(Reflex::Type::ByName("BNelectron"), &(selectedCollections.tightLoosePreselectedElectronCollection),
                                                                                "numberOfExpectedInnerHits", "all_electrons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allElectronNumExpInnerHits);

  GenericCollectionMember<int, BNelectronCollection> allElectronPassConvVeto(Reflex::Type::ByName("BNelectron"), &(selectedCollections.tightLoosePreselectedElectronCollection),
                                                                             "passConvVeto", "all_electrons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allElectronPassConvVeto);

  GenericCollectionMember<double, BNelectronCollection> allElectronEta(Reflex::Type::ByName("BNelectron"), &(selectedCollections.tightLoosePreselectedElectronCollection),
                                                                       "eta", "all_electrons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allElectronEta);

  GenericCollectionMember<double, BNelectronCollection> allElectronPt(Reflex::Type::ByName("BNelectron"), &(selectedCollections.tightLoosePreselectedElectronCollection),
                                                                      "pt", "all_electrons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allElectronPt);

  ////////// tight leptons /////////
  GenericCollectionMember<double, BNleptonCollection> tightLeptonPt(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLeptonCollection),
                                                                  "pt", "tight_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&tightLeptonPt);

  GenericCollectionMember<double, BNleptonCollection> tightLeptonEta(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLeptonCollection),
                                                                   "eta", "tight_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&tightLeptonEta);

  ////////// all jets //////////
  GenericCollectionMember<double, BNjetCollection> allJetPt(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetCollection),
                                                            "pt", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetPt);

  GenericCollectionMember<double, BNjetCollection> allJetEta(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetCollection),
                                                             "eta", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetEta);

  GenericCollectionMember<double, BNjetCollection> allJetPhi(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetCollection),
                                                             "phi", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetPhi);

  GenericCollectionMember<double, BNjetCollection> allJetCSV(Reflex::Type::ByName("BNjet"),  &(selectedCollections.jetCollection),
                                                             "btagCombinedSecVertex", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetCSV);

  ////////// met //////////
  GenericCollectionMember<double, BNmetCollection> metPt(Reflex::Type::ByName("BNmet"),  &(selectedCollections.metCollection),
                                                         "pt", "met",  KinematicVariableConstants::FLOAT_INIT, 1);
  kinVars.push_back(&metPt);

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

  FinalBDT myFinalBDT(&tightLeptonEta, &tightLeptonPt, &myMHT, &myMinDeltaRLep2Jet, &myMtMetLep, &mySumPt);
  kinVars.push_back(&myFinalBDT);

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

    LeptonVarsThisAnalysis(&selectedCollections, LeptonCutThisAnalysis(&selectedCollections), TwoMuon, TwoElectron, MuonElectron);

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
