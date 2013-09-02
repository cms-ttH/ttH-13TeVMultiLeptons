
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

  unsigned numTightMuons = inputCollections->muonCollection->size();
  unsigned numLooseMuons = inputCollections->looseMuonCollection->size();
  unsigned numTightElectrons = inputCollections->eleCollection->size();
  unsigned numLooseElectrons = inputCollections->looseEleCollection->size();

  bool passTwoLepton = false;

  // two tight leptons
  // we will cut on loose muons later
  if (numTightMuons ==2 || numTightElectrons==2 || (numTightMuons==1 && numTightElectrons==1))
      passTwoLepton = true;

  return passTwoLepton;

}

void LeptonVarsThisAnalysis(BEANFileInterface * inputCollections, bool passTwoLepton, int & TwoMuon, int & TwoEle, int & MuonEle) {

  unsigned numTightMuons = inputCollections->muonCollection->size();
  unsigned numLooseMuons = inputCollections->looseMuonCollection->size();
  unsigned numTightElectrons = inputCollections->eleCollection->size();
  unsigned numLooseElectrons = inputCollections->looseEleCollection->size();

  TwoMuon = 0;
  TwoEle = 0;
  MuonEle = 0;
  
  if (!passTwoLepton){
    return;
  }

  if (numTightMuons == 2 ) {
    TwoMuon = 1;
    return;
  }

  if (numTightElectrons ==2 ) {
    TwoEle = 1;
    return;
  }

  if ( numTightElectrons ==1 && numTightMuons==1 ) {
    MuonEle =1;
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

  myConfig.outputFileName = "ntuple_ssTwoLep.root";
  myConfig.sampleName = "ttH125";
  myConfig.maxEvents = 1000;

  loadTTH125Files(myConfig.inputFileNames);
  
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
  muonID::muonID muonLooseID = muonID::muonSide;
  electronID::electronID eleTightID = electronID::electronSideTightMVA;
  electronID::electronID eleLooseID = electronID::electronSide;
  
  // declare your kinematic variables that you want
  // to be written out into the tree
  vector<ArbitraryVariable*> kinVars;
  vector<ArbitraryVariable*> cutVars;

   // This is a hack, so that we can specify which collection to use before it is initialized inside the
   // event loop. After initialization, ptrToSelectedCollections is set to point at selectedCollections.
   BEANFileInterface * ptrToSelectedCollections = new BEANFileInterface;
   
   GenericCollectionSizeVariable<BNjetCollection> numJets(&(ptrToSelectedCollections->jetCollection), "numJets");
   kinVars.push_back(&numJets);
   numJets.setCut(4);
   cutVars.push_back(&numJets); 

   GenericCollectionSizeVariable<BNleptonCollection> numLeptons(&(ptrToSelectedCollections->mergedLeptonCollection), "numLeptons");
   kinVars.push_back(&numLeptons);

   GenericCollectionSizeVariable<BNmuonCollection> numMuons(&(ptrToSelectedCollections->muonCollection), "numMuons");
   kinVars.push_back(&numMuons);

   GenericCollectionSizeVariable<BNelectronCollection> numElectrons(&(ptrToSelectedCollections->eleCollection), "numElectrons");
   kinVars.push_back(&numElectrons);

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

   // do these definitions work?
   // yes, it it tight and everything else is loose
   LeptonScaleFactors myLepSF(&lepHelper, muonTightID, muonLooseID, eleTightID, eleLooseID);
   kinVars.push_back(&myLepSF);

   LeptonTriggerScaleFactors myLepTrig( &lepHelper);
   kinVars.push_back(&myLepTrig);

   CleanEventVars myClean (&lepHelper);
   kinVars.push_back(&myClean);

   CheckTwoLepTrigger checkTrig (&lepHelper);
   kinVars.push_back(&checkTrig);

   MassLepLep mll;
   kinVars.push_back(&mll);

   LepMVAs myLepMVAs(&lepHelper, 5);
   kinVars.push_back(&myLepMVAs);

   MHT myMHT;
   kinVars.push_back(&myMHT);

//    LepTrackCharges myLepTrackCharges(2);
//    kinVars.push_back(&myLepTrackCharges);
//    myLepTrackCharges.setCut("SS");
//    cutVars.push_back(&myLepTrackCharges);

   CERNTightCharges myCERNTightCharges(&(ptrToSelectedCollections->mergedLeptonCollection), "CERN_tight_charge", "preselected_leptons_by_pt", 2);
   kinVars.push_back(&myCERNTightCharges);
   myCERNTightCharges.setCut("pass");

   int TwoMuon = 0;
   int TwoEle = 0;
   int MuonEle = 0;
   int numLooseBJets = 0;
   int numMediumBJets = 0;

   summaryTree->Branch("TwoMuon", &TwoMuon);
   summaryTree->Branch("TwoEle", &TwoEle);
   summaryTree->Branch("MuonEle", &MuonEle);
   summaryTree->Branch("numLooseBJets", &numLooseBJets);
   summaryTree->Branch("numMediumBJets", &numMediumBJets);

  GenericCollectionMember<double, BNleptonCollection> allLeptonPt(Reflex::Type::ByName("BNlepton"), &(ptrToSelectedCollections->mergedLeptonCollection), "pt", "preselected_lepton_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonPt);

  GenericCollectionMember<double, BNleptonCollection> allLeptonEta(Reflex::Type::ByName("BNlepton"), &(ptrToSelectedCollections->mergedLeptonCollection), "eta", "preselected_lepton_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonEta);

  GenericCollectionMember<int, BNleptonCollection> allLeptonIsMuon(Reflex::Type::ByName("BNlepton"), &(ptrToSelectedCollections->mergedLeptonCollection), "isMuon", "preselected_lepton_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonIsMuon);

  GenericCollectionMember<int, BNleptonCollection> allLeptonIsElectron(Reflex::Type::ByName("BNlepton"), &(ptrToSelectedCollections->mergedLeptonCollection), "isElectron", "preselected_lepton_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonIsElectron);

  GenericCollectionMember<int, BNleptonCollection> allLeptonTkCharge(Reflex::Type::ByName("BNlepton"), &(ptrToSelectedCollections->mergedLeptonCollection), "tkCharge", "preselected_lepton_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonTkCharge);         

  GenericCollectionMember<double, BNmuonCollection> allMuonPt(Reflex::Type::ByName("BNmuon"), &(ptrToSelectedCollections->muonCollection), "pt", "muon_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allMuonPt);

  GenericCollectionMember<double, BNmuonCollection> allMuonEta(Reflex::Type::ByName("BNmuon"), &(ptrToSelectedCollections->muonCollection), "eta", "muon_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allMuonEta);

  GenericCollectionMember<double, BNelectronCollection> allElectronEta(Reflex::Type::ByName("BNelectron"), &(ptrToSelectedCollections->eleCollection), "eta", "electron_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allElectronEta);

  GenericCollectionMember<double, BNelectronCollection> allElectronPt(Reflex::Type::ByName("BNelectron"), &(ptrToSelectedCollections->eleCollection), "pt", "electron_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allElectronPt);  

  GenericCollectionMember<double, BNjetCollection> allJetPt(Reflex::Type::ByName("BNjet"), &(ptrToSelectedCollections->jetCollection), "pt", "jet_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetPt);

  GenericCollectionMember<double, BNjetCollection> allJetEta(Reflex::Type::ByName("BNjet"), &(ptrToSelectedCollections->jetCollection), "eta", "jet_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetEta);

  GenericCollectionMember<double, BNjetCollection> allJetCSV(Reflex::Type::ByName("BNjet"),  &(ptrToSelectedCollections->jetCollection), "btagCombinedSecVertex", "jet_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetCSV);

  GenericCollectionMember<unsigned, BNeventCollection> runNumber(Reflex::Type::ByName("BNevent"), &(ptrToSelectedCollections->eventCollection), "run", "eventInfo",  KinematicVariableConstants::UINT_INIT, 1);
  kinVars.push_back(&runNumber);

  GenericCollectionMember<unsigned, BNeventCollection> lumiBlock(Reflex::Type::ByName("BNevent"), &(ptrToSelectedCollections->eventCollection), "lumi", "eventInfo",  KinematicVariableConstants::UINT_INIT, 1);
  kinVars.push_back(&lumiBlock);

  //MET
  GenericCollectionMember<double, BNmetCollection> metPt(Reflex::Type::ByName("BNmet"),  &(ptrToSelectedCollections->metCollection), "pt", "met",  KinematicVariableConstants::FLOAT_INIT, 1);
  kinVars.push_back(&metPt);

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
	lepHelper.getTightCorrectedJets(25.0, 4.7, jetID::jetLoose, &selectedCollections);

    if (debug > 9) cout << "Getting loose CSV jets"  << endl;
	selectedCollections.jetCollectionLooseCSV = lepHelper.getCorrectedSelectedJets(25.0, 4.7, jetID::jetLoose, 'L');
    numLooseBJets = int((selectedCollections.jetCollectionLooseCSV)->size());
    
    if (debug > 9) cout << "Getting medium CSV jets"  << endl;
	selectedCollections.jetCollectionMediumCSV = lepHelper.getCorrectedSelectedJets(25.0, 4.7, jetID::jetLoose, 'M');
    numMediumBJets = int((selectedCollections.jetCollectionMediumCSV)->size());

    //------------  Electrons
    if (debug > 9) cout << "Getting electrons "  << endl;
    lepHelper.getTightAndLooseElectrons(eleTightID, eleLooseID, &selectedCollections);
    
    //-----------    Muons
    if (debug > 9) cout << "Getting muons "  << endl;
    lepHelper.getTightAndLooseMuons(muonTightID, muonLooseID, &selectedCollections);

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
    TwoEle = 0;
    MuonEle = 0;

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

    LeptonVarsThisAnalysis(&selectedCollections, LeptonCutThisAnalysis(&selectedCollections), TwoMuon, TwoEle, MuonEle);

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
