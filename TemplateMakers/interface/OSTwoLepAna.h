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
		
		ofstream fout;
		FILE * lep1;
		FILE * el2;
		FILE * el3;
		FILE * el4;
		FILE * ml2;
		FILE * ml3;
		FILE * ml4;
		
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
		
		double allJetCSV_intree;

		int eventnum_intree;
		int higgs_decay_intree;

                vector<ttH::Lepton> preselected_leptons_intree;
		vector<ttH::Lepton> loose_leptons_intree;
		vector<ttH::Lepton> tight_leptons_intree;
 
		vector<ttH::Electron> raw_electrons_intree;               
		vector<ttH::Electron> preselected_electrons_intree;
		vector<ttH::Electron> loose_electrons_intree;
		vector<ttH::Electron> tight_electrons_intree;

		vector<ttH::Muon> raw_muons_intree;
                vector<ttH::Muon> preselected_muons_intree;
                vector<ttH::Muon> loose_muons_intree;
                vector<ttH::Muon> tight_muons_intree;

                vector<ttH::Jet> preselected_jets_intree;
		vector<ttH::Jet> loose_bJets_intree;
		
		vector<ttH::MET> met_intree;
		
		vector<ttH::GenParticle> pruned_genParticles_intree;
		
		// additional variables from 2012
		double myFinalBDT_OS_2012_intree;
		
		int lumiBlock_intree;
		int runNumber_intree;
		int numExtraPartons_intree;
		
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
		double wallTimePerEvent_intree;
		int HiggsDecayType_intree;
		
		int checkTrig_intree;
		//double Clean;
		double LepTrigCorr_intree;
		double LepIDAndIsoSF_intree;
		double TopPt_intree;
		double TopPtCorr_intree;
		double PU_intree;
		double PUCorr_intree;
		
		int numJets_fromHiggs_30_intree;
		int numJets_fromHiggs_intree;
				
		//cutvars
		
		bool PassZmask_cut;
		bool numTightLeptons_cut;
		bool numTightLooseLeptons_cut;
		bool isOS_cut;
		bool numJets_cut;

       edm::EDGetTokenT<reco::BeamSpot> bsToken_;		
       edm::EDGetTokenT<reco::ConversionCollection> conversionToken_;

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
	summaryTree->Branch("wallTimePerEvent", &wallTimePerEvent_intree, "wallTimePerEvent/D");
	
	
	summaryTree->Branch("eventnum", &eventnum_intree, "eventnum/I");
	summaryTree->Branch("lumiBlock", &lumiBlock_intree, "lumiBlock/I");
	summaryTree->Branch("runNumber", &runNumber_intree, "runNumber/I");
	summaryTree->Branch("numExtraPartons", &numExtraPartons_intree, "numExtraPartons/I");
	summaryTree->Branch("higgs_decay", &higgs_decay_intree);
	//int HiggsDecayType_intree;
	
	summaryTree->Branch("allLeptonGenGrandMotherId", &allLeptonGenGrandMotherId_intree);
	summaryTree->Branch("allLeptonGenMotherId", &allLeptonGenMotherId_intree);
	summaryTree->Branch("allLeptonTkCharge", &allLeptonTkCharge_intree);


	summaryTree->Branch("preselected_leptons", &preselected_leptons_intree);
	summaryTree->Branch("preselected_electrons", &preselected_electrons_intree);
	summaryTree->Branch("preselected_muons", &preselected_muons_intree);
	summaryTree->Branch("loose_leptons", &loose_leptons_intree);
	summaryTree->Branch("loose_electrons", &loose_electrons_intree);
	summaryTree->Branch("loose_muons", &loose_muons_intree);
	summaryTree->Branch("tight_leptons", &tight_leptons_intree);
	summaryTree->Branch("tight_electrons", &tight_electrons_intree);
	summaryTree->Branch("tight_muons", &tight_muons_intree);
	summaryTree->Branch("raw_electrons", &raw_electrons_intree);
	summaryTree->Branch("raw_muons", &raw_muons_intree);
	summaryTree->Branch("preselected_jets", &preselected_jets_intree);
	summaryTree->Branch("loose_bJets", &loose_bJets_intree);
	summaryTree->Branch("met", &met_intree);
	summaryTree->Branch("pruned_genParticles", &pruned_genParticles_intree);
	

	summaryTree->Branch("numJets_fromHiggs_30", &numJets_fromHiggs_30_intree, "numJets_fromHiggs_30/I");
	summaryTree->Branch("numJets_fromHiggs", &numJets_fromHiggs_intree, "numJets_fromHiggs/I");
		
	
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
	wallTimePerEvent_intree = -9999.;

	eventnum_intree = -99;
	lumiBlock_intree = -99;
	runNumber_intree = -99;
	numExtraPartons_intree = -99;
	higgs_decay_intree = -9999;
	
	allLeptonGenGrandMotherId_intree.clear();
	allLeptonGenMotherId_intree.clear();
	allLeptonTkCharge_intree.clear();
	
	preselected_leptons_intree.clear();
	preselected_electrons_intree.clear();
	preselected_muons_intree.clear();
	loose_leptons_intree.clear();
	loose_electrons_intree.clear();
	loose_muons_intree.clear();
	tight_leptons_intree.clear();
	tight_electrons_intree.clear();
	tight_muons_intree.clear();
	raw_electrons_intree.clear();
	raw_muons_intree.clear();

	preselected_jets_intree.clear();
	loose_bJets_intree.clear();
	
	met_intree.clear();

	pruned_genParticles_intree.clear();

	numJets_fromHiggs_30_intree = -99;
	numJets_fromHiggs_intree = -99;

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
