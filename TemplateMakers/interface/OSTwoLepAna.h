// created by Geoff Smith

#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/MultileptonAna.h"
#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/EGammaMvaEleEstimatorFWLite.h"

class OSTwoLepAna: public MultileptonAna, public edm::EDAnalyzer
{
	private:
		
		// EDAnalyzer-specific:
		virtual void beginJob() ;
      		virtual void analyze(const edm::Event&, const edm::EventSetup&);
      		virtual void endJob() ;
      		virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      		virtual void endRun(edm::Run const&, edm::EventSetup const&);
      		virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      		virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);				

		// OSTwoLep-specific
		void tree_add_branches();
		void initialize_variables();
	
	public:
		explicit OSTwoLepAna(const edm::ParameterSet&);
		~OSTwoLepAna();
		
		FILE * ep;
		FILE * mp;
			

		vstring alltriggerstostudy;
		
		// declare the tree
		TTree * summaryTree;
		
		// declare any histos
		
		//TH1D *sampleNumber
		//TH1D *nGen
		//TH1D *Xsec
		TH1D *numtighteles;
		TH1D *numlooseeles;
		TH1D *numtightmuons;
		TH1D *numloosemuons;
		TH1D *numrawjets;
		TH1D *numjetsnoele;
		TH1D *numjetsnomu;
		TH1D *numjetsnomuorele;
		TH1D *numjetscorrected;
		TH1D *numjetsselectedloose;
		TH1D *numbtagsselectedlooseCSVM;
		TH1D *leadingtightmupt;
		TH1D *subleadingtightmupt;
		TH1D *leadingtightelept;
		TH1D *subleadingtightelept;
		TH1D *leadingtightleppt;
		TH1D *subleadingtightleppt;
		TH1D *jet1pt;
		TH1D *jet2pt;
		TH1D *jet3pt;
		TH1D *jet4pt;
		TH1D *met_pt;
		TH1D *hlt_count_hist;		
		
		TH2D *lep1_lep2_pt;

		// tree branches:
				
		double mcwgt_intree;
		double wgt_intree;
		
		int numLooseMuons_intree;
		int numLooseElectrons_intree;
		int numTightMuons_intree;
		int numTightElectrons_intree;		
		//int numPreselectedLeptons_intree;
		int numTightLeptons_intree;
		int numLooseLeptons_intree;
		
		int num_preselectedLeptons_intree;
		int num_preselectedMuons_intree;		
		int num_preselectedElectrons_intree;
		
		int numCernMuons_intree;
		int numCernElectrons_intree;
		int numCernLeptons_intree;
		int numCernJets_intree;

		double allJetCSV_intree;
		//int numJets_intree;			
		int num_BJetsLoose_intree;
		int num_BJetsMedium_intree;
		int num_BJetsTight_intree;
		int num_Jets_intree;
		
		int mu1_charge_intree;
		int mu2_charge_intree;
		float mu1_pt_intree;
		float mu2_pt_intree;
		float mu1_eta_intree;
		float mu2_eta_intree;
		float mu1_phi_intree;
		float mu2_phi_intree;
		int mu1_id_intree;
		int mu2_id_intree;
		float mu1_lepMVA_intree;
		float mu2_lepMVA_intree;
		int mu1_chargeFlip_intree;
		int mu2_chargeFlip_intree;
		

		//for event dumps sync
		
		int lep1_id_intree;
		float lep1_pt_intree;
		float lep1_eta_intree;
		float lep1_phi_intree;
		
		int lep2_id_intree;
		float lep2_pt_intree;
		float lep2_eta_intree;
		float lep2_phi_intree;
		 
		float met_pt_intree;
		float met_phi_intree;

		float mu1_chRelIso_intree;
		float mu1_nuRelIso_intree;
		float mu1_jetdR_intree;
		float mu1_jetPtRatio_intree;
		float mu1_bTagCSV_intree;
		float mu1_sip3d_intree;
		
		int ele1_charge_intree;
		int ele2_charge_intree;
		float ele1_pt_intree;
		float ele2_pt_intree;
		float ele1_eta_intree;
		float ele2_eta_intree;
		float ele1_phi_intree;
		float ele2_phi_intree;
		int ele1_id_intree;
		int ele2_id_intree;
		float ele1_lepMVA_intree;
		float ele2_lepMVA_intree;
		int ele1_chargeFlip_intree;
		int ele2_chargeFlip_intree;

		float ele1_chRelIso_intree;
		float ele1_nuRelIso_intree;
		float ele1_jetdR_intree;
		float ele1_jetPtRatio_intree;
		float ele1_bTagCSV_intree;
		float ele1_sip3d_intree;
		
		int eventnum_intree;
		int higgs_decay_intree;

                vector<ttH::Lepton> PreselectedLeptons_intree;
		TLorentzVectorCMS testTLV_intree;
		TLorentzVectorCMS MET_intree;
		vecTLorentzVectorCMS Jets_intree;
		vecTLorentzVectorCMS LooseElectrons_intree;
		vecTLorentzVectorCMS LooseMuons_intree;
		vecTLorentzVectorCMS TightElectrons_intree;
		vecTLorentzVectorCMS TightMuons_intree;
		vdouble	JetCSV_intree;
		


		// additional variables from 2012
		double myFinalBDT_OS_2012_intree;
		
		int lumiBlock_intree;
		int runNumber_intree;
		int numExtraPartons_intree;
		
		// PassTwoLepton
	      	//MuonElectron
	      	//TwoElectron
	      	//TwoMuon
		
		vint allLeptonGenGrandMotherId_intree;
		vint allLeptonGenMotherId_intree;
		vint allLeptonTkCharge_intree;
		double AvgBtagDiscNonBtags_intree;
		double AvgBtagDiscBtags_intree;
		double NumHiggsLikeDijet15_intree;
		double HiggsLikeDijetMass2_intree;
		double HiggsLikeDijetMass_intree;
		double GenHiggsDijetMass_intree;
		double DeltaPhiMetLepLep_intree;
		double DeltaRMetLepLep_intree;
		double MTMetLepLep_intree;
		double MassMetLepLep_intree;
		double MaxDeltaPhiMetJet_fromHiggs_intree;
		double MinDeltaPhiMetJet_fromHiggs_intree;
		double MaxDeltaPhiMetJet_intree;
		double MinDeltaPhiMetJet_intree;
		double DeltaPhiMetLep2_intree;
		double DeltaPhiMetLep1_intree;
		double DeltaRJets_FromHiggs_intree;
		double DeltaPhiJets_FromHiggs_intree;
		double WLikeDijetMass81_intree;
		double SumNonTaggedJetMass_intree;
		double SumJetMass_intree;
		double SumJetPt_intree;
		double SumPt_intree;
		double MinDrJets_intree;
		double MHT_intree;
		double DeltaPhiLepLep_intree;
		double DeltaRLepLep_intree;
		double Zmass_intree;
		double MassLepLep_intree;
		int HiggsDecayType_intree;
		
		int checkTrig_intree;
		//double Clean;
		double LepTrigCorr_intree;
		double LepIDAndIsoSF_intree;
		double TopPt_intree;
		double TopPtCorr_intree;
		double PU_intree;
		double PUCorr_intree;
		
		//numLooseBJets;
		//numMediumBJets;
		//numTightBJets;
		
		int numJets_fromHiggs_30_intree;
		int numJets_fromHiggs_intree;
				
		//cutvars
		
		bool PassZmask_cut;
		bool numTightLeptons_cut;
		bool numTightLooseLeptons_cut;
		bool isOS_cut;
		bool numJets_cut;

};

void OSTwoLepAna::tree_add_branches()
{
	
	// add the branches to the tree:
	
	
	summaryTree->Branch("checkTrig", &checkTrig_intree, "checkTrig/I");
		
	summaryTree->Branch("LepTrigCorr", &LepTrigCorr_intree);
	summaryTree->Branch("LepIDAndIsoSF", &LepIDAndIsoSF_intree);
	summaryTree->Branch("TopPt", &TopPt_intree);
	summaryTree->Branch("TopPtCorr", &TopPtCorr_intree);
	summaryTree->Branch("PU", &PU_intree);
	summaryTree->Branch("PUCorr", &PUCorr_intree);
	
	summaryTree->Branch("mcwgt", &mcwgt_intree, "mcwgt/D");
	summaryTree->Branch("wgt", &wgt_intree, "wgt/D");
	
	
	summaryTree->Branch("eventnum", &eventnum_intree, "eventnum/I");
	summaryTree->Branch("lumiBlock", &lumiBlock_intree, "lumiBlock/I");
	summaryTree->Branch("runNumber", &runNumber_intree, "runNumber/I");
	summaryTree->Branch("numExtraPartons", &numExtraPartons_intree, "numExtraPartons/I");
	summaryTree->Branch("higgs_decay", &higgs_decay_intree);
	//int HiggsDecayType_intree;
	
	summaryTree->Branch("allLeptonGenGrandMotherId", &allLeptonGenGrandMotherId_intree);
	summaryTree->Branch("allLeptonGenMotherId", &allLeptonGenMotherId_intree);
	summaryTree->Branch("allLeptonTkCharge", &allLeptonTkCharge_intree);

	summaryTree->Branch("numLooseMuons", &numLooseMuons_intree, "numLooseMuons/I");
      	summaryTree->Branch("numLooseElectrons", &numLooseElectrons_intree, "numLooseElectrons/I");
      	summaryTree->Branch("numTightMuons", &numTightMuons_intree, "numTightMuons/I");
      	summaryTree->Branch("numTightElectrons", &numTightElectrons_intree, "numTightElectrons/I");
	summaryTree->Branch("num_preselectedMuons", &num_preselectedMuons_intree, "num_preselectedMuons/I");
      	summaryTree->Branch("num_preselectedElectrons", &num_preselectedElectrons_intree, "num_preselectedElectrons/I");	
	summaryTree->Branch("num_preselectedLeptons",&num_preselectedLeptons_intree);
	
	summaryTree->Branch("Jets", &Jets_intree);
	summaryTree->Branch("MET", &MET_intree);
	summaryTree->Branch("LooseElectrons", &LooseElectrons_intree);
	summaryTree->Branch("LooseMuons", &LooseMuons_intree);
	summaryTree->Branch("TightElectrons", &TightElectrons_intree);
	summaryTree->Branch("TightMuons", &TightMuons_intree);
	summaryTree->Branch("JetCSV", &JetCSV_intree);

	summaryTree->Branch("PreselectedLeptons", &PreselectedLeptons_intree);

	summaryTree->Branch("lep1_id",&lep1_id_intree);
	summaryTree->Branch("lep1_pt",&lep1_pt_intree);
	summaryTree->Branch("lep1_eta",&lep1_eta_intree);
	summaryTree->Branch("lep1_phi",&lep1_phi_intree);
	
	summaryTree->Branch("lep2_id",&lep2_id_intree);
	summaryTree->Branch("lep2_pt",&lep2_pt_intree);
	summaryTree->Branch("lep2_eta",&lep2_eta_intree);
	summaryTree->Branch("lep2_phi",&lep2_phi_intree);
	summaryTree->Branch("met_pt",&met_pt_intree);
	summaryTree->Branch("met_phi",&met_phi_intree);
	
	summaryTree->Branch("num_Jets",&num_Jets_intree);
	summaryTree->Branch("num_BJetsLoose",&num_BJetsLoose_intree);
	summaryTree->Branch("num_BJetsMedium_intree",&num_BJetsMedium_intree);
	summaryTree->Branch("num_BJetsTight_intree",&num_BJetsTight_intree);
	
	summaryTree->Branch("numJets_fromHiggs_30", &numJets_fromHiggs_30_intree, "numJets_fromHiggs_30/I");
	summaryTree->Branch("numJets_fromHiggs", &numJets_fromHiggs_intree, "numJets_fromHiggs/I");
		
	
	//summaryTree->Branch("num_muons",&num_preselectedMuons_intree);
	summaryTree->Branch("mu1_charge",&mu1_charge_intree);
	summaryTree->Branch("mu2_charge",&mu2_charge_intree);
	summaryTree->Branch("mu1_pt",&mu1_pt_intree);
	summaryTree->Branch("mu2_pt",&mu2_pt_intree);
	summaryTree->Branch("mu1_eta",&mu1_eta_intree);
	summaryTree->Branch("mu2_eta",&mu2_eta_intree);
	summaryTree->Branch("mu1_phi",&mu1_phi_intree);
	summaryTree->Branch("mu2_phi",&mu2_phi_intree);
	summaryTree->Branch("mu1_id",&mu1_id_intree);
	summaryTree->Branch("mu2_id",&mu2_id_intree);
	summaryTree->Branch("mu1_lepMVA",&mu1_lepMVA_intree);
	summaryTree->Branch("mu2_lepMVA",&mu2_lepMVA_intree);
	summaryTree->Branch("mu1_chargeFlip",&mu1_chargeFlip_intree);
	summaryTree->Branch("mu2_chargeFlip",&mu2_chargeFlip_intree);

	summaryTree->Branch("mu1_chreliso",&mu1_chRelIso_intree);
	summaryTree->Branch("mu1_nureliso",&mu1_nuRelIso_intree);
	summaryTree->Branch("mu1_jetdR",&mu1_jetdR_intree);
	summaryTree->Branch("mu1_jetPtRatio",&mu1_jetPtRatio_intree);
	summaryTree->Branch("mu1_bTagCSV",&mu1_bTagCSV_intree);
	summaryTree->Branch("mu1_sip3d",&mu1_sip3d_intree);

	//summaryTree->Branch("num_electrons",&num_preselectedElectrons_intree);
	summaryTree->Branch("ele1_charge",&ele1_charge_intree);
	summaryTree->Branch("ele2_charge",&ele2_charge_intree);
	summaryTree->Branch("ele1_pt",&ele1_pt_intree);
	summaryTree->Branch("ele2_pt",&ele2_pt_intree);

	summaryTree->Branch("ele1_eta",&ele1_eta_intree);
	summaryTree->Branch("ele2_eta",&ele2_eta_intree);
	summaryTree->Branch("ele1_phi",&ele1_phi_intree);
	summaryTree->Branch("ele2_phi",&ele2_phi_intree);
	summaryTree->Branch("ele1_id",&ele1_id_intree);
	summaryTree->Branch("ele2_id",&ele2_id_intree);

	summaryTree->Branch("ele1_lepMVA",&ele1_lepMVA_intree);
	summaryTree->Branch("ele2_lepMVA",&ele2_lepMVA_intree);
	summaryTree->Branch("ele1_chargeFlip",&ele1_chargeFlip_intree);
	summaryTree->Branch("ele2_chargeFlip",&ele2_chargeFlip_intree);

	summaryTree->Branch("ele1_chreliso",&ele1_chRelIso_intree);
	summaryTree->Branch("ele1_nureliso",&ele1_nuRelIso_intree);
	summaryTree->Branch("ele1_jetdR",&ele1_jetdR_intree);
	summaryTree->Branch("ele1_jetPtRatio",&ele1_jetPtRatio_intree);
	summaryTree->Branch("ele1_bTagCSV",&ele1_bTagCSV_intree);
	summaryTree->Branch("ele1_sip3d",&ele1_sip3d_intree);

	//summaryTree->Branch("event",&eventnum_intree);

	summaryTree->Branch("AvgBtagDiscNonBtags", &AvgBtagDiscNonBtags_intree);
	summaryTree->Branch("AvgBtagDiscBtags", &AvgBtagDiscBtags_intree);
	summaryTree->Branch("NumHiggsLikeDijet15", &NumHiggsLikeDijet15_intree);
	summaryTree->Branch("HiggsLikeDijetMass2", &HiggsLikeDijetMass2_intree);
	summaryTree->Branch("HiggsLikeDijetMass", &HiggsLikeDijetMass_intree);
	summaryTree->Branch("GenHiggsDijetMass", &GenHiggsDijetMass_intree);
	summaryTree->Branch("DeltaPhiMetLepLep", &DeltaPhiMetLepLep_intree);
	summaryTree->Branch("DeltaRMetLepLep", &DeltaRMetLepLep_intree);
	summaryTree->Branch("MTMetLepLep", &MTMetLepLep_intree);
	summaryTree->Branch("MassMetLepLep", &MassMetLepLep_intree);
	summaryTree->Branch("MaxDeltaPhiMetJet", &MaxDeltaPhiMetJet_fromHiggs_intree);
	summaryTree->Branch("MinDeltaPhiMetJet", &MinDeltaPhiMetJet_fromHiggs_intree);
	summaryTree->Branch("MaxDeltaPhiMetJet", &MaxDeltaPhiMetJet_intree);
	summaryTree->Branch("MinDeltaPhiMetJet", &MinDeltaPhiMetJet_intree);
	summaryTree->Branch("DeltaPhiMetLep2", &DeltaPhiMetLep2_intree);
	summaryTree->Branch("DeltaPhiMetLep1", &DeltaPhiMetLep1_intree);
	summaryTree->Branch("DeltaRJets_FromHiggs", &DeltaRJets_FromHiggs_intree);
	summaryTree->Branch("DeltaPhiJets_FromHiggs", &DeltaPhiJets_FromHiggs_intree);
	summaryTree->Branch("WLikeDijetMass81", &WLikeDijetMass81_intree);
	summaryTree->Branch("SumNonTaggedJetMass", &SumNonTaggedJetMass_intree);
	summaryTree->Branch("SumJetMass", &SumJetMass_intree);
	summaryTree->Branch("SumJetPt", &SumJetPt_intree);
	summaryTree->Branch("SumPt", &SumPt_intree);
	summaryTree->Branch("MinDrJets", &MinDrJets_intree);
	summaryTree->Branch("MHT", &MHT_intree);
	summaryTree->Branch("DeltaPhiLepLep", &DeltaPhiLepLep_intree);
	summaryTree->Branch("DeltaRLepLep", &DeltaRLepLep_intree);
	summaryTree->Branch("Zmass", &Zmass_intree);
	summaryTree->Branch("MassLepLep", &MassLepLep_intree);

	summaryTree->Branch("myFinalBDT_OS_2012", &myFinalBDT_OS_2012_intree, "myFinalBDT_OS_2012/D");
	
}

void OSTwoLepAna::initialize_variables()
{
	//testTLV_intree.SetPxPyPzE(0.,0.,0.,0.);
	
	
	checkTrig_intree = -1;
	
	LepTrigCorr_intree = -9.e6;
	LepIDAndIsoSF_intree = -9.e6;
	TopPt_intree = -9.e6;
	TopPtCorr_intree = -9.e6;
	PU_intree = -9.e6;
	PUCorr_intree = -9.e6;	
	
	mcwgt_intree = -9999.;
	wgt_intree = -9999.;
	
	eventnum_intree = -99;
	lumiBlock_intree = -99;
	runNumber_intree = -99;
	numExtraPartons_intree = -99;
	higgs_decay_intree = -9999;
	
	allLeptonGenGrandMotherId_intree.clear();
	allLeptonGenMotherId_intree.clear();
	allLeptonTkCharge_intree.clear();
	
	numLooseMuons_intree = -1;
	numLooseElectrons_intree = -1;
	numTightMuons_intree = -1;
	numTightElectrons_intree = -1;
	num_preselectedMuons_intree = -1;
	num_preselectedElectrons_intree = -1;
	num_preselectedLeptons_intree = -1;
	
	PreselectedLeptons_intree.clear();

	Jets_intree.clear();
	MET_intree.SetPxPyPzE(0.,0.,0.,0.);
	LooseElectrons_intree.clear();
	LooseMuons_intree.clear();
	TightElectrons_intree.clear();
	TightMuons_intree.clear();
	JetCSV_intree.clear();
	
	lep1_id_intree = -9e6;
	lep1_pt_intree = -9.e6;
	lep1_eta_intree = -9.e6;
	lep1_phi_intree = -9.e6;
	
	lep2_id_intree = -9e6;
	lep2_pt_intree = -9.e6;
	lep2_eta_intree = -9.e6;
	lep2_phi_intree = -9.e6;
	
	met_pt_intree = -9.e6;
	met_phi_intree = -9.e6;



	num_Jets_intree= -99;
	num_BJetsLoose_intree = -99;
	num_BJetsMedium_intree = -99;
	num_BJetsTight_intree = -99;
	
	numJets_fromHiggs_30_intree = -99;
	numJets_fromHiggs_intree = -99;

	num_preselectedLeptons_intree = -99;

	num_preselectedMuons_intree = -99;
        mu1_charge_intree = -99;
        mu2_charge_intree = -99;
        mu1_pt_intree = -9.e6;
        mu2_pt_intree = -9.e6;
        mu1_lepMVA_intree = -9.e6;
        mu2_lepMVA_intree = -9.e6;
        mu1_chargeFlip_intree = -99;
	mu2_chargeFlip_intree = -99;

        mu1_chRelIso_intree = -9.e6;
        mu1_nuRelIso_intree = -9.e6;
        mu1_jetdR_intree = -9.e6;
        mu1_jetPtRatio_intree = -9.e6;
        mu1_bTagCSV_intree = -9.e6;
        mu1_sip3d_intree = -9.e6;

	num_preselectedElectrons_intree= -99;
	ele1_charge_intree= -99;
	ele2_charge_intree= -99;
        ele1_pt_intree = -9.e6;
        ele2_pt_intree = -9.e6;
        ele1_lepMVA_intree = -9.e6;
        ele2_lepMVA_intree = -9.e6;
        ele1_chargeFlip_intree= -99;
        ele2_chargeFlip_intree= -99;

	ele1_chRelIso_intree = -9.e6;
	ele1_nuRelIso_intree = -9.e6;
        ele1_jetdR_intree = -9.e6;
        ele1_jetPtRatio_intree = -9.e6;
        ele1_bTagCSV_intree = -9.e6;
        ele1_sip3d_intree = -9.e6;

        higgs_decay_intree = -9e6;
	
	AvgBtagDiscNonBtags_intree = -9e6;
	AvgBtagDiscBtags_intree = -9e6;
	NumHiggsLikeDijet15_intree = -9e6;
	HiggsLikeDijetMass2_intree = -9e6;
	HiggsLikeDijetMass_intree = -9e6;
	GenHiggsDijetMass_intree = -9e6;
	DeltaPhiMetLepLep_intree = -9e6;
	DeltaRMetLepLep_intree = -9e6;
	MTMetLepLep_intree = -9e6;
	MassMetLepLep_intree = -9e6;
	MaxDeltaPhiMetJet_fromHiggs_intree = -9e6;
	MinDeltaPhiMetJet_fromHiggs_intree = -9e6;
	MaxDeltaPhiMetJet_intree = -9e6;
	MinDeltaPhiMetJet_intree = -9e6;
	DeltaPhiMetLep2_intree = -9e6;
	DeltaPhiMetLep1_intree = -9e6;
	DeltaRJets_FromHiggs_intree = -9e6;
	DeltaPhiJets_FromHiggs_intree = -9e6;
	WLikeDijetMass81_intree = -9e6;
	SumNonTaggedJetMass_intree = -9e6;
	SumJetMass_intree = -9e6;
	SumJetPt_intree = -9e6;
	SumPt_intree = -9e6;
	MinDrJets_intree = -9e6;
	MHT_intree = -9e6;
	DeltaPhiLepLep_intree = -9e6;
	DeltaRLepLep_intree = -9e6;
	Zmass_intree = -9e6;
	MassLepLep_intree = -9e6;

	myFinalBDT_OS_2012_intree = -9.e6;
	
	
}

/*  LocalWords:  lumi
 */
