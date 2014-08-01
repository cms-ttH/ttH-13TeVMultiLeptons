#include "ttHMultileptonAnalysis/TemplateMakers/interface/BEANFileInterface.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/HelperLeptonCore.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/GenericCollection.h"

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

void getNumExtraPartons(BEANhelper* beanHelper, BNmcparticleCollection& mcParticles, int& numExtraPartons) {

  numExtraPartons = beanHelper->GetNumExtraPartons(mcParticles);

  return;
}

void dibosonPlusHFKeepEventFunction(BEANhelper * beanHelper, BNmcparticleCollection& mcParticles,
                                    BNjetCollection& rawJets, bool & dibosonPlusHFKeepEventBool) {

  dibosonPlusHFKeepEventBool = beanHelper->dibosonPlusHFKeepEvent(mcParticles, rawJets);

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
  myConfig.jetSyst = inputs.getParameter < string > ("jetSyst");

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

  sysType::sysType jetSyst = sysType::NA;
  if (myConfig.jetSyst == "NA") jetSyst = sysType::NA;
  else if (myConfig.jetSyst == "JESUp") jetSyst = sysType::JESup;
  else if (myConfig.jetSyst == "JESDown") jetSyst = sysType::JESdown;
  else std::cout << "No valid JES corrections specified - using nominal" << std::endl;

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
  tauID::tauID tauTightID = tauID::tauMedium;
  tauID::tauID tauLooseID = tauID::tauLoose;
  tauID::tauID tauPreselectedID = tauID::tauNonIso;

  // Create selected collections
  GenericCollection<BNelectronCollection> tightElectrons(beanHelper);
  GenericCollection<BNelectronCollection> looseElectrons(beanHelper);
  GenericCollection<BNelectronCollection> preselectedElectrons(beanHelper);
  GenericCollection<BNelectronCollection> tightLooseElectrons(beanHelper);
  GenericCollection<BNelectronCollection> loosePreselectedElectrons(beanHelper);
  GenericCollection<BNelectronCollection> tightLoosePreselectedElectrons(beanHelper);

  GenericCollection<BNmuonCollection> tightMuons(beanHelper);
  GenericCollection<BNmuonCollection> looseMuons(beanHelper);
  GenericCollection<BNmuonCollection> preselectedMuons(beanHelper);
  GenericCollection<BNmuonCollection> tightLooseMuons(beanHelper);
  GenericCollection<BNmuonCollection> tightLoosePreselectedMuons(beanHelper);

  GenericCollection<BNleptonCollection> tightLeptons(beanHelper);
  GenericCollection<BNleptonCollection> tightLooseLeptons(beanHelper);
  GenericCollection<BNleptonCollection> tightLoosePreselectedLeptons(beanHelper);

  GenericCollection<BNleptonCollection> tightLoosePreselectedZLeptons(beanHelper);
  GenericCollection<BNleptonCollection> tightLoosePreselectedNonZLeptons(beanHelper);

  GenericCollection<BNtauCollection> tightTaus(beanHelper);
  GenericCollection<BNtauCollection> tightLooseTaus(beanHelper);
  GenericCollection<BNtauCollection> tightLoosePreselectedTaus(beanHelper);

  GenericCollection<BNjetCollection> jets(beanHelper);
  GenericCollection<BNjetCollection> jetsByCSV(beanHelper);
  GenericCollection<BNjetCollection> looseCSVJets(beanHelper);
  GenericCollection<BNjetCollection> mediumCSVJets(beanHelper);
  GenericCollection<BNjetCollection> tightCSVJets(beanHelper);
  GenericCollection<BNjetCollection> notLooseCSVJets(beanHelper);
  GenericCollection<BNjetCollection> jetsForLepMVA(beanHelper);
  
  GenericCollection<BNmetCollection> met(beanHelper);
  GenericCollection<BNprimaryvertexCollection> primaryVertexes(beanHelper);
  GenericCollection<BNtriggerCollection> hltCollection(beanHelper);
  GenericCollection<BNeventCollection> events(beanHelper);
  GenericCollection<BNmcparticleCollection> mcParticles(beanHelper);

  GenericCollection<BNmcparticleCollection> genWFromTops(beanHelper);
  GenericCollection<BNmcparticleCollection> genWFromAntiTops(beanHelper);

  GenericCollection<BNjetCollection> jetsFromW(beanHelper);
  GenericCollection<BNjetCollection> jetsFromLepTop(beanHelper);
  GenericCollection<BNjetCollection> jetsFromHadTop(beanHelper);
  GenericCollection<BNjetCollection> jetsFromTop(beanHelper);
  GenericCollection<BNjetCollection> jetsFromAntiTop(beanHelper);

  GenericCollection<BNleptonCollection> leptonsFromW(beanHelper);
  GenericCollection<BNleptonCollection> leptonsFromZ(beanHelper);
  GenericCollection<BNleptonCollection> leptonsFromTop(beanHelper);
  GenericCollection<BNleptonCollection> leptonsFromAntiTop(beanHelper);
  GenericCollection<BNleptonCollection> leptonsFromBFromTop(beanHelper);
  GenericCollection<BNleptonCollection> leptonsFromBFromAntiTop(beanHelper);
  GenericCollection<BNleptonCollection> leptonsFromNP(beanHelper);

  GenericCollection<BNleptonCollection> leptonsSS(beanHelper);
  GenericCollection<BNleptonCollection> leptonsOS(beanHelper);

  // declare your kinematic variables that you want
  // to be written out into the tree
  vector<ArbitraryVariable*> kinVars;
  vector<ArbitraryVariable*> cutVars;

  GenericCollectionSizeVariable<BNjetCollection> numJets(&(jets.ptrToItems), "numJets");
  kinVars.push_back(&numJets);
  numJets.setCutMin(2);
//   //cutvar for ttbar_lj or ttbar_ll
//   cutVars.push_back(&numJets);

  GenericCollectionSizeVariable<BNjetCollection> numLooseBJets(&(looseCSVJets.ptrToItems), "numLooseBJets");
  kinVars.push_back(&numLooseBJets);

  GenericCollectionSizeVariable<BNjetCollection> numMediumBJets(&(mediumCSVJets.ptrToItems), "numMediumBJets");
  kinVars.push_back(&numMediumBJets);

  GenericCollectionSizeVariable<BNjetCollection> numTightBJets(&(tightCSVJets.ptrToItems), "numTightBJets");
  kinVars.push_back(&numTightBJets);

  GenericCollectionSizeVariable<BNleptonCollection> numTightLeptons(&(tightLeptons.ptrToItems), "numTightLeptons");
  kinVars.push_back(&numTightLeptons);
//   //cutVar for ttbar_lj
//   numTightLeptons.setCutMin(1);
//   cutVars.push_back(&numTightLeptons);
//   //cutVar for ttbar_ll
//   numTightLeptons.setCutMin(2);
//   cutVars.push_back(&numTightLeptons);
  
  GenericCollectionSizeVariable<BNleptonCollection> numTightLooseLeptons(&(tightLooseLeptons.ptrToItems), "numTightLooseLeptons");
  kinVars.push_back(&numTightLooseLeptons);

  GenericCollectionSizeVariable<BNleptonCollection> numAllLeptons(&(tightLoosePreselectedLeptons.ptrToItems), "numAllLeptons");
  kinVars.push_back(&numAllLeptons);
  //comment out for ttbar_lj or ttbar_ll
  numAllLeptons.setCutMin(3);
  cutVars.push_back(&numAllLeptons);

  GenericCollectionSizeVariable<BNmuonCollection> numAllMuons(&(tightLoosePreselectedMuons.ptrToItems), "numAllMuons");
  kinVars.push_back(&numAllMuons);

  GenericCollectionSizeVariable<BNelectronCollection> numAllElectrons(&(tightLoosePreselectedElectrons.ptrToItems), "numAllElectrons");
  kinVars.push_back(&numAllElectrons);

  GenericCollectionSizeVariable<BNleptonCollection> numAllZLeptons(&(tightLoosePreselectedZLeptons.ptrToItems), "numAllZLeptons");
  kinVars.push_back(&numAllZLeptons);

  GenericCollectionSizeVariable<BNleptonCollection> numAllNonZLeptons(&(tightLoosePreselectedNonZLeptons.ptrToItems), "numAllNonZLeptons");
  kinVars.push_back(&numAllNonZLeptons);

  GenericCollectionSizeVariable<BNleptonCollection> numLeptonsSS(&(leptonsSS.ptrToItems), "numLeptonsSS");
  kinVars.push_back(&numLeptonsSS);

  GenericCollectionSizeVariable<BNleptonCollection> numLeptonsOS(&(leptonsOS.ptrToItems), "numLeptonsOS");
  kinVars.push_back(&numLeptonsOS);

  GenericCollectionSizeVariable<BNtauCollection> numAllTaus(&(tightLoosePreselectedTaus.ptrToItems), "numAllTaus");
  kinVars.push_back(&numAllTaus);

  GenericCollectionSizeVariable<BNtauCollection> numTightLooseTaus(&(tightLooseTaus.ptrToItems), "numTightLooseTaus");
  kinVars.push_back(&numTightLooseTaus);

  GenericCollectionSizeVariable<BNtauCollection> numTightTaus(&(tightTaus.ptrToItems), "numTightTaus");
  kinVars.push_back(&numTightTaus);

  //ttH hadrons reweighting
  CSVWeights myCSV(beanHelper, &(jets.ptrToItems), jetSyst);
  kinVars.push_back(&myCSV);

  //Btag POG reweighting
  vector<pair<string, double>> WPs = {make_pair("CSVT", 0.898), make_pair("CSVM", 0.679), make_pair("CSVL", 0.244)};
  BTagWeights myBTagWeights(WPs, &(jets.ptrToItems));
  kinVars.push_back(&myBTagWeights);

  PUWeights myPU(&lepHelper, &(events.ptrToItems));
  kinVars.push_back(&myPU);

  TopPtWeights myTopPt(&lepHelper, &(mcParticles.ptrToItems));
  kinVars.push_back(&myTopPt);

// // //Currently, gets ND loose lepton SF; could switch to tight and loose - AWB Feb 12, 2014
// //   LeptonIDAndIsoScaleFactors myLepIDAndIsoSF(&lepHelper, muonID::muonTight, muonID::muonLoose,
// //                                              electronID::electronTight, electronID::electronLoose,
// //                                              &(tightMuons.ptrToItems), &(looseMuons.ptrToItems),
// //                                              &(tightElectrons.ptrToItems), &(looseElectrons.ptrToItems));
//   LeptonIDAndIsoScaleFactors myLepIDAndIsoSF(&lepHelper, muonTightID, muonLooseID, electronTightID, electronLooseID,
//                                              &(tightMuons.ptrToItems), &(looseMuons.ptrToItems),
//                                              &(tightElectrons.ptrToItems), &(looseElectrons.ptrToItems));
//   kinVars.push_back(&myLepIDAndIsoSF);

  //CERN version
  RecoIDIsoSIPSFs myRecoIDIsoSIPSF3Lep(3, &(tightLoosePreselectedLeptons.ptrToItems));
  kinVars.push_back(&myRecoIDIsoSIPSF3Lep);

  RecoIDIsoSIPSFs myRecoIDIsoSIPSF4Lep(4, &(tightLoosePreselectedLeptons.ptrToItems));
  kinVars.push_back(&myRecoIDIsoSIPSF4Lep);

  LeptonTriggerScaleFactors myLepTrig(&lepHelper, &(tightMuons.ptrToItems), &(looseMuons.ptrToItems),
                                      &(preselectedMuons.ptrToItems), &(tightElectrons.ptrToItems),
                                      &(looseElectrons.ptrToItems), &(preselectedElectrons.ptrToItems));
  kinVars.push_back(&myLepTrig);

  //Give particular collections
//   TightChargeAndLepMVAScaleFactors myTightChargeAndLepMVASF3Lep(3, &(tightLoosePreselectedLeptons.ptrToItems));
//   kinVars.push_back(&myTightChargeAndLepMVASF3Lep);

//   TightChargeAndLepMVAScaleFactors myTightChargeAndLepMVASF4Lep(4, &(tightLoosePreselectedLeptons.ptrToItems));
//   kinVars.push_back(&myTightChargeAndLepMVASF4Lep);

//   TightChargeAndLepMVAScaleFactorsPerLepton myTightChargeAndLepMVASFPerLepton(4, &(tightLoosePreselectedLeptons.ptrToItems));
//   kinVars.push_back(&myTightChargeAndLepMVASFPerLepton);

//   TightChargeAndLepMVAScaleFactorsPerLepton myTightChargeAndLepMVASFPerZLepton(2, &(tightLoosePreselectedZLeptons.ptrToItems), "_Z");
//   kinVars.push_back(&myTightChargeAndLepMVASFPerZLepton);

//   TightChargeAndLepMVAScaleFactorsPerLepton myTightChargeAndLepMVASFPerNonZLepton(2, &(tightLoosePreselectedNonZLeptons.ptrToItems), "_nonZ");
//   kinVars.push_back(&myTightChargeAndLepMVASFPerNonZLepton);

//   TightChargeAndLepMVAScaleFactorsPerLepton myTightChargeAndLepMVASFPerSSLepton(2, &(leptonsSS.ptrToItems), "_SS");
//   kinVars.push_back(&myTightChargeAndLepMVASFPerSSLepton);

//   TightChargeAndLepMVAScaleFactorsPerLepton myTightChargeAndLepMVASFPerOSLepton(1, &(leptonsOS.ptrToItems), "_OS");
//   kinVars.push_back(&myTightChargeAndLepMVASFPerOSLepton);

  TightChargeAndLepCutScaleFactors myTightChargeAndLepCutSF3Lep(3, &(tightLoosePreselectedLeptons.ptrToItems));
  kinVars.push_back(&myTightChargeAndLepCutSF3Lep);

  TightChargeAndLepCutScaleFactors myTightChargeAndLepCutSF4Lep(4, &(tightLoosePreselectedLeptons.ptrToItems));
  kinVars.push_back(&myTightChargeAndLepCutSF4Lep);

  TightChargeAndLepCutScaleFactorsPerLepton myTightChargeAndLepCutSFPerLepton(4, &(tightLoosePreselectedLeptons.ptrToItems));
  kinVars.push_back(&myTightChargeAndLepCutSFPerLepton);

  TightChargeAndLepCutScaleFactorsPerLepton myTightChargeAndLepCutSFPerZLepton(2, &(tightLoosePreselectedZLeptons.ptrToItems), "_Z");
  kinVars.push_back(&myTightChargeAndLepCutSFPerZLepton);

  TightChargeAndLepCutScaleFactorsPerLepton myTightChargeAndLepCutSFPerNonZLepton(2, &(tightLoosePreselectedNonZLeptons.ptrToItems), "_nonZ");
  kinVars.push_back(&myTightChargeAndLepCutSFPerNonZLepton);

  TightChargeAndLepCutScaleFactorsPerLepton myTightChargeAndLepCutSFPerSSLepton(2, &(leptonsSS.ptrToItems), "_SS");
  kinVars.push_back(&myTightChargeAndLepCutSFPerSSLepton);

  TightChargeAndLepCutScaleFactorsPerLepton myTightChargeAndLepCutSFPerOSLepton(1, &(leptonsOS.ptrToItems), "_OS");
  kinVars.push_back(&myTightChargeAndLepCutSFPerOSLepton);

  CleanEventVars myClean(&lepHelper, &(events.ptrToItems), &(primaryVertexes.ptrToItems));
  kinVars.push_back(&myClean);

  CheckTwoLepTrigger checkTrig(&lepHelper, &(hltCollection.ptrToItems));
  kinVars.push_back(&checkTrig);

  LepMVAs<BNleptonCollection> myLepMVAsAllLeptons(&lepHelper, &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 4);
  kinVars.push_back(&myLepMVAsAllLeptons);

  LepMVAs<BNleptonCollection> myLepMVAsAllZLeptons(&lepHelper, &(tightLoosePreselectedZLeptons.ptrToItems), "all_Z_leptons_by_pt", 2);
  kinVars.push_back(&myLepMVAsAllZLeptons);

  LepMVAs<BNleptonCollection> myLepMVAsAllNonZLeptons(&lepHelper, &(tightLoosePreselectedNonZLeptons.ptrToItems), "all_nonZ_leptons_by_pt", 2);
  kinVars.push_back(&myLepMVAsAllNonZLeptons);

  LepMVAs<BNleptonCollection> myLepMVAsAllLeptonsSS(&lepHelper, &(leptonsSS.ptrToItems), "all_SS_leptons_by_pt", 2);
  kinVars.push_back(&myLepMVAsAllLeptonsSS);

  LepMVAs<BNleptonCollection> myLepMVAsAllLeptonsOS(&lepHelper, &(leptonsOS.ptrToItems), "all_OS_leptons_by_pt", 1);
  kinVars.push_back(&myLepMVAsAllLeptonsOS);

  LepCuts<BNleptonCollection> myLepCutsAllLeptons(&(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 4);
  kinVars.push_back(&myLepCutsAllLeptons);

  LepCuts<BNleptonCollection> myLepCutsAllZLeptons(&(tightLoosePreselectedZLeptons.ptrToItems), "all_Z_leptons_by_pt", 2);
  kinVars.push_back(&myLepCutsAllZLeptons);

  LepCuts<BNleptonCollection> myLepCutsAllNonZLeptons(&(tightLoosePreselectedNonZLeptons.ptrToItems), "all_nonZ_leptons_by_pt", 2);
  kinVars.push_back(&myLepCutsAllNonZLeptons);

  LepCuts<BNleptonCollection> myLepCutsAllLeptonsSS(&(leptonsSS.ptrToItems), "all_SS_leptons_by_pt", 2);
  kinVars.push_back(&myLepCutsAllLeptonsSS);

  LepCuts<BNleptonCollection> myLepCutsAllLeptonsOS(&(leptonsOS.ptrToItems), "all_OS_leptons_by_pt", 1);
  kinVars.push_back(&myLepCutsAllLeptonsOS);

//   DataDrivenFR<BNleptonCollection> myDataDrivenFR3Tight(&lepHelper, &(tightLoosePreselectedLeptons.ptrToItems), &(mediumCSVJets.ptrToItems),
//                                                         3, 0.7, "FR_merged_data", "QF_data_el", "_3_tight"); 
//   kinVars.push_back(&myDataDrivenFR3Tight);
  
//   DataDrivenFR<BNleptonCollection> myDataDrivenFR2LooseZ1TightNonZ(&lepHelper, &(tightLoosePreselectedZLeptons.ptrToItems), &(mediumCSVJets.ptrToItems),
//                                                                    2, -0.3, "FR_merged_data", "QF_data_el", "_2_loose_Z_1_tight_nonZ",
//                                                                    &(tightLoosePreselectedNonZLeptons.ptrToItems), 1, 0.7); 
//   kinVars.push_back(&myDataDrivenFR2LooseZ1TightNonZ);

//   DataDrivenFR<BNleptonCollection> myDataDrivenFR2TightSS1LooseOS(&lepHelper, &(leptonsSS.ptrToItems), &(mediumCSVJets.ptrToItems),
//                                                                   2, 0.7, "FR_merged_data", "QF_data_el", "_2_tight_SS_1_loose_OS",
//                                                                   &(leptonsOS.ptrToItems), 1, -0.3); 
//   kinVars.push_back(&myDataDrivenFR2TightSS1LooseOS);

//   DataDrivenFRPerLepton<BNleptonCollection> myDataDrivenFRPerLepton2LooseZ(&lepHelper, &(tightLoosePreselectedZLeptons.ptrToItems), &(mediumCSVJets.ptrToItems),
//                                                                    2, -0.3, "FR_merged_data", "QF_data_el", "_2_loose_Z"); 
//   kinVars.push_back(&myDataDrivenFRPerLepton2LooseZ);
  
//   DataDrivenFRPerLepton<BNleptonCollection> myDataDrivenFRPerLepton1TightNonZ(&lepHelper, &(tightLoosePreselectedNonZLeptons.ptrToItems), &(mediumCSVJets.ptrToItems),
//                                                                    1, 0.7, "FR_merged_data", "QF_data_el", "_1_tight_nonZ"); 
//   kinVars.push_back(&myDataDrivenFRPerLepton1TightNonZ);
  
//   DataDrivenFRPerLepton<BNleptonCollection> myDataDrivenFRPerLepton2TightSS(&lepHelper, &(leptonsSS.ptrToItems), &(mediumCSVJets.ptrToItems),
//                                                                             2, 0.7, "FR_merged_data", "QF_data_el", "_2_tight_SS"); 
//   kinVars.push_back(&myDataDrivenFRPerLepton2TightSS);
  
//   DataDrivenFRPerLepton<BNleptonCollection> myDataDrivenFRPerLepton1LooseOS(&lepHelper, &(leptonsOS.ptrToItems), &(mediumCSVJets.ptrToItems),
//                                                                             1, -0.3, "FR_merged_data", "QF_data_el", "_1_loose_OS"); 
//   kinVars.push_back(&myDataDrivenFRPerLepton1LooseOS);
  
//   DataDrivenFR<BNleptonCollection> myDataDrivenFR3Loose(&lepHelper, &(tightLoosePreselectedLeptons.ptrToItems), &(mediumCSVJets.ptrToItems),
//                                                         3, -0.3, "FR_merged_data", "QF_data_el", "_3_loose");
//   kinVars.push_back(&myDataDrivenFR3Loose);
  
//   DataDrivenFR<BNleptonCollection> myDataDrivenFR4Loose(&lepHelper, &(tightLoosePreselectedLeptons.ptrToItems), &(mediumCSVJets.ptrToItems),
//                                                         4, -0.3, "FR_merged_data", "QF_data_el", "_4_loose");
//   kinVars.push_back(&myDataDrivenFR4Loose);

  DataDrivenFRLepCut<BNleptonCollection> myDataDrivenFRLepCut3Tight(&(tightLoosePreselectedLeptons.ptrToItems),
                                                        3, 2, "FR_merged_data", "QF_data_el", "_3_tight"); 
  kinVars.push_back(&myDataDrivenFRLepCut3Tight);
  
  DataDrivenFRLepCut<BNleptonCollection> myDataDrivenFRLepCut2LooseZ1TightNonZ(&(tightLoosePreselectedZLeptons.ptrToItems),
                                                                   2, 1, "FR_merged_data", "QF_data_el", "_2_loose_Z_1_tight_nonZ",
                                                                   &(tightLoosePreselectedNonZLeptons.ptrToItems), 1, 2); 
  kinVars.push_back(&myDataDrivenFRLepCut2LooseZ1TightNonZ);

  DataDrivenFRLepCut<BNleptonCollection> myDataDrivenFRLepCut2TightSS1LooseOS(&(leptonsSS.ptrToItems),
                                                                  2, 2, "FR_merged_data", "QF_data_el", "_2_tight_SS_1_loose_OS",
                                                                  &(leptonsOS.ptrToItems), 1, 1); 
  kinVars.push_back(&myDataDrivenFRLepCut2TightSS1LooseOS);

  DataDrivenFRLepCutPerLepton<BNleptonCollection> myDataDrivenFRLepCutPerLepton2LooseZ(&(tightLoosePreselectedZLeptons.ptrToItems),
                                                                   2, 1, "FR_merged_data", "QF_data_el", "_2_loose_Z"); 
  kinVars.push_back(&myDataDrivenFRLepCutPerLepton2LooseZ);
  
  DataDrivenFRLepCutPerLepton<BNleptonCollection> myDataDrivenFRLepCutPerLepton1TightNonZ(&(tightLoosePreselectedNonZLeptons.ptrToItems),
                                                                   1, 2, "FR_merged_data", "QF_data_el", "_1_tight_nonZ"); 
  kinVars.push_back(&myDataDrivenFRLepCutPerLepton1TightNonZ);
  
  DataDrivenFRLepCutPerLepton<BNleptonCollection> myDataDrivenFRLepCutPerLepton2TightSS(&(leptonsSS.ptrToItems),
                                                                            2, 2, "FR_merged_data", "QF_data_el", "_2_tight_SS"); 
  kinVars.push_back(&myDataDrivenFRLepCutPerLepton2TightSS);
  
  DataDrivenFRLepCutPerLepton<BNleptonCollection> myDataDrivenFRLepCutPerLepton1LooseOS(&(leptonsOS.ptrToItems),
                                                                            1, 1, "FR_merged_data", "QF_data_el", "_1_loose_OS"); 
  kinVars.push_back(&myDataDrivenFRLepCutPerLepton1LooseOS);
  
  DataDrivenFRLepCut<BNleptonCollection> myDataDrivenFRLepCut3Loose(&(tightLoosePreselectedLeptons.ptrToItems),
                                                        3, 1, "FR_merged_data", "QF_data_el", "_3_loose");
  kinVars.push_back(&myDataDrivenFRLepCut3Loose);
  
  DataDrivenFRLepCut<BNleptonCollection> myDataDrivenFRLepCut4Tight(&(tightLoosePreselectedLeptons.ptrToItems),
                                                        4, 2, "FR_merged_data", "QF_data_el", "_4_tight"); 
  kinVars.push_back(&myDataDrivenFRLepCut4Tight);
  
  DataDrivenFRLepCut<BNleptonCollection> myDataDrivenFRLepCut4Loose(&(tightLoosePreselectedLeptons.ptrToItems),
                                                        4, 1, "FR_merged_data", "QF_data_el", "_4_loose");
  kinVars.push_back(&myDataDrivenFRLepCut4Loose);

  DBCorrectedRelIsoDR04s myDBCorrectedRelIsoDR04s(&lepHelper, &(tightLoosePreselectedLeptons.ptrToItems),
                                                  "all_leptons_by_pt", 1, 4);
  kinVars.push_back(&myDBCorrectedRelIsoDR04s);

  HiggsDecayType myHiggsDecayType(&lepHelper, &(mcParticles.ptrToItems));
  kinVars.push_back(&myHiggsDecayType);

  // Full event kinematics
  TwoObjectKinematic<BNleptonCollection,BNjetCollection>
    mySumPt("pt", "sum", "sum_pt",
            &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
            &(jets.ptrToItems), "jets_by_pt", 1, 99);
  kinVars.push_back(&mySumPt);
  
  TwoObjectKinematic<BNjetCollection,BNjetCollection>
    mySumJetPt("pt", "sum", "sum_jet_pt",
               &(jets.ptrToItems), "jets_by_pt", 1, 99,
               &(jets.ptrToItems), "jets_by_pt", 1, 99);
  kinVars.push_back(&mySumJetPt);
  
  TwoObjectKinematic<BNjetCollection,BNjetCollection>
    myMassOfJets("mass", "vector_sum", "mass_of_jets",
                    &(jets.ptrToItems), "jets_by_pt", 1, 99,
                    &(jets.ptrToItems), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMassOfJets);
  
  TwoObjectKinematic<BNjetCollection,BNjetCollection>
    myMTOfJets("MT", "vector_sum", "MT_of_jets",
                    &(jets.ptrToItems), "jets_by_pt", 1, 99,
                    &(jets.ptrToItems), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMTOfJets);
  
  ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection>
    myMassOfEverything("mass", "vector_sum", "mass_of_everything",
                       &(met.ptrToItems), "met", 1, 1,
                       &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                       &(jets.ptrToItems), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMassOfEverything);

  ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection>
    myMTOfEverything("MT", "vector_sum", "MT_of_everything",
                       &(met.ptrToItems), "met", 1, 1,
                       &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                       &(jets.ptrToItems), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMTOfEverything);

//   //3l ttbarZ
//   TwoObjectKinematic<BNjetCollection,BNjetCollection>
//     myWLikeDijetMass81X1B("mass", "closest_to", "WLike_dijet_mass_X1b",
//                           &(jetsByCSV.ptrToItems), "jets_by_CSV", 2, 99,
//                           &(jetsByCSV.ptrToItems), "jets_by_CSV", 2, 99,
//                           81);
//   kinVars.push_back(&myWLikeDijetMass81X1B);

//   TwoObjectKinematic<BNjetCollection,BNjetCollection>
//     myWLikeDijetMass81X2B("mass", "closest_to", "WLike_dijet_mass_X2b",
//                           &(jetsByCSV.ptrToItems), "jets_by_CSV", 3, 99,
//                           &(jetsByCSV.ptrToItems), "jets_by_CSV", 3, 99,
//                           81);
//   kinVars.push_back(&myWLikeDijetMass81X2B);

  //3l ttbarZ
  TwoObjectKinematic<BNmetCollection,BNleptonCollection>
    myMtMetNonZLep("MT", "min", "WLike_MT_met_lep",
                   &(met.ptrToItems), "met", 1, 1,
                   &(tightLoosePreselectedNonZLeptons.ptrToItems), "all_nonZ_leptons_by_pt", 1, 1);
  kinVars.push_back(&myMtMetNonZLep);
  
  TwoObjectKinematic<BNmetCollection,BNleptonCollection>
    myDeltaPhiMetNonZLep("deltaPhi", "min", "WLike_deltaPhi_met_lep",
                   &(met.ptrToItems), "met", 1, 1,
                   &(tightLoosePreselectedNonZLeptons.ptrToItems), "all_nonZ_leptons_by_pt", 1, 1);
  kinVars.push_back(&myDeltaPhiMetNonZLep);
  
//   ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection>
//     myMtMetNonZLepB("MT", "all_pairs", "topLike_MT_met_lep_b",
//                     &(met.ptrToItems), "met", 1, 1,
//                     &(tightLoosePreselectedNonZLeptons.ptrToItems), "all_nonZ_leptons_by_pt", 1, 1,
//                     &(jetsByCSV.ptrToItems), "jets_by_CSV", 1, 2);
//   kinVars.push_back(&myMtMetNonZLepB);
  
//   ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection>
//     myMtMetNonZLepB175("MT", "closest_to", "topLike_MT_met_lep_b_175",
//                        &(met.ptrToItems), "met", 1, 1,
//                        &(tightLoosePreselectedNonZLeptons.ptrToItems), "all_nonZ_leptons_by_pt", 1, 1,
//                        &(jetsByCSV.ptrToItems), "jets_by_CSV", 1, 2,
//                        175);
//   kinVars.push_back(&myMtMetNonZLepB175);
  
//   TwoObjectKinematic<BNleptonCollection,BNjetCollection>
//     myMassNonZLepB("mass", "all_pairs", "topLike_mass_lep_b",
//                    &(tightLoosePreselectedNonZLeptons.ptrToItems), "all_nonZ_leptons_by_pt", 1, 1,
//                    &(jetsByCSV.ptrToItems), "jets_by_CSV", 1, 2);
//   kinVars.push_back(&myMassNonZLepB);

//   TwoObjectKinematic<BNleptonCollection,BNjetCollection>
//     myMassNonZLepB100("mass", "closest_to", "topLike_mass_lep_b_100",
//                    &(tightLoosePreselectedNonZLeptons.ptrToItems), "all_nonZ_leptons_by_pt", 1, 1,
//                       &(jetsByCSV.ptrToItems), "jets_by_CSV", 1, 2,
//                       100);
//   kinVars.push_back(&myMassNonZLepB100);

//   TwoObjectKinematic<BNjetCollection,BNjetCollection>
//     myTopLikeMultijetMassB1("mass", "vector_sum", "topLike_multijet_mass_b1",
//                                &(jetsByCSV.ptrToItems), "jets_by_CSV", 1, 1,
//                                &(jetsByCSV.ptrToItems), "jets_by_CSV", 3, 99);
//   kinVars.push_back(&myTopLikeMultijetMassB1);

//   TwoObjectKinematic<BNjetCollection,BNjetCollection>
//     myTopLikeMultijetMassB2("mass", "vector_sum", "topLike_multijet_mass_b2",
//                                &(jetsByCSV.ptrToItems), "jets_by_CSV", 2, 2,
//                                &(jetsByCSV.ptrToItems), "jets_by_CSV", 3, 99);
//   kinVars.push_back(&myTopLikeMultijetMassB2);

//   ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection>
//     myMtMetNonZLepJets("MT", "vector_sum", "topPairLike_MT_met_lep_jets",
//                        &(met.ptrToItems), "met", 1, 1,
//                        &(tightLoosePreselectedNonZLeptons.ptrToItems), "all_nonZ_leptons_by_pt", 1, 1,
//                        &(jets.ptrToItems), "jets_by_pt", 1, 99);
//   kinVars.push_back(&myMtMetNonZLepJets);
  
//   TwoObjectKinematic<BNleptonCollection,BNjetCollection>
//     myMassNonZLepJets("mass", "vector_sum", "topPairLike_mass_lep_jets",
//                       &(tightLoosePreselectedNonZLeptons.ptrToItems), "all_nonZ_leptons_by_pt", 1, 1,
//                       &(jets.ptrToItems), "jets_by_pt", 1, 99);
//   kinVars.push_back(&myMassNonZLepJets);

  
  // Two lepton kinematics
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMinMassLepLepSFOS("mass", "min", "min_mass_leplep_SFOS",
                                                                                &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                                                                                &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                                                                                -99, "same_flavour", "opposite_sign");
  kinVars.push_back(&myMinMassLepLepSFOS);
  
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMinMassLepLepOS("mass", "min", "min_mass_leplep_OS",
                                                                                &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                                                                                &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                                                                                -99, "opposite_sign");
  kinVars.push_back(&myMinMassLepLepOS);
  
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMinMassLepLep("mass", "min", "min_mass_leplep_all",
                                                                            &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                                                                            &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99);
  kinVars.push_back(&myMinMassLepLep);
  
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMinMassZNonZLep("mass", "min", "min_mass_Z_nonZ_lep",
                                                                            &(tightLoosePreselectedZLeptons.ptrToItems), "all_Z_leptons_by_pt", 1, 99,
                                                                            &(tightLoosePreselectedNonZLeptons.ptrToItems), "all_nonZ_leptons_by_pt", 1, 99);
  kinVars.push_back(&myMinMassZNonZLep);
  
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMinDeltaRZNonZLep("deltaR", "min", "min_deltaR_Z_nonZ_lep",
                                                                            &(tightLoosePreselectedZLeptons.ptrToItems), "all_Z_leptons_by_pt", 1, 99,
                                                                            &(tightLoosePreselectedNonZLeptons.ptrToItems), "all_nonZ_leptons_by_pt", 1, 99);
  kinVars.push_back(&myMinDeltaRZNonZLep);
  
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZLikeMassLepLepSFOSAll("mass", "closest_to", "ZLike_mass_leplep_SFOS_all",
                                                                                     &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                                                                                     &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                                                                                     91.2, "same_flavour", "opposite_sign");
  kinVars.push_back(&myZLikeMassLepLepSFOSAll);  

  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZLikePtLepLepSFOSAll("vectPt", "max", "ZLike_pt_leplep_SFOS_all",
                                                                                &(tightLoosePreselectedZLeptons.ptrToItems), "all_Z_leptons_by_pt", 1, 99,
                                                                                &(tightLoosePreselectedZLeptons.ptrToItems), "all_Z_leptons_by_pt", 1, 99);
  kinVars.push_back(&myZLikePtLepLepSFOSAll);

  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZLikeEtaLepLepSFOSAll("vectEta", "max", "ZLike_eta_leplep_SFOS_all",
                                                                                &(tightLoosePreselectedZLeptons.ptrToItems), "all_Z_leptons_by_pt", 1, 99,
                                                                                &(tightLoosePreselectedZLeptons.ptrToItems), "all_Z_leptons_by_pt", 1, 99);
  kinVars.push_back(&myZLikeEtaLepLepSFOSAll);

  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZLikeMassLepLepSFOSAll2("mass", "closest_to", "ZLike_mass_leplep_SFOS_all_2",
                                                                                           &(tightLoosePreselectedNonZLeptons.ptrToItems), "all_nonZ_leptons_by_pt", 1, 99,
                                                                                           &(tightLoosePreselectedNonZLeptons.ptrToItems), "all_nonZ_leptons_by_pt", 1, 99,
                                                                                           91.2, "same_flavour", "opposite_sign");
  kinVars.push_back(&myZLikeMassLepLepSFOSAll2);

  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZLikeMassLepLepAFASAll2("mass", "closest_to", "ZLike_mass_leplep_AFAS_all_2",
                                                                                           &(tightLoosePreselectedNonZLeptons.ptrToItems), "all_nonZ_leptons_by_pt", 1, 99,
                                                                                           &(tightLoosePreselectedNonZLeptons.ptrToItems), "all_nonZ_leptons_by_pt", 1, 99,
                                                                                           91.2);
  kinVars.push_back(&myZLikeMassLepLepAFASAll2);

//   //Variables for CERN same-sign dilepton BDT
  TwoObjectKinematic<BNleptonCollection,BNjetCollection> myMHT("pt", "vector_sum", "mht",
                                                               &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                                                               &(jets.ptrToItems), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMHT);

  TightCharges myTightCharges(&(tightLoosePreselectedLeptons.ptrToItems), "CERN_tight_charge", "all_leptons_by_pt", 4);
  kinVars.push_back(&myTightCharges);
  //myTightCharges.setCut("pass");

  //////////////////////////////////
  //Variables for both matching algorithms
  //////////////////////////////////
  GenericCollectionSizeVariable<BNleptonCollection> numLeptonsFromW(&(leptonsFromW.ptrToItems), "numLeptonsFromW");
  kinVars.push_back(&numLeptonsFromW);
//   //cutvar for ttbar_lj
//   numLeptonsFromW.setCutMin(1);
//   cutVars.push_back(&numLeptonsFromW);
//   //cutvar for ttbar_ll
//   numLeptonsFromW.setCutMin(2);
//   cutVars.push_back(&numLeptonsFromW);

//   GenericCollectionMember<int, BNleptonCollection> LeptonsFromWTkCharge(Reflex::Type::ByName("BNlepton"), &(leptonsFromW.ptrToItems),
//                                                                         "tkCharge", "leptonsFromW",  KinematicVariableConstants::INT_INIT, 3);
//   kinVars.push_back(&LeptonsFromWTkCharge);
  
//   TwoObjectKinematic<BNleptonCollection,BNjetCollection>
//     myMassLepFromWJet("mass", "all_pairs", "mass_lepFromW_jet",
//                         &(leptonsFromW.ptrToItems), "leptonsFromW", 1, 3,
//                         &(jets.ptrToItems), "jets_by_pt", 1, 6);
//   kinVars.push_back(&myMassLepFromWJet);
  
//   //////////////////////////////////
//   //Variables for ttZ matching algorithm
//   //////////////////////////////////
  GenericCollectionSizeVariable<BNjetCollection> numJetsFromW(&(jetsFromW.ptrToItems), "numJetsFromW");
  kinVars.push_back(&numJetsFromW);

  GenericCollectionSizeVariable<BNjetCollection> numJetsFromLepTop(&(jetsFromLepTop.ptrToItems), "numJetsFromLepTop");
  kinVars.push_back(&numJetsFromLepTop);

  GenericCollectionSizeVariable<BNjetCollection> numJetsFromHadTop(&(jetsFromHadTop.ptrToItems), "numJetsFromHadTop");
  kinVars.push_back(&numJetsFromHadTop);

  GenericCollectionSizeVariable<BNleptonCollection> numLeptonsFromZ(&(leptonsFromZ.ptrToItems), "numLeptonsFromZ");
  kinVars.push_back(&numLeptonsFromZ);

//   GenericCollectionMember<double, BNjetCollection> genWJetCSV(Reflex::Type::ByName("BNjet"),  &(jetsFromW.ptrToItems),
//                                                              "btagCombinedSecVertex", "jetsFromW_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&genWJetCSV);

//   GenericCollectionMember<double, BNjetCollection> genLepTopJetCSV(Reflex::Type::ByName("BNjet"),  &(jetsFromLepTop.ptrToItems),
//                                                              "btagCombinedSecVertex", "jetsFromLepTop",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&genLepTopJetCSV);

//   GenericCollectionMember<double, BNjetCollection> genHadTopJetCSV(Reflex::Type::ByName("BNjet"),  &(jetsFromHadTop.ptrToItems),
//                                                              "btagCombinedSecVertex", "jetsFromHadTop",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&genHadTopJetCSV);

//   GenericCollectionMember<double, BNjetCollection> genWJetCharge(Reflex::Type::ByName("BNjet"),  &(jetsFromW.ptrToItems),
//                                                              "charge", "jetsFromW_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&genWJetCharge);

//   GenericCollectionMember<double, BNjetCollection> genLepTopJetCharge(Reflex::Type::ByName("BNjet"),  &(jetsFromLepTop.ptrToItems),
//                                                              "charge", "jetsFromLepTop",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&genLepTopJetCharge);

//   GenericCollectionMember<double, BNjetCollection> genHadTopJetCharge(Reflex::Type::ByName("BNjet"),  &(jetsFromHadTop.ptrToItems),
//                                                              "charge", "jetsFromHadTop",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&genHadTopJetCharge);

//   GenericCollectionMember<double, BNjetCollection> genWJetJetChargeRelativePtWeighted(Reflex::Type::ByName("BNjet"),  &(jetsFromW.ptrToItems),
//                                                              "jetChargeRelativePtWeighted", "jetsFromW_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&genWJetJetChargeRelativePtWeighted);

//   GenericCollectionMember<double, BNjetCollection> genLepTopJetJetChargeRelativePtWeighted(Reflex::Type::ByName("BNjet"),  &(jetsFromLepTop.ptrToItems),
//                                                              "jetChargeRelativePtWeighted", "jetsFromLepTop",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&genLepTopJetJetChargeRelativePtWeighted);

//   GenericCollectionMember<double, BNjetCollection> genHadTopJetJetChargeRelativePtWeighted(Reflex::Type::ByName("BNjet"),  &(jetsFromHadTop.ptrToItems),
//                                                              "jetChargeRelativePtWeighted", "jetsFromHadTop",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&genHadTopJetJetChargeRelativePtWeighted);

//   GenericCollectionMember<int, BNjetCollection> genWJetFlavour(Reflex::Type::ByName("BNjet"),  &(jetsFromW.ptrToItems),
//                                                              "flavour", "jetsFromW_by_CSV",  KinematicVariableConstants::INT_INIT, 2);
//   kinVars.push_back(&genWJetFlavour);

//   GenericCollectionMember<int, BNjetCollection> genWJetGenPartonId(Reflex::Type::ByName("BNjet"),  &(jetsFromW.ptrToItems),
//                                                              "genPartonId", "jetsFromW_by_CSV",  KinematicVariableConstants::INT_INIT, 2);
//   kinVars.push_back(&genWJetGenPartonId);

//   TwoObjectKinematic<BNmetCollection,BNleptonCollection>
//     myGenWMtMetLep("MT", "min", "gen_W_MT_met_lep",
//                    &(met.ptrToItems), "met", 1, 1,
//                    &(leptonsFromW.ptrToItems), "leptonsFromW", 1, 1);
//   kinVars.push_back(&myGenWMtMetLep);
  
//   TwoObjectKinematic<BNjetCollection,BNjetCollection>
//     myGenWDijetMass("mass", "vector_sum", "gen_W_dijet_mass",
//                     &(jetsFromW.ptrToItems), "jetsFromW_by_CSV", 1, 1,
//                     &(jetsFromW.ptrToItems), "jetsFromW_by_CSV", 2, 2);
//   kinVars.push_back(&myGenWDijetMass);
  
// //   TwoObjectKinematic<BNjetCollection,BNjetCollection>
// //     myRecoWDijetMass("mass", "vector_sum", "reco_W_dijet_mass",
// //                      &(jets.ptrToItems), "jets_by_pt", iJetFromW_1, iJetFromW_1,
// //                      &(jets.ptrToItems), "jets_by_pt", iJetFromW_2, iJetFromW_2);
// //   kinVars.push_back(&myRecoWDijetMass);
  
//   TwoObjectKinematic<BNjetCollection,BNjetCollection>
//     myGenHadTopTrijetMass("mass", "vector_sum", "gen_hadTop_trijet_mass",
//                           &(jetsFromW.ptrToItems), "jetsFromW_by_CSV", 1, 2,
//                           &(jetsFromHadTop.ptrToItems), "jetsFromHadTop", 1, 1);
//   kinVars.push_back(&myGenHadTopTrijetMass);
  
// //   ThreeObjectKinematic<BNjetCollection,BNjetCollection,BNjetCollection>
// //     myRecoHadTopTrijetMass("mass", "vector_sum", "reco_hadTop_trijet_mass",
// //                   &(jets.ptrToItems), "jets_by_pt", iJetFromHadTop, iJetFromHadTop,
// //                   &(jets.ptrToItems), "jets_by_pt", iJetFromW_1, iJetFromW_1,
// //                   &(jets.ptrToItems), "jets_by_pt", iJetFromW_2, iJetFromW_2);
// //   kinVars.push_back(&myRecoHadTopTrijetMass);

//   ThreeObjectKinematic<BNjetCollection,BNjetCollection,BNjetCollection>
//     myGenTTbarQuadjetMass("mass", "vector_sum", "gen_ttbar_quadjet_mass",
//                           &(jetsFromW.ptrToItems), "jetsFromW_by_CSV", 1, 2,
//                           &(jetsFromLepTop.ptrToItems), "jetsFromLepTop", 1, 1,
//                           &(jetsFromHadTop.ptrToItems), "jetsFromHadTop", 1, 1);
//   kinVars.push_back(&myGenTTbarQuadjetMass);

// //   FourObjectKinematic<BNjetCollection,BNjetCollection,BNjetCollection,BNjetCollection>
// //     myRecoTTbarQuadjetMass("mass", "vector_sum", "reco_ttbar_quadjet_mass",
// //                            &(jets.ptrToItems), "jets_by_pt", iJetFromLepTop, iJetFromLepTop,
// //                            &(jets.ptrToItems), "jets_by_pt", iJetFromHadTop, iJetFromHadTop,
// //                            &(jets.ptrToItems), "jets_by_pt", iJetFromW_1, iJetFromW_1,
// //                            &(jets.ptrToItems), "jets_by_pt", iJetFromW_2, iJetFromW_2);
// //   kinVars.push_back(&myRecoTTbarQuadjetMass);

//   ThreeObjectKinematic<BNjetCollection,BNjetCollection,BNjetCollection>
//     myGenTTbarQuadjetMT("MT", "vector_sum", "gen_ttbar_quadjet_MT",
//                           &(jetsFromW.ptrToItems), "jetsFromW_by_CSV", 1, 2,
//                           &(jetsFromLepTop.ptrToItems), "jetsFromLepTop", 1, 1,
//                           &(jetsFromHadTop.ptrToItems), "jetsFromHadTop", 1, 1);
//   kinVars.push_back(&myGenTTbarQuadjetMT);

// //   FourObjectKinematic<BNjetCollection,BNjetCollection,BNjetCollection,BNjetCollection>
// //     myRecoTTbarQuadjetMT("MT", "vector_sum", "reco_ttbar_quadjet_MT",
// //                            &(jets.ptrToItems), "jets_by_pt", iJetFromLepTop, iJetFromLepTop,
// //                            &(jets.ptrToItems), "jets_by_pt", iJetFromHadTop, iJetFromHadTop,
// //                            &(jets.ptrToItems), "jets_by_pt", iJetFromW_1, iJetFromW_1,
// //                            &(jets.ptrToItems), "jets_by_pt", iJetFromW_2, iJetFromW_2);
// //   kinVars.push_back(&myRecoTTbarQuadjetMT);

//   ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection>
//     myGenLepTopMtMetLepB("MT", "min", "gen_lepTop_MT_met_lep_b",
//                        &(met.ptrToItems), "met", 1, 1,
//                        &(leptonsFromW.ptrToItems), "leptonsFromW", 1, 1,
//                        &(jetsFromLepTop.ptrToItems), "jetsFromLepTop", 1, 1);
//   kinVars.push_back(&myGenLepTopMtMetLepB);
  
// //   ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection>
// //     myRecoLepTopMtMetLepB("MT", "min", "reco_lepTop_MT_met_lep_b",
// //                        &(met.ptrToItems), "met", 1, 1,
// //                        &(tightLoosePreselectedNonZLeptons.ptrToItems), "tightLoosePreselectedNonZLeptons", 1, 1,
// //                        &(jets.ptrToItems), "jets_by_pt", iJetFromLepTop, iJetFromLepTop);
// //   kinVars.push_back(&myRecoLepTopMtMetLepB);
  
//   TwoObjectKinematic<BNleptonCollection,BNjetCollection>
//     myGenLepTopMassLepB("mass", "min", "gen_lepTop_mass_lep_b",
//                        &(leptonsFromW.ptrToItems), "leptonsFromW", 1, 1,
//                        &(jetsFromLepTop.ptrToItems), "jetsFromLepTop", 1, 1);
//   kinVars.push_back(&myGenLepTopMassLepB);
  
// //   TwoObjectKinematic<BNleptonCollection,BNjetCollection>
// //     myRecoLepTopMassLepB("mass", "min", "reco_lepTop_mass_lep_b",
// //                        &(tightLoosePreselectedNonZLeptons.ptrToItems), "tightLoosePreselectedNonZLeptons", 1, 1,
// //                        &(jets.ptrToItems), "jets_by_pt", iJetFromLepTop, iJetFromLepTop);
// //   kinVars.push_back(&myRecoLepTopMassLepB);
  
//   TwoObjectKinematic<BNjetCollection,BNjetCollection>
//     myDijetMasses("mass", "all_pairs", "dijet_mass",
//                   &(jets.ptrToItems), "jets_by_pt", 1, 6,
//                   &(jets.ptrToItems), "jets_by_pt", 1, 6);
//   kinVars.push_back(&myDijetMasses);

//   ThreeObjectKinematic<BNjetCollection,BNjetCollection,BNjetCollection>
//     myTrijetMasses("mass", "all_pairs", "trijet_mass",
//                   &(jets.ptrToItems), "jets_by_pt", 1, 6,
//                   &(jets.ptrToItems), "jets_by_pt", 1, 6,
//                   &(jets.ptrToItems), "jets_by_pt", 1, 6);
//   kinVars.push_back(&myTrijetMasses);

//   FourObjectKinematic<BNjetCollection,BNjetCollection,BNjetCollection,BNjetCollection>
//     myQuadjetMasses("mass", "all_pairs", "quadjet_mass",
//                     &(jets.ptrToItems), "jets_by_pt", 1, 6,
//                     &(jets.ptrToItems), "jets_by_pt", 1, 6,
//                     &(jets.ptrToItems), "jets_by_pt", 1, 6,
//                     &(jets.ptrToItems), "jets_by_pt", 1, 6);
//   kinVars.push_back(&myQuadjetMasses);
  
//   TwoObjectKinematic<BNjetCollection,BNjetCollection>
//     myDijetMTs("MT", "all_pairs", "dijet_MT",
//                   &(jets.ptrToItems), "jets_by_pt", 1, 6,
//                   &(jets.ptrToItems), "jets_by_pt", 1, 6);
//   kinVars.push_back(&myDijetMTs);

//   ThreeObjectKinematic<BNjetCollection,BNjetCollection,BNjetCollection>
//     myTrijetMTs("MT", "all_pairs", "trijet_MT",
//                   &(jets.ptrToItems), "jets_by_pt", 1, 6,
//                   &(jets.ptrToItems), "jets_by_pt", 1, 6,
//                   &(jets.ptrToItems), "jets_by_pt", 1, 6);
//   kinVars.push_back(&myTrijetMTs);

//   FourObjectKinematic<BNjetCollection,BNjetCollection,BNjetCollection,BNjetCollection>
//     myQuadjetMTs("MT", "all_pairs", "quadjet_MT",
//                  &(jets.ptrToItems), "jets_by_pt", 1, 6,
//                  &(jets.ptrToItems), "jets_by_pt", 1, 6,
//                  &(jets.ptrToItems), "jets_by_pt", 1, 6,
//                  &(jets.ptrToItems), "jets_by_pt", 1, 6);
//   kinVars.push_back(&myQuadjetMTs);

//   ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection>
//     myMtMetLepFromWJet("MT", "all_pairs", "MT_met_lepFromW_jet",
//                        &(met.ptrToItems), "met", 1, 1,
//                        &(leptonsFromW.ptrToItems), "leptonsFromW", 1, 1,
//                        &(jets.ptrToItems), "jets_by_pt", 1, 6);
//   kinVars.push_back(&myMtMetLepFromWJet);
  
  
//   //////////////////////////////////
//   //Variables for ttW matching algorithm
//   //////////////////////////////////
  GenericCollectionSizeVariable<BNjetCollection> numJetsFromTop(&(jetsFromTop.ptrToItems), "numJetsFromTop");
  kinVars.push_back(&numJetsFromTop);

  GenericCollectionSizeVariable<BNjetCollection> numJetsFromAntiTop(&(jetsFromAntiTop.ptrToItems), "numJetsFromAntiTop");
  kinVars.push_back(&numJetsFromAntiTop);

  GenericCollectionSizeVariable<BNleptonCollection> numLeptonsFromTop(&(leptonsFromTop.ptrToItems), "numLeptonsFromTop");
  kinVars.push_back(&numLeptonsFromTop);

  GenericCollectionSizeVariable<BNleptonCollection> numLeptonsFromAntiTop(&(leptonsFromAntiTop.ptrToItems), "numLeptonsFromAntiTop");
  kinVars.push_back(&numLeptonsFromAntiTop);

//   GenericCollectionMember<double, BNjetCollection> genTopJetCSV(Reflex::Type::ByName("BNjet"),  &(jetsFromTop.ptrToItems),
//                                                              "btagCombinedSecVertex", "jetsFromTop",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&genTopJetCSV);

//   GenericCollectionMember<double, BNjetCollection> genAntiTopJetCSV(Reflex::Type::ByName("BNjet"),  &(jetsFromAntiTop.ptrToItems),
//                                                              "btagCombinedSecVertex", "jetsFromAntiTop",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&genAntiTopJetCSV);

//   GenericCollectionMember<double, BNjetCollection> genTopJetPt(Reflex::Type::ByName("BNjet"),  &(jetsFromTop.ptrToItems),
//                                                              "pt", "jetsFromTop",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&genTopJetPt);

//   GenericCollectionMember<double, BNjetCollection> genAntiTopJetPt(Reflex::Type::ByName("BNjet"),  &(jetsFromAntiTop.ptrToItems),
//                                                              "pt", "jetsFromAntiTop",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&genAntiTopJetPt);

//   GenericCollectionMember<double, BNjetCollection> genTopJetEta(Reflex::Type::ByName("BNjet"),  &(jetsFromTop.ptrToItems),
//                                                              "eta", "jetsFromTop",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&genTopJetEta);

//   GenericCollectionMember<double, BNjetCollection> genAntiTopJetEta(Reflex::Type::ByName("BNjet"),  &(jetsFromAntiTop.ptrToItems),
//                                                              "eta", "jetsFromAntiTop",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&genAntiTopJetEta);

//   GenericCollectionMember<double, BNjetCollection> genTopJetCharge(Reflex::Type::ByName("BNjet"),  &(jetsFromTop.ptrToItems),
//                                                              "charge", "jetsFromTop",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&genTopJetCharge);

//   GenericCollectionMember<double, BNjetCollection> genAntiTopJetCharge(Reflex::Type::ByName("BNjet"),  &(jetsFromAntiTop.ptrToItems),
//                                                              "charge", "jetsFromAntiTop",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&genAntiTopJetCharge);

//   TwoObjectKinematic<BNleptonCollection,BNjetCollection>
//     myGenTopMassLepB("mass", "min", "gen_top_mass_lep_b",
//                      &(leptonsFromTop.ptrToItems), "leptonsFromTop", 1, 1,
//                      &(jetsFromTop.ptrToItems), "jetsFromTop", 1, 1);
//   kinVars.push_back(&myGenTopMassLepB);
  
//   TwoObjectKinematic<BNleptonCollection,BNjetCollection>
//     myGenAntiTopMassLepB("mass", "min", "gen_antiTop_mass_lep_b",
//                      &(leptonsFromAntiTop.ptrToItems), "leptonsFromAntiTop", 1, 1,
//                      &(jetsFromAntiTop.ptrToItems), "jetsFromAntiTop", 1, 1);
//   kinVars.push_back(&myGenAntiTopMassLepB);

//   TwoObjectKinematic<BNjetCollection,BNjetCollection>
//     myGenTTbarDijetMass("mass", "vector_sum", "gen_ttbar_dijet_mass",
//                         &(jetsFromTop.ptrToItems), "jetsFromTop", 1, 1,
//                         &(jetsFromAntiTop.ptrToItems), "jetsFromAntiTop", 1, 1);
//   kinVars.push_back(&myGenTTbarDijetMass);
  
//   TwoObjectKinematic<BNjetCollection,BNjetCollection>
//     myGenTTbarDijetMT("MT", "vector_sum", "gen_ttbar_dijet_MT",
//                       &(jetsFromTop.ptrToItems), "jetsFromTop", 1, 1,
//                       &(jetsFromAntiTop.ptrToItems), "jetsFromAntiTop", 1, 1);
//   kinVars.push_back(&myGenTTbarDijetMT);

//   //Only include if ttZ is not included
//   TwoObjectKinematic<BNjetCollection,BNjetCollection>
//     myDijetMasses("mass", "all_pairs", "dijet_mass",
//                   &(jets.ptrToItems), "jets_by_pt", 1, 4,
//                   &(jets.ptrToItems), "jets_by_pt", 1, 4);
//   kinVars.push_back(&myDijetMasses);

//   TwoObjectKinematic<BNjetCollection,BNjetCollection>
//     myDijetMTs("MT", "all_pairs", "dijet_MT",
//                   &(jets.ptrToItems), "jets_by_pt", 1, 4,
//                   &(jets.ptrToItems), "jets_by_pt", 1, 4);
//   kinVars.push_back(&myDijetMTs);


//   //////////////////////////////////
//   //Variables for ttbar_ll_fake matching algorithm
//   //////////////////////////////////
  GenericCollectionSizeVariable<BNleptonCollection> numLeptonsFromBFromTop(&(leptonsFromBFromTop.ptrToItems), "numLeptonsFromBFromTop");
  kinVars.push_back(&numLeptonsFromBFromTop);

  GenericCollectionSizeVariable<BNleptonCollection> numLeptonsFromBFromAntiTop(&(leptonsFromBFromAntiTop.ptrToItems), "numLeptonsFromBFromAntiTop");
  kinVars.push_back(&numLeptonsFromBFromAntiTop);

//   TwoObjectKinematic<BNleptonCollection,BNleptonCollection>
//     myGenTopMassLepBlep("mass", "min", "gen_top_mass_lep_blep",
//                      &(leptonsFromTop.ptrToItems), "leptonsFromTop", 1, 1,
//                      &(leptonsFromBFromTop.ptrToItems), "leptonsFromBFromTop", 1, 1);
//   kinVars.push_back(&myGenTopMassLepBlep);
  
//   TwoObjectKinematic<BNleptonCollection,BNleptonCollection>
//     myGenAntiTopMassLepBlep("mass", "min", "gen_antiTop_mass_lep_blep",
//                      &(leptonsFromAntiTop.ptrToItems), "leptonsFromAntiTop", 1, 1,
//                      &(leptonsFromBFromAntiTop.ptrToItems), "leptonsFromBFromAntiTop", 1, 1);
//   kinVars.push_back(&myGenAntiTopMassLepBlep);
  
//   TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMassLepLepOS("mass", "all_pairs", "mass_leplep_OS",
//                                                                            &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 3,
//                                                                            &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 3,
//                                                                            -99, "opposite_sign");
//   kinVars.push_back(&myMassLepLepOS);

  /////////////////////////////////
  //// Leptons
  /////////////////////////////////

  // pT
  
  GenericCollectionMember<double, BNleptonCollection> LeptonPt(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
                                                                  "pt", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&LeptonPt);

  GenericCollectionMember<double, BNleptonCollection> ZLeptonPt(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
                                                                  "pt", "all_Z_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&ZLeptonPt);

  GenericCollectionMember<double, BNleptonCollection> NonZLeptonPt(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
                                                                  "pt", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&NonZLeptonPt);

  GenericCollectionMember<double, BNleptonCollection> SSLeptonPt(Reflex::Type::ByName("BNlepton"), &(leptonsSS.ptrToItems),
                                                                  "pt", "all_SS_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&SSLeptonPt);

  GenericCollectionMember<double, BNleptonCollection> OSLeptonPt(Reflex::Type::ByName("BNlepton"), &(leptonsOS.ptrToItems),
                                                                  "pt", "all_OS_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 1);
  kinVars.push_back(&OSLeptonPt);

  // eta
  
  GenericCollectionMember<double, BNleptonCollection> LeptonEta(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
                                                                  "eta", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&LeptonEta);

  GenericCollectionMember<double, BNleptonCollection> ZLeptonEta(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
                                                                  "eta", "all_Z_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&ZLeptonEta);

  GenericCollectionMember<double, BNleptonCollection> NonZLeptonEta(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
                                                                  "eta", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&NonZLeptonEta);

  GenericCollectionMember<double, BNleptonCollection> SSLeptonEta(Reflex::Type::ByName("BNlepton"), &(leptonsSS.ptrToItems),
                                                                  "eta", "all_SS_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&SSLeptonEta);

  GenericCollectionMember<double, BNleptonCollection> OSLeptonEta(Reflex::Type::ByName("BNlepton"), &(leptonsOS.ptrToItems),
                                                                  "eta", "all_OS_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&OSLeptonEta);

  GenericCollectionMember<double, BNleptonCollection> SSLeptonJetBtagCSV(Reflex::Type::ByName("BNlepton"), &(leptonsSS.ptrToItems),
                                                                  "jetBTagCSV", "all_SS_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&SSLeptonJetBtagCSV);

  // isMuon / isElectron
  
  GenericCollectionMember<int, BNleptonCollection> NonZLeptonIsMuon(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
                                                                       "isMuon", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&NonZLeptonIsMuon);

  GenericCollectionMember<int, BNleptonCollection> NonZLeptonIsElectron(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
                                                                       "isElectron", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&NonZLeptonIsElectron);

  GenericCollectionMember<int, BNleptonCollection> SSLeptonIsMuon(Reflex::Type::ByName("BNlepton"), &(leptonsSS.ptrToItems),
                                                                       "isMuon", "all_SS_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&SSLeptonIsMuon);

  GenericCollectionMember<int, BNleptonCollection> OSLeptonIsMuon(Reflex::Type::ByName("BNlepton"), &(leptonsOS.ptrToItems),
                                                                       "isMuon", "all_OS_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&OSLeptonIsMuon);

  // tkCharge
  
  GenericCollectionMember<int, BNleptonCollection> allLeptonTkCharge(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
                                                                     "tkCharge", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonTkCharge);

  GenericCollectionMember<int, BNleptonCollection> NonZLeptonTkCharge(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
                                                                  "tkCharge", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&NonZLeptonTkCharge);

  GenericCollectionMember<int, BNleptonCollection> OSLeptonTkCharge(Reflex::Type::ByName("BNlepton"), &(leptonsOS.ptrToItems),
                                                                  "tkCharge", "all_OS_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&OSLeptonTkCharge);

//   GenericCollectionMember<double, BNleptonCollection> allLeptonSIP(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
//                                                                    "SIP", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&allLeptonSIP);

//   GenericCollectionMember<double, BNleptonCollection> allLeptonD0(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
//                                                                   "correctedD0Vertex", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&allLeptonD0);

//   GenericCollectionMember<double, BNleptonCollection> allLeptonDZ(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
//                                                                   "correctedDZ", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&allLeptonDZ);

//   GenericCollectionMember<double, BNleptonCollection> allLeptonIP(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
//                                                                                "IP", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&allLeptonIP);

//   GenericCollectionMember<double, BNleptonCollection> allLeptonIPError(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
//                                                                                     "IPError", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&allLeptonIPError);

//   // NonZ extra lepton variables
  
//   GenericCollectionMember<double, BNleptonCollection> NonZLeptonPhi(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
//                                                                   "phi", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&NonZLeptonPhi);

//   GenericCollectionMember<double, BNleptonCollection> NonZLeptonSamNormChi2(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
//                                                                   "samNormChi2", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&NonZLeptonSamNormChi2);

//   GenericCollectionMember<double, BNleptonCollection> NonZLeptonSamPT(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
//                                                                   "samPT", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&NonZLeptonSamPT);

//   GenericCollectionMember<double, BNleptonCollection> NonZLeptonSamEta(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
//                                                                   "samEta", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&NonZLeptonSamEta);

//   GenericCollectionMember<double, BNleptonCollection> NonZLeptonSamPhi(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
//                                                                   "samPhi", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&NonZLeptonSamPhi);

//   DBCorrectedRelIsoDR04s myDBCorrectedRelIsoDR04sNonZ(&lepHelper, &(tightLoosePreselectedNonZLeptons.ptrToItems),
//                                                   "all_nonZ_leptons_by_pt", 1, 1);
//   kinVars.push_back(&myDBCorrectedRelIsoDR04sNonZ);

//   GenericCollectionMember<double, BNleptonCollection> NonZLeptonJetBTagCSV(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
//                                                                   "jetBTagCSV", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&NonZLeptonJetBTagCSV);

//   GenericCollectionMember<double, BNleptonCollection> NonZLeptonJetPtRatio(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
//                                                                   "jetPtRatio", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&NonZLeptonJetPtRatio);

//   GenericCollectionMember<double, BNleptonCollection> NonZLeptonJetDeltaR(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
//                                                                   "jetDeltaR", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&NonZLeptonJetDeltaR);

//   GenericCollectionMember<double, BNleptonCollection> NonZLeptonSIP(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
//                                                                    "SIP", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&NonZLeptonSIP);

//   GenericCollectionMember<double, BNleptonCollection> NonZLeptonD0(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
//                                                                   "correctedD0Vertex", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&NonZLeptonD0);

//   GenericCollectionMember<double, BNleptonCollection> NonZLeptonDZ(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
//                                                                   "correctedDZ", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&NonZLeptonDZ);

//   GenericCollectionMember<double, BNleptonCollection> NonZLeptonIP(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
//                                                                                "IP", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&NonZLeptonIP);

//   GenericCollectionMember<double, BNleptonCollection> NonZLeptonIPError(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
//                                                                                     "IPError", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&NonZLeptonIPError);

//   GenericCollectionMember<double, BNleptonCollection> NonZLeptonNormalizedChi2(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
//                                                                                     "normalizedChi2", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&NonZLeptonNormalizedChi2);

//   GenericCollectionMember<double, BNleptonCollection> NonZLeptonInnerTrackNormChi2(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
//                                                                                     "innerTrackNormChi2", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&NonZLeptonInnerTrackNormChi2);

//   GenericCollectionMember<double, BNleptonCollection> NonZLeptonTkNormChi2(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
//                                                                            "tkNormChi2", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&NonZLeptonTkNormChi2);

//   GenericCollectionMember<int, BNleptonCollection> NonZLeptonNumberOfValidTrackerHitsInnerTrack(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
//                                                                                     "numberOfValidTrackerHitsInnerTrack", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 1);
//   kinVars.push_back(&NonZLeptonNumberOfValidTrackerHitsInnerTrack);

//   GenericCollectionMember<int, BNleptonCollection> NonZLeptonNumberOfValidTrackerHits(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
//                                                                                     "numberOfValidTrackerHits", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 1);
//   kinVars.push_back(&NonZLeptonNumberOfValidTrackerHits);

//   GenericCollectionMember<int, BNleptonCollection> NonZLeptonNumberOfValidMuonHits(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
//                                                                                     "numberOfValidMuonHits", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 1);
//   kinVars.push_back(&NonZLeptonNumberOfValidMuonHits);

//   GenericCollectionMember<int, BNleptonCollection> NonZLeptonNumberOfValidPixelHits(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
//                                                                                     "numberOfValidPixelHits", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 1);
//   kinVars.push_back(&NonZLeptonNumberOfValidPixelHits);

//   GenericCollectionMember<int, BNleptonCollection> NonZLeptonNumberOfMatchedStations(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
//                                                                                     "numberOfMatchedStations", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 1);
//   kinVars.push_back(&NonZLeptonNumberOfMatchedStations);

//   GenericCollectionMember<int, BNleptonCollection> NonZLeptonNumberOfMatches(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
//                                                                                     "numberOfMatches", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 1);
//   kinVars.push_back(&NonZLeptonNumberOfMatches);

//   GenericCollectionMember<int, BNleptonCollection> NonZLeptonIsTrackerMuon(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
//                                                                                     "isTrackerMuon", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 1);
//   kinVars.push_back(&NonZLeptonIsTrackerMuon);

//   GenericCollectionMember<int, BNleptonCollection> NonZLeptonIsGlobalMuonPromptTight(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
//                                                                                     "isGlobalMuonPromptTight", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 1);
//   kinVars.push_back(&NonZLeptonIsGlobalMuonPromptTight);

//   GenericCollectionMember<int, BNleptonCollection> NonZLeptonIsGoodMuon_1StationTight(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
//                                                                                     "isGoodMuon_1StationTight", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 1);
//   kinVars.push_back(&NonZLeptonIsGoodMuon_1StationTight);

//   // Z extra lepton variables
  
//   GenericCollectionMember<double, BNleptonCollection> ZLeptonPhi(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
//                                                                   "phi", "all_Z_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&ZLeptonPhi);

//   GenericCollectionMember<double, BNleptonCollection> ZLeptonSamNormChi2(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
//                                                                   "samNormChi2", "all_Z_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&ZLeptonSamNormChi2);

//   GenericCollectionMember<double, BNleptonCollection> ZLeptonSamPT(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
//                                                                   "samPT", "all_Z_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&ZLeptonSamPT);

//   GenericCollectionMember<double, BNleptonCollection> ZLeptonSamEta(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
//                                                                   "samEta", "all_Z_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&ZLeptonSamEta);

//   GenericCollectionMember<double, BNleptonCollection> ZLeptonSamPhi(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
//                                                                   "samPhi", "all_Z_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&ZLeptonSamPhi);

//   DBCorrectedRelIsoDR04s myDBCorrectedRelIsoDR04sZ(&lepHelper, &(tightLoosePreselectedZLeptons.ptrToItems),
//                                                   "all_Z_leptons_by_pt", 1, 2);
//   kinVars.push_back(&myDBCorrectedRelIsoDR04sZ);

//   GenericCollectionMember<double, BNleptonCollection> ZLeptonJetBTagCSV(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
//                                                                   "jetBTagCSV", "all_Z_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&ZLeptonJetBTagCSV);

//   GenericCollectionMember<double, BNleptonCollection> ZLeptonJetPtRatio(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
//                                                                   "jetPtRatio", "all_Z_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&ZLeptonJetPtRatio);

//   GenericCollectionMember<double, BNleptonCollection> ZLeptonJetDeltaR(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
//                                                                   "jetDeltaR", "all_Z_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&ZLeptonJetDeltaR);

//   GenericCollectionMember<double, BNleptonCollection> ZLeptonSIP(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
//                                                                    "SIP", "all_Z_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&ZLeptonSIP);

//   GenericCollectionMember<double, BNleptonCollection> ZLeptonD0(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
//                                                                   "correctedD0Vertex", "all_Z_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&ZLeptonD0);

//   GenericCollectionMember<double, BNleptonCollection> ZLeptonDZ(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
//                                                                   "correctedDZ", "all_Z_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&ZLeptonDZ);

//   GenericCollectionMember<double, BNleptonCollection> ZLeptonIP(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
//                                                                                "IP", "all_Z_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&ZLeptonIP);

//   GenericCollectionMember<double, BNleptonCollection> ZLeptonIPError(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
//                                                                                     "IPError", "all_Z_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&ZLeptonIPError);

//   GenericCollectionMember<double, BNleptonCollection> ZLeptonNormalizedChi2(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
//                                                                                     "normalizedChi2", "all_Z_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&ZLeptonNormalizedChi2);

//   GenericCollectionMember<double, BNleptonCollection> ZLeptonInnerTrackNormChi2(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
//                                                                                     "innerTrackNormChi2", "all_Z_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&ZLeptonInnerTrackNormChi2);

//   GenericCollectionMember<double, BNleptonCollection> ZLeptonTkNormChi2(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
//                                                                            "tkNormChi2", "all_Z_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&ZLeptonTkNormChi2);

//   GenericCollectionMember<int, BNleptonCollection> ZLeptonNumberOfValidTrackerHitsInnerTrack(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
//                                                                                     "numberOfValidTrackerHitsInnerTrack", "all_Z_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
//   kinVars.push_back(&ZLeptonNumberOfValidTrackerHitsInnerTrack);

//   GenericCollectionMember<int, BNleptonCollection> ZLeptonNumberOfValidTrackerHits(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
//                                                                                     "numberOfValidTrackerHits", "all_Z_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
//   kinVars.push_back(&ZLeptonNumberOfValidTrackerHits);

//   GenericCollectionMember<int, BNleptonCollection> ZLeptonNumberOfValidMuonHits(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
//                                                                                     "numberOfValidMuonHits", "all_Z_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
//   kinVars.push_back(&ZLeptonNumberOfValidMuonHits);

//   GenericCollectionMember<int, BNleptonCollection> ZLeptonNumberOfValidPixelHits(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
//                                                                                     "numberOfValidPixelHits", "all_Z_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
//   kinVars.push_back(&ZLeptonNumberOfValidPixelHits);

//   GenericCollectionMember<int, BNleptonCollection> ZLeptonNumberOfMatchedStations(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
//                                                                                     "numberOfMatchedStations", "all_Z_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
//   kinVars.push_back(&ZLeptonNumberOfMatchedStations);

//   GenericCollectionMember<int, BNleptonCollection> ZLeptonNumberOfMatches(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
//                                                                                     "numberOfMatches", "all_Z_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
//   kinVars.push_back(&ZLeptonNumberOfMatches);

//   GenericCollectionMember<int, BNleptonCollection> ZLeptonIsTrackerMuon(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
//                                                                                     "isTrackerMuon", "all_Z_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
//   kinVars.push_back(&ZLeptonIsTrackerMuon);

//   GenericCollectionMember<int, BNleptonCollection> ZLeptonIsGlobalMuonPromptTight(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
//                                                                                     "isGlobalMuonPromptTight", "all_Z_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
//   kinVars.push_back(&ZLeptonIsGlobalMuonPromptTight);

//   GenericCollectionMember<int, BNleptonCollection> ZLeptonIsGoodMuon_1StationTight(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
//                                                                                     "isGoodMuon_1StationTight", "all_Z_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
//   kinVars.push_back(&ZLeptonIsGoodMuon_1StationTight);

  /////////////////////////////////////
  //// REQUIRED - Must do something with muons and electrons for leptons to be filled
  /////////////////////////////////////

  GenericCollectionMember<int, BNmuonCollection>
    allMuonIsMuon(Reflex::Type::ByName("BNmuon"), &(tightLoosePreselectedMuons.ptrToItems), "isMuon", "all_muons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allMuonIsMuon);
  
  GenericCollectionMember<int, BNelectronCollection>
    allElectronIsElectron(Reflex::Type::ByName("BNelectron"), &(tightLoosePreselectedElectrons.ptrToItems), "isElectron", "all_electrons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allElectronIsElectron);
  
  /////////////////////////////////////
  //// END REQUIRED - Must do something with muons and electrons for leptons to be filled
  /////////////////////////////////////

  // tight charge variables
  GenericCollectionMember<double, BNmuonCollection>
    allMuonNumberOfValidTrackerHitsInnerTrack(Reflex::Type::ByName("BNmuon"), &(tightLoosePreselectedMuons.ptrToItems), "numberOfValidTrackerHitsInnerTrack", "all_muons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allMuonNumberOfValidTrackerHitsInnerTrack);
  
  GenericCollectionMember<int, BNelectronCollection>
    allElectronNumberOfExpectedInnerHits(Reflex::Type::ByName("BNelectron"), &(tightLoosePreselectedElectrons.ptrToItems), "numberOfExpectedInnerHits", "all_electrons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allElectronNumberOfExpectedInnerHits);
  
  GenericCollectionMember<int, BNelectronCollection>
    allElectronPassConvVeto(Reflex::Type::ByName("BNelectron"), &(tightLoosePreselectedElectrons.ptrToItems), "passConvVeto", "all_electrons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allElectronPassConvVeto);
  
  GenericCollectionMember<int, BNelectronCollection>
    allElectronIsGsfCtfScPixChargeConsistent(Reflex::Type::ByName("BNelectron"), &(tightLoosePreselectedElectrons.ptrToItems), "isGsfCtfScPixChargeConsistent", "all_electrons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allElectronIsGsfCtfScPixChargeConsistent);
  
  // genId
  
  GenericCollectionMember<int, BNleptonCollection> ZLeptonGenMotherId(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
                                                                  "genMotherId", "all_Z_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&ZLeptonGenMotherId);

  GenericCollectionMember<int, BNleptonCollection> NonZLeptonGenMotherId(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
                                                                  "genMotherId", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&NonZLeptonGenMotherId);

  GenericCollectionMember<int, BNleptonCollection> ZLeptonGenGrandMotherId(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedZLeptons.ptrToItems),
                                                                  "genGrandMother00Id", "all_Z_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&ZLeptonGenGrandMotherId);

  GenericCollectionMember<int, BNleptonCollection> NonZLeptonGenGrandMotherId(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
                                                                  "genGrandMother00Id", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&NonZLeptonGenGrandMotherId);

//   ////////// all taus //////////
//   GenericCollectionMember<double, BNtauCollection> allTauPt(Reflex::Type::ByName("BNtau"), &(tightLoosePreselectedTaus.ptrToItems),
//                                                                       "pt", "all_taus_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&allTauPt);

//   GenericCollectionMember<double, BNtauCollection> allTauEta(Reflex::Type::ByName("BNtau"), &(tightLoosePreselectedTaus.ptrToItems),
//                                                                        "eta", "all_taus_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&allTauEta);

  ////////// jets by pt //////////
  GenericCollectionMember<double, BNjetCollection> allJetPt(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems),
                                                            "pt", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetPt);

  GenericCollectionMember<double, BNjetCollection> allJetCharge(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems),
                                                            "charge", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetCharge);

  GenericCollectionMember<double, BNjetCollection> allJetJetChargeRelativePtWeighted(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems),
                                                            "jetChargeRelativePtWeighted", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetJetChargeRelativePtWeighted);


  GenericCollectionMember<double, BNjetCollection> allJetEta(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems),
                                                             "eta", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetEta);

  GenericCollectionMember<double, BNjetCollection> allJetCSV(Reflex::Type::ByName("BNjet"),  &(jets.ptrToItems),
                                                             "btagCombinedSecVertex", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetCSV);

//   GenericCollectionMember<int, BNjetCollection> allJetGenPartonId(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems),
//                                                              "genPartonId", "jets_by_pt",  KinematicVariableConstants::INT_INIT, 6);
//   kinVars.push_back(&allJetGenPartonId);

//   GenericCollectionMember<int, BNjetCollection> allJetGenPartonMotherId(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems),
//                                                              "genPartonMotherId", "jets_by_pt",  KinematicVariableConstants::INT_INIT, 6);
//   kinVars.push_back(&allJetGenPartonMotherId);

//   GenericCollectionMember<int, BNjetCollection> allJetGenPartonGrandMother00Id(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems),
//                                                              "genPartonGrandMother00Id", "jets_by_pt",  KinematicVariableConstants::INT_INIT, 6);
//   kinVars.push_back(&allJetGenPartonGrandMother00Id);

  ////////// jets by CSV //////////
  GenericCollectionMember<double, BNjetCollection> allJetByCSVPt(Reflex::Type::ByName("BNjet"), &(jetsByCSV.ptrToItems),
                                                            "pt", "jets_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetByCSVPt);

//   GenericCollectionMember<double, BNjetCollection> allJetByCSVMass(Reflex::Type::ByName("BNjet"), &(jetsByCSV.ptrToItems),
//                                                             "mass", "jets_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 6);
//   kinVars.push_back(&allJetByCSVMass);

//   GenericCollectionMember<double, BNjetCollection> allJetByCSVEta(Reflex::Type::ByName("BNjet"), &(jetsByCSV.ptrToItems),
//                                                              "eta", "jets_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 6);
//   kinVars.push_back(&allJetByCSVEta);

  GenericCollectionMember<double, BNjetCollection> allJetByCSVCSV(Reflex::Type::ByName("BNjet"),  &(jetsByCSV.ptrToItems),
                                                             "btagCombinedSecVertex", "jets_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetByCSVCSV);

//   GenericCollectionMember<int, BNjetCollection> allJetByCSVGenPartonId(Reflex::Type::ByName("BNjet"), &(jetsByCSV.ptrToItems),
//                                                              "genPartonId", "jets_by_CSV",  KinematicVariableConstants::INT_INIT, 6);
//   kinVars.push_back(&allJetByCSVGenPartonId);

//   GenericCollectionMember<int, BNjetCollection> allJetByCSVGenPartonMotherId(Reflex::Type::ByName("BNjet"), &(jetsByCSV.ptrToItems),
//                                                              "genPartonMotherId", "jets_by_CSV",  KinematicVariableConstants::INT_INIT, 6);
//   kinVars.push_back(&allJetByCSVGenPartonMotherId);

//   GenericCollectionMember<int, BNjetCollection> allJetByCSVGenPartonGrandMother00Id(Reflex::Type::ByName("BNjet"), &(jetsByCSV.ptrToItems),
//                                                              "genPartonGrandMother00Id", "jets_by_CSV",  KinematicVariableConstants::INT_INIT, 6);
//   kinVars.push_back(&allJetByCSVGenPartonGrandMother00Id);


  ////////// met //////////
  GenericCollectionMember<double, BNmetCollection> metPt(Reflex::Type::ByName("BNmet"),  &(met.ptrToItems),
                                                         "pt", "met",  KinematicVariableConstants::FLOAT_INIT, 1);
  kinVars.push_back(&metPt);

  GenericCollectionMember<double, BNmetCollection> metPhi(Reflex::Type::ByName("BNmet"),  &(met.ptrToItems),
                                                         "phi", "met",  KinematicVariableConstants::FLOAT_INIT, 1);
  kinVars.push_back(&metPhi);

//   ////////// mc particles ////////
// //   GenericCollectionMember<double, BNmcparticleCollection> allMcParticlePt(Reflex::Type::ByName("BNmcparticle"), &(mcParticles.ptrToItems),
// //                                                                   "pt", "mcParticles_by_pt",  KinematicVariableConstants::FLOAT_INIT, 20);
// //   kinVars.push_back(&allMcParticlePt);

//   GenericCollectionMember<int, BNmcparticleCollection> allMcParticleId(Reflex::Type::ByName("BNmcparticle"), &(mcParticles.ptrToItems),
//                                                                   "id", "mcParticles_by_pt",  KinematicVariableConstants::INT_INIT, 10);
//   kinVars.push_back(&allMcParticleId);

  int numExtraPartons = -99;
  summaryTree->Branch("numExtraPartons", &numExtraPartons);

  bool dibosonPlusHFKeepEventBool = false;
  
  ////////// event info //////////
  GenericCollectionMember<unsigned, BNeventCollection> runNumber(Reflex::Type::ByName("BNevent"), &(events.ptrToItems),
                                                                 "run", "eventInfo",  KinematicVariableConstants::UINT_INIT, 1);
  kinVars.push_back(&runNumber);

  GenericCollectionMember<unsigned, BNeventCollection> lumiBlock(Reflex::Type::ByName("BNevent"), &(events.ptrToItems),
                                                                 "lumi", "eventInfo",  KinematicVariableConstants::UINT_INIT, 1);
  kinVars.push_back(&lumiBlock);

  // this is a long inside BNevent
  // just using keyword long won't work
  // needs to be Long64_t 
  GenericCollectionMember<Long64_t, BNeventCollection> eventNumber(Reflex::Type::ByName("BNevent"),  &(events.ptrToItems),
                                                                   "evt", "eventInfo",  KinematicVariableConstants::INT_INIT, 1);
  kinVars.push_back(&eventNumber);

  MetLD myMetLD(&myMHT, &metPt);
  kinVars.push_back(&myMetLD);

  //Comment out for ttbar_lj
  MatchTester_ttZ_3l myMatchTester_ttZ_3l(&(tightLoosePreselectedNonZLeptons.ptrToItems), &(jetsByCSV.ptrToItems), &(met.ptrToItems));
  kinVars.push_back(&myMatchTester_ttZ_3l);
  
  //Comment out for ttbar_ll
  MatchTester_ttW_3l myMatchTester_ttW_3l(&(tightLoosePreselectedLeptons.ptrToItems), &(jetsByCSV.ptrToItems));
  kinVars.push_back(&myMatchTester_ttW_3l);

  MatchTester_ttbar_fake_3l myMatchTester_ttbar_fake_3l(&(tightLoosePreselectedLeptons.ptrToItems), &(jetsByCSV.ptrToItems));
  kinVars.push_back(&myMatchTester_ttbar_fake_3l);

  FinalBDT_ttZ_3l myFinalBDT_ttZ_3l(&(jets.ptrToItems), &(mediumCSVJets.ptrToItems), &myMatchTester_ttZ_3l, &myZLikeMassLepLepSFOSAll);
  kinVars.push_back(&myFinalBDT_ttZ_3l);

  FinalBDT_ttW_3l myFinalBDT_ttW_3l(&(jets.ptrToItems), &(mediumCSVJets.ptrToItems), &myMTOfEverything,
                                    &myMassOfEverything, &myMatchTester_ttbar_fake_3l, &myMatchTester_ttW_3l);
  kinVars.push_back(&myFinalBDT_ttW_3l);

//   MatchTester_ttZ_3l_GP myMatchTester_ttZ_3l_GP(&(tightLoosePreselectedNonZLeptons.ptrToItems), &(jetsByCSV.ptrToItems), &(met.ptrToItems));
//   kinVars.push_back(&myMatchTester_ttZ_3l_GP);

//   MatchTesterBDT_ttZ_3l myMatchTesterBDT_ttZ_3l(&(tightLoosePreselectedNonZLeptons.ptrToItems), &(jetsByCSV.ptrToItems), &(met.ptrToItems));
//   kinVars.push_back(&myMatchTesterBDT_ttZ_3l);
  
//   //MatchTester for ttbar_lj
//   MatchTester_ttZ_3l myMatchTester_ttZ_3l(&(tightLeptons.ptrToItems), &(jetsByCSV.ptrToItems), &(met.ptrToItems));
//   kinVars.push_back(&myMatchTester_ttZ_3l);

// //   MatchTesterBDT_ttZ_3l myMatchTesterBDT_ttZ_3l(&(tightLeptons.ptrToItems), &(jetsByCSV.ptrToItems), &(met.ptrToItems));
// //   kinVars.push_back(&myMatchTesterBDT_ttZ_3l);
  
//   //MatchTester for ttbar_ll
//   MatchTester_ttW_3l myMatchTester_ttW_3l(&(tightLeptons.ptrToItems), &(jetsByCSV.ptrToItems));
//   kinVars.push_back(&myMatchTester_ttW_3l);

  Char_t *dataset = (Char_t *)lepHelper.dataset.c_str();
  summaryTree->Branch("dataset", (void*)dataset, "dataset/C");

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

  // begin for each event
  for (ev.toBegin(); !ev.atEnd(); ++ev){
    numEvents++;

    if ((numEvents > myConfig.maxEvents) && myConfig.maxEvents != -1) break;

    if (numEvents == 1 || numEvents % printEvery == 0 )
      cout << "Processing event.... " << numEvents << endl;

    if (debug > 9) cout << "---------->>>>>> Event " << numEvents << endl;


    /////////////////////////////////////////////////////////////
    //
    //    Initialize collections and apply object ids
    //
    //////////////////////////////////////////////////////////////
    jetsForLepMVA.initializeRawItemsSortedByCSV(ev, "BNproducer", "patJetsAK5PF");
    tightLoosePreselectedMuons.initializeRawItemsSortedByPt(ev, "BNproducer","selectedPatMuonsLoosePFlow");
    tightLoosePreselectedElectrons.initializeRawItemsSortedByPt(ev, "BNproducer","selectedPatElectronsGSF");
    tightLoosePreselectedTaus.initializeRawItemsSortedByPt(ev, "BNproducer","selectedPatTausPFlow");

    //lepHelper.applyRochesterCorrections(tightLoosePreselectedMuons.rawItems);
    //Apply Rochester for data only
    bool applyRochester = (lepHelper.isData);
    if (applyRochester) lepHelper.applyRochesterCorrections(tightLoosePreselectedMuons.rawItems);
    //bool applySmearing = !(lepHelper.isData);
    //No smearing
    bool applySmearing = false;
    if (applySmearing) {
      lepHelper.fillMCMatchAny(tightLoosePreselectedMuons.rawItems, mcParticles.rawItems, 0.3);
      lepHelper.fillMCMatchAny(tightLoosePreselectedElectrons.rawItems, mcParticles.rawItems, 0.3);
      lepHelper.fillMCMatchID(tightLoosePreselectedMuons.rawItems, mcParticles.rawItems, 1.2);
      lepHelper.fillMCMatchID(tightLoosePreselectedElectrons.rawItems, mcParticles.rawItems, 1.2);

      lepHelper.scaleMCCollectionDZ(tightLoosePreselectedElectrons.rawItems);
      lepHelper.scaleMCCollectionDZ(tightLoosePreselectedMuons.rawItems);
      lepHelper.scaleMCCollectionDXY(tightLoosePreselectedElectrons.rawItems);
      lepHelper.scaleMCCollectionDXY(tightLoosePreselectedMuons.rawItems);
    }
    lepHelper.fillSIP(tightLoosePreselectedMuons.rawItems, applySmearing);
    lepHelper.fillSIP(tightLoosePreselectedElectrons.rawItems, applySmearing);
    lepHelper.fillLepJetPtRatio(tightLoosePreselectedMuons.rawItems, jetsForLepMVA.rawItems, applySmearing);
    lepHelper.fillLepJetPtRatio(tightLoosePreselectedElectrons.rawItems, jetsForLepMVA.rawItems, applySmearing);
    lepHelper.fillLepJetDeltaR(tightLoosePreselectedMuons.rawItems, jetsForLepMVA.rawItems, applySmearing);
    lepHelper.fillLepJetDeltaR(tightLoosePreselectedElectrons.rawItems, jetsForLepMVA.rawItems, applySmearing);
    lepHelper.fillLepJetBTagCSV(tightLoosePreselectedMuons.rawItems, jetsForLepMVA.rawItems);
    lepHelper.fillLepJetBTagCSV(tightLoosePreselectedElectrons.rawItems, jetsForLepMVA.rawItems);

    auto electronPt10 = [] (BNelectron e) { return (e.pt > 10); };
    tightLoosePreselectedElectrons.keepSelectedParticles(electronPt10);
    auto muonPt10 = [] (BNmuon m) { return (m.pt > 10); };
    tightLoosePreselectedMuons.keepSelectedParticles(muonPt10);
    
    tightLoosePreselectedElectrons.keepSelectedParticles(electronPreselectedID);
    tightElectrons.initializeRawItems(tightLoosePreselectedElectrons.rawItems);
    tightElectrons.keepSelectedParticles(electronTightID);
    tightLooseElectrons.initializeRawItems(tightLoosePreselectedElectrons.rawItems);
    tightLooseElectrons.keepSelectedParticles(electronLooseID);
    looseElectrons.initializeRawItems(tightLoosePreselectedElectrons.rawItems);
    looseElectrons.keepSelectedDifference(electronLooseID, electronTightID);
    preselectedElectrons.initializeRawItems(tightLoosePreselectedElectrons.rawItems);
    preselectedElectrons.keepSelectedDifference(electronPreselectedID, electronLooseID);
    loosePreselectedElectrons.initializeRawItems(tightLoosePreselectedElectrons.rawItems);
    loosePreselectedElectrons.addUnion({looseElectrons.items, preselectedElectrons.items});

    tightLoosePreselectedMuons.keepSelectedParticles(muonPreselectedID);
    tightMuons.initializeRawItems(tightLoosePreselectedMuons.rawItems);
    tightMuons.keepSelectedParticles(muonTightID);
    looseMuons.initializeRawItems(tightLoosePreselectedMuons.rawItems);
    looseMuons.keepSelectedDifference(muonLooseID, muonTightID);
    preselectedMuons.initializeRawItems(tightLoosePreselectedMuons.rawItems);
    preselectedMuons.keepSelectedDifference(muonPreselectedID, muonLooseID);
    tightLooseMuons.initializeRawItems(tightLoosePreselectedMuons.rawItems);
    tightLooseMuons.keepSelectedParticles(muonLooseID);
    
    // Require reset before first pushback to avoid keeping leptons from previous event
    tightLeptons.resetAndPushBack(tightElectrons.items);
    tightLeptons.pushBackAndSort(tightMuons.items);
    tightLooseLeptons.resetAndPushBack(tightLooseElectrons.items);
    tightLooseLeptons.pushBackAndSort(tightLooseMuons.items);
    tightLoosePreselectedLeptons.resetAndPushBack(tightLoosePreselectedElectrons.items);
    tightLoosePreselectedLeptons.pushBackAndSort(tightLoosePreselectedMuons.items);

    tightLoosePreselectedTaus.keepSelectedParticles(tauPreselectedID);
    tightTaus.initializeRawItems(tightLoosePreselectedTaus.rawItems);
    tightTaus.keepSelectedParticles(tauTightID);
    tightLooseTaus.initializeRawItems(tightLoosePreselectedTaus.rawItems);
    tightLooseTaus.keepSelectedParticles(tauLooseID);
    
    jets.initializeRawItemsSortedByPt(ev, "BNproducer","selectedPatJetsPFlow");
    jets.correctRawJets(jetSyst);
    // comment out for ttbar_lj or ttbar_ll
    jets.cleanJets(tightLoosePreselectedLeptons.items);
//     // cleanJets for ttbar_lj or ttbar_ll
//     jets.cleanJets(tightLeptons.items);
    jets.keepSelectedJets(25.0, 2.4, jetID::jetLoose, '-');
    jetsByCSV.initializeRawItemsSortedByCSV(jets.items);
    looseCSVJets.initializeRawItems(jets.rawItems);
    looseCSVJets.keepSelectedJets(25.0, 2.4, jetID::jetLoose, 'L');
    mediumCSVJets.initializeRawItems(jets.rawItems);
    mediumCSVJets.keepSelectedJets(25.0, 2.4, jetID::jetLoose, 'M');
    tightCSVJets.initializeRawItems(jets.rawItems);
    tightCSVJets.keepSelectedJets(25.0, 2.4, jetID::jetLoose, 'T');
    notLooseCSVJets.initializeRawItems(beanHelper->GetDifference(jets.items, looseCSVJets.items));

    met.initializeRawItems(ev, "BNproducer", "patMETsPFlow");
    met.getCorrectedMet(jets);
    events.initializeRawItems(ev, "BNproducer", "");
    mcParticles.initializeRawItems(ev, "BNproducer", "MCstatus3");
    primaryVertexes.initializeRawItems(ev, "BNproducer","offlinePrimaryVertices");
    hltCollection.initializeRawItems(ev, "BNproducer", "HLT");

//     genHiggs.initializeRawItems(mcParticles.rawItems);
//     auto higgsPDGID = [] (BNmcparticle p) { return (p.id == 25); };
//     genHiggs.keepSelectedParticles(higgsPDGID);

//     genTops.initializeRawItems(mcParticles.rawItems);
//     auto topPDGID = [] (BNmcparticle p) { return (p.id == 6); };
//     genTops.keepSelectedParticles(topPDGID);

//     genAntiTops.initializeRawItems(mcParticles.rawItems);
//     auto antiTopPDGID = [] (BNmcparticle p) { return (p.id == -6); };
//     genAntiTops.keepSelectedParticles(antiTopPDGID);

    genWFromTops.initializeRawItems(mcParticles.rawItems);
    auto WFromTopPDGID = [] (BNmcparticle p) { return (p.id == 24 && p.motherId == 6); };
    genWFromTops.keepSelectedParticles(WFromTopPDGID);
    
    genWFromAntiTops.initializeRawItems(mcParticles.rawItems);
    auto WFromAntiTopPDGID = [] (BNmcparticle p) { return (p.id == -24 && p.motherId == -6); };
    genWFromAntiTops.keepSelectedParticles(WFromAntiTopPDGID);

    // Initialize SFOS pair closest to Z mass
    myZLikeMassLepLepSFOSAll.reset();
    myZLikeMassLepLepSFOSAll.evaluate();
    
    tightLoosePreselectedZLeptons.resetAndPushBack(myZLikeMassLepLepSFOSAll.selectedParticles1);
    tightLoosePreselectedZLeptons.pushBack(myZLikeMassLepLepSFOSAll.selectedParticles2);

//     tightNonZLeptons.initializeRawItems(beanHelper->GetDifference(tightLeptons.items, tightZLeptons.items));
//     tightLooseNonZLeptons.initializeRawItems(beanHelper->GetDifference(tightLooseLeptons.items, tightLooseZLeptons.items));
    tightLoosePreselectedNonZLeptons.initializeRawItems(beanHelper->GetDifference(tightLoosePreselectedLeptons.items, tightLoosePreselectedZLeptons.items));

    leptonsFromW.resetAndPushBack(tightLoosePreselectedLeptons.items);
    auto leptonFromGenW = [] (BNlepton l) { return (abs(l.genMotherId) == 24 || (abs(l.genMotherId) == 15 && abs(l.genGrandMother00Id) == 24)); };
    leptonsFromW.keepSelectedParticles(leptonFromGenW);

    leptonsFromZ.resetAndPushBack(tightLoosePreselectedLeptons.items);
    auto leptonFromGenZ = [] (BNlepton l) { return ((l.genMotherId == 23) || (abs(l.genMotherId) == 15 && abs(l.genGrandMother00Id) == 23)); };
    leptonsFromZ.keepSelectedParticles(leptonFromGenZ);
    
    float gen_W_from_top_daughter0PT = KinematicVariableConstants::FLOAT_INIT;
    float gen_W_from_top_daughter1PT = KinematicVariableConstants::FLOAT_INIT;
    float gen_W_from_antiTop_daughter0PT = KinematicVariableConstants::FLOAT_INIT;
    float gen_W_from_antiTop_daughter1PT = KinematicVariableConstants::FLOAT_INIT;
    if (genWFromTops.items.size() == 1) gen_W_from_top_daughter0PT = genWFromTops.items.at(0).daughter0PT;
    if (genWFromTops.items.size() == 1) gen_W_from_top_daughter1PT = genWFromTops.items.at(0).daughter1PT;
    if (genWFromAntiTops.items.size() == 1) gen_W_from_antiTop_daughter0PT = genWFromAntiTops.items.at(0).daughter0PT;
    if (genWFromAntiTops.items.size() == 1) gen_W_from_antiTop_daughter1PT = genWFromAntiTops.items.at(0).daughter1PT;

    leptonsFromTop.resetAndPushBack(tightLoosePreselectedLeptons.items);
    auto leptonFromGenTop = [] (BNlepton l, float x, float y) { return ( (l.genMotherId == 24 && l.genGrandMother00Id == 6) ||
                                                                         (l.genMotherId == -15 && l.genGrandMother00Id == 24 &&
                                                                          ( abs(l.genMotherPT - x) < 10 || abs(l.genMotherPT - y) < 10)) ) ; };
    leptonsFromTop.keepSelectedParticles(leptonFromGenTop, gen_W_from_top_daughter0PT, gen_W_from_top_daughter1PT);
    
    leptonsFromAntiTop.resetAndPushBack(tightLoosePreselectedLeptons.items);
    auto leptonFromGenAntiTop = [] (BNlepton l, float x, float y) { return ( (l.genMotherId == -24 && l.genGrandMother00Id == -6) ||
                                                                             (l.genMotherId == 15 && l.genGrandMother00Id == -24 &&
                                                                              (abs(l.genMotherPT - x) < 10 || abs(l.genMotherPT - y) < 10)) ) ; };
    leptonsFromAntiTop.keepSelectedParticles(leptonFromGenAntiTop, gen_W_from_antiTop_daughter0PT, gen_W_from_antiTop_daughter1PT);
    
    leptonsFromBFromTop.resetAndPushBack(tightLoosePreselectedLeptons.items);
    auto leptonFromBFromGenTop = [] (BNlepton l) { return (abs(l.genMotherId) > 100 && l.tkCharge == -1) ; };
    leptonsFromBFromTop.keepSelectedParticles(leptonFromBFromGenTop);
    
    leptonsFromBFromAntiTop.resetAndPushBack(tightLoosePreselectedLeptons.items);
    auto leptonFromBFromGenAntiTop = [] (BNlepton l) { return (abs(l.genMotherId) > 100 && l.tkCharge == 1) ; };
    leptonsFromBFromAntiTop.keepSelectedParticles(leptonFromBFromGenAntiTop);
    
    leptonsFromNP.resetAndPushBack(tightLoosePreselectedLeptons.items);
    auto leptonFromGenNP = [] (BNlepton l) { return (abs(l.genMotherId) > 100) ; };
    leptonsFromNP.keepSelectedParticles(leptonFromGenNP);

    int sum_lep_charge = KinematicVariableConstants::INT_INIT;
    if (tightLoosePreselectedLeptons.items.size() >= 3) {
      sum_lep_charge = tightLoosePreselectedLeptons.items.at(0)->tkCharge+
        tightLoosePreselectedLeptons.items.at(1)->tkCharge+
        tightLoosePreselectedLeptons.items.at(2)->tkCharge; }

    //Leptons with the same and opposite charges
    leptonsSS.resetAndPushBack(tightLoosePreselectedLeptons.items);
    auto leptonSS = [] (BNlepton l, int i) { return (l.tkCharge == i); };
    leptonsSS.keepSelectedParticles(leptonSS, sum_lep_charge);
    leptonsOS.resetAndPushBack(tightLoosePreselectedLeptons.items);
    auto leptonOS = [] (BNlepton l, int i) { return (l.tkCharge == -1*i); };
    leptonsOS.keepSelectedParticles(leptonOS, sum_lep_charge);
    
    jetsFromW.initializeRawItems(jetsByCSV.items);
    auto jetFromGenW = [] (BNjet j) { return (abs(j.genPartonMotherId) == 24); };
    jetsFromW.keepSelectedParticles(jetFromGenW);

    int gen_W_lep_charge = KinematicVariableConstants::INT_INIT;
    if (leptonsFromW.items.size() >= 1) gen_W_lep_charge = leptonsFromW.items.at(0)->tkCharge;

    jetsFromLepTop.initializeRawItems(jets.items);
    auto jetFromGenLepTop = [] (BNjet j, int i) { return (j.genPartonMotherId == 6*i); };
    jetsFromLepTop.keepSelectedParticles(jetFromGenLepTop, gen_W_lep_charge);

    jetsFromHadTop.initializeRawItems(jets.items);
    auto jetFromGenHadTop = [] (BNjet j, int i) { return (j.genPartonMotherId == -6*i); };
    jetsFromHadTop.keepSelectedParticles(jetFromGenHadTop, gen_W_lep_charge);

    jetsFromTop.initializeRawItems(jetsByCSV.items);
    auto jetFromGenTop = [] (BNjet j) { return (j.genPartonMotherId == 6); };
    jetsFromTop.keepSelectedParticles(jetFromGenTop);

    jetsFromAntiTop.initializeRawItems(jetsByCSV.items);
    auto jetFromGenAntiTop = [] (BNjet j) { return (j.genPartonMotherId == -6); };
    jetsFromAntiTop.keepSelectedParticles(jetFromGenAntiTop);


    // reset all the vars
    if (debug > 9) cout << "Resetting "  << endl;
    for (vector<ArbitraryVariable*>::iterator iVar = kinVars.begin();
         iVar != kinVars.end();
         iVar++) {

      (*iVar)->reset();
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
    passAllCuts = passAllCuts;

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

      if (debug > 9) (*iVar)->print();
      if (debug > 9) std::cout << "" << std::endl;
      (*iVar)->evaluate();
      if (debug > 9) (*iVar)->print();
      if (debug > 9) std::cout << "" << std::endl;
    }

    getNumExtraPartons(beanHelper, mcParticles.items, numExtraPartons);
    if (myConfig.sampleName.find("_0p") != std::string::npos) { //0 parton samples
    //Cut to require 0 partons
      if (numExtraPartons != 0) {
        numEventsFailCuts++;
        numEventsPassCuts--;
        continue;
      }
    }

    if (myConfig.sampleName.find("wz_") != std::string::npos || myConfig.sampleName.find("zz_") != std::string::npos) { //diboson samples
      dibosonPlusHFKeepEventFunction(beanHelper, mcParticles.items, jets.rawItems, dibosonPlusHFKeepEventBool);
      if (!dibosonPlusHFKeepEventBool) {
        numEventsFailCuts++;
        numEventsPassCuts--;
        continue; //Don't go on to fill tree with this event
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
