// created by Geoff Smith

#include "ttHMultileptonAnalysis/TemplateMakers/interface/TriggerAna.h"


	
TriggerAna::TriggerAna(const edm::ParameterSet& constructparams){ //Anything that needs to be done at creation time
	debug = constructparams.getParameter<bool> ("debug");
	entire_pset = constructparams;
	parse_params();
}
TriggerAna::~TriggerAna(){} //Anything that needs to be done at destruction time


void TriggerAna::beginJob()
{
	edm::Service<TFileService> newfs;
	
	
	
	//variables = new Variables;
	//summaryTree = new TTree("summaryTree", "Summary Event Values");
	///summaryTree("summaryTree", "Summary Event Values");	
	
	//variables->initialize();
	//variables=0;
	//summaryTree->Branch("variables.","Variables",&variables,8000,1);
	
	
	
	//initialize_tree(summaryTree, variables);
	//initialize_tree();
	
	
	sampleNumber=9120; //hack for now -> to include in parameterset. Right now there is only one sample.
	
	SetUp(analysisYear, sampleNumber, analysisType::DIL, isData);
	SetFactorizedJetCorrector();

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
	
	

	// initialize some variables:

	electronTightID = electronID::electronTight;
	electronLooseID = electronID::electronLoose;
	electronPreselectedID = electronID::electronNoCuts;

	muonTightID = muonID::muonTight;
	muonLooseID = muonID::muonLoose;
	muonPreselectedID = muonID::muonNoCuts;

	tauTightID = tauID::tauMedium;
	// tauLooseID = tauID::tauVLoose;
	tauPreselectedID = tauID::tauNonIso;

	eventcount=0;

	//	doublmucount=0;
	//	doubleelecount=0;
	//	muelecount=0;
	//	elemucount=0;	    

	doublemucount=0.;
	doublemucount2=0.;
	doublemucount3=0.;
	doublemucount4=0.;
	doubleelecount=0.;
	doubleelecount2=0.;
	muelecount=0.;
	elemucount=0.;	
	tripelcount=0.;
	
	for (int i=0; i<1000; i++)
	{
		//allcount[i] = 0.;
		
		allcount_mumu[i] = 0.;
		allcount_elel[i] = 0.;
		allcount_muel[i] = 0.;
		allcount_elmu[i] = 0.;
		
	}

	numpassedcuts=0;

	numpassedmumucuts=0.;
	numpassedelelcuts=0.;
	numpassedmuelcuts=0.;
	numpassedelmucuts=0.;
	
	doublemucount5=0;
	
	// usually this will be parsed elsewhere:
// 	mumutriggerstostudy.push_back("HLT_Mu17_Mu8_v1");
// 	mumutriggerstostudy.push_back("HLT_Mu17_TkMu8_v1");
// 	mumutriggerstostudy.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v1");
// 	mumutriggerstostudy.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v1");
// 	eleltriggerstostudy.push_back("HLT_Ele17_Ele8_Gsf_v1");
// 	eleltriggerstostudy.push_back("HLT_Ele23_Ele12_CaloId_TrackId_Iso_v1");
// 	mueltriggerstostudy.push_back("HLT_Mu23_TrkIsoVVL_Ele12_Gsf_CaloId_TrackId_Iso_MediumWP_v1");
// 	elmutriggerstostudy.push_back("HLT_Mu8_TrkIsoVVL_Ele23_Gsf_CaloId_TrackId_Iso_MediumWP_v1");
// 	tripeltriggerstostudy.push_back("HLT_Ele17_Ele12_Ele10_CaloId_TrackId_v1");
	
	
// 	mumutriggerstostudy.push_back("HLT_Mu13_Mu8_v23");
// 	mumutriggerstostudy.push_back("HLT_Mu17_Mu8_v23");
// 	mumutriggerstostudy.push_back("HLT_Mu17_TkMu8_v15");
// 	mumutriggerstostudy.push_back("HLT_Mu22_TkMu8_v10");
// 	eleltriggerstostudy.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v20");
// 	eleltriggerstostudy.push_back("HLT_Ele27_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele15_CaloIdT_CaloIsoVL_trackless_v9");
// 	mueltriggerstostudy.push_back("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v10");
// 	elmutriggerstostudy.push_back("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v10");
// 	tripeltriggerstostudy.push_back("HLT_Ele15_Ele8_Ele5_CaloIdL_TrkIdVL_v7");
	
	alltriggerstostudy = HLTInfo();
	
	int numtrigs = alltriggerstostudy.size();
	
	if (numtrigs) mumutriggerstostudy.push_back(alltriggerstostudy[0]);
	if (numtrigs>1) mumutriggerstostudy.push_back(alltriggerstostudy[1]);
	if (numtrigs>2) mumutriggerstostudy.push_back(alltriggerstostudy[2]);
	if (numtrigs>3) mumutriggerstostudy.push_back(alltriggerstostudy[3]);
	if (numtrigs>4) eleltriggerstostudy.push_back(alltriggerstostudy[4]);
	if (numtrigs>5) eleltriggerstostudy.push_back(alltriggerstostudy[5]);
	if (numtrigs>6) mueltriggerstostudy.push_back(alltriggerstostudy[6]);
	if (numtrigs>7) elmutriggerstostudy.push_back(alltriggerstostudy[7]);
	if (numtrigs>8) tripeltriggerstostudy.push_back(alltriggerstostudy[8]);
	
	
	for (int i=0; i<10; i++)
	{
		if (i<numtrigs)
		{
			lep1_pt_didpass_double_lep[i] = newfs->make<TH1D>(alltriggerstostudy[i].c_str(),("lep1_pt_didpass_double_lep_" + alltriggerstostudy[i]).c_str(),100,0,200);
			lep2_pt_didpass_double_lep[i] = newfs->make<TH1D>(alltriggerstostudy[i].c_str(),("lep2_pt_didpass_double_lep_" + alltriggerstostudy[i]).c_str(),100,0,200);
			lep1_pt_didntpass_double_lep_but_passed_single_lep[i] = newfs->make<TH1D>(alltriggerstostudy[i].c_str(),("lep1_pt_didntpass_double_lep_but_passed_single_lep_" + alltriggerstostudy[i]).c_str(),100,0,200);
			lep2_pt_didntpass_double_lep_but_passed_single_lep[i] = newfs->make<TH1D>(alltriggerstostudy[i].c_str(),("lep2_pt_didntpass_double_lep_but_passed_single_lep_" + alltriggerstostudy[i]).c_str(),100,0,200);
		
			lep1_eta_didpass_double_lep[i] = newfs->make<TH1D>(alltriggerstostudy[i].c_str(),("lep1_eta_didpass_double_lep_" + alltriggerstostudy[i]).c_str(),100,-3,3);
			lep2_eta_didpass_double_lep[i] = newfs->make<TH1D>(alltriggerstostudy[i].c_str(),("lep2_eta_didpass_double_lep_" + alltriggerstostudy[i]).c_str(),100,-3,3);
			lep1_eta_didntpass_double_lep_but_passed_single_lep[i] = newfs->make<TH1D>(alltriggerstostudy[i].c_str(),("lep1_eta_didntpass_double_lep_but_passed_single_lep_" + alltriggerstostudy[i]).c_str(),100,-3,3);
			lep2_eta_didntpass_double_lep_but_passed_single_lep[i] = newfs->make<TH1D>(alltriggerstostudy[i].c_str(),("lep2_eta_didntpass_double_lep_but_passed_single_lep_" + alltriggerstostudy[i]).c_str(),100,-3,3);
		
			lep1_phi_didpass_double_lep[i] = newfs->make<TH1D>(alltriggerstostudy[i].c_str(),("lep1_phi_didpass_double_lep_" + alltriggerstostudy[i]).c_str(),100,-3.5,3.5);
			lep2_phi_didpass_double_lep[i] = newfs->make<TH1D>(alltriggerstostudy[i].c_str(),("lep2_phi_didpass_double_lep_" + alltriggerstostudy[i]).c_str(),100,-3.5,3.5);
			lep1_phi_didntpass_double_lep_but_passed_single_lep[i] = newfs->make<TH1D>(alltriggerstostudy[i].c_str(),("lep1_phi_didntpass_double_lep_but_passed_single_lep_" + alltriggerstostudy[i]).c_str(),100,-3.5,3.5);
			lep2_phi_didntpass_double_lep_but_passed_single_lep[i] = newfs->make<TH1D>(alltriggerstostudy[i].c_str(),("lep2_phi_didntpass_double_lep_but_passed_single_lep_" + alltriggerstostudy[i]).c_str(),100,-3.5,3.5);
		
			lep1_iso_didpass_double_lep[i] = newfs->make<TH1D>(alltriggerstostudy[i].c_str(),("lep1_iso_didpass_double_lep_" + alltriggerstostudy[i]).c_str(),100,0,0.25);
			lep2_iso_didpass_double_lep[i] = newfs->make<TH1D>(alltriggerstostudy[i].c_str(),("lep2_iso_didpass_double_lep_" + alltriggerstostudy[i]).c_str(),100,0,0.25);
			lep1_iso_didntpass_double_lep_but_passed_single_lep[i] = newfs->make<TH1D>(alltriggerstostudy[i].c_str(),("lep1_iso_didntpass_double_lep_but_passed_single_lep_" + alltriggerstostudy[i]).c_str(),100,0,0.25);
			lep2_iso_didntpass_double_lep_but_passed_single_lep[i] = newfs->make<TH1D>(alltriggerstostudy[i].c_str(),("lep2_iso_didntpass_double_lep_but_passed_single_lep_" + alltriggerstostudy[i]).c_str(),100,0,0.25);
		

		
		
		}
		else
		{
			ostringstream os;
			os << i << endl;
			
			lep1_pt_didpass_double_lep[i] = newfs->make<TH1D>(os.str().c_str(),("lep1_pt_didpass_double_lep_" + os.str()).c_str(),100,0,200);
			lep2_pt_didpass_double_lep[i] = newfs->make<TH1D>(os.str().c_str(),("lep2_pt_didpass_double_lep_" + os.str()).c_str(),100,0,200);
			lep1_pt_didntpass_double_lep_but_passed_single_lep[i] = newfs->make<TH1D>(os.str().c_str(),("lep1_pt_didntpass_double_lep_but_passed_single_lep_" + os.str()).c_str(),100,0,200);
			lep2_pt_didntpass_double_lep_but_passed_single_lep[i] = newfs->make<TH1D>(os.str().c_str(),("lep2_pt_didntpass_double_lep_but_passed_single_lep_" + os.str()).c_str(),100,0,200);
		
			lep1_eta_didpass_double_lep[i] = newfs->make<TH1D>(os.str().c_str(),("lep1_eta_didpass_double_lep_" + os.str()).c_str(),100,-3,3);
			lep2_eta_didpass_double_lep[i] = newfs->make<TH1D>(os.str().c_str(),("lep2_eta_didpass_double_lep_" + os.str()).c_str(),100,-3,3);
			lep1_eta_didntpass_double_lep_but_passed_single_lep[i] = newfs->make<TH1D>(os.str().c_str(),("lep1_eta_didntpass_double_lep_but_passed_single_lep_" + os.str()).c_str(),100,-3,3);
			lep2_eta_didntpass_double_lep_but_passed_single_lep[i] = newfs->make<TH1D>(os.str().c_str(),("lep2_eta_didntpass_double_lep_but_passed_single_lep_" + os.str()).c_str(),100,-3,3);
		
			lep1_phi_didpass_double_lep[i] = newfs->make<TH1D>(os.str().c_str(),("lep1_phi_didpass_double_lep_" + os.str()).c_str(),100,-3.5,3.5);
			lep2_phi_didpass_double_lep[i] = newfs->make<TH1D>(os.str().c_str(),("lep2_phi_didpass_double_lep_" + os.str()).c_str(),100,-3.5,3.5);
			lep1_phi_didntpass_double_lep_but_passed_single_lep[i] = newfs->make<TH1D>(os.str().c_str(),("lep1_phi_didntpass_double_lep_but_passed_single_lep_" + os.str()).c_str(),100,-3.5,3.5);
			lep2_phi_didntpass_double_lep_but_passed_single_lep[i] = newfs->make<TH1D>(os.str().c_str(),("lep2_phi_didntpass_double_lep_but_passed_single_lep_" + os.str()).c_str(),100,-3.5,3.5);
		
			lep1_iso_didpass_double_lep[i] = newfs->make<TH1D>(os.str().c_str(),("lep1_iso_didpass_double_lep_" + os.str()).c_str(),100,0,0.25);
			lep2_iso_didpass_double_lep[i] = newfs->make<TH1D>(os.str().c_str(),("lep2_iso_didpass_double_lep_" + os.str()).c_str(),100,0,0.25);
			lep1_iso_didntpass_double_lep_but_passed_single_lep[i] = newfs->make<TH1D>(os.str().c_str(),("lep1_iso_didntpass_double_lep_but_passed_single_lep_" + os.str()).c_str(),100,0,0.25);
			lep2_iso_didntpass_double_lep_but_passed_single_lep[i] = newfs->make<TH1D>(os.str().c_str(),("lep2_iso_didntpass_double_lep_but_passed_single_lep_" + os.str()).c_str(),100,0,0.25);
		
		
		
		
		}
	}
	
	mumu_lep1_denom = newfs->make<TH1D>("mumu_lep1_denom","mumu_lep1_denom",100,0,200);
	mumu_lep2_denom = newfs->make<TH1D>("mumu_lep2_denom","mumu_lep2_denom",100,0,200);
	muel_lep1_denom = newfs->make<TH1D>("muel_lep1_denom","muel_lep1_denom",100,0,200);
	muel_lep2_denom = newfs->make<TH1D>("muel_lep2_denom","muel_lep2_denom",100,0,200);
	elel_lep1_denom = newfs->make<TH1D>("elel_lep1_denom","elel_lep1_denom",100,0,200);
	elel_lep2_denom = newfs->make<TH1D>("elel_lep2_denom","elel_lep2_denom",100,0,200);
	elmu_lep1_denom = newfs->make<TH1D>("elmu_lep1_denom","elmu_lep1_denom",100,0,200);
	elmu_lep2_denom = newfs->make<TH1D>("elmu_lep2_denom","elmu_lep2_denom",100,0,200);
	
	//TFileDirectory results = TFileDirectory( newfs->mkdir("anotherdir") ); // doesn't actually make the dir, but for some reason needed to save the tree
	
	summaryTree = newfs->make<TTree>("summaryTree", "Summary Event Values");
	tree_add_branches();
	
	
	//summaryTree = new TTree("summaryTree", "Summary Event Values");
	
	// variables = new Variables();
// 	
// 	
	
}
void TriggerAna::endJob() {

//  cout << "Num Events processed " << numEvents << endl;
//       << "Passed cuts " << numEventsPassCuts << endl;
//       << "Failed cuts " << numEventsFailCuts << endl;
       
} // job completion (cutflow table, etc.)

void TriggerAna::analyze(const edm::Event& event, const edm::EventSetup& evsetup) // this function is called once at each event
{
	// analysis goes here
	if (debug) cout << "event: " << event.id().event() << endl;
	
	eventcount++;
	SetupOptions(event);
  
	trigRes triggerResults = 	GetTriggers(event);
	patMuons muons = 		GetMuons(event);
	patJets pfjets = 		GetJets(event);
	patElectrons electrons = 	GetElectrons(event);
	patMETs mets = 			GetMet(event);
	
	SetRho(rho);
	
	int numpvs =			GetVertices(event);
	if (debug) cout << "numpvs: " << numpvs << endl;
		
	edm::Handle<GenEventInfoProduct> GenInfo;
    	event.getByLabel("generator",GenInfo);
    	double wgt = GenInfo->weight();		// <- gen-level weight
	
	double weight = 1.;			// <- analysis weight 
	//  int numEvents = 0;
	//  int numEventsFailCuts = 0;
	//  int numEventsPassCuts = 0;
	//  int printEvery = 1;
  
	
	//wgt = weight; //test

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
	vecPatElectron selectedElectrons_loose_notight = RemoveOverlaps( selectedElectrons_tight, selectedElectrons_loose);	//miniAODhelper.
	
	int numTightElectrons = int(selectedElectrons_tight.size());
	int numLooseElectrons = int(selectedElectrons_loose.size());


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
	vecPatMuon selectedMuons_loose_notight = RemoveOverlaps(selectedMuons_tight,selectedMuons_loose);		//miniAODhelper.

	int numTightMuons = int(selectedMuons_tight.size());
	int numLooseMuons = int(selectedMuons_loose.size());


	//bool isOS = false;	
	
	vecTLorentzVectorCMS muonsTLVloose = Get_vecTLorentzVectorCMS(selectedMuons_loose);
	vecTLorentzVectorCMS muonsTLVtight = Get_vecTLorentzVectorCMS(selectedMuons_tight);
			  
	vecTLorentzVectorCMS elesTLVloose = Get_vecTLorentzVectorCMS(selectedElectrons_loose);
	vecTLorentzVectorCMS elesTLVtight = Get_vecTLorentzVectorCMS(selectedElectrons_tight);
	
	vecTLorentzVectorCMS leptonsTLVtight = Get_vecTLorentzVectorCMS_sorted_leptons (muonsTLVtight, elesTLVtight); 
	vecTLorentzVectorCMS leptonsTLVloose = Get_vecTLorentzVectorCMS_sorted_leptons (muonsTLVloose, elesTLVloose); 
	
	vecTLorentzVectorCMS muonsTLVloosenotight = Get_vecTLorentzVectorCMS(selectedMuons_loose_notight);
	vecTLorentzVectorCMS elesTLVloosenotight = Get_vecTLorentzVectorCMS(selectedElectrons_loose_notight);
	
	vdouble muonIsosLoose = Get_Isos(selectedMuons_loose);
	vdouble muonIsosTight = Get_Isos(selectedMuons_tight);
	
	vdouble electronIsosLoose = Get_Isos(selectedElectrons_loose);
	vdouble electronIsosTight = Get_Isos(selectedElectrons_tight);
	
		
	/////////
	///
	/// Jets
	///
	////////

 	
	vecPatJet rawJets				= GetUncorrectedJets(*pfjets);  					  //miniAODhelper.
	vecPatJet jetsNoMu			       	= RemoveOverlaps(selectedMuons_loose, rawJets); 			    //miniAODhelper.
	vecPatJet jetsNoEle			       	= RemoveOverlaps(selectedElectrons_loose, rawJets);			    //miniAODhelper.
	vecPatJet jetsNoLep			       	= RemoveOverlaps(selectedElectrons_loose, jetsNoMu);			    //miniAODhelper.
	vecPatJet correctedJets_noSys		       	= GetCorrectedJets(jetsNoLep);  					    //miniAODhelper.
	vecPatJet selectedJets_noSys_unsorted	       	= GetSelectedJets(correctedJets_noSys, 30., 2.4, jetID::jetLoose, '-' );    //miniAODhelper.
	vecPatJet selectedJets_tag_noSys_unsorted	= GetSelectedJets( correctedJets_noSys, 30., 2.4, jetID::jetLoose, 'M' );   //miniAODhelper.
	vecPatJet selectedJets_loose_noSys_unsorted     = GetSelectedJets(correctedJets_noSys, 20., 2.4, jetID::jetLoose, '-' );    //miniAODhelper.
	vecPatJet selectedJets_loose_tag_noSys_unsorted	= GetSelectedJets( correctedJets_noSys, 20., 2.4, jetID::jetLoose, 'M' );   //miniAODhelper.

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
	
	
	
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	// fill some basic histos:

	numtighteles->Fill					(numTightElectrons,weight);
	numlooseeles->Fill					(numLooseElectrons,weight);
	numtightmuons->Fill					(numTightMuons,weight);
	numloosemuons->Fill					(numLooseMuons,weight);
	numrawjets->Fill					(numRawJets,weight);
	numjetsnoele->Fill					(numJetsNoEle,weight);
	numjetsnomu->Fill					(numJetsNoMu,weight);
	numjetsnomuorele->Fill					(numJetsNoLep,weight);
	numjetscorrected->Fill					(numJetsCorr,weight);
	numjetsselectedloose->Fill				(numSelJetsLoose,weight);
	numbtagsselectedlooseCSVM->Fill				(numSelJetsLooseCSVM,weight);
	if (numTightMuons) leadingtightmupt->Fill		(muonsTLVtight[0].Pt(),weight);
	if (numTightMuons>1) subleadingtightmupt->Fill		(muonsTLVtight[1].Pt(),weight);
	if (numTightElectrons) leadingtightelept->Fill		(elesTLVtight[0].Pt(),weight);
	if (numTightElectrons>1) subleadingtightelept->Fill	(elesTLVtight[1].Pt(),weight);
	if (leptonsTLVtight.size()) leadingtightleppt->Fill	(leptonsTLVtight[0].Pt(),weight);
	if (leptonsTLVtight.size()>1) subleadingtightleppt->Fill(leptonsTLVtight[1].Pt(),weight);
	if (jetsTLVloose.size())jet1pt->Fill			(jetsTLVloose[0].Pt(),weight);
	if (jetsTLVloose.size()>1)jet2pt->Fill			(jetsTLVloose[1].Pt(),weight);
	if (jetsTLVloose.size()>2)jet3pt->Fill			(jetsTLVloose[2].Pt(),weight);
	if (jetsTLVloose.size()>3)jet4pt->Fill			(jetsTLVloose[3].Pt(),weight);
	met_pt->Fill						(theMET.Pt(),weight);
	// .....


	///////////////////////////////////////////////////////////////////////////////////////////////
	// Do anything else specific to the analysis (like apply event selection, evaluate variables, loop over systematics, save things to a tree)
	// In this case, I'm doing some trigger studies:
	// ////////////////////////////////////////////////////////////////////////////////////////////
	
	
	
	edm::Handle<trigger::TriggerEvent> aodTriggerEvent;   
	event.getByLabel(edm::InputTag("hltTriggerSummaryAOD", "", hltTag), aodTriggerEvent); // this won't be in a regular miniAOD sample!
	
	if (numLooseMuons>1)
	{
		for (int i=0; i<(numLooseMuons-1); i++)
		{
			if (muonsTLVloose[i+1].Pt()>muonsTLVloose[i].Pt()) cout << "hey!" << endl; // are they sorted by pt? yes.
		}
	}
	
	if (!triggerResults.isValid())
	{
		std::cout << "Trigger results not valid" << std::endl;
	}

	std::vector<std::string> myTriggernames = hltConfig_.triggerNames();
	
	int triggersize = myTriggernames.size();

	for (int j=0; j<triggersize; j++)
	{	
		unsigned int path__index = hltConfig_.triggerIndex(myTriggernames[j]);
	
		if (eventcount==1)
		{
			cout << myTriggernames[j] << endl;
		}
	
		if(triggerResults->accept(path__index))
		{
			hlt_count_hist->Fill(j);
		}
	}



	
	if (leptonsTLVloose.size()>1)
	{
		for (int i=0; i<30; i++)
		{
			for (int j=0; j<30; j++)
			{
				double amount = 5.;
				
				double leadingcut = (double)i*amount;
				double subleadingcut = (double)j*amount;
				
				if (leptonsTLVloose[0].Pt()>leadingcut&&leptonsTLVloose[1].Pt()>subleadingcut) lep1_lep2_pt->Fill(leadingcut,subleadingcut);
			}
		}
	}
	
	//if(numLooseElectrons>1&&numTightElectrons>0) lep1_lep2_pt->Fill(elesTLVtight[0].Pt(),elesTLVloosenotight[0].Pt());
	
	// if(numLooseMuons>1&&numTightMuons>0)
// 	{
// 		if (muonsTLVloose[0].Pt()!=muonsTLVtight[0].Pt()) lep1_lep2_pt->Fill(muonsTLVtight[0].Pt(),muonsTLVloose[0].Pt());
// 		else lep1_lep2_pt->Fill(muonsTLVtight[0].Pt(),muonsTLVloose[1].Pt());
// 	}
	

	// select events with one tight lepton with pt > 20, and one additional loose lepton with pt >10 :
	double leg1 = 20.; //pt
	double leg2 = 10.; //pt
	
	double loosedubmu2pt = -1.;
	double loosedubel2pt = -1.;
	
	double loosedubmu2eta = -99.;
	double loosedubel2eta = -99.;
	
	double loosedubmu2phi = -99.;
	double loosedubel2phi = -99.;
	
	double loosedubmu2iso = -99.;
	double loosedubel2iso = -99.;
	
	
	
	bool tightmupass = false;
	if ((numTightMuons>0)&&(muonsTLVtight[0].Pt()>leg1)) tightmupass = true;
	
	bool tightelepass = false;
	if ((numTightElectrons>0)&&(elesTLVtight[0].Pt()>leg1)) tightelepass = true;
	
	bool loosedubmupass = false;
	if (tightmupass&&(numLooseMuons>1))
	{
		if ((muonsTLVtight[0].Pt()!=muonsTLVloose[0].Pt())&&(muonsTLVloose[0].Pt()>leg2))
		{
			loosedubmupass=true; 
			loosedubmu2pt = muonsTLVloose[0].Pt(); 
			loosedubmu2eta = muonsTLVloose[0].Eta();
			loosedubmu2phi = muonsTLVloose[0].Phi();
			loosedubmu2iso = muonIsosLoose[0];
		}
		if ((muonsTLVtight[0].Pt()==muonsTLVloose[0].Pt())&&(muonsTLVloose[1].Pt()>leg2)) 
		{
			loosedubmupass=true; 
			loosedubmu2pt = muonsTLVloose[1].Pt(); 
			loosedubmu2eta = muonsTLVloose[1].Eta();
			loosedubmu2phi = muonsTLVloose[1].Phi();
			loosedubmu2iso = muonIsosLoose[1];
		}
	}
	
	bool loosedubelepass = false;
	if (tightelepass&&(numLooseElectrons>1))
	{
		if ((elesTLVtight[0].Pt()!=elesTLVloose[0].Pt())&&(elesTLVloose[0].Pt()>leg2)) 
		{ 
			loosedubelepass=true; 
			loosedubel2pt = elesTLVloose[0].Pt();
			loosedubel2eta = elesTLVloose[0].Eta();
			loosedubel2phi = elesTLVloose[0].Phi();
			loosedubel2iso = electronIsosLoose[0];
		}
		if ((elesTLVtight[0].Pt()==elesTLVloose[0].Pt())&&(elesTLVloose[1].Pt()>leg2)) 
		{ 
			loosedubelepass=true; 
			loosedubel2pt = elesTLVloose[1].Pt(); 
			loosedubel2eta = elesTLVloose[1].Eta();
			loosedubel2phi = elesTLVloose[1].Phi();
			loosedubel2iso = electronIsosLoose[1];
		}
	}
	
	bool muele_looseelepass = false;
	if (numLooseElectrons) if (tightmupass&&(elesTLVloose[0].Pt()>leg2)) muele_looseelepass = true;
	
	bool muele_loosemupass = false;
	if (numLooseMuons) if (tightelepass&&(muonsTLVloose[0].Pt()>leg2)) muele_loosemupass = true;
	
	
	
	//// out of those events, find which ones passed which triggers:
	// also, pt of leps that passed, didn't pass certain triggers:
	
	//string extra_trig = "HLT_IsoMu30_v12";
	string extra_trig = "HLT_Ele27_WP80_v13";


	if (tightmupass&&loosedubmupass)
	{
		if (triggerResults->accept(hltConfig_.triggerIndex(mumutriggerstostudy[0]))||triggerResults->accept(hltConfig_.triggerIndex(extra_trig))) doublemucount += wgt; // doublemucount++;
		if (triggerResults->accept(hltConfig_.triggerIndex(mumutriggerstostudy[1]))||triggerResults->accept(hltConfig_.triggerIndex(extra_trig))) doublemucount2 += wgt; // doublemucount2++;
		if (triggerResults->accept(hltConfig_.triggerIndex(mumutriggerstostudy[2]))||triggerResults->accept(hltConfig_.triggerIndex(extra_trig))) doublemucount3 += wgt; // doublemucount3++;
		if (triggerResults->accept(hltConfig_.triggerIndex(mumutriggerstostudy[3]))||triggerResults->accept(hltConfig_.triggerIndex(extra_trig))) doublemucount4 += wgt; // doublemucount4++;
		
		if (triggerResults->accept(hltConfig_.triggerIndex(mumutriggerstostudy[1]))||triggerResults->accept(hltConfig_.triggerIndex(mumutriggerstostudy[2]))) doublemucount5 += wgt;

		for (int i=0; i<triggersize; i++) if (triggerResults->accept(i)) allcount_mumu[i] += wgt;

		cout << wgt << endl;

		numpassedmumucuts += wgt; //numpassedmumucuts++;
		
		mumu_lep1_denom->Fill(muonsTLVtight[0].Pt());
		mumu_lep2_denom->Fill(loosedubmu2pt);
		
		if (triggerResults->accept(hltConfig_.triggerIndex(mumutriggerstostudy[0]))) 
		{ 
			lep1_pt_didpass_double_lep[0]->Fill(muonsTLVtight[0].Pt()); 
			lep2_pt_didpass_double_lep[0]->Fill(loosedubmu2pt);
			lep1_eta_didpass_double_lep[0]->Fill(muonsTLVtight[0].Eta()); 
			lep2_eta_didpass_double_lep[0]->Fill(loosedubmu2eta);
			lep1_phi_didpass_double_lep[0]->Fill(muonsTLVtight[0].Phi()); 
			lep2_phi_didpass_double_lep[0]->Fill(loosedubmu2phi);
			lep1_iso_didpass_double_lep[0]->Fill(muonIsosTight[0]); 
			lep2_iso_didpass_double_lep[0]->Fill(loosedubmu2iso);
			 
		}
		if ((!triggerResults->accept(hltConfig_.triggerIndex(mumutriggerstostudy[0])))&&triggerResults->accept(hltConfig_.triggerIndex(extra_trig))) 
		{ 
			lep1_pt_didntpass_double_lep_but_passed_single_lep[0]->Fill(muonsTLVtight[0].Pt()); 
			lep2_pt_didntpass_double_lep_but_passed_single_lep[0]->Fill(loosedubmu2pt);
			lep1_eta_didntpass_double_lep_but_passed_single_lep[0]->Fill(muonsTLVtight[0].Eta());
			lep2_eta_didntpass_double_lep_but_passed_single_lep[0]->Fill(loosedubmu2eta);
			lep1_phi_didntpass_double_lep_but_passed_single_lep[0]->Fill(muonsTLVtight[0].Phi());
			lep2_phi_didntpass_double_lep_but_passed_single_lep[0]->Fill(loosedubmu2phi);
			lep1_iso_didntpass_double_lep_but_passed_single_lep[0]->Fill(muonIsosTight[0]); 
			lep2_iso_didntpass_double_lep_but_passed_single_lep[0]->Fill(loosedubmu2iso);
			

		}
		if (triggerResults->accept(hltConfig_.triggerIndex(mumutriggerstostudy[1]))) 
		{ 
			lep1_pt_didpass_double_lep[1]->Fill(muonsTLVtight[0].Pt()); 
			lep2_pt_didpass_double_lep[1]->Fill(loosedubmu2pt);
			lep1_eta_didpass_double_lep[1]->Fill(muonsTLVtight[0].Eta()); 
			lep2_eta_didpass_double_lep[1]->Fill(loosedubmu2eta);
			lep1_phi_didpass_double_lep[1]->Fill(muonsTLVtight[0].Phi()); 
			lep2_phi_didpass_double_lep[1]->Fill(loosedubmu2phi);
			lep1_iso_didpass_double_lep[1]->Fill(muonIsosTight[0]); 
			lep2_iso_didpass_double_lep[1]->Fill(loosedubmu2iso);			
			 
		}
		if ((!triggerResults->accept(hltConfig_.triggerIndex(mumutriggerstostudy[1])))&&triggerResults->accept(hltConfig_.triggerIndex(extra_trig))) 
		{ 
			lep1_pt_didntpass_double_lep_but_passed_single_lep[1]->Fill(muonsTLVtight[0].Pt()); 
			lep2_pt_didntpass_double_lep_but_passed_single_lep[1]->Fill(loosedubmu2pt);
			lep1_eta_didntpass_double_lep_but_passed_single_lep[1]->Fill(muonsTLVtight[0].Eta());
			lep2_eta_didntpass_double_lep_but_passed_single_lep[1]->Fill(loosedubmu2eta);
			lep1_phi_didntpass_double_lep_but_passed_single_lep[1]->Fill(muonsTLVtight[0].Phi());
			lep2_phi_didntpass_double_lep_but_passed_single_lep[1]->Fill(loosedubmu2phi);
			lep1_iso_didntpass_double_lep_but_passed_single_lep[1]->Fill(muonIsosTight[0]); 
			lep2_iso_didntpass_double_lep_but_passed_single_lep[1]->Fill(loosedubmu2iso);
									 
		}
		if (triggerResults->accept(hltConfig_.triggerIndex(mumutriggerstostudy[2]))) 
		{ 
			lep1_pt_didpass_double_lep[2]->Fill(muonsTLVtight[0].Pt()); 
			lep2_pt_didpass_double_lep[2]->Fill(loosedubmu2pt);
			lep1_eta_didpass_double_lep[2]->Fill(muonsTLVtight[0].Eta()); 
			lep2_eta_didpass_double_lep[2]->Fill(loosedubmu2eta);
			lep1_phi_didpass_double_lep[2]->Fill(muonsTLVtight[0].Phi()); 
			lep2_phi_didpass_double_lep[2]->Fill(loosedubmu2phi);
			lep1_iso_didpass_double_lep[2]->Fill(muonIsosTight[0]); 
			lep2_iso_didpass_double_lep[2]->Fill(loosedubmu2iso);
			
			 
		}
		if ((!triggerResults->accept(hltConfig_.triggerIndex(mumutriggerstostudy[2])))&&triggerResults->accept(hltConfig_.triggerIndex(extra_trig))) 
		{ 
			lep1_pt_didntpass_double_lep_but_passed_single_lep[2]->Fill(muonsTLVtight[0].Pt()); 
			lep2_pt_didntpass_double_lep_but_passed_single_lep[2]->Fill(loosedubmu2pt);
			lep1_eta_didntpass_double_lep_but_passed_single_lep[2]->Fill(muonsTLVtight[0].Eta());
			lep2_eta_didntpass_double_lep_but_passed_single_lep[2]->Fill(loosedubmu2eta);
			lep1_phi_didntpass_double_lep_but_passed_single_lep[2]->Fill(muonsTLVtight[0].Phi());
			lep2_phi_didntpass_double_lep_but_passed_single_lep[2]->Fill(loosedubmu2phi);
			lep1_iso_didntpass_double_lep_but_passed_single_lep[2]->Fill(muonIsosTight[0]); 
			lep2_iso_didntpass_double_lep_but_passed_single_lep[2]->Fill(loosedubmu2iso);
			
		}
		if (triggerResults->accept(hltConfig_.triggerIndex(mumutriggerstostudy[3]))) 
		{ 
			lep1_pt_didpass_double_lep[3]->Fill(muonsTLVtight[0].Pt()); 
			lep2_pt_didpass_double_lep[3]->Fill(loosedubmu2pt);
			lep1_eta_didpass_double_lep[3]->Fill(muonsTLVtight[0].Eta()); 
			lep2_eta_didpass_double_lep[3]->Fill(loosedubmu2eta);
			lep1_phi_didpass_double_lep[3]->Fill(muonsTLVtight[0].Phi()); 
			lep2_phi_didpass_double_lep[3]->Fill(loosedubmu2phi);
			lep1_iso_didpass_double_lep[3]->Fill(muonIsosTight[0]); 
			lep2_iso_didpass_double_lep[3]->Fill(loosedubmu2iso);			
			 
		}
		if ((!triggerResults->accept(hltConfig_.triggerIndex(mumutriggerstostudy[3])))&&triggerResults->accept(hltConfig_.triggerIndex(extra_trig))) 
		{ 
			lep1_pt_didntpass_double_lep_but_passed_single_lep[3]->Fill(muonsTLVtight[0].Pt()); 
			lep2_pt_didntpass_double_lep_but_passed_single_lep[3]->Fill(loosedubmu2pt);
			lep1_eta_didntpass_double_lep_but_passed_single_lep[3]->Fill(muonsTLVtight[0].Eta());
			lep2_eta_didntpass_double_lep_but_passed_single_lep[3]->Fill(loosedubmu2eta);
			lep1_phi_didntpass_double_lep_but_passed_single_lep[3]->Fill(muonsTLVtight[0].Phi());
			lep2_phi_didntpass_double_lep_but_passed_single_lep[3]->Fill(loosedubmu2phi);
			lep1_iso_didntpass_double_lep_but_passed_single_lep[3]->Fill(muonIsosTight[0]); 
			lep2_iso_didntpass_double_lep_but_passed_single_lep[3]->Fill(loosedubmu2iso);
			 
		}
		
	}

	if (tightelepass&&loosedubelepass)
	{
		if (triggerResults->accept(hltConfig_.triggerIndex(eleltriggerstostudy[0]))||triggerResults->accept(hltConfig_.triggerIndex(extra_trig))) doubleelecount += wgt; //doubleelecount++;
		if (triggerResults->accept(hltConfig_.triggerIndex(eleltriggerstostudy[1]))||triggerResults->accept(hltConfig_.triggerIndex(extra_trig))) doubleelecount2 += wgt; //doubleelecount2++;
		numpassedelelcuts += wgt; //numpassedelelcuts++;
		
		for (int i=0; i<triggersize; i++) if (triggerResults->accept(i)) allcount_elel[i] += wgt;
		
		elel_lep1_denom->Fill(elesTLVtight[0].Pt());
		elel_lep2_denom->Fill(loosedubel2pt);
		
		if (triggerResults->accept(hltConfig_.triggerIndex(eleltriggerstostudy[0]))) 
		{ 
			lep1_pt_didpass_double_lep[4]->Fill(elesTLVtight[0].Pt()); 
			lep2_pt_didpass_double_lep[4]->Fill(loosedubel2pt);
			lep1_eta_didpass_double_lep[4]->Fill(elesTLVtight[0].Eta()); 
			lep2_eta_didpass_double_lep[4]->Fill(loosedubel2eta);
			lep1_phi_didpass_double_lep[4]->Fill(elesTLVtight[0].Phi()); 
			lep2_phi_didpass_double_lep[4]->Fill(loosedubel2phi);
			lep1_iso_didpass_double_lep[4]->Fill(electronIsosTight[0]); 
			lep2_iso_didpass_double_lep[4]->Fill(loosedubel2iso);			
			 
		}
		if ((!triggerResults->accept(hltConfig_.triggerIndex(eleltriggerstostudy[0])))&&triggerResults->accept(hltConfig_.triggerIndex(extra_trig))) 
		{ 
			lep1_pt_didntpass_double_lep_but_passed_single_lep[4]->Fill(elesTLVtight[0].Pt()); 
			lep2_pt_didntpass_double_lep_but_passed_single_lep[4]->Fill(loosedubel2pt);
			lep1_eta_didntpass_double_lep_but_passed_single_lep[4]->Fill(elesTLVtight[0].Eta());
			lep2_eta_didntpass_double_lep_but_passed_single_lep[4]->Fill(loosedubel2eta);
			lep1_phi_didntpass_double_lep_but_passed_single_lep[4]->Fill(elesTLVtight[0].Phi());
			lep2_phi_didntpass_double_lep_but_passed_single_lep[4]->Fill(loosedubel2phi);
			lep1_iso_didntpass_double_lep_but_passed_single_lep[4]->Fill(electronIsosTight[0]); 
			lep2_iso_didntpass_double_lep_but_passed_single_lep[4]->Fill(loosedubel2iso);
						 
		}
		
		if (triggerResults->accept(hltConfig_.triggerIndex(eleltriggerstostudy[1]))) 
		{ 
			lep1_pt_didpass_double_lep[5]->Fill(elesTLVtight[0].Pt()); 
			lep2_pt_didpass_double_lep[5]->Fill(loosedubel2pt);
			lep1_eta_didpass_double_lep[5]->Fill(elesTLVtight[0].Eta()); 
			lep2_eta_didpass_double_lep[5]->Fill(loosedubel2eta);
			lep1_phi_didpass_double_lep[5]->Fill(elesTLVtight[0].Phi()); 
			lep2_phi_didpass_double_lep[5]->Fill(loosedubel2phi);
			lep1_iso_didpass_double_lep[5]->Fill(electronIsosTight[0]); 
			lep2_iso_didpass_double_lep[5]->Fill(loosedubel2iso);
						
			 
		}
		if ((!triggerResults->accept(hltConfig_.triggerIndex(eleltriggerstostudy[1])))&&triggerResults->accept(hltConfig_.triggerIndex(extra_trig))) 
		{ 
			lep1_pt_didntpass_double_lep_but_passed_single_lep[5]->Fill(elesTLVtight[0].Pt()); 
			lep2_pt_didntpass_double_lep_but_passed_single_lep[5]->Fill(loosedubel2pt);
			lep1_eta_didntpass_double_lep_but_passed_single_lep[5]->Fill(elesTLVtight[0].Eta());
			lep2_eta_didntpass_double_lep_but_passed_single_lep[5]->Fill(loosedubel2eta);
			lep1_phi_didntpass_double_lep_but_passed_single_lep[5]->Fill(elesTLVtight[0].Phi());
			lep2_phi_didntpass_double_lep_but_passed_single_lep[5]->Fill(loosedubel2phi);
			lep1_iso_didntpass_double_lep_but_passed_single_lep[5]->Fill(electronIsosTight[0]); 
			lep2_iso_didntpass_double_lep_but_passed_single_lep[5]->Fill(loosedubel2iso);						
			 
		}
		
	}

	if (tightmupass&&muele_looseelepass)
	{
		if (triggerResults->accept(hltConfig_.triggerIndex(mueltriggerstostudy[0]))||triggerResults->accept(hltConfig_.triggerIndex(extra_trig))) muelecount += wgt; //muelecount++;
		numpassedmuelcuts += wgt; //numpassedmuelcuts++;
		
		for (int i=0; i<triggersize; i++) if (triggerResults->accept(i)) allcount_muel[i] += wgt;
		
		muel_lep1_denom->Fill(muonsTLVtight[0].Pt());
		muel_lep2_denom->Fill(elesTLVloose[0].Pt());
		
		if (triggerResults->accept(hltConfig_.triggerIndex(mueltriggerstostudy[0]))) 
		{ 
			lep1_pt_didpass_double_lep[6]->Fill(muonsTLVtight[0].Pt()); 
			lep2_pt_didpass_double_lep[6]->Fill(elesTLVloose[0].Pt());
			lep1_eta_didpass_double_lep[6]->Fill(muonsTLVtight[0].Eta());
			lep2_eta_didpass_double_lep[6]->Fill(elesTLVloose[0].Eta());
			lep1_phi_didpass_double_lep[6]->Fill(muonsTLVtight[0].Phi());
			lep2_phi_didpass_double_lep[6]->Fill(elesTLVloose[0].Phi());
			lep1_iso_didpass_double_lep[6]->Fill(muonIsosTight[0]);
			lep2_iso_didpass_double_lep[6]->Fill(electronIsosLoose[0]);
			
			 
		}
		if ((!triggerResults->accept(hltConfig_.triggerIndex(mueltriggerstostudy[0])))&&triggerResults->accept(hltConfig_.triggerIndex(extra_trig))) 
		{ 
			lep1_pt_didntpass_double_lep_but_passed_single_lep[6]->Fill(muonsTLVtight[0].Pt()); 
			lep2_pt_didntpass_double_lep_but_passed_single_lep[6]->Fill(elesTLVloose[0].Pt());
			lep1_eta_didntpass_double_lep_but_passed_single_lep[6]->Fill(muonsTLVtight[0].Eta());
			lep2_eta_didntpass_double_lep_but_passed_single_lep[6]->Fill(elesTLVloose[0].Eta());
			lep1_phi_didntpass_double_lep_but_passed_single_lep[6]->Fill(muonsTLVtight[0].Phi());
			lep2_phi_didntpass_double_lep_but_passed_single_lep[6]->Fill(elesTLVloose[0].Phi());
			lep1_iso_didntpass_double_lep_but_passed_single_lep[6]->Fill(muonIsosTight[0]);
			lep2_iso_didntpass_double_lep_but_passed_single_lep[6]->Fill(electronIsosLoose[0]);
						 
		}	
		
	}

	if (tightelepass&&muele_loosemupass)
	{
		if (triggerResults->accept(hltConfig_.triggerIndex(elmutriggerstostudy[0]))||triggerResults->accept(hltConfig_.triggerIndex(extra_trig))) elemucount += wgt; //elemucount++;
		numpassedelmucuts += wgt; //numpassedelmucuts++;
		
		for (int i=0; i<triggersize; i++) if (triggerResults->accept(i)) allcount_elmu[i] += wgt;
		
		elmu_lep1_denom->Fill(elesTLVtight[0].Pt());
		elmu_lep2_denom->Fill(muonsTLVloose[0].Pt());
		
		if (triggerResults->accept(hltConfig_.triggerIndex(elmutriggerstostudy[0]))) 
		{ 
			lep1_pt_didpass_double_lep[7]->Fill(elesTLVtight[0].Pt()); 
			lep2_pt_didpass_double_lep[7]->Fill(muonsTLVloose[0].Pt());
			lep1_eta_didpass_double_lep[7]->Fill(elesTLVtight[0].Eta());
			lep2_eta_didpass_double_lep[7]->Fill(muonsTLVloose[0].Eta());
			lep1_phi_didpass_double_lep[7]->Fill(elesTLVtight[0].Phi());
			lep2_phi_didpass_double_lep[7]->Fill(muonsTLVloose[0].Phi());
			lep1_iso_didpass_double_lep[7]->Fill(electronIsosTight[0]);
			lep2_iso_didpass_double_lep[7]->Fill(muonIsosLoose[0]);			
			 
		}
		if ((!triggerResults->accept(hltConfig_.triggerIndex(elmutriggerstostudy[0])))&&triggerResults->accept(hltConfig_.triggerIndex(extra_trig))) 
		{ 
			lep1_pt_didntpass_double_lep_but_passed_single_lep[7]->Fill(elesTLVtight[0].Pt()); 
			lep2_pt_didntpass_double_lep_but_passed_single_lep[7]->Fill(muonsTLVloose[0].Pt());
			lep1_eta_didntpass_double_lep_but_passed_single_lep[7]->Fill(elesTLVtight[0].Eta());
			lep2_eta_didntpass_double_lep_but_passed_single_lep[7]->Fill(muonsTLVloose[0].Eta());
			lep1_phi_didntpass_double_lep_but_passed_single_lep[7]->Fill(elesTLVtight[0].Phi());
			lep2_phi_didntpass_double_lep_but_passed_single_lep[7]->Fill(muonsTLVloose[0].Phi());
			lep1_iso_didntpass_double_lep_but_passed_single_lep[7]->Fill(electronIsosTight[0]);
			lep2_iso_didntpass_double_lep_but_passed_single_lep[7]->Fill(muonIsosLoose[0]);			
			 
		}	
		
		
	}
	
	// variables->numLooseMuons = numLooseMuons;
// 	variables->numLooseElectrons = numLooseElectrons;	
// 	variables->numTightMuons = numTightMuons;
// 	variables->numTightElectrons = numTightElectrons;
	
	// assign values to tree variables:
	numLooseMuons_intree = numLooseMuons;
	numLooseElectrons_intree = numLooseElectrons;
	numTightMuons_intree = numTightMuons;
	numTightElectrons_intree = numTightElectrons;
	
	//testvect.push_back(3.);
	//testvect.push_back(11.);
	
	//testTLV_intree = theMET;
	
	
	
	Jets_intree = jetsTLVloose;
	MET_intree = theMET;
	LooseElectrons_intree = elesTLVloose;
	LooseMuons_intree = muonsTLVloose;
	TightElectrons_intree = elesTLVtight;
	TightMuons_intree = muonsTLVtight;
	JetCSV_intree = ReturnBTagDisc(selectedJets_loose_noSys_unsorted);
		
	
	
	// fill it:
	//summaryTree->Fill();
	

	
	
} // end for each event

void TriggerAna::beginRun(edm::Run const& run, edm::EventSetup const& evsetup){
		
	// This has to be done here (not at beginjob):
	
	bool changed = true;
	if (hltConfig_.init(run, evsetup, hltTag, changed)) std::cout << "HLT config with process name " << hltTag << " successfully extracted" << std::endl;
	
	else std::cout << "Warning, didn't find process " << hltTag << std::endl;
	
	std::cout << " HLTConfig processName " << hltConfig_.processName() << " tableName " << hltConfig_.tableName() << " size " << hltConfig_.size() << std::endl; // " globalTag: " << hltConfig_.globalTag() << std::endl;
	
}
void TriggerAna::endRun(edm::Run const& run, edm::EventSetup const& evsetup){

	//cout << doublmucount << endl;
	//cout << numpassedcuts << endl;
	cout << "total events processed: " << eventcount << endl;
	
	cout << "trigger results" << endl;
// 	cout << mumutriggerstostudy[0] << "  " << doublemucount << "out of " << numpassedmumucuts << endl;
// 	cout << mumutriggerstostudy[1] << "  " << doublemucount2 << "out of " << numpassedmumucuts << endl;
// 	cout << mumutriggerstostudy[2] << "  " << doublemucount3 << "out of " << numpassedmumucuts << endl;
// 	cout << mumutriggerstostudy[3] << "  " << doublemucount4 << "out of " << numpassedmumucuts << endl;
// 	cout << "  " << endl;
// 	cout << eleltriggerstostudy[0] << "  " << doubleelecount << "out of " << numpassedelelcuts << endl;
// 	cout << eleltriggerstostudy[1] << "  " << doubleelecount2 << "out of " << numpassedelelcuts << endl;
// 	cout << "  " << endl;
// 	cout << mueltriggerstostudy[0] << "  " << muelecount << "out of " << numpassedmuelcuts << endl;
// 	cout << "  " << endl;
// 	cout << elmutriggerstostudy[0] << "  " << elemucount << "out of " << numpassedelmucuts << endl;


	cout << mumutriggerstostudy[0] << "  " << doublemucount << "out of " << numpassedmumucuts << ", fraction: " << (double)doublemucount/numpassedmumucuts << endl;
	cout << mumutriggerstostudy[1] << "  " << doublemucount2 << "out of " << numpassedmumucuts << ", fraction: " << (double)doublemucount2/numpassedmumucuts << endl;
	cout << mumutriggerstostudy[2] << "  " << doublemucount3 << "out of " << numpassedmumucuts << ", fraction: " << (double)doublemucount3/numpassedmumucuts << endl;
	cout << mumutriggerstostudy[3] << "  " << doublemucount4 << "out of " << numpassedmumucuts << ", fraction: " << (double)doublemucount4/numpassedmumucuts << endl;
	cout << "  " << endl;
	cout << eleltriggerstostudy[0] << "  " << doubleelecount << "out of " << numpassedelelcuts << ", fraction: " << (double)doubleelecount/numpassedelelcuts << endl;
	cout << eleltriggerstostudy[1] << "  " << doubleelecount2 << "out of " << numpassedelelcuts << ", fraction: " << (double)doubleelecount2/numpassedelelcuts << endl;
	cout << "  " << endl;
	cout << mueltriggerstostudy[0] << "  " << muelecount << "out of " << numpassedmuelcuts << ", fraction: " << (double)muelecount/numpassedmuelcuts << endl;
	cout << "  " << endl;
	cout << elmutriggerstostudy[0] << "  " << elemucount << "out of " << numpassedelmucuts << ", fraction: " << (double)elemucount/numpassedelmucuts << endl;
	cout << "  " << endl;
	cout << doublemucount5 <<  "  "  << numpassedmumucuts << endl;
	cout << "  " << endl;
	cout << "  " << endl;
	
	int numtrigs = hltConfig_.size();
	std::vector<std::string> myTriggernames = hltConfig_.triggerNames();
	
	cout << "mumu: " << endl;
	for (int i =0; i<numtrigs; i++) cout << myTriggernames[i] << ":  " << allcount_mumu[i] << endl;
	cout << "elel: " << endl;
	for (int i =0; i<numtrigs; i++) cout << myTriggernames[i] << ":  " << allcount_elel[i] << endl;
	cout << "muel: " << endl;
	for (int i =0; i<numtrigs; i++) cout << myTriggernames[i] << ":  " << allcount_muel[i] << endl;
	cout << "elmu: " << endl;
	for (int i =0; i<numtrigs; i++) cout << myTriggernames[i] << ":  " << allcount_elmu[i] << endl;
	

	
// 	std::vector<std::string> the_saved_tag_modules = hltConfig_.saveTagsModules(hltConfig_.triggerIndex("HLT_Mu17_Mu8_v1"));
// 	cout << "HLT_Mu17_Mu8_v1" << ": " << the_saved_tag_modules[0] << endl;
// 	std::vector<std::string> the_saved_tag_modules2 = hltConfig_.saveTagsModules(hltConfig_.triggerIndex("HLT_Mu17_TkMu8_v1"));
// 	cout << "HLT_Mu17_TkMu8_v1" << ": " << the_saved_tag_modules2[0] << endl;
// 	std::vector<std::string> the_saved_tag_modules3 = hltConfig_.saveTagsModules(hltConfig_.triggerIndex("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v1"));
// 	cout << "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v1" << ": " << the_saved_tag_modules3[0] << endl;
// 	std::vector<std::string> the_saved_tag_modules4 = hltConfig_.saveTagsModules(hltConfig_.triggerIndex("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v1"));
// 	cout << "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v1" << ": " << the_saved_tag_modules4[0] << endl;
// 	std::vector<std::string> the_saved_tag_modules5 = hltConfig_.saveTagsModules(hltConfig_.triggerIndex("HLT_Ele17_Ele8_Gsf_v1"));
// 	cout << "HLT_Ele17_Ele8_Gsf_v1" << ": " << the_saved_tag_modules5[0] << endl;
// 	std::vector<std::string> the_saved_tag_modules6 = hltConfig_.saveTagsModules(hltConfig_.triggerIndex("HLT_Ele23_Ele12_CaloId_TrackId_Iso_v1"));
// 	cout << "HLT_Ele23_Ele12_CaloId_TrackId_Iso_v1" << ": " << the_saved_tag_modules6[0] << endl;
// 	std::vector<std::string> the_saved_tag_modules7 = hltConfig_.saveTagsModules(hltConfig_.triggerIndex("HLT_Mu23_TrkIsoVVL_Ele12_Gsf_CaloId_TrackId_Iso_MediumWP_v1"));
// 	cout << "HLT_Mu23_TrkIsoVVL_Ele12_Gsf_CaloId_TrackId_Iso_MediumWP_v1" << ": " << the_saved_tag_modules7[0] << endl;
// 	std::vector<std::string> the_saved_tag_modules8 = hltConfig_.saveTagsModules(hltConfig_.triggerIndex("HLT_Mu8_TrkIsoVVL_Ele23_Gsf_CaloId_TrackId_Iso_MediumWP_v1"));
// 	cout << "HLT_Mu8_TrkIsoVVL_Ele23_Gsf_CaloId_TrackId_Iso_MediumWP_v1" << ": " << the_saved_tag_modules8[0] << endl;
	
	

} // anything special for the end of a run

void TriggerAna::beginLuminosityBlock(edm::LuminosityBlock const& lumi, edm::EventSetup const& evsetup){} // anything special for the beginning of a lumi block
void TriggerAna::endLuminosityBlock(edm::LuminosityBlock const& lumi, edm::EventSetup const& evsetup){} // anything special for the end of a lumi block


DEFINE_FWK_MODULE(TriggerAna);
