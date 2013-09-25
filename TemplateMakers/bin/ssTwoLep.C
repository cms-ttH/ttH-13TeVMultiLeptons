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
  numJets.setCut(2);
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

  // CSV weights don't exist for jets with a pt < 30
  //   CSVWeights myCSV(&lepHelper);
  //   kinVars.push_back(&myCSV);

  PUWeights myPU(&lepHelper);
  kinVars.push_back(&myPU);

  TopPtWeights myTopPt(&lepHelper);
  kinVars.push_back(&myTopPt);

  XsecWeight myXsec (&lepHelper);
  kinVars.push_back(&myXsec);

  LeptonScaleFactors myLepSF(&lepHelper, muonTightID, muonLooseID, electronTightID, electronLooseID);
  kinVars.push_back(&myLepSF);

  LeptonTriggerScaleFactors myLepTrig( &lepHelper);
  kinVars.push_back(&myLepTrig);

  CleanEventVars myClean (&lepHelper);
  kinVars.push_back(&myClean);

  CheckTwoLepTrigger checkTrig (&lepHelper);
  kinVars.push_back(&checkTrig);

  MassLepLep mll;
  kinVars.push_back(&mll);

  // 6 integers: tight, loose, preselected,
  // tightLoose, loosePreselected, and
  // tightLoosePreselected - AWB
  LepMVAs myLepMVAs(&lepHelper, 2, 2, 2, 0, 0, 3);
  kinVars.push_back(&myLepMVAs);

  MHT myMHT;
  kinVars.push_back(&myMHT);

  SumLep1Lep2MetPt suml1l2metPts;
  kinVars.push_back(&suml1l2metPts);

  DBCorrectedRelIsoDR04s myDBCorrectedRelIsoDR04s(&lepHelper, 4);
  kinVars.push_back(&myDBCorrectedRelIsoDR04s);

  HiggsDecayType myHiggsDecayType(&lepHelper);
  kinVars.push_back(&myHiggsDecayType);

  LepTrackCharges myLepTrackCharges(2);
  kinVars.push_back(&myLepTrackCharges);
  myLepTrackCharges.setCut("SS");
  cutVars.push_back(&myLepTrackCharges);

  CERNTightCharges myCERNTightCharges(&(selectedCollections.tightLoosePreselectedLeptonCollection), "CERN_tight_charge", "all_leptons_by_pt", 2);
  kinVars.push_back(&myCERNTightCharges);
  myCERNTightCharges.setCut("pass");

  int TwoMuon = 0;
  int TwoElectron = 0;
  int MuonElectron = 0;

  summaryTree->Branch("TwoMuon", &TwoMuon);
  summaryTree->Branch("TwoElectron", &TwoElectron);
  summaryTree->Branch("MuonElectron", &MuonElectron);

  ////////// all leptons //////////
  GenericCollectionMember<double, BNleptonCollection> allLeptonPt(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection), "pt", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonPt);

  GenericCollectionMember<double, BNleptonCollection> allLeptonTkPT(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection), "tkPT", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonTkPT);
  
  GenericCollectionMember<double, BNleptonCollection> allLeptonEta(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection), "eta", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonEta);

  GenericCollectionMember<int, BNleptonCollection> allLeptonIsMuon(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection), "isMuon", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonIsMuon);

  GenericCollectionMember<int, BNleptonCollection> allLeptonIsElectron(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection), "isElectron", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonIsElectron);

  GenericCollectionMember<int, BNleptonCollection> allLeptonTkCharge(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection), "tkCharge", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonTkCharge);

  GenericCollectionMember<double, BNleptonCollection> allLeptonD0(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),  "correctedD0Vertex", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonD0);

  GenericCollectionMember<double, BNleptonCollection> allLeptonDZ(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),  "correctedDZ", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonDZ);

  GenericCollectionMember<double, BNleptonCollection> allLeptonImpactParameter(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),  "IP", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonImpactParameter);

  GenericCollectionMember<double, BNleptonCollection> allLeptonImpactParameterError(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),  "IPError", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonImpactParameterError);

  GenericCollectionMember<double, BNleptonCollection> allLeptonPhi(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),  "phi", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonPhi);    
  
  ////////// all muons //////////
//   GenericCollectionMember<double, BNmuonCollection> allMuonSamPT(Reflex::Type::ByName("BNmuon"), &(selectedCollections.tightLoosePreselectedMuonCollection), "samPT", "all_muons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&allMuonSamPT);

//   GenericCollectionMember<double, BNmuonCollection> allMuonComPT(Reflex::Type::ByName("BNmuon"), &(selectedCollections.tightLoosePreselectedMuonCollection), "comPT", "all_muons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&allMuonComPT);  

  GenericCollectionMember<int, BNmuonCollection> allMuonPFmuon(Reflex::Type::ByName("BNmuon"), &(selectedCollections.tightLoosePreselectedMuonCollection), "isPFMuon", "all_muons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allMuonPFmuon);
  
  GenericCollectionMember<int, BNmuonCollection> allMuonGlobalMuon(Reflex::Type::ByName("BNmuon"), &(selectedCollections.tightLoosePreselectedMuonCollection),  "isGlobalMuon", "all_muons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allMuonGlobalMuon);

  GenericCollectionMember<int, BNmuonCollection> allMuonTrackerMuon(Reflex::Type::ByName("BNmuon"), &(selectedCollections.tightLoosePreselectedMuonCollection),  "isTrackerMuon", "all_muons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allMuonTrackerMuon);

  GenericCollectionMember<double, BNmuonCollection> tightMuonPt(Reflex::Type::ByName("BNmuon"), &(selectedCollections.tightLoosePreselectedMuonCollection), "pt", "all_muons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&tightMuonPt);

  GenericCollectionMember<double, BNmuonCollection> tightMuonEta(Reflex::Type::ByName("BNmuon"), &(selectedCollections.tightLoosePreselectedMuonCollection), "eta", "all_muons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&tightMuonEta);

  ////////// all electrons //////////
  GenericCollectionMember<int, BNelectronCollection> allElectronNumberOfExpectedInnerHits(Reflex::Type::ByName("BNelectron"), &(selectedCollections.tightLoosePreselectedElectronCollection), "numberOfExpectedInnerHits", "all_electrons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allElectronNumberOfExpectedInnerHits);

  GenericCollectionMember<int, BNelectronCollection> allElectronPassConvVeto(Reflex::Type::ByName("BNelectron"), &(selectedCollections.tightLoosePreselectedElectronCollection), "passConvVeto", "all_electrons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allElectronPassConvVeto);  

  ////////// tight electrons //////////
  GenericCollectionMember<double, BNelectronCollection> tightElectronEta(Reflex::Type::ByName("BNelectron"), &(selectedCollections.tightElectronCollection), "eta", "tight_electrons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&tightElectronEta);  

  GenericCollectionMember<double, BNelectronCollection> tightElectronPt(Reflex::Type::ByName("BNelectron"), &(selectedCollections.tightElectronCollection), "pt", "tight_electrons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&tightElectronPt);  

  ////////// all jets //////////
  GenericCollectionMember<double, BNjetCollection> allJetPt(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetCollection), "pt", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetPt);

  GenericCollectionMember<double, BNjetCollection> allJetEta(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetCollection), "eta", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetEta);

  GenericCollectionMember<double, BNjetCollection> allJetPhi(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetCollection), "phi", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetPhi);  

  GenericCollectionMember<double, BNjetCollection> allJetCSV(Reflex::Type::ByName("BNjet"),  &(selectedCollections.jetCollection), "btagCombinedSecVertex", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetCSV);

  ////////// met ////////// 
  GenericCollectionMember<double, BNmetCollection> metPt(Reflex::Type::ByName("BNmet"),  &(selectedCollections.metCollection), "pt", "met",  KinematicVariableConstants::FLOAT_INIT, 1);
  kinVars.push_back(&metPt);

  ////////// event info ////////// 
  GenericCollectionMember<unsigned, BNeventCollection> runNumber(Reflex::Type::ByName("BNevent"), &(selectedCollections.eventCollection), "run", "eventInfo",  KinematicVariableConstants::UINT_INIT, 1);
  kinVars.push_back(&runNumber);

  GenericCollectionMember<unsigned, BNeventCollection> lumiBlock(Reflex::Type::ByName("BNevent"), &(selectedCollections.eventCollection), "lumi", "eventInfo",  KinematicVariableConstants::UINT_INIT, 1);
  kinVars.push_back(&lumiBlock);

  // this is a long inside BNevent
  // just using keyword long won't work
  // needs to be Long64_t 
  GenericEventCollectionMember<Long64_t, BNeventCollection> eventNumber(Reflex::Type::ByName("BNevent"),  "evt", "eventInfo",  KinematicVariableConstants::INT_INIT, 1);
  kinVars.push_back(&eventNumber);

  MetLD myMetLD(&myMHT, &metPt);
  kinVars.push_back(&myMetLD);

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

      //!!!!    Skip The event  ///////////////
      
      continue;

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
