void MakeGoodPlot::save_analysis_hists()
{
    bool debug = false;
    
    vector<TString> allAnaHists;
    vector<TString> cats;
    
    //allAnaHists.push_back("2los_ee_1b.");
    //allAnaHists.push_back("2los_ee_2b.");
    //allAnaHists.push_back("2los_sfz_ee_1b.");
    //allAnaHists.push_back("2los_sfz_ee_2b.");
    //allAnaHists.push_back("2los_emu_1b.");
    //allAnaHists.push_back("2los_emu_2b.");
    //allAnaHists.push_back("2los_mumu_1b.");
    //allAnaHists.push_back("2los_mumu_2b.");
    //allAnaHists.push_back("2los_sfz_mumu_1b.");
    //allAnaHists.push_back("2los_sfz_mumu_2b.");
    //allAnaHists.push_back("2lss_p_ee_1b.");
    allAnaHists.push_back("2lss_p_ee_2b.");
    //allAnaHists.push_back("2lss_p_emu_1b.");
    allAnaHists.push_back("2lss_p_emu_2b.");
    //allAnaHists.push_back("2lss_p_mumu_1b.");
    allAnaHists.push_back("2lss_p_mumu_2b.");
    //allAnaHists.push_back("2lss_m_ee_1b.");
    allAnaHists.push_back("2lss_m_ee_2b.");
    //allAnaHists.push_back("2lss_m_emu_1b.");
    allAnaHists.push_back("2lss_m_emu_2b.");
    //allAnaHists.push_back("2lss_m_mumu_1b.");
    allAnaHists.push_back("2lss_m_mumu_2b.");
    allAnaHists.push_back("3l_ppp_1b.");
    allAnaHists.push_back("3l_ppp_2b.");
    allAnaHists.push_back("3l_mmm_1b.");
    allAnaHists.push_back("3l_mmm_2b.");
    allAnaHists.push_back("3l_mix_1b.");
    allAnaHists.push_back("3l_mix_2b.");
    allAnaHists.push_back("3l_mix_sfz_1b.");
    allAnaHists.push_back("3l_mix_sfz_2b.");
    //allAnaHists.push_back("4l_1b.");
    allAnaHists.push_back("4l_2b.");
    //allAnaHists.push_back("ge5l_1b.");
    
    //cats.push_back("2lss.");   
    //cats.push_back("3l.");
    cats.push_back("2lss_p_ee_1b.");   
    cats.push_back("3l_ppp_1b.");    
    
    vector<TString> allSysts;
    allSysts.push_back("");
    allSysts.push_back("JESUP");
    allSysts.push_back("JESDOWN");
    allSysts.push_back("FRUP");
    allSysts.push_back("FRDOWN");
    
    // for the other systs, need some way of picking MC-only, etc.

    // construct hists for combined 2lss + 3l categories
    // Note: this modifies existing histograms, so comment it out if not using.
    for (int i=0; i<numsamples; i++)
    {     
        for (const auto syst : allSysts)
        {
//             auto combohist1 = (TH1EFT*)hist[i].FindObject("2lss_p_ee_1b."+syst); //->Clone("2lss."+syst);
//             combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_p_emu_1b."+syst));
//             combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_p_mumu_1b."+syst));
//             combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_m_ee_1b."+syst));
//             combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_m_emu_1b."+syst));
//             combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_m_mumu_1b."+syst));
//             combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_p_ee_2b."+syst));
//             combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_p_emu_2b."+syst));
//             combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_p_mumu_2b."+syst));
//             combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_m_ee_2b."+syst));
//             combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_m_emu_2b."+syst));
//             combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_m_mumu_2b."+syst));            
//             if (debug) combohist1->DumpFits();
//             if (debug) cout << "Should be same as: " << endl;
//             if (debug) ((TH1EFT*)hist[i].FindObject("2lss_p_ee_1b."+syst))->DumpFits();
//             //hist[i].Add(combohist1);
//             
//             auto combohist2 = (TH1EFT*)hist[i].FindObject("3l_ppp_1b."+syst); //->Clone("3l."+syst);
//             combohist2->Add((TH1EFT*)hist[i].FindObject("3l_mmm_1b."+syst));
//             combohist2->Add((TH1EFT*)hist[i].FindObject("3l_mix_1b."+syst));
//             combohist2->Add((TH1EFT*)hist[i].FindObject("3l_mix_sfz_1b."+syst));
//             combohist2->Add((TH1EFT*)hist[i].FindObject("3l_ppp_2b."+syst));
//             combohist2->Add((TH1EFT*)hist[i].FindObject("3l_mmm_2b."+syst));
//             combohist2->Add((TH1EFT*)hist[i].FindObject("3l_mix_2b."+syst));
//             combohist2->Add((TH1EFT*)hist[i].FindObject("3l_mix_sfz_2b."+syst));            
//             if (debug) combohist2->DumpFits();
//             if (debug) cout << "Should be same as: " << endl;
//             if (debug) ((TH1EFT*)hist[i].FindObject("3l_ppp_1b."+syst))->DumpFits();
//             //hist[i].Add(combohist2);            


            auto combohist1 = (TH1EFT*)hist[i].FindObject("3l_mix_1b."+syst); //->Clone("3l."+syst);
            combohist1->Add((TH1EFT*)hist[i].FindObject("3l_mmm_1b."+syst));
            combohist1->Add((TH1EFT*)hist[i].FindObject("3l_ppp_1b."+syst));
            
            auto combohist2 = (TH1EFT*)hist[i].FindObject("3l_mix_2b."+syst); //->Clone("3l."+syst);
            combohist2->Add((TH1EFT*)hist[i].FindObject("3l_mmm_2b."+syst));
            combohist2->Add((TH1EFT*)hist[i].FindObject("3l_ppp_2b."+syst));


        }
    } 



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
        
        
        for (const TString thissyst : allSysts)
        {
            for (const TString thiscat : allAnaHists)
            {   
                if (debug) cout << thiscat+thissyst << endl;
                
                if (thisSamp!=95 && (thissyst=="FRUP" || thissyst=="FRDOWN")) continue;
                
                auto thishist = (TH1EFT*)hist[i].FindObject(thiscat+thissyst);
                
                if (thissyst=="") thishist->SetName(thishist->GetName()+sample_names_reg[thisSamp]);
                else thishist->SetName(thishist->GetName()+string(".")+sample_names_reg[thisSamp]);
                
                if (thisSamp<40) thishist->Scale(lumi*xsec[thisSamp]/numgen[thisSamp]);
                else if(thisSamp>=40 && thisSamp<84) 
                {
                    thishist->ScaleFits(lumi);
                }
                else if(thisSamp>=84 && thisSamp<90) 
                {
                    thishist->ScaleFits(lumi*xsec[thisSamp]); // <- not really the xsec under this condition (see rateinfo.h)
                }
                canvas.Add(thishist); //<-- last step 
            }
            
//             for (const TString thiscat : cats)
//             {   
//                 if (debug) cout << thiscat+thissyst << endl;
//                 auto thishist = (TH1EFT*)hist[i].FindObject(thiscat+thissyst);
//                 
//                 if (thissyst=="") thishist->SetName(thishist->GetName()+sample_names_reg[thisSamp]);
//                 else thishist->SetName(thishist->GetName()+string(".")+sample_names_reg[thisSamp]);
//                 
//                 if (thisSamp<40) thishist->Scale(lumi*xsec[thisSamp]/numgen[thisSamp]);
//                 else if(thisSamp>=40 && thisSamp<94) 
//                 {
//                     thishist->ScaleFits(lumi);
//                 }
//                 
//                 canvas.Add(thishist); //<-- last step 
//             }

        }
    }
    
    // That's it! Now just pick SaveAllToFile draw option
    
}