void MakeGoodPlot::standard_plots()
{
    
    std::vector<std::pair<GoodPlot*,int>> canvect;
    
    //canvect.push_back({new GoodPlot("category_yields","darren"),-1});
    //canvect.push_back({new GoodPlot("category_yields_njets_nbjets","darren"),-1});
    
    vector<TString> cats;
    vector<std::pair<TString,int>> quants;

    
    // CRs (actually just use the combos now)
//     cats.push_back("2los_ee");
//     cats.push_back("2los_emu");
//     cats.push_back("2los_mumu");
//     cats.push_back("2los_sfz_ee");
//     cats.push_back("2los_sfz_mumu");
//     cats.push_back("2lss_p_ee");
//     cats.push_back("2lss_p_emu");
//     cats.push_back("2lss_p_mumu");
//     cats.push_back("2lss_m_ee");
//     cats.push_back("2lss_m_emu");
//     cats.push_back("2lss_m_mumu");
//     cats.push_back("3l_ppp");
//     cats.push_back("3l_mmm");
//     cats.push_back("3l_mix");
//     cats.push_back("3l_mix_p");
//     cats.push_back("3l_mix_m");
//     cats.push_back("3l_mix_sfz");
// //     cats.push_back("4l");
// //     cats.push_back("ge5l");
// //     cats.push_back("1l_mu");
// //     cats.push_back("1l_e");
    
    
     
     // CR quants
//      quants.push_back({"__nbjets.",-1});
//      quants.push_back({"__njets.",-1});
//      quants.push_back({"__jetpt.",-1});        // 5
//      quants.push_back({"__jeteta.",-1});
// //     quants.push_back({"__jetcsv",-1});
//      quants.push_back({"__jetDeepCSV.",5});       // 5
// //     quants.push_back({"__jetDeepCSVprobb",-1});
// //     quants.push_back({"__jetDeepCSVprobbb",-1});
// //     quants.push_back({"__leppt",2});       // 5
//      quants.push_back({"__lep1pt.",2});      // 5
//      quants.push_back({"__lep2pt.",2});      // 5
//      quants.push_back({"__lepeta.",-1});
//      quants.push_back({"__llmass.",-1});

//     quants.push_back({"__lepMVA",-1});    
//     quants.push_back({"__met",2});         // 5
//     quants.push_back({"__metphi",-1});
//     quants.push_back({"__MHT",2});         // 5
//     quants.push_back({"__HT",2});         // 5
//     quants.push_back({"__numPVs",-1});
//     quants.push_back({"__PUMVA",-1});
//     quants.push_back({"__qgid",-1});
//     quants.push_back({"__dxy",-1});
//     quants.push_back({"__dz",-1});
//     quants.push_back({"__miniIso",-1});
//     quants.push_back({"__miniIsoR",-1});
//     quants.push_back({"__miniIsoCharged",-1});
//     quants.push_back({"__miniIsoNeutral",-1});
//     quants.push_back({"__jetPtRatio",-1});
//     quants.push_back({"__jetPtRel",-1});
//     quants.push_back({"__nearestJetCSV",-1});
//     quants.push_back({"__sip3D",-1});
//     quants.push_back({"__jet_nCharged_tracks",-1});
//     quants.push_back({"__effArea",-1});
//     quants.push_back({"__rho",-1});
//     quants.push_back({"__correctedPt",20});

//     quants.push_back({"__nnpdfWeightUp",-1});
//     quants.push_back({"__nnpdfWeightDown",-1});
//     quants.push_back({"__muRWeightUp",-1});
//     quants.push_back({"__muRWeightDown",-1});
//     quants.push_back({"__muFWeightUp",-1});
//     quants.push_back({"__muFWeightDown",-1});

    
    // or ...
    // sig regions
    quants.push_back({"",-1});
    cats.push_back("2lss_p_ee_2b.");
    cats.push_back("2lss_p_emu_2b.");
    cats.push_back("2lss_p_mumu_2b.");
    cats.push_back("2lss_m_ee_2b.");
    cats.push_back("2lss_m_emu_2b.");
    cats.push_back("2lss_m_mumu_2b.");
    //cats.push_back("3l_ppp_1b.");
    //cats.push_back("3l_ppp_2b.");
    //cats.push_back("3l_mmm_1b.");
    //cats.push_back("3l_mmm_2b.");    
    cats.push_back("3l_mix_p_1b.");
    cats.push_back("3l_mix_m_1b.");
     cats.push_back("3l_mix_p_2b.");
    cats.push_back("3l_mix_m_2b.");
    cats.push_back("3l_mix_sfz_1b.");
    cats.push_back("3l_mix_sfz_2b.");
    //cats.push_back("4l_1b.");
    cats.push_back("4l_2b.");
    ////cats.push_back("ge5l_1b.");
//     
    
    
    // it's this one for CR cats!
//    cats.push_back("2lss"); // if you don't want the combo plots just comment this    
//    cats.push_back("3l_mix"); // if you don't want the combo plots just comment this
//    cats.push_back("3l_mix_sfz"); // if you don't want the combo plots just comment this

    // mainly for sync
//     cats.push_back("all");
//     quants.push_back({"__miniIsoCharged",-1});
//     quants.push_back({"__miniIsoNeutral",-1});
//     quants.push_back({"__leppt",-1});
//     quants.push_back({"__lepeta.",-1});
//     quants.push_back({"__jetPtRatio",-1});
//     quants.push_back({"__jetcsv",-1});
//     quants.push_back({"__jet_nCharged_tracks",-1});
//     quants.push_back({"__jetPtRel",-1});
//     quants.push_back({"__dxy",-1});
//     quants.push_back({"__dz",-1});
//     quants.push_back({"__sip3D",-1});
//     //t->Draw(l+"_ntMVAeleID>>all__eleMVA(200,?,?)",cond);      // mvaIdFall17noIso  to add
//     //t->Draw(l+"_segmentCompatibility>>all__segmentCompatibility(?,?,?)",cond);       // segmentCompatibility
//     quants.push_back({"__lepMVA",-1});


    for (const TString cat : cats)
    {
        for (const auto quant : quants)
        {
            canvect.push_back({new GoodPlot(cat+quant.first,"darren"),quant.second});
        }
    }
    
    // construct hists for combined 2lss + 3l categories:
    for (int i=0; i<numsamples; i++)
    {     
        for (const auto quant : quants)
        {
            for (int thisSyst=0; thisSyst<numberOfSysts; thisSyst++) // comment out for non-"." hists
            //for (int thisSyst=0; thisSyst<1; thisSyst++) // comment out for "." hists
            {
                // mainly for CRs //
            
//                 auto combohist1 = (TH1EFT*)hist[i].FindObject("2lss_p_ee"+quant.first+systint2str(thisSyst))->Clone("2lss"+quant.first+systint2str(thisSyst));
//                 combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_p_emu"+quant.first+systint2str(thisSyst)));
//                 combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_p_mumu"+quant.first+systint2str(thisSyst)));
//                 combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_m_ee"+quant.first+systint2str(thisSyst)));
//                 combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_m_emu"+quant.first+systint2str(thisSyst)));
//                 combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_m_mumu"+quant.first+systint2str(thisSyst)));
//             
//                 hist[i].Add(combohist1);
//             
//                 auto combohist2 = (TH1EFT*)hist[i].FindObject("3l_ppp"+quant.first+systint2str(thisSyst))->Clone("3l_mix"+quant.first+systint2str(thisSyst));
//                 combohist2->Add((TH1EFT*)hist[i].FindObject("3l_mmm"+quant.first+systint2str(thisSyst)));
//                 combohist2->Add((TH1EFT*)hist[i].FindObject("3l_mix_p"+quant.first+systint2str(thisSyst)));
//                 combohist2->Add((TH1EFT*)hist[i].FindObject("3l_mix_m"+quant.first+systint2str(thisSyst)));
//             
//                 hist[i].Add(combohist2);            
            
                // --------------- //
                // Mainly for SRs  //
            
                ((TH1EFT*)hist[i].FindObject("3l_mix_p_1b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("3l_ppp_1b."+quant.first+systint2str(thisSyst)));
                ((TH1EFT*)hist[i].FindObject("3l_mix_m_1b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("3l_mmm_1b."+quant.first+systint2str(thisSyst)));
                ((TH1EFT*)hist[i].FindObject("3l_mix_p_2b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("3l_ppp_2b."+quant.first+systint2str(thisSyst)));
                ((TH1EFT*)hist[i].FindObject("3l_mix_m_2b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("3l_mmm_2b."+quant.first+systint2str(thisSyst)));
                    
                
                // for sync
//                 if(quant.first=="__jet_nCharged_tracks")
//                 {
//                     ((TH1EFT*)hist[i].FindObject("all"+quant.first))->SetTitle(";jetNDauChargedMVASel");
//                 }

                
            }
        }
    }  
    

    // n.b.: if this crashes, check first if there's a mismatch in number of systs saved in 
    // a given file and the number in numberOfSysts

    // now actually make the plots and save them:
    for (int i=0; i<numsamples; i++)
    //for (int i=(numsamples-1); i>=0; i--)
    {           
        cout << " " << endl;
        cout << "Doing " << sample_names[samples[i]] << endl;
        double wc = 0.;
        if (samples[i]>99)
        {
            for (int j=0; j<canvect.size(); j++)
            {
                canvect[j].first->addPlotData(*this,"same",i,"samp",canvect[j].second,"E");
            }

            continue;
        }
        
        for (int j=0; j<canvect.size(); j++)
        {
            //canvect[j].first->addPlot(*this, "same", i, "samp");
            canvect[j].first->addStackWithSumMC(*this,"same",i,"samp",canvect[j].second);
            //canvect[j].first->addPlotNorm(*this, "same", i, "samp",canvect[j].second,"E");
            //if (samples[i]<40) canvect[j].first->addPlotNorm(*this, "auto", i, "samp",canvect[j].second,"E");
            //else if (samples[i]<94) canvect[j].first->addPlotNormTH1EFT(*this, "auto", i,wc,"samp",canvect[j].second,"E");
        }              

    }
    
    //can1->printStackContents();
    //can1->printStackContentsLatex();
//    can1->printCombosLatex(*this);

    //cancategory_yields_njets_nbjets->printStackContentsLatex();
    //cancategory_yields_njets_nbjets->printStackContentsForCard(*this);
        
    
    // if you're plotting the per-category hists:
    
    
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
    
    cout << "Diboson";
    for (int j=0; j<canvect.size(); j++)
    {        
        cout << " & " << std::fixed << std::setprecision(2) << canvect[j].first->sumDiboson->Integral();
    }
    cout << " \\\\ " << endl;

    cout << "Triboson";
    for (int j=0; j<canvect.size(); j++)
    {        
        cout << " & " << std::fixed << std::setprecision(2) << canvect[j].first->sumTriboson->Integral();
    }        
    cout << " \\\\ " << endl;
    
//     cout << "Single Top";
//     for (int j=0; j<canvect.size(); j++)
//     {        
//         cout << " & " << std::fixed << std::setprecision(2) << canvect[j].first->sumSingleTop->Integral();
//     }        
//     cout << " \\\\ " << endl;    
    

    for (int i=0; i<numsamples; i++)
    {
        if (samples[i]==getComboSampInt(samples[i])) // finds ones that AREN'T in a combo
        {
            cout << sample_names[samples[i]];
            for (int j=0; j<canvect.size(); j++)
            {
                cout << " & " << std::fixed << std::setprecision(2) << ((TH1*)canvect[j].first->thestack->GetHists()->At(i))->Integral(); // Oh Yeah. Ridiculous index + pointer achievement unlocked
            }
            cout << " \\\\ " << endl;
        }
    }
    cout << "\\hline" << endl;

    cout << "Sum Signal";
    for (int j=0; j<canvect.size(); j++)
    {
        double sumsig = ((TH1*)canvect[j].first->thestack->GetStack()->Last())->Integral() - ((TH1*)canvect[j].first->thebackstack->GetStack()->Last())->Integral();
        cout << " & " << std::fixed << std::setprecision(2) << sumsig; // Oh Yeah. Ridiculous index + pointer achievement unlocked
    }
    cout << " \\\\ " << endl;

    
    cout << "Sum Background";
    for (int j=0; j<canvect.size(); j++)
    {
        cout << " & " << std::fixed << std::setprecision(2) << ((TH1*)canvect[j].first->thebackstack->GetStack()->Last())->Integral(); // Oh Yeah. Ridiculous index + pointer achievement unlocked
    }
    cout << " \\\\ " << endl;
              
    cout << "Sig/$\\sqrt{Bkgd}$";
    for (int j=0; j<canvect.size(); j++)
    {
        double sumsig = ((TH1*)canvect[j].first->thestack->GetStack()->Last())->Integral() - ((TH1*)canvect[j].first->thebackstack->GetStack()->Last())->Integral();
        sumsig = sumsig / sqrt(((TH1*)canvect[j].first->thebackstack->GetStack()->Last())->Integral());
        cout << " & " << std::fixed << std::setprecision(2) << sumsig; // Oh Yeah. Ridiculous index + pointer achievement unlocked
    }
    cout << " \\\\ " << endl;
    
    
    
}

