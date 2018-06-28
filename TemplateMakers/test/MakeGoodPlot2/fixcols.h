void HistMaker::fixcollections()
{
    // any global cleaning or re-ID of objects that will be used everywhere downstream

    fakeable_leptons.clear();
    tight_leptons.clear();
    fakeable_electrons.clear();
    tight_electrons.clear();
    fakeable_muons.clear();
    tight_muons.clear();
    preselected_jets.clear();
    preselected_jets_JECup.clear();
    preselected_jets_JECdown.clear();
    
    for (const auto muon : *preselected_muons_intree)
    {
        if (mu_fakeable(muon)) 
        {
            //ttH::Muon newmu = muon;
            //ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > blah(newmu.correctedPt,,,);
        
            //cpt = newmu.correctedPt;
            
            //if (!mu_tight(muon)) newmu.obj = blah; // newmu.obj.SetPt(cpt);
            
            //fakeable_muons.push_back(newmu);
            //fakeable_leptons.push_back(muon);
            fakeable_muons.push_back(muon);
        }
        else break; // I *think* this is what we want..
    }
    for (const auto muon : *preselected_muons_intree)
    {   
        if (mu_tight(muon))
        {
            tight_muons.push_back(muon);
            //tight_leptons.push_back(muon);
        }
        else break;
    }
    for (const auto electron : *preselected_electrons_intree)
    {
        if (ele_fakeable(electron)) 
        {
            //ttH::Electron newele = electron;
            //if (!ele_tight(electron)) newele.obj.SetPt(newele.correctedPt);            
            //fakeable_electrons.push_back(newele);
            //fakeable_leptons.push_back(electron);
            fakeable_electrons.push_back(electron);
        }
        else break;
    }
    for (const auto electron : *preselected_electrons_intree)
    {        
        if (ele_tight(electron))
        {
            tight_electrons.push_back(electron);
            //tight_leptons.push_back(electron);
        }
        else break;
    }        
    
    // have to do it this way for combinitoric reasons
    for (const auto lepton : *preselected_leptons_intree)
    {
        if (abs(lepton.pdgID)==11)
        {
            bool foundmatch = false;
            ttH::Lepton matchedlep;
            for (const auto electron : tight_electrons)
            {
                if (lepton.obj==electron.obj)
                {
                    foundmatch=true;
                    matchedlep=electron;
                    break;
                }
            }
            if (!foundmatch) break;
            else tight_leptons.push_back(matchedlep);
        }
        if (abs(lepton.pdgID)==13)
        {
            bool foundmatch = false;
            ttH::Lepton matchedlep;
            for (const auto muon : tight_muons)
            {
                if (lepton.obj==muon.obj)
                {
                    foundmatch=true;
                    matchedlep=muon;
                    break;
                }
            }
            if (!foundmatch) break;
            else tight_leptons.push_back(matchedlep);
        }            
    }
    for (const auto lepton : *preselected_leptons_intree)
    {
        if (abs(lepton.pdgID)==11)
        {
            bool foundmatch = false;
            ttH::Lepton matchedlep;
            for (const auto electron : fakeable_electrons)
            {
                if (lepton.obj==electron.obj)
                {
                    foundmatch=true;
                    matchedlep=electron;
                    break;
                }
            }
            if (!foundmatch) break;
            else fakeable_leptons.push_back(matchedlep);
        }
        if (abs(lepton.pdgID)==13)
        {
            bool foundmatch = false;
            ttH::Lepton matchedlep;
            for (const auto muon : fakeable_muons)
            {
                if (lepton.obj==muon.obj)
                {
                    foundmatch=true;
                    matchedlep=muon;
                    break;
                }
            }
            if (!foundmatch) break;
            else fakeable_leptons.push_back(matchedlep);
        }            
    }     
        
        
        
    // now, shouldn't need this..
    //fakeable_leptons = sortParticles(fakeable_leptons);
    //tight_leptons = sortParticles(tight_leptons);
        
        
    preselected_jets = simpleJetCut(*preselected_jets_intree,"pt",30.0);
    preselected_jets_JECup = simpleJetCut(*preselected_jets_JECup_intree,"pt",30.0);
    preselected_jets_JECdown = simpleJetCut(*preselected_jets_JECup_intree,"pt",30.0);  
    
}