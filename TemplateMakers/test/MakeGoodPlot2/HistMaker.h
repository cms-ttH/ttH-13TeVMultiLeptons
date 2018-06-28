// HistMaker histogram-making class
// Created by Geoff Smith, 2017

class HistMaker
{
    // don't inherit anything
    public:
        // everything is public
        
        HistMaker();
        HistMaker(TString thepassedsamp, bool cfs=false, bool fks=false);
        
        // member variables
        const unsigned int th1arrsize = 2000;
        const unsigned int th2arrsize = 500;
        const unsigned int th1eftarrsize = 250;
        int sample = -1;
        
        TH1D *th1ds[2000]; 
        TH2D *th2ds[500];
        TH1EFT *th1efts[250];
        std::unordered_map<string,TH1D*> th1d;
        std::unordered_map<string,TH2D*> th2d;
        std::unordered_map<string,TH1EFT*> th1eft;
        std::unordered_map<string,TGraph*> tgraph;

        TObjArray *objArray;
        
        TTreeReaderValue<double> wgt_intree;
        TTreeReaderValue<vector<string>> passTrigger_intree;
        TTreeReaderValue<int> numPVs_intree;
        TTreeReaderValue<int> numTruePVs_intree;
        TTreeReaderValue<int> higgsdecay_intree;
        TTreeReaderValue<std::unordered_map<std::string,double>> eftwgts_intree;
        TTreeReaderValue<double> originalXWGTUP_intree;
        TTreeReaderValue<vector<ttH::Lepton>> raw_leptons_intree;
        TTreeReaderValue<vector<ttH::Lepton>> preselected_leptons_intree;
        TTreeReaderValue<vector<ttH::Lepton>> loose_leptons_intree;
        TTreeReaderValue<vector<ttH::Lepton>> fakeable_leptons_intree;
        TTreeReaderValue<vector<ttH::Lepton>> cutBased_leptons_intree;
        TTreeReaderValue<vector<ttH::Lepton>> looseMvaBased_leptons_intree;
        TTreeReaderValue<vector<ttH::Lepton>> tightMvaBased_leptons_intree;
        TTreeReaderValue<vector<ttH::Lepton>> tight_leptons_intree;
        
        TTreeReaderValue<vector<ttH::Electron>> raw_electrons_intree;      
        TTreeReaderValue<vector<ttH::Electron>> preselected_electrons_intree;
        TTreeReaderValue<vector<ttH::Electron>> loose_electrons_intree;
        TTreeReaderValue<vector<ttH::Electron>> fakeable_electrons_intree;
        TTreeReaderValue<vector<ttH::Electron>> cutBased_electrons_intree;
        TTreeReaderValue<vector<ttH::Electron>> looseMvaBased_electrons_intree;
        TTreeReaderValue<vector<ttH::Electron>> tightMvaBased_electrons_intree;
        TTreeReaderValue<vector<ttH::Electron>> tight_electrons_intree;

        TTreeReaderValue<vector<ttH::Muon>> raw_muons_intree;
        TTreeReaderValue<vector<ttH::Muon>> preselected_muons_intree;
        TTreeReaderValue<vector<ttH::Muon>> loose_muons_intree;
        TTreeReaderValue<vector<ttH::Muon>> fakeable_muons_intree;
        TTreeReaderValue<vector<ttH::Muon>> cutBased_muons_intree;
        TTreeReaderValue<vector<ttH::Muon>> looseMvaBased_muons_intree;
        TTreeReaderValue<vector<ttH::Muon>> tightMvaBased_muons_intree;
        TTreeReaderValue<vector<ttH::Muon>> tight_muons_intree;

        TTreeReaderValue<vector<ttH::Jet>> raw_jets_intree;
        TTreeReaderValue<vector<ttH::Jet>> loose_jets_intree;
        TTreeReaderValue<vector<ttH::Jet>> preselected_jets_intree;
        TTreeReaderValue<vector<ttH::Jet>> preselected_jets_JECup_intree;
        TTreeReaderValue<vector<ttH::Jet>> preselected_jets_JECdown_intree;
        TTreeReaderValue<vector<ttH::Jet>> loose_bJets_intree;
        TTreeReaderValue<vector<ttH::Jet>> tight_bJets_intree;

        TTreeReaderValue<vector<ttH::MET>> met_intree;

        TTreeReaderValue<vector<ttH::GenParticle>> pruned_genParticles_intree;
        TTreeReaderValue<vector<ttH::GenParticle>> genJets_intree;
        
        
        vector<ttH::Lepton> fakeable_leptons;
        vector<ttH::Lepton> tight_leptons;
        vector<ttH::Electron> fakeable_electrons;
        vector<ttH::Electron> tight_electrons;
        vector<ttH::Muon> fakeable_muons;
        vector<ttH::Muon> tight_muons;
        vector<ttH::Jet> preselected_jets;
        vector<ttH::Jet> preselected_jets_JECup;
        vector<ttH::Jet> preselected_jets_JECdown;        
        
        // sf hists
        TH1D *pileupSFs;
        TH2F *muh4_2l;
        TH2F *muh4_3l; 
        TH2F *eleh4_2l;
        TH2F *eleh4_3l;
        TGraphAsymmErrors *muh1;
        TH2D *muh2;
        TH2F *eleh1;
        TH2F *eleh1lowpt;
        
        // data-driven bkgd hists
        TH2D *elQFsfs;
        TH2D *elFRsfs;
        TH2D *muFRsfs;
        
        // technical functions needed to run HistMaker
        void bookHistos();
        void setBranchAddresses(TTreeReader & newreader); //TTreeReader & newreader
        void run(TTreeReader & newreader);
        void doOneEvent();
        void collectResults();
        
        // analysis supporting functions
        void fixcollections();
        string eventselection(std::vector<ttH::Jet> thejets, bool useFakeable=false);
        vector<string> eventselections(bool useFakeable=false);
        //void get_rate_info(int samp);
        bool removeDatasetOverlaps();
        bool passesDatasetDependentTriggers(int mysample);
        bool passesAnyTrigger();
        double pileupSF(int numtrueint=0);
        void setupSFs();
        double muonSF(double mu_pt, double mu_eta, int lepmult);
        double electronSF(double ele_pt, double ele_eta, int lepmult);
        double totalSF(int iSys, vector<string> category);
        double getFakeWeight(int iSys, vector<string> category);
        std::pair<double,double> getQFweights(string category);
        
        bool dochgfs = false;
        bool dofakes = false;
    
        bool ele_tight(ttH::Electron ele);
        bool mu_tight(ttH::Muon mu);
        bool lep_tight(ttH::Lepton lep);
        bool ele_fakeable(ttH::Electron ele);
        bool mu_fakeable(ttH::Muon mu);        

        //add'l trigger studies stuff
        bool passes_common();     
        bool passes_2lss();   
        bool passes_geq3l();
        bool passes_SSee();
        bool passes_SSmumu();
        bool passes_SSemu();
        bool passes_3l();
        bool passes_4l();
        bool passes_2l2b2qtest();
        bool passes_mu2tau();
        bool passes_ele2tau();
        void trigger_studies();

        // regular analysis hist-filling functions
        void proof_of_concept();
        void lepton_eff_studies();
        void get_hist_of_simple_variable_2D();
        void jet_cleaning_studies();
        void standard_hists();
        void mc_validation_hists();
        void incl_hists();
        
};

HistMaker::HistMaker()
{
    TH1::SetDefaultSumw2();  
    
    // Default method, when running with multiple cores
    // Getting the sample number this way due to limitations of TTreeProcessorMP   
    ifstream passedSample;
    passedSample.open("current_samp.txt");
    passedSample >> sample;
    passedSample.close();
    
    // doing it this way instead when using condor/batch (not lobster):
//     auto samp_env_var = getenv("SAMPLE");
//     string samp_env_var_string = samp_env_var;
//     stringstream samp_env_var_ss(samp_env_var_string);
//     samp_env_var_ss >> sample;
    
}
HistMaker::HistMaker(TString thepassedsamp, bool cfs, bool fks)
{
    if (cfs==true && fks==true)
    {
        cout << "You can't run both the charge-flip and fake background estimation at the same time! Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
    dochgfs=cfs;
    dofakes=fks;
    
    
    // Use this when running lobster
    // Alternative constructor (if you have direct access to the sample number, i.e. 
    // when running from wrapper_lobster.C)
    
    TH1::SetDefaultSumw2(); 
    sample = sample_TString2int(thepassedsamp); // see loadsample.h
    setupSFs();
}

