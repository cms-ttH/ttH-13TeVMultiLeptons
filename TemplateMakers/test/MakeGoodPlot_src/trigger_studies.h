void MakeGoodPlot::trigger_studies(std::vector<int> samps)
{
    bool debug = false;
    int numsamples = samps.size();		
    load_samples(samps);
    
    for (int i=0; i<numsamples; i++)
    {	
	int samp_int = samps[i];
		
	cout << "doing " << sample_names[samp_int] << endl;
        
        
        ch[samp_int]->SetBranchAddress("mcwgt", &mcwgt_intree);
        ch[samp_int]->SetBranchAddress("wgt", &wgt_intree);

        if (debug) cout << "hey0.1" << endl;

        ch[samp_int]->SetBranchAddress("passTrigger", &passTrigger_intree);
        
        if (debug) cout << "hey0.2" << endl;

        ch[samp_int]->SetBranchAddress("preselected_leptons", &preselected_leptons_intree);
        ch[samp_int]->SetBranchAddress("preselected_electrons", &preselected_electrons_intree);
        ch[samp_int]->SetBranchAddress("preselected_muons", &preselected_muons_intree);

        ch[samp_int]->SetBranchAddress("looseMvaBased_leptons", &looseMvaBased_leptons_intree);
        ch[samp_int]->SetBranchAddress("looseMvaBased_electrons", &looseMvaBased_electrons_intree);
        ch[samp_int]->SetBranchAddress("looseMvaBased_muons", &looseMvaBased_muons_intree);

        ch[samp_int]->SetBranchAddress("tightMvaBased_leptons", &tightMvaBased_leptons_intree);
        ch[samp_int]->SetBranchAddress("tightMvaBased_electrons", &tightMvaBased_electrons_intree);
        ch[samp_int]->SetBranchAddress("tightMvaBased_muons", &tightMvaBased_muons_intree);

        ch[samp_int]->SetBranchAddress("preselected_jets", &preselected_jets_intree);
        ch[samp_int]->SetBranchAddress("met", &met_intree);

        //ch[samp_int]->SetBranchAddress("pruned_genParticles", &pruned_genParticles_intree);
        
        
        double count_passSSee_2l = 0.;
        double count_passSSemu_2l = 0.;
        double count_passSSmue_2l = 0.;
        double count_passSSmumu_2l = 0.;

        double count_passSSee_1l = 0.;
        double count_passSSemu_1l = 0.;
        double count_passSSmue_1l = 0.;
        double count_passSSmumu_1l = 0.; 
        
        double count_passSSee_2l_denom = 0.;
        double count_passSSemu_2l_denom = 0.;
        double count_passSSmue_2l_denom = 0.;
        double count_passSSmumu_2l_denom = 0.;

        double count_passSSee_1l_denom = 0.;
        double count_passSSemu_1l_denom = 0.;
        double count_passSSmue_1l_denom = 0.;
        double count_passSSmumu_1l_denom = 0.; 
        
        
        int theEntries = ch[samp_int]->GetEntries();
        
        if (debug) cout << "hey1" << endl;
        
        for (int j=0;j<theEntries;j++)
        {
	    if (debug) cout << "hey1.01" << endl;
            ch[samp_int]->GetEntry(j);
	    if (debug) cout << "hey1.02" << endl;					
            weight = wgt_intree; 
            
            if (debug) cout << "hey1.1" << endl;
            int numtrigfire = (*passTrigger_intree).size();
            if (debug) cout << "hey1.2" << endl;
            
            
            bool passSSee_2l = false;
            bool passSSemu_2l = false;
            bool passSSmue_2l = false;
            bool passSSmumu_2l = false;
            
            bool passSSee_1l = false;
            bool passSSemu_1l = false;
            bool passSSmue_1l = false;
            bool passSSmumu_1l = false;
            
            
            bool passSSee_2l_denom = false;
            bool passSSemu_2l_denom = false;
            bool passSSmue_2l_denom = false;
            bool passSSmumu_2l_denom = false;
            
            bool passSSee_1l_denom = false;
            bool passSSemu_1l_denom = false;
            bool passSSmue_1l_denom = false;
            bool passSSmumu_1l_denom = false;
            
            
            if (debug) cout << "hey2" << endl;
            
            
            
            if (passes_common(samp_int))
            {
                // ee
                if (passes_SSee(samp_int))
                {
                    if ((*tightMvaBased_electrons_intree)[0].obj.Pt()>25. && (*tightMvaBased_electrons_intree)[1].obj.Pt()>15.)
                    {
                        passSSee_2l_denom = true;
                    }

                    if ( (*tightMvaBased_electrons_intree)[0].obj.Pt()>35. && (*tightMvaBased_electrons_intree)[1].obj.Pt()>7. && (*tightMvaBased_electrons_intree)[1].obj.Pt()<=15. 
                        && fabs((*tightMvaBased_electrons_intree)[0].obj.Eta())<2.1) // && fabs((*tightMvaBased_electrons_intree)[1].obj.Eta())<2.1 )
                    {                        
                        passSSee_1l_denom = true;
                    }
                }
                
                // mumu
                if (passes_SSmumu(samp_int))
                {
                    if ((*tightMvaBased_muons_intree)[0].obj.Pt()>20. && (*tightMvaBased_muons_intree)[1].obj.Pt()>10.)
                    {
                        passSSmumu_2l_denom = true;
                    }

                    if ((*tightMvaBased_muons_intree)[0].obj.Pt()>30. && (*tightMvaBased_muons_intree)[1].obj.Pt()>5. && (*tightMvaBased_muons_intree)[1].obj.Pt()<=10.)
                    {
                        passSSmumu_1l_denom = true;
                    }
                }
                                

                // emu
                if ( passes_SSemu(samp_int))
                {
                    if ((*tightMvaBased_electrons_intree)[0].obj.Pt()>25. && (*tightMvaBased_muons_intree)[0].obj.Pt()>10.)
                    {
                        passSSemu_2l_denom = true;
                    }

                    if ((*tightMvaBased_electrons_intree)[0].obj.Pt()>35. && (*tightMvaBased_muons_intree)[0].obj.Pt()>5. && (*tightMvaBased_muons_intree)[0].obj.Pt()<=10. 
                        && fabs((*tightMvaBased_electrons_intree)[0].obj.Eta())<2.1) // && fabs((*tightMvaBased_electrons_intree)[1].obj.Eta())<2.1 )
                    {                        
                        passSSemu_1l_denom = true;
                    }
                }
                

                // mue
                if ( passes_SSemu(samp_int))
                {
                    if ((*tightMvaBased_muons_intree)[0].obj.Pt()>25. && (*tightMvaBased_electrons_intree)[0].obj.Pt()>15.)
                    {
                        passSSmue_2l_denom = true;
                    }

                    if ( (*tightMvaBased_muons_intree)[0].obj.Pt()>30. && (*tightMvaBased_electrons_intree)[0].obj.Pt()>7. && (*tightMvaBased_electrons_intree)[0].obj.Pt()<=15.)
                    {                        
                        passSSmue_1l_denom = true;
                    }
                }
                

                if (debug) cout << "hey3" << endl;

                //passes_3l(samp_int)
                //passes_4l(samp_int)        

                
                
                for (int k=0; k<numtrigfire; k++)
                {

                    // ee
                    if (passSSee_2l_denom)
                    {
                        if ((*passTrigger_intree)[k]=="HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v1")
                        {
                            passSSee_2l = true;
                        }
                    }
                    
                    if (passSSee_2l_denom)
                    {
                        if ((*tightMvaBased_electrons_intree)[0].obj.Pt()>35. && fabs((*tightMvaBased_electrons_intree)[0].obj.Eta())<2.1 // && fabs((*tightMvaBased_electrons_intree)[1].obj.Eta())<2.1
                            && (*passTrigger_intree)[k]=="HLT_Ele32_eta2p1_WP75_Gsf_v1")
                        {
                            passSSee_2l = true;
                        }
                    }                    
                    
                    if (passSSee_1l_denom)
                    {
                        if ((*passTrigger_intree)[k]=="HLT_Ele32_eta2p1_WP75_Gsf_v1")
                        {
                            passSSee_1l = true;
                        }
                    }
                    
                    
                    // mumu
                    if (passSSmumu_2l_denom)
                    {
                        if (((*passTrigger_intree)[k]=="HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v1" || (*passTrigger_intree)[k]=="HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v1"))
                        {
                            passSSmumu_2l = true;
                        }
                    }
                    if (passSSmumu_2l_denom)
                    {
                        if ((*tightMvaBased_muons_intree)[0].obj.Pt()>30. && ((*passTrigger_intree)[k]=="HLT_IsoMu27_v1" || (*passTrigger_intree)[k]=="HLT_IsoTkMu27_v1"))
                        {
                            passSSmumu_2l = true;
                        }
                    }
                    if (passSSmumu_1l_denom)
                    {
                        if (((*passTrigger_intree)[k]=="HLT_IsoMu27_v1" || (*passTrigger_intree)[k]=="HLT_IsoTkMu27_v1"))
                        {
                            passSSmumu_1l = true;
                        }
                    }
                    
                    // emu
                    if (passSSemu_2l_denom)
                    {
                        if ((*passTrigger_intree)[k]=="HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1")
                        {
                            passSSemu_2l = true;
                        }
                    }
                    
                    if (passSSemu_2l_denom)
                    {
                        if ((*tightMvaBased_electrons_intree)[0].obj.Pt()>35. && fabs((*tightMvaBased_electrons_intree)[0].obj.Eta())<2.1 //&& fabs((*tightMvaBased_electrons_intree)[1].obj.Eta())<2.1
                            && (*passTrigger_intree)[k]=="HLT_Ele32_eta2p1_WP75_Gsf_v1")
                        {
                            passSSemu_2l = true;
                        }
                    }                    
                    
                    if (passSSemu_1l_denom)
                    {
                        if ((*passTrigger_intree)[k]=="HLT_Ele32_eta2p1_WP75_Gsf_v1")
                        {
                            passSSemu_1l = true;
                        }
                    }
                    
                    
                    // mue
                    if (passSSmue_2l_denom)
                    {
                        if ((*passTrigger_intree)[k]=="HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1")
                        {
                            passSSmue_2l = true;
                        }
                    }
                    if (passSSmue_2l_denom)
                    {
                        if ((*tightMvaBased_muons_intree)[0].obj.Pt()>30. && ((*passTrigger_intree)[k]=="HLT_IsoMu27_v1" || (*passTrigger_intree)[k]=="HLT_IsoTkMu27_v1"))
                        {
                            passSSmue_2l = true;
                        }
                    }
                    if (passSSmue_1l_denom)
                    {
                        if (((*passTrigger_intree)[k]=="HLT_IsoMu27_v1" || (*passTrigger_intree)[k]=="HLT_IsoTkMu27_v1"))
                        {
                            passSSmue_1l = true;
                        }
                    }                    
            
                }
            }
            
            if (passSSee_2l_denom) count_passSSee_2l_denom += weight;
            if (passSSemu_2l_denom) count_passSSemu_2l_denom += weight;
            if (passSSmue_2l_denom) count_passSSmue_2l_denom += weight;
            if (passSSmumu_2l_denom) count_passSSmumu_2l_denom += weight;

            if (passSSee_1l_denom) count_passSSee_1l_denom += weight;
            if (passSSemu_1l_denom) count_passSSemu_1l_denom += weight;
            if (passSSmue_1l_denom) count_passSSmue_1l_denom += weight;
            if (passSSmumu_1l_denom) count_passSSmumu_1l_denom += weight;
            
            if (passSSee_2l) count_passSSee_2l += weight;
            if (passSSemu_2l) count_passSSemu_2l += weight;
            if (passSSmue_2l) count_passSSmue_2l += weight;
            if (passSSmumu_2l) count_passSSmumu_2l += weight;

            if (passSSee_1l) count_passSSee_1l += weight;
            if (passSSemu_1l) count_passSSemu_1l += weight;
            if (passSSmue_1l) count_passSSmue_1l += weight;
            if (passSSmumu_1l) count_passSSmumu_1l += weight;
            
            if (debug) cout << "hey4" << endl;
        }
         
         
        cout << "  " << endl;
        
        cout << "  " << endl;
        cout << "SS2e:" << endl;
        cout << "  " << endl;
        cout << "Trigger & evts pass & evts & fraction \\" << endl;
        cout << "\hline" << endl;
        cout << "HLT\_Ele23\_Ele12\_CaloIdL\_TrackIdL\_IsoVL\_DZ\_v1 & " << count_passSSee_2l << " & " << count_passSSee_2l_denom << " & " << count_passSSee_2l/count_passSSee_2l_denom << "\\" << endl;
        cout << "OR HLT\_Ele32\_eta2p1\_WP75\_Gsf\_v1 & " << " & " << " & " << "\\" << endl;
        cout << "\hline" << endl;
        cout << "HLT\_Ele32\_eta2p1\_WP75\_Gsf\_v1 & " << count_passSSee_1l << " & " << count_passSSee_1l_denom << " & " << count_passSSee_1l/count_passSSee_1l_denom << "\\" << endl;
        cout << "\hline" << endl;
        cout << "  " << endl;
        
        cout << "  " << endl;
        cout << "SS2mu:" << endl;
        cout << "  " << endl;
        cout << "Trigger & evts pass & evts & fraction \\" << endl;
        cout << "\hline" << endl;
        cout << "HLT\_Mu17\_TrkIsoVVL\_Mu8\_TrkIsoVVL\_DZ\_v1 & " << count_passSSmumu_2l << " & " << count_passSSmumu_2l_denom << " & " << count_passSSmumu_2l/count_passSSmumu_2l_denom << "\\" << endl;
        cout << "OR HLT\_Mu17\_TrkIsoVVL\_TkMu8\_TrkIsoVVL\_DZ\_v1 & " << " & " << " & " << "\\" << endl;
        cout << "OR HLT\_IsoMu27\_v1 & " << " & " << " & " << "\\" << endl;
        cout << "OR HLT\_IsoTkMu27\_v1 & " << " & " << " & " << "\\" << endl;
        cout << "\hline" << endl;        
        cout << "HLT\_IsoMu27\_v1 & " << count_passSSmumu_1l << " & " << count_passSSmumu_1l_denom << " & " << count_passSSmumu_1l/count_passSSmumu_1l_denom << "\\" << endl;
        cout << "OR HLT\_IsoTkMu27\_v1 & " << " & " << " & " << "\\" << endl;
        cout << "\hline" << endl;
        cout << "  " << endl;
        
        cout << "  " << endl;
        cout << "SSemu:" << endl;
        cout << "  " << endl;
        cout << "Trigger & evts pass & evts & fraction \\" << endl;
        cout << "\hline" << endl;
        cout << "HLT_Mu8\_TrkIsoVVL\_Ele23\_CaloIdL\_TrackIdL\_IsoVL\_v1 & " << count_passSSemu_2l << " & " << count_passSSemu_2l_denom << " & " << count_passSSemu_2l/count_passSSemu_2l_denom << "\\" << endl;
        cout << "OR HLT\_Ele32\_eta2p1\_WP75\_Gsf\_v1 & " << " & " << " & " << "\\" << endl;
        cout << "\hline" << endl;
        cout << "HLT\_Ele32\_eta2p1\_WP75\_Gsf\_v1 & " << count_passSSemu_1l << " & " << count_passSSemu_1l_denom << " & " << count_passSSemu_1l/count_passSSemu_1l_denom << "\\" << endl;
        cout << "\hline" << endl;
        cout << "  " << endl;
        
        cout << "  " << endl;
        cout << "SSmue:" << endl;
        cout << "  " << endl;
        cout << "Trigger & evts pass & evts & fraction \\" << endl;
        cout << "\hline" << endl;
        cout << "HLT\_Mu23\_TrkIsoVVL\_Ele12\_CaloIdL\_TrackIdL\_IsoVL\_v1 & " << count_passSSmue_2l << " & " << count_passSSmue_2l_denom << " & " << count_passSSmue_2l/count_passSSmue_2l_denom << "\\" << endl;
        cout << "OR HLT\_IsoMu27\_v1 & " << " & " << " & " << "\\" << endl;
        cout << "OR HLT\_IsoTkMu27\_v1 & " << " & " << " & " << "\\" << endl;
        cout << "\hline" << endl;        
        cout << "HLT\_IsoMu27\_v1 & " << count_passSSmue_1l << " & " << count_passSSmue_1l_denom << " & " << count_passSSmue_1l/count_passSSmue_1l_denom << "\\" << endl;
        cout << "OR HLT\_IsoTkMu27\_v1 & " << " & " << " & " << "\\" << endl;
        cout << "\hline" << endl;
        cout << "  " << endl;
        
        cout << "  " << endl;
     }
            
}
