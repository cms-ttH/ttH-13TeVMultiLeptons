#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/BEANFileInterface.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/HelperLeptonCore.h"

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

void LeptonVarsThisAnalysis(BEANFileInterface * inputCollections, int & TwoMuon, int & TwoElectron, int & MuonElectron, int & PassTwoLepton) {

    //Collection definitions set by muonID::muonID and electronID::electronID inside main function
    unsigned numTightMuons = inputCollections->tightMuonCollection->size();
    unsigned numTightElectrons = inputCollections->tightElectronCollection->size();
    unsigned numTightLooseMuons = inputCollections->tightLooseMuonCollection->size();
    unsigned numTightLooseElectrons = inputCollections->tightLooseElectronCollection->size();

    TwoMuon = 0; TwoElectron = 0; MuonElectron = 0; PassTwoLepton = 0;

    if ( numTightMuons >= 1 && numTightLooseMuons == 2 && numTightLooseElectrons == 0 ) TwoMuon = 1;
    if ( numTightElectrons >= 1 && numTightLooseElectrons == 2 && numTightLooseMuons == 0 ) TwoElectron = 1;
    if ( ( numTightMuons + numTightElectrons ) >= 1 && numTightLooseMuons == 1 && numTightLooseElectrons == 1 ) MuonElectron = 1;
    if ( TwoMuon + TwoElectron + MuonElectron == 1 ) PassTwoLepton = 1;

    return;
}

void getNumExtraPartons(BEANhelper * beanHelper, BEANFileInterface selectedCollections, int & numExtraPartons) {

  numExtraPartons = beanHelper->GetNumExtraPartons(*(selectedCollections.mcParticleCollection));

  return;
} 
  
void ttPlusHFKeepEventFunction(BEANhelper * beanHelper, BEANFileInterface selectedCollections,
                               BEANFileInterface rawCollections, bool & ttPlusHFKeepEventBool) {

  ttPlusHFKeepEventBool = beanHelper->ttPlusHFKeepEvent(*(selectedCollections.mcParticleCollection),
                                                        *(rawCollections.jetCollection));

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

  muonID::muonID muonTightID = muonID::muonTight;
  muonID::muonID muonLooseID = muonID::muonLoose;
  muonID::muonID muonPreselectedID = muonID::muonRaw;
  electronID::electronID electronTightID = electronID::electronTight;
  electronID::electronID electronLooseID = electronID::electronLoose;
  electronID::electronID electronPreselectedID = electronID::electronRaw;

  // declare your kinematic variables that you want
  // to be written out into the tree
  vector<ArbitraryVariable*> kinVars;
  vector<ArbitraryVariable*> cutVars;

  BEANFileInterface rawCollections;
  BEANFileInterface selectedCollections;

//   GenericCollectionSizeVariable<BNprimaryvertex> numPV(&(rawCollections.primaryVertexCollection), "numPV");
//   kinVars.push_back(&numPV);
  
  GenericCollectionSizeVariable<BNjetCollection> numJets(&(selectedCollections.jetCollection), "numJets");
  kinVars.push_back(&numJets);
  numJets.setCutMin(2);
  cutVars.push_back(&numJets);

  GenericCollectionSizeVariable<BNjetCollection> numRawJets(&(rawCollections.jetCollection), "numRawJets");
  kinVars.push_back(&numRawJets);

  GenericCollectionSizeVariable<BNjetCollection> numMediumBJets(&(selectedCollections.jetCollectionMediumCSV), "numMediumBJets");
  kinVars.push_back(&numMediumBJets);

  GenericCollectionSizeVariable<BNleptonCollection> numTightLooseLeptons(&(selectedCollections.tightLooseLeptonCollection), "numTightLooseLeptons");
  kinVars.push_back(&numTightLooseLeptons);
  numTightLooseLeptons.setCutMin(2);
  cutVars.push_back(&numTightLooseLeptons);

  GenericCollectionSizeVariable<BNleptonCollection> numAllLeptons(&(selectedCollections.tightLoosePreselectedLeptonCollection), "numAllLeptons");
  kinVars.push_back(&numAllLeptons);

  GenericCollectionSizeVariable<BNleptonCollection> numTightLeptons(&(selectedCollections.tightLeptonCollection), "numTightLeptons");
  kinVars.push_back(&numTightLeptons);
  numTightLeptons.setCutMin(1);
  cutVars.push_back(&numTightLeptons);

  GenericCollectionSizeVariable<BNmuonCollection> numTightMuons(&(selectedCollections.tightMuonCollection), "numTightMuons");
  kinVars.push_back(&numTightMuons);

  GenericCollectionSizeVariable<BNelectronCollection> numTightElectrons(&(selectedCollections.tightElectronCollection), "numTightElectrons");
  kinVars.push_back(&numTightElectrons);

  CSVWeights myCSV(&lepHelper);
  kinVars.push_back(&myCSV);

  PUWeights myPU(&lepHelper);
  kinVars.push_back(&myPU);

  TopPtWeights myTopPt(&lepHelper);
  kinVars.push_back(&myTopPt);

  LeptonIDAndIsoScaleFactors myLepIDAndIsoSF(&lepHelper, muonTightID, muonLooseID, electronTightID, electronLooseID);
  kinVars.push_back(&myLepIDAndIsoSF);

  LeptonTriggerScaleFactors myLepTrig(&lepHelper);
  kinVars.push_back(&myLepTrig);

  CleanEventVars myClean (&lepHelper);
  kinVars.push_back(&myClean);

  CheckTwoLepTrigger checkTrig (&lepHelper);
  kinVars.push_back(&checkTrig);

  //DBCorrectedRelIsoDR04s myDBCorrectedRelIsoDR04s(&lepHelper, 2);
  //kinVars.push_back(&myDBCorrectedRelIsoDR04s);

  HiggsDecayType myHiggsDecayType(&lepHelper);
  kinVars.push_back(&myHiggsDecayType);

  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMassLepLep("mass", "min", "mass_leplep",
                                                                              &(selectedCollections.tightLooseLeptonCollection), "leptons_by_pt", 1, 99,
                                                                              &(selectedCollections.tightLooseLeptonCollection), "leptons_by_pt", 1, 99);
  kinVars.push_back(&myMassLepLep);
  
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZmass("mass", "closest_to", "Zmass",
                                                                    &(selectedCollections.tightLooseLeptonCollection), "leptons_by_pt", 1, 99,
                                                                    &(selectedCollections.tightLooseLeptonCollection), "leptons_by_pt", 1, 99,
                                                                    91.2, "same_flavour");
  kinVars.push_back(&myZmass);
  
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myDeltaRLepLep("deltaR", "min", "dR_leplep",
                                                                              &(selectedCollections.tightLooseLeptonCollection), "leptons_by_pt", 1, 99,
                                                                              &(selectedCollections.tightLooseLeptonCollection), "leptons_by_pt", 1, 99);
  kinVars.push_back(&myDeltaRLepLep);

  TwoObjectKinematic<BNleptonCollection,BNjetCollection> myMHT("pt", "vector_sum", "mht",
                                                               &(selectedCollections.tightLooseLeptonCollection), "leptons_by_pt", 1, 99,
                                                               &(selectedCollections.jetCollection), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMHT);

  ////////// Variables for BDT //////////
  
  TwoObjectKinematic<BNjetCollection,BNjetCollection> myMinDrJets("deltaR", "min", "min_dr_jets",
                                                                  &(selectedCollections.jetCollection), "jets_by_pt", 1, 99,
                                                                  &(selectedCollections.jetCollection), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMinDrJets);

  TwoObjectKinematic<BNleptonCollection,BNjetCollection> mySumPt("pt", "sum", "sum_pt",
                                                                 &(selectedCollections.tightLooseLeptonCollection), "leptons_by_pt", 1, 99,
                                                                 &(selectedCollections.jetCollection), "jets_by_pt", 1, 99);
  kinVars.push_back(&mySumPt);

  TwoJetVariables myAvgBtagDiscBtags("CSV", "avg", "avg_btag_disc_btags",
                                     &(selectedCollections.jetCollectionMediumCSV), "medium_bjets_by_pt", 1, 99,
                                     &(selectedCollections.jetCollectionMediumCSV), "medium_bjets_by_pt", 1, 99);
  kinVars.push_back(&myAvgBtagDiscBtags);

  TwoJetVariables myAvgBtagDiscNonBtags("CSV", "avg", "avg_btag_disc_non_btags",
                                        &(selectedCollections.jetCollectionNotMediumCSV), "not_medium_bjets_by_pt", 1, 99,
                                        &(selectedCollections.jetCollectionNotMediumCSV), "not_medium_bjets_by_pt", 1, 99);
  kinVars.push_back(&myAvgBtagDiscNonBtags);
  
  TwoObjectKinematic<BNjetCollection,BNjetCollection> myHiggsLikeDijetMass("mass", "closest_to", "higgsLike_dijet_mass",
                                                                           &(selectedCollections.jetCollection), "jets_by_pt", 1, 99,
                                                                           &(selectedCollections.jetCollection), "jets_by_pt", 1, 99,
                                                                           115.0);
  kinVars.push_back(&myHiggsLikeDijetMass);
  
  TwoObjectKinematic<BNjetCollection,BNjetCollection> myHiggsLikeDijetMass2("mass", "second_closest_to", "higgsLike_dijet_mass2",
                                                                            &(selectedCollections.jetCollection), "jets_by_pt", 1, 99,
                                                                            &(selectedCollections.jetCollection), "jets_by_pt", 1, 99,
                                                                            115.0);
  kinVars.push_back(&myHiggsLikeDijetMass2);

  TwoObjectKinematic<BNjetCollection,BNjetCollection> myNumJetsFloat("eta", "num_within", "numJets_float",
                                                                     &(selectedCollections.jetCollection), "jets_by_pt", 1, 99,
                                                                     &(selectedCollections.jetCollection), "jets_by_pt", 1, 99,
                                                                     0.0, "", "", 5.0);
  kinVars.push_back(&myNumJetsFloat);

  TwoObjectKinematic<BNjetCollection,BNjetCollection> myNumHiggsLikeDijet15("mass", "num_within", "numHiggsLike_dijet_15_float",
                                                                            &(selectedCollections.jetCollection), "jets_by_pt", 1, 99,
                                                                            &(selectedCollections.jetCollection), "jets_by_pt", 1, 99,
                                                                            115.0, "", "", 15.0);
  kinVars.push_back(&myNumHiggsLikeDijet15);

  ////////// all leptons //////////
  GenericCollectionMember<double, BNleptonCollection> allLeptonPt(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLooseLeptonCollection),
                                                                  "pt", "leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allLeptonPt);

  GenericCollectionMember<double, BNleptonCollection> allLeptonEta(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLooseLeptonCollection),
                                                                   "eta", "leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allLeptonEta);

  GenericCollectionMember<int, BNleptonCollection> allLeptonTkCharge(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLooseLeptonCollection),
                                                                   "tkCharge", "leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allLeptonTkCharge);

  // NECESSARY TO ACTUALLY FILL LEPTON VALUES - DO NOT COMMENT OUT //
  GenericCollectionMember<double, BNmuonCollection> allMuonPt(Reflex::Type::ByName("BNmuon"), &(selectedCollections.tightLooseMuonCollection),
                                                                  "pt", "muons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allMuonPt);

  GenericCollectionMember<double, BNelectronCollection> allElectronPt(Reflex::Type::ByName("BNelectron"), &(selectedCollections.tightLooseElectronCollection),
                                                                  "pt", "electrons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allElectronPt);

  ////////// all jets //////////
  GenericCollectionMember<double, BNjetCollection> allJetPt(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetCollection),
                                                            "pt", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allJetPt);

  GenericCollectionMember<double, BNjetCollection> allJetEta(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetCollection),
                                                             "eta", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allJetEta);

  GenericCollectionMember<double, BNjetCollection> allJetCSV(Reflex::Type::ByName("BNjet"),  &(selectedCollections.jetCollection),
                                                             "btagCombinedSecVertex", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allJetCSV);

  ////////// met //////////
  GenericCollectionMember<double, BNmetCollection> metPt(Reflex::Type::ByName("BNmet"),  &(selectedCollections.metCollection),
                                                         "pt", "met",  KinematicVariableConstants::FLOAT_INIT, 1);
  kinVars.push_back(&metPt);

  ////////// manual variables //////////
  int TwoMuon = 0;
  int TwoElectron = 0;
  int MuonElectron = 0;
  int PassTwoLepton = 0;
  summaryTree->Branch("TwoMuon", &TwoMuon);
  summaryTree->Branch("TwoElectron", &TwoElectron);
  summaryTree->Branch("MuonElectron", &MuonElectron);
  summaryTree->Branch("PassTwoLepton", &PassTwoLepton);

  int numExtraPartons = -99;
  summaryTree->Branch("numExtraPartons", &numExtraPartons);

  bool ttPlusHFKeepEventBool = false;
  
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

  ////////// variables from functions //////////
  PassZmask myPassZmask(&myZmass, &myMHT, &metPt);
  kinVars.push_back(&myPassZmask);
  myPassZmask.setCut("PassZmask_mht");
  cutVars.push_back(&myPassZmask);

  FinalBDT_OS_2012 myFinalBDT_OS_2012(&myMinDrJets, &mySumPt, &myAvgBtagDiscBtags, &myAvgBtagDiscNonBtags,
                                      &myHiggsLikeDijetMass, &myHiggsLikeDijetMass2, &myNumJetsFloat, &myNumHiggsLikeDijet15);
  kinVars.push_back(&myFinalBDT_OS_2012);

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

    //For opposite sign, second argument ("isLepMVA" is FALSE)
    lepHelper.initializeInputCollections(ev, false, selectedCollections);
    lepHelper.initializeInputCollections(ev, false, rawCollections);

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
    if (debug > 9) cout << "Getting jets "  << endl;
	lepHelper.getTightCorrectedJets(30.0, 2.4, jetID::jetLoose, &selectedCollections);

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
    LeptonVarsThisAnalysis(&selectedCollections, TwoMuon, TwoElectron, MuonElectron, PassTwoLepton);

    getNumExtraPartons(beanHelper, selectedCollections, numExtraPartons);
    if (myConfig.sampleName.find("_0p") != std::string::npos) { //0 parton samples
      //Cut to require 0 partons
      if (numExtraPartons != 0) {
        numEventsFailCuts++;
        numEventsPassCuts--;
        continue; //Don't go on to fill tree with this event
      }
    }

    if (myConfig.sampleName == "ttbar" || myConfig.sampleName.find("ttbar_") != std::string::npos ) { //ttbar samples
      ttPlusHFKeepEventFunction(beanHelper, selectedCollections, rawCollections, ttPlusHFKeepEventBool);
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
