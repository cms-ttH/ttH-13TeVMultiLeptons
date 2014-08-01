#include "ttHMultileptonAnalysis/TemplateMakers/interface/BEANFileInterface.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/HelperLeptonCore.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/GenericCollection.h"

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

void LeptonVarsThisAnalysis(BNmuonCollection& tightMuons, BNelectronCollection& tightElectrons,
                            BNmuonCollection& tightLooseMuons, BNelectronCollection& tightLooseElectrons,
                            bool PassTwoLepton, int & TwoMuon, int & TwoElectron, int & MuonElectron) {
    //Collection definitions set by muonID::muonID and electronID::electronID inside main function
    unsigned numTightMuons =  tightMuons.size();
    unsigned numTightElectrons = tightElectrons.size();
    unsigned numTightLooseMuons = tightLooseMuons.size();
    unsigned numTightLooseElectrons = tightLooseElectrons.size();

    TwoMuon = 0; TwoElectron = 0; MuonElectron = 0; PassTwoLepton = 0;

    if ( numTightMuons >= 1 && numTightLooseMuons == 2 && numTightLooseElectrons == 0 ) TwoMuon = 1;
    if ( numTightElectrons >= 1 && numTightLooseElectrons == 2 && numTightLooseMuons == 0 ) TwoElectron = 1;
    if ( ( numTightMuons + numTightElectrons ) >= 1 && numTightLooseMuons == 1 && numTightLooseElectrons == 1 ) MuonElectron = 1;
    if ( TwoMuon + TwoElectron + MuonElectron == 1 ) PassTwoLepton = 1;

    return;
}

void getNumExtraPartons(BEANhelper * beanHelper, BNmcparticleCollection& mcParticles, int& numExtraPartons) {

  numExtraPartons = beanHelper->GetNumExtraPartons(mcParticles);

  return;
}

void ttPlusHFKeepEventFunction(BEANhelper * beanHelper, BNmcparticleCollection& mcParticles,
                               BNjetCollection& jets, bool & ttPlusHFKeepEventBool) {

  ttPlusHFKeepEventBool = beanHelper->ttPlusHFKeepEvent(mcParticles, jets);

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

  // setup the analysis
  // it comes from the lepHelper
  BEANhelper * beanHelper = lepHelper.setupAnalysisParameters("2012_53x", myConfig.sampleName);

  sysType::sysType jetSyst = sysType::NA;
  if (myConfig.jetSyst == "NA") jetSyst = sysType::NA;
  else if (myConfig.jetSyst == "JESUp") jetSyst = sysType::JESup;
  else if (myConfig.jetSyst == "JESDown") jetSyst = sysType::JESdown;
  else std::cout << "No valid JES corrections specified - using nominal" << std::endl;

  // ---------------------------------------------
  // Note for future development: should these be
  // saved inside the lepHelper somewhere?
  // For now they are ok here
  // ---------------------------------------------

  muonID::muonID muonTightID = muonID::muonTight;
  muonID::muonID muonLooseID = muonID::muonLoose;
  muonID::muonID muonPreselectedID = muonID::muonNoCuts;
  electronID::electronID electronTightID = electronID::electronTight;
  electronID::electronID electronLooseID = electronID::electronLoose;
  electronID::electronID electronPreselectedID = electronID::electronNoCuts;

  // collections
  GenericCollection<BNelectronCollection> tightElectrons(beanHelper);
  GenericCollection<BNelectronCollection> looseElectrons(beanHelper);
  GenericCollection<BNelectronCollection> preselectedElectrons(beanHelper);
  GenericCollection<BNelectronCollection> tightLooseElectrons(beanHelper);
  GenericCollection<BNelectronCollection> loosePreselectedElectrons(beanHelper);
  GenericCollection<BNelectronCollection> tightLoosePreselectedElectrons(beanHelper);

  GenericCollection<BNmuonCollection> tightMuons(beanHelper);
  GenericCollection<BNmuonCollection> looseMuons(beanHelper);
  GenericCollection<BNmuonCollection> preselectedMuons(beanHelper);
  GenericCollection<BNmuonCollection> tightLooseMuons(beanHelper);
  GenericCollection<BNmuonCollection> tightLoosePreselectedMuons(beanHelper);

  GenericCollection<BNleptonCollection> tightLeptons(beanHelper);
  GenericCollection<BNleptonCollection> looseLeptons(beanHelper);
  GenericCollection<BNleptonCollection> preselectedLeptons(beanHelper);
  GenericCollection<BNleptonCollection> tightLooseLeptons(beanHelper);
  GenericCollection<BNleptonCollection> tightLoosePreselectedLeptons(beanHelper);

  GenericCollection<BNtauCollection> tightTaus(beanHelper);
  GenericCollection<BNtauCollection> tightLooseTaus(beanHelper);
  GenericCollection<BNtauCollection> tightLoosePreselectedTaus(beanHelper);

  GenericCollection<BNjetCollection> jets(beanHelper);
  GenericCollection<BNjetCollection> mediumCSVJets(beanHelper);

  GenericCollection<BNmetCollection> met(beanHelper);
  GenericCollection<BNprimaryvertexCollection> primaryVertexes(beanHelper);
  GenericCollection<BNtriggerCollection> hltCollection(beanHelper);
  GenericCollection<BNeventCollection> events(beanHelper);
  GenericCollection<BNmcparticleCollection> mcParticles(beanHelper);

  // declare your kinematic variables that you want
  // to be written out into the tree
  vector<ArbitraryVariable*> kinVars;
  vector<ArbitraryVariable*> cutVars;

//   GenericCollectionSizeVariable<BNprimaryvertex> numPV(&(rawCollections.primaryVertexCollection), "numPV");
//   kinVars.push_back(&numPV);
//jet selection: exactly two jets  -------
  GenericCollectionSizeVariable<BNjetCollection> numJets(&(jets.ptrToItems), "numJets");
  kinVars.push_back(&numJets);
  numJets.setCutMin(2);
  numJets.setCutMax(2);
  cutVars.push_back(&numJets);

  GenericCollectionSizeVariable<BNjetCollection> numMediumBJets(&(mediumCSVJets.ptrToItems), "numMediumBJets");
  kinVars.push_back(&numMediumBJets);
//lepton selection: exactly two, at least one tight  -------
  GenericCollectionSizeVariable<BNleptonCollection> numTightLooseLeptons(&(tightLooseLeptons.ptrToItems), "numTightLooseLeptons");
  kinVars.push_back(&numTightLooseLeptons);
  numTightLooseLeptons.setCutMin(2);
  numTightLooseLeptons.setCutMax(2);
  cutVars.push_back(&numTightLooseLeptons);

  GenericCollectionSizeVariable<BNleptonCollection> numTightLeptons(&(tightLeptons.ptrToItems), "numTightLeptons");
  kinVars.push_back(&numTightLeptons);
  numTightLeptons.setCutMin(1);
  cutVars.push_back(&numTightLeptons);

  // various event weights
  //Older or deprecated? AWB 01/08/14
  //CSVWeightsSF myCSV(beanHelper, &(jets.ptrToItems));
  //kinVars.push_back(&myCSV);

  CSVWeights myCSV(beanHelper, &(jets.ptrToItems), jetSyst);
  kinVars.push_back(&myCSV);

  PUWeights myPU(&lepHelper, &(events.ptrToItems));
  kinVars.push_back(&myPU);

  TopPtWeights myTopPt(&lepHelper, &(mcParticles.ptrToItems));
  kinVars.push_back(&myTopPt);

  LeptonIDAndIsoScaleFactors myLepIDAndIsoSF(&lepHelper, muonTightID, muonLooseID, electronTightID, electronLooseID,
                                             &(tightMuons.ptrToItems), &(looseMuons.ptrToItems),
                                             &(tightElectrons.ptrToItems), &(looseElectrons.ptrToItems));
  kinVars.push_back(&myLepIDAndIsoSF);

  LeptonTriggerScaleFactors myLepTrig(&lepHelper, &(tightMuons.ptrToItems), &(looseMuons.ptrToItems), &(preselectedMuons.ptrToItems),
                                      &(tightElectrons.ptrToItems), &(looseElectrons.ptrToItems), &(preselectedElectrons.ptrToItems));
  kinVars.push_back(&myLepTrig);

  CleanEventVars myClean(&lepHelper, &(events.ptrToItems), &(primaryVertexes.ptrToItems));
  kinVars.push_back(&myClean);

  CheckTwoLepTrigger checkTrig(&lepHelper, &(hltCollection.ptrToItems));
  kinVars.push_back(&checkTrig);

  /////////
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMassLepLep("mass", "min", "mass_leplep",
                                                                              &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 99,
                                                                              &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 99);
  kinVars.push_back(&myMassLepLep);
  
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZmass("mass", "closest_to", "Zmass",
                                                                    &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 99,
                                                                    &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 99,
                                                                    91.2, "same_flavour");
  kinVars.push_back(&myZmass);
  
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myDeltaRLepLep("deltaR", "min", "dR_leplep",
                                                                              &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 99,
                                                                              &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 99);
  kinVars.push_back(&myDeltaRLepLep);

  TwoObjectKinematic<BNleptonCollection,BNjetCollection> myMHT("pt", "vector_sum", "mht",
                                                               &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 99,
                                                               &(jets.ptrToItems), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMHT);


  ////////// all jets //////////
  GenericCollectionMember<double, BNjetCollection> allJetPt(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems),
                                                            "pt", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allJetPt);

  GenericCollectionMember<double, BNjetCollection> allJetEta(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems),
                                                             "eta", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allJetEta);

  GenericCollectionMember<double, BNjetCollection> allJetCSV(Reflex::Type::ByName("BNjet"),  &(jets.ptrToItems),
                                                             "btagCombinedSecVertex", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allJetCSV);

  GenericCollectionMember<int, BNjetCollection> allJetFlavor(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems),
                                                            "flavour", "jets_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allJetFlavor);

  ////////// met //////////
  GenericCollectionMember<double, BNmetCollection> metPt(Reflex::Type::ByName("BNmet"),  &(met.ptrToItems),
                                                         "pt", "met",  KinematicVariableConstants::FLOAT_INIT, 1);
  kinVars.push_back(&metPt);

  ///////////////////////// opposite sign requirement
  GenericCollectionMember<int, BNleptonCollection> allLeptonTkCharge(Reflex::Type::ByName("BNlepton"), &(tightLooseLeptons.ptrToItems),
                                                                     "tkCharge", "leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allLeptonTkCharge);
  auto tkChargeCut = [] (vector<BranchInfo<int>> vars) { return ((vars[0].branchVal * vars[1].branchVal) == -1); };
  allLeptonTkCharge.setCut(tkChargeCut);
  cutVars.push_back(&allLeptonTkCharge);  //// opposite sign requirement

  GenericCollectionMember<double, BNleptonCollection> allLeptonPt(Reflex::Type::ByName("BNlepton"), &(tightLooseLeptons.ptrToItems),
                                                                     "pt", "leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allLeptonPt);

  //////// DO NOT REMOVE BELOW - ESSENTIAL FOR LEPTON COLLECTION VARIABLES TO BE FILLED ///////////////
  GenericCollectionMember<double, BNmuonCollection> allMuonPt(Reflex::Type::ByName("BNmuon"), &(tightLooseMuons.ptrToItems),
                                                                     "pt", "muons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allMuonPt);

  GenericCollectionMember<double, BNelectronCollection> allElectronPt(Reflex::Type::ByName("BNelectron"), &(tightLooseElectrons.ptrToItems),
                                                                     "pt", "electrons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allElectronPt);
  //////// DO NOT REMOVE ABOVE - ESSENTIAL FOR LEPTON COLLECTION VARIABLES TO BE FILLED ///////////////



  ////////// manual variables //////////
  int TwoMuon = 0;
  int TwoElectron = 0;
  int MuonElectron = 0;
  int PassTwoLepton = 0;
  summaryTree->Branch("TwoMuon", &TwoMuon);
  summaryTree->Branch("TwoElectron", &TwoElectron);
  summaryTree->Branch("MuonElectron", &MuonElectron);
//   summaryTree->Branch("PassTwoLepton", &PassTwoLepton);

  int numExtraPartons = -99;
//   summaryTree->Branch("numExtraPartons", &numExtraPartons);

  bool ttPlusHFKeepEventBool = false;

//   int sampleNumber = (int)lepHelper.sampleNumber;
//   double weight_Xsec = (double)lepHelper.weight_Xsec;
  int nGen = (int)lepHelper.nGen;
  double Xsec = (double)lepHelper.Xsec;
//   summaryTree->Branch("sampleNumber", &sampleNumber);
//   summaryTree->Branch("weight_Xsec", &weight_Xsec);
  summaryTree->Branch("nGen", &nGen);
  summaryTree->Branch("Xsec", &Xsec);

  ////////// event info //////////
  GenericCollectionMember<unsigned, BNeventCollection> runNumber(Reflex::Type::ByName("BNevent"), &(events.ptrToItems),
                                                                 "run", "eventInfo",  KinematicVariableConstants::UINT_INIT, 1);
  kinVars.push_back(&runNumber);

  GenericCollectionMember<unsigned, BNeventCollection> lumiBlock(Reflex::Type::ByName("BNevent"), &(events.ptrToItems),
                                                                 "lumi", "eventInfo",  KinematicVariableConstants::UINT_INIT, 1);
  kinVars.push_back(&lumiBlock);

  // this is a long inside BNevent
  // just using keyword long won't work
  // needs to be Long64_t 
  GenericCollectionMember<Long64_t, BNeventCollection> eventNumber(Reflex::Type::ByName("BNevent"),  &(events.ptrToItems),
                                                                   "evt", "eventInfo",  KinematicVariableConstants::INT_INIT, 1);
  kinVars.push_back(&eventNumber);

  ////////// variables from functions //////////
  PassZmask myPassZmask(&myZmass, &myMHT, &metPt);
  kinVars.push_back(&myPassZmask);
//   myPassZmask.setCut("PassZmask_mht");
//   cutVars.push_back(&myPassZmask);


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
  // start event loop
  for (ev.toBegin(); !ev.atEnd(); ++ev){
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
    tightLoosePreselectedMuons.initializeRawItemsSortedByPt(ev, "BNproducer","selectedPatMuonsPFlow");
    tightLoosePreselectedElectrons.initializeRawItemsSortedByPt(ev, "BNproducer","selectedPatElectronsPFlow");

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

    tightLoosePreselectedMuons.keepSelectedParticles(muonPreselectedID);
    tightMuons.initializeRawItems(tightLoosePreselectedMuons.rawItems);
    tightMuons.keepSelectedParticles(muonTightID);
    looseMuons.initializeRawItems(tightLoosePreselectedMuons.rawItems);
    looseMuons.keepSelectedDifference(muonLooseID, muonTightID);
    preselectedMuons.initializeRawItems(tightLoosePreselectedMuons.rawItems);
    preselectedMuons.keepSelectedDifference(muonPreselectedID, muonLooseID);
    tightLooseMuons.initializeRawItems(tightLoosePreselectedMuons.rawItems);
    tightLooseMuons.keepSelectedParticles(muonLooseID);

    // Require reset before first pushback to avoid keeping leptons from previous event
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

    jets.initializeRawItemsSortedByPt(ev, "BNproducer","selectedPatJetsPFlow");
    jets.correctRawJets(jetSyst);
    jets.keepSelectedJets(30.0, 2.4, jetID::jetLoose, '-');
    mediumCSVJets.initializeRawItems(jets.rawItems);
    mediumCSVJets.keepSelectedJets(30.0, 2.4, jetID::jetLoose, 'M');

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

    // Get manual variables
    LeptonVarsThisAnalysis(tightMuons.items, tightElectrons.items, tightLooseMuons.items, tightLooseElectrons.items,
                           PassTwoLepton, TwoMuon, TwoElectron, MuonElectron);

  getNumExtraPartons(beanHelper, mcParticles.items, numExtraPartons);
    if (myConfig.sampleName.find("_0p") != std::string::npos) { //0 parton samples
      //Cut to require 0 partons
      if (numExtraPartons != 0) {
        numEventsFailCuts++;
        numEventsPassCuts--;
        continue; //Don't go on to fill tree with this event
      }
    }

    if (myConfig.sampleName == "ttbar" || myConfig.sampleName.find("ttbar_") != std::string::npos ) { //ttbar samples
      ttPlusHFKeepEventFunction(beanHelper, mcParticles.items, jets.items, ttPlusHFKeepEventBool);
      if (!ttPlusHFKeepEventBool) {
        numEventsFailCuts++;
        numEventsPassCuts--;
        continue; //Don't go on to fill tree with this event
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
