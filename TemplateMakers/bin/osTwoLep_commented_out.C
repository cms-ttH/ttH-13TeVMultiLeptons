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

// void LeptonVarsThisAnalysis(BNmuonCollection& tightMuons, BNmuonCollection& tightLooseMuons,
//                             BNelectronCollection& tightElectrons, BNelectronCollection& tightLooseElectrons,
//                             int & TwoMuon, int & TwoElectron, int & MuonElectron, int & PassTwoLepton) {

//     //Collection definitions set by muonID::muonID and electronID::electronID inside main function
//     unsigned numTightMuons = tightMuons.size();
//     unsigned numTightElectrons = tightElectrons.size();
//     unsigned numTightLooseMuons = tightLooseMuons.size();
//     unsigned numTightLooseElectrons = tightLooseElectrons.size();

//     TwoMuon = 0; TwoElectron = 0; MuonElectron = 0; PassTwoLepton = 0;

//     if ( numTightMuons >= 1 && numTightLooseMuons == 2 && numTightLooseElectrons == 0 ) TwoMuon = 1;
//     if ( numTightElectrons >= 1 && numTightLooseElectrons == 2 && numTightLooseMuons == 0 ) TwoElectron = 1;
//     if ( ( numTightMuons + numTightElectrons ) >= 1 && numTightLooseMuons == 1 && numTightLooseElectrons == 1 ) MuonElectron = 1;
//     if ( TwoMuon + TwoElectron + MuonElectron == 1 ) PassTwoLepton = 1;

//     return;
// }

// void getNumExtraPartons(BEANhelper * beanHelper, BNmcparticleCollection& mcParticles, int & numExtraPartons) {

//   numExtraPartons = beanHelper->GetNumExtraPartons(mcParticles);

//   return;
// } 
  
// void ttPlusHFKeepEventFunction(BEANhelper * beanHelper, BNmcparticleCollection& mcParticles,
//                                BNjetCollection& jets, bool & ttPlusHFKeepEventBool) {

//   ttPlusHFKeepEventBool = beanHelper->ttPlusHFKeepEvent(mcParticles,
//                                                         jets);

//   return;
// } 
  
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

  // setup the analysis
  // it comes from the lepHelper
  BEANhelper * beanHelper = lepHelper.setupAnalysisParameters("2012_53x", myConfig.sampleName);

  sysType::sysType jetSyst = sysType::NA;
  if (myConfig.jetSyst == "NA") jetSyst = sysType::NA;
  else if (myConfig.jetSyst == "JESUp") jetSyst = sysType::JESup;
  else if (myConfig.jetSyst == "JESDown") jetSyst = sysType::JESdown;
  else std::cout << "No valid JES corrections specified - using nominal" << std::endl;

  // ---------------------------------------------
  // Note for future development: should these be
  // saved inside the lepHelper somewhere?
  // For now they are ok here
  // ---------------------------------------------

  muonID::muonID muonTightID = muonID::muonTight;
  muonID::muonID muonLooseID = muonID::muonLoose;
  muonID::muonID muonPreselectedID = muonID::muonNoCuts;
  electronID::electronID electronTightID = electronID::electronTight;
  electronID::electronID electronLooseID = electronID::electronLoose;
  electronID::electronID electronPreselectedID = electronID::electronNoCuts;
  tauID::tauID tauTightID = tauID::tauMedium;
  //  tauID::tauID tauLooseID = tauID::tauVLoose;
  tauID::tauID tauPreselectedID = tauID::tauNonIso;

  // collections
  GenericCollection<BNelectronCollection> tightElectrons(beanHelper);
//   GenericCollection<BNelectronCollection> looseElectrons(beanHelper);
//   GenericCollection<BNelectronCollection> preselectedElectrons(beanHelper);
  GenericCollection<BNelectronCollection> tightLooseElectrons(beanHelper);
//   GenericCollection<BNelectronCollection> loosePreselectedElectrons(beanHelper);
  GenericCollection<BNelectronCollection> tightLoosePreselectedElectrons(beanHelper);

  GenericCollection<BNmuonCollection> tightMuons(beanHelper);
//   GenericCollection<BNmuonCollection> looseMuons(beanHelper);
//   GenericCollection<BNmuonCollection> preselectedMuons(beanHelper);
  GenericCollection<BNmuonCollection> tightLooseMuons(beanHelper);
  GenericCollection<BNmuonCollection> tightLoosePreselectedMuons(beanHelper);

//   GenericCollection<BNleptonCollection> tightLeptons(beanHelper);
//   GenericCollection<BNleptonCollection> looseLeptons(beanHelper);
//   GenericCollection<BNleptonCollection> preselectedLeptons(beanHelper);
//   GenericCollection<BNleptonCollection> tightLooseLeptons(beanHelper);
//   GenericCollection<BNleptonCollection> tightLoosePreselectedLeptons(beanHelper);

// //   GenericCollection<BNleptonCollection> tightLooseLeptons_fromHiggs(beanHelper); //failed to get working 

//   GenericCollection<BNtauCollection> tightTaus(beanHelper);
//   GenericCollection<BNtauCollection> tightLooseTaus(beanHelper);
//   GenericCollection<BNtauCollection> tightLoosePreselectedTaus(beanHelper);

//   GenericCollection<BNjetCollection> jets(beanHelper);
//   GenericCollection<BNjetCollection> jets_30(beanHelper);
//   GenericCollection<BNjetCollection> jetsByCSV(beanHelper);
//   GenericCollection<BNjetCollection> looseCSVJets(beanHelper);
//   GenericCollection<BNjetCollection> mediumCSVJets(beanHelper);
//   GenericCollection<BNjetCollection> notMediumCSVJets(beanHelper);

//   GenericCollection<BNjetCollection> jets_fromHiggs(beanHelper);
//   GenericCollection<BNjetCollection> jets_fromHiggs_30(beanHelper);

//   GenericCollection<BNmetCollection> met(beanHelper);
//   GenericCollection<BNprimaryvertexCollection> primaryVertexes(beanHelper);
//   GenericCollection<BNtriggerCollection> hltCollection(beanHelper);
//   GenericCollection<BNeventCollection> events(beanHelper);
//   GenericCollection<BNmcparticleCollection> mcParticles(beanHelper);

//   GenericCollection<BNmcparticleCollection> genHiggsParticles(beanHelper);
//   GenericCollection<BNmcparticleCollection> genTopParticles(beanHelper);
//   GenericCollection<BNmcparticleCollection> genAntiTopParticles(beanHelper);

  // declare your kinematic variables that you want
  // to be written out into the tree
  vector<ArbitraryVariable*> kinVars;
  vector<ArbitraryVariable*> cutVars;


//   GenericCollectionSizeVariable<BNjetCollection>
//     numJets(&(jets.ptrToItems), "numJets");
//   kinVars.push_back(&numJets);
//   numJets.setCutMin(2);
//   cutVars.push_back(&numJets);

//   GenericCollectionSizeVariable<BNjetCollection>
//     numJets_30(&(jets_30.ptrToItems), "numJets_30");
//   kinVars.push_back(&numJets_30);

//   GenericCollectionSizeVariable<BNjetCollection>
//     numJets_fromHiggs(&(jets_fromHiggs.ptrToItems), "numJets_fromHiggs");
//   kinVars.push_back(&numJets_fromHiggs);

//   GenericCollectionSizeVariable<BNjetCollection>
//     numJets_fromHiggs_30(&(jets_fromHiggs_30.ptrToItems), "numJets_fromHiggs_30");
//   kinVars.push_back(&numJets_fromHiggs_30);

//   GenericCollectionSizeVariable<BNjetCollection>
//     numMediumBJets(&(mediumCSVJets.ptrToItems), "numMediumBJets");
//   kinVars.push_back(&numMediumBJets);

//   GenericCollectionSizeVariable<BNjetCollection>
//     numLooseBJets(&(looseCSVJets.ptrToItems), "numLooseBJets");
//   kinVars.push_back(&numLooseBJets);
  
//   GenericCollectionSizeVariable<BNleptonCollection>
//     numTightLooseLeptons(&(tightLooseLeptons.ptrToItems), "numTightLooseLeptons");
//   kinVars.push_back(&numTightLooseLeptons);
//   numTightLooseLeptons.setCutMin(2);
//   cutVars.push_back(&numTightLooseLeptons);

//   GenericCollectionSizeVariable<BNleptonCollection>
//     numAllLeptons(&(tightLoosePreselectedLeptons.ptrToItems), "numAllLeptons");
//   kinVars.push_back(&numAllLeptons);

//   GenericCollectionSizeVariable<BNleptonCollection>
//     numTightLeptons(&(tightLeptons.ptrToItems), "numTightLeptons");
//   kinVars.push_back(&numTightLeptons);
//   numTightLeptons.setCutMin(1);
//   cutVars.push_back(&numTightLeptons);

//   GenericCollectionSizeVariable<BNmuonCollection>
//     numTightMuons(&(tightMuons.ptrToItems), "numTightMuons");
//   kinVars.push_back(&numTightMuons);

//   GenericCollectionSizeVariable<BNelectronCollection>
//     numTightElectrons(&(tightElectrons.ptrToItems), "numTightElectrons");
//   kinVars.push_back(&numTightElectrons);

//   CSVWeights
//     myCSV(beanHelper, &(jets.ptrToItems), jetSyst);
//   kinVars.push_back(&myCSV);

//   PUWeights
//     myPU(&lepHelper, &(events.ptrToItems));
//   kinVars.push_back(&myPU);

//   TopPtWeights
//     myTopPt(&lepHelper, &(mcParticles.ptrToItems));
//   kinVars.push_back(&myTopPt);

//   LeptonIDAndIsoScaleFactors
//     myLepIDAndIsoSF(&lepHelper, muonTightID, muonLooseID, electronTightID, electronLooseID,
//                     &(tightMuons.ptrToItems), &(looseMuons.ptrToItems),
//                     &(tightElectrons.ptrToItems), &(looseElectrons.ptrToItems));
//   kinVars.push_back(&myLepIDAndIsoSF);
  
//   LeptonTriggerScaleFactors
//     myLepTrig(&lepHelper, &(tightMuons.ptrToItems), &(looseMuons.ptrToItems), &(preselectedMuons.ptrToItems),
//               &(tightElectrons.ptrToItems), &(looseElectrons.ptrToItems), &(preselectedElectrons.ptrToItems));
//   kinVars.push_back(&myLepTrig);
  
//   CleanEventVars
//     myClean(&lepHelper, &(events.ptrToItems), &(primaryVertexes.ptrToItems));
//   kinVars.push_back(&myClean);
  
//   CheckTwoLepTrigger
//     checkTrig(&lepHelper, &(hltCollection.ptrToItems));
//   kinVars.push_back(&checkTrig);
  
//   //DBCorrectedRelIsoDR04s myDBCorrectedRelIsoDR04s(&lepHelper, 2);
//   //kinVars.push_back(&myDBCorrectedRelIsoDR04s);
 
//    HiggsDecayType
//     myHiggsDecayType(&lepHelper, &(mcParticles.ptrToItems));
//   kinVars.push_back(&myHiggsDecayType);
  
//   TwoObjectKinematic<BNleptonCollection,BNleptonCollection>
//     myMassLepLep("mass", "min", "mass_leplep",
//                  &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 99,
//                  &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 99);
//   kinVars.push_back(&myMassLepLep);
  
//   TwoObjectKinematic<BNleptonCollection,BNleptonCollection>
//     myZmass("mass", "closest_to", "Zmass",
//             &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 99,
//             &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 99,
//             91.2, "same_flavour");
//   kinVars.push_back(&myZmass);
  
//   TwoObjectKinematic<BNleptonCollection,BNleptonCollection>
//     myDeltaRLepLep("deltaR", "min", "dR_leplep",
//                    &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 99,
//                    &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 99);
//   kinVars.push_back(&myDeltaRLepLep);

//   TwoObjectKinematic<BNleptonCollection,BNleptonCollection>
//     myDeltaPhiLepLep("deltaPhi", "min", "dPhi_leplep",
//                    &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 99,
//                    &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 99);
//   kinVars.push_back(&myDeltaPhiLepLep);
  
//   TwoObjectKinematic<BNleptonCollection,BNjetCollection>
//     myMHT("pt", "vector_sum", "mht",
//           &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 99,
//           &(jets.ptrToItems), "jets_by_pt", 1, 99);
//   kinVars.push_back(&myMHT);

//   ////////// Variables for BDT //////////
  
//   TwoObjectKinematic<BNjetCollection,BNjetCollection>
//     myMinDrJets("deltaR", "min", "min_dr_jets",
//                 &(jets.ptrToItems), "jets_by_pt", 1, 99,
//                 &(jets.ptrToItems), "jets_by_pt", 1, 99);
//   kinVars.push_back(&myMinDrJets);
  
//   TwoObjectKinematic<BNleptonCollection,BNjetCollection>
//     mySumPt("pt", "sum", "sum_pt",
//             &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 99,
//             &(jets.ptrToItems), "jets_by_pt", 1, 99);
//   kinVars.push_back(&mySumPt);

//   TwoObjectKinematic<BNjetCollection,BNjetCollection>
//     mySumJetPt("pt", "sum", "sum_jet_pt",
//                &(jets.ptrToItems), "jets_by_pt", 1, 99,
//                &(jets.ptrToItems), "jets_by_pt", 1, 99);
//   kinVars.push_back(&mySumJetPt);

//   TwoObjectKinematic<BNjetCollection,BNjetCollection>
//     mySumJetMass("mass", "vector_sum", "sum_jet_mass",
//                  &(jets.ptrToItems), "jets_by_pt", 1, 99,
//                  &(jets.ptrToItems), "jets_by_pt", 1, 99);
//   kinVars.push_back(&mySumJetMass);

//   TwoObjectKinematic<BNjetCollection,BNjetCollection>
//     mySumNonTaggedJetMass("mass", "vector_sum", "sum_non_tagged_jet_mass",
//                           &(notMediumCSVJets.ptrToItems), "untagged_jets_by_pt", 1, 99,
//                           &(notMediumCSVJets.ptrToItems), "untagged_jets_by_pt", 1, 99);
//   kinVars.push_back(&mySumNonTaggedJetMass);

//   TwoObjectKinematic<BNjetCollection,BNjetCollection>
//     myWLikeDijetMass81("mass", "closest_to", "WLike_dijet_mass",
//                        &(notMediumCSVJets.ptrToItems), "untagged_jets_by_pt", 1, 99,
//                        &(notMediumCSVJets.ptrToItems), "untagged_jets_by_pt", 1, 99,
//                        81);
//   kinVars.push_back(&myWLikeDijetMass81);

//   TwoObjectKinematic<BNjetCollection,BNjetCollection>
//     myDeltaPhiJets_FromHiggs("deltaPhi", "min", "dPhi_jets_fromHiggs",
//                              &(jets_fromHiggs.ptrToItems), "jets_fromHiggs_by_pt", 1, 99,
//                              &(jets_fromHiggs.ptrToItems), "jets_fromHiggs_by_pt", 1, 99);
//   kinVars.push_back(&myDeltaPhiJets_FromHiggs);
  
//   TwoObjectKinematic<BNjetCollection,BNjetCollection>
//     myDeltaRJets_FromHiggs("deltaR", "min", "dR_jets_fromHiggs",
//                            &(jets_fromHiggs.ptrToItems), "jets_fromHiggs_by_pt", 1, 99,
//                            &(jets_fromHiggs.ptrToItems), "jets_fromHiggs_by_pt", 1, 99);
//   kinVars.push_back(&myDeltaRJets_FromHiggs);
  
//   TwoObjectKinematic<BNmetCollection,BNleptonCollection>
//     myDeltaPhiMetLep1("deltaPhi", "min", "dPhi_met_lep1",
//                       &(met.ptrToItems), "met", 1, 1,
//                       &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 1);
//   kinVars.push_back(&myDeltaPhiMetLep1);
  
//   TwoObjectKinematic<BNmetCollection,BNleptonCollection>
//     myDeltaPhiMetLep2("deltaPhi", "min", "dPhi_met_lep2",
//                       &(met.ptrToItems), "met", 1, 1,
//                       &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 2, 2);
//   kinVars.push_back(&myDeltaPhiMetLep2);

//   TwoObjectKinematic<BNmetCollection,BNjetCollection>
//     myMinDeltaPhiMetJet("deltaPhi", "min", "min_dPhi_metjet",
//                         &(met.ptrToItems), "met", 1, 99,
//                         &(jets.ptrToItems), "jets_by_pt", 1, 99);
//   kinVars.push_back(&myMinDeltaPhiMetJet);

//   TwoObjectKinematic<BNmetCollection,BNjetCollection>
//     myMaxDeltaPhiMetJet("deltaPhi", "max", "max_dPhi_metjet",
//                         &(met.ptrToItems), "met", 1, 99,
//                         &(jets.ptrToItems), "jets_by_pt", 1, 99);
//   kinVars.push_back(&myMaxDeltaPhiMetJet);
  
//   TwoObjectKinematic<BNmetCollection,BNjetCollection>
//     myMinDeltaPhiMetJet_fromHiggs("deltaPhi", "min", "min_dPhi_metjet_fromHiggs",
//                         &(met.ptrToItems), "met", 1, 99,
//                         &(jets_fromHiggs.ptrToItems), "jets_fromHiggs_by_pt", 1, 99);
//   kinVars.push_back(&myMinDeltaPhiMetJet_fromHiggs);

//   TwoObjectKinematic<BNmetCollection,BNjetCollection>
//     myMaxDeltaPhiMetJet_fromHiggs("deltaPhi", "max", "max_dPhi_metjet_fromHiggs",
//                         &(met.ptrToItems), "met", 1, 99,
//                         &(jets_fromHiggs.ptrToItems), "jets_by_pt", 1, 99);
//   kinVars.push_back(&myMaxDeltaPhiMetJet_fromHiggs);

//   ThreeObjectKinematic<BNleptonCollection, BNleptonCollection, BNmetCollection>
//     myMassMetLepLep("mass", "min", "mass_met_leplep",
//                     &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 1,
//                     &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 2, 2,
//                     &(met.ptrToItems), "met", 1, 1);
//   kinVars.push_back(&myMassMetLepLep);
  
//   ThreeObjectKinematic<BNleptonCollection, BNleptonCollection, BNmetCollection>
//     myMTMetLepLep("MT", "min", "MT_met_leplep",
//                     &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 1,
//                     &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 2, 2,
//                     &(met.ptrToItems), "met", 1, 1);
//   kinVars.push_back(&myMTMetLepLep);
  
//   ThreeObjectKinematic<BNleptonCollection, BNleptonCollection, BNmetCollection>
//     myDeltaRMetLepLep("deltaR", "min", "dR_met_leplep",
//                       &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 1,
//                       &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 2, 2,
//                       &(met.ptrToItems), "met", 1, 1);
//   kinVars.push_back(&myDeltaRMetLepLep);
  
//   ThreeObjectKinematic<BNleptonCollection, BNleptonCollection, BNmetCollection>
//     myDeltaPhiMetLepLep("deltaPhi", "min", "dPhi_met_leplep",
//                         &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 1,
//                         &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 2, 2,
//                         &(met.ptrToItems), "met", 1, 1);
//   kinVars.push_back(&myDeltaPhiMetLepLep);
  
//   TwoObjectKinematic<BNjetCollection,BNjetCollection>
//     myGenHiggsDijetMass("mass", "min", "genHiggs_dijet_mass",
//                         &(jets_fromHiggs.ptrToItems), "jets_by_pt", 1, 1,
//                         &(jets_fromHiggs.ptrToItems), "jets_by_pt", 2, 2);
//   kinVars.push_back(&myGenHiggsDijetMass);
  
//   TwoObjectKinematic<BNjetCollection,BNjetCollection>
//     myHiggsLikeDijetMass("mass", "closest_to", "higgsLike_dijet_mass",
//                          &(jets.ptrToItems), "jets_by_pt", 1, 99,
//                          &(jets.ptrToItems), "jets_by_pt", 1, 99,
//                          115.0);
//   kinVars.push_back(&myHiggsLikeDijetMass);
  
//   TwoObjectKinematic<BNjetCollection,BNjetCollection>
//     myHiggsLikeDijetMass2("mass", "second_closest_to", "higgsLike_dijet_mass2",
//                           &(jets.ptrToItems), "jets_by_pt", 1, 99,
//                           &(jets.ptrToItems), "jets_by_pt", 1, 99,
//                           115.0);
//   kinVars.push_back(&myHiggsLikeDijetMass2);

//   TwoObjectKinematic<BNjetCollection,BNjetCollection>
//     myNumJetsFloat("eta", "num_within", "numJets_float",
//                    &(jets.ptrToItems), "jets_by_pt", 1, 99,
//                    &(jets.ptrToItems), "jets_by_pt", 1, 99,
//                    0.0, "", "", 5.0);
//   kinVars.push_back(&myNumJetsFloat);

//   TwoObjectKinematic<BNjetCollection,BNjetCollection>
//     myNumHiggsLikeDijet15("mass", "num_within", "numHiggsLike_dijet_15_float",
//                           &(jets.ptrToItems), "jets_by_pt", 1, 99,
//                           &(jets.ptrToItems), "jets_by_pt", 1, 99,
//                           115.0, "", "", 15.0);
//   kinVars.push_back(&myNumHiggsLikeDijet15);
  
//   TwoJetVariables
//     myAvgBtagDiscBtags("CSV", "avg", "avg_btag_disc_btags",
//                        &(mediumCSVJets.ptrToItems), "medium_bjets_by_pt", 1, 99,
//                        &(mediumCSVJets.ptrToItems), "medium_bjets_by_pt", 1, 99);
//   kinVars.push_back(&myAvgBtagDiscBtags);
  
//   TwoJetVariables
//     myAvgBtagDiscNonBtags("CSV", "avg", "avg_btag_disc_non_btags",
//                           &(notMediumCSVJets.ptrToItems), "not_medium_bjets_by_pt", 1, 99,
//                           &(notMediumCSVJets.ptrToItems), "not_medium_bjets_by_pt", 1, 99);
//   kinVars.push_back(&myAvgBtagDiscNonBtags);

//   ////////// all leptons //////////
//   GenericCollectionMember<double, BNleptonCollection>
//     allLeptonPt(Reflex::Type::ByName("BNlepton"), &(tightLooseLeptons.ptrToItems),
//                 "pt", "leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&allLeptonPt);
  
//   GenericCollectionMember<double, BNleptonCollection>
//     allLeptonEta(Reflex::Type::ByName("BNlepton"), &(tightLooseLeptons.ptrToItems),
//                  "eta", "leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&allLeptonEta);
  
//   GenericCollectionMember<int, BNleptonCollection>
//     allLeptonTkCharge(Reflex::Type::ByName("BNlepton"), &(tightLooseLeptons.ptrToItems),
//                       "tkCharge", "leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
//   kinVars.push_back(&allLeptonTkCharge);

//   GenericCollectionMember<int, BNleptonCollection>
//     allLeptonGenMotherId(Reflex::Type::ByName("BNlepton"), &(tightLooseLeptons.ptrToItems),
//                          "genMotherId", "leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
//   kinVars.push_back(&allLeptonGenMotherId);

//   GenericCollectionMember<int, BNleptonCollection>
//     allLeptonGenGrandMotherId(Reflex::Type::ByName("BNlepton"), &(tightLooseLeptons.ptrToItems),
//                               "genGrandMother00Id", "leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
//   kinVars.push_back(&allLeptonGenGrandMotherId);
  
  // NECESSARY TO FILL LEPTON VALUES - DO NOT COMMENT OUT //
  GenericCollectionMember<double, BNmuonCollection>
    allMuonPt(Reflex::Type::ByName("BNmuon"), &(tightLooseMuons.ptrToItems),
              "pt", "muons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allMuonPt);
  
  GenericCollectionMember<double, BNelectronCollection>
    allElectronPt(Reflex::Type::ByName("BNelectron"), &(tightLooseElectrons.ptrToItems),
                  "pt", "electrons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allElectronPt);
  
  ////////// all jets //////////
//   GenericCollectionMember<double, BNjetCollection>
//     allJetPt(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems),
//              "pt", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&allJetPt);

//   GenericCollectionMember<double, BNjetCollection>
//     allJetEta(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems),
//               "eta", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&allJetEta);

//   GenericCollectionMember<double, BNjetCollection>
//     allJetCSV(Reflex::Type::ByName("BNjet"),  &(jets.ptrToItems),
//               "btagCombinedSecVertex", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&allJetCSV);

//   ////////// met //////////
//   GenericCollectionMember<double, BNmetCollection>
//     metPt(Reflex::Type::ByName("BNmet"),  &(met.ptrToItems),
//           "pt", "met",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&metPt);

  ////////// manual variables //////////
//   int TwoMuon = 0;
//   int TwoElectron = 0;
//   int MuonElectron = 0;
//   int PassTwoLepton = 0;
//   Char_t *dataset = (Char_t *)lepHelper.dataset.c_str();

//   int sampleNumber = (int)lepHelper.sampleNumber;
//   double weight_Xsec = (double)lepHelper.weight_Xsec;
//   int nGen = (int)lepHelper.nGen;
//   double Xsec = (double)lepHelper.Xsec;
//   summaryTree->Branch("sampleNumber", &sampleNumber);
//   summaryTree->Branch("weight_Xsec", &weight_Xsec);
//   summaryTree->Branch("nGen", &nGen);
//   summaryTree->Branch("Xsec", &Xsec);

//   summaryTree->Branch("TwoMuon", &TwoMuon);
//   summaryTree->Branch("TwoElectron", &TwoElectron);
//   summaryTree->Branch("MuonElectron", &MuonElectron);
//   summaryTree->Branch("PassTwoLepton", &PassTwoLepton);
//   summaryTree->Branch("dataset", (void*)dataset, "dataset/C");

//   int numExtraPartons = -99;
//   summaryTree->Branch("numExtraPartons", &numExtraPartons);

  bool ttPlusHFKeepEventBool = false;
  
  ////////// event info //////////
//   GenericCollectionMember<unsigned, BNeventCollection>
//     runNumber(Reflex::Type::ByName("BNevent"), &(events.ptrToItems),
//               "run", "eventInfo",  KinematicVariableConstants::UINT_INIT, 1);
//   kinVars.push_back(&runNumber);

//   GenericCollectionMember<unsigned, BNeventCollection>
//     lumiBlock(Reflex::Type::ByName("BNevent"), &(events.ptrToItems),
//               "lumi", "eventInfo",  KinematicVariableConstants::UINT_INIT, 1);
//   kinVars.push_back(&lumiBlock);
  
  // this is a long inside BNevent
  // just using keyword long won't work
  // needs to be Long64_t 
//   GenericCollectionMember<Long64_t, BNeventCollection>
//     eventNumber(Reflex::Type::ByName("BNevent"),  &(events.ptrToItems),
//                 "evt", "eventInfo",  KinematicVariableConstants::INT_INIT, 1);
//   kinVars.push_back(&eventNumber);

  ////////// variables from functions //////////
//   PassZmask myPassZmask(&myZmass, &myMHT, &metPt);
//   kinVars.push_back(&myPassZmask);
//   myPassZmask.setCut("PassZmask_mht");
//   cutVars.push_back(&myPassZmask);

//  FinalBDT_OS_2012 myFinalBDT_OS_2012(&myMinDrJets, &mySumPt, &myAvgBtagDiscBtags, &myAvgBtagDiscNonBtags,
//                                      &myHiggsLikeDijetMass, &myHiggsLikeDijetMass2, &myNumJetsFloat, &myNumHiggsLikeDijet15);
//  kinVars.push_back(&myFinalBDT_OS_2012);

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


    /////////////////////////////////////////////////////////////
    //
    //    Initialize collections and apply object ids
    //
    //////////////////////////////////////////////////////////////   
    tightLoosePreselectedElectrons.initializeRawItemsSortedByPt(ev, "BNproducer","selectedPatElectronsPFlow");
    tightLoosePreselectedMuons.initializeRawItemsSortedByPt(ev, "BNproducer","selectedPatMuonsPFlow");
    
    tightLoosePreselectedElectrons.keepSelectedParticles(electronPreselectedID);
//     tightElectrons.initializeRawItems(tightLoosePreselectedElectrons.rawItems);
//     tightElectrons.keepSelectedParticles(electronTightID);
    tightLooseElectrons.initializeRawItems(tightLoosePreselectedElectrons.rawItems);
    tightLooseElectrons.keepSelectedParticles(electronLooseID);
//     looseElectrons.initializeRawItems(tightLoosePreselectedElectrons.rawItems);
//     looseElectrons.keepSelectedDifference(electronLooseID, electronTightID);
//     preselectedElectrons.initializeRawItems(tightLoosePreselectedElectrons.rawItems);
//     preselectedElectrons.keepSelectedDifference(electronPreselectedID, electronLooseID);
//     loosePreselectedElectrons.initializeRawItems(tightLoosePreselectedElectrons.rawItems);
//     loosePreselectedElectrons.addUnion({looseElectrons.items, preselectedElectrons.items});

    tightLoosePreselectedMuons.keepSelectedParticles(muonPreselectedID);
//     tightMuons.initializeRawItems(tightLoosePreselectedMuons.rawItems);
//     tightMuons.keepSelectedParticles(muonTightID);
//     looseMuons.initializeRawItems(tightLoosePreselectedMuons.rawItems);
//     looseMuons.keepSelectedDifference(muonLooseID, muonTightID);
//     preselectedMuons.initializeRawItems(tightLoosePreselectedMuons.rawItems);
//     preselectedMuons.keepSelectedDifference(muonPreselectedID, muonLooseID);
    tightLooseMuons.initializeRawItems(tightLoosePreselectedMuons.rawItems);
    tightLooseMuons.keepSelectedParticles(muonLooseID);

// // Require reset before first pushback to avoid keeping leptons from previous event
//     tightLeptons.resetAndPushBack(tightElectrons.items);
//     tightLeptons.pushBackAndSort(tightMuons.items);
//     looseLeptons.resetAndPushBack(looseElectrons.items);
//     looseLeptons.pushBackAndSort(looseMuons.items);
//     preselectedLeptons.resetAndPushBack(preselectedElectrons.items);
//     preselectedLeptons.pushBackAndSort(preselectedMuons.items);
//     tightLooseLeptons.resetAndPushBack(tightLooseElectrons.items);
//     tightLooseLeptons.pushBackAndSort(tightLooseMuons.items);
//     tightLoosePreselectedLeptons.resetAndPushBack(tightLoosePreselectedElectrons.items);
//     tightLoosePreselectedLeptons.pushBackAndSort(tightLoosePreselectedMuons.items);

//     tightTaus.initializeRawItemsSortedByPt(ev, "BNproducer","selectedPatTaus");
//     tightTaus.keepSelectedParticles(tauTightID);
//     tightLooseTaus.initializeRawItems(tightTaus.rawItems);
//     tightLooseTaus.keepSelectedParticles(tauTightID);
//     tightLoosePreselectedTaus.initializeRawItems(tightTaus.rawItems);
//     tightLoosePreselectedTaus.keepSelectedParticles(tauPreselectedID);

//     jets.initializeRawItemsSortedByPt(ev, "BNproducer","selectedPatJetsPFlow");
//     jets.cleanJets(tightLoosePreselectedLeptons.items);
//     jets.correctRawJets(jetSyst);
//     jets.keepSelectedJets(25.0, 2.4, jetID::jetLoose, '-');
//     jetsByCSV.initializeRawItemsSortedByCSV(jets.items);
//     looseCSVJets.initializeRawItems(jets.rawItems);
//     looseCSVJets.keepSelectedJets(25.0, 2.4, jetID::jetLoose, 'L');
//     mediumCSVJets.initializeRawItems(jets.rawItems);
//     mediumCSVJets.keepSelectedJets(25.0, 2.4, jetID::jetLoose, 'M');
//     notMediumCSVJets.initializeRawItems(beanHelper->GetDifference(jets.items, mediumCSVJets.items));

//     jets_30.initializeRawItems(jets.items);
//     jets_30.keepSelectedJets(30.0, 2.4, jetID::jetLoose, '-');
//     jets_fromHiggs.initializeRawItems(jets.items);
//     auto jetGenPartonMotherId = [] (BNjet j) { return (j.genPartonMotherId == 25); };
//     jets_fromHiggs.keepSelectedParticles(jetGenPartonMotherId);
//     jets_fromHiggs_30.initializeRawItems(jets_30.items);
//     jets_fromHiggs_30.keepSelectedParticles(jetGenPartonMotherId);

//     met.initializeRawItems(ev, "BNproducer","patMETsPFlow");
//     met.getCorrectedMet(jets);
//     events.initializeRawItems(ev, "BNproducer", "");
//     mcParticles.initializeRawItems(ev, "BNproducer", "MCstatus3");
//     primaryVertexes.initializeRawItems(ev, "BNproducer","offlinePrimaryVertices");
//     hltCollection.initializeRawItems(ev, "BNproducer", "HLT");

//     genHiggsParticles.initializeRawItems(mcParticles.rawItems);
//     auto higgsPDGID = [] (BNmcparticle p) { return (p.id == 25); };
//     genHiggsParticles.keepSelectedParticles(higgsPDGID);
//     genTopParticles.initializeRawItems(mcParticles.rawItems);
//     auto topPDGID = [] (BNmcparticle p) { return (p.id == 6); };
//     genTopParticles.keepSelectedParticles(topPDGID);
//     genAntiTopParticles.initializeRawItems(mcParticles.rawItems);
//     auto antitopPDGID = [] (BNmcparticle p) { return (p.id == -6); };


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

    // Get manual variables
    //    LeptonVarsThisAnalysis(tightMuons.items, tightLooseMuons.items, tightElectrons.items, tightLooseElectrons.items,
    //                           TwoMuon, TwoElectron, MuonElectron, PassTwoLepton);

    //    getNumExtraPartons(beanHelper, mcParticles.items, numExtraPartons);
    //    if (myConfig.sampleName.find("_0p") != std::string::npos) { //0 parton samples
      //Cut to require 0 partons
//       if (numExtraPartons != 0) {
//         numEventsFailCuts++;
//         numEventsPassCuts--;
//         continue; //Don't go on to fill tree with this event
//       }
//    }

    if (myConfig.sampleName == "ttbar" || myConfig.sampleName.find("ttbar_") != std::string::npos ) { //ttbar samples
      //ttPlusHFKeepEventFunction(beanHelper, mcParticles.items, jets.items, ttPlusHFKeepEventBool);
      if (!ttPlusHFKeepEventBool) {
        numEventsFailCuts++;
        numEventsPassCuts--;
        continue; //Don't go on to fill tree with this event
      }
    }
    
    // Fill the trees
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
