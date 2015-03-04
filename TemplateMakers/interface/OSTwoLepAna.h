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
		
		// tree branches:
		double mcwgt_intree;
		double wgt_intree;
		double wallTimePerEvent_intree;

		int eventnum_intree;
		int higgs_decay_intree;

		int lumiBlock_intree;
		int runNumber_intree;

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
		vector<ttH::Jet> tight_bJets_intree;
		
		vector<ttH::MET> met_intree;
		
		vector<ttH::GenParticle> pruned_genParticles_intree;
		
		

       edm::EDGetTokenT<reco::BeamSpot> bsToken_;		
       edm::EDGetTokenT<reco::ConversionCollection> conversionToken_;

};

void OSTwoLepAna::tree_add_branches()
{
	// add the branches to the tree:
	summaryTree->Branch("mcwgt", &mcwgt_intree, "mcwgt/D");
	summaryTree->Branch("wgt", &wgt_intree, "wgt/D");
	summaryTree->Branch("wallTimePerEvent", &wallTimePerEvent_intree, "wallTimePerEvent/D");
	
	summaryTree->Branch("eventnum", &eventnum_intree, "eventnum/I");
	summaryTree->Branch("lumiBlock", &lumiBlock_intree, "lumiBlock/I");
	summaryTree->Branch("runNumber", &runNumber_intree, "runNumber/I");
	summaryTree->Branch("higgs_decay", &higgs_decay_intree);

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
	summaryTree->Branch("tight_bJets", &tight_bJets_intree);
	summaryTree->Branch("met", &met_intree);
	summaryTree->Branch("pruned_genParticles", &pruned_genParticles_intree);
}

void OSTwoLepAna::initialize_variables()
{
	mcwgt_intree = -9999.;
	wgt_intree = -9999.;
	wallTimePerEvent_intree = -9999.;

	eventnum_intree = -99;
	lumiBlock_intree = -99;
	runNumber_intree = -99;
	
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
	tight_bJets_intree.clear();
	
	met_intree.clear();

	pruned_genParticles_intree.clear();

        higgs_decay_intree = -9e6;
}

/*  LocalWords:  lumi
 */
