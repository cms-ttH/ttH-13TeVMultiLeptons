void MakeGoodPlot::fr_studies_plots()
{
    
    //std::vector<std::pair<GoodPlot*,int>> canvect;
    
    
    vector<TString> cats;
    vector<std::pair<TString,int>> quants;
    

    
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
//     quants.push_back({"FRUP",-1});
//     quants.push_back({"FRDOWN",-1});
//     quants.push_back({"FRQCD",-1});
//     quants.push_back({"FRTTBAR",-1});
//     quants.push_back({"FRPT1",-1});
//     quants.push_back({"FRPT2",-1});
//     quants.push_back({"FRETA1",-1});
//     quants.push_back({"FRETA2",-1});

    
    cats.push_back("2lss."); // if you don't want the combo plots just comment this    
    cats.push_back("3l."); // if you don't want the combo plots just comment this


    
    
    // construct hists for combined 2lss + 3l categories:
    for (int i=0; i<numsamples; i++)
    {     
        for (const auto quant : quants)
        {
            auto combohist1 = (TH1D*)hist[i].FindObject("2lss_p_ee_2b."+quant.first)->Clone("2lss."+quant.first);
            combohist1->Add((TH1D*)hist[i].FindObject("2lss_p_emu_2b."+quant.first));
            combohist1->Add((TH1D*)hist[i].FindObject("2lss_p_mumu_2b."+quant.first));
            combohist1->Add((TH1D*)hist[i].FindObject("2lss_m_ee_2b."+quant.first));
            combohist1->Add((TH1D*)hist[i].FindObject("2lss_m_emu_2b."+quant.first));
            combohist1->Add((TH1D*)hist[i].FindObject("2lss_m_mumu_2b."+quant.first));
            
            hist[i].Add(combohist1);
            
            auto combohist2 = (TH1D*)hist[i].FindObject("3l_ppp_2b."+quant.first)->Clone("3l."+quant.first);
            combohist2->Add((TH1D*)hist[i].FindObject("3l_mmm_2b."+quant.first));
            combohist2->Add((TH1D*)hist[i].FindObject("3l_mix_p_2b."+quant.first));
            combohist2->Add((TH1D*)hist[i].FindObject("3l_mix_m_2b."+quant.first));
            combohist2->Add((TH1D*)hist[i].FindObject("3l_mix_sfz_2b."+quant.first));
            combohist2->Add((TH1D*)hist[i].FindObject("3l_mix_p_1b."+quant.first));
            combohist2->Add((TH1D*)hist[i].FindObject("3l_mix_m_1b."+quant.first));
            combohist2->Add((TH1D*)hist[i].FindObject("3l_mix_sfz_1b."+quant.first));            
            
            hist[i].Add(combohist2);            
            

        }
    }  
    

    

    // now actually make the plots and save them:

    for (const TString cat : cats)
    {
        //GoodPlot *frpltcls = new GoodPlot(cat,"darren",1,2);
        GoodPlot *frpltcls = new GoodPlot(cat,"darren");
        GoodPlot *frpltup = new GoodPlot(cat+"FRUP","darren",1,2);
        GoodPlot *frpltdown = new GoodPlot(cat+"FRDOWN","darren",1,2);
        GoodPlot *frpltpt1 = new GoodPlot(cat+"FRPT1","darren",1,2);
        GoodPlot *frpltpt2 = new GoodPlot(cat+"FRPT2","darren",1,2);
        GoodPlot *frplteta1 = new GoodPlot(cat+"FRETA1","darren",1,2);
        GoodPlot *frplteta2 = new GoodPlot(cat+"FRETA2","darren",1,2);
        
        for (const auto quant : quants)
        {    
            TString legtxt = quant.first;
            if (legtxt=="") legtxt = "samp";
            frpltcls->addPlot(*this, cat+quant.first, 0, legtxt, -1, "E");
            frpltup->addPlot(*this, cat+quant.first, 0, legtxt);
            frpltdown->addPlot(*this, cat+quant.first, 0, legtxt);
            frpltpt1->addPlot(*this, cat+quant.first, 0, legtxt);
            frpltpt2->addPlot(*this, cat+quant.first, 0, legtxt); 
            frplteta1->addPlot(*this, cat+quant.first, 0, legtxt);
            frplteta2->addPlot(*this, cat+quant.first, 0, legtxt);

                 
        }
        
        //frplt->addSimpleRatio(*this, cat+"FRTTBAR", cat+"FRQCD", 0, "(FRTTBAR-FRQCD)/FRQCD",-1,"E",2);
        
//         frpltcls->addSimpleRatio(*this, cat+"FRTTBAR", cat+"FRQCD", 0, "(FRTTBAR-FRQCD)/FRQCD");
//         
//         frpltup->addSimpleRatio(*this, cat+"FRUP", cat, 0, "(FRUP-Fakes)/Fakes");
//         frpltdown->addSimpleRatio(*this, cat+"FRDOWN", cat, 0, "(FRDOWN-Fakes)/Fakes");
//         
//         frpltpt1->addSimpleRatio(*this, cat+"FRPT1", cat, 0, "(X-Fakes)/Fakes");
//         frpltpt2->addSimpleRatio(*this, cat+"FRPT2", cat, 0, "(X-Fakes)/Fakes");
//         frplteta1->addSimpleRatio(*this, cat+"FRETA1", cat, 0, "(X-Fakes)/Fakes");
//         frplteta2->addSimpleRatio(*this, cat+"FRETA2", cat, 0, "(X-Fakes)/Fakes");

        
        canvas.Add(frpltcls);
        //canvas.Add(frpltup);
        //canvas.Add(frpltdown);
        
//         canvas.Add(frpltpt1);
//         canvas.Add(frpltpt2);
//         canvas.Add(frplteta1);
//         canvas.Add(frplteta2);
        
    }
    

    
}

