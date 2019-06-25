void HistMaker::setBranchAddresses( TTreeReader & newreader )
{
    // all the branches are aliased to member variables of HistMaker
    
    //cout << "Getting tree branches..." << endl;
    
    wgt_intree = TTreeReaderValue<double>(newreader, "wgt");       
    passTrigger_intree = TTreeReaderValue<vector<string>>(newreader, "passTrigger");
    numPVs_intree = TTreeReaderValue<int>(newreader, "numPVs");
    numTruePVs_intree = TTreeReaderValue<int>(newreader, "numTruePVs");
    higgsdecay_intree = TTreeReaderValue<int>(newreader, "higgs_decay");
    
    eftwgts_intree = TTreeReaderValue<std::unordered_map<std::string,double>>(newreader, "eftwgts");
    originalXWGTUP_intree = TTreeReaderValue<double>(newreader, "originalXWGTUP");
    
    if (sample<100)
    {
        nnpdfWeightUp_intree = TTreeReaderValue<double>(newreader, "nnpdfWeightUp");
        nnpdfWeightDown_intree = TTreeReaderValue<double>(newreader, "nnpdfWeightDown");
        muRWeightUp_intree = TTreeReaderValue<double>(newreader, "muRWeightUp");
        muRWeightDown_intree = TTreeReaderValue<double>(newreader, "muRWeightDown");
        muFWeightUp_intree = TTreeReaderValue<double>(newreader, "muFWeightUp");
        muFWeightDown_intree = TTreeReaderValue<double>(newreader, "muFWeightDown");
        
        prefiringweight_intree = TTreeReaderValue<double>(newreader, "prefiringweight");        
        prefiringweightup_intree = TTreeReaderValue<double>(newreader, "prefiringweightup");        
        prefiringweightdown_intree = TTreeReaderValue<double>(newreader, "prefiringweightdown");        
        preshowerISRweightUp_intree = TTreeReaderValue<double>(newreader, "preshowerISRweightUp");        
        preshowerFSRweightUp_intree = TTreeReaderValue<double>(newreader, "preshowerFSRweightUp");        
        preshowerISRweightDown_intree = TTreeReaderValue<double>(newreader, "preshowerISRweightDown");
        preshowerFSRweightDown_intree = TTreeReaderValue<double>(newreader, "preshowerFSRweightDown");
        
        
//        cout << "switch back (insdie setbranchaddresses!)" << endl;
//         prefiringweight_intree = TTreeReaderValue<double>(newreader, "originalXWGTUP");        
//         prefiringweightup_intree = TTreeReaderValue<double>(newreader, "originalXWGTUP");        
//         prefiringweightdown_intree = TTreeReaderValue<double>(newreader, "originalXWGTUP");        
//         preshowerISRweightUp_intree = TTreeReaderValue<double>(newreader, "originalXWGTUP");        
//         preshowerFSRweightUp_intree = TTreeReaderValue<double>(newreader, "originalXWGTUP");        
//         preshowerISRweightDown_intree = TTreeReaderValue<double>(newreader, "originalXWGTUP");
//         preshowerFSRweightDown_intree = TTreeReaderValue<double>(newreader, "originalXWGTUP");  
    }
    else
    {
        // is this really needed?
        nnpdfWeightUp_intree = TTreeReaderValue<double>(newreader, "originalXWGTUP");
        nnpdfWeightDown_intree = TTreeReaderValue<double>(newreader, "originalXWGTUP");
        muRWeightUp_intree = TTreeReaderValue<double>(newreader, "originalXWGTUP");
        muRWeightDown_intree = TTreeReaderValue<double>(newreader, "originalXWGTUP");
        muFWeightUp_intree = TTreeReaderValue<double>(newreader, "originalXWGTUP");
        muFWeightDown_intree = TTreeReaderValue<double>(newreader, "originalXWGTUP");
    }    

    
    raw_electrons_intree = TTreeReaderValue<vector<ttH::Electron>>(newreader, "raw_electrons");    
    //raw_leptons_intree = TTreeReaderValue<vector<ttH::Lepton>>(newreader, "raw_leptons");
    raw_muons_intree = TTreeReaderValue<vector<ttH::Muon>>(newreader, "raw_muons");    
    
    fakeable_electrons_intree = TTreeReaderValue<vector<ttH::Electron>>(newreader, "fakeable_electrons");
    fakeable_leptons_intree = TTreeReaderValue<vector<ttH::Lepton>>(newreader, "fakeable_leptons");
    fakeable_muons_intree = TTreeReaderValue<vector<ttH::Muon>>(newreader, "fakeable_muons");    
    
    preselected_electrons_intree = TTreeReaderValue<vector<ttH::Electron>>(newreader, "preselected_electrons");    
    preselected_leptons_intree = TTreeReaderValue<vector<ttH::Lepton>>(newreader, "preselected_leptons");
    preselected_muons_intree = TTreeReaderValue<vector<ttH::Muon>>(newreader, "preselected_muons");    
    
    tight_electrons_intree = TTreeReaderValue<vector<ttH::Electron>>(newreader, "tight_electrons");    
    tight_leptons_intree = TTreeReaderValue<vector<ttH::Lepton>>(newreader, "tight_leptons");
    tight_muons_intree = TTreeReaderValue<vector<ttH::Muon>>(newreader, "tight_muons");
    
    //tight_electrons_intree = TTreeReaderValue<vector<ttH::Electron>>(newreader, "preselected_electrons");    
    //tight_leptons_intree = TTreeReaderValue<vector<ttH::Lepton>>(newreader, "preselected_leptons");
    //tight_muons_intree = TTreeReaderValue<vector<ttH::Muon>>(newreader, "preselected_muons");     
    
    selected_taus_intree = TTreeReaderValue<vector<ttH::Tau>>(newreader, "selected_taus");
    
    raw_jets_intree = TTreeReaderValue<vector<ttH::Jet>>(newreader, "raw_jets");
    //loose_jets_intree = TTreeReaderValue<vector<ttH::Jet>>(newreader, "loose_jets");
//     preselected_jets_intree = TTreeReaderValue<vector<ttH::Jet>>(newreader, "preselected_jets");
//     preselected_jets_JECup_intree = TTreeReaderValue<vector<ttH::Jet>>(newreader, "preselected_jets_JECup");
//     preselected_jets_JECdown_intree = TTreeReaderValue<vector<ttH::Jet>>(newreader, "preselected_jets_JECdown");
    preselected_jets_intree = TTreeReaderValue<vector<ttH::Jet>>(newreader, "preselected_jets_noTauClean");
    preselected_jets_JECup_intree = TTreeReaderValue<vector<ttH::Jet>>(newreader, "preselected_jets_JECup_noTauClean");
    preselected_jets_JECdown_intree = TTreeReaderValue<vector<ttH::Jet>>(newreader, "preselected_jets_JECdown_noTauClean");    
     
    met_intree = TTreeReaderValue<vector<ttH::MET>>(newreader, "met");
    
    pruned_genParticles_intree = TTreeReaderValue<vector<ttH::GenParticle>>(newreader, "pruned_genParticles");
    genJets_intree = TTreeReaderValue<vector<ttH::GenParticle>>(newreader, "genJets");

    
}
