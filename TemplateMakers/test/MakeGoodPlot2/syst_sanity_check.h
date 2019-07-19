void MakeGoodPlot::syst_sanity_check()
{
    
    
    std::vector<std::pair<GoodPlot*,int>> canvect;
    
    //canvect.push_back({new GoodPlot("category_yields","darren"),-1});
    //canvect.push_back({new GoodPlot("category_yields_njets_nbjets","darren"),-1});
    
    vector<TString> cats;
    vector<std::pair<TString,int>> quants;
    
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
    

//     quants.push_back({".",-1});
//      quants.push_back({"__nbjets.",-1});
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
    
    
    // or ...
    
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
    //cats.push_back("ge5l_1b.");
    
    quants.push_back({"",-1});
    
//     cats.push_back("2lss"); // if you don't want the combo plots just comment this    
//     cats.push_back("3l_mix"); // if you don't want the combo plots just comment this
//     cats.push_back("3l_mix_sfz"); // if you don't want the combo plots just comment this

    cats.push_back("2lss.");
    cats.push_back("3l.");


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
            {
                // mainly for CRs //
            
 //                auto combohist1 = (TH1D*)hist[i].FindObject("2lss_p_ee"+quant.first+systint2str(thisSyst))->Clone("2lss"+quant.first+systint2str(thisSyst));
//                 combohist1->Add((TH1D*)hist[i].FindObject("2lss_p_emu"+quant.first+systint2str(thisSyst)));
//                 combohist1->Add((TH1D*)hist[i].FindObject("2lss_p_mumu"+quant.first+systint2str(thisSyst)));
//                 combohist1->Add((TH1D*)hist[i].FindObject("2lss_m_ee"+quant.first+systint2str(thisSyst)));
//                 combohist1->Add((TH1D*)hist[i].FindObject("2lss_m_emu"+quant.first+systint2str(thisSyst)));
//                 combohist1->Add((TH1D*)hist[i].FindObject("2lss_m_mumu"+quant.first+systint2str(thisSyst)));
//             
//                 hist[i].Add(combohist1);
//             
//                 auto combohist2 = (TH1D*)hist[i].FindObject("3l_ppp"+quant.first+systint2str(thisSyst))->Clone("3l_mix"+quant.first+systint2str(thisSyst));
//                 combohist2->Add((TH1D*)hist[i].FindObject("3l_mmm"+quant.first+systint2str(thisSyst)));
//                 combohist2->Add((TH1D*)hist[i].FindObject("3l_mix_p"+quant.first+systint2str(thisSyst)));
//                 combohist2->Add((TH1D*)hist[i].FindObject("3l_mix_m"+quant.first+systint2str(thisSyst)));
//                //combohist2->Add((TH1D*)hist[i].FindObject("3l_mix_sfz"+quant.first));
//            
//                hist[i].Add(combohist2);            
            
                // --------------- //
                // Mainly for SRs  //
            
                //(TH1D*)hist[i].FindObject("3l_mix_p"+quant.first)->Add((TH1D*)hist[i].FindObject("3l_ppp"+quant.first));
                //(TH1D*)hist[i].FindObject("3l_mix_m"+quant.first)->Add((TH1D*)hist[i].FindObject("3l_mmm"+quant.first));
                ((TH1EFT*)hist[i].FindObject("3l_mix_p_1b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("3l_ppp_1b."+quant.first+systint2str(thisSyst)));
                ((TH1EFT*)hist[i].FindObject("3l_mix_m_1b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("3l_mmm_1b."+quant.first+systint2str(thisSyst)));
                ((TH1EFT*)hist[i].FindObject("3l_mix_p_2b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("3l_ppp_2b."+quant.first+systint2str(thisSyst)));
                ((TH1EFT*)hist[i].FindObject("3l_mix_m_2b."+quant.first+systint2str(thisSyst)))->Add((TH1EFT*)hist[i].FindObject("3l_mmm_2b."+quant.first+systint2str(thisSyst)));
                

                auto combohist1 = (TH1D*)hist[i].FindObject("2lss_p_ee_2b."+quant.first+systint2str(thisSyst))->Clone("2lss."+quant.first+systint2str(thisSyst));
                combohist1->Add((TH1D*)hist[i].FindObject("2lss_p_emu_2b."+quant.first+systint2str(thisSyst)));
                combohist1->Add((TH1D*)hist[i].FindObject("2lss_p_mumu_2b."+quant.first+systint2str(thisSyst)));
                combohist1->Add((TH1D*)hist[i].FindObject("2lss_m_ee_2b."+quant.first+systint2str(thisSyst)));
                combohist1->Add((TH1D*)hist[i].FindObject("2lss_m_emu_2b."+quant.first+systint2str(thisSyst)));
                combohist1->Add((TH1D*)hist[i].FindObject("2lss_m_mumu_2b."+quant.first+systint2str(thisSyst)));

                hist[i].Add(combohist1);

                auto combohist2 = (TH1D*)hist[i].FindObject("3l_mix_p_2b."+quant.first+systint2str(thisSyst))->Clone("3l."+quant.first+systint2str(thisSyst));
                combohist2->Add((TH1D*)hist[i].FindObject("3l_mix_m_2b."+quant.first+systint2str(thisSyst)));
                combohist2->Add((TH1D*)hist[i].FindObject("3l_mix_sfz_2b."+quant.first+systint2str(thisSyst)));
                combohist2->Add((TH1D*)hist[i].FindObject("3l_mix_p_1b."+quant.first+systint2str(thisSyst)));
                combohist2->Add((TH1D*)hist[i].FindObject("3l_mix_m_1b."+quant.first+systint2str(thisSyst)));
                combohist2->Add((TH1D*)hist[i].FindObject("3l_mix_sfz_1b."+quant.first+systint2str(thisSyst)));            

                hist[i].Add(combohist2);  


            
            }
        }
    }  
    

    

    // now actually make the plots and save them:
//     for (int i=0; i<numsamples; i++)
//     //for (int i=(numsamples-1); i>=0; i--)
//     {           
//         cout << " " << endl;
//         cout << "Doing " << sample_names[samples[i]] << endl;
//         double wc = 0.;
//         
//         for (int j=0; j<canvect.size(); j++)
//         {
//            for (int thisSyst=0; thisSyst<numberOfSysts; thisSyst++) // comment out for non-"." hists
//            { 
// 		        TString legtxt = systint2str(thisSyst);
// 		        if (legtxt=="") legtxt = "samp";		
//                 //if (thisSyst>=23 && thisSyst<=28) continue;
//                 if ((thisSyst>=31 && thisSyst<=36) || thisSyst==5 || thisSyst==6 || thisSyst==39 || thisSyst==40) continue; // the case for all samps
//             	if ((thisSyst==3 || thisSyst==4)) continue; // fakes only - if doing fakes then put a "!" in front of this
//             	if (!(thisSyst==1 || thisSyst==2 || thisSyst==7 || thisSyst==8 || thisSyst==27 || thisSyst==28 || thisSyst==43 || thisSyst==44)) continue; // if cherry-picking
//             	if (samples[i]<40) canvect[j].first->addPlot(*this, canvect[j].first->GetName()+systint2str(thisSyst), 0, legtxt);
// 	    	    else canvect[j].first->addPlotTH1EFT(*this,canvect[j].first->GetName()+systint2str(thisSyst),0,wc,legtxt, -1, "E,PLC");
// 	    	    
// 		        //canvect[j].first->addStackWithSumMC(*this,"same",i,"samp",canvect[j].second);
//             	//canvect[j].first->addPlotNorm(*this, "auto", i, "samp",canvect[j].second,"E");
//             	//else if (samples[i]<94) canvect[j].first->addPlotNormTH1EFT(*this, "auto", i,wc,"samp",canvect[j].second,"E");
//         
// 	        }
// 	        //canvas.Add(canvect[j].first);              
// 	    }
//     }

    for (int i=0; i<numsamples; i++)
    //for (int i=(numsamples-1); i>=0; i--)
    {           
        cout << " " << endl;
        cout << "Doing " << sample_names[samples[i]] << endl;
        double wc = 0.;
        
        for (int j=0; j<canvect.size(); j++)
        {
           for (int thisSyst=1; thisSyst<numberOfSysts; thisSyst++) // comment out for non-"." hists //numberOfSysts
           { 
		        TString legtxt = systint2str(thisSyst);
		        if (legtxt=="") legtxt = "samp";		
                //if (thisSyst>=23 && thisSyst<=28) continue;
                
                if ((thisSyst>=31 && thisSyst<=36) || thisSyst==5 || thisSyst==6 || thisSyst==39 || thisSyst==40) continue; // the case for all samps
            	if (samples[i]==95 && !(thisSyst==3 || thisSyst==4)) continue; // fakes only
            	
            	//if (samples[i]==95 && !(thisSyst==3 || thisSyst==4 || thisSyst==5 || thisSyst==6 || thisSyst==31 || thisSyst==32 || thisSyst==33 || thisSyst==34 )) continue; // fakes only
            	
            	if (samples[i]!=95 && (thisSyst==3 || thisSyst==4)) continue; // don't consider fake systs if not fakes
            	if (samples[i]<94 && !(thisSyst==1 || thisSyst==2 || thisSyst==11 || thisSyst==12 || thisSyst==27 || thisSyst==28)) continue; // || thisSyst==43 || thisSyst==44)) continue; // if cherry-picking
            	
            	canvect[j].first->addSimpleRatio(*this, canvect[j].first->GetName()+systint2str(thisSyst),canvect[j].first->GetName(), i,legtxt, -1, "hist,PLC");

        
	        }
	        //canvas.Add(canvect[j].first);              
	    }
    }

    for (int j=0; j<canvect.size(); j++) canvas.Add(canvect[j].first);              



    
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
    cout << " & 3l (1b)";
    cout << " & 3l ($\\geq$2b)";
    cout << " & 3l (SFOS Z, 1b)";
    cout << " & 3l (SFOS Z, $\\geq$2b)";
    cout << " & $\\geq$4l";
    cout << " \\\\ " << endl;
    cout << "\\hline" << endl;
    
//     cout << "Diboson";
//     for (int j=0; j<canvect.size(); j++)
//     {        
//         cout << " & " << std::fixed << std::setprecision(2) << canvect[j].first->sumDiboson->Integral();
//     }
//     cout << " \\\\ " << endl;
// 
//     cout << "Triboson";
//     for (int j=0; j<canvect.size(); j++)
//     {        
//         cout << " & " << std::fixed << std::setprecision(2) << canvect[j].first->sumTriboson->Integral();
//     }        
//     cout << " \\\\ " << endl;
    
//    for (int i=0; i<numsamples; i++)
//    {
//        if (samples[i]==getComboSampInt(samples[i])) // finds ones that AREN'T in a combo
//        {
//            cout << sample_names[samples[i]];
//            for (int j=0; j<canvect.size(); j++)
//            {
//                cout << " & " << std::fixed << std::setprecision(2) << ((TH1*)canvect[j].first->thestack->GetHists()->At(i))->Integral(); // Oh Yeah. Ridiculous index + pointer achievement unlocked
//            }
//            cout << " \\\\ " << endl;
//        }
//    }
//    cout << "\\hline" << endl;
              
    
}

