// created by Geoff Smith

//#include "ttHMultileptonAnalysis/TemplateMakers/src/MultileptonAna.cc"
#include "ttHMultileptonAnalysis/TemplateMakers/interface/MultileptonAna.h"

// #ifdef __MAKECINT__
// 
// #pragma link C++ class Variables+;
// 
// #endif

//#if !defined(__CINT__) && !defined(__MAKECINT__)

//#include "ttHMultileptonAnalysis/TemplateMakers/interface/Variables.h"

//#endif

#pragma link C++ class std::vector< TLorentzVector >+;


//struct Variables { int test; int testt; };



class TriggerAna: public MultileptonAna, public edm::EDAnalyzer
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
		
		
		// OSTwoLep-specific vars (here, a bunch of trigger studies/counting stuff)
		double doublemucount;
		double doublemucount2;
		double doublemucount3;
		double doublemucount4;
		double doublemucount5;
		
		double doubleelecount;
		double doubleelecount2;
		
		double muelecount;
		double elemucount; 
		
		double tripelcount;
		
		double allcount_mumu[1000];
		double allcount_elel[1000];
		double allcount_muel[1000];
		double allcount_elmu[1000];		
		
		int numpassedcuts;
		double numpassedmumucuts;
		double numpassedelelcuts;
		double numpassedmuelcuts;
		double numpassedelmucuts;
		
		vstring alltriggerstostudy;
		vstring mumutriggerstostudy;
		vstring eleltriggerstostudy;
		vstring mueltriggerstostudy;
		vstring elmutriggerstostudy;
		vstring tripeltriggerstostudy;		
		
		//Variables variables;
		//TTree *summaryTree; //("summaryTree", "Summary Event Values");
		
		void tree_add_branches();
		void initialize_variables();
		
	public:
		explicit TriggerAna(const edm::ParameterSet&);
		~TriggerAna();
		
		// declare the tree
		TTree *summaryTree;
		//struct Variables variables;
		//void initialize_tree();
		
		// declare any histos
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
		
		//GenericCollection<pat::MuonCollection> tightMuons;
		
		TH1D *lep1_pt_didpass_double_lep[10];
		TH1D *lep2_pt_didpass_double_lep[10];
		TH1D *lep1_pt_didntpass_double_lep_but_passed_single_lep[10];
		TH1D *lep2_pt_didntpass_double_lep_but_passed_single_lep[10];
		
		TH1D *lep1_eta_didpass_double_lep[10];
		TH1D *lep2_eta_didpass_double_lep[10];
		TH1D *lep1_eta_didntpass_double_lep_but_passed_single_lep[10];
		TH1D *lep2_eta_didntpass_double_lep_but_passed_single_lep[10];

		TH1D *lep1_phi_didpass_double_lep[10];
		TH1D *lep2_phi_didpass_double_lep[10];
		TH1D *lep1_phi_didntpass_double_lep_but_passed_single_lep[10];
		TH1D *lep2_phi_didntpass_double_lep_but_passed_single_lep[10];

		TH1D *lep1_iso_didpass_double_lep[10];
		TH1D *lep2_iso_didpass_double_lep[10];
		TH1D *lep1_iso_didntpass_double_lep_but_passed_single_lep[10];
		TH1D *lep2_iso_didntpass_double_lep_but_passed_single_lep[10];

		
		
		TH1D *mumu_lep1_denom;
		TH1D *mumu_lep2_denom;
		TH1D *muel_lep1_denom;
		TH1D *muel_lep2_denom;
		TH1D *elel_lep1_denom;
		TH1D *elel_lep2_denom;
		TH1D *elmu_lep1_denom;
		TH1D *elmu_lep2_denom;
		
		
		// tree branches:
				
		double mcwgt_intree;
		double wgt_intree;
		
		int numLooseMuons_intree;
		int numLooseElectrons_intree;
		int numTightMuons_intree;
		int numTightElectrons_intree;
		
		int numPreselectedLeptons_intree;
		int numTightLeptons_intree;
		int numLooseLeptons_intree;
		
		int numCernMuons_intree;
		int numCernElectrons_intree;
		int numCernLeptons_intree;
		int numCernJets_intree;

		double allJetCSV_intree;
		int numJets_intree;


		
		vdouble testvect;
		
		TLorentzVectorCMS testTLV_intree;
		
		
		TLorentzVectorCMS	  MET_intree;
		std::vector<math::XYZTLorentzVectorD> Jets_intree;
		vecTLorentzVectorCMS LooseElectrons_intree;
		vecTLorentzVectorCMS LooseMuons_intree;
		vecTLorentzVectorCMS TightElectrons_intree;
		vecTLorentzVectorCMS TightMuons_intree;
		vdouble		  JetCSV_intree;
		
		
		
		

		// Variables *variables;
		
		//GenericCollectionSizeVariable<std::vector<pat::Muon>> numTightMuons(const GenericCollection<pat::MuonCollection> &, const string);
		
};

void TriggerAna::tree_add_branches()
{
	
	// add the branches to the tree:
	
	
	
	summaryTree->Branch("mcwgt", &mcwgt_intree, "mcwgt/D");
	summaryTree->Branch("wgt", &wgt_intree, "wgt/D");

	summaryTree->Branch("numLooseMuons", &numLooseMuons_intree, "numLooseMuons/I");
      	summaryTree->Branch("numLooseElectrons", &numLooseElectrons_intree, "numLooseElectrons/I");
      	summaryTree->Branch("numTightMuons", &numTightMuons_intree, "numTightMuons/I");
      	summaryTree->Branch("numTightElectrons", &numTightElectrons_intree, "numTightElectrons/I");
      	
	summaryTree->Branch("testvect", &testvect);
	//summaryTree->Branch("testTLV", &testTLV_intree);
	
	//summaryTree->Branch("Jets", "std::vector<TLorentzVector>", &Jets_intree);
	//summaryTree->Branch("Jets", "std::vector<math::XYZTLorentzVectorD>", &Jets_intree);
	summaryTree->Branch("Jets", &Jets_intree);
	summaryTree->Branch("MET", &MET_intree);
	summaryTree->Branch("LooseElectrons", &LooseElectrons_intree);
	summaryTree->Branch("LooseMuons", &LooseMuons_intree);
	summaryTree->Branch("TightElectrons", &TightElectrons_intree);
	summaryTree->Branch("TightMuons", &TightMuons_intree);
	summaryTree->Branch("JetCSV", &JetCSV_intree);
	
	
// 	numPreselectedLeptons_intree;
// 	numTightLeptons_intree;
// 	numLooseLeptons_intree;
// 		
// 	numCernMuons_intree;
// 	numCernElectrons_intree;
// 	numCernLeptons_intree;
// 	numCernJets_intree;
// 
// 	allMuonPt_intree;
// 	allElectronPt_intree;
// 	allLeptonPt_intree;
// 	allJetPt_intree;
// 	allLeptonPhi_intree;
// 
// 	allJetCSV_intree;
// 	numJets_intree;
	
	

	
	//summaryTree->Branch("variables.","Variables",&variables);
	
}

void TriggerAna::initialize_variables()
{
	testTLV_intree.SetPxPyPzE(0.,0.,0.,0.);
	
	testvect.clear();
	
	mcwgt_intree = -9999.;
	wgt_intree = -9999.;
	
	numLooseMuons_intree = -1;
	numLooseElectrons_intree = -1;
	numTightMuons_intree = -1;
	numTightElectrons_intree = -1;
	
	Jets_intree.clear();
	MET_intree.SetPxPyPzE(0.,0.,0.,0.);
	LooseElectrons_intree.clear();
	LooseMuons_intree.clear();
	TightElectrons_intree.clear();
	TightMuons_intree.clear();
	JetCSV_intree.clear();
	
	
	
	
	
}
