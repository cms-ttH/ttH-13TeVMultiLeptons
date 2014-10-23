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
	string rhostr = setupoptionsparams.getParameter<string> ("rhohandle");
	edm::Handle<double> rhoHandle;
  	event.getByLabel(rhostr,rhoHandle);  //"fixedGridRhoAll");
  	rho = *rhoHandle; 

}
vstring MultileptonAna::Triggers (const edm::Event& event)
{
	vstring HLT_triggers = triggerparams.getParameter<vstring> ("trigger_vstring");
	if (debug) cout << "triggers to include: << endl;
	if (debug) for (unsigned int i=0; i<HLT_triggers.size(); i++) { cout << HLT_triggers[i] << endl; }
	hltTag = triggerparams.getParameter<string> ("hltlabel");
	
	return HLT_triggers;
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
		miniAODhelper.SetVertex(vertex);
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
//vecTLorentzVector Get_vecTLorentzVector_Muons

vecTLorentzVector MultileptonAna::Get_vecTLorentzVector_sorted_leptons (vecTLorentzVector leps1, vecTLorentzVector leps2)
{	

	vecTLorentzVector newvecTLV;
	
	// assuming they are already sorted by pt, respectively:
	
// 	int size1 = leps1.size();
// 	int size2 = leps2.size();
// 	
// 	//if (size1==0&&size2==0) return 0;
// 	
// 	int maxsize = max(size1,size2);
// 	int minsize = min(size1,size2);
// 	
// 	bool smallestis1 = (size1<size2) ? true : false;
// 	
// 	int i = 0;
// 	int j = 0;
// 	
// 	while (true)
// 	{
// 		if ((i==minsize&&smallestis1)||(j==minsize&&(!smallestis1))) break;
// 
// 		if (leps1[i].Pt() < leps2[j].Pt())
// 		{
// 			newvecTLV.push_back(leps2[j]);
// 			j++;
// 		}
// 		else
// 		{
// 			newvecTLV.push_back(leps1[i]);
// 			i++;
// 		}
// 	}		
// 	if (smallestis1)
// 	{
// 		while (true)
// 		{
// 			if (j==maxsize) break;
// 			newvecTLV.push_back(leps2[j]);
// 			j++;
// 		}								
// 	}
// 	if (!smallestis1)
// 	{			
// 		while (true)
// 		{
// 			if (i==maxsize) break;
// 			newvecTLV.push_back(leps1[i]);
// 			i++;
// 		}
// 	}
	
//// above takes a time that is linear in size of the vectors.
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
			
	
	TLorentzVector dummy;
	dummy.SetPxPyPzE(0.,0.,0.,0.);
	newvecTLV.push_back(dummy);

	return newvecTLV;
	
}
