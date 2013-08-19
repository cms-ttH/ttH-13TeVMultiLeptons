
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


  // declare your kinematic variables
  vector<KinematicVariable*> kinVars;
  
  AllJetPt myJetPt(4);
  kinVars.push_back(&myJetPt);

  NumJets myNjets;
  kinVars.push_back(&myNjets);


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
  for (ev.toBegin(); !ev.atEnd(); ++ev){

    BEANFileInterface * rawCollections = lepHelper.initializeInputCollections(ev, false);


    BNjetCollection selectedJets_unsorted  = beanHelper->GetSelectedJets( *(rawCollections->jetCollection), 30., 2.4, jetID::jetLoose, '-' ); 
	BNjetCollection selectedJets       = beanHelper->GetSortedByPt( selectedJets_unsorted );
    

    // Shallow copy
    BEANFileInterface eventCollections = (*rawCollections);

    // replace raw objects with selected ones
    eventCollections.jetCollection = &selectedJets;
    

    // reset all the vars

    for (vector<KinematicVariable*>::iterator iVar = kinVars.begin();
         iVar != kinVars.end();
         iVar++) {
      
      (*iVar)->reset();
      (*iVar)->assignCollections(&eventCollections);
      
    }


    // In principle, you could apply different selections here
    
    // Now  evaluate the vars
    
    for (vector<KinematicVariable*>::iterator iVar = kinVars.begin();
         iVar != kinVars.end();
         iVar++) {
      
      (*iVar)->evaluate();
      
    }

    numEvents++;
    
    summaryTree->Fill();

  }// end for each event
  

  cout << "Num Events processed " << numEvents << endl;


  outputFile->Write();
  outputFile->Close();
  

}
