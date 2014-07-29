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

//   int iJetFromLepTop = 1;
//   int iJetFromHadTop = 2;
//   int iJetFromW_1 = 3;
//   int iJetFromW_2 = 4;

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
//   tauID::tauID tauTightID = tauID::tauMedium;
//   tauID::tauID tauLooseID = tauID::tauLoose;
//   tauID::tauID tauPreselectedID = tauID::tauNonIso;

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

//   GenericCollection<BNtauCollection> tightTaus(beanHelper);
//   GenericCollection<BNtauCollection> tightLooseTaus(beanHelper);
//   GenericCollection<BNtauCollection> tightLoosePreselectedTaus(beanHelper);

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

//   GenericCollection<BNmcparticleCollection> genHiggs(beanHelper);
//   GenericCollection<BNmcparticleCollection> genTops(beanHelper);
//   GenericCollection<BNmcparticleCollection> genAntiTops(beanHelper);
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

  // declare your kinematic variables that you want
  // to be written out into the tree
  vector<ArbitraryVariable*> kinVars;
  vector<ArbitraryVariable*> cutVars;

  GenericCollectionSizeVariable<BNjetCollection> numJets(&(jets.ptrToItems), "numJets");
  kinVars.push_back(&numJets);
  numJets.setCutMin(2);
  //cutVars.push_back(&numJets);

  GenericCollectionSizeVariable<BNjetCollection> numLooseBJets(&(looseCSVJets.ptrToItems), "numLooseBJets");
  kinVars.push_back(&numLooseBJets);

  GenericCollectionSizeVariable<BNjetCollection> numMediumBJets(&(mediumCSVJets.ptrToItems), "numMediumBJets");
  kinVars.push_back(&numMediumBJets);

  GenericCollectionSizeVariable<BNjetCollection> numTightBJets(&(tightCSVJets.ptrToItems), "numTightBJets");
  kinVars.push_back(&numTightBJets);

  GenericCollectionSizeVariable<BNleptonCollection> numTightLeptons(&(tightLeptons.ptrToItems), "numTightLeptons");
  kinVars.push_back(&numTightLeptons);
  if (myConfig.sampleName.find("NP_sideband") == std::string::npos &&
      myConfig.sampleName.find("ttbar_") == std::string::npos &&
      myConfig.sampleName.find("singlet") == std::string::npos &&
      myConfig.sampleName.find("wjets") == std::string::npos) { //All prompt MC samples
    numTightLeptons.setCutMin(2);
  }
  else if (myConfig.sampleName.find("NP_sideband") != std::string::npos) { //NP_sideband
    numTightLeptons.setCutMax(1);
  }
  else { //non-prompt MC samples
    numTightLeptons.setCutMin(0);
  }
  //cutVars.push_back(&numTightLeptons);
  
  GenericCollectionSizeVariable<BNleptonCollection> numTightLooseLeptons(&(tightLooseLeptons.ptrToItems), "numTightLooseLeptons");
  kinVars.push_back(&numTightLooseLeptons);

  GenericCollectionSizeVariable<BNleptonCollection> numAllLeptons(&(tightLoosePreselectedLeptons.ptrToItems), "numAllLeptons");
  kinVars.push_back(&numAllLeptons);
  numAllLeptons.setCutMin(2);
  cutVars.push_back(&numAllLeptons);

  GenericCollectionSizeVariable<BNmuonCollection> numAllMuons(&(tightLoosePreselectedMuons.ptrToItems), "numAllMuons");
  kinVars.push_back(&numAllMuons);

  GenericCollectionSizeVariable<BNelectronCollection> numAllElectrons(&(tightLoosePreselectedElectrons.ptrToItems), "numAllElectrons");
  kinVars.push_back(&numAllElectrons);

//   GenericCollectionSizeVariable<BNtauCollection> numAllTaus(&(tightLoosePreselectedTaus.ptrToItems), "numAllTaus");
//   kinVars.push_back(&numAllTaus);

//   GenericCollectionSizeVariable<BNtauCollection> numTightLooseTaus(&(tightLooseTaus.ptrToItems), "numTightLooseTaus");
//   kinVars.push_back(&numTightLooseTaus);

//   GenericCollectionSizeVariable<BNtauCollection> numTightTaus(&(tightTaus.ptrToItems), "numTightTaus");
//   kinVars.push_back(&numTightTaus);

  //ttH hadrons reweighting
  CSVWeights myCSV(beanHelper, &(jets.ptrToItems));
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
  RecoIDIsoSIPSFs myRecoIDIsoSIPSF2Lep(2, &(tightLoosePreselectedLeptons.ptrToItems));
  kinVars.push_back(&myRecoIDIsoSIPSF2Lep);

  LeptonTriggerScaleFactors myLepTrig(&lepHelper, &(tightMuons.ptrToItems), &(looseMuons.ptrToItems),
                                      &(preselectedMuons.ptrToItems), &(tightElectrons.ptrToItems),
                                      &(looseElectrons.ptrToItems), &(preselectedElectrons.ptrToItems));
  kinVars.push_back(&myLepTrig);

  //Give particular collections
//   TightChargeAndLepMVAScaleFactors myTightChargeAndLepMVASF2Lep(2, &(tightLoosePreselectedLeptons.ptrToItems));
//   kinVars.push_back(&myTightChargeAndLepMVASF2Lep);

//   TightChargeAndLepMVAScaleFactorsPerLepton myTightChargeAndLepMVASFPerLepton(2, &(tightLoosePreselectedLeptons.ptrToItems));
//   kinVars.push_back(&myTightChargeAndLepMVASFPerLepton);

  TightChargeAndLepCutScaleFactors myTightChargeAndLepCutSF2Lep(2, &(tightLoosePreselectedLeptons.ptrToItems));
  kinVars.push_back(&myTightChargeAndLepCutSF2Lep);

  TightChargeAndLepCutScaleFactorsPerLepton myTightChargeAndLepCutSFPerLepton(2, &(tightLoosePreselectedLeptons.ptrToItems));
  kinVars.push_back(&myTightChargeAndLepCutSFPerLepton);

  CleanEventVars myClean(&lepHelper, &(events.ptrToItems), &(primaryVertexes.ptrToItems));
  kinVars.push_back(&myClean);

  CheckTwoLepTrigger checkTrig(&lepHelper, &(hltCollection.ptrToItems));
  kinVars.push_back(&checkTrig);

  LepMVAs<BNleptonCollection> myLepMVAsAllLeptons(&lepHelper, &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 3);
  kinVars.push_back(&myLepMVAsAllLeptons);

  LepCuts<BNleptonCollection> myLepCutsAllLeptons(&(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 3);
  kinVars.push_back(&myLepCutsAllLeptons);

//   DataDrivenFR<BNleptonCollection> myDataDrivenFR2Tight(&lepHelper, &(tightLoosePreselectedLeptons.ptrToItems), &(mediumCSVJets.ptrToItems),
//                                                         2, 0.7, "FR_merged_data", "QF_data_el", "_2_tight"); 
//   kinVars.push_back(&myDataDrivenFR2Tight);
  
  DataDrivenFRLepCut<BNleptonCollection> myDataDrivenFRLepCut2Tight(&(tightLoosePreselectedLeptons.ptrToItems),
                                                        2, 2, "FR_merged_data", "QF_data_el", "_2_tight"); 
  kinVars.push_back(&myDataDrivenFRLepCut2Tight);
  
  DataDrivenFRLepCut<BNleptonCollection> myDataDrivenFRLepCut2Loose(&(tightLoosePreselectedLeptons.ptrToItems),
                                                        2, 1, "FR_merged_data", "QF_data_el", "_2_loose"); 
  kinVars.push_back(&myDataDrivenFRLepCut2Loose);
  
  //Causes run-time error
  DBCorrectedRelIsoDR04s myDBCorrectedRelIsoDR04s(&lepHelper, &(tightLoosePreselectedLeptons.ptrToItems),
                                                  "all_leptons_by_pt", 1, 2);
  kinVars.push_back(&myDBCorrectedRelIsoDR04s);

  HiggsDecayType myHiggsDecayType(&lepHelper, &(mcParticles.ptrToItems));
  kinVars.push_back(&myHiggsDecayType);

  // Full event kinematics

  TwoObjectKinematic<BNleptonCollection,BNjetCollection>
    mySumPt("pt", "sum", "sum_pt",
            &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 2,
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
                       &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 2,
                       &(jets.ptrToItems), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMassOfEverything);

  ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection>
    myMTOfEverything("MT", "vector_sum", "MT_of_everything",
                       &(met.ptrToItems), "met", 1, 1,
                       &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 2,
                       &(jets.ptrToItems), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMTOfEverything);

  //SS ttbarW and 3l ttbarZ
  TwoObjectKinematic<BNjetCollection,BNjetCollection>
    myWLikeDijetMass81X1B("mass", "closest_to", "WLike_dijet_mass_X1b",
                          &(jetsByCSV.ptrToItems), "jets_by_CSV", 2, 99,
                          &(jetsByCSV.ptrToItems), "jets_by_CSV", 2, 99,
                          81);
  kinVars.push_back(&myWLikeDijetMass81X1B);

  TwoObjectKinematic<BNjetCollection,BNjetCollection>
    myWLikeDijetMass81X2B("mass", "closest_to", "WLike_dijet_mass_X2b",
                          &(jetsByCSV.ptrToItems), "jets_by_CSV", 3, 99,
                          &(jetsByCSV.ptrToItems), "jets_by_CSV", 3, 99,
                          81);
  kinVars.push_back(&myWLikeDijetMass81X2B);

  // Two lepton kinematics
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMassLep1Lep2("mass", "min", "mass_lep1_lep2",
                                                                           &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 1,
                                                                           &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 2, 2);
  kinVars.push_back(&myMassLep1Lep2);
  
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMassLep1Lep2OS("mass", "min", "mass_lep1_lep2_OS",
                                                                             &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 1,
                                                                             &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 2, 2,
                                                                             -99, "opposite_sign");
  kinVars.push_back(&myMassLep1Lep2OS);
  
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMinMassLepLepAll("mass", "min", "min_mass_leplep_all",
                                                                               &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                                                                               &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99);
  kinVars.push_back(&myMinMassLepLepAll);
  
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZLikeMassLepLepSFAll("mass", "closest_to", "ZLike_mass_leplep_SF_all",
                                                                                   &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                                                                                   &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                                                                                   91.2, "same_flavour");
  kinVars.push_back(&myZLikeMassLepLepSFAll);  
  
  TwoObjectKinematic<BNleptonCollection,BNjetCollection> myMHT("pt", "vector_sum", "mht",
                                                               &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 2,
                                                               &(jets.ptrToItems), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMHT);

  TightCharges myTightCharges(&(tightLoosePreselectedLeptons.ptrToItems), "CERN_tight_charge", "all_leptons_by_pt", 2);
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

  GenericCollectionSizeVariable<BNjetCollection> numJetsFromW(&(jetsFromW.ptrToItems), "numJetsFromW");
  kinVars.push_back(&numJetsFromW);

  GenericCollectionSizeVariable<BNjetCollection> numJetsFromLepTop(&(jetsFromLepTop.ptrToItems), "numJetsFromLepTop");
  kinVars.push_back(&numJetsFromLepTop);

  GenericCollectionSizeVariable<BNjetCollection> numJetsFromHadTop(&(jetsFromHadTop.ptrToItems), "numJetsFromHadTop");
  kinVars.push_back(&numJetsFromHadTop);

  GenericCollectionSizeVariable<BNleptonCollection> numLeptonsFromZ(&(leptonsFromZ.ptrToItems), "numLeptonsFromZ");
  kinVars.push_back(&numLeptonsFromZ);

//   GenericCollectionMember<int, BNleptonCollection> LeptonsFromWTkCharge(Reflex::Type::ByName("BNlepton"), &(leptonsFromW.ptrToItems),
//                                                                         "tkCharge", "leptonsFromW",  KinematicVariableConstants::INT_INIT, 3);
//   kinVars.push_back(&LeptonsFromWTkCharge);
  
//   TwoObjectKinematic<BNleptonCollection,BNjetCollection>
//     myMassLepFromWJet("mass", "all_pairs", "mass_lepFromW_jet",
//                         &(leptonsFromW.ptrToItems), "leptonsFromW", 1, 3,
//                         &(jets.ptrToItems), "jets_by_pt", 1, 6);
//   kinVars.push_back(&myMassLepFromWJet);
  
  //////////////////////////////////
  //Variables for ttbar_lj_fake matching algorithm
  //////////////////////////////////
  GenericCollectionSizeVariable<BNleptonCollection> numLeptonsFromNP(&(leptonsFromNP.ptrToItems), "numLeptonsFromNP");
  kinVars.push_back(&numLeptonsFromNP);

//   GenericCollectionMember<double, BNjetCollection> genLepTopJetCSV(Reflex::Type::ByName("BNjet"),  &(jetsFromLepTop.ptrToItems),
//                                                                    "btagCombinedSecVertex", "jetsFromLepTop",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&genLepTopJetCSV);
  
//   GenericCollectionMember<double, BNjetCollection> genWJetCSV(Reflex::Type::ByName("BNjet"),  &(jetsFromW.ptrToItems),
//                                                               "btagCombinedSecVertex", "jetsFromW_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&genWJetCSV);
  
//   GenericCollectionMember<double, BNjetCollection> genLepTopJetCharge(Reflex::Type::ByName("BNjet"),  &(jetsFromLepTop.ptrToItems),
//                                                                       "charge", "jetsFromLepTop",  KinematicVariableConstants::FLOAT_INIT, 1);
//   kinVars.push_back(&genLepTopJetCharge);
  
//   GenericCollectionMember<double, BNjetCollection> genWJetCharge(Reflex::Type::ByName("BNjet"),  &(jetsFromW.ptrToItems),
//                                                                  "charge", "jetsFromW_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&genWJetCharge);
  
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
  
//   TwoObjectKinematic<BNleptonCollection,BNjetCollection>
//     myGenLepTopMassLepB("mass", "min", "gen_lepTop_mass_lep_b",
//                         &(leptonsFromW.ptrToItems), "leptonsFromW", 1, 1,
//                         &(jetsFromLepTop.ptrToItems), "jetsFromLepTop", 1, 1);
//   kinVars.push_back(&myGenLepTopMassLepB);
  
//   ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection>
//     myGenLepTopMtMetLepB("MT", "min", "gen_lepTop_MT_met_lep_b",
//                          &(met.ptrToItems), "met", 1, 1,
//                          &(leptonsFromW.ptrToItems), "leptonsFromW", 1, 1,
//                          &(jetsFromLepTop.ptrToItems), "jetsFromLepTop", 1, 1);
//   kinVars.push_back(&myGenLepTopMtMetLepB);
  
//   TwoObjectKinematic<BNleptonCollection,BNjetCollection>
//     myGenHadTopLepDijetMass("mass", "vector_sum", "gen_hadTop_lep_dijet_mass",
//                             &(leptonsFromNP.ptrToItems), "leptonsFromNP", 1, 1,
//                             &(jetsFromW.ptrToItems), "jetsFromW_by_CSV", 1, 2);
//   kinVars.push_back(&myGenHadTopLepDijetMass);
  
//   TwoObjectKinematic<BNmetCollection,BNleptonCollection>
//     myMtMetLep("MT", "all_pairs", "MT_met_lep",
//                &(met.ptrToItems), "met", 1, 1,
//                &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 2);
//   kinVars.push_back(&myMtMetLep);
  
//   TwoObjectKinematic<BNjetCollection,BNjetCollection>
//     myDijetMasses("mass", "all_pairs", "dijet_mass",
//                   &(jets.ptrToItems), "jets_by_pt", 1, 6,
//                   &(jets.ptrToItems), "jets_by_pt", 1, 6);
//   kinVars.push_back(&myDijetMasses);

//   TwoObjectKinematic<BNleptonCollection,BNjetCollection>
//     myMassLepJet("mass", "all_pairs", "mass_lep_jet",
//                  &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 2,
//                  &(jets.ptrToItems), "jets_by_pt", 1, 6);
//   kinVars.push_back(&myMassLepJet);
    
//   ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection>
//     myMTMetLepJet("MT", "all_pairs", "MT_met_lep_jet",
//                   &(met.ptrToItems), "met", 1, 1,
//                   &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 2,
//                   &(jets.ptrToItems), "jets_by_pt", 1, 6);
//   kinVars.push_back(&myMTMetLepJet);
  
//   ThreeObjectKinematic<BNleptonCollection,BNjetCollection,BNjetCollection>
//     myMassLepDijet("mass", "all_pairs", "mass_lep_dijet",
//                    &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 2,
//                    &(jets.ptrToItems), "jets_by_pt", 1, 6,
//                    &(jets.ptrToItems), "jets_by_pt", 1, 6);
//   kinVars.push_back(&myMassLepDijet);
    
  /////////////////////////////////
  //// Leptons
  /////////////////////////////////

  // pT
  
  GenericCollectionMember<double, BNleptonCollection> LeptonPt(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
                                                                  "pt", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 3);
  kinVars.push_back(&LeptonPt);

  // eta
  
  GenericCollectionMember<double, BNleptonCollection> LeptonEta(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
                                                                "eta", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 3);
  kinVars.push_back(&LeptonEta);

  // tkCharge
  
  GenericCollectionMember<int, BNleptonCollection> allLeptonTkCharge(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
                                                                     "tkCharge", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 3);
  kinVars.push_back(&allLeptonTkCharge);

  if (myConfig.sampleName.find("QF_sideband") == std::string::npos) { //All samples except QF_sideband
    //Cut to require same-sign leptons
    auto tkChargeCut = [] (vector<BranchInfo<int>> vars) { return ((abs(vars[0].branchVal + vars[1].branchVal)) == 2); };
    allLeptonTkCharge.setCut(tkChargeCut);
  }
  else if (myConfig.sampleName.find("QF_sideband") != std::string::npos) { //QF_sideband samples
    //Cut to require opposite-sign leptons
    auto tkChargeCut = [] (vector<BranchInfo<int>> vars) { return ((vars[0].branchVal + vars[1].branchVal) == 0); };
    allLeptonTkCharge.setCut(tkChargeCut);
  }
  cutVars.push_back(&allLeptonTkCharge);

  GenericCollectionMember<double, BNleptonCollection> allLeptonSIP(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
                                                                   "SIP", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allLeptonSIP);
  
//   GenericCollectionMember<double, BNleptonCollection> allLeptonD0(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
//                                                                   "correctedD0Vertex", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&allLeptonD0);
  
//   GenericCollectionMember<double, BNleptonCollection> allLeptonDZ(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
//                                                                   "correctedDZ", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&allLeptonDZ);
  
  GenericCollectionMember<double, BNleptonCollection> allLeptonIP(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
                                                                  "IP", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allLeptonIP);
  
//   GenericCollectionMember<double, BNleptonCollection> allLeptonIPError(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
//                                                                        "IPError", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&allLeptonIPError);
  
  GenericCollectionMember<double, BNleptonCollection> allLeptonJetBTagCSV(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
                                                                          "jetBTagCSV", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allLeptonJetBTagCSV);

  GenericCollectionMember<double, BNleptonCollection> allLeptonJetPtRatio(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
                                                                          "jetPtRatio", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allLeptonJetPtRatio);
  
//   GenericCollectionMember<double, BNleptonCollection> allLeptonJetDeltaR(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
//                                                                          "jetDeltaR", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&allLeptonJetDeltaR);

  // isMuon  
  GenericCollectionMember<int, BNleptonCollection> allLeptonIsMuon(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
                                                                     "isMuon", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 3);
  kinVars.push_back(&allLeptonIsMuon);

  /////////////////////////////////////
  //// REQUIRED - Must do something with muons and electrons for leptons to be filled
  /////////////////////////////////////

  GenericCollectionMember<int, BNmuonCollection>
    allMuonIsMuon(Reflex::Type::ByName("BNmuon"), &(tightLoosePreselectedMuons.ptrToItems), "isMuon", "all_muons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allMuonIsMuon);
  
  GenericCollectionMember<int, BNelectronCollection>
    allElectronIsElectron(Reflex::Type::ByName("BNelectron"), &(tightLoosePreselectedElectrons.ptrToItems), "isElectron", "all_electrons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allElectronIsElectron);
  
  /////////////////////////////////////
  //// END REQUIRED - Must do something with muons and electrons for leptons to be filled
  /////////////////////////////////////

  // tight charge variables
  GenericCollectionMember<double, BNmuonCollection>
    allMuonNumberOfValidTrackerHitsInnerTrack(Reflex::Type::ByName("BNmuon"), &(tightLoosePreselectedMuons.ptrToItems), "numberOfValidTrackerHitsInnerTrack", "all_muons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allMuonNumberOfValidTrackerHitsInnerTrack);
  
  GenericCollectionMember<int, BNelectronCollection>
    allElectronNumberOfExpectedInnerHits(Reflex::Type::ByName("BNelectron"), &(tightLoosePreselectedElectrons.ptrToItems), "numberOfExpectedInnerHits", "all_electrons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allElectronNumberOfExpectedInnerHits);
  
  GenericCollectionMember<int, BNelectronCollection>
    allElectronPassConvVeto(Reflex::Type::ByName("BNelectron"), &(tightLoosePreselectedElectrons.ptrToItems), "passConvVeto", "all_electrons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allElectronPassConvVeto);
  
  GenericCollectionMember<int, BNelectronCollection>
    allElectronIsGsfCtfScPixChargeConsistent(Reflex::Type::ByName("BNelectron"), &(tightLoosePreselectedElectrons.ptrToItems), "isGsfCtfScPixChargeConsistent", "all_electrons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allElectronIsGsfCtfScPixChargeConsistent);
  
  // genId
  
  GenericCollectionMember<int, BNleptonCollection> ZLeptonGenMotherId(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
                                                                      "genMotherId", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&ZLeptonGenMotherId);
  
  GenericCollectionMember<int, BNleptonCollection> ZLeptonGenGrandMotherId(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
                                                                           "genGrandMother00Id", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&ZLeptonGenGrandMotherId);
  
//   ////////// all taus //////////
//   GenericCollectionMember<double, BNtauCollection> allTauPt(Reflex::Type::ByName("BNtau"), &(tightLoosePreselectedTaus.ptrToItems),
//                                                                       "pt", "all_taus_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&allTauPt);

//   GenericCollectionMember<double, BNtauCollection> allTauEta(Reflex::Type::ByName("BNtau"), &(tightLoosePreselectedTaus.ptrToItems),
//                                                                        "eta", "all_taus_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
//   kinVars.push_back(&allTauEta);

  ////////// jets by pt //////////
  GenericCollectionMember<double, BNjetCollection> allJetPt(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems),
                                                            "pt", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allJetPt);

  GenericCollectionMember<double, BNjetCollection> allJetCharge(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems),
                                                            "charge", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allJetCharge);

//   GenericCollectionMember<double, BNjetCollection> allJetJetChargeRelativePtWeighted(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems),
//                                                             "jetChargeRelativePtWeighted", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&allJetJetChargeRelativePtWeighted);


//   GenericCollectionMember<double, BNjetCollection> allJetEta(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems),
//                                                              "eta", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&allJetEta);

  GenericCollectionMember<double, BNjetCollection> allJetCSV(Reflex::Type::ByName("BNjet"),  &(jets.ptrToItems),
                                                             "btagCombinedSecVertex", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allJetCSV);

//   GenericCollectionMember<int, BNjetCollection> allJetGenPartonId(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems),
//                                                              "genPartonId", "jets_by_pt",  KinematicVariableConstants::INT_INIT, 4);
//   kinVars.push_back(&allJetGenPartonId);

//   GenericCollectionMember<int, BNjetCollection> allJetGenPartonMotherId(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems),
//                                                              "genPartonMotherId", "jets_by_pt",  KinematicVariableConstants::INT_INIT, 4);
//   kinVars.push_back(&allJetGenPartonMotherId);

//   GenericCollectionMember<int, BNjetCollection> allJetGenPartonGrandMother00Id(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems),
//                                                              "genPartonGrandMother00Id", "jets_by_pt",  KinematicVariableConstants::INT_INIT, 4);
//   kinVars.push_back(&allJetGenPartonGrandMother00Id);

  ////////// jets by CSV //////////
  GenericCollectionMember<double, BNjetCollection> allJetByCSVPt(Reflex::Type::ByName("BNjet"), &(jetsByCSV.ptrToItems),
                                                            "pt", "jets_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allJetByCSVPt);

//   GenericCollectionMember<double, BNjetCollection> allJetByCSVEta(Reflex::Type::ByName("BNjet"), &(jetsByCSV.ptrToItems),
//                                                              "eta", "jets_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&allJetByCSVEta);

  GenericCollectionMember<double, BNjetCollection> allJetByCSVCSV(Reflex::Type::ByName("BNjet"),  &(jetsByCSV.ptrToItems),
                                                             "btagCombinedSecVertex", "jets_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allJetByCSVCSV);

//   GenericCollectionMember<int, BNjetCollection> allJetByCSVGenPartonId(Reflex::Type::ByName("BNjet"), &(jetsByCSV.ptrToItems),
//                                                              "genPartonId", "jets_by_CSV",  KinematicVariableConstants::INT_INIT, 4);
//   kinVars.push_back(&allJetByCSVGenPartonId);

//   GenericCollectionMember<int, BNjetCollection> allJetByCSVGenPartonMotherId(Reflex::Type::ByName("BNjet"), &(jetsByCSV.ptrToItems),
//                                                              "genPartonMotherId", "jets_by_CSV",  KinematicVariableConstants::INT_INIT, 4);
//   kinVars.push_back(&allJetByCSVGenPartonMotherId);

//   GenericCollectionMember<int, BNjetCollection> allJetByCSVGenPartonGrandMother00Id(Reflex::Type::ByName("BNjet"), &(jetsByCSV.ptrToItems),
//                                                              "genPartonGrandMother00Id", "jets_by_CSV",  KinematicVariableConstants::INT_INIT, 4);
//   kinVars.push_back(&allJetByCSVGenPartonGrandMother00Id);


  ////////// met //////////
  GenericCollectionMember<double, BNmetCollection> metPt(Reflex::Type::ByName("BNmet"),  &(met.ptrToItems),
                                                         "pt", "met",  KinematicVariableConstants::FLOAT_INIT, 1);
  kinVars.push_back(&metPt);

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

  MatchTester_ttW_SS myMatchTester_ttW_SS(&(tightLoosePreselectedLeptons.ptrToItems), &(jetsByCSV.ptrToItems), &(met.ptrToItems));
  kinVars.push_back(&myMatchTester_ttW_SS);
  
  MatchTester_ttbar_fake_SS myMatchTester_ttbar_fake_SS(&(tightLoosePreselectedLeptons.ptrToItems), &(jetsByCSV.ptrToItems), &(met.ptrToItems));
  kinVars.push_back(&myMatchTester_ttbar_fake_SS);

  FinalBDT_ttW_SS myFinalBDT_ttW_SS(&myMatchTester_ttW_SS, &myMatchTester_ttbar_fake_SS,
                                    &myMetLD, &(jetsByCSV.ptrToItems), &myMTOfEverything);
  kinVars.push_back(&myFinalBDT_ttW_SS);
  
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
    //Normal non-PF jets for lepMVA
    jetsForLepMVA.initializeRawItemsSortedByCSV(ev, "BNproducer", "patJetsAK5PF");
//     //PF jets; testing. (Turns out these jets had the leptons cleaned out, so they're useless - AWB 06/26/14)
//     jetsForLepMVA.initializeRawItemsSortedByCSV(ev, "BNproducer","selectedPatJetsPFlow");
//     //jetsForLepMVA.correctRawJets();
    
    tightLoosePreselectedMuons.initializeRawItemsSortedByPt(ev, "BNproducer","selectedPatMuonsLoosePFlow");
    tightLoosePreselectedElectrons.initializeRawItemsSortedByPt(ev, "BNproducer","selectedPatElectronsGSF");
//     tightLoosePreselectedTaus.initializeRawItemsSortedByPt(ev, "BNproducer","selectedPatTausPFlow");


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

//     tightLoosePreselectedTaus.keepSelectedParticles(tauPreselectedID);
//     tightTaus.initializeRawItems(tightLoosePreselectedTaus.rawItems);
//     tightTaus.keepSelectedParticles(tauTightID);
//     tightLooseTaus.initializeRawItems(tightLoosePreselectedTaus.rawItems);
//     tightLooseTaus.keepSelectedParticles(tauLooseID);
    
    jets.initializeRawItemsSortedByPt(ev, "BNproducer","selectedPatJetsPFlow");
    jets.correctRawJets();
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
