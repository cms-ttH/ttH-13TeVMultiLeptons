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

  muonID::muonID muonTightID = muonID::muonSideTightCut;
  muonID::muonID muonLooseID = muonID::muonSideLooseCut;
  muonID::muonID muonPreselectedID = muonID::muonSide;
  electronID::electronID electronTightID = electronID::electronSideTightCut;
  electronID::electronID electronLooseID = electronID::electronSideLooseCut;
  electronID::electronID electronPreselectedID = electronID::electronSide;

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

  //ttH hadrons reweighting
  CSVWeights myCSV(beanHelper, &(jets.ptrToItems), jetSyst, "skipSyst");
  kinVars.push_back(&myCSV);

  PUWeights myPU(&lepHelper, &(events.ptrToItems), "skipSyst");
  kinVars.push_back(&myPU);

  TopPtWeights myTopPt(&lepHelper, &(mcParticles.ptrToItems), "skipSyst");
  kinVars.push_back(&myTopPt);

  //CERN version
  RecoIDIsoSIPSFs myRecoIDIsoSIPSF3Lep(3, &(tightLoosePreselectedLeptons.ptrToItems));
  kinVars.push_back(&myRecoIDIsoSIPSF3Lep);

  LeptonTriggerScaleFactors myLepTrig(&lepHelper, &(tightMuons.ptrToItems), &(looseMuons.ptrToItems),
                                      &(preselectedMuons.ptrToItems), &(tightElectrons.ptrToItems),
                                      &(looseElectrons.ptrToItems), &(preselectedElectrons.ptrToItems));
  kinVars.push_back(&myLepTrig);

  TightChargeAndLepCutScaleFactors myTightChargeAndLepCutSF3Lep(3, &(tightLoosePreselectedLeptons.ptrToItems));
  kinVars.push_back(&myTightChargeAndLepCutSF3Lep);

  TightChargeAndLepCutScaleFactorsPerLepton myTightChargeAndLepCutSFPerLepton(4, &(tightLoosePreselectedLeptons.ptrToItems));
  kinVars.push_back(&myTightChargeAndLepCutSFPerLepton);

  TightChargeAndLepCutScaleFactorsPerLepton myTightChargeAndLepCutSFPerSSLepton(2, &(leptonsSS.ptrToItems), "_SS");
  kinVars.push_back(&myTightChargeAndLepCutSFPerSSLepton);

  CleanEventVars myClean(&lepHelper, &(events.ptrToItems), &(primaryVertexes.ptrToItems));
  kinVars.push_back(&myClean);

  CheckTwoLepTrigger checkTrig(&lepHelper, &(hltCollection.ptrToItems));
  kinVars.push_back(&checkTrig);

  LepCuts<BNleptonCollection> myLepCutsAllLeptons(beanHelper, &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 4);
  kinVars.push_back(&myLepCutsAllLeptons);

  LepCuts<BNleptonCollection> myLepCutsAllLeptonsSS(beanHelper, &(leptonsSS.ptrToItems), "all_SS_leptons_by_pt", 2);
  kinVars.push_back(&myLepCutsAllLeptonsSS);

  LepCuts<BNleptonCollection> myLepCutsAllLeptonsOS(beanHelper, &(leptonsOS.ptrToItems), "all_OS_leptons_by_pt", 2);
  kinVars.push_back(&myLepCutsAllLeptonsOS);

  // Two lepton kinematics
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMinMassLepLepSFOS("mass", "min", "min_mass_leplep_SFOS",
                                                                                &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                                                                                &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                                                                                -99, "same_flavour", "opposite_sign");
  kinVars.push_back(&myMinMassLepLepSFOS);
  
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMinMassLepLep("mass", "min", "min_mass_leplep_all",
                                                                            &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                                                                            &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99);
  kinVars.push_back(&myMinMassLepLep);
  
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZLikeMassLepLepSFOSAll("mass", "closest_to", "ZLike_mass_leplep_SFOS_all",
                                                                                     &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                                                                                     &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                                                                                     91.2, "same_flavour", "opposite_sign");
  kinVars.push_back(&myZLikeMassLepLepSFOSAll);  

  TightCharges myTightCharges(&(tightLoosePreselectedLeptons.ptrToItems), "CERN_tight_charge", "all_leptons_by_pt", 4);
  kinVars.push_back(&myTightCharges);

  TightCharges myTightChargesSS(&(leptonsSS.ptrToItems), "CERN_tight_charge", "all_SS_leptons_by_pt", 2);
  kinVars.push_back(&myTightChargesSS);

  //////////////////////////////////
  //Variables for match_ttbarZ_3l, match_ttbarW_3l, match_ttbar_ll_fake_3l
  //////////////////////////////////
  GenericCollectionSizeVariable<BNleptonCollection> numLeptonsFromW(&(leptonsFromW.ptrToItems), "numLeptonsFromW");
  kinVars.push_back(&numLeptonsFromW);
//   //cutvar for ttbar_lj
//   numLeptonsFromW.setCutMin(1);
//   cutVars.push_back(&numLeptonsFromW);
//   //cutvar for ttbar_ll
//   numLeptonsFromW.setCutMin(2);
//   cutVars.push_back(&numLeptonsFromW);

  GenericCollectionMember<int, BNleptonCollection> LeptonsFromWTkCharge(Reflex::Type::ByName("BNlepton"), &(leptonsFromW.ptrToItems),
                                                                        "tkCharge", "leptonsFromW",  KinematicVariableConstants::INT_INIT, 3);
  kinVars.push_back(&LeptonsFromWTkCharge);
  
  TwoObjectKinematic<BNleptonCollection,BNjetCollection>
    myMassLepFromWJet("mass", "all_pairs", "mass_lepFromW_jet",
                        &(leptonsFromW.ptrToItems), "leptonsFromW", 1, 3,
                        &(jets.ptrToItems), "jets_by_pt", 1, 6);
  kinVars.push_back(&myMassLepFromWJet);
  
  //////////////////////////////////
  //Variables for match_ttbarZ_3l, match_ttbarW_3l
  //////////////////////////////////
  TwoObjectKinematic<BNjetCollection,BNjetCollection>
    myDijetMasses("mass", "all_pairs", "dijet_mass",
                  &(jets.ptrToItems), "jets_by_pt", 1, 6,
                  &(jets.ptrToItems), "jets_by_pt", 1, 6);
  kinVars.push_back(&myDijetMasses);

  //////////////////////////////////
  //Variables for match_ttbarZ_3l
  //////////////////////////////////
  GenericCollectionSizeVariable<BNjetCollection> numJetsFromW(&(jetsFromW.ptrToItems), "numJetsFromW");
  kinVars.push_back(&numJetsFromW);

  GenericCollectionSizeVariable<BNjetCollection> numJetsFromLepTop(&(jetsFromLepTop.ptrToItems), "numJetsFromLepTop");
  kinVars.push_back(&numJetsFromLepTop);

  GenericCollectionSizeVariable<BNjetCollection> numJetsFromHadTop(&(jetsFromHadTop.ptrToItems), "numJetsFromHadTop");
  kinVars.push_back(&numJetsFromHadTop);

  GenericCollectionSizeVariable<BNleptonCollection> numLeptonsFromZ(&(leptonsFromZ.ptrToItems), "numLeptonsFromZ");
  kinVars.push_back(&numLeptonsFromZ);

  GenericCollectionMember<double, BNjetCollection> genWJetCSV(Reflex::Type::ByName("BNjet"),  &(jetsFromW.ptrToItems),
                                                             "btagCombinedSecVertex", "jetsFromW_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&genWJetCSV);

  GenericCollectionMember<double, BNjetCollection> genLepTopJetCSV(Reflex::Type::ByName("BNjet"),  &(jetsFromLepTop.ptrToItems),
                                                             "btagCombinedSecVertex", "jetsFromLepTop",  KinematicVariableConstants::FLOAT_INIT, 1);
  kinVars.push_back(&genLepTopJetCSV);

  GenericCollectionMember<double, BNjetCollection> genHadTopJetCSV(Reflex::Type::ByName("BNjet"),  &(jetsFromHadTop.ptrToItems),
                                                             "btagCombinedSecVertex", "jetsFromHadTop",  KinematicVariableConstants::FLOAT_INIT, 1);
  kinVars.push_back(&genHadTopJetCSV);

  GenericCollectionMember<double, BNjetCollection> genWJetCharge(Reflex::Type::ByName("BNjet"),  &(jetsFromW.ptrToItems),
                                                             "charge", "jetsFromW_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&genWJetCharge);

  GenericCollectionMember<double, BNjetCollection> genLepTopJetCharge(Reflex::Type::ByName("BNjet"),  &(jetsFromLepTop.ptrToItems),
                                                             "charge", "jetsFromLepTop",  KinematicVariableConstants::FLOAT_INIT, 1);
  kinVars.push_back(&genLepTopJetCharge);

  GenericCollectionMember<double, BNjetCollection> genHadTopJetCharge(Reflex::Type::ByName("BNjet"),  &(jetsFromHadTop.ptrToItems),
                                                             "charge", "jetsFromHadTop",  KinematicVariableConstants::FLOAT_INIT, 1);
  kinVars.push_back(&genHadTopJetCharge);

  GenericCollectionMember<double, BNjetCollection> genWJetJetChargeRelativePtWeighted(Reflex::Type::ByName("BNjet"),  &(jetsFromW.ptrToItems),
                                                             "jetChargeRelativePtWeighted", "jetsFromW_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&genWJetJetChargeRelativePtWeighted);

  GenericCollectionMember<double, BNjetCollection> genLepTopJetJetChargeRelativePtWeighted(Reflex::Type::ByName("BNjet"),  &(jetsFromLepTop.ptrToItems),
                                                             "jetChargeRelativePtWeighted", "jetsFromLepTop",  KinematicVariableConstants::FLOAT_INIT, 1);
  kinVars.push_back(&genLepTopJetJetChargeRelativePtWeighted);

  GenericCollectionMember<double, BNjetCollection> genHadTopJetJetChargeRelativePtWeighted(Reflex::Type::ByName("BNjet"),  &(jetsFromHadTop.ptrToItems),
                                                             "jetChargeRelativePtWeighted", "jetsFromHadTop",  KinematicVariableConstants::FLOAT_INIT, 1);
  kinVars.push_back(&genHadTopJetJetChargeRelativePtWeighted);

  GenericCollectionMember<int, BNjetCollection> genWJetFlavour(Reflex::Type::ByName("BNjet"),  &(jetsFromW.ptrToItems),
                                                             "flavour", "jetsFromW_by_CSV",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&genWJetFlavour);

  GenericCollectionMember<int, BNjetCollection> genWJetGenPartonId(Reflex::Type::ByName("BNjet"),  &(jetsFromW.ptrToItems),
                                                             "genPartonId", "jetsFromW_by_CSV",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&genWJetGenPartonId);

  TwoObjectKinematic<BNmetCollection,BNleptonCollection>
    myGenWMtMetLep("MT", "min", "gen_W_MT_met_lep",
                   &(met.ptrToItems), "met", 1, 1,
                   &(leptonsFromW.ptrToItems), "leptonsFromW", 1, 1);
  kinVars.push_back(&myGenWMtMetLep);
  
  TwoObjectKinematic<BNjetCollection,BNjetCollection>
    myGenWDijetMass("mass", "vector_sum", "gen_W_dijet_mass",
                    &(jetsFromW.ptrToItems), "jetsFromW_by_CSV", 1, 1,
                    &(jetsFromW.ptrToItems), "jetsFromW_by_CSV", 2, 2);
  kinVars.push_back(&myGenWDijetMass);
  
  TwoObjectKinematic<BNjetCollection,BNjetCollection>
    myGenHadTopTrijetMass("mass", "vector_sum", "gen_hadTop_trijet_mass",
                          &(jetsFromW.ptrToItems), "jetsFromW_by_CSV", 1, 2,
                          &(jetsFromHadTop.ptrToItems), "jetsFromHadTop", 1, 1);
  kinVars.push_back(&myGenHadTopTrijetMass);
  
  ThreeObjectKinematic<BNjetCollection,BNjetCollection,BNjetCollection>
    myGenTTbarQuadjetMass("mass", "vector_sum", "gen_ttbar_quadjet_mass",
                          &(jetsFromW.ptrToItems), "jetsFromW_by_CSV", 1, 2,
                          &(jetsFromLepTop.ptrToItems), "jetsFromLepTop", 1, 1,
                          &(jetsFromHadTop.ptrToItems), "jetsFromHadTop", 1, 1);
  kinVars.push_back(&myGenTTbarQuadjetMass);

  ThreeObjectKinematic<BNjetCollection,BNjetCollection,BNjetCollection>
    myGenTTbarQuadjetMT("MT", "vector_sum", "gen_ttbar_quadjet_MT",
                          &(jetsFromW.ptrToItems), "jetsFromW_by_CSV", 1, 2,
                          &(jetsFromLepTop.ptrToItems), "jetsFromLepTop", 1, 1,
                          &(jetsFromHadTop.ptrToItems), "jetsFromHadTop", 1, 1);
  kinVars.push_back(&myGenTTbarQuadjetMT);

  ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection>
    myGenLepTopMtMetLepB("MT", "min", "gen_lepTop_MT_met_lep_b",
                       &(met.ptrToItems), "met", 1, 1,
                       &(leptonsFromW.ptrToItems), "leptonsFromW", 1, 1,
                       &(jetsFromLepTop.ptrToItems), "jetsFromLepTop", 1, 1);
  kinVars.push_back(&myGenLepTopMtMetLepB);
  
  TwoObjectKinematic<BNleptonCollection,BNjetCollection>
    myGenLepTopMassLepB("mass", "min", "gen_lepTop_mass_lep_b",
                       &(leptonsFromW.ptrToItems), "leptonsFromW", 1, 1,
                       &(jetsFromLepTop.ptrToItems), "jetsFromLepTop", 1, 1);
  kinVars.push_back(&myGenLepTopMassLepB);
  
  ThreeObjectKinematic<BNjetCollection,BNjetCollection,BNjetCollection>
    myTrijetMasses("mass", "all_pairs", "trijet_mass",
                  &(jets.ptrToItems), "jets_by_pt", 1, 6,
                  &(jets.ptrToItems), "jets_by_pt", 1, 6,
                  &(jets.ptrToItems), "jets_by_pt", 1, 6);
  kinVars.push_back(&myTrijetMasses);

  FourObjectKinematic<BNjetCollection,BNjetCollection,BNjetCollection,BNjetCollection>
    myQuadjetMasses("mass", "all_pairs", "quadjet_mass",
                    &(jets.ptrToItems), "jets_by_pt", 1, 6,
                    &(jets.ptrToItems), "jets_by_pt", 1, 6,
                    &(jets.ptrToItems), "jets_by_pt", 1, 6,
                    &(jets.ptrToItems), "jets_by_pt", 1, 6);
  kinVars.push_back(&myQuadjetMasses);
  
  FourObjectKinematic<BNjetCollection,BNjetCollection,BNjetCollection,BNjetCollection>
    myQuadjetMTs("MT", "all_pairs", "quadjet_MT",
                 &(jets.ptrToItems), "jets_by_pt", 1, 6,
                 &(jets.ptrToItems), "jets_by_pt", 1, 6,
                 &(jets.ptrToItems), "jets_by_pt", 1, 6,
                 &(jets.ptrToItems), "jets_by_pt", 1, 6);
  kinVars.push_back(&myQuadjetMTs);

  ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection>
    myMtMetLepFromWJet("MT", "all_pairs", "MT_met_lepFromW_jet",
                       &(met.ptrToItems), "met", 1, 1,
                       &(leptonsFromW.ptrToItems), "leptonsFromW", 1, 1,
                       &(jets.ptrToItems), "jets_by_pt", 1, 6);
  kinVars.push_back(&myMtMetLepFromWJet);
  
  ///////////////////////////////////////////////////////////////
  //Variables for match_ttbarW_3l and match_ttbar_ll_fake_3l.yaml
  ///////////////////////////////////////////////////////////////
  GenericCollectionSizeVariable<BNjetCollection> numJetsFromTop(&(jetsFromTop.ptrToItems), "numJetsFromTop");
  kinVars.push_back(&numJetsFromTop);

  GenericCollectionSizeVariable<BNjetCollection> numJetsFromAntiTop(&(jetsFromAntiTop.ptrToItems), "numJetsFromAntiTop");
  kinVars.push_back(&numJetsFromAntiTop);

  GenericCollectionSizeVariable<BNleptonCollection> numLeptonsFromTop(&(leptonsFromTop.ptrToItems), "numLeptonsFromTop");
  kinVars.push_back(&numLeptonsFromTop);

  GenericCollectionSizeVariable<BNleptonCollection> numLeptonsFromAntiTop(&(leptonsFromAntiTop.ptrToItems), "numLeptonsFromAntiTop");
  kinVars.push_back(&numLeptonsFromAntiTop);

  GenericCollectionMember<double, BNjetCollection> genTopJetCSV(Reflex::Type::ByName("BNjet"),  &(jetsFromTop.ptrToItems),
                                                             "btagCombinedSecVertex", "jetsFromTop",  KinematicVariableConstants::FLOAT_INIT, 1);
  kinVars.push_back(&genTopJetCSV);

  GenericCollectionMember<double, BNjetCollection> genAntiTopJetCSV(Reflex::Type::ByName("BNjet"),  &(jetsFromAntiTop.ptrToItems),
                                                             "btagCombinedSecVertex", "jetsFromAntiTop",  KinematicVariableConstants::FLOAT_INIT, 1);
  kinVars.push_back(&genAntiTopJetCSV);

  GenericCollectionMember<double, BNjetCollection> genTopJetCharge(Reflex::Type::ByName("BNjet"),  &(jetsFromTop.ptrToItems),
                                                             "charge", "jetsFromTop",  KinematicVariableConstants::FLOAT_INIT, 1);
  kinVars.push_back(&genTopJetCharge);

  GenericCollectionMember<double, BNjetCollection> genAntiTopJetCharge(Reflex::Type::ByName("BNjet"),  &(jetsFromAntiTop.ptrToItems),
                                                             "charge", "jetsFromAntiTop",  KinematicVariableConstants::FLOAT_INIT, 1);
  kinVars.push_back(&genAntiTopJetCharge);

  TwoObjectKinematic<BNleptonCollection,BNjetCollection>
    myGenTopMassLepB("mass", "min", "gen_top_mass_lep_b",
                     &(leptonsFromTop.ptrToItems), "leptonsFromTop", 1, 1,
                     &(jetsFromTop.ptrToItems), "jetsFromTop", 1, 1);
  kinVars.push_back(&myGenTopMassLepB);
  
  TwoObjectKinematic<BNleptonCollection,BNjetCollection>
    myGenAntiTopMassLepB("mass", "min", "gen_antiTop_mass_lep_b",
                     &(leptonsFromAntiTop.ptrToItems), "leptonsFromAntiTop", 1, 1,
                     &(jetsFromAntiTop.ptrToItems), "jetsFromAntiTop", 1, 1);
  kinVars.push_back(&myGenAntiTopMassLepB);

  ///////////////////////////////
  //Variables for match_ttbarW_3l
  ///////////////////////////////
  TwoObjectKinematic<BNjetCollection,BNjetCollection>
    myGenTTbarDijetMass("mass", "vector_sum", "gen_ttbar_dijet_mass",
                        &(jetsFromTop.ptrToItems), "jetsFromTop", 1, 1,
                        &(jetsFromAntiTop.ptrToItems), "jetsFromAntiTop", 1, 1);
  kinVars.push_back(&myGenTTbarDijetMass);
  
  TwoObjectKinematic<BNjetCollection,BNjetCollection>
    myGenTTbarDijetMT("MT", "vector_sum", "gen_ttbar_dijet_MT",
                      &(jetsFromTop.ptrToItems), "jetsFromTop", 1, 1,
                      &(jetsFromAntiTop.ptrToItems), "jetsFromAntiTop", 1, 1);
  kinVars.push_back(&myGenTTbarDijetMT);

  TwoObjectKinematic<BNjetCollection,BNjetCollection>
    myDijetMTs("MT", "all_pairs", "dijet_MT",
                  &(jets.ptrToItems), "jets_by_pt", 1, 4,
                  &(jets.ptrToItems), "jets_by_pt", 1, 4);
  kinVars.push_back(&myDijetMTs);

  //////////////////////////////////////
  //Variables for match_ttbar_ll_fake_3l
  //////////////////////////////////////
  GenericCollectionSizeVariable<BNleptonCollection> numLeptonsFromBFromTop(&(leptonsFromBFromTop.ptrToItems), "numLeptonsFromBFromTop");
  kinVars.push_back(&numLeptonsFromBFromTop);

  GenericCollectionSizeVariable<BNleptonCollection> numLeptonsFromBFromAntiTop(&(leptonsFromBFromAntiTop.ptrToItems), "numLeptonsFromBFromAntiTop");
  kinVars.push_back(&numLeptonsFromBFromAntiTop);

  TwoObjectKinematic<BNleptonCollection,BNleptonCollection>
    myGenTopMassLepBlep("mass", "min", "gen_top_mass_lep_blep",
                     &(leptonsFromTop.ptrToItems), "leptonsFromTop", 1, 1,
                     &(leptonsFromBFromTop.ptrToItems), "leptonsFromBFromTop", 1, 1);
  kinVars.push_back(&myGenTopMassLepBlep);
  
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection>
    myGenAntiTopMassLepBlep("mass", "min", "gen_antiTop_mass_lep_blep",
                     &(leptonsFromAntiTop.ptrToItems), "leptonsFromAntiTop", 1, 1,
                     &(leptonsFromBFromAntiTop.ptrToItems), "leptonsFromBFromAntiTop", 1, 1);
  kinVars.push_back(&myGenAntiTopMassLepBlep);
  
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMassLepLepOS("mass", "all_pairs", "mass_leplep_OS",
                                                                           &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 3,
                                                                           &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 3,
                                                                           -99, "opposite_sign");
  kinVars.push_back(&myMassLepLepOS);

  /////////////////////////////////
  //// Leptons
  /////////////////////////////////

  // pT
  
  GenericCollectionMember<double, BNleptonCollection> LeptonPt(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
                                                                  "pt", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 3);
  kinVars.push_back(&LeptonPt);

  GenericCollectionMember<int, BNleptonCollection> allLeptonTkCharge(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
                                                                     "tkCharge", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 3);
  kinVars.push_back(&allLeptonTkCharge);

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

  ////////// jets by pt //////////
  GenericCollectionMember<double, BNjetCollection> allJetPt(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems),
                                                            "pt", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetPt);

  GenericCollectionMember<double, BNjetCollection> allJetCharge(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems),
                                                            "charge", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetCharge);

  GenericCollectionMember<double, BNjetCollection> allJetCSV(Reflex::Type::ByName("BNjet"),  &(jets.ptrToItems),
                                                             "btagCombinedSecVertex", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetCSV);

//   ////////// mc particles ////////
  int numExtraPartons = -99;
  summaryTree->Branch("numExtraPartons", &numExtraPartons);

  bool dibosonPlusHFKeepEventBool = false;
  
  ////////// event info //////////

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

    //Can't place above "tightLoosePreselectedMuons.keepSelectedParticles(muonPreselectedID);" line - won't work
    auto electronPt10 = [] (BNelectron e) { return (e.pt > 10); };
    tightLoosePreselectedElectrons.keepSelectedParticles(electronPt10);
    auto muonPt10 = [] (BNmuon m) { return (m.pt > 10); };
    tightLoosePreselectedMuons.keepSelectedParticles(muonPt10);
    
    // Require reset before first pushback to avoid keeping leptons from previous event
    tightLeptons.resetAndPushBack(tightElectrons.items);
    tightLeptons.pushBackAndSort(tightMuons.items);
    tightLooseLeptons.resetAndPushBack(tightLooseElectrons.items);
    tightLooseLeptons.pushBackAndSort(tightLooseMuons.items);
    tightLoosePreselectedLeptons.resetAndPushBack(tightLoosePreselectedElectrons.items);
    tightLoosePreselectedLeptons.pushBackAndSort(tightLoosePreselectedMuons.items);

    jets.initializeRawItemsSortedByPt(ev, "BNproducer","selectedPatJetsPFlow");
    jets.correctRawJets(jetSyst);
    jets.cleanJets(tightLoosePreselectedLeptons.items);

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

    genWFromTops.initializeRawItems(mcParticles.rawItems);
    auto WFromTopPDGID = [] (BNmcparticle p) { return (p.id == 24 && p.motherId == 6); };
    genWFromTops.keepSelectedParticles(WFromTopPDGID);
    
    genWFromAntiTops.initializeRawItems(mcParticles.rawItems);
    auto WFromAntiTopPDGID = [] (BNmcparticle p) { return (p.id == -24 && p.motherId == -6); };
    genWFromAntiTops.keepSelectedParticles(WFromAntiTopPDGID);

    // Initialize SFOS pair closest to Z mass
    myZLikeMassLepLepSFOSAll.reset();
    myZLikeMassLepLepSFOSAll.evaluate();
    
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
