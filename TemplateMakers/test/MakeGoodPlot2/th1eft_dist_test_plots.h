void MakeGoodPlot::th1eft_test_plots()
{    
    
    std::vector<std::pair<GoodPlot*,int>> canvect;
    
    //canvect.push_back({new GoodPlot("category_yields","darren"),-1});
    //canvect.push_back({new GoodPlot("category_yields_njets_nbjets","darren"),-1});
    
    vector<TString> cats;
    vector<std::pair<TString,int>> quants;
    
    //cats.push_back("2los_ee");
    //cats.push_back("2los_emu");
    //cats.push_back("2los_mumu");
    //cats.push_back("2los_sfz_ee");
    //cats.push_back("2los_sfz_emu");
    //cats.push_back("2los_sfz_mumu");
//     cats.push_back("2lss_p_ee");
//     cats.push_back("2lss_p_emu");
//     cats.push_back("2lss_p_mumu");
//     cats.push_back("2lss_m_ee");
//     cats.push_back("2lss_m_emu");
//     cats.push_back("2lss_m_mumu");
//     cats.push_back("3l_ppp");
//     cats.push_back("3l_mmm");
//     cats.push_back("3l_mix");
//     cats.push_back("3l_mix_sfz");
    //cats.push_back("4l");
    //cats.push_back("1l_mu");
    //cats.push_back("1l_e");    
    
    //quants.push_back({"_1b.",-1});
    //quants.push_back({"_2b.",-1});
    
//     quants.push_back({"__nnpdfWeightUp",-1});
//     quants.push_back({"__nnpdfWeightDown",-1});
//     quants.push_back({"__muRWeightUp",-1});
//     quants.push_back({"__muRWeightDown",-1});
//     quants.push_back({"__muFWeightUp",-1});
//     quants.push_back({"__muFWeightDown",-1});



    // or ...
    // sig regions
    quants.push_back({"",-1});
//     cats.push_back("2lss_p_ee_2b.");
//     cats.push_back("2lss_p_emu_2b.");
//     cats.push_back("2lss_p_mumu_2b.");
//     cats.push_back("2lss_m_ee_2b.");
//     cats.push_back("2lss_m_emu_2b.");
//     cats.push_back("2lss_m_mumu_2b.");
//     //cats.push_back("3l_ppp_1b.");
//     //cats.push_back("3l_ppp_2b.");
//     //cats.push_back("3l_mmm_1b.");
//     //cats.push_back("3l_mmm_2b.");    
//     cats.push_back("3l_mix_p_1b.");
//     cats.push_back("3l_mix_m_1b.");
//     cats.push_back("3l_mix_p_2b.");
//     cats.push_back("3l_mix_m_2b.");
//     cats.push_back("3l_mix_sfz_1b.");
//     cats.push_back("3l_mix_sfz_2b.");
//     //cats.push_back("4l_1b.");
//     cats.push_back("4l_2b.");
    //cats.push_back("ge5l_1b.");


    // combos
    cats.push_back("2lss_p_ee_2b.");    
    cats.push_back("3l_ppp_2b."); 

    

    // construct hists for combined 2lss + 3l categories:
    for (int i=0; i<numsamples; i++)
    {     
        int thisnumberofsysts = numberOfSysts;
        if (samples[i]<40) thisnumberofsysts = 1;
        for (const auto quant : quants)
        {
            for (int thisSyst=0; thisSyst<thisnumberofsysts; thisSyst++) // comment out for "." hists // or <1
            {
                // HEY! Clone doesn't work with TH1EFTs!!!
                // if doing combos:
                //auto combohist1 = (TH1EFT*)hist[i].FindObject("2lss_p_ee_2b."+quant.first+systint2str(thisSyst))->Clone("2lss"+quant.first+systint2str(thisSyst));
                auto combohist1 = (TH1EFT*)hist[i].FindObject("2lss_p_ee_2b."+quant.first+systint2str(thisSyst));
                combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_p_emu_2b."+quant.first+systint2str(thisSyst)));
                combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_p_mumu_2b."+quant.first+systint2str(thisSyst)));
                combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_m_ee_2b."+quant.first+systint2str(thisSyst)));
                combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_m_emu_2b."+quant.first+systint2str(thisSyst)));
                combohist1->Add((TH1EFT*)hist[i].FindObject("2lss_m_mumu_2b."+quant.first+systint2str(thisSyst)));
            
                //hist[i].Add(combohist1);
            
                //auto combohist2 = (TH1EFT*)hist[i].FindObject("3l_ppp_2b."+quant.first+systint2str(thisSyst))->Clone("3l_mix"+quant.first+systint2str(thisSyst));
                auto combohist2 = (TH1EFT*)hist[i].FindObject("3l_ppp_2b."+quant.first+systint2str(thisSyst));
                combohist2->Add((TH1EFT*)hist[i].FindObject("3l_mmm_2b."+quant.first+systint2str(thisSyst)));
                combohist2->Add((TH1EFT*)hist[i].FindObject("3l_mix_p_2b."+quant.first+systint2str(thisSyst)));
                combohist2->Add((TH1EFT*)hist[i].FindObject("3l_mix_m_2b."+quant.first+systint2str(thisSyst)));
                combohist2->Add((TH1EFT*)hist[i].FindObject("3l_mix_sfz_2b."+quant.first+systint2str(thisSyst)));
                combohist2->Add((TH1EFT*)hist[i].FindObject("3l_ppp_1b."+quant.first+systint2str(thisSyst)));
                combohist2->Add((TH1EFT*)hist[i].FindObject("3l_mmm_1b."+quant.first+systint2str(thisSyst)));
                combohist2->Add((TH1EFT*)hist[i].FindObject("3l_mix_p_1b."+quant.first+systint2str(thisSyst)));
                combohist2->Add((TH1EFT*)hist[i].FindObject("3l_mix_m_1b."+quant.first+systint2str(thisSyst)));
                combohist2->Add((TH1EFT*)hist[i].FindObject("3l_mix_sfz_1b."+quant.first+systint2str(thisSyst)));
                
                //hist[i].Add(combohist2);            

                
            }
        }
    }  


    for (const TString cat : cats)
    {
        for (const auto quant : quants)
        {
            canvect.push_back({new GoodPlot(cat+quant.first,"darren"),quant.second});
        }
    }


    // now actually make the plots and save them:
    for (int i=0; i<numsamples; i++)
    {           
        double wc = 0.; // set to ctZ
        if (samples[i]<40)
        {
            for (int j=0; j<canvect.size(); j++)
            {
                canvect[j].first->addPlot(*this,"same",i,"samp", -1, "E,PLC");
                //addPlot(MakeGoodPlot &thisMGP, TString thehist, int i, TString legtext="none", int rebin=-1, TString drawopt="hist,PLC");
                //canvect[j].first->addPlotNorm(*this,"auto",i,"samp");
            } 
        }
        else
        {
            for (int j=0; j<canvect.size(); j++)
            {
                //addPlotTH1EFT(MakeGoodPlot &thisMGP, TString thehist, int i, double wc=0., TString legtext="none", int rebin=-1, TString drawopt="hist,PLC");
                //canvect[j].first->addPlotTH1EFT(*this,"same",i,wc,"samp", -1, "E,PLC");    //(*this,"same",i,"samp",canvect[j].second);
                canvect[j].first->addStackWithSumMC(*this,"same",i,"samp",canvect[j].second,true);           
                //canvect[j].first->addPlotNormTH1EFT(*this,"auto",i,wc,"samp");    //(*this,"same",i,"samp",canvect[j].second);
            }
        }              
        
    }





          
    
}