void HistMaker::setBranchAddresses( TTreeReader & newreader )
{
    // all the branches are aliased to member variables of HistMaker
    
    //cout << "Getting tree branches..." << endl;
    
    wgt_intree = TTreeReaderValue<double>(newreader, "wgt");       
    
    
    raw_electrons_intree = TTreeReaderValue<vector<ttH::Electron>>(newreader, "raw_electrons");    
    raw_leptons_intree = TTreeReaderValue<vector<ttH::Lepton>>(newreader, "raw_leptons");
    raw_muons_intree = TTreeReaderValue<vector<ttH::Muon>>(newreader, "raw_muons");
    raw_jets_intree = TTreeReaderValue<vector<ttH::Jet>>(newreader, "raw_jets");
    
    loose_jets_intree = TTreeReaderValue<vector<ttH::Jet>>(newreader, "loose_jets");
    
    tight_electrons_intree = TTreeReaderValue<vector<ttH::Electron>>(newreader, "tight_electrons");    
    tight_leptons_intree = TTreeReaderValue<vector<ttH::Lepton>>(newreader, "tight_leptons");
    tight_muons_intree = TTreeReaderValue<vector<ttH::Muon>>(newreader, "tight_muons");    
    
     
    met_intree = TTreeReaderValue<vector<ttH::MET>>(newreader, "met");
    //preselected_jets_intree = TTreeReaderValue<vector<ttH::Jet>>(newreader, "preselected_jets");
    pruned_genParticles_intree = TTreeReaderValue<vector<ttH::GenParticle>>(newreader, "pruned_genParticles");

    // and the rest ....

    
}
