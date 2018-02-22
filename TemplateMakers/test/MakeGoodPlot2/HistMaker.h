// HistMaker histogram-making class
// Created by Geoff Smith, 2017

class HistMaker
{
    // don't inherit anything
    public:
        // everything is public
        
        HistMaker();
        HistMaker(TString thepassedsamp);
        
        const unsigned int th1arrsize = 5000;
        const unsigned int th2arrsize = 1000;
        int sample = -1;
        
        // you DO need these here!
        TH1D *th1ds[5000]; 
        TH2D *th2ds[1000];
        std::unordered_map<string,TH1D*> th1d;
        std::unordered_map<string,TH2D*> th2d;
        std::unordered_map<string,TGraph*> tgraph;

        TObjArray *objArray;
        
        TTreeReaderValue<double> wgt_intree;
        TTreeReaderValue<vector<string>> passTrigger_intree;
        TTreeReaderValue<int> numPVs_intree;
        
        TTreeReaderValue<vector<ttH::Lepton>> raw_leptons_intree;
        TTreeReaderValue<vector<ttH::Lepton>> preselected_leptons_intree;
        TTreeReaderValue<vector<ttH::Lepton>> loose_leptons_intree;
        TTreeReaderValue<vector<ttH::Lepton>> cutBased_leptons_intree;
        TTreeReaderValue<vector<ttH::Lepton>> looseMvaBased_leptons_intree;
        TTreeReaderValue<vector<ttH::Lepton>> tightMvaBased_leptons_intree;
        TTreeReaderValue<vector<ttH::Lepton>> tight_leptons_intree;
        
        TTreeReaderValue<vector<ttH::Electron>> raw_electrons_intree;      
        TTreeReaderValue<vector<ttH::Electron>> preselected_electrons_intree;
        TTreeReaderValue<vector<ttH::Electron>> loose_electrons_intree;
        TTreeReaderValue<vector<ttH::Electron>> cutBased_electrons_intree;
        TTreeReaderValue<vector<ttH::Electron>> looseMvaBased_electrons_intree;
        TTreeReaderValue<vector<ttH::Electron>> tightMvaBased_electrons_intree;
        TTreeReaderValue<vector<ttH::Electron>> tight_electrons_intree;

        TTreeReaderValue<vector<ttH::Muon>> raw_muons_intree;
        TTreeReaderValue<vector<ttH::Muon>> preselected_muons_intree;
        TTreeReaderValue<vector<ttH::Muon>> loose_muons_intree;
        TTreeReaderValue<vector<ttH::Muon>> cutBased_muons_intree;
        TTreeReaderValue<vector<ttH::Muon>> looseMvaBased_muons_intree;
        TTreeReaderValue<vector<ttH::Muon>> tightMvaBased_muons_intree;
        TTreeReaderValue<vector<ttH::Muon>> tight_muons_intree;

        TTreeReaderValue<vector<ttH::Jet>> raw_jets_intree;
        TTreeReaderValue<vector<ttH::Jet>> loose_jets_intree;
        TTreeReaderValue<vector<ttH::Jet>> preselected_jets_intree;
        TTreeReaderValue<vector<ttH::Jet>> loose_bJets_intree;
        TTreeReaderValue<vector<ttH::Jet>> tight_bJets_intree;

        TTreeReaderValue<vector<ttH::MET>> met_intree;

        TTreeReaderValue<vector<ttH::GenParticle>> pruned_genParticles_intree;


        void bookHistos();
        void setBranchAddresses(TTreeReader & newreader); //TTreeReader & newreader
        void run(TTreeReader & newreader);
        void doOneEvent();
        void collectResults();
        string eventselection();
        //void get_rate_info(int samp);
        bool removeDatasetOverlaps();
        bool passesDatasetDependentTriggers(int mysample);
        bool passesAnyTrigger();
        
        //HistMaker(TTreeReader & newreader);

        void proof_of_concept();
        void lepton_eff_studies();
        void get_hist_of_simple_variable_2D();
        void jet_cleaning_studies();
        void standard_hists();
        
        bool ele_tight(ttH::Electron ele);
        bool mu_tight(ttH::Muon mu);
};

HistMaker::HistMaker()
{
    TH1::SetDefaultSumw2();  
    
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
HistMaker::HistMaker(TString thepassedsamp)
{
    // Use this when running lobster
    // Alternative constructor (if you have direct access to the sample number, i.e. 
    // when running from wrapper_lobster.C)
    
    TH1::SetDefaultSumw2(); 
    sample = sample_TString2int(thepassedsamp); // see loadsample.h
}

