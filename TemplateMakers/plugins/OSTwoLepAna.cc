// created by Geoff Smith

#include "ttHMultileptonAnalysis/TemplateMakers/interface/OSTwoLepAna.h"

	
OSTwoLepAna::OSTwoLepAna(const edm::ParameterSet& constructparams){ //Anything that needs to be done at creation time
	debug = constructparams.getParameter<bool> ("debug");
	entire_pset = constructparams;
	parse_params();
}
OSTwoLepAna::~OSTwoLepAna(){} //Anything that needs to be done at destruction time

void OSTwoLepAna::beginJob()
{
	edm::Service<TFileService> newfs;
	
	
	//summaryTree = new TTree("summaryTree", "Summary Event Values"); // <-- usually we will want this
	
	sampleNumber=9120; //hack for now -> to include in parameterset
	
	miniAODhelper.SetUp(analysisYear, sampleNumber, analysisType::DIL, isData);

	miniAODhelper.SetFactorizedJetCorrector();


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
  
	trigRes triggerResults = 	GetTriggers(event);
	patMuons muons = 		GetMuons(event);
	patJets pfjets = 		GetJets(event);
	patElectrons electrons = 	GetElectrons(event);
	//  patMETs mets = 		GetMET(event);

	miniAODhelper.SetRho(rho);	
		
	int numpvs =			GetVertices(event);
	if (debug) cout << "numpvs: " << numpvs << endl;
		
	edm::Handle<GenEventInfoProduct> GenInfo;
    	event.getByLabel("generator",GenInfo);
    	double wgt = GenInfo->weight();		// <- gen-level weights
	
	double weight = 1.;			// <- analysis weight 
	//  int numEvents = 0;
	//  int numEventsFailCuts = 0;
	//  int numEventsPassCuts = 0;
	//  int printEvery = 1;
  
	
	//wgt = weight; //test

				
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

	vecPatElectron selectedElectrons_tight = miniAODhelper.GetSelectedElectrons( *electrons, mintightelept, electronID::electronTight );
	vecPatElectron selectedElectrons_loose = miniAODhelper.GetSelectedElectrons( *electrons, minlooseelept, electronID::electronLoose );
	vecPatElectron selectedElectrons_loose_notight = miniAODhelper.RemoveOverlaps( selectedElectrons_tight, selectedElectrons_loose);
	
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

	vecPatMuon selectedMuons_tight = miniAODhelper.GetSelectedMuons( *muons, mintightmupt, muonID::muonTight );
	vecPatMuon selectedMuons_loose = miniAODhelper.GetSelectedMuons( *muons, minloosemupt, muonID::muonLoose );
	vecPatMuon selectedMuons_loose_notight = miniAODhelper.RemoveOverlaps(selectedMuons_tight,selectedMuons_loose);

	int numTightMuons = int(selectedMuons_tight.size());
	int numLooseMuons = int(selectedMuons_loose.size());


	//bool isOS = false;	
	
	vecTLorentzVector muonsTLVloose = Get_vecTLorentzVector(selectedMuons_loose);
	vecTLorentzVector muonsTLVtight = Get_vecTLorentzVector(selectedMuons_tight);
			  
	vecTLorentzVector elesTLVloose = Get_vecTLorentzVector(selectedElectrons_loose);
	vecTLorentzVector elesTLVtight = Get_vecTLorentzVector(selectedElectrons_tight);
	
	
	vecTLorentzVector leptonsTLVtight = Get_vecTLorentzVector_sorted_leptons (muonsTLVtight, elesTLVtight); 
	vecTLorentzVector leptonsTLVloose = Get_vecTLorentzVector_sorted_leptons (muonsTLVloose, elesTLVloose); 
	
	vecTLorentzVector muonsTLVloosenotight = Get_vecTLorentzVector(selectedMuons_loose_notight);
	vecTLorentzVector elesTLVloosenotight = Get_vecTLorentzVector(selectedElectrons_loose_notight);
	
		
	/////////
	///
	/// Jets
	///
	////////

 	
	vecPatJet rawJets				= miniAODhelper.GetUncorrectedJets(*pfjets);
	vecPatJet jetsNoMu			       	= miniAODhelper.RemoveOverlaps(selectedMuons_loose, rawJets);
	vecPatJet jetsNoEle			       	= miniAODhelper.RemoveOverlaps(selectedElectrons_loose, rawJets);
	vecPatJet jetsNoLep			       	= miniAODhelper.RemoveOverlaps(selectedElectrons_loose, jetsNoMu);
	vecPatJet correctedJets_noSys		       	= miniAODhelper.GetCorrectedJets(jetsNoLep);
	vecPatJet selectedJets_noSys_unsorted	       	= miniAODhelper.GetSelectedJets(correctedJets_noSys, 30., 2.4, jetID::jetLoose, '-' );
	vecPatJet selectedJets_tag_noSys_unsorted	= miniAODhelper.GetSelectedJets( correctedJets_noSys, 30., 2.4, jetID::jetLoose, 'M' );
	vecPatJet selectedJets_loose_noSys_unsorted     = miniAODhelper.GetSelectedJets(correctedJets_noSys, 20., 2.4, jetID::jetLoose, '-' );
	vecPatJet selectedJets_loose_tag_noSys_unsorted	= miniAODhelper.GetSelectedJets( correctedJets_noSys, 20., 2.4, jetID::jetLoose, 'M' );

	vecTLorentzVector jetsTLVloose = Get_vecTLorentzVector(selectedJets_loose_noSys_unsorted);
	vecTLorentzVector jetsTLVtight = Get_vecTLorentzVector(selectedJets_noSys_unsorted);

	int numRawJets = rawJets.size();
	int numJetsNoEle = jetsNoEle.size();
	int numJetsNoMu = jetsNoMu.size();
	int numJetsNoLep = jetsNoLep.size();
	int numJetsCorr = correctedJets_noSys.size();

	int numSelJetsLoose = selectedJets_loose_noSys_unsorted.size();
	//int numSelJets = selectedJets_noSys_unsorted.size();

	int numSelJetsLooseCSVM = selectedJets_loose_tag_noSys_unsorted.size();


	// fill histos:

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
	// .....


	//////////////////////////////////////////////////////////////////////////////////////////////
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
	
	
	double leg1 = 20.; //pt
	double leg2 = 1.; //pt
	
	bool tightmupass = false;
	if ((numTightMuons>0)&&(muonsTLVtight[0].Pt()>leg1)) tightmupass = true;
	
	bool tightelepass = false;
	if ((numTightElectrons>0)&&(elesTLVtight[0].Pt()>leg1)) tightelepass = true;
	
	bool loosedubmupass = false;
	if (tightmupass&&(numLooseMuons>1))
	{
		if ((muonsTLVtight[0].Pt()!=muonsTLVloose[0].Pt())&&(muonsTLVloose[0].Pt()>leg2)) loosedubmupass=true;
		if ((muonsTLVtight[0].Pt()==muonsTLVloose[0].Pt())&&(muonsTLVloose[1].Pt()>leg2)) loosedubmupass=true;
	}
	
	bool loosedubelepass = false;
	if (tightelepass&&(numLooseElectrons>1))
	{
		if ((elesTLVtight[0].Pt()!=elesTLVloose[0].Pt())&&(elesTLVloose[0].Pt()>leg2)) loosedubelepass=true;
		if ((elesTLVtight[0].Pt()==elesTLVloose[0].Pt())&&(elesTLVloose[1].Pt()>leg2)) loosedubelepass=true;
	}
	
	bool muele_looseelepass = false;
	if (numLooseElectrons) if (tightmupass&&(elesTLVloose[0].Pt()>leg2)) muele_looseelepass = true;
	
	bool muele_loosemupass = false;
	if (numLooseMuons) if (tightelepass&&(muonsTLVloose[0].Pt()>leg2)) muele_loosemupass = true;
	
	


	if (tightmupass&&loosedubmupass)
	{
		if (triggerResults->accept(hltConfig_.triggerIndex(mumutriggerstostudy[0]))) doublemucount += wgt; // doublemucount++;
		if (triggerResults->accept(hltConfig_.triggerIndex(mumutriggerstostudy[1]))) doublemucount2 += wgt; // doublemucount2++;
		if (triggerResults->accept(hltConfig_.triggerIndex(mumutriggerstostudy[2]))) doublemucount3 += wgt; // doublemucount3++;
		if (triggerResults->accept(hltConfig_.triggerIndex(mumutriggerstostudy[3]))) doublemucount4 += wgt; // doublemucount4++;
		
		if (triggerResults->accept(hltConfig_.triggerIndex(mumutriggerstostudy[1]))||triggerResults->accept(hltConfig_.triggerIndex(mumutriggerstostudy[2]))) doublemucount5 += wgt;

		for (int i=0; i<triggersize; i++) if (triggerResults->accept(i)) allcount_mumu[i] += wgt;

		cout << wgt << endl;

		numpassedmumucuts += wgt; //numpassedmumucuts++;
	}

	if (tightelepass&&loosedubelepass)
	{
		if (triggerResults->accept(hltConfig_.triggerIndex(eleltriggerstostudy[0]))) doubleelecount += wgt; //doubleelecount++;
		if (triggerResults->accept(hltConfig_.triggerIndex(eleltriggerstostudy[1]))) doubleelecount2 += wgt; //doubleelecount2++;
		numpassedelelcuts += wgt; //numpassedelelcuts++;
		
		for (int i=0; i<triggersize; i++) if (triggerResults->accept(i)) allcount_elel[i] += wgt;
		
		
	}

	if (tightmupass&&muele_looseelepass)
	{
		if (triggerResults->accept(hltConfig_.triggerIndex(mueltriggerstostudy[0]))) muelecount += wgt; //muelecount++;
		numpassedmuelcuts += wgt; //numpassedmuelcuts++;
		
		for (int i=0; i<triggersize; i++) if (triggerResults->accept(i)) allcount_muel[i] += wgt;
		
	}

	if (tightelepass&&muele_loosemupass)
	{
		if (triggerResults->accept(hltConfig_.triggerIndex(elmutriggerstostudy[0]))) elemucount += wgt; //elemucount++;
		numpassedelmucuts += wgt; //numpassedelmucuts++;
		
		for (int i=0; i<triggersize; i++) if (triggerResults->accept(i)) allcount_elmu[i] += wgt;
	}

	
	
	
	
	
	
// 	if (numTightMuons>0)
// 	{
// 		if ((muonsTLVtight[0].Pt()>leg1)&&(muonsTLVtight[1].Pt()>leg2))
// 		{
// 			if (triggerResults->accept(hltConfig_.triggerIndex(mumutriggerstostudy[0]))) doublemucount += wgt; // doublemucount++;
// 			if (triggerResults->accept(hltConfig_.triggerIndex(mumutriggerstostudy[1]))) doublemucount2 += wgt; // doublemucount2++;
// 			if (triggerResults->accept(hltConfig_.triggerIndex(mumutriggerstostudy[2]))) doublemucount3 += wgt; // doublemucount3++;
// 			if (triggerResults->accept(hltConfig_.triggerIndex(mumutriggerstostudy[3]))) doublemucount4 += wgt; // doublemucount4++;
// 			
// 			//cout << wgt << endl;
// 			
// 			numpassedmumucuts += wgt; //numpassedmumucuts++;
// 		}
// 	}
// 	if (numTightElectrons>0)
// 	{
// 		if ((elesTLVtight[0].Pt()>leg1)&&(elesTLVtight[1].Pt()>leg2))
// 		{
// 			if (triggerResults->accept(hltConfig_.triggerIndex(eleltriggerstostudy[0]))) doubleelecount += wgt; //doubleelecount++;
// 			if (triggerResults->accept(hltConfig_.triggerIndex(eleltriggerstostudy[1]))) doubleelecount2 += wgt; //doubleelecount2++;
// 			numpassedelelcuts += wgt; //numpassedelelcuts++;
// 		}
// 		
// 	}
// 	if ((numTightMuons>0)||(numTightElectrons>0))
// 	{
// 		if ((muonsTLVtight[0].Pt()>leg1)&&(elesTLVtight[1].Pt()>leg2))
// 		{
// 			if (triggerResults->accept(hltConfig_.triggerIndex(mueltriggerstostudy[0]))) muelecount += wgt; //muelecount++;
// 			numpassedmuelcuts += wgt; //numpassedmuelcuts++;
// 		}
// 		
// 		if ((elesTLVtight[0].Pt()>leg1)&&(muonsTLVtight[1].Pt()>leg2))
// 		{
// 			if (triggerResults->accept(hltConfig_.triggerIndex(elmutriggerstostudy[0]))) elemucount += wgt; //elemucount++;
// 			numpassedelmucuts += wgt; //numpassedelmucuts++;
// 		}
// 	}



	
	
} // end for each event

void OSTwoLepAna::beginRun(edm::Run const& run, edm::EventSetup const& evsetup){
		
	// This has to be done here (not at beginjob):
	
	bool changed = true;
	if (hltConfig_.init(run, evsetup, hltTag, changed)) std::cout << "HLT config with process name " << hltTag << " successfully extracted" << std::endl;
	
	else std::cout << "Warning, didn't find process " << hltTag << std::endl;
	
	std::cout << " HLTConfig processName " << hltConfig_.processName() << " tableName " << hltConfig_.tableName() << " size " << hltConfig_.size() << std::endl; // " globalTag: " << hltConfig_.globalTag() << std::endl;
	
}
void OSTwoLepAna::endRun(edm::Run const& run, edm::EventSetup const& evsetup){

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


	cout << mumutriggerstostudy[0] << "  " << doublemucount << "out of " << numpassedmumucuts << endl;
	cout << mumutriggerstostudy[1] << "  " << doublemucount2 << "out of " << numpassedmumucuts << endl;
	cout << mumutriggerstostudy[2] << "  " << doublemucount3 << "out of " << numpassedmumucuts << endl;
	cout << mumutriggerstostudy[3] << "  " << doublemucount4 << "out of " << numpassedmumucuts << endl;
	cout << "  " << endl;
	cout << eleltriggerstostudy[0] << "  " << doubleelecount << "out of " << numpassedelelcuts << endl;
	cout << eleltriggerstostudy[1] << "  " << doubleelecount2 << "out of " << numpassedelelcuts << endl;
	cout << "  " << endl;
	cout << mueltriggerstostudy[0] << "  " << muelecount << "out of " << numpassedmuelcuts << endl;
	cout << "  " << endl;
	cout << elmutriggerstostudy[0] << "  " << elemucount << "out of " << numpassedelmucuts << endl;
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

void OSTwoLepAna::beginLuminosityBlock(edm::LuminosityBlock const& lumi, edm::EventSetup const& evsetup){} // anything special for the beginning of a lumi block
void OSTwoLepAna::endLuminosityBlock(edm::LuminosityBlock const& lumi, edm::EventSetup const& evsetup){} // anything special for the end of a lumi block


DEFINE_FWK_MODULE(OSTwoLepAna);
