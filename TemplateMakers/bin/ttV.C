#include "ttHMultileptonAnalysis/TemplateMakers/interface/BEANFileInterface.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/HelperLeptonCore.h"

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

void getNumExtraPartons(BEANhelper * beanHelper, BEANFileInterface selectedCollections, int & numExtraPartons) {

  numExtraPartons = beanHelper->GetNumExtraPartons(*(selectedCollections.mcParticleCollection));

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
  tauID::tauID tauLooseID = tauID::tauVLoose;
  tauID::tauID tauPreselectedID = tauID::tauNonIso;

  // declare your kinematic variables that you want
  // to be written out into the tree
  vector<ArbitraryVariable*> kinVars;
  vector<ArbitraryVariable*> cutVars;

  BEANFileInterface selectedCollections;

  GenericVariable<string> dataset(lepHelper.dataset, "dataset", "not set");
  kinVars.push_back(&dataset);

  GenericCollectionSizeVariable<BNjetCollection> numJets(&(selectedCollections.jetCollection), "numJets");
  kinVars.push_back(&numJets);
  numJets.setCutMin(2);
  //cutVars.push_back(&numJets);

  GenericCollectionSizeVariable<BNjetCollection> numLooseBJets(&(selectedCollections.jetCollectionLooseCSV), "numLooseBJets");
  kinVars.push_back(&numLooseBJets);

  GenericCollectionSizeVariable<BNjetCollection> numMediumBJets(&(selectedCollections.jetCollectionMediumCSV), "numMediumBJets");
  kinVars.push_back(&numMediumBJets);

  GenericCollectionSizeVariable<BNjetCollection> numTightBJets(&(selectedCollections.jetCollectionTightCSV), "numTightBJets");
  kinVars.push_back(&numTightBJets);

  GenericCollectionSizeVariable<BNleptonCollection> numTightLeptons(&(selectedCollections.tightLeptonCollection), "numTightLeptons");
  kinVars.push_back(&numTightLeptons);
  
  GenericCollectionSizeVariable<BNleptonCollection> numTightLooseLeptons(&(selectedCollections.tightLooseLeptonCollection), "numTightLooseLeptons");
  kinVars.push_back(&numTightLooseLeptons);

  GenericCollectionSizeVariable<BNleptonCollection> numAllLeptons(&(selectedCollections.tightLoosePreselectedLeptonCollection), "numAllLeptons");
  kinVars.push_back(&numAllLeptons);
  numAllLeptons.setCutMin(3);
  cutVars.push_back(&numAllLeptons);

  GenericCollectionSizeVariable<BNmuonCollection> numAllMuons(&(selectedCollections.tightLoosePreselectedMuonCollection), "numAllMuons");
  kinVars.push_back(&numAllMuons);

  GenericCollectionSizeVariable<BNelectronCollection> numAllElectrons(&(selectedCollections.tightLoosePreselectedElectronCollection), "numAllElectrons");
  kinVars.push_back(&numAllElectrons);

  GenericCollectionSizeVariable<BNleptonCollection> numTightZLeptons(&(selectedCollections.tightZLeptonCollection), "numTightZLeptons");
  kinVars.push_back(&numTightZLeptons);

  GenericCollectionSizeVariable<BNleptonCollection> numTightLooseZLeptons(&(selectedCollections.tightLooseZLeptonCollection), "numTightLooseZLeptons");
  kinVars.push_back(&numTightLooseZLeptons);

  GenericCollectionSizeVariable<BNleptonCollection> numAllZLeptons(&(selectedCollections.tightLoosePreselectedZLeptonCollection), "numAllZLeptons");
  kinVars.push_back(&numAllZLeptons);

  GenericCollectionSizeVariable<BNtauCollection> numAllTaus(&(selectedCollections.tightLoosePreselectedTauCollection), "numAllTaus");
  kinVars.push_back(&numAllTaus);

  GenericCollectionSizeVariable<BNtauCollection> numTightLooseTaus(&(selectedCollections.tightLooseTauCollection), "numTightLooseTaus");
  kinVars.push_back(&numTightLooseTaus);

  GenericCollectionSizeVariable<BNtauCollection> numTightTaus(&(selectedCollections.tightTauCollection), "numTightTaus");
  kinVars.push_back(&numTightTaus);

  //ttH hadrons reweighting
  CSVWeights myCSV(&lepHelper);
  kinVars.push_back(&myCSV);

  //Btag POG reweighting
  vector<pair<string, double>> WPs = {make_pair("CSVT", 0.898), make_pair("CSVM", 0.679), make_pair("CSVL", 0.244)};
  BTagWeights myBTagWeights(WPs);
  kinVars.push_back(&myBTagWeights);

  PUWeights myPU(&lepHelper);
  kinVars.push_back(&myPU);

  TopPtWeights myTopPt(&lepHelper);
  kinVars.push_back(&myTopPt);

//   // //Currently, gets ND loose lepton SF; could switch to tight and loose - AWB Feb 12, 2014
//   //LeptonIDAndIsoScaleFactors myLepIDAndIsoSF(&lepHelper, muonID::muonTight, muonID::muonLoose, electronID::electronTight, electronID::electronLoose);
//   LeptonIDAndIsoScaleFactors myLepIDAndIsoSF(&lepHelper, muonTightID, muonLooseID, electronTightID, electronLooseID);
//   kinVars.push_back(&myLepIDAndIsoSF);

  //CERN version
  RecoIDIsoSIPSFs myRecoIDIsoSIPSFs(3);
  kinVars.push_back(&myRecoIDIsoSIPSFs);

  LeptonTriggerScaleFactors myLepTrig(&lepHelper);
  kinVars.push_back(&myLepTrig);

  //Give particular collections
  TightChargeAndLepMVAScaleFactors myTightChargeAndLepMVASFs(3);
  kinVars.push_back(&myTightChargeAndLepMVASFs);

  TightChargeAndLepMVAScaleFactorsPerLepton myTightChargeAndLepMVASFPerLepton(3);
  kinVars.push_back(&myTightChargeAndLepMVASFPerLepton);

  CleanEventVars myClean (&lepHelper);
  kinVars.push_back(&myClean);

  CheckTwoLepTrigger checkTrig (&lepHelper);
  kinVars.push_back(&checkTrig);

  LepMVAs<BNleptonCollection> myLepMVAsAllLeptons(&lepHelper, &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 4);
  kinVars.push_back(&myLepMVAsAllLeptons);

  LepMVAs<BNleptonCollection> myLepMVAsAllZLeptons(&lepHelper, &(selectedCollections.tightLoosePreselectedZLeptonCollection), "all_Z_leptons_by_pt", 2);
  kinVars.push_back(&myLepMVAsAllZLeptons);

  LepMVAs<BNleptonCollection> myLepMVAsAllNonZLeptons(&lepHelper, &(selectedCollections.tightLoosePreselectedNonZLeptonCollection), "all_nonZ_leptons_by_pt", 2);
  kinVars.push_back(&myLepMVAsAllNonZLeptons);

  DataDrivenFR<BNleptonCollection> myDataDrivenFR3Tight(&lepHelper, &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                        3, 0.7, "FR_merged_data", "QF_data_el", "_3_tight"); 
  kinVars.push_back(&myDataDrivenFR3Tight);
  
  DataDrivenFR<BNleptonCollection> myDataDrivenFR2LooseZ1TightNonZ(&lepHelper, &(selectedCollections.tightLoosePreselectedZLeptonCollection),
                                                                   2, -0.3, "FR_merged_data", "QF_data_el", "_2_loose_Z_1_tight_nonZ",
                                                                   &(selectedCollections.tightLoosePreselectedNonZLeptonCollection), 1, 0.7); 
  kinVars.push_back(&myDataDrivenFR2LooseZ1TightNonZ);
  
  DataDrivenFRPerLepton<BNleptonCollection> myDataDrivenFRPerLepton2LooseZ1TightNonZ(&lepHelper, &(selectedCollections.tightLoosePreselectedZLeptonCollection),
                                                                   2, -0.3, "FR_merged_data", "QF_data_el", "_2_loose_Z"); 
  kinVars.push_back(&myDataDrivenFRPerLepton2LooseZ1TightNonZ);
  
  DataDrivenFR<BNleptonCollection> myDataDrivenFR3Loose(&lepHelper, &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                        3, -0.3, "FR_merged_data", "QF_data_el", "_3_loose");
  kinVars.push_back(&myDataDrivenFR3Loose);
  
  DataDrivenFR<BNleptonCollection> myDataDrivenFR4Loose(&lepHelper, &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                        4, -0.3, "FR_merged_data", "QF_data_el", "_4_loose");
  kinVars.push_back(&myDataDrivenFR4Loose);
  
  DBCorrectedRelIsoDR04s myDBCorrectedRelIsoDR04s(&lepHelper, 4);
  kinVars.push_back(&myDBCorrectedRelIsoDR04s);

  HiggsDecayType myHiggsDecayType(&lepHelper);
  kinVars.push_back(&myHiggsDecayType);

  // Full event kinematics

  TwoObjectKinematic<BNleptonCollection,BNjetCollection>
    mySumPt("pt", "sum", "sum_pt",
            &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99,
            &(selectedCollections.jetCollection), "jets_by_pt", 1, 99);
  kinVars.push_back(&mySumPt);
  
  TwoObjectKinematic<BNjetCollection,BNjetCollection>
    mySumJetPt("pt", "sum", "sum_jet_pt",
               &(selectedCollections.jetCollection), "jets_by_pt", 1, 99,
               &(selectedCollections.jetCollection), "jets_by_pt", 1, 99);
  kinVars.push_back(&mySumJetPt);
  
  TwoObjectKinematic<BNjetCollection,BNjetCollection>
    myMassOfAllJets("mass", "vector_sum", "mass_of_all_jets",
                    &(selectedCollections.jetCollection), "jets_by_pt", 1, 99,
                    &(selectedCollections.jetCollection), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMassOfAllJets);
  
  //SS ttbarW and 3l ttbarZ
  TwoObjectKinematic<BNjetCollection,BNjetCollection>
    myWLikeDijetMass81X1B("mass", "closest_to", "WLike_dijet_mass_X1b",
                          &(selectedCollections.jetsByCSVCollection), "jets_by_CSV", 2, 99,
                          &(selectedCollections.jetsByCSVCollection), "jets_by_CSV", 2, 99,
                          81);
  kinVars.push_back(&myWLikeDijetMass81X1B);

  TwoObjectKinematic<BNjetCollection,BNjetCollection>
    myWLikeDijetMass81X2B("mass", "closest_to", "WLike_dijet_mass_X2b",
                          &(selectedCollections.jetsByCSVCollection), "jets_by_CSV", 3, 99,
                          &(selectedCollections.jetsByCSVCollection), "jets_by_CSV", 3, 99,
                          81);
  kinVars.push_back(&myWLikeDijetMass81X2B);

  //3l ttbarZ
  TwoObjectKinematic<BNmetCollection,BNleptonCollection>
    myMtMetNonZLep("MT", "all_pairs", "WLike_MT_met_lep",
                   &(selectedCollections.metCollection), "met", 1, 1,
                   &(selectedCollections.tightLoosePreselectedNonZLeptonCollection), "all_nonZ_leptons_by_pt", 1, 1);
  kinVars.push_back(&myMtMetNonZLep);
  
  ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection>
    myMtMetNonZLepB("MT", "all_pairs", "topLike_MT_met_lep_b",
                    &(selectedCollections.metCollection), "met", 1, 1,
                    &(selectedCollections.tightLoosePreselectedNonZLeptonCollection), "all_nonZ_leptons_by_pt", 1, 1,
                    &(selectedCollections.jetsByCSVCollection), "jets_by_CSV", 1, 2);
  kinVars.push_back(&myMtMetNonZLepB);
  
  ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection>
    myMtMetNonZLepB175("MT", "closest_to", "topLike_MT_met_lep_b_175",
                       &(selectedCollections.metCollection), "met", 1, 1,
                       &(selectedCollections.tightLoosePreselectedNonZLeptonCollection), "all_nonZ_leptons_by_pt", 1, 1,
                       &(selectedCollections.jetsByCSVCollection), "jets_by_CSV", 1, 2,
                       175);
  kinVars.push_back(&myMtMetNonZLepB175);
  
  TwoObjectKinematic<BNleptonCollection,BNjetCollection>
    myMassNonZLepB("mass", "all_pairs", "topLike_mass_lep_b",
                   &(selectedCollections.tightLoosePreselectedNonZLeptonCollection), "all_nonZ_leptons_by_pt", 1, 1,
                   &(selectedCollections.jetsByCSVCollection), "jets_by_CSV", 1, 2);
  kinVars.push_back(&myMassNonZLepB);

  TwoObjectKinematic<BNleptonCollection,BNjetCollection>
    myMassNonZLepB100("mass", "closest_to", "topLike_mass_lep_b_100",
                   &(selectedCollections.tightLoosePreselectedNonZLeptonCollection), "all_nonZ_leptons_by_pt", 1, 1,
                      &(selectedCollections.jetsByCSVCollection), "jets_by_CSV", 1, 2,
                      100);
  kinVars.push_back(&myMassNonZLepB100);

  TwoObjectKinematic<BNjetCollection,BNjetCollection>
    myTopLikeMultijetMassB1("mass", "vector_sum", "topLike_multijet_mass_b1",
                               &(selectedCollections.jetsByCSVCollection), "jets_by_CSV", 1, 1,
                               &(selectedCollections.jetsByCSVCollection), "jets_by_CSV", 3, 99);
  kinVars.push_back(&myTopLikeMultijetMassB1);

  TwoObjectKinematic<BNjetCollection,BNjetCollection>
    myTopLikeMultijetMassB2("mass", "vector_sum", "topLike_multijet_mass_b2",
                               &(selectedCollections.jetsByCSVCollection), "jets_by_CSV", 2, 2,
                               &(selectedCollections.jetsByCSVCollection), "jets_by_CSV", 3, 99);
  kinVars.push_back(&myTopLikeMultijetMassB2);

  ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection>
    myMtMetNonZLepJets("MT", "vector_sum", "topPairLike_MT_met_lep_jets",
                       &(selectedCollections.metCollection), "met", 1, 1,
                       &(selectedCollections.tightLoosePreselectedNonZLeptonCollection), "all_nonZ_leptons_by_pt", 1, 1,
                       &(selectedCollections.jetCollection), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMtMetNonZLepJets);
  
  TwoObjectKinematic<BNleptonCollection,BNjetCollection>
    myMassNonZLepJets("mass", "vector_sum", "topPairLike_mass_lep_jets",
                      &(selectedCollections.tightLoosePreselectedNonZLeptonCollection), "all_nonZ_leptons_by_pt", 1, 1,
                      &(selectedCollections.jetCollection), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMassNonZLepJets);


  // Two lepton kinematics
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMinMassLepLepSFOS("mass", "min", "min_mass_leplep_SFOS",
                                                                                &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99,
                                                                                &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99,
                                                                                -99, "same_flavour", "opposite_sign");
  kinVars.push_back(&myMinMassLepLepSFOS);
  
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMinMassLepLep("mass", "min", "min_mass_leplep",
                                                                            &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99,
                                                                            &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99);
  kinVars.push_back(&myMinMassLepLep);
  
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZLikeMassLepLepSFOSTight("mass", "closest_to", "ZLike_mass_leplep_SFOS_tight",
                                                                                     &(selectedCollections.tightLeptonCollection), "tight_leptons_by_pt", 1, 99,
                                                                                     &(selectedCollections.tightLeptonCollection), "tight_leptons_by_pt", 1, 99,
                                                                                     91.2, "same_flavour", "opposite_sign");
  kinVars.push_back(&myZLikeMassLepLepSFOSTight);  

  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZLikeMassLepLepSFOSTightLoose("mass", "closest_to", "ZLike_mass_leplep_SFOS_loose",
                                                                                     &(selectedCollections.tightLooseLeptonCollection), "tightLoose_leptons_by_pt", 1, 99,
                                                                                     &(selectedCollections.tightLooseLeptonCollection), "tightLoose_leptons_by_pt", 1, 99,
                                                                                     91.2, "same_flavour", "opposite_sign");
  kinVars.push_back(&myZLikeMassLepLepSFOSTightLoose);  

  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZLikeMassLepLepSFOSAll("mass", "closest_to", "ZLike_mass_leplep_SFOS_all",
                                                                                     &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99,
                                                                                     &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99,
                                                                                     91.2, "same_flavour", "opposite_sign");
  kinVars.push_back(&myZLikeMassLepLepSFOSAll);  

  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZLikePtLepLepSFOSAll("vectPt", "max", "ZLike_pt_leplep_SFOS_all",
                                                                                &(selectedCollections.tightLoosePreselectedZLeptonCollection), "all_Z_leptons_by_pt", 1, 99,
                                                                                &(selectedCollections.tightLoosePreselectedZLeptonCollection), "all_Z_leptons_by_pt", 1, 99);
  kinVars.push_back(&myZLikePtLepLepSFOSAll);

  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZLikeEtaLepLepSFOSAll("vectEta", "max", "ZLike_eta_leplep_SFOS_all",
                                                                                &(selectedCollections.tightLoosePreselectedZLeptonCollection), "all_Z_leptons_by_pt", 1, 99,
                                                                                &(selectedCollections.tightLoosePreselectedZLeptonCollection), "all_Z_leptons_by_pt", 1, 99);
  kinVars.push_back(&myZLikeEtaLepLepSFOSAll);

//   //Variables for CERN same-sign dilepton BDT
  TwoObjectKinematic<BNleptonCollection,BNjetCollection> myMHT("pt", "vector_sum", "mht",
                                                               &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 99,
                                                               &(selectedCollections.jetCollection), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMHT);
  
//   TwoObjectKinematic<BNleptonCollection,BNjetCollection> myMinDeltaRLep2Jet("deltaR", "min", "min_deltaR_lep2_jet",
//                                                                             &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 2, 2,
//                                                                             &(selectedCollections.jetCollection), "jets_by_pt", 1, 99);
//   kinVars.push_back(&myMinDeltaRLep2Jet);

//   TwoObjectKinematic<BNmetCollection,BNleptonCollection> myMtMetLep("MT", "all_pairs", "",
//                                                                     &(selectedCollections.metCollection), "met", 1, 1,
//                                                                     &(selectedCollections.tightLoosePreselectedLeptonCollection), "all_leptons_by_pt", 1, 2);
//   kinVars.push_back(&myMtMetLep);

//   TightCharges myTightCharges(&(selectedCollections.tightLoosePreselectedLeptonCollection), "CERN_tight_charge", "all_leptons_by_pt", 2);
//   kinVars.push_back(&myTightCharges);
//   //myTightCharges.setCut("pass");

// //   int TwoMuon = 0;
// //   int TwoElectron = 0;
// //   int MuonElectron = 0;

// //   summaryTree->Branch("TwoMuon", &TwoMuon);
// //   summaryTree->Branch("TwoElectron", &TwoElectron);
// //   summaryTree->Branch("MuonElectron", &MuonElectron);

  /////////////////////////////////
  //// Leptons
  /////////////////////////////////

  // pT
  
  GenericCollectionMember<double, BNleptonCollection> LeptonPt(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                                  "pt", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&LeptonPt);

  GenericCollectionMember<double, BNleptonCollection> ZLeptonPt(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedZLeptonCollection),
                                                                  "pt", "all_Z_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&ZLeptonPt);

  GenericCollectionMember<double, BNleptonCollection> NonZLeptonPt(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedNonZLeptonCollection),
                                                                  "pt", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&NonZLeptonPt);

  // eta
  
  GenericCollectionMember<double, BNleptonCollection> LeptonEta(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                                  "eta", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&LeptonEta);

  GenericCollectionMember<double, BNleptonCollection> ZLeptonEta(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedZLeptonCollection),
                                                                  "eta", "all_Z_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&ZLeptonEta);

  GenericCollectionMember<double, BNleptonCollection> NonZLeptonEta(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedNonZLeptonCollection),
                                                                  "eta", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&NonZLeptonEta);

  // isMuon / isElectron
  
  GenericCollectionMember<int, BNleptonCollection> NonZLeptonIsMuon(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedNonZLeptonCollection),
                                                                       "isMuon", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&NonZLeptonIsMuon);

  GenericCollectionMember<int, BNleptonCollection> NonZLeptonIsElectron(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedNonZLeptonCollection),
                                                                       "isElectron", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&NonZLeptonIsElectron);

  // tkCharge
  
  GenericCollectionMember<int, BNleptonCollection> LeptonTkCharge(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                                  "tkCharge", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&LeptonTkCharge);

  GenericCollectionMember<int, BNleptonCollection> NonZLeptonTkCharge(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedNonZLeptonCollection),
                                                                  "tkCharge", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&NonZLeptonTkCharge);

//   if (myConfig.sampleName.find("QF_sideband") == std::string::npos) { //All samples except QF_sideband
//     //Cut to require same-sign leptons
//     auto tkChargeCut = [] (vector<BranchInfo<int>> vars) { return ((vars[0].branchVal * vars[1].branchVal) > 0); };
//     allLeptonTkCharge.setCut(tkChargeCut);
//   }
//   else if (myConfig.sampleName.find("QF_sideband") != std::string::npos) { //QF_sideband samples
//     //Cut to require opposite-sign leptons
//     auto tkChargeCut = [] (vector<BranchInfo<int>> vars) { return ((vars[0].branchVal * vars[1].branchVal) < 0); };
//     allLeptonTkCharge.setCut(tkChargeCut);
//   }
//   cutVars.push_back(&allLeptonTkCharge);

  GenericCollectionMember<double, BNleptonCollection> allLeptonSIP(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                                   "SIP", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonSIP);

  GenericCollectionMember<double, BNleptonCollection> allLeptonD0(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                                  "correctedD0Vertex", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonD0);

  GenericCollectionMember<double, BNleptonCollection> allLeptonDZ(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                                  "correctedDZ", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonDZ);

  GenericCollectionMember<double, BNleptonCollection> allLeptonIP(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                                               "IP", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonIP);

  GenericCollectionMember<double, BNleptonCollection> allLeptonIPError(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedLeptonCollection),
                                                                                    "IPError", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonIPError);

  /////////////////////////////////////
  //// REQUIRED - Properties of muons and electrons for lepton selection
  /////////////////////////////////////

  GenericCollectionMember<int, BNmuonCollection> allMuonPFmuon(Reflex::Type::ByName("BNmuon"), &(selectedCollections.tightLoosePreselectedMuonCollection),
                                                               "isPFMuon", "all_muons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allMuonPFmuon);

  GenericCollectionMember<int, BNmuonCollection> allMuonGlobalMuon(Reflex::Type::ByName("BNmuon"), &(selectedCollections.tightLoosePreselectedMuonCollection),
                                                                   "isGlobalMuon", "all_muons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allMuonGlobalMuon);

  GenericCollectionMember<int, BNmuonCollection> allMuonTrackerMuon(Reflex::Type::ByName("BNmuon"), &(selectedCollections.tightLoosePreselectedMuonCollection),
                                                                    "isTrackerMuon", "all_muons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allMuonTrackerMuon);

  GenericCollectionMember<int, BNelectronCollection> allElectronNumExpInnerHits(Reflex::Type::ByName("BNelectron"), &(selectedCollections.tightLoosePreselectedElectronCollection),
                                                                                "numberOfExpectedInnerHits", "all_electrons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allElectronNumExpInnerHits);

  GenericCollectionMember<int, BNelectronCollection> allElectronPassConvVeto(Reflex::Type::ByName("BNelectron"), &(selectedCollections.tightLoosePreselectedElectronCollection),
                                                                             "passConvVeto", "all_electrons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allElectronPassConvVeto);

  GenericCollectionMember<double, BNelectronCollection> allElectronEta(Reflex::Type::ByName("BNelectron"), &(selectedCollections.tightLoosePreselectedElectronCollection),
                                                                       "eta", "all_electrons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allElectronEta);

  GenericCollectionMember<double, BNelectronCollection> allElectronPt(Reflex::Type::ByName("BNelectron"), &(selectedCollections.tightLoosePreselectedElectronCollection),
                                                                      "pt", "all_electrons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allElectronPt);

  // genId
  
  GenericCollectionMember<int, BNleptonCollection> ZLeptonGenMotherId(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedZLeptonCollection),
                                                                  "genMotherId", "all_Z_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&ZLeptonGenMotherId);

  GenericCollectionMember<int, BNleptonCollection> NonZLeptonGenMotherId(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedNonZLeptonCollection),
                                                                  "genMotherId", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&NonZLeptonGenMotherId);

  GenericCollectionMember<int, BNleptonCollection> ZLeptonGenGrandMotherId(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedZLeptonCollection),
                                                                  "genGrandMother00Id", "all_Z_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&ZLeptonGenGrandMotherId);

  GenericCollectionMember<int, BNleptonCollection> NonZLeptonGenGrandMotherId(Reflex::Type::ByName("BNlepton"), &(selectedCollections.tightLoosePreselectedNonZLeptonCollection),
                                                                  "genGrandMother00Id", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&NonZLeptonGenGrandMotherId);

  ////////// all taus //////////
  GenericCollectionMember<double, BNtauCollection> allTauPt(Reflex::Type::ByName("BNtau"), &(selectedCollections.tightLoosePreselectedTauCollection),
                                                                      "pt", "all_taus_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allTauPt);

  GenericCollectionMember<double, BNtauCollection> allTauEta(Reflex::Type::ByName("BNtau"), &(selectedCollections.tightLoosePreselectedTauCollection),
                                                                       "eta", "all_taus_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allTauEta);

  ////////// jets by pt //////////
  GenericCollectionMember<double, BNjetCollection> allJetPt(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetCollection),
                                                            "pt", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetPt);

//   GenericCollectionMember<double, BNjetCollection> allJetEta(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetCollection),
//                                                              "eta", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
//   kinVars.push_back(&allJetEta);

  GenericCollectionMember<double, BNjetCollection> allJetCSV(Reflex::Type::ByName("BNjet"),  &(selectedCollections.jetCollection),
                                                             "btagCombinedSecVertex", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetCSV);

  GenericCollectionMember<int, BNjetCollection> allJetGenPartonId(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetCollection),
                                                             "genPartonId", "jets_by_pt",  KinematicVariableConstants::INT_INIT, 6);
  kinVars.push_back(&allJetGenPartonId);

  GenericCollectionMember<int, BNjetCollection> allJetGenPartonMotherId(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetCollection),
                                                             "genPartonMotherId", "jets_by_pt",  KinematicVariableConstants::INT_INIT, 6);
  kinVars.push_back(&allJetGenPartonMotherId);

  GenericCollectionMember<int, BNjetCollection> allJetGenPartonGrandMother00Id(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetCollection),
                                                             "genPartonGrandMother00Id", "jets_by_pt",  KinematicVariableConstants::INT_INIT, 6);
  kinVars.push_back(&allJetGenPartonGrandMother00Id);

//   GenericCollectionMember<double, BNjetCollection> mediumBJetPt(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetCollectionMediumCSV),
//                                                             "pt", "medium_tags_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&mediumBJetPt);

//   GenericCollectionMember<double, BNjetCollection> mediumBJetEta(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetCollectionMediumCSV),
//                                                              "eta", "medium_tags_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&mediumBJetEta);

//   GenericCollectionMember<double, BNjetCollection> notMediumBJetPt(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetCollectionNotMediumCSV),
//                                                             "pt", "medium_untags_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&notMediumBJetPt);

//   GenericCollectionMember<double, BNjetCollection> notMediumBJetEta(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetCollectionNotMediumCSV),
//                                                              "eta", "medium_untags_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&notMediumBJetEta);

  ////////// jets by CSV //////////
  GenericCollectionMember<double, BNjetCollection> allJetByCSVPt(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetsByCSVCollection),
                                                            "pt", "jets_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetByCSVPt);

  GenericCollectionMember<double, BNjetCollection> allJetByCSVMass(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetsByCSVCollection),
                                                            "mass", "jets_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetByCSVMass);

//   GenericCollectionMember<double, BNjetCollection> allJetByCSVEta(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetsByCSVCollection),
//                                                              "eta", "jets_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 6);
//   kinVars.push_back(&allJetByCSVEta);

  GenericCollectionMember<double, BNjetCollection> allJetByCSVCSV(Reflex::Type::ByName("BNjet"),  &(selectedCollections.jetsByCSVCollection),
                                                             "btagCombinedSecVertex", "jets_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetByCSVCSV);

  GenericCollectionMember<int, BNjetCollection> allJetByCSVGenPartonId(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetsByCSVCollection),
                                                             "genPartonId", "jets_by_CSV",  KinematicVariableConstants::INT_INIT, 6);
  kinVars.push_back(&allJetByCSVGenPartonId);

  GenericCollectionMember<int, BNjetCollection> allJetByCSVGenPartonMotherId(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetsByCSVCollection),
                                                             "genPartonMotherId", "jets_by_CSV",  KinematicVariableConstants::INT_INIT, 6);
  kinVars.push_back(&allJetByCSVGenPartonMotherId);

  GenericCollectionMember<int, BNjetCollection> allJetByCSVGenPartonGrandMother00Id(Reflex::Type::ByName("BNjet"), &(selectedCollections.jetsByCSVCollection),
                                                             "genPartonGrandMother00Id", "jets_by_CSV",  KinematicVariableConstants::INT_INIT, 6);
  kinVars.push_back(&allJetByCSVGenPartonGrandMother00Id);

  ////////// met //////////
  GenericCollectionMember<double, BNmetCollection> metPt(Reflex::Type::ByName("BNmet"),  &(selectedCollections.metCollection),
                                                         "pt", "met",  KinematicVariableConstants::FLOAT_INIT, 1);
  kinVars.push_back(&metPt);

//   ////////// mc particles ////////
// //   GenericCollectionMember<double, BNmcparticleCollection> allMcParticlePt(Reflex::Type::ByName("BNmcparticle"), &(selectedCollections.mcParticleCollection),
// //                                                                   "pt", "mcParticles_by_pt",  KinematicVariableConstants::FLOAT_INIT, 20);
// //   kinVars.push_back(&allMcParticlePt);

//   GenericCollectionMember<int, BNmcparticleCollection> allMcParticleId(Reflex::Type::ByName("BNmcparticle"), &(selectedCollections.mcParticleCollection),
//                                                                   "id", "mcParticles_by_pt",  KinematicVariableConstants::INT_INIT, 10);
//   kinVars.push_back(&allMcParticleId);

  int numExtraPartons = -99;
  summaryTree->Branch("numExtraPartons", &numExtraPartons);

  ////////// event info //////////
  GenericCollectionMember<unsigned, BNeventCollection> runNumber(Reflex::Type::ByName("BNevent"), &(selectedCollections.eventCollection),
                                                                 "run", "eventInfo",  KinematicVariableConstants::UINT_INIT, 1);
  kinVars.push_back(&runNumber);

  GenericCollectionMember<unsigned, BNeventCollection> lumiBlock(Reflex::Type::ByName("BNevent"), &(selectedCollections.eventCollection),
                                                                 "lumi", "eventInfo",  KinematicVariableConstants::UINT_INIT, 1);
  kinVars.push_back(&lumiBlock);

  // this is a long inside BNevent
  // just using keyword long won't work
  // needs to be Long64_t 
  GenericCollectionMember<Long64_t, BNeventCollection> eventNumber(Reflex::Type::ByName("BNevent"),  &(selectedCollections.eventCollection),
                                                                   "evt", "eventInfo",  KinematicVariableConstants::INT_INIT, 1);
  kinVars.push_back(&eventNumber);

  MetLD myMetLD(&myMHT, &metPt);
  kinVars.push_back(&myMetLD);

//   FinalBDT myFinalBDT(&allLeptonEta, &allLeptonPt, &myMHT, &myMinDeltaRLep2Jet, &myMtMetLep, &mySumPt);
//   kinVars.push_back(&myFinalBDT);

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

    lepHelper.initializeInputCollections(ev, true, selectedCollections);
    lepHelper.applyRochesterCorrections(*(lepHelper.rawCollections.rawMuonCollection));

    if (!lepHelper.isData) {
      lepHelper.fillMCMatchAny(*(lepHelper.rawCollections.rawMuonCollection), 0.3);
      lepHelper.fillMCMatchAny(*(lepHelper.rawCollections.rawElectronCollection), 0.3);
      lepHelper.fillMCMatchID(*(lepHelper.rawCollections.rawMuonCollection), 1.2);
      lepHelper.fillMCMatchID(*(lepHelper.rawCollections.rawElectronCollection), 1.2);

      lepHelper.scaleMCCollectionDZ(*(lepHelper.rawCollections.rawElectronCollection));
      lepHelper.scaleMCCollectionDZ(*(lepHelper.rawCollections.rawMuonCollection));
      lepHelper.scaleMCCollectionDXY(*(lepHelper.rawCollections.rawElectronCollection));
      lepHelper.scaleMCCollectionDXY(*(lepHelper.rawCollections.rawMuonCollection));
    }
    bool applySmearing = !(lepHelper.isData);
    lepHelper.fillSIP(*(lepHelper.rawCollections.rawMuonCollection), applySmearing);
    lepHelper.fillSIP(*(lepHelper.rawCollections.rawElectronCollection), applySmearing);
    lepHelper.fillLepJetPtRatio(*(lepHelper.rawCollections.rawMuonCollection), *(lepHelper.rawCollections.jetsForLepMVACollection), applySmearing);
    lepHelper.fillLepJetPtRatio(*(lepHelper.rawCollections.rawElectronCollection), *(lepHelper.rawCollections.jetsForLepMVACollection), applySmearing);
    lepHelper.fillLepJetDeltaR(*(lepHelper.rawCollections.rawMuonCollection), *(lepHelper.rawCollections.jetsForLepMVACollection), applySmearing);
    lepHelper.fillLepJetDeltaR(*(lepHelper.rawCollections.rawElectronCollection), *(lepHelper.rawCollections.jetsForLepMVACollection), applySmearing);
    lepHelper.fillLepJetBTagCSV(*(lepHelper.rawCollections.rawMuonCollection), *(lepHelper.rawCollections.jetsForLepMVACollection));
    lepHelper.fillLepJetBTagCSV(*(lepHelper.rawCollections.rawElectronCollection), *(lepHelper.rawCollections.jetsForLepMVACollection));

    /////////////////////////////////////////////////////////////
    //
    //    Apply object ids
    //
    //////////////////////////////////////////////////////////////

    //------------  Electrons
    if (debug > 9) cout << "Getting electrons "  << endl;
    lepHelper.getTightLoosePreselectedElectrons(electronTightID, electronLooseID, electronPreselectedID, &selectedCollections);

    //-----------    Muons
    if (debug > 9) cout << "Getting muons "  << endl;
    lepHelper.getTightLoosePreselectedMuons(muonTightID, muonLooseID, muonPreselectedID, &selectedCollections);

    //----------    MET
    if (debug > 9) cout << "Getting met "  << endl;
    lepHelper.getCorrectedMet(&selectedCollections);

    //--------- fill up the lepton collections
    if (debug >9) cout << "Filling lepton collections" << endl;
    lepHelper.fillLepCollectionWithSelectedLeptons(&selectedCollections);
    lepHelper.fillZLepCollectionWithSelectedLeptons(&selectedCollections, &myZLikeMassLepLepSFOSTight,
                                                    &myZLikeMassLepLepSFOSTightLoose, &myZLikeMassLepLepSFOSAll);

    //------------    Jets
    *(lepHelper.rawCollections.jetCollection) = beanHelper->GetCleanJets(*(lepHelper.rawCollections.jetCollection), *(selectedCollections.tightLoosePreselectedLeptonCollection), 0.5);

    if (debug > 9) cout << "Getting jets "  << endl;
	lepHelper.getTightCorrectedJets(25.0, 2.4, jetID::jetLoose, &selectedCollections);

    //------------    Taus
    if (debug > 9) cout << "Getting taus "  << endl;
    lepHelper.getTightLoosePreselectedTaus(tauTightID, tauLooseID, tauPreselectedID, &selectedCollections);

    // reset all the vars
    if (debug > 9) cout << "Resetting "  << endl;
    for (vector<ArbitraryVariable*>::iterator iVar = kinVars.begin();
         iVar != kinVars.end();
         iVar++) {

      (*iVar)->reset();
      (*iVar)->assignCollections(&selectedCollections);
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

    getNumExtraPartons(beanHelper, selectedCollections, numExtraPartons);
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
