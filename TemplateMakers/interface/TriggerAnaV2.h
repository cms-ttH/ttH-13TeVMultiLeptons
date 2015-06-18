// created by Geoff Smith

#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/MultileptonAna.h"

class TriggerAnaV2: public MultileptonAna, public edm::EDAnalyzer
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
		double doublemucount[5];
		double doublemucount2[5];
		double doublemucount3[5];
		double doublemucount4[5];
		double doublemucount5[5];
		
		double doubleelecount[5];
		double doubleelecount2[5];
		
		double muelecount[5];
		double elemucount[5]; 
		
		double tripelcount[5];
		
		double allcount_mumu[1000];
		double allcount_elel[1000];
		double allcount_muel[1000];
		double allcount_elmu[1000];		
		
		int numpassedcuts;
		double numpassedmumucuts[5];
		double numpassedelelcuts[5];
		double numpassedmuelcuts[5];
		double numpassedelmucuts[5];
                
                double doublemucount_ext[5];
                double doubleelecount_ext[5];
                double muelecount_ext[5];
                double elemucount_ext[5];	
                double tripelcount_ext[5];

                double numpassedmumucuts_ext[5];
                double numpassedelelcuts_ext[5];
                double numpassedmuelcuts_ext[5];
                double numpassedelmucuts_ext[5];

                                
                               
                vstring alltriggerstostudy;
		vstring mumutriggerstostudy;
		vstring eleltriggerstostudy;
		vstring mueltriggerstostudy;
		vstring elmutriggerstostudy;
		vstring tripeltriggerstostudy;	
		
		string extra_trig;	
		string extra_trig_mu;
                
		//Variables variables;
		//TTree *summaryTree; //("summaryTree", "Summary Event Values");
		
		void tree_add_branches();
		void initialize_variables();
		
	public:
		explicit TriggerAnaV2(const edm::ParameterSet&);
		~TriggerAnaV2();
		
		FILE * ep;
		FILE * mp;
                
		edm::EDGetTokenT<reco::BeamSpot> bsToken_;		
                edm::EDGetTokenT<reco::ConversionCollection> conversionToken_;
                
                char last_module_with_saved_tags_label[500];
		char last_module_with_2objs_label[500];
		int last_module_with_saved_tags_index;
		
                // declare the tree
		TTree *summaryTree;
		//struct Variables variables;
		//void initialize_tree();
		
		// declare any histos
		TH1D *numtighteles;
		TH1D *numlooseeles;
		TH1D *numtightmuons;
		TH1D *numloosemuons;
		TH1D *numtightleptons;
		TH1D *numlooseleptons;
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
		
		TH1D *leadingloosemupt;
		TH1D *subleadingloosemupt;
		TH1D *leadinglooseelept;
		TH1D *subleadinglooseelept;
		TH1D *leadinglooseleppt;
		TH1D *subleadinglooseleppt;
		
		TH1D *jet1pt;
		TH1D *jet2pt;
		TH1D *jet3pt;
		TH1D *jet4pt;
		TH1D *met_pt;
		TH1D *hlt_count_hist;		
		
		TH1D *numraweles;
		TH1D *numrawmuons;
		TH1D *numrawleps;
		TH1D *rawele1pt;
		TH1D *rawele2pt;
		TH1D *rawmu1pt;
		TH1D *rawmu2pt;
		TH1D *rawlep1pt;
		TH1D *rawlep2pt;
		TH1D *rawlep3ormorept;
				
		
		TH2D *lep1_lep2_pt;
		
		TH1D *genparticle_IDs;
		TH2D *gen_ele_info_vs_hlt;
		TH2D *gen_mu_info_vs_hlt;
		TH2D *genstatusinfo;
		
		TH1D *leadingEle_pat_gen_chosen_reso;
		TH1D *subleadingEle_pat_gen_chosen_reso;
		TH1D *leadingEle_pat_gen_dpt;
		TH1D *subleadingEle_pat_gen_dpt;
		TH2D *leadingEle_pat_gen_deta_dphi;
		TH2D *subleadingEle_pat_gen_deta_dphi;
		
		TH1D *leadingMuon_pat_gen_dpt;
		TH1D *subleadingMuon_pat_gen_dpt;
		TH2D *leadingMuon_pat_gen_deta_dphi;
		TH2D *subleadingMuon_pat_gen_deta_dphi;
				
		
		
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
		
		TH2D *lep1_pt_didpass_double_lep_PATobj_x_HLTobj_y[10];
		TH2D *lep2_pt_didpass_double_lep_PATobj_x_HLTobj_y[10];
		TH2D *lep1_pt_didntpass_double_lep_but_passed_single_lep_PATobj_x_HLTobj_y[10];
		TH2D *lep2_pt_didntpass_double_lep_but_passed_single_lep_PATobj_x_HLTobj_y[10];
		
		TH2D *lep1_eta_didpass_double_lep_PATobj_x_HLTobj_y[10];
		TH2D *lep2_eta_didpass_double_lep_PATobj_x_HLTobj_y[10];
		TH2D *lep1_eta_didntpass_double_lep_but_passed_single_lep_PATobj_x_HLTobj_y[10];
		TH2D *lep2_eta_didntpass_double_lep_but_passed_single_lep_PATobj_x_HLTobj_y[10];
		
                TH1D *numInitialWeightedMCevents;
		
                //////
                TH1F *SS2mu_mumu0;
                TH1F *SS2mu_mumu1;
                TH1F *SS2mu_mumu2;
                TH1F *SS2mu_mumu3;
                
                TH1F *SS2mu_mumu0_OR;
                TH1F *SS2mu_mumu1_OR;
                TH1F *SS2mu_mumu2_OR;
                TH1F *SS2mu_mumu3_OR;
                
                TH1F *SS2mu_mumu_total;
                
                TH1F *SS2mu_mu;
                TH1F *SS2mu_mu_total;
                
                //////
                TH1F *SS2el_elel0;                
                TH1F *SS2el_elel0_OR;                
                TH1F *SS2el_elel_total;
                
                TH1F *SS2el_el;
                TH1F *SS2el_el_total;
                
                //////
                TH1F *SSmuel_muel0;                
                TH1F *SSmuel_muel0_OR;                
                TH1F *SSmuel_muel_total;
                
                TH1F *SSmuel_mu;
                TH1F *SSmuel_mu_total;
                
                //////
                TH1F *SSelmu_elmu0;                
                TH1F *SSelmu_elmu0_OR;                
                TH1F *SSelmu_elmu_total;
                
                TH1F *SSelmu_el;
                TH1F *SSelmu_el_total;
                
                
                
                
                
                
                
                
                
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
		vector<ttH::Lepton> cutBased_leptons_intree;
		vector<ttH::Lepton> looseMvaBased_leptons_intree;
		vector<ttH::Lepton> tightMvaBased_leptons_intree;
 
		vector<ttH::Electron> raw_electrons_intree;               
		vector<ttH::Electron> preselected_electrons_intree;
		vector<ttH::Electron> loose_electrons_intree;
		vector<ttH::Electron> cutBased_electrons_intree;
		vector<ttH::Electron> looseMvaBased_electrons_intree;
		vector<ttH::Electron> tightMvaBased_electrons_intree;

		vector<ttH::Muon> raw_muons_intree;
                vector<ttH::Muon> preselected_muons_intree;
                vector<ttH::Muon> loose_muons_intree;
                vector<ttH::Muon> cutBased_muons_intree;
                vector<ttH::Muon> looseMvaBased_muons_intree;
                vector<ttH::Muon> tightMvaBased_muons_intree;

                vector<ttH::Jet> raw_jets_intree;
                vector<ttH::Jet> preselected_jets_intree;
		vector<ttH::Jet> loose_bJets_intree;
		vector<ttH::Jet> tight_bJets_intree;
		
		vector<ttH::MET> met_intree;
		vector<ttH::GenParticle> pruned_genParticles_intree;

                

		
};

void TriggerAnaV2::tree_add_branches()
{
	
    // add the branches to the tree:
    summaryTree->Branch("mcwgt", &mcwgt_intree);
    summaryTree->Branch("wgt", &wgt_intree);
    summaryTree->Branch("wallTimePerEvent", &wallTimePerEvent_intree);

    summaryTree->Branch("eventnum", &eventnum_intree);
    summaryTree->Branch("lumiBlock", &lumiBlock_intree);
    summaryTree->Branch("runNumber", &runNumber_intree);
    summaryTree->Branch("higgs_decay", &higgs_decay_intree);

    summaryTree->Branch("preselected_leptons", &preselected_leptons_intree);
    summaryTree->Branch("preselected_electrons", &preselected_electrons_intree);
    summaryTree->Branch("preselected_muons", &preselected_muons_intree);
    summaryTree->Branch("loose_leptons", &loose_leptons_intree);
    summaryTree->Branch("loose_electrons", &loose_electrons_intree);
    summaryTree->Branch("loose_muons", &loose_muons_intree);

    summaryTree->Branch("cutBased_leptons", &cutBased_leptons_intree);
    summaryTree->Branch("cutBased_electrons", &cutBased_electrons_intree);
    summaryTree->Branch("cutBased_muons", &cutBased_muons_intree);

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
    summaryTree->Branch("loose_bJets", &loose_bJets_intree);
    summaryTree->Branch("tight_bJets", &tight_bJets_intree);
    summaryTree->Branch("met", &met_intree);
    summaryTree->Branch("pruned_genParticles", &pruned_genParticles_intree);

	

	
}

void TriggerAnaV2::initialize_variables()
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

    cutBased_leptons_intree.clear();
    cutBased_electrons_intree.clear();
    cutBased_muons_intree.clear();

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
    loose_bJets_intree.clear();
    tight_bJets_intree.clear();

    met_intree.clear();
    pruned_genParticles_intree.clear();

    higgs_decay_intree = -9e6;
	
}
