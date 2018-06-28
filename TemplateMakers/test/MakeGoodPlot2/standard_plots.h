void MakeGoodPlot::standard_plots()
{
    
    std::vector<GoodPlot*> canvect;
    
    //canvect.push_back(new GoodPlot("category_yields","darren"));
    //canvect.push_back(new GoodPlot("category_yields_njets_nbjets","darren"));
    
    vector<TString> cats;
    vector<TString> quants;
    
    //cats.push_back("2los_ee");
    //cats.push_back("2los_emu");
    //cats.push_back("2los_mumu");
    //cats.push_back("2los_sfz_ee");
    //cats.push_back("2los_sfz_emu");
    //cats.push_back("2los_sfz_mumu");
    cats.push_back("2lss_p_ee");
    cats.push_back("2lss_p_emu");
    cats.push_back("2lss_p_mumu");
    cats.push_back("2lss_m_ee");
    cats.push_back("2lss_m_emu");
    cats.push_back("2lss_m_mumu");
//     cats.push_back("3l_ppp");
//     cats.push_back("3l_mmm");
//     cats.push_back("3l_mix");
//     cats.push_back("3l_mix_sfz");
    //cats.push_back("4l");
    //cats.push_back("1l_mu");
    //cats.push_back("1l_e");
    
//    cats.push_back("2lss"); // if you don't want the combo plots just comment this    
//    cats.push_back("3l"); // if you don't want the combo plots just comment this

    quants.push_back("__njets");
    quants.push_back("__nbjets");
//     quants.push_back("__jetpt");
// //     quants.push_back("__jeteta");
// //     quants.push_back("__jetcsv");
// //     quants.push_back("__jetDeepCSVprobb");
// //     quants.push_back("__jetDeepCSVprobbb");
//      quants.push_back("__leppt");
//      quants.push_back("__lep1pt");
//      quants.push_back("__lep2pt");
// //     quants.push_back("__lepeta");
// //     quants.push_back("__llmass");
// //     quants.push_back("__lepMVA");    
//      quants.push_back("__met");
// //     quants.push_back("__metphi");
//      quants.push_back("__MHT");    
// //     quants.push_back("__numPVs");
// //     quants.push_back("__PUMVA");
// //     quants.push_back("__qgid");
// //     quants.push_back("__dxy");
// //     quants.push_back("__dz");
// //     quants.push_back("__miniIso");
// //     quants.push_back("__miniIsoR");
// //     quants.push_back("__miniIsoCharged");
// //     quants.push_back("__miniIsoNeutral");
// //     quants.push_back("__jetPtRatio");
// //     quants.push_back("__jetPtRel");
// //     quants.push_back("__nearestJetCSV");
// //     quants.push_back("__sip3D");
// //     quants.push_back("__jet_nCharged_tracks");
// //     quants.push_back("__effArea");
// //     quants.push_back("__rho");
//      quants.push_back("__correctedPt");

    for (const TString cat : cats)
    {
        for (const TString quant : quants)
        {
            canvect.push_back(new GoodPlot(cat+quant,"darren"));
        }
    }
    
    
    
    // construct hists for combined 2lss + 3l categories:
    for (int i=0; i<numsamples; i++)
    {     
        for (const TString quant : quants)
        {
            auto combohist1 = (TH1D*)hist[i].FindObject("2lss_p_ee"+quant)->Clone("2lss"+quant);
            combohist1->Add((TH1D*)hist[i].FindObject("2lss_p_emu"+quant));
            combohist1->Add((TH1D*)hist[i].FindObject("2lss_p_mumu"+quant));
            combohist1->Add((TH1D*)hist[i].FindObject("2lss_m_ee"+quant));
            combohist1->Add((TH1D*)hist[i].FindObject("2lss_m_emu"+quant));
            combohist1->Add((TH1D*)hist[i].FindObject("2lss_m_mumu"+quant));
            
            hist[i].Add(combohist1);
            
            auto combohist2 = (TH1D*)hist[i].FindObject("3l_ppp"+quant)->Clone("3l"+quant);
            combohist2->Add((TH1D*)hist[i].FindObject("3l_mmm"+quant));
            combohist2->Add((TH1D*)hist[i].FindObject("3l_mix"+quant));
            combohist2->Add((TH1D*)hist[i].FindObject("3l_mix_sfz"+quant));
            
            hist[i].Add(combohist2);            
            

        }
    }  
    

    

    // now actually make the plots and save them:
    for (int i=0; i<numsamples; i++)
    //for (int i=(numsamples-1); i>=0; i--)
    {           
        if (samples[i]>99)
        {
            for (int j=0; j<canvect.size(); j++)
            {
                canvect[j]->addPlotData(*this,"same",i,"samp",-1,"E");
            }

            continue;
        }
        
        for (int j=0; j<canvect.size(); j++)
        {
            canvect[j]->addStackWithSumMC(*this,"same",i,"samp");
        }              

    }
  
    //can1->printStackContents();
    //can1->printStackContentsLatex();
//    can1->printCombosLatex(*this);

    //cancategory_yields_njets_nbjets->printStackContentsLatex();
    //cancategory_yields_njets_nbjets->printStackContentsForCard(*this);
        
               
    
}
