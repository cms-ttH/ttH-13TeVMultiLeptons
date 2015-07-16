// Created by Geoff Smith

#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/OSTwoLepAna.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/EGammaMvaEleEstimatorFWLite.h"

OSTwoLepAna::OSTwoLepAna(const edm::ParameterSet& constructparams){ //Anything that needs to be done at creation time
	debug = constructparams.getParameter<bool> ("debug");
	entire_pset = constructparams;
	parse_params();

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
      string header[35] = {"event","pdgId","pT","Eta","Phi","dxy","dz","relIso","sip3D","prompt MVA",
			   "ele MVA ID / isPFMuon","lost hits / isGlobalMuon","isGsfCtfScPixChargeConsistent / chargeFlip",
			   "passConversionVeto / isTrackerMuon","global normalized chi2","chi2 local","track kink","valid Frac",
			   "segment compatibility"," ","neuRelIso03","chRelIso03","jetDR,lep.pt()","lep.jet.pt()","jetPtRatio","jetBTagCSV",
			   "sip3d","dxy","dz","mvaIdPhys14 / segmentCompatibility",">= 2 preselected leptons","el el SS/mu mu SS","pt2020",
			   "2 cut-selection leptons","== 2 ss tight eles"};
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
	patPackedCands packedCands         =    GetPackedPFCandidates(event);

	//set candidates for mini Iso
	for (const auto & mu : *muons) addVetos(mu);
	for (const auto & ele : *electrons) addVetos(ele);
	SetPackedCandidates(*packedCands);

	SetRho(rho);
	
	int numpvs =				GetVertices(event);
	
	if (false) cout << "numpvs: " << numpvs << endl;
	
	edm::Handle<GenEventInfoProduct> GenInfo;
    	event.getByLabel("generator",GenInfo);
    	
	///////////////////////////
	mcwgt_intree = GenInfo->weight();		// <- gen-level weight
        
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
	
	//double minTightLeptonPt = 20.;
	//double minLooseLeptonPt = 10.;
	
        //double minTightLeptonPt = 10.;
	//double minLooseLeptonPt = 5.;
                
	//double mintightelept = minTightLeptonPt;
	//double minlooseelept = minLooseLeptonPt;

	double mintightelept = 7.; // lowered for studies
	double minlooseelept = 7.; // lowered for studies

	vecPatElectron selectedElectrons_preselected = GetSelectedElectrons( *electrons, 7., electronID::electronPreselection );	//miniAODhelper.
	vecPatElectron selectedElectrons_tight = GetSelectedElectrons( *electrons, mintightelept, electronID::electronTight);	//miniAODhelper.
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
        

	vecPatMuon selectedMuons_tight = GetSelectedMuons( *muons, mintightmupt, muonID::muonTight );
	vecPatMuon selectedMuons_loose = GetSelectedMuons( *muons, minloosemupt, muonID::muonLoose );
	vecPatMuon selectedMuons_preselected = GetSelectedMuons( *muons, 5., muonID::muonPreselection );
	vecPatMuon selectedMuons_raw = GetSelectedMuons( *muons, 5., muonID::muonRaw );
	vecPatMuon selectedMuons_forcleaning = GetSelectedMuons( *muons, 5., muonID::muonPreselection ); // was *muons, 10., muonID::muonPreselection
	//	vecPatMuon selectedMuons_loose_notight = RemoveOverlaps(selectedMuons_tight,selectedMuons_loose);

	/////////
	///
	/// Cleaning 
	///
	////////

	//remove electrons that are close (dR <=0.05) to muons
	selectedElectrons_preselected = cleanObjects<pat::Electron,pat::Muon>(selectedElectrons_preselected,selectedMuons_preselected,0.05); 	

	//make sure the electrons used for jet cleaning are already cleaned of muons
	vecPatElectron selectedElectrons_forcleaning = GetSelectedElectrons(selectedElectrons_preselected, 7., electronID::electronPreselection); // was selectedElectrons_preselected, 10., electronID::electronPreselection

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
 	
	    //set up JEC
	    const JetCorrector* corrector = JetCorrector::getJetCorrector( "ak4PFchsL1L2L3", evsetup );  
	    MiniAODHelper::SetJetCorrector(corrector);

	    vecPatJet rawJets = GetUncorrectedJets(*pfjets);

	    //no JEC
	    //	    vecPatJet selectedJets_forLepMVA  = GetSelectedJets(rawJets, 10., 2.4, jetID::none, '-' );
	    //	    vecPatJet cleaned_rawJets  = cleanObjects<pat::Jet,reco::LeafCandidate>(rawJets,selectedLeptons_forcleaning,0.4);
	    
	    //with JEC
	    vecPatJet correctedRawJets = GetCorrectedJets(rawJets,event,evsetup);
	    vecPatJet cleaned_rawJets  = cleanObjects<pat::Jet,reco::LeafCandidate>(correctedRawJets,selectedLeptons_forcleaning,0.4);
            vecPatJet cleaned_rawJets_uncor  = cleanObjects<pat::Jet,reco::LeafCandidate>(rawJets,selectedLeptons_forcleaning,0.4);
	    vecPatJet selectedJets_forLepMVA = GetSelectedJets(correctedRawJets, 5., 2.4, jetID::none, '-' );                                  // was (correctedRawJets, 10., 2.4, jetID::none, '-' );

	    vecPatJet correctedJets_noSys		       	= GetCorrectedJets(cleaned_rawJets);  					 
	    vecPatJet selectedJets_noSys_unsorted	       	= GetSelectedJets(correctedJets_noSys, 30., 2.4, jetID::jetLoose, '-' ); 
	    vecPatJet selectedJets_tag_noSys_unsorted	= GetSelectedJets(correctedJets_noSys, 30., 2.4, jetID::jetLoose, 'M' );
	    vecPatJet selectedJets_loose_noSys_unsorted     = GetSelectedJets(correctedJets_noSys, 20., 2.4, jetID::jetLoose, '-' );
	    vecPatJet selectedJets_loose_tag_noSys_unsorted	= GetSelectedJets(correctedJets_noSys, 20., 2.4, jetID::jetLoose, 'M' );
	    vecPatJet selectedJets_preselected          	= GetSelectedJets(cleaned_rawJets, 25., 2.4, jetID::jetPU, '-' );
            vecPatJet selectedJets_preselected_uncor          	= GetSelectedJets(cleaned_rawJets_uncor, 25., 2.4, jetID::jetPU, '-' );
	    vecPatJet selectedJets_bJetsLoose          	= GetSelectedJets(cleaned_rawJets, 25., 2.4, jetID::jetPU, 'L' );
	    vecPatJet selectedJets_bJetsTight          	= GetSelectedJets(cleaned_rawJets, 25., 2.4, jetID::jetPU, 'M' );
	
	    // test
	    vecPatJet *testHiggsjets  = &selectedJets_noSys_unsorted;
	    TwoObjectKinematic<vecPatJet,vecPatJet> myNumHiggsLikeDijet15("mass", "num_within", "numHiggsLike_dijet_15_float", &(testHiggsjets), "jets_by_pt", 1, 99, &(testHiggsjets), "jets_by_pt", 1, 99, 115.0, "", "", 15.0);

	    /////////
	    ///
	    /// Filling final selection PAT collections
	    ///
	    ////////

	    auto lepTuple = pickLeptons(selectedMuons_preselected, muonID::muonLooseMvaBased, minloosemupt, selectedElectrons_preselected, electronID::electronLooseMvaBased, minlooseelept, selectedJets_forLepMVA);
	    vecPatMuon selectedMuons_looseMvaBased = std::get<0>(lepTuple);
	    vecPatElectron selectedElectrons_looseMvaBased = std::get<1>(lepTuple);

	    lepTuple = pickLeptons(selectedMuons_preselected, muonID::muonTightMvaBased, mintightmupt, selectedElectrons_preselected, electronID::electronTightMvaBased, mintightelept, selectedJets_forLepMVA);
	    vecPatMuon selectedMuons_tightMvaBased = std::get<0>(lepTuple);
	    vecPatElectron selectedElectrons_tightMvaBased = std::get<1>(lepTuple);



	    //2lss final state cuts FOR OBJ SYNCHRONIZATION ONLY
	    // vecPatLepton selectedLeptons_looseMvaBased = fillLeptons(selectedMuons_looseMvaBased,selectedElectrons_looseMvaBased);
	    // vecPatLepton selectedLeptons_tightMvaBased = fillLeptons(selectedMuons_tightMvaBased,selectedElectrons_tightMvaBased);

	    // //looseMvaBased
	    // if (selectedLeptons_looseMvaBased.size()==2 && selectedLeptons_looseMvaBased[0].charge() == selectedLeptons_looseMvaBased[1].charge())
	    //   {
	    // 	selectedElectrons_looseMvaBased = GetSelectedElectrons(selectedElectrons_looseMvaBased, 10., electronID::electron2lss);
	    // 	selectedMuons_looseMvaBased = GetSelectedMuons(selectedMuons_looseMvaBased, 5., muonID::muon2lss);
	    //   }
	    // selectedLeptons_looseMvaBased.clear();

	    // //tightMvaBased
	    // if (selectedLeptons_tightMvaBased.size()==2 && selectedLeptons_tightMvaBased[0].charge() == selectedLeptons_tightMvaBased[1].charge())
	    //   {
	    // 	selectedElectrons_tightMvaBased = GetSelectedElectrons(selectedElectrons_tightMvaBased, 10., electronID::electron2lss);
	    // 	selectedMuons_tightMvaBased = GetSelectedMuons(selectedMuons_tightMvaBased, 5., muonID::muon2lss);
	    //   }
	    // selectedLeptons_tightMvaBased.clear();
	    
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

		vstring hlt_alltrigs;

		// single lep
		
		string hlt_singlemu0 = "HLT_IsoMu24_eta2p1_v1"; // HLT_IsoMu24_IterTrk02_v1 // HLT_IsoTkMu27_v1 ? //// "to be kept ps'd" ?! not according to google doc...
		hlt_alltrigs.push_back(hlt_singlemu0);
		string hlt_singlemu1 = "HLT_IsoMu27_v1"; // HLT_IsoMu24_IterTrk02_v1 // HLT_IsoTkMu27_v1 ? // unps'd
		hlt_alltrigs.push_back(hlt_singlemu1);		
		string hlt_singlemu2 = "HLT_IsoTkMu27_v1"; // HLT_IsoMu24_IterTrk02_v1 // HLT_IsoTkMu27_v1 ? // unps'd
		hlt_alltrigs.push_back(hlt_singlemu2);
		
		
		string hlt_singleel0 = "HLT_Ele32_eta2p1_WP75_Gsf_v1";
		hlt_alltrigs.push_back(hlt_singleel0);
		
		// double lep
		
		string hlt_doublemu0 = "HLT_Mu17_Mu8_DZ_v1"; // ps'd
		hlt_alltrigs.push_back(hlt_doublemu0);
		string hlt_doublemu1 = "HLT_Mu17_TkMu8_DZ_v1"; // ps'd
		hlt_alltrigs.push_back(hlt_doublemu1);
		string hlt_doublemu2 = "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v1";
		hlt_alltrigs.push_back(hlt_doublemu2);
		string hlt_doublemu3 = "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v1";
		hlt_alltrigs.push_back(hlt_doublemu3);
		
		string hlt_doubleel0 = "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v1";
		hlt_alltrigs.push_back(hlt_doubleel0);
		
		string hlt_muel0 = "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1";
		hlt_alltrigs.push_back(hlt_muel0);
		
		string hlt_elmu0 = "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1";
		hlt_alltrigs.push_back(hlt_elmu0);
		
		// triple lep
		
		string hlt_elelel0 = "HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v1";
		hlt_alltrigs.push_back(hlt_elelel0);
		
		string hlt_mumumu0 = "HLT_TripleMu_12_10_5_v1";
		hlt_alltrigs.push_back(hlt_mumumu0);
		
		string hlt_muelel0 = "HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v1";
		hlt_alltrigs.push_back(hlt_muelel0);
		
		string hlt_mumuel0 = "HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v1";
		hlt_alltrigs.push_back(hlt_mumuel0);		
		
		// .. quad lep?

		
		// if event passes an HLT path add it to the tree:
		for (unsigned int trigit=0; trigit<hlt_alltrigs.size(); trigit++)
		{
			//try
			//{
				if (triggerResults->accept(hltConfig_.triggerIndex(hlt_alltrigs[trigit])))
				{
					passTrigger_intree.push_back(hlt_alltrigs[trigit]);
				}
			//}
			//catch(...)
			//{
			//	continue;
			//}
			
		}


	    /////////////////////////
	    //////
	    ////// fill the collections
	    //////
	    /////////////////////////

	    vector<ttH::Electron> raw_electrons = GetCollection(selectedElectrons_raw,selectedJets_forLepMVA);
	    vector<ttH::Electron> preselected_electrons = GetCollection(selectedElectrons_preselected,selectedJets_forLepMVA);
	    vector<ttH::Electron> looseMvaBased_electrons = GetCollection(selectedElectrons_looseMvaBased,selectedJets_forLepMVA);
	    vector<ttH::Electron> tightMvaBased_electrons = GetCollection(selectedElectrons_tightMvaBased,selectedJets_forLepMVA);

	    vector<ttH::Muon> raw_muons = GetCollection(selectedMuons_raw,selectedJets_forLepMVA);
	    vector<ttH::Muon> preselected_muons = GetCollection(selectedMuons_preselected,selectedJets_forLepMVA);
	    vector<ttH::Muon> looseMvaBased_muons = GetCollection(selectedMuons_looseMvaBased,selectedJets_forLepMVA);
	    vector<ttH::Muon> tightMvaBased_muons = GetCollection(selectedMuons_tightMvaBased,selectedJets_forLepMVA);

	    vector<ttH::Lepton> preselected_leptons = GetCollection(preselected_muons,preselected_electrons);
	    vector<ttH::Lepton> looseMvaBased_leptons = GetCollection(looseMvaBased_muons,looseMvaBased_electrons);
	    vector<ttH::Lepton> tightMvaBased_leptons = GetCollection(tightMvaBased_muons,tightMvaBased_electrons);

	    vector<ttH::Jet> raw_jets = GetCollection(rawJets);
	    vector<ttH::Jet> preselected_jets = GetCollection(selectedJets_preselected);
            vector<ttH::Jet> preselected_jets_uncor = GetCollection(selectedJets_preselected_uncor);
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
	      bool ss2l = (preselected_leptons[0].pdgID == preselected_leptons[0].pdgID);
	      bool pt2020 = (preselected_leptons[0].obj.Pt() >= 20 && preselected_leptons[0].obj.Pt() >=20);
	      bool lepMva = (tightMvaBased_leptons.size()>=2);
	      bool TwoCutSelection = true;
	      bool ss2tightEles = (tightMvaBased_electrons.size() ==2 && tightMvaBased_electrons[0].pdgID == tightMvaBased_electrons[1].pdgID);

	      for (const auto & ele : preselected_electrons)
		{
		  fout << eventnum_intree << ','<< ele.pdgID << ','<< ele.obj.Pt() <<','
		       << ele.obj.Eta() <<','<< ele.obj.Phi() <<','<< ele.dxy<<','<<ele.dz<<','
		       <<ele.relIso<<','<<ele.sip3D<<','<<ele.lepMVA<<','<<ele.mvaID<<','
		       <<ele.numMissingInnerHits<<','<<ele.isGsfCtfScPixChargeConsistent<<','<<ele.passConversioVeto<<','
		       <<' '<<','<<' '<<','<<' '<<','<<' '<<','<<' '<<','<<' '<<','
		       <<ele.nureliso<<','<<ele.chreliso<<','<<ele.matchedJetdR<<','<<ele.obj.Pt()<<','
		       <<ele.obj.Pt()/ele.jetPtRatio<<','<<ele.jetPtRatio<<','<<ele.csv<<','<<ele.sip3D<<','
		       <<ele.dxy<<','<<ele.dz<<','<<ele.mvaID<<','<< (2 >= preselected_leptons.size()) <<','
		       <<ss2l<<','<<pt2020<<','<<lepMva<<','<<TwoCutSelection<<','<<ss2tightEles<<'\n';
		  //		       <<'SS ee/mm'<<','<<'pt2020'<<','<<'lepMVA'<<','<<'2 cut -slection'<<','<<'==2 tight eles'<<
		  //		       <<'\n';



		}
	      for (const auto & mu : preselected_muons)
		{
		  fout << eventnum_intree << ','<<mu.pdgID<<','<<mu.obj.Pt()<<','<<mu.obj.Eta()<<','<<mu.obj.Phi()<<','
		       <<mu.dxy<<','<<mu.dz<<','<<mu.relIso<<','<<mu.sip3D<<','<<mu.lepMVA<<','<<mu.isPFMuon<<','
		       <<mu.isGlobalMuon<<','<<mu.chargeFlip<<','<<mu.isTrackerMuon<<','
		       <<mu.normalizedChi2<<','
		       <<mu.localChi2<<','<<mu.trKink<<','<<mu.validFrac<<','<<mu.segCompatibility<<','<<' '<<','
		       <<mu.nureliso<<','<<mu.chreliso<<','<<mu.matchedJetdR<<','<<mu.obj.Pt()<<','
		       <<mu.obj.Pt()/mu.jetPtRatio<<','<<mu.jetPtRatio<<','<<mu.csv<<','<<mu.sip3D<<','
		       <<mu.dxy<<','<<mu.dz<<','<<mu.segCompatibility<<','<< (2 >= preselected_leptons.size()) <<','
		       <<ss2l<<','<<pt2020<<','<<lepMva<<','<<TwoCutSelection<<','<<ss2tightEles<<'\n';
		       // <<'SS ee/mm '<<','<<'pt2020'<<','<<'lepMVA'<<','<<'2 cut -slection'<<','<<'==2 tight eles'<<
		       // <<'\n';		    

		}


	      if (preselected_leptons.size() >= 2 && higgs_decay_intree == 1)
		{
		  fprintf(lep1,"%6d %6d %10d  %+2d  %6.2f %+4.2f %+4.2f   %+2d  %6.2f %+4.2f %+4.2f    %6.1f  %+4.2f    %d \n",
			  runNumber_intree, lumiBlock_intree, eventnum_intree,
			  preselected_leptons[0].pdgID, preselected_leptons[0].obj.Pt(), preselected_leptons[0].obj.Eta(), preselected_leptons[0].obj.Phi(),
			  preselected_leptons[1].pdgID, preselected_leptons[1].obj.Pt(), preselected_leptons[1].obj.Eta(), preselected_leptons[1].obj.Phi(),
			theMET[0].pt_forSync, theMET[0].phi_forSync, int(preselected_jets.size()));

		  if ( tightMvaBased_leptons.size()==2 && tightMvaBased_leptons[0].charge == tightMvaBased_leptons[1].charge )
		    {
		      if (abs(tightMvaBased_leptons[0].pdgID) == 11 && abs(tightMvaBased_leptons[1].pdgID) == 11)
			{
			  fprintf(el4,"%6d %6d %10d  %+2d  %6.2f %+4.2f %+4.2f   %+2d  %6.2f %+4.2f %+4.2f    %6.1f  %+4.2f    %d \n",
				  runNumber_intree, lumiBlock_intree, eventnum_intree,
				  tightMvaBased_leptons[0].pdgID, tightMvaBased_leptons[0].obj.Pt(), tightMvaBased_leptons[0].obj.Eta(), tightMvaBased_leptons[0].obj.Phi(),
				  tightMvaBased_leptons[1].pdgID, tightMvaBased_leptons[1].obj.Pt(), tightMvaBased_leptons[1].obj.Eta(), tightMvaBased_leptons[1].obj.Phi(),
				  theMET[0].pt_forSync, theMET[0].phi_forSync, int(preselected_jets.size()));
			}
		      else if (abs(tightMvaBased_leptons[0].pdgID) == 13 && abs(tightMvaBased_leptons[1].pdgID) == 13)
			{
			  fprintf(ml4,"%6d %6d %10d  %+2d  %6.2f %+4.2f %+4.2f   %+2d  %6.2f %+4.2f %+4.2f    %6.1f  %+4.2f    %d \n",
				  runNumber_intree, lumiBlock_intree, eventnum_intree,
				  tightMvaBased_leptons[0].pdgID, tightMvaBased_leptons[0].obj.Pt(), tightMvaBased_leptons[0].obj.Eta(), tightMvaBased_leptons[0].obj.Phi(),
				  tightMvaBased_leptons[1].pdgID, tightMvaBased_leptons[1].obj.Pt(), tightMvaBased_leptons[1].obj.Eta(), tightMvaBased_leptons[1].obj.Phi(),
				  theMET[0].pt_forSync, theMET[0].phi_forSync, int(preselected_jets.size()));
			}
		    }
		}
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
            
            
	    preselected_leptons_intree = preselected_leptons;
	    preselected_electrons_intree = preselected_electrons;
	    preselected_muons_intree = preselected_muons;

	    looseMvaBased_muons_intree = looseMvaBased_muons;
	    tightMvaBased_muons_intree = tightMvaBased_muons;
	    looseMvaBased_electrons_intree = looseMvaBased_electrons;
	    tightMvaBased_electrons_intree = tightMvaBased_electrons;
	    looseMvaBased_leptons_intree = looseMvaBased_leptons;
	    tightMvaBased_leptons_intree = tightMvaBased_leptons;

	    //raw_electrons_intree = raw_electrons;
	    //raw_muons_intree = raw_muons;
	    //raw_jets_intree = raw_jets;
            
	    preselected_jets_intree = preselected_jets;
	    preselected_jets_uncor_intree = preselected_jets_uncor;
            
            //loose_bJets_intree = loose_bJets;
	    //tight_bJets_intree = tight_bJets;

	    met_intree = theMET;

	    pruned_genParticles_intree = pruned_genParticles;

	    wgt_intree = weight;
	
	    wallTimePerEvent_intree = double( clock() - startTime ) / (double)CLOCKS_PER_SEC;

	    summaryTree->Fill();// fill tree;
	    
        } //end skim if statement

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
