void HistMaker::setBranchAddresses( TTreeReader & newreader )
{
    // all the branches are aliased to member variables of HistMaker
    
    //cout << "Getting tree branches..." << endl;
    
    wgt_intree = TTreeReaderValue<double>(newreader, "wgt");       
    passTrigger_intree = TTreeReaderValue<vector<string>>(newreader, "passTrigger");
    numPVs_intree = TTreeReaderValue<int>(newreader, "numPVs");
    
    raw_electrons_intree = TTreeReaderValue<vector<ttH::Electron>>(newreader, "raw_electrons");    
    //raw_leptons_intree = TTreeReaderValue<vector<ttH::Lepton>>(newreader, "raw_leptons");
    raw_muons_intree = TTreeReaderValue<vector<ttH::Muon>>(newreader, "raw_muons");    
    
    preselected_electrons_intree = TTreeReaderValue<vector<ttH::Electron>>(newreader, "preselected_electrons");    
    preselected_leptons_intree = TTreeReaderValue<vector<ttH::Lepton>>(newreader, "preselected_leptons");
    preselected_muons_intree = TTreeReaderValue<vector<ttH::Muon>>(newreader, "preselected_muons");    
    
    tight_electrons_intree = TTreeReaderValue<vector<ttH::Electron>>(newreader, "tight_electrons");    
    tight_leptons_intree = TTreeReaderValue<vector<ttH::Lepton>>(newreader, "tight_leptons");
    tight_muons_intree = TTreeReaderValue<vector<ttH::Muon>>(newreader, "tight_muons");
    
    raw_jets_intree = TTreeReaderValue<vector<ttH::Jet>>(newreader, "raw_jets");
    //loose_jets_intree = TTreeReaderValue<vector<ttH::Jet>>(newreader, "loose_jets");
    preselected_jets_intree = TTreeReaderValue<vector<ttH::Jet>>(newreader, "preselected_jets");
    
     
    met_intree = TTreeReaderValue<vector<ttH::MET>>(newreader, "met");
    
    pruned_genParticles_intree = TTreeReaderValue<vector<ttH::GenParticle>>(newreader, "pruned_genParticles");

    // and the rest ....

    
}
