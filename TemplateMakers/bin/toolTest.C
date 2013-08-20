
#include "ttH-Multileptons/TemplateMakers/interface/BEANFileInterface.h"
#include "ttH-Multileptons/TemplateMakers/interface/HelperLeptonCore.h"


///-------------- Kinematic Variables ------------------
#include "ttH-Multileptons/TemplateMakers/interface/KinematicVariable.h"
#include "ttH-Multileptons/TemplateMakers/interface/AllJetPt.h"
#include "ttH-Multileptons/TemplateMakers/interface/NumJets.h"

#include "BEAN/BEANmaker/interface/BtagWeight.h"
#include "BEAN/BEANmaker/interface/BEANhelper.h"




int main () {

   // load framework libraries
   gSystem->Load( "libFWCoreFWLite" );
   //gSystem->Load("libNtupleMakerBEANmaker.so");
   AutoLibraryLoader::enable();


  TFile * outputFile = new TFile ("ntuple_toolTest.root", "RECREATE");

  outputFile->cd();

  TTree * summaryTree = new TTree("summaryTree", "Summary Event Values");


  vector<string> fileNames;
  fileNames.push_back("file:/hadoop/users/awoodard/2012_53x_BEAN_GTV7G_skims/TTH_Inclusive_M-125_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1_skimDilep_BEAN_GTV7G_V01_CV04/d821efbc3befd142036a29052ef27c00/output_10_2_3LV.root");
  fwlite::ChainEvent ev(fileNames);


  // declare your kinematic variables that you want
  // to be written out into the tree
  vector<KinematicVariable*> kinVars;
  vector<KinematicVariable*> cutVars;
  
  AllJetPt myJetPt(4); // parameter is max num jet pts to save
  kinVars.push_back(&myJetPt);

  NumJets myNjets;
  myNjets.setCut(2); // parameter is keep events with jets  >= num
  kinVars.push_back(&myNjets); //save it in the tree
  cutVars.push_back(&myNjets); //also cut on it

  
  
  

  // declare some cut variables
  // you might want to write them out
  
  

  HelperLeptonCore lepHelper;

  // declare your helper
  // it comes from the lepHelper
  BEANhelper * beanHelper = lepHelper.setupAnalysisParameters("2012_53x", "ttH125");
  
  // hook up the variables

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
    
	lepHelper.getTightCorrectedJets(30.0, 2.4, jetID::jetLoose, &eventCollections);


    //------------  Electrons

    lepHelper.getTightAndLooseElectrons(electronID::electronTight, electronID::electronLoose, &eventCollections);
    
    //-----------    Muons

    lepHelper.getTightAndLooseMuons(muonID::muonTight, muonID::muonLoose, &eventCollections);


    //----------    MET
    lepHelper.getCorrectedMet(&eventCollections);
    

    // reset all the vars

    for (vector<KinematicVariable*>::iterator iVar = kinVars.begin();
         iVar != kinVars.end();
         iVar++) {
      
      (*iVar)->reset();
      (*iVar)->assignCollections(&eventCollections);
      
    }


    // In principle, you could apply different selections here
    bool passAllCuts = true;
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
    
    for (vector<KinematicVariable*>::iterator iVar = kinVars.begin();
         iVar != kinVars.end();
         iVar++) {
      
      (*iVar)->evaluate();
      
    }


    
    summaryTree->Fill();

  }// end for each event
  

  cout << "Num Events processed " << numEvents << endl
       << "Passed cuts " << numEventsPassCuts << endl
       << "Failed cuts " << numEventsFailCuts << endl ;


  outputFile->Write();
  outputFile->Close();
  

}
