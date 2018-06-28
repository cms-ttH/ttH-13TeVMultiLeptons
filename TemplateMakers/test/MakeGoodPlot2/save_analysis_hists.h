void MakeGoodPlot::save_analysis_hists()
{
    bool debug = false;
    
    vector<TString> allAnaHists;
    
    allAnaHists.push_back("2los_ee_1b.");
    allAnaHists.push_back("2los_ee_2b.");
    allAnaHists.push_back("2los_sfz_ee_1b.");
    allAnaHists.push_back("2los_sfz_ee_2b.");
    allAnaHists.push_back("2los_emu_1b.");
    allAnaHists.push_back("2los_emu_2b.");
    allAnaHists.push_back("2los_mumu_1b.");
    allAnaHists.push_back("2los_mumu_2b.");
    allAnaHists.push_back("2los_sfz_mumu_1b.");
    allAnaHists.push_back("2los_sfz_mumu_2b.");
    allAnaHists.push_back("2lss_p_ee_1b.");
    allAnaHists.push_back("2lss_p_ee_2b.");
    allAnaHists.push_back("2lss_p_emu_1b.");
    allAnaHists.push_back("2lss_p_emu_2b.");
    allAnaHists.push_back("2lss_p_mumu_1b.");
    allAnaHists.push_back("2lss_p_mumu_2b.");
    allAnaHists.push_back("2lss_m_ee_1b.");
    allAnaHists.push_back("2lss_m_ee_2b.");
    allAnaHists.push_back("2lss_m_emu_1b.");
    allAnaHists.push_back("2lss_m_emu_2b.");
    allAnaHists.push_back("2lss_m_mumu_1b.");
    allAnaHists.push_back("2lss_m_mumu_2b.");
    allAnaHists.push_back("3l_ppp_1b.");
    allAnaHists.push_back("3l_ppp_2b.");
    allAnaHists.push_back("3l_mmm_1b.");
    allAnaHists.push_back("3l_mmm_2b.");
    allAnaHists.push_back("3l_mix_1b.");
    allAnaHists.push_back("3l_mix_2b.");
    allAnaHists.push_back("3l_mix_sfz_1b.");
    allAnaHists.push_back("3l_mix_sfz_2b.");
    allAnaHists.push_back("4l_1b.");
    allAnaHists.push_back("4l_2b.");
    allAnaHists.push_back("ge5l_1b.");
    
    vector<TString> allSysts;
    allSysts.push_back("");
    allSysts.push_back("JESUP");
    allSysts.push_back("JESDOWN");
    // for the other systs, need some way of picking MC-only, etc.
    
    for (int i=0; i<numsamples; i++)
    {    
        int thisSamp = samples[i];
        
        cout << " " << endl;
        cout << " " << endl;
        cout << "Doing " << sample_names[thisSamp] << endl;
        cout << " " << endl; 
        
        
        string strtochg = TString2string(sample_names_reg[thisSamp]);
        //std::replace( strtochg.begin(), strtochg.begin()+1, '_', '');
        strtochg.erase(0,1);
        sample_names_reg[thisSamp] = strtochg.c_str();
        
        
        for (const TString thiscat : allAnaHists)
        {
            for (const TString thissyst : allSysts)
            {   
                if (debug) cout << thiscat+thissyst << endl;
                auto thishist = (TH1D*)hist[i].FindObject(thiscat+thissyst);
                if (debug) cout << "oi 1" << endl;
                
                //strtochg = TString2string(thishist->GetName());
                //std::replace( strtochg.begin(), strtochg.end(), '_JESUP', '.JESUP');
                //std::replace( strtochg.begin(), strtochg.end(), '_JESDOWN', '.JESDOWN');
                //thishist->SetName(strtochg.c_str());
                
                if (thissyst=="") thishist->SetName(thishist->GetName()+sample_names_reg[thisSamp]);
                else thishist->SetName(thishist->GetName()+string(".")+sample_names_reg[thisSamp]);
                
                if (debug) cout << "oi 2" << endl;
                
                if (thisSamp<40) thishist->Scale(lumi*xsec[thisSamp]/numgen[thisSamp]);
                else if(thisSamp>=40 && thisSamp<100) thishist->Scale(lumi);
                
                if (debug) cout << "oi 3" << endl;
                canvas.Add(thishist); //<-- last step 
                if (debug) cout << "oi 4" << endl;
            }
        }
    }
    
    // That's it! Now just pick SaveAllToFile draw option
    
}