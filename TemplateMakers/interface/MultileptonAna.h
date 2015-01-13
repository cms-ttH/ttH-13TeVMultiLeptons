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

#include "Reflex/Object.h"
#include "Reflex/Type.h"
#include "Reflex/Member.h"
#include "Reflex/Kernel.h"


// Framework

//#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
#include "FWCore/ParameterSet/interface/ProcessDesc.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
//#include "FWCore/Framework/interface/Handle.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/PythonParameterSet/interface/PythonProcessDesc.h"


// Physics

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

// Trigger

#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/HLTReco/interface/TriggerEventWithRefs.h"
#include "DataFormats/HLTReco/interface/TriggerTypeDefs.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"


// MiniAOD

#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"


// Multilepton

#include "ttHMultileptonAnalysis/TemplateMakers/interface/GenericCollectionMember.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/GenericCollectionMethod.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/GenericCollectionSizeVariable2.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/GenericCollection.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/BTagDiscrim.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/TwoObjectKinematic.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/GenPt.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/JobParameters.h"

// hack for ele mva id
#include "ttHMultileptonAnalysis/TemplateMakers/interface/EGammaMvaEleEstimatorFWLite.h"

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

typedef edm::Handle<pat::MuonCollection>	patMuons;
typedef edm::Handle<pat::ElectronCollection>	patElectrons;


typedef edm::Handle<pat::JetCollection>		patJets;
typedef edm::Handle<pat::METCollection>		patMETs;
typedef edm::Handle<reco::GenParticleCollection> prunedGenParticles;

typedef edm::Handle<std::vector< PileupSummaryInfo > > 	pileupInfo;
typedef edm::Handle<edm::TriggerResults>	trigRes;

typedef edm::Handle<pat::Muon>		patMuon;
typedef edm::Handle<pat::Electron>	patElectron;
typedef edm::Handle<pat::Jet>		patJet;
typedef edm::Handle<pat::MET>		patMET;
typedef edm::Handle<reco::GenParticle>  prunedGenParticle;


typedef std::vector<pat::Muon>	     vecPatMuon;
typedef std::vector<pat::Electron>   vecPatElectron;
typedef std::vector<reco::LeafCandidate> vecPatLepton;
typedef std::vector<pat::Jet>	     vecPatJet;
typedef std::vector<pat::MET>	     vecPatMET;


typedef std::vector<pat::Jet>::const_iterator 		jetit;
typedef std::vector<pat::Muon>::const_iterator		muit;
typedef std::vector<pat::Electron>::const_iterator	eleit;
typedef std::vector<pat::MET>::const_iterator		metit;


class MultileptonAna: public MiniAODHelper
{
 protected:
  
  bool isData;
  string sampleName;
  int sampleNumber;
  bool debug;
  int eventcount;
  
  void detectData(string sampleName);
  
  EGammaMvaEleEstimatorFWLite* mvaID_;
  void setupMva();
  
  int convertSampleNameToNumber(string sampleName);
  
  edm::ParameterSet entire_pset;
  edm::ParameterSet setupoptionsparams;
  edm::ParameterSet triggerparams;
  edm::ParameterSet muonparams;
  edm::ParameterSet electronparams;
  edm::ParameterSet leptonparams;
  edm::ParameterSet jetparams;
  edm::ParameterSet subjetparams;
  edm::ParameterSet btagparams;
  edm::ParameterSet prunedparams;
  edm::ParameterSet metparams;
  edm::ParameterSet variableparams;
  edm::ParameterSet systparams;
  edm::ParameterSet selectionparams;

  void parse_params();
  
  //MiniAODHelper miniAODhelper;
  
  double rho;
  
  HLTConfigProvider hltConfig_;
  std::string hltTag;	
  
 public:
  
  MultileptonAna();
  ~MultileptonAna();
  
  string analysisYear = "2012_53x"; // "2015_74X"!
		
  electronID::electronID electronTightID;
  electronID::electronID electronLooseID;
  electronID::electronID electronPreselectedID;
  
  muonID::muonID muonTightID;
  muonID::muonID muonLooseID;
  muonID::muonID muonPreselectedID;
  
  tauID::tauID tauTightID;
  // tauID::tauID tauLooseID = tauID::tauVLoose;
  tauID::tauID tauPreselectedID;
  vector<ArbitraryVariable*> kinVars;
  vector<ArbitraryVariable*> cutVars;
  
  vecTLorentzVectorCMS Get_vecTLorentzVectorCMS (vecPatJet theobjs);
  vecTLorentzVectorCMS Get_vecTLorentzVectorCMS (vecPatMuon theobjs);
  vecTLorentzVectorCMS Get_vecTLorentzVectorCMS (vecPatElectron theobjs);
  TLorentzVectorCMS Get_TLorentzVectorCMS (patMETs theobjs);
  TLorentzVectorCMS Get_TLorentzVectorCMS (pat::MET theMET);
  vecTLorentzVectorCMS Get_vecTLorentzVectorCMS_sorted_leptons(vecTLorentzVectorCMS leps1, vecTLorentzVectorCMS leps2);
  vecPatLepton fillLeptons(vecPatMuon& mus, vecPatElectron& eles);

  void SetupOptions(const edm::Event& event);
  trigRes GetTriggers(const edm::Event& event);
  patMuons GetMuons(const edm::Event& event);
  patElectrons GetElectrons(const edm::Event& event); 
  patJets GetJets(const edm::Event& event);
  patJets GetSubJets(const edm::Event& event); 
  patMETs GetMet(const edm::Event& event);
  prunedGenParticles GetPrunedGenParticles(const edm::Event& event);
  int GetVertices (const edm::Event& event);
  void GetLeptons(const edm::Event& event);
  void GetBtags(const edm::Event& event);
  vector<double> ReturnBTagDisc (vecPatJet theobjs);
  //void Variables(const edm::Event& event); 
  void Systematics(const edm::Event& event);
  void EventSelection(const edm::Event& event);
  vstring HLTInfo ();
  vdouble Get_Isos(vecPatMuon theobjs);
  vdouble Get_Isos(vecPatElectron theobjs);
  
  

  // replace virtual members from inherited miniAODhelper:
  bool isGoodMuon(const pat::Muon&, const float, const muonID::muonID);
  bool isGoodElectron(const pat::Electron&, const float, const electronID::electronID);
  bool isGoodTau(const pat::Tau&, const float, const tauID::tauID);
  bool isGoodJet(const pat::Jet&, const float, const float, const jetID::jetID, const char);
  float GetMuonRelIsoR03(const pat::Muon&) const;
  float GetMuonRelIsoR04(const pat::Muon&) const;
  int GetHiggsDaughterId(const std::vector<reco::GenParticle>&);
  
  template <typename obj1, typename obj2> std::vector<obj1> cleanObjects(const std::vector<obj1>&, const std::vector<obj2>&, const double);
  
  template <typename particleType> pat::Jet getClosestJet(const std::vector<pat::Jet>&, const particleType&);

  //lepMVA
  float GetMuonLepMVA( const pat::Muon&, const std::vector<pat::Jet>&);
  float GetElectronLepMVA(const pat::Electron&, const std::vector<pat::Jet>&);



 private:
  
  // lepMVA TMVA readers
  TMVA::Reader* mu_reader_high_b;
  TMVA::Reader* mu_reader_high_e;
  TMVA::Reader* mu_reader_low_b;
  TMVA::Reader* mu_reader_low_e;
  TMVA::Reader* ele_reader_high_cb;
  TMVA::Reader* ele_reader_high_fb;
  TMVA::Reader* ele_reader_high_ec;
  TMVA::Reader* ele_reader_low_cb;
  TMVA::Reader* ele_reader_low_fb;
  TMVA::Reader* ele_reader_low_ec;
  Float_t varneuRelIso;
  Float_t varchRelIso;
  Float_t varjetDR_in;
  Float_t varjetPtRatio_in;
  Float_t varjetBTagCSV_in;
  Float_t varsip3d;
  Float_t varmvaId;
  Float_t varinnerHits;
  Float_t vardxy;
  Float_t vardz;
  
  
  
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
