// MultileptonAna base class: to be inherited by the EDAnalyzers for the individual channels
// created Oct. 9 2014
// Geoff Smith
// 
// 
// -----------------------------------------------
// begin includes

// Root, etc.

#include <cstdlib>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <boost/any.hpp>

#include <iostream>
#include <algorithm>
#include <exception>
#include <cmath> 
#include <iomanip>
#include <fstream>
#include <sstream>

#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
#include <TRandom3.h>
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TH2D.h"
#include "TVector.h"
#include "TLorentzVector.h"

// Framework
#include "FWCore/ParameterSet/interface/ProcessDesc.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/PythonParameterSet/interface/PythonProcessDesc.h"

// Physics
#include "Math/LorentzVector.h"
#include "DataFormats/Math/interface/LorentzVectorFwd.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/GenericParticle.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "PhysicsTools/SelectorUtils/interface/JetIDSelectionFunctor.h"
#include "PhysicsTools/SelectorUtils/interface/strbitset.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/JetReco/interface/PileupJetIdentifier.h"

//JEC
#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"

// Trigger
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/HLTReco/interface/TriggerEventWithRefs.h"
#include "DataFormats/HLTReco/interface/TriggerTypeDefs.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "HLTrigger/HLTcore/interface/HLTPrescaleProvider.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"

// MiniAOD
#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"

// Multilepton
#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/JobParameters.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/src/classes.h"

// end includes
// -----------------------------------------------

// may or may not want these:
//using namespace edm;
//using namespace trigger;
//using namespace std;

typedef math::XYZTLorentzVectorD 		TLorentzVectorCMS;
typedef std::vector< math::XYZTLorentzVectorD >	vecTLorentzVectorCMS;
typedef std::vector< TLorentzVector >          	vecTLorentzVector;
typedef std::vector<int>                       	vint;
typedef std::vector<double>                    	vdouble;
typedef std::vector<std::vector<double> > 	vvdouble;
typedef std::vector<std::string> 		vstring;

//typedef edm::Handle<pat::JetCollection>		patJets;
typedef edm::Handle<pat::METCollection>		patMETs;
typedef edm::Handle<reco::GenParticleCollection> prunedGenParticles;
typedef edm::Handle<pat::PackedGenParticleCollection> packedGenParticles;
typedef edm::Handle<pat::PackedCandidateCollection> patPackedCands;

typedef edm::Handle<std::vector< PileupSummaryInfo > > 	pileupInfo;
typedef edm::Handle<edm::TriggerResults>	trigRes;

typedef std::vector<pat::Muon>	     vecPatMuon;
typedef std::vector<pat::Electron>   vecPatElectron;
typedef std::vector<reco::LeafCandidate> vecPatLepton;
typedef std::vector<pat::Tau>        vecPatTau;
typedef std::vector<pat::Jet>	     vecPatJet;
typedef std::vector<pat::MET>	     vecPatMET;


class MultileptonAna: public MiniAODHelper
{
 protected:
  
  bool isData;
  string sampleName;
  int sampleNumber;
  bool debug;
  bool jetCleanFakeable;
  bool skim;
  int eventcount;
  
  void detectData(string sampleName);
  
  int convertSampleNameToNumber(string sampleName);
  
  edm::ParameterSet entire_pset;
  edm::ParameterSet setupoptionsparams;
  edm::ParameterSet triggerparams;
  edm::ParameterSet jetparams;
  edm::ParameterSet subjetparams;
  edm::ParameterSet btagparams;
  edm::ParameterSet prunedparams;
  edm::ParameterSet packedparams;
  edm::ParameterSet metparams;
  edm::ParameterSet variableparams;
  edm::ParameterSet systparams;
  edm::ParameterSet selectionparams;
  
  // bullshit:
  edm::EDGetTokenT<edm::TriggerResults> triggerResults_token_;
  edm::EDGetTokenT<pat::JetCollection> jets_token_;
  edm::EDGetTokenT<pat::METCollection> mets_token_;
  edm::EDGetTokenT<reco::GenParticleCollection> genParticles_token_;
  edm::EDGetTokenT<pat::PackedGenParticleCollection> genPackedParticles_token_;
  edm::EDGetTokenT<reco::VertexCollection> vertex_token_;
  edm::EDGetTokenT<double> rho_token_;
  edm::EDGetTokenT<GenEventInfoProduct> genInfo_token_;
  edm::EDGetTokenT<edm::ValueMap<float>> qg_token_;
  edm::EDGetTokenT<std::vector<reco::GenJet>> genJet_token_;
  edm::EDGetTokenT<int> badmu_token_;


  void parse_params();
  
  //MiniAODHelper miniAODhelper;
  
  double rho;
  
  HLTConfigProvider hltConfig_;
  std::string hltTag;	
  
 public:
  
  MultileptonAna();
  //virtual ~MultileptonAna() noexcept (false);
  ~MultileptonAna();
  
  string analysisYear = "2015_72x"; // "2015_73x, 2015_74x ..."
		
  vector<ttH::Lepton> GetCollection(vector<ttH::Muon> muObjs, vector<ttH::Electron> eleObjs);
  vector<ttH::Electron> GetCollection(vecPatElectron theobjs);
  vector<ttH::Muon> GetCollection(vecPatMuon theobjs);
  vector<ttH::Tau> GetCollection(vecPatTau theobjs);
  vector<ttH::Jet> GetCollection(vecPatJet theobjs);
  vector<ttH::GenParticle> GetCollection(std::vector<reco::GenJet> theobjs);
  vector<ttH::MET> GetCollection(edm::Handle<pat::METCollection> theobjs);
  //  vector<ttH::GenParticle> GetCollection(std::vector<reco::GenParticle> theobjs);
  template <typename templateGenParticle> vector<ttH::GenParticle> GetCollection(std::vector<templateGenParticle> theobjs);
  template <typename T> edm::Handle<T> get_collection(const edm::Event& event, const edm::EDGetTokenT<T>& token);

  vecPatLepton fillLeptons(const vecPatMuon& mus, const vecPatElectron& eles);

  void SetupOptions(const edm::Event& event);
  trigRes GetTriggers(const edm::Event& event);
  int GetVertices (const edm::Event& event);
  void Systematics(const edm::Event& event);
  void EventSelection(const edm::Event& event);
  vstring HLTInfo ();

  const reco::Candidate* GetGenMotherNoFsr(const reco::Candidate* theobj);
  std::pair<const reco::Candidate*, const reco::Candidate*> GetGenDaughterNoFsr(const reco::Candidate* theobj);

  // replace virtual members from inherited miniAODhelper:
  std::vector<pat::Muon> GetSelectedMuons(const std::vector<pat::Muon>&, const float, const muonID::muonID);
  std::vector<pat::Electron> GetSelectedElectrons(const std::vector<pat::Electron>&, const float, const electronID::electronID);
  std::vector<pat::Tau> GetSelectedTaus(const std::vector<pat::Tau>&, const float, const tauID::tauID);
  int GetHiggsDaughterId(const std::vector<reco::GenParticle>&);
  template <typename obj1, typename obj2> std::vector<obj1> cleanObjects(const std::vector<obj1>&, const std::vector<obj2>&, const double);
  template <typename particleType> pat::Jet getClosestJet(const std::vector<pat::Jet>&, const particleType&);

  
};

template <typename obj1, typename obj2> std::vector<obj1> MultileptonAna::cleanObjects(const std::vector<obj1>& dirtyCollection,const std::vector<obj2>& soapCollection,const double coneSize)
{
  std::vector<obj1> cleanedCollection;
  bool isClean;
  for (typename std::vector<obj1>::const_iterator dirtObj = dirtyCollection.begin(); dirtObj != dirtyCollection.end(); dirtObj++)
    {
      isClean = true;
      for (typename std::vector<obj2>::const_iterator soapObj = soapCollection.begin(); soapObj != soapCollection.end(); soapObj++)
        {
          if (MiniAODHelper::DeltaR(dirtObj,soapObj) <= coneSize )
            {
              isClean = false;
              break;
            }
        }
      if (isClean)
        {
          obj1 cleanedObj = (*dirtObj);
          cleanedCollection.push_back(cleanedObj);
        }
    }
  
  return cleanedCollection;
}

template <typename particleType>
pat::Jet MultileptonAna::getClosestJet(const std::vector<pat::Jet>& jets, const particleType& object) {
  pat::Jet result;
  double minDeltaR = 999;
  //  for (auto& jet: jets) {
  for (std::vector<pat::Jet>::const_iterator iJet = jets.begin(); iJet != jets.end(); iJet++)
    {
      double dR = MiniAODHelper::DeltaR(iJet, &object);
      if (dR < minDeltaR)
	{
	  minDeltaR = dR;
	  result = (*iJet);
	}
    }
  return result;
}

template <typename templateGenParticle> std::vector<ttH::GenParticle> MultileptonAna::GetCollection (std::vector<templateGenParticle> theobjs)
{
  ttH::GenParticle genParticle;
  std::vector<ttH::GenParticle> theGenParticles;
  std::vector<templateGenParticle> theFinalGenParticles;
  const reco::Candidate* child0;
  const reco::Candidate* child1;
  const reco::Candidate* mother;
  const reco::Candidate* grandMother;
  std::pair<const reco::Candidate*, const reco::Candidate*> childPair;

  unsigned int i = 0;
  for (const auto & iGenParticle: theobjs)
    {
      genParticle.obj = iGenParticle.p4();
      genParticle.pdgID = iGenParticle.pdgId();
      genParticle.status = iGenParticle.status();      
      genParticle.charge = iGenParticle.charge();      
      genParticle.isPromptFinalState = iGenParticle.isPromptFinalState();
      genParticle.isDirectPromptTauDecayProductFinalState = iGenParticle.isDirectPromptTauDecayProductFinalState();
      
      theGenParticles.push_back(genParticle);
      i+=1;
    }
  
  i=0;
  for (const auto & iGenParticle : theobjs)
    {
      childPair = GetGenDaughterNoFsr(&iGenParticle);
      child0 = childPair.first;
      child1 = childPair.second;
      
      mother = GetGenMotherNoFsr(&iGenParticle);
      grandMother = GetGenMotherNoFsr(mother);

      unsigned int j =0;
      for (const auto & customGenParticle : theGenParticles)
	{
	  if (child0->pdgId() != iGenParticle.pdgId() && child0->pt() == (float)customGenParticle.obj.Pt())
	    {	 
	      if (child0->status() == customGenParticle.status) theGenParticles[i].child0 = j;
	    } 
	  else if (child1->pdgId() != iGenParticle.pdgId() && child1->pt() == (float)customGenParticle.obj.Pt())
	    {
	      if (child1->status() == customGenParticle.status) theGenParticles[i].child1 = j;
	    }
	  else if (mother->pdgId() != iGenParticle.pdgId() && mother->pt() == (float)customGenParticle.obj.Pt())
	    {
	      if (mother->status() == customGenParticle.status) theGenParticles[i].mother = j;
	    }
	  else if (grandMother->pdgId() != iGenParticle.pdgId() && grandMother->pt() == (float)customGenParticle.obj.Pt())
	    {
	      if (grandMother->status() == customGenParticle.status) theGenParticles[i].grandmother = j;
	    }

	  if (theGenParticles[i].child0 != 9999 && theGenParticles[i].child1 != 9999 && theGenParticles[i].mother != 9999 && theGenParticles[i].grandmother != 9999) break;
	  j+=1;
	}
      i+=1;
    }
  return theGenParticles;
 }

template<typename T>
edm::Handle<T>
MultileptonAna::get_collection(const edm::Event& event, const edm::EDGetTokenT<T>& token)
{
  edm::Handle<T> handle;
  event.getByToken(token, handle);
  if (!handle.isValid())
    throw edm::Exception(edm::errors::InvalidReference, "Can't find a collection.");
  return handle;
}
