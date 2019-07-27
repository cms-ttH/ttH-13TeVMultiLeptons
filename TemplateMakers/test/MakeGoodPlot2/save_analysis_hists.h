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
    //allAnaHists.push_back("3l_ppp_1b.");
    //allAnaHists.push_back("3l_ppp_2b.");
    //allAnaHists.push_back("3l_mmm_1b.");
    //allAnaHists.push_back("3l_mmm_2b.");
    allAnaHists.push_back("3l_mix_p_1b.");
    allAnaHists.push_back("3l_mix_m_1b.");
    allAnaHists.push_back("3l_mix_p_2b.");
    allAnaHists.push_back("3l_mix_m_2b.");
    allAnaHists.push_back("3l_mix_sfz_1b.");
    allAnaHists.push_back("3l_mix_sfz_2b.");
    //allAnaHists.push_back("4l_1b.");
    allAnaHists.push_back("4l_2b.");
    //allAnaHists.push_back("ge5l_1b.");
    
    // ?
    //cats.push_back("2lss.");   
    //cats.push_back("3l.");
    //cats.push_back("2lss_p_ee_1b.");   
    //cats.push_back("3l_ppp_1b.");    
    
    vector<TString> allSysts;
    allSysts.push_back("");
    allSysts.push_back("JESUP");
    allSysts.push_back("JESDOWN");
    allSysts.push_back("FRUP");
    allSysts.push_back("FRDOWN");
    //allSysts.push_back("FRQCD");
    //allSysts.push_back("FRTTBAR");
    allSysts.push_back("CERR1UP");
    allSysts.push_back("CERR1DOWN");
    allSysts.push_back("CERR2UP");
    allSysts.push_back("CERR2DOWN");
    allSysts.push_back("HFUP");
    allSysts.push_back("HFDOWN");
    allSysts.push_back("HFSTATS1UP");
    allSysts.push_back("HFSTATS1DOWN");
    allSysts.push_back("HFSTATS2UP");
    allSysts.push_back("HFSTATS2DOWN");
    allSysts.push_back("LFUP");
    allSysts.push_back("LFDOWN");
    allSysts.push_back("LFSTATS1UP");
    allSysts.push_back("LFSTATS1DOWN");
    allSysts.push_back("LFSTATS2UP");
    allSysts.push_back("LFSTATS2DOWN");
    allSysts.push_back("PDFUP");
    allSysts.push_back("PDFDOWN");
    allSysts.push_back("MURUP");
    allSysts.push_back("MURDOWN");
    allSysts.push_back("MUFUP");
    allSysts.push_back("MUFDOWN");
    allSysts.push_back("LEPIDUP");
    allSysts.push_back("LEPIDDOWN");
    allSysts.push_back("PSISRUP");
    allSysts.push_back("PSISRDOWN");
    allSysts.push_back("TRGUP");
    allSysts.push_back("TRGDOWN");
    allSysts.push_back("PUUP");
    allSysts.push_back("PUDOWN");  
    //allSysts.push_back("ADHOCNJUP");
    //allSysts.push_back("ADHOCNJDOWN");
    
    // for the other systs, need some way of picking MC-only, etc.

    // construct hists for combined 2lss + 3l categories
    // Note: this modifies existing histograms, so comment it out if not using.
    
    cout << "here1" << endl;
    
    for (int i=0; i<numsamples; i++)
    {     
        for (const auto syst : allSysts)
        {
	      int thisSamp = samples[i];
	      cout << i << ", " << thisSamp << ", " << syst << endl;

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

	    if (!(thisSamp>=84 && thisSamp<=88) && (syst=="ADHOCNJUP" || syst=="ADHOCNJDOWN")) continue;

            auto combohist1 = (TH1EFT*)hist[i].FindObject("3l_mix_p_1b."+syst); //->Clone("3l."+syst);
            combohist1->Add((TH1EFT*)hist[i].FindObject("3l_ppp_1b."+syst));
            
            auto combohist2 = (TH1EFT*)hist[i].FindObject("3l_mix_m_1b."+syst);
            combohist2->Add((TH1EFT*)hist[i].FindObject("3l_mmm_1b."+syst));
            
            auto combohist3 = (TH1EFT*)hist[i].FindObject("3l_mix_p_2b."+syst); //->Clone("3l."+syst);
            combohist3->Add((TH1EFT*)hist[i].FindObject("3l_ppp_2b."+syst));            
            
            auto combohist4 = (TH1EFT*)hist[i].FindObject("3l_mix_m_2b."+syst); //->Clone("3l."+syst);
            combohist4->Add((TH1EFT*)hist[i].FindObject("3l_mmm_2b."+syst));
            


        }
    } 

    cout << "\\hline" << endl;
    cout << " & 2lss ($e^{+}e^{+}$)";
    cout << " & 2lss ($e^{+}\\mu^{+}$)";
    cout << " & 2lss ($\\mu^{+}\\mu^{+}$)";
    cout << " & 2lss ($e^{-}e^{-}$)";
    cout << " & 2lss ($e^{-}\\mu^{-}$)";
    cout << " & 2lss ($\\mu^{-}\\mu^{-}$)";
    cout << " & 3l (1b \"p\")";
    cout << " & 3l (1b \"m\")";
    cout << " & 3l ($\\geq$2b \"p\")";
    cout << " & 3l ($\\geq$2b \"m\")";
    cout << " & 3l (SFOS Z, 1b)";
    cout << " & 3l (SFOS Z, $\\geq$2b)";
    cout << " & $\\geq$4l";
    cout << " \\\\ " << endl;
    cout << "\\hline" << endl;

    //TH1EFT *data;

    for (int i=0; i<numsamples; i++)
    {    
        int thisSamp = samples[i];
        
//         cout << " " << endl;
//         cout << " " << endl;
//         cout << "Doing " << sample_names[thisSamp] << endl;
//         cout << " " << endl; 
        
        
        string strtochg = TString2string(sample_names_reg[thisSamp]);
        //std::replace( strtochg.begin(), strtochg.begin()+1, '_', '');
        strtochg.erase(0,1);
        sample_names_reg[thisSamp] = strtochg.c_str();
        
  
//         cout << "\\hline" << endl;
//         cout << " & 2lss ($e^{+}e^{+}$)";
//         cout << " & 2lss ($e^{+}\\mu^{+}$)";
//         cout << " & 2lss ($\\mu^{+}\\mu^{+}$)";
//         cout << " & 2lss ($e^{-}e^{-}$)";
//         cout << " & 2lss ($e^{-}\\mu^{-}$)";
//         cout << " & 2lss ($\\mu^{-}\\mu^{-}$)";
//         cout << " & 3l (1b)";
//         cout << " & 3l ($\\geq$2b)";
//         cout << " & 3l (SFOS Z, 1b)";
//         cout << " & 3l (SFOS Z, $\\geq$2b)";
//         cout << " & $\\geq$4l";
//         cout << " \\\\ " << endl;
//         cout << "\\hline" << endl;
  
        vector<double> nomylds;
        for (const TString thissyst : allSysts)
        {
            if (thissyst=="") cout << sample_names[thisSamp] << ": ";
            else cout << sample_names[thisSamp] << ", " << thissyst << ": ";
            
            int cnt=0;            
            
            
            for (const TString thiscat : allAnaHists)
            {   
                if (debug) cout << thiscat+thissyst << endl;
                
                
                if (thisSamp!=95 && (thissyst=="FRUP" || thissyst=="FRDOWN")) continue;
                if (thisSamp==95 && (thissyst!="FRUP" && thissyst!="FRDOWN" && thissyst!="")) continue;
                if (thisSamp==94 && thissyst!="") continue;
                if (thisSamp>99 && thissyst!="") continue;
                if (!(thisSamp>=84 && thisSamp<=88) && (thissyst=="ADHOCNJUP" || thissyst=="ADHOCNJDOWN")) continue;

                auto thishist = (TH1EFT*)hist[i].FindObject(thiscat+thissyst);
                
                if (thissyst=="") thishist->SetName(thishist->GetName()+sample_names_reg[thisSamp]);
                else thishist->SetName(thishist->GetName()+string(".")+sample_names_reg[thisSamp]);
                
                
                if (thisSamp<40)
                {
                    thishist->Scale(lumi*xsec[thisSamp]/numgen[thisSamp]);
                    // Dibosons
                    if (thisSamp==11)
                    {
                        if (thissyst=="") ((TH1EFT*)hist[i-1].FindObject(thiscat+thissyst+sample_names_reg[10]))->Add(thishist); // assumes i-1 is sample 10 (WZ)!!!
                        else ((TH1EFT*)hist[i-1].FindObject(thiscat+thissyst+string(".")+sample_names_reg[10]))->Add(thishist); // assumes i-1 is sample 10 (WZ)!!!
                    }
                    if (thisSamp==12)
                    {
                        if (thissyst=="") ((TH1EFT*)hist[i-2].FindObject(thiscat+thissyst+sample_names_reg[10]))->Add(thishist); // assumes i-2 is sample 10 (WZ)!!!
                        else ((TH1EFT*)hist[i-2].FindObject(thiscat+thissyst+string(".")+sample_names_reg[10]))->Add(thishist); // assumes i-2 is sample 10 (WZ)!!!
                    }
                    // Tribosons
                    if (thisSamp==23)
                    {
                        if (thissyst=="") ((TH1EFT*)hist[i-1].FindObject(thiscat+thissyst+sample_names_reg[22]))->Add(thishist); // assumes i-1 is sample 22 (WWW)!!!
                        else ((TH1EFT*)hist[i-1].FindObject(thiscat+thissyst+string(".")+sample_names_reg[22]))->Add(thishist); // assumes i-1 is sample 22 (WWW)!!!
                    }
                    if (thisSamp==24)
                    {
                        if (thissyst=="") ((TH1EFT*)hist[i-2].FindObject(thiscat+thissyst+sample_names_reg[22]))->Add(thishist); // assumes i-2 is sample 22 (WWW)!!!
                        else ((TH1EFT*)hist[i-2].FindObject(thiscat+thissyst+string(".")+sample_names_reg[22]))->Add(thishist); // assumes i-2 is sample 22 (WWW)!!!
                    }
                    if (thisSamp==25)
                    {
                        if (thissyst=="") ((TH1EFT*)hist[i-3].FindObject(thiscat+thissyst+sample_names_reg[22]))->Add(thishist); // assumes i-3 is sample 22 (WWW)!!!
                        else ((TH1EFT*)hist[i-3].FindObject(thiscat+thissyst+string(".")+sample_names_reg[22]))->Add(thishist); // assumes i-3 is sample 22 (WWW)!!!
                    }                    
                }
                else if(thisSamp>=40 && thisSamp<84) 
                {
                    thishist->ScaleFits(lumi);
                    thishist->Scale(WCPoint());
                    if (thissyst=="PDFUP" || thissyst=="PDFDOWN" || thissyst=="MURUP" || thissyst=="MURDOWN" || thissyst=="MUFUP" || thissyst=="MUFDOWN")
                    {
                        auto nomhist = (TH1EFT*)hist[i].FindObject(thiscat+sample_names_reg[thisSamp]); // should have already been scaled
                        double normamnt = (nomhist->GetEntries()!=0 && thishist->Integral()!=0.) ? nomhist->Integral()/thishist->Integral() : 1.;
                        thishist->ScaleFits(normamnt);
                        thishist->Scale(WCPoint());
                    }
                }
                else if(thisSamp>=84 && thisSamp<90) 
                {
                    double addlfactor = 1.;
                    //if (thisSamp==87 && (thiscat=="3l_mix_p_1b." || thiscat=="3l_mix_m_1b." || thiscat=="3l_mix_p_2b." || thiscat=="3l_mix_m_2b.")) addlfactor = extra_tllq_factor_3lnonZ;
                    //else if (thisSamp==87 && (thiscat=="2lss_p_ee_2b." || thiscat=="2lss_p_emu_2b." || thiscat=="2lss_p_mumu_2b." || thiscat=="2lss_m_ee_2b." || thiscat=="2lss_m_emu_2b." || thiscat=="2lss_m_mumu_2b.")) addlfactor = extra_tllq_factor_2lss;
                    
                    //thishist->ScaleFits(addlfactor*lumi*xsec[thisSamp]); // see rateinfo.h
                    thishist->ScaleFits(lumi*xsec[thisSamp]/numgen[thisSamp]); // using updated norm method for EFT samps
                    thishist->Scale(WCPoint()); // SM
                    
                    //WCPoint pt;
                    //pt.setStrength("ctZ",10.);
                    //thishist->Scale(pt);
                    
                    // systematics that are shape-only variations:
                    if (thissyst=="PDFUP" || thissyst=="PDFDOWN" || thissyst=="MURUP" || thissyst=="MURDOWN" || thissyst=="MUFUP" || thissyst=="MUFDOWN")
                    {
                        auto nomhist = (TH1EFT*)hist[i].FindObject(thiscat+sample_names_reg[thisSamp]); // should have already been scaled
                        double normamnt = (nomhist->GetEntries()!=0 && thishist->Integral()!=0.) ? nomhist->Integral()/thishist->Integral() : 1.;
                        thishist->ScaleFits(normamnt);
                        thishist->Scale(WCPoint()); // SM
                    }
                }
                //else if (thisSamp>99)
                else if (thisSamp==104)
                {
                    //cout << "hey" << endl;
//                     if (thisSamp==100) data = (TH1EFT*)hist[i].FindObject(thiscat+thissyst+sample_names_reg[thisSamp])->Clone();
//                     else data->Add(thishist);
                    
                    // The following assumes that you're including all the data samples (100-104), and that 104 was the last sample included.
                    auto data = (TH1EFT*)hist[i].FindObject(thiscat+sample_names_reg[thisSamp]);
                    data->Add((TH1EFT*)hist[i-1].FindObject(thiscat+sample_names_reg[103]));
                    data->Add((TH1EFT*)hist[i-2].FindObject(thiscat+sample_names_reg[102]));
                    data->Add((TH1EFT*)hist[i-3].FindObject(thiscat+sample_names_reg[101]));
                    data->Add((TH1EFT*)hist[i-4].FindObject(thiscat+sample_names_reg[100]));                    
                    
                }
                
                TString cltxt = "\\textcolor{black}{";
                
                if (thissyst=="")
                {
                    nomylds.push_back(thishist->Integral());
                }
                else
                {
                    double offamnt = abs((thishist->Integral() - nomylds[cnt])/nomylds[cnt]);
                    if (offamnt>0.05) cltxt = "\\textcolor{red}{";
                
                }

                cout << " & " << cltxt << std::fixed << std::setprecision(2) << thishist->Integral() << "}";
                //cout << " & " << cltxt << std::fixed << std::setprecision(2) << abs((thishist->Integral() - nomylds[cnt])/nomylds[cnt]) << "}";
                
                if (!(thisSamp>=10 && thisSamp<=12) && !(thisSamp>=22 && thisSamp<=25) && thisSamp<100) canvas.Add(thishist); //<-- last step 
                if (thisSamp==12) 
                {
                    if (thissyst=="") canvas.Add( (TH1EFT*)hist[i-2].FindObject(thiscat+thissyst+sample_names_reg[10]) );
                    else canvas.Add( (TH1EFT*)hist[i-2].FindObject(thiscat+thissyst+string(".")+sample_names_reg[10]) );
                }
                if (thisSamp==25) 
                {
                    if (thissyst=="") canvas.Add( (TH1EFT*)hist[i-3].FindObject(thiscat+thissyst+sample_names_reg[22]) );
                    else canvas.Add( (TH1EFT*)hist[i-3].FindObject(thiscat+thissyst+string(".")+sample_names_reg[22]) );
                }     
                if (thisSamp==104)
                {
                    auto data = (TH1EFT*)hist[i].FindObject(thiscat+sample_names_reg[thisSamp]);
                    data->SetName(thiscat+thissyst+"data");
                    //cout << "blah" << endl;
                    canvas.Add(data);
                }           
                cnt++;
            }
            
            cout << " \\\\ " << endl;   
            
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
        
        cout << "  " << endl;
        cout << "  " << endl;        
        
    }
    
    // That's it! Now just pick SaveAllToFile draw option
    
}
