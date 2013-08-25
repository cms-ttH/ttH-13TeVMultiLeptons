
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BEANFileInterface.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/HelperLeptonCore.h"


///-------------- Kinematic Variables ------------------
#include "ttHMultileptonAnalysis/TemplateMakers/interface/EveryVariable.h"

#include "BEAN/BEANmaker/interface/BtagWeight.h"
#include "BEAN/BEANmaker/interface/BEANhelper.h"

#include "Reflex/Object.h"
#include "Reflex/Type.h"
#include "Reflex/Member.h"
#include "Reflex/Kernel.h"




bool LeptonCutThisAnalysis (BEANFileInterface * inputCollections ) {

  unsigned numTightMuons = inputCollections->muonCollection->size();
  unsigned numLooseMuons = inputCollections->looseMuonCollection->size();
  unsigned numTightElectrons = inputCollections->eleCollection->size();
  unsigned numLooseElectrons = inputCollections->looseEleCollection->size();

  bool passTwoLepton = false;
  
  if ( (numTightMuons + numLooseMuons + numTightElectrons + numLooseElectrons) ==2
       && (numTightMuons + numTightElectrons) > 0)
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

  if (numTightMuons == 2 || (numTightMuons==1 && numLooseMuons==1)) {
    TwoMuon = 1;
    return;
  }

  if (numTightElectrons ==2 || (numTightElectrons==1 && numLooseElectrons==1)) {
    TwoEle = 1;
    return;
  }

  if ( (numTightElectrons ==1 && numTightMuons==1)
       || (numTightElectrons ==1 && numLooseMuons ==1)
       || (numTightMuons == 1 && numLooseElectrons ==1) ) {
    MuonEle =1;
    return;
    
  }
  
}



int main () {

  // load framework libraries
  gSystem->Load( "libFWCoreFWLite" );
  //gSystem->Load("libNtupleMakerBEANmaker.so");
  AutoLibraryLoader::enable();
  
  int debug = 10; // levels of debug
  
  TFile * outputFile = new TFile ("ntuple_toolTest.root", "RECREATE");

  outputFile->cd();

  TTree * summaryTree = new TTree("summaryTree", "Summary Event Values");


  vector<string> fileNames;
  //                   file:/hadoop/users/awoodard/2012_53x_BEAN_GTV7G_skims/TTH_Inclusive_M-125_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1_skimDilep_BEAN_GTV7G_V01_CV04/d821efbc3befd142036a29052ef27c00/output_10_2_3LV.root
  fileNames.push_back("file:/hadoop/users/awoodard/2012_53x_BEAN_GTV7G_skims/TTH_Inclusive_M-125_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1_skimDilep_BEAN_GTV7G_V01_CV04/d821efbc3befd142036a29052ef27c00/output_10_2_3LV.root");
  fwlite::ChainEvent ev(fileNames);


  
  HelperLeptonCore lepHelper;

  // declare your helper
  // it comes from the lepHelper
  BEANhelper * beanHelper = lepHelper.setupAnalysisParameters("2012_53x", "ttH125");

  // ---------------------------------------------
  // Note for future development: should these be
  // saved inside the lepHelper somewhere?
  // ---------------------------------------------
  
  muonID::muonID muonTightID = muonID::muonTight;
  muonID::muonID muonLooseID = muonID::muonLoose;
  electronID::electronID eleTightID = electronID::electronTight;
  electronID::electronID eleLooseID = electronID::electronLoose;
  

  
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


   CSVWeights myCSV(&lepHelper);
   kinVars.push_back(&myCSV);

   PUWeights myPU(&lepHelper);
   kinVars.push_back(&myPU);

   TopPtWeights myTopPt(&lepHelper);
   kinVars.push_back(&myTopPt);

   XsecWeight myXsec (&lepHelper);
   kinVars.push_back(&myXsec);


   LeptonScaleFactors myLepSF(&lepHelper, muonTightID, muonLooseID, eleTightID, eleLooseID);
   kinVars.push_back(&myLepSF);

   LeptonTriggerScaleFactors myLepTrig( &lepHelper);
   kinVars.push_back(&myLepTrig);
   

   int TwoMuon = 0;
   int TwoEle = 0;
   int MuonEle = 0;


   summaryTree->Branch("TwoMuon", &TwoMuon);
   summaryTree->Branch("TwoEle", &TwoEle);
   summaryTree->Branch("MuonEle", &MuonEle);

  

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
  
  for (ev.toBegin(); !ev.atEnd(); ++ev){
    numEvents++;
    if (debug > 9) cout << "---------->>>>>> Event " << numEvents << endl;
    
    BEANFileInterface * rawCollections = lepHelper.initializeInputCollections(ev, false);

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
	lepHelper.getTightCorrectedJets(30.0, 2.4, jetID::jetLoose, &selectedCollections);


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
