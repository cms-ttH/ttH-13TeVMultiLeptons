#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/BEANFileInterface.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/HelperLeptonCore.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/GenericCollection.h"

///-------------- Kinematic Variables ------------------
#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/EveryVariable.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/JobParameters.h"

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

void getNumExtraPartons(BEANhelper * beanHelper, BNmcparticleCollection& mcParticles, int& numExtraPartons) {

  numExtraPartons = beanHelper->GetNumExtraPartons(mcParticles);

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
  myConfig.jetSyst = inputs.getParameter < string > ("jetSyst");

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

  BEANhelper * beanHelper = lepHelper.setupAnalysisParameters("2012_53x", myConfig.sampleName);

  sysType::sysType jetSyst = sysType::NA;
  if (myConfig.jetSyst == "NA") jetSyst = sysType::NA;
  else if (myConfig.jetSyst == "JESUp") jetSyst = sysType::JESup;
  else if (myConfig.jetSyst == "JESDown") jetSyst = sysType::JESdown;
  else std::cout << "No valid JES corrections specified - using nominal" << std::endl;

  muonID::muonID muonTightID = muonID::muonSideTightCut;
  muonID::muonID muonLooseID = muonID::muonSideLooseCut;
  muonID::muonID muonPreselectedID = muonID::muonSide;
  electronID::electronID electronTightID = electronID::electronSideTightCut;
  electronID::electronID electronLooseID = electronID::electronSideLooseCut;
  electronID::electronID electronPreselectedID = electronID::electronSide;

  // collections
  GenericCollection<BNelectronCollection> tightElectrons(beanHelper);
  GenericCollection<BNelectronCollection> looseElectrons(beanHelper);
  GenericCollection<BNelectronCollection> preselectedElectrons(beanHelper);
//   GenericCollection<BNelectronCollection> tightLooseElectrons(beanHelper);
//   GenericCollection<BNelectronCollection> loosePreselectedElectrons(beanHelper);
  GenericCollection<BNelectronCollection> tightLoosePreselectedElectrons(beanHelper);

  GenericCollection<BNmuonCollection> tightMuons(beanHelper);
  GenericCollection<BNmuonCollection> looseMuons(beanHelper);
  GenericCollection<BNmuonCollection> preselectedMuons(beanHelper);
//   GenericCollection<BNmuonCollection> tightLooseMuons(beanHelper);
  GenericCollection<BNmuonCollection> tightLoosePreselectedMuons(beanHelper);

  GenericCollection<BNleptonCollection> tightLeptons(beanHelper);
//   GenericCollection<BNleptonCollection> looseLeptons(beanHelper);
//   GenericCollection<BNleptonCollection> preselectedLeptons(beanHelper);
//   GenericCollection<BNleptonCollection> tightLooseLeptons(beanHelper);
  GenericCollection<BNleptonCollection> tightLoosePreselectedLeptons(beanHelper);

  GenericCollection<BNjetCollection> jets(beanHelper);
  GenericCollection<BNjetCollection> jetsByCSV(beanHelper);
  GenericCollection<BNjetCollection> looseCSVJets(beanHelper);
  GenericCollection<BNjetCollection> mediumCSVJets(beanHelper);
  GenericCollection<BNjetCollection> jetsForLepMVA(beanHelper);

  GenericCollection<BNmetCollection> met(beanHelper);
  GenericCollection<BNprimaryvertexCollection> primaryVertexes(beanHelper);
  GenericCollection<BNtriggerCollection> hltCollection(beanHelper);
  GenericCollection<BNeventCollection> events(beanHelper);
  GenericCollection<BNmcparticleCollection> mcParticles(beanHelper);

  // declare the kinematic variables that you want to be written out into the tree
  vector<ArbitraryVariable*> kinVars;
  vector<ArbitraryVariable*> cutVars;

  ////////////////////////// corrections, weights, etc
  CSVWeights myCSV(beanHelper, &(jets.ptrToItems), jetSyst, "skipSyst");
  kinVars.push_back(&myCSV);

//   //Btag POG version
//   vector<pair<string, double>> WPs = {make_pair("CSVT", 0.898), make_pair("CSVM", 0.679), make_pair("CSVL", 0.244)};
//   BTagWeights myBTagWeights(WPs, &(jets.ptrToItems), "skipSyst");
//   kinVars.push_back(&myBTagWeights);

  PUWeights myPU(&lepHelper, &(events.ptrToItems), "skipSyst");
  kinVars.push_back(&myPU);

  TopPtWeights myTopPt(&lepHelper, &(mcParticles.ptrToItems), "skipSyst");
  kinVars.push_back(&myTopPt);

//   //Currently, gets ND loose lepton SF; could switch to tight and loose - AWB Feb 12, 2014
//   //LeptonIDAndIsoScaleFactors myLepIDAndIsoSF(&lepHelper, muonID::muonTight, muonID::muonLoose, electronID::electronTight, electronID::electronLoose);
//   LeptonIDAndIsoScaleFactors myLepIDAndIsoSF(&lepHelper, muonTightID, muonLooseID, electronTightID, electronLooseID,
//                                              &(tightMuons.ptrToItems), &(looseMuons.ptrToItems),
//                                              &(tightElectrons.ptrToItems), &(looseElectrons.ptrToItems));
//   kinVars.push_back(&myLepIDAndIsoSF);

  //CERN version
  RecoIDIsoSIPSFs myRecoIDIsoSIPSFs(2, &(tightLoosePreselectedLeptons.ptrToItems), "skipSyst");
  kinVars.push_back(&myRecoIDIsoSIPSFs);

  LeptonTriggerScaleFactors
  myLepTrig(&lepHelper, &(tightMuons.ptrToItems), &(looseMuons.ptrToItems), &(preselectedMuons.ptrToItems),
            &(tightElectrons.ptrToItems), &(looseElectrons.ptrToItems), &(preselectedElectrons.ptrToItems));
  kinVars.push_back(&myLepTrig);

//   TightChargeAndLepMVAScaleFactors myTightChargeAndLepMVASFs(2, &(tightLoosePreselectedLeptons.ptrToItems));
//   kinVars.push_back(&myTightChargeAndLepMVASFs);

  TightChargeAndLepCutScaleFactors myTightChargeAndLepCutSFs(2, &(tightLoosePreselectedLeptons.ptrToItems));
  kinVars.push_back(&myTightChargeAndLepCutSFs);

  CleanEventVars myClean(&lepHelper, &(events.ptrToItems), &(primaryVertexes.ptrToItems));
  kinVars.push_back(&myClean);

  CheckTwoLepTrigger checkTrig(&lepHelper, &(hltCollection.ptrToItems));
  kinVars.push_back(&checkTrig);

//   DataDrivenFR<BNleptonCollection>
//   myDataDrivenFRAllLeptons(&lepHelper, &(tightLoosePreselectedLeptons.ptrToItems), &(mediumCSVJets.ptrToItems), 2, 0.7, "FR_merged_data", "QF_data_el");
//   kinVars.push_back(&myDataDrivenFRAllLeptons);

//   DataDrivenFR<BNleptonCollection>
//   myDataDrivenFRAllLeptonsLoose(&lepHelper, &(tightLoosePreselectedLeptons.ptrToItems), &(mediumCSVJets.ptrToItems), 2, -0.3, "FR_merged_data", "QF_data_el", "_Loose");
//   kinVars.push_back(&myDataDrivenFRAllLeptonsLoose);

  TightCharges myTightCharges(&(tightLoosePreselectedLeptons.ptrToItems), "CERN_tight_charge", "all_leptons_by_pt", 2);
  kinVars.push_back(&myTightCharges);
  //myTightCharges.setCut("pass");

  ////////////////////////// collection sizes

  GenericCollectionSizeVariable<BNjetCollection> numJets(&(jets.ptrToItems), "numJets");
  kinVars.push_back(&numJets);
  numJets.setCutMin(2);
  //cutVars.push_back(&numJets);

  GenericCollectionSizeVariable<BNjetCollection> numLooseBJets(&(looseCSVJets.ptrToItems), "numLooseBJets");
  kinVars.push_back(&numLooseBJets);

  GenericCollectionSizeVariable<BNjetCollection> numMediumBJets(&(mediumCSVJets.ptrToItems), "numMediumBJets");
  kinVars.push_back(&numMediumBJets);
  numMediumBJets.setCutMin(1);
  //cutVars.push_back(&numMediumBJets);

  GenericCollectionSizeVariable<BNmuonCollection> numAllMuons(&(tightLoosePreselectedMuons.ptrToItems), "numAllMuons");
  kinVars.push_back(&numAllMuons);

  GenericCollectionSizeVariable<BNelectronCollection> numAllElectrons(&(tightLoosePreselectedElectrons.ptrToItems), "numAllElectrons");
  kinVars.push_back(&numAllElectrons);

  GenericCollectionSizeVariable<BNleptonCollection> numAllLeptons(&(tightLoosePreselectedLeptons.ptrToItems), "numAllLeptons");
  kinVars.push_back(&numAllLeptons);
  numAllLeptons.setCutMin(2);
  cutVars.push_back(&numAllLeptons);

//   GenericCollectionSizeVariable<BNmuonCollection> numTightLooseMuons(&(tightLooseMuons.ptrToItems), "numTightLooseMuons");
//   kinVars.push_back(&numTightLooseMuons);

//   GenericCollectionSizeVariable<BNelectronCollection> numTightLooseElectrons(&(tightLooseElectrons.ptrToItems), "numTightLooseElectrons");
//   kinVars.push_back(&numTightLooseElectrons);

//   GenericCollectionSizeVariable<BNleptonCollection> numTightLooseLeptons(&(tightLooseLeptons.ptrToItems), "numTightLooseLeptons");
//   kinVars.push_back(&numTightLooseLeptons);

//   GenericCollectionSizeVariable<BNmuonCollection> numTightMuons(&(tightMuons.ptrToItems), "numTightMuons");
//   kinVars.push_back(&numTightMuons);

//   GenericCollectionSizeVariable<BNelectronCollection> numTightElectrons(&(tightElectrons.ptrToItems), "numTightElectrons");
//   kinVars.push_back(&numTightElectrons);

  GenericCollectionSizeVariable<BNleptonCollection> numTightLeptons(&(tightLeptons.ptrToItems), "numTightLeptons");
  kinVars.push_back(&numTightLeptons);

  ////////////////////////// lep MVAs
  LepMVAs<BNleptonCollection> myLepMVAsAllLeptons(&lepHelper, &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 2);
  kinVars.push_back(&myLepMVAsAllLeptons);

  LepCuts<BNleptonCollection> myLepCutsAllLeptons(beanHelper, &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 2);
  kinVars.push_back(&myLepCutsAllLeptons);

  ////////////////////////// composite objects
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection>
    myMinMassLepLepAll("mass", "min", "min_mass_leplep_all",
                       &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                       &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99);
  kinVars.push_back(&myMinMassLepLepAll);
  
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection>
    myZLikeMassLepLepSFOS("mass", "closest_to", "ZLike_mass_leplep_SFOS",
                          &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                          &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                          91.2, "same_flavour", "opposite_sign");
  kinVars.push_back(&myZLikeMassLepLepSFOS);
  
  TwoObjectKinematic<BNleptonCollection, BNjetCollection>
    myMHT("pt", "vector_sum", "mht",
          &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
          &(jets.ptrToItems), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMHT);
  
  int sampleNumber = (int)lepHelper.sampleNumber;
  double weight_Xsec = (double)lepHelper.weight_Xsec;
  int nGen = (int)lepHelper.nGen;
  double Xsec = (double)lepHelper.Xsec;
  summaryTree->Branch("sampleNumber", &sampleNumber);
  summaryTree->Branch("weight_Xsec", &weight_Xsec);
  summaryTree->Branch("nGen", &nGen);
  summaryTree->Branch("Xsec", &Xsec);

  Char_t *dataset = (Char_t *)lepHelper.dataset.c_str();
  summaryTree->Branch("dataset", (void*)dataset, "dataset/C");

  ////////// all leptons //////////
  //Used for muon tight charge
  GenericCollectionMember<int, BNleptonCollection>
  allLeptonNumberOfValidTrackerHitsInnerTrack(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "numberOfValidTrackerHitsInnerTrack", "all_leptons_by_pt", KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allLeptonNumberOfValidTrackerHitsInnerTrack);

  //Used for electron tight charge
  GenericCollectionMember<int, BNleptonCollection>
  allLeptonIsGsfCtfScPixChargeConsistent(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "isGsfCtfScPixChargeConsistent", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allLeptonIsGsfCtfScPixChargeConsistent);

  GenericCollectionMember<int, BNleptonCollection>
  allLeptonPassConvVeto(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "passConvVeto", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allLeptonPassConvVeto);

  GenericCollectionMember<int, BNleptonCollection>
  allLeptonNumberOfExpectedInnerHits(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "numberOfExpectedInnerHits", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allLeptonNumberOfExpectedInnerHits);

//   //Should be used for muon tight charge, but unfilled in BEANs
//   GenericCollectionMember<double, BNleptonCollection>
//   allLeptonInnerTkPt(Reflex::Type::ByName("BNlepton"),
//                      &(tightLoosePreselectedLeptons.ptrToItems), "innerTrackPt",
//                      "all_leptons_by_pt", KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&allLeptonInnerTkPt);

//   GenericCollectionMember<double, BNleptonCollection>
//   allLeptonInnerTkPtError(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
//                           "innerTrackPtError", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&allLeptonInnerTkPtError);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonPt(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "pt", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allLeptonPt);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonEta(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "eta", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allLeptonEta);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonPhi(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "phi", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allLeptonPhi);

  GenericCollectionMember<int, BNleptonCollection>
  allLeptonTkCharge(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "tkCharge", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allLeptonTkCharge);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonJetBTagCSV(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "jetBTagCSV", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allLeptonJetBTagCSV);

  //Begin extra lepton quality variables

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonJetPtRatio(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "jetPtRatio", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allLeptonJetPtRatio);

//   GenericCollectionMember<double, BNleptonCollection>
//   allLeptonJetDeltaR(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "jetDeltaR", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&allLeptonJetDeltaR);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonChargedHadronIsoDR04(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "chargedHadronIsoDR04", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allLeptonChargedHadronIsoDR04);

//   GenericCollectionMember<double, BNleptonCollection>
//   allLeptonPuChargedHadronIsoDR04(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "puChargedHadronIsoDR04", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&allLeptonPuChargedHadronIsoDR04);

//   GenericCollectionMember<double, BNleptonCollection>
//   allLeptonNeutralHadronIsoDR04(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "neutralHadronIsoDR04", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&allLeptonNeutralHadronIsoDR04);

//   GenericCollectionMember<double, BNleptonCollection>
//   allLeptonPhotonIsoDR04(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "photonIsoDR04", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&allLeptonPhotonIsoDR04);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonSIP(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "SIP", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allLeptonSIP);

//   GenericCollectionMember<double, BNleptonCollection>
//   allLeptonCorrectedD0Vertex(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "correctedD0Vertex", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&allLeptonCorrectedD0Vertex);

//   GenericCollectionMember<double, BNleptonCollection>
//   allLeptonCorrectedDZ(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "correctedDZ", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&allLeptonCorrectedDZ);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonIP(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "IP", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allLeptonIP);

//   GenericCollectionMember<double, BNleptonCollection>
//   allLeptonIPError(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "IPError", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&allLeptonIPError);

  //End extra lepton quality variables

  GenericCollectionMember<int, BNleptonCollection>
  allLeptonIsMuon(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "isMuon", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allLeptonIsMuon);

  GenericCollectionMember<int, BNleptonCollection>
  allLeptonIsElectron(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "isElectron", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allLeptonIsElectron);

  GenericCollectionMember<int, BNleptonCollection>
  allLeptonGenMotherId(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "genMotherId", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allLeptonGenMotherId);

  GenericCollectionMember<int, BNleptonCollection>
  allLeptonGenGrandMother00Id(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "genGrandMother00Id", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allLeptonGenGrandMother00Id);

  /////////////////////////////////////
  //// REQUIRED - Must do something with muons and electrons for leptons to be filled
  /////////////////////////////////////

  GenericCollectionMember<int, BNmuonCollection>
  allMuonIsMuon(Reflex::Type::ByName("BNmuon"), &(tightLoosePreselectedMuons.ptrToItems), "isMuon", "all_muons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allMuonIsMuon);

  GenericCollectionMember<int, BNelectronCollection>
  allElectronIsElectron(Reflex::Type::ByName("BNelectron"), &(tightLoosePreselectedElectrons.ptrToItems), "isElectron", "all_electrons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allElectronIsElectron);

  /////////////////////////////////////
  //// END REQUIRED - Must do something with muons and electrons for leptons to be filled
  /////////////////////////////////////
  
  ////////// met //////////
  GenericCollectionMember<double, BNmetCollection>
  metPt(Reflex::Type::ByName("BNmet"), &(met.ptrToItems), "pt", "met",  KinematicVariableConstants::FLOAT_INIT, 1);
  kinVars.push_back(&metPt);

  GenericCollectionMember<double, BNmetCollection>
  met1d(Reflex::Type::ByName("BNmet"), &(met.ptrToItems), "pt", "metpfType1CorrectedMetBN",  KinematicVariableConstants::FLOAT_INIT, 1);
  kinVars.push_back(&met1d);

  int numExtraPartons = -99;
  summaryTree->Branch("numExtraPartons", &numExtraPartons);

  ////////// event info //////////
  GenericCollectionMember<unsigned, BNeventCollection>
  runNumber(Reflex::Type::ByName("BNevent"), &(events.ptrToItems), "run", "eventInfo", KinematicVariableConstants::UINT_INIT, 1);
  kinVars.push_back(&runNumber);

  GenericCollectionMember<unsigned, BNeventCollection>
  lumiBlock(Reflex::Type::ByName("BNevent"), &(events.ptrToItems), "lumi", "eventInfo",  KinematicVariableConstants::UINT_INIT, 1);
  kinVars.push_back(&lumiBlock);

  // this is a long inside BNevent: just using keyword long won't work-- needs to be Long64_t
  GenericCollectionMember<Long64_t, BNeventCollection>
  eventNumber(Reflex::Type::ByName("BNevent"),  &(events.ptrToItems), "evt", "eventInfo",  KinematicVariableConstants::INT_INIT, 1);
  kinVars.push_back(&eventNumber);

  MetLD myMetLD(&myMHT, &metPt);
  kinVars.push_back(&myMetLD);

  ////////// Final BDT inputs ////////////

  cutVars.push_back(&numJets);
  cutVars.push_back(&numMediumBJets);

  //// SS ttW
  //myMatchTester_ttW_SS
  //myMatchTester_ttbar_fake_SS
  //myMetLD  
  GenericCollectionMember<double, BNjetCollection> allJetByCSVBtagCombinedSecVertex(Reflex::Type::ByName("BNjet"), &(jetsByCSV.ptrToItems),
                                                                                    "btagCombinedSecVertex", "jets_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allJetByCSVBtagCombinedSecVertex);
  
  ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection>
    myMTOfEverything("MT", "vector_sum", "MT_of_everything",
                     &(met.ptrToItems), "met", 1, 1,
                     &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 2,
                     &(jets.ptrToItems), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMTOfEverything);
  
  //// 3l ttW
  //numMediumBJets
  //MT_of_everything
  ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection>
    myMassOfEverything("mass", "vector_sum", "mass_of_everything",
                     &(met.ptrToItems), "met", 1, 1,
                     &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 2,
                     &(jets.ptrToItems), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMassOfEverything);

  //Slight modification of MatchTester_ttW_3l
  MatchTester_ttbar_ll myMatchTester_ttbar_ll(&(tightLoosePreselectedLeptons.ptrToItems), &(jetsByCSV.ptrToItems));
  kinVars.push_back(&myMatchTester_ttbar_ll);

  ////////// End of Final BDT inputs ////////////
  

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

  for (ev.toBegin(); !ev.atEnd(); ++ev) {
    numEvents++;

    if ((numEvents > myConfig.maxEvents) && myConfig.maxEvents != -1) break;

    if (numEvents == 1 || numEvents % printEvery == 0 )
      cout << "Processing event.... " << numEvents << endl;

    if (debug > 9) cout << "---------->>>>>> Event " << numEvents << endl;

    /////////////////////////////////////////////////////////////
    //
    //    Initialize collections and apply object ids
    //
    //////////////////////////////////////////////////////////////
    jetsForLepMVA.initializeRawItemsSortedByCSV(ev, "BNproducer", "patJetsAK5PF");
    tightLoosePreselectedMuons.initializeRawItemsSortedByPt(ev, "BNproducer","selectedPatMuonsLoosePFlow");
    tightLoosePreselectedElectrons.initializeRawItemsSortedByPt(ev, "BNproducer","selectedPatElectronsGSF");

    //lepHelper.applyRochesterCorrections(tightLoosePreselectedMuons.rawItems);
    //Apply Rochester for data only
    bool applyRochester = (lepHelper.isData);
    if (applyRochester) lepHelper.applyRochesterCorrections(tightLoosePreselectedMuons.rawItems);
    //bool applySmearing = !(lepHelper.isData);
    //No smearing
    bool applySmearing = false;
    if (applySmearing) {
      lepHelper.fillMCMatchAny(tightLoosePreselectedMuons.rawItems, mcParticles.rawItems, 0.3);
      lepHelper.fillMCMatchAny(tightLoosePreselectedElectrons.rawItems, mcParticles.rawItems, 0.3);
      lepHelper.fillMCMatchID(tightLoosePreselectedMuons.rawItems, mcParticles.rawItems, 1.2);
      lepHelper.fillMCMatchID(tightLoosePreselectedElectrons.rawItems, mcParticles.rawItems, 1.2);

      lepHelper.scaleMCCollectionDZ(tightLoosePreselectedElectrons.rawItems);
      lepHelper.scaleMCCollectionDZ(tightLoosePreselectedMuons.rawItems);
      lepHelper.scaleMCCollectionDXY(tightLoosePreselectedElectrons.rawItems);
      lepHelper.scaleMCCollectionDXY(tightLoosePreselectedMuons.rawItems);
    }
    lepHelper.fillSIP(tightLoosePreselectedMuons.rawItems, applySmearing);
    lepHelper.fillSIP(tightLoosePreselectedElectrons.rawItems, applySmearing);
    lepHelper.fillLepJetPtRatio(tightLoosePreselectedMuons.rawItems, jetsForLepMVA.rawItems, applySmearing);
    lepHelper.fillLepJetPtRatio(tightLoosePreselectedElectrons.rawItems, jetsForLepMVA.rawItems, applySmearing);
    lepHelper.fillLepJetDeltaR(tightLoosePreselectedMuons.rawItems, jetsForLepMVA.rawItems, applySmearing);
    lepHelper.fillLepJetDeltaR(tightLoosePreselectedElectrons.rawItems, jetsForLepMVA.rawItems, applySmearing);
    lepHelper.fillLepJetBTagCSV(tightLoosePreselectedMuons.rawItems, jetsForLepMVA.rawItems);
    lepHelper.fillLepJetBTagCSV(tightLoosePreselectedElectrons.rawItems, jetsForLepMVA.rawItems);

    tightLoosePreselectedElectrons.keepSelectedParticles(electronPreselectedID);
    tightElectrons.initializeRawItems(tightLoosePreselectedElectrons.rawItems);
    tightElectrons.keepSelectedParticles(electronTightID);
//     tightLooseElectrons.initializeRawItems(tightLoosePreselectedElectrons.rawItems);
//     tightLooseElectrons.keepSelectedParticles(electronLooseID);
    looseElectrons.initializeRawItems(tightLoosePreselectedElectrons.rawItems);
    looseElectrons.keepSelectedDifference(electronLooseID, electronTightID);
    preselectedElectrons.initializeRawItems(tightLoosePreselectedElectrons.rawItems);
    preselectedElectrons.keepSelectedDifference(electronPreselectedID, electronLooseID);
//     loosePreselectedElectrons.initializeRawItems(tightLoosePreselectedElectrons.rawItems);
//     loosePreselectedElectrons.addUnion({looseElectrons.items, preselectedElectrons.items});

    tightLoosePreselectedMuons.keepSelectedParticles(muonPreselectedID);
    tightMuons.initializeRawItems(tightLoosePreselectedMuons.rawItems);
    tightMuons.keepSelectedParticles(muonTightID);
    looseMuons.initializeRawItems(tightLoosePreselectedMuons.rawItems);
    looseMuons.keepSelectedDifference(muonLooseID, muonTightID);
    preselectedMuons.initializeRawItems(tightLoosePreselectedMuons.rawItems);
    preselectedMuons.keepSelectedDifference(muonPreselectedID, muonLooseID);
//     tightLooseMuons.initializeRawItems(tightLoosePreselectedMuons.rawItems);
//     tightLooseMuons.keepSelectedParticles(muonLooseID);

    //Can't place above "tightLoosePreselectedMuons.keepSelectedParticles(muonPreselectedID);" line - won't work
    auto electronPt10 = [] (BNelectron e) { return (e.pt > 10); };
    tightLoosePreselectedElectrons.keepSelectedParticles(electronPt10);
    auto muonPt10 = [] (BNmuon m) { return (m.pt > 10); };
    tightLoosePreselectedMuons.keepSelectedParticles(muonPt10);
    
    // Require reset before first pushback to avoid keeping leptons from previous event
    tightLeptons.resetAndPushBack(tightElectrons.items);
    tightLeptons.pushBackAndSort(tightMuons.items);
//     looseLeptons.resetAndPushBack(looseElectrons.items);
//     looseLeptons.pushBackAndSort(looseMuons.items);
//     preselectedLeptons.resetAndPushBack(preselectedElectrons.items);
//     preselectedLeptons.pushBackAndSort(preselectedMuons.items);
//     tightLooseLeptons.resetAndPushBack(tightLooseElectrons.items);
//     tightLooseLeptons.pushBackAndSort(tightLooseMuons.items);
    tightLoosePreselectedLeptons.resetAndPushBack(tightLoosePreselectedElectrons.items);
    tightLoosePreselectedLeptons.pushBackAndSort(tightLoosePreselectedMuons.items);

    jets.initializeRawItemsSortedByPt(ev, "BNproducer","selectedPatJetsPFlow");
    jets.cleanJets(tightLoosePreselectedLeptons.items);
    jets.correctRawJets(jetSyst);
    jets.keepSelectedJets(25.0, 2.4, jetID::jetLoose, '-');
    jetsByCSV.initializeRawItemsSortedByCSV(jets.items);
    looseCSVJets.initializeRawItems(jets.rawItems);
    looseCSVJets.keepSelectedJets(25.0, 2.4, jetID::jetLoose, 'L');
    mediumCSVJets.initializeRawItems(jets.rawItems);
    mediumCSVJets.keepSelectedJets(25.0, 2.4, jetID::jetLoose, 'M');

    met.initializeRawItems(ev, "BNproducer","patMETsPFlow");
    met.getCorrectedMet(jets);
    events.initializeRawItems(ev, "BNproducer", "");
    mcParticles.initializeRawItems(ev, "BNproducer", "MCstatus3");
    primaryVertexes.initializeRawItems(ev, "BNproducer","offlinePrimaryVertices");
    hltCollection.initializeRawItems(ev, "BNproducer", "HLT");

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

    getNumExtraPartons(beanHelper, mcParticles.items, numExtraPartons);
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

