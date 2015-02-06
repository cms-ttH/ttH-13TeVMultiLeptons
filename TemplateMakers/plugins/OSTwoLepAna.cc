// created by Geoff Smith

#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/OSTwoLepAna.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/EGammaMvaEleEstimatorFWLite.h"

OSTwoLepAna::OSTwoLepAna(const edm::ParameterSet& constructparams){ //Anything that needs to be done at creation time
	debug = constructparams.getParameter<bool> ("debug");
	entire_pset = constructparams;
	parse_params();

	bsToken_ = consumes <reco::BeamSpot> (edm::InputTag(std::string("offlineBeamSpot")));
	conversionToken_ = consumes <reco::ConversionCollection> (edm::InputTag(std::string("reducedEgamma"),std::string("reducedConversions")));

}
OSTwoLepAna::~OSTwoLepAna(){} //Anything that needs to be done at destruction time


void OSTwoLepAna::beginJob()
{

	el1 = fopen ("ele_loose1.txt", "w+");
	el2 = fopen ("ele_loose2.txt", "w+");
	el3 = fopen ("ele_loose3.txt", "w+");
	
	ml2 = fopen ("mu_loose2.txt", "w+");
	ml3 = fopen ("mu_loose3.txt", "w+");

	et1 = fopen ("ele_tight1.txt", "w+");
	et2 = fopen ("ele_tight2.txt", "w+");
	et3 = fopen ("ele_tight3.txt", "w+");
	
	mt2 = fopen ("mu_tight2.txt", "w+");
	mt3 = fopen ("mu_tight3.txt", "w+");

	// job setup	
	sampleNumber = convertSampleNameToNumber(sampleName);
	SetUp(analysisYear, sampleNumber, analysisType::DIL, isData);
	SetFactorizedJetCorrector();
	setupMva();
	alltriggerstostudy = HLTInfo();
	
	// needed in edanalyzer:
	edm::Service<TFileService> newfs;
	
	// add the tree:
	summaryTree = newfs->make<TTree>("summaryTree", "Summary Event Values");	
	tree_add_branches();
	
}
void OSTwoLepAna::endJob() {

  fclose(el1);
  fclose(el2);
  fclose(el3);
  fclose(ml2);
  fclose(ml3);

  fclose(et1);
  fclose(et2);
  fclose(et3);
  fclose(mt2);
  fclose(mt3);

  //  cout << "Num Events processed " << numEvents << endl;
  //       << "Passed cuts " << numEventsPassCuts << endl;
  //       << "Failed cuts " << numEventsFailCuts << endl;
  
} // job completion (cutflow table, etc.)

void OSTwoLepAna::analyze(const edm::Event& event, const edm::EventSetup& evsetup) // this function is called once at each event
{
	// analysis goes here
	if (debug) cout << "event: " << event.id().event() << endl;

	eventcount++;
	SetupOptions(event);
  
	trigRes triggerResults = 		GetTriggers(event);
	patMuons muons = 			GetMuons(event);
	patJets pfjets = 			GetJets(event);
	patElectrons electrons = 		GetElectrons(event);
	patMETs mets = 				GetMet(event);
	prunedGenParticles prunedParticles = 	GetPrunedGenParticles(event);
	packedGenParticles packedParticles =    GetPackedGenParticles(event);
	
	//this needs to be cleaned up eventually
	recoBeamSpot bsHandle;
	event.getByToken(bsToken_,bsHandle);
	const reco::BeamSpot &beamspot = *bsHandle.product();

	edm::Handle<reco::ConversionCollection> hConversions;
	event.getByToken(conversionToken_,hConversions);
	
	SetRho(rho);
	
	int numpvs =				GetVertices(event);
	
	if (debug) cout << "numpvs: " << numpvs << endl;
		
	edm::Handle<GenEventInfoProduct> GenInfo;
    	event.getByLabel("generator",GenInfo);
    	
	///////////////////////////
	double mcwgt_intree = GenInfo->weight();		// <- gen-level weight
	double weight = 1.;					// <- analysis weight 
	weight *= mcwgt_intree;					// MC-only (flag to be added)
	///////////////////////////
	
	
	initialize_variables();	
			
	/////////
	///
	/// Electrons
	///
	////////
	
	//double minTightLeptonPt = 20.;
	//double minLooseLeptonPt = 10.;
	double minTightLeptonPt = 10.;
	double minLooseLeptonPt = 5.;

	double mintightelept = minTightLeptonPt;
	double minlooseelept = minLooseLeptonPt;

	//double mintightelept = 10.;
	//double minlooseelept = 5.;

	vecPatElectron selectedElectrons_tight = GetSelectedElectrons( *electrons, mintightelept, electronID::electronTight);	//miniAODhelper.
	vecPatElectron selectedElectrons_loose = GetSelectedElectrons( *electrons, minlooseelept, electronID::electronLoose );	//miniAODhelper.
	vecPatElectron selectedElectrons_preselected = GetSelectedElectrons( *electrons, 7., electronID::electronPreselection );	//miniAODhelper.
	vecPatElectron selectedElectrons_raw = GetSelectedElectrons( *electrons, 7., electronID::electronRaw );	//miniAODhelper.
	vecPatElectron selectedElectrons_forcleaning = GetSelectedElectrons( *electrons, 10., electronID::electronPreselection );	//miniAODhelper.
	vecPatElectron selectedElectrons_loose_notight = RemoveOverlaps( selectedElectrons_tight, selectedElectrons_loose);	//miniAODhelper.
	vecPatElectron selectedElectrons_looseCutBased = GetSelectedElectrons( *electrons, 7., electronID::electronLooseCutBased);	//miniAODhelper.

	//special stuff for sync, need to add fancy converstion veto
	//with vtx fit probability which uses beamspon and conversion collections
	//and i'm too lazy to add them to isGoodElectron in MiniAODhelper (temporary)
	vecPatElectron selectedElectrons_tightcb = GetSelectedElectrons( *electrons, 7, electronID::electronTightCutBased);	//miniAODhelper.
	vecPatElectron selectedElectrons_tightCutBased;

	bool allowCkfMatch = true;
	float lxyMin = 2.0;
	float probMin = 1e-6;
	uint nHitsBeforeVtxMax = 0;
	for(const auto & ele: selectedElectrons_tightcb)
	  {
	    if (!ConversionTools::hasMatchedConversion(ele,hConversions,beamspot.position(),allowCkfMatch,lxyMin,probMin,nHitsBeforeVtxMax))
	      {
		selectedElectrons_tightCutBased.push_back(ele);
	      }
	  }

	/////////
	///
	/// Muons
	///
	////////
	double mintightmupt = minTightLeptonPt;
	double minloosemupt = minLooseLeptonPt;

	vecPatMuon selectedMuons_tight = GetSelectedMuons( *muons, mintightmupt, muonID::muonTight );
	vecPatMuon selectedMuons_loose = GetSelectedMuons( *muons, minloosemupt, muonID::muonLoose );
	vecPatMuon selectedMuons_preselected = GetSelectedMuons( *muons, 5., muonID::muonPreselection );
	vecPatMuon selectedMuons_raw = GetSelectedMuons( *muons, 5., muonID::muonRaw );
	vecPatMuon selectedMuons_forcleaning = GetSelectedMuons( *muons, 10., muonID::muonPreselection );
	vecPatMuon selectedMuons_loose_notight = RemoveOverlaps(selectedMuons_tight,selectedMuons_loose);
	vecPatMuon selectedMuons_looseCutBased = GetSelectedMuons( *muons, 5., muonID::muonLooseCutBased );
	vecPatMuon selectedMuons_tightCutBased = GetSelectedMuons( *muons, 5., muonID::muonTightCutBased );

	/////////
	///
	/// Leptons
	///
	////////
	
	selectedElectrons_preselected = cleanObjects<pat::Electron,pat::Muon>(selectedElectrons_preselected,selectedMuons_preselected,0.02); 	//remove electrons that are close (dR <=0.02) to muons
	vecPatLepton selectedLeptons_preselected = fillLeptons(selectedMuons_preselected,selectedElectrons_preselected);
	selectedLeptons_preselected = MiniAODHelper::GetSortedByPt(selectedLeptons_preselected);

	selectedElectrons_loose = cleanObjects<pat::Electron,pat::Muon>(selectedElectrons_loose,selectedMuons_loose,0.02);
	vecPatLepton selectedLeptons_loose = fillLeptons(selectedMuons_loose,selectedElectrons_loose);
	selectedLeptons_loose = MiniAODHelper::GetSortedByPt(selectedLeptons_loose);

	selectedElectrons_tight = cleanObjects<pat::Electron,pat::Muon>(selectedElectrons_tight,selectedMuons_tight,0.02);
	vecPatLepton selectedLeptons_tight = fillLeptons(selectedMuons_tight,selectedElectrons_tight);
	selectedLeptons_tight = MiniAODHelper::GetSortedByPt(selectedLeptons_tight);
	
	vecPatLepton selectedLeptons_looseCutBased = fillLeptons(selectedMuons_looseCutBased,selectedElectrons_looseCutBased);
	selectedLeptons_looseCutBased = MiniAODHelper::GetSortedByPt(selectedLeptons_looseCutBased);

	vecPatLepton selectedLeptons_tightCutBased = fillLeptons(selectedMuons_tightCutBased,selectedElectrons_tightCutBased);
	selectedLeptons_tightCutBased = MiniAODHelper::GetSortedByPt(selectedLeptons_tightCutBased);

	vecPatLepton selectedLeptons_raw = fillLeptons(selectedMuons_raw,selectedElectrons_raw);
	selectedLeptons_raw = MiniAODHelper::GetSortedByPt(selectedLeptons_raw);
	
	vecPatLepton selectedLeptons_forcleaning = fillLeptons(selectedMuons_forcleaning,selectedElectrons_forcleaning);
	
	/////////
	///
	/// Jets
	///
	////////
 	
	vecPatJet rawJets				= GetUncorrectedJets(*pfjets);  					  //miniAODhelper.
	std::vector<pat::Jet> cleaned_rawJets           = cleanObjects<pat::Jet,reco::LeafCandidate>(rawJets,selectedLeptons_forcleaning,0.4);
	vecPatJet jetsNoMu			       	= RemoveOverlaps(selectedMuons_loose, rawJets); 			    //miniAODhelper.
	vecPatJet jetsNoEle			       	= RemoveOverlaps(selectedElectrons_loose, rawJets);			    //miniAODhelper.
	vecPatJet jetsNoLep			       	= RemoveOverlaps(selectedElectrons_loose, jetsNoMu);			    //miniAODhelper.
	vecPatJet correctedJets_noSys		       	= GetCorrectedJets(jetsNoLep);  					    //miniAODhelper.
	vecPatJet selectedJets_noSys_unsorted	       	= GetSelectedJets(correctedJets_noSys, 30., 2.4, jetID::jetLoose, '-' );    //miniAODhelper.
	vecPatJet selectedJets_tag_noSys_unsorted	= GetSelectedJets(correctedJets_noSys, 30., 2.4, jetID::jetLoose, 'M' );   //miniAODhelper.
	vecPatJet selectedJets_loose_noSys_unsorted     = GetSelectedJets(correctedJets_noSys, 20., 2.4, jetID::jetLoose, '-' );    //miniAODhelper.
	vecPatJet selectedJets_loose_tag_noSys_unsorted	= GetSelectedJets(correctedJets_noSys, 20., 2.4, jetID::jetLoose, 'M' );   //miniAODhelper.
	vecPatJet selectedJets_bJetsLoose          	= GetSelectedJets(cleaned_rawJets, 25., 2.4, jetID::jetPU, 'L' );   //miniAODhelper.
	vecPatJet selectedJets_forSync          	= GetSelectedJets(cleaned_rawJets, 25., 2.4, jetID::jetPU, '-' );   //miniAODhelper.
	vecPatJet selectedJets_forLepMVA          	= GetSelectedJets(rawJets, 10., 2.4, jetID::none, '-' );   //miniAODhelper.
	
	// test
	vecPatJet *testHiggsjets  = &selectedJets_noSys_unsorted;
	TwoObjectKinematic<vecPatJet,vecPatJet> myNumHiggsLikeDijet15("mass", "num_within", "numHiggsLike_dijet_15_float", &(testHiggsjets), "jets_by_pt", 1, 99, &(testHiggsjets), "jets_by_pt", 1, 99, 115.0, "", "", 15.0);

	/////////
	///
	/// MET
	///
	////////

	//do anything to pat met here

	/////////////////////////
	//////
	////// fill the collections
	//////
	/////////////////////////

        vector<ttH::Lepton> preselected_leptons = GetCollection(selectedLeptons_preselected);
        vector<ttH::Lepton> loose_leptons = GetCollection(selectedLeptons_loose);
        vector<ttH::Lepton> tight_leptons = GetCollection(selectedLeptons_tight);

	vector<ttH::Lepton> looseCutBased_leptons = GetCollection(selectedLeptons_looseCutBased);
        vector<ttH::Lepton> tightCutBased_leptons = GetCollection(selectedLeptons_tightCutBased);

	vector<ttH::Electron> raw_electrons = GetCollection(selectedElectrons_raw,selectedJets_forLepMVA);
	vector<ttH::Electron> preselected_electrons = GetCollection(selectedElectrons_preselected,selectedJets_forLepMVA);
	vector<ttH::Electron> loose_electrons = GetCollection(selectedElectrons_loose,selectedJets_forLepMVA);
	vector<ttH::Electron> looseCutBased_electrons = GetCollection(selectedElectrons_looseCutBased,selectedJets_forLepMVA);
	vector<ttH::Electron> tight_electrons = GetCollection(selectedElectrons_tight,selectedJets_forLepMVA);
	vector<ttH::Electron> tightCutBased_electrons = GetCollection(selectedElectrons_tightCutBased,selectedJets_forLepMVA);

	vector<ttH::Muon> raw_muons = GetCollection(selectedMuons_raw,selectedJets_forLepMVA);
	vector<ttH::Muon> preselected_muons = GetCollection(selectedMuons_preselected,selectedJets_forLepMVA);
	vector<ttH::Muon> loose_muons = GetCollection(selectedMuons_loose,selectedJets_forLepMVA);
	vector<ttH::Muon> looseCutBased_muons = GetCollection(selectedMuons_looseCutBased,selectedJets_forLepMVA);
	vector<ttH::Muon> tight_muons = GetCollection(selectedMuons_tight,selectedJets_forLepMVA);
	vector<ttH::Muon> tightCutBased_muons = GetCollection(selectedMuons_tightCutBased,selectedJets_forLepMVA);

	vector<ttH::Jet> preselected_jets = GetCollection(selectedJets_forSync);
	vector<ttH::Jet> loose_bJets = GetCollection(selectedJets_bJetsLoose);
	
	vector<ttH::MET> theMET = GetCollection(mets);
	vector<ttH::GenParticle> pruned_genParticles = GetCollection(*prunedParticles);
	
	/////////////////////////
	//////
	////// cut flow studies
	//////
	/////////////////////////
	
	int higgs_daughter1 = GetHiggsDaughterId(*prunedParticles);
	//	int higgs_daughter2 = GetHiggsDaughterId(*prunedParticles,2);
	
	higgs_decay_intree = (higgs_daughter1==24 || higgs_daughter1==23 || higgs_daughter1==15) ? 1 : 0;
	
	eventnum_intree = event.id().event();
	lumiBlock_intree = event.id().luminosityBlock();
	runNumber_intree = event.id().run();
	

	if (looseCutBased_leptons.size() >= 2 && higgs_decay_intree == 1)
	  {
	    fprintf(el1,"%6d %6d %10d  %+2d  %6.2f %+4.2f %+4.2f   %+2d  %6.2f %+4.2f %+4.2f    %6.1f  %+4.2f    %d \n",
		    runNumber_intree, lumiBlock_intree, eventnum_intree,
		    looseCutBased_leptons[0].pdgID, looseCutBased_leptons[0].obj.Pt(), looseCutBased_leptons[0].obj.Eta(), looseCutBased_leptons[0].obj.Phi(),
		    looseCutBased_leptons[1].pdgID, looseCutBased_leptons[1].obj.Pt(), looseCutBased_leptons[1].obj.Eta(), looseCutBased_leptons[1].obj.Phi(),
		    theMET[0].pt_forSync, theMET[0].phi_forSync, int(preselected_jets.size()));
	    if ( looseCutBased_leptons[0].pdgID == looseCutBased_leptons[1].pdgID && abs(looseCutBased_leptons[0].pdgID) == 11)
	      {
		fprintf(el2,"%6d %6d %10d  %+2d  %6.2f %+4.2f %+4.2f   %+2d  %6.2f %+4.2f %+4.2f    %6.1f  %+4.2f    %d \n",
			runNumber_intree, lumiBlock_intree, eventnum_intree,
			looseCutBased_leptons[0].pdgID, looseCutBased_leptons[0].obj.Pt(), looseCutBased_leptons[0].obj.Eta(), looseCutBased_leptons[0].obj.Phi(),
			looseCutBased_leptons[1].pdgID, looseCutBased_leptons[1].obj.Pt(), looseCutBased_leptons[1].obj.Eta(), looseCutBased_leptons[1].obj.Phi(),
			theMET[0].pt_forSync, theMET[0].phi_forSync, int(preselected_jets.size()));
		
		if ( looseCutBased_leptons[0].obj.Pt() > 20 && looseCutBased_leptons[1].obj.Pt() > 20)
		  {
		    fprintf(el3,"%6d %6d %10d  %+2d  %6.2f %+4.2f %+4.2f   %+2d  %6.2f %+4.2f %+4.2f    %6.1f  %+4.2f    %d \n",
			    runNumber_intree, lumiBlock_intree, eventnum_intree,
			    looseCutBased_leptons[0].pdgID, looseCutBased_leptons[0].obj.Pt(), looseCutBased_leptons[0].obj.Eta(), looseCutBased_leptons[0].obj.Phi(),
			    looseCutBased_leptons[1].pdgID, looseCutBased_leptons[1].obj.Pt(), looseCutBased_leptons[1].obj.Eta(), looseCutBased_leptons[1].obj.Phi(),
			    theMET[0].pt_forSync, theMET[0].phi_forSync, int(preselected_jets.size()));
		  }
	      }
	    else if (looseCutBased_leptons[0].pdgID == looseCutBased_leptons[1].pdgID && abs(looseCutBased_leptons[0].pdgID) == 13)
	      {
		fprintf(ml2,"%6d %6d %10d  %+2d  %6.2f %+4.2f %+4.2f   %+2d  %6.2f %+4.2f %+4.2f    %6.1f  %+4.2f    %d \n",
			runNumber_intree, lumiBlock_intree, eventnum_intree,
			looseCutBased_leptons[0].pdgID, looseCutBased_leptons[0].obj.Pt(), looseCutBased_leptons[0].obj.Eta(), looseCutBased_leptons[0].obj.Phi(),
			looseCutBased_leptons[1].pdgID, looseCutBased_leptons[1].obj.Pt(), looseCutBased_leptons[1].obj.Eta(), looseCutBased_leptons[1].obj.Phi(),
			theMET[0].pt_forSync, theMET[0].phi_forSync, int(preselected_jets.size()));
		if (looseCutBased_leptons[0].obj.Pt() > 20 && looseCutBased_leptons[1].obj.Pt() > 20 )
		  {
		    fprintf(ml3,"%6d %6d %10d  %+2d  %6.2f %+4.2f %+4.2f   %+2d  %6.2f %+4.2f %+4.2f    %6.1f  %+4.2f    %d \n",
			    runNumber_intree, lumiBlock_intree, eventnum_intree,
			    looseCutBased_leptons[0].pdgID, looseCutBased_leptons[0].obj.Pt(), looseCutBased_leptons[0].obj.Eta(), looseCutBased_leptons[0].obj.Phi(),
			    looseCutBased_leptons[1].pdgID, looseCutBased_leptons[1].obj.Pt(), looseCutBased_leptons[1].obj.Eta(), looseCutBased_leptons[1].obj.Phi(),
			    theMET[0].pt_forSync, theMET[0].phi_forSync, int(preselected_jets.size()));
		  }
	      }
	  }
	
	
	//tight cut based print outs
	if (tightCutBased_leptons.size() >= 2 && higgs_decay_intree == 1)
	  {
	    fprintf(et1,"%6d %6d %10d  %+2d  %6.2f %+4.2f %+4.2f   %+2d  %6.2f %+4.2f %+4.2f    %6.1f  %+4.2f    %d \n",
		    runNumber_intree, lumiBlock_intree, eventnum_intree,
		    tightCutBased_leptons[0].pdgID, tightCutBased_leptons[0].obj.Pt(), tightCutBased_leptons[0].obj.Eta(), tightCutBased_leptons[0].obj.Phi(),
		    tightCutBased_leptons[1].pdgID, tightCutBased_leptons[1].obj.Pt(), tightCutBased_leptons[1].obj.Eta(), tightCutBased_leptons[1].obj.Phi(),
		    theMET[0].pt_forSync, theMET[0].phi_forSync, int(preselected_jets.size()));
	    if ( tightCutBased_leptons[0].pdgID == tightCutBased_leptons[1].pdgID && abs(tightCutBased_leptons[0].pdgID) == 11)
	      {
		fprintf(et2,"%6d %6d %10d  %+2d  %6.2f %+4.2f %+4.2f   %+2d  %6.2f %+4.2f %+4.2f    %6.1f  %+4.2f    %d \n",
			runNumber_intree, lumiBlock_intree, eventnum_intree,
			tightCutBased_leptons[0].pdgID, tightCutBased_leptons[0].obj.Pt(), tightCutBased_leptons[0].obj.Eta(), tightCutBased_leptons[0].obj.Phi(),
			tightCutBased_leptons[1].pdgID, tightCutBased_leptons[1].obj.Pt(), tightCutBased_leptons[1].obj.Eta(), tightCutBased_leptons[1].obj.Phi(),
			theMET[0].pt_forSync, theMET[0].phi_forSync, int(preselected_jets.size()));
		
		if ( tightCutBased_leptons[0].obj.Pt() > 20 && tightCutBased_leptons[1].obj.Pt() > 20)
		  {
		    fprintf(et3,"%6d %6d %10d  %+2d  %6.2f %+4.2f %+4.2f   %+2d  %6.2f %+4.2f %+4.2f    %6.1f  %+4.2f    %d \n",
			    runNumber_intree, lumiBlock_intree, eventnum_intree,
			    tightCutBased_leptons[0].pdgID, tightCutBased_leptons[0].obj.Pt(), tightCutBased_leptons[0].obj.Eta(), tightCutBased_leptons[0].obj.Phi(),
			    tightCutBased_leptons[1].pdgID, tightCutBased_leptons[1].obj.Pt(), tightCutBased_leptons[1].obj.Eta(), tightCutBased_leptons[1].obj.Phi(),
			    theMET[0].pt_forSync, theMET[0].phi_forSync, int(preselected_jets.size()));
		  }
	      }
	    else if (tightCutBased_leptons[0].pdgID == tightCutBased_leptons[1].pdgID && abs(tightCutBased_leptons[0].pdgID) == 13)
	      {
		fprintf(mt2,"%6d %6d %10d  %+2d  %6.2f %+4.2f %+4.2f   %+2d  %6.2f %+4.2f %+4.2f    %6.1f  %+4.2f    %d \n",
			runNumber_intree, lumiBlock_intree, eventnum_intree,
			tightCutBased_leptons[0].pdgID, tightCutBased_leptons[0].obj.Pt(), tightCutBased_leptons[0].obj.Eta(), tightCutBased_leptons[0].obj.Phi(),
			tightCutBased_leptons[1].pdgID, tightCutBased_leptons[1].obj.Pt(), tightCutBased_leptons[1].obj.Eta(), tightCutBased_leptons[1].obj.Phi(),
			theMET[0].pt_forSync, theMET[0].phi_forSync, int(preselected_jets.size()));
		if (tightCutBased_leptons[0].obj.Pt() > 20 && tightCutBased_leptons[1].obj.Pt() > 20 )
		  {
		    fprintf(mt3,"%6d %6d %10d  %+2d  %6.2f %+4.2f %+4.2f   %+2d  %6.2f %+4.2f %+4.2f    %6.1f  %+4.2f    %d \n",
			    runNumber_intree, lumiBlock_intree, eventnum_intree,
			    tightCutBased_leptons[0].pdgID, tightCutBased_leptons[0].obj.Pt(), tightCutBased_leptons[0].obj.Eta(), tightCutBased_leptons[0].obj.Phi(),
			    tightCutBased_leptons[1].pdgID, tightCutBased_leptons[1].obj.Pt(), tightCutBased_leptons[1].obj.Eta(), tightCutBased_leptons[1].obj.Phi(),
			    theMET[0].pt_forSync, theMET[0].phi_forSync, int(preselected_jets.size()));
		  }
	      }
	  }

	
	myNumHiggsLikeDijet15.evaluate();
	if (myNumHiggsLikeDijet15.myVars.size()) NumHiggsLikeDijet15_intree =  myNumHiggsLikeDijet15.myVars[0].branchVal;
	
        preselected_leptons_intree = preselected_leptons;
        preselected_electrons_intree = preselected_electrons;
        preselected_muons_intree = preselected_muons;

        loose_leptons_intree = looseCutBased_leptons;
        loose_electrons_intree = looseCutBased_electrons;
        loose_muons_intree = looseCutBased_muons;

        tight_leptons_intree = tightCutBased_leptons;
        tight_electrons_intree = tightCutBased_electrons;
        tight_muons_intree = tightCutBased_muons;

	raw_electrons_intree = raw_electrons;
	raw_muons_intree = raw_muons;

	preselected_jets_intree = preselected_jets;
	loose_bJets_intree = loose_bJets;
	
	met_intree = theMET;

	pruned_genParticles_intree = pruned_genParticles;

	wgt_intree = weight;
	
	// fill it:
	summaryTree->Fill();
	
} // end event loop

void OSTwoLepAna::beginRun(edm::Run const& run, edm::EventSetup const& evsetup)
{
		
	// This has to be done here (not at beginjob):
	
	bool changed = true;
	if (hltConfig_.init(run, evsetup, hltTag, changed)) std::cout << "HLT config with process name " << hltTag << " successfully extracted" << std::endl;
	
	else std::cout << "Warning, didn't find process " << hltTag << std::endl;
	
	std::cout << " HLTConfig processName " << hltConfig_.processName() << " tableName " << hltConfig_.tableName() << " size " << hltConfig_.size() << std::endl; // " globalTag: " << hltConfig_.globalTag() << std::endl;
	
}
void OSTwoLepAna::endRun(edm::Run const& run, edm::EventSetup const& evsetup)
{

	cout << "total events processed: " << eventcount << endl;
	
	

} // anything special for the end of a run

void OSTwoLepAna::beginLuminosityBlock(edm::LuminosityBlock const& lumi, edm::EventSetup const& evsetup){} // anything special for the beginning of a lumi block
void OSTwoLepAna::endLuminosityBlock(edm::LuminosityBlock const& lumi, edm::EventSetup const& evsetup){} // anything special for the end of a lumi block


DEFINE_FWK_MODULE(OSTwoLepAna);

//  LocalWords:  chargeFlipC
