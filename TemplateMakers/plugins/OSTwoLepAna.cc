// Created by Geoff Smith

#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/OSTwoLepAna.h"

OSTwoLepAna::OSTwoLepAna(const edm::ParameterSet& constructparams) :
  hltPrescaleProvider_(constructparams, consumesCollector(), *this){ //Anything that needs to be done at creation time
  
  debug = constructparams.getParameter<bool> ("debug");
  entire_pset = constructparams;
  parse_params();
  
  alltriggerstostudy = HLTInfo();
	
  muons_token_ = consumes<pat::MuonCollection>(constructparams.getParameter<edm::InputTag>("muons"));
  electrons_token_ = consumes<pat::ElectronCollection>(constructparams.getParameter<edm::InputTag>("electrons"));
  taus_token_ = consumes<pat::TauCollection>(constructparams.getParameter<edm::InputTag>("taus"));
  triggerResults_token_ = consumes<edm::TriggerResults>(edm::InputTag("TriggerResults","", hltTag));  
  jets_token_ = consumes<pat::JetCollection>(jetparams.getParameter<string>("jetCollection"));
  qg_token_ = consumes<edm::ValueMap<float>>(edm::InputTag("QGTagger", "qgLikelihood"));
  mets_token_ = consumes<pat::METCollection>(metparams.getParameter<string>("METCollection"));
  genParticles_token_ = consumes<reco::GenParticleCollection>(prunedparams.getParameter<string>("prunedCollection"));
  rho_token_ = consumes<double>(setupoptionsparams.getParameter<string>("rhoHandle"));
  vertex_token_ = consumes<reco::VertexCollection>(edm::InputTag("offlineSlimmedPrimaryVertices")); // ,"","RECO"));
  genInfo_token_ = consumes<GenEventInfoProduct>(edm::InputTag("generator"));
  
}

OSTwoLepAna::~OSTwoLepAna(){} //Anything that needs to be done at destruction time

void OSTwoLepAna::beginJob()
{
  
  // job setup	
  SetUp(analysisYear, sampleNumber, analysisType::DIL, isData);
  //  SetFactorizedJetCorrector(); // remove ???
  
  // needed in edanalyzer:
  edm::Service<TFileService> newfs;
  
  // book histos:
  numInitialWeightedMCevents = newfs->make<TH1D>("numInitialWeightedMCevents","numInitialWeightedMCevents",1,1,2);
  
  // add the tree:
  summaryTree = newfs->make<TTree>("summaryTree", "Summary Event Values");	
  tree_add_branches();

  singleEleCount=0;
  singleMuCount=0;
  singleTauCount=0;
  singleJetCount=0;
    
    	
}
void OSTwoLepAna::endJob() {

  //  cout << "Num Events processed " << numEvents << endl;
  //       << "Passed cuts " << numEventsPassCuts << endl;
  //       << "Failed cuts " << numEventsFailCuts << endl;
  
  
  cout << "singleMuCount: " << singleMuCount << endl;
  cout << "singleEleCount: " << singleEleCount << endl;
  cout << "singleTauCount: " << singleTauCount << endl;
  cout << "singleJetCount: " << singleJetCount << endl;
  
  
} // job completion (cutflow table, etc.)

void OSTwoLepAna::analyze(const edm::Event& event, const edm::EventSetup& evsetup) // this function is called once at each event
{
  
  // if ( event.id().event() != 1692766 ) 
  //   {
  //     if (debug) cout << "eventA: " << event.id().event() << endl;
  //     return;
  //   }
  
  // analysis goes here
  //  if (debug) cout << "eventB: " << event.id().event() << endl;
	clock_t startTime = clock();
	eventcount++;
	SetupOptions(event); // chgd
    
    
        // tree vars to default values:
        initialize_variables();
  
	trigRes triggerResults = 		GetTriggers(event);
	auto muons =                    get_collection(event, muons_token_);
	auto electrons =                get_collection(event, electrons_token_);
	auto taus =                     get_collection(event, taus_token_);
	edm::Handle<pat::JetCollection> pfjets = 			    get_collection(event, jets_token_);
	patMETs mets = 				    get_collection(event, mets_token_);
	prunedGenParticles prunedParticles;
	if (!isData) prunedParticles =  get_collection(event, genParticles_token_);

	SetRho(rho);
	
	int numpvs =				GetVertices(event);
        if (numpvs<1) return; // skips event?
	if (debug) cout << "numpvs: " << numpvs << endl;
	
	edm::Handle<GenEventInfoProduct> GenInfo;
	if (!isData) event.getByToken(genInfo_token_,GenInfo);
    	
	///////////////////////////
	if (!isData) mcwgt_intree = GenInfo->weight();		// <- gen-level weight
        
	// make it +/-1!
	mcwgt_intree = mcwgt_intree<0. ? -1. : 1.;        
        
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
	
	//double mintightelept = minTightLeptonPt;
	//double minlooseelept = minLooseLeptonPt;

	double mintightelept = 7.; // lowered for studies
	double minlooseelept = 7.; // lowered for studies

	vecPatElectron selectedElectrons_preselected = GetSelectedElectrons( *electrons, 7., electronID::electronPreselection );	//miniAODhelper.
	vecPatElectron selectedElectrons_loose = GetSelectedElectrons( *electrons, minlooseelept, electronID::electronLoose );	//miniAODhelper.
	vecPatElectron selectedElectrons_raw = GetSelectedElectrons( *electrons, 7., electronID::electronRaw );	//miniAODhelper.


	/////////
	///
	/// Muons
	///
	////////

	//double mintightmupt = minTightLeptonPt;
	//double minloosemupt = minLooseLeptonPt;
        
	double mintightmupt = 5.; // lowered for studies
	double minloosemupt = 5.; // lowered for studies
        

	vecPatMuon selectedMuons_loose = GetSelectedMuons( *muons, minloosemupt, muonID::muonLoose );
	vecPatMuon selectedMuons_preselected = GetSelectedMuons( *muons, 5., muonID::muonPreselection );
	vecPatMuon selectedMuons_raw = GetSelectedMuons( *muons, 5., muonID::muonRaw );
	vecPatMuon selectedMuons_forcleaning = GetSelectedMuons( *muons, 5., muonID::muonPreselection ); // was *muons, 10., muonID::muonPreselection
	//	vecPatMuon selectedMuons_loose_notight = RemoveOverlaps(selectedMuons_tight,selectedMuons_loose);
        
        
        
	/////////
	///
	/// taus
	///
	////////        
        
	vecPatTau selectedTaus_preselected = GetSelectedTaus( *taus, 20., tauID::tauLoose );

	/////////
	///
	/// Cleaning 
	///
	////////
	
	//remove electrons that are close (dR <=0.05) to muons
	selectedElectrons_preselected = cleanObjects<pat::Electron,pat::Muon>(selectedElectrons_preselected,selectedMuons_preselected,0.05); 	

        //remove taus that are close (dR <=0.4) to muons
	selectedTaus_preselected = cleanObjects<pat::Tau,pat::Muon>(selectedTaus_preselected,selectedMuons_preselected,0.4);
        
        //remove taus that are close (dR <=0.4) to electrons
	selectedTaus_preselected = cleanObjects<pat::Tau,pat::Electron>(selectedTaus_preselected,selectedElectrons_preselected,0.4);
        
	vecPatTau selectedTaus_selected = GetSelectedTaus( selectedTaus_preselected, 20., tauID::tauMedium );
	
	/////////
	///
	/// Leptons
	///
	////////	
	
	bool skim_statement = (selectedMuons_preselected.size()+selectedElectrons_preselected.size() >= 2);
	//bool skim_statement = true;
        if ( skim_statement )
        {
            
	  eventnum_intree = event.id().event();
	  lumiBlock_intree = event.id().luminosityBlock();
	  runNumber_intree = event.id().run();
            
	  vecPatLepton selectedLeptons_raw = fillLeptons(selectedMuons_raw,selectedElectrons_raw);
	  selectedLeptons_raw = MiniAODHelper::GetSortedByPt(selectedLeptons_raw);
	  
	  vecPatLepton selectedLeptons_forcleaning = fillLeptons(selectedMuons_forcleaning,selectedElectrons_preselected);
	  
	    /////////
	    ///
	    /// Jets
	    ///
	    ////////
 	
	    //set up JEC
	    //const JetCorrector* corrector = JetCorrector::getJetCorrector( "ak4PFCHSL1L2L3Residual", evsetup );  
	    //MiniAODHelper::SetJetCorrector(corrector);

	    //vecPatJet rawJets = GetUncorrectedJets(*pfjets);

	    //no JEC (?)
	    //	    vecPatJet selectedJets_forLepMVA  = GetSelectedJets(rawJets, 10., 2.4, jetID::none, '-' );
	    //	    vecPatJet cleaned_rawJets  = cleanObjects<pat::Jet,reco::LeafCandidate>(rawJets,selectedLeptons_forcleaning,0.4);
	    
	    //with JEC
	    //vecPatJet correctedRawJets = GetCorrectedJets(rawJets,event,evsetup);
            //no jec
	    vecPatJet correctedRawJets = (*pfjets);
          

	    ///// Grab the QGID 
	    edm::Handle<edm::ValueMap<float>> qgHandle;
	    event.getByToken(qg_token_, qgHandle);
            int jet_counter = 0;
            for(auto jet = pfjets->begin();  jet != pfjets->end(); ++jet)
              {
		edm::RefToBase<pat::Jet> jetRef(edm::Ref<pat::JetCollection> (pfjets, jet - pfjets->begin()));
                float qgLikelihood = (*qgHandle)[jetRef];
		correctedRawJets[jet_counter].addUserFloat("qgid",qgLikelihood);
                jet_counter +=1;
              }

            vecPatJet cleaned_rawJets  = cleanObjects<pat::Jet,reco::LeafCandidate>(correctedRawJets,selectedLeptons_forcleaning,0.4);  // <------
            cleaned_rawJets  = cleanObjects<pat::Jet,pat::Tau>(cleaned_rawJets,selectedTaus_selected,0.4);                // <------
            //vecPatJet cleaned_rawJets_uncor  = cleanObjects<pat::Jet,reco::LeafCandidate>(rawJets,selectedLeptons_forcleaning,0.4);
	    vecPatJet selectedJets_forLepMVA = GetSelectedJets(correctedRawJets, 5., 2.4, jetID::none, '-' );                // was (correctedRawJets, 10., 2.4, jetID::none, '-' );

	    vecPatJet correctedJets_noSys		       	= GetCorrectedJets(cleaned_rawJets);  
            //vecPatJet correctedJets_noSys		       	= cleaned_rawJets;
	    vecPatJet selectedJets_noSys_unsorted	       	= GetSelectedJets(correctedJets_noSys, 30., 2.4, jetID::jetLoose, '-' ); 
	    vecPatJet selectedJets_tag_noSys_unsorted	= GetSelectedJets(correctedJets_noSys, 30., 2.4, jetID::jetLoose, 'M' );
	    vecPatJet selectedJets_loose_noSys_unsorted     = GetSelectedJets(correctedJets_noSys, 20., 2.4, jetID::jetLoose, '-' );
	    vecPatJet selectedJets_loose_tag_noSys_unsorted	= GetSelectedJets(correctedJets_noSys, 20., 2.4, jetID::jetLoose, 'M' );
	    vecPatJet selectedJets_preselected          	= GetSelectedJets(cleaned_rawJets, 25., 2.4, jetID::jetPU, '-' );           // <------
            //vecPatJet selectedJets_preselected_uncor          	= GetSelectedJets(cleaned_rawJets_uncor, 25., 2.4, jetID::jetPU, '-' );
	    vecPatJet selectedJets_bJetsLoose          	= GetSelectedJets(cleaned_rawJets, 25., 2.4, jetID::jetPU, 'L' );
	    vecPatJet selectedJets_bJetsTight          	= GetSelectedJets(cleaned_rawJets, 25., 2.4, jetID::jetPU, 'M' );
	
	    /////////
	    ///
	    /// Filling final selection PAT collections
	    ///
	    ////////

	    auto lepTuple = pickLeptons(selectedMuons_preselected, muonID::muonLooseMvaBased, minloosemupt, selectedElectrons_preselected, electronID::electronLooseMvaBased, minlooseelept);
	    vecPatMuon selectedMuons_looseMvaBased = std::get<0>(lepTuple);
	    vecPatElectron selectedElectrons_looseMvaBased = std::get<1>(lepTuple);

	    lepTuple = pickLeptons(selectedMuons_preselected, muonID::muonTightMvaBased, mintightmupt, selectedElectrons_preselected, electronID::electronTightMvaBased, mintightelept);
	    vecPatMuon selectedMuons_tightMvaBased = std::get<0>(lepTuple);
	    vecPatElectron selectedElectrons_tightMvaBased = std::get<1>(lepTuple);

	    /////////
	    ///
	    /// MET
	    ///
	    ////////

	    //do anything to pat met here


	    /////////
	    ///
	    /// Trigger
	    ///
	    ////////
	    
	    //cout << hlt_alltrigs.size() << endl;
	    
	    // if event passes an HLT path add it to the tree:
	    for (unsigned int trigit=0; trigit<hlt_alltrigs.size(); trigit++)
	      {
		try
		  {
		    if (triggerResults->accept(hltConfig_.triggerIndex(hlt_alltrigs[trigit])))
		      {
			// pair: <L1 prescale, HLT prescale>
			//std::pair<int,int> prescaleVals= hltPrescaleProvider_.prescaleValues(event, evsetup, hlt_alltrigs[trigit]);
			
			// pair: < vector of pairs of (L1 seed, L1 prescale), HLT prescale >
			std::pair<std::vector<std::pair<std::string,int> >,int> prescaleVals = hltPrescaleProvider_.prescaleValuesInDetail(event, evsetup, hlt_alltrigs[trigit]);					
			std::vector<std::pair<std::string,int> > prescaleValsL1 = prescaleVals.first;
			
			if (prescaleVals.second==1) // check if HLT prescale=1
			  {					
			    for (unsigned int trigit2=0; trigit2<prescaleValsL1.size(); trigit2++)
			      {    					        					        					
				if (prescaleValsL1[trigit2].second==1) // check for at least 1 L1 seed that had prescale=1 (in the case of multiple seeds, we are assuming they are in OR!)
				  {
				    passTrigger_intree.push_back(hlt_alltrigs[trigit]);
				    break;
				  }
			      }
			  }
		      }
		  }
		catch(...)
		  {
		    cout << "problem with trigger loop..." << endl;
		    continue;
		    }
		
	      }
	    
	    /////////////////////////
	    //////
	    ////// fill the ttH namespace collections
	    //////
	    /////////////////////////
	    
	    vector<ttH::Electron> raw_electrons = GetCollection(selectedElectrons_raw);
	    vector<ttH::Electron> preselected_electrons = GetCollection(selectedElectrons_preselected);
	    vector<ttH::Electron> looseMvaBased_electrons = GetCollection(selectedElectrons_looseMvaBased);
	    vector<ttH::Electron> tightMvaBased_electrons = GetCollection(selectedElectrons_tightMvaBased);

	    vector<ttH::Muon> raw_muons = GetCollection(selectedMuons_raw);
	    vector<ttH::Muon> preselected_muons = GetCollection(selectedMuons_preselected);
	    vector<ttH::Muon> looseMvaBased_muons = GetCollection(selectedMuons_looseMvaBased);
	    vector<ttH::Muon> tightMvaBased_muons = GetCollection(selectedMuons_tightMvaBased);
            
            vector<ttH::Tau> preselected_taus = GetCollection(selectedTaus_preselected);
            vector<ttH::Tau> selected_taus = GetCollection(selectedTaus_selected);

	    vector<ttH::Lepton> preselected_leptons = GetCollection(preselected_muons,preselected_electrons);
	    vector<ttH::Lepton> looseMvaBased_leptons = GetCollection(looseMvaBased_muons,looseMvaBased_electrons);
	    vector<ttH::Lepton> tightMvaBased_leptons = GetCollection(tightMvaBased_muons,tightMvaBased_electrons);

	    //vector<ttH::Jet> raw_jets = GetCollection(rawJets);
	    vector<ttH::Jet> preselected_jets = GetCollection(selectedJets_preselected);
            //vector<ttH::Jet> preselected_jets_uncor = GetCollection(selectedJets_preselected_uncor); // temporary
	    vector<ttH::Jet> preselected_jets_uncor = preselected_jets; // temporary
            vector<ttH::Jet> loose_bJets = GetCollection(selectedJets_bJetsLoose);
	    vector<ttH::Jet> tight_bJets = GetCollection(selectedJets_bJetsTight);
	
	    vector<ttH::MET> theMET = GetCollection(mets);
	    vector<ttH::GenParticle> pruned_genParticles;
	    if (!isData) pruned_genParticles = GetCollection(*prunedParticles);
	
	    /////////////////////////
	    //////
	    ////// cut flow studies
	    //////
	    /////////////////////////
	
	    
	    if (!isData) 
	    {
	        int higgs_daughter1 = GetHiggsDaughterId(*prunedParticles);
	        //	int higgs_daughter2 = GetHiggsDaughterId(*prunedParticles,2);	
	        higgs_decay_intree = higgs_daughter1;
	    }

            // dumps available tagging algos:
            // for (jetit iJet = selectedJets_preselected.begin(); iJet != selectedJets_preselected.end(); ++iJet)
// 	    {                
//                 // this just dumps all the available taggers.. should be commented out in normal operation!
//                 std::vector<std::pair<std::string, float> > dislist = iJet->getPairDiscri();
//                 for (auto pairit = dislist.begin(); pairit != dislist.end(); ++pairit)
//                 {
//                     cout << pairit->first << "  " << pairit->second << endl;
//                 }
// 	    }
            
            /////////////////////////
	    //////
	    ////// finally, associate the ttH collections
	    ////// with the ones stored in the tree
            //////
	    /////////////////////////
            
            
            if ((preselected_muons.size()>=1)) singleMuCount++;
            if (preselected_electrons.size()>=1) singleEleCount++;
            if (preselected_taus.size()>=1) singleTauCount++;
            if (preselected_jets.size()>=1) singleJetCount++;
            
	    preselected_leptons_intree = preselected_leptons;
	    preselected_electrons_intree = preselected_electrons;
	    preselected_muons_intree = preselected_muons;
	    preselected_taus_intree = preselected_taus;
	    selected_taus_intree = selected_taus;

	    looseMvaBased_muons_intree = looseMvaBased_muons;
	    tightMvaBased_muons_intree = tightMvaBased_muons;
	    looseMvaBased_electrons_intree = looseMvaBased_electrons;
	    tightMvaBased_electrons_intree = tightMvaBased_electrons;
	    looseMvaBased_leptons_intree = looseMvaBased_leptons;
	    tightMvaBased_leptons_intree = tightMvaBased_leptons;

	    raw_electrons_intree = raw_electrons;
	    raw_muons_intree = raw_muons;
	    //    raw_jets_intree = raw_jets;
            
	    preselected_jets_intree = preselected_jets;
	    preselected_jets_uncor_intree = preselected_jets_uncor;
            
            //loose_bJets_intree = loose_bJets;
	    //tight_bJets_intree = tight_bJets;

	    met_intree = theMET;

	    if (!isData) pruned_genParticles_intree = pruned_genParticles;

	    wgt_intree = weight;
	
	    wallTimePerEvent_intree = double( clock() - startTime ) / (double)CLOCKS_PER_SEC;

            /////////////////////////////////
	    summaryTree->Fill();// fill tree;
            /////////////////////////////////
	    
        } //end skim if statement

} // end event loop

void OSTwoLepAna::beginRun(edm::Run const& run, edm::EventSetup const& evsetup)
{
		
	// This has to be done here (not at beginjob):
	
	bool changed = true;
	if (hltConfig_.init(run, evsetup, hltTag, changed)) std::cout << "HLT config with process name " << hltTag << " successfully extracted" << std::endl;
	
	else std::cout << "Warning, didn't find process " << hltTag << std::endl;
	
	std::cout << " HLTConfig processName " << hltConfig_.processName() << " tableName " << hltConfig_.tableName() << " size " << hltConfig_.size() << std::endl; // " globalTag: " << hltConfig_.globalTag() << std::endl;
    
    // also get the L1 + HLT prescales:    
    if (hltPrescaleProvider_.init(run,evsetup,hltTag,changed)) std::cout << "Got L1 + HLT prescales .." << std::endl;
	
	std::vector<std::string> myTriggernames = hltConfig_.triggerNames();
	int triggersize = myTriggernames.size();
	vstring hlt_trigstofind;
	hlt_alltrigs.clear();
	
	// Just MC
	
    // single lep
    
//     hlt_trigstofind.push_back("HLT_IsoMu24_eta2p1_v"); // HLT_IsoMu24_IterTrk02_v1 // HLT_IsoTkMu27_v1 ? //// "to be kept ps'd" ?! not according to google doc...
//     hlt_trigstofind.push_back("HLT_IsoMu27_v"); // HLT_IsoMu24_IterTrk02_v1 // HLT_IsoTkMu27_v1 ? // unps'd
//     hlt_trigstofind.push_back("HLT_IsoTkMu27_v"); // HLT_IsoMu24_IterTrk02_v1 // HLT_IsoTkMu27_v1 ? // unps'd
//     hlt_trigstofind.push_back("HLT_Ele32_eta2p1_WP75_Gsf_v"); // <<---
//     
//     // double lep
//     
//     hlt_trigstofind.push_back("HLT_Mu17_Mu8_DZ_v"); // ps'd (here and data)
//     hlt_trigstofind.push_back("HLT_Mu17_TkMu8_DZ_v"); // ps'd (here and data)
//     hlt_trigstofind.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
//     hlt_trigstofind.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");		
//     hlt_trigstofind.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");		
//     hlt_trigstofind.push_back("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v");
//     hlt_trigstofind.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v");
//             
//     // triple lep
//     
//     hlt_trigstofind.push_back("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v");		
//     hlt_trigstofind.push_back("HLT_TripleMu_12_10_5_v");		
//     hlt_trigstofind.push_back("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v");
//     hlt_trigstofind.push_back("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v");
    
    
    // Data + MC
    
    
    //single lep    
    hlt_trigstofind.push_back("HLT_Ele22_eta2p1_WPLoose_Gsf_v");    //Data
    hlt_trigstofind.push_back("HLT_Ele23_WPLoose_Gsf_v");           //Data
    hlt_trigstofind.push_back("HLT_Ele27_WPLoose_Gsf_v");           //Data
    hlt_trigstofind.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_v");    //Data
    hlt_trigstofind.push_back("HLT_Ele32_eta2p1_WPLoose_Gsf_v");    //Data
    hlt_trigstofind.push_back("HLT_Ele22_eta2p1_WP75_Gsf_v");       //MC
    hlt_trigstofind.push_back("HLT_Ele27_WP85_Gsf_v");              //MC
    hlt_trigstofind.push_back("HLT_Ele27_eta2p1_WP75_Gsf_v");       //MC
    hlt_trigstofind.push_back("HLT_Ele32_eta2p1_WP75_Gsf_v");       //MC
    hlt_trigstofind.push_back("HLT_Ele23_CaloIdL_TrackIdL_IsoVL_v");//MC
    
    
    hlt_trigstofind.push_back("HLT_IsoMu18_v");
    hlt_trigstofind.push_back("HLT_IsoMu20_v");
    hlt_trigstofind.push_back("HLT_IsoMu22_v");
    hlt_trigstofind.push_back("HLT_IsoMu20_eta2p1_v");
    hlt_trigstofind.push_back("HLT_IsoMu24_eta2p1_v");
    hlt_trigstofind.push_back("HLT_IsoMu27_v");
    
    hlt_trigstofind.push_back("HLT_IsoTkMu18_v");
    hlt_trigstofind.push_back("HLT_IsoTkMu20_v");
    hlt_trigstofind.push_back("HLT_IsoTkMu22_v");
    hlt_trigstofind.push_back("HLT_IsoTkMu20_eta2p1_v");
    hlt_trigstofind.push_back("HLT_IsoTkMu24_eta2p1_v");
    hlt_trigstofind.push_back("HLT_IsoTkMu27_v");    
    
    // double lep
    hlt_trigstofind.push_back("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");    // unpsd?    
    hlt_trigstofind.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
    hlt_trigstofind.push_back("HLT_Mu17_Mu8_SameSign_DZ_v");                      // new
    hlt_trigstofind.push_back("HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v");
    hlt_trigstofind.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
    hlt_trigstofind.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v");
    hlt_trigstofind.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");
    hlt_trigstofind.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v");
    hlt_trigstofind.push_back("HLT_Mu20_Mu10_SameSign_DZ_v");
    hlt_trigstofind.push_back("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v");   
    hlt_trigstofind.push_back("HLT_Mu27_TkMu8_v");
    hlt_trigstofind.push_back("HLT_Mu30_TkMu11_v");
    hlt_trigstofind.push_back("HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v");
    hlt_trigstofind.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v");
        
    // triple lep (same)
    hlt_trigstofind.push_back("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v");
    hlt_trigstofind.push_back("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v");
    hlt_trigstofind.push_back("HLT_TripleMu_12_10_5_v");
    hlt_trigstofind.push_back("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v");
    
    // for the met dataset:
    hlt_trigstofind.push_back("HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight_BTagCSV0p72_v");
    hlt_trigstofind.push_back("HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight_v");
    hlt_trigstofind.push_back("HLT_MET200_JetIdCleaned_v");
    hlt_trigstofind.push_back("HLT_MET250_v");
    hlt_trigstofind.push_back("HLT_MET300_v");
    hlt_trigstofind.push_back("HLT_MET60_IsoTrk35_Loose_v");
    hlt_trigstofind.push_back("HLT_MET75_IsoTrk50_v");
    hlt_trigstofind.push_back("HLT_MET90_IsoTrk50_v");
    hlt_trigstofind.push_back("HLT_MonoCentralPFJet80_PFMETNoMu120_JetIdCleaned_PFMHTNoMu120_IDTight_v");
    hlt_trigstofind.push_back("HLT_MonoCentralPFJet80_PFMETNoMu90_JetIdCleaned_PFMHTNoMu90_IDTight_v");
    hlt_trigstofind.push_back("HLT_Mu14er_PFMET100_JetIdCleaned_v");
    hlt_trigstofind.push_back("HLT_Mu3er_PFHT140_PFMET125_JetIdCleaned_v");
    hlt_trigstofind.push_back("HLT_Mu6_PFHT200_PFMET100_JetIdCleaned_v");
    hlt_trigstofind.push_back("HLT_Mu6_PFHT200_PFMET80_JetIdCleaned_BTagCSV0p72_v");
    hlt_trigstofind.push_back("HLT_PFMET100_PFMHT100_IDTight_v");
    hlt_trigstofind.push_back("HLT_PFMET110_PFMHT110_IDTight_v");
    hlt_trigstofind.push_back("HLT_PFMET120_JetIdCleaned_BTagCSV0p72_v");
    hlt_trigstofind.push_back("HLT_PFMET120_JetIdCleaned_Mu5_v");
    hlt_trigstofind.push_back("HLT_PFMET120_PFMHT120_IDTight_v");
    hlt_trigstofind.push_back("HLT_PFMET170_HBHECleaned_v");
    hlt_trigstofind.push_back("HLT_PFMET170_JetIdCleaned_v");
    hlt_trigstofind.push_back("HLT_PFMET170_NoiseCleaned_v");
    hlt_trigstofind.push_back("HLT_PFMET170_v");
    hlt_trigstofind.push_back("HLT_PFMET300_JetIdCleaned_v");
    hlt_trigstofind.push_back("HLT_PFMET400_JetIdCleaned_v");
    hlt_trigstofind.push_back("HLT_PFMET90_PFMHT90_IDTight_v");
    hlt_trigstofind.push_back("HLT_PFMETNoMu120_JetIdCleaned_PFMHTNoMu120_IDTight_v");
    hlt_trigstofind.push_back("HLT_PFMETNoMu90_JetIdCleaned_PFMHTNoMu90_IDTight_v");
    
    
    
    
    for (int trigit=0; trigit<triggersize; trigit++)
	{
        if (debug) cout << myTriggernames[trigit] << endl;
        
        for (unsigned int trigit2=0; trigit2<hlt_trigstofind.size(); trigit2++)
	    {
            std::size_t found = myTriggernames[trigit].find(hlt_trigstofind[trigit2]);
            if (found!=std::string::npos)
            {
                hlt_alltrigs.push_back(myTriggernames[trigit]);
            }
        }
    }
                
	
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
