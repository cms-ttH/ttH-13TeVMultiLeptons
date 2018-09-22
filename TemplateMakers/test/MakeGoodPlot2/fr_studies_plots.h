void MakeGoodPlot::fr_studies_plots()
{
    
    //std::vector<std::pair<GoodPlot*,int>> canvect;
    
    
    vector<TString> cats;
    vector<std::pair<TString,int>> quants;
    

    
    cats.push_back("2lss_p_ee_2b.");
//     cats.push_back("2lss_p_emu_2b.");
//     cats.push_back("2lss_p_mumu_2b.");
//     cats.push_back("2lss_m_ee_2b.");
//     cats.push_back("2lss_m_emu_2b.");
//     cats.push_back("2lss_m_mumu_2b.");
//     //cats.push_back("3l_ppp_1b.");
//     //cats.push_back("3l_ppp_2b.");
//     //cats.push_back("3l_mmm_1b.");
//     //cats.push_back("3l_mmm_2b.");
//     cats.push_back("3l_mix_1b.");
//     cats.push_back("3l_mix_2b.");
//     cats.push_back("3l_mix_sfz_1b.");
//     cats.push_back("3l_mix_sfz_2b.");
//     cats.push_back("4l_1b.");
    //cats.push_back("4l_2b.");
    //cats.push_back("ge5l_1b.");
    
    quants.push_back({"",-1});    
    quants.push_back({"FRUP",-1});
    quants.push_back({"FRDOWN",-1});
    quants.push_back({"FRQCD",-1});
    quants.push_back({"FRTTBAR",-1});

    
//    cats.push_back("2lss"); // if you don't want the combo plots just comment this    
//    cats.push_back("3l"); // if you don't want the combo plots just comment this


    
    
    // construct hists for combined 2lss + 3l categories:
//     for (int i=0; i<numsamples; i++)
//     {     
//         for (const auto quant : quants)
//         {
//             auto combohist1 = (TH1D*)hist[i].FindObject("2lss_p_ee"+quant.first)->Clone("2lss"+quant.first);
//             combohist1->Add((TH1D*)hist[i].FindObject("2lss_p_emu"+quant.first));
//             combohist1->Add((TH1D*)hist[i].FindObject("2lss_p_mumu"+quant.first));
//             combohist1->Add((TH1D*)hist[i].FindObject("2lss_m_ee"+quant.first));
//             combohist1->Add((TH1D*)hist[i].FindObject("2lss_m_emu"+quant.first));
//             combohist1->Add((TH1D*)hist[i].FindObject("2lss_m_mumu"+quant.first));
//             
//             hist[i].Add(combohist1);
//             
//             auto combohist2 = (TH1D*)hist[i].FindObject("3l_ppp"+quant.first)->Clone("3l"+quant.first);
//             combohist2->Add((TH1D*)hist[i].FindObject("3l_mmm"+quant.first));
//             combohist2->Add((TH1D*)hist[i].FindObject("3l_mix"+quant.first));
//             combohist2->Add((TH1D*)hist[i].FindObject("3l_mix_sfz"+quant.first));
//             
//             hist[i].Add(combohist2);            
//             
// 
//         }
//     }  
    

    

    // now actually make the plots and save them:

    for (const TString cat : cats)
    {
        GoodPlot *frplt = new GoodPlot(cat,"darren",1,2);
        
        for (const auto quant : quants)
        {    
            TString legtxt = quant.first;
            if (legtxt=="") legtxt = "samp";
            frplt->addPlot(*this, cat+quant.first, 0, legtxt);
                 
        }
        
        //frplt->addSimpleRatio(*this, cat+"FRTTBAR", cat+"FRQCD", 0, "(FRTTBAR-FRQCD)/FRQCD",-1,"E",2);
        frplt->addSimpleRatio(*this, cat+"FRTTBAR", cat+"FRQCD", 0, "(FRTTBAR-FRQCD)/FRQCD");
        
        canvas.Add(frplt);
    }
    

    
}

