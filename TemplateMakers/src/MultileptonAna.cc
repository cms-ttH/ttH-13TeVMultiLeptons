// created by Geoff Smith

#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/MultileptonAna.h"
#include <algorithm>
#include <array>

//// #if !defined( MULTILEPTONANA_CC )

MultileptonAna::MultileptonAna(){} // use EDAnalyzer constructor

MultileptonAna::~MultileptonAna(){} 


void MultileptonAna::detectData(string sampleName) {
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



void MultileptonAna::parse_params()
{

  setupoptionsparams = 	entire_pset.getParameter<edm::ParameterSet> ("setupoptions");
  triggerparams = 	entire_pset.getParameter<edm::ParameterSet> ("triggers");
  jetparams = 		entire_pset.getParameter<edm::ParameterSet> ("jets");
  subjetparams = 		entire_pset.getParameter<edm::ParameterSet> ("fatjets");
  btagparams = 		entire_pset.getParameter<edm::ParameterSet> ("btags");
  metparams = 		entire_pset.getParameter<edm::ParameterSet> ("met");
  prunedparams =      entire_pset.getParameter<edm::ParameterSet> ("prunedgenparticles");
  packedparams =      entire_pset.getParameter<edm::ParameterSet> ("packedgenparticles");
  variableparams = 	entire_pset.getParameter<edm::ParameterSet> ("variables");
  systparams = 		entire_pset.getParameter<edm::ParameterSet> ("systematics");
  selectionparams = 	entire_pset.getParameter<edm::ParameterSet> ("eventselection");
	
}

void MultileptonAna::SetupOptions (const edm::Event& event)
{
 	string rhostr = setupoptionsparams.getParameter<string> ("rhoHandle");
 	 	
 	edm::Handle<double> rhoHandle;
   	event.getByToken(rho_token_, rhoHandle);
 	
   	rho = *rhoHandle;
	sampleName = setupoptionsparams.getParameter<string> ("sample");
	isData = setupoptionsparams.getParameter<bool> ("isdata");

}
vstring MultileptonAna::HLTInfo ()
{
	vstring HLT_triggers = triggerparams.getParameter<vstring> ("trigger_vstring");
	if (debug) cout << "triggers to include:" << endl;
	if (debug) for (unsigned int i=0; i<HLT_triggers.size(); i++) { cout << HLT_triggers[i] << endl; }
	hltTag = triggerparams.getParameter<string> ("hltlabel");
	
	return HLT_triggers;
}

trigRes MultileptonAna::GetTriggers (const edm::Event& event)
{
	// hltTag already got by HLTInfo ...	
	edm::Handle<edm::TriggerResults> triggerResults;
	event.getByToken(triggerResults_token_, triggerResults);
	return triggerResults;
}

vecPatLepton MultileptonAna::fillLeptons(const vecPatMuon& muons, const vecPatElectron& electrons)
{
  vecPatLepton leptons;
  for (vecPatMuon::const_iterator iMu = muons.begin(); iMu != muons.end(); iMu++)
    {
      leptons.push_back(*iMu);
    }
  for (vecPatElectron::const_iterator iEle = electrons.begin(); iEle != electrons.end(); iEle++)
    {
      leptons.push_back(*iEle);
    }
  return leptons;
}

int MultileptonAna::GetVertices (const edm::Event& event)
{
	
	////////////////////////////////////////////////////////////
	//
	// count pvs for miniAODhelper
	//
	////////////////////////////////////////////////////////////

	//vars for vertex loop
	reco::Vertex vertex;
	double minNDOF = 4.0;
	double maxAbsZ = 24.0;
	double maxd0 = 2.;
	int numpv = 0;

	edm::Handle<reco::VertexCollection> vtxHandle;
	event.getByToken(vertex_token_,vtxHandle);
	reco::VertexCollection primaryVertices = *vtxHandle;

	numpv = 0;

	for (reco::VertexCollection::const_iterator iPV = primaryVertices.begin(); iPV != primaryVertices.end(); ++iPV)
	{
		bool isGood = ( !(iPV->isFake()) && (iPV->ndof()>minNDOF) && (abs(iPV->z())<=maxAbsZ) && (abs(iPV->position().Rho())<=maxd0)); // ndof()>=minNDOF
		if ( !isGood ) continue;
		if ( numpv == 0 ) vertex = *iPV;
		numpv++;
	}

	//cout << "numpv = " << numpv << endl;
	if ( numpv > 0 )
	{
		//cout << "setting vertex, numpv > 0" << endl;
		//miniAODhelper.SetVertex(vertex);
		SetVertex(vertex);
	}

	return numpv;
	
}



int MultileptonAna::GetHiggsDaughterId(const std::vector<reco::GenParticle>& genParticles)
{
  int daughter_id = -99e6;
  for (std::vector<reco::GenParticle>::const_iterator genParticle = genParticles.begin(); genParticle != genParticles.end(); genParticle++)
    {
      
      if (genParticle->pdgId() == 25 && genParticle->numberOfDaughters() > 0 && abs(genParticle->daughter(0)->pdgId()) != 25)
	{
	  daughter_id = abs(genParticle->daughter(0)->pdgId());
	  // if (daughter_id == 25 && genParticle->numberOfDaughters() >= 1)
	  //   {
	  //     daughter_id = abs(genParticle->daughter(1)->pdgId());
	  //   }
	  break;
	}
    }
  return daughter_id;
}

vector<ttH::Lepton> MultileptonAna::GetCollection (vector<ttH::Muon> muObjs, vector<ttH::Electron>eleObjs)
{
  vector<ttH::Lepton> lepCollection(muObjs.begin(),muObjs.end());
  lepCollection.insert(lepCollection.end(),eleObjs.begin(),eleObjs.end());
  std::sort(lepCollection.begin(), lepCollection.end(), [] (ttH::Lepton a, ttH::Lepton b) { return a.obj.Pt() > b.obj.Pt();});
  return lepCollection;
}

vector<ttH::Electron> MultileptonAna::GetCollection (vecPatElectron theobjs)
{
  ttH::Electron ele;
  vector<ttH::Electron> eleCollection;

  for (const auto & iEle: theobjs)
  {
      ele.obj = iEle.p4();
      ele.SCeta = iEle.userFloat("superClusterEta");
      ele.pdgID = iEle.pdgId();
      ele.dxy = iEle.userFloat("dxy");
      ele.dz = iEle.userFloat("dz");
      ele.numMissingInnerHits = iEle.userFloat("numMissingHits");
      ele.charge = iEle.charge();
      ele.isGsfCtfScPixChargeConsistent = iEle.isGsfCtfScPixChargeConsistent();
      ele.isGsfScPixChargeConsistent = iEle.isGsfScPixChargeConsistent();
      ele.passConversioVeto = iEle.passConversionVeto();
      ele.relIso = iEle.userFloat("relIso");
      ele.miniIso = iEle.userFloat("miniIso");
      ele.dEtaIn = iEle.deltaEtaSuperClusterTrackAtVtx();
      ele.dPhiIn = iEle.deltaPhiSuperClusterTrackAtVtx();
      ele.full5x5_sigmaIetaIeta = iEle.full5x5_sigmaIetaIeta();
      ele.hadronicOverEm = iEle.hadronicOverEm();
      ele.lepMVA = iEle.userFloat("leptonMVA");
      ele.miniIsoCharged = iEle.userFloat("chargedRelIso");
      ele.miniIsoNeutral = iEle.userFloat("neutralRelIso");
      ele.jetPtRatio = iEle.userFloat("nearestJetPtRatio");
      ele.jetPtRel = iEle.userFloat("nearestJetPtRel");
      ele.csv = iEle.userFloat("nearestJetCsv");
      ele.sip3D = iEle.userFloat("sip3D");
      ele.mvaID = iEle.userFloat("eleMvaIdHZZ");
      ele.mvaIDGP = iEle.userFloat("eleMvaId");
      ele.jet_nCharged_tracks = iEle.userFloat("nearestJetNDauCharged");
      ele.correctedPt = iEle.userFloat("correctedPt");

      // extra for sync     
      ele.miniAbsIsoCharged = iEle.userFloat("miniAbsIsoCharged");
      ele.miniAbsIsoNeutral = iEle.userFloat("miniAbsIsoNeutral");
      ele.rho = iEle.userFloat("rho");
      ele.effArea = iEle.userFloat("effArea");
      ele.miniIsoR = iEle.userFloat("miniIsoR");
      ele.miniAbsIsoNeutralcorr = iEle.userFloat("miniAbsIsoNeutralcorr");      
      
      // trying stuff out:

      ele.idTightPOG = PassElectron80XId(iEle,electronID::electron80XCutBasedT);
      ele.idMediumPOG = PassElectron80XId(iEle,electronID::electron80XCutBasedM); 
      ele.idLoosePOG = PassElectron80XId(iEle,electronID::electron80XCutBasedL);    
      ele.isPreselected = iEle.userFloat("idPreselection")>0.5;
      
      
      /////// set of eta-dep. cuts: ///////
      bool passesEtaDepCuts = false;
      
      if (fabs(iEle.eta()) < 0.8) {
         passesEtaDepCuts = iEle.full5x5_sigmaIetaIeta() < 0.011 &&
            iEle.hcalOverEcal() < 0.10 &&
            fabs(iEle.deltaEtaSuperClusterTrackAtVtx()) < 0.01 &&
            fabs(iEle.deltaPhiSuperClusterTrackAtVtx()) < 0.04 &&
            1.0/iEle.ecalEnergy() - iEle.eSuperClusterOverP()/iEle.ecalEnergy() > -0.05 &&
            1.0/iEle.ecalEnergy() - iEle.eSuperClusterOverP()/iEle.ecalEnergy() < 0.010;
      }
      else if (fabs(iEle.eta()) < 1.479) {
         passesEtaDepCuts = iEle.full5x5_sigmaIetaIeta() < 0.011 &&
            iEle.hcalOverEcal() < 0.10 &&
            fabs(iEle.deltaEtaSuperClusterTrackAtVtx()) < 0.01 &&
            fabs(iEle.deltaPhiSuperClusterTrackAtVtx()) < 0.04 &&
            1.0/iEle.ecalEnergy() - iEle.eSuperClusterOverP()/iEle.ecalEnergy() > -0.05 &&
            1.0/iEle.ecalEnergy() - iEle.eSuperClusterOverP()/iEle.ecalEnergy() < 0.010;
      }
      else if (fabs(iEle.eta()) < 2.5) {
         passesEtaDepCuts = iEle.full5x5_sigmaIetaIeta() < 0.030 &&
            iEle.hcalOverEcal() < 0.07 &&
            fabs(iEle.deltaEtaSuperClusterTrackAtVtx()) < 0.008 &&
            fabs(iEle.deltaPhiSuperClusterTrackAtVtx()) < 0.07 &&
            1.0/iEle.ecalEnergy() - iEle.eSuperClusterOverP()/iEle.ecalEnergy() > -0.05 &&
            1.0/iEle.ecalEnergy() - iEle.eSuperClusterOverP()/iEle.ecalEnergy() < 0.005;
      }
                
      //if (ele.obj.Pt()<30.) passespt30Cuts = true; // note: usually the corrected pt + a lepMVA cut is used here
      
      ele.passesEtaDepCuts = passesEtaDepCuts;
      
      
      //// gen stuff ////
      if (iEle.genParticle())
      {
        ele.genPdgID = iEle.genParticle()->pdgId();
	ele.isPromptFinalState = iEle.genParticle()->isPromptFinalState();
	ele.isDirectPromptTauDecayProductFinalState = iEle.genParticle()->isDirectPromptTauDecayProductFinalState();
	const reco::Candidate* genMother = GetGenMotherNoFsr(iEle.genParticle());
	ele.genMotherPdgID = genMother->pdgId();        
        const reco::Candidate* genGrandMother = GetGenMotherNoFsr(genMother);        
        ele.genGrandMotherPdgID = genGrandMother->pdgId();
      }
      else 
      {
        ele.genPdgID = 9999;
	ele.isPromptFinalState = false;
	ele.isDirectPromptTauDecayProductFinalState = false;
        ele.genMotherPdgID = 9999;
        ele.genGrandMotherPdgID = 9999;
      }
      eleCollection.push_back(ele);
  }
  std::sort(eleCollection.begin(), eleCollection.end(), [] (ttH::Electron a, ttH::Electron b) { return a.obj.Pt() > b.obj.Pt();});
  return eleCollection;
}

vector<ttH::Muon> MultileptonAna::GetCollection (vecPatMuon theobjs)
{
  ttH::Muon mu;
  vector<ttH::Muon> muCollection;
  for(const auto & iMu: theobjs)
    {
      mu.obj = iMu.p4();
      mu.pdgID = iMu.pdgId();
      mu.charge = iMu.charge();
      mu.isPFMuon = iMu.isPFMuon();
      mu.isTrackerMuon = iMu.isTrackerMuon();
      mu.isGlobalMuon = iMu.isGlobalMuon();
      mu.relIso = iMu.userFloat("relIso");
      mu.miniIso = iMu.userFloat("miniIso");
      mu.localChi2 = iMu.userFloat("localChiSq");
      mu.trKink = iMu.userFloat("trackKink");
      mu.segCompatibility = iMu.segmentCompatibility();
      mu.dxy = iMu.userFloat("dxy");
      mu.dz = iMu.userFloat("dz");
      mu.numberOfValidPixelHits = iMu.userFloat("numValidPixelHits");
      mu.trackerLayersWithMeasurement = iMu.userFloat("trackerLayersWithMeasurement");
      mu.chargeFlip = iMu.userFloat("chargeFlip");
      mu.lepMVA = iMu.userFloat("leptonMVA");
      mu.validFrac = iMu.userFloat("validFraction");
      mu.normalizedChi2 = iMu.userFloat("normalizedChiSq");
      mu.numberOfValidMuonHits = iMu.userFloat("numValidMuonHits");
      mu.numberOfMatchedStations = iMu.numberOfMatchedStations();
      mu.miniIsoCharged = iMu.userFloat("chargedRelIso");
      mu.miniIsoNeutral = iMu.userFloat("neutralRelIso");
      mu.jetPtRatio = iMu.userFloat("nearestJetPtRatio");
      mu.jetPtRel = iMu.userFloat("nearestJetPtRel");
      mu.csv = iMu.userFloat("nearestJetCsv");
      mu.sip3D = iMu.userFloat("sip3D");
      mu.jet_nCharged_tracks = iMu.userFloat("nearestJetNDauCharged");
      mu.correctedPt = iMu.userFloat("correctedPt");

      // extra for sync     
      mu.miniAbsIsoCharged = iMu.userFloat("miniAbsIsoCharged");
      mu.miniAbsIsoNeutral = iMu.userFloat("miniAbsIsoNeutral");
      mu.rho = iMu.userFloat("rho");
      mu.effArea = iMu.userFloat("effArea");
      mu.miniIsoR = iMu.userFloat("miniIsoR");
      mu.miniAbsIsoNeutralcorr = iMu.userFloat("miniAbsIsoNeutralcorr");
      
      // trying stuff out:
      //mu.idTightPOG = iMu.userFloat("idTightLJ");
      mu.idTightPOG = iMu.isTightMuon(vertex);      // <-- from PAT
      mu.idMediumPOG = iMu.isMediumMuon();          // <-- from PAT
      mu.idLoosePOG = iMu.isLooseMuon();            // <-- from PAT
      
      // Loose muon POG ID is really loose. Basically
      // anything you're likely to make a collection out of (besides
      // some of "raw" muons) should pass it.
      
      mu.isPreselected = iMu.userFloat("idPreselection")>0.5;

      if (iMu.genParticle())
	{
	  mu.genPdgID = iMu.genParticle()->pdgId();
	  mu.isPromptFinalState = iMu.genParticle()->isPromptFinalState();
	  mu.isDirectPromptTauDecayProductFinalState = iMu.genParticle()->isDirectPromptTauDecayProductFinalState();
	  const reco::Candidate* genMother = GetGenMotherNoFsr(iMu.genParticle());
	  mu.genMotherPdgID = genMother->pdgId();
	  const reco::Candidate* genGrandMother = GetGenMotherNoFsr(genMother);        
	  mu.genGrandMotherPdgID = genGrandMother->pdgId();
	}
      else
	{
	  mu.genPdgID = 9999;
	  mu.isPromptFinalState = false;
	  mu.isDirectPromptTauDecayProductFinalState = false;
	  mu.genMotherPdgID = 9999;
	  mu.genGrandMotherPdgID = 9999;
	}
      muCollection.push_back(mu);
    }
  std::sort(muCollection.begin(), muCollection.end(), [] (ttH::Muon a, ttH::Muon b) { return a.obj.Pt() > b.obj.Pt();});
  return muCollection;
}

vector<ttH::Tau> MultileptonAna::GetCollection(vecPatTau theobjs)
{
  ttH::Tau tau;
  vector<ttH::Tau> tauCollection;
  for(const auto & iTau: theobjs)
  {
      tau.obj = iTau.p4();
      
      if (iTau.genParticle())
      {
        tau.genPdgID = iTau.genParticle()->pdgId();
        const reco::Candidate* genMother = GetGenMotherNoFsr(iTau.genParticle());
	tau.genMotherPdgID = genMother->pdgId();
        const reco::Candidate* genGrandMother = GetGenMotherNoFsr(genMother);        
        tau.genGrandMotherPdgID = genGrandMother->pdgId();
      }
      else
      {
        tau.genPdgID = 9999;
        tau.genMotherPdgID = 9999;
        tau.genGrandMotherPdgID = 9999;
      }
      tau.charge = iTau.charge();
      tau.dxy = iTau.userFloat("dxy");
      tau.dz = iTau.userFloat("dz");
      tau.decayModeFinding = iTau.tauID("decayModeFinding");
      tau.mvaID = iTau.tauID("byMediumIsolationMVArun2v1DBdR03oldDMwLT");

      tauCollection.push_back(tau);

  }
  std::sort(tauCollection.begin(), tauCollection.end(), [] (ttH::Tau a, ttH::Tau b) { return a.obj.Pt() > b.obj.Pt();});
  return tauCollection;
}

vector<ttH::Jet> MultileptonAna::GetCollection (vecPatJet theobjs)
{
  ttH::Jet jet;
  vector<ttH::Jet> jetCollection;
  for(const auto & iJet: theobjs)
  {
      jet.obj = iJet.p4();
      if (iJet.genParton())
      {
        jet.genPdgID = iJet.genParton()->pdgId();
        const reco::Candidate* genMother = GetGenMotherNoFsr(iJet.genParton());
	jet.genMotherPdgID = genMother->pdgId();
        const reco::Candidate* genGrandMother = GetGenMotherNoFsr(genMother);        
        jet.genGrandMotherPdgID = genGrandMother->pdgId();
      }
      else
      {
        jet.genPdgID = 9999;
        jet.genMotherPdgID = 9999;
        jet.genGrandMotherPdgID = 9999;
      }
      jet.charge = iJet.jetCharge();
      string thedisc = btagparams.getParameter<string> ("btagdisc");
      jet.csv = iJet.bDiscriminator(thedisc);
      //jet.qgid = -99.;//iJet.userFloat("qgid");
      jet.qgid = iJet.userFloat("qgid");
      jet.pdgID = iJet.pdgId();
      jet.flavor = iJet.hadronFlavour();
      jetCollection.push_back(jet);

  }
  std::sort(jetCollection.begin(), jetCollection.end(), [] (ttH::Jet a, ttH::Jet b) { return a.obj.Pt() > b.obj.Pt();});
  return jetCollection;
}

vector<ttH::GenParticle> MultileptonAna::GetCollection(std::vector<reco::GenJet> theobjs)
{
  vector<ttH::GenParticle> tth_gen_jets;
  ttH::GenParticle tth_gen_jet;

  for (const auto & pat_gen_jet : theobjs)
    {
      tth_gen_jet.obj = pat_gen_jet.p4();
      tth_gen_jet.pdgID = pat_gen_jet.pdgId();
      tth_gen_jet.status = pat_gen_jet.status();
      tth_gen_jet.charge = pat_gen_jet.charge();
      tth_gen_jets.push_back(tth_gen_jet);
    }
  return tth_gen_jets;
}

vector<ttH::MET> MultileptonAna::GetCollection (patMETs theobjs)
{
  vector<ttH::MET> theMETs;
  ttH::MET theMET;
  pat::MET patMET = theobjs->front();

  theMET.obj = patMET.p4();
  theMET.pt_forSync = floor(patMET.pt()*100+0.5)/100;
  theMET.phi_forSync = floor(patMET.phi()*100+0.5)/100;

  theMETs.push_back(theMET);
  return theMETs;
}
  

std::vector<pat::Muon>
MultileptonAna::GetSelectedMuons(const std::vector<pat::Muon>& inputMuons, const float iMinPt, const muonID::muonID iMuonID){
  CheckSetUp();
  
  std::vector<pat::Muon> selectedMuons;

  for( const auto& mu: inputMuons)
  {
      bool passSelection = false;
      bool passPt = (mu.pt() >= iMinPt);
      switch(iMuonID)
      {
	case muonID::muonRaw: 
            passSelection = true;
            break;
        case muonID::muonLoose: 
            passSelection = mu.isLooseMuon() && passPt;
            break;
	case muonID::muonPreselection: 
            passSelection = (mu.userFloat("idPreselection") > 0.5 && passPt);
            break;
	case muonID::muonFakeable: 
            passSelection = (mu.userFloat("idFakeable") > 0.5 && passPt);
            break;
	case muonID::muonTight: 
            passSelection = (mu.userFloat("idTight") > 0.5 && passPt);
            break;    
        case muonID::muonTightMvaBased:
            passSelection = (mu.userFloat("idMVABased") > 0.5 && passPt);
            break;
        default:
            cout << "GetSelectedMuons-> no such muonID!" << endl;
            break;
      }

      if( passSelection ) selectedMuons.push_back(mu);
      else if (iMuonID == muonID::muonLooseMvaBased || iMuonID == muonID::muonTightMvaBased) break;

  }
  return selectedMuons;
}

std::vector<pat::Electron>
MultileptonAna::GetSelectedElectrons(const std::vector<pat::Electron>& inputElectrons, const float iMinPt, const electronID::electronID iElectronID){

  CheckSetUp();

  std::vector<pat::Electron> selectedElectrons;

  for(const auto& ele: inputElectrons)
  {
      bool passSelection = false;
      bool passPt = (ele.pt() >= iMinPt);
      switch(iElectronID)
      {
	case electronID::electronRaw: 
            passSelection = true;
            break;
	case electronID::electronPreselection: 
            passSelection = (ele.userFloat("idPreselection") > 0.5 && passPt);
            break;
	case electronID::electronFakeable: 
            passSelection = (ele.userFloat("idFakeable") > 0.5 && passPt);
            break;
	case electronID::electronTight: 
            passSelection = (ele.userFloat("idTight") > 0.5 && passPt);
            break;
	case electronID::electronTightMvaBased: 
            passSelection = (ele.userFloat("idMVABased") > 0.5 && passPt);     
            break;                  
        default:
            cout << "GetSelectedElectrons-> no such electronID!" << endl;
            break;
      }
    
    if( passSelection ) selectedElectrons.push_back(ele);
    else if (iElectronID == electronID::electronLooseMvaBased || iElectronID == electronID::electronTightMvaBased) break;
  }

  return selectedElectrons;
}


std::vector<pat::Tau>
MultileptonAna::GetSelectedTaus(const std::vector<pat::Tau>& inputTaus, const float iMinPt, const tauID::tauID iTauID){

  CheckSetUp();

  std::vector<pat::Tau> selectedTaus;

  for(const auto& tau: inputTaus){
      bool passSelection = false;
      bool passPt = (tau.pt() >= iMinPt);
      switch(iTauID)
      {
        case tauID::tauRaw: 
          passSelection = true;
          break;        
        case tauID::tauLoose:
	  passSelection = ((tau.userFloat("idPreselection")>0.5) && passPt);
	  break;
        case tauID::tauMedium:
	  passSelection = ((tau.userFloat("idSelection")>0.5) && passPt);
	  break;
	default:
	  break;

      }
    
      if( passSelection ) selectedTaus.push_back(tau);
  }

  return selectedTaus;
}


const reco::Candidate* MultileptonAna::GetGenMotherNoFsr(const reco::Candidate* theobj)
{
  if (theobj->numberOfMothers()>0)
    {
      const reco::Candidate* mother = theobj->mother(0);
      if (mother->pdgId() != theobj->pdgId()) return mother;
      else return GetGenMotherNoFsr(mother);
    }
  else 
    {
      return theobj;
    }
}

std::pair<const reco::Candidate*, const reco::Candidate*> MultileptonAna::GetGenDaughterNoFsr(const reco::Candidate* theobj)
{
  const reco::Candidate* returnDau0 = theobj;
  const reco::Candidate* returnDau1 = theobj;

  if (theobj->numberOfDaughters()>0)
    {
      const reco::Candidate* daughter = theobj->daughter(0);
      if (daughter->pdgId() != theobj->pdgId()) returnDau0 = daughter;
      else returnDau0 = GetGenDaughterNoFsr(daughter).first;
    
      if (theobj->numberOfDaughters()>1)
	{
	  daughter = theobj->daughter(1);
	  if (daughter->pdgId() != theobj->pdgId()) returnDau1 = daughter;
	  else returnDau1 = GetGenDaughterNoFsr(daughter).second;
	}
    }
  std::pair<const reco::Candidate*, const reco::Candidate*> returnPair(returnDau0,returnDau1);
  return returnPair;
}

//// #endif // !defined( MULTILEPTONANA_CC ) 

