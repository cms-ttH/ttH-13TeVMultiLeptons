
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


  // declare your kinematic variables that you want
  // to be written out into the tree
  vector<KinematicVariable*> kinVars;
  vector<KinematicVariable*> cutVars;

  RunLumiEvent myEvent;
  kinVars.push_back(&myEvent);
  
  AllJetPt myJetPt(4); // parameter is max num jet pts to save
  kinVars.push_back(&myJetPt);

  NumJets myNjets;
  myNjets.setCut(2); // parameter is keep events with jets  >= num
  kinVars.push_back(&myNjets); //save it in the tree
  cutVars.push_back(&myNjets); //also cut on it


  NumTightLooseMuons myNmuons;
  myNmuons.setCutOnSumTightLoose(1, 2); // at least one tight, at most two total t+l
  kinVars.push_back(&myNmuons);
  cutVars.push_back(&myNmuons); // use this to make a small ntuple


  BNmuon targetMuon;
  
  GenericObjectMember<double> muonPt(Reflex::Type::ByName("BNmuon"),  &targetMuon, "pt", "muon_1",  KinematicVariableConstants::FLOAT_INIT);
  GenericObjectMember<double> muonEta(Reflex::Type::ByName("BNmuon"),  &targetMuon, "eta", "muon_1",  KinematicVariableConstants::FLOAT_INIT);
  GenericObjectMember<double> muonPhi(Reflex::Type::ByName("BNmuon"),  &targetMuon, "phi", "muon_1",  KinematicVariableConstants::FLOAT_INIT);
  
  kinVars.push_back(&muonPt);
  

  HelperLeptonCore lepHelper;

  // declare your helper
  // it comes from the lepHelper
  BEANhelper * beanHelper = lepHelper.setupAnalysisParameters("2012_53x", "ttH125");
  
  // hook up the variables

  if (debug > 9) { cout << "Hooking variables to tree" << endl;}
  for (vector<KinematicVariable*>::iterator iVar = kinVars.begin();
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
    BEANFileInterface eventCollections = (*rawCollections);



    /////////////////////////////////////////////////////////////
    //
    //    Apply object ids
    //   
    //
    //////////////////////////////////////////////////////////////


    //------------    Jets
    if (debug > 9) cout << "Getting jets "  << endl;
	lepHelper.getTightCorrectedJets(30.0, 2.4, jetID::jetLoose, &eventCollections);


    //------------  Electrons
    if (debug > 9) cout << "Getting electrons "  << endl;
    lepHelper.getTightAndLooseElectrons(electronID::electronTight, electronID::electronLoose, &eventCollections);
    
    //-----------    Muons
    if (debug > 9) cout << "Getting muons "  << endl;
    lepHelper.getTightAndLooseMuons(muonID::muonTight, muonID::muonLoose, &eventCollections);


    //----------    MET
    if (debug > 9) cout << "Getting met "  << endl;
    lepHelper.getCorrectedMet(&eventCollections);
    

    // reset all the vars
    if (debug > 9) cout << "Resetting "  << endl;
    for (vector<KinematicVariable*>::iterator iVar = kinVars.begin();
         iVar != kinVars.end();
         iVar++) {
      
      (*iVar)->reset();
      (*iVar)->assignCollections(&eventCollections);
      
    }

    // rest targetMuon
    targetMuon = BNmuon();

    if (eventCollections.muonCollection->size() >0){

      targetMuon = eventCollections.muonCollection->at(0);

    }

    // In principle, you could apply different selections here
    bool passAllCuts = true;

    if (debug > 9) cout << "Checking cuts "  << endl;
    
    for (vector<KinematicVariable*>::iterator iCut = cutVars.begin();
         iCut != cutVars.end();
         iCut++ ) {

      (*iCut)->evaluate();
      passAllCuts = passAllCuts && (*iCut)->passCut();

    }

    if (!passAllCuts) {
      numEventsFailCuts++;
      continue;
    } else {
      numEventsPassCuts++;
    }
    
    
    // Now  evaluate the vars
    if (debug > 9) cout << "Evaluating vars "  << endl;

    
    for (vector<KinematicVariable*>::iterator iVar = kinVars.begin();
         iVar != kinVars.end();
         iVar++) {
      
      (*iVar)->evaluate();
      
    }


    if (debug > 9) {
      for (vector<KinematicVariable*>::iterator iVar = kinVars.begin();
           iVar != kinVars.end();
           iVar++) {
        
        (*iVar)->print();
        cout << endl;
        
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
