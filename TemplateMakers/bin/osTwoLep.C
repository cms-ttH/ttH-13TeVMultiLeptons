//new include items for miniAOD compatibility
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/GenericParticle.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"
#include "DataFormats/PatCandidates/interface/Tau.h"

#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
#include <TRandom3.h>
#include <vector>
#include "ttHMultileptonAnalysis/TemplateMakers/interface/GenericCollectionMember.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/GenericCollectionMethod.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/GenericCollectionSizeVariable.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/GenericCollection.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/TwoObjectKinematic.h"

// #include "ttHMultileptonAnalysis/TemplateMakers/interface/minDr_leplep.h"
// #include "ttHMultileptonAnalysis/TemplateMakers/interface/minDr_leplep_dxyz.h"
// #include "ttHMultileptonAnalysis/TemplateMakers/interface/minDr_leplep2.h"
// #include "ttHMultileptonAnalysis/TemplateMakers/interface/minDr_leplep3.h"

#include "ttHMultileptonAnalysis/TemplateMakers/interface/GenPt.h"

#include "ttHMultileptonAnalysis/TemplateMakers/interface/SingleObjectVariable.h"

#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

#include "ttHMultileptonAnalysis/TemplateMakers/interface/EGammaMvaEleEstimatorFWLite.h"

///-------------- Kinematic Variables ------------------
//done
#include "ttHMultileptonAnalysis/TemplateMakers/interface/JobParameters.h"
//needs work
#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"

#include "Reflex/Object.h"
#include "Reflex/Type.h"
#include "Reflex/Member.h"
#include "Reflex/Kernel.h"

//----------  Use python utilities to configure
#include "FWCore/PythonParameterSet/interface/PythonProcessDesc.h"
#include "FWCore/ParameterSet/interface/ProcessDesc.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"

//define some global variables (probs not the best idea)!! 
bool isData;
string analysisYear = "2012_53x";
string sampleName;
int sampleNumber;


void detectData(string sampleName) {
  isData = false;
  string dataset = "MC";

  if (TString(sampleName).Contains("DoubleElectron")) dataset = "DoubleElectron";
  if (TString(sampleName).Contains("DoubleMu")) dataset = "DoubleMu";
  if (TString(sampleName).Contains("MuEG")) dataset = "MuEG";
  if (TString(sampleName).Contains("MET")) dataset = "MET";

  if (dataset != "MC") {
    std::cout << "CONFIG: DATA detected for sample " << sampleName << std::endl;
    isData = true;
  }
}

int convertSampleNameToNumber(string sampleName) {
  sampleNumber = 999999;
  double weight_Xsec = 1.0;
  int nGen = 1;
  float Xsec = 1.0;

  // make a TString version of this so you can use it for contains
  TString tmpName (sampleName);

  if (analysisYear == "2012_52x" || analysisYear == "2012_53x") {
    if (isData) sampleNumber = -1;
    else if (sampleName == "ttbar" || tmpName.Contains("ttbar_part")) { sampleNumber = 2500;
      nGen = 6912438+1362471; Xsec = 245.8; }
    else if (tmpName.Contains("ttH") && analysisYear == "2012_52x") {
      if (tmpName.Contains("FullSim")) sampleNumber = 8120;
      else sampleNumber = 9120;
    }
    else if (tmpName.Contains("ttH") && analysisYear == "2012_53x") {
      if (tmpName.Contains("_tautau")) { sampleNumber = 7120;
        nGen = 992997; Xsec = 0.1302*0.1302; }
      else if (tmpName.Contains("_bb")) { sampleNumber = 8120;
        nGen = 980931; Xsec = 0.1302*0.577; }
      else { sampleNumber = 9120;
        nGen = 992997; Xsec = 0.1302; }
    }
    else assert (sampleName == "sampleName is not in the approved list");
  }
  else {
    assert (analysisYear == "either 2012_52x, 2012_53x, or 2011");
  }

  if (tmpName.Contains("wz") || tmpName.Contains("zz")) {
    if (tmpName.Contains("_lf")) sampleNumber = sampleNumber*10 + 1;
    if (tmpName.Contains("_cc")) sampleNumber = sampleNumber*10 + 2;
    if (tmpName.Contains("_bb")) sampleNumber = sampleNumber*10 + 4;
    else if (tmpName.Contains("_b")) sampleNumber = sampleNumber*10 + 3;
  }

  std::cout << "CONFIG: Sample Name = " << sampleName
            << ", sample Number = " << sampleNumber << endl;
  
  std::cout << weight_Xsec << nGen << Xsec << endl;
  return sampleNumber;
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
  AutoLibraryLoader::enable();

  int debug = 0; // levels of debug, 10 is large

  JobParameters myConfig = parseJobOptions(argc, argv);

  TFile * outputFile = new TFile (myConfig.outputFileName.c_str(), "RECREATE");

  outputFile->cd();

  TTree * summaryTree = new TTree("summaryTree", "Summary Event Values");

  fwlite::ChainEvent ev(myConfig.inputFileNames);

  // setup the analysis
  // it comes from the lepHelper

  sampleName = myConfig.sampleName;
  detectData(sampleName);
  convertSampleNameToNumber(sampleName);
  // initializePUReweighting();

  //initialize hacked electron mvaID
  EGammaMvaEleEstimatorFWLite* mvaID_ = new EGammaMvaEleEstimatorFWLite();
  bool useBinnedVersion_ = true;
  string method_ = "BDT";
  EGammaMvaEleEstimatorFWLite::MVAType type_ = EGammaMvaEleEstimatorFWLite::kNonTrig;
  std::vector<std::string> mvaWeightFiles_;
  mvaWeightFiles_.push_back("EgammaAnalysis/ElectronTools/data/Electrons_BDTG_NonTrigV0_Cat1.weights.xml");
  mvaWeightFiles_.push_back("EgammaAnalysis/ElectronTools/data/Electrons_BDTG_NonTrigV0_Cat2.weights.xml");
  mvaWeightFiles_.push_back("EgammaAnalysis/ElectronTools/data/Electrons_BDTG_NonTrigV0_Cat3.weights.xml");
  mvaWeightFiles_.push_back("EgammaAnalysis/ElectronTools/data/Electrons_BDTG_NonTrigV0_Cat4.weights.xml");
  mvaWeightFiles_.push_back("EgammaAnalysis/ElectronTools/data/Electrons_BDTG_NonTrigV0_Cat5.weights.xml");
  mvaWeightFiles_.push_back("EgammaAnalysis/ElectronTools/data/Electrons_BDTG_NonTrigV0_Cat6.weights.xml");
  mvaID_->initialize(method_, type_, useBinnedVersion_, mvaWeightFiles_);
  ///end ele mva id hack  
  
  MiniAODHelper * miniAODhelper = new MiniAODHelper();
  miniAODhelper->SetUp(analysisYear, sampleNumber, analysisType::DIL, isData);

  miniAODhelper->SetFactorizedJetCorrector();
  
  fwlite::Handle<double> rhoHandle;
  rhoHandle.getByLabel(ev,"fixedGridRhoFastjetAll");//"fixedGridRhoAll");
  double rho = *rhoHandle;
  
  miniAODhelper->SetRho(rho);

  sysType::sysType jetSyst = sysType::NA;
  if (myConfig.jetSyst == "NA") jetSyst = sysType::NA;
  else if (myConfig.jetSyst == "JESUp") jetSyst = sysType::JESup;
  else if (myConfig.jetSyst == "JESDown") jetSyst = sysType::JESdown;
  else std::cout << "No valid JES corrections specified - using nominal" << std::endl;
  
  std::cout << jetSyst << std::endl;

  // ---------------------------------------------
  // Note for future development: should these be
  // saved inside the lepHelper somewhere?
  // For now they are ok here
  // ---------------------------------------------
  
  electronID::electronID electronTightID = electronID::electronTight;
  electronID::electronID electronLooseID = electronID::electronLoose;
  electronID::electronID electronPreselectedID = electronID::electronNoCuts;
  electronID::electronID electronCernID = electronID::electronPreselection;
  
  muonID::muonID muonTightID = muonID::muonTight;
  muonID::muonID muonLooseID = muonID::muonLoose;
  muonID::muonID muonPreselectedID = muonID::muonNoCuts;
  muonID::muonID muonCernID = muonID::muonPreselection;
  
  tauID::tauID tauTightID = tauID::tauMedium;
  // tauID::tauID tauLooseID = tauID::tauVLoose;
  tauID::tauID tauPreselectedID = tauID::tauNonIso;
  
  
  //collections
  GenericCollection<pat::ElectronCollection> tightElectrons(miniAODhelper);
  GenericCollection<pat::ElectronCollection> looseElectrons(miniAODhelper);
  GenericCollection<pat::ElectronCollection> preselectedElectrons(miniAODhelper);
  GenericCollection<pat::ElectronCollection> tightLooseElectrons(miniAODhelper);
  GenericCollection<pat::ElectronCollection> loosePreselectedElectrons(miniAODhelper);
  GenericCollection<pat::ElectronCollection> tightLoosePreselectedElectrons(miniAODhelper);
  GenericCollection<pat::ElectronCollection> cernElectrons(miniAODhelper);

  GenericCollection<pat::MuonCollection> tightMuons(miniAODhelper);
  GenericCollection<pat::MuonCollection> looseMuons(miniAODhelper);
  GenericCollection<pat::MuonCollection> preselectedMuons(miniAODhelper);
  GenericCollection<pat::MuonCollection> tightLooseMuons(miniAODhelper);
  GenericCollection<pat::MuonCollection> tightLoosePreselectedMuons(miniAODhelper);
  GenericCollection<pat::MuonCollection> cernMuons(miniAODhelper);

  GenericCollection<pat::TauCollection> tightTaus(miniAODhelper);
  GenericCollection<pat::TauCollection> tightLooseTaus(miniAODhelper);
  GenericCollection<pat::TauCollection> tightLoosePreselectedTaus(miniAODhelper);

  GenericCollection<std::vector<reco::LeafCandidate>> tightLeptons(miniAODhelper);  

  GenericCollection<std::vector<reco::LeafCandidate>> looseLeptons(miniAODhelper);
  GenericCollection<std::vector<reco::LeafCandidate>> preselectedLeptons(miniAODhelper);
  GenericCollection<std::vector<reco::LeafCandidate>> tightLooseLeptons(miniAODhelper);
  GenericCollection<std::vector<reco::LeafCandidate>> tightLoosePreselectedLeptons(miniAODhelper);
  
  GenericCollection<std::vector<reco::LeafCandidate>> cernLeptons(miniAODhelper);

  GenericCollection<pat::JetCollection> jets(miniAODhelper);
  GenericCollection<pat::JetCollection> jets_30(miniAODhelper);
  GenericCollection<pat::JetCollection> jetsByCSV(miniAODhelper);

  GenericCollection<reco::VertexCollection> primaryVertices(miniAODhelper);

  GenericCollection<reco::GenParticleCollection> genParticles(miniAODhelper);
  GenericCollection<reco::GenParticleCollection> genTopParticles(miniAODhelper);
  GenericCollection<reco::GenParticleCollection> genHiggsParticles(miniAODhelper);
  //GenericCollection<pat::PackedGenParticleCollection> genHiggsParticles(miniAODhelper);

  GenericCollection<pat::PackedGenParticleCollection> genLeptons(miniAODhelper);
  //GenericCollection<pat::PackedGenParticleCollection> genElectrons(miniAODhelper);

  vector<ArbitraryVariable*> kinVars;
  vector<ArbitraryVariable*> cutVars;

  double wgt;

  //////////////////////////////////////////////////////////////////////////////
  ////
  //// Add vars to tree
  ////
  //////////////////////////////////////////////////////////////////////////////

  ///////////// Series Variables of data members //////////////// 


  SingleObjectVariable<double>
    evtwgt(&wgt,"aMC@NLO_event_weight");
  kinVars.push_back(&evtwgt);
  
  GenericCollectionMember<float,std::vector<pat::Muon>> 
    allMuonPt(Reflex::Type::ByName("pat::Muon"), &(tightLooseMuons.ptrToItems),
              "pt_", "muons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allMuonPt);

  GenericCollectionMember<float,std::vector<pat::Electron>> 
    allElectronPt(Reflex::Type::ByName("pat::Electron"), &(tightLooseElectrons.ptrToItems),
  		  "pt_", "electrons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 2);
  kinVars.push_back(&allElectronPt);

  GenericCollectionMember<float,std::vector<reco::LeafCandidate>> 
    allLeptonPt(Reflex::Type::ByName("reco::LeafCandidate"), &(tightLooseLeptons.ptrToItems),
  		  "pt_", "leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonPt);

  GenericCollectionMember<float,std::vector<pat::Jet>>
    allJetPt(Reflex::Type::ByName("pat::Jet"), &(jets.ptrToItems),
  		  "pt_", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allJetPt);

  GenericCollectionMember<float,std::vector<reco::LeafCandidate>> 
    allLeptonPhi(Reflex::Type::ByName("reco::LeafCandidate"), &(tightLooseLeptons.ptrToItems),
  		  "phi_", "leptons_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allLeptonPhi);
  

  ///////////// Series Variables of class methods //////////////// 

  // GenericCollectionMethod<int, std::vector<pat::Jet>>
  //   allJetNumberOfDaughters(Reflex::Type::ByName("pat::Jet"), &(jets.ptrToItems),
  // 	      "numberOfDaughters", "", "jets_by_pt",  KinematicVariableConstants::INT_INIT, 4);
  // kinVars.push_back(&allJetNumberOfDaughters);
  
  
  GenPt<std::vector<reco::GenParticle>>
    higgsPdgId(&(genHiggsParticles.ptrToItems),"genHiggsPt");
  kinVars.push_back(&higgsPdgId);


  GenericCollectionMethod<float, std::vector<pat::Jet>>
    allJetCSV(Reflex::Type::ByName("pat::Jet"), &(jets.ptrToItems),
  	      "bDiscriminator", "combinedSecondaryVertexBJetTags", "jets_by_pt",  KinematicVariableConstants::FLOAT_INIT, 4);
  kinVars.push_back(&allJetCSV);

  ///////////// Size Variables //////////////// 

  GenericCollectionSizeVariable<std::vector<pat::Muon>>
    numTightMuons(&(tightMuons.ptrToItems), "numTightMuons");
  kinVars.push_back(&numTightMuons);

  GenericCollectionSizeVariable<std::vector<pat::Electron>>
    numTightElectrons(&(tightElectrons.ptrToItems), "numTightElectrons");
  kinVars.push_back(&numTightElectrons);

  GenericCollectionSizeVariable<std::vector<pat::Electron>>
    numCernElectrons(&(cernElectrons.ptrToItems), "numCernElectrons");
  kinVars.push_back(&numCernElectrons);

  GenericCollectionSizeVariable<std::vector<pat::Jet>>
    numJets(&(jets.ptrToItems), "numJets");
  kinVars.push_back(&numJets);

  GenericCollectionSizeVariable<std::vector<reco::LeafCandidate>>
    numTightLeptons(&(tightLeptons.ptrToItems), "numTightLeptons");
  kinVars.push_back(&numTightLeptons);

  GenericCollectionSizeVariable<std::vector<reco::LeafCandidate>>
    numLooseLeptons(&(tightLooseLeptons.ptrToItems), "numTightLooseLeptons");
  kinVars.push_back(&numLooseLeptons);

  GenericCollectionSizeVariable<std::vector<reco::LeafCandidate>>
    numPreselectedLeptons(&(tightLoosePreselectedLeptons.ptrToItems), "numPreselectedLeptons");
  kinVars.push_back(&numPreselectedLeptons);

  GenericCollectionSizeVariable<std::vector<reco::LeafCandidate>>
    numCernLeptons(&(cernLeptons.ptrToItems), "numCernLeptons");
  kinVars.push_back(&numCernLeptons);
  
  ///////////// Two Object Kinematic Variables ////////////////

  // TwoObjectKinematic<std::vector<reco::LeafCandidate>,std::vector<reco::LeafCandidate>>
  //   myMassLepLep("mass", "min", "mass_leplep",
  // 		 &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 99,
  // 		 &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 99);
  // kinVars.push_back(&myMassLepLep);
  
  // TwoObjectKinematic<std::vector<reco::LeafCandidate>,std::vector<reco::LeafCandidate>>
  //   myZmass("mass", "closest_to", "Zmass",
  // 	    &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 99,
  // 	    &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 99,
  // 	    91.2, "same_flavour");
  // kinVars.push_back(&myZmass);

  // TwoObjectKinematic<std::vector<reco::LeafCandidate>,std::vector<reco::LeafCandidate>>
  //   myDeltaRLepLep("deltaR", "min", "dR_leplep",
  // 		   &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 99,
  // 		   &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 99);
  // kinVars.push_back(&myDeltaRLepLep);


  // TwoObjectKinematic<std::vector<reco::LeafCandidate>,std::vector<reco::LeafCandidate>>
  //   myDeltaPhiLepLep("deltaPhi", "min", "dPhi_leplep",
  // 		     &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 99,
  // 		     &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 99);
  // kinVars.push_back(&myDeltaPhiLepLep);


  // TwoObjectKinematic<std::vector<pat::Jet>,std::vector<pat::Jet>>
  //   myMinDrJets("deltaR", "min", "min_dr_jets",
  // 		&(jets.ptrToItems), "jets_by_pt", 1, 99,
  // 		&(jets.ptrToItems), "jets_by_pt", 1, 99);
  // kinVars.push_back(&myMinDrJets);

  // TwoObjectKinematic<std::vector<reco::LeafCandidate>,std::vector<pat::Jet>>
  //   mySumPt("pt", "sum", "sum_pt",
  // 	    &(tightLooseLeptons.ptrToItems), "leptons_by_pt", 1, 99,
  // 	    &(jets.ptrToItems), "jets_by_pt", 1, 99);
  // kinVars.push_back(&mySumPt);

  // TwoObjectKinematic<std::vector<pat::Jet>,std::vector<pat::Jet>>
  //   mySumJetPt("pt", "sum", "sum_jet_pt",
  // 	       &(jets.ptrToItems), "jets_by_pt", 1, 99,
  // 	       &(jets.ptrToItems), "jets_by_pt", 1, 99);
  // kinVars.push_back(&mySumJetPt);

  // TwoObjectKinematic<std::vector<pat::Jet>,std::vector<pat::Jet>>
  //   mySumJetMass("mass", "vector_sum", "sum_jet_mass",
  // 		 &(jets.ptrToItems), "jets_by_pt", 1, 99,
  // 		 &(jets.ptrToItems), "jets_by_pt", 1, 99);
  // kinVars.push_back(&mySumJetMass);

  // TwoObjectKinematic<std::vector<pat::Jet>,std::vector<pat::Jet>>
  //   myHiggsLikeDijetMass("mass", "closest_to", "higgsLike_dijet_mass",
  // 			 &(jets.ptrToItems), "jets_by_pt", 1, 99,
  // 			 &(jets.ptrToItems), "jets_by_pt", 1, 99,
  // 			 115.0);
  // kinVars.push_back(&myHiggsLikeDijetMass);
  
  // TwoObjectKinematic<std::vector<pat::Jet>,std::vector<pat::Jet>>
  //   myHiggsLikeDijetMass2("mass", "second_closest_to", "higgsLike_dijet_mass2",
  // 			  &(jets.ptrToItems), "jets_by_pt", 1, 99,
  // 			  &(jets.ptrToItems), "jets_by_pt", 1, 99,
  // 			  115.0);
  // kinVars.push_back(&myHiggsLikeDijetMass2);

  //////// INVESTIGATION VARIABLES //////////////////

  // minDr_leplep<std::vector<pat::PackedGenParticle>,std::vector<reco::LeafCandidate>>
  //   cernLeptonMotherId(&(genLeptons.ptrToItems),&(cernLeptons.ptrToItems),"cern_");
  // kinVars.push_back(&cernLeptonMotherId);

  // minDr_leplep<std::vector<pat::PackedGenParticle>,std::vector<reco::LeafCandidate>>
  //   tightLeptonMotherId(&(genLeptons.ptrToItems),&(tightLeptons.ptrToItems),"tight_");
  // kinVars.push_back(&tightLeptonMotherId);

  // minDr_leplep<std::vector<pat::PackedGenParticle>,std::vector<reco::LeafCandidate>>
  //   looseLeptonMotherId(&(genLeptons.ptrToItems),&(tightLooseLeptons.ptrToItems),"loose_");
  // kinVars.push_back(&looseLeptonMotherId);

  // minDr_leplep<std::vector<pat::PackedGenParticle>,std::vector<reco::LeafCandidate>>
  //   tightLoosePreselectedLeptonMotherId(&(genLeptons.ptrToItems),&(tightLoosePreselectedLeptons.ptrToItems),"tightLoosePreselected_");
  // kinVars.push_back(&tightLoosePreselectedLeptonMotherId);

  // minDr_leplep_dxyz<std::vector<reco::LeafCandidate>,std::vector<pat::Muon>,std::vector<pat::Electron>,std::vector<reco::Vertex>>
  //   dxyz(&(tightLoosePreselectedLeptons.ptrToItems),&(tightLoosePreselectedMuons.ptrToItems),&(tightLoosePreselectedElectrons.ptrToItems),&(primaryVertices.ptrToItems),"tightLoosePreselected");
  // kinVars.push_back(&dxyz);

  // // minDr_leplep2<std::vector<reco::LeafCandidate>,std::vector<reco::LeafCandidate>>
  // //   leptonIds(&(tightLooseLeptons.ptrToItems),&(tightLooseLeptons.ptrToItems),"lepton1","lepton2","_pdgId");
  // // kinVars.push_back(&leptonIds);

  // // minDr_leplep2<std::vector<reco::LeafCandidate>,std::vector<reco::LeafCandidate>>
  // //   leptonPts(&(tightLooseLeptons.ptrToItems),&(tightLooseLeptons.ptrToItems),"lepton1","lepton2","_pTs");
  // // kinVars.push_back(&leptonPts);

  // // minDr_leplep2<std::vector<reco::LeafCandidate>,std::vector<reco::LeafCandidate>>
  // //   leptonPhi(&(tightLooseLeptons.ptrToItems),&(tightLooseLeptons.ptrToItems),"lepton1","lepton2","_phi");
  // // kinVars.push_back(&leptonPhi);

  // // minDr_leplep3<std::vector<reco::LeafCandidate>,std::vector<reco::LeafCandidate>>
  // //   customDeltaPhiLepLep(&(tightLooseLeptons.ptrToItems),&(tightLooseLeptons.ptrToItems),"dPhi_leplep_custom");
  // // kinVars.push_back(&customDeltaPhiLepLep);

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
  
  //vars for vertex loop
  reco::Vertex vertex;
  double minNDOF = 4.0;
  double maxAbsZ = 24.0;
  double maxd0 = 2.;
  int numpv = 0;

  for (ev.toBegin(); !ev.atEnd(); ++ev){
    numEvents++;

    if ((numEvents > myConfig.maxEvents) && myConfig.maxEvents != -1) break;

    if (numEvents == 1 || numEvents % printEvery == 0 )
      cout << "Processing event.... " << numEvents << endl;

    if (debug > 9) cout << "---------->>>>>> Event " << numEvents << endl;
    ////////////////////////////////////////////////////////////
    //
    // count pvs for miniAODhelper
    //
    ////////////////////////////////////////////////////////////
    primaryVertices.initializeRawItems(ev,"offlineSlimmedPrimaryVertices");
    numpv = 0;
    for (reco::VertexCollection::const_iterator iPV = primaryVertices.ptrToItems->begin(); iPV != primaryVertices.ptrToItems->end(); ++iPV){
      bool isGood = ( !(iPV->isFake()) &&
		     (iPV->ndof() >= minNDOF) &&
		     (abs(iPV->z()) <= maxAbsZ) &&
		     (abs(iPV->position().Rho()) <= maxd0)
		     );
      if ( !isGood ) continue;
      if ( numpv == 0 ) vertex = *iPV;
      numpv++;
    }
    
    //cout << "numpv = " << numpv << endl;
    if ( numpv > 0 ){
      //cout << "setting vertex, numpv > 0" << endl;
      miniAODhelper->SetVertex(vertex);
    }
    ///define weights here
    //evt_wgts.initializeRawWgtItems(ev,"generator");


    /////////////////////////////////////////////////////////////
    //
    //    Initialize collections and apply object ids
    //
    //////////////////////////////////////////////////////////////   
    
    //object IDs
    
    //preselected muons

    tightLoosePreselectedElectrons.initializeRawItemsSortedByPt(ev,"slimmedElectrons");
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
    
    cernElectrons.initializeRawItemsSortedByPt(ev,"slimmedElectrons");
    cernElectrons.keepSelectedParticles(electronCernID);
    auto eleMvaNonTrigID = [&] (pat::Electron p) { 
      bool useFull5x5 = true;
      bool mvaDebug = false;
      double eleMvaNonTrig = mvaID_->mvaValue(p,vertex,rho,useFull5x5,mvaDebug);
      bool passesMVA = false;
      if ( p.pt() < 10 ){
	if ( abs(p.eta()) > 0. && abs(p.eta()) < 0.8){
	  passesMVA = ( eleMvaNonTrig > 0.47 );
	}
	else if ( abs(p.eta()) >= 0.8 && abs(p.eta()) < 1.479){
	  passesMVA = ( eleMvaNonTrig > 0.004 );
	}
	else if ( abs(p.eta()) >= 1.479 && abs(p.eta()) <= 2.5){
	  passesMVA = ( eleMvaNonTrig > 0.295 );
	}
	
      }
      else if ( p.pt() >= 10 ) {
	if ( abs(p.eta()) > 0. && abs(p.eta()) < 0.8){
	  passesMVA = ( eleMvaNonTrig > 0.34 );
	}
	else if ( abs(p.eta()) >= 0.8 && abs(p.eta()) < 1.479){
	  passesMVA = ( eleMvaNonTrig > -065 );
	}
	else if ( abs(p.eta()) >= 1.479 && abs(p.eta()) <= 2.5){
	  passesMVA = ( eleMvaNonTrig > 0.60 );
	}
	
      }

      return ( passesMVA );
    };
    cernElectrons.keepSelectedParticles(eleMvaNonTrigID);
    

    tightLoosePreselectedMuons.initializeRawItemsSortedByPt(ev, "slimmedMuons");
    tightLoosePreselectedMuons.keepSelectedParticles(muonPreselectedID);
    tightMuons.initializeRawItems(tightLoosePreselectedMuons.rawItems);
    tightMuons.keepSelectedParticles(muonTightID);
    
    tightLooseMuons.initializeRawItems(tightLoosePreselectedMuons.rawItems);
    tightLooseMuons.keepSelectedParticles(muonLooseID);
    
    looseMuons.initializeRawItems(tightLoosePreselectedMuons.rawItems);
    looseMuons.keepSelectedDifference(muonLooseID, muonTightID);
    preselectedMuons.initializeRawItems(tightLoosePreselectedMuons.rawItems);
    preselectedMuons.keepSelectedDifference(muonPreselectedID, muonLooseID);

    cernMuons.initializeRawItemsSortedByPt(ev, "slimmedMuons");
    cernMuons.keepSelectedParticles(muonCernID);
    
    tightTaus.initializeRawItemsSortedByPt(ev, "slimmedTaus");
    tightTaus.keepSelectedParticles(tauTightID);
    tightLooseTaus.initializeRawItems(tightTaus.rawItems);
    tightLooseTaus.keepSelectedParticles(tauTightID);
    tightLoosePreselectedTaus.initializeRawItems(tightTaus.rawItems);
    tightLoosePreselectedTaus.keepSelectedParticles(tauPreselectedID);

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
    
    cernLeptons.resetAndPushBack(cernElectrons.items);
    cernLeptons.pushBackAndSort(cernMuons.items);

    jets.initializeRawItemsSortedByPt(ev, "slimmedJets");
    jets.cleanJets(tightLoosePreselectedMuons.items);
    jets.cleanJets(tightLoosePreselectedElectrons.items);

    jets.keepSelectedJets(30.0, 2.4, jetID::jetLoose, '-');
    jetsByCSV.initializeRawItemsSortedByCSV(jets.items);

    jets_30.initializeRawItems(jets.items);
    jets_30.keepSelectedJets(30.0, 2.4, jetID::jetLoose, '-');

    /////////   aMC@NLO negative event weights   //////////////
    fwlite::Handle<GenEventInfoProduct> GenInfo;
    GenInfo.getByLabel(ev,"generator");
    wgt = GenInfo->weight();

    genTopParticles.initializeRawItems(ev,"prunedGenParticles");
    auto topPDGID = [] (reco::GenParticle p) { return (p.pdgId() == 6 ); };
    genTopParticles.keepSelectedParticles(topPDGID);

    genHiggsParticles.initializeRawItems(ev,"prunedGenParticles");
    auto higgsPDGID = [] (reco::GenParticle p) { return (p.pdgId() == 25 ); };
    genHiggsParticles.keepSelectedParticles(higgsPDGID);

    genLeptons.initializeRawItems(ev,"packedGenParticles");
    auto leptonPDGID = [] (pat::PackedGenParticle p) { return (abs(p.pdgId()) == 13 || abs(p.pdgId()) == 11 ); };
    auto leptonPt = [] (pat::PackedGenParticle p) { return (p.pt() >= 10 ); };
    genLeptons.keepSelectedParticles(leptonPDGID);
    genLeptons.keepSelectedParticles(leptonPt);

    // genElectrons.initializeRawItems(ev,"packedGenParticles");
    // auto electronPDGID = [] (pat::PackedGenParticle p) { return (abs(p.pdgId()) == 11 ); };
    // auto electronPt = [] (pat::PackedGenParticle p) { return (p.pt() >= 10. ); };
    // genElectrons.keepSelectedParticles(electronPDGID);
    // genElectrons.keepSelectedParticles(electronPt);

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












