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
  bool passTwoLepton = false;

  //Collection definitions set by muonID::muonID and electronID::electronID inside main function
//   unsigned numTightMuons = inputCollections->tightMuonCollection->size();
//   unsigned numLooseMuons = inputCollections->looseMuonCollection->size();
//   unsigned numTightElectrons = inputCollections->tightElectronCollection->size();
//   unsigned numLooseElectrons = inputCollections->looseElectronCollection->size();
//   if (numTightMuons ==2 || numTightElectrons==2 || (numTightMuons==1 && numTightElectrons==1))
//     passTwoLepton = true;

  unsigned numAllLeptons = inputCollection.size();
  if (numAllLeptons >= 2)
    passTwoLepton = true;

  return passTwoLepton;
}

void LeptonVarsThisAnalysis(BNmuonCollection& muons, BNelectronCollection& electrons, bool passTwoLepton, int & TwoMuon, int & TwoElectron, int & MuonElectron) {
  //Collection definitions set by muonID::muonID and electronID::electronID inside main function
  unsigned numTightMuons = muons.size();
  unsigned numTightElectrons = electrons.size();

  TwoMuon = 0;
  TwoElectron = 0;
  MuonElectron = 0;

  if (!passTwoLepton){
    return;
  }

  if (numTightMuons == 2 ) {
    TwoMuon = 1;
    return;
  }

  if (numTightElectrons == 2 ) {
    TwoElectron = 1;
    return;
  }

  if ( numTightElectrons ==1 && numTightMuons==1 ) {
    MuonElectron = 1;
    return;
  }
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
  tauID::tauID tauTightID = tauID::tauMedium;
  tauID::tauID tauLooseID = tauID::tauLoose;
  tauID::tauID tauPreselectedID = tauID::tauNonIso;

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

  GenericCollection<BNtauCollection> tightTaus(beanHelper);
  GenericCollection<BNtauCollection> tightLooseTaus(beanHelper);
  GenericCollection<BNtauCollection> tightLoosePreselectedTaus(beanHelper);

  GenericCollection<BNjetCollection> jets(beanHelper);
  GenericCollection<BNjetCollection> jetsByCSV(beanHelper);
  GenericCollection<BNjetCollection> looseCSVJets(beanHelper);
  GenericCollection<BNjetCollection> mediumCSVJets(beanHelper);
  GenericCollection<BNjetCollection> notLooseCSVJets(beanHelper);
  GenericCollection<BNjetCollection> jetsForLepMVA(beanHelper);
  GenericCollection<BNjetCollection> jetsClosestToLep1(beanHelper);

  GenericCollection<BNmetCollection> met(beanHelper);
  GenericCollection<BNprimaryvertexCollection> primaryVertexes(beanHelper);
  GenericCollection<BNtriggerCollection> hltCollection(beanHelper);
  GenericCollection<BNeventCollection> events(beanHelper);
  GenericCollection<BNmcparticleCollection> mcParticles(beanHelper);

  GenericCollection<BNmcparticleCollection> genHiggsParticles(beanHelper);
  GenericCollection<BNmcparticleCollection> genTopParticles(beanHelper);
  GenericCollection<BNmcparticleCollection> genAntiTopParticles(beanHelper);
  GenericCollection<BNmcparticleCollection> genTTbarParticles(beanHelper);

  // declare the kinematic variables that you want to be written out into the tree
  vector<ArbitraryVariable*> kinVars;
  vector<ArbitraryVariable*> cutVars;

  ////////////////////////// corrections, weights, etc
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

  //Currently, gets ND loose lepton SF; could switch to tight and loose - AWB Feb 12, 2014
  //LeptonIDAndIsoScaleFactors myLepIDAndIsoSF(&lepHelper, muonID::muonTight, muonID::muonLoose, electronID::electronTight, electronID::electronLoose);
  LeptonIDAndIsoScaleFactors myLepIDAndIsoSF(&lepHelper, muonTightID, muonLooseID, electronTightID, electronLooseID,
                                             &(tightMuons.ptrToItems), &(looseMuons.ptrToItems),
                                             &(tightElectrons.ptrToItems), &(looseElectrons.ptrToItems));
  kinVars.push_back(&myLepIDAndIsoSF);

  //CERN version
  RecoIDIsoSIPSFs myRecoIDIsoSIPSFs(2, &(tightLoosePreselectedLeptons.ptrToItems));
  kinVars.push_back(&myRecoIDIsoSIPSFs);

  LeptonTriggerScaleFactors
  myLepTrig(&lepHelper, &(tightMuons.ptrToItems), &(looseMuons.ptrToItems), &(preselectedMuons.ptrToItems),
            &(tightElectrons.ptrToItems), &(looseElectrons.ptrToItems), &(preselectedElectrons.ptrToItems));
  kinVars.push_back(&myLepTrig);

  TightChargeAndLepMVAScaleFactors myTightChargeAndLepMVASFs(2, &(tightLoosePreselectedLeptons.ptrToItems));
  kinVars.push_back(&myTightChargeAndLepMVASFs);

  CleanEventVars myClean(&lepHelper, &(events.ptrToItems), &(primaryVertexes.ptrToItems));
  kinVars.push_back(&myClean);

  CheckTwoLepTrigger checkTrig(&lepHelper, &(hltCollection.ptrToItems));
  kinVars.push_back(&checkTrig);

  DataDrivenFR<BNleptonCollection>
  myDataDrivenFRAllLeptons(&lepHelper, &(tightLoosePreselectedLeptons.ptrToItems), &(mediumCSVJets.ptrToItems), 2, 0.7, "FR_merged_data", "QF_data_el");
  kinVars.push_back(&myDataDrivenFRAllLeptons);

  DataDrivenFR<BNleptonCollection>
  myDataDrivenFRAllLeptonsLoose(&lepHelper, &(tightLoosePreselectedLeptons.ptrToItems), &(mediumCSVJets.ptrToItems), 2, -0.3, "FR_merged_data", "QF_data_el", "_Loose");
  kinVars.push_back(&myDataDrivenFRAllLeptonsLoose);

  HiggsDecayType myHiggsDecayType(&lepHelper, &(mcParticles.ptrToItems));
  kinVars.push_back(&myHiggsDecayType);

  TightCharges myTightCharges(&(tightLoosePreselectedLeptons.ptrToItems), "CERN_tight_charge", "all_leptons_by_pt", 2);
  kinVars.push_back(&myTightCharges);
  //myTightCharges.setCut("pass");

  ////////////////////////// collection sizes
  GenericCollectionSizeVariable<BNjetCollection> numJets(&(jets.ptrToItems), "numJets");
  kinVars.push_back(&numJets);
  numJets.setCutMin(2);
  //cutVars.push_back(&numJets);

  GenericCollectionSizeVariable<BNjetCollection> numLooseBJets(&(looseCSVJets.ptrToItems), "numLooseBJets");
  kinVars.push_back(&numLooseBJets);

  GenericCollectionSizeVariable<BNjetCollection> numMediumBJets(&(mediumCSVJets.ptrToItems), "numMediumBJets");
  kinVars.push_back(&numMediumBJets);

  GenericCollectionSizeVariable<BNjetCollection> numJetsClosestToLep1(&(jetsClosestToLep1.ptrToItems), "numJetsClosestToLep1");
  kinVars.push_back(&numJetsClosestToLep1);

  GenericCollectionSizeVariable<BNmuonCollection> numAllMuons(&(tightLoosePreselectedMuons.ptrToItems), "numAllMuons");
  kinVars.push_back(&numAllMuons);

  GenericCollectionSizeVariable<BNelectronCollection> numAllElectrons(&(tightLoosePreselectedElectrons.ptrToItems), "numAllElectrons");
  kinVars.push_back(&numAllElectrons);

  GenericCollectionSizeVariable<BNleptonCollection> numAllLeptons(&(tightLoosePreselectedLeptons.ptrToItems), "numAllLeptons");
  kinVars.push_back(&numAllLeptons);

  GenericCollectionSizeVariable<BNleptonCollection> numTightLooseLeptons(&(tightLooseLeptons.ptrToItems), "numTightLooseLeptons");
  kinVars.push_back(&numTightLooseLeptons);

  GenericCollectionSizeVariable<BNmuonCollection> numTightMuons(&(tightMuons.ptrToItems), "numTightMuons");
  kinVars.push_back(&numTightMuons);

  GenericCollectionSizeVariable<BNelectronCollection> numTightElectrons(&(tightElectrons.ptrToItems), "numTightElectrons");
  kinVars.push_back(&numTightElectrons);

  GenericCollectionSizeVariable<BNleptonCollection> numTightLeptons(&(tightLeptons.ptrToItems), "numTightLeptons");
  kinVars.push_back(&numTightLeptons);
  if (myConfig.sampleName.find("NP_sideband") == std::string::npos) { //All samples except NP_sideband
    std::cout << "Sample is not a sideband" << std::endl;
    numTightLeptons.setCutMin(2);
  }
  else if (myConfig.sampleName.find("NP_sideband") != std::string::npos) { //NP_sideband samples
    std::cout << "Sample is a sideband" << std::endl;
    //Cut to require opposite-sign leptons
    numTightLeptons.setCutMin(0);
  }
  cutVars.push_back(&numTightLeptons);

  GenericCollectionSizeVariable<BNtauCollection> numAllTaus(&(tightLoosePreselectedTaus.ptrToItems), "numAllTaus");
  kinVars.push_back(&numAllTaus);

  GenericCollectionSizeVariable<BNtauCollection> numTightLooseTaus(&(tightLooseTaus.ptrToItems), "numTightLooseTaus");
  kinVars.push_back(&numTightLooseTaus);

  GenericCollectionSizeVariable<BNtauCollection> numTightTaus(&(tightTaus.ptrToItems), "numTightTaus");
  kinVars.push_back(&numTightTaus);

  ////////////////////////// lep MVAs
  LepMVAs<BNleptonCollection> myLepMVAsTightLeptons(&lepHelper, &(tightLeptons.ptrToItems), "tight_leptons_by_pt", 2);
  kinVars.push_back(&myLepMVAsTightLeptons);

  LepMVAs<BNleptonCollection> myLepMVAsLooseLeptons(&lepHelper, &(looseLeptons.ptrToItems), "loose_leptons_by_pt", 2);
  kinVars.push_back(&myLepMVAsLooseLeptons);

  LepMVAs<BNleptonCollection> myLepMVAsPreselectedLeptons(&lepHelper, &(preselectedLeptons.ptrToItems), "preselected_leptons_by_pt", 2);
  kinVars.push_back(&myLepMVAsPreselectedLeptons);

  LepMVAs<BNleptonCollection> myLepMVAsAllLeptons(&lepHelper, &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 3);
  kinVars.push_back(&myLepMVAsAllLeptons);

  LepMVAs<BNmuonCollection> myLepMVAsAllMuons(&lepHelper, &(tightLoosePreselectedMuons.ptrToItems), "all_muons_by_pt", 3);
  kinVars.push_back(&myLepMVAsAllMuons);

  ////////////////////////// composite objects
  TwoObjectKinematic<BNleptonCollection, BNmetCollection>
  mySumLep1Lep2MetPt("pt", "sum", "sum_lep1pt_lep2pt_met",
                     &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 2,
                     &(met.ptrToItems), "met", 1, 1);
  kinVars.push_back(&mySumLep1Lep2MetPt);

  TwoObjectKinematic<BNleptonCollection, BNleptonCollection>
  myMinMassLepLep("mass", "min", "min_mass_leplep",
                  &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                  &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99);
  kinVars.push_back(&myMinMassLepLep);

  TwoObjectKinematic<BNleptonCollection,BNleptonCollection>
  myMinMassLepLepSFOS("mass", "min", "min_mass_leplep_SFOS",
                      &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                      &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                      -99, "same_flavour", "opposite_sign");
  kinVars.push_back(&myMinMassLepLepSFOS);

  TwoObjectKinematic<BNleptonCollection,BNleptonCollection>
  myZLikeMassLepLepSFOS("mass", "closest_to", "ZLike_mass_leplep_SFOS",
                        &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                        &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                        91.2, "same_flavour", "opposite_sign");
  kinVars.push_back(&myZLikeMassLepLepSFOS);


  TwoObjectKinematic<BNleptonCollection, BNleptonCollection>
  myMinDeltaRLepLep("deltaR", "min", "min_dR_leplep",
                    &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                    &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99);
  kinVars.push_back(&myMinDeltaRLepLep);

  TwoObjectKinematic<BNjetCollection, BNjetCollection>
  myHiggsLikeDijetMass110("mass", "closest_to", "higgsLike_dijet_mass",
                          &(mediumCSVJets.ptrToItems), "medium_btags_by_pt", 1, 99,
                          &(mediumCSVJets.ptrToItems), "medium_btags_by_pt", 1, 99, 110);
  kinVars.push_back(&myHiggsLikeDijetMass110);

  TwoObjectKinematic<BNtauCollection, BNjetCollection>
  myMinDeltaRTau1Jet("deltaR", "min", "min_deltaR_tau1_jet",
                     &(tightLoosePreselectedTaus.ptrToItems), "all_taus_by_pt", 1, 1,
                     &(jets.ptrToItems), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMinDeltaRTau1Jet);

  TwoObjectKinematic<BNtauCollection, BNleptonCollection>
  myMassTau1Leptons("mass", "all_pairs", "",
                    &(tightLoosePreselectedTaus.ptrToItems), "all_taus_by_pt", 1, 1,
                    &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 2);
  kinVars.push_back(&myMassTau1Leptons);

  //Variables for CERN same-sign dilepton BDT
  TwoObjectKinematic<BNleptonCollection, BNjetCollection>
  myMHT("pt", "vector_sum", "mht",
        &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
        &(jets.ptrToItems), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMHT);

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
  myMinDeltaRLep3Jet("deltaR", "min", "mindr_lep3_jet",
                     &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 3, 3,
                     &(jets.ptrToItems), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMinDeltaRLep3Jet);

  TwoObjectKinematic<BNmetCollection, BNleptonCollection>
  myMtMetLep("MT", "all_pairs", "",
             &(met.ptrToItems), "met", 1, 1,
             &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 2);
  kinVars.push_back(&myMtMetLep);

  TwoObjectKinematic<BNleptonCollection,BNjetCollection>
  mySumPt("pt", "sum", "sum_pt",
          &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
          &(jets.ptrToItems), "jets_by_pt", 1, 99);
  kinVars.push_back(&mySumPt);

  int TwoMuon = 0;
  int TwoElectron = 0;
  int MuonElectron = 0;
  Char_t *dataset = (Char_t *)lepHelper.dataset.c_str();

  int sampleNumber = (int)lepHelper.sampleNumber;
  double weight_Xsec = (double)lepHelper.weight_Xsec;
  int nGen = (int)lepHelper.nGen;
  double Xsec = (double)lepHelper.Xsec;
  summaryTree->Branch("sampleNumber", &sampleNumber);
  summaryTree->Branch("weight_Xsec", &weight_Xsec);
  summaryTree->Branch("nGen", &nGen);
  summaryTree->Branch("Xsec", &Xsec);

  summaryTree->Branch("TwoMuon", &TwoMuon);
  summaryTree->Branch("TwoElectron", &TwoElectron);
  summaryTree->Branch("MuonElectron", &MuonElectron);
  summaryTree->Branch("dataset", (void*)dataset, "dataset/C");

  ////////// all leptons //////////
  GenericCollectionMember<int, BNleptonCollection>
  allLeptonNumberOfValidTrackerHitsInnerTrack(Reflex::Type::ByName("BNlepton"),
                                              &(tightLoosePreselectedLeptons.ptrToItems),
                                              "numberOfValidTrackerHitsInnerTrack", "all_leptons_by_pt",
                                              KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonNumberOfValidTrackerHitsInnerTrack);


  GenericCollectionMember<double, BNleptonCollection>
  allLeptonInnerTkPt(Reflex::Type::ByName("BNlepton"),
                     &(tightLoosePreselectedLeptons.ptrToItems), "innerTrackPt",
                     "all_leptons_by_pt", KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonInnerTkPt);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonInnerTkPtError(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
                          "innerTrackPtError", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonInnerTkPtError);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonJetDeltaR(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "jetDeltaR", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonJetDeltaR);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonJetPtRatio(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "jetPtRatio", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonJetPtRatio);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonJetBTagCSV(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "jetBTagCSV", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonJetBTagCSV);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonMvaNonTrigV0(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "mvaNonTrigV0", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonMvaNonTrigV0);

  GenericCollectionMember<int, BNleptonCollection>
  allLeptonNumberOfExpectedInnerHits(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "numberOfExpectedInnerHits", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonNumberOfExpectedInnerHits);

  GenericCollectionMember<int, BNleptonCollection>
  allLeptonIsGsfCtfScPixChargeConsistent(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "isGsfCtfScPixChargeConsistent", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonIsGsfCtfScPixChargeConsistent);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonPt(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "pt", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonPt);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonTkPT(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "tkPT", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonTkPT);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonEta(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "eta", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonEta);

  GenericCollectionMember<int, BNleptonCollection>
  allLeptonIsMuon(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "isMuon", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonIsMuon);

  GenericCollectionMember<int, BNleptonCollection>
  allLeptonIsElectron(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "isElectron", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonIsElectron);

  GenericCollectionMember<int, BNleptonCollection>
  allLeptonTkCharge(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "tkCharge", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonTkCharge);

  if (myConfig.sampleName.find("QF_sideband") == std::string::npos) { //All samples except QF_sideband
    //Cut to require same-sign leptons
    auto tkChargeCut = [] (vector<BranchInfo<int>> vars) { return ((vars[0].branchVal * vars[1].branchVal) > 0 || abs(vars[2].branchVal) == 1 ); };
    allLeptonTkCharge.setCut(tkChargeCut);
  }
  else if (myConfig.sampleName.find("QF_sideband") != std::string::npos) { //QF_sideband samples
    //Cut to require opposite-sign leptons
    auto tkChargeCut = [] (vector<BranchInfo<int>> vars) { return ((vars[0].branchVal * vars[1].branchVal) < 0); };
    allLeptonTkCharge.setCut(tkChargeCut);
  }
  cutVars.push_back(&allLeptonTkCharge);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonSIP(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "SIP", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonSIP);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonD0(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "correctedD0Vertex", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonD0);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonDZ(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "correctedDZ", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonDZ);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonIP(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "IP", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonIP);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonIPError(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "IPError", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonIPError);

  GenericCollectionMember<double, BNleptonCollection>
  allLeptonPhi(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "phi", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonPhi);

  GenericCollectionMember<int, BNleptonCollection>
  allLeptonGlobalMuon(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems), "isGlobalMuon", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allLeptonGlobalMuon);

  ////////// all muons //////////
  GenericCollectionMember<int, BNmuonCollection>
  allMuonPFmuon(Reflex::Type::ByName("BNmuon"), &(tightLoosePreselectedMuons.ptrToItems), "isPFMuon", "all_muons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allMuonPFmuon);

  GenericCollectionMember<int, BNmuonCollection>
  allMuonGlobalMuon(Reflex::Type::ByName("BNmuon"), &(tightLoosePreselectedMuons.ptrToItems), "isGlobalMuon", "all_muons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allMuonGlobalMuon);

  GenericCollectionMember<int, BNmuonCollection>
  allMuonTrackerMuon(Reflex::Type::ByName("BNmuon"), &(tightLoosePreselectedMuons.ptrToItems), "isTrackerMuon", "all_muons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allMuonTrackerMuon);

  GenericCollectionMember<double, BNmuonCollection>
  allMuonPt(Reflex::Type::ByName("BNmuon"), &(tightLoosePreselectedMuons.ptrToItems), "pt", "all_muons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allMuonPt);

  GenericCollectionMember<double, BNmuonCollection>
  allMuonEta(Reflex::Type::ByName("BNmuon"), &(tightLoosePreselectedMuons.ptrToItems), "eta", "all_muons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allMuonEta);

  ////////// all electrons //////////
  GenericCollectionMember<int, BNelectronCollection>
  allElectronNumExpInnerHits(Reflex::Type::ByName("BNelectron"), &(tightLoosePreselectedElectrons.ptrToItems), "numberOfExpectedInnerHits", "all_electrons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allElectronNumExpInnerHits);

  GenericCollectionMember<int, BNelectronCollection>
  allElectronPassConvVeto(Reflex::Type::ByName("BNelectron"), &(tightLoosePreselectedElectrons.ptrToItems), "passConvVeto", "all_electrons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allElectronPassConvVeto);

  GenericCollectionMember<double, BNelectronCollection>
  allElectronEta(Reflex::Type::ByName("BNelectron"), &(tightLoosePreselectedElectrons.ptrToItems), "eta", "all_electrons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allElectronEta);

  GenericCollectionMember<double, BNelectronCollection>
  allElectronPt(Reflex::Type::ByName("BNelectron"), &(tightLoosePreselectedElectrons.ptrToItems), "pt", "all_electrons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allElectronPt);

  ////////// tight leptons /////////
  GenericCollectionMember<double, BNleptonCollection>
  tightLeptonInnerTkPt(Reflex::Type::ByName("BNlepton"), &(tightLeptons.ptrToItems), "innerTrackPt", "tight_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&tightLeptonInnerTkPt);

  GenericCollectionMember<double, BNleptonCollection>
  tightLeptonInnerTkPtError(Reflex::Type::ByName("BNlepton"), &(tightLeptons.ptrToItems), "innerTrackPtError", "tight_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&tightLeptonInnerTkPtError);

  GenericCollectionMember<double, BNleptonCollection>
  tightLeptonPt(Reflex::Type::ByName("BNlepton"), &(tightLeptons.ptrToItems), "pt", "tight_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&tightLeptonPt);

  GenericCollectionMember<double, BNleptonCollection>
  tightLeptonEta(Reflex::Type::ByName("BNlepton"), &(tightLeptons.ptrToItems), "eta", "tight_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&tightLeptonEta);

  ////////// all taus //////////
  GenericCollectionMember<double, BNtauCollection>
  allTauPt(Reflex::Type::ByName("BNtau"), &(tightLoosePreselectedTaus.ptrToItems), "pt", "all_taus_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allTauPt);

  GenericCollectionMember<double, BNtauCollection>
  allTauEta(Reflex::Type::ByName("BNtau"), &(tightLoosePreselectedTaus.ptrToItems), "eta", "all_taus_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allTauEta);

  ////////// all jets //////////
  GenericCollectionMember<double, BNjetCollection>
  allJetPt(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems), "pt", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetPt);

  GenericCollectionMember<double, BNjetCollection>
  allJetEta(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems), "eta", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetEta);

  GenericCollectionMember<double, BNjetCollection>
  allJetPhi(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems), "phi", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetPhi);

  GenericCollectionMember<double, BNjetCollection>
  allJetCSV(Reflex::Type::ByName("BNjet"),  &(jets.ptrToItems), "btagCombinedSecVertex", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetCSV);

  ////////// all jets, ordered by CSV //////////
  GenericCollectionMember<double, BNjetCollection>
  allJetByCSVPt(Reflex::Type::ByName("BNjet"), &(jetsByCSV.ptrToItems), "pt", "jets_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetByCSVPt);

  GenericCollectionMember<double, BNjetCollection>
  allJetByCSVEta(Reflex::Type::ByName("BNjet"), &(jetsByCSV.ptrToItems), "eta", "jets_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetByCSVEta);

  GenericCollectionMember<double, BNjetCollection>
  allJetByCSVPhi(Reflex::Type::ByName("BNjet"), &(jetsByCSV.ptrToItems), "phi", "jets_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetByCSVPhi);

  GenericCollectionMember<double, BNjetCollection>
  allJetByCSVCSV(Reflex::Type::ByName("BNjet"),  &(jetsByCSV.ptrToItems), "btagCombinedSecVertex", "jets_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetByCSVCSV);

  ////////// lepMVA jets //////////
  GenericCollectionMember<double, BNjetCollection>
  lepMVAJetPt(Reflex::Type::ByName("BNjet"), &(jetsForLepMVA.ptrToItems), "pt", "lepMVAjets_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&lepMVAJetPt);

  GenericCollectionMember<double, BNjetCollection>
  lepMVAJetEta(Reflex::Type::ByName("BNjet"), &(jetsForLepMVA.ptrToItems), "eta", "lepMVAjets_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&lepMVAJetEta);

  GenericCollectionMember<double, BNjetCollection>
  lepMVAJetPhi(Reflex::Type::ByName("BNjet"), &(jetsForLepMVA.ptrToItems), "phi", "lepMVAjets_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&lepMVAJetPhi);

  GenericCollectionMember<double, BNjetCollection>
  lepMVAJetCSV(Reflex::Type::ByName("BNjet"),  &(jetsForLepMVA.ptrToItems), "btagCombinedSecVertex", "lepMVAjets_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&lepMVAJetCSV);

  ////////// met //////////
  GenericCollectionMember<double, BNmetCollection>
  metPt(Reflex::Type::ByName("BNmet"), &(met.ptrToItems), "pt", "met",  KinematicVariableConstants::FLOAT_INIT, 1);
  kinVars.push_back(&metPt);

//   GenericCollectionMember<double, BNmetCollection>
//   met1d(Reflex::Type::ByName("BNmet"), &(selectedCollections.metpfType1CorrectedMetBNCollection), "pt", "metpfType1CorrectedMetBN",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&met1d);

  int numExtraPartons = -99;
  summaryTree->Branch("numExtraPartons", &numExtraPartons);

  ////////// event info //////////
  GenericCollectionMember<unsigned, BNeventCollection>
  runNumber(Reflex::Type::ByName("BNevent"), &(events.ptrToItems), "run", "eventInfo", KinematicVariableConstants::UINT_INIT, 1);
  kinVars.push_back(&runNumber);

  GenericCollectionMember<unsigned, BNeventCollection>
  lumiBlock(Reflex::Type::ByName("BNevent"), &(events.ptrToItems), "lumi", "eventInfo",  KinematicVariableConstants::UINT_INIT, 1);
  kinVars.push_back(&lumiBlock);

  // this is a long inside BNevent: just using keyword long won't work-- needs to be Long64_t
  GenericCollectionMember<Long64_t, BNeventCollection>
  eventNumber(Reflex::Type::ByName("BNevent"),  &(events.ptrToItems), "evt", "eventInfo",  KinematicVariableConstants::INT_INIT, 1);
  kinVars.push_back(&eventNumber);

  MetLD myMetLD(&myMHT, &metPt);
  kinVars.push_back(&myMetLD);

  FinalBDT myFinalBDT(&allLeptonEta, &allLeptonPt, &myMHT, &myMinDeltaRLep2Jet, &myMtMetLep, &mySumPt);
  kinVars.push_back(&myFinalBDT);

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

    tightTaus.initializeRawItemsSortedByPt(ev, "BNproducer","selectedPatTausPFlow");
    tightTaus.keepSelectedParticles(tauTightID);
    tightLooseTaus.initializeRawItems(tightTaus.rawItems);
    tightLooseTaus.keepSelectedParticles(tauTightID);
    tightLoosePreselectedTaus.initializeRawItems(tightTaus.rawItems);
    tightLoosePreselectedTaus.keepSelectedParticles(tauPreselectedID);

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

    met.initializeRawItems(ev, "BNproducer","patMETsPFlow");
    met.getCorrectedMet(jets);
    events.initializeRawItems(ev, "BNproducer", "");
    mcParticles.initializeRawItems(ev, "BNproducer", "MCstatus3");
    primaryVertexes.initializeRawItems(ev, "BNproducer","offlinePrimaryVertices");
    hltCollection.initializeRawItems(ev, "BNproducer", "HLT");

    genHiggsParticles.initializeRawItems(mcParticles.rawItems);
    auto higgsPDGID = [] (BNmcparticle p) { return (p.id == 25); };
    genHiggsParticles.keepSelectedParticles(higgsPDGID);
    genTopParticles.initializeRawItems(mcParticles.rawItems);
    auto topPDGID = [] (BNmcparticle p) { return (p.id == 6); };
    genTopParticles.keepSelectedParticles(topPDGID);
    genAntiTopParticles.initializeRawItems(mcParticles.rawItems);
    auto antitopPDGID = [] (BNmcparticle p) { return (p.id == -6); };

    float lep1_eta = KinematicVariableConstants::FLOAT_INIT;
    float lep1_phi = KinematicVariableConstants::FLOAT_INIT;
    if (tightLoosePreselectedLeptons.items.size() >= 1) {
      lep1_eta = tightLoosePreselectedLeptons.items.at(0)->eta;
      lep1_phi = tightLoosePreselectedLeptons.items.at(0)->phi; }
    float lep1_jet_deltaR = 0.7;
    jetsClosestToLep1.initializeRawItems(jets.items);
    auto jetsClosestToLep1Auto = [] (BNjet j, float x, float y, float z) { return (sqrt( pow(j.eta - x, 2)+pow(j.phi - y,2) ) < z); };
    jetsClosestToLep1.keepSelectedParticles(jetsClosestToLep1Auto, lep1_eta, lep1_phi, lep1_jet_deltaR);
    
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
    passAllCuts = passAllCuts &&  LeptonCutThisAnalysis(tightLoosePreselectedLeptons.items);

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

    LeptonVarsThisAnalysis(tightMuons.items, tightElectrons.items, LeptonCutThisAnalysis(tightLoosePreselectedLeptons.items), TwoMuon, TwoElectron, MuonElectron);

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

// old variable graveyard

//   GenericCollectionMember<double, BNleptonCollection>
//   allLeptonComPt(Reflex::Type::ByName("BNlepton"),
//                  &(tightLoosePreselectedLeptons.ptrToItems),
//                  "comPT",
//                  "all_leptons_by_pt",
//                  KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&allLeptonComPt);

//   GenericCollectionMember<double, BNleptonCollection>
//   allLeptonSamPt(Reflex::Type::ByName("BNlepton"),
//                  &(tightLoosePreselectedLeptons.ptrToItems),
//                  "samPT",
//                  "all_leptons_by_pt",
//                  KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&allLeptonSamPt);

//   DBCorrectedRelIsoDR04s myDBCorrectedRelIsoDR04s(&lepHelper, 4);
//   kinVars.push_back(&myDBCorrectedRelIsoDR04s);

//   GenericCollectionMember<double, BNleptonCollection>
//   allLeptonNeutralHadronIsoDR04(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
//                                 "neutralHadronIsoDR04", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&allLeptonNeutralHadronIsoDR04);

//   GenericCollectionMember<double, BNleptonCollection>
//   allLeptonPhotonIsoDR04(Reflex::Type::ByName("BNlepton"),
//                          &(tightLoosePreselectedLeptons.ptrToItems), "photonIsoDR04",
//                          "all_leptons_by_pt", KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&allLeptonPhotonIsoDR04);

//   GenericCollectionMember<double, BNleptonCollection>
//   allLeptonPUChargedHadronIsoDR04(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
//                                   "puChargedHadronIsoDR04", "all_leptons_by_pt", KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&allLeptonPUChargedHadronIsoDR04);

//   GenericCollectionMember<double, BNleptonCollection>
//   allLeptonChargedHadronIso(Reflex::Type::ByName("BNlepton"),
//                             &(tightLoosePreselectedLeptons.ptrToItems),
//                             "chargedHadronIso", "all_leptons_by_pt", KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&allLeptonChargedHadronIso);

