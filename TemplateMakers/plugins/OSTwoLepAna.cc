// created by Geoff Smith

#include "ttHMultileptonAnalysis/TemplateMakers/interface/OSTwoLepAna.h"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/EGammaMvaEleEstimatorFWLite.h"

OSTwoLepAna::OSTwoLepAna(const edm::ParameterSet& constructparams){ //Anything that needs to be done at creation time
	debug = constructparams.getParameter<bool> ("debug");
	entire_pset = constructparams;
	parse_params();


}
OSTwoLepAna::~OSTwoLepAna(){} //Anything that needs to be done at destruction time


void OSTwoLepAna::beginJob()
{
	
	// job setup
	
	sampleNumber=9120; //hack for now -> to include in parameterset. Right now there is only one sample.
	SetUp(analysisYear, sampleNumber, analysisType::DIL, isData);
	SetFactorizedJetCorrector();
	setupMva();

	// initialize some variables:
	electronTightID = electronID::electronTight;
	electronLooseID = electronID::electronLoose;
	electronPreselectedID = electronID::electronPreselection;
	muonTightID = muonID::muonTight;
	muonLooseID = muonID::muonLoose;
	muonPreselectedID = muonID::muonNoCuts;
	tauTightID = tauID::tauMedium;
	// tauLooseID = tauID::tauVLoose;
	tauPreselectedID = tauID::tauNonIso;
	
	// needed in edanalyzer:
	edm::Service<TFileService> newfs;
	
	// book histos:
	numtighteles = 	newfs->make<TH1D>("numtighteles","numtighteles",6,0,6);
	numlooseeles = 	newfs->make<TH1D>("numlooseeles","numlooseeles",6,0,6);
	numtightmuons = newfs->make<TH1D>("numtightmuons","numtightmuons",6,0,6);
	numloosemuons = newfs->make<TH1D>("numloosemuons","numloosemuons",6,0,6);
	numrawjets = 	newfs->make<TH1D>("numrawjets","numrawjets",15,0,15);
	numjetsnoele = 			newfs->make<TH1D>("numjetsnoele","numjetsnoele",15,0,15);
	numjetsnomu = 			newfs->make<TH1D>("numjetsnomu","numjetsnomu",15,0,15);
	numjetsnomuorele = 		newfs->make<TH1D>("numjetsnomuorele","numjetsnomuorele",15,0,15);
	numjetscorrected = 		newfs->make<TH1D>("numjetscorrected","numjetscorrected",15,0,15);
	numjetsselectedloose = 		newfs->make<TH1D>("numjetsselectedloose","numjetsselectedloose",15,0,15);
	numbtagsselectedlooseCSVM = 	newfs->make<TH1D>("numbtagsselectedlooseCSVM","numbtagsselectedlooseCSVM",12,0,12);
	leadingtightmupt = 		newfs->make<TH1D>("leadingtightmupt","leadingtightmupt",200,0,400);
	subleadingtightmupt = 		newfs->make<TH1D>("subleadingtightmupt","subleadingtightmupt",200,0,400);
	leadingtightelept = 		newfs->make<TH1D>("leadingtightelept","leadingtightelept",200,0,400);
	subleadingtightelept = 		newfs->make<TH1D>("subleadingtightelept","subleadingtightelept",200,0,400);
	leadingtightleppt = 		newfs->make<TH1D>("leadingtightleppt","leadingtightleppt",200,0,400);
	subleadingtightleppt = 		newfs->make<TH1D>("subleadingtightleppt","subleadingtightleppt",200,0,400);
	jet1pt = newfs->make<TH1D>("jet1pt","jet1pt",200,0,400);
	jet2pt = newfs->make<TH1D>("jet2pt","jet2pt",200,0,400);
	jet3pt = newfs->make<TH1D>("jet3pt","jet3pt",200,0,400);
	jet4pt = newfs->make<TH1D>("jet4pt","jet4pt",200,0,400);   
	met_pt = newfs->make<TH1D>("met_pt","met_pt",200,0,400);
	lep1_lep2_pt = newfs->make<TH2D>("lep1_lep2_pt","lep1_lep2_pt",30,0,150,30,0,150);
	hlt_count_hist = newfs->make<TH1D>("hlt_count_hist","hlt_count_hist",1000,0,1000);
		
	// add the tree:
	summaryTree = newfs->make<TTree>("summaryTree", "Summary Event Values");	
	tree_add_branches();
	
	
}
void OSTwoLepAna::endJob() {

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
	
	SetRho(rho);
	
	int numpvs =				GetVertices(event);
	
	if (debug) cout << "numpvs: " << numpvs << endl;
		
	edm::Handle<GenEventInfoProduct> GenInfo;
    	event.getByLabel("generator",GenInfo);
    	double mcwgt_intree = GenInfo->weight();		// <- gen-level weight
	
	double weight = 1.;			// <- analysis weight 

	weight *= mcwgt_intree;				// MC-only (flag to be added)

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

	vecPatElectron selectedElectrons_tight = GetSelectedElectrons( *electrons, mintightelept, electronID::electronTight );	//miniAODhelper.
	vecPatElectron selectedElectrons_loose = GetSelectedElectrons( *electrons, minlooseelept, electronID::electronLoose );	//miniAODhelper.
	vecPatElectron selectedElectrons_preselected = GetSelectedElectrons( *electrons, 7., electronID::electronPreselection );	//miniAODhelper.
	vecPatElectron selectedElectrons_nocuts = GetSelectedElectrons( *electrons, 10., electronID::electronNoCuts );	//miniAODhelper.
	vecPatElectron selectedElectrons_loose_notight = RemoveOverlaps( selectedElectrons_tight, selectedElectrons_loose);	//miniAODhelper.
	
	int numTightElectrons = int(selectedElectrons_tight.size());
	int numLooseElectrons = int(selectedElectrons_loose.size());



	vecTLorentzVectorCMS elesTLVloose = Get_vecTLorentzVectorCMS(selectedElectrons_loose);
	vecTLorentzVectorCMS elesTLVtight = Get_vecTLorentzVectorCMS(selectedElectrons_tight);
	vecTLorentzVectorCMS elesTLVloosenotight = Get_vecTLorentzVectorCMS(selectedElectrons_loose_notight);




	/////////
	///
	/// Muons
	///
	////////



	//double mintightmupt = 10.;
	double mintightmupt = minTightLeptonPt;
	double minloosemupt = minLooseLeptonPt;

	vecPatMuon selectedMuons_tight = GetSelectedMuons( *muons, mintightmupt, muonID::muonTight );		//miniAODhelper.
	vecPatMuon selectedMuons_loose = GetSelectedMuons( *muons, minloosemupt, muonID::muonLoose );		//miniAODhelper.
	vecPatMuon selectedMuons_preselected = GetSelectedMuons( *muons, 5., muonID::muonPreselection );	//miniAODhelper.
	vecPatMuon selectedMuons_nocuts = GetSelectedMuons( *muons, 10., muonID::muonNoCuts );	//miniAODhelper.
	vecPatMuon selectedMuons_loose_notight = RemoveOverlaps(selectedMuons_tight,selectedMuons_loose);		//miniAODhelper.
	
	int numTightMuons = int(selectedMuons_tight.size());
	int numLooseMuons = int(selectedMuons_loose.size());
	
	
	vecTLorentzVectorCMS muonsTLVloose = Get_vecTLorentzVectorCMS(selectedMuons_loose);
	vecTLorentzVectorCMS muonsTLVtight = Get_vecTLorentzVectorCMS(selectedMuons_tight);	
	vecTLorentzVectorCMS muonsTLVloosenotight = Get_vecTLorentzVectorCMS(selectedMuons_loose_notight);

	
	/////////
	///
	/// Leptons
	///
	////////
	
	//remove electrons that are close (dR <=0.02) to muons
	selectedElectrons_preselected = cleanObjects(selectedElectrons_preselected,selectedMuons_preselected,0.02);
	
	vecPatLepton selectedLeptons_preselected = fillLeptons(selectedMuons_preselected,selectedElectrons_preselected);
	vecPatLepton selectedLeptons_nocuts = fillLeptons(selectedMuons_nocuts,selectedElectrons_nocuts);

	vecTLorentzVectorCMS leptonsTLVtight = Get_vecTLorentzVectorCMS_sorted_leptons (muonsTLVtight, elesTLVtight); 
	vecTLorentzVectorCMS leptonsTLVloose = Get_vecTLorentzVectorCMS_sorted_leptons (muonsTLVloose, elesTLVloose); 	
	
	/////////
	///
	/// Jets
	///
	////////

 	
	vecPatJet rawJets				= GetUncorrectedJets(*pfjets);  					  //miniAODhelper.
	vecPatJet cleaned_rawJets                       = cleanObjects(rawJets,selectedLeptons_nocuts,0.4);
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
	vecPatJet selectedJets_forLepMVA          	= GetSelectedJets(rawJets, 10., 9.e9, jetID::none, '-' );   //miniAODhelper.
	

	vecTLorentzVectorCMS jetsTLVloose = Get_vecTLorentzVectorCMS(selectedJets_loose_noSys_unsorted);
	vecTLorentzVectorCMS jetsTLVtight = Get_vecTLorentzVectorCMS(selectedJets_noSys_unsorted);

	int numRawJets = rawJets.size();
	int numJetsNoEle = jetsNoEle.size();
	int numJetsNoMu = jetsNoMu.size();
	int numJetsNoLep = jetsNoLep.size();
	int numJetsCorr = correctedJets_noSys.size();

	int numSelJetsLoose = selectedJets_loose_noSys_unsorted.size();
	//int numSelJets = selectedJets_noSys_unsorted.size();

	int numSelJetsLooseCSVM = selectedJets_loose_tag_noSys_unsorted.size();

	
	/////////
	///
	/// MET
	///
	////////
	
	TLorentzVectorCMS theMET = Get_TLorentzVectorCMS(mets);
	
	/////////////////////////
	//////
	////// cut flow studies
	//////
	/////////////////////////
	
	num_BJetsLoose_intree = int(selectedJets_bJetsLoose.size());
	num_Jets_intree = int(selectedJets_forSync.size());
	
	num_preselectedMuons_intree = int(selectedMuons_preselected.size());
	num_preselectedElectrons_intree = int(selectedElectrons_preselected.size());
	num_preselectedLeptons_intree = int(selectedLeptons_preselected.size());

	int higgs_daughter1 = GetHiggsDaughterId(*prunedParticles,1);
	int higgs_daughter2 = GetHiggsDaughterId(*prunedParticles,2);

	higgs_decay_intree = ((higgs_daughter1==24 && higgs_daughter2==24)||(higgs_daughter1==23 && higgs_daughter2==23)||(higgs_daughter1==15 && higgs_daughter2==15)) ? 1 : 0;
	
	eventnum_intree = event.id().event();
	
	if (num_preselectedMuons_intree == 2)
	  {
	    mu1_charge_intree = selectedMuons_preselected[0].charge();
	    mu2_charge_intree = selectedMuons_preselected[1].charge();
	    mu1_pt_intree = selectedMuons_preselected[0].pt();
	    mu2_pt_intree = selectedMuons_preselected[1].pt();
	    mu1_lepMVA_intree = GetMuonLepMVA(selectedMuons_preselected[0],selectedJets_forLepMVA);
	    mu2_lepMVA_intree = GetMuonLepMVA(selectedMuons_preselected[1],selectedJets_forLepMVA);
	    mu1_chargeFlip_intree = (selectedMuons_preselected[0].innerTrack()->ptError()/selectedMuons_preselected[0].innerTrack()->pt() < 0.2 ) ? 1 : 0;
	    mu2_chargeFlip_intree = (selectedMuons_preselected[1].innerTrack()->ptError()/selectedMuons_preselected[1].innerTrack()->pt() < 0.2 ) ? 1 : 0;
	    
	    mu1_chRelIso_intree = selectedMuons_preselected[0].chargedHadronIso()/selectedMuons_preselected[0].pt();
	    mu1_nuRelIso_intree = GetMuonRelIsoR04(selectedMuons_preselected[0]) - mu1_chRelIso_intree;
	    pat::Jet matchedJet = getClosestJet(selectedJets_forLepMVA,selectedMuons_preselected[0]);
	    double dR = MiniAODHelper::DeltaR(&matchedJet,&selectedMuons_preselected[0]);
	    mu1_jetdR_intree = min(dR,0.5);
	    mu1_jetPtRatio_intree =  min(selectedMuons_preselected[0].pt()/matchedJet.pt(), float(1.5));
	    mu1_bTagCSV_intree = max(matchedJet.bDiscriminator("combinedSecondaryVertexBJetTags"), float(0.0));
	    mu1_sip3d_intree = fabs(selectedMuons_preselected[0].dB(pat::Muon::PV3D)/selectedMuons_preselected[0].edB(pat::Muon::PV3D));

	  } 
	
	if (num_preselectedElectrons_intree == 2)
	  {
	    ele1_charge_intree = selectedElectrons_preselected[0].charge();
	    ele2_charge_intree = selectedElectrons_preselected[1].charge();
	    ele1_pt_intree = selectedElectrons_preselected[0].pt();
	    ele2_pt_intree = selectedElectrons_preselected[1].pt();
	    ele1_lepMVA_intree = GetElectronLepMVA(selectedElectrons_preselected[0],selectedJets_forLepMVA);
	    ele2_lepMVA_intree = GetElectronLepMVA(selectedElectrons_preselected[1],selectedJets_forLepMVA);

	    bool ele1_chargeFlipA = selectedElectrons_preselected[0].isGsfCtfScPixChargeConsistent();
	    bool ele1_chargeFlipB = ( selectedElectrons_preselected[0].gsfTrack()->trackerExpectedHitsInner().numberOfHits() == 0 );
	    bool ele1_chargeFlipC = selectedElectrons_preselected[0].passConversionVeto();

	    bool ele2_chargeFlipA = selectedElectrons_preselected[1].isGsfCtfScPixChargeConsistent();
	    bool ele2_chargeFlipB = (selectedElectrons_preselected[1].gsfTrack()->trackerExpectedHitsInner().numberOfHits() == 0);
	    bool ele2_chargeFlipC = selectedElectrons_preselected[1].passConversionVeto();

	    ele1_chargeFlip_intree =  (ele1_chargeFlipA && ele1_chargeFlipB && ele1_chargeFlipC) ? 1 : 0;
	    ele2_chargeFlip_intree =  (ele2_chargeFlipA && ele2_chargeFlipB && ele2_chargeFlipC) ? 1 : 0;
	    
	    ele1_chRelIso_intree = selectedElectrons_preselected[0].chargedHadronIso()/selectedElectrons_preselected[0].pt();
	    ele1_nuRelIso_intree = GetElectronRelIso(selectedElectrons_preselected[0]) - ele1_chRelIso_intree;
	    pat::Jet matchedJet = getClosestJet(selectedJets_forLepMVA,selectedElectrons_preselected[0]);
	    double dR = MiniAODHelper::DeltaR(&matchedJet,&selectedElectrons_preselected[0]);
	    ele1_jetdR_intree = min(dR,0.5);
	    ele1_jetPtRatio_intree =  min(selectedElectrons_preselected[0].pt()/matchedJet.pt(), float(1.5));
	    ele1_bTagCSV_intree = max(matchedJet.bDiscriminator("combinedSecondaryVertexBJetTags"), float(0.0));
	    ele1_sip3d_intree = fabs(selectedElectrons_preselected[0].dB(pat::Electron::PV3D)/selectedElectrons_preselected[0].edB(pat::Electron::PV3D));

	  } 
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	// fill some basic histos:

	numtighteles->						Fill(numTightElectrons,weight);
	numlooseeles->						Fill(numLooseElectrons,weight);
	numtightmuons->						Fill(numTightMuons,weight);
	numloosemuons->						Fill(numLooseMuons,weight);
	numrawjets->						Fill(numRawJets,weight);
	numjetsnoele->						Fill(numJetsNoEle,weight);
	numjetsnomu->						Fill(numJetsNoMu,weight);
	numjetsnomuorele->					Fill(numJetsNoLep,weight);
	numjetscorrected->					Fill(numJetsCorr,weight);
	numjetsselectedloose->					Fill(numSelJetsLoose,weight);
	numbtagsselectedlooseCSVM->				Fill(numSelJetsLooseCSVM,weight);
	if (numTightMuons) leadingtightmupt->			Fill(muonsTLVtight[0].Pt(),weight);
	if (numTightMuons>1) subleadingtightmupt->		Fill(muonsTLVtight[1].Pt(),weight);
	if (numTightElectrons) leadingtightelept->		Fill(elesTLVtight[0].Pt(),weight);
	if (numTightElectrons>1) subleadingtightelept->		Fill(elesTLVtight[1].Pt(),weight);
	if (leptonsTLVtight.size()) leadingtightleppt->		Fill(leptonsTLVtight[0].Pt(),weight);
	if (leptonsTLVtight.size()>1) subleadingtightleppt->	Fill(leptonsTLVtight[1].Pt(),weight);
	if (jetsTLVloose.size())jet1pt->			Fill(jetsTLVloose[0].Pt(),weight);
	if (jetsTLVloose.size()>1)jet2pt->			Fill(jetsTLVloose[1].Pt(),weight);
	if (jetsTLVloose.size()>2)jet3pt->			Fill(jetsTLVloose[2].Pt(),weight);
	if (jetsTLVloose.size()>3)jet4pt->			Fill(jetsTLVloose[3].Pt(),weight);
	met_pt->						Fill(theMET.Pt(),weight);

	
// 	TwoMuon = 0; TwoElectron = 0; MuonElectron = 0; PassTwoLepton = 0; 
// 	if ( numTightMuons >= 1 && numTightLooseMuons == 2 && numTightLooseElectrons == 0 ) TwoMuon = 1; 
// 	if ( numTightElectrons >= 1 && numTightLooseElectrons == 2 && numTightLooseMuons == 0 ) TwoElectron = 1; 
// 	if ( ( numTightMuons + numTightElectrons ) >= 1 && numTightLooseMuons == 1 && numTightLooseElectrons == 1 ) MuonElectron = 1; 
// 	if ( TwoMuon + TwoElectron + MuonElectron == 1 ) PassTwoLepton = 1;
	
	
	// assign values to tree variables:
	numLooseMuons_intree = numLooseMuons;
	numLooseElectrons_intree = numLooseElectrons;
	numTightMuons_intree = numTightMuons;
	numTightElectrons_intree = numTightElectrons;
	
	//testvect.push_back(3.);
	//testvect.push_back(11.);
	
	Jets_intree = jetsTLVloose;
	MET_intree = theMET;
	LooseElectrons_intree = elesTLVloose;
	LooseMuons_intree = muonsTLVloose;
	TightElectrons_intree = elesTLVtight;
	TightMuons_intree = muonsTLVtight;
	JetCSV_intree = ReturnBTagDisc(selectedJets_loose_noSys_unsorted);
		
	wgt_intree = weight;
	
	// fill it:
	summaryTree->Fill();
	
} // end for each event

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
