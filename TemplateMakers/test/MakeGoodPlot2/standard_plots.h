void MakeGoodPlot::standard_plots()
{
    
    std::vector<std::pair<GoodPlot*,int>> canvect;
    
    //canvect.push_back({new GoodPlot("category_yields","darren"),-1});
    //canvect.push_back({new GoodPlot("category_yields_njets_nbjets","darren"),-1});
    
    vector<TString> cats;
    vector<std::pair<TString,int>> quants;

    bool sr = true;                                    //// <<-------------
    
    bool scaleFromFits = sr;
    
    // CRs (actually just use the combos below now - this section just for ref)
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
    
    
    if (!sr)
    {
    
        // CR quants
//        quants.push_back({"__nbjets.",-1});
        quants.push_back({"__njets.",-1});
//         quants.push_back({"__jetpt.",2});        // 5
//         quants.push_back({"__jeteta.",2});
//         quants.push_back({"__jetDeepCSV.",5});       // 5
//         quants.push_back({"__lep1pt.",2});      // 5
//         quants.push_back({"__lep2pt.",2});      // 5
//         quants.push_back({"__lepeta.",2});
//         quants.push_back({"__llmass.",-1});
//         quants.push_back({"__met.",2});         // 5
//         quants.push_back({"__MHT.",4});         // 5    
//         quants.push_back({"__PUMVA.",40});    
//         quants.push_back({"__ntaus.",-1});
//         quants.push_back({"__hadtopmass.",10});
//         quants.push_back({"__HT.",10});
    
        // if doing any of the ones below, need to change the loop over systs also below!
    //     quants.push_back({"__jetcsv",-1});    
        //     quants.push_back({"__jetDeepCSVprobb",-1});
    //     quants.push_back({"__jetDeepCSVprobbb",-1});
    //     quants.push_back({"__leppt",2});       // 5
    //     quants.push_back({"__lepMVA",-1});    
    //     quants.push_back({"__metphi",-1});
    //     quants.push_back({"__HT",2});         // 5
    //     quants.push_back({"__numPVs",8});
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
    }
    else
    {
    // or ...
    // sig regions
        quants.push_back({"",-1});
//        cats.push_back("2lss.");        
        cats.push_back("2lss_p_ee_2b.");
        cats.push_back("2lss_p_emu_2b.");
        cats.push_back("2lss_p_mumu_2b.");
        cats.push_back("2lss_m_ee_2b.");
        cats.push_back("2lss_m_emu_2b.");
        cats.push_back("2lss_m_mumu_2b.");
        cats.push_back("3l_mix_p_1b.");
        cats.push_back("3l_mix_m_1b.");
        cats.push_back("3l_mix_p_2b.");
        cats.push_back("3l_mix_m_2b.");
        cats.push_back("3l_mix_sfz_1b.");
        cats.push_back("3l_mix_sfz_2b.");
        cats.push_back("4l_2b.");
        
        
        //cats.push_back("3l_ppp_1b.");
        //cats.push_back("3l_ppp_2b.");
        //cats.push_back("3l_mmm_1b.");
        //cats.push_back("3l_mmm_2b.");         
        //cats.push_back("4l_1b.");
    ////cats.push_back("ge5l_1b.");
//     
    }
    
    if (!sr)
    {
        // CR combo cats
        cats.push_back("2lss"); // if you don't want the combo plots just comment this    
        cats.push_back("3l_mix"); // if you don't want the combo plots just comment this
        cats.push_back("3l_mix_sfz"); // if you don't want the combo plots just comment this
    }
  
    
    
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
            canvect.push_back({new GoodPlot(cat+quant.first,"darren",1,1,scaleFromFits),quant.second});
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
                if (!sr)
                {
                    auto combohist1 = (TH1EFT*)hist[i].FindObject("2lss_p_ee"+quant.first+systint2str(thisSyst))->Clone("2lss"+quant.first+systint2str(thisSyst));
                    combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_p_emu"+quant.first+systint2str(thisSyst)));
                    combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_p_mumu"+quant.first+systint2str(thisSyst)));
                    combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_m_ee"+quant.first+systint2str(thisSyst)));
                    combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_m_emu"+quant.first+systint2str(thisSyst)));
                    combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_m_mumu"+quant.first+systint2str(thisSyst)));
                
                    // if you want mu only:
                    //auto combohist1 = (TH1EFT*)hist[i].FindObject("2lss_p_mumu"+quant.first+systint2str(thisSyst))->Clone("2lss"+quant.first+systint2str(thisSyst));
                    //combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_m_mumu"+quant.first+systint2str(thisSyst)));
            
                    hist[i].Add(combohist1);
            
                    auto combohist2 = (TH1EFT*)hist[i].FindObject("3l_ppp"+quant.first+systint2str(thisSyst))->Clone("3l_mix"+quant.first+systint2str(thisSyst));
                    combohist2->Add((TH1EFT*)hist[i].FindObject("3l_mmm"+quant.first+systint2str(thisSyst)));
                    combohist2->Add((TH1EFT*)hist[i].FindObject("3l_mix_p"+quant.first+systint2str(thisSyst)));
                    combohist2->Add((TH1EFT*)hist[i].FindObject("3l_mix_m"+quant.first+systint2str(thisSyst)));
            
                    hist[i].Add(combohist2);           

                }
                else
                {
                // --------------- //
                // Mainly for SRs  //
            
                    ((TH1EFT*)hist[i].FindObject("3l_mix_p_1b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("3l_ppp_1b."+quant.first+systint2str(thisSyst)));
                    ((TH1EFT*)hist[i].FindObject("3l_mix_m_1b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("3l_mmm_1b."+quant.first+systint2str(thisSyst)));
                    ((TH1EFT*)hist[i].FindObject("3l_mix_p_2b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("3l_ppp_2b."+quant.first+systint2str(thisSyst)));
                    ((TH1EFT*)hist[i].FindObject("3l_mix_m_2b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("3l_mmm_2b."+quant.first+systint2str(thisSyst)));
                    
                    
                    // if you want to merge hist bins:
//                     for (const TString cat : cats)
//                     {
//                         auto tomerge = (TH1EFT*)hist[i].FindObject(cat+quant.first+systint2str(thisSyst));
//                         WCFit newfit = tomerge->GetSumFit();
//                         tomerge->Rebin(4); // assumes hist has 4 bins!
//                         tomerge->hist_fits.clear(); // should already have been cleared by calling Rebin(), but just making sure
//                         tomerge->hist_fits.push_back(newfit);
//                     }
                    
                    
                    // if you want to merge cats ala CR plots (Clone has problems):
//                     ((TH1EFT*)hist[i].FindObject("2lss_p_ee_2b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("2lss_p_emu_2b."+quant.first+systint2str(thisSyst)));
//                     ((TH1EFT*)hist[i].FindObject("2lss_p_ee_2b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("2lss_p_mumu_2b."+quant.first+systint2str(thisSyst)));
//                     ((TH1EFT*)hist[i].FindObject("2lss_p_ee_2b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("2lss_m_ee_2b."+quant.first+systint2str(thisSyst)));
//                     ((TH1EFT*)hist[i].FindObject("2lss_p_ee_2b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("2lss_m_emu_2b."+quant.first+systint2str(thisSyst)));
//                     ((TH1EFT*)hist[i].FindObject("2lss_p_ee_2b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("2lss_m_mumu_2b."+quant.first+systint2str(thisSyst)));
//                     ((TH1EFT*)hist[i].FindObject("2lss_p_ee_2b."+quant.first+systint2str(thisSyst)))->SetName("2lss."+quant.first+systint2str(thisSyst));
                }
                
                // for sync
//                 if(quant.first=="__jet_nCharged_tracks")
//                 {
//                     ((TH1EFT*)hist[i].FindObject("all"+quant.first))->SetTitle(";jetNDauChargedMVASel");
//                 }

                
            }
        }
    }  
    
    groupsamples = false;

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
                canvect[j].first->addPlotData(*this,"same",i,"samp",canvect[j].second,"E"); // "E1X0"
            }

            continue;
        }
        
        for (int j=0; j<canvect.size(); j++)
        {
            //canvect[j].first->addPlot(*this, "same", i, "samp");
            
            canvect[j].first->addStackWithSumMC(*this,"same",i,"samp",canvect[j].second);
            
            ////canvect[j].first->addPlotNorm(*this, "same", i, "samp",canvect[j].second,"E");
            //if (samples[i]<40) canvect[j].first->addPlotNorm(*this, "same", i, "samp",canvect[j].second,"E");
            //else if (samples[i]<94) canvect[j].first->addPlotNormTH1EFT(*this, "same", i,wc,"samp",canvect[j].second,"hist");
        }              

    }
    
    //can1->printStackContents();
    //can1->printStackContentsLatex();
//    can1->printCombosLatex(*this);

    //cancategory_yields_njets_nbjets->printStackContentsLatex();
    //cancategory_yields_njets_nbjets->printStackContentsForCard(*this);
        
    
    // if you're plotting the per-category hists:
    
    //cout << !canvect[0].first->sumDiboson << endl;
    
    bool doprintout = true;
    
    if (doprintout)
    {
        
        if (sr)
        {
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
        }
        else
        {
            cout << "\\hline" << endl;
            cout << " & 2lss";
            cout << " & 3l_mix";
            cout << " & 3l_mix_sfz";
            cout << " \\\\ " << endl;
            cout << "\\hline" << endl;
        }

    
        if (groupsamples) // should figure out why you need this
        {
    
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
    
        }
    
    //     cout << "Single Top";
    //     for (int j=0; j<canvect.size(); j++)
    //     {        
    //         cout << " & " << std::fixed << std::setprecision(2) << canvect[j].first->sumSingleTop->Integral();
    //     }        
    //     cout << " \\\\ " << endl;    
        
        std::vector<std::map<int,double>> ylds = {{{-1,0.}},{{-1,0.}},{{-1,0.}}}; // assumes 3 cats at most
        std::vector<std::map<int,double>> ylds_unc = {{{-1,0.}},{{-1,0.}},{{-1,0.}}}; // assumes 3 cats at most
            
        if (!groupsamples)
        {
            for (int i=0; i<numsamples; i++)
            {
                if (samples[i]==getComboSampInt(samples[i])) // finds ones that AREN'T in a combo
                {
                    cout << sample_names[samples[i]];
                    for (int j=0; j<canvect.size(); j++)
                    {
                        auto hist = (TH1*)canvect[j].first->thestack->GetHists()->At(i);
                        double integral = 0.;
                        double error = 0.;
                        for (int bin=1; bin<=hist->GetNbinsX(); bin++)
                        {
                            integral += hist->GetBinContent(bin);
                            error += hist->GetBinError(bin)*hist->GetBinError(bin);
                        }
                        error = sqrt(error);
                        
                        //cout << " & " << std::fixed << std::setprecision(2) << ((TH1*)canvect[j].first->thestack->GetHists()->At(i))->Integral(); // Oh Yeah. Ridiculous index + pointer achievement unlocked
                        cout << " & " << std::fixed << std::setprecision(2) << integral << " +/- " << error; 
                        if (!sr) ylds[j][samples[i]] = integral;
                        if (!sr) ylds_unc[j][samples[i]] = error;
                    }
                    cout << " \\\\ " << endl;
                }
            }
        }
        cout << "\\hline" << endl;





//         cout << "Sum Signal";
//         for (int j=0; j<canvect.size(); j++)
//         {
//             double sumsig = ((TH1*)canvect[j].first->thestack->GetStack()->Last())->Integral() - ((TH1*)canvect[j].first->thebackstack->GetStack()->Last())->Integral();
//             cout << " & " << std::fixed << std::setprecision(2) << sumsig;
//         }
//         cout << " \\\\ " << endl;
// 
//     
//         cout << "Sum Background";
//         for (int j=0; j<canvect.size(); j++)
//         {
//             cout << " & " << std::fixed << std::setprecision(2) << ((TH1*)canvect[j].first->thebackstack->GetStack()->Last())->Integral();
//         }
//         cout << " \\\\ " << endl;
//               
//         cout << "Sig/$\\sqrt{Bkgd}$";
//         for (int j=0; j<canvect.size(); j++)
//         {
//             double sumsig = ((TH1*)canvect[j].first->thestack->GetStack()->Last())->Integral() - ((TH1*)canvect[j].first->thebackstack->GetStack()->Last())->Integral();
//             sumsig = sumsig / sqrt(((TH1*)canvect[j].first->thebackstack->GetStack()->Last())->Integral());
//             cout << " & " << std::fixed << std::setprecision(2) << sumsig;
//         }
//         cout << " \\\\ " << endl;
//     
//         cout << " " << endl;
//         cout << "Sum error band (up)";
//         for (int j=0; j<canvect.size(); j++)
//         {
//             cout << " & " << std::fixed << std::setprecision(2) << canvect[j].first->sumMCbandNoStat->GetErrorYhigh(0);
//         }
//         cout << " \\\\ " << endl;
//         cout << "Sum error band (down)";
//         for (int j=0; j<canvect.size(); j++)
//         {
//             cout << " & " << std::fixed << std::setprecision(2) << canvect[j].first->sumMCbandNoStat->GetErrorYlow(0);
//         }
//         cout << " \\\\ " << endl;    
//     
//         cout << "\\hline" << endl;
//         cout << "S+B";
//         for (int j=0; j<canvect.size(); j++)
//         {
//             double toterrup = sqrt(canvect[j].first->sumMCbandNoStat->GetErrorYhigh(0)*canvect[j].first->sumMCbandNoStat->GetErrorYhigh(0) + ((TH1*)canvect[j].first->sumdata)->Integral());
//             double toterrdown = sqrt(canvect[j].first->sumMCbandNoStat->GetErrorYlow(0)*canvect[j].first->sumMCbandNoStat->GetErrorYlow(0) + ((TH1*)canvect[j].first->sumdata)->Integral());
//             cout << " & " << std::fixed << std::setprecision(2) << ((TH1*)canvect[j].first->thestack->GetStack()->Last())->Integral() << "$^{+" << toterrup << "}_{-" << toterrdown << "}$";
//         }
//         cout << " \\\\ " << endl;
//     
//     
//         cout << "\\hline" << endl;
//         cout << "Data";
//         for (int j=0; j<canvect.size(); j++)
//         {
//             cout << " & " << std::fixed << std::setprecision(0) << ((TH1*)canvect[j].first->sumdata)->Integral();
//         }
//         cout << " \\\\ " << endl;
//         cout << "\\hline" << endl;
        
        
        
        
        
        // prob leave this commented out most of time?
        if (!sr) 
        {
            for (int blah=0; blah<cats.size(); blah++)
            {
                cout << " " << endl;
                cout << cats[blah] << endl;
                cout << sample_names[85] << ": " << 100*(ylds[blah][85] - ylds[blah][8]) / ylds[blah][8] << "$\pm$" << 100*sqrt(pow(ylds_unc[blah][85],2) + pow(ylds_unc[blah][8],2)) / ylds[blah][8] << endl;
                cout << sample_names[86] << ": " << 100*(ylds[blah][86] - ylds[blah][9]) / ylds[blah][9] << "$\pm$" << 100*sqrt(pow(ylds_unc[blah][86],2) + pow(ylds_unc[blah][9],2)) / ylds[blah][9] << endl;
                cout << sample_names[84] << ": " << 100*(ylds[blah][84] - ylds[blah][1]) / ylds[blah][1] << "$\pm$" << 100*sqrt(pow(ylds_unc[blah][84],2) + pow(ylds_unc[blah][1],2)) / ylds[blah][1] << endl;
                cout << sample_names[87] << ": " << 100*(ylds[blah][87] - ylds[blah][26]) / ylds[blah][26] << "$\pm$" << 100*sqrt(pow(ylds_unc[blah][87],2) + pow(ylds_unc[blah][26],2)) / ylds[blah][26] << endl;
            }
        }
            
// 85 // ttlnu_multidim
// 86 // ttll_multidim
// 84 // ttH_multidim
// 87 // tllq_multidim
// 
// 
// 8 // ttW   
// 9 // ttZ    
// 1 // ttH  
// 26 // tZq
            
            
            
        
    }
    
}

