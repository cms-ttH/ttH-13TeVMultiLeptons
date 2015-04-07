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

  if (debug)
    {
      lep1 = fopen ("lep1.txt", "w+");
      el2 = fopen ("ele_2.txt", "w+");
      el3 = fopen ("ele_3.txt", "w+");
      el4 = fopen ("ele_4.txt", "w+");
      ml2 = fopen ("mu_2.txt", "w+");
      ml3 = fopen ("mu_3.txt", "w+");
      ml4 = fopen ("mu_4.txt", "w+");

      fout.open("preselEventDump.csv");
      string header[19] = {"event","pdgId","pT","Eta","Phi","dxy","dz","relIso","sip3D","prompt MVA",
			   "ele MVA ID / isPFMuon","lost hits / isGlobalMuon","isGsfCtfScPixChargeConsistent / chargeFlip",
			   "passConversionVeto / isTrackerMuon","global normalized chi2","chi2 local","track kink","valid Frac",
			   "segment compatibility"};
      for (const auto & title : header) fout << title << ',';
      fout << "\n";
    }
	// job setup	
	sampleNumber = convertSampleNameToNumber(sampleName);
	SetUp(analysisYear, sampleNumber, analysisType::DIL, isData);
	SetFactorizedJetCorrector();
	setupMva();
	alltriggerstostudy = HLTInfo();
	
	// needed in edanalyzer:
	edm::Service<TFileService> newfs;
	
        // book histos:
        numInitialWeightedMCevents = newfs->make<TH1D>("numInitialWeightedMCevents","numInitialWeightedMCevents",1,1,2);
	
        // add the tree:
	summaryTree = newfs->make<TTree>("summaryTree", "Summary Event Values");	
	tree_add_branches();
	
}
void OSTwoLepAna::endJob() {

  if (debug)
    {
      fout.close();
      fclose(lep1);
      fclose(el2);
      fclose(el3);
      fclose(el4);
      fclose(ml2);
      fclose(ml3);
      fclose(ml4);
    }
  //  cout << "Num Events processed " << numEvents << endl;
  //       << "Passed cuts " << numEventsPassCuts << endl;
  //       << "Failed cuts " << numEventsFailCuts << endl;
  
} // job completion (cutflow table, etc.)

void OSTwoLepAna::analyze(const edm::Event& event, const edm::EventSetup& evsetup) // this function is called once at each event
{
  
	// analysis goes here
	//if (debug) cout << "event: " << event.id().event() << endl;
	clock_t startTime = clock();
	eventcount++;
	SetupOptions(event);
        
        // tree vars to default values:
        initialize_variables();
  
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
	
	if (false) cout << "numpvs: " << numpvs << endl;
		
	edm::Handle<GenEventInfoProduct> GenInfo;
    	event.getByLabel("generator",GenInfo);
    	
	///////////////////////////
	double mcwgt_intree = GenInfo->weight();		// <- gen-level weight
	double weight = 1.;					// <- analysis weight 
	weight *= mcwgt_intree;					// MC-only (flag to be added if nec)
	///////////////////////////
	
        // count number of weighted mc events we started with:
        numInitialWeightedMCevents->Fill(1,mcwgt_intree);
					
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

	vecPatElectron selectedElectrons_preselected = GetSelectedElectrons( *electrons, 7., electronID::electronPreselection );	//miniAODhelper.
	vecPatElectron selectedElectrons_tight = GetSelectedElectrons( *electrons, mintightelept, electronID::electronTight);	//miniAODhelper.
	vecPatElectron selectedElectrons_loose = GetSelectedElectrons( *electrons, minlooseelept, electronID::electronLoose );	//miniAODhelper.
	vecPatElectron selectedElectrons_raw = GetSelectedElectrons( *electrons, 7., electronID::electronRaw );	//miniAODhelper.
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
	/// Cleaning 
	///
	////////

	
	selectedElectrons_preselected = cleanObjects<pat::Electron,pat::Muon>(selectedElectrons_preselected,selectedMuons_preselected,0.05); 	//remove electrons that are close (dR <=0.05) to muons
	//make sure the electrons used for jet cleaning are already cleaned of muons
	vecPatElectron selectedElectrons_forcleaning = GetSelectedElectrons(selectedElectrons_preselected, 10., electronID::electronPreselection);

	vecPatElectron selectedElectrons_cutBased = GetSelectedElectrons(selectedElectrons_preselected, 10., electronID::electronCutBased);
	vecPatMuon selectedMuons_cutBased = GetSelectedMuons(selectedMuons_preselected, 5., muonID::muonCutBased);

	/////////
	///
	/// Leptons
	///
	////////	
	
	//saves time by skipping the rest of the loop if <= 2 preselected leptons
	if (selectedMuons_preselected.size()+selectedElectrons_preselected.size() >= 2)
	  {

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
	    vecPatJet selectedJets_forSync          	= GetSelectedJets(cleaned_rawJets, 25., 2.4, jetID::jetPU, '-' );   //miniAODhelper.
	    vecPatJet selectedJets_bJetsLoose          	= GetSelectedJets(cleaned_rawJets, 25., 2.4, jetID::jetPU, 'L' );   //miniAODhelper.
	    vecPatJet selectedJets_bJetsTight          	= GetSelectedJets(cleaned_rawJets, 25., 2.4, jetID::jetPU, 'M' );   //miniAODhelper.
	    vecPatJet selectedJets_forLepMVA          	= GetSelectedJets(rawJets, 10., 2.4, jetID::none, '-' );   //miniAODhelper.
	
	    // test
	    vecPatJet *testHiggsjets  = &selectedJets_noSys_unsorted;
	    TwoObjectKinematic<vecPatJet,vecPatJet> myNumHiggsLikeDijet15("mass", "num_within", "numHiggsLike_dijet_15_float", &(testHiggsjets), "jets_by_pt", 1, 99, &(testHiggsjets), "jets_by_pt", 1, 99, 115.0, "", "", 15.0);

	    /////////
	    ///
	    /// Filling final selection collections
	    ///
	    ////////

	    vecPatElectron selectedElectrons_looseMvaBased = GetSelectedElectrons(selectedElectrons_preselected, 10., electronID::electronLooseMvaBased, selectedJets_forLepMVA);
	    vecPatElectron selectedElectrons_tightMvaBased = GetSelectedElectrons(selectedElectrons_preselected, 10., electronID::electronTightMvaBased, selectedJets_forLepMVA);

	    vecPatMuon selectedMuons_looseMvaBased = GetSelectedMuons(selectedMuons_preselected, 5., muonID::muonLooseMvaBased, selectedJets_forLepMVA);
	    vecPatMuon selectedMuons_tightMvaBased = GetSelectedMuons(selectedMuons_preselected, 5., muonID::muonTightMvaBased, selectedJets_forLepMVA);

	    //2lss final state cuts
	    
	    //cutBased
	    if (selectedElectrons_cutBased.size() == 2 && selectedMuons_cutBased.size() == 0) selectedElectrons_cutBased = GetSelectedElectrons(selectedElectrons_cutBased, 10., electronID::electron2lss); 
	    else if (selectedMuons_cutBased.size() == 2 && selectedElectrons_cutBased.size() == 0) selectedMuons_cutBased = GetSelectedMuons(selectedMuons_cutBased, 5., muonID::muon2lss);
	    
	    //looseMvaBased
	    if (selectedElectrons_looseMvaBased.size() == 2 && selectedMuons_looseMvaBased.size() == 0) selectedElectrons_looseMvaBased = GetSelectedElectrons(selectedElectrons_looseMvaBased, 10., electronID::electron2lss); 
	    else if (selectedMuons_looseMvaBased.size() == 2 && selectedElectrons_looseMvaBased.size() == 0) selectedMuons_looseMvaBased = GetSelectedMuons(selectedMuons_looseMvaBased, 5., muonID::muon2lss);

	    //tightMvaBased
	    if (selectedElectrons_tightMvaBased.size() == 2 && selectedMuons_tightMvaBased.size() == 0) selectedElectrons_tightMvaBased = GetSelectedElectrons(selectedElectrons_tightMvaBased, 10., electronID::electron2lss); 
	    else if (selectedMuons_tightMvaBased.size() == 2 && selectedElectrons_tightMvaBased.size() == 0) selectedMuons_tightMvaBased = GetSelectedMuons(selectedMuons_tightMvaBased, 5., muonID::muon2lss);
	    
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

	    vector<ttH::Electron> raw_electrons = GetCollection(selectedElectrons_raw,selectedJets_forLepMVA);
	    vector<ttH::Electron> preselected_electrons = GetCollection(selectedElectrons_preselected,selectedJets_forLepMVA);
	    vector<ttH::Electron> cutBased_electrons = GetCollection(selectedElectrons_cutBased,selectedJets_forLepMVA);
	    vector<ttH::Electron> looseMvaBased_electrons = GetCollection(selectedElectrons_looseMvaBased,selectedJets_forLepMVA);
	    vector<ttH::Electron> tightMvaBased_electrons = GetCollection(selectedElectrons_tightMvaBased,selectedJets_forLepMVA);

	    vector<ttH::Muon> raw_muons = GetCollection(selectedMuons_raw,selectedJets_forLepMVA);
	    vector<ttH::Muon> preselected_muons = GetCollection(selectedMuons_preselected,selectedJets_forLepMVA);
	    vector<ttH::Muon> cutBased_muons = GetCollection(selectedMuons_cutBased,selectedJets_forLepMVA);
	    vector<ttH::Muon> looseMvaBased_muons = GetCollection(selectedMuons_looseMvaBased,selectedJets_forLepMVA);
	    vector<ttH::Muon> tightMvaBased_muons = GetCollection(selectedMuons_tightMvaBased,selectedJets_forLepMVA);

	    vector<ttH::Lepton> preselected_leptons = GetCollection(preselected_muons,preselected_electrons);
	    vector<ttH::Lepton> cutBased_leptons = GetCollection(cutBased_muons,cutBased_electrons);
	    vector<ttH::Lepton> looseMvaBased_leptons = GetCollection(looseMvaBased_muons,looseMvaBased_electrons);
	    vector<ttH::Lepton> tightMvaBased_leptons = GetCollection(tightMvaBased_muons,tightMvaBased_electrons);

	    vector<ttH::Jet> preselected_jets = GetCollection(selectedJets_forSync);
	    vector<ttH::Jet> loose_bJets = GetCollection(selectedJets_bJetsLoose);
	    vector<ttH::Jet> tight_bJets = GetCollection(selectedJets_bJetsTight);
	
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
	    
	    if (debug){
	      for (const auto & ele : preselected_electrons)
		{
		  fout << eventnum_intree << ','<< ele.pdgID << ','<< ele.obj.Pt() <<','
		       << ele.obj.Eta() <<','<< ele.obj.Phi() <<','<< ele.dxy<<','<<ele.dz<<','
		       <<ele.relIso<<','<<ele.sip3D<<','<<ele.lepMVA<<','<<ele.mvaID<<','
		       <<ele.numMissingInnerHits<<','<<ele.isGsfCtfScPixChargeConsistent<<','<<ele.passConversioVeto<<'\n';
		}
	      for (const auto & mu : preselected_muons)
		{
		  fout << eventnum_intree << ','<<mu.pdgID<<','<<mu.obj.Pt()<<','<<mu.obj.Eta()<<','<<mu.obj.Phi()<<','
		       <<mu.dxy<<','<<mu.dz<<','<<mu.relIso<<','<<mu.sip3D<<','<<mu.lepMVA<<','<<mu.isPFMuon<<','
		       <<mu.isGlobalMuon<<','<<mu.chargeFlip<<','<<mu.isTrackerMuon<<','<<mu.normalizedChi2<<','
		       <<mu.localChi2<<','<<mu.trKink<<','<<mu.validFrac<<','<<mu.segCompatibility<<'\n';
		}


	      if (preselected_leptons.size() >= 2 && higgs_decay_intree == 1)
		{
		  fprintf(lep1,"%6d %6d %10d  %+2d  %6.2f %+4.2f %+4.2f   %+2d  %6.2f %+4.2f %+4.2f    %6.1f  %+4.2f    %d \n",
			  runNumber_intree, lumiBlock_intree, eventnum_intree,
			  preselected_leptons[0].pdgID, preselected_leptons[0].obj.Pt(), preselected_leptons[0].obj.Eta(), preselected_leptons[0].obj.Phi(),
			  preselected_leptons[1].pdgID, preselected_leptons[1].obj.Pt(), preselected_leptons[1].obj.Eta(), preselected_leptons[1].obj.Phi(),
			theMET[0].pt_forSync, theMET[0].phi_forSync, int(preselected_jets.size()));
		  if ( preselected_leptons[0].pdgID == preselected_leptons[1].pdgID && abs(preselected_leptons[0].pdgID) == 11)
		    {
		      fprintf(el2,"%6d %6d %10d  %+2d  %6.2f %+4.2f %+4.2f   %+2d  %6.2f %+4.2f %+4.2f    %6.1f  %+4.2f    %d \n",
			      runNumber_intree, lumiBlock_intree, eventnum_intree,
			      preselected_leptons[0].pdgID, preselected_leptons[0].obj.Pt(), preselected_leptons[0].obj.Eta(), preselected_leptons[0].obj.Phi(),
			      preselected_leptons[1].pdgID, preselected_leptons[1].obj.Pt(), preselected_leptons[1].obj.Eta(), preselected_leptons[1].obj.Phi(),
			      theMET[0].pt_forSync, theMET[0].phi_forSync, int(preselected_jets.size()));
		
		      if ( preselected_leptons[0].obj.Pt() > 20 && preselected_leptons[1].obj.Pt() > 20)
			{
			  fprintf(el3,"%6d %6d %10d  %+2d  %6.2f %+4.2f %+4.2f   %+2d  %6.2f %+4.2f %+4.2f    %6.1f  %+4.2f    %d \n",
				  runNumber_intree, lumiBlock_intree, eventnum_intree,
				  preselected_leptons[0].pdgID, preselected_leptons[0].obj.Pt(), preselected_leptons[0].obj.Eta(), preselected_leptons[0].obj.Phi(),
				  preselected_leptons[1].pdgID, preselected_leptons[1].obj.Pt(), preselected_leptons[1].obj.Eta(), preselected_leptons[1].obj.Phi(),
				  theMET[0].pt_forSync, theMET[0].phi_forSync, int(preselected_jets.size()));
			  if (cutBased_leptons.size() ==2 && cutBased_electrons[0].isGsfCtfScPixChargeConsistent && cutBased_electrons[1].isGsfCtfScPixChargeConsistent){
			    fprintf(el4,"%6d %6d %10d  %+2d  %6.2f %+4.2f %+4.2f   %+2d  %6.2f %+4.2f %+4.2f    %6.1f  %+4.2f    %d \n",
				    runNumber_intree, lumiBlock_intree, eventnum_intree,
				    cutBased_leptons[0].pdgID, cutBased_leptons[0].obj.Pt(), cutBased_leptons[0].obj.Eta(), cutBased_leptons[0].obj.Phi(),
				    cutBased_leptons[1].pdgID, cutBased_leptons[1].obj.Pt(), cutBased_leptons[1].obj.Eta(), cutBased_leptons[1].obj.Phi(),
				    theMET[0].pt_forSync, theMET[0].phi_forSync, int(preselected_jets.size()));
			  }
			}
		    }
		  else if (preselected_leptons[0].pdgID == preselected_leptons[1].pdgID && abs(preselected_leptons[0].pdgID) == 13)
		    {
		      fprintf(ml2,"%6d %6d %10d  %+2d  %6.2f %+4.2f %+4.2f   %+2d  %6.2f %+4.2f %+4.2f    %6.1f  %+4.2f    %d \n",
			      runNumber_intree, lumiBlock_intree, eventnum_intree,
			      preselected_leptons[0].pdgID, preselected_leptons[0].obj.Pt(), preselected_leptons[0].obj.Eta(), preselected_leptons[0].obj.Phi(),
			      preselected_leptons[1].pdgID, preselected_leptons[1].obj.Pt(), preselected_leptons[1].obj.Eta(), preselected_leptons[1].obj.Phi(),
			      theMET[0].pt_forSync, theMET[0].phi_forSync, int(preselected_jets.size()));
		      if (preselected_leptons[0].obj.Pt() > 20 && preselected_leptons[1].obj.Pt() > 20 )
			{
			  fprintf(ml3,"%6d %6d %10d  %+2d  %6.2f %+4.2f %+4.2f   %+2d  %6.2f %+4.2f %+4.2f    %6.1f  %+4.2f    %d \n",
				  runNumber_intree, lumiBlock_intree, eventnum_intree,
				  preselected_leptons[0].pdgID, preselected_leptons[0].obj.Pt(), preselected_leptons[0].obj.Eta(), preselected_leptons[0].obj.Phi(),
				  preselected_leptons[1].pdgID, preselected_leptons[1].obj.Pt(), preselected_leptons[1].obj.Eta(), preselected_leptons[1].obj.Phi(),
				  theMET[0].pt_forSync, theMET[0].phi_forSync, int(preselected_jets.size()));
			  if (cutBased_leptons.size() ==2 && cutBased_muons[0].chargeFlip < 0.2 && cutBased_muons[1].chargeFlip < 0.2){
			    fprintf(ml4,"%6d %6d %10d  %+2d  %6.2f %+4.2f %+4.2f   %+2d  %6.2f %+4.2f %+4.2f    %6.1f  %+4.2f    %d \n",
				    runNumber_intree, lumiBlock_intree, eventnum_intree,
				    cutBased_leptons[0].pdgID, cutBased_leptons[0].obj.Pt(), cutBased_leptons[0].obj.Eta(), cutBased_leptons[0].obj.Phi(),
				    cutBased_leptons[1].pdgID, cutBased_leptons[1].obj.Pt(), cutBased_leptons[1].obj.Eta(), cutBased_leptons[1].obj.Phi(),
				    theMET[0].pt_forSync, theMET[0].phi_forSync, int(preselected_jets.size()));
			  }
			}
		    }
		}
	    }
	    
	    preselected_leptons_intree = preselected_leptons;
	    preselected_electrons_intree = preselected_electrons;
	    preselected_muons_intree = preselected_muons;

	    cutBased_leptons_intree = cutBased_leptons;
	    cutBased_electrons_intree = cutBased_electrons;
	    cutBased_muons_intree = cutBased_muons;

	    looseMvaBased_muons_intree = looseMvaBased_muons;
	    tightMvaBased_muons_intree = tightMvaBased_muons;
	    looseMvaBased_electrons_intree = looseMvaBased_electrons;
	    tightMvaBased_electrons_intree = tightMvaBased_electrons;
	    looseMvaBased_leptons_intree = looseMvaBased_leptons;
	    tightMvaBased_leptons_intree = tightMvaBased_leptons;

	    raw_electrons_intree = raw_electrons;
	    raw_muons_intree = raw_muons;

	    preselected_jets_intree = preselected_jets;
	    loose_bJets_intree = loose_bJets;
	    tight_bJets_intree = tight_bJets;

	    met_intree = theMET;

	    pruned_genParticles_intree = pruned_genParticles;

	    wgt_intree = weight;
	
	    wallTimePerEvent_intree = double( clock() - startTime ) / (double)CLOCKS_PER_SEC;

	    summaryTree->Fill();// fill tree;
	    
	  }

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
}
// anything special for the end of a run

void OSTwoLepAna::beginLuminosityBlock(edm::LuminosityBlock const& lumi, edm::EventSetup const& evsetup){} // anything special for the beginning of a lumi block
void OSTwoLepAna::endLuminosityBlock(edm::LuminosityBlock const& lumi, edm::EventSetup const& evsetup){} // anything special for the end of a lumi block


DEFINE_FWK_MODULE(OSTwoLepAna);

//  LocalWords:  chargeFlipC
