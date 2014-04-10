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

  GenericCollection<BNleptonCollection> tightZLeptons(beanHelper);
  GenericCollection<BNleptonCollection> tightLooseZLeptons(beanHelper);
  GenericCollection<BNleptonCollection> tightLoosePreselectedZLeptons(beanHelper);

  GenericCollection<BNleptonCollection> tightNonZLeptons(beanHelper);
  GenericCollection<BNleptonCollection> tightLooseNonZLeptons(beanHelper);
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

  GenericCollection<BNmcparticleCollection> genHiggsParticles(beanHelper);
  GenericCollection<BNmcparticleCollection> genTopParticles(beanHelper);

  GenericCollection<BNjetCollection> jetsFromW(beanHelper);
  GenericCollection<BNjetCollection> jetsFromLepTop(beanHelper);
  GenericCollection<BNjetCollection> jetsFromHadTop(beanHelper);

  GenericCollection<BNleptonCollection> leptonsFromW(beanHelper);
  GenericCollection<BNleptonCollection> leptonsFromZ(beanHelper);

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

  GenericCollectionSizeVariable<BNjetCollection> numJetsFromW(&(jetsFromW.ptrToItems), "numJetsFromW");
  kinVars.push_back(&numJetsFromW);

  GenericCollectionSizeVariable<BNjetCollection> numJetsFromLepTop(&(jetsFromLepTop.ptrToItems), "numJetsFromLepTop");
  kinVars.push_back(&numJetsFromLepTop);

  GenericCollectionSizeVariable<BNjetCollection> numJetsFromHadTop(&(jetsFromHadTop.ptrToItems), "numJetsFromHadTop");
  kinVars.push_back(&numJetsFromHadTop);

  GenericCollectionSizeVariable<BNleptonCollection> numTightLeptons(&(tightLeptons.ptrToItems), "numTightLeptons");
  kinVars.push_back(&numTightLeptons);
  
  GenericCollectionSizeVariable<BNleptonCollection> numTightLooseLeptons(&(tightLooseLeptons.ptrToItems), "numTightLooseLeptons");
  kinVars.push_back(&numTightLooseLeptons);

  GenericCollectionSizeVariable<BNleptonCollection> numAllLeptons(&(tightLoosePreselectedLeptons.ptrToItems), "numAllLeptons");
  kinVars.push_back(&numAllLeptons);
  numAllLeptons.setCutMin(3);
  cutVars.push_back(&numAllLeptons);

  GenericCollectionSizeVariable<BNmuonCollection> numAllMuons(&(tightLoosePreselectedMuons.ptrToItems), "numAllMuons");
  kinVars.push_back(&numAllMuons);

  GenericCollectionSizeVariable<BNelectronCollection> numAllElectrons(&(tightLoosePreselectedElectrons.ptrToItems), "numAllElectrons");
  kinVars.push_back(&numAllElectrons);

  GenericCollectionSizeVariable<BNleptonCollection> numTightZLeptons(&(tightZLeptons.ptrToItems), "numTightZLeptons");
  kinVars.push_back(&numTightZLeptons);

  GenericCollectionSizeVariable<BNleptonCollection> numTightLooseZLeptons(&(tightLooseZLeptons.ptrToItems), "numTightLooseZLeptons");
  kinVars.push_back(&numTightLooseZLeptons);

  GenericCollectionSizeVariable<BNleptonCollection> numAllZLeptons(&(tightLoosePreselectedZLeptons.ptrToItems), "numAllZLeptons");
  kinVars.push_back(&numAllZLeptons);

  GenericCollectionSizeVariable<BNleptonCollection> numTightNonZLeptons(&(tightNonZLeptons.ptrToItems), "numTightNonZLeptons");
  kinVars.push_back(&numTightNonZLeptons);

  GenericCollectionSizeVariable<BNleptonCollection> numTightLooseNonZLeptons(&(tightLooseNonZLeptons.ptrToItems), "numTightLooseNonZLeptons");
  kinVars.push_back(&numTightLooseNonZLeptons);

  GenericCollectionSizeVariable<BNleptonCollection> numAllNonZLeptons(&(tightLoosePreselectedNonZLeptons.ptrToItems), "numAllNonZLeptons");
  kinVars.push_back(&numAllNonZLeptons);

  GenericCollectionSizeVariable<BNleptonCollection> numLeptonsFromW(&(leptonsFromW.ptrToItems), "numLeptonsFromW");
  kinVars.push_back(&numLeptonsFromW);

  GenericCollectionSizeVariable<BNleptonCollection> numLeptonsFromZ(&(leptonsFromZ.ptrToItems), "numLeptonsFromZ");
  kinVars.push_back(&numLeptonsFromZ);

  GenericCollectionSizeVariable<BNtauCollection> numAllTaus(&(tightLoosePreselectedTaus.ptrToItems), "numAllTaus");
  kinVars.push_back(&numAllTaus);

  GenericCollectionSizeVariable<BNtauCollection> numTightLooseTaus(&(tightLooseTaus.ptrToItems), "numTightLooseTaus");
  kinVars.push_back(&numTightLooseTaus);

  GenericCollectionSizeVariable<BNtauCollection> numTightTaus(&(tightTaus.ptrToItems), "numTightTaus");
  kinVars.push_back(&numTightTaus);

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
  RecoIDIsoSIPSFs myRecoIDIsoSIPSF3Lep(3, &(tightLoosePreselectedLeptons.ptrToItems));
  kinVars.push_back(&myRecoIDIsoSIPSF3Lep);

  RecoIDIsoSIPSFs myRecoIDIsoSIPSF4Lep(3, &(tightLoosePreselectedLeptons.ptrToItems));
  kinVars.push_back(&myRecoIDIsoSIPSF4Lep);

  LeptonTriggerScaleFactors myLepTrig(&lepHelper, &(tightMuons.ptrToItems), &(looseMuons.ptrToItems),
                                      &(preselectedMuons.ptrToItems), &(tightElectrons.ptrToItems),
                                      &(looseElectrons.ptrToItems), &(preselectedElectrons.ptrToItems));
  kinVars.push_back(&myLepTrig);

  //Give particular collections
  TightChargeAndLepMVAScaleFactors myTightChargeAndLepMVASF3Lep(3, &(tightLoosePreselectedLeptons.ptrToItems));
  kinVars.push_back(&myTightChargeAndLepMVASF3Lep);

  TightChargeAndLepMVAScaleFactors myTightChargeAndLepMVASF4Lep(4, &(tightLoosePreselectedLeptons.ptrToItems));
  kinVars.push_back(&myTightChargeAndLepMVASF4Lep);

  TightChargeAndLepMVAScaleFactorsPerLepton myTightChargeAndLepMVASFPerLepton(3, &(tightLoosePreselectedLeptons.ptrToItems));
  kinVars.push_back(&myTightChargeAndLepMVASFPerLepton);

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

  DataDrivenFR<BNleptonCollection> myDataDrivenFR3Tight(&lepHelper, &(tightLoosePreselectedLeptons.ptrToItems), &(mediumCSVJets.ptrToItems),
                                                        3, 0.7, "FR_merged_data", "QF_data_el", "_3_tight"); 
  kinVars.push_back(&myDataDrivenFR3Tight);
  
  DataDrivenFR<BNleptonCollection> myDataDrivenFR2LooseZ1TightNonZ(&lepHelper, &(tightLoosePreselectedZLeptons.ptrToItems), &(mediumCSVJets.ptrToItems),
                                                                   2, -0.3, "FR_merged_data", "QF_data_el", "_2_loose_Z_1_tight_nonZ",
                                                                   &(tightLoosePreselectedNonZLeptons.ptrToItems), 1, 0.7); 
  kinVars.push_back(&myDataDrivenFR2LooseZ1TightNonZ);

  DataDrivenFRPerLepton<BNleptonCollection> myDataDrivenFRPerLepton2LooseZ(&lepHelper, &(tightLoosePreselectedZLeptons.ptrToItems), &(mediumCSVJets.ptrToItems),
                                                                   2, -0.3, "FR_merged_data", "QF_data_el", "_2_loose_Z"); 
  kinVars.push_back(&myDataDrivenFRPerLepton2LooseZ);
  
  DataDrivenFRPerLepton<BNleptonCollection> myDataDrivenFRPerLepton1TightNonZ(&lepHelper, &(tightLoosePreselectedNonZLeptons.ptrToItems), &(mediumCSVJets.ptrToItems),
                                                                   1, 0.7, "FR_merged_data", "QF_data_el", "_1_tight_nonZ"); 
  kinVars.push_back(&myDataDrivenFRPerLepton1TightNonZ);
  
  DataDrivenFR<BNleptonCollection> myDataDrivenFR3Loose(&lepHelper, &(tightLoosePreselectedLeptons.ptrToItems), &(mediumCSVJets.ptrToItems),
                                                        3, -0.3, "FR_merged_data", "QF_data_el", "_3_loose");
  kinVars.push_back(&myDataDrivenFR3Loose);
  
  DataDrivenFR<BNleptonCollection> myDataDrivenFR4Loose(&lepHelper, &(tightLoosePreselectedLeptons.ptrToItems), &(mediumCSVJets.ptrToItems),
                                                        4, -0.3, "FR_merged_data", "QF_data_el", "_4_loose");
  kinVars.push_back(&myDataDrivenFR4Loose);

//   //Causes run-time error
//   DBCorrectedRelIsoDR04s myDBCorrectedRelIsoDR04s(&lepHelper, 4);
//   kinVars.push_back(&myDBCorrectedRelIsoDR04s);

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

  //3l ttbarZ
  TwoObjectKinematic<BNmetCollection,BNleptonCollection>
    myMtMetNonZLep("MT", "min", "WLike_MT_met_lep",
                   &(met.ptrToItems), "met", 1, 1,
                   &(tightLoosePreselectedNonZLeptons.ptrToItems), "all_nonZ_leptons_by_pt", 1, 1);
  kinVars.push_back(&myMtMetNonZLep);
  
  ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection>
    myMtMetNonZLepB("MT", "all_pairs", "topLike_MT_met_lep_b",
                    &(met.ptrToItems), "met", 1, 1,
                    &(tightLoosePreselectedNonZLeptons.ptrToItems), "all_nonZ_leptons_by_pt", 1, 1,
                    &(jetsByCSV.ptrToItems), "jets_by_CSV", 1, 2);
  kinVars.push_back(&myMtMetNonZLepB);
  
  ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection>
    myMtMetNonZLepB175("MT", "closest_to", "topLike_MT_met_lep_b_175",
                       &(met.ptrToItems), "met", 1, 1,
                       &(tightLoosePreselectedNonZLeptons.ptrToItems), "all_nonZ_leptons_by_pt", 1, 1,
                       &(jetsByCSV.ptrToItems), "jets_by_CSV", 1, 2,
                       175);
  kinVars.push_back(&myMtMetNonZLepB175);
  
  TwoObjectKinematic<BNleptonCollection,BNjetCollection>
    myMassNonZLepB("mass", "all_pairs", "topLike_mass_lep_b",
                   &(tightLoosePreselectedNonZLeptons.ptrToItems), "all_nonZ_leptons_by_pt", 1, 1,
                   &(jetsByCSV.ptrToItems), "jets_by_CSV", 1, 2);
  kinVars.push_back(&myMassNonZLepB);

  TwoObjectKinematic<BNleptonCollection,BNjetCollection>
    myMassNonZLepB100("mass", "closest_to", "topLike_mass_lep_b_100",
                   &(tightLoosePreselectedNonZLeptons.ptrToItems), "all_nonZ_leptons_by_pt", 1, 1,
                      &(jetsByCSV.ptrToItems), "jets_by_CSV", 1, 2,
                      100);
  kinVars.push_back(&myMassNonZLepB100);

  TwoObjectKinematic<BNjetCollection,BNjetCollection>
    myTopLikeMultijetMassB1("mass", "vector_sum", "topLike_multijet_mass_b1",
                               &(jetsByCSV.ptrToItems), "jets_by_CSV", 1, 1,
                               &(jetsByCSV.ptrToItems), "jets_by_CSV", 3, 99);
  kinVars.push_back(&myTopLikeMultijetMassB1);

  TwoObjectKinematic<BNjetCollection,BNjetCollection>
    myTopLikeMultijetMassB2("mass", "vector_sum", "topLike_multijet_mass_b2",
                               &(jetsByCSV.ptrToItems), "jets_by_CSV", 2, 2,
                               &(jetsByCSV.ptrToItems), "jets_by_CSV", 3, 99);
  kinVars.push_back(&myTopLikeMultijetMassB2);

  ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection>
    myMtMetNonZLepJets("MT", "vector_sum", "topPairLike_MT_met_lep_jets",
                       &(met.ptrToItems), "met", 1, 1,
                       &(tightLoosePreselectedNonZLeptons.ptrToItems), "all_nonZ_leptons_by_pt", 1, 1,
                       &(jets.ptrToItems), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMtMetNonZLepJets);
  
  TwoObjectKinematic<BNleptonCollection,BNjetCollection>
    myMassNonZLepJets("mass", "vector_sum", "topPairLike_mass_lep_jets",
                      &(tightLoosePreselectedNonZLeptons.ptrToItems), "all_nonZ_leptons_by_pt", 1, 1,
                      &(jets.ptrToItems), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMassNonZLepJets);


  // Two lepton kinematics
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMinMassLepLepSFOS("mass", "min", "min_mass_leplep_SFOS",
                                                                                &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                                                                                &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                                                                                -99, "same_flavour", "opposite_sign");
  kinVars.push_back(&myMinMassLepLepSFOS);
  
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myMinMassLepLep("mass", "min", "min_mass_leplep",
                                                                            &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                                                                            &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99);
  kinVars.push_back(&myMinMassLepLep);
  
  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZLikeMassLepLepSFOSTight("mass", "closest_to", "ZLike_mass_leplep_SFOS_tight",
                                                                                     &(tightLeptons.ptrToItems), "tight_leptons_by_pt", 1, 99,
                                                                                     &(tightLeptons.ptrToItems), "tight_leptons_by_pt", 1, 99,
                                                                                     91.2, "same_flavour", "opposite_sign");
  kinVars.push_back(&myZLikeMassLepLepSFOSTight);  

  TwoObjectKinematic<BNleptonCollection,BNleptonCollection> myZLikeMassLepLepSFOSTightLoose("mass", "closest_to", "ZLike_mass_leplep_SFOS_loose",
                                                                                     &(tightLooseLeptons.ptrToItems), "tightLoose_leptons_by_pt", 1, 99,
                                                                                     &(tightLooseLeptons.ptrToItems), "tightLoose_leptons_by_pt", 1, 99,
                                                                                     91.2, "same_flavour", "opposite_sign");
  kinVars.push_back(&myZLikeMassLepLepSFOSTightLoose);  

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

//   //Variables for CERN same-sign dilepton BDT
  TwoObjectKinematic<BNleptonCollection,BNjetCollection> myMHT("pt", "vector_sum", "mht",
                                                               &(tightLoosePreselectedLeptons.ptrToItems), "all_leptons_by_pt", 1, 99,
                                                               &(jets.ptrToItems), "jets_by_pt", 1, 99);
  kinVars.push_back(&myMHT);

//   TightCharges myTightCharges(&(tightLoosePreselectedLeptons.ptrToItems), "CERN_tight_charge", "all_leptons_by_pt", 2);
//   kinVars.push_back(&myTightCharges);
//   //myTightCharges.setCut("pass");

  //////////////////////////////////
  //Variables for matching algorithm
  //////////////////////////////////
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

  GenericCollectionMember<int, BNleptonCollection> LeptonFromWTkCharge(Reflex::Type::ByName("BNlepton"), &(leptonsFromW.ptrToItems),
                                                                       "tkCharge", "leptonsFromW",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&LeptonFromWTkCharge);

  TwoObjectKinematic<BNmetCollection,BNleptonCollection>
    myGenWMtMetLep("MT", "min", "gen_W_MT_met_lep",
                   &(met.ptrToItems), "met", 1, 1,
                   &(leptonsFromW.ptrToItems), "leptonsFromW", 1, 1);
  kinVars.push_back(&myGenWMtMetLep);
  
  TwoObjectKinematic<BNjetCollection,BNjetCollection>
    myGenWDijetMass("mass", "closest_to", "gen_W_dijet_mass",
                          &(jetsFromW.ptrToItems), "jetsFromW_by_CSV", 1, 1,
                          &(jetsFromW.ptrToItems), "jetsFromW_by_CSV", 2, 2,
                          81);
  kinVars.push_back(&myGenWDijetMass);

  TwoObjectKinematic<BNjetCollection,BNjetCollection>
    myGenHadTopTrijetMass("mass", "vector_sum", "gen_hadTop_trijet_mass",
                           &(jetsFromW.ptrToItems), "jetsFromW_by_CSV", 1, 2,
                           &(jetsFromHadTop.ptrToItems), "jetsFromHadTop", 1, 1);
  kinVars.push_back(&myGenHadTopTrijetMass);

  ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection>
    myGenLepTopMtMetLepB("MT", "min", "gen_lepTop_MT_met_lep_b",
                       &(met.ptrToItems), "met", 1, 1,
                       &(leptonsFromW.ptrToItems), "leptonsFromW", 1, 1,
                       &(jetsByCSV.ptrToItems), "jetsFromLepTop", 1, 1);
  kinVars.push_back(&myGenLepTopMtMetLepB);
  
  TwoObjectKinematic<BNleptonCollection,BNjetCollection>
    myGenLepTopMassLepB("mass", "min", "gen_lepTop_mass_lep_b",
                       &(leptonsFromW.ptrToItems), "leptonsFromW", 1, 1,
                       &(jetsByCSV.ptrToItems), "jetsFromLepTop", 1, 1);
  kinVars.push_back(&myGenLepTopMassLepB);
  
  TwoObjectKinematic<BNjetCollection,BNjetCollection>
    myDijetMasses("mass", "all_pairs", "dijet_mass",
                  &(jets.ptrToItems), "jets_by_pt", 1, 6,
                  &(jets.ptrToItems), "jets_by_pt", 1, 6);
  kinVars.push_back(&myDijetMasses);

  ThreeObjectKinematic<BNjetCollection,BNjetCollection,BNjetCollection>
    myTrijetMasses("mass", "all_pairs", "trijet_mass",
                  &(jets.ptrToItems), "jets_by_pt", 1, 6,
                  &(jets.ptrToItems), "jets_by_pt", 1, 6,
                  &(jets.ptrToItems), "jets_by_pt", 1, 6);
  kinVars.push_back(&myTrijetMasses);

  TwoObjectKinematic<BNleptonCollection,BNjetCollection>
    myMassLepFromWJet("mass", "all_pairs", "mass_lepFromW_jet",
                      &(leptonsFromW.ptrToItems), "leptonsFromW", 1, 1,
                      &(jets.ptrToItems), "jets_by_pt", 1, 6);
  kinVars.push_back(&myMassLepFromWJet);
  
  ThreeObjectKinematic<BNmetCollection,BNleptonCollection,BNjetCollection>
    myMtMetLepFromWJet("MT", "all_pairs", "MT_met_lepFromW_jet",
                       &(met.ptrToItems), "met", 1, 1,
                       &(leptonsFromW.ptrToItems), "leptonsFromW", 1, 1,
                       &(jets.ptrToItems), "jets_by_pt", 1, 6);
  kinVars.push_back(&myMtMetLepFromWJet);
  
  
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

  // isMuon / isElectron
  
  GenericCollectionMember<int, BNleptonCollection> NonZLeptonIsMuon(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
                                                                       "isMuon", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&NonZLeptonIsMuon);

  GenericCollectionMember<int, BNleptonCollection> NonZLeptonIsElectron(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
                                                                       "isElectron", "all_nonZ_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&NonZLeptonIsElectron);

  // tkCharge
  
  GenericCollectionMember<int, BNleptonCollection> LeptonTkCharge(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
                                                                  "tkCharge", "all_leptons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&LeptonTkCharge);

  GenericCollectionMember<int, BNleptonCollection> NonZLeptonTkCharge(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedNonZLeptons.ptrToItems),
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

  GenericCollectionMember<double, BNleptonCollection> allLeptonSIP(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
                                                                   "SIP", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonSIP);

  GenericCollectionMember<double, BNleptonCollection> allLeptonD0(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
                                                                  "correctedD0Vertex", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonD0);

  GenericCollectionMember<double, BNleptonCollection> allLeptonDZ(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
                                                                  "correctedDZ", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonDZ);

  GenericCollectionMember<double, BNleptonCollection> allLeptonIP(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
                                                                               "IP", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonIP);

  GenericCollectionMember<double, BNleptonCollection> allLeptonIPError(Reflex::Type::ByName("BNlepton"), &(tightLoosePreselectedLeptons.ptrToItems),
                                                                                    "IPError", "all_leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonIPError);

  /////////////////////////////////////
  //// REQUIRED - Properties of muons and electrons for lepton selection
  /////////////////////////////////////

  GenericCollectionMember<int, BNmuonCollection> allMuonPFmuon(Reflex::Type::ByName("BNmuon"), &(tightLoosePreselectedMuons.ptrToItems),
                                                               "isPFMuon", "all_muons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allMuonPFmuon);

  GenericCollectionMember<int, BNmuonCollection> allMuonGlobalMuon(Reflex::Type::ByName("BNmuon"), &(tightLoosePreselectedMuons.ptrToItems),
                                                                   "isGlobalMuon", "all_muons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allMuonGlobalMuon);

  GenericCollectionMember<int, BNmuonCollection> allMuonTrackerMuon(Reflex::Type::ByName("BNmuon"), &(tightLoosePreselectedMuons.ptrToItems),
                                                                    "isTrackerMuon", "all_muons_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  kinVars.push_back(&allMuonTrackerMuon);

  GenericCollectionMember<int, BNelectronCollection> allElectronNumExpInnerHits(Reflex::Type::ByName("BNelectron"), &(tightLoosePreselectedElectrons.ptrToItems),
                                                                                "numberOfExpectedInnerHits", "all_electrons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allElectronNumExpInnerHits);

  GenericCollectionMember<int, BNelectronCollection> allElectronPassConvVeto(Reflex::Type::ByName("BNelectron"), &(tightLoosePreselectedElectrons.ptrToItems),
                                                                             "passConvVeto", "all_electrons_by_pt",  KinematicVariableConstants::INT_INIT, 2);
  kinVars.push_back(&allElectronPassConvVeto);

  GenericCollectionMember<double, BNelectronCollection> allElectronEta(Reflex::Type::ByName("BNelectron"), &(tightLoosePreselectedElectrons.ptrToItems),
                                                                       "eta", "all_electrons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allElectronEta);

  GenericCollectionMember<double, BNelectronCollection> allElectronPt(Reflex::Type::ByName("BNelectron"), &(tightLoosePreselectedElectrons.ptrToItems),
                                                                      "pt", "all_electrons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allElectronPt);

  /////////////////////////////////////
  //// END REQUIRED - Properties of muons and electrons for lepton selection
  /////////////////////////////////////

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


//   GenericCollectionMember<double, BNjetCollection> allJetEta(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems),
//                                                              "eta", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
//   kinVars.push_back(&allJetEta);

  GenericCollectionMember<double, BNjetCollection> allJetCSV(Reflex::Type::ByName("BNjet"),  &(jets.ptrToItems),
                                                             "btagCombinedSecVertex", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetCSV);

  GenericCollectionMember<int, BNjetCollection> allJetGenPartonId(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems),
                                                             "genPartonId", "jets_by_pt",  KinematicVariableConstants::INT_INIT, 6);
  kinVars.push_back(&allJetGenPartonId);

  GenericCollectionMember<int, BNjetCollection> allJetGenPartonMotherId(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems),
                                                             "genPartonMotherId", "jets_by_pt",  KinematicVariableConstants::INT_INIT, 6);
  kinVars.push_back(&allJetGenPartonMotherId);

  GenericCollectionMember<int, BNjetCollection> allJetGenPartonGrandMother00Id(Reflex::Type::ByName("BNjet"), &(jets.ptrToItems),
                                                             "genPartonGrandMother00Id", "jets_by_pt",  KinematicVariableConstants::INT_INIT, 6);
  kinVars.push_back(&allJetGenPartonGrandMother00Id);

//   GenericCollectionMember<double, BNjetCollection> mediumBJetPt(Reflex::Type::ByName("BNjet"), &(jets.ptrToItemsMediumCSV),
//                                                             "pt", "medium_tags_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&mediumBJetPt);

//   GenericCollectionMember<double, BNjetCollection> mediumBJetEta(Reflex::Type::ByName("BNjet"), &(jets.ptrToItemsMediumCSV),
//                                                              "eta", "medium_tags_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&mediumBJetEta);

//   GenericCollectionMember<double, BNjetCollection> notMediumBJetPt(Reflex::Type::ByName("BNjet"), &(jets.ptrToItemsNotMediumCSV),
//                                                             "pt", "medium_untags_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&notMediumBJetPt);

//   GenericCollectionMember<double, BNjetCollection> notMediumBJetEta(Reflex::Type::ByName("BNjet"), &(jets.ptrToItemsNotMediumCSV),
//                                                              "eta", "medium_untags_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
//   kinVars.push_back(&notMediumBJetEta);

  ////////// jets by CSV //////////
  GenericCollectionMember<double, BNjetCollection> allJetByCSVPt(Reflex::Type::ByName("BNjet"), &(jetsByCSV.ptrToItems),
                                                            "pt", "jets_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetByCSVPt);

  GenericCollectionMember<double, BNjetCollection> allJetByCSVMass(Reflex::Type::ByName("BNjet"), &(jetsByCSV.ptrToItems),
                                                            "mass", "jets_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetByCSVMass);

//   GenericCollectionMember<double, BNjetCollection> allJetByCSVEta(Reflex::Type::ByName("BNjet"), &(jetsByCSV.ptrToItems),
//                                                              "eta", "jets_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 6);
//   kinVars.push_back(&allJetByCSVEta);

  GenericCollectionMember<double, BNjetCollection> allJetByCSVCSV(Reflex::Type::ByName("BNjet"),  &(jetsByCSV.ptrToItems),
                                                             "btagCombinedSecVertex", "jets_by_CSV",  KinematicVariableConstants::FLOAT_INIT, 6);
  kinVars.push_back(&allJetByCSVCSV);

  GenericCollectionMember<int, BNjetCollection> allJetByCSVGenPartonId(Reflex::Type::ByName("BNjet"), &(jetsByCSV.ptrToItems),
                                                             "genPartonId", "jets_by_CSV",  KinematicVariableConstants::INT_INIT, 6);
  kinVars.push_back(&allJetByCSVGenPartonId);

  GenericCollectionMember<int, BNjetCollection> allJetByCSVGenPartonMotherId(Reflex::Type::ByName("BNjet"), &(jetsByCSV.ptrToItems),
                                                             "genPartonMotherId", "jets_by_CSV",  KinematicVariableConstants::INT_INIT, 6);
  kinVars.push_back(&allJetByCSVGenPartonMotherId);

  GenericCollectionMember<int, BNjetCollection> allJetByCSVGenPartonGrandMother00Id(Reflex::Type::ByName("BNjet"), &(jetsByCSV.ptrToItems),
                                                             "genPartonGrandMother00Id", "jets_by_CSV",  KinematicVariableConstants::INT_INIT, 6);
  kinVars.push_back(&allJetByCSVGenPartonGrandMother00Id);


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

//   FinalBDT myFinalBDT(&allLeptonEta, &allLeptonPt, &myMHT, &myMinDeltaRLep2Jet, &myMtMetLep, &mySumPt);
//   kinVars.push_back(&myFinalBDT);

//   HypothesisTester_ttZ myHypothesisTester_ttZ(&(tightLoosePreselectedNonZLeptons.ptrToItems), &(jets.ptrToItems), &(met.ptrToItems));
//   kinVars.push_back(&myHypothesisTester_ttZ);

  MatchTester_ttZ_3l myMatchTester_ttZ_3l(&(tightLoosePreselectedNonZLeptons.ptrToItems), &(jetsByCSV.ptrToItems), &(met.ptrToItems));
  kinVars.push_back(&myMatchTester_ttZ_3l);

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
    tightLoosePreselectedTaus.initializeRawItemsSortedByPt(ev, "BNproducer","selectedPatTausPFlow");

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
    jets.correctRawJets();
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

    genHiggsParticles.initializeRawItems(mcParticles.rawItems);
    auto higgsPDGID = [] (BNmcparticle p) { return (p.id == 25); };
    genHiggsParticles.keepSelectedParticles(higgsPDGID);
    genTopParticles.initializeRawItems(mcParticles.rawItems);
    auto topPDGID = [] (BNmcparticle p) { return (abs(p.id) == 6); };
    genTopParticles.keepSelectedParticles(topPDGID);

    // Initialize SFOS pair closest to Z mass
    myZLikeMassLepLepSFOSTight.reset();
    myZLikeMassLepLepSFOSTight.evaluate();
    myZLikeMassLepLepSFOSTightLoose.reset();
    myZLikeMassLepLepSFOSTightLoose.evaluate();
    myZLikeMassLepLepSFOSAll.reset();
    myZLikeMassLepLepSFOSAll.evaluate();
    
    tightZLeptons.resetAndPushBack(myZLikeMassLepLepSFOSTight.selectedParticles1);
    tightZLeptons.pushBack(myZLikeMassLepLepSFOSTight.selectedParticles2);
    tightLooseZLeptons.resetAndPushBack(myZLikeMassLepLepSFOSTightLoose.selectedParticles1);
    tightLooseZLeptons.pushBack(myZLikeMassLepLepSFOSTightLoose.selectedParticles2);
    tightLoosePreselectedZLeptons.resetAndPushBack(myZLikeMassLepLepSFOSAll.selectedParticles1);
    tightLoosePreselectedZLeptons.pushBack(myZLikeMassLepLepSFOSAll.selectedParticles2);

    tightNonZLeptons.initializeRawItems(beanHelper->GetDifference(tightLeptons.items, tightZLeptons.items));
    tightLooseNonZLeptons.initializeRawItems(beanHelper->GetDifference(tightLooseLeptons.items, tightLooseZLeptons.items));
    tightLoosePreselectedNonZLeptons.initializeRawItems(beanHelper->GetDifference(tightLoosePreselectedLeptons.items, tightLoosePreselectedZLeptons.items));

    leptonsFromW.resetAndPushBack(tightLoosePreselectedLeptons.items);
    auto leptonFromGenW = [] (BNlepton l) { return (abs(l.genMotherId) == 24); };
    leptonsFromW.keepSelectedParticles(leptonFromGenW);
    leptonsFromZ.resetAndPushBack(tightLoosePreselectedLeptons.items);
    auto leptonFromGenZ = [] (BNlepton l) { return (l.genMotherId == 23); };
    leptonsFromZ.keepSelectedParticles(leptonFromGenZ);
    
//     leptonsFromW.resetAndPushBack(tightLoosePreselectedLeptons.items);
//     auto leptonFromGenW = [] (BNlepton l) { return (abs(l.genMotherId) == 24); };
//     leptonsFromW.keepSelectedLeptons(leptonFromGenW);
//     leptonsFromZ.resetAndPushBack(tightLoosePreselectedLeptons.items);
//     auto leptonFromGenZ = [] (BNlepton l) { return (l.genMotherId == 23); };
//     leptonsFromZ.keepSelectedLeptons(leptonFromGenZ);
    
    jetsFromW.initializeRawItems(jetsByCSV.items);
    auto jetFromGenW = [] (BNjet j) { return (abs(j.genPartonMotherId) == 24); };
    jetsFromW.keepSelectedParticles(jetFromGenW);

    int W_lep_charge = KinematicVariableConstants::INT_INIT;
    if (leptonsFromW.items.size() >= 1) W_lep_charge = leptonsFromW.items.at(0)->tkCharge;
    
    jetsFromLepTop.initializeRawItems(jets.items);
    auto jetFromGenLepTop = [] (BNjet j, int i) { return (j.genPartonMotherId == 6*i); };
    jetsFromLepTop.keepSelectedParticles(jetFromGenLepTop, W_lep_charge);
    jetsFromHadTop.initializeRawItems(jets.items);
    auto jetFromGenHadTop = [] (BNjet j, int i) { return (j.genPartonMotherId == -6*i); };
    jetsFromHadTop.keepSelectedParticles(jetFromGenHadTop, W_lep_charge);

//     jetsFromLepTop.initializeRawItems(jets.items);
//     auto jetFromGenLepTop = [] (BNjet j, int i) { return (j.genPartonMotherId == 6*i); };
//     jetsFromLepTop.keepSelectedParticlesByInt(jetFromGenLepTop, W_lep_charge);
//     jetsFromHadTop.initializeRawItems(jets.items);
//     auto jetFromGenHadTop = [] (BNjet j, int i) { return (j.genPartonMotherId == -6*i); };
//     jetsFromHadTop.keepSelectedParticlesByInt(jetFromGenHadTop, W_lep_charge);

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
