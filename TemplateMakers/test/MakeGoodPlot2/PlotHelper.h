class PlotHelper
{
    // don't inherit anything
    // don't even bother defining const./destr.
        
    public:
        
        PlotHelper() { TH1::SetDefaultSumw2(); }
        
        const unsigned int arrsize = 500;
        
        // you DO need these here!
        TH1D *th1ds[500]; 
        TH2D *th2ds[500];
        std::unordered_map<string,TH1D*> th1d;
        std::unordered_map<string,TH2D*> th2d;
        std::unordered_map<string,TGraph*> tgraph;

        TObjArray *objArray;
        
        TTreeReaderValue<double> wgt_intree;
        
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
        
        //PlotHelper(TTreeReader & newreader);

        void proof_of_concept();
        void lepton_eff_studies();
        void get_hist_of_simple_variable_2D();
        void jet_cleaning_studies();
        void standard_hists();
        
        bool ele_tight(ttH::Electron ele);
        bool mu_tight(ttH::Muon mu);
};
