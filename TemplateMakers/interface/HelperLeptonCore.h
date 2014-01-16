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
#include <TRandom3.h>

#if !defined(__CINT__) && !defined(__MAKECINT__)

#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/FWLite/interface/ChainEvent.h"

#include "FWCore/Framework/interface/Event.h"

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

#include "BEAN/BEANmaker/interface/BtagWeight.h"
#include "BEAN/BEANmaker/interface/BEANhelper.h"

#include "BEAN/BEANmaker/interface/AnglesUtil.h"
#include "PhysicsTools/Utilities/interface/LumiReweightingStandAlone.h"

#endif

#include "ttHMultileptonAnalysis/TemplateMakers/interface/BEANFileInterface.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/KinematicVariable.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/TwoObjectKinematic.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/GenericCollectionMember.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/JobParameters.h"

class HelperLeptonCore  {
public:
  HelperLeptonCore();

  BEANhelper * setupAnalysisParameters(string year, string sampleName); // initialize
  void detectData(string sampleName);
  int convertSampleNameToNumber(string sampleName);
  void initializePUReweighting(); // setup some PU reweighting flags
  void initializeInputCollections(edm::EventBase&, bool, BEANFileInterface&);

  // Handle the gymnastics of tight and loose collection definitions
  void getTightLoosePreselectedElectrons(electronID::electronID tightID,
                                         electronID::electronID looseID,
                                         electronID::electronID preselectedID,
                                         BEANFileInterface* selectedCollections);

  void getTightLoosePreselectedMuons(muonID::muonID tightID,
                                     muonID::muonID looseID,
                                     muonID::muonID preselectedID,
                                     BEANFileInterface* selectedCollections);

  void getTightCorrectedJets(double ptCut,
                             double etaCut,
                             jetID::jetID tightID,
                             BEANFileInterface* selectedCollections);

  BNjetCollection * getCorrectedSelectedJets(double ptCut,
                                             double etaCut,
                                             jetID::jetID jetID,
                                             const char csvWorkingPoint);

  void getCorrectedMet(BEANFileInterface * selectedCollections,
                       sysType::sysType shift = sysType::NA);

  void fillLepCollectionWithSelectedLeptons(BEANFileInterface * selectedCollections);
  void fillZLepCollectionWithSelectedLeptons(BEANFileInterface * selectedCollections,
                                             TwoObjectKinematic<BNleptonCollection,BNleptonCollection> * myZLikeMassLepLepSFOS_tight,
                                             TwoObjectKinematic<BNleptonCollection,BNleptonCollection> * myZLikeMassLepLepSFOS_tightLoose,
                                             TwoObjectKinematic<BNleptonCollection,BNleptonCollection> * myZLikeMassLepLepSFOS_all);

  bool isFromB(BNmcparticle particle);

  double scaleIPVarsMC(double ipvar, int pdgId, double pt, double eta, int mcMatchId, int mcMatchAny);
  double scaleSIPMC(double& sip, int& genID, double& pt, int& mcMatchID, int& mcMatchAny, double& eta);
  double scaleDZMC(double dz, int genID, double pt, double eta, int mcMatchID, int mcMatchAny);
  double scaleDXYMC(double dxy, int genID, double pt, double eta, int mcMatchID, int mcMatchAny);
  double scaleLepJetPtRatioMC(double jetPtRatio, int genID, double pt, double eta, int mcMatchID, int mcMatchAny);
  double scaleLepJetDRMC(double jetDR, int genID, double pt, double eta, int mcMatchID, int mcMatchAny);

  template <typename collectionType> void fillMCMatchID(collectionType& collection, const double& maxDR);
  template <typename collectionType> void fillMCMatchAny(collectionType& collection, const double& maxDR);
  template <typename collectionType> void fillSIP(collectionType& collection, bool applySmearing);
  template <typename collectionType> void fillLepJetPtRatio(collectionType& collection, BNjetCollection& jetCollection, bool applySmearing);
  template <typename collectionType> void fillLepJetDeltaR(collectionType& collection, BNjetCollection& jetCollection, bool applySmearing);
  template <typename collectionType> void fillLepJetBTagCSV(collectionType& collection, BNjetCollection& jetCollection);
  template <typename collectionType> void scaleMCCollectionDZ(collectionType& collection);
  template <typename collectionType> void scaleMCCollectionDXY(collectionType& collection);
  template <typename particleType> bool isPlausible(particleType particle, const BNmcparticle& mcParticle);
  template <typename particleType> BNmcparticleCollection getPlausibleParticles(particleType& particle, BNmcparticleCollection * mcParticles);

  TRandom *gSmearer;

  //-------------------- Variables
  std::string analysisYear;

  double weight_Xsec;
  int nGen;
  float Xsec;
  int sampleNumber;
  string sampleName;

  bool isData;
  string dataset;

  sysType::sysType jetEnergyShift;
  sysType::sysType csvShift;

  BEANhelper bHelp;
  BEANFileInterface rawCollections;

  JobParameters config;

  bool verbose;

  std::string listOfCollisionDatasets;
  std::string datasetForBEANHelper;

  edm::Handle<BNeventCollection> h_event;
  BNeventCollection events;

  edm::Handle<BNmuonCollection> h_muons;
  BNmuonCollection muonsRaw;
  BNmuonCollection muonsTight;
  BNmuonCollection muonsLoose;
  BNmuonCollection muonsPreselected;
  BNmuonCollection muonsTightLoose;
  BNmuonCollection muonsLoosePreselected;
  BNmuonCollection muonsTightLoosePreselected;

  edm::Handle<BNmcparticleCollection> h_mcparticles;
  BNmcparticleCollection mcparticles;

  edm::Handle<BNjetCollection> h_pfjets;
  BNjetCollection sortedCorrSelJets;
  BNjetCollection pfjets;
  BNjetCollection jetsTight;
  BNjetCollection jetsLooseCSV;
  BNjetCollection jetsTightCSV;
  BNjetCollection jetsNotLooseCSV;
  BNjetCollection jetsNotMediumCSV;
  BNjetCollection jetsNotTightCSV;
  BNjetCollection jetsMediumCSV;

  edm::Handle<BNmetCollection> h_pfmets;
  BNmetCollection pfmets;
  BNmetCollection metCorrected;

  edm::Handle<BNtriggerCollection> h_hlt;
  BNtriggerCollection hltInfo;

  edm::Handle<BNprimaryvertexCollection> h_pvs;
  BNprimaryvertexCollection pvs;

  edm::Handle<BNelectronCollection> h_electrons;
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
  BNleptonCollection leptonsTightZ;
  BNleptonCollection leptonsTightNonZ;
  BNleptonCollection leptonsTightLooseZ;
  BNleptonCollection leptonsTightLooseNonZ;
  BNleptonCollection leptonsTightLoosePreselectedZ;
  BNleptonCollection leptonsTightLoosePreselectedNonZ;

  edm::Handle<BNjetCollection> h_lepMvaJets;
  BNjetCollection lepMvaJets;

//-------------------- Inline functions
  inline double smearMC(TRandom* gSmearer, double x, double mu, double sigma) {
    if (x == 0) return gSmearer->Gaus(mu,sigma);
    else return (x/abs(x))*(abs(x) + gSmearer->Gaus(mu,sigma));
  }
  inline double logSmearMC(TRandom* gSmearer, double x, double mu, double sigma) {
    if (x == 0) return std::exp(gSmearer->Gaus(mu,sigma));
    else return (x/abs(x))*std::exp(std::log(abs(x)) + gSmearer->Gaus(mu,sigma));
  }
  inline double shiftMC(double x, double delta) {
    if (x == 0) return delta;
    else return (x/abs(x))*(abs(x) + delta);
  }
  inline double scaleShiftMC(double x, double scale, double shift) {
    if (x == 0) return shift;
    else return (x/abs(x))*(abs(x)*scale + shift);
  }
  
};

//-------------------- Template functions
template <typename collectionType>
void HelperLeptonCore::fillMCMatchID(collectionType& collection, const double& maxDR) {
  BNmcparticleCollection plausibleParticles;
  BNmcparticle matchedParticle;

  for (auto& object: collection) {
    plausibleParticles = getPlausibleParticles(object, rawCollections.mcParticleCollection);
    matchedParticle = bHelp.GetMatchedMCparticle(plausibleParticles, object, maxDR);
    object.mcMatchID = matchedParticle.id;
  }
}

template <typename collectionType>
void HelperLeptonCore::fillMCMatchAny(collectionType& collection, const double& maxDR) {
  BNmcparticleCollection plausibleParticles;
  BNmcparticle matchedParticle;

  for (auto& object: collection) {
    plausibleParticles = getPlausibleParticles(object, rawCollections.mcParticleCollection);
    matchedParticle = bHelp.GetMatchedMCparticle(plausibleParticles, object, maxDR);
    object.mcMatchAny = 1 + int(isFromB(matchedParticle));
  }
}

template <typename particleType>
BNmcparticleCollection HelperLeptonCore::getPlausibleParticles(particleType& particle, BNmcparticleCollection * mcParticles) {
  BNmcparticleCollection plausibleParticles;

  for (auto mcParticle: *mcParticles) {
    if (isPlausible(particle, mcParticle)) plausibleParticles.push_back(mcParticle);
  }
  return plausibleParticles;
}

template <typename particleType>
bool HelperLeptonCore::isPlausible(particleType particle, const BNmcparticle& mcParticle) {
  if ((abs(particle.genId) == 11) && (abs(mcParticle.id != 11))) return false;
  if ((abs(particle.genId) == 13) && (abs(mcParticle.id != 13))) return false;
  double dR = deltaR(particle.eta, particle.phi, mcParticle.eta, mcParticle.phi);
  if (dR < 0.3) return true;
  if ((particle.pt < 10) && (abs(particle.genId) == 13) && (mcParticle.id != particle.genId)) return false;
  if (dR<0.7) return true;
  if (min(particle.pt, mcParticle.pt) / max(particle.pt, mcParticle.pt) < 0.3) return false;
  return true;
}

template <typename collectionType>
void HelperLeptonCore::fillSIP(collectionType& collection, bool applySmearing) {
  double sip = -99.0;
  for (auto& object: collection) {
    if (object.IP != -99 && object.IPError != -99) sip = object.IP / object.IPError;
    if (applySmearing) sip = scaleSIPMC(sip, object.genId, object.pt, object.mcMatchID, object.mcMatchAny, object.eta);
    object.SIP = sip;
  }
}

template <typename collectionType>
void HelperLeptonCore::fillLepJetBTagCSV(collectionType& collection, BNjetCollection& jetCollection) {
  double jetBTagCSV = 0.0;
  BNjet matchedJet;

  for (auto& object: collection) {
    matchedJet = bHelp.GetClosestJet(jetCollection, object, 100.0);
    if (deltaR(object.eta, object.phi, matchedJet.eta, matchedJet.phi) <= 0.5) jetBTagCSV = max(matchedJet.btagCombinedSecVertex, 0.0);

    object.jetBTagCSV = jetBTagCSV;
  }
}

template <typename collectionType>
void HelperLeptonCore::fillLepJetPtRatio(collectionType& collection, BNjetCollection& jetCollection, bool applySmearing) {
  double jetPtRatio = 1.5;
  BNjet matchedJet;

  for (auto& object: collection) {
    matchedJet = bHelp.GetClosestJet(jetCollection, object, 100.0);
    if (deltaR(object.eta, object.phi, matchedJet.eta, matchedJet.phi) <= 0.5) jetPtRatio = min(object.pt/matchedJet.pt, 1.5);
    if (applySmearing) jetPtRatio = scaleLepJetPtRatioMC(jetPtRatio, object.genId, object.pt, object.eta, object.mcMatchID, object.mcMatchAny);

    object.jetPtRatio = jetPtRatio;
  }
}

template <typename collectionType>
void HelperLeptonCore::fillLepJetDeltaR(collectionType& collection, BNjetCollection& jetCollection, bool applySmearing) {
  double jetDeltaR = -99;
  BNjet matchedJet;

  for (auto& object: collection) {
    matchedJet = bHelp.GetClosestJet(jetCollection, object, 100.0);
    jetDeltaR = min(deltaR(object.eta, object.phi, matchedJet.eta, matchedJet.phi), 0.5);
    if (applySmearing) jetDeltaR = scaleLepJetDRMC(jetDeltaR, object.genId, object.pt, object.eta, object.mcMatchID, object.mcMatchAny);

    object.jetDeltaR = jetDeltaR;
  }
}

template <typename collectionType>
void HelperLeptonCore::scaleMCCollectionDZ(collectionType& collection) {
  double dz = -99.0;
  for (auto& object: collection) {
    dz = scaleDZMC(object.correctedDZ, object.genId, object.pt, object.eta, object.mcMatchID, object.mcMatchAny);
    object.correctedDZ = dz;
  }
}

template <typename collectionType>
void HelperLeptonCore::scaleMCCollectionDXY(collectionType& collection) {
  double dxy = -99.0;
  for (auto& object: collection) {
    dxy = scaleDXYMC(object.correctedD0Vertex, object.genId, object.pt, object.eta, object.mcMatchID, object.mcMatchAny);
    object.correctedD0Vertex = dxy;
  }
}

#endif // _HelperLeptonCore_h
