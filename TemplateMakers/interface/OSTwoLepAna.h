// created by Geoff Smith

#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/MultileptonAna.h"
#include <boost/any.hpp>

class OSTwoLepAna: public MultileptonAna, public edm::EDAnalyzer
{
	private:
	
		HLTPrescaleProvider hltPrescaleProvider_;
		
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
		vstring hlt_alltrigs;
	public:
		explicit OSTwoLepAna(const edm::ParameterSet&);
		~OSTwoLepAna();
		
		ofstream fout;
                FILE * ffout;
		
		vstring alltriggerstostudy;
		
                // declare any histos
                // Charlie, don't worry we'll keep these to a minimum..
                TH1D *numInitialWeightedMCevents; // <- easily keep track of num (weighted) mc events we started with
                
		// declare the tree
		TTree * summaryTree;
		
		// tree branches:
		double mcwgt_intree;
		double wgt_intree;
		double wallTimePerEvent_intree;
                
		vstring passTrigger_intree;

		std::string higgs_final_state;
		std::string top_final_state; 
		
		int eventnum_intree;
		int higgs_decay_intree;

		int lumiBlock_intree;
		int runNumber_intree;
		
		vector<ttH::Lepton> preselected_leptons_intree;
		vector<ttH::Lepton> loose_leptons_intree;
		vector<ttH::Lepton> looseMvaBased_leptons_intree;
		vector<ttH::Lepton> tightMvaBased_leptons_intree;
 
		vector<ttH::Electron> raw_electrons_intree;               
		vector<ttH::Electron> preselected_electrons_intree;
		vector<ttH::Electron> loose_electrons_intree;
		vector<ttH::Electron> looseMvaBased_electrons_intree;
		vector<ttH::Electron> tightMvaBased_electrons_intree;

		vector<ttH::Muon> raw_muons_intree;
		vector<ttH::Muon> preselected_muons_intree;
		vector<ttH::Muon> loose_muons_intree;
		vector<ttH::Muon> looseMvaBased_muons_intree;
		vector<ttH::Muon> tightMvaBased_muons_intree;
                
                vector<ttH::Tau> preselected_taus_intree;
                vector<ttH::Tau> selected_taus_intree;

		vector<ttH::Jet> raw_jets_intree;
		vector<ttH::Jet> preselected_jets_intree;
		vector<ttH::Jet> preselected_jets_uncor_intree;
                
		vector<ttH::Jet> loose_bJets_intree;
		vector<ttH::Jet> tight_bJets_intree;
		
		vector<ttH::MET> met_intree;
		vector<ttH::GenParticle> pruned_genParticles_intree;
		vector<ttH::GenParticle> packed_genParticles_intree;
		vector<ttH::GenParticle> genJets_intree;
		
		edm::EDGetTokenT<pat::MuonCollection> muons_token_;
		edm::EDGetTokenT<pat::ElectronCollection> electrons_token_;
		edm::EDGetTokenT<pat::TauCollection> taus_token_;

                int singleEleCount;
                int singleMuCount;
                int singleTauCount;
                int singleJetCount;
                
};

void OSTwoLepAna::tree_add_branches()
{
  // add the branches to the tree:
  summaryTree->Branch("mcwgt", &mcwgt_intree);
  summaryTree->Branch("wgt", &wgt_intree);
  summaryTree->Branch("wallTimePerEvent", &wallTimePerEvent_intree);
  
  summaryTree->Branch("eventnum", &eventnum_intree);
  summaryTree->Branch("lumiBlock", &lumiBlock_intree);
  summaryTree->Branch("runNumber", &runNumber_intree);
  summaryTree->Branch("higgs_decay", &higgs_decay_intree);
  
  summaryTree->Branch("passTrigger", &passTrigger_intree);
  //summaryTree->Branch("passTrigger", passTrigger_intree, "passTrigger/C");
  
  summaryTree->Branch("preselected_leptons", &preselected_leptons_intree);
  summaryTree->Branch("preselected_electrons", &preselected_electrons_intree);
  summaryTree->Branch("preselected_muons", &preselected_muons_intree);
  summaryTree->Branch("preselected_taus", &preselected_taus_intree);
  summaryTree->Branch("selected_taus", &selected_taus_intree);
  
  summaryTree->Branch("loose_leptons", &loose_leptons_intree);
  summaryTree->Branch("loose_electrons", &loose_electrons_intree);
  summaryTree->Branch("loose_muons", &loose_muons_intree);
  
  summaryTree->Branch("looseMvaBased_leptons", &looseMvaBased_leptons_intree);
  summaryTree->Branch("looseMvaBased_electrons", &looseMvaBased_electrons_intree);
  summaryTree->Branch("looseMvaBased_muons", &looseMvaBased_muons_intree);
  
  summaryTree->Branch("tightMvaBased_leptons", &tightMvaBased_leptons_intree);
  summaryTree->Branch("tightMvaBased_electrons", &tightMvaBased_electrons_intree);
  summaryTree->Branch("tightMvaBased_muons", &tightMvaBased_muons_intree);
  
  summaryTree->Branch("raw_electrons", &raw_electrons_intree);
  summaryTree->Branch("raw_muons", &raw_muons_intree);
  summaryTree->Branch("raw_jets", &raw_jets_intree);
  
  summaryTree->Branch("preselected_jets", &preselected_jets_intree);
  summaryTree->Branch("preselected_jets_uncor", &preselected_jets_uncor_intree);
  
  //summaryTree->Branch("loose_bJets", &loose_bJets_intree);
  //summaryTree->Branch("tight_bJets", &tight_bJets_intree);
  summaryTree->Branch("met", &met_intree);
  summaryTree->Branch("pruned_genParticles", &pruned_genParticles_intree);
  summaryTree->Branch("packed_genParticles", &packed_genParticles_intree);
  summaryTree->Branch("genJets", &genJets_intree);
}

void OSTwoLepAna::initialize_variables()
{
  mcwgt_intree = -9999.;
  wgt_intree = -9999.;
  wallTimePerEvent_intree = -9999.;
  
  eventnum_intree = -99;
  lumiBlock_intree = -99;
  runNumber_intree = -99;
  //passTrigger_intree = false;
  passTrigger_intree.clear();
  preselected_leptons_intree.clear();
  preselected_electrons_intree.clear();
  preselected_muons_intree.clear();
  preselected_taus_intree.clear();
  selected_taus_intree.clear();
  loose_leptons_intree.clear();
  loose_electrons_intree.clear();
  loose_muons_intree.clear();
  
  looseMvaBased_leptons_intree.clear();
  looseMvaBased_electrons_intree.clear();
  looseMvaBased_muons_intree.clear();
  
  tightMvaBased_leptons_intree.clear();
  tightMvaBased_electrons_intree.clear();
  tightMvaBased_muons_intree.clear();
  
  raw_electrons_intree.clear();
  raw_muons_intree.clear();
  raw_jets_intree.clear();
  
  preselected_jets_intree.clear();
  preselected_jets_uncor_intree.clear();
  //loose_bJets_intree.clear();
  //tight_bJets_intree.clear();
	
  met_intree.clear();
  pruned_genParticles_intree.clear();
  packed_genParticles_intree.clear();
  genJets_intree.clear();
  
  higgs_decay_intree = 0;
  higgs_final_state = "none";
  top_final_state = "none";
}

/*  LocalWords:  lumi
 */
