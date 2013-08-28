
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




bool LeptonCutThisAnalysis (BEANFileInterface * inputCollections ) {

  unsigned numTightMuons = inputCollections->muonCollection->size();
  unsigned numLooseMuons = inputCollections->looseMuonCollection->size();
  unsigned numTightElectrons = inputCollections->eleCollection->size();
  unsigned numLooseElectrons = inputCollections->looseEleCollection->size();

  bool passLeptonCut = false;

  // three tight leptons
  // no loose leptons
  if ( (numTightMuons + numTightElectrons) == 4 )
    passLeptonCut = true;

  return passLeptonCut;

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

  myConfig.outputFileName = "ntuple_toolTest.root";
  myConfig.sampleName = "ttH125";
  myConfig.maxEvents = 4000;

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


  //vector<string> fileNames;
  //                   file:/hadoop/users/awoodard/2012_53x_BEAN_GTV7G_skims/TTH_Inclusive_M-125_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1_skimDilep_BEAN_GTV7G_V01_CV04/d821efbc3befd142036a29052ef27c00/output_10_2_3LV.root
  //fileNames.push_back("file:/hadoop/users/awoodard/2012_53x_BEAN_GTV7G_skims/TTH_Inclusive_M-125_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1_skimDilep_BEAN_GTV7G_V01_CV04/d821efbc3befd142036a29052ef27c00/output_10_2_3LV.root");


  
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

  // when the selections are the same, then everything should be tight not loose
  muonID::muonID muonTightID = muonID::muonSideLooseMVA;
  muonID::muonID muonLooseID = muonID::muonSideLooseMVA; 
  electronID::electronID eleTightID = electronID::electronSideLooseMVA;
  electronID::electronID eleLooseID = electronID::electronSideLooseMVA;
  

  
  // declare your kinematic variables that you want
  // to be written out into the tree
  vector<ArbitraryVariable*> kinVars;
  vector<ArbitraryVariable*> cutVars;

  

   NumJets myNjets;
   myNjets.setCut(2); // parameter is keep events with jets  >= num
   kinVars.push_back(&myNjets); //save it in the tree
   cutVars.push_back(&myNjets); //also cut on it

   NumLeptons myNlep;
   kinVars.push_back(&myNlep);

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

   
   


  

  GenericMuonCollectionMember<double, BNmuonCollection> allMuonPt(Reflex::Type::ByName("BNmuon"),  "pt", "muon_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allMuonPt);

  GenericMuonCollectionMember<double, BNmuonCollection> allMuonEta(Reflex::Type::ByName("BNmuon"),  "eta", "muon_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allMuonEta);

  GenericJetCollectionMember<double, BNjetCollection> allJetPt(Reflex::Type::ByName("BNjet"),  "pt", "jet_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetPt);

  GenericJetCollectionMember<double, BNjetCollection> allJetEta(Reflex::Type::ByName("BNjet"),  "eta", "jet_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetEta);

  GenericEventCollectionMember<unsigned, BNeventCollection> runNumber(Reflex::Type::ByName("BNevent"),  "run", "eventInfo",  KinematicVariableConstants::UINT_INIT, 1);
  kinVars.push_back(&runNumber);

  GenericEventCollectionMember<unsigned, BNeventCollection> lumiBlock(Reflex::Type::ByName("BNevent"),  "lumi", "eventInfo",  KinematicVariableConstants::UINT_INIT, 1);
  kinVars.push_back(&lumiBlock);

  // this is a long inside BNevent
  // just using keyword long won't work
  // needs to be Long64_t 
  GenericEventCollectionMember<Long64_t, BNeventCollection> eventNumber(Reflex::Type::ByName("BNevent"),  "evt", "eventInfo",  KinematicVariableConstants::INT_INIT, 1);
  kinVars.push_back(&eventNumber);
  // hook up the variables

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

    if (numEvents > myConfig.maxEvents) break;

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
    
    

    // reset all the vars
    if (debug > 9) cout << "Resetting "  << endl;
    for (vector<ArbitraryVariable*>::iterator iVar = kinVars.begin();
         iVar != kinVars.end();
         iVar++) {
      
      (*iVar)->reset();
      (*iVar)->assignCollections(&selectedCollections);
      
    }



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

    //LeptonVarsThisAnalysis(&selectedCollections, LeptonCutThisAnalysis(&selectedCollections), TwoMuon, TwoEle, MuonEle);

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
