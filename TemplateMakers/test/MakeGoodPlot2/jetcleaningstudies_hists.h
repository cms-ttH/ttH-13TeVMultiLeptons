void HistMaker::jet_cleaning_studies()
{
    double weight = *wgt_intree;
    
    //int num_mus = raw_muons_intree->size();
    //int num_eles = raw_electrons_intree->size();
    //int num_jets = raw_jets_intree->size();
    
    double testcone = 0.4;
    
    //for (const auto & ele : *raw_electrons_intree)
    for (const auto & ele : *tight_electrons_intree)
    {
        //if (ele.obj.Pt()>40.)        
        {            
            int bins = 50;
            double interval = 2./bins;            
            
            for (int i=0; i<bins; i++)
            {
                double max_dR = interval*i;
                int jetcount = 0;
                
                for (const auto & jet : *raw_jets_intree)
                {
                    if (getdR(ele,jet)<=max_dR) jetcount++;
                }
            
                th2d["electron_numjets_vs_dR"]->Fill(max_dR+(0.1*interval),jetcount,weight);
                if (ele.isPromptFinalState || ele.isDirectPromptTauDecayProductFinalState) 
                {
                    th2d["electron_numjets_vs_dR_prompt"]->Fill(max_dR+(0.1*interval),jetcount,weight);
                }
                else th2d["electron_numjets_vs_dR_nonprompt"]->Fill(max_dR+(0.1*interval),jetcount,weight);
            }
            
            interval = 0.2/bins;             
            
            for (int i=0; i<bins; i++)
            {
                double max_dR = interval*i;
                int jetcount = 0;
                
                for (const auto & jet : *raw_jets_intree)
                {
                    if (getdR(ele,jet)<=max_dR) jetcount++;
                }
            
                th2d["electron_numjets_vs_dR_zoomin"]->Fill(max_dR+(0.1*interval),jetcount,weight);
                if (ele.isPromptFinalState || ele.isDirectPromptTauDecayProductFinalState) 
                {
                    th2d["electron_numjets_vs_dR_prompt_zoomin"]->Fill(max_dR+(0.1*interval),jetcount,weight);
                }
                else th2d["electron_numjets_vs_dR_nonprompt_zoomin"]->Fill(max_dR+(0.1*interval),jetcount,weight);                
            }
            
            
            
            for (const auto & jet : *raw_jets_intree)
            {
                if (getdR(ele,jet)<=testcone)
                {
                    TLorentzVector eleTLV = makeRealTLV(ele.obj);
                    TLorentzVector jetTLV = makeRealTLV(jet.obj);
                    auto vectdiff = jetTLV - eleTLV;
                    if (ele.isPromptFinalState || ele.isDirectPromptTauDecayProductFinalState) 
                    {                                                                    
                        th1d["jet_pt_minus_electron_pt_one_jet_in_dR0p4_prompt"]->Fill(vectdiff.Pt(),weight); // was jet.obj.Pt()-ele.obj.Pt(), or vectdiff.Pt(), or eleTLV.Perp(vectdiff.Vect())
                        th2d["jet_pt_minus_electron_pt_one_jet_in_dR0p4_prompt_vs_lep_pt"]->Fill(ele.obj.Pt(),vectdiff.Pt(),weight);
                        
                    }
                    else
                    {
                        th1d["jet_pt_minus_electron_pt_one_jet_in_dR0p4_nonprompt"]->Fill(vectdiff.Pt(),weight);
                        th2d["jet_pt_minus_electron_pt_one_jet_in_dR0p4_nonprompt_vs_lep_pt"]->Fill(ele.obj.Pt(),vectdiff.Pt(),weight);
                        
                    }
                }
            }           
            
        }
            
    }
    //for (const auto & mu : *raw_muons_intree)
    for (const auto & mu : *tight_muons_intree)
    {    
        //if (mu.obj.Pt()>40.)
        {            
            int bins = 50;
            double interval = 2./bins;
            
            for (int i=0; i<bins; i++)
            {
                double max_dR = interval*i;
                int jetcount = 0;
                
                for (const auto & jet : *raw_jets_intree)
                {
                    if (getdR(mu,jet)<=max_dR) jetcount++;
                }
            
                th2d["muon_numjets_vs_dR"]->Fill(max_dR+(0.1*interval),jetcount,weight);
                if (mu.isPromptFinalState || mu.isDirectPromptTauDecayProductFinalState) 
                {
                    th2d["muon_numjets_vs_dR_prompt"]->Fill(max_dR+(0.1*interval),jetcount,weight);
                }
                else th2d["muon_numjets_vs_dR_nonprompt"]->Fill(max_dR+(0.1*interval),jetcount,weight);
            }
            
            interval = 0.2/bins;
            
            for (int i=0; i<bins; i++)
            {
                double max_dR = interval*i;
                int jetcount = 0;
                
                for (const auto & jet : *raw_jets_intree)
                {
                    if (getdR(mu,jet)<=max_dR) jetcount++;
                }
            
                th2d["muon_numjets_vs_dR_zoomin"]->Fill(max_dR+(0.1*interval),jetcount,weight);
                if (mu.isPromptFinalState || mu.isDirectPromptTauDecayProductFinalState) 
                {
                    th2d["muon_numjets_vs_dR_prompt_zoomin"]->Fill(max_dR+(0.1*interval),jetcount,weight);
                }
                else th2d["muon_numjets_vs_dR_nonprompt_zoomin"]->Fill(max_dR+(0.1*interval),jetcount,weight);                
            }            
            
            for (const auto & jet : *raw_jets_intree)
            {
                if (getdR(mu,jet)<=testcone)
                {
                    TLorentzVector muTLV = makeRealTLV(mu.obj);      
                    TLorentzVector jetTLV = makeRealTLV(jet.obj);  
                    auto vectdiff = jetTLV - muTLV;
                    if (mu.isPromptFinalState || mu.isDirectPromptTauDecayProductFinalState) 
                    {                                            
                        th1d["jet_pt_minus_muon_pt_one_jet_in_dR0p4_prompt"]->Fill(vectdiff.Pt(),weight); // was jet.obj.Pt()-mu.obj.Pt()
                        th2d["jet_pt_minus_muon_pt_one_jet_in_dR0p4_prompt_vs_lep_pt"]->Fill(mu.obj.Pt(),vectdiff.Pt(),weight);
                        
                    }
                    else 
                    {
                        th1d["jet_pt_minus_muon_pt_one_jet_in_dR0p4_nonprompt"]->Fill(vectdiff.Pt(),weight);
                        th2d["jet_pt_minus_muon_pt_one_jet_in_dR0p4_nonprompt_vs_lep_pt"]->Fill(mu.obj.Pt(),vectdiff.Pt(),weight);
                    }
                    
                }
            }           

        }
        
    }
    
}
