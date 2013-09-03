
#ifndef _HelperLeptonCore_h
#define _HelperLeptonCore_h


#include "TFile.h"
#include "TChain.h"
#include "TH1.h"
#include "TH3.h"
#include "TH2F.h"
#include "TF1.h"
#include "TF2.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TPaveStats.h"
#include "TAxis.h"
#include "TMath.h"
#include "TRandom3.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <exception>
#include <cmath>
#include <random>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include "TGraphAsymmErrors.h"
#include "TLorentzVector.h"
//Root includes
#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
#include "FWCore/FWLite/interface/AutoLibraryLoader.h"

//#include "LumiReweightingStandAlone.h"
//#include "PUConstants.h"

#if !defined(__CINT__) && !defined(__MAKECINT__)

#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/FWLite/interface/ChainEvent.h"

//Headers for the data items
#include "BEAN/Collections/interface/BNelectron.h"
#include "BEAN/Collections/interface/BNevent.h"
#include "BEAN/Collections/interface/BNjet.h"
#include "BEAN/Collections/interface/BNmcparticle.h"
#include "BEAN/Collections/interface/BNmet.h"
#include "BEAN/Collections/interface/BNmuon.h"
#include "BEAN/Collections/interface/BNphoton.h"
#include "BEAN/Collections/interface/BNsupercluster.h"
#include "BEAN/Collections/interface/BNtrack.h"
#include "BEAN/Collections/interface/BNtrigger.h"
#include "BEAN/Collections/interface/BNskimbits.h"
#include "BEAN/Collections/interface/BNtrigobj.h"
#include "BEAN/Collections/interface/BNprimaryvertex.h"


// headers for python config processing

//#include "FWCore/PythonParameterSet/interface/PythonProcessDesc.h"
//#include "FWCore/ParameterSet/interface/ProcessDesc.h"
//#include "FWCore/ParameterSet/interface/FileInPath.h"

#include "BEAN/BEANmaker/interface/BtagWeight.h"
#include "BEAN/BEANmaker/interface/BEANhelper.h"

#include "BEAN/BEANmaker/interface/AnglesUtil.h"
#include "PhysicsTools/Utilities/interface/LumiReweightingStandAlone.h"
// For MVA reprocessing
//#include "TMVAGui.C"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"


#endif

#include "ttHMultileptonAnalysis/TemplateMakers/interface/BEANFileInterface.h"


// HelperLeptonCore
// This is also a TTreeWapper, but we keep the definitions
// separate so that things are easier to read and separable for
// other situations


class HelperLeptonCore  {

public:
  
  // constructor
  HelperLeptonCore ();

  // initialize

  BEANhelper *  setupAnalysisParameters (string year, string sampleName) ;


  // detect data by sampleName

  bool detectData (string sampleName);
  
  // convert sample name to sample number

  int convertSampleNameToNumber (string sampleName);

  
  // setup some PU reweighting flags
  void initializePUReweighting ();


  // initializeTrigger
  // this may already be in beanhelper
  void initializeTrigger ();

  // setup several  BN pointers
  BEANFileInterface * initializeInputCollections (fwlite::ChainEvent & ev, bool isLepMVA);

  // do some MC calculations
  void initializeGenInfo ();

  // get corrected MET
  void initializeMet ();

  // determine true and reco pvs for PU reweight
  void countNumPVs ();
  
  // check to see if trigger passed
  bool isTriggerPassed();

  // check to see if cleaning is ok
  bool checkEventCleaning();

  bool parseSysTypes();
  

  // Handle the gymnastics of tight and loose collection definitions
  void getTightLoosePreselectedElectrons (electronID::electronID tightID,
                                  electronID::electronID looseID,
                                  electronID::electronID preselectedID,
                                  BEANFileInterface* selectedCollections);
  
    // Handle the gymnastics of tight and loose collection definitions
  void getTightLoosePreselectedMuons (muonID::muonID tightID,
                              muonID::muonID looseID,
                              muonID::muonID preselectedID,
                              BEANFileInterface* selectedCollections);

  void getTightCorrectedJets (double ptCut,
                              double etaCut,
                              jetID::jetID tightID,
                              BEANFileInterface * selectedCollections);
    
  BNjetCollection * getCorrectedSelectedJets (double ptCut,
                                              double etaCut,
                                              jetID::jetID jetID,
                                              const char csvWorkingPoint);
                                 
  void getCorrectedMet (BEANFileInterface * selectedCollections,
                        sysType::sysType shift = sysType::NA);

  void fillLepCollectionWithSelectedLeptons ( BEANFileInterface * selectedCollections);

  //void checkCollections ();
  
  // fill in everything you have
  //void fillOutputBranches ();





  //-------------------- Variables

  std::string analysisYear;

  
  double weight_Xsec;
  int nGen;
  float Xsec;
  int sampleNumber;
  string sampleName;

  bool isData;

  string sysType_lep;
  sysType::sysType jetEnergyShift;
  sysType::sysType csvShift;
  

  BEANhelper bHelp;
  BEANFileInterface rawCollections;

  bool verbose;

  std::string listOfCollisionDatasets;
  std::string datasetForBEANHelper;

  //branches
  fwlite::Handle<BNeventCollection> h_event;
  BNeventCollection events;

  fwlite::Handle<BNmuonCollection> h_muons;
  BNmuonCollection muonsRaw;
  BNmuonCollection muonsTight;
  BNmuonCollection muonsLoose;
  BNmuonCollection muonsPreselected;
  BNmuonCollection muonsTightLoose;
  BNmuonCollection muonsLoosePreselected;
  BNmuonCollection muonsTightLoosePreselected;
  

  fwlite::Handle<BNmcparticleCollection> h_mcparticles;
  BNmcparticleCollection mcparticles;


  fwlite::Handle<BNjetCollection> h_pfjets;
  BNjetCollection pfjets;
  BNjetCollection jetsTight;

  fwlite::Handle<BNmetCollection> h_pfmets;
  BNmetCollection pfmets;
  BNmetCollection metCorrected;

  fwlite::Handle<BNtriggerCollection> h_hlt;
  BNtriggerCollection hltInfo;

  fwlite::Handle<BNprimaryvertexCollection> h_pvs;
  BNprimaryvertexCollection pvs;

  fwlite::Handle<BNelectronCollection> h_electrons;
  BNelectronCollection electronsRaw;
  BNelectronCollection electronsTight;
  BNelectronCollection electronsLoose;
  BNelectronCollection electronsPreselected;
  BNelectronCollection electronsTightLoose;
  BNelectronCollection electronsLoosePreselected;
  BNelectronCollection electronsTightLoosePreselected;
  

  BNleptonCollection leptonsRaw;
  BNleptonCollection leptonsTight;
  BNleptonCollection leptonsLoose;
  BNleptonCollection leptonsPreselected;
  BNleptonCollection leptonsTightLoose;
  BNleptonCollection leptonsLoosePreselected;
  BNleptonCollection leptonsTightLoosePreselected;


  fwlite::Handle<BNjetCollection> h_lepMvaJets;
  BNjetCollection lepMvaJets;
  
  
};


#endif // _HelperLeptonCore_h
