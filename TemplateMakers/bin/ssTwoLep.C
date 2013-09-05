#include "ttHMultileptonAnalysis/TemplateMakers/interface/BEANFileInterface.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/HelperLeptonCore.h"


///-------------- Kinematic Variables ------------------
#include "ttHMultileptonAnalysis/TemplateMakers/interface/EveryVariable.h"

#include "BEAN/BEANmaker/interface/BtagWeight.h"
#include "BEAN/BEANmaker/interface/BEANhelper.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/JobParameters.h"

#include "Reflex/Object.h"
#include "Reflex/Type.h"
#include "Reflex/Member.h"
#include "Reflex/Kernel.h"


bool LeptonCutThisAnalysis (BEANFileInterface * inputCollections) {

  //Collection definitions set by muonID::muonID and electronID::electronID inside main function
  unsigned numTightMuons = inputCollections->tightMuonCollection->size();
  unsigned numLooseMuons = inputCollections->looseMuonCollection->size();
  unsigned numTightElectrons = inputCollections->tightElectronCollection->size();
  unsigned numLooseElectrons = inputCollections->looseElectronCollection->size();

  bool passTwoLepton = false;

  // two tight leptons
  // we will cut on loose muons later
  if (numTightMuons ==2 || numTightElectrons==2 || (numTightMuons==1 && numTightElectrons==1))
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

  if (numTightElectrons ==2 ) {
    TwoElectron = 1;
    return;
  }

  if ( numTightElectrons ==1 && numTightMuons==1 ) {
    MuonElectron =1;
    return;
    
  }
  
}

void loadTTH125Files (vector<string> & target ) {

  //----- version 3 skims have better configurations
  target.push_back("file:/hadoop/users/awoodard/BEAN_53xOn53x_V04_skims/TTH_Inclusive_M-125_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1_skimDilep_BEAN_53xOn53x_V04_CV02/d821efbc3befd142036a29052ef27c00/output_1_2_AHw.root");                   

}



// use this function to figure out how to
// setup the job
// for now, it is just a hack to make testing easy
JobParameters parseJobOptions (int argc, char** argv) {

  JobParameters myConfig;

  vector<string> inputFiles;
  inputFiles.push_back(argv[1]);

  string outputFileName = argv[2];

  myConfig.inputFileNames = inputFiles;
  myConfig.outputFileName = outputFileName;

//   myConfig.outputFileName = "ntuple_ssTwoLep.root";
   myConfig.sampleName = "ttH125";
   myConfig.maxEvents = -1;

//   loadTTH125Files(myConfig.inputFileNames);
  
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

  // the lepton helper  
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

   // This is a hack, so that we can specify which collection to use before it is initialized inside the
   // event loop. After initialization, ptrToSelectedCollections is set to point at selectedCollections.
   BEANFileInterface * ptrToSelectedCollections = new BEANFileInterface;
   
   GenericCollectionSizeVariable<BNjetCollection> numJets(&(ptrToSelectedCollections->jetCollection), "numJets");
   kinVars.push_back(&numJets);
   numJets.setCut(2);
   cutVars.push_back(&numJets); 

   GenericCollectionSizeVariable<BNjetCollection> numLooseBJets(&(ptrToSelectedCollections->jetCollectionLooseCSV), "numLooseBJets");
   kinVars.push_back(&numLooseBJets);

   GenericCollectionSizeVariable<BNjetCollection> numMediumBJets(&(ptrToSelectedCollections->jetCollectionMediumCSV), "numMediumBJets");
   kinVars.push_back(&numMediumBJets);   
   
   GenericCollectionSizeVariable<BNleptonCollection> numAllLeptons(&(ptrToSelectedCollections->tightLoosePreselectedLeptonCollection), "numAllLeptons");
   kinVars.push_back(&numAllLeptons);

   GenericCollectionSizeVariable<BNmuonCollection> numTightMuons(&(ptrToSelectedCollections->tightMuonCollection), "numTightMuons");
   kinVars.push_back(&numTightMuons);

   GenericCollectionSizeVariable<BNelectronCollection> numTightElectrons(&(ptrToSelectedCollections->tightElectronCollection), "numTightElectrons");
   kinVars.push_back(&numTightElectrons);

   // CSV weights don't exist for jets
   // with a pt < 30
   // 
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

//    LepTrackCharges myLepTrackCharges(2);
//    kinVars.push_back(&myLepTrackCharges);
//    myLepTrackCharges.setCut("SS");
//    cutVars.push_back(&myLepTrackCharges);

  CERNTightCharges myCERNTightCharges(&(ptrToSelectedCollections->tightLoosePreselectedLeptonCollection), "CERN_tight_charge", "all_leptons_by_pt", 2);
  kinVars.push_back(&myCERNTightCharges);
  myCERNTightCharges.setCut("pass");

  int TwoMuon = 0;
  int TwoElectron = 0;
  int MuonElectron = 0;

  summaryTree->Branch("TwoMuon", &TwoMuon);
  summaryTree->Branch("TwoElectron", &TwoElectron);
  summaryTree->Branch("MuonElectron", &MuonElectron);

  ////////// all leptons //////////
  GenericCollectionMember<double, BNleptonCollection> allLeptonPt(Reflex::Type::ByName("BNlepton"), &(ptrToSelectedCollections->tightLoosePreselectedLeptonCollection), "pt", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonPt);

  GenericCollectionMember<double, BNleptonCollection> allLeptonEta(Reflex::Type::ByName("BNlepton"), &(ptrToSelectedCollections->tightLoosePreselectedLeptonCollection), "eta", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonEta);

  GenericCollectionMember<int, BNleptonCollection> allLeptonIsMuon(Reflex::Type::ByName("BNlepton"), &(ptrToSelectedCollections->tightLoosePreselectedLeptonCollection), "isMuon", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonIsMuon);

  GenericCollectionMember<int, BNleptonCollection> allLeptonIsElectron(Reflex::Type::ByName("BNlepton"), &(ptrToSelectedCollections->tightLoosePreselectedLeptonCollection), "isElectron", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonIsElectron);

  GenericCollectionMember<int, BNleptonCollection> allLeptonTkCharge(Reflex::Type::ByName("BNlepton"), &(ptrToSelectedCollections->tightLoosePreselectedLeptonCollection), "tkCharge", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonTkCharge);

  GenericCollectionMember<double, BNleptonCollection> allLeptonD0(Reflex::Type::ByName("BNlepton"), &(ptrToSelectedCollections->tightLoosePreselectedLeptonCollection),  "correctedD0Vertex", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonD0);

  GenericCollectionMember<double, BNleptonCollection> allLeptonDZ(Reflex::Type::ByName("BNlepton"), &(ptrToSelectedCollections->tightLoosePreselectedLeptonCollection),  "correctedDZ", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonDZ);

  GenericCollectionMember<double, BNleptonCollection> allLeptonImpactParameter(Reflex::Type::ByName("BNlepton"), &(ptrToSelectedCollections->tightLoosePreselectedLeptonCollection),  "IP", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonImpactParameter);

  GenericCollectionMember<double, BNleptonCollection> allLeptonImpactParameterError(Reflex::Type::ByName("BNlepton"), &(ptrToSelectedCollections->tightLoosePreselectedLeptonCollection),  "IPError", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonImpactParameterError);  
  
  ////////// all muons //////////
  GenericCollectionMember<int, BNmuonCollection> allMuonPFmuon(Reflex::Type::ByName("BNmuon"), &(ptrToSelectedCollections->tightLoosePreselectedMuonCollection), "isPFMuon", "all_muons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allMuonPFmuon);
  
  GenericCollectionMember<int, BNmuonCollection> allMuonGlobalMuon(Reflex::Type::ByName("BNmuon"), &(ptrToSelectedCollections->tightLoosePreselectedMuonCollection),  "isGlobalMuon", "all_muons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allMuonGlobalMuon);

  GenericCollectionMember<int, BNmuonCollection> allMuonTrackerMuon(Reflex::Type::ByName("BNmuon"), &(ptrToSelectedCollections->tightLoosePreselectedMuonCollection),  "isTrackerMuon", "all_muons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allMuonTrackerMuon);

  ////////// tight muons //////////
  GenericCollectionMember<double, BNmuonCollection> tightMuonPt(Reflex::Type::ByName("BNmuon"), &(ptrToSelectedCollections->tightLoosePreselectedMuonCollection), "pt", "all_muons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&tightMuonPt);

  GenericCollectionMember<double, BNmuonCollection> tightMuonEta(Reflex::Type::ByName("BNmuon"), &(ptrToSelectedCollections->tightLoosePreselectedMuonCollection), "eta", "all_muons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&tightMuonEta);

  ////////// tight electrons //////////
  GenericCollectionMember<double, BNelectronCollection> tightElectronEta(Reflex::Type::ByName("BNelectron"), &(ptrToSelectedCollections->tightElectronCollection), "eta", "tight_electrons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&tightElectronEta);

  GenericCollectionMember<double, BNelectronCollection> tightElectronPt(Reflex::Type::ByName("BNelectron"), &(ptrToSelectedCollections->tightElectronCollection), "pt", "tight_electrons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&tightElectronPt);  

  ////////// all jets //////////
  GenericCollectionMember<double, BNjetCollection> allJetPt(Reflex::Type::ByName("BNjet"), &(ptrToSelectedCollections->jetCollection), "pt", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetPt);

  GenericCollectionMember<double, BNjetCollection> allJetEta(Reflex::Type::ByName("BNjet"), &(ptrToSelectedCollections->jetCollection), "eta", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetEta);

  GenericCollectionMember<double, BNjetCollection> allJetCSV(Reflex::Type::ByName("BNjet"),  &(ptrToSelectedCollections->jetCollection), "btagCombinedSecVertex", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetCSV);

  ////////// met ////////// 
  GenericCollectionMember<double, BNmetCollection> metPt(Reflex::Type::ByName("BNmet"),  &(ptrToSelectedCollections->metCollection), "pt", "met",  KinematicVariableConstants::FLOAT_INIT, 1);
  kinVars.push_back(&metPt);

  ////////// event info ////////// 
  GenericCollectionMember<unsigned, BNeventCollection> runNumber(Reflex::Type::ByName("BNevent"), &(ptrToSelectedCollections->eventCollection), "run", "eventInfo",  KinematicVariableConstants::UINT_INIT, 1);
  kinVars.push_back(&runNumber);

  GenericCollectionMember<unsigned, BNeventCollection> lumiBlock(Reflex::Type::ByName("BNevent"), &(ptrToSelectedCollections->eventCollection), "lumi", "eventInfo",  KinematicVariableConstants::UINT_INIT, 1);
  kinVars.push_back(&lumiBlock);

  // this is a long inside BNevent
  // just using keyword long won't work
  // needs to be Long64_t 
  GenericEventCollectionMember<Long64_t, BNeventCollection> eventNumber(Reflex::Type::ByName("BNevent"),  "evt", "eventInfo",  KinematicVariableConstants::INT_INIT, 1);
  kinVars.push_back(&eventNumber);
  // hook up the variables

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
    
    BEANFileInterface * rawCollections = lepHelper.initializeInputCollections(ev, true);

    // make a shallow copy
    // update pointer as you make new collections
    BEANFileInterface selectedCollections = (*rawCollections);



    /////////////////////////////////////////////////////////////
    //
    //    Apply object ids
    //   
    //
    //////////////////////////////////////////////////////////////


    //------------    Jets
    if (debug > 9) cout << "Getting jets "  << endl;
	lepHelper.getTightCorrectedJets(25.0, 2.4, jetID::jetLoose, &selectedCollections);

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
    
    *ptrToSelectedCollections = selectedCollections;

    // reset all the vars
    if (debug > 9) cout << "Resetting "  << endl;
    for (vector<ArbitraryVariable*>::iterator iVar = kinVars.begin();
         iVar != kinVars.end();
         iVar++) {
      
      (*iVar)->reset();
      (*iVar)->assignCollections(&selectedCollections);
      
    }

    TwoMuon = 0;
    TwoElectron = 0;
    MuonElectron = 0;

    // There are several ways to define a selection
    // One way is with a kinematic varaible,
    // Another way is with a function that is a cut
        
    bool passAllCuts = true;

    if (debug > 9) cout << "Checking cuts "  << endl;
    
    for (vector<ArbitraryVariable*>::iterator iCut = cutVars.begin();
         iCut != cutVars.end();
         iCut++ ) {

      (*iCut)->evaluate();
      passAllCuts = passAllCuts && (*iCut)->passCut();

    }

    // do the lepton cut
    //passAllCuts = passAllCuts &&  LeptonCutThisAnalysis(&selectedCollections);
    
    
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
