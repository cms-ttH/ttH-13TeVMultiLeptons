// created by Geoff Smith

#include "ttH-13TeVMultiLeptons/TemplateMakers/interface/MultileptonAna.h"
#include <boost/any.hpp>

// includes
#include "LHAPDF/LHAPDF.h"
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"

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
        
        TH1D *numInitialWeightedMCevents; // <- easily keep track of num (weighted) mc events we started with
        TH1D *numSummedWeights_pdfUp;
        TH1D *numSummedWeights_pdfDown;
        TH1D *numSummedWeights_muRUp;
        TH1D *numSummedWeights_muRDown;
        TH1D *numSummedWeights_muFUp;
        TH1D *numSummedWeights_muFDown;

        //
        // sums for renormalization
        double nnpdfWeightSumUp;
        double nnpdfWeightSumDown;

        double muRWeightSumUp;
        double muRWeightSumDown;

        double muFWeightSumUp;
        double muFWeightSumDown;
                
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
        
        int numBadMuons_intree;
        int numPVs_intree;
        int numTruePVs_intree;

        vector<ttH::Lepton> raw_leptons_intree;
        vector<ttH::Lepton> loose_leptons_intree;
        vector<ttH::Lepton> preselected_leptons_intree;
        vector<ttH::Lepton> fakeable_leptons_intree;
        vector<ttH::Lepton> tight_leptons_intree;
 
        vector<ttH::Electron> raw_electrons_intree; 
        vector<ttH::Electron> loose_electrons_intree;            
        vector<ttH::Electron> preselected_electrons_intree;
        vector<ttH::Electron> fakeable_electrons_intree;
        vector<ttH::Electron> tight_electrons_intree;

        vector<ttH::Muon> raw_muons_intree;
        vector<ttH::Muon> loose_muons_intree;
        vector<ttH::Muon> preselected_muons_intree;
        vector<ttH::Muon> fakeable_muons_intree;
        vector<ttH::Muon> tight_muons_intree;
        
        vector<ttH::Tau> raw_taus_intree;
        vector<ttH::Tau> preselected_taus_intree;
        vector<ttH::Tau> selected_taus_intree;

        vector<ttH::Jet> raw_jets_intree;
        vector<ttH::Jet> loose_jets_intree;
        vector<ttH::Jet> preselected_jets_intree;
        vector<ttH::Jet> preselected_jets_JECup_intree;
        vector<ttH::Jet> preselected_jets_JECdown_intree;
        vector<ttH::Jet> preselected_jets_uncor_intree;
        vector<ttH::Jet> preselected_jets_noTauClean_intree;
        vector<ttH::Jet> preselected_jets_JECup_noTauClean_intree;
        vector<ttH::Jet> preselected_jets_JECdown_noTauClean_intree;

                        
        vector<ttH::MET> met_intree;
        vector<ttH::GenParticle> pruned_genParticles_intree;
        vector<ttH::GenParticle> packed_genParticles_intree;
        vector<ttH::GenParticle> genJets_intree;
        
        edm::EDGetTokenT<pat::MuonCollection> muons_token_;
        edm::EDGetTokenT<pat::ElectronCollection> electrons_token_;
        edm::EDGetTokenT<pat::TauCollection> taus_token_;

        // pdf and Q^2 weights
        // token and mapping definition
        //	edm::EDGetTokenT<LHEEventProduct> lheEventToken_;
        edm::EDGetTokenT<LHERunInfoProduct> lheRunToken_;
        std::map<int, int> pdfIdMap_; // this is the map we want to fill

        double nnpdfWeightUp_intree;
        double nnpdfWeightDown_intree;

        double muRWeightUp_intree;
        double muRWeightDown_intree;

        double muFWeightUp_intree;
        double muFWeightDown_intree;
        
        edm::EDGetTokenT< double > prefweight_token;
        edm::EDGetTokenT< double > prefweightup_token;
        edm::EDGetTokenT< double > prefweightdown_token;
        
        double prefiringweight_intree;
        double prefiringweightup_intree;
        double prefiringweightdown_intree;
        double preshowerISRweightUp_intree;
        double preshowerFSRweightUp_intree;
        double preshowerISRweightDown_intree;
        double preshowerFSRweightDown_intree;

        
        std::auto_ptr<JetCorrectionUncertainty> junc_;//charlie

        std::unordered_map<std::string,double> eftwgts_intree;
        double originalXWGTUP_intree;

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
    summaryTree->Branch("numPVs", &numPVs_intree);
    summaryTree->Branch("numTruePVs", &numTruePVs_intree);
    summaryTree->Branch("passTrigger", &passTrigger_intree);
  
    summaryTree->Branch("preselected_leptons", &preselected_leptons_intree);
    summaryTree->Branch("preselected_electrons", &preselected_electrons_intree);
    summaryTree->Branch("preselected_muons", &preselected_muons_intree);
    summaryTree->Branch("preselected_taus", &preselected_taus_intree);
    summaryTree->Branch("selected_taus", &selected_taus_intree);

    summaryTree->Branch("fakeable_leptons", &fakeable_leptons_intree);
    summaryTree->Branch("fakeable_electrons", &fakeable_electrons_intree);
    summaryTree->Branch("fakeable_muons", &fakeable_muons_intree);

    //summaryTree->Branch("loose_leptons", &loose_leptons_intree);
    //summaryTree->Branch("loose_electrons", &loose_electrons_intree);
    //summaryTree->Branch("loose_muons", &loose_muons_intree);

    summaryTree->Branch("tight_leptons", &tight_leptons_intree);
    summaryTree->Branch("tight_electrons", &tight_electrons_intree);
    summaryTree->Branch("tight_muons", &tight_muons_intree);

    //summaryTree->Branch("loose_jets", &loose_jets_intree);

    summaryTree->Branch("raw_electrons", &raw_electrons_intree);
    summaryTree->Branch("raw_muons", &raw_muons_intree);
    //summaryTree->Branch("raw_leptons", &raw_leptons_intree);
    //summaryTree->Branch("raw_taus", &raw_taus_intree);
    summaryTree->Branch("raw_jets", &raw_jets_intree);

    summaryTree->Branch("preselected_jets", &preselected_jets_intree);
    summaryTree->Branch("preselected_jets_JECup", &preselected_jets_JECup_intree);
    summaryTree->Branch("preselected_jets_JECdown", &preselected_jets_JECdown_intree);
    summaryTree->Branch("preselected_jets_noTauClean", &preselected_jets_noTauClean_intree);
    summaryTree->Branch("preselected_jets_JECup_noTauClean", &preselected_jets_JECup_noTauClean_intree);
    summaryTree->Branch("preselected_jets_JECdown_noTauClean", &preselected_jets_JECdown_noTauClean_intree);    
    //summaryTree->Branch("preselected_jets_uncor", &preselected_jets_uncor_intree);

    summaryTree->Branch("met", &met_intree);
    summaryTree->Branch("pruned_genParticles", &pruned_genParticles_intree);
    //summaryTree->Branch("packed_genParticles", &packed_genParticles_intree);
    summaryTree->Branch("genJets", &genJets_intree);
    //summaryTree->Branch("numBadMuons", &numBadMuons_intree);

    summaryTree->Branch("eftwgts",&eftwgts_intree);
    summaryTree->Branch("originalXWGTUP",&originalXWGTUP_intree);

    summaryTree->Branch("nnpdfWeightUp",&nnpdfWeightUp_intree);
    summaryTree->Branch("nnpdfWeightDown",&nnpdfWeightDown_intree);

    summaryTree->Branch("muRWeightUp",&muRWeightUp_intree);
    summaryTree->Branch("muRWeightDown",&muRWeightDown_intree);

    summaryTree->Branch("muFWeightUp",&muFWeightUp_intree);
    summaryTree->Branch("muFWeightDown",&muFWeightDown_intree);

    summaryTree->Branch("prefiringweight",&prefiringweight_intree);
    summaryTree->Branch("prefiringweightup",&prefiringweightup_intree);
    summaryTree->Branch("prefiringweightdown",&prefiringweightdown_intree);

    summaryTree->Branch("preshowerISRweightUp",&preshowerISRweightUp_intree);
    summaryTree->Branch("preshowerFSRweightUp",&preshowerFSRweightUp_intree);
    summaryTree->Branch("preshowerISRweightDown",&preshowerISRweightDown_intree);
    summaryTree->Branch("preshowerFSRweightDown",&preshowerFSRweightDown_intree);


}

void OSTwoLepAna::initialize_variables()
{
    mcwgt_intree = 1.;
    wgt_intree = 1.;
    wallTimePerEvent_intree = -9999.;
  
    eventnum_intree = -99;
    lumiBlock_intree = -99;
    runNumber_intree = -99;
    numBadMuons_intree = -99;
    numPVs_intree = -99;
    numTruePVs_intree = -99;
    //passTrigger_intree = false;
    passTrigger_intree.clear();
    preselected_leptons_intree.clear();
    preselected_electrons_intree.clear();
    preselected_muons_intree.clear();
    preselected_taus_intree.clear();
    selected_taus_intree.clear();
  
    fakeable_leptons_intree.clear();
    fakeable_electrons_intree.clear();
    fakeable_muons_intree.clear();
  
    tight_leptons_intree.clear();
    tight_electrons_intree.clear();
    tight_muons_intree.clear();
  
    raw_leptons_intree.clear();
    raw_electrons_intree.clear();
    raw_muons_intree.clear();
    raw_taus_intree.clear();
    raw_jets_intree.clear();
  
    preselected_jets_intree.clear();
    preselected_jets_JECup_intree.clear();
    preselected_jets_JECdown_intree.clear();
    preselected_jets_uncor_intree.clear();
    
    preselected_jets_noTauClean_intree.clear();
    preselected_jets_JECup_noTauClean_intree.clear();
    preselected_jets_JECdown_noTauClean_intree.clear();    
    
    met_intree.clear();
    pruned_genParticles_intree.clear();
    packed_genParticles_intree.clear();
    genJets_intree.clear();
  
    higgs_decay_intree = 0;
    higgs_final_state = "none";
    top_final_state = "none";

    eftwgts_intree.clear();
    originalXWGTUP_intree = -99;

    // pdf and Q^2 weights
    nnpdfWeightUp_intree = 1.;
    nnpdfWeightDown_intree = 1.;

    muRWeightUp_intree = 1.;
    muRWeightDown_intree = 1.;

    muFWeightUp_intree = 1.;
    muFWeightDown_intree = 1.;
    
    prefiringweight_intree = 1.;
    prefiringweightup_intree = 1.;
    prefiringweightdown_intree = 1.;
    
    preshowerISRweightUp_intree = 1.;
    preshowerFSRweightUp_intree = 1.;
    preshowerISRweightDown_intree = 1.;
    preshowerFSRweightDown_intree = 1.;


}
