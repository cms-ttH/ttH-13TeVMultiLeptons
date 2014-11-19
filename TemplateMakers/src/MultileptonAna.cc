// created by Geoff Smith

#include "ttHMultileptonAnalysis/TemplateMakers/interface/MultileptonAna.h"

void MultileptonAna::parse_params()
{
	setupoptionsparams = 	entire_pset.getParameter<edm::ParameterSet> ("setupoptions");
	triggerparams = 	entire_pset.getParameter<edm::ParameterSet> ("triggers");
	muonparams = 		entire_pset.getParameter<edm::ParameterSet> ("muons");
      	electronparams = 	entire_pset.getParameter<edm::ParameterSet> ("electrons");
      	leptonparams = 		entire_pset.getParameter<edm::ParameterSet> ("leptons");
      	jetparams = 		entire_pset.getParameter<edm::ParameterSet> ("jets");
      	subjetparams = 		entire_pset.getParameter<edm::ParameterSet> ("fatjets");
      	btagparams = 		entire_pset.getParameter<edm::ParameterSet> ("btags");
      	metparams = 		entire_pset.getParameter<edm::ParameterSet> ("met");
      	variableparams = 	entire_pset.getParameter<edm::ParameterSet> ("variables");
      	systparams = 		entire_pset.getParameter<edm::ParameterSet> ("systematics");
      	selectionparams = 	entire_pset.getParameter<edm::ParameterSet> ("eventselection");
	
}

void MultileptonAna::SetupOptions (const edm::Event& event)
{
	string rhostr = setupoptionsparams.getParameter<string> ("rhoHandle");
	edm::Handle<double> rhoHandle;
  	event.getByLabel(rhostr,rhoHandle);  //"fixedGridRhoAll");
  	rho = *rhoHandle; 

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
	event.getByLabel(edm::InputTag("TriggerResults","", hltTag), triggerResults);
	return triggerResults;
}


patMuons MultileptonAna::GetMuons (const edm::Event& event)
{
	string muCollection = muonparams.getParameter<string> ("muonCollection");
	patMuons muonHandle; 
	event.getByLabel(muCollection,muonHandle);
	return muonHandle;
	
}
patElectrons MultileptonAna::GetElectrons (const edm::Event& event)
{
	string elCollection = electronparams.getParameter<string> ("electronCollection");
	patElectrons electronHandle; 
	event.getByLabel(elCollection,electronHandle);
	return electronHandle;
	
}
vecPatLepton MultileptonAna::fillLeptons(vecPatMuon& muons, vecPatElectron& electrons)
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
void MultileptonAna::GetLeptons (const edm::Event& event)
{
	bool are_electrons_added_to_leptons = leptonparams.getParameter<bool> ("useElectrons");
	bool are_muons_added_to_leptons = leptonparams.getParameter<bool> ("useMuons");
	
	if (debug) cout << are_electrons_added_to_leptons << " " << are_muons_added_to_leptons << endl;
	
	
}
patJets MultileptonAna::GetJets (const edm::Event& event)
{
	string mainjetCollection = jetparams.getParameter<string> ("jetCollection");
	patJets jetsHandle; 
	event.getByLabel(mainjetCollection,jetsHandle);
	return jetsHandle;
	
	
}
patJets MultileptonAna::GetSubJets (const edm::Event& event)
{
	string subjetCollection = subjetparams.getParameter<string> ("fatjetCollection");
	patJets subjetsHandle; 
	event.getByLabel(subjetCollection,subjetsHandle);
	return subjetsHandle;
	
	
}
void MultileptonAna::GetBtags (const edm::Event& event)
{
	
}
patMETs MultileptonAna::GetMet (const edm::Event& event)
{
	
	string metCollection = metparams.getParameter<string> ("METCollection");
	patMETs METsHandle; 
	event.getByLabel(metCollection,METsHandle);
	return METsHandle;
	
	
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
	event.getByLabel("offlineSlimmedPrimaryVertices",vtxHandle);
	reco::VertexCollection primaryVertices = *vtxHandle;

	numpv = 0;

	for (reco::VertexCollection::const_iterator iPV = primaryVertices.begin(); iPV != primaryVertices.end(); ++iPV)
	{
		bool isGood = ( !(iPV->isFake()) && (iPV->ndof()>=minNDOF) && (abs(iPV->z())<=maxAbsZ) && (abs(iPV->position().Rho())<=maxd0));
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


void MultileptonAna::Variables (const edm::Event& event)
{
	//vstring variable_list = variableparams.getParameter<vstring> ("thevars");
}
void MultileptonAna::Systematics (const edm::Event& event)
{
	
	//bool include_systematics = systparams.getParameter<bool> ("include_syst");
	//vstring vstring_of_systs = systparams.getParameter<vstring> ("syst_list");
	
}
void MultileptonAna::EventSelection (const edm::Event& event)
{
	//edm::ParameterSet lepselection_pset = selectionparams.getParameter<edm::ParameterSet> ("Leps");
	//string numJets_str = selectionparams.getParameter<string> ("numJets");
	//string numTags_str = selectionparams.getParameter<string> ("numTags");
	//double met_cut = selectionparams.getParameter<double> ("METcut");
	
}



vecTLorentzVector MultileptonAna::Get_vecTLorentzVector (vecPatMuon theobjs)
{
	//int nobjs = theobjcollection.size();
	vecTLorentzVector theobjs_vecTLV;
	
	for (muit iMuon= theobjs.begin(); iMuon != theobjs.end(); ++iMuon)
	{
		TLorentzVector tempTLV;
		tempTLV.SetPxPyPzE(iMuon->px(),iMuon->py(),iMuon->pz(),iMuon->energy());
		theobjs_vecTLV.push_back(tempTLV);
	}
		
	return theobjs_vecTLV;
		
}
vecTLorentzVector MultileptonAna::Get_vecTLorentzVector (vecPatElectron theobjs)
{
	vecTLorentzVector theobjs_vecTLV;
	
	for (eleit iEle= theobjs.begin(); iEle != theobjs.end(); ++iEle)
	{
		TLorentzVector tempTLV;
		tempTLV.SetPxPyPzE(iEle->px(),iEle->py(),iEle->pz(),iEle->energy());
		theobjs_vecTLV.push_back(tempTLV);
	}
		
	return theobjs_vecTLV;
}
vecTLorentzVector MultileptonAna::Get_vecTLorentzVector (vecPatJet theobjs)
{
	vecTLorentzVector theobjs_vecTLV;
	
	for (jetit iJet = theobjs.begin(); iJet != theobjs.end(); ++iJet)
	{
		TLorentzVector tempTLV;
		tempTLV.SetPxPyPzE(iJet->px(),iJet->py(),iJet->pz(),iJet->energy());
		theobjs_vecTLV.push_back(tempTLV);
	}
		
	return theobjs_vecTLV;
	
	
}
//vecTLorentzVector Get_vecTLorentzVector_SubJets ()

TLorentzVector MultileptonAna::Get_TLorentzVector (patMETs theobjs)
{
	pat::MET theMET = theobjs->front();
	TLorentzVector metTLV(theMET.px(),theMET.py(),0.0,theMET.pt());
	return metTLV;
	
}
TLorentzVector MultileptonAna::Get_TLorentzVector (pat::MET theMET)
{
	//pat::MET theMET = theobj;
	TLorentzVector metTLV(theMET.px(),theMET.py(),0.0,theMET.pt());
	return metTLV;
	
}

vecTLorentzVector MultileptonAna::Get_vecTLorentzVector_sorted_leptons (vecTLorentzVector leps1, vecTLorentzVector leps2)
{	

	vecTLorentzVector newvecTLV;
	
	// assuming they are already sorted by pt, respectively:
	
	int size1 = leps1.size();
 	int size2 = leps2.size();
 	
 	if (size1==0||size2!=0) return leps2;
	if (size2==0||size1!=0) return leps1;
	if (size1==0&&size2==0) { TLorentzVector ret(0.,0.,0.,0.); newvecTLV.push_back(ret); return newvecTLV; } // <- should figure out something else for this case..
	
	int maxsize = max(size1,size2);
	int minsize = min(size1,size2);
	
	bool smallestis1 = (size1<size2) ? true : false;
	
	int i = 0;
	int j = 0;
	
	while (true)
	{
		if ((i==minsize&&smallestis1)||(j==minsize&&(!smallestis1))) break;

		if (leps1[i].Pt() < leps2[j].Pt())
		{
			newvecTLV.push_back(leps2[j]);
			j++;
		}
		else
		{
			newvecTLV.push_back(leps1[i]);
			i++;
		}
	}		
	if (smallestis1)
	{
		while (true)
		{
			if (j==maxsize) break;
			newvecTLV.push_back(leps2[j]);
			j++;
		}								
	}
	if (!smallestis1)
	{			
		while (true)
		{
			if (i==maxsize) break;
			newvecTLV.push_back(leps1[i]);
			i++;
		}
	}
	
//// above takes a time that is linear with size of the vectors.
//// brute force (if you aren't sure if they are sorted beforehand), takes
//// a time that is quadratic in size of the vector:
// 	
// 	leps1.insert(leps1.end(),leps2.begin(),leps2.end());
// 	vecTLorentzVector newvecTLV;
// 	
// 	//int startingpoint = 0;
// 	int size = leps1.size();
// 	
// 	for (int i=0; i<size; i++)
// 	{
// 		for (int j=0; j<size; j++)
// 		{
// 			bool isprevious = false;
// 			
// 			int max
			
	
//	TLorentzVector dummy;
//	dummy.SetPxPyPzE(0.,0.,0.,0.);
//	newvecTLV.push_back(dummy);

	return newvecTLV;
	
}


bool MultileptonAna::isGoodMuon(const pat::Muon& iMuon, const float iMinPt, const muonID::muonID iMuonID){

  CheckVertexSetUp();

  double minMuonPt = iMinPt;

  //float maxLooseMuonAbsEta = 2.5;
  float maxLooseMuonAbsEta = muonparams.getParameter<double> ("maxLooseMuonAbsEta");
  
  

  //float maxTightMuonAbsEta = 2.1;
//float maxTightMuonAbsEta = 0.25;
  float maxTightMuonAbsEta = muonparams.getParameter<double> ("maxTightMuonAbsEta");
  
  // Be skeptical about this muon making it through
  bool passesKinematics	= false;
  bool passesIso        = false;
  bool passesID         = false;
  bool isPFMuon         = false;
  bool passesTrackerID  = false;

  bool passesGlobalTrackID   = false;
  bool passesMuonBestTrackID = false;
  bool passesInnerTrackID    = false;
  bool passesTrackID         = false;

  
  double tightRelativeIso = muonparams.getParameter<double> ("tightRelativeIso");
  double looseRelativeIso = muonparams.getParameter<double> ("looseRelativeIso");
  double tightTrackNormalizedChi2 = muonparams.getParameter<double> ("tightTrackNormalizedChi2");
  int tightTrackNumberOfValidMuonHits = muonparams.getParameter<int> ("tightTrackNumberOfValidMuonHits");
  double tightTrackDxy = muonparams.getParameter<double> ("tightTrackDxy");
  double tightTrackDz = muonparams.getParameter<double> ("tightTrackDz");
  int tightNumberOfValidPixelHits = muonparams.getParameter<int> ("tightNumberOfValidPixelHits");
  int tightTrackerLayersWithMeasurement = muonparams.getParameter<int> ("tightTrackerLayersWithMeasurement");
  

  switch(iMuonID){
  case muonID::muonSide:
  case muonID::muonSideLooseMVA:
  case muonID::muonSideTightMVA:
  case muonID::muonPtOnly:
  case muonID::muonPtEtaOnly:
  case muonID::muonPtEtaIsoOnly:
  case muonID::muonPtEtaIsoTrackerOnly:
  case muonID::muonNoCuts:
  case muonID::muonLoose:
    passesKinematics = ((iMuon.pt() >= minMuonPt) && (fabs(iMuon.eta()) <= maxLooseMuonAbsEta));
    passesIso        = (GetMuonRelIso(iMuon) < looseRelativeIso);
    isPFMuon         = true;
    passesID         = (( iMuon.isGlobalMuon() || iMuon.isTrackerMuon() ) && isPFMuon);
    break;
  case muonID::muonTight:
    passesKinematics = ((iMuon.pt() >= minMuonPt) && (fabs(iMuon.eta()) <= maxTightMuonAbsEta));
    passesIso        = (GetMuonRelIso(iMuon) < tightRelativeIso);
    isPFMuon         = true;

    if( iMuon.globalTrack().isAvailable() ){
      passesGlobalTrackID = ( (iMuon.globalTrack()->normalizedChi2() < tightTrackNormalizedChi2) 
			      && (iMuon.globalTrack()->hitPattern().numberOfValidMuonHits() > tightTrackNumberOfValidMuonHits)
			      );
    }
    if( iMuon.muonBestTrack().isAvailable() ){
      passesMuonBestTrackID = ( (fabs(iMuon.muonBestTrack()->dxy(vertex.position())) < tightTrackDxy)
				&& (fabs(iMuon.muonBestTrack()->dz(vertex.position())) < tightTrackDz)
				);
    }
    if( iMuon.innerTrack().isAvailable() )
      passesInnerTrackID = (iMuon.innerTrack()->hitPattern().numberOfValidPixelHits() > tightNumberOfValidPixelHits);
    if( iMuon.track().isAvailable() )
      passesTrackID = (iMuon.track()->hitPattern().trackerLayersWithMeasurement() > tightTrackerLayersWithMeasurement);

    passesTrackerID = ( passesGlobalTrackID && passesMuonBestTrackID && passesInnerTrackID && passesTrackID && (iMuon.numberOfMatchedStations() > 1) );

    passesID        = ((iMuon.isGlobalMuon() || iMuon.isTrackerMuon()) && isPFMuon && passesTrackerID);
    break;
  case muonID::muonPreselection:
    passesKinematics = ((iMuon.pt() > minMuonPt) && (fabs(iMuon.eta()) < 2.4));
    passesIso        = (GetMuonRelIso(iMuon) < 0.400);
    isPFMuon         = true;
    if( iMuon.muonBestTrack().isAvailable() ){
      passesMuonBestTrackID = ( (fabs(iMuon.muonBestTrack()->dxy(vertex.position())) < 0.05)
                                && (fabs(iMuon.muonBestTrack()->dz(vertex.position())) < 0.2)
                                );
    }
    //need charge flip cuts...
    passesID         = (( iMuon.isGlobalMuon() || iMuon.isTrackerMuon() ) && isPFMuon && passesMuonBestTrackID );
    break;
  }

  return (passesKinematics && passesIso && passesID);
}


bool MultileptonAna::isGoodElectron(const pat::Electron& iElectron, const float iMinPt, const electronID::electronID iElectronID){

  CheckVertexSetUp();

  double minElectronPt = iMinPt;

  float maxLooseElectronAbsEta = electronparams.getParameter<double> ("maxLooseElectronAbsEta");
  float maxTightElectronAbsEta = electronparams.getParameter<double> ("maxTightElectronAbsEta");
  string theElectronMVA = electronparams.getParameter<string> ("theElectronMVA");
  double passMVAcut = electronparams.getParameter<double> ("passMVAcut");
  double tightElectronIso = electronparams.getParameter<double> ("tightElectronIso");
  double looseElectronIso = electronparams.getParameter<double> ("looseElectronIso");  
  double tightDxy = electronparams.getParameter<double> ("tightDxy");
  double looseDxy = electronparams.getParameter<double> ("looseDxy");
  double dz = electronparams.getParameter<double> ("dZ");
  

  // Be skeptical about this electron making it through
  bool passesKinematics	= false;
  bool passesIso        = false;
  bool passesID         = false;

  bool inCrack = false;
  if( iElectron.superCluster().isAvailable() )
    inCrack = ( fabs(iElectron.superCluster()->position().eta())>1.4442 && fabs(iElectron.superCluster()->position().eta())<1.5660 ); // doesn't change


  // below should be made less confusing ...

  bool myTrigPresel = true;

  double eleID      = iElectron.electronID(theElectronMVA);
  bool passMVAId53x = ( eleID > passMVAcut );  // For 2012_53x, tighter selection

  bool d02 = false; 
  bool d04 = false;
  bool dZ  = false;
  bool no_exp_inner_trkr_hits = true; //false; // see below
  bool passGsfTrackID = false;
  if( iElectron.gsfTrack().isAvailable() ){
    d02 = ( fabs(iElectron.gsfTrack()->dxy(vertex.position())) < tightDxy );
    d04 = ( fabs(iElectron.gsfTrack()->dxy(vertex.position())) < looseDxy );
    //no_exp_inner_trkr_hits = ( iElectron.gsfTrack()->trackerExpectedHitsInner().numberOfHits() <= 0 ); // deprecated in 7_2_0 .. replace with ..?
    dZ = ( fabs(iElectron.gsfTrack()->dz(vertex.position())) < dz );
  }

  bool notConv = ( iElectron.passConversionVeto() );
  bool id      = ( passMVAId53x && d02 && dZ && notConv );

  switch(iElectronID){
  case electronID::electronSide:
  case electronID::electronSideLooseMVA:
  case electronID::electronSideTightMVA:
  case electronID::electronLooseMinusTrigPresel:
  case electronID::electronNoCuts:
  case electronID::electronLoose:
    passesKinematics = ((iElectron.pt() >= minElectronPt) && (fabs(iElectron.eta()) <= maxLooseElectronAbsEta) && !inCrack);
    passesIso        = (GetElectronRelIso(iElectron) < looseElectronIso);
    passesID         = ( passMVAId53x && no_exp_inner_trkr_hits && d04 && notConv && myTrigPresel );
    break;
  case electronID::electronTightMinusTrigPresel:
  case electronID::electronTight:
    passesKinematics = ((iElectron.pt() >= minElectronPt) && (fabs(iElectron.eta()) <= maxTightElectronAbsEta) && !inCrack);
    passesIso        = (GetElectronRelIso(iElectron) < tightElectronIso);
    passesID         = ( id && no_exp_inner_trkr_hits && myTrigPresel );
    break;
  case electronID::electronPreselection:
    passesKinematics = ((iElectron.pt() > minElectronPt) && (fabs(iElectron.eta()) < maxLooseElectronAbsEta) && !inCrack);
    passesIso        = (GetElectronRelIso(iElectron) < 0.400);
    if( iElectron.gsfTrack().isAvailable() ){
      passGsfTrackID = ( (fabs(iElectron.gsfTrack()->dxy(vertex.position())) < 0.05) && (fabs(iElectron.gsfTrack()->dz(vertex.position())) < 0.2) && iElectron.gsfTrack()->trackerExpectedHitsInner().numberOfHits() <= 1  );
    }

    passesID         = ( passGsfTrackID && passMVAId53x && no_exp_inner_trkr_hits && notConv && myTrigPresel );    
    break;
  }

  return (passesKinematics && passesIso && passesID);
}

bool MultileptonAna::isGoodTau(const pat::Tau& iTau, const float iMinPt, const tauID::tauID iTauID){

  CheckVertexSetUp();
 
  double minTauPt = iMinPt;
  
  //double tauMinPt
  //double tauMaxAbsEta = 
  
  bool passesKinematics = false;
  passesKinematics = (iTau.pt() >= 20) && (fabs(iTau.eta()) <= 2.1) && (iTau.pt() > minTauPt); //minTauPt vs. 20?
  return passesKinematics;
}

bool MultileptonAna::isGoodJet(const pat::Jet& iJet, const float iMinPt, const float iMaxAbsEta, const jetID::jetID iJetID, const char iCSVworkingPoint){

  CheckVertexSetUp();

  
//   neutralHadronEnergyFraction
//   chargedEmEnergyFraction
//   neutralEmEnergyFraction
//   numberOfDaughters
//   chargedHadronEnergyFraction
//   chargedMultiplicity

  // Transverse momentum requirement
  if( iJet.pt() < iMinPt ) return false;

  // Absolute eta requirement
  if( fabs(iJet.eta()) > iMaxAbsEta ) return false;

  bool loose = (

		iJet.neutralHadronEnergyFraction() < 0.99 &&
		iJet.chargedEmEnergyFraction() < 0.99 &&
		iJet.neutralEmEnergyFraction() < 0.99 &&
		iJet.numberOfDaughters() > 1

		);

  if( fabs(iJet.eta())<2.4 ){ // endcaps
    loose = ( loose &&
	      iJet.chargedHadronEnergyFraction() > 0.0 &&
	      iJet.chargedMultiplicity() > 0
	      );
  }

  // Jet ID
  switch(iJetID){
  case jetID::none:
  case jetID::jetMinimal:
  case jetID::jetLooseAOD:
  case jetID::jetLoose:
  case jetID::jetTight:
    if( !loose ) return false;
    break;
  default:
    break;
  }

  if( !PassesCSV(iJet, iCSVworkingPoint) ) return false;

  return true;
}
