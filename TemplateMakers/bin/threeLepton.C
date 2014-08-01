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

void getNumExtraPartons(BEANhelper * beanHelper, BNmcparticleCollection& mcParticles, int& numExtraPartons) {

  numExtraPartons = beanHelper->GetNumExtraPartons(mcParticles);

  return;
}

bool LeptonCutThisAnalysis (BNleptonCollection& inputCollection) {
  unsigned numTightLoosePreselectedLeptons = inputCollection.size();

  bool passThreeLepton = false;

  if (numTightLoosePreselectedLeptons >= 3) passThreeLepton = true;

  return passThreeLepton;
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
  gSystem->Load( "libFWCoreFWLite" );
  AutoLibraryLoader::enable();

  int debug = 0; // levels of debug, 10 is large

  JobParameters myConfig = parseJobOptions(argc, argv);

  TFile * outputFile = new TFile(myConfig.outputFileName.c_str(), "RECREATE");

  outputFile->cd();

  TTree * summaryTree = new TTree("summaryTree", "Summary Event Values");

  fwlite::ChainEvent ev(myConfig.inputFileNames);

  HelperLeptonCore lepHelper;

  BEANhelper * beanHelper = lepHelper.setupAnalysisParameters("2012_53x", myConfig.sampleName);

  sysType::sysType jetSyst = sysType::NA;
  if (myConfig.jetSyst == "NA") jetSyst = sysType::NA;
  else if (myConfig.jetSyst == "JESUp") jetSyst = sysType::JESup;
  else if (myConfig.jetSyst == "JESDown") jetSyst = sysType::JESdown;
  else std::cout << "No valid JES corrections specified - using nominal" << std::endl;

  muonID::muonID muonTightID = muonID::muonSideTightMVA;
  muonID::muonID muonLooseID = muonID::muonSideLooseMVA;
  muonID::muonID muonPreselectedID = muonID::muonSide;
  electronID::electronID electronTightID = electronID::electronSideTightMVA;
  electronID::electronID electronLooseID = electronID::electronSideLooseMVA;
  electronID::electronID electronPreselectedID = electronID::electronSide;

  // collections
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
  GenericCollection<BNleptonCollection> looseLeptons(beanHelper);
  GenericCollection<BNleptonCollection> preselectedLeptons(beanHelper);
  GenericCollection<BNleptonCollection> tightLooseLeptons(beanHelper);
  GenericCollection<BNleptonCollection> tightLoosePreselectedLeptons(beanHelper);

  GenericCollection<BNjetCollection> jets(beanHelper);
  GenericCollection<BNjetCollection> jetsByCSV(beanHelper);
  GenericCollection<BNjetCollection> looseCSVJets(beanHelper);
  GenericCollection<BNjetCollection> mediumCSVJets(beanHelper);
  GenericCollection<BNjetCollection> notLooseCSVJets(beanHelper);
  GenericCollection<BNjetCollection> jetsForLepMVA(beanHelper);

  GenericCollection<BNmetCollection> met(beanHelper);
  GenericCollection<BNprimaryvertexCollection> primaryVertexes(beanHelper);
  GenericCollection<BNtriggerCollection> hltCollection(beanHelper);
  GenericCollection<BNeventCollection> events(beanHelper);
  GenericCollection<BNmcparticleCollection> mcParticles(beanHelper);

  GenericCollection<BNmcparticleCollection> genHiggsParticles(beanHelper);
  GenericCollection<BNmcparticleCollection> genTopParticles(beanHelper);

  // declare the kinematic variables that you want to be written out into the tree
  vector<ArbitraryVariable*> kinVars;
  vector<ArbitraryVariable*> cutVars;

  GenericCollectionSizeVariable<BNjetCollection> numJets(&(jets.ptrToItems), "numJets");
  kinVars.push_back(&numJets);
  numJets.setCutMin(2);
  cutVars.push_back(&numJets);

  GenericCollectionSizeVariable<BNjetCollection> numLooseBJets(&(looseCSVJets.ptrToItems), "numLooseBJets");
  kinVars.push_back(&numLooseBJets);

  GenericCollectionSizeVariable<BNjetCollection> numMediumBJets(&(mediumCSVJets.ptrToItems), "numMediumBJets");
  kinVars.push_back(&numMediumBJets);

  GenericCollectionSizeVariable<BNleptonCollection> numAllLeptons(&(tightLoosePreselectedLeptons.ptrToItems), "numAllLeptons");
  kinVars.push_back(&numAllLeptons);

  GenericCollectionSizeVariable<BNmuonCollection> numTightMuons(&(tightMuons.ptrToItems), "numTightMuons");
  kinVars.push_back(&numTightMuons);

  GenericCollectionSizeVariable<BNmuonCollection> numAllMuons(&(tightLoosePreselectedMuons.ptrToItems), "numAllMuons");
  kinVars.push_back(&numAllMuons);

  GenericCollectionSizeVariable<BNelectronCollection> numTightElectrons(&(tightElectrons.ptrToItems), "numTightElectrons");
  kinVars.push_back(&numTightElectrons);

  GenericCollectionSizeVariable<BNelectronCollection> numAllElectrons(&(tightLoosePreselectedElectrons.ptrToItems), "numAllElectrons");
  kinVars.push_back(&numAllElectrons);

  GenericCollectionSizeVariable<BNleptonCollection> numTightLeptons(&(tightLeptons.ptrToItems), "numTightLeptons");
  kinVars.push_back(&numTightLeptons);
  if (myConfig.sampleName.find("NP_sideband") == std::string::npos) { //All samples except NP_sideband
    std::cout << "Sample is not a sideband" << std::endl;
    numTightLeptons.setCutMin(2);
  }
  else if (myConfig.sampleName.find("NP_sideband") != std::string::npos) { //NP_sideband samples
    std::cout << "Sample is a sideband" << std::endl;
    numTightLeptons.setCutMax(2);
  }
  cutVars.push_back(&numTightLeptons);

  CSVWeights myCSV(beanHelper, &(jets.ptrToItems), jetSyst);
  kinVars.push_back(&myCSV);

  //Btag POG version
  vector<pair<string, double>> WPs = {make_pair("CSVT", 0.898), make_pair("CSVM", 0.679), make_pair("CSVL", 0.244)};
  BTagWeights myBTagWeights(WPs, &(jets.ptrToItems));
  kinVars.push_back(&myBTagWeights);

  PUWeights myPU(&lepHelper, &(events.ptrToItems));
  kinVars.push_back(&myPU);

  TopPtWeights myTopPt(&lepHelper, &(mcParticles.ptrToItems));
  kinVars.push_back(&myTopPt);

  LeptonIDAndIsoScaleFactors myLepIDAndIsoSF(&lepHelper, muonTightID, muonLooseID, electronTightID, electronLooseID,
                                             &(tightMuons.ptrToItems), &(looseMuons.ptrToItems),
                                             &(tightElectrons.ptrToItems), &(looseElectrons.ptrToItems));
  kinVars.push_back(&myLepIDAndIsoSF);

  //CERN version
  RecoIDIsoSIPSFs myRecoIDIsoSIPSFs(3, &(tightLoosePreselectedLeptons.ptrToItems));
  kinVars.push_back(&myRecoIDIsoSIPSFs);

  LeptonTriggerScaleFactors
  myLepTrig(&lepHelper, &(tightMuons.ptrToItems), &(looseMuons.ptrToItems), &(preselectedMuons.ptrToItems),
            &(tightElectrons.ptrToItems), &(looseElectrons.ptrToItems), &(preselectedElectrons.ptrToItems));
  kinVars.push_back(&myLepTrig);

  TightChargeAndLepMVAScaleFactors myTightChargeAndLepMVASFs(3, &(tightLoosePreselectedLeptons.ptrToItems));
  kinVars.push_back(&myTightChargeAndLepMVASFs);

  CleanEventVars myClean(&lepHelper, &(events.ptrToItems), &(primaryVertexes.ptrToItems));
  kinVars.push_back(&myClean);

  CheckTwoLepTrigger checkTrig(&lepHelper, &(hltCollection.ptrToItems));
  kinVars.push_back(&checkTrig);

//   TightCharges myTightCharges(&(tightLoosePreselectedLeptons.ptrToItems), "CERN_tight_charge", "all_leptons_by_pt", 2);
//   kinVars.push_back(&myTightCharges);

  LepMVAs<BNleptonCollection>
  myLepMVAsAllLeptons(&lepHelper, &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 3);
  kinVars.push_back(&myLepMVAsAllLeptons);

  LepMVAs<BNmuonCollection>
  myLepMVAsAllMuons(&lepHelper, &(tightLoosePreselectedMuons.ptrToItems), "all_muons_by_pt", 3);
  kinVars.push_back(&myLepMVAsAllMuons);

  DataDrivenFR<BNleptonCollection>
  myDataDrivenFRAllLeptons(&lepHelper, &(tightLoosePreselectedLeptons.ptrToItems), &(mediumCSVJets.ptrToItems), 3, 0.7, "FR_merged_data", "QF_data_el", "3l");
  kinVars.push_back(&myDataDrivenFRAllLeptons);

  HiggsDecayType myHiggsDecayType(&lepHelper, &(mcParticles.ptrToItems));
  kinVars.push_back(&myHiggsDecayType);

  TwoObjectKinematic<BNleptonCollection, BNjetCollection>
  myMHT("pt", "vector_sum", "mht",
        &(tightLoosePreselectedLeptons.ptrToItems), "tight_leptons_by_pt", 1, 99,
        &(jets.ptrToItems), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMHT);

//   TwoObjectKinematic<BNmuonCollection, BNjetCollection>
//   myMassMuonJetNew("mass", "all_pairs", "", &(tightMuons.ptrToItems),
//                    "tight_muons_by_pt", 1, 2, &(jets.ptrToItems), "jets_by_pt", 1, 4);
//   kinVars.push_back(&myMassMuonJetNew);

  TwoObjectKinematic<BNleptonCollection,BNmetCollection>
  mySumLep1Lep2MetPt("pt", "sum", "sum_lep1pt_lep2pt_met", &(tightLoosePreselectedLeptons.ptrToItems),
                     "all_leptons_by_pt", 1, 2, &(met.ptrToItems), "met", 1, 1);
  kinVars.push_back(&mySumLep1Lep2MetPt);

  TwoObjectKinematic<BNleptonCollection,BNleptonCollection>
  myMinMassLepLep("mass", "min", "min_test_leplep",
                  &(tightLoosePreselectedLeptons.ptrToItems),
                  "all_leptons_by_pt", 1, 99,
                  &(tightLoosePreselectedLeptons.ptrToItems),
                  "all_leptons_by_pt", 1, 99);
  kinVars.push_back(&myMinMassLepLep);

  TwoObjectKinematic<BNleptonCollection, BNleptonCollection>
  myMaxMassLepLep("mass", "max", "max_mass_leplep",
                  &(tightLoosePreselectedLeptons.ptrToItems),
                  "all_leptons_by_pt", 1, 99,
                  &(tightLoosePreselectedLeptons.ptrToItems),
                  "all_leptons_by_pt", 1, 99);
  kinVars.push_back(&myMaxMassLepLep);

  TwoObjectKinematic<BNleptonCollection, BNleptonCollection>
  myMinDeltaRLepLep("deltaR", "min", "min_dR_leplep",
                    &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                    &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99);
  kinVars.push_back(&myMinDeltaRLepLep);

  TwoObjectKinematic<BNjetCollection, BNmetCollection>
  mySumWeightedAbsDeltaPhiBJetMet("weightedAbsDeltaPhi", "sum", "sum_weighted_abs_dPhi_bjet_met",
                                  &(looseCSVJets.ptrToItems), "", 1, 99,
                                  &(met.ptrToItems), "met", 1, 1);
  kinVars.push_back(&mySumWeightedAbsDeltaPhiBJetMet);

  TwoObjectKinematic<BNleptonCollection, BNjetCollection>
  myMinWeightedDeltaRLeadingLepBJet("weightedDeltaR", "min", "min_weighted_dR_lep1_b_jet",
                                    &(tightLoosePreselectedLeptons.ptrToItems), "", 1, 1,
                                    &(looseCSVJets.ptrToItems), "", 1, 99);
  kinVars.push_back(&myMinWeightedDeltaRLeadingLepBJet);

  TwoObjectKinematic<BNleptonCollection, BNmetCollection>
  myWeightedDeltaPhiMetLep("weightedAbsDeltaPhi", "sum", "sum_weighted_abs_dPhi_lep_met",
                           &(tightLoosePreselectedLeptons.ptrToItems), "", 1, 99,
                           &(met.ptrToItems), "met", 1, 1);
  kinVars.push_back(&myWeightedDeltaPhiMetLep);

  TwoObjectKinematic<BNleptonCollection, BNleptonCollection>
  myMinMassLepLepAFASAll("mass", "min", "min_mass_leplep_AFAS_all",
                         &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                         &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99, -99);
  kinVars.push_back(&myMinMassLepLepAFASAll);

  TwoObjectKinematic<BNleptonCollection,BNleptonCollection>
  myMinMassLepLepSFOS("mass", "min", "min_mass_leplep_SFOS",
                      &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                      &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                      -99, "same_flavour", "opposite_sign");
  kinVars.push_back(&myMinMassLepLepSFOS);

  TwoObjectKinematic<BNleptonCollection,BNleptonCollection>
  myZLikeMassLepLepSFOSTightLoose("mass", "closest_to", "ZLike_mass_leplep_SFOS_tightLoose",
                                  &(tightLooseLeptons.ptrToItems), "tightLoose_leptons_by_pt", 1, 99,
                                  &(tightLooseLeptons.ptrToItems), "tightLoose_leptons_by_pt", 1, 99,
                                  91.2, "same_flavour", "opposite_sign");
  kinVars.push_back(&myZLikeMassLepLepSFOSTightLoose);

  TwoObjectKinematic<BNleptonCollection,BNleptonCollection>
  myZLikeMassLepLepSFOSAll("mass", "closest_to", "ZLike_mass_leplep_SFOS_all",
                           &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                           &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                           91.2, "same_flavour", "opposite_sign");
  kinVars.push_back(&myZLikeMassLepLepSFOSAll);

  TwoObjectKinematic<BNleptonCollection,BNleptonCollection>
  myZLikeMassLepLepAFASAll("mass", "closest_to", "Z_like_mass_lep_lep_AFAS_all",
                           &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                           &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99, 91.2);
  kinVars.push_back(&myZLikeMassLepLepAFASAll);

  TwoObjectKinematic<BNjetCollection,BNjetCollection>
  myHiggsLikeDijetMass110("mass", "closest_to", "higgsLike_dijet_mass",
                          &(mediumCSVJets.ptrToItems), "medium_btags_by_pt", 1, 99,
                          &(mediumCSVJets.ptrToItems), "medium_btags_by_pt", 1, 99, 110);
  kinVars.push_back(&myHiggsLikeDijetMass110);

  TwoObjectKinematic<BNleptonCollection, BNjetCollection>
  myMinDeltaPhiLep1Jet("deltaPhi", "min", "min_dPhi_lep1_jet",
                       &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 1,
                       &(jets.ptrToItems), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMinDeltaPhiLep1Jet);

  TwoObjectKinematic<BNleptonCollection, BNjetCollection>
  myMinDeltaPhiLep2Jet("deltaPhi", "min", "min_dPhi_lep2_jet",
                     &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 2, 2,
                     &(jets.ptrToItems), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMinDeltaPhiLep2Jet);

  TwoObjectKinematic<BNmetCollection, BNleptonCollection>
  myMtMetLep("MT", "all_pairs", "",
             &(met.ptrToItems), "met", 1, 1,
             &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 2);
  kinVars.push_back(&myMtMetLep);

  TwoObjectKinematic<BNleptonCollection,BNjetCollection>
  mySumPt("pt", "sum", "sum_pt",
          &(tightLoosePreselectedLeptons.ptrToItems), "tight_leptons_by_pt", 1, 99,
          &(jets.ptrToItems), "jets_by_pt", 1, 99);
  kinVars.push_back(&mySumPt);

  TwoObjectKinematic<BNleptonCollection, BNjetCollection>
  myMinDeltaRLep1Jet("deltaR", "min", "min_deltaR_lep1_jet",
                       &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 1,
                       &(jets.ptrToItems), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMinDeltaRLep1Jet);

  TwoObjectKinematic<BNleptonCollection, BNjetCollection>
  myMinDeltaRLep2Jet("deltaR", "min", "min_deltaR_lep2_jet",
                     &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 2, 2,
                     &(jets.ptrToItems), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMinDeltaRLep2Jet);

  TwoObjectKinematic<BNleptonCollection, BNjetCollection>
  myMinDeltaRLep3Jet("deltaR", "min", "min_deltaR_lep3_jet",
                       &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 3, 3,
                       &(jets.ptrToItems), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMinDeltaRLep3Jet);

  ////////// all leptons //////////
  GenericCollectionMember<int, BNleptonCollection>
  allLeptonNumberOfValidTrackerHitsInnerTrack(Reflex::Type::ByName("BNlepton"),
                                              &(tightLoosePreselectedLeptons.ptrToItems),
                                              "numberOfValidTrackerHitsInnerTrack", "all_leptons_by_pt",
                                              KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonNumberOfValidTrackerHitsInnerTrack);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonInnerTkPt(Reflex::Type::ByName("BNlepton"),
                     &(tightLoosePreselectedLeptons.ptrToItems),
                     "innerTrackPt", "all_leptons_by_pt",
                     KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonInnerTkPt);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonInnerTkPtError(Reflex::Type::ByName("BNlepton"),
                          &(tightLoosePreselectedLeptons.ptrToItems),
                          "innerTrackPtError", "all_leptons_by_pt",
                          KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonInnerTkPtError);

//   GenericCollectionMember<double, BNleptonCollection>
//   allLeptonNeutralHadronIsoDR04(Reflex::Type::ByName("BNlepton"),
//                                 &(tightLoosePreselectedLeptons.ptrToItems),
//                                 "neutralHadronIsoDR04", "all_leptons_by_pt",
//                                 KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&allLeptonNeutralHadronIsoDR04);

//   GenericCollectionMember<double, BNleptonCollection>
//   allLeptonPhotonIsoDR04(Reflex::Type::ByName("BNlepton"),
//                          &(tightLoosePreselectedLeptons.ptrToItems),
//                          "photonIsoDR04", "all_leptons_by_pt",
//                          KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&allLeptonPhotonIsoDR04);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonPUChargedHadronIsoDR04(Reflex::Type::ByName("BNlepton"),
                                  &(tightLoosePreselectedLeptons.ptrToItems),
                                  "puChargedHadronIsoDR04", "all_leptons_by_pt",
                                  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonPUChargedHadronIsoDR04);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonChargedHadronIso(Reflex::Type::ByName("BNlepton"),
                            &(tightLoosePreselectedLeptons.ptrToItems),
                            "chargedHadronIso", "all_leptons_by_pt",
                            KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonChargedHadronIso);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonJetDeltaR(Reflex::Type::ByName("BNlepton"),
                     &(tightLoosePreselectedLeptons.ptrToItems),
                     "jetDeltaR", "all_leptons_by_pt",
                     KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonJetDeltaR);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonJetPtRatio(Reflex::Type::ByName("BNlepton"),
                      &(tightLoosePreselectedLeptons.ptrToItems),
                      "jetPtRatio", "all_leptons_by_pt",
                      KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonJetPtRatio);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonJetBTagCSV(Reflex::Type::ByName("BNlepton"),
                      &(tightLoosePreselectedLeptons.ptrToItems),
                      "jetBTagCSV", "all_leptons_by_pt",
                      KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonJetBTagCSV);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonMvaNonTrigV0(Reflex::Type::ByName("BNlepton"),
                        &(tightLoosePreselectedLeptons.ptrToItems),
                        "mvaNonTrigV0", "all_leptons_by_pt",
                        KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonMvaNonTrigV0);

  GenericCollectionMember<int, BNleptonCollection>
  allLeptonNumberOfExpectedInnerHits(Reflex::Type::ByName("BNlepton"),
                                     &(tightLoosePreselectedLeptons.ptrToItems),
                                     "numberOfExpectedInnerHits", "all_leptons_by_pt",
                                     KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonNumberOfExpectedInnerHits);

  GenericCollectionMember<int, BNleptonCollection>
  allLeptonIsGsfCtfScPixChargeConsistent(Reflex::Type::ByName("BNlepton"),
                                         &(tightLoosePreselectedLeptons.ptrToItems),
                                         "isGsfCtfScPixChargeConsistent", "all_leptons_by_pt",
                                         KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonIsGsfCtfScPixChargeConsistent);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonPt(Reflex::Type::ByName("BNlepton"),
              &(tightLoosePreselectedLeptons.ptrToItems),
              "pt", "all_leptons_by_pt",
              KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonPt);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonTkPT(Reflex::Type::ByName("BNlepton"),
                &(tightLoosePreselectedLeptons.ptrToItems),
                "tkPT", "all_leptons_by_pt",
                KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonTkPT);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonEta(Reflex::Type::ByName("BNlepton"),
               &(tightLoosePreselectedLeptons.ptrToItems),
               "eta", "all_leptons_by_pt",
               KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonEta);

  GenericCollectionMember<int, BNleptonCollection>
  allLeptonIsMuon(Reflex::Type::ByName("BNlepton"),
                  &(tightLoosePreselectedLeptons.ptrToItems),
                  "isMuon", "all_leptons_by_pt",
                  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonIsMuon);

  GenericCollectionMember<int, BNleptonCollection>
  allLeptonIsElectron(Reflex::Type::ByName("BNlepton"),
                      &(tightLoosePreselectedLeptons.ptrToItems),
                      "isElectron", "all_leptons_by_pt",
                      KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonIsElectron);

  GenericCollectionMember<int, BNleptonCollection>
  allLeptonTkCharge(Reflex::Type::ByName("BNlepton"),
                    &(tightLoosePreselectedLeptons.ptrToItems),
                    "tkCharge", "all_leptons_by_pt",
                    KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonTkCharge);

  GenericCollectionMember<int, BNleptonCollection>
  allLeptonCharge(Reflex::Type::ByName("BNlepton"),
                  &(tightLoosePreselectedLeptons.ptrToItems),
                  "charge", "all_leptons_by_pt",
                  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonCharge);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonSIP(Reflex::Type::ByName("BNlepton"),
               &(tightLoosePreselectedLeptons.ptrToItems),
               "SIP", "all_leptons_by_pt",
               KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonSIP);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonD0(Reflex::Type::ByName("BNlepton"),
              &(tightLoosePreselectedLeptons.ptrToItems),
              "correctedD0Vertex", "all_leptons_by_pt",
              KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonD0);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonDZ(Reflex::Type::ByName("BNlepton"),
              &(tightLoosePreselectedLeptons.ptrToItems),
              "correctedDZ", "all_leptons_by_pt",
              KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonDZ);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonIP(Reflex::Type::ByName("BNlepton"),
              &(tightLoosePreselectedLeptons.ptrToItems),
              "IP", "all_leptons_by_pt",
              KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonIP);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonIPError(Reflex::Type::ByName("BNlepton"),
                   &(tightLoosePreselectedLeptons.ptrToItems),
                   "IPError", "all_leptons_by_pt",
                   KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonIPError);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonPhi(Reflex::Type::ByName("BNlepton"),
               &(tightLoosePreselectedLeptons.ptrToItems),
               "phi", "all_leptons_by_pt",
               KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonPhi);

  GenericCollectionMember<int, BNleptonCollection>
  allLeptonGlobalMuon(Reflex::Type::ByName("BNlepton"),
                      &(tightLoosePreselectedLeptons.ptrToItems),
                      "isGlobalMuon", "all_leptons_by_pt",
                      KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonGlobalMuon);

  GenericCollectionMember<int, BNleptonCollection>
  allLeptonPassConvVeto(Reflex::Type::ByName("BNlepton"),
                        &(tightLoosePreselectedLeptons.ptrToItems),
                        "passConvVeto", "all_leptons_by_pt",
                        KinematicVariableConstants::INT_INIT, 3);
  kinVars.push_back(&allLeptonPassConvVeto);

  GenericCollectionMember<int, BNleptonCollection>
  allLeptonNumExpInnerHits(Reflex::Type::ByName("BNlepton"),
                           &(tightLoosePreselectedLeptons.ptrToItems),
                           "numberOfExpectedInnerHits", "all_leptons_by_pt",
                           KinematicVariableConstants::INT_INIT, 3);
  kinVars.push_back(&allLeptonNumExpInnerHits);

  ////////// all muons //////////
  GenericCollectionMember<double, BNmuonCollection> allMuonPt(Reflex::Type::ByName("BNmuon"), &(tightLoosePreselectedMuons.ptrToItems),
                                                              "pt", "all_muons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allMuonPt);

  ////////// all electrons //////////
  GenericCollectionMember<double, BNelectronCollection> allElectronPt(Reflex::Type::ByName("BNelectron"), &(tightLoosePreselectedElectrons.ptrToItems),
                                                                      "pt", "all_electrons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allElectronPt);

  ////////// all jets //////////
  GenericCollectionMember<double, BNjetCollection> allJetPt(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems),
                                                            "pt", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetPt);

  GenericCollectionMember<double, BNjetCollection> allJetEta(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems),
                                                             "eta", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetEta);

  GenericCollectionMember<double, BNjetCollection> allJetPhi(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems),
                                                             "phi", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetPhi);

  GenericCollectionMember<double, BNjetCollection> allJetCSV(Reflex::Type::ByName("BNjet"),  &(jets.ptrToItems),
                                                             "btagCombinedSecVertex", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetCSV);

  ////////// met //////////
  GenericCollectionMember<double, BNmetCollection> metPt(Reflex::Type::ByName("BNmet"),  &(met.ptrToItems),
                                                         "pt", "met",  KinematicVariableConstants::FLOAT_INIT, 1);
  kinVars.push_back(&metPt);

  int numExtraPartons = -99;
  summaryTree->Branch("numExtraPartons", &numExtraPartons);

  ////////// event info //////////
  GenericCollectionMember<unsigned, BNeventCollection> runNumber(Reflex::Type::ByName("BNevent"), &(events.ptrToItems),
                                                                 "run", "eventInfo",  KinematicVariableConstants::UINT_INIT, 1);
  kinVars.push_back(&runNumber);

  GenericCollectionMember<unsigned, BNeventCollection> lumiBlock(Reflex::Type::ByName("BNevent"), &(events.ptrToItems),
                                                                 "lumi", "eventInfo",  KinematicVariableConstants::UINT_INIT, 1);
  kinVars.push_back(&lumiBlock);

  ////////// gen collections //////////
  GenericCollectionMember<double, BNmcparticleCollection>
  higgsPt(Reflex::Type::ByName("BNmcparticle"), &(genHiggsParticles.ptrToItems),
          "pt", "higgs", KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&higgsPt);

  GenericCollectionMember<double, BNmcparticleCollection>
  higgsEta(Reflex::Type::ByName("BNmcparticle"), &(genHiggsParticles.ptrToItems),
          "eta", "higgs", KinematicVariableConstants::FLOAT_INIT, 1);
  kinVars.push_back(&higgsEta);

  GenericCollectionMember<double, BNmcparticleCollection>
  higgsPhi(Reflex::Type::ByName("BNmcparticle"), &(genHiggsParticles.ptrToItems),
          "phi", "higgs", KinematicVariableConstants::FLOAT_INIT, 1);
  kinVars.push_back(&higgsPhi);

  // this is a long inside BNevent: just using keyword long won't work, needs to be Long64_t
  GenericCollectionMember<Long64_t, BNeventCollection>
  eventNumber(Reflex::Type::ByName("BNevent"),  &(events.ptrToItems), "evt", "eventInfo",  KinematicVariableConstants::INT_INIT, 1);
  kinVars.push_back(&eventNumber);

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

    lepHelper.applyRochesterCorrections(tightLoosePreselectedMuons.rawItems);
    bool applySmearing = !(lepHelper.isData);
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
    looseLeptons.resetAndPushBack(looseElectrons.items);
    looseLeptons.pushBackAndSort(looseMuons.items);
    preselectedLeptons.resetAndPushBack(preselectedElectrons.items);
    preselectedLeptons.pushBackAndSort(preselectedMuons.items);
    tightLooseLeptons.resetAndPushBack(tightLooseElectrons.items);
    tightLooseLeptons.pushBackAndSort(tightLooseMuons.items);
    tightLoosePreselectedLeptons.resetAndPushBack(tightLoosePreselectedElectrons.items);
    tightLoosePreselectedLeptons.pushBackAndSort(tightLoosePreselectedMuons.items);

    jets.initializeRawItemsSortedByPt(ev, "BNproducer","selectedPatJetsPFlow");
    jets.cleanJets(tightLoosePreselectedLeptons.items);
    jets.correctRawJets(jetSyst);
    jets.keepSelectedJets(25.0, 2.4, jetID::jetLoose, '-');
    jetsByCSV.initializeRawItemsSortedByCSV(jets.items);
    looseCSVJets.initializeRawItems(jets.rawItems);
    looseCSVJets.keepSelectedJets(25.0, 2.4, jetID::jetLoose, 'L');
    mediumCSVJets.initializeRawItems(jets.rawItems);
    mediumCSVJets.keepSelectedJets(25.0, 2.4, jetID::jetLoose, 'M');
    notLooseCSVJets.initializeRawItems(beanHelper->GetDifference(jets.items, looseCSVJets.items));

    met.initializeRawItems(ev, "BNproducer", "patMETsPFlow");
    met.getCorrectedMet(jets);
    events.initializeRawItems(ev, "BNproducer", "");
    mcParticles.initializeRawItems(ev, "BNproducer", "MCstatus3");
    primaryVertexes.initializeRawItems(ev, "BNproducer","offlinePrimaryVertices");
    hltCollection.initializeRawItems(ev, "BNproducer", "HLT");

    genHiggsParticles.initializeRawItems(mcParticles.rawItems);
    auto higgsPDGID = [] (BNmcparticle p) { return (p.id == 25); };
    genHiggsParticles.keepSelectedParticles(higgsPDGID);
    genTopParticles.initializeRawItems(mcParticles.rawItems);
    auto topPDGID = [] (BNmcparticle p) { return (abs(p.id) == 6); };
    genTopParticles.keepSelectedParticles(topPDGID);

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
    passAllCuts = passAllCuts && LeptonCutThisAnalysis(tightLoosePreselectedLeptons.items);

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

    getNumExtraPartons(beanHelper, mcParticles.items, numExtraPartons);
    if (myConfig.sampleName.find("_0p") != std::string::npos) { //0 parton samples
      //Cut to require 0 partons
      if (numExtraPartons != 0) {
        numEventsFailCuts++;
        numEventsPassCuts--;
        continue;
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
